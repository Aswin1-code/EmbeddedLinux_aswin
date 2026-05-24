//read_write_lock.c

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t lock;

int shared_data = 0;

void* reader(void* arg)
{
    pthread_rwlock_rdlock(&lock);

    printf("Reader: %d\n", shared_data);

    pthread_rwlock_unlock(&lock);

    return NULL;
}

void* writer(void* arg)
{
    pthread_rwlock_wrlock(&lock);

    shared_data++;

    printf("Writer updated data\n");

    pthread_rwlock_unlock(&lock);

    return NULL;
}

int main()
{
    pthread_t r1, r2, w1;

    pthread_rwlock_init(&lock, NULL);

    pthread_create(&w1, NULL, writer, NULL);
    pthread_create(&r1, NULL, reader, NULL);
    pthread_create(&r2, NULL, reader, NULL);

    pthread_join(w1, NULL);
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);

    return 0;
}