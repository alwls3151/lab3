#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_SIZE 1024

int main() {
    key_t key = ftok("progfile", 65);
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);

    if (fork() == 0) { // 자식 프로세스
        char *shared_mem = (char *)shmat(shmid, (void *)0, 0);
        printf("Child read: %s\n", shared_mem);
        shmdt(shared_mem); // 공유 메모리 분리
        shmctl(shmid, IPC_RMID, NULL); // 공유 메모리 삭제
    } else { // 부모 프로세스
        char *shared_mem = (char *)shmat(shmid, (void *)0, 0);
        strcpy(shared_mem, "Hello from parent!");
        shmdt(shared_mem); // 공유 메모리 분리
        wait(NULL);
    }

    return 0;
}
