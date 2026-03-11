#include "yieldSpinlock.h"
#include "spinlock.h"
#include <sched.h>

static _Atomic int* global_yieldSpinlock;

void initYieldSpinlocks()
{
    atomic_init(global_yieldSpinlock, SPINLOCK_UNLOCKED);
}



// Snippet from Google AI

// #include <stdatomic.h>
// #include <sched.h> // For sched_yield()
// #include <stdbool.h>

// typedef struct {
//     atomic_flag flag;
// } spinlock_t;

// void spinlock_init(spinlock_t *lock) {
//     atomic_flag_clear(&lock->flag);
// }

// void spinlock_lock(spinlock_t *lock) {
//     int backoff = 1;
//     // Try to acquire the lock
//     while (atomic_flag_test_and_set(&lock->flag)) {
//         // Back-off: Yield the CPU to allow other threads to run
//         for (int i = 0; i < backoff; ++i) {
//             // Optional: Insert pause instruction here for tighter loops
//             // __builtin_ia32_pause(); 
//         }
        
//         sched_yield(); // Voluntarily yield the processor
        
//         // Exponentially increase back-off
//         if (backoff < 1024) backoff <<= 1;
//     }
// }

// void spinlock_unlock(spinlock_t *lock) {
//     atomic_flag_clear(&lock->flag);
// }
