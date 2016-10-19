#include "server_tools.h"
#include "chat_server.h"

static int MAX_READ_BUFFER = 2048;

static int listenfd;

Client * top_c;

int main(void){
    /*struct sigaction term_signal_action;
    term_signal_action.sa_handler = shutdownServer;
    term_signal_action.sa_flags = 0;
    sigemptyset(&term_signal_action.sa_mask);
    sigaction(SIGINT, &term_signal_action, NULL);*/


    listenfd = setup();

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
        if(select(max_fd + 1, &fds, NULL, NULL, 0) < 0){
            perror("select");
        }
        else{
            for(c = top_c; c; c = c->next){
                if(FD_ISSET(c->fd, &fds)){
                    process_client(c);
                }
            }
            if(FD_ISSET(listenfd, &fds)){
                report("Creating new connection...");
                new_connection();
            }
        }

    }
}

void new_connection(){
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
    c->fd = fd;
    c->ipaddr = ipaddr;
    c->next = top_c;
    top_c = c;
    report("Client struct created.");
}

void process_client(Client * c){
    char * buffer = malloc(MAX_READ_BUFFER);
    readLine(c->fd, buffer, MAX_READ_BUFFER);
    fprintf(stderr, "Line read: %s", buffer);
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
