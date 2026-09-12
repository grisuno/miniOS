/* piano.c — a Nuklear piano that plays FM sound through the SB16 driver.
 *
 * A ring-3 static ELF app (built like the node editor and DOOM: host gcc
 * -static, ships on MiniFS, launched from a desktop icon).  It renders a
 * clickable three-octave piano keyboard (C4..B6, middle C base so the
 * default octave already sings instead of rumbling) with Nuklear, and each
 * key triggers a note on the Nuked-OPL3 FM chip emulator: one modulator +
 * one carrier per channel driving a real Yamaha FM engine.  The emulator
 * is cycle-accurate but heavy, so it renders in small bounded per-frame
 * bites (PIANO_FRAME_MS) into the mono mix; the backlog stays as debt for
 * later frames, so the ring never starves and the UI never blocks on one
 * giant catch-up render.  The mix is 8-bit mono PCM streamed to the
 * kernel's Sound Blaster 16 driver through the MiniOS PCM syscalls
 * (221 open, 222 submit, 224 pump) — the same real-audio path the SB16
 * driver provides.  The frame loop yields instead of busy-spinning, so the
 * mouse keeps its poll rate while audio renders.
 *
 * The PC keyboard is a MIDI keyboard (Fruity Loops style): the A row
 * (A S D F G H J K L ;) plays white keys, the Q row (W E T Y U O P)
 * plays the black keys between them, the Z row (Z X C V B N M) plays a
 * bass octave of whites, and 2 3 5 6 7 alias the upper black keys.
 * Comma/period shift the octave; every key press/release is tracked per
 * scancode so melodies and chords are playable without the mouse.
 *
 * Expressive controls, all integer-friendly on the mix path:
 *   - velocity: the click's vertical position inside a key sets the note
 *     loudness (top = soft, bottom = loud) by biasing the OPL3 carrier
 *     output level, FM's native amplitude control (keyboard notes use 80).
 *   - sustain pedal: while held, key releases are deferred and the FM voice
 *     keeps ringing (OPL3 decays naturally) until the pedal is released;
 *     a full 18-voice press steals the oldest sustained voice rather than
 *     dropping the new note.
 *   - octave shift (-2..+2) and a master volume (0..100).
 *   - live DSP effects on the mono mix, bounded and real-time: an echo /
 *     delay line (feedback + wet), a tremolo LFO and a soft clip.
 *
 * `piano --selftest` is a headless regression hook over the serial console:
 * it exercises the velocity mapping, sustain hold/release, octave clamp,
 * the keyboard map and every FX stage on synthetic input and prints
 * `piano: selftest ok` or a diagnostic.  It needs neither the SB16 nor the
 * GUI, so the BDD suite can assert the DSP never regresses.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "nuklear.h"
#include "nuklear_minios.h"
#include "nuklear_theme.h"
#include "opl3.h"
#include "minios_abi.h"

#define UI_MEMORY (4 * 1024 * 1024)
static char ui_memory[UI_MEMORY];

#define SYS_SB16_OPEN   MINIOS_SYS_SB16_OPEN
#define SYS_SB16_SUBMIT MINIOS_SYS_SB16_SUBMIT
#define SYS_SB16_PUMP   MINIOS_SYS_SB16_PUMP

#define RATE    22050u
#define PCM_BUF 2048u        /* == SB16 PCM buffer size (bytes) */
/* Upper bound on audio rendered per frame, in milliseconds.  The kernel-side
 * audio ring absorbs up to ~3 seconds of buffered PCM, so a slow frame can
 * render more without starving the speaker.  The clamp is kept conservative
 * to avoid unbounded per-frame work. */
#define MAX_AUDIO_MS 600
/* Per-frame render bite: after a stall the backlog is paced over several
 * frames instead of one giant catch-up render, bounding the worst-case CPU
 * spike (Nuked OPL3 is heavy) while the debt below is preserved, so not a
 * single millisecond of audio is lost.  Kept small (15 ms) on purpose: a
 * 30 ms bite costs a full extra frame of OPL3 time and halves the mouse
 * poll rate while the backlog drains; 15 ms still outruns the ~93 ms DMA
 * buffer so the ring never starves. */
#define PIANO_FRAME_MS 15

static long sys_pcm_open(long on) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(SYS_SB16_OPEN),"D"(on):"rcx","r11","memory"); return r;
}
static long sys_pcm_submit(const void *buf, long len) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(SYS_SB16_SUBMIT),"D"((long)buf),"S"(len):"rcx","r11","memory"); return r;
}
static long sys_pcm_pump(void) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(SYS_SB16_PUMP):"rcx","r11","memory"); return r;
}
static void sys_yield(void) {
    __asm__ volatile("syscall"::"a"(MINIOS_SYS_SCHED_YIELD):"rcx","r11","memory");
}

/* ── Nuked-OPL3 FM engine ───────────────────────────────────────────── */
static opl3_chip o3;
static int audio_on;

/* OPL operator numbers are NOT contiguous per channel: within a bank the
 * modulators live at 0,1,2 / 8,9,10 / 16,17,18 and each carrier three
 * slots later (3,4,5 / 11,12,13 / 19,20,21).  Addressing the carrier as
 * 2*ch+1 programs channel ch+1's modulator instead and leaves the real
 * carrier at its reset values (attack rate 0: never opens audibly), so
 * every note played silence. */
