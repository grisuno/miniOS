# ADR-0024: Wayland-mini subset and ring-3 compositor

Status: accepted (phased F0-F3, shim-first)

## Context

The desktop composites one GAME plus one NK window through the kernel
(`GFX_PRESENT`). FreeDom already ships a Wayland-to-MiniOS shim
(ADR-0019): surface becomes the NK back-buffer, present/title/pointer/
keyboard map to MiniOS syscalls. Real multi-window Wayland needs N
surfaces, a wire protocol, and a compositor, but the kernel has no
`AF_UNIX`/`SCM_RIGHTS` and must not grow a Weston. NovaOS shows the
shape (tiny client table over a socket), freedesktop `src/` shows what
NOT to port (epoll, shm fds, scanner runtime).

## Decision

Subset interfaces only: `wl_display`, `wl_registry`, `wl_compositor`,
`wl_surface`, `wl_shm`, `wl_shm_pool`, `wl_buffer`, `xdg_wm_base`,
`xdg_surface`, `xdg_toplevel`. One header contract
`progs/wl/wl_mini.h` (wire encode/decode, ids, opcodes, pool and
surface state, client helpers, compositor z-order), header-only like
`wm_geom.h`, host-tested by `make test-wl`. Transport starts as
`pipe()` + validated pool ids, never truncated fds. Compositor is the
ring-3 `bin/wlcomp` (max 8 surfaces, focus z-order, presents through
`GFX_PRESENT BUF_NK`, titles through `GFX_SET_TITLE`, input focus
follows the `vga_fb_ps2_owner` rule). Syscalls 243/244/245
(`WL_ATTACH`/`WL_COMMIT`/`WL_INPUT`) are reserved in `minios_abi.h`
outside the checksum; the ABI version moves only when the kernel
answers them. No layout address moves: surfaces reuse `MINIOS_NK_W/H`
bounds, no new pinned address.

## Proof

`make test-wl` pins wire roundtrip plus fail-closed bounds (liar size,
truncated opcode, wild object id, pool overflow). `wlcomp --selftest`
prints `wlcomp: frame ok (800x360)` and the existing `gfx frames`
counter proves composition. Mutants for the three reserved numbers and
the size check die in the host suite.

## Consequences

`freedom_wl` ports to `wl_mini` client helpers without changing its
fetch engine. Full `xdg-shell`, client decoration, DMA-BUF and real
`AF_UNIX` stay explicit later phases behind new ADRs. Kernel stays a
single-window compositor until Phase 2 wires the syscalls.
