#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <cstring>
#include <iostream>
#include "proto.h"

using namespace std;

int main() {
    // 获取key值
    key_t key = ftok(PATHNAME, PROJ_ID);
    if (key < 0) {
        perror("ftok");
        exit(-1);
    }

    // 创建消息队列
    int msgid = msgget(key, IPC_CREAT | 0600);
    if (msgid < 0) {
        perror("msgget");
        exit(-2);
    }

    // 发送数据
    msg_buf buf;
    buf.mtype = 1;
    while (true) {
        cout << "name: ";
        cin >> buf.name;
        cout << "chinese: ";
        cin >> buf.chinese;
        cout << "math: ";
        cin >> buf.math;
        cout << "english: ";
        cin >> buf.english;

        if (msgsnd(msgid, (void*)&buf, sizeof(msg_buf) - sizeof(long), 0) < 0) {
            perror("msgsnd");
            exit(-3);
        }
    }

    return 0;
}