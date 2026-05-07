//interval_timer.c

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void timer_handler(int sig)
{
    printf("Timer Expired!\n");
}

int main()
{
    struct itimerval timer;

    signal(SIGALRM, timer_handler);

    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;

    timer.it_interval.tv_sec = 2;
    timer.it_interval.tv_usec = 0;

    setitimer(ITIMER_REAL, &timer, NULL);

    while(1)
    {
        pause();
    }

    return 0;
}