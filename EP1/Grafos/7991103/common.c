
#include "common.h"

void printArray(int *a, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%-3d", a[i]);
    }
    printf("]\n");
}

int min(int a, int b) {
    return a < b ? a : b;
}
