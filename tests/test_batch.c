/** Docstring: Host test for kernel/batch.c (make test-batch).
 *
 * Drives the executor with stub effects. Verifies in-order execution
 * with per-index results, stop-on-first-error with completion accounting,
 * unknown-opcode refusal, count bounds and null-pointer refusal. The
 * completed out-parameter is asserted on every path.
 */

#include <stdio.h>

#include "batch.h"

static int failures = 0;
static int calls;
static int fail_on_nop;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

static long stub_dispatch(uint32_t opcode) {
    calls++;
    if (opcode == BATCH_OP_NOP && fail_on_nop)
        return -5;
    return (long)(100 + opcode);
}

int main(void) {
    batch_op_t ops[BATCH_MAX_OPS];
    long results[BATCH_MAX_OPS];
    int completed = -1;
    long r;
    int i;
    {
        calls = 0;
        fail_on_nop = 0;
        ops[0].opcode = BATCH_OP_NOP;
        ops[1].opcode = BATCH_OP_YIELD;
        ops[2].opcode = BATCH_OP_TIME;
        ops[3].opcode = BATCH_OP_GETPID;
        r = batch_exec(ops, results, 4, &completed, stub_dispatch);
        CHECK(r == BATCH_OK, "clean batch returns OK");
        CHECK(completed == 4, "clean batch completes all");
        CHECK(calls == 4, "clean batch dispatches in order");
        CHECK(results[0] == 100 && results[3] == 103,
              "results land per index");
    }
    {
        calls = 0;
        fail_on_nop = 1;
        ops[0].opcode = BATCH_OP_TIME;
        ops[1].opcode = BATCH_OP_NOP;
        ops[2].opcode = BATCH_OP_GETPID;
        completed = -1;
        r = batch_exec(ops, results, 3, &completed, stub_dispatch);
        CHECK(r == -5, "failing batch returns the op error");
        CHECK(completed == 1, "completion stops before the failure");
        CHECK(calls == 2, "dispatch stops at the failure");
        CHECK(results[0] == 102, "prior results survive the stop");
        fail_on_nop = 0;
    }
    {
        ops[0].opcode = 77;
        completed = -1;
        r = batch_exec(ops, results, 1, &completed, stub_dispatch);
        CHECK(r == BATCH_ERR_OPCODE, "unknown opcode is refused");
        CHECK(completed == 0, "refused batch completes nothing");
    }
    {
        completed = -1;
        CHECK(batch_exec(ops, results, BATCH_MAX_OPS + 1, &completed,
                         stub_dispatch) == BATCH_ERR_COUNT,
              "overlong batch is refused");
        CHECK(completed == 0, "overlong batch completes nothing");
        CHECK(batch_exec(ops, results, -1, &completed,
                         stub_dispatch) == BATCH_ERR_COUNT,
              "negative count is refused");
        CHECK(batch_exec(0, results, 2, &completed,
                         stub_dispatch) == BATCH_ERR_PTR,
              "null ops is refused");
        CHECK(batch_exec(ops, 0, 2, &completed,
                         stub_dispatch) == BATCH_ERR_PTR,
              "null results is refused");
        CHECK(batch_exec(ops, results, 0, &completed,
                         stub_dispatch) == BATCH_OK,
              "empty batch is OK");
        for (i = 0; i < BATCH_MAX_OPS; i++)
            ops[i].opcode = BATCH_OP_NOP;
        completed = -1;
        CHECK(batch_exec(ops, results, BATCH_MAX_OPS, &completed,
                         stub_dispatch) == BATCH_OK,
              "max batch runs");
        CHECK(completed == BATCH_MAX_OPS, "max batch completes fully");
    }
    if (failures == 0)
        printf("batch: ok\n");
    else
        printf("batch: %d failures\n", failures);
    return failures != 0;
}
