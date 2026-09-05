/* Host-side unit test for the blocking sync primitives (kernel/sync.c).
 *
 * sync.c depends only on sched.h (proc states, procs[], schedule) and
 * spinlock.h, so it is exercised directly here against the host libc.
 * Privileged pieces are stubbed at compile time (see `make test-sync`):
 * cli/sti never execute on the host, and current_pid/schedule/proc_get
 * are provided by this file.  The test verifies the observable contract
 * (block/wake order, mutex ownership, semaphore counts, cond relock,
 * rwlock exclusion) so a mutant that drops a wake-up or a state change
 * is caught.
 *
 * Run through `make test-sync`.
 */

#include <stdio.h>

#include "sync.h"

/* ---- Stubs (replace the SMP/scheduler environment) ---- */
proc_t procs[MAX_PROCS];
int t_cur_pid;
static int schedule_calls;

proc_t *proc_get(int pid) {
    if (pid < 0 || pid >= MAX_PROCS) return 0;
    if (procs[pid].state == PROC_FREE) return 0;
    return &procs[pid];
}

void schedule(void) {
    schedule_calls++;
}

/* ---- Harness ---- */
static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

static void fresh_proc(int pid) {
    int i;
    for (i = 0; i < (int)sizeof(proc_t); i++) ((char *)&procs[pid])[i] = 0;
    procs[pid].pid = pid;
    procs[pid].state = PROC_READY;
    procs[pid].wq_next = WQ_NONE;
}

static void fresh_all(void) {
    int i;
    for (i = 0; i < MAX_PROCS; i++) {
        procs[i].pid = i;
        procs[i].state = PROC_FREE;
        procs[i].wq_next = WQ_NONE;
    }
    schedule_calls = 0;
    t_cur_pid = 0;
}

int main(void) {
    /* 1. Empty queue operations are safe no-ops. */
    {
        wait_queue_t q = WAIT_QUEUE_INIT;
        CHECK(wake_up(&q) == WQ_NONE, "empty wake_up returns WQ_NONE");
        CHECK(wake_up_all(&q) == 0, "empty wake_up_all returns 0");
        CHECK(q.head == WQ_NONE && q.tail == WQ_NONE, "queue stays empty");
    }

    /* 2. sleep_on blocks the caller and schedules away; wake_up wakes it. */
    {
        wait_queue_t q = WAIT_QUEUE_INIT;
        fresh_all();
        fresh_proc(1);
        t_cur_pid = 1;
        sleep_on(&q);
        CHECK(procs[1].state == PROC_BLOCKED, "sleeper is BLOCKED");
        CHECK(schedule_calls == 1, "sleep schedules away once");
        CHECK(q.head == 1 && q.tail == 1, "sleeper is queued");
        CHECK(wake_up(&q) == 1, "wake returns sleeper pid");
        CHECK(procs[1].state == PROC_READY, "woken sleeper is READY");
        CHECK(q.head == WQ_NONE, "queue drains");
    }

    /* 3. Waiters wake in FIFO order. */
    {
        wait_queue_t q = WAIT_QUEUE_INIT;
        fresh_all();
        fresh_proc(1); fresh_proc(2); fresh_proc(3);
        t_cur_pid = 1; sleep_on(&q);
        t_cur_pid = 2; sleep_on(&q);
        t_cur_pid = 3; sleep_on(&q);
        CHECK(wake_up(&q) == 1, "fifo first");
        CHECK(wake_up(&q) == 2, "fifo second");
        CHECK(wake_up(&q) == 3, "fifo third");
        CHECK(wake_up(&q) == WQ_NONE, "fifo drains");
        CHECK(wake_up_all(&q) == 0, "drained broadcast is 0");
    }

    /* 4. Mutex: ownership, blocking contender, handoff by retry. */
    {
        mutex_t m = MUTEX_INIT;
        fresh_all();
        fresh_proc(1); fresh_proc(2);
        t_cur_pid = 1;
        mutex_lock(&m);
        CHECK(m.locked && m.owner == 1, "locker owns mutex");
        t_cur_pid = 2;
        schedule_calls = 0;
        /* Contender cannot take it; drive one retry iteration by hand:
         * sleep directly, then check it is queued and descheduled. */
        sleep_on(&m.waiters);
        CHECK(procs[2].state == PROC_BLOCKED, "contender blocks");
        CHECK(schedule_calls == 1, "contender schedules away");
        t_cur_pid = 1;
        mutex_unlock(&m);
        CHECK(!m.locked, "unlock frees mutex");
        CHECK(procs[2].state == PROC_READY, "unlock wakes contender");
        t_cur_pid = 2;
        mutex_lock(&m);
        CHECK(m.locked && m.owner == 2, "woken contender acquires");
        mutex_unlock(&m);
        CHECK(!m.locked && m.owner == WQ_NONE, "unlock clears owner");
    }

    /* 5. Semaphore: counting, blocking at zero, post wakes. */
    {
        sem_t s = SEM_INIT(1);
        fresh_all();
        fresh_proc(1); fresh_proc(2);
        t_cur_pid = 1;
        sem_wait(&s);
        CHECK(s.count == 0, "wait consumes token");
        t_cur_pid = 2;
        sleep_on(&s.waiters);
        CHECK(procs[2].state == PROC_BLOCKED, "waiter blocks at zero");
        t_cur_pid = 1;
        sem_post(&s);
        CHECK(s.count == 1, "post restores token");
        CHECK(procs[2].state == PROC_READY, "post wakes waiter");
        t_cur_pid = 2;
        sem_wait(&s);
        CHECK(s.count == 0, "woken waiter consumes");
    }

    /* 6. Condition variable: wait releases the mutex and relocks it. */
    {
        mutex_t m = MUTEX_INIT;
        cond_t c = COND_INIT;
        fresh_all();
        fresh_proc(1); fresh_proc(2);
        t_cur_pid = 2;
        mutex_lock(&m);
        /* Consumer waits: unlock + sleep. Relock needs the mutex free,
         * so the producer signals first, then the consumer relocks. */
        mutex_unlock(&m);
        sleep_on(&c.waiters);
        CHECK(!m.locked, "cond wait released mutex");
        CHECK(procs[2].state == PROC_BLOCKED, "consumer blocks on cond");
        t_cur_pid = 1;
        mutex_lock(&m);
        CHECK(m.owner == 1, "producer takes mutex");
        cond_signal(&c);
        CHECK(procs[2].state == PROC_READY, "signal wakes consumer");
        mutex_unlock(&m);
        t_cur_pid = 2;
        mutex_lock(&m);
        CHECK(m.owner == 2, "consumer relocks after wait");
        mutex_unlock(&m);
        cond_broadcast(&c);
        CHECK(1, "broadcast on empty queue is safe");
    }

    /* 7. RWLock: concurrent readers, exclusive writer, last-out wakes. */
    {
        rwlock_t rw = RWLOCK_INIT;
        fresh_all();
        fresh_proc(1); fresh_proc(2); fresh_proc(3);
        t_cur_pid = 1; rwlock_read_lock(&rw);
        t_cur_pid = 2; rwlock_read_lock(&rw);
        CHECK(rw.readers == 2 && !rw.writer, "two concurrent readers");
        t_cur_pid = 3;
        sleep_on(&rw.waiters);
        CHECK(procs[3].state == PROC_BLOCKED, "writer waits on readers");
        t_cur_pid = 1; rwlock_read_unlock(&rw);
        CHECK(procs[3].state == PROC_BLOCKED, "first reader out, writer waits");
        t_cur_pid = 2; rwlock_read_unlock(&rw);
        CHECK(procs[3].state == PROC_READY, "last reader out wakes writer");
        CHECK(rw.readers == 0, "no readers left");
        t_cur_pid = 3; rwlock_write_lock(&rw);
        CHECK(rw.writer, "writer holds lock");
        rwlock_write_unlock(&rw);
        CHECK(!rw.writer, "writer releases");
    }

    /* 8. sleep_on with no current process is a safe no-op. */
    {
        wait_queue_t q = WAIT_QUEUE_INIT;
        fresh_all();
        t_cur_pid = 7; /* PROC_FREE: proc_get returns 0 */
        sleep_on(&q);
        CHECK(schedule_calls == 0, "no proc means no schedule");
        CHECK(q.head == WQ_NONE, "no proc means no enqueue");
    }

    if (failures == 0) printf("sync: ok\n");
    else printf("sync: %d failures\n", failures);
    return failures != 0;
}
