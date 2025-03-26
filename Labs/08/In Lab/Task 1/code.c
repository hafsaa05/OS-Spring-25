// part (c)

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread_function(void *arg) {
    printf("Thread executing...\n");
    pthread_exit((void *)42); // Exiting thread with status 42
}

int main() {
    pthread_t thread;
    void *exit_status;

    // Create thread
    if (pthread_create(&thread, NULL, thread_function, NULL) != 0) {
        perror("Failed to create thread");
        return 1;
    }

    // Wait for the thread to finish and get its exit status
    if (pthread_join(thread, &exit_status) != 0) {
        perror("Failed to join thread");
        return 1;
    }

    printf("Thread exited with status: %ld\n", (long)exit_status);

    return 0;
}
