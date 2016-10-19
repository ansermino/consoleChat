#include "server_tools.h"
#include "chat_server.h"



static int listenfd;

Client * top_c;

int main(void){
    listenfd = setup();

    while(1){
        fd_set fds;
        int max_fd = listenfd;
        FD_ZERO(&fds);
        FD_SET(listenfd, &fds);
        if(select(max_fd + 1, &fds, NULL, NULL, 0) < 0){
            perror("select");
        }
        else{
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

void shutdownServer(){
    // Free all clients
}
