#include "kernel.h"
#include "sb16.h"

/* Sound Blaster 16 DMA audio driver.
 *
 * The SB16 (DSP 4.05) is an ISA device at 0x220 with a digital (PCM) path
 * fed through the 8237 DMA controller.  This driver streams 8-bit unsigned
 * mono audio at 22050 Hz using single-cycle DMA on channel 1 with a ring of
 * DMA buffers: one is played while the others are queued.  In tone mode the
 * driver renders a square wave into each refilled slot (so the existing
 * `sys_tone` callers need no change); in PCM mode a ring-3 renderer submits
 * raw sample buffers through `sb16_pcm_submit` and the driver drains them.
 *
 * DMA completion is serviced from the SB16 IRQ (vector 37): a single-cycle
 * transfer completes once and stops, QEMU raises the IRQ, and the handler
 * acknowledges it via the 0x22E read (which also drops the line so the next
 * completion produces a fresh PIC edge) and re-arms the next buffer.
 *
 * The DSP commands must match what QEMU's hw/audio/sb16.c expects: the 8-bit
 * rate is set with 0x40 plus one time-constant byte (the 0x41 command wants
 * two frequency bytes and would desynchronize the command stream), and the
 * 0x14 playback count is (hi then lo) of `length - 1`, which QEMU adds one
 * back to.  Getting these wrong silently produces no output while the DMA
 * ring still appears to drain.
 *
 * The DMA buffers MUST live in physical memory below 16 MB that is identity
 * mapped, because the 8237 can only reach that window and the address is
 * driven from the DMA page/address registers, not from the page tables.  They
 * sit in the reserved low region [0x90000, 0x94000): the kernel stack starts
 * at 0x90000 and grows DOWN, so it never touches them, and bootdefs.h
 * documents the reservation.  No kernel-static array is used, because under
 * KASLR the kernel image's physical base can land above 16 MB where the DMA
 * controller cannot reach it.  Fail-closed: with no SB16 the probe times out,
 * `sb16_present()` stays false, and submits are refused. */

#define SB16_BASE_PORT      0x220
#define SB16_DSP_RESET      0x226   /* write 1 then 0 to reset the DSP */
#define SB16_DSP_READ_DATA  0x22A   /* read 1 byte of DSP output */
#define SB16_DSP_WRITE_DATA 0x22C   /* write 1 byte of DSP input */
#define SB16_DSP_STATUS     0x22C   /* read bit 7 = write buffer full */
#define SB16_IRQ_ACK        0x22E   /* read to acknowledge a DSP IRQ */

#define SB16_CMD_READ_VER   0xE1    /* get DSP version (major then minor) */
#define SB16_CMD_SET_TC8    0x40    /* set 8-bit time constant (1 byte) */
#define SB16_CMD_PLAY8      0x14    /* 8-bit single-cycle DMA playback */

#define SB16_DSP_READY_MASK 0x80

#define SB16_TC             211u    /* 256 - 1000000/22050 (8-bit time const) */

/* 8237 DMA channel 1 (low controller): address 0x02, count 0x03, page 0x83,
 * mask command 0x0A, clear-byte-pointer 0x0C.  Mask value 0x01 unmask, 0x05
 * mask.  Count is length-1. */
#define DMA_CH1_ADDR        0x02
#define DMA_CH1_CNT         0x03
#define DMA_CH1_PAGE        0x83
#define DMA_MASK            0x0A
#define DMA_FF_CLR          0x0C
#define DMA_CH1_UNMASK      0x01
#define DMA_CH1_MASK        0x05

/* Reserved identity-mapped low region for the DMA ring: 8 slots of 2 KB each
 * at [0x90000, 0x94000).  The last slot is the permanent silence buffer so
 * the ring never plays stale audio when it runs dry.  (see header + bootdefs) */
#define SB16_DMA_BUF0       0x00090000u
#define SB16_SLOTS          8u
#define SB16_SILENCE_SLOT   (SB16_SLOTS - 1u)
#define SB16_RING_CAP       (SB16_SLOTS - 1u)   /* usable queue slots */
#define SB16_BUF            SB16_PCM_BUF

#define SB16_PROBE_WAIT     200000u /* bounded reset/version wait iterations */

#define SB16_MODE_TONE 0
#define SB16_MODE_PCM  1

#define SB16_SQ_CYCLE 512           /* one square cycle = 2*256 phase units */

