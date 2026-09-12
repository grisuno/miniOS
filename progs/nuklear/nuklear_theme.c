/** Docstring: shared Nuklear theme loader, linked by every NK app.
 *
 * Every bound, path and default lives here; the key table comes from
 * NK_THEME_KEY_LIST in the header so no copy can drift. Files are
 * hostile data: unknown keys are skipped, out-of-range numbers clamp,
 * overlong lines and names fail closed, and the table always starts
 * from the compiled-in fallback before overlaying.
 */

#include <stdio.h>
#include <string.h>
#include "nuklear.h"
#include "nuklear_theme.h"

struct nk_theme_slot {
    const char *key;
    int idx;
};

static const struct nk_theme_slot nk_theme_slots[] = {
#define X(k, i) {#k, i},
    NK_THEME_KEY_LIST
#undef X
};

static const unsigned char nk_theme_fallback[NK_THEME_KEY_COUNT][3] = {
    {204, 204, 204}, {51, 51, 51}, {51, 102, 153}, {0, 0, 0},
    {102, 102, 102}, {153, 153, 153}, {51, 102, 153}, {102, 102, 102},
    {153, 153, 153}, {51, 102, 153}, {51, 102, 153}, {51, 102, 153},
    {102, 102, 102}, {204, 204, 204}, {255, 255, 255}, {51, 102, 153},
    {102, 102, 102}, {0, 0, 0}, {0, 204, 0}, {102, 102, 102},
    {51, 51, 51}, {51, 102, 153}, {204, 204, 0}, {102, 102, 102},
    {153, 153, 153}, {204, 204, 204}, {51, 102, 153}, {51, 102, 153},
    {51, 51, 51}, {51, 102, 153}, {204, 204, 204}, {51, 102, 153},
};

static int nk_theme_name_ok(const char *name) {
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

int nk_theme_active(char *dst, int cap) {
    FILE *f;
    if (cap <= NK_THEME_NAME_MAX) return -1;
    f = fopen(NK_THEME_PATH_CURRENT, "r");
    if (f) {
        char line[NK_THEME_LINE_MAX];
        if (fgets(line, sizeof(line), f)) {
            unsigned n = 0;
            while (line[n] && line[n] != '\n' && line[n] != '\r' &&
                   n < NK_THEME_NAME_MAX) {
                dst[n] = line[n];
                n++;
            }
            dst[n] = 0;
            fclose(f);
            if (nk_theme_name_ok(dst)) return 0;
        } else {
            fclose(f);
        }
    }
    snprintf(dst, (unsigned)cap, "%s", NK_THEME_DEFAULT);
    return -1;
}

static int nk_theme_parse_line(const char *line,
                               unsigned char rgb[NK_THEME_KEY_COUNT][3]) {
    char key[NK_THEME_KEY_MAX + 1];
    long v[3];
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
    if (sscanf(line + k, "%ld %ld %ld", &v[0], &v[1], &v[2]) != 3) return -1;
    for (i = 0; i < 3; i++) {
        if (v[i] < 0) v[i] = 0;
        if (v[i] > 255) v[i] = 255;
    }
    for (i = 0; i < NK_THEME_KEY_COUNT; i++) {
        if (strcmp(nk_theme_slots[i].key, key) == 0) {
            rgb[nk_theme_slots[i].idx][0] = (unsigned char)v[0];
            rgb[nk_theme_slots[i].idx][1] = (unsigned char)v[1];
            rgb[nk_theme_slots[i].idx][2] = (unsigned char)v[2];
            return 0;
        }
    }
    return -1;
}

int nk_theme_probe(const char *name, unsigned char rgb[NK_THEME_KEY_COUNT][3]) {
    char want[NK_THEME_NAME_MAX + 1];
    char path[64];
    FILE *f;
    unsigned i;
    for (i = 0; i < NK_THEME_KEY_COUNT; i++) {
        rgb[i][0] = nk_theme_fallback[i][0];
        rgb[i][1] = nk_theme_fallback[i][1];
        rgb[i][2] = nk_theme_fallback[i][2];
    }
    if (name && name[0]) {
        if (!nk_theme_name_ok(name)) return -1;
        snprintf(want, sizeof(want), "%s", name);
    } else {
        nk_theme_active(want, sizeof(want));
    }
    snprintf(path, sizeof(path), "%s%s", NK_THEME_PATH_DIR, want);
    f = fopen(path, "r");
    if (!f) return -1;
    {
        char line[NK_THEME_LINE_MAX + 8];
        while (fgets(line, sizeof(line), f)) {
            if (strlen(line) >= NK_THEME_LINE_MAX + 7) {
                char drain[64];
                while (fgets(drain, sizeof(drain), f) &&
                       strlen(drain) >= sizeof(drain) - 1) {
                }
                continue;
            }
            nk_theme_parse_line(line, rgb);
        }
    }
    fclose(f);
    return 0;
}

int nk_theme_apply(struct nk_context *ctx, const char *name) {
    unsigned char rgb[NK_THEME_KEY_COUNT][3];
    struct nk_color table[32];
    unsigned i;
    int rc = nk_theme_probe(name, rgb);
    for (i = 0; i < NK_THEME_KEY_COUNT; i++)
        table[i] = nk_rgb(rgb[i][0], rgb[i][1], rgb[i][2]);
    nk_style_from_table(ctx, table);
    return rc;
}
