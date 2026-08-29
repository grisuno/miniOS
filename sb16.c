#include "kernel.h"
#include "sb16.h"

/* Sound Blaster 16 DMA audio driver.
 *
 * The SB16 (DSP 4.05) is an ISA device at 0x220 with a digital (PCM) path fed
 * through the 8237 DMA controller.  This driver streams 8-bit unsigned mono
 * audio at SB16_PCM_RATE using single-cycle DMA on channel 1 over a ring of
 * DMA buffers: one is played while the others are queued.  In tone mode the
 * driver renders a square wave into each refilled slot so existing `sys_tone`
 * callers need no change; in PCM mode a ring-3 renderer submits raw sample
 * buffers through `sb16_pcm_submit` and the driver drains them.
 *
 * DMA completion is serviced from two places.  The SB16 IRQ (vector 37) is
 * the precise fast path: a single-cycle transfer completes once and stops,
 * QEMU raises the IRQ, and the handler acknowledges it via the 0x22E read
 * (which also lowers the line so the next completion produces a fresh edge)
 * before re-arming.  The timer ISR calls `sb16_poll` as a watchdog: some
 * QEMU audio backends never raise the completion IRQ (they only consume once
 * their engine buffer drains, which a stalled host backend never does), and
 * without a fallback the 7-slot ring fills once and every later submit is
 * refused, deadening the audio path.  Both paths funnel through `sb16_arm`,
 * which re-arms at most once per buffer duration, so the two paths are
 * idempotent and a fast backend can never drive an interrupt storm.
 *
 * The DSP commands must match what QEMU's hw/audio/sb16.c expects: the 8-bit
 * sample rate is set with the 0x41 command (two frequency bytes, low then
 * high) so the clock matches SB16_PCM_RATE exactly; the 0x14 playback count
 * is (hi then lo) of `length - 1`, which QEMU adds one back to.  Getting the
 * command stream wrong silently produces no output while the ring still
 * appears to drain.
 *
 * The DMA buffers MUST live in physical memory below 16 MB that is identity
 * mapped, because the 8237 can only reach that window and the address is
 * driven from the DMA page/address registers, not from the page tables.  They
 * sit in the reserved low region [SB16_DMA_BUF0, SB16_DMA_BUF0 + ring size):
 * the kernel stack starts above them and grows down, so it never touches
 * them, and bootdefs.h documents the reservation.  No kernel-static array is
 * used, because under KASLR the kernel image's physical base can land above
 * 16 MB where the DMA controller cannot reach it.  Fail-closed: with no SB16
 * the probe times out, `sb16_present()` stays false, and submits are refused. */

#define SB16_BASE_PORT      0x220
#define SB16_DSP_RESET      0x226
#define SB16_DSP_READ_DATA  0x22A
#define SB16_DSP_WRITE_DATA 0x22C
#define SB16_DSP_STATUS     0x22C
#define SB16_IRQ_ACK        0x22E

#define SB16_CMD_READ_VER   0xE1
#define SB16_CMD_SET_FREQ   0x41
#define SB16_CMD_PLAY8      0x14

#define SB16_FREQ_LO        (unsigned char)(SB16_PCM_RATE & 0xFF)
#define SB16_FREQ_HI        (unsigned char)((SB16_PCM_RATE >> 8) & 0xFF)

#define SB16_DSP_READY_MASK 0x80

#define DMA_CH1_ADDR        0x02
#define DMA_CH1_CNT         0x03
#define DMA_CH1_PAGE        0x83
#define DMA_MASK            0x0A
#define DMA_FF_CLR          0x0C
#define DMA_CH1_UNMASK      0x01
#define DMA_CH1_MASK        0x05

#define SB16_DMA_BUF0       0x00090000u
#define SB16_SILENCE_SLOT   (SB16_SLOTS - 1u)
#define SB16_BUF            SB16_PCM_BUF

#define SB16_PROBE_WAIT     200000u

#define SB16_MODE_TONE 0
#define SB16_MODE_PCM  1

