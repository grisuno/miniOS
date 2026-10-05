# headers

*Community 11 | 2 files | cohesion 0.33*

## Definition

This community groups 2 file(s) rooted at `headers` with dominant language h (cohesion 0.33). Central symbols: `CHECK`, `KTIME_H`, `ktime_us_from_delta`, `main`, `wall_us_from_parts`. Core file: `headers/ktime.h` (3 symbols). Documented purpose: pure time-conversion helpers shared by the kernel clock.

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/ktime.h` | h | utility | 3 | yes |
| `tests/test_ktime.c` | c | testing | 2 | yes |

## Key Symbols

- `KTIME_H` (macro, `headers/ktime.h:2`) `#define KTIME_H`
- `ktime_us_from_delta` (function, `headers/ktime.h:19`) `static inline unsigned long ktime_us_from_delta(unsigned long delta_ticks,`
- `wall_us_from_parts` (function, `headers/ktime.h:30`) `static inline unsigned long wall_us_from_parts(unsigned long base_sec,` - wall_us_from_parts: wall-clock microseconds from an RTC-anchored base. base_sec is the last seen RTC
- `CHECK` (macro, `tests/test_ktime.c:14`) `#define CHECK(c, m)`
- `main` (function, `tests/test_ktime.c:16`) `int main(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 1
- Cross-boundary resolved imports (EXTRACTED): 2

## Connections

- No cross-community bridges recorded. This community is self-contained.

## Risks

- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `mcp/minios_addons.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `mcp/minios_mcp.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `tools/boot_wl.py` -> `headers/ktime.h` via `subprocess` (2 hops)

## Open Questions

- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.33?

## Sources

- `headers/ktime.h`
- `tests/test_ktime.c`
