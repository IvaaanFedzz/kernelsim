#include "memory.h"
#include <stdlib.h>
#include <stdio.h>

memory_t *memory_create(uint32_t page_size, uint32_t total_pages){
    memory_t *m = calloc(1, sizeof(memory_t));
    if(!m) return NULL;
    m->page_size = page_size;
    m->total_pages = total_pages;
    page_t *head = NULL;
    for(uint32_t i=0;i<total_pages;i++){
        page_t *p = calloc(1, sizeof(page_t));
        p->pid = 0;
        p->vpage = i;
        p->used = 0;
        p->next = head;
        head = p;
    }
    m->pages = head;
    return m;
}

void memory_destroy(memory_t *m){
    page_t *p = m->pages;
    while(p){
        page_t *n = p->next;
        free(p);
        p = n;
    }
    free(m);
}

int memory_allocate(memory_t *m, uint32_t pid, uint32_t vpages){
    uint32_t allocated = 0;
    page_t *p = m->pages;
    while(p && allocated < vpages){
        if(!p->used){
            p->used = 1;
            p->pid = pid;
            allocated++;
        }
        p = p->next;
    }
    return allocated;
}

void memory_free_pid(memory_t *m, uint32_t pid){
    page_t *p = m->pages;
    while(p){
        if(p->used && p->pid == pid){
            p->used = 0;
            p->pid = 0;
        }
        p = p->next;
    }
}

void memory_memmap(memory_t *m, uint32_t pid){
    printf("Memory map for PID %u:\n", pid);
    page_t *p = m->pages;
    int idx = 0;
    while(p){
        if(p->used && p->pid == pid){
            printf(" page %d -> pid %u vpage %u\n", idx, p->pid, p->vpage);
        }
        p = p->next;
        idx++;
    }
}
