#include <internal/io.h>
#include <internal/syscall.h>
#include <internal/types.h>
#include <errno.h>

int puts(const char *str) {
    const char *temp = str;

    // Iterez prin sir pana la caracterul NULL
    while (*temp != '\0') {
        temp++;
    }

    // Calculez lungimea sirului
    size_t length = temp - str;

    // Daca numarul de bytes scris nu este egal cu lungimea sirului returneaza input/output error
    if (write(__NR_write, str, length) != (ssize_t)length) {
        return EIO;
    }

    // Daca scrierea esueaza returneaza input/output error
    if (write(__NR_write, "\n", 1) != 1) {
        return EIO;
    }

    return 0;
}
