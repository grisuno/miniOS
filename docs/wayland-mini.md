# Wayland-mini: miniOS Wayland subset (spec)

Status: phased implementation (F0-F3). It is neither Weston nor full
libwayland: it is a wire subset plus a ring-3 compositor that reuses the
existing kernel compositor (`GFX_PRESENT`).

## Why not port libwayland

The freedesktop `libwayland` assumes `AF_UNIX + SCM_RIGHTS`, `mmap/shm`,
`epoll` and `wayland-scanner` at runtime. miniOS has no UNIX sockets and
no fd passing, and its network is TCP/UDP over slirp (`10.0.2.x`). NovaOS
(`Wayland/client.h`) is not full Wayland either: a 32-client table over a
socket. The honest path is to implement the protocol over miniOS
primitives.

## Subset (frozen)

Interfaces: `wl_display`, `wl_registry`, `wl_compositor`, `wl_surface`,
`wl_shm`, `wl_shm_pool`, `wl_buffer`, `xdg_wm_base`, `xdg_surface`,
`xdg_toplevel`. Nothing more: no client decoration, no DMA-BUF, no
output hotplug, no full seat (basic pointer+keyboard through the
existing `SYS_MOUSE`/`SYS_KBD`).

Wire format (same as Wayland): header `object_id u32 + opcode u16 +
size u16`, args `int/uint/string/fd`. Limits (`progs/wl/wl_mini.h`):
`WL_MAX_MSG 4096`, `WL_MAX_STR 256`, `WL_MAX_SURFACES 8`,
`WL_MAX_POOLS 8`, surfaces max `800x360` (same as `MINIOS_NK_W/H`).
Anything beyond that fails closed (`WL_ERR_*`), never truncated.

## Transport

Phase 1 (done): the attach/commit wire exists as pure encode/decode
(`wl_attach_encode/decode` for pool plus dimensions,
`wl_commit_encode/decode` for the surface id) and every client speaks it
logically: `freedom_wl` walks it in its selftest and in its host probe.
Without `SCM_RIGHTS`: the fd is replaced by a validated `pool_id`. In this
phase the live cross-process transport over `pipe()` stays open: surfaces
are state inside the compositor and no shm byte crosses processes yet.
Later phase: real `AF_UNIX` if the kernel wins it.

Shared clipboard: object `WL_ID_CLIPBOARD` with `WL_OP_CLIPBOARD_SET`
(publish) and `WL_OP_CLIPBOARD_GET` (fetch), bounded by `WL_CLIP_MAX`
4096 bytes through `wl_clip_encode/decode` (fail-closed on oversize,
truncation and liar sizes, same discipline as attach/commit). The
kernel slot behind syscalls 249/250 and the shell `clip` builtin speak
the same bounds. Terminal selection and vedit paste on top are Phase 2.

## Compositor

The ring-3 `bin/wlcomp` (no kernel): owns N<=8 surfaces, z-order by
focus, tiles them with `wl_comp_layout_tile` (one fills the frame, two
split vertically, three or more form a grid), composites real client
pixels with `wlcomp_blit` onto the NK back-buffer and presents with
`GFX_PRESENT BUF_NK` (compatible with `vga_fb_blit_nk_window`). Moving
geometry through `wl_comp_set_rect` with validation. Input: focus owns
`SYS_MOUSE` / `SYS_KBD` (same rule as `vga_fb_ps2_owner`). Title through
`GFX_SET_TITLE`. The existing `gfx frames` counter proves the render.

## Reserved syscalls (not wired yet)

`243 WL_ATTACH`, `244 WL_COMMIT`, `245 WL_INPUT`. Defined in
`progs/minios_abi.h`, outside the checksum until the kernel answers them
(then `MINIOS_ABI_VERSION` moves). Today wlcomp composites in ring-3
without needing them.

## Session (Phase 2)

The session lives apart from the transport and runs over any source of
bytes: `wl_stream_t` reassembles messages split anywhere (even
mid-header) with a bounded buffer (`WL_STREAM_CAP`, `WL_ERR_MORE` asks
for more bytes, a lying size kills the connection), `wl_iface_t` carries
the hand-written descriptor tables for the ten interfaces (no scanner at
this scale), `wl_comp_attach_buf` binds a buffer to its surface, and
`wl_dispatch` routes every subset request to the existing `wl_comp_*`
operations, failing closed on a wild id, an unknown opcode and a short
payload. `wlcomp --selftest` proves it with a synthetic nine-message
session fed in two chunks.

## Multiprocess and desktop (Phase 3)

The mailbox transport carries the first live bytes between processes with
no kernel change at all: one wire message per file under
`/shm/wl/<box>-<seq>.msg` (`WLMB` magic plus sequence), pixels beside it
as `<box>.raw` sized exactly to the last attach. The server drains at
most `WL_MBOX_POLL_MAX` files per tick in the listed order (attach and
commit are order independent by construction), validates every frame
before dispatching, unlinks what it consumed and leaves half-written
files for the next poll. One surface per connection (the box owns its
slot) bounds the server to `WL_MAX_SURFACES` with no translation table;
the full id space stays for the future `pipe()` carrier. Routing lives
in `wl_mbox_route` (pure and tested) and freshness in `wl_mbox_fresh`;
the IO (stdio, `DIR_LIST`, `unlink`) stays in `wlcomp.c` and is proven
live in the guest.

`wlcomp` stops being a one-shot demo: `--server` takes the screen
through `SYS_VGA_MODE`, uploads the shared palette before every present,
focuses on click, drags with `wl_comp_set_rect`, re-tiles with `Alt+T`,
quits with `Alt+Q` (ESC quits too when no window is mapped) redrawing the
desktop. `--once` drains once for scripts. `--client` attaches one
surface from another process. `--clean` removes the mailbox files. Since the
layout resizes cells and the pixels arrive at attach size, the server
rescales on fit (`wl_scale_nearest`, nearest neighbour); a lying raw
falls back to solid ink, never to a torn frame.

The 768-byte hybrid palette lived in three identical copies while the
program that needed it most had none, and on truecolor VBE that read as
a glitch. Today it lives once in `progs/nk_palette.h` with the three
sites as thin wrappers, and `wlcomp` uploads it before every present
like every NK app.

## Tests

`make test-wl` (`tests/test_wl.c` vs `progs/wl/wl_mini.h`): encode/
decode, bounds, truncated string, wild object_id, pool overflow, z-order,
rectangles, tiling geometry, pixel blit, attach/commit roundtrip and
wild pool/id on decode, split reassembly, the full nine-message session
and the interface table. BDD: `wlcomp --selftest` prints
`wlcomp: frame ok (800x360)`. Mutants (`tools/wl_scoped.sh`): layout
columns, attach pool, blit border, commit id, stream split, consume
skip, short attach, create size, interface lookup, scale axes, mailbox
magic, mailbox freshness, route commit, route short, chrome active,
chrome close, chrome minimize, chrome zone, event magic, event map
outside, event scancode count, box pid, event name suffix, minimize
sink, minimize focus, chrome body title, event map body. Decisions:
`docs/adr/0024-wayland-mini.md`, `docs/adr/0025-wayland-session.md`.
