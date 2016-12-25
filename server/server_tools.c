#include "server_tools.h"

#define RESET "\x1B[0m"
#define BLUE "\x1B[0m34"

static int MAX_BACKLOG_QUEUE = 5;

int verbose = 1; //TODO: Set to 0 default and implement set_verbose()

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

int setup(void){
    int listenfd;
    int on = 1, status;
    struct sockaddr_in self;
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }
    status = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const char *) &on, sizeof(on));
    if(status == -1) {
        perror("setsockopt -- REUSEADDR");
    }

    self.sin_family = AF_INET;
    self.sin_addr.s_addr = INADDR_ANY;
    self.sin_port = htons(PORT);
    memset(&self.sin_zero,0, sizeof(self.sin_zero));

    fprintf(stderr, "Listening on port %d\n", PORT);

    if(bind(listenfd, (struct sockaddr *)&self, sizeof(self)) == -1){
        perror("bind");
        exit(1);
    }
    if(listen(listenfd, MAX_BACKLOG_QUEUE) == -1){
        perror("listen");
        exit(1);
    }
    return listenfd;
}

int find_network_newline(char * str, int in_buffer){
	int i = 0;
	while(i < in_buffer	- 1){
		if((str[i] == '\r') && (str[i+1] == '\n')){
			return i;
		}
		i++;
	}
	return -1;	
}

void diagnostic_buffer_print(char * buf){
	for(int i = 0; i < 50; i++){
		if(buf[i] == '\n'){
			fprintf(stderr, "\\n");
		}
		else if(buf[i] == '\r'){
			fprintf(stderr, "\\r");
		}
		else if(buf[i] == '\0'){
			fprintf(stderr, "\\0");
		}
		else{
			fprintf(stderr, "%c", buf[i]);
		}
	}
	fprintf(stderr, "\n");
}

char * get_colour(){
	char * colour = malloc(strlen(BLUE) + 1);
	report("length of blue %d", strlen(BLUE));
	strcpy(colour, BLUE);
	return colour;
}

/**
 * Read characters from 'fd' until a newline is encountered. If a newline
 * character is not encountered in the first (n - 1) bytes, then the excess
 * characters are discarded. The returned string placed in 'buf' is
 * null-terminated and includes the newline character if it was read in the
 * first (n - 1) bytes. The function return value is the number of bytes
 * placed in buffer (which includes the newline character if encountered,
 * but excludes the terminating null byte).
 *
 * See attribute in header file.
 */
ssize_t readLine(int fd, void *buffer, size_t n) {
    ssize_t numRead;                    /* # of bytes fetched by last read() */
    size_t totRead;                     /* Total bytes read so far */
    char *buf;
    char ch;

    if (n <= 0 || buffer == NULL) {
        errno = EINVAL;
        return -1;
    }

    buf = buffer;                       /* No pointer arithmetic on "void *" */

    totRead = 0;
    for (;;) {
        numRead = read(fd, &ch, 1);

        if (numRead == -1) {
            if (errno == EINTR)         /* Interrupted --> restart read() */
                continue;
            else
                return -1;              /* Some other error */

        } else if (numRead == 0) {      /* EOF */
            if (totRead == 0)           /* No bytes read; return 0 */
                return 0;
            else                        /* Some bytes read; add '\0' */
                break;

        } else {                        /* 'numRead' must be 1 if we get here */
            if (totRead < n - 1) {      /* Discard > (n - 1) bytes */
                totRead++;
                *buf++ = ch;
            }

            if (ch == '\n')
                break;
        }
    }
    buf--;
    //buf--;
    *buf = '\0';
    report("Read successful.");

    return totRead - 2;
}
