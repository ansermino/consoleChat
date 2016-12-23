#ifndef CONSOLECHAT_CHATSERVER_H
#define CONSOLECHAT_CHATSERVER_H

#endif //CONSOLECHAT_CHATSERVER_H

#include <string.h>

void new_connection();

void create_client (int fd, struct in_addr ipaddr);

void process_incoming_data(Client * c);

void process_cmd(Client * c, char * cmd);

void client_exit(Client * c);

void client_receive_msg(Client * c, char * buffer);

void broadcast(char * msg, ...);

void broadcast_except(Client * c, char * msg, ...);

void write_to_client(Client * c, char * text);

void remove_client(Client * c);

void shutdown_server();
