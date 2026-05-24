//recursive_mutex.c

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

void recursive_function(int n)
{
    if(n == 0)
        return;

    pthread_mutex_lock(&mutex);

    printf("Locked %d\n", n);

    recursive_function(n - 1);

    pthread_mutex_unlock(&mutex);

    printf("Unlocked %d\n", n);
}

int main()
{
    pthread_mutexattr_t attr;

    pthread_mutexattr_init(&attr);

    pthread_mutexattr_settype(&attr,
                              PTHREAD_MUTEX_RECURSIVE);

    pthread_mutex_init(&mutex, &attr);

    recursive_function(3);

    return 0;
}