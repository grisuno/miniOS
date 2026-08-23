/*
 * vga_fb.c  --  Mode 13h framebuffer desktop (320x200, 256 colors)
 *
 * Desktop with terminal window, PS/2 mouse cursor, scrollbar and
 * scrollback buffer.  When vga_fb_active, all kernel output renders
 * in the framebuffer terminal instead of VGA text buffer 0xB8000.
 * Keyboard shortcuts: F11=fullscreen, Ctrl+arrows=move, F5=reset.
 */
#include "kernel.h"
#include "vga_fb.h"
#include "bootdefs.h"

int vga_fb_active;

/* Framebuffer geometry, sized by vga_fb_boot_config from the VBE info the
 * boot loader recorded (Mode 13h defaults when VBE is unavailable). */
int fb_width  = 320;
int fb_height = 200;
int fb_pitch  = 320;
unsigned long fb_phys_base = 0x000A0000UL;

void vga_fb_boot_config(void) {
    volatile uint8_t *p = (volatile uint8_t *)VBE_INFO_ADDR;
    unsigned long base;
    unsigned pitch, width, height;
    int valid = p[VBE_INFO_VALID_OFF];
    if (!valid) return;
    base   = p[VBE_INFO_FBBASE_OFF + 0]
           | ((unsigned long)p[VBE_INFO_FBBASE_OFF + 1] << 8)
           | ((unsigned long)p[VBE_INFO_FBBASE_OFF + 2] << 16)
           | ((unsigned long)p[VBE_INFO_FBBASE_OFF + 3] << 24);
    pitch  = p[VBE_INFO_PITCH_OFF + 0] | (p[VBE_INFO_PITCH_OFF + 1] << 8);
    width  = p[VBE_INFO_WIDTH_OFF + 0] | (p[VBE_INFO_WIDTH_OFF + 1] << 8);
    height = p[VBE_INFO_HEIGHT_OFF + 0] | (p[VBE_INFO_HEIGHT_OFF + 1] << 8);
    if (base == 0 || width == 0 || height == 0 || pitch == 0)
        return;
    fb_phys_base = base;
    fb_pitch     = pitch;
    fb_width     = width;
    fb_height    = height;
}

/* ---- Mouse state (fed by sched.c IRQ12 handler) ---- */
mouse_state_t mouse_state;

/* ---- Scrollback ring ---- */
static sb_ring_t sb;

static void sb_init(void) {
    sb.head = sb.tail = sb.count = 0;
    sb.view_offset = 0;
}

static void sb_push_line(const char *line, int len) {
    int idx = sb.tail;
    int i;
    if (len >= SB_LINE_MAX) len = SB_LINE_MAX - 1;
    for (i = 0; i < len; i++) sb.lines[idx][i] = line[i];
    sb.lines[idx][len] = '\0';
    sb.tail = (sb.tail + 1) % SB_MAX_LINES;
    if (sb.count < SB_MAX_LINES) sb.count++;
    else sb.head = (sb.head + 1) % SB_MAX_LINES;
}

static const char *sb_get_line(int offset) {
    if (offset < 0 || offset >= sb.count) return 0;
    int idx = (sb.tail - 1 - offset + SB_MAX_LINES * 2) % SB_MAX_LINES;
    return sb.lines[idx];
}

static int sb_total(void) { return sb.count; }

static void sb_scroll_up(void) {
    if (sb.view_offset < sb.count - 1) sb.view_offset++;
}

static void sb_scroll_down(void) {
    if (sb.view_offset > 0) sb.view_offset--;
}

static void sb_scroll_bottom(void) {
    sb.view_offset = 0;
}

/* ---- Current line being assembled (for line-level scrollback capture) ---- */
static char term_line_buf[SB_LINE_MAX];
static int  term_line_len;

static void term_line_reset(void) {
    term_line_len = 0;
}

static void term_line_push(char c) {
    if (c == '\n') {
        if (term_line_len > 0)
            sb_push_line(term_line_buf, term_line_len);
        term_line_len = 0;
        return;
    }
    if (term_line_len < SB_LINE_MAX - 1)
        term_line_buf[term_line_len++] = c;
}

