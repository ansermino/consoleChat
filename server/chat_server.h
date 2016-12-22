//
// Created by david on 18/10/16.
//

#ifndef CONSOLECHAT_CHATSERVER_H
#define CONSOLECHAT_CHATSERVER_H

#endif //CONSOLECHAT_CHATSERVER_H

void new_connection();

void create_client (int fd, struct in_addr ipaddr);

void process_client(Client * c);

void client_exit(Client * c);

void client_receive_msg(Client * c, char * buffer);

void broadcast(char * msg);

void broadcast_except(Client * c, char * msg);

void remove_client(Client * c);

void shutdown_server();
