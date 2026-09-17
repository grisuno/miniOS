# progs/doomgeneric

*Community 2 | 232 files | cohesion 0.98*

## Definition

This community groups 232 file(s) rooted at `progs/doomgeneric` with dominant language c (cohesion 0.98). Central symbols: `AMSTR_FOLLOWOFF`, `AMSTR_FOLLOWON`, `AMSTR_GRIDOFF`, `AMSTR_GRIDON`, `AMSTR_MARKEDSPOT`, `AMSTR_MARKSCLEARED`, `AM_Drawer`, `AM_LevelInit`. Core file: `progs/doomgeneric/d_englsh.h` (286 symbols). Documented purpose: Unified audio API for MiniOS..

## Files

### `progs/doomgeneric` (183 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomgeneric/am_map.c` | c | utility | 87 | yes |

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

### `progs/wl` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/wl/wl_client.h` | h | infrastructure | 5 | yes |

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
| `progs/doomedit/doomedit.c` | c | infrastructure | 108 | yes |

### `progs/file` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/file/file.c` | c | utility | 47 | yes |

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

### `progs/pokemon/minios_stubs` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/pokemon/minios_stubs/SDL.h` | h | testing | 10 | yes |

### `progs/quake2generic` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/quake2generic/q2generic_minios.c` | c | utility | 30 | yes |

*... and 212 more files in this community.*


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

- Internal resolved imports (EXTRACTED): 896
- Cross-boundary resolved imports (EXTRACTED): 15

## Connections

- [EXTRACTED] depends_on community 0 <-> 2 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 4 <-> 2 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports kernel/string.c.
- [EXTRACTED] depends_on community 2 <-> 5 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/doomgeneric_xlib.c imports kernel/time.c.
- [EXTRACTED] depends_on community 6 <-> 2 (strength 0.9): Extracted import edge crosses communities: progs/lua/minios.c imports progs/minios_abi.h.
- [INFERRED] shares_context community 1 <-> 2 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (headers) and community 2 (progs/doomgeneric).
- [INFERRED] shares_context community 2 <-> 3 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 2 (progs/doomgeneric) and community 3 (headers).

## Risks

- [taint high] `mcp/mcp_dbg_driver.py` -> `progs/minios_abi.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `progs/minios_abi.h` via `subprocess` (3 hops)
- [cycle] `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h` -> `progs/doomgeneric/r_data.h`
- [layer strict] `tests/test_freedomui.c` (testing) -> `progs/freedomui/freedomui_minios.c` (presentation)
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:1556` `dmap_build_wad` `side`: `side` assigned at line 1556 but never read afterwards.
- [dataflow DEAD_STORE] `progs/doomedit/doomedit.c:1633` `dmap_build_wad` `dir`: `dir` assigned at line 1633 but never read afterwards.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/d_iwad.c:217` `GetRegistryString` `result`: Result of allocator stored in `result` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/d_iwad.c:346` `CheckSteamGUSPatches` `patch_path`: Result of allocator stored in `patch_path` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/d_iwad.c:425` `CheckDirectoryHasIWAD` `filename`: Result of allocator stored in `filename` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/d_iwad.c:764` `D_FindAllIWADs` `result`: Result of allocator stored in `result` is never checked against NULL.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/doomgeneric.c:8` `dg_Create` `DG_ScreenBuffer`: Result of allocator stored in `DG_ScreenBuffer` is never checked against NULL.
- [dataflow UNINIT_USE] `progs/doomgeneric/doomgeneric_minios.c:211` `DG_Init` `myargc`: `myargc` may be read before initialization (declared line 209).
- [dataflow UNINIT_USE] `progs/doomgeneric/doomgeneric_minios.c:211` `DG_Init` `myargv`: `myargv` may be read before initialization (declared line 210).
- [dataflow DEAD_STORE] `progs/doomgeneric/doomgeneric_minios.c:224` `DG_DrawFrame` `dst`: `dst` assigned at line 224 but never read afterwards.
- [dataflow UNCHECKED_ALLOC] `progs/doomgeneric/doomgeneric_soso.c:144` `DG_Init` `FrameBuffer`: Result of allocator stored in `FrameBuffer` is never checked against NULL.

## Open Questions

- Why do 15 file(s) lack file-level docs (e.g. `progs/doomgeneric/doomgeneric.c`)? What purpose do they serve?
- Can the cycle `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h` be broken with an interface?
- What would break if the most connected file in progs/doomgeneric changed?
- Should progs/doomgeneric be split, given cohesion 0.98?

## Sources

- `headers/audio.h`
- `kernel/string.c`
- `progs/doomedit/doomedit.c`
- `progs/doomgeneric/am_map.c`
- `progs/doomgeneric/am_map.h`
- `progs/doomgeneric/config.h`
- `progs/doomgeneric/d_englsh.h`
- `progs/doomgeneric/d_event.c`
- `progs/doomgeneric/d_event.h`
- `progs/doomgeneric/d_items.c`
- `progs/doomgeneric/d_items.h`
- `progs/doomgeneric/d_iwad.c`
- `progs/doomgeneric/d_iwad.h`
- `progs/doomgeneric/d_loop.c`
- `progs/doomgeneric/d_loop.h`
- `progs/doomgeneric/d_main.c`
- `progs/doomgeneric/d_main.h`
- `progs/doomgeneric/d_mode.c`
- `progs/doomgeneric/d_mode.h`
- `progs/doomgeneric/d_net.c`
- *... and 212 more*
