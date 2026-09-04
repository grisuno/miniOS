# Subsystem: fs

## fs/kfile.c
- Layer: utility
- Doc: include "kernel.h" include "minifs.h"  ================================================================
- Language: c
- Symbols:
  - `kfile_stdin` (function, line 14) `KFILE *kfile_stdin(void)`
  - `kfile_stdout` (function, line 16) `KFILE *kfile_stdout(void)`
  - `kfile_stderr` (function, line 17) `KFILE *kfile_stderr(void)`
  - `kfopen` (function, line 18) `KFILE *kfopen(const char *path, const char *mode)`
  - `kfclose` (function, line 88) `int kfclose(KFILE *f)`
  - `kfgetc` (function, line 101) `int kfgetc(KFILE *f)`
  - `kfgets` (function, line 122) `char *kfgets(char *buf, int size, KFILE *f)`
  - `kfungetc` (function, line 136) `int kfungetc(int c, KFILE *f)`
  - `kfread` (function, line 142) `unsigned long kfread(void *ptr, unsigned long size, unsigned long n, KFILE *f)`
  - `kfwrite` (function, line 164) `unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long n, KFILE *f)`
  - `kfseek` (function, line 193) `int kfseek(KFILE *f, long offset, int whence)`
  - `kftell` (function, line 207) `long kftell(KFILE *f)`
  - `kfflush` (function, line 211) `int kfflush(KFILE *f)`
  - `kfputs` (function, line 234) `int kfputs(const char *s, KFILE *f)`
  - `kfputc` (function, line 240) `int kfputc(int c, KFILE *f)`
  - `krewind` (function, line 245) `void krewind(KFILE *f)`

## fs/minifs.c
- Layer: utility
- Doc: MiniFS: minimal Unix-like filesystem for MiniOS.
- Language: c
- Symbols:
  - `minifs_compress` (function, line 23) `unsigned int minifs_compress(const void *src, unsigned int src_len,
                             ...`
  - `minifs_decompress` (function, line 33) `unsigned int minifs_decompress(const void *src, unsigned int src_len,
                           ...`
  - `minifs_crc16` (function, line 44) `static unsigned short minifs_crc16(const void *data, unsigned int len)`
  - `minifs_crc32` (function, line 56) `static unsigned int minifs_crc32(const void *data, unsigned int len)`
  - `roundup4` (function, line 68) `static unsigned int roundup4(unsigned int v)`
  - `div_round_up` (function, line 70) `static unsigned int div_round_up(unsigned int n, unsigned int d)`
  - `fs_write_super` (function, line 76) `static int fs_write_super(void)`
  - `fs_read_inode` (function, line 87) `static int fs_read_inode(unsigned int num, MiniFSInode *out)`
  - `fs_write_inode` (function, line 96) `static int fs_write_inode(unsigned int num, const MiniFSInode *in)`
  - `bm_test` (function, line 107) `static int bm_test(unsigned char *bm, unsigned int bit)`
  - `bm_set` (function, line 111) `static void bm_set(unsigned char *bm, unsigned int bit)`
  - `bm_clear` (function, line 115) `static void bm_clear(unsigned char *bm, unsigned int bit)`
  - `minifs_alloc_block` (function, line 121) `int minifs_alloc_block(void)`
  - `minifs_free_block` (function, line 138) `void minifs_free_block(unsigned int block)`
  - `minifs_alloc_inode` (function, line 146) `int minifs_alloc_inode(void)`
  - `minifs_free_inode` (function, line 158) `void minifs_free_inode(int num)`
  - `minifs_inode_get_block` (function, line 166) `int minifs_inode_get_block(MiniFSInode *inode, unsigned int logblk,
                           un...`
  - `fs_inode_set_block` (function, line 189) `static int fs_inode_set_block(MiniFSInode *inode, unsigned int logblk,
                          ...`
  - `minifs_inode_alloc_block` (function, line 235) `int minifs_inode_alloc_block(MiniFSInode *inode, unsigned int logblk)`
  - `fs_inode_free_all_blocks` (function, line 249) `static void fs_inode_free_all_blocks(MiniFSInode *inode)`
  - `journal_load_super` (function, line 319) `static void journal_load_super(void)`
  - `journal_save_super` (function, line 335) `static void journal_save_super(unsigned int state)`
  - `journal_save_entries` (function, line 346) `static void journal_save_entries(void)`
  - `minifs_journal_begin` (function, line 361) `void minifs_journal_begin(unsigned int txn_id)`
  - `minifs_journal_add_block` (function, line 368) `void minifs_journal_add_block(unsigned int block)`
  - `minifs_journal_commit` (function, line 393) `int minifs_journal_commit(unsigned int txn_id)`
  - `minifs_journal_recover` (function, line 411) `void minifs_journal_recover(void)`
  - `fs_namecmp` (function, line 451) `static int fs_namecmp(const char *a, unsigned char alen, const char *b)`
  - `minifs_dir_lookup` (function, line 460) `int minifs_dir_lookup(int dir_ino, const char *name)`
  - `minifs_dir_add_entry` (function, line 484) `int minifs_dir_add_entry(int dir_ino, const char *name, int child_ino,
                         u...`
  - `minifs_dir_remove_entry` (function, line 598) `int minifs_dir_remove_entry(int dir_ino, const char *name)`
  - `minifs_dir_read` (function, line 623) `int minifs_dir_read(int dir_ino, int index, MiniFSDirEntry *out, char *name_out)`
  - `minifs_resolve_path` (function, line 657) `int minifs_resolve_path(const char *path)`
  - `minifs_create` (function, line 690) `int minifs_create(const char *path, unsigned short mode)`
  - `minifs_mkdir` (function, line 742) `int minifs_mkdir(const char *path, unsigned short mode)`
  - `minifs_unlink` (function, line 792) `int minifs_unlink(const char *path)`
  - `minifs_rmdir` (function, line 828) `int minifs_rmdir(const char *path)`
  - `minifs_read` (function, line 865) `int minifs_read(int inode_num, void *buf, unsigned int offset, unsigned int len)`
  - `minifs_write` (function, line 929) `int minifs_write(int inode_num, const void *buf, unsigned int offset,
                 unsigned i...`
  - `minifs_truncate` (function, line 1012) `int minifs_truncate(int inode_num, unsigned int new_size)`
  - `minifs_stat` (function, line 1028) `int minifs_stat(int inode_num, MiniFSInode *out)`
  - `minifs_access` (function, line 1032) `int minifs_access(const char *path)`
  - `minifs_init` (function, line 1038) `void minifs_init(void)`
  - `minifs_get_lba_start` (function, line 1046) `unsigned int minifs_get_lba_start(void)`
  - `minifs_is_mounted` (function, line 1048) `int minifs_is_mounted(void)`
  - `minifs_mount` (function, line 1049) `int minifs_mount(void)`
  - `minifs_mkfs` (function, line 1123) `int minifs_mkfs(unsigned int total_blocks)`
  - `minifs_sync` (function, line 1194) `int minifs_sync(void)`
  - `minifs_file_open` (function, line 1209) `MiniFSFile *minifs_file_open(int inode_num, int flags)`
  - `minifs_file_close` (function, line 1223) `int minifs_file_close(MiniFSFile *f)`
  - `minifs_get_total_blocks` (function, line 1230) `unsigned int minifs_get_total_blocks(void)`
  - `DE_NAME` (macro, line 12)
  - `DE_NAME_W` (macro, line 13)

