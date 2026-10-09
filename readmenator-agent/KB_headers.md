# Subsystem: headers (page 1 of 5)
Pages: [KB_headers.md](KB_headers.md), [KB_headers_p2.md](KB_headers_p2.md), [KB_headers_p3.md](KB_headers_p3.md), [KB_headers_p4.md](KB_headers_p4.md), [KB_headers_p5.md](KB_headers_p5.md)

## headers/abi.h
- Doc: Docstring: abi.h -- Boot-time ABI manifest gate contract.
- Layer: utility
- Language: h
- Symbols:
  - `abi_verify` (function, line 25) `int abi_verify(const char *text, long version, unsigned long checksum);`
  - `abi_check_manifest` (function, line 28) `int abi_check_manifest(void);`
  - `ABI_H` (macro, line 14) `#define ABI_H`
  - `ABI_OK` (macro, line 16) `#define ABI_OK`
  - `ABI_NO_MANIFEST` (macro, line 17) `#define ABI_NO_MANIFEST`
  - `ABI_BAD_FORMAT` (macro, line 18) `#define ABI_BAD_FORMAT`
  - `ABI_VERSION_MISMATCH` (macro, line 19) `#define ABI_VERSION_MISMATCH`
  - `ABI_CHECKSUM_MISMATCH` (macro, line 20) `#define ABI_CHECKSUM_MISMATCH`
  - `ABI_MANIFEST_NAME` (macro, line 22) `#define ABI_MANIFEST_NAME`
  - `ABI_MANIFEST_MAX` (macro, line 23) `#define ABI_MANIFEST_MAX`
- Imported by: `kernel.c`, `kernel/abi.c`, `tests/test_abi.c`

## headers/ap_stub.h
- Doc: generated from ap_stub.bin - do not edit
- Layer: testing
- Language: h
- Imported by: `smp.c`

## headers/arena.h
- Doc: Docstring: bump arena for MiniOS, kernel and ring-3 alike.
- Layer: utility
- Language: h
- Symbols:
  - `minios_arena` (struct, line 41)
  - `arena_init` (function, line 48) `static inline void arena_init(arena_t *a, void *block, size_t size)`
  - `arena_align_up` (function, line 62) `static inline size_t arena_align_up(size_t n, size_t align)`
  - `arena_bytes_for` (function, line 74) `static inline size_t arena_bytes_for(size_t count, size_t elem_size)`
  - `arena_alloc` (function, line 81) `static inline void *arena_alloc(arena_t *a, size_t size, size_t align)`
  - `arena_used` (function, line 95) `static inline size_t arena_used(const arena_t *a)`
  - `arena_free_bytes` (function, line 101) `static inline size_t arena_free_bytes(const arena_t *a)`
  - `arena_reset` (function, line 107) `static inline void arena_reset(arena_t *a)`
  - `arena_checkpoint` (function, line 113) `static inline size_t arena_checkpoint(const arena_t *a)`
  - `arena_rewind` (function, line 119) `static inline int arena_rewind(arena_t *a, size_t checkpoint)`
  - `arena_contains` (function, line 128) `static inline int arena_contains(const arena_t *a, const void *ptr)`
  - `kmalloc` (function, line 3) `* * A bump arena serves one kmalloc (kernel) or malloc (ring-3) with pointer * bumps instead of N allocator round...`
  - `kfree` (function, line 25) `* kfree(back);`
  - `MINIOS_ARENA_H` (macro, line 33) `#define MINIOS_ARENA_H`
  - `ARENA_DEFAULT_ALIGN` (macro, line 38) `#define ARENA_DEFAULT_ALIGN`
- Imported by: `kernel/spawn.c`, `tests/test_arena.c`

