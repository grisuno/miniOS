# Symbols (page 24 of 26)
Previous: [SYMBOLS_p23.md](SYMBOLS_p23.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `wlclient_pat_t` | struct | `progs/wl/wlcomp.c:995` | `` |
| `wlcomp_cfg_t` | struct | `progs/wl/wlcomp.c:43` | `` |
| `wlcomp_clean` | function | `progs/wl/wlcomp.c:1137` | `static int wlcomp_clean(void)` |
| `wlcomp_client` | function | `progs/wl/wlcomp.c:1034` | `static int wlcomp_client(const char *box, const char *pat)` |
| `wlcomp_demo` | function | `progs/wl/wlcomp.c:189` | `static int wlcomp_demo(wl_comp_t *c)` |
| `wlcomp_demo_blit` | function | `progs/wl/wlcomp.c:214` | `static int wlcomp_demo_blit(wl_comp_t *c, unsigned char *fb)` |
| `wlcomp_emit` | function | `progs/wl/wlcomp.c:260` | `static int wlcomp_emit(unsigned char *s, int cap, int o, unsigned int id,         unsigned int op...` |
| `wlcomp_once` | function | `progs/wl/wlcomp.c:1165` | `static int wlcomp_once(void)` |
| `wlcomp_palette` | function | `progs/wl/wlcomp.c:139` | `static int wlcomp_palette(void)` |
| `wlcomp_path` | function | `progs/wl/wlcomp.c:1103` | `static int wlcomp_path(char *dst, int cap, const char *name)` |
| `wlcomp_pattern` | function | `progs/wl/wlcomp.c:150` | `static void wlcomp_pattern(unsigned char *dst, int w, int h,         unsigned char a, unsigned ch...` |
| `wlcomp_selftest` | function | `progs/wl/wlcomp.c:345` | `static int wlcomp_selftest(void)` |
| `wlcomp_server` | function | `progs/wl/wlcomp.c:1197` | `static int wlcomp_server(void)` |
| `wlcomp_session` | function | `progs/wl/wlcomp.c:272` | `static int wlcomp_session(wl_comp_t *c, wl_client_t *cl)` |
| `wlcomp_sys_dir_list` | function | `progs/wl/wlcomp.c:129` | `static long wlcomp_sys_dir_list(const char *path, char *buf, long cap)` |
| `wlcomp_sys_kbd` | function | `progs/wl/wlcomp.c:97` | `static long wlcomp_sys_kbd(void)` |
| `wlcomp_sys_kbd_raw` | function | `progs/wl/wlcomp.c:105` | `static long wlcomp_sys_kbd_raw(long on)` |
| `wlcomp_sys_mouse` | function | `progs/wl/wlcomp.c:89` | `static long wlcomp_sys_mouse(int *m)` |
| `wlcomp_sys_palette` | function | `progs/wl/wlcomp.c:81` | `static long wlcomp_sys_palette(unsigned char *pal)` |
| `wlcomp_sys_present` | function | `progs/wl/wlcomp.c:65` | `static long wlcomp_sys_present(long buf)` |
| `wlcomp_sys_present_origin` | function | `progs/wl/wlcomp.c:73` | `static long wlcomp_sys_present_origin(long buf, int *origin)` |
| `wlcomp_sys_title` | function | `progs/wl/wlcomp.c:57` | `static long wlcomp_sys_title(const char *t)` |
| `wlcomp_sys_vga_mode` | function | `progs/wl/wlcomp.c:113` | `static long wlcomp_sys_vga_mode(long on)` |
| `wlcomp_sys_yield` | function | `progs/wl/wlcomp.c:121` | `static long wlcomp_sys_yield(void)` |
| `wlserv_box_known` | function | `progs/wl/wlcomp.c:830` | `static int wlserv_box_known(const wlserv_t *s, const char *box)` |
| `wlserv_clean_ev` | function | `progs/wl/wlcomp.c:765` | `static void wlserv_clean_ev(void)` |
| `wlserv_close` | function | `progs/wl/wlcomp.c:798` | `static int wlserv_close(wlserv_t *s, unsigned int id)` |
| `wlserv_drain` | function | `progs/wl/wlcomp.c:933` | `static int wlserv_drain(wlserv_t *s)` |
| `wlserv_ev_clear` | function | `progs/wl/wlcomp.c:706` | `static void wlserv_ev_clear(wlserv_t *s, int b)` |
| `wlserv_fit` | function | `progs/wl/wlcomp.c:547` | `static void wlserv_fit(wlserv_t *s)` |
| `wlserv_focus_box` | function | `progs/wl/wlcomp.c:664` | `static int wlserv_focus_box(const wlserv_t *s)` |
| `wlserv_gc_strays` | function | `progs/wl/wlcomp.c:609` | `static void wlserv_gc_strays(void)` |
| `wlserv_init` | function | `progs/wl/wlcomp.c:418` | `static void wlserv_init(wlserv_t *s)` |
| `wlserv_key` | function | `progs/wl/wlcomp.c:686` | `static void wlserv_key(wlserv_t *s, unsigned char byte)` |
| `wlserv_load_raw` | function | `progs/wl/wlcomp.c:502` | `static int wlserv_load_raw(wlserv_t *s, int b, int idx)` |
| `wlserv_present` | function | `progs/wl/wlcomp.c:467` | `static int wlserv_present(wlserv_t *s)` |
| `wlserv_push_ev` | function | `progs/wl/wlcomp.c:717` | `static void wlserv_push_ev(wlserv_t *s, int fx, int fy, int buttons)` |
| `wlserv_recolor` | function | `progs/wl/wlcomp.c:450` | `static void wlserv_recolor(wl_comp_t *c)` |
| `wlserv_relayout_present` | function | `progs/wl/wlcomp.c:1123` | `static int wlserv_relayout_present(wlserv_t *s)` |
| `wlserv_slot` | function | `progs/wl/wlcomp.c:437` | `static int wlserv_slot(const wl_comp_t *c, unsigned int id)` |
| `wlserv_t` | struct | `progs/wl/wlcomp.c:406` | `` |
| `channel` | function | `qga.c:10` | `* * Polled channel (no interrupt controller): qga_init sets up COM2 and * qga_poll, called from raw_blocking_getc...` |
| `qga_b64_encode` | function | `qga.c:231` | `static void qga_b64_encode(const unsigned char *in, int n)` |
| `qga_cmd_exec` | function | `qga.c:306` | `static void qga_cmd_exec(const struct qga_pair *pairs, int n)` |
| `qga_cmd_file_close` | function | `qga.c:384` | `static void qga_cmd_file_close(const struct qga_pair *pairs, int n)` |
| `qga_cmd_file_open` | function | `qga.c:334` | `static void qga_cmd_file_open(const struct qga_pair *pairs, int n)` |
| `qga_cmd_file_read` | function | `qga.c:360` | `static void qga_cmd_file_read(const struct qga_pair *pairs, int n)` |
| `qga_cmd_get_time` | function | `qga.c:281` | `static void qga_cmd_get_time(void)` |
| `qga_cmd_shutdown` | function | `qga.c:316` | `static void qga_cmd_shutdown(const struct qga_pair *pairs, int n)` |
| `qga_dispatch` | function | `qga.c:401` | `static void qga_dispatch(struct qga_pair *pairs, int n)` |
| `qga_err` | function | `qga.c:210` | `static void qga_err(const char *klass, const char *desc)` |
| `qga_file_size` | function | `qga.c:329` | `static int qga_file_size(const KFILE *f)` |
| `qga_get_int` | function | `qga.c:166` | `static int qga_get_int(const struct qga_pair *pairs, int n, const char *key, long *out)` |
| `qga_get_str` | function | `qga.c:158` | `static const char *qga_get_str(const struct qga_pair *pairs, int n, const char *key)` |
| `qga_init` | function | `qga.c:35` | `void qga_init(void)` |
| `qga_pair` | struct | `qga.c:49` | `` |
| `qga_parse_flat` | function | `qga.c:147` | `static int qga_parse_flat(const char *s, struct qga_pair *out, int max)` |
| `qga_parse_object` | function | `qga.c:65` | `static int qga_parse_object(const char **pp, struct qga_pair *out, int max,                      ...` |
| `qga_poll` | function | `qga.c:446` | `void qga_poll(void)` |
| `qga_putc` | function | `qga.c:30` | `static void qga_putc(char c)` |
| `qga_puts_resp` | function | `qga.c:218` | `static void qga_puts_resp(void)` |
| `qga_resp_put_long` | function | `qga.c:201` | `static void qga_resp_put_long(long v)` |
| `qga_resp_putc_enc` | function | `qga.c:194` | `static void qga_resp_putc_enc(char c)` |
| `qga_resp_puts` | function | `qga.c:186` | `static void qga_resp_puts(const char *s)` |
| `qga_resp_reset` | function | `qga.c:184` | `static void qga_resp_reset(void)` |
| `qga_rx_ready` | function | `qga.c:28` | `static int qga_rx_ready(void)` |
| `qga_tx_ready` | function | `qga.c:27` | `static int qga_tx_ready(void)` |
| `qga_ws` | function | `qga.c:56` | `static int qga_ws(char c)` |
| `BSP` | function | `smp.c:238` | `* were programmed only on the BSP (syscall_init runs in kmain), so * an AP's first sysretq loaded SS from a zeroed...` |
| `INIT` | function | `smp.c:332` | `* INIT (edge-triggered): resets APs to wait-for-SIPI state. * QEMU 11 drops level-triggered INIT (delivery status...` |
| `LAPIC_BASE` | macro | `smp.c:28` | `#define LAPIC_BASE` |
| `LAPIC_EOI_OFF` | macro | `smp.c:38` | `#define LAPIC_EOI_OFF` |
| `LAPIC_ICR_ALL_EXC` | macro | `smp.c:47` | `#define LAPIC_ICR_ALL_EXC` |
| `LAPIC_ICR_BUSY` | macro | `smp.c:44` | `#define LAPIC_ICR_BUSY` |
| `LAPIC_ICR_HI` | macro | `smp.c:31` | `#define LAPIC_ICR_HI` |
| `LAPIC_ICR_INIT` | macro | `smp.c:45` | `#define LAPIC_ICR_INIT` |
| `LAPIC_ICR_LEVEL` | macro | `smp.c:48` | `#define LAPIC_ICR_LEVEL` |
| `LAPIC_ICR_LO` | macro | `smp.c:32` | `#define LAPIC_ICR_LO` |
| `LAPIC_ICR_SIPI` | macro | `smp.c:46` | `#define LAPIC_ICR_SIPI` |
| `LAPIC_ICR_TRIGGER` | macro | `smp.c:49` | `#define LAPIC_ICR_TRIGGER` |
| `LAPIC_ID_OFF` | macro | `smp.c:29` | `#define LAPIC_ID_OFF` |
| `LAPIC_LVT_EXTINT` | macro | `smp.c:37` | `#define LAPIC_LVT_EXTINT` |
| `LAPIC_LVT_LINT0` | macro | `smp.c:34` | `#define LAPIC_LVT_LINT0` |
| `LAPIC_LVT_LINT1` | macro | `smp.c:35` | `#define LAPIC_LVT_LINT1` |
| `LAPIC_LVT_MASKED` | macro | `smp.c:36` | `#define LAPIC_LVT_MASKED` |
| `LAPIC_LVT_TIMER` | macro | `smp.c:33` | `#define LAPIC_LVT_TIMER` |
| `LAPIC_PDPT_SLOT` | macro | `smp.c:67` | `#define LAPIC_PDPT_SLOT` |
| `LAPIC_PD_ADDR` | macro | `smp.c:66` | `#define LAPIC_PD_ADDR` |
| `LAPIC_PD_IDX` | macro | `smp.c:68` | `#define LAPIC_PD_IDX` |
| `LAPIC_SVR_ENABLE` | macro | `smp.c:43` | `#define LAPIC_SVR_ENABLE` |
| `LAPIC_SVR_OFF` | macro | `smp.c:30` | `#define LAPIC_SVR_OFF` |
| `LAPIC_TIMER_CUR` | macro | `smp.c:41` | `#define LAPIC_TIMER_CUR` |
| `LAPIC_TIMER_DIV` | macro | `smp.c:39` | `#define LAPIC_TIMER_DIV` |
| `LAPIC_TIMER_DIVIDE_16` | macro | `smp.c:57` | `#define LAPIC_TIMER_DIVIDE_16` |
| `LAPIC_TIMER_INIT` | macro | `smp.c:40` | `#define LAPIC_TIMER_INIT` |
| `LAPIC_TIMER_PERIODIC` | macro | `smp.c:58` | `#define LAPIC_TIMER_PERIODIC` |
| `PIT_HZ` | macro | `smp.c:54` | `#define PIT_HZ` |
| `SIPI_VECTOR` | macro | `smp.c:51` | `#define SIPI_VECTOR` |
| `ap_delay` | function | `smp.c:121` | `static void ap_delay(void)` |
| `ap_lapic_timer_init` | function | `smp.c:190` | `static void ap_lapic_timer_init(void)` |
| `ap_lapic_timer_start` | function | `smp.c:184` | `static void ap_lapic_timer_start(void)` |
| `lapic_calibrate` | function | `smp.c:150` | `static void lapic_calibrate(void)` |
| `lapic_read` | function | `smp.c:84` | `static unsigned lapic_read(unsigned off)` |
| `lapic_write` | function | `smp.c:87` | `static void lapic_write(unsigned off, unsigned val)` |
| `map_lapic` | function | `smp.c:108` | `static int map_lapic(void)` |
| `smp_init` | function | `smp.c:314` | `void smp_init(void)` |
| `syscall_entry` | function | `smp.c:82` | `extern void syscall_entry(void);` |
| `bad` | function | `tests/host_aes.sh:24` | `` |
| `ok` | function | `tests/host_aes.sh:23` | `` |
| `rd` | function | `tests/host_aes.sh:25` | `` |
| `bad` | function | `tests/host_codecs.sh:23` | `` |
| `gen_input` | function | `tests/host_codecs.sh:27` | `` |
| `ok` | function | `tests/host_codecs.sh:22` | `` |
| `reject` | function | `tests/host_codecs.sh:40` | `` |
| `roundtrip` | function | `tests/host_codecs.sh:31` | `` |
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
| `masked` | function | `tests/test_futex.c:153` | `* with PRIVATE and CLOCK_REALTIME masked (393 = 9\|128\|256). */ CHECK(futex_linux_cmd(9) == LINUX_FUTEX_WAIT_BITSET...` |
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
| `Config` | class | `tests/test_minifs_tools.py:23` | `class Config` |
| `MiniFSToolsTest` | class | `tests/test_minifs_tools.py:40` | `class MiniFSToolsTest(TestCase)` |
| `mkfs` | method | `tests/test_minifs_tools.py:58` | `def mkfs(self)` |
| `run` | method | `tests/test_minifs_tools.py:35` | `def run(args)` |
| `setUp` | method | `tests/test_minifs_tools.py:43` | `def setUp(self)` |
| `superblock_word` | method | `tests/test_minifs_tools.py:64` | `def superblock_word(self, image, off)` |
| `tearDown` | method | `tests/test_minifs_tools.py:47` | `def tearDown(self)` |
| `test_counters_match_bitmaps` | method | `tests/test_minifs_tools.py:69` | `def test_counters_match_bitmaps(self)` |
| `test_duplicate_file_is_an_error` | method | `tests/test_minifs_tools.py:107` | `def test_duplicate_file_is_an_error(self)` |
| `test_fsck_rejects_drifted_counters` | method | `tests/test_minifs_tools.py:79` | `def test_fsck_rejects_drifted_counters(self)` |
| `test_same_named_directories_merge` | method | `tests/test_minifs_tools.py:93` | `def test_same_named_directories_merge(self)` |
| `tree` | method | `tests/test_minifs_tools.py:50` | `def tree(self, root, rel, data)` |
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
| `check` | function | `tests/test_ps2_keymap.c:19` | `static void check(int cond, const char *name)` |
| `feed_seq` | function | `tests/test_ps2_keymap.c:29` | `static int feed_seq(ps2_state *s, const unsigned char *seq, int n, ps2_key *out)` |
| `main` | function | `tests/test_ps2_keymap.c:293` | `int main(void)` |
| `press` | function | `tests/test_ps2_keymap.c:36` | `static int press(ps2_state *s, unsigned char code, ps2_key *out)` |
| `release` | function | `tests/test_ps2_keymap.c:41` | `static int release(ps2_state *s, unsigned char code, ps2_key *out)` |
| `test_caps_lock` | function | `tests/test_ps2_keymap.c:69` | `static void test_caps_lock(void)` |
| `test_chords_have_no_text` | function | `tests/test_ps2_keymap.c:128` | `static void test_chords_have_no_text(void)` |
| `test_control_key_text` | function | `tests/test_ps2_keymap.c:111` | `static void test_control_key_text(void)` |
| `test_extended_keys` | function | `tests/test_ps2_keymap.c:150` | `static void test_extended_keys(void)` |
| `test_fail_closed` | function | `tests/test_ps2_keymap.c:280` | `static void test_fail_closed(void)` |
| `test_function_keys` | function | `tests/test_ps2_keymap.c:202` | `static void test_function_keys(void)` |
| `test_keypad_num_lock` | function | `tests/test_ps2_keymap.c:218` | `static void test_keypad_num_lock(void)` |
| `test_letters_and_shift` | function | `tests/test_ps2_keymap.c:45` | `static void test_letters_and_shift(void)` |
| `test_prefix_sequences` | function | `tests/test_ps2_keymap.c:263` | `static void test_prefix_sequences(void)` |
| `test_punctuation` | function | `tests/test_ps2_keymap.c:90` | `static void test_punctuation(void)` |
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
| `ARGS2_OFF` | macro | `tests/test_seccomp_bpf.c:30` | `#define ARGS2_OFF` |
| `CHECK` | macro | `tests/test_seccomp_bpf.c:17` | `#define CHECK(cond, msg)` |
| `JUMP` | macro | `tests/test_seccomp_bpf.c:22` | `#define JUMP(c, k, t, f)` |
| `NR_MMAP` | macro | `tests/test_seccomp_bpf.c:27` | `#define NR_MMAP` |
| `NR_MPROTECT` | macro | `tests/test_seccomp_bpf.c:28` | `#define NR_MPROTECT` |
| `NR_OPEN` | macro | `tests/test_seccomp_bpf.c:26` | `#define NR_OPEN` |
| `NR_READ` | macro | `tests/test_seccomp_bpf.c:24` | `#define NR_READ` |
| `NR_WRITE` | macro | `tests/test_seccomp_bpf.c:25` | `#define NR_WRITE` |
| `PROT_EXEC` | macro | `tests/test_seccomp_bpf.c:29` | `#define PROT_EXEC` |
| `STMT` | macro | `tests/test_seccomp_bpf.c:21` | `#define STMT(c, k)` |
| `data_for` | function | `tests/test_seccomp_bpf.c:34` | `static sbpf_data data_for(int nr, unsigned long long a2)` |
| `main` | function | `tests/test_seccomp_bpf.c:210` | `int main(void)` |
| `test_action_rank` | function | `tests/test_seccomp_bpf.c:199` | `static void test_action_rank(void)` |
| `test_alu_and_jumps` | function | `tests/test_seccomp_bpf.c:150` | `static void test_alu_and_jumps(void)` |
| `test_check_refusals` | function | `tests/test_seccomp_bpf.c:88` | `static void test_check_refusals(void)` |
| `test_freedom_shape` | function | `tests/test_seccomp_bpf.c:43` | `static void test_freedom_shape(void)` |
| `test_scratch_flow` | function | `tests/test_seccomp_bpf.c:130` | `static void test_scratch_flow(void)` |
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

Next: [SYMBOLS_p25.md](SYMBOLS_p25.md)
