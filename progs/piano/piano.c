/* piano.c — a Nuklear piano that plays real FM sound through the SB16 driver.
 *
 * A ring-3 static ELF app (built like the node editor and DOOM: host gcc
 * -static, ships on MiniFS, launched from a desktop icon).  It renders a
 * clickable two-octave piano keyboard with Nuklear, and each key triggers a
 * note on the Nuked-OPL3 FM synthesizer.  The OPL3 output is mixed to 8-bit
 * mono PCM and streamed to the kernel's Sound Blaster 16 driver through the
 * MiniOS PCM syscalls (221 open, 222 submit) — the same real-audio path the
 * SB16 driver provides.  Polyphonic up to OPL3's 18 FM voices.
 *
 * The audio is decoupled from the UI frame rate: each frame renders exactly
 * the PCM for the wall-clock time elapsed since the last frame and submits it
 * in SB16-sized buffers, so the ring paces output in real time and the UI
 * never stalls.  With no SB16 the PCM open fails and the piano is silent but
 * still fully interactive.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "nuklear.h"
#include "nuklear_minios.h"
#include "opl3.h"

#define UI_MEMORY (4 * 1024 * 1024)
static char ui_memory[UI_MEMORY];

#define SYS_SB16_OPEN   221
#define SYS_SB16_SUBMIT 222

#define RATE    22050u
#define PCM_BUF 2048u        /* == SB16 PCM buffer size (bytes) */
#define MAX_MS  50           /* per-frame audio budget (ms) */

static long sys_pcm_open(long on) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(SYS_SB16_OPEN),"D"(on):"rcx","r11","memory"); return r;
}
static long sys_pcm_submit(const void *buf, long len) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(SYS_SB16_SUBMIT),"D"((long)buf),"S"(len):"rcx","r11","memory"); return r;
}

/* ── OPL3 FM engine ─────────────────────────────────────────────────── */
static opl3_chip o3;
static int audio_on;

static void o3_opreg(int op, int regbase, int val) {
    int base = op < 18 ? 0x00 : 0x100;
    OPL3_WriteReg(&o3, (uint16_t)(base + regbase + (op % 18)), (uint8_t)val);
}
static void o3_chreg(int ch, int regbase, int val) {
    int base = ch < 9 ? 0x00 : 0x100;
    OPL3_WriteReg(&o3, (uint16_t)(base + regbase + (ch % 9)), (uint8_t)val);
}

