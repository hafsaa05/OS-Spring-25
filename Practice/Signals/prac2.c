#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void my_handler(int signum) {
    fprintf(stdout, "Caught custom signal %d\n", signum); // Added newline
    fflush(stdout); // Ensure the output is printed immediately
}

int main() {
    pid_t pid;
    printf("Program running. PID : %d\n", pid);

    signal(SIGUSR1, my_handler);

    // Wait a bit then send SIGUSR1 to self
    sleep(2);                            // Wait 2 seconds
    printf("Raising SIGUSR1 for myself...\n");
    kill(pid, SIGUSR1);                  // Send SIGUSR1 to self

    return 0;
}
