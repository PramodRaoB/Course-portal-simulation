#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include "course.h"
#include "lab.h"
#include "wrapper.h"
#include "globals.h"

Course *all_courses;

void course_init(int n) {
    all_courses = (Course *) malloc(n * sizeof(Course));
    assert(all_courses);
    for (int i = 0; i < n; i++) {
        all_courses[i].id = i;
        all_courses[i].prefer = 0;
        Pthread_mutex_init(&all_courses[i].tutLock, NULL);
        Pthread_cond_init(&all_courses[i].tutorialSlots, NULL);
        all_courses[i].name = (char *) malloc(MAX_COURSE_NAME);
        assert(all_courses[i].name);
    }
}

void take_tutorial(Course *course, Lab *lab, int ta) {
    int pickSlots = (rand() % course->course_max_slots) + 1;
    int pref = course->prefer;
    pickSlots = MIN(pickSlots, pref);
    Pthread_mutex_lock(&course->tutLock);
    sleep(2);
    for (int i = 0; i < pickSlots; i++)
        Pthread_cond_signal(&course->tutorialSlots);
    Pthread_mutex_unlock(&course->tutLock);
}

void *course_process(void *input) {
    Course *course = (Course *) input;
    int found = 1;
    while (found) {
        found = 0;
        for (int i = 0; i < course->numValidLabs; i++) {
            Lab currentLab = all_labs[course->validLabs[i]];
            if (!currentLab.available) continue;
            found = 1;
            for (int j = 0; j < currentLab.numTA; j++) {
                if (currentLab.taTimes[j] == currentLab.TALimit) continue;
                Pthread_mutex_lock(&currentLab.taLock[j]);
                if (currentLab.taTimes[j] == currentLab.TALimit) {
                    Pthread_mutex_unlock(&currentLab.taLock[j]);
                    continue;
                }
                take_tutorial(course, &currentLab, j);
                currentLab.taTimes[j]++;
                Pthread_mutex_unlock(&currentLab.taLock[j]);
            }
        }
    }
}
