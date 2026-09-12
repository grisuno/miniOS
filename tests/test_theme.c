/** Docstring: host test for the shared Nuklear theme contract.
 *
 * Mirrors the line/name validation of progs/nuklear/nuklear_theme.c and
 * pins the shipped files under progs/etc/themes: every key known (via
 * the same NK_THEME_KEY_LIST, so the table cannot drift), every value
 * 0..255 and palette-exact, all 32 keys present exactly once per theme,
 * and current naming an existing theme.
 */

#include <stdio.h>
#include <string.h>
#include "../progs/nuklear/nuklear_theme.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

struct tslot {
    const char *key;
    int idx;
};

static const struct tslot tslots[] = {
#define X(k, i) {#k, i},
    NK_THEME_KEY_LIST
#undef X
};

static int t_name_ok(const char *name) {
    unsigned n = 0;
    if (!name || !name[0]) return 0;
    while (name[n] && n < NK_THEME_NAME_MAX) {
        char c = name[n];
        if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9'))) return 0;
        n++;
    }
    if (name[n] || n == 0) return 0;
    return 1;
}

static int t_parse_line(const char *line, int *idx, long v[3]) {
    char key[NK_THEME_KEY_MAX + 1];
    unsigned k = 0;
    unsigned i;
    int n = 0;
    while (line[k] == ' ' || line[k] == '\t') k++;
    if (!line[k] || line[k] == '#') return -1;
    while (line[k] && line[k] != ' ' && line[k] != '\t' &&
           (unsigned)n < sizeof(key) - 1) {
        key[n++] = line[k++];
    }
    if (line[k] && line[k] != ' ' && line[k] != '\t') return -1;
    key[n] = 0;
    if (n == 0) return -1;
    {
        long a, b, c;
        if (sscanf(line + k, "%ld %ld %ld", &a, &b, &c) != 3) return -1;
        v[0] = a; v[1] = b; v[2] = c;
    }
    for (i = 0; i < NK_THEME_KEY_COUNT; i++) {
        if (strcmp(tslots[i].key, key) == 0) {
            *idx = tslots[i].idx;
            return 0;
        }
    }
    return -1;
}

static int cube_exact(long v) {
    return v == 0 || v == 51 || v == 102 || v == 153 || v == 204 || v == 255;
}

static void check_theme_file(const char *path) {
    FILE *f = fopen(path, "r");
    char line[96];
    int seen[32];
    unsigned i;
    for (i = 0; i < 32; i++) seen[i] = 0;
    CHECK(f != 0, "theme file opens");
    if (!f) return;
    while (fgets(line, sizeof(line), f)) {
        int idx = -1;
        long v[3] = {0, 0, 0};
        unsigned k = 0;
        while (line[k] == ' ' || line[k] == '\t') k++;
        if (!line[k] || line[k] == '#') continue;
        CHECK(t_parse_line(line, &idx, v) == 0, "theme line parses");
        if (idx < 0) continue;
        CHECK(idx >= 0 && idx < 32, "theme key in range");
        CHECK(seen[idx] == 0, "theme key unique");
        seen[idx] = 1;
        CHECK(v[0] >= 0 && v[0] <= 255, "theme value clamped range");
        CHECK(v[1] >= 0 && v[1] <= 255, "theme value clamped range");
        CHECK(v[2] >= 0 && v[2] <= 255, "theme value clamped range");
        CHECK(cube_exact(v[0]) && cube_exact(v[1]) && cube_exact(v[2]),
              "shipped theme value palette-exact");
    }
    fclose(f);
    for (i = 0; i < 32; i++) CHECK(seen[i] == 1, "theme covers all 32 keys");
}

int main(void) {
    int idx = -1;
    long v[3] = {0, 0, 0};
    FILE *f;

    CHECK(NK_THEME_KEY_COUNT == 32, "32 theme keys");

    CHECK(t_name_ok("dark"), "plain name ok");
    CHECK(!t_name_ok(""), "empty name rejected");
    CHECK(!t_name_ok("../x"), "traversal rejected");
    CHECK(!t_name_ok("Dark"), "uppercase rejected");
    CHECK(!t_name_ok("a|b"), "pipe rejected");

    CHECK(t_parse_line("text 204 204 204", &idx, v) == 0, "plain line");
    CHECK(idx == 0 && v[0] == 204, "line values parsed");
    CHECK(t_parse_line("# comment", &idx, v) != 0, "comment skipped");
    CHECK(t_parse_line("nope 1 2 3", &idx, v) != 0, "unknown key rejected");
    CHECK(t_parse_line("text 1 2", &idx, v) != 0, "short line rejected");
    CHECK(t_parse_line("text a b c", &idx, v) != 0, "non-numeric rejected");

    check_theme_file("progs/etc/themes/dark");
    check_theme_file("progs/etc/themes/light");
    check_theme_file("progs/etc/themes/amber");
    check_theme_file("progs/etc/themes/forest");
    check_theme_file("progs/etc/themes/slate");

    f = fopen("progs/etc/themes/current", "r");
    CHECK(f != 0, "current opens");
    if (f) {
        char name[32] = {0};
        CHECK(fgets(name, sizeof(name), f) != 0, "current names a theme");
        {
            unsigned n = 0;
            while (name[n] && name[n] != '\n' && name[n] != '\r') n++;
            name[n] = 0;
        }
        CHECK(t_name_ok(name), "current name valid");
        {
            char path[64];
            FILE *tf;
            snprintf(path, sizeof(path), "progs/etc/themes/%s", name);
            tf = fopen(path, "r");
            CHECK(tf != 0, "current theme file exists");
            if (tf) fclose(tf);
        }
        fclose(f);
    }

    if (failures == 0)
        printf("theme: ok\n");
    return failures != 0;
}
