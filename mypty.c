#include <stdio.h>
#include <unistd.h>
#include <linux/limits.h>

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

    while (1) {
        count = read(fd, input, sizeof(input) - 1);
        if (count > 0) {
            printf("Received %d byte%s\n", count, count == 1 ? ":" : "s:");
            hexdump(input, count);
            putchar('\n');
        } else {
            puts("PTY closed.");
            break;
        }
    }

    return 0;
}

