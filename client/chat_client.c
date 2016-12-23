#include "chat_client.h"


#ifndef PORT
    #define PORT 30000
#endif

static int sockfd;
static int MAX_READ_BUFFER = 2048;


int setup(char ** argv){
    struct sockaddr_in peer;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("client socket");
        exit(1);
    }

    peer.sin_family = AF_INET;
    peer.sin_port = htons(PORT);
    if(inet_pton(AF_INET, argv[1], &peer.sin_addr) < 1){
        perror("client: inet_ptons");
        close(sockfd);
        exit(1);
    }

    if(connect(sockfd, (struct sockaddr *)&peer, sizeof(peer)) == -1){
        perror("client: cannot connect");
        exit(1);
    }
    return sockfd;
}

int main(int argc, char ** argv){
    struct sockaddr_in peer;

    if(argc != 2){
        fprintf(stderr, "Need server address!\n");
        exit(1);
    }

    sockfd = setup(argv);

	struct timeval tout;
	tout.tv_usec = 0;
	tout.tv_sec = 5;
    while(1){
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        FD_SET(sockfd, &fds);
        if(select(sockfd + 1, &fds, NULL, NULL, &tout) < 0){
            perror("select");
        }
        else{
            if(FD_ISSET(STDIN_FILENO, &fds)){
           		read_stdin();
			} 
            if(FD_ISSET(sockfd, &fds)){
                char * buffer = malloc(MAX_READ_BUFFER);
                if(read_line(sockfd, buffer, MAX_READ_BUFFER) == 0){
						report("Server has quit.");
						exit(0);
				}
				fprintf(stderr, "%s\n", buffer);
            }
        }

    }	
}

void read_stdin(){
	report("Reading from stdin...");
	char buffer[MAX_READ_BUFFER];
	int end; 
	if((end = read(STDIN_FILENO, &buffer, MAX_READ_BUFFER - 1)) < 0){
		perror("stdin read");
	}
	if(end == 0){ //TODO: Does this work to ignore empty messages?
		return;
	}
	buffer[end] = '\0';
	report("%s\n", buffer);
	write_to_server(buffer);
}

void write_to_server(char * text){
	char * msg = malloc(sizeof(text) + 2);
	strcat(msg, text);
	strcat(msg, "\r\n");
    if(write(sockfd, msg, sizeof(msg)) != sizeof(msg)){
        perror("write failed");
    }
    report("Sent: %s", msg);
}

void terminate(void){

}
