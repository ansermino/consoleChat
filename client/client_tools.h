#ifndef CONSOLECHAT_CLIENT_TOOLS_H
#define CONSOLECHAT_CLIENT_TOOLS_H

#endif //CONSOLECHAT_CLIENT_TOOLS_H

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>

typedef struct DataBuffer{
		char * buffer;
		int fd;
		int in_buffer;
} DataBuffer;

void report(char * msg, ...);
int find_network_newline(DataBuffer * d);
int read_line(DataBuffer * db);