static void o3_instrument(int ch) {
    int mod = 2 * ch, car = 2 * ch + 1;
    o3_opreg(mod, 0x20, 0x01);
    o3_opreg(mod, 0x40, 0x18);
    o3_opreg(mod, 0x60, 0x42);
    o3_opreg(mod, 0x80, 0x85);
    o3_opreg(mod, 0xE0, 0x00);
    o3_opreg(car, 0x20, 0x01);
    o3_opreg(car, 0x40, 0x08);
    o3_opreg(car, 0x60, 0x44);
    o3_opreg(car, 0x80, 0x77);
    o3_opreg(car, 0xE0, 0x00);
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

/* ── Polyphonic note allocator (up to OPL3's 18 voices) ─────────────── */
#define MAX_VOICES 18
static int key_to_chan[MAX_VOICES];   /* key index -> OPL3 channel, -1 = off */
static int chan_used[MAX_VOICES];

static void note_off_key(int key) {
    if (key < 0 || key >= MAX_VOICES) return;
    int ch = key_to_chan[key];
    if (ch < 0) return;
    o3_note(ch, 0, 0);
    chan_used[ch] = 0;
    key_to_chan[key] = -1;
}
static void note_on_key(int key, int midi) {
    if (key < 0 || key >= MAX_VOICES || !audio_on) return;
    if (key_to_chan[key] >= 0) return;
    int ch;
    for (ch = 0; ch < MAX_VOICES; ch++) if (!chan_used[ch]) break;
    if (ch >= MAX_VOICES) return;                 /* all voices busy */
    chan_used[ch] = 1;
    key_to_chan[key] = ch;
    o3_instrument(ch);
    o3_note(ch, midi, 1);
}

/* ── PCM renderer (bounded per frame, ring-paced) ───────────────────── */
static unsigned char obuf[PCM_BUF];
static int fill;
static long last_render;

static void render_audio(long ms) {
    static int16_t st[512 * 2];
    long nsamples = ms * (long)RATE / 1000;
    long left = nsamples;
    while (left > 0) {
        long n = left < 512 ? left : 512;
        OPL3_GenerateStream(&o3, st, (uint32_t)n);
        long i;
        for (i = 0; i < n; i++) {
            int m = (st[i * 2] + st[i * 2 + 1]) / 2;
            if (m > 32767) m = 32767;
            if (m < -32768) m = -32768;
            obuf[fill++] = (unsigned char)((m >> 8) + 128);
            if (fill == PCM_BUF) {
                sys_pcm_submit(obuf, PCM_BUF);
                fill = 0;
            }
        }
        left -= n;
    }
}

/* ── Keyboard model: two octaves C3..C5 (14 white + 10 black keys) ──── */
#define KEY_W 42
#define KEY_H 150
#define BK_W   26
#define BK_H   100
#define KEY_Y  60

static const struct { int black; int midi; int x; } keys[] = {
    {0, 48,   0}, {1, 49,  29}, {0, 50,  42}, {1, 51,  71}, {0, 52,  84},
    {0, 53, 126}, {1, 54, 155}, {0, 55, 168}, {1, 56, 197}, {0, 57, 210},
    {1, 58, 239}, {0, 59, 252},
    {0, 60, 294}, {1, 61, 323}, {0, 62, 336}, {1, 63, 365}, {0, 64, 378},
    {0, 65, 420}, {1, 66, 449}, {0, 67, 462}, {1, 68, 491}, {0, 69, 504},
    {1, 70, 533}, {0, 71, 546},
};
#define NKEYS ((int)(sizeof(keys) / sizeof(keys[0])))

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

/* ── UI ─────────────────────────────────────────────────────────────── */
static void ui_run(void) {
    unsigned char pal768[768];
    int fw, fh, fp;

    nk_sys_vga_mode(1);
    nk_sys_kbd_raw(1);
    nk_build_palette(pal768);
    nk_sys_palette(pal768);
    nk_sys_fb_info(&fw, &fh, &fp);

    audio_on = sys_pcm_open(1) == 1 ? 1 : 0;
    OPL3_Reset(&o3, RATE);
    int i;
    for (i = 0; i < MAX_VOICES; i++) key_to_chan[i] = -1;
    last_render = (long)nk_sys_time_ms();

    struct nk_user_font font = nk_minios_font();
    struct nk_context ctx;
    if (!nk_init_fixed(&ctx, ui_memory, UI_MEMORY, &font)) {
        printf("piano: init failed\n");
        nk_sys_kbd_raw(0);
        nk_sys_vga_mode(0);
        return;
    }

    int origin[2] = {0, 0};
    int quit = 0;
    int last_mouse[2] = {-1, -1};
    int last_down = 0;
    while (!quit) {
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
                struct nk_color col = keys[k].black
                    ? nk_rgb(20, 20, 20)
                    : (k % 7 == 0 || k % 7 == 3 ? nk_rgb(235, 235, 235)
                                                : nk_rgb(245, 245, 245));
                nk_fill_rect(canvas, r, 0, col);
                nk_stroke_rect(canvas, r, 0, 1, nk_rgb(90, 90, 90));
            }
            nk_fill_rect(canvas, nk_rect(0, 0, (float)NK_W, 44), 0, nk_rgb(40, 40, 40));
            nk_text(&ctx, audio_on ? "OPL3 FM piano -> SB16" : "piano (no SB16: silent)",
                    0, NK_TEXT_CENTERED);
            nk_text(&ctx, "Click the keys to play. Two octaves, 18-voice FM.",
                    0, NK_TEXT_CENTERED);
        }
        nk_end(&ctx);

        /* Note on/off from the mouse. */
        int hit = hit_key((int)mx, (int)my);
        if (down && !last_down && hit >= 0)
            note_on_key(hit, keys[hit].midi);
        else if (!down && last_down) {
            if (hit >= 0) note_off_key(hit);
        }
        last_down = down;

        nk_rasterize(&ctx);
        if (nk_sys_nk_frame(origin) == 0)
            nk_set_window_origin(origin[0], origin[1]);
        nk_clear(&ctx);

        /* Render the PCM for the wall-clock time since the last frame. */
        long now = (long)nk_sys_time_ms();
        long elapsed = now - last_render;
        last_render = now;
        if (elapsed > 0) {
            if (elapsed > MAX_MS) elapsed = MAX_MS;
            if (audio_on) render_audio(elapsed);
        }

        unsigned t0 = (unsigned)nk_sys_time_ms();
        while ((unsigned)nk_sys_time_ms() - t0 < 8) __asm__ volatile("pause");
    }

    nk_free(&ctx);
    nk_sys_kbd_raw(0);
    nk_sys_vga_mode(0);
    sys_pcm_open(0);
}

int main(int argc, char **argv) {
    (void)argc; (void)argv;
    ui_run();
    return 0;
}