/* ---- Mouse cursor bitmap (8x8 arrow) ---- */
static const uint8_t cursor_bmp[8] = {
    0b11000000,
    0b11100000,
    0b11110000,
    0b11111000,
    0b11111100,
    0b11110000,
    0b10011000,
    0b00001100,
};

static uint8_t cursor_save[8][8];
static int cursor_old_x, cursor_old_y;
static int cursor_visible;

static void cursor_save_bg(int mx, int my) {
    int i, j;
    for (j = 0; j < 8; j++)
        for (i = 0; i < 8; i++)
            cursor_save[j][i] = FB_ADDR[(my + j) * fb_pitch + (mx + i)];
}

static void cursor_draw(int mx, int my) {
    int i, j;
    for (j = 0; j < 8; j++)
        for (i = 0; i < 8; i++) {
            if (cursor_bmp[j] & (0x80 >> i))
                vga_fb_pixel(mx + i, my + j, COL_WHITE);
        }
}

static void cursor_restore(int mx, int my) {
    int i, j;
    for (j = 0; j < 8; j++)
        for (i = 0; i < 8; i++)
            vga_fb_pixel(mx + i, my + j, cursor_save[j][i]);
}

/* ---- 8x8 CP437 font (ASCII 32-127) ---- */
static const uint8_t font8x8[96][8] = {
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

/* Default non-fullscreen terminal window geometry. The shell runs in a
 * movable window: a title bar on top, a scrollbar on its right edge and text
 * below. The defaults are clamped to the framebuffer so the window always
 * fits (a small screen degrades to a near-fullscreen window). */
#define WIN_DEF_COLS  72
#define WIN_DEF_ROWS  40
#define WIN_DEF_X     4
#define WIN_DEF_Y     3

/* ---- Terminal state ---- */
static int term_cx, term_cy;
int term_x = WIN_DEF_X, term_y = WIN_DEF_Y;
int term_cols, term_rows;
static int term_fullscreen;
static int term_px_x, term_px_y, term_px_w, term_px_h;

#define FB_OFFSET(x,y) ((unsigned)(y) * fb_pitch + (unsigned)(x))

/* The text area starts one FONT_H below the window's top-left corner, which
 * is occupied by the title bar. */
static int term_content_y(void) { return term_px_y + FONT_H; }

/* ---- Palette ---- */
static void vga_fb_set_palette(void) {
    static const uint8_t pal[][3] = {
        {  0,  0,  0},  /*  0 black        */
        { 15, 15, 50},  /*  1 bg (dark navy)*/
        {100,100,110},  /*  2 taskbar       */
        {255,255,255},  /*  3 taskbar text  */
        { 60, 90,140},  /*  4 title bar     */
        {255,255,255},  /*  5 title text    */
        { 15, 15, 15},  /*  6 terminal bg   */
        {  0,220,  0},  /*  7 terminal text */
        {  0,160,  0},  /*  8 cursor        */
        {180,180,190},  /*  9 border        */
        {255,255,255},  /* 10 white         */
        { 30, 30, 40},  /* 11 shadow        */
        {100,140,220},  /* 12 highlight     */
        { 60, 60, 70},  /* 13 scrollbar bg  */
        {140,140,155},  /* 14 scrollbar thumb */
    };
    int i;
    outb(0x3C8, 0);
    for (i = 0; i < 15; i++) {
        outb(0x3C9, pal[i][0] >> 2);
        outb(0x3C9, pal[i][1] >> 2);
        outb(0x3C9, pal[i][2] >> 2);
    }
}

/* ---- Drawing primitives ---- */
void vga_fb_pixel(int x, int y, uint8_t color) {
    if (x >= 0 && x < fb_width && y >= 0 && y < fb_height)
        FB_ADDR[y * fb_pitch + x] = color;
}

void vga_fb_rect(int x, int y, int w, int h, uint8_t color) {
    int i, j;
    for (j = y; j < y + h; j++)
        for (i = x; i < x + w; i++)
            vga_fb_pixel(i, j, color);
}

void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg) {
    int px, py, i, j;
    uint8_t bits;
    const uint8_t *glyph;
    if (c < 32 || c > 127) c = 32;
    glyph = font8x8[c - 32];
    px = term_px_x + col * FONT_W;
    py = term_content_y() + row * FONT_H;
    for (j = 0; j < FONT_H; j++) {
        bits = glyph[j];
        for (i = 0; i < FONT_W; i++)
            vga_fb_pixel(px + i, py + j, (bits & (0x80 >> i)) ? fg : bg);
    }
}

void vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg) {
    int i = 0;
    while (s[i] && col + i < term_cols) {
        vga_fb_char(col + i, row, s[i], fg, bg);
        i++;
    }
}

/* Blit a text string at an absolute pixel position. Used for window chrome
 * (title bar, taskbar) which lives outside the content-relative coordinate
 * space that vga_fb_char/str operate in. */
static void text_px(int px, int py, const char *s, uint8_t fg, uint8_t bg) {
    int k, i, j;
    uint8_t bits;
    const uint8_t *glyph;
    for (k = 0; s[k]; k++) {
        char c = s[k];
        if (c < 32 || c > 127) c = 32;
        glyph = font8x8[c - 32];
        for (j = 0; j < FONT_H; j++) {
            bits = glyph[j];
            for (i = 0; i < FONT_W; i++)
                vga_fb_pixel(px + k * FONT_W + i, py + j,
                             (bits & (0x80 >> i)) ? fg : bg);
        }
    }
}

/* Composite the graphics back-buffer (e.g. DOOM's 320x200 frame) onto the
 * desktop in a titled window at native resolution, leaving the shell window
 * and desktop visible around it. Placed at the bottom-right so it does not
 * cover the default shell window. */
void vga_fb_blit_gfx_window(void) {
    const volatile uint8_t *bb = (const volatile uint8_t *)DOOM_BACKBUF_ADDR;
    int dst_x = fb_width - DOOM_W - SCROLLBAR_W;
    int dst_y = fb_height - DOOM_H - FONT_H;
    int r, b;
    if (dst_x < 0) dst_x = 0;
    if (dst_y < 0) dst_y = 0;
    vga_fb_rect(dst_x, dst_y, DOOM_W + SCROLLBAR_W, FONT_H, COL_TITLEBAR);
    text_px(dst_x + 4, dst_y, "DOOM", COL_TITLE_TXT, COL_TITLEBAR);
    for (r = 0; r < DOOM_H; r++) {
        volatile uint8_t *dst = &FB_ADDR[(dst_y + FONT_H + r) * fb_pitch + dst_x];
        const volatile uint8_t *src = bb + r * DOOM_W;
        for (b = 0; b < DOOM_W; b++)
            dst[b] = src[b];
    }
}

void vga_fb_clear(void) {
    kmemset((void *)FB_ADDR, 0, fb_width * fb_height);
}

/* ---- Layout ---- */
static void term_recalc(void) {
    int max_cols = (fb_width - SCROLLBAR_W) / FONT_W;
    int max_rows = (fb_height - FONT_H - FONT_H) / FONT_H;
    if (term_fullscreen) {
        term_x = 0; term_y = 0;
        term_cols = max_cols;
        term_rows = (fb_height - FONT_H) / FONT_H;
    } else {
        term_cols = WIN_DEF_COLS;
        if (term_cols > max_cols) term_cols = max_cols;
        term_rows = WIN_DEF_ROWS;
        if (term_rows > max_rows) term_rows = max_rows;
        /* Preserve the current window position, clamping it into range so a
         * drag or Ctrl+arrow move is not undone by the next layout pass. */
        if (term_x < 0) term_x = 0;
        if (term_y < 0) term_y = 0;
        if (term_x > max_cols - term_cols) term_x = max_cols - term_cols;
        if (term_y > max_rows - term_rows) term_y = max_rows - term_rows;
    }
    term_px_x = term_x * FONT_W;
    term_px_y = term_y * FONT_H;
    term_px_w = term_cols * FONT_W;
    term_px_h = term_rows * FONT_H;
}

