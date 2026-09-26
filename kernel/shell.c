#include "kernel.h"
#include "net.h"
#include "httpd.h"
#include "minifs.h"
#include "fat32.h"
#include "ext4.h"
#include "drivers/virtio_blk.h"
#include "sched.h"
#include "smp.h"
#include "percpu_rq.h"
#include "vga_fb.h"
#include "pcspk.h"
#include "sb16.h"
#include "pcm2.h"
#include "rtc.h"
#include "drivers/kbd.h"
#include "wm_layout.h"
#include "wm_notify.h"
#define XXH_STATIC_LINKING_ONLY
#include "xxhash.h"
#include "zip.h"
#include "minifetch.h"
#include "shell.h"
#include "editor.h"
#include "kernel/console_in.h"

/* ================================================================
 *  Shell (kernel/shell.c)
 *
 *  Extracted from kernel.c (Phase 6.1).  The shell owns the console
 *  line reader, the command history and completion, the built-in
 *  editor and every builtin command.  It reaches the rest of the
 *  kernel through the public kernel.h API plus the subsystem
 *  headers; redirect lifecycle lives in kernel/redirect.c and the
 *  capture hot-path (redirect_putc) stays in kernel.c inlined into
 *  vga_putc.
 * ================================================================ */
/* ================================================================
 *  Shell
 * ================================================================ */

/* The CVM interpreter ships on the ramdisk as objects/cvm.o and is loaded
 * on demand the first time a .cvm module is run. */
#define SHELL_CVM_INTERP    "objects/cvm.o"

/* Runnable-file lookup: a bare name is mapped to a toolchain directory by
 * its suffix, so `ld.o` finds objects/ld.o, `fib.elf` finds bin/fib.elf and
 * `w1.cvm` finds cvm/w1.cvm. A bare name with no recognised suffix (cp,
 * freedom, ...) resolves through bin/, the command path. Every candidate is
 * checked for existence before it is run, so a name can never be truncated
 * into a path it does not own. */
typedef struct {
    const char *suffix;    /* matched against the name tail; "" is the default */
    const char *dir;       /* ramdisk directory prefix, no leading slash */
} ShellRunDir;

static const ShellRunDir shell_run_dirs[] = {
    { ".cvm",  "cvm/" },
    { ".o",    "objects/" },
    { ".elf",  "bin/" },
    { "",      "bin/" },
};
#define SHELL_RUN_DIRS (sizeof(shell_run_dirs) / sizeof(shell_run_dirs[0]))

static char cmd_buf[CMD_BUF_SZ];
/** Docstring: Nonzero while the shell blocks in a foreground wait. */
volatile int shell_fg_active = 0;
/* A desktop-icon launch that arrived while a user program owned the CPU.
 * The ISR-driven desktop tick cannot run shell_run_any (it would re-enter
 * k_exec_user from ISR context and corrupt the running program), so the
 * command is queued here and executed as the shell's next command. */
static char shell_pending_cmd[CMD_BUF_SZ];
static int  shell_pending_len;

/* Queue a desktop-icon command to run after the current user program exits.
 * Overwrites any earlier pending launch; safe to call from the ISR (it only
 * copies into a kernel buffer). */
void shell_queue_launch(const char *cmd) {
    unsigned i = 0;
    if (!cmd) return;
    while (cmd[i] && i < (unsigned)CMD_BUF_SZ - 1) {
        shell_pending_cmd[i] = cmd[i];
        i++;
    }
    shell_pending_cmd[i] = 0;
    shell_pending_len = (int)i;
}

#define SHELL_HIST_MAX 16
static char shell_hist[SHELL_HIST_MAX][CMD_BUF_SZ];
static int  shell_hist_count;
static int  shell_hist_idx = -1;
static char shell_line_saved[CMD_BUF_SZ];
static int  shell_line_saved_pos;
/* On-screen cursor column within the edit line, so a repaint can back up to
 * the line start exactly. Kept in sync by every echo/repaint path. */
static int  shell_cur;

/* Multi-window input routing: the focused terminal owns cmd_buf while the
 * prompt is active. Alt-Tab (or `wm focus`, or a title-bar click) parks the
 * half-typed line into the outgoing window and restores the incoming one;
 * shell_edit_gen tells the readline loop its buffer moved under it. */
static int  shell_in_readline;
int  shell_edit_pos;
unsigned shell_edit_gen;
int shell_readline_active(void) { return shell_in_readline; }
void shell_focus_park(void) {
    if (!shell_in_readline) return;
    vga_fb_park_line(cmd_buf, shell_edit_pos);
    shell_hist_idx = -1;
}
void shell_focus_restore(void) {
    int p = 0;
    char tmp[CMD_BUF_SZ];
    if (!shell_in_readline) return;
    if (vga_fb_unpark_line(tmp, &p)) {
        kmemcpy(cmd_buf, tmp, (unsigned long)CMD_BUF_SZ);
        shell_edit_pos = p;
        shell_cur = p;
    } else {
        cmd_buf[0] = '\0';
        shell_edit_pos = 0;
        shell_cur = 0;
        /* Fresh window: print its own prompt so both terminals always
         * show a live `miniOS> ` — unless one is already there (refocus
         * would stack duplicate prompts). No newline on an empty line,
         * so no blank ring entry; otherwise start a new line. */
        if (!vga_fb_prompt_live()) {
            if (vga_fb_act_empty()) vga_puts("miniOS> ");
            else vga_puts("\nminiOS> ");
        }
        shell_cur = (int)kstrlen(cmd_buf);
    }
    shell_hist_idx = -1;
    shell_edit_gen++;
    vga_fb_text_cursor(shell_edit_pos);
}

static void shell_prompt(void) { vga_puts("\nminiOS> "); vga_fb_note_prompt(); }

void shell_exec_builtin(int argc, char **argv);
static int shell_run_pipeline(char **argv, int argc,
        const char *redir_path, int redir_append, int redirected);
static int etrel_path_trusted(const char *full);

/* Strict decimal parse for the `vol` builtin: delegates the digit and
 * overflow work to shell_parse_long and clamps the result to the
 * speaker's valid range. Garbage is rejected, never silently zero. */
static int shell_parse_vol(const char *s, unsigned *out) {
    long v;
    if (!shell_parse_long(s, &v)) return 0;
    if (v < PCSPK_VOL_MIN) v = PCSPK_VOL_MIN;
    if (v > PCSPK_VOL_MAX) v = PCSPK_VOL_MAX;
    *out = (unsigned)v;
    return 1;
}


/* ---- Console input multiplexer (serial + PS/2) ----
 *
 * Bytes from either source are funneled through a small FIFO ("pb") so that
 * escape sequences can be recognised, partially consumed, and re-injected.
 * The PageUp/PageDown keys — whether they arrive as PS/2 E0-prefixed make
 * codes (translated by kbd_read into the standard CSI form) or directly over
 * the serial line as ESC [ 5 ~ / ESC [ 6 ~ — enter a scrollback view of past
 * output; any other key leaves scrollback and is delivered to the caller. */

/* Blocking reads live in kernel/console_in.c; the prompt loop below
 * consumes them through console_getc/console_peek. */

/* non-blocking and classifies it; implementation in kernel/console_in.c. */

/* Read one line into buf (at most size-1 chars). Echoes input and
 * honours backspace. Shared by the shell prompt and the editor. */
void shell_readline_buf(char *buf, int size) {
    int pos = 0;
    kmemset(buf, 0, (unsigned long)size);
    while (1) {
        int c = console_getc();
        if (c < 0) continue;
        if (c == '\n' || c == '\r') {
            vga_putc('\n');
            buf[pos] = 0;
            return;
        }
        if (c == '\b' || c == 0x7F) {
            if (pos > 0) {
                pos--;
                vga_putc('\b');
            }
            continue;
        }
        if (pos < size - 1 && kbd_is_printable(c)) {
            buf[pos++] = (char)c;
            vga_putc((char)c);
        }
    }
}

static void shell_readline_hist(char *buf, int size);

/* The component of a ramdisk path after the last '/', or the whole path when
 * there is no '/'. Used to match a bare command word against a file's name. */
static const char *shell_name_base(const char *path) {
    const char *base = path;
    const char *slash = kstrchr(path, '/');
    while (slash) { base = slash + 1; slash = kstrchr(base, '/'); }
    return base;
}

/* Builtin names for first-word TAB completion (zsh completes builtins;
 * only the shell dispatch below knows them, so they are listed once here
 * for the completer instead of hiding behind the file tiers). */
static const char *shell_builtin_names[] = {
    "bootlog", "cat", "catfs", "cd", "clear", "clip", "clock", "date", "desktop",
    "echo", "edit", "ext4", "fat", "fx", "gdb", "gfx", "hash", "help", "httpd", "irqstat", "jobs", "kbd", "kill", "kstack",
    "load", "ls", "lsfs", "ltrace", "mem", "minifetch",     "mkdir", "mount", "mrun", "mv", "net",
    "nice", "panic", "perf", "poweroff", "ps", "pwd", "rlimit", "rm", "rmdir", "run",
    "schedtop", "seccomp", "sh", "sleep", "smp", "strace", "trace", "unmount", "unzip",
    "vfstest", "vmmap", "vol", "wait", "wm", "zip", "vblk",
};
#define SHELL_BUILTIN_COUNT (sizeof(shell_builtin_names) / sizeof(shell_builtin_names[0]))

/* Runnable tier of a file name for first-word TAB completion: 0=.elf,
 * 1=.cvm, 2=.o, 3=anything else. A bare command word completes toward the
 * highest-priority non-empty tier, so `poke` offers the game binary instead
 * of its icon PNG. */
static int shell_complete_tier(const char *nm) {
    int nl = (int)kstrlen(nm);
    if (nl >= 4 && kstrcmp(nm + nl - 4, ".elf") == 0) return 0;
    if (nl >= 4 && kstrcmp(nm + nl - 4, ".cvm") == 0) return 1;
    if (nl >= 2 && kstrcmp(nm + nl - 2, ".o") == 0) return 2;
    return 3;
}

/* Replace the current word [word_start, word_start+wlen) in `buf` with `text`
 * and move the cursor to the end of the completed line. Bounds checked: a
 * completion that would overflow `size` is refused, never truncated. */
static void shell_line_repaint(char *buf, int size, int pos);
static void shell_complete_replace(char *buf, int size, int *pos,
                                   char *word_start, unsigned long wlen,
                                   const char *text) {
    unsigned long tlen = kstrlen(text);
    unsigned long head = (unsigned long)(word_start - buf);
    unsigned long tail = (unsigned long)(buf + *pos) - (unsigned long)(word_start + wlen);
    if (head + tlen + tail + 1 > (unsigned long)size) return;
    if (tlen != wlen)
        kmemmove(word_start + tlen, word_start + wlen, tail);
    kmemcpy(word_start, text, tlen);
    *pos = (int)(head + tlen + tail);
    buf[*pos] = 0;
    shell_line_repaint(buf, size, *pos);
}

/* Complete an argument word from MiniFS (the ramdisk loop at the call
 * site covers the ramdisk half). The word's directory part resolves
 * against the cwd; entries of that MiniFS directory matching the leaf
 * prefix are offered as full word-relative paths, directories with a
 * trailing '/'. At most 8 entries in static storage, never truncated,
 * duplicates of ramdisk offers skipped. */
static void shell_complete_minifs_arg(const char *word, unsigned long wlen,
                                      char **comps, int *ncomps) {
    static char tab_arg[8][RAMDISK_FNAME_LEN];
    char dir[RAMDISK_FNAME_LEN], leaf[RAMDISK_FNAME_LEN];
    char cdir[RAMDISK_FNAME_LEN];
    unsigned long slash = wlen, leaflen = 0, k;
    int narg = 0, idx = 0, dir_ino;
    MiniFSDirEntry de;
    MiniFSInode st;
    char mname[RAMDISK_FNAME_LEN];
    unsigned long dl;
    for (k = 0; k < wlen; k++)
        if (word[k] == '/') slash = k;
    if (slash < wlen) {
        if (slash >= sizeof(dir)) return;
        kmemcpy(dir, word, slash);
        dir[slash] = 0;
        leaflen = wlen - slash - 1;
        if (leaflen >= sizeof(leaf)) return;
        kmemcpy(leaf, word + slash + 1, leaflen);
        leaf[leaflen] = 0;
    } else {
        dir[0] = 0;
        if (wlen >= sizeof(leaf)) return;
        kmemcpy(leaf, word, wlen);
        leaf[wlen] = 0;
    }
    if (dir[0]) {
        if (!fs_resolve(dir, cdir, sizeof(cdir))) return;
    } else {
        kmemcpy(cdir, fs_cwd, sizeof(cdir));
    }
    dl = kstrlen(cdir);
    if (dl > 0 && cdir[dl - 1] == '/') cdir[dl - 1] = 0;
    if (!minifs_is_mounted()) return;
    dir_ino = minifs_resolve_path(cdir);
    if (dir_ino < 0) return;
    if (minifs_stat(dir_ino, &st) < 0) return;
    if ((st.mode & MINIFS_S_IFMT) != MINIFS_S_IFDIR) return;
    while (narg < 8 && *ncomps < 32 &&
           minifs_dir_read(dir_ino, idx, &de, mname) == 0) {
        unsigned long ml, base;
        int isdir = 0, dup = 0, j;
        MiniFSInode est;
        idx++;
        if (de.inode == 0) continue;
        if (kstrncmp(mname, leaf, leaflen) != 0) continue;
        ml = kstrlen(mname);
        if (minifs_stat(de.inode, &est) == 0 &&
            (est.mode & MINIFS_S_IFMT) == MINIFS_S_IFDIR) isdir = 1;
        base = (slash < wlen) ? slash + 1 : 0;
        if (base + ml + (unsigned long)(isdir ? 1 : 0) + 1 > sizeof(tab_arg[0]))
            continue;
        kmemcpy(tab_arg[narg], word, base);
        kmemcpy(tab_arg[narg] + base, mname, ml + 1);
        if (isdir) {
            tab_arg[narg][base + ml] = '/';
            tab_arg[narg][base + ml + 1] = 0;
        }
        for (j = 0; j < *ncomps; j++)
            if (kstrcmp(comps[j], tab_arg[narg]) == 0) { dup = 1; break; }
        if (dup) continue;
        comps[(*ncomps)++] = tab_arg[narg];
        narg++;
    }
}

static void shell_readline(void) {
    shell_readline_hist(cmd_buf, CMD_BUF_SZ);
}

/* Redraw the edit line: erase what is shown, then write `text` into buf and
 * onto the console, leaving the text cursor at `*pos`. The cursor is drawn
 * on the framebuffer terminal; on the serial console the text is rewritten
 * and the reader's position is implied by the console cursor. */
static void shell_hist_show(char *buf, int size, int *pos, const char *text) {
    int i, n = 0;
    /* Erase the whole current line: back up to its start, blank it, return. */
    for (i = 0; i < shell_cur; i++) vga_putc('\b');
    for (i = 0; i < shell_cur; i++) vga_putc(' ');
    for (i = 0; i < shell_cur; i++) vga_putc('\b');
    kmemset(buf, 0, (unsigned long)size);
    while (text[n] && n < size - 1) {
        buf[n] = text[n];
        vga_putc(text[n]);
        n++;
    }
    *pos = n;
    shell_cur = n;
    vga_fb_text_cursor(n);
}

/* Repaint the edit line after a cursor move or mid-line edit: erase the whole
 * visible line, rewrite buf, then back the console cursor up to `pos` and
 * redraw the framebuffer text cursor there. `shell_cur` holds the on-screen
 * cursor column, so the erase backs up to the line start before blanking it
 * (a serial backspace alone does not clear a character). */
static void shell_line_repaint(char *buf, int size, int pos) {
    int i, len = (int)kstrlen(buf);
    for (i = 0; i < shell_cur; i++) vga_putc('\b');
    for (i = 0; i < len; i++) vga_putc(' ');
    for (i = 0; i < len; i++) vga_putc('\b');
    for (i = 0; i < len; i++) vga_putc(buf[i]);
    for (i = len; i > pos; i--) vga_putc('\b');
    shell_cur = pos;
    vga_fb_text_cursor(pos);
}

/* Insert character c into buf at `pos`, shifting the tail right. Bounds
 * checked; the caller repaints afterwards. */
static void shell_line_insert(char *buf, int size, int *pos, char c) {
    int len = (int)kstrlen(buf);
    if (len >= size - 1) return;
    kmemmove(buf + *pos + 1, buf + *pos, (unsigned long)(len - *pos + 1));
    buf[*pos] = c;
    (*pos)++;
}

/* Delete the character before the cursor (backspace). */
static void shell_line_backspace(char *buf, int size, int *pos) {
    int len = (int)kstrlen(buf);
    if (*pos <= 0) return;
    kmemmove(buf + *pos - 1, buf + *pos, (unsigned long)(len - *pos + 1));
    (*pos)--;
}

/* Delete the character at the cursor (Delete key). */
static void shell_line_delete(char *buf, int size, int *pos) {
    int len = (int)kstrlen(buf);
    if (*pos >= len) return;
    kmemmove(buf + *pos, buf + *pos + 1, (unsigned long)(len - *pos));
}

/* Delete from the cursor to the start of the line (Ctrl+U). */
static void shell_line_kill_front(char *buf, int size, int *pos) {
    int len = (int)kstrlen(buf);
    kmemmove(buf, buf + *pos, (unsigned long)(len - *pos + 1));
    *pos = 0;
}

/* Delete from the cursor to the end of the line (Ctrl+K). */
static void shell_line_kill_tail(char *buf, int size, int *pos) {
    buf[*pos] = '\0';
}

/* Delete the word before the cursor (Ctrl+W): skip spaces, then non-spaces. */
static void shell_line_kill_word(char *buf, int size, int *pos) {
    int len = (int)kstrlen(buf);
    int s = *pos;
    while (s > 0 && buf[s - 1] == ' ') s--;
    while (s > 0 && buf[s - 1] != ' ') s--;
    kmemmove(buf + s, buf + *pos, (unsigned long)(len - *pos + 1));
    *pos = s;
}

/* Most recent history entry starting with `prefix` (of length plen) that is
 * strictly longer than the prefix, or -1 when there is none. The suggestion
 * for a typed prefix is always the newest match, zsh-style. */
static int shell_hist_newest_match(const char *prefix, unsigned long plen) {
    int i;
    if (!prefix || plen == 0) return -1;
    for (i = shell_hist_count - 1; i >= 0; i--) {
        if (kstrncmp(shell_hist[i], prefix, plen) == 0 &&
            kstrlen(shell_hist[i]) > plen)
            return i;
    }
    return -1;
}

/* Move through the history ring with a zsh-style prefix filter: Up recalls
 * the most recent older entry starting with what was typed, Down moves
 * forward again and finally restores the live line. The prefix is the live
 * line saved on the first Up, so typing "minigcc" then Up/Up walks only the
 * commands starting with "minigcc". An empty line matches every entry, i.e.
 * plain chronological recall. Any printable edit while scrolling drops back
 * to the live line (handled by the caller resetting shell_hist_idx). */
static void shell_hist_nav(char *buf, int size, int *pos, int up) {
    unsigned long plen;
    int i;
    if (shell_hist_count == 0) return;
    if (up) {
        const char *prefix;
        if (shell_hist_idx < 0) {
            kmemcpy(shell_line_saved, buf, (unsigned long)size);
            shell_line_saved_pos = *pos;
            prefix = shell_line_saved;
            i = shell_hist_count - 1;
        } else {
            prefix = shell_line_saved;
            i = shell_hist_idx - 1;
        }
        plen = kstrlen(prefix);
        while (i >= 0 && kstrncmp(shell_hist[i], prefix, plen) != 0) i--;
        if (i < 0) return;
        shell_hist_idx = i;
        shell_hist_show(buf, size, pos, shell_hist[shell_hist_idx]);
    } else {
        if (shell_hist_idx < 0) return;
        plen = kstrlen(shell_line_saved);
        i = shell_hist_idx + 1;
        while (i < shell_hist_count &&
               kstrncmp(shell_hist[i], shell_line_saved, plen) != 0) i++;
        if (i >= shell_hist_count) {
            shell_hist_idx = -1;
            shell_hist_show(buf, size, pos, shell_line_saved);
            *pos = shell_line_saved_pos;
            shell_line_repaint(buf, size, *pos);
            return;
        }
        shell_hist_idx = i;
        shell_hist_show(buf, size, pos, shell_hist[shell_hist_idx]);
    }
}

/* Shell prompt readline: like shell_readline_buf plus command history.
 * Up arrow (ESC [ A) recalls the previous command starting with the typed
 * prefix (empty prefix recalls everything), down arrow moves forward.
 * Right arrow at end of line accepts the newest history match for the
 * prefix; TAB completes programs, files and recent history words. Any
 * editing key while scrolling returns to the live line. */
