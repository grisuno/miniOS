/* drivers/pcm2.c -- low-latency PCM audio over SB16 single-cycle DMA.
 *
 * See headers/pcm2.h for the contract. What this file owns:
 * - DSP ownership against the legacy engine (mutual -EBUSY, both ways:
 *   the legacy guards live in drivers/sb16.c and read pcm2_active()).
 * - DSP/DMA programming in the legacy-proven single-cycle order and the
 *   IRQ/poll re-arm path: one 512-byte block is armed at a time and the
 *   next is armed from the terminal-count IRQ, with the timer poll as the
 *   null-backend fallback (kernel-heap ring feeds both).
 * - The blocking write: predicate and sleep share pcm2_lock (futex
 *   discipline), so a refill wakeup can never slip between the space
 *   check and the deschedule and strand a writer forever.
 *
 * What this file never does (legacy engine keeps it all): tone mode,
 * the mixer streams, 2048-byte submits.
 */

#include "kernel.h"
#include "sched.h"
#include "spinlock.h"
#include "sb16.h"
#include "pcm2.h"
#include "pcm_ring.h"
#include "bootdefs.h"

#define PCM2_BASE_PORT      0x220
#define PCM2_DSP_RESET      0x226
#define PCM2_DSP_WRITE_DATA 0x22C
#define PCM2_DSP_STATUS     0x22C
#define PCM2_IRQ_ACK        0x22E

#define PCM2_CMD_SET_FREQ   0x41
#define PCM2_CMD_SPK_ON     0xD1
#define PCM2_CMD_PLAY8      0x14
#define PCM2_CMD_STOP_NOW   0xD0

/* Single-cycle DMA, the same sequence the legacy engine has proven under
 * QEMU: auto-init DMA holds the ISA DMA engine busy in emulation and
 * wedges the IDE PIO path, so each 512-byte block is armed on its own and
 * re-armed from the terminal-count IRQ (prompt, gapless) with the timer
 * poll as the null-backend fallback (ktime_ms elapsed). */
#define PCM2_DMA_MODE_PORT  0x0B
#define PCM2_DMA_CH1_SINGLE 0x49
#define PCM2_DMA_CH1_ADDR   0x02
#define PCM2_DMA_CH1_CNT    0x03
#define PCM2_DMA_CH1_PAGE   0x83
#define PCM2_DMA_MASK       0x0A
#define PCM2_DMA_FF_CLR     0x0C
#define PCM2_DMA_CH1_MASK   0x05
#define PCM2_DMA_CH1_UNMASK 0x01

#define PCM2_DMA_ADDR       BOOT_PCM2_DMA_ADDR
#define PCM2_DMA_COUNT      (PCM2_DMA_BYTES - 1u)
#define PCM2_READY_MASK     0x80
#define PCM2_PROBE_WAIT     200000u
#define PCM2_SILENCE        0x80
/* One armed block plays for this long. Ceil so an early completion can
 * never cut the tail; the IRQ path re-arms at the true terminal count. */
#define PCM2_BLOCK_MS       (((PCM2_DMA_BYTES * 1000u) + PCM2_RATE - 1u) / PCM2_RATE)
#define PCM2_BLOCK_SLACK_MS 2u

_Static_assert(PCM2_DMA_ADDR + PCM2_DMA_BYTES < 0xA0000,
               "pcm2 DMA buffer must not cross a 64KB page");
_Static_assert((PCM2_DMA_BYTES & (PCM2_DMA_BYTES - 1u)) == 0,
               "pcm2 DMA size must be a power of two");

static int pcm2_on;
static int pcm2_owner;
static int pcm2_nonblock;
static int pcm2_inflight;
static pcm_ring_t pcm2_ring;
static unsigned char *pcm2_ring_mem;
static spinlock_t pcm2_lock;
static unsigned long pcm2_arm_ms;
static pcm2_counters_t pcm2_stat;

static unsigned char *pcm2_dma(void) {
    return (unsigned char *)(unsigned long)PCM2_DMA_ADDR;
}

static int pcm2_wait_write(void) {
    unsigned i = 0;
    while ((inb(PCM2_DSP_STATUS) & PCM2_READY_MASK) && i < PCM2_PROBE_WAIT)
        i++;
    return i < PCM2_PROBE_WAIT;
}

static void pcm2_cmd(unsigned char c) {
    pcm2_wait_write();
    outb(PCM2_DSP_WRITE_DATA, c);
}

