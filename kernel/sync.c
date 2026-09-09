/* sync.c -- Blocking synchronization primitives (roadmap Phase 3.1).
 *
 * Layered on the scheduler (sched.c) and the irqsave spinlocks
 * (spinlock.h).  Deliberately free of other kernel dependencies so the
 * whole file stays host-testable (tests/test_sync.c, `make test-sync`).
 *
 * Design notes, kept visible because they are the teaching content:
 *   - A sleeper marks itself PROC_BLOCKED while holding the queue lock
 *     with interrupts disabled, so the timer-ISR dispatch (which only
 *     picks PROC_READY) can neither lose nor double-schedule it.
 *   - The queue lock is never held across schedule(): wake_up needs the
 *     same lock, and a spinlock must never cross a blocking operation.
 *   - Mutexes have no handoff: unlock wakes one waiter, and the woken
 *     sleeper retries the acquisition loop.  Priority inheritance lifts a
 *     holder to its highest waiter's level (pi_boost/pi_recompute).
 *   - Semaphores wake one waiter per post; broadcasts drain the queue.
 */

#include "sync.h"

#ifdef SYNC_HOST_CURRENT_PID
/* Host unit-test hook (tests/test_sync.c, `make test-sync`): current_pid
 * is mapped to this test global by -Dcurrent_pid=t_cur_pid. */
extern int t_cur_pid;
#endif

void wq_init(wait_queue_t *q) {
    spin_init(&q->lock);
    q->head = WQ_NONE;
    q->tail = WQ_NONE;
}

void sleep_on(wait_queue_t *q) {
    irqflags_t flags;
    spin_lock_irqsave(&q->lock, &flags);
    proc_t *cur = proc_get(current_pid);
    if (!cur) {
        spin_unlock_irqrestore(&q->lock, flags);
        return;
    }
    cur->state = PROC_BLOCKED;
    cur->wq_next = WQ_NONE;
    if (q->head == WQ_NONE) {
        q->head = cur->pid;
        q->tail = cur->pid;
    } else {
        procs[q->tail].wq_next = cur->pid;
        q->tail = cur->pid;
    }
    spin_unlock_irqrestore(&q->lock, flags);
    schedule();
}

int wake_up(wait_queue_t *q) {
    irqflags_t flags;
    spin_lock_irqsave(&q->lock, &flags);
    if (q->head == WQ_NONE) {
        spin_unlock_irqrestore(&q->lock, flags);
        return WQ_NONE;
    }
    int pid = q->head;
    q->head = procs[pid].wq_next;
    if (q->head == WQ_NONE) q->tail = WQ_NONE;
    procs[pid].wq_next = WQ_NONE;
    if (procs[pid].state == PROC_BLOCKED) procs[pid].state = PROC_READY;
    spin_unlock_irqrestore(&q->lock, flags);
    return pid;
}

int wake_up_all(wait_queue_t *q) {
    int n = 0;
    while (wake_up(q) != WQ_NONE) n++;
    return n;
}

void mutex_init(mutex_t *m) {
    spin_init(&m->guard);
    m->locked = 0;
    m->owner = WQ_NONE;
    wq_init(&m->waiters);
}

/* Priority-inheritance state, parallel to procs[] (proc_t size is frozen
 * by the syscall-entry asm). pi_blocked_on stores owner pid + 1 so that
 * zero-initialized memory means "blocks on nobody". All updates happen
 * with the mutex guard held, which already serializes lock/unlock paths;
 * pi_set_base takes the guard of no mutex and races a concurrent boost by
 * at most one stale read, resolved on the next lock/unlock recompute. */
static int pi_base[MAX_PROCS];
static int pi_eff[MAX_PROCS];
static int pi_blocked_on[MAX_PROCS];

static int pi_valid(int pid) {
    return pid >= 0 && pid < MAX_PROCS;
}

static void pi_recompute(int pid);

void pi_set_base(int pid, int prio) {
    if (!pi_valid(pid) || prio < 0) return;
    pi_base[pid] = prio;
    /* Recompute instead of max: lowering a base while donated keeps the
     * live donation, and a fresh assignment never inherits a stale boost
     * from an earlier test or a dead waiter. */
    pi_recompute(pid);
}

int pi_get_eff(int pid) {
    if (!pi_valid(pid)) return -1;
    return pi_eff[pid];
}

static void pi_recompute(int pid) {
    int p, best;
    if (!pi_valid(pid)) return;
    best = pi_base[pid];
    for (p = 0; p < MAX_PROCS; p++) {
        if (pi_blocked_on[p] == pid + 1 && pi_eff[p] > best)
            best = pi_eff[p];
    }
    pi_eff[pid] = best;
}

static void pi_boost(int waiter, int owner) {
    int depth, cur, next;
    if (!pi_valid(waiter) || !pi_valid(owner)) return;
    cur = waiter;
    next = owner;
    for (depth = 0; depth < MAX_PROCS; depth++) {
        if (pi_eff[next] >= pi_eff[cur]) break;
        pi_eff[next] = pi_eff[cur];
        if (!pi_blocked_on[next]) break;
        cur = next;
        next = pi_blocked_on[next] - 1;
        if (!pi_valid(next)) break;
    }
}

