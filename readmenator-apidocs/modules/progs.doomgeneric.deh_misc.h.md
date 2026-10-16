# `progs/doomgeneric/deh_misc.h`

> Source: [progs/doomgeneric/deh_misc.h:1](../../progs/doomgeneric/deh_misc.h#L1) | language `h` | coverage 3.0% | [API index](../index.md)

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.   Parses "Misc" sections in dehacked files

## Contents

- **Macros:** [`DEH_DEFAULT_INITIAL_HEALTH`](#deh_default_initial_health), [`DEH_DEFAULT_INITIAL_BULLETS`](#deh_default_initial_bullets), [`DEH_DEFAULT_MAX_HEALTH`](#deh_default_max_health), [`DEH_DEFAULT_MAX_ARMOR`](#deh_default_max_armor), [`DEH_DEFAULT_GREEN_ARMOR_CLASS`](#deh_default_green_armor_class), [`DEH_DEFAULT_BLUE_ARMOR_CLASS`](#deh_default_blue_armor_class), [`DEH_DEFAULT_MAX_SOULSPHERE`](#deh_default_max_soulsphere), [`DEH_DEFAULT_SOULSPHERE_HEALTH`](#deh_default_soulsphere_health), [`DEH_DEFAULT_MEGASPHERE_HEALTH`](#deh_default_megasphere_health), [`DEH_DEFAULT_GOD_MODE_HEALTH`](#deh_default_god_mode_health), [`DEH_DEFAULT_IDFA_ARMOR`](#deh_default_idfa_armor), [`DEH_DEFAULT_IDFA_ARMOR_CLASS`](#deh_default_idfa_armor_class), [`DEH_DEFAULT_IDKFA_ARMOR`](#deh_default_idkfa_armor), [`DEH_DEFAULT_IDKFA_ARMOR_CLASS`](#deh_default_idkfa_armor_class), [`DEH_DEFAULT_BFG_CELLS_PER_SHOT`](#deh_default_bfg_cells_per_shot), [`DEH_DEFAULT_SPECIES_INFIGHTING`](#deh_default_species_infighting), [`deh_initial_health`](#deh_initial_health), [`deh_initial_bullets`](#deh_initial_bullets), [`deh_max_health`](#deh_max_health), [`deh_max_armor`](#deh_max_armor), [`deh_green_armor_class`](#deh_green_armor_class), [`deh_blue_armor_class`](#deh_blue_armor_class), [`deh_max_soulsphere`](#deh_max_soulsphere), [`deh_soulsphere_health`](#deh_soulsphere_health), [`deh_megasphere_health`](#deh_megasphere_health), [`deh_god_mode_health`](#deh_god_mode_health), [`deh_idfa_armor`](#deh_idfa_armor), [`deh_idfa_armor_class`](#deh_idfa_armor_class), [`deh_idkfa_armor`](#deh_idkfa_armor), [`deh_idkfa_armor_class`](#deh_idkfa_armor_class), [`deh_bfg_cells_per_shot`](#deh_bfg_cells_per_shot), [`deh_species_infighting`](#deh_species_infighting)
- **Variables:** [`deh_initial_health`](#deh_initial_health), [`deh_initial_bullets`](#deh_initial_bullets), [`deh_max_health`](#deh_max_health), [`deh_max_armor`](#deh_max_armor), [`deh_green_armor_class`](#deh_green_armor_class), [`deh_blue_armor_class`](#deh_blue_armor_class), [`deh_max_soulsphere`](#deh_max_soulsphere), [`deh_soulsphere_health`](#deh_soulsphere_health), [`deh_megasphere_health`](#deh_megasphere_health), [`deh_god_mode_health`](#deh_god_mode_health), [`deh_idfa_armor`](#deh_idfa_armor), [`deh_idfa_armor_class`](#deh_idfa_armor_class), [`deh_idkfa_armor`](#deh_idkfa_armor), [`deh_idkfa_armor_class`](#deh_idkfa_armor_class), [`deh_bfg_cells_per_shot`](#deh_bfg_cells_per_shot), [`deh_species_infighting`](#deh_species_infighting)

## Macros

<a id="deh_default_initial_health"></a>

### `DEH_DEFAULT_INITIAL_HEALTH`

`macro` | [progs/doomgeneric/deh_misc.h:23](../../progs/doomgeneric/deh_misc.h#L23)

```c
#define DEH_DEFAULT_INITIAL_HEALTH
```

---

<a id="deh_default_initial_bullets"></a>

### `DEH_DEFAULT_INITIAL_BULLETS`

`macro` | [progs/doomgeneric/deh_misc.h:24](../../progs/doomgeneric/deh_misc.h#L24)

```c
#define DEH_DEFAULT_INITIAL_BULLETS
```

---

<a id="deh_default_max_health"></a>

### `DEH_DEFAULT_MAX_HEALTH`

`macro` | [progs/doomgeneric/deh_misc.h:25](../../progs/doomgeneric/deh_misc.h#L25)

```c
#define DEH_DEFAULT_MAX_HEALTH
```

---

<a id="deh_default_max_armor"></a>

### `DEH_DEFAULT_MAX_ARMOR`

`macro` | [progs/doomgeneric/deh_misc.h:26](../../progs/doomgeneric/deh_misc.h#L26)

```c
#define DEH_DEFAULT_MAX_ARMOR
```

---

<a id="deh_default_green_armor_class"></a>

### `DEH_DEFAULT_GREEN_ARMOR_CLASS`

`macro` | [progs/doomgeneric/deh_misc.h:27](../../progs/doomgeneric/deh_misc.h#L27)

```c
#define DEH_DEFAULT_GREEN_ARMOR_CLASS
```

---

<a id="deh_default_blue_armor_class"></a>

### `DEH_DEFAULT_BLUE_ARMOR_CLASS`

`macro` | [progs/doomgeneric/deh_misc.h:28](../../progs/doomgeneric/deh_misc.h#L28)

```c
#define DEH_DEFAULT_BLUE_ARMOR_CLASS
```

---

<a id="deh_default_max_soulsphere"></a>

### `DEH_DEFAULT_MAX_SOULSPHERE`

`macro` | [progs/doomgeneric/deh_misc.h:29](../../progs/doomgeneric/deh_misc.h#L29)

```c
#define DEH_DEFAULT_MAX_SOULSPHERE
```

---

<a id="deh_default_soulsphere_health"></a>

### `DEH_DEFAULT_SOULSPHERE_HEALTH`

`macro` | [progs/doomgeneric/deh_misc.h:30](../../progs/doomgeneric/deh_misc.h#L30)

```c
#define DEH_DEFAULT_SOULSPHERE_HEALTH
```

---

<a id="deh_default_megasphere_health"></a>

### `DEH_DEFAULT_MEGASPHERE_HEALTH`

`macro` | [progs/doomgeneric/deh_misc.h:31](../../progs/doomgeneric/deh_misc.h#L31)

```c
#define DEH_DEFAULT_MEGASPHERE_HEALTH
```

---

<a id="deh_default_god_mode_health"></a>

### `DEH_DEFAULT_GOD_MODE_HEALTH`

`macro` | [progs/doomgeneric/deh_misc.h:32](../../progs/doomgeneric/deh_misc.h#L32)

```c
#define DEH_DEFAULT_GOD_MODE_HEALTH
```

---

<a id="deh_default_idfa_armor"></a>

### `DEH_DEFAULT_IDFA_ARMOR`

`macro` | [progs/doomgeneric/deh_misc.h:33](../../progs/doomgeneric/deh_misc.h#L33)

```c
#define DEH_DEFAULT_IDFA_ARMOR
```

---

<a id="deh_default_idfa_armor_class"></a>

### `DEH_DEFAULT_IDFA_ARMOR_CLASS`

`macro` | [progs/doomgeneric/deh_misc.h:34](../../progs/doomgeneric/deh_misc.h#L34)

```c
#define DEH_DEFAULT_IDFA_ARMOR_CLASS
```

---

<a id="deh_default_idkfa_armor"></a>

### `DEH_DEFAULT_IDKFA_ARMOR`

`macro` | [progs/doomgeneric/deh_misc.h:35](../../progs/doomgeneric/deh_misc.h#L35)

```c
#define DEH_DEFAULT_IDKFA_ARMOR
```

---

<a id="deh_default_idkfa_armor_class"></a>

### `DEH_DEFAULT_IDKFA_ARMOR_CLASS`

`macro` | [progs/doomgeneric/deh_misc.h:36](../../progs/doomgeneric/deh_misc.h#L36)

```c
#define DEH_DEFAULT_IDKFA_ARMOR_CLASS
```

---

<a id="deh_default_bfg_cells_per_shot"></a>

### `DEH_DEFAULT_BFG_CELLS_PER_SHOT`

`macro` | [progs/doomgeneric/deh_misc.h:37](../../progs/doomgeneric/deh_misc.h#L37)

```c
#define DEH_DEFAULT_BFG_CELLS_PER_SHOT
```

---

<a id="deh_default_species_infighting"></a>

### `DEH_DEFAULT_SPECIES_INFIGHTING`

`macro` | [progs/doomgeneric/deh_misc.h:38](../../progs/doomgeneric/deh_misc.h#L38)

```c
#define DEH_DEFAULT_SPECIES_INFIGHTING
```

---

<a id="deh_initial_health"></a>

### `deh_initial_health`

`macro` | [progs/doomgeneric/deh_misc.h:63](../../progs/doomgeneric/deh_misc.h#L63)

```c
#define deh_initial_health
```

---

<a id="deh_initial_bullets"></a>

### `deh_initial_bullets`

`macro` | [progs/doomgeneric/deh_misc.h:64](../../progs/doomgeneric/deh_misc.h#L64)

```c
#define deh_initial_bullets
```

---

<a id="deh_max_health"></a>

### `deh_max_health`

`macro` | [progs/doomgeneric/deh_misc.h:65](../../progs/doomgeneric/deh_misc.h#L65)

```c
#define deh_max_health
```

---

<a id="deh_max_armor"></a>

### `deh_max_armor`

`macro` | [progs/doomgeneric/deh_misc.h:66](../../progs/doomgeneric/deh_misc.h#L66)

```c
#define deh_max_armor
```

---

<a id="deh_green_armor_class"></a>

### `deh_green_armor_class`

`macro` | [progs/doomgeneric/deh_misc.h:67](../../progs/doomgeneric/deh_misc.h#L67)

```c
#define deh_green_armor_class
```

---

<a id="deh_blue_armor_class"></a>

### `deh_blue_armor_class`

`macro` | [progs/doomgeneric/deh_misc.h:68](../../progs/doomgeneric/deh_misc.h#L68)

```c
#define deh_blue_armor_class
```

---

<a id="deh_max_soulsphere"></a>

### `deh_max_soulsphere`

`macro` | [progs/doomgeneric/deh_misc.h:69](../../progs/doomgeneric/deh_misc.h#L69)

```c
#define deh_max_soulsphere
```

---

<a id="deh_soulsphere_health"></a>

### `deh_soulsphere_health`

`macro` | [progs/doomgeneric/deh_misc.h:70](../../progs/doomgeneric/deh_misc.h#L70)

```c
#define deh_soulsphere_health
```

---

<a id="deh_megasphere_health"></a>

### `deh_megasphere_health`

`macro` | [progs/doomgeneric/deh_misc.h:71](../../progs/doomgeneric/deh_misc.h#L71)

```c
#define deh_megasphere_health
```

---

<a id="deh_god_mode_health"></a>

### `deh_god_mode_health`

`macro` | [progs/doomgeneric/deh_misc.h:72](../../progs/doomgeneric/deh_misc.h#L72)

```c
#define deh_god_mode_health
```

---

<a id="deh_idfa_armor"></a>

### `deh_idfa_armor`

`macro` | [progs/doomgeneric/deh_misc.h:73](../../progs/doomgeneric/deh_misc.h#L73)

```c
#define deh_idfa_armor
```

---

<a id="deh_idfa_armor_class"></a>

### `deh_idfa_armor_class`

`macro` | [progs/doomgeneric/deh_misc.h:74](../../progs/doomgeneric/deh_misc.h#L74)

```c
#define deh_idfa_armor_class
```

---

<a id="deh_idkfa_armor"></a>

### `deh_idkfa_armor`

`macro` | [progs/doomgeneric/deh_misc.h:75](../../progs/doomgeneric/deh_misc.h#L75)

```c
#define deh_idkfa_armor
```

---

<a id="deh_idkfa_armor_class"></a>

### `deh_idkfa_armor_class`

`macro` | [progs/doomgeneric/deh_misc.h:76](../../progs/doomgeneric/deh_misc.h#L76)

```c
#define deh_idkfa_armor_class
```

---

<a id="deh_bfg_cells_per_shot"></a>

### `deh_bfg_cells_per_shot`

`macro` | [progs/doomgeneric/deh_misc.h:77](../../progs/doomgeneric/deh_misc.h#L77)

```c
#define deh_bfg_cells_per_shot
```

---

<a id="deh_species_infighting"></a>

### `deh_species_infighting`

`macro` | [progs/doomgeneric/deh_misc.h:78](../../progs/doomgeneric/deh_misc.h#L78)

```c
#define deh_species_infighting
```

---

## Variables

<a id="deh_initial_health"></a>

### `deh_initial_health`

`variable` `extern` | [progs/doomgeneric/deh_misc.h:42](../../progs/doomgeneric/deh_misc.h#L42)

```c
extern int deh_initial_health;
```

---

<a id="deh_initial_bullets"></a>

### `deh_initial_bullets`

`variable` `extern` | [progs/doomgeneric/deh_misc.h:43](../../progs/doomgeneric/deh_misc.h#L43)

```c
extern int deh_initial_bullets;
```

---

<a id="deh_max_health"></a>

### `deh_max_health`

`variable` `extern` | [progs/doomgeneric/deh_misc.h:44](../../progs/doomgeneric/deh_misc.h#L44)

```c
extern int deh_max_health;
```

---

<a id="deh_max_armor"></a>

### `deh_max_armor`

`variable` `extern` | [progs/doomgeneric/deh_misc.h:45](../../progs/doomgeneric/deh_misc.h#L45)

```c
extern int deh_max_armor;
```

---

<a id="deh_green_armor_class"></a>

### `deh_green_armor_class`

`variable` `extern` | [progs/doomgeneric/deh_misc.h:46](../../progs/doomgeneric/deh_misc.h#L46)

```c
extern int deh_green_armor_class;
```

---

<a id="deh_blue_armor_class"></a>

### `deh_blue_armor_class`

`variable` `extern` | [progs/doomgeneric/deh_misc.h:47](../../progs/doomgeneric/deh_misc.h#L47)

```c
extern int deh_blue_armor_class;
```

---

<a id="deh_max_soulsphere"></a>

### `deh_max_soulsphere`

`variable` `extern` | [progs/doomgeneric/deh_misc.h:48](../../progs/doomgeneric/deh_misc.h#L48)

```c
extern int deh_max_soulsphere;
```

---

<a id="deh_soulsphere_health"></a>

### `deh_soulsphere_health`

`variable` `extern` | [progs/doomgeneric/deh_misc.h:49](../../progs/doomgeneric/deh_misc.h#L49)

```c
extern int deh_soulsphere_health;
```

---

<a id="deh_megasphere_health"></a>

### `deh_megasphere_health`

`variable` `extern` | [progs/doomgeneric/deh_misc.h:50](../../progs/doomgeneric/deh_misc.h#L50)

```c
extern int deh_megasphere_health;
```

---

<a id="deh_god_mode_health"></a>

### `deh_god_mode_health`

`variable` `extern` | [progs/doomgeneric/deh_misc.h:51](../../progs/doomgeneric/deh_misc.h#L51)

```c
extern int deh_god_mode_health;
```

---

<a id="deh_idfa_armor"></a>

### `deh_idfa_armor`

`variable` `extern` | [progs/doomgeneric/deh_misc.h:52](../../progs/doomgeneric/deh_misc.h#L52)

```c
extern int deh_idfa_armor;
```

---

<a id="deh_idfa_armor_class"></a>

### `deh_idfa_armor_class`

`variable` `extern` | [progs/doomgeneric/deh_misc.h:53](../../progs/doomgeneric/deh_misc.h#L53)

```c
extern int deh_idfa_armor_class;
```

---

<a id="deh_idkfa_armor"></a>

### `deh_idkfa_armor`

`variable` `extern` | [progs/doomgeneric/deh_misc.h:54](../../progs/doomgeneric/deh_misc.h#L54)

```c
extern int deh_idkfa_armor;
```

---

<a id="deh_idkfa_armor_class"></a>

### `deh_idkfa_armor_class`

`variable` `extern` | [progs/doomgeneric/deh_misc.h:55](../../progs/doomgeneric/deh_misc.h#L55)

```c
extern int deh_idkfa_armor_class;
```

---

<a id="deh_bfg_cells_per_shot"></a>

### `deh_bfg_cells_per_shot`

`variable` `extern` | [progs/doomgeneric/deh_misc.h:56](../../progs/doomgeneric/deh_misc.h#L56)

```c
extern int deh_bfg_cells_per_shot;
```

---

<a id="deh_species_infighting"></a>

### `deh_species_infighting`

`variable` `extern` | [progs/doomgeneric/deh_misc.h:57](../../progs/doomgeneric/deh_misc.h#L57)

```c
extern int deh_species_infighting;
```

---
