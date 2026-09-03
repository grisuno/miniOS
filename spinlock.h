#ifndef SPINLOCK_H
#define SPINLOCK_H

/* spinlock.h -- Lightweight spinlock for MiniOS kernel.
 *
 * A spinlock is the simplest mutual exclusion primitive for a uniprocessor
 * or early SMP kernel.  Two acquisition modes are provided:
 *
 *   spin_lock / spin_unlock
 *     Disables interrupts on acquisition and re-enables on release.
 *     Safe when the caller knows interrupts are already disabled (ISRs).
 *     Must NOT be nested: a caller that already holds another spinlock
 *     with interrupts disabled and calls spin_lock will deadlock when
 *     the inner spin_unlock re-enables interrupts prematurely.
 *
 *   spin_lock_irqsave / spin_unlock_irqrestore
 *     Saves RFLAGS.IF before disabling interrupts and restores the
 *     original state on release.  Safe for nested critical sections:
 *     the inner release restores IF to its saved value (still disabled
 *     if the outer section had IF=0), so the outer spin_unlock can
 *     safely re-enable interrupts exactly once.
 *
 * Contract:
 *   A spinlock must never be held across a blocking operation.
 *   A spinlock must never be acquired twice without releasing (deadlock).
 *   spin_lock is for ISR context (interrupts already off or single-level).
 *   spin_lock_irqsave is for all other kernel paths.
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

typedef unsigned long irqflags_t;

#define SPINLOCK_INIT { .locked = 0 }

static inline void spin_init(spinlock_t *lock) {
    lock->locked = 0;
}

/* Read RFLAGS and disable interrupts. */
static inline irqflags_t spin_save_irq(void) {
    irqflags_t flags;
    __asm__ volatile("pushfq; pop %0; cli" : "=r"(flags));
    return flags;
}

/* Restore RFLAGS (including IF) from a saved value. */
static inline void spin_restore_irq(irqflags_t flags) {
    __asm__ volatile("push %0; popfq" : : "r"(flags) : "memory");
}

/* Acquire the lock and disable interrupts.
 * Interrupts are disabled before the CAS loop to prevent ISR re-entry.
 * The memory clobber ensures the compiler does not reorder across the lock.
 * Use this from ISR context or when a single-level lock is sufficient. */
static inline void spin_lock(spinlock_t *lock) {
    __asm__ volatile("cli");
    while (__sync_lock_test_and_set(&lock->locked, 1)) {
    }
    __sync_synchronize();
}

/* Release the lock and re-enable interrupts.
 * The release uses __sync_lock_release which is a store-release with
 * the correct memory ordering. */
static inline void spin_unlock(spinlock_t *lock) {
    __sync_synchronize();
    __sync_lock_release(&lock->locked);
    __asm__ volatile("sti");
}

/* Acquire the lock with interrupt state saved.
 * Saves RFLAGS (including IF), disables interrupts, then acquires.
 * Safe for nested critical sections: the inner unlock restores the
 * saved flags, keeping IF disabled if the outer section had it off. */
static inline void spin_lock_irqsave(spinlock_t *lock, irqflags_t *flags) {
    *flags = spin_save_irq();
    while (__sync_lock_test_and_set(&lock->locked, 1)) {
    }
    __sync_synchronize();
}

/* Release the lock and restore the saved interrupt state.
 * If the caller's interrupts were enabled before spin_lock_irqsave,
 * they are re-enabled here.  If they were disabled, they stay disabled. */
static inline void spin_unlock_irqrestore(spinlock_t *lock, irqflags_t flags) {
    __sync_synchronize();
    __sync_lock_release(&lock->locked);
    spin_restore_irq(flags);
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
