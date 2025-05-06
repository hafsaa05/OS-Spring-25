#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>

void proc_exit(int signum) {
    pid_t pid;
    int status;

    // Reap all terminated children
    while ((pid = waitpid(-1, &status, WNOHANG)) > 0) {
        printf("Child process with PID %d terminated\n", pid);
    }
}

int main() {
    signal(SIGCHLD, proc_exit);  // Register SIGCHLD handler

    for (int i = 0; i < 3; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            printf("Child %d (PID %d) is running\n", i + 1, getpid());
            exit(100 + i);  // Exit with a different code for each child
        } else if (pid < 0) {
            perror("fork failed");
        }
    }

    // Parent process sleeps while children terminate
    sleep(5);  // This delay allows all child processes to terminate first (become zombies)

    printf("Parent finished sleeping. Exiting now.\n");
    return 0;
}
