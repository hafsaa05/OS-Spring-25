#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signum) {
    printf("Caught SIGINT (Ctrl+C): %d\n", signum);
    fflush(stdout);
    raise(SIGKILL);  // Force kill the process
}

void my_handler(int signum) {
    printf("Caught custom user signal SIGUSR1: %d\n", signum);
    fflush(stdout);
}

int main() {
    pid_t pid = getpid();
    printf("Program running. PID = %d\n", pid);

    // Register signal handlers
    signal(SIGINT, sigint_handler);      // Handle Ctrl+C
    signal(SIGUSR1, my_handler);         // Handle custom user signal

    // Wait a bit then send SIGUSR1 to self
    sleep(3);                            // Wait 3 seconds
    printf("Raising SIGUSR1 for myself...\n");
    kill(pid, SIGUSR1);                  // Send SIGUSR1 to self

    // Keep the program alive to test Ctrl+C too
    while (1) {
        usleep(500000);  // 0.5 seconds
    }

    return 0;
}
