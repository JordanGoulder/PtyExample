#include <stdio.h>
#include <linux/limits.h>
#include <sys/time.h>

#include "hexdump.h"
#include "pty.h"
#include "timed_read.h"

int main(int argc, char argv[])
{
    int fd;
    ssize_t count;
    unsigned char input[1024];
    char ptyName[PATH_MAX];

    printf("Creating pseudo-terminal...\n");

    fd = createPty(ptyName, sizeof(ptyName));

    if (fd < 0) {
        fprintf(stderr, "Error creating pseudo-terminal.");
        return -1;
    }

    printf("Listening to pseudo-terminal: %s\n\n", ptyName);

    struct timeval timeout;
    timeout.tv_sec = 0;
    timeout.tv_usec = 200000;

    while (1) {

        count = timed_read(fd, input, sizeof(input), &timeout);

        if (count < 0) {
            perror("timed_read");
            return -1;
        } else if (count > 0) {
            printf("\nReceived %d byte%s\n", count, count == 1 ? ":" : "s:");
            hexdump(input, count);
            putchar('\n');
        } else {
            putchar('.');
            fflush(stdout);
        }
    }

    return 0;
}

