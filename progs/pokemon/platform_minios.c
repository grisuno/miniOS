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

static long sys_nk_frame(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_NK_FRAME), "D"(0) : "rcx","r11","memory");
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
 * PC speaker audio
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

/* Self-healing registration: main.c touches callbacks after
 * gb_platform_register_context, so (re)install if missing. */
static void minios_audio_ensure(GBContext *ctx) {
    if (ctx && !ctx->callbacks.on_audio_sample) {
        ctx->callbacks.on_audio_sample = minios_audio_sample;
    }
}

/* --- Per-channel note frequencies from APU registers --- */

typedef struct {
    unsigned freq;
    bool audible;
} gb_voice_t;

/* GB square/wave frequency: 131072 / (2048 - N), N = 11-bit register */
static unsigned gb_voice_freq(unsigned n) {
    if (n >= 2048u) {
        return 0;
    }
    return 131072u / (2048u - n);
}

static bool gb_voice_in_range(unsigned f) {
    return f >= MINIOS_AUDIO_MIN_HZ && f <= MINIOS_AUDIO_MAX_HZ;
}

static void sample_apu_voices(gb_voice_t *v) {
    v[0].freq = v[1].freq = v[2].freq = 0;
    v[0].audible = v[1].audible = v[2].audible = false;
    if (!g_ctx || !g_ctx->io) {
        return;
    }
    const uint8_t *io = g_ctx->io;
    if (!(io[0x26] & 0x80u)) {
        return; /* APU master off */
    }
    /* CH1 square+sweep: NR12 vol/env, NR13/NR14 freq, status bit 0 */
    {
        unsigned n = (((unsigned)(io[0x14] & 0x07)) << 8) | io[0x13];
        v[0].freq = gb_voice_freq(n);
        v[0].audible = (io[0x26] & 0x01u) && (io[0x12] & 0xF8u) &&
                       ((io[0x12] >> 4) != 0) && gb_voice_in_range(v[0].freq);
    }
    /* CH2 square: NR22, NR23/NR24, status bit 1 */
    {
        unsigned n = (((unsigned)(io[0x19] & 0x07)) << 8) | io[0x18];
        v[1].freq = gb_voice_freq(n);
        v[1].audible = (io[0x26] & 0x02u) && (io[0x17] & 0xF8u) &&
                       ((io[0x17] >> 4) != 0) && gb_voice_in_range(v[1].freq);
    }
    /* CH3 wave: NR30 DAC, NR32 vol code (0 = mute), NR33/NR34, bit 2 */
    {
        unsigned n = (((unsigned)(io[0x1E] & 0x07)) << 8) | io[0x1D];
        v[2].freq = gb_voice_freq(n);
        v[2].audible = (io[0x26] & 0x04u) && (io[0x1A] & 0x80u) &&
                       ((io[0x1C] & 0x60u) != 0) && gb_voice_in_range(v[2].freq);
    }
    /* CH4 noise: dropped, like DOOM drops the percussion channel */
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

    /* Present (palette was pushed once at init) */
    sys_nk_frame();
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

void gb_platform_register_context(GBContext *ctx) {
    g_ctx = ctx;
}

void gb_platform_shutdown(void) {
    sys_tone(0);       /* silence the speaker */
    sys_vga_mode(0);   /* back to VGA text */
    sys_kbd_raw(0);
    g_ctx = NULL;
}

bool gb_platform_poll_events(GBContext *ctx) {
    poll_keyboard();
    minios_audio_ensure(ctx);
    g_dbg_poll++;
    return true; /* never quit via window close on MiniOS */
}

void gb_platform_render_frame(const uint32_t *framebuffer) {
    uint32_t now = (uint32_t)sys_time_ms();

    upload_frame(framebuffer);
    minios_audio_ensure(g_ctx);
    minios_audio_frame();

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
    sys_nk_frame();
    g_dbg_lcd_off++;
    dbg_heartbeat();
}

void gb_platform_vsync(uint32_t frame_cycles) {
    /* Pace at ~59.7 FPS (4194304 / 70224 cycles per frame) */
    g_dbg_vsync++;
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
