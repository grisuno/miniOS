/**
 * @file platform_minios.c
 * @brief MiniOS platform layer for GameBoy Recompiled projects
 *
 * Game-agnostic: works with any gb-recompiled generated project, no
 * per-game patches needed. Replaces platform_sdl.cpp using MiniOS
 * syscalls:
 *   SYS_TIME        - millisecond timing
 *   SYS_KBD         - PS/2 keyboard input
 *   SYS_NK_FRAME    - composite 800x360 backbuffer onto desktop
 *   SYS_PALETTE     - VGA palette (3-3-2 RGB ramp, pushed once)
 *   SYS_VGA_MODE    - switch to graphics mode
 *   SYS_KBD_RAW     - raw keyboard mode
 *   SYS_PCSPK_TONE  - PC speaker square wave
 *   SYS_GFX_SET_TITLE - window title
 *
 * Video: GB screen (160x144) at exact 2x (320x288) centered in the
 * 800x360 NK backbuffer. The DOOM buffer (320x200) cannot fit 2x
 * (320x288), so the NK buffer is used instead.
 *
 * Audio (DOOM-style: sparse syscalls from poll points, no threads):
 * the runtime mixes 44100 Hz stereo PCM and calls on_audio_sample per
 * sample; a syscall per sample (44k/sec) would die under emulation, so
 * the callback only accumulates zero crossings + energy (a handful of
 * integer ops, no syscalls). Once per rendered frame the APU registers
 * are sampled for per-channel note frequencies (squares + wave, like
 * DOOM decodes MUS voices; noise is dropped like DOOM drops
 * percussion) and played as bass pedal + melody arpeggio with DOOM-like
 * busy-wait slots. The PCM energy gates everything, so envelopes,
 * fades and silence behave correctly and a decayed-but-on channel can
 * never drone forever. If the mix sounds but no register voice is
 * audible (noise SFX, sweep zaps), the raw mix estimate is played.
 *
 * Debug: heartbeat to stderr is OFF unless the game is started with
 * --debug. Detected via a constructor scanning _dl_argv (static
 * glibc), so generated main.c files need no patches.
 */

#include "gbrt.h"
#include "ppu.h"
#include "platform_sdl.h"
#include "audio.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* MiniOS ABI constants (MINIOS_DIR/progs on the include path) */
#include "minios_abi.h"

/* ============================================================================
 * MiniOS syscalls
 * ========================================================================== */

static long sys_time_ms(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_TIME), "D"(0) : "rcx","r11","memory");
    return ret;
}

static long sys_kbd(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_KBD), "D"(0) : "rcx","r11","memory");
    return ret;
}

static long sys_nk_frame(int *origin) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_NK_FRAME), "D"(origin) : "rcx","r11","memory");
    return ret;
}

static long sys_mouse(int *xybw) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_MOUSE), "D"(xybw) : "rcx","r11","memory");
    return ret;
}

static long sys_vga_mode(int on) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_VGA_MODE), "D"((long)on) : "rcx","r11","memory");
    return ret;
}

static long sys_kbd_raw(int on) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_KBD_RAW), "D"((long)on) : "rcx","r11","memory");
    return ret;
}

static long sys_palette(const unsigned char *pal) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_PALETTE), "D"(pal) : "rcx","r11","memory");
    return ret;
}

static long sys_gfx_title(const char *t) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_GFX_SET_TITLE), "D"(t) : "rcx","r11","memory");
    return ret;
}

static long sys_tone(unsigned f) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_PCSPK_TONE), "D"((long)f) : "rcx","r11","memory");
    return ret;
}

/* ============================================================================
 * Framebuffer: 800x360 NK backbuffer, GB at exact 2x centered
 * ========================================================================== */

#define FB_ADDR  ((volatile uint8_t *)MINIOS_NK_BACKBUF_ADDR)
#define FB_W     MINIOS_NK_W   /* 800 */
#define FB_H     MINIOS_NK_H   /* 360 */

#define GB_SCALE  2
#define GB_DST_W  (GB_SCREEN_WIDTH * GB_SCALE)    /* 320 */
#define GB_DST_H  (GB_SCREEN_HEIGHT * GB_SCALE)   /* 288 */
#define GB_DST_X0 ((FB_W - GB_DST_W) / 2)         /* 240 */
#define GB_DST_Y0 ((FB_H - GB_DST_H) / 2)         /* 36 */

/* Joypad state - active low, matches GB convention */
uint8_t g_joypad_buttons = 0xFF;
uint8_t g_joypad_dpad = 0xFF;

/* Registered emulation context (set by gb_platform_register_context) */
static GBContext *g_ctx = NULL;

/* ============================================================================
 * Debug heartbeat (OFF unless --debug)
 * ========================================================================== */

static unsigned g_dbg_render = 0;
static unsigned g_dbg_present = 0;
static unsigned g_dbg_lcd_off = 0;
static unsigned g_dbg_poll = 0;
static unsigned g_dbg_vsync = 0;

/* Serial prints cost real frame rate under emulation: default OFF. */
static bool g_minios_debug = false;

void gb_platform_set_debug(bool enabled) {
    g_minios_debug = enabled;
}

/* NOTE: --debug used to be auto-detected here by scanning argv through
 * the static-glibc loader vector (_dl_argv) in a constructor. That
 * crashed at startup: this toolchain's loader internals don't expose a
 * usable _dl_argv (it bound to unrelated storage and strcmp faulted).
 * DO NOT reintroduce argv sniffing here. --debug arrives through
 * gb_platform_set_debug(), wired by the --debug flag that
 * main-minios.patch adds to generated main.c files (auto-applied by
 * Makefile.minios, marker-gated, SDL builds untouched). */

static void dbg_heartbeat(void) {
    unsigned total = g_dbg_render + g_dbg_present + g_dbg_lcd_off;
    if (!g_minios_debug || total % 3600 != 0) {
        return;
    }
    fprintf(stderr,
            "[MINIOS-DBG] render=%u present=%u lcd_off=%u poll=%u vsync=%u "
            "joypad dpad=%02x buttons=%02x\n",
            g_dbg_render, g_dbg_present, g_dbg_lcd_off,
            g_dbg_poll, g_dbg_vsync,
            g_joypad_dpad, g_joypad_buttons);
    fflush(stderr);
}

