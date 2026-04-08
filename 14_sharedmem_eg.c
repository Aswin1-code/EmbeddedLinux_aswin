#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>
#include<unistd.h>

#define SIZE 1024

int main(){
    key_t key;
    int shmid;
    char *data;

    // Generate key
    key = ftok("file.txt", 65);

    // Create shared memory
    shmid = shmget(key, SIZE, 0666 | IPC_CREAT);

    // Attach
    data = (char*) shmat(shmid, NULL, 0);

    printf("Writing to memory...\n");
    strcpy(data, "Hello from shared memory!");

    sleep(5);

    printf("Reading from memory: %s\n", data);

    // Detach
    shmdt(data);

    // Control (Delete)
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}