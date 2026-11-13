/** Docstring: Host test for headers/wm_dock.h (make test-dock).
 *
 * Covers the fluid dock contract: the bell curve peaks under the
 * pointer, rests at the reach, is symmetric and never grows with
 * distance; the level scales the growth linearly and ramps in time
 * toward its target; the sampler is the identity at 1:1, interpolates
 * between texel centres, clamps at the borders, weights colour by alpha
 * so transparent texels never darken an edge, and fails closed.
 */

#include <stdio.h>

#include "wm_dock.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

int main(void)
{
    wm_dock_config_t cfg = { 32, 64, 120 };
    wm_dock_config_t bad;
    static const unsigned char pair[8] = { 0, 0, 0, 255, 255, 255, 255, 255 };
    static const unsigned char fringe[8] = { 255, 0, 0, 255, 0, 0, 0, 0 };
    static const unsigned char clear[8] = { 9, 9, 9, 0, 9, 9, 9, 0 };
    static const unsigned char column[8] = { 0, 0, 200, 255, 0, 0, 100, 255 };
    unsigned char quad[2 * 2 * 4];
    unsigned long c;
    int a, d, prev, i;

    CHECK(wm_dock_mag_size(&cfg, 0, WM_DOCK_LEVEL_ONE) == 64, "peak under the pointer");
    CHECK(wm_dock_mag_size(&cfg, 120, WM_DOCK_LEVEL_ONE) == 32, "base at the reach");
    CHECK(wm_dock_mag_size(&cfg, 5000, WM_DOCK_LEVEL_ONE) == 32, "base beyond the reach");
    CHECK(wm_dock_mag_size(&cfg, 60, WM_DOCK_LEVEL_ONE) == 50, "bell value at half the reach");
    CHECK(wm_dock_mag_size(&cfg, 30, WM_DOCK_LEVEL_ONE) == 60, "bell value at a quarter of the reach");
    CHECK(wm_dock_mag_size(&cfg, 90, WM_DOCK_LEVEL_ONE) == 38, "bell value at three quarters of the reach");
    CHECK(wm_dock_mag_size(&cfg, -60, WM_DOCK_LEVEL_ONE) == 50, "bell is symmetric");
    CHECK(wm_dock_mag_size(&cfg, -5000, WM_DOCK_LEVEL_ONE) == 32, "base beyond the reach on the left");
    prev = 65;
    for (d = 0; d <= 130; d++) {
        int s = wm_dock_mag_size(&cfg, d, WM_DOCK_LEVEL_ONE);
        if (s > prev || s < 32 || s > 64) {
            CHECK(0, "bell never grows with distance and stays in range");
            break;
        }
        prev = s;
    }

    CHECK(wm_dock_mag_size(&cfg, 0, 0) == 32, "level zero is a flat dock");
    CHECK(wm_dock_mag_size(&cfg, 0, WM_DOCK_LEVEL_ONE / 2) == 48, "half level is half the growth");
    CHECK(wm_dock_mag_size(&cfg, 60, WM_DOCK_LEVEL_ONE / 2) == 41, "half level scales the bell");
    CHECK(wm_dock_mag_size(&cfg, 0, -40) == 32, "negative level clamps to flat");
    CHECK(wm_dock_mag_size(&cfg, 0, 9999) == 64, "level beyond one clamps to full");

    CHECK(wm_dock_mag_size(0, 0, WM_DOCK_LEVEL_ONE) == 0, "null configuration yields no size");
    bad = cfg; bad.base = 0;
    CHECK(wm_dock_mag_size(&bad, 0, WM_DOCK_LEVEL_ONE) == 0, "non-positive base yields no size");
    bad = cfg; bad.peak = 32;
    CHECK(wm_dock_mag_size(&bad, 0, WM_DOCK_LEVEL_ONE) == 32, "peak not above base stays flat");
    bad = cfg; bad.reach = 0;
    CHECK(wm_dock_mag_size(&bad, 0, WM_DOCK_LEVEL_ONE) == 32, "zero reach stays flat");
    bad = cfg; bad.reach = WM_DOCK_REACH_MAX + 1;
    CHECK(wm_dock_mag_size(&bad, 0, WM_DOCK_LEVEL_ONE) == 32, "reach beyond the bound stays flat");
    bad = cfg; bad.reach = WM_DOCK_REACH_MAX; bad.peak = WM_DOCK_SIZE_MAX;
    CHECK(wm_dock_mag_size(&bad, 0, WM_DOCK_LEVEL_ONE) == WM_DOCK_SIZE_MAX, "bounds do not overflow at the peak");
    CHECK(wm_dock_mag_size(&bad, WM_DOCK_REACH_MAX - 1, WM_DOCK_LEVEL_ONE) == 32, "bounds do not overflow at the rim");
    bad = cfg; bad.peak = WM_DOCK_SIZE_MAX + 1;
    CHECK(wm_dock_mag_size(&bad, 0, WM_DOCK_LEVEL_ONE) == 32, "peak beyond the bound stays flat");

    CHECK(wm_dock_level(0, 1, 0, 12) == 0, "ramp starts where it was");
    CHECK(wm_dock_level(0, 1, 6, 12) == 128, "rising ramp is linear");
    CHECK(wm_dock_level(0, 1, 12, 12) == WM_DOCK_LEVEL_ONE, "rising ramp reaches one");
    CHECK(wm_dock_level(0, 1, 500, 12) == WM_DOCK_LEVEL_ONE, "rising ramp holds one");
    CHECK(wm_dock_level(WM_DOCK_LEVEL_ONE, 0, 3, 12) == 192, "falling ramp is linear");
    CHECK(wm_dock_level(WM_DOCK_LEVEL_ONE, 0, 12, 12) == 0, "falling ramp reaches zero");
    CHECK(wm_dock_level(128, 1, 9, 12) == WM_DOCK_LEVEL_ONE, "rising ramp clamps at one");
    CHECK(wm_dock_level(128, 0, 9, 12) == 0, "falling ramp clamps at zero");
    CHECK(wm_dock_level(128, 1, 3, 12) == 192, "ramp resumes from a partial level");
    CHECK(wm_dock_level(128, 0, 3, 12) == 64, "ramp falls from a partial level");
    CHECK(wm_dock_level(0, 1, 0, 0) == WM_DOCK_LEVEL_ONE, "zero duration jumps up");
    CHECK(wm_dock_level(WM_DOCK_LEVEL_ONE, 0, 0, 0) == 0, "zero duration jumps down");
    CHECK(wm_dock_level(-50, 1, 3, 12) == 64, "start level clamps below");
    CHECK(wm_dock_level(9999, 0, 3, 12) == 192, "start level clamps above");

    CHECK(wm_dock_src_coord(0, 4, 4) == 0 && wm_dock_src_coord(3, 4, 4) == 3 * WM_DOCK_FRAC_ONE,
          "1:1 scale maps pixels onto texels");
    CHECK(wm_dock_src_coord(1, 4, 2) == 64, "upscale maps between texel centres");
    CHECK(wm_dock_src_coord(0, 4, 2) == 0, "coordinate clamps to the first texel");
    CHECK(wm_dock_src_coord(3, 4, 2) == WM_DOCK_FRAC_ONE, "coordinate clamps to the last texel");
    CHECK(wm_dock_src_coord(0, 0, 2) == 0 && wm_dock_src_coord(0, 4, 0) == 0, "degenerate spans map to zero");

    for (i = 0; i < 16; i++) {
        quad[i] = (unsigned char)(i * 13 + 7);
    }
    quad[3] = 255; quad[7] = 255; quad[11] = 255; quad[15] = 255;
    c = wm_dock_sample(quad, 2, 2, 2, 2, 1, 0, &a);
    CHECK(c == (((unsigned long)quad[4] << 16) | ((unsigned long)quad[5] << 8) | quad[6]) && a == 255,
          "1:1 sample is the source texel");
    c = wm_dock_sample(quad, 2, 2, 2, 2, 0, 1, &a);
    CHECK(c == (((unsigned long)quad[8] << 16) | ((unsigned long)quad[9] << 8) | quad[10]) && a == 255,
          "1:1 sample addresses rows");

    c = wm_dock_sample(pair, 2, 1, 4, 1, 0, 0, &a);
    CHECK(c == 0x000000UL && a == 255, "upscale left border is the first texel");
    c = wm_dock_sample(pair, 2, 1, 4, 1, 1, 0, &a);
    CHECK(c == 0x404040UL && a == 255, "upscale interpolates a quarter");
    c = wm_dock_sample(pair, 2, 1, 4, 1, 2, 0, &a);
    CHECK(c == 0xBFBFBFUL && a == 255, "upscale interpolates three quarters");
    c = wm_dock_sample(pair, 2, 1, 4, 1, 3, 0, &a);
    CHECK(c == 0xFFFFFFUL && a == 255, "upscale right border is the last texel");

    c = wm_dock_sample(column, 1, 2, 1, 4, 0, 1, &a);
    CHECK(c == 0x0000AFUL && a == 255, "upscale interpolates vertically");

    c = wm_dock_sample(fringe, 2, 1, 4, 1, 1, 0, &a);
    CHECK(c == 0xFF0000UL, "transparent texel does not darken the colour");
    CHECK(a == 191, "coverage interpolates toward the transparent texel");
    c = wm_dock_sample(fringe, 2, 1, 4, 1, 3, 0, &a);
    CHECK(c == 0 && a == 0, "fully transparent sample has no coverage");
    c = wm_dock_sample(clear, 2, 1, 4, 1, 1, 0, &a);
    CHECK(c == 0 && a == 0, "transparent source yields nothing");

    a = 77;
    CHECK(wm_dock_sample(0, 2, 1, 4, 1, 0, 0, &a) == 0 && a == 0, "null source fails closed");
    a = 77;
    CHECK(wm_dock_sample(pair, 0, 1, 4, 1, 0, 0, &a) == 0 && a == 0, "empty source fails closed");
    a = 77;
    CHECK(wm_dock_sample(pair, 2, 1, 0, 1, 0, 0, &a) == 0 && a == 0, "empty destination fails closed");
    a = 77;
    CHECK(wm_dock_sample(pair, 2, 1, 4, 1, 4, 0, &a) == 0 && a == 0, "pixel past the width fails closed");
    a = 77;
    CHECK(wm_dock_sample(pair, 2, 1, 4, 1, 0, 1, &a) == 0 && a == 0, "pixel past the height fails closed");
    a = 77;
    CHECK(wm_dock_sample(pair, 2, 1, 4, 1, -1, 0, &a) == 0 && a == 0, "negative pixel fails closed");
    CHECK(wm_dock_sample(pair, 2, 1, 4, 1, 0, 0, 0) == 0, "null alpha fails closed");

    if (failures) {
        fprintf(stderr, "wm_dock: %d failure(s)\n", failures);
        return 1;
    }
    printf("wm_dock: all checks passed\n");
    return 0;
}
