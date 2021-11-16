#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include "course.h"
#include "lab.h"
#include "wrapper.h"
#include "globals.h"
#include <stdio.h>

Course *all_courses;

void course_init(int n) {
    all_courses = (Course *) malloc(n * sizeof(Course));
    assert(all_courses);
    for (int i = 0; i < n; i++) {
        all_courses[i].id = i;
        all_courses[i].prefer = 0;
        all_courses[i].tutSlots = 0;
        all_courses[i].withdrawn = 0;
        Pthread_mutex_init(&all_courses[i].tutLock, NULL);
        Pthread_mutex_init(&all_courses[i].courseLock, NULL);
        Pthread_cond_init(&all_courses[i].tutCond, NULL);
        Pthread_cond_init(&all_courses[i].openCond, NULL);
        all_courses[i].name = (char *) malloc(MAX_COURSE_NAME);
        assert(all_courses[i].name);
    }
}

void take_tutorial(Course *course) {
    int pickSlots = (rand() % course->course_max_slots) + 1;
    printf(C_COURSE "Course %s has been allocated %d seats\n" RESET, course->name, pickSlots);
    Pthread_mutex_lock(&course->courseLock);
    int numAttendingTut = MIN(course->prefer, pickSlots);
    for (int i = 0; i < numAttendingTut; i++) {
        Pthread_cond_signal(&course->openCond);
    }
    Pthread_mutex_unlock(&course->courseLock);

    Pthread_mutex_lock(&course->courseLock);
    while(course->tutSlots < numAttendingTut);
    printf(C_COURSE "Tutorial has started for course %s with %d filled out of %d\n" RESET, course->name, course->tutSlots, pickSlots);
    sleep(2);
    Pthread_mutex_lock(&course->tutLock);
    for (int i = 0; i < course->tutSlots; i++) {
        Pthread_cond_signal(&course->tutCond);
    }
    course->tutSlots = 0;
    Pthread_mutex_unlock(&course->tutLock);
    Pthread_mutex_unlock(&course->courseLock);
}

void *course_process(void *input) {
    Course *course = (Course *) input;
    int found = 1;
    while (found) {
        found = 0;
        for (int i = 0; i < course->numValidLabs; i++) {
            Lab currentLab = all_labs[course->validLabs[i]];
            if (!currentLab.available) continue;
            for (int j = 0; j < currentLab.numTA; j++) {
                if (currentLab.taTimes[j] == currentLab.TALimit) continue;
                Pthread_mutex_lock(&currentLab.taLock[j]);
                found = 1;
                if (currentLab.taTimes[j] == currentLab.TALimit) {
                    Pthread_mutex_unlock(&currentLab.taLock[j]);
                    continue;
                }
                printf(C_LAB "TA %d from lab %s has been allocated to course %s for %dth TAship\n" RESET, j, currentLab.name, course->name, currentLab.taTimes[j] + 1);
                take_tutorial(course);
                currentLab.taTimes[j]++;
                printf(C_COURSE "TA %d from lab %s has completed the tutorial and left the course %s\n" RESET, j, currentLab.name, course->name);
                Pthread_mutex_unlock(&currentLab.taLock[j]);
            }
        }
    }
    Pthread_mutex_lock(&course->courseLock);
    course->withdrawn = 1;
    printf(C_COURSE "Course %s doesn't have any TAs eligible and is removed from course offerings\n" RESET, course->name);
    Pthread_cond_broadcast(&course->openCond);
    Pthread_mutex_unlock(&course->courseLock);

    return NULL;
}
