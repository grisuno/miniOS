#ifndef NUKLEAR_THEME_H
#define NUKLEAR_THEME_H

/** Docstring: shared Nuklear theme contract for every MiniOS NK app.
 *
 * One config surface for the look of file, nuklear, piano and vedit:
 * a theme is a plain-text file under /etc/themes with `key r g b`
 * lines, and /etc/themes/current holds the active theme name. Values
 * SHOULD sit on the 6x6x6 cube (multiples of 51) so the 8-bit backend
 * maps them exactly instead of nearest-neighbour. Loading starts from
 * the compiled-in fallback and overlays parsed lines, so a partial
 * file still themes fully and a missing file degrades to the default.
 */

#define NK_THEME_NAME_MAX 16
#define NK_THEME_KEY_MAX 24
#define NK_THEME_LINE_MAX 64
#define NK_THEME_PATH_DIR "/etc/themes/"
#define NK_THEME_PATH_CURRENT "/etc/themes/current"
#define NK_THEME_DEFAULT "dark"

/** Single source of truth for theme keys (X-macro: no table drift). */
#define NK_THEME_KEY_LIST \
    X(text, 0) \
    X(window, 1) \
    X(header, 2) \
    X(border, 3) \
    X(button, 4) \
    X(button_hover, 5) \
    X(button_active, 6) \
    X(toggle, 7) \
    X(toggle_hover, 8) \
    X(toggle_cursor, 9) \
    X(select, 10) \
    X(select_active, 11) \
    X(slider, 12) \
    X(slider_cursor, 13) \
    X(slider_cursor_hover, 14) \
    X(slider_cursor_active, 15) \
    X(property, 16) \
    X(edit, 17) \
    X(edit_cursor, 18) \
    X(combo, 19) \
    X(chart, 20) \
    X(chart_color, 21) \
    X(chart_color_highlight, 22) \
    X(scrollbar, 23) \
    X(scrollbar_cursor, 24) \
    X(scrollbar_cursor_hover, 25) \
    X(scrollbar_cursor_active, 26) \
    X(tab_header, 27) \
    X(knob, 28) \
    X(knob_cursor, 29) \
    X(knob_cursor_hover, 30) \
    X(knob_cursor_active, 31)

#define NK_THEME_KEY_COUNT 32

struct nk_context;

/** Resolve the active theme name (current file, else the default). */
int nk_theme_active(char *dst, int cap);

/** Load name (or active when 0) into rgb[32][3]; 0 ok, <0 fallback used. */
int nk_theme_probe(const char *name, unsigned char rgb[NK_THEME_KEY_COUNT][3]);

/** Apply name (or active when 0) to ctx; 0 ok, <0 fallback applied. */
int nk_theme_apply(struct nk_context *ctx, const char *name);

#endif
