#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

typedef struct page {
    uint32_t pid;
    uint32_t vpage;
    int used;
    struct page *next;
} page_t;

typedef struct memory {
    uint32_t page_size;
    uint32_t total_pages;
    page_t *pages;
} memory_t;

memory_t *memory_create(uint32_t page_size, uint32_t total_pages);
void memory_destroy(memory_t *m);

int memory_allocate(memory_t *m, uint32_t pid, uint32_t vpages);
void memory_free_pid(memory_t *m, uint32_t pid);
void memory_memmap(memory_t *m, uint32_t pid);

#endif
