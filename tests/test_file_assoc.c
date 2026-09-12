/** Docstring: host test for the file browser assoc contract (make test-file).
 *
 * Mirror pin for progs/file/file.c: extension lowercasing, assoc line
 * validation (traversal rejected, shell/internal//path programs only),
 * and dispatch kinds. Vectors here match file --selftest one to one;
 * a drift in either copy fails visibly.
 */

#include <stdio.h>
#include <string.h>

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

    if (failures == 0)
        printf("file-assoc: ok\n");
    return failures != 0;
}
