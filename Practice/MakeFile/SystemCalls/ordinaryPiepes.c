// Ordinary Pipes (Unidirectional Communication)
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void) {
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[BUFFER_SIZE];
    int fd[2]; // file descriptors for the pipe
    pid_t pid;

    // Create a pipe
    if (pipe(fd) == -1) {
        fprintf(stderr, "Pipe failed\n");
        return 1;
    }

    pid = fork(); // Fork a new process
    if (pid < 0) { // Fork failed
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }

    if (pid > 0) { // Parent process
        close(fd[READ_END]); // Close the read end
        write(fd[WRITE_END], write_msg, strlen(write_msg) + 1); // Write message to the pipe
        close(fd[WRITE_END]); // Close the write end
    } else { // Child process
        close(fd[WRITE_END]); // Close the write end
        read(fd[READ_END], read_msg, BUFFER_SIZE); // Read from the pipe
        printf("Read: %s\n", read_msg); // Print the received message
        close(fd[READ_END]); // Close the read end
    }

    return 0;
}
