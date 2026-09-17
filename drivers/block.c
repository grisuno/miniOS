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
#include "driver.h"

static unsigned int block_total_sectors;
static unsigned int block_lba_base;

/* Direct-mapped cache: 16 x 4096 = 64 KB of recently-read blocks.
 * Every shared line mutates only under bc_lock, which is irqsave (a
 * plain spin is fatal in this preemptive kernel: a holder preempted
 * mid-copy by the 100 Hz timer with IF=1 is descheduled holding the
 * lock, and a second context spinning for it with IF=0 kills the
 * timer, so neither ever runs again -- the silent wedge a background
 * wlcomp drain plus one shell write hit as an intermittent machine
 * stop with a waiter spinning on fs_lock downstream). The lock is a
 * leaf (never held across file IO, never nested inside
 * sched_lock/mm_lock/fd_lock) and only ever covers tag checks and
 * 4 KB copies, never the IDE PIO: a miss reads into a private heap
 * buffer with preemption allowed and installs atomically, so two
 * processes filling colliding lines both get their own bytes instead
 * of each other's. Without this, any two processes doing MiniFS IO
 * at once (a background server draining its mailboxes while a
 * program image loads) deterministically read torn blocks: wrong ELF
 * bytes jump anywhere, wrong dirents resolve wrong files. Hit rate
 * is unchanged; a miss costs one extra 4 KB copy. */
static spinlock_t bc_lock = SPINLOCK_INIT;
#define BC_WAYS 16
#define BC_MASK (BC_WAYS - 1)
static unsigned int  bc_block[BC_WAYS];
static unsigned char bc_valid[BC_WAYS];
static unsigned char bc_data[BC_WAYS][BLOCK_SIZE];

static unsigned int bc_index(unsigned int block_num) {
    return block_num & BC_MASK;
}

static void bc_invalidate_locked(unsigned int block_num) {
    unsigned int idx = bc_index(block_num);
    if (bc_valid[idx] && bc_block[idx] == block_num) bc_valid[idx] = 0;
}

static void bc_invalidate(unsigned int block_num) {
    irqflags_t flags;
    spin_lock_irqsave(&bc_lock, &flags);
    bc_invalidate_locked(block_num);
    spin_unlock_irqrestore(&bc_lock, flags);
}

void block_init(void) {
    ide_init();
    block_total_sectors = ide_total_sectors();
    block_lba_base = 0;
}

void block_set_base(unsigned int lba_base) {
    if (lba_base != block_lba_base) {
        unsigned int i;
        for (i = 0; i < BC_WAYS; i++) bc_valid[i] = 0;
        block_lba_base = lba_base;
    }
}

/* Strategy consumer: sector I/O goes through the registered block device's
 * ops table (dev->ops->read/write), never straight at the hardware. The
 * direct ide_* call is a fail-closed fallback for the window between
 * block_init's probe and the registry publish, and for images whose IDE
 * probe found no disk (registry still publishes, present() says 0). */
static int block_dev_read(unsigned lba, unsigned count, void *buf) {
    device_t *d = device_find("ide0");
    if (d && d->block && d->block->read_sectors)
        return d->block->read_sectors(d, lba, count, buf);
    return ide_read_sectors(lba, count, buf);
}

static int block_dev_write(unsigned lba, unsigned count, const void *buf) {
    device_t *d = device_find("ide0");
    if (d && d->block && d->block->write_sectors)
        return d->block->write_sectors(d, lba, count, buf);
    return ide_write_sectors(lba, count, buf);
}

int block_read(unsigned int block_num, void *buf) {
    unsigned int idx = bc_index(block_num);
    unsigned char *tmp = 0;
    unsigned int lba;
    unsigned int i;
    unsigned char *dst = (unsigned char *)buf;
    irqflags_t flags;
    if (!buf) return -1;
    spin_lock_irqsave(&bc_lock, &flags);
    if (bc_valid[idx] && bc_block[idx] == block_num) {
        unsigned char *src = bc_data[idx];
        for (i = 0; i < BLOCK_SIZE; i++) dst[i] = src[i];
        spin_unlock_irqrestore(&bc_lock, flags);
        return 0;
    }
    spin_unlock_irqrestore(&bc_lock, flags);
    tmp = (unsigned char *)kmalloc(BLOCK_SIZE);
    if (!tmp) return -1;
    lba = block_lba_base + block_num * SECTORS_PER_BLOCK;
    if (block_dev_read(lba, SECTORS_PER_BLOCK, tmp) < 0) {
        kfree(tmp);
        return -1;
    }
    spin_lock_irqsave(&bc_lock, &flags);
    if (bc_valid[idx] && bc_block[idx] == block_num) {
        unsigned char *src = bc_data[idx];
        for (i = 0; i < BLOCK_SIZE; i++) dst[i] = src[i];
    } else {
        unsigned char *line = bc_data[idx];
        for (i = 0; i < BLOCK_SIZE; i++) line[i] = tmp[i];
        bc_block[idx] = block_num;
        bc_valid[idx] = 1;
        for (i = 0; i < BLOCK_SIZE; i++) dst[i] = tmp[i];
    }
    spin_unlock_irqrestore(&bc_lock, flags);
    kfree(tmp);
    return 0;
}

int block_write(unsigned int block_num, const void *buf) {
    unsigned int lba = block_lba_base + block_num * SECTORS_PER_BLOCK;
    int r;
    bc_invalidate(block_num);
    r = block_dev_write(lba, SECTORS_PER_BLOCK, buf);
    bc_invalidate(block_num);
    return r;
}

int block_read_multi(unsigned int block_num, unsigned int count, void *buf) {
    unsigned int lba = block_lba_base + block_num * SECTORS_PER_BLOCK;
    return block_dev_read(lba, count * SECTORS_PER_BLOCK, buf);
}

int block_write_multi(unsigned int block_num, unsigned int count, const void *buf) {
    unsigned int i;
    unsigned int lba = block_lba_base + block_num * SECTORS_PER_BLOCK;
    int r;
    irqflags_t flags;
    spin_lock_irqsave(&bc_lock, &flags);
    for (i = 0; i < count; i++) bc_invalidate_locked(block_num + i);
    spin_unlock_irqrestore(&bc_lock, flags);
    r = block_dev_write(lba, count * SECTORS_PER_BLOCK, buf);
    spin_lock_irqsave(&bc_lock, &flags);
    for (i = 0; i < count; i++) bc_invalidate_locked(block_num + i);
    spin_unlock_irqrestore(&bc_lock, flags);
    return r;
}

void block_flush(void) { }

unsigned int block_total(void) {
    if (block_total_sectors == 0) return 0;
    return block_total_sectors / SECTORS_PER_BLOCK;
}
