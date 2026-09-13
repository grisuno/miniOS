/** Docstring: Hardware pointer sprite layer (kernel/vga_cursor.c).
 *
 * Owns every byte of the mouse cursor: the arrow bitmap, the saved
 * background underneath it, and the last painted position. All drawing
 * goes through the framebuffer primitive API (vga_fb_pixel,
 * fb_read_packed, fb_write_packed), the same split Linux fbdev uses
 * between the generic layer and the hardware driver: this module never
 * touches raw framebuffer memory itself. Callers invalidate through
 * cursor_invalidate/cursor_note_repaint and never poke the state. */
#include "kernel.h"
#include "vga_fb.h"
#include "kernel/vga_cursor.h"

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

/** Docstring: True when the arrow bitmap sets pixel i,j. */
static int cursor_is_set(int i, int j)
{
    if (i < 0 || i >= 8 || j < 0 || j >= 8) return 0;
    return (cursor_bmp[j] & (0x80 >> i)) ? 1 : 0;
}

/** Docstring: True when an 8-neighbour of i,j belongs to the arrow. */
static int cursor_has_set_neighbour(int i, int j)
{
    int dj, di;
    for (dj = -1; dj <= 1; dj++)
        for (di = -1; di <= 1; di++) {
            if (di == 0 && dj == 0) continue;
            if (cursor_is_set(i + di, j + dj)) return 1;
        }
    return 0;
}

static void cursor_draw(int mx, int my) {
    int i, j;
    int x0 = mx - CURSOR_TIP_X;
    int y0 = my - CURSOR_TIP_Y;
    for (j = 0; j < 8; j++)
        for (i = 0; i < 8; i++) {
            if (cursor_is_set(i, j))
                vga_fb_pixel(x0 + i, y0 + j, COL_WHITE);
            else if (cursor_has_set_neighbour(i, j))
                vga_fb_pixel(x0 + i, y0 + j, COL_BLACK);
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

/** Docstring: True when the cursor sprite overlaps the given screen
 * rectangle. Used to decide whether a partial repaint overwrote the
 * cursor, in which case its saved background must be refreshed; otherwise
 * the cursor keeps its saved background and moves without leaving a
 * trail. The sprite is CURSOR_W x CURSOR_H with its top-left corner at
 * (mx, my). */
int cursor_over(int x0, int y0, int w, int h) {
    int cxl = mouse_state.x;                 /* sprite left edge */
    int cxt = mouse_state.x + CURSOR_W;      /* sprite right edge */
    int cyl = mouse_state.y;                 /* sprite top edge */
    int cyt = mouse_state.y + CURSOR_H;      /* sprite bottom edge */
    return cxl < x0 + w && cxt > x0 && cyl < y0 + h && cyt > y0;
}

/** Docstring: Paint the pointer at mx/my unconditionally: save the
 * background, draw the sprite, record the position. */
void cursor_place(int mx, int my) {
    cursor_save_bg(mx, my);
    cursor_draw(mx, my);
    cursor_old_x = mx;
    cursor_old_y = my;
    cursor_visible = 1;
}

/** Docstring: Desktop-tick pointer update: repaint only when the position
 * moved since the last paint, otherwise keep the saved background. */
void cursor_move(int mx, int my) {
    if (cursor_visible) {
        if (mx != cursor_old_x || my != cursor_old_y) {
            cursor_restore(cursor_old_x, cursor_old_y);
            cursor_save_bg(mx, my);
            cursor_draw(mx, my);
            cursor_old_x = mx;
            cursor_old_y = my;
        }
    } else {
        cursor_place(mx, my);
    }
}

/** Docstring: Restore the saved background when the pointer is up, then
 * mark it hidden. A repaint that covered the sprite calls
 * cursor_invalidate instead: the background is gone, nothing to restore. */
void cursor_erase(void) {
    if (!cursor_visible) return;
    cursor_restore(cursor_old_x, cursor_old_y);
    cursor_visible = 0;
}

/** Docstring: Mark the pointer hidden without touching the framebuffer.
 * Used after any repaint that may have covered the sprite. */
void cursor_invalidate(void) {
    cursor_visible = 0;
}

/** Docstring: Invalidate the pointer when it overlaps a repainted screen
 * rectangle, so the next move re-saves a fresh background. */
void cursor_note_repaint(int x0, int y0, int w, int h) {
    if (cursor_over(x0, y0, w, h))
        cursor_visible = 0;
}
