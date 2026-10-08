# Symbols (page 23 of 24)
Previous: [SYMBOLS_p22.md](SYMBOLS_p22.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `PCI_MMIO_SIZE` | macro | `tests/stubs/kernel.h:22` | `#define PCI_MMIO_SIZE` |
| `TEST_STUB_KERNEL_H` | macro | `tests/stubs/kernel.h:14` | `#define TEST_STUB_KERNEL_H` |
| `__attribute__` | function | `tests/stubs/kernel.h:30` | `static __attribute__((unused)) void kfree(void *p)` |
| `__attribute__` | function | `tests/stubs/kernel.h:34` | `static __attribute__((unused)) void *kmalloc_aligned(unsigned long size, unsigned long align)` |
| `__attribute__` | function | `tests/stubs/kernel.h:51` | `static __attribute__((unused)) int kprintf(const char *fmt, ...)` |
| `__attribute__` | function | `tests/stubs/kernel.h:60` | `static __attribute__((unused)) int kmm_make_uncached(unsigned long phys, unsigned long len)` |
| `__attribute__` | function | `tests/stubs/kernel.h:66` | `static __attribute__((unused)) unsigned long kmm_map_device(unsigned long phys,                  ...` |
| `__attribute__` | function | `tests/stubs/kernel.h:74` | `static __attribute__((unused)) unsigned long ktime_ms(void)` |
| `__attribute__` | function | `tests/stubs/kernel.h:80` | `static __attribute__((unused)) irqflags_t spin_save_irq(void)` |
| `__attribute__` | function | `tests/stubs/kernel.h:84` | `static __attribute__((unused)) void spin_restore_irq(irqflags_t flags)` |
| `irqflags_t` | type_alias | `tests/stubs/kernel.h:77` | `typedef unsigned long irqflags_t;` |
| `kmemcpy` | macro | `tests/stubs/kernel.h:49` | `#define kmemcpy` |
| `kmemset` | macro | `tests/stubs/kernel.h:48` | `#define kmemset` |
| `observe` | function | `tests/stubs/kernel.h:8` | `* the tests must observe (fed scancodes, queued bytes, registered devices)  * is recorded in vari...` |
| `stub_ms_now` | variable | `tests/stubs/kernel.h:72` | `extern unsigned long stub_ms_now;` |
| `expect` | function | `tests/test_abi.c:16` | `static void expect(const char *name, const char *manifest, int want)` |
| `main` | function | `tests/test_abi.c:25` | `int main(void)` |
| `CHECK` | macro | `tests/test_arena.c:14` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_arena.c:23` | `int main(void)` |
| `CHECK` | macro | `tests/test_batch.c:17` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_batch.c:31` | `int main(void)` |
| `stub_dispatch` | function | `tests/test_batch.c:24` | `static long stub_dispatch(uint32_t opcode)` |
| `ExtendedLegendTests` | class | `tests/test_doom_pwad.py:255` | `class ExtendedLegendTests(TestCase)` |
| `GridValidationTests` | class | `tests/test_doom_pwad.py:29` | `class GridValidationTests(TestCase)` |
| `MultiSectorMutationTests` | class | `tests/test_doom_pwad.py:388` | `class MultiSectorMutationTests(TestCase)` |
| `MultiSectorTests` | class | `tests/test_doom_pwad.py:317` | `class MultiSectorTests(TestCase)` |
| `PwadLayoutTests` | class | `tests/test_doom_pwad.py:82` | `class PwadLayoutTests(TestCase)` |
| `PwadMutationTests` | class | `tests/test_doom_pwad.py:181` | `class PwadMutationTests(TestCase)` |
| `door_line` | method | `tests/test_doom_pwad.py:406` | `def door_line(self)` |
| `lump_blob` | method | `tests/test_doom_pwad.py:310` | `def lump_blob(blob, idx)` |
| `mutate_line` | method | `tests/test_doom_pwad.py:395` | `def mutate_line(self, idx, field, value)` |
| `setUp` | method | `tests/test_doom_pwad.py:184` | `def setUp(self)` |
| `setUp` | method | `tests/test_doom_pwad.py:391` | `def setUp(self)` |
| `test_bad_magic_dies` | method | `tests/test_doom_pwad.py:188` | `def test_bad_magic_dies(self)` |
| `test_dark_and_nukage_sector_props` | method | `tests/test_doom_pwad.py:355` | `def test_dark_and_nukage_sector_props(self)` |
| `test_door_lines_are_tagged_openers` | method | `tests/test_doom_pwad.py:327` | `def test_door_lines_are_tagged_openers(self)` |
| `test_door_room_builds_two_sectors` | method | `tests/test_doom_pwad.py:320` | `def test_door_room_builds_two_sectors(self)` |
| `test_door_tag_zero_dies` | method | `tests/test_doom_pwad.py:418` | `def test_door_tag_zero_dies(self)` |
| `test_every_legend_char_builds` | method | `tests/test_doom_pwad.py:273` | `def test_every_legend_char_builds(self)` |
| `test_every_thing_id_matches_engine` | method | `tests/test_doom_pwad.py:278` | `def test_every_thing_id_matches_engine(self)` |
| `test_exit_needs_wall` | method | `tests/test_doom_pwad.py:66` | `def test_exit_needs_wall(self)` |
| `test_exit_on_every_side` | method | `tests/test_doom_pwad.py:141` | `def test_exit_on_every_side(self)` |
| `test_exit_switch_pin` | method | `tests/test_doom_pwad.py:129` | `def test_exit_switch_pin(self)` |
| `test_exit_tagged_dies` | method | `tests/test_doom_pwad.py:433` | `def test_exit_tagged_dies(self)` |
| `test_header_pin` | method | `tests/test_doom_pwad.py:96` | `def test_header_pin(self)` |
| `test_illegal_char_refused` | method | `tests/test_doom_pwad.py:51` | `def test_illegal_char_refused(self)` |
| `test_lump_order_pin` | method | `tests/test_doom_pwad.py:103` | `def test_lump_order_pin(self)` |
| `test_missing_exit_dies` | method | `tests/test_doom_pwad.py:230` | `def test_missing_exit_dies(self)` |
| `test_missing_exit_refused` | method | `tests/test_doom_pwad.py:46` | `def test_missing_exit_refused(self)` |
| `test_missing_player_refused` | method | `tests/test_doom_pwad.py:41` | `def test_missing_player_refused(self)` |
| `test_new_legend_chars_build` | method | `tests/test_doom_pwad.py:382` | `def test_new_legend_chars_build(self)` |
| `test_onesided_with_back_dies` | method | `tests/test_doom_pwad.py:428` | `def test_onesided_with_back_dies(self)` |
| `test_open_boundary_dies` | method | `tests/test_doom_pwad.py:168` | `def test_open_boundary_dies(self)` |
| `test_partial_record_dies` | method | `tests/test_doom_pwad.py:212` | `def test_partial_record_dies(self)` |
| `test_pillar_room_stays_closed` | method | `tests/test_doom_pwad.py:154` | `def test_pillar_room_stays_closed(self)` |
| `test_ragged_rows_refused` | method | `tests/test_doom_pwad.py:36` | `def test_ragged_rows_refused(self)` |
| `test_reject_scales_with_sector_count` | method | `tests/test_doom_pwad.py:374` | `def test_reject_scales_with_sector_count(self)` |
| `test_roundtrip_check` | method | `tests/test_doom_pwad.py:85` | `def test_roundtrip_check(self)` |
| `test_swapped_lumps_die` | method | `tests/test_doom_pwad.py:198` | `def test_swapped_lumps_die(self)` |
| `test_things_pin` | method | `tests/test_doom_pwad.py:115` | `def test_things_pin(self)` |
| `test_truncated_file_dies` | method | `tests/test_doom_pwad.py:193` | `def test_truncated_file_dies(self)` |
| `test_unknown_special_dies` | method | `tests/test_doom_pwad.py:423` | `def test_unknown_special_dies(self)` |
| `test_unreachable_exit_refused` | method | `tests/test_doom_pwad.py:56` | `def test_unreachable_exit_refused(self)` |
| `test_unterminated_blockmap_dies` | method | `tests/test_doom_pwad.py:243` | `def test_unterminated_blockmap_dies(self)` |
| `test_valid_room_parses` | method | `tests/test_doom_pwad.py:32` | `def test_valid_room_parses(self)` |
| `test_wild_vertex_dies` | method | `tests/test_doom_pwad.py:221` | `def test_wild_vertex_dies(self)` |
| `main` | function | `tests/test_driver.c:65` | `int main(void)` |
| `test_pcm_open` | function | `tests/test_driver.c:28` | `static void test_pcm_open(device_t *d)` |
| `test_pcm_submit` | function | `tests/test_driver.c:33` | `static int test_pcm_submit(device_t *d, const unsigned char *pcm, unsigned len)` |
| `test_read` | function | `tests/test_driver.c:15` | `static int test_read(device_t *d, unsigned lba, unsigned count, void *buf)` |
| `test_tone` | function | `tests/test_driver.c:39` | `static void test_tone(device_t *d, unsigned freq)` |
| `CHECK` | macro | `tests/test_ext4.c:135` | `#define CHECK(cond)` |
| `EXT_FIX_BLOCKS` | macro | `tests/test_ext4.c:62` | `#define EXT_FIX_BLOCKS` |
| `EXT_FIX_SIZE` | macro | `tests/test_ext4.c:63` | `#define EXT_FIX_SIZE` |
| `block_disk_sectors` | function | `tests/test_ext4.c:119` | `unsigned long block_disk_sectors(void)` |
| `block_read_sectors` | function | `tests/test_ext4.c:123` | `int block_read_sectors(unsigned lba, unsigned count, void *buf)` |
| `e16` | function | `tests/test_ext4.c:143` | `static void e16(unsigned char *p, unsigned v)` |
| `e32` | function | `tests/test_ext4.c:148` | `static void e32(unsigned char *p, unsigned long v)` |
| `ext_fix_build` | function | `tests/test_ext4.c:192` | `static void ext_fix_build(void)` |
| `ext_fix_de` | function | `tests/test_ext4.c:156` | `static unsigned ext_fix_de(unsigned char *d, unsigned off, const char *nm,                       ...` |
| `ext_fix_inode` | function | `tests/test_ext4.c:168` | `static void ext_fix_inode(unsigned ino, unsigned mode, unsigned long size,                       ...` |
| `ext_fix_x1` | function | `tests/test_ext4.c:180` | `static void ext_fix_x1(unsigned char *iblk, unsigned l0, unsigned p0,                        unsi...` |
| `fs_resolve` | function | `tests/test_ext4.c:55` | `int fs_resolve(const char *path, char *out, unsigned cap)` |
| `ide_present` | function | `tests/test_ext4.c:104` | `int ide_present(void)` |
| `ide_read_sectors` | function | `tests/test_ext4.c:112` | `int ide_read_sectors(unsigned int lba, unsigned int count, void *buf)` |
| `ide_total_sectors` | function | `tests/test_ext4.c:108` | `unsigned int ide_total_sectors(void)` |
| `kfree` | function | `tests/test_ext4.c:28` | `void kfree(void *ptr)` |
| `kmalloc` | function | `tests/test_ext4.c:24` | `void *kmalloc(unsigned long size)` |
| `kmemcpy` | function | `tests/test_ext4.c:47` | `void *kmemcpy(void *dst, const void *src, unsigned long n)` |
| `kstrchr` | function | `tests/test_ext4.c:51` | `char *kstrchr(const char *s, int c)` |
| `kstrlen` | function | `tests/test_ext4.c:32` | `unsigned long kstrlen(const char *s)` |
| `kstrncmp` | function | `tests/test_ext4.c:36` | `int kstrncmp(const char *a, const char *b, unsigned long n)` |
| `kstrncpy` | function | `tests/test_ext4.c:40` | `char *kstrncpy(char *dst, const char *src, unsigned long n)` |
| `main` | function | `tests/test_ext4.c:421` | `int main(void)` |
| `minifs_is_mounted` | function | `tests/test_ext4.c:81` | `int minifs_is_mounted(void)` |
| `minifs_read` | function | `tests/test_ext4.c:96` | `int minifs_read(int ino, void *buf, unsigned off, unsigned len)` |
| `minifs_resolve_path` | function | `tests/test_ext4.c:85` | `int minifs_resolve_path(const char *path)` |
| `minifs_stat` | function | `tests/test_ext4.c:90` | `int minifs_stat(int ino, MiniFSInode *out)` |
| `ramdisk_open` | function | `tests/test_ext4.c:68` | `RDFile *ramdisk_open(const char *name)` |
| `ramdisk_read` | function | `tests/test_ext4.c:73` | `int ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len)` |
| `test_bad_magic` | function | `tests/test_ext4.c:412` | `static void test_bad_magic(void)` |
| `test_image` | function | `tests/test_ext4.c:305` | `static void test_image(void)` |
| `CHECK` | macro | `tests/test_fat32.c:137` | `#define CHECK(cond)` |
| `FAT_FIX_SECTORS` | macro | `tests/test_fat32.c:58` | `#define FAT_FIX_SECTORS` |
| `FAT_FIX_SIZE` | macro | `tests/test_fat32.c:59` | `#define FAT_FIX_SIZE` |
| `block_disk_sectors` | function | `tests/test_fat32.c:121` | `unsigned long block_disk_sectors(void)` |
| `block_read_sectors` | function | `tests/test_fat32.c:125` | `int block_read_sectors(unsigned lba, unsigned count, void *buf)` |
| `fat_fix_build` | function | `tests/test_fat32.c:157` | `static void fat_fix_build(void)` |
| `fs_resolve` | function | `tests/test_fat32.c:51` | `int fs_resolve(const char *path, char *out, unsigned cap)` |
| `ide_present` | function | `tests/test_fat32.c:102` | `int ide_present(void)` |
| `ide_read_sectors` | function | `tests/test_fat32.c:110` | `int ide_read_sectors(unsigned int lba, unsigned int count, void *buf)` |
| `ide_total_sectors` | function | `tests/test_fat32.c:106` | `unsigned int ide_total_sectors(void)` |
| `kfree` | function | `tests/test_fat32.c:28` | `void kfree(void *ptr)` |
| `kmalloc` | function | `tests/test_fat32.c:24` | `void *kmalloc(unsigned long size)` |
| `kmemcpy` | function | `tests/test_fat32.c:47` | `void *kmemcpy(void *dst, const void *src, unsigned long n)` |
| `kstrcmp` | function | `tests/test_fat32.c:117` | `int kstrcmp(const char *a, const char *b)` |
| `kstrlen` | function | `tests/test_fat32.c:32` | `unsigned long kstrlen(const char *s)` |
| `kstrncmp` | function | `tests/test_fat32.c:36` | `int kstrncmp(const char *a, const char *b, unsigned long n)` |
| `kstrncpy` | function | `tests/test_fat32.c:40` | `char *kstrncpy(char *dst, const char *src, unsigned long n)` |
| `main` | function | `tests/test_fat32.c:329` | `int main(void)` |
| `minifs_is_mounted` | function | `tests/test_fat32.c:79` | `int minifs_is_mounted(void)` |
| `minifs_read` | function | `tests/test_fat32.c:94` | `int minifs_read(int ino, void *buf, unsigned off, unsigned len)` |
| `minifs_resolve_path` | function | `tests/test_fat32.c:83` | `int minifs_resolve_path(const char *path)` |
| `minifs_stat` | function | `tests/test_fat32.c:88` | `int minifs_stat(int ino, MiniFSInode *out)` |
| `ramdisk_open` | function | `tests/test_fat32.c:66` | `RDFile *ramdisk_open(const char *name)` |
| `ramdisk_read` | function | `tests/test_fat32.c:71` | `int ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len)` |
| `st16` | function | `tests/test_fat32.c:145` | `static void st16(unsigned char *p, unsigned v)` |
| `st32` | function | `tests/test_fat32.c:150` | `static void st32(unsigned char *p, unsigned long v)` |
| `test_bad_magic` | function | `tests/test_fat32.c:320` | `static void test_bad_magic(void)` |
| `test_image` | function | `tests/test_fat32.c:258` | `static void test_image(void)` |
| `test_units` | function | `tests/test_fat32.c:236` | `static void test_units(void)` |
| `CHECK` | macro | `tests/test_fault.c:28` | `#define CHECK(c, m)` |
| `TRUSTED_DIR` | macro | `tests/test_fault.c:81` | `#define TRUSTED_DIR` |
| `TRUSTED_LEN` | macro | `tests/test_fault.c:82` | `#define TRUSTED_LEN` |
| `U_BASE` | macro | `tests/test_fault.c:31` | `#define U_BASE` |
| `U_END` | macro | `tests/test_fault.c:32` | `#define U_END` |
| `against` | function | `tests/test_fault.c:10` | `* after bounding against (END-BASE)/elemsz, so the product cannot * wrap past the range check);` |
| `main` | function | `tests/test_fault.c:94` | `int main(void)` |
| `normalize` | function | `tests/test_fault.c:52` | `static void normalize(const char *path, char *out, unsigned cap)` |
| `path_trusted` | function | `tests/test_fault.c:83` | `static int path_trusted(const char *full)` |
| `range_ok` | function | `tests/test_fault.c:35` | `static int range_ok(unsigned long p, unsigned long len)` |
| `str_ok` | function | `tests/test_fault.c:41` | `static int str_ok(const unsigned char *mem, unsigned long p,                   unsigned long maxlen)` |
| `CHECK` | macro | `tests/test_file_assoc.c:16` | `#define CHECK(cond, msg)` |
| `T_EXT_MAX` | macro | `tests/test_file_assoc.c:23` | `#define T_EXT_MAX` |
| `T_ICON_BIG` | macro | `tests/test_file_assoc.c:93` | `#define T_ICON_BIG` |
| `T_ICON_SMALL` | macro | `tests/test_file_assoc.c:92` | `#define T_ICON_SMALL` |
| `T_PROG_MAX` | macro | `tests/test_file_assoc.c:24` | `#define T_PROG_MAX` |
| `main` | function | `tests/test_file_assoc.c:99` | `int main(void)` |
| `t_assoc_line` | function | `tests/test_file_assoc.c:46` | `static int t_assoc_line(const char *line, char *ext, char *prog)` |
| `t_ext_of` | function | `tests/test_file_assoc.c:26` | `static void t_ext_of(const char *fname, char *dst, unsigned cap)` |
| `t_icon_kind` | function | `tests/test_file_assoc.c:80` | `static int t_icon_kind(const char *fname, int isdir)` |
| `t_icon_sz` | function | `tests/test_file_assoc.c:95` | `static int t_icon_sz(void)` |
| `FREEDOM_WL_HOST_TEST` | macro | `tests/test_freedom_wl.c:8` | `#define FREEDOM_WL_HOST_TEST` |
| `check_host` | function | `tests/test_freedom_wl.c:12` | `static int check_host(int cond, const char *name)` |
| `main` | function | `tests/test_freedom_wl.c:22` | `int main(void)` |
| `FREEDOMUI_HOST_TEST` | macro | `tests/test_freedomui.c:10` | `#define FREEDOMUI_HOST_TEST` |
| `main` | function | `tests/test_freedomui.c:24` | `int main(void)` |
| `CHECK` | macro | `tests/test_futex.c:32` | `#define CHECK(cond, msg)` |
| `fresh_all` | function | `tests/test_futex.c:48` | `static void fresh_all(void)` |
| `fresh_proc` | function | `tests/test_futex.c:39` | `static void fresh_proc(int pid)` |
| `main` | function | `tests/test_futex.c:60` | `int main(void)` |
| `proc_get` | function | `tests/test_futex.c:18` | `proc_t *proc_get(int pid)` |
| `schedule` | function | `tests/test_futex.c:26` | `void schedule(void)` |
| `CHECK` | macro | `tests/test_fx.c:16` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_fx.c:23` | `int main(void)` |
| `CHECK` | macro | `tests/test_hal_io.c:23` | `#define CHECK(cond, msg)` |
| `HAL_IO_HOST_TEST` | macro | `tests/test_hal_io.c:11` | `#define HAL_IO_HOST_TEST` |
| `main` | function | `tests/test_hal_io.c:30` | `int main(void)` |
| `CHECK` | macro | `tests/test_httpd.c:18` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_httpd.c:25` | `int main(void)` |
| `CHECK` | macro | `tests/test_ktime.c:14` | `#define CHECK(c, m)` |
| `main` | function | `tests/test_ktime.c:16` | `int main(void)` |
| `CHECK` | macro | `tests/test_ldso.c:20` | `#define CHECK(cond, msg)` |
| `DYN_OFF` | macro | `tests/test_ldso.c:54` | `#define DYN_OFF` |
| `HASH_OFF` | macro | `tests/test_ldso.c:57` | `#define HASH_OFF` |
| `IMG_SZ` | macro | `tests/test_ldso.c:53` | `#define IMG_SZ` |
| `RELA_OFF` | macro | `tests/test_ldso.c:58` | `#define RELA_OFF` |
| `STR_OFF` | macro | `tests/test_ldso.c:55` | `#define STR_OFF` |
| `SYM_OFF` | macro | `tests/test_ldso.c:56` | `#define SYM_OFF` |
| `build_tables` | function | `tests/test_ldso.c:92` | `static void build_tables(unsigned char *img, int rela_type)` |
| `main` | function | `tests/test_ldso.c:127` | `int main(void)` |
| `w16` | function | `tests/test_ldso.c:27` | `static void w16(unsigned char *p, unsigned v)` |
| `w32` | function | `tests/test_ldso.c:32` | `static void w32(unsigned char *p, unsigned long v)` |
| `w64` | function | `tests/test_ldso.c:39` | `static void w64(unsigned char *p, unsigned long long v)` |
| `CHECK` | macro | `tests/test_leakcheck.c:20` | `#define CHECK(cond, msg)` |
| `MINIOS_LEAKCHECK_IMPL` | macro | `tests/test_leakcheck.c:10` | `#define MINIOS_LEAKCHECK_IMPL` |
| `MINIOS_LK_ENABLE` | macro | `tests/test_leakcheck.c:11` | `#define MINIOS_LK_ENABLE` |
| `main` | function | `tests/test_leakcheck.c:27` | `int main(void)` |
| `CHECK` | macro | `tests/test_minios_png.c:16` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_minios_png.c:191` | `int main(void)` |
| `t_332` | function | `tests/test_minios_png.c:24` | `static void t_332(void)` |
| `t_blit` | function | `tests/test_minios_png.c:139` | `static void t_blit(void)` |
| `t_geom` | function | `tests/test_minios_png.c:58` | `static void t_geom(void)` |
| `t_load` | function | `tests/test_minios_png.c:157` | `static void t_load(void)` |
| `t_nearest` | function | `tests/test_minios_png.c:33` | `static void t_nearest(void)` |
| `t_policy` | function | `tests/test_minios_png.c:176` | `static void t_policy(void)` |
| `t_scale` | function | `tests/test_minios_png.c:70` | `static void t_scale(void)` |
| `t_scale_big` | function | `tests/test_minios_png.c:99` | `static void t_scale_big(void)` |
| `CHECK` | macro | `tests/test_modifiers.c:17` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_modifiers.c:24` | `int main(void)` |
| `CHECK` | macro | `tests/test_notify.c:9` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_notify.c:22` | `int main(void)` |
| `probe_handler` | function | `tests/test_notify.c:16` | `static void probe_handler(const wm_notify_event_t *e)` |
| `CHECK` | macro | `tests/test_paint.c:16` | `#define CHECK(cond, msg)` |
| `T_H` | macro | `tests/test_paint.c:24` | `#define T_H` |
| `T_N` | macro | `tests/test_paint.c:25` | `#define T_N` |
| `T_PATH_MAX` | macro | `tests/test_paint.c:26` | `#define T_PATH_MAX` |
| `T_W` | macro | `tests/test_paint.c:23` | `#define T_W` |
| `main` | function | `tests/test_paint.c:300` | `int main(void)` |
| `t_clamp` | function | `tests/test_paint.c:30` | `static int t_clamp(int v, int lo, int hi)` |
| `t_crc` | function | `tests/test_paint.c:129` | `static unsigned long t_crc(const unsigned char *p, unsigned long n)` |
| `t_crc_init` | function | `tests/test_paint.c:116` | `static void t_crc_init(void)` |
| `t_flood` | function | `tests/test_paint.c:70` | `static int t_flood(unsigned char *buf, int w, int h, int x, int y,                    unsigned ch...` |
| `t_line` | function | `tests/test_paint.c:44` | `static int t_line(unsigned char *buf, int w, int h, int x0, int y0, int x1,                   int...` |
| `t_nearest` | function | `tests/test_paint.c:155` | `static int t_nearest(const unsigned char *pal, unsigned r, unsigned g,                      unsig...` |
| `t_path_ok` | function | `tests/test_paint.c:138` | `static int t_path_ok(const char *p)` |
| `t_plot` | function | `tests/test_paint.c:36` | `static int t_plot(unsigned char *buf, int w, int h, int x, int y,                   unsigned char c)` |
| `test_flood` | function | `tests/test_paint.c:207` | `static void test_flood(void)` |
| `test_line` | function | `tests/test_paint.c:188` | `static void test_line(void)` |
| `test_nearest` | function | `tests/test_paint.c:287` | `static void test_nearest(void)` |
| `test_path` | function | `tests/test_paint.c:273` | `static void test_path(void)` |
| `test_plot` | function | `tests/test_paint.c:171` | `static void test_plot(void)` |
| `test_png_codec` | function | `tests/test_paint.c:228` | `static void test_png_codec(void)` |
| `test_png_layout` | function | `tests/test_paint.c:259` | `static void test_png_layout(void)` |
| `CHECK` | macro | `tests/test_panic.c:16` | `#define CHECK(cond, msg)` |
| `always_valid` | function | `tests/test_panic.c:23` | `static int always_valid(unsigned long addr)` |
| `deny_valid` | function | `tests/test_panic.c:35` | `static int deny_valid(unsigned long addr)` |
| `main` | function | `tests/test_panic.c:39` | `int main(void)` |
| `never_valid` | function | `tests/test_panic.c:28` | `static int never_valid(unsigned long addr)` |
| `CHECK` | macro | `tests/test_pcache.c:36` | `#define CHECK(cond, msg)` |
| `kfree` | function | `tests/test_pcache.c:23` | `void kfree(void *ptr)` |
| `kmalloc` | function | `tests/test_pcache.c:19` | `void *kmalloc(unsigned long size)` |
| `kprintf` | function | `tests/test_pcache.c:27` | `int kprintf(const char *fmt, ...)` |
| `main` | function | `tests/test_pcache.c:43` | `int main(void)` |
| `CHECK` | macro | `tests/test_pci.c:26` | `#define CHECK(cond, msg)` |
| `FAKE_BUSES` | macro | `tests/test_pci.c:33` | `#define FAKE_BUSES` |
| `FAKE_REGS` | macro | `tests/test_pci.c:34` | `#define FAKE_REGS` |
| `fake_inl` | function | `tests/test_pci.c:60` | `static unsigned fake_inl(unsigned short port)` |
| `fake_outl` | function | `tests/test_pci.c:39` | `static void fake_outl(unsigned short port, unsigned val)` |
| `main` | function | `tests/test_pci.c:79` | `int main(void)` |
| `set_dev` | function | `tests/test_pci.c:73` | `static void set_dev(unsigned bus, unsigned dev, unsigned func,                     unsigned id, u...` |
| `CHECK` | macro | `tests/test_pcm.c:21` | `#define CHECK(cond, msg)` |
| `lcg_next` | function | `tests/test_pcm.c:104` | `static unsigned lcg_next(void)` |
| `main` | function | `tests/test_pcm.c:144` | `int main(void)` |
| `t_model` | function | `tests/test_pcm.c:109` | `static void t_model(void)` |
| `t_overrun` | function | `tests/test_pcm.c:61` | `static void t_overrun(void)` |
| `t_roundtrip` | function | `tests/test_pcm.c:28` | `static void t_roundtrip(void)` |
| `t_underrun` | function | `tests/test_pcm.c:75` | `static void t_underrun(void)` |
| `t_wrap` | function | `tests/test_pcm.c:44` | `static void t_wrap(void)` |
| `t_zero_cap` | function | `tests/test_pcm.c:91` | `static void t_zero_cap(void)` |
| `CHECK` | macro | `tests/test_percpu_rq.c:17` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_percpu_rq.c:24` | `int main(void)` |
| `CHECK` | macro | `tests/test_pipe.c:16` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_pipe.c:23` | `int main(void)` |
| `CHECK` | macro | `tests/test_randmix.c:16` | `#define CHECK(c, m)` |
| `main` | function | `tests/test_randmix.c:24` | `int main(void)` |
| `popcount64` | function | `tests/test_randmix.c:18` | `static int popcount64(unsigned long x)` |
| `CHECK` | macro | `tests/test_rcu.c:30` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_rcu.c:37` | `int main(void)` |
| `rcu_host_cpu` | function | `tests/test_rcu.c:19` | `cpu_t *rcu_host_cpu(void)` |
| `test_cb` | function | `tests/test_rcu.c:23` | `static void test_cb(void *arg)` |
| `CHECK` | macro | `tests/test_rtc.c:16` | `#define CHECK(c, m)` |
| `main` | function | `tests/test_rtc.c:18` | `int main(void)` |
| `CHECK` | macro | `tests/test_sanitize.c:41` | `#define CHECK(cond, msg)` |
| `EFAULT` | macro | `tests/test_sanitize.c:13` | `#define EFAULT` |
| `copy_probe` | function | `tests/test_sanitize.c:61` | `static long copy_probe(unsigned long uptr, long count, unsigned long elemsz)` |
| `kmemcpy` | function | `tests/test_sanitize.c:32` | `void *kmemcpy(void *dst, const void *src, unsigned long n)` |
| `main` | function | `tests/test_sanitize.c:67` | `int main(void)` |
| `range_probe` | function | `tests/test_sanitize.c:48` | `static long range_probe(unsigned long p, long len)` |
| `str_probe` | function | `tests/test_sanitize.c:54` | `static long str_probe(unsigned long p)` |
| `user_range_ok` | function | `tests/test_sanitize.c:20` | `int user_range_ok(unsigned long p, unsigned long len)` |
| `user_str_ok` | function | `tests/test_sanitize.c:26` | `int user_str_ok(unsigned long p, unsigned long maxlen)` |
| `CHECK` | macro | `tests/test_sync.c:37` | `#define CHECK(cond, msg)` |
| `fresh_all` | function | `tests/test_sync.c:52` | `static void fresh_all(void)` |
| `fresh_proc` | function | `tests/test_sync.c:44` | `static void fresh_proc(int pid)` |
| `main` | function | `tests/test_sync.c:63` | `int main(void)` |
| `proc_get` | function | `tests/test_sync.c:24` | `proc_t *proc_get(int pid)` |
| `schedule` | function | `tests/test_sync.c:30` | `void schedule(void)` |
| `CHECK` | macro | `tests/test_theme.c:16` | `#define CHECK(cond, msg)` |
| `X` | macro | `tests/test_theme.c:29` | `#define X(k, i)` |
| `check_theme_file` | function | `tests/test_theme.c:78` | `static void check_theme_file(const char *path)` |
| `cube_exact` | function | `tests/test_theme.c:74` | `static int cube_exact(long v)` |
| `main` | function | `tests/test_theme.c:107` | `int main(void)` |
| `t_name_ok` | function | `tests/test_theme.c:34` | `static int t_name_ok(const char *name)` |
| `t_parse_line` | function | `tests/test_theme.c:46` | `static int t_parse_line(const char *line, int *idx, long v[3])` |
| `tslot` | struct | `tests/test_theme.c:23` | `` |
| `CHECK` | macro | `tests/test_tick.c:17` | `#define CHECK(cond, msg)` |
| `dummy` | function | `tests/test_tick.c:47` | `static void dummy(void *ctx)` |
| `main` | function | `tests/test_tick.c:52` | `int main(void)` |
| `rec_a` | function | `tests/test_tick.c:24` | `static void rec_a(void *ctx)` |
| `rec_b` | function | `tests/test_tick.c:31` | `static void rec_b(void *ctx)` |
| `rec_d` | function | `tests/test_tick.c:38` | `static void rec_d(void *ctx)` |
| `CHECK` | macro | `tests/test_usbblk.c:36` | `#define CHECK(cond, msg)` |
| `device_find` | function | `tests/test_usbblk.c:26` | `device_t *device_find(const char *name)` |
| `device_register` | function | `tests/test_usbblk.c:20` | `int device_register(device_t *dev)` |
| `main` | function | `tests/test_usbblk.c:43` | `int main(void)` |
| `CHECK` | macro | `tests/test_usbhid.c:41` | `#define CHECK(cond, msg)` |
| `check_usage` | function | `tests/test_usbhid.c:48` | `static void check_usage(unsigned usage, unsigned char want_sc, int want_e0,                      ...` |
| `kbd_feed_scancode` | function | `tests/test_usbhid.c:22` | `int kbd_feed_scancode(unsigned char sc)` |
| `kbd_q_push` | function | `tests/test_usbhid.c:30` | `void kbd_q_push(unsigned char c)` |
| `main` | function | `tests/test_usbhid.c:59` | `int main(void)` |
| `CHECK` | macro | `tests/test_vedit_build.c:33` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_vedit_build.c:345` | `int main(void)` |
| `t_base_of` | function | `tests/test_vedit_build.c:51` | `static int t_base_of(const char *fname, char *dst, size_t cap)` |
| `t_cmd` | function | `tests/test_vedit_build.c:299` | `static int t_cmd(const char *name)` |
| `t_has_ext` | function | `tests/test_vedit_build.c:40` | `static int t_has_ext(const char *fname, const char *ext)` |
| `t_join` | function | `tests/test_vedit_build.c:71` | `static int t_join(const char *dir, const char *base, const char *ext,                   char *dst...` |
| `t_lang_of` | function | `tests/test_vedit_build.c:101` | `static int t_lang_of(const char *fname)` |
| `t_link_fmt` | function | `tests/test_vedit_build.c:87` | `static int t_link_fmt(const char *s)` |
| `t_magic` | function | `tests/test_vedit_build.c:268` | `static int t_magic(const char *text, const char *pat, int *mlen)` |
| `t_matom` | function | `tests/test_vedit_build.c:188` | `static int t_matom(const char *pat, int c, int *atom_len)` |
| `t_mclass` | function | `tests/test_vedit_build.c:166` | `static int t_mclass(int c, const char *cls)` |
| `t_mhere` | function | `tests/test_vedit_build.c:211` | `static int t_mhere(const char *text, const char *pat, int *mlen)` |
| `t_parse_key` | function | `tests/test_vedit_build.c:312` | `static int t_parse_key(const char *s)` |
| `t_run_kind` | function | `tests/test_vedit_build.c:121` | `static int t_run_kind(const char *fname)` |
| `t_str_case` | function | `tests/test_vedit_build.c:131` | `static void t_str_case(char *s, int mode)` |
| `t_transpose` | function | `tests/test_vedit_build.c:157` | `static void t_transpose(char *s, int len, int pos)` |
| `CHECK` | macro | `tests/test_vma.c:20` | `#define CHECK(cond, msg)` |
| `black_height` | function | `tests/test_vma.c:27` | `static int black_height(const vma_node_t *n)` |
| `count_nodes` | function | `tests/test_vma.c:75` | `static int count_nodes(const vma_node_t *root)` |
| `main` | function | `tests/test_vma.c:199` | `int main(void)` |
| `test_file_tags_and_containing` | function | `tests/test_vma.c:167` | `static void test_file_tags_and_containing(void)` |
| `test_full_drain` | function | `tests/test_vma.c:153` | `static void test_full_drain(void)` |
| `test_insert_find_delete` | function | `tests/test_vma.c:89` | `static void test_insert_find_delete(void)` |
| `test_pool_exhaustion` | function | `tests/test_vma.c:136` | `static void test_pool_exhaustion(void)` |
| `tree_valid` | function | `tests/test_vma.c:38` | `static int tree_valid(const vma_node_t *root)` |
| `LIST_MAX` | macro | `tests/test_vma_bench.c:20` | `#define LIST_MAX` |
| `bench` | function | `tests/test_vma_bench.c:34` | `static void bench(int n)` |
| `l_find` | function | `tests/test_vma_bench.c:28` | `static int l_find(unsigned long b)` |
| `l_insert` | function | `tests/test_vma_bench.c:23` | `static void l_insert(unsigned long b)` |
| `main` | function | `tests/test_vma_bench.c:54` | `int main(void)` |
| `now_us` | function | `tests/test_vma_bench.c:13` | `static long now_us(void)` |
| `CHECK` | macro | `tests/test_wl.c:20` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_wl.c:27` | `int main(void)` |
| `CHECK` | macro | `tests/test_wm.c:22` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_wm.c:29` | `int main(void)` |
| `CHECK` | macro | `tests/test_xhci.c:23` | `#define CHECK(cond, msg)` |
| `main` | function | `tests/test_xhci.c:30` | `int main(void)` |
| `CHECK` | macro | `tls_test.c:62` | `#define CHECK(name, cond)` |
| `bytes_eq` | function | `tls_test.c:80` | `static int bytes_eq(const unsigned char *a, const unsigned char *b, int n)` |
| `hexdigit` | function | `tls_test.c:67` | `static int hexdigit(int c)` |
| `http_over_tls` | function | `tls_test.c:265` | `static int http_over_tls(int port, const char *host)` |
| `main` | function | `tls_test.c:349` | `int main(int argc, char **argv)` |
| `scenario_bad_ca` | function | `tls_test.c:329` | `static int scenario_bad_ca(int port)` |
| `scenario_bad_host` | function | `tls_test.c:319` | `static int scenario_bad_host(int port)` |
| `scenario_expired` | function | `tls_test.c:339` | `static int scenario_expired(int port)` |
| `scenario_good` | function | `tls_test.c:290` | `static int scenario_good(int port)` |
| `scenario_wild_deep` | function | `tls_test.c:309` | `static int scenario_wild_deep(int port)` |
| `scenario_wild_good` | function | `tls_test.c:295` | `static int scenario_wild_good(int port)` |
| `scenario_wild_root` | function | `tls_test.c:299` | `static int scenario_wild_root(int port)` |
| `tcp_connect` | function | `tls_test.c:249` | `static int tcp_connect(int port)` |
| `test_gcm` | function | `tls_test.c:114` | `static void test_gcm(void)` |
| `test_p256` | function | `tls_test.c:154` | `static void test_p256(void)` |
| `test_rsa_ecdsa_vectors` | function | `tls_test.c:200` | `static void test_rsa_ecdsa_vectors(void)` |
| `test_sha256` | function | `tls_test.c:88` | `static void test_sha256(void)` |
| `test_sha384` | function | `tls_test.c:103` | `static void test_sha384(void)` |
| `tls_test_close` | function | `tls_test.c:54` | `void tls_test_close(int fd)` |
| `tls_test_recv` | function | `tls_test.c:36` | `int tls_test_recv(int fd, char *buf, int len)` |
| `tls_test_recv_timeout` | function | `tls_test.c:41` | `int tls_test_recv_timeout(int fd, char *buf, int len, unsigned long ms)` |
| `tls_test_send` | function | `tls_test.c:26` | `int tls_test_send(int fd, const char *buf, int len)` |
| `unhex` | function | `tls_test.c:74` | `static void unhex(const char *hex, unsigned char *out, int n)` |
| `main` | function | `tools/abi_stamp.c:14` | `int main(void)` |
| `WlBoot` | class | `tools/boot_wl.py:67` | `class WlBoot` |
| `WlBootConfig` | class | `tools/boot_wl.py:40` | `class WlBootConfig` |
| `__init__` | method | `tools/boot_wl.py:68` | `def __init__(self, cfg)` |
| `boot` | method | `tools/boot_wl.py:91` | `def boot(self)` |
| `close` | method | `tools/boot_wl.py:80` | `def close(self)` |
| `fail` | method | `tools/boot_wl.py:75` | `def fail(self, msg)` |
| `headless` | method | `tools/boot_wl.py:182` | `def headless(self)` |
| `main` | method | `tools/boot_wl.py:226` | `def main()` |
| `proxy` | method | `tools/boot_wl.py:195` | `def proxy(self)` |
| `qmp` | method | `tools/boot_wl.py:165` | `def qmp(self, obj)` |
| `send` | method | `tools/boot_wl.py:135` | `def send(self, line)` |
| `send_wait` | method | `tools/boot_wl.py:142` | `def send_wait(self, line, timeout)` |
| `setup` | method | `tools/boot_wl.py:154` | `def setup(self)` |
| `snapshot` | method | `tools/boot_wl.py:107` | `def snapshot(self, timeout)` |
| `wait_prompt` | method | `tools/boot_wl.py:124` | `def wait_prompt(self)` |
| `main` | function | `tools/check_abi_numbers.py:156` | `def main()` |
| `normalize` | function | `tools/check_abi_numbers.py:128` | `def normalize(minios_name)` |
| `parse_abi` | function | `tools/check_abi_numbers.py:132` | `def parse_abi(path)` |
| `parse_dispatch` | function | `tools/check_abi_numbers.py:143` | `def parse_dispatch(path)` |
| `load_parser` | function | `tools/check_addons.py:22` | `def load_parser()` |
| `main` | function | `tools/check_addons.py:31` | `def main()` |
| `compute_cohesion` | function | `tools/check_cohesion.py:31` | `def compute_cohesion(community_nodes, community_edges)` |
| `extract_communities` | function | `tools/check_cohesion.py:42` | `def extract_communities(cpg)` |
| `load_cpg` | function | `tools/check_cohesion.py:23` | `def load_cpg(path)` |
| `main` | function | `tools/check_cohesion.py:58` | `def main()` |
| `count_symbols` | function | `tools/check_complexity.py:24` | `def count_symbols(filepath)` |
| `load_approval` | function | `tools/check_complexity.py:46` | `def load_approval(policy_path)` |
| `main` | function | `tools/check_complexity.py:61` | `def main()` |
| `Config` | class | `tools/check_fork_stubs.py:18` | `class Config` |
| `check_stubs` | method | `tools/check_fork_stubs.py:37` | `def check_stubs(text, cfg)` |
| `handler_body` | method | `tools/check_fork_stubs.py:27` | `def handler_body(text, name)` |
| `main` | method | `tools/check_fork_stubs.py:52` | `def main()` |
| `main` | function | `tools/check_kb_sync.py:43` | `def main()` |
| `regenerate_kb` | function | `tools/check_kb_sync.py:24` | `def regenerate_kb()` |
| `Config` | class | `tools/check_mutant_anchors.py:17` | `class Config` |
| `anchor_matches` | method | `tools/check_mutant_anchors.py:67` | `def anchor_matches(repo, target, expr)` |
| `bash_unquote` | method | `tools/check_mutant_anchors.py:26` | `def bash_unquote(expr)` |
| `main` | method | `tools/check_mutant_anchors.py:86` | `def main()` |
| `parse_mutations` | method | `tools/check_mutant_anchors.py:41` | `def parse_mutations(text)` |
| `Config` | class | `tools/check_spin_discipline.py:23` | `class Config` |
| `check_file` | method | `tools/check_spin_discipline.py:64` | `def check_file(path)` |
| `iter_functions` | method | `tools/check_spin_discipline.py:38` | `def iter_functions(path)` |
| `main` | method | `tools/check_spin_discipline.py:99` | `def main(argv)` |
| `bfs_min_hops` | function | `tools/check_surprising.py:56` | `def bfs_min_hops(nodes, edges, source, target_community, max_hops)` |
| `build_graph` | function | `tools/check_surprising.py:33` | `def build_graph(cpg)` |
| `find_surprising_connections` | function | `tools/check_surprising.py:87` | `def find_surprising_connections(nodes, edges, min_hops)` |
| `load_cpg` | function | `tools/check_surprising.py:25` | `def load_cpg(path)` |
| `main` | function | `tools/check_surprising.py:118` | `def main()` |
| `Config` | class | `tools/check_syscall_sanitize.py:18` | `class Config` |
| `audit_body` | method | `tools/check_syscall_sanitize.py:162` | `def audit_body(name, body)` |
| `audit_file` | method | `tools/check_syscall_sanitize.py:217` | `def audit_file(path)` |
| `checked_names` | method | `tools/check_syscall_sanitize.py:112` | `def checked_names(body)` |
| `delegated_only` | method | `tools/check_syscall_sanitize.py:122` | `def delegated_only(body, alias)` |
| `main` | method | `tools/check_syscall_sanitize.py:228` | `def main()` |
| `split_functions` | method | `tools/check_syscall_sanitize.py:69` | `def split_functions(lines)` |
| `split_top_args` | method | `tools/check_syscall_sanitize.py:143` | `def split_top_args(argtext)` |
| `ClipBridgeConfig` | class | `tools/clip_bridge.py:30` | `class ClipBridgeConfig` |
| `build_plan` | method | `tools/clip_bridge.py:59` | `def build_plan(text, dst, cfg)` |
| `main` | method | `tools/clip_bridge.py:84` | `def main(argv)` |
| `printable_line` | method | `tools/clip_bridge.py:52` | `def printable_line(line, cfg)` |
| `valid_dst` | method | `tools/clip_bridge.py:41` | `def valid_dst(name, cfg)` |
| `DoomPwadConfig` | class | `tools/doom_pwad.py:52` | `class DoomPwadConfig` |
| `PwadError` | class | `tools/doom_pwad.py:161` | `class PwadError(Exception)` |
| `build_lumps` | method | `tools/doom_pwad.py:516` | `def build_lumps(rows)` |
| `build_pwad` | method | `tools/doom_pwad.py:597` | `def build_pwad(rows)` |
| `cell_class` | method | `tools/doom_pwad.py:279` | `def cell_class(cell)` |
| `cell_corners` | method | `tools/doom_pwad.py:269` | `def cell_corners(row, col)` |
| `check_multiple` | method | `tools/doom_pwad.py:655` | `def check_multiple(name, fmt)` |
| `check_pwad` | method | `tools/doom_pwad.py:639` | `def check_pwad(data)` |
| `cmd_build` | method | `tools/doom_pwad.py:816` | `def cmd_build(grid_path, out_path)` |
| `cmd_check` | method | `tools/doom_pwad.py:826` | `def cmd_check(path)` |
| `compile_geometry` | method | `tools/doom_pwad.py:371` | `def compile_geometry(rows, exit_pos, wall_side)` |
| `compile_things` | method | `tools/doom_pwad.py:485` | `def compile_things(rows)` |
| `flood_reachable` | method | `tools/doom_pwad.py:210` | `def flood_reachable(rows)` |
| `grid_extents` | method | `tools/doom_pwad.py:195` | `def grid_extents(rows)` |
| `is_wall` | method | `tools/doom_pwad.py:203` | `def is_wall(rows, row, col)` |
| `label_regions` | method | `tools/doom_pwad.py:291` | `def label_regions(rows)` |
| `main` | method | `tools/doom_pwad.py:834` | `def main(argv)` |
| `pad_tex` | method | `tools/doom_pwad.py:165` | `def pad_tex(raw)` |
| `parse_grid` | method | `tools/doom_pwad.py:172` | `def parse_grid(text)` |
| `payload` | method | `tools/doom_pwad.py:650` | `def payload(name)` |
| `read_pwad` | method | `tools/doom_pwad.py:616` | `def read_pwad(data)` |
| `region_sector` | method | `tools/doom_pwad.py:326` | `def region_sector(region, door_tag)` |
| `seg_angle` | method | `tools/doom_pwad.py:506` | `def seg_angle(dx, dy)` |
| `validate_grid` | method | `tools/doom_pwad.py:240` | `def validate_grid(rows)` |
| `vertex` | method | `tools/doom_pwad.py:386` | `def vertex(x, y)` |
| `main` | function | `tools/gdb_repro.py:27` | `def main()` |
| `quit_doom` | function | `tools/gdb_repro.py:70` | `def quit_doom()` |
| `rs` | function | `tools/gdb_repro.py:23` | `def rs(m, t)` |
| `send` | function | `tools/gdb_repro.py:65` | `def send(line)` |
| `main` | function | `tools/gen_desktop_pngs.py:75` | `def main()` |
| `write_atomic` | function | `tools/gen_desktop_pngs.py:69` | `def write_atomic(img, path)` |
| `main` | function | `tools/gen_icons.py:214` | `def main()` |
| `make_chunk` | function | `tools/gen_icons.py:209` | `def make_chunk(chunk_type, data)` |
| `make_png` | function | `tools/gen_icons.py:179` | `def make_png(pixels, palette, width, height)` |
| `main` | function | `tools/gen_zip_fixtures.py:42` | `def main()` |
| `write_zip` | function | `tools/gen_zip_fixtures.py:28` | `def write_zip(path, entries)` |
| `SurveyConfig` | class | `tools/kernel_feature_survey.py:18` | `class SurveyConfig` |
| `count_params` | method | `tools/kernel_feature_survey.py:59` | `def count_params(params)` |
| `find_asm_constraints` | method | `tools/kernel_feature_survey.py:49` | `def find_asm_constraints(path, text)` |
| `find_fnptr_hits` | method | `tools/kernel_feature_survey.py:43` | `def find_fnptr_hits(path, text)` |
| `iter_sources` | method | `tools/kernel_feature_survey.py:34` | `def iter_sources(root)` |
| `main` | method | `tools/kernel_feature_survey.py:122` | `def main(argv)` |
| `render_text` | method | `tools/kernel_feature_survey.py:103` | `def render_text(findings)` |
| `survey` | method | `tools/kernel_feature_survey.py:67` | `def survey(root)` |
| `die` | function | `tools/lisp_scoped.sh:9` | `` |
| `lisp_mut` | function | `tools/lisp_scoped.sh:41` | `` |
| `mut_usage` | function | `tools/lisp_scoped.sh:63` | `` |
| `mutant` | function | `tools/lisp_scoped.sh:20` | `` |
| `say` | function | `tools/lisp_scoped.sh:8` | `` |
| `usage` | function | `tools/make_usb.sh:40` | `` |
| `wizard` | function | `tools/make_usb.sh:56` | `` |
| `FS` | class | `tools/minifs_dump.py:25` | `class FS` |
| `__init__` | method | `tools/minifs_dump.py:26` | `def __init__(self, fn)` |
| `_sb` | method | `tools/minifs_dump.py:30` | `def _sb(self)` |
| `blk` | method | `tools/minifs_dump.py:29` | `def blk(self, n)` |
| `inode` | method | `tools/minifs_dump.py:38` | `def inode(self, i)` |
| `ls` | method | `tools/minifs_dump.py:86` | `def ls(self, ino, prefix)` |
| `main` | method | `tools/minifs_dump.py:105` | `def main()` |
| `mode_str` | function | `tools/minifs_dump.py:16` | `def mode_str(m)` |
| `read` | method | `tools/minifs_dump.py:47` | `def read(self, ino)` |
| `resolve` | method | `tools/minifs_dump.py:67` | `def resolve(self, path)` |
| `u16` | function | `tools/minifs_dump.py:13` | `def u16(d, o)` |
| `u32` | function | `tools/minifs_dump.py:14` | `def u32(d, o)` |
| `FSCK` | class | `tools/minifs_fsck.py:23` | `class FSCK` |
| `__init__` | method | `tools/minifs_fsck.py:24` | `def __init__(self, fn)` |
| `_find_base` | method | `tools/minifs_fsck.py:31` | `def _find_base(self)` |
| `_sb` | method | `tools/minifs_fsck.py:52` | `def _sb(self)` |
| `blk` | method | `tools/minifs_fsck.py:49` | `def blk(self, n)` |
| `crc32` | function | `tools/minifs_fsck.py:15` | `def crc32(data)` |
| `err` | method | `tools/minifs_fsck.py:86` | `def err(self, msg)` |

Next: [SYMBOLS_p24.md](SYMBOLS_p24.md)
