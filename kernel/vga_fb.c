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
#include "drivers/kbd.h"
#include "desktop_shortcuts.h"
#include "desktop_icons.h"
#include "stb_api.h"

int vga_fb_active;
unsigned long gfx_frames_composited;

/* Framebuffer geometry, sized by vga_fb_boot_config from the VBE info the
 * boot loader recorded (Mode 13h defaults when VBE is unavailable). */
int fb_width  = 320;
int fb_height = 200;
int fb_pitch  = 320;
int fb_bpp    = 8;
unsigned long fb_phys_base = 0x000A0000UL;

void vga_fb_boot_config(void) {
    volatile uint8_t *p = (volatile uint8_t *)VBE_INFO_ADDR;
    unsigned long base;
    unsigned pitch, width, height, bpp;
    int valid = p[VBE_INFO_VALID_OFF];
    if (!valid) return;
    base   = p[VBE_INFO_FBBASE_OFF + 0]
           | ((unsigned long)p[VBE_INFO_FBBASE_OFF + 1] << 8)
           | ((unsigned long)p[VBE_INFO_FBBASE_OFF + 2] << 16)
           | ((unsigned long)p[VBE_INFO_FBBASE_OFF + 3] << 24);
    pitch  = p[VBE_INFO_PITCH_OFF + 0] | (p[VBE_INFO_PITCH_OFF + 1] << 8);
    width  = p[VBE_INFO_WIDTH_OFF + 0] | (p[VBE_INFO_WIDTH_OFF + 1] << 8);
    height = p[VBE_INFO_HEIGHT_OFF + 0] | (p[VBE_INFO_HEIGHT_OFF + 1] << 8);
    bpp    = p[VBE_INFO_BPP_OFF];
    if (base == 0 || width == 0 || height == 0 || pitch == 0)
        return;
    /* Only the modes stage 2 probes are accepted; anything else keeps the
     * 8-bit defaults instead of misinterpreting the framebuffer layout. */
    if (bpp != 8 && bpp != 24 && bpp != 32)
        bpp = 8;
    fb_phys_base = base;
    fb_pitch     = pitch;
    fb_width     = width;
    fb_height    = height;
    fb_bpp       = (int)bpp;
}

int fb_bytes_per_pixel(void) {
    if (fb_bpp == 32) return 4;
    if (fb_bpp == 24) return 3;
    return 1;
}

/* ---- Mouse state (fed by sched.c IRQ12 handler) ---- */
mouse_state_t mouse_state;

/* True-color pixel layer (defined beside the palette tables below). In a
 * 32/24-bit mode every palette-index write is expanded to RGB here, so all
 * drawing code above keeps speaking indices; in 8-bit mode the helpers are
 * plain framebuffer accesses. Packed pixels are 0x00RRGGBB. */
static unsigned long fb_pack_idx(unsigned idx);
static void fb_write_packed(int x, int y, unsigned long rgb);
static unsigned long fb_read_packed(int x, int y);

/* Forward: the wallpaper cache lives with the shortcut-icon code below, but
 * the desktop painter above needs it. */
static void wallpaper_draw(void);

/* ---- Unified terminal buffer (logical lines, re-flowed at display width) ----
 *
 * The whole terminal history lives in ONE place: a ring of logical lines
 * (`lg`) holding every completed line, plus the in-progress line being typed
 * or emitted (`act`). The screen is never stored pre-wrapped; on every render
 * the visible window is reconstructed by wrapping the logical lines at the
 * current `term_cols`. Because there is a single source of truth, live screen
 * and scrollback can never disagree, and resizing the window re-wraps the
 * content instead of clipping it.
 *
 * A display row is the slice of a logical line that fits in `term_cols`
 * columns. A logical line of length L occupies max(1, ceil(L/term_cols))
 * display rows. The whole history occupies `total_rows` display rows stacked
 * oldest at top, and the viewport shows `term_rows` of them. `disp_off` is
 * how many display rows the viewport is scrolled up from the bottom (0 =
 * live). Scrolling is implicit: completed lines naturally leave the viewport
 * as new content is added, and remain reachable in the ring.
 *
 * There is deliberately no "scroll the screen up" operation. A completed
 * logical line is pushed to the ring exactly once, when it ends with '\n';
 * that eliminates the duplicated/partial scrollback entries the old two-buffer
 * scheme produced, which were the source of the pixel artifacts. */
static char lg[SB_MAX_LINES][SB_LINE_MAX];   /* completed logical lines */
static int  lg_head, lg_tail, lg_count;
static char act[SB_LINE_MAX];                /* in-progress line */
static int  act_len;
static int  disp_off;                        /* scrollback rows above the bottom */
static int  term_cursor_col = -1;            /* text cursor column (-1 = hidden) */
static int  csi_state;                       /* ANSI CSI drop: 1 after ESC, 2 in params */

/* Ring accessor: logical line at age i (0 = oldest, count-1 = newest). */
static const char *lg_get(int i) {
    return lg[(lg_head + i) % SB_MAX_LINES];
}

/* Append a completed logical line to the ring. The line is stored whole (no
 * width-dependent wrap), so it can be re-wrapped on any future resize. */
static void lg_push(const char *line, int len) {
    int k, idx;
    if (len >= SB_LINE_MAX) len = SB_LINE_MAX - 1;
    idx = lg_tail;
    for (k = 0; k < len; k++) lg[idx][k] = line[k];
    lg[idx][len] = '\0';
    lg_tail = (lg_tail + 1) % SB_MAX_LINES;
    if (lg_count < SB_MAX_LINES) lg_count++;
    else lg_head = (lg_head + 1) % SB_MAX_LINES;
}

/* Display rows a logical line of `len` characters occupies at term_cols. */
static int line_nrows(int len) {
    int w = term_cols > 0 ? term_cols : 1;
    int n = len / w + (len % w ? 1 : 0);
    if (n < 1) n = 1;   /* an empty line still shows as one row */
    return n;
}

static int act_nrows(void) { return line_nrows(act_len); }

/* Total display rows of the whole history (completed lines + active line). */
static int total_rows(void) {
    int t = 0, i;
    for (i = 0; i < lg_count; i++)
        t += line_nrows((int)kstrlen(lg_get(i)));
    return t + act_nrows();
}

/* Clamp disp_off to a legal scroll range. */
static void disp_clamp(void) {
    int tr = total_rows();
    int max = tr > term_rows ? tr - term_rows : 0;
    if (disp_off > max) disp_off = max;
    if (disp_off < 0)   disp_off = 0;
}

/* Absolute display-row index of the top of the viewport. Negative when the
 * history is shorter than the window (those rows are rendered blank). */
static int disp_top(void) {
    int tr = total_rows();
    if (tr <= term_rows) return tr - term_rows;
    return (tr - term_rows) - disp_off;
}

/* Locate the logical line contributing the display row `abs`, and set *off to
 * the character offset where that display row starts. Returns the line text,
 * or 0 when abs is beyond the history. */
static const char *line_at(int abs, int *off) {
    int acc = 0, i;
    for (i = 0; i < lg_count; i++) {
        const char *l = lg_get(i);
        int n = line_nrows((int)kstrlen(l));
        if (abs < acc + n) { *off = (abs - acc) * term_cols; return l; }
        acc += n;
    }
    if (abs < acc + act_nrows()) { *off = (abs - acc) * term_cols; return act; }
    return 0;
}

static void draw_scrollbar(void);
static void term_render(void);

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

/* The arrow's visual point is its top-left pixel: the sprite is drawn with its
 * top-left corner at (mx, my), so click hit-tests use (mx, my) directly and a
 * click lands where the user aims the arrow tip. */
#define CURSOR_TIP_X 0
#define CURSOR_TIP_Y 0
#define CURSOR_W 8
#define CURSOR_H 8

static unsigned long cursor_save[8][8];
static int cursor_old_x, cursor_old_y;
static int cursor_visible;

/* The cursor is drawn with its top-left corner at (mx, my), so the sprite
 * spans down-right of the pointer. The caller clamps mx/my so the position
 * stays inside the framebuffer; pixels outside the screen are clipped by the
 * packed helpers, and the snapshot holds packed RGB so a restore is exact in
 * any color depth. */
static void cursor_save_bg(int mx, int my) {
    int i, j;
    int x0 = mx - CURSOR_TIP_X;
    int y0 = my - CURSOR_TIP_Y;
    for (j = 0; j < 8; j++)
        for (i = 0; i < 8; i++)
            cursor_save[j][i] = fb_read_packed(x0 + i, y0 + j);
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
            fb_write_packed(x0 + i, y0 + j, cursor_save[j][i]);
}

