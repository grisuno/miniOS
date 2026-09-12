#ifndef VGA_FB_H
#define VGA_FB_H

#include <stdint.h>
#include "minios_abi.h"

/* Framebuffer geometry. The boot loader probes VESA BIOS Extensions for a
 * high-resolution linear framebuffer (32-bit true color first, then the
 * 8-bit-palette modes) and records width, height, pitch, physical base and
 * bits per pixel in the fixed VBE_INFO_ADDR struct; vga_fb_boot_config loads
 * them into the globals below before the kernel maps the framebuffer.
 * Without VBE the values are the Mode 13h defaults (320x200x8, phys 0xA0000).
 * In a true-color mode the kernel's palette-index drawing is expanded to RGB
 * on write, so desktop, icons and wallpaper are no longer quantized to the
 * 256-entry VGA DAC; in 8-bit mode the DAC path is used unchanged.
 * FB_ADDR is the fixed virtual address in the user window that both the kernel
 * desktop and graphics programs write through. It sits in the reserved tail
 * above DOOM_BACKBUF_ADDR (which is also the brk cap), so a program's heap can
 * never grow over the framebuffer. All three pinned addresses derive from
 * progs/minios_abi.h (single source of truth for the kernel-ABI layout). */
#define FB_ADDR    ((volatile uint8_t *)MINIOS_FB_ADDR)
extern int fb_width;
extern int fb_height;
extern int fb_pitch;
extern int fb_bpp;
extern unsigned long fb_phys_base;
/* Bytes per framebuffer pixel derived from fb_bpp (1 for 8-bit, 3 for 24,
 * 4 for 32). */
int fb_bytes_per_pixel(void);
/* Read one desktop pixel as packed 0x00RRGGBB (palette-resolved in 8-bit
 * mode, native in true color). Backstop for `gfx pixel`/`gfx shot`, which
 * must report colors instead of DAC indices once the DAC is gone. */
unsigned long vga_fb_read_rgb(int x, int y);
/* Store the graphics program's 768-byte palette (SYS_PALETTE). In 8-bit mode
 * it is also programmed into the DAC; in true color it is only kept so the
 * DOOM/Nuklear blits can expand their indexed back-buffers to RGB. */
void vga_fb_set_gfx_palette(const unsigned char *pal);

void vga_fb_boot_config(void);

/* Graphics-window compositing. A ring-3 program (DOOM) renders into a
 * kernel-backed back-buffer mapped into the user window at DOOM_BACKBUF_ADDR
 * and calls SYS_DOOM_FRAME (211) to have the kernel composite it onto the
 * desktop at its native resolution, so the shell window stays visible. */
#define DOOM_W            MINIOS_DOOM_W
#define DOOM_H            MINIOS_DOOM_H
#define DOOM_BACKBUF_ADDR MINIOS_DOOM_BACKBUF_ADDR
void vga_fb_blit_gfx_window(void);
extern const char *gfx_win_title;
/** Docstring: Default graphics window title before SYS_GFX_SET_TITLE. */
#define GFX_TITLE_DEFAULT "DOOM"

/* Number of frames a ring-3 graphics program (DOOM, Quake 2, Nuklear) has
 * composited through SYS_DOOM_FRAME / SYS_NK_FRAME since boot. The shell's
 * `gfx frames` builtin reports it over the serial console, so the BDD suite
 * can prove a game actually rendered frames -- not merely launched -- by
 * running a demo and checking the counter climbed. */
extern unsigned long gfx_frames_composited;

/* Nuklear UI back-buffer. A ring-3 program (the node editor) renders a UI
 * into a kernel-heap back-buffer mapped into the user window and calls
 * SYS_NK_FRAME (220); the kernel composites it as a titled window on the
 * desktop exactly like the DOOM window, so the shell stays visible. It sits
 * in the reserved tail with the framebuffer, above DOOM_BACKBUF_ADDR (the brk
 * cap), so neither a growing heap nor the mmap zone can ever reach it. */
