#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 3

int *numbers;
int count;

void *calculate_average(void *arg) {
    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += numbers[i];
    }
    double *avg = malloc(sizeof(double));
    *avg = sum / count;
    return (void *)avg;
}

void *find_minimum(void *arg) {
    int *min = malloc(sizeof(int));
    *min = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] < *min) {
            *min = numbers[i];
        }
    }
    return (void *)min;
}

void *find_maximum(void *arg) {
    int *max = malloc(sizeof(int));
    *max = numbers[0];
    for (int i = 1; i < count; i++) {
        if (numbers[i] > *max) {
            *max = numbers[i];
        }
    }
    return (void *)max;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <numbers>\n", argv[0]);
        return 1;
    }

    count = argc - 1;
    numbers = malloc(count * sizeof(int));
    for (int i = 0; i < count; i++) {
        numbers[i] = atoi(argv[i + 1]);
    }

    pthread_t threads[NUM_THREADS];
    void *results[NUM_THREADS];

    pthread_create(&threads[0], NULL, calculate_average, NULL);
    pthread_create(&threads[1], NULL, find_minimum, NULL);
    pthread_create(&threads[2], NULL, find_maximum, NULL);

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], &results[i]);
    }

    printf("The average value is %.2f.\n", *(double *)results[0]);
    printf("The minimum value is %d.\n", *(int *)results[1]);
    printf("The maximum value is %d.\n", *(int *)results[2]);

    free(results[0]);
    free(results[1]);
    free(results[2]);
    free(numbers);

    return 0;
}