/* ============================================================================
 * PC speaker audio (DOOM-style: sparse syscalls from poll points)
 *
 * Per rendered frame, live voice frequencies come from gb_audio_voice()
 * (runtime accessor over internal channel state: enabled, DAC, LIVE
 * envelope volume, master switch -- a decayed-but-on channel can never
 * drone) and play as bass pedal + melody arpeggio with DOOM-like slots.
 * The 44100 Hz on_audio_sample callback only accumulates zero crossings
 * + energy (a handful of integer ops, no syscalls); its gate keeps
 * envelopes, fades and silence honest, and its raw mix estimate covers
 * passages with no tonal voice (noise SFX, sweep zaps). Noise-channel
 * drums are dropped, exactly like DOOM drops the percussion channel.
 * A syscall per sample (44k/sec) would die under emulation; here it is
 * a handful per frame, max.
 * ========================================================================== */

#define MINIOS_AUDIO_RATE       44100u
#define MINIOS_AUDIO_SILENCE_E  256u    /* mean-abs below this = silent */
#define MINIOS_AUDIO_MIN_HZ     40u
#define MINIOS_AUDIO_MAX_HZ     12000u
#define MINIOS_ARP_BASS_MS      6
#define MINIOS_ARP_MEL_MS       5

/* --- Mix statistics: filled by the per-sample callback, no syscalls --- */

static uint64_t g_audio_zc = 0;
static uint64_t g_audio_n = 0;
static uint64_t g_audio_energy = 0;
static int g_audio_prev_sign = 0;
static bool g_audio_have_prev = false;

static void minios_audio_sample(GBContext *ctx, int16_t left, int16_t right) {
    (void)ctx;
    int32_t mono = ((int32_t)left >> 1) + ((int32_t)right >> 1);
    int sign = (mono > 0) - (mono < 0);
    if (g_audio_have_prev && sign != 0 && g_audio_prev_sign != 0 &&
        sign != g_audio_prev_sign) {
        g_audio_zc++;
    }
    if (sign != 0) {
        g_audio_prev_sign = sign;
        g_audio_have_prev = true;
    }
    g_audio_energy += (uint64_t)(mono < 0 ? -mono : mono);
    g_audio_n++;
}

/* --- Per-channel note frequencies, live from the APU ---
 *
 * Uses gb_audio_voice() (runtime accessor over the internal channel
 * state: enabled flag, DAC, LIVE envelope volume, master switch), NOT
 * the raw io[] mirror: io[0x26] only holds last-written values, its
 * channel bits are never set there (the computed NR52 value exists
 * only on the gb_audio_read path), so register snooping would gate
 * every voice off and fall back to mush. Envelope volume also means
 * a decayed-but-on channel can never drone. */

typedef struct {
    unsigned freq;
    bool audible;
} gb_voice_t;

static bool gb_voice_in_range(unsigned f) {
    return f >= MINIOS_AUDIO_MIN_HZ && f <= MINIOS_AUDIO_MAX_HZ;
}

static void sample_apu_voices(gb_voice_t *v) {
    v[0].freq = v[1].freq = v[2].freq = 0;
    v[0].audible = v[1].audible = v[2].audible = false;
    if (!g_ctx) {
        return;
    }
    /* CH4 noise: dropped, like DOOM drops the percussion channel */
    for (int ch = 0; ch < 3; ch++) {
        unsigned f = 0;
        if (gb_audio_voice(g_ctx, ch, &f) && gb_voice_in_range(f)) {
            v[ch].freq = f;
            v[ch].audible = true;
        }
    }
}

/* --- DOOM-style player: bass pedal + melody arpeggio --- */

static unsigned g_arp_index = 0;

static void hold_tone(unsigned freq, unsigned ms) {
    sys_tone(freq);
    unsigned long until = (unsigned long)sys_time_ms() + ms;
    while ((unsigned long)sys_time_ms() < until) {
        __asm__ volatile("pause");
    }
}

static void minios_audio_play(const gb_voice_t *v, bool pcm_audible,
                              unsigned zc_freq) {
    if (!pcm_audible) {
        sys_tone(0);
        return;
    }
    bool m1 = v[0].audible, m2 = v[1].audible, bass = v[2].audible;
    if (!m1 && !m2 && !bass) {
        /* Mix sounds but no tonal voice (noise SFX, out-of-range sweep):
         * fall back to the raw mix estimate. */
        if (zc_freq >= MINIOS_AUDIO_MIN_HZ && zc_freq <= MINIOS_AUDIO_MAX_HZ) {
            hold_tone(zc_freq, 8);
        } else {
            sys_tone(0);
        }
        return;
    }
    unsigned mel[2];
    int nmel = 0;
    if (m1) {
        mel[nmel++] = v[0].freq;
    }
    if (m2) {
        mel[nmel++] = v[1].freq;
    }
    if (bass) {
        hold_tone(v[2].freq, MINIOS_ARP_BASS_MS);
    }
    if (nmel > 0) {
        hold_tone(mel[g_arp_index % (unsigned)nmel], MINIOS_ARP_MEL_MS);
        g_arp_index++;
    }
}

/* Called once per rendered frame: a handful of syscalls, max. */
static void minios_audio_frame(void) {
    uint64_t n = g_audio_n, e = g_audio_energy, zc = g_audio_zc;
    g_audio_zc = 0;
    g_audio_n = 0;
    g_audio_energy = 0;
    bool pcm_audible = (n > 0) && (e / n >= MINIOS_AUDIO_SILENCE_E);
    unsigned zc_freq = (n > 0) ? (unsigned)((zc * MINIOS_AUDIO_RATE) / (2u * n)) : 0;
    gb_voice_t v[3];
    sample_apu_voices(v);
    minios_audio_play(v, pcm_audible, zc_freq);
}

/* ============================================================================
 * PS/2 Set 1 scancode -> GB joypad mapping
 *
 *   Arrow keys = D-pad
 *   Z = A, X = B
 *   Enter = Start, Backspace = Select
 * ========================================================================== */

static uint8_t g_key_state[128]; /* pressed/released per scancode */

static void rebuild_joypad(void) {
    g_joypad_dpad = 0xFF;
    g_joypad_buttons = 0xFF;
    if (g_key_state[0x48]) g_joypad_dpad &= ~0x04;  /* Up */
    if (g_key_state[0x50]) g_joypad_dpad &= ~0x08;  /* Down */
    if (g_key_state[0x4B]) g_joypad_dpad &= ~0x02;  /* Left */
    if (g_key_state[0x4D]) g_joypad_dpad &= ~0x01;  /* Right */
    if (g_key_state[0x2C]) g_joypad_buttons &= ~0x01;  /* Z = A */
    if (g_key_state[0x2D]) g_joypad_buttons &= ~0x02;  /* X = B */
    if (g_key_state[0x1C]) g_joypad_buttons &= ~0x08;  /* Enter = Start */
    if (g_key_state[0x0E]) g_joypad_buttons &= ~0x04;  /* Backspace = Select */
}

