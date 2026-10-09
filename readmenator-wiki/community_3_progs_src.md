# progs/src

*Community 3 | 67 files | cohesion 0.70*

## Definition

This community groups 67 file(s) rooted at `progs/src` with dominant language c (cohesion 0.70). Central symbols: `ARENA_DEFAULT_ALIGN`, `ASCII_BS`, `ASCII_CR`, `ASCII_DEL`, `ASCII_ESC`, `ASCII_TAB`, `AUDIO_CHANNELS_MONO`, `AUDIO_FORMAT_S16`. Core file: `progs/vedit/vedit.c` (243 symbols). Documented purpose: Docstring: bump arena for MiniOS, kernel and ring-3 alike..

## Files

### `progs/src` (11 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/src/audio.c` | c | utility | 17 | no |

### `tests` (11 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_arena.c` | c | testing | 2 | yes |

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

### `headers` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/arena.h` | h | utility | 15 | yes |

### `progs` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/minios_abi.h` | h | utility | 153 | yes |

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

### `kernel` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/string.c` | c | utility | 13 | yes |

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

*... and 47 more files in this community.*


## Key Symbols

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
- `audio_init` (function, `headers/audio.h:21`) `int audio_init(void);` - PC speaker (square wave, syscalls 209/210/214) - Sound Blaster 16 (8-bit mono PCM DMA, syscalls 221/
- `audio_tone` (function, `headers/audio.h:24`) `void audio_tone(unsigned freq);` - Ring-3 programs use these wrappers instead of calling raw syscalls. The kernel dispatches to the app
- `audio_pcm_open` (function, `headers/audio.h:27`) `int audio_pcm_open(unsigned rate, unsigned channels, unsigned format);` - #define AUDIO_RATE_DEFAULT  22050 #define AUDIO_CHANNELS_MONO 1 #define AUDIO_FORMAT_U8     0 #defin
- `audio_pcm_submit` (function, `headers/audio.h:28`) `int audio_pcm_submit(const void *buf, unsigned len);`
- `audio_pcm_pump` (function, `headers/audio.h:29`) `void audio_pcm_pump(void);`
- `audio_pcm_close` (function, `headers/audio.h:30`) `void audio_pcm_close(void);`
- `audio_set_volume` (function, `headers/audio.h:33`) `void audio_set_volume(unsigned volume);` - /* Initialize the audio subsystem.  Probes for SB16, resets PC speaker. int  audio_init(void); /* To
- `audio_get_volume` (function, `headers/audio.h:34`) `unsigned audio_get_volume(void);`
- `audio_sb16_present` (function, `headers/audio.h:37`) `int audio_sb16_present(void);` - /* Tone mode: play a square wave at `freq` Hz.  0 = silence. void audio_tone(unsigned freq); /* PCM
- `audio_stream_open` (function, `headers/audio.h:40`) `int audio_stream_open(void);` - /* PCM streaming mode (SB16). int  audio_pcm_open(unsigned rate, unsigned channels, unsigned format)

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 123
- Cross-boundary resolved imports (EXTRACTED): 53

## Connections

- [EXTRACTED] depends_on community 0 <-> 3 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 6 <-> 3 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports kernel/string.c.
- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_iwad.c imports kernel/string.c.
- [EXTRACTED] depends_on community 7 <-> 3 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_loop.c imports kernel/string.c.
- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/doomdef.h imports kernel/string.c.
- [EXTRACTED] depends_on community 4 <-> 3 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/doomgeneric_xlib.c imports kernel/string.c.

## Risks

- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:1556` `dmap_build_wad` `side`: `side` assigned at line 1556 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:1633` `dmap_build_wad` `dir`: `dir` assigned at line 1633 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:2145` `dmap_selftest` `mrgb`: `mrgb` assigned at line 2145 but never read afterwards.
- [dataflow UNINIT_USE] `progs/doomgeneric/doomgeneric_minios.c:235` `DG_Init` `myargc`: `myargc` may be read before initialization (declared line 233).
- [dataflow UNINIT_USE] `progs/doomgeneric/doomgeneric_minios.c:235` `DG_Init` `myargv`: `myargv` may be read before initialization (declared line 234).
- [dataflow DEAD_STORE] `progs/doomgeneric/doomgeneric_minios.c:251` `DG_DrawFrame` `dst`: `dst` assigned at line 251 but never read afterwards.

## Open Questions

- Why do 8 file(s) lack file-level docs (e.g. `progs/lisp/lisp.c`)? What purpose do they serve?
- What would break if the most connected file in progs/src changed?
- Should progs/src be split, given cohesion 0.70?

## Sources

- `headers/arena.h`
- `headers/audio.h`
- `headers/leakcheck.h`
- `kernel/string.c`
- `progs/doomedit/doomedit.c`
- `progs/doomgeneric/doomgeneric_minios.c`
- `progs/doomgeneric/memio.c`
- `progs/doomgeneric/memio.h`
- `progs/file/file.c`
- `progs/file/file_assoc.h`
- `progs/freedomui/freedomui_minios.c`
- `progs/freedomui/media_unavailable.c`
- `progs/freedomui/platform_minios.c`
- `progs/freedomui/ps2_keymap.c`
- `progs/freedomui/ps2_keymap.h`
- `progs/lisp/lisp.c`
- `progs/lua/lua_main.c`
- `progs/lua/minios.c`
- `progs/micropython/variants/minios/lib/hello.py`
- `progs/micropython/variants/minios/minios_module.c`
- *... and 47 more*
