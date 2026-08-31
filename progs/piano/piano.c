/* piano.c — a Nuklear piano that plays FM sound through the SB16 driver.
 *
 * A ring-3 static ELF app (built like the node editor and DOOM: host gcc
 * -static, ships on MiniFS, launched from a desktop icon).  It renders a
 * clickable two-octave piano keyboard with Nuklear, and each key triggers a
 * note on the Nuked-OPL3 FM chip emulator: one modulator + one carrier per
 * channel driving a real Yamaha FM engine.  The emulator is cycle-accurate
 * but heavy, so it renders in bounded per-frame blocks into the mono mix
 * rather than sample-by-sample; the app stays fluid because the PCM is
 * decoupled from the UI frame rate.  The mix is 8-bit mono PCM streamed to
 * the kernel's Sound Blaster 16 driver through the MiniOS PCM syscalls
 * (221 open, 222 submit) — the same real-audio path the SB16 driver provides.
 *
 * The audio is decoupled from the UI frame rate: each frame renders exactly
 * the PCM for the wall-clock time elapsed since the last frame and submits it
 * in SB16-sized buffers, so the ring paces output in real time and the UI
 * never stalls.  With no SB16 the PCM open fails and the piano is silent but
 * still fully interactive.
 *
 * Expressive controls, all integer-friendly on the mix path:
 *   - velocity: the click's vertical position inside a key sets the note
 *     loudness (top = soft, bottom = loud) by biasing the OPL3 carrier
 *     output level, FM's native amplitude control.
 *   - sustain pedal: while held, key releases are deferred and the FM voice
 *     keeps ringing (OPL3 decays naturally) until the pedal is released;
 *     a full 18-voice press steals the oldest sustained voice rather than
 *     dropping the new note.
 *   - octave shift and a master volume (0..100).
 *   - live DSP effects on the mono mix, bounded and real-time: an echo /
 *     delay line (feedback + wet), a tremolo LFO and a soft clip.
 *
 * `piano --selftest` is a headless regression hook over the serial console:
 * it exercises the velocity mapping, sustain hold/release, octave clamp and
 * every FX stage on synthetic input and prints `piano: selftest ok` or a
 * diagnostic.  It needs neither the SB16 nor the GUI, so the BDD suite can
 * assert the DSP never regresses.
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
#define SYS_SB16_PUMP   224

#define RATE    22050u
#define PCM_BUF 2048u        /* == SB16 PCM buffer size (bytes) */
/* Upper bound on audio rendered per frame, in milliseconds.  The kernel-side
 * audio ring absorbs up to ~3 seconds of buffered PCM, so a slow frame can
 * render more without starving the speaker.  The clamp is kept conservative
 * to avoid unbounded per-frame work. */
#define MAX_AUDIO_MS 600

static long sys_pcm_open(long on) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(SYS_SB16_OPEN),"D"(on):"rcx","r11","memory"); return r;
}
static long sys_pcm_submit(const void *buf, long len) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(SYS_SB16_SUBMIT),"D"((long)buf),"S"(len):"rcx","r11","memory"); return r;
}
static long sys_pcm_pump(void) {
    long r; __asm__ volatile("syscall":"=a"(r):"a"(SYS_SB16_PUMP):"rcx","r11","memory"); return r;
}

/* ── Nuked-OPL3 FM engine ───────────────────────────────────────────── */
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

/* Program one FM patch; `vel` (1..100) biases the carrier output level so a
 * louder velocity is audibly less attenuated, FM's native amplitude. */
static void o3_instrument(int ch, int vel) {
    int mod = 2 * ch, car = 2 * ch + 1;
    int tl = 0x08 + ((100 - vel) * 0x1F) / 100;   /* 0x08 (loud) .. 0x27 (soft) */
    if (tl > 0x3F) tl = 0x3F;
    o3_opreg(mod, 0x20, 0x01);
    o3_opreg(mod, 0x40, 0x18);
    o3_opreg(mod, 0x60, 0x42);
    o3_opreg(mod, 0x80, 0x85);
    o3_opreg(mod, 0xE0, 0x00);
    o3_opreg(car, 0x20, 0x01);
    o3_opreg(car, 0x40, (uint8_t)tl);
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

/* ── Expressive note state: velocity, sustain, octave ───────────────── */
#define MAX_VOICES 18
static int key_to_chan[MAX_VOICES];   /* key index -> OPL3 channel, -1 = off */
static int chan_used[MAX_VOICES];
static int chan_sustained[MAX_VOICES];/* key released but pedal holds the voice */

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
        }
    }
}

