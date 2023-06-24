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

    // 接收数据
    msg_buf buf;
    while (true) {
        if (msgrcv(msgid, (void*)&buf, sizeof(msg_buf) - sizeof(long), 0, 0) < 0) {
            perror("msgrcv");
            exit(-3);
        }
        cout << "name = " << buf.name << '\n';
        cout << "chinese = " << buf.chinese << '\n';
        cout << "math = " << buf.math << '\n';
        cout << "english = " << buf.english << endl;
    }

    return 0;
}