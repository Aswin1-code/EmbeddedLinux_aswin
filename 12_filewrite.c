//Writing Contents to a File using System Call
#include<fcntl.h> //File Control System call functions
#include<unistd.h>
int main(){
     int fd; //File discriptor
     char buf[50]="File handling using system calls\n";
     fd = open("myfile.txt", O_CREAT | O_RDWR);
     write(fd,buf,50);
     close(fd);
     return 0;
}