static void note_off_key(int key) {
    if (key < 0 || key >= MAX_VOICES) return;
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
    if (key < 0 || key >= MAX_VOICES || !audio_on) return;
    if (key_to_chan[key] >= 0) return;   /* same key already sounding */
    int ch;
    for (ch = 0; ch < MAX_VOICES; ch++) if (!chan_used[ch]) break;
    if (ch >= MAX_VOICES) {
        /* All voices busy: steal the oldest sustained voice, never drop a
         * new note because a held pedal blocked every channel. */
        for (ch = 0; ch < MAX_VOICES; ch++) if (chan_sustained[ch]) break;
        if (ch >= MAX_VOICES) return;
        o3_note(ch, 0, 0);
        chan_sustained[ch] = 0;
    }
    chan_used[ch] = 1;
    key_to_chan[key] = ch;
    o3_instrument(ch, vel);
    o3_note(ch, clamp_midi(midi + 12 * octave), 1);
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
    nk_sys_kbd_raw(1);
    nk_build_palette(pal768);
    nk_sys_palette(pal768);
    nk_sys_fb_info(&fw, &fh, &fp);

    audio_on = sys_pcm_open(1) == 1 ? 1 : 0;
    OPL3_Reset(&o3, RATE);
    int i;
    for (i = 0; i < MAX_VOICES; i++) {
        key_to_chan[i] = -1;
        chan_used[i] = 0;
        chan_sustained[i] = 0;
    }
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

    int origin[2] = {0, 0};
    int quit = 0;
    int last_down = 0;
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
                struct nk_color col = keys[k].black
                    ? nk_rgb(20, 20, 20)
                    : (k % 7 == 0 || k % 7 == 3 ? nk_rgb(235, 235, 235)
                                                : nk_rgb(245, 245, 245));
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
            char head[64];
            snprintf(head, sizeof(head), "OPL3 FM piano -> SB16  oct%+d  vol%d",
                     octave, volume);
            nk_draw_text(canvas,
                nk_rect(8, 10, (float)NK_W - 16, 24), head, (int)strlen(head),
                &font, audio_on ? nk_rgb(230, 230, 230) : nk_rgb(200, 90, 90),
                nk_rgb(0, 0, 0));
        }
        nk_end(&ctx);

        /* Note on/off and control presses from the mouse. */
        int hit = hit_key((int)mx, (int)my);
        if (down && !last_down) {
            if (hit >= 0) {
                note_on_key(hit, keys[hit].midi, hit_velocity(hit, (int)my));
            } else {
                int c;
                for (c = 0; c < NCTRLS; c++) if (ctrl_hit(c, (int)mx, (int)my)) { ctrl_press(c); break; }
            }
        } else if (!down && last_down) {
            if (hit >= 0) note_off_key(hit);   /* sustain defers the release */
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
            if (elapsed > MAX_AUDIO_MS) elapsed = MAX_AUDIO_MS;
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

/* ── Headless selftest (BDD hook) ───────────────────────────────────── */
static int run_selftest(void) {
    int i;
    audio_on = 1;
    OPL3_Reset(&o3, RATE);
    for (i = 0; i < MAX_VOICES; i++) {
        key_to_chan[i] = -1;
        chan_used[i] = 0;
        chan_sustained[i] = 0;
    }
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
    note_on_key(0, 48, 80);
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

    /* Audio pacing: one PCM buffer must span a full SB16 buffer duration and
     * a whole ring must be able to absorb a MAX_AUDIO_MS frame, otherwise a
     * slow frame either under-renders (starving the ring into a buzz) or
     * over-renders (silently dropping audio). */
    {
        long buf_ms = (long)PCM_BUF * 1000 / (long)RATE;
        long ring_ms = buf_ms * 7;
        if (MAX_AUDIO_MS <= buf_ms || MAX_AUDIO_MS > ring_ms) {
            printf("piano: pacing constants fail (max=%d buf=%ld ring=%ld)\n",
                   MAX_AUDIO_MS, buf_ms, ring_ms);
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
