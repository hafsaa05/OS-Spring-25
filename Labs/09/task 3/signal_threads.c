#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>

#define NUM_THREADS 4
pthread_t threads[NUM_THREADS]; // Global thread IDs

// Signal handler
void sigusr1_handler(int signum) {
    pid_t tid = syscall(SYS_gettid);    // Get Thread ID
    pid_t pid = getpid();               // Get Process ID
    pid_t ppid = getppid();             // Get Parent Process ID

    fprintf(stdout,
        "Thread received SIGUSR1 signal → "
        "ProcessID: %d, ParentID: %d, ThreadID (TID): %d, pthread_self: %lu\n",
        pid, ppid, tid, pthread_self());
}

// Thread function
void* thread_function(void* arg) {
    // Register signal handler in thread (for Experiment 2 only)
    signal(SIGUSR1, sigusr1_handler); 

    while (1) sleep(1);  // Keep thread alive
    return NULL;
}

int main() {
    // Register signal handler in main process (for Experiment 1)
    signal(SIGUSR1, sigusr1_handler);  // Line 23

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    sleep(1);  // Wait for threads to start

    // Print thread and process info
    pid_t tid = syscall(SYS_gettid);
    pid_t pid = getpid();
    pid_t ppid = getppid();

    fprintf(stdout,
        "Parent Process ID: %d, Process ID: %d, Main Thread ID (TID): %d\n",
        ppid, pid, tid);

    fprintf(stdout,
        "Thread IDs: 0=%lu, 1=%lu, 2=%lu, 3=%lu\n",
        threads[0], threads[1], threads[2], threads[3]);

    // Send SIGUSR1 to process and specific thread
    kill(pid, SIGUSR1);               // Line 34
    pthread_kill(threads[2], SIGUSR1); // Line 35

    // Join threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
