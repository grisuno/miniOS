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

/* The arrow's visual point is its lower-right tip, not the cell's top-left
 * corner. Click hit-tests use (mouse + tip) so a click lands where the user
 * aims the arrow instead of a few pixels up-left of it. */
#define CURSOR_TIP_X 6
#define CURSOR_TIP_Y 7

static uint8_t cursor_save[8][8];
static int cursor_old_x, cursor_old_y;
static int cursor_visible;

/* The cursor is drawn with its arrow tip at (mx, my), so the sprite spans
 * up-left of the pointer by CURSOR_TIP offsets. The caller clamps mx/my so
 * the sprite's top-left corner stays non-negative and the raw FB reads in
 * cursor_save_bg never go out of bounds. */
static void cursor_save_bg(int mx, int my) {
    int i, j;
    int x0 = mx - CURSOR_TIP_X;
    int y0 = my - CURSOR_TIP_Y;
    for (j = 0; j < 8; j++)
        for (i = 0; i < 8; i++)
            cursor_save[j][i] = FB_ADDR[(y0 + j) * fb_pitch + (x0 + i)];
}

static void cursor_draw(int mx, int my) {
    int i, j;
    int x0 = mx - CURSOR_TIP_X;
    int y0 = my - CURSOR_TIP_Y;
    for (j = 0; j < 8; j++)
        for (i = 0; i < 8; i++) {
            if (cursor_bmp[j] & (0x80 >> i))
                vga_fb_pixel(x0 + i, y0 + j, COL_WHITE);
        }
}

static void cursor_restore(int mx, int my) {
    int i, j;
    int x0 = mx - CURSOR_TIP_X;
    int y0 = my - CURSOR_TIP_Y;
    for (j = 0; j < 8; j++)
        for (i = 0; i < 8; i++)
            vga_fb_pixel(x0 + i, y0 + j, cursor_save[j][i]);
}

/* True when the cursor sprite overlaps the given screen rectangle. Used to
 * decide whether a partial repaint (taskbar, terminal content) overwrote the
 * cursor, in which case its saved background must be refreshed; otherwise the
 * cursor keeps its saved background and moves without leaving a trail. */
