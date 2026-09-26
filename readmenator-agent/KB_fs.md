# Subsystem: fs

## fs/ext4.c
- Layer: utility
- Doc: ================================================================
- Language: c
- Symbols:
  - `ext_geo_t` (struct, line 44)
  - `ext_ino_t` (struct, line 115)
  - `ext_ld16` (function, line 32) `static unsigned ext_ld16(const unsigned char *p)`
  - `ext_ld32` (function, line 36) `static unsigned long ext_ld32(const unsigned char *p)`
  - `ext_parse_sb` (function, line 55) `static int ext_parse_sb(const fsimg_t *img, ext_geo_t *g)`
  - `ext_inode_off` (function, line 92) `static int ext_inode_off(const fsimg_t *img, const ext_geo_t *g,
                         unsigne...`
  - `ext_read_inode` (function, line 122) `static int ext_read_inode(const fsimg_t *img, const ext_geo_t *g,
                          unsig...`
  - `ext_map` (function, line 171) `static int ext_map(const fsimg_t *img, const ext_geo_t *g,
                   const unsigned char...`
  - `ext_map_leaf` (function, line 211) `static int ext_map_leaf(const fsimg_t *img, const ext_geo_t *g,
                        const uns...`
  - `ext_resolve` (function, line 356) `static int ext_resolve(const fsimg_t *img, const ext_geo_t *g,
                       const char ...`
  - `ext_file_block` (function, line 464) `static int ext_file_block(const fsimg_t *img, const ext_geo_t *g,
                          const...`
  - `ext4_list` (function, line 485) `int ext4_list(const char *imgpath, const char *dirpath,
              char names[][EXT4_NAME_MAX ...`
  - `ext_split` (function, line 580) `static int ext_split(const char *path, char *img, char *extp)`
  - `ext4_vfs_open` (function, line 585) `int ext4_vfs_open(const char *path, int mode, void **handle)`
  - `ext4_vfs_read` (function, line 626) `int ext4_vfs_read(void *handle, void *buf, unsigned long pos,
                  unsigned long len)`
  - `ext4_vfs_write` (function, line 666) `int ext4_vfs_write(void *handle, const void *buf, unsigned long pos,
                   unsigned ...`
  - `ext4_vfs_close` (function, line 675) `int ext4_vfs_close(void *handle)`
  - `ext4_vfs_fstat` (function, line 680) `int ext4_vfs_fstat(void *handle, unsigned long *size_out)`
  - `ext4_vfs_truncate` (function, line 687) `int ext4_vfs_truncate(void *handle, unsigned long size)`
  - `ext_mbr_entry` (function, line 705) `static int ext_mbr_entry(const unsigned char *mbr, int idx,
                         unsigned lon...`
  - `ext_scan_dev` (function, line 730) `static int ext_scan_dev(unsigned long total_sec,
                        unsigned long *base_out)`
  - `ext_dev_base` (function, line 751) `long ext_dev_base(void)`
  - `ext_map_down` (function, line 168) `static int ext_map_down(const fsimg_t *img, const ext_geo_t *g, const unsigned char *root, unsigned nent, unsigned long lblk, unsigned char *node);`
  - `only` (function, line 352) `* listings only ('.' skipped, '..' refused). "" or "/" is root (2). */ static int ext_file_block(const fsimg_t *img, const ext_geo_t *g, const ext_ino_t *st, unsigned long lblk, unsigned char *blk, un`
  - `EXT4_SUPER_OFF` (macro, line 18) `#define EXT4_SUPER_OFF`
  - `EXT4_MAGIC` (macro, line 19) `#define EXT4_MAGIC`
  - `EXT4_EXT_MAGIC` (macro, line 20) `#define EXT4_EXT_MAGIC`
  - `EXT4_S_IFMT` (macro, line 21) `#define EXT4_S_IFMT`
  - `EXT4_S_IFREG` (macro, line 22) `#define EXT4_S_IFREG`
  - `EXT4_S_IFDIR` (macro, line 23) `#define EXT4_S_IFDIR`
  - `EXT4_S_IFLNK` (macro, line 24) `#define EXT4_S_IFLNK`
  - `EXT4_EXTENTS_FL` (macro, line 25) `#define EXT4_EXTENTS_FL`
  - `EXT4_INDEX_FL` (macro, line 26) `#define EXT4_INDEX_FL`
  - `EXT4_ENCRYPT_FL` (macro, line 27) `#define EXT4_ENCRYPT_FL`
  - `EXT4_INLINE_FL` (macro, line 28) `#define EXT4_INLINE_FL`
  - `EXT4_EXT_UNINIT` (macro, line 29) `#define EXT4_EXT_UNINIT`
  - `EXT4_MBR_LINUX` (macro, line 30) `#define EXT4_MBR_LINUX`
