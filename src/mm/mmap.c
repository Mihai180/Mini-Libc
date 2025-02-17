// SPDX-License-Identifier: BSD-3-Clause

#include <sys/mman.h>
#include <errno.h>
#include <internal/syscall.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>

void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
{
	/* TODO: Implement mmap(). */
    // Verific flagurile sa fie setate corect
    if ((flags & MAP_SHARED) && (flags & MAP_PRIVATE)) {
        errno = EINVAL;
        return MAP_FAILED;
    }

    // Ma asigur ca cel putin un flag este setat
    if (!(flags & (MAP_SHARED | MAP_PRIVATE))) {
        errno = EINVAL;
        return MAP_FAILED;
    }

    // Verific daca fd este nenul cand MAP_ANONYMOUS este setat
    if (!(flags & MAP_ANONYMOUS)) {
        struct stat st;
        if (fd < 0 || fstat(fd, &st) == -1) {
            errno = EBADF;
            return MAP_FAILED;
        }
    }

    void *result = (void *)syscall(__NR_mmap, addr, length, prot, flags, fd, offset);

    if (result == MAP_FAILED) {
        return MAP_FAILED;
    }

    return result;
}

void *mremap(void *old_address, size_t old_size, size_t new_size, int flags)
{
	/* TODO: Implement mremap(). */
	void *result = (void *)syscall(__NR_mremap, old_address, old_size, new_size, flags);

    if (result == (void *)-1) {
        return MAP_FAILED;
    }

    return result;
}

int munmap(void *addr, size_t length)
{
	/* TODO: Implement munmap(). */
	int result = syscall(__NR_munmap, addr, length);

    if (result == -1) {
        return -1;
    }

    return 0;
}
