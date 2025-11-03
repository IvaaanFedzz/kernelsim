#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

shell_t *shell_create(kernel_t *k, scheduler_t *s, memory_t *m, fs_t *fsys, device_t *d){
    shell_t *sh = calloc(1, sizeof(shell_t));
    sh->kernel = k;
    sh->sched = s;
    sh->mem = m;
    sh->fs = fsys;
    sh->dev = d;
    sh->running = 1;
    return sh;
}

void shell_destroy(shell_t *sh){
    free(sh);
}

static void cmd_help(){
    printf("Commands:\n");
    printf(" run <name> [vpages] - crear proceso simulado y asignar vpages\n");
    printf(" ps - listar procesos\n");
    printf(" kill <pid> - matar proceso\n");
    printf(" tick [n] - avanzar n ticks del scheduler\n");
    printf(" memmap <pid> - mostrar paginas asignadas\n");
    printf(" ls - listar archivos en fs\n");
    printf(" write <file> <text> - escribir en archivo simulado\n");
    printf(" read <file> - leer archivo\n");
    printf(" disk - hacer write simulado en disco\n");
    printf(" net - enviar paquete simulado\n");
    printf(" exit - salir\n");
}

void shell_loop(shell_t *sh){
    char line[256];
    while(sh->running){
        printf("kernelsim> ");
        if(!fgets(line, sizeof(line), stdin)) break;
        char *nl = strchr(line, '\n'); if(nl) *nl = 0;
        if(strlen(line)==0) continue;
        char *tok = strtok(line, " ");
        if(!tok) continue;
        if(strcmp(tok, "help")==0){
            cmd_help();
        } else if(strcmp(tok, "run")==0){
            char *name = strtok(NULL, " ");
            char *vpages_s = strtok(NULL, " ");
            if(!name) name = "proc";
            process_t *p = scheduler_fork_process(sh->sched, sh->kernel, name);
            printf("Created PID %u name=%s\n", p->pid, p->name);
            int vpages = vpages_s ? atoi(vpages_s) : 0;
            if(vpages>0){
                int got = memory_allocate(sh->mem, p->pid, (uint32_t)vpages);
                printf("Allocated %d pages to PID %u\n", got, p->pid);
            }
        } else if(strcmp(tok, "ps")==0){
            scheduler_list(sh->sched);
        } else if(strcmp(tok, "kill")==0){
            char *pid_s = strtok(NULL, " ");
            if(pid_s){
                uint32_t pid = (uint32_t)atoi(pid_s);
                scheduler_kill(sh->sched, pid);
                memory_free_pid(sh->mem, pid);
                printf("Killed %u\n", pid);
            }
        } else if(strcmp(tok, "tick")==0){
            char *n_s = strtok(NULL, " ");
            int n = n_s ? atoi(n_s) : 1;
            for(int i=0;i<n;i++){
                scheduler_tick(sh->sched);
            }
            printf("Advanced %d ticks\n", n);
        } else if(strcmp(tok, "memmap")==0){
            char *pid_s = strtok(NULL, " ");
            if(pid_s){
                uint32_t pid = (uint32_t)atoi(pid_s);
                memory_memmap(sh->mem, pid);
            }
        } else if(strcmp(tok, "ls")==0){
            fs_list(sh->fs);
        } else if(strcmp(tok, "write")==0){
            char *fname = strtok(NULL, " ");
            char *text = strtok(NULL, ""); // rest of line
            if(fname && text){
                fs_write(sh->fs, fname, text);
                printf("Wrote %zu bytes to %s\n", strlen(text), fname);
            } else {
                printf("Usage: write <file> <text>\n");
            }
        } else if(strcmp(tok, "read")==0){
            char *fname = strtok(NULL, " ");
            if(fname){
                const char *d = fs_read(sh->fs, fname);
                if(d) printf("%s\n", d); else printf("(no such file)\n");
            }
        } else if(strcmp(tok, "disk")==0){
            device_disk_write(sh->dev);
        } else if(strcmp(tok, "net")==0){
            device_net_send(sh->dev);
        } else if(strcmp(tok, "exit")==0){
            sh->running = 0;
        } else {
            printf("Unknown command: %s (type 'help')\n", tok);
        }
    }
}
