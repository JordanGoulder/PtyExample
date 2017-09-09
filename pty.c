#define _XOPEN_SOURCE 600
#define _DEFAULT_SOURCE
#define _GNU_SOURCE
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>

#include "pty.h"

int createPty(char *name, int len)
{
    int error;
    int fd;

    fd = posix_openpt(O_RDWR);

    if (fd < 0) {
        fprintf(stderr, "Error %d on posix_openpt()\n", errno);
        return -1;
    }

    error = grantpt(fd);
    if (error != 0) {
        fprintf(stderr, "Error %d on grantpt()\n", errno);
        return -1;
    }

    error = unlockpt(fd);
    if (error != 0) {
        fprintf(stderr, "Error %d on unlockpt()\n", errno);
        return -1;
    }

    ptsname_r(fd, name, len);

    return fd;
}

