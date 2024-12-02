#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_dir_recursively(const char *path) {
    struct dirent *entry;
    DIR *dp = opendir(path);

    if (dp == NULL) {
        perror("opendir failed");
        return;
    }

    printf("\nDirectory: %s\n", path);

    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue; // 현재 디렉토리와 부모 디렉토리 무시
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        struct stat path_stat;
        if (stat(full_path, &path_stat) == 0) {
            if (S_ISDIR(path_stat.st_mode)) {
                // 디렉토리인 경우 재귀 호출
                list_dir_recursively(full_path);
            } else {
                // 파일 출력
                printf("%s\n", full_path);
            }
        } else {
            perror("stat failed");
        }
    }

    closedir(dp);
}

int main() {
    char path[1024];

    printf("나열할 디렉토리를 입력하세요 (재귀적): ");
    scanf("%s", path);

    list_dir_recursively(path);

    return 0;
}