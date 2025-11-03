#include <stdio.h>
#include <stdlib.h>
#include "core/core.h"
#include "scheduler/scheduler.h"
#include "memory/memory.h"
#include "fs/fs.h"
#include "device/device.h"
#include "shell/shell.h"

int main(int argc, char **argv){
    printf("KernelSim starting...\n");

    kernel_t *k = kernel_create();
    scheduler_t *s = scheduler_create(3);
    memory_t *m = memory_create(4096, 128); // 128 pages of 4KiB
    fs_t *fs = fs_create();
    device_t *d = device_create();

    k->scheduler = s;
    k->memory = m;
    k->fs = fs;
    k->device = d;

    shell_t *sh = shell_create(k, s, m, fs, d);
    shell_loop(sh);

    printf("Shutting down...\n");
    shell_destroy(sh);
    device_destroy(d);
    fs_destroy(fs);
    memory_destroy(m);
    scheduler_destroy(s);
    kernel_destroy(k);

    return 0;
}
