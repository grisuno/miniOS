/* sbtone.c — headless SB16 diagnostic (ring-3, no GUI).
 *
 * Opens the Sound Blaster 16 PCM sink and streams a clean 440 Hz sine for a
 * fixed window, pacing each 2048-byte buffer (~93 ms of audio) to wall time.
 * It reports how many buffers it actually submitted in the guest-time window
 * and how much guest time elapsed.  The point is to isolate the SB16 audio
 * path from the piano's GUI:
 *
 *   - a CLEAN 440 Hz tone and ~32 buffers in ~3000 ms means the SB16 driver
 *     is correct and fast, so the piano's slowness / garbage is its GUI;
 *   - garbage audio, or a submit count far below real time, points at the
 *     SB16 DMA / driver.
 *
 * Exit code is the number of submitted buffers (0 on failure to open).
 */

#include <stdio.h>
#include <math.h>
#include "minios_abi.h"

#define SYS_SB16_OPEN   MINIOS_SYS_SB16_OPEN
#define SYS_SB16_SUBMIT MINIOS_SYS_SB16_SUBMIT
#define SYS_TIME        MINIOS_SYS_TIME

#define RATE 22050u
#define BUF  2048u
#define WINDOW_MS 3000

static long call(long n, long a, long b, long d) {
    long r;
    __asm__ volatile("syscall":"=a"(r):"a"(n),"D"(a),"S"(b),"d"(d)
                     :"rcx","r11","memory");
    return r;
}

int main(void) {
    long st = call(SYS_SB16_OPEN, 1, 0, 0);
    if (st != 1) { printf("sbtone: no sb16\n"); return 0; }

    static unsigned char outbuf[BUF];
    int i;
    double ph = 0.0;
    for (i = 0; i < BUF; i++) {
        outbuf[i] = (unsigned char)(128 + 60 * sin(2.0 * 3.14159265 * 440.0 * ph / RATE));
        ph += 1.0;
    }

    long start = call(SYS_TIME, 0, 0, 0);
    long last = start;
    long ok = 0;
    long now = start;
    while (1) {
        now = call(SYS_TIME, 0, 0, 0);
        if (now - start >= WINDOW_MS) break;
        if (call(SYS_SB16_SUBMIT, (long)outbuf, BUF, 0) == 0) ok++;
        /* Pace each buffer to ~BUF/RATE seconds of audio (real-time). */
        long target = last + BUF * 1000 / RATE;
        while (call(SYS_TIME, 0, 0, 0) < target) __asm__ volatile("pause");
        last = call(SYS_TIME, 0, 0, 0);
    }

    long audio_ms = ok * BUF * 1000 / RATE;
    printf("sbtone: submitted %ld buffers (%ld ms audio) in %ld ms guest\n",
           ok, audio_ms, now - start);
    call(SYS_SB16_OPEN, 0, 0, 0);
    return (int)ok;
}
