#ifndef SYNC_H
#define SYNC_H

/* sync.h -- Blocking synchronization primitives (roadmap Phase 3.1).
 *
 * spinlock.h covers single-level mutual exclusion with interrupts off.
 * This header adds the blocking layer on top of the scheduler: wait
 * queues, mutexes, counting semaphores, condition variables and
 * read-write locks.  Everything here is SMP-safe (per-object spinlock
 * with irqsave) and single-core correct (state changes happen with
 * interrupts disabled, and the timer-ISR dispatch only ever picks
 * PROC_READY processes).
 *
 * Blocking contract (applies to sleep_on, mutex_lock, sem_wait,
 * cond_wait and the rwlock writers/readers when they must wait):
 *   - Never hold a spinlock across schedule().  Each primitive drops
 *     its guard before sleeping and re-acquires it afterwards.
 *   - Callers must loop on their predicate around any sleep, because a
 *     wake-up can arrive between the predicate check and the sleep
 *     (interrupts are re-enabled when the queue guard is dropped).
 *   - A sleep with no matching wake-up blocks forever; drivers must
 *     pair every sleep_on site with a wake_up site on all exit paths.
 *
 * There is no deadlock detection: a thread
 * that locks the same mutex twice without unlocking deadlocks, exactly
 * like a double spin_lock. Prefer mutex_trylock on paths that may
 * re-enter. Futexes (fast userspace mutexes) are a
 * later step and will reuse wait_queue_t for their sleepers.
 */

#include <stdint.h>

#include "spinlock.h"
#include "sched.h"

/* wait-queue linkage: procs chain through proc_t.wq_next, WQ_NONE ends
 * the chain and marks an empty queue.  PIDs start at 1 (sched.c), so a
 * zeroed proc_t never aliases a queued entry. */
#define WQ_NONE (-1)

/* ---- Wait queues ---- */
typedef struct {
    spinlock_t lock;
    int        head;   /* pid at the front, WQ_NONE when empty */
    int        tail;   /* pid at the back, valid only when head != WQ_NONE */
} wait_queue_t;

#define WAIT_QUEUE_INIT { SPINLOCK_INIT, WQ_NONE, WQ_NONE }

void wq_init(wait_queue_t *q);
void sleep_on(wait_queue_t *q);
int  wake_up(wait_queue_t *q);
int  wake_up_all(wait_queue_t *q);

/* ---- Mutex (blocking, non-recursive) ----
 * Priority inheritance (thesis correction 3): a low-priority holder that
 * blocks a high-priority waiter is boosted to the waiter's effective
 * priority, transitively along the blocked-on chain, until it releases.
 * pi_set_base assigns a thread's base priority (default 0); pi_get_eff
 * reports the boosted value the scheduler must honor. State lives in
 * sync.c parallel arrays: proc_t is 248 bytes by asm contract (sched.c
 * asserts it, syscall_entry hardcodes it), so no field can be added. */
typedef struct {
    spinlock_t   guard;
    int          locked;   /* 0 = free, 1 = held */
    int          owner;    /* pid of holder, WQ_NONE when free */
    wait_queue_t waiters;
} mutex_t;

#define MUTEX_INIT { SPINLOCK_INIT, 0, WQ_NONE, WAIT_QUEUE_INIT }

void mutex_init(mutex_t *m);
void mutex_lock(mutex_t *m);
void mutex_unlock(mutex_t *m);
int  mutex_trylock(mutex_t *m);
void mutex_note_waiter(mutex_t *m, int waiter);
void pi_set_base(int pid, int prio);
int  pi_get_eff(int pid);

/* ---- Counting semaphore ---- */
typedef struct {
    spinlock_t   guard;
    int          count;
    wait_queue_t waiters;
} sem_t;

#define SEM_INIT(n) { SPINLOCK_INIT, (n), WAIT_QUEUE_INIT }

void sem_init(sem_t *s, int value);
void sem_wait(sem_t *s);
void sem_post(sem_t *s);

/* ---- Condition variable ----
 * Always paired with a mutex: cond_wait atomically releases the mutex,
 * sleeps, and re-acquires it before returning (Mesa semantics: re-check
 * the predicate in a loop). */
typedef struct {
    wait_queue_t waiters;
} cond_t;

#define COND_INIT { WAIT_QUEUE_INIT }

void cond_init(cond_t *c);
void cond_wait(cond_t *c, mutex_t *m);
void cond_signal(cond_t *c);
void cond_broadcast(cond_t *c);

/* ---- Read-write lock (writer-preferring, no recursion) ---- */
typedef struct {
    spinlock_t   guard;
    int          readers;  /* active readers */
    int          writer;   /* 0 = no writer, 1 = writer holds */
    wait_queue_t waiters;
} rwlock_t;

#define RWLOCK_INIT { SPINLOCK_INIT, 0, 0, WAIT_QUEUE_INIT }

void rwlock_init(rwlock_t *rw);
void rwlock_read_lock(rwlock_t *rw);
void rwlock_read_unlock(rwlock_t *rw);
void rwlock_write_lock(rwlock_t *rw);
void rwlock_write_unlock(rwlock_t *rw);

#endif
