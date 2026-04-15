#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include "conditionVars.h"

#define PRODUCER_THREADS 50 // --max-threads must be at minimum 2 times this amount

// Producer/Consumer threads will randomly add/decrease 1 - this amount in counter
#define RANGE 20 

pthread_barrier_t barrier;

int counter = 0;
int consumed = 0;

void *routine(void *args)
{
	int isProducer = *((int*)args);
	int amount = *((int*)args + 1);
	
	// To help make sure all threads start at the same time
	pthread_barrier_wait(&barrier);

	if (isProducer == 1)
	{
		blockMutex_lock();
		counter += amount;
		printf("Thread +%d increased counter to: %d\n", amount, counter);
		blockMutex_unlock();
		signal();
	}
	else
	{
		blockMutex_lock();
		while (!(counter >= amount))
		{
			// Debug statement to track threads sleeping
			//printf("Thread -%d going to sleep because counter (%d) < amount (%d)\n", amount, counter, amount);
			wait();
		}
		counter -= amount;
		consumed += amount;
		printf("Thread -%d decreased counter to: %d\n", amount, counter);
		blockMutex_unlock();
	}

	return NULL;
}


int main()
{
	srand(time(NULL));

	initConditionVar();

	pthread_barrier_init(&barrier, NULL, PRODUCER_THREADS * 2);

	pthread_t threads[PRODUCER_THREADS * 2];
	int totalProduced = 0;

	// Make Producer Threads
	for (int i = 0; i < PRODUCER_THREADS * 2; i++)
	{
		int* args = malloc(sizeof(int) * 2);
		args[0] = 1; // Producer

		int produceAmt = (rand() % RANGE) + 1; // Random num between 1 - range
		args[1] = produceAmt;
		totalProduced += produceAmt;

		int ret = pthread_create(&(threads[i]), NULL, routine, (void*)args);
		if (ret)
			printf("failed to spawn thread #%d\n", i);


		args[0] = 0; // Consumer

		ret = pthread_create(&(threads[++i]), NULL, routine, (void*)args);
		if (ret)
	  		printf("failed to spawn thread #%d\n", i);

		free(args);
	}

	for (int i = 0; i < PRODUCER_THREADS * 2; i++)
	{
		pthread_join(threads[i], NULL);
  	}

	printf("Amount Produced: %d\n", totalProduced);
	printf("Counter (Is Supposed to be 0): %d\n", counter);
	printf("Consumed: %d\n", consumed);
	return 0;
}