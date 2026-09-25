/** vedit IDE build and run contract.
 *
 * Ctrl+R saves the buffer then builds or runs it by extension through
 * SYS_SPAWN so the shell stays usable: .c compiles with objects/minigcc.o
 * into asm/<base>.s, .lua runs with lua, .py runs with micropython,
 * .lisp runs with lisp. Ctrl+L
 * prompts for a link format and links the compiled asm/<base>.s with
 * objects/ld.o into bin/<base>.elf or cvm/<base>.cvm. Every build drops
 * the graphics mode first so the desktop terminal stays ordered and the
 * toolchain output lands on the console, then the IDE resumes. Untitled
 * buffers highlight as C until a name with an extension is given.
 *
 * uemacs adoption (8 buffers, kill ring, macros, M-x, splits, shell):
 * ^A/^E bol/eol, M-f/M-b word motion, M-c/M-l/M-u case word, ^@ set mark,
 * M-w copy, M-k kill region, ^K kill line, ^Y yank, ^T transpose,
 * ^] goto fence, ^U universal arg, M-s/M-r isearch, M-n hunt, M-% query
 * replace, M-q fill, M-1/M-2/M-o windows, M-x command, M-! shell capture,
 * M-# filter, M-( M-) M-e macro, M-x grep + next-error. Saving writes a
 * "~" backup and refuses a disk-changed file until forced by a second
 * save. Startup runs /etc/vedit.rc then ./vedit.rc (`bind <key> <cmd>`
 * plus bare commands). Clipboard (249/250): mouse drag selects into it,
 * M-v pastes, M-W copies the region; --selftest-build proves the wire.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
#include "nuklear.h"
#include "nuklear_minios.h"
#include "nuklear_theme.h"

/** Platform syscalls vedit needs beyond the platform layer. */
static long vedit_getc_raw(long blocking) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_GETC_RAW), "D"(blocking)
                     : "rcx", "r11", "memory");
    return ret;
}

/** Set the graphics window title. */
static long vedit_set_title(const char *t) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_GFX_SET_TITLE), "D"(t)
                     : "rcx", "r11", "memory");
    return ret;
}

/** Run a program through SYS_SPAWN, preserving the IDE across the child. */
static long vedit_spawn(const char *path, const char *redir, int argc,
                        const char **argv) {
    long ret;
    register long r10 __asm__("r10") = (long)argv;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_SPAWN), "D"(path), "S"(redir),
                       "d"((long)argc), "r"(r10)
                     : "rcx", "r11", "memory");
    return ret;
}

/** Release or reclaim the display so toolchain output stays on the terminal. */
static long vedit_vga(int on) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_VGA_MODE), "D"((long)on)
                     : "rcx", "r11", "memory");
    return ret;
}

/** Force cooked keyboard mode: GETC_RAW (this editor's only key source)
 * starves while raw mode diverts PS/2 bytes to the raw queue, so vedit
 * asserts its requirement at startup instead of inheriting the
 * launcher's mode (a file-browser spawn left raw on and all keys died). */
static long vedit_kbd_raw(int on) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_KBD_RAW), "D"((long)on)
                     : "rcx", "r11", "memory");
    return ret;
}

/** Wall-clock milliseconds for the cross-frame ESC-sequence timeout. */
static unsigned long vedit_time_ms(void) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_TIME)
                     : "rcx", "r11", "memory");
    return (unsigned long)ret;
}

/** Shared clipboard: SET copies in (249), GET copies out (250). */
static long vedit_clip_set(const char *s, long len) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_CLIP_SET), "D"(s), "S"(len)
                     : "rcx", "r11", "memory");
    return ret;
}

static long vedit_clip_get(char *out, long cap) {
    long ret;
    __asm__ volatile("syscall" : "=a"(ret)
                     : "a"(MINIOS_SYS_CLIP_GET), "D"(out), "S"(cap)
                     : "rcx", "r11", "memory");
    return ret;
}

/** Central configuration: every bound, key, tool, directory and label. */
#define VEDIT_MAX_LINES 4096
#define VEDIT_LINE_MAX 256
#define VEDIT_LINE_USED (VEDIT_LINE_MAX - 1)
#define VEDIT_FILE_MAX (512 * 1024)
#define VEDIT_FNAME_MAX 64
#define VEDIT_DEFAULT_FILE "untitled"
#define VEDIT_MSG_MAX 128
#define VEDIT_WORD_MAX 32
#define VEDIT_TAB_W 4
#define VEDIT_ESC_MS 1000
#define VEDIT_FRAME_MS 8
#define VEDIT_UI_MEMORY (4 * 1024 * 1024)
#define VEDIT_KEY_RUN 18
#define VEDIT_KEY_LINK 12
#define VEDIT_KEY_DUMP 4
#define VEDIT_TOOL_MINIGCC "/objects/minigcc.o"
#define VEDIT_TOOL_LD "/objects/ld.o"
#define VEDIT_TOOL_CVM "/objects/cvm.o"
#define VEDIT_TOOL_LUA "/lua"
#define VEDIT_TOOL_PY "/micropython"
#define VEDIT_TOOL_LISP "/lisp"
#define VEDIT_DIR_ASM "/asm/"
#define VEDIT_DIR_BIN "/bin/"
#define VEDIT_DIR_CVM "/cvm/"
#define VEDIT_BUILD_LOG "/tmp/vedit.log"
#define VEDIT_LINK_ELF "elf"
#define VEDIT_LINK_CVM "cvm"
#define VEDIT_STATUS_MAX 256
#define VEDIT_BASE_MAX 48
#define VEDIT_PATH_MAX 64
#define VEDIT_LOG_TAIL 4096

/* ---- Languages ---- */
#define VEDIT_LANG_TEXT 0
#define VEDIT_LANG_C 1
#define VEDIT_LANG_PY 2
#define VEDIT_LANG_LUA 3
#define VEDIT_LANG_ASM 4
#define VEDIT_LANG_LISP 5

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

static const char *vedit_kw_lisp =
    " quote if begin define set lambda let else cond and or not car cdr cons"
    " null number string error message concat eq length at char code print"
    " println open read write close exit time ms rtc fb info vol pal pcspeaker"
    " quit minios run true false nil";

static const char *vedit_kw_asm =
    " mov movb movw movl movq movabs movzbw movzbl movzwl movzbq movzwq"
    " movsbw movsbl movswl movsbq movswq movslq lea leaq push pushq pop popq"
    " pushf popf pushfq popfq call callq ret retq leave enter jmp jmpq je jne"
    " jz jnz jl jle jg jge ja jae jb jbe js jns jo jno jp jnp jcxz jecxz loop"
    " loope loopne add addb addw addl addq sub subb subw subl subq imul mul"
    " div idiv inc dec neg not and orb or andl andq orb orl orq xor xorb xorl"
    " xorq shl shr sal sar rol ror test testb testl testq cmp cmpb cmpl cmpq"
    " cmov xchg xadd bswap cmpxchg clc stc cld std cli sti nop hlt int int3"
    " iret iretq syscall sysret sysenter sysexit in inb inw inl out outb outw"
    " outl movs movsb movsw movsl movsq stos stosb stosw stosl stosq lods"
    " lodsb lodsw lodsl lodsq scas scasb scasw scasl scasq cmps cmpsb cmpsw"
    " cmpsl cmpsq rep repz repnz repzb repzl repzq cltq cqto cqo cdq";

/* ---- Buffer: flat pool plus parallel used counts (no structs needed) ----
 * uemacs model: up to VEDIT_NBUF live buffers, each with its own pool and
 * cursor. The active buffer's state is addressed through macros so every
 * existing editing op works unchanged; switching parks nothing because the
 * state already lives per buffer. Buffer 0 is the startup buffer. */

/* ---- IDE (uemacs adoption): every new bound lives here, never inline --- */
#define VEDIT_NBUF 8
#define VEDIT_KILL_N 8
#define VEDIT_KILL_MAX 4096
#define VEDIT_MACRO_MAX 1024
#define VEDIT_HIST_N 16
#define VEDIT_CMD_MAX 48
#define VEDIT_MAGIC_MAX 128
#define VEDIT_KEY_META(c) (3000 + (c))
#define VEDIT_KEY_ARG 21
#define VEDIT_KEY_MARK 0
#define VEDIT_KEY_KILL_LINE 11
#define VEDIT_KEY_YANK 25
#define VEDIT_KEY_TRANSPOSE 20
#define VEDIT_KEY_FENCE 29
#define VEDIT_KEY_BOL 1
#define VEDIT_KEY_EOL 5
/* Forward: pure F1/F4 helpers used by the build selftest before their
 * definitions (C99, one file, no headers). */
static void vedit_str_case(char *s, int mode);
static void vedit_str_transpose(char *s, int len, int pos);
static int vedit_magic_match(const char *text, const char *pat, int *mlen);
static int vedit_cmd_lookup(const char *name);
static int vedit_parse_key(const char *s);
static void vedit_sel_clear(void);
static int vedit_clip_paste(void);
static int vedit_region_to_clip(void);
static char *vedit_pools[VEDIT_NBUF];
static int *vedit_useds[VEDIT_NBUF];
static int vedit_counts[VEDIT_NBUF];
static int vedit_cxs[VEDIT_NBUF];
static int vedit_cys[VEDIT_NBUF];
static int vedit_tops[VEDIT_NBUF];
static int vedit_hoffs[VEDIT_NBUF];
static int vedit_dirtys[VEDIT_NBUF];
static int vedit_truncs[VEDIT_NBUF];
static int vedit_langs[VEDIT_NBUF];
static int vedit_ros[VEDIT_NBUF];
static long vedit_sizes[VEDIT_NBUF];
static long vedit_mtimes[VEDIT_NBUF];
static char vedit_fnames[VEDIT_NBUF][VEDIT_FNAME_MAX];
static char vedit_msgs[VEDIT_NBUF][VEDIT_MSG_MAX];
static int vedit_cur;
#define vedit_pool (vedit_pools[vedit_cur])
#define vedit_used (vedit_useds[vedit_cur])
#define vedit_count (vedit_counts[vedit_cur])
#define vedit_cx (vedit_cxs[vedit_cur])
#define vedit_cy (vedit_cys[vedit_cur])
#define vedit_top (vedit_tops[vedit_cur])
#define vedit_hoff (vedit_hoffs[vedit_cur])
#define vedit_dirty (vedit_dirtys[vedit_cur])
#define vedit_trunc (vedit_truncs[vedit_cur])
#define vedit_lang (vedit_langs[vedit_cur])
#define vedit_fname (vedit_fnames[vedit_cur])
#define vedit_msg (vedit_msgs[vedit_cur])
static int vedit_cell[VEDIT_LINE_MAX];

/** Prompt state for find/goto/save-as/link, answered on the status row.
 * Lives up here (not with the UI) because the F2/F4 verbs open prompts. */
static int vedit_prompt_on;
static char vedit_prompt_label[16];
static char vedit_prompt_buf[VEDIT_LINE_MAX];
static int vedit_prompt_pos;
#define VEDIT_PROMPT_FIND 0
#define VEDIT_PROMPT_GOTO 1
#define VEDIT_PROMPT_NAME 2
#define VEDIT_PROMPT_LINK 3
#define VEDIT_PROMPT_CMD 4
#define VEDIT_PROMPT_ISEARCH_F 5
#define VEDIT_PROMPT_ISEARCH_R 6
#define VEDIT_PROMPT_REP_OLD 7
#define VEDIT_PROMPT_REP_NEW 8
#define VEDIT_PROMPT_QREP 9
#define VEDIT_PROMPT_SHELLCMD 10
#define VEDIT_PROMPT_FILTER 11
#define VEDIT_PROMPT_SELECT 12
#define VEDIT_PROMPT_GREP 13
#define VEDIT_PROMPT_BINDKEY 14
#define VEDIT_PROMPT_BINDCMD 15
static int vedit_prompt_mode;

/* ---- Mark, kill ring, macro, history (uemacs region.c + main.c) ---- */
static int vedit_mark_on;
static int vedit_mark_y;
static int vedit_mark_x;
static char vedit_kill[VEDIT_KILL_N][VEDIT_KILL_MAX];
static int vedit_kill_len[VEDIT_KILL_N];
static int vedit_kill_head;
static int vedit_arg;
static int vedit_arg_on;
static int vedit_overwrite;
static int vedit_macro_rec;
static int vedit_macro_len;
static int vedit_macro[VEDIT_MACRO_MAX];
static char vedit_hist[VEDIT_HIST_N][VEDIT_FNAME_MAX];
static int vedit_hist_n;
static char vedit_last_find[VEDIT_LINE_MAX];

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

/** Shared token helpers for vedit_scan_line (DRY, no behaviour change).
 *
 * Per-language quirks stay in the caller (C block comments and '#'
 * directives, Python triple-quoted strings, Lua long brackets and '--'
 * comments). Only the byte-identical pieces live here: quoted strings
 * with backslash escapes, number runs and whole-word keyword lookup.
 * allow_quote exists because C digit separators (1'000'000) are not
 * valid in Python/Lua numbers.
 */
static int vedit_parse_string(const char *t, int len, int i) {
    int q = (unsigned char)t[i];
    int j = i + 1;
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
    return j;
}

static int vedit_parse_number(const char *t, int len, int i, int allow_quote) {
    int j = i;
    int k;
    while (j < len) {
        int e = (unsigned char)t[j];
        if (vedit_is_wordc(e) || e == '.' || e == '_' ||
            (allow_quote && e == '\''))
            j++;
        else
            break;
    }
    for (k = i; k < j; k++) vedit_cell[k] = VEDIT_COL_NUMBER;
    return j;
}

static int vedit_parse_keyword(const char *t, int len, int i,
                               const char *kw_table) {
    char w[VEDIT_WORD_MAX];
    int wl = 0;
    int j = i;
    int k;
    while (j < len && vedit_is_wordc((unsigned char)t[j])) {
        if (wl < VEDIT_WORD_MAX - 1) w[wl++] = t[j];
        j++;
    }
    if (vedit_is_kw(kw_table, w, wl)) {
        for (k = i; k < j; k++) vedit_cell[k] = VEDIT_COL_KEYWORD;
    }
    return j;
}

/** Map a file name to its highlight language. */
static int vedit_lang_of(const char *fname) {
    size_t n = strlen(fname);
    if (n >= 2 && fname[n - 2] == '.') {
        if (fname[n - 1] == 'c') return VEDIT_LANG_C;
        if (fname[n - 1] == 'h') return VEDIT_LANG_C;
        if (fname[n - 1] == 's') return VEDIT_LANG_ASM;
    }
    if (n >= 3 && fname[n - 3] == '.' &&
        fname[n - 2] == 'p' && fname[n - 1] == 'y')
        return VEDIT_LANG_PY;
    if (n >= 4 && fname[n - 4] == '.' && fname[n - 3] == 'l' &&
        fname[n - 2] == 'u' && fname[n - 1] == 'a')
        return VEDIT_LANG_LUA;
    if (n >= 5 && fname[n - 5] == '.' && fname[n - 4] == 'l' &&
        fname[n - 3] == 'i' && fname[n - 2] == 's' && fname[n - 1] == 'p')
        return VEDIT_LANG_LISP;
    return VEDIT_LANG_C;
}

/** Name a highlight language for the status row. */

