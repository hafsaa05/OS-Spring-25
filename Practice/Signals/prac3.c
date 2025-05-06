#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <unistd.h>

// Signal handler for SIGCHLD
void proc_exit(int signum) {
    int wstat;
    pid_t pid;

    while ((pid = wait3(&wstat, WNOHANG, NULL)) > 0) {
        fprintf(stdout, "Child with PID %d exited.\n", pid);
        fprintf(stdout, "Return code: %d\n", WEXITSTATUS(wstat));
    }
}

int main() {
    // Register the SIGCHLD handler
    signal(SIGCHLD, proc_exit);

    // Create child process
    switch (fork()) {
        case -1:
            perror("main: fork");
            exit(1);

        case 0: // Child process
            printf("I'm alive (temporarily)\n");
            int ret_code = rand() % 256;  // limit to valid exit codes
            printf("Return code is %d\n", ret_code);
            exit(ret_code);

        default: // Parent process
            pause();  // Wait for SIGCHLD
            exit(0);
    }
}
