# Subsystem: fs

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
  - `kfclose` (function, line 232) `int kfclose(KFILE *f)`
  - `kfgetc` (function, line 272) `int kfgetc(KFILE *f)`
  - `kfgets` (function, line 313) `char *kfgets(char *buf, int size, KFILE *f)`
  - `kfungetc` (function, line 327) `int kfungetc(int c, KFILE *f)`
  - `kfread` (function, line 334) `unsigned long kfread(void *ptr, unsigned long size, unsigned long n, KFILE *f)`
  - `kfwrite` (function, line 379) `unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long n, KFILE *f)`
  - `kfseek` (function, line 435) `int kfseek(KFILE *f, long offset, int whence)`
  - `kftell` (function, line 455) `long kftell(KFILE *f)`
  - `kfflush` (function, line 459) `int kfflush(KFILE *f)`
  - `kfputs` (function, line 482) `int kfputs(const char *s, KFILE *f)`
  - `kfputc` (function, line 488) `int kfputc(int c, KFILE *f)`
  - `krewind` (function, line 493) `void krewind(KFILE *f)`
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
  - `minifs_resolve_path` (function, line 869) `int minifs_resolve_path(const char *path)`
  - `minifs_create` (function, line 902) `int minifs_create(const char *path, unsigned short mode)`
  - `minifs_mkdir` (function, line 956) `int minifs_mkdir(const char *path, unsigned short mode)`
  - `minifs_unlink` (function, line 1006) `int minifs_unlink(const char *path)`
  - `minifs_rmdir` (function, line 1045) `int minifs_rmdir(const char *path)`
  - `minifs_read` (function, line 1085) `int minifs_read(int inode_num, void *buf, unsigned int offset, unsigned int len)`
  - `minifs_write` (function, line 1156) `int minifs_write(int inode_num, const void *buf, unsigned int offset,
                 unsigned i...`
  - `minifs_truncate` (function, line 1245) `int minifs_truncate(int inode_num, unsigned int new_size)`
  - `minifs_stat` (function, line 1261) `int minifs_stat(int inode_num, MiniFSInode *out)`
  - `minifs_access` (function, line 1265) `int minifs_access(const char *path)`
  - `minifs_init` (function, line 1271) `void minifs_init(void)`
  - `minifs_get_lba_start` (function, line 1279) `unsigned int minifs_get_lba_start(void)`
  - `minifs_is_mounted` (function, line 1280) `int minifs_is_mounted(void)`
  - `minifs_mount` (function, line 1288) `int minifs_mount(void)`
  - `minifs_mkfs` (function, line 1438) `int minifs_mkfs(unsigned int total_blocks)`
  - `minifs_sync` (function, line 1509) `int minifs_sync(void)`
  - `minifs_file_open` (function, line 1524) `MiniFSFile *minifs_file_open(int inode_num, int flags)`
  - `minifs_file_close` (function, line 1538) `int minifs_file_close(MiniFSFile *f)`
  - `minifs_get_total_blocks` (function, line 1545) `unsigned int minifs_get_total_blocks(void)`
  - `minifs_usage` (function, line 1550) `void minifs_usage(unsigned int *free_b, unsigned int *total_b,
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
  - `vfs_mount_t` (struct, line 8)
  - `ramdisk_handle_t` (struct, line 157)
  - `minifs_handle_t` (struct, line 248)
  - `mem_file_t` (struct, line 334)
  - `vfs_init` (function, line 20) `void vfs_init(void)`
  - `vfs_register` (function, line 25) `int vfs_register(const char *prefix, const vfs_ops_t *ops, const char *driver)`
  - `vfs_unregister` (function, line 60) `int vfs_unregister(const char *prefix)`
  - `vfs_open` (function, line 104) `int vfs_open(const char *path, int mode, vfs_file_t *f)`
  - `ramdisk_vfs_open` (function, line 173) `static int ramdisk_vfs_open(const char *path, int mode, void **handle)`
  - `ramdisk_vfs_read` (function, line 199) `static int ramdisk_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len)`
  - `ramdisk_vfs_write` (function, line 208) `static int ramdisk_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len)`
  - `ramdisk_vfs_close` (function, line 216) `static int ramdisk_vfs_close(void *handle)`
  - `ramdisk_vfs_fstat` (function, line 222) `static int ramdisk_vfs_fstat(void *handle, unsigned long *size_out)`
  - `ramdisk_vfs_truncate` (function, line 229) `static int ramdisk_vfs_truncate(void *handle, unsigned long size)`
  - `minifs_vfs_open` (function, line 253) `static int minifs_vfs_open(const char *path, int mode, void **handle)`
  - `minifs_vfs_read` (function, line 281) `static int minifs_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len)`
  - `minifs_vfs_write` (function, line 290) `static int minifs_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len)`
  - `minifs_vfs_close` (function, line 298) `static int minifs_vfs_close(void *handle)`
  - `minifs_vfs_fstat` (function, line 304) `static int minifs_vfs_fstat(void *handle, unsigned long *size_out)`
  - `minifs_vfs_truncate` (function, line 311) `static int minifs_vfs_truncate(void *handle, unsigned long size)`
  - `mem_lookup` (function, line 343) `static int mem_lookup(const char *path)`
  - `mem_open` (function, line 351) `static int mem_open(const char *path, int mode, void **handle)`
  - `mem_slot` (function, line 371) `static int mem_slot(void *handle)`
  - `mem_read` (function, line 378) `static int mem_read(void *handle, void *buf, unsigned long pos, unsigned long len)`
  - `mem_write` (function, line 388) `static int mem_write(void *handle, const void *buf, unsigned long pos, unsigned long len)`
  - `mem_close` (function, line 399) `static int mem_close(void *handle)`
  - `mem_fstat` (function, line 403) `static int mem_fstat(void *handle, unsigned long *size_out)`
  - `mem_truncate` (function, line 410) `static int mem_truncate(void *handle, unsigned long size)`
  - `fs_resolve` (function, line 434) `int fs_resolve(const char *path, char *out, unsigned cap)`
  - `fs_dir_exists` (function, line 467) `int fs_dir_exists(const char *dir)`
  - `fs_is_dir` (function, line 492) `int fs_is_dir(const char *resolved)`
  - `minifs_mkdir_p` (function, line 505) `int minifs_mkdir_p(const char *resolved)`
  - `vfs_register_builtins` (function, line 528) `void vfs_register_builtins(void)`
  - `vfs_mount_driver` (function, line 539) `int vfs_mount_driver(const char *prefix, const char *driver)`
  - `vfs_read` (function, line 556) `int vfs_read(vfs_file_t *f, void *buf, unsigned long len)`
  - `vfs_write` (function, line 565) `int vfs_write(vfs_file_t *f, const void *buf, unsigned long len)`
  - `vfs_close` (function, line 581) `int vfs_close(vfs_file_t *f)`
  - `vfs_fstat` (function, line 599) `int vfs_fstat(vfs_file_t *f, unsigned long *size_out)`
  - `MEM_FILES` (macro, line 330) `#define MEM_FILES`
  - `MEM_FNAME` (macro, line 331) `#define MEM_FNAME`
  - `MEM_FSIZE` (macro, line 332) `#define MEM_FSIZE`
- Depends on: `headers/kernel.h`, `headers/minifs.h`

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
