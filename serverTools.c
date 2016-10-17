#include "serverTools.h"


int setup(void){
    int listenfd;
    int on = 1, status;
    struct sockaddr_in self;
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }
    status = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const char *) &on, sizeof(on));
    if(status == -1) {
        perror("setsockopt -- REUSEADDR");
    }

    self.sin_family = AF_INET;
    self.sin_addr.s_addr = INADDR_ANY;
    self.sin_port = htons(PORT);
    memset(&self.sin_zero,0, sizeof(self.sin_zero));

    fprintf(stderr, "Listening on port %d\n", PORT);

    if(bind(listenfd, (struct sockaddr *)&self, sizeof(self)) == -1){
        perror("bind");
        exit(1);
    }
    if(listen(listenfd, MAX_BACKLOG_QUEUE) == -1){
        perror("listen");
        exit(1);
    }
    return listenfd;
}
