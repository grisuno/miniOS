# headers

*Community 1 | 11 files | cohesion 0.46*

## Definition

This community groups 11 file(s) rooted at `headers` with dominant language c (cohesion 0.46). Central symbols: `BC_MASK`, `BC_WAYS`, `BLOCK_H`, `BLOCK_SHIFT`, `BLOCK_SIZE`, `DEV_MAX`, `DEV_NAME_LEN`, `DEV_TYPE_AUDIO`. Core file: `fs/minifs.c` (69 symbols). Documented purpose: include "kernel.h" include "lz4_kernel.h"  define HASH_BITS 12 define HASH_SIZE (1 << HASH_BITS).

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/block.c` | c | infrastructure | 21 | yes |
| `drivers/driver.c` | c | infrastructure | 8 | yes |
| `drivers/ide.c` | c | infrastructure | 24 | yes |
| `fs/minifs.c` | c | utility | 69 | yes |
| `headers/block.h` | h | utility | 12 | yes |
| `headers/driver.h` | h | infrastructure | 19 | yes |
| `headers/ide.h` | h | utility | 35 | yes |
| `headers/lz4_kernel.h` | h | utility | 4 | yes |
| `kernel/lz4_kernel.c` | c | utility | 13 | yes |
| `kernel/mm/swap.c` | c | utility | 10 | yes |
| `tests/test_driver.c` | c | testing | 12 | yes |

## Key Symbols

- `BC_WAYS` (macro, `drivers/block.c:41`) `#define BC_WAYS`
- `BC_MASK` (macro, `drivers/block.c:42`) `#define BC_MASK`
- `bc_index` (function, `drivers/block.c:46`) `static unsigned int bc_index(unsigned int block_num)`
- `bc_invalidate_locked` (function, `drivers/block.c:50`) `static void bc_invalidate_locked(unsigned int block_num)`
- `bc_invalidate` (function, `drivers/block.c:55`) `static void bc_invalidate(unsigned int block_num)`
- `spin_lock_irqsave` (function, `drivers/block.c:58`) `spin_lock_irqsave(&bc_lock, &flags);`
- `spin_unlock_irqrestore` (function, `drivers/block.c:60`) `spin_unlock_irqrestore(&bc_lock, flags);`
- `block_init` (function, `drivers/block.c:62`) `void block_init(void)`
- `ide_init` (function, `drivers/block.c:64`) `ide_init();`
- `block_set_base` (function, `drivers/block.c:68`) `void block_set_base(unsigned int lba_base)`
- `ide_read_sectors` (function, `drivers/block.c:86`) `return ide_read_sectors(lba, count, buf);`
- `block_dev_write` (function, `drivers/block.c:88`) `static int block_dev_write(unsigned lba, unsigned count, const void *buf)`
- `ide_write_sectors` (function, `drivers/block.c:93`) `return ide_write_sectors(lba, count, buf);`
- `block_read` (function, `drivers/block.c:95`) `int block_read(unsigned int block_num, void *buf)`
- `kfree` (function, `drivers/block.c:116`) `kfree(tmp);`
- `block_write` (function, `drivers/block.c:134`) `int block_write(unsigned int block_num, const void *buf)`
- `block_read_multi` (function, `drivers/block.c:143`) `int block_read_multi(unsigned int block_num, unsigned int count, void *buf)`
- `block_dev_read` (function, `drivers/block.c:146`) `return block_dev_read(lba, count * SECTORS_PER_BLOCK, buf);`
- `block_write_multi` (function, `drivers/block.c:148`) `int block_write_multi(unsigned int block_num, unsigned int count, const void *bu`
- `block_flush` (function, `drivers/block.c:163`) `void block_flush(void)`
- `block_total` (function, `drivers/block.c:165`) `unsigned int block_total(void)`
- `dev_len` (function, `drivers/driver.c:13`) `static unsigned dev_len(const char *s)`
- `dev_copy` (function, `drivers/driver.c:19`) `static void dev_copy(char *dst, const char *src, unsigned cap)`
- `dev_eq` (function, `drivers/driver.c:26`) `static int dev_eq(const char *a, const char *b)`
- `device_reset` (function, `drivers/driver.c:31`) `void device_reset(void)`
- `device_register` (function, `drivers/driver.c:43`) `int device_register(device_t *dev)`
- `device_find` (function, `drivers/driver.c:65`) `device_t *device_find(const char *name)`
- `device_find_by_type` (function, `drivers/driver.c:75`) `device_t *device_find_by_type(int type)`
- `device_count` (function, `drivers/driver.c:84`) `int device_count(void)`
- `ide_delay` (function, `drivers/ide.c:12`) `static void ide_delay(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 13
- Cross-boundary resolved imports (EXTRACTED): 15

## Connections

- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: drivers/block.c imports headers/kernel.h.

## Risks

- [high] `tests/test_driver.c:68` (in `strcpy`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- [high] `tests/test_driver.c:114` (in `snprintf`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- [high] `tests/test_driver.c:127` (in `snprintf`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- [high] `tests/test_driver.c:130` (in `snprintf`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.

## Open Questions

- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.46?

## Sources

- `drivers/block.c`
- `drivers/driver.c`
- `drivers/ide.c`
- `fs/minifs.c`
- `headers/block.h`
- `headers/driver.h`
- `headers/ide.h`
- `headers/lz4_kernel.h`
- `kernel/lz4_kernel.c`
- `kernel/mm/swap.c`
- `tests/test_driver.c`
