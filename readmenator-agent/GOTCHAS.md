# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `headers/kernel.h` (score: 137.40)
- `kernel/string.c` (score: 129.30)
- `progs/doomgeneric/doomtype.h` (score: 101.40)
- `progs/doomgeneric/doomdef.h` (score: 90.90)
- `progs/doomgeneric/doomstat.h` (score: 84.80)
- `progs/doomgeneric/z_zone.h` (score: 81.30)
- `progs/doomgeneric/i_system.h` (score: 81.20)
- `progs/doomgeneric/d_main.c` (score: 80.90)
- `progs/doomgeneric/g_game.c` (score: 73.40)
- `progs/minios_abi.h` (score: 68.90)

## Hotspots (complexity + centrality)

- `headers/kernel.h` -- complexity: 1.0, centrality: 0.7, combined: 0.8
- `progs/doomgeneric/d_main.c` -- complexity: 0.1, centrality: 1.0, combined: 0.6
- `progs/doomgeneric/g_game.c` -- complexity: 0.2, centrality: 0.9, combined: 0.6
- `kernel/syscalls.c` -- complexity: 0.3, centrality: 0.7, combined: 0.5
- `progs/doomgeneric/st_stuff.c` -- complexity: 0.4, centrality: 0.6, combined: 0.5
- `kernel/string.c` -- complexity: 0.0, centrality: 0.8, combined: 0.5
- `progs/doomgeneric/m_menu.c` -- complexity: 0.2, centrality: 0.6, combined: 0.4
- `kernel/vga_fb.c` -- complexity: 0.5, centrality: 0.4, combined: 0.4
- `progs/doomgeneric/doomstat.h` -- complexity: 0.2, centrality: 0.5, combined: 0.4
- `progs/doomgeneric/doomtype.h` -- complexity: 0.0, centrality: 0.7, combined: 0.4

## Dependency Cycles

Circular dependencies. Refactor to break the cycle.

- `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h` -> `progs/doomgeneric/r_data.h`

## Layer Violations

- `tests/test_freedomui.c` (testing) -> `progs/freedomui/freedomui_minios.c` (presentation): testing must not import presentation
- `tests/test_wm.c` (testing) -> `headers/wm_render.h` (presentation): testing must not import presentation
- `tests/test_wm.c` (testing) -> `headers/wm_layout.h` (presentation): testing must not import presentation

## Dataflow Issues (INFERRED, review each lead)

- `drivers/sb16.c:258` `sb16_pump` [DEAD_STORE] `dst`: `dst` assigned at line 258 but never read afterwards.
- `drivers/sb16.c:503` `sb16_init` [DEAD_STORE] `major`: `major` assigned at line 503 but never read afterwards.
- `kernel/loader.c:458` `load_exec_elf` [DEAD_STORE] `base`: `base` assigned at line 458 but never read afterwards.
- `kernel/loader.c:463` `load_exec_elf` [DEAD_STORE] `max_end`: `max_end` assigned at line 463 but never read afterwards.
- `kernel/mm/paging.c:42` `mm_setup_protections` [DEAD_STORE] `pd`: `pd` assigned at line 42 but never read afterwards.
- `kernel/sched.c:345` `irqstat_report` [DEAD_STORE] `txf`: `txf` assigned at line 345 but never read afterwards.
- `kernel/sched.c:1085` `syscall` [DEAD_STORE] `wheel`: `wheel` assigned at line 1085 but never read afterwards.
- `kernel/sched.c:1583` `proc_spawn_elf` [DEAD_STORE] `frame`: `frame` assigned at line 1583 but never read afterwards.
- `kernel/sched.c:1658` `schedule` [DEAD_STORE] `cpu`: `cpu` assigned at line 1658 but never read afterwards.
- `kernel/sched.c:2083` `it` [DEAD_STORE] `cr3`: `cr3` assigned at line 2083 but never read afterwards.
