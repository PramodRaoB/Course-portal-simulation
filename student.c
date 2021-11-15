#include <malloc.h>
#include <assert.h>
#include "student.h"

Student *all_students;

void student_init(int n) {
    all_students = (Student *) malloc(n * sizeof(Student));
    assert(all_students);
    for (int i = 0; i < n; i++) {
        all_students[i].id = i;
    }
}
