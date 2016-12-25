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
	char * buffer;
	int in_buffer; 
	int buffer_space; //May not need this
	int max_read; //May not need
    struct in_addr ipaddr;
	char * colour;
    struct Client * next;
}Client;


void set_verbose(int);
void report(char *, ...);
int find_network_newline(char * str, int in_buffer);
void diagnostic_buffer_print(char * buf);
char * get_colour();
ssize_t readLine(int fd, void *buffer, size_t n);

int setup();
