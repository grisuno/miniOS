# progs/doomgeneric: p_spec

*Community 3 | 64 files | cohesion 0.54*

## Definition

This community groups 64 file(s) rooted at `progs/doomgeneric` with dominant language c (cohesion 0.54). Central symbols: `ANG1`, `ANG180`, `ANG1_X`, `ANG270`, `ANG45`, `ANG5`, `ANG60`, `ANG90`. Core file: `progs/doomgeneric/p_spec.h` (94 symbols). Documented purpose: Copyright(C) 1993-1996 Id Software, Inc. Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the .

## Files

### `progs/doomgeneric` (63 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomgeneric/d_items.c` | c | utility | 0 | yes |
| `progs/doomgeneric/d_items.h` | h | utility | 3 | yes |
| `progs/doomgeneric/d_think.h` | h | utility | 4 | yes |
| `progs/doomgeneric/deh_misc.h` | h | utility | 49 | yes |
| `progs/doomgeneric/doomdata.h` | h | utility | 11 | yes |
| `progs/doomgeneric/doomdef.c` | c | utility | 0 | yes |
| `progs/doomgeneric/doomdef.h` | h | utility | 9 | yes |
| `progs/doomgeneric/doomstat.c` | c | utility | 0 | yes |
| `progs/doomgeneric/doomstat.h` | h | utility | 68 | yes |
| `progs/doomgeneric/hu_lib.c` | c | utility | 22 | yes |
| `progs/doomgeneric/hu_lib.h` | h | utility | 24 | yes |
| `progs/doomgeneric/info.c` | c | utility | 74 | yes |
| `progs/doomgeneric/info.h` | h | utility | 6 | yes |
| `progs/doomgeneric/m_bbox.c` | c | utility | 2 | yes |
| `progs/doomgeneric/m_bbox.h` | h | utility | 3 | yes |
| `progs/doomgeneric/m_fixed.h` | h | utility | 6 | yes |
| `progs/doomgeneric/m_random.h` | h | utility | 4 | yes |
| `progs/doomgeneric/p_ceilng.c` | c | utility | 6 | yes |
| `progs/doomgeneric/p_doors.c` | c | utility | 10 | yes |

### `progs/quake2generic` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/quake2generic/q2generic_minios.c` | c | utility | 34 | yes |

*... and 44 more files in this community.*


## Key Symbols

