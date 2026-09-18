/** Docstring: host test for the file browser assoc contract (make test-file).
 *
 * Mirror pin for progs/file/file.c: extension lowercasing, assoc line
 * validation (traversal rejected, shell/internal//path programs only),
 * dispatch kinds and the entry-icon classifier (folder/files/image/
 * object). Vectors here match file --selftest one to one; a drift in
 * either copy fails visibly.
 */

#include <stdio.h>
#include <string.h>
#include "progs/file/file_assoc.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

#define T_EXT_MAX 8
#define T_PROG_MAX 32

static void t_ext_of(const char *fname, char *dst, unsigned cap) {
    unsigned n = 0;
    unsigned dot = 0;
    unsigned k = 0;
    unsigned found = 0;
    while (fname[n] && n < 64) n++;
    for (k = 0; k < n; k++)
        if (fname[k] == '.') { dot = k; found = 1; }
    if (!found || dot + 1 >= n) { dst[0] = 0; return; }
    {
        unsigned m = 0;
        for (k = dot + 1; k < n && m + 1 < cap && m <= T_EXT_MAX; k++) {
            char c = fname[k];
            if (c >= 'A' && c <= 'Z') c = (char)(c + 32);
            dst[m++] = c;
        }
        dst[m] = 0;
    }
}

static int t_assoc_line(const char *line, char *ext, char *prog) {
    unsigned k = 0;
    unsigned m = 0;
    if (!line[0] || line[0] == '#') return -1;
    while (line[k] && line[k] != '|' && m < T_EXT_MAX) {
        char c = line[k];
        if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))) return -1;
        ext[m++] = c;
        k++;
    }
    if (!line[k] || line[k] != '|' || m == 0) return -1;
    k++;
    {
        unsigned p = 0;
        while (line[p + k] && line[p + k] != '\n' && line[p + k] != '\r' &&
               p < T_PROG_MAX) {
            if (line[p + k] == '|') return -1;
            prog[p] = line[p + k];
            p++;
        }
        if (line[p + k] && line[p + k] != '\n' && line[p + k] != '\r') return -1;
        while (p > 0 && (prog[p - 1] == ' ' || prog[p - 1] == '\t')) p--;
        prog[p] = 0;
    }
    ext[m] = 0;
    if (!prog[0]) return -1;
    if (strcmp(prog, "shell") != 0 && strcmp(prog, "internal") != 0 &&
        prog[0] != '/')
        return -1;
    return 0;
}

/** Mirror of file_icon_kind in progs/file/file.c (0 folder, 1 files,
 * 2 image, 3 object). */
static int t_icon_kind(const char *fname, int isdir) {
    char ext[T_EXT_MAX + 1];
    if (isdir) return 0;
    t_ext_of(fname, ext, sizeof(ext));
    if (strcmp(ext, "png") == 0) return 2;
    if (strcmp(ext, "o") == 0 || strcmp(ext, "elf") == 0 ||
        strcmp(ext, "cvm") == 0)
        return 3;
    return 1;
}

/** Mirror of the file icon size toggle (16 small default, 32 big). */
#define T_ICON_SMALL 16
#define T_ICON_BIG 32
static int t_icon_big;
static int t_icon_sz(void) {
    return t_icon_big ? T_ICON_BIG : T_ICON_SMALL;
}

