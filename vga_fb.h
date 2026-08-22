#ifndef VGA_FB_H
#define VGA_FB_H

#include <stdint.h>

#define FB_WIDTH   320
#define FB_HEIGHT  200
#define FB_ADDR    ((volatile uint8_t *)0x1F00000UL)

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
#define SB_MAX_LINES 256
#define SB_LINE_MAX  48

typedef struct {
    char lines[SB_MAX_LINES][SB_LINE_MAX];
    int  head;
    int  tail;
    int  count;
    int  view_offset;
} sb_ring_t;

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
void     vga_fb_scroll_term(void);
void     vga_fb_handle_key(int scancode);
void     vga_fb_toggle_fullscreen(void);
void     vga_fb_move_terminal(int dx, int dy);
void     vga_fb_mouse_tick(void);
void     vga_fb_mouse_init(void);

extern int vga_fb_active;

#endif