/* ---- Desktop ---- */
static void draw_title(void) {
    const char *title = "MiniOS Terminal";
    vga_fb_rect(term_px_x, term_px_y, term_px_w + SCROLLBAR_W, FONT_H, COL_TITLEBAR);
    text_px(term_px_x + 4, term_px_y, title, COL_TITLE_TXT, COL_TITLEBAR);
}

static void draw_status(void) {
    const char *s1 = "F11:fs F5:reset Drag title:move Wheel:scroll";
    vga_fb_rect(0, fb_height - FONT_H, fb_width, FONT_H, COL_TASKBAR);
    text_px(0, fb_height - FONT_H, s1, COL_TASKBAR_TXT, COL_TASKBAR);
}

/* ---- Scrollbar (attached to the window's right edge) ---- */
static void draw_scrollbar(void) {
    int sx = term_px_x + term_px_w;
    int sy = term_content_y();
    int sh = term_px_h;
    int total = sb_total();
    int visible = term_rows;
    int thumb_h, thumb_y;

    /* Track background */
    vga_fb_rect(sx, sy, SCROLLBAR_W, sh, COL_SCROLLBAR);

    /* Compute thumb size and position */
    if (total <= visible) {
        thumb_h = sh;
        thumb_y = sy;
    } else {
        thumb_h = (visible * sh) / (total + visible);
        if (thumb_h < 4) thumb_h = 4;
        if (sb.view_offset == 0) {
            thumb_y = sy + sh - thumb_h;
        } else {
            int max_off = total;
            thumb_y = sy + sh - thumb_h
                      - (sb.view_offset * (sh - thumb_h)) / max_off;
        }
    }
    /* Clamp */
    if (thumb_y < sy) thumb_y = sy;
    if (thumb_y + thumb_h > sy + sh) thumb_y = sy + sh - thumb_h;

    /* Thumb (with 1px inset on each side) */
    vga_fb_rect(sx + SCROLLBAR_PAD, thumb_y + SCROLLBAR_PAD,
                SCROLLBAR_W - 2 * SCROLLBAR_PAD,
                thumb_h - 2 * SCROLLBAR_PAD, COL_SCROLL_THUMB);
}

/* ---- Full redraw of terminal content (used after scrollback navigation) ---- */
static void term_redraw_content(void) {
    int row;
    vga_fb_rect(term_px_x, term_content_y(), term_px_w, term_px_h, COL_TERMINAL);
    if (sb.view_offset > 0) {
        int start = sb.view_offset - 1;
        for (row = 0; row < term_rows && row < sb_total(); row++) {
            const char *line = sb_get_line(start - row);
            if (line) vga_fb_str(0, term_rows - 1 - row, line, COL_TERM_TXT, COL_TERMINAL);
        }
    }
    draw_scrollbar();
}

void vga_fb_draw_desktop(void) {
    vga_fb_set_palette();
    vga_fb_clear();
    term_recalc();
    vga_fb_rect(0, 0, fb_width, fb_height, COL_BG);
    draw_status();
    draw_title();
    /* Terminal content background */
    vga_fb_rect(term_px_x, term_content_y(), term_px_w, term_px_h, COL_TERMINAL);
    term_cx = 0; term_cy = 0;
    draw_scrollbar();
}

/* ---- Terminal scroll ---- */
void vga_fb_scroll_term(void) {
    /* Push the top visible line to scrollback before scrolling */
    if (sb.view_offset == 0)
        sb_push_line(term_line_buf, term_line_len);
    term_line_len = 0;
    /* Move pixel data up by FONT_H rows, honoring the framebuffer pitch. */
    if (term_px_h > FONT_H) {
        int rows = (term_px_h - FONT_H) / FONT_H;
        int r, b;
        for (r = 0; r < rows; r++) {
            const volatile uint8_t *s =
                &FB_ADDR[(term_content_y() + (r + 1) * FONT_H) * fb_pitch + term_px_x];
            volatile uint8_t *d =
                &FB_ADDR[(term_content_y() + r * FONT_H) * fb_pitch + term_px_x];
            for (b = 0; b < term_px_w; b++)
                d[b] = s[b];
        }
    }
    /* Clear bottom row */
    vga_fb_rect(term_px_x, term_content_y() + term_px_h - FONT_H, term_px_w, FONT_H, COL_TERMINAL);
    draw_scrollbar();
}

