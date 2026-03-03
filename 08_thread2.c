#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *Thread1(void*){
  printf("\nI am in a Thread 1:%lu", pthread_self());
  pthread_exit(NULL);
}
int main(){
  pthread_t t1;
  printf("\nMain Process ID %d:",getpid());
  printf("\nMain Thread ID %lu:",pthread_self());
  pthread_create(&t1,NULL, Thread1, NULL);
  pthread_join(t1,NULL);
  pthread_exit(NULL);
  return 0;
}
