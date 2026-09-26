#ifndef EXT4_H
#define EXT4_H

/* ext4.h -- Read-only ext4 loopback/device driver.
 *
 * A subset of ext4, read-only: superblock, block groups (32 or 64
 * bit descriptors), inodes (extent trees plus legacy direct and
 * singly-indirect blocks), linear directories. Out of scope and
 * refused fail-closed: htree-indexed directories, symlinks (even
 * fast ones), encrypted or inline-data files, doubly and triply
 * indirect blocks, journal replay (reads see the last consistent
 * state). Checksums are not verified; every structural offset is
 * bounds-checked instead. The image backend (regular file or real
 * disk region) is the shared fsimg contract. */

#define EXT4_NAME_MAX  255
#define EXT4_MAX_DEPTH 8
#define EXT4_LIST_CAP  64
#define EXT4_PATH_MAX  256

/* One open ext4 file: image backend plus the located inode. */
typedef struct {
    int ino_img;
    RDFile *rf;
    int is_dev;
    unsigned long dev_lba;
    unsigned long img_size;
    unsigned bs;
    unsigned ino;
    unsigned long file_size;
} ext4_handle_t;

/* List one directory: names (dirs with trailing '/') up to cap.
 * Returns the entry count, or -1 when the image, path or walk fails. */
int ext4_list(const char *imgpath, const char *dirpath,
              char names[][EXT4_NAME_MAX + 1], int *isdir, int cap);

/* VFS verbs: open "imgpath:extpath" (first ':' splits), read, close,
 * fstat. Write/truncate refuse. All fail closed with -1. */
int ext4_vfs_open(const char *path, int mode, void **handle);
int ext4_vfs_read(void *handle, void *buf, unsigned long pos,
                  unsigned long len);
int ext4_vfs_write(void *handle, const void *buf, unsigned long pos,
                   unsigned long len);
int ext4_vfs_close(void *handle);
int ext4_vfs_fstat(void *handle, unsigned long *size_out);
int ext4_vfs_truncate(void *handle, unsigned long size);

/* First Linux-native partition on the primary IDE master: a real
 * MBR 0x83 entry first (proven by a superblock read), then a magic
 * scan over 2048-aligned LBAs for superfloppy layouts. Returns the
 * base LBA, or -1 when no ext4 is present. Cached. */
long ext_dev_base(void);

extern const vfs_ops_t ext4_vfs_ops;

#endif
