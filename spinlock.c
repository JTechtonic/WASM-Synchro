#include "spinlock.h"

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

void initSpinlocks()
{
	atomic_init(global_spinlock, SPINLOCK_UNLOCKED);
}