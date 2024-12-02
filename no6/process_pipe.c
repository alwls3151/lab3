#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Failed to fork");
        return 1;
    }

    if (pid == 0) { // 자식 프로세스
        close(pipe_fd[0]); // 읽기 끝 닫기
        const char *message = "Hello from child process!";
        write(pipe_fd[1], message, sizeof(message));
        close(pipe_fd[1]); // 쓰기 끝 닫기
    } else { // 부모 프로세스
        close(pipe_fd[1]); // 쓰기 끝 닫기
        char buffer[256];
        read(pipe_fd[0], buffer, sizeof(buffer));
        close(pipe_fd[0]); // 읽기 끝 닫기
        printf("Parent received: %s\n", buffer);
    }

    return 0;
}
