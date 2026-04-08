include<stdio.h>
#include<unistd.h>
#include<pthread.h>

void *Thread1(void*){
  int i;
  printf("\nI am in a Thread 1:%lu", pthread_self());
  for(i = 1; i <= 10; i++){
        printf("\nThread 1 printing:%d",i);
        sleep(1);
  }
  pthread_exit(NULL);
}
int main(){
  pthread_t t1;
  int i;
  printf("\nMain Process ID %d:",getpid());
  printf("\nMain Thread ID %lu:",pthread_self());
  pthread_create(&t1,NULL, Thread1, NULL);
  for(i=100; i<=1000; i=i+100){
        printf("\nMain Thread printing:%d",i);
        sleep(2);
  }
  pthread_join(t1,NULL);

  pthread_exit(NULL);
  return 0;
}
