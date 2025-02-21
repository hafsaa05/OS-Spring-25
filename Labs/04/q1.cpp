#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main() {
    pid_t child1, child2;

    child1 = fork();
    if (child1 == 0) {
        cout << "First Child: My PID is " << getpid() << endl;
        return 0;
    } 
    else if (child1 > 0) {
        child2 = fork();
        if (child2 == 0) {
            cout << "Second Child: My Parent PID is " << getppid() << endl;
            return 0;
        }
        else if (child2 > 0) {
            wait(NULL);
            wait(NULL);
            cout << "Parent: Both children have terminated." << endl;
        }
        else {
            cerr << "Error: Failed to create second child process." << endl;
        }
    } 
    else {
        cerr << "Error: Failed to create first child process." << endl;
    }
    return 0;
}
