# headers

*Community 2 | 27 files | cohesion 0.52*

## Definition

This community groups 27 file(s) rooted at `kernel` with dominant language c (cohesion 0.52). Central symbols: `BOOT_CPU`, `BSP`, `CHECK`, `CLONE_FILES`, `CLONE_VM`, `COM1`, `COND_INIT`, `DESKTOP_TICK_INTERVAL`. Core file: `kernel/sched.c` (138 symbols). Documented purpose: ifndef MOUSE_H define MOUSE_H  Docstring: mouse.h -- boundary of the PS/2 mouse device driver.

## Files

### `headers` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/futex.h` | h | utility | 17 | yes |
| `headers/percpu_rq.h` | h | utility | 14 | yes |
| `headers/rcu.h` | h | utility | 18 | yes |
| `headers/sched.h` | h | utility | 102 | yes |
| `headers/smp.h` | h | utility | 11 | yes |

### `kernel` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/futex.c` | c | utility | 11 | yes |
| `kernel/mm.c` | c | utility | 13 | yes |
| `kernel/percpu_rq.c` | c | utility | 14 | yes |
| `kernel/rcu.c` | c | utility | 21 | yes |
| `kernel/sched.c` | c | utility | 138 | no |

### `tests` (6 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_futex.c` | c | testing | 11 | yes |
| `tests/test_hal_io.c` | c | testing | 9 | yes |
| `tests/test_modifiers.c` | c | testing | 6 | yes |
| `tests/test_percpu_rq.c` | c | testing | 10 | yes |
| `tests/test_rcu.c` | c | testing | 13 | yes |

### `drivers` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/kbd.c` | c | infrastructure | 44 | yes |
| `drivers/mouse.c` | c | infrastructure | 10 | yes |

### `headers/drivers` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/drivers/modifiers.h` | h | infrastructure | 11 | yes |
| `headers/drivers/mouse.h` | h | infrastructure | 4 | yes |

### `headers/arch/x86` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/arch/x86/hal_io.h` | h | utility | 53 | yes |

*... and 7 more files in this community.*


## Key Symbols

- `kbd_get_layout` (function, `drivers/kbd.c:99`) `int kbd_get_layout(void)`
- `kbd_set_layout` (function, `drivers/kbd.c:101`) `void kbd_set_layout(int layout)`
- `kbd_toggle_layout` (function, `drivers/kbd.c:105`) `void kbd_toggle_layout(void)`
- `kbd_shift` (macro, `drivers/kbd.c:115`) `#define kbd_shift`
- `kbd_ctrl` (macro, `drivers/kbd.c:116`) `#define kbd_ctrl`
- `kbd_alt` (macro, `drivers/kbd.c:117`) `#define kbd_alt`
- `kbd_super` (macro, `drivers/kbd.c:118`) `#define kbd_super`
- `kbd_altgr` (macro, `drivers/kbd.c:119`) `#define kbd_altgr`
- `KBD_QUEUE_LEN` (macro, `drivers/kbd.c:120`) `#define KBD_QUEUE_LEN`
- `KBD_SCAN_DEL` (macro, `drivers/kbd.c:122`) `#define KBD_SCAN_DEL`
- `kbd_drop_counts` (function, `drivers/kbd.c:132`) `void kbd_drop_counts(unsigned long *cooked, unsigned long *raw)` - #define kbd_super (kbd_mods.super) #define kbd_altgr (kbd_mods.altgr) #define KBD_QUEUE_LEN 8 #defin
- `KBD_RAW_LEN` (macro, `drivers/kbd.c:140`) `#define KBD_RAW_LEN`
- `kbd_q_push` (function, `drivers/kbd.c:145`) `void kbd_q_push(unsigned char c)`
- `kbd_raw_push_internal` (function, `drivers/kbd.c:155`) `static void kbd_raw_push_internal(unsigned char c)`
- `kbd_q_empty` (function, `drivers/kbd.c:165`) `int kbd_q_empty(void)`
- `kbd_q_pop` (function, `drivers/kbd.c:167`) `int kbd_q_pop(void)`
- `kbd_available` (function, `drivers/kbd.c:174`) `int kbd_available(void)`
- `kbd_raw_mode_get` (function, `drivers/kbd.c:180`) `int kbd_raw_mode_get(void)`
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
- `raw_track_mods` (function, `drivers/kbd.c:220`) `static int raw_track_mods(int code, int brk, int e0)`
- `modifiers_update` (function, `drivers/kbd.c:222`) `return modifiers_update(&kbd_keys, &kbd_mods, code, brk, e0);`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 40
- Cross-boundary resolved imports (EXTRACTED): 37

## Connections

- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: drivers/kbd.c imports headers/kernel.h.
- [EXTRACTED] depends_on community 2 <-> 9 (strength 0.9): Extracted import edge crosses communities: headers/sched.h imports headers/vma.h.
- [EXTRACTED] depends_on community 2 <-> 0 (strength 0.9): Extracted import edge crosses communities: kernel/sched.c imports headers/arch/x86/boot/bootdefs.h.
- [EXTRACTED] depends_on community 2 <-> 8 (strength 0.9): Extracted import edge crosses communities: kernel/sched.c imports headers/tick.h.
- [EXTRACTED] depends_on community 7 <-> 2 (strength 0.9): Extracted import edge crosses communities: kernel/vga_fb.c imports headers/sched.h.

## Risks

- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/spinlock.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/spinlock.h` via `subprocess` (3 hops)

## Open Questions

- Why do 1 file(s) lack file-level docs (e.g. `kernel/sched.c`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.52?

## Sources

- `drivers/kbd.c`
- `drivers/mouse.c`
- `headers/arch/x86/hal_io.h`
- `headers/drivers/modifiers.h`
- `headers/drivers/mouse.h`
- `headers/futex.h`
- `headers/percpu_rq.h`
- `headers/rcu.h`
- `headers/sched.h`
- `headers/smp.h`
- `headers/spinlock.h`
- `headers/sync.h`
- `headers/wm_events.h`
- `kernel/futex.c`
- `kernel/mm.c`
- `kernel/percpu_rq.c`
- `kernel/rcu.c`
- `kernel/sched.c`
- `kernel/serial.c`
- `kernel/sync.c`
- *... and 7 more*
