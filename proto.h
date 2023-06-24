#pragma once

#define PATHNAME "/home/sjq/cppProjects/wut-training"

#define PROJ_ID 'x'

#define NAME_SIZE 32

struct msg_buf {
    long mtype;
    char name[NAME_SIZE];
    int chinese;
    int math;
    int english;
};