#define SB16_SQ_CYCLE 512

static int sb16_ready;
static int sb16_mode = SB16_MODE_TONE;
static unsigned sb16_freq;
static unsigned sb16_phase;
static int sb16_inflight;
static unsigned long sb16_last_arm_ms;
static sb16_counters_t sb16_stat;

static unsigned pcm_head;
static unsigned pcm_tail;
static unsigned pcm_free;

static unsigned char *sb16_slot(unsigned i) {
    return (unsigned char *)(unsigned long)(SB16_DMA_BUF0 + i * SB16_BUF);
}

static void sb16_wait_dsp_write(void) {
    unsigned i;
    for (i = 0; i < 16u; i++) __asm__ volatile("pause");
}

static int sb16_read_data(unsigned char *out) {
    unsigned i = 0;
    while (!(inb(SB16_DSP_READ_DATA) & SB16_DSP_READY_MASK) && i < SB16_PROBE_WAIT)
        i++;
    if (i >= SB16_PROBE_WAIT) return 0;
    *out = inb(SB16_DSP_READ_DATA);
    return 1;
}

static int sb16_reset_dsp(void) {
    unsigned i;
    outb(SB16_DSP_RESET, 1);
    for (i = 0; i < 10000u; i++) __asm__ volatile("pause");
    outb(SB16_DSP_RESET, 0);
    for (i = 0; i < 10000u; i++) __asm__ volatile("pause");
    for (i = 0; i < SB16_PROBE_WAIT; i++) {
        if ((inb(SB16_DSP_READ_DATA) & SB16_DSP_READY_MASK) &&
            inb(SB16_DSP_READ_DATA) == 0xAA)
            return 1;
    }
    return 0;
}

static void sb16_dma_play(unsigned addr, unsigned len) {
    unsigned n = len - 1;
    outb(DMA_MASK, DMA_CH1_MASK);
    outb(DMA_FF_CLR, 0);
    outb(DMA_CH1_ADDR, addr & 0xFF);
    outb(DMA_CH1_ADDR, (addr >> 8) & 0xFF);
    outb(DMA_CH1_CNT, n & 0xFF);
    outb(DMA_CH1_CNT, (n >> 8) & 0xFF);
    outb(DMA_CH1_PAGE, (addr >> 16) & 0xFF);
    outb(DMA_MASK, DMA_CH1_UNMASK);
    sb16_wait_dsp_write();
    outb(SB16_DSP_WRITE_DATA, SB16_CMD_PLAY8);
    outb(SB16_DSP_WRITE_DATA, (n >> 8) & 0xFF);
    outb(SB16_DSP_WRITE_DATA, n & 0xFF);
}

static void sb16_refill(int slot_index) {
    unsigned char *buf = sb16_slot((unsigned)slot_index);
    unsigned i;
    if (sb16_freq == 0) {
        for (i = 0; i < SB16_BUF; i++) buf[i] = 0x80;
        return;
    }
    unsigned step = (SB16_SQ_CYCLE * sb16_freq) / SB16_PCM_RATE;
    if (step == 0) step = 1;
    for (i = 0; i < SB16_BUF; i++) {
        buf[i] = (sb16_phase < SB16_SQ_CYCLE / 2) ? 0xC0 : 0x40;
        sb16_phase += step;
        if (sb16_phase >= SB16_SQ_CYCLE) sb16_phase -= SB16_SQ_CYCLE;
    }
}

