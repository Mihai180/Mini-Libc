#ifndef TIME_H
#define TIME_H

#include <errno.h>
#include <internal/types.h>
#include <internal/essentials.h>


#ifdef __cplusplus
extern "C" {
#endif

struct timespec {
    long tv_sec;  // seconds
    long tv_nsec; // nanoseconds
};

int nanosleep(const struct timespec *req, struct timespec *rem);

#ifdef __cplusplus
}
#endif

#endif // TIME_H
