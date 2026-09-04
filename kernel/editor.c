#include "kernel.h"
#include "shell.h"
#include "editor.h"

/* ================================================================
 *  Built-in line editor (extracted from the shell)
 *
 *  A command-driven line editor over ramdisk/MiniFS files, modelled on
 *  a small `ed`/`ex` with a nano-style status: a `*` suffix marks a
 *  modified buffer and `!` marks a truncated one.  It keeps a current
 *  line for `g`/`n`/`b`/`.` navigation and `/` searching.  Text entry
 *  for `e`/`a`/`i` reuses the shell's arrow-key line reader, so editing
 *  a line has the same mid-line cursor behaviour as the prompt.
 *
 *  Invariants (covered by the mutation suite):
 *    1. a buffer that did not hold the whole file refuses to save;
 *    2. `q` refuses to discard unsaved changes, `q!` discards explicitly.
 * ================================================================ */

#define EDIT_MAX_LINES 512
#define EDIT_LINE_MAX  128
#define EDIT_FILE_MAX  (64UL * 1024)

typedef struct {
    char text[EDIT_LINE_MAX];
    int  used;
} EditLine;

typedef struct {
    EditLine *lines;
    int       count;
    int       cur;       /* current line index (0-based), -1 when none */
    char      fname[RAMDISK_FNAME_LEN];
    int       dirty;
    int       truncated;
} EditBuf;

static EditBuf *edit_alloc(const char *fname) {
    EditBuf *e = kmalloc(sizeof(EditBuf));
    if (!e) return 0;
    e->lines = kcalloc(EDIT_MAX_LINES, sizeof(EditLine));
    if (!e->lines) {
        kfree(e);
        return 0;
    }
    e->count     = 0;
    e->cur       = -1;
    e->dirty     = 0;
    e->truncated = 0;
    kstrncpy(e->fname, fname, RAMDISK_FNAME_LEN - 1);
    e->fname[RAMDISK_FNAME_LEN - 1] = 0;
    return e;
}

static void edit_free(EditBuf *e) {
    if (!e) return;
    if (e->lines) kfree(e->lines);
    kfree(e);
}

static int edit_load(EditBuf *e) {
    KFILE *f = kfopen(e->fname, "r");
    if (!f) return 0;
    if (f->rf->size > EDIT_FILE_MAX) {
        kfclose(f);
        return -1;
    }
    int idx = 0;
    int used = 0;
    while (1) {
        int c = kfgetc(f);
        if (c == EOF) break;
        if (idx >= EDIT_MAX_LINES) { e->truncated = 1; break; }
        if (c == '\n') {
            e->lines[idx].used = used;
            idx++;
            used = 0;
            continue;
        }
        if (c == '\r') continue;
        if (used < EDIT_LINE_MAX - 1) {
            e->lines[idx].text[used++] = (char)c;
        } else {
            e->truncated = 1;
        }
    }
    if (used > 0 && idx < EDIT_MAX_LINES) {
        e->lines[idx].used = used;
        idx++;
    }
    e->count = idx;
    if (e->count > 0) e->cur = 0;
    kfclose(f);
    return 1;
}

static int edit_save(EditBuf *e) {
    KFILE *f = kfopen(e->fname, "w");
    if (!f) return -1;
    int i;
    for (i = 0; i < e->count; i++) {
        if (e->lines[i].used > 0)
            kfwrite(e->lines[i].text, 1, (unsigned long)e->lines[i].used, f);
        if (i + 1 < e->count) kfputc('\n', f);
    }
    if (kfclose(f) != 0) return -1;
    e->dirty = 0;
    return 0;
}

static void edit_print(EditBuf *e, int idx) {
    if (idx < 0 || idx >= e->count) return;
    kprintf("%4d: ", idx + 1);
    int i;
    for (i = 0; i < e->lines[idx].used; i++) vga_putc(e->lines[idx].text[i]);
    vga_putc('\n');
}

/* List a (possibly empty) range [start, end], both 1-based inclusive.  A
 * single argument lists from that line; no argument lists everything. */
static void edit_list(EditBuf *e, int start, int end) {
    int i;
    if (e->count == 0) {
        vga_puts("(empty)\n");
        return;
    }
    if (start < 1) start = 1;
    if (end < start) end = e->count;
    if (end > e->count) end = e->count;
    for (i = start - 1; i < end; i++) edit_print(e, i);
}

