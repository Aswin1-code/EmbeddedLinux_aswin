//Signal IPC Programming Demo on SIGUSR1 
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
void handler(int sig) { //Signal handler function
    if (sig == SIGUSR1) {  //checking signal type
        printf("Child (PID %d): Received SIGUSR1 from parent!\n", getpid());
        exit(0); // Terminate after handling
    }
}
int main() {
    pid_t pid;
    struct sigaction sa; //struct sigaction - is defined in signal.h
    pid = fork();
    if (pid == 0) {
        printf("Child (PID %d): Waiting for signal...\n", getpid());
        sa.sa_handler = handler; //Assigning Signal handler function
        //-----
        if (sigaction(SIGUSR1, &sa, NULL) == -1) { // sigaction -> register handler
            perror("sigaction");
            exit(1);
        }
        //-----
        while (1) {   // waiting for signal
            sleep(1);
        }
    } else {
        sleep(2); // Parent ensuring child is ready
        printf("Parent (PID %d): sending SIGUSR1 to child (PID %d)\n", getpid(), pid);
        kill(pid, SIGUSR1); //send signal to child
        wait(NULL); //Parent waiting for child to complete
        printf("Parent: Child finished, exiting.\n");
    }
    return 0;
}
