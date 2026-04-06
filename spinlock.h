#ifndef _SPINLOCK_H_
#define _SPINLOCK_H_

#include <stdbool.h>

#define SPINLOCK_LOCKED 1
#define SPINLOCK_UNLOCKED 0

static int* global_spinlock;

bool atomic_test_and_set(int* spinlock);
void spinlock_lock();
void spinlock_unlock();
void initSpinlocks();

#endif