static void shell_readline_hist(char *buf, int size) {
    int pos = 0;
    unsigned gen;
    kmemset(buf, 0, (unsigned long)size);
    shell_in_readline = 1;
    shell_edit_pos = 0;
    gen = shell_edit_gen;
    while (1) {
        int c;
        shell_edit_pos = pos;
        c = console_getc();
        if (c < 0) continue;
        /* A window switch moved cmd_buf under us (Alt-Tab, `wm focus`,
         * title click): adopt the incoming window's line and handle this
         * byte against it. The byte arrived after the switch, so it
         * belongs to the new window; discarding it here ate the first
         * keystroke after every Alt-Tab ("wm list" ran as "m list").
         * The screen already shows the line; no repaint needed. */
        if (gen != shell_edit_gen) {
            gen = shell_edit_gen;
            pos = shell_edit_pos;
        }
        /* Ctrl+C at the prompt: no foreground job to kill, so bell and
         * keep the line (foreground waits handle ^C separately). Ctrl+D
         * is EOF: an empty line submits (fresh prompt), a non-empty
         * line bells like a terminal. */
        if (c == 0x03) { vga_putc('\a'); continue; }
        if (c == 0x04) {
            if (kstrlen(buf)) { vga_putc('\a'); continue; }
            c = '\n';
        }
        if (c == '\n' || c == '\r') {
            vga_putc('\n');
            vga_fb_hide_text_cursor();
            shell_cur = 0;
            shell_in_readline = 0;
            buf[kstrlen(buf)] = 0;
            shell_hist_idx = -1;
            if (buf[0] && (shell_hist_count == 0 ||
                kstrcmp(shell_hist[shell_hist_count - 1], buf) != 0)) {
                if (shell_hist_count == SHELL_HIST_MAX) {
                    for (int i = 1; i < SHELL_HIST_MAX; i++)
                        kmemcpy(shell_hist[i - 1], shell_hist[i],
                                (unsigned long)CMD_BUF_SZ);
                    shell_hist_count--;
                }
                kmemcpy(shell_hist[shell_hist_count], buf,
                        (unsigned long)CMD_BUF_SZ);
                shell_hist_count++;
            }
            return;
        }
        if (c == KEY_ESC) {
            if (console_peek() == KEY_CSI) {
                console_getc();
                int b = console_peek();
                if (b == KEY_ARR_UP || b == KEY_ARR_DOWN) {
                    console_getc();
                    shell_hist_nav(buf, size, &pos, b == KEY_ARR_UP);
                } else if (b == KEY_ARR_LEFT || b == KEY_ARR_RIGHT) {
                    console_getc();
                    int len = (int)kstrlen(buf);
                    if (b == KEY_ARR_RIGHT && pos >= len && len > 0) {
                        /* At end of line: accept the autosuggestion, i.e.
                         * complete to the most recent history entry starting
                         * with the typed prefix. The prefix is kept for
                         * further Up/Down navigation. A plain cursor move
                         * would be a no-op here, so nothing is lost. */
                        int m = shell_hist_newest_match(buf, (unsigned long)len);
                        if (m >= 0) {
                            if (shell_hist_idx < 0) {
                                kmemcpy(shell_line_saved, buf, (unsigned long)size);
                                shell_line_saved_pos = pos;
                            }
                            shell_hist_idx = m;
                            shell_hist_show(buf, size, &pos, shell_hist[m]);
                            continue;
                        }
                    }
                    int npos = pos + (b == KEY_ARR_RIGHT ? 1 : -1);
                    if (npos >= 0 && npos <= len) {
                        pos = npos;
                        shell_line_repaint(buf, size, pos);
                    }
                } else if (b == KEY_HOME_SEQ || b == KEY_END_SEQ) {
                    console_getc();
                    pos = (b == KEY_HOME_SEQ) ? 0 : (int)kstrlen(buf);
                    shell_line_repaint(buf, size, pos);
                } else if (b == '3') {
                    console_getc();
                    /* The `~` terminator may not have arrived yet over serial;
                     * read it blocking. A non-~ byte is pushed back and
                     * reprocessed on the next loop iteration. */
                    int t = console_getc();
                    if (t == KEY_TILDE) {
                        shell_line_delete(buf, size, &pos);
                        shell_line_repaint(buf, size, pos);
                    } else if (t >= 0) {
                        console_ungetc((unsigned char)t);
                    }
                }
            }
            continue;
        }
        if (c == '\t') {
            char *word_start = buf + pos;
            while (word_start > buf && word_start[-1] != ' ' && word_start[-1] != '\t')
                word_start--;
            unsigned long wlen = (unsigned long)pos - (unsigned long)(word_start - buf);
            if (wlen == 0) { vga_putc('\a'); continue; }
            char *comps[32];
            int ncomps = 0;
            if (word_start == buf) {
                /* First word: newest history commands complete too, so TAB
                 * after "minigcc" offers the most recent matching command
                 * first. Only the command word (up to the first space) is
                 * a candidate; full lines are recalled with Up/Right. */
                static char tab_hist_tok[8][32];
                int ntok = 0;
                for (int hi = shell_hist_count - 1; hi >= 0 && ntok < 8; hi--) {
                    const char *e = shell_hist[hi];
                    unsigned long tl = 0;
                    while (e[tl] && e[tl] != ' ' && e[tl] != '\t') tl++;
                    if (tl <= wlen || tl >= sizeof(tab_hist_tok[0])) continue;
                    if (kstrncmp(e, word_start, wlen) != 0) continue;
                    int dup = 0;
                    for (int k = 0; k < ntok; k++) {
                        if (kstrncmp(tab_hist_tok[k], e, tl) == 0 &&
                            tab_hist_tok[k][tl] == 0) { dup = 1; break; }
                    }
                    if (dup) continue;
                    kmemcpy(tab_hist_tok[ntok], e, tl);
                    tab_hist_tok[ntok][tl] = 0;
                    comps[ncomps++] = tab_hist_tok[ntok];
                    ntok++;
                }
            }
            for (int i = 0; i < kprog_count && ncomps < 32; i++) {
                int dup = 0;
                if (kstrncmp(kprog_table[i].name, word_start, wlen) != 0)
                    continue;
                for (int k = 0; k < ncomps; k++) {
                    if (kstrcmp(comps[k], kprog_table[i].name) == 0) { dup = 1; break; }
                }
                if (!dup)
                    comps[ncomps++] = kprog_table[i].name;
            }
            for (unsigned long i = 0; i < SHELL_BUILTIN_COUNT && ncomps < 32; i++) {
                int dup = 0;
                if (kstrncmp(shell_builtin_names[i], word_start, wlen) != 0)
                    continue;
                for (int k = 0; k < ncomps; k++) {
                    if (kstrcmp(comps[k], shell_builtin_names[i]) == 0) { dup = 1; break; }
                }
                if (!dup)
                    comps[ncomps++] = (char *)shell_builtin_names[i];
            }
            if (ncomps == 0) {
                /* A bare first word (no '/') completes runnable-first: the
                 * .elf tier, then .cvm, then .o, across the ramdisk and the
                 * MiniFS root (where the big ELFs live under bare names),
                 * and only the highest-priority non-empty tier is kept. An
                 * explicit path or an argument word keeps every match, so
                 * navigating to data files still works. */
                int first_bare = (word_start == buf);
                if (first_bare) {
                    for (unsigned long k = 0; k < wlen; k++) {
                        if (word_start[k] == '/') { first_bare = 0; break; }
                    }
                }
                if (first_bare) {
                    static char tab_mini[8][RAMDISK_FNAME_LEN];
                    int nmini = 0;
                    if (minifs_is_mounted()) {
                        MiniFSDirEntry de;
                        char mname[RAMDISK_FNAME_LEN];
                        int idx = 0;
                        while (nmini < 8 &&
                               minifs_dir_read(MINIFS_ROOT_INODE, idx, &de, mname) == 0) {
                            idx++;
                            if (de.inode == 0) continue;
                            if (kstrncmp(mname, word_start, wlen) != 0) continue;
                            MiniFSInode st;
                            int isdir = (minifs_stat(de.inode, &st) == 0 &&
                                         (st.mode & 0170000) == 0040000);
                            unsigned long ml = kstrlen(mname);
                            if (ml + (unsigned long)(isdir ? 1 : 0) + 1 >
                                sizeof(tab_mini[0])) continue;
                            kmemcpy(tab_mini[nmini], mname, ml + 1);
                            if (isdir) {
                                tab_mini[nmini][ml] = '/';
                                tab_mini[nmini][ml + 1] = 0;
                            }
                            nmini++;
                        }
                    }
                    RDFile *files[RAMDISK_MAX_FILES];
                    int n = ramdisk_list(files, RAMDISK_MAX_FILES);
                    for (int t = 0; t < 4 && ncomps < 32; t++) {
                        int before = ncomps;
                        for (int i = 0; i < n && ncomps < 32; i++) {
                            const char *nm = files[i]->name;
                            if (kstrncmp(nm, word_start, wlen) != 0 &&
                                kstrncmp(shell_name_base(nm), word_start, wlen) != 0)
                                continue;
                            if (shell_complete_tier(nm) != t) continue;
                            comps[ncomps++] = (char *)nm;
                        }
                        for (int i = 0; i < nmini && ncomps < 32; i++) {
                            if (shell_complete_tier(tab_mini[i]) != t) continue;
                            comps[ncomps++] = tab_mini[i];
                        }
                        if (ncomps > before) break;
                    }
                } else {
                    RDFile *files[RAMDISK_MAX_FILES];
                    int n = ramdisk_list(files, RAMDISK_MAX_FILES);
                    for (int i = 0; i < n && ncomps < 32; i++) {
                        const char *base = shell_name_base(files[i]->name);
                        if (kstrncmp(files[i]->name, word_start, wlen) == 0 ||
                            kstrncmp(base, word_start, wlen) == 0)
                            comps[ncomps++] = files[i]->name;
                    }
                    /* Argument words complete MiniFS paths too: without
                     * this a file created under a MiniFS-only directory
                     * (every redirect outside the ramdisk namespace) can
                     * never be TAB-completed. */
                    if (ncomps < 32)
                        shell_complete_minifs_arg(word_start, wlen, comps,
                                                  &ncomps);
                }
            }
            if (ncomps == 0) { vga_putc('\a'); continue; }
            if (ncomps == 1) {
                if (kstrcmp(comps[0], word_start) != 0)
                    shell_complete_replace(buf, size, &pos, word_start, wlen, comps[0]);
                else {
                    if (pos < size - 1) { buf[pos++] = ' '; buf[pos] = 0; }
                    vga_putc(' ');
                    shell_cur = pos;
                }
                continue;
            }
            unsigned long common = kstrlen(comps[0]);
            for (int i = 1; i < ncomps; i++) {
                unsigned long l = kstrlen(comps[i]);
                if (l < common) common = l;
                unsigned long j;
                for (j = 0; j < common; j++)
                    if (comps[0][j] != comps[i][j]) break;
                common = j;
            }
            if (common > wlen && kstrncmp(comps[0], word_start, wlen) == 0) {
                char prefix[RAMDISK_FNAME_LEN];
                if (common < sizeof(prefix)) {
                    kmemcpy(prefix, comps[0], common);
                    prefix[common] = 0;
                    shell_complete_replace(buf, size, &pos, word_start, wlen, prefix);
                }
                continue;
            }
            vga_puts("Possible completions:");
            vga_putc('\n');
            for (int i = 0; i < ncomps; i++) {
                vga_puts("  ");
                vga_puts(comps[i]);
                vga_putc('\n');
            }
            continue;
        }
        if (c == '\b' || c == 0x7F || kbd_is_printable(c)) {
            if (shell_hist_idx >= 0) shell_hist_idx = -1;
        }
        /* Ctrl keys: A/E start/end, U kill front, K kill tail, W kill word. */
        if (c == 0x01 || c == 0x05) {
            pos = (c == 0x01) ? 0 : (int)kstrlen(buf);
            shell_line_repaint(buf, size, pos);
            continue;
        }
        if (c == 0x15) { /* Ctrl+U */
            shell_line_kill_front(buf, size, &pos);
            shell_line_repaint(buf, size, pos);
            continue;
        }
        if (c == 0x0B) { /* Ctrl+K */
            shell_line_kill_tail(buf, size, &pos);
            shell_line_repaint(buf, size, pos);
            continue;
        }
        if (c == 0x17) { /* Ctrl+W */
            shell_line_kill_word(buf, size, &pos);
            shell_line_repaint(buf, size, pos);
            continue;
        }
        if (c == '\b' || c == 0x7F) {
            if (pos > 0) {
                int at_end = (pos == (int)kstrlen(buf));
                shell_line_backspace(buf, size, &pos);
                if (at_end) {
                    vga_putc('\b'); vga_putc(' '); vga_putc('\b');
                    shell_cur = pos;
                } else {
                    shell_line_repaint(buf, size, pos);
                }
            }
            continue;
        }
        if (pos < size - 1 && kbd_is_printable(c)) {
            int at_end = (pos == (int)kstrlen(buf));
            shell_line_insert(buf, size, &pos, (char)c);
            if (at_end) {
                vga_putc(c);
                shell_cur = pos;
            } else {
                shell_line_repaint(buf, size, pos);
            }
        }
    }
}

int shell_parse(char *line, char **argv, int max_args) {
    int argc = 0;
    char *p = line;
    while (*p && argc < max_args) {
        while (*p == ' ' || *p == '\t') p++;
        if (*p == 0) break;
        if (*p == '"') {
            p++;
            argv[argc++] = p;
            while (*p && *p != '"') p++;
            if (*p) { *p = 0; p++; }
        } else {
            argv[argc++] = p;
            while (*p && *p != ' ' && *p != '\t') p++;
            if (*p) { *p = 0; p++; }
        }
    }
    argv[argc] = 0;
    return argc;
}


static void desktop_unflag(const char *name);

/* Startup commands from etc/init: one shell command per line, `#`
 * comments and blank lines skipped. Runs once at boot before the
 * first prompt; a missing file means a plain boot. Each line goes
 * through the same parse + redirect + builtin dispatch as an
 * interactive command, so init stays a plain command list. */
static void shell_run_init(void) {
    KFILE *f = kfopen("etc/init", "r");
    char line[CMD_BUF_SZ];
    if (!f) return;
    while (kfgets(line, sizeof(line), f)) {
        char *argv[MAX_ARGS + 1];
        char *redir_path = 0;
        int redir_append = 0;
        int redirected;
        int argc;
        unsigned n = 0;
        while (line[n] && line[n] != '\n' && line[n] != '\r') n++;
        if (!line[n]) {
            /* No line end: the command overflowed the buffer. Drain
             * the rest so the tail never runs as its own command. */
            int c;
            do { c = kfgetc(f); } while (c >= 0 && c != '\n');
            continue;
        }
        line[n] = 0;
        {
            char *p = line;
            while (*p == ' ' || *p == '\t') p++;
            if (*p == 0 || *p == '#') continue;
        }
        argc = shell_parse(line, argv, MAX_ARGS);
        if (argc <= 0) continue;
        redirected = shell_take_redirect(&argc, argv, &redir_path, &redir_append);
        if (redirected < 0 || argc == 0) continue;
        if (shell_run_pipeline(argv, argc, redir_path, redir_append, redirected))
            continue;
        if (redirected && !redirect_begin()) continue;
        shell_exec_builtin(argc, argv);
        if (redirected && redirect_commit(redir_path, redir_append) != 0)
            kprintf("init: cannot write %s\n", redir_path);
    }
    kfclose(f);
}

void shell_run(void) {
    /* Drop session flags left by a previous life (poweroff during a
     * desktop session): client mode with no server would blind NK
     * apps, and a stale quit is a stop nobody asked for. Once per
     * boot, before the first prompt. */
    desktop_unflag("client");
    desktop_unflag("quit");
    shell_run_init();
    while (1) {
        /* Reap finished background jobs before printing the prompt, so a
         * dead job never lingers past one command and pid slots cannot
         * leak. At a fresh prompt act is empty, so the report cannot
         * corrupt a half-typed line. */
        {
            int rp, rc;
            while (shell_reap_nb(&rp, &rc))
                kprintf("job done: pid %d code: %d\n", rp, rc);
        }
        if (shell_pending_len > 0) {
            /* A desktop icon was clicked while a program ran; run it now
             * that the shell has control again, without a fresh prompt.
             * Through desktop_launch so the cwd pin applies: a queued
             * icon is still an icon, not a shell-relative command. */
            desktop_launch(shell_pending_cmd);
            shell_pending_len = 0;
            continue;
        } else {
            shell_prompt();
            shell_readline();
        }

        /* An empty submit (Enter / Ctrl+D on a blank line) consumed the
         * live prompt too: clear it before looping, or every refocus
         * stacks another `miniOS> ` on the window. */
        vga_fb_clear_prompt();
        if (cmd_buf[0] == 0) continue;

        char *argv[MAX_ARGS + 1];
        int argc = shell_parse(cmd_buf, argv, MAX_ARGS);

        if (argc == 0) continue;

        char *redir_path = 0;
        int redir_append = 0;
        int redirected = shell_take_redirect(&argc, argv, &redir_path, &redir_append);
        if (redirected < 0) {
            vga_puts("syntax: > needs a target file\n");
            continue;
        }
        if (argc == 0) {
            vga_puts("syntax: > needs a command\n");
            continue;
        }
        if (shell_run_pipeline(argv, argc, redir_path, redir_append, redirected))
            continue;
        if (redirected && !redirect_begin()) {
            vga_puts("redirect: out of memory\n");
            continue;
        }

        shell_exec_builtin(argc, argv);

        if (redirected && redirect_commit(redir_path, redir_append) != 0)
            kprintf("redirect: cannot write %s\n", redir_path);
    }
}

/* Load an ELF file from the ramdisk and register it under its filename stem.
 * Returns 1 for an ET_REL program, 2 for an ET_EXEC/ET_DYN Linux process,
 * 0 on failure.  progname_out must hold at least 32 bytes. */
static int shell_load(const char *fname, char *progname_out, void **entry_out) {
    char resolved[RAMDISK_FNAME_LEN];
    if (!fs_resolve(fname, resolved, sizeof(resolved))) return 0;
    if (fs_is_dir(resolved)) return 0;
    RDFile *f = ramdisk_open(resolved);
    unsigned char *data = 0;
    unsigned data_size = 0;
    if (f) {
        data_size = f->size;
        data = kmalloc(data_size ? data_size : 1);
        if (!data) return 0;
        ramdisk_read(f, data, 0, data_size);
    } else if (minifs_is_mounted()) {
        int ino = minifs_resolve_path(resolved);
        if (ino < 0 && kstrchr(resolved, '/')) {
            const char *base = resolved;
            const char *p;
            for (p = resolved; *p; p++)
                if (*p == '/') base = p + 1;
            ino = minifs_resolve_path(base);
        }
        if (ino >= 0) {
            MiniFSInode st;
            if (minifs_stat(ino, &st) >= 0 && st.size > 0) {
                data_size = st.size;
                data = kmalloc(data_size);
                if (!data) return 0;
                minifs_read(ino, data, 0, data_size);
            }
        }
    }
    if (!data) return 0;

    const char *base = resolved;
    const char *slash = kstrchr(base, '/');
    while (slash) { base = slash + 1; slash = kstrchr(base, '/'); }
    const char *dot = kstrchr(base, '.');
    int nl = dot ? (int)(dot - base) : (int)kstrlen(base);
    if (nl > 30) nl = 30;
    kmemcpy(progname_out, base, nl);
    progname_out[nl] = 0;

    int kind = 0;
    void *entry = 0;
    if (data_size >= 4 && data[0] == 0x7F && data[1] == 'E' && data[2] == 'L' && data[3] == 'F') {
        Elf64_Half etype = ((Elf64_Ehdr *)data)->e_type;
        if (etype == ET_REL) {
            if (!etrel_path_trusted(resolved)) {
                kprintf("load: refusing untrusted ET_REL '%s'", resolved);
            } else {
                entry = elf_load(data, data_size, 0);
                if (entry) { k_register_program(progname_out, (prog_entry_t)entry); kind = 1; }
            }
        } else if (etype == ET_EXEC || etype == ET_DYN) {
            entry = load_exec_elf(data, data_size);
            if (entry) { k_register_process(progname_out, entry); kind = 2; }
        }
    }
    if (entry_out) *entry_out = entry;
    kfree(data);
    return kind;
}

static inline void outw_port(unsigned short port, unsigned short val) {
    __asm__ volatile("outw %0, %1" : : "a"(val), "Nd"(port));
}

#define QEMU_PM_PORT 0x604

static void shell_cmd_poweroff(void) {
    vga_puts("powering off\n");
    outw_port(QEMU_PM_PORT, 0x2000);
    while (1) __asm__ volatile("hlt");
}

/* ---- Runnable-file resolution (objects/ bin/ cvm/) ----
 *
 * `run <file>` and a bare `<file>` share one resolver and one loader. A bare
 * name is mapped through shell_run_dirs by its suffix; a path with a '/' is
 * resolved against the cwd. Every candidate must exist as a real file before
 * it is considered. The same resolver backs the shell prompt's TAB
 * completion, so what completes is exactly what can run. */

/* The toolchain directory that owns `name`, chosen by suffix. Bare names with
 * no recognised suffix fall through to the command path bin/. */
static const ShellRunDir *shell_run_dir_for(const char *name) {
    int i;
    for (i = 0; i < SHELL_RUN_DIRS; i++) {
        const char *suf = shell_run_dirs[i].suffix;
        if (suf[0] == 0) continue;
        int sl = (int)kstrlen(suf);
        int nl = (int)kstrlen(name);
        if (nl >= sl && kstrcmp(name + nl - sl, suf) == 0)
            return &shell_run_dirs[i];
    }
    for (i = 0; i < SHELL_RUN_DIRS; i++)
        if (shell_run_dirs[i].suffix[0] == 0)
            return &shell_run_dirs[i];
    return &shell_run_dirs[0];
}

/* Is `resolved` (already normalised against the cwd) a real ramdisk file? A
 * directory name or a non-existent path is rejected, never run. */
static int shell_file_is_real(const char *resolved) {
    if (!resolved[0]) return 0;
    if (fs_is_dir(resolved)) return 0;
    return ramdisk_open(resolved) ? 1 : 0;
}

/* Resolve `name` to a full ramdisk path suitable for running. A bare name is
 * tried first against the cwd, then through the suffix-picked toolchain
 * directory, then through the remaining directories as fallback. Returns 1
 * and fills `out` (cap bytes) on success, 0 when no candidate is a real file.
 * A candidate that cannot fit `cap` is skipped like a missing file, never
 * truncated. */
