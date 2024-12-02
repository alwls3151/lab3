#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("testfile.txt", "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
    }
    fclose(fp);

    printf("\nFile 'testfile.txt' read successfully.\n");
    return 0;
}
