/** Docstring: Host test for kernel/futex.c (make test-futex).
 *
 * Compiles the kernel implementation against host stubs for the process
 * table, current_pid and schedule, the same harness shape as
 * tests/test_sync.c. Verifies the observable contract: mismatch never
 * sleeps, matching waits block and schedule away, wake selects by address
 * only, counts bound the wake, and degenerate inputs are safe no-ops.
 */

#include <stdio.h>

#include "futex.h"

proc_t procs[MAX_PROCS];
int t_cur_pid;
static int schedule_calls;

proc_t *proc_get(int pid) {
    if (pid < 0 || pid >= MAX_PROCS)
        return 0;
    if (procs[pid].state == PROC_FREE)
        return 0;
    return &procs[pid];
}

void schedule(void) {
    schedule_calls++;
}

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

static void fresh_proc(int pid) {
    int i;
    for (i = 0; i < (int)sizeof(proc_t); i++)
        ((char *)&procs[pid])[i] = 0;
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
    futex_init();
}

int main(void) {
    static int word_a;
    static int word_b;
    {
        fresh_all();
        fresh_proc(1);
        t_cur_pid = 1;
        word_a = 5;
        CHECK(futex_wait((unsigned long)&word_a, 6) == FUTEX_NOMATCH,
              "mismatch returns NOMATCH");
        CHECK(procs[1].state == PROC_READY, "mismatch never blocks");
        CHECK(schedule_calls == 0, "mismatch never schedules");
    }
    {
        fresh_all();
        fresh_proc(1);
        t_cur_pid = 1;
        word_a = 7;
        CHECK(futex_wait((unsigned long)&word_a, 7) == FUTEX_OK,
              "matching wait sleeps");
        CHECK(procs[1].state == PROC_BLOCKED, "waiter is BLOCKED");
        CHECK(schedule_calls == 1, "wait schedules away once");
        CHECK(futex_wake((unsigned long)&word_a, 1) == 1,
              "wake reports one thread");
        CHECK(procs[1].state == PROC_READY, "woken waiter is READY");
        CHECK(futex_wake((unsigned long)&word_a, 1) == 0,
              "second wake finds nobody");
    }
    {
        fresh_all();
        fresh_proc(1);
        fresh_proc(2);
        word_a = 1;
        word_b = 1;
        t_cur_pid = 1;
        futex_wait((unsigned long)&word_a, 1);
        t_cur_pid = 2;
        futex_wait((unsigned long)&word_b, 1);
        CHECK(futex_wake((unsigned long)&word_a, 10) == 1,
              "wake selects by address");
        CHECK(procs[1].state == PROC_READY, "matching waiter wakes");
        CHECK(procs[2].state == PROC_BLOCKED, "other address sleeps on");
        CHECK(futex_wake((unsigned long)&word_b, 10) == 1,
              "second address wakes separately");
        CHECK(procs[2].state == PROC_READY, "second waiter wakes");
    }
    {
        fresh_all();
        fresh_proc(1);
        fresh_proc(2);
        fresh_proc(3);
        word_a = 9;
        t_cur_pid = 1;
        futex_wait((unsigned long)&word_a, 9);
        t_cur_pid = 2;
        futex_wait((unsigned long)&word_a, 9);
        t_cur_pid = 3;
        futex_wait((unsigned long)&word_a, 9);
        CHECK(futex_wake((unsigned long)&word_a, 2) == 2,
              "wake count bounds the wake");
        CHECK(procs[1].state == PROC_READY, "first waiter wakes");
        CHECK(procs[2].state == PROC_READY, "second waiter wakes");
        CHECK(procs[3].state == PROC_BLOCKED, "third waiter stays");
        CHECK(futex_wake((unsigned long)&word_a, FUTEX_WAKE_ALL) == 1,
              "wake-all drains the rest");
        CHECK(procs[3].state == PROC_READY, "drained waiter wakes");
    }
    {
        fresh_all();
        word_a = 3;
        t_cur_pid = 7;
        CHECK(futex_wait((unsigned long)&word_a, 3) == FUTEX_NOPROC,
              "no proc returns NOPROC");
        CHECK(schedule_calls == 0, "no proc never schedules");
        CHECK(futex_wake((unsigned long)&word_a, 0) == 0,
              "zero count wakes nothing");
        CHECK(futex_wake((unsigned long)&word_a, -5) == 0,
              "negative count wakes nothing");
    }
    {
        /* Linux op decode for syscall 202 (the retired TLS_SEND number):
         * WAIT/WAKE served, PRIVATE masked, everything else refused.
         * This is what keeps glibc's NPTL alive in-guest: a WAKE|PRIVATE
         * from getaddrinfo must decode to WAKE, never -1 (which the old
         * stub turned into the fatal -ENOSYS). */
        CHECK(futex_linux_cmd(0) == 0, "WAIT decodes");
        CHECK(futex_linux_cmd(1) == 1, "WAKE decodes");
        CHECK(futex_linux_cmd(128) == 0, "WAIT|PRIVATE decodes");
        CHECK(futex_linux_cmd(129) == 1, "WAKE|PRIVATE decodes");
        CHECK(futex_linux_cmd(2) == -1, "REQUEUE refused");
        CHECK(futex_linux_cmd(5) == -1, "WAKE_OP refused");
        CHECK(futex_linux_cmd(-1) == -1, "negative op refused");
        /* Bitset ops (glibc condition variables and timed waits) decode,
         * with PRIVATE and CLOCK_REALTIME masked (393 = 9|128|256). */
        CHECK(futex_linux_cmd(9) == LINUX_FUTEX_WAIT_BITSET, "WAIT_BITSET decodes");
        CHECK(futex_linux_cmd(10) == LINUX_FUTEX_WAKE_BITSET, "WAKE_BITSET decodes");
        CHECK(futex_linux_cmd(137) == LINUX_FUTEX_WAIT_BITSET, "WAIT_BITSET|PRIVATE decodes");
        CHECK(futex_linux_cmd(393) == LINUX_FUTEX_WAIT_BITSET, "WAIT_BITSET|PRIVATE|REALTIME decodes");
        CHECK(futex_linux_cmd(256) == LINUX_FUTEX_WAIT, "WAIT|REALTIME decodes");
        CHECK(futex_linux_cmd(1024 | 9) == -1, "unknown flag refused");
    }
    {
        /* Timeout arithmetic: relative for WAIT, absolute for WAIT_BITSET;
         * invalid timespecs refused; huge seconds never overflow. */
        long r;
        CHECK(futex_timeout_remaining_us(LINUX_FUTEX_WAIT, 0, 500000, 1000) == 500,
              "relative 0.5 ms");
        CHECK(futex_timeout_remaining_us(LINUX_FUTEX_WAIT, 2, 0, 99) == 2000000,
              "relative ignores now");
        CHECK(futex_timeout_remaining_us(LINUX_FUTEX_WAIT_BITSET, 3, 0, 1000000) == 2000000,
              "absolute minus now");
        r = futex_timeout_remaining_us(LINUX_FUTEX_WAIT_BITSET, 1, 0, 5000000);
        CHECK(r <= 0 && r != FUTEX_TIMEOUT_INVALID, "past deadline expired");
        CHECK(futex_timeout_remaining_us(LINUX_FUTEX_WAIT, 0, 1000000000L, 0) == FUTEX_TIMEOUT_INVALID,
              "nsec out of range refused");
        CHECK(futex_timeout_remaining_us(LINUX_FUTEX_WAIT, -1, 0, 0) == FUTEX_TIMEOUT_INVALID,
              "negative seconds refused");
        CHECK(futex_timeout_remaining_us(LINUX_FUTEX_WAIT, 0x7fffffffffffffffL, 0, 0) ==
              FUTEX_TIMEOUT_FOREVER, "huge seconds clamp to forever");
    }
    {
        /* A waiter killed in the queue whose slot is reused and waits
         * again on the same word: the stale node is the tail, and the
         * old enqueue linked tail -> tail, a cycle wake spun on forever. */
        fresh_all();
        fresh_proc(2);
        t_cur_pid = 2;
        word_a = 9;
        CHECK(futex_wait((unsigned long)&word_a, 9) == FUTEX_OK, "first wait sleeps");
        procs[2].state = PROC_ZOMBIE;
        fresh_proc(2);
        t_cur_pid = 2;
        CHECK(futex_wait((unsigned long)&word_a, 9) == FUTEX_OK, "reused slot waits again");
        CHECK(procs[2].wq_next == WQ_NONE, "reused slot never links to itself");
        CHECK(futex_wake((unsigned long)&word_a, FUTEX_WAKE_ALL) == 1,
              "wake reaches the reused waiter exactly once");
        CHECK(procs[2].state == PROC_READY, "reused waiter woken");
    }
    {
        /* A dead entry ahead of a live waiter is unlinked by wake, and the
         * live one behind it still wakes. */
        fresh_all();
        fresh_proc(3);
        fresh_proc(4);
        word_a = 1;
        t_cur_pid = 3;
        CHECK(futex_wait((unsigned long)&word_a, 1) == FUTEX_OK, "dead-to-be waits");
        t_cur_pid = 4;
        CHECK(futex_wait((unsigned long)&word_a, 1) == FUTEX_OK, "live waits");
        procs[3].state = PROC_ZOMBIE;
        CHECK(futex_wake((unsigned long)&word_a, 1) == 1, "live waiter behind a dead one wakes");
        CHECK(procs[4].state == PROC_READY, "live waiter READY");
        CHECK(futex_wake((unsigned long)&word_a, 1) == 0, "dead entry was pruned, nothing left");
    }
    {
        /* futex_forget unlinks a reaped slot so a later waiter in the
         * bucket never walks through it. */
        fresh_all();
        fresh_proc(5);
        fresh_proc(6);
        word_a = 2;
        t_cur_pid = 5;
        CHECK(futex_wait((unsigned long)&word_a, 2) == FUTEX_OK, "reaped-to-be waits");
        futex_forget(5);
        procs[5].state = PROC_FREE;
        t_cur_pid = 6;
        CHECK(futex_wait((unsigned long)&word_a, 2) == FUTEX_OK, "next waiter queues");
        CHECK(futex_wake((unsigned long)&word_a, FUTEX_WAKE_ALL) == 1, "only the live waiter wakes");
        CHECK(procs[6].state == PROC_READY, "live waiter READY after forget");
    }
    if (failures == 0)
        printf("futex: ok\n");
    else
        printf("futex: %d failures\n", failures);
    return failures != 0;
}