static void poll_keyboard(void) {
    for (;;) {
        long sc = sys_kbd();
        if (sc < 0) {
            break;
        }
        unsigned char raw = (unsigned char)sc;

        if (raw == 0xE0) {
            /* Extended prefix: next byte is the actual scancode */
            long sc2 = sys_kbd();
            if (sc2 < 0) {
                break;
            }
            unsigned char make = ((unsigned char)sc2) & 0x7F;
            int pressed = !(((unsigned char)sc2) & 0x80);
            if (make == 0x48 || make == 0x50 ||
                make == 0x4B || make == 0x4D) {
                g_key_state[make] = pressed ? 1 : 0;
                rebuild_joypad();
            }
            continue;
        }

        if (raw & 0x80) {
            g_key_state[raw & 0x7F] = 0;
        } else {
            g_key_state[raw] = 1;
        }
        rebuild_joypad();
    }
}

/* ============================================================================
 * Framebuffer upload: 3-3-2 RGB, exact 2x
 * ========================================================================== */

/* 3-3-2 RGB palette ramp, pushed ONCE at init (not per frame).
 * Pixel index = (R & 0xE0) | ((G & 0xE0) >> 3) | ((B & 0xC0) >> 6). */
static void push_332_palette(void) {
    uint8_t dac[768];
    for (int i = 0; i < 256; i++) {
        uint8_t r = (uint8_t)(i & 0xE0);
        uint8_t g = (uint8_t)((i & 0x1C) << 3);
        uint8_t b = (uint8_t)((i & 0x03) << 6);
        dac[i * 3 + 0] = (uint8_t)(r | (r >> 3) | (r >> 6));
        dac[i * 3 + 1] = (uint8_t)(g | (g >> 3) | (g >> 6));
        dac[i * 3 + 2] = (uint8_t)(b | (b >> 2) | (b >> 4) | (b >> 6));
    }
    sys_palette(dac);
}

/* 8x8 bitmap font (public-domain font8x8, ASCII 32..127; same source as
 * the one in progs/nuklear/nuklear_minios.c, copied so this port does not
 * depend on the Nuklear checkout). */
