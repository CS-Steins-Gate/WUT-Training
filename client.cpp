#include <pthread.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <cstring>
#include <iostream>
#include "proto.h"

using namespace std;

// key值
key_t key;
// 消息队列id
int msgid;
// 消息包大小
constexpr unsigned long MSG_SZ = sizeof(msg_buf) - sizeof(long);
// 读线程id
pthread_t tid1;
// 写线程id
pthread_t tid2;

// client端读进程
void* server_read(void* arg) {
    msg_buf buf;
    ssize_t res;

    while (true) {
        res = msgrcv(msgid, (void*)&buf, MSG_SZ, 2, 0);
        if (res < 0) {
            perror("msgrcv");
            return nullptr;
        }
        if (strcasecmp(buf.message, LOGOUT) == 0) {
            cerr << "\n退出成功\n";
            break;
        }
        printf("\n信道: %ld, 消息内容: %s\n", buf.mtype, buf.message);
        cerr << "请输入消息内容 >>>";
    }

    return nullptr;
}

// server的写进程
void* server_write(void* arg) {
    msg_buf snd;
    snd.mtype = 1;

    while (true) {
        cerr << "请输入消息内容 >>>";
        cin >> snd.message;

        if (msgsnd(msgid, (void*)&snd, MSG_SZ, 0) < 0) {
            perror("msgsnd");
            return nullptr;
        }
        if (strcasecmp(snd.message, LOGOUT) == 0) {
            pthread_cancel(tid1);   // 取消读线程
            cout << "退出成功\n";
            while(true);
        }
    }

    return nullptr;
}

int main() {
    // 获取key值
    key = ftok(PATHNAME, PROJ_ID);
    if (key < 0) {
        perror("ftok");
        exit(-1);
    }

    // 创建消息队列
    msgid = msgget(key, IPC_CREAT | 0600);
    if (msgid < 0) {
        perror("msgget");
        exit(-2);
    }

    // 创建线程
    if (pthread_create(&tid1, nullptr, server_read, nullptr) != 0) {
        perror("pthread_create");
        exit(-4);
    }
    if (pthread_create(&tid2, nullptr, server_write, nullptr) != 0) {
        perror("pthread_create");
        exit(-4);
    }

    // 阻塞读
    pthread_join(tid1, nullptr);

    // 取消写线程
    pthread_cancel(tid2);

    // 删除消息队列
    msgctl(msgid, IPC_RMID, nullptr);

    return 0;
}