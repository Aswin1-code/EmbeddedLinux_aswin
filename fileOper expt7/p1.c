#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() 
{
    int fd1, fd2;
    char buffer[100];
    int bytesRead;

    // Open input file in read-only mode
    fd1 = open("input.txt", O_RDONLY);

    // Create output file in write mode
    fd2 = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

    // Read data from input file
    bytesRead = read(fd1, buffer, sizeof(buffer));

    // Write data to output file
    write(fd2, buffer, bytesRead);

    // Close both files
    close(fd1);
    close(fd2);

    printf("Data copied successfully.\n");

    return 0;
}