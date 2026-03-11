#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <stdatomic.h>

void initAtomics();

#define SPINLOCK_LOCKED 1
#define SPINLOCK_UNLOCKED 0

_Atomic int* global_spinlock;

#define NUM_THREADS 10 // Adjust --max-threads=N flag to match this

int counter = 0;

bool atomic_test_and_set(_Atomic int* spinlock)
{
	int free = SPINLOCK_UNLOCKED;
	int locked = SPINLOCK_LOCKED;

	// Checks to see if spinlock is free; if it is free then make it locked
	bool obtainedLock = atomic_compare_exchange_strong(spinlock, &free, locked);

	// Returns true if the spinlock used to be free and is now locked; false otherwise
    return obtainedLock;
}

void spinlock_lock(_Atomic int* spinlock)
{
	while (!atomic_test_and_set(spinlock)) {};
}

void spinlock_unlock(_Atomic int* spinlock)
{
	*spinlock = SPINLOCK_UNLOCKED;
}


void *thread_routine(void *arg)
{
	//spinlock_lock(global_spinlock);
	for (int i = 0; i < 1000000; i++)
	{
		spinlock_lock(global_spinlock);
		counter++;
		spinlock_unlock(global_spinlock);
	}
	//spinlock_unlock(global_spinlock);

	return NULL;
}

int main()
{
	initAtomics();

	pthread_t threads[NUM_THREADS];
	for (int i = 0; i < NUM_THREADS; i++)
	{
		int ret = pthread_create(&threads[i], NULL, thread_routine, NULL);
    	if (ret)
      		printf("failed to spawn thread: %d\n", ret);

  	}

  	for (int i = 0; i < NUM_THREADS; i++)
	{
    	pthread_join(threads[i], NULL);
  	}

	printf("%d\n", counter);
	printf("Is supposed to be: %d\n", NUM_THREADS * 1000000);
	return 0;
}

void initAtomics()
{
	atomic_init(global_spinlock, SPINLOCK_UNLOCKED);
	//wasm_cluster_set_max_thread_num(100);
}