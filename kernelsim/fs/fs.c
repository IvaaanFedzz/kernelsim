#include "fs.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

fs_t *fs_create(void){
    fs_t *fs = calloc(1, sizeof(fs_t));
    return fs;
}

void fs_destroy(fs_t *fs){
    file_t *f = fs->root;
    while(f){
        file_t *n = f->next;
        free(f->name);
        free(f->data);
        free(f);
        f = n;
    }
    free(fs);
}

file_t *fs_create_file(fs_t *fs, const char *name){
    if(fs_find(fs, name)) return NULL;
    file_t *f = calloc(1, sizeof(file_t));
    f->name = strdup(name);
    f->data = NULL;
    f->size = 0;
    f->next = fs->root;
    fs->root = f;
    return f;
}

file_t *fs_find(fs_t *fs, const char *name){
    file_t *f = fs->root;
    while(f){
        if(strcmp(f->name, name)==0) return f;
        f = f->next;
    }
    return NULL;
}

void fs_write(fs_t *fs, const char *name, const char *data){
    file_t *f = fs_find(fs, name);
    if(!f) f = fs_create_file(fs, name);
    free(f->data);
    f->size = strlen(data);
    f->data = strdup(data);
}

const char *fs_read(fs_t *fs, const char *name){
    file_t *f = fs_find(fs, name);
    if(!f) return NULL;
    return f->data;
}

void fs_list(fs_t *fs){
    printf("Files:\n");
    file_t *f = fs->root;
    while(f){
        printf(" - %s (size=%zu)\n", f->name, f->size);
        f = f->next;
    }
}
