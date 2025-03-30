#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define N 10000000
#define NUM_THREADS 10

float *A, *B, *C;

typedef struct {
    size_t start, end;
} ThreadData;

void *add_part(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    for (size_t i = data->start; i < data->end; i++) {
        C[i] = A[i] + B[i];
    }
    pthread_exit(NULL);
}

int main() {
    A = (float *)malloc(N * sizeof(float));
    B = (float *)malloc(N * sizeof(float));
    C = (float *)malloc(N * sizeof(float));

    if (!A || !B || !C) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    for (size_t i = 0; i < N; i++) {
        A[i] = 1.0f;
        B[i] = 2.0f;
    }

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    size_t chunk_size = N / NUM_THREADS;

    clock_t start = clock();

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? N : (i + 1) * chunk_size;
        pthread_create(&threads[i], NULL, add_part, &thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();
    printf("Time taken (multithreaded): %.6f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(A);
    free(B);
    free(C);
    return 0;
}
