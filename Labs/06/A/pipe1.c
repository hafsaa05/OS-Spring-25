#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {
    char write_msg[BUFFER_SIZE];
    char read_msg[BUFFER_SIZE];
    int fd[2];
    pid_t pid;

    if (pipe(fd) == -1) { // create a pipe
        fprintf(stderr, "Pipe failed\n");
        return 1;
    }

    printf("Enter a message: ");
    fgets(write_msg, BUFFER_SIZE, stdin);
    
    // Remove newline character if present
    write_msg[strcspn(write_msg, "\n")] = 0;

    pid = fork();

    if (pid < 0) { // error occurred
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }

    if (pid > 0) { /* parent process */
        close(fd[READ_END]);
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
        close(fd[WRITE_END]);
    } else { /* child process */
        close(fd[WRITE_END]); // close the unused end of the pipe
        read(fd[READ_END], read_msg, BUFFER_SIZE); // read from the pipe
        printf("Received message: %s\n", read_msg);
        close(fd[READ_END]); // close the read end of the pipe
    }

    return 0;
}