static int shell_resolve_run(const char *name, char *out, unsigned cap) {
    char cand[RAMDISK_FNAME_LEN];
    if (kstrchr(name, '/')) {
        if (!fs_resolve(name, cand, sizeof(cand))) return 0;
        if (!shell_file_is_real(cand)) return 0;
        kmemcpy(out, cand, kstrlen(cand) + 1);
        return 1;
    }
    if (fs_resolve(name, cand, sizeof(cand)) && shell_file_is_real(cand)) {
        kmemcpy(out, cand, kstrlen(cand) + 1);
        return 1;
    }
    const ShellRunDir *pref = shell_run_dir_for(name);
    unsigned long pref_off = (unsigned long)(pref - shell_run_dirs);
    int i;
    for (i = 0; i < SHELL_RUN_DIRS; i++) {
        const ShellRunDir *d =
            &shell_run_dirs[(pref_off + (unsigned long)i) % SHELL_RUN_DIRS];
        unsigned dl = (unsigned)kstrlen(d->dir);
        unsigned nl = (unsigned)kstrlen(name);
        if (dl + nl + 1 > sizeof(cand)) continue;
        kmemcpy(cand, d->dir, dl);
        kmemcpy(cand + dl, name, nl + 1);
        if (shell_file_is_real(cand)) {
            if (dl + nl + 1 > cap) return 0;
            kmemcpy(out, cand, dl + nl + 1);
            return 1;
        }
    }
    return 0;
}

/* ET_REL trust gate (boyscout fix for ring-0 .o without validation):
 * relocatables execute as kernel extensions, so only the toolchain
 * directory (ETREL_TRUSTED_DIR in kernel.h) owns them. `full` is already
 * normalised by fs_resolve (".."/"."/"//" collapsed, no symlinks on
 * MiniFS), so a prefix match is a containment proof, not a string hope.
 * TOCTOU note: the bytes are snapshotted into a kernel buffer at open
 * time and the gate checks the same resolved path the bytes were read
 * from; swapping the file between resolve and open only changes WHICH
 * bytes load, and hostile bytes still face the ELF/reloc validators plus
 * the ETREL_IMAGE_MAX cap. ET_EXEC/ET_DYN/CVM are unaffected. */
static int etrel_path_trusted(const char *full) {
    const char *p = full;
    unsigned i;
    if (p[0] == '/') p++;
    for (i = 0; p[i] && p[i] != '/'; i++) {
        if (p[i] == '.' && (p[i + 1] == 0 || p[i + 1] == '/')) return 0;
    }
    if (kstrncmp(p, ETREL_TRUSTED_DIR, ETREL_TRUSTED_LEN) == 0) return 1;
    return 0;
}
/* Run a raw ELF image (ET_REL, ET_EXEC or ET_DYN) already read into `data`.
 * argv[0] is the program name the program sees. Returns the exit code, or -1
 * when the buffer is not a loadable ELF. The image is not registered; it is
 * relocated and executed fresh, then dropped. */
static int shell_run_elf_buf_path(const char *data, unsigned size, int argc,
                                  char **argv, const char *srcpath) {
    if (!data || size < EI_NIDENT ||
        !(data[0] == 0x7F && data[1] == 'E' && data[2] == 'L' && data[3] == 'F'))
        return -1;
    Elf64_Half etype = ((const Elf64_Ehdr *)data)->e_type;
    if (etype == ET_REL) {
        if (srcpath && !etrel_path_trusted(srcpath)) {
            kprintf("run: refusing untrusted ET_REL '%s': link to ELF with 'ld -f elf'", srcpath);
            return -1;
        }
        prog_entry_t entry;
        void *base = 0;
        int rc;
        entry = elf_load((void *)data, size, &base);
        if (!entry) return -1;
        rc = k_run_rel(entry, argc, argv);
        kfree(base);
        return rc;
    }
    if (etype == ET_EXEC || etype == ET_DYN) {
        void *entry = load_exec_elf((void *)data, size);
        if (!entry) return -1;
        return k_exec_user(entry, argc, argv);
    }
    return -1;
}

/* Load the ramdisk file at `full` and run it as an ELF. Returns the exit
 * code, or -1 when the file cannot be read or loaded. */
static int shell_run_elf_file(const char *full, int argc, char **argv) {
    RDFile *f = ramdisk_open(full);
    if (!f) return -1;
    unsigned char *data = kmalloc(f->size ? f->size : 1);
    if (!data) { kprintf("run: out of memory\n"); return -1; }
    ramdisk_read(f, data, 0, f->size);
    int ret = shell_run_elf_buf_path((const char *)data, f->size, argc, argv, full);
    kfree(data);
    return ret;
}

/* Load a Linux ELF from the MiniFS disk and run it (preserves the historical
 * `run` fallback when a name is not on the ramdisk). */
static int shell_run_elf_minifs(const char *name, int argc, char **argv) {
    if (!minifs_is_mounted()) return -1;
    char cand[RAMDISK_FNAME_LEN];
    char resolved[RAMDISK_FNAME_LEN];
    int ino = -1;
    if (fs_resolve(name, resolved, sizeof(resolved)))
        ino = minifs_resolve_path(resolved);
    if (ino < 0 && kstrchr(name, '/')) {
        ino = minifs_resolve_path(name);
        if (ino < 0) {
            const char *base = name;
            const char *p;
            for (p = name; *p; p++)
                if (*p == '/') base = p + 1;
            ino = minifs_resolve_path(base);
        }
    }
    if (ino < 0 && !kstrchr(name, '/')) {
        ino = minifs_resolve_path(name);
        if (ino < 0) {
            const ShellRunDir *pref = shell_run_dir_for(name);
            unsigned long pref_off = (unsigned long)(pref - shell_run_dirs);
            for (int i = 0; i < SHELL_RUN_DIRS; i++) {
                const ShellRunDir *d =
                    &shell_run_dirs[(pref_off + (unsigned long)i) % SHELL_RUN_DIRS];
                unsigned dl = (unsigned)kstrlen(d->dir);
                unsigned nl = (unsigned)kstrlen(name);
                if (dl + nl + 1 > sizeof(cand)) continue;
                kmemcpy(cand, d->dir, dl);
                kmemcpy(cand + dl, name, nl + 1);
                ino = minifs_resolve_path(cand);
                if (ino >= 0) break;
            }
        }
    }
    if (ino < 0) return -1;
    MiniFSInode st;
    if (minifs_stat(ino, &st) < 0 || st.size == 0) return -1;
    unsigned char *buf = (unsigned char *)kmalloc(st.size);
    if (!buf) return -1;
    minifs_read(ino, buf, 0, st.size);
    int ret = shell_run_elf_buf_path((const char *)buf, st.size, argc, argv, name);
    kfree(buf);
    return ret;
}

/* Run a `.cvm` module at the resolved path `full`. The interpreter is loaded
 * from the ramdisk on first use and cached. argv[0] is the module name the
 * module sees; the interpreter passes it and the remaining words through as
 * a Linux-style argv. */
static int shell_run_cvm(const char *full, int argc, char **argv) {
    static prog_entry_t cvm_entry = 0;
    if (!cvm_entry) {
        RDFile *rf = ramdisk_open(SHELL_CVM_INTERP);
        if (!rf) { shell_report("run: objects/cvm.o not on ramdisk", 0); return -1; }
        unsigned char *data = kmalloc(rf->size ? rf->size : 1);
        if (!data) { kprintf("run: out of memory\n"); return -1; }
        ramdisk_read(rf, data, 0, rf->size);
        void *e = elf_load(data, rf->size, 0);
        kfree(data);
        if (!e) { shell_report("run: cannot load objects/cvm.o", 0); return -1; }
        cvm_entry = (prog_entry_t)e;
    }
    char *saved0 = argv[0];
    /* The interpreter opens argv[0] via fopen -> kfopen -> fs_resolve.
     * A bare ramdisk path like "cvm/fib.cvm" would be resolved against cwd
     * again, so build an absolute path to prevent double resolution.
     * Heap buffer, not a stack local: handing a local's address to the
     * callee through argv is an escaped-stack bug (cppcheck
     * autoVariables), and malloc is recursion-safe where a static would
     * break nested cvm runs. */
    char *abspath = kmalloc(RAMDISK_FNAME_LEN);
    int ret;
    if (!abspath) return -1;
    abspath[0] = '/';
    kmemcpy(abspath + 1, full, kstrlen(full) + 1);
    argv[0] = abspath;
    ret = cvm_entry(argc, argv);
    argv[0] = saved0;
    kfree(abspath);
    return ret;
}

/* Run `name` as a ramdisk/MiniFS file: `.cvm` modules through the
 * interpreter, ELF files by content through the matching loader. Returns the
 * exit code, or -1 when the name resolves to nothing runnable. */
static int shell_run_file(const char *name, int argc, char **argv) {
    char full[RAMDISK_FNAME_LEN];
    int nl = (int)kstrlen(name);
    if (nl >= 4 && kstrcmp(name + nl - 4, ".cvm") == 0) {
        if (shell_resolve_run(name, full, sizeof(full)))
            return shell_run_cvm(full, argc, argv);
        if (minifs_is_mounted()) {
            char resolved[RAMDISK_FNAME_LEN];
            int ino = -1;
            const char *use = name;
            if (fs_resolve(name, resolved, sizeof(resolved)))
                ino = minifs_resolve_path(resolved);
            if (ino >= 0) use = resolved;
            else {
                ino = minifs_resolve_path(name);
                if (ino < 0 && kstrchr(name, '/')) {
                    const char *base = name;
                    const char *p;
                    for (p = name; *p; p++)
                        if (*p == '/') base = p + 1;
                    ino = minifs_resolve_path(base);
                    if (ino >= 0) use = base;
                }
            }
            if (ino >= 0)
                return shell_run_cvm(use, argc, argv);
        }
        return -1;
    }
    if (shell_resolve_run(name, full, sizeof(full)))
        return shell_run_elf_file(full, argc, argv);
    return shell_run_elf_minifs(name, argc, argv);
}

/* ---- Multitask run (mrun): concurrent isolated ELFs ----
 *
 * `mrun a.elf b.elf ...` loads each ET_EXEC/ET_DYN into its own user
 * window (proc_spawn_elf) and waits for all of them. The 100 Hz timer
 * preempts the BSP across the READY set, so small programs overlap in
 * time instead of running one after another. ET_REL is refused (ring-0
 * extensions are not multitask-safe); `.cvm` keeps the `run` path.
 * Best-effort limits of this revision: no mmap/VMA isolation between
 * the children (programs that mmap concurrently share the global VMA
 * tree) and one shared fd table; exit codes print per program. */
static int shell_read_elf_bytes(const char *name, unsigned char **out,
                                unsigned *out_size) {
    char full[RAMDISK_FNAME_LEN];
    RDFile *f;
    if (shell_resolve_run(name, full, sizeof(full))) {
        f = ramdisk_open(full);
        if (f) {
            unsigned char *data = kmalloc(f->size ? f->size : 1);
            if (!data) return -1;
            ramdisk_read(f, data, 0, f->size);
            *out = data;
            *out_size = f->size;
            return 0;
        }
    }
    if (minifs_is_mounted()) {
        char resolved[RAMDISK_FNAME_LEN];
        char cand[RAMDISK_FNAME_LEN];
        int ino = -1;
        if (fs_resolve(name, resolved, sizeof(resolved)))
            ino = minifs_resolve_path(resolved);
        if (ino < 0) ino = minifs_resolve_path(name);
        if (ino < 0) {
            const char *base = name;
            const char *p;
            for (p = name; *p; p++)
                if (*p == '/') base = p + 1;
            ino = minifs_resolve_path(base);
        }
        if (ino < 0 && !kstrchr(name, '/')) {
            ino = minifs_resolve_path(name);
            if (ino < 0) {
                const ShellRunDir *pref = shell_run_dir_for(name);
                unsigned long pref_off = (unsigned long)(pref - shell_run_dirs);
                for (int i = 0; i < SHELL_RUN_DIRS; i++) {
                    const ShellRunDir *d =
                        &shell_run_dirs[(pref_off + (unsigned long)i) % SHELL_RUN_DIRS];
                    unsigned dl = (unsigned)kstrlen(d->dir);
                    unsigned nl = (unsigned)kstrlen(name);
                    if (dl + nl + 1 > sizeof(cand)) continue;
                    kmemcpy(cand, d->dir, dl);
                    kmemcpy(cand + dl, name, nl + 1);
                    ino = minifs_resolve_path(cand);
                    if (ino >= 0) break;
                }
            }
        }
        if (ino >= 0) {
            MiniFSInode st;
            unsigned char *buf;
            if (minifs_stat(ino, &st) < 0 || st.size == 0) return -1;
            buf = (unsigned char *)kmalloc(st.size);
            if (!buf) return -1;
            minifs_read(ino, buf, 0, st.size);
            *out = buf;
            *out_size = st.size;
            return 0;
        }
    }
    return -1;
}

/* Foreground wait over spawned jobs with Ctrl+C: polls for each pid's
 * exit, yields the CPU between polls (voluntary switches; the 100 Hz
 * timer preempts involuntarily per OSDev's preemptive model), and on
 * Ctrl+C kills the whole foreground set like SIGINT, then reaps. Returns
 * the last exit code (130 when interrupted). */
static int shell_wait_fg(int *pids, int n, int kill_on_int) {
    int ndone = 0, last = 0;
    int done[8] = {0,0,0,0,0,0,0,0};
    int i;
    if (n > 8) n = 8;
    shell_fg_active = 1;
    for (;;) {
        int alive = 0;
        for (i = 0; i < n; i++) {
            int code;
            if (done[i]) continue;
            if (shell_reap_one(pids[i], &code)) {
                done[i] = 1;
                ndone++;
                last = code;
                kprintf("mrun: pid %d exit code: %d\n", pids[i], code);
                continue;
            }
            /* A pid the shell no longer owns (reaped elsewhere, slot
             * reused by a stranger) can never report: stop tracking
             * it instead of yield-looping past the end of the job. */
            {
                int k, me = current_pid, owned = 0;
                spin_lock(&sched_lock);
                for (k = 0; k < MAX_PROCS; k++)
                    if (procs[k].state != PROC_FREE
                        && procs[k].parent_pid == me
                        && procs[k].pid == pids[i]) { owned = 1; break; }
                spin_unlock(&sched_lock);
                if (owned) alive = 1;
                else { done[i] = 1; ndone++; }
            }
        }
        if (ndone >= n) { shell_fg_active = 0; return last; }
        if (!alive) { shell_fg_active = 0; return last; }
        if (console_peek() == 0x03) {
            console_getc();
            kprintf("^C\n");
            if (kill_on_int) {
                for (i = 0; i < n; i++)
                    if (!done[i]) do_kill(pids[i]);
                last = 130;
            } else {
                shell_fg_active = 0;
                return 130;
            }
            continue;
        }
        yield();
    }
}

static void shell_cmd_mrun(int argc, char **argv) {
    int pids[8];
    int npids = 0;
    int i;
    int bg = 0;
    if (argc > 1 && kstrcmp(argv[argc - 1], "&") == 0) { bg = 1; argc--; }
    if (argc < 2) { vga_puts("usage: mrun <a.elf> [b.elf ...] [&]\n"); return; }
    if (argc - 1 > 8) { vga_puts("mrun: at most 8 programs\n"); return; }
    for (i = 1; i < argc; i++) {
        unsigned char *data = 0;
        unsigned size = 0;
        int pid;
        char *pargv[1];
        if (shell_read_elf_bytes(argv[i], &data, &size)) {
            kprintf("mrun: %s: not found\n", argv[i]);
            continue;
        }
        if (size < 4 || !(data[0] == 0x7F && data[1] == 'E' &&
                          data[2] == 'L' && data[3] == 'F')) {
            kprintf("mrun: %s: not an ELF\n", argv[i]);
            kfree(data);
            continue;
        }
        if (((const Elf64_Ehdr *)data)->e_type == ET_REL) {
            kprintf("mrun: %s: ET_REL refused (use run)\n", argv[i]);
            kfree(data);
            continue;
        }
        pargv[0] = argv[i];
        pid = proc_spawn_elf(argv[i], data, size, 1, pargv);
        kfree(data);
        if (pid < 0) {
            kprintf("mrun: %s: spawn failed\n", argv[i]);
            continue;
        }
        kprintf("mrun: %s started as pid %d\n", argv[i], pid);
        pids[npids++] = pid;
    }
    if (bg) {
        if (npids) kprintf("mrun: %d job(s) in background\n", npids);
        return;
    }
    if (npids) shell_wait_fg(pids, npids, 1);
}

/* `run <elf> &`: background a single isolated ELF (same spawn path as
 * mrun). ET_REL and .cvm stay foreground-only: ring-0 extensions and the
 * single cached interpreter cannot run detached. */
static void shell_run_bg(const char *name, int argc, char **argv) {
    unsigned char *data = 0;
    unsigned size = 0;
    int pid;
    if (shell_read_elf_bytes(name, &data, &size)) {
        kprintf("run: %s: not found\n", name);
        return;
    }
    if (size < 4 || !(data[0] == 0x7F && data[1] == 'E' &&
                      data[2] == 'L' && data[3] == 'F')) {
        kprintf("run: %s: not an ELF (cvm/o run in foreground)\n", name);
        kfree(data);
        return;
    }
    if (((const Elf64_Ehdr *)data)->e_type == ET_REL) {
        kprintf("run: %s: ET_REL runs in foreground\n", name);
        kfree(data);
        return;
    }
    pid = proc_spawn_elf(name, data, size, argc, argv);
    kfree(data);
    if (pid < 0) { kprintf("run: %s: spawn failed\n", name); return; }
    kprintf("run: %s started as job pid %d\n", name, pid);
}

/* `desktop`: one-command Wayland session (ADR-0026 live step).
 *
 * `desktop` writes the mirror+client flags under /shm/wl and spawns
 * `wlcomp --server` as a background job, turning a plain `make run`
 * boot into the tiled Wayland desktop: every NK app started after
 * this (paint, vedit, file, nuklear, doomedit, piano) runs as a
 * Wayland client (pixels to its pid-unique mailbox, input from its
 * .ev file) instead of stealing the display, so windows tile with
 * title bars, focus, close, resize and minimize under real
 * preemptive multitasking (`jobs` lists clients beside the server).
 * `desktop stop` asks the server out through the quit flag (a
 * background job owns no console to hear keys on); `desktop status`
 * reports flags plus the server pid state. Server shortcuts are
 * Alt-held (Alt+T/M/U/Q) so plain keys always reach the focused
 * client. A live client re-attaches after a title-X close, so
 * closing one also wants `kill <pid>` (the box name carries it). */
static int desktop_srv_pid = -1;

static void desktop_path(const char *name, char *dst, unsigned cap) {
    const char *base = "/shm/wl/";
    unsigned bi = 0;
    unsigned ni = 0;
    while (base[bi] && bi + 1 < cap) { dst[bi] = base[bi]; bi++; }
    while (name[ni] && bi + 1 < cap) { dst[bi++] = name[ni++]; }
    dst[bi] = 0;
}

static void desktop_flag(const char *name) {
    char path[RAMDISK_FNAME_LEN];
    KFILE *f;
    desktop_path(name, path, sizeof(path));
    f = kfopen(path, "w");
    if (!f) { kprintf("desktop: cannot write %s\n", path); return; }
    kfwrite("1", 1, 1, f);
    kfclose(f);
}

static int desktop_flag_on(const char *name) {
    char path[RAMDISK_FNAME_LEN];
    KFILE *f;
    desktop_path(name, path, sizeof(path));
    f = kfopen(path, "r");
    if (!f) return 0;
    kfclose(f);
    return 1;
}

/* A reboot with a stale client flag would blind every NK app (client
 * mode with no server mirrors into the void and never presents), so
 * the shell clears session flags once at startup and `desktop stop`
 * clears them on exit. Mirror stays: it is harmless without a server
 * and external flows (make wl) set it themselves. */
static void desktop_unflag(const char *name) {
    char path[RAMDISK_FNAME_LEN];
    desktop_path(name, path, sizeof(path));
    if (minifs_is_mounted())
        minifs_unlink(path);
}

static int desktop_srv_alive(void) {
    int alive = 0;
    int i;
    if (desktop_srv_pid <= 0) return 0;
    spin_lock(&sched_lock);
    for (i = 0; i < MAX_PROCS; i++) {
        if (procs[i].pid == desktop_srv_pid
            && procs[i].state != PROC_FREE
            && procs[i].state != PROC_ZOMBIE
            && kstrncmp(procs[i].name, "wlcomp", 6) == 0)
            alive = 1;
    }
    spin_unlock(&sched_lock);
    return alive;
}

