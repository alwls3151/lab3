#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

#define SHM_SIZE 1024 // 공유 메모리 크기
#define SEM_KEY 1234  // 세마포어 키
#define SHM_KEY 5678  // 공유 메모리 키

// 세마포어 연산 정의
void sem_op(int semid, int semnum, int op) {
    struct sembuf sb = {semnum, op, 0};
    if (semop(semid, &sb, 1) == -1) {
        perror("semop failed");
        exit(EXIT_FAILURE);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // 공유 메모리 및 세마포어 생성
    int shmid = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(EXIT_FAILURE);
    }

    int semid = semget(SEM_KEY, 2, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget failed");
        exit(EXIT_FAILURE);
    }

    // 세마포어 초기화 (0번: 부모, 1번: 자식)
    semctl(semid, 0, SETVAL, 1); // 부모 프로세스 사용 가능
    semctl(semid, 1, SETVAL, 0); // 자식 프로세스 사용 불가

    // 공유 메모리 연결
    char *shm_addr = (char *)shmat(shmid, NULL, 0);
    if (shm_addr == (void *)-1) {
        perror("shmat failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == -1) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) { // 자식 프로세스: 파일 쓰기
        int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (dest_fd == -1) {
            perror("open destination file failed");
            exit(EXIT_FAILURE);
        }

        while (1) {
            // 자식 세마포어 대기
            sem_op(semid, 1, -1);

            // 공유 메모리에서 읽기
            if (strncmp(shm_addr, "EOF", 3) == 0) break;

            if (write(dest_fd, shm_addr, strlen(shm_addr)) == -1) {
                perror("write failed");
                exit(EXIT_FAILURE);
            }

            // 부모 세마포어 신호
            sem_op(semid, 0, 1);
        }

        close(dest_fd);
        shmdt(shm_addr); // 공유 메모리 분리
        exit(EXIT_SUCCESS);

    } else { // 부모 프로세스: 파일 읽기
        int src_fd = open(argv[1], O_RDONLY);
        if (src_fd == -1) {
            perror("open source file failed");
            exit(EXIT_FAILURE);
        }

        while (1) {
            // 부모 세마포어 대기
            sem_op(semid, 0, -1);

            // 파일에서 읽기
            ssize_t bytes_read = read(src_fd, shm_addr, SHM_SIZE - 1);
            if (bytes_read == -1) {
                perror("read failed");
                exit(EXIT_FAILURE);
            }

            shm_addr[bytes_read] = '\0'; // 널 종료
            if (bytes_read == 0) { // 파일 끝
                strncpy(shm_addr, "EOF", 3);
                sem_op(semid, 1, 1);
                break;
            }

            // 자식 세마포어 신호
            sem_op(semid, 1, 1);
        }

        close(src_fd);
        wait(NULL); // 자식 프로세스 종료 대기
        shmdt(shm_addr); // 공유 메모리 분리

        // 공유 메모리 및 세마포어 제거
        shmctl(shmid, IPC_RMID, NULL);
        semctl(semid, 0, IPC_RMID);
    }

    return 0;
}