## headers/audio.h
- Doc: Unified audio API for MiniOS.
- Layer: utility
- Language: h
- Symbols:
  - `audio_init` (function, line 21) `int audio_init(void);`
  - `audio_tone` (function, line 24) `void audio_tone(unsigned freq);`
  - `audio_pcm_open` (function, line 27) `int audio_pcm_open(unsigned rate, unsigned channels, unsigned format);`
  - `audio_pcm_submit` (function, line 28) `int audio_pcm_submit(const void *buf, unsigned len);`
  - `audio_pcm_pump` (function, line 29) `void audio_pcm_pump(void);`
  - `audio_pcm_close` (function, line 30) `void audio_pcm_close(void);`
  - `audio_set_volume` (function, line 33) `void audio_set_volume(unsigned volume);`
  - `audio_get_volume` (function, line 34) `unsigned audio_get_volume(void);`
  - `audio_sb16_present` (function, line 37) `int audio_sb16_present(void);`
  - `audio_stream_open` (function, line 40) `int audio_stream_open(void);`
  - `audio_stream_close` (function, line 41) `void audio_stream_close(int id);`
  - `audio_stream_submit` (function, line 42) `int audio_stream_submit(int id, const void *buf, unsigned len);`
  - `audio_stream_volume` (function, line 43) `void audio_stream_volume(int id, unsigned char vol);`
  - `AUDIO_H` (macro, line 2) `#define AUDIO_H`
  - `AUDIO_RATE_DEFAULT` (macro, line 15) `#define AUDIO_RATE_DEFAULT`
  - `AUDIO_CHANNELS_MONO` (macro, line 16) `#define AUDIO_CHANNELS_MONO`
  - `AUDIO_FORMAT_U8` (macro, line 17) `#define AUDIO_FORMAT_U8`
  - `AUDIO_FORMAT_S16` (macro, line 18) `#define AUDIO_FORMAT_S16`
- Imported by: `progs/pokemon/platform_minios.c`

## headers/batch.h
- Doc: Docstring: batch.h -- Batched synchronous syscall submission.
- Layer: utility
- Language: h
- Symbols:
  - `batch_op_t` (struct, line 53)
  - `batch_exec` (function, line 62) `long batch_exec(const batch_op_t *ops, long *results, int count, int *completed, batch_handler_t dispatch);`
  - `BATCH_H` (macro, line 2) `#define BATCH_H`
  - `BATCH_MAX_OPS` (macro, line 41) `#define BATCH_MAX_OPS`
  - `BATCH_OP_NOP` (macro, line 43) `#define BATCH_OP_NOP`
  - `BATCH_OP_YIELD` (macro, line 44) `#define BATCH_OP_YIELD`
  - `BATCH_OP_TIME` (macro, line 45) `#define BATCH_OP_TIME`
  - `BATCH_OP_GETPID` (macro, line 46) `#define BATCH_OP_GETPID`
  - `BATCH_OK` (macro, line 48) `#define BATCH_OK`
  - `BATCH_ERR_COUNT` (macro, line 49) `#define BATCH_ERR_COUNT`
  - `BATCH_ERR_PTR` (macro, line 50) `#define BATCH_ERR_PTR`
  - `BATCH_ERR_OPCODE` (macro, line 51) `#define BATCH_ERR_OPCODE`
- Imported by: `kernel/batch.c`, `kernel/syscalls.c`, `tests/test_batch.c`

## headers/block.h
- Doc: Block device abstraction for MiniFS.
- Layer: utility
- Language: h
- Symbols:
  - `block_init` (function, line 12) `void block_init(void);`
  - `block_set_base` (function, line 15) `void block_set_base(unsigned int lba_base);`
  - `block_read` (function, line 18) `int block_read(unsigned int block_num, void *buf);`
  - `block_write` (function, line 19) `int block_write(unsigned int block_num, const void *buf);`
  - `block_read_multi` (function, line 23) `int block_read_multi(unsigned int block_num, unsigned int count, void *buf);`
  - `block_write_multi` (function, line 24) `int block_write_multi(unsigned int block_num, unsigned int count, const void *buf);`
  - `block_flush` (function, line 27) `void block_flush(void);`
  - `block_total` (function, line 30) `unsigned int block_total(void);`
  - `block_read_sectors` (function, line 37) `int block_read_sectors(unsigned lba, unsigned count, void *buf);`
  - `block_disk_sectors` (function, line 40) `unsigned long block_disk_sectors(void);`
  - `BLOCK_H` (macro, line 2) `#define BLOCK_H`
  - `BLOCK_SIZE` (macro, line 7) `#define BLOCK_SIZE`
  - `BLOCK_SHIFT` (macro, line 8) `#define BLOCK_SHIFT`
  - `SECTORS_PER_BLOCK` (macro, line 9) `#define SECTORS_PER_BLOCK`
- Imported by: `drivers/block.c`, `fs/ext4.c`, `fs/fat32.c`, `fs/fsimg.c`, `fs/minifs.c`, `kernel.c`, `kernel/syscalls.c`

