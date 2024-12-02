#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// 사용자 정의 system 함수
int my_system(const char *command) {
    if (command == NULL) {
        fprintf(stderr, "Invalid command\n");
        return -1; // 실패: 잘못된 명령
    }

    pid_t pid = fork(); // 새로운 프로세스 생성
    if (pid == 0) { // 자식 프로세스
        execl("/bin/sh", "sh", "-c", command, NULL); // 명령어 실행
        perror("execl failed"); // 실행 실패 시 에러 출력
        exit(EXIT_FAILURE); // 실패 시 자식 프로세스 종료
    } else if (pid > 0) { // 부모 프로세스
        int status;
        waitpid(pid, &status, 0); // 자식 프로세스 종료 대기
        return status; // 자식 프로세스의 종료 상태 반환
    } else {
        perror("fork failed"); // fork 실패 시 에러 출력
        return -1; // 실패 반환
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command>\n", argv[0]);
        return EXIT_FAILURE; // 명령어 인자가 없을 경우 종료
    }

    // 입력 명령어를 하나의 문자열로 합치기
    char command[256] = "";
    for (int i = 1; i < argc; i++) {
        strcat(command, argv[i]);
        if (i < argc - 1) strcat(command, " "); // 인자 간 공백 추가
    }

    printf("Executing command: %s\n", command);

    // 사용자 정의 system 함수 호출
    int result = my_system(command);

    if (result == -1) {
        printf("Command execution failed.\n");
    } else {
        printf("Command executed successfully.\n");
    }

    return EXIT_SUCCESS;
}