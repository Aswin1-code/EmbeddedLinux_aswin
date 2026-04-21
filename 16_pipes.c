#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main(){
      int p[2];
      char wrtmsg[100];
      char readmsg[100];
      pipe(p); //Create a pipe (p[0] - read, p[1] - write)
      pid_t pid = fork();
      if(pid == 0){
             //sleep(1);
             close(p[1]); //close write
             read(p[0], readmsg, sizeof(readmsg)); //child perform read
             printf("\nChild read from pipe:%s\n",readmsg);
             close(p[0]); //close read
      }
      else{
            close(p[0]); //close write
            strcpy(wrtmsg, "Welcome to Pipes");
            write(p[1],wrtmsg,sizeof(wrtmsg)); //parent perform write
            printf("\nParent written to pipe:%s\n", wrtmsg);
            close(p[1]); //close write
          }
    return 0;
 }
6