#define NK_W            MINIOS_NK_W
#define NK_H            MINIOS_NK_H
#define NK_BACKBUF_ADDR MINIOS_NK_BACKBUF_ADDR
void vga_fb_blit_nk_window(void);
/* Window origin of the last Nuklear composite, so SYS_NK_FRAME can report
 * where the UI landed for mouse-coordinate translation. */
extern int nk_win_x, nk_win_y;

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

/* Wallpaper: a photographic background on the 8-bit desktop. The image
 * file below (800x600 RGB PNG on the ramdisk, produced by
 * tools/gen_desktop_pngs.py) is decoded once per boot via stbi_load_file,
 * stretched to the framebuffer and mapped to a fixed 6x6x6 websafe cube
 * at DAC 16-231, clear of the desktop (0-14) and icon (240-255) ranges. */
#define WALLPAPER_PATH "wall/wallpaper.png"
#define WALL_PAL_BASE  16
#define WALL_PAL_SIZE  216

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
/* Keyboard-layout widget: two-letter "EN"/"ES" label, click toggles. */
#define TASKBAR_KBD_CH     2      /* "EN" / "ES" */
#define TASKBAR_KBD_W      (TASKBAR_KBD_CH * FONT_W)

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

/* Title-bar window controls (minimize, maximize, close). Drawn as a strip of
 * three FONT_W-wide glyph buttons at the right end of any titled window
 * (terminal, DOOM, Nuklear); the mouse tick hit-tests them before drag. */
#define WM_BTN_W       FONT_W
#define WM_BTN_H       FONT_H
#define WM_BTN_PAD     2
#define WM_BTN_MIN     1
#define WM_BTN_MAX     2
#define WM_BTN_CLOSE   3

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
void     vga_fb_text_cursor(int col);
void     vga_fb_hide_text_cursor(void);
void     vga_fb_draw_desktop(void);
void     vga_fb_toggle_fullscreen(void);
void     vga_fb_move_terminal(int dx, int dy);
void     vga_fb_snap_window(int zone);
void     vga_fb_resize(int dcols, int drows);
void     vga_fb_reset_default(void);
void     vga_fb_toggle_minimize(void);
int      vga_fb_is_minimized(void);
int      vga_fb_is_fullscreen(void);
int      vga_fb_close_active(void);
/* Multi-window manager: Alt-Tab focus cycle, Super-Tab tiling, second
 * terminal. Focus ids 0/1 = terminals, 2 = graphics window. */
#define WM_FOCUS_GFX 2
void     vga_fb_focus_next(void);
int      vga_fb_focus_id(int id);
int      vga_fb_focus_get(void);
/* PS/2 ownership for pid: 1 when pid may consume the keyboard port. One
 * keyboard feeds every window, so the focused window owns it: a background
 * gfx job reads only while the gfx window is focused, the shell only while
 * a terminal is. A legacy foreground program owns everything (its shell is
 * blocked, so there is nobody to steal from). Serial stays shell-only. */
int      vga_fb_ps2_owner(int pid);
int      vga_fb_nterms_get(void);
int      vga_fb_term_split(void);
int      vga_fb_term_close_focused(void);
void     vga_fb_tile_all(void);
void     vga_fb_list_windows(void);
int      wm_close_pending(void);
void     wm_clear_close(void);
int      wm_gfx_mode_active(void);
void vga_fb_mouse_tick(void);
void vga_fb_mouse_init(void);

/* Graphics-mode pointer. SYS_VGA_MODE toggles vga_fb_set_gfx_mode; while a
 * ring-3 graphics program owns the display the kernel idle loop (and with it
 * vga_fb_mouse_tick) never runs, so the frame-composite functions restore the
 * previous frame's pointer before the blit and redraw it after, keeping the
 * desktop pointer visible over the whole display without leaving trails. */
void vga_fb_set_gfx_mode(int on);

extern int vga_fb_active;

#endif
