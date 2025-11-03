#include "scheduler.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

scheduler_t *scheduler_create(unsigned int quantum){
    scheduler_t *s = calloc(1, sizeof(scheduler_t));
    if(!s) return NULL;
    s->quantum = quantum ? quantum : 3;
    return s;
}

void scheduler_destroy(scheduler_t *s){
    process_t *p = s->ready_head;
    while(p){
        process_t *next = p->next;
        free(p);
        p = next;
    }
    free(s);
}

process_t *scheduler_fork_process(scheduler_t *s, kernel_t *k, const char *name){
    process_t *p = calloc(1, sizeof(process_t));
    if(!p) return NULL;
    p->pid = k->next_pid++;
    strncpy(p->name, name, sizeof(p->name)-1);
    p->state = PROC_READY;
    p->next = NULL;
    scheduler_enqueue(s, p);
    return p;
}

void scheduler_enqueue(scheduler_t *s, process_t *p){
    p->next = NULL;
    if(!s->ready_head){
        s->ready_head = s->ready_tail = p;
    } else {
        s->ready_tail->next = p;
        s->ready_tail = p;
    }
}

process_t *scheduler_dequeue(scheduler_t *s){
    process_t *p = s->ready_head;
    if(!p) return NULL;
    s->ready_head = p->next;
    if(!s->ready_head) s->ready_tail = NULL;
    p->next = NULL;
    return p;
}

process_t *scheduler_next(scheduler_t *s){
    // Round-robin: pop head => current
    if(s->current && s->current->state == PROC_RUNNING){
        // move running to ready if still alive
        s->current->state = PROC_READY;
        scheduler_enqueue(s, s->current);
    }
    process_t *p = scheduler_dequeue(s);
    if(p){
        p->state = PROC_RUNNING;
        s->current = p;
    } else {
        s->current = NULL;
    }
    s->tick_count = 0;
    return s->current;
}

void scheduler_tick(scheduler_t *s){
    if(!s->current){
        scheduler_next(s);
        return;
    }
    s->tick_count++;
    s->current->cpu_time++;
    if(s->tick_count >= s->quantum){
        // time slice over
        scheduler_next(s);
    }
}

void scheduler_kill(scheduler_t *s, uint32_t pid){
    // remove from ready queue or current
    if(s->current && s->current->pid == pid){
        s->current->state = PROC_TERMINATED;
        free(s->current);
        s->current = NULL;
        return;
    }
    process_t *prev = NULL;
    process_t *p = s->ready_head;
    while(p){
        if(p->pid == pid){
            if(prev) prev->next = p->next;
            else s->ready_head = p->next;
            if(p == s->ready_tail) s->ready_tail = prev;
            p->state = PROC_TERMINATED;
            free(p);
            return;
        }
        prev = p;
        p = p->next;
    }
}

process_t *scheduler_find(scheduler_t *s, uint32_t pid){
    if(s->current && s->current->pid == pid) return s->current;
    process_t *p = s->ready_head;
    while(p){
        if(p->pid == pid) return p;
        p = p->next;
    }
    return NULL;
}

void scheduler_list(scheduler_t *s){
    printf("PID\tSTATE\t\tNAME\n");
    if(s->current){
        printf("%u\tRUNNING\t%s\n", s->current->pid, s->current->name);
    }
    process_t *p = s->ready_head;
    while(p){
        const char *st = (p->state==PROC_READY)?"READY":"OTHER";
        printf("%u\t%s\t\t%s\n", p->pid, st, p->name);
        p = p->next;
    }
}
