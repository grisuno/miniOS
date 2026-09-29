# Wayland-mini compositor (wlcomp)

Moved verbatim from CLAUDE.md (2026-09-29 compaction); CLAUDE.md keeps the
rules and hazards and indexes this file.

### Wayland-mini compositor (`wlcomp`)
`bin/wlcomp` is the ring-3 Wayland-mini compositor from ADR-0024, built
exactly like the other static ELFs (host gcc `-static -no-pie`, MiniFS
with a bare-name alias, source beside it at `progs/wl/wlcomp.c`). The
wire contract is the header-only `progs/wl/wl_mini.h`: the subset
interfaces `wl_display`/`wl_registry`/`wl_compositor`/`wl_surface`/
`wl_shm`/`wl_shm_pool`/`wl_buffer` plus `xdg_wm_base`/`xdg_surface`/
`xdg_toplevel`, with encode/decode, ids, opcodes, pool and surface
state, client helpers and compositor z-order in one file, the same
header-only pattern as the `wm_*.h` contracts.

- The compositor holds at most 8 surfaces with focus z-order and
  presents through `GFX_PRESENT` with `BUF_NK` (titles through
  `GFX_SET_TITLE`), so no layout address moves: surfaces reuse the
  `MINIOS_NK_W/H` bounds and no new pinned address exists. Input focus
  follows the `vga_fb_ps2_owner` rule like every other graphics app.
  Transport starts as `pipe()` plus validated pool ids, never truncated
  fds. Syscalls 243/244/245 (`WL_ATTACH`/`WL_COMMIT`/`WL_INPUT`) stay
  reserved in `minios_abi.h` outside the checksum; the ABI version moves
  only when the kernel answers them, and the kernel stays a
  single-window compositor until that Phase 2 lands.
- I tile the surfaces in the compositor instead of overlapping them:
  `wl_comp_set_rect` moves and resizes one surface with validated
  geometry, `wl_comp_layout_tile` lays every mapped surface over the
  frame in z-order (one fills, two split vertically, three or more form
  a grid with the remainder absorbed), and `wlcomp_blit` composites
  real client pixels with clipping and a 1px border, falling back to
  the solid color when a client supplies no pixels. Geometry bounds
  live in one place (`WL_SURF_MAX_W/H`, reused by `wl_pool_fit`,
  layout and blit). Clients speak attach/commit over the wire
  (`wl_attach_encode/decode` for pool plus dimensions,
  `wl_commit_encode/decode` for the surface id, fail-closed on wild
  ids, oversize frames and truncation); `freedom_wl` proves adoption
  by roundtripping both messages in its selftest and host probe while
  its present path stays `GFX_PRESENT BUF_NK`. Bare `wlcomp` tiles two
  demo surfaces side by side with generated stripe and checker pixels
  instead of overlapping solid rects. Live cross-process transport
  over `pipe()` stays the open step: surfaces are in-compositor state
  and no shm bytes cross processes yet.
- I separate the session from the transport (ADR-0025): `wl_stream_t`
  reassembles messages split anywhere with a bounded buffer
  (`WL_ERR_MORE` asks for more bytes, a liar size kills the
  connection), `wl_iface_t` carries the hand-written descriptor tables
  for the ten interfaces, and `wl_dispatch` routes every subset
  request to the existing `wl_comp_*` operations, fail-closed on wild
  ids, unknown opcodes and short payloads. `wlcomp --selftest` drives
  a nine-message synthetic session fed in two chunks split mid-header.
  Either future carrier (kernel `pipe()` as new nr 22 handler, or
  MiniFS mailbox files as a zero-kernel interim) feeds the stream
  unchanged. The kernel audit behind this stands: no `pipe()`
  handler exists, sockets serve TCP only, and there is no `AF_UNIX`,
  `socketpair`, `SCM_RIGHTS` or `dup`, so live multi-process bytes
  are Fase 3, never assumed here.
