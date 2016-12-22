#include "chat_client.h"


#ifndef PORT
    #define PORT 30000
#endif

static int sockfd;
static int MAX_READ_BUFFER;


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
    run_client();
}

void run_client(void){
    //chooseUsername();
    chat();
}

void chat(){
    while(1){
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        FD_SET(sockfd, &fds);
        if(select(sockfd + 1, &fds, NULL, NULL, 0) < 0){
            perror("select");
        }
        else{
            if(FD_ISSET(STDIN_FILENO, &fds)){
                char * buffer = malloc(MAX_READ_BUFFER);
                read_line(sockfd, buffer, MAX_READ_BUFFER);
                fprintf(stderr, "STDIN: %s\n", buffer);
                write_to_server(buffer);
            }
            if(FD_ISSET(sockfd, &fds)){
                char * buffer = malloc(MAX_READ_BUFFER);
                read_line(sockfd, buffer, MAX_READ_BUFFER);
            }
        }

    }
}

void write_to_server(char * msg){
    int write_size = strlen(msg) * sizeof(char); // Is sizeof(char) redundant?
    if(write(sockfd, msg, write_size) != write_size){
        perror("write failed");
    }
    char * end_of_line = "\r\n";
    write(sockfd,end_of_line, sizeof(end_of_line));
    report("Sent: %s\n", msg);
}

void terminate(void){

}
