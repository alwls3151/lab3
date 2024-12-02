#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// SIGUSR1 핸들러 함수
void handle_sigusr1(int sig) {
    printf("Received SIGUSR1 (signal %d) from process %d\n", sig, getpid());
}

int main() {
    // SIGUSR1 신호를 핸들링하도록 설정
    signal(SIGUSR1, handle_sigusr1);

    printf("Program running with PID %d. Send SIGUSR1 using 'kill -SIGUSR1 %d'.\n", getpid(), getpid());

    // 무한 루프
    while (1) {
        sleep(1); // 대기
    }

    return 0;
}
