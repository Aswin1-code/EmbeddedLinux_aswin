#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <aio.h>
#include <string.h>

int main()
{
    int fd;
    struct aiocb cb;
    char writebuf[] = "Hello Async IO in Linux";
    char readbuf[100];

    // Open file
    fd = open("async.txt", O_RDWR | O_CREAT, 0666);

    // Initialize aiocb structure for write
    memset(&cb, 0, sizeof(struct aiocb));

    cb.aio_fildes = fd;
    cb.aio_buf = writebuf;
    cb.aio_nbytes = strlen(writebuf);
    cb.aio_offset = 0;

    printf("Starting asynchronous write...\n");

    // Start asynchronous write
    aio_write(&cb);

    // Wait until write completes
    while(aio_error(&cb) == EINPROGRESS);

    printf("Asynchronous write completed\n");

    // Prepare for asynchronous read
    memset(readbuf, 0, sizeof(readbuf));

    cb.aio_buf = readbuf;
    cb.aio_nbytes = sizeof(readbuf);
    cb.aio_offset = 0;

    printf("Starting asynchronous read...\n");

    // Start asynchronous read
    aio_read(&cb);

    // Wait until read completes
    while(aio_error(&cb) == EINPROGRESS);

    printf("Asynchronous read completed\n");

    // Display content
    printf("Data Read: %s\n", readbuf);

    close(fd);

    return 0;
}