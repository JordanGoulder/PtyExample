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

void hexdump(unsigned char buff[], int len);

int main(int argc, char argv[])
{
    int fdMaster;
    int fdSlave;
    int error;
    ssize_t count;
    unsigned char input[256];

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

    printf("The slave side is named: %s\n\n", ptsname(fdMaster));

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

void hexdump(unsigned char buff[], int len)
{
    int offset = 0;
    int total = len;

    while (len > 0) {

        printf("%08x ", offset);
        for (int i = 0; i < 8; i++)
        {
            if (i < len) {
                printf(" %02x", buff[offset + i]);
            } else {
                printf("   ");
            }
        }

        putchar(' ');

        for (int i = 0; i < 8; i++)
        {
            if ((i + 8) < len) {
                printf(" %02x", buff[offset + i]);
            } else {
                printf("   ");
            }
        }

        printf("  |");
        for (int i = 0; i < 16; i++) {
            if (i < len) {
                if (isprint(buff[offset + i])) {
                    putchar(buff[offset + i]);
                } else {
                    putchar('.');
                }
            } else {
                break;
            }
        }
        printf("|\n");

        len -= 16;
        offset += 16;
    }
    printf("%08x\n", total);
}
