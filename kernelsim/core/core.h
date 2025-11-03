#ifndef CORE_H
#define CORE_H

#include <stdint.h>

#define MAX_NAME 32

typedef enum { PROC_NEW, PROC_READY, PROC_RUNNING, PROC_WAITING, PROC_TERMINATED } proc_state_t;

typedef struct process {
    uint32_t pid;
    char name[MAX_NAME];
    proc_state_t state;
    int priority;
    uint64_t cpu_time;
    struct process *next;
} process_t;

typedef struct kernel {
    uint32_t next_pid;
    void *scheduler;
    void *memory;
    void *fs;
    void *device;
} kernel_t;

kernel_t *kernel_create(void);
void kernel_destroy(kernel_t *k);

#endif
