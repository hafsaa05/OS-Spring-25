//Named Pipes (FIFOs) (Bidirectional Communication)

//Producer Code
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_FILE "/tmp/myfifo"

int main() {
    int fd;
    char buffer[BUFSIZ];
    ssize_t num_bytes;

    // Create the named pipe (FIFO)
    if (mkfifo(FIFO_FILE, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // Open the named pipe for writing (producer)
    fd = open(FIFO_FILE, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (1) { // Producer loop
        printf("Producer: Enter a message (or 'exit' to quit): ");
        fgets(buffer, BUFSIZ, stdin);
        num_bytes = write(fd, buffer, strlen(buffer)); // Write input to the named pipe
        if (num_bytes == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        if (strncmp(buffer, "exit", 4) == 0) { // Check for exit condition
            break;
        }
    }

    //Consumer Code
    #include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FIFO_FILE "/tmp/myfifo"

int main() {
    int fd;
    char buffer[BUFSIZ];
    ssize_t num_bytes;

    // Open the named pipe for reading (consumer)
    fd = open(FIFO_FILE, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (1) {
        num_bytes = read(fd, buffer, BUFSIZ); // Read input from the named pipe
        if (num_bytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("Consumer: Received message: %s", buffer); // Display received message

        if (strncmp(buffer, "exit", 4) == 0) { // Check for exit condition
            break;
        }
    }

    close(fd); // Close the named pipe

    return 0;
}

    close(fd); // Close the named pipe
    unlink(FIFO_FILE); // Remove the named pipe from the filesystem

    return 0;
}
