#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    pid_t pid = fork(); // 새로운 프로세스 생성

    if (pid < 0) { // fork 실패 시
        perror("Failed to fork");
        return 1;
    }

    if (pid == 0) { // 자식 프로세스
        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
        exit(0); // 자식 프로세스 종료
    } else { // 부모 프로세스
        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
    }

    return 0;
}