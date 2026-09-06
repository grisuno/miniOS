/** Docstring: kernel/futex.c -- Kernel side of the futex contract.
 *
 * Implements futex.h on top of the scheduler process table and the irqsave
 * spinlocks. The file has no other kernel dependency, so the host unit
 * test (tests/test_futex.c, make test-futex) compiles it directly against
 * stubs for proc_get, schedule and current_pid, exactly like sync.c.
 */

#include "futex.h"
#include "sync.h"

#ifdef SYNC_HOST_CURRENT_PID
extern int t_cur_pid;
#endif

typedef struct {
    futex_bucket_t buckets[FUTEX_BUCKETS];
    unsigned long awaited[MAX_PROCS];
} futex_table_t;

static futex_table_t futex_table;

static unsigned long futex_hash(unsigned long uaddr) {
    unsigned long word = uaddr >> 2;
    word ^= word >> 16;
    word *= FUTEX_HASH_GOLDEN;
    word ^= word >> 13;
    return word & FUTEX_BUCKET_MASK;
}

static futex_bucket_t *futex_bucket(unsigned long uaddr) {
    return &futex_table.buckets[futex_hash(uaddr)];
}

/** Docstring: Initialize every bucket queue and clear the awaited table. */
void futex_init(void) {
    int i;
    for (i = 0; i < FUTEX_BUCKETS; i++) {
        spin_init(&futex_table.buckets[i].lock);
        futex_table.buckets[i].head = WQ_NONE;
        futex_table.buckets[i].tail = WQ_NONE;
    }
    for (i = 0; i < MAX_PROCS; i++)
        futex_table.awaited[i] = 0;
}

/** Docstring: Sleep while the word at uaddr still equals val.
 *
 * Returns FUTEX_OK after sleeping (caller re-checks its predicate),
 * FUTEX_NOMATCH when the word already differs (no sleep performed),
 * FUTEX_NOPROC when there is no current process. The value comparison
 * and the enqueue share the bucket lock, which is what makes lost
 * wakeups impossible. The bucket lock is released before schedule.
 */
long futex_wait(unsigned long uaddr, int val) {
    futex_bucket_t *b = futex_bucket(uaddr);
    irqflags_t flags;
    spin_lock_irqsave(&b->lock, &flags);
    proc_t *cur = proc_get(current_pid);
    if (!cur) {
        spin_unlock_irqrestore(&b->lock, flags);
        return FUTEX_NOPROC;
    }
    if (*(volatile int *)uaddr != val) {
        spin_unlock_irqrestore(&b->lock, flags);
        return FUTEX_NOMATCH;
    }
    cur->state = PROC_BLOCKED;
    cur->wq_next = WQ_NONE;
    futex_table.awaited[cur->pid] = uaddr;
    if (b->head == WQ_NONE) {
        b->head = cur->pid;
        b->tail = cur->pid;
    } else {
        procs[b->tail].wq_next = cur->pid;
        b->tail = cur->pid;
    }
    spin_unlock_irqrestore(&b->lock, flags);
    schedule();
    return FUTEX_OK;
}

/** Docstring: Wake up to n sleepers waiting on uaddr.
 *
 * Only entries whose recorded address equals uaddr change state; hash
 * collisions sleep through. Returns the number of threads woken, zero
 * when the bucket holds no waiter for this address. Never sleeps.
 */
long futex_wake(unsigned long uaddr, int n) {
    futex_bucket_t *b = futex_bucket(uaddr);
    irqflags_t flags;
    long woken = 0;
    int prev = WQ_NONE;
    int pid;
    if (n <= 0)
        return 0;
    spin_lock_irqsave(&b->lock, &flags);
    pid = b->head;
    while (pid != WQ_NONE && woken < n) {
        int next = procs[pid].wq_next;
        if (futex_table.awaited[pid] == uaddr &&
            procs[pid].state == PROC_BLOCKED) {
            if (prev == WQ_NONE)
                b->head = next;
            else
                procs[prev].wq_next = next;
            if (b->tail == pid)
                b->tail = prev;
            procs[pid].wq_next = WQ_NONE;
            futex_table.awaited[pid] = 0;
            procs[pid].state = PROC_READY;
            woken++;
        } else {
            prev = pid;
        }
        pid = next;
    }
    spin_unlock_irqrestore(&b->lock, flags);
    return woken;
}
