# headers

*Community 1 | 22 files | cohesion 0.57*

## Definition

This community groups 22 file(s) rooted at `headers` with dominant language c (cohesion 0.57). Central symbols: `BC_LINE`, `BC_MASK`, `BC_WAYS`, `BLOCK_H`, `BLOCK_SHIFT`, `BLOCK_SIZE`, `CHECK`, `DEV_MAX`. Core file: `headers/minifs.h` (78 symbols). Documented purpose: Block device layer for MiniFS..

## Files

### `headers` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/block.h` | h | utility | 12 | yes |
| `headers/driver.h` | h | infrastructure | 16 | yes |
| `headers/ext4.h` | h | utility | 15 | yes |
| `headers/fat32.h` | h | utility | 16 | yes |
| `headers/fsimg.h` | h | utility | 6 | yes |
| `headers/ide.h` | h | utility | 35 | yes |

### `fs` (6 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fs/ext4.c` | c | utility | 37 | yes |
| `fs/fat32.c` | c | utility | 31 | yes |
| `fs/fsimg.c` | c | utility | 5 | yes |
| `fs/kfile.c` | c | utility | 25 | yes |
| `fs/minifs.c` | c | utility | 67 | yes |
| `fs/vfs.c` | c | utility | 41 | yes |

### `drivers` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/block.c` | c | infrastructure | 15 | yes |
| `drivers/driver.c` | c | infrastructure | 8 | yes |
| `drivers/ide.c` | c | infrastructure | 19 | yes |

### `tests` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_driver.c` | c | testing | 5 | yes |
| `tests/test_ext4.c` | c | testing | 29 | yes |
| `tests/test_fat32.c` | c | testing | 26 | yes |

### `kernel` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/lz4_kernel.c` | c | utility | 10 | no |

### `kernel/mm` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/mm/swap.c` | c | utility | 11 | yes |

*... and 2 more files in this community.*


## Key Symbols

- `BC_WAYS` (macro, `drivers/block.c:41`) `#define BC_WAYS`
- `BC_MASK` (macro, `drivers/block.c:42`) `#define BC_MASK`
- `BC_LINE` (macro, `drivers/block.c:50`) `#define BC_LINE(idx)`
- `bc_index` (function, `drivers/block.c:52`) `static unsigned int bc_index(unsigned int block_num)`
- `bc_invalidate_locked` (function, `drivers/block.c:56`) `static void bc_invalidate_locked(unsigned int block_num)`
- `bc_invalidate` (function, `drivers/block.c:61`) `static void bc_invalidate(unsigned int block_num)`
- `block_init` (function, `drivers/block.c:68`) `void block_init(void)`
- `block_set_base` (function, `drivers/block.c:76`) `void block_set_base(unsigned int lba_base)`
- `block_dev_write` (function, `drivers/block.c:96`) `static int block_dev_write(unsigned lba, unsigned count, const void *buf)`
- `block_read` (function, `drivers/block.c:103`) `int block_read(unsigned int block_num, void *buf)`
- `block_write` (function, `drivers/block.c:144`) `int block_write(unsigned int block_num, const void *buf)`
- `block_read_multi` (function, `drivers/block.c:153`) `int block_read_multi(unsigned int block_num, unsigned int count, void *buf)`
- `block_write_multi` (function, `drivers/block.c:158`) `int block_write_multi(unsigned int block_num, unsigned int count, const void *bu`
- `block_flush` (function, `drivers/block.c:173`) `void block_flush(void)`
- `block_total` (function, `drivers/block.c:175`) `unsigned int block_total(void)`
- `dev_len` (function, `drivers/driver.c:14`) `static unsigned dev_len(const char *s)`
- `dev_copy` (function, `drivers/driver.c:20`) `static void dev_copy(char *dst, const char *src, unsigned cap)`
- `dev_eq` (function, `drivers/driver.c:27`) `static int dev_eq(const char *a, const char *b)`
- `device_reset` (function, `drivers/driver.c:32`) `void device_reset(void)`
- `device_register` (function, `drivers/driver.c:44`) `int device_register(device_t *dev)`
- `device_find` (function, `drivers/driver.c:66`) `device_t *device_find(const char *name)`
- `device_find_by_type` (function, `drivers/driver.c:76`) `device_t *device_find_by_type(int type)`
- `device_count` (function, `drivers/driver.c:85`) `int device_count(void)`
- `ide_delay` (function, `drivers/ide.c:13`) `static void ide_delay(void)`
- `ide_read_status` (function, `drivers/ide.c:23`) `static unsigned char ide_read_status(void)`
- `ide_wait_not_busy` (function, `drivers/ide.c:27`) `static int ide_wait_not_busy(unsigned int timeout)`
- `ide_wait_drq` (function, `drivers/ide.c:40`) `static int ide_wait_drq(unsigned int timeout)`
- `ide_select_drive` (function, `drivers/ide.c:53`) `static void ide_select_drive(unsigned char drive)`
- `ide_soft_reset` (function, `drivers/ide.c:59`) `static void ide_soft_reset(void)`
- `ide_identify` (function, `drivers/ide.c:66`) `static int ide_identify(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 39
- Cross-boundary resolved imports (EXTRACTED): 30

## Connections

- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: drivers/block.c imports headers/kernel.h.
- [EXTRACTED] depends_on community 1 <-> 4 (strength 0.9): Extracted import edge crosses communities: tests/test_driver.c imports kernel/string.c.
- [INFERRED] shares_context community 1 <-> 2 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (headers) and community 2 (headers).
- [INFERRED] shares_context community 1 <-> 5 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (headers) and community 5 (headers).
- [INFERRED] shares_context community 1 <-> 6 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (headers) and community 6 (headers).

## Risks

- [dataflow DEAD_STORE] `fs/kfile.c:98` `kpipe_pair` `ref`: `ref` assigned at line 98 but never read afterwards.

## Open Questions

- Why do 2 file(s) lack file-level docs (e.g. `headers/lz4_kernel.h`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.57?

## Sources

- `drivers/block.c`
- `drivers/driver.c`
- `drivers/ide.c`
- `fs/ext4.c`
- `fs/fat32.c`
- `fs/fsimg.c`
- `fs/kfile.c`
- `fs/minifs.c`
- `fs/vfs.c`
- `headers/block.h`
- `headers/driver.h`
- `headers/ext4.h`
- `headers/fat32.h`
- `headers/fsimg.h`
- `headers/ide.h`
- `headers/lz4_kernel.h`
- `headers/minifs.h`
- `kernel/lz4_kernel.c`
- `kernel/mm/swap.c`
- `tests/test_driver.c`
- *... and 2 more*
