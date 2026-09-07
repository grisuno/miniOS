/* desktop_shortcuts.h -- configurable desktop icon shortcuts.
 *
 * Shortcuts are defined in etc/shortcuts on the ramdisk (one per line,
 * pipe-delimited: name|icon|command).  At boot the kernel loads the file,
 * decodes each icon PNG via stbi_load_file and caches the raw RGBA pixels,
 * so icons keep their full color depth on true-color desktops instead of
 * being quantized to the 16-entry icon palette (that mapping only applies
 * in the 8-bit fallback mode).  The desktop renderer draws the cached
 * icons; mouse clicks launch the command through the shell.
 */

#ifndef DESKTOP_SHORTCUTS_H
#define DESKTOP_SHORTCUTS_H

#include <stdint.h>

/* Maximum number of desktop shortcuts and label length. */
#define MAX_SHORTCUTS    16
#define SHORTCUT_NAME_LEN 13   /* 12 chars + NUL */
#define SHORTCUT_CMD_LEN  48
#define SHORTCUT_PATH_LEN 32

/* Icon geometry. */
#define ICON_W  32
#define ICON_H  32
#define ICON_PAD_X  8          /* horizontal gap between icons */
#define ICON_PAD_Y  12         /* vertical gap (icon + label) */
#define ICON_LABEL_H 10        /* text row below icon */

/* Dock geometry: icons sit in a centered bar just above the taskbar,
 * Mac OS X style, so they float over the wallpaper with a dark backing
 * for contrast instead of a left-edge column. */
#define DOCK_PAD_X  12         /* side padding inside the dock bar */
#define DOCK_PAD_Y  8          /* top/bottom padding inside the dock bar */
#define DOCK_GAP    6          /* gap between dock bar and taskbar */
#define DOCK_LABEL_GAP 2       /* gap between icon bitmap and its label */

/* Icon palette: 16 colours loaded into VGA DAC indices 240-255 in the
 * 8-bit fallback mode. Indices 0-14 stay as the desktop palette; the icon
 * palette gives enough range for simple pixel-art icons. In true color the
 * cached icon pixels are raw RGBA and this palette only feeds the embedded
 * fallback icons and the 8-bit quantizer. */
#define ICON_PAL_BASE  240
#define ICON_PAL_SIZE  16

/* A decoded+cached desktop shortcut. Pixels are raw RGBA bytes
 * (ICON_W*ICON_H*4): the PNG's own colors, alpha below 128 transparent.
 * Embedded fallback icons arrive as palette indices and are expanded to
 * RGBA at load time, so the renderer has a single code path. */
struct desktop_shortcut {
    char name[SHORTCUT_NAME_LEN];
    char cmd[SHORTCUT_CMD_LEN];
    int  x, y;                 /* pixel position on the desktop */
    int  w, h;                 /* icon dimensions (ICON_W x ICON_H) */
    const uint8_t *pixels;     /* RGBA pixels (ICON_W*ICON_H*4 bytes) */
};

/* Load shortcuts from etc/shortcuts, decode icons, compute layout.
 * Called once from vga_fb_draw_desktop on first draw. */
void desktop_shortcuts_load(void);

/* Draw all shortcut icons and labels onto the framebuffer. */
void desktop_shortcuts_draw(void);

/* Handle a left-click at (mx, my).  Returns the command string if the
 * click hit an icon, or NULL otherwise. */
const char *desktop_shortcuts_hit_test(int mx, int my);

#endif
