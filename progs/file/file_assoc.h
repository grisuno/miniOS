/** Docstring: dynamic association table for the MiniOS file browser.
 *
 * Ring-3 only contract replacing the former fixed file_table[32] that
 * silently dropped every association line past 32. The table grows on
 * demand with amortized constant time push, preserves existing entries
 * on allocation failure, and refuses entries past a hard bound so a
 * hostile /etc/association can never drive unbounded allocation.
 * Validation mirrors file_assoc_line: lowercase alnum extensions with
 * bounded length, programs are shell, internal, or absolute paths with
 * no pipe character. Lookup is a linear scan preserving file order so
 * the first match wins exactly as before.
 */

#ifndef MINIOS_FILE_ASSOC_H
#define MINIOS_FILE_ASSOC_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#ifndef FASSOC_EXT_MAX
#define FASSOC_EXT_MAX 8
#endif

#ifndef FASSOC_PROG_MAX
#define FASSOC_PROG_MAX 32
#endif

#ifndef FASSOC_INIT_CAP
#define FASSOC_INIT_CAP 32
#endif

#ifndef FASSOC_HARD_MAX
#define FASSOC_HARD_MAX 512
#endif

#ifndef FASSOC_GROW_NUM
#define FASSOC_GROW_NUM 2
#endif

#ifndef FASSOC_GROW_DEN
#define FASSOC_GROW_DEN 1
#endif

/** Docstring: one validated association entry, ext without dot. */
struct fassoc_entry {
    char ext[FASSOC_EXT_MAX + 1];
    char prog[FASSOC_PROG_MAX + 1];
};

/** Docstring: dynamic table state, zero init is valid. */
struct fassoc_table {
    struct fassoc_entry *p;
    size_t cnt;
    size_t cap;
};

/** Docstring: validate ext against the assoc line charset and bound. */
static int fassoc_ext_ok(const char *ext) {
    size_t n = 0;
    size_t k = 0;
    if (ext == NULL) return 0;
    while (ext[n] != 0) n++;
    if (n == 0 || n > (size_t)FASSOC_EXT_MAX) return 0;
    for (k = 0; k < n; k++) {
        char c = ext[k];
        if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))) return 0;
    }
    return 1;
}

/** Docstring: validate prog against shell, internal, or absolute path. */
static int fassoc_prog_ok(const char *prog) {
    size_t n = 0;
    size_t k = 0;
    if (prog == NULL) return 0;
    while (prog[n] != 0) n++;
    if (n == 0 || n > (size_t)FASSOC_PROG_MAX) return 0;
    if (strcmp(prog, "shell") == 0) return 1;
    if (strcmp(prog, "internal") == 0) return 1;
    if (prog[0] != '/') return 0;
    for (k = 0; k < n; k++) {
        if (prog[k] == '|') return 0;
    }
    return 1;
}

/** Docstring: reset table to empty without releasing capacity. */
static void fassoc_clear(struct fassoc_table *t) {
    if (t == NULL) return;
    t->cnt = 0;
}

/** Docstring: release backing store and reset to zero init state. */
static void fassoc_free(struct fassoc_table *t) {
    if (t == NULL) return;
    free(t->p);
    t->p = NULL;
    t->cnt = 0;
    t->cap = 0;
}

/** Docstring: ensure capacity for want entries, old data kept on failure. */
static int fassoc_reserve(struct fassoc_table *t, size_t want) {
    size_t ncap = 0;
    struct fassoc_entry *np = NULL;
    if (t == NULL) return -1;
    if (want > (size_t)FASSOC_HARD_MAX) return -1;
    if (t->cap >= want) return 0;
    ncap = t->cap > 0 ? t->cap : (size_t)FASSOC_INIT_CAP;
    while (ncap < want) {
        size_t nxt = ncap * (size_t)FASSOC_GROW_NUM / (size_t)FASSOC_GROW_DEN + 1;
        if (nxt <= ncap) return -1;
        if (nxt > (size_t)FASSOC_HARD_MAX) nxt = (size_t)FASSOC_HARD_MAX;
        ncap = nxt;
    }
    np = (struct fassoc_entry *)realloc(t->p, ncap * sizeof(*np));
    if (np == NULL) return -1;
    t->p = np;
    t->cap = ncap;
    return 0;
}

/** Docstring: append one validated entry, fail closed without mutation. */
static int fassoc_push(struct fassoc_table *t, const char *ext, const char *prog) {
    if (t == NULL) return -1;
    if (!fassoc_ext_ok(ext)) return -1;
    if (!fassoc_prog_ok(prog)) return -1;
    if (t->cnt >= (size_t)FASSOC_HARD_MAX) return -1;
    if (t->cnt >= t->cap) {
        if (fassoc_reserve(t, t->cnt + 1) != 0) return -1;
    }
    strcpy(t->p[t->cnt].ext, ext);
    strcpy(t->p[t->cnt].prog, prog);
    t->cnt++;
    return 0;
}

/** Docstring: program for ext in file order, empty string when unmapped. */
static const char *fassoc_lookup(const struct fassoc_table *t, const char *ext) {
    size_t k = 0;
    if (t == NULL || ext == NULL || ext[0] == 0) return "";
    for (k = 0; k < t->cnt; k++) {
        if (strcmp(t->p[k].ext, ext) == 0) return t->p[k].prog;
    }
    return "";
}

/** Docstring: logical entry count, zero for null table. */
static size_t fassoc_count(const struct fassoc_table *t) {
    if (t == NULL) return 0;
    return t->cnt;
}

#endif
