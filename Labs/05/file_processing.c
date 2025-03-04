#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

int main() {
    int fd;
    char buffer[BUFFER_SIZE];

    fd = open("input.txt", O_RDWR);
    if (fd == -1) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    ssize_t bytesRead = read(fd, buffer, BUFFER_SIZE - 1);
    if (bytesRead == -1) {
        perror("Error reading file");
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer[bytesRead] = '\0'; 
  
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        close(fd);
        exit(EXIT_FAILURE);
    } 
    else if (pid == 0) {
        const char *msg = "Processed by child process\n";
        lseek(fd, 0, SEEK_END); 
        write(fd, msg, sizeof(msg));
        close(fd);

        execlp("cat", "cat", "input.txt", NULL);
        perror("execlp failed"); 
        exit(EXIT_FAILURE);
    } 
    else { 
        wait(NULL);
        close(fd);
        printf("Parent process complete.\n");
    }

    return 0;
}
