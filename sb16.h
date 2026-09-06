#ifndef SB16_H
#define SB16_H

/* Sound Blaster 16 DMA audio driver contract.
 *
 * The kernel owns a real PCM audio device (QEMU `-device sb16`) and exposes
 * a multicanal mixer over a continuous IRQ-driven 8-bit DMA stream:
 *
 *  - tone mode (default): `sb16_tone` renders a square wave so the existing
 *    `sys_tone` sink (Doom's note players, the shell, any program) gets real
 *    audio instead of the 1-bit PC speaker when an SB16 is present.
 *
 *  - PCM mixer mode: up to SB16_STREAMS concurrent streams, each with its
 *    own ring buffer and volume.  `sb16_mix_all` sums all active streams
 *    into a mix buffer that feeds the DMA ring.  The legacy
 *    `sb16_pcm_open`/`sb16_pcm_submit` API is preserved as stream 0 for
 *    backward compatibility.
 *
 * DMA completion is signalled by the SB16 interrupt (IRQ5, vector 37) AND by
 * a timer-ISR watchdog (`sb16_poll`).  The interrupt is the precise fast
 * path; the watchdog re-arms on elapsed guest time when the interrupt is
 * missed or delayed, and the shared re-arm gate rate-limits both paths so a
 * fast host audio backend can never wedge the ring or trigger an interrupt
 * storm.  Without the watchdog the 7-slot ring fills once and every later
 * submit is refused, deadening the audio path.
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

/* Per-stream ring buffer.  Each stream gets SB16_STREAM_BUF bytes of
 * kernel-side buffering so multiple producers never interfere.  At 22050 Hz
 * 8-bit mono that is ~366 ms per stream. */
#define SB16_STREAMS      4u       /* max concurrent mixer streams */
#define SB16_STREAM_BUF   (SB16_PCM_BUF * 4u)  /* 8192 bytes per stream */

/* Mixer stream state. */
typedef struct {
    int active;             /* stream is open */
    unsigned char *ring;    /* per-stream ring buffer (SB16_STREAM_BUF bytes) */
    unsigned head;          /* write position (bytes) */
    unsigned tail;          /* read position (bytes) */
    unsigned count;         /* bytes available */
    unsigned char volume;   /* 0..255 (255 = full volume, 128 = unity) */
} sb16_stream_t;

typedef struct {
    unsigned long irq_arms;   /* re-arms granted on the IRQ fast path */
    unsigned long poll_arms;  /* re-arms granted by the timer watchdog */
    unsigned long submits;    /* successful pcm_submit calls */
    unsigned long drops;      /* pcm_submit calls refused (ring full / bad) */
    unsigned long stalls;     /* DMA needed data but kernel ring was empty */
    unsigned long pump_fills; /* pump calls that moved data to DMA */
    unsigned long mixes;      /* sb16_mix_all calls */
} sb16_counters_t;

int sb16_init(void);
int sb16_present(void);
void sb16_tone(unsigned freq);
void sb16_irq(void);
void sb16_poll(void);

/* Legacy single-stream API (maps to mixer stream 0: pcm_open allocates it,
 * pcm_submit forwards into it, pcm_close releases it). */
void sb16_pcm_open(void);
int  sb16_pcm_submit(const unsigned char *pcm, unsigned len);
void sb16_pcm_close(void);
void sb16_pump(void);

/* Mixer stream API. */
int  sb16_stream_open(void);
void sb16_stream_close(int id);
int  sb16_stream_submit(int id, const unsigned char *pcm, unsigned len);
void sb16_stream_volume(int id, unsigned char vol);
int  sb16_stream_count(void);

unsigned sb16_ring_free(void);
int      sb16_mode_active(void);

void sb16_counters(sb16_counters_t *out);

#endif
