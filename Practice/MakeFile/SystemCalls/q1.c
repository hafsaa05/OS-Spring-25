#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child1, child2;

    child1 = fork();
    if (child1 == 0) {
        // First child process
        printf("First Child: My PID is %d\n", getpid());
        return 0;
    } 
    else if (child1 > 0) {
        // Parent process creates second child
        child2 = fork();
        if (child2 == 0) {
            // Second child process
            printf("Second Child: My Parent PID is %d\n", getppid());
            return 0;
        } 
        else if (child2 > 0) {
            // Parent process waits for both children
            wait(NULL); // wait for one child
            wait(NULL); // wait for second child
            printf("Parent: Both children have terminated.\n");
        } 
        else {
            // Failed to create second child
            fprintf(stderr, "Error: Failed to create second child process.\n");
        }
    } 
    else {
        // Failed to create first child
        fprintf(stderr, "Error: Failed to create first child process.\n");
    }

    return 0;
}