static void shell_cmd_desktop(int argc, char **argv) {
    if (argc > 1 && kstrcmp(argv[1], "stop") == 0) {
        desktop_flag("quit");
        desktop_unflag("client");
        desktop_unflag("mirror");
        desktop_srv_pid = -1;
        /* The quit flag only works when the server still polls. A
         * server that already faulted leaves gfx mode plus raw kbd
         * behind with nobody to consume the flag, which used to wedge
         * the shell with no keyboard. Restore text mode here too:
         * idempotent when the server exits cleanly and restores it
         * itself. */
        kbd_raw_mode_set(0);
        vga_fb_set_gfx_mode(0);
        vga_fb_draw_desktop();
        vga_puts("desktop: stopping (server exits, text mode returns)\n");
        return;
    }
    if (argc > 1 && kstrcmp(argv[1], "status") == 0) {
        kprintf("desktop: mirror=%d client=%d server=%s\n",
            desktop_flag_on("mirror"), desktop_flag_on("client"),
            desktop_srv_alive() ? "running" : "stopped");
        return;
    }
    if (argc > 1) { vga_puts("usage: desktop [stop|status]\n"); return; }
    if (desktop_srv_alive()) {
        kprintf("desktop: server already running as pid %d\n",
            desktop_srv_pid);
        return;
    }
    desktop_flag("mirror");
    desktop_flag("client");
    {
        unsigned char *data = 0;
        unsigned size = 0;
        char *pargv[2];
        int pid;
        if (shell_read_elf_bytes("wlcomp", &data, &size)) {
            vga_puts("desktop: wlcomp: not found\n");
            return;
        }
        if (size < 4 || !(data[0] == 0x7F && data[1] == 'E'
                && data[2] == 'L' && data[3] == 'F')) {
            vga_puts("desktop: wlcomp: not an ELF\n");
            kfree(data);
            return;
        }
        pargv[0] = "wlcomp";
        pargv[1] = "--server";
        pid = proc_spawn_elf("wlcomp", data, size, 2, pargv);
        kfree(data);
        if (pid < 0) { vga_puts("desktop: spawn failed\n"); return; }
        desktop_srv_pid = pid;
        kprintf("desktop: wayland up (server pid %d)\n", pid);
        vga_puts("desktop: click focuses, drag moves, rim resizes, X closes\n");
        vga_puts("desktop: Alt+T tile Alt+M minimize Alt+U restore Alt+Q quit\n");
        vga_puts("desktop: Alt+Tab cycles focus, ESC quits on an empty desktop\n");
        vga_puts("desktop: start apps as clients (mrun paint &), jobs lists them\n");
    }
}

/* Unified dispatcher used by `run` and by bare commands: a registered program
 * wins, then the runnable-file resolver. argv[0] is the command/program name
 * as typed. Returns the exit code, or -1 when the name cannot be run. */
int shell_run_any(const char *name, int argc, char **argv) {
    int nl = (int)kstrlen(name);
    /* Record the launch name for the taskbar button: if this program goes
     * graphics, the button resolves its icon through etc/shortcuts. */
    vga_fb_set_gfx_program(name);
    if (nl >= 4 && kstrcmp(name + nl - 4, ".cvm") == 0)
        return shell_run_file(name, argc, argv);
    KProg *p = kprog_lookup(name);
    if (p) {
        if (p->is_proc) return k_exec_user(p->proc_entry, argc, argv);
        return k_run_rel(p->entry, argc, argv);
    }
    return shell_run_file(name, argc, argv);
}

/* ---- Desktop shortcut launch ----
 * Called by the desktop click handler (vga_fb.c) when an icon is clicked.
 * Splits the command line into argv and routes through shell_exec_builtin,
 * which handles builtins (run, cat, ls, ...) and falls through to
 * shell_run_any for registered programs and files.  The ~shell command name
 * is special: it activates the terminal. */
void desktop_launch(const char *cmd) {
    if (!cmd || !*cmd) return;
    if (user_program_active) {
        /* The tick runs from the ISR while a program owns the CPU; defer the
         * launch until the program exits instead of re-entering k_exec_user
         * from ISR context (which corrupts the running program's state). */
        shell_queue_launch(cmd);
        return;
    }
    if (cmd[0] == '~' && kstrcmp(cmd, "~shell") == 0) {
        /* ~shell: bring the terminal to focus (already visible). */
        return;
    }
    /* Icons are not relative to the shell: a dock launch runs with the
     * cwd pinned to the root and restores the shell cwd afterwards, so
     * `+set basedir .` (Quake 2) or any other relative path in a
     * shortcut resolves against / no matter where the shell sits. */
    char saved_cwd[RAMDISK_FNAME_LEN];
    kmemcpy(saved_cwd, fs_cwd, sizeof(saved_cwd));
    fs_cwd[0] = 0;
    /* Parse command into argv (space-separated, max 8 args).  Each arg is
     * copied sequentially into buf so argv pointers stay valid for the call. */
    char buf[128];
    char *argv[8];
    int argc = 0;
    int pos = 0;
    const char *p = cmd;
    while (*p && argc < 8) {
        while (*p == ' ') p++;
        if (!*p) break;
        argv[argc] = buf + pos;
        while (*p && *p != ' ' && pos < (int)sizeof(buf) - 1) {
            buf[pos++] = *p++;
        }
        buf[pos++] = '\0';
        argc++;
    }
    if (argc > 0) shell_exec_builtin(argc, argv);
    kmemcpy(fs_cwd, saved_cwd, sizeof(saved_cwd));
}

/* ---- Graphics debugging (`gfx` builtin) ----
 *
 * The serial console is the observability surface the BDD suite drives, but a
 * framebuffer program's output never reaches it. `gfx` lifts the graphics
 * side onto the console: state, single-pixel sampling, region statistics and
 * a PPM screenshot are all reported as text, so the desktop and the windowed
 * graphics programs are testable from the shell exactly like `date`/`vol`
 * are. Every coordinate is clamped to the framebuffer and every parse is
 * strict, so a malformed invocation is a usage diagnostic, never a crash. */
static int gfx_parse_int(const char *s, int *out) {
    long v = 0;
    int sign = 1;
    if (!s || !*s) return 0;
    if (*s == '-') { sign = -1; s++; }
    else if (*s == '+') s++;
    if (!*s) return 0;
    for (; *s; s++) {
        int d = *s - '0';
        if (d < 0 || d > 9) return 0;
        v = v * 10 + d;
        if (v > 0x7FFFFFFFL) return 0;
    }
    *out = (int)(sign * v);
    return 1;
}

/* Read the current 256-entry VGA DAC palette (3x6-bit per entry, read at 8-bit
 * precision by the kernel's normalisation). Used by `gfx shot` to turn the
 * indexed framebuffer into an RGB PPM. */
static void gfx_read_palette(unsigned char pal[768]) {
    int i;
    outb(0x3C7, 0);            /* DAC read mode, start at index 0 */
    for (i = 0; i < 768; i++)
        pal[i] = inb(0x3C9);
}

static void shell_cmd_gfx(int argc, char **argv) {
    if (argc == 1) {
        kprintf("gfx: fb %dx%d pitch %d base %lx mode %s active %d\n",
                fb_width, fb_height, fb_pitch, fb_phys_base,
                vga_mode_is_active() ? "gfx" : "text", vga_fb_active);
        kprintf("gfx: mouse present %d at (%d,%d) buttons %d wheel %d\n",
                mouse_state.present, mouse_state.x, mouse_state.y,
                mouse_state.buttons, mouse_state.wheel);
        kprintf("gfx: term (%d,%d) %dx%d cells  minimized %d  fullscreen %d\n",
                term_x, term_y, term_cols, term_rows,
                vga_fb_is_minimized(), vga_fb_is_fullscreen());
        return;
    }
    if (kstrcmp(argv[1], "pixel") == 0) {
        int x, y;
        if (argc < 4 || !gfx_parse_int(argv[2], &x) || !gfx_parse_int(argv[3], &y)) {
            vga_puts("usage: gfx pixel <x> <y>\n");
            return;
        }
        if (x < 0 || x >= fb_width || y < 0 || y >= fb_height) {
            kprintf("gfx: pixel (%d,%d) out of range (%dx%d)\n",
                    x, y, fb_width, fb_height);
            return;
        }
        if (fb_bpp == 8) {
            kprintf("gfx: pixel (%d,%d) = %d\n", x, y,
                    FB_ADDR[(unsigned)y * (unsigned)fb_pitch + (unsigned)x]);
        } else {
            unsigned long rgb = vga_fb_read_rgb(x, y);
            kprintf("gfx: pixel (%d,%d) = #%06lx\n", x, y, rgb & 0xFFFFFFUL);
        }
        return;
    }
    if (kstrcmp(argv[1], "rect") == 0) {
        int x0, y0, x1, y1, i, x, y;
        if (argc < 6 || !gfx_parse_int(argv[2], &x0) || !gfx_parse_int(argv[3], &y0) ||
            !gfx_parse_int(argv[4], &x1) || !gfx_parse_int(argv[5], &y1)) {
            vga_puts("usage: gfx rect <x0> <y0> <x1> <y1>\n");
            return;
        }
        if (x0 < 0) x0 = 0;
        if (x1 >= fb_width) x1 = fb_width - 1;
        if (y0 < 0) y0 = 0;
        if (y1 >= fb_height) y1 = fb_height - 1;
        if (x1 < x0 || y1 < y0) {
            vga_puts("gfx: rect inverted or empty\n");
            return;
        }
        if (fb_bpp != 8) {
            /* True color: per-channel ranges instead of a DAC-index
             * histogram, which no longer exists. */
            unsigned rmin = 255, rmax = 0, gmin = 255, gmax = 0;
            unsigned bmin = 255, bmax = 0;
            unsigned long total = 0;
            for (y = y0; y <= y1; y++)
                for (x = x0; x <= x1; x++) {
                    unsigned long rgb = vga_fb_read_rgb(x, y);
                    unsigned r = (unsigned)((rgb >> 16) & 0xFF);
                    unsigned g = (unsigned)((rgb >> 8) & 0xFF);
                    unsigned b = (unsigned)(rgb & 0xFF);
                    if (r < rmin) rmin = r;
                    if (r > rmax) rmax = r;
                    if (g < gmin) gmin = g;
                    if (g > gmax) gmax = g;
                    if (b < bmin) bmin = b;
                    if (b > bmax) bmax = b;
                    total++;
                }
            kprintf("gfx: rect (%d,%d)-(%d,%d): %lu px r[%u..%u] g[%u..%u] b[%u..%u]\n",
                    x0, y0, x1, y1, total, rmin, rmax, gmin, gmax, bmin, bmax);
            return;
        }
        {
            unsigned hist[256];
            int min = 255, max = 0, distinct = 0, top = 0, top_n = 0;
            unsigned long total = 0;
            kmemset(hist, 0, sizeof(hist));
            for (y = y0; y <= y1; y++)
                for (x = x0; x <= x1; x++)
                    hist[FB_ADDR[(unsigned)y * (unsigned)fb_pitch + (unsigned)x]]++;
            for (i = 0; i < 256; i++) {
                if (hist[i]) {
                    distinct++;
                    if (i < min) min = i;
                    if (i > max) max = i;
                    if ((int)hist[i] > top_n) { top_n = (int)hist[i]; top = i; }
                    total += hist[i];
                }
            }
            kprintf("gfx: rect (%d,%d)-(%d,%d): %lu px distinct %d range [%d..%d] top %d x%lu\n",
                    x0, y0, x1, y1, total, distinct, min, max, top,
                    (unsigned long)top_n);
        }
        return;
    }
    if (kstrcmp(argv[1], "shot") == 0) {
        const char *path;
        KFILE *f;
        unsigned char pal[768];
        unsigned long written = 0;
        char hdr[64];
        int i, y, n;
        if (argc < 3) { vga_puts("usage: gfx shot <file>\n"); return; }
        path = argv[2];
        f = kfopen(path, "w");
        if (!f) { kprintf("gfx: shot: cannot open %s\n", path); return; }
        gfx_read_palette(pal);
        n = ksprintf(hdr, "P6\n%d %d\n255\n", fb_width, fb_height);
        written += (unsigned long)n;
        kfwrite(hdr, 1, (unsigned long)n, f);
        for (y = 0; y < fb_height; y++) {
            for (i = 0; i < fb_width; i++) {
                unsigned char rgb[3];
                if (fb_bpp == 8) {
                    unsigned idx = FB_ADDR[(unsigned)y * (unsigned)fb_pitch + (unsigned)i];
                    rgb[0] = pal[idx * 3 + 0];
                    rgb[1] = pal[idx * 3 + 1];
                    rgb[2] = pal[idx * 3 + 2];
                } else {
                    unsigned long px = vga_fb_read_rgb(i, y);
                    rgb[0] = (unsigned char)((px >> 16) & 0xFF);
                    rgb[1] = (unsigned char)((px >> 8) & 0xFF);
                    rgb[2] = (unsigned char)(px & 0xFF);
                }
                kfwrite(rgb, 1, 3, f);
                written += 3;
            }
        }
        kfclose(f);
        kprintf("gfx: shot %s (%lu bytes)\n", path, written);
        return;
    }
    if (kstrcmp(argv[1], "frames") == 0) {
        kprintf("gfx: frames composited %lu\n", gfx_frames_composited);
        return;
    }
    if (kstrcmp(argv[1], "palette") == 0) {
        unsigned char pal[768];
        int i;
        gfx_read_palette(pal);
        for (i = 0; i < 15; i++)
            kprintf("  %2d: %3d %3d %3d\n", i, pal[i * 3], pal[i * 3 + 1], pal[i * 3 + 2]);
        return;
    }
    vga_puts("usage: gfx [pixel <x> <y> | rect <x0> <y0> <x1> <y1> | shot <file> | frames | palette]\n");
}

/* `wm <op>` — window-manager operations, exposed as a shell builtin so the
 * tiling-WM behaviour is observable and testable over the serial console
 * exactly like `date`/`vol`. The operations are the same functions the
 * title-bar buttons, the Alt/Super shortcuts and the mouse tick call, so
 * the framebuffer and the shell can never disagree. */
static void shell_cmd_wm(int argc, char **argv) {
    if (argc > 1) {
        if (kstrcmp(argv[1], "minimize") == 0) { vga_fb_toggle_minimize(); return; }
        if (kstrcmp(argv[1], "maximize") == 0) { vga_fb_toggle_fullscreen(); return; }
        if (kstrcmp(argv[1], "close") == 0) {
            if (!vga_fb_term_close_focused()) vga_fb_close_active();
            return;
        }
        if (kstrcmp(argv[1], "split") == 0) {
            if (vga_fb_term_split())
                kprintf("wm: split failed (out of memory)\n");
            else
                kprintf("wm: split: term2 on, focus %d\n", vga_fb_focus_get());
            return;
        }
        if (kstrcmp(argv[1], "list") == 0) { vga_fb_list_windows(); return; }
        if (kstrcmp(argv[1], "tile") == 0) {
            vga_fb_tile_all();
            kprintf("wm: tiled %d terms\n", vga_fb_nterms_get());
            return;
        }
        if (kstrcmp(argv[1], "layout") == 0) {
            int m = -1;
            if (argc < 3) {
                kprintf("wm: layout %s\n", vga_fb_layout_name());
                return;
            }
            if (kstrcmp(argv[2], "tile") == 0) m = WM_LAYOUT_TILE;
            else if (kstrcmp(argv[2], "bsp") == 0) m = WM_LAYOUT_BSP;
            else if (kstrcmp(argv[2], "cascade") == 0) m = WM_LAYOUT_CASCADE;
            else if (kstrcmp(argv[2], "fibonacci") == 0) m = WM_LAYOUT_FIBONACCI;
            else if (kstrcmp(argv[2], "cycle") == 0) {
                vga_fb_layout_cycle();
                kprintf("wm: layout %s\n", vga_fb_layout_name());
                return;
            } else {
                vga_puts("usage: wm layout [tile|bsp|cascade|fibonacci|cycle]\n");
                return;
            }
            if (vga_fb_layout_set(m)) {
                vga_puts("wm: layout failed\n");
                return;
            }
            vga_fb_tile_all();
            kprintf("wm: layout %s\n", vga_fb_layout_name());
            return;
        }
        if (kstrcmp(argv[1], "snap") == 0) {
            int z = -1;
            if (argc < 3) { vga_puts("usage: wm snap left|right|top|bottom|tl|tr|bl|br\n"); return; }
            if (kstrcmp(argv[2], "left") == 0) z = TILING_LEFT;
            else if (kstrcmp(argv[2], "right") == 0) z = TILING_RIGHT;
            else if (kstrcmp(argv[2], "top") == 0) z = TILING_TOP;
            else if (kstrcmp(argv[2], "bottom") == 0) z = TILING_BOTTOM;
            else if (kstrcmp(argv[2], "tl") == 0) z = TILING_TOP_LEFT;
            else if (kstrcmp(argv[2], "tr") == 0) z = TILING_TOP_RIGHT;
            else if (kstrcmp(argv[2], "bl") == 0) z = TILING_BOTTOM_LEFT;
            else if (kstrcmp(argv[2], "br") == 0) z = TILING_BOTTOM_RIGHT;
            else { vga_puts("usage: wm snap left|right|top|bottom|tl|tr|bl|br\n"); return; }
            vga_fb_snap_window(z);
            kprintf("wm: snapped focus %d\n", vga_fb_focus_get());
            return;
        }
        if (kstrcmp(argv[1], "focus") == 0) {
            if (argc > 2) {
                if (kstrcmp(argv[2], "next") == 0) vga_fb_focus_next();
                else if (argv[2][0] >= '0' && argv[2][0] <= '2' && !argv[2][1]) {
                    int before = vga_fb_focus_get();
                    if (vga_fb_focus_id(argv[2][0] - '0'))
                        kprintf("wm: no such window\n");
                    else
                        vga_fb_focus_report(before, WM_FOCUS_SRC_PROGRAM);
                } else {
                    vga_puts("usage: wm focus [next|0|1|2]\n");
                    return;
                }
            } else {
                vga_fb_focus_next();
            }
            /* fall through to report */
        }
        if (kstrcmp(argv[1], "state") == 0) { /* fall through to report */ }
        else if (kstrcmp(argv[1], "focus") != 0) {
            vga_puts("usage: wm [minimize|maximize|close|split|list|tile|layout|focus|state]\n");
            return;
        }
    }
    kprintf("wm: minimized %d fullscreen %d gfx-mode %d focus %d nterms %d\n",
            vga_fb_is_minimized(), vga_fb_is_fullscreen(),
            wm_gfx_mode_active(), vga_fb_focus_get(),
            vga_fb_nterms_get());
    kprintf("wm: fx %s\n", vga_fx_enabled() ? "on" : "off");
    kprintf("wm: layout %s\n", vga_fb_layout_name());
    {
        unsigned long kicks = 0;
        unsigned long paints = 0;
        unsigned long edges = 0;
        dock_bounce_counts(&kicks, &paints);
        dock_click_count(&edges);
        kprintf("wm: bounce kicks=%lu paints=%lu edges=%lu pending=%d\n",
                kicks, paints, edges, dock_pending_active());
    }
    {
        char theme[17];
        vga_fb_theme_name(theme, sizeof(theme));
        kprintf("wm: theme %s\n", theme);
    }
    {
        unsigned long cooked = 0;
        unsigned long raw = 0;
        kbd_drop_counts(&cooked, &raw);
        kprintf("wm: kbd drops cooked=%lu raw=%lu\n", cooked, raw);
    }
    {
        const wm_notify_event_t *fe = vga_fb_focus_event();
        if (fe)
            kprintf("wm: focus-event %d->%d %s\n", fe->old_focus,
                    fe->new_focus, wm_notify_src_name(fe->source));
        else
            kprintf("wm: focus-event none\n");
    }
}

/* Job control (`jobs`/`wait`/`kill` + trailing `&`): real preemptive
 * parallelism for ring-3 ELFs. `run p.elf &` / `mrun a b &` spawn isolated
 * processes (own CR3 via proc_spawn_elf) and return the prompt at once;
 * the 100 Hz timer preempts shell and jobs against each other while voluntary
 * yield()s in the wait loops keep most switches cooperative (OSDev's
 * preemptive model: involuntary preemption is the backstop, not the norm).
 * Exits surface three ways: the fg wait prints them, `wait` reaps on demand,
 * and the prompt auto-reaps leftovers as `job done`, so pid slots never
 * leak. Ctrl+C kills the foreground set (SIGKILL semantics; rt_sigaction
 * handlers stay a stub, so no guest handler runs). Limits: background is
 * ET_EXEC/DYN only (ET_REL/.cvm refuse `&`), one shared fd table and VMA
 * tree (mmap-heavy jobs stay best-effort), legacy blocking `run` ignores
 * Ctrl+C (it never polls the console). */
static const char *shell_proc_state(int st) {
    switch (st) {
    case PROC_READY: return "ready";
    case PROC_RUNNING: return "run";
    case PROC_BLOCKED: return "wait";
    case PROC_ZOMBIE: return "done";
    case PROC_SWITCHING: return "spawn";
    default: return "?";
    }
}

static void shell_cmd_jobs(void) {
    struct job_row { int pid; int state; char name[32]; };
    struct job_row snap[MAX_PROCS];
    int i, n = 0;
    spin_lock(&sched_lock);
    for (i = 0; i < MAX_PROCS && n < MAX_PROCS; i++) {
        int k;
        if (procs[i].state == PROC_FREE || procs[i].parent_pid != 0)
            continue;
        snap[n].pid = procs[i].pid;
        snap[n].state = procs[i].state;
        for (k = 0; k < 31 && procs[i].name[k]; k++)
            snap[n].name[k] = procs[i].name[k];
        snap[n].name[k] = 0;
        n++;
    }
    spin_unlock(&sched_lock);
    for (i = 0; i < n; i++)
        kprintf("job pid %d %s %s\n", snap[i].pid,
                shell_proc_state(snap[i].state), snap[i].name);
    if (!n) kprintf("jobs: none\n");
}

/* Live-child check for one pid: a slot that is neither FREE nor
 * reparented still belongs to this shell. Waiting on anything else
 * (an already reaped job, a stranger's pid) must fail fast: the old
 * code fell into shell_wait_fg for a pid that can never exit again
 * and yield-looped forever with the console wedged (only Ctrl+C
 * escaped), which read exactly like a dead machine. */
static int shell_has_child(int pid) {
    int i, found = 0, me = current_pid;
    spin_lock(&sched_lock);
    for (i = 0; i < MAX_PROCS; i++)
        if (procs[i].state != PROC_FREE && procs[i].parent_pid == me
            && procs[i].pid == pid) { found = 1; break; }
    spin_unlock(&sched_lock);
    return found;
}

