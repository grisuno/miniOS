# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `kernel.h` (score: 106.10)
- `progs/doomgeneric/doomtype.h` (score: 101.40)
- `progs/doomgeneric/doomdef.h` (score: 90.90)
- `progs/doomgeneric/d_main.c` (score: 89.30)
- `progs/doomgeneric/doomstat.h` (score: 84.80)
- `kernel/string.c` (score: 83.30)
- `progs/doomgeneric/i_system.h` (score: 81.50)
- `progs/doomgeneric/z_zone.h` (score: 81.30)
- `progs/doomgeneric/g_game.c` (score: 77.70)
- `progs/doomgeneric/p_local.h` (score: 62.10)

## Hotspots (complexity + centrality)

- `kernel.h` -- complexity: 0.9, centrality: 1.0, combined: 1.0
- `progs/doomgeneric/d_main.c` -- complexity: 0.4, centrality: 1.0, combined: 0.8
- `progs/doomgeneric/g_game.c` -- complexity: 0.3, centrality: 0.9, combined: 0.7
- `progs/doomgeneric/st_stuff.c` -- complexity: 0.6, centrality: 0.6, combined: 0.6
- `kernel/syscalls.c` -- complexity: 0.5, centrality: 0.5, combined: 0.5
- `progs/doomgeneric/m_menu.c` -- complexity: 0.3, centrality: 0.6, combined: 0.5
- `progs/doomgeneric/doomstat.h` -- complexity: 0.2, centrality: 0.5, combined: 0.4
- `progs/doomgeneric/doomtype.h` -- complexity: 0.0, centrality: 0.7, combined: 0.4
- `progs/doomgeneric/d_englsh.h` -- complexity: 1.0, centrality: 0.0, combined: 0.4
- `progs/doomgeneric/doomdef.h` -- complexity: 0.0, centrality: 0.6, combined: 0.4

## Dependency Cycles

Circular dependencies. Refactor to break the cycle.

- `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h`
