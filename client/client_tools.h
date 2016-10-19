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

void report(char * msg, ...);
size_t read_line(int fd, void *buffer, size_t n);
