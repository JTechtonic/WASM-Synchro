#include "spinlock.h"

bool atomic_test_and_set(int* spinlock)
{
	int free = SPINLOCK_UNLOCKED;
	int locked = SPINLOCK_LOCKED;

	// Checks to see if spinlock is free; if it is free then make it locked
	//bool obtainedLock = atomic_compare_exchange_strong(global_spinlock, &free, locked);
	return __atomic_compare_exchange(spinlock, &free, &locked, false, 
									__ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}

void spinlock_lock()
{
	while (!atomic_test_and_set(global_spinlock)) {};
}

void spinlock_unlock()
{
	int free = SPINLOCK_UNLOCKED;
	__atomic_store(global_spinlock, &free, __ATOMIC_SEQ_CST);
}

void initSpinlocks()
{
	//atomic_init(global_spinlock, SPINLOCK_UNLOCKED);
	int free = SPINLOCK_UNLOCKED;
	__atomic_store(global_spinlock, &free, __ATOMIC_SEQ_CST);
}