/* fptest.c -- FPU/SSE context-switch probe (Phase 0.1, ADR-0014).
 *
 * Two threads grind distinct floating-point constants through thousands
 * of iterations with yields (voluntary switches) while the 100 Hz timer
 * preempts them underneath (involuntary switches; the AP too under
 * -smp 2). Each thread compares its accumulator against a serially
 * computed expected value: any lost XMM/x87 register on a switch changes
 * the bits and the run reports FAIL. SSE2 doubles and x87 long doubles
 * are both covered, and every thread asserts its MXCSR control bits still
 * equal the main thread's, so a clobbered control word is caught too.
 *
 * Discipline: workers never touch stdio. Threads share one address
 * space, so they share glibc's stdout buffer: two workers printf'ing
 * concurrently duplicate lines, which looks exactly like a thread
 * running twice. Workers record into per-thread slots; only main prints,
 * after both joins. The stack-alignment canary is an explicit movaps to
 * a 16-aligned stack slot: the entry stack must satisfy SysV (see
 * mthreads.h), and a misaligned stack faults here with #GP, killing the
 * worker with -14 instead of silently misrounding later.
 *
 * The same run smokes gettid (Phase 0.4: the two workers must observe
 * distinct tids, never the constant 1) and getrandom (Phase 0.5: it
 * must fill the buffer and report the count, never EFAULT).
 *
 * FP state is thread-local by construction: only one integer arg crosses
 * the thread entry (the spawn contract carries no XMM registers), the
 * constants live inside the workers.
 *
 * Build with the host toolchain (`make progs/bin/fptest`, static, like
 * thdemo); it ships on MiniFS. Usage: run bin/fptest (or fptest).
 */

#include <stdio.h>

#include "mthreads.h"
#include "minios_abi.h"

#define FP_ITERS 4000

static unsigned int main_mxcsr;

static unsigned int read_mxcsr(void) {
    unsigned int v;
    __asm__ volatile("stmxcsr %0" : "=m"(v));
    return v;
}

static long raw_gettid(void) {
    return m_syscall6(MINIOS_SYS_GETTID, 0, 0, 0);
}

static long raw_getrandom(void *buf, unsigned long n) {
    return m_syscall6(MINIOS_SYS_GETRANDOM, (long)buf, (long)n, 0);
}

typedef struct {
    volatile long tid;
    volatile int done;
    volatile int fail;
    volatile double acc;
    volatile double exp_d;
    volatile long double lacc;
    volatile long double lexp;
    volatile unsigned int mxcsr;
} fp_slot_t;

static fp_slot_t slots[2];
static volatile int worker_fail;
static volatile long worker_tid[2];
static volatile int worker_tails;

/* Stack-alignment canary: an aligned SSE store to a stack slot faults
 * with #GP unless the thread entry stack satisfies SysV (rsp%16==8 at
 * entry, 16-aligned after the call prologue). Compiler spills
 * would only sometimes touch the misaligned area; this faults
 * deterministically. A fault kills the worker with -14, which the join
 * reports instead of a silent wrong answer. */
static void stack_align_canary(void) {
    char tmp[32] __attribute__((aligned(16)));
    __asm__ volatile("movaps %%xmm0, %0" :: "m"(tmp) : "memory");
    __asm__ volatile("" ::: "memory");
}

