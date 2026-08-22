/* doomgeneric_minios.c - MiniOS platform layer for doomgeneric.
 *
 * VGA Mode 13h (320x200, 256 colors) set by stage1.S.
 * Framebuffer at virtual 0x1F00000 (physical 0xA0000).
 * Syscalls: 204=time(ms), 205=kbd(scancode), 206=palette(768 bytes),
 *           207=kbd_raw_mode(0/1).
 */

#include "doomgeneric.h"
#include <stdint.h>
#include <string.h>

/* ---------- MiniOS syscalls ---------- */

static long sys_time_ms(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(204), "D"(0) : "rcx","r11","memory");
    return ret;
}
static long sys_kbd(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(205), "D"(0) : "rcx","r11","memory");
    return ret;
}
static long sys_palette(const unsigned char *pal) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(206), "D"(pal) : "rcx","r11","memory");
    return ret;
}
static long sys_kbd_raw(int on) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(207), "D"((long)on) : "rcx","r11","memory");
    return ret;
}

/* ---------- VGA Mode 13h framebuffer ---------- */

#define FB_ADDR    ((volatile uint8_t *)0x1F00000UL)
#define FB_WIDTH   320
#define FB_HEIGHT  200

/* ---------- Palette management ---------- */

/* Extern from i_video.c - the gamma-corrected palette colors */
struct color { uint32_t b:8; uint32_t g:8; uint32_t r:8; uint32_t a:8; };
extern struct color colors[256];

/* Dirty flag: set by I_SetPalette(), cleared after we rebuild the VGA state.
 * Avoids rebuilding the 4096-entry hash table and pushing 768 bytes to the
 * VGA DAC on every single frame. */
volatile int minios_palette_dirty = 1;

/* 4-bit hash table for fast RGB -> palette index lookup */
#define HT_SIZE 4096
static int16_t ht_idx[HT_SIZE];
static uint8_t ht_r[HT_SIZE], ht_g[HT_SIZE], ht_b[HT_SIZE];

static unsigned ht_hash(uint8_t r, uint8_t g, uint8_t b) {
    return (((unsigned)r << 8) | ((unsigned)g << 4) | (unsigned)b) & (HT_SIZE - 1);
}

static void ht_clear(void) {
    int i;
    for (i = 0; i < HT_SIZE; i++) ht_idx[i] = -1;
}

static void ht_insert(uint8_t r, uint8_t g, uint8_t b, uint8_t idx) {
    unsigned h = ht_hash(r, g, b);
    while (ht_idx[h] >= 0) h = (h + 1) & (HT_SIZE - 1);
    ht_idx[h] = (int16_t)idx;
    ht_r[h] = r; ht_g[h] = g; ht_b[h] = b;
}

static uint8_t ht_lookup(uint8_t r, uint8_t g, uint8_t b) {
    unsigned h = ht_hash(r, g, b);
    while (ht_idx[h] >= 0) {
        if (ht_r[h] == r && ht_g[h] == g && ht_b[h] == b)
            return (uint8_t)ht_idx[h];
        h = (h + 1) & (HT_SIZE - 1);
    }
    /* brute-force fallback */
    int best = 0, best_d = 0x7fffffff;
    int i;
    for (i = 0; i < 256; i++) {
        int dr = (int)colors[i].r - r;
        int dg = (int)colors[i].g - g;
        int db = (int)colors[i].b - b;
        int d = dr*dr + dg*dg + db*db;
        if (d < best_d) { best_d = d; best = i; }
    }
    return (uint8_t)best;
}

static void rebuild_palette_ht(void) {
    ht_clear();
    int i;
    for (i = 0; i < 256; i++)
        ht_insert(colors[i].r, colors[i].g, colors[i].b, (uint8_t)i);
}

static void load_vga_palette(void) {
    uint8_t dac[768];
    int i;
    for (i = 0; i < 256; i++) {
        dac[i*3+0] = colors[i].r;
        dac[i*3+1] = colors[i].g;
        dac[i*3+2] = colors[i].b;
    }
    sys_palette(dac);
}

/* ---------- PS/2 Set 1 -> DOOM key ---------- */

