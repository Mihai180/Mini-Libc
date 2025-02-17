// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
	/* TODO: Implement malloc(). */
    // Daca size este 0 nu se aloca memorie
	if (size == 0) {
        return NULL;
    }

    // OS-ul alege adresa de memorie, aceasta poate fi citita si scrisa
    // fara file descriptor sau offset pentru MAP_ANONYMOUS
    void *ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

    if (ptr == MAP_FAILED) {
        return NULL;
    }

    // Daca nu se reuseste adaugarea la memory tracking list se elibereaza memoria
    if (mem_list_add(ptr, size) != 0) {
        munmap(ptr, size);
        return NULL;
    }

    return ptr;
}

void *calloc(size_t nmemb, size_t size)
{
	/* TODO: Implement calloc(). */
    // Calculez marimea memoriei necesare
	size_t total_size = nmemb * size;

    // Verific inputul sa fie valid si sa nu se faca overflow
    if (nmemb == 0 || size == 0 || total_size / nmemb != size) {
        return NULL;
    }

    void *ptr = malloc(total_size);

    // Daca s-a reusit alocarea memoriei se initializeaza cu 0
    if (ptr != NULL) {
        memset(ptr, 0, total_size);
    }

    return ptr;
}

void free(void *ptr)
{
	/* TODO: Implement free(). */
	if (ptr == NULL) {
        return;
    }

    // Gasesc nodul din lista pentru memorie asociat acestui pointer
    struct mem_list *node = mem_list_find(ptr);
    if (node == NULL) {
        return;
    }

    // Eliberez memoria
    munmap(ptr, node->len);
    mem_list_del(ptr);
}

void *realloc(void *ptr, size_t size)
{
	/* TODO: Implement realloc(). */
    // Daca pointerul este NULL se aloca o noua zona de memorie
	if (ptr == NULL) {
        return malloc(size);
    }

    // Daca marimea este 0 eliberez memoria alocata si returnez NULL
    if (size == 0) {
        free(ptr);
        return NULL;
    }

    // Gasesc nodul din lista pentru memorie asociat acestui pointer
    struct mem_list *node = mem_list_find(ptr);
    if (node == NULL) {
        return NULL; // Pointer not found
    }

    // Aloc o noua zona de memorie
    void *new_ptr = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new_ptr == MAP_FAILED) {
        return NULL;
    }

    // Aflu marimea memoriei pe care trebuie sa o copiez
    size_t copy_size;
    if (size < node->len) {
        copy_size = size;
    } else {
        copy_size = node->len;
    }
    memcpy(new_ptr, ptr, copy_size);
    free(ptr);

    // Adaug noua zona de memorie in lista pentru memorie
    if (mem_list_add(new_ptr, size) != 0) {
        munmap(new_ptr, size);
        return NULL;
    }

    return new_ptr;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	/* TODO: Implement reallocarray(). */
    // Calculez totalul de memorie de care este nevoie
	size_t total_size = nmemb * size;

    // Verific inputul si sa nu aiba loc overflow
    if (nmemb == 0 || size == 0 || total_size / nmemb != size) {
        return NULL;
    }

    return realloc(ptr, total_size);
}
