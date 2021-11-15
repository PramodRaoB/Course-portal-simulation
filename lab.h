#ifndef PARALLELISM_LAB_H
#define PARALLELISM_LAB_H

#define MAX_LAB_NAME 256

struct lab {
    int id;
    char *name;
    int numTA;
    int TALimit;
};

typedef struct lab Lab;

extern Lab *all_labs;

void lab_init(int n);

#endif //PARALLELISM_LAB_H
