#include "timed_read.h"
#include <unistd.h>
#include <sys/time.h>

ssize_t timed_read(int fd, void *buff, size_t count, struct timeval *timeout)
{
    fd_set rfds;
    int error;
    struct timeval to;

    to = *timeout;

    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);

    error = select(fd + 1, &rfds, NULL, NULL, &to);

    if (error > 0) {
        error = read(fd, buff, count);
    }

    return error;
}