static void *worker(void *p) {
    volatile unsigned long canary = 0x123456789ABCDEFUL;
    long id = (long)p;
    void *entry_p = p;
    volatile double acc = (id == 0) ? 1.25 : 2.5;
    volatile double step = (id == 0) ? 1.000001 : 1.000002;
    volatile long double lacc = (id == 0) ? 3.75L : 5.125L;
    volatile long double lstep = (id == 0) ? 1.0000005L : 1.0000007L;
    /* exp_d/exp_ld/s/ls are PLAIN locals: the compiler keeps them in
     * XMM/x87 registers across myield(), so any FPU state lost on a
     * switch corrupts them while acc/lacc (volatile, memory) survive.
     * If a failure ever reproduces with everything volatile, the
     * corruption is in GPRs/stack, not FPU. */
    double exp_d = (id == 0) ? 1.25 : 2.5;
    long double exp_ld = (id == 0) ? 3.75L : 5.125L;
    double s = step;
    long double ls = lstep;
    int i;
    int fail = 0;

    stack_align_canary();
    slots[id].tid = raw_gettid();
    worker_tid[id] = slots[id].tid;
    slots[id].done = 0;
    for (i = 0; i < FP_ITERS; i++) {
        acc = acc * s + (double)id + 0.125;
        lacc = lacc * ls + (long double)id + 0.0625L;
        exp_d = exp_d * s + (double)id + 0.125;
        exp_ld = exp_ld * ls + (long double)id + 0.0625L;
        if ((i & 15) == 15) {
            if (canary != 0x123456789ABCDEFUL)
                fail |= 8;
            if (p != entry_p || (long)p != id)
                fail |= 16;
            myield();
        }
    }
    slots[id].acc = acc;
    slots[id].exp_d = exp_d;
    slots[id].lacc = lacc;
    slots[id].lexp = exp_ld;
    slots[id].mxcsr = read_mxcsr();
    /* MXCSR carries sticky status flags (PE/UE/OE/ZE/DE/IE) that
     * legitimate FP math sets; only the control bits (masks, rounding,
     * FTZ/DAZ) must survive a switch. Comparing the whole word would
     * fail two threads that took different arithmetic paths. */
    if ((slots[id].mxcsr & 0xFFC0u) != (main_mxcsr & 0xFFC0u))
        fail |= 1;
    if (acc != exp_d)
        fail |= 2;
    if (lacc != exp_ld)
        fail |= 4;
    if (canary != 0x123456789ABCDEFUL)
        fail |= 8;
    if (id < 0 || id > 1)
        fail |= 32;
    slots[id].fail = fail;
    if (fail)
        worker_fail = 1;
    __sync_fetch_and_add(&worker_tails, 1);
    slots[id].done = 1;
    return (void *)(long)(fail ? 1 : 0);
}

int main(void) {
    mthread_t t0, t1;
    void *r0 = 0, *r1 = 0;
    int j0, j1;
    unsigned char rnd[8];
    long rn;
    int k;

    main_mxcsr = read_mxcsr();
    worker_fail = 0;
    worker_tails = 0;
    slots[0].done = slots[1].done = 0;
    slots[0].fail = slots[1].fail = 0;
    worker_tid[0] = worker_tid[1] = 0;
    for (k = 0; k < 8; k++) rnd[k] = 0;
    rn = raw_getrandom(rnd, 8);
    if (rn != 8) {
        printf("fptest: FAIL (getrandom=%ld)\n", rn);
        return 1;
    }
    if (mthread_create(&t0, worker, (void *)0) != 0) {
        printf("fptest: FAIL (spawn 0)\n");
        return 1;
    }
    if (mthread_create(&t1, worker, (void *)1) != 0) {
        printf("fptest: FAIL (spawn 1)\n");
        return 1;
    }
    j0 = mthread_join(t0, &r0);
    j1 = mthread_join(t1, &r1);
    if (j0 != 0 || j1 != 0 || r0 != 0 || r1 != 0 || worker_fail) {
        printf("fptest: FAIL (j0=%d j1=%d r0=%ld r1=%ld code %d %d)\n",
               j0, j1, (long)r0, (long)r1, slots[0].fail, slots[1].fail);
        printf("fptest: w0 acc=%a exp=%a\n",
               (double)slots[0].acc, (double)slots[0].exp_d);
        printf("fptest: w1 acc=%a exp=%a\n",
               (double)slots[1].acc, (double)slots[1].exp_d);
        return 1;
    }
    if (worker_tid[0] == worker_tid[1] || worker_tid[0] <= 0) {
        printf("fptest: FAIL (tids %ld %ld)\n",
               worker_tid[0], worker_tid[1]);
        return 1;
    }
    if (worker_tails != 2 || !slots[0].done || !slots[1].done) {
        printf("fptest: FAIL (tails=%d done %d %d)\n",
               worker_tails, slots[0].done, slots[1].done);
        return 1;
    }
    printf("fptest: ok (2 threads x %d iters, mxcsr=%08x, tids %ld %ld)\n",
           FP_ITERS, main_mxcsr, worker_tid[0], worker_tid[1]);
    return 0;
}