int main(void) {
    char ext[T_EXT_MAX + 1];
    char prog[T_PROG_MAX + 1];

    t_ext_of("hello.c", ext, sizeof(ext));
    CHECK(strcmp(ext, "c") == 0, "ext of hello.c");
    t_ext_of("A.PNG", ext, sizeof(ext));
    CHECK(strcmp(ext, "png") == 0, "ext lowercases");
    t_ext_of("noext", ext, sizeof(ext));
    CHECK(ext[0] == 0, "empty ext when none");
    t_ext_of("a.", ext, sizeof(ext));
    CHECK(ext[0] == 0, "empty ext on trailing dot");

    CHECK(t_assoc_line("c|/vedit", ext, prog) == 0, "plain assoc line");
    CHECK(strcmp(ext, "c") == 0, "assoc ext parsed");
    CHECK(strcmp(prog, "/vedit") == 0, "assoc prog parsed");
    CHECK(t_assoc_line("elf|shell", ext, prog) == 0, "shell prog");
    CHECK(t_assoc_line("png|internal", ext, prog) == 0, "internal prog");
    CHECK(t_assoc_line("# comment", ext, prog) != 0, "comment skipped");
    CHECK(t_assoc_line("../x|/vedit", ext, prog) != 0, "traversal rejected");
    CHECK(t_assoc_line("C|/vedit", ext, prog) != 0, "uppercase ext rejected");
    CHECK(t_assoc_line("c|", ext, prog) != 0, "empty prog rejected");
    CHECK(t_assoc_line("c|vedit", ext, prog) != 0, "relative prog rejected");
    CHECK(t_assoc_line("c|/vedit|extra", ext, prog) != 0, "pipe in prog rejected");

    CHECK(t_icon_kind("sub/", 1) == 0, "dir is folder");
    CHECK(t_icon_kind("a.c", 0) == 1, "c is files");
    CHECK(t_icon_kind("a.h", 0) == 1, "h is files");
    CHECK(t_icon_kind("a.lisp", 0) == 1, "lisp is files");
    CHECK(t_icon_kind("a.lua", 0) == 1, "lua is files");
    CHECK(t_icon_kind("a.py", 0) == 1, "py is files");
    CHECK(t_icon_kind("a.txt", 0) == 1, "txt is files");
    CHECK(t_icon_kind("a.s", 0) == 1, "s is files");
    CHECK(t_icon_kind("A.PNG", 0) == 2, "png is image");
    CHECK(t_icon_kind("a.o", 0) == 3, "o is object");
    CHECK(t_icon_kind("a.elf", 0) == 3, "elf is object");
    CHECK(t_icon_kind("a.cvm", 0) == 3, "cvm is object");
    CHECK(t_icon_kind("a.zip", 0) == 1, "unknown falls back to files");
    CHECK(t_icon_kind("noext", 0) == 1, "no ext falls back to files");

    CHECK(t_icon_sz() == 16, "default icon size small");
    t_icon_big = !t_icon_big;
    CHECK(t_icon_sz() == 32, "toggled icon size big");
    t_icon_big = !t_icon_big;
    CHECK(t_icon_sz() == 16, "toggled icon size small again");

    {
        struct fassoc_table t;
        char ebuf[16];
        char pbuf[40];
        unsigned k = 0;
        memset(&t, 0, sizeof(t));
        CHECK(fassoc_count(&t) == 0, "empty table count zero");
        CHECK(strcmp(fassoc_lookup(&t, "c"), "") == 0, "empty lookup misses");
        for (k = 0; k < 64; k++) {
            snprintf(ebuf, sizeof(ebuf), "e%u", k);
            snprintf(pbuf, sizeof(pbuf), "/prog%u", k);
            CHECK(fassoc_push(&t, ebuf, pbuf) == 0, "dynamic push grows past 32");
        }
        CHECK(fassoc_count(&t) == 64, "64 entries stored, old cap gone");
        CHECK(strcmp(fassoc_lookup(&t, "e0"), "/prog0") == 0, "first lookup kept");
        CHECK(strcmp(fassoc_lookup(&t, "e63"), "/prog63") == 0, "last lookup kept");
        CHECK(strcmp(fassoc_lookup(&t, "nope"), "") == 0, "miss stays empty");
        CHECK(fassoc_push(&t, "BAD", "/vedit") != 0, "uppercase ext rejected");
        CHECK(fassoc_push(&t, "../x", "/vedit") != 0, "traversal ext rejected");
        CHECK(fassoc_push(&t, "ok", "vedit") != 0, "relative prog rejected");
        CHECK(fassoc_push(&t, "ok", "") != 0, "empty prog rejected");
        CHECK(fassoc_count(&t) == 64, "rejected pushes mutate nothing");
        fassoc_clear(&t);
        CHECK(fassoc_count(&t) == 0, "clear empties count");
        CHECK(fassoc_push(&t, "c", "/vedit") == 0, "reuse after clear");
        fassoc_free(&t);
        CHECK(fassoc_count(&t) == 0, "free resets count");
    }

    if (failures == 0)
        printf("file-assoc: ok\n");
    return failures != 0;
}