static int edit_set_line(EditBuf *e, int idx, const char *text) {
    unsigned long n = kstrlen(text);
    if (n > EDIT_LINE_MAX - 1) n = EDIT_LINE_MAX - 1;
    kmemcpy(e->lines[idx].text, text, n);
    e->lines[idx].used = (int)n;
    e->dirty = 1;
    return 0;
}

static int edit_insert(EditBuf *e, int idx, const char *text) {
    if (e->count >= EDIT_MAX_LINES) return -1;
    if (idx < 0) idx = 0;
    if (idx > e->count) idx = e->count;
    kmemmove(&e->lines[idx + 1], &e->lines[idx],
             (unsigned long)(e->count - idx) * sizeof(EditLine));
    e->count++;
    return edit_set_line(e, idx, text);
}

static int edit_delete(EditBuf *e, int idx) {
    if (idx < 0 || idx >= e->count) return -1;
    kmemmove(&e->lines[idx], &e->lines[idx + 1],
             (unsigned long)(e->count - idx - 1) * sizeof(EditLine));
    e->count--;
    e->dirty = 1;
    if (e->cur >= e->count) e->cur = e->count ? e->count - 1 : -1;
    return 0;
}

/* Copy a line into a NUL-terminated scratch buffer (lines are otherwise
 * stored length-prefixed without a terminator). */
static void edit_line_cstr(EditLine *l, char *out) {
    kmemcpy(out, l->text, (unsigned long)l->used);
    out[l->used] = 0;
}

static void edit_search(EditBuf *e, const char *needle) {
    if (!needle || !needle[0]) {
        vga_puts("usage: / <text>\n");
        return;
    }
    char tmp[EDIT_LINE_MAX];
    int found = 0, i;
    for (i = 0; i < e->count; i++) {
        edit_line_cstr(&e->lines[i], tmp);
        if (kstrstr(tmp, needle)) {
            kprintf("%4d: %s\n", i + 1, tmp);
            found = 1;
        }
    }
    if (!found) kprintf("no match for \"%s\"\n", needle);
}

static void edit_status(EditBuf *e) {
    kprintf("%s: %d line%s", e->fname, e->count, e->count == 1 ? "" : "s");
    if (e->cur >= 0) kprintf(", current %d", e->cur + 1);
    if (e->dirty) vga_puts(", modified");
    if (e->truncated) vga_puts(", truncated");
    vga_putc('\n');
}

static void edit_usage(void) {
    vga_puts("  h help          l [a [b]] list (range)\n");
    vga_puts("  p N print       g N go to line\n");
    vga_puts("  n next          b previous      . current\n");
    vga_puts("  / text search   = status\n");
    vga_puts("  e N edit        a append        i N insert   d N delete\n");
    vga_puts("  w save          x save+quit     q quit       q! discard\n");
}

/* A buffer that did not hold the whole file must never be written back:
 * saving it would drop the part that was never loaded. */
static int edit_refuse_save(EditBuf *e) {
    if (!e->truncated) return 0;
    vga_puts("refusing to save: file did not fit in the buffer\n");
    return 1;
}

static int edit_arg_line(int argc, char **argv, EditBuf *e, int *out) {
    if (argc < 2) return -1;
    int n = (int)katol(argv[1]);
    if (n < 1 || n > e->count) return -1;
    *out = n - 1;
    return 0;
}

