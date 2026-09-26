#ifndef FAT32_H
#define FAT32_H

/* fat32.h -- Read-only FAT32 loopback driver over ramdisk/MiniFS images.
 *
 * A FAT32 disk image stored as a regular file (built on the host with
 * mkfs.vfat, packed into minifs.bin) is parsed here: BPB validation,
 * cluster-chain walking and 8.3 directory traversal. Only the read
 * half of vfs_ops_t is served (open/read/close/fstat); write and
 * truncate refuse, and the image file itself is opened read-only, so
 * a guest can never dirty the backing store. Every offset is
 * bounds-checked against the image size with overflow-safe
 * arithmetic, cluster walks are step-bounded, directory depth is
 * capped, and long-file-name entries are skipped (8.3 only). */

#define FAT32_NAME_MAX  13
#define FAT32_MAX_DEPTH 8
#define FAT32_LIST_CAP  64
#define FAT32_CLUS_MAX  65536

/* One open FAT file: image backend plus the located entry. */
typedef struct {
    int ino;
    RDFile *rf;
    unsigned long img_size;
    unsigned byts_per_sec;
    unsigned sec_per_clus;
    unsigned rsvd_sec;
    unsigned num_fats;
    unsigned fatsz_sec;
    unsigned root_clus;
    unsigned data_off;
    unsigned nclus;
    unsigned start_clus;
    unsigned long file_size;
} fat32_handle_t;

/* List one directory: names (dirs with trailing '/') up to cap.
 * Returns the entry count, or -1 when the image, path or walk fails. */
int fat32_list(const char *imgpath, const char *dirpath,
               char names[][FAT32_NAME_MAX], int *isdir, int cap);

/* VFS verbs: open "imgpath:fatpath" (first ':' splits), read, close,
 * fstat. Write/truncate refuse. All fail closed with -1. */
int fat32_vfs_open(const char *path, int mode, void **handle);
int fat32_vfs_read(void *handle, void *buf, unsigned long pos,
                   unsigned long len);
int fat32_vfs_write(void *handle, const void *buf, unsigned long pos,
                    unsigned long len);
int fat32_vfs_close(void *handle);
int fat32_vfs_fstat(void *handle, unsigned long *size_out);
int fat32_vfs_truncate(void *handle, unsigned long size);

extern const vfs_ops_t fat32_vfs_ops;

#endif
