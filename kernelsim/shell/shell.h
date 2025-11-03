#ifndef SHELL_H
#define SHELL_H

#include "../core/core.h"
#include "../scheduler/scheduler.h"
#include "../memory/memory.h"
#include "../fs/fs.h"
#include "../device/device.h"

typedef struct shell {
    kernel_t *kernel;
    scheduler_t *sched;
    memory_t *mem;
    fs_t *fs;
    device_t *dev;
    int running;
} shell_t;

shell_t *shell_create(kernel_t *k, scheduler_t *s, memory_t *m, fs_t *fsys, device_t *d);
void shell_destroy(shell_t *sh);
void shell_loop(shell_t *sh);

#endif
