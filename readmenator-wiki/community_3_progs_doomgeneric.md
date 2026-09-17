# progs/doomgeneric

*Community 3 | 59 files | cohesion 0.69*

## Definition

This community groups 59 file(s) rooted at `progs/doomgeneric` with dominant language c (cohesion 0.69). Central symbols: `AUDIO_CHANNELS_MONO`, `AUDIO_FORMAT_S16`, `AUDIO_FORMAT_U8`, `AUDIO_H`, `AUDIO_RATE_DEFAULT`, `AllocTracker`, `BACKBUF`, `BEZIER_PAD`. Core file: `progs/minicraft/minicraft.c` (233 symbols). Documented purpose: Unified audio API for MiniOS..

## Files

### `progs/doomgeneric` (9 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomgeneric/doomgeneric.c` | c | utility | 1 | no |

### `progs/nuklear` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/nuklear/cvm_emit.c` | c | utility | 56 | yes |

### `progs/src` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/src/audio.c` | c | infrastructure | 17 | no |

### `tests` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_file_assoc.c` | c | testing | 6 | yes |

### `progs/wl` (5 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/wl/wl_client.h` | h | infrastructure | 5 | yes |

### `progs` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/minios_abi.h` | h | utility | 129 | yes |

### `progs/file` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/file/file.c` | c | utility | 46 | yes |

### `headers` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/audio.h` | h | infrastructure | 18 | yes |

### `kernel` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/string.c` | c | utility | 13 | yes |

### `progs/doomedit` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomedit/doomedit.c` | c | infrastructure | 108 | yes |

### `progs/freedomui` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/freedomui/freedomui_minios.c` | c | presentation | 42 | yes |

### `progs/lisp` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/lisp/lisp.c` | c | utility | 105 | no |

### `progs/lua` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/lua/lua_main.c` | c | utility | 7 | no |

### `progs/micropython/variants/minios` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/micropython/variants/minios/minios_module.c` | c | utility | 21 | no |

### `progs/minicraft` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/minicraft/minicraft.c` | c | utility | 233 | yes |

### `progs/paint` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/paint/paint.c` | c | utility | 53 | yes |

### `progs/piano` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/piano/piano.c` | c | utility | 60 | yes |

### `progs/pokemon` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/pokemon/platform_minios.c` | c | data_access | 105 | no |

### `progs/quake2generic` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/quake2generic/q2generic_minios.c` | c | utility | 30 | yes |

### `progs/tls_u` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/tls_u/tls_u_port.c` | c | utility | 15 | yes |

*... and 39 more files in this community.*


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
- `kstrlen` (function, `kernel/string.c:17`) `unsigned long kstrlen(const char *s)`
- `kstrcpy` (function, `kernel/string.c:23`) `char *kstrcpy(char *dst, const char *src)`
- `kstrncpy` (function, `kernel/string.c:29`) `char *kstrncpy(char *dst, const char *src, unsigned long n)`
- `kstrncat` (function, `kernel/string.c:35`) `char *kstrncat(char *dst, const char *src, unsigned long n)`
- `kstrcmp` (function, `kernel/string.c:43`) `int kstrcmp(const char *a, const char *b)`
- `kstrncmp` (function, `kernel/string.c:48`) `int kstrncmp(const char *a, const char *b, unsigned long n)`
- `kstrchr` (function, `kernel/string.c:53`) `char *kstrchr(const char *s, int c)`
- `kstrstr` (function, `kernel/string.c:58`) `char *kstrstr(const char *hay, const char *ndl)`
- `kmemcpy` (function, `kernel/string.c:68`) `void *kmemcpy(void *dst, const void *src, unsigned long n)`
- `kmemset` (function, `kernel/string.c:75`) `void *kmemset(void *dst, int c, unsigned long n)`
- `kmemcmp` (function, `kernel/string.c:81`) `int kmemcmp(const void *a, const void *b, unsigned long n)`
- `kmemmove` (function, `kernel/string.c:87`) `void *kmemmove(void *dst, const void *src, unsigned long n)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 111
- Cross-boundary resolved imports (EXTRACTED): 52

## Connections

- [EXTRACTED] depends_on community 0 <-> 3 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 9 <-> 3 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_iwad.c imports kernel/string.c.
- [EXTRACTED] depends_on community 3 <-> 8 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/doomgeneric_xlib.c imports kernel/time.c.
- [EXTRACTED] depends_on community 10 <-> 3 (strength 0.9): Extracted import edge crosses communities: progs/lua/minios.c imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: tests/test_abi.c imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: tests/test_driver.c imports kernel/string.c.

## Risks

- [taint high] `mcp/mcp_dbg_driver.py` -> `progs/minios_abi.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `progs/minios_abi.h` via `subprocess` (3 hops)
- [layer strict] `tests/test_freedomui.c` (testing) -> `progs/freedomui/freedomui_minios.c` (presentation)
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:1556` `dmap_build_wad` `side`: `side` assigned at line 1556 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:1633` `dmap_build_wad` `dir`: `dir` assigned at line 1633 but never read afterwards.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/doomgeneric.c:8` `dg_Create` `DG_ScreenBuffer`: Result of allocator stored in `DG_ScreenBuffer` is never checked against NULL.
- [dataflow UNINIT_USE] `progs/doomgeneric/doomgeneric_minios.c:211` `DG_Init` `myargc`: `myargc` may be read before initialization (declared line 209).
- [dataflow UNINIT_USE] `progs/doomgeneric/doomgeneric_minios.c:211` `DG_Init` `myargv`: `myargv` may be read before initialization (declared line 210).
- [dataflow DEAD_STORE] `progs/doomgeneric/doomgeneric_minios.c:224` `DG_DrawFrame` `dst`: `dst` assigned at line 224 but never read afterwards.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/doomgeneric_soso.c:144` `DG_Init` `FrameBuffer`: Result of allocator stored in `FrameBuffer` is never checked against NULL.

## Open Questions

- Why do 11 file(s) lack file-level docs (e.g. `progs/doomgeneric/doomgeneric.c`)? What purpose do they serve?
- What would break if the most connected file in progs/doomgeneric changed?
- Should progs/doomgeneric be split, given cohesion 0.69?

## Sources

- `headers/audio.h`
- `kernel/string.c`
- `progs/doomedit/doomedit.c`
- `progs/doomgeneric/doomgeneric.c`
- `progs/doomgeneric/doomgeneric.h`
- `progs/doomgeneric/doomgeneric_minios.c`
- `progs/doomgeneric/doomgeneric_soso.c`
- `progs/doomgeneric/doomgeneric_sosox.c`
- `progs/doomgeneric/doomgeneric_win.c`
- `progs/doomgeneric/doomgeneric_xlib.c`
- `progs/doomgeneric/memio.c`
- `progs/doomgeneric/memio.h`
- `progs/file/file.c`
- `progs/file/file_assoc.h`
- `progs/freedomui/freedomui_minios.c`
- `progs/lisp/lisp.c`
- `progs/lua/lua_main.c`
- `progs/micropython/variants/minios/minios_module.c`
- `progs/minicraft/minicraft.c`
- `progs/minios_abi.h`
- *... and 39 more*
