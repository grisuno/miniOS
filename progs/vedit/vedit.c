/* vedit.c - fullscreen mini IDE for MiniOS, hosted on Nuklear.
 *
 * A visual text editor with live C/Python/Lua syntax highlighting that
 * runs as an ordinary ring-3 program, never as kernel code: it renders
 * into the Nuklear back-buffer and the kernel composites it as a titled
 * window on the desktop (the DOOM/Nuklear/piano pattern), so the shell
 * stays visible and the desktop keeps working around it.
 *
 * Every platform fact comes from minios_abi.h or a syscall, never from
 * a literal: syscall numbers from MINIOS_SYS_*, geometry from
 * NK_W/NK_H, cell metrics from the platform font at runtime, the
 * composite origin from SYS_NK_FRAME. Keystrokes arrive through
 * GETC_RAW (serial + PS/2 multiplexer with no line buffering, echo or
 * scrollback detour); frames leave as pixels, diagnostics as stdout
 * text (serial only while the gfx mode owns the display).
 *
 * Interaction: arrows move, typing inserts, Enter splits with
 * auto-indent, Tab indents, Backspace/Delete erase and join lines,
 * Home/End/PgUp/PgDn jump, ^O/^S save, ^W find (wraps once), ^G goto,
 * ^X save+quit, Esc quit without saving, ^L dumps the buffer with ANSI
 * highlight to the console (serial fallback, BDD hook). The on-screen
 * Save/Find/Quit buttons are clickable too. Bounds are the kernel
 * editor's (512 lines, 127 chars); full lines, overflowing joins and
 * full buffers refuse whole, and a truncated load refuses to save.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "nuklear.h"
#include "nuklear_minios.h"

/* ---- MiniOS syscalls vedit needs beyond the platform layer ---- */
static long vedit_getc_raw(long blocking) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_GETC_RAW), "D"(blocking)
                     : "rcx", "r11", "memory");
    return ret;
}

static long vedit_set_title(const char *t) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_GFX_SET_TITLE), "D"(t)
                     : "rcx", "r11", "memory");
    return ret;
}

/* ---- Bounds (the kernel editor's, so files round-trip byte-identical) -- */
#define VEDIT_MAX_LINES 512
#define VEDIT_LINE_MAX 128
#define VEDIT_LINE_USED (VEDIT_LINE_MAX - 1)
#define VEDIT_FILE_MAX (64 * 1024)
#define VEDIT_FNAME_MAX 64
#define VEDIT_MSG_MAX 128
#define VEDIT_WORD_MAX 32
#define VEDIT_TAB_W 4
#define VEDIT_SEQ_SPINS 20000
#define VEDIT_UI_MEMORY (4 * 1024 * 1024)

/* ---- Languages ---- */
#define VEDIT_LANG_TEXT 0
#define VEDIT_LANG_C 1
#define VEDIT_LANG_PY 2
#define VEDIT_LANG_LUA 3

/* ---- Token colours (theme; RGB mirrors of the desktop/icon palette) ---- */
#define VEDIT_COL_DEFAULT 0
#define VEDIT_COL_KEYWORD 1
#define VEDIT_COL_STRING 2
#define VEDIT_COL_COMMENT 3
#define VEDIT_COL_NUMBER 4
#define VEDIT_COL_PREPROC 5

/* ---- Cross-line scanner state ---- */
#define VEDIT_ST_BLOCK 1
#define VEDIT_ST_PY3S 2
#define VEDIT_ST_PY3D 4
#define VEDIT_ST_LUABLK 8
#define VEDIT_ST_LUASTR 16

/* ---- Decoded keys above any byte ---- */
#define VEDIT_KEY_UP 1000
#define VEDIT_KEY_DOWN 1001
#define VEDIT_KEY_LEFT 1002
#define VEDIT_KEY_RIGHT 1003
#define VEDIT_KEY_HOME 1004
#define VEDIT_KEY_END 1005
#define VEDIT_KEY_PGUP 1006
#define VEDIT_KEY_PGDN 1007
#define VEDIT_KEY_DEL 1008
#define VEDIT_KEY_ESC 1009

/* ---- Theme: every ink named once, used everywhere ---- */
static struct nk_color vedit_c_bg(void)      { return nk_rgb(12, 12, 12); }
static struct nk_color vedit_c_gutter(void)  { return nk_rgb(100, 100, 110); }
static struct nk_color vedit_c_default(void) { return nk_rgb(0, 220, 0); }
static struct nk_color vedit_c_keyword(void) { return nk_rgb(100, 149, 237); }
static struct nk_color vedit_c_string(void)  { return nk_rgb(255, 215, 0); }
static struct nk_color vedit_c_comment(void) { return nk_rgb(100, 100, 110); }
static struct nk_color vedit_c_number(void)  { return nk_rgb(255, 165, 0); }
static struct nk_color vedit_c_preproc(void) { return nk_rgb(220, 80, 60); }
static struct nk_color vedit_c_header(void)  { return nk_rgb(60, 90, 140); }
static struct nk_color vedit_c_headtxt(void) { return nk_rgb(255, 255, 255); }
static struct nk_color vedit_c_status(void)  { return nk_rgb(60, 60, 70); }
static struct nk_color vedit_c_cursor(void)  { return nk_rgb(0, 160, 0); }

static struct nk_color vedit_ink(int col) {
    if (col == VEDIT_COL_KEYWORD) return vedit_c_keyword();
    if (col == VEDIT_COL_STRING) return vedit_c_string();
    if (col == VEDIT_COL_COMMENT) return vedit_c_comment();
    if (col == VEDIT_COL_NUMBER) return vedit_c_number();
    if (col == VEDIT_COL_PREPROC) return vedit_c_preproc();
    return vedit_c_default();
}

/* ---- Keyword tables (whole-word match, so `in` never fires in `print`) -- */
static const char *vedit_kw_c =
    " auto break case char const continue default do double else enum extern"
    " float for goto if inline int long register restrict return short signed"
    " sizeof static struct switch typedef union unsigned void volatile while"
    " _Bool _Complex _Imaginary _Alignas _Alignof _Atomic _Static_assert"
    " _Noreturn _Thread_local _Generic true false NULL";

static const char *vedit_kw_py =
    " False None True and as assert async await break class continue def del"
    " elif else except finally for from global if import in is lambda nonlocal"
    " not or pass raise return try while with yield print len range str int"
    " float list dict set open self";

static const char *vedit_kw_lua =
    " and break do else elseif end false for function goto if in local nil not"
    " or repeat return then true until while print require ipairs pairs"
    " tostring tonumber";

/* ---- Buffer: flat pool plus parallel used counts (no structs needed) ---- */
static char *vedit_pool;
static int *vedit_used;
static int vedit_count;
static int vedit_cx;
static int vedit_cy;
static int vedit_top;
static int vedit_hoff;
static int vedit_dirty;
static int vedit_trunc;
static int vedit_lang;
static char vedit_fname[VEDIT_FNAME_MAX];
static char vedit_msg[VEDIT_MSG_MAX];
static int vedit_cell[VEDIT_LINE_MAX];