static int cursor_over(int x0, int y0, int w, int h) {
    int cxl = mouse_state.x - CURSOR_TIP_X;   /* sprite left edge */
    int cxt = mouse_state.x + 1;              /* sprite right edge */
    int cyl = mouse_state.y - CURSOR_TIP_Y;   /* sprite top edge */
    int cyt = mouse_state.y;                  /* sprite bottom edge */
    return cxl < x0 + w && cxt > x0 && cyl < y0 + h && cyt > y0;
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
#define WIN_DEF_COLS  88
#define WIN_DEF_ROWS  40
#define WIN_DEF_X     4
#define WIN_DEF_Y     3

/* ---- Terminal state ---- */
static int term_cx, term_cy;
int term_x = WIN_DEF_X, term_y = WIN_DEF_Y;
int term_cols, term_rows;
static int term_sz_cols = WIN_DEF_COLS;   /* persisted size across redraws */
static int term_sz_rows = WIN_DEF_ROWS;
static int term_fullscreen;
static int term_px_x, term_px_y, term_px_w, term_px_h;

/* Live-screen text buffer. The framebuffer terminal is re-rendered from this
 * whenever the desktop redraws (window move/snap/resize/fullscreen), so moving
 * the window never erases the current screen — the prompt and typed command
 * survive. Bounds are enforced when the size is clamped in term_recalc, so the
 * buffer can never be indexed out of range. */
static char term_screen[TERM_MAX_ROWS][TERM_MAX_COLS];

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
 * and desktop visible around it. Centered on the screen because the graphics
 * program owns the display while it runs (no mouse), so the window cannot be
 * dragged into a better spot. */
void vga_fb_blit_gfx_window(void) {
    const volatile uint8_t *bb = (const volatile uint8_t *)DOOM_BACKBUF_ADDR;
    int dst_x = (fb_width - DOOM_W) / 2;
    int dst_y = (fb_height - DOOM_H) / 2;
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
static int term_max_cols(void);
static int term_max_rows(void);
static void term_redraw_screen(void);

static void term_recalc(void) {
    int max_cols = term_max_cols();
    int max_rows = term_max_rows();
    if (term_fullscreen) {
        term_x = 0; term_y = 0;
        term_cols = max_cols;
        term_rows = max_rows;
    } else {
        term_cols = term_sz_cols;
        if (term_cols > max_cols) term_cols = max_cols;
        term_rows = term_sz_rows;
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

/* ---- Taskbar (clock + speaker volume) ----
 * The bottom strip is the desktop's status bar: a live CMOS clock on the
 * right and a speaker icon with -/+ volume buttons. The widgets and the
 * shell `date`/`vol` builtins share the same rtc_read_tod/pcspk_get_volume
 * state, so the framebuffer and the serial console can never disagree. */
static int tb_spk_x, tb_minus_x, tb_plus_x, tb_vol_x, tb_clock_x;

static void taskbar_layout(void) {
    int x = fb_width;
    x -= TASKBAR_CLOCK_CH * FONT_W; tb_clock_x = x;
    x -= TASKBAR_PAD;
    x -= TASKBAR_VOL_CH * FONT_W;   tb_vol_x = x;
    x -= TASKBAR_PAD;
    x -= TASKBAR_BTN_W;             tb_plus_x = x;
    x -= TASKBAR_PAD;
    x -= TASKBAR_BTN_W;             tb_minus_x = x;
    x -= TASKBAR_PAD;
    x -= TASKBAR_ICON_W;            tb_spk_x = x;
}

/* 8x8 speaker glyph: body on the left, two sound arcs to the right. */
static void draw_speaker_icon(int x, int y, uint8_t color) {
    vga_fb_rect(x, y + 1, 2, 6, color);
    vga_fb_rect(x + 2, y + 3, 2, 2, color);
    vga_fb_pixel(x + 4, y + 3, color);
    vga_fb_pixel(x + 5, y + 2, color);
    vga_fb_pixel(x + 5, y + 4, color);
    vga_fb_pixel(x + 6, y + 3, color);
}

static void taskbar_render(void) {
    char buf[16];
    int h, m, s;
    unsigned vol = pcspk_get_volume();
    int y = fb_height - FONT_H;
    vga_fb_rect(0, y, fb_width, FONT_H, COL_TASKBAR);
    taskbar_layout();
    text_px(0, y, "Drag title:move Wheel:scroll Alt:snap/resize",
            COL_TASKBAR_TXT, COL_TASKBAR);
    draw_speaker_icon(tb_spk_x, y, vol ? COL_TASKBAR_TXT : COL_HIGHLIGHT);
    text_px(tb_minus_x, y, "-", COL_TASKBAR_TXT, COL_TASKBAR);
    text_px(tb_plus_x, y, "+", COL_TASKBAR_TXT, COL_TASKBAR);
    ksprintf(buf, "%u%%", vol);
    text_px(tb_vol_x, y, buf, COL_TASKBAR_TXT, COL_TASKBAR);
    if (rtc_read_tod(&h, &m, &s)) {
        ksprintf(buf, "%02d:%02d:%02d", h, m, s);
        text_px(tb_clock_x, y, buf, COL_TASKBAR_TXT, COL_TASKBAR);
    }
}

/* Redraw the clock only when the wall-clock second changes. Only the taskbar
 * strip is repainted, so the cursor must be re-saved (cursor_visible = 0) only
 * when it actually sat over the taskbar; otherwise it keeps its saved
 * background and moves normally, which is what prevents pointer trails. */
static void taskbar_tick(void) {
    int h, m, s;
    int y = fb_height - FONT_H;
    static int last_h = -1, last_m = -1, last_s = -1;
    if (!rtc_read_tod(&h, &m, &s)) return;
    if (h == last_h && m == last_m && s == last_s) return;
    last_h = h; last_m = m; last_s = s;
    taskbar_render();
    if (cursor_over(0, y, fb_width, FONT_H))
        cursor_visible = 0;
}

/* Click handling for the speaker icon and -/+ buttons. */
static void taskbar_handle_click(int mx, int my) {
    unsigned v;
    static int spk_saved_valid;
    static unsigned spk_saved_vol;
    int y = fb_height - FONT_H;
    if (my < y || my >= y + FONT_H) return;
    if (mx >= tb_spk_x && mx < tb_spk_x + TASKBAR_ICON_W) {
        v = pcspk_get_volume();
        if (v == 0) {
            pcspk_set_volume(spk_saved_valid ? spk_saved_vol : v);
        } else {
            spk_saved_vol = v;
            spk_saved_valid = 1;
            pcspk_set_volume(0);
        }
        return;
    }
    if (mx >= tb_minus_x && mx < tb_minus_x + TASKBAR_BTN_W) {
        v = pcspk_get_volume();
        pcspk_set_volume(v > TASKBAR_VOL_STEP ? v - TASKBAR_VOL_STEP : 0);
        return;
    }
    if (mx >= tb_plus_x && mx < tb_plus_x + TASKBAR_BTN_W) {
        pcspk_set_volume(pcspk_get_volume() + TASKBAR_VOL_STEP);
        return;
    }
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

/* Draw a text string into the terminal starting at screen row `row`, wrapping
 * long lines at term_cols exactly as the live screen does, and return the row
 * below the last drawn. Used when replaying scrollback so a line wider than
 * the window is never cut short. */
static int term_puts_wrap(int row, const char *s, uint8_t fg, uint8_t bg) {
    int i = 0;
    while (row < term_rows) {
        int drawn = 0;
        while (s[i] && drawn < term_cols) {
            vga_fb_char(drawn, row, s[i], fg, bg);
            i++;
            drawn++;
        }
        if (drawn < term_cols) return row + 1;
        row++;
    }
    return row;
}

/* Repaint the terminal content honouring the current scrollback view: the
 * scrolled-back history when sb.view_offset > 0, otherwise the live screen
 * replayed from the buffer. Scrolled-back lines are shown newest-at-bottom,
 * oldest-at-top, wrapped to the window width. Used after a desktop redraw and
 * by wheel scroll. */
static void term_redraw_content(void) {
    int row = 0;
    vga_fb_rect(term_px_x, term_content_y(), term_px_w, term_px_h, COL_TERMINAL);
    if (sb.view_offset > 0) {
        int off = (sb.view_offset - 1) + (term_rows - 1);   /* oldest visible */
        int end = sb.view_offset - 1;                        /* newest visible */
        for (; off >= end && row < term_rows; off--) {
            const char *line = sb_get_line(off);
            if (line) row = term_puts_wrap(row, line, COL_TERM_TXT, COL_TERMINAL);
        }
    } else {
        term_redraw_screen();
    }
    draw_scrollbar();
}

void vga_fb_draw_desktop(void) {
    vga_fb_set_palette();
    vga_fb_clear();
    term_recalc();
    vga_fb_rect(0, 0, fb_width, fb_height, COL_BG);
    taskbar_render();
    draw_title();
    /* Repaint the terminal content (live screen or scrollback view) so the
     * prompt and any typed/echoed text survive a window move, snap, resize or
     * fullscreen toggle. */
    term_cx = 0; term_cy = 0;
    term_redraw_content();
    /* Any redraw changed the pixels under the cursor; force a fresh save so a
     * stale snapshot never leaves pointer trails behind. */
    cursor_visible = 0;
}

/* ---- Terminal scroll ---- */

/* Draw one character into both the live-screen buffer and the framebuffer,
 * keeping the two in sync so a desktop redraw can replay the screen. */
static void term_draw_char(int col, int row, char c, uint8_t fg, uint8_t bg) {
    if (col < 0 || col >= term_cols || row < 0 || row >= term_rows) return;
    term_screen[row][col] = c;
    vga_fb_char(col, row, c, fg, bg);
}

/* Replay the whole visible screen from the buffer. Called after a desktop
 * redraw repainted only the terminal background. */
static void term_redraw_screen(void) {
    int r, c;
    for (r = 0; r < term_rows; r++)
        for (c = 0; c < term_cols; c++)
            vga_fb_char(c, r, term_screen[r][c], COL_TERM_TXT, COL_TERMINAL);
}

void vga_fb_scroll_term(void) {
    int r, c;
    /* Push the top visible line to scrollback before scrolling */
    if (sb.view_offset == 0)
        sb_push_line(term_line_buf, term_line_len);
    term_line_len = 0;
    /* Shift the live-screen buffer up one row and blank the new bottom row. */
    for (r = 0; r < term_rows - 1; r++)
        for (c = 0; c < term_cols; c++)
            term_screen[r][c] = term_screen[r + 1][c];
    for (c = 0; c < term_cols; c++)
        term_screen[term_rows - 1][c] = ' ';
    /* Move pixel data up by FONT_H rows, honoring the framebuffer pitch. */
    if (term_px_h > FONT_H) {
        int rows = (term_px_h - FONT_H) / FONT_H;
        int r2, b;
        for (r2 = 0; r2 < rows; r2++) {
            const volatile uint8_t *s =
                &FB_ADDR[(term_content_y() + (r2 + 1) * FONT_H) * fb_pitch + term_px_x];
            volatile uint8_t *d =
                &FB_ADDR[(term_content_y() + r2 * FONT_H) * fb_pitch + term_px_x];
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
                term_draw_char(term_cx, term_cy, ' ', COL_TERM_TXT, COL_TERMINAL);
        }
        return;
    }
    if (c >= 32 && c <= 126) {
        term_line_push(c);
        if (!scrolled_back) {
            term_draw_char(term_cx, term_cy, c, COL_TERM_TXT, COL_TERMINAL);
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

/* ---- Tiling window operations (Alt = WM modifier) ----
 * Snap places the window in a screen half or quadrant and sizes it to that
 * region; resize grows/shrinks the persisted size. Both exit fullscreen and
 * preserve the new size across redraws. */
static int term_max_cols(void) {
    int m = (fb_width - SCROLLBAR_W) / FONT_W;
    return m > TERM_MAX_COLS ? TERM_MAX_COLS : m;
}
static int term_max_rows(void) {
    int m = (fb_height - 2 * FONT_H) / FONT_H;
    return m > TERM_MAX_ROWS ? TERM_MAX_ROWS : m;
}

static void term_finish_layout(void) {
    term_recalc();
    term_cx = 0; term_cy = 0;
    term_line_reset();
    vga_fb_draw_desktop();
}

void vga_fb_snap_window(int zone) {
    int mc = term_max_cols();
    int mr = term_max_rows();
    int hw = mc / 2;
    int hh = mr / 2;
    int ow = mc - hw;   /* right/bottom half (larger when odd) */
    int oh = mr - hh;
    term_fullscreen = 0;
    switch (zone) {
    case TILING_LEFT:        term_sz_cols = hw; term_sz_rows = mr; term_x = 0; term_y = 0; break;
    case TILING_RIGHT:       term_sz_cols = ow; term_sz_rows = mr; term_x = hw; term_y = 0; break;
    case TILING_TOP:         term_sz_cols = mc; term_sz_rows = hh; term_x = 0; term_y = 0; break;
    case TILING_BOTTOM:      term_sz_cols = mc; term_sz_rows = oh; term_x = 0; term_y = hh; break;
    case TILING_TOP_LEFT:    term_sz_cols = hw; term_sz_rows = hh; term_x = 0; term_y = 0; break;
    case TILING_TOP_RIGHT:   term_sz_cols = ow; term_sz_rows = hh; term_x = hw; term_y = 0; break;
    case TILING_BOTTOM_LEFT: term_sz_cols = hw; term_sz_rows = oh; term_x = 0; term_y = hh; break;
    case TILING_BOTTOM_RIGHT: term_sz_cols = ow; term_sz_rows = oh; term_x = hw; term_y = hh; break;
    default: return;
    }
    term_finish_layout();
}

void vga_fb_resize(int dcols, int drows) {
    int mc = term_max_cols();
    int mr = term_max_rows();
    int ncol = term_sz_cols + dcols;
    int nrow = term_sz_rows + drows;
    if (ncol < 1) ncol = 1;
    if (nrow < 1) nrow = 1;
    if (ncol > mc) ncol = mc;
    if (nrow > mr) nrow = mr;
    if (ncol == term_sz_cols && nrow == term_sz_rows && !term_fullscreen) return;
    term_fullscreen = 0;
    term_sz_cols = ncol;
    term_sz_rows = nrow;
    term_finish_layout();
}

/* Alt+0: restore the default window position and size (not just position). */
void vga_fb_reset_default(void) {
    term_fullscreen = 0;
    term_sz_cols = WIN_DEF_COLS;
    term_sz_rows = WIN_DEF_ROWS;
    term_x = WIN_DEF_X;
    term_y = WIN_DEF_Y;
    term_finish_layout();
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
    static unsigned tb_prev_buttons;
    int mx, my;
    int win_w = term_px_w + SCROLLBAR_W;

    if (!mouse_state.present) return;

    /* Refresh the taskbar clock and react to volume clicks on the rising edge
     * of the left button, before any window drag/scrollbar handling. */
    taskbar_tick();
    if ((mouse_state.buttons & 1) && !(tb_prev_buttons & 1))
        taskbar_handle_click(mouse_state.x, mouse_state.y);
    tb_prev_buttons = (unsigned)(mouse_state.buttons & 1);

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
        if (cursor_over(term_px_x, term_content_y(), term_px_w, term_px_h))
            cursor_visible = 0;
    }

    mx = mouse_state.x;
    my = mouse_state.y;

    /* Title-bar drag: grab the window on a left press over the title bar and
     * move it while the button is held. Redrawing the desktop resets the
     * cursor, so the cursor is re-saved afterwards. */
    if (!term_fullscreen) {
        /* The grab zone covers the title bar and a little below, so the drag
         * triggers whether the user aims the arrow tip or the sprite body at
         * the title bar (the tip is offset CURSOR_TIP_Y below the sprite's
         * top-left corner). */
        int in_title = (my >= term_px_y && my < term_content_y() + CURSOR_TIP_Y &&
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
            if (cursor_over(term_px_x, term_content_y(), term_px_w, term_px_h))
                cursor_visible = 0;
        }
    }

    /* Clamp the mouse so the cursor sprite's top-left corner (offset up-left
     * of the tip) stays inside the framebuffer and never reads out of bounds. */
    if (mouse_state.x < CURSOR_TIP_X) mouse_state.x = CURSOR_TIP_X;
    if (mouse_state.x >= fb_width) mouse_state.x = fb_width - 1;
    if (mouse_state.y < CURSOR_TIP_Y) mouse_state.y = CURSOR_TIP_Y;
    if (mouse_state.y >= fb_height) mouse_state.y = fb_height - 1;

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
