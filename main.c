#include <stdio.h>
#include <pthread.h>
#include <string.h>

#include "spinlock.h"

#define NUM_THREADS 9 // Adjust --max-threads=N flag to match this
#define LOOP_AMT 100000

int counter = 0;


void *normalSpinlockRoutine(void *arg)
{
	for (int i = 0; i < LOOP_AMT; i++)
	{
		spinlock_lock(global_spinlock);
		counter++;
		spinlock_unlock(global_spinlock);
	}

	return NULL;
}

int main()
{
	initSpinlocks();

	pthread_t threads[NUM_THREADS];
	for (int i = 0; i < NUM_THREADS; i++)
	{
		int ret = pthread_create(&(threads[i]), NULL, normalSpinlockRoutine, NULL);
		


    	if (ret)
      		printf("failed to spawn thread #%d\n", i);
  	}

  	for (int i = 0; i < NUM_THREADS; i++)
	{
    	pthread_join(threads[i], NULL);
  	}

	printf("%d\n", counter);
	printf("Is supposed to be: %d\n", NUM_THREADS * LOOP_AMT);
	return 0;
}