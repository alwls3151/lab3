#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_SENTENCES 5
#define MAX_LENGTH 256

// 샘플 문장 배열
const char *sample_sentences[MAX_SENTENCES] = {
    "The quick brown fox jumps over the lazy dog.",
    "Practice makes perfect.",
    "C programming is powerful.",
    "Keep calm and code on.",
    "Typing fast is an essential skill."
};

int main() {
    int total_mistakes = 0; // 총 오타 수
    double total_time = 0;  // 총 시간 (초)
    char user_input[MAX_LENGTH]; // 사용자 입력
    clock_t start, end; // 타이머 변수

    printf("=== 타자 연습 프로그램 ===\n");
    printf("총 %d개의 문장이 제공됩니다. 정확히 입력하세요.\n\n", MAX_SENTENCES);

    // 각 문장을 반복하여 연습
    for (int i = 0; i < MAX_SENTENCES; i++) {
        printf("문장 %d: %s\n", i + 1, sample_sentences[i]);
        printf("입력: ");
        
        // 문장 시작 시간 기록
        start = clock();
        fgets(user_input, sizeof(user_input), stdin);
        end = clock(); // 문장 종료 시간 기록

        // 입력 시간 계산
        double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        total_time += elapsed_time;

        // 사용자 입력에서 줄바꿈 제거
        user_input[strcspn(user_input, "\n")] = '\0';

        // 오타 확인
        int mistakes = 0;
        for (int j = 0; j < strlen(sample_sentences[i]); j++) {
            if (user_input[j] != sample_sentences[i][j]) {
                mistakes++;
            }
        }

        printf("오타 수: %d\n", mistakes);
        total_mistakes += mistakes;
    }

    // 평균 분당 타자 수 계산
    double wpm = (double)(MAX_SENTENCES * 5) / (total_time / 60.0); // 5 단어 기준

    printf("\n=== 결과 ===\n");
    printf("총 오타 수: %d\n", total_mistakes);
    printf("평균 분당 타자수: %.2f WPM\n", wpm);

    return 0;
}