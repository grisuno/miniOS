# Wayland-mini user guide

`wlcomp` is the Wayland-mini compositor: up to 8 client surfaces with
focus z-order, presenting through the existing kernel compositor
(`GFX_PRESENT` with `BUF_NK`). Clients speak the wire
(`wl_hdr_encode`, attach/commit messages) framed through mailbox
files under `/shm/wl`, one message per file, with raw pixels beside
them; the wire format matches Wayland (u32 object id, u16 opcode, u16
size, then args) with fail-closed bounds (`WL_ERR_*`, never
truncation).

## Commands

```
miniOS> wlcomp --selftest     # headless: wlcomp: frame ok (800x360)
miniOS> wlcomp                 # visible: 2 surfaces on the desktop
miniOS> wlcomp --server        # interactive desktop: click focuses,
                               # drag moves, t re-tiles, ESC quits
miniOS> wlcomp --client red stripe   # attach a surface from a client
miniOS> wlcomp --once          # drain once for scripts
miniOS> wlcomp --clean         # unlink the mailbox directory
miniOS> freedom_wl --once <url>  # graphical browser, now a wl_mini client
```

`wlcomp` without arguments is the visible proof: it builds two demo
surfaces, tiles them side by side with `wl_comp_layout_tile`,
software-composites generated stripe and checker pixels with
`wlcomp_blit` into the NK back-buffer in desktop palette indices (bg 1,
border 9, so the desktop behind never recolors), uploads the shared
hybrid palette (`progs/nk_palette.h`, the same table every NK-window
app uses, which is what keeps true-color modes from rendering the
gray ramp), titles the window `wlcomp` and presents through
`GFX_PRESENT BUF_NK`. `wlcomp: presented 2 surfaces (800x360)` plus a
climbing `gfx frames` counter prove the composite landed; the BDD
scenario pins both lines.

`wlcomp --server` is the functional desktop: it owns the display,
drains client mailboxes, focuses on click, drags the focused surface
(`wl_comp_set_rect`), re-tiles on `t` and quits on ESC with the
desktop redrawn. `make wl` boots the desktop in one step (`tools/boot_wl.py` over
`os.img`): mailbox clean, mirror flag, three real app frames
(`paint`, `vedit`, `nuklear` selftests, strictly sequential),
one terminal-pattern client, server in background, console attached
for interactive use. Headless CI gets the same desktop plus a
screendump instead:

```
miniOS$ make wl
miniOS$ WL_HEADLESS=1 WL_SHOT=/tmp/wl.png make wl
```

Every NK app mirrors through one choke point
(`nk_sys_nk_frame` in `progs/nuklear/nuklear_minios.c`): when
`/shm/wl/mirror` exists, every 8th present also publishes the
backbuffer plus a six-message session under the program's own box
name, best-effort and never failing the present. `file` has no
headless frame to mirror (its selftest never presents), so it joins
the desktop only in live mode. Live multi-app concurrency stays
gated on the honest-limits race note in `CLAUDE.md`: setup steps
never overlap, each program runs alone and exits before the next
starts.

`wlcomp --once` drains once and exits so scripts
prove multiprocess composition through `gfx frames`:

```
miniOS> wlcomp --client stripe0 stripe
miniOS> wlcomp --client checker0 checker
miniOS> wlcomp --once     # wlcomp: mapped 2 surfaces (800x360)
```

`freedom_wl` allocates its logical surface id through `wl_mini`
(`freedom_wl_surface_id`, validated by `wl_surface_id_valid`) and
roundtrips the attach/commit wire (`freedom_wl_surface_attach`) while
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
