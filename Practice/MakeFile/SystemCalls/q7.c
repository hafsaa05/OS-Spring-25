#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (execlp("ls", "ls", (char *)NULL) == -1) {
            perror("Error: Failed to execute ls command");
            return 1;
        }
    } 
    else if (pid > 0) {
        // Parent process
        wait(NULL);
        printf("Child process completed. Parent process terminating.\n");
    } 
    else {
        // Error in fork()
        perror("Error: Failed to create child process");
    }

    return 0;
}
