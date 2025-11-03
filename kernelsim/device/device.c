#include "device.h"
#include <stdlib.h>
#include <stdio.h>

device_t *device_create(void){
    device_t *d = calloc(1, sizeof(device_t));
    return d;
}

void device_destroy(device_t *d){
    free(d);
}

void device_disk_write(device_t *d){
    d->disk_ops++;
    printf("[device] simulated disk write (ops=%llu)\n", (unsigned long long)d->disk_ops);
}

void device_net_send(device_t *d){
    d->net_packets++;
    printf("[device] simulated net send (pkts=%llu)\n", (unsigned long long)d->net_packets);
}