static unsigned char scancode_to_doom(unsigned char raw) {
    unsigned char sc = raw & 0x7F;
    int pressed = !(raw & 0x80);

    switch (sc) {
        case 0x01: return 0x1B; /* Escape */
        case 0x1C: return 0x0D; /* Enter */
        case 0x39: return ' ';   /* Space = use */
        case 0x1D: return 0x1D; /* Ctrl = fire */
        case 0x2A: case 0x36: return 0x1D; /* Shift = fire */
        case 0x48: return 0xB0; /* Up arrow */
        case 0x50: return 0xB1; /* Down arrow */
        case 0x4B: return 0xB2; /* Left arrow */
        case 0x4D: return 0xB3; /* Right arrow */
        case 0x02: return '1';
        case 0x03: return '2';
        case 0x04: return '3';
        case 0x05: return '4';
        case 0x06: return '5';
        case 0x07: return '6';
        case 0x08: return '7';
        case 0x09: return '8';
        case 0x0A: return '9';
        case 0x0B: return '0';
        case 0x10: return 'q';
        case 0x11: return 'w';
        case 0x12: return 'e';
        case 0x13: return 'r';
        case 0x14: return 't';
        case 0x15: return 'y';
        case 0x16: return 'u';
        case 0x17: return 'i';
        case 0x18: return 'o';
        case 0x19: return 'p';
        case 0x1E: return 'a';
        case 0x1F: return 's';
        case 0x20: return 'd';
        case 0x21: return 'f';
        case 0x22: return 'g';
        case 0x23: return 'h';
        case 0x24: return 'j';
        case 0x25: return 'k';
        case 0x26: return 'l';
        case 0x2C: return 'z';
        case 0x2D: return 'x';
        case 0x2E: return 'c';
        case 0x2F: return 'v';
        case 0x30: return 'b';
        case 0x31: return 'n';
        case 0x32: return 'm';
        case 0x0E: return 0x08; /* Backspace */
        case 0x0F: return 0x09; /* Tab */
        default: return 0;
    }
}

/* ---------- Keyboard queue ---------- */

#define KBD_QUEUE_SIZE 32
static unsigned char kbd_q[KBD_QUEUE_SIZE];
static int kbd_head, kbd_tail;

static void kbd_enqueue(unsigned char doom_key, int pressed) {
    unsigned short entry = ((unsigned short)(pressed ? 1 : 0) << 8) | doom_key;
    kbd_q[kbd_head] = (unsigned char)entry;
    kbd_q[(kbd_head + 1) & (KBD_QUEUE_SIZE - 1)] = (unsigned char)(entry >> 8);
    kbd_head = (kbd_head + 2) & (KBD_QUEUE_SIZE - 1);
}

static void kbd_poll(void) {
    for (;;) {
        long sc = sys_kbd();
        if (sc < 0) break;
        unsigned char raw = (unsigned char)sc;

        if (raw == 0xE0) {
            /* Extended key prefix: next byte is the actual scancode */
            long sc2 = sys_kbd();
            if (sc2 < 0) break;
            unsigned char raw2 = (unsigned char)sc2;
            unsigned char doom_key = 0;
            if (raw2 == 0x48) doom_key = 0xB0; /* Up */
            else if (raw2 == 0x50) doom_key = 0xB1; /* Down */
            else if (raw2 == 0x4B) doom_key = 0xB2; /* Left */
            else if (raw2 == 0x4D) doom_key = 0xB3; /* Right */
            if (doom_key) {
                int pressed = !(raw2 & 0x80);
                kbd_enqueue(doom_key, pressed);
            }
            continue;
        }

        if (raw & 0x80) {
            /* Break code: key released */
            unsigned char doom_key = scancode_to_doom(raw);
            if (doom_key) kbd_enqueue(doom_key, 0);
        } else {
            /* Make code: key pressed */
            unsigned char doom_key = scancode_to_doom(raw);
            if (doom_key) kbd_enqueue(doom_key, 1);
        }
    }
}

/* ---------- doomgeneric interface ---------- */

void DG_Init(void) {
    sys_kbd_raw(1);  /* enable raw keyboard mode for DOOM */
}

void DG_DrawFrame(void) {
    if (!DG_ScreenBuffer) return;

    if (minios_palette_dirty) {
        rebuild_palette_ht();
        load_vga_palette();
        minios_palette_dirty = 0;
    }

    uint32_t *src = DG_ScreenBuffer;
    int x, y;

    for (y = 0; y < FB_HEIGHT; y++) {
        int sy = y * 2;
        if (sy >= DOOMGENERIC_RESY) sy = DOOMGENERIC_RESY - 1;

        volatile uint8_t *row = FB_ADDR + (y * FB_WIDTH);

        for (x = 0; x < FB_WIDTH; x++) {
            int sx = x * 2;
            if (sx >= DOOMGENERIC_RESX) sx = DOOMGENERIC_RESX - 1;

            uint32_t px = src[sy * DOOMGENERIC_RESX + sx];
            uint8_t r = (px >> 16) & 0xFF;
            uint8_t g = (px >> 8)  & 0xFF;
            uint8_t b = (px)       & 0xFF;
            row[x] = ht_lookup(r, g, b);
        }
    }
    kbd_poll();
}

void DG_SleepMs(uint32_t ms) {
    unsigned int start = (unsigned int)sys_time_ms();
    while ((unsigned int)sys_time_ms() - start < ms)
        __asm__ volatile("pause");
}

uint32_t DG_GetTicksMs(void) {
    return (unsigned int)sys_time_ms();
}

int DG_GetKey(int *pressed, unsigned char *key) {
    if (kbd_head == kbd_tail) return 0;
    unsigned char dk = kbd_q[kbd_tail];
    kbd_tail = (kbd_tail + 1) & (KBD_QUEUE_SIZE - 1);
    unsigned char pflag = kbd_q[kbd_tail];
    kbd_tail = (kbd_tail + 1) & (KBD_QUEUE_SIZE - 1);
    *pressed = pflag;
    *key = dk;
    return 1;
}

void DG_SetWindowTitle(const char *title) {
    (void)title;
}
