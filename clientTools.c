#include <stdio.h>
#include <errno.h>
#include <unistd.h>


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

        fprintf(stderr, "%s", report);
    }
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
 *
 * Adapted from sample code from "Linux Programming Interface" by Michael Kerrisk.
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
    buf--;
    *buf = '\0';
    report("Read successful.\n");

    return totRead - 2;
}