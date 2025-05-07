#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        // Child process
        execlp("ls", "ls", "-l", (char *)NULL);
        // If execlp fails
        perror("Error: Failed to execute ls command");
        return 1;
    } 
    else if (pid > 0) {
        // Parent process
        wait(NULL);
        printf("Child process completed. Parent process terminating.\n");
    } 
    else {
        // Error in fork()
        perror("Error: Failed to create child process");
        return 1;
    }

    return 0;
}
