#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/wait.h>
#include <unistd.h>

#define NUM_MSGS 3
#define MSG_SIZE 100

struct msgbuf {
    long msgtype;
    char data[MSG_SIZE];
};

int main() {
    key_t key = ftok("/home/iotits/sta.c", 65); // Make sure this file exists
    int mqid = msgget(key, 0666 | IPC_CREAT);

    struct msgbuf message;
    pid_t pid = fork();

    if (pid == 0) {
        // Child process: receive and print all messages
        sleep(2);
        for (int i = 0; i < NUM_MSGS; i++) {
            if (i%2!=0){
            msgrcv(mqid, &message, sizeof(message.data), 1, 0);
            printf("Child1 received: %s\n", message.data);
        }
        else{
            msgrcv(mqid, &message, sizeof(message.data), 2, 0);
            printf("Child2 received: %s\n", message.data);
        }
    }
        // Remove the message queue
        msgctl(mqid, IPC_RMID, NULL);
    } else {
        // Parent process: send multiple messages
        char *messages[NUM_MSGS] = {
            "Hello from parent - message 1",
            "Hello from parent - message 2",
            "Hello from parent - message 3"
        };
        for (int i = 0; i < NUM_MSGS; i++) {
            message.msgtype = 1;
            strncpy(message.data, messages[i],MSG_SIZE);
            msgsnd(mqid, &message, sizeof(message.data), 0);
            printf("Parent sent: %s\n", message.data);
        }
        for (int i = 0; i < NUM_MSGS; i++) {
            message.msgtype = 2;
            strncpy(message.data, messages[i], MSG_SIZE);
            msgsnd(mqid, &message, sizeof(message.data), 0);
            printf("Parent sent: %s\n", message.data);
        }

       wait(NULL); // Wait for child to finish
    }
    return 0;
}