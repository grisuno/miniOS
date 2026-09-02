#ifndef AUDIO_H
#define AUDIO_H

/* Unified audio API for MiniOS.
 *
 * Provides a single interface over the two hardware sinks:
 *   - PC speaker (square wave, syscalls 209/210/214)
 *   - Sound Blaster 16 (8-bit mono PCM DMA, syscalls 221/222/224)
 *
 * Ring-3 programs use these wrappers instead of calling raw syscalls.
 * The kernel dispatches to the appropriate hardware backend.
 */

#define AUDIO_RATE_DEFAULT  22050
#define AUDIO_CHANNELS_MONO 1
#define AUDIO_FORMAT_U8     0
#define AUDIO_FORMAT_S16    1

/* Initialize the audio subsystem.  Probes for SB16, resets PC speaker. */
int  audio_init(void);

/* Tone mode: play a square wave at `freq` Hz.  0 = silence. */
void audio_tone(unsigned freq);

/* PCM streaming mode (SB16). */
int  audio_pcm_open(unsigned rate, unsigned channels, unsigned format);
int  audio_pcm_submit(const void *buf, unsigned len);
void audio_pcm_pump(void);
void audio_pcm_close(void);

/* Volume control (PC speaker mute switch). */
void audio_set_volume(unsigned volume);
unsigned audio_get_volume(void);

/* Query hardware presence. */
int audio_sb16_present(void);

#endif /* AUDIO_H */
