#ifndef SB16_H
#define SB16_H

/* Sound Blaster 16 DMA audio driver.  The kernel owns a real PCM audio
 * device (QEMU `-device sb16`) and exposes two sinks on top of a continuous
 * IRQ-driven 8-bit DMA stream:
 *
 *  - tone mode (the default): `sb16_tone` renders a square wave, so the
 *    existing `sys_tone` sink (Doom's MUS/DP note players, the shell, any
 *    ring-0 or ring-3 program) gets real audio output instead of the 1-bit
 *    PC speaker when an SB16 is present.
 *
 *  - PCM mode: `sb16_pcm_open`/`sb16_pcm_submit` stream raw 8-bit PCM from
 *    a ring-3 renderer through the same DMA path.  This is the hook a
 *    Nuked-OPL3 / ADLMIDI FM synth feeds, giving full OPL3-quality audio.
 *
 * Fail-closed: when no SB16 is present the probe returns false and the kernel
 * keeps routing `sys_tone` to the PC speaker; nothing hangs, nothing plays
 * from a phantom device, and a PCM submit with no SB16 is refused. */

#define SB16_PCM_BUF  0x800u   /* per-buffer byte count (2048) */
#define SB16_PCM_RATE 22050u   /* 8-bit unsigned mono sample rate */

int  sb16_init(void);                    /* probe DSP, reset, set rate */
int  sb16_present(void);                 /* 1 once sb16_init probed an SB16 */
void sb16_tone(unsigned freq);           /* 0 = silence; square wave at freq */
void sb16_irq(void);                     /* SB16 IRQ fast path (vector 37) */

void sb16_pcm_open(void);                /* switch sink to PCM streaming */
int  sb16_pcm_submit(const unsigned char *pcm, unsigned len); /* copy+queue */
void sb16_pcm_close(void);               /* back to tone mode / silence */

#endif
