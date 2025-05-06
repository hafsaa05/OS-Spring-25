#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include <sys/syscall.h>  // for syscall(SYS_gettid)

#define NUM_THREADS 4
pthread_t threads[NUM_THREADS]; // global array to store thread IDs

// Signal handler for SIGUSR1
void sigusr1_handler(int signum) {
    pid_t tid = syscall(SYS_gettid);     // Get thread ID (Linux-specific)
    pid_t pid = getpid();                // Get process ID
    pid_t ppid = getppid();              // Get parent process ID

    fprintf(stdout,
        "Thread received SIGUSR1 (parent=%d) [pid=%d] {tid=%d}\n",
        ppid, pid, tid);
}

// Thread function
void* thread_function(void* arg) {
    while (1) {
        sleep(1);  // Keep the thread alive
    }
    return NULL;
}

int main() {
    // Register signal handler for SIGUSR1
    signal(SIGUSR1, sigusr1_handler);

    // Create threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Print IDs
    pid_t main_tid = syscall(SYS_gettid);
    pid_t pid = getpid();
    pid_t ppid = getppid();

    fprintf(stdout, "Parent Process ID: %d, Process ID: %d, main() thread ID: %d\n", ppid, pid, main_tid);
    fprintf(stdout, "Thread IDs: 0=%lu, 1=%lu, 2=%lu, 3=%lu\n",
        threads[0], threads[1], threads[2], threads[3]);

    // Wait a bit before sending signals
    sleep(2);

    // Send signal to entire process (any thread may handle it)
    kill(pid, SIGUSR1);

    // Send signal specifically to thread 2
    pthread_kill(threads[2], SIGUSR1);

    // Wait for threads to finish (they won't unless killed)
    for (int i = 0; i < NUM_THREADS; ++i) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
