// SPDX-License-Identifier: BSD-3-Clause

#include <unistd.h>
#include <internal/syscall.h>
#include <errno.h>

int truncate(const char *path, off_t length)
{
	/* TODO: Implement truncate(). */
	int ret = syscall(__NR_truncate, path, length);

    // Daca syscall returneaza o valoare negativa setez
    // errno la valoarea pozitiva a ei
    if (ret < 0) {
        errno = -ret;
        return -1;
    }

    return 0;
}
