#include "yieldSpinlock.h"

void initYieldSpinlocks()
{
	int free = SPINLOCK_UNLOCKED;
	__atomic_store(global_yieldSpinlock, &free, __ATOMIC_SEQ_CST);
}

void yieldSpinlock_lock()
{
	int backoff = 1;
	
	// Try to acquire the lock
	while (!atomic_test_and_set(global_yieldSpinlock))
	{
		// Back-off: Yield the CPU to allow other threads to run
		for (int i = 0; i < backoff; i++) {	}
		
		sched_yield(); // Voluntarily yield the processor
		
		// Exponentially increase back-off
		if (backoff < 1024) backoff <<= 1;
	}
}

void yieldSpinlock_unlock()
{
	int free = SPINLOCK_UNLOCKED;
	__atomic_store(global_yieldSpinlock, &free, __ATOMIC_SEQ_CST);
}