static void pcm2_dma_program(void) {
    unsigned n = PCM2_DMA_COUNT;
    outb(PCM2_DMA_MASK, PCM2_DMA_CH1_MASK);
    outb(PCM2_DMA_MODE_PORT, PCM2_DMA_CH1_SINGLE);
    outb(PCM2_DMA_FF_CLR, 0);
    outb(PCM2_DMA_CH1_ADDR, PCM2_DMA_ADDR & 0xFF);
    outb(PCM2_DMA_CH1_ADDR, (PCM2_DMA_ADDR >> 8) & 0xFF);
    outb(PCM2_DMA_CH1_CNT, n & 0xFF);
    outb(PCM2_DMA_CH1_CNT, (n >> 8) & 0xFF);
    outb(PCM2_DMA_CH1_PAGE, (PCM2_DMA_ADDR >> 16) & 0xFF);
    outb(PCM2_DMA_MASK, PCM2_DMA_CH1_UNMASK);
}

static void pcm2_dma_stop(void) {
    outb(PCM2_DMA_MASK, PCM2_DMA_CH1_MASK);
}

static void pcm2_dsp_play(void) {
    pcm2_cmd(PCM2_CMD_SET_FREQ);
    pcm2_cmd((unsigned char)((PCM2_RATE >> 8) & 0xFF));
    pcm2_cmd((unsigned char)(PCM2_RATE & 0xFF));
    pcm2_cmd(PCM2_CMD_SPK_ON);
    pcm2_cmd(PCM2_CMD_PLAY8);
    pcm2_cmd((unsigned char)(PCM2_DMA_COUNT & 0xFF));
    pcm2_cmd((unsigned char)((PCM2_DMA_COUNT >> 8) & 0xFF));
}

static void pcm2_wake_owner(void) {
    proc_t *o;
    if (pcm2_owner < 0 || pcm2_owner >= MAX_PROCS) return;
    o = proc_get(pcm2_owner);
    if (o && o->state == PROC_BLOCKED) {
        o->state = PROC_READY;
        pcm2_stat.wakes++;
    }
}

/* Fill the DMA block from the ring (silence on underrun) and arm one
 * single-cycle transfer. Runs under pcm2_lock, so a single in-flight
 * block means no double arm and no lost wakeup. */
static void pcm2_arm_block(void) {
    pcm_ring_read(&pcm2_ring, pcm2_dma(), PCM2_DMA_BYTES);
    pcm2_stat.bytes += PCM2_DMA_BYTES;
    pcm2_stat.underruns = pcm2_ring.underruns;
    pcm2_dma_program();
    pcm2_dsp_play();
    pcm2_inflight = 1;
    pcm2_arm_ms = ktime_ms();
}

/* One service tick. A single 512-byte block is in flight; the terminal
 * count IRQ retires it and re-arms the next at once (gapless), and the
 * 100 Hz poll retires it on elapsed guest time when the IRQ never comes
 * (null backend). Completion is never inferred twice: inflight gates it,
 * and the accounting is counters only, so no position value can wrap a
 * loop (the auto-init livelock is structurally impossible here). The IRQ
 * path rejects a stray pulse that arrives before half the block could
 * have played. Both callers hold pcm2_lock with interrupts saved. */
static void pcm2_service(int from_irq) {
    unsigned long now = ktime_ms();
    if (from_irq) pcm2_stat.irqs++;
    else pcm2_stat.polls++;

    if (pcm2_inflight) {
        unsigned long elapsed = now - pcm2_arm_ms;
        int done = 0;
        if (from_irq) {
            if (elapsed + PCM2_BLOCK_SLACK_MS >= PCM2_BLOCK_MS / 2u)
                done = 1;
            else
                pcm2_stat.spurious++;
        } else if (elapsed >= (unsigned long)PCM2_BLOCK_MS +
                              (unsigned long)PCM2_BLOCK_SLACK_MS) {
            done = 1;
        }
        if (done) pcm2_inflight = 0;
    } else if (from_irq) {
        pcm2_stat.spurious++;
    }

    if (!pcm2_inflight) pcm2_arm_block();
    pcm2_wake_owner();
}

int pcm2_active(void) {
    return pcm2_on;
}

