/** Docstring: kernel/percpu_rq.c -- Per-CPU runqueue hints and stealing.
 *
 * Implements percpu_rq.h. The rings hold pid hints only; the process
 * table owns all dispatch truth. The file depends on sched.h for the CPU
 * topology and on spinlock.h for the ring locks, which keeps it
 * host-testable (tests/test_percpu_rq.c, make test-percpu-rq) with a stub
 * topology of fake CPUs.
 */

#include "percpu_rq.h"

static percpu_rq_t rqueues[MAX_CPUS];

static int rq_cpu_valid(int cpu) {
    return cpu >= 0 && cpu < MAX_CPUS && cpu < cpu_count;
}

/** Docstring: Clear every ring and counter. Called once from sched_init. */
void rq_init(void) {
    int c;
    int i;
    for (c = 0; c < MAX_CPUS; c++) {
        spin_init(&rqueues[c].lock);
        for (i = 0; i < RQ_DEPTH; i++)
            rqueues[c].ring[i] = WQ_NONE_HINT;
        rqueues[c].head = 0;
        rqueues[c].count = 0;
        rqueues[c].hits = 0;
        rqueues[c].steals = 0;
        rqueues[c].drops = 0;
        rqueues[c].polls = 0;
    }
}

/** Docstring: Record pid as READY work for cpu.
 *
 * Lossy by contract: a full ring drops the hint and counts the drop. The
 * global scan remains the fallback, so a drop costs one rescan period of
 * latency at most, never correctness. Pids outside the table are refused.
 */
void rq_enqueue(int cpu, int pid) {
    irqflags_t flags;
    int slot;
    if (!rq_cpu_valid(cpu))
        return;
    if (pid <= 0 || pid >= MAX_PROCS)
        return;
    spin_lock_irqsave(&rqueues[cpu].lock, &flags);
    if (rqueues[cpu].count >= RQ_DEPTH) {
        rqueues[cpu].drops++;
        spin_unlock_irqrestore(&rqueues[cpu].lock, flags);
        return;
    }
    slot = (rqueues[cpu].head + rqueues[cpu].count) % RQ_DEPTH;
    rqueues[cpu].ring[slot] = pid;
    rqueues[cpu].count++;
    spin_unlock_irqrestore(&rqueues[cpu].lock, flags);
}

/** Docstring: Pop one hint from the local ring, WQ_NONE_HINT when empty. */
int rq_pop_local(int cpu) {
    irqflags_t flags;
    int pid;
    if (!rq_cpu_valid(cpu))
        return WQ_NONE_HINT;
    spin_lock_irqsave(&rqueues[cpu].lock, &flags);
    if (rqueues[cpu].count <= 0) {
        spin_unlock_irqrestore(&rqueues[cpu].lock, flags);
        return WQ_NONE_HINT;
    }
    pid = rqueues[cpu].ring[rqueues[cpu].head];
    rqueues[cpu].ring[rqueues[cpu].head] = WQ_NONE_HINT;
    rqueues[cpu].head = (rqueues[cpu].head + 1) % RQ_DEPTH;
    rqueues[cpu].count--;
    rqueues[cpu].hits++;
    spin_unlock_irqrestore(&rqueues[cpu].lock, flags);
    return pid;
}

/** Docstring: Non-blocking steal of one hint from another CPU's ring.
 *
 * Tries every remote ring once with spin_trylock and returns the first
 * hint found, reporting the donor through from_cpu. Rings that are busy
 * are skipped, never waited on. Returns WQ_NONE_HINT when nothing could
 * be stolen without blocking. The thief's steal counter is owner-written
 * but updated under the donor's lock, so it uses an atomic add (the same
 * pattern as smp_dispatches) instead of relying on the donor's lock.
 */
int rq_steal_once(int self_cpu, int *from_cpu) {
    int c;
    for (c = 0; c < cpu_count && c < MAX_CPUS; c++) {
        int pid;
        if (c == self_cpu)
            continue;
        if (!spin_trylock(&rqueues[c].lock))
            continue;
        if (rqueues[c].count <= 0) {
            spin_unlock(&rqueues[c].lock);
            continue;
        }
        pid = rqueues[c].ring[rqueues[c].head];
        rqueues[c].ring[rqueues[c].head] = WQ_NONE_HINT;
        rqueues[c].head = (rqueues[c].head + 1) % RQ_DEPTH;
        rqueues[c].count--;
        __sync_fetch_and_add(&rqueues[self_cpu].steals, 1);
        spin_unlock(&rqueues[c].lock);
        if (from_cpu)
            *from_cpu = c;
        return pid;
    }
    return WQ_NONE_HINT;
}

/** Docstring: True when cpu holds no hint. Lock-protected peek. */
int rq_empty(int cpu) {
    irqflags_t flags;
    int empty;
    if (!rq_cpu_valid(cpu))
        return 1;
    spin_lock_irqsave(&rqueues[cpu].lock, &flags);
    empty = (rqueues[cpu].count <= 0);
    spin_unlock_irqrestore(&rqueues[cpu].lock, flags);
    return empty;
}

/** Docstring: Count an unsuccessful claim poll for the rescan schedule. */
void rq_note_poll(int cpu) {
    irqflags_t flags;
    if (!rq_cpu_valid(cpu))
        return;
    spin_lock_irqsave(&rqueues[cpu].lock, &flags);
    rqueues[cpu].polls++;
    spin_unlock_irqrestore(&rqueues[cpu].lock, flags);
}

/** Docstring: True every RQ_RESCAN_PERIOD polls, bounding hint staleness. */
int rq_should_rescan(int cpu) {
    irqflags_t flags;
    int due = 0;
    if (!rq_cpu_valid(cpu))
        return 1;
    spin_lock_irqsave(&rqueues[cpu].lock, &flags);
    if (rqueues[cpu].polls >= RQ_RESCAN_PERIOD) {
        rqueues[cpu].polls = 0;
        due = 1;
    }
    spin_unlock_irqrestore(&rqueues[cpu].lock, flags);
    return due;
}

/** Docstring: Snapshot hits, steals and drops for diagnostics. */
void rq_stats(int cpu, unsigned long *hits, unsigned long *steals,
              unsigned long *drops) {
    irqflags_t flags;
    if (!rq_cpu_valid(cpu))
        return;
    spin_lock_irqsave(&rqueues[cpu].lock, &flags);
    if (hits)
        *hits = rqueues[cpu].hits;
    if (steals)
        *steals = rqueues[cpu].steals;
    if (drops)
        *drops = rqueues[cpu].drops;
    spin_unlock_irqrestore(&rqueues[cpu].lock, flags);
}
