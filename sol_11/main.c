#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS

void processFile(const char* filename);

void processFile(const char* filename) {
    FILE* file;
    char line[MAX_LINE_LENGTH];
    int* i;             // int 형 동적 배열
    char* c;            // char 형 동적 배열
    char** s;           // 문자열 포인터의 배열 형태의 동적 배열
    int count_d = 0;    // %d 개수
    int count_c = 0;    // %c 개수
    int count_s = 0;    // %s 개수

    // 파일 열기
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // 파일에서 텍스트 읽어오기 및 개수 세기
    while (fgets(line, sizeof(line), file) != NULL) {
        char* token = strtok(line, "%");
        while (token != NULL) {
            if (strstr(token, "d"))
                count_d++;
            else if (strstr(token, "c"))
                count_c++;
            else if (strstr(token, "s"))
                count_s++;
            token = strtok(NULL, "%");
        }
    }

    // 동적 배열 할당
    i = (int*)malloc(sizeof(int) * count_d);
    c = (char*)malloc(sizeof(char) * count_c);
    s = (char**)malloc(sizeof(char*) * count_s);

    // 파일 다시 읽어오기
    fseek(file, 0, SEEK_SET);
    int index_d = 0;
    int index_c = 0;
    int index_s = 0;

    // 동적 배열에 값 할당
    while (fgets(line, sizeof(line), file) != NULL) {
        char* token = strtok(line, "%");
        while (token != NULL) {
            if (strstr(token, "d")) {
                i[index_d] = atoi(token);
                index_d++;
            }
            else if (strstr(token, "c")) {
                c[index_c] = token[0];
                index_c++;
            }
            else if (strstr(token, "s")) {
                token[strcspn(token, "\n")] = '\0';  // 개행 문자 제거
                s[index_s] = (char*)malloc(sizeof(char) * (strlen(token) + 1));
                strcpy(s[index_s], token);
                index_s++;
            }
            token = strtok(NULL, "%");
        }
    }

    // 동적 배열 값 확인
    printf("int 개수: %d\n", count_d);
    printf("char 개수: %d\n", count_c);
    printf("string 개수: %d\n", count_s);

    // 동적 배열 해제
    free(i);
    free(c);
    for (int j = 0; j < count_s; j++) {
        free(s[j]);
    }
    free(s);

    // 파일 닫기
    fclose(file);
}

int main() {
    processFile("input.txt");
    return 0;
}
