/** Docstring: Host test for headers/wm_chrome.h (make test-chrome).
 *
 * Covers the chrome pixel contract: blend endpoints and rounding, channel
 * clamping, integer square root exactness, gradient endpoints and
 * monotonicity, shadow alpha inside, on the edge and beyond the radius
 * with monotonic falloff, corner coverage symmetry and anti-aliasing
 * range, and degenerate input failing closed.
 */

#include <stdio.h>

#include "wm_chrome.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

int main(void)
{
    wm_chrome_config_t cfg = WM_CHROME_CONFIG_DEFAULT;
    unsigned long v;
    int i;
    int prev;
    int x, y;

    CHECK(cfg.shadow_radius == 8, "config carries shadow radius");
    CHECK(cfg.glow_alpha == 70, "config carries glow alpha");
    CHECK(cfg.term_alpha == 205, "config carries terminal alpha");
    CHECK(cfg.term_alpha > 0 && cfg.term_alpha < WM_CHROME_ALPHA_OPAQUE, "terminal is translucent but visible");
    CHECK(wm_chrome_blend(0x808080UL, 0x0F0F0FUL, cfg.term_alpha) == 0x252525UL, "terminal tint over mid gray");
    CHECK(cfg.corner_radius <= WM_CHROME_RADIUS_MAX, "corner radius within scratch bound");

    for (v = 0; v < 70000; v++) {
        unsigned long r = wm_chrome_isqrt(v);
        if (r * r > v || (r + 1) * (r + 1) <= v) {
            CHECK(0, "isqrt floor property");
            break;
        }
    }
    CHECK(wm_chrome_isqrt(~0UL) == 0xFFFFFFFFUL, "isqrt of the maximum word");

    CHECK(wm_chrome_blend_channel(10, 200, 0) == 10, "alpha 0 keeps dst");
    CHECK(wm_chrome_blend_channel(10, 200, 255) == 200, "alpha 255 takes src");
    CHECK(wm_chrome_blend_channel(0, 255, 128) == 128, "midpoint rounds");
    CHECK(wm_chrome_blend_channel(300, -5, 255) == 0, "inputs are clamped");
    CHECK(wm_chrome_blend_channel(0, 255, 999) == 255, "alpha above 255 clamps");
    CHECK(wm_chrome_blend(0x102030UL, 0xA0B0C0UL, 0) == 0x102030UL, "packed alpha 0");
    CHECK(wm_chrome_blend(0x102030UL, 0xA0B0C0UL, 255) == 0xA0B0C0UL, "packed alpha 255");
    CHECK(wm_chrome_blend(0xFFFFFFUL, 0x000000UL, 128) == 0x7F7F7FUL, "packed black over white");

    CHECK(wm_chrome_shift(0x808080UL, 10) == 0x8A8A8AUL, "shift up");
    CHECK(wm_chrome_shift(0xFEFEFEUL, 10) == 0xFFFFFFUL, "shift saturates high");
    CHECK(wm_chrome_shift(0x050505UL, -10) == 0x000000UL, "shift saturates low");

    CHECK(wm_chrome_gradient(0x404040UL, 0, 8, &cfg) == wm_chrome_shift(0x404040UL, cfg.title_lift),
          "gradient top is lifted");
    CHECK(wm_chrome_gradient(0x404040UL, 7, 8, &cfg) == wm_chrome_shift(0x404040UL, -cfg.title_sink),
          "gradient bottom is sunk");
    prev = 1000;
    for (i = 0; i < 8; i++) {
        int c = (int)(wm_chrome_gradient(0x808080UL, i, 8, &cfg) & 0xFF);
        CHECK(c <= prev, "gradient is monotonic non-increasing");
        prev = c;
    }
    CHECK(wm_chrome_gradient(0x404040UL, 3, 1, &cfg) == 0x404040UL, "span 1 keeps base");
    CHECK(wm_chrome_gradient(0x404040UL, 9, 8, &cfg) == 0x404040UL, "row out of span keeps base");
    CHECK(wm_chrome_gradient(0x404040UL, 3, 8, 0) == 0x404040UL, "null cfg keeps base");

    CHECK(wm_chrome_shadow_alpha(&cfg, 100 + cfg.shadow_dx + 5, 100 + cfg.shadow_dy + 5,
                                 100, 100, 50, 50) == cfg.shadow_alpha,
          "inside the shifted rect is the maximum");
    CHECK(wm_chrome_shadow_alpha(&cfg, 100 + cfg.shadow_dx + 50 + cfg.shadow_radius, 120,
                                 100, 100, 50, 50) == 0,
          "beyond the radius is zero");
    CHECK(wm_chrome_shadow_alpha(&cfg, 0, 0, 100, 100, 50, 50) == 0, "far away is zero");
    prev = 1000;
    for (i = 0; i <= cfg.shadow_radius + 2; i++) {
        int a = wm_chrome_shadow_alpha(&cfg, 100 + cfg.shadow_dx + 50 - 1 + i, 120, 100, 100, 50, 50);
        CHECK(a <= prev, "shadow falls off monotonically");
        CHECK(a >= 0 && a <= cfg.shadow_alpha, "shadow alpha within bounds");
        prev = a;
    }
    {
        int edge_x = 100 + cfg.shadow_dx + 50 - 1;
        CHECK(wm_chrome_shadow_alpha(&cfg, edge_x + 1, 120, 100, 100, 50, 50) == 84, "falloff at 1 px is quadratic");
        CHECK(wm_chrome_shadow_alpha(&cfg, edge_x + 4, 120, 100, 100, 50, 50) == 27, "falloff at 4 px is quadratic");
        CHECK(wm_chrome_shadow_alpha(&cfg, edge_x + 7, 120, 100, 100, 50, 50) == 1, "falloff at 7 px is quadratic");
        CHECK(wm_chrome_shadow_alpha(&cfg, 130, 100 + cfg.shadow_dy - 1, 100, 100, 50, 50) < cfg.shadow_alpha,
              "vertical offset shifts the shadow down");
        CHECK(wm_chrome_shadow_alpha(&cfg, 100 + cfg.shadow_dx - 1, 130, 100, 100, 50, 50) < cfg.shadow_alpha,
              "horizontal offset shifts the shadow right");
    }
    CHECK(wm_chrome_shadow_alpha(0, 1, 1, 0, 0, 10, 10) == 0, "null cfg fails closed");
    CHECK(wm_chrome_shadow_alpha(&cfg, 1, 1, 0, 0, 0, 10) == 0, "zero width fails closed");
    CHECK(wm_chrome_shadow_alpha(&cfg, 1, 1, 0, 0, 10, -1) == 0, "negative height fails closed");

    for (y = 0; y < cfg.corner_radius; y++) {
        for (x = 0; x < cfg.corner_radius; x++) {
            int c = wm_chrome_corner_coverage(cfg.corner_radius, x, y);
            CHECK(c == wm_chrome_corner_coverage(cfg.corner_radius, y, x), "corner is symmetric");
            CHECK(c >= 0 && c <= 255, "coverage within range");
            if (x > 0 && y > 0) {
                CHECK(c >= wm_chrome_corner_coverage(cfg.corner_radius, x - 1, y - 1),
                      "coverage grows toward the inside");
            }
        }
    }
    CHECK(wm_chrome_corner_coverage(4, 1, 0) == 55, "radius 4 coverage at (1,0)");
    CHECK(wm_chrome_corner_coverage(4, 2, 0) == 183, "radius 4 coverage at (2,0)");
    CHECK(wm_chrome_corner_coverage(4, 3, 0) == 247, "radius 4 coverage at (3,0)");
    CHECK(wm_chrome_corner_coverage(4, 1, 1) == 247, "radius 4 coverage at (1,1)");
    CHECK(wm_chrome_corner_coverage(cfg.corner_radius, 0, 0) == 0, "outermost pixel is cut");
    CHECK(wm_chrome_corner_coverage(cfg.corner_radius, cfg.corner_radius - 1, cfg.corner_radius - 1) == 255,
          "innermost pixel is solid");
    CHECK(wm_chrome_corner_coverage(cfg.corner_radius, cfg.corner_radius, 0) == 255,
          "outside the radius box is solid");
    CHECK(wm_chrome_disc_coverage(4, 3, 3) == 255, "disc centre is solid");
    CHECK(wm_chrome_disc_coverage(4, 0, 0) == 0, "disc box corner is empty");
    CHECK(wm_chrome_disc_coverage(4, 7, 7) == 0, "disc far corner is empty");
    CHECK(wm_chrome_disc_coverage(4, 1, 0) == 55, "disc edge matches the corner arc");
    CHECK(wm_chrome_disc_coverage(4, 6, 0) == 55, "disc is mirrored horizontally");
    CHECK(wm_chrome_disc_coverage(4, 0, 6) == 55, "disc is mirrored vertically");
    CHECK(wm_chrome_disc_coverage(4, 8, 3) == 0, "outside the box is empty");
    CHECK(wm_chrome_disc_coverage(4, -1, 3) == 0, "negative coordinate is empty");
    CHECK(wm_chrome_disc_coverage(0, 0, 0) == 0, "radius 0 disc is empty");
    CHECK(wm_chrome_corner_coverage(0, 0, 0) == 255, "radius 0 is square");
    CHECK(wm_chrome_corner_coverage(4, -1, 0) == 255, "negative coordinate is solid");

    if (failures) {
        fprintf(stderr, "%d failure(s)\n", failures);
        return 1;
    }
    printf("chrome_test: all checks passed\n");
    return 0;
}