- Depends on: `headers/ext4.h`, `headers/fsimg.h`, `headers/ide.h`, `headers/kernel.h`, `headers/minifs.h`
- Imported by: `tests/test_ext4.c`

## fs/fat32.c
- Layer: utility
- Doc: ================================================================
- Language: c
- Symbols:
  - `fat_geo_t` (struct, line 45)
  - `fat_ld16` (function, line 18) `static unsigned fat_ld16(const unsigned char *p)`
  - `fat_ld32` (function, line 22) `static unsigned fat_ld32(const unsigned char *p)`
  - `fat_img_open` (function, line 29) `static int fat_img_open(const char *resolved, fsimg_t *img)`
  - `fat_parse_bpb` (function, line 56) `static int fat_parse_bpb(const fsimg_t *img, fat_geo_t *g)`
  - `fat_mbr_is_fat` (function, line 114) `static int fat_mbr_is_fat(unsigned char t)`
  - `fat_dev_base` (function, line 182) `long fat_dev_base(void)`
  - `fat_clus_ok` (function, line 210) `static int fat_clus_ok(const fat_geo_t *g, unsigned c)`
  - `fat_entry` (function, line 217) `static int fat_entry(const fsimg_t *img, const fat_geo_t *g,
                     unsigned clus, ...`
  - `fat_eoc` (function, line 234) `static int fat_eoc(unsigned v)`
  - `fat_badch` (function, line 248) `static int fat_badch(char c)`
  - `fat_qword` (function, line 260) `static int fat_qword(const char *q, unsigned qlen, char name8[8],
                     char ext3[3])`
  - `fat_match` (function, line 291) `static int fat_match(const unsigned char *de, const char name8[8],
                     const cha...`
  - `fat_resolve` (function, line 307) `static int fat_resolve(const fsimg_t *img, const fat_geo_t *g,
                       const char ...`
  - `fat32_list` (function, line 407) `int fat32_list(const char *imgpath, const char *dirpath,
               char names[][FAT32_NAME_M...`
  - `fat32_vfs_open` (function, line 482) `int fat32_vfs_open(const char *path, int mode, void **handle)`
  - `fat_views` (function, line 523) `static void fat_views(const fat32_handle_t *h, fsimg_t *img,
                      fat_geo_t *g)`
  - `fat_seek` (function, line 542) `static int fat_seek(const fat32_handle_t *h, unsigned long pos,
                    unsigned *clu...`
  - `fat32_vfs_read` (function, line 567) `int fat32_vfs_read(void *handle, void *buf, unsigned long pos,
                   unsigned long len)`
  - `fat32_vfs_write` (function, line 607) `int fat32_vfs_write(void *handle, const void *buf, unsigned long pos,
                    unsigne...`
  - `fat32_vfs_close` (function, line 616) `int fat32_vfs_close(void *handle)`
  - `fat32_vfs_fstat` (function, line 621) `int fat32_vfs_fstat(void *handle, unsigned long *size_out)`
  - `fat32_vfs_truncate` (function, line 628) `int fat32_vfs_truncate(void *handle, unsigned long size)`
  - `FAT_MBR_SIG_OFF` (macro, line 105) `#define FAT_MBR_SIG_OFF`
  - `FAT_MBR_TAB_OFF` (macro, line 106) `#define FAT_MBR_TAB_OFF`
  - `FAT_MBR_ENTRY_SZ` (macro, line 107) `#define FAT_MBR_ENTRY_SZ`
  - `FAT_MBR_NENTRY` (macro, line 108) `#define FAT_MBR_NENTRY`
  - `FAT_MBR_TYPE_OFF` (macro, line 109) `#define FAT_MBR_TYPE_OFF`
  - `FAT_MBR_START_OFF` (macro, line 110) `#define FAT_MBR_START_OFF`
  - `FAT_MBR_COUNT_OFF` (macro, line 111) `#define FAT_MBR_COUNT_OFF`
  - `FAT_MBR_GPT_PROT` (macro, line 112) `#define FAT_MBR_GPT_PROT`
