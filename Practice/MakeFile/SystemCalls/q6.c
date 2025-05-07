#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void handleAlarm(int sig) {
    printf("\nAlarm received. Terminating program.\n");
    exit(0);
}

int main() {
    // Set up the signal handler for SIGALRM
    signal(SIGALRM, handleAlarm);
    
    // Set an alarm to trigger in 5 seconds
    alarm(5);

    // Main loop: print message every second
    while (1) {
        printf("Sleeping for 1 second...\n");
        sleep(1);
    }

    return 0;
}
