/*
 * opl3: a ring-3 Nuked-OPL3 FM synthesizer feeding the SB16 DMA PCM path.
 *
 * This program is the proof of the real-audio chain end to end: it resets the
 * Nuked-OPL3 chip emulator, programs a simple 2-operator FM instrument, plays
 * a short melody, renders the chip output to 8-bit unsigned mono PCM at
 * 22050 Hz with OPL3_GenerateStream, and streams it to the kernel's Sound
 * Blaster 16 driver through the MiniOS PCM syscalls (221 open, 222 submit).
 *
 * Built like DOOM: host gcc -static, ring-3 ET_EXEC, ships on MiniFS.  When no
 * SB16 is present the submit syscall returns -1 and the program exits quietly
 * (it is an audio demo, not a diagnostic).  The FM instrument is a documented
 * 2-operator patch on channel 0 so the melody is musical, not a bare tone.
 */
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "opl3.h"

#define SYS_TIME         204
#define SYS_SB16_OPEN    221
#define SYS_SB16_SUBMIT  222
#define SYS_WRITE        1

static long gen_ms;

#define SAMPLE_RATE 22050u
#define STEREO_FRAMES 2048u       /* int16 pairs per submit == SB16 PCM buf */
#define MONO_BYTES   STEREO_FRAMES /* 1 byte per sample, matches SB16 buf */

#define BUF_MS (STEREO_FRAMES * 1000u / SAMPLE_RATE) /* audio ms per buffer */

#define F_NUM_FACTOR 65536.0 / 49716.0

static long sys_time(void) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(SYS_TIME),"D"(0):"rcx","r11","memory"); return r;
}
static long sys_open(long on) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(SYS_SB16_OPEN),"D"(on):"rcx","r11","memory"); return r;
}
static long sys_submit(const void *buf, long len) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(SYS_SB16_SUBMIT),"D"((long)buf),"S"(len):"rcx","r11","memory"); return r;
}

static void busy_ms(long ms) {
    long t0 = sys_time();
    while (sys_time() - t0 < ms) __asm__ volatile("pause");
}

/* 2-op FM instrument, channel 0 (modulator op0, carrier op1). */
static void opl3_set_instrument(opl3_chip *chip) {
    /* modulator op0 */
    OPL3_WriteReg(chip, 0x20, 0x01);  /* MULT 1, no AM/VIB/EG */
    OPL3_WriteReg(chip, 0x40, 0x10);  /* KSL 0, level */
    OPL3_WriteReg(chip, 0x60, 0xF0);  /* attack fast */
    OPL3_WriteReg(chip, 0x80, 0xF5);  /* sustain full, short release */
    OPL3_WriteReg(chip, 0xE0, 0x00);  /* waveform sine */
    /* carrier op1 */
    OPL3_WriteReg(chip, 0x21, 0x01);  /* MULT 1 */
    OPL3_WriteReg(chip, 0x41, 0x00);  /* loud */
    OPL3_WriteReg(chip, 0x61, 0x93);  /* attack, decay */
    OPL3_WriteReg(chip, 0x81, 0xF5);  /* sustain, release */
    OPL3_WriteReg(chip, 0xE1, 0x00);
    /* channel 0: feedback 0, algorithm 0 (FM mod->carrier) */
    OPL3_WriteReg(chip, 0xC0, 0x00);
}

static void opl3_note(opl3_chip *chip, unsigned block, unsigned fnum, int on) {
    OPL3_WriteReg(chip, 0xA0, fnum & 0xFF);
    OPL3_WriteReg(chip, 0xB0, (unsigned char)((block << 2) | ((fnum >> 8) & 0x03) | (on ? 0x20 : 0)));
}

/* Render `ms` of the current note and stream it to the SB16.  Each submit is
 * one DMA buffer of MONO_BYTES; submissions are paced to real-time audio
 * (BUF_MS each) so the kernel ring stays full without overflowing. */
static void render(opl3_chip *chip, long ms, long *fail) {
    static int16_t stereo[STEREO_FRAMES * 2];
    static unsigned char mono[MONO_BYTES];
    long samples = ms * (long)SAMPLE_RATE / 1000;
    long bufs = (samples + (long)STEREO_FRAMES - 1) / (long)STEREO_FRAMES;
    long i;
    for (i = 0; i < bufs; i++) {
        long t0 = sys_time();
        OPL3_GenerateStream(chip, stereo, STEREO_FRAMES);
        gen_ms += sys_time() - t0;
        unsigned j;
        for (j = 0; j < MONO_BYTES; j++) {
            int l = stereo[j * 2];
            int r = stereo[j * 2 + 1];
            int m = (l + r) / 2;                 /* mono mix */
            int u = (m / 256) + 128;             /* 16-bit -> 8-bit unsigned */
            if (u < 0) u = 0;
            if (u > 255) u = 255;
            mono[j] = (unsigned char)u;
        }
        if (sys_submit(mono, MONO_BYTES) != 0 && *fail == 0) *fail = 1;
        busy_ms(BUF_MS);
    }
}

typedef struct { unsigned block; unsigned fnum; long ms; } note_t;

static const double scale[10] = { 220.00, 246.94, 261.63, 293.66, 329.63,
                                  349.23, 392.00, 440.00, 493.88, 523.25 };

int main(void) {
    opl3_chip chip;
    long fail = 0;

    OPL3_Reset(&chip, SAMPLE_RATE);
    opl3_set_instrument(&chip);
    sys_open(1);                       /* switch the SB16 to PCM mode */

    /* A little run up the scale, then back down. */
    int i;
    for (i = 0; i < 10; i++) {
        unsigned fnum = (unsigned)(scale[i] * F_NUM_FACTOR);
        opl3_note(&chip, 4, fnum, 1);
        render(&chip, 160, &fail);
        opl3_note(&chip, 4, fnum, 0);
    }
    for (i = 8; i >= 1; i--) {
        unsigned fnum = (unsigned)(scale[i] * F_NUM_FACTOR);
        opl3_note(&chip, 4, fnum, 1);
        render(&chip, 160, &fail);
        opl3_note(&chip, 4, fnum, 0);
    }

    /* Let the SB16 drain before we exit so the tail is not cut off. */
    busy_ms(300);

    char msg[96];
    int n = snprintf(msg, sizeof(msg),
                     "opl3: gen_ms=%ld failures=%ld (%s)\n", gen_ms, fail,
                     fail ? "dropped" : "streamed clean");
    __asm__ volatile("syscall"::"a"(SYS_WRITE),"D"(1),"S"(msg),"d"((long)n)
                     :"rcx","r11","memory");
    return 0;
}
