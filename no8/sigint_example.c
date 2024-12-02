#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// SIGINT 핸들러 함수
void handle_sigint(int sig) {
    printf("\nCaught SIGINT (signal %d). Exiting gracefully...\n", sig);
    exit(0);
}

int main() {
    // SIGINT 신호를 핸들링하도록 설정
    signal(SIGINT, handle_sigint);

    printf("Program running. Press Ctrl+C to send SIGINT.\n");

    // 무한 루프
    while (1) {
        printf("Working...\n");
        sleep(1);
    }

    return 0;
}