- Depends on: `headers/fat32.h`, `headers/fsimg.h`, `headers/ide.h`, `headers/kernel.h`, `headers/minifs.h`
- Imported by: `tests/test_fat32.c`

## fs/fsimg.c
- Layer: utility
- Doc: ================================================================
- Language: c
- Symbols:
  - `fsimg_open_file` (function, line 15) `int fsimg_open_file(const char *resolved, fsimg_t *img)`
  - `fsimg_open_dev` (function, line 51) `int fsimg_open_dev(unsigned long base_lba, unsigned long nsec,
                   fsimg_t *img)`
  - `fsimg_dev_read` (function, line 68) `static int fsimg_dev_read(const fsimg_t *img, unsigned long off,
                          void *...`
  - `fsimg_read` (function, line 86) `int fsimg_read(const fsimg_t *img, unsigned long off, void *buf,
               unsigned long len)`
  - `fsimg_split` (function, line 102) `int fsimg_split(const char *path, char *left, unsigned llen,
                char *right, unsigne...`
- Depends on: `headers/fsimg.h`, `headers/ide.h`, `headers/kernel.h`, `headers/minifs.h`
- Imported by: `tests/test_ext4.c`, `tests/test_fat32.c`

## fs/kfile.c
- Layer: utility
- Doc: ================================================================
- Language: c
- Symbols:
  - `kfile_stdin` (function, line 15) `KFILE *kfile_stdin(void)`
  - `kfile_stdout` (function, line 16) `KFILE *kfile_stdout(void)`
  - `kfile_stderr` (function, line 17) `KFILE *kfile_stderr(void)`
  - `recovery` (function, line 23) `* halts the machine with no recovery (the DOOM ABI-drift black screen),
 * so every public KFILE ...`
  - `kfile_corrupt` (function, line 28) `static int kfile_corrupt(const KFILE *f)`
  - `fs_take` (function, line 61) `static inline void fs_take(irqflags_t *flags)`
  - `fs_drop` (function, line 65) `static inline void fs_drop(irqflags_t flags)`
  - `kpipe_pair` (function, line 73) `int kpipe_pair(KFILE **rend_out, KFILE **wend_out)`
  - `kpipe_is_write_end` (function, line 125) `int kpipe_is_write_end(KFILE *f)`
  - `kpipe_grow` (function, line 132) `static int kpipe_grow(pipe_ring_t *ring)`
  - `kfopen` (function, line 155) `KFILE *kfopen(const char *path, const char *mode)`
  - `fs_rename_on_minifs` (function, line 250) `static int fs_rename_on_minifs(const char *dst)`
  - `entry` (function, line 269) `* directory with a volatile ramdisk entry (the kfopen misroute class) or
 * need a copy+delete th...`
  - `kfclose` (function, line 311) `int kfclose(KFILE *f)`
  - `kfgetc` (function, line 351) `int kfgetc(KFILE *f)`
  - `kfgets` (function, line 392) `char *kfgets(char *buf, int size, KFILE *f)`
  - `kfungetc` (function, line 406) `int kfungetc(int c, KFILE *f)`
  - `kfread` (function, line 413) `unsigned long kfread(void *ptr, unsigned long size, unsigned long n, KFILE *f)`
  - `kfwrite` (function, line 458) `unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long n, KFILE *f)`
  - `kfseek` (function, line 514) `int kfseek(KFILE *f, long offset, int whence)`
  - `kftell` (function, line 534) `long kftell(KFILE *f)`
  - `kfflush` (function, line 538) `int kfflush(KFILE *f)`
  - `kfputs` (function, line 561) `int kfputs(const char *s, KFILE *f)`
  - `kfputc` (function, line 567) `int kfputc(int c, KFILE *f)`
  - `krewind` (function, line 572) `void krewind(KFILE *f)`
