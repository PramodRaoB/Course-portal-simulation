#ifndef PARALLELISM_GLOBALS_H
#define PARALLELISM_GLOBALS_H

#define MIN(a, b) (a < b) ? a : b

#define C_STUDENT     "\x1b[31m"
#define C_LAB   "\x1b[32m"
#define C_COURSE  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

extern int num_students;
extern int num_labs;
extern int num_courses;

#endif //PARALLELISM_GLOBALS_H
