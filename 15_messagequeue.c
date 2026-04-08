#include<stdio.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/wait.h>
#include<string.h>

struct msgbuf {//Fix size of shared memory
   long msgtype;
   char data[100];
 };
int main(){
  int mqid; //ID for message queue
  struct msgbuf message; //struct to store data to write/read from mem
  key_t key = ftok("/home/iotits/sta.c",65); //Generate key
  
  mqid = msgget(key, 0666 | IPC_CREAT); //Create msg queue identifer.
  pid_t pid = fork(); // create a child process
  if (pid == 0){
    sleep(2); // wait for parent to write to shared mem
    printf("\nI am child process:");
    
    msgrcv(mqid,&message, sizeof(message.data),1,0);
    printf("\nMessage received at child:%s\n", message.data);
    
    msgctl(mqid, IPC_RMID, NULL);
    printf("\n Message Queue identifer removed from RAM");
  }
  else{
    message.msgtype=1;
    printf("\nI am parent process:\n");
    strcpy(message.data, "Welcome to Messsage Queue Demo");
    
    msgsnd(mqid,&message, sizeof(message.data),0);
    printf("\nMessage sent from_parent:%s\n", message.data);
  }
  return 0;
}
