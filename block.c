/* Block device layer for MiniFS.
 *
 * Maps 4096-byte logical blocks to 512-byte IDE sectors. */

#include "kernel.h"
#include "ide.h"
#include "block.h"

static unsigned int block_total_sectors;
static unsigned int block_lba_base;

void block_init(void) {
    ide_init();
    block_total_sectors = ide_total_sectors();
    block_lba_base = 0;
}

void block_set_base(unsigned int lba_base) {
    block_lba_base = lba_base;
}

int block_read(unsigned int block_num, void *buf) {
    unsigned int lba = block_lba_base + block_num * SECTORS_PER_BLOCK;
    return ide_read_sectors(lba, SECTORS_PER_BLOCK, buf);
}

int block_write(unsigned int block_num, const void *buf) {
    unsigned int lba = block_lba_base + block_num * SECTORS_PER_BLOCK;
    return ide_write_sectors(lba, SECTORS_PER_BLOCK, buf);
}

int block_read_multi(unsigned int block_num, unsigned int count, void *buf) {
    unsigned int lba = block_lba_base + block_num * SECTORS_PER_BLOCK;
    return ide_read_sectors(lba, count * SECTORS_PER_BLOCK, buf);
}

int block_write_multi(unsigned int block_num, unsigned int count, const void *buf) {
    unsigned int lba = block_lba_base + block_num * SECTORS_PER_BLOCK;
    return ide_write_sectors(lba, count * SECTORS_PER_BLOCK, buf);
}

void block_flush(void) { }

unsigned int block_total(void) {
    if (block_total_sectors == 0) return 0;
    return block_total_sectors / SECTORS_PER_BLOCK;
}
