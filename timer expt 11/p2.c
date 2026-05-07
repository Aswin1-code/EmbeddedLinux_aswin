//realtime_signal.c

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void signal_handler(int sig)
{
    printf("Received Real Time Signal: %d\n", sig);
}

int main()
{
    signal(SIGRTMIN, signal_handler);

    printf("PID = %d\n", getpid());

    while(1)
    {
        pause();
    }

    return 0;
}