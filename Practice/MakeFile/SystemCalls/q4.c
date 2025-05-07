#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
using namespace std;

int main() {
    int inputFile, outputFile;
    char buffer[1024];
    ssize_t bytesRead;

    inputFile = open("input.txt", O_RDONLY);
    if (inputFile < 0) {
        cerr << "Error: Failed to open input.txt" << endl;
        return 1;
    }

    outputFile = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outputFile < 0) {
        cerr << "Error: Failed to open output.txt" << endl;
        close(inputFile);
        return 1;
    }

    while ((bytesRead = read(inputFile, buffer, sizeof(buffer))) > 0) {
        if (write(outputFile, buffer, bytesRead) != bytesRead) {
            cerr << "Error: Failed to write to output.txt" << endl;
            close(inputFile);
            close(outputFile);
            return 1;
        }
    }

    if (bytesRead < 0) {
        cerr << "Error: Failed to read from input.txt" << endl;
    }

    close(inputFile);
    close(outputFile);

    cout << "Content copied from input.txt to output.txt successfully." << endl;
    return 0;
}
