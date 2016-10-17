#include "serverTools.h"



//static int listenfd;


#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"
int main(void){
    int listenfd = setup();

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
#pragma clang diagnostic pop
