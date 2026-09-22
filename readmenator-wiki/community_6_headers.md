# headers

*Community 6 | 2 files | cohesion 0.33*

## Definition

This community groups 2 file(s) rooted at `headers` with dominant language h (cohesion 0.33). Central symbols: `CHECK`, `PCM_RING_H`, `lcg_next`, `main`, `pcm_ring_free`, `pcm_ring_init`, `pcm_ring_read`, `pcm_ring_t`. Core file: `tests/test_pcm.c` (9 symbols). Documented purpose: single-producer/single-consumer byte ring for PCM audio..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/pcm_ring.h` | h | utility | 7 | yes |
| `tests/test_pcm.c` | c | testing | 9 | yes |

## Key Symbols

- `PCM_RING_H` (macro, `headers/pcm_ring.h:2`) `#define PCM_RING_H`
- `pcm_ring_t` (struct, `headers/pcm_ring.h:26`)
- `pcm_ring_init` (function, `headers/pcm_ring.h:36`) `static inline void pcm_ring_init(pcm_ring_t *r, unsigned char *buf,`
- `pcm_ring_used` (function, `headers/pcm_ring.h:47`) `static inline unsigned pcm_ring_used(const pcm_ring_t *r)`
- `pcm_ring_free` (function, `headers/pcm_ring.h:51`) `static inline unsigned pcm_ring_free(const pcm_ring_t *r)`
- `pcm_ring_write` (function, `headers/pcm_ring.h:55`) `static inline unsigned pcm_ring_write(pcm_ring_t *r, const unsigned char *src,`
- `pcm_ring_read` (function, `headers/pcm_ring.h:76`) `static inline unsigned pcm_ring_read(pcm_ring_t *r, unsigned char *dst,`
- `CHECK` (macro, `tests/test_pcm.c:21`) `#define CHECK(cond, msg)`
- `t_roundtrip` (function, `tests/test_pcm.c:28`) `static void t_roundtrip(void)`
- `t_wrap` (function, `tests/test_pcm.c:44`) `static void t_wrap(void)`
- `t_overrun` (function, `tests/test_pcm.c:61`) `static void t_overrun(void)`
- `t_underrun` (function, `tests/test_pcm.c:75`) `static void t_underrun(void)`
- `t_zero_cap` (function, `tests/test_pcm.c:91`) `static void t_zero_cap(void)`
- `lcg_next` (function, `tests/test_pcm.c:104`) `static unsigned lcg_next(void)`
- `t_model` (function, `tests/test_pcm.c:109`) `static void t_model(void)`
- `main` (function, `tests/test_pcm.c:144`) `int main(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 1
- Cross-boundary resolved imports (EXTRACTED): 2

## Connections

- [EXTRACTED] depends_on community 0 <-> 6 (strength 0.9): Extracted import edge crosses communities: drivers/pcm2.c imports headers/pcm_ring.h.
- [EXTRACTED] depends_on community 6 <-> 3 (strength 0.9): Extracted import edge crosses communities: tests/test_pcm.c imports kernel/string.c.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.33?

## Sources

- `headers/pcm_ring.h`
- `tests/test_pcm.c`
