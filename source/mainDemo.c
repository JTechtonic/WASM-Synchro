#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "spinlock.h"
#include "yieldSpinlock.h"
#include "blockMutex.h"

#define NUM_THREADS 11 // Adjust --max-threads=N flag to match this
#define LOOP_AMT 100000

// Dev definition to change which lock to use
int LOCK_METHOD = 0;

int counter = 0;


void *routine(void *arg)
{
	for (int i = 0; i < LOOP_AMT; i++)
	{
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
	}

	return NULL;
}

int main(int argc, char* argv[])
{
	// Change lock method depending on command line arg
	if (argc > 1)
	{
		int input = atoi(argv[1]);

		if (input < 0 || input > 2)
			LOCK_METHOD = 0;
		else
			LOCK_METHOD = input;
	}

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