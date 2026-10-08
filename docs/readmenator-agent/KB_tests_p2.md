# Subsystem: tests (page 2 of 2)
Previous: [KB_tests.md](KB_tests.md)

## tests/test_sanitize.c
- Doc: Docstring: Host test for sanitize.h (make test-sanitize).
- Layer: testing
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
- Doc: Host-side unit test for the blocking sync primitives (kernel/sync.c).
- Layer: testing
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
- Doc: Docstring: host test for the shared Nuklear theme contract.
- Layer: testing
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
- Doc: Docstring: Host test for kernel/tick.c (make test-tick).
- Layer: testing
- Language: c
- Symbols:
  - `rec_a` (function, line 24) `static void rec_a(void *ctx)`
  - `rec_b` (function, line 31) `static void rec_b(void *ctx)`
  - `rec_d` (function, line 38) `static void rec_d(void *ctx)`
  - `dummy` (function, line 47) `static void dummy(void *ctx)`
  - `main` (function, line 52) `int main(void)`
  - `CHECK` (macro, line 17) `#define CHECK(cond, msg)`
- Depends on: `headers/tick.h`

## tests/test_usbblk.c
- Doc: Docstring: Host test for the USB mass-storage driver (make test-usbblk).
- Layer: testing
- Language: c
- Symbols:
  - `device_register` (function, line 20) `int device_register(device_t *dev)`
  - `device_find` (function, line 26) `device_t *device_find(const char *name)`
  - `main` (function, line 43) `int main(void)`
  - `CHECK` (macro, line 36) `#define CHECK(cond, msg)`
- Depends on: `drivers/usbblk.c`, `drivers/xhci.c`, `headers/driver.h`, `headers/drivers/usbblk.h`

## tests/test_usbhid.c
- Doc: Docstring: Host test for the USB HID driver (make test-usbhid).
- Layer: testing
- Language: c
- Symbols:
  - `kbd_feed_scancode` (function, line 22) `int kbd_feed_scancode(unsigned char sc)`
  - `kbd_q_push` (function, line 30) `void kbd_q_push(unsigned char c)`
  - `check_usage` (function, line 48) `static void check_usage(unsigned usage, unsigned char want_sc, int want_e0,
                     ...`
  - `main` (function, line 59) `int main(void)`
  - `CHECK` (macro, line 41) `#define CHECK(cond, msg)`
- Depends on: `drivers/usbhid.c`, `drivers/xhci.c`, `headers/drivers/usbhid.h`, `kernel/string.c`

## tests/test_vedit_build.c
- Doc: Docstring: Host test for the vedit IDE build contract (make test-vedit).
- Layer: testing
- Language: c
- Symbols:
  - `t_has_ext` (function, line 40) `static int t_has_ext(const char *fname, const char *ext)`
  - `t_base_of` (function, line 51) `static int t_base_of(const char *fname, char *dst, size_t cap)`
  - `t_join` (function, line 71) `static int t_join(const char *dir, const char *base, const char *ext,
                  char *dst...`
  - `t_link_fmt` (function, line 87) `static int t_link_fmt(const char *s)`
  - `t_lang_of` (function, line 101) `static int t_lang_of(const char *fname)`
  - `t_run_kind` (function, line 121) `static int t_run_kind(const char *fname)`
  - `t_str_case` (function, line 131) `static void t_str_case(char *s, int mode)`
  - `t_transpose` (function, line 157) `static void t_transpose(char *s, int len, int pos)`
  - `t_mclass` (function, line 166) `static int t_mclass(int c, const char *cls)`
  - `t_matom` (function, line 188) `static int t_matom(const char *pat, int c, int *atom_len)`
  - `t_mhere` (function, line 211) `static int t_mhere(const char *text, const char *pat, int *mlen)`
  - `t_magic` (function, line 268) `static int t_magic(const char *text, const char *pat, int *mlen)`
  - `t_cmd` (function, line 299) `static int t_cmd(const char *name)`
  - `t_parse_key` (function, line 312) `static int t_parse_key(const char *s)`
  - `main` (function, line 345) `int main(void)`
  - `CHECK` (macro, line 33) `#define CHECK(cond, msg)`
- Depends on: `kernel/string.c`

## tests/test_vma.c
- Doc: Host-side unit test for the VMA red-black tree (vma.c).
- Layer: testing
- Language: c
- Symbols:
  - `black_height` (function, line 27) `static int black_height(const vma_node_t *n)`
  - `tree_valid` (function, line 38) `static int tree_valid(const vma_node_t *root)`
  - `count_nodes` (function, line 75) `static int count_nodes(const vma_node_t *root)`
  - `test_insert_find_delete` (function, line 89) `static void test_insert_find_delete(void)`
  - `test_pool_exhaustion` (function, line 136) `static void test_pool_exhaustion(void)`
  - `test_full_drain` (function, line 153) `static void test_full_drain(void)`
  - `test_file_tags_and_containing` (function, line 167) `static void test_file_tags_and_containing(void)`
  - `main` (function, line 199) `int main(void)`
  - `CHECK` (macro, line 20) `#define CHECK(cond, msg)`
- Depends on: `headers/vma.h`

## tests/test_vma_bench.c
- Doc: RB-tree vs sorted-list benchmark (boyscout gap #9).
- Layer: testing
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
- Doc: Host test for progs/wl/wl_mini.h (make test-wl).
- Layer: testing
- Language: c
- Symbols:
  - `main` (function, line 27) `int main(void)`
  - `CHECK` (macro, line 20) `#define CHECK(cond, msg)`
- Depends on: `kernel/string.c`, `progs/minios_abi.h`, `progs/nk_palette.h`, `progs/wl/wl_mbox.h`, `progs/wl/wl_mini.h`, `progs/wl/wl_pixbuf.h`

## tests/test_wm.c
- Doc: Docstring: Host test for wm_geom.h and wm_events.h (make test-wm).
- Layer: testing
- Language: c
- Symbols:
  - `main` (function, line 29) `int main(void)`
  - `CHECK` (macro, line 22) `#define CHECK(cond, msg)`
- Depends on: `headers/wm_events.h`, `headers/wm_focus.h`, `headers/wm_geom.h`, `headers/wm_gfxview.h`, `headers/wm_layout.h`, `headers/wm_render.h`, `headers/wm_tiling.h`, `headers/wm_window.h`

## tests/test_xhci.c
- Doc: Docstring: Host test for the xHCI controller driver (make test-xhci).
- Layer: testing
- Language: c
- Symbols:
  - `main` (function, line 30) `int main(void)`
  - `CHECK` (macro, line 23) `#define CHECK(cond, msg)`
- Depends on: `drivers/xhci.c`, `headers/drivers/xhci.h`, `kernel/string.c`

