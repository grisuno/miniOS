# headers/drivers

*Community 3 | 2 files | cohesion 0.33*

## Definition

This community groups 2 file(s) rooted at `headers/drivers` with dominant language h (cohesion 0.33). Central symbols: `CHECK`, `MODIFIERS_H`, `MOD_ALT`, `MOD_ALTGR`, `MOD_CTRL`, `MOD_SHIFT`, `MOD_SUPER`, `main`. Core file: `headers/drivers/modifiers.h` (11 symbols). Documented purpose: Docstring: Unified modifier tracking for cooked and raw paths..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/drivers/modifiers.h` | h | infrastructure | 11 | yes |
| `tests/test_modifiers.c` | c | testing | 2 | no |

## Key Symbols

- `MODIFIERS_H` (macro, `headers/drivers/modifiers.h:2`) `#define MODIFIERS_H`
- `modifier_state_t` (struct, `headers/drivers/modifiers.h:5`) - #ifndef MODIFIERS_H #define MODIFIERS_H /** Docstring: Unified modifier tracking for cooked and raw
- `modifier_keys_t` (struct, `headers/drivers/modifiers.h:14`) - #ifndef MODIFIERS_H #define MODIFIERS_H /** Docstring: Unified modifier tracking for cooked and raw
- `MOD_SHIFT` (macro, `headers/drivers/modifiers.h:24`) `#define MOD_SHIFT`
- `MOD_CTRL` (macro, `headers/drivers/modifiers.h:25`) `#define MOD_CTRL`
- `MOD_ALT` (macro, `headers/drivers/modifiers.h:26`) `#define MOD_ALT`
- `MOD_ALTGR` (macro, `headers/drivers/modifiers.h:27`) `#define MOD_ALTGR`
- `MOD_SUPER` (macro, `headers/drivers/modifiers.h:28`) `#define MOD_SUPER`
- `modifiers_init` (function, `headers/drivers/modifiers.h:31`) `static inline void modifiers_init(modifier_state_t *st)` - int ctrl_l; int alt_l; int alt_r; int super_l; int super_r; } modifier_keys_t; #define MOD_SHIFT (1
- `modifiers_update` (function, `headers/drivers/modifiers.h:42`) `static inline int modifiers_update(const modifier_keys_t *keys,` - #define MOD_SUPER (1 << 4) /** Docstring: Clear every modifier, shell reset path. static inline void
- `modifiers_match` (function, `headers/drivers/modifiers.h:76`) `static inline int modifiers_match(const modifier_state_t *st, int mask)` - return 0; } if (code == keys->alt_r) { st->altgr = pressed; return 1; } if (code == keys->super_l \|\|
- `CHECK` (macro, `tests/test_modifiers.c:9`) `#define CHECK(cond, msg)`
- `main` (function, `tests/test_modifiers.c:16`) `int main(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 1
- Cross-boundary resolved imports (EXTRACTED): 2

## Connections

- [EXTRACTED] depends_on community 0 <-> 3 (strength 0.9): Extracted import edge crosses communities: drivers/kbd.c imports headers/drivers/modifiers.h.
- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: headers/wm_events.h imports headers/drivers/modifiers.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 1 file(s) lack file-level docs (e.g. `tests/test_modifiers.c`)? What purpose do they serve?
- What would break if the most connected file in headers/drivers changed?
- Should headers/drivers be split, given cohesion 0.33?

## Sources

- `headers/drivers/modifiers.h`
- `tests/test_modifiers.c`
