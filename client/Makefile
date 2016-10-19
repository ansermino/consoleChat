PORT= 59248
CFLAGS= -DPORT=\$(PORT) -g -Wall -std=c99 #-Werror

chat_client: chat_client.o client_tools.o
		gcc $(CFLAGS) -o chat_client chat_client.o client_tools.o

chat_client.o: chat_client.c chat_client.h
		gcc $(CFLAGS) -c chat_client.c

client_tools.o: client_tools.c client_tools.h
		gcc $(CFLAGS) -c client_tools.c

clean:
		rm *.o
		rm chat_client
