#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
void handler(int sig) { //Signal handler function
    printf("\nCaught signal %d (SIGINT). Exiting the process...\n", sig);
    exit(0);
}
int main() {
    signal(SIGINT, handler); //Handler registration for SIGINT
    printf("Press Ctrl+C to send signal IPC\n");
    while (1) { //Write your process action here and wait for signal
        sleep(1);
    }
    return 0;
}

