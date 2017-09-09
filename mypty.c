#define _XOPEN_SOURCE 600
#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#define __USE_BSD
#include <termios.h>

#include "hexdump.h"

int main(int argc, char argv[])
{
    int fdMaster;
    int fdSlave;
    int error;
    ssize_t count;
    unsigned char input[256];

    printf("Creating pseudo-terminal...\n");

    fdMaster = posix_openpt(O_RDWR);

    if (fdMaster < 0) {
        fprintf(stderr, "Error %d on posix_openpt()\n", errno);
        return 1;
    }

    error = grantpt(fdMaster);
    if (error != 0) {
        fprintf(stderr, "Error %d on grantpt()\n", errno);
        return 1;
    }

    error = unlockpt(fdMaster);
    if (error != 0) {
        fprintf(stderr, "Error %d on unlockpt()\n", errno);
        return 1;
    }

    printf("Listening to pseudo-terminal: %s\n\n", ptsname(fdMaster));

    while (1) {
        count = read(fdMaster, input, sizeof(input) - 1);
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

