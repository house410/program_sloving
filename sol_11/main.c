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
    int* i;             // int �� ���� �迭
    char* c;            // char �� ���� �迭
    char** s;           // ���ڿ� �������� �迭 ������ ���� �迭
    int count_d = 0;    // %d ����
    int count_c = 0;    // %c ����
    int count_s = 0;    // %s ����

    // ���� ����
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return;
    }

    // ���Ͽ��� �ؽ�Ʈ �о���� �� ���� ����
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

    // ���� �迭 �Ҵ�
    i = (int*)malloc(sizeof(int) * count_d);
    c = (char*)malloc(sizeof(char) * count_c);
    s = (char**)malloc(sizeof(char*) * count_s);

    // ���� �ٽ� �о����
    fseek(file, 0, SEEK_SET);
    int index_d = 0;
    int index_c = 0;
    int index_s = 0;

    // ���� �迭�� �� �Ҵ�
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
                token[strcspn(token, "\n")] = '\0';  // ���� ���� ����
                s[index_s] = (char*)malloc(sizeof(char) * (strlen(token) + 1));
                strcpy(s[index_s], token);
                index_s++;
            }
            token = strtok(NULL, "%");
        }
    }

    // ���� �迭 �� Ȯ��
    printf("int ����: %d\n", count_d);
    printf("char ����: %d\n", count_c);
    printf("string ����: %d\n", count_s);

    // ���� �迭 ����
    free(i);
    free(c);
    for (int j = 0; j < count_s; j++) {
        free(s[j]);
    }
    free(s);

    // ���� �ݱ�
    fclose(file);
}

int main() {
    processFile("input.txt");
    return 0;
}
