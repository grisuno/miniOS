# progs/nuklear

*Community 12 | 18 files | cohesion 0.51*

## Definition

This community groups 18 file(s) rooted at `progs/nuklear` with dominant language c (cohesion 0.51). Central symbols: `BEZIER_PAD`, `CHECK`, `CVM_EMIT_H`, `CVM_FUNC_ENTRY_SIZE`, `CVM_GLOBAL_ENTRY_SIZE`, `CVM_MAGIC_0`, `CVM_MAGIC_1`, `CVM_MAGIC_2`. Core file: `progs/vedit/vedit.c` (243 symbols). Documented purpose: Docstring: allocation tracker for MiniOS, STB leakcheck lineage..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/leakcheck.h` | h | utility | 24 | yes |
| `progs/doomedit/doomedit.c` | c | infrastructure | 108 | yes |
| `progs/file/file.c` | c | utility | 65 | yes |
| `progs/file/file_assoc.h` | h | utility | 17 | yes |
| `progs/minios_png.h` | h | utility | 21 | yes |
| `progs/nuklear/cvm_emit.c` | c | utility | 56 | yes |
| `progs/nuklear/cvm_emit.h` | h | utility | 6 | yes |
| `progs/nuklear/font8x8.c` | c | utility | 0 | yes |
| `progs/nuklear/node_editor.c` | c | infrastructure | 34 | yes |
| `progs/nuklear/nuklear_minios.h` | h | utility | 29 | yes |
| `progs/nuklear/nuklear_theme.c` | c | utility | 7 | yes |
| `progs/nuklear/nuklear_theme.h` | h | utility | 13 | yes |
| `progs/paint/paint.c` | c | utility | 53 | yes |
| `progs/vedit/vedit.c` | c | infrastructure | 243 | yes |
| `tests/test_file_assoc.c` | c | testing | 10 | yes |
| `tests/test_leakcheck.c` | c | testing | 4 | yes |
| `tests/test_minios_png.c` | c | testing | 10 | yes |
| `tests/test_theme.c` | c | testing | 8 | yes |

## Key Symbols

- `MINIOS_LEAKCHECK_H` (macro, `headers/leakcheck.h:28`) `#define MINIOS_LEAKCHECK_H`
- `MINIOS_LK_PIPE` (macro, `headers/leakcheck.h:42`) `#define MINIOS_LK_PIPE`
- `MINIOS_LK_PIPE` (macro, `headers/leakcheck.h:44`) `#define MINIOS_LK_PIPE`
- `lk_block_t` (type_alias, `headers/leakcheck.h:49`) `typedef struct lk_block lk_block_t;` - #ifndef MINIOS_LK_KERNEL #include <stdlib.h> #include <stdio.h> #endif #ifndef MINIOS_LK_PIPE #ifdef
- `lk_block` (struct, `headers/leakcheck.h:50`)
- `kmalloc` (function, `headers/leakcheck.h:79`) `extern void *kmalloc(unsigned long size);` - ifdef MINIOS_LK_KERNEL
- `kfree` (function, `headers/leakcheck.h:80`) `extern void kfree(void *ptr);`
- `kprintf` (function, `headers/leakcheck.h:81`) `extern int kprintf(const char *fmt, ...);`
- `MINIOS_LK_RAW_ALLOC` (macro, `headers/leakcheck.h:82`) `#define MINIOS_LK_RAW_ALLOC(sz)`
- `MINIOS_LK_RAW_FREE` (macro, `headers/leakcheck.h:83`) `#define MINIOS_LK_RAW_FREE(p)`
- `MINIOS_LK_RAW_ALLOC` (macro, `headers/leakcheck.h:88`) `#define MINIOS_LK_RAW_ALLOC(sz)`
- `MINIOS_LK_RAW_FREE` (macro, `headers/leakcheck.h:89`) `#define MINIOS_LK_RAW_FREE(p)`
- `lk_malloc` (function, `headers/leakcheck.h:96`) `void *lk_malloc(size_t size, const char *file, int line)` - #define MINIOS_LK_RAW_ALLOC(sz) kmalloc((unsigned long)(sz)) #define MINIOS_LK_RAW_FREE(p) kfree(p)
- `lk_unlink` (function, `headers/leakcheck.h:110`) `static void lk_unlink(lk_block_t *b)` - void *lk_malloc(size_t size, const char *file, int line) { lk_block_t *b = (lk_block_t *)MINIOS_LK_R
- `lk_find` (function, `headers/leakcheck.h:120`) `static lk_block_t *lk_find(void *ptr)` - return b + 1; } /** Docstring: unlink one record from the live-block list. static void lk_unlink(lk_
- `lk_free` (function, `headers/leakcheck.h:130`) `void lk_free(void *ptr)` - if (b->next) b->next->prev = b->prev; } /** Docstring: find the record owning ptr by scanning for it
- `lk_realloc` (function, `headers/leakcheck.h:143`) `void *lk_realloc(void *ptr, size_t size, const char *file, int line)` - /** Docstring: tracked free, passes unknown blocks to the raw backend. void lk_free(void *ptr) { lk_
- `lk_print` (function, `headers/leakcheck.h:186`) `static void lk_print(const char *reason, const lk_block_t *b)` - return ptr; } q = lk_malloc(size, file, line); if (q) { d = (unsigned char *)q; s = (unsigned char *
- `lk_dumpmem` (function, `headers/leakcheck.h:197`) `void lk_dumpmem(void)` - } /** Docstring: print one live record on the configured pipe. static void lk_print(const char *reas
- `lk_live_count` (function, `headers/leakcheck.h:206`) `unsigned long lk_live_count(void)` - b->file, b->line, (unsigned long)b->size, (const void *)(b + 1)); #endif } /** Docstring: report eve
- `lk_live_bytes` (function, `headers/leakcheck.h:217`) `unsigned long lk_live_bytes(void)` - } /** Docstring: count of blocks still live. unsigned long lk_live_count(void) { unsigned long n = 0
- `malloc` (macro, `headers/leakcheck.h:235`) `#define malloc(sz)`
- `free` (macro, `headers/leakcheck.h:236`) `#define free(p)`
- `realloc` (macro, `headers/leakcheck.h:237`) `#define realloc(p, sz)`
- `DMAP_MAX_W` (macro, `progs/doomedit/doomedit.c:55`) `#define DMAP_MAX_W`
- `DMAP_MAX_H` (macro, `progs/doomedit/doomedit.c:56`) `#define DMAP_MAX_H`
- `DMAP_DEF_W` (macro, `progs/doomedit/doomedit.c:57`) `#define DMAP_DEF_W`
- `DMAP_DEF_H` (macro, `progs/doomedit/doomedit.c:58`) `#define DMAP_DEF_H`
- `DMAP_TILE` (macro, `progs/doomedit/doomedit.c:59`) `#define DMAP_TILE`
- `DMAP_CELL_PX` (macro, `progs/doomedit/doomedit.c:60`) `#define DMAP_CELL_PX`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 23
- Cross-boundary resolved imports (EXTRACTED): 22

## Connections

- [EXTRACTED] depends_on community 12 <-> 7 (strength 0.9): Extracted import edge crosses communities: headers/leakcheck.h imports kernel/string.c.

## Risks

- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:1556` `dmap_build_wad` `side`: `side` assigned at line 1556 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:1633` `dmap_build_wad` `dir`: `dir` assigned at line 1633 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:2145` `dmap_selftest` `mrgb`: `mrgb` assigned at line 2145 but never read afterwards.

## Open Questions

- What would break if the most connected file in progs/nuklear changed?
- Should progs/nuklear be split, given cohesion 0.51?

## Sources

- `headers/leakcheck.h`
- `progs/doomedit/doomedit.c`
- `progs/file/file.c`
- `progs/file/file_assoc.h`
- `progs/minios_png.h`
- `progs/nuklear/cvm_emit.c`
- `progs/nuklear/cvm_emit.h`
- `progs/nuklear/font8x8.c`
- `progs/nuklear/node_editor.c`
- `progs/nuklear/nuklear_minios.h`
- `progs/nuklear/nuklear_theme.c`
- `progs/nuklear/nuklear_theme.h`
- `progs/paint/paint.c`
- `progs/vedit/vedit.c`
- `tests/test_file_assoc.c`
- `tests/test_leakcheck.c`
- `tests/test_minios_png.c`
- `tests/test_theme.c`
