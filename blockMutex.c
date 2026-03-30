#include "blockMutex.h"

void initBlockMutex()
{
	//*globalBlockMutex = MUTEX_UNLOCKED;
	int free = MUTEX_UNLOCKED;
	__atomic_store(globalBlockMutex, &free, __ATOMIC_SEQ_CST);
}

bool try_lock()
{
	// Use the exposed clang version to do try lock
	int free = MUTEX_UNLOCKED;
	int locked = MUTEX_LOCKED;

	// Works the same way as atomic_test_and_set() in spinlock.c
	return __atomic_compare_exchange(globalBlockMutex, &free, &locked, false, 
									__ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}

void blockMutex_lock()
{
	// Lost wakeup bug would have this be an if statement instead of a while loop
	while (!try_lock())
	{
		// Put the thread to sleep indefinitely if we can't get the lock
		int ret = __builtin_wasm_memory_atomic_wait32(globalBlockMutex, MUTEX_LOCKED, -1);
		if (ret == 0)
			printf("Thread awoken");
	}
}

void blockMutex_unlock()
{
	int free = MUTEX_UNLOCKED;

	// Make the lock unlocked and wake a singular thread that is asleep
	__atomic_store(globalBlockMutex, &free, __ATOMIC_SEQ_CST);
	__builtin_wasm_memory_atomic_notify(globalBlockMutex, 1);
}