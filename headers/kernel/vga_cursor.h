#ifndef VGA_CURSOR_H
#define VGA_CURSOR_H

/** Docstring: vga_cursor.h -- boundary of the pointer sprite layer
 * (kernel/vga_cursor.c). Owns the arrow bitmap, the saved background and
 * the painted position; draws only through the framebuffer primitives.
 * Callers move/erase/invalidate through these ops and never poke state. */

#include "kernel.h"

/** Docstring: Pointer sprite dimensions in pixels. */
#define CURSOR_W 8
#define CURSOR_H 8

/** Docstring: True when the sprite overlaps the given screen rectangle. */
int cursor_over(int x0, int y0, int w, int h);

/** Docstring: Paint the pointer at mx/my unconditionally. */
void cursor_place(int mx, int my);

/** Docstring: Desktop-tick update: repaint only when the position moved. */
void cursor_move(int mx, int my);

/** Docstring: Restore the saved background and mark the pointer hidden. */
void cursor_erase(void);

/** Docstring: Mark the pointer hidden without touching the framebuffer. */
void cursor_invalidate(void);

/** Docstring: Invalidate when the pointer overlaps a repainted rectangle. */
void cursor_note_repaint(int x0, int y0, int w, int h);

#endif
