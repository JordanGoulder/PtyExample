#ifndef TIMED_READ_H
#define TIMED_READ_H

#include <unistd.h>
#include <sys/time.h>

ssize_t timed_read(int fd, void *buff, size_t count, struct timeval *timeout);

#endif//TIMED_READ_H
