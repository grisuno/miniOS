# progs/src

*Community 3 | 67 files | cohesion 0.69*

## Definition

This community groups 67 file(s) rooted at `progs/src` with dominant language c (cohesion 0.69). Central symbols: `ASCII_BS`, `ASCII_CR`, `ASCII_DEL`, `ASCII_ESC`, `ASCII_TAB`, `AUDIO_CHANNELS_MONO`, `AUDIO_FORMAT_S16`, `AUDIO_FORMAT_U8`. Core file: `progs/vedit/vedit.c` (243 symbols). Documented purpose: Unified audio API for MiniOS..

## Files

### `progs/src` (13 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/src/audio.c` | c | utility | 17 | no |

### `tests` (10 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_file_assoc.c` | c | testing | 10 | yes |

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

### `progs` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/minios_abi.h` | h | utility | 153 | yes |

### `progs/doomgeneric` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomgeneric/doomgeneric_minios.c` | c | utility | 29 | yes |

### `headers` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/audio.h` | h | utility | 18 | yes |

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
- `audio_stream_close` (function, `headers/audio.h:41`) `void audio_stream_close(int id);`
- `audio_stream_submit` (function, `headers/audio.h:42`) `int audio_stream_submit(int id, const void *buf, unsigned len);`
- `audio_stream_volume` (function, `headers/audio.h:43`) `void audio_stream_volume(int id, unsigned char vol);`
- `MINIOS_LEAKCHECK_H` (macro, `headers/leakcheck.h:28`) `#define MINIOS_LEAKCHECK_H`
- `MINIOS_LK_PIPE` (macro, `headers/leakcheck.h:42`) `#define MINIOS_LK_PIPE`
- `MINIOS_LK_PIPE` (macro, `headers/leakcheck.h:44`) `#define MINIOS_LK_PIPE`
- `lk_block_t` (type_alias, `headers/leakcheck.h:49`) `typedef struct lk_block lk_block_t;` - #ifndef MINIOS_LK_KERNEL #include <stdlib.h> #include <stdio.h> #endif #ifndef MINIOS_LK_PIPE #ifdef
- `lk_block` (struct, `headers/leakcheck.h:50`)
- `kmalloc` (function, `headers/leakcheck.h:79`) `extern void *kmalloc(unsigned long size);` - ifdef MINIOS_LK_KERNEL
- `kfree` (function, `headers/leakcheck.h:80`) `extern void kfree(void *ptr);`
- `kprintf` (function, `headers/leakcheck.h:81`) `extern int kprintf(const char *fmt, ...);`
- `MINIOS_LK_RAW_ALLOC` (macro, `headers/leakcheck.h:82`) `#define MINIOS_LK_RAW_ALLOC(sz)`
- `MINIOS_LK_RAW_FREE` (macro, `headers/leakcheck.h:83`) `#define MINIOS_LK_RAW_FREE(p)`
- `MINIOS_LK_RAW_ALLOC` (macro, `headers/leakcheck.h:88`) `#define MINIOS_LK_RAW_ALLOC(sz)`
- `MINIOS_LK_RAW_FREE` (macro, `headers/leakcheck.h:89`) `#define MINIOS_LK_RAW_FREE(p)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 123
- Cross-boundary resolved imports (EXTRACTED): 54

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
- Should progs/src be split, given cohesion 0.69?

## Sources

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
- `progs/minicraft/minicraft.c`
- *... and 47 more*