static int sb16_ready;
static int sb16_mode = SB16_MODE_TONE;
static unsigned sb16_freq;
static unsigned sb16_phase;         /* 0..SB16_SQ_CYCLE fixed-point phase */
static int sb16_inflight;           /* a single-cycle transfer is playing */

/* PCM ring over slots [0, SB16_RING_CAP). */
static unsigned pcm_head;
static unsigned pcm_tail;
static unsigned pcm_free;

static unsigned char *sb16_slot(unsigned i) {
    return (unsigned char *)(unsigned long)(SB16_DMA_BUF0 + i * SB16_BUF);
}

static void sb16_wait_dsp_write(void) {
    unsigned i;
    /* The DSP status register bit 7 (0x80) means "data available to read",
     * NOT "write buffer empty", so it must never gate command writes: if it
     * happens to be set (a pending byte, or a QEMU quirk) the old 100000-trip
     * spin burned through the whole bound on every DMA re-arm from the IRQ
     * handler, which is exactly what stalled the whole VM while the SB16
     * streamed.  DSP commands are issued only a few times per transfer
     * (~93 ms apart), so a short fixed grace is all that is needed and the
     * DMA command stream can never desynchronize from a busy DSP. */
    for (i = 0; i < 16u; i++) __asm__ volatile("pause");
}

/* Read one byte of DSP output, waiting for the data-ready bit, bounded. */
static int sb16_read_data(unsigned char *out) {
    unsigned i = 0;
    while (!(inb(SB16_DSP_READ_DATA) & SB16_DSP_READY_MASK) && i < SB16_PROBE_WAIT)
        i++;
    if (i >= SB16_PROBE_WAIT) return 0;
    *out = inb(SB16_DSP_READ_DATA);
    return 1;
}

/* Reset the DSP and wait for the 0xAA "ready" byte. */
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

/* Program 8-bit single-cycle DMA on channel 1 to play `len` bytes from the
 * physical address `addr`, then start the DSP playback.  The DMA controller's
 * count register takes length-1; QEMU's SB16 reads the DSP 0x14 count as
 * (hi then lo) of `length - 1` and adds one back (see qemu hw/audio/sb16.c,
 * complete(): case 0x14 -> dma_cmd8(s, 0, dsp_get_lohi(s) + 1)). */
static void sb16_dma_play(unsigned addr, unsigned len) {
    unsigned n = len - 1;
    outb(DMA_MASK, DMA_CH1_MASK);               /* mask ch1 while programming */
    outb(DMA_FF_CLR, 0);                        /* reset the byte pointer */
    outb(DMA_CH1_ADDR, addr & 0xFF);
    outb(DMA_CH1_ADDR, (addr >> 8) & 0xFF);
    outb(DMA_CH1_CNT, n & 0xFF);
    outb(DMA_CH1_CNT, (n >> 8) & 0xFF);
    outb(DMA_CH1_PAGE, (addr >> 16) & 0xFF);
    outb(DMA_MASK, DMA_CH1_UNMASK);             /* release the channel */
    sb16_wait_dsp_write();
    outb(SB16_DSP_WRITE_DATA, SB16_CMD_PLAY8);
    outb(SB16_DSP_WRITE_DATA, (n >> 8) & 0xFF); /* count, high byte first */
    outb(SB16_DSP_WRITE_DATA, n & 0xFF);
}

/* Render one buffer of the current square wave (or silence at freq 0). */
static void sb16_refill(int slot_index) {
    unsigned char *buf = sb16_slot((unsigned)slot_index);
    unsigned i;
    if (sb16_freq == 0) {
        for (i = 0; i < SB16_BUF; i++) buf[i] = 0x80;
        return;
    }
    /* Square wave: value flips at phase SB16_SQ_CYCLE/2.  High and low
     * straddle the 0x80 midpoint so the amplitude is symmetric and quiet. */
    unsigned step = (SB16_SQ_CYCLE * sb16_freq) / SB16_PCM_RATE;
    if (step == 0) step = 1;
    for (i = 0; i < SB16_BUF; i++) {
        buf[i] = (sb16_phase < SB16_SQ_CYCLE / 2) ? 0xC0 : 0x40;
        sb16_phase += step;
        if (sb16_phase >= SB16_SQ_CYCLE) sb16_phase -= SB16_SQ_CYCLE;
    }
}

/* Re-arm DMA with the next thing to play.  Shared by the IRQ fast path and
 * the timer poll.  Called only after the pending transfer is acknowledged. */