- Depends on: `headers/kernel.h`, `headers/minifs.h`

## fs/minifs.c
- Layer: utility
- Doc: MiniFS: minimal Unix-like filesystem for MiniOS.
- Language: c
- Symbols:
  - `minifs_compress` (function, line 27) `unsigned int minifs_compress(const void *src, unsigned int src_len,
                             ...`
  - `minifs_decompress` (function, line 38) `unsigned int minifs_decompress(const void *src, unsigned int src_len,
                           ...`
  - `minifs_crc16` (function, line 49) `static unsigned short minifs_crc16(const void *data, unsigned int len)`
  - `minifs_crc32` (function, line 61) `static unsigned int minifs_crc32(const void *data, unsigned int len)`
  - `roundup4` (function, line 73) `static unsigned int roundup4(unsigned int v)`
  - `div_round_up` (function, line 75) `static unsigned int div_round_up(unsigned int n, unsigned int d)`
  - `returns` (function, line 84) `* overflowed the slot and smashed returns (measured ring-0 #UD on
 * lua->lua->cp). Every scratch...`
  - `blk_free` (function, line 92) `static void blk_free(unsigned char *b)`
  - `fs_write_super` (function, line 99) `static int fs_write_super(void)`
  - `fs_read_inode` (function, line 113) `static int fs_read_inode(unsigned int num, MiniFSInode *out)`
  - `fs_write_inode` (function, line 124) `static int fs_write_inode(unsigned int num, const MiniFSInode *in)`
  - `bm_test` (function, line 140) `static int bm_test(unsigned char *bm, unsigned int bit)`
  - `bm_set` (function, line 144) `static void bm_set(unsigned char *bm, unsigned int bit)`
  - `bm_clear` (function, line 148) `static void bm_clear(unsigned char *bm, unsigned int bit)`
  - `minifs_alloc_block` (function, line 154) `int minifs_alloc_block(void)`
  - `minifs_free_block` (function, line 171) `void minifs_free_block(unsigned int block)`
  - `minifs_alloc_inode` (function, line 179) `int minifs_alloc_inode(void)`
  - `minifs_free_inode` (function, line 191) `void minifs_free_inode(int num)`
  - `minifs_inode_get_block` (function, line 199) `int minifs_inode_get_block(MiniFSInode *inode, unsigned int logblk,
                           un...`
  - `fs_inode_set_block` (function, line 228) `static int fs_inode_set_block(MiniFSInode *inode, unsigned int logblk,
                          ...`
  - `minifs_inode_alloc_block` (function, line 282) `int minifs_inode_alloc_block(MiniFSInode *inode, unsigned int logblk)`
  - `fs_inode_free_all_blocks` (function, line 303) `static void fs_inode_free_all_blocks(MiniFSInode *inode)`
  - `journal_load_super` (function, line 385) `static void journal_load_super(void)`
  - `journal_save_super` (function, line 403) `static void journal_save_super(unsigned int state)`
  - `journal_save_entries` (function, line 417) `static void journal_save_entries(void)`
  - `minifs_journal_begin` (function, line 434) `void minifs_journal_begin(unsigned int txn_id)`
  - `minifs_journal_add_block` (function, line 443) `void minifs_journal_add_block(unsigned int block)`
  - `minifs_journal_commit` (function, line 450) `int minifs_journal_commit(unsigned int txn_id)`
  - `minifs_journal_clear` (function, line 460) `void minifs_journal_clear(void)`
  - `minifs_journal_abort` (function, line 470) `void minifs_journal_abort(void)`
  - `first` (function, line 495) `* keep the first (oldest) snapshot. */
void minifs_journal_touch(unsigned int phys)`
  - `minifs_journal_recover` (function, line 536) `void minifs_journal_recover(void)`
  - `fs_namecmp` (function, line 622) `static int fs_namecmp(const char *a, unsigned char alen, const char *b)`
  - `minifs_dir_lookup` (function, line 631) `int minifs_dir_lookup(int dir_ino, const char *name)`
  - `minifs_dir_add_entry` (function, line 661) `int minifs_dir_add_entry(int dir_ino, const char *name, int child_ino,
                          ...`
  - `minifs_dir_remove_entry` (function, line 799) `int minifs_dir_remove_entry(int dir_ino, const char *name)`
  - `minifs_dir_read` (function, line 830) `int minifs_dir_read(int dir_ino, int index, MiniFSDirEntry *out, char *name_out)`
  - `minifs_resolve_path` (function, line 880) `int minifs_resolve_path(const char *path)`
  - `minifs_create` (function, line 913) `int minifs_create(const char *path, unsigned short mode)`
  - `minifs_mkdir` (function, line 967) `int minifs_mkdir(const char *path, unsigned short mode)`
  - `minifs_unlink` (function, line 1017) `int minifs_unlink(const char *path)`
  - `minifs_split_parent` (function, line 1059) `static int minifs_split_parent(const char *path, char *parent_out,
                              ...`
  - `minifs_rename` (function, line 1084) `int minifs_rename(const char *oldpath, const char *newpath)`
  - `minifs_rmdir` (function, line 1116) `int minifs_rmdir(const char *path)`
  - `minifs_read` (function, line 1156) `int minifs_read(int inode_num, void *buf, unsigned int offset, unsigned int len)`
  - `minifs_write` (function, line 1227) `int minifs_write(int inode_num, const void *buf, unsigned int offset,
                 unsigned i...`
  - `minifs_truncate` (function, line 1316) `int minifs_truncate(int inode_num, unsigned int new_size)`
  - `minifs_stat` (function, line 1332) `int minifs_stat(int inode_num, MiniFSInode *out)`
  - `minifs_access` (function, line 1336) `int minifs_access(const char *path)`
  - `minifs_init` (function, line 1342) `void minifs_init(void)`
  - `minifs_get_lba_start` (function, line 1350) `unsigned int minifs_get_lba_start(void)`
  - `minifs_is_mounted` (function, line 1351) `int minifs_is_mounted(void)`
  - `minifs_mount` (function, line 1359) `int minifs_mount(void)`
  - `minifs_mkfs` (function, line 1509) `int minifs_mkfs(unsigned int total_blocks)`
  - `minifs_sync` (function, line 1580) `int minifs_sync(void)`
  - `minifs_file_open` (function, line 1595) `MiniFSFile *minifs_file_open(int inode_num, int flags)`
  - `minifs_file_close` (function, line 1609) `int minifs_file_close(MiniFSFile *f)`
  - `minifs_get_total_blocks` (function, line 1616) `unsigned int minifs_get_total_blocks(void)`
  - `minifs_usage` (function, line 1621) `void minifs_usage(unsigned int *free_b, unsigned int *total_b,
                  unsigned int *fr...`
  - `minifs_journal_touch` (function, line 15) `void minifs_journal_touch(unsigned int phys);`
  - `blocks` (function, line 494) `* blocks (self-protection);`
  - `DE_NAME` (macro, line 12) `#define DE_NAME(de)`
  - `DE_NAME_W` (macro, line 13) `#define DE_NAME_W(de)`
