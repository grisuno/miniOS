/** Docstring: Host test for headers/vga_fx.h (make test-fx).
 *
 * Covers the DOOM-melt column contract: staggered init fronts Peer f_wipe.c
 * (first column in -15..0, neighbours drifting by at most 1, never positive,
 * never -16), advance monotonicity and termination, front clamping, rect
 * clamping on every edge, null and degenerate inputs failing closed, and
 * determinism across identical seeds.
 */

#include <stdio.h>

#include "vga_fx.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

int main(void)
{
    vga_fx_config_t cfg = VGA_FX_CONFIG_DEFAULT;
    int cols[VGA_FX_COLS_MAX];
    int i;
    int x, y, w, h;

    CHECK(cfg.step_px == 8, "config carries step");
    CHECK(cfg.frame_ms == 8, "config carries frame pacing");
    CHECK(cfg.max_delay == 16, "config carries max delay");

    CHECK(vga_fx_init_cols(0, cols, 10) != 0, "null cfg fails closed");
    CHECK(vga_fx_init_cols(&cfg, 0, 10) != 0, "null cols fails closed");
    CHECK(vga_fx_init_cols(&cfg, cols, 0) != 0, "zero width fails closed");
    CHECK(vga_fx_init_cols(&cfg, cols, VGA_FX_COLS_MAX + 1) != 0, "wide fails closed");
    CHECK(vga_fx_advance(0, cols, 10, 10) == 1, "null cfg advance done");
    CHECK(vga_fx_advance(&cfg, 0, 10, 10) == 1, "null cols advance done");

    CHECK(vga_fx_init_cols(&cfg, cols, 320) == 0, "init accepts doom width");
    CHECK(cols[0] <= 0 && cols[0] > -16, "first column staggered negative");
    for (i = 1; i < 320; i++) {
        int d = cols[i] - cols[i - 1];
        if (d < -1 || d > 1) {
            break;
        }
        if (cols[i] > 0 || cols[i] == -16) {
            break;
        }
    }
    CHECK(i == 320, "columns drift by at most one, never positive, never -16");

    {
        int cols2[VGA_FX_COLS_MAX];
        vga_fx_init_cols(&cfg, cols2, 320);
        for (i = 0; i < 320; i++) {
            if (cols[i] != cols2[i]) {
                break;
            }
        }
        CHECK(i == 320, "same seed replays identical fronts");
    }

    {
        int h = 200;
        int frames = 0;
        int prev[VGA_FX_COLS_MAX];
        for (i = 0; i < 320; i++) {
            prev[i] = vga_fx_front(cols[i], h);
        }
        while (!vga_fx_advance(&cfg, cols, 320, h) && frames < 1000) {
            frames++;
            for (i = 0; i < 320; i++) {
                int f = vga_fx_front(cols[i], h);
                if (f < prev[i] || f > h) {
                    break;
                }
                prev[i] = f;
            }
            if (i != 320) {
                break;
            }
        }
        CHECK(i == 320, "fronts advance monotonically inside bounds");
        CHECK(frames < 1000, "melt terminates");
        for (i = 0; i < 320; i++) {
            if (cols[i] != h) {
                break;
            }
        }
        CHECK(i == 320, "every column reaches the bottom");
    }

    CHECK(vga_fx_front(-5, 200) == 0, "negative front reveals nothing");
    CHECK(vga_fx_front(0, 200) == 0, "zero front reveals nothing");
    CHECK(vga_fx_front(37, 200) == 37, "mid front reveals rows");
    CHECK(vga_fx_front(500, 200) == 200, "front clamps at bottom");
    CHECK(vga_fx_front(201, 200) == 200, "one past bottom clamps");

    x = 10; y = 20; w = 30; h = 40;
    CHECK(vga_fx_clamp_rect(&x, &y, &w, &h, 800, 600) == 0, "inside rect passes");
    CHECK(x == 10 && y == 20 && w == 30 && h == 40, "inside rect untouched");
    x = -5; y = -5; w = 30; h = 40;
    CHECK(vga_fx_clamp_rect(&x, &y, &w, &h, 800, 600) == 0, "negative origin clamps");
    CHECK(x == 0 && y == 0 && w == 25 && h == 35, "negative origin shrinks size");
    x = 790; y = 590; w = 30; h = 30;
    CHECK(vga_fx_clamp_rect(&x, &y, &w, &h, 800, 600) == 0, "overflow clamps");
    CHECK(w == 10 && h == 10, "overflow shrinks to framebuffer");
    x = 0; y = 0; w = 0; h = 10;
    CHECK(vga_fx_clamp_rect(&x, &y, &w, &h, 800, 600) != 0, "zero width rejected");
    x = 900; y = 0; w = 10; h = 10;
    CHECK(vga_fx_clamp_rect(&x, &y, &w, &h, 800, 600) != 0, "offscreen rejected");
    CHECK(vga_fx_clamp_rect(0, &y, &w, &h, 800, 600) != 0, "null x rejected");

    if (failures == 0) {
        printf("fx: ok (melt columns mirror f_wipe.c)\n");
    }
    return failures ? 1 : 0;
}
