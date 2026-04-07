// Write a System C Program using Shared Memory to transfer multiple data (probably could be array of data) from parent process to child process. 
#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<string.h>
#define MAX_MSG 5
#define MSG_LEN 100
#define SIZE (MAX_MSG * MSG_LEN)
int main() {
    int smid;
    key_t key;
    char (*memdata)[MSG_LEN];   // pointer to array of strings
    key = ftok("/home/iotits", 70);
    smid = shmget(key, SIZE, 0666 | IPC_CREAT);
    memdata = (char (*)[MSG_LEN]) shmat(smid, NULL, 0);
    pid_t pid = fork();
    if (pid == 0) {     // CHILD PROCESS
        sleep(2);   // wait for parent
        printf("\nI am child process\n");
        printf("Messages received from parent:\n");
        for(int i = 0; i < MAX_MSG; i++) {
            printf("Message %d: %s\n", i+1, memdata[i]);
        }
        shmdt(memdata);
    }
    else {              // PARENT PROCESS
        printf("\nI am parent process\n");
        strcpy(memdata[0], "Welcome to Shared Memory Demo");
        strcpy(memdata[1], "Message Passing using IPC");
        strcpy(memdata[2], "Parent sending multiple messages");
        strcpy(memdata[3], "Child reading messages");
        strcpy(memdata[4], "Shared Memory Communication Done");
        wait(NULL);
        shmdt(memdata);
        shmctl(smid, IPC_RMID, NULL);
        printf("\nShared memory removed from RAM\n");
    }
    return 0;
}