static const uint8_t menu_font8x8[96][8] = {
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},
    {0x18,0x18,0x18,0x18,0x18,0x00,0x18,0x00},
    {0x6C,0x6C,0x00,0x00,0x00,0x00,0x00,0x00},
    {0x6C,0x6C,0xFE,0x6C,0xFE,0x6C,0x6C,0x00},
    {0x18,0x3E,0x60,0x3C,0x06,0x7C,0x18,0x00},
    {0xC2,0xC6,0x0C,0x18,0x30,0x66,0xC6,0x00},
    {0x38,0x6C,0x38,0x76,0xDC,0xCC,0x76,0x00},
    {0x18,0x18,0x30,0x00,0x00,0x00,0x00,0x00},
    {0x0C,0x18,0x30,0x30,0x30,0x18,0x0C,0x00},
    {0x30,0x18,0x0C,0x0C,0x0C,0x18,0x30,0x00},
    {0x00,0x66,0x3C,0xFF,0x3C,0x66,0x00,0x00},
    {0x00,0x18,0x18,0x7E,0x18,0x18,0x00,0x00},
    {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x30},
    {0x00,0x00,0x00,0x7E,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00},
    {0x02,0x06,0x0C,0x18,0x30,0x60,0x40,0x00},
    {0x7C,0xC6,0xCE,0xDE,0xF6,0xE6,0x7C,0x00},
    {0x18,0x38,0x78,0x18,0x18,0x18,0x7E,0x00},
    {0x7C,0xC6,0x06,0x1C,0x30,0x66,0xFE,0x00},
    {0x7C,0xC6,0x06,0x3C,0x06,0xC6,0x7C,0x00},
    {0x1C,0x3C,0x6C,0xCC,0xFE,0x0C,0x1E,0x00},
    {0xFE,0xC0,0xFC,0x06,0x06,0xC6,0x7C,0x00},
    {0x38,0x60,0xC0,0xFC,0xC6,0xC6,0x7C,0x00},
    {0xFE,0xC6,0x0C,0x18,0x30,0x30,0x30,0x00},
    {0x7C,0xC6,0xC6,0x7C,0xC6,0xC6,0x7C,0x00},
    {0x7C,0xC6,0xC6,0x7E,0x06,0x0C,0x78,0x00},
    {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x00},
    {0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x30},
    {0x0C,0x18,0x30,0x60,0x30,0x18,0x0C,0x00},
    {0x00,0x00,0x7E,0x00,0x7E,0x00,0x00,0x00},
    {0x60,0x30,0x18,0x0C,0x18,0x30,0x60,0x00},
    {0x7C,0xC6,0x0C,0x18,0x18,0x00,0x18,0x00},
    {0x7C,0xC6,0xDE,0xDE,0xDE,0xC0,0x78,0x00},
    {0x38,0x6C,0xC6,0xC6,0xFE,0xC6,0xC6,0x00},
    {0xFC,0x66,0x66,0x7C,0x66,0x66,0xFC,0x00},
    {0x3C,0x66,0xC0,0xC0,0xC0,0x66,0x3C,0x00},
    {0xF8,0x6C,0x66,0x66,0x66,0x6C,0xF8,0x00},
    {0xFE,0x62,0x68,0x78,0x68,0x62,0xFE,0x00},
    {0xFE,0x62,0x68,0x78,0x68,0x60,0xF0,0x00},
    {0x3C,0x66,0xC0,0xC0,0xC6,0x66,0x3E,0x00},
    {0xC6,0xC6,0xC6,0xFE,0xC6,0xC6,0xC6,0x00},
    {0x3C,0x18,0x18,0x18,0x18,0x18,0x3C,0x00},
    {0x1E,0x0C,0x0C,0x0C,0xCC,0xCC,0x78,0x00},
    {0xE6,0x66,0x6C,0x78,0x6C,0x66,0xE6,0x00},
    {0xF0,0x60,0x60,0x60,0x62,0x66,0xFE,0x00},
    {0xC6,0xEE,0xFE,0xFE,0xD6,0xC6,0xC6,0x00},
    {0xC6,0xE6,0xF6,0xDE,0xCE,0xC6,0xC6,0x00},
    {0x7C,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00},
    {0xFC,0x66,0x66,0x7C,0x60,0x60,0xF0,0x00},
    {0x7C,0xC6,0xC6,0xC6,0xD6,0xDE,0x7C,0x06},
    {0xFC,0x66,0x66,0x7C,0x6C,0x66,0xE6,0x00},
    {0x7C,0xC6,0xE0,0x7C,0x0E,0xC6,0x7C,0x00},
    {0x7E,0x7E,0x5A,0x18,0x18,0x18,0x3C,0x00},
    {0xC6,0xC6,0xC6,0xC6,0xC6,0xC6,0x7C,0x00},
    {0xC6,0xC6,0xC6,0xC6,0x6C,0x38,0x10,0x00},
    {0xC6,0xC6,0xC6,0xD6,0xFE,0xEE,0xC6,0x00},
    {0xC6,0xC6,0x6C,0x38,0x6C,0xC6,0xC6,0x00},
    {0x66,0x66,0x66,0x3C,0x18,0x18,0x3C,0x00},
    {0xFE,0xC6,0x8C,0x18,0x32,0x66,0xFE,0x00},
    {0x3C,0x30,0x30,0x30,0x30,0x30,0x3C,0x00},
    {0xC0,0x60,0x30,0x18,0x0C,0x06,0x02,0x00},
    {0x3C,0x0C,0x0C,0x0C,0x0C,0x0C,0x3C,0x00},
    {0x10,0x38,0x6C,0xC6,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF},
    {0x30,0x18,0x0C,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x00,0x78,0x0C,0x7C,0xCC,0x76,0x00},
    {0xE0,0x60,0x7C,0x66,0x66,0x66,0xDC,0x00},
    {0x00,0x00,0x7C,0xC6,0xC0,0xC6,0x7C,0x00},
    {0x1C,0x0C,0x7C,0xCC,0xCC,0xCC,0x76,0x00},
    {0x00,0x00,0x7C,0xC6,0xFE,0xC0,0x7C,0x00},
    {0x1C,0x36,0x30,0x7C,0x30,0x30,0x78,0x00},
    {0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0x78},
    {0xE0,0x60,0x6C,0x76,0x66,0x66,0xE6,0x00},
    {0x18,0x00,0x38,0x18,0x18,0x18,0x3C,0x00},
    {0x06,0x00,0x06,0x06,0x06,0x66,0x66,0x3C},
    {0xE0,0x60,0x66,0x6C,0x78,0x6C,0xE6,0x00},
    {0x38,0x18,0x18,0x18,0x18,0x18,0x3C,0x00},
    {0x00,0x00,0xEC,0xFE,0xD6,0xD6,0xD6,0x00},
    {0x00,0x00,0xDC,0x66,0x66,0x66,0x66,0x00},
    {0x00,0x00,0x7C,0xC6,0xC6,0xC6,0x7C,0x00},
    {0x00,0x00,0xDC,0x66,0x66,0x7C,0x60,0xF0},
    {0x00,0x00,0x76,0xCC,0xCC,0x7C,0x0C,0x1E},
    {0x00,0x00,0xDC,0x76,0x60,0x60,0xF0,0x00},
    {0x00,0x00,0x7E,0xC0,0x7C,0x06,0xFC,0x00},
    {0x30,0x30,0x7C,0x30,0x30,0x36,0x1C,0x00},
    {0x00,0x00,0xCC,0xCC,0xCC,0xCC,0x76,0x00},
    {0x00,0x00,0xC6,0xC6,0xC6,0x6C,0x38,0x00},
    {0x00,0x00,0xC6,0xD6,0xD6,0xFE,0x6C,0x00},
    {0x00,0x00,0xC6,0x6C,0x38,0x6C,0xC6,0x00},
    {0x00,0x00,0xC6,0xC6,0xCE,0x76,0x06,0xFC},
    {0x00,0x00,0xFC,0x98,0x30,0x64,0xFC,0x00},
    {0x0E,0x18,0x18,0x70,0x18,0x18,0x0E,0x00},
    {0x18,0x18,0x18,0x00,0x18,0x18,0x18,0x00},
    {0x70,0x18,0x18,0x0E,0x18,0x18,0x70,0x00},
    {0x76,0xDC,0x00,0x00,0x00,0x00,0x00,0x00},
    {0x00,0x10,0x38,0x6C,0xC6,0xC6,0xFE,0x00}
};

/* ============================================================================
 * FILE menu (no Nuklear on purpose)
 *
 * A 16 px menu bar lives in the top margin the 2x GB image never touches
 * (it starts at GB_DST_Y0 = 36). Clicking FILE (or pressing Esc) drops a
 * 3-item menu: Save State, Load State, Quit. Drawing is a few filled rects
 * plus 8x8 glyphs straight into the backbuffer: no widget library, no atlas
 * upload, no measurable frame cost. Nuklear would drag its whole
 * immediate-mode renderer into this binary for three buttons while the game
 * is already CPU-bound under QEMU-TCG. The game keeps running behind the
 * open menu; save/load run at poll points between emulation slices, so they
 * can never race the CPU.
 * ========================================================================== */

#define MENU_BAR_H   16
#define MENU_FILE_X0 4
#define MENU_FILE_X1 56
#define MENU_DROP_X0 4
#define MENU_DROP_W  176
#define MENU_ITEM_H  14
#define MENU_NITEMS  3

/* 3-3-2 palette indices (the pushed 332 ramp is live while we draw). */
#define MENU_BG      0x09
#define MENU_FG      0xFF
#define MENU_HOVER   0x62
#define MENU_OSD_BG  0x00

/* Forward declarations for helpers defined further down. */
static void minios_state_path(char *out, size_t n, const GBContext *ctx);
static void minios_legacy_state_path(char *out, size_t n, const GBContext *ctx);

static bool g_menu_open = false;
static int g_menu_hover = -1;
static int g_win_ox = 0, g_win_oy = 0;
static int g_prev_lbtn = 0;
static bool g_want_quit = false;
static unsigned g_osd_until = 0;
static char g_osd[56] = {0};

static void menu_fill(int x0, int y0, int w, int h, uint8_t idx) {
    volatile uint8_t *dst = FB_ADDR;
    if (x0 < 0) { w += x0; x0 = 0; }
    if (y0 < 0) { h += y0; y0 = 0; }
    if (x0 + w > FB_W) w = FB_W - x0;
    if (y0 + h > FB_H) h = FB_H - y0;
    if (w <= 0 || h <= 0) return;
    for (int y = 0; y < h; y++) {
        volatile uint8_t *row = dst + (y0 + y) * FB_W + x0;
        for (int x = 0; x < w; x++) row[x] = idx;
    }
}