/* True when the cursor sprite overlaps the given screen rectangle. Used to
 * decide whether a partial repaint (taskbar, terminal content) overwrote the
 * cursor, in which case its saved background must be refreshed; otherwise the
 * cursor keeps its saved background and moves without leaving a trail. The
 * sprite is CURSOR_W x CURSOR_H with its top-left corner at (mx, my). */
static int cursor_over(int x0, int y0, int w, int h) {
    int cxl = mouse_state.x;                 /* sprite left edge */
    int cxt = mouse_state.x + CURSOR_W;      /* sprite right edge */
    int cyl = mouse_state.y;                 /* sprite top edge */
    int cyt = mouse_state.y + CURSOR_H;      /* sprite bottom edge */
    return cxl < x0 + w && cxt > x0 && cyl < y0 + h && cyt > y0;
}

/* ---- Graphics-mode pointer (compositor contract) ----
 *
 * While a ring-3 graphics program owns the display (SYS_VGA_MODE 1) the
 * kernel never runs the idle loop that drives vga_fb_mouse_tick, so the
 * desktop pointer would simply vanish as soon as e.g. the Nuklear node
 * editor composites its first frame. The frame syscalls take its place:
 * the kernel restores the previous frame's pointer before a composite and
 * redraws it afterwards, using the same save/restore machinery as the
 * desktop path, so the pointer stays live over the whole display without
 * ever leaving a trail. */
static int vga_fb_gfx_mode;

/* Geometry of the last composited graphics window (DOOM or Nuklear). The WM
 * uses it to hit-test the title-bar window controls while a graphics program
 * owns the display. */
static int gfx_win_x, gfx_win_y, gfx_win_w;

void vga_fb_set_gfx_mode(int on) {
    vga_fb_gfx_mode = on;
    if (!on) cursor_visible = 0;
    /* A new graphics program claims the display: drop any title the previous
     * one set (via SYS_GFX_SET_TITLE), so the next DOOM window is not
     * mis-labelled with the last program's name. */
    if (on) gfx_win_title = "DOOM";
}

/* Restore the last composite's pointer before the new frame covers it. Only
 * meaningful in graphics mode; the desktop path (vga_fb_mouse_tick) manages
 * its own cursor with the same functions. */
static void vga_fb_gfx_cursor_erase(void) {
    if (!vga_fb_gfx_mode || !cursor_visible) return;
    cursor_restore(cursor_old_x, cursor_old_y);
    cursor_visible = 0;
}

/* Clamp the mouse into the framebuffer (the idle loop that normally clamps
 * never runs in graphics mode) and draw the pointer at the current position. */
