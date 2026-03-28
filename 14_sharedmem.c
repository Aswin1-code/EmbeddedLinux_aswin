#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/wait.h>
#include<string.h>

#define SIZE 1024 //Fix size of shared memory

int main(){
  int smid; //ID for shared memory
  char *memdata; //string to store data to write/read from mem
  key_t key = ftok("/home/iotits/sta.c",65); //Generate key
  smid = shmget(key, SIZE, 0666 | IPC_CREAT); //Create Shared mem.
  memdata = (char*)shmat(smid,NULL,0); //Attach mem to process
  pid_t pid = fork(); // create a child process
  if (pid == 0){
    sleep(2); // wait for parent to write to shared mem
    printf("\nI am child process:");
    printf("\nMessage from parent:%s", memdata);
    shmdt(memdata);
  }
  else{
    printf("\nI am parent process:\n");
    strcpy(memdata, "Welcome to Shared Memory Demo");
    wait(NULL); //Intimate child that parent completed
    shmdt(memdata);
    shmctl(smid, IPC_RMID, NULL);
    printf("\nShared memory removed from RAM");
  }
  return 0;
}