- `__D_ITEMS__` (macro, `progs/doomgeneric/d_items.h:21`) `#define __D_ITEMS__`
- `weaponinfo_t` (struct, `progs/doomgeneric/d_items.h:28`) - Weapon info: sprite frames, ammunition use.
- `weaponinfo` (variable, `progs/doomgeneric/d_items.h:39`) `extern weaponinfo_t weaponinfo[NUMWEAPONS];`
- `__D_THINK__` (macro, `progs/doomgeneric/d_think.h:23`) `#define __D_THINK__`
- `think_t` (type_alias, `progs/doomgeneric/d_think.h:54`) `typedef actionf_t think_t;` - Historically, "think_t" is yet another function pointer to a routine to handle an actor.
- `thinker_s` (struct, `progs/doomgeneric/d_think.h:58`) - Doubly linked list of actors.
- `prev` (type_alias, `progs/doomgeneric/d_think.h:58`) `typedef struct thinker_s { struct thinker_s* prev;` - Doubly linked list of actors.
- `DEH_MISC_H` (macro, `progs/doomgeneric/deh_misc.h:19`) `#define DEH_MISC_H`
- `DEH_DEFAULT_INITIAL_HEALTH` (macro, `progs/doomgeneric/deh_misc.h:23`) `#define DEH_DEFAULT_INITIAL_HEALTH`
- `DEH_DEFAULT_INITIAL_BULLETS` (macro, `progs/doomgeneric/deh_misc.h:24`) `#define DEH_DEFAULT_INITIAL_BULLETS`
- `DEH_DEFAULT_MAX_HEALTH` (macro, `progs/doomgeneric/deh_misc.h:25`) `#define DEH_DEFAULT_MAX_HEALTH`
- `DEH_DEFAULT_MAX_ARMOR` (macro, `progs/doomgeneric/deh_misc.h:26`) `#define DEH_DEFAULT_MAX_ARMOR`
- `DEH_DEFAULT_GREEN_ARMOR_CLASS` (macro, `progs/doomgeneric/deh_misc.h:27`) `#define DEH_DEFAULT_GREEN_ARMOR_CLASS`
- `DEH_DEFAULT_BLUE_ARMOR_CLASS` (macro, `progs/doomgeneric/deh_misc.h:28`) `#define DEH_DEFAULT_BLUE_ARMOR_CLASS`
- `DEH_DEFAULT_MAX_SOULSPHERE` (macro, `progs/doomgeneric/deh_misc.h:29`) `#define DEH_DEFAULT_MAX_SOULSPHERE`
- `DEH_DEFAULT_SOULSPHERE_HEALTH` (macro, `progs/doomgeneric/deh_misc.h:30`) `#define DEH_DEFAULT_SOULSPHERE_HEALTH`
- `DEH_DEFAULT_MEGASPHERE_HEALTH` (macro, `progs/doomgeneric/deh_misc.h:31`) `#define DEH_DEFAULT_MEGASPHERE_HEALTH`
- `DEH_DEFAULT_GOD_MODE_HEALTH` (macro, `progs/doomgeneric/deh_misc.h:32`) `#define DEH_DEFAULT_GOD_MODE_HEALTH`
- `DEH_DEFAULT_IDFA_ARMOR` (macro, `progs/doomgeneric/deh_misc.h:33`) `#define DEH_DEFAULT_IDFA_ARMOR`
- `DEH_DEFAULT_IDFA_ARMOR_CLASS` (macro, `progs/doomgeneric/deh_misc.h:34`) `#define DEH_DEFAULT_IDFA_ARMOR_CLASS`
- `DEH_DEFAULT_IDKFA_ARMOR` (macro, `progs/doomgeneric/deh_misc.h:35`) `#define DEH_DEFAULT_IDKFA_ARMOR`
- `DEH_DEFAULT_IDKFA_ARMOR_CLASS` (macro, `progs/doomgeneric/deh_misc.h:36`) `#define DEH_DEFAULT_IDKFA_ARMOR_CLASS`
- `DEH_DEFAULT_BFG_CELLS_PER_SHOT` (macro, `progs/doomgeneric/deh_misc.h:37`) `#define DEH_DEFAULT_BFG_CELLS_PER_SHOT`
- `DEH_DEFAULT_SPECIES_INFIGHTING` (macro, `progs/doomgeneric/deh_misc.h:38`) `#define DEH_DEFAULT_SPECIES_INFIGHTING`
- `deh_initial_health` (variable, `progs/doomgeneric/deh_misc.h:42`) `extern int deh_initial_health;`
- `deh_initial_bullets` (variable, `progs/doomgeneric/deh_misc.h:43`) `extern int deh_initial_bullets;`
- `deh_max_health` (variable, `progs/doomgeneric/deh_misc.h:44`) `extern int deh_max_health;`
- `deh_max_armor` (variable, `progs/doomgeneric/deh_misc.h:45`) `extern int deh_max_armor;`
- `deh_green_armor_class` (variable, `progs/doomgeneric/deh_misc.h:46`) `extern int deh_green_armor_class;`
- `deh_blue_armor_class` (variable, `progs/doomgeneric/deh_misc.h:47`) `extern int deh_blue_armor_class;`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 187
- Cross-boundary resolved imports (EXTRACTED): 156

## Connections

- [EXTRACTED] depends_on community 1 <-> 3 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/am_map.c imports progs/doomgeneric/doomdef.h.
- [EXTRACTED] depends_on community 5 <-> 3 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/d_loop.c imports progs/doomgeneric/m_fixed.h.
- [EXTRACTED] depends_on community 3 <-> 2 (strength 0.9): Extracted import edge crosses communities: progs/doomgeneric/doomdef.h imports kernel/string.c.

## Risks

- [cycle] `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h` -> `progs/doomgeneric/r_data.h`

## Open Questions

- Can the cycle `progs/doomgeneric/r_data.h` -> `progs/doomgeneric/r_state.h` be broken with an interface?
- What would break if the most connected file in progs/doomgeneric: p_spec changed?
- Should progs/doomgeneric: p_spec be split, given cohesion 0.54?

## Sources

- `progs/doomgeneric/d_items.c`
- `progs/doomgeneric/d_items.h`
- `progs/doomgeneric/d_think.h`
- `progs/doomgeneric/deh_misc.h`
- `progs/doomgeneric/doomdata.h`
- `progs/doomgeneric/doomdef.c`
- `progs/doomgeneric/doomdef.h`
- `progs/doomgeneric/doomstat.c`
- `progs/doomgeneric/doomstat.h`
- `progs/doomgeneric/hu_lib.c`
- `progs/doomgeneric/hu_lib.h`
- `progs/doomgeneric/info.c`
- `progs/doomgeneric/info.h`
- `progs/doomgeneric/m_bbox.c`
- `progs/doomgeneric/m_bbox.h`
- `progs/doomgeneric/m_fixed.h`
- `progs/doomgeneric/m_random.h`
- `progs/doomgeneric/p_ceilng.c`
- `progs/doomgeneric/p_doors.c`
- `progs/doomgeneric/p_enemy.c`
- *... and 44 more*
