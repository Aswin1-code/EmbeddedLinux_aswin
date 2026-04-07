//Write a System C Program using Message Queues to transfer multiple data (probably could be array of data) from parent process to child process. 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
struct message {
    long msg_type;
    char msg_text[100];
};
int main() {
    int msgid;
    struct message msg;
    key_t key = ftok("msgqueuefile", 65);
    msgid = msgget(key, 0666 | IPC_CREAT);
    pid_t pid = fork();
    if (pid == 0) {
         sleep(2);
         while(1) {
            msgrcv(msgid, &msg, sizeof(msg.msg_text), 1, 0);
            printf("Child Received: %s\n", msg.msg_text);
            if(strcmp(msg.msg_text, "END") == 0)
                break;
        }
    }
    else {
        char *messages[] = {
            "Message 1: Hello",
            "Message 2: Linux IPC",
            "Message 3: Message Queue Demo",
            "END"
        };
        sleep(1); // ensure child waits first
        for(int i = 0; i < 4; i++) {
            msg.msg_type = 1;
            strcpy(msg.msg_text, messages[i]);
            msgsnd(msgid, &msg, sizeof(msg.msg_text), 0);
            printf("Parent Sent: %s\n", msg.msg_text);
            sleep(1);
        }
    }
        msgctl(msgid, IPC_RMID, NULL);
        printf("Message Queue Removed\n");
    return 0;
}