static void vga_fb_gfx_cursor_draw(void) {
    int mx, my;
    if (!vga_fb_gfx_mode) return;
    mx = mouse_state.x;
    my = mouse_state.y;
    if (mx < 0) mx = 0;
    if (mx >= fb_width)    mx = fb_width - 1;
    if (my < 0) my = 0;
    if (my >= fb_height)   my = fb_height - 1;
    mouse_state.x = mx;
    mouse_state.y = my;
    cursor_save_bg(mx, my);
    cursor_draw(mx, my);
    cursor_old_x = mx;
    cursor_old_y = my;
    cursor_visible = 1;
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
#define WIN_DEF_COLS  74
#define WIN_DEF_ROWS  28
#define WIN_DEF_X     4
#define WIN_DEF_Y     3

/* ---- Terminal state ---- */
int term_x = WIN_DEF_X, term_y = WIN_DEF_Y;
int term_cols, term_rows;
static int term_sz_cols = WIN_DEF_COLS;   /* persisted size across redraws */
static int term_sz_rows = WIN_DEF_ROWS;
static int term_fullscreen;
static int term_minimized;
static int term_px_x, term_px_y, term_px_w, term_px_h;

/* Close request for a graphics window. A ring-3 program owns the display and
 * only the kernel can end it: the WM's close button sets this flag and the
 * syscall dispatcher acts on it at the program's next syscall, so the exit
 * runs on the child's own stack, never from the ISR. */
static volatile int wm_close_request;

/* There is no pre-wrapped screen buffer: the visible window is reconstructed
 * from the logical line history on every render (see term_render), so a resize
 * re-wraps the content instead of clipping it. */

#define FB_OFFSET(x,y) ((unsigned)(y) * fb_pitch + (unsigned)(x))

/* The text area starts one FONT_H below the window's top-left corner, which
 * is occupied by the title bar. */
static int term_content_y(void) { return term_px_y + FONT_H; }

/* ---- Palette ---- */
/* Icon palette (16 colours at VGA DAC indices 240-255). File scope so the
 * DAC programming below and the runtime PNG-to-palette mapper share one
 * table instead of drifting apart. */
static const uint8_t icon_pal[][3] = {
    {  0,  0,  0},   /* 0  transparent/black   */
    { 70,130,180},   /* 1  steel blue           */
    {220, 80, 60},   /* 2  tomato               */
    { 60,179,113},   /* 3  sea green            */
    {255,255,255},   /* 4  white                */
    { 40, 40, 50},   /* 5  dark bg              */
    {100,100,110},   /* 6  gray                 */
    {180,180,190},   /* 7  light gray           */
    {255,215,  0},   /* 8  gold                 */
    {  0,160,  0},   /* 9  green                */
    {147,112,219},   /* A  medium purple        */
    {255,165,  0},   /* B  orange               */
    {100,149,237},   /* C  cornflower           */
    { 15, 15, 50},   /* D  navy (desktop bg)    */
    { 60, 90,140},   /* E  title blue           */
    {  0,220,  0},   /* F  terminal green       */
};

/* Wallpaper colour cube: 6 levels per channel (websafe) at DAC 16-231.
 * The desktop UI owns 0-14 and the icons 240-255; the 216 cube slots give
 * a photographic wallpaper without touching either range. In true color the
 * cached wallpaper indices resolve through the same cube levels to full RGB
 * instead of the quantized DAC entries. */
static const uint8_t wall_levels[6] = { 0, 51, 102, 153, 204, 255 };

/* Desktop palette (DAC indices 0-14). File scope so the DAC programming, the
 * true-color packer and the icon mapper share one table. */
static const uint8_t desk_pal[][3] = {
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

/* Graphics program palette (768 bytes, set through SYS_PALETTE). In 8-bit
 * mode it owns the whole DAC; in true color it is only the lookup table the
 * DOOM/Nuklear blits expand their indexed back-buffers through, so a game
 * can no longer recolor the desktop behind its window. A gray ramp until the
 * first program sets it, never uninitialized pixels. */
static unsigned char gfx_pal[768];

void vga_fb_set_gfx_palette(const unsigned char *pal) {
    int i;
    for (i = 0; i < 768; i++) gfx_pal[i] = pal[i];
    if (fb_bpp != 8) return;
    outb(0x3C8, 0);
    for (i = 0; i < 768; i++) outb(0x3C9, pal[i] >> 2);
}

/* ---- True-color pixel layer ----
 * VBE true-color framebuffers store pixels natively as B,G,R(,X) bytes, so
 * the DAC is bypassed entirely. Every index the desktop draws with resolves
 * here: UI 0-14 through desk_pal, wallpaper 16-231 through the websafe cube,
 * icons 240-255 through icon_pal. Indices with no owner (15, 232-239) are
 * black. Graphics back-buffers never pass through this table; they expand
 * through gfx_pal at blit time. */
static unsigned long fb_pack_idx(unsigned idx) {
    unsigned r, g, b;
    if (idx < 15) {
        r = desk_pal[idx][0]; g = desk_pal[idx][1]; b = desk_pal[idx][2];
    } else if (idx >= WALL_PAL_BASE && idx < WALL_PAL_BASE + WALL_PAL_SIZE) {
        unsigned c = idx - WALL_PAL_BASE;
        r = wall_levels[c / 36]; g = wall_levels[(c / 6) % 6]; b = wall_levels[c % 6];
    } else if (idx >= ICON_PAL_BASE && idx < ICON_PAL_BASE + ICON_PAL_SIZE) {
        unsigned c = idx - ICON_PAL_BASE;
        r = icon_pal[c][0]; g = icon_pal[c][1]; b = icon_pal[c][2];
    } else {
        r = 0; g = 0; b = 0;
    }
    return (r << 16) | (g << 8) | b;
}

static void fb_write_packed(int x, int y, unsigned long rgb) {
    volatile uint8_t *p;
    if (x < 0 || x >= fb_width || y < 0 || y >= fb_height) return;
    p = FB_ADDR + (unsigned)y * (unsigned)fb_pitch;
    if (fb_bpp == 32) {
        p += (unsigned)x * 4;
        p[0] = (uint8_t)(rgb & 0xFF);
        p[1] = (uint8_t)((rgb >> 8) & 0xFF);
        p[2] = (uint8_t)((rgb >> 16) & 0xFF);
        p[3] = 0;
    } else if (fb_bpp == 24) {
        p += (unsigned)x * 3;
        p[0] = (uint8_t)(rgb & 0xFF);
        p[1] = (uint8_t)((rgb >> 8) & 0xFF);
        p[2] = (uint8_t)((rgb >> 16) & 0xFF);
    } else {
        p[x] = (uint8_t)(rgb & 0xFF);
    }
}

static unsigned long fb_read_packed(int x, int y) {
    volatile uint8_t *p;
    if (x < 0 || x >= fb_width || y < 0 || y >= fb_height) return 0;
    p = FB_ADDR + (unsigned)y * (unsigned)fb_pitch;
    if (fb_bpp == 32) {
        p += (unsigned)x * 4;
        return (unsigned long)p[0]
             | ((unsigned long)p[1] << 8)
             | ((unsigned long)p[2] << 16);
    }
    if (fb_bpp == 24) {
        p += (unsigned)x * 3;
        return (unsigned long)p[0]
             | ((unsigned long)p[1] << 8)
             | ((unsigned long)p[2] << 16);
    }
    /* 8-bit: return the raw palette index, not its resolved RGB. The cursor
     * save/restore round-trips through fb_write_packed, which in 8-bit writes
     * the low byte straight back into the framebuffer; resolving to RGB here
     * (and thus restoring only the blue channel as an index) is what smeared
     * the pointer into a trail. */
    return p[x];
}

unsigned long vga_fb_read_rgb(int x, int y) { return fb_read_packed(x, y); }

/* Nearest cube level for one 0-255 channel (boundaries at 25/76/127/178/229). */
static int wall_level(int v) {
    if (v <= 25) return 0;
    if (v <= 76) return 1;
    if (v <= 127) return 2;
    if (v <= 178) return 3;
    if (v <= 229) return 4;
    return 5;
}

static void vga_fb_set_palette(void) {
    int i;
    if (fb_bpp != 8) return;
    outb(0x3C8, 0);
    for (i = 0; i < 15; i++) {
        outb(0x3C9, desk_pal[i][0] >> 2);
        outb(0x3C9, desk_pal[i][1] >> 2);
        outb(0x3C9, desk_pal[i][2] >> 2);
    }
    /* Icon palette: 16 colours at VGA DAC indices 240-255. */
    {
        int i;
        outb(0x3C8, ICON_PAL_BASE);
        for (i = 0; i < ICON_PAL_SIZE; i++) {
            outb(0x3C9, icon_pal[i][0] >> 2);
            outb(0x3C9, icon_pal[i][1] >> 2);
            outb(0x3C9, icon_pal[i][2] >> 2);
        }
    }
    /* Wallpaper cube: 216 websafe colours at DAC 16-231. */
    {
        int r, g, b;
        outb(0x3C8, WALL_PAL_BASE);
        for (r = 0; r < 6; r++)
            for (g = 0; g < 6; g++)
                for (b = 0; b < 6; b++) {
                    outb(0x3C9, wall_levels[r] >> 2);
                    outb(0x3C9, wall_levels[g] >> 2);
                    outb(0x3C9, wall_levels[b] >> 2);
                }
    }
}

/* ---- Latin-1 Spanish glyphs (8x8, same style as font8x8) ----
 * The ES keyboard layout emits these single-byte Latin-1 codes; without
 * glyphs they would render as blanks. Approximations of the base letter
 * with the Spanish diacritic, recognizable at 8x8. */
static const uint8_t glyph_inv_excl[8] = {0x18,0x00,0x18,0x18,0x18,0x18,0x18,0x00};
static const uint8_t glyph_diaeresis[8]= {0x66,0x66,0x00,0x00,0x00,0x00,0x00,0x00};
static const uint8_t glyph_ord_fem[8]  = {0x78,0x0C,0x7C,0xCC,0x7C,0x00,0x00,0x00};
static const uint8_t glyph_notsign[8]  = {0x7C,0x04,0x04,0x04,0x00,0x00,0x00,0x00};static const uint8_t glyph_acute[8]    = {0x0C,0x0C,0x18,0x00,0x00,0x00,0x00,0x00};
static const uint8_t glyph_middot[8]   = {0x00,0x00,0x00,0x18,0x18,0x00,0x00,0x00};
static const uint8_t glyph_ord_masc[8] = {0x38,0x44,0x44,0x38,0x00,0x00,0x00,0x00};
static const uint8_t glyph_inv_quest[8]= {0x00,0x18,0x00,0x18,0x18,0x30,0x66,0x3C};
static const uint8_t glyph_Ccedil[8]   = {0x3C,0x66,0xC0,0xC0,0xC0,0x66,0x3C,0x30};
static const uint8_t glyph_Ntilde[8]   = {0x76,0xDC,0xE6,0xF6,0xDE,0xCE,0xC6,0x00};
static const uint8_t glyph_ccedil[8]   = {0x00,0x00,0x7C,0xC6,0xC0,0xC6,0x7C,0x30};
static const uint8_t glyph_ntilde[8]   = {0x76,0xDC,0xDC,0x66,0x66,0x66,0x66,0x00};

/* Resolve one byte to its 8-row glyph: ASCII through font8x8, Spanish
 * Latin-1 through the table above, anything else (including control codes)
 * as a blank. Takes an unsigned value so Latin-1 bytes above 127 survive a
 * signed-char parameter. */
static const uint8_t *fb_glyph(unsigned char c) {
    if (c < 32) return font8x8[0];
    if (c <= 127) return font8x8[c - 32];
    switch (c) {
    case 0xA1: return glyph_inv_excl;
    case 0xA8: return glyph_diaeresis;
    case 0xAA: return glyph_ord_fem;
    case 0xAC: return glyph_notsign;
    case 0xB4: return glyph_acute;
    case 0xB7: return glyph_middot;
    case 0xBA: return glyph_ord_masc;
    case 0xBF: return glyph_inv_quest;
    case 0xC7: return glyph_Ccedil;
    case 0xD1: return glyph_Ntilde;
    case 0xE7: return glyph_ccedil;
    case 0xF1: return glyph_ntilde;
    default: return font8x8[0];
    }
}

/* ---- Drawing primitives ---- */
void vga_fb_pixel(int x, int y, uint8_t color) {
    if (fb_bpp == 8) {
        if (x >= 0 && x < fb_width && y >= 0 && y < fb_height)
            FB_ADDR[(unsigned)y * (unsigned)fb_pitch + (unsigned)x] = color;
        return;
    }
    fb_write_packed(x, y, fb_pack_idx(color));
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
    glyph = fb_glyph((unsigned char)c);
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
        unsigned char c = (unsigned char)s[k];
        glyph = fb_glyph(c);
        for (j = 0; j < FONT_H; j++) {
            bits = glyph[j];
            for (i = 0; i < FONT_W; i++)
                vga_fb_pixel(px + k * FONT_W + i, py + j,
                             (bits & (0x80 >> i)) ? fg : bg);
        }
    }
}

/* ---- Window controls ----
 * Three glyph buttons at the right end of a window's title bar: minimize (_),
 * maximize (square) and close (X). They are shared by the terminal window and
 * the composited graphics windows (DOOM/Nuklear), so hit-testing must work on
 * any titled window. Each button is FONT_W x FONT_H, separated by WM_BTN_PAD. */
static int wm_buttons_x0(int win_x, int win_w) {
    return win_x + win_w - 3 * (WM_BTN_W + WM_BTN_PAD);
}

/* Draw the three window-control glyphs at (px,py), the title bar's top-left. */
static void wm_draw_buttons(int px, int py, int win_w, uint8_t fg, uint8_t bg) {
    int bx = wm_buttons_x0(px, win_w);
    int by = py;
    int i;
    vga_fb_rect(bx, by, 3 * WM_BTN_W + 2 * WM_BTN_PAD, WM_BTN_H, bg);
    /* minimize: a short bar across the lower half. */
    vga_fb_rect(bx + 1, by + WM_BTN_H - 3, WM_BTN_W - 2, 1, fg);
    bx += WM_BTN_W + WM_BTN_PAD;
    /* maximize: an open square outline. */
    for (i = 1; i < WM_BTN_W - 1; i++) {
        vga_fb_pixel(bx + i, by + 1, fg);
        vga_fb_pixel(bx + i, by + WM_BTN_H - 2, fg);
    }
    for (i = 1; i < WM_BTN_H - 1; i++) {
        vga_fb_pixel(bx + 1, by + i, fg);
        vga_fb_pixel(bx + WM_BTN_W - 2, by + i, fg);
    }
    bx += WM_BTN_W + WM_BTN_PAD;
    /* close: two crossing diagonals. */
    for (i = 1; i < WM_BTN_W - 1; i++) {
        vga_fb_pixel(bx + i, by + i, fg);
        vga_fb_pixel(bx + WM_BTN_W - 1 - i, by + i, fg);
    }
}

/* Return which window-control button is under (mx,my), or 0 for none. */
static int wm_buttons_hit(int mx, int my, int win_x, int win_y, int win_w) {
    int x0 = wm_buttons_x0(win_x, win_w);
    int rel;
    if (my < win_y || my >= win_y + WM_BTN_H) return 0;
    if (mx < x0 || mx >= win_x + win_w) return 0;
    rel = mx - x0;
    if (rel < WM_BTN_W) return WM_BTN_MIN;
    if (rel < WM_BTN_W + WM_BTN_PAD + WM_BTN_W) return WM_BTN_MAX;
    if (rel < WM_BTN_W + WM_BTN_PAD + WM_BTN_W + WM_BTN_PAD + WM_BTN_W)
        return WM_BTN_CLOSE;
    return 0;
}

/* Close request bridge: the syscall dispatcher polls this so a graphics
 * program's next syscall exits it on the child's own stack. */
int wm_close_pending(void) { return wm_close_request; }
void wm_clear_close(void) { wm_close_request = 0; }
int wm_gfx_mode_active(void) { return vga_fb_gfx_mode; }

/* Hit-test and dispatch a click on a titled window's controls. The active
 * window is the graphics window when one is composited, else the terminal.
 * Returns 1 when the click was consumed by a window control. */
static int wm_button_click(int mx, int my) {
    int win_x, win_y, win_w;
    int btn;
    if (vga_fb_gfx_mode) {
        win_x = gfx_win_x;
        win_y = gfx_win_y;
        win_w = gfx_win_w;
    } else {
        if (term_minimized) return 0;
        win_x = term_px_x;
        win_y = term_px_y;
        win_w = term_px_w + SCROLLBAR_W;
    }
    btn = wm_buttons_hit(mx, my, win_x, win_y, win_w);
    switch (btn) {
    case WM_BTN_MIN:
        if (vga_fb_gfx_mode) {
            wm_close_request = 1;
        } else {
            vga_fb_toggle_minimize();
        }
        return 1;
    case WM_BTN_MAX:
        if (vga_fb_gfx_mode) {
            /* Graphics windows are already sized to the display; no-op. */
        } else {
            vga_fb_toggle_fullscreen();
        }
        return 1;
    case WM_BTN_CLOSE:
        vga_fb_close_active();
        return 1;
    default:
        return 0;
    }
}

/* Composite the graphics back-buffer (e.g. DOOM's 320x200 frame) onto the
 * desktop in a titled window at native resolution, leaving the shell window
 * and desktop visible around it. Centered on the screen because the graphics
 * program owns the display while it runs (no mouse), so the window cannot be
 * dragged into a better spot. */
const char *gfx_win_title = "DOOM";

/* Fast true-color blit of an indexed back-buffer row block. Bounds are
 * clipped once here; the inner loop expands through gfx_pal inline with row
 * pointers, no per-pixel call or check. px holds 0x00RRGGBB so a 32-bit LE
 * store lands as B,G,R,0, the VBE byte order. Deliberately no cached u32
 * table: the kernel image must end below USER_LOAD_BASE (mm guard) and it
 * fits with ~1 KB to spare, so this file spends zero new .bss. */
static void blit_indexed_truecolor(const volatile uint8_t *bb, int bb_w,
                                   int bb_h, int dst_x, int dst_y) {
    volatile uint8_t *fb = (volatile uint8_t *)FB_ADDR;
    unsigned pitch = (unsigned)fb_pitch;
    int width = fb_width, height = fb_height;
    int is32 = (fb_bpp == 32);
    int r;
    for (r = 0; r < bb_h; r++) {
        int y = dst_y + r;
        const volatile uint8_t *src;
        volatile uint8_t *row;
        int x0, x1, b, w;
        if (y < 0 || y >= height) continue;
        x0 = dst_x < 0 ? -dst_x : 0;
        x1 = dst_x + bb_w > width ? width - dst_x : bb_w;
        if (x0 >= x1) continue;
        src = bb + r * bb_w + x0;
        row = fb + (unsigned)y * pitch + (unsigned)(dst_x + x0) * (is32 ? 4u : 3u);
        w = x1 - x0;
        if (is32) {
            for (b = 0; b < w; b++) {
                unsigned o = (unsigned)src[b] * 3u;
                unsigned px = ((unsigned)gfx_pal[o] << 16)
                            | ((unsigned)gfx_pal[o + 1] << 8)
                            |  (unsigned)gfx_pal[o + 2];
                *(volatile unsigned *)row = px;
                row += 4;
            }
        } else {
            for (b = 0; b < w; b++) {
                unsigned o = (unsigned)src[b] * 3u;
                row[0] = gfx_pal[o + 2];
                row[1] = gfx_pal[o + 1];
                row[2] = gfx_pal[o];
                row += 3;
            }
        }
    }
}

void vga_fb_blit_gfx_window(void) {
    const volatile uint8_t *bb = (const volatile uint8_t *)DOOM_BACKBUF_ADDR;
    int dst_x = (fb_width - DOOM_W) / 2;
    int dst_y = (fb_height - DOOM_H) / 2;
    int r, b;
    gfx_frames_composited++;
    vga_fb_gfx_cursor_erase();
    if (dst_x < 0) dst_x = 0;
    if (dst_y < 0) dst_y = 0;
    gfx_win_x = dst_x;
    gfx_win_y = dst_y;
    gfx_win_w = DOOM_W + SCROLLBAR_W;
    vga_fb_rect(dst_x, dst_y, DOOM_W + SCROLLBAR_W, FONT_H, COL_TITLEBAR);
    text_px(dst_x + 4, dst_y, gfx_win_title, COL_TITLE_TXT, COL_TITLEBAR);
    wm_draw_buttons(dst_x, dst_y, DOOM_W + SCROLLBAR_W,
                    COL_TITLE_TXT, COL_TITLEBAR);
    /* Indexed back-buffer pixels expand through the program's own palette,
     * so the game keeps its colors without recoloring the desktop. */
    if (fb_bpp == 8) {
        for (r = 0; r < DOOM_H; r++) {
            volatile uint8_t *dst = &FB_ADDR[(unsigned)(dst_y + FONT_H + r) * (unsigned)fb_pitch + (unsigned)dst_x];
            const volatile uint8_t *src = bb + r * DOOM_W;
            for (b = 0; b < DOOM_W; b++)
                dst[b] = src[b];
        }
    } else {
        blit_indexed_truecolor(bb, DOOM_W, DOOM_H, dst_x, dst_y + FONT_H);
    }
    vga_fb_gfx_cursor_draw();
}

void vga_fb_clear(void) {
    kmemset((void *)FB_ADDR, 0, (unsigned long)fb_pitch * (unsigned long)fb_height);
}

/* Window origin of the last Nuklear composite. SYS_NK_FRAME reports this so a
 * ring-3 Nuklear app can translate desktop mouse coordinates into the local
 * coordinates its UI expects (the app renders into the back-buffer, whose
 * top-left lands at this desktop origin). */
int nk_win_x, nk_win_y;

/* Composite the Nuklear UI back-buffer onto the desktop as a titled window,
 * mirroring the DOOM window: the back-buffer is a kernel-heap region mapped
 * into the user window that the ring-3 app renders into, and the kernel blits
 * it to the framebuffer on SYS_NK_FRAME. The window is centered and the shell
 * window stays visible around it. */
void vga_fb_blit_nk_window(void) {
    const volatile uint8_t *bb = (const volatile uint8_t *)NK_BACKBUF_ADDR;
    int dst_x = (fb_width - NK_W) / 2;
    int dst_y = (fb_height - NK_H) / 2;
    int r, b;
    gfx_frames_composited++;
    vga_fb_gfx_cursor_erase();
    if (dst_x < 0) dst_x = 0;
    if (dst_y < 0) dst_y = 0;
    nk_win_x = dst_x;
    nk_win_y = dst_y;
    gfx_win_x = dst_x;
    gfx_win_y = dst_y;
    gfx_win_w = NK_W + SCROLLBAR_W;
    vga_fb_rect(dst_x, dst_y, NK_W + SCROLLBAR_W, FONT_H, COL_TITLEBAR);
    text_px(dst_x + 4, dst_y, "Nuklear", COL_TITLE_TXT, COL_TITLEBAR);
    wm_draw_buttons(dst_x, dst_y, NK_W + SCROLLBAR_W,
                    COL_TITLE_TXT, COL_TITLEBAR);
    if (fb_bpp == 8) {
        for (r = 0; r < NK_H; r++) {
            volatile uint8_t *dst = &FB_ADDR[(unsigned)(dst_y + FONT_H + r) * (unsigned)fb_pitch + (unsigned)dst_x];
            const volatile uint8_t *src = bb + r * NK_W;
            for (b = 0; b < NK_W; b++)
                dst[b] = src[b];
        }
    } else {
        blit_indexed_truecolor(bb, NK_W, NK_H, dst_x, dst_y + FONT_H);
    }
    vga_fb_gfx_cursor_draw();
}

/* ---- Layout ---- */
static int term_max_cols(void);
static int term_max_rows(void);
static void term_render(void);

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
    int w = term_px_w + SCROLLBAR_W;
    int tw = 3 * (WM_BTN_W + WM_BTN_PAD) + 8;   /* room for the controls */
    vga_fb_rect(term_px_x, term_px_y, w, FONT_H, COL_TITLEBAR);
    if (w > tw)
        text_px(term_px_x + 4, term_px_y, title, COL_TITLE_TXT, COL_TITLEBAR);
    wm_draw_buttons(term_px_x, term_px_y, w, COL_TITLE_TXT, COL_TITLEBAR);
}

