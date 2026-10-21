# WM Layout Specification

I describe the window layout contract I implement for the MiniOS desktop.
I write this before I change code so behavior stays verifiable.

## Problem

I observe three gaps in the current manager. The tiling contract in
`wm_tiling.h` covers only two terminals in fixed splits. The graphics
window is a special case parked to one side instead of a first class
window. Resize and fullscreen apply only to terminals, so Alt+Enter
behaves differently depending on focus. Each desktop repaint clears the
whole framebuffer, which I read as the main flicker source during drag
and tile operations.

## Goal

I provide one layout engine that treats every window equally, supports
bspwm style binary splits plus tile, cascade and fibonacci orders, keeps
drag for pointer users, reduces full repaints, and makes Alt+Enter mean
fullscreen on whichever window holds focus.

## Scope

I cover geometry planning only. I do not move pixel code. The kernel
keeps owning framebuffer writes. I compute rectangles in character cells
for terminals and in pixels for graphics placement hints. Hit testing,
focus rotation and paint order stay in their existing contracts.

## Contracts

I add `wm_layout.h` as the single owner of layout decisions.

I define `wm_layout_mode_t` with `TILE`, `BSP`, `CASCADE`, `FIBONACCI`
and `FULLSCREEN`. I define `wm_layout_window_t` with kind, id, a present
flag and the minimum columns and rows a window needs. I define
`wm_layout_config_t` with gap, the cascade step in columns and rows, and
the fibonacci ratio as a numerator over a denominator. Every numeric
choice arrives through that config. I expose no bare constant.

I expose `wm_layout_compute` which takes the window list, the mode, the
focused id and the screen grid and returns one cell per present window in
input order, absent windows skipped. I expose `wm_layout_fullscreen_cell`
which returns the full-grid cell; `wm_layout_compute` is what gives it to
the focused window. I fail closed: null pointers, zero windows, zero
grid or a full output buffer return zero and write nothing.

## Behavior

In `TILE` I split the grid evenly across the window count on the long
axis, which matches the legacy two terminal split exactly. In `BSP` I
split the longer remaining axis in half at every step, so a third window
does not collapse the first two. In `CASCADE` I offset each window by
the configured step so titles stay visible. In `FIBONACCI` I carve each
next window from the remaining strip by the configured ratio, which gives
the spiral feel without floating point. In `FULLSCREEN` I return one cell
covering the grid for the focused window only.

The legacy `wm_tile_layout` keeps its own signature and its own two
terminal split in `wm_tiling.h`, so its callers and vectors do not break;
the kernel tiles through `wm_layout_compute`.

## Fullscreen uniformity

I treat Alt+Enter as fullscreen on focus: the shared combo table maps
`Alt+Enter` to `WM_COMBO_FULLSCREEN`, and `vga_fb_toggle_fullscreen`
answers it for whichever window holds focus. A terminal fullscreen fills
the grid in cells. A graphics fullscreen switches to the `fullscreen`
graphics view: the frame fills the display, the title disappears and the
content is centered inside it. Exit restores the previous view mode.

The `FULLSCREEN` layout mode is the layout contract's own mode: I give
the full grid to the focused window and an empty cell to the rest, and
the kernel reaches it through the layout mode API (`wm layout`), never
through the combo.

## Resize

I express resize as cell delta plus clamp to minimum and grid bounds.
Terminals resize in cells. The graphics window does not resize at all: its
backbuffer is fixed size, so `vga_fb_resize` refuses the request and
only the terminal cells move, never a framebuffer write.

## Flicker reduction

I reduce repaints by contract, not by pixels. The layout engine reports
whether the plan changed. The kernel skips `vga_fb_draw_desktop` when the
plan is identical to the previous frame. Drag coalesces to cell changes:
pointer motion that stays inside the same cell produces no new plan.
This keeps drag smooth without touching the rasterizer.

## Verification

I extend `tests/test_wm.c` with vectors for each mode, odd grids, empty
input, null output and fullscreen uniformity. I run `make test-wm` host
side. I run `tools/wm_scoped.sh` for touched objects with zero warnings.
I prove pixels with `tools/test_gui_wm.py`. Full `test_bdd.sh` and
`mutate.sh` run once at the end of the todo list because they take hours.

## Risks

I keep the window count at two terminals plus one graphics window. The
layout entry point accepts up to eight windows, so the contract does not
hardcode that bound, but the kernel still allocates two terminal slots
plus the graphics window. I do not change the 8x8 font geometry. I do not
change syscall numbers.