## headers/desktop_icons.h
- Doc: embedded icon pixel data for desktop shortcuts.
- Layer: utility
- Language: h
- Symbols:
  - `DESKTOP_ICONS_H` (macro, line 8) `#define DESKTOP_ICONS_H`
  - `ICON_EMBEDDED_W` (macro, line 12) `#define ICON_EMBEDDED_W`
  - `ICON_EMBEDDED_H` (macro, line 13) `#define ICON_EMBEDDED_H`
- Imported by: `kernel/vga_fb.c`

## headers/desktop_shortcuts.h
- Doc: configurable desktop icon shortcuts.
- Layer: utility
- Language: h
- Symbols:
  - `desktop_shortcut` (struct, line 72)
  - `desktop_shortcuts_load` (function, line 82) `void desktop_shortcuts_load(void);`
  - `desktop_shortcuts_draw` (function, line 85) `void desktop_shortcuts_draw(void);`
  - `desktop_shortcuts_hit_test` (function, line 89) `const char *desktop_shortcuts_hit_test(int mx, int my);`
  - `DESKTOP_SHORTCUTS_H` (macro, line 13) `#define DESKTOP_SHORTCUTS_H`
  - `MAX_SHORTCUTS` (macro, line 18) `#define MAX_SHORTCUTS`
  - `SHORTCUT_NAME_LEN` (macro, line 19) `#define SHORTCUT_NAME_LEN`
  - `SHORTCUT_CMD_LEN` (macro, line 20) `#define SHORTCUT_CMD_LEN`
  - `SHORTCUT_PATH_LEN` (macro, line 21) `#define SHORTCUT_PATH_LEN`
  - `ICON_W` (macro, line 24) `#define ICON_W`
  - `ICON_H` (macro, line 25) `#define ICON_H`
  - `ICON_PAD_X` (macro, line 26) `#define ICON_PAD_X`
  - `ICON_PAD_Y` (macro, line 27) `#define ICON_PAD_Y`
  - `ICON_LABEL_H` (macro, line 28) `#define ICON_LABEL_H`
  - `DOCK_PAD_X` (macro, line 33) `#define DOCK_PAD_X`
  - `DOCK_PAD_Y` (macro, line 34) `#define DOCK_PAD_Y`
  - `DOCK_GAP` (macro, line 35) `#define DOCK_GAP`
  - `DOCK_LABEL_GAP` (macro, line 36) `#define DOCK_LABEL_GAP`
  - `DOCK_CRYSTAL_STEP` (macro, line 41) `#define DOCK_CRYSTAL_STEP`
  - `DOCK_MAG_W` (macro, line 48) `#define DOCK_MAG_W`
  - `DOCK_MAG_H` (macro, line 49) `#define DOCK_MAG_H`
  - `DOCK_NEAR_W` (macro, line 50) `#define DOCK_NEAR_W`
  - `DOCK_NEAR_H` (macro, line 51) `#define DOCK_NEAR_H`
  - `DOCK_BOUNCE_H` (macro, line 57) `#define DOCK_BOUNCE_H`
  - `DOCK_BOUNCE_TICKS` (macro, line 58) `#define DOCK_BOUNCE_TICKS`
  - `ICON_PAL_BASE` (macro, line 65) `#define ICON_PAL_BASE`
  - `ICON_PAL_SIZE` (macro, line 66) `#define ICON_PAL_SIZE`
- Imported by: `kernel/vga_fb.c`

## headers/driver.h
- Doc: Strategy pattern for hardware drivers (thesis correction 2).
- Layer: infrastructure
- Language: h
- Symbols:
  - `device` (struct, line 48)
  - `block_ops_t` (struct, line 28)
  - `audio_ops_t` (struct, line 37)
  - `device_t` (type_alias, line 25) `typedef struct device device_t;`
  - `device_register` (function, line 56) `int device_register(device_t *dev);`
  - `device_find` (function, line 57) `device_t *device_find(const char *name);`
  - `device_find_by_type` (function, line 58) `device_t *device_find_by_type(int type);`
  - `device_count` (function, line 59) `int device_count(void);`
  - `device_reset` (function, line 60) `void device_reset(void);`
  - `DRIVER_H` (macro, line 2) `#define DRIVER_H`
  - `DEV_NAME_LEN` (macro, line 18) `#define DEV_NAME_LEN`
  - `DEV_MAX` (macro, line 19) `#define DEV_MAX`
  - `DEV_TYPE_BLOCK` (macro, line 21) `#define DEV_TYPE_BLOCK`
  - `DEV_TYPE_AUDIO` (macro, line 22) `#define DEV_TYPE_AUDIO`
  - `DEV_TYPE_NET` (macro, line 23) `#define DEV_TYPE_NET`
  - `DEV_TYPE_CHAR` (macro, line 24) `#define DEV_TYPE_CHAR`
