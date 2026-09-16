#ifndef PERCPU_RQ_H
#define PERCPU_RQ_H

/** Docstring: percpu_rq.h -- Per-CPU runqueues with work stealing.
 *
 * Problem addressed: sched_lock serializes every dispatch decision and
 * every idle poll across all CPUs, so scheduler ticks and thread wakeups
 * contend on one lock and throughput stops scaling past two cores.
 *
 * Design:
 * Each CPU owns a small ring of pid hints (threads that became READY on
 * that CPU, recorded at spawn time). Claiming from the local ring needs
 * only the local ring lock; a global sched_lock is taken only to validate
 * a hint (procs[] stays authoritative) and only when a hint exists. An
 * idle CPU whose local ring is empty attempts one non-blocking steal per
 * remote ring (spin_trylock, never blocking) before falling back to the
 * legacy global scan.
 *
 * Hints are advisory, never authoritative:
 * A hint may be stale (thread already running, blocked or reaped) or lost
 * (ring full, waiter woken through a path that records no hint). Claiming
 * validates procs[pid].state == PROC_READY under sched_lock and discards
 * anything else. Lossy hints therefore degrade to the old global scan,
 * never to incorrect dispatch. To bound staleness, idle CPUs perform a
 * global-scan fallback every RQ_RESCAN_PERIOD unsuccessful polls, so a
 * READY thread with no live hint waits at most that many polls.
 *
 * Locking discipline:
 * Ring locks are leaves: they never nest inside sched_lock nor inside
 * another ring lock. Stealing pops a hint under the remote ring lock,
 * releases it, then validates under sched_lock. The fast idle path (all
 * rings empty) touches no sched_lock at all.
 *
 * Scope:
 * Only CLONE_VM threads migrate; a non-VM process keeps its address
 * space view on the BSP and is never hinted, never stolen, and always
 * dispatched through the global scan.
 */

#include <stdint.h>

#include "spinlock.h"
#include "sched.h"

#define RQ_DEPTH 16
#define RQ_RESCAN_PERIOD 64
#define RQ_VALIDATE_ATTEMPTS 4
#define WQ_NONE_HINT (-1)

typedef struct {
    spinlock_t lock;
    int ring[RQ_DEPTH];
    int head;
    int count;
    unsigned long hits;
    unsigned long steals;
    unsigned long drops;
    unsigned long polls;
} percpu_rq_t;

void rq_init(void);
void rq_enqueue(int cpu, int pid);
int rq_pop_local(int cpu);
int rq_steal_once(int self_cpu, int *from_cpu);
int rq_empty(int cpu);
int rq_should_rescan(int cpu);
void rq_note_poll(int cpu);
void rq_stats(int cpu, unsigned long *hits, unsigned long *steals,
              unsigned long *drops);

#endif
