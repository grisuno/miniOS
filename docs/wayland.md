# Wayland-mini user guide

`wlcomp` is the Wayland-mini compositor: up to 8 client surfaces with
focus z-order, presenting through the existing kernel compositor
(`GFX_PRESENT` with `BUF_NK`). Clients speak the wire
(`wl_hdr_encode`, attach/commit messages) framed through mailbox
files under `/shm/wl`, one message per file, with raw pixels beside
them; the wire format matches Wayland (u32 object id, u16 opcode, u16
size, then args) with fail-closed bounds (`WL_ERR_*`, never
truncation). Input flows back server-to-client through fixed `.ev`
frames, so a focused window owns mouse and keys exactly like a real
Wayland compositor.

## Commands

```
miniOS> desktop                # one-command Wayland session from make run:
                               # flags + wlcomp --server in background
miniOS> desktop status         # mirror/client flags + server pid state
miniOS> desktop stop           # clean quit (text mode returns)
miniOS> mrun paint &           # live client windows tile beside the shell
miniOS> jobs                   # server + clients as preemptive jobs
miniOS> wlcomp --selftest     # headless: wlcomp: frame ok (800x360)
miniOS> wlcomp                 # visible: 2 surfaces on the desktop
miniOS> wlcomp --server        # interactive desktop (same as desktop,
                               # foreground; desktop backgrounds it)
miniOS> wlcomp --client red stripe   # attach a surface from a client
miniOS> wlcomp --once          # drain once for scripts
miniOS> wlcomp --clean         # unlink the mailbox directory
miniOS> freedom_wl --once <url>  # graphical browser, now a wl_mini client
```

A plain `make run` boot plus one `desktop` is the multitasking
Wayland session: click focuses (active title paints bright), title
drag moves, rim drag resizes, the close box closes (kill a live
client's job too, it re-attaches otherwise), `t` re-tiles, `m`/`u`
minimize/restore, `q` quits. Server shortcuts are Alt-held
(`Alt+T/M/U/Q`) so plain keys always reach the focused client; `ESC`
belongs to the app. `desktop stop` quits through the quit flag
because a background job owns no console to hear keys on.

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

Every NK app (`paint`, `vedit`, `file`, `nuklear`, `doomedit`,
`piano`) joins through one choke point
(`progs/nuklear/nuklear_minios.c`):

- Mirror (no server needed): when `/shm/wl/mirror` exists, every 8th
  present also publishes the backbuffer plus a six-message session
  under the program's own box name, best-effort and never failing
  the present. `file` has no headless frame to mirror (its selftest
  never presents), so it joins the desktop only in live mode.
- Client mode (server running): when `/shm/wl/client` exists, the
  app never takes the display (`VGA_MODE` ignored, no direct
  present) and never touches PS/2. Pixels publish damage-tracked (an
  FNV over the backbuffer, heartbeat every 32nd frame, so an idle
  window costs zero fs churn) under a pid-unique box
  (`wl_client_box`: lowercase program plus pid, so two paints never
  share a mailbox), and input arrives from its `.ev` file
  (`nk_client_poll` feeds scancodes through the app's own translator
  plus mapped pointer/wheel). Boxes, frames and the map helper are
  pure and host-tested (`wl_ev_encode/decode`, `wl_ev_map`,
  `wl_client_box`).

## Limits (live clients)

Live big clients (`paint`, `file`, `nuklear`, ...) fault at spawn
while the server runs (`EXCEPTION 0e`, NX fetch into `.rodata` at
startup, exit `-14`), while small ELFs (`fib`, exit 55) spawn fine
and the same big apps spawn fine with no server. The fault precedes
`main` (pristine stack, wild jump), hits the legacy and isolated
loaders alike (the legacy whole-load `cli` does not save it), and
matches the documented open audit layer in `CLAUDE.md` (preempt
park/resume under sustained overlap): a constantly-READY server
makes every tick context-switch, and big-image spawn/entry windows
are wide enough to always catch one. Until that layer lands, run
heavyweights sequentially (each alone, as `make wl` does) and treat
the `desktop` + live-client combo as the integration target, not
yet the demo path. Static clients (`--client`, selftest mirrors,
`--once`) tile perfectly and are the stable proof today.

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
