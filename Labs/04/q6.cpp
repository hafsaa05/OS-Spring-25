#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;

void handleAlarm(int sig) {
    cout << "\nAlarm received. Terminating program." << endl;
    exit(0);
}

int main() {
    signal(SIGALRM, handleAlarm);
    alarm(5);

    while (true) {
        cout << "Sleeping for 1 second..." << endl;
        sleep(1);
    }
    return 0;
}
