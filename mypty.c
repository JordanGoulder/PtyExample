#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/time.h>
#include <sys/select.h>

#include "hexdump.h"
#include "pty.h"

int main(int argc, char argv[])
{
    int fd;
    ssize_t count;
    unsigned char input[256];
    char ptyName[PATH_MAX];

    printf("Creating pseudo-terminal...\n");

    fd = createPty(ptyName, sizeof(ptyName));

    if (fd < 0) {
        fprintf(stderr, "Error creating pseudo-terminal.");
        return -1;
    }

    printf("Listening to pseudo-terminal: %s\n\n", ptyName);

    fd_set rfds;
    struct timeval tv;
    int error;

    while (1) {

        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);

        tv.tv_sec = 1;
        tv.tv_usec = 0;

        error = select(fd + 1, &rfds, NULL, NULL, &tv);

        if (error == -1) {
            perror("select()");
        } else if (error) {
            count = read(fd, input, sizeof(input) - 1);
            if (count > 0) {
                printf("\nReceived %d byte%s\n", count, count == 1 ? ":" : "s:");
                hexdump(input, count);
                putchar('\n');
            } else {
                perror("read()");
                break;
            }
        } else {
            putchar('.');
            fflush(stdout);
        }
    }

    return 0;
}

