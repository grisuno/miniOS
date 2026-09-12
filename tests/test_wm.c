/** Docstring: Host test for wm_geom.h and wm_events.h (make test-wm).
 *
 * Covers rectangle validity, containment boundaries, title content and
 * scrollbar constructors, hit-test parity with the legacy kernel
 * expressions, point clamping, click release scroll and move translation
 * order, null safety and degenerate input failing closed.
 */

#include <stdio.h>

#include "wm_geom.h"
#include "wm_events.h"
#include "wm_window.h"
#include "wm_render.h"
#include "wm_tiling.h"
#include "wm_focus.h"
#include "wm_layout.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

int main(void)
{
    wm_geom_config_t gcfg = WM_GEOM_CONFIG_DEFAULT;
    wm_event_config_t ecfg = WM_EVENT_CONFIG_DEFAULT;
    wm_rect_t r;
    wm_rect_t t;
    wm_rect_t c;
    wm_rect_t s;
    wm_mouse_t prev;
    wm_mouse_t curr;
    wm_event_t evt;
    int cx;
    int cy;

    CHECK(gcfg.font_w == 8, "geom config carries font width");
    CHECK(gcfg.font_h == 8, "geom config carries font height");
    CHECK(gcfg.scrollbar_w == 8, "geom config carries scrollbar width");
    CHECK(gcfg.title_h == 8, "geom config carries title height");
    CHECK(ecfg.left_mask == 1, "event config carries button mask");
    CHECK(ecfg.wheel_step == 3, "event config carries wheel step");

    r.x = 10;
    r.y = 20;
    r.w = 30;
    r.h = 40;
    CHECK(wm_rect_valid(&r) != 0, "populated rect is valid");
    CHECK(wm_rect_contains(&r, 10, 20) != 0, "top-left corner hits");
    CHECK(wm_rect_contains(&r, 39, 59) != 0, "bottom-right inside hits");
    CHECK(wm_rect_contains(&r, 40, 20) == 0, "right edge excludes");
    CHECK(wm_rect_contains(&r, 10, 60) == 0, "bottom edge excludes");
    CHECK(wm_rect_contains(&r, 9, 20) == 0, "left outside misses");
    r.w = 0;
    CHECK(wm_rect_valid(&r) == 0, "zero width invalid");
    CHECK(wm_rect_contains(&r, 10, 20) == 0, "zero width never hits");
    CHECK(wm_rect_valid(0) == 0, "null rect invalid");
    CHECK(wm_rect_contains(0, 10, 20) == 0, "null rect never hits");

    t = wm_title_bar_rect(&gcfg, 100, 50, 200);
    CHECK(t.x == 100 && t.y == 50, "title bar origin matches window");
    CHECK(t.w == 200 && t.h == 8, "title bar spans width with title height");
    CHECK(wm_hit_title_bar(&gcfg, 100, 50, 200, 150, 54) != 0, "title interior hits");
    CHECK(wm_hit_title_bar(&gcfg, 100, 50, 200, 150, 58) == 0, "below title misses");
    CHECK(wm_hit_title_bar(&gcfg, 100, 50, 200, 99, 54) == 0, "left of title misses");
    CHECK(wm_hit_title_bar(&gcfg, 100, 50, 200, 300, 54) == 0, "right of title misses");
    CHECK(wm_hit_title_bar(0, 100, 50, 200, 150, 54) == 0, "null config fails closed");

    c = wm_content_rect(&gcfg, 100, 50, 200, 100);
    CHECK(c.x == 100 && c.y == 58, "content starts below title");
    CHECK(c.w == 200 && c.h == 92, "content shrinks by title height");

    s = wm_scrollbar_rect(&gcfg, 100, 50, 200, 100);
    CHECK(s.x == 300, "scrollbar sits at content right edge");
    CHECK(s.y == 58, "scrollbar starts below title");
    CHECK(s.w == 8, "scrollbar width comes from config");
    CHECK(s.h == 100, "scrollbar height matches content");

    cx = -5;
    cy = 9999;
    wm_clamp_point(&cx, &cy, 800, 600);
    CHECK(cx == 0, "negative x clamps to zero");
    CHECK(cy == 599, "overflow y clamps to bound");
    wm_clamp_point(0, 0, 800, 600);
    wm_clamp_point(&cx, &cy, 0, 0);
    CHECK(cx == 0 && cy == 599, "degenerate framebuffer keeps point");

    prev.x = 10;
    prev.y = 10;
    prev.buttons = 0;
    prev.wheel = 0;
    prev.present = 1;
    curr.x = 10;
    curr.y = 10;
    curr.buttons = 1;
    curr.wheel = 0;
    curr.present = 1;
    evt = wm_translate_event(&ecfg, &prev, &curr);
    CHECK(evt.type == WM_EVT_CLICK, "rising edge translates to click");
    CHECK(wm_event_suppresses_drag(&evt) != 0, "click suppresses drag");

    evt = wm_translate_event(&ecfg, &curr, &prev);
    CHECK(evt.type == WM_EVT_RELEASE, "falling edge translates to release");
    CHECK(wm_event_suppresses_drag(&evt) == 0, "release keeps drag");

    curr.buttons = 0;
    curr.wheel = -1;
    evt = wm_translate_event(&ecfg, &prev, &curr);
    CHECK(evt.type == WM_EVT_SCROLL, "nonzero wheel translates to scroll");

    curr.wheel = 0;
    curr.x = 11;
    evt = wm_translate_event(&ecfg, &prev, &curr);
    CHECK(evt.type == WM_EVT_MOVE, "motion translates to move");

    evt = wm_translate_event(&ecfg, &prev, &prev);
    CHECK(evt.type == WM_EVT_NONE, "idle snapshots translate to none");

    curr.present = 0;
    evt = wm_translate_event(&ecfg, &prev, &curr);
    CHECK(evt.type == WM_EVT_NONE, "absent mouse translates to none");

    evt = wm_translate_event(&ecfg, 0, &curr);
    CHECK(evt.type == WM_EVT_NONE, "null prev fails closed");
    evt = wm_translate_event(&ecfg, &prev, 0);
    CHECK(evt.type == WM_EVT_NONE, "null curr fails closed");
    CHECK(wm_event_suppresses_drag(0) == 0, "null event never suppresses");

    CHECK(wm_is_click_edge(&ecfg, 0, 1) != 0, "click edge helper detects rise");
    CHECK(wm_is_click_edge(&ecfg, 1, 1) == 0, "click edge helper ignores hold");
    CHECK(wm_is_release_edge(&ecfg, 1, 0) != 0, "release helper detects fall");
    CHECK(wm_is_release_edge(&ecfg, 0, 0) == 0, "release helper ignores idle");
    CHECK(wm_is_click_edge(0, 0, 1) != 0, "null config keeps default mask");

    {
        wm_window_t term;
        wm_window_t gfx;
        wm_window_t hidden;
        int present[2] = { 1, 1 };
        int solo[2] = { 1, 0 };
        int order[2];
        int n;
        term.kind = WM_WIN_TERMINAL;
        term.id = 0;
        term.x = 100;
        term.y = 50;
        term.w = 200;
        term.h = 100;
        term.present = 1;
        term.minimized = 0;
        gfx.kind = WM_WIN_GRAPHICS;
        gfx.id = WM_WINDOW_GFX_ID;
        gfx.x = 240;
        gfx.y = 200;
        gfx.w = 320;
        gfx.h = 208;
        gfx.present = 1;
        gfx.minimized = 0;
        hidden = term;
        hidden.minimized = 1;
        CHECK(WM_WINDOW_GFX_ID == 2, "graphics id matches focus space");
        CHECK(WM_WINDOW_MAX_TERMS == 2, "window bound matches manager");
        CHECK(wm_window_active(&term) != 0, "present terminal is active");
        CHECK(wm_window_active(&hidden) == 0, "minimized window inactive");
        CHECK(wm_window_active(0) == 0, "null window inactive");
        CHECK(wm_window_contains(&term, 150, 80) != 0, "terminal body hits");
        CHECK(wm_window_contains(&term, 99, 80) == 0, "terminal outside misses");
        CHECK(wm_window_contains(&hidden, 150, 80) == 0, "minimized never hits");
        CHECK(wm_window_contains(0, 150, 80) == 0, "null never hits");
        CHECK(wm_window_title_hits(&gcfg, &term, 150, 54) != 0, "terminal title hits");
        CHECK(wm_window_title_hits(&gcfg, &term, 150, 80) == 0, "terminal body is not title");
        CHECK(wm_window_title_hits(&gcfg, &gfx, 300, 204) != 0, "graphics title hits");
        CHECK(wm_window_title_hits(&gcfg, &hidden, 150, 54) == 0, "minimized title misses");
        CHECK(wm_window_title_hits(0, &term, 150, 54) == 0, "null config title fails closed");
        CHECK(wm_focus_next_id(present, 2, 0, 0) == 1, "focus cycles terminals");
        CHECK(wm_focus_next_id(present, 2, 0, 1) == 0, "focus wraps terminals");
        CHECK(wm_focus_next_id(present, 2, 1, 1) == 2, "focus reaches graphics");
        CHECK(wm_focus_next_id(present, 2, 1, 2) == 0, "focus wraps from graphics");
        CHECK(wm_focus_next_id(solo, 2, 0, 0) == 0, "single window keeps focus");
        CHECK(wm_focus_next_id(0, 2, 0, 0) == 0, "null table keeps focus");
        n = wm_paint_order(present, 2, 1, order, 2);
        CHECK(n == 2, "paint order covers both");
        CHECK(order[0] == 0 && order[1] == 1, "paint order ends focused");
        n = wm_paint_order(solo, 2, 0, order, 2);
        CHECK(n == 1 && order[0] == 0, "paint order skips absent");
        CHECK(wm_paint_order(0, 2, 0, order, 2) == 0, "null table paints nothing");
    }

    {
        wm_render_config_t rcfg = WM_RENDER_CONFIG_DEFAULT;
        wm_render_item_t items[8];
        int present[2] = { 1, 1 };
        int solo[2] = { 1, 0 };
        int n;
        CHECK(rcfg.max_items == 8, "render config carries item bound");
        n = wm_build_render_plan(&rcfg, present, 2, 1, 0, items, 8);
        CHECK(n == 5, "plan covers chrome plus two terminals");
        CHECK(items[0].layer == WM_LAYER_WALLPAPER, "wallpaper paints first");
        CHECK(items[1].layer == WM_LAYER_SHORTCUTS, "shortcuts follow wallpaper");
        CHECK(items[2].layer == WM_LAYER_TASKBAR, "taskbar follows shortcuts");
        CHECK(items[3].layer == WM_LAYER_TERMINAL && items[3].id == 0, "unfocused terminal precedes focus");
        CHECK(items[4].layer == WM_LAYER_TERMINAL && items[4].id == 1, "focused terminal precedes graphics");
        n = wm_build_render_plan(&rcfg, present, 2, 1, 1, items, 8);
        CHECK(n == 6, "graphics appends one item");
        CHECK(items[5].layer == WM_LAYER_GRAPHICS && items[5].id == WM_WINDOW_GFX_ID, "graphics paints last");
        n = wm_build_render_plan(&rcfg, solo, 2, 0, 0, items, 8);
        CHECK(n == 4, "single terminal plan shrinks");
        CHECK(items[3].layer == WM_LAYER_TERMINAL && items[3].id == 0, "single plan keeps terminal");
        CHECK(wm_build_render_plan(&rcfg, 0, 2, 0, 0, items, 8) == 0, "null table builds nothing");
        CHECK(wm_build_render_plan(&rcfg, present, 2, 0, 0, 0, 8) == 0, "null items builds nothing");
        n = wm_build_render_plan(0, present, 2, 0, 0, items, 8);
        CHECK(n == 5, "null config keeps default bound");
        {
            wm_render_config_t small;
            small.max_items = 4;
            n = wm_build_render_plan(&small, present, 2, 1, 1, items, 8);
            CHECK(n == 4, "small bound truncates plan");
            CHECK(items[3].layer == WM_LAYER_TERMINAL, "truncation keeps back layers");
        }
    }

    {
        wm_tile_cell_t cells[2];
        int present[2] = { 1, 1 };
        int solo[2] = { 1, 0 };
        int n;
        n = wm_tile_layout(present, 2, 0, 80, 40, cells, 2);
        CHECK(n == 2, "dual layout covers both");
        CHECK(cells[0].x == 0 && cells[0].cols == 40, "dual left takes half");
        CHECK(cells[1].x == 40 && cells[1].cols == 40, "dual right takes rest");
        CHECK(cells[0].rows == 40 && cells[1].rows == 40, "dual keeps full height");
        n = wm_tile_layout(present, 2, 1, 80, 40, cells, 2);
        CHECK(n == 2, "gfx layout stacks terminals");
        CHECK(cells[0].rows == 20 && cells[1].rows == 20, "gfx stack splits rows");
        CHECK(cells[0].y == 0 && cells[1].y == 20, "gfx stack offsets second");
        n = wm_tile_layout(solo, 1, 0, 80, 40, cells, 2);
        CHECK(n == 1 && cells[0].fullscreen == 1, "single fills screen");
        n = wm_tile_layout(solo, 1, 1, 80, 40, cells, 2);
        CHECK(n == 1 && cells[0].cols == 40 && cells[0].fullscreen == 0, "single yields half to graphics");
        CHECK(wm_tile_layout(0, 2, 0, 80, 40, cells, 2) == 0, "null table lays nothing");
        CHECK(wm_tile_layout(present, 2, 0, 0, 40, cells, 2) == 0, "zero grid lays nothing");
        CHECK(wm_tile_layout(present, 2, 0, 80, 40, 0, 2) == 0, "null out lays nothing");
        n = wm_tile_layout(present, 2, 0, 81, 40, cells, 2);
        CHECK(n == 2, "odd grid covers both");
        CHECK(cells[0].cols == 40, "odd grid left floors half");
        CHECK(cells[1].cols == 41 && cells[1].x == 40, "odd grid right takes rest");
        n = wm_tile_layout(solo, 1, 1, 81, 40, cells, 2);
        CHECK(n == 1 && cells[0].cols == 40, "odd single yields floored half");
    }

    {
        wm_focus_state_t st;
        st.focus = 0;
        st.nterms = 2;
        st.present[0] = 1;
        st.present[1] = 1;
        st.present[2] = 0;
        st.present[3] = 0;
        st.gfx_active = 0;
        CHECK(wm_focus_selectable(&st, 0) != 0, "present terminal selectable");
        CHECK(wm_focus_selectable(&st, 2) == 0, "graphics blocked when inactive");
        CHECK(wm_focus_selectable(&st, 5) == 0, "out of range rejected");
        CHECK(wm_focus_selectable(0, 0) == 0, "null state rejects");
        CHECK(wm_focus_next(&st) == 1, "focus advances terminals");
        st.focus = 1;
        CHECK(wm_focus_next(&st) == 0, "focus wraps terminals");
        st.gfx_active = 1;
        CHECK(wm_focus_selectable(&st, 2) != 0, "graphics selectable when active");
        CHECK(wm_focus_next(&st) == 2, "focus reaches graphics");
        st.focus = 2;
        CHECK(wm_focus_next(&st) == 0, "focus wraps from graphics");
        CHECK(wm_focus_set(&st, 1) == 1, "valid set returns id");
        CHECK(wm_focus_set(&st, 5) == -1, "invalid set refused");
        st.gfx_active = 0;
        CHECK(wm_focus_set(&st, 2) == -1, "inactive graphics refused");
    }

    {
        int zone = -1;
        CHECK(wm_combo_lookup(1, 0, 0, 0, WM_SC_TAB, WM_PATH_COOKED, &zone) == WM_COMBO_FOCUS_NEXT, "alt tab cooked focuses");
        CHECK(wm_combo_lookup(1, 0, 0, 0, WM_SC_TAB, WM_PATH_RAW, &zone) == WM_COMBO_FOCUS_NEXT, "alt tab raw focuses");
        CHECK(wm_combo_lookup(0, 0, 1, 0, WM_SC_TAB, WM_PATH_COOKED, &zone) == WM_COMBO_TILE_ALL, "super tab cooked tiles");
        CHECK(wm_combo_lookup(0, 0, 1, 0, WM_SC_TAB, WM_PATH_RAW, &zone) == WM_COMBO_TILE_ALL, "super tab raw tiles");
        CHECK(wm_combo_lookup(1, 1, 0, 0, WM_SC_TAB, WM_PATH_COOKED, &zone) == WM_COMBO_NONE, "altgr blocks combo");
        CHECK(wm_combo_lookup(1, 0, 0, 1, WM_SC_UP, WM_PATH_COOKED, &zone) == WM_COMBO_SNAP, "alt arrows cooked snap");
        CHECK(wm_combo_lookup(1, 0, 0, 1, WM_SC_UP, WM_PATH_RAW, &zone) == WM_COMBO_NONE, "alt arrows raw stay game");
        CHECK(wm_combo_lookup(0, 0, 1, 1, WM_SC_LEFT, WM_PATH_RAW, &zone) == WM_COMBO_SNAP, "super arrows raw snap");
        CHECK(wm_combo_lookup(1, 0, 0, 0, WM_SC_M, WM_PATH_COOKED, &zone) == WM_COMBO_MINIMIZE, "alt m minimizes");
        CHECK(wm_combo_lookup(1, 0, 0, 0, WM_SC_X, WM_PATH_RAW, &zone) == WM_COMBO_CLOSE, "alt x raw closes");
        CHECK(wm_combo_lookup(1, 0, 0, 0, WM_SC_LBRACKET, WM_PATH_COOKED, &zone) == WM_COMBO_RESIZE_DEC_W, "alt bracket resizes");
        CHECK(wm_combo_lookup(1, 0, 0, 0, WM_SC_ZERO, WM_PATH_COOKED, &zone) == WM_COMBO_RESET, "alt zero resets");
        CHECK(wm_combo_lookup(0, 0, 0, 0, WM_SC_TAB, WM_PATH_COOKED, &zone) == WM_COMBO_NONE, "bare tab ignored");
        CHECK(wm_combo_lookup(1, 0, 0, 0, WM_SC_TAB, 0, &zone) == WM_COMBO_NONE, "bad path fails closed");
        zone = -1;
        CHECK(wm_combo_lookup(0, 0, 1, 1, WM_SC_HOME, WM_PATH_COOKED, &zone) == WM_COMBO_SNAP, "super home snaps");
        CHECK(zone == WM_SNAP_TOP_LEFT, "snap zone reports top left");
    }

    {
        wm_layout_config_t lcfg = WM_LAYOUT_CONFIG_DEFAULT;
        wm_layout_window_t one[1];
        wm_layout_window_t two[2];
        wm_layout_window_t three[3];
        wm_layout_cell_t cells[4];
        wm_layout_cell_t prev[4];
        wm_layout_cell_t solo;
        int n;
        CHECK(WM_LAYOUT_MODE_COUNT == 5, "layout carries five modes");
        CHECK(wm_layout_mode_valid(WM_LAYOUT_TILE) != 0, "tile mode valid");
        CHECK(wm_layout_mode_valid(WM_LAYOUT_FULLSCREEN) != 0, "fullscreen valid");
        CHECK(wm_layout_mode_valid(99) == 0, "bad mode invalid");
        CHECK(wm_layout_mode_name(WM_LAYOUT_BSP) != 0, "bsp name exists");
        CHECK(wm_layout_mode_name(99) == 0, "bad mode name null");
        one[0].kind = 1;
        one[0].id = 0;
        one[0].present = 1;
        one[0].min_cols = 1;
        one[0].min_rows = 1;
        two[0] = one[0];
        two[1] = one[0];
        two[1].id = 1;
        three[0] = one[0];
        three[1] = one[0];
        three[1].id = 1;
        three[2] = one[0];
        three[2].id = 2;
        n = wm_layout_compute(&lcfg, two, 2, WM_LAYOUT_TILE, 0, 80, 40, cells, 4);
        CHECK(n == 2, "tile dual covers both");
        CHECK(cells[0].cols == 40 && cells[1].cols == 40, "tile dual halves cols");
        CHECK(cells[0].x == 0 && cells[1].x == 40, "tile dual offsets second");
        n = wm_layout_compute(&lcfg, two, 2, WM_LAYOUT_TILE, 0, 81, 40, cells, 4);
        CHECK(n == 2 && cells[0].cols == 40 && cells[1].cols == 41, "tile odd keeps rest");
        n = wm_layout_compute(&lcfg, one, 1, WM_LAYOUT_TILE, 0, 80, 40, cells, 4);
        CHECK(n == 1 && cells[0].fullscreen == 1, "tile single fullscreen");
        n = wm_layout_compute(&lcfg, three, 3, WM_LAYOUT_BSP, 0, 80, 40, cells, 4);
        CHECK(n == 3, "bsp triple covers all");
        CHECK(cells[0].cols == 40, "bsp first takes half");
        CHECK(cells[1].x == 40, "bsp second starts at half");
        CHECK(cells[2].cols + cells[2].x == 80, "bsp cells stay in grid");
        n = wm_layout_compute(&lcfg, three, 3, WM_LAYOUT_CASCADE, 0, 80, 40, cells, 4);
        CHECK(n == 3, "cascade triple covers all");
        CHECK(cells[1].x > cells[0].x && cells[1].y > cells[0].y, "cascade offsets grow");
        n = wm_layout_compute(&lcfg, three, 3, WM_LAYOUT_FIBONACCI, 0, 80, 40, cells, 4);
        CHECK(n == 3, "fibonacci triple covers all");
        CHECK(cells[0].cols > 0 && cells[0].rows > 0, "fibonacci first valid");
        CHECK(cells[2].x + cells[2].cols <= 80, "fibonacci stays in cols");
        CHECK(cells[2].y + cells[2].rows <= 40, "fibonacci stays in rows");
        n = wm_layout_compute(&lcfg, two, 2, WM_LAYOUT_FULLSCREEN, 1, 80, 40, cells, 4);
        CHECK(n == 2, "fullscreen returns both slots");
        CHECK(cells[1].fullscreen == 1 && cells[1].cols == 80, "fullscreen focus fills");
        CHECK(cells[0].cols == 0, "fullscreen hides rest");
        CHECK(wm_layout_fullscreen_cell(80, 40, &solo) == 1, "fullscreen cell builds");
        CHECK(solo.cols == 80 && solo.fullscreen == 1, "fullscreen cell fills");
        CHECK(wm_layout_fullscreen_cell(0, 40, &solo) == 0, "zero grid fails closed");
        CHECK(wm_layout_fullscreen_cell(80, 40, 0) == 0, "null out fails closed");
        n = wm_layout_compute(&lcfg, two, 2, WM_LAYOUT_TILE, 0, 80, 40, cells, 4);
        CHECK(n == 2, "same compares stable plan");
        prev[0] = cells[0];
        prev[1] = cells[1];
        CHECK(wm_layout_same(cells, prev, 2) != 0, "identical plans match");
        cells[1].x = 41;
        CHECK(wm_layout_same(cells, prev, 2) == 0, "moved cell differs");
        CHECK(wm_layout_same(0, prev, 2) == 0, "null plan differs");
        CHECK(wm_layout_same(cells, prev, 0) != 0, "empty count matches");
        CHECK(wm_layout_compute(0, two, 2, WM_LAYOUT_TILE, 0, 80, 40, cells, 4) == 2, "null config keeps tile");
        CHECK(wm_layout_compute(&lcfg, two, 2, 99, 0, 80, 40, cells, 4) == 0, "bad mode lays nothing");
        CHECK(wm_layout_compute(&lcfg, 0, 2, WM_LAYOUT_TILE, 0, 80, 40, cells, 4) == 0, "null wins lays nothing");
        CHECK(wm_layout_compute(&lcfg, two, 2, WM_LAYOUT_TILE, 0, 0, 40, cells, 4) == 0, "zero grid lays nothing");
        CHECK(wm_layout_compute(&lcfg, two, 2, WM_LAYOUT_TILE, 0, 80, 40, 0, 4) == 0, "null out lays nothing");
        CHECK(wm_layout_compute(&lcfg, two, 2, WM_LAYOUT_TILE, 0, 80, 40, cells, 1) == 0, "small cap lays nothing");
    }

    if (failures == 0) {
        printf("wm: ok\n");
    }
    return failures != 0;
}