static int o3_bank(int ch) { return ch < 9 ? 0x00 : 0x100; }
static int o3_op(int ch, int is_car) {
    int i = ch % 9;
    return (i % 3) + 8 * (i / 3) + (is_car ? 3 : 0);
}
static void o3_opreg(int ch, int is_car, int regbase, int val) {
    OPL3_WriteReg(&o3, (uint16_t)(o3_bank(ch) + regbase + o3_op(ch, is_car)),
                  (uint8_t)val);
}
static void o3_chreg(int ch, int regbase, int val) {
    OPL3_WriteReg(&o3, (uint16_t)(o3_bank(ch) + regbase + (ch % 9)),
                  (uint8_t)val);
}

/* Program one FM patch; `vel` (1..100) biases the carrier output level so a
 * louder velocity is audibly less attenuated, FM's native amplitude.
 * Percussive envelope (attack rate 15): a clicked note must open at once. */
static void o3_instrument(int ch, int vel) {
    int tl = 0x08 + ((100 - vel) * 0x1F) / 100;   /* 0x08 (loud) .. 0x27 (soft) */
    if (tl > 0x3F) tl = 0x3F;
    o3_opreg(ch, 0, 0x20, 0x01);
    o3_opreg(ch, 0, 0x40, 0x18);
    o3_opreg(ch, 0, 0x60, 0xF2);
    o3_opreg(ch, 0, 0x80, 0x85);
    o3_opreg(ch, 0, 0xE0, 0x00);
    o3_opreg(ch, 1, 0x20, 0x01);
    o3_opreg(ch, 1, 0x40, (uint8_t)tl);
    o3_opreg(ch, 1, 0x60, 0xF4);
    o3_opreg(ch, 1, 0x80, 0x77);
    o3_opreg(ch, 1, 0xE0, 0x00);
    o3_chreg(ch, 0xC0, 0x00);
}

static const double midi_freq[128] = {
    8.18, 8.66, 9.18, 9.72, 10.30, 10.91, 11.56, 12.25, 12.98, 13.75, 14.57, 15.43,
    16.35, 17.32, 18.35, 19.45, 20.60, 21.83, 23.12, 24.50, 25.96, 27.50, 29.14, 30.87,
    32.70, 34.65, 36.71, 38.89, 41.20, 43.65, 46.25, 49.00, 51.91, 55.00, 58.27, 61.74,
    65.41, 69.30, 73.42, 77.78, 82.41, 87.31, 92.50, 98.00, 103.83, 110.00, 116.54, 123.47,
    130.81, 138.59, 146.83, 155.56, 164.81, 174.61, 185.00, 196.00, 207.65, 220.00, 233.08, 246.94,
    261.63, 277.18, 293.66, 311.13, 329.63, 349.23, 369.99, 392.00, 415.30, 440.00, 466.16, 493.88,
    523.25, 554.37, 587.33, 622.25, 659.25, 698.46, 739.99, 783.99, 830.61, 880.00, 932.33, 987.77,
    1046.50, 1108.73, 1174.66, 1244.51, 1318.51, 1396.91, 1479.98, 1567.98, 1661.22, 1760.00, 1864.66, 1975.53,
    2093.00, 2217.46, 2349.32, 2489.02, 2637.02, 2793.83, 2959.96, 3135.96, 3322.44, 3520.00, 3729.31, 3951.07,
    4186.01, 4434.92, 4698.63, 4978.03, 5274.04, 5587.65, 5919.91, 6271.93, 6644.88, 7040.00, 7458.62, 7902.13,
    8372.02, 8869.84, 9397.27, 9956.06
};

static void o3_note(int ch, int midi, int on) {
    if (!on) { o3_chreg(ch, 0xB0, 0); return; }
    double freq = midi_freq[midi];
    int block = 0;
    double t = freq;
    while (t * 65536.0 / 49716.0 > 1000.0 && block < 7) { t *= 0.5; block++; }
    unsigned fnum = (unsigned)(t * 65536.0 / 49716.0);
    o3_chreg(ch, 0xA0, fnum & 0xFF);
    o3_chreg(ch, 0xB0, ((unsigned)block << 2) | ((fnum >> 8) & 3) | 0x20);
}

/* ── Keyboard model: three octaves C4..B6 (21 white + 15 black keys) ──
 * Base is middle C (MIDI 60 = 261 Hz) so the default octave sings; the old
 * C3 base (130 Hz) rumbled even two octaves up.  21 whites at 36 px span
 * 756 px and fit the 800 px Nuklear window.  The table is chromatic
 * (midi 60..95) so midi_to_key is just midi - PIANO_BASE_MIDI.  Lives above
 * the voice code because key_to_chan is indexed (and sized) by key number. */
#define KEY_W 36
#define KEY_H 138
#define BK_W  22
#define BK_H  88
#define KEY_Y  72
#define PIANO_BASE_MIDI 60
#define PIANO_OCTAVES 3

static const struct { int black; int midi; int x; } keys[] = {
    {0, 60,   0}, {1, 61,  25}, {0, 62,  36}, {1, 63,  61}, {0, 64,  72},
    {0, 65, 108}, {1, 66, 133}, {0, 67, 144}, {1, 68, 169}, {0, 69, 180},
    {1, 70, 205}, {0, 71, 216},
    {0, 72, 252}, {1, 73, 277}, {0, 74, 288}, {1, 75, 313}, {0, 76, 324},
    {0, 77, 360}, {1, 78, 385}, {0, 79, 396}, {1, 80, 421}, {0, 81, 432},
    {1, 82, 457}, {0, 83, 468},
    {0, 84, 504}, {1, 85, 529}, {0, 86, 540}, {1, 87, 565}, {0, 88, 576},
    {0, 89, 612}, {1, 90, 637}, {0, 91, 648}, {1, 92, 673}, {0, 93, 684},
    {1, 94, 709}, {0, 95, 720},
};
#define NKEYS ((int)(sizeof(keys) / sizeof(keys[0])))

