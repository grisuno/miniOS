# Wayland-mini user guide

`wlcomp` is the Wayland-mini compositor: up to 8 client surfaces with
focus z-order, presenting through the existing kernel compositor
(`GFX_PRESENT` with `BUF_NK`). Clients use `progs/wl/wl_mini.h`
(`wl_client_init`, `wl_client_surface`, `wl_client_pool`) instead of
raw syscalls; the wire format matches Wayland (u32 object id, u16
opcode, u16 size, then args) with fail-closed bounds (`WL_ERR_*`,
never truncation).

## Commands

```
miniOS> wlcomp --selftest     # headless: wlcomp: frame ok (800x360)
miniOS> wlcomp                 # visible: 2 surfaces on the desktop
miniOS> freedom_wl --once <url>  # graphical browser, now a wl_mini client
```

`wlcomp` without arguments is the visible proof: it builds two demo
surfaces (320x200 at 40,40 and 400x180 at 240,100, focus on top),
software-composites them with `wlcomp_render` into the NK back-buffer
in desktop palette indices (bg 1, border 9, so the desktop behind never
recolors), titles the window `wlcomp` and presents through
`GFX_PRESENT BUF_NK`. `wlcomp: presented 2 surfaces (800x360)` plus a
climbing `gfx frames` counter prove the composite landed; the BDD
scenario pins both lines.

`freedom_wl` allocates its logical surface id through `wl_mini`
(`freedom_wl_surface_id`, validated by `wl_surface_id_valid`) while
the present path stays `GFX_PRESENT BUF_NK`, so behavior is unchanged
and the adoption is testable on the host.

## Limits (frozen subset)

Interfaces: `wl_display`, `wl_registry`, `wl_compositor`,
`wl_surface`, `wl_shm`, `wl_shm_pool`, `wl_buffer`, `xdg_wm_base`,
`xdg_surface`, `xdg_toplevel`. Surfaces max `800x360`
(`MINIOS_NK_W/H`); messages max 4096 bytes; strings max 256 bytes.
Syscalls 243/244/245 (`WL_ATTACH`/`WL_COMMIT`/`WL_INPUT`) are reserved
in `progs/minios_abi.h` and unanswered (`-ENOSYS`) until Phase 2.

## Tests

```
make test-wl        # host wire + compositor state suite
make progs/bin/wlcomp.elf   # ring-3 guest binary (MiniFS)
```

Spec: `docs/wayland-mini.md`. Decision: `docs/adr/0024-wayland-mini.md`.
