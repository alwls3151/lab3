#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> // wait 함수 선언 포함

int main() {
    int fd[2];
    pid_t pid;
    char write_msg[] = "Hello from parent!";
    char read_msg[100];

    if (pipe(fd) == -1) {
        perror("Pipe failed");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid > 0) { // 부모 프로세스
        close(fd[0]); // 읽기 끝 닫기
        write(fd[1], write_msg, strlen(write_msg) + 1);
        close(fd[1]); // 쓰기 끝 닫기
        wait(NULL); // 자식 프로세스 종료 대기
    } else { // 자식 프로세스
        close(fd[1]); // 쓰기 끝 닫기
        read(fd[0], read_msg, sizeof(read_msg));
        printf("Child received: %s\n", read_msg);
        close(fd[0]); // 읽기 끝 닫기
    }

    return 0;
}
