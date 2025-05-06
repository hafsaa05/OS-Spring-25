#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int signum) {
    fprintf(stdout, "Caught SIGINT signal %d\n", signum); // Added newline
    fflush(stdout); // Ensure the output is printed immediately
}

int main() {
    signal(SIGINT, signal_handler);
    printf("Press ctrl+c to activate signal...\n");

    // Keep the program running
    while (1) {
        usleep(500000); // 0.5 seconds = 500,000 microseconds
    }

    return 0;
}
