# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `kernel.h` (score: 116.30)
- `progs/doomgeneric/doomtype.h` (score: 101.40)
- `kernel/string.c` (score: 97.30)
- `progs/doomgeneric/doomdef.h` (score: 90.90)
- `progs/doomgeneric/d_main.c` (score: 89.30)
- `progs/doomgeneric/doomstat.h` (score: 84.80)
- `progs/doomgeneric/i_system.h` (score: 81.50)
- `progs/doomgeneric/z_zone.h` (score: 81.30)
- `progs/doomgeneric/g_game.c` (score: 77.70)
- `kernel/syscalls.c` (score: 62.30)

## Hotspots (complexity + centrality)

- `kernel.h` -- complexity: 1.0, centrality: 1.0, combined: 1.0
- `progs/doomgeneric/d_main.c` -- complexity: 0.4, centrality: 0.9, combined: 0.7
- `progs/doomgeneric/g_game.c` -- complexity: 0.3, centrality: 0.8, combined: 0.6
- `progs/doomgeneric/st_stuff.c` -- complexity: 0.5, centrality: 0.5, combined: 0.5
- `kernel/syscalls.c` -- complexity: 0.5, centrality: 0.6, combined: 0.5
- `progs/doomgeneric/m_menu.c` -- complexity: 0.3, centrality: 0.6, combined: 0.5
- `progs/doomgeneric/doomstat.h` -- complexity: 0.2, centrality: 0.5, combined: 0.4
- `kernel/vga_fb.c` -- complexity: 0.5, centrality: 0.3, combined: 0.4
- `progs/doomgeneric/doomtype.h` -- complexity: 0.0, centrality: 0.6, combined: 0.4
- `progs/doomgeneric/d_englsh.h` -- complexity: 0.9, centrality: 0.0, combined: 0.4

## Dependency Cycles

Circular dependencies. Refactor to break the cycle.

- `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h`

## Layer Violations

- `tests/test_wm.c` (testing) -> `wm_render.h` (presentation): testing must not import presentation
- `tests/test_wm.c` (testing) -> `wm_render.h` (presentation): testing must not import presentation
