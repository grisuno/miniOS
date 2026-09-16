#ifndef BATCH_H
#define BATCH_H

/** Docstring: batch.h -- Batched synchronous syscall submission.
 *
 * Problem addressed: every syscall is a full trap round-trip, so I/O
 * heavy workloads (audio PCM submits, filesystem scans, repeated clock
 * reads) pay the entry/exit cost once per operation while the work per
 * operation is small.
 *
 * Design:
 * One SYS_SUBMIT_BATCH call carries an array of up to BATCH_MAX_OPS
 * descriptors; the kernel executes them in order in a single trap. Each
 * descriptor names an opcode plus three arguments, and each result lands
 * in the parallel results array at the same index. Execution stops at
 * the first failing operation: completed reports how many succeeded, and
 * the return value carries the failing operation's error. A batch is
 * synchronous (no completion queues, no async machinery): it only
 * amortizes trap overhead, which keeps the programming model identical
 * to issuing the calls one by one.
 *
 * Opcode policy:
 * Only side-effect-light, non-blocking operations are batchable. The set
 * is BATCH_OP_NOP (result 0), BATCH_OP_YIELD (deschedule once, result 0),
 * BATCH_OP_TIME (current milliseconds), and BATCH_OP_GETPID (current
 * pid). Anything else returns BATCH_ERR_OPCODE and stops the batch.
 * Blocking, pointer-carrying, or allocating operations stay single
 * syscalls: batching them would smuggle arbitrary memory access past the
 * per-syscall user-pointer validation.
 *
 * Bounds and failure modes, all fail-closed:
 * Counts above BATCH_MAX_OPS or below zero are refused before any
 * operation runs. A null ops or results pointer with nonzero count is
 * refused. The syscall layer validates both arrays against the user
 * window before the first operation, so a hostile length can neither
 * over-read nor over-write. completed is always written on return.
 */

#include <stdint.h>

#define BATCH_MAX_OPS 16

#define BATCH_OP_NOP 0
#define BATCH_OP_YIELD 1
#define BATCH_OP_TIME 2
#define BATCH_OP_GETPID 3

#define BATCH_OK 0
#define BATCH_ERR_COUNT (-1)
#define BATCH_ERR_PTR (-2)
#define BATCH_ERR_OPCODE (-3)

typedef struct {
    uint32_t opcode;
    uint64_t arg1;
    uint64_t arg2;
    uint64_t arg3;
} batch_op_t;

typedef long (*batch_handler_t)(uint32_t opcode);

long batch_exec(const batch_op_t *ops, long *results, int count,
                int *completed, batch_handler_t dispatch);

#endif
