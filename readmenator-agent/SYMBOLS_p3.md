# Symbols (page 3 of 26)
Previous: [SYMBOLS_p2.md](SYMBOLS_p2.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `RD_DATA_MIN` | macro | `fs/ramdisk.c:18` | `#define RD_DATA_MIN` |
| `RD_DATA_SPARE` | macro | `fs/ramdisk.c:19` | `#define RD_DATA_SPARE` |
| `RD_ENTRY_FLG_OFF` | macro | `fs/ramdisk.c:23` | `#define RD_ENTRY_FLG_OFF` |
| `RD_ENTRY_OFF_OFF` | macro | `fs/ramdisk.c:22` | `#define RD_ENTRY_OFF_OFF` |
| `RD_ENTRY_RAW_OFF` | macro | `fs/ramdisk.c:20` | `#define RD_ENTRY_RAW_OFF` |
| `RD_ENTRY_SIZE` | macro | `fs/ramdisk.c:17` | `#define RD_ENTRY_SIZE` |
| `RD_ENTRY_STO_OFF` | macro | `fs/ramdisk.c:21` | `#define RD_ENTRY_STO_OFF` |
| `RD_FLAG_DEFLATE` | macro | `fs/ramdisk.c:24` | `#define RD_FLAG_DEFLATE` |
| `RD_HEADER_SIZE` | macro | `fs/ramdisk.c:16` | `#define RD_HEADER_SIZE` |
| `RD_MAGIC` | macro | `fs/ramdisk.c:15` | `#define RD_MAGIC` |
| `ramdisk_count` | function | `fs/ramdisk.c:230` | `int ramdisk_count(void)` |
| `ramdisk_create` | function | `fs/ramdisk.c:171` | `RDFile *ramdisk_create(const char *name, unsigned size)` |
| `ramdisk_delete` | function | `fs/ramdisk.c:247` | `int ramdisk_delete(RDFile *f)` |
| `ramdisk_file_name` | function | `fs/ramdisk.c:242` | `const char *ramdisk_file_name(int idx)` |
| `ramdisk_init` | function | `fs/ramdisk.c:128` | `void ramdisk_init(void)` |
| `ramdisk_list` | function | `fs/ramdisk.c:222` | `int ramdisk_list(RDFile **out, int max)` |
| `ramdisk_open` | function | `fs/ramdisk.c:145` | `RDFile *ramdisk_open(const char *name)` |
| `ramdisk_read` | function | `fs/ramdisk.c:155` | `int ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len)` |
| `ramdisk_rename` | function | `fs/ramdisk.c:269` | `int ramdisk_rename(const char *oldname, const char *newname)` |
| `ramdisk_reserve` | function | `fs/ramdisk.c:37` | `static int ramdisk_reserve(unsigned long want)` |
| `ramdisk_resize` | function | `fs/ramdisk.c:185` | `int ramdisk_resize(RDFile *f, unsigned newsize)` |
| `ramdisk_setup_from` | function | `fs/ramdisk.c:55` | `void ramdisk_setup_from(void *data, unsigned size)` |
| `ramdisk_usage` | function | `fs/ramdisk.c:236` | `void ramdisk_usage(unsigned *used, unsigned *cap, unsigned *max)` |
| `ramdisk_write` | function | `fs/ramdisk.c:163` | `int ramdisk_write(RDFile *f, const void *buf, unsigned offset, unsigned len)` |
| `MEM_FILES` | macro | `fs/vfs.c:457` | `#define MEM_FILES` |
| `MEM_FNAME` | macro | `fs/vfs.c:458` | `#define MEM_FNAME` |
| `MEM_FSIZE` | macro | `fs/vfs.c:459` | `#define MEM_FSIZE` |
| `fs_dir_exists` | function | `fs/vfs.c:613` | `int fs_dir_exists(const char *dir)` |
| `fs_is_dir` | function | `fs/vfs.c:638` | `int fs_is_dir(const char *resolved)` |
| `fs_resolve` | function | `fs/vfs.c:580` | `int fs_resolve(const char *path, char *out, unsigned cap)` |
| `mem_close` | function | `fs/vfs.c:526` | `static int mem_close(void *handle)` |
| `mem_file_t` | struct | `fs/vfs.c:461` | `` |
| `mem_fstat` | function | `fs/vfs.c:530` | `static int mem_fstat(void *handle, unsigned long *size_out)` |
| `mem_lookup` | function | `fs/vfs.c:470` | `static int mem_lookup(const char *path)` |
| `mem_open` | function | `fs/vfs.c:478` | `static int mem_open(const char *path, int mode, void **handle)` |
| `mem_read` | function | `fs/vfs.c:505` | `static int mem_read(void *handle, void *buf, unsigned long pos, unsigned long len)` |
| `mem_readdir` | function | `fs/vfs.c:548` | `static int mem_readdir(const char *path, vfs_dirent_t *ents, int cap)` |
| `mem_slot` | function | `fs/vfs.c:498` | `static int mem_slot(void *handle)` |
| `mem_truncate` | function | `fs/vfs.c:537` | `static int mem_truncate(void *handle, unsigned long size)` |
| `mem_write` | function | `fs/vfs.c:515` | `static int mem_write(void *handle, const void *buf, unsigned long pos, unsigned long len)` |
| `minifs_handle_t` | struct | `fs/vfs.c:346` | `` |
| `minifs_mkdir_p` | function | `fs/vfs.c:651` | `int minifs_mkdir_p(const char *resolved)` |
| `minifs_vfs_close` | function | `fs/vfs.c:396` | `static int minifs_vfs_close(void *handle)` |
| `minifs_vfs_fstat` | function | `fs/vfs.c:402` | `static int minifs_vfs_fstat(void *handle, unsigned long *size_out)` |
| `minifs_vfs_open` | function | `fs/vfs.c:351` | `static int minifs_vfs_open(const char *path, int mode, void **handle)` |
| `minifs_vfs_read` | function | `fs/vfs.c:379` | `static int minifs_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len)` |
| `minifs_vfs_truncate` | function | `fs/vfs.c:409` | `static int minifs_vfs_truncate(void *handle, unsigned long size)` |
| `minifs_vfs_write` | function | `fs/vfs.c:388` | `static int minifs_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len)` |
| `open` | function | `fs/vfs.c:688` | `* open (loopback image file plus in-image path), so one registration  * serves every image. */ in...` |
| `ramdisk_handle_t` | struct | `fs/vfs.c:196` | `` |
| `ramdisk_vfs_close` | function | `fs/vfs.c:255` | `static int ramdisk_vfs_close(void *handle)` |
| `ramdisk_vfs_fstat` | function | `fs/vfs.c:261` | `static int ramdisk_vfs_fstat(void *handle, unsigned long *size_out)` |
| `ramdisk_vfs_open` | function | `fs/vfs.c:212` | `static int ramdisk_vfs_open(const char *path, int mode, void **handle)` |
| `ramdisk_vfs_read` | function | `fs/vfs.c:238` | `static int ramdisk_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len)` |
| `ramdisk_vfs_readdir` | function | `fs/vfs.c:278` | `static int ramdisk_vfs_readdir(const char *path, vfs_dirent_t *ents,         int cap)` |
| `ramdisk_vfs_truncate` | function | `fs/vfs.c:268` | `static int ramdisk_vfs_truncate(void *handle, unsigned long size)` |
| `ramdisk_vfs_write` | function | `fs/vfs.c:247` | `static int ramdisk_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len)` |
| `taken` | function | `fs/vfs.c:160` | `* refcount is taken (ops tables are static, never freed), so a  * listing can never pin an unmoun...` |
| `vfs_close` | function | `fs/vfs.c:734` | `int vfs_close(vfs_file_t *f)` |
| `vfs_fstat` | function | `fs/vfs.c:752` | `int vfs_fstat(vfs_file_t *f, unsigned long *size_out)` |
| `vfs_init` | function | `fs/vfs.c:22` | `void vfs_init(void)` |
| `vfs_mount_t` | struct | `fs/vfs.c:10` | `` |
| `vfs_open` | function | `fs/vfs.c:106` | `int vfs_open(const char *path, int mode, vfs_file_t *f)` |
| `vfs_read` | function | `fs/vfs.c:709` | `int vfs_read(vfs_file_t *f, void *buf, unsigned long len)` |
| `vfs_register` | function | `fs/vfs.c:27` | `int vfs_register(const char *prefix, const vfs_ops_t *ops, const char *driver)` |
| `vfs_register_builtins` | function | `fs/vfs.c:674` | `void vfs_register_builtins(void)` |
| `vfs_unregister` | function | `fs/vfs.c:62` | `int vfs_unregister(const char *prefix)` |
| `vfs_write` | function | `fs/vfs.c:718` | `int vfs_write(vfs_file_t *f, const void *buf, unsigned long len)` |
| `marker` | function | `fs/zip.c:50` | `* marker (trailing '/') is preserved by the caller, not here. */ static int zip_sanitize_name(con...` |
| `mz_zip_writer_mem_ptr` | function | `fs/zip.c:18` | `void *mz_zip_writer_mem_ptr(mz_zip_archive *pZip);` |
| `mz_zip_writer_mem_size` | function | `fs/zip.c:19` | `size_t mz_zip_writer_mem_size(mz_zip_archive *pZip);` |
| `root` | function | `fs/zip.c:8` | `* names are hostile data: each is normalized to forward slashes and rejected * when it escapes the extraction root...` |
| `shell_cmd_unzip` | function | `fs/zip.c:176` | `void shell_cmd_unzip(int argc, char **argv)` |
| `shell_cmd_zip` | function | `fs/zip.c:254` | `void shell_cmd_zip(int argc, char **argv)` |
| `zip_build_path` | function | `fs/zip.c:79` | `static int zip_build_path(const char *destdir, const char *name, char *out)` |
| `zip_do_entry` | function | `fs/zip.c:117` | `static int zip_do_entry(mz_zip_archive *zip, mz_uint idx, const char *destdir)` |
| `zip_ensure_dir_tree` | function | `fs/zip.c:95` | `static int zip_ensure_dir_tree(const char *dir)` |
| `zip_read_whole` | function | `fs/zip.c:25` | `static unsigned char *zip_read_whole(const char *path, unsigned long *size)` |
| `ABI_BAD_FORMAT` | macro | `headers/abi.h:18` | `#define ABI_BAD_FORMAT` |
| `ABI_CHECKSUM_MISMATCH` | macro | `headers/abi.h:20` | `#define ABI_CHECKSUM_MISMATCH` |
| `ABI_H` | macro | `headers/abi.h:14` | `#define ABI_H` |
| `ABI_MANIFEST_MAX` | macro | `headers/abi.h:23` | `#define ABI_MANIFEST_MAX` |
| `ABI_MANIFEST_NAME` | macro | `headers/abi.h:22` | `#define ABI_MANIFEST_NAME` |
| `ABI_NO_MANIFEST` | macro | `headers/abi.h:17` | `#define ABI_NO_MANIFEST` |
| `ABI_OK` | macro | `headers/abi.h:16` | `#define ABI_OK` |
| `ABI_VERSION_MISMATCH` | macro | `headers/abi.h:19` | `#define ABI_VERSION_MISMATCH` |
| `abi_check_manifest` | function | `headers/abi.h:28` | `int abi_check_manifest(void);` |
| `abi_verify` | function | `headers/abi.h:25` | `int abi_verify(const char *text, long version, unsigned long checksum);` |
| `A20_CONTROL_PORT` | macro | `headers/arch/x86/boot/bootdefs.h:157` | `#define A20_CONTROL_PORT` |
| `A20_ENABLE_BIT` | macro | `headers/arch/x86/boot/bootdefs.h:158` | `#define A20_ENABLE_BIT` |
| `A20_RESET_CLEAR_MASK` | macro | `headers/arch/x86/boot/bootdefs.h:159` | `#define A20_RESET_CLEAR_MASK` |
| `AP_STUB_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:193` | `#define AP_STUB_ADDR` |
| `BIOS_DISK_EXT_ACK_MAGIC` | macro | `headers/arch/x86/boot/bootdefs.h:97` | `#define BIOS_DISK_EXT_ACK_MAGIC` |
| `BIOS_DISK_EXT_CHECK` | macro | `headers/arch/x86/boot/bootdefs.h:95` | `#define BIOS_DISK_EXT_CHECK` |
| `BIOS_DISK_EXT_PACKET_BIT` | macro | `headers/arch/x86/boot/bootdefs.h:98` | `#define BIOS_DISK_EXT_PACKET_BIT` |
| `BIOS_DISK_EXT_REQ_MAGIC` | macro | `headers/arch/x86/boot/bootdefs.h:96` | `#define BIOS_DISK_EXT_REQ_MAGIC` |
| `BIOS_DISK_INT` | macro | `headers/arch/x86/boot/bootdefs.h:94` | `#define BIOS_DISK_INT` |
| `BIOS_DISK_READ_EXT` | macro | `headers/arch/x86/boot/bootdefs.h:99` | `#define BIOS_DISK_READ_EXT` |
| `BIOS_VBE_GET_MODE_INFO` | macro | `headers/arch/x86/boot/bootdefs.h:117` | `#define BIOS_VBE_GET_MODE_INFO` |
| `BIOS_VBE_SET_MODE` | macro | `headers/arch/x86/boot/bootdefs.h:118` | `#define BIOS_VBE_SET_MODE` |
| `BIOS_VIDEO_INT` | macro | `headers/arch/x86/boot/bootdefs.h:101` | `#define BIOS_VIDEO_INT` |
| `BIOS_VIDEO_SET_MODE` | macro | `headers/arch/x86/boot/bootdefs.h:104` | `#define BIOS_VIDEO_SET_MODE` |
| `BIOS_VIDEO_TTY_ATTR` | macro | `headers/arch/x86/boot/bootdefs.h:103` | `#define BIOS_VIDEO_TTY_ATTR` |
| `BIOS_VIDEO_TTY_WRITE` | macro | `headers/arch/x86/boot/bootdefs.h:102` | `#define BIOS_VIDEO_TTY_WRITE` |
| `BOOTDEFS_H` | macro | `headers/arch/x86/boot/bootdefs.h:52` | `#define BOOTDEFS_H` |
| `BOOT_BIOS_MAX_SECTORS` | macro | `headers/arch/x86/boot/bootdefs.h:85` | `#define BOOT_BIOS_MAX_SECTORS` |
| `BOOT_CHUNK_SECTORS` | macro | `headers/arch/x86/boot/bootdefs.h:84` | `#define BOOT_CHUNK_SECTORS` |
| `BOOT_DAP_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:64` | `#define BOOT_DAP_ADDR` |
| `BOOT_DAP_OFF_COUNT` | macro | `headers/arch/x86/boot/bootdefs.h:66` | `#define BOOT_DAP_OFF_COUNT` |
| `BOOT_DAP_OFF_LBA_HI` | macro | `headers/arch/x86/boot/bootdefs.h:70` | `#define BOOT_DAP_OFF_LBA_HI` |
| `BOOT_DAP_OFF_LBA_LO` | macro | `headers/arch/x86/boot/bootdefs.h:69` | `#define BOOT_DAP_OFF_LBA_LO` |
| `BOOT_DAP_OFF_OFFSET` | macro | `headers/arch/x86/boot/bootdefs.h:67` | `#define BOOT_DAP_OFF_OFFSET` |
| `BOOT_DAP_OFF_SEGMENT` | macro | `headers/arch/x86/boot/bootdefs.h:68` | `#define BOOT_DAP_OFF_SEGMENT` |
| `BOOT_DAP_SIZE` | macro | `headers/arch/x86/boot/bootdefs.h:65` | `#define BOOT_DAP_SIZE` |
| `BOOT_DRIVE_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:71` | `#define BOOT_DRIVE_ADDR` |
| `BOOT_KASLR_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:72` | `#define BOOT_KASLR_ADDR` |
| `BOOT_KERNEL_BUF_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:80` | `#define BOOT_KERNEL_BUF_ADDR` |
| `BOOT_KERNEL_BUF_SEG` | macro | `headers/arch/x86/boot/bootdefs.h:81` | `#define BOOT_KERNEL_BUF_SEG` |
| `BOOT_KERNEL_LBA` | macro | `headers/arch/x86/boot/bootdefs.h:79` | `#define BOOT_KERNEL_LBA` |
| `BOOT_KERNEL_PHYS_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:82` | `#define BOOT_KERNEL_PHYS_ADDR` |
| `BOOT_PCM2_DMA_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:91` | `#define BOOT_PCM2_DMA_ADDR` |
| `BOOT_PCM2_DMA_BYTES` | macro | `headers/arch/x86/boot/bootdefs.h:92` | `#define BOOT_PCM2_DMA_BYTES` |
| `BOOT_PM_STACK_TOP` | macro | `headers/arch/x86/boot/bootdefs.h:87` | `#define BOOT_PM_STACK_TOP` |
| `BOOT_SB16_DMA_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:89` | `#define BOOT_SB16_DMA_ADDR` |
| `BOOT_SB16_DMA_BYTES` | macro | `headers/arch/x86/boot/bootdefs.h:90` | `#define BOOT_SB16_DMA_BYTES` |
| `BOOT_SEG_NULL` | macro | `headers/arch/x86/boot/bootdefs.h:61` | `#define BOOT_SEG_NULL` |
| `BOOT_SIGNATURE` | macro | `headers/arch/x86/boot/bootdefs.h:58` | `#define BOOT_SIGNATURE` |
| `BOOT_SIGNATURE_BYTES` | macro | `headers/arch/x86/boot/bootdefs.h:59` | `#define BOOT_SIGNATURE_BYTES` |
| `BOOT_STACK_TOP` | macro | `headers/arch/x86/boot/bootdefs.h:62` | `#define BOOT_STACK_TOP` |
| `BOOT_STAGE2_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:76` | `#define BOOT_STAGE2_ADDR` |
| `BOOT_STAGE2_LBA` | macro | `headers/arch/x86/boot/bootdefs.h:74` | `#define BOOT_STAGE2_LBA` |
| `BOOT_STAGE2_SECTORS` | macro | `headers/arch/x86/boot/bootdefs.h:75` | `#define BOOT_STAGE2_SECTORS` |
| `BOOT_STAGE2_SEG` | macro | `headers/arch/x86/boot/bootdefs.h:77` | `#define BOOT_STAGE2_SEG` |
| `CMOS_DATA_PORT` | macro | `headers/arch/x86/boot/bootdefs.h:287` | `#define CMOS_DATA_PORT` |
| `CMOS_EXTMEM_BASE` | macro | `headers/arch/x86/boot/bootdefs.h:292` | `#define CMOS_EXTMEM_BASE` |
| `CMOS_EXTMEM_UNIT` | macro | `headers/arch/x86/boot/bootdefs.h:293` | `#define CMOS_EXTMEM_UNIT` |
| `CMOS_INDEX_PORT` | macro | `headers/arch/x86/boot/bootdefs.h:286` | `#define CMOS_INDEX_PORT` |
| `CMOS_NMI_DISABLE` | macro | `headers/arch/x86/boot/bootdefs.h:288` | `#define CMOS_NMI_DISABLE` |
| `CMOS_REG_EXTMEM_HI` | macro | `headers/arch/x86/boot/bootdefs.h:291` | `#define CMOS_REG_EXTMEM_HI` |
| `CMOS_REG_EXTMEM_LO` | macro | `headers/arch/x86/boot/bootdefs.h:290` | `#define CMOS_REG_EXTMEM_LO` |
| `CMOS_REG_HOURS` | macro | `headers/arch/x86/boot/bootdefs.h:296` | `#define CMOS_REG_HOURS` |
| `CMOS_REG_MINUTES` | macro | `headers/arch/x86/boot/bootdefs.h:295` | `#define CMOS_REG_MINUTES` |
| `CMOS_REG_SECONDS` | macro | `headers/arch/x86/boot/bootdefs.h:294` | `#define CMOS_REG_SECONDS` |
| `CR0_PE` | macro | `headers/arch/x86/boot/bootdefs.h:161` | `#define CR0_PE` |
| `CR0_PE_CLEAR_MASK` | macro | `headers/arch/x86/boot/bootdefs.h:162` | `#define CR0_PE_CLEAR_MASK` |
| `CR0_PG` | macro | `headers/arch/x86/boot/bootdefs.h:163` | `#define CR0_PG` |
| `CR0_WP` | macro | `headers/arch/x86/boot/bootdefs.h:164` | `#define CR0_WP` |
| `CR4_PAE` | macro | `headers/arch/x86/boot/bootdefs.h:165` | `#define CR4_PAE` |
| `EFER_LME` | macro | `headers/arch/x86/boot/bootdefs.h:168` | `#define EFER_LME` |
| `EFER_NXE` | macro | `headers/arch/x86/boot/bootdefs.h:169` | `#define EFER_NXE` |
| `GDT32_CODE16_SEL` | macro | `headers/arch/x86/boot/bootdefs.h:173` | `#define GDT32_CODE16_SEL` |
| `GDT32_CODE32_SEL` | macro | `headers/arch/x86/boot/bootdefs.h:171` | `#define GDT32_CODE32_SEL` |
| `GDT32_DATA16_SEL` | macro | `headers/arch/x86/boot/bootdefs.h:174` | `#define GDT32_DATA16_SEL` |
| `GDT32_DATA32_SEL` | macro | `headers/arch/x86/boot/bootdefs.h:172` | `#define GDT32_DATA32_SEL` |
| `GDT32_DESC_CODE16` | macro | `headers/arch/x86/boot/bootdefs.h:179` | `#define GDT32_DESC_CODE16` |
| `GDT32_DESC_CODE32` | macro | `headers/arch/x86/boot/bootdefs.h:177` | `#define GDT32_DESC_CODE32` |
| `GDT32_DESC_DATA16` | macro | `headers/arch/x86/boot/bootdefs.h:180` | `#define GDT32_DESC_DATA16` |
| `GDT32_DESC_DATA32` | macro | `headers/arch/x86/boot/bootdefs.h:178` | `#define GDT32_DESC_DATA32` |
| `GDT32_DESC_NULL` | macro | `headers/arch/x86/boot/bootdefs.h:176` | `#define GDT32_DESC_NULL` |
| `GDT64_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:182` | `#define GDT64_ADDR` |
| `GDT64_BYTES` | macro | `headers/arch/x86/boot/bootdefs.h:183` | `#define GDT64_BYTES` |
| `GDT64_CODE_SEL` | macro | `headers/arch/x86/boot/bootdefs.h:194` | `#define GDT64_CODE_SEL` |
| `GDT64_DATA_SEL` | macro | `headers/arch/x86/boot/bootdefs.h:195` | `#define GDT64_DATA_SEL` |
| `GDT64_DESC_CODE` | macro | `headers/arch/x86/boot/bootdefs.h:199` | `#define GDT64_DESC_CODE` |
| `GDT64_DESC_DATA` | macro | `headers/arch/x86/boot/bootdefs.h:200` | `#define GDT64_DESC_DATA` |
| `GDT64_DESC_NULL` | macro | `headers/arch/x86/boot/bootdefs.h:198` | `#define GDT64_DESC_NULL` |
| `GDT64_DESC_UCODE` | macro | `headers/arch/x86/boot/bootdefs.h:202` | `#define GDT64_DESC_UCODE` |
| `GDT64_DESC_UDATA` | macro | `headers/arch/x86/boot/bootdefs.h:201` | `#define GDT64_DESC_UDATA` |
| `GDT64_SMP_BYTES` | macro | `headers/arch/x86/boot/bootdefs.h:188` | `#define GDT64_SMP_BYTES` |
| `GDT64_USER_CODE_SEL` | macro | `headers/arch/x86/boot/bootdefs.h:197` | `#define GDT64_USER_CODE_SEL` |
| `GDT64_USER_DATA_SEL` | macro | `headers/arch/x86/boot/bootdefs.h:196` | `#define GDT64_USER_DATA_SEL` |
| `KASLR_ALIGN_SHIFT` | macro | `headers/arch/x86/boot/bootdefs.h:280` | `#define KASLR_ALIGN_SHIFT` |
| `KASLR_IMAGE_SPAN` | macro | `headers/arch/x86/boot/bootdefs.h:284` | `#define KASLR_IMAGE_SPAN` |
| `KASLR_IMG_OFF_1MB` | macro | `headers/arch/x86/boot/bootdefs.h:282` | `#define KASLR_IMG_OFF_1MB` |
| `KASLR_IMG_OFF_2MB` | macro | `headers/arch/x86/boot/bootdefs.h:283` | `#define KASLR_IMG_OFF_2MB` |
| `KASLR_MAX_UNITS` | macro | `headers/arch/x86/boot/bootdefs.h:281` | `#define KASLR_MAX_UNITS` |
| `KASLR_MIN_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:279` | `#define KASLR_MIN_ADDR` |
| `KMM_DEVICE_PDPT_SLOT` | macro | `headers/arch/x86/boot/bootdefs.h:239` | `#define KMM_DEVICE_PDPT_SLOT` |
| `MSR_EFER` | macro | `headers/arch/x86/boot/bootdefs.h:167` | `#define MSR_EFER` |
| `PT_ADDR_MASK` | macro | `headers/arch/x86/boot/bootdefs.h:217` | `#define PT_ADDR_MASK` |
| `PT_ENTRY_PRESENT` | macro | `headers/arch/x86/boot/bootdefs.h:220` | `#define PT_ENTRY_PRESENT` |
| `PT_ENTRY_USER` | macro | `headers/arch/x86/boot/bootdefs.h:221` | `#define PT_ENTRY_USER` |
| `PT_FILL_ENTRIES` | macro | `headers/arch/x86/boot/bootdefs.h:246` | `#define PT_FILL_ENTRIES` |
| `PT_FILL_START_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:245` | `#define PT_FILL_START_ADDR` |
| `PT_FILL_START_INDEX` | macro | `headers/arch/x86/boot/bootdefs.h:244` | `#define PT_FILL_START_INDEX` |
| `PT_FLAGS_NX` | macro | `headers/arch/x86/boot/bootdefs.h:216` | `#define PT_FLAGS_NX` |
| `PT_FLAGS_PCD` | macro | `headers/arch/x86/boot/bootdefs.h:214` | `#define PT_FLAGS_PCD` |
| `PT_FLAGS_PRESENT_RW` | macro | `headers/arch/x86/boot/bootdefs.h:210` | `#define PT_FLAGS_PRESENT_RW` |
| `PT_FLAGS_PRESENT_RW_PS` | macro | `headers/arch/x86/boot/bootdefs.h:211` | `#define PT_FLAGS_PRESENT_RW_PS` |
| `PT_FLAGS_PS` | macro | `headers/arch/x86/boot/bootdefs.h:212` | `#define PT_FLAGS_PS` |
| `PT_FLAGS_PWT` | macro | `headers/arch/x86/boot/bootdefs.h:215` | `#define PT_FLAGS_PWT` |
| `PT_FLAGS_UNCACHED` | macro | `headers/arch/x86/boot/bootdefs.h:233` | `#define PT_FLAGS_UNCACHED` |
| `PT_FLAGS_USER` | macro | `headers/arch/x86/boot/bootdefs.h:213` | `#define PT_FLAGS_USER` |
| `PT_PDPT_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:205` | `#define PT_PDPT_ADDR` |
| `PT_PD_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:206` | `#define PT_PD_ADDR` |
| `PT_PD_ENTRIES` | macro | `headers/arch/x86/boot/bootdefs.h:240` | `#define PT_PD_ENTRIES` |
| `PT_PD_ENTRY_BYTES` | macro | `headers/arch/x86/boot/bootdefs.h:241` | `#define PT_PD_ENTRY_BYTES` |
| `PT_PD_INDEX_SHIFT` | macro | `headers/arch/x86/boot/bootdefs.h:243` | `#define PT_PD_INDEX_SHIFT` |
| `PT_PD_PAGE_BYTES` | macro | `headers/arch/x86/boot/bootdefs.h:242` | `#define PT_PD_PAGE_BYTES` |
| `PT_PML4_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:204` | `#define PT_PML4_ADDR` |
| `PT_USER0_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:207` | `#define PT_USER0_ADDR` |
| `PT_USER1_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:208` | `#define PT_USER1_ADDR` |
| `PT_USER_ENTRY` | macro | `headers/arch/x86/boot/bootdefs.h:218` | `#define PT_USER_ENTRY` |
| `PT_USER_NX_ENTRY` | macro | `headers/arch/x86/boot/bootdefs.h:219` | `#define PT_USER_NX_ENTRY` |
| `PT_USER_TABLES_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:266` | `#define PT_USER_TABLES_ADDR` |
| `PT_USER_TABLES_BYTES` | macro | `headers/arch/x86/boot/bootdefs.h:267` | `#define PT_USER_TABLES_BYTES` |
| `PT_ZERO_DWORDS` | macro | `headers/arch/x86/boot/bootdefs.h:209` | `#define PT_ZERO_DWORDS` |
| `SB16_DMA_PT_ENTRY` | macro | `headers/arch/x86/boot/bootdefs.h:227` | `#define SB16_DMA_PT_ENTRY` |
| `SB16_DMA_PT_PAGES` | macro | `headers/arch/x86/boot/bootdefs.h:228` | `#define SB16_DMA_PT_PAGES` |
| `SECTOR_BYTES` | macro | `headers/arch/x86/boot/bootdefs.h:54` | `#define SECTOR_BYTES` |
| `SECTOR_DWORD_SHIFT` | macro | `headers/arch/x86/boot/bootdefs.h:56` | `#define SECTOR_DWORD_SHIFT` |
| `SECTOR_PARAGRAPH_SHIFT` | macro | `headers/arch/x86/boot/bootdefs.h:55` | `#define SECTOR_PARAGRAPH_SHIFT` |
| `VBE_ATTR_LFB` | macro | `headers/arch/x86/boot/bootdefs.h:129` | `#define VBE_ATTR_LFB` |
| `VBE_ATTR_SUPPORTED` | macro | `headers/arch/x86/boot/bootdefs.h:128` | `#define VBE_ATTR_SUPPORTED` |
| `VBE_BPP_24` | macro | `headers/arch/x86/boot/bootdefs.h:136` | `#define VBE_BPP_24` |
| `VBE_BPP_32` | macro | `headers/arch/x86/boot/bootdefs.h:137` | `#define VBE_BPP_32` |
| `VBE_BPP_8` | macro | `headers/arch/x86/boot/bootdefs.h:135` | `#define VBE_BPP_8` |
| `VBE_INFO_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:149` | `#define VBE_INFO_ADDR` |
| `VBE_INFO_BPP_OFF` | macro | `headers/arch/x86/boot/bootdefs.h:155` | `#define VBE_INFO_BPP_OFF` |
| `VBE_INFO_BPP_SRC_OFF` | macro | `headers/arch/x86/boot/bootdefs.h:134` | `#define VBE_INFO_BPP_SRC_OFF` |
| `VBE_INFO_BYTES_SCAN_OFF` | macro | `headers/arch/x86/boot/bootdefs.h:132` | `#define VBE_INFO_BYTES_SCAN_OFF` |
| `VBE_INFO_FBBASE_OFF` | macro | `headers/arch/x86/boot/bootdefs.h:150` | `#define VBE_INFO_FBBASE_OFF` |
| `VBE_INFO_HEIGHT_OFF` | macro | `headers/arch/x86/boot/bootdefs.h:153` | `#define VBE_INFO_HEIGHT_OFF` |
| `VBE_INFO_PHYSBASE_OFF` | macro | `headers/arch/x86/boot/bootdefs.h:133` | `#define VBE_INFO_PHYSBASE_OFF` |
| `VBE_INFO_PITCH_OFF` | macro | `headers/arch/x86/boot/bootdefs.h:151` | `#define VBE_INFO_PITCH_OFF` |
| `VBE_INFO_VALID_OFF` | macro | `headers/arch/x86/boot/bootdefs.h:154` | `#define VBE_INFO_VALID_OFF` |
| `VBE_INFO_WIDTH_OFF` | macro | `headers/arch/x86/boot/bootdefs.h:152` | `#define VBE_INFO_WIDTH_OFF` |
| `VBE_INFO_XRES_OFF` | macro | `headers/arch/x86/boot/bootdefs.h:130` | `#define VBE_INFO_XRES_OFF` |
| `VBE_INFO_YRES_OFF` | macro | `headers/arch/x86/boot/bootdefs.h:131` | `#define VBE_INFO_YRES_OFF` |
| `VBE_MODE_1024x768x32` | macro | `headers/arch/x86/boot/bootdefs.h:119` | `#define VBE_MODE_1024x768x32` |
| `VBE_MODE_1024x768x8` | macro | `headers/arch/x86/boot/bootdefs.h:122` | `#define VBE_MODE_1024x768x8` |
| `VBE_MODE_640x480x32` | macro | `headers/arch/x86/boot/bootdefs.h:121` | `#define VBE_MODE_640x480x32` |
| `VBE_MODE_640x480x8` | macro | `headers/arch/x86/boot/bootdefs.h:124` | `#define VBE_MODE_640x480x8` |
| `VBE_MODE_800x600x32` | macro | `headers/arch/x86/boot/bootdefs.h:120` | `#define VBE_MODE_800x600x32` |
| `VBE_MODE_800x600x8` | macro | `headers/arch/x86/boot/bootdefs.h:123` | `#define VBE_MODE_800x600x8` |
| `VBE_MODE_ATTR_OFF` | macro | `headers/arch/x86/boot/bootdefs.h:127` | `#define VBE_MODE_ATTR_OFF` |
| `VBE_MODE_INFO_ADDR` | macro | `headers/arch/x86/boot/bootdefs.h:126` | `#define VBE_MODE_INFO_ADDR` |
| `VBE_MODE_LFB` | macro | `headers/arch/x86/boot/bootdefs.h:125` | `#define VBE_MODE_LFB` |
| `address` | function | `headers/arch/x86/boot/bootdefs.h:191` | `* address (below 1 MB so a real-mode SIPI can reach it) and executed by every * AP. It reuses the page tables and...` |
| `HAL_IO_H` | macro | `headers/arch/x86/hal_io.h:13` | `#define HAL_IO_H` |
| `HAL_LAPIC_EOI_ADDR` | macro | `headers/arch/x86/hal_io.h:100` | `#define HAL_LAPIC_EOI_ADDR` |
| `HAL_MOUSE_BUTTON_MASK` | macro | `headers/arch/x86/hal_io.h:93` | `#define HAL_MOUSE_BUTTON_MASK` |
| `HAL_MOUSE_CMD_DEFAULTS` | macro | `headers/arch/x86/hal_io.h:72` | `#define HAL_MOUSE_CMD_DEFAULTS` |
| `HAL_MOUSE_CMD_DISABLE` | macro | `headers/arch/x86/hal_io.h:76` | `#define HAL_MOUSE_CMD_DISABLE` |
| `HAL_MOUSE_CMD_ENABLE` | macro | `headers/arch/x86/hal_io.h:74` | `#define HAL_MOUSE_CMD_ENABLE` |
| `HAL_MOUSE_CMD_GET_ID` | macro | `headers/arch/x86/hal_io.h:70` | `#define HAL_MOUSE_CMD_GET_ID` |
| `HAL_MOUSE_CMD_RESET` | macro | `headers/arch/x86/hal_io.h:66` | `#define HAL_MOUSE_CMD_RESET` |
| `HAL_MOUSE_CMD_SET_RATE` | macro | `headers/arch/x86/hal_io.h:68` | `#define HAL_MOUSE_CMD_SET_RATE` |
| `HAL_MOUSE_HW_TIMEOUT` | macro | `headers/arch/x86/hal_io.h:86` | `#define HAL_MOUSE_HW_TIMEOUT` |
| `HAL_MOUSE_ID_INTELLI` | macro | `headers/arch/x86/hal_io.h:84` | `#define HAL_MOUSE_ID_INTELLI` |
| `HAL_MOUSE_OVF_BITS` | macro | `headers/arch/x86/hal_io.h:91` | `#define HAL_MOUSE_OVF_BITS` |
| `HAL_MOUSE_PACKET_LEN` | macro | `headers/arch/x86/hal_io.h:95` | `#define HAL_MOUSE_PACKET_LEN` |
| `HAL_MOUSE_RATE_KNOCK_100` | macro | `headers/arch/x86/hal_io.h:80` | `#define HAL_MOUSE_RATE_KNOCK_100` |
| `HAL_MOUSE_RATE_KNOCK_200` | macro | `headers/arch/x86/hal_io.h:78` | `#define HAL_MOUSE_RATE_KNOCK_200` |
| `HAL_MOUSE_RATE_KNOCK_80` | macro | `headers/arch/x86/hal_io.h:82` | `#define HAL_MOUSE_RATE_KNOCK_80` |
| `HAL_MOUSE_SCALE` | macro | `headers/arch/x86/hal_io.h:97` | `#define HAL_MOUSE_SCALE` |
| `HAL_MOUSE_SYNC_BIT` | macro | `headers/arch/x86/hal_io.h:89` | `#define HAL_MOUSE_SYNC_BIT` |
| `HAL_PIC1_CMD` | macro | `headers/arch/x86/hal_io.h:16` | `#define HAL_PIC1_CMD` |
| `HAL_PIC1_DATA` | macro | `headers/arch/x86/hal_io.h:18` | `#define HAL_PIC1_DATA` |
| `HAL_PIC2_CMD` | macro | `headers/arch/x86/hal_io.h:20` | `#define HAL_PIC2_CMD` |
| `HAL_PIC2_DATA` | macro | `headers/arch/x86/hal_io.h:22` | `#define HAL_PIC2_DATA` |
| `HAL_PIC_EOI` | macro | `headers/arch/x86/hal_io.h:24` | `#define HAL_PIC_EOI` |
| `HAL_PIT_CH0` | macro | `headers/arch/x86/hal_io.h:29` | `#define HAL_PIT_CH0` |
| `HAL_PIT_CMD` | macro | `headers/arch/x86/hal_io.h:27` | `#define HAL_PIT_CMD` |
| `HAL_PS2_CMD_DISABLE_AUX` | macro | `headers/arch/x86/hal_io.h:46` | `#define HAL_PS2_CMD_DISABLE_AUX` |
| `HAL_PS2_CMD_DISABLE_KBD` | macro | `headers/arch/x86/hal_io.h:50` | `#define HAL_PS2_CMD_DISABLE_KBD` |
| `HAL_PS2_CMD_ENABLE_AUX` | macro | `headers/arch/x86/hal_io.h:44` | `#define HAL_PS2_CMD_ENABLE_AUX` |
| `HAL_PS2_CMD_ENABLE_KBD` | macro | `headers/arch/x86/hal_io.h:48` | `#define HAL_PS2_CMD_ENABLE_KBD` |
| `HAL_PS2_CMD_READ_CONFIG` | macro | `headers/arch/x86/hal_io.h:52` | `#define HAL_PS2_CMD_READ_CONFIG` |
| `HAL_PS2_CMD_WRITE_CONFIG` | macro | `headers/arch/x86/hal_io.h:54` | `#define HAL_PS2_CMD_WRITE_CONFIG` |
| `HAL_PS2_CMD_WRITE_MOUSE` | macro | `headers/arch/x86/hal_io.h:42` | `#define HAL_PS2_CMD_WRITE_MOUSE` |
| `HAL_PS2_CONFIG_DISABLE_AUX` | macro | `headers/arch/x86/hal_io.h:62` | `#define HAL_PS2_CONFIG_DISABLE_AUX` |
| `HAL_PS2_CONFIG_DISABLE_KBD` | macro | `headers/arch/x86/hal_io.h:60` | `#define HAL_PS2_CONFIG_DISABLE_KBD` |
| `HAL_PS2_CONFIG_IRQ1` | macro | `headers/arch/x86/hal_io.h:56` | `#define HAL_PS2_CONFIG_IRQ1` |
| `HAL_PS2_CONFIG_IRQ12` | macro | `headers/arch/x86/hal_io.h:58` | `#define HAL_PS2_CONFIG_IRQ12` |
| `HAL_PS2_CONFIG_TRANSLATE` | macro | `headers/arch/x86/hal_io.h:64` | `#define HAL_PS2_CONFIG_TRANSLATE` |
| `HAL_PS2_DATA` | macro | `headers/arch/x86/hal_io.h:34` | `#define HAL_PS2_DATA` |
| `HAL_PS2_IBF_EMPTY` | macro | `headers/arch/x86/hal_io.h:38` | `#define HAL_PS2_IBF_EMPTY` |
| `HAL_PS2_MOUSE_OBF` | macro | `headers/arch/x86/hal_io.h:36` | `#define HAL_PS2_MOUSE_OBF` |
| `HAL_PS2_OBF_FULL` | macro | `headers/arch/x86/hal_io.h:40` | `#define HAL_PS2_OBF_FULL` |
| `HAL_PS2_STATUS` | macro | `headers/arch/x86/hal_io.h:32` | `#define HAL_PS2_STATUS` |
| `hal_inb` | function | `headers/arch/x86/hal_io.h:196` | `static inline unsigned char hal_inb(unsigned short port)` |
| `hal_inb` | function | `headers/arch/x86/hal_io.h:235` | `static inline unsigned char hal_inb(unsigned short port)` |
| `hal_inw` | function | `headers/arch/x86/hal_io.h:209` | `static inline unsigned short hal_inw(unsigned short port)` |
| `hal_inw` | function | `headers/arch/x86/hal_io.h:247` | `static inline unsigned short hal_inw(unsigned short port)` |
| `hal_io_stub_lapic_eois` | variable | `headers/arch/x86/hal_io.h:184` | `extern unsigned hal_io_stub_lapic_eois;` |
| `hal_io_stub_last_port` | variable | `headers/arch/x86/hal_io.h:180` | `extern unsigned hal_io_stub_last_port;` |
| `hal_io_stub_last_val` | variable | `headers/arch/x86/hal_io.h:182` | `extern unsigned hal_io_stub_last_val;` |
| `hal_io_stub_read_val` | variable | `headers/arch/x86/hal_io.h:186` | `extern unsigned char hal_io_stub_read_val;` |
| `hal_io_stub_writes` | variable | `headers/arch/x86/hal_io.h:178` | `extern unsigned hal_io_stub_writes;` |
| `hal_lapic_eoi` | function | `headers/arch/x86/hal_io.h:215` | `static inline void hal_lapic_eoi(void)` |
| `hal_lapic_eoi` | function | `headers/arch/x86/hal_io.h:254` | `static inline void hal_lapic_eoi(void)` |
| `hal_mmio_mb` | function | `headers/arch/x86/hal_io.h:171` | `static inline void hal_mmio_mb(void)` |
| `hal_mmio_read16` | function | `headers/arch/x86/hal_io.h:139` | `static inline unsigned short hal_mmio_read16(const volatile unsigned short *addr)` |
| `hal_mmio_read64` | function | `headers/arch/x86/hal_io.h:128` | `static inline unsigned long long hal_mmio_read64(const volatile unsigned long long *addr)` |
| `hal_mmio_read8` | function | `headers/arch/x86/hal_io.h:150` | `static inline unsigned char hal_mmio_read8(const volatile unsigned char *addr)` |
| `hal_mmio_rmb` | function | `headers/arch/x86/hal_io.h:166` | `static inline void hal_mmio_rmb(void)` |
| `hal_mmio_wmb` | function | `headers/arch/x86/hal_io.h:161` | `static inline void hal_mmio_wmb(void)` |
| `hal_mmio_write16` | function | `headers/arch/x86/hal_io.h:144` | `static inline void hal_mmio_write16(volatile unsigned short *addr,                               ...` |
| `hal_mmio_write32` | function | `headers/arch/x86/hal_io.h:123` | `static inline void hal_mmio_write32(volatile unsigned *addr, unsigned val)` |
| `hal_mmio_write64` | function | `headers/arch/x86/hal_io.h:133` | `static inline void hal_mmio_write64(volatile unsigned long long *addr,                           ...` |
| `hal_mmio_write8` | function | `headers/arch/x86/hal_io.h:155` | `static inline void hal_mmio_write8(volatile unsigned char *addr,                                 ...` |
| `hal_outb` | function | `headers/arch/x86/hal_io.h:189` | `static inline void hal_outb(unsigned short port, unsigned char val)` |
| `hal_outb` | function | `headers/arch/x86/hal_io.h:230` | `static inline void hal_outb(unsigned short port, unsigned char val)` |
| `hal_outw` | function | `headers/arch/x86/hal_io.h:202` | `static inline void hal_outw(unsigned short port, unsigned short val)` |
| `hal_outw` | function | `headers/arch/x86/hal_io.h:242` | `static inline void hal_outw(unsigned short port, unsigned short val)` |
| `hal_pic_eoi` | function | `headers/arch/x86/hal_io.h:220` | `static inline void hal_pic_eoi(int irq)` |
| `hal_pic_eoi` | function | `headers/arch/x86/hal_io.h:259` | `static inline void hal_pic_eoi(int irq)` |
| `ARCH_X86_MSR_H` | macro | `headers/arch/x86/msr.h:2` | `#define ARCH_X86_MSR_H` |
| `MSR_FSBASE` | macro | `headers/arch/x86/msr.h:22` | `#define MSR_FSBASE` |
| `MSR_GSBASE` | macro | `headers/arch/x86/msr.h:23` | `#define MSR_GSBASE` |
| `MSR_KERNEL_GS_BASE` | macro | `headers/arch/x86/msr.h:24` | `#define MSR_KERNEL_GS_BASE` |
| `MSR_LSTAR` | macro | `headers/arch/x86/msr.h:20` | `#define MSR_LSTAR` |
| `MSR_SFMASK` | macro | `headers/arch/x86/msr.h:21` | `#define MSR_SFMASK` |
| `MSR_STAR` | macro | `headers/arch/x86/msr.h:19` | `#define MSR_STAR` |
| `rdmsr` | function | `headers/arch/x86/msr.h:13` | `static inline unsigned long rdmsr(unsigned msr)` |
| `wrmsr` | function | `headers/arch/x86/msr.h:8` | `static inline void wrmsr(unsigned msr, unsigned long val)` |
| `ARENA_DEFAULT_ALIGN` | macro | `headers/arena.h:38` | `#define ARENA_DEFAULT_ALIGN` |
| `MINIOS_ARENA_H` | macro | `headers/arena.h:33` | `#define MINIOS_ARENA_H` |
| `arena_align_up` | function | `headers/arena.h:62` | `static inline size_t arena_align_up(size_t n, size_t align)` |
| `arena_alloc` | function | `headers/arena.h:81` | `static inline void *arena_alloc(arena_t *a, size_t size, size_t align)` |
| `arena_bytes_for` | function | `headers/arena.h:74` | `static inline size_t arena_bytes_for(size_t count, size_t elem_size)` |
| `arena_checkpoint` | function | `headers/arena.h:113` | `static inline size_t arena_checkpoint(const arena_t *a)` |
| `arena_contains` | function | `headers/arena.h:128` | `static inline int arena_contains(const arena_t *a, const void *ptr)` |
| `arena_free_bytes` | function | `headers/arena.h:101` | `static inline size_t arena_free_bytes(const arena_t *a)` |
| `arena_init` | function | `headers/arena.h:48` | `static inline void arena_init(arena_t *a, void *block, size_t size)` |
| `arena_reset` | function | `headers/arena.h:107` | `static inline void arena_reset(arena_t *a)` |
| `arena_rewind` | function | `headers/arena.h:119` | `static inline int arena_rewind(arena_t *a, size_t checkpoint)` |
| `arena_used` | function | `headers/arena.h:95` | `static inline size_t arena_used(const arena_t *a)` |
| `kfree` | function | `headers/arena.h:25` | `* kfree(back);` |
| `kmalloc` | function | `headers/arena.h:3` | `* * A bump arena serves one kmalloc (kernel) or malloc (ring-3) with pointer * bumps instead of N allocator round...` |
| `minios_arena` | struct | `headers/arena.h:41` | `` |
| `AUDIO_CHANNELS_MONO` | macro | `headers/audio.h:16` | `#define AUDIO_CHANNELS_MONO` |
| `AUDIO_FORMAT_S16` | macro | `headers/audio.h:18` | `#define AUDIO_FORMAT_S16` |
| `AUDIO_FORMAT_U8` | macro | `headers/audio.h:17` | `#define AUDIO_FORMAT_U8` |
| `AUDIO_H` | macro | `headers/audio.h:2` | `#define AUDIO_H` |
| `AUDIO_RATE_DEFAULT` | macro | `headers/audio.h:15` | `#define AUDIO_RATE_DEFAULT` |
| `audio_get_volume` | function | `headers/audio.h:34` | `unsigned audio_get_volume(void);` |
| `audio_init` | function | `headers/audio.h:21` | `int audio_init(void);` |
| `audio_pcm_close` | function | `headers/audio.h:30` | `void audio_pcm_close(void);` |
| `audio_pcm_open` | function | `headers/audio.h:27` | `int audio_pcm_open(unsigned rate, unsigned channels, unsigned format);` |
| `audio_pcm_pump` | function | `headers/audio.h:29` | `void audio_pcm_pump(void);` |
| `audio_pcm_submit` | function | `headers/audio.h:28` | `int audio_pcm_submit(const void *buf, unsigned len);` |
| `audio_sb16_present` | function | `headers/audio.h:37` | `int audio_sb16_present(void);` |
| `audio_set_volume` | function | `headers/audio.h:33` | `void audio_set_volume(unsigned volume);` |
| `audio_stream_close` | function | `headers/audio.h:41` | `void audio_stream_close(int id);` |
| `audio_stream_open` | function | `headers/audio.h:40` | `int audio_stream_open(void);` |
| `audio_stream_submit` | function | `headers/audio.h:42` | `int audio_stream_submit(int id, const void *buf, unsigned len);` |
| `audio_stream_volume` | function | `headers/audio.h:43` | `void audio_stream_volume(int id, unsigned char vol);` |
| `audio_tone` | function | `headers/audio.h:24` | `void audio_tone(unsigned freq);` |
| `BATCH_ERR_COUNT` | macro | `headers/batch.h:49` | `#define BATCH_ERR_COUNT` |
| `BATCH_ERR_OPCODE` | macro | `headers/batch.h:51` | `#define BATCH_ERR_OPCODE` |
| `BATCH_ERR_PTR` | macro | `headers/batch.h:50` | `#define BATCH_ERR_PTR` |
| `BATCH_H` | macro | `headers/batch.h:2` | `#define BATCH_H` |
| `BATCH_MAX_OPS` | macro | `headers/batch.h:41` | `#define BATCH_MAX_OPS` |
| `BATCH_OK` | macro | `headers/batch.h:48` | `#define BATCH_OK` |
| `BATCH_OP_GETPID` | macro | `headers/batch.h:46` | `#define BATCH_OP_GETPID` |
| `BATCH_OP_NOP` | macro | `headers/batch.h:43` | `#define BATCH_OP_NOP` |
| `BATCH_OP_TIME` | macro | `headers/batch.h:45` | `#define BATCH_OP_TIME` |
| `BATCH_OP_YIELD` | macro | `headers/batch.h:44` | `#define BATCH_OP_YIELD` |
| `batch_exec` | function | `headers/batch.h:62` | `long batch_exec(const batch_op_t *ops, long *results, int count, int *completed, batch_handler_t dispatch);` |
| `batch_op_t` | struct | `headers/batch.h:53` | `` |
| `BLOCK_H` | macro | `headers/block.h:2` | `#define BLOCK_H` |
| `BLOCK_SHIFT` | macro | `headers/block.h:8` | `#define BLOCK_SHIFT` |
| `BLOCK_SIZE` | macro | `headers/block.h:7` | `#define BLOCK_SIZE` |
| `SECTORS_PER_BLOCK` | macro | `headers/block.h:9` | `#define SECTORS_PER_BLOCK` |
| `block_disk_sectors` | function | `headers/block.h:40` | `unsigned long block_disk_sectors(void);` |
| `block_flush` | function | `headers/block.h:27` | `void block_flush(void);` |
| `block_init` | function | `headers/block.h:12` | `void block_init(void);` |
| `block_read` | function | `headers/block.h:18` | `int block_read(unsigned int block_num, void *buf);` |
| `block_read_multi` | function | `headers/block.h:23` | `int block_read_multi(unsigned int block_num, unsigned int count, void *buf);` |
| `block_read_sectors` | function | `headers/block.h:37` | `int block_read_sectors(unsigned lba, unsigned count, void *buf);` |
| `block_set_base` | function | `headers/block.h:15` | `void block_set_base(unsigned int lba_base);` |
| `block_total` | function | `headers/block.h:30` | `unsigned int block_total(void);` |
| `block_write` | function | `headers/block.h:19` | `int block_write(unsigned int block_num, const void *buf);` |
| `block_write_multi` | function | `headers/block.h:24` | `int block_write_multi(unsigned int block_num, unsigned int count, const void *buf);` |
| `DESKTOP_ICONS_H` | macro | `headers/desktop_icons.h:8` | `#define DESKTOP_ICONS_H` |
| `ICON_EMBEDDED_H` | macro | `headers/desktop_icons.h:13` | `#define ICON_EMBEDDED_H` |
| `ICON_EMBEDDED_W` | macro | `headers/desktop_icons.h:12` | `#define ICON_EMBEDDED_W` |
| `DESKTOP_SHORTCUTS_H` | macro | `headers/desktop_shortcuts.h:13` | `#define DESKTOP_SHORTCUTS_H` |
| `DOCK_BOUNCE_H` | macro | `headers/desktop_shortcuts.h:57` | `#define DOCK_BOUNCE_H` |
| `DOCK_BOUNCE_TICKS` | macro | `headers/desktop_shortcuts.h:58` | `#define DOCK_BOUNCE_TICKS` |
| `DOCK_CRYSTAL_STEP` | macro | `headers/desktop_shortcuts.h:41` | `#define DOCK_CRYSTAL_STEP` |
| `DOCK_GAP` | macro | `headers/desktop_shortcuts.h:35` | `#define DOCK_GAP` |
| `DOCK_LABEL_GAP` | macro | `headers/desktop_shortcuts.h:36` | `#define DOCK_LABEL_GAP` |
| `DOCK_MAG_H` | macro | `headers/desktop_shortcuts.h:49` | `#define DOCK_MAG_H` |
| `DOCK_MAG_W` | macro | `headers/desktop_shortcuts.h:48` | `#define DOCK_MAG_W` |
| `DOCK_NEAR_H` | macro | `headers/desktop_shortcuts.h:51` | `#define DOCK_NEAR_H` |
| `DOCK_NEAR_W` | macro | `headers/desktop_shortcuts.h:50` | `#define DOCK_NEAR_W` |
| `DOCK_PAD_X` | macro | `headers/desktop_shortcuts.h:33` | `#define DOCK_PAD_X` |
| `DOCK_PAD_Y` | macro | `headers/desktop_shortcuts.h:34` | `#define DOCK_PAD_Y` |
| `ICON_H` | macro | `headers/desktop_shortcuts.h:25` | `#define ICON_H` |
| `ICON_LABEL_H` | macro | `headers/desktop_shortcuts.h:28` | `#define ICON_LABEL_H` |
| `ICON_PAD_X` | macro | `headers/desktop_shortcuts.h:26` | `#define ICON_PAD_X` |
| `ICON_PAD_Y` | macro | `headers/desktop_shortcuts.h:27` | `#define ICON_PAD_Y` |
| `ICON_PAL_BASE` | macro | `headers/desktop_shortcuts.h:65` | `#define ICON_PAL_BASE` |
| `ICON_PAL_SIZE` | macro | `headers/desktop_shortcuts.h:66` | `#define ICON_PAL_SIZE` |
| `ICON_W` | macro | `headers/desktop_shortcuts.h:24` | `#define ICON_W` |
| `MAX_SHORTCUTS` | macro | `headers/desktop_shortcuts.h:18` | `#define MAX_SHORTCUTS` |
| `SHORTCUT_CMD_LEN` | macro | `headers/desktop_shortcuts.h:20` | `#define SHORTCUT_CMD_LEN` |
| `SHORTCUT_NAME_LEN` | macro | `headers/desktop_shortcuts.h:19` | `#define SHORTCUT_NAME_LEN` |
| `SHORTCUT_PATH_LEN` | macro | `headers/desktop_shortcuts.h:21` | `#define SHORTCUT_PATH_LEN` |
| `desktop_shortcut` | struct | `headers/desktop_shortcuts.h:72` | `` |
| `desktop_shortcuts_draw` | function | `headers/desktop_shortcuts.h:85` | `void desktop_shortcuts_draw(void);` |
| `desktop_shortcuts_hit_test` | function | `headers/desktop_shortcuts.h:89` | `const char *desktop_shortcuts_hit_test(int mx, int my);` |
| `desktop_shortcuts_load` | function | `headers/desktop_shortcuts.h:82` | `void desktop_shortcuts_load(void);` |
| `DEV_MAX` | macro | `headers/driver.h:19` | `#define DEV_MAX` |
| `DEV_NAME_LEN` | macro | `headers/driver.h:18` | `#define DEV_NAME_LEN` |
| `DEV_TYPE_AUDIO` | macro | `headers/driver.h:22` | `#define DEV_TYPE_AUDIO` |
| `DEV_TYPE_BLOCK` | macro | `headers/driver.h:21` | `#define DEV_TYPE_BLOCK` |
| `DEV_TYPE_CHAR` | macro | `headers/driver.h:24` | `#define DEV_TYPE_CHAR` |
| `DEV_TYPE_NET` | macro | `headers/driver.h:23` | `#define DEV_TYPE_NET` |
| `DRIVER_H` | macro | `headers/driver.h:2` | `#define DRIVER_H` |
| `audio_ops_t` | struct | `headers/driver.h:37` | `` |
| `block_ops_t` | struct | `headers/driver.h:28` | `` |
| `device` | struct | `headers/driver.h:48` | `` |
| `device_count` | function | `headers/driver.h:59` | `int device_count(void);` |
| `device_find` | function | `headers/driver.h:57` | `device_t *device_find(const char *name);` |
| `device_find_by_type` | function | `headers/driver.h:58` | `device_t *device_find_by_type(int type);` |
| `device_register` | function | `headers/driver.h:56` | `int device_register(device_t *dev);` |
| `device_reset` | function | `headers/driver.h:60` | `void device_reset(void);` |
| `device_t` | type_alias | `headers/driver.h:25` | `typedef struct device device_t;` |
| `KBD_H` | macro | `headers/drivers/kbd.h:2` | `#define KBD_H` |
| `KBD_LAYOUT_EN` | macro | `headers/drivers/kbd.h:6` | `#define KBD_LAYOUT_EN` |
| `KBD_LAYOUT_ES` | macro | `headers/drivers/kbd.h:7` | `#define KBD_LAYOUT_ES` |
| `kbd_available` | function | `headers/drivers/kbd.h:9` | `int kbd_available(void);` |
| `kbd_drop_counts` | function | `headers/drivers/kbd.h:32` | `void kbd_drop_counts(unsigned long *cooked, unsigned long *raw);` |
| `kbd_e0_get` | function | `headers/drivers/kbd.h:40` | `int kbd_e0_get(void);` |
| `kbd_e0_set` | function | `headers/drivers/kbd.h:41` | `void kbd_e0_set(int v);` |
| `kbd_feed_scancode` | function | `headers/drivers/kbd.h:11` | `int kbd_feed_scancode(unsigned char sc);` |
| `kbd_flush_all` | function | `headers/drivers/kbd.h:42` | `void kbd_flush_all(void);` |
| `kbd_get_layout` | function | `headers/drivers/kbd.h:15` | `int kbd_get_layout(void);` |
| `kbd_q_empty` | function | `headers/drivers/kbd.h:27` | `int kbd_q_empty(void);` |
| `kbd_q_pop` | function | `headers/drivers/kbd.h:28` | `int kbd_q_pop(void);` |
| `kbd_q_push` | function | `headers/drivers/kbd.h:29` | `void kbd_q_push(unsigned char c);` |
| `kbd_raw_empty` | function | `headers/drivers/kbd.h:37` | `int kbd_raw_empty(void);` |
| `kbd_raw_flush` | function | `headers/drivers/kbd.h:43` | `void kbd_raw_flush(void);` |
| `kbd_raw_mode_get` | function | `headers/drivers/kbd.h:35` | `int kbd_raw_mode_get(void);` |
| `kbd_raw_mode_set` | function | `headers/drivers/kbd.h:36` | `void kbd_raw_mode_set(int on);` |
| `kbd_raw_pop` | function | `headers/drivers/kbd.h:38` | `int kbd_raw_pop(void);` |
| `kbd_raw_push_byte` | function | `headers/drivers/kbd.h:39` | `void kbd_raw_push_byte(unsigned char c);` |
| `kbd_read` | function | `headers/drivers/kbd.h:10` | `int kbd_read(void);` |
| `kbd_reset_for_shell` | function | `headers/drivers/kbd.h:12` | `void kbd_reset_for_shell(void);` |
| `kbd_set_layout` | function | `headers/drivers/kbd.h:16` | `void kbd_set_layout(int layout);` |
| `kbd_sys_raw_filter` | function | `headers/drivers/kbd.h:50` | `int kbd_sys_raw_filter(unsigned char sc);` |
| `kbd_toggle_layout` | function | `headers/drivers/kbd.h:17` | `void kbd_toggle_layout(void);` |
| `MODIFIERS_H` | macro | `headers/drivers/modifiers.h:2` | `#define MODIFIERS_H` |
| `MOD_ALT` | macro | `headers/drivers/modifiers.h:32` | `#define MOD_ALT` |
| `MOD_ALTGR` | macro | `headers/drivers/modifiers.h:33` | `#define MOD_ALTGR` |
| `MOD_CTRL` | macro | `headers/drivers/modifiers.h:31` | `#define MOD_CTRL` |
| `MOD_SHIFT` | macro | `headers/drivers/modifiers.h:30` | `#define MOD_SHIFT` |
| `MOD_SUPER` | macro | `headers/drivers/modifiers.h:34` | `#define MOD_SUPER` |
| `modifier_keys_t` | struct | `headers/drivers/modifiers.h:19` | `` |
| `modifier_state_t` | struct | `headers/drivers/modifiers.h:5` | `` |
| `modifiers_init` | function | `headers/drivers/modifiers.h:37` | `static inline void modifiers_init(modifier_state_t *st)` |
| `modifiers_match` | function | `headers/drivers/modifiers.h:92` | `static inline int modifiers_match(const modifier_state_t *st, int mask)` |
| `modifiers_update` | function | `headers/drivers/modifiers.h:54` | `static inline int modifiers_update(const modifier_keys_t *keys,                                  ...` |
| `MOUSE_H` | macro | `headers/drivers/mouse.h:2` | `#define MOUSE_H` |
| `mouse_disable` | function | `headers/drivers/mouse.h:14` | `void mouse_disable(void);` |
| `mouse_enable` | function | `headers/drivers/mouse.h:17` | `void mouse_enable(void);` |
| `mouse_hw_init` | function | `headers/drivers/mouse.h:11` | `void mouse_hw_init(void);` |
| `DRIVERS_NVME_H` | macro | `headers/drivers/nvme.h:2` | `#define DRIVERS_NVME_H` |
| `nvme_init` | function | `headers/drivers/nvme.h:4` | `int nvme_init(void);` |
| `nvme_note` | function | `headers/drivers/nvme.h:7` | `const char *nvme_note(void);` |
| `nvme_present` | function | `headers/drivers/nvme.h:5` | `int nvme_present(void);` |
| `nvme_read_sectors` | function | `headers/drivers/nvme.h:9` | `int nvme_read_sectors(unsigned lba, unsigned count, void *buf);` |
| `nvme_sectors` | function | `headers/drivers/nvme.h:8` | `unsigned long nvme_sectors(void);` |
| `nvme_version` | function | `headers/drivers/nvme.h:6` | `unsigned nvme_version(void);` |
| `DRIVERS_PCI_H` | macro | `headers/drivers/pci.h:11` | `#define DRIVERS_PCI_H` |
| `PCI_ABSENT_ID` | macro | `headers/drivers/pci.h:44` | `#define PCI_ABSENT_ID` |
| `PCI_BAR_64BIT` | macro | `headers/drivers/pci.h:39` | `#define PCI_BAR_64BIT` |
| `PCI_BAR_ADDR_MASK` | macro | `headers/drivers/pci.h:41` | `#define PCI_BAR_ADDR_MASK` |
| `PCI_BAR_IO` | macro | `headers/drivers/pci.h:38` | `#define PCI_BAR_IO` |
| `PCI_BAR_PREFETCH` | macro | `headers/drivers/pci.h:40` | `#define PCI_BAR_PREFETCH` |
| `PCI_BAR_TYPE_MASK` | macro | `headers/drivers/pci.h:37` | `#define PCI_BAR_TYPE_MASK` |
| `PCI_CFG_ADDR` | macro | `headers/drivers/pci.h:13` | `#define PCI_CFG_ADDR` |
| `PCI_CFG_DATA` | macro | `headers/drivers/pci.h:14` | `#define PCI_CFG_DATA` |
| `PCI_CLASS_ANY` | macro | `headers/drivers/pci.h:62` | `#define PCI_CLASS_ANY` |
| `PCI_CLASS_BRIDGE` | macro | `headers/drivers/pci.h:55` | `#define PCI_CLASS_BRIDGE` |
| `PCI_CLASS_MAX_PASSES` | macro | `headers/drivers/pci.h:68` | `#define PCI_CLASS_MAX_PASSES` |
| `PCI_CLASS_XHCI` | macro | `headers/drivers/pci.h:57` | `#define PCI_CLASS_XHCI` |
| `PCI_COMMAND_BUS_MASTER` | macro | `headers/drivers/pci.h:34` | `#define PCI_COMMAND_BUS_MASTER` |
| `PCI_COMMAND_IO` | macro | `headers/drivers/pci.h:32` | `#define PCI_COMMAND_IO` |
| `PCI_COMMAND_MEMORY` | macro | `headers/drivers/pci.h:33` | `#define PCI_COMMAND_MEMORY` |
| `PCI_HDR_TYPE_BRIDGE` | macro | `headers/drivers/pci.h:47` | `#define PCI_HDR_TYPE_BRIDGE` |
| `PCI_HEADER_MULTIFUNC` | macro | `headers/drivers/pci.h:45` | `#define PCI_HEADER_MULTIFUNC` |
| `PCI_HEADER_TYPE_MASK` | macro | `headers/drivers/pci.h:46` | `#define PCI_HEADER_TYPE_MASK` |
| `PCI_MAX_BUS` | macro | `headers/drivers/pci.h:15` | `#define PCI_MAX_BUS` |
| `PCI_MAX_DEV` | macro | `headers/drivers/pci.h:16` | `#define PCI_MAX_DEV` |
| `PCI_MAX_FUNC` | macro | `headers/drivers/pci.h:17` | `#define PCI_MAX_FUNC` |
| `PCI_PROGIF_XHCI` | macro | `headers/drivers/pci.h:59` | `#define PCI_PROGIF_XHCI` |
| `PCI_REG_BAR0` | macro | `headers/drivers/pci.h:25` | `#define PCI_REG_BAR0` |
| `PCI_REG_BAR_COUNT` | macro | `headers/drivers/pci.h:29` | `#define PCI_REG_BAR_COUNT` |

Next: [SYMBOLS_p4.md](SYMBOLS_p4.md)
