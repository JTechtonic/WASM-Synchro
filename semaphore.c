#include "semaphore.h"

void semaphore_init()
{
    globalSem = malloc(sizeof(semaphore));
    atomic_init(&(globalSem->sem_val), 1);
}

void semaphore_wait()
{
    atomic_fetch_sub(&(globalSem->sem_val), 1);
    if (atomic_load(&(globalSem->sem_val)) < 0) 
    {
        __builtin_wasm_memory_atomic_wait32((int*)&(globalSem->sem_val), 1, -1);
    }
}

void semaphore_post()
{
    atomic_fetch_add(&(globalSem->sem_val), 1);
    if (atomic_load(&(globalSem->sem_val)) <= 0)
    {
        __builtin_wasm_memory_atomic_notify((int*)&(globalSem->sem_val), 1);
    }
}