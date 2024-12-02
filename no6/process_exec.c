#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf("Current process PID = %d\n", getpid());

    char *args[] = {"/bin/ls", "-l", NULL};
    printf("Executing 'ls -l' command:\n");
    execve("/bin/ls", args, NULL);

    // execve가 실패한 경우
    perror("execve failed");
    return 1;
}
