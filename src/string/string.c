// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	/* TODO: Implement strcpy(). */
	char *dest = destination;
    // Iterez prin toate caracterele din source
    while (*source != '\0') {
        *dest = *source;  // Copiez caracterul curent
        dest++;
        source++;
        }
        *dest = '\0';  // Adaug caracterul NULL la finalul sirului
    return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncpy(). */
	char *dest = destination;
    while (len > 0 && *source != '\0') {
        *dest = *source;  // Copiez caracterul curent
        dest++;
        source++;
        len--;  // Scad lungimea la fiecare pas
    }

    // Daca mai raman caractere in destination le completez cu caracterul NULL
    while (len > 0) {
        *dest = '\0';
        dest++;
        len--;
    }
    return destination;
}

char *strcat(char *destination, const char *source)
{
	/* TODO: Implement strcat(). */
	char *dest = destination;
    dest = dest + strlen(destination);
    // Copiez caracterele din source in destination
    while (*source != '\0') {
        *dest = *source;
        dest++;
        source++;
    }

    *dest = '\0';  // Adaug caracterul NULL la finalul sirului
    return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	/* TODO: Implement strncat(). */
	char *dest = destination;
    dest = dest + strlen(destination);
    while (len > 0 && *source != '\0') {
        *dest = *source;  // Copiez caracterul curent
        dest++;
        source++;
        len--;
    }

    *dest = '\0';  // Adaug caracterul NULL la finalul sirului
    return destination;
}

int strcmp(const char *str1, const char *str2)
{
	/* TODO: Implement strcmp(). */
    // Compar caracterele cat timp sunt nenule si egale
	while (*str1 != '\0' && *str1 == *str2) {
        str1++;
        str2++;
    }
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	/* TODO: Implement strncmp(). */
    // Compar caracterle cat sunt egale si ambele siruri sunt nenule
	while (len > 0 && *str1 != '\0' && (*str1 == *str2)) {
        str1++;
        str2++;
        len--;
    }
    if (len == 0)  // Sirurile sunt egale pana la len
        return 0;
    return *(unsigned char *)str1 - *(unsigned char *)str2;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	/* TODO: Implement strchr(). */
	while (*str != '\0') {
        // Daca caracterul curent este egal cu c returnez un pointer la pozitia lui
        if (*str == (char)c)
            return (char *)str;
        str++;
    }
    if (c == '\0') {
        return (char *)str;
    } else {
        return NULL;
    }
}

char *strrchr(const char *str, int c)
{
	/* TODO: Implement strrchr(). */
	const char *last = NULL;
    while (*str != 0) {
        if (*str == (char)c)
            last = str;  // Daca gasesc c last pointeaza catre pozitia lui
        str++;
    }

    if ((char)c == '\0') {
        return (char *)str;
    }

    return (char *)last;
}

char *strstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strstr(). */
	if (*needle == '\0') {
        return (char *)haystack;
    }
    // Pointeri pentru a itera prin haystack si needle
    const char *h, *n;
    while (*haystack != '\0') {
        h = haystack;
        n = needle;
        // Compar caracterele din haystack si needle cat timp sunt la fel
        while (*h != '\0' && *n != '\0' && (*h == *n)) {
            h++;
            n++;
        }
        // Daca am ajuns la finalul lui needle s-a gasit sirul
        if (*n == '\0')
            return (char *)haystack;
        haystack++;
    }
    return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	/* TODO: Implement strrstr(). */
    // Daca needle este gol, returnez un pointer la finalul lui haystack
	if (*needle == '\0') {
        return (char *)haystack + strlen(haystack);
    }

    const char *result = NULL;
    const char *h;
    // Iterez prin toate aparitiile lui needle in haystack
    while ((h = strstr(haystack, needle)) != NULL) {
        result = h;
        haystack = h + 1;
    }

    return (char *)result;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memcpy(). */
	unsigned char *dest = (unsigned char *)destination;
    const unsigned char *src = (const unsigned char *)source;

    // Iterez prin fiecare byte si copiez din source in destination
    while (num > 0) {
        *dest = *src;
        dest++;
        src++;
        num--;
    }

    return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
	unsigned char *dest = (unsigned char *)destination;
    const unsigned char *src = (const unsigned char *)source;

    // Daca destination este inaintea lui source in memorie copiez
    if (dest < src) {
        while (num > 0) {
            *dest = *src;
            dest++;
            src++;
            num--;
        }
    } else {  // Daca destination este inaintea lui source in memorie copiez invers
        dest = dest + num;
        src = src +
        num;
        while (num > 0) {
            dest--;
            src--;
            *dest = *src;
            num--;
        }
    }

    return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */
	const unsigned char *l = (const unsigned char *)ptr1;
    const unsigned char *r = (const unsigned char *)ptr2;

    // Iterez prin fiecare byte din memorie
    while (num > 0) {
        if (*l != *r)
            return *l - *r; // Daca bytes nu sunt egali returnez diferenta
        l++;
        r++;
        num--;
    }

    // Daca nu exista diferente returnez 0
    return 0;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
	unsigned char *s = (unsigned char *)source;

    // Iterez prin memorie si setez fiecare byte la valoarea potrivita
    while (num > 0) {
        *s = (unsigned char)value;
        s++;
        num--;
    }
    return source;
}
