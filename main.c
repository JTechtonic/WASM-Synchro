#include <stdio.h>
#include <pthread.h>
#include <string.h>

int counter = 0;

#define NUM_THREADS 4 // 4 is max for some reason?

void *thread_routine(void *arg)
{
	for (int i = 0; i < 1000000; i++)
	{
		counter++;
	}

	return NULL;
}

int main(int argc, char** argv)
{
	pthread_t threads[10];
	for (int i = 0; i < NUM_THREADS; i++)
	{
		int ret = pthread_create(&threads[i], NULL, thread_routine, NULL);
    	if (ret)
      		printf("failed to spawn thread: %d", ret);

  	}

  	for (int i = 0; i < NUM_THREADS; i++)
	{
    	pthread_join(threads[i], NULL);
  	}

	printf("%d\n", counter);
	return 0;
}