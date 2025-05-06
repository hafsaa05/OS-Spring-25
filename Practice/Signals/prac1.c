#include<stdio.h>
#include<signal.h>
#include<unistd.h>

void signal_handler(int signum){
    fprintf(stdout, "Caught SIGINT signal %d", signum);
}

int main(){
    signal(SIGINT, signal_handler);
    printf("Press ctrl+c to activate signal..");

    //to keep the program running
    while(1){
        sleep(0.5);
    }
    return 0;
}
