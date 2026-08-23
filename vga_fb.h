#ifndef VGA_FB_H
#define VGA_FB_H

#include <stdint.h>

/* Framebuffer geometry. The boot loader probes VESA BIOS Extensions for a
 * high-resolution 8-bit-palette linear framebuffer and records width, height,
 * pitch and physical base in the fixed VBE_INFO_ADDR struct; vga_fb_boot_config
 * loads them into the globals below before the kernel maps the framebuffer.
 * Without VBE the values are the Mode 13h defaults (320x200x8, phys 0xA0000).
 * FB_ADDR is the fixed virtual address in the user window that both the kernel
 * desktop and graphics programs write through. */
#define FB_ADDR    ((volatile uint8_t *)0x1F00000UL)
extern int fb_width;
extern int fb_height;
extern int fb_pitch;
extern unsigned long fb_phys_base;

void vga_fb_boot_config(void);

/* Graphics-window compositing. A ring-3 program (DOOM) renders into a
 * kernel-backed back-buffer mapped into the user window at DOOM_BACKBUF_ADDR
 * and calls SYS_DOOM_FRAME (211) to have the kernel composite it onto the
 * desktop at its native resolution, so the shell window stays visible. */
#define DOOM_W            320
#define DOOM_H            200
#define DOOM_BACKBUF_ADDR 0x1FE0000UL
void vga_fb_blit_gfx_window(void);

/* Palette indices */
#define COL_BG          1
#define COL_TASKBAR     2
#define COL_TASKBAR_TXT 3
#define COL_TITLEBAR    4
#define COL_TITLE_TXT   5
#define COL_TERMINAL    6
#define COL_TERM_TXT    7
#define COL_TERM_CUR    8
#define COL_BORDER      9
#define COL_WHITE       10
#define COL_SHADOW      11
#define COL_HIGHLIGHT   12
#define COL_SCROLLBAR   13
#define COL_SCROLL_THUMB 14

#define FONT_W  8
#define FONT_H  8

/* Upper bound on the terminal's size, used to size the live-screen buffer and
 * the scrollback ring. The framebuffer dimensions are clamped to these before
 * any buffer is indexed, so a very large display never overruns them. */
#define TERM_MAX_COLS 256
#define TERM_MAX_ROWS 128

/* Taskbar geometry (drawn at the bottom, height = one font row). */
#define TASKBAR_H         FONT_H
#define TASKBAR_PAD        4
#define TASKBAR_CLOCK_CH   8      /* "HH:MM:SS" */
#define TASKBAR_VOL_CH     3      /* "NN%" */
#define TASKBAR_VOL_STEP   10
#define TASKBAR_ICON_W     8
#define TASKBAR_BTN_W      8

/* Tiling snap zones (Alt is the WM modifier). */
#define TILING_LEFT          0
#define TILING_RIGHT         1
#define TILING_TOP           2
#define TILING_BOTTOM        3
#define TILING_TOP_LEFT      4
#define TILING_TOP_RIGHT     5
#define TILING_BOTTOM_LEFT   6
#define TILING_BOTTOM_RIGHT  7

/* Scrollbar geometry */
#define SCROLLBAR_W     8
#define SCROLLBAR_PAD   1

/* Terminal geometry (set by vga_fb layout engine) */
extern int term_x, term_y, term_cols, term_rows;

/* ---- Mouse state (updated by IRQ12 handler in sched.c) ---- */
typedef struct {
    int x, y;
    int buttons;
    int dx, dy;
    int wheel;
    int present;
} mouse_state_t;

extern mouse_state_t mouse_state;

/* ---- Scrollback ---- */
/* A scrollback line can be up to the widest terminal (TERM_MAX_COLS), and a
 * long logical line that wrapped across several screen rows is stored whole,
 * so the ring must not truncate it or a re-rendered line would be cut short. */
#define SB_MAX_LINES 256
#define SB_LINE_MAX  TERM_MAX_COLS

/* ---- Public API ---- */
void     vga_fb_init(void);
void     vga_fb_clear(void);
void     vga_fb_pixel(int x, int y, uint8_t color);
void     vga_fb_rect(int x, int y, int w, int h, uint8_t color);
void     vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg);
void     vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg);
void     vga_fb_putc_term(char c);
void     vga_fb_puts_term(const char *s);
void     vga_fb_draw_desktop(void);
void     vga_fb_handle_key(int scancode);
void     vga_fb_toggle_fullscreen(void);
void     vga_fb_move_terminal(int dx, int dy);
void     vga_fb_snap_window(int zone);
void     vga_fb_resize(int dcols, int drows);
void     vga_fb_reset_default(void);
void     vga_fb_mouse_tick(void);
void     vga_fb_mouse_init(void);

extern int vga_fb_active;

#endif
