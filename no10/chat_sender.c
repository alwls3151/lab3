#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chat_common.h"

int main() {
    int msgid = msgget(MESSAGE_QUEUE_KEY, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget failed");
        exit(EXIT_FAILURE);
    }

    struct message msg;
    msg.message_type = 1; // 메시지 유형 지정

    printf("=== 채팅 프로그램: 송신 ===\n");
    printf("종료하려면 'exit' 입력\n");

    while (1) {
        printf("메시지 입력: ");
        fgets(msg.text, MAX_TEXT, stdin);
        msg.text[strcspn(msg.text, "\n")] = '\0'; // 줄바꿈 제거

        if (strcmp(msg.text, "exit") == 0) break; // 종료 조건

        if (msgsnd(msgid, &msg, sizeof(msg.text), 0) == -1) {
            perror("msgsnd failed");
            exit(EXIT_FAILURE);
        }
    }

    printf("송신 프로그램 종료.\n");
    return 0;
}
