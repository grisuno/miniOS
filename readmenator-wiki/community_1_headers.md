# headers

*Community 1 | 7 files | cohesion 0.40*

## Definition

This community groups 7 file(s) rooted at `headers` with dominant language c (cohesion 0.40). Central symbols: `BC_LINE`, `BC_MASK`, `BC_WAYS`, `BLOCK_H`, `BLOCK_SHIFT`, `BLOCK_SIZE`, `DE_NAME`, `DE_NAME_W`. Core file: `fs/minifs.c` (63 symbols). Documented purpose: Block device layer for MiniFS..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/block.c` | c | infrastructure | 15 | yes |
| `fs/minifs.c` | c | utility | 63 | yes |
| `headers/block.h` | h | utility | 12 | yes |
| `headers/ide.h` | h | utility | 35 | yes |
| `headers/lz4_kernel.h` | h | utility | 4 | no |
| `kernel/lz4_kernel.c` | c | utility | 10 | no |
| `kernel/mm/swap.c` | c | utility | 11 | yes |

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
- `DE_NAME` (macro, `fs/minifs.c:12`) `#define DE_NAME(de)`
- `DE_NAME_W` (macro, `fs/minifs.c:13`) `#define DE_NAME_W(de)`
- `minifs_journal_touch` (function, `fs/minifs.c:15`) `void minifs_journal_touch(unsigned int phys);`
- `minifs_compress` (function, `fs/minifs.c:27`) `unsigned int minifs_compress(const void *src, unsigned int src_len,` - #define DE_NAME_W(de) ((char *)((de) + 1)) void minifs_journal_touch(unsigned int phys); void minifs
- `minifs_decompress` (function, `fs/minifs.c:38`) `unsigned int minifs_decompress(const void *src, unsigned int src_len,`
- `minifs_crc16` (function, `fs/minifs.c:49`) `static unsigned short minifs_crc16(const void *data, unsigned int len)`
- `minifs_crc32` (function, `fs/minifs.c:61`) `static unsigned int minifs_crc32(const void *data, unsigned int len)`
- `roundup4` (function, `fs/minifs.c:73`) `static unsigned int roundup4(unsigned int v)`
- `div_round_up` (function, `fs/minifs.c:75`) `static unsigned int div_round_up(unsigned int n, unsigned int d)`
- `returns` (function, `fs/minifs.c:84`) `* overflowed the slot and smashed returns (measured ring-0 #UD on  * lua->lua->c`
- `blk_free` (function, `fs/minifs.c:92`) `static void blk_free(unsigned char *b)`
- `fs_write_super` (function, `fs/minifs.c:99`) `static int fs_write_super(void)`
- `fs_read_inode` (function, `fs/minifs.c:113`) `static int fs_read_inode(unsigned int num, MiniFSInode *out)`
- `fs_write_inode` (function, `fs/minifs.c:124`) `static int fs_write_inode(unsigned int num, const MiniFSInode *in)`
- `bm_test` (function, `fs/minifs.c:140`) `static int bm_test(unsigned char *bm, unsigned int bit)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 8
- Cross-boundary resolved imports (EXTRACTED): 12

## Connections

- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: drivers/block.c imports headers/kernel.h.
- [INFERRED] shares_context community 1 <-> 2 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (headers) and community 2 (headers).
- [INFERRED] shares_context community 1 <-> 3 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (headers) and community 3 (progs/doomgeneric).

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 2 file(s) lack file-level docs (e.g. `headers/lz4_kernel.h`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.40?

## Sources

- `drivers/block.c`
- `fs/minifs.c`
- `headers/block.h`
- `headers/ide.h`
- `headers/lz4_kernel.h`
- `kernel/lz4_kernel.c`
- `kernel/mm/swap.c`