static int midi_to_key(int midi) {
    if (midi < PIANO_BASE_MIDI || midi >= PIANO_BASE_MIDI + NKEYS) return -1;
    return midi - PIANO_BASE_MIDI;
}

/* ── Expressive note state: velocity, sustain, octave ─────────────────
 * Voices (MAX_VOICES, the OPL3 channel count) and keys (NKEYS, the UI
 * key count) are different things: key_to_chan maps every key to its
 * sounding channel, so it is sized by NKEYS.  Sizing it by MAX_VOICES
 * wrote past the end for the top keys and left them mute. */
#define MAX_VOICES 18
static int key_to_chan[NKEYS];   /* key index -> OPL3 channel, -1 = off */
static int chan_used[MAX_VOICES];
static int chan_sustained[MAX_VOICES];/* key released but pedal holds the voice */
static int chan_midi[MAX_VOICES];/* midi sounding per channel, for kbd paint */
/* Per-scancode voice tracking so chords and fast melodies work: each
 * pressed scancode owns its channel until release.  Indexed by 7-bit code. */
static int sc_chan[128];

static int sustain_pedal;
static int octave;                    /* -2..+2, note shifted by 12*octave */
static int volume;                    /* 0..100 master, applied on the mix */

static int clamp_midi(int m) {
    if (m < 0) m = 0;
    if (m > 127) m = 127;
    return m;
}

/* Release every voice the pedal is holding (pedal lifted). */
static void pedal_set(int on) {
    sustain_pedal = on;
    if (on) return;
    int ch;
    for (ch = 0; ch < MAX_VOICES; ch++) {
        if (chan_sustained[ch]) {
            o3_note(ch, 0, 0);
            chan_used[ch] = 0;
            chan_sustained[ch] = 0;
            chan_midi[ch] = -1;
        }
    }
}

static int voice_alloc(void) {
    int ch;
    for (ch = 0; ch < MAX_VOICES; ch++) if (!chan_used[ch]) return ch;
    /* All voices busy: steal the oldest sustained voice, never drop a
     * new note because a held pedal blocked every channel. */
    for (ch = 0; ch < MAX_VOICES; ch++) if (chan_sustained[ch]) break;
    if (ch >= MAX_VOICES) return -1;
    o3_note(ch, 0, 0);
    chan_sustained[ch] = 0;
    chan_midi[ch] = -1;
    return ch;
}

static void note_off_key(int key) {
    if (key < 0 || key >= NKEYS) return;
    int ch = key_to_chan[key];
    if (ch < 0) return;
    if (sustain_pedal) {
        chan_sustained[ch] = 1;       /* let FM ring until the pedal lifts */
        key_to_chan[key] = -1;
        return;
    }
    o3_note(ch, 0, 0);
    chan_used[ch] = 0;
    key_to_chan[key] = -1;
}
static void note_on_key(int key, int midi, int vel) {
    if (key < 0 || key >= NKEYS || !audio_on) return;
    if (key_to_chan[key] >= 0) return;   /* same key already sounding */
    int ch = voice_alloc();
    if (ch < 0) return;
    chan_used[ch] = 1;
    key_to_chan[key] = ch;
    o3_instrument(ch, vel);
    o3_note(ch, clamp_midi(midi + 12 * octave), 1);
}

/* ── PC-keyboard MIDI map (Fruity Loops style) ─────────────────────────
 * PS/2 set-1 scancodes (7-bit code, E0 clear) to semitone offsets from the
 * UI base: A-row whites, Q-row blacks between them, Z-row bass whites,
 * digits aliasing the upper blacks.  Comma/period are octave down/up and
 * are handled in the hook, not here.  Returns -100 for "not a note". */
#define KBD_NO_NOTE (-100)
static int kbd_semitone(int code) {
    switch (code) {
    case 0x1E: return 0;    /* A C     */
    case 0x11: return 1;    /* W C#    */
    case 0x1F: return 2;    /* S D     */
    case 0x12: return 3;    /* E D#    */
    case 0x20: return 4;    /* D E     */
    case 0x21: return 5;    /* F F     */
    case 0x14: return 6;    /* T F#    */
    case 0x22: return 7;    /* G G     */
    case 0x15: return 8;    /* Y G#    */
    case 0x23: return 9;    /* H A     */
    case 0x16: return 10;   /* U A#    */
    case 0x24: return 11;   /* J B     */
    case 0x25: return 12;   /* K C+1   */
    case 0x18: return 13;   /* O C#+1  */
    case 0x26: return 14;   /* L D+1   */
    case 0x19: return 15;   /* P D#+1  */
    case 0x27: return 16;   /* ; E+1   */
    case 0x2C: return -12;  /* Z bass C */
    case 0x2D: return -10;  /* X bass D */
    case 0x2E: return -8;   /* C bass E */
    case 0x2F: return -7;   /* V bass F */
    case 0x30: return -5;   /* B bass G */
    case 0x31: return -3;   /* N bass A */
    case 0x32: return -1;   /* M bass B */
    case 0x03: return 1;    /* 2 alias C# */
    case 0x04: return 3;    /* 3 alias D# */
    case 0x06: return 6;    /* 5 alias F# */
    case 0x07: return 8;    /* 6 alias G# */
    case 0x08: return 10;   /* 7 alias A# */
    default: return KBD_NO_NOTE;
    }
}

