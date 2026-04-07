//Pipes IPC Programming Demo (Multiple messages)
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main() {
    int p[2];
    pid_t pid;
    char *msg[] = {
        "Hello Child!",
        "This is IPC using Pipes.",
        "Sending multiple sentences.",
        "System Programming Demo.",
        "Goodbye!"
    };
    char buffer[100];
    int n = 5;   // number of msg
    pipe(p);
    pid = fork();
    if (pid < 0) {
        printf("Fork failed\n");
        return 1;
    }
    if (pid == 0) {
        close(p[1]);   // Close write end
        printf("Child receiving msg:\n");
        for(int i = 0; i < n; i++) {
            read(p[0], buffer, sizeof(buffer));
            printf("Received: %s\n", buffer);
        }
        close(p[0]);
    }
    else {
        close(p[0]);   // Close read end
        printf("Parent sending msg:\n");
        for(int i = 0; i < n; i++) {
            write(p[1], msg[i], strlen(msg[i]) + 1);
            printf("Sent: %s\n", msg[i]);
            sleep(1);   // just for clear output order
        }
        close(p[1]);
    }
    return 0;
}