static void shell_cmd_wait(int argc, char **argv) {
    if (argc > 1) {
        int pid;
        int one[1];
        int code;
        if (!shell_parse_pid(argv[1], 1, &pid)) {
            vga_puts("usage: wait [pid]\n");
            return;
        }
        one[0] = pid;
        if (!shell_reap_one(pid, &code)) {
            if (!shell_has_child(pid)) {
                kprintf("wait: %d: no such job\n", pid);
                return;
            }
            shell_wait_fg(one, 1, 0);
        }
        return;
    }
    for (;;) {
        int rp, rc;
        shell_fg_active = 1;
        while (shell_reap_nb(&rp, &rc))
            kprintf("mrun: pid %d exit code: %d\n", rp, rc);
        if (!shell_nchildren()) { shell_fg_active = 0; return; }
        if (console_peek() == 0x03) {
            console_getc();
            kprintf("^C\n");
            shell_fg_active = 0;
            return;
        }
        yield();
    }
}

static void shell_cmd_kill(int argc, char **argv) {
    int pid, i, mine = 0;
    if (argc < 2) { vga_puts("usage: kill <pid>\n"); return; }
    if (!shell_parse_pid(argv[1], 1, &pid)) {
        vga_puts("usage: kill <pid>\n");
        return;
    }
    spin_lock(&sched_lock);
    for (i = 0; i < MAX_PROCS; i++)
        if (procs[i].state != PROC_FREE && procs[i].pid == pid &&
            procs[i].parent_pid == 0)
            mine = 1;
    spin_unlock(&sched_lock);
    if (!mine) { kprintf("kill: %d: no such job\n", pid); return; }
    if (do_kill(pid)) kprintf("kill: %d: failed\n", pid);
    else kprintf("kill: pid %d terminated\n", pid);
}

/* `mem` — memory and disk pressure in one screenful: kernel heap use
 * (dlmalloc), ramdisk use versus its cap, MiniFS free blocks/inodes and
 * live processes. The demo-scale failure mode is a silent exhaustion
 * (a big Zone alloc or a ramdisk write fails closed far from its cause),
 * so this is the first thing to read when a load stops loading. */
static void shell_cmd_mem(void) {
    unsigned long hu = 0, hf = 0, ha = 0;
    unsigned ru = 0, rc = 0, rm = 0;
    int i, nlive = 0;
    dlmalloc_usage(&hu, &hf, &ha);
    kprintf("mem: heap used=%luK free=%luK arena=%luK\n",
            hu / 1024, hf / 1024, ha / 1024);
    ramdisk_usage(&ru, &rc, &rm);
    kprintf("mem: ramdisk used=%luK cap=%luK max=%luK files=%d\n",
            ru / 1024, rc / 1024, rm / 1024, ramdisk_count());
    if (minifs_is_mounted()) {
        unsigned int fb = 0, tb = 0, fi = 0, ti = 0;
        minifs_usage(&fb, &tb, &fi, &ti);
        kprintf("mem: minifs free=%u/%u blocks free=%u/%u inodes\n",
                fb, tb, fi, ti);
    } else {
        vga_puts("mem: minifs not mounted\n");
    }
    spin_lock(&sched_lock);
    for (i = 0; i < MAX_PROCS; i++)
        if (procs[i].state != PROC_FREE) nlive++;
    spin_unlock(&sched_lock);
    kprintf("mem: procs live=%d/%d\n", nlive, MAX_PROCS);
}

/* `vmmap [pid]` -- virtual-memory map of one process. In this single-
 * address-space kernel every process shares the window layout from
 * progs/minios_abi.h; what differs per process is the brk/mmap view (the
 * globals for pid 0 / the running view, the saved per-proc view otherwise)
 * plus the live VMA (mmap) tree. The walk is bounded (64-deep explicit
 * stack, 128 regions printed) and snapshot under sched_lock + mm_lock, so
 * a hostile VMA shape can truncate the listing but never overflow it. */
static void shell_cmd_vmmap(int argc, char **argv) {
    int pid = 0, i;
    unsigned long brk = 0, brk_lim = 0, mcur = 0;
    vma_node_t *live = VMA_NIL;
    char pname[32];
    int found = 0;
    if (argc > 1) {
        if (!shell_parse_pid(argv[1], 0, &pid)) {
            kprintf("vmmap: pid %s out of range 0..%d\n", argv[1], MAX_PROCS - 1);
            return;
        }
    }
    spin_lock(&sched_lock);
    if (procs[pid].state == PROC_FREE) {
        spin_unlock(&sched_lock);
        kprintf("vmmap: pid %d: no such process (see ps)\n", pid);
        return;
    }
    found = 1;
    for (i = 0; i < 31 && procs[pid].name[i]; i++) pname[i] = procs[pid].name[i];
    pname[i] = 0;
    if (pid == current_pid || pid == 0) {
        brk = g_brk; brk_lim = g_brk_limit; mcur = user_mmap_cur;
        live = vma_live_root;
    } else if (procs[pid].vma) {
        brk = procs[pid].brk; brk_lim = procs[pid].brk_limit;
        mcur = procs[pid].mmap_cur;
        live = procs[pid].vma->live;
    }
    spin_unlock(&sched_lock);
    if (!found) return;
    kprintf("vmmap: pid=%d (%s) window 0x%lx..0x%lx\n", pid, pname,
            (unsigned long)USER_LOAD_BASE, (unsigned long)USER_LOAD_END);
    kprintf("  text 0x%lx..0x%lx  brk 0x%lx cap 0x%lx  mmap 0x%lx..0x%lx\n",
            (unsigned long)USER_LOAD_BASE, brk, brk, brk_lim,
            mcur, (unsigned long)USER_BRK_END);
    kprintf("  game 0x%lx  fb 0x%lx  nk 0x%lx  rgb 0x%lx  stack 0x%lx..0x%lx\n",
            (unsigned long)DOOM_BACKBUF_ADDR, (unsigned long)FB_ADDR,
            (unsigned long)NK_BACKBUF_ADDR, (unsigned long)NK_RGB_ADDR,
            (unsigned long)USER_STACK_BASE, (unsigned long)USER_STACK_TOP);
    {
        vma_node_t *stack[64];
        int sp = 0, shown = 0;
        vma_node_t *x = live;
        kprintf("  vma-live:");
        if (x == VMA_NIL) {
            kprintf(" (empty)\n");
        } else {
            kprintf("\n");
            while ((x != VMA_NIL || sp > 0) && shown < 128) {
                while (x != VMA_NIL) {
                    if (sp < 64) stack[sp++] = x; else break;
                    x = x->left;
                }
                if (sp <= 0) break;
                x = stack[--sp];
                kprintf("    0x%lx len 0x%lx (%luK)\n",
                        x->base, x->len, x->len / 1024);
                shown++;
                x = x->right;
            }
            if (shown >= 128) kprintf("    ... truncated at 128 regions\n");
        }
    }
}

/* Run a shell line with the syscall tracer held on, then restore the
 * previous mode. `strace` uses the verbose (named + decoded) form;
 * `ltrace` is the honest proxy this kernel can offer: static ELFs carry
 * no PLT to hook, so it traces the allocator-backed syscalls malloc/free
 * actually trap to (brk/mmap/munmap/mprotect) and says so up front. */
static void shell_cmd_trace_run(int argc, char **argv, int ltrace) {
    int prev_on, prev_vb;
    int ret;
    if (argc < 2) {
        vga_puts(ltrace ? "usage: ltrace <command> [args...]\n"
                        : "usage: strace <command> [args...]\n");
        return;
    }
    unsigned long before, after;
    prev_on = (int)syscall_trace_enabled();
    prev_vb = (int)syscall_trace_verbose_enabled();
    syscall_trace_set(1);
    syscall_trace_verbose_set(1);
    if (ltrace)
        vga_puts("ltrace: no PLT on static ELFs; brk/mmap/mprotect/open/close only\n");
    before = syscall_trace_shown();
    shell_exec_builtin(argc - 1, argv + 1);
    after = syscall_trace_shown();
    ret = 0;
    (void)ret;
    syscall_trace_set(prev_on);
    syscall_trace_verbose_set(prev_vb);
    /* Zero traced syscalls means the target never crossed into ring 3:
     * a shell builtin runs in ring 0, so there is nothing to trace.
     * Say so explicitly instead of printing a bare "done" that reads
     * as "the tracer is broken". */
    if (after == before)
        kprintf("%s: '%s' is a shell builtin (ring 0): nothing to trace (try '%s run bin/lxhello.elf')\n",
                ltrace ? "ltrace" : "strace", argv[1],
                ltrace ? "ltrace" : "strace");
    kprintf("%s: done (%lu syscalls, tracing %s)\n",
            ltrace ? "ltrace" : "strace", after - before,
            prev_on ? "restored on" : "off");
}

/* Shared magnitude loop behind every strict numeric operand: consumes
 * decimal digits (plus a-f when base is 16), whole string, fail-closed
 * on empty input, garbage or a magnitude past lim. One copy serves the
 * unsigned inspector parser, the signed shell/editor parser and, through
 * it, the volume parser, so the digit/overflow logic cannot drift. */
static int shell_parse_mag(const char *s, unsigned long base,
                           unsigned long lim, unsigned long *out) {
    unsigned long v = 0;
    int any = 0;
    if (!s || !s[0]) return 0;
    for (; *s; s++) {
        unsigned long d;
        if (*s >= '0' && *s <= '9') d = (unsigned long)(*s - '0');
        else if (base == 16 && *s >= 'a' && *s <= 'f')
            d = (unsigned long)(*s - 'a' + 10);
        else if (base == 16 && *s >= 'A' && *s <= 'F')
            d = (unsigned long)(*s - 'A' + 10);
        else return 0;
        if (d >= base) return 0;
        if (v > (lim - d) / base) return 0;
        v = v * base + d;
        any = 1;
    }
    if (!any) return 0;
    *out = v;
    return 1;
}

/* Strict unsigned parse for debugger/inspector operands: `0x`-prefixed
 * hex or plain decimal, no signs, no trailing garbage, fail-closed on
 * overflow or empty input. katol is decimal-only, so `gdb dump 0x400000`
 * used to parse as 0; this is the single choke point for numeric
 * inspector arguments. */
static int shell_parse_u64(const char *s, unsigned long *out) {
    unsigned long base = 10;
    if (!s || !s[0]) return 0;
    if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X')) {
        base = 16;
        s += 2;
    }
    return shell_parse_mag(s, base, 0xFFFFFFFFFFFFFFFFUL, out);
}

/* Strict signed decimal twin of shell_parse_u64: optional sign, at
 * least one digit, whole string consumed, overflow fail-closed. The
 * bound comes from the compiler's __LONG_MAX__ (freestanding-safe, no
 * libc header needed); a negative sign allows one extra unit of
 * magnitude for LONG_MIN. Shared through shell.h so the editor's line
 * numbers use the same choke point instead of a second copy. */
int shell_parse_long(const char *s, long *out) {
    unsigned long v = 0;
    unsigned long lim;
    int neg = 0;
    if (!s || !s[0]) return 0;
    if (*s == '-') { neg = 1; s++; }
    else if (*s == '+') s++;
    lim = (unsigned long)__LONG_MAX__ + (neg ? 1UL : 0UL);
    if (!shell_parse_mag(s, 10, lim, &v)) return 0;
    if (neg) {
        if (v == lim) *out = (-__LONG_MAX__) - 1;
        else *out = -(long)v;
    } else {
        *out = (long)v;
    }
    return 1;
}

/* Bounded pid parse shared by wait/kill/vmmap: one range check instead of
 * three open-coded copies. min_pid is 1 for job commands (pid 0 is the
 * shell view, never a job) and 0 for inspectors like vmmap. */
int shell_parse_pid(const char *s, int min_pid, int *out) {
    long v;
    if (!shell_parse_long(s, &v)) return 0;
    if (v < min_pid || v >= MAX_PROCS) return 0;
    *out = (int)v;
    return 1;
}

/* `gdb <op>` -- in-OS inspector half of the debugger story. Full
 * register-level debugging (breakpoints, single-step, live register edit)
 * stays on the QEMU gdb stub: `make gdb`, then from the host
 * `gdb -ex 'target remote :1234' -ex 'add-symbol-file kernel.elf 0x100000'`.
 * Here: `gdb regs [pid]` dumps the stored context (LIVE sampled registers
 * for the running pid), `gdb dump <addr> <len>` hexdumps 1..256 bytes
 * (decimal or 0x-hex), `gdb qemu` prints the remote hookup. */
static void shell_cmd_gdb(int argc, char **argv) {
    if (argc < 2) {
        vga_puts("usage: gdb [regs [pid] | dump <addr> <len> | qemu]\n");
        return;
    }
    if (kstrcmp(argv[1], "regs") == 0) {
        int pid = current_pid < 0 ? 0 : current_pid;
        unsigned long v;
        if (argc > 2) {
            if (!shell_parse_u64(argv[2], &v) || v >= (unsigned long)MAX_PROCS) {
                kprintf("gdb: bad pid '%s' (0..%d, see ps)\n",
                        argv[2], MAX_PROCS - 1);
                return;
            }
            pid = (int)v;
        }
        gdb_regs_report(pid);
        return;
    }
    if (kstrcmp(argv[1], "dump") == 0) {
        unsigned long addr, len;
        if (argc < 4) { vga_puts("usage: gdb dump <addr> <len>\n"); return; }
        if (!shell_parse_u64(argv[2], &addr) ||
            !shell_parse_u64(argv[3], &len)) {
            kprintf("gdb: bad number (decimal or 0x-hex, no garbage)\n");
            return;
        }
        gdb_dump_report(addr, len);
        return;
    }
    if (kstrcmp(argv[1], "qemu") == 0) {
        vga_puts("gdb: make gdb -> QEMU -s -S (:1234, halted)\n");
        vga_puts("gdb: host: target remote :1234 + add-symbol-file kernel.elf 0x100000\n");
        return;
    }
    vga_puts("usage: gdb [regs [pid] | dump <addr> <len> | qemu]\n");
}

/* `hash <file>` — XXH64 (64-bit, seed 0) of a ramdisk/MiniFS file, streamed
 * in bounded chunks so a large MiniFS file never needs a whole-file buffer.
 * This is the integrity tool for CVM modules and any ramdisk payload: an
 * image built from source is compared against a recorded hash, and a module
 * that drifted is detected before it is trusted. */
static void shell_cmd_hash(int argc, char **argv) {
    KFILE *f;
    unsigned char buf[1024];
    unsigned long n;
    XXH64_state_t h;
    if (argc < 2) { vga_puts("usage: hash <file>\n"); return; }
    f = kfopen(argv[1], "r");
    if (!f) { kprintf("hash: %s: no such file\n", argv[1]); return; }
    XXH64_reset(&h, 0);
    while ((n = kfread(buf, 1, sizeof(buf), f)) > 0)
        XXH64_update(&h, buf, n);
    kfclose(f);
    kprintf("hash: %s = %016lx\n", argv[1], (unsigned long)XXH64_digest(&h));
}

/** Docstring: Resolve `arg` against the cwd into `out`
 * (`RAMDISK_FNAME_LEN` bytes); on failure print `<cmd>: <arg>: <reason>`
 * and return 0. Unifies the resolve-or-diagnose prelude every path-taking
 * builtin repeats. */
static int shell_resolve_arg(const char *cmd, const char *arg,
                             const char *reason, char *out) {
    if (fs_resolve(arg, out, RAMDISK_FNAME_LEN)) return 1;
    kprintf("%s: %s: %s\n", cmd, arg, reason);
    return 0;
}

/* `ls`: extracted from shell_exec_builtin so its listing locals (dir
 * buffers, file list, dir entries) live in this frame instead of
 * inflating the dispatch frame past the 2 KB gate (stack discipline,
 * CLAUDE.md). */
static void shell_cmd_ls(int argc, char **argv) {
    char dir[RAMDISK_FNAME_LEN];
    unsigned plen;
    /* Heap list like ps/schedtop: 128 pointers are 1 KB that must not
     * live in any frame. */
    RDFile **files = (RDFile **)kmalloc(sizeof(RDFile *) * RAMDISK_MAX_FILES);
    int n, i, shown = 0;
    if (!files) { kprintf("ls: out of memory\n"); return; }
    if (argc > 1) {
        if (!fs_resolve(argv[1], dir, sizeof(dir))) {
            shell_report("ls: name too long: ", argv[1]);
            kfree(files);
            return;
        }
        unsigned dl = (unsigned)kstrlen(dir);
        if (dl && dir[dl - 1] != '/') {
            if (dl + 1 >= sizeof(dir)) { kfree(files); return; }
            dir[dl] = '/';
            dir[dl + 1] = 0;
        }
        if (!fs_dir_exists(dir)) {
            shell_report("ls: no such directory: ", dir);
            kfree(files);
            return;
        }
    } else {
        kmemcpy(dir, fs_cwd, RAMDISK_FNAME_LEN);
    }
    plen = (unsigned)kstrlen(dir);
    n = ramdisk_list(files, RAMDISK_MAX_FILES);
    for (i = 0; i < n; i++) {
        if (plen && kstrncmp(files[i]->name, dir, plen) != 0) continue;
        if ((unsigned)kstrlen(files[i]->name) == plen) continue; /* dir marker */
        kprintf("  %-20s  %u bytes\n", files[i]->name + plen, files[i]->size);
        shown = 1;
    }
    if (!shown && minifs_is_mounted()) {
        char bare[RAMDISK_FNAME_LEN];
        unsigned bl;
        int ino;
        MiniFSInode dst;
        kmemcpy(bare, dir, plen + 1);
        bl = plen;
        while (bl > 0 && bare[bl - 1] == '/') bare[--bl] = 0;
        ino = (bl == 0) ? MINIFS_ROOT_INODE : minifs_resolve_path(bare);
        if (ino >= 0 && minifs_stat(ino, &dst) == 0 &&
            (dst.mode & 0170000) == 0040000) {
            MiniFSDirEntry de;
            char mname[RAMDISK_FNAME_LEN];
            int idx = 0;
            while (minifs_dir_read(ino, idx, &de, mname) == 0) {
                MiniFSInode st;
                idx++;
                if (de.inode == 0) continue;
                if (minifs_stat(de.inode, &st) < 0) continue;
                if ((st.mode & 0170000) == 0040000)
                    kprintf("  %s/\n", mname);
                else
                    kprintf("  %-20s  %u bytes\n", mname, st.size);
                shown = 1;
            }
        }
    }
    if (!shown) vga_puts("  (empty)\n");
    kfree(files);
}

/* Dispatcher exemption from the -Wframe-larger-than=2048 gate: this
 * function runs only on the shell's own boot stack (generous), never on
 * a 16 KB proc slot — no ring-3 syscall path reaches it — and -Os
 * inlines single-use command helpers into its frame. Shrinking the
 * number further would mean splitting every branch for the metric
 * without changing peak stack one byte, so the exemption stands while
 * every syscall/ISR-reachable function stays gated. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-larger-than="
/* Dispatcher exemption from the -Wframe-larger-than=2048 gate: this
 * function runs only on the shell's own boot stack (generous), never on
 * a 16 KB proc slot — no ring-3 syscall path reaches it — and -Os
 * inlines single-use command helpers into its frame. Shrinking the
 * number further would mean splitting every branch for the metric
 * without changing peak stack one byte, so the exemption stands while
 * every syscall/ISR-reachable function stays gated. */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wframe-larger-than="

/* ---- httpd helpers (static file server over server-side TCP) ---- */

#define HTTPD_REQ_CAP 2048u
#define HTTPD_IO_CHUNK 2048u

/* Serve one accepted connection: read one request, map GET path onto
 * the VFS mounts under root, stream head + body, close. Every failure
 * is a status code, never a hang: the request read is deadline
 * bounded and every oversize/shortfall path answers 4xx. */
static void shell_httpd_one(int child, const char *root) {
    char *req = 0;
    char upath[HTTPD_MAX_PATH];
    char fspath[RAMDISK_FNAME_LEN];
    char head[HTTPD_HEAD_MAX];
    vfs_file_t f;
    unsigned long body_len = 0u;
    int code = 200;
    const char *reason = "OK";
    int n, hn;
    req = kmalloc(HTTPD_REQ_CAP);
    if (!req) return;
    n = net_recv_timeout(child, req, (int)(HTTPD_REQ_CAP - 1), 10000);
    if (n <= 0) {
        hn = httpd_header(400, "Bad Request", "text/plain", 0u, head, sizeof(head));
        if (hn > 0) net_send(child, head, hn);
        kfree(req);
        return;
    }
    req[n] = 0;
    if (httpd_parse_get(req, (unsigned long)n, upath, sizeof(upath)) != 0) {
        code = 400;
        reason = "Bad Request";
    } else {
        unsigned long rl = kstrlen(root), pl = kstrlen(upath);
        if (rl + 1u + pl >= sizeof(fspath)) {
            code = 414;
            reason = "URI Too Long";
        } else {
            unsigned long k;
            for (k = 0u; k < rl; k++) fspath[k] = root[k];
            fspath[rl] = '/';
            for (k = 0u; k <= pl; k++) fspath[rl + 1u + k] = upath[k];
            if (vfs_open(fspath, 0, &f) != 0) {
                code = 404;
                reason = "Not Found";
            } else {
                if (vfs_fstat(&f, &body_len) != 0) {
                    vfs_close(&f);
                    code = 500;
                    reason = "Internal Error";
                }
            }
        }
    }
    if (code != 200) {
        hn = httpd_header(code, reason, "text/plain", 0u, head, sizeof(head));
        if (hn > 0) net_send(child, head, hn);
        kprintf("httpd: GET %s -> %d\n", code == 400 ? "?" : upath, code);
        kfree(req);
        return;
    }
    hn = httpd_header(200, "OK", httpd_ctype(upath), body_len, head, sizeof(head));
    if (hn <= 0 || net_send(child, head, hn) != hn) {
        vfs_close(&f);
        kfree(req);
        return;
    }
    {
        char *chunk = kmalloc(HTTPD_IO_CHUNK);
        unsigned long sent = 0u;
        if (chunk) {
            while (sent < body_len) {
                int want = (int)((body_len - sent > HTTPD_IO_CHUNK) ?
                        HTTPD_IO_CHUNK : (body_len - sent));
                int got = vfs_read(&f, chunk, (unsigned long)want);
                int w;
                if (got <= 0) break;
                w = net_send(child, chunk, got);
                if (w != got) break;
                sent += (unsigned long)got;
            }
            kfree(chunk);
        }
        kprintf("httpd: GET /%s -> 200 (%lu bytes)\n", upath, sent);
    }
    vfs_close(&f);
    kfree(req);
}