static void sb16_arm(int from_irq) {
    unsigned long now = ktime_ms();
    if (!sb16_ready || !sb16_inflight) return;
    if ((long)(now - sb16_last_arm_ms) < (long)SB16_ARM_PERIOD_MS) return;
    if (sb16_mode == SB16_MODE_PCM) {
        if (pcm_free == SB16_RING_CAP) {
            sb16_dma_play(SB16_DMA_BUF0 + SB16_SILENCE_SLOT * SB16_BUF, SB16_BUF);
        } else {
            sb16_dma_play(SB16_DMA_BUF0 + pcm_tail * SB16_BUF, SB16_BUF);
            pcm_tail = (pcm_tail + 1) % SB16_RING_CAP;
            pcm_free++;
        }
    } else {
        static int tone_next;
        int slot = tone_next;
        tone_next = 1 - tone_next;
        sb16_refill(slot);
        sb16_dma_play(SB16_DMA_BUF0 + (unsigned)slot * SB16_BUF, SB16_BUF);
    }
    sb16_last_arm_ms = now;
    if (from_irq) sb16_stat.irq_arms++;
    else sb16_stat.poll_arms++;
}

int sb16_present(void) { return sb16_ready; }

void sb16_tone(unsigned freq) {
    if (!sb16_ready) return;
    sb16_mode = SB16_MODE_TONE;
    sb16_freq = freq;
    pcm_head = pcm_tail = 0;
    pcm_free = SB16_RING_CAP;
    if (!sb16_inflight) {
        sb16_last_arm_ms = ktime_ms();
        sb16_refill(0);
        sb16_dma_play(SB16_DMA_BUF0, SB16_BUF);
        sb16_inflight = 1;
    }
}

void sb16_pcm_open(void) {
    if (!sb16_ready) return;
    sb16_mode = SB16_MODE_PCM;
    sb16_freq = 0;
    pcm_head = pcm_tail = 0;
    pcm_free = SB16_RING_CAP;
    unsigned i;
    for (i = 0; i < SB16_BUF; i++) sb16_slot(SB16_SILENCE_SLOT)[i] = 0x80;
    if (!sb16_inflight) {
        sb16_last_arm_ms = ktime_ms();
        sb16_dma_play(SB16_DMA_BUF0 + SB16_SILENCE_SLOT * SB16_BUF, SB16_BUF);
        sb16_inflight = 1;
    }
}

void sb16_pcm_close(void) { if (sb16_ready) sb16_tone(0); }

int sb16_pcm_submit(const unsigned char *pcm, unsigned len) {
    unsigned i;
    if (!sb16_ready || sb16_mode != SB16_MODE_PCM) return -1;
    if (len == 0 || len > SB16_BUF) return -1;
    if (pcm_free == 0) { sb16_stat.drops++; return -1; }
    unsigned char *dst = sb16_slot(pcm_head);
    for (i = 0; i < len; i++) dst[i] = pcm[i];
    for (; i < SB16_BUF; i++) dst[i] = 0x80;
    pcm_head = (pcm_head + 1) % SB16_RING_CAP;
    pcm_free--;
    sb16_stat.submits++;
    return 0;
}

void sb16_irq(void) {
    if (!sb16_ready || !sb16_inflight) return;
    (void)inb(SB16_IRQ_ACK);
    sb16_arm(1);
}

void sb16_poll(void) { sb16_arm(0); }

unsigned sb16_ring_free(void) { return pcm_free; }
int sb16_mode_active(void) { return sb16_mode; }

void sb16_counters(sb16_counters_t *out) {
    if (out) *out = sb16_stat;
}

int sb16_init(void) {
    unsigned char major = 0, minor = 0;
    if (sb16_ready) return 1;
    if (!sb16_reset_dsp()) return 0;
    if (!sb16_read_data(&major)) return 0;
    if (!sb16_read_data(&minor)) return 0;
    (void)minor;
    if (major < 4) return 0;
    sb16_wait_dsp_write();
    outb(SB16_DSP_WRITE_DATA, SB16_CMD_SET_FREQ);
    outb(SB16_DSP_WRITE_DATA, SB16_FREQ_LO);
    outb(SB16_DSP_WRITE_DATA, SB16_FREQ_HI);
    sb16_freq = 0;
    sb16_inflight = 0;
    pcm_head = pcm_tail = 0;
    pcm_free = SB16_RING_CAP;
    sb16_ready = 1;
    sb16_last_arm_ms = ktime_ms();
    return 1;
}
