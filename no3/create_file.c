#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fp = fopen("testfile.txt", "w");
    if (fp == NULL) {
        perror("Failed to create file");
        return 1;
    }

    fprintf(fp, "Hello, World!\n");
    fclose(fp);

    printf("File 'testfile.txt' created and written successfully.\n");
    return 0;
}
