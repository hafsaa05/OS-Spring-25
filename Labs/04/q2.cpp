#include <iostream>
#include <unistd.h>
using namespace std;

int main() {
    pid_t pid;

    pid = fork();
    if (pid == 0) {
        for (int i = 0; i < 100; i++) {
            cout << "I am a child process" << endl;
        }
    } 
    else if (pid > 0) {
        for (int i = 0; i < 100; i++) {
            cout << "I am a parent process" << endl;
        }
    } 
    else {
        cout << "Failed to create child process." << endl;
    }
    return 0;
}
