#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "../core/core.h"

typedef struct scheduler {
    process_t *ready_head;
    process_t *ready_tail;
    unsigned int quantum;
    process_t *current;
    unsigned int tick_count;
} scheduler_t;

scheduler_t *scheduler_create(unsigned int quantum);
void scheduler_destroy(scheduler_t *s);

process_t *scheduler_fork_process(scheduler_t *s, kernel_t *k, const char *name);
void scheduler_enqueue(scheduler_t *s, process_t *p);
process_t *scheduler_dequeue(scheduler_t *s);
process_t *scheduler_next(scheduler_t *s);
void scheduler_tick(scheduler_t *s);

void scheduler_kill(scheduler_t *s, uint32_t pid);
void scheduler_list(scheduler_t *s);
process_t *scheduler_find(scheduler_t *s, uint32_t pid);

#endif