/* Accept loop: one connection at a time, Ctrl+C quits. The accept
 * poll is non-blocking with a yield so the desktop tick and the
 * console stay live while waiting for peers. max_conn < 0 serves
 * forever; otherwise the loop exits after that many connections
 * (--once scripts a single fetch from the host with -hostfwd). */
static void shell_httpd_serve(unsigned short port, const char *root,
        int max_conn) {
    int lfd = net_listen(port);
    int served = 0;
    if (lfd < 0) {
        kprintf("httpd: cannot listen on %u\n", (unsigned)port);
        return;
    }
    kprintf("httpd: serving '%s' on port %u (Ctrl+C quits)\n",
            root[0] ? root : "/", (unsigned)port);
    for (;;) {
        int child;
        if (console_peek() == 0x03) {
            console_getc();
            vga_puts("^C\n");
            break;
        }
        child = net_accept_nb(lfd);
        if (child < 0) {
            yield();
            continue;
        }
        shell_httpd_one(child, root);
        net_close(child);
        served++;
        if (max_conn >= 0 && served >= max_conn) break;
    }
    net_close(lfd);
}

/* Headless proof: the full server handshake plus one request/response
 * through the production demux with injected peer segments (no NIC
 * needed: transmits fail closed without ARP, receives are real). */
static void shell_httpd_selftest(void) {
    static const unsigned char peer[4] = { 10, 0, 2, 99 };
    static const char body[] = "httpd-selftest-bytes";
    static const char get[] = "GET /self.txt HTTP/1.0\r\n\r\n";
    int lfd, child;
    unsigned cseq = 0u, cack = 0u;
    vfs_file_t f;
    char req[HTTPD_REQ_CAP];
    char upath[HTTPD_MAX_PATH];
    char head[HTTPD_HEAD_MAX];
    int n, hn;
    lfd = net_listen(18080);
    if (lfd < 0) {
        vga_puts("httpd: selftest listen failed\n");
        return;
    }
    vga_puts("httpd: listen ok\n");
    /* Seed the served file on the mem: proof tree. */
    if (vfs_open("mem:/self.txt", 1, &f) != 0 ||
            vfs_write(&f, body, 20) != 20) {
        vga_puts("httpd: selftest seed failed\n");
        net_close(lfd);
        return;
    }
    vfs_close(&f);
    net_test_inject_tcp(peer, 50000, 18080, 0x02, 1000u, 0u, 0, 0);
    if (net_accept_nb(lfd) >= 0) {
        vga_puts("httpd: selftest accepted before ACK\n");
        net_close(lfd);
        return;
    }
    vga_puts("httpd: syn ok\n");
    {
        int ci;
        /* Pending child only: find the SYN_RCVD socket on this port. */
        int found = -1;
        for (ci = 0; ci < 16; ci++) {
            if (net_sock_state(ci) == 6) { found = ci; break; }
        }
        if (found < 0 || net_sock_seq(found, &cseq, &cack) != 0) {
            vga_puts("httpd: selftest no pending child\n");
            net_close(lfd);
            return;
        }
    }
    /* A wrong ACK completes nothing: the child stays SYN_RCVD and the
     * accept still finds nobody. Only the exact ack establishes. */
    net_test_inject_tcp(peer, 50000, 18080, 0x10, 1001u, cseq + 500u, 0, 0);
    if (net_accept_nb(lfd) >= 0) {
        vga_puts("httpd: selftest accepted on wrong ack\n");
        net_close(lfd);
        return;
    }
    vga_puts("httpd: ack guard ok\n");
    net_test_inject_tcp(peer, 50000, 18080, 0x10, 1001u, cseq, 0, 0);
    child = net_accept_nb(lfd);
    if (child < 0 || net_sock_state(child) != 2) {
        vga_puts("httpd: selftest handshake failed\n");
        net_close(child);
        net_close(lfd);
        return;
    }
    vga_puts("httpd: handshake ok\n");
    if (net_sock_seq(child, &cseq, &cack) != 0) {
        vga_puts("httpd: selftest seq read failed\n");
        net_close(child);
        net_close(lfd);
        return;
    }
    net_test_inject_tcp(peer, 50000, 18080, 0x18, cack, cseq,
            (const unsigned char *)get, 26);
    net_test_inject_tcp(peer, 50000, 18080, 0x11, cack + 26u, cseq, 0, 0);
    n = net_recv_timeout(child, req, (int)sizeof(req) - 1, 2000);
    if (n != 26 || httpd_parse_get(req, (unsigned long)n, upath,
                sizeof(upath)) != 0) {
        vga_puts("httpd: selftest request failed\n");
        net_close(child);
        net_close(lfd);
        return;
    }
    vga_puts("httpd: request ok\n");
    if (vfs_open("mem:/self.txt", 0, &f) != 0) {
        vga_puts("httpd: selftest serve open failed\n");
        net_close(child);
        net_close(lfd);
        return;
    }
    {
        unsigned long sz = 0u;
        char got[32];
        int gotn;
        vfs_fstat(&f, &sz);
        gotn = vfs_read(&f, got, sz < 20u ? sz : 20u);
        vfs_close(&f);
        hn = httpd_header(200, "OK", httpd_ctype(upath), sz, head,
                sizeof(head));
        if (sz != 20u || gotn != 20 || hn <= 0) {
            vga_puts("httpd: selftest body failed\n");
            net_close(child);
            net_close(lfd);
            return;
        }
        {
            int k, ok = 1;
            for (k = 0; k < 20; k++)
                if (got[k] != body[k]) ok = 0;
            if (!ok) {
                vga_puts("httpd: selftest body mismatch\n");
                net_close(child);
                net_close(lfd);
                return;
            }
        }
    }
    vga_puts("httpd: 200 ok\n");
    hn = httpd_header(404, "Not Found", "text/plain", 0u, head,
            sizeof(head));
    if (hn <= 0) {
        vga_puts("httpd: selftest 404 failed\n");
        net_close(child);
        net_close(lfd);
        return;
    }
    vga_puts("httpd: 404 ok\n");
    net_close(child);
    net_close(lfd);
    vga_puts("httpd: selftest ok\n");
}

/* Stream one file from a cross-filesystem VFS driver (fat:, ext4:)
 * to the console: "drv:/img:path" per open (the prefix match needs
 * '/' after "drv:", stripped before the driver splits img from
 * path), 4 KB heap chunks so a hostile size can never drive an
 * oversized alloc. Shared by the fat and ext4 builtins instead of
 * one copy each. */
static void shell_cross_cat(const char *drv, const char *imgarg,
                            const char *patharg) {
    char img[RAMDISK_FNAME_LEN];
    char vpath[5 + RAMDISK_FNAME_LEN + 1 + EXT4_PATH_MAX];
    vfs_file_t f;
    char *chunk;
    int n;
    unsigned long dl = kstrlen(drv);
    if (dl == 0 || dl > 4) return;
    if (!shell_resolve_arg(drv, imgarg, "no such image", img)) return;
    if (kstrlen(patharg) >= EXT4_PATH_MAX) {
        kprintf("%s: %s: name too long\n", drv, patharg);
        return;
    }
    {
        unsigned long il = kstrlen(img), fl = kstrlen(patharg), k;
        for (k = 0; k < dl; k++) vpath[k] = drv[k];
        vpath[dl] = ':';
        vpath[dl + 1] = '/';
        kmemcpy(vpath + dl + 2, img, il);
        vpath[dl + 2 + il] = ':';
        kmemcpy(vpath + dl + 3 + il, patharg, fl + 1);
    }
    if (vfs_open(vpath, 0, &f) != 0) {
        kprintf("%s: %s: no such file\n", drv, patharg);
        return;
    }
    chunk = (char *)kmalloc(4096);
    if (!chunk) {
        vfs_close(&f);
        kprintf("%s: out of memory\n", drv);
        return;
    }
    for (;;) {
        n = vfs_read(&f, chunk, 4096);
        if (n <= 0) break;
        for (int i = 0; i < n; i++) vga_putc(chunk[i]);
    }
    vfs_close(&f);
    kfree(chunk);
}

