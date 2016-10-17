//
// Created by david on 10/17/16.
//

#ifndef CONSOLECHAT_SERVERTOOLS_H
#define CONSOLECHAT_SERVERTOOLS_H

#endif //CONSOLECHAT_SERVERTOOLS_H


#ifndef PORT
    #define PORT 59247
#endif

#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

static int MAX_BACKLOG_QUEUE = 5;

int setup();