static void menu_text(int x, int y, const char *s, uint8_t fg) {
    volatile uint8_t *dst = FB_ADDR;
    if (y < 0 || y + 8 > FB_H) return;
    while (*s) {
        unsigned char c = (unsigned char)*s++;
        if (c < 32 || c > 127) c = '?';
        if (x + 8 > FB_W) break;
        const uint8_t *g = menu_font8x8[c - 32];
        for (int r = 0; r < 8; r++) {
            uint8_t bits = g[r];
            if (!bits) continue;
            volatile uint8_t *row = dst + (y + r) * FB_W + x;
            for (int col = 0; col < 8; col++)
                if (bits & (0x80 >> col)) row[col] = fg;
        }
        x += 8;
    }
}

static void menu_osd(const char *s) {
    strncpy(g_osd, s, sizeof(g_osd) - 1);
    g_osd[sizeof(g_osd) - 1] = 0;
    g_osd_until = (uint32_t)sys_time_ms() + 3000u;
}

static void menu_draw(void) {
    uint32_t now = (uint32_t)sys_time_ms();
    menu_fill(0, 0, FB_W, MENU_BAR_H, MENU_BG);
    menu_text(MENU_FILE_X0 + 4, 4, "FILE", MENU_FG);
    if (g_menu_open) {
        static const char *items[MENU_NITEMS] = {
            "Save State", "Load State", "Quit"
        };
        for (int i = 0; i < MENU_NITEMS; i++) {
            int iy = MENU_BAR_H + i * MENU_ITEM_H;
            menu_fill(MENU_DROP_X0, iy, MENU_DROP_W, MENU_ITEM_H,
                      i == g_menu_hover ? MENU_HOVER : MENU_BG);
            menu_text(MENU_DROP_X0 + 6, iy + 3, items[i], MENU_FG);
        }
        menu_fill(MENU_DROP_X0, MENU_BAR_H + MENU_NITEMS * MENU_ITEM_H,
                  MENU_DROP_W, 1, MENU_FG);
    }
    if (g_osd[0]) {
        if (now < g_osd_until) {
            size_t w = strlen(g_osd) * 8 + 12;
            if (w > (size_t)FB_W - 16) w = (size_t)FB_W - 16;
            menu_fill(8, FB_H - 16, (int)w, 12, MENU_OSD_BG);
            menu_text(14, FB_H - 14, g_osd, MENU_FG);
        } else {
            g_osd[0] = 0;
        }
    }
}

static int menu_item_at(int lx, int ly) {
    if (!g_menu_open) return -1;
    if (lx < MENU_DROP_X0 || lx >= MENU_DROP_X0 + MENU_DROP_W) return -1;
    int i = (ly - MENU_BAR_H) / MENU_ITEM_H;
    return (i >= 0 && i < MENU_NITEMS) ? i : -1;
}

static void menu_do_save(void) {
    g_menu_open = false;
    if (!g_ctx) return;
    char path[64];
    minios_state_path(path, sizeof(path), g_ctx);
    gb_context_save_ram(g_ctx);
    if (gb_context_save_state_file(g_ctx, path)) {
        menu_osd("State saved");
        fprintf(stderr, "[MINIOS] State saved to %s (persists on MiniFS)\n", path);
    } else {
        menu_osd("Save FAILED");
        fprintf(stderr, "[MINIOS] State save FAILED\n");
    }
    fflush(stderr);
}

static void menu_do_load(void) {
    g_menu_open = false;
    if (!g_ctx) return;
    char path[64], legacy[64];
    minios_state_path(path, sizeof(path), g_ctx);
    minios_legacy_state_path(legacy, sizeof(legacy), g_ctx);
    if (gb_context_load_state_file(g_ctx, path)) {
        menu_osd("State loaded");
        fprintf(stderr, "[MINIOS] State loaded from %s\n", path);
    } else if (gb_context_load_state_file(g_ctx, legacy)) {
        menu_osd("State loaded");
        fprintf(stderr, "[MINIOS] State loaded from %s (legacy ramdisk path)\n", legacy);
    } else {
        menu_osd("Load FAILED");
        fprintf(stderr, "[MINIOS] State load FAILED (no checkpoint yet?)\n");
    }
    fflush(stderr);
}

/* PS/2 Set 1 Esc = 0x01 toggles the menu; the mouse drives it otherwise. */
static void poll_menu(void) {
    static uint8_t prev_esc = 0;
    uint8_t esc = g_key_state[0x01];
    if (esc && !prev_esc) g_menu_open = !g_menu_open;
    prev_esc = esc;
    int m[4];
    if (sys_mouse(m) != 0) return;
    int lx = m[0] - g_win_ox;
    int ly = m[1] - g_win_oy;
    int lbtn = m[2] & 1;
    g_menu_hover = menu_item_at(lx, ly);
    if (lbtn && !g_prev_lbtn) {
        if (lx >= MENU_FILE_X0 && lx < MENU_FILE_X1 && ly >= 0 && ly < MENU_BAR_H) {
            g_menu_open = !g_menu_open;
        } else if (g_menu_open) {
            int it = menu_item_at(lx, ly);
            if (it == 0) menu_do_save();
            else if (it == 1) menu_do_load();
            else if (it == 2) { g_menu_open = false; g_want_quit = true; }
            else g_menu_open = false;
        }
    }
    g_prev_lbtn = lbtn;
}

/* Scale and upload frame to backbuffer (nearest neighbor, exact 2x). */
static void upload_frame(const uint32_t *framebuffer) {
    volatile uint8_t *dst = FB_ADDR;

    for (int y = 0; y < GB_DST_H; y++) {
        int src_y = y >> 1;
        const uint32_t *src_row = framebuffer + src_y * GB_SCREEN_WIDTH;
        volatile uint8_t *dst_row = dst + (GB_DST_Y0 + y) * FB_W + GB_DST_X0;

        for (int x = 0; x < GB_DST_W; x++) {
            uint32_t pixel = src_row[x >> 1];
            uint8_t r = (uint8_t)((pixel >> 16) & 0xFF);
            uint8_t g = (uint8_t)((pixel >> 8) & 0xFF);
            uint8_t b = (uint8_t)(pixel & 0xFF);
            dst_row[x] = (uint8_t)((r & 0xE0) | ((g & 0xE0) >> 3) |
                                   ((b & 0xC0) >> 6));
        }
    }

    /* Menu bar + dropdown + OSD live in the margins the 2x image never
     * touches; then present and capture the window content origin so the
     * next poll maps mouse clicks onto the backbuffer. */
    menu_draw();
    {
        int origin[2] = {0, 0};
        sys_nk_frame(origin);
        g_win_ox = origin[0];
        g_win_oy = origin[1];
    }
}

