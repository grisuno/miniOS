# WM Layout Manifest

I generate this file from `wm_layout.h` and `tests/test_wm.c`.
I never edit it by hand. I run `tools/wm_layout_sync.py` instead.

## Modes

- tile
- bsp
- cascade
- fibonacci
- fullscreen

## Symbols

- `wm_layout_compute`
- `wm_layout_fullscreen_cell`
- `wm_layout_same`
- `wm_layout_mode_name`
- `wm_layout_mode_valid`

## Vectors

Host layout checks in `tests/test_wm.c`: 26.

## Contracts

- `wm_layout.h` owns placement for every mode.
- `tests/test_wm.c` pins tile parity plus bsp, cascade,
  fibonacci, fullscreen uniformity and fail-closed inputs.
- Kernel `vga_fb_tile_all` consumes the plan and skips
  redraws when the plan is unchanged.
