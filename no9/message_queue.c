#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_TEXT 100

struct message {
    long msg_type;
    char msg_text[MAX_TEXT];
};

int main() {
    key_t key;
    int msgid;

    key = ftok("progfile", 65); // 메시지 큐 키 생성
    msgid = msgget(key, 0666 | IPC_CREAT); // 메시지 큐 생성

    if (fork() == 0) { // 자식 프로세스
        struct message msg;
        msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0);
        printf("Child received: %s\n", msg.msg_text);
        msgctl(msgid, IPC_RMID, NULL); // 메시지 큐 삭제
    } else { // 부모 프로세스
        struct message msg;
        msg.msg_type = 1;
        strcpy(msg.msg_text, "Hello from parent!");
        msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);
        wait(NULL);
    }

    return 0;
}