/* ============================================================================
 * State
 * ========================================================================== */

static int g_scale = 2;
static uint32_t g_last_frame_time = 0;
static int g_speed_percent = 100;
static int g_benchmark_mode = 0;
static GBPlatformExitAction g_exit_action = GB_PLATFORM_EXIT_QUIT;
static uint64_t g_present_count = 0;
static uint32_t g_last_guest_framebuffer[GB_FRAMEBUFFER_SIZE];

/* Timing */
static double g_timing_render_total = 0.0;
static uint32_t g_timing_frame_count = 0;
static GBPlatformTimingInfo g_last_timing = {0};

/* Persistence (stub for MiniOS - no filesystem for saves yet) */
static char g_persistence_dir[256] = {0};

/* Input script */
static int g_input_script_active = 0;

/* Autoquit for headless testing */
static int g_autoquit_frames = 0;
static int g_autoquit_count = 0;

/* Dump frames (stub) */
static uint32_t g_dump_frames[100];
static int g_dump_count = 0;
static uint32_t g_dump_present_frames[100];
static int g_dump_present_count = 0;
static char g_screenshot_prefix[128] = "screenshot";

/* ============================================================================
 * gb_platform_* interface implementation
 * ========================================================================== */

bool gb_platform_init(int scale) {
    g_scale = scale;
    (void)g_scale;

    sys_vga_mode(1);   /* switch kernel to graphics mode */
    sys_kbd_raw(1);    /* enable raw PS/2 keyboard */
    sys_gfx_title("Pokemon - MiniOS");

    memset(g_last_guest_framebuffer, 0, sizeof(g_last_guest_framebuffer));
    memset((void *)FB_ADDR, 0, (size_t)FB_W * FB_H);
    push_332_palette();

    g_last_frame_time = (uint32_t)sys_time_ms();
    fprintf(stderr, "[MINIOS] Platform initialized, backbuffer at %p\n",
            (void *)MINIOS_NK_BACKBUF_ADDR);
    return true;
}

/* --- Battery + RTC persistence (direct write to MiniFS) ---
 *
 * Paths use saves/: kfopen tries the ramdisk FIRST and creates there
 * when the parent directory exists on the ramdisk, so bin/ (which the
 * ramdisk ships as bin/minigcc.elf, bin/cp) would land on volatile
 * ramdisk and vanish on reboot. saves/ exists on neither the ramdisk
 * nor a fresh MiniFS, so the write falls through to MiniFS (mkdir_p +
 * create) and survives reboot/poweroff. Writes are direct (fopen w +
 * fwrite + fclose); there is no rename() on MiniOS yet, so no atomic
 * temp+rename transaction like the SDL port does. */

static void minios_persist_path(char *out, size_t n, const GBContext *ctx,
                                const char *ext) {
    const char *id = (ctx && ctx->save_id[0]) ? (const char *)ctx->save_id : "pokemon";
    snprintf(out, n, "saves/%.40s%s", id, ext);
}

/* Legacy ramdisk path (pre-MiniFS fix wrote bin/<id>.* onto volatile
 * ramdisk). Loads still probe it as a fallback so a checkpoint saved
 * in the same session before an upgrade is not invisible. */
static void minios_legacy_path(char *out, size_t n, const GBContext *ctx,
                               const char *ext) {
    const char *id = (ctx && ctx->save_id[0]) ? (const char *)ctx->save_id : "pokemon";
    snprintf(out, n, "bin/%.40s%s", id, ext);
}

static bool minios_load_helper(const char *path, void *data, size_t size,
                               GBContext *ctx) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        return false;
    }
    size_t got = fread(data, 1, size, f);
    int trailing = fgetc(f);
    fclose(f);
    if (got != size || trailing != EOF) {
        if (ctx) {
            ctx->persistence_load_failed = true;
        }
        return false;
    }
    return true;
}

static bool minios_save_helper(const char *path, const void *data, size_t size) {
    FILE *f = fopen(path, "wb");
    if (!f) {
        return false;
    }
    size_t wrote = fwrite(data, 1, size, f);
    int ok = (wrote == size) && (fflush(f) == 0);
    fclose(f);
    return ok;
}

static bool minios_load_battery_ram(GBContext *ctx, const char *rom_name,
                                     void *data, size_t size) {
    char path[64];
    (void)rom_name;
    minios_persist_path(path, sizeof(path), ctx, ".sav");
    if (minios_load_helper(path, data, size, ctx)) {
        return true;
    }
    /* Fallback: checkpoint written to volatile ramdisk by the old
     * bin/ path before the MiniFS fix (same session only). */
    ctx->persistence_load_failed = false;
    minios_legacy_path(path, sizeof(path), ctx, ".sav");
    return minios_load_helper(path, data, size, ctx);
}

static bool minios_save_battery_ram(GBContext *ctx, const char *rom_name,
                                    const void *data, size_t size) {
    char path[64];
    (void)ctx;
    (void)rom_name;
    /* save_id may be empty before first boot; fall back inside helper */
    minios_persist_path(path, sizeof(path), ctx, ".sav");
    return minios_save_helper(path, data, size);
}

static bool minios_load_rtc_data(GBContext *ctx, const char *rom_name,
                                  void *data, size_t size) {
    char path[64];
    (void)rom_name;
    minios_persist_path(path, sizeof(path), ctx, ".rtc");
    if (minios_load_helper(path, data, size, ctx)) {
        return true;
    }
    ctx->persistence_load_failed = false;
    minios_legacy_path(path, sizeof(path), ctx, ".rtc");
    return minios_load_helper(path, data, size, ctx);
}

static bool minios_save_rtc_data(GBContext *ctx, const char *rom_name,
                                 const void *data, size_t size) {
    char path[64];
    (void)ctx;
    (void)rom_name;
    minios_persist_path(path, sizeof(path), ctx, ".rtc");
    return minios_save_helper(path, data, size);
}

