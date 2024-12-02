#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *dir_name = "testdir";

    if (mkdir(dir_name, 0755) == 0) {
        printf("Directory '%s' created successfully.\n", dir_name);
    } else {
        perror("Failed to create directory");
    }

    return 0;
}
