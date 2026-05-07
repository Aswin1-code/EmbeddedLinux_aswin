#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd;

    struct flock lock;

    // Open file
    fd = open("sample.txt", O_RDWR | O_CREAT, 0666);

    // Initialize lock structure
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    printf("Applying write lock on file...\n");

    // Apply lock
    fcntl(fd, F_SETLK, &lock);

    printf("File locked successfully.\n");
    printf("Press Enter to unlock file...\n");
    getchar();

    // Unlock file
    lock.l_type = F_UNLCK;

    fcntl(fd, F_SETLK, &lock);

    printf("File unlocked successfully.\n");

    // Close file
    close(fd);

    return 0;
}