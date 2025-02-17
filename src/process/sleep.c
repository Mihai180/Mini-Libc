#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <internal/syscall.h>

int nanosleep(const struct timespec *req, struct timespec *rem) {
    // Verific daca inputul este corect
    if (req == NULL || req->tv_nsec < 0 || req->tv_nsec >= 1000000000) {
        errno = EINVAL;  // Setez errno pentru argument invalid
        return -1;
    }

    struct timespec remaining = *req; // Initializez remaining cu timpul cerut
    while (1) {
        // Iterez cat timp mai este timp si nu apare o eroare
        int ret = syscall(__NR_nanosleep, &remaining, rem);

        if (ret == 0) {
            // Sleep s-a terminat cu succes
            return 0;
        } else if (errno == EINTR) {
            // Sleep a fost intrerupt si se incearca reluarea lui
            if (rem != NULL) {
                remaining = *rem;
            }
            continue; // Se incearca reluarea lui sleep
        } else {
            return -1;
        }
    }
}

unsigned int sleep(unsigned int seconds) {
    if (seconds == 0) {
        return 0; // Daca numarul de secunde este 0 nu este nevoie de sleep
    }

    struct timespec req, rem;
    req.tv_sec = seconds;
    req.tv_nsec = 0; // Setez nanosecundele la 0

    // Folosesc nanosleep intr-o bucla in caz de intrerupere incercand din nou
    while (nanosleep(&req, &rem) == -1 && errno == EINTR) {
        req = rem;
    }

    return req.tv_sec; // Returnez numarul de secunde ramase
}
