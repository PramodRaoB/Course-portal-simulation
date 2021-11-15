#ifndef PARALLELISM_COURSE_H
#define PARALLELISM_COURSE_H

#define MAX_COURSE_NAME 256

struct course {
    int id;
    char *name;
    double interestQuotient;
    int course_max_slots;
    int *validLabs;
};

typedef struct course Course;

extern Course *all_courses;

void course_init(int n);

#endif //PARALLELISM_COURSE_H
