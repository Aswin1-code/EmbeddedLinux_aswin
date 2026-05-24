//getrusage_demo.c

#include <stdio.h>
#include <sys/resource.h>

int main()
{
    struct rusage usage;

    for(long int i = 0; i < 100000000; i++);

    getrusage(RUSAGE_SELF, &usage);

    printf("User CPU Time: %ld sec\n",
            usage.ru_utime.tv_sec);

    printf("System CPU Time: %ld sec\n",
            usage.ru_stime.tv_sec);

    printf("Max Memory Usage: %ld KB\n",
            usage.ru_maxrss);

    return 0;
}