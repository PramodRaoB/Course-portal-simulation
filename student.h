#ifndef PARALLELISM_STUDENT_H
#define PARALLELISM_STUDENT_H

struct student {
    int id;
    int preference[3];
    long long int enterTime;
    double calibre;
};

typedef struct student Student;

extern Student *all_students;

void student_init(int n);
void *student_process(void *input);

#endif //PARALLELISM_STUDENT_H
