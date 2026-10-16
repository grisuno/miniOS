# progs/src

*Community 2 | 86 files | cohesion 0.72*

## Definition

This community groups 86 file(s) rooted at `tests` with dominant language c (cohesion 0.72). Central symbols: `ABI_BAD_FORMAT`, `ABI_CHECKSUM_MISMATCH`, `ABI_H`, `ABI_MANIFEST_MAX`, `ABI_MANIFEST_NAME`, `ABI_NO_MANIFEST`, `ABI_OK`, `ABI_VERSION_MISMATCH`. Core file: `progs/vedit/vedit.c` (245 symbols). Documented purpose: Docstring: abi.h -- Boot-time ABI manifest gate contract..

## Files

### `tests` (17 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_abi.c` | c | testing | 2 | yes |

### `progs/src` (16 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/src/apsse.c` | c | utility | 15 | yes |

### `headers` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/abi.h` | h | utility | 10 | yes |

### `progs/nuklear` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/nuklear/cvm_emit.c` | c | utility | 56 | yes |

### `progs/freedomui` (5 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/freedomui/freedomui_minios.c` | c | utility | 42 | yes |

### `progs/wl` (5 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/wl/wl_client.h` | h | infrastructure | 5 | yes |

### `kernel` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/abi.c` | c | utility | 3 | yes |

### `progs` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/minios_abi.h` | h | utility | 156 | yes |

### `progs/doomgeneric` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomgeneric/doomgeneric_minios.c` | c | utility | 29 | yes |

### `progs/file` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/file/file.c` | c | utility | 65 | yes |

### `progs/lua` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/lua/lua_main.c` | c | utility | 7 | no |

### `progs/doomedit` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomedit/doomedit.c` | c | utility | 108 | yes |

### `progs/lisp` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/lisp/lisp.c` | c | utility | 105 | no |

### `progs/micropython/variants/minios` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/micropython/variants/minios/minios_module.c` | c | utility | 21 | no |

### `progs/micropython/variants/minios/lib` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/micropython/variants/minios/lib/hello.py` | py | utility | 0 | yes |

### `progs/minicraft` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/minicraft/minicraft.c` | c | utility | 237 | yes |

### `progs/paint` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/paint/paint.c` | c | utility | 53 | yes |

### `progs/piano` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/piano/piano.c` | c | utility | 65 | yes |

### `progs/pokemon` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/pokemon/platform_minios.c` | c | utility | 111 | no |

### `progs/quake2generic` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/quake2generic/snddma_minios.c` | c | utility | 16 | yes |

*... and 66 more files in this community.*


## Key Symbols

