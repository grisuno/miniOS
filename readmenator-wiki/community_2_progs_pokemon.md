# progs/pokemon

*Community 2 | 4 files | cohesion 0.43*

## Definition

This community groups 4 file(s) rooted at `progs/pokemon` with dominant language h (cohesion 0.43). Central symbols: `AUDIO_CHANNELS_MONO`, `AUDIO_FORMAT_S16`, `AUDIO_FORMAT_U8`, `AUDIO_H`, `AUDIO_RATE_DEFAULT`, `CHECK`, `FB_ADDR`, `FB_H`. Core file: `progs/pokemon/platform_minios.c` (111 symbols). Documented purpose: Unified audio API for MiniOS..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/audio.h` | h | infrastructure | 18 | yes |
| `progs/minios_png.h` | h | utility | 21 | yes |
| `progs/pokemon/platform_minios.c` | c | data_access | 111 | no |
| `tests/test_minios_png.c` | c | testing | 10 | yes |

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
- `MINIOS_PNG_H` (macro, `progs/minios_png.h:22`) `#define MINIOS_PNG_H`
- `MPNG_FILE_MAX` (macro, `progs/minios_png.h:28`) `#define MPNG_FILE_MAX`
- `MPNG_MAX_DIM` (macro, `progs/minios_png.h:29`) `#define MPNG_MAX_DIM`
- `MPNG_BIG_DIM` (macro, `progs/minios_png.h:33`) `#define MPNG_BIG_DIM`
- `MPNG_PAL_N` (macro, `progs/minios_png.h:34`) `#define MPNG_PAL_N`
- `MPNG_PAL_BYTES` (macro, `progs/minios_png.h:35`) `#define MPNG_PAL_BYTES`
- `MPNG_PATH_MAX` (macro, `progs/minios_png.h:36`) `#define MPNG_PATH_MAX`
- `MPNG_RIGHT_PATH` (macro, `progs/minios_png.h:37`) `#define MPNG_RIGHT_PATH`
- `MPNG_LEFT_N` (macro, `progs/minios_png.h:38`) `#define MPNG_LEFT_N`
- `MPNG_ERR_OK` (macro, `progs/minios_png.h:39`) `#define MPNG_ERR_OK`
- `MPNG_ERR_BOUND` (macro, `progs/minios_png.h:40`) `#define MPNG_ERR_BOUND`
- `MPNG_ERR_EMPTY` (macro, `progs/minios_png.h:41`) `#define MPNG_ERR_EMPTY`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 3
- Cross-boundary resolved imports (EXTRACTED): 4

## Connections

- [EXTRACTED] depends_on community 8 <-> 2 (strength 0.9): Extracted import edge crosses communities: progs/file/file.c imports progs/minios_png.h.
- [EXTRACTED] depends_on community 2 <-> 6 (strength 0.9): Extracted import edge crosses communities: progs/pokemon/platform_minios.c imports kernel/string.c.
- [INFERRED] shares_context community 0 <-> 2 (strength 0.5): Inferred shared context (language c) with no import path between community 0 (headers) and community 2 (progs/pokemon).

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 1 file(s) lack file-level docs (e.g. `progs/pokemon/platform_minios.c`)? What purpose do they serve?
- What would break if the most connected file in progs/pokemon changed?
- Should progs/pokemon be split, given cohesion 0.43?

## Sources

- `headers/audio.h`
- `progs/minios_png.h`
- `progs/pokemon/platform_minios.c`
- `tests/test_minios_png.c`