/* ---- Taskbar (clock + speaker volume + keyboard layout) ----
 * The bottom strip is the desktop's status bar: a live CMOS clock on the
 * right, a speaker icon with -/+ volume buttons, and an "EN"/"ES" keyboard
 * layout widget left of the speaker. The widgets and the shell
 * `date`/`vol`/`kbd` builtins share the same
 * rtc_read_tod/pcspk_get_volume/kbd_get_layout state, so the framebuffer and
 * the serial console can never disagree. */
static int tb_spk_x, tb_minus_x, tb_plus_x, tb_vol_x, tb_clock_x, tb_kbd_x;
static int tb_restore_x, tb_restore_w;

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
    x -= TASKBAR_PAD;
    x -= TASKBAR_KBD_W;             tb_kbd_x = x;
    /* Restore button on the far left: "[]" when a window is minimized. */
    tb_restore_w = 2 * FONT_W;
    tb_restore_x = TASKBAR_PAD;
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
    if (term_minimized)
        text_px(tb_restore_x, y, "[]", COL_HIGHLIGHT, COL_TASKBAR);
    draw_speaker_icon(tb_spk_x, y, vol ? COL_TASKBAR_TXT : COL_HIGHLIGHT);
    text_px(tb_minus_x, y, "-", COL_TASKBAR_TXT, COL_TASKBAR);
    text_px(tb_plus_x, y, "+", COL_TASKBAR_TXT, COL_TASKBAR);
    ksprintf(buf, "%u%%", vol);
    text_px(tb_vol_x, y, buf, COL_TASKBAR_TXT, COL_TASKBAR);
    text_px(tb_kbd_x, y,
            kbd_get_layout() == KBD_LAYOUT_ES ? "ES" : "EN",
            COL_TASKBAR_TXT, COL_TASKBAR);
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

