#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t child1, child2;

    child1 = fork();
    if (child1 == 0) {
        printf("First Child: My PID is %d\n", getpid());
        return 0;
    } 
    else if (child1 > 0) {
        child2 = fork();
        if (child2 == 0) {
            printf("Second Child: My Parent PID is %d\n", getppid());
            return 0;
        }
        else if (child2 > 0) {
            wait(NULL);
            wait(NULL);
            printf("Parent: Both children have terminated.\n");
        }
        else {
            printf("Failed to create second child process.\n");
        }
    } 
    else {
        printf("Failed to create first child process.\n");
    }
    return 0;
}
