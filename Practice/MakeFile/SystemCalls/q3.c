#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

void printUserID() {
    uid_t uid = getuid();
    printf("User ID (UID) of the current user: %d\n", uid);
}

int main() {
    printf("Current Process ID (PID): %d\n", getpid());
    printf("Parent Process ID (PPID): %d\n", getppid());
    printUserID();
    return 0;
}
