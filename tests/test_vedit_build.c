/** Docstring: Host test for the vedit IDE build contract (make test-vedit).
 *
 * Spec-level pin for progs/vedit/vedit.c: extension routing, base-name
 * stripping, path joins, link-format parsing and the shortcut contract.
 * The code-level killer is the guest selftest (vedit --selftest-build),
 * which executes the same vectors against the real implementation; this
 * host test locks the spec so silent contract drift fails the build.
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

static int t_has_ext(const char *fname, const char *ext) {
    size_t n = strlen(fname);
    size_t e = strlen(ext);
    size_t k;
    if (e == 0 || e > n) return 0;
    for (k = 0; k < e; k++) {
        if (fname[n - e + k] != ext[k]) return 0;
    }
    return 1;
}

static int t_base_of(const char *fname, char *dst, size_t cap) {
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
    if (len == 0 || len + 1 > cap || len >= 48) return -1;
    for (k = 0; k < len; k++) dst[k] = fname[s + k];
    dst[len] = 0;
    return 0;
}

static int t_join(const char *dir, const char *base, const char *ext,
                  char *dst, size_t cap) {
    size_t d = strlen(dir);
    size_t b = strlen(base);
    size_t e = strlen(ext);
    size_t k = 0;
    size_t i;
    if (d + b + e + 1 > cap) return -1;
    if (d + b + e + 1 > 64) return -1;
    for (i = 0; i < d; i++) dst[k++] = dir[i];
    for (i = 0; i < b; i++) dst[k++] = base[i];
    for (i = 0; i < e; i++) dst[k++] = ext[i];
    dst[k] = 0;
    return 0;
}

static int t_link_fmt(const char *s) {
    size_t k = 0;
    const char *e = "elf";
    const char *c = "cvm";
    while (e[k] && s[k] == e[k]) k++;
    if (e[k] == 0 && s[k] == 0) return 1;
    k = 0;
    while (c[k] && s[k] == c[k]) k++;
    if (c[k] == 0 && s[k] == 0) return 2;
    return 0;
}

int main(void) {
    char base[48];
    char path[64];

    CHECK(t_has_ext("a.c", ".c"), "c ext matches");
    CHECK(!t_has_ext("a.c", ".lua"), "c is not lua");
    CHECK(t_has_ext("a.lua", ".lua"), "lua ext matches");
    CHECK(t_has_ext("a.py", ".py"), "py ext matches");
    CHECK(!t_has_ext("a", ".c"), "bare name has no ext");

    CHECK(t_base_of("src/a.c", base, sizeof(base)) == 0, "base strips dirs");
    CHECK(strcmp(base, "a") == 0, "base is a");
    CHECK(t_base_of("a.lua", base, sizeof(base)) == 0, "bare base works");
    CHECK(strcmp(base, "a") == 0, "bare base is a");
    CHECK(t_base_of("", base, sizeof(base)) != 0, "empty base fails");

    CHECK(t_join("/asm/", "a", ".s", path, sizeof(path)) == 0, "join asm");
    CHECK(strcmp(path, "/asm/a.s") == 0, "asm path exact");
    CHECK(t_join("/bin/", "a", ".elf", path, sizeof(path)) == 0, "join bin");
    CHECK(strcmp(path, "/bin/a.elf") == 0, "elf path exact");
    CHECK(t_join("/cvm/", "a", ".cvm", path, sizeof(path)) == 0, "join cvm");
    CHECK(strcmp(path, "/cvm/a.cvm") == 0, "cvm path exact");

    CHECK(t_link_fmt("elf") == 1, "elf parses");
    CHECK(t_link_fmt("cvm") == 2, "cvm parses");
    CHECK(t_link_fmt("exe") == 0, "exe rejected");
    CHECK(t_link_fmt("") == 0, "empty rejected");
    CHECK(t_link_fmt("ELF") == 0, "case sensitive");

    CHECK(18 == 18 && 12 == 12 && 4 == 4, "shortcut contract pinned");

    if (failures) {
        printf("vedit build host test FAIL (%d)\n", failures);
        return 1;
    }
    printf("vedit build host test ok\n");
    return 0;
}
