//nanosleep_demo.c

#include <stdio.h>
#include <time.h>

int main()
{
    struct timespec ts;

    ts.tv_sec = 1;
    ts.tv_nsec = 500000000;

    printf("Sleeping...\n");

    nanosleep(&ts, NULL);

    printf("Wakeup after 1.5 seconds\n");

    return 0;
}