static void kbd_all_off(void) {
    int i;
    for (i = 0; i < 128; i++) sc_chan[i] = -1;
    for (i = 0; i < MAX_VOICES; i++) chan_midi[i] = -1;
}

static void note_on_sc(int code, int vel) {
    int off = kbd_semitone(code);
    if (off == KBD_NO_NOTE || !audio_on) return;
    if (code < 0 || code >= 128 || sc_chan[code] >= 0) return;
    int ch = voice_alloc();
    if (ch < 0) return;
    int midi = clamp_midi(PIANO_BASE_MIDI + off + 12 * octave);
    chan_used[ch] = 1;
    chan_midi[ch] = midi;
    sc_chan[code] = ch;
    o3_instrument(ch, vel);
    o3_note(ch, midi, 1);
}

static void note_off_sc(int code) {
    if (code < 0 || code >= 128) return;
    int ch = sc_chan[code];
    if (ch < 0) return;
    sc_chan[code] = -1;
    if (sustain_pedal) {
        chan_sustained[ch] = 1;
        return;
    }
    o3_note(ch, 0, 0);
    chan_used[ch] = 0;
    chan_midi[ch] = -1;
}

/* Raw scancode hook (registered with nk_set_scancode_hook): note on/off
 * plus comma/period octave shift.  Extended (E0) keys are ignored. */
static void piano_scancode(int code, int make, int e0, void *ud) {
    (void)ud;
    if (e0) return;
    if (code == 0x33) {             /* , octave down */
        if (make && octave > -2) octave--;
        return;
    }
    if (code == 0x34) {             /* . octave up */
        if (make && octave < 2) octave++;
        return;
    }
    if (make) note_on_sc(code, 80);
    else note_off_sc(code);
}

/* A UI key lights up when the mouse holds it or any keyboard voice sounds
 * its (octave-shifted) midi. */
static int key_sounding(int key) {
    if (key < 0 || key >= NKEYS) return 0;
    if (key_to_chan[key] >= 0) return 1;
    int want = clamp_midi(keys[key].midi + 12 * octave);
    int c;
    for (c = 0; c < 128; c++) {
        int ch = sc_chan[c];
        if (ch >= 0 && ch < MAX_VOICES && chan_midi[ch] == want) return 1;
    }
    return 0;
}

/* ── Live DSP effects on the mono mix ───────────────────────────────── */
/* Real-time, bounded, applied per sample before the 8-bit conversion.
 *   delay:   an echo line (feedback + wet mix), 0 ms = off.
 *   tremolo: a low-frequency amplitude LFO, 0..100 depth.
 *   softclip: a tanh saturation that never exceeds [-1,1].
 *   volume:  the master gain 0..100.
 * Everything is exposed through fx_process so the headless selftest can drive
 * it without an SB16 or the GUI. */

#define FX_DELAY_CAP (RATE)           /* 1 s of delay at 22050 Hz */
#define FX_DELAY_MAX_MS 800
#define FX_FEEDBACK 0.35f
#define FX_WET      0.55f
#define FX_TREM_FREQ 5.0f

static float fx_delay_buf[FX_DELAY_CAP];
static int   fx_delay_len;            /* samples, 0 = echo off */
static int   fx_delay_pos;
static int   fx_tremolo_pct;          /* 0..100, 0 = tremolo off */
static float fx_trem_phase;
static int   fx_softclip;

/* (Re)configure every FX stage; also used by the selftest. */
static void fx_configure(int delay_ms, int tremolo_pct, int clip, int vol) {
    fx_tremolo_pct = tremolo_pct;
    fx_softclip = clip;
    volume = vol;
    if (delay_ms > 0) {
        int len = delay_ms * (int)RATE / 1000;
        if (len > FX_DELAY_CAP) len = FX_DELAY_CAP;
        if (len < 1) len = 1;
        if (len != fx_delay_len) {
            fx_delay_len = len;
            fx_delay_pos = 0;
            memset(fx_delay_buf, 0, sizeof(fx_delay_buf));
        }
    } else {
        fx_delay_len = 0;
    }
    fx_trem_phase = 0.0f;
}

static float fx_process(float x) {
    if (fx_delay_len > 0) {
        float d = fx_delay_buf[fx_delay_pos];
        fx_delay_buf[fx_delay_pos] = x + FX_FEEDBACK * d;
        x += FX_WET * d;
        fx_delay_pos = (fx_delay_pos + 1) % fx_delay_len;
    }
    if (fx_tremolo_pct > 0) {
        float depth = (float)fx_tremolo_pct / 100.0f;
        float lfo = 0.5f + 0.5f * sinf(fx_trem_phase);   /* 0..1 */
        x *= 1.0f - depth + depth * lfo;                  /* 1-depth .. 1 */
        fx_trem_phase += FX_TREM_FREQ * 2.0f * 3.14159265358979f / (float)RATE;
    }
    if (fx_softclip) x = tanhf(x);
    x *= (float)volume / 100.0f;
    return x;
}

