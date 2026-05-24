#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>

int main()
{
    int fd;
    char *mapped_memory;
    // Open file
    fd = open("mmapfile.txt", O_RDWR | O_CREAT, 0666);
    // Set file size
    ftruncate(fd, 100);

    // Map file into memory
    mapped_memory = mmap(
                        NULL,
                        100,
                        PROT_READ | PROT_WRITE,
                        MAP_SHARED,
                        fd,
                        0
                        );

    // Write data to mapped memory
    strcpy(mapped_memory, "Hello Memory Mapped IO");

    printf("Written Data: %s\n", mapped_memory);

    // Synchronize memory with file
    msync(mapped_memory, 100, MS_SYNC);

    printf("Data synchronized to file\n");

    // Unmap memory
    munmap(mapped_memory, 100);

    // Close file
    close(fd);

    return 0;
}