#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_LINE 256
#define MAX_ARGS 50

int getargs(char *cmd, char **argv);

int main() {
    char buf[MAX_LINE];
    char *argv[MAX_ARGS];
    pid_t pid;

    while (1) {
        printf("shell> ");
        fflush(stdout);

        if (!fgets(buf, sizeof(buf), stdin)) break; // EOF 처리
        buf[strcspn(buf, "\n")] = '\0'; // 줄바꿈 제거

        if (strlen(buf) == 0) continue; // 빈 입력 무시

        int narg = getargs(buf, argv);

        if (strcmp(argv[0], "exit") == 0) break; // 종료 명령어 처리

        pid = fork();

        if (pid == 0) { // 자식 프로세스
            execvp(argv[0], argv);
            perror("execvp failed");
            exit(EXIT_FAILURE);
        } else if (pid > 0) { // 부모 프로세스
            wait(NULL); // 자식 대기
        } else {
            perror("fork failed");
        }
    }
    return 0;
}

int getargs(char *cmd, char **argv) {
    int narg = 0;
    while (*cmd) {
        while (*cmd == ' ' || *cmd == '\t') *cmd++ = '\0'; // 공백 제거
        if (*cmd) argv[narg++] = cmd;
        while (*cmd && *cmd != ' ' && *cmd != '\t') cmd++;
    }
    argv[narg] = NULL;
    return narg;
}