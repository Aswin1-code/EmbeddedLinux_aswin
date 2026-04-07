//Signal IPC Programming Demo on SIGUSR1 
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
void handler(int sig) { //Signal handler function
    if (sig == SIGUSR1) {
        printf("Child (PID %d): Received SIGUSR1 from parent!\n", getpid());
        exit(0); // Terminate after handling
    }
}
int main() {
    pid_t pid;
    struct sigaction sa;
    pid = fork();
    if (pid == 0) {
        printf("Child (PID %d): Waiting for signal...\n", getpid());
        sa.sa_handler = handler; //Assign Signal handler function to action
        if (sigaction(SIGUSR1, &sa, NULL) == -1) {
            perror("sigaction");
            exit(1);
        }
        while (1) {
            sleep(1);
        }
    } else {
        sleep(2); // Parent ensuring child is ready
        printf("Parent (PID %d): sending SIGUSR1 to child (PID %d)\n", getpid(), pid);
        kill(pid, SIGUSR1);
        wait(NULL); //Parent waiting for child to complete
        printf("Parent: Child finished, exiting.\n");
    }
    return 0;
}
