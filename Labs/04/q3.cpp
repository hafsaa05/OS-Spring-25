#include <iostream>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

void printUserID() {
    uid_t uid = getuid();
    cout << "User ID (UID) of the current user: " << uid << endl;
}

int main() {
    cout << "Current Process ID (PID): " << getpid() << endl;
    cout << "Parent Process ID (PPID): " << getppid() << endl;
    printUserID();
    return 0;
}
