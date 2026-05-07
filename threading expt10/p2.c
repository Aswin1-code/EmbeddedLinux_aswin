//condition_variable.c

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond;

int data_ready = 0;

void* producer(void* arg)
{
    sleep(2);

    pthread_mutex_lock(&mutex);

    data_ready = 1;

    printf("Producer: Data Ready\n");

    pthread_cond_signal(&cond);

    pthread_mutex_unlock(&mutex);

    return NULL;
}

void* consumer(void* arg)
{
    pthread_mutex_lock(&mutex);

    while(data_ready == 0)
    {
        pthread_cond_wait(&cond, &mutex);
    }

    printf("Consumer: Data Consumed\n");

    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, consumer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}