void shell_exec_builtin(int argc, char **argv) {
    if (kstrcmp(argv[0], "help") == 0) {
        vga_puts("Commands: help clear ls lsfs cat catfs echo edit vedit rm mkdir cd pwd ps load run sh\n");
        vga_puts("          net trace strace ltrace vmmap schedtop irqstat bootlog gdb date vol kbd gfx wm hash\n");
        vga_puts("          unzip zip smp kstack mem minifetch sb16 perf clock jobs wait kill sleep mrun\n");
        vga_puts("          rmdir rlimit nice seccomp poweroff mount unmount vfstest httpd clip panic\n");
        vga_puts("  ls [dir]           list files (under the cwd by default)\n");
        vga_puts("  lsfs               list files on the MiniFS disk filesystem\n");
        vga_puts("  catfs <file>       print a file from MiniFS\n");
        vga_puts("  cd [dir] / pwd     change / print the working directory\n");
        vga_puts("  mkdir <name>       create a directory entry\n");
        vga_puts("  rmdir <dir>        remove an empty directory\n");
        vga_puts("  rm <file>          delete a ramdisk file\n");
        vga_puts("  mv <src> <dst>    rename a file within its filesystem\n");
        vga_puts("  fat ls|cat        read-only FAT32 loopback image browser\n");
        vga_puts("  ext4 ls|cat       read-only ext4 loopback/partition browser\n");
        vga_puts("  rlimit [k] [v]     caps: as bytes, cpu ticks, nofile count\n");
        vga_puts("  nice [n]           scheduler niceness -20..19\n");
        vga_puts("  seccomp <op> [n]   deny/allow MiniOS syscalls 200..231\n");
        vga_puts("  ps                 list live processes (pid/ppid/state)\n");
        vga_puts("  smp                per-CPU state and thread dispatches\n");
        vga_puts("  kstack             kernel-stack high-water marks + canary\n");
        vga_puts("  net                network status (rtl8139, slirp)\n");
        vga_puts("  net ping <ip>      one ICMP echo\n");
        vga_puts("  trace [on|off|verbose|quiet] report syscalls (verbose names+args)\n");
        vga_puts("  strace <cmd>       run one command with verbose tracing\n");
        vga_puts("  ltrace <cmd>       allocator-trap proxy (no PLT on static ELFs)\n");
        vga_puts("  vmmap [pid]        user-window map + VMA tree\n");
        vga_puts("  schedtop           cpus, thread groups, ticks per thread\n");
        vga_puts("  irqstat            timer/kbd/mouse/sb16/net/gfx arrivals\n");
        vga_puts("  bootlog            timestamped boot phases\n");
        vga_puts("  gdb [regs|dump|qemu] in-OS inspector; remote GDB via `make gdb`\n");
        vga_puts("  panic              paint the panic screen (demo, no halt)\n");
        vga_puts("  mount [p driver]   list VFS mounts or mount ramdisk|minifs|mem|fat|ext4\n");
        vga_puts("  unmount <prefix>   drop a VFS mount (busy refuses, / pinned)\n");
        vga_puts("  vfstest            prove mount/unmount/remount on mem:\n");
        vga_puts("  httpd [--once] <port> [root] static file server (GET, VFS root)\n");
        vga_puts("  httpd --selftest   prove the server handshake headless\n");
        vga_puts("  clip [text|clear]  shared clipboard (terminal copy, vedit paste)\n");
        vga_puts("  date               print the CMOS clock (HH:MM:SS)\n");
        vga_puts("  vol [0-100]        print or set the PC-speaker volume\n");
        vga_puts("  kbd [en|es]        print or set the keyboard layout\n");
        vga_puts("  gfx [..]           graphics state / pixel / rect / shot\n");
        vga_puts("  wm [op]            window mgmt: minimize|maximize|close|split|list|tile|focus|state\n");
        vga_puts("  Alt+Tab focus next, Super+Tab tile, Super+arrows snap focused\n");
        vga_puts("  desktop [stop|status] wayland session: tile NK apps as windows\n");
        vga_puts("  hash <file>        XXH64 checksum of a file\n");
        vga_puts("  mem                heap/ramdisk/minifs/procs pressure\n");
        vga_puts("  minifetch          system screen (doom logo + specs)\n");
        vga_puts("  unzip <z> [dir]    extract a ZIP archive (or -l to list)\n");
        vga_puts("  zip <out> <f...>   store files into a ZIP archive\n");
        vga_puts("  edit <file>        line editor for ramdisk files\n");
        vga_puts("  vedit <file>       fullscreen editor (C/Python/Lua)\n");
        vga_puts("  run  <name|file>   run a loaded program, ELF or .cvm module\n");
        vga_puts("  run/mrun ... &    background jobs (isolated ELFs, prompt returns)\n");
        vga_puts("  jobs|wait|kill    list / reap / terminate background jobs (^C kills fg)\n");
        vga_puts("  sleep <secs>      yield until the wall clock advances (^C aborts)\n");
        vga_puts("  mrun <a.elf> [...] run isolated ELFs concurrently (multitask)\n");
        vga_puts("  load <file>        load an ELF (.o relocatable or Linux exe)\n");
        vga_puts("  <cmd> > <file>     redirect command output to a file\n");
        vga_puts("  <cmd> 2> <file>    same capture (MiniOS merges stdout/stderr)\n");
        vga_puts("  <a> | <b>          pipe stdout of a into stdin of b\n");
        vga_puts("  <cmd> [args...]    run a file or bare name (objects/bin/cvm)\n");
        vga_puts("Keys: TAB complete, Up/Dn prefix history, Right accept suggestion\n");
        vga_puts("Toolchain: edit p.c; minigcc.o p.c > p.s;\n");
        vga_puts("           ld.o -f elf -o p.elf p.s; p.elf\n");
        vga_puts("CVM:       minigcc.o w1.c > w1.s; ld.o -f cvm -o w1.cvm w1.s; w1.cvm\n");
        vga_puts("Interpreters: micropython (REPL/script), lua (REPL/script);\n");
        vga_puts("           lua src/test.lua runs the in-OS test suite (minios module)\n");
    }
    else if (kstrcmp(argv[0], "clear") == 0) {
        vga_clear();
    }
    else if (kstrcmp(argv[0], "poweroff") == 0) {
        shell_cmd_poweroff();
    }
    else if (kstrcmp(argv[0], "edit") == 0) {
        shell_cmd_edit(argc, argv);
    }
    else if (kstrcmp(argv[0], "ls") == 0) {
        shell_cmd_ls(argc, argv);
    }
    else if (kstrcmp(argv[0], "perf") == 0) {
        /* Diagnose where guest time goes: raw CPU, ktime_ms overhead, and
         * console output throughput (serial + terminal render). */
        unsigned long a, b, i;
        volatile unsigned long sink = 0;
        a = ktime_ms();
        for (i = 0; i < 1000000; i++) __asm__ volatile("nop");
        b = ktime_ms();
        kprintf("perf: 1M nop = %ld ms\n", (long)(b - a));
        a = ktime_ms();
        for (i = 0; i < 100000; i++) sink += ktime_ms();
        b = ktime_ms();
        kprintf("perf: 100k ktime_ms = %ld ms\n", (long)(b - a));
        a = ktime_ms();
        for (i = 0; i < 1000; i++)
            kprintf("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789\n");
        b = ktime_ms();
        kprintf("perf: 1000x100-char kprintf = %ld ms\n", (long)(b - a));
        kprintf("perf: done (sink %ld)\n", (long)sink);
    }
    else if (kstrcmp(argv[0], "cat") == 0) {
        /* No file arguments: copy stdin to stdout, so `cat` terminates
         * a pipeline (`echo hi | cat`) and echoes piped bytes. stdin
         * here is console_getc, which serves the pipeline buffer when
         * a pipe feeds this stage and the live console otherwise. */
        if (argc < 2) {
            int c;
            if (!console_stdin_active()) {
                vga_puts("usage: cat <file> [file...]\n");
                return;
            }
            while ((c = console_getc()) >= 0)
                vga_putc((char)c);
            return;
        }
        int fi;
        for (fi = 1; fi < argc; fi++) {
            char resolved[RAMDISK_FNAME_LEN];
            if (!fs_resolve(argv[fi], resolved, sizeof(resolved)) || fs_is_dir(resolved)) {
                kprintf("cat: %s: no such file or is a directory\n", argv[fi]);
                return;
            }
            KFILE *kf = kfopen(argv[fi], "r");
            if (!kf) { kprintf("cat: %s: no such file\n", argv[fi]); return; }
            char c;
            while (kfread(&c, 1, 1, kf) == 1)
                vga_putc(c);
            kfclose(kf);
        }
        vga_putc('\n');
    }
    else if (kstrcmp(argv[0], "lsfs") == 0) {
        if (!minifs_is_mounted()) { vga_puts("minifs: not mounted\n"); return; }
        int parent = MINIFS_ROOT_INODE;
        if (argc > 1) {
            parent = minifs_resolve_path(argv[1]);
            if (parent < 0) { kprintf("lsfs: %s: not found\n", argv[1]); return; }
        }
        MiniFSInode dir_inode;
        if (minifs_stat(parent, &dir_inode) < 0) return;
        if ((dir_inode.mode & 0170000) != 0040000) {
            kprintf("  %s  %u bytes\n", argv[1], dir_inode.size);
            return;
        }
        MiniFSDirEntry de;
        char name[RAMDISK_FNAME_LEN];
        int idx = 0, shown = 0;
        while (minifs_dir_read(parent, idx, &de, name) == 0) {
            if (de.inode == 0) { idx++; continue; }
            MiniFSInode st;
            minifs_stat(de.inode, &st);
            if ((st.mode & 0170000) == 0040000)
                kprintf("  %s/\n", name);
            else
                kprintf("  %-20s  %u bytes\n", name, st.size);
            shown = 1;
            idx++;
        }
        if (!shown) vga_puts("  (empty)\n");
    }
    else if (kstrcmp(argv[0], "catfs") == 0) {
        if (!minifs_is_mounted()) { vga_puts("minifs: not mounted\n"); return; }
        if (argc < 2) { vga_puts("usage: catfs <file>\n"); return; }
        int ino = minifs_resolve_path(argv[1]);
        if (ino < 0) { kprintf("catfs: %s: not found\n", argv[1]); return; }
        MiniFSInode st;
        if (minifs_stat(ino, &st) < 0) { kprintf("catfs: %s: stat failed\n", argv[1]); return; }
        unsigned sz = st.size;
        if (sz == 0) { vga_putc('\n'); return; }
        char *catfs_buf = (char *)kmalloc(sz + 1);
        if (!catfs_buf) { vga_puts("catfs: out of memory\n"); return; }
        minifs_read(ino, catfs_buf, 0, sz);
        catfs_buf[sz] = 0;
        for (unsigned i = 0; i < sz; i++) vga_putc(catfs_buf[i]);
        vga_putc('\n');
        kfree(catfs_buf);
    }
    else if (kstrcmp(argv[0], "rm") == 0) {
        if (argc < 2) { vga_puts("usage: rm <file>\n"); return; }
        char resolved[RAMDISK_FNAME_LEN];
        if (!shell_resolve_arg("rm", argv[1], "no such file", resolved)) {
            return;
        }
        if (fs_is_dir(resolved)) {
            kprintf("rm: %s: is a directory\n", argv[1]);
            return;
        }
        RDFile *f = ramdisk_open(resolved);
        if (f) {
            ramdisk_delete(f);
            kprintf("removed %s\n", resolved);
            return;
        }
        /* Writes fall back to MiniFS when the ramdisk namespace cannot
         * host them (kfopen), so deletes must too: otherwise a file the
         * shell just created via redirect is undeletable (`rm: no such
         * file` right after a successful `cat`). */
        if (minifs_is_mounted() && minifs_unlink(resolved) == 0) {
            kprintf("removed %s\n", resolved);
            return;
        }
        kprintf("rm: %s: no such file\n", argv[1]);
    }
    else if (kstrcmp(argv[0], "mv") == 0) {
        /* `mv <src> <dst>`: one file, same filesystem, through fs_rename
         * (ramdisk in-place, MiniFS entry move, no data copy). Refuses
         * directories, a missing src, an existing dst (no silent
         * overwrite) and cross-filesystem moves, each with its own
         * diagnostic, never a half-moved file. */
        char src[RAMDISK_FNAME_LEN], dst[RAMDISK_FNAME_LEN];
        int r;
        if (argc < 3) { vga_puts("usage: mv <src> <dst>\n"); return; }
        if (!shell_resolve_arg("mv", argv[1], "no such file", src)) return;
        if (!shell_resolve_arg("mv", argv[2], "name too long", dst)) return;
        r = fs_rename(src, dst);
        if (r == 0) { kprintf("renamed %s to %s\n", src, dst); return; }
        if (r == -21) { kprintf("mv: %s: is a directory\n", argv[1]); return; }
        if (r == -17) { kprintf("mv: %s: already exists\n", argv[2]); return; }
        if (r == -18) { kprintf("mv: %s: other filesystem or missing directory\n", argv[2]); return; }
        kprintf("mv: %s: no such file\n", argv[1]);
    }
    /* `mount [prefix driver]`: list the live VFS mounts, or mount a
     * known driver (ramdisk, minifs, mem) under a new prefix.
     * `unmount <prefix>`: drop a mount; busy (open handles) refuses
     * with -EBUSY, the pinned root "" refuses, unknown refuses. */
    else if (kstrcmp(argv[0], "mount") == 0) {
        if (argc == 1) {
            char (*pfx)[VFS_PREFIX_LEN] = kmalloc(8u * VFS_PREFIX_LEN);
            char (*drv)[VFS_DRIVER_LEN] = 0;
            int *refs = 0;
            int n = 0, i;
            if (!pfx) { vga_puts("mount: out of memory\n"); return; }
            drv = kmalloc(8u * VFS_DRIVER_LEN);
            refs = kmalloc(8u * sizeof(int));
            if (!drv || !refs) {
                if (drv) kfree(drv);
                if (refs) kfree(refs);
                kfree(pfx);
                vga_puts("mount: out of memory\n");
                return;
            }
            n = vfs_list(pfx, drv, refs, 8);
            for (i = 0; i < n; i++)
                kprintf("  %s (%s) refs=%d\n",
                        pfx[i][0] ? pfx[i] : "/",
                        drv[i], refs[i]);
            if (!n) vga_puts("  (no mounts)\n");
            kfree(pfx); kfree(drv); kfree(refs);
            return;
        }
        if (argc == 3) {
            if (vfs_mount_driver(argv[1], argv[2]) == 0) {
                kprintf("mount: %s on %s\n", argv[2], argv[1]);
                return;
            }
            kprintf("mount: cannot mount %s on %s\n", argv[2], argv[1]);
            return;
        }
        vga_puts("usage: mount [prefix driver]\n");
        return;
    }
    else if (kstrcmp(argv[0], "unmount") == 0) {
        int rc;
        if (argc != 2) { vga_puts("usage: unmount <prefix>\n"); return; }
        rc = vfs_unregister(argv[1]);
        if (rc == 0) { kprintf("unmount: %s removed\n", argv[1]); return; }
        if (rc == -16) { kprintf("unmount: %s busy\n", argv[1]); return; }
        if (rc == -22) { vga_puts("unmount: / is pinned\n"); return; }
        kprintf("unmount: %s: no such mount\n", argv[1]);
        return;
    }
    /* `vfstest`: end-to-end proof of dynamic mounts through the public
     * VFS API: write/read on mem:, busy-refused unmount with a live
     * handle, unmount, closed refusal, remount. Every step prints its
     * marker, so the BDD suite pins the whole lifecycle. */
    else if (kstrcmp(argv[0], "vfstest") == 0) {
        static const char msg[] = "vfs-works";
        vfs_file_t f;
        char back[16];
        int n, i, ok;
        if (vfs_open("mem:/vfs_proof", 1, &f) != 0) {
            vga_puts("vfstest: open for write failed\n");
            return;
        }
        if (vfs_write(&f, msg, 9) != 9) {
            vfs_close(&f);
            vga_puts("vfstest: write failed\n");
            return;
        }
        vfs_close(&f);
        vga_puts("vfstest: rw ok\n");
        if (vfs_open("mem:/vfs_proof", 0, &f) != 0) {
            vga_puts("vfstest: reopen failed\n");
            return;
        }
        kmemset(back, 0, sizeof(back));
        n = vfs_read(&f, back, 9);
        ok = (n == 9);
        for (i = 0; ok && i < 9; i++)
            if (back[i] != msg[i]) ok = 0;
        if (!ok) {
            vfs_close(&f);
            vga_puts("vfstest: data mismatch\n");
            return;
        }
        vga_puts("vfstest: data ok\n");
        if (vfs_unregister("mem:") != -16) {
            vfs_close(&f);
            vga_puts("vfstest: busy unmount not refused\n");
            return;
        }
        vga_puts("vfstest: busy refused\n");
        vfs_close(&f);
        if (vfs_unregister("mem:") != 0) {
            vga_puts("vfstest: unmount failed\n");
            return;
        }
        vga_puts("vfstest: unmount ok\n");
        if (vfs_open("mem:/vfs_proof", 0, &f) == 0) {
            vfs_close(&f);
            vga_puts("vfstest: open after unmount not refused\n");
            return;
        }
        vga_puts("vfstest: closed ok\n");
        if (vfs_mount_driver("mem:", "mem") != 0 ||
                vfs_open("mem:/vfs_proof", 0, &f) != 0) {
            vga_puts("vfstest: remount failed\n");
            return;
        }
        vfs_close(&f);
        vga_puts("vfstest: remount ok\n");
    }
    /* `fat ls <img> [dir]` / `fat cat <img> <file>`: read-only FAT32
     * loopback. The image is an ordinary file (etc/fat.img on MiniFS);
     * directory entries list through fat32_list, file bytes stream
     * through the fat: VFS driver ("img:fatpath" per open, registered
     * at boot beside mem:), 4 KB heap chunks so a hostile size can
     * never drive an oversized alloc. Bad magic, missing files and
     * overlong names are diagnostics. */
    else if (kstrcmp(argv[0], "fat") == 0) {
        if (argc >= 2 && kstrcmp(argv[1], "ls") == 0) {
            static char names[FAT32_LIST_CAP][FAT32_NAME_MAX];
            static int isdir[FAT32_LIST_CAP];
            char img[RAMDISK_FNAME_LEN];
            const char *dir = (argc >= 4) ? argv[3] : "/";
            int n, i;
            if (argc < 3) { vga_puts("usage: fat ls <img> [dir]\n"); return; }
            if (!shell_resolve_arg("fat", argv[2], "no such image", img))
                return;
            n = fat32_list(img, dir, names, isdir, FAT32_LIST_CAP);
            if (n < 0) { kprintf("fat: %s: cannot list %s\n", argv[2], dir); return; }
            for (i = 0; i < n; i++) {
                vga_puts("  ");
                vga_puts(names[i]);
                vga_putc('\n');
            }
            return;
        }
        if (argc >= 2 && kstrcmp(argv[1], "cat") == 0) {
            if (argc < 4) { vga_puts("usage: fat cat <img> <file>\n"); return; }
            shell_cross_cat("fat", argv[2], argv[3]);
            return;
        }
        vga_puts("usage: fat ls <img> [dir] | fat cat <img> <file>\n");
    }
    /* `ext4 ls <img> [dir]` / `ext4 cat <img> <file>`: read-only ext4
     * loopback and disk partitions, the same contract as `fat` over
     * a harder format (extents, block groups, linear dirs). */
    else if (kstrcmp(argv[0], "ext4") == 0) {
        if (argc >= 2 && kstrcmp(argv[1], "ls") == 0) {
            static char names[EXT4_LIST_CAP][EXT4_NAME_MAX + 1];
            static int isdir[EXT4_LIST_CAP];
            char img[RAMDISK_FNAME_LEN];
            const char *dir = (argc >= 4) ? argv[3] : "/";
            int n, i;
            if (argc < 3) { vga_puts("usage: ext4 ls <img> [dir]\n"); return; }
            if (!shell_resolve_arg("ext4", argv[2], "no such image", img))
                return;
            n = ext4_list(img, dir, names, isdir, EXT4_LIST_CAP);
            if (n < 0) { kprintf("ext4: %s: cannot list %s\n", argv[2], dir); return; }
            for (i = 0; i < n; i++) {
                vga_puts("  ");
                vga_puts(names[i]);
                vga_putc('\n');
            }
            return;
        }
        if (argc >= 2 && kstrcmp(argv[1], "cat") == 0) {
            if (argc < 4) { vga_puts("usage: ext4 cat <img> <file>\n"); return; }
            shell_cross_cat("ext4", argv[2], argv[3]);
            return;
        }
        vga_puts("usage: ext4 ls <img> [dir] | ext4 cat <img> <file>\n");
    }
    /* `clip [text...|clear]`: the shared text clipboard (terminal
     * copy, vedit paste). Bare `clip` prints the slot, `clip <words>`
     * publishes them joined by spaces, `clip clear` empties it. Past
     * 4096 bytes refuses, never a silently truncated paste. */
    else if (kstrcmp(argv[0], "clip") == 0) {
        if (argc == 1) {
            /* Fixed 4 KB read buffer (the whole slot, heap): clip_get
             * refuses empty itself, so the empty path is one call,
             * not a racy len-then-get pair. */
            char *buf = kmalloc(4096u);
            int n;
            if (!buf) { vga_puts("clip: out of memory\n"); return; }
            n = clip_get(buf, 4096u);
            if (n < 0) {
                kfree(buf);
                vga_puts("(empty)\n");
                return;
            }
            buf[n] = 0;
            kprintf("%s\n", buf);
            kfree(buf);
            return;
        }
        if (argc == 2 && kstrcmp(argv[1], "clear") == 0) {
            clip_clear();
            return;
        }
        {
            unsigned long total = 0u;
            int i;
            char *joined;
            unsigned long at;
            for (i = 1; i < argc; i++)
                total += kstrlen(argv[i]) + 1u;
            if (total == 0u || total - 1u > 4096u) {
                vga_puts("clip: text too long\n");
                return;
            }
            joined = kmalloc(total);
            if (!joined) { vga_puts("clip: out of memory\n"); return; }
            at = 0u;
            for (i = 1; i < argc; i++) {
                unsigned long l = kstrlen(argv[i]), k;
                for (k = 0u; k < l; k++) joined[at++] = argv[i][k];
                if (i + 1 < argc) joined[at++] = ' ';
            }
            if (clip_set(joined, at) != 0)
                vga_puts("clip: text too long\n");
            kfree(joined);
        }
    }
    /* `vblk`: virtio-blk probe and sector proof. Initializes the
     * device (absent hardware reports `absent`, never hangs), prints
     * capacity, then reads LBA 0 (boot signature) and LBA 2048 (the
     * MiniFS superblock) straight off the virtio queue and checks
     * both magics, proving the fast path serves the same bytes as
     * IDE PIO. */
    else if (kstrcmp(argv[0], "vblk") == 0) {
        unsigned char *sec;
        unsigned long magic;
        if (!vblk_init()) {
            vga_puts("vblk: absent\n");
            return;
        }
        sec = kmalloc(512u);
        if (!sec) { vga_puts("vblk: out of memory\n"); return; }
        kprintf("vblk: present sectors=%lu\n", vblk_sectors());
        if (vblk_read_sectors(0, 1, sec) != 0 ||
                sec[510] != 0x55 || sec[511] != 0xAA) {
            vga_puts("vblk: LBA0 boot signature mismatch\n");
            kfree(sec);
            return;
        }
        vga_puts("vblk: LBA0 ok\n");
        if (vblk_read_sectors(2048, 1, sec) != 0) {
            vga_puts("vblk: superblock unreadable\n");
            kfree(sec);
            return;
        }
        magic = (unsigned long)sec[0] | ((unsigned long)sec[1] << 8) |
                ((unsigned long)sec[2] << 16) | ((unsigned long)sec[3] << 24);
        if (magic != MINIFS_MAGIC) {
            vga_puts("vblk: superblock magic mismatch\n");
            kfree(sec);
            return;
        }
        vga_puts("vblk: superblock ok\n");
        kfree(sec);
    }
    else if (kstrcmp(argv[0], "mkdir") == 0) {
        if (argc < 2) { vga_puts("usage: mkdir <name>\n"); return; }
        char resolved[RAMDISK_FNAME_LEN];
        if (!shell_resolve_arg("mkdir", argv[1], "name too long",
                              resolved)) {
            return;
        }
        char dirname[RAMDISK_FNAME_LEN];
        kmemcpy(dirname, resolved, sizeof(dirname));
        unsigned dl = (unsigned)kstrlen(dirname);
        if (dl == 0 || dirname[dl - 1] != '/') {
            if (dl + 1 >= sizeof(dirname)) { kprintf("mkdir: %s: name too long\n", argv[1]); return; }
            dirname[dl] = '/';
            dirname[dl + 1] = 0;
        }
        if (fs_dir_exists(dirname)) {
            kprintf("mkdir: %s: already exists\n", dirname);
            return;
        }
        if (dl > 0) {
            char parent[RAMDISK_FNAME_LEN];
            unsigned pl = dl - 1;
            while (pl > 0 && dirname[pl - 1] != '/') pl--;
            kmemcpy(parent, dirname, pl);
            parent[pl] = 0;
            if (!fs_dir_exists(parent)) {
                kprintf("mkdir: %s: no such directory\n", parent);
                return;
            }
        }
        if (!ramdisk_create(dirname, 0)) {
            kprintf("mkdir: %s: cannot create\n", dirname);
            return;
        }
        kprintf("created %s\n", dirname);
    }
    else if (kstrcmp(argv[0], "rmdir") == 0) {
        if (argc < 2) { vga_puts("usage: rmdir <dir>\n"); return; }
        char resolved[RAMDISK_FNAME_LEN];
        if (!shell_resolve_arg("rmdir", argv[1], "no such directory",
                              resolved)) {
            return;
        }
        char dirname[RAMDISK_FNAME_LEN];
        kmemcpy(dirname, resolved, sizeof(dirname));
        unsigned dl = (unsigned)kstrlen(dirname);
        if (dl == 0 || dirname[dl - 1] != '/') {
            if (dl + 1 >= sizeof(dirname)) { kprintf("rmdir: %s: no such directory\n", argv[1]); return; }
            dirname[dl] = '/';
            dirname[dl + 1] = 0;
            dl++;
        }
        if (!fs_is_dir(dirname)) {
            kprintf("rmdir: %s: no such directory\n", argv[1]);
            return;
        }
        /* Refuse non-empty ramdisk dirs: any other entry with this prefix
         * means children exist (the flat namespace has no real nesting). */
        {
            RDFile *listed[RAMDISK_MAX_FILES];
            int n = ramdisk_list(listed, RAMDISK_MAX_FILES);
            int i;
            for (i = 0; i < n; i++) {
                if (kstrcmp(listed[i]->name, dirname) != 0 &&
                    kstrncmp(listed[i]->name, dirname, dl) == 0) {
                    kprintf("rmdir: %s: directory not empty\n", argv[1]);
                    return;
                }
            }
        }
        RDFile *f = ramdisk_open(dirname);
        if (f) {
            ramdisk_delete(f);
            kprintf("removed %s\n", dirname);
            return;
        }
        if (minifs_is_mounted() && minifs_rmdir(dirname) == 0) {
            kprintf("removed %s\n", dirname);
            return;
        }
        kprintf("rmdir: %s: cannot remove\n", argv[1]);
    }
    else if (kstrcmp(argv[0], "cd") == 0) {
        if (argc < 2) { fs_cwd[0] = 0; return; }
        char resolved[RAMDISK_FNAME_LEN];
        if (!shell_resolve_arg("cd", argv[1], "no such directory",
                              resolved)) {
            return;
        }
        unsigned rl = (unsigned)kstrlen(resolved);
        if (rl == 0) { fs_cwd[0] = 0; return; }   /* root has no marker */
        char target[RAMDISK_FNAME_LEN];
        kmemcpy(target, resolved, rl + 1);
        if (target[rl - 1] != '/') {
            if (rl + 1 >= sizeof(target)) { kprintf("cd: %s: no such directory\n", argv[1]); return; }
            target[rl] = '/';
            target[rl + 1] = 0;
        }
        if (!fs_dir_exists(target)) {
            kprintf("cd: %s: no such directory\n", argv[1]);
            return;
        }
        kmemcpy(fs_cwd, target, sizeof(target));
    }
    else if (kstrcmp(argv[0], "pwd") == 0) {
        vga_puts(fs_cwd[0] ? fs_cwd : "/");
        vga_putc('\n');
    }
    else if (kstrcmp(argv[0], "trace") == 0) {
        if (argc > 1) {
            if (kstrcmp(argv[1], "on") == 0) syscall_trace_set(1);
            else if (kstrcmp(argv[1], "off") == 0) syscall_trace_set(0);
            else if (kstrcmp(argv[1], "verbose") == 0) {
                syscall_trace_set(1);
                syscall_trace_verbose_set(1);
            }
            else if (kstrcmp(argv[1], "quiet") == 0) syscall_trace_verbose_set(0);
            else { vga_puts("usage: trace [on|off|verbose|quiet]\n"); return; }
        }
        kprintf("syscall tracing: %s (%s)\n",
                syscall_trace_enabled() ? "on" : "off",
                syscall_trace_verbose_enabled() ? "verbose" : "numeric");
    }
    else if (kstrcmp(argv[0], "strace") == 0) {
        shell_cmd_trace_run(argc, argv, 0);
    }
    else if (kstrcmp(argv[0], "ltrace") == 0) {
        shell_cmd_trace_run(argc, argv, 1);
    }
    else if (kstrcmp(argv[0], "vmmap") == 0) {
        shell_cmd_vmmap(argc, argv);
    }
    else if (kstrcmp(argv[0], "schedtop") == 0) {
        (void)argc; (void)argv;
        schedtop_report();
    }
    else if (kstrcmp(argv[0], "irqstat") == 0) {
        (void)argc; (void)argv;
        irqstat_report();
    }
    else if (kstrcmp(argv[0], "bootlog") == 0) {
        (void)argc; (void)argv;
        bootlog_report();
    }
    else if (kstrcmp(argv[0], "gdb") == 0) {
        shell_cmd_gdb(argc, argv);
    }
    else if (kstrcmp(argv[0], "net") == 0) {
        if (argc < 2) {
            net_cmd_status();
        } else if (kstrcmp(argv[1], "ping") == 0) {
            if (argc < 3) { vga_puts("usage: net ping <ip>\n"); return; }
            net_cmd_ping(argv[2]);
        } else if (kstrcmp(argv[1], "dns") == 0) {
            if (argc < 3) { vga_puts("usage: net dns <host>\n"); return; }
            net_cmd_dns(argv[2]);
        } else {
            vga_puts("usage: net [ping <ip> | dns <host>]\n");
        }
    }
    /* `httpd`: minimal static file server over the server-side TCP
     * stack (bind/listen/accept). GET only, one connection at a time,
     * paths mapped onto the VFS mounts under vfs-root (default "mem:"
     * proof tree, "" serves the ramdisk). `--selftest` drives a full
     * handshake plus request/response through the production demux
     * with injected peer segments (no NIC needed). */
    else if (kstrcmp(argv[0], "httpd") == 0) {
        if (argc >= 2 && kstrcmp(argv[1], "--selftest") == 0) {
            shell_httpd_selftest();
            return;
        }
        if (argc < 2) { vga_puts("usage: httpd [--once] <port> [vfs-root]\n"); return; }
        {
            long port = -1;
            int once = 0;
            const char *root = "";
            int ai;
            for (ai = 1; ai < argc; ai++) {
                long v;
                if (kstrcmp(argv[ai], "--once") == 0) {
                    once = 1;
                } else if (port < 0 && shell_parse_long(argv[ai], &v) &&
                        v > 0 && v <= 65535) {
                    port = v;
                } else if (port >= 0 && root[0] == 0 && argv[ai][0] != 0) {
                    root = argv[ai];
                } else {
                    vga_puts("usage: httpd [--once] <port> [vfs-root]\n");
                    return;
                }
            }
            if (port < 0) {
                vga_puts("usage: httpd [--once] <port> [vfs-root]\n");
                return;
            }
            shell_httpd_serve((unsigned short)port, root, once ? 1 : -1);
        }
    }
    else if (kstrcmp(argv[0], "ps") == 0) {
        struct ps_row { int pid; int ppid; int state; char name[32]; };
        /* Heap snapshot like schedtop_report: 64 rows are 3 KB and must
         * not live in this frame (stack discipline, CLAUDE.md). */
        struct ps_row *snap = (struct ps_row *)kmalloc(sizeof(struct ps_row) * MAX_PROCS);
        int i, n = 0;
        if (!snap) { kprintf("ps: out of memory\n"); return; }
        spin_lock(&sched_lock);
        for (i = 0; i < MAX_PROCS && n < MAX_PROCS; i++) {
            int k;
            if (procs[i].state == PROC_FREE)
                continue;
            snap[n].pid = procs[i].pid;
            snap[n].ppid = procs[i].parent_pid;
            snap[n].state = procs[i].state;
            for (k = 0; k < 31 && procs[i].name[k]; k++)
                snap[n].name[k] = procs[i].name[k];
            snap[n].name[k] = 0;
            n++;
        }
        spin_unlock(&sched_lock);
        kprintf("  pid  ppid state name\n");
        for (i = 0; i < n; i++)
            kprintf("  %-4d %-4d %-5s %s\n", snap[i].pid,
                    snap[i].ppid,
                    shell_proc_state(snap[i].state), snap[i].name);
        if (!n) vga_puts("  (no processes)\n");
        kfree(snap);
    }
    /* `panic`: paint the kernel panic screen with live registers and a
     * frame-pointer backtrace, then return (demo mode, no halt). Real
     * faults halt through the same screen from the fault handler. */
    else if (kstrcmp(argv[0], "panic") == 0) {
        unsigned long rip = 0, rsp = 0, rbp = 0;
        __asm__ volatile("leaq 0(%%rip), %0" : "=r"(rip));
        __asm__ volatile("mov %%rsp, %0" : "=r"(rsp));
        __asm__ volatile("mov %%rbp, %0" : "=r"(rbp));
        panic_screen(0x100, 0, rip, rsp, rbp, 0);
    }
    else if (kstrcmp(argv[0], "smp") == 0) {
        int c;
        kprintf("smp: %d CPU(s)\n", cpu_count);
        for (c = 0; c < cpu_count && c < MAX_CPUS; c++) {
            unsigned long hits = 0;
            unsigned long steals = 0;
            unsigned long drops = 0;
            rq_stats(c, &hits, &steals, &drops);
            kprintf("  cpu%d lapic=%d %s cur=%d dispatched=%lu polls=%lu rq_hits=%lu rq_steals=%lu rq_drops=%lu\n",
                    cpus[c].cpu_id, cpus[c].lapic_id,
                    cpus[c].is_bsp ? "BSP" : "AP ",
                    cpus[c].cur_pid, smp_dispatches[c], smp_idle_polls[c],
                    hits, steals, drops);
        }
        kprintf("  bad_gs=%u\n", smp_dbg_bad_gs);
        kprintf("  lapic_cal=%u %s\n", lapic_cal_10ms,
                lapic_cal_valid ? "measured" : "fallback");
    }
    else if (kstrcmp(argv[0], "nice") == 0) {
        if (argc > 1) {
            long nv;
            int n;
            if (!shell_parse_long(argv[1], &nv)) {
                kprintf("nice: bad value '%s'\n", argv[1]);
            } else {
                n = (int)nv;
                if (n < -20) n = -20;
                if (n > 19) n = 19;
                procs[current_pid < 0 ? 0 : current_pid].nice = n;
            }
        }
        kprintf("nice: %d", procs[current_pid < 0 ? 0 : current_pid].nice);
    }
    else if (kstrcmp(argv[0], "seccomp") == 0) {
        int pid = current_pid < 0 ? 0 : current_pid;
        long nv;
        if (argc > 2 && kstrcmp(argv[1], "deny") == 0) {
            if (!shell_parse_long(argv[2], &nv) || nv < 0) {
                kprintf("seccomp: bad number '%s'\n", argv[2]);
                return;
            }
            int n = (int)nv;
            kprintf("seccomp: deny %d -> %d", n, seccomp_deny_one(pid, n));
        } else if (argc > 2 && kstrcmp(argv[1], "allow") == 0) {
            if (!shell_parse_long(argv[2], &nv) || nv < 0) {
                kprintf("seccomp: bad number '%s'\n", argv[2]);
                return;
            }
            int n = (int)nv;
            kprintf("seccomp: allow %d -> %d", n, seccomp_allow_one(pid, n));
        } else {
            kprintf("seccomp: mask=%lx", (unsigned long)procs[pid].seccomp_deny);
        }
    }
    else if (kstrcmp(argv[0], "rlimit") == 0) {
        int pid = current_pid < 0 ? 0 : current_pid;
        proc_t *rp = &procs[pid];
        if (argc > 2) {
            long lv;
            unsigned long v;
            if (!shell_parse_long(argv[2], &lv) || lv < 0) {
                vga_puts("usage: rlimit [as|cpu|nofile] [value]\n");
                return;
            }
            v = (unsigned long)lv;
            if (kstrcmp(argv[1], "as") == 0) rp->rl_as_max = v;
            else if (kstrcmp(argv[1], "cpu") == 0) {
                rp->rl_cpu_max = v;
                rp->cpu_ticks = 0;
                rp->cpu_kill_pending = 0;
            }
            else if (kstrcmp(argv[1], "nofile") == 0) {
                if (v <= (unsigned long)KFD_MAX) rp->rl_nofile_max = v;
            }
            else { vga_puts("usage: rlimit [as|cpu|nofile] [value]\n"); return; }
        }
        kprintf("rlimit: as=%lu cpu=%lu ticks=%lu nofile=%lu open=%d\n",
                rp->rl_as_max, rp->rl_cpu_max, rp->cpu_ticks,
                rp->rl_nofile_max, rp->open_files);
    }
    else if (kstrcmp(argv[0], "echo") == 0) {
        int i;
        for (i = 1; i < argc; i++) {
            if (i > 1) vga_putc(' ');
            vga_puts(argv[i]);
        }
        vga_putc('\n');
    }
    else if (kstrcmp(argv[0], "vol") == 0) {
        if (argc > 1) {
            unsigned v;
            if (!shell_parse_vol(argv[1], &v)) { vga_puts("usage: vol [0-100]\n"); return; }
            pcspk_set_volume(v);
        }
        kprintf("volume: %u%%\n", pcspk_get_volume());
    }
    else if (kstrcmp(argv[0], "date") == 0) {
        int h, m, s;
        if (rtc_read_tod(&h, &m, &s))
            kprintf("%02d:%02d:%02d\n", h, m, s);
        else
            vga_puts("date: clock unavailable\n");
    }
    else if (kstrcmp(argv[0], "clock") == 0) {
        /* Phase 0.2/0.3 BDD hook: two wall-clock reads and two monotonic
         * reads; neither may step backwards, and the wall fraction must
         * stay inside the second. A regression to second resolution or
         * to the old uptime-as-epoch prints visibly wrong values here. */
        unsigned long w1 = wall_us_now(), m1 = ktime_us();
        unsigned long w2 = wall_us_now(), m2 = ktime_us();
        kprintf("clock: wall=%lu.%06lu mono=%lu us\n",
                w1 / 1000000UL, w1 % 1000000UL, m1);
        kprintf("clock: wall=%lu.%06lu mono=%lu us %s\n",
                w2 / 1000000UL, w2 % 1000000UL, m2,
                (w2 >= w1 && m2 >= m1) ? "monotonic" : "BACKWARDS");
    }
    else if (kstrcmp(argv[0], "kbd") == 0) {
        if (argc > 1) {
            if (kstrcmp(argv[1], "en") == 0)
                kbd_set_layout(KBD_LAYOUT_EN);
            else if (kstrcmp(argv[1], "es") == 0)
                kbd_set_layout(KBD_LAYOUT_ES);
            else if (kstrcmp(argv[1], "toggle") == 0)
                kbd_toggle_layout();
            else { vga_puts("usage: kbd [en|es]\n"); return; }
        }
        kprintf("kbd: %s\n", kbd_get_layout() == KBD_LAYOUT_ES ? "es" : "en");
    }
    else if (kstrcmp(argv[0], "kstack") == 0) {
        kstack_report();
    }
    else if (kstrcmp(argv[0], "sb16") == 0) {
        sb16_counters_t c;
        pcm2_counters_t p2;
        sb16_counters(&c);
        pcm2_counters(&p2);
        kprintf("sb16: present=%d mode=%d ring=%u/%u streams=%d\n",
                sb16_present(), sb16_mode_active(), sb16_ring_free(),
                (unsigned)SB16_RING_CAP, sb16_stream_count());
        kprintf("sb16: arms irq=%lu poll=%lu submits=%lu drops=%lu\n",
                c.irq_arms, c.poll_arms, c.submits, c.drops);
        kprintf("sb16: stalls=%lu pump_fills=%lu mixes=%lu\n",
                c.stalls, c.pump_fills, c.mixes);
        kprintf("pcm2: active=%d irqs=%lu polls=%lu spurious=%lu\n",
                pcm2_active(), p2.irqs, p2.polls, p2.spurious);
        kprintf("pcm2: bytes=%lu underruns=%lu drops=%lu wakes=%lu\n",
                p2.bytes, p2.underruns, p2.drops, p2.wakes);
    }
    else if (kstrcmp(argv[0], "gfx") == 0) {
        shell_cmd_gfx(argc, argv);
    }
    else if (kstrcmp(argv[0], "fx") == 0) {
        if (argc > 1) {
            if (kstrcmp(argv[1], "on") == 0)
                vga_fx_set_enabled(1);
            else if (kstrcmp(argv[1], "off") == 0)
                vga_fx_set_enabled(0);
            else { vga_puts("usage: fx [on|off]\n"); return; }
        }
        kprintf("fx: %s melts=%lu\n", vga_fx_enabled() ? "on" : "off", fx_melts_completed);
    }
    else if (kstrcmp(argv[0], "wm") == 0) {
        shell_cmd_wm(argc, argv);
    }
    else if (kstrcmp(argv[0], "hash") == 0) {
        shell_cmd_hash(argc, argv);
    }
    else if (kstrcmp(argv[0], "mem") == 0) {
        (void)argc; (void)argv;
        shell_cmd_mem();
    }
    else if (kstrcmp(argv[0], "minifetch") == 0) {
        (void)argc; (void)argv;
        shell_cmd_minifetch();
    }
    else if (kstrcmp(argv[0], "unzip") == 0) {
        shell_cmd_unzip(argc, argv);
    }
    else if (kstrcmp(argv[0], "zip") == 0) {
        shell_cmd_zip(argc, argv);
    }
    else if (kstrcmp(argv[0], "load") == 0) {
        if (argc < 2) { vga_puts("usage: load <file>\n"); return; }
        char progname[32];
        void *entry = 0;
        int kind = shell_load(argv[1], progname, &entry);
        if (kind == 0) { kprintf("load: %s: not an ELF or load failed\n", argv[1]); return; }
        if (kind == 1) kprintf("Loaded relocatable '%s' at %p\n", progname, entry);
        else           kprintf("Loaded Linux ELF '%s' entry %p  (run %s)\n",
                               progname, entry, progname);
    }
    else if (kstrcmp(argv[0], "run") == 0) {
        if (argc < 2) { vga_puts("usage: run <program|file> [args...] [&]\n"); return; }
        if (kstrcmp(argv[argc - 1], "&") == 0) {
            argc--;
            if (argc < 2) { vga_puts("usage: run <program|file> [args...] [&]\n"); return; }
            shell_run_bg(argv[1], argc - 1, argv + 1);
            return;
        }
        int ret = shell_run_any(argv[1], argc - 1, argv + 1);
        if (ret < 0) shell_report("run: not found: ", argv[1]);
        else shell_report_exit(ret);
    }
    else if (kstrcmp(argv[0], "mrun") == 0) {
        shell_cmd_mrun(argc, argv);
    }
    else if (kstrcmp(argv[0], "desktop") == 0) {
        shell_cmd_desktop(argc, argv);
    }
    else if (kstrcmp(argv[0], "jobs") == 0) {
        shell_cmd_jobs();
    }
    else if (kstrcmp(argv[0], "wait") == 0) {
        shell_cmd_wait(argc, argv);
    }
    else if (kstrcmp(argv[0], "kill") == 0) {
        shell_cmd_kill(argc, argv);
    }
    else if (kstrcmp(argv[0], "sleep") == 0) {
        /* `sleep <secs>`: yield until the wall clock advances, so a
         * background job (a booting game, a finishing fetch) can be
         * awaited before the next command observes it. Ctrl+C aborts. */
        long secs, end;
        long sv;
        if (argc < 2) { vga_puts("usage: sleep <secs>\n"); return; }
        if (!shell_parse_long(argv[1], &sv)) {
            vga_puts("usage: sleep <secs>\n");
            return;
        }
        secs = sv;
        if (secs < 0) secs = 0;
        if (secs > 3600) secs = 3600;
        end = (long)ktime_ms() + secs * 1000;
        while ((long)ktime_ms() < end) {
            if (console_peek() == 0x03) { console_getc(); kprintf("^C\n"); return; }
            yield();
        }
    }
    else if (kstrcmp(argv[0], "sh") == 0) {
        if (argc < 2) { vga_puts("usage: sh <script.sh>\n"); return; }
        shell_cmd_sh(argc, argv);
    }
    else {
        int ret = shell_run_any(argv[0], argc, argv);
        if (ret < 0) shell_report("command not found: ", argv[0]);
        else shell_report_exit(ret);
    }
}
#pragma GCC diagnostic pop

