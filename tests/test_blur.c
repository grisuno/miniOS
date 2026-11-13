/** Docstring: Host test for headers/wm_blur.h (make test-blur).
 *
 * Covers the frosted-glass contract: the reciprocal average equals the
 * rounded integer division for every reachable sum, a uniform image is
 * returned unchanged, an impulse spreads into the exact box and triangle
 * kernels, edges replicate the border pixel, channels never leak into
 * each other, the strided column pass filters columns, the rect filter
 * runs rows and columns for every pass, and degenerate input fails
 * closed leaving the pixels untouched.
 */

#include <stdio.h>
#include <string.h>

#include "wm_blur.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

#define GRID_W 7
#define GRID_H 5

int main(void)
{
    wm_blur_config_t cfg = WM_BLUR_CONFIG_DEFAULT;
    wm_blur_config_t one = { 1, 1 };
    wm_blur_config_t two = { 1, 2 };
    wm_blur_config_t bad;
    unsigned int px[GRID_W * GRID_H];
    unsigned int keep[GRID_W * GRID_H];
    unsigned int line[GRID_W];
    unsigned int row[9];
    unsigned int scratch[9];
    int r, i, x, y;

    CHECK(cfg.radius == 4, "default radius");
    CHECK(cfg.passes == 2, "default passes");
    CHECK(wm_blur_config_valid(&cfg), "default configuration is valid");
    CHECK(!wm_blur_config_valid(0), "null configuration is invalid");
    bad.radius = 0; bad.passes = 1;
    CHECK(!wm_blur_config_valid(&bad), "zero radius is invalid");
    bad.radius = WM_BLUR_RADIUS_MAX + 1; bad.passes = 1;
    CHECK(!wm_blur_config_valid(&bad), "radius beyond the bound is invalid");
    bad.radius = WM_BLUR_RADIUS_MAX; bad.passes = 1;
    CHECK(wm_blur_config_valid(&bad), "radius at the bound is valid");
    bad.radius = 1; bad.passes = 0;
    CHECK(!wm_blur_config_valid(&bad), "zero passes is invalid");
    bad.radius = 1; bad.passes = WM_BLUR_PASSES_MAX + 1;
    CHECK(!wm_blur_config_valid(&bad), "passes beyond the bound are invalid");
    bad.radius = 1; bad.passes = WM_BLUR_PASSES_MAX;
    CHECK(wm_blur_config_valid(&bad), "passes at the bound are valid");

    CHECK(wm_blur_line_len(7, 5) == 7, "scratch is the longer side (width)");
    CHECK(wm_blur_line_len(3, 9) == 9, "scratch is the longer side (height)");
    CHECK(wm_blur_line_len(0, 9) == 0, "empty width needs no scratch");
    CHECK(wm_blur_line_len(9, 0) == 0, "empty height needs no scratch");
    CHECK(wm_blur_recip(0) == 0, "reciprocal of an empty window");

    for (r = 1; r <= WM_BLUR_RADIUS_MAX; r++) {
        int win = 2 * r + 1;
        unsigned long recip = wm_blur_recip(win);
        unsigned long sum;
        for (sum = 0; sum <= 255UL * (unsigned long)win; sum++) {
            if (wm_blur_avg(sum, win, recip) != (sum + (unsigned long)(win / 2)) / (unsigned long)win) {
                CHECK(0, "reciprocal average equals the rounded division");
                r = WM_BLUR_RADIUS_MAX;
                break;
            }
        }
    }

    CHECK(wm_blur_edge(-3, 5) == 0, "edge clamps below");
    CHECK(wm_blur_edge(7, 5) == 4, "edge clamps above");
    CHECK(wm_blur_edge(2, 5) == 2, "edge keeps an inner index");

    for (i = 0; i < GRID_W * GRID_H; i++) {
        px[i] = 0x336699u;
    }
    CHECK(wm_blur_rect(px, GRID_W, GRID_H, &cfg, line) == 1, "uniform rect is accepted");
    for (i = 0; i < GRID_W * GRID_H; i++) {
        if (px[i] != 0x336699u) {
            CHECK(0, "uniform image survives the blur unchanged");
            break;
        }
    }

    memset(row, 0, sizeof(row));
    row[4] = 0xFF0000u;
    wm_blur_line(row, 1L, 9, 1, scratch);
    CHECK(row[3] == 0x550000u && row[4] == 0x550000u && row[5] == 0x550000u,
          "impulse spreads into a 3-pixel box");
    CHECK(row[2] == 0 && row[6] == 0, "box stops at the radius");
    CHECK(scratch[4] == 0xFF0000u, "scratch keeps the source line");

    memset(row, 0, sizeof(row));
    row[4] = 0x0000FFu;
    wm_blur_line(row, 1L, 9, 2, scratch);
    CHECK(row[2] == 0x000033u && row[6] == 0x000033u && row[1] == 0 && row[7] == 0,
          "radius two spreads into a 5-pixel box");

    memset(row, 0, sizeof(row));
    row[0] = 0x00FF00u;
    wm_blur_line(row, 1L, 9, 1, scratch);
    CHECK(row[0] == 0x00AA00u, "left edge replicates the border pixel");
    CHECK(row[1] == 0x005500u && row[2] == 0, "left edge spreads inward only");

    memset(row, 0, sizeof(row));
    row[8] = 0x00FF00u;
    wm_blur_line(row, 1L, 9, 1, scratch);
    CHECK(row[8] == 0x00AA00u, "right edge replicates the border pixel");
    CHECK(row[7] == 0x005500u && row[6] == 0, "right edge spreads inward only");

    memset(row, 0, sizeof(row));
    row[4] = 0xFF0000u;
    row[5] = 0x0000FFu;
    wm_blur_line(row, 1L, 9, 1, scratch);
    CHECK(row[4] == 0x550055u && row[3] == 0x550000u && row[6] == 0x000055u,
          "channels are filtered independently");

    memset(row, 0, sizeof(row));
    row[3] = 0x000001u;
    row[4] = 0x000001u;
    wm_blur_line(row, 1L, 9, 1, scratch);
    CHECK(row[3] == 0x000001u && row[4] == 0x000001u && row[2] == 0 && row[5] == 0,
          "average rounds to nearest");

    memset(row, 0, sizeof(row));
    row[4] = 0xFFFFFFu;
    wm_blur_line(row, 1L, 9, 0, scratch);
    CHECK(row[4] == 0xFFFFFFu && row[3] == 0, "radius zero leaves the line untouched");
    wm_blur_line(row, 1L, 9, WM_BLUR_RADIUS_MAX + 1, scratch);
    CHECK(row[4] == 0xFFFFFFu && row[3] == 0, "radius beyond the bound leaves the line untouched");
    wm_blur_line(row, 1L, 0, 1, scratch);
    wm_blur_line(0, 1L, 9, 1, scratch);
    wm_blur_line(row, 1L, 9, 1, 0);
    CHECK(row[4] == 0xFFFFFFu && row[3] == 0, "degenerate line calls leave the line untouched");

    memset(px, 0, sizeof(px));
    px[2 * GRID_W + 3] = 0xFF0000u;
    wm_blur_line(px + 3, (long)GRID_W, GRID_H, 1, line);
    CHECK(px[1 * GRID_W + 3] == 0x550000u && px[2 * GRID_W + 3] == 0x550000u &&
          px[3 * GRID_W + 3] == 0x550000u, "strided pass filters a column");
    CHECK(px[2 * GRID_W + 2] == 0 && px[2 * GRID_W + 4] == 0, "strided pass stays in its column");

    memset(px, 0, sizeof(px));
    px[2 * GRID_W + 3] = 0xFFFFFFu;
    CHECK(wm_blur_rect(px, GRID_W, GRID_H, &one, line) == 1, "one pass is accepted");
    for (y = 0; y < GRID_H; y++) {
        for (x = 0; x < GRID_W; x++) {
            unsigned int want = (x >= 2 && x <= 4 && y >= 1 && y <= 3) ? 0x1C1C1Cu : 0u;
            if (px[y * GRID_W + x] != want) {
                CHECK(0, "one pass turns an impulse into a 3x3 box");
                y = GRID_H;
                break;
            }
        }
    }

    memset(row, 0, sizeof(row));
    row[4] = 0xFF0000u;
    CHECK(wm_blur_rect(row, 9, 1, &two, scratch) == 1, "two passes are accepted");
    CHECK(row[2] == 0x1C0000u && row[3] == 0x390000u && row[4] == 0x550000u &&
          row[5] == 0x390000u && row[6] == 0x1C0000u && row[1] == 0 && row[7] == 0,
          "two passes build a triangle kernel");

    memset(px, 0, sizeof(px));
    px[2 * GRID_W + 3] = 0xFFFFFFu;
    memcpy(keep, px, sizeof(px));
    CHECK(wm_blur_rect(0, GRID_W, GRID_H, &one, line) == 0, "null pixels fail closed");
    CHECK(wm_blur_rect(px, GRID_W, GRID_H, &one, 0) == 0, "null scratch fails closed");
    CHECK(wm_blur_rect(px, 0, GRID_H, &one, line) == 0, "empty width fails closed");
    CHECK(wm_blur_rect(px, GRID_W, 0, &one, line) == 0, "empty height fails closed");
    CHECK(wm_blur_rect(px, GRID_W, GRID_H, 0, line) == 0, "null configuration fails closed");
    bad.radius = WM_BLUR_RADIUS_MAX + 1; bad.passes = 1;
    CHECK(wm_blur_rect(px, GRID_W, GRID_H, &bad, line) == 0, "invalid configuration fails closed");
    CHECK(memcmp(keep, px, sizeof(px)) == 0, "rejected calls leave the pixels untouched");

    if (failures) {
        fprintf(stderr, "wm_blur: %d failure(s)\n", failures);
        return 1;
    }
    printf("wm_blur: all checks passed\n");
    return 0;
}
