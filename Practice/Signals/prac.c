// The task is to create a C program that defines a custom signal handler for `SIGUSR1`. 
// When the signal is received, the program should spawn two threads to compute the sum of numbers from 
// 1 to 666, dividing the range into two segments. One thread will calculate the sum of numbers from 1 
// to 333, while the other thread will compute the sum from 334 to 666. The results from both threads 
// must be safely combined using a mutex to prevent race conditions. The program should block the 
// signal `SIGKILL` during the execution of the signal handler, ensuring that the signal handler can 
// finish its execution without interference. The program should only begin the computation after 
// receiving the custom signal and properly synchronize the final result, ensuring that both threads 
// have completed their calculations before displaying the total sum.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>

pthread_mutex_t mutex; // Mutex to ensure thread-safe combining of results

int sum = 0; // Global variable to store the sum
int range1 = 334; // Range for thread 1 (334 to 666)
int range2 = 667; // Range for thread 2 (1 to 333)

void my_handler(int signum) {
    fprintf(stdout, "Caught custom signal %d\n", signum);
    fflush(stdout); // Ensure the output is printed immediately
}

void* sum1(void* param) {
    int start = 1, end = range1;
    int local_sum = 0;

    for (int i = start; i < end; i++) {
        local_sum += i;
    }

    pthread_mutex_lock(&mutex); // Lock to update the global sum safely
    sum += local_sum;
    pthread_mutex_unlock(&mutex); // Unlock after updating

    return NULL;
}

void* sum2(void* param) {
    int start = range1, end = range2;
    int local_sum = 0;

    for (int i = start; i < end; i++) {
        local_sum += i;
    }

    pthread_mutex_lock(&mutex); // Lock to update the global sum safely
    sum += local_sum;
    pthread_mutex_unlock(&mutex); // Unlock after updating

    return NULL;
}

int main() {
    signal(SIGUSR1, my_handler); // Set up the signal handler
    pid_t pid = getpid(); // Get the process ID for sending signal to the process

    // Block SIGKILL to ensure the program can finish its execution properly
    // Declare a sigset_t variable to hold the set of signals to be blocked
    sigset_t blockset;
    
    // Initialize the blockset to an empty set (i.e., no signals are blocked initially)
    sigemptyset(&blockset);
    
    // Add the SIGKILL signal to the blockset, meaning we want to block SIGKILL
    sigaddset(&blockset, SIGKILL);
    
    // Block the signals in blockset (in this case, SIGKILL) for the current process
    // This will prevent the process from being terminated by SIGKILL while it executes
    sigprocmask(SIG_BLOCK, &blockset, NULL);

    pthread_t p1, p2;

    pthread_mutex_init(&mutex, NULL); // Initialize the mutex

    // Create two threads for summing the segments
    pthread_create(&p1, NULL, sum1, NULL);
    pthread_create(&p2, NULL, sum2, NULL);

    // Wait for the threads to complete
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);

    // After both threads have completed, unblock SIGKILL
    sigprocmask(SIG_UNBLOCK, &blockset, NULL);

    // Send the custom signal to the program
    kill(pid, SIGUSR1);

    // Output the final result after synchronization
    printf("Final Sum: %d\n", sum);

    pthread_mutex_destroy(&mutex); // Clean up mutex

    return 0;
}
