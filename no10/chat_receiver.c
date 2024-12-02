#include <stdio.h>
#include <stdlib.h>
#include "chat_common.h"

int main() {
    int msgid = msgget(MESSAGE_QUEUE_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    struct message msg;

    printf("=== 채팅 프로그램: 수신 ===\n");
    printf("종료하려면 Ctrl+C를 누르세요.\n");

    while (1) {
        if (msgrcv(msgid, &msg, sizeof(msg.text), 1, 0) == -1) {
            perror("msgrcv failed");
            exit(EXIT_FAILURE);
        }

        printf("받은 메시지: %s\n", msg.text);
    }

    return 0;
}
