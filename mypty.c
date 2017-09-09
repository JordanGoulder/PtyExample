#define _XOPEN_SOURCE 600
#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#define __USE_BSD
#include <termios.h>

int main(int argc, char argv[])
{
    int fdMaster;
    int fdSlave;
    int error;
    ssize_t count;
    char input[150];

    printf("Before creating pseudo-terminal...\n");
    system("ls -l /dev/pts");
    putchar('\n');

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

    printf("After creating pseudo-terminal...\n");
    system("ls -l /dev/pts");
    putchar('\n');

    printf("The slave side is named: %s\n", ptsname(fdMaster));

    while (1) {
        count = read(fdMaster, input, sizeof(input) - 1);
        if (count > 0) {
            input[count] = '\0';
            printf("Received %d bytes\n", count);
            printf("'%s'\n", input);
            for (int i = 0; i < count; i++) {
                printf("%02X ", input[i]);
            }
            putchar('\n');
        } else {
            printf("Read 0 bytes. Exiting.\n");
            break;
        }
    }

    return 0;
}