static const char *vedit_lang_name(int lang) {
    if (lang == VEDIT_LANG_C) return "C";
    if (lang == VEDIT_LANG_PY) return "Python";
    if (lang == VEDIT_LANG_LUA) return "Lua";
    if (lang == VEDIT_LANG_ASM) return "Asm";
    if (lang == VEDIT_LANG_LISP) return "Lisp";
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
                i = vedit_parse_string(t, len, i);
            } else if (vedit_is_digit(c)) {
                i = vedit_parse_number(t, len, i, 1);
            } else if (vedit_is_alpha(c)) {
                i = vedit_parse_keyword(t, len, i, vedit_kw_c);
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
                i = vedit_parse_string(t, len, i);
            } else if (vedit_is_digit(c)) {
                i = vedit_parse_number(t, len, i, 0);
            } else if (vedit_is_alpha(c)) {
                i = vedit_parse_keyword(t, len, i, vedit_kw_py);
            } else {
                i++;
            }
        }
        return 0;
    }
    if (vedit_lang == VEDIT_LANG_ASM) {
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
        while (i < len) {
            int c = (unsigned char)t[i];
            int d = (i + 1 < len) ? (unsigned char)t[i + 1] : 0;
            if (c == '#') {
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
                i = vedit_parse_string(t, len, i);
            } else if (c == '.') {
                j = i + 1;
                while (j < len && (vedit_is_wordc((unsigned char)t[j])))
                    j++;
                for (k = i; k < j; k++) vedit_cell[k] = VEDIT_COL_PREPROC;
                i = (j > i + 1) ? j : i + 1;
            } else if (c == '%') {
                j = i + 1;
                while (j < len && (vedit_is_wordc((unsigned char)t[j])))
                    j++;
                for (k = i; k < j; k++) vedit_cell[k] = VEDIT_COL_NUMBER;
                i = (j > i + 1) ? j : i + 1;
            } else if (vedit_is_digit(c)) {
                i = vedit_parse_number(t, len, i, 0);
            } else if (vedit_is_alpha(c) || c == '_') {
                char w[VEDIT_WORD_MAX];
                int wl = 0;
                j = i;
                while (j < len && vedit_is_wordc((unsigned char)t[j])) {
                    if (wl < VEDIT_WORD_MAX - 1) w[wl++] = t[j];
                    j++;
                }
                if (j < len && t[j] == ':') {
                    for (k = i; k <= j; k++) vedit_cell[k] = VEDIT_COL_STRING;
                    i = j + 1;
                } else if (vedit_is_kw(vedit_kw_asm, w, wl)) {
                    for (k = i; k < j; k++) vedit_cell[k] = VEDIT_COL_KEYWORD;
                    i = j;
                } else {
                    i = j;
                }
            } else {
                i++;
            }
        }
        return 0;
    }
    if (vedit_lang == VEDIT_LANG_LISP) {
        while (i < len) {
            int c = (unsigned char)t[i];
            if (c == ';') {
                for (k = i; k < len; k++) vedit_cell[k] = VEDIT_COL_COMMENT;
                break;
            } else if (c == '"') {
                i = vedit_parse_string(t, len, i);
            } else if (vedit_is_digit(c)) {
                i = vedit_parse_number(t, len, i, 0);
            } else if (vedit_is_alpha(c)) {
                i = vedit_parse_keyword(t, len, i, vedit_kw_lisp);
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
            i = vedit_parse_string(t, len, i);
        } else if (vedit_is_digit(c)) {
            i = vedit_parse_number(t, len, i, 0);
        } else if (vedit_is_alpha(c)) {
            i = vedit_parse_keyword(t, len, i, vedit_kw_lua);
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
    if (vedit_ros[vedit_cur]) {
        vedit_set_msg("buffer is read-only");
        return;
    }
    vedit_sel_clear();
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
    if (vedit_overwrite && vedit_cx < vedit_used[vedit_cy]) {
        l[vedit_cx] = (char)c;
        vedit_cx++;
        vedit_dirty = 1;
        vedit_msg[0] = 0;
        return;
    }
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
    if (vedit_ros[vedit_cur]) {
        vedit_set_msg("buffer is read-only");
        return;
    }
    vedit_sel_clear();
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
    if (vedit_ros[vedit_cur]) {
        vedit_set_msg("buffer is read-only");
        return;
    }
    vedit_sel_clear();
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
    if (vedit_ros[vedit_cur]) {
        vedit_set_msg("buffer is read-only");
        return;
    }
    vedit_sel_clear();
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
    if (vedit_ros[vedit_cur]) {
        vedit_set_msg("buffer is read-only");
        return;
    }
    vedit_sel_clear();
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

/* ---- uemacs F1: pure helpers (mirrored by make test-vedit) ---- */

/** Upper/lower/capitalize a NUL string in place; mode 1=upper, 2=lower,
 * 3=capitalize. Pure: the host suite mirrors it byte for byte. */
static void vedit_str_case(char *s, int mode) {
    int i = 0;
    int new_word = 1;
    if (!s || (mode != 1 && mode != 2 && mode != 3)) return;
    while (s[i]) {
        int c = (unsigned char)s[i];
        if (c == ' ' || c == '\t' || c == '\n') {
            new_word = 1;
        } else if (mode == 1) {
            if (c >= 'a' && c <= 'z') s[i] = (char)(c - 32);
            new_word = 0;
        } else if (mode == 2) {
            if (c >= 'A' && c <= 'Z') s[i] = (char)(c + 32);
            new_word = 0;
        } else {
            if (new_word) {
                if (c >= 'a' && c <= 'z') s[i] = (char)(c - 32);
                new_word = 0;
            } else {
                if (c >= 'A' && c <= 'Z') s[i] = (char)(c + 32);
            }
        }
        i++;
    }
}

/** Transpose two adjacent bytes around dot; pure string core of ^T. */
static void vedit_str_transpose(char *s, int len, int pos) {
    char t;
    if (!s || len < 2 || pos < 1 || pos >= len) return;
    t = s[pos - 1];
    s[pos - 1] = s[pos];
    s[pos] = t;
}

/** Minimal magic matcher (uemacs search.c subset): '.' any, '*' repeat,
 * '^'/'$' anchors, '[...]' classes with ranges and '^' negation. Returns 1
 * on a match of pat against the prefix of text, with *mlen set to the
 * matched length. Pure: host suite pins every vector. */
static int vedit_magic_class(int c, const char *cls) {
    int neg = 0;
    int hit = 0;
    if (!cls || cls[0] != '[') return 0;
    cls++;
    if (*cls == '^') {
        neg = 1;
        cls++;
    }
    while (*cls && *cls != ']') {
        if (cls[1] == '-' && cls[2] && cls[2] != ']') {
            if (c >= (unsigned char)cls[0] && c <= (unsigned char)cls[2])
                hit = 1;
            cls += 3;
        } else {
            if (c == (unsigned char)*cls) hit = 1;
            cls++;
        }
    }
    return neg ? !hit : hit;
}

static int vedit_magic_atom(const char *pat, int c, int *atom_len) {
    if (!pat || !pat[0] || c < 0) return 0;
    if (pat[0] == '.') {
        *atom_len = 1;
        return 1;
    }
    if (pat[0] == '[') {
        int k = 1;
        if (pat[k] == '^') k++;
        if (pat[k] == ']') k++;
        while (pat[k] && pat[k] != ']') k++;
        if (!pat[k]) return 0;
        *atom_len = k + 1;
        return vedit_magic_class(c, pat);
    }
    if (pat[0] == '\\' && pat[1]) {
        *atom_len = 2;
        return c == (unsigned char)pat[1];
    }
    *atom_len = 1;
    return c == (unsigned char)pat[0];
}

static int vedit_magic_here(const char *text, const char *pat, int *mlen) {
    int total = 0;
    if (!text || !pat || !mlen) return 0;
    if (pat[0] == '$' && pat[1] == 0) {
        *mlen = 0;
        return text[0] == 0;
    }
    while (pat[0]) {
        int alen = 0;
        int star = 0;
        if (pat[0] == '$' && pat[1] == 0) {
            *mlen = total;
            return text[0] == 0;
        }
        if (pat[0] == '[') {
            int k = 1;
            if (pat[k] == '^') k++;
            if (pat[k] == ']') k++;
            while (pat[k] && pat[k] != ']') k++;
            if (!pat[k]) return 0;
            alen = k + 1;
        } else if (pat[0] == '\\' && pat[1]) {
            alen = 2;
        } else {
            alen = 1;
        }
        star = (pat[alen] == '*');
        if (!star) {
            if (!text[0]) return 0;
            if (!vedit_magic_atom(pat, (unsigned char)text[0], &alen))
                return 0;
            text++;
            total++;
            pat += alen;
        } else {
            const char *rest = pat + alen + 1;
            int max = 0;
            int k;
            while (text[max]) {
                int dummy = 0;
                if (!vedit_magic_atom(pat, (unsigned char)text[max],
                                      &dummy))
                    break;
                max++;
            }
            for (k = max; k >= 0; k--) {
                int sub = 0;
                if (vedit_magic_here(text + k, rest, &sub)) {
                    *mlen = total + k + sub;
                    return 1;
                }
                if (k == 0) break;
            }
            return 0;
        }
    }
    *mlen = total;
    return 1;
}

/** Match pat anywhere in text; anchored when pat starts with '^'. */
static int vedit_magic_match(const char *text, const char *pat, int *mlen) {
    int off = 0;
    int anchored = 0;
    if (!text || !pat || !mlen) return 0;
    if (pat[0] == '^') {
        anchored = 1;
        pat++;
    }
    if (anchored) return vedit_magic_here(text, pat, mlen);
    while (text[off]) {
        int sub = 0;
        if (vedit_magic_here(text + off, pat, &sub)) {
            *mlen = sub;
            return 1;
        }
        off++;
    }
    {
        int sub = 0;
        if (vedit_magic_here(text + off, pat, &sub)) {
            *mlen = sub;
            return 1;
        }
    }
    return 0;
}

/* ---- uemacs F1: buffers, mark, kill ring, word ops, fence ---- */

static int vedit_buf_alloc(int idx) {
    if (idx < 0 || idx >= VEDIT_NBUF) return -1;
    if (vedit_pools[idx]) return 0;
    vedit_pools[idx] = malloc(VEDIT_MAX_LINES * VEDIT_LINE_MAX);
    if (!vedit_pools[idx]) return -1;
    vedit_useds[idx] = malloc(VEDIT_MAX_LINES * sizeof(int));
    if (!vedit_useds[idx]) {
        free(vedit_pools[idx]);
        vedit_pools[idx] = 0;
        return -1;
    }
    memset(vedit_useds[idx], 0, VEDIT_MAX_LINES * sizeof(int));
    return 0;
}

/** Parked-cursor buffer switch: state already lives per buffer, so this
 * only retargets the macros and clears the mark (a mark never spans
 * buffers, exactly like uemacs). */
static int vedit_switch_buffer(int idx) {
    if (idx < 0 || idx >= VEDIT_NBUF) return -1;
    if (!vedit_pools[idx]) return -1;
    vedit_cur = idx;
    vedit_mark_on = 0;
    vedit_sel_clear();
    vedit_msg[0] = 0;
    return 0;
}

static int vedit_next_buffer(void) {
    int k;
    for (k = 1; k <= VEDIT_NBUF; k++) {
        int idx = (vedit_cur + k) % VEDIT_NBUF;
        if (vedit_pools[idx]) {
            vedit_switch_buffer(idx);
            return 0;
        }
    }
    return -1;
}

static int vedit_open_in_buffer(const char *fname, int ro);

static void vedit_hist_push(const char *fname) {
    size_t n;
    int k;
    if (!fname || !fname[0]) return;
    n = strlen(fname);
    if (n >= VEDIT_FNAME_MAX) return;
    for (k = 0; k < vedit_hist_n; k++) {
        if (strcmp(vedit_hist[k], fname) == 0) return;
    }
    if (vedit_hist_n < VEDIT_HIST_N) {
        memcpy(vedit_hist[vedit_hist_n], fname, n + 1);
        vedit_hist_n++;
    } else {
        for (k = 0; k < VEDIT_HIST_N - 1; k++)
            memcpy(vedit_hist[k], vedit_hist[k + 1], VEDIT_FNAME_MAX);
        memcpy(vedit_hist[VEDIT_HIST_N - 1], fname, n + 1);
    }
}

static void vedit_set_mark(void) {
    vedit_mark_on = 1;
    vedit_mark_y = vedit_cy;
    vedit_mark_x = vedit_cx;
    vedit_set_msg("mark set");
}

/** Region bounds in buffer order; returns 0 when no usable region. */
static int vedit_region(int *y0, int *x0, int *y1, int *x1) {
    if (!vedit_mark_on || !y0 || !x0 || !y1 || !x1) return 0;
    *y0 = vedit_mark_y;
    *x0 = vedit_mark_x;
    *y1 = vedit_cy;
    *x1 = vedit_cx;
    if (*y0 > *y1 || (*y0 == *y1 && *x0 > *x1)) {
        int t = *y0;
        *y0 = *y1;
        *y1 = t;
        t = *x0;
        *x0 = *x1;
        *x1 = t;
    }
    if (*y0 == *y1 && *x0 == *x1) return 0;
    if (*y0 >= vedit_count) return 0;
    if (*y1 >= vedit_count) *y1 = vedit_count - 1;
    return 1;
}

/** Copy the region into the kill ring head (uemacs copy-region). */
static int vedit_copy_region(void) {
    int y0;
    int x0;
    int y1;
    int x1;
    int y;
    int pos = 0;
    if (!vedit_region(&y0, &x0, &y1, &x1)) {
        vedit_set_msg("no region");
        return -1;
    }
    vedit_kill_head = (vedit_kill_head + 1) % VEDIT_KILL_N;
    for (y = y0; y <= y1 && pos < VEDIT_KILL_MAX - 1; y++) {
        int a = (y == y0) ? x0 : 0;
        int b = (y == y1) ? x1 : vedit_used[y];
        int k;
        if (a > vedit_used[y]) a = vedit_used[y];
        if (b > vedit_used[y]) b = vedit_used[y];
        for (k = a; k < b && pos < VEDIT_KILL_MAX - 1; k++)
            vedit_kill[vedit_kill_head][pos++] = vedit_row_ptr(y)[k];
        if (y < y1 && pos < VEDIT_KILL_MAX - 1)
            vedit_kill[vedit_kill_head][pos++] = '\n';
    }
    vedit_kill[vedit_kill_head][pos] = 0;
    vedit_kill_len[vedit_kill_head] = pos;
    vedit_set_msg("copied");
    return 0;
}

/** Delete the region after copying it (uemacs kill-region). */
static int vedit_kill_region(void) {
    int y0;
    int x0;
    int y1;
    int x1;
    int y;
    int k;
    int tail;
    if (vedit_ros[vedit_cur]) {
        vedit_set_msg("buffer is read-only");
        return -1;
    }
    vedit_sel_clear();
    if (vedit_copy_region() != 0) return -1;
    if (y0 < 0 || y1 >= vedit_count) return -1;
    if (y0 == y1) {
        char *l = vedit_row_ptr(y0);
        if (x0 > vedit_used[y0]) x0 = vedit_used[y0];
        if (x1 > vedit_used[y0]) x1 = vedit_used[y0];
        for (k = x1; k < vedit_used[y0]; k++) l[x0 + k - x1] = l[k];
        vedit_used[y0] -= (x1 - x0);
        vedit_cy = y0;
        vedit_cx = x0;
    } else {
        char *first = vedit_row_ptr(y0);
        char *last = vedit_row_ptr(y1);
        if (x0 > vedit_used[y0]) x0 = vedit_used[y0];
        if (x1 > vedit_used[y1]) x1 = vedit_used[y1];
        tail = vedit_used[y1] - x1;
        if (x0 + tail > VEDIT_LINE_USED) {
            vedit_set_msg("line too long to join");
            return -1;
        }
        for (k = 0; k < tail; k++) first[x0 + k] = last[x1 + k];
        vedit_used[y0] = x0 + tail;
        for (y = y1; y > y0; y--) vedit_delete_line_at(y);
        vedit_cy = y0;
        vedit_cx = x0;
    }
    vedit_mark_on = 0;
    vedit_dirty = 1;
    vedit_set_msg("killed");
    return 0;
}

/** Kill to end of line, or the newline itself when already at it. */
static int vedit_kill_line(void) {
    char *l;
    int n;
    int k;
    if (vedit_ros[vedit_cur]) {
        vedit_set_msg("buffer is read-only");
        return -1;
    }
    if (vedit_count <= 0 || vedit_cy >= vedit_count) return -1;
    l = vedit_row_ptr(vedit_cy);
    vedit_kill_head = (vedit_kill_head + 1) % VEDIT_KILL_N;
    if (vedit_cx < vedit_used[vedit_cy]) {
        n = vedit_used[vedit_cy] - vedit_cx;
        if (n > VEDIT_KILL_MAX - 1) n = VEDIT_KILL_MAX - 1;
        for (k = 0; k < n; k++)
            vedit_kill[vedit_kill_head][k] = l[vedit_cx + k];
        vedit_kill[vedit_kill_head][n] = 0;
        vedit_kill_len[vedit_kill_head] = n;
        vedit_used[vedit_cy] = vedit_cx;
    } else {
        if (vedit_cy + 1 >= vedit_count) {
            vedit_set_msg("nothing to kill");
            return -1;
        }
        vedit_kill[vedit_kill_head][0] = '\n';
        vedit_kill[vedit_kill_head][1] = 0;
        vedit_kill_len[vedit_kill_head] = 1;
        vedit_delete_char();
        vedit_set_msg("killed");
        vedit_dirty = 1;
        return 0;
    }
    vedit_dirty = 1;
    vedit_set_msg("killed");
    return 0;
}

/** Yank the ring head at dot (uemacs yank). */
static int vedit_yank(void) {
    const char *s;
    int k;
    if (vedit_ros[vedit_cur]) {
        vedit_set_msg("buffer is read-only");
        return -1;
    }
    if (vedit_kill_len[vedit_kill_head] <= 0) {
        vedit_set_msg("kill ring empty");
        return -1;
    }
    s = vedit_kill[vedit_kill_head];
    for (k = 0; s[k]; k++) {
        if (s[k] == '\n') {
            vedit_cx = vedit_used[vedit_cy];
            vedit_split();
            if (vedit_msg[0]) return -1;
        } else {
            if (vedit_overwrite && vedit_cx < vedit_used[vedit_cy]) {
                vedit_row_ptr(vedit_cy)[vedit_cx] = s[k];
                vedit_cx++;
                vedit_dirty = 1;
            } else {
                vedit_insert_char((unsigned char)s[k]);
                if (vedit_msg[0]) return -1;
            }
        }
    }
    vedit_msg[0] = 0;
    return 0;
}

/** Word motion core: dir +1 forward, -1 back. */
static int vedit_word_move(int dir) {
    if (vedit_count <= 0) return -1;
    if (dir > 0) {
        char *l = vedit_row_ptr(vedit_cy);
        while (vedit_cx < vedit_used[vedit_cy] &&
               !vedit_is_wordc((unsigned char)l[vedit_cx]))
            vedit_cx++;
        while (vedit_cx < vedit_used[vedit_cy] &&
               vedit_is_wordc((unsigned char)l[vedit_cx]))
            vedit_cx++;
        if (vedit_cx < vedit_used[vedit_cy]) return 0;
        if (vedit_cy + 1 >= vedit_count) return 0;
        vedit_cy++;
        vedit_cx = 0;
        return 0;
    }
    {
        char *l = vedit_row_ptr(vedit_cy);
        if (vedit_cx == 0) {
            if (vedit_cy == 0) return 0;
            vedit_cy--;
            vedit_cx = vedit_used[vedit_cy];
            return 0;
        }
        while (vedit_cx > 0 &&
               !vedit_is_wordc((unsigned char)l[vedit_cx - 1]))
            vedit_cx--;
        while (vedit_cx > 0 &&
               vedit_is_wordc((unsigned char)l[vedit_cx - 1]))
            vedit_cx--;
        return 0;
    }
}

/** Apply case mode to the word at/after dot (uemacs word.c). */
static int vedit_case_word(int mode) {
    char *l;
    int start;
    int end;
    int k;
    if (vedit_ros[vedit_cur]) {
        vedit_set_msg("buffer is read-only");
        return -1;
    }
    if (vedit_count <= 0 || vedit_cy >= vedit_count) return -1;
    l = vedit_row_ptr(vedit_cy);
    start = vedit_cx;
    while (start < vedit_used[vedit_cy] &&
           !vedit_is_wordc((unsigned char)l[start]))
        start++;
    end = start;
    while (end < vedit_used[vedit_cy] &&
           vedit_is_wordc((unsigned char)l[end]))
        end++;
    if (end <= start) {
        vedit_set_msg("no word");
        return -1;
    }
    for (k = start; k < end; k++) {
        int c = (unsigned char)l[k];
        if (mode == 1 && c >= 'a' && c <= 'z') l[k] = (char)(c - 32);
        else if (mode == 2 && c >= 'A' && c <= 'Z') l[k] = (char)(c + 32);
        else if (mode == 3) {
            if (k == start && c >= 'a' && c <= 'z') l[k] = (char)(c - 32);
            if (k > start && c >= 'A' && c <= 'Z') l[k] = (char)(c + 32);
        }
    }
    vedit_cx = end;
    vedit_dirty = 1;
    vedit_msg[0] = 0;
    return 0;
}

/** Transpose the two characters around dot (uemacs random.c). */
static int vedit_transpose(void) {
    char *l;
    if (vedit_ros[vedit_cur]) {
        vedit_set_msg("buffer is read-only");
        return -1;
    }
    if (vedit_count <= 0 || vedit_cy >= vedit_count) return -1;
    l = vedit_row_ptr(vedit_cy);
    if (vedit_used[vedit_cy] < 2) {
        vedit_set_msg("nothing to transpose");
        return -1;
    }
    if (vedit_cx <= 0) vedit_cx = 1;
    if (vedit_cx >= vedit_used[vedit_cy])
        vedit_cx = vedit_used[vedit_cy] - 1;
    vedit_str_transpose(l, vedit_used[vedit_cy], vedit_cx);
    if (vedit_cx < vedit_used[vedit_cy]) vedit_cx++;
    vedit_dirty = 1;
    vedit_msg[0] = 0;
    return 0;
}

/** Jump to the fence matching the one under dot (uemacs random.c). */
static int vedit_goto_fence(void) {
    char open = 0;
    char close = 0;
    int dir = 0;
    int depth = 0;
    int y;
    int x;
    char *l;
    if (vedit_count <= 0 || vedit_cy >= vedit_count) return -1;
    l = vedit_row_ptr(vedit_cy);
    if (vedit_cx < vedit_used[vedit_cy]) {
        char c = l[vedit_cx];
        if (c == '(' || c == '[' || c == '{') {
            open = c;
            close = (c == '(') ? ')' : (c == '[') ? ']' : '}';
            dir = 1;
        } else if (c == ')' || c == ']' || c == '}') {
            close = c;
            open = (c == ')') ? '(' : (c == ']') ? '[' : '{';
            dir = -1;
        }
    }
    if (!dir) {
        vedit_set_msg("no fence under cursor");
        return -1;
    }
    y = vedit_cy;
    x = vedit_cx;
    while (1) {
        if (dir > 0) {
            x++;
            if (x >= vedit_used[y]) {
                y++;
                x = -1;
                if (y >= vedit_count) break;
                continue;
            }
        } else {
            x--;
            if (x < 0) {
                y--;
                if (y < 0) break;
                x = vedit_used[y] - 1;
                if (x < 0) continue;
                continue;
            }
        }
        {
            char c = vedit_row_ptr(y)[x];
            if (c == open) depth++;
            else if (c == close) {
                if (depth == 0) {
                    vedit_cy = y;
                    vedit_cx = x;
                    vedit_msg[0] = 0;
                    return 0;
                }
                depth--;
            }
        }
    }
    vedit_set_msg("no match");
    return -1;
}

/** Count words/lines/chars from dot to end, emacs-style, into msg. */
static void vedit_count_words(void) {
    int y;
    int words = 0;
    int lines = 0;
    int chars = 0;
    int in_word = 0;
    char nb[96];
    for (y = vedit_cy; y < vedit_count; y++) {
        char *l = vedit_row_ptr(y);
        int a = (y == vedit_cy) ? vedit_cx : 0;
        int k;
        lines++;
        for (k = a; k < vedit_used[y]; k++) {
            chars++;
            if (vedit_is_wordc((unsigned char)l[k])) {
                if (!in_word) {
                    words++;
                    in_word = 1;
                }
            } else {
                in_word = 0;
            }
        }
        chars++;
        in_word = 0;
    }
    snprintf(nb, sizeof(nb), "words=%d lines=%d chars=%d", words, lines,
             chars);
    vedit_set_msg(nb);
    printf("vedit: %s\n", nb);
}

/* ---- uemacs F2: magic search, isearch, replace, fill ---- */
#define VEDIT_FILL_COL 72

static int vedit_isearch_oy;
static int vedit_isearch_ox;
static int vedit_isearch_dir;
static int vedit_qrep_on;
static char vedit_qrep_old[VEDIT_MAGIC_MAX];
static char vedit_qrep_new[VEDIT_LINE_MAX];

/** Match needle at line/col; magic when flag set. Returns match length. */
static int vedit_match_at(int row, int col, const char *needle, int magic,
                          int *mlen) {
    char *l;
    int nlen;
    int k;
    if (!needle || !needle[0] || !mlen) return 0;
    if (row < 0 || row >= vedit_count) return 0;
    l = vedit_row_ptr(row);
    if (col < 0 || col > vedit_used[row]) return 0;
    if (!magic) {
        nlen = (int)strlen(needle);
        if (col + nlen > vedit_used[row]) return 0;
        for (k = 0; k < nlen; k++) {
            if ((unsigned char)l[col + k] != (unsigned char)needle[k])
                return 0;
        }
        *mlen = nlen;
        return 1;
    }
    {
        char tmp[VEDIT_LINE_MAX + 1];
        int m = 0;
        int avail = vedit_used[row] - col;
        if (avail > VEDIT_LINE_MAX) avail = VEDIT_LINE_MAX;
        for (k = 0; k < avail; k++) tmp[k] = l[col + k];
        tmp[avail] = 0;
        if (!vedit_magic_match(tmp, needle, &m)) return 0;
        if (m == 0) {
            *mlen = 0;
            return 1;
        }
        *mlen = m;
        return 1;
    }
}

/** Forward search from (row,col); wraps once. Moves dot, returns 0. */
static int vedit_search_fwd(int row, int col, const char *needle, int magic,
                            int *wrapped) {
    int r;
    int c;
    int mlen = 0;
    int start_r = row;
    int start_c = col;
    if (wrapped) *wrapped = 0;
    for (r = row; r < vedit_count; r++) {
        c = (r == row) ? col : 0;
        for (; c <= vedit_used[r]; c++) {
            if (vedit_match_at(r, c, needle, magic, &mlen) && mlen > 0) {
                vedit_cy = r;
                vedit_cx = c;
                return 0;
            }
        }
    }
    for (r = 0; r <= start_r && r < vedit_count; r++) {
        int end = (r == start_r) ? start_c : vedit_used[r];
        for (c = 0; c < end; c++) {
            if (vedit_match_at(r, c, needle, magic, &mlen) && mlen > 0) {
                vedit_cy = r;
                vedit_cx = c;
                if (wrapped) *wrapped = 1;
                return 0;
            }
        }
    }
    return -1;
}

static int vedit_search_rev(int row, int col, const char *needle, int magic) {
    int r;
    int c;
    int mlen = 0;
    int best_r = -1;
    int best_c = -1;
    for (r = 0; r <= row && r < vedit_count; r++) {
        int end = (r == row) ? col : vedit_used[r] + 1;
        for (c = 0; c < end; c++) {
            if (vedit_match_at(r, c, needle, magic, &mlen) && mlen > 0) {
                best_r = r;
                best_c = c;
            }
        }
    }
    if (best_r >= 0) {
        vedit_cy = best_r;
        vedit_cx = best_c;
        return 0;
    }
    return -1;
}

static void vedit_isearch_step(void) {
    int w = 0;
    if (!vedit_prompt_buf[0]) {
        vedit_cy = vedit_isearch_oy;
        vedit_cx = vedit_isearch_ox;
        vedit_msg[0] = 0;
        return;
    }
    if (vedit_isearch_dir > 0) {
        if (vedit_search_fwd(vedit_isearch_oy, vedit_isearch_ox,
                             vedit_prompt_buf, 0, &w) != 0)
            vedit_set_msg("failing");
        else if (w)
            vedit_set_msg("wrapped");
        else
            vedit_msg[0] = 0;
    } else {
        if (vedit_search_rev(vedit_isearch_oy, vedit_isearch_ox,
                             vedit_prompt_buf, 0) != 0)
            vedit_set_msg("failing");
        else
            vedit_msg[0] = 0;
    }
    memcpy(vedit_last_find, vedit_prompt_buf, VEDIT_LINE_MAX);
}

/** Replace one occurrence at (row,col); returns new cursor col or -1. */
static int vedit_replace_at(int row, int col, const char *old_s,
                            const char *new_s, int magic) {
    char *l;
    int mlen = 0;
    int nlen;
    int k;
    if (!vedit_match_at(row, col, old_s, magic, &mlen) || mlen <= 0)
        return -1;
    l = vedit_row_ptr(row);
    nlen = (int)strlen(new_s);
    if (vedit_used[row] - mlen + nlen > VEDIT_LINE_USED) return -1;
    for (k = vedit_used[row] - 1; k >= col + mlen; k--)
        l[k - mlen + nlen] = l[k];
    for (k = 0; k < nlen; k++) l[col + k] = new_s[k];
    vedit_used[row] += nlen - mlen;
    vedit_dirty = 1;
    return col + nlen;
}

/** Replace all, forward from dot with wrap; reports count, fail closed. */
static int vedit_replace_all(const char *old_s, const char *new_s,
                             int magic) {
    int count = 0;
    int guard = 0;
    int r = vedit_cy;
    int c = vedit_cx;
    int mlen = 0;
    if (!old_s || !old_s[0] || !new_s) {
        vedit_set_msg("usage: old and new text");
        return -1;
    }
    if (vedit_ros[vedit_cur]) {
        vedit_set_msg("buffer is read-only");
        return -1;
    }
    while (guard++ < VEDIT_MAX_LINES * 4) {
        int nc;
        if (!vedit_match_at(r, c, old_s, magic, &mlen) || mlen <= 0) {
            c++;
            if (c > vedit_used[r]) {
                r++;
                c = 0;
                if (r >= vedit_count) break;
            }
            continue;
        }
        nc = vedit_replace_at(r, c, old_s, new_s, magic);
        if (nc < 0) {
            c++;
            if (c > vedit_used[r]) {
                r++;
                c = 0;
                if (r >= vedit_count) break;
            }
            continue;
        }
        count++;
        c = nc;
        if (c > vedit_used[r]) {
            r++;
            c = 0;
            if (r >= vedit_count) break;
        }
    }
    {
        char nb[64];
        snprintf(nb, sizeof(nb), "replaced %d", count);
        vedit_set_msg(nb);
    }
    return 0;
}

/** Refill the blank-line-delimited paragraph at dot (uemacs word.c). */
static int vedit_fill_paragraph(void) {
    int top;
    int bot;
    int y;
    int k;
    char words[VEDIT_FILE_MAX / 8];
    int wpos = 0;
    int wstart;
    int col;
    int first;
    if (vedit_ros[vedit_cur]) {
        vedit_set_msg("buffer is read-only");
        return -1;
    }
    if (vedit_count <= 0) return -1;
    top = vedit_cy;
    while (top > 0 && vedit_used[top - 1] > 0) top--;
    bot = vedit_cy;
    while (bot + 1 < vedit_count && vedit_used[bot + 1] > 0) bot++;
    for (y = top; y <= bot; y++) {
        char *l = vedit_row_ptr(y);
        for (k = 0; k < vedit_used[y] && wpos < (int)sizeof(words) - 1;
             k++) {
            if (l[k] == ' ' || l[k] == '\t') {
                if (wpos > 0 && words[wpos - 1] != ' ')
                    words[wpos++] = ' ';
            } else {
                words[wpos++] = l[k];
            }
        }
    }
    while (wpos > 0 && words[wpos - 1] == ' ') wpos--;
    words[wpos] = 0;
    while (top < bot) {
        vedit_delete_line_at(top);
        bot--;
    }
    vedit_used[top] = 0;
    vedit_cy = top;
    vedit_cx = 0;
    col = 0;
    first = 1;
    wstart = 0;
    while (words[wstart]) {
        int wend = wstart;
        int wlen;
        while (words[wend] && words[wend] != ' ') wend++;
        wlen = wend - wstart;
        if (!first && col + 1 + wlen > VEDIT_FILL_COL) {
            if (vedit_count >= VEDIT_MAX_LINES) {
                vedit_set_msg("buffer full");
                return -1;
            }
            vedit_cy = top;
            vedit_cx = vedit_used[top];
            vedit_split();
            if (vedit_msg[0]) return -1;
            top++;
            vedit_cy = top;
            vedit_cx = 0;
            col = 0;
            first = 1;
        }
        if (!first) {
            vedit_row_ptr(top)[vedit_used[top]++] = ' ';
            col++;
        }
        for (k = 0; k < wlen; k++) {
            if (vedit_used[top] >= VEDIT_LINE_USED) {
                vedit_set_msg("line full");
                return -1;
            }
            vedit_row_ptr(top)[vedit_used[top]++] = words[wstart + k];
            col++;
        }
        first = 0;
        wstart = wend;
        while (words[wstart] == ' ') wstart++;
    }
    vedit_dirty = 1;
    vedit_msg[0] = 0;
    return 0;
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
    if (nlen >= VEDIT_LINE_MAX) nlen = VEDIT_LINE_MAX - 1;
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
                int q;
                vedit_cy = r;
                vedit_cx = k;
                vedit_msg[0] = 0;
                for (q = 0; q < nlen; q++)
                    vedit_last_find[q] = needle[q];
                vedit_last_find[nlen] = 0;
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

static int vedit_armed[VEDIT_NBUF];

/** Copy the on-disk file to its "~" backup; 0 ok, -1 when there is
 * nothing to back up or the copy fails (fail closed, save continues). */
static int vedit_backup(void) {
    char bak[VEDIT_FNAME_MAX];
    size_t n;
    FILE *in;
    FILE *out;
    char chunk[512];
    size_t r;
    n = strlen(vedit_fname);
    if (n + 1 >= VEDIT_FNAME_MAX) return -1;
    memcpy(bak, vedit_fname, n);
    bak[n] = '~';
    bak[n + 1] = 0;
    in = fopen(vedit_fname, "r");
    if (!in) return -1;
    out = fopen(bak, "w");
    if (!out) {
        fclose(in);
        return -1;
    }
    while ((r = fread(chunk, 1, sizeof(chunk), in)) > 0) {
        if (fwrite(chunk, 1, r, out) != r) {
            fclose(in);
            fclose(out);
            return -1;
        }
    }
    fclose(in);
    if (fclose(out) != 0) return -1;
    return 0;
}

static int vedit_save(void) {
    FILE *f;
    int i;
    struct stat st;
    if (vedit_trunc) {
        vedit_set_msg("refusing to save: file did not fit in the buffer");
        return -1;
    }
    if (vedit_ros[vedit_cur]) {
        vedit_set_msg("buffer is read-only");
        return -1;
    }
    if (stat(vedit_fname, &st) == 0 && vedit_sizes[vedit_cur] >= 0 &&
        (st.st_size != vedit_sizes[vedit_cur] ||
         st.st_mtime != vedit_mtimes[vedit_cur]) &&
        !vedit_armed[vedit_cur]) {
        vedit_armed[vedit_cur] = 1;
        vedit_set_msg("file changed on disk; save again to force");
        return -1;
    }
    vedit_armed[vedit_cur] = 0;
    vedit_backup();
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
        struct stat st;
        snprintf(nb, sizeof(nb), "wrote %d line(s) to %s",
                 vedit_count, vedit_fname);
        vedit_set_msg(nb);
        if (stat(vedit_fname, &st) == 0) {
            vedit_sizes[vedit_cur] = (long)st.st_size;
            vedit_mtimes[vedit_cur] = (long)st.st_mtime;
        }
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
    if (!f) {
        vedit_sizes[vedit_cur] = -1;
        vedit_mtimes[vedit_cur] = -1;
        return 0;
    }
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
    {
        struct stat st;
        if (stat(vedit_fname, &st) == 0) {
            vedit_sizes[vedit_cur] = (long)st.st_size;
            vedit_mtimes[vedit_cur] = (long)st.st_mtime;
        } else {
            vedit_sizes[vedit_cur] = -1;
            vedit_mtimes[vedit_cur] = -1;
        }
    }
    return 1;
}

/** Open a file in a free buffer (or reuse the pristine untitled one). */
static int vedit_open_in_buffer(const char *fname, int ro) {
    int idx = -1;
    int k;
    size_t n;
    if (!fname || !fname[0]) {
        vedit_set_msg("empty name");
        return -1;
    }
    n = strlen(fname);
    if (n >= VEDIT_FNAME_MAX) {
        vedit_set_msg("name too long");
        return -1;
    }
    for (k = 0; k < VEDIT_NBUF; k++) {
        if (vedit_pools[k] && strcmp(vedit_fnames[k], fname) == 0) {
            vedit_switch_buffer(k);
            vedit_ros[k] = ro;
            return k;
        }
    }
    if (vedit_count == 0 && !vedit_dirty &&
        strcmp(vedit_fname, VEDIT_DEFAULT_FILE) == 0)
        idx = vedit_cur;
    else {
        for (k = 0; k < VEDIT_NBUF; k++) {
            if (!vedit_pools[k] && vedit_buf_alloc(k) != 0) {
                vedit_set_msg("out of memory");
                return -1;
            }
            if (vedit_counts[k] == 0 && !vedit_dirtys[k]) {
                idx = k;
                break;
            }
        }
        if (idx < 0) {
            vedit_set_msg("no free buffer (8 max)");
            return -1;
        }
    }
    vedit_switch_buffer(idx);
    memcpy(vedit_fname, fname, n + 1);
    vedit_lang = vedit_lang_of(vedit_fname);
    vedit_ros[idx] = ro;
    vedit_hist_push(fname);
    vedit_load();
    vedit_cx = 0;
    vedit_cy = 0;
    vedit_top = 0;
    vedit_hoff = 0;
    vedit_mark_on = 0;
    return idx;
}

/** Insert a file at dot, char by char through the fail-closed ops. */
static int vedit_insert_file(const char *fname) {
    FILE *f;
    long size;
    char *data;
    size_t n;
    size_t k;
    if (vedit_ros[vedit_cur]) {
        vedit_set_msg("buffer is read-only");
        return -1;
    }
    f = fopen(fname, "r");
    if (!f) {
        vedit_set_msg("cannot read file");
        return -1;
    }
    if (fseek(f, 0, SEEK_END) != 0) {
        fclose(f);
        vedit_set_msg("cannot read file");
        return -1;
    }
    size = ftell(f);
    if (size < 0 || size > VEDIT_FILE_MAX) {
        fclose(f);
        vedit_set_msg("file too large");
        return -1;
    }
    if (fseek(f, 0, SEEK_SET) != 0) {
        fclose(f);
        vedit_set_msg("cannot read file");
        return -1;
    }
    if (size == 0) {
        fclose(f);
        vedit_set_msg("empty file");
        return 0;
    }
    data = malloc((size_t)size);
    if (!data) {
        fclose(f);
        vedit_set_msg("out of memory");
        return -1;
    }
    n = fread(data, 1, (size_t)size, f);
    fclose(f);
    for (k = 0; k < n; k++) {
        if (data[k] == '\n' || data[k] == '\r') {
            if (data[k] == '\r') continue;
            vedit_split();
        } else {
            vedit_insert_char((unsigned char)data[k]);
        }
        if (vedit_msg[0]) {
            free(data);
            vedit_set_msg("insert stopped: buffer full");
            return -1;
        }
    }
    free(data);
    vedit_msg[0] = 0;
    return 0;
}

/** Report whether a file name ends with the given extension. */
static int vedit_has_ext(const char *fname, const char *ext) {
    size_t n = strlen(fname);
    size_t e = strlen(ext);
    size_t k;
    if (e == 0 || e > n) return 0;
    for (k = 0; k < e; k++) {
        if (fname[n - e + k] != ext[k]) return 0;
    }
    return 1;
}

/** Copy the base name without directories or extension into dst. */
static int vedit_base_of(const char *fname, char *dst, size_t cap) {
    size_t n = strlen(fname);
    size_t s = 0;
    size_t e = n;
    size_t k;
    size_t len;
    for (k = 0; k < n; k++) {
        if (fname[k] == '/') s = k + 1;
    }
    for (k = s; k < n; k++) {
        if (fname[k] == '.') e = k;
    }
    if (e <= s) e = n;
    len = e - s;
    if (len == 0 || len + 1 > cap || len >= VEDIT_BASE_MAX) return -1;
    for (k = 0; k < len; k++) dst[k] = fname[s + k];
    dst[len] = 0;
    return 0;
}

/** Join dir + base + ext into dst with bounds checking. */
static int vedit_join(const char *dir, const char *base, const char *ext,
                      char *dst, size_t cap) {
    size_t d = strlen(dir);
    size_t b = strlen(base);
    size_t e = strlen(ext);
    size_t k = 0;
    size_t i;
    if (d + b + e + 1 > cap) return -1;
    if (d + b + e + 1 > VEDIT_PATH_MAX) return -1;
    for (i = 0; i < d; i++) dst[k++] = dir[i];
    for (i = 0; i < b; i++) dst[k++] = base[i];
    for (i = 0; i < e; i++) dst[k++] = ext[i];
    dst[k] = 0;
    return 0;
}

/** Accept only the two linker formats, rejecting anything else. */
static int vedit_link_fmt(const char *s) {
    size_t k = 0;
    const char *e = VEDIT_LINK_ELF;
    const char *c = VEDIT_LINK_CVM;
    while (e[k] && s[k] == e[k]) k++;
    if (e[k] == 0 && s[k] == 0) return 1;
    k = 0;
    while (c[k] && s[k] == c[k]) k++;
    if (c[k] == 0 && s[k] == 0) return 2;
    return 0;
}

/** Print a captured toolchain log to the console in bounded chunks. */
static void vedit_print_log(const char *path) {
    FILE *f = fopen(path, "r");
    char buf[512];
    size_t n;
    if (!f) {
        printf("vedit: no output captured (%s missing)\n", path);
        return;
    }
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0) {
        size_t k;
        for (k = 0; k < n; k++) putchar(buf[k]);
    }
    fclose(f);
    fflush(stdout);
}

/** Drop the display, run one child, echo its log, then resume the IDE. */
static long vedit_spawn_visible(const char *tool, const char *redir, int argc,
                                const char **argv, const char *label) {
    unsigned char pal768[768];
    long rc;
    char nb[VEDIT_MSG_MAX];
    vedit_vga(0);
    printf("--- vedit: %s ---\n", label);
    fflush(stdout);
    rc = vedit_spawn(tool, redir, argc, argv);
    if (redir && redir[0]) vedit_print_log(redir);
    printf("vedit: %s exit code: %ld\n", label, rc);
    fflush(stdout);
    vedit_vga(1);
    nk_build_palette(pal768);
    nk_sys_palette(pal768);
    if (rc < 0) {
        snprintf(nb, sizeof(nb), "%s failed (%ld)", label, rc);
        vedit_set_msg(nb);
    } else if (rc != 0) {
        snprintf(nb, sizeof(nb), "%s exit %ld", label, rc);
        vedit_set_msg(nb);
    } else {
        snprintf(nb, sizeof(nb), "%s ok", label);
        vedit_set_msg(nb);
    }
    return rc;
}

/** Run a freshly linked artifact so its output lands on the console. */
static void vedit_cmd_exec(const char *out, int kind) {
    const char *args[2];
    char label[VEDIT_MSG_MAX];
    snprintf(label, sizeof(label), "run %s", out);
    args[0] = out;
    args[1] = 0;
    if (kind == 1)
        vedit_spawn_visible(out, 0, 1, args, label);
    else
        vedit_spawn_visible(VEDIT_TOOL_CVM, 0, 1, args, label);
}

/** Decide the ^R tool for a file: 1=minigcc, 2=lua, 3=python, 4=ld, 5=lisp. */
static int vedit_run_kind(const char *fname) {
    if (vedit_has_ext(fname, ".c") || vedit_has_ext(fname, ".h")) return 1;
    if (vedit_has_ext(fname, ".lua")) return 2;
    if (vedit_has_ext(fname, ".py")) return 3;
    if (vedit_has_ext(fname, ".s")) return 4;
    if (vedit_has_ext(fname, ".lisp")) return 5;
    return 0;
}

/** Save, then compile or run the current buffer by extension. */
static void vedit_cmd_run(void) {
    char base[VEDIT_BASE_MAX];
    char out[VEDIT_PATH_MAX];
    char label[VEDIT_MSG_MAX];
    const char *tool;
    const char *args[7];
    const char *redir = 0;
    size_t k;
    int kind;
    if (vedit_trunc) {
        vedit_set_msg("refusing to run: file did not fit in the buffer");
        return;
    }
    if (vedit_save() != 0) return;
    kind = vedit_run_kind(vedit_fname);
    if (kind == 1) {
        if (vedit_base_of(vedit_fname, base, sizeof(base)) != 0) {
            vedit_set_msg("name too long");
            return;
        }
        if (vedit_join(VEDIT_DIR_ASM, base, ".s", out, sizeof(out)) != 0) {
            vedit_set_msg("name too long");
            return;
        }
        tool = VEDIT_TOOL_MINIGCC;
        args[0] = tool;
        args[1] = vedit_fname;
        args[2] = 0;
        for (k = 0; k < sizeof(label) - 1 && vedit_fname[k]; k++)
            label[k] = vedit_fname[k];
        label[k] = 0;
        vedit_spawn_visible(tool, out, 2, args, label);
        return;
    }
    if (kind == 4) {
        if (vedit_base_of(vedit_fname, base, sizeof(base)) != 0) {
            vedit_set_msg("name too long");
            return;
        }
        if (vedit_join(VEDIT_DIR_BIN, base, ".elf", out, sizeof(out)) != 0) {
            vedit_set_msg("name too long");
            return;
        }
        tool = VEDIT_TOOL_LD;
        args[0] = tool;
        args[1] = "-f";
        args[2] = VEDIT_LINK_ELF;
        args[3] = "-o";
        args[4] = out;
        args[5] = vedit_fname;
        args[6] = 0;
        for (k = 0; k < sizeof(label) - 1 && vedit_fname[k]; k++)
            label[k] = vedit_fname[k];
        label[k] = 0;
        if (vedit_spawn_visible(tool, VEDIT_BUILD_LOG, 6, args, label) != 0)
            return;
        vedit_cmd_exec(out, 1);
        return;
    }
    if (kind == 2) tool = VEDIT_TOOL_LUA;
    else if (kind == 3) tool = VEDIT_TOOL_PY;
    else if (kind == 5) tool = VEDIT_TOOL_LISP;
    else {
        vedit_set_msg("usage: save as .c, .s, .lua, .py or .lisp first");
        return;
    }
    args[0] = tool;
    args[1] = vedit_fname;
    args[2] = 0;
    for (k = 0; k < sizeof(label) - 1 && vedit_fname[k]; k++)
        label[k] = vedit_fname[k];
    label[k] = 0;
    redir = VEDIT_BUILD_LOG;
    vedit_spawn_visible(tool, redir, 2, args, label);
}

/** Save, then link asm/<base>.s into bin/<base>.elf or cvm/<base>.cvm. */
static void vedit_cmd_link(const char *fmt) {
    char base[VEDIT_BASE_MAX];
    char in[VEDIT_PATH_MAX];
    char out[VEDIT_PATH_MAX];
    char label[VEDIT_MSG_MAX];
    const char *tool = VEDIT_TOOL_LD;
    const char *args[7];
    int kind = vedit_link_fmt(fmt ? fmt : "");
    if (kind == 0) {
        vedit_set_msg("usage: elf|cvm");
        return;
    }
    if (vedit_trunc) {
        vedit_set_msg("refusing to link: file did not fit in the buffer");
        return;
    }
    if (vedit_save() != 0) return;
    if (vedit_base_of(vedit_fname, base, sizeof(base)) != 0) {
        vedit_set_msg("name too long");
        return;
    }
    if (vedit_join(VEDIT_DIR_ASM, base, ".s", in, sizeof(in)) != 0) {
        vedit_set_msg("name too long");
        return;
    }
    if (kind == 1) {
        if (vedit_join(VEDIT_DIR_BIN, base, ".elf", out, sizeof(out)) != 0) {
            vedit_set_msg("name too long");
            return;
        }
    } else {
        if (vedit_join(VEDIT_DIR_CVM, base, ".cvm", out, sizeof(out)) != 0) {
            vedit_set_msg("name too long");
            return;
        }
    }
    args[0] = tool;
    args[1] = "-f";
    args[2] = (kind == 1) ? VEDIT_LINK_ELF : VEDIT_LINK_CVM;
    args[3] = "-o";
    args[4] = out;
    args[5] = in;
    args[6] = 0;
    snprintf(label, sizeof(label), "link %s", out);
    if (vedit_spawn_visible(tool, VEDIT_BUILD_LOG, 6, args, label) == 0)
        vedit_cmd_exec(out, kind);
}

/** Headless build contract check: no display, no syscalls, exit status only.
 * Mirror contract with tests/test_vedit_build.c: any vector added here
 * must gain a host CHECK there too, so spec drift fails the build. */
static int vedit_selftest_build(void) {
    char base[VEDIT_BASE_MAX];
    char path[VEDIT_PATH_MAX];
    int fails = 0;
    if (vedit_lang_of(VEDIT_DEFAULT_FILE) != VEDIT_LANG_C) {
        printf("vedit: untitled must highlight as C\n");
        fails++;
    }
    if (vedit_lang_of("a.c") != VEDIT_LANG_C) {
        printf("vedit: .c must highlight as C\n");
        fails++;
    }
    if (vedit_lang_of("a.py") != VEDIT_LANG_PY) {
        printf("vedit: .py must highlight as Python\n");
        fails++;
    }
    if (vedit_lang_of("a.lua") != VEDIT_LANG_LUA) {
        printf("vedit: .lua must highlight as Lua\n");
        fails++;
    }
    if (vedit_lang_of("a.s") != VEDIT_LANG_ASM) {
        printf("vedit: .s must highlight as Asm\n");
        fails++;
    }
    if (vedit_lang_of("a.lisp") != VEDIT_LANG_LISP) {
        printf("vedit: .lisp must highlight as Lisp\n");
        fails++;
    }
    if (vedit_run_kind("a.c") != 1 || vedit_run_kind("a.h") != 1) {
        printf("vedit: .c/.h must route to minigcc\n");
        fails++;
    }
    if (vedit_run_kind("a.s") != 4) {
        printf("vedit: .s must route to ld\n");
        fails++;
    }
    if (vedit_run_kind("a.lua") != 2 || vedit_run_kind("a.py") != 3) {
        printf("vedit: .lua/.py must route to runners\n");
        fails++;
    }
    if (vedit_run_kind("a.lisp") != 5) {
        printf("vedit: .lisp must route to lisp\n");
        fails++;
    }
    if (vedit_run_kind("a.txt") != 0) {
        printf("vedit: .txt must route nowhere\n");
        fails++;
    }
    if (!vedit_has_ext("a.c", ".c") || vedit_has_ext("a.c", ".lua")) {
        printf("vedit: extension match broken\n");
        fails++;
    }
    if (vedit_base_of("src/a.c", base, sizeof(base)) != 0) {
        printf("vedit: base strip failed\n");
        fails++;
    } else if (strcmp(base, "a") != 0) {
        printf("vedit: base must be a, got %s\n", base);
        fails++;
    }
    if (vedit_join(VEDIT_DIR_ASM, "a", ".s", path, sizeof(path)) != 0) {
        printf("vedit: join failed\n");
        fails++;
    } else if (strcmp(path, "/asm/a.s") != 0) {
        printf("vedit: join must be /asm/a.s, got %s\n", path);
        fails++;
    }
    if (vedit_link_fmt("elf") != 1 || vedit_link_fmt("cvm") != 2) {
        printf("vedit: link formats broken\n");
        fails++;
    }
    if (vedit_link_fmt("exe") != 0 || vedit_link_fmt("") != 0) {
        printf("vedit: bad link format must fail\n");
        fails++;
    }
    if (VEDIT_KEY_RUN != 18 || VEDIT_KEY_LINK != 12 || VEDIT_KEY_DUMP != 4) {
        printf("vedit: shortcut contract broken\n");
        fails++;
    }
    {
        char sc[32];
        int ml = 0;
        memcpy(sc, "hello world", 12);
        vedit_str_case(sc, 1);
        if (strcmp(sc, "HELLO WORLD") != 0) {
            printf("vedit: upper broken (%s)\n", sc);
            fails++;
        }
        memcpy(sc, "Hello World", 12);
        vedit_str_case(sc, 2);
        if (strcmp(sc, "hello world") != 0) {
            printf("vedit: lower broken (%s)\n", sc);
            fails++;
        }
        memcpy(sc, "hello world", 12);
        vedit_str_case(sc, 3);
        if (strcmp(sc, "Hello World") != 0) {
            printf("vedit: capitalize broken (%s)\n", sc);
            fails++;
        }
        memcpy(sc, "ab", 3);
        vedit_str_transpose(sc, 2, 1);
        if (strcmp(sc, "ba") != 0) {
            printf("vedit: transpose broken (%s)\n", sc);
            fails++;
        }
        if (!vedit_magic_match("foobar", "foo", &ml) || ml != 3) {
            printf("vedit: magic exact broken\n");
            fails++;
        }
        if (!vedit_magic_match("foobar", "f.o", &ml) || ml != 3) {
            printf("vedit: magic dot broken\n");
            fails++;
        }
        if (!vedit_magic_match("foobar", "f*bar", &ml)) {
            printf("vedit: magic star broken\n");
            fails++;
        }
        if (!vedit_magic_match("foobar", "^foo", &ml) || ml != 3) {
            printf("vedit: magic anchor broken\n");
            fails++;
        }
        if (vedit_magic_match("xfoobar", "^foo", &ml)) {
            printf("vedit: magic anchor must fail\n");
            fails++;
        }
        if (!vedit_magic_match("foobar", "bar$", &ml) || ml != 3) {
            printf("vedit: magic end anchor broken\n");
            fails++;
        }
        if (!vedit_magic_match("a1c", "a[0-9]c", &ml) || ml != 3) {
            printf("vedit: magic class broken\n");
            fails++;
        }
        if (vedit_magic_match("abc", "a[^0-9]c", &ml)) {
            (void)ml;
        } else {
            printf("vedit: magic negated class broken\n");
            fails++;
        }
        if (!vedit_magic_match("abc", "z*", &ml) || ml != 0) {
            printf("vedit: magic empty star broken\n");
            fails++;
        }
        if (vedit_cmd_lookup("save-file") < 0 ||
            vedit_cmd_lookup("query-replace") < 0 ||
            vedit_cmd_lookup("no-such-cmd") >= 0) {
            printf("vedit: command table broken\n");
            fails++;
        }
        if (vedit_parse_key("^K") != 11 || vedit_parse_key("^@") != 0 ||
            vedit_parse_key("M-f") != VEDIT_KEY_META('f') ||
            vedit_parse_key("PgDn") != VEDIT_KEY_PGDN ||
            vedit_parse_key("bogus") >= 0) {
            printf("vedit: key parser broken\n");
            fails++;
        }
    }
    if (fails) {
        printf("vedit: build selftest FAIL (%d)\n", fails);
        return 1;
    }
    {
        char cb[16];
        long n;
        if (vedit_clip_set("abc", 3) != 0) {
            printf("vedit: clip set broken\n");
            fails++;
        }
        n = vedit_clip_get(cb, sizeof(cb));
        if (n != 3 || memcmp(cb, "abc", 3) != 0) {
            printf("vedit: clip get broken (n=%ld)\n", n);
            fails++;
        }
        if (vedit_clip_set("x", 4097) == 0) {
            printf("vedit: clip must refuse oversize\n");
            fails++;
        }
        if (vedit_clip_get(cb, 1) >= 0) {
            printf("vedit: clip must refuse undersize\n");
            fails++;
        }
    }
    if (fails) {
        printf("vedit: clip selftest FAIL (%d)\n", fails);
        return 1;
    }
    printf("vedit: build ok (run=^R link=^L dump=^D)\n");
    return 0;
}

/* ---- uemacs F3: two-pane split (uemacs window.c, stacked) ---- */
static int vedit_split_on;
static int vedit_apane;
static int vedit_panes_buf[2];
static int vedit_panes_cy[2];
static int vedit_panes_cx[2];
static int vedit_panes_top[2];
static int vedit_pane_y0;
static int vedit_pane_cursor_on;

static void vedit_pane_save(int p) {
    if (p < 0 || p > 1) return;
    vedit_panes_buf[p] = vedit_cur;
    vedit_panes_cy[p] = vedit_cy;
    vedit_panes_cx[p] = vedit_cx;
    vedit_panes_top[p] = vedit_top;
}

static int vedit_first_open(void) {
    int k;
    for (k = 0; k < VEDIT_NBUF; k++) {
        if (vedit_pools[k]) return k;
    }
    return -1;
}

static void vedit_pane_load(int p) {
    if (p < 0 || p > 1) return;
    vedit_cur = vedit_panes_buf[p];
    if (vedit_cur < 0 || vedit_cur >= VEDIT_NBUF || !vedit_pools[vedit_cur])
        vedit_cur = vedit_first_open();
    if (vedit_cur < 0) vedit_cur = 0;
    vedit_cy = vedit_panes_cy[p];
    vedit_cx = vedit_panes_cx[p];
    vedit_top = vedit_panes_top[p];
    vedit_mark_on = 0;
}

static int vedit_count_open(void) {
    int n = 0;
    int k;
    for (k = 0; k < VEDIT_NBUF; k++) {
        if (vedit_pools[k]) n++;
    }
    return n;
}

static void vedit_split_set(int on) {
    if (on) {
        vedit_pane_save(0);
        vedit_panes_buf[1] = vedit_panes_buf[0];
        vedit_panes_cy[1] = vedit_panes_cy[0];
        vedit_panes_cx[1] = vedit_panes_cx[0];
        vedit_panes_top[1] = vedit_panes_top[0];
        vedit_apane = 1;
        vedit_split_on = 1;
        vedit_set_msg("split: M-o switches pane, M-1 single");
    } else {
        vedit_pane_load(vedit_apane);
        vedit_split_on = 0;
        vedit_apane = 0;
        vedit_panes_buf[0] = vedit_cur;
        vedit_set_msg("single window");
    }
}

static void vedit_next_pane(void) {
    if (!vedit_split_on) {
        vedit_set_msg("single window (M-2 splits)");
        return;
    }
    vedit_pane_save(vedit_apane);
    vedit_apane = 1 - vedit_apane;
    vedit_pane_load(vedit_apane);
    vedit_sel_clear();
    vedit_msg[0] = 0;
}

/* ---- uemacs F4: named commands, macros, bindings, startup rc ---- */

/** Named-command table (uemacs names.c + exec.c M-x). IDs are dense;
 * vedit_cmd_lookup is pure and mirrored by the host suite. */
static const char *vedit_cmd_names[] = {
    "save-file", "find-file", "insert-file", "view-file", "list-buffers",
    "select-buffer", "next-buffer", "kill-buffer", "copy-region",
    "kill-region", "yank", "kill-line", "transpose-chars",
    "goto-matching-fence", "count-words", "fill-paragraph",
    "overwrite-mode", "read-only", "goto-line", "search-forward",
    "search-reverse", "search-forward-magic", "hunt-forward",
    "hunt-backward", "replace-string", "query-replace", "set-mark",
    "exchange-point-and-mark", "split-window", "single-window",
    "next-window", "begin-macro", "end-macro", "execute-macro",
    "shell-command", "filter-buffer", "grep", "next-error", "compile",
    "link", "help", "describe-bindings", "save-and-quit", "quit",
    "paste", "copy-to-clipboard",
    0
};

static int vedit_cmd_lookup(const char *name) {
    int k = 0;
    if (!name || !name[0]) return -1;
    while (vedit_cmd_names[k]) {
        const char *t = vedit_cmd_names[k];
        int i = 0;
        while (t[i] && name[i] == t[i]) i++;
        if (!t[i] && !name[i]) return k;
        k++;
    }
    return -1;
}

/** Parse a key description into a decoded key code: ^A..^Z ^@ ^[ ^\ ^]
 * ^^ ^_, M-<c>, or Up Down Left Right Home End PgUp PgDn Del Esc.
 * Pure: host suite pins every vector. */
static int vedit_parse_key(const char *s) {
    if (!s || !s[0]) return -1;
    if (s[0] == '^' && s[1] && !s[2]) {
        int c = (unsigned char)s[1];
        if (c >= 'a' && c <= 'z') return c - 'a' + 1;
        if (c >= 'A' && c <= 'Z') return c - 'A' + 1;
        if (c == '@') return 0;
        if (c == '[') return 27;
        if (c == '\\') return 28;
        if (c == ']') return 29;
        if (c == '^') return 30;
        if (c == '_') return 31;
        return -1;
    }
    if (s[0] == 'M' && s[1] == '-' && s[2] && !s[3])
        return VEDIT_KEY_META((unsigned char)s[2]);
    {
        const char *names[] = {"Up", "Down", "Left", "Right", "Home",
                               "End", "PgUp", "PgDn", "Del", "Esc", 0};
        int codes[] = {VEDIT_KEY_UP, VEDIT_KEY_DOWN, VEDIT_KEY_LEFT,
                       VEDIT_KEY_RIGHT, VEDIT_KEY_HOME, VEDIT_KEY_END,
                       VEDIT_KEY_PGUP, VEDIT_KEY_PGDN, VEDIT_KEY_DEL,
                       VEDIT_KEY_ESC};
        int k = 0;
        while (names[k]) {
            const char *t = names[k];
            int i = 0;
            while (t[i] && s[i] == t[i]) i++;
            if (!t[i] && !s[i]) return codes[k];
            k++;
        }
    }
    return -1;
}

static int vedit_bind_key[VEDIT_CMD_MAX];
static int vedit_bind_cmd[VEDIT_CMD_MAX];
static int vedit_nbind;
static int vedit_find_magic;
static int vedit_select_insert;
static int vedit_macro_depth;
static char vedit_bindkey_tmp[32];

/* Forward: prompt opener (defined with the UI) and F5 IDE verbs. */
static void vedit_prompt_open(const char *label, int mode);
static void vedit_prompt_isearch(int dir);
static void vedit_key(int key, int *quit, int *save_and_quit);
static void vedit_shell_command(const char *line);
static void vedit_filter_buffer(const char *prog);
static void vedit_grep(const char *pat);
static void vedit_next_error(void);

static int vedit_cmd_bind(int key, int cmd) {
    int k;
    if (cmd < 0 || !vedit_cmd_names[cmd]) return -1;
    for (k = 0; k < vedit_nbind; k++) {
        if (vedit_bind_key[k] == key) {
            vedit_bind_cmd[k] = cmd;
            return 0;
        }
    }
    if (vedit_nbind >= VEDIT_CMD_MAX) return -1;
    vedit_bind_key[vedit_nbind] = key;
    vedit_bind_cmd[vedit_nbind] = cmd;
    vedit_nbind++;
    return 0;
}

static int vedit_cmd_bound(int key) {
    int k;
    for (k = 0; k < vedit_nbind; k++) {
        if (vedit_bind_key[k] == key) return vedit_bind_cmd[k];
    }
    return -1;
}

static void vedit_list_buffers(void) {
    int k;
    int n = 0;
    printf("--- buffers ---\n");
    for (k = 0; k < VEDIT_NBUF; k++) {
        if (!vedit_pools[k]) continue;
        n++;
        printf("%c %d: %s%s %d lines\n", k == vedit_cur ? '*' : ' ', k,
               vedit_fnames[k], vedit_dirtys[k] ? " (modified)" : "",
               vedit_counts[k]);
    }
    fflush(stdout);
    {
        char nb[32];
        snprintf(nb, sizeof(nb), "%d buffer(s)", n);
        vedit_set_msg(nb);
    }
}

static void vedit_hist_show(void) {
    int k;
    if (vedit_hist_n <= 0) return;
    printf("--- recent files ---\n");
    for (k = 0; k < vedit_hist_n; k++) printf("%s\n", vedit_hist[k]);
    fflush(stdout);
}

static void vedit_help_text(void) {
    printf("--- vedit keys ---\n");
    printf("arrows/Home/End/PgUp/PgDn move, ^U arg, ^A/^E bol/eol\n");
    printf("M-f/M-b word, M-c/M-l/M-u case word, ^@/M-SP mark, M-w copy\n");
    printf("M-k kill region, ^K kill line, ^Y yank, ^T transpose\n");
    printf("^] goto fence, M-s/M-r isearch, M-n hunt, M-%% query\n");
    printf("M-q fill, M-1/M-2/M-o windows, M-x command, M-! shell\n");
    printf("M-# filter, M-( M-) M-e macro, ^W find, ^G goto\n");
    printf("M-v paste, M-W region to clipboard, drag selects to clipboard\n");
    printf("^O/^S save, ^N name, ^R run, ^L link, ^D dump, ^X done\n");
    printf("M-x help names every command; vedit.rc runs at startup\n");
    fflush(stdout);
    vedit_set_msg("see console for key list");
}

/** Execute a named command id; arg carries an rc-file argument or 0. */
static void vedit_cmd_exec_id(int id, const char *arg, int *quit,
                              int *save_and_quit) {
    const char *name = vedit_cmd_names[id];
    (void)arg;
    if (!name) {
        vedit_set_msg("unknown command");
        return;
    }
    if (strcmp(name, "save-file") == 0) {
        if (vedit_save() == 0)
            printf("vedit: wrote %d line(s) to %s\n", vedit_count,
                   vedit_fname);
    } else if (strcmp(name, "find-file") == 0) {
        if (arg && arg[0]) vedit_open_in_buffer(arg, 0);
        else {
            vedit_select_insert = 0;
            vedit_hist_show();
            vedit_prompt_open("find file: ", VEDIT_PROMPT_SELECT);
        }
    } else if (strcmp(name, "insert-file") == 0) {
        if (arg && arg[0]) vedit_insert_file(arg);
        else {
            vedit_select_insert = 1;
            vedit_prompt_open("insert file: ", VEDIT_PROMPT_SELECT);
        }
    } else if (strcmp(name, "view-file") == 0) {
        if (arg && arg[0]) vedit_open_in_buffer(arg, 1);
        else {
            vedit_select_insert = 0;
            vedit_hist_show();
            vedit_prompt_open("view file: ", VEDIT_PROMPT_SELECT);
        }
    } else if (strcmp(name, "list-buffers") == 0) {
        vedit_list_buffers();
    } else if (strcmp(name, "select-buffer") == 0) {
        vedit_select_insert = 0;
        vedit_list_buffers();
        vedit_prompt_open("buffer: ", VEDIT_PROMPT_SELECT);
    } else if (strcmp(name, "next-buffer") == 0) {
        if (vedit_next_buffer() != 0) vedit_set_msg("only one buffer");
    } else if (strcmp(name, "kill-buffer") == 0) {
        if (vedit_dirty) {
            vedit_set_msg("unsaved changes (save first)");
        } else if (vedit_count_open() <= 1) {
            vedit_set_msg("only one buffer");
        } else {
            int k = vedit_cur;
            free(vedit_pools[k]);
            free(vedit_useds[k]);
            vedit_pools[k] = 0;
            vedit_useds[k] = 0;
            vedit_next_buffer();
            if (vedit_split_on) {
                vedit_panes_buf[0] = vedit_cur;
                vedit_panes_buf[1] = vedit_cur;
            } else {
                vedit_panes_buf[0] = vedit_cur;
            }
            vedit_set_msg("buffer killed");
        }
    } else if (strcmp(name, "copy-region") == 0) {
        vedit_copy_region();
    } else if (strcmp(name, "kill-region") == 0) {
        vedit_kill_region();
    } else if (strcmp(name, "yank") == 0) {
        vedit_yank();
    } else if (strcmp(name, "kill-line") == 0) {
        vedit_kill_line();
    } else if (strcmp(name, "transpose-chars") == 0) {
        vedit_transpose();
    } else if (strcmp(name, "goto-matching-fence") == 0) {
        vedit_goto_fence();
    } else if (strcmp(name, "count-words") == 0) {
        vedit_count_words();
    } else if (strcmp(name, "fill-paragraph") == 0) {
        vedit_fill_paragraph();
    } else if (strcmp(name, "overwrite-mode") == 0) {
        vedit_overwrite = !vedit_overwrite;
        vedit_set_msg(vedit_overwrite ? "overwrite on" : "overwrite off");
    } else if (strcmp(name, "read-only") == 0) {
        vedit_ros[vedit_cur] = !vedit_ros[vedit_cur];
        vedit_set_msg(vedit_ros[vedit_cur] ? "read-only on" :
                      "read-only off");
    } else if (strcmp(name, "goto-line") == 0) {
        if (arg && arg[0]) {
            int n = 0;
            int i = 0;
            while (arg[i] >= '0' && arg[i] <= '9') {
                n = n * 10 + (arg[i] - '0');
                i++;
            }
            if (i > 0 && !arg[i] && n >= 1 && n <= vedit_count) {
                vedit_cy = n - 1;
                vedit_cx = 0;
                vedit_msg[0] = 0;
            } else {
                vedit_set_msg("no such line");
            }
        } else {
            vedit_prompt_open("goto: ", VEDIT_PROMPT_GOTO);
        }
    } else if (strcmp(name, "search-forward") == 0) {
        vedit_find_magic = 0;
        vedit_prompt_open("find: ", VEDIT_PROMPT_FIND);
    } else if (strcmp(name, "search-reverse") == 0) {
        vedit_prompt_isearch(-1);
    } else if (strcmp(name, "search-forward-magic") == 0) {
        vedit_find_magic = 1;
        vedit_prompt_open("magic: ", VEDIT_PROMPT_FIND);
    } else if (strcmp(name, "hunt-forward") == 0) {
        if (!vedit_last_find[0]) vedit_set_msg("no previous search");
        else {
            int w = 0;
            if (vedit_search_fwd(vedit_cy, vedit_cx + 1, vedit_last_find,
                                 0, &w) != 0)
                vedit_set_msg("not found");
            else if (w) vedit_set_msg("wrapped");
            else vedit_msg[0] = 0;
        }
    } else if (strcmp(name, "hunt-backward") == 0) {
        if (!vedit_last_find[0]) vedit_set_msg("no previous search");
        else if (vedit_search_rev(vedit_cy, vedit_cx - 1, vedit_last_find,
                                  0) != 0)
            vedit_set_msg("not found");
        else vedit_msg[0] = 0;
    } else if (strcmp(name, "replace-string") == 0) {
        vedit_qrep_on = 0;
        vedit_prompt_open("replace: ", VEDIT_PROMPT_REP_OLD);
    } else if (strcmp(name, "query-replace") == 0) {
        vedit_qrep_on = 1;
        vedit_prompt_open("query replace: ", VEDIT_PROMPT_REP_OLD);
    } else if (strcmp(name, "set-mark") == 0) {
        vedit_set_mark();
    } else if (strcmp(name, "exchange-point-and-mark") == 0) {
        if (!vedit_mark_on) vedit_set_msg("no mark");
        else {
            int t = vedit_mark_y;
            vedit_mark_y = vedit_cy;
            vedit_cy = t;
            t = vedit_mark_x;
            vedit_mark_x = vedit_cx;
            vedit_cx = t;
            vedit_msg[0] = 0;
        }
    } else if (strcmp(name, "split-window") == 0) {
        if (!vedit_split_on) vedit_split_set(1);
    } else if (strcmp(name, "single-window") == 0) {
        if (vedit_split_on) vedit_split_set(0);
    } else if (strcmp(name, "next-window") == 0) {
        vedit_next_pane();
    } else if (strcmp(name, "begin-macro") == 0) {
        vedit_macro_rec = 1;
        vedit_macro_len = 0;
        vedit_set_msg("recording macro");
    } else if (strcmp(name, "end-macro") == 0) {
        vedit_macro_rec = 0;
        vedit_set_msg("macro recorded");
    } else if (strcmp(name, "execute-macro") == 0) {
        if (vedit_macro_len <= 0) vedit_set_msg("no macro");
        else if (vedit_macro_depth >= 4) vedit_set_msg("macro too deep");
        else {
            int k;
            vedit_macro_depth++;
            for (k = 0; k < vedit_macro_len; k++) {
                vedit_key(vedit_macro[k], quit, save_and_quit);
                if (*quit) break;
            }
            vedit_macro_depth--;
            vedit_msg[0] = 0;
        }
    } else if (strcmp(name, "shell-command") == 0) {
        if (arg && arg[0]) vedit_shell_command(arg);
        else vedit_prompt_open("!: ", VEDIT_PROMPT_SHELLCMD);
    } else if (strcmp(name, "filter-buffer") == 0) {
        if (arg && arg[0]) vedit_filter_buffer(arg);
        else vedit_prompt_open("filter: ", VEDIT_PROMPT_FILTER);
    } else if (strcmp(name, "grep") == 0) {
        if (arg && arg[0]) vedit_grep(arg);
        else vedit_prompt_open("grep: ", VEDIT_PROMPT_GREP);
    } else if (strcmp(name, "next-error") == 0) {
        vedit_next_error();
    } else if (strcmp(name, "compile") == 0) {
        vedit_cmd_run();
    } else if (strcmp(name, "link") == 0) {
        vedit_prompt_open("link elf/cvm: ", VEDIT_PROMPT_LINK);
    } else if (strcmp(name, "bind-to-key") == 0) {
        vedit_prompt_open("bind key: ", VEDIT_PROMPT_BINDKEY);
    } else if (strcmp(name, "help") == 0 ||
               strcmp(name, "describe-bindings") == 0) {
        vedit_help_text();
    } else if (strcmp(name, "save-and-quit") == 0) {
        *save_and_quit = 1;
        *quit = 1;
    } else if (strcmp(name, "quit") == 0) {
        *quit = 1;
    } else if (strcmp(name, "paste") == 0) {
        vedit_clip_paste();
    } else if (strcmp(name, "copy-to-clipboard") == 0) {
        vedit_region_to_clip();
    } else {
        vedit_set_msg("not implemented");
    }
}

/** Run the startup script: `bind <key> <cmd>` plus bare commands with
 * an optional trailing argument. Unknown lines are reported, never fatal. */
static void vedit_run_rc(const char *path) {
    FILE *f = fopen(path, "r");
    char line[256];
    if (!f) return;
    while (fgets(line, sizeof(line), f)) {
        char cmd[64];
        char arg[128];
        int i = 0;
        int a = 0;
        int b = 0;
        while (line[i] == ' ' || line[i] == '\t') i++;
        if (!line[i] || line[i] == '#' || line[i] == '\n' ||
            line[i] == ';')
            continue;
        while (line[i] && line[i] != ' ' && line[i] != '\t' &&
               line[i] != '\n' && a < (int)sizeof(cmd) - 1)
            cmd[a++] = line[i++];
        cmd[a] = 0;
        while (line[i] == ' ' || line[i] == '\t') i++;
        while (line[i] && line[i] != '\n' && b < (int)sizeof(arg) - 1)
            arg[b++] = line[i++];
        arg[b] = 0;
        if (strcmp(cmd, "bind") == 0) {
            char key[32];
            char name[64];
            int q = 0;
            int r = 0;
            int id;
            int keycode;
            while (arg[q] && arg[q] != ' ' && arg[q] != '\t' &&
                   r < (int)sizeof(key) - 1)
                key[r++] = arg[q++];
            key[r] = 0;
            while (arg[q] == ' ' || arg[q] == '\t') q++;
            r = 0;
            while (arg[q] && r < (int)sizeof(name) - 1) name[r++] = arg[q++];
            name[r] = 0;
            id = vedit_cmd_lookup(name);
            keycode = vedit_parse_key(key);
            if (id < 0 || keycode < 0 ||
                vedit_cmd_bind(keycode, id) != 0)
                printf("vedit.rc: bad bind %s %s\n", key, name);
            (void)b;
        } else {
            int id = vedit_cmd_lookup(cmd);
            int dummy_q = 0;
            int dummy_s = 0;
            if (id < 0) {
                printf("vedit.rc: unknown command %s\n", cmd);
                continue;
            }
            vedit_cmd_exec_id(id, arg[0] ? arg : 0, &dummy_q, &dummy_s);
        }
    }
    fclose(f);
    fflush(stdout);
}

/* ---- uemacs F5: shell capture, filter, grep (spawn.c + IDE) ---- */
#define VEDIT_TMP_OUT "/tmp/vedit-out"
#define VEDIT_TMP_IN "/tmp/vedit-in"
#define VEDIT_TMP_F "/tmp/vedit-filter"
#define VEDIT_SH_ARGS 8
#define VEDIT_SH_LINE 256
#define VEDIT_CLIP_MAX 4096

static int vedit_grep_src = -1;

/* ---- Clipboard selection + paste (Phase 2: syscalls 249/250) ---- */
static int vedit_sel_down;
static int vedit_sel_on;
static int vedit_sel_buf;
static int vedit_sy0;
static int vedit_sx0;
static int vedit_sy1;
static int vedit_sx1;
static char vedit_clipbuf[VEDIT_CLIP_MAX + 1];

static void vedit_sel_clear(void) {
    vedit_sel_on = 0;
    vedit_sel_down = 0;
}

static void vedit_sel_norm(void) {
    if (vedit_sy0 > vedit_sy1 ||
        (vedit_sy0 == vedit_sy1 && vedit_sx0 > vedit_sx1)) {
        int t = vedit_sy0;
        vedit_sy0 = vedit_sy1;
        vedit_sy1 = t;
        t = vedit_sx0;
        vedit_sx0 = vedit_sx1;
        vedit_sx1 = t;
    }
}

/** Copy the mouse selection into the kernel clipboard; 0 ok. */
static int vedit_sel_copy(void) {
    int y;
    int pos = 0;
    vedit_sel_norm();
    for (y = vedit_sy0; y <= vedit_sy1; y++) {
        int a = (y == vedit_sy0) ? vedit_sx0 : 0;
        int b = (y == vedit_sy1) ? vedit_sx1 : vedit_used[y];
        int k;
        if (y < 0 || y >= vedit_count) continue;
        if (a > vedit_used[y]) a = vedit_used[y];
        if (b > vedit_used[y]) b = vedit_used[y];
        for (k = a; k < b; k++) {
            if (pos >= VEDIT_CLIP_MAX) {
                vedit_set_msg("selection too big (4096 max)");
                return -1;
            }
            vedit_clipbuf[pos++] = vedit_row_ptr(y)[k];
        }
        if (y < vedit_sy1) {
            if (pos >= VEDIT_CLIP_MAX) {
                vedit_set_msg("selection too big (4096 max)");
                return -1;
            }
            vedit_clipbuf[pos++] = '\n';
        }
    }
    if (pos <= 0) {
        vedit_set_msg("nothing selected");
        return -1;
    }
    if (vedit_clip_set(vedit_clipbuf, pos) != 0) {
        vedit_set_msg("clipboard refused");
        return -1;
    }
    {
        char nb[64];
        snprintf(nb, sizeof(nb), "copied %d byte(s)", pos);
        vedit_set_msg(nb);
    }
    return 0;
}

/** Paste the kernel clipboard at dot; fail closed, never truncated. */
static int vedit_clip_paste(void) {
    long n;
    long k;
    if (vedit_ros[vedit_cur]) {
        vedit_set_msg("buffer is read-only");
        return -1;
    }
    n = vedit_clip_get(vedit_clipbuf, VEDIT_CLIP_MAX);
    if (n < 0) {
        vedit_set_msg("clipboard empty (or too big)");
        return -1;
    }
    vedit_clipbuf[n] = 0;
    for (k = 0; k < n; k++) {
        if (vedit_clipbuf[k] == '\r') continue;
        if (vedit_clipbuf[k] == '\n')
            vedit_split();
        else
            vedit_insert_char((unsigned char)vedit_clipbuf[k]);
        if (vedit_msg[0]) {
            vedit_set_msg("paste stopped: buffer full");
            return -1;
        }
    }
    vedit_sel_clear();
    vedit_msg[0] = 0;
    return 0;
}

/** Copy the emacs region (not the mouse) into the clipboard. */
static int vedit_region_to_clip(void) {
    int y0;
    int x0;
    int y1;
    int x1;
    int y;
    int pos = 0;
    if (!vedit_region(&y0, &x0, &y1, &x1)) {
        vedit_set_msg("no region");
        return -1;
    }
    for (y = y0; y <= y1; y++) {
        int a = (y == y0) ? x0 : 0;
        int b = (y == y1) ? x1 : vedit_used[y];
        int k;
        if (a > vedit_used[y]) a = vedit_used[y];
        if (b > vedit_used[y]) b = vedit_used[y];
        for (k = a; k < b; k++) {
            if (pos >= VEDIT_CLIP_MAX) {
                vedit_set_msg("region too big (4096 max)");
                return -1;
            }
            vedit_clipbuf[pos++] = vedit_row_ptr(y)[k];
        }
        if (y < y1) {
            if (pos >= VEDIT_CLIP_MAX) {
                vedit_set_msg("region too big (4096 max)");
                return -1;
            }
            vedit_clipbuf[pos++] = '\n';
        }
    }
    if (pos <= 0) {
        vedit_set_msg("nothing selected");
        return -1;
    }
    if (vedit_clip_set(vedit_clipbuf, pos) != 0) {
        vedit_set_msg("clipboard refused");
        return -1;
    }
    vedit_set_msg("copied to clipboard");
    return 0;
}

/** Split a shell line into argv; returns argc or -1 on overflow. */
static int vedit_sh_split(const char *line, char *buf, const char **argv) {
    int argc = 0;
    int k = 0;
    if (!line || !buf || !argv) return -1;
    while (*line) {
        while (*line == ' ' || *line == '\t') line++;
        if (!*line) break;
        if (argc >= VEDIT_SH_ARGS) return -1;
        argv[argc++] = buf + k;
        while (*line && *line != ' ' && *line != '\t') {
            if (k >= VEDIT_SH_LINE - 1) return -1;
            buf[k++] = *line++;
        }
        buf[k++] = 0;
    }
    argv[argc] = 0;
    return argc;
}

/** Run a shell line, capturing stdout into the *shell* buffer. */
static void vedit_shell_command(const char *line) {
    char shb[VEDIT_SH_LINE];
    const char *argv[VEDIT_SH_ARGS + 1];
    int argc;
    int idx;
    if (!line || !line[0]) {
        vedit_set_msg("usage: M-! program [args]");
        return;
    }
    argc = vedit_sh_split(line, shb, argv);
    if (argc <= 0) {
        vedit_set_msg("too many args (8 max)");
        return;
    }
    vedit_spawn_visible(argv[0], VEDIT_TMP_OUT, argc, argv, line);
    idx = vedit_open_in_buffer("*shell*", 0);
    if (idx < 0) return;
    vedit_count = 0;
    vedit_cx = 0;
    vedit_cy = 0;
    vedit_top = 0;
    vedit_insert_file(VEDIT_TMP_OUT);
    vedit_cx = 0;
    vedit_cy = 0;
    vedit_top = 0;
    vedit_set_msg("see *shell* buffer");
}

/** Write the region (or whole buffer) to path; 0 ok. */
static int vedit_write_region(const char *path, int *y0o, int *x0o, int *y1o,
                              int *x1o) {
    FILE *f;
    int y0;
    int x0;
    int y1;
    int x1;
    int y;
    if (!vedit_region(&y0, &x0, &y1, &x1)) {
        y0 = 0;
        x0 = 0;
        y1 = vedit_count - 1;
        x1 = (y1 >= 0) ? vedit_used[y1] : 0;
        if (y1 < 0) {
            vedit_set_msg("buffer empty");
            return -1;
        }
    }
    f = fopen(path, "w");
    if (!f) {
        vedit_set_msg("cannot write temp file");
        return -1;
    }
    for (y = y0; y <= y1; y++) {
        int a = (y == y0) ? x0 : 0;
        int b = (y == y1) ? x1 : vedit_used[y];
        int k;
        if (a > vedit_used[y]) a = vedit_used[y];
        if (b > vedit_used[y]) b = vedit_used[y];
        for (k = a; k < b; k++) putc(vedit_row_ptr(y)[k], f);
        if (y < y1) putc('\n', f);
    }
    if (fclose(f) != 0) {
        vedit_set_msg("cannot write temp file");
        return -1;
    }
    if (y0o) *y0o = y0;
    if (x0o) *x0o = x0;
    if (y1o) *y1o = y1;
    if (x1o) *x1o = x1;
    return 0;
}

/** Pipe the region (or buffer) through an external program. */
static void vedit_filter_buffer(const char *prog) {
    char shb[VEDIT_SH_LINE];
    const char *argv[VEDIT_SH_ARGS + 1];
    const char *base[2];
    int y0;
    int x0;
    int y1;
    int x1;
    int argc;
    int k;
    long rc;
    if (!prog || !prog[0]) {
        vedit_set_msg("usage: M-# program");
        return;
    }
    if (vedit_ros[vedit_cur]) {
        vedit_set_msg("buffer is read-only");
        return;
    }
    if (vedit_write_region(VEDIT_TMP_IN, &y0, &x0, &y1, &x1) != 0) return;
    base[0] = prog;
    base[1] = VEDIT_TMP_IN;
    argc = 2;
    for (k = 0; k < argc; k++) {
        size_t n = strlen(base[k]);
        if (n > VEDIT_SH_LINE - 1) {
            vedit_set_msg("name too long");
            return;
        }
    }
    {
        size_t p = 0;
        size_t i;
        for (k = 0; k < argc; k++) {
            argv[k] = shb + p;
            for (i = 0; base[k][i]; i++) shb[p++] = base[k][i];
            shb[p++] = 0;
        }
        argv[argc] = 0;
    }
    rc = vedit_spawn_visible(prog, VEDIT_TMP_F, argc, argv, prog);
    if (rc != 0) {
        vedit_set_msg("filter failed, buffer kept");
        return;
    }
    vedit_cy = y1;
    vedit_cx = x1;
    vedit_mark_y = y0;
    vedit_mark_x = x0;
    vedit_mark_on = 1;
    if (vedit_kill_region() != 0) return;
    if (vedit_insert_file(VEDIT_TMP_F) != 0) {
        vedit_set_msg("filter output did not fit");
        return;
    }
    vedit_mark_on = 0;
    vedit_set_msg("filtered");
}

/** Magic grep of the current buffer into the *grep* buffer. */
static void vedit_grep(const char *pat) {
    int idx;
    int r;
    int hits = 0;
    int src;
    if (!pat || !pat[0]) {
        vedit_set_msg("usage: M-x grep <pattern>");
        return;
    }
    src = vedit_cur;
    idx = vedit_open_in_buffer("*grep*", 0);
    if (idx < 0) return;
    vedit_count = 0;
    vedit_cx = 0;
    vedit_cy = 0;
    vedit_top = 0;
    vedit_cur = src;
    for (r = 0; r < vedit_counts[src]; r++) {
        char tmp[VEDIT_LINE_MAX + 1];
        int mlen = 0;
        int k;
        int avail = vedit_useds[src][r];
        if (avail > VEDIT_LINE_MAX) avail = VEDIT_LINE_MAX;
        for (k = 0; k < avail; k++)
            tmp[k] = vedit_pools[src][r * VEDIT_LINE_MAX + k];
        tmp[avail] = 0;
        if (!vedit_magic_match(tmp, pat, &mlen)) continue;
        vedit_cur = idx;
        {
            char line[VEDIT_LINE_MAX];
            int n = snprintf(line, sizeof(line), "%d: %s", r + 1, tmp);
            int q;
            if (n < 0) {
                vedit_cur = src;
                break;
            }
            if (vedit_count >= VEDIT_MAX_LINES) {
                vedit_set_msg("grep output full");
                break;
            }
            if (n > VEDIT_LINE_USED) n = VEDIT_LINE_USED;
            for (q = 0; q < n; q++)
                vedit_pools[idx][vedit_count * VEDIT_LINE_MAX + q] =
                    line[q];
            vedit_useds[idx][vedit_count] = n;
            vedit_count++;
            hits++;
        }
        vedit_cur = src;
    }
    vedit_switch_buffer(idx);
    vedit_grep_src = src;
    vedit_cx = 0;
    vedit_cy = 0;
    vedit_top = 0;
    {
        char nb[64];
        snprintf(nb, sizeof(nb), "%d match(es)", hits);
        vedit_set_msg(nb);
    }
}

/** Jump to the match under dot in *grep* ("N: text" -> src buffer line N). */
static void vedit_next_error(void) {
    int n = 0;
    int i = 0;
    char *l;
    if (vedit_grep_src < 0 || !vedit_pools[vedit_grep_src]) {
        vedit_set_msg("no grep buffer");
        return;
    }
    if (vedit_count <= 0 || vedit_cy >= vedit_count) return;
    l = vedit_row_ptr(vedit_cy);
    while (i < vedit_used[vedit_cy] && l[i] >= '0' && l[i] <= '9') {
        n = n * 10 + (l[i] - '0');
        i++;
    }
    if (i == 0 || i >= vedit_used[vedit_cy] || l[i] != ':') {
        if (vedit_cy + 1 < vedit_count) {
            vedit_cy++;
            vedit_cx = 0;
            vedit_next_error();
        } else {
            vedit_set_msg("no more matches");
        }
        return;
    }
    if (n < 1 || n > vedit_counts[vedit_grep_src]) {
        vedit_set_msg("line out of range");
        return;
    }
    vedit_switch_buffer(vedit_grep_src);
    vedit_cy = n - 1;
    vedit_cx = 0;
    vedit_msg[0] = 0;
}

/** Keyboard: GETC_RAW bytes decoded into extended key codes.
 *
 * One nonblocking poll per frame; the ESC [ sequence state survives
 * across frames with a bounded timeout, so the loop keeps presenting
 * (and draining the mouse wheel) while a sequence is in flight instead
 * of blocking the whole UI on the next byte. An incomplete sequence
 * degrades to ESC, never a hang. The timeout is a full second on
 * purpose: ESC is also the Meta prefix (ESC, then a key), and a human
 * hunting for the second key must not be mistaken for a lone ESC
 * (which quits). A lone ESC therefore quits up to one second late. */
static int vedit_esc_state;
static int vedit_esc_p1;
static unsigned vedit_esc_t0;

static int vedit_read_key_poll(void) {
    long c = vedit_getc_raw(0);
    unsigned now;
    if (c < 0) {
        if (vedit_esc_state) {
            now = (unsigned)vedit_time_ms();
            if (now - vedit_esc_t0 > VEDIT_ESC_MS) {
                vedit_esc_state = 0;
                return VEDIT_KEY_ESC;
            }
        }
        return -1;
    }
    now = (unsigned)vedit_time_ms();
    if (vedit_esc_state == 0) {
        if (c != 27) return (int)c;
        vedit_esc_state = 1;
        vedit_esc_t0 = now;
        return -1;
    }
    if (vedit_esc_state == 1) {
        vedit_esc_state = 0;
        if (c != '[') {
            if (c >= 0 && c < 128) return VEDIT_KEY_META((int)c);
            return VEDIT_KEY_ESC;
        }
        vedit_esc_state = 2;
        vedit_esc_t0 = now;
        return -1;
    }
    if (vedit_esc_state == 2) {
        vedit_esc_state = 0;
        if (c == 'A') return VEDIT_KEY_UP;
        if (c == 'B') return VEDIT_KEY_DOWN;
        if (c == 'C') return VEDIT_KEY_RIGHT;
        if (c == 'D') return VEDIT_KEY_LEFT;
        if (c == 'H') return VEDIT_KEY_HOME;
        if (c == 'F') return VEDIT_KEY_END;
        if (c == '3' || c == '5' || c == '6') {
            vedit_esc_p1 = (int)c;
            vedit_esc_state = 3;
            vedit_esc_t0 = now;
            return -1;
        }
        return VEDIT_KEY_ESC;
    }
    vedit_esc_state = 0;
    if (c != '~') return VEDIT_KEY_ESC;
    if (vedit_esc_p1 == '3') return VEDIT_KEY_DEL;
    if (vedit_esc_p1 == '5') return VEDIT_KEY_PGUP;
    return VEDIT_KEY_PGDN;
}

/** Serial ANSI mirror: the UI itself is pixels. */
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

/** Prompt openers (state lives at the top with the other IDE state). */
static void vedit_prompt_open(const char *label, int mode) {
    size_t n = strlen(label);
    if (n > sizeof(vedit_prompt_label) - 1) n = sizeof(vedit_prompt_label) - 1;
    memcpy(vedit_prompt_label, label, n);
    vedit_prompt_label[n] = 0;
    vedit_prompt_pos = 0;
    vedit_prompt_buf[0] = 0;
    vedit_prompt_mode = mode;
    vedit_prompt_on = 1;
}

static void vedit_prompt_find(void) {
    vedit_prompt_open("find: ", VEDIT_PROMPT_FIND);
}

static void vedit_prompt_isearch(int dir) {
    vedit_isearch_oy = vedit_cy;
    vedit_isearch_ox = vedit_cx;
    vedit_isearch_dir = dir;
    vedit_prompt_open(dir > 0 ? "I-search: " : "reverse-I-search: ",
                      dir > 0 ? VEDIT_PROMPT_ISEARCH_F :
                      VEDIT_PROMPT_ISEARCH_R);
}

/** Step the pending query-replace from (r,c); prompts or finishes. */
static void vedit_qrep_next(int r, int c) {
    int w = 0;
    if (vedit_search_fwd(r, c, vedit_qrep_old, 0, &w) != 0) {
        vedit_qrep_on = 0;
        vedit_prompt_on = 0;
        vedit_set_msg("query-replace done");
        return;
    }
    vedit_qrep_on = 1;
    vedit_prompt_open("query (y/n/!/q): ", VEDIT_PROMPT_QREP);
}

static void vedit_qrep_answer(int key) {
    if (key == 'q' || key == 'Q' || key == VEDIT_KEY_ESC) {
        vedit_qrep_on = 0;
        vedit_prompt_on = 0;
        vedit_set_msg("query-replace quit");
        return;
    }
    if (key == '!') {
        vedit_prompt_on = 0;
        vedit_replace_all(vedit_qrep_old, vedit_qrep_new, 0);
        vedit_qrep_on = 0;
        return;
    }
    if (key == 'y' || key == 'Y' || key == ' ') {
        int nc = vedit_replace_at(vedit_cy, vedit_cx, vedit_qrep_old,
                                  vedit_qrep_new, 0);
        if (nc < 0) nc = vedit_cx + 1;
        vedit_prompt_on = 0;
        vedit_qrep_next(vedit_cy, nc);
        return;
    }
    if (key == 'n' || key == 'N' || key == '\b' || key == 127) {
        int c = vedit_cx + 1;
        int r = vedit_cy;
        if (c > vedit_used[r]) {
            r++;
            c = 0;
        }
        vedit_prompt_on = 0;
        if (r >= vedit_count) {
            vedit_qrep_on = 0;
            vedit_set_msg("query-replace done");
            return;
        }
        vedit_qrep_next(r, c);
        return;
    }
}

static void vedit_prompt_saveas(void) {
    size_t n;
    vedit_prompt_open("name: ", VEDIT_PROMPT_NAME);
    n = strlen(vedit_fname);
    if (n > sizeof(vedit_prompt_buf) - 1) n = sizeof(vedit_prompt_buf) - 1;
    memcpy(vedit_prompt_buf, vedit_fname, n);
    vedit_prompt_buf[n] = 0;
    vedit_prompt_pos = (int)n;
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
    int y = vedit_pane_y0 + vrow * vedit_ch;
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
    if (is_cursor_row && vedit_pane_cursor_on &&
        vedit_cx >= vedit_hoff &&
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
    if (vedit_sel_on && vedit_cur == vedit_sel_buf && line_idx >= 0 &&
        line_idx < vedit_count && line_idx >= vedit_sy0 &&
        line_idx <= vedit_sy1) {
        int textw = vedit_cols - vedit_gutter_w;
        int a = (line_idx == vedit_sy0) ? vedit_sx0 : 0;
        int b = (line_idx == vedit_sy1) ? vedit_sx1 : len;
        int c;
        if (a < 0) a = 0;
        if (b > len) b = len;
        for (c = a; c < b; c++) {
            int vc = c - vedit_hoff;
            if (vc < 0 || vc >= textw) continue;
            nk_draw_text(canvas,
                         nk_rect((float)(x + vc * vedit_cw), (float)y,
                                 (float)vedit_cw, (float)vedit_ch),
                         l + c, 1, font, vedit_c_cursor(), vedit_c_bg());
        }
    }
}

/** Draw the IDE window: menu buttons, code rows, status and help. */
static void vedit_draw_ui(struct nk_context *ctx, struct nk_user_font *font,
                          int *quit, int *save_and_quit) {
    struct nk_command_buffer *canvas;
    int r;
    int li;
    char status[VEDIT_STATUS_MAX];
    static const char *help =
        "^O save ^W find ^R run ^L link ^D dump ^X done  "
        "M-x cmd M-s search ^K kill ^Y yank M-v paste M-2 split";
    static int prev_buttons = 0;
    int mouse[4] = {0, 0, 0, 0};
    int mdown = 0;
    int clicked = 0;
    int btn_w = 11 * vedit_cw;
    int btn_h = vedit_ch + 6;
    int bx = vedit_cw;
    int by = 2;
    static const char *labels[8] = {"^O Save", "^W Find", "^N Name",
                                        "^R Run", "^L Link", "Buf",
                                        "M-x", "^X Done"};

    vedit_clamp();
    vedit_follow();
    vedit_pane_save(vedit_apane);

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
        if (mouse[3] && vedit_count > 0) {
            if (mouse[3] > 0) {
                vedit_cy += 3;
                if (vedit_cy >= vedit_count) vedit_cy = vedit_count - 1;
            } else {
                vedit_cy -= 3;
                if (vedit_cy < 0) vedit_cy = 0;
            }
        }
    }

    nk_fill_rect(canvas, nk_rect(0, 0, (float)NK_W, (float)vedit_menu_h), 0,
                 vedit_c_header());
    for (r = 0; r < 8; r++) {
        int x = bx + r * (btn_w + vedit_cw);        int hover = mdown && mouse[0] >= x && mouse[0] < x + btn_w &&
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
            } else if (r == 2) {
                vedit_prompt_saveas();
            } else if (r == 3) {
                vedit_cmd_run();
            } else if (r == 4) {
                vedit_prompt_open("link elf/cvm: ", VEDIT_PROMPT_LINK);
            } else if (r == 5) {
                if (vedit_next_buffer() == 0) {
                    char nb[96];
                    snprintf(nb, sizeof(nb), "buffer %s", vedit_fname);
                    vedit_set_msg(nb);
                    if (vedit_split_on) vedit_pane_save(vedit_apane);
                } else {
                    vedit_set_msg("only one buffer");
                }
            } else if (r == 6) {
                vedit_prompt_open("M-x ", VEDIT_PROMPT_CMD);
            } else {
                *save_and_quit = 1;
                *quit = 1;
            }
        }
    }

    {
        int gy0;
        int grows;
        if (!vedit_split_on) {
            gy0 = vedit_code_y;
            grows = vedit_code_rows;
        } else if (vedit_apane == 0) {
            gy0 = vedit_code_y;
            grows = vedit_code_rows / 2;
            if (grows < 1) grows = 1;
        } else {
            int rows0 = vedit_code_rows / 2;
            if (rows0 < 1) rows0 = 1;
            gy0 = vedit_code_y + rows0 * vedit_ch + vedit_ch;
            grows = vedit_code_rows - rows0 - 1;
            if (grows < 1) grows = 1;
        }
        if (mdown) {
            int rx = mouse[0] - vedit_gutter_w * vedit_cw;
            int vrow = (vedit_ch > 0) ? (mouse[1] - gy0) / vedit_ch : -1;
            if (mouse[0] >= vedit_gutter_w * vedit_cw && vrow >= 0 &&
                vrow < grows) {
                int line = vedit_top + vrow;
                int col = (rx >= 0 ? rx / vedit_cw : 0) + vedit_hoff;
                if (line >= vedit_count) line = vedit_count - 1;
                if (line < 0) line = 0;
                if (col < 0) col = 0;
                if (line < vedit_count && col > vedit_used[line])
                    col = vedit_used[line];
                if (clicked && !vedit_sel_down) {
                    vedit_sel_down = 1;
                    vedit_sel_buf = vedit_cur;
                    vedit_sy0 = line;
                    vedit_sx0 = col;
                    vedit_sy1 = line;
                    vedit_sx1 = col;
                    vedit_sel_on = 0;
                } else if (vedit_sel_down &&
                           vedit_sel_buf == vedit_cur) {
                    vedit_sy1 = line;
                    vedit_sx1 = col;
                    if (line != vedit_sy0 || col != vedit_sx0) {
                        vedit_sel_on = 1;
                        vedit_sel_norm();
                    }
                }
            }
        }
        if (!mdown && vedit_sel_down) {
            vedit_sel_down = 0;
            if (vedit_sel_on && vedit_sel_buf == vedit_cur)
                vedit_sel_copy();
            else
                vedit_sel_on = 0;
        }
    }

    if (!vedit_split_on) {
        vedit_pane_y0 = vedit_code_y;
        vedit_pane_cursor_on = 1;
        for (r = 0; r < vedit_code_rows; r++) {
            li = vedit_top + r;
            vedit_draw_row(canvas, font, r, li, li == vedit_cy);
        }
    } else {
        int rows0 = vedit_code_rows / 2;
        int rows1 = vedit_code_rows - rows0 - 1;
        int sepy;
        if (rows0 < 1) rows0 = 1;
        if (rows1 < 1) rows1 = 1;
        vedit_pane_load(0);
        vedit_clamp();
        vedit_follow();
        vedit_pane_y0 = vedit_code_y;
        vedit_pane_cursor_on = (vedit_apane == 0);
        for (r = 0; r < rows0; r++) {
            li = vedit_top + r;
            vedit_draw_row(canvas, font, r, li, li == vedit_cy);
        }
        sepy = vedit_code_y + rows0 * vedit_ch;
        nk_fill_rect(canvas, nk_rect(0, (float)sepy, (float)NK_W,
                                     (float)vedit_ch),
                     0, vedit_c_status());
        nk_draw_text(canvas,
                     nk_rect((float)vedit_cw, (float)sepy,
                             (float)(NK_W - 2 * vedit_cw), (float)vedit_ch),
                     vedit_fnames[vedit_panes_buf[1]],
                     (int)strlen(vedit_fnames[vedit_panes_buf[1]]), font,
                     vedit_c_status(), vedit_c_headtxt());
        vedit_pane_load(1);
        vedit_clamp();
        vedit_follow();
        vedit_pane_y0 = sepy + vedit_ch;
        vedit_pane_cursor_on = (vedit_apane == 1);
        for (r = 0; r < rows1; r++) {
            li = vedit_top + r;
            vedit_draw_row(canvas, font, r, li, li == vedit_cy);
        }
        vedit_pane_load(vedit_apane);
        vedit_pane_save(vedit_apane);
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
        char flags[32];
        int pct = 0;
        flags[0] = 0;
        if (vedit_count > 0)
            pct = (vedit_cy + 1) * 100 / vedit_count;
        {
            size_t fl = 0;
            if (vedit_ros[vedit_cur] && fl < sizeof(flags) - 5) {
                memcpy(flags + fl, " RO", 3);
                fl += 3;
            }
            if (vedit_overwrite && fl < sizeof(flags) - 5) {
                memcpy(flags + fl, " OVR", 4);
                fl += 4;
            }
            if (vedit_macro_rec && fl < sizeof(flags) - 5) {
                memcpy(flags + fl, " REC", 4);
                fl += 4;
            }
            if (vedit_mark_on && fl < sizeof(flags) - 5) {
                memcpy(flags + fl, " MRK", 4);
                fl += 4;
            }
            if (vedit_sel_on && fl < sizeof(flags) - 5) {
                memcpy(flags + fl, " SEL", 4);
                fl += 4;
            }
            if (vedit_esc_state && fl < sizeof(flags) - 6) {
                memcpy(flags + fl, " META", 5);
                fl += 5;
            }
            if (vedit_arg_on && fl < sizeof(flags) - 5) {
                memcpy(flags + fl, " ARG", 4);
                fl += 4;
            }
            flags[fl] = 0;
        }
        snprintf(status, sizeof(status), " %s [%s] B%d/%d Ln %d/%d(%d%%)"
                 " Col %d%s %s", vedit_fname,
                 vedit_lang_name(vedit_lang), vedit_cur + 1,
                 vedit_count_open(), vedit_cy + 1,
                 vedit_count > 0 ? vedit_count : 1, pct, vedit_cx + 1,
                 flags, vedit_msg);
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

/** Route one decoded key while a prompt is open. */
static void vedit_prompt_key(int key) {
    if (vedit_prompt_mode == VEDIT_PROMPT_QREP) {
        vedit_qrep_answer(key);
        return;
    }
    if (key == '\n' || key == '\r') {
        int mode = vedit_prompt_mode;
        vedit_prompt_on = 0;
        if (vedit_prompt_mode == VEDIT_PROMPT_GOTO) {
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
        } else if (vedit_prompt_mode == VEDIT_PROMPT_NAME) {
            size_t n = strlen(vedit_prompt_buf);
            if (n == 0) {
                vedit_set_msg("empty name, keeping old one");
            } else if (n >= VEDIT_FNAME_MAX) {
                vedit_set_msg("name too long");
            } else {
                memcpy(vedit_fname, vedit_prompt_buf, n);
                vedit_fname[n] = 0;
                vedit_lang = vedit_lang_of(vedit_fname);
                if (vedit_save() == 0)
                    printf("vedit: wrote %d line(s) to %s\n",
                           vedit_count, vedit_fname);
            }
        } else if (vedit_prompt_mode == VEDIT_PROMPT_LINK) {
            vedit_cmd_link(vedit_prompt_buf);
        } else if (mode == VEDIT_PROMPT_ISEARCH_F ||
                   mode == VEDIT_PROMPT_ISEARCH_R) {
            if (vedit_prompt_buf[0]) {
                memcpy(vedit_last_find, vedit_prompt_buf, VEDIT_LINE_MAX);
                vedit_msg[0] = 0;
            } else {
                vedit_cy = vedit_isearch_oy;
                vedit_cx = vedit_isearch_ox;
            }
        } else if (mode == VEDIT_PROMPT_REP_OLD) {
            size_t n = strlen(vedit_prompt_buf);
            if (n == 0) {
                vedit_set_msg("empty pattern");
            } else {
                if (n > VEDIT_MAGIC_MAX - 1) n = VEDIT_MAGIC_MAX - 1;
                memcpy(vedit_qrep_old, vedit_prompt_buf, n);
                vedit_qrep_old[n] = 0;
                vedit_prompt_open("replace with: ", VEDIT_PROMPT_REP_NEW);
            }
        } else if (mode == VEDIT_PROMPT_REP_NEW) {
            size_t n = strlen(vedit_prompt_buf);
            if (n > VEDIT_LINE_MAX - 1) n = VEDIT_LINE_MAX - 1;
            memcpy(vedit_qrep_new, vedit_prompt_buf, n);
            vedit_qrep_new[n] = 0;
            if (vedit_qrep_on)
                vedit_qrep_next(vedit_cy, vedit_cx);
            else
                vedit_replace_all(vedit_qrep_old, vedit_qrep_new, 0);
        } else if (mode == VEDIT_PROMPT_CMD) {
            int id = vedit_cmd_lookup(vedit_prompt_buf);
            if (id < 0) {
                vedit_set_msg("unknown command (M-x help)");
            } else {
                int dq = 0;
                int ds = 0;
                vedit_cmd_exec_id(id, 0, &dq, &ds);
            }
        } else if (mode == VEDIT_PROMPT_SELECT) {
            if (!vedit_prompt_buf[0]) {
                vedit_set_msg("empty name");
            } else if (vedit_select_insert) {
                vedit_select_insert = 0;
                vedit_insert_file(vedit_prompt_buf);
            } else {
                int k;
                int found = -1;
                for (k = 0; k < VEDIT_NBUF; k++) {
                    if (vedit_pools[k] &&
                        strcmp(vedit_fnames[k], vedit_prompt_buf) == 0) {
                        found = k;
                        break;
                    }
                }
                if (found >= 0) {
                    vedit_switch_buffer(found);
                } else {
                    vedit_open_in_buffer(vedit_prompt_buf, 0);
                }
            }
            vedit_select_insert = 0;
        } else if (mode == VEDIT_PROMPT_BINDKEY) {
            if (vedit_parse_key(vedit_prompt_buf) < 0) {
                vedit_set_msg("bad key (try ^K, M-f, PgDn)");
            } else {
                size_t n = strlen(vedit_prompt_buf);
                if (n > sizeof(vedit_bindkey_tmp) - 1)
                    n = sizeof(vedit_bindkey_tmp) - 1;
                memcpy(vedit_bindkey_tmp, vedit_prompt_buf, n);
                vedit_bindkey_tmp[n] = 0;
                vedit_prompt_open("command: ", VEDIT_PROMPT_BINDCMD);
            }
        } else if (mode == VEDIT_PROMPT_BINDCMD) {
            int id = vedit_cmd_lookup(vedit_prompt_buf);
            int kc = vedit_parse_key(vedit_bindkey_tmp);
            if (id < 0) {
                vedit_set_msg("unknown command");
            } else if (kc < 0 || vedit_cmd_bind(kc, id) != 0) {
                vedit_set_msg("bind failed");
            } else {
                vedit_set_msg("bound");
            }
        } else if (mode == VEDIT_PROMPT_SHELLCMD) {
            vedit_shell_command(vedit_prompt_buf);
        } else if (mode == VEDIT_PROMPT_FILTER) {
            vedit_filter_buffer(vedit_prompt_buf);
        } else if (mode == VEDIT_PROMPT_GREP) {
            vedit_grep(vedit_prompt_buf);
        } else if (vedit_find_magic) {
            int w = 0;
            vedit_find_magic = 0;
            if (vedit_search_fwd(vedit_cy, vedit_cx, vedit_prompt_buf, 1,
                                 &w) != 0)
                vedit_set_msg("not found");
            else if (w)
                vedit_set_msg("wrapped");
            else
                vedit_msg[0] = 0;
        } else {
            vedit_find_magic = 0;
            vedit_find(vedit_prompt_buf);
        }
        return;
    }
    if (key == VEDIT_KEY_ESC) {
        if (vedit_prompt_mode == VEDIT_PROMPT_ISEARCH_F ||
            vedit_prompt_mode == VEDIT_PROMPT_ISEARCH_R) {
            vedit_cy = vedit_isearch_oy;
            vedit_cx = vedit_isearch_ox;
        }
        vedit_prompt_on = 0;
        vedit_qrep_on = 0;
        vedit_set_msg("cancelled");
        return;
    }
    if (key == '\b' || key == 127) {
        if (vedit_prompt_pos > 0) {
            vedit_prompt_pos--;
            vedit_prompt_buf[vedit_prompt_pos] = 0;
            if (vedit_prompt_mode == VEDIT_PROMPT_ISEARCH_F ||
                vedit_prompt_mode == VEDIT_PROMPT_ISEARCH_R)
                vedit_isearch_step();
        }
        return;
    }
    if (key >= 32 && key < 127 && vedit_prompt_pos < VEDIT_LINE_MAX - 1) {
        vedit_prompt_buf[vedit_prompt_pos++] = (char)key;
        vedit_prompt_buf[vedit_prompt_pos] = 0;
        if (vedit_prompt_mode == VEDIT_PROMPT_ISEARCH_F ||
            vedit_prompt_mode == VEDIT_PROMPT_ISEARCH_R)
            vedit_isearch_step();
    }
}

/** Route one decoded key when no prompt is open. */
static void vedit_key(int key, int *quit, int *save_and_quit) {
    int rep;
    int k;
    if (vedit_prompt_on) {
        vedit_prompt_key(key);
        return;
    }
    if (key == VEDIT_KEY_ARG) {
        if (!vedit_arg_on) {
            vedit_arg_on = 1;
            vedit_arg = 4;
        } else {
            vedit_arg *= 4;
            if (vedit_arg > 4096) vedit_arg = 4096;
        }
        {
            char nb[32];
            snprintf(nb, sizeof(nb), "arg=%d", vedit_arg);
            vedit_set_msg(nb);
        }
        return;
    }
    if (vedit_arg_on && key >= '0' && key <= '9') {
        vedit_arg = vedit_arg * 10 + (key - '0');
        if (vedit_arg > 4096) vedit_arg = 4096;
        {
            char nb[32];
            snprintf(nb, sizeof(nb), "arg=%d", vedit_arg);
            vedit_set_msg(nb);
        }
        return;
    }
    rep = vedit_arg_on ? vedit_arg : 1;
    vedit_arg_on = 0;
    if (rep < 1) rep = 1;
    if (rep > 4096) rep = 4096;
    if (key != VEDIT_KEY_META('(') && key != VEDIT_KEY_META(')') &&
        key != VEDIT_KEY_META('e') && key != VEDIT_KEY_META('E')) {
        if (vedit_macro_rec && vedit_macro_len < VEDIT_MACRO_MAX)
            vedit_macro[vedit_macro_len++] = key;
    }
    {
        int bound = vedit_cmd_bound(key);
        if (bound >= 0) {
            vedit_cmd_exec_id(bound, 0, quit, save_and_quit);
            return;
        }
    }
    if (key == VEDIT_KEY_UP) {
        for (k = 0; k < rep; k++) {
            if (vedit_cy > 0) vedit_cy--;
        }
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_DOWN) {
        for (k = 0; k < rep; k++) {
            if (vedit_cy + 1 < vedit_count) vedit_cy++;
        }
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_LEFT) {
        for (k = 0; k < rep; k++) {
            if (vedit_cx > 0) {
                vedit_cx--;
            } else if (vedit_cy > 0) {
                vedit_cy--;
                vedit_cx = vedit_used[vedit_cy];
            }
        }
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_RIGHT) {
        for (k = 0; k < rep; k++) {
            if (vedit_count > 0 && vedit_cy < vedit_count &&
                vedit_cx < vedit_used[vedit_cy]) {
                vedit_cx++;
            } else if (vedit_cy + 1 < vedit_count) {
                vedit_cy++;
                vedit_cx = 0;
            }
        }
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_HOME || key == VEDIT_KEY_BOL) {
        vedit_cx = 0;
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_END || key == VEDIT_KEY_EOL) {
        if (vedit_count > 0 && vedit_cy < vedit_count)
            vedit_cx = vedit_used[vedit_cy];
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_MARK || key == VEDIT_KEY_META(' ')) {
        vedit_set_mark();
    } else if (key == VEDIT_KEY_KILL_LINE) {
        for (k = 0; k < rep; k++) {
            if (vedit_kill_line() != 0) break;
        }
    } else if (key == VEDIT_KEY_YANK) {
        vedit_yank();
    } else if (key == VEDIT_KEY_TRANSPOSE) {
        for (k = 0; k < rep; k++) {
            if (vedit_transpose() != 0) break;
        }
    } else if (key == VEDIT_KEY_FENCE) {
        vedit_goto_fence();
    } else if (key == VEDIT_KEY_META('f') || key == VEDIT_KEY_META('F')) {
        for (k = 0; k < rep; k++) vedit_word_move(1);
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_META('b') || key == VEDIT_KEY_META('B')) {
        for (k = 0; k < rep; k++) vedit_word_move(-1);
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_META('c') || key == VEDIT_KEY_META('C')) {
        vedit_case_word(3);
    } else if (key == VEDIT_KEY_META('l') || key == VEDIT_KEY_META('L')) {
        vedit_case_word(2);
    } else if (key == VEDIT_KEY_META('u') || key == VEDIT_KEY_META('U')) {
        vedit_case_word(1);
    } else if (key == VEDIT_KEY_META('w') || key == VEDIT_KEY_META('W')) {
        if (key == VEDIT_KEY_META('W'))
            vedit_region_to_clip();
        else
            vedit_copy_region();
    } else if (key == VEDIT_KEY_META('k') || key == VEDIT_KEY_META('K')) {
        vedit_kill_region();
    } else if (key == VEDIT_KEY_META('s') || key == VEDIT_KEY_META('S')) {
        vedit_prompt_isearch(1);
    } else if (key == VEDIT_KEY_META('r') || key == VEDIT_KEY_META('R')) {
        vedit_prompt_isearch(-1);
    } else if (key == VEDIT_KEY_META('n') || key == VEDIT_KEY_META('N')) {
        if (!vedit_last_find[0]) {
            vedit_set_msg("no previous search");
        } else {
            int w = 0;
            int c = vedit_cx + 1;
            int r = vedit_cy;
            if (c > vedit_used[r]) {
                r++;
                c = 0;
            }
            if (r >= vedit_count ||
                vedit_search_fwd(r, c, vedit_last_find, 0, &w) != 0)
                vedit_set_msg("not found");
            else if (w)
                vedit_set_msg("wrapped");
            else
                vedit_msg[0] = 0;
        }
    } else if (key == VEDIT_KEY_META('%')) {
        vedit_qrep_on = 1;
        vedit_prompt_open("query replace: ", VEDIT_PROMPT_REP_OLD);
    } else if (key == VEDIT_KEY_META('q') || key == VEDIT_KEY_META('Q')) {
        vedit_fill_paragraph();
    } else if (key == VEDIT_KEY_META('x') || key == VEDIT_KEY_META('X')) {
        vedit_prompt_open("M-x ", VEDIT_PROMPT_CMD);
    } else if (key == VEDIT_KEY_META('!')) {
        vedit_prompt_open("!: ", VEDIT_PROMPT_SHELLCMD);
    } else if (key == VEDIT_KEY_META('#')) {
        vedit_prompt_open("filter: ", VEDIT_PROMPT_FILTER);
    } else if (key == VEDIT_KEY_META('(')) {
        vedit_macro_rec = 1;
        vedit_macro_len = 0;
        vedit_set_msg("recording macro");
    } else if (key == VEDIT_KEY_META(')')) {
        vedit_macro_rec = 0;
        vedit_set_msg("macro recorded");
    } else if (key == VEDIT_KEY_META('e') || key == VEDIT_KEY_META('E')) {        if (vedit_macro_len <= 0) vedit_set_msg("no macro");
        else if (vedit_macro_depth >= 4) vedit_set_msg("macro too deep");
        else {
            vedit_macro_depth++;
            for (k = 0; k < vedit_macro_len; k++) {
                vedit_key(vedit_macro[k], quit, save_and_quit);
                if (*quit) break;
            }
            vedit_macro_depth--;
            vedit_msg[0] = 0;
        }
    } else if (key == VEDIT_KEY_META('2')) {
        if (!vedit_split_on) vedit_split_set(1);
        else vedit_set_msg("already split");
    } else if (key == VEDIT_KEY_META('1')) {
        if (vedit_split_on) vedit_split_set(0);
        else vedit_set_msg("single window");
    } else if (key == VEDIT_KEY_META('o') || key == VEDIT_KEY_META('O')) {
        vedit_next_pane();
    } else if (key == VEDIT_KEY_META('v') || key == VEDIT_KEY_META('V')) {
        vedit_clip_paste();
    } else if (key == VEDIT_KEY_PGUP) {
        for (k = 0; k < rep; k++) {
            vedit_cy -= vedit_code_rows;
            if (vedit_cy < 0) {
                vedit_cy = 0;
                break;
            }
        }
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_PGDN) {
        for (k = 0; k < rep; k++) {
            vedit_cy += vedit_code_rows;
            if (vedit_count > 0 && vedit_cy >= vedit_count) {
                vedit_cy = vedit_count - 1;
                break;
            }
        }
        vedit_msg[0] = 0;
    } else if (key == VEDIT_KEY_DEL) {
        vedit_delete_char();
    } else if (key == 15 || key == 19) {
        if (vedit_save() == 0)
            printf("vedit: wrote %d line(s) to %s\n",
                   vedit_count, vedit_fname);
    } else if (key == 23) {
        vedit_prompt_find();
    } else if (key == 14) {
        vedit_prompt_saveas();
    } else if (key == 7) {
        vedit_prompt_open("goto: ", VEDIT_PROMPT_GOTO);
    } else if (key == VEDIT_KEY_RUN) {
        vedit_cmd_run();
    } else if (key == VEDIT_KEY_LINK) {
        vedit_prompt_open("link elf/cvm: ", VEDIT_PROMPT_LINK);
    } else if (key == VEDIT_KEY_DUMP) {
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
        for (k = 0; k < rep; k++) {
            vedit_insert_char(key);
            if (vedit_msg[0]) break;
        }
    } else if (key >= 3000) {
        vedit_set_msg("unbound (M-x help lists keys)");
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
    vedit_kbd_raw(0);
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
    vedit_pane_y0 = vedit_code_y;
    vedit_pane_cursor_on = 1;
    vedit_split_on = 0;
    vedit_apane = 0;
    vedit_panes_buf[0] = vedit_cur;
    vedit_panes_cy[0] = vedit_cy;
    vedit_panes_cx[0] = vedit_cx;
    vedit_panes_top[0] = vedit_top;
    vedit_panes_buf[1] = vedit_cur;
    vedit_panes_cy[1] = vedit_cy;
    vedit_panes_cx[1] = vedit_cx;
    vedit_panes_top[1] = vedit_top;
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
    nk_theme_apply(&ctx, 0);

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
            key = vedit_read_key_poll();
            if (key >= 0) vedit_key(key, &quit, &save_and_quit);
        }
        {
            unsigned t0 = (unsigned)vedit_time_ms();
            while ((unsigned)vedit_time_ms() - t0 < VEDIT_FRAME_MS) {
                __asm__ volatile("pause");
            }
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
    /* Mirror the marker into the RGB twin when the kernel maps it: the
     * present routes there and the origin check would otherwise read the
     * rasterized UI pixel. Mirrored exact, never nearest. */
    if (nk_rgb_available()) {
        volatile uint8_t *mrgb = NK_RGB_BUF;
        mrgb[0] = pal768[0xF0 * 3];
        mrgb[1] = pal768[0xF0 * 3 + 1];
        mrgb[2] = pal768[0xF0 * 3 + 2];
    }
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
    const char *fname;
    if (argc > 1 && strcmp(argv[1], "--selftest") == 0)
        return vedit_selftest();
    if (argc > 1 && strcmp(argv[1], "--selftest-build") == 0)
        return vedit_selftest_build();
    if (argc == 1) {
        fname = VEDIT_DEFAULT_FILE;
    } else if (argc == 2) {
        fname = argv[1];
    } else {
        printf("usage: vedit [file]\n");
        return 1;
    }
    if (strlen(fname) >= VEDIT_FNAME_MAX) {
        printf("vedit: %s: name too long\n", fname);
        return 1;
    }
    n = strlen(fname);
    memcpy(vedit_fname, fname, n);
    vedit_fname[n] = 0;
    for (n = 0; n < VEDIT_NBUF; n++) {
        vedit_pools[n] = 0;
        vedit_useds[n] = 0;
        vedit_sizes[n] = -1;
        vedit_mtimes[n] = -1;
    }
    if (vedit_buf_alloc(0) != 0) {
        printf("vedit: out of memory\n");
        return 1;
    }
    vedit_cur = 0;
    vedit_lang = vedit_lang_of(vedit_fname);
    vedit_dirty = 0;
    vedit_hist_push(fname);
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
    vedit_run_rc("/etc/vedit.rc");
    vedit_run_rc("vedit.rc");
    vedit_gui_run();
    for (n = 0; n < VEDIT_NBUF; n++) {
        free(vedit_pools[n]);
        free(vedit_useds[n]);
    }
    return 0;
}
