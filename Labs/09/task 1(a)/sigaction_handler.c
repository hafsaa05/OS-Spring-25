#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler function for SIGINT
void sigint_handler(int signum) {
    printf("Ctrl+C (SIGINT) received. Exiting...\n");
    exit(signum);  // Exit after receiving SIGINT
}

int main() {
    // Set up the signal action structure
    struct sigaction sa;
    sa.sa_handler = sigint_handler; // Specify the signal handler function
    sigemptyset(&sa.sa_mask);       // Clear the signal mask (no signals are blocked)
    sa.sa_flags = SA_RESTART;      // Set SA_RESTART flag to automatically restart system calls

    // Register the signal handler for SIGINT using sigaction
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    // Loop indefinitely to keep the program running
    printf("Waiting for Ctrl+C (SIGINT)...\n");

    while (1) {
        // Do some work or wait for input
        sleep(1);  // Simulate work by sleeping
    }

    return EXIT_SUCCESS;
}
