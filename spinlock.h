#ifndef _SPINLOCK_H_
#define _SPINLOCK_H_

#include <stdbool.h>
#include <stdatomic.h>

#define SPINLOCK_LOCKED 1
#define SPINLOCK_UNLOCKED 0

static _Atomic int* global_spinlock;

bool atomic_test_and_set();
void spinlock_lock();
void spinlock_unlock();
void initSpinlocks();

#endif