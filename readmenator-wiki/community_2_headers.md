# headers

*Community 2 | 89 files | cohesion 0.73*

## Definition

This community groups 89 file(s) rooted at `headers` with dominant language c (cohesion 0.73). Central symbols: `ALIGN_UP`, `ARCH_X86_MSR_H`, `BOOTLOG_MAX`, `BOOT_CPU`, `BSP`, `C`, `CHECK`, `CLIP_MAX`. Core file: `headers/kernel.h` (339 symbols). Documented purpose: CMOS RTC time-of-day reader. The desktop clock and the shell `date` builtin.

## Files

### `headers` (32 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/ap_stub.h` | h | testing | 0 | yes |
| `headers/desktop_icons.h` | h | utility | 3 | yes |

### `kernel` (21 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/clip.c` | c | utility | 4 | yes |
| `kernel/console.c` | c | utility | 24 | yes |

### `tests` (11 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_fault.c` | c | testing | 11 | yes |
| `tests/test_fx.c` | c | testing | 2 | yes |

### `.` (5 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel.c` | c | utility | 20 | yes |
| `qga.c` | c | utility | 27 | yes |

### `net` (5 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `net/net.c` | c | utility | 66 | yes |
| `net/rtl8139.c` | c | utility | 29 | no |

### `fs` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fs/kfile.c` | c | utility | 23 | yes |
| `fs/ramdisk.c` | c | infrastructure | 19 | yes |

### `drivers` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/kbd.c` | c | infrastructure | 34 | yes |
| `drivers/rtc.c` | c | infrastructure | 25 | yes |

### `headers/drivers` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/drivers/kbd.h` | h | infrastructure | 23 | yes |

### `headers/kernel` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/kernel/console_in.h` | h | utility | 11 | yes |

### `kernel/mm` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/mm/cow.c` | c | utility | 15 | yes |

### `headers/arch/x86` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/arch/x86/msr.h` | h | utility | 9 | yes |

### `headers/net` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/net/rtl8139.h` | h | utility | 8 | no |

### `progs/tls_u` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/tls_u/tls_u_main.c` | c | utility | 5 | yes |

*... and 69 more files in this community.*


## Key Symbols

- `kbd_get_layout` (function, `drivers/kbd.c:100`) `int kbd_get_layout(void)`
- `kbd_set_layout` (function, `drivers/kbd.c:101`) `void kbd_set_layout(int layout)`
- `kbd_toggle_layout` (function, `drivers/kbd.c:105`) `void kbd_toggle_layout(void)`
- `kbd_shift` (macro, `drivers/kbd.c:115`) `#define kbd_shift`
- `kbd_ctrl` (macro, `drivers/kbd.c:116`) `#define kbd_ctrl`
- `kbd_alt` (macro, `drivers/kbd.c:117`) `#define kbd_alt`
- `kbd_super` (macro, `drivers/kbd.c:118`) `#define kbd_super`
- `kbd_altgr` (macro, `drivers/kbd.c:119`) `#define kbd_altgr`
- `KBD_QUEUE_LEN` (macro, `drivers/kbd.c:121`) `#define KBD_QUEUE_LEN`
- `KBD_SCAN_DEL` (macro, `drivers/kbd.c:122`) `#define KBD_SCAN_DEL`
- `kbd_drop_counts` (function, `drivers/kbd.c:132`) `void kbd_drop_counts(unsigned long *cooked, unsigned long *raw)` - #define kbd_super (kbd_mods.super) #define kbd_altgr (kbd_mods.altgr) #define KBD_QUEUE_LEN 8 #defin
- `KBD_RAW_LEN` (macro, `drivers/kbd.c:141`) `#define KBD_RAW_LEN`
- `kbd_q_push` (function, `drivers/kbd.c:146`) `void kbd_q_push(unsigned char c)`
- `kbd_raw_push_internal` (function, `drivers/kbd.c:156`) `static void kbd_raw_push_internal(unsigned char c)`
- `kbd_q_empty` (function, `drivers/kbd.c:166`) `int kbd_q_empty(void)`
- `kbd_q_pop` (function, `drivers/kbd.c:168`) `int kbd_q_pop(void)`
- `kbd_available` (function, `drivers/kbd.c:175`) `int kbd_available(void)`
- `kbd_raw_mode_get` (function, `drivers/kbd.c:181`) `int kbd_raw_mode_get(void)`
- `kbd_raw_mode_set` (function, `drivers/kbd.c:182`) `void kbd_raw_mode_set(int on)`
- `kbd_raw_empty` (function, `drivers/kbd.c:183`) `int kbd_raw_empty(void)`
- `kbd_raw_pop` (function, `drivers/kbd.c:184`) `int kbd_raw_pop(void)`
- `kbd_raw_push_byte` (function, `drivers/kbd.c:190`) `void kbd_raw_push_byte(unsigned char c)`
- `kbd_e0_get` (function, `drivers/kbd.c:191`) `int kbd_e0_get(void)`
- `kbd_e0_set` (function, `drivers/kbd.c:192`) `void kbd_e0_set(int v)`
- `kbd_flush_all` (function, `drivers/kbd.c:193`) `void kbd_flush_all(void)`
- `kbd_raw_flush` (function, `drivers/kbd.c:200`) `void kbd_raw_flush(void)` - Drop queued raw scancodes (shell-typed while a terminal owned PS/2) so a * newly focused game never
- `paths` (function, `drivers/kbd.c:210`) `* keeps the modifier state in sync on both paths (the old raw branch never * tra`
- `too` (function, `drivers/kbd.c:215`) `* too (DOOM strafes with Alt+arrows);`
- `raw_track_mods` (function, `drivers/kbd.c:221`) `static int raw_track_mods(int code, int brk, int e0)`
- `wm_combo_dispatch` (function, `drivers/kbd.c:226`) `static int wm_combo_dispatch(int action, int zone)` - wm_raw_combo performs the WM action and reports 1 when the byte must be swallowed. Deliberately narr

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 176
- Cross-boundary resolved imports (EXTRACTED): 66

