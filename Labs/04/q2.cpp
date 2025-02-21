#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        for (int i = 0; i < 100; i++) {
            printf("I am a child process\n");
        }
    } 
    else if (pid > 0) {
        for (int i = 0; i < 100; i++) {
            printf("I am a parent process\n");
        }
    } 
    else {
        printf("Failed to create child process.\n");
    }
    return 0;
}
