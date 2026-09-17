# Subsystem: drivers

## headers/drivers/kbd.h
- Layer: infrastructure
- Doc: Keyboard layout: US qwerty (default) or Spanish (Spain) qwerty. Toggled from the taskbar widget or the `kbd` shell built
- Language: h
- Symbols:
  - `kbd_available` (function, line 8) `int kbd_available(void);`
  - `kbd_read` (function, line 10) `int kbd_read(void);`
  - `kbd_reset_for_shell` (function, line 11) `void kbd_reset_for_shell(void);`
  - `kbd_get_layout` (function, line 14) `int kbd_get_layout(void);`
  - `kbd_set_layout` (function, line 15) `void kbd_set_layout(int layout);`
  - `kbd_toggle_layout` (function, line 16) `void kbd_toggle_layout(void);`
  - `kbd_q_empty` (function, line 26) `int kbd_q_empty(void);`
  - `kbd_q_pop` (function, line 27) `int kbd_q_pop(void);`
  - `kbd_q_push` (function, line 28) `void kbd_q_push(unsigned char c);`
  - `kbd_drop_counts` (function, line 31) `void kbd_drop_counts(unsigned long *cooked, unsigned long *raw);`
  - `kbd_raw_mode_get` (function, line 34) `int kbd_raw_mode_get(void);`
  - `kbd_raw_mode_set` (function, line 35) `void kbd_raw_mode_set(int on);`
  - `kbd_raw_empty` (function, line 36) `int kbd_raw_empty(void);`
  - `kbd_raw_pop` (function, line 37) `int kbd_raw_pop(void);`
  - `kbd_raw_push_byte` (function, line 38) `void kbd_raw_push_byte(unsigned char c);`
  - `kbd_e0_get` (function, line 39) `int kbd_e0_get(void);`
  - `kbd_e0_set` (function, line 40) `void kbd_e0_set(int v);`
  - `kbd_flush_all` (function, line 41) `void kbd_flush_all(void);`
  - `kbd_raw_flush` (function, line 42) `void kbd_raw_flush(void);`
  - `kbd_sys_raw_filter` (function, line 49) `int kbd_sys_raw_filter(unsigned char sc);`
  - `KBD_H` (macro, line 2) `#define KBD_H`
  - `KBD_LAYOUT_EN` (macro, line 6) `#define KBD_LAYOUT_EN`
  - `KBD_LAYOUT_ES` (macro, line 7) `#define KBD_LAYOUT_ES`
- Imported by: `drivers/kbd.c`, `kernel/console_in.c`, `kernel/exec.c`, `kernel/shell.c`, `kernel/syscalls.c`, `kernel/vga_fb.c`

## headers/drivers/modifiers.h
- Layer: infrastructure
- Doc: Docstring: Unified modifier tracking for cooked and raw paths.
- Language: h
- Symbols:
  - `modifier_state_t` (struct, line 5)
  - `modifier_keys_t` (struct, line 14)
  - `modifiers_init` (function, line 31) `static inline void modifiers_init(modifier_state_t *st)`
  - `modifiers_update` (function, line 42) `static inline int modifiers_update(const modifier_keys_t *keys,
                                 ...`
  - `modifiers_match` (function, line 76) `static inline int modifiers_match(const modifier_state_t *st, int mask)`
  - `MODIFIERS_H` (macro, line 2) `#define MODIFIERS_H`
  - `MOD_SHIFT` (macro, line 23) `#define MOD_SHIFT`
  - `MOD_CTRL` (macro, line 25) `#define MOD_CTRL`
  - `MOD_ALT` (macro, line 26) `#define MOD_ALT`
  - `MOD_ALTGR` (macro, line 27) `#define MOD_ALTGR`
  - `MOD_SUPER` (macro, line 28) `#define MOD_SUPER`
- Imported by: `drivers/kbd.c`, `headers/wm_events.h`, `tests/test_modifiers.c`

## headers/drivers/mouse.h
- Layer: infrastructure
- Doc: Docstring: mouse.h -- boundary of the PS/2 mouse device driver
- Language: h
- Symbols:
  - `mouse_hw_init` (function, line 11) `void mouse_hw_init(void);`
  - `mouse_disable` (function, line 14) `void mouse_disable(void);`
  - `mouse_enable` (function, line 17) `void mouse_enable(void);`
  - `MOUSE_H` (macro, line 2) `#define MOUSE_H`
- Depends on: `headers/kernel.h`
- Imported by: `drivers/mouse.c`, `kernel/sched.c`
