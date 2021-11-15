#ifndef PARALLELISM_LAB_H
#define PARALLELISM_LAB_H

#include <pthread.h>

#define MAX_LAB_NAME 256

struct lab {
    int id;
    char *name;
    int numTA;
    int TALimit;
    int *taTimes;
    int available;
    pthread_mutex_t *taLock;
};

typedef struct lab Lab;

extern Lab *all_labs;

void lab_init(int n);
void *lab_process(void *input);

#endif //PARALLELISM_LAB_H