/* Click handling for the keyboard widget, the speaker icon and -/+
 * buttons, plus the restore button that reappears while the terminal window
 * is minimized. A click on "EN" switches to Spanish and a click on "ES"
 * switches back to English. */
static void taskbar_handle_click(int mx, int my) {
    unsigned v;
    static int spk_saved_valid;
    static unsigned spk_saved_vol;
    int y = fb_height - FONT_H;
    if (my < y || my >= y + FONT_H) return;
    if (term_minimized &&
        mx >= tb_restore_x && mx < tb_restore_x + tb_restore_w) {
        vga_fb_toggle_minimize();
        return;
    }
    if (mx >= tb_kbd_x && mx < tb_kbd_x + TASKBAR_KBD_W) {
        kbd_toggle_layout();
        taskbar_render();
        if (cursor_over(0, y, fb_width, FONT_H))
            cursor_visible = 0;
        return;
    }
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
    int total = total_rows();
    int visible = term_rows;
    int thumb_h, thumb_y;

    /* Track background */
    vga_fb_rect(sx, sy, SCROLLBAR_W, sh, COL_SCROLLBAR);

    /* Compute thumb size and position */
    if (total <= visible) {
        thumb_h = sh;
        thumb_y = sy;
    } else {
        int max_off = total - visible;
        thumb_h = (visible * sh) / total;
        if (thumb_h < 4) thumb_h = 4;
        thumb_y = sy + sh - thumb_h
                  - (disp_off * (sh - thumb_h)) / max_off;
    }
    /* Clamp */
    if (thumb_y < sy) thumb_y = sy;
    if (thumb_y + thumb_h > sy + sh) thumb_y = sy + sh - thumb_h;

    /* Thumb (with 1px inset on each side) */
    vga_fb_rect(sx + SCROLLBAR_PAD, thumb_y + SCROLLBAR_PAD,
                SCROLLBAR_W - 2 * SCROLLBAR_PAD,
                thumb_h - 2 * SCROLLBAR_PAD, COL_SCROLL_THUMB);
}

/* Blank one viewport row: every cell is repainted with the terminal
 * background. vga_fb_str with an empty string would draw nothing and leave
 * whatever pixels the previous content left behind, so blanking is explicit. */
static void render_blank_row(int vrow) {
    int c;
    for (c = 0; c < term_cols; c++)
        vga_fb_char(c, vrow, ' ', COL_TERM_TXT, COL_TERMINAL);
}

/* Render one display row at viewport row `vrow` for the absolute display row
 * `abs`. Rows outside the history (above the oldest line, or below the active
 * line) are blanked. When this is a row of the active line and a text cursor
 * is shown, the cursor cell is drawn inverted (COL_TERM_CUR background). */
static void render_row(int vrow, int abs) {
    const char *line;
    int off, len, c, src;
    int active_start = total_rows() - act_nrows();
    int is_active = (abs >= active_start);
    if (abs < 0) { render_blank_row(vrow); return; }
    line = line_at(abs, &off);
    if (!line) { render_blank_row(vrow); return; }
    len = (int)kstrlen(line);
    for (c = 0; c < term_cols; c++) {
        src = off + c;
        if (is_active && term_cursor_col >= 0) {
            int cl = term_cursor_col % term_cols;
            int crow = (term_cursor_col / term_cols);
            if (abs == active_start + crow && c == cl) {
                vga_fb_char(c, vrow, src < len ? line[src] : ' ',
                            COL_TERMINAL, COL_TERM_CUR);
                continue;
            }
        }
        vga_fb_char(c, vrow, src < len ? line[src] : ' ',
                    COL_TERM_TXT, COL_TERMINAL);
    }
}

/* Full repaint of the terminal window from the logical history, honouring the
 * current scroll position. Used on desktop redraws, resize, wrap, scroll and
 * any structural change. */
static void term_render(void) {
    int top = disp_top();
    int v;
    vga_fb_rect(term_px_x, term_content_y(), term_px_w, term_px_h, COL_TERMINAL);
    for (v = 0; v < term_rows; v++)
        render_row(v, top + v);
    draw_scrollbar();
}

/* Repaint only the bottom region that a live edit touches: from the active
 * line's first visible display row to the bottom of the window. Used for a
 * character append/backspace that does not change the number of display rows,
 * so typing stays cheap while remaining correct. */
static void term_render_active(void) {
    int top = disp_top();
    int abs_active = total_rows() - act_nrows();
    int v0 = abs_active - top;
    int v;
    if (v0 < 0) v0 = 0;
    if (v0 >= term_rows) v0 = term_rows - 1;
    for (v = v0; v < term_rows; v++)
        render_row(v, top + v);
    draw_scrollbar();
}

/* Draw ONE cell of the active (typed) line, honoring the text cursor. This is
 * the O(1) per-character path: bulk console output appends a char at a time,
 * and redrawing the whole active row (term_cols glyphs, via term_render_active)
 * on every char made 100000-char output take ~14 s. A single cell draw is
 * ~100x cheaper and keeps the accumulating line live. */