static void edit_loop(EditBuf *e) {
    char buf[CMD_BUF_SZ];
    vga_puts("edit: 'h' for help\n");
    while (1) {
        kprintf("edit%s%s> ", e->dirty ? " *" : "", e->truncated ? " !" : "");
        shell_readline_buf(buf, CMD_BUF_SZ);
        char *argv[MAX_ARGS + 1];
        int argc = shell_parse(buf, argv, MAX_ARGS);
        if (argc == 0) continue;

        if (kstrcmp(argv[0], "h") == 0) {
            edit_usage();
        } else if (kstrcmp(argv[0], "l") == 0) {
            int start = 1, end = e->count;
            if (argc >= 2) {
                start = (int)katol(argv[1]);
                end = start;
                if (argc >= 3) end = (int)katol(argv[2]);
            }
            edit_list(e, start, end);
        } else if (kstrcmp(argv[0], "p") == 0) {
            int idx;
            if (edit_arg_line(argc, argv, e, &idx) != 0) { vga_puts("no such line\n"); continue; }
            edit_print(e, idx);
        } else if (kstrcmp(argv[0], "g") == 0) {
            int idx;
            if (edit_arg_line(argc, argv, e, &idx) != 0) { vga_puts("no such line\n"); continue; }
            e->cur = idx;
            edit_print(e, idx);
        } else if (kstrcmp(argv[0], "n") == 0) {
            if (e->cur < 0 || e->cur + 1 >= e->count) { vga_puts("at end\n"); continue; }
            e->cur++;
            edit_print(e, e->cur);
        } else if (kstrcmp(argv[0], "b") == 0) {
            if (e->cur <= 0) { vga_puts("at start\n"); continue; }
            e->cur--;
            edit_print(e, e->cur);
        } else if (kstrcmp(argv[0], ".") == 0) {
            if (e->cur < 0) { vga_puts("no current line\n"); continue; }
            edit_print(e, e->cur);
        } else if (kstrcmp(argv[0], "/") == 0) {
            edit_search(e, argc >= 2 ? argv[1] : "");
        } else if (kstrcmp(argv[0], "=") == 0) {
            edit_status(e);
        } else if (kstrcmp(argv[0], "e") == 0) {
            int idx;
            if (edit_arg_line(argc, argv, e, &idx) != 0) { vga_puts("no such line\n"); continue; }
            char line[EDIT_LINE_MAX];
            shell_readline_buf(line, EDIT_LINE_MAX);
            edit_set_line(e, idx, line);
        } else if (kstrcmp(argv[0], "a") == 0) {
            char line[EDIT_LINE_MAX];
            shell_readline_buf(line, EDIT_LINE_MAX);
            if (edit_insert(e, e->count, line) != 0) vga_puts("buffer full\n");
        } else if (kstrcmp(argv[0], "i") == 0) {
            int n = argc >= 2 ? (int)katol(argv[1]) : e->count + 1;
            if (n < 1 || n > e->count + 1) { vga_puts("no such line\n"); continue; }
            char line[EDIT_LINE_MAX];
            shell_readline_buf(line, EDIT_LINE_MAX);
            if (edit_insert(e, n - 1, line) != 0) vga_puts("buffer full\n");
        } else if (kstrcmp(argv[0], "d") == 0) {
            int idx;
            if (edit_arg_line(argc, argv, e, &idx) != 0) { vga_puts("no such line\n"); continue; }
            if (edit_delete(e, idx) != 0) vga_puts("no such line\n");
        } else if (kstrcmp(argv[0], "w") == 0) {
            if (edit_refuse_save(e)) continue;
            if (edit_save(e) != 0) vga_puts("save failed\n");
            else kprintf("wrote %d line(s) to %s\n", e->count, e->fname);
        } else if (kstrcmp(argv[0], "x") == 0) {
            if (edit_refuse_save(e)) continue;
            if (edit_save(e) != 0) { vga_puts("save failed\n"); continue; }
            kprintf("wrote %d line(s) to %s\n", e->count, e->fname);
            return;
        } else if (kstrcmp(argv[0], "q") == 0) {
            if (e->dirty) {
                vga_puts("unsaved changes: 'w' to save, 'q!' to discard\n");
                continue;
            }
            return;
        } else if (kstrcmp(argv[0], "q!") == 0) {
            return;
        } else {
            vga_puts("unknown command\n");
            edit_usage();
        }
    }
}

void shell_cmd_edit(int argc, char **argv) {
    if (argc < 2) {
        vga_puts("usage: edit <file>\n");
        return;
    }
    char resolved[RAMDISK_FNAME_LEN];
    if (!fs_resolve(argv[1], resolved, sizeof(resolved))) {
        kprintf("edit: %s: cannot open\n", argv[1]);
        return;
    }
    if (fs_is_dir(resolved)) {
        kprintf("edit: %s: is a directory\n", argv[1]);
        return;
    }
    EditBuf *e = edit_alloc(argv[1]);
    if (!e) {
        vga_puts("edit: out of memory\n");
        return;
    }
    int rc = edit_load(e);
    if (rc < 0) {
        vga_puts("edit: file too large\n");
        edit_free(e);
        return;
    }
    if (rc == 0) {
        kprintf("edit: new file %s\n", argv[1]);
    }
    edit_loop(e);
    edit_free(e);
}