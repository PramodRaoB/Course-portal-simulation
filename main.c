#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "student.h"
#include "course.h"
#include "lab.h"
#include "globals.h"

int num_students, num_labs, num_courses;

int main() {
    scanf("%d %d %d", &num_students, &num_labs, &num_courses);
    student_init(num_students);
    lab_init(num_labs);
    course_init(num_courses);

    for (int i = 0; i < num_courses; i++) {
        scanf("%s %lf %d", all_courses[i].name, &all_courses[i].interestQuotient, &all_courses[i].course_max_slots);
        int numValidLabs;
        scanf("%d", &numValidLabs);
        all_courses[i].validLabs = (int *) malloc(numValidLabs * sizeof(int));
        assert(all_courses[i].validLabs);
        for (int j = 0; j < numValidLabs; j++)
            scanf("%d", &all_courses[i].validLabs[j]);
    }

    for (int i = 0; i < num_students; i++) {
        scanf("%lf", &all_students[i].calibre);
        for (int j = 0; j < 3; j++)
            scanf("%d", &all_students[i].preference[j]);
        scanf("%lld", &all_students[i].enterTime);
    }

    for (int i = 0; i < num_labs; i++) {
        scanf("%s %d %d", all_labs[i].name, &all_labs[i].numTA, &all_labs[i].TALimit);
    }
}