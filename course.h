#ifndef PARALLELISM_COURSE_H
#define PARALLELISM_COURSE_H

#define MAX_COURSE_NAME 256

struct course {
    int id;
    char *name;
    double interestQuotient;
    int course_max_slots;
    int numValidLabs;
    int *validLabs;
    int prefer;
    pthread_mutex_t courseLock;
    pthread_cond_t tutCond;
    pthread_cond_t openCond;
    int tutSlots;
    pthread_mutex_t tutLock;
    int withdrawn;
};

typedef struct course Course;

extern Course *all_courses;

void course_init(int n);
void *course_process(void *input);

#endif //PARALLELISM_COURSE_H
