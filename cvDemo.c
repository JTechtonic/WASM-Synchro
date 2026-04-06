#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <pthread.h>
#include "conditionVars.h"

#define PRODUCER_THREADS 50 // --max-threads must be at minimum 2 times this amount

// Producer/Consumer threads will randomly add/decrease 1 - this amount in counter
#define RANGE 20 

int counter = 0;
int consumed = 0;

// Look into the following link:
// https://www.google.com/search?client=opera-gx&q=how+to+implement+condition+variables&sourceid=opera&ie=UTF-8&oe=UTF-8

void *routine(void *args)
{
	int isProducer = *((int*)args);
	int amount = *((int*)args + 1);

	if (isProducer == 1)
	{
		blockMutex_lock();
		counter += amount;
		printf("Counter is increased to: %d\n", counter);
		blockMutex_unlock();
		signal();
	}
	else
	{
		blockMutex_lock();
		while (!(counter >= amount))
		{
			wait();
		}
		counter -= amount;
		consumed += amount;
		printf("Counter is decreased to: %d\n", counter);
		blockMutex_unlock();
	}

	return NULL;
}


int main()
{ // Look into making all threads start at the same time with pthread_barrier_t
	srand(time(NULL));

	initConditionVar();

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