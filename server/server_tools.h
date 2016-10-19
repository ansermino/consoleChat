#ifndef SERVER_TOOLS_H
#define SERVER_TOOLS_H

#endif //CONSOLECHAT_SERVERTOOLS_H


#ifndef PORT
    #define PORT 59247
#endif

#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/types.h>
#include <ctype.h>
#include <time.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/signal.h>
#include <signal.h>

typedef struct Client{
    int fd;
    char * username;
    struct in_addr ipaddr;
    struct Client * next;
}Client;


void set_verbose(int);
void report(char *, ...);

int setup();
