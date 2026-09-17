/** Docstring: host test for the shared ring-3 PNG helpers (make test-png).
 *
 * Mirror pin for progs/minios_png.h: 3-3-2 quantize, nearest palette,
 * center geometry, fit scale, scaled RGB to indexed conversion, clipped
 * blit, bounded file load and the pokemon side-art candidate policy.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "progs/minios_png.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

/** Docstring: 3-3-2 quantize matches the manual bit packing. */
static void t_332(void) {
    CHECK(mpng_332_idx(255, 0, 0) == 0xE0, "332 red");
    CHECK(mpng_332_idx(0, 255, 0) == 0x1C, "332 green");
    CHECK(mpng_332_idx(0, 0, 255) == 0x03, "332 blue");
    CHECK(mpng_332_idx(0, 0, 0) == 0x00, "332 black");
    CHECK(mpng_332_idx(255, 255, 255) == 0xFF, "332 white");
}

/** Docstring: nearest search hits exact entries and rejects bad input. */
static void t_nearest(void) {
    unsigned char pal[768];
    int k;
    memset(pal, 0, sizeof(pal));
    pal[0] = 255;
    pal[1] = 0;
    pal[2] = 0;
    pal[3] = 0;
    pal[4] = 255;
    pal[5] = 0;
    pal[6] = 0;
    pal[7] = 0;
    pal[8] = 255;
    CHECK(mpng_nearest(pal, 3, 255, 0, 0) == 0, "nearest red");
    CHECK(mpng_nearest(pal, 3, 0, 255, 0) == 1, "nearest green");
    CHECK(mpng_nearest(pal, 3, 0, 0, 255) == 2, "nearest blue");
    CHECK(mpng_nearest(0, 3, 0, 0, 0) < 0, "nearest null pal");
    CHECK(mpng_nearest(pal, 0, 0, 0, 0) < 0, "nearest empty pal");
    CHECK(mpng_nearest(pal, 9999, 0, 0, 0) < 0, "nearest oversize pal");
    for (k = 0; k < 768; k++)
        pal[k] = 0;
    CHECK(mpng_nearest(pal, 256, 10, 20, 30) == 0, "nearest first wins");
}

/** Docstring: center and fit-scale geometry with fail-closed edges. */
static void t_geom(void) {
    CHECK(mpng_center(800, 320) == 240, "center 800/320");
    CHECK(mpng_center(360, 360) == 0, "center exact");
    CHECK(mpng_center(100, 200) < 0, "center unfit");
    CHECK(mpng_center(-1, 10) < 0, "center negative");
    CHECK(mpng_fit_scale(32, 32, 240, 344) == 7, "fit 32 in 240x344");
    CHECK(mpng_fit_scale(512, 512, 240, 344) == 1, "fit large keeps 1");
    CHECK(mpng_fit_scale(0, 32, 240, 344) < 0, "fit zero src");
    CHECK(mpng_fit_scale(32, 32, 0, 10) < 0, "fit zero box");
}

/** Docstring: scaled conversion preserves corners and rejects bounds. */
static void t_scale(void) {
    unsigned char pal[768];
    unsigned char rgb[2 * 2 * 3];
    unsigned char dst[4 * 4];
    unsigned char dst332[4 * 4];
    memset(pal, 0, sizeof(pal));
    pal[242 * 3] = 255;
    pal[242 * 3 + 1] = 0;
    pal[242 * 3 + 2] = 0;
    rgb[0] = 255; rgb[1] = 0; rgb[2] = 0;
    rgb[3] = 0; rgb[4] = 255; rgb[5] = 0;
    rgb[6] = 0; rgb[7] = 0; rgb[8] = 255;
    rgb[9] = 255; rgb[10] = 255; rgb[11] = 255;
    CHECK(mpng_rgb_to_idx_scaled(rgb, 2, 2, pal, 256, dst, 4, 4) == 0,
          "scale ok");
    CHECK(dst[0] == 242, "scale corner keeps red");
    CHECK(mpng_rgb_to_332_scaled(rgb, 2, 2, dst332, 4, 4) == 0,
          "scale332 ok");
    CHECK(dst332[0] == (unsigned char)mpng_332_idx(255, 0, 0),
          "scale332 corner");
    CHECK(mpng_rgb_to_idx_scaled(0, 2, 2, pal, 256, dst, 4, 4) < 0,
          "scale null rgb");
    CHECK(mpng_rgb_to_idx_scaled(rgb, 9999, 2, pal, 256, dst, 4, 4) < 0,
          "scale oversize src");
    CHECK(mpng_rgb_to_idx_scaled(rgb, 2, 2, pal, 256, dst, 9999, 4) < 0,
          "scale oversize dst");
}