- Depends on: `headers/block.h`, `headers/ide.h`, `headers/kernel.h`, `headers/lz4_kernel.h`, `headers/minifs.h`

## fs/ramdisk.c
- Layer: infrastructure
- Doc: ================================================================
- Language: c
- Symbols:
  - `RDSuper` (struct, line 13)
  - `ramdisk_reserve` (function, line 24) `static int ramdisk_reserve(unsigned long want)`
  - `ramdisk_setup_from` (function, line 42) `void ramdisk_setup_from(void *data, unsigned size)`
  - `ramdisk_init` (function, line 94) `void ramdisk_init(void)`
  - `ramdisk_open` (function, line 111) `RDFile *ramdisk_open(const char *name)`
  - `ramdisk_read` (function, line 121) `int ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len)`
  - `ramdisk_write` (function, line 129) `int ramdisk_write(RDFile *f, const void *buf, unsigned offset, unsigned len)`
  - `ramdisk_create` (function, line 137) `RDFile *ramdisk_create(const char *name, unsigned size)`
  - `ramdisk_resize` (function, line 151) `int ramdisk_resize(RDFile *f, unsigned newsize)`
  - `ramdisk_list` (function, line 188) `int ramdisk_list(RDFile **out, int max)`
  - `ramdisk_count` (function, line 196) `int ramdisk_count(void)`
  - `ramdisk_usage` (function, line 202) `void ramdisk_usage(unsigned *used, unsigned *cap, unsigned *max)`
  - `ramdisk_file_name` (function, line 208) `const char *ramdisk_file_name(int idx)`
  - `ramdisk_delete` (function, line 213) `int ramdisk_delete(RDFile *f)`
  - `ramdisk_rename` (function, line 235) `int ramdisk_rename(const char *oldname, const char *newname)`
  - `RD_MAGIC` (macro, line 7) `#define RD_MAGIC`
  - `RD_HEADER_SIZE` (macro, line 8) `#define RD_HEADER_SIZE`
  - `RD_ENTRY_SIZE` (macro, line 9) `#define RD_ENTRY_SIZE`
  - `RD_DATA_MIN` (macro, line 10) `#define RD_DATA_MIN`
  - `RD_DATA_SPARE` (macro, line 11) `#define RD_DATA_SPARE`
