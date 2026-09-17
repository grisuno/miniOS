# progs/doomgeneric

*Community 5 | 114 files | cohesion 0.63*

## Definition

This community groups 114 file(s) rooted at `progs/doomgeneric` with dominant language c (cohesion 0.63). Central symbols: `ANG1`, `ANG180`, `ANG1_X`, `ANG270`, `ANG45`, `ANG60`, `ANG90`, `ANGLETOFINESHIFT`. Core file: `progs/minicraft/minicraft.c` (246 symbols). Documented purpose: config.hin.  Generated from configure.ac by autoheader..

## Files

### `progs/doomgeneric` (65 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomgeneric/config.h` | h | infrastructure | 16 | yes |

### `progs/nuklear` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/nuklear/cvm_emit.c` | c | utility | 59 | yes |

### `progs/src` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/src/audio.c` | c | infrastructure | 18 | yes |

### `tests` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_file_assoc.c` | c | testing | 8 | yes |

### `progs/wl` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/wl/wl_client.h` | h | infrastructure | 6 | yes |

### `progs` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/minios_abi.h` | h | utility | 129 | yes |

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
| `progs/doomedit/doomedit.c` | c | infrastructure | 141 | yes |

### `progs/file` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/file/file.c` | c | utility | 72 | yes |

### `progs/freedomui` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/freedomui/freedomui_minios.c` | c | presentation | 47 | yes |

### `progs/lisp` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/lisp/lisp.c` | c | utility | 116 | no |

### `progs/lua` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/lua/lua_main.c` | c | utility | 25 | no |

### `progs/micropython/variants/minios` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/micropython/variants/minios/minios_module.c` | c | utility | 33 | no |

### `progs/minicraft` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/minicraft/minicraft.c` | c | utility | 246 | yes |

### `progs/paint` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/paint/paint.c` | c | utility | 85 | yes |

### `progs/piano` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/piano/piano.c` | c | utility | 87 | yes |

### `progs/pokemon` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/pokemon/platform_minios.c` | c | data_access | 118 | no |

### `progs/pokemon/minios_stubs` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/pokemon/minios_stubs/SDL.h` | h | testing | 10 | yes |

### `progs/quake2generic` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/quake2generic/q2generic_minios.c` | c | utility | 36 | yes |

*... and 94 more files in this community.*


## Key Symbols

- `AUDIO_H` (macro, `headers/audio.h:2`) `#define AUDIO_H`
- `AUDIO_RATE_DEFAULT` (macro, `headers/audio.h:14`) `#define AUDIO_RATE_DEFAULT`
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
- `kstrlen` (function, `kernel/string.c:16`) `unsigned long kstrlen(const char *s)` - string.c -- Kernel string and memory functions.  Pure functions with no dependencies beyond their ow
- `kstrcpy` (function, `kernel/string.c:22`) `char *kstrcpy(char *dst, const char *src)`
- `kstrncpy` (function, `kernel/string.c:28`) `char *kstrncpy(char *dst, const char *src, unsigned long n)`
- `kstrncat` (function, `kernel/string.c:34`) `char *kstrncat(char *dst, const char *src, unsigned long n)`
- `kstrcmp` (function, `kernel/string.c:42`) `int kstrcmp(const char *a, const char *b)`
- `kstrncmp` (function, `kernel/string.c:47`) `int kstrncmp(const char *a, const char *b, unsigned long n)`
- `kstrchr` (function, `kernel/string.c:52`) `char *kstrchr(const char *s, int c)`
- `kstrstr` (function, `kernel/string.c:57`) `char *kstrstr(const char *hay, const char *ndl)`
- `kmemcpy` (function, `kernel/string.c:67`) `void *kmemcpy(void *dst, const void *src, unsigned long n)`
- `kmemset` (function, `kernel/string.c:74`) `void *kmemset(void *dst, int c, unsigned long n)`
- `kmemcmp` (function, `kernel/string.c:80`) `int kmemcmp(const void *a, const void *b, unsigned long n)`
- `kmemmove` (function, `kernel/string.c:86`) `void *kmemmove(void *dst, const void *src, unsigned long n)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 267
- Cross-boundary resolved imports (EXTRACTED): 155

## Connections

- [EXTRACTED] depends_on community 3 <-> 5 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 11 <-> 5 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/am_map.c imports progs/doomgeneric/doomkeys.h.
- [EXTRACTED] depends_on community 12 <-> 5 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_loop.c imports kernel/string.c.
- [EXTRACTED] depends_on community 5 <-> 10 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/doomgeneric_xlib.c imports kernel/time.c.
- [EXTRACTED] depends_on community 13 <-> 5 (strength 0.9): Extracted import edge crosses communities: progs/lua/minios.c imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 4 <-> 5 (strength 0.9): Extracted import edge crosses communities: tests/test_abi.c imports progs/minios_abi.h.

## Risks

- [high] `progs/doomgeneric/i_system.c:274` (in `ZenityAvailable`) C006: Command injection via system() — use execve instead Fix: Avoid shell=True and string-built commands; use argument arrays and input allowlists.
- [high] `progs/doomgeneric/i_system.c:342` (in `M_snprintf`) C006: Command injection via system() — use execve instead Fix: Avoid shell=True and string-built commands; use argument arrays and input allowlists.
- [high] `progs/file/file.c:185` (in `strcpy`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- [high] `progs/file/file.c:186` (in `strcpy`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- [high] `progs/file/file.c:398` (in `nk_label`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- [high] `progs/file/file.c:403` (in `nk_label`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- [high] `progs/file/file.c:408` (in `nk_label`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- [high] `progs/file/file.c:413` (in `nk_label`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- [high] `progs/file/file.c:467` (in `file_selftest`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- [high] `progs/file/file.c:468` (in `file_selftest`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- [high] `progs/file/file.c:469` (in `file_selftest`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- [high] `progs/file/file.c:470` (in `file_selftest`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- [high] `progs/file/file.c:471` (in `file_selftest`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- [high] `progs/file/file.c:472` (in `file_selftest`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.
- [high] `progs/file/file.c:544` (in `nk_theme_apply`) C001: Buffer overflow risk: strcpy — use strncpy or snprintf instead Fix: Use bounded functions (strncpy, snprintf) with explicit sizes and NUL termination.

## Open Questions

- Why do 8 file(s) lack file-level docs (e.g. `progs/doomgeneric/dummy.c`)? What purpose do they serve?
- What would break if the most connected file in progs/doomgeneric changed?
- Should progs/doomgeneric be split, given cohesion 0.63?

## Sources

- `headers/audio.h`
- `kernel/string.c`
- `progs/doomedit/doomedit.c`
- `progs/doomgeneric/config.h`
- `progs/doomgeneric/d_iwad.c`
- `progs/doomgeneric/d_iwad.h`
- `progs/doomgeneric/d_mode.c`
- `progs/doomgeneric/d_mode.h`
- `progs/doomgeneric/d_textur.h`
- `progs/doomgeneric/deh_str.h`
- `progs/doomgeneric/doomfeatures.h`
- `progs/doomgeneric/doomgeneric.c`
- `progs/doomgeneric/doomgeneric.h`
- `progs/doomgeneric/doomgeneric_minios.c`
- `progs/doomgeneric/doomgeneric_sdl.c`
- `progs/doomgeneric/doomgeneric_soso.c`
- `progs/doomgeneric/doomgeneric_sosox.c`
- `progs/doomgeneric/doomgeneric_win.c`
- `progs/doomgeneric/doomgeneric_xlib.c`
- `progs/doomgeneric/doomkeys.h`
- *... and 94 more*
