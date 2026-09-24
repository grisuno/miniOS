/** Docstring: drivers/virtio_blk.h -- virtio-blk boundary.
 *
 * Polled legacy virtio-blk (drivers/virtio_blk.c) behind the IDE
 * sector contract: probe once, then read/write 512-byte sectors by
 * LBA. The `vblk` builtin and a future block-layer preference are
 * the only consumers; MiniFS itself never names a device. */

#ifndef DRIVERS_VIRTIO_BLK_H
#define DRIVERS_VIRTIO_BLK_H

int vblk_init(void);
int vblk_present(void);
unsigned long vblk_sectors(void);
int vblk_read_sectors(unsigned lba, unsigned count, void *buf);
int vblk_write_sectors(unsigned lba, unsigned count, const void *buf);

#endif
