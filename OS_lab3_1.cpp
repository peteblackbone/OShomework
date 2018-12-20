#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

int x = 0;
sem_t sync;
void *myfunc(void *arg){
	sem_wait(&sync);
	printf("X = %d\n",x);
}
int main (){
	pthread_t thread;
	if(sem_init(&sync,0,0) == -1) {
		perror("Could not initialize mylock semaphore");
	}
	if(pthread_create(&thread,NULL,myfunc,NULL) < 0) {
		perror("Error: thread cannot be create");
		exit(1);
	}
	x = 55;
	sem_post (&sync);
	pthread_join(thread,NULL);
	sem_destroy(&sync);
	exit(0);
}
