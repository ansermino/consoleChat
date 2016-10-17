#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>


#ifndef PORT
    #define PORT 30000
#endif


int setup(char * argv){
    int sockfd;
    struct sockadd_in peer;

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
}

int main(int argc, char * argv){
    int sockfd;
    struct sockadd_in peer;

    if(argc != 2){
        fprintf(stderr, "Need server address!\n");
        exit(1);
    }

    sockfd = setup(argv);
    runClient();
}

void runClient(void){
    chooseUsername();
    chat();
}

void terminate(void){

}