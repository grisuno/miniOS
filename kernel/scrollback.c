/* scrollback.c - Console scrollback ring buffer.
 *
 * A ring of VGA text lines that scrolled off the top of the 25-row screen.
 * Captured lazily from vga_scroll(); viewed with PageUp/PageDown in the shell.
 *
 * Shared between the VGA driver (sb_capture_row0) and the shell's scrollback
 * view (scrollback_view/scrollback_render).
 */

#include "kernel.h"

#define SCROLLBACK_ROWS 4096

static char *sb_ring;
static int   sb_head, sb_count, sb_inited;

void sb_init(void) {
    sb_ring = (char *)kmalloc((unsigned long)SCROLLBACK_ROWS * VGA_COLS);
    sb_inited = sb_ring ? 1 : -1;
    sb_head = sb_count = 0;
}

void sb_capture_row0(void) {
    if (sb_inited == 0) sb_init();
    if (sb_inited != 1) return;
    int idx = (sb_head + sb_count) % SCROLLBACK_ROWS;
    /* Row 0 character cells: VGA_BASE[x*2] for each column. */
    for (int x = 0; x < VGA_COLS; x++)
        sb_ring[(unsigned long)idx * VGA_COLS + x] = VGA_BASE[x * 2];
    if (sb_count < SCROLLBACK_ROWS) sb_count++;
    else sb_head = (sb_head + 1) % SCROLLBACK_ROWS;
}

void sb_reset(void) {
    if (sb_ring) { sb_head = sb_count = 0; }
}

int sb_get_count(void) { return sb_count; }
int sb_get_head(void)  { return sb_head; }

char sb_get_char(int row, int col) {
    int idx = (sb_head + row) % SCROLLBACK_ROWS;
    return sb_ring[(unsigned long)idx * VGA_COLS + col];
}
