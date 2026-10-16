# `progs/doomgeneric/doomkeys.h`

> Source: [progs/doomgeneric/doomkeys.h:1](../../progs/doomgeneric/doomkeys.h#L1) | language `h` | coverage 5.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Key definitions     DOOM keyboard definition. This is the stuff configured by Setup.Exe. Most key data are simple ascii (uppercased).

## Contents

- **Macros:** [`__DOOMKEYS__`](#__doomkeys__), [`KEY_RIGHTARROW`](#key_rightarrow), [`KEY_LEFTARROW`](#key_leftarrow), [`KEY_UPARROW`](#key_uparrow), [`KEY_DOWNARROW`](#key_downarrow), [`KEY_STRAFE_L`](#key_strafe_l), [`KEY_STRAFE_R`](#key_strafe_r), [`KEY_USE`](#key_use), [`KEY_FIRE`](#key_fire), [`KEY_ESCAPE`](#key_escape), [`KEY_ENTER`](#key_enter), [`KEY_TAB`](#key_tab), [`KEY_F1`](#key_f1), [`KEY_F2`](#key_f2), [`KEY_F3`](#key_f3), [`KEY_F4`](#key_f4), [`KEY_F5`](#key_f5), [`KEY_F6`](#key_f6), [`KEY_F7`](#key_f7), [`KEY_F8`](#key_f8), [`KEY_F9`](#key_f9), [`KEY_F10`](#key_f10), [`KEY_F11`](#key_f11), [`KEY_F12`](#key_f12), [`KEY_BACKSPACE`](#key_backspace), [`KEY_PAUSE`](#key_pause), [`KEY_EQUALS`](#key_equals), [`KEY_MINUS`](#key_minus), [`KEY_RSHIFT`](#key_rshift), [`KEY_RCTRL`](#key_rctrl), [`KEY_RALT`](#key_ralt), [`KEY_LALT`](#key_lalt), [`KEY_CAPSLOCK`](#key_capslock), [`KEY_NUMLOCK`](#key_numlock), [`KEY_SCRLCK`](#key_scrlck), [`KEY_PRTSCR`](#key_prtscr), [`KEY_HOME`](#key_home), [`KEY_END`](#key_end), [`KEY_PGUP`](#key_pgup), [`KEY_PGDN`](#key_pgdn), [`KEY_INS`](#key_ins), [`KEY_DEL`](#key_del), [`KEYP_0`](#keyp_0), [`KEYP_1`](#keyp_1), [`KEYP_2`](#keyp_2), [`KEYP_3`](#keyp_3), [`KEYP_4`](#keyp_4), [`KEYP_5`](#keyp_5), [`KEYP_6`](#keyp_6), [`KEYP_7`](#keyp_7), [`KEYP_8`](#keyp_8), [`KEYP_9`](#keyp_9), [`KEYP_DIVIDE`](#keyp_divide), [`KEYP_PLUS`](#keyp_plus), [`KEYP_MINUS`](#keyp_minus), [`KEYP_MULTIPLY`](#keyp_multiply), [`KEYP_PERIOD`](#keyp_period), [`KEYP_EQUALS`](#keyp_equals), [`KEYP_ENTER`](#keyp_enter)

## Macros

<a id="__doomkeys__"></a>

### `__DOOMKEYS__`

`macro` | [progs/doomgeneric/doomkeys.h:20](../../progs/doomgeneric/doomkeys.h#L20)

```c
#define __DOOMKEYS__
```

---

<a id="key_rightarrow"></a>

### `KEY_RIGHTARROW`

`macro` | [progs/doomgeneric/doomkeys.h:27](../../progs/doomgeneric/doomkeys.h#L27)

```c
#define KEY_RIGHTARROW
```

DOOM keyboard definition.

This is the stuff configured by Setup.Exe. Most key data are simple ascii (uppercased).

---

<a id="key_leftarrow"></a>

### `KEY_LEFTARROW`

`macro` | [progs/doomgeneric/doomkeys.h:28](../../progs/doomgeneric/doomkeys.h#L28)

```c
#define KEY_LEFTARROW
```

---

<a id="key_uparrow"></a>

### `KEY_UPARROW`

`macro` | [progs/doomgeneric/doomkeys.h:29](../../progs/doomgeneric/doomkeys.h#L29)

```c
#define KEY_UPARROW
```

---

<a id="key_downarrow"></a>

### `KEY_DOWNARROW`

`macro` | [progs/doomgeneric/doomkeys.h:30](../../progs/doomgeneric/doomkeys.h#L30)

```c
#define KEY_DOWNARROW
```

---

<a id="key_strafe_l"></a>

### `KEY_STRAFE_L`

`macro` | [progs/doomgeneric/doomkeys.h:31](../../progs/doomgeneric/doomkeys.h#L31)

```c
#define KEY_STRAFE_L
```

---

<a id="key_strafe_r"></a>

### `KEY_STRAFE_R`

`macro` | [progs/doomgeneric/doomkeys.h:32](../../progs/doomgeneric/doomkeys.h#L32)

```c
#define KEY_STRAFE_R
```

---

<a id="key_use"></a>

### `KEY_USE`

`macro` | [progs/doomgeneric/doomkeys.h:33](../../progs/doomgeneric/doomkeys.h#L33)

```c
#define KEY_USE
```

---

<a id="key_fire"></a>

### `KEY_FIRE`

`macro` | [progs/doomgeneric/doomkeys.h:34](../../progs/doomgeneric/doomkeys.h#L34)

```c
#define KEY_FIRE
```

---

<a id="key_escape"></a>

### `KEY_ESCAPE`

`macro` | [progs/doomgeneric/doomkeys.h:35](../../progs/doomgeneric/doomkeys.h#L35)

```c
#define KEY_ESCAPE
```

---

<a id="key_enter"></a>

### `KEY_ENTER`

`macro` | [progs/doomgeneric/doomkeys.h:36](../../progs/doomgeneric/doomkeys.h#L36)

```c
#define KEY_ENTER
```

---

<a id="key_tab"></a>

### `KEY_TAB`

`macro` | [progs/doomgeneric/doomkeys.h:37](../../progs/doomgeneric/doomkeys.h#L37)

```c
#define KEY_TAB
```

---

<a id="key_f1"></a>

### `KEY_F1`

`macro` | [progs/doomgeneric/doomkeys.h:38](../../progs/doomgeneric/doomkeys.h#L38)

```c
#define KEY_F1
```

---

<a id="key_f2"></a>

### `KEY_F2`

`macro` | [progs/doomgeneric/doomkeys.h:39](../../progs/doomgeneric/doomkeys.h#L39)

```c
#define KEY_F2
```

---

<a id="key_f3"></a>

### `KEY_F3`

`macro` | [progs/doomgeneric/doomkeys.h:40](../../progs/doomgeneric/doomkeys.h#L40)

```c
#define KEY_F3
```

---

<a id="key_f4"></a>

### `KEY_F4`

`macro` | [progs/doomgeneric/doomkeys.h:41](../../progs/doomgeneric/doomkeys.h#L41)

```c
#define KEY_F4
```

---

<a id="key_f5"></a>

### `KEY_F5`

`macro` | [progs/doomgeneric/doomkeys.h:42](../../progs/doomgeneric/doomkeys.h#L42)

```c
#define KEY_F5
```

---

<a id="key_f6"></a>

### `KEY_F6`

`macro` | [progs/doomgeneric/doomkeys.h:43](../../progs/doomgeneric/doomkeys.h#L43)

```c
#define KEY_F6
```

---

<a id="key_f7"></a>

### `KEY_F7`

`macro` | [progs/doomgeneric/doomkeys.h:44](../../progs/doomgeneric/doomkeys.h#L44)

```c
#define KEY_F7
```

---

<a id="key_f8"></a>

### `KEY_F8`

`macro` | [progs/doomgeneric/doomkeys.h:45](../../progs/doomgeneric/doomkeys.h#L45)

```c
#define KEY_F8
```

---

<a id="key_f9"></a>

### `KEY_F9`

`macro` | [progs/doomgeneric/doomkeys.h:46](../../progs/doomgeneric/doomkeys.h#L46)

```c
#define KEY_F9
```

---

<a id="key_f10"></a>

### `KEY_F10`

`macro` | [progs/doomgeneric/doomkeys.h:47](../../progs/doomgeneric/doomkeys.h#L47)

```c
#define KEY_F10
```

---

<a id="key_f11"></a>

### `KEY_F11`

`macro` | [progs/doomgeneric/doomkeys.h:48](../../progs/doomgeneric/doomkeys.h#L48)

```c
#define KEY_F11
```

---

<a id="key_f12"></a>

### `KEY_F12`

`macro` | [progs/doomgeneric/doomkeys.h:49](../../progs/doomgeneric/doomkeys.h#L49)

```c
#define KEY_F12
```

---

<a id="key_backspace"></a>

### `KEY_BACKSPACE`

`macro` | [progs/doomgeneric/doomkeys.h:51](../../progs/doomgeneric/doomkeys.h#L51)

```c
#define KEY_BACKSPACE
```

========== Keyboard (PS/2) ==========

> **Inherited:** Documentation from [`KEY_BACKSPACE`](#key_backspace) (headers/kernel.h:138).

---

<a id="key_pause"></a>

### `KEY_PAUSE`

`macro` | [progs/doomgeneric/doomkeys.h:52](../../progs/doomgeneric/doomkeys.h#L52)

```c
#define KEY_PAUSE
```

---

<a id="key_equals"></a>

### `KEY_EQUALS`

`macro` | [progs/doomgeneric/doomkeys.h:54](../../progs/doomgeneric/doomkeys.h#L54)

```c
#define KEY_EQUALS
```

---

<a id="key_minus"></a>

### `KEY_MINUS`

`macro` | [progs/doomgeneric/doomkeys.h:55](../../progs/doomgeneric/doomkeys.h#L55)

```c
#define KEY_MINUS
```

---

<a id="key_rshift"></a>

### `KEY_RSHIFT`

`macro` | [progs/doomgeneric/doomkeys.h:57](../../progs/doomgeneric/doomkeys.h#L57)

```c
#define KEY_RSHIFT
```

---

<a id="key_rctrl"></a>

### `KEY_RCTRL`

`macro` | [progs/doomgeneric/doomkeys.h:58](../../progs/doomgeneric/doomkeys.h#L58)

```c
#define KEY_RCTRL
```

---

<a id="key_ralt"></a>

### `KEY_RALT`

`macro` | [progs/doomgeneric/doomkeys.h:59](../../progs/doomgeneric/doomkeys.h#L59)

```c
#define KEY_RALT
```

---

<a id="key_lalt"></a>

### `KEY_LALT`

`macro` | [progs/doomgeneric/doomkeys.h:61](../../progs/doomgeneric/doomkeys.h#L61)

```c
#define KEY_LALT
```

---

<a id="key_capslock"></a>

### `KEY_CAPSLOCK`

`macro` | [progs/doomgeneric/doomkeys.h:65](../../progs/doomgeneric/doomkeys.h#L65)

```c
#define KEY_CAPSLOCK
```

---

<a id="key_numlock"></a>

### `KEY_NUMLOCK`

`macro` | [progs/doomgeneric/doomkeys.h:66](../../progs/doomgeneric/doomkeys.h#L66)

```c
#define KEY_NUMLOCK
```

---

<a id="key_scrlck"></a>

### `KEY_SCRLCK`

`macro` | [progs/doomgeneric/doomkeys.h:67](../../progs/doomgeneric/doomkeys.h#L67)

```c
#define KEY_SCRLCK
```

---

<a id="key_prtscr"></a>

### `KEY_PRTSCR`

`macro` | [progs/doomgeneric/doomkeys.h:68](../../progs/doomgeneric/doomkeys.h#L68)

```c
#define KEY_PRTSCR
```

---

<a id="key_home"></a>

### `KEY_HOME`

`macro` | [progs/doomgeneric/doomkeys.h:70](../../progs/doomgeneric/doomkeys.h#L70)

```c
#define KEY_HOME
```

---

<a id="key_end"></a>

### `KEY_END`

`macro` | [progs/doomgeneric/doomkeys.h:71](../../progs/doomgeneric/doomkeys.h#L71)

```c
#define KEY_END
```

---

<a id="key_pgup"></a>

### `KEY_PGUP`

`macro` | [progs/doomgeneric/doomkeys.h:72](../../progs/doomgeneric/doomkeys.h#L72)

```c
#define KEY_PGUP
```

---

<a id="key_pgdn"></a>

### `KEY_PGDN`

`macro` | [progs/doomgeneric/doomkeys.h:73](../../progs/doomgeneric/doomkeys.h#L73)

```c
#define KEY_PGDN
```

---

<a id="key_ins"></a>

### `KEY_INS`

`macro` | [progs/doomgeneric/doomkeys.h:74](../../progs/doomgeneric/doomkeys.h#L74)

```c
#define KEY_INS
```

---

<a id="key_del"></a>

### `KEY_DEL`

`macro` | [progs/doomgeneric/doomkeys.h:75](../../progs/doomgeneric/doomkeys.h#L75)

```c
#define KEY_DEL
```

---

<a id="keyp_0"></a>

### `KEYP_0`

`macro` | [progs/doomgeneric/doomkeys.h:77](../../progs/doomgeneric/doomkeys.h#L77)

```c
#define KEYP_0
```

---

<a id="keyp_1"></a>

### `KEYP_1`

`macro` | [progs/doomgeneric/doomkeys.h:78](../../progs/doomgeneric/doomkeys.h#L78)

```c
#define KEYP_1
```

---

<a id="keyp_2"></a>

### `KEYP_2`

`macro` | [progs/doomgeneric/doomkeys.h:79](../../progs/doomgeneric/doomkeys.h#L79)

```c
#define KEYP_2
```

---

<a id="keyp_3"></a>

### `KEYP_3`

`macro` | [progs/doomgeneric/doomkeys.h:80](../../progs/doomgeneric/doomkeys.h#L80)

```c
#define KEYP_3
```

---

<a id="keyp_4"></a>

### `KEYP_4`

`macro` | [progs/doomgeneric/doomkeys.h:81](../../progs/doomgeneric/doomkeys.h#L81)

```c
#define KEYP_4
```

---

<a id="keyp_5"></a>

### `KEYP_5`

`macro` | [progs/doomgeneric/doomkeys.h:82](../../progs/doomgeneric/doomkeys.h#L82)

```c
#define KEYP_5
```

---

<a id="keyp_6"></a>

### `KEYP_6`

`macro` | [progs/doomgeneric/doomkeys.h:83](../../progs/doomgeneric/doomkeys.h#L83)

```c
#define KEYP_6
```

---

<a id="keyp_7"></a>

### `KEYP_7`

`macro` | [progs/doomgeneric/doomkeys.h:84](../../progs/doomgeneric/doomkeys.h#L84)

```c
#define KEYP_7
```

---

<a id="keyp_8"></a>

### `KEYP_8`

`macro` | [progs/doomgeneric/doomkeys.h:85](../../progs/doomgeneric/doomkeys.h#L85)

```c
#define KEYP_8
```

---

<a id="keyp_9"></a>

### `KEYP_9`

`macro` | [progs/doomgeneric/doomkeys.h:86](../../progs/doomgeneric/doomkeys.h#L86)

```c
#define KEYP_9
```

---

<a id="keyp_divide"></a>

### `KEYP_DIVIDE`

`macro` | [progs/doomgeneric/doomkeys.h:88](../../progs/doomgeneric/doomkeys.h#L88)

```c
#define KEYP_DIVIDE
```

---

<a id="keyp_plus"></a>

### `KEYP_PLUS`

`macro` | [progs/doomgeneric/doomkeys.h:89](../../progs/doomgeneric/doomkeys.h#L89)

```c
#define KEYP_PLUS
```

---

<a id="keyp_minus"></a>

### `KEYP_MINUS`

`macro` | [progs/doomgeneric/doomkeys.h:90](../../progs/doomgeneric/doomkeys.h#L90)

```c
#define KEYP_MINUS
```

---

<a id="keyp_multiply"></a>

### `KEYP_MULTIPLY`

`macro` | [progs/doomgeneric/doomkeys.h:91](../../progs/doomgeneric/doomkeys.h#L91)

```c
#define KEYP_MULTIPLY
```

---

<a id="keyp_period"></a>

### `KEYP_PERIOD`

`macro` | [progs/doomgeneric/doomkeys.h:92](../../progs/doomgeneric/doomkeys.h#L92)

```c
#define KEYP_PERIOD
```

---

<a id="keyp_equals"></a>

### `KEYP_EQUALS`

`macro` | [progs/doomgeneric/doomkeys.h:93](../../progs/doomgeneric/doomkeys.h#L93)

```c
#define KEYP_EQUALS
```

---

<a id="keyp_enter"></a>

### `KEYP_ENTER`

`macro` | [progs/doomgeneric/doomkeys.h:94](../../progs/doomgeneric/doomkeys.h#L94)

```c
#define KEYP_ENTER
```

---
