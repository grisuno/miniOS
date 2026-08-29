#ifndef SB16_H
#define SB16_H

/* Sound Blaster 16 DMA audio driver contract.
 *
 * The kernel owns a real PCM audio device (QEMU `-device sb16`) and exposes
 * two sinks over a continuous IRQ-driven 8-bit DMA stream:
 *
 *  - tone mode (default): `sb16_tone` renders a square wave so the existing
 *    `sys_tone` sink (Doom's note players, the shell, any program) gets real
 *    audio instead of the 1-bit PC speaker when an SB16 is present.
 *
 *  - PCM mode: `sb16_pcm_open`/`sb16_pcm_submit` stream raw 8-bit PCM from a
 *    ring-3 renderer through the same DMA path.  This is the hook a synth
 *    renderer feeds, giving full-quality audio.
 *
 * DMA completion is signalled by the SB16 interrupt (IRQ5, vector 37) AND by
 * a timer-ISR watchdog (`sb16_poll`).  The interrupt is the precise fast
 * path; the watchdog re-arms on elapsed guest time when the interrupt is
 * missed or delayed, and the shared re-arm gate rate-limits both paths so a
 * fast host audio backend can never wedge the ring or trigger an interrupt
 * storm.  Without the watchdog the 7-slot ring fills once and every later
 * submit is refused (observed on QEMU backends that never consume), which
 * deadens the audio path.
 *
 * Fail-closed: when no SB16 is present the probe returns false and the kernel
 * keeps routing `sys_tone` to the PC speaker; a PCM submit with no SB16 is
 * refused, and a submit that would not fit the ring is refused (never
 * overwrites a slot the DMA may still be reading). */

#define SB16_PCM_BUF      0x800u   /* bytes per DMA buffer (2048) */
#define SB16_PCM_RATE     22050u   /* 8-bit unsigned mono sample rate */
#define SB16_SLOTS        8u       /* DMA ring slots, one is permanent silence */
#define SB16_RING_CAP     (SB16_SLOTS - 1u)
#define SB16_ARM_PERIOD_MS \
    ((unsigned)((SB16_PCM_BUF * 1000u + SB16_PCM_RATE - 1u) / SB16_PCM_RATE))

typedef struct {
    unsigned long irq_arms;   /* re-arms granted on the IRQ fast path */
    unsigned long poll_arms;  /* re-arms granted by the timer watchdog */
    unsigned long submits;    /* successful pcm_submit calls */
    unsigned long drops;      /* pcm_submit calls refused (ring full / bad) */
} sb16_counters_t;

int sb16_init(void);
int sb16_present(void);
void sb16_tone(unsigned freq);
void sb16_irq(void);
void sb16_poll(void);

void sb16_pcm_open(void);
int  sb16_pcm_submit(const unsigned char *pcm, unsigned len);
void sb16_pcm_close(void);

unsigned sb16_ring_free(void);
int      sb16_mode_active(void);

void sb16_counters(sb16_counters_t *out);

#endif
