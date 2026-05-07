#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main()
{
    int fd;
    char buffer[100];

    // Open file with specific permissions
    fd = open("sample.txt", O_RDWR | O_CREAT, 0644);

    // Write data into file
    write(fd, "Hello Linux System Programming", 30);

    // Move file pointer to beginning
    lseek(fd, 0, SEEK_SET);

    // Read data from file
    read(fd, buffer, sizeof(buffer));

    // Display file content
    printf("File Content: %s\n", buffer);

    // Change file permissions
    chmod("sample.txt", 0777);

    printf("File permissions changed successfully\n");

    // Close file
    close(fd);

    return 0;
}