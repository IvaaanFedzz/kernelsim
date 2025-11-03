#include "core.h"
#include <stdlib.h>
#include <string.h>

kernel_t *kernel_create(void){
    kernel_t *k = calloc(1, sizeof(kernel_t));
    if(!k) return NULL;
    k->next_pid = 1;
    return k;
}

void kernel_destroy(kernel_t *k){
    free(k);
}
