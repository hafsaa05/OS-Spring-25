#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        execlp("ls", "ls", (char *)NULL);
        cerr << "Error: Failed to execute ls command." << endl;
        return 1;
    } 
    else if (pid > 0) {
        wait(NULL);
        cout << "Child process completed. Parent process terminating." << endl;
    } 
    else {
        cerr << "Error: Failed to create child process." << endl;
    }
    return 0;
}

