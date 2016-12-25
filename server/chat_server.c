#include "server_tools.h"
#include "chat_server.h"

#define BLUE "\x1B[34m"
#define RESET "\x1B[0m"

static int MAX_READ_BUFFER = 2048;

static int listenfd;

const char * clr = BLUE;

Client * top_c;

int main(void){
    /*struct sigaction term_signal_action;
    term_signal_action.sa_handler = shutdownServer;
    term_signal_action.sa_flags = 0;
    sigemptyset(&term_signal_action.sa_mask);
    sigaction(SIGINT, &term_signal_action, NULL);*/


    listenfd = setup();
    struct timeval tout; //TODO: Determine if this is necessary
    tout.tv_usec = 0;
    tout.tv_sec = 5;

    while(1){
        fd_set fds;
        int max_fd = listenfd;
        Client * c;
        FD_ZERO(&fds);
        FD_SET(listenfd, &fds);
        for(c = top_c; c; c = c->next){
            FD_SET(c->fd, &fds);
            if(c->fd > max_fd){
                max_fd = c->fd;
            }
        }
        if(select(max_fd + 1, &fds, NULL, NULL, &tout) < 0){
            perror("select");
        }
        else{
            for(c = top_c; c; c = c->next){
                if(FD_ISSET(c->fd, &fds)){
                    process_incoming_data(c);
                }
            }
            if(FD_ISSET(listenfd, &fds)){
                new_connection();
            }
        }

    }
}

void new_connection(){
    report("Creating new connection...");
    int new_fd;
    struct sockaddr_in new_addr;
    socklen_t socklen = sizeof(new_addr);

    if((new_fd = accept(listenfd, (struct sockaddr*) &new_addr, &socklen)) < 0){
        perror("accept");
        exit(1);
    }
    report("New connection accepted.");
    create_client(new_fd, new_addr.sin_addr);
    report("Client created.");
}

void create_client (int fd, struct in_addr ipaddr){
    Client * c = malloc(sizeof(Client));
	c->username = malloc(10); //TODO: Replace
	c->buffer = malloc(MAX_READ_BUFFER);
	c->in_buffer = 0;
    c->fd = fd;
    c->ipaddr = ipaddr;
	c->colour = "\x1B[34m"; //get_colour(); //\x1B[34m
    c->next = top_c;
    top_c = c;
    report("Client struct created.");
}

void process_incoming_data(Client * c){
	report("Processing incoming data...");
	char * insert_ptr = c->buffer + c->in_buffer;
	int buffer_space = MAX_READ_BUFFER - c->in_buffer;
	int read_size;
	if((read_size = read(c->fd, insert_ptr, buffer_space)) >= 0){
		c->in_buffer += read_size;
		if(read_size == 0){
			remove_client(c);
			return;
		}
		int newline_index = find_network_newline(c->buffer, c->in_buffer);
		if(newline_index >= 0){
			report("Complete client request recieved.");
			c->buffer[newline_index] = '\0';
			c->buffer[newline_index + 1] = '\0';
			char cmd[newline_index + 1];
			strcpy(cmd, c->buffer);
			process_cmd(c, cmd);
			newline_index += 2;
			c->in_buffer -= newline_index;
			memmove(c->buffer, c->buffer + newline_index, c->in_buffer);
		}
	}
	else{
		perror("client read");
	}	
}

void process_cmd(Client * c, char * cmd){
	fprintf(stderr, "%s", c->colour);
	report("Processing command...");
	fprintf(stderr, RESET);
	if(strcmp(cmd, ":exit") == 0){
	    client_exit(c);
	}
	else{
		client_receive_msg(c, cmd);
	}

}

void client_exit(Client * c){
	report("Client %s is exiting.", c->username);
	char * username = malloc(sizeof(c->username));
	strcpy(username, c->username);
	remove_client(c);
	broadcast("%s has left the chat.", username);
	free(username);
}

void client_receive_msg(Client * c, char * cmd){
	if(strcmp(c->username, "") == 0){
		strncpy(c->username, cmd, 10);
		c->username[9] = '\0';
		broadcast_except(c, "%s has joined the chat.", c->username);
		return;
	}
	report("%s said: %s", c->username, cmd);
	broadcast_except(c, "%s: %s", c->username, cmd);
}

void broadcast(char * msg, ...){
	char bc_msg[128]; //TODO: Use a macro
	va_list args;
	va_start(args, msg);
	vsnprintf(bc_msg, sizeof(bc_msg), msg, args);
	va_end(args);

	report("Broadcasting: %s", bc_msg);
	Client * c = top_c;
	while(c != NULL){
		write_to_client(c, bc_msg);
		c = c->next;
	}
}

void broadcast_except(Client * exception, char * msg, ...){
	char bc_msg[128]; //TODO: Use a macro
	va_list args;
	va_start(args, msg);
	vsnprintf(bc_msg, sizeof(bc_msg), msg, args);
	va_end(args);

	report("Broadcasting(except %s): %s", exception->username, bc_msg);
	Client * c = top_c;
	while(c != NULL){
		if(c != exception){
			report("writing to client.");
			write_to_client(c, bc_msg);
		}
		c = c->next;
	}
}

void write_to_client(Client * c, char * text){
		char * msg = malloc(sizeof(msg) + 2);
		strcat(msg, text);
		strcat(msg, "\r\n");
		write(c->fd, msg, strlen(msg));
}

void remove_client(Client * c){
	report("Removing client %s...", c->username);
	Client * prev = top_c;
	Client * next = top_c->next;
	if(prev == c){
		top_c = next;
		free(c);
		return;
	}
	while(next != NULL && next != c){
		prev = next;
		next = prev->next;
	}
	if(next == c){
		prev->next = next->next;
		free(c);
	}
	else{
		report("Error removing client. Client not found.\n");
	}
}

void shutdown_server(){
    // Free all clients
    Client * c = top_c;
    Client * nextC = c->next;
    while(c){
        free(c);
        c = nextC;
    }
}
