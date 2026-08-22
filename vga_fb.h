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

#define FONT_W  8
#define FONT_H  8

/* Terminal geometry (set by vga_fb layout engine) */
extern int term_x, term_y, term_cols, term_rows;

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

extern int vga_fb_active;

#endif
