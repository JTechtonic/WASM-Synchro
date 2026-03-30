#include <stdio.h>
#include <pthread.h>
#include <string.h>

#include "spinlock.h"
#include "yieldSpinlock.h"
#include "blockMutex.h"

#define NUM_THREADS 11 // Adjust --max-threads=N flag to match this
#define LOOP_AMT 100000

// Dev definition to change which lock to use
#define LOCK_METHOD 2

int counter = 0;


void *routine(void *arg)
{
	for (int i = 0; i < LOOP_AMT; i++)
	{
		//spinlock_lock();
		//yieldSpinlock_lock();
		//blockMutex_lock();

		switch (LOCK_METHOD)
		{
			case 0:
				spinlock_lock();
				break;

			case 1:
				yieldSpinlock_lock();
				break;

			case 2:
				blockMutex_lock();
				break;
		}

		counter++;

		switch (LOCK_METHOD)
		{
			case 0:
				spinlock_unlock();
				break;

			case 1:
				yieldSpinlock_unlock();
				break;

			case 2:
				blockMutex_unlock();
				break;
		}

		//blockMutex_unlock();
		//yieldSpinlock_unlock();
		//spinlock_unlock();
	}

	return NULL;
}

int main()
{
	switch (LOCK_METHOD)
	{
		case 0:
			initSpinlocks();
			break;

		case 1:
			initYieldSpinlocks();
			break;

		case 2:
			initBlockMutex();
			break;
	}

	pthread_t threads[NUM_THREADS];
	for (int i = 0; i < NUM_THREADS; i++)
	{
		//__wasi_thread_spawn() //Look into using this for spawning threads	
		int ret = pthread_create(&(threads[i]), NULL, routine, NULL);
		
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