int pcm2_open(unsigned flags, int owner) {
    irqflags_t irq;
    unsigned i;
    if (!sb16_present()) return PCM2_ERR_NODEV;
    if (owner < 0 || owner >= MAX_PROCS) return PCM2_ERR_PERM;
    spin_lock_irqsave(&pcm2_lock, &irq);
    if (pcm2_on) {
        spin_unlock_irqrestore(&pcm2_lock, irq);
        return PCM2_ERR_BUSY;
    }
    if (sb16_legacy_busy()) {
        spin_unlock_irqrestore(&pcm2_lock, irq);
        return PCM2_ERR_BUSY;
    }
    pcm2_ring_mem = (unsigned char *)kmalloc(PCM2_RING);
    if (!pcm2_ring_mem) {
        spin_unlock_irqrestore(&pcm2_lock, irq);
        return PCM2_ERR_NOMEM;
    }
    pcm_ring_init(&pcm2_ring, pcm2_ring_mem, PCM2_RING);
    for (i = 0; i < PCM2_DMA_BYTES; i++) pcm2_dma()[i] = PCM2_SILENCE;
    pcm2_inflight = 0;
    pcm2_arm_ms = 0;
    pcm2_owner = owner;
    pcm2_nonblock = (flags & PCM2_FLAG_NONBLOCK) ? 1 : 0;
    pcm2_on = 1;
    pcm2_arm_block();
    spin_unlock_irqrestore(&pcm2_lock, irq);
    return 0;
}

static int pcm2_owner_live(void) {
    proc_t *o = proc_get(pcm2_owner);
    return o && o->state != PROC_FREE && o->state != PROC_ZOMBIE;
}

static void pcm2_release_locked(void) {
    pcm2_cmd(PCM2_CMD_STOP_NOW);
    pcm2_dma_stop();
    if (pcm2_ring_mem) kfree(pcm2_ring_mem);
    pcm2_ring_mem = 0;
    pcm2_on = 0;
    pcm2_owner = -1;
}

int pcm2_write(const unsigned char *user, unsigned len, int owner) {
    unsigned accepted = 0;
    if (!user) return PCM2_ERR_PERM;
    for (;;) {
        irqflags_t irq;
        unsigned space, chunk;
        spin_lock_irqsave(&pcm2_lock, &irq);
        if (!pcm2_on || owner != pcm2_owner) {
            spin_unlock_irqrestore(&pcm2_lock, irq);
            return (accepted > 0) ? (int)accepted : PCM2_ERR_PERM;
        }
        if (!pcm2_owner_live()) {
            pcm2_release_locked();
            spin_unlock_irqrestore(&pcm2_lock, irq);
            return (accepted > 0) ? (int)accepted : PCM2_ERR_PIPE;
        }
        space = pcm_ring_free(&pcm2_ring);
        if (space == 0) {
            proc_t *cur;
            if (pcm2_nonblock) {
                spin_unlock_irqrestore(&pcm2_lock, irq);
                return (int)accepted;
            }
            cur = proc_get(owner);
            if (!cur) {
                spin_unlock_irqrestore(&pcm2_lock, irq);
                return (accepted > 0) ? (int)accepted : PCM2_ERR_PIPE;
            }
            cur->state = PROC_BLOCKED;
            spin_unlock_irqrestore(&pcm2_lock, irq);
            schedule();
            continue;
        }
        chunk = len - accepted;
        if (chunk > space) chunk = space;
        if (chunk > PCM2_FRAG) chunk = PCM2_FRAG;
        pcm_ring_write(&pcm2_ring, user + accepted, chunk);
        accepted += chunk;
        pcm2_stat.drops = pcm2_ring.drops;
        spin_unlock_irqrestore(&pcm2_lock, irq);
        if (accepted >= len) return (int)accepted;
        /* NONBLOCK returns what fits so far; blocking loops back and
         * sleeps when the ring is full. Either way a short count is
         * backpressure, never loss: the caller holds the remainder. */
    }
}

void pcm2_close(int owner) {
    irqflags_t irq;
    spin_lock_irqsave(&pcm2_lock, &irq);
    if (!pcm2_on || owner != pcm2_owner) {
        spin_unlock_irqrestore(&pcm2_lock, irq);
        return;
    }
    pcm2_release_locked();
    spin_unlock_irqrestore(&pcm2_lock, irq);
}

void pcm2_irq(void) {
    irqflags_t irq;
    (void)inb(PCM2_IRQ_ACK);
    spin_lock_irqsave(&pcm2_lock, &irq);
    if (!pcm2_on) {
        pcm2_stat.spurious++;
        spin_unlock_irqrestore(&pcm2_lock, irq);
        return;
    }
    pcm2_service(1);
    spin_unlock_irqrestore(&pcm2_lock, irq);
}

void pcm2_poll(void) {
    irqflags_t irq;
    if (!pcm2_on) return;
    spin_lock_irqsave(&pcm2_lock, &irq);
    if (!pcm2_on) {
        spin_unlock_irqrestore(&pcm2_lock, irq);
        return;
    }
    pcm2_service(0);
    spin_unlock_irqrestore(&pcm2_lock, irq);
}

void pcm2_counters(pcm2_counters_t *out) {
    if (out) *out = pcm2_stat;
}
