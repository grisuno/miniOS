/* q2generic_minios.c - MiniOS platform layer for quake2generic.
 *
 * Quake 2 renders into a kernel back-buffer in the user window at virtual
 * 0x1FE0000; each frame it calls SYS_DOOM_FRAME (211) and the kernel
 * composites the buffer onto the hi-res desktop as a titled window at
 * native 320x200, leaving the shell window visible.
 * Syscalls: 204=time(ms), 205=kbd(scancode), 206=palette(768 bytes),
 *           207=kbd_raw_mode(0/1), 208=vga_mode, 211=doom_frame,
 *           219=mouse(x,y,buttons,wheel), 223=set_window_title.
 */

#include "quake2.h"
#include "quakegeneric.h"
#include "client/keys.h"
#include "ref_soft/r_local.h"
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define Q2G_FB_W 320
#define Q2G_FB_H 200

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

static long sys_mouse(int *buf) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(219), "D"(buf) : "rcx","r11","memory");
    return ret;
}

static long sys_set_title(const char *t) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(223), "D"(t) : "rcx","r11","memory");
    return ret;
}

#define Q2G_BACKBUF ((volatile uint8_t *)0x0B000000UL)

static int s_prev_mouse_x;
static int s_prev_mouse_y;

void QG_GetMouseDiff(int *dx, int *dy) {
    int m[4];
    sys_mouse(m);
    int cur_x = m[0];
    int cur_y = m[1];
    *dx = cur_x - s_prev_mouse_x;
    *dy = cur_y - s_prev_mouse_y;
    s_prev_mouse_x = cur_x;
    s_prev_mouse_y = cur_y;
}

void QG_CaptureMouse(void) {
    sys_kbd_raw(1);
}

void QG_ReleaseMouse(void) {
}

void QG_Mkdir(const char *path) {
    (void)path;
}

static unsigned char scancode_to_q2key(unsigned char raw) {
    unsigned char sc = raw & 0x7F;

    switch (sc) {
        case 0x01: return K_ESCAPE;
        case 0x1C: return K_ENTER;
        case 0x39: return K_SPACE;
        case 0x1D: return K_CTRL;
        case 0x2A: case 0x36: return K_SHIFT;
        case 0x38: return K_ALT;
        case 0x0E: return K_BACKSPACE;
        case 0x0F: return K_TAB;
        case 0x3A: return 0;
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
        case 0x3B: return ';';
        case 0x27: return '\'';
        case 0x28: return '`';
        case 0x33: return ',';
        case 0x34: return '.';
        case 0x35: return '/';
        case 0x0C: return '-';
        case 0x0D: return '=';
        case 0x1A: return '[';
        case 0x1B: return ']';
        case 0x29: return '\\';
        case 0x3C: return K_F1;
        case 0x3D: return K_F2;
        case 0x3E: return K_F3;
        case 0x3F: return K_F4;
        case 0x40: return K_F5;
        case 0x41: return K_F6;
        case 0x42: return K_F7;
        case 0x43: return K_F8;
        case 0x44: return K_F9;
        case 0x57: return K_F10;
        case 0x58: return K_F11;
        case 0x5B: return K_F12;
        case 0x47: return K_HOME;
        case 0x4F: return K_END;
        case 0x49: return K_PGUP;
        case 0x51: return K_PGDN;
        case 0x52: return K_INS;
        case 0x53: return K_DEL;
        case 0x46: return K_PAUSE;
        default: return 0;
    }
}

static unsigned char extended_to_q2key(unsigned char sc) {
    switch (sc) {
        case 0x48: return K_UPARROW;
        case 0x50: return K_DOWNARROW;
        case 0x4B: return K_LEFTARROW;
        case 0x4D: return K_RIGHTARROW;
        case 0x1D: return K_CTRL;
        case 0x38: return K_ALT;
        case 0x47: return K_HOME;
        case 0x4F: return K_END;
        case 0x49: return K_PGUP;
        case 0x51: return K_PGDN;
        case 0x52: return K_INS;
        case 0x53: return K_DEL;
        default: return 0;
    }
}

static void kbd_poll(void) {
    for (;;) {
        long sc = sys_kbd();
        if (sc < 0) break;
        unsigned char raw = (unsigned char)sc;

        if (raw == 0xE0) {
            long sc2 = sys_kbd();
            if (sc2 < 0) break;
            unsigned char raw2 = (unsigned char)sc2;
            unsigned char qkey = extended_to_q2key(raw2 & 0x7F);
            if (qkey) {
                Quake2_SendKey(qkey, !(raw2 & 0x80));
            }
            continue;
        }

        if (raw & 0x80) {
            unsigned char qkey = scancode_to_q2key(raw);
            if (qkey) Quake2_SendKey(qkey, 0);
        } else {
            unsigned char qkey = scancode_to_q2key(raw);
            if (qkey) Quake2_SendKey(qkey, 1);
        }
    }
}

static int palette_dirty = 1;
static unsigned char q2_palette[768];

void SWimp_SetPalette(const unsigned char *palette) {
    int i;
    for (i = 0; i < 256; i++) {
        q2_palette[i * 3 + 0] = palette[i * 4 + 0];
        q2_palette[i * 3 + 1] = palette[i * 4 + 1];
        q2_palette[i * 3 + 2] = palette[i * 4 + 2];
    }
    palette_dirty = 1;
}

rserr_t SWimp_SetMode(int *pwidth, int *pheight, int mode, qboolean fullscreen) {
    (void)mode;
    (void)fullscreen;

    ri.Con_Printf(PRINT_ALL, "...forcing mode 320x200\n");

    *pwidth  = 320;
    *pheight = 200;

    vid.rowbytes = 320;
    vid.buffer   = (pixel_t *)Q2G_BACKBUF;

    ri.Vid_NewWindow(320, 200);

    return rserr_ok;
}

int SWimp_Init(void *hInstance, void *wndProc) {
    sys_vga_mode(1);
    sys_kbd_raw(1);
    return 1;
}

void SWimp_Shutdown(void) {
}

void SWimp_BeginFrame(float camera_separation) {
}

void SWimp_EndFrame(void) {
    if (palette_dirty) {
        sys_palette(q2_palette);
        palette_dirty = 0;
    }

    sys_doom_frame();
    kbd_poll();
}

void SWimp_AppActivate(qboolean active) {
    (void)active;
}

int QG_Milliseconds(void) {
    return (int)sys_time_ms();
}

int main(int argc, char **argv) {
    int time, oldtime, newtime;

    sys_set_title("Quake 2");

    Quake2_Init(argc, argv);

    int m[4];
    sys_mouse(m);
    s_prev_mouse_x = m[0];
    s_prev_mouse_y = m[1];

    oldtime = Quake2_Milliseconds();
    while (1) {
        do {
            newtime = Quake2_Milliseconds();
            time = newtime - oldtime;
        } while (time < 1);

        Quake2_Frame(time);

        oldtime = newtime;
    }

    return 0;
}
