/* doomgeneric_minios.c - MiniOS platform layer for doomgeneric.
 *
 * DOOM renders into a kernel back-buffer in the user window at virtual
 * 0x0B000000 (DOOM_BACKBUF_ADDR); each frame it calls SYS_DOOM_FRAME (211)
 * and the kernel composites the buffer onto the hi-res desktop as a titled
 * window at native 320x200, leaving the shell window visible. The VBE linear
 * framebuffer is set up by the boot loader.
 * Syscalls: 204=time(ms), 205=kbd(scancode), 206=palette(768 bytes),
 *           207=kbd_raw_mode(0/1), 208=vga_mode, 211=doom_frame.
 */

#include "doomgeneric.h"
#include "doomkeys.h"
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
static long sys_vga_mode(int on) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(208), "D"((long)on) : "rcx","r11","memory");
    return ret;
}
static long sys_doom_frame(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(211), "D"(0) : "rcx","r11","memory");
    return ret;
}

/* ---------- Graphics back-buffer ---------- */

/* DOOM renders into a kernel-backed back-buffer in the user window; the
 * kernel composites it onto the desktop as a window on SYS_DOOM_FRAME. */
#define FB_ADDR    ((volatile uint8_t *)0x0B000000UL)
#define FB_WIDTH   320
#define FB_HEIGHT  200

/* ---------- Palette management ---------- */

/* Extern from i_video.c - the gamma-corrected palette colors */
struct color { uint32_t b:8; uint32_t g:8; uint32_t r:8; uint32_t a:8; };
extern struct color colors[256];

/* Dirty flag: set by I_SetPalette(), cleared after we push the 768 bytes of
 * the 256-color VGA DAC on the next frame, instead of on every frame. */
volatile int minios_palette_dirty = 1;

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

    switch (sc) {
        case 0x01: return KEY_ESCAPE;
        case 0x1C: return KEY_ENTER;
        case 0x39: return KEY_USE;      /* Space = use */
        case 0x1D: return KEY_FIRE;     /* Ctrl = fire */
        case 0x2A: case 0x36: return KEY_RSHIFT;
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
        case 0x0E: return KEY_BACKSPACE;
        case 0x0F: return KEY_TAB;
        case 0x3A: return KEY_CAPSLOCK;
        case 0x38: return KEY_LALT;
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
            /* Extract the make code (strip break bit for lookup) */
            unsigned char make = raw2 & 0x7F;
            if (make == 0x48) doom_key = KEY_UPARROW;
            else if (make == 0x50) doom_key = KEY_DOWNARROW;
            else if (make == 0x4B) doom_key = KEY_LEFTARROW;
            else if (make == 0x4D) doom_key = KEY_RIGHTARROW;
            else if (make == 0x1D) doom_key = KEY_RCTRL;
            else if (make == 0x38) doom_key = KEY_RALT;
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

extern unsigned char *I_VideoBuffer;

void DG_Init(void) {
    sys_vga_mode(1);  /* tell kernel to stop touching VGA text hardware */
    sys_kbd_raw(1);   /* enable raw keyboard mode for DOOM */
}

void DG_DrawFrame(void) {
    if (!I_VideoBuffer) return;

    if (minios_palette_dirty) {
        load_vga_palette();
        minios_palette_dirty = 0;
    }

    volatile uint8_t *dst = FB_ADDR;
    uint8_t *src = (uint8_t *)I_VideoBuffer;
    int i;
    for (i = 0; i < 64000; i++) {
        dst[i] = src[i];
    }
    sys_doom_frame();
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
