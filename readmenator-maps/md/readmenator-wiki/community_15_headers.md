# headers

*Community 15 | 3 files | cohesion 0.67*

## Definition

This community groups 3 file(s) rooted at `headers` with dominant language c (cohesion 0.67). Central symbols: `CHECK`, `TICK_CONFIG_DEFAULT`, `TICK_H`, `TICK_MAX_AUDIO_LISTENERS`, `TICK_MAX_DESKTOP_LISTENERS`, `TICK_MAX_USB_LISTENERS`, `dummy`, `main`. Core file: `headers/tick.h` (16 symbols). Documented purpose: Docstring: Tick listener bus contract..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/tick.h` | h | utility | 16 | yes |
| `kernel/tick.c` | c | utility | 11 | yes |
| `tests/test_tick.c` | c | testing | 6 | yes |

## Key Symbols

- `TICK_H` (macro, `headers/tick.h:19`) `#define TICK_H`
- `tick_config_t` (struct, `headers/tick.h:22`) - gating predicate for the desktop tick.  Design: fixed-size tables, no heap, no locks. Registration h
- `TICK_MAX_AUDIO_LISTENERS` (macro, `headers/tick.h:29`) `#define TICK_MAX_AUDIO_LISTENERS`
- `TICK_MAX_DESKTOP_LISTENERS` (macro, `headers/tick.h:31`) `#define TICK_MAX_DESKTOP_LISTENERS`
- `TICK_MAX_USB_LISTENERS` (macro, `headers/tick.h:34`) `#define TICK_MAX_USB_LISTENERS`
- `TICK_CONFIG_DEFAULT` (macro, `headers/tick.h:37`) `#define TICK_CONFIG_DEFAULT`
- `tick_reset` (function, `headers/tick.h:47`) `void tick_reset(void);` - needs; the bound exists so the tables stay fixed-size. #define TICK_MAX_USB_LISTENERS 2 /** Docstrin
- `tick_register_audio` (function, `headers/tick.h:54`) `int tick_register_audio(tick_fn_t fn, void *ctx);` - Docstring: Register an unconditional BSP audio effect.  Returns 0 on success, -1 when the handler is
- `tick_register_desktop` (function, `headers/tick.h:61`) `int tick_register_desktop(tick_fn_t fn, void *ctx);` - Docstring: Register a gated desktop effect.  Returns 0 on success, -1 when the handler is null or th
- `tick_register_usb` (function, `headers/tick.h:69`) `int tick_register_usb(tick_fn_t fn, void *ctx);` - Docstring: Register a polled USB controller effect.  The xHCI event ring is polled by decision rathe
- `tick_run_usb` (function, `headers/tick.h:72`) `void tick_run_usb(void);` - Docstring: Register a polled USB controller effect.  The xHCI event ring is polled by decision rathe
- `tick_run_audio` (function, `headers/tick.h:75`) `void tick_run_audio(void);` - Docstring: Register a polled USB controller effect.  The xHCI event ring is polled by decision rathe
- `tick_run_desktop` (function, `headers/tick.h:78`) `void tick_run_desktop(void);` - The xHCI event ring is polled by decision rather than interrupt-driven, so this listener is the poll
- `tick_audio_count` (function, `headers/tick.h:81`) `int tick_audio_count(void);` - handler is null or the USB table is full. A refusal changes nothing.  int tick_register_usb(tick_fn_
- `tick_desktop_count` (function, `headers/tick.h:84`) `int tick_desktop_count(void);` - /** Docstring: Run USB listeners in registration order. void tick_run_usb(void); /** Docstring: Run
- `tick_desktop_due` (function, `headers/tick.h:92`) `int tick_desktop_due(unsigned long long ticks, unsigned interval);` - Docstring: Pure desktop gating predicate.  Returns nonzero when the given tick count falls on a desk
- `tick_slot_t` (struct, `kernel/tick.c:15`) - Docstring: Tick listener bus implementation.  Owns two fixed listener tables behind the tick.h contr
- `tick_reset` (function, `kernel/tick.c:34`) `void tick_reset(void)` - /** Docstring: Audio listener table. static tick_slot_t tick_audio_slots[TICK_MAX_AUDIO_LISTENERS];
- `tick_register_audio` (function, `kernel/tick.c:58`) `int tick_register_audio(tick_fn_t fn, void *ctx)` - Docstring: Register an unconditional BSP audio effect.  Returns 0 on success, -1 when the handler is
- `tick_register_desktop` (function, `kernel/tick.c:76`) `int tick_register_desktop(tick_fn_t fn, void *ctx)` - Docstring: Register a gated desktop effect.  Returns 0 on success, -1 when the handler is null or th
- `tick_register_usb` (function, `kernel/tick.c:89`) `int tick_register_usb(tick_fn_t fn, void *ctx)`
- `tick_run_usb` (function, `kernel/tick.c:103`) `void tick_run_usb(void)` - int tick_register_usb(tick_fn_t fn, void *ctx) { if (fn == NULL) { return -1; } if (tick_usb_used <
- `tick_run_audio` (function, `kernel/tick.c:113`) `void tick_run_audio(void)` - return 0; } /** Docstring: Run USB listeners in registration order. void tick_run_usb(void) { int i;
- `tick_run_desktop` (function, `kernel/tick.c:123`) `void tick_run_desktop(void)` - } } /** Docstring: Run audio listeners in registration order. void tick_run_audio(void) { int i; for
- `tick_audio_count` (function, `kernel/tick.c:133`) `int tick_audio_count(void)` - } } /** Docstring: Run desktop listeners in registration order. void tick_run_desktop(void) { int i;
- `tick_desktop_count` (function, `kernel/tick.c:144`) `int tick_desktop_count(void)` - } /** Docstring: Count registered audio listeners. int tick_audio_count(void) { if (tick_audio_used
- `tick_desktop_due` (function, `kernel/tick.c:160`) `int tick_desktop_due(unsigned long long ticks, unsigned interval)` - Docstring: Pure desktop gating predicate.  Returns nonzero when the given tick count falls on a desk
- `CHECK` (macro, `tests/test_tick.c:17`) `#define CHECK(cond, msg)`
- `rec_a` (function, `tests/test_tick.c:24`) `static void rec_a(void *ctx)`
- `rec_b` (function, `tests/test_tick.c:31`) `static void rec_b(void *ctx)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 2
- Cross-boundary resolved imports (EXTRACTED): 1

## Connections

- No cross-community bridges recorded. This community is self-contained.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.67?

## Sources

- `headers/tick.h`
- `kernel/tick.c`
- `tests/test_tick.c`
