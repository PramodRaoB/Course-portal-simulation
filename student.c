#include <malloc.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "student.h"
#include "course.h"
#include "wrapper.h"
#include "globals.h"

Student *all_students;

void student_init(int n) {
    all_students = (Student *) malloc(n * sizeof(Student));
    assert(all_students);
    for (int i = 0; i < n; i++) {
        all_students[i].id = i;
    }
}

void *student_process(void *input) {
    Student *student = (Student *) input;
    sleep(student->enterTime);
    printf(C_STUDENT "Student %d has filled in preferences for course registration\n" RESET, student->id);
    int found = 0;
    for (int i = 0; i < 3 && !found; i++) {
        Course *course = &all_courses[student->preference[i]];
        if (course->withdrawn) {
            if (i < 2)
                printf(C_STUDENT "Student %d changed current preference from course %s (priority %d) to course %s (priority %d)\n" RESET, student->id, course->name, i + 1, all_courses[student->preference[i + 1]].name, i + 2);
            else
                printf(C_STUDENT "Student %d couldn't get any of his preferred courses\n" RESET, student->id);
            continue;
        }
        Pthread_mutex_lock(&course->courseLock);
        course->prefer++;
        if (course->prefer == 1)
            Pthread_cond_signal(&course->emptyCond);
        Pthread_cond_wait(&course->openCond, &course->courseLock);
        course->prefer--;
        //might have gotten because of broadcast
        if (course->withdrawn) {
            Pthread_mutex_unlock(&course->courseLock);
            if (i < 2)
                printf(C_STUDENT "Student %d changed current preference from course %s (priority %d) to course %s (priority %d)\n" RESET, student->id, course->name, i + 1, all_courses[student->preference[i + 1]].name, i + 2);
            else
                printf(C_STUDENT "Student %d couldn't get any of his preferred courses\n" RESET, student->id);
            continue;
        }
        printf(C_STUDENT "Student %d has been allocated a seat in course %s\n" RESET, student->id, course->name);
        Pthread_mutex_unlock(&course->courseLock);

        Pthread_mutex_lock(&course->tutLock);
        course->tutSlots++;
        Pthread_cond_signal(&course->fullCond);
        Pthread_cond_wait(&course->tutCond, &course->tutLock);
        Pthread_mutex_unlock(&course->tutLock);

        double prob = course->interestQuotient * student->calibre;
        double randomSample = (double) rand() / RAND_MAX;
        if (randomSample <= prob) {
            printf(C_STUDENT "Student %d has selected course %s permanently\n" RESET, student->id, course->name);
            found = 1;
        }
        else {
            if (i < 2)
                printf(C_STUDENT "Student %d changed current preference from course %s (priority %d) to course %s (priority %d)\n" RESET, student->id, course->name, i + 1, all_courses[student->preference[i + 1]].name, i + 2);
            else
                printf(C_STUDENT "Student %d couldn't get any of his preferred courses\n" RESET, student->id);
        }
    }

    return NULL;
}