- Imported by: `drivers/block.c`, `drivers/driver.c`, `drivers/ide.c`, `drivers/pcspk.c`, `drivers/sb16.c`, `drivers/usbblk.c`, `drivers/virtio_blk.c`, `kernel/syscalls.c`, `tests/test_driver.c`, `tests/test_usbblk.c`

## headers/editor.h
- Doc: the built-in line editor contract.
- Layer: utility
- Language: h
- Symbols:
  - `shell_cmd_edit` (function, line 15) `void shell_cmd_edit(int argc, char **argv);`
  - `EDITOR_H` (macro, line 2) `#define EDITOR_H`
- Depends on: `headers/kernel.h`
- Imported by: `kernel/editor.c`, `kernel/shell.c`

## headers/ext4.h
- Doc: Read-only ext4 loopback/device driver.
- Layer: utility
- Language: h
- Symbols:
  - `ext4_handle_t` (struct, line 22)
  - `ext4_list` (function, line 35) `int ext4_list(const char *imgpath, const char *dirpath, char names[][EXT4_NAME_MAX + 1], int *isdir, int cap);`
  - `ext4_vfs_open` (function, line 40) `int ext4_vfs_open(const char *path, int mode, void **handle);`
  - `ext4_vfs_read` (function, line 41) `int ext4_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len);`
  - `ext4_vfs_write` (function, line 43) `int ext4_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len);`
  - `ext4_vfs_close` (function, line 45) `int ext4_vfs_close(void *handle);`
  - `ext4_vfs_fstat` (function, line 46) `int ext4_vfs_fstat(void *handle, unsigned long *size_out);`
  - `ext4_vfs_truncate` (function, line 47) `int ext4_vfs_truncate(void *handle, unsigned long size);`
  - `first` (function, line 50) `* MBR 0x83 entry first (proven by a superblock read), then a magic * scan over 2048-aligned LBAs for superfloppy...`
  - `ext4_vfs_ops` (variable, line 55) `extern const vfs_ops_t ext4_vfs_ops;`
  - `EXT4_H` (macro, line 2) `#define EXT4_H`
  - `EXT4_NAME_MAX` (macro, line 16) `#define EXT4_NAME_MAX`
  - `EXT4_MAX_DEPTH` (macro, line 17) `#define EXT4_MAX_DEPTH`
  - `EXT4_LIST_CAP` (macro, line 18) `#define EXT4_LIST_CAP`
  - `EXT4_PATH_MAX` (macro, line 19) `#define EXT4_PATH_MAX`
- Imported by: `fs/ext4.c`, `fs/vfs.c`, `kernel/shell.c`, `tests/test_ext4.c`

## headers/fat32.h
- Doc: Read-only FAT32 loopback driver over ramdisk/MiniFS images.
- Layer: utility
- Language: h
- Symbols:
  - `fat32_handle_t` (struct, line 25)
  - `file` (function, line 6) `* * A FAT32 disk image stored as a regular file (built on the host with * mkfs.vfat, packed into minifs.bin) is...`
  - `fat32_list` (function, line 45) `int fat32_list(const char *imgpath, const char *dirpath, char names[][FAT32_NAME_MAX], int *isdir, int cap);`
  - `fat_dev_base` (function, line 54) `long fat_dev_base(void);`
  - `fat32_vfs_open` (function, line 58) `int fat32_vfs_open(const char *path, int mode, void **handle);`
  - `fat32_vfs_read` (function, line 59) `int fat32_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len);`
  - `fat32_vfs_write` (function, line 61) `int fat32_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len);`
  - `fat32_vfs_close` (function, line 63) `int fat32_vfs_close(void *handle);`
  - `fat32_vfs_fstat` (function, line 64) `int fat32_vfs_fstat(void *handle, unsigned long *size_out);`
  - `fat32_vfs_truncate` (function, line 65) `int fat32_vfs_truncate(void *handle, unsigned long size);`
  - `fat32_vfs_ops` (variable, line 67) `extern const vfs_ops_t fat32_vfs_ops;`
  - `FAT32_H` (macro, line 2) `#define FAT32_H`
  - `FAT32_NAME_MAX` (macro, line 16) `#define FAT32_NAME_MAX`
  - `FAT32_MAX_DEPTH` (macro, line 17) `#define FAT32_MAX_DEPTH`
  - `FAT32_LIST_CAP` (macro, line 18) `#define FAT32_LIST_CAP`
  - `FAT32_CLUS_MAX` (macro, line 19) `#define FAT32_CLUS_MAX`
