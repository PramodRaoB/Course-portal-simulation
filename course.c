#include <malloc.h>
#include <assert.h>
#include "course.h"

Course *all_courses;

void course_init(int n) {
    all_courses = (Course *) malloc(n * sizeof(Course));
    assert(all_courses);
    for (int i = 0; i < n; i++) {
        all_courses[i].id = i;
        all_courses[i].name = (char *) malloc(MAX_COURSE_NAME);
        assert(all_courses[i].name);
    }
}