- `ABI_H` (macro, `headers/abi.h:14`) `#define ABI_H`
- `ABI_OK` (macro, `headers/abi.h:16`) `#define ABI_OK`
- `ABI_NO_MANIFEST` (macro, `headers/abi.h:17`) `#define ABI_NO_MANIFEST`
- `ABI_BAD_FORMAT` (macro, `headers/abi.h:18`) `#define ABI_BAD_FORMAT`
- `ABI_VERSION_MISMATCH` (macro, `headers/abi.h:19`) `#define ABI_VERSION_MISMATCH`
- `ABI_CHECKSUM_MISMATCH` (macro, `headers/abi.h:20`) `#define ABI_CHECKSUM_MISMATCH`
- `ABI_MANIFEST_NAME` (macro, `headers/abi.h:22`) `#define ABI_MANIFEST_NAME`
- `ABI_MANIFEST_MAX` (macro, `headers/abi.h:23`) `#define ABI_MANIFEST_MAX`
- `abi_verify` (function, `headers/abi.h:25`) `int abi_verify(const char *text, long version, unsigned long checksum);`
- `abi_check_manifest` (function, `headers/abi.h:28`) `int abi_check_manifest(void);` - ifndef ABI_HOST_TEST
- `kmalloc` (function, `headers/arena.h:3`) `* * A bump arena serves one kmalloc (kernel) or malloc (ring-3) with pointer * b`
- `kfree` (function, `headers/arena.h:25`) `* kfree(back);`
- `MINIOS_ARENA_H` (macro, `headers/arena.h:33`) `#define MINIOS_ARENA_H`
- `ARENA_DEFAULT_ALIGN` (macro, `headers/arena.h:38`) `#define ARENA_DEFAULT_ALIGN`
- `minios_arena` (struct, `headers/arena.h:41`) - Alignment defaults to 8 bytes when the caller passes 0. Every size sum is overflow checked and fails
- `arena_init` (function, `headers/arena.h:48`) `static inline void arena_init(arena_t *a, void *block, size_t size)` - #include <stddef.h> /** Docstring: default borrow alignment when the caller passes align 0. #define
- `arena_align_up` (function, `headers/arena.h:62`) `static inline size_t arena_align_up(size_t n, size_t align)` - static inline void arena_init(arena_t *a, void *block, size_t size) { if (!a) return; if (!block \|\|
- `arena_bytes_for` (function, `headers/arena.h:74`) `static inline size_t arena_bytes_for(size_t count, size_t elem_size)` - /** Docstring: round n up to align, 0 on overflow or non-power-of-two align. static inline size_t ar
- `arena_alloc` (function, `headers/arena.h:81`) `static inline void *arena_alloc(arena_t *a, size_t size, size_t align)` - mask = align - 1; if (n > (size_t)-1 - mask) return 0; up = (n + mask) & ~mask; return up; } /** Doc
- `arena_used` (function, `headers/arena.h:95`) `static inline size_t arena_used(const arena_t *a)` - static inline void *arena_alloc(arena_t *a, size_t size, size_t align) { size_t off; size_t up; if (
- `arena_free_bytes` (function, `headers/arena.h:101`) `static inline size_t arena_free_bytes(const arena_t *a)` - if (up == 0 && off != 0) return 0; if (up > (size_t)(a->end - a->base)) return 0; if (size > (size_t
- `arena_reset` (function, `headers/arena.h:107`) `static inline void arena_reset(arena_t *a)` - /** Docstring: bytes borrowed so far, 0 for a null or empty arena. static inline size_t arena_used(c
- `arena_checkpoint` (function, `headers/arena.h:113`) `static inline size_t arena_checkpoint(const arena_t *a)` - /** Docstring: bytes still borrowable, 0 for a null or empty arena. static inline size_t arena_free_
- `arena_rewind` (function, `headers/arena.h:119`) `static inline int arena_rewind(arena_t *a, size_t checkpoint)` - /** Docstring: rewind the scope to empty without releasing the backing block. static inline void are
- `arena_contains` (function, `headers/arena.h:128`) `static inline int arena_contains(const arena_t *a, const void *ptr)` - if (!a \|\| !a->base) return 0; return (size_t)(a->cur - a->base); } /** Docstring: rewind to a checkp
- `AUDIO_H` (macro, `headers/audio.h:2`) `#define AUDIO_H`
- `AUDIO_RATE_DEFAULT` (macro, `headers/audio.h:15`) `#define AUDIO_RATE_DEFAULT`
- `AUDIO_CHANNELS_MONO` (macro, `headers/audio.h:16`) `#define AUDIO_CHANNELS_MONO`
- `AUDIO_FORMAT_U8` (macro, `headers/audio.h:17`) `#define AUDIO_FORMAT_U8`
- `AUDIO_FORMAT_S16` (macro, `headers/audio.h:18`) `#define AUDIO_FORMAT_S16`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 142
- Cross-boundary resolved imports (EXTRACTED): 55

## Connections

- [EXTRACTED] depends_on community 0 <-> 2 (strength 0.9): Extracted import edge crosses communities: drivers/pcm2.c imports headers/pcm_ring.h.
- [EXTRACTED] depends_on community 4 <-> 2 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports kernel/string.c.
- [EXTRACTED] depends_on community 1 <-> 2 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_iwad.c imports kernel/string.c.
- [EXTRACTED] depends_on community 6 <-> 2 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_loop.c imports kernel/string.c.
- [EXTRACTED] depends_on community 3 <-> 2 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/doomdef.h imports kernel/string.c.
- [INFERRED] shares_context community 2 <-> 5 (strength 0.5): Inferred shared context (layer utility) with no import path between community 2 (progs/src) and community 5 (headers: vga_fb).

## Risks

- [layer strict] `tests/test_httpd.c` (testing) -> `headers/httpd.h` (presentation)
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:1556` `dmap_build_wad` `side`: `side` assigned at line 1556 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:1633` `dmap_build_wad` `dir`: `dir` assigned at line 1633 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:2145` `dmap_selftest` `mrgb`: `mrgb` assigned at line 2145 but never read afterwards.
- [dataflow UNINIT_USE] `progs/doomgeneric/doomgeneric_minios.c:235` `DG_Init` `myargc`: `myargc` may be read before initialization (declared line 233).
- [dataflow UNINIT_USE] `progs/doomgeneric/doomgeneric_minios.c:235` `DG_Init` `myargv`: `myargv` may be read before initialization (declared line 234).
- [dataflow DEAD_STORE] `progs/doomgeneric/doomgeneric_minios.c:251` `DG_DrawFrame` `dst`: `dst` assigned at line 251 but never read afterwards.

## Open Questions

- Why do 8 file(s) lack file-level docs (e.g. `progs/lisp/lisp.c`)? What purpose do they serve?
- What would break if the most connected file in progs/src changed?
- Should progs/src be split, given cohesion 0.72?

## Sources

- `headers/abi.h`
- `headers/arena.h`
- `headers/audio.h`
- `headers/httpd.h`
- `headers/leakcheck.h`
- `headers/pcm_ring.h`
- `headers/seccomp_bpf.h`
- `headers/sign.h`
- `kernel/abi.c`
- `kernel/ed25519.c`
- `kernel/seccomp_bpf.c`
- `kernel/string.c`
- `progs/doomedit/doomedit.c`
- `progs/doomgeneric/doomgeneric_minios.c`
- `progs/doomgeneric/memio.c`
- `progs/doomgeneric/memio.h`
- `progs/file/file.c`
- `progs/file/file_assoc.h`
- `progs/freedomui/freedomui_minios.c`
- `progs/freedomui/media_unavailable.c`
- *... and 66 more*