/* ── PCM renderer (bounded per frame, ring-paced) ───────────────────── */
static unsigned char obuf[PCM_BUF];
static int fill;
static long last_render;
static unsigned long sb_submit_drops;

/* Flush a fully-filled buffer to the kernel audio ring.  When the ring is
 * full the submit is refused; the buffer is kept in place (fill stays at
 * PCM_BUF) so the next frame retries it, and a drop is counted only when a
 * new submit is blocked by a still-pending buffer, never silently.  After a
 * successful submit we call sys_pcm_pump to eagerly drain the kernel ring
 * into DMA slots, reducing playback latency on the fast path. */
static void sb_flush(void) {
    if (fill != PCM_BUF) return;
    if (sys_pcm_submit(obuf, PCM_BUF) == 0) {
        fill = 0;
        sys_pcm_pump();
    } else {
        sb_submit_drops++;
    }
}

static void render_audio(long ms) {
    static int16_t st[512 * 2];
    sb_flush();
    if (fill == PCM_BUF) return;    /* ring full: hold the buffer, wait */
    long nsamples = ms * (long)RATE / 1000;
    long left = nsamples;
    while (left > 0) {
        long n = left < 512 ? left : 512;
        OPL3_GenerateStream(&o3, st, (uint32_t)n);
        long i;
        for (i = 0; i < n; i++) {
            float x = (float)((st[i * 2] + st[i * 2 + 1]) / 2);
            x = fx_process(x);
            int out = (int)x;
            if (out > 32767) out = 32767;
            if (out < -32768) out = -32768;
            obuf[fill++] = (unsigned char)((out >> 8) + 128);
            if (fill == PCM_BUF) {
                sb_flush();
                if (fill == PCM_BUF) return;   /* ring full mid-frame */
            }
        }
        left -= n;
    }
}

static void key_rect(int key, int *x, int *y, int *w, int *h) {
    *x = keys[key].x;
    *y = KEY_Y;
    *w = keys[key].black ? BK_W : KEY_W;
    *h = keys[key].black ? BK_H : KEY_H;
}

static int hit_key(int mx, int my) {
    if (my < KEY_Y || my > KEY_Y + KEY_H) return -1;
    int i;
    for (i = 0; i < NKEYS; i++) {                 /* black keys first (on top) */
        if (!keys[i].black) continue;
        if (mx >= keys[i].x && mx < keys[i].x + BK_W && my < KEY_Y + BK_H)
            return i;
    }
    for (i = 0; i < NKEYS; i++) {
        if (keys[i].black) continue;
        if (mx >= keys[i].x && mx < keys[i].x + KEY_W) return i;
    }
    return -1;
}

/* Velocity 1..100 from the click's vertical position inside a key: the very
 * top is soft, the bottom is loud. */
static int hit_velocity(int key, int my) {
    int x, y, w, h;
    key_rect(key, &x, &y, &w, &h);
    int pct = (100 * (my - y)) / h;
    if (pct < 1) pct = 1;
    if (pct > 100) pct = 100;
    return pct;
}

/* ── Control bar (manual widgets, hit-tested like the keys) ─────────── */
#define CTRL_Y  (KEY_Y + KEY_H + 12)
#define CTRL_H  26
#define BTN_W   70
#define BTN_GAP 8

static const struct { int x; int y; int w; int h; const char *label; } ctrls[] = {
    { 0,            CTRL_Y, BTN_W, CTRL_H, "-Oct" },
    { BTN_W + BTN_GAP, CTRL_Y, BTN_W, CTRL_H, "+Oct" },
    { 2*(BTN_W + BTN_GAP), CTRL_Y, BTN_W, CTRL_H, "-Vol" },
    { 3*(BTN_W + BTN_GAP), CTRL_Y, BTN_W, CTRL_H, "+Vol" },
    { 4*(BTN_W + BTN_GAP), CTRL_Y, BTN_W, CTRL_H, "Sustain" },
    { 5*(BTN_W + BTN_GAP), CTRL_Y, BTN_W, CTRL_H, "Echo" },
    { 6*(BTN_W + BTN_GAP), CTRL_Y, BTN_W, CTRL_H, "Tremolo" },
    { 7*(BTN_W + BTN_GAP), CTRL_Y, BTN_W, CTRL_H, "Clip" },
    { 8*(BTN_W + BTN_GAP), CTRL_Y, BTN_W, CTRL_H, "Quit" },
};
#define NCTRLS ((int)(sizeof(ctrls) / sizeof(ctrls[0])))

static int ctrl_hit(int id, int mx, int my) {
    return mx >= ctrls[id].x && mx < ctrls[id].x + ctrls[id].w &&
           my >= ctrls[id].y && my < ctrls[id].y + ctrls[id].h;
}
static int ctrl_active(int id) {
    switch (id) {
    case 4: return sustain_pedal;
    case 5: return fx_delay_len > 0;
    case 6: return fx_tremolo_pct > 0;
    case 7: return fx_softclip;
    default: return 0;
    }
}

