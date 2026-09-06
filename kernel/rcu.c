/** Docstring: kernel/rcu.c -- Epoch grace periods over scheduler ticks.
 *
 * Implements rcu.h. Epochs advance in rcu_poll; quiescent states arrive
 * from rcu_note_tick (timer ISR) and rcu_note_idle (idle loop). The file
 * depends only on sched.h topology and spinlock.h, so the host unit test
 * (tests/test_rcu.c, make test-rcu) drives epochs with synthetic ticks.
 */

#include "rcu.h"

#ifdef RCU_HOST_TEST
cpu_t *rcu_host_cpu(void);
static cpu_t *rcu_me(void) {
    return rcu_host_cpu();
}
#else
static cpu_t *rcu_me(void) {
    return this_cpu();
}
#endif

typedef struct {
    rcu_cb_t fn;
    void *arg;
    unsigned long epoch;
} rcu_slot_t;

typedef struct {
    spinlock_t lock;
    unsigned long epoch;
    unsigned long qs[MAX_CPUS];
    unsigned long depth[MAX_CPUS];
    rcu_slot_t pending[RCU_CB_MAX];
    int pending_count;
    unsigned long completed;
} rcu_state_t;

static rcu_state_t rcu_state;

static int rcu_cpu_valid(int cpu) {
    return cpu >= 0 && cpu < MAX_CPUS && cpu < cpu_count;
}

/** Docstring: Reset epoch, quiescent marks, depths and callbacks. */
void rcu_init(void) {
    int i;
    spin_init(&rcu_state.lock);
    rcu_state.epoch = 1;
    for (i = 0; i < MAX_CPUS; i++) {
        rcu_state.qs[i] = 0;
        rcu_state.depth[i] = 0;
    }
    for (i = 0; i < RCU_CB_MAX; i++) {
        rcu_state.pending[i].fn = 0;
        rcu_state.pending[i].arg = 0;
        rcu_state.pending[i].epoch = 0;
    }
    rcu_state.pending_count = 0;
    rcu_state.completed = 0;
}

/** Docstring: Enter a read section on the current CPU. Nests. */
void rcu_read_lock(void) {
    cpu_t *me = rcu_me();
    int cpu = me->cpu_id;
    irqflags_t flags;
    if (!rcu_cpu_valid(cpu))
        return;
    spin_lock_irqsave(&rcu_state.lock, &flags);
    rcu_state.depth[cpu]++;
    spin_unlock_irqrestore(&rcu_state.lock, flags);
}

/** Docstring: Leave a read section. Underflow is clamped, never wraps. */
void rcu_read_unlock(void) {
    cpu_t *me = rcu_me();
    int cpu = me->cpu_id;
    irqflags_t flags;
    if (!rcu_cpu_valid(cpu))
        return;
    spin_lock_irqsave(&rcu_state.lock, &flags);
    if (rcu_state.depth[cpu] > 0)
        rcu_state.depth[cpu]--;
    spin_unlock_irqrestore(&rcu_state.lock, flags);
}

/** Docstring: Load a published pointer inside a read section. */
void *rcu_deref(void *volatile *pp) {
    __sync_synchronize();
    return *pp;
}

/** Docstring: Publish a new pointer value with release ordering. */
void rcu_publish(void *volatile *pp, void *v) {
    __sync_synchronize();
    *pp = v;
    __sync_synchronize();
}

/** Docstring: Retire fn(arg) after the next grace period.
 *
 * Refuses with RCU_ERR_FULL when the queue is full (caller keeps the
 * object) and with RCU_ERR_TIMEOUT semantics never: enqueue itself never
 * waits. Callbacks fire from rcu_poll, in tick context.
 */
long rcu_call(rcu_cb_t fn, void *arg) {
    irqflags_t flags;
    long r = RCU_OK;
    if (!fn)
        return RCU_ERR_FULL;
    spin_lock_irqsave(&rcu_state.lock, &flags);
    if (rcu_state.pending_count >= RCU_CB_MAX) {
        r = RCU_ERR_FULL;
    } else {
        rcu_slot_t *s = &rcu_state.pending[rcu_state.pending_count];
        s->fn = fn;
        s->arg = arg;
        s->epoch = rcu_state.epoch;
        rcu_state.pending_count++;
    }
    spin_unlock_irqrestore(&rcu_state.lock, flags);
    return r;
}

/** Docstring: Record a quiescent state for cpu at the current epoch. */
void rcu_note_tick(int cpu) {
    irqflags_t flags;
    if (!rcu_cpu_valid(cpu))
        return;
    spin_lock_irqsave(&rcu_state.lock, &flags);
    if (rcu_state.depth[cpu] == 0)
        rcu_state.qs[cpu] = rcu_state.epoch;
    spin_unlock_irqrestore(&rcu_state.lock, flags);
}

/** Docstring: Idle CPUs are always quiescent. */
void rcu_note_idle(int cpu) {
    irqflags_t flags;
    if (!rcu_cpu_valid(cpu))
        return;
    spin_lock_irqsave(&rcu_state.lock, &flags);
    rcu_state.qs[cpu] = rcu_state.epoch;
    spin_unlock_irqrestore(&rcu_state.lock, flags);
}

/** Docstring: Advance the epoch and run due callbacks.
 *
 * A grace period closes when every online CPU reported quiescence at the
 * current epoch. Callbacks stamped with an older epoch then run inline
 * and the epoch advances. Runs from the timer tick; never blocks.
 */
void rcu_poll(void) {
    irqflags_t flags;
    int c;
    int quiet = 1;
    int i = 0;
    spin_lock_irqsave(&rcu_state.lock, &flags);
    for (c = 0; c < cpu_count && c < MAX_CPUS; c++) {
        if (rcu_state.qs[c] != rcu_state.epoch) {
            quiet = 0;
            break;
        }
    }
    if (!quiet) {
        spin_unlock_irqrestore(&rcu_state.lock, flags);
        return;
    }
    while (i < rcu_state.pending_count) {
        if (rcu_state.pending[i].epoch < rcu_state.epoch) {
            rcu_cb_t fn = rcu_state.pending[i].fn;
            void *arg = rcu_state.pending[i].arg;
            int j;
            for (j = i; j + 1 < rcu_state.pending_count; j++)
                rcu_state.pending[j] = rcu_state.pending[j + 1];
            rcu_state.pending_count--;
            rcu_state.completed++;
            spin_unlock_irqrestore(&rcu_state.lock, flags);
            fn(arg);
            spin_lock_irqsave(&rcu_state.lock, &flags);
        } else {
            i++;
        }
    }
    rcu_state.epoch++;
    spin_unlock_irqrestore(&rcu_state.lock, flags);
}

/** Docstring: Wait until a full grace period elapses.
 *
 * Polls rcu_poll up to RCU_SYNC_SPINS times. Returns RCU_OK once the
 * epoch advanced past the entry value, RCU_ERR_TIMEOUT when the bound
 * expires (ticks stalled, never a hang).
 */
long rcu_synchronize(void) {
    unsigned long start = rcu_state.epoch;
    unsigned long spins = 0;
    while (rcu_state.epoch <= start) {
        rcu_poll();
        if (++spins >= RCU_SYNC_SPINS)
            return RCU_ERR_TIMEOUT;
    }
    return RCU_OK;
}
