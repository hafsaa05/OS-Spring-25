#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 10000000

int main() {
    float *A = (float *)malloc(N * sizeof(float));
    float *B = (float *)malloc(N * sizeof(float));
    float *C = (float *)malloc(N * sizeof(float));

    if (!A || !B || !C) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (size_t i = 0; i < N; i++) {
        A[i] = 1.0f;
        B[i] = 2.0f;
    }

    clock_t start = clock();

    for (size_t i = 0; i < N; i++) {
        C[i] = A[i] + B[i];
    }

    clock_t end = clock();
    printf("Time taken (serial): %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(A);
    free(B);
    free(C);
    return 0;
}
