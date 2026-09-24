# headers

*Community 8 | 3 files | cohesion 0.67*

## Definition

This community groups 3 file(s) rooted at `headers` with dominant language c (cohesion 0.67). Central symbols: `CHECK`, `TICK_CONFIG_DEFAULT`, `TICK_H`, `TICK_MAX_AUDIO_LISTENERS`, `TICK_MAX_DESKTOP_LISTENERS`, `dummy`, `main`, `rec_a`. Core file: `headers/tick.h` (13 symbols). Documented purpose: Docstring: Tick listener bus contract..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/tick.h` | h | utility | 13 | yes |
| `kernel/tick.c` | c | utility | 9 | yes |
| `tests/test_tick.c` | c | testing | 6 | yes |

## Key Symbols

- `TICK_H` (macro, `headers/tick.h:18`) `#define TICK_H`
- `tick_config_t` (struct, `headers/tick.h:21`) - desktop effect, plus a pure gating predicate for the desktop tick.  Design: fixed-size tables, no he
- `TICK_MAX_AUDIO_LISTENERS` (macro, `headers/tick.h:27`) `#define TICK_MAX_AUDIO_LISTENERS`
- `TICK_MAX_DESKTOP_LISTENERS` (macro, `headers/tick.h:29`) `#define TICK_MAX_DESKTOP_LISTENERS`
- `TICK_CONFIG_DEFAULT` (macro, `headers/tick.h:32`) `#define TICK_CONFIG_DEFAULT`
- `tick_reset` (function, `headers/tick.h:41`) `void tick_reset(void);` - #define TICK_MAX_AUDIO_LISTENERS 8 /** Docstring: Default desktop bus capacity. #define TICK_MAX_DES
- `tick_register_audio` (function, `headers/tick.h:48`) `int tick_register_audio(tick_fn_t fn, void *ctx);` - Docstring: Register an unconditional BSP audio effect.  Returns 0 on success, -1 when the handler is
- `tick_register_desktop` (function, `headers/tick.h:55`) `int tick_register_desktop(tick_fn_t fn, void *ctx);` - Docstring: Register a gated desktop effect.  Returns 0 on success, -1 when the handler is null or th
- `tick_run_audio` (function, `headers/tick.h:58`) `void tick_run_audio(void);` - Docstring: Register a gated desktop effect.  Returns 0 on success, -1 when the handler is null or th
- `tick_run_desktop` (function, `headers/tick.h:61`) `void tick_run_desktop(void);` - Docstring: Register a gated desktop effect.  Returns 0 on success, -1 when the handler is null or th
- `tick_audio_count` (function, `headers/tick.h:64`) `int tick_audio_count(void);` - Docstring: Register a gated desktop effect.  Returns 0 on success, -1 when the handler is null or th
- `tick_desktop_count` (function, `headers/tick.h:67`) `int tick_desktop_count(void);` - table is full. A refusal changes nothing.  int tick_register_desktop(tick_fn_t fn, void *ctx); /** D
- `tick_desktop_due` (function, `headers/tick.h:75`) `int tick_desktop_due(unsigned long long ticks, unsigned interval);` - Docstring: Pure desktop gating predicate.  Returns nonzero when the given tick count falls on a desk
- `tick_slot_t` (struct, `kernel/tick.c:15`) - Docstring: Tick listener bus implementation.  Owns two fixed listener tables behind the tick.h contr
- `tick_reset` (function, `kernel/tick.c:30`) `void tick_reset(void)` - tick_fn_t fn; void *ctx; } tick_slot_t; /** Docstring: Audio listener table. static tick_slot_t tick
- `tick_register_audio` (function, `kernel/tick.c:49`) `int tick_register_audio(tick_fn_t fn, void *ctx)` - Docstring: Register an unconditional BSP audio effect.  Returns 0 on success, -1 when the handler is
- `tick_register_desktop` (function, `kernel/tick.c:67`) `int tick_register_desktop(tick_fn_t fn, void *ctx)` - Docstring: Register a gated desktop effect.  Returns 0 on success, -1 when the handler is null or th
- `tick_run_audio` (function, `kernel/tick.c:81`) `void tick_run_audio(void)` - int tick_register_desktop(tick_fn_t fn, void *ctx) { if (fn == NULL) { return -1; } if (tick_desktop
- `tick_run_desktop` (function, `kernel/tick.c:91`) `void tick_run_desktop(void)` - return 0; } /** Docstring: Run audio listeners in registration order. void tick_run_audio(void) { in
- `tick_audio_count` (function, `kernel/tick.c:101`) `int tick_audio_count(void)` - } } /** Docstring: Run desktop listeners in registration order. void tick_run_desktop(void) { int i;
- `tick_desktop_count` (function, `kernel/tick.c:112`) `int tick_desktop_count(void)` - } /** Docstring: Count registered audio listeners. int tick_audio_count(void) { if (tick_audio_used
- `tick_desktop_due` (function, `kernel/tick.c:128`) `int tick_desktop_due(unsigned long long ticks, unsigned interval)` - Docstring: Pure desktop gating predicate.  Returns nonzero when the given tick count falls on a desk
- `CHECK` (macro, `tests/test_tick.c:17`) `#define CHECK(cond, msg)`
- `rec_a` (function, `tests/test_tick.c:24`) `static void rec_a(void *ctx)`
- `rec_b` (function, `tests/test_tick.c:31`) `static void rec_b(void *ctx)`
- `rec_d` (function, `tests/test_tick.c:38`) `static void rec_d(void *ctx)`
- `dummy` (function, `tests/test_tick.c:47`) `static void dummy(void *ctx)`
- `main` (function, `tests/test_tick.c:52`) `int main(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 2
- Cross-boundary resolved imports (EXTRACTED): 1

## Connections

- [EXTRACTED] depends_on community 0 <-> 8 (strength 0.9): Extracted import edge crosses communities: kernel/sched.c imports headers/tick.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.67?

## Sources

- `headers/tick.h`
- `kernel/tick.c`
- `tests/test_tick.c`
