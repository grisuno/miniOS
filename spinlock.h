#ifndef SPINLOCK_H
#define SPINLOCK_H

/* spinlock.h -- Lightweight spinlock for MiniOS kernel.
 *
 * A spinlock is the simplest mutual exclusion primitive for a uniprocessor
 * or early SMP kernel.  It disables interrupts on acquisition (to prevent
 * deadlock from an ISR re-entering the critical section) and busy-waits
 * on contention.
 *
 * Contract:
 *   spin_lock disables interrupts, then acquires the lock.
 *   spin_unlock releases the lock, then restores the interrupt state.
 *   A spinlock must never be held across a blocking operation.
 *   A spinlock must never be acquired twice without releasing (deadlock).
 *
 * Per-CPU vs shared:
 *   spinlocks protect SHARED data structures (proc_table, ready_queue).
 *   Per-CPU data (current PID on each core, per-CPU stacks) needs no lock.
 *
 * Implementation: xchg-based test-and-set.  The x86 LOCK XCHG is atomic
 * even on multi-core systems and does not require an explicit LOCK prefix.
 */

typedef struct {
    volatile unsigned int locked;
} spinlock_t;

#define SPINLOCK_INIT { .locked = 0 }

static inline void spin_init(spinlock_t *lock) {
    lock->locked = 0;
}

/* Acquire the lock with interrupt save.
 * Interrupts are disabled before the CAS loop to prevent ISR re-entry.
 * The memory clobber ensures the compiler does not reorder across the lock. */
static inline void spin_lock(spinlock_t *lock) {
    __asm__ volatile("cli");
    while (__sync_lock_test_and_set(&lock->locked, 1)) {
        /* spin */
    }
    __sync_synchronize();
}

/* Release the lock and restore interrupts.
 * The release uses __sync_lock_release which is a store-release with
 * the correct memory ordering. */
static inline void spin_unlock(spinlock_t *lock) {
    __sync_synchronize();
    __sync_lock_release(&lock->locked);
    __asm__ volatile("sti");
}

/* Try to acquire the lock without blocking.
 * Returns 1 if the lock was acquired, 0 if contended.
 * Interrupts are NOT modified (caller decides). */
static inline int spin_trylock(spinlock_t *lock) {
    int was = __sync_lock_test_and_set(&lock->locked, 1);
    if (!was) __sync_synchronize();
    return !was;
}

#endif