## fs/ramdisk.c
- Layer: infrastructure
- Doc: include "kernel.h"  ================================================================
- Language: c
- Symbols:
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
  - `ramdisk_file_name` (function, line 201) `const char *ramdisk_file_name(int idx)`
  - `ramdisk_delete` (function, line 206) `int ramdisk_delete(RDFile *f)`
  - `RD_MAGIC` (macro, line 6)
  - `RD_HEADER_SIZE` (macro, line 8)
  - `RD_ENTRY_SIZE` (macro, line 9)
  - `RD_DATA_MIN` (macro, line 10)
  - `RD_DATA_SPARE` (macro, line 11)
  - `RD_DATA_MAX` (macro, line 12)

## fs/vfs.c
- Layer: utility
- Doc: include "kernel.h" include "minifs.h"  ================================================================
- Language: c
- Symbols:
  - `vfs_init` (function, line 19) `void vfs_init(void)`
  - `vfs_register` (function, line 24) `int vfs_register(const char *prefix, const vfs_ops_t *ops)`
  - `vfs_unregister` (function, line 40) `int vfs_unregister(const char *prefix)`
  - `vfs_open` (function, line 52) `int vfs_open(const char *path, int mode, vfs_file_t *f)`
  - `ramdisk_vfs_open` (function, line 85) `static int ramdisk_vfs_open(const char *path, int mode, void **handle)`
  - `ramdisk_vfs_read` (function, line 110) `static int ramdisk_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len)`
  - `ramdisk_vfs_write` (function, line 119) `static int ramdisk_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len)`
  - `ramdisk_vfs_close` (function, line 127) `static int ramdisk_vfs_close(void *handle)`
  - `ramdisk_vfs_fstat` (function, line 133) `static int ramdisk_vfs_fstat(void *handle, unsigned long *size_out)`
  - `ramdisk_vfs_truncate` (function, line 140) `static int ramdisk_vfs_truncate(void *handle, unsigned long size)`
  - `minifs_vfs_open` (function, line 164) `static int minifs_vfs_open(const char *path, int mode, void **handle)`
  - `minifs_vfs_read` (function, line 192) `static int minifs_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len)`
  - `minifs_vfs_write` (function, line 201) `static int minifs_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len)`
  - `minifs_vfs_close` (function, line 209) `static int minifs_vfs_close(void *handle)`
  - `minifs_vfs_fstat` (function, line 215) `static int minifs_vfs_fstat(void *handle, unsigned long *size_out)`
  - `minifs_vfs_truncate` (function, line 222) `static int minifs_vfs_truncate(void *handle, unsigned long size)`
  - `fs_resolve` (function, line 243) `int fs_resolve(const char *path, char *out, unsigned cap)`
  - `fs_dir_exists` (function, line 276) `int fs_dir_exists(const char *dir)`
  - `fs_is_dir` (function, line 301) `int fs_is_dir(const char *resolved)`
  - `minifs_mkdir_p` (function, line 314) `int minifs_mkdir_p(const char *resolved)`
  - `vfs_register_builtins` (function, line 337) `void vfs_register_builtins(void)`
  - `VFS_MAX_MOUNTS` (macro, line 7)
  - `VFS_PREFIX_LEN` (macro, line 9)

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