static void term_draw_cell(int col) {
    int top = disp_top();
    int active_start = total_rows() - act_nrows();
    int crow = col / term_cols;
    int cl = col % term_cols;
    int abs = active_start + crow;
    int vrow = abs - top;
    if (vrow < 0 || vrow >= term_rows) return;
    char ch = (col < act_len) ? act[col] : ' ';
    int is_cur = (term_cursor_col == col);
    vga_fb_char(cl, vrow, ch,
                is_cur ? COL_TERMINAL : COL_TERM_TXT,
                is_cur ? COL_TERM_CUR : COL_TERMINAL);
}

/* Emit one character into the logical terminal. The active line is the only
 * editable state: '\n' completes it into the ring, printable characters append
 * to it, '\b' shortens it. The viewport always snaps to the live bottom on
 * output, so new input/output is always visible. When the edit changes the
 * number of display rows (wrap or newline), the whole window is repainted;
 * otherwise only the active line's rows are redrawn.
 *
 * act is kept NUL-terminated at act[act_len] after every mutation: render_row
 * reads it with kstrlen, so without that terminator a shorter new line would
 * display stale bytes left over from a longer previous line (e.g. the prompt
 * would show the tail of the previous command's last output line stuck after
 * it). */
void vga_fb_putc_term(char c) {
    int rows_before = total_rows();

    /* ANSI CSI drop: ring-3 fullscreen programs (vedit) address the serial
     * console with ESC [ ... final sequences. The logical terminal is a
     * scrolling line device with no 2D cursor, so it cannot honour them;
     * swallowing them here keeps the escapes (which the serial side needs)
     * from printing as literal "[2J[H" garbage on the desktop. A bare ESC
     * outside a sequence is ignored as before. */
    if (csi_state == 1) {
        if (c == '[') { csi_state = 2; return; }
        csi_state = 0;
        if (c == '\x1b') { csi_state = 1; return; }
    } else if (csi_state == 2) {
        if ((c >= '0' && c <= '9') || c == ';' || c == '?') return;
        csi_state = 0;
        return;
    }
    if (c == '\x1b') { csi_state = 1; return; }

    if (c == '\n') {
        /* Once the ring is full every push evicts the oldest line, so the
         * total row count can stay identical while the whole viewport moved
         * up one line. Comparing row counts alone would then take the
         * active-line-only fast path and freeze the screen (only the bottom
         * line ever repainted), so an evicting push always fully renders. */
        int evicted = (lg_count == SB_MAX_LINES);
        lg_push(act, act_len);
        act_len = 0;
        act[0] = '\0';
        disp_off = 0;
        if (evicted || total_rows() != rows_before) term_render();
        else term_render_active();
        return;
    }
    if (c == '\r') { disp_off = 0; return; }
    if (c == '\b') {
        if (act_len > 0) act_len--;
        act[act_len] = '\0';
        disp_off = 0;
        if (total_rows() != rows_before) term_render();
        else term_render_active();
        return;
    }
    if (kbd_is_printable((unsigned char)c)) {
        int old_len = act_len;
        if (act_len < SB_LINE_MAX - 1) {
            act[act_len++] = c;
            act[act_len] = '\0';
        }
        disp_off = 0;
        if (total_rows() != rows_before) {
            term_render();          /* wrap changed the row count: full repaint */
        } else {
            /* Revert the previous cursor cell, then paint the new char cell. */
            if (term_cursor_col >= 0 && term_cursor_col < old_len)
                term_draw_cell(term_cursor_col);
            term_draw_cell(act_len - 1);
        }
        return;
    }
}

void vga_fb_puts_term(const char *s) {
    while (*s) vga_fb_putc_term(*s++);
}

/* Show the text cursor at character column `col` of the active line, or hide
 * it with a negative column. The cursor is a block rendered by render_row. */
void vga_fb_text_cursor(int col) {
    if (col < 0) { term_cursor_col = -1; }
    else { term_cursor_col = col; }
    disp_clamp();
    term_render();
}

/* Hide the text cursor (used when a live edit starts or the window redraws). */
void vga_fb_hide_text_cursor(void) {
    term_cursor_col = -1;
}

void vga_fb_draw_desktop(void) {
    vga_fb_set_palette();
    vga_fb_clear();
    term_recalc();
    wallpaper_draw();
    desktop_shortcuts_load();
    /* Dock sits on the wallpaper, BELOW the terminal window: drawn before the
     * terminal so a terminal that is dragged over the dock area covers it
     * (normal window-on-top-of-dock behaviour), never the reverse. */
    desktop_shortcuts_draw();
    taskbar_render();
    /* A minimized window is not drawn; the content stays in the logical ring,
     * so restoring repaints it from scratch with nothing lost. */
    if (!term_minimized) {
        draw_title();
        /* Repaint the terminal content (live or scrolled view) so the prompt
         * and any typed/echoed text survive a window move, snap, resize or
         * fullscreen toggle. Re-wrapping from the logical lines makes the
         * content adapt to the new window size instead of being clipped. */
        disp_clamp();
        term_render();
    }
    /* Any redraw changed the pixels under the cursor; force a fresh save so a
     * stale snapshot never leaves pointer trails behind. */
    cursor_visible = 0;
}

/* ---- Keyboard shortcuts ---- */
void vga_fb_toggle_fullscreen(void) {
    term_fullscreen = !term_fullscreen;
    if (term_fullscreen) term_minimized = 0;
    disp_off = 0;
    vga_fb_draw_desktop();
}

/* Minimize/restore the terminal window. The content is not touched; the
 * window is merely hidden and repainted on restore. Fullscreen and minimize
 * are mutually exclusive: entering fullscreen un-minimizes. */
void vga_fb_toggle_minimize(void) {
    term_minimized = !term_minimized;
    if (term_minimized) term_fullscreen = 0;
    disp_off = 0;
    vga_fb_draw_desktop();
}

int vga_fb_is_minimized(void) { return term_minimized; }
int vga_fb_is_fullscreen(void) { return term_fullscreen; }

/* Close the active window. For a graphics window this arms the close request
 * that the syscall dispatcher honours on the child's next syscall; for the
 * terminal window it restores the default position (the shell cannot be
 * closed). Returns 1 when a close was armed, 0 otherwise. */
int vga_fb_close_active(void) {
    if (vga_fb_gfx_mode) {
        wm_close_request = 1;
        return 1;
    }
    term_minimized = 0;
    term_fullscreen = 0;
    term_sz_cols = WIN_DEF_COLS;
    term_sz_rows = WIN_DEF_ROWS;
    term_x = WIN_DEF_X;
    term_y = WIN_DEF_Y;
    disp_off = 0;
    vga_fb_draw_desktop();
    return 0;
}

