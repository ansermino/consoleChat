//
// Created by david on 18/10/16.
//

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

void write_to_server(char * msg);
void run_client(void);
void chat();
