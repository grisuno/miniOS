# headers

*Community 13 | 2 files | cohesion 0.50*

## Definition

This community groups 2 file(s) rooted at `headers` with dominant language h (cohesion 0.50). Central symbols: `CHECK`, `RANDMIX_H`, `main`, `popcount64`, `source`. Core file: `tests/test_randmix.c` (3 symbols). Documented purpose: entropy mixer for getrandom (318)..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/randmix.h` | h | utility | 2 | yes |
| `tests/test_randmix.c` | c | testing | 3 | yes |

## Key Symbols

- `RANDMIX_H` (macro, `headers/randmix.h:2`) `#define RANDMIX_H`
- `source` (function, `headers/randmix.h:11`) `* source (all-zero seed) still walks, because the increment is inside  * the mix`
- `CHECK` (macro, `tests/test_randmix.c:16`) `#define CHECK(c, m)`
- `popcount64` (function, `tests/test_randmix.c:18`) `static int popcount64(unsigned long x)`
- `main` (function, `tests/test_randmix.c:24`) `int main(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 1
- Cross-boundary resolved imports (EXTRACTED): 1

## Connections

- No cross-community bridges recorded. This community is self-contained.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.50?

## Sources

- `headers/randmix.h`
- `tests/test_randmix.c`
