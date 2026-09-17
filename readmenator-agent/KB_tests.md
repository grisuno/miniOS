# Subsystem: tests

## tests/host_aes.sh
- Layer: testing
- Doc: host_aes.sh - host-side verification for the AES-256-CTR command tools.  The miniGCC-built tools are static Linux ELFs, 
- Language: sh
- Symbols:
  - `ok` (function, line 23)
  - `bad` (function, line 24)
  - `rd` (function, line 25)

## tests/host_codecs.sh
- Layer: testing
- Doc: host_codecs.sh - reusable host-side verification for the in-OS codec tools.  The miniGCC-compiled tools are static Linux
- Language: sh
- Symbols:
  - `ok` (function, line 22)
  - `bad` (function, line 23)
  - `gen_input` (function, line 27)
  - `roundtrip` (function, line 31)
  - `reject` (function, line 40)

## tests/test_abi.c
- Layer: testing
- Doc: Docstring: tests/test_abi.c -- Host test for the ABI manifest gate.
- Language: c
- Symbols:
  - `expect` (function, line 16) `static void expect(const char *name, const char *manifest, int want)`
  - `main` (function, line 25) `int main(void)`
- Depends on: `headers/abi.h`, `progs/minios_abi.h`

## tests/test_batch.c
- Layer: testing
- Doc: Docstring: Host test for kernel/batch.c (make test-batch).
- Language: c
- Symbols:
  - `stub_dispatch` (function, line 24) `static long stub_dispatch(uint32_t opcode)`
  - `main` (function, line 31) `int main(void)`
  - `CHECK` (macro, line 17) `#define CHECK(cond, msg)`
- Depends on: `headers/batch.h`

## tests/test_doom_pwad.py
- Layer: testing
- Doc: test_doom_pwad.py - host contract suite for tools/doom_pwad.py.  Runs the grid compiler and the PWAD checker against fix
- Language: py
- Symbols:
  - `GridValidationTests` (class, line 29) `class GridValidationTests(TestCase)`
  - `PwadLayoutTests` (class, line 82) `class PwadLayoutTests(TestCase)`
  - `PwadMutationTests` (class, line 181) `class PwadMutationTests(TestCase)`
  - `ExtendedLegendTests` (class, line 255) `class ExtendedLegendTests(TestCase)`
  - `lump_blob` (method, line 310) `def lump_blob(blob, idx)`
  - `MultiSectorTests` (class, line 317) `class MultiSectorTests(TestCase)`
  - `MultiSectorMutationTests` (class, line 388) `class MultiSectorMutationTests(TestCase)`
  - `test_valid_room_parses` (method, line 32) `def test_valid_room_parses(self)`
  - `test_ragged_rows_refused` (method, line 36) `def test_ragged_rows_refused(self)`
  - `test_missing_player_refused` (method, line 41) `def test_missing_player_refused(self)`
  - `test_missing_exit_refused` (method, line 46) `def test_missing_exit_refused(self)`
  - `test_illegal_char_refused` (method, line 51) `def test_illegal_char_refused(self)`
  - `test_unreachable_exit_refused` (method, line 56) `def test_unreachable_exit_refused(self)`
  - `test_exit_needs_wall` (method, line 66) `def test_exit_needs_wall(self)`
  - `test_roundtrip_check` (method, line 85) `def test_roundtrip_check(self)`
  - `test_header_pin` (method, line 96) `def test_header_pin(self)`
  - `test_lump_order_pin` (method, line 103) `def test_lump_order_pin(self)`
  - `test_things_pin` (method, line 115) `def test_things_pin(self)`
  - `test_exit_switch_pin` (method, line 129) `def test_exit_switch_pin(self)`
  - `test_exit_on_every_side` (method, line 141) `def test_exit_on_every_side(self)`
  - `test_pillar_room_stays_closed` (method, line 154) `def test_pillar_room_stays_closed(self)`
  - `test_open_boundary_dies` (method, line 168) `def test_open_boundary_dies(self)`
  - `setUp` (method, line 184) `def setUp(self)`
  - `test_bad_magic_dies` (method, line 188) `def test_bad_magic_dies(self)`
  - `test_truncated_file_dies` (method, line 193) `def test_truncated_file_dies(self)`
  - `test_swapped_lumps_die` (method, line 198) `def test_swapped_lumps_die(self)`
  - `test_partial_record_dies` (method, line 212) `def test_partial_record_dies(self)`
  - `test_wild_vertex_dies` (method, line 221) `def test_wild_vertex_dies(self)`
  - `test_missing_exit_dies` (method, line 230) `def test_missing_exit_dies(self)`
  - `test_unterminated_blockmap_dies` (method, line 243) `def test_unterminated_blockmap_dies(self)`
  - `test_every_legend_char_builds` (method, line 273) `def test_every_legend_char_builds(self)`
  - `test_every_thing_id_matches_engine` (method, line 278) `def test_every_thing_id_matches_engine(self)`
  - `test_door_room_builds_two_sectors` (method, line 320) `def test_door_room_builds_two_sectors(self)`
  - `test_door_lines_are_tagged_openers` (method, line 327) `def test_door_lines_are_tagged_openers(self)`
  - `test_dark_and_nukage_sector_props` (method, line 355) `def test_dark_and_nukage_sector_props(self)`
  - `test_reject_scales_with_sector_count` (method, line 374) `def test_reject_scales_with_sector_count(self)`
  - `test_new_legend_chars_build` (method, line 382) `def test_new_legend_chars_build(self)`
  - `setUp` (method, line 391) `def setUp(self)`
  - `mutate_line` (method, line 395) `def mutate_line(self, idx, field, value)`
  - `door_line` (method, line 406) `def door_line(self)`
  - `test_door_tag_zero_dies` (method, line 418) `def test_door_tag_zero_dies(self)`
  - `test_unknown_special_dies` (method, line 423) `def test_unknown_special_dies(self)`
  - `test_onesided_with_back_dies` (method, line 428) `def test_onesided_with_back_dies(self)`
  - `test_exit_tagged_dies` (method, line 433) `def test_exit_tagged_dies(self)`
