//a parent process creates a shared memory segment and a pipe . the child writes a msg to shared memory and sends a signal string "done" through the pipe . The parent writes to receive "done" from the pipe before reading shared memory. 1.Implement using fork and pipe system calls with proper error handling. 2.What will happen if the pipe read is done before the child writes to shared memory ? 3. Modify logic so that 2 children write sequentially to shared memory, and the parent reads both msgs correctly. 4.Fix potential synchronisation issues w/o using semaphores

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>

#define SIZE 4096

int main() {
    int pipefd[2];
    char buffer[10];

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    // Create shared memory
    char *shm = mmap(NULL, SIZE, PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shm == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child Process
        close(pipefd[0]); // Close read end

        const char *msg = "Hello from Child";
        strcpy(shm, msg); // Write to shared memory

        write(pipefd[1], "done", 4); // Notify parent
        close(pipefd[1]);
        exit(0);
    } else {
        // Parent Process
        close(pipefd[1]); // Close write end

        read(pipefd[0], buffer, sizeof(buffer)); // Wait for signal
        printf("Parent received: %s\n", buffer);
        printf("Parent reads from shared memory: %s\n", shm);

        close(pipefd[0]);
        wait(NULL); // Wait for child to finish
    }

    return 0;
}
//Code: Two Children, Sequential Writes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>

#define SIZE 4096

int main() {
    int pipefd[2];
    char buffer[10];

    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        exit(1);
    }

    // Create shared memory
    char *shm = mmap(NULL, SIZE, PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    if (shm == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    pid_t pid1 = fork();
    if (pid1 < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid1 == 0) {
        // First child
        close(pipefd[0]);
        const char *msg1 = "Msg from Child 1\n";
        strcpy(shm, msg1);
        write(pipefd[1], "done1", 5);
        close(pipefd[1]);
        exit(0);
    }

    wait(NULL); // Ensure child 1 is done

    pid_t pid2 = fork();
    if (pid2 < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid2 == 0) {
        // Second child
        close(pipefd[0]);
        strcat(shm, "Msg from Child 2\n");
        write(pipefd[1], "done2", 5);
        close(pipefd[1]);
        exit(0);
    }

    // Parent
    close(pipefd[1]);
    for (int i = 0; i < 2; ++i) {
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
    }

    printf("Parent reads shared memory:\n%s", shm);
    close(pipefd[0]);
    wait(NULL);

    return 0;
}
