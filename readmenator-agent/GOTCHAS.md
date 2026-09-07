# Gotchas

## God Nodes (high connectivity)

These files have the most connections. Changes here have high blast radius.

- `progs/doomgeneric/doomtype.h` (score: 101.20)
- `progs/doomgeneric/doomdef.h` (score: 90.90)
- `kernel.h` (score: 86.40)
- `kernel/string.c` (score: 81.30)
- `progs/doomgeneric/z_zone.h` (score: 80.20)
- `progs/doomgeneric/d_main.c` (score: 80.10)
- `progs/doomgeneric/i_system.h` (score: 80.10)
- `progs/doomgeneric/doomstat.h` (score: 78.30)
- `progs/doomgeneric/g_game.c` (score: 72.80)
- `progs/doomgeneric/w_wad.h` (score: 60.20)

## Hotspots (complexity + centrality)

- `progs/doomgeneric/d_main.c` -- complexity: 0.1, centrality: 1.0, combined: 0.6
- `progs/doomgeneric/g_game.c` -- complexity: 0.2, centrality: 0.9, combined: 0.6
- `progs/doomgeneric/st_stuff.c` -- complexity: 0.5, centrality: 0.6, combined: 0.5
- `kernel.h` -- complexity: 0.2, centrality: 0.6, combined: 0.4
- `progs/doomgeneric/m_menu.c` -- complexity: 0.2, centrality: 0.6, combined: 0.4
- `progs/doomgeneric/doomtype.h` -- complexity: 0.0, centrality: 0.7, combined: 0.4
- `progs/doomgeneric/d_englsh.h` -- complexity: 1.0, centrality: 0.0, combined: 0.4
- `progs/doomgeneric/doomdef.h` -- complexity: 0.0, centrality: 0.6, combined: 0.4
- `progs/doomgeneric/am_map.c` -- complexity: 0.3, centrality: 0.4, combined: 0.4
- `progs/doomgeneric/doomstat.h` -- complexity: 0.0, centrality: 0.5, combined: 0.3

## Dependency Cycles

Circular dependencies. Refactor to break the cycle.

- `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h`