static void sb16_rearm(void) {
    if (sb16_mode == SB16_MODE_PCM) {
        if (pcm_free == SB16_RING_CAP) {
            /* Nothing queued: keep playing the permanent silence buffer. */
            sb16_dma_play(SB16_DMA_BUF0 + SB16_SILENCE_SLOT * SB16_BUF, SB16_BUF);
        } else {
            sb16_dma_play(SB16_DMA_BUF0 + pcm_tail * SB16_BUF, SB16_BUF);
            pcm_tail = (pcm_tail + 1) % SB16_RING_CAP;
            pcm_free++;
        }
        return;
    }
    /* Tone mode: refill the opposite of the last refilled slot.  Track the
     * slot index that was armed so tone alternates between two slots. */
    static int tone_next;
    int slot = tone_next;
    tone_next = 1 - tone_next;
    sb16_refill(slot);
    sb16_dma_play(SB16_DMA_BUF0 + (unsigned)slot * SB16_BUF, SB16_BUF);
}

int sb16_present(void) { return sb16_ready; }

void sb16_tone(unsigned freq) {
    if (!sb16_ready) return;
    sb16_mode = SB16_MODE_TONE;
    sb16_freq = freq;
    pcm_head = pcm_tail = 0;
    pcm_free = SB16_RING_CAP;
    if (!sb16_inflight) {
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
    /* Pre-fill the silence slot so a dry ring never plays stale bytes. */
    unsigned i;
    for (i = 0; i < SB16_BUF; i++) sb16_slot(SB16_SILENCE_SLOT)[i] = 0x80;
    if (!sb16_inflight) {
        sb16_dma_play(SB16_DMA_BUF0 + SB16_SILENCE_SLOT * SB16_BUF, SB16_BUF);
        sb16_inflight = 1;
    }
}

void sb16_pcm_close(void) { if (sb16_ready) sb16_tone(0); }

/* Copy a user PCM buffer into the next free ring slot.  Returns 0 on success,
 * -1 when the ring is full or a buffer would not fit.  The caller validates
 * the user pointer; this function only copies within the reserved region. */
int sb16_pcm_submit(const unsigned char *pcm, unsigned len) {
    unsigned i;
    if (!sb16_ready || sb16_mode != SB16_MODE_PCM) return -1;
    if (len == 0 || len > SB16_BUF) return -1;
    if (pcm_free == 0) return -1;               /* ring full: caller retries */
    unsigned char *dst = sb16_slot(pcm_head);
    for (i = 0; i < len; i++) dst[i] = pcm[i];
    for (; i < SB16_BUF; i++) dst[i] = 0x80;    /* zero-pad the rest */
    pcm_head = (pcm_head + 1) % SB16_RING_CAP;
    pcm_free--;
    return 0;
}

/* Service a completed single-cycle transfer.  Called from the SB16 IRQ (vector
 * 37), which QEMU raises once per completed block and lowers again when the
 * 0x22E acknowledge is read, so one IRQ arrives per transfer.  Acknowledge
 * (which also lowers the line so the next completion produces a fresh edge)
 * and re-arm the next buffer. */
static void sb16_service(void) {
    if (!sb16_ready || !sb16_inflight) return;
    (void)inb(SB16_IRQ_ACK);            /* acknowledge + lower the IRQ line */
    sb16_rearm();
}

void sb16_irq(void) { sb16_service(); }

int sb16_init(void) {
    unsigned char major = 0, minor = 0;
    if (sb16_ready) return 1;
    if (!sb16_reset_dsp()) return 0;    /* no DSP: keep the PC speaker */
    if (!sb16_read_data(&major)) return 0;
    if (!sb16_read_data(&minor)) return 0;
    (void)minor;
    if (major < 4) return 0;            /* not an SB16 DSP */
    /* Program the 8-bit output frequency with the time constant command
     * (0x40 takes ONE byte: TC = 256 - 1000000/rate).  The 0x41 command
     * would expect two frequency bytes and corrupt the command stream. */
    sb16_wait_dsp_write();
    outb(SB16_DSP_WRITE_DATA, SB16_CMD_SET_TC8);
    outb(SB16_DSP_WRITE_DATA, SB16_TC);
    sb16_freq = 0;
    sb16_inflight = 0;
    pcm_head = pcm_tail = 0;
    pcm_free = SB16_RING_CAP;
    sb16_ready = 1;
    return 1;
}
