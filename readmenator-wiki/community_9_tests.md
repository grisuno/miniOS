# tests

*Community 9 | 5 files | cohesion 0.40*

## Definition

This community groups 5 file(s) rooted at `tests` with dominant language c (cohesion 0.40). Central symbols: `CHECK`, `LIST_MAX`, `TRUSTED_DIR`, `TRUSTED_LEN`, `U_BASE`, `U_END`, `VMA_H`, `VMA_MAX`. Core file: `headers/vma.h` (21 symbols). Documented purpose: test_fault.c -- fault-injection suite (boyscout gap #10)..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/vma.h` | h | utility | 21 | yes |
| `tests/test_fault.c` | c | testing | 15 | yes |
| `tests/test_vma.c` | c | testing | 13 | yes |
| `tests/test_vma_bench.c` | c | testing | 10 | yes |
| `vma.c` | c | utility | 14 | yes |

## Key Symbols

- `VMA_H` (macro, `headers/vma.h:2`) `#define VMA_H`
- `base` (type_alias, `headers/vma.h:20`) `typedef struct vma_node { unsigned long base;` - Replaces the former flat mmap_used/mmap_free arrays with an O(log n) tree.  A single fixed node pool
- `vma_node` (struct, `headers/vma.h:21`)
- `VMA_MAX` (macro, `headers/vma.h:27`) `#define VMA_MAX`
- `vma_ctx_t` (struct, `headers/vma.h:41`) - Per-process VMA context (multitask foundation): every non-CLONE_VM process owns its live/free trees
- `VMA_NIL` (variable, `headers/vma.h:50`) `extern vma_node_t *VMA_NIL;`
- `vma_live_root` (variable, `headers/vma.h:52`) `extern vma_node_t *vma_live_root;`
- `vma_free_root` (variable, `headers/vma.h:53`) `extern vma_node_t *vma_free_root;`
- `vma_pool` (variable, `headers/vma.h:54`) `extern vma_node_t vma_pool[VMA_MAX];`
- `vma_pool_n` (variable, `headers/vma.h:55`) `extern int vma_pool_n;`
- `vma_pool_ptr` (variable, `headers/vma.h:56`) `extern vma_node_t *vma_pool_ptr;`
- `vma_legacy` (variable, `headers/vma.h:57`) `extern vma_ctx_t vma_legacy;`
- `vma_tree_init` (function, `headers/vma.h:58`) `void vma_tree_init(void);`
- `vma_tree_insert` (function, `headers/vma.h:60`) `vma_node_t *vma_tree_insert(vma_node_t **root, unsigned long base, unsigned long`
- `vma_tree_find` (function, `headers/vma.h:61`) `vma_node_t *vma_tree_find(vma_node_t *root, unsigned long base);`
- `vma_tree_delete` (function, `headers/vma.h:62`) `int vma_tree_delete(vma_node_t **root, unsigned long base);`
- `vma_ctx_init` (function, `headers/vma.h:63`) `void vma_ctx_init(vma_ctx_t *c, vma_node_t *pool);`
- `vma_ctx_bind` (function, `headers/vma.h:64`) `void vma_ctx_bind(vma_ctx_t *c);`
- `vma_ctx_save` (function, `headers/vma.h:65`) `void vma_ctx_save(vma_ctx_t *c);`
- `vma_ctx_alloc` (function, `headers/vma.h:68`) `vma_ctx_t *vma_ctx_alloc(void);` - Heap-backed contexts live in sched.c (vma.c stays host-testable): * alloc returns a fresh context wi
- `vma_ctx_free` (function, `headers/vma.h:69`) `void vma_ctx_free(vma_ctx_t *c);`
- `against` (function, `tests/test_fault.c:10`) `* after bounding against (END-BASE)/elemsz, so the product cannot * wrap past th`
- `CHECK` (macro, `tests/test_fault.c:28`) `#define CHECK(c, m)`
- `U_BASE` (macro, `tests/test_fault.c:31`) `#define U_BASE`
- `U_END` (macro, `tests/test_fault.c:32`) `#define U_END`
- `range_ok` (function, `tests/test_fault.c:35`) `static int range_ok(unsigned long p, unsigned long len)`
- `str_ok` (function, `tests/test_fault.c:41`) `static int str_ok(const unsigned char *mem, unsigned long p,                   u` - cannot report is itself a failure. #define CHECK(c, m) do { if (!(c)) { failures++; if (fprintf(stde
- `normalize` (function, `tests/test_fault.c:52`) `static void normalize(const char *path, char *out, unsigned cap)` - Minimal mirror of fs/vfs.c fs_resolve (cwd-relative, cap 64): * collapses ".", pops "..", skips empt
- `memcpy` (function, `tests/test_fault.c:74`) `memcpy(out + len, start, clen);`
- `TRUSTED_DIR` (macro, `tests/test_fault.c:81`) `#define TRUSTED_DIR`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 4
- Cross-boundary resolved imports (EXTRACTED): 6

## Connections

- [EXTRACTED] depends_on community 3 <-> 9 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports headers/vma.h.
- [EXTRACTED] depends_on community 2 <-> 9 (strength 0.9): Extracted import edge crosses communities: headers/sched.h imports headers/vma.h.

## Risks

- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/vma.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/vma.h` via `subprocess` (3 hops)
- [taint high] `mcp/minios_addons.py` -> `headers/vma.h` via `subprocess` (3 hops)

## Open Questions

- What would break if the most connected file in tests changed?
- Should tests be split, given cohesion 0.40?

## Sources

- `headers/vma.h`
- `tests/test_fault.c`
- `tests/test_vma.c`
- `tests/test_vma_bench.c`
- `vma.c`