/* ---- Terminal output ---- */
void vga_fb_putc_term(char c) {
    int scrolled_back = (sb.view_offset > 0);

    if (c == '\n') {
        term_line_push('\n');
        term_cx = 0;
        if (!scrolled_back) {
            term_cy++;
            if (term_cy >= term_rows) {
                vga_fb_scroll_term();
                term_cy = term_rows - 1;
            }
        }
        return;
    }
    if (c == '\r') { term_cx = 0; return; }
    if (c == '\b') {
        if (term_cx > 0) {
            term_cx--;
            if (term_line_len > 0) term_line_len--;
            if (!scrolled_back)
                vga_fb_char(term_cx, term_cy, ' ', COL_TERM_TXT, COL_TERMINAL);
        }
        return;
    }
    if (c >= 32 && c <= 126) {
        term_line_push(c);
        if (!scrolled_back) {
            vga_fb_char(term_cx, term_cy, c, COL_TERM_TXT, COL_TERMINAL);
            term_cx++;
            if (term_cx >= term_cols) {
                term_cx = 0;
                term_cy++;
                if (term_cy >= term_rows) {
                    vga_fb_scroll_term();
                    term_cy = term_rows - 1;
                }
            }
        }
    }
}

void vga_fb_puts_term(const char *s) {
    while (*s) vga_fb_putc_term(*s++);
}

/* ---- Keyboard shortcuts ---- */
void vga_fb_toggle_fullscreen(void) {
    term_fullscreen = !term_fullscreen;
    sb_scroll_bottom();
    term_cx = 0; term_cy = 0;
    term_line_reset();
    vga_fb_draw_desktop();
}

void vga_fb_move_terminal(int dx, int dy) {
    if (dx == 0 && dy == 0) {
        /* Reset to default position */
        term_fullscreen = 0;
        term_x = WIN_DEF_X; term_y = WIN_DEF_Y;
        sb_scroll_bottom();
        term_cx = 0; term_cy = 0;
        term_line_reset();
        vga_fb_draw_desktop();
        return;
    }
    int max_x = (fb_width - SCROLLBAR_W) / FONT_W - term_cols;
    int max_y = (fb_height - 2 * FONT_H) / FONT_H - term_rows;
    int nx = term_x + dx;
    int ny = term_y + dy;
    if (nx < 0) nx = 0;
    if (ny < 0) ny = 0;
    if (nx > max_x) nx = max_x;
    if (ny > max_y) ny = max_y;
    if (nx == term_x && ny == term_y) return;
    term_x = nx; term_y = ny;
    term_px_x = term_x * FONT_W;
    term_px_y = term_y * FONT_H;
    term_cx = 0; term_cy = 0;
    vga_fb_draw_desktop();
}

/* Move the window so its title bar follows the mouse during a drag. grab_cx
 * is the character column (within the title bar) where the grab happened, so
 * the window stays under the pointer instead of jumping to the mouse origin. */
static void vga_fb_drag_terminal(int mx, int my, int grab_cx) {
    int max_x = (fb_width - SCROLLBAR_W) / FONT_W - term_cols;
    int max_y = (fb_height - 2 * FONT_H) / FONT_H - term_rows;
    int nx = mx / FONT_W - grab_cx;
    int ny = my / FONT_H;
    if (nx < 0) nx = 0;
    if (ny < 0) ny = 0;
    if (nx > max_x) nx = max_x;
    if (ny > max_y) ny = max_y;
    if (nx == term_x && ny == term_y) return;
    term_x = nx; term_y = ny;
    term_px_x = term_x * FONT_W;
    term_px_y = term_y * FONT_H;
    term_cx = 0; term_cy = 0;
    vga_fb_draw_desktop();
}