## Connections

- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: drivers/block.c imports headers/kernel.h.
- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: drivers/kbd.c imports headers/arch/x86/hal_io.h.
- [EXTRACTED] depends_on community 0 <-> 2 (strength 0.9): Extracted import edge crosses communities: drivers/pcm2.c imports headers/kernel.h.
- [EXTRACTED] depends_on community 4 <-> 2 (strength 0.9): Extracted import edge crosses communities: drivers/virtio_blk.c imports headers/kernel.h.
- [EXTRACTED] depends_on community 2 <-> 6 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 2 <-> 9 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports kernel/time.c.
- [EXTRACTED] depends_on community 5 <-> 2 (strength 0.9): Extracted import edge crosses communities: kernel/abi.c imports headers/kernel.h.

## Risks

- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/kernel.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/vma.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/pipe.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/kernel.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/vma.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/pipe.h` via `subprocess` (3 hops)
- [taint high] `mcp/minios_addons.py` -> `headers/kernel.h` via `subprocess` (2 hops)
- [layer strict] `tests/test_httpd.c` (testing) -> `headers/httpd.h` (presentation)
- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_render.h` (presentation)
- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_layout.h` (presentation)
- [dataflow DEAD_STORE] `fs/kfile.c:98` `kpipe_pair` `ref`: `ref` assigned at line 98 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/loader.c:458` `load_exec_elf` `base`: `base` assigned at line 458 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/loader.c:463` `load_exec_elf` `max_end`: `max_end` assigned at line 463 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/mm/paging.c:42` `mm_setup_protections` `pd`: `pd` assigned at line 42 but never read afterwards.
- [dataflow UNINIT_USE] `kernel/shell.c:1583` `context` `buf`: `buf` may be read before initialization (declared line 1575).

## Open Questions

- Why do 8 file(s) lack file-level docs (e.g. `headers/net/rtl8139.h`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.73?

## Sources

- `drivers/kbd.c`
- `drivers/rtc.c`
- `fs/kfile.c`
- `fs/ramdisk.c`
- `fs/vfs.c`
- `fs/zip.c`
- `headers/ap_stub.h`
- `headers/arch/x86/msr.h`
- `headers/desktop_icons.h`
- `headers/desktop_shortcuts.h`
- `headers/drivers/kbd.h`
- `headers/drivers/modifiers.h`
- `headers/editor.h`
- `headers/httpd.h`
- `headers/kernel.h`
- `headers/kernel/console_in.h`
- `headers/kernel/vga_cursor.h`
- `headers/minifetch.h`
- `headers/minifs.h`
- `headers/net.h`
- *... and 69 more*
