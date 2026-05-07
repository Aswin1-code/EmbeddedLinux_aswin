//barrier_demo.c

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_barrier_t barrier;

void* thread_func(void* arg)
{
    int id = *(int*)arg;

    printf("Thread %d before barrier\n", id);

    sleep(1);

    pthread_barrier_wait(&barrier);

    printf("Thread %d after barrier\n", id);

    return NULL;
}

int main()
{
    pthread_t t[3];
    int id[3] = {1,2,3};

    pthread_barrier_init(&barrier, NULL, 3);

    for(int i=0;i<3;i++)
    {
        pthread_create(&t[i], NULL, thread_func, &id[i]);
    }

    for(int i=0;i<3;i++)
    {
        pthread_join(t[i], NULL);
    }

    return 0;
}