/* desktop_shortcuts.h -- configurable desktop icon shortcuts.
 *
 * Shortcuts are defined in etc/shortcuts on the ramdisk (one per line,
 * pipe-delimited: name|icon|command).  At boot the kernel loads the file,
 * decodes each icon PNG via stbi_load_file, maps the RGBA pixels to the
 * nearest entry in the icon palette, and caches the result.  The desktop
 * renderer draws the cached icons; mouse clicks launch the command through
 * the shell.
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

/* Icon palette: 16 colours loaded into VGA DAC indices 240-255.
 * Indices 0-14 stay as the desktop palette; the icon palette gives
 * enough range for simple pixel-art icons. */
#define ICON_PAL_BASE  240
#define ICON_PAL_SIZE  16

/* A decoded+cached desktop shortcut. */
struct desktop_shortcut {
    char name[SHORTCUT_NAME_LEN];
    char cmd[SHORTCUT_CMD_LEN];
    int  x, y;                 /* pixel position on the desktop */
    int  w, h;                 /* icon dimensions (ICON_W x ICON_H) */
    const uint8_t *pixels;     /* palette-mapped pixel indices (ICON_W*ICON_H bytes) */
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
