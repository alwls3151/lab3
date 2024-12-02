#ifndef CHAT_COMMON_H
#define CHAT_COMMON_H

#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 256

struct message {
    long message_type; // 메시지 유형
    char text[MAX_TEXT]; // 메시지 내용
};

#define MESSAGE_QUEUE_KEY 1234 // 메시지 큐 키

#endif
