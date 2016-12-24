#ifndef CONSOLECHAT_CHAT_CLIENT_H
#define CONSOLECHAT_CHAT_CLIENT_H

#endif //CONSOLECHAT_CHAT_CLIENT_H

#include "client_tools.h"
//#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <sys/select.h>

void display_header();
void read_stdin();
void create_data_buffer();
void set_username();
void write_to_server(char * text);

