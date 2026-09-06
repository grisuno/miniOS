/** Docstring: kernel/batch.c -- Ordered batch executor.
 *
 * Implements batch.h. The executor is pure: operation effects arrive
 * through the dispatch callback, so the host unit test (tests/test_batch.c,
 * make test-batch) drives it with stub effects and asserts ordering,
 * stop-on-error, completion accounting and bounds without any kernel.
 */

#include "batch.h"

/** Docstring: Run ops in order, storing one result per index.
 *
 * Returns BATCH_OK when every operation dispatched without a negative
 * result. On the first negative dispatch result, stops immediately and
 * returns that error. completed always reports the number of successful
 * operations, including on early refusal (zero). A null dispatch table
 * entry for a known opcode is treated as BATCH_ERR_OPCODE, never called.
 */
long batch_exec(const batch_op_t *ops, long *results, int count,
                int *completed, batch_handler_t dispatch) {
    int i;
    if (completed)
        *completed = 0;
    if (count < 0 || count > BATCH_MAX_OPS)
        return BATCH_ERR_COUNT;
    if (count > 0 && (!ops || !results || !completed || !dispatch))
        return BATCH_ERR_PTR;
    for (i = 0; i < count; i++) {
        uint32_t op = ops[i].opcode;
        long r;
        if (op != BATCH_OP_NOP && op != BATCH_OP_YIELD &&
            op != BATCH_OP_TIME && op != BATCH_OP_GETPID)
            return BATCH_ERR_OPCODE;
        r = dispatch(op);
        if (r < 0)
            return r;
        results[i] = r;
        *completed = i + 1;
    }
    return BATCH_OK;
}