/* --- In-game save flushing + emulator savestates ---
 *
 * The runtime only persists battery RAM on clean exit
 * (gb_context_destroy); QEMU poweroff never takes that path, so MiniOS
 * flushes SRAM itself: every 60 s via gb_context_save_ram(), plus
 * on-demand full savestates with F5 / Ctrl+S (save) and F8 / Ctrl+L
 * (load), matching upstream's convention (F5/F8) plus the Ctrl pair.
 * All files land on persistent MiniFS (saves/<save-id>.*: .sav/.rtc
 * for battery, .state for the full savestate), so they survive reboot
 * and poweroff; the battery files auto-load on next boot, the .state
 * file resumes with F8 / Ctrl+L. Single-threaded: these run between
 * emulation slices, never concurrently with the CPU. */

static uint32_t g_last_autosave_ms = 0;
#define MINIOS_AUTOSAVE_MS 60000u

/* --- Fast-forward with SPACE (frameskip at max) ---
 *
 * While SPACE (PS/2 Set 1 0x39) is held the emulator runs as fast as
 * possible: vsync waits nothing, PC-speaker audio is silenced (its
 * DOOM-style busy-wait slots would cap the speed), and only 1 of every
 * MINIOS_FF_FRAMESKIP+1 frames is uploaded (classic frameskip 9, the
 * highest usual value). SPACE is never a joypad key, so holding it
 * cannot leak into the game. */
#define MINIOS_FF_FRAMESKIP 9u
static unsigned g_ff_counter = 0;
static bool g_ff_muted = false;
static inline bool minios_fast_forward(void) {
    return g_key_state[0x39] != 0;
}

static void minios_state_path(char *out, size_t n, const GBContext *ctx) {
    const char *id = (ctx && ctx->save_id[0]) ? (const char *)ctx->save_id : "pokemon";
    snprintf(out, n, "saves/%.40s.state", id);
}

static void minios_legacy_state_path(char *out, size_t n, const GBContext *ctx) {
    const char *id = (ctx && ctx->save_id[0]) ? (const char *)ctx->save_id : "pokemon";
    snprintf(out, n, "bin/%.40s.state", id);
}

static void minios_autosave(uint32_t now) {
    if (!g_ctx || now - g_last_autosave_ms < MINIOS_AUTOSAVE_MS) {
        return;
    }
    g_last_autosave_ms = now;
    if (gb_context_save_ram(g_ctx)) {
        fprintf(stderr, "[MINIOS] Autosaved battery/RTC\n");
        fflush(stderr);
    }
}

/* PS/2 Set 1: F5 = 0x3F, F8 = 0x42, Ctrl = 0x1D, S = 0x1F, L = 0x26,
 * SPACE = 0x39 (fast-forward, handled in vsync/render, not here). */
static void poll_hotkeys(void) {
    static uint8_t prev[128];
    bool ctrl = g_key_state[0x1D] != 0;
    bool save_edge = (g_key_state[0x3F] && !prev[0x3F]) ||
                     (g_key_state[0x1F] && !prev[0x1F] && ctrl);
    bool load_edge = (g_key_state[0x42] && !prev[0x42]) ||
                     (g_key_state[0x26] && !prev[0x26] && ctrl);
    memcpy(prev, g_key_state, sizeof(prev));
    if (!g_ctx) {
        return;
    }
    if (save_edge) {
        char path[64];
        minios_state_path(path, sizeof(path), g_ctx);
        /* Flush battery/RTC first so .sav/.rtc agree with the .state. */
        gb_context_save_ram(g_ctx);
        if (gb_context_save_state_file(g_ctx, path)) {
            fprintf(stderr, "[MINIOS] State saved to %s (persists on MiniFS)\n", path);
        } else {
            fprintf(stderr, "[MINIOS] State save FAILED\n");
        }
        fflush(stderr);
    } else if (load_edge) {
        char path[64];
        char legacy[64];
        minios_state_path(path, sizeof(path), g_ctx);
        minios_legacy_state_path(legacy, sizeof(legacy), g_ctx);
        if (gb_context_load_state_file(g_ctx, path)) {
            fprintf(stderr, "[MINIOS] State loaded from %s\n", path);
        } else if (gb_context_load_state_file(g_ctx, legacy)) {
            fprintf(stderr, "[MINIOS] State loaded from %s (legacy ramdisk path)\n", legacy);
        } else {
            fprintf(stderr, "[MINIOS] State load FAILED (no checkpoint yet?)\n");
        }
        fflush(stderr);
    }
}

void gb_platform_register_context(GBContext *ctx) {
    g_ctx = ctx;
    if (!ctx) {
        return;
    }
    /* Preserve hooks main.c may already hold (serial stdout); installing
     * the battery callback also triggers the runtime's first load. */
    GBPlatformCallbacks cbs = ctx->callbacks;
    cbs.on_audio_sample = minios_audio_sample;
    cbs.load_battery_ram = minios_load_battery_ram;
    cbs.save_battery_ram = minios_save_battery_ram;
    cbs.load_rtc_data = minios_load_rtc_data;
    cbs.save_rtc_data = minios_save_rtc_data;
    gb_set_platform_callbacks(ctx, &cbs);
}

void gb_platform_shutdown(void) {
    sys_tone(0);       /* silence the speaker */
    sys_vga_mode(0);   /* back to VGA text */
    sys_kbd_raw(0);
    g_ctx = NULL;
}

bool gb_platform_poll_events(GBContext *ctx) {
    (void)ctx;
    poll_keyboard();
    poll_hotkeys();
    poll_menu();
    if (g_want_quit) {
        /* Graceful quit from the FILE menu: flush battery, restore text
         * mode and return false; main then destroys the context (which
         * saves battery again, harmlessly) and exits to the shell. */
        g_want_quit = false;
        if (g_ctx) {
            gb_context_save_ram(g_ctx);
            fprintf(stderr, "[MINIOS] Quit from menu, battery flushed\n");
            fflush(stderr);
        }
        gb_platform_shutdown();
        return false;
    }
    g_dbg_poll++;
    return true; /* never quit via window close on MiniOS */
}