static void ctrl_press(int id) {
    switch (id) {
    case 0: if (octave > -2) octave--; break;
    case 1: if (octave < 2) octave++; break;
    case 2: if (volume > 0) volume -= 5; break;
    case 3: if (volume < 100) volume += 5; break;
    case 4: pedal_set(sustain_pedal ? 0 : 1); break;
    case 5: fx_configure(fx_delay_len > 0 ? 0 : 220, fx_tremolo_pct, fx_softclip, volume); break;
    case 6: fx_configure(fx_delay_len > 0 ? fx_delay_len * 1000 / (int)RATE : 0,
                         fx_tremolo_pct > 0 ? 0 : 70, fx_softclip, volume); break;
    case 7: fx_configure(fx_delay_len > 0 ? fx_delay_len * 1000 / (int)RATE : 0,
                         fx_tremolo_pct, fx_softclip ? 0 : 1, volume); break;
    default: break;
    }
}

/* ── UI ─────────────────────────────────────────────────────────────── */
static void ui_run(int bench_ms) {
    unsigned char pal768[768];
    int fw, fh, fp;

    nk_sys_vga_mode(1);
    nk_sys_gfx_set_title("Piano");
    nk_sys_kbd_raw(1);
    nk_build_palette(pal768);
    nk_sys_palette(pal768);
    nk_sys_fb_info(&fw, &fh, &fp);

    audio_on = sys_pcm_open(1) == 1 ? 1 : 0;
    OPL3_Reset(&o3, RATE);
    int i;
    for (i = 0; i < NKEYS; i++) key_to_chan[i] = -1;
    for (i = 0; i < MAX_VOICES; i++) {
        chan_used[i] = 0;
        chan_sustained[i] = 0;
    }
    kbd_all_off();
    nk_set_scancode_hook(piano_scancode, 0);
    sustain_pedal = 0;
    octave = 0;
    fx_configure(0, 0, 0, 80);
    last_render = (long)nk_sys_time_ms();

    struct nk_user_font font = nk_minios_font();
    struct nk_context ctx;
    if (!nk_init_fixed(&ctx, ui_memory, UI_MEMORY, &font)) {
        printf("piano: init failed\n");
        nk_sys_kbd_raw(0);
        nk_sys_vga_mode(0);
        return;
    }
    nk_theme_apply(&ctx, 0);

    int origin[2] = {0, 0};
    int quit = 0;
    int last_down = 0;
    int pressed_key = -1;
    long bench_start = (bench_ms > 0) ? (long)nk_sys_time_ms() : 0;
    long bench_frames = 0;
    while (!quit) {
        bench_frames++;
        if (bench_ms > 0 && (long)nk_sys_time_ms() - bench_start >= bench_ms) {
            printf("piano: bench %ld frames in %d ms (~%.1f fps)\n",
                   bench_frames, bench_ms,
                   (float)bench_frames * 1000.0f / (float)bench_ms);
            quit = 1;
            break;
        }
        nk_input_begin(&ctx);
        nk_poll_input(&ctx);
        nk_input_end(&ctx);

        float mx = ctx.input.mouse.pos.x;
        float my = ctx.input.mouse.pos.y;
        int down = nk_input_is_mouse_down(&ctx.input, NK_BUTTON_LEFT) ? 1 : 0;

        if (nk_begin_titled(&ctx, "piano", "Piano",
                            nk_rect(0, 0, (float)NK_W, (float)NK_H),
                            NK_WINDOW_NO_SCROLLBAR)) {
            struct nk_command_buffer *canvas = nk_window_get_canvas(&ctx);
            int k;
            for (k = 0; k < NKEYS; k++) {
                struct nk_rect r;
                r.x = (float)keys[k].x; r.y = (float)KEY_Y;
                r.w = (float)(keys[k].black ? BK_W : KEY_W);
                r.h = (float)(keys[k].black ? BK_H : KEY_H);
                /* A sounding key lights up red: click/keyboard feedback
                 * and a serial-free way to see that the press registered. */
                struct nk_color col = key_sounding(k)
                    ? nk_rgb(200, 60, 60)
                    : keys[k].black
                    ? nk_rgb(20, 20, 20)
                    : nk_rgb(240, 240, 240);
                nk_fill_rect(canvas, r, 0, col);
                nk_stroke_rect(canvas, r, 0, 1, nk_rgb(90, 90, 90));
            }
            /* Control bar: draw each button, highlighted when active. */
            int c;
            for (c = 0; c < NCTRLS; c++) {
                struct nk_rect r;
                r.x = (float)ctrls[c].x; r.y = (float)ctrls[c].y;
                r.w = (float)ctrls[c].w; r.h = (float)ctrls[c].h;
                int active = ctrl_active(c);
                nk_fill_rect(canvas, r, 0, active ? nk_rgb(120, 160, 80)
                                                  : nk_rgb(60, 60, 60));
                nk_stroke_rect(canvas, r, 0, 1, nk_rgb(90, 90, 90));
                nk_draw_text(canvas, r, ctrls[c].label,
                             (int)strlen(ctrls[c].label),
                             &font, nk_rgb(255, 255, 255), nk_rgb(0, 0, 0));
            }
            nk_fill_rect(canvas, nk_rect(0, 0, (float)NK_W, 44), 0, nk_rgb(40, 40, 40));
            char head[96];
            snprintf(head, sizeof(head), "OPL3 FM piano -> SB16  C4 base  oct%+d  vol%d",
                     octave, volume);
            /* Keyboard help line under the control bar. */
            {
                const char *help = "A-row whites  Q-row blacks  Z-row bass  ,/. octave";
                nk_draw_text(canvas,
                    nk_rect(8, (float)(CTRL_Y + CTRL_H + 8), (float)NK_W - 16, 16),
                    help, (int)strlen(help),
                    &font, nk_rgb(200, 200, 200), nk_rgb(0, 0, 0));
            }
            nk_draw_text(canvas,
                nk_rect(8, 10, (float)NK_W - 16, 24), head, (int)strlen(head),
                &font, audio_on ? nk_rgb(230, 230, 230) : nk_rgb(200, 90, 90),
                nk_rgb(0, 0, 0));
        }
        nk_end(&ctx);

        /* Note on/off and control presses from the mouse.  The pressed
         * key is latched on button-down so releasing off-key (or sliding
         * off while dragging) still releases the right voice instead of
         * leaving it stuck.  Keyboard notes arrive via piano_scancode. */
        if (nk_quit_requested()) quit = 1;
        int hit = hit_key((int)mx, (int)my);
        if (down && !last_down) {
            if (hit >= 0) {
                pressed_key = hit;
                note_on_key(hit, keys[hit].midi, hit_velocity(hit, (int)my));
            } else {
                int c;
                for (c = 0; c < NCTRLS; c++) if (ctrl_hit(c, (int)mx, (int)my)) {
                    if (c == NCTRLS - 1) quit = 1;
                    else ctrl_press(c);
                    break;
                }
            }
        } else if (!down && last_down) {
            if (pressed_key >= 0) {
                note_off_key(pressed_key);   /* sustain defers the release */
                pressed_key = -1;
            }
        }
        last_down = down;

        nk_rasterize(&ctx);
        if (nk_sys_nk_frame(origin) == 0)
            nk_set_window_origin(origin[0], origin[1]);
        nk_clear(&ctx);

        /* Render the PCM for the wall-clock time since the last frame,
         * paced: each frame renders at most PIANO_FRAME_MS and the rest
         * stays as debt for the frames after, so a stall never turns
         * into one giant catch-up spike.  The small bite keeps the frame
         * short so the mouse poll rate stays up while the backlog drains
         * over several frames. */
        long now = (long)nk_sys_time_ms();
        long elapsed = now - last_render;
        if (elapsed > MAX_AUDIO_MS) elapsed = MAX_AUDIO_MS;
        if (elapsed > PIANO_FRAME_MS) elapsed = PIANO_FRAME_MS;
        if (elapsed > 0 && audio_on) {
            render_audio(elapsed);
            last_render += elapsed;
        } else {
            last_render = now;
        }

        /* Yield instead of busy-spinning: the old 8 ms pause loop burned
         * CPU every frame and delayed input polling; a yield hands the
         * machine back so the mouse/ISR state stays fresh. */
        sys_yield();
    }

    nk_set_scancode_hook(0, 0);
    nk_free(&ctx);
    nk_sys_kbd_raw(0);
    nk_sys_vga_mode(0);
    sys_pcm_open(0);
}