- Depends on: `headers/kernel.h`

## fs/vfs.c
- Layer: utility
- Doc: ================================================================
- Language: c
- Symbols:
  - `vfs_mount_t` (struct, line 10)
  - `ramdisk_handle_t` (struct, line 159)
  - `minifs_handle_t` (struct, line 250)
  - `mem_file_t` (struct, line 336)
  - `vfs_init` (function, line 22) `void vfs_init(void)`
  - `vfs_register` (function, line 27) `int vfs_register(const char *prefix, const vfs_ops_t *ops, const char *driver)`
  - `vfs_unregister` (function, line 62) `int vfs_unregister(const char *prefix)`
  - `vfs_open` (function, line 106) `int vfs_open(const char *path, int mode, vfs_file_t *f)`
  - `ramdisk_vfs_open` (function, line 175) `static int ramdisk_vfs_open(const char *path, int mode, void **handle)`
  - `ramdisk_vfs_read` (function, line 201) `static int ramdisk_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len)`
  - `ramdisk_vfs_write` (function, line 210) `static int ramdisk_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len)`
  - `ramdisk_vfs_close` (function, line 218) `static int ramdisk_vfs_close(void *handle)`
  - `ramdisk_vfs_fstat` (function, line 224) `static int ramdisk_vfs_fstat(void *handle, unsigned long *size_out)`
  - `ramdisk_vfs_truncate` (function, line 231) `static int ramdisk_vfs_truncate(void *handle, unsigned long size)`
  - `minifs_vfs_open` (function, line 255) `static int minifs_vfs_open(const char *path, int mode, void **handle)`
  - `minifs_vfs_read` (function, line 283) `static int minifs_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len)`
  - `minifs_vfs_write` (function, line 292) `static int minifs_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len)`
  - `minifs_vfs_close` (function, line 300) `static int minifs_vfs_close(void *handle)`
  - `minifs_vfs_fstat` (function, line 306) `static int minifs_vfs_fstat(void *handle, unsigned long *size_out)`
  - `minifs_vfs_truncate` (function, line 313) `static int minifs_vfs_truncate(void *handle, unsigned long size)`
  - `mem_lookup` (function, line 345) `static int mem_lookup(const char *path)`
  - `mem_open` (function, line 353) `static int mem_open(const char *path, int mode, void **handle)`
  - `mem_slot` (function, line 373) `static int mem_slot(void *handle)`
  - `mem_read` (function, line 380) `static int mem_read(void *handle, void *buf, unsigned long pos, unsigned long len)`
  - `mem_write` (function, line 390) `static int mem_write(void *handle, const void *buf, unsigned long pos, unsigned long len)`
  - `mem_close` (function, line 401) `static int mem_close(void *handle)`
  - `mem_fstat` (function, line 405) `static int mem_fstat(void *handle, unsigned long *size_out)`
  - `mem_truncate` (function, line 412) `static int mem_truncate(void *handle, unsigned long size)`
  - `fs_resolve` (function, line 436) `int fs_resolve(const char *path, char *out, unsigned cap)`
  - `fs_dir_exists` (function, line 469) `int fs_dir_exists(const char *dir)`
  - `fs_is_dir` (function, line 494) `int fs_is_dir(const char *resolved)`
  - `minifs_mkdir_p` (function, line 507) `int minifs_mkdir_p(const char *resolved)`
  - `vfs_register_builtins` (function, line 530) `void vfs_register_builtins(void)`
  - `open` (function, line 544) `* open (loopback image file plus in-image path), so one registration
 * serves every image. */
in...`
  - `vfs_read` (function, line 565) `int vfs_read(vfs_file_t *f, void *buf, unsigned long len)`
  - `vfs_write` (function, line 574) `int vfs_write(vfs_file_t *f, const void *buf, unsigned long len)`
  - `vfs_close` (function, line 590) `int vfs_close(vfs_file_t *f)`
  - `vfs_fstat` (function, line 608) `int vfs_fstat(vfs_file_t *f, unsigned long *size_out)`
  - `MEM_FILES` (macro, line 332) `#define MEM_FILES`
  - `MEM_FNAME` (macro, line 333) `#define MEM_FNAME`
  - `MEM_FSIZE` (macro, line 334) `#define MEM_FSIZE`
