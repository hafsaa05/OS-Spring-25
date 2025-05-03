#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ARRAY_SIZE 10

int array[ARRAY_SIZE] = {7, 2, 5, 8, 1, 3, 4, 9, 6, 0};

void* sort_half(void* arg) {
    int start = *(int*)arg;
    int end = start + (ARRAY_SIZE / 2);

    // Simple bubble sort for the specified half
    for (int i = start; i < end - 1; i++) {
        for (int j = start; j < end - i - 1 + start; j++) {
            if (array[j] > array[j + 1]) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }

    pthread_exit(NULL);
}

void merge_sorted_arrays() {
    int temp[ARRAY_SIZE];
    int mid = ARRAY_SIZE / 2;
    int i = 0, j = mid, k = 0;

    while (i < mid && j < ARRAY_SIZE) {
        if (array[i] < array[j]) {
            temp[k++] = array[i++];
        } else {
            temp[k++] = array[j++];
        }
    }

    while (i < mid) {
        temp[k++] = array[i++];
    }

    while (j < ARRAY_SIZE) {
        temp[k++] = array[j++];
    }

    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = temp[i];
    }
}

int main() {
    pthread_t thread1, thread2;
    int start1 = 0, start2 = ARRAY_SIZE / 2;

    // Create threads to sort two halves of the array
    pthread_create(&thread1, NULL, sort_half, (void*)&start1);
    pthread_create(&thread2, NULL, sort_half, (void*)&start2);

    // Wait for both threads to complete
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Merge the sorted halves
    merge_sorted_arrays();

    // Print the sorted array
    printf("Sorted array: ");
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
