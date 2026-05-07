//time_process.c

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sched.h>
#include <sys/time.h>

int main()
{
    struct timespec start, end;
    cpu_set_t set;

    // Start time
    clock_gettime(CLOCK_MONOTONIC, &start);

    // Set CPU affinity to CPU 0
    CPU_ZERO(&set);
    CPU_SET(0, &set);

    sched_setaffinity(0, sizeof(set), &set);

    // Set process priority
    struct sched_param param;
    param.sched_priority = 10;

    sched_setscheduler(0, SCHED_FIFO, &param);

    // Dummy task
    for(long int i = 0; i < 1000000000; i++);

    // End time
    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_taken;

    time_taken =
        (end.tv_sec - start.tv_sec) +
        (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Execution Time = %f seconds\n", time_taken);

    return 0;
}