void vga_fb_move_terminal(int dx, int dy) {
    if (dx == 0 && dy == 0) {
        /* Reset to default position */
        term_fullscreen = 0;
        term_x = WIN_DEF_X; term_y = WIN_DEF_Y;
        disp_off = 0;
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
    disp_off = 0;
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
    vga_fb_draw_desktop();
}

/* ---- Wallpaper ----
 * The background is a photographic PNG (wall/wallpaper.png on the ramdisk),
 * not a solid fill. It is decoded ONCE per boot via stbi_load_file and cached
 * as cube-mapped indices in the kernel heap: draw_desktop runs on every window
 * move/resize/drag tick, and re-decoding a ~650 KB PNG there would stall the
 * pointer. A failed or missing image falls back to the solid COL_BG fill, and
 * a failed cache allocation does the same, never a partial background. */
static uint8_t *wall_cache;
static int wall_cw, wall_ch;
static int wall_tried;

static void wallpaper_ensure(void) {
    int w, h, ch, x, y;
    unsigned char *img;
    uint8_t *cache;
    if (wall_tried || fb_width <= 0 || fb_height <= 0)
        return;
    wall_tried = 1;
    img = stbi_load_file(WALLPAPER_PATH, &w, &h, &ch, 4);
    if (!img)
        return;
    if (w <= 0 || h <= 0) {
        stbi_image_free(img);
        return;
    }
    cache = kmalloc((unsigned long)fb_width * (unsigned long)fb_height);
    if (!cache) {
        stbi_image_free(img);
        return;
    }
    for (y = 0; y < fb_height; y++) {
        int sy = y * h / fb_height;
        for (x = 0; x < fb_width; x++) {
            int sx = x * w / fb_width;
            unsigned char *px = img + ((sy * w) + sx) * 4;
            int idx = (wall_level(px[0]) * 6 + wall_level(px[1])) * 6
                      + wall_level(px[2]);
            cache[y * fb_width + x] = (uint8_t)(WALL_PAL_BASE + idx);
        }
    }
    stbi_image_free(img);
    wall_cache = cache;
    wall_cw = fb_width;
    wall_ch = fb_height;
}

static void wallpaper_draw(void) {
    int x, y;
    wallpaper_ensure();
    if (!wall_cache || wall_cw != fb_width || wall_ch != fb_height) {
        vga_fb_rect(0, 0, fb_width, fb_height, COL_BG);
        return;
    }
    if (fb_bpp == 8) {
        for (y = 0; y < fb_height; y++)
            for (x = 0; x < fb_width; x++)
                FB_ADDR[(unsigned)y * (unsigned)fb_pitch + (unsigned)x] =
                    wall_cache[y * fb_width + x];
        return;
    }
    /* True color: the cached cube indices resolve to full RGB, so the
     * photographic wallpaper is no longer quantized to 216 DAC entries. */
    for (y = 0; y < fb_height; y++)
        for (x = 0; x < fb_width; x++)
            fb_write_packed(x, y, fb_pack_idx(wall_cache[y * fb_width + x]));
}

/* ---- Desktop shortcut icons ----
 * Shortcuts are defined in etc/shortcuts on the ramdisk, one per line:
 *   name|icon_path|command
 * Icons are 32x32 PNG files decoded at boot via stbi_load_file and mapped
 * to the icon palette (VGA DAC indices 240-255).  The cached palette-indexed
 * pixels are redrawn on every desktop paint; mouse clicks launch the command. */

static struct desktop_shortcut shortcuts[MAX_SHORTCUTS];
static int shortcut_count;
static int shortcuts_loaded;

/* Find a pipe-delimited field by index (0-based). */
static const char *pipe_field(const char *line, int idx, char *buf, int buflen) {
    const char *p = line;
    for (int i = 0; i < idx; i++) {
        while (*p && *p != '|') p++;
        if (*p == '|') p++;
        else return 0;
    }
    const char *start = p;
    while (*p && *p != '\n' && *p != '\r' && *p != '|') p++;
    int len = (int)(p - start);
    if (len >= buflen) len = buflen - 1;
    for (int i = 0; i < len; i++) buf[i] = start[i];
    buf[len] = '\0';
    return buf;
}

/* Nearest entry in the 16-colour icon palette (squared RGB distance,
 * integer-only: at most 3*255*255 per entry, far from overflow). */
static int icon_nearest(int r, int g, int b) {
    int best = 0, best_d = 0x7fffffff, i;
    for (i = 0; i < ICON_PAL_SIZE; i++) {
        int dr = r - icon_pal[i][0];
        int dg = g - icon_pal[i][1];
        int db = b - icon_pal[i][2];
        int d = dr * dr + dg * dg + db * db;
        if (d < best_d) {
            best_d = d;
            best = i;
        }
    }
    return best;
}

/* Embedded fallback when the shortcut's PNG is missing or undecodable. */
static const uint8_t *icon_embedded(const char *name) {
    if (kstrcmp(name, "Terminal") == 0)
        return icon_terminal;
    if (kstrcmp(name, "DOOM") == 0)
        return icon_doom;
    if (kstrcmp(name, "Nuklear") == 0)
        return icon_nuklear;
    if (kstrcmp(name, "Piano") == 0)
        return icon_piano;
    if (kstrcmp(name, "Quake 2") == 0)
        return icon_quake2;
    return 0;
}

/* Decode a shortcut's PNG to raw 32x32 RGBA pixels. Returns a heap buffer
 * that lives until reboot, or 0 on any failure (missing file, undecodable
 * image, exhausted heap); the caller then uses icon_embedded. Keeping the
 * PNG's own colors (instead of mapping to the 16-entry icon palette) is
 * what makes icons distinguishable on a true-color desktop; the 8-bit mode
 * quantizes back through icon_nearest at draw time. */
static const uint8_t *icon_decode(const char *path) {
    int w, h, ch, x, y;
    unsigned char *img;
    uint8_t *out;
    if (!path || !path[0])
        return 0;
    img = stbi_load_file(path, &w, &h, &ch, 4);
    if (!img)
        return 0;
    if (w <= 0 || h <= 0) {
        stbi_image_free(img);
        return 0;
    }
    out = kmalloc(ICON_W * ICON_H * 4);
    if (!out) {
        stbi_image_free(img);
        return 0;
    }
    for (y = 0; y < ICON_H; y++) {
        int sy = y * h / ICON_H;
        for (x = 0; x < ICON_W; x++) {
            int sx = x * w / ICON_W;
            unsigned char *px = img + ((sy * w) + sx) * 4;
            uint8_t *dst = out + ((y * ICON_W) + x) * 4;
            dst[0] = px[0]; dst[1] = px[1]; dst[2] = px[2]; dst[3] = px[3];
        }
    }
    stbi_image_free(img);
    return out;
}

/* Expand an embedded index icon (desktop_icons.h, transparent 0) to RGBA
 * through the icon palette, so fallback art follows the same draw path as
 * decoded PNGs. Returns a heap buffer or 0 when exhausted. */
static const uint8_t *icon_embedded_rgba(const uint8_t *idx) {
    uint8_t *out;
    int i;
    if (!idx) return 0;
    out = kmalloc(ICON_W * ICON_H * 4);
    if (!out) return 0;
    for (i = 0; i < ICON_W * ICON_H; i++) {
        uint8_t c = idx[i];
        uint8_t *dst = out + i * 4;
        if (c == 0) {
            dst[0] = dst[1] = dst[2] = dst[3] = 0;
        } else {
            if (c >= ICON_PAL_SIZE) c = ICON_PAL_SIZE - 1;
            dst[0] = icon_pal[c][0];
            dst[1] = icon_pal[c][1];
            dst[2] = icon_pal[c][2];
            dst[3] = 255;
        }
    }
    return out;
}

/* Width of the longest shortcut label in pixels (cached after load). Labels
 * are centred under their icon and a dock column must be wide enough for one,
 * or neighbouring labels overlap. */
static int dock_cell_w;

/* Width (px) one label occupies (FONT_W per character). */
static int dock_label_px(const struct desktop_shortcut *sc) {
    return (int)kstrlen(sc->name) * FONT_W;
}

/* Dock layout: one centred row just above the taskbar. Every shortcut owns a
 * column `dock_cell_w` wide (enough for its label), the icon is centred in the
 * column and the label centred beneath it, so long names never collide with a
 * neighbour. Recomputed on every draw/hit-test from fb_width/fb_height so a
 * resolution change never leaves stale coordinates behind. */
static void shortcuts_layout(void) {
    int dock_w, x0, y0, dock_h, cell_left, i;
    if (shortcut_count <= 0) return;
    dock_w = shortcut_count * dock_cell_w + 2 * DOCK_PAD_X;
    dock_h = ICON_H + DOCK_LABEL_GAP + ICON_LABEL_H + 2 * DOCK_PAD_Y;
    x0 = (fb_width - dock_w) / 2;
    if (x0 < 0) x0 = 0;
    y0 = fb_height - TASKBAR_H - DOCK_GAP - dock_h;
    if (y0 < 0) y0 = 0;
    cell_left = x0 + DOCK_PAD_X;
    for (i = 0; i < shortcut_count; i++) {
        shortcuts[i].x = cell_left + (dock_cell_w - ICON_W) / 2;
        shortcuts[i].y = y0 + DOCK_PAD_Y;
        cell_left += dock_cell_w;
    }
}

/* Left edge of shortcut i's column (used to centre its label under the icon). */
static int shortcut_cell_left(int i) {
    int dock_w = shortcut_count * dock_cell_w + 2 * DOCK_PAD_X;
    int x0 = (fb_width - dock_w) / 2;
    if (x0 < 0) x0 = 0;
    return x0 + DOCK_PAD_X + i * dock_cell_w;
}

void desktop_shortcuts_load(void) {
    char line[128];
    char name[SHORTCUT_NAME_LEN];
    char path[SHORTCUT_PATH_LEN];
    char cmd[SHORTCUT_CMD_LEN];

    if (shortcuts_loaded) return;
    shortcuts_loaded = 1;
    shortcut_count = 0;

    KFILE *f = kfopen("etc/shortcuts", "r");
    if (!f) return;

    while (kfgets(line, sizeof(line), f) && shortcut_count < MAX_SHORTCUTS) {
        /* Skip comments and empty lines. */
        if (line[0] == '#' || line[0] == '\n' || line[0] == '\r' || line[0] == '\0')
            continue;
        if (!pipe_field(line, 0, name, sizeof(name))) continue;
        if (!pipe_field(line, 1, path, sizeof(path))) continue;
        if (!pipe_field(line, 2, cmd, sizeof(cmd))) continue;

        struct desktop_shortcut *sc = &shortcuts[shortcut_count];
        kmemset(sc, 0, sizeof(*sc));
        /* Copy name (truncated). */
        for (int i = 0; i < SHORTCUT_NAME_LEN - 1 && name[i]; i++)
            sc->name[i] = name[i];
        /* Copy command. */
        for (int i = 0; i < SHORTCUT_CMD_LEN - 1 && cmd[i]; i++)
            sc->cmd[i] = cmd[i];
        sc->w = ICON_W;
        sc->h = ICON_H;

        /* PNG first (custom art from tools/gen_desktop_pngs.py), embedded
         * pixel data as fallback when the file is missing or undecodable. */
        sc->pixels = icon_decode(path);
        if (!sc->pixels)
            sc->pixels = icon_embedded_rgba(icon_embedded(name));

        shortcut_count++;
    }
    kfclose(f);

    /* Cache the widest cell after the names are known, then lay the dock out.
     * A label is the widest thing in a column, so the column is sized to hold
     * it (never narrower than the icon) and labels cannot overlap. */
    dock_cell_w = ICON_W;
    for (int i = 0; i < shortcut_count; i++) {
        int pw = dock_label_px(&shortcuts[i]) + 6;
        if (pw > dock_cell_w) dock_cell_w = pw;
    }
    shortcuts_layout();
}

void desktop_shortcuts_draw(void) {
    int dock_w, dock_h, x0, y0;
    shortcuts_layout();
    if (shortcut_count <= 0) return;
    /* Dock bar: dark backing for contrast over the wallpaper, Mac style. */
    dock_w = shortcut_count * dock_cell_w + 2 * DOCK_PAD_X;
    dock_h = ICON_H + DOCK_LABEL_GAP + ICON_LABEL_H + 2 * DOCK_PAD_Y;
    x0 = (fb_width - dock_w) / 2;
    if (x0 < 0) x0 = 0;
    y0 = fb_height - TASKBAR_H - DOCK_GAP - dock_h;
    if (y0 < 0) y0 = 0;
    vga_fb_rect(x0, y0, dock_w, dock_h, COL_SHADOW);
    vga_fb_rect(x0, y0, dock_w, 1, COL_BORDER);
    vga_fb_rect(x0, y0 + dock_h - 1, dock_w, 1, COL_BORDER);
    vga_fb_rect(x0, y0, 1, dock_h, COL_BORDER);
    vga_fb_rect(x0 + dock_w - 1, y0, 1, dock_h, COL_BORDER);
    for (int i = 0; i < shortcut_count; i++) {
        struct desktop_shortcut *sc = &shortcuts[i];
        int cl = shortcut_cell_left(i);
        /* Draw icon pixels (raw RGBA; alpha below 128 transparent). In
         * the 8-bit fallback the colors quantize back to the icon
         * palette, matching the old look exactly. */
        if (sc->pixels) {
            for (int py = 0; py < ICON_H; py++) {
                for (int px = 0; px < ICON_W; px++) {
                    const uint8_t *sp =
                        sc->pixels + ((py * ICON_W) + px) * 4;
                    if (sp[3] < 128) continue;
                    if (fb_bpp == 8)
                        vga_fb_pixel(sc->x + px, sc->y + py,
                                     (uint8_t)(ICON_PAL_BASE +
                                               icon_nearest(sp[0], sp[1], sp[2])));
                    else
                        fb_write_packed(sc->x + px, sc->y + py,
                                        ((unsigned long)sp[0] << 16) |
                                        ((unsigned long)sp[1] << 8) |
                                        (unsigned long)sp[2]);
                }
            }
        } else {
            /* No icon: draw a placeholder rectangle. */
            vga_fb_rect(sc->x, sc->y, ICON_W, ICON_H, COL_SHADOW);
        }
        /* Draw label centred in its own column, on the dock backing, so it
         * never runs into a neighbour's label. */
        {
            int label_w = dock_label_px(sc);
            int lx = cl + (dock_cell_w - label_w) / 2;
            text_px(lx, sc->y + ICON_H + DOCK_LABEL_GAP, sc->name,
                    COL_TASKBAR_TXT, COL_SHADOW);
        }
    }
}

const char *desktop_shortcuts_hit_test(int mx, int my) {
    shortcuts_layout();
    for (int i = 0; i < shortcut_count; i++) {
        struct desktop_shortcut *sc = &shortcuts[i];
        int cl = shortcut_cell_left(i);
        if (mx >= cl && mx < cl + dock_cell_w &&
            my >= sc->y && my < sc->y + ICON_H + ICON_LABEL_H) {
            return sc->cmd;
        }
    }
    return 0;
}

/* ---- Mouse ---- */
void vga_fb_mouse_tick(void) {
    static int dragging;
    static int grab_cx;
    static unsigned tb_prev_buttons;
    static int skip_drag;   /* suppress drag on the tick after a button click */
    int mx, my;
    int win_w = term_px_w + SCROLLBAR_W;

    if (!mouse_state.present) return;

    /* Refresh the taskbar clock and react to volume clicks on the rising edge
     * of the left button, before any window drag/scrollbar handling. */
    taskbar_tick();
    if ((mouse_state.buttons & 1) && !(tb_prev_buttons & 1)) {
        taskbar_handle_click(mouse_state.x, mouse_state.y);
        /* Window controls (minimize/maximize/close) win over a title-bar drag
         * on the same click: hit-test the active titled window first. */
        if (wm_button_click(mouse_state.x, mouse_state.y)) {
            tb_prev_buttons = (unsigned)(mouse_state.buttons & 1);
            cursor_visible = 0;
            skip_drag = 1;
            return;
        }
        /* Check desktop icon clicks. */
        const char *cmd = desktop_shortcuts_hit_test(mouse_state.x, mouse_state.y);
        if (cmd) desktop_launch(cmd);
    }
    if (!(mouse_state.buttons & 1)) skip_drag = 0;
    tb_prev_buttons = (unsigned)(mouse_state.buttons & 1);

    /* Process wheel: scroll back/forward (only when the window is visible). */
    if (mouse_state.wheel != 0 && !term_minimized) {
        int tr = total_rows();
        int max_off = tr > term_rows ? tr - term_rows : 0;
        if (mouse_state.wheel > 0)
            disp_off += 3;
        else
            disp_off -= 3;
        if (disp_off > max_off) disp_off = max_off;
        if (disp_off < 0) disp_off = 0;
        mouse_state.wheel = 0;
        term_render();
        if (cursor_over(term_px_x, term_content_y(), term_px_w, term_px_h))
            cursor_visible = 0;
    }

    mx = mouse_state.x;
    my = mouse_state.y;

    /* Title-bar drag: grab the window on a left press over the title bar and
     * move it while the button is held.  skip_drag suppresses the drag on the
     * tick(s) after a window-control button was clicked, so the button action
     * (minimize/maximize/close) fires without the window jumping. */
    if (!term_fullscreen && !term_minimized && !skip_drag) {
        /* The grab zone is exactly the title bar: the cursor tip is the
         * sprite's top-left pixel, so (mx, my) is where the user aims. */
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
    if ((mouse_state.buttons & 1) && !dragging && !term_minimized &&
        mx >= term_px_x + term_px_w && mx < term_px_x + win_w &&
        my >= term_content_y() && my < term_content_y() + term_px_h) {
        int sy = term_content_y();
        int sh = term_px_h;
        int total = total_rows();
        int visible = term_rows;
        if (total > visible && sh > 0) {
            int max_off = total - visible;
            int new_off = ((sy + sh - my) * max_off) / sh;
            if (new_off < 0) new_off = 0;
            if (new_off > max_off) new_off = max_off;
            disp_off = new_off;
            term_render();
            if (cursor_over(term_px_x, term_content_y(), term_px_w, term_px_h))
                cursor_visible = 0;
        }
    }

    /* Clamp the mouse into the framebuffer. Out-of-range sprite pixels are
     * clipped by the packed helpers, so clamping the tip is enough. */
    if (mouse_state.x < 0) mouse_state.x = 0;
    if (mouse_state.x >= fb_width) mouse_state.x = fb_width - 1;
    if (mouse_state.y < 0) mouse_state.y = 0;
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
    lg_head = lg_tail = lg_count = 0;
    act_len = 0;
    act[0] = '\0';
    disp_off = 0;
}

void vga_fb_init(void) {
    int i;
    /* Gray ramp until the first graphics program sets its palette. */
    for (i = 0; i < 256; i++) {
        gfx_pal[i * 3 + 0] = (unsigned char)i;
        gfx_pal[i * 3 + 1] = (unsigned char)i;
        gfx_pal[i * 3 + 2] = (unsigned char)i;
    }
    vga_fb_active = 1;
    vga_fb_mouse_init();
    vga_fb_draw_desktop();
}
