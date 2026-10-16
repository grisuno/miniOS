# `progs/doomgeneric/m_random.h`

> Source: [progs/doomgeneric/m_random.h:1](../../progs/doomgeneric/m_random.h#L1) | language `h` | coverage 80.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION:          Returns a number from 0 to 255, from a lookup table.

## Contents

- **Functions:** [`M_Random`](#m_random), [`P_Random`](#p_random), [`M_ClearRandom`](#m_clearrandom)
- **Macros:** [`__M_RANDOM__`](#__m_random__)

## Functions

<a id="m_random"></a>

### `M_Random`

`function` | [progs/doomgeneric/m_random.h:30](../../progs/doomgeneric/m_random.h#L30)

```c
int M_Random (void);
```

Returns a number from 0 to 255, from a lookup table.

**Returns:** `int`

*Called by:* [`wipe_initMelt`](progs.doomgeneric.f_wipe.c.md#wipe_initmelt), [`ST_Ticker`](progs.doomgeneric.st_stuff.c.md#st_ticker), [`WI_initAnimatedBack`](progs.doomgeneric.wi_stuff.c.md#wi_initanimatedback), [`WI_updateAnimatedBack`](progs.doomgeneric.wi_stuff.c.md#wi_updateanimatedback)

---

<a id="p_random"></a>

### `P_Random`

`function` | [progs/doomgeneric/m_random.h:33](../../progs/doomgeneric/m_random.h#L33)

```c
int P_Random (void);
```

As M_Random, but used only by the play simulation.

**Returns:** `int`

*Called by:* [`G_DeathMatchSpawnPlayer`](progs.doomgeneric.g_game.c.md#g_deathmatchspawnplayer), [`A_BrainExplode`](progs.doomgeneric.p_enemy.c.md#a_brainexplode), [`A_BrainScream`](progs.doomgeneric.p_enemy.c.md#a_brainscream), [`A_BruisAttack`](progs.doomgeneric.p_enemy.c.md#a_bruisattack), [`A_CPosAttack`](progs.doomgeneric.p_enemy.c.md#a_cposattack), [`A_CPosRefire`](progs.doomgeneric.p_enemy.c.md#a_cposrefire), [`A_Chase`](progs.doomgeneric.p_enemy.c.md#a_chase), [`A_FaceTarget`](progs.doomgeneric.p_enemy.c.md#a_facetarget), [`A_HeadAttack`](progs.doomgeneric.p_enemy.c.md#a_headattack), [`A_Look`](progs.doomgeneric.p_enemy.c.md#a_look), [`A_PosAttack`](progs.doomgeneric.p_enemy.c.md#a_posattack), [`A_SPosAttack`](progs.doomgeneric.p_enemy.c.md#a_sposattack) and 33 more

---

<a id="m_clearrandom"></a>

### `M_ClearRandom`

`function` | [progs/doomgeneric/m_random.h:36](../../progs/doomgeneric/m_random.h#L36)

```c
void M_ClearRandom (void);
```

Fix randoms for demos.

*Called by:* [`G_InitNew`](progs.doomgeneric.g_game.c.md#g_initnew)

---

## Macros

<a id="__m_random__"></a>

### `__M_RANDOM__`

`macro` | [progs/doomgeneric/m_random.h:21](../../progs/doomgeneric/m_random.h#L21)

```c
#define __M_RANDOM__
```

---