- Depends on: `tools/doom_pwad.py`

## tests/test_driver.c
- Layer: testing
- Doc: test_driver.c -- Host test for the Strategy-pattern device registry.
- Language: c
- Symbols:
  - `test_read` (function, line 15) `static int test_read(device_t *d, unsigned lba, unsigned count, void *buf)`
  - `test_pcm_open` (function, line 28) `static void test_pcm_open(device_t *d)`
  - `test_pcm_submit` (function, line 33) `static int test_pcm_submit(device_t *d, const unsigned char *pcm, unsigned len)`
  - `test_tone` (function, line 39) `static void test_tone(device_t *d, unsigned freq)`
  - `main` (function, line 65) `int main(void)`
- Depends on: `headers/driver.h`, `kernel/string.c`

## tests/test_fault.c
- Layer: testing
- Doc: test_fault.c -- fault-injection suite (boyscout gap #10).
- Language: c
- Symbols:
  - `range_ok` (function, line 35) `static int range_ok(unsigned long p, unsigned long len)`
  - `str_ok` (function, line 41) `static int str_ok(const unsigned char *mem, unsigned long p,
                  unsigned long maxlen)`
  - `normalize` (function, line 52) `static void normalize(const char *path, char *out, unsigned cap)`
  - `path_trusted` (function, line 83) `static int path_trusted(const char *full)`
  - `main` (function, line 94) `int main(void)`
  - `against` (function, line 10) `* after bounding against (END-BASE)/elemsz, so the product cannot * wrap past the range check);`
  - `CHECK` (macro, line 28) `#define CHECK(c, m)`
  - `U_BASE` (macro, line 31) `#define U_BASE`
  - `U_END` (macro, line 32) `#define U_END`
  - `TRUSTED_DIR` (macro, line 81) `#define TRUSTED_DIR`
  - `TRUSTED_LEN` (macro, line 82) `#define TRUSTED_LEN`
- Depends on: `headers/vma.h`, `kernel/string.c`

## tests/test_file_assoc.c
- Layer: testing
- Doc: Docstring: host test for the file browser assoc contract (make test-file).
- Language: c
- Symbols:
  - `t_ext_of` (function, line 24) `static void t_ext_of(const char *fname, char *dst, unsigned cap)`
  - `t_assoc_line` (function, line 44) `static int t_assoc_line(const char *line, char *ext, char *prog)`
  - `main` (function, line 76) `int main(void)`
  - `CHECK` (macro, line 14) `#define CHECK(cond, msg)`
  - `T_EXT_MAX` (macro, line 21) `#define T_EXT_MAX`
  - `T_PROG_MAX` (macro, line 22) `#define T_PROG_MAX`
- Depends on: `kernel/string.c`

## tests/test_freedom_wl.c
- Layer: testing
- Doc: test_freedom_wl - host suite for the Wayland to MiniOS mapping.
- Language: c
- Symbols:
  - `check_host` (function, line 12) `static int check_host(int cond, const char *name)`
  - `main` (function, line 22) `int main(void)`
  - `FREEDOM_WL_HOST_TEST` (macro, line 8) `#define FREEDOM_WL_HOST_TEST`
- Depends on: `progs/src/freedom_wl.c`

## tests/test_freedomui.c
- Layer: testing
- Doc: test_freedomui - host suite for the real FreeDom MiniOS backend.
- Language: c
- Symbols:
  - `main` (function, line 24) `int main(void)`
  - `FREEDOMUI_HOST_TEST` (macro, line 10) `#define FREEDOMUI_HOST_TEST`
- Depends on: `kernel/string.c`, `progs/freedomui/freedomui_minios.c`

## tests/test_futex.c
- Layer: testing
- Doc: Docstring: Host test for kernel/futex.c (make test-futex).
- Language: c
- Symbols:
  - `proc_get` (function, line 18) `proc_t *proc_get(int pid)`
  - `schedule` (function, line 26) `void schedule(void)`
  - `fresh_proc` (function, line 39) `static void fresh_proc(int pid)`
  - `fresh_all` (function, line 48) `static void fresh_all(void)`
  - `main` (function, line 60) `int main(void)`
  - `CHECK` (macro, line 32) `#define CHECK(cond, msg)`
- Depends on: `headers/futex.h`

## tests/test_hal_io.c
- Layer: testing
- Doc: Docstring: Host test for arch/x86/hal_io.h (make test-hal).
- Language: c
- Symbols:
  - `main` (function, line 30) `int main(void)`
  - `HAL_IO_HOST_TEST` (macro, line 11) `#define HAL_IO_HOST_TEST`
  - `CHECK` (macro, line 23) `#define CHECK(cond, msg)`
- Depends on: `headers/arch/x86/hal_io.h`

## tests/test_ktime.c
- Layer: testing
- Doc: test_ktime.c -- host test for the pure conversion math in ktime.h
- Language: c
- Symbols:
  - `main` (function, line 16) `int main(void)`
  - `CHECK` (macro, line 14) `#define CHECK(c, m)`
- Depends on: `headers/ktime.h`

## tests/test_minios_png.c
- Layer: testing
- Doc: Docstring: host test for the shared ring-3 PNG helpers (make test-png).
- Language: c
- Symbols:
  - `t_332` (function, line 24) `static void t_332(void)`
  - `t_nearest` (function, line 33) `static void t_nearest(void)`
  - `t_geom` (function, line 58) `static void t_geom(void)`
  - `t_scale` (function, line 70) `static void t_scale(void)`
  - `t_blit` (function, line 99) `static void t_blit(void)`
  - `t_load` (function, line 117) `static void t_load(void)`
  - `t_policy` (function, line 136) `static void t_policy(void)`
  - `main` (function, line 151) `int main(void)`
  - `CHECK` (macro, line 16) `#define CHECK(cond, msg)`
- Depends on: `kernel/string.c`, `progs/minios_png.h`

## tests/test_modifiers.c
- Layer: testing
- Language: c
- Symbols:
  - `main` (function, line 16) `int main(void)`
  - `CHECK` (macro, line 9) `#define CHECK(cond, msg)`
- Depends on: `headers/drivers/modifiers.h`

## tests/test_notify.c
- Layer: testing
- Language: c
- Symbols:
  - `probe_handler` (function, line 16) `static void probe_handler(const wm_notify_event_t *e)`
  - `main` (function, line 22) `int main(void)`
  - `CHECK` (macro, line 9) `#define CHECK(cond, msg)`
- Depends on: `headers/wm_notify.h`

## tests/test_paint.c
- Layer: testing
- Doc: Docstring: host test for the paint canvas/PNG contract (make test-paint).
- Language: c
- Symbols:
  - `t_clamp` (function, line 30) `static int t_clamp(int v, int lo, int hi)`
  - `t_plot` (function, line 36) `static int t_plot(unsigned char *buf, int w, int h, int x, int y,
                  unsigned char c)`
  - `t_line` (function, line 44) `static int t_line(unsigned char *buf, int w, int h, int x0, int y0, int x1,
                  int...`
  - `t_flood` (function, line 70) `static int t_flood(unsigned char *buf, int w, int h, int x, int y,
                   unsigned ch...`
  - `t_crc_init` (function, line 116) `static void t_crc_init(void)`
  - `t_crc` (function, line 129) `static unsigned long t_crc(const unsigned char *p, unsigned long n)`
  - `t_path_ok` (function, line 138) `static int t_path_ok(const char *p)`
  - `t_nearest` (function, line 155) `static int t_nearest(const unsigned char *pal, unsigned r, unsigned g,
                     unsig...`
  - `test_plot` (function, line 171) `static void test_plot(void)`
  - `test_line` (function, line 188) `static void test_line(void)`
  - `test_flood` (function, line 207) `static void test_flood(void)`
  - `test_png_codec` (function, line 228) `static void test_png_codec(void)`
  - `test_png_layout` (function, line 259) `static void test_png_layout(void)`
  - `test_path` (function, line 273) `static void test_path(void)`
  - `test_nearest` (function, line 287) `static void test_nearest(void)`
  - `main` (function, line 300) `int main(void)`
  - `CHECK` (macro, line 16) `#define CHECK(cond, msg)`
  - `T_W` (macro, line 23) `#define T_W`
  - `T_H` (macro, line 24) `#define T_H`
  - `T_N` (macro, line 25) `#define T_N`
  - `T_PATH_MAX` (macro, line 26) `#define T_PATH_MAX`
- Depends on: `kernel/string.c`

## tests/test_percpu_rq.c
- Layer: testing
- Doc: Docstring: Host test for kernel/percpu_rq.c (make test-percpu-rq).
- Language: c
- Symbols:
  - `main` (function, line 24) `int main(void)`
  - `CHECK` (macro, line 17) `#define CHECK(cond, msg)`
- Depends on: `headers/percpu_rq.h`

## tests/test_randmix.c
- Layer: testing
- Doc: test_randmix.c -- host test for the getrandom mixer in randmix.h
- Language: c
- Symbols:
  - `popcount64` (function, line 18) `static int popcount64(unsigned long x)`
  - `main` (function, line 24) `int main(void)`
  - `CHECK` (macro, line 16) `#define CHECK(c, m)`
- Depends on: `headers/randmix.h`

## tests/test_rcu.c
- Layer: testing
- Doc: Docstring: Host test for kernel/rcu.c (make test-rcu).
- Language: c
- Symbols:
  - `rcu_host_cpu` (function, line 19) `cpu_t *rcu_host_cpu(void)`
  - `test_cb` (function, line 23) `static void test_cb(void *arg)`
  - `main` (function, line 37) `int main(void)`
  - `CHECK` (macro, line 30) `#define CHECK(cond, msg)`
- Depends on: `headers/rcu.h`

## tests/test_rtc.c
- Layer: testing
- Doc: test_rtc.c -- host test for the pure date math in drivers/rtc.c
- Language: c
- Symbols:
  - `main` (function, line 18) `int main(void)`
  - `CHECK` (macro, line 16) `#define CHECK(c, m)`
- Depends on: `headers/rtc.h`

## tests/test_sanitize.c
- Layer: testing
- Doc: Docstring: Host test for sanitize.h (make test-sanitize).
- Language: c
- Symbols:
  - `user_range_ok` (function, line 20) `int user_range_ok(unsigned long p, unsigned long len)`
  - `user_str_ok` (function, line 26) `int user_str_ok(unsigned long p, unsigned long maxlen)`
  - `kmemcpy` (function, line 32) `void *kmemcpy(void *dst, const void *src, unsigned long n)`
  - `range_probe` (function, line 48) `static long range_probe(unsigned long p, long len)`
  - `str_probe` (function, line 54) `static long str_probe(unsigned long p)`
  - `copy_probe` (function, line 61) `static long copy_probe(unsigned long uptr, long count, unsigned long elemsz)`
  - `main` (function, line 67) `int main(void)`
  - `EFAULT` (macro, line 13) `#define EFAULT`
  - `CHECK` (macro, line 41) `#define CHECK(cond, msg)`
- Depends on: `headers/sanitize.h`, `kernel/string.c`

## tests/test_sync.c
- Layer: testing
- Doc: Host-side unit test for the blocking sync primitives (kernel/sync.c).
- Language: c
- Symbols:
  - `proc_get` (function, line 24) `proc_t *proc_get(int pid)`
  - `schedule` (function, line 30) `void schedule(void)`
  - `fresh_proc` (function, line 44) `static void fresh_proc(int pid)`
  - `fresh_all` (function, line 52) `static void fresh_all(void)`
  - `main` (function, line 63) `int main(void)`
  - `CHECK` (macro, line 37) `#define CHECK(cond, msg)`
- Depends on: `headers/sync.h`

## tests/test_theme.c
- Layer: testing
- Doc: Docstring: host test for the shared Nuklear theme contract.
- Language: c
- Symbols:
  - `tslot` (struct, line 23)
  - `t_name_ok` (function, line 34) `static int t_name_ok(const char *name)`
  - `t_parse_line` (function, line 46) `static int t_parse_line(const char *line, int *idx, long v[3])`
  - `cube_exact` (function, line 74) `static int cube_exact(long v)`
  - `check_theme_file` (function, line 78) `static void check_theme_file(const char *path)`
  - `main` (function, line 107) `int main(void)`
  - `CHECK` (macro, line 16) `#define CHECK(cond, msg)`
  - `X` (macro, line 29) `#define X(k, i)`
- Depends on: `kernel/string.c`, `progs/nuklear/nuklear_theme.h`

## tests/test_tick.c
- Layer: testing
- Doc: Docstring: Host test for kernel/tick.c (make test-tick).
- Language: c
- Symbols:
  - `rec_a` (function, line 24) `static void rec_a(void *ctx)`
  - `rec_b` (function, line 31) `static void rec_b(void *ctx)`
  - `rec_d` (function, line 38) `static void rec_d(void *ctx)`
  - `dummy` (function, line 47) `static void dummy(void *ctx)`
  - `main` (function, line 52) `int main(void)`
  - `CHECK` (macro, line 17) `#define CHECK(cond, msg)`
- Depends on: `headers/tick.h`

## tests/test_vedit_build.c
- Layer: testing
- Doc: Docstring: Host test for the vedit IDE build contract (make test-vedit).
- Language: c
- Symbols:
  - `t_has_ext` (function, line 32) `static int t_has_ext(const char *fname, const char *ext)`
  - `t_base_of` (function, line 43) `static int t_base_of(const char *fname, char *dst, size_t cap)`
  - `t_join` (function, line 63) `static int t_join(const char *dir, const char *base, const char *ext,
                  char *dst...`
  - `t_link_fmt` (function, line 79) `static int t_link_fmt(const char *s)`
  - `t_lang_of` (function, line 93) `static int t_lang_of(const char *fname)`
  - `t_run_kind` (function, line 110) `static int t_run_kind(const char *fname)`
  - `main` (function, line 118) `int main(void)`
  - `CHECK` (macro, line 25) `#define CHECK(cond, msg)`
- Depends on: `kernel/string.c`

## tests/test_vma.c
- Layer: testing
- Doc: Host-side unit test for the VMA red-black tree (vma.c).
- Language: c
- Symbols:
  - `black_height` (function, line 27) `static int black_height(const vma_node_t *n)`
  - `tree_valid` (function, line 38) `static int tree_valid(const vma_node_t *root)`
  - `count_nodes` (function, line 75) `static int count_nodes(const vma_node_t *root)`
  - `test_insert_find_delete` (function, line 89) `static void test_insert_find_delete(void)`
  - `test_pool_exhaustion` (function, line 136) `static void test_pool_exhaustion(void)`
  - `test_full_drain` (function, line 153) `static void test_full_drain(void)`
  - `main` (function, line 167) `int main(void)`
  - `CHECK` (macro, line 20) `#define CHECK(cond, msg)`
- Depends on: `headers/vma.h`

## tests/test_vma_bench.c
- Layer: testing
- Doc: test_vma_bench.c -- RB-tree vs sorted-list benchmark (boyscout gap #9).
- Language: c
- Symbols:
  - `now_us` (function, line 13) `static long now_us(void)`
  - `l_insert` (function, line 23) `static void l_insert(unsigned long b)`
  - `l_find` (function, line 28) `static int l_find(unsigned long b)`
  - `bench` (function, line 34) `static void bench(int n)`
  - `main` (function, line 54) `int main(void)`
  - `LIST_MAX` (macro, line 20) `#define LIST_MAX`
- Depends on: `headers/vma.h`, `kernel/time.c`

## tests/test_wl.c
- Layer: testing
- Doc: Host test for progs/wl/wl_mini.h (make test-wl).
- Language: c
- Symbols:
  - `main` (function, line 25) `int main(void)`
  - `CHECK` (macro, line 18) `#define CHECK(cond, msg)`
- Depends on: `kernel/string.c`, `progs/minios_abi.h`, `progs/nk_palette.h`, `progs/wl/wl_mbox.h`, `progs/wl/wl_mini.h`

## tests/test_wm.c
- Layer: testing
- Doc: Docstring: Host test for wm_geom.h and wm_events.h (make test-wm).
- Language: c
- Symbols:
  - `main` (function, line 28) `int main(void)`
  - `CHECK` (macro, line 21) `#define CHECK(cond, msg)`
- Depends on: `headers/wm_events.h`, `headers/wm_focus.h`, `headers/wm_geom.h`, `headers/wm_layout.h`, `headers/wm_render.h`, `headers/wm_tiling.h`, `headers/wm_window.h`
