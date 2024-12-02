#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const char *file_name = "testfile.txt";

    if (unlink(file_name) == 0) {
        printf("File '%s' deleted successfully.\n", file_name);
    } else {
        perror("Failed to delete file");
    }

    return 0;
}
