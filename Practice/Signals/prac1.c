#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signum) {
    fprintf(stdout, "Caught SIGINT signal %d\n", signum); // Added newline
    fflush(stdout); // Ensure the output is printed immediately
    exit(0);  // Cleanly terminate
    raise(SIGKILL);  // Force kill this process
}

void my_handler(int signum) {
    printf("Caught custom user signal SIGUSR1: %d\n", signum);
    fflush(stdout);
}

int main() {
    signal(SIGINT, sigint_handler);      // Ctrl+C handler
    printf("Press ctrl+c to activate signal...\n");

    // Keep the program running
    while (1) {
        usleep(500000); // 0.5 seconds = 500,000 microseconds
    }

    return 0;
}
