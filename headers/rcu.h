#ifndef RCU_H
#define RCU_H

/** Docstring: rcu.h -- Read-copy-update, lite epoch edition.
 *
 * Problem addressed: shared locks on read-mostly data (configuration
 * snapshots, diagnostic counters, published pointers) serialize readers
 * that never conflict with each other. A global spinlock on a hot read
 * path costs a cache-line bounce per reader per read.
 *
 * Design:
 * Readers bracket access with rcu_read_lock / rcu_read_unlock and never
 * take a lock; writers publish with rcu_publish (single pointer store)
 * and retire the old version with rcu_call, whose callback runs only
 * after a grace period. A grace period ends when every CPU has reported
 * a quiescent state past the current epoch. Quiescent states are the
 * system's natural schedule points: the timer tick and the idle loop
 * already run at 100 Hz, so rcu_note_tick and rcu_note_idle feed them in
 * with no new interrupt source. Grace latency is therefore bounded by a
 * small multiple of the tick period, which suits rare writers.
 *
 * Nesting and preemption:
 * Read sections nest through a per-CPU depth counter; only the outermost
 * exit matters. Read sections never block: sleeping inside one delays
 * grace periods for every writer, so blocking there is a contract
 * violation, caught in debug builds by the depth check in rcu_call.
 *
 * Bounds and failure modes, all fail-closed:
 * The callback queue holds RCU_CB_MAX entries; a full queue refuses the
 * retirement (the writer keeps ownership) instead of dropping the free.
 * Callbacks run in tick context with interrupts disabled, so they must
 * be short and non-blocking. rcu_synchronize spins on quiescent reports
 * with a bounded poll count (RCU_SYNC_SPINS); expiry returns
 * RCU_ERR_TIMEOUT instead of hanging the writer.
 */

#include <stdint.h>

#include "spinlock.h"
#include "sched.h"

#define RCU_CB_MAX 32
#define RCU_SYNC_SPINS 1000000UL

#define RCU_OK 0
#define RCU_ERR_FULL (-1)
#define RCU_ERR_TIMEOUT (-2)

typedef void (*rcu_cb_t)(void *arg);

void rcu_init(void);
void rcu_read_lock(void);
void rcu_read_unlock(void);
void *rcu_deref(void *volatile *pp);
void rcu_publish(void *volatile *pp, void *v);
long rcu_call(rcu_cb_t fn, void *arg);
void rcu_note_tick(int cpu);
void rcu_note_idle(int cpu);
void rcu_poll(void);
long rcu_synchronize(void);

#endif