/* ---- View geometry, derived from the window and font at runtime ---- */
static int vedit_cw;
static int vedit_ch;
static int vedit_cols;
static int vedit_code_rows;
static int vedit_menu_h;
static int vedit_code_y;
static int vedit_status_y;
static int vedit_help_y;
static int vedit_gutter_w;

static char ui_memory[VEDIT_UI_MEMORY];

static void vedit_set_msg(const char *s) {
    size_t n = strlen(s);
    if (n > VEDIT_MSG_MAX - 1) n = VEDIT_MSG_MAX - 1;
    memcpy(vedit_msg, s, n);
    vedit_msg[n] = 0;
}

static int vedit_is_alpha(int c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static int vedit_is_digit(int c) {
    return c >= '0' && c <= '9';
}

static int vedit_is_wordc(int c) {
    return vedit_is_alpha(c) || vedit_is_digit(c);
}

static int vedit_is_kw(const char *table, const char *word, int wlen) {
    int i = 0;
    if (wlen <= 0) return 0;
    while (table[i]) {
        int j = 0;
        while (table[i] == ' ') i++;
        if (!table[i]) break;
        while (table[i + j] && table[i + j] != ' ' &&
               j < wlen && table[i + j] == word[j])
            j++;
        if (j == wlen && (table[i + j] == ' ' || table[i + j] == 0))
            return 1;
        while (table[i] && table[i] != ' ') i++;
    }
    return 0;
}

static int vedit_lang_of(const char *fname) {
    size_t n = strlen(fname);
    if (n >= 2 && fname[n - 2] == '.') {
        if (fname[n - 1] == 'c') return VEDIT_LANG_C;
        if (fname[n - 1] == 'h') return VEDIT_LANG_C;
        if (fname[n - 1] == 's') return VEDIT_LANG_C;
    }
    if (n >= 3 && fname[n - 3] == '.' &&
        fname[n - 2] == 'p' && fname[n - 1] == 'y')
        return VEDIT_LANG_PY;
    if (n >= 4 && fname[n - 4] == '.' && fname[n - 3] == 'l' &&
        fname[n - 2] == 'u' && fname[n - 1] == 'a')
        return VEDIT_LANG_LUA;
    return VEDIT_LANG_TEXT;
}

static const char *vedit_lang_name(int lang) {
    if (lang == VEDIT_LANG_C) return "C";
    if (lang == VEDIT_LANG_PY) return "Python";
    if (lang == VEDIT_LANG_LUA) return "Lua";
    return "text";
}

/* Paint one line into vedit_cell; returns the state for the next line. */
static int vedit_scan_line(const char *t, int len, int st) {
    int i = 0;
    int k;
    int j;
    for (k = 0; k < len; k++) vedit_cell[k] = VEDIT_COL_DEFAULT;
    if (len <= 0) return st;
    if (vedit_lang == VEDIT_LANG_TEXT) return 0;
    if (vedit_lang == VEDIT_LANG_C) {
        if (st == VEDIT_ST_BLOCK) {
            for (j = 0; j + 1 < len; j++) {
                if (t[j] == '*' && t[j + 1] == '/') break;
            }
            if (j + 1 >= len) {
                for (k = 0; k < len; k++) vedit_cell[k] = VEDIT_COL_COMMENT;
                return VEDIT_ST_BLOCK;
            }
            for (k = 0; k <= j + 1; k++) vedit_cell[k] = VEDIT_COL_COMMENT;
            i = j + 2;
            st = 0;
        }
        j = 0;
        while (j < len && (t[j] == ' ' || t[j] == '\t')) j++;
        if (j < len && t[j] == '#') {
            for (k = 0; k < len; k++) vedit_cell[k] = VEDIT_COL_PREPROC;
            return 0;
        }
        while (i < len) {
            int c = (unsigned char)t[i];
            int d = (i + 1 < len) ? (unsigned char)t[i + 1] : 0;
            if (c == '/' && d == '/') {
                for (k = i; k < len; k++) vedit_cell[k] = VEDIT_COL_COMMENT;
                break;
            }
            if (c == '/' && d == '*') {
                vedit_cell[i] = vedit_cell[i + 1] = VEDIT_COL_COMMENT;
                for (j = i + 2; j + 1 < len; j++) {
                    if (t[j] == '*' && t[j + 1] == '/') break;
                }
                if (j + 1 >= len) {
                    for (k = i + 2; k < len; k++)
                        vedit_cell[k] = VEDIT_COL_COMMENT;
                    return VEDIT_ST_BLOCK;
                }
                for (k = i + 2; k <= j + 1; k++)
                    vedit_cell[k] = VEDIT_COL_COMMENT;
                i = j + 2;
            } else if (c == '"' || c == '\'') {
                int q = c;
                j = i + 1;
                vedit_cell[i] = VEDIT_COL_STRING;
                while (j < len) {
                    int e = (unsigned char)t[j];
                    vedit_cell[j] = VEDIT_COL_STRING;
                    if (e == '\\' && j + 1 < len) {
                        vedit_cell[j + 1] = VEDIT_COL_STRING;
                        j += 2;
                    } else if (e == q) {
                        j++;
                        break;
                    } else {
                        j++;
                    }
                }
                i = j;
            } else if (vedit_is_digit(c)) {
                j = i;
                while (j < len) {
                    int e = (unsigned char)t[j];
                    if (vedit_is_wordc(e) || e == '.' || e == '\'' || e == '_')
                        j++;
                    else
                        break;
                }
                for (k = i; k < j; k++) vedit_cell[k] = VEDIT_COL_NUMBER;
                i = j;
            } else if (vedit_is_alpha(c)) {
                char w[VEDIT_WORD_MAX];
                int wl = 0;
                j = i;
                while (j < len && vedit_is_wordc((unsigned char)t[j])) {
                    if (wl < VEDIT_WORD_MAX - 1) w[wl++] = t[j];
                    j++;
                }
                if (vedit_is_kw(vedit_kw_c, w, wl)) {
                    for (k = i; k < j; k++) vedit_cell[k] = VEDIT_COL_KEYWORD;
                }
                i = j;
            } else {
                i++;
            }
        }
        return 0;
    }
    if (vedit_lang == VEDIT_LANG_PY) {
        if (st == VEDIT_ST_PY3S || st == VEDIT_ST_PY3D) {
            int qq = (st == VEDIT_ST_PY3D) ? '"' : '\'';
            for (j = 0; j + 2 < len; j++) {
                if (t[j] == qq && t[j + 1] == qq && t[j + 2] == qq) break;
            }
            if (j + 2 >= len) {
                for (k = 0; k < len; k++) vedit_cell[k] = VEDIT_COL_STRING;
                return st;
            }
            for (k = 0; k <= j + 2; k++) vedit_cell[k] = VEDIT_COL_STRING;
            i = j + 3;
            st = 0;
        }
        while (i < len) {
            int c = (unsigned char)t[i];
            if (c == '#') {
                for (k = i; k < len; k++) vedit_cell[k] = VEDIT_COL_COMMENT;
                break;
            }
            if (i + 2 < len && (c == '\'' || c == '"') &&
                (unsigned char)t[i + 1] == (unsigned)c &&
                (unsigned char)t[i + 2] == (unsigned)c) {
                int want = (c == '"') ? VEDIT_ST_PY3D : VEDIT_ST_PY3S;
                vedit_cell[i] = vedit_cell[i + 1] =
                    vedit_cell[i + 2] = VEDIT_COL_STRING;
                for (j = i + 3; j + 2 < len; j++) {
                    if ((unsigned char)t[j] == (unsigned)c &&
                        (unsigned char)t[j + 1] == (unsigned)c &&
                        (unsigned char)t[j + 2] == (unsigned)c)
                        break;
                }
                if (j + 2 >= len) {
                    for (k = i + 3; k < len; k++)
                        vedit_cell[k] = VEDIT_COL_STRING;
                    return want;
                }
                for (k = i + 3; k <= j + 2; k++)
                    vedit_cell[k] = VEDIT_COL_STRING;
                i = j + 3;
            } else if (c == '"' || c == '\'') {
                int q = c;
                j = i + 1;
                vedit_cell[i] = VEDIT_COL_STRING;
                while (j < len) {
                    int e = (unsigned char)t[j];
                    vedit_cell[j] = VEDIT_COL_STRING;
                    if (e == '\\' && j + 1 < len) {
                        vedit_cell[j + 1] = VEDIT_COL_STRING;
                        j += 2;
                    } else if (e == q) {
                        j++;
                        break;
                    } else {
                        j++;
                    }
                }
                i = j;
            } else if (vedit_is_digit(c)) {
                j = i;
                while (j < len) {
                    int e = (unsigned char)t[j];
                    if (vedit_is_wordc(e) || e == '.' || e == '_')
                        j++;
                    else
                        break;
                }
                for (k = i; k < j; k++) vedit_cell[k] = VEDIT_COL_NUMBER;
                i = j;
            } else if (vedit_is_alpha(c)) {
                char w[VEDIT_WORD_MAX];
                int wl = 0;
                j = i;
                while (j < len && vedit_is_wordc((unsigned char)t[j])) {
                    if (wl < VEDIT_WORD_MAX - 1) w[wl++] = t[j];
                    j++;
                }
                if (vedit_is_kw(vedit_kw_py, w, wl)) {
                    for (k = i; k < j; k++) vedit_cell[k] = VEDIT_COL_KEYWORD;
                }
                i = j;
            } else {
                i++;
            }
        }
        return 0;
    }
    if (st == VEDIT_ST_LUABLK) {
        for (j = 0; j + 1 < len; j++) {
            if (t[j] == ']' && t[j + 1] == ']') break;
        }
        if (j + 1 >= len) {
            for (k = 0; k < len; k++) vedit_cell[k] = VEDIT_COL_COMMENT;
            return VEDIT_ST_LUABLK;
        }
        for (k = 0; k <= j + 1; k++) vedit_cell[k] = VEDIT_COL_COMMENT;
        i = j + 2;
        st = 0;
    } else if (st == VEDIT_ST_LUASTR) {
        for (j = 0; j + 1 < len; j++) {
            if (t[j] == ']' && t[j + 1] == ']') break;
        }
        if (j + 1 >= len) {
            for (k = 0; k < len; k++) vedit_cell[k] = VEDIT_COL_STRING;
            return VEDIT_ST_LUASTR;
        }
        for (k = 0; k <= j + 1; k++) vedit_cell[k] = VEDIT_COL_STRING;
        i = j + 2;
        st = 0;
    }
    while (i < len) {
        int c = (unsigned char)t[i];
        int d = (i + 1 < len) ? (unsigned char)t[i + 1] : 0;
        if (c == '-' && d == '-') {
            int e = (i + 3 < len) ? (unsigned char)t[i + 2] : 0;
            int f = (i + 3 < len) ? (unsigned char)t[i + 3] : 0;
            if (e == '[' && f == '[') {
                for (k = i; k <= i + 3; k++) vedit_cell[k] = VEDIT_COL_COMMENT;
                for (j = i + 4; j + 1 < len; j++) {
                    if (t[j] == ']' && t[j + 1] == ']') break;
                }
                if (j + 1 >= len) {
                    for (k = i + 4; k < len; k++)
                        vedit_cell[k] = VEDIT_COL_COMMENT;
                    return VEDIT_ST_LUABLK;
                }
                for (k = i + 4; k <= j + 1; k++)
                    vedit_cell[k] = VEDIT_COL_COMMENT;
                i = j + 2;
            } else {
                for (k = i; k < len; k++) vedit_cell[k] = VEDIT_COL_COMMENT;
                break;
            }
        } else if (c == '[' && d == '[') {
            vedit_cell[i] = vedit_cell[i + 1] = VEDIT_COL_STRING;
            for (j = i + 2; j + 1 < len; j++) {
                if (t[j] == ']' && t[j + 1] == ']') break;
            }
            if (j + 1 >= len) {
                for (k = i + 2; k < len; k++) vedit_cell[k] = VEDIT_COL_STRING;
                return VEDIT_ST_LUASTR;
            }
            for (k = i + 2; k <= j + 1; k++) vedit_cell[k] = VEDIT_COL_STRING;
            i = j + 2;
        } else if (c == '"' || c == '\'') {
            int q = c;
            j = i + 1;
            vedit_cell[i] = VEDIT_COL_STRING;
            while (j < len) {
                int e = (unsigned char)t[j];
                vedit_cell[j] = VEDIT_COL_STRING;
                if (e == '\\' && j + 1 < len) {
                    vedit_cell[j + 1] = VEDIT_COL_STRING;
                    j += 2;
                } else if (e == q) {
                    j++;
                    break;
                } else {
                    j++;
                }
            }
            i = j;
        } else if (vedit_is_digit(c)) {
            j = i;
            while (j < len) {
                int e = (unsigned char)t[j];
                if (vedit_is_wordc(e) || e == '.' || e == '_')
                    j++;
                else
                    break;
            }
            for (k = i; k < j; k++) vedit_cell[k] = VEDIT_COL_NUMBER;
            i = j;
        } else if (vedit_is_alpha(c)) {
            char w[VEDIT_WORD_MAX];
            int wl = 0;
            j = i;
            while (j < len && vedit_is_wordc((unsigned char)t[j])) {
                if (wl < VEDIT_WORD_MAX - 1) w[wl++] = t[j];
                j++;
            }
            if (vedit_is_kw(vedit_kw_lua, w, wl)) {
                for (k = i; k < j; k++) vedit_cell[k] = VEDIT_COL_KEYWORD;
            }
            i = j;
        } else {
            i++;
        }
    }
    return 0;
}

/* Multi-line state at the start of a row: replay earlier lines. */
static int vedit_state_at(int row) {
    int st = 0;
    int r;
    for (r = 0; r < row && r < vedit_count; r++)
        st = vedit_scan_line(vedit_pool + r * VEDIT_LINE_MAX,
                             vedit_used[r], st);
    return st;
}

static char *vedit_row_ptr(int idx) {
    return vedit_pool + idx * VEDIT_LINE_MAX;
}

static void vedit_clamp(void) {
    if (vedit_count <= 0) {
        vedit_cy = 0;
        vedit_cx = 0;
        return;
    }
    if (vedit_cy < 0) vedit_cy = 0;
    if (vedit_cy >= vedit_count) vedit_cy = vedit_count - 1;
    if (vedit_cx < 0) vedit_cx = 0;
    if (vedit_cx > vedit_used[vedit_cy]) vedit_cx = vedit_used[vedit_cy];
}

static void vedit_follow(void) {
    int textw = vedit_cols - vedit_gutter_w;
    if (vedit_cy < vedit_top) vedit_top = vedit_cy;
    if (vedit_cy >= vedit_top + vedit_code_rows)
        vedit_top = vedit_cy - vedit_code_rows + 1;
    if (vedit_top < 0) vedit_top = 0;
    if (vedit_cx < vedit_hoff) vedit_hoff = vedit_cx;
    if (vedit_cx >= vedit_hoff + textw) vedit_hoff = vedit_cx - textw + 1;
    if (vedit_hoff < 0) vedit_hoff = 0;
}

/* ---- Editing ops (fail closed: refuse whole, never truncate) ---- */

static void vedit_insert_char(int c) {
    char *l;
    int k;
    if (vedit_count <= 0) {
        if (vedit_count >= VEDIT_MAX_LINES) {
            vedit_set_msg("buffer full");
            return;
        }
        vedit_used[0] = 0;
        vedit_count = 1;
        vedit_cy = 0;
        vedit_cx = 0;
    }
    l = vedit_row_ptr(vedit_cy);
    if (vedit_used[vedit_cy] >= VEDIT_LINE_USED) {
        vedit_set_msg("line full");
        return;
    }
    for (k = vedit_used[vedit_cy]; k > vedit_cx; k--) l[k] = l[k - 1];
    l[vedit_cx] = (char)c;
    vedit_used[vedit_cy]++;
    vedit_cx++;
    vedit_dirty = 1;
    vedit_msg[0] = 0;
}

static void vedit_delete_line_at(int idx) {
    int k;
    if (idx < 0 || idx >= vedit_count) return;
    for (k = idx; k < vedit_count - 1; k++) {
        vedit_used[k] = vedit_used[k + 1];
        memmove(vedit_row_ptr(k), vedit_row_ptr(k + 1), VEDIT_LINE_MAX);
    }
    vedit_count--;
    vedit_dirty = 1;
}

static void vedit_backspace(void) {
    char *l;
    char *p;
    int k;
    int n;
    if (vedit_count <= 0 || vedit_cy >= vedit_count) return;
    l = vedit_row_ptr(vedit_cy);
    if (vedit_cx > 0) {
        for (k = vedit_cx - 1; k < vedit_used[vedit_cy] - 1; k++)
            l[k] = l[k + 1];
        vedit_used[vedit_cy]--;
        vedit_cx--;
        vedit_dirty = 1;
        vedit_msg[0] = 0;
        return;
    }
    if (vedit_cy == 0) return;
    p = vedit_row_ptr(vedit_cy - 1);
    if (vedit_used[vedit_cy - 1] + vedit_used[vedit_cy] > VEDIT_LINE_USED) {
        vedit_set_msg("line too long to join");
        return;
    }
    n = vedit_used[vedit_cy];
    for (k = 0; k < n; k++) p[vedit_used[vedit_cy - 1] + k] = l[k];
    vedit_cx = vedit_used[vedit_cy - 1];
    vedit_used[vedit_cy - 1] += n;
    vedit_delete_line_at(vedit_cy);
    vedit_cy--;
    vedit_msg[0] = 0;
}

static void vedit_delete_char(void) {
    char *l;
    char *nx;
    int k;
    int n;
    if (vedit_count <= 0 || vedit_cy >= vedit_count) return;
    l = vedit_row_ptr(vedit_cy);
    if (vedit_cx < vedit_used[vedit_cy]) {
        for (k = vedit_cx; k < vedit_used[vedit_cy] - 1; k++)
            l[k] = l[k + 1];
        vedit_used[vedit_cy]--;
        vedit_dirty = 1;
        vedit_msg[0] = 0;
        return;
    }
    if (vedit_cy + 1 >= vedit_count) return;
    nx = vedit_row_ptr(vedit_cy + 1);
    if (vedit_used[vedit_cy] + vedit_used[vedit_cy + 1] > VEDIT_LINE_USED) {
        vedit_set_msg("line too long to join");
        return;
    }
    n = vedit_used[vedit_cy + 1];
    for (k = 0; k < n; k++) l[vedit_used[vedit_cy] + k] = nx[k];
    vedit_used[vedit_cy] += n;
    vedit_delete_line_at(vedit_cy + 1);
    vedit_msg[0] = 0;
}

static void vedit_split(void) {
    char *l;
    char *dst;
    int ni = 0;
    int k;
    int t;
    if (vedit_count <= 0) {
        if (vedit_count >= VEDIT_MAX_LINES) {
            vedit_set_msg("buffer full");
            return;
        }
        vedit_used[0] = 0;
        vedit_count = 1;
        vedit_cy = 0;
        vedit_cx = 0;
        return;
    }
    if (vedit_count >= VEDIT_MAX_LINES) {
        vedit_set_msg("buffer full");
        return;
    }
    l = vedit_row_ptr(vedit_cy);
    while (ni < vedit_used[vedit_cy] && ni < VEDIT_LINE_USED) {
        int e = (unsigned char)l[ni];
        if (e == ' ' || e == '\t')
            ni++;
        else
            break;
    }
    for (k = vedit_count; k > vedit_cy + 1; k--) {
        vedit_used[k] = vedit_used[k - 1];
        memmove(vedit_row_ptr(k), vedit_row_ptr(k - 1), VEDIT_LINE_MAX);
    }
    dst = vedit_row_ptr(vedit_cy + 1);
    t = 0;
    for (k = 0; k < ni && t < VEDIT_LINE_USED; k++) dst[t++] = l[k];
    for (k = vedit_cx; k < vedit_used[vedit_cy] && t < VEDIT_LINE_USED; k++)
        dst[t++] = l[k];
    vedit_used[vedit_cy + 1] = t;
    vedit_used[vedit_cy] = vedit_cx;
    vedit_count++;
    vedit_cy++;
    vedit_cx = ni;
    if (vedit_cx > vedit_used[vedit_cy]) vedit_cx = vedit_used[vedit_cy];
    vedit_dirty = 1;
    vedit_msg[0] = 0;
}

static void vedit_tab(void) {
    char *l;
    int k;
    if (vedit_count <= 0) {
        if (vedit_count >= VEDIT_MAX_LINES) {
            vedit_set_msg("buffer full");
            return;
        }
        vedit_used[0] = 0;
        vedit_count = 1;
        vedit_cy = 0;
        vedit_cx = 0;
    }
    l = vedit_row_ptr(vedit_cy);
    if (VEDIT_LINE_USED - vedit_used[vedit_cy] < VEDIT_TAB_W) {
        vedit_set_msg("line full");
        return;
    }
    for (k = vedit_used[vedit_cy] - 1; k >= vedit_cx; k--)
        l[k + VEDIT_TAB_W] = l[k];
    for (k = 0; k < VEDIT_TAB_W; k++) l[vedit_cx + k] = ' ';
    vedit_used[vedit_cy] += VEDIT_TAB_W;
    vedit_cx += VEDIT_TAB_W;
    vedit_dirty = 1;
    vedit_msg[0] = 0;
}

static void vedit_find(const char *needle) {
    int r;
    int k;
    int nlen;
    if (!needle || needle[0] == 0) {
        vedit_set_msg("usage: find <text>");
        return;
    }
    nlen = (int)strlen(needle);
    for (r = vedit_cy; r < vedit_count; r++) {
        char *l = vedit_row_ptr(r);
        int start = (r == vedit_cy) ? vedit_cx : 0;
        for (k = start; k + nlen <= vedit_used[r]; k++) {
            int m = 0;
            while (m < nlen && (unsigned char)l[k + m] ==
                   (unsigned char)needle[m])
                m++;
            if (m == nlen) {
                char nb[32];
                vedit_cy = r;
                vedit_cx = k;
                vedit_msg[0] = 0;
                snprintf(nb, sizeof(nb), "found line %d", r + 1);
                vedit_set_msg(nb);
                return;
            }
        }
    }
    for (r = 0; r < vedit_cy && r < vedit_count; r++) {
        char *l = vedit_row_ptr(r);
        for (k = 0; k + nlen <= vedit_used[r]; k++) {
            int m = 0;
            while (m < nlen && (unsigned char)l[k + m] ==
                   (unsigned char)needle[m])
                m++;
            if (m == nlen) {
                char nb[32];
                vedit_cy = r;
                vedit_cx = k;
                snprintf(nb, sizeof(nb), "found line %d (wrapped)", r + 1);
                vedit_set_msg(nb);
                return;
            }
        }
    }
    vedit_set_msg("not found");
}

/* ---- Load/save (byte-parity with the kernel editor: NL between lines) -- */

static int vedit_save(void) {
    FILE *f;
    int i;
    if (vedit_trunc) {
        vedit_set_msg("refusing to save: file did not fit in the buffer");
        return -1;
    }
    f = fopen(vedit_fname, "w");
    if (!f) {
        vedit_set_msg("save failed");
        return -1;
    }
    for (i = 0; i < vedit_count; i++) {
        if (vedit_used[i] > 0) {
            if (fwrite(vedit_row_ptr(i), 1, (size_t)vedit_used[i], f) !=
                (size_t)vedit_used[i]) {
                fclose(f);
                vedit_set_msg("save failed");
                return -1;
            }
        }
        if (i + 1 < vedit_count) {
            if (fwrite("\n", 1, 1, f) != 1) {
                fclose(f);
                vedit_set_msg("save failed");
                return -1;
            }
        }
    }
    if (fclose(f) != 0) {
        vedit_set_msg("save failed");
        return -1;
    }
    vedit_dirty = 0;
    {
        char nb[96];
        snprintf(nb, sizeof(nb), "wrote %d line(s) to %s",
                 vedit_count, vedit_fname);
        vedit_set_msg(nb);
    }
    return 0;
}

static int vedit_load(void) {
    FILE *f;
    char chunk[512];
    size_t n;
    size_t k;
    int idx = 0;
    int used = 0;
    int total = 0;
    vedit_count = 0;
    vedit_trunc = 0;
    f = fopen(vedit_fname, "r");
    if (!f) return 0;
    while ((n = fread(chunk, 1, sizeof(chunk), f)) > 0) {
        total += (int)n;
        if (total > VEDIT_FILE_MAX) {
            fclose(f);
            return -1;
        }
        for (k = 0; k < n; k++) {
            int c = (unsigned char)chunk[k];
            if (c == '\n') {
                vedit_used[idx] = used;
                idx++;
                used = 0;
                if (idx >= VEDIT_MAX_LINES) {
                    vedit_trunc = 1;
                    vedit_count = idx;
                    fclose(f);
                    return 1;
                }
            } else if (c == '\r') {
            } else if (used < VEDIT_LINE_USED) {
                char *dst;
                if (idx >= VEDIT_MAX_LINES) {
                    vedit_trunc = 1;
                    vedit_count = idx;
                    fclose(f);
                    return 1;
                }
                dst = vedit_row_ptr(idx);
                dst[used] = chunk[k];
                used++;
            } else {
                vedit_trunc = 1;
            }
        }
    }
    if (used > 0 && idx < VEDIT_MAX_LINES) {
        vedit_used[idx] = used;
        idx++;
    }
    vedit_count = idx;
    fclose(f);
    return 1;
}

/* ---- Keyboard: GETC_RAW bytes decoded into extended key codes ---- */

static long vedit_getc_blocking(void) {
    return vedit_getc_raw(1);
}

static int vedit_poll(void) {
    int n = 0;
    while (n < VEDIT_SEQ_SPINS) {
        long c = vedit_getc_raw(0);
        if (c >= 0) return (int)c;
        n++;
    }
    return -1;
}

static int vedit_read_key(void) {
    long c = vedit_getc_blocking();
    int p1;
    int p2;
    if (c != 27) return (int)c;
    p1 = vedit_poll();
    if (p1 < 0) return VEDIT_KEY_ESC;
    if (p1 != '[') return VEDIT_KEY_ESC;
    p1 = vedit_poll();
    if (p1 < 0) return VEDIT_KEY_ESC;
    if (p1 == 'A') return VEDIT_KEY_UP;
    if (p1 == 'B') return VEDIT_KEY_DOWN;
    if (p1 == 'C') return VEDIT_KEY_RIGHT;
    if (p1 == 'D') return VEDIT_KEY_LEFT;
    if (p1 == 'H') return VEDIT_KEY_HOME;
    if (p1 == 'F') return VEDIT_KEY_END;
    if (p1 == '3' || p1 == '5' || p1 == '6') {
        p2 = vedit_poll();
        if (p2 == '~') {
            if (p1 == '3') return VEDIT_KEY_DEL;
            if (p1 == '5') return VEDIT_KEY_PGUP;
            return VEDIT_KEY_PGDN;
        }
        return VEDIT_KEY_ESC;
    }
    return VEDIT_KEY_ESC;
}

/* ---- Serial ANSI mirror (^L dump + save lines; the UI itself is pixels) -- */

static void vedit_ansi_for(int col) {
    if (col == VEDIT_COL_KEYWORD) printf("\033[1;34m");
    else if (col == VEDIT_COL_STRING) printf("\033[33m");
    else if (col == VEDIT_COL_COMMENT) printf("\033[90m");
    else if (col == VEDIT_COL_NUMBER) printf("\033[35m");
    else if (col == VEDIT_COL_PREPROC) printf("\033[31m");
}

static void vedit_console_dump(void) {
    int r;
    int st = 0;
    int c;
    int cur;
    printf("--- %s [%s] %d lines ---\n", vedit_fname,
           vedit_lang_name(vedit_lang), vedit_count);
    for (r = 0; r < vedit_count; r++) {
        char *l = vedit_row_ptr(r);
        printf("%4d: ", r + 1);
        st = vedit_scan_line(l, vedit_used[r], st);
        cur = VEDIT_COL_DEFAULT;
        for (c = 0; c < vedit_used[r]; c++) {
            if (vedit_cell[c] != cur) {
                if (cur != VEDIT_COL_DEFAULT) printf("\033[0m");
                if (vedit_cell[c] != VEDIT_COL_DEFAULT)
                    vedit_ansi_for(vedit_cell[c]);
                cur = vedit_cell[c];
            }
            putchar(l[c]);
        }
        if (cur != VEDIT_COL_DEFAULT) printf("\033[0m");
        putchar('\n');
    }
    fflush(stdout);
}

/* ---- Nuklear UI ---- */

/* Prompt state for find/goto, answered on the status row. */
static int vedit_prompt_on;
static char vedit_prompt_label[16];
static char vedit_prompt_buf[VEDIT_LINE_MAX];
static int vedit_prompt_pos;
static int vedit_prompt_goto;

static void vedit_prompt_open(const char *label, int is_goto) {
    size_t n = strlen(label);
    if (n > sizeof(vedit_prompt_label) - 1) n = sizeof(vedit_prompt_label) - 1;
    memcpy(vedit_prompt_label, label, n);
    vedit_prompt_label[n] = 0;
    vedit_prompt_pos = 0;
    vedit_prompt_buf[0] = 0;
    vedit_prompt_goto = is_goto;
    vedit_prompt_on = 1;
}

static void vedit_prompt_find(void) {
    vedit_prompt_open("find: ", 0);
}

static void vedit_draw_row(struct nk_command_buffer *canvas,
                           struct nk_user_font *font, int vrow, int line_idx,
                           int is_cursor_row) {
    char *l = NULL;
    int len = 0;
    int st = 0;
    int c;
    int cur;
    int run_start;
    int x = vedit_gutter_w * vedit_cw;
    int y = vedit_code_y + vrow * vedit_ch;
    char num[16];
    struct nk_color bg = vedit_c_bg();
    if (line_idx < vedit_count) {
        l = vedit_row_ptr(line_idx);
        len = vedit_used[line_idx];
        st = vedit_state_at(line_idx);
        st = vedit_scan_line(l, len, st);
        snprintf(num, sizeof(num), "%4d  ", line_idx + 1);
    } else {
        snprintf(num, sizeof(num), "~     ");
    }
    nk_draw_text(canvas, nk_rect((float)(x - vedit_gutter_w * vedit_cw),
                                 (float)y,
                                 (float)(vedit_gutter_w * vedit_cw),
                                 (float)vedit_ch),
                 num, (int)strlen(num), font, bg, vedit_c_gutter());
    if (!l) return;
    nk_fill_rect(canvas,
                 nk_rect((float)x, (float)y,
                         (float)((vedit_cols - vedit_gutter_w) * vedit_cw),
                         (float)vedit_ch),
                 0, bg);
    {
        int textw = vedit_cols - vedit_gutter_w;
        cur = VEDIT_COL_DEFAULT;
        run_start = 0;
        for (c = 0; c <= textw; c++) {
            int src = vedit_hoff + c;
            int want = VEDIT_COL_DEFAULT;
            int at_end = (c == textw);
            if (!at_end && src < len) want = vedit_cell[src];
            if (at_end || want != cur) {
                if (c > run_start) {
                    int rs = vedit_hoff + run_start;
                    if (rs < len) {
                        int show = c - run_start;
                        if (rs + show > len) show = len - rs;
                        nk_draw_text(canvas,
                                     nk_rect((float)(x + run_start * vedit_cw),
                                             (float)y,
                                             (float)(show * vedit_cw),
                                             (float)vedit_ch),
                                     l + rs, show, font, bg,
                                     vedit_ink(cur));
                    }
                }
                run_start = c;
                cur = want;
            }
        }
    }
    if (is_cursor_row && vedit_cx >= vedit_hoff &&
        vedit_cx < vedit_hoff + (vedit_cols - vedit_gutter_w)) {
        int ccx = x + (vedit_cx - vedit_hoff) * vedit_cw;
        nk_fill_rect(canvas, nk_rect((float)ccx, (float)y, (float)vedit_cw,
                                     (float)vedit_ch),
                     0, vedit_c_cursor());
        if (vedit_cx < len) {
            nk_draw_text(canvas,
                         nk_rect((float)ccx, (float)y, (float)vedit_cw,
                                 (float)vedit_ch),
                         l + vedit_cx, 1, font, vedit_c_cursor(),
                         vedit_c_bg());
        }
    }
}

static void vedit_draw_ui(struct nk_context *ctx, struct nk_user_font *font,
                          int *quit, int *save_and_quit) {
    struct nk_command_buffer *canvas;
    int r;
    int li;
    char status[256];
    static const char *help =
        "arrows move  type  Enter split  Tab indent  ^O save  ^X done  "
        "^W find  ^G goto  ^L console  Esc exit";
    static int prev_buttons = 0;
    int mouse[4] = {0, 0, 0, 0};
    int mdown = 0;
    int clicked = 0;
    int btn_w = 12 * vedit_cw;
    int btn_h = vedit_ch + 6;
    int bx = vedit_cw;
    int by = 2;
    static const char *labels[3] = {"^O Save", "^W Find", "^X Done"};

    vedit_clamp();
    vedit_follow();

    if (!nk_begin_titled(ctx, "vedit", "vedit",
                         nk_rect(0, 0, (float)NK_W, (float)NK_H),
                         NK_WINDOW_NO_SCROLLBAR)) {
        nk_end(ctx);
        return;
    }
    canvas = nk_window_get_canvas(ctx);

    nk_fill_rect(canvas, nk_rect(0, 0, (float)NK_W, (float)NK_H), 0,
                 vedit_c_bg());

    if (nk_sys_mouse(mouse) == 0) {
        int b = mouse[2] & 1;
        mdown = b;
        clicked = b && !prev_buttons;
        prev_buttons = b;
        if (mouse[3] > 0) vedit_top += 3;
        else if (mouse[3] < 0) vedit_top -= 3;
        if (vedit_top < 0) vedit_top = 0;
        if (mouse[3] && vedit_top > vedit_count) vedit_top = vedit_count;
    }

    nk_fill_rect(canvas, nk_rect(0, 0, (float)NK_W, (float)vedit_menu_h), 0,
                 vedit_c_header());
    for (r = 0; r < 3; r++) {
        int x = bx + r * (btn_w + vedit_cw);
        int hover = mdown && mouse[0] >= x && mouse[0] < x + btn_w &&
            mouse[1] >= by && mouse[1] < by + btn_h;
        nk_fill_rect(canvas, nk_rect((float)x, (float)by, (float)btn_w,
                                     (float)btn_h),
                     0, hover ? vedit_c_cursor() : vedit_c_status());
        nk_draw_text(canvas,
                     nk_rect((float)(x + vedit_cw), (float)(by + 3),
                             (float)(btn_w - 2 * vedit_cw), (float)vedit_ch),
                     labels[r], (int)strlen(labels[r]), font,
                     hover ? vedit_c_cursor() : vedit_c_status(),
                     vedit_c_headtxt());
        if (clicked && mouse[0] >= x && mouse[0] < x + btn_w &&
            mouse[1] >= by && mouse[1] < by + btn_h) {
            if (r == 0) {
                if (vedit_save() == 0)
                    printf("vedit: wrote %d line(s) to %s\n",
                           vedit_count, vedit_fname);
            } else if (r == 1) {
                vedit_prompt_find();
            } else {
                *save_and_quit = 1;
                *quit = 1;
            }
        }
    }

    for (r = 0; r < vedit_code_rows; r++) {
        li = vedit_top + r;
        vedit_draw_row(canvas, font, r, li, li == vedit_cy);
    }

    if (vedit_prompt_on) {
        size_t ln = strlen(vedit_prompt_label);
        size_t k;
        if (ln > sizeof(status) - 1) ln = sizeof(status) - 1;
        memcpy(status, vedit_prompt_label, ln);
        for (k = 0; k < strlen(vedit_prompt_buf) &&
             ln < sizeof(status) - 1; k++)
            status[ln++] = vedit_prompt_buf[k];
        status[ln] = 0;
    } else {
        snprintf(status, sizeof(status), " %s [%s] Ln %d/%d Col %d %s",
                 vedit_fname, vedit_lang_name(vedit_lang), vedit_cy + 1,
                 vedit_count > 0 ? vedit_count : 1, vedit_cx + 1, vedit_msg);
    }
    nk_fill_rect(canvas,
                 nk_rect(0, (float)vedit_status_y, (float)NK_W,
                         (float)(vedit_ch + 4)),
                 0, vedit_c_status());
    nk_draw_text(canvas,
                 nk_rect((float)vedit_cw, (float)(vedit_status_y + 2),
                         (float)(NK_W - 2 * vedit_cw), (float)vedit_ch),
                 status, (int)strlen(status), font, vedit_c_status(),
                 vedit_c_headtxt());
    if (vedit_prompt_on) {
        nk_fill_rect(canvas,
                     nk_rect((float)(vedit_cw + (int)strlen(status) *
                                     vedit_cw),
                             (float)(vedit_status_y + 2), (float)vedit_cw,
                             (float)vedit_ch),
                     0, vedit_c_cursor());
    }
    nk_draw_text(canvas,
                 nk_rect((float)vedit_cw, (float)vedit_help_y,
                         (float)(NK_W - 2 * vedit_cw), (float)vedit_ch),
                 help, (int)strlen(help), font, vedit_c_bg(),
                 vedit_c_gutter());
    nk_end(ctx);
}

/* Route one decoded key: prompt captures everything while open. */
static void vedit_prompt_key(int key) {
    if (key == '\n' || key == '\r') {
        vedit_prompt_on = 0;
        if (vedit_prompt_goto) {
            int n = 0;
            int i = 0;
            while (vedit_prompt_buf[i] >= '0' &&
                   vedit_prompt_buf[i] <= '9') {
                n = n * 10 + (vedit_prompt_buf[i] - '0');
                i++;
            }
            if (i == 0 || vedit_prompt_buf[i] != 0 ||
                n < 1 || n > vedit_count) {
                vedit_set_msg("no such line");
            } else {
                vedit_cy = n - 1;
                vedit_cx = 0;
                vedit_msg[0] = 0;
            }
        } else {
            vedit_find(vedit_prompt_buf);
        }
        return;
    }
    if (key == VEDIT_KEY_ESC) {
        vedit_prompt_on = 0;
        vedit_set_msg("cancelled");
        return;
    }
    if (key == '\b' || key == 127) {
        if (vedit_prompt_pos > 0) {
            vedit_prompt_pos--;
            vedit_prompt_buf[vedit_prompt_pos] = 0;
        }
        return;
    }
    if (key >= 32 && key < 127 && vedit_prompt_pos < VEDIT_LINE_MAX - 1) {
        vedit_prompt_buf[vedit_prompt_pos++] = (char)key;
        vedit_prompt_buf[vedit_prompt_pos] = 0;
    }
}

/* Route one decoded key: prompt captures everything while open. */
static void vedit_key(int key, int *quit, int *save_and_quit) {
    if (vedit_prompt_on) {
        vedit_prompt_key(key);
        return;
    }
    if (key == VEDIT_KEY_UP) {
        if (vedit_cy > 0) vedit_cy--;
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_DOWN) {
        if (vedit_cy + 1 < vedit_count) vedit_cy++;
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_LEFT) {
        if (vedit_cx > 0) {
            vedit_cx--;
        } else if (vedit_cy > 0) {
            vedit_cy--;
            vedit_cx = vedit_used[vedit_cy];
        }
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_RIGHT) {
        if (vedit_count > 0 && vedit_cy < vedit_count &&
            vedit_cx < vedit_used[vedit_cy]) {
            vedit_cx++;
        } else if (vedit_cy + 1 < vedit_count) {
            vedit_cy++;
            vedit_cx = 0;
        }
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_HOME) {
        vedit_cx = 0;
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_END) {
        if (vedit_count > 0 && vedit_cy < vedit_count)
            vedit_cx = vedit_used[vedit_cy];
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_PGUP) {
        vedit_cy -= vedit_code_rows;
        if (vedit_cy < 0) vedit_cy = 0;
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_PGDN) {
        vedit_cy += vedit_code_rows;
        if (vedit_count > 0 && vedit_cy >= vedit_count)
            vedit_cy = vedit_count - 1;
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_DEL) {
        vedit_delete_char();
    } else if (key == 15 || key == 19) {
        if (vedit_save() == 0)
            printf("vedit: wrote %d line(s) to %s\n",
                   vedit_count, vedit_fname);
    } else if (key == 23) {
        vedit_prompt_find();
    } else if (key == 7) {
        vedit_prompt_open("goto: ", 1);
    } else if (key == 12) {
        vedit_console_dump();
    } else if (key == 24) {
        *save_and_quit = 1;
        *quit = 1;
    } else if (key == VEDIT_KEY_ESC || key == 17) {
        *quit = 1;
    } else if (key == '\n' || key == '\r') {
        vedit_split();
    } else if (key == '\t') {
        vedit_tab();
    } else if (key == '\b' || key == 127) {
        vedit_backspace();
    } else if (key >= 32 && key < 127) {
        vedit_insert_char(key);
    }
}

static int vedit_title_dirty_shown = -1;

static void vedit_sync_title(void) {
    if (vedit_dirty != vedit_title_dirty_shown) {
        vedit_title_dirty_shown = vedit_dirty;
        if (vedit_dirty)
            vedit_set_title("vedit *");
        else
            vedit_set_title("vedit");
    }
}

static void vedit_gui_run(void) {
    unsigned char pal768[768];
    int fw;
    int fh;
    int fp;
    int origin[2] = {0, 0};
    int quit = 0;
    int save_and_quit = 0;
    struct nk_user_font font = nk_minios_font();
    struct nk_context ctx;

    nk_sys_vga_mode(1);
    nk_build_palette(pal768);
    nk_sys_palette(pal768);
    nk_sys_fb_info(&fw, &fh, &fp);
    (void)fw;
    (void)fh;
    (void)fp;

    vedit_cw = 8;
    vedit_ch = (int)font.height > 0 ? (int)font.height : 8;
    vedit_cols = NK_W / vedit_cw;
    if (vedit_cols < 20) vedit_cols = 20;
    vedit_gutter_w = 6;
    vedit_menu_h = vedit_ch * 2;
    vedit_code_y = vedit_menu_h;
    {
        int status_h = vedit_ch + 4;
        int help_h = vedit_ch + 4;
        vedit_code_rows = (NK_H - vedit_menu_h - status_h - help_h) / vedit_ch;
        if (vedit_code_rows < 1) vedit_code_rows = 1;
        vedit_help_y = NK_H - help_h - 2;
        vedit_status_y = vedit_help_y - status_h;
    }

    if (!nk_init_fixed(&ctx, ui_memory, VEDIT_UI_MEMORY, &font)) {
        printf("vedit: init failed\n");
        nk_sys_vga_mode(0);
        return;
    }

    vedit_set_msg("type to edit, ^X done");
    vedit_sync_title();
    while (!quit) {
        int key;
        nk_input_begin(&ctx);
        nk_input_end(&ctx);
        vedit_draw_ui(&ctx, &font, &quit, &save_and_quit);
        nk_rasterize(&ctx);
        if (nk_sys_nk_frame(origin) == 0)
            nk_set_window_origin(origin[0], origin[1]);
        nk_clear(&ctx);
        vedit_sync_title();
        if (!quit) {
            key = vedit_read_key();
            vedit_key(key, &quit, &save_and_quit);
        }
    }

    if (save_and_quit) {
        if (vedit_save() == 0)
            printf("vedit: wrote %d line(s) to %s\n",
                   vedit_count, vedit_fname);
    }

    nk_free(&ctx);
    nk_sys_vga_mode(0);
}

/* ---- Headless selftest: one frame through the whole pipeline ---- */

static int vedit_selftest(void) {
    unsigned char pal768[768];
    int fw;
    int fh;
    int fp;
    int origin[2] = {0, 0};
    struct nk_user_font font = nk_minios_font();
    struct nk_context ctx;
    volatile uint8_t *fb;
    int ox;
    int oy;
    int bpx;
    int landed = 0;

    nk_sys_vga_mode(1);
    nk_build_palette(pal768);
    nk_sys_palette(pal768);
    nk_sys_fb_info(&fw, &fh, &fp);
    if (!nk_init_fixed(&ctx, ui_memory, VEDIT_UI_MEMORY, &font)) {
        printf("vedit: init failed\n");
        return 1;
    }
    nk_input_begin(&ctx);
    nk_input_end(&ctx);
    if (nk_begin_titled(&ctx, "vedit", "vedit",
                        nk_rect(0, 0, (float)NK_W, (float)NK_H),
                        NK_WINDOW_NO_SCROLLBAR)) {
        struct nk_command_buffer *canvas = nk_window_get_canvas(&ctx);
        nk_fill_rect(canvas, nk_rect(0, 0, (float)NK_W, (float)NK_H), 0,
                     vedit_c_bg());
        nk_draw_text(canvas, nk_rect(8, 8, 200, 8), "vedit selftest", 14,
                     &font, vedit_c_bg(), vedit_c_default());
        nk_end(&ctx);
    } else {
        nk_end(&ctx);
    }
    nk_rasterize(&ctx);
    NK_BACKBUF[0] = 0xF0;
    if (nk_sys_nk_frame(origin) != 0) {
        printf("vedit: frame syscall failed\n");
        return 1;
    }
    fb = (volatile uint8_t *)MINIOS_FB_ADDR;
    ox = origin[0];
    oy = origin[1];
    bpx = (fw > 0 && fp % fw == 0) ? fp / fw : 1;
    if (ox >= 0 && oy >= 0 && ox < fw && oy < fh) {
        volatile uint8_t *px = fb + oy * fp + ox * bpx;
        if (bpx == 1) {
            landed = (px[0] == NK_BACKBUF[0]);
        } else {
            unsigned pi = (unsigned)NK_BACKBUF[0] * 3;
            landed = (px[0] == pal768[pi + 2] &&
                      px[1] == pal768[pi + 1] &&
                      px[2] == pal768[pi + 0]);
        }
    }
    if (!landed) {
        printf("vedit: composite did not land at the window origin\n");
        return 1;
    }
    nk_free(&ctx);
    nk_sys_vga_mode(0);
    printf("vedit: frame ok (%dx%d)\n", NK_W, NK_H);
    return 0;
}

int main(int argc, char **argv) {
    int rc;
    size_t n;
    if (argc > 1 && strcmp(argv[1], "--selftest") == 0)
        return vedit_selftest();
    if (argc != 2) {
        printf("usage: vedit <file>\n");
        return 1;
    }
    if (strlen(argv[1]) >= VEDIT_FNAME_MAX) {
        printf("vedit: %s: name too long\n", argv[1]);
        return 1;
    }
    n = strlen(argv[1]);
    memcpy(vedit_fname, argv[1], n);
    vedit_fname[n] = 0;
    vedit_pool = malloc(VEDIT_MAX_LINES * VEDIT_LINE_MAX);
    if (!vedit_pool) {
        printf("vedit: out of memory\n");
        return 1;
    }
    vedit_used = malloc(VEDIT_MAX_LINES * sizeof(int));
    if (!vedit_used) {
        printf("vedit: out of memory\n");
        return 1;
    }
    memset(vedit_used, 0, VEDIT_MAX_LINES * sizeof(int));
    vedit_lang = vedit_lang_of(vedit_fname);
    vedit_dirty = 0;
    rc = vedit_load();
    if (rc < 0) {
        printf("vedit: file too large\n");
        return 1;
    }
    if (rc == 0) {
        printf("vedit: new file %s\n", vedit_fname);
    }
    vedit_cx = 0;
    vedit_cy = 0;
    vedit_top = 0;
    vedit_hoff = 0;
    vedit_msg[0] = 0;
    vedit_gui_run();
    free(vedit_pool);
    free(vedit_used);
    return 0;
}
