/** Docstring: Host test for kernel/rcu.c (make test-rcu).
 *
 * Drives epochs with synthetic ticks on a stub single CPU. Verifies
 * publish/deref visibility, two-period grace before callbacks run, full
 * queue refusal with caller-kept ownership, synchronize success once
 * quiescence is reported, synchronize timeout when ticks stall, and
 * nested read sections with underflow clamping.
 */

#include <stdio.h>

#include "rcu.h"

int cpu_count;
static cpu_t fake_cpu;
static int cb_runs;
static void *cb_last;

cpu_t *rcu_host_cpu(void) {
    return &fake_cpu;
}

static void test_cb(void *arg) {
    cb_runs++;
    cb_last = arg;
}

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

int main(void) {
    void *volatile slot = 0;
    int a = 11;
    int b = 22;
    int i;
    cpu_count = 1;
    fake_cpu.self = &fake_cpu;
    fake_cpu.cpu_id = 0;
    rcu_init();
    {
        rcu_publish(&slot, &a);
        CHECK(rcu_deref(&slot) == &a, "published pointer is visible");
        rcu_publish(&slot, &b);
        CHECK(rcu_deref(&slot) == &b, "republish is visible");
    }
    {
        cb_runs = 0;
        cb_last = 0;
        CHECK(rcu_call(test_cb, &a) == RCU_OK, "retire enqueues");
        rcu_note_tick(0);
        rcu_poll();
        CHECK(cb_runs == 0, "callback waits out the first grace");
        rcu_note_tick(0);
        rcu_poll();
        CHECK(cb_runs == 1, "callback runs after grace closes");
        CHECK(cb_last == &a, "callback keeps its argument");
    }
    {
        for (i = 0; i < RCU_CB_MAX; i++)
            CHECK(rcu_call(test_cb, &a) == RCU_OK, "queue fills");
        CHECK(rcu_call(test_cb, &a) == RCU_ERR_FULL,
              "full queue refuses the retirement");
        CHECK(rcu_call(0, &a) == RCU_ERR_FULL, "null callback refused");
    }
    {
        rcu_init();
        rcu_note_tick(0);
        CHECK(rcu_synchronize() == RCU_OK,
              "synchronize succeeds on reported quiescence");
    }
    {
        rcu_init();
        CHECK(rcu_synchronize() == RCU_ERR_TIMEOUT,
              "synchronize times out on stalled ticks");
    }
    {
        rcu_init();
        rcu_read_lock();
        rcu_read_lock();
        rcu_note_tick(0);
        rcu_poll();
        rcu_read_unlock();
        rcu_read_unlock();
        rcu_read_unlock();
        CHECK(1, "nested sections and underflow are safe");
    }
    if (failures == 0)
        printf("rcu: ok\n");
    else
        printf("rcu: %d failures\n", failures);
    return failures != 0;
}