- Depends on: `headers/ext4.h`, `headers/fat32.h`, `headers/kernel.h`, `headers/minifs.h`

## fs/zip.c
- Layer: utility
- Doc: zip.c — the unzip/zip shell builtins over the miniz zip library.
- Language: c
- Symbols:
  - `zip_read_whole` (function, line 25) `static unsigned char *zip_read_whole(const char *path, unsigned long *size)`
  - `marker` (function, line 50) `* marker (trailing '/') is preserved by the caller, not here. */
static int zip_sanitize_name(con...`
  - `zip_build_path` (function, line 79) `static int zip_build_path(const char *destdir, const char *name, char *out)`
  - `zip_ensure_dir_tree` (function, line 95) `static int zip_ensure_dir_tree(const char *dir)`
  - `zip_do_entry` (function, line 117) `static int zip_do_entry(mz_zip_archive *zip, mz_uint idx, const char *destdir)`
  - `shell_cmd_unzip` (function, line 176) `void shell_cmd_unzip(int argc, char **argv)`
  - `shell_cmd_zip` (function, line 254) `void shell_cmd_zip(int argc, char **argv)`
  - `root` (function, line 8) `* names are hostile data: each is normalized to forward slashes and rejected * when it escapes the extraction root (absolute paths, '.'/'..' components, * empty names), so a crafted archive can never `
  - `mz_zip_writer_mem_ptr` (function, line 18) `void *mz_zip_writer_mem_ptr(mz_zip_archive *pZip);`
  - `mz_zip_writer_mem_size` (function, line 19) `size_t mz_zip_writer_mem_size(mz_zip_archive *pZip);`
- Depends on: `headers/kernel.h`
