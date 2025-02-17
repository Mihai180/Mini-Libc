// SPDX-License-Identifier: BSD-3-Clause

#include <fcntl.h>
#include <internal/syscall.h>
#include <stdarg.h>
#include <errno.h>

int open(const char *filename, int flags, ...)
{
	/* TODO: Implement open system call. */
	va_list args;
    mode_t mode = 0;

    // Daca flag-ul O_CREAT este setat, folosesc
    // va_list pentru permisiunile noului fisier
    if (flags & O_CREAT) {
        va_start(args, flags);
        mode = va_arg(args, mode_t);
        va_end(args);
    }

    int ret = syscall(__NR_open, filename, flags, mode);

    // Daca syscall returneaza o valoare negativa setez
    // errno la valoarea pozitiva a ei
    if (ret < 0) {
        errno = -ret;
        return -1;
    }

    return ret;
}