/* ---- Pipelines (`left | right [| ...]`) ----
 *
 * Sequential capture model for a single-threaded shell: every stage runs
 * to completion, its stdout is captured, and the capture becomes the
 * next stage's stdin. Two capture paths run in parallel because the two
 * program kinds write through different doors: builtins and ET_REL
 * children write vga_putc (caught by redirect_begin/take), ET_EXEC
 * children write sys_write fd 1 (caught by a kfd_table[1] pipe
 * override). Two stdin doors match: console_getc (builtins, ET_REL,
 * fed by console_stdin_push) and sys_read fd 0 (ET_EXEC, fed by a
 * kfd_table[0] pipe override). Exactly one door carries bytes per
 * stage; both are drained and concatenated, so no output is ever lost.
 *
 * Merged streams: MiniOS has one console stream, so stderr flows into
 * the pipe exactly like stdout (`2>` is an alias of `>`).
 * Per-stage `exit code:` lines report to the console, never into the
 * pipe (shell_report suspends the capture), so `run x | cat` shows the
 * code beside the piped bytes. Tracing pollutes pipelines the same
 * way: `trace on` kprintf lines land in the capture.
 * Bounds: each hop is capped at 16 MB (redirect_take plus the pipe
 * drain); past it the hop is dropped with a diagnostic, never
 * truncated. A stage that reads stdin with no pipe coming in reads the
 * live console exactly as without a pipe. */

#define PIPE_HOP_MAX (16UL * 1024 * 1024)

static int shell_is_pipe_tok(const char *a) {
    return a[0] == '|' && a[1] == 0;
}

/* Drain a closed-writer pipe read end into a heap buffer. Returns the
 * buffer (caller frees) with its length, or 0 with len 0 on empty/OOM.
 * Bounded by PIPE_HOP_MAX, fail-closed past it. */
static char *shell_drain_pipe(KFILE *r, unsigned long *len_out) {
    unsigned long len = 0u, cap = 4096u;
    char *out;
    *len_out = 0u;
    if (!r) return 0;
    out = kmalloc(cap);
    if (!out) return 0;
    for (;;) {
        unsigned long got;
        if (len == cap) {
            char *grown;
            if (cap >= PIPE_HOP_MAX) { kfree(out); return 0; }
            cap *= 2u;
            if (cap > PIPE_HOP_MAX) cap = PIPE_HOP_MAX;
            grown = krealloc(out, cap);
            if (!grown) { kfree(out); return 0; }
            out = grown;
        }
        got = kfread(out + len, 1, cap - len, r);
        if (got == 0) break;
        len += got;
    }
    *len_out = len;
    if (len == 0) { kfree(out); return 0; }
    return out;
}

/* Run one pipeline stage with stdin/out doors installed. input may be
 * 0 (first stage reads the live console). Returns the stage output
 * (caller frees) with its length; on any setup failure prints a
 * diagnostic and returns 0 with len 0. not_last selects the stdout
 * pipe override for ET_EXEC children. */
static char *shell_run_stage(char **sargv, int sargc,
        const char *input, unsigned long input_len,
        int not_last, unsigned long *len_out) {
    KFILE *rin = 0, *win = 0, *rout = 0, *wout = 0;
    KFILE *old0 = 0, *old1 = 0;
    char *taken = 0, *drained = 0, *out = 0;
    unsigned long taken_len = 0u, drained_len = 0u, total = 0u, i;
    *len_out = 0u;
    if (input && input_len > 0u) {
        /* ET_EXEC door: pipe pair, input written, writer closed (EOF
         * after drain), read end on fd 0. */
        if (kpipe_pair(&rin, &win) != 0) {
            vga_puts("pipe: out of memory\n");
            return 0;
        }
        if (kfwrite(input, 1, input_len, win) != input_len) {
            kfd_put(win); kfd_put(rin);
            vga_puts("pipe: input too large\n");
            return 0;
        }
        kfclose(win);
        win = 0;
        old0 = kfd_override(0, rin);
        /* Builtin/ET_REL door: same bytes through the console reader. */
        if (!console_stdin_push(input, input_len)) {
            kfd_override(0, old0);
            kfclose(rin);
            vga_puts("pipe: out of memory\n");
            return 0;
        }
    }
    if (not_last) {
        if (kpipe_pair(&rout, &wout) != 0) {
            if (rin) { kfd_override(0, old0); kfclose(rin); }
            console_stdin_clear();
            vga_puts("pipe: out of memory\n");
            return 0;
        }
        old1 = kfd_override(1, wout);
    }
    if (!redirect_begin()) {
        if (rin) { kfd_override(0, old0); kfclose(rin); }
        if (rout) { kfd_override(1, old1); kfclose(rout); kfclose(wout); }
        console_stdin_clear();
        vga_puts("pipe: out of memory\n");
        return 0;
    }
    shell_exec_builtin(sargc, sargv);
    if (rin) { kfd_override(0, old0); kfclose(rin); }
    if (rout) {
        kfd_override(1, old1);
        kfclose(wout);
        drained = shell_drain_pipe(rout, &drained_len);
        kfclose(rout);
        if (drained_len >= PIPE_HOP_MAX && !drained) {
            console_stdin_clear();
            redirect_take(0);
            vga_puts("pipe: stage output too large\n");
            return 0;
        }
    }
    console_stdin_clear();
    taken = redirect_take(&taken_len);
    total = drained_len + taken_len;
    if (total == 0u) return 0;
    if (total > PIPE_HOP_MAX) {
        if (taken) kfree(taken);
        if (drained) kfree(drained);
        vga_puts("pipe: stage output too large\n");
        return 0;
    }
    out = kmalloc(total + 1);
    if (!out) {
        if (taken) kfree(taken);
        if (drained) kfree(drained);
        vga_puts("pipe: out of memory\n");
        return 0;
    }
    for (i = 0u; i < drained_len; i++) out[i] = drained[i];
    for (i = 0u; i < taken_len; i++) out[drained_len + i] = taken[i];
    out[total] = 0;
    if (taken) kfree(taken);
    if (drained) kfree(drained);
    *len_out = total;
    return out;
}

/* Run argv as a pipeline when it holds `|` tokens, else return 0 and
 * leave everything (including argv) untouched for the normal dispatch.
 * A malformed pipeline prints a diagnostic and returns 1 (handled).
 * The last stage prints to the console, or commits to redir_path when
 * redirected (the `> file` / `2> file` tail was already split off by
 * shell_take_redirect before this runs). */
static int shell_run_pipeline(char **argv, int argc,
        const char *redir_path, int redir_append, int redirected) {
    int i, nstages = 1, s;
    char *input = 0;
    unsigned long input_len = 0u;
    for (i = 0; i < argc; i++)
        if (shell_is_pipe_tok(argv[i])) nstages++;
    if (nstages == 1) return 0;
    s = 0;
    for (i = 0; i <= argc; i++) {
        if (i == argc || shell_is_pipe_tok(argv[i])) {
            char **sargv = argv + s;
            int sargc = i - s;
            int last = (i == argc);
            char *out = 0;
            unsigned long out_len = 0u;
            if (sargc == 0) {
                if (input) kfree(input);
                vga_puts("syntax: | needs a command\n");
                return 1;
            }
            argv[i] = 0;
            out = shell_run_stage(sargv, sargc, input, input_len,
                    !last, &out_len);
            if (input) { kfree(input); input = 0; input_len = 0u; }
            if (!last) {
                input = out;
                input_len = out_len;
                if (!input) { input_len = 0u; }
            } else {
                if (redirected) {
                    /* Commit the vga_putc capture to the file, then
                     * append the ET_EXEC pipe half: redirect_take
                     * already ran inside the stage, so re-emit both
                     * halves through a plain file write. */
                    KFILE *f = kfopen(redir_path, redir_append ? "a" : "w");
                    if (!f) {
                        if (out) kfree(out);
                        kprintf("redirect: cannot write %s\n", redir_path);
                        return 1;
                    }
                    if (out && out_len > 0u &&
                            kfwrite(out, 1, out_len, f) != out_len) {
                        kfclose(f);
                        kfree(out);
                        kprintf("redirect: cannot write %s\n", redir_path);
                        return 1;
                    }
                    kfclose(f);
                    if (out) kfree(out);
                } else if (out && out_len > 0u) {
                    unsigned long k;
                    for (k = 0u; k < out_len; k++) vga_putc(out[k]);
                    kfree(out);
                }
            }
            s = i + 1;
        }
    }
    return 1;
}

/* ---- shell script runner ----
 *
 * Reads a .sh file line by line and executes each non-empty, non-comment
 * line through the normal shell dispatch (builtins, programs, redirects).
 * Lines starting with '#' are comments.  No variables, no control flow --
 * just sequential commands, easy for a non-programmer to write. */

int shell_cmd_sh(int argc, char **argv)
{
    if (argc < 2) { vga_puts("usage: sh <script.sh>\n"); return 1; }
    KFILE *f = kfopen(argv[1], "r");
    if (!f) {
        kprintf("sh: %s: cannot open\n", argv[1]);
        return 1;
    }

    char line[CMD_BUF_SZ];
    int line_no = 0;

    while (kfgets(line, sizeof(line), f)) {
        line_no++;

        /* strip trailing newline */
        int len = kstrlen(line);
        while (len > 0 && (line[len-1] == '\n' || line[len-1] == '\r'))
            line[--len] = 0;

        /* skip blank lines and comments */
        if (len == 0 || line[0] == '#') continue;

        /* copy line because shell_parse is destructive */
        char buf[CMD_BUF_SZ];
        kmemcpy(buf, line, len + 1);

        char *parse_argv[MAX_ARGS + 1];
        int  parse_argc = shell_parse(buf, parse_argv, MAX_ARGS);
        if (parse_argc == 0) continue;

        /* handle redirects (same as shell_run) */
        char *redir_path   = 0;
        int   redir_append = 0;
        int redir = shell_take_redirect(&parse_argc, parse_argv,
                                        &redir_path, &redir_append);
        if (redir < 0) {
            kprintf("sh: line %d: syntax error near redirect\n", line_no);
            continue;
        }
        if (parse_argc == 0) {
            kprintf("sh: line %d: syntax error: command expected\n", line_no);
            continue;
        }

        if (shell_run_pipeline(parse_argv, parse_argc,
                    redir_path, redir_append, redir))
            continue;
        if (redir && !redirect_begin()) {
            kprintf("sh: line %d: redirect out of memory\n", line_no);
            continue;
        }
        shell_exec_builtin(parse_argc, parse_argv);
        if (redir && redirect_commit(redir_path, redir_append) != 0)
            kprintf("sh: line %d: cannot write %s\n", line_no, redir_path);
    }

    kfclose(f);
    return 0;
}