- I carry live multiprocess bytes on mailbox files (ADR-0026):
  one wire message per file under `/shm/wl/<box>-<seq>.msg`
  (`WLMB` magic plus sequence), pixels beside it as `<box>.raw`
  sized by the last attach. The server drains at most
  `WL_MBOX_POLL_MAX` files per tick, validates every frame before
  dispatch, unlinks what it consumed and leaves torn writes for the
  next poll. One surface per connection bounds the server with no id
  translation table; routing (`wl_mbox_route`) and freshness
  (`wl_mbox_fresh`) stay pure and host-tested while stdio, `DIR_LIST`
  and `unlink` live in `wlcomp.c` and prove out live in the guest.
  The thin client `progs/wl/wl_client.h` owns the attach sequence
  (`wl_client_raw_file`, `wl_client_emit_file`, `wl_client_attach`)
  so every ring-3 program becomes a real multitasking client:
  `mrun a &`, `mrun b &`, then the server tiles both. `wlcomp` is a
  desktop now: `--server` owns the display, focuses on click, title
  drag moves, rim drag resizes through `wl_comp_set_rect`, close box
  closes through `wlserv_close` (slot plus raw unlinked for the next
  client), `t` re-tiles, `m` minimizes the focused window, `u`
  restores all, ESC quits; `--once` drains once for scripts;
  `--client` attaches from a second process; `--clean` clears the
  directory. Layout resizes cells while pixels arrive at attach size,
  so the server rescales on fit (`wl_scale_nearest`); a lying raw
  degrades to solid ink, never a torn frame. `make wl` boots this
  desktop directly (Fase 4, `tools/boot_wl.sh`).
- The 768-byte hybrid palette lived in three identical copies while
  the program that needed it most had none, which read as a glitch
  on truecolor VBE modes. It lives once in `progs/nk_palette.h`
  with the three call sites as thin wrappers, and `wlcomp` uploads
  it before every present like every other NK-window app.
- Proof: `make test-wl` (host, wire roundtrip plus fail-closed bounds:
  liar size, truncated opcode, wild object id, pool overflow, rect
  bounds, tile geometry, pixel blit, attach/commit roundtrip and wild
  pool/id on decode, split reassembly, nine-message session, iface
  table, mailbox names plus frames plus route plus freshness, palette
  bytes, scaler vectors),
  `wlcomp --selftest` prints `wlcomp: frame ok (800x360)`, and bare
  `wlcomp` composites two demo surfaces
  (`wlcomp: presented 2 surfaces (800x360)`, BDD-pinned beside the
  `gfx frames` climb). Live proof is `wlcomp --client` plus
  `wlcomp --once` beside the `gfx frames` climb from 0 to 1, and a
  headless QMP screendump carrying desktop-exact inks. Mutants for
  the three reserved numbers and the size check die in the host
  suite; nineteen scoped mutants over the header paths (layout
  columns, attach pool, blit border, commit id, rect fit, stream
  split, consume skip, short attach, create size, iface lookup,
  scale axes, mailbox magic, mailbox freshness, route commit, route
  short, chrome active, chrome close, chrome minimize, chrome zone)
  die in `make test-wl` via `tools/wl_scoped.sh`.
- Window chrome is protocol, not pixels: `wl_mini.h` owns the title
  geometry (`WL_TITLE_H`, `WL_CLOSE_W`, `WL_RESIZE_EDGE`), the
  desktop-exact inks (`WL_TITLE_ACTIVE`, `WL_TITLE_INACTIVE`,
  `WL_CLOSE_INK`), the hit zones (`WL_HIT_BODY/TITLE/CLOSE/RESIZE`)
  through `wl_surface_hit_zone`, the active flag through
  `wl_comp_refresh_active` (top-most mapped window paints bright),
  minimize through `wl_comp_set_minimized` (skips hit, tile and
  composite until restored), and `wlcomp_blit_chrome` (title plus
  close box plus content, small surfaces fall back to the legacy
  blit). The server hot loop never allocates: `wlserv_pool` plus two
  static scratch frames replace the old per-frame malloc, and a
  periodic stray sweep unlinks dead `.msg` files so crashed clients
  leave no orphans. Syscalls 243/244/245 stay reserved outside the
  checksum; the mailbox remains the zero-kernel transport.
- I run the desktop from a plain boot with one command: the `desktop`
  builtin writes the mirror+client flags and spawns `wlcomp --server`
  as a background job (`desktop status`/`stop` round it out; `stop`
  quits through the quit flag and clears session flags, and the shell
  clears stale client/quit flags once at boot so a reboot never
  blinds NK apps). Server shortcuts are Alt-held (`Alt+T/M/U/Q`) so
  plain keys always reach the focused client; `wlserv_push_ev` maps
  frame coords into raw-buffer coords (`wl_ev_map`) and serves a
  44-byte `.ev` frame per focused box with a queued scancode batch
  that clears after write (never replays). Every NK app speaks it
  through `progs/nuklear/nuklear_minios.c` with zero app-code
  changes: client mode skips the display takeover and PS/2, publishes
  damage-tracked pixels (FNV, heartbeat every 32nd frame) under a
  pid-unique box, and polls `.ev` for input. Host proof is `make
  test-wl` (ev roundtrip plus map plus box vectors); live proof is
  the `desktop` BDD scenario (up, jobs, stop, status).
