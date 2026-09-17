# headers

*Community 6 | 3 files | cohesion 0.67*

## Definition

This community groups 3 file(s) rooted at `tests` with dominant language c (cohesion 0.67). Central symbols: `BATCH_ERR_COUNT`, `BATCH_ERR_OPCODE`, `BATCH_ERR_PTR`, `BATCH_H`, `BATCH_MAX_OPS`, `BATCH_OK`, `BATCH_OP_GETPID`, `BATCH_OP_NOP`. Core file: `headers/batch.h` (13 symbols). Documented purpose: Docstring: Host test for kernel/batch.c (make test-batch)..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/batch.h` | h | utility | 13 | yes |
| `kernel/batch.c` | c | utility | 1 | yes |
| `tests/test_batch.c` | c | testing | 6 | yes |

## Key Symbols

- `BATCH_H` (macro, `headers/batch.h:2`) `#define BATCH_H`
- `BATCH_MAX_OPS` (macro, `headers/batch.h:40`) `#define BATCH_MAX_OPS`
- `BATCH_OP_NOP` (macro, `headers/batch.h:42`) `#define BATCH_OP_NOP`
- `BATCH_OP_YIELD` (macro, `headers/batch.h:44`) `#define BATCH_OP_YIELD`
- `BATCH_OP_TIME` (macro, `headers/batch.h:45`) `#define BATCH_OP_TIME`
- `BATCH_OP_GETPID` (macro, `headers/batch.h:46`) `#define BATCH_OP_GETPID`
- `BATCH_OK` (macro, `headers/batch.h:47`) `#define BATCH_OK`
- `BATCH_ERR_COUNT` (macro, `headers/batch.h:49`) `#define BATCH_ERR_COUNT`
- `BATCH_ERR_PTR` (macro, `headers/batch.h:50`) `#define BATCH_ERR_PTR`
- `BATCH_ERR_OPCODE` (macro, `headers/batch.h:51`) `#define BATCH_ERR_OPCODE`
- `batch_op_t` (struct, `headers/batch.h:53`)
- `long` (function, `headers/batch.h:59`) `typedef long (*batch_handler_t)(uint32_t opcode);`
- `batch_exec` (function, `headers/batch.h:61`) `long batch_exec(const batch_op_t *ops, long *results, int count, int *completed,`
- `batch_exec` (function, `kernel/batch.c:19`) `long batch_exec(const batch_op_t *ops, long *results, int count,` - Docstring: Run ops in order, storing one result per index.  Returns BATCH_OK when every operation di
- `CHECK` (macro, `tests/test_batch.c:16`) `#define CHECK(cond, msg)`
- `fprintf` (function, `tests/test_batch.c:20`) `fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__);`
- `stub_dispatch` (function, `tests/test_batch.c:23`) `static long stub_dispatch(uint32_t opcode)`
- `main` (function, `tests/test_batch.c:30`) `int main(void)`
- `CHECK` (function, `tests/test_batch.c:45`) `CHECK(r == BATCH_OK, "clean batch returns OK");`
- `printf` (function, `tests/test_batch.c:100`) `else printf("batch: %d failures\n", failures);`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 2
- Cross-boundary resolved imports (EXTRACTED): 1

## Connections

- [EXTRACTED] depends_on community 3 <-> 6 (strength 0.9): Extracted import edge crosses communities: kernel/syscalls.c imports headers/batch.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.67?

## Sources

- `headers/batch.h`
- `kernel/batch.c`
- `tests/test_batch.c`
