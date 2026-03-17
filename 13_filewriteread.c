//Writing and Reading from a file using System Calls
#include<stdio.h>
#include<fcntl.h> //File Control System call functions
#include<unistd.h>
int main(){
     int fd; //File discriptor
     char buf[50];
     fd = open("myfile.txt", O_CREAT | O_RDWR);
     write(fd,"Welcome of File handling Emb. Linux",36);
     lseek(fd, 0, SEEK_SET);
     read(fd,buf,36);
     printf("\nFile Contents:%s",buf);
     close(fd);
     return 0;
}
