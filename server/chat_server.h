//
// Created by david on 18/10/16.
//

#ifndef CONSOLECHAT_CHATSERVER_H
#define CONSOLECHAT_CHATSERVER_H

#endif //CONSOLECHAT_CHATSERVER_H

void new_connection();

void create_client (int fd, struct in_addr ipaddr);

void process_client(Client * c);

void shutdown_server();
