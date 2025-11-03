#ifndef FS_H
#define FS_H

#include <stdint.h>

typedef struct file {
    char *name;
    char *data;
    size_t size;
    struct file *next;
} file_t;

typedef struct fs {
    file_t *root;
} fs_t;

fs_t *fs_create(void);
void fs_destroy(fs_t *fs);

file_t *fs_create_file(fs_t *fs, const char *name);
file_t *fs_find(fs_t *fs, const char *name);
void fs_write(fs_t *fs, const char *name, const char *data);
const char *fs_read(fs_t *fs, const char *name);
void fs_list(fs_t *fs);

#endif