void gb_platform_render_frame(const uint32_t *framebuffer) {
    uint32_t now = (uint32_t)sys_time_ms();

    if (minios_fast_forward()) {
        /* Max-speed path: silence the speaker once, skip audio (its
         * busy-wait slots would cap the speed) and upload only 1 of
         * every MINIOS_FF_FRAMESKIP+1 frames. Counters and autosave
         * still advance so timing/quit behaviour stays sane. */
        if (!g_ff_muted) {
            sys_tone(0);
            g_ff_muted = true;
        }
        g_ff_counter++;
        if ((g_ff_counter % (MINIOS_FF_FRAMESKIP + 1u)) != 0) {
            memcpy(g_last_guest_framebuffer, framebuffer,
                   sizeof(g_last_guest_framebuffer));
            g_timing_frame_count++;
            g_present_count++;
            g_dbg_render++;
            dbg_heartbeat();
            if (g_autoquit_frames > 0 && ++g_autoquit_count >= g_autoquit_frames) {
                fprintf(stderr, "[MINIOS] Autoquit: played %d frames\n", g_autoquit_count);
                exit(0);
            }
            g_last_frame_time = now;
            minios_autosave(now);
            return;
        }
        upload_frame(framebuffer);
        minios_autosave(now);
    } else {
        g_ff_counter = 0;
        g_ff_muted = false;
        upload_frame(framebuffer);
        minios_audio_frame();
        minios_autosave(now);
    }

    memcpy(g_last_guest_framebuffer, framebuffer,
           sizeof(g_last_guest_framebuffer));

    g_timing_frame_count++;
    g_present_count++;
    g_dbg_render++;
    dbg_heartbeat();

    /* Autoquit check */
    if (g_autoquit_frames > 0 && ++g_autoquit_count >= g_autoquit_frames) {
        fprintf(stderr, "[MINIOS] Autoquit: played %d frames\n", g_autoquit_count);
        exit(0);
    }

    /* Update timing */
    uint32_t elapsed = now - g_last_frame_time;
    g_last_frame_time = now;
    g_timing_render_total += (double)elapsed;
}

void gb_platform_present_framebuffer(const uint32_t *framebuffer) {
    upload_frame(framebuffer);
    g_dbg_present++;
    dbg_heartbeat();
}

void gb_platform_render_lcd_off_frame(void) {
    volatile uint8_t *dst = FB_ADDR;
    for (int y = 0; y < GB_DST_H; y++) {
        memset((void *)(dst + (GB_DST_Y0 + y) * FB_W + GB_DST_X0), 0, GB_DST_W);
    }
    menu_draw();
    {
        int origin[2] = {0, 0};
        sys_nk_frame(origin);
        g_win_ox = origin[0];
        g_win_oy = origin[1];
    }
    g_dbg_lcd_off++;
    dbg_heartbeat();
}

void gb_platform_vsync(uint32_t frame_cycles) {
    /* Pace at ~59.7 FPS (4194304 / 70224 cycles per frame).
     * While SPACE is held there is no wait at all: max speed. */
    g_dbg_vsync++;
    if (minios_fast_forward()) {
        g_last_frame_time = (uint32_t)sys_time_ms();
        return;
    }
    (void)frame_cycles;
    uint32_t now = (uint32_t)sys_time_ms();
    uint32_t target_ms = 1000 * g_speed_percent / 5970;
    uint32_t elapsed = now - g_last_frame_time;
    if (elapsed < target_ms) {
        uint32_t wait = target_ms - elapsed;
        uint32_t wstart = (uint32_t)sys_time_ms();
        while ((uint32_t)sys_time_ms() - wstart < wait) {
            __asm__ volatile("pause");
        }
    }
}

void gb_platform_set_benchmark_mode(bool enabled) {
    g_benchmark_mode = enabled ? 1 : 0;
}

bool gb_platform_set_input_script(const char *script) {
    (void)script;
    g_input_script_active = (script && script[0]) ? 1 : 0;
    return true;
}

void gb_platform_set_input_record_file(const char *path) {
    (void)path;
    /* No input recording on MiniOS - stub */
}

bool gb_platform_set_persistence_dir(const char *path) {
    if (!path || !path[0]) {
        g_persistence_dir[0] = '\0';
        return false;
    }
    strncpy(g_persistence_dir, path, sizeof(g_persistence_dir) - 1);
    return true;
}

void gb_platform_set_dump_frames(const char *frames) {
    g_dump_count = 0;
    if (!frames || !frames[0]) {
        return;
    }
    /* Simple comma-separated parse */
    const char *p = frames;
    while (*p && g_dump_count < 100) {
        uint32_t val = 0;
        while (*p >= '0' && *p <= '9') {
            val = val * 10 + (unsigned)(*p - '0');
            p++;
        }
        g_dump_frames[g_dump_count++] = val;
        if (*p == ',') {
            p++;
        } else {
            break;
        }
    }
}

void gb_platform_set_dump_present_frames(const char *frames) {
    g_dump_present_count = 0;
    if (!frames || !frames[0]) {
        return;
    }
    const char *p = frames;
    while (*p && g_dump_present_count < 100) {
        uint32_t val = 0;
        while (*p >= '0' && *p <= '9') {
            val = val * 10 + (unsigned)(*p - '0');
            p++;
        }
        g_dump_present_frames[g_dump_present_count++] = val;
        if (*p == ',') {
            p++;
        } else {
            break;
        }
    }
}

void gb_platform_set_screenshot_prefix(const char *prefix) {
    if (prefix) {
        strncpy(g_screenshot_prefix, prefix, sizeof(g_screenshot_prefix) - 1);
    }
}

void gb_platform_get_timing_info(GBPlatformTimingInfo *out) {
    if (out) {
        *out = g_last_timing;
        g_last_timing = (GBPlatformTimingInfo){0};
    }
}

uint8_t gb_platform_get_joypad(void) {
    return g_joypad_buttons;
}

void gb_platform_set_title(const char *title) {
    if (title) {
        sys_gfx_title(title);
    }
}

bool gb_platform_get_smooth_lcd_transitions(void) {
    return true;
}

void gb_platform_set_smooth_lcd_transitions(bool enabled) {
    (void)enabled;
}

void gb_platform_set_launcher_return_enabled(bool enabled) {
    (void)enabled;
}

GBPlatformExitAction gb_platform_get_exit_action(void) {
    return g_exit_action;
}

void gb_platform_submit_port_frame(void *user, const GBPortFrame *frame) {
    (void)user;
    (void)frame;
}

/* Test-hook stubs (no-ops on MiniOS) */
bool gb_platform_test_audio_concurrency(uint32_t frames,
                                        void *out_result) {
    (void)frames;
    if (out_result) {
        memset(out_result, 0, 64);
    }
    return false;
}

void gb_platform_test_inject_persistence_fault(
    GBPersistenceTestTarget target,
    GBPersistenceTestFault fault) {
    (void)target;
    (void)fault;
}
