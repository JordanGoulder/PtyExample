#define _XOPEN_SOURCE 600
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char argv[])
{
    int fdMaster;
    int error;

    printf("Before creating pseudo-terminal...\n");
    system("ls -l /dev/pts");

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

    printf("The slave side is named: %s\n", ptsname(fdMaster));
}