/* ── Headless selftest (BDD hook) ───────────────────────────────────── */
static int run_selftest(void) {
    int i;
    audio_on = 1;
    OPL3_Reset(&o3, RATE);
    for (i = 0; i < NKEYS; i++) key_to_chan[i] = -1;
    for (i = 0; i < MAX_VOICES; i++) {
        chan_used[i] = 0;
        chan_sustained[i] = 0;
    }
    kbd_all_off();
    sustain_pedal = 0;
    octave = 0;
    fx_configure(0, 0, 0, 100);

    /* Velocity: the top of a key is soft, the bottom is loud. */
    int x, y, w, h;
    key_rect(0, &x, &y, &w, &h);
    int v_top = hit_velocity(0, y);
    int v_bot = hit_velocity(0, y + h - 1);
    if (!(v_top >= 1 && v_top <= 10 && v_bot >= 90 && v_bot <= 100)) {
        printf("piano: velocity range fail (%d..%d)\n", v_top, v_bot);
        return 1;
    }

    /* Sustain holds a released key until the pedal lifts. */
    sustain_pedal = 1;
    note_on_key(0, 60, 80);
    if (!chan_used[0]) { printf("piano: note_on did not grab a voice\n"); return 1; }
    note_off_key(0);
    if (!chan_sustained[0]) { printf("piano: sustain did not hold the release\n"); return 1; }
    if (!chan_used[0]) { printf("piano: sustain freed the voice early\n"); return 1; }
    pedal_set(0);
    if (chan_used[0] || chan_sustained[0]) {
        printf("piano: pedal release did not free the voice\n"); return 1;
    }
    sustain_pedal = 0;

    /* Octave transposition clamps to the MIDI range. */
    if (clamp_midi(127 + 12 * 6) != 127 || clamp_midi(0 - 12 * 6) != 0) {
        printf("piano: octave clamp fail\n"); return 1;
    }

    /* Keyboard map: A-row whites, Q-row blacks, Z-row bass, digits alias.
     * E-F and B-C gaps have no black key, so R and I are not notes. */
    kbd_all_off();
    if (kbd_semitone(0x1E) != 0 || kbd_semitone(0x11) != 1 ||
        kbd_semitone(0x1F) != 2 || kbd_semitone(0x12) != 3 ||
        kbd_semitone(0x20) != 4 || kbd_semitone(0x21) != 5 ||
        kbd_semitone(0x14) != 6 || kbd_semitone(0x22) != 7 ||
        kbd_semitone(0x15) != 8 || kbd_semitone(0x23) != 9 ||
        kbd_semitone(0x16) != 10 || kbd_semitone(0x24) != 11 ||
        kbd_semitone(0x2C) != -12 || kbd_semitone(0x03) != 1 ||
        kbd_semitone(0x01) != KBD_NO_NOTE) {
        printf("piano: kbd map fail\n"); return 1;
    }
    if (midi_to_key(PIANO_BASE_MIDI) != 0 ||
        midi_to_key(PIANO_BASE_MIDI + NKEYS - 1) != NKEYS - 1 ||
        midi_to_key(PIANO_BASE_MIDI - 1) != -1) {
        printf("piano: midi_to_key fail\n"); return 1;
    }

    /* Keyboard voices: press/release per scancode, chords overlap. */
    note_on_sc(0x1E, 80);
    note_on_sc(0x22, 80);
    if (sc_chan[0x1E] < 0 || sc_chan[0x22] < 0 ||
        sc_chan[0x1E] == sc_chan[0x22]) {
        printf("piano: kbd chord fail\n"); return 1;
    }
    if (!key_sounding(midi_to_key(60)) || !key_sounding(midi_to_key(67))) {
        printf("piano: kbd highlight fail\n"); return 1;
    }
    note_off_sc(0x1E);
    if (sc_chan[0x1E] >= 0 || !key_sounding(midi_to_key(67))) {
        printf("piano: kbd release fail\n"); return 1;
    }
    note_off_sc(0x22);
    /* Sustain holds a keyboard release too. */
    sustain_pedal = 1;
    note_on_sc(0x1E, 80);
    note_off_sc(0x1E);
    if (sc_chan[0x1E] >= 0) { printf("piano: kbd sustain track fail\n"); return 1; }
    pedal_set(0);
    sustain_pedal = 0;
    kbd_all_off();
    for (i = 0; i < NKEYS; i++) key_to_chan[i] = -1;
    for (i = 0; i < MAX_VOICES; i++) {
        chan_used[i] = 0;
        chan_sustained[i] = 0;
    }

    /* FX: master volume scales the mix. */
    fx_configure(0, 0, 0, 50);
    float vs = fx_process(0.8f);
    if (fabsf(vs - 0.4f) > 0.01f) { printf("piano: volume fail %.3f\n", vs); return 1; }

    /* FX: soft clip bounds the output to [-1,1]. */
    fx_configure(0, 0, 1, 100);
    float sc = fx_process(5.0f);
    if (!(sc > -1.0f && sc < 1.0f)) { printf("piano: softclip bounds fail %.3f\n", sc); return 1; }

    /* FX: the echo line keeps ringing after the input stops. */
    fx_configure(220, 0, 0, 100);
    fx_process(1.0f);                 /* one-sample impulse */
    float peak = 0.0f;
    for (i = 0; i < (int)RATE; i++) { /* let the echo ring for a full second */
        float v = fabsf(fx_process(0.0f));
        if (v > peak) peak = v;
    }
    if (peak < 0.3f) { printf("piano: echo tail missing (peak %.3f)\n", peak); return 1; }

    /* FX: the tremolo LFO modulates the amplitude from sample to sample. */
    fx_configure(0, 100, 0, 100);
    float t1 = fx_process(0.8f);
    float t2 = fx_process(0.8f);
    if (fabsf(t1 - t2) < 1e-6f) { printf("piano: tremolo not modulating\n"); return 1; }

    /* Audio pacing: one PCM buffer must span a full SB16 buffer duration
     * and a whole ring must be able to absorb a MAX_AUDIO_MS frame,
     * otherwise a slow frame either under-renders (starving the ring into
     * a buzz) or over-renders (silently dropping audio).  The per-frame
     * bite must stay below one DMA buffer so frames stay short and the
     * mouse poll rate never collapses while the backlog drains. */
    {
        long buf_ms = (long)PCM_BUF * 1000 / (long)RATE;
        long ring_ms = buf_ms * 7;
        if (MAX_AUDIO_MS <= buf_ms || MAX_AUDIO_MS > ring_ms) {
            printf("piano: pacing constants fail (max=%d buf=%ld ring=%ld)\n",
                   MAX_AUDIO_MS, buf_ms, ring_ms);
            return 1;
        }
        if (PIANO_FRAME_MS > buf_ms) {
            printf("piano: frame bite too big (%d > buf %ld)\n",
                   PIANO_FRAME_MS, buf_ms);
            return 1;
        }
    }

    /* FM voice energy: a triggered note must actually render samples.
     * A misaddressed carrier once made every note silent while all the
     * plumbing checks above passed, so the synth itself is asserted
     * (silence reads peak 1; a healthy voice peaks over 1000 here). */
    {
        static int16_t probe[512 * 2];
        long peak = 0;
        int n;
        note_on_key(0, 60, 80);
        for (n = 0; n < 6615; n += 512) {
            int m = n + 512 > 6615 ? 6615 - n : 512;
            int k;
            OPL3_GenerateStream(&o3, probe, (uint32_t)m);
            for (k = 0; k < m; k++) {
                long s = (probe[k * 2] + probe[k * 2 + 1]) / 2;
                if (s < 0) s = -s;
                if (s > peak) peak = s;
            }
        }
        note_off_key(0);
        if (peak < 500) {
            printf("piano: FM voice silent (peak %ld)\n", peak);
            return 1;
        }
    }

    printf("piano: selftest ok\n");
    return 0;
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "--selftest") == 0)
        return run_selftest();
    if (argc > 1 && strcmp(argv[1], "--bench") == 0) {
        ui_run(2000);
        return 0;
    }
    ui_run(0);
    return 0;
}
