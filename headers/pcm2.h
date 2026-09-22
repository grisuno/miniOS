#ifndef PCM2_H
#define PCM2_H

/* pcm2.h -- low-latency PCM audio path over SB16 single-cycle DMA.
 *
 * BSD/Linux-style PCM core next to the legacy game path, never through
 * it. The legacy engine (drivers/sb16.c, syscalls 221/222/224) exists
 * for Doom music and tone effects: 2048-byte submits, a 7-slot DMA
 * ring re-armed from the timer watchdog, ~650 ms of buffering. That is
 * the right shape for background music and the wrong shape for an
 * interactive synth, where every extra 100 ms of buffering reads as
 * input lag and a watchdog re-arm replays stale audio. pcm2 is the
 * standard engine for ring-3 audio (piano, Quake 2, DOOM, Pokémon); the
 * two share only the DSP and never at the same time (mutual -EBUSY, both
 * directions).
 *
 * Hardware program (OSDev "Sound Blaster 16", Creative programming
 * guide): DSP 0x41 rate (high byte then low, the order Linux uses),
 * speaker on, DMA channel 1 in single-cycle read mode (0x49) and DSP
 * 0x14 single-cycle 8-bit playback of one 512-byte block at a time.
 * The block is re-armed from the terminal-count IRQ5 (acked by reading
 * 0x22E), so the audible gap is the few microseconds of the ISR; a
 * 100 Hz timer poll additionally retires the block on elapsed guest
 * time, so playback continues even when QEMU never delivers the IRQ
 * (null backend). Auto-init DMA is deliberately NOT used: in emulation
 * it holds the ISA DMA engine busy and wedges the IDE PIO path, stalling
 * every MiniFS read for minutes (observed as a guest hang right after
 * the first pcm2 open).
 *
 * Buffering (ALSA-style, bounded, all constants below):
 * - DMA block: PCM2_DMA_BYTES bytes below 16 MB (BOOT_PCM2_DMA_ADDR),
 *   never crossing a 64 KB page, written only by the arm path.
 * - Heap ring: PCM2_RING bytes (pcm_ring.h: overrun counts drops,
 *   underrun pads 0x80 silence and counts, never stalls the engine).
 * - Write path copies user bytes in chunks and blocks (PROC_BLOCKED +
 *   schedule, futex discipline: predicate and sleep share pcm2_lock)
 *   unless opened NONBLOCK, in which case a full ring takes what fits
 *   and reports the short count.
 * Steady-state latency is about one DMA block (~23 ms at 22050 Hz)
 * plus the IRQ re-arm against ~650 ms on the legacy ring.
 *
 * Failure modes, all fail-closed:
 * - no SB16: open refuses -ENODEV; legacy owns DSP: -EBUSY; already
 *   open (exclusive, OSS-style): -EBUSY; OOM ring: -ENOMEM.
 * - killed owner: the next write/close entry finds a ZOMBIE/FREE
 *   owner, releases the device and reports -EPIPE instead of
 *   blocking forever on a corpse that do_kill already reaped.
 * - close stops the DSP immediately (0xD0 + DMA mask), frees the
 *   ring and clears ownership; a foreign close reports -EPERM.
 */

#define PCM2_RATE       22050u
#define PCM2_FRAG       256u
#define PCM2_FRAGS      2u
#define PCM2_DMA_BYTES  (PCM2_FRAG * PCM2_FRAGS)
#define PCM2_RING       (PCM2_FRAG * 4u)

#define PCM2_FLAG_NONBLOCK 1u

#define PCM2_ERR_BUSY   (-16)
#define PCM2_ERR_NODEV  (-19)
#define PCM2_ERR_NOMEM  (-12)
#define PCM2_ERR_PERM   (-1)
#define PCM2_ERR_PIPE   (-32)
#define PCM2_ERR_INVAL  (-22)

typedef struct {
    unsigned long irqs;
    unsigned long polls;
    unsigned long spurious;
    unsigned long bytes;
    unsigned long underruns;
    unsigned long drops;
    unsigned long wakes;
} pcm2_counters_t;

int  pcm2_active(void);
int  pcm2_open(unsigned flags, int owner);
int  pcm2_write(const unsigned char *user, unsigned len, int owner);
void pcm2_close(int owner);
void pcm2_irq(void);
void pcm2_poll(void);
void pcm2_counters(pcm2_counters_t *out);

#endif
