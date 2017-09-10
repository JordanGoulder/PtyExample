#include "hexdump.h"

#include <stdio.h>
#include <ctype.h>

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
                printf(" %02x", buff[offset + i + 8]);
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