- Per-process TLS base: every static glibc binary sets FSBASE once via
  `arch_prctl` and addresses its thread descriptor through `%fs` on
  every malloc, so the context switch used to resume each process with
  whatever TLS base the previous one left behind. I store one `fsbase`
  per `proc_t` (`PROC_FSBASE_OFF`, `PROC_T_SIZE` grew 320 to 328 with
  the static asserts proving it): `switch_to` saves the live base,
  `switch_to_notrap` restores the incoming one (full 64 bit split
  across `edx:eax`; the first revision reused the restored `rdx` as
  the high half and poisoned the MSR to `+4GB`, which is why the
  fault address read `0x1007723c0` for a base of `0x7723c0`), the
  preempt park saves it alongside the FPU image, and pid 0 plus the
  idle loop keep the live base since the kernel never addresses
  through `%fs`. The fault dumper prints `fs=` beside `gs=`/`kgs=`.
  This fixed the server dying beside a second process; small ELFs
  (`fib`, exit 55) and tiny live publishers multitask cleanly now.
- Live tiny clients (`progs/src/spin.c`, `bin/spin.elf`, nostdlib like
  `lxhello`, 9 KB, no libc/TLS/heap): `run spin.elf wl <box> <frames>
  &` attaches a 200x90 stripe surface and republishes a shifting
  stripe plus commit per frame with yield pacing, using only
  open/write/close/unlink syscalls and byte-identical wire to
  `wl_client_attach`. Two live clients plus the server run
  concurrently (`run spin.elf wl sa 30 &`, `run spin.elf wl sb 30 &`,
  both exit 43, `gfx frames` climbs to 36, `server done (2
  surfaces)` on stop). Console interleaving of two tick-mode spins
  proves the preemptive scheduler alongside it. `tools/wl_scoped.sh`
  pins the spin build with zero warnings.
- Honest ceiling, measured: spawning a big glibc ELF (`paint`, `file`,
  `wlcomp` itself, ~800 KB+) while the server runs still faults it at
  startup (`EXCEPTION 0e`, NX fetch into `.rodata`, exit `-14`)
  before `main`, while small ELFs (`fib`, exit 55) and the tiny live
  publishers above spawn fine and the same big apps spawn fine with
  no server (two paints concurrently: both ready, no fault). The TLS
  layer is closed (the victim now faults with `fs=0`, before its own
  `arch_prctl`, and its entry bytes verify intact at load), so the
  defect sits one layer deeper: first-schedule/entry of a
  glibc-heavy image under constant tick plus concurrent MiniFS
  traffic from the server drain. Until that audit lands,
  heavyweights run sequentially and tiny live clients plus static
  attaches are the stable desktop proof.
- The block cache owns the other half of desktop stability:
  `bc_lock` is irqsave (a plain spin preempted mid-copy by the timer
  deschedules its holder, and a second context spinning with IF=0
  kills the timer: the silent machine-stop a server drain plus one
  shell write hit intermittently, observed as a waiter spinning on
  `fs_lock` downstream). Leaf discipline unchanged, still never held
  across PIO.
- Compositor correctness pass (2026-09-28), each pinned by `make
  test-wl` vectors plus a scoped mutant in `tools/wl_scoped.sh`:
  keyboard input follows `wl_comp_top_visible`, never the raw top of
  the z-order, and minimizing sinks the surface to the bottom and hands
  focus to the top visible window (Alt+M used to leave a minimized
  window holding the keyboard and re-target itself); client pixels are
  resampled into the body below the title strip, the exact rect
  `wl_ev_map` maps pointer events from (the title used to hide the
  client's top 14 rows and every click landed on a different pixel than
  the one shown), and `wl_ev_map` counts the body rows without its old
  off-by-one; a box whose first message is torn, stale or rejected gives
  back the slot it was provisionally assigned (`wlserv_unclaim`), so
  bad files can no longer squat the eight surface slots; and the server
  keeps a per-slot copy of each client's raw pixels (`wlserv_raw`),
  re-read only when that client published an attach or commit, so a
  move, re-tile or resize drag resamples from memory instead of
  re-reading every `.raw` file on every motion step.
