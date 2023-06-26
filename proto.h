#pragma once

// 路径名
#define PATHNAME "/home/sjq/cppProjects/wut-training"

// 项目标识符
#define PROJ_ID 'x'

// 消息内容大小
#define MSG_SIZE 64

// 退出信号
#define LOGOUT "quit"

// 消息包
struct msg_buf {
    long mtype;
    char message[MSG_SIZE];
    pid_t pid;
};