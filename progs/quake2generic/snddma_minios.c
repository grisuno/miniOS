/* snddma_minios.c - Quake 2 DMA sound backend over the MiniOS pcm2 path.
 *
 * The engine (client/snd_mix.c S_TransferPaintBuffer) mixes every sound
 * effect into a single 8-bit unsigned mono ring, dma.buffer, and asks the
 * platform for the hardware play position through SNDDMA_GetDMAPos; that
 * position drives the paint schedule in client/snd_dma.c (S_Update_ /
 * GetSoundtime). The upstream snddma_null.c answers "no sound", so the
 * whole mixer has always run for nothing.
 *
 * This backend turns that ring into a stream for the kernel's low-latency
 * pcm2 engine (syscalls 246/247/248, 8-bit mono 22050 Hz single-cycle DMA;
 * see CLAUDE.md "Low-latency path pcm2"). SNDDMA_Submit pushes only a small
 * window of the freshly painted bytes (about one kernel ring ahead of the
 * play position) with NONBLOCK writes that never stall the frame loop, and
 * the rest waits in dma.buffer for the next Submit: a blocking push of the
 * whole painted lead would cost ~200 ms per frame (the 0.2 s s_mixahead at
 * 22050 Hz) and drop the game to single-digit fps. SNDDMA_GetDMAPos reports
 * a play position derived from elapsed guest time, clamped to what has
 * actually been submitted, which is what GetSoundtime uses to detect wraps
 * and to never paint past the hardware.
 *
 * The mixer runs 16-bit: upstream S_PaintChannelFrom8 indexes its volume
 * table with `leftvol >> 11`, which is 0 for every legal volume (the table
 * has 32 rows, the correct shift is 3), so the 8-bit path mixes silence.
 * The 16-bit path is correct, so this backend declares a 16-bit mono ring
 * to the engine and downconverts to 8-bit unsigned on the way to pcm2,
 * instead of carrying a patch for upstream mixer code.
 *
 * Geometry rules the engine imposes (client/snd_mix.c):
 * - dma.samples must be a power of two: S_TransferPaintBuffer indexes the
 *   ring with `paintedtime & (dma.samples - 1)`.
 * - The ring is byte-per-sample for 8-bit mono, silence is 0x80, and
 *   dma.channels == 1 means fullsamples == dma.samples.
 * - dma.speed is the resample target in client/snd_mem.c, so it must equal
 *   the pcm2 hardware rate (22050) or every sfx plays at the wrong pitch.
 *
 * Fail closed: no SB16 (pcm2 open refuses) and this file leaves dma.buffer
 * NULL; the engine then runs silently through S_ClearBuffer like it always
 * did, never a crash.
 */

#include "client/client.h"
#include "client/snd_loc.h"
#include "minios_abi.h"
#include <string.h>
#include <stdlib.h>

#define Q2SND_RATE      22050
#define Q2SND_SAMPLES   8192          /* power of two for the engine's mask */
#define Q2SND_SILENCE   0x80
/* Submit window: frames kept queued ahead of the play position. Matches the
 * kernel ring (1024 B), so a NONBLOCK write takes the whole window without
 * ever stalling the frame loop; larger would block, smaller would starve. */
#define Q2SND_AHEAD     1024
/* Mixer ring is 16-bit mono (see header comment); the device takes 8-bit. */
#define Q2SND_BUF_BYTES (Q2SND_SAMPLES * 2)

static unsigned char q2_conv[1024];

static unsigned char *q2_dma_buf;
static int            q2_dma_open;
static long long      q2_dma_written;   /* frames handed to pcm2 so far */
static long long      q2_dma_start_ms;
static long long      q2_dma_loud;      /* pushed bytes clearly above silence */
static long long      q2_dma_total;

static long sys_pcm2_open(long flags) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_PCM2_OPEN), "D"(flags)
                     : "rcx", "r11", "memory");
    return ret;
}

static long sys_pcm2_write(const void *buf, long len) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_PCM2_WRITE), "D"(buf), "S"(len)
                     : "rcx", "r11", "memory");
    return ret;
}

static void sys_pcm2_close(void) {
    __asm__ volatile("syscall"
                     : : "a"(MINIOS_SYS_PCM2_CLOSE)
                     : "rcx", "r11", "memory");
}

static long sys_time_ms(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_TIME), "D"(0)
                     : "rcx", "r11", "memory");
    return ret;
}

/* Push the freshly painted range [q2_dma_written, end) in ring order with
 * NONBLOCK writes that take what the kernel ring has room for. The mixer
 * ring is 16-bit mono; each frame is downconverted to 8-bit unsigned for
 * pcm2 in bounded sub-chunks. A short count is not loss: the frames wait
 * in dma.buffer (the engine only wraps far behind the paint lead) and go
 * out on the next Submit. Returns the number of frames handed to the
 * device. */
static int q2_dma_push(int end) {
    int pushed = 0;
    while (q2_dma_written < end) {
        int idx = (int)(q2_dma_written & (Q2SND_SAMPLES - 1));
        int n = end - (int)q2_dma_written;
        int m, k;
        long r;
        short *src;
        if (n > Q2SND_SAMPLES - idx) n = Q2SND_SAMPLES - idx;
        if (n > (int)sizeof(q2_conv)) n = (int)sizeof(q2_conv);
        src = (short *)(q2_dma_buf + (unsigned)idx * 2u);
        for (k = 0; k < n; k++) {
            int v = (int)src[k] >> 8;
            if (v > 127) v = 127;
            else if (v < -128) v = -128;
            q2_conv[k] = (unsigned char)(v + 128);
        }
        r = sys_pcm2_write(q2_conv, n);
        if (r <= 0) break;
        /* Loudness probe on the accepted prefix only, so a retry never
         * double-counts: anything clearly off the 0x80 line is real mixed
         * audio, not padding. */
        for (k = 0; k < r; k++) {
            int d = (int)q2_conv[k] - (int)Q2SND_SILENCE;
            if (d < 0) d = -d;
            if (d > 4) q2_dma_loud++;
        }
        q2_dma_total += r;
        q2_dma_written += r;
        pushed += (int)r;
    }
    return pushed;
}

qboolean SNDDMA_Init(void) {
    memset(&dma, 0, sizeof(dma));

    if (sys_pcm2_open(MINIOS_PCM2_NONBLOCK) < 0) {
        Com_Printf("pcm2 unavailable, sound disabled\n");
        return false;
    }

    q2_dma_buf = (unsigned char *)malloc(Q2SND_BUF_BYTES);
    if (!q2_dma_buf) {
        sys_pcm2_close();
        Com_Printf("sound buffer allocation failed, sound disabled\n");
        return false;
    }
    memset(q2_dma_buf, 0, Q2SND_BUF_BYTES);

    dma.channels = 1;
    dma.samples = Q2SND_SAMPLES;
    dma.submission_chunk = 1;
    dma.samplepos = 0;
    dma.samplebits = 16;
    dma.speed = Q2SND_RATE;
    dma.buffer = q2_dma_buf;

    q2_dma_open = 1;
    q2_dma_written = 0;
    q2_dma_start_ms = sys_time_ms();

    Com_Printf("pcm2 dma: %d Hz, %d mono samples (16-bit mixer)\n",
               dma.speed, dma.samples);
    return true;
}

/* Frames the device has finished, from the audio clock. Clamped to what has
 * actually been submitted so the engine (and the Submit window) can never
 * run ahead of the hardware. */
static long long q2_dma_played(void) {
    long long played =
        ((long long)(sys_time_ms() - q2_dma_start_ms) * Q2SND_RATE) / 1000;
    if (played < 0) played = 0;
    if (played > q2_dma_written) played = q2_dma_written;
    return played;
}

int SNDDMA_GetDMAPos(void) {
    long long played;
    if (!q2_dma_open) return 0;
    played = q2_dma_played();
    dma.samplepos = (int)(played & (Q2SND_SAMPLES - 1));
    return dma.samplepos;
}

void SNDDMA_Shutdown(void) {
    if (!q2_dma_open) return;
    Com_Printf("q2snd: pushed %lld bytes (%lld loud)\n",
               q2_dma_total, q2_dma_loud);
    if (q2_dma_loud > 0) Com_Printf("q2snd: audio present\n");
    sys_pcm2_close();
    free(q2_dma_buf);
    q2_dma_buf = NULL;
    dma.buffer = NULL;
    q2_dma_open = 0;
}

void SNDDMA_BeginPainting(void) {
}

void SNDDMA_Submit(void) {
    long long played, horizon;
    if (!q2_dma_open) return;
    if (paintedtime < q2_dma_written) q2_dma_written = paintedtime;
    /* Feed at most one kernel ring ahead of the play position; anything
     * further painted stays in dma.buffer for a later Submit. Pushing the
     * whole painted lead here would stall the frame for ~200 ms. */
    played = q2_dma_played();
    horizon = played + Q2SND_AHEAD;
    if (horizon > paintedtime) horizon = paintedtime;
    q2_dma_push((int)horizon);
}

/* Headless plumbing probe (BDD hook): open pcm2, stream one pattern, close,
 * report. Needs no game data, so it runs on a bare boot with the SB16
 * attached and is the serial proof that the Quake 2 backend reaches the
 * low-latency path. */
int q2snd_probe(void) {
    unsigned char pat[512];
    long rc, n;
    int i;

    for (i = 0; i < (int)sizeof(pat); i++)
        pat[i] = (unsigned char)(Q2SND_SILENCE + ((i * 5) & 0x3f) - 32);

    rc = sys_pcm2_open(0);
    if (rc < 0) {
        printf("q2snd: pcm2 open refused (%ld)\n", rc);
        return 1;
    }
    n = sys_pcm2_write(pat, (long)sizeof(pat));
    if (n != (long)sizeof(pat)) {
        printf("q2snd: pcm2 short write (%ld)\n", n);
        sys_pcm2_close();
        return 1;
    }
    sys_pcm2_close();
    printf("q2snd: pcm2 ok (accepted=%ld)\n", n);
    return 0;
}
