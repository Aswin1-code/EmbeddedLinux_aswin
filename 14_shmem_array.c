#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/shm.h>
#include<sys/ipc.h>
#include<string.h>

#define NUM_STRINGS 3
#define STR_SIZE 100

int main() {
    int shmid;
    key_t key = ftok("/home/iotits/sta.c", 65); // Make sure this file exists
    if (key == -1) {
        perror("ftok");
        return 1;
    }

    // Allocate shared memory for NUM_STRINGS strings of STR_SIZE each
    shmid = shmget(key, NUM_STRINGS * STR_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        return 1;
    }

    char (*memdata)[STR_SIZE];
    memdata = (char(*)[STR_SIZE])shmat(shmid, NULL, 0);
    if (memdata == (void*)-1) {
        perror("shmat");
        return 1;
    }

    pid_t pid = fork();

    if (pid == 0) {
        // Child process: read and print the strings
        sleep(2); // Wait for parent to write
        printf("Child: Reading strings from shared memory:\n");
        for (int i = 0; i < NUM_STRINGS; i++) {
            printf("%d: %s\n", i, memdata[i]);
        }
        shmdt(memdata);
    } else {
        // Parent process: write the strings
        strcpy(memdata[0], "Welcome to Shared Memory Demo");
        strcpy(memdata[1], "Interprocess Communication");
        strcpy(memdata[2], "Embedded Linux");
        printf("Parent: Strings written to shared memory.\n");
        wait(NULL); // Wait for child to finish
        shmdt(memdata);
        shmctl(shmid, IPC_RMID, NULL); // Remove shared memory
        printf("Parent: Shared memory removed.\n");
    }
}