//Write a C program using shared memory to demonstrate IPC bw two processes : producer &  consumer . The consumer reads numbers from shared memory, squares them and computes their sum , and displays the result , ensure proper error handling , and perform cleanup of shared memory after execution
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define SIZE 4096
#define NUM_COUNT 5

typedef struct {
    int numbers[NUM_COUNT];
    int ready; // Flag to indicate data is ready
} SharedData;

int main() {
    // Create shared memory
    SharedData *shm = mmap(NULL, SIZE, PROT_READ | PROT_WRITE,
                           MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shm == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    shm->ready = 0; // Initially, data is not ready

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        munmap(shm, SIZE);
        exit(1);
    }

    if (pid == 0) {
        // Producer process
        printf("Producer: Writing numbers to shared memory...\n");
        for (int i = 0; i < NUM_COUNT; ++i) {
            shm->numbers[i] = i + 1; // Example: 1 to 5
        }
        shm->ready = 1; // Mark data as ready
        printf("Producer: Data written and marked ready.\n");
        exit(0);
    } else {
        // Consumer process
        wait(NULL); // Wait for producer to finish

        if (shm->ready != 1) {
            fprintf(stderr, "Consumer: Data not ready.\n");
            munmap(shm, SIZE);
            exit(1);
        }

        printf("Consumer: Reading data from shared memory...\n");

        int sum = 0;
        for (int i = 0; i < NUM_COUNT; ++i) {
            int squared = shm->numbers[i] * shm->numbers[i];
            sum += squared;
            printf("Consumer: %d^2 = %d\n", shm->numbers[i], squared);
        }

        printf("Consumer: Sum of squares = %d\n", sum);

        // Cleanup
        if (munmap(shm, SIZE) == -1) {
            perror("munmap failed");
            exit(1);
        }
    }

    return 0;
}
