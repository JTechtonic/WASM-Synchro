#include "spinlock.h"

bool atomic_test_and_set()
{
	int free = SPINLOCK_UNLOCKED;
	int locked = SPINLOCK_LOCKED;

	// Checks to see if spinlock is free; if it is free then make it locked
	bool obtainedLock = atomic_compare_exchange_strong(global_spinlock, &free, locked);

	// Returns true if the spinlock used to be free and is now locked; false otherwise
    return obtainedLock;
}

void spinlock_lock()
{
	while (!atomic_test_and_set()) {};
}

void spinlock_unlock()
{
	*global_spinlock = SPINLOCK_UNLOCKED;
}

void initSpinlocks()
{
	atomic_init(global_spinlock, SPINLOCK_UNLOCKED);
}