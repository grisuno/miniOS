# ADR-0020: Window manager header contracts (`wm_*.h`)

Status: accepted

## Context

`kernel/vga_fb.c` (~2900 lines) owned terminal rendering, focus, drag,
desktop icons, taskbar, graphics compositing and cursor handling in one
file. Hit-testing was duplicated per window type (terminal versus
graphics title bars, scrollbar edges), the title height was a bare
`FONT_H` at every use site, and drag grabs lived in function-static
variables inside `vga_fb_mouse_tick`, so a focus change through
`tw_select` could never reset them and a stale grab leaked into the next
gesture. None of this logic was host-testable: every check required a
QEMU boot.

## Decision

Six header-only contracts, one file per contract, each with a
centralized config struct, integer-only and free of kernel dependencies
so they compile under both the freestanding kernel flags and the host
`CFLAGS_HOST`:

- `wm_geom.h`: every rectangle (title, content, scrollbar, clamp) via
  `wm_geom_config_t` derived once from `FONT_W`/`FONT_H`/`SCROLLBAR_W`.
  Degenerate rectangles fail closed.
- `wm_events.h`: click/release/scroll/move translation via
  `wm_event_config_t`, a stateless pure function over two mouse
  snapshots, so an interrupted gesture poisons nothing.
- `wm_window.h`: unified terminal/graphics model (`wm_window_t` with a
  kind tag), hit-testing, focus rotation and paint order. `tw_hit`
  delegates to it and gained the bounds check it was missing.
- `wm_render.h`: back-to-front composition plan (wallpaper, shortcuts,
  taskbar, terminals in paint order, graphics last) with a capacity
  bound that truncates instead of overrunning.
- `wm_tiling.h`: terminal cell layout in character units (split halves,
  vertical stack beside graphics, fullscreen single).
- `wm_focus.h`: validated focus transitions over an explicit state
  struct; `vga_fb_focus_next`/`vga_fb_focus_id` delegate id selection
  and refuse invalid targets.

`kernel/vga_fb.c` keeps owning the pixel work and kernel state (rings,
slots, offsets, cursor) and consumes the contracts at each decision
point. Drag grabs moved to file scope (`wm_dragging`, `wm_gdrag`) so
`tw_select` resets them on every focus change. One behavioral quirk was
fixed deliberately: a two-slot manager with an absent second terminal
plus an active graphics window used to fullscreen the terminal over the
graphics half; it now side-tiles like the single-terminal case.

## Consequences

No geometry or transition logic is duplicated: one definition per
rectangle, edge and rotation. The contracts are host-tested by
`tests/test_wm.c` (`make test-wm`, wired into `test-host` and both
`CLAUDE.md` validation gates), mutation-covered across title height,
containment edges, click/release confusion, paint order, layer order,
tiling splits (including odd widths) and focus validity, with null and
degenerate inputs failing closed. The kernel image budget is unchanged
in practice (`_kernel_end 0x3f86c0 < USER_LOAD_BASE`, 31040 bytes
spare). Live-boot proof is the existing `wm` BDD surface (split, list,
focus, tile, close), exercised over the serial console.
