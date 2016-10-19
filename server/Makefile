PORT= 59248
CFLAGS= -DPORT=\$(PORT) -g -Wall -std=c99 //-Werror

chat_server: chat_server.o server_tools.o
		gcc $(CFLAGS) -o chat_server chat_server.o server_tools.o

chat_server.o: chat_server.c chat_server.h
		gcc $(CFLAGS) -c chat_server.c

server_tools.o: server_tools.c server_tools.h
		gcc $(CFLAGS) -c server_tools.c

clean:
		rm *.o
		rm chat_server
