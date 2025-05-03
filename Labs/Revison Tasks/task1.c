#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

FILE *tempFile;

void handle_sigint(int sig) {
    if (tempFile) {
        fclose(tempFile);
        remove("tempfile.txt");
        printf("\nSIGINT received. Temporary file closed and deleted. Exiting.\n");
    }
    exit(0);
}

int main() {
    signal(SIGINT, handle_sigint);

    tempFile = fopen("tempfile.txt", "w+");
    if (!tempFile) {
        perror("Unable to create file");
        return 1;
    }

    int counter = 1;
    while (1) {
        fprintf(tempFile, "Line %d written.\n", counter++);
        fflush(tempFile);
        printf("Wrote line %d\n", counter - 1);
        sleep(1);
    }

    return 0;
}
