#include "serverTools.h"



//static int listenfd;


int main(void){
    int listenfd = setup();

    while(1){
        fd_set fds;
        int max_fd = listenfd;
        FD_ZERO(&fds);
        FD_SET(listenfd, &fds);

    }
}
