#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Failed to fork");
        return 1;
    }

    if (pid == 0) {
        printf("Child process: PID = %d\n", getpid());
        sleep(2); // 자식 프로세스에서 2초 대기
        printf("Child process exiting.\n");
        exit(0);
    } else {
        printf("Parent process waiting for child to complete.\n");
        wait(NULL); // 자식 프로세스 종료 대기
        printf("Child process has completed.\n");
    }

    return 0;
}