/** Docstring: clipped blit lands inside and ignores outside. */
static void t_blit(void) {
    unsigned char fb[16];
    unsigned char tile[4];
    memset(fb, 7, sizeof(fb));
    tile[0] = 1;
    tile[1] = 2;
    tile[2] = 3;
    tile[3] = 4;
    CHECK(mpng_blit_idx(fb, 4, 4, tile, 2, 2, 1, 1) == 0, "blit ok");
    CHECK(fb[1 * 4 + 1] == 1 && fb[1 * 4 + 2] == 2, "blit row0");
    CHECK(fb[2 * 4 + 1] == 3 && fb[2 * 4 + 2] == 4, "blit row1");
    CHECK(fb[0] == 7, "blit outside untouched");
    CHECK(mpng_blit_idx(0, 4, 4, tile, 2, 2, 0, 0) < 0, "blit null fb");
    CHECK(mpng_blit_idx(fb, 4, 4, tile, 9999, 2, 0, 0) < 0,
          "blit oversize tile");
}

/** Docstring: bounded load fails closed on bad paths and caps. */
static void t_load(void) {
    unsigned char *out = 0;
    long n = 0;
    CHECK(mpng_load_file("/no/such/file.png", &out, &n, MPNG_FILE_MAX) < 0,
          "load missing");
    CHECK(mpng_load_file("", &out, &n, MPNG_FILE_MAX) < 0, "load empty");
    CHECK(mpng_load_file(0, &out, &n, MPNG_FILE_MAX) < 0, "load null");
    CHECK(mpng_load_file("/no/such/file.png", 0, &n, MPNG_FILE_MAX) < 0,
          "load null out");
    CHECK(mpng_load_file("tests/test_minios_png.c", &out, &n, 4) < 0,
          "load tiny cap");
    CHECK(mpng_load_file("tests/test_minios_png.c", &out, &n,
                         MPNG_FILE_MAX) == 0, "load self");
    CHECK(out != 0 && n > 0, "load content");
    if (out)
        free(out);
}

/** Docstring: side-art policy pins right pokemon and no cgoblin left. */
static void t_policy(void) {
    int k;
    CHECK(strcmp(MPNG_RIGHT_PATH, "/icons/pokemon.png") == 0, "right art");
    CHECK(MPNG_LEFT_N == 10, "left count");
    for (k = 0; k < MPNG_LEFT_N; k++) {
        CHECK(mpng_left_candidates[k] != 0, "left entry");
        CHECK(strstr(mpng_left_candidates[k], "cgoblin") == 0,
              "left excludes cgoblin");
        CHECK(strstr(mpng_left_candidates[k], "wallpaper") == 0,
              "left excludes wallpaper");
        CHECK(strncmp(mpng_left_candidates[k], "/icons/", 7) == 0,
              "left icons dir");
    }
}

int main(void) {
    t_332();
    t_nearest();
    t_geom();
    t_scale();
    t_blit();
    t_load();
    t_policy();
    if (failures) {
        printf("minios_png: FAIL (%d)\n", failures);
        return 1;
    }
    printf("minios_png: ok (332 nearest geom scale blit load policy)\n");
    return 0;
}
