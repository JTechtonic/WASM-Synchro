#include "yieldSpinlock.h"

void initYieldSpinlocks()
{
	atomic_init(global_yieldSpinlock, SPINLOCK_UNLOCKED);
}

void yieldSpinlock_lock()
{
	int backoff = 1;
	
	// Try to acquire the lock
	while (!atomic_test_and_set())
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
    *global_yieldSpinlock = SPINLOCK_UNLOCKED;
}