/* mthreads.h -- Minimal pthread-like threads for MiniOS ELFs (roadmap
 * Phase 1.1, 1:1 model over thread_spawn).
 *
 * A thread is a 1:1 kernel entity (its own proc_t, shared CR3) that starts
 * at fn(arg) on a caller-owned 8 KB stack and dies by exit; the parent
 * reaps it with waitpid, which returns the exit code.  No libc thread
 * support is involved: this header is self-contained on raw syscalls.
 *
 * Rules (single address space, shared everything):
 *   - Allocate all stacks and thread slots BEFORE creating threads.
 *   - After threads start, allocate only under a mutex: brk/mmap are
 *     process-global, so two concurrent allocators corrupt the heap.
 *     In practice that means: printf (which may malloc) only under the
 *     print mutex, and no malloc/mmap in workers at all.
 *   - Mutexes are futex-backed (kernel sleep/wake with a userland fast
 *     path): an uncontended lock/unlock never traps; contention sleeps in
 *     the kernel instead of spinning on yield.  On a kernel without futex
 *     support (ENOSYS) the slow path degrades to spin+yield.
 *   - Condition variables are Mesa-style: always wait in a
 *     while (!predicate) loop, because a wake-up can precede the sleep.
 */

#ifndef MTHREADS_H
#define MTHREADS_H

#include "minios_abi.h"

#define MTHREAD_STACK_SZ 8192
#define MTHREAD_MAX      16

#define MMUTEX_FREE 0
#define MMUTEX_HELD 1
#define MMUTEX_CONTENDED 2
#define MMUTEX_SPINS 100

typedef int mthread_t;   /* slot index; slot holds the kernel pid */

typedef struct {
    volatile int locked; /* 0 = free, 1 = held */
} mmutex_t;

typedef struct {
    void *(*fn)(void *);
    void *arg;
    void *retval;
    int pid;             /* kernel pid, -1 when free */
    int used;
} mthread_slot_t;

static inline long m_syscall6(long n, long a, long b, long c) {
    long r;
    __asm__ volatile("syscall"
                     : "=a"(r)
                     : "a"(n), "D"(a), "S"(b), "d"(c)
                     : "rcx", "r11", "memory");
    return r;
}

static inline void myield(void) {
    m_syscall6(MINIOS_SYS_SCHED_YIELD, 0, 0, 0);
}

static inline long mfutex_wait(volatile int *addr, int val) {
    return m_syscall6(MINIOS_SYS_FUTEX_WAIT, (long)addr, val, 0);
}

static inline long mfutex_wake(volatile int *addr, int n) {
    return m_syscall6(MINIOS_SYS_FUTEX_WAKE, (long)addr, n, 0);
}

static inline void mmutex_init(mmutex_t *m) {
    m->locked = MMUTEX_FREE;
}

static inline void mmutex_lock(mmutex_t *m) {
    int spins = 0;
    while (__sync_lock_test_and_set(&m->locked, MMUTEX_HELD) != MMUTEX_FREE) {
        if (++spins < MMUTEX_SPINS)
            continue;
        if (__sync_lock_test_and_set(&m->locked, MMUTEX_CONTENDED) == MMUTEX_FREE)
            return;
        if (mfutex_wait(&m->locked, MMUTEX_CONTENDED) == -38) {
            while (m->locked != MMUTEX_FREE)
                myield();
        }
        spins = 0;
    }
}

static inline void mmutex_unlock(mmutex_t *m) {
    int old = __sync_lock_test_and_set(&m->locked, MMUTEX_FREE);
    if (old == MMUTEX_CONTENDED)
        mfutex_wake(&m->locked, 1);
}

/* Thread entry trampoline: runs fn(arg), stores the return, exits 0.
 * The exit code is always 0; join reads retval from the shared slot. */
static void mthread_entry(void *p) {
    mthread_slot_t *s = (mthread_slot_t *)p;
    s->retval = s->fn(s->arg);
    m_syscall6(MINIOS_SYS_EXIT, 0, 0, 0);
    for (;;)
        ;
}

/* Slot storage lives here: single-TU use (one instance per binary).
 * Stacks are 16-aligned; the TOP is passed to the kernel (stacks grow
 * down, and the SysV ABI needs 16-byte alignment at call time). */
static mthread_slot_t mthread_slots[MTHREAD_MAX];
static char mthread_stacks[MTHREAD_MAX][MTHREAD_STACK_SZ]
    __attribute__((aligned(16)));

static int mthread_create(mthread_t *t, void *(*fn)(void *), void *arg) {
    int i;
    for (i = 0; i < MTHREAD_MAX; i++)
        if (!mthread_slots[i].used)
            break;
    if (i >= MTHREAD_MAX)
        return -1;
    mthread_slots[i].fn = fn;
    mthread_slots[i].arg = arg;
    mthread_slots[i].retval = 0;
    mthread_slots[i].used = 1;
    long stack_top = (long)(mthread_stacks[i] + MTHREAD_STACK_SZ);
    long pid = m_syscall6(MINIOS_SYS_THREAD_SPAWN, (long)mthread_entry,
                          stack_top, (long)&mthread_slots[i]);
    if (pid < 0) {
        mthread_slots[i].used = 0;
        return -1;
    }
    mthread_slots[i].pid = (int)pid;
    *t = i;
    return 0;
}

static int mthread_join(mthread_t t, void **retval) {
    if (t < 0 || t >= MTHREAD_MAX || !mthread_slots[t].used)
        return -1;
    long code = m_syscall6(MINIOS_SYS_WAIT4, mthread_slots[t].pid, 0, 0);
    __sync_synchronize();
    if (retval)
        *retval = mthread_slots[t].retval;
    mthread_slots[t].used = 0;
    return (int)code;
}

#endif
