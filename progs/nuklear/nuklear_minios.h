#ifndef NUKLEAR_MINIOS_H
#define NUKLEAR_MINIOS_H

/* nuklear_minios.h — MiniOS platform layer for Nuklear.
 *
 * A ring-3 static ELF app (the node editor) drives Nuklear over this layer:
 * it renders into the 8-bit kernel-heap back-buffer at NK_BACKBUF_ADDR and
 * calls SYS_NK_FRAME (220) so the kernel composites it as a titled window on
 * the desktop, exactly like the DOOM window. The layer owns the hybrid
 * palette (indices 0-14 keep the desktop colors, 15-255 are the UI ramp),
 * the 8x8 bitmap font, the software command rasterizer and the input
 * translation (raw PS/2 scancodes -> Nuklear keys/unicode, mouse state).
 */

#include <stdint.h>

#define NK_W           800
#define NK_H           360
#define NK_BACKBUF      ((volatile uint8_t *)0x0B400000UL)

/* MiniOS syscalls used by the platform. */
long nk_sys_time_ms(void);
long nk_sys_kbd(void);
long nk_sys_palette(const unsigned char *pal768);
long nk_sys_kbd_raw(int on);
long nk_sys_vga_mode(int on);
long nk_sys_fb_info(int *w, int *h, int *pitch);
long nk_sys_mouse(int *xybw);          /* int[4]: x, y, buttons, wheel */
/* Call SYS_MOUSE with a pointer that is NOT in the user window; the kernel
 * must reject it with -EFAULT. Used by --selftest to prove the pointer
 * validation, so a mutant that drops the bounds check is killed. */
long nk_sys_mouse_badptr(void);
long nk_sys_nk_frame(int *origin);     /* int[2]: window content origin */

/* Hybrid palette: indices 0-14 are the desktop colors (kept so the desktop
 * behind the window never recolors); 15-255 are the UI ramp. */
void nk_build_palette(unsigned char *pal768);

/* 8x8 bitmap font (ASCII 32..127), shared with the rasterizer. */
extern const uint8_t nk_font8x8[96][8];

/* The nk_user_font for this backend: 8x8 monospace. */
struct nk_user_font nk_minios_font(void);

/* Rasterize the Nuklear command list into the back-buffer. */
void nk_rasterize(struct nk_context *ctx);

/* Feed raw keyboard scancodes and mouse state into the Nuklear context.
 * Call between nk_input_begin/nk_input_end of the application loop.
 * The mouse position is translated from desktop coordinates into the UI
 * window's local coordinates using the last origin returned by
 * SYS_NK_FRAME (nk_set_window_origin). */
void nk_set_window_origin(int x, int y);
void nk_poll_input(struct nk_context *ctx);

#endif