- Imported by: `fs/fat32.c`, `fs/vfs.c`, `kernel/shell.c`, `tests/test_fat32.c`

## headers/fsimg.h
- Doc: One image backend for read-only filesystem drivers.
- Layer: utility
- Language: h
- Symbols:
  - `fsimg_t` (struct, line 13)
  - `fsimg_open_file` (function, line 23) `int fsimg_open_file(const char *resolved, fsimg_t *img);`
  - `fsimg_open_dev` (function, line 27) `int fsimg_open_dev(unsigned long base_lba, unsigned long nsec, fsimg_t *img);`
  - `fsimg_read` (function, line 32) `int fsimg_read(const fsimg_t *img, unsigned long off, void *buf, unsigned long len);`
  - `fsimg_split` (function, line 40) `int fsimg_split(const char *path, char *left, unsigned llen, char *right, unsigned rlen);`
  - `FSIMG_H` (macro, line 2) `#define FSIMG_H`
- Imported by: `fs/ext4.c`, `fs/fat32.c`, `fs/fsimg.c`, `tests/test_ext4.c`, `tests/test_fat32.c`

## headers/futex.h
- Doc: Docstring: futex.h -- Fast userspace mutex sleep/wake contract.
- Layer: utility
- Language: h
- Symbols:
  - `futex_bucket_t` (struct, line 68)
  - `futex_init` (function, line 74) `void futex_init(void);`
  - `futex_wait` (function, line 75) `long futex_wait(unsigned long uaddr, int val);`
  - `futex_wake` (function, line 76) `long futex_wake(unsigned long uaddr, int n);`
  - `FUTEX_PRIVATE_FLAG` (function, line 79) `* FUTEX_PRIVATE_FLAG (process-private is served on the same global * buckets: same semantics, no isolation...`
  - `futex_linux_cmd` (function, line 84) `int futex_linux_cmd(long op);`
  - `FUTEX_H` (macro, line 2) `#define FUTEX_H`
  - `FUTEX_BUCKETS` (macro, line 51) `#define FUTEX_BUCKETS`
  - `FUTEX_BUCKET_MASK` (macro, line 52) `#define FUTEX_BUCKET_MASK`
  - `FUTEX_HASH_GOLDEN` (macro, line 53) `#define FUTEX_HASH_GOLDEN`
  - `FUTEX_OK` (macro, line 55) `#define FUTEX_OK`
  - `FUTEX_NOMATCH` (macro, line 56) `#define FUTEX_NOMATCH`
  - `FUTEX_NOPROC` (macro, line 57) `#define FUTEX_NOPROC`
  - `FUTEX_WAKE_ALL` (macro, line 58) `#define FUTEX_WAKE_ALL`
  - `LINUX_FUTEX_WAIT` (macro, line 64) `#define LINUX_FUTEX_WAIT`
  - `LINUX_FUTEX_WAKE` (macro, line 65) `#define LINUX_FUTEX_WAKE`
  - `LINUX_FUTEX_PRIVATE_FLAG` (macro, line 66) `#define LINUX_FUTEX_PRIVATE_FLAG`
- Depends on: `headers/sched.h`, `headers/spinlock.h`, `headers/sync.h`
- Imported by: `kernel/futex.c`, `kernel/sched.c`, `kernel/syscalls.c`, `tests/test_futex.c`

## headers/httpd.h
- Doc: Docstring: httpd.h -- Minimal static HTTP/1.0 server contract.
- Layer: presentation
- Language: h
- Symbols:
  - `httpd_ctype` (function, line 28) `static inline const char *httpd_ctype(const char *path)`
  - `httpd_header` (function, line 121) `static inline int httpd_header(int code, const char *reason,
        const char *ctype, unsigned ...`
  - `HTTPD_H` (macro, line 15) `#define HTTPD_H`
  - `HTTPD_MAX_PATH` (macro, line 17) `#define HTTPD_MAX_PATH`
  - `HTTPD_MAX_REQ` (macro, line 18) `#define HTTPD_MAX_REQ`
  - `HTTPD_HEAD_MAX` (macro, line 19) `#define HTTPD_HEAD_MAX`
  - `HTTPD_ERR_BOUND` (macro, line 21) `#define HTTPD_ERR_BOUND`
  - `HTTPD_ERR_METHOD` (macro, line 22) `#define HTTPD_ERR_METHOD`
  - `HTTPD_ERR_PATH` (macro, line 23) `#define HTTPD_ERR_PATH`
  - `HTTPD_ERR_VERSION` (macro, line 24) `#define HTTPD_ERR_VERSION`