/* Record that waiter blocks on this mutex's holder and donate its
 * priority along the chain. Guard must be held. Split out so the host
 * suite drives contention deterministically (a real mutex_lock contender
 * would spin on the host stub scheduler). */
void mutex_note_waiter(mutex_t *m, int waiter) {
    if (pi_valid(waiter) && pi_valid(m->owner)) {
        pi_blocked_on[waiter] = m->owner + 1;
        pi_boost(waiter, m->owner);
    }
}

void mutex_lock(mutex_t *m) {
    for (;;) {
        irqflags_t flags;
        int me;
        spin_lock_irqsave(&m->guard, &flags);
        if (!m->locked) {
            m->locked = 1;
            m->owner = current_pid;
            me = current_pid;
            spin_unlock_irqrestore(&m->guard, flags);
            if (pi_valid(me)) pi_blocked_on[me] = 0;
            return;
        }
        me = current_pid;
        mutex_note_waiter(m, me);
        spin_unlock_irqrestore(&m->guard, flags);
        sleep_on(&m->waiters);
    }
}

int mutex_trylock(mutex_t *m) {
    irqflags_t flags;
    int ok;
    spin_lock_irqsave(&m->guard, &flags);
    if (m->locked) {
        ok = -1;
    } else {
        m->locked = 1;
        m->owner = current_pid;
        ok = 0;
    }
    spin_unlock_irqrestore(&m->guard, flags);
    if (ok == 0 && pi_valid(current_pid)) pi_blocked_on[current_pid] = 0;
    return ok;
}

void mutex_unlock(mutex_t *m) {
    irqflags_t flags;
    int old, q;
    spin_lock_irqsave(&m->guard, &flags);
    old = m->owner;
    m->locked = 0;
    m->owner = WQ_NONE;
    /* Queued waiters stop blocking on the old owner: they retry and
     * re-establish (or clear) their edge on the next acquisition loop,
     * so no stale donation survives the release. */
    q = m->waiters.head;
    while (q != WQ_NONE && pi_valid(q)) {
        int next = procs[q].wq_next;
        pi_blocked_on[q] = 0;
        q = next;
    }
    spin_unlock_irqrestore(&m->guard, flags);
    if (pi_valid(old)) pi_recompute(old);
    wake_up(&m->waiters);
}

void sem_init(sem_t *s, int value) {
    spin_init(&s->guard);
    s->count = value < 0 ? 0 : value;
    wq_init(&s->waiters);
}

void sem_wait(sem_t *s) {
    for (;;) {
        irqflags_t flags;
        spin_lock_irqsave(&s->guard, &flags);
        if (s->count > 0) {
            s->count--;
            spin_unlock_irqrestore(&s->guard, flags);
            return;
        }
        spin_unlock_irqrestore(&s->guard, flags);
        sleep_on(&s->waiters);
    }
}

void sem_post(sem_t *s) {
    irqflags_t flags;
    spin_lock_irqsave(&s->guard, &flags);
    s->count++;
    spin_unlock_irqrestore(&s->guard, flags);
    wake_up(&s->waiters);
}

void cond_init(cond_t *c) {
    wq_init(&c->waiters);
}

void cond_wait(cond_t *c, mutex_t *m) {
    mutex_unlock(m);
    sleep_on(&c->waiters);
    mutex_lock(m);
}

void cond_signal(cond_t *c) {
    wake_up(&c->waiters);
}

void cond_broadcast(cond_t *c) {
    wake_up_all(&c->waiters);
}

void rwlock_init(rwlock_t *rw) {
    spin_init(&rw->guard);
    rw->readers = 0;
    rw->writer = 0;
    wq_init(&rw->waiters);
}

void rwlock_read_lock(rwlock_t *rw) {
    for (;;) {
        irqflags_t flags;
        spin_lock_irqsave(&rw->guard, &flags);
        if (!rw->writer) {
            rw->readers++;
            spin_unlock_irqrestore(&rw->guard, flags);
            return;
        }
        spin_unlock_irqrestore(&rw->guard, flags);
        sleep_on(&rw->waiters);
    }
}

void rwlock_read_unlock(rwlock_t *rw) {
    irqflags_t flags;
    spin_lock_irqsave(&rw->guard, &flags);
    if (rw->readers > 0) rw->readers--;
    int wake = (rw->readers == 0);
    spin_unlock_irqrestore(&rw->guard, flags);
    if (wake) wake_up(&rw->waiters);
}

void rwlock_write_lock(rwlock_t *rw) {
    for (;;) {
        irqflags_t flags;
        spin_lock_irqsave(&rw->guard, &flags);
        if (!rw->writer && rw->readers == 0) {
            rw->writer = 1;
            spin_unlock_irqrestore(&rw->guard, flags);
            return;
        }
        spin_unlock_irqrestore(&rw->guard, flags);
        sleep_on(&rw->waiters);
    }
}

void rwlock_write_unlock(rwlock_t *rw) {
    irqflags_t flags;
    spin_lock_irqsave(&rw->guard, &flags);
    rw->writer = 0;
    spin_unlock_irqrestore(&rw->guard, flags);
    wake_up_all(&rw->waiters);
}
