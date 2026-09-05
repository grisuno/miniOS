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
 *     sleeper retries the acquisition loop.  No priority inheritance.
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

void mutex_lock(mutex_t *m) {
    for (;;) {
        irqflags_t flags;
        spin_lock_irqsave(&m->guard, &flags);
        if (!m->locked) {
            m->locked = 1;
            m->owner = current_pid;
            spin_unlock_irqrestore(&m->guard, flags);
            return;
        }
        spin_unlock_irqrestore(&m->guard, flags);
        sleep_on(&m->waiters);
    }
}

void mutex_unlock(mutex_t *m) {
    irqflags_t flags;
    spin_lock_irqsave(&m->guard, &flags);
    m->locked = 0;
    m->owner = WQ_NONE;
    spin_unlock_irqrestore(&m->guard, flags);
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
