# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `kernel/string.c` (score: 163.30, imported by 81 files)
- `progs/doomgeneric/doomtype.h` (score: 101.40, imported by 50 files)
- `progs/doomgeneric/doomdef.h` (score: 90.90, imported by 41 files)
- `progs/doomgeneric/doomstat.h` (score: 84.80, imported by 34 files)
- `progs/doomgeneric/z_zone.h` (score: 81.30, imported by 40 files)
- `progs/doomgeneric/i_system.h` (score: 81.20, imported by 38 files)
- `progs/doomgeneric/d_main.c` (score: 80.90)
- `progs/minios_abi.h` (score: 75.30, imported by 30 files)
- `progs/doomgeneric/g_game.c` (score: 73.40)
- `kernel/syscalls.c` (score: 72.10)

## Blast Radius (change impact)

Editing these files can break the listed number of dependents. Run their tests after any change.

- `kernel/string.c` -- 50 direct, 81 total dependents
- `progs/doomgeneric/m_fixed.h` -- 9 direct, 58 total dependents
- `progs/doomgeneric/tables.h` -- 6 direct, 56 total dependents
- `progs/doomgeneric/v_patch.h` -- 2 direct, 54 total dependents
- `progs/doomgeneric/d_ticcmd.h` -- 6 direct, 53 total dependents
- `progs/doomgeneric/i_video.h` -- 18 direct, 53 total dependents
- `progs/doomgeneric/net_defs.h` -- 9 direct, 52 total dependents
- `progs/doomgeneric/d_event.h` -- 13 direct, 51 total dependents
- `progs/doomgeneric/d_items.h` -- 2 direct, 51 total dependents
- `progs/doomgeneric/d_mode.h` -- 6 direct, 51 total dependents

## Hotspots (complexity + centrality)

- `progs/doomgeneric/d_main.c` -- complexity: 0.1, centrality: 1.0, combined: 0.6
- `kernel/string.c` -- complexity: 0.0, centrality: 1.0, combined: 0.6
- `kernel/syscalls.c` -- complexity: 0.4, centrality: 0.7, combined: 0.6
- `progs/doomgeneric/g_game.c` -- complexity: 0.1, centrality: 0.9, combined: 0.6
- `kernel/shell.c` -- complexity: 0.3, centrality: 0.7, combined: 0.5
- `headers/kernel.h` -- complexity: 1.0, centrality: 0.2, combined: 0.5
- `progs/doomgeneric/st_stuff.c` -- complexity: 0.4, centrality: 0.6, combined: 0.5
- `kernel/vga_fb.c` -- complexity: 0.5, centrality: 0.4, combined: 0.5
- `progs/doomgeneric/m_menu.c` -- complexity: 0.2, centrality: 0.6, combined: 0.4
- `progs/doomgeneric/doomtype.h` -- complexity: 0.0, centrality: 0.6, combined: 0.4

## Dependency Cycles

Circular dependencies. Refactor to break the cycle.

- `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h` -> `progs/doomgeneric/r_data.h`

## Layer Violations

- `tests/test_httpd.c` (testing) -> `headers/httpd.h` (presentation): testing must not import presentation
- `tests/test_wm.c` (testing) -> `headers/wm_render.h` (presentation): testing must not import presentation
- `tests/test_wm.c` (testing) -> `headers/wm_layout.h` (presentation): testing must not import presentation

## Dataflow Issues (INFERRED, review each lead)

- `boot/uefi_stub.c:518` `efi_main` [UNCHECKED_ALLOC] `rc`: Result of allocator stored in `rc` is never checked against NULL.
- `drivers/sb16.c:259` `sb16_pump` [DEAD_STORE] `dst`: `dst` assigned at line 259 but never read afterwards.
- `drivers/sb16.c:531` `sb16_init` [DEAD_STORE] `major`: `major` assigned at line 531 but never read afterwards.
- `drivers/virtio_blk.c:169` `vblk_desc` [DEAD_STORE] `d`: `d` assigned at line 169 but never read afterwards.
- `drivers/virtio_blk.c:189` `vblk_avail_push` [DEAD_STORE] `a`: `a` assigned at line 189 but never read afterwards.
- `drivers/virtio_net.c:146` `vnet_desc` [DEAD_STORE] `d`: `d` assigned at line 146 but never read afterwards.
- `fs/kfile.c:103` `kpipe_pair` [DEAD_STORE] `ref`: `ref` assigned at line 103 but never read afterwards.
- `kernel/loader.c:925` `ldso_bind_into` [UNINIT_USE] `symname`: `symname` may be read before initialization (declared line 889).
- `kernel/loader.c:1074` `load_exec_elf` [DEAD_STORE] `base`: `base` assigned at line 1074 but never read afterwards.
- `kernel/loader.c:1079` `load_exec_elf` [DEAD_STORE] `max_end`: `max_end` assigned at line 1079 but never read afterwards.
