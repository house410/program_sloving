
#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int vr_scanf(const char* str, void* a, void* b, void* c, void* d) {
    char input_str[1024];
    fgets(input_str, 1024, stdin);

    char* token = strtok(input_str, " \t");
    int index = 0;
    while (token != NULL) {
        switch (index) {
        case 0:
            if (sscanf(token, "%d", (int*)a) != 1) return -1;
            break;
        case 1:
            if (sscanf(token, "%c", (char*)b) != 1) return -1;
            break;
        case 2:
            if (sscanf(token, "%f", (float*)c) != 1) return -1;
            break;
        case 3:
            if (sscanf(token, "%s", (char*)d) != 1) return -1;
            break;
        default:
            break;
        }
        token = strtok(NULL, " \t");
        index++;
    }

    if (index < 4) return -1;
    return 0;
}

int main() {
    int a;
    char b;
    float c;
    char d[1024];

    printf("Enter values: ");

    int result = vr_scanf("%d %c %f %s\t", &a, &b, &c, d);
    if (result == 0) {
        printf("입력된 값: %d %c %f %s\n", a, b, c, d);
    }
    else {
        printf("Error\n");
    }

    return 0;
}


#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS