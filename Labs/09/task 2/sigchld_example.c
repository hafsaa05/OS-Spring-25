#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>

// Signal handler function to handle SIGCHLD
void proc_exit(int signum) {
    pid_t pid;
    int wstat;
    
    // Reap terminated child processes
    while ((pid = wait3(&wstat, WNOHANG, NULL)) > 0) {
        printf("Child process with PID %d terminated\n", pid);
        printf("Return code: %d\n", WEXITSTATUS(wstat));
    }

    printf("return value of wait3() is %d\n", pid);
}

// Main function
int main() {
    // Register signal handler for SIGCHLD
    signal(SIGCHLD, proc_exit);
    
    // Create 3 child processes
    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("main: fork");
            exit(1);
        }

        // In the child process, print a message and exit with a random return code
        if (pid == 0) {
            printf("Child %d is alive temporarily (PID: %d)\n", i + 1, getpid());
            int ret_code = rand();  // Random exit code
            printf("Child %d exiting with return code %d\n", i + 1, ret_code);
            exit(ret_code);
        }
    }
    
    // Parent process sleeps, allowing children to terminate and become zombies
    sleep(5);  // Allow time for child processes to terminate and become zombies
    
    // Main process will wait for signals (SIGCHLD)
    printf("Parent process waiting for signals...\n");
    pause(); // Suspends the execution of the parent until a signal arrives
    
    return 0;
}
