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


    {
        vga_fx_motion_t m = VGA_FX_MOTION_DEFAULT;
        int heat, base, prog, r, lx, ly, ok;
        int dy, left, width, pdy, prev_ok;
        int thr_lo, thr_hi;

        CHECK(vga_fx_burn_span(&m) == VGA_FX_PROG_ONE, "burn span fills the progress scale");
        CHECK(vga_fx_smooth(-1) == 0 && vga_fx_smooth(0) == 0, "smooth clamps low");
        CHECK(vga_fx_smooth(VGA_FX_PROG_ONE) == VGA_FX_PROG_ONE &&
              vga_fx_smooth(VGA_FX_PROG_ONE * 2) == VGA_FX_PROG_ONE, "smooth clamps high");
        CHECK(vga_fx_smooth(VGA_FX_PROG_ONE / 2) == VGA_FX_PROG_ONE / 2, "smooth midpoint");
        CHECK(vga_fx_smooth(VGA_FX_PROG_ONE / 4) < VGA_FX_PROG_ONE / 4, "smooth eases in");
        ok = 1;
        for (prog = 1; prog <= VGA_FX_PROG_ONE; prog++) {
            if (vga_fx_smooth(prog) < vga_fx_smooth(prog - 1)) {
                ok = 0;
            }
        }
        CHECK(ok, "smooth is monotonic");

        CHECK(vga_fx_noise(5, 5, 0, 1UL) == 0, "noise rejects a zero cell");
        CHECK(vga_fx_noise(-1, 5, 8, 1UL) == 0, "noise rejects negative x");
        ok = 1;
        for (ly = 0; ly < 64; ly++) {
            for (lx = 0; lx < 64; lx++) {
                int n = vga_fx_noise(lx, ly, 14, m.seed);
                if (n < 0 || n > 255 || n != vga_fx_noise(lx, ly, 14, m.seed)) {
                    ok = 0;
                }
            }
        }
        CHECK(ok, "noise stays in range and is deterministic");
        CHECK(vga_fx_noise(7, 9, 14, 1UL) != vga_fx_noise(7, 9, 14, 2UL) ||
              vga_fx_noise(70, 90, 14, 1UL) != vga_fx_noise(70, 90, 14, 2UL), "noise follows the seed");

        CHECK(vga_fx_burn_threshold(0, 0, 0, 10, 10) == 0, "threshold null cfg fails closed");
        CHECK(vga_fx_burn_threshold(&m, 10, 0, 10, 10) == 0, "threshold out of range fails closed");
        thr_lo = vga_fx_burn_threshold(&m, 20, 199, 100, 200);
        thr_hi = vga_fx_burn_threshold(&m, 20, 0, 100, 200);
        CHECK(thr_lo < m.burn_jitter, "bottom row ignites first");
        CHECK(thr_hi >= m.burn_rise * 199 / 200, "top row ignites last");
        ok = 1;
        for (ly = 0; ly < 200; ly++) {
            for (lx = 0; lx < 100; lx++) {
                int t = vga_fx_burn_threshold(&m, lx, ly, 100, 200);
                if (t < 0 || t + m.burn_band > VGA_FX_PROG_ONE) {
                    ok = 0;
                }
            }
        }
        CHECK(ok, "every ignition finishes inside the progress scale");

        base = vga_fx_burn_pixel(&m, 500, 0, &heat);
        CHECK(base == 0 && heat == 0, "before the glow the old pixel is untouched");
        base = vga_fx_burn_pixel(&m, 500, 500 - m.burn_glow / 2, &heat);
        CHECK(base == 0 && heat > 0 && heat < m.burn_ember, "glow tints the old pixel");
        base = vga_fx_burn_pixel(&m, 500, 500, &heat);
        CHECK(base == 0 && heat == m.burn_ember, "ignition starts at the ember heat");
        base = vga_fx_burn_pixel(&m, 500, 500 + m.burn_band / 4, &heat);
        CHECK(base == 1 && heat >= VGA_FX_HEAT_MAX - 1, "peak flame switches to the new pixel");
        base = vga_fx_burn_pixel(&m, 500, 500 + m.burn_band - 1, &heat);
        CHECK(base == 1 && heat < 10, "flame cools to nothing");
        base = vga_fx_burn_pixel(&m, 500, 500 + m.burn_band, &heat);
        CHECK(base == 1 && heat == 0, "after the band the new pixel shows clean");
        base = vga_fx_burn_pixel(&m, 500, VGA_FX_PROG_ONE, &heat);
        CHECK(base == 1, "burn ends on the new frame");
        CHECK(vga_fx_burn_pixel(0, 500, 0, &heat) == 1, "burn null cfg shows the new frame");

        CHECK(vga_fx_fire_color(-5) == vga_fx_fire_color(0), "fire colour clamps low");
        CHECK(vga_fx_fire_color(900) == vga_fx_fire_color(VGA_FX_HEAT_MAX), "fire colour clamps high");
        CHECK(vga_fx_fire_color(0) == 0x3C0000u, "coldest ember is dark red");
        CHECK(vga_fx_fire_color(VGA_FX_HEAT_STEP * 2) == 0xFF7800u, "mid heat is orange");
        CHECK(((vga_fx_fire_color(VGA_FX_HEAT_MAX) >> 8) & 255u) > 240u, "hot core is nearly white");
        ok = 1;
        for (heat = 1; heat <= VGA_FX_HEAT_MAX; heat++) {
            if (((vga_fx_fire_color(heat) >> 8) & 255u) < ((vga_fx_fire_color(heat - 1) >> 8) & 255u)) {
                ok = 0;
            }
        }
        CHECK(ok, "green rises with heat");

        CHECK(vga_fx_mix(0x102030u, 0xF0E0D0u, 0) == 0x102030u, "mix alpha 0 keeps a");
        CHECK(vga_fx_mix(0x102030u, 0xF0E0D0u, 255) == 0xF0E0D0u, "mix alpha 255 gives b");
        CHECK(vga_fx_mix(0x000000u, 0xFEFEFEu, 128) == 0x7F7F7Fu, "mix halfway");
        CHECK(vga_fx_burn_compose(0xAABBCCu, 0) == 0xAABBCCu, "no heat keeps the base");
        CHECK(vga_fx_burn_compose(0xAABBCCu, VGA_FX_HEAT_MAX) == vga_fx_fire_color(VGA_FX_HEAT_MAX),
              "full heat is opaque flame");
        CHECK(vga_fx_burn_compose(0xAABBCCu, 60) != 0xAABBCCu, "low heat tints the base");

        CHECK(vga_fx_genie_row(0, 0, 0, 100, 100, 50, 300, 0, 0, &dy, &left, &width) != 0, "genie null cfg");
        CHECK(vga_fx_genie_row(&m, 0, 0, 100, 100, 50, 300, 100, 0, &dy, &left, &width) != 0, "genie row range");
        CHECK(vga_fx_genie_row(&m, 0, 0, 0, 100, 50, 300, 0, 0, &dy, &left, &width) != 0, "genie zero width");
        vga_fx_genie_row(&m, 40, 60, 200, 100, 400, 500, 30, 0, &dy, &left, &width);
        CHECK(dy == 90 && left == 40 && width == 200, "genie progress 0 leaves the window in place");
        vga_fx_genie_row(&m, 40, 60, 200, 100, 400, 500, 30, VGA_FX_PROG_ONE, &dy, &left, &width);
        CHECK(dy == 500 && width == m.genie_min_w && left + width / 2 == 400,
              "genie progress end lands every row at the target");
        vga_fx_genie_row(&m, 40, 60, 200, 100, 400, 500, 99, VGA_FX_PROG_ONE / 4, &dy, &left, &width);
        {
            int ty0, tw0;
            vga_fx_genie_row(&m, 40, 60, 200, 100, 400, 500, 0, VGA_FX_PROG_ONE / 4, &ty0, &left, &tw0);
            CHECK(dy - 159 > ty0 - 60, "bottom row leads the top row");
            CHECK(width < tw0, "bottom row narrows first");
        }
        vga_fx_genie_row(&m, 40, 60, 200, 100, 400, 100, 99, VGA_FX_PROG_ONE, &dy, &left, &width);
        CHECK(dy == 159, "a target above the window is held at its last row");

        ok = 1;
        for (prog = 0; prog <= VGA_FX_PROG_ONE; prog += 16) {
            prev_ok = 0;
            pdy = 0;
            for (r = 0; r < 100; r++) {
                vga_fx_genie_row(&m, 40, 60, 200, 100, 700, 590, r, prog, &dy, &left, &width);
                if (prev_ok && dy < pdy) {
                    ok = 0;
                }
                if (width < 1 || width > 200) {
                    ok = 0;
                }
                pdy = dy;
                prev_ok = 1;
            }
        }
        CHECK(ok, "genie rows stay ordered and widths bounded at every progress");
    }

    if (failures == 0) {
        printf("fx: ok (melt, burn and genie contracts)\n");
    }
    return failures ? 1 : 0;
}
