cmake_minimum_required(VERSION 3.21)
project(parallelism C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lpthread")

add_executable(parallelism
        main.c course.c course.h student.c student.h globals.h lab.c lab.h wrapper.c wrapper.h)