- Imported by: `kernel/shell.c`, `tests/test_httpd.c`

## headers/ide.h
- Doc: IDE/ATA PIO driver for MiniOS.
- Layer: utility
- Language: h
- Symbols:
  - `ide_init` (function, line 49) `void ide_init(void);`
  - `ide_read_sectors` (function, line 53) `int ide_read_sectors(unsigned int lba, unsigned int count, void *buf);`
  - `ide_write_sectors` (function, line 54) `int ide_write_sectors(unsigned int lba, unsigned int count, const void *buf);`
  - `ide_read_sector` (function, line 57) `int ide_read_sector(unsigned int lba, void *buf);`
  - `ide_write_sector` (function, line 58) `int ide_write_sector(unsigned int lba, const void *buf);`
  - `ide_total_sectors` (function, line 61) `unsigned int ide_total_sectors(void);`
  - `ide_present` (function, line 64) `int ide_present(void);`
  - `ide_register_device` (function, line 68) `void ide_register_device(void);`
  - `IDE_H` (macro, line 2) `#define IDE_H`
  - `IDE_PRIMARY_BASE` (macro, line 9) `#define IDE_PRIMARY_BASE`
  - `IDE_PRIMARY_CTRL` (macro, line 10) `#define IDE_PRIMARY_CTRL`
  - `IDE_REG_DATA` (macro, line 13) `#define IDE_REG_DATA`
  - `IDE_REG_ERROR` (macro, line 14) `#define IDE_REG_ERROR`
  - `IDE_REG_SECCOUNT` (macro, line 15) `#define IDE_REG_SECCOUNT`
  - `IDE_REG_LBA_LO` (macro, line 16) `#define IDE_REG_LBA_LO`
  - `IDE_REG_LBA_MID` (macro, line 17) `#define IDE_REG_LBA_MID`
  - `IDE_REG_LBA_HI` (macro, line 18) `#define IDE_REG_LBA_HI`
  - `IDE_REG_DRIVE` (macro, line 19) `#define IDE_REG_DRIVE`
  - `IDE_REG_STATUS` (macro, line 20) `#define IDE_REG_STATUS`
  - `IDE_REG_ALTSTATUS` (macro, line 21) `#define IDE_REG_ALTSTATUS`
  - `IDE_STATUS_ERR` (macro, line 24) `#define IDE_STATUS_ERR`
  - `IDE_STATUS_DRQ` (macro, line 25) `#define IDE_STATUS_DRQ`
  - `IDE_STATUS_SRV` (macro, line 26) `#define IDE_STATUS_SRV`
  - `IDE_STATUS_DF` (macro, line 27) `#define IDE_STATUS_DF`
  - `IDE_STATUS_RDY` (macro, line 28) `#define IDE_STATUS_RDY`
  - `IDE_STATUS_BSY` (macro, line 29) `#define IDE_STATUS_BSY`
  - `IDE_CMD_READ` (macro, line 32) `#define IDE_CMD_READ`
  - `IDE_CMD_WRITE` (macro, line 33) `#define IDE_CMD_WRITE`
  - `IDE_CMD_IDENTIFY` (macro, line 34) `#define IDE_CMD_IDENTIFY`
  - `IDE_CMD_FLUSH` (macro, line 35) `#define IDE_CMD_FLUSH`
  - `IDE_DRIVE_LBA` (macro, line 38) `#define IDE_DRIVE_LBA`
  - `IDE_DRIVE_MASTER` (macro, line 39) `#define IDE_DRIVE_MASTER`
  - `IDE_DRIVE_SLAVE` (macro, line 40) `#define IDE_DRIVE_SLAVE`
  - `IDE_TIMEOUT` (macro, line 43) `#define IDE_TIMEOUT`
  - `IDE_SECTOR_SIZE` (macro, line 46) `#define IDE_SECTOR_SIZE`
- Imported by: `drivers/block.c`, `drivers/ide.c`, `fs/minifs.c`, `kernel.c`, `kernel/mm/swap.c`, `kernel/syscalls.c`


Next: [KB_headers_p2.md](KB_headers_p2.md)