void vga_fb_handle_key(int scancode) {
    switch (scancode) {
    case 0x57: vga_fb_toggle_fullscreen(); break;
    case 0x3F: term_x = WIN_DEF_X; term_y = WIN_DEF_Y; term_fullscreen = 0;
               sb_scroll_bottom();
               term_cx = 0; term_cy = 0;
               term_line_reset();
               vga_fb_draw_desktop(); break;
    }
}

/* ---- Mouse ---- */
void vga_fb_mouse_tick(void) {
    static int dragging;
    static int grab_cx;
    int mx, my;
    int win_w = term_px_w + SCROLLBAR_W;

    if (!mouse_state.present) return;

    /* Process wheel: scroll back/forward */
    if (mouse_state.wheel != 0) {
        if (mouse_state.wheel > 0) {
            sb_scroll_up();
            sb_scroll_up();
            sb_scroll_up();
        } else {
            sb_scroll_down();
            sb_scroll_down();
            sb_scroll_down();
        }
        mouse_state.wheel = 0;
        term_redraw_content();
        draw_scrollbar();
        cursor_visible = 0;   /* content changed under the cursor: re-save */
    }

    mx = mouse_state.x;
    my = mouse_state.y;

    /* Title-bar drag: grab the window on a left press over the title bar and
     * move it while the button is held. Redrawing the desktop resets the
     * cursor, so the cursor is re-saved afterwards. */
    if (!term_fullscreen) {
        int in_title = (my >= term_px_y && my < term_content_y() &&
                        mx >= term_px_x && mx < term_px_x + win_w);
        if (mouse_state.buttons & 1) {
            if (!dragging && in_title) {
                dragging = 1;
                grab_cx = (mx - term_px_x) / FONT_W;
            }
        } else {
            dragging = 0;
        }
        if (dragging) {
            vga_fb_drag_terminal(mx, my, grab_cx);
            cursor_visible = 0;   /* desktop redraw cleared the old cursor */
            mx = mouse_state.x;
            my = mouse_state.y;
        }
    }

    /* Left click on the window scrollbar jumps the view to that position. */
    if ((mouse_state.buttons & 1) && !dragging &&
        mx >= term_px_x + term_px_w && mx < term_px_x + win_w &&
        my >= term_content_y() && my < term_content_y() + term_px_h) {
        int sy = term_content_y();
        int sh = term_px_h;
        int total = sb_total();
        int visible = term_rows;
        if (total > visible && sh > 0) {
            int max_off = total;
            int new_off = ((sy + sh - my) * max_off) / sh;
            if (new_off < 0) new_off = 0;
            if (new_off > max_off) new_off = max_off;
            sb.view_offset = new_off;
            term_redraw_content();
            cursor_visible = 0;   /* content changed under the cursor: re-save */
        }
    }

    /* Clamp mouse position */
    if (mouse_state.x < 0) mouse_state.x = 0;
    if (mouse_state.x >= fb_width - 8) mouse_state.x = fb_width - 8;
    if (mouse_state.y < 0) mouse_state.y = 0;
    if (mouse_state.y >= fb_height - 8) mouse_state.y = fb_height - 8;

    mx = mouse_state.x;
    my = mouse_state.y;

    /* Erase old cursor and draw new one */
    if (cursor_visible) {
        if (mx != cursor_old_x || my != cursor_old_y) {
            cursor_restore(cursor_old_x, cursor_old_y);
            cursor_save_bg(mx, my);
            cursor_draw(mx, my);
            cursor_old_x = mx;
            cursor_old_y = my;
        }
    } else {
        cursor_save_bg(mx, my);
        cursor_draw(mx, my);
        cursor_old_x = mx;
        cursor_old_y = my;
        cursor_visible = 1;
    }
}

void vga_fb_mouse_init(void) {
    mouse_state.x = fb_width / 2;
    mouse_state.y = fb_height / 2;
    mouse_state.buttons = 0;
    mouse_state.dx = 0;
    mouse_state.dy = 0;
    mouse_state.wheel = 0;
    mouse_state.present = 0;
    cursor_visible = 0;
    sb_init();
    term_line_reset();
}

void vga_fb_init(void) {
    vga_fb_active = 1;
    vga_fb_mouse_init();
    vga_fb_draw_desktop();
}
