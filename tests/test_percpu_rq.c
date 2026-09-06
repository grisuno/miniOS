/** Docstring: Host test for kernel/percpu_rq.c (make test-percpu-rq).
 *
 * Drives the hint rings with a stub two-CPU topology. Verifies FIFO
 * order, lossy-full drops, non-blocking steals, rescan scheduling and
 * invalid-input refusal. Claim validation against procs[] lives in
 * sched.c and is covered by the BDD suite, not here.
 */

#include <stdio.h>

#include "percpu_rq.h"

int cpu_count;

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

int main(void) {
    unsigned long hits;
    unsigned long steals;
    unsigned long drops;
    int i;
    int from;
    cpu_count = 2;
    rq_init();
    {
        CHECK(rq_empty(0), "fresh ring is empty");
        CHECK(rq_pop_local(0) == WQ_NONE_HINT, "pop on empty is none");
        rq_enqueue(0, 3);
        rq_enqueue(0, 4);
        CHECK(!rq_empty(0), "enqueued ring is not empty");
        CHECK(rq_pop_local(0) == 3, "first hint pops first");
        CHECK(rq_pop_local(0) == 4, "second hint pops second");
        CHECK(rq_empty(0), "drained ring is empty");
    }
    {
        for (i = 1; i <= RQ_DEPTH; i++)
            rq_enqueue(1, i);
        rq_enqueue(1, 7);
        rq_stats(1, &hits, &steals, &drops);
        CHECK(drops == 1, "full ring drops the hint");
        CHECK(rq_pop_local(1) == 1, "oldest hint survives the drop");
        for (i = 2; i <= RQ_DEPTH; i++)
            rq_pop_local(1);
        CHECK(rq_empty(1), "ring drains fully after drop");
    }
    {
        rq_enqueue(1, 11);
        rq_enqueue(1, 12);
        from = -1;
        CHECK(rq_steal_once(0, &from) == 11, "steal takes oldest hint");
        CHECK(from == 1, "steal reports the donor");
        CHECK(rq_pop_local(1) == 12, "donor keeps the remainder");
        CHECK(rq_steal_once(0, &from) == WQ_NONE_HINT,
              "steal on empty is none");
    }
    {
        int p;
        for (p = 0; p < RQ_RESCAN_PERIOD - 1; p++)
            rq_note_poll(0);
        CHECK(!rq_should_rescan(0), "rescan waits out the period");
        rq_note_poll(0);
        CHECK(rq_should_rescan(0), "rescan fires on schedule");
        CHECK(!rq_should_rescan(0), "rescan rearms after firing");
    }
    {
        rq_enqueue(-1, 5);
        rq_enqueue(9, 5);
        rq_enqueue(0, 0);
        rq_enqueue(0, MAX_PROCS);
        CHECK(rq_empty(0), "invalid enqueues record nothing");
        rq_stats(9, &hits, &steals, &drops);
        CHECK(rq_empty(9), "invalid cpu reads empty");
        CHECK(rq_should_rescan(9), "invalid cpu rescans safe");
    }
    if (failures == 0)
        printf("percpu_rq: ok\n");
    else
        printf("percpu_rq: %d failures\n", failures);
    return failures != 0;
}
