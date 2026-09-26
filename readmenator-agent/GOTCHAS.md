# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `headers/kernel.h` (score: 158.20)
- `kernel/string.c` (score: 137.30)
- `progs/doomgeneric/doomtype.h` (score: 101.40)
- `progs/doomgeneric/doomdef.h` (score: 90.90)
- `progs/doomgeneric/doomstat.h` (score: 84.80)
- `progs/doomgeneric/z_zone.h` (score: 81.30)
- `progs/doomgeneric/i_system.h` (score: 81.20)
- `progs/doomgeneric/d_main.c` (score: 80.90)
- `progs/doomgeneric/g_game.c` (score: 73.40)
- `progs/minios_abi.h` (score: 72.20)

## Hotspots (complexity + centrality)

- `headers/kernel.h` -- complexity: 1.0, centrality: 0.8, combined: 0.9
- `progs/doomgeneric/d_main.c` -- complexity: 0.1, centrality: 1.0, combined: 0.6
- `progs/doomgeneric/g_game.c` -- complexity: 0.2, centrality: 0.9, combined: 0.6
- `kernel/syscalls.c` -- complexity: 0.4, centrality: 0.7, combined: 0.6
- `kernel/string.c` -- complexity: 0.0, centrality: 0.9, combined: 0.5
- `progs/doomgeneric/st_stuff.c` -- complexity: 0.4, centrality: 0.6, combined: 0.5
- `kernel/vga_fb.c` -- complexity: 0.5, centrality: 0.4, combined: 0.5
- `kernel/shell.c` -- complexity: 0.3, centrality: 0.6, combined: 0.4
- `progs/doomgeneric/m_menu.c` -- complexity: 0.2, centrality: 0.6, combined: 0.4
- `progs/doomgeneric/doomtype.h` -- complexity: 0.0, centrality: 0.7, combined: 0.4

## Dependency Cycles

Circular dependencies. Refactor to break the cycle.

- `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h` -> `progs/doomgeneric/r_data.h`

## Layer Violations

- `tests/test_freedomui.c` (testing) -> `progs/freedomui/freedomui_minios.c` (presentation): testing must not import presentation
- `tests/test_httpd.c` (testing) -> `headers/httpd.h` (presentation): testing must not import presentation
- `tests/test_wm.c` (testing) -> `headers/wm_render.h` (presentation): testing must not import presentation
- `tests/test_wm.c` (testing) -> `headers/wm_layout.h` (presentation): testing must not import presentation

## Dataflow Issues (INFERRED, review each lead)

- `drivers/sb16.c:259` `sb16_pump` [DEAD_STORE] `dst`: `dst` assigned at line 259 but never read afterwards.
- `drivers/sb16.c:531` `sb16_init` [DEAD_STORE] `major`: `major` assigned at line 531 but never read afterwards.
- `drivers/virtio_blk.c:168` `vblk_desc` [DEAD_STORE] `d`: `d` assigned at line 168 but never read afterwards.
- `drivers/virtio_blk.c:188` `vblk_avail_push` [DEAD_STORE] `a`: `a` assigned at line 188 but never read afterwards.
- `fs/kfile.c:98` `kpipe_pair` [DEAD_STORE] `ref`: `ref` assigned at line 98 but never read afterwards.
- `kernel/loader.c:460` `load_exec_elf` [DEAD_STORE] `base`: `base` assigned at line 460 but never read afterwards.
- `kernel/loader.c:465` `load_exec_elf` [DEAD_STORE] `max_end`: `max_end` assigned at line 465 but never read afterwards.
- `kernel/mm/paging.c:42` `mm_setup_protections` [DEAD_STORE] `pd`: `pd` assigned at line 42 but never read afterwards.
- `kernel/sched.c:413` `irqstat_report` [DEAD_STORE] `txf`: `txf` assigned at line 413 but never read afterwards.
- `kernel/sched.c:1153` `syscall` [DEAD_STORE] `wheel`: `wheel` assigned at line 1153 but never read afterwards.
