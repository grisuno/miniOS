#ifndef FUTEX_H
#define FUTEX_H

/** Docstring: futex.h -- Fast userspace mutex sleep/wake contract.
 *
 * A futex is a 32-bit word in user memory paired with kernel wait queues.
 * Uncontended acquire/release never enters the kernel (plain atomics in
 * userland, see progs/src/mthreads.h); the kernel is involved only when a
 * thread must sleep until the word changes (FUTEX_WAIT) or when a thread
 * must wake sleepers after changing it (FUTEX_WAKE). This turns userland
 * mutexes from spin+yield loops into real blocking primitives without a
 * per-mutex kernel object: the address itself is the key.
 *
 * Sleeping contract, mirroring sync.h:
 * Never hold a spinlock across schedule. Callers loop on their predicate
 * around every wait, because a wake can land between the predicate check
 * and the sleep, and because wakeups are level-agnostic (a wake may arrive
 * with no matching waiter and is then a no-op, never an error).
 *
 * Hash design:
 * Waiters chain intrusively through proc_t.wq_next on one of FUTEX_BUCKETS
 * bucket queues selected by a multiplicative hash of the user address.
 * Buckets may collide: each sleeper records its awaited address in the
 * parallel futex_wait_addr table indexed by pid, and FUTEX_WAKE scans the
 * bucket chain waking only entries whose recorded address matches. A
 * thread sleeps on exactly one primitive at a time, so sharing wq_next
 * with sleep_on is safe.
 *
 * Lost-wakeup freedom:
 * Both the value check and the enqueue run under the bucket lock, and the
 * state transition to PROC_BLOCKED happens before the lock is released.
 * A waker either observes the queued waiter (and READYs it) or runs fully
 * before the waiter queued (and then the waiter observes the updated
 * value and never sleeps). The unlock-to-schedule window degrades to a
 * single spurious extra deschedule, never to an infinite sleep.
 *
 * Bounds and failure modes, all fail-closed:
 * A null waiter count, an unknown pid and an empty bucket are safe no-ops.
 * futex_wait on a word whose value already differs returns FUTEX_NOMATCH
 * without sleeping. Counts above FUTEX_WAKE_ALL clamp to drain-the-bucket.
 * Kernel addresses never reach the queues: the syscall layer rejects any
 * word outside the user window with -EFAULT before calling in.
 */

#include <stdint.h>

#include "spinlock.h"
#include "sched.h"
#include "sync.h"

#define FUTEX_BUCKETS 64
#define FUTEX_BUCKET_MASK (FUTEX_BUCKETS - 1)
#define FUTEX_HASH_GOLDEN 0x9e3779b1UL

#define FUTEX_OK 0
#define FUTEX_NOMATCH 1
#define FUTEX_NOPROC (-1)
#define FUTEX_WAKE_ALL 0x7fffffff

typedef struct {
    spinlock_t lock;
    int head;
    int tail;
} futex_bucket_t;

void futex_init(void);
long futex_wait(unsigned long uaddr, int val);
long futex_wake(unsigned long uaddr, int n);

#endif
