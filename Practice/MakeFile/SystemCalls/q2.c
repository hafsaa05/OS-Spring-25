#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        // Child process
        for (int i = 0; i < 100; i++) {
            printf("I am a child process\n");
        }
    } 
    else if (pid > 0) {
        // Parent process
        for (int i = 0; i < 100; i++) {
            printf("I am a parent process\n");
        }
    } 
    else {
        // Fork failed
        printf("Failed to create child process.\n");
    }

    return 0;
}
