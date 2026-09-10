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
        CHECK(futex_linux_cmd(9) == -1, "WAIT_BITSET refused");
        CHECK(futex_linux_cmd(137) == -1, "WAKE|PRIVATE|extra refused");
        CHECK(futex_linux_cmd(-1) == -1, "negative op refused");
    }
    if (failures == 0)
        printf("futex: ok\n");
    else
        printf("futex: %d failures\n", failures);
    return failures != 0;
}
