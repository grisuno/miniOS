/* Block device layer for MiniFS.
 *
 * Maps 4096-byte logical blocks to 512-byte IDE sectors.
 *
 * A small direct-mapped write-through cache is layered on top of the IDE PIO
 * reads.  IDE PIO is the slowest part of the guest (every 32-bit data read is
 * an emulated VM-exit under QEMU), and MiniFS's directory iteration re-reads
 * the same directory block for every entry (minifs_dir_read re-scans the whole
 * directory), so without a cache `lsfs` is O(entries x blocks) in disk reads.
 * Caching the recently-read blocks turns that into one read per directory
 * block plus one per touched inode.  Writes are write-through and invalidate
 * the matching cache line so a cached copy can never go stale. */

#include "kernel.h"
#include "ide.h"
#include "block.h"

static unsigned int block_total_sectors;
static unsigned int block_lba_base;

/* Direct-mapped cache: 16 x 4096 = 64 KB of recently-read blocks. */
#define BC_WAYS 16
#define BC_MASK (BC_WAYS - 1)
static unsigned int  bc_block[BC_WAYS];
static unsigned char bc_valid[BC_WAYS];
static unsigned char bc_data[BC_WAYS][BLOCK_SIZE];

static unsigned int bc_index(unsigned int block_num) {
    return block_num & BC_MASK;
}

static void bc_invalidate(unsigned int block_num) {
    unsigned int idx = bc_index(block_num);
    if (bc_valid[idx] && bc_block[idx] == block_num) bc_valid[idx] = 0;
}

void block_init(void) {
    ide_init();
    block_total_sectors = ide_total_sectors();
    block_lba_base = 0;
}

void block_set_base(unsigned int lba_base) {
    block_lba_base = lba_base;
}

int block_read(unsigned int block_num, void *buf) {
    unsigned int idx = bc_index(block_num);
    if (bc_valid[idx] && bc_block[idx] == block_num) {
        unsigned char *src = bc_data[idx], *dst = (unsigned char *)buf;
        unsigned int i;
        for (i = 0; i < BLOCK_SIZE; i++) dst[i] = src[i];
        return 0;
    }
    unsigned int lba = block_lba_base + block_num * SECTORS_PER_BLOCK;
    if (ide_read_sectors(lba, SECTORS_PER_BLOCK, bc_data[idx]) < 0) return -1;
    bc_block[idx] = block_num;
    bc_valid[idx] = 1;
    {
        unsigned char *src = bc_data[idx], *dst = (unsigned char *)buf;
        unsigned int i;
        for (i = 0; i < BLOCK_SIZE; i++) dst[i] = src[i];
    }
    return 0;
}

int block_write(unsigned int block_num, const void *buf) {
    bc_invalidate(block_num);
    unsigned int lba = block_lba_base + block_num * SECTORS_PER_BLOCK;
    return ide_write_sectors(lba, SECTORS_PER_BLOCK, buf);
}

int block_read_multi(unsigned int block_num, unsigned int count, void *buf) {
    unsigned int lba = block_lba_base + block_num * SECTORS_PER_BLOCK;
    return ide_read_sectors(lba, count * SECTORS_PER_BLOCK, buf);
}

int block_write_multi(unsigned int block_num, unsigned int count, const void *buf) {
    unsigned int i;
    for (i = 0; i < count; i++) bc_invalidate(block_num + i);
    unsigned int lba = block_lba_base + block_num * SECTORS_PER_BLOCK;
    return ide_write_sectors(lba, count * SECTORS_PER_BLOCK, buf);
}

void block_flush(void) { }

unsigned int block_total(void) {
    if (block_total_sectors == 0) return 0;
    return block_total_sectors / SECTORS_PER_BLOCK;
}
