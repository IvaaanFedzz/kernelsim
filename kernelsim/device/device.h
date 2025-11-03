#ifndef DEVICE_H
#define DEVICE_H

#include <stdint.h>

typedef struct device {
    uint64_t disk_ops;
    uint64_t net_packets;
} device_t;

device_t *device_create(void);
void device_destroy(device_t *d);

void device_disk_write(device_t *d);
void device_net_send(device_t *d);

#endif
