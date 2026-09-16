#ifndef BLOCK_H
#define BLOCK_H

/* Block device abstraction for MiniFS.
 * Maps 4096-byte logical blocks to 512-byte IDE sectors. */

#define BLOCK_SIZE      4096
#define BLOCK_SHIFT     12
#define SECTORS_PER_BLOCK  (BLOCK_SIZE / IDE_SECTOR_SIZE)

/* Initialize the block layer. Calls ide_init() internally. */
void block_init(void);

/* Set the base LBA offset for all block I/O. */
void block_set_base(unsigned int lba_base);

/* Read/write one 4096-byte block. Returns 0 on success. */
int block_read(unsigned int block_num, void *buf);
int block_write(unsigned int block_num, const void *buf);

/* Read/write multiple contiguous blocks.
 * Returns 0 on success. */
int block_read_multi(unsigned int block_num, unsigned int count, void *buf);
int block_write_multi(unsigned int block_num, unsigned int count, const void *buf);

/* Flush any cached writes (currently a no-op, IDE is synchronous). */
void block_flush(void);

/* Total blocks available, 0 if no disk. */
unsigned int block_total(void);

#endif
