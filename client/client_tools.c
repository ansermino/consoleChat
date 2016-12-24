#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "client_tools.h"


int verbose = 1; //TODO: Set to 0 default and implement set_verbose()
static int MAX_READ_BUFFER = 2048;

/**
 * Set verbose to true(!0) or false(0)
 */
void set_verbose(int value){
    verbose = value;
}

/**
 * For verbose mode. All data reported to stderr.
 */
void report(char * msg, ...){
    if(verbose){
        char report[100];
        va_list args;

        va_start(args, msg);
        vsnprintf(report, sizeof(report), msg, args);
        va_end(args);

        fprintf(stderr, "%s\n", report);
    }
}

int find_network_newline(DataBuffer  * d){
	int i = 0;
	while(i < d->in_buffer - 1){
		if((d->buffer[i] == '\r') && (d->buffer[i + 1] == '\n')){
			return i;
		}
		i++;
	}
	return -1;
}

int read_line(DataBuffer * d){
	char * insert_ptr = d->buffer + d->in_buffer;
	int buffer_space = MAX_READ_BUFFER - d->in_buffer;
	int read_size;
	if((read_size = read(d->fd, insert_ptr, buffer_space)) >= 0){
		d->in_buffer += read_size;
		if(read_size == 0){
			//TODO: Shutdown client
		}
		int newline_index = find_network_newline(d);
		if(newline_index >= 0){
			d->buffer[newline_index] = '\0';
			d->buffer[newline_index + 1] = '\0';
			char data[newline_index + 1];
			strcpy(data, d->buffer);
			printf("%s\n", data);
			newline_index += 2;
			d->in_buffer -= newline_index;
			memmove(d->buffer, d->buffer + newline_index, d->in_buffer);
		}
	}
	else{
		perror("server read");
	}
	return read_size;
}

