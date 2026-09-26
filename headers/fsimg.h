#ifndef FSIMG_H
#define FSIMG_H

/* fsimg.h -- One image backend for read-only filesystem drivers.
 *
 * A disk image is either a regular file (ramdisk first, MiniFS
 * fallback with the flat-root basename rule, like kfopen) or a real
 * disk region (absolute LBA sectors through the IDE driver). Every
 * offset is bounds-checked against the size with overflow-safe
 * arithmetic; sector math is 64-bit and fenced. FAT32 and ext4 share
 * this contract instead of each carrying a copy. */

typedef struct {
    RDFile *rf;
    int ino;
    int is_dev;
    unsigned long dev_lba;
    unsigned long size;
} fsimg_t;

/* Open a resolved path as a loopback image. Refuses past 4 GB (all
 * sector math below is 32-bit). */
int fsimg_open_file(const char *resolved, fsimg_t *img);

/* Open an absolute disk region [base_lba, base_lba + nsec) as an
 * image. Bounds are 64-bit and fenced to the drive size. */
int fsimg_open_dev(unsigned long base_lba, unsigned long nsec,
                   fsimg_t *img);

/* Read len bytes at off into buf. Fails closed on any bound
 * violation, short backend transfer, or missing device. */
int fsimg_read(const fsimg_t *img, unsigned long off, void *buf,
               unsigned long len);

/* Split "left:right" at the first ':' (image names never carry one).
 * Bounds are per side: image paths resolve under RAMDISK_FNAME_LEN,
 * in-image paths may run deeper. Refuses empty sides and overlong
 * parts. Shared by the fat: and ext4: VFS addressings, which have
 * the same shape. */
int fsimg_split(const char *path, char *left, unsigned llen, char *right,
                unsigned rlen);

#endif
