/** Docstring: Host test for headers/wm_jelly.h (make test-jelly).
 *
 * Covers the wobbly-window spring mesh: a still mesh stays at rest, a move
 * displaces nodes against the motion with the grab point pinned, the spring
 * pulls every node home and settles within the frame budget, displacement
 * stays inside the configured clamp, sampling is bilinear and exact on
 * nodes, the settle verdict only holds when displacement and velocity are
 * both below their thresholds, and null or degenerate input fails closed.
 */

#include <stdio.h>

#include "wm_jelly.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

static int absi(int v)
{
    return v < 0 ? -v : v;
}

int main(void)
{
    wm_jelly_config_t cfg = WM_JELLY_CONFIG_DEFAULT;
    wm_jelly_t j;
    int ox, oy, i, frames, peak;

    CHECK(cfg.grid == WM_JELLY_GRID, "config carries grid");
    CHECK(cfg.max_px > 0, "config carries clamp");
    CHECK(cfg.impulse > 0 && cfg.impulse <= WM_JELLY_WEIGHT_ONE, "config carries impulse");
    CHECK(cfg.max_frames > 0, "config carries settle budget");

    wm_jelly_reset(&j);
    CHECK(wm_jelly_at_rest(&cfg, &j), "fresh mesh is at rest");
    wm_jelly_sample(&j, 10, 10, 100, 100, &ox, &oy);
    CHECK(ox == 0 && oy == 0, "fresh mesh samples zero");

    wm_jelly_reset(0);
    wm_jelly_kick(0, &cfg, 5, 5, 0, 0, 10, 10);
    wm_jelly_kick(&j, 0, 5, 5, 0, 0, 10, 10);
    wm_jelly_step(0, &j);
    wm_jelly_step(&cfg, 0);
    CHECK(wm_jelly_at_rest(0, &j) == 1, "null cfg reports rest");
    CHECK(wm_jelly_at_rest(&cfg, 0) == 1, "null mesh reports rest");
    wm_jelly_sample(0, 1, 1, 10, 10, &ox, &oy);
    wm_jelly_sample(&j, 1, 1, 0, 10, &ox, &oy);
    CHECK(ox == 0 && oy == 0, "degenerate sample yields zero");

    wm_jelly_kick(&j, &cfg, 20, 0, 0, 0, 200, 100);
    CHECK(!wm_jelly_at_rest(&cfg, &j), "a move wakes the mesh");
    wm_jelly_sample(&j, 0, 0, 200, 100, &ox, &oy);
    CHECK(ox == 0 && oy == 0, "grab corner stays pinned");
    wm_jelly_sample(&j, 199, 99, 200, 100, &ox, &oy);
    CHECK(ox < 0, "far corner lags against a rightward move");
    CHECK(absi(ox) <= cfg.max_px, "lag stays inside the clamp");

    wm_jelly_reset(&j);
    wm_jelly_kick(&j, &cfg, 0, -20, 199, 99, 200, 100);
    wm_jelly_sample(&j, 0, 0, 200, 100, &ox, &oy);
    CHECK(oy > 0, "far corner lags against an upward move");

    wm_jelly_reset(&j);
    wm_jelly_kick(&j, &cfg, 20, -10, 0, 0, 200, 100);
    CHECK(j.vx[WM_JELLY_GRID * WM_JELLY_GRID - 1] < 0, "a move launches far nodes against it (x)");
    CHECK(j.vy[WM_JELLY_GRID * WM_JELLY_GRID - 1] > 0, "a move launches far nodes against it (y)");
    CHECK(j.vx[0] == 0 && j.vy[0] == 0, "the pinned node gets no launch");

    wm_jelly_reset(&j);
    wm_jelly_kick(&j, &cfg, 20, 20, 199, 99, 200, 100);
    wm_jelly_sample(&j, 199, 99, 200, 100, &ox, &oy);
    CHECK(ox == 0 && oy == 0, "grab at the far corner stays pinned");
    wm_jelly_sample(&j, 0, 0, 200, 100, &ox, &oy);
    CHECK(ox < 0 && oy < 0, "origin lags against motion when the grab is far");

    wm_jelly_reset(&j);
    j.dx[5] = cfg.max_px << WM_JELLY_FP;
    j.dy[5] = -(cfg.max_px << WM_JELLY_FP);
    j.vx[5] = 20000;
    j.vy[5] = -20000;
    wm_jelly_step(&cfg, &j);
    CHECK(j.dx[5] <= (cfg.max_px << WM_JELLY_FP), "step clamps outward x velocity");
    CHECK(j.dy[5] >= -(cfg.max_px << WM_JELLY_FP), "step clamps outward y velocity");
    j.dx[5] = -(cfg.max_px << WM_JELLY_FP);
    j.dy[5] = cfg.max_px << WM_JELLY_FP;
    j.vx[5] = -20000;
    j.vy[5] = 20000;
    wm_jelly_step(&cfg, &j);
    CHECK(j.dx[5] >= -(cfg.max_px << WM_JELLY_FP), "step clamps negative x");
    CHECK(j.dy[5] <= (cfg.max_px << WM_JELLY_FP), "step clamps positive y");

    wm_jelly_reset(&j);
    wm_jelly_kick(&j, &cfg, 1000, 1000, 0, 0, 200, 100);
    peak = 0;
    for (i = 0; i < WM_JELLY_GRID * WM_JELLY_GRID; i++) {
        if (absi(j.dx[i]) > peak) peak = absi(j.dx[i]);
        if (absi(j.dy[i]) > peak) peak = absi(j.dy[i]);
    }
    CHECK(peak <= (cfg.max_px << WM_JELLY_FP), "huge kick is clamped");

    wm_jelly_reset(&j);
    wm_jelly_kick(&j, &cfg, 40, 40, 0, 0, 200, 100);
    wm_jelly_kick(&j, &cfg, 40, 40, 0, 0, 200, 100);
    peak = 0;
    for (i = 0; i < WM_JELLY_GRID * WM_JELLY_GRID; i++) {
        if (absi(j.dx[i]) > peak) peak = absi(j.dx[i]);
        if (absi(j.dy[i]) > peak) peak = absi(j.dy[i]);
    }
    CHECK(peak <= (cfg.max_px << WM_JELLY_FP), "accumulated kicks stay clamped");

    wm_jelly_reset(&j);
    wm_jelly_kick(&j, &cfg, 20, 10, 0, 0, 200, 100);
    wm_jelly_sample(&j, 199, 99, 200, 100, &ox, &oy);
    CHECK(ox == (j.dx[WM_JELLY_GRID * WM_JELLY_GRID - 1] + 128) >> WM_JELLY_FP, "corner sample equals its node (x)");
    CHECK(oy == (j.dy[WM_JELLY_GRID * WM_JELLY_GRID - 1] + 128) >> WM_JELLY_FP, "corner sample equals its node (y)");
    wm_jelly_sample(&j, 199, 0, 200, 100, &ox, &oy);
    CHECK(ox == (j.dx[WM_JELLY_GRID - 1] + 128) >> WM_JELLY_FP, "top-right sample equals its node");

    wm_jelly_reset(&j);
    wm_jelly_kick(&j, &cfg, 30, 12, 0, 0, 200, 100);
    for (frames = 0; frames < cfg.max_frames && !wm_jelly_at_rest(&cfg, &j); frames++) {
        wm_jelly_step(&cfg, &j);
    }
    CHECK(wm_jelly_at_rest(&cfg, &j), "mesh settles within the budget");
    CHECK(frames > 3, "settling is a visible motion, not a snap");
    wm_jelly_sample(&j, 199, 99, 200, 100, &ox, &oy);
    CHECK(absi(ox) <= 1 && absi(oy) <= 1, "settled mesh samples near zero");

    wm_jelly_reset(&j);
    wm_jelly_kick(&j, &cfg, 30, 0, 0, 0, 200, 100);
    {
        int crossed = 0, prev, now;
        wm_jelly_sample(&j, 199, 50, 200, 100, &prev, &oy);
        for (i = 0; i < cfg.max_frames; i++) {
            wm_jelly_step(&cfg, &j);
            wm_jelly_sample(&j, 199, 50, 200, 100, &now, &oy);
            if ((prev < 0 && now > 0) || (prev > 0 && now < 0)) crossed = 1;
            if (now != 0) prev = now;
        }
        CHECK(crossed, "jelly overshoots: it wobbles instead of creeping");
    }

    wm_jelly_reset(&j);
    wm_jelly_kick(&j, &cfg, 24, 0, 0, 0, 200, 100);
    for (i = 0; i < 3; i++) wm_jelly_step(&cfg, &j);
    wm_jelly_sample(&j, 100, 0, 200, 100, &ox, &oy);
    {
        int mid = ox;
        wm_jelly_sample(&j, 199, 0, 200, 100, &ox, &oy);
        CHECK(absi(ox) >= absi(mid), "lag grows with distance from the grab");
    }

    wm_jelly_reset(&j);
    j.dx[5] = 3 << WM_JELLY_FP;
    CHECK(!wm_jelly_at_rest(&cfg, &j), "residual displacement is not rest");
    j.dx[5] = 0;
    j.vy[7] = 3 << WM_JELLY_FP;
    CHECK(!wm_jelly_at_rest(&cfg, &j), "residual velocity is not rest");
    j.vy[7] = 0;
    j.vx[7] = 3 << WM_JELLY_FP;
    CHECK(!wm_jelly_at_rest(&cfg, &j), "residual x velocity is not rest");
    j.vx[7] = 0;
    j.dy[9] = 3 << WM_JELLY_FP;
    CHECK(!wm_jelly_at_rest(&cfg, &j), "residual y displacement is not rest");

    wm_jelly_reset(&j);
    wm_jelly_kick(&j, &cfg, 16, 0, 0, 0, 90, 90);
    {
        wm_jelly_t k = j;
        wm_jelly_step(&cfg, &j);
        wm_jelly_step(&cfg, &k);
        CHECK(j.dx[3] == k.dx[3] && j.vx[3] == k.vx[3], "stepping is deterministic");
    }

    if (failures) {
        fprintf(stderr, "%d failure(s)\n", failures);
        return 1;
    }
    printf("jelly: all checks passed\n");
    return 0;
}
