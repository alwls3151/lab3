#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const char *dir_name = "testdir";

    if (rmdir(dir_name) == 0) {
        printf("Directory '%s' deleted successfully.\n", dir_name);
    } else {
        perror("Failed to delete directory");
    }

    return 0;
}
