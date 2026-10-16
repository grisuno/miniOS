# `progs/doomgeneric/d_englsh.h`

> Source: [progs/doomgeneric/d_englsh.h:1](../../progs/doomgeneric/d_englsh.h#L1) | language `h` | coverage 3.1% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Printed strings for translation. English language support (default).     Printed strings for translation    D_Main.C

## Contents

- **Macros:** [`__D_ENGLSH__`](#__d_englsh__), [`D_DEVSTR`](#d_devstr), [`D_CDROM`](#d_cdrom), [`PRESSKEY`](#presskey), [`PRESSYN`](#pressyn), [`QUITMSG`](#quitmsg), [`LOADNET`](#loadnet), [`QLOADNET`](#qloadnet), [`QSAVESPOT`](#qsavespot), [`SAVEDEAD`](#savedead), [`QSPROMPT`](#qsprompt), [`QLPROMPT`](#qlprompt), [`NEWGAME`](#newgame), [`NIGHTMARE`](#nightmare), [`SWSTRING`](#swstring), [`MSGOFF`](#msgoff), [`MSGON`](#msgon), [`NETEND`](#netend), [`ENDGAME`](#endgame), [`DOSY`](#dosy), [`DETAILHI`](#detailhi), [`DETAILLO`](#detaillo), [`GAMMALVL0`](#gammalvl0), [`GAMMALVL1`](#gammalvl1), [`GAMMALVL2`](#gammalvl2), [`GAMMALVL3`](#gammalvl3), [`GAMMALVL4`](#gammalvl4), [`EMPTYSTRING`](#emptystring), [`GOTARMOR`](#gotarmor), [`GOTMEGA`](#gotmega), [`GOTHTHBONUS`](#goththbonus), [`GOTARMBONUS`](#gotarmbonus), [`GOTSTIM`](#gotstim), [`GOTMEDINEED`](#gotmedineed), [`GOTMEDIKIT`](#gotmedikit), [`GOTSUPER`](#gotsuper), [`GOTBLUECARD`](#gotbluecard), [`GOTYELWCARD`](#gotyelwcard), [`GOTREDCARD`](#gotredcard), [`GOTBLUESKUL`](#gotblueskul), [`GOTYELWSKUL`](#gotyelwskul), [`GOTREDSKULL`](#gotredskull), [`GOTINVUL`](#gotinvul), [`GOTBERSERK`](#gotberserk), [`GOTINVIS`](#gotinvis), [`GOTSUIT`](#gotsuit), [`GOTMAP`](#gotmap), [`GOTVISOR`](#gotvisor), [`GOTMSPHERE`](#gotmsphere), [`GOTCLIP`](#gotclip), [`GOTCLIPBOX`](#gotclipbox), [`GOTROCKET`](#gotrocket), [`GOTROCKBOX`](#gotrockbox), [`GOTCELL`](#gotcell), [`GOTCELLBOX`](#gotcellbox), [`GOTSHELLS`](#gotshells), [`GOTSHELLBOX`](#gotshellbox), [`GOTBACKPACK`](#gotbackpack), [`GOTBFG9000`](#gotbfg9000), [`GOTCHAINGUN`](#gotchaingun), [`GOTCHAINSAW`](#gotchainsaw), [`GOTLAUNCHER`](#gotlauncher), [`GOTPLASMA`](#gotplasma), [`GOTSHOTGUN`](#gotshotgun), [`GOTSHOTGUN2`](#gotshotgun2), [`PD_BLUEO`](#pd_blueo), [`PD_REDO`](#pd_redo), [`PD_YELLOWO`](#pd_yellowo), [`PD_BLUEK`](#pd_bluek), [`PD_REDK`](#pd_redk), [`PD_YELLOWK`](#pd_yellowk), [`GGSAVED`](#ggsaved), [`HUSTR_MSGU`](#hustr_msgu), [`HUSTR_E1M1`](#hustr_e1m1), [`HUSTR_E1M2`](#hustr_e1m2), [`HUSTR_E1M3`](#hustr_e1m3), [`HUSTR_E1M4`](#hustr_e1m4), [`HUSTR_E1M5`](#hustr_e1m5), [`HUSTR_E1M6`](#hustr_e1m6), [`HUSTR_E1M7`](#hustr_e1m7), [`HUSTR_E1M8`](#hustr_e1m8), [`HUSTR_E1M9`](#hustr_e1m9), [`HUSTR_E2M1`](#hustr_e2m1), [`HUSTR_E2M2`](#hustr_e2m2), [`HUSTR_E2M3`](#hustr_e2m3), [`HUSTR_E2M4`](#hustr_e2m4), [`HUSTR_E2M5`](#hustr_e2m5), [`HUSTR_E2M6`](#hustr_e2m6), [`HUSTR_E2M7`](#hustr_e2m7), [`HUSTR_E2M8`](#hustr_e2m8), [`HUSTR_E2M9`](#hustr_e2m9), [`HUSTR_E3M1`](#hustr_e3m1), [`HUSTR_E3M2`](#hustr_e3m2), [`HUSTR_E3M3`](#hustr_e3m3), [`HUSTR_E3M4`](#hustr_e3m4), [`HUSTR_E3M5`](#hustr_e3m5), [`HUSTR_E3M6`](#hustr_e3m6), [`HUSTR_E3M7`](#hustr_e3m7), [`HUSTR_E3M8`](#hustr_e3m8), [`HUSTR_E3M9`](#hustr_e3m9), [`HUSTR_E4M1`](#hustr_e4m1), [`HUSTR_E4M2`](#hustr_e4m2), [`HUSTR_E4M3`](#hustr_e4m3), [`HUSTR_E4M4`](#hustr_e4m4), [`HUSTR_E4M5`](#hustr_e4m5), [`HUSTR_E4M6`](#hustr_e4m6), [`HUSTR_E4M7`](#hustr_e4m7), [`HUSTR_E4M8`](#hustr_e4m8), [`HUSTR_E4M9`](#hustr_e4m9), [`HUSTR_1`](#hustr_1), [`HUSTR_2`](#hustr_2), [`HUSTR_3`](#hustr_3), [`HUSTR_4`](#hustr_4), [`HUSTR_5`](#hustr_5), [`HUSTR_6`](#hustr_6), [`HUSTR_7`](#hustr_7), [`HUSTR_8`](#hustr_8), [`HUSTR_9`](#hustr_9), [`HUSTR_10`](#hustr_10), [`HUSTR_11`](#hustr_11), [`HUSTR_12`](#hustr_12), [`HUSTR_13`](#hustr_13), [`HUSTR_14`](#hustr_14), [`HUSTR_15`](#hustr_15), [`HUSTR_16`](#hustr_16), [`HUSTR_17`](#hustr_17), [`HUSTR_18`](#hustr_18), [`HUSTR_19`](#hustr_19), [`HUSTR_20`](#hustr_20), [`HUSTR_21`](#hustr_21), [`HUSTR_22`](#hustr_22), [`HUSTR_23`](#hustr_23), [`HUSTR_24`](#hustr_24), [`HUSTR_25`](#hustr_25), [`HUSTR_26`](#hustr_26), [`HUSTR_27`](#hustr_27), [`HUSTR_28`](#hustr_28), [`HUSTR_29`](#hustr_29), [`HUSTR_30`](#hustr_30), [`HUSTR_31`](#hustr_31), [`HUSTR_32`](#hustr_32), [`PHUSTR_1`](#phustr_1), [`PHUSTR_2`](#phustr_2), [`PHUSTR_3`](#phustr_3), [`PHUSTR_4`](#phustr_4), [`PHUSTR_5`](#phustr_5), [`PHUSTR_6`](#phustr_6), [`PHUSTR_7`](#phustr_7), [`PHUSTR_8`](#phustr_8), [`PHUSTR_9`](#phustr_9), [`PHUSTR_10`](#phustr_10), [`PHUSTR_11`](#phustr_11), [`PHUSTR_12`](#phustr_12), [`PHUSTR_13`](#phustr_13), [`PHUSTR_14`](#phustr_14), [`PHUSTR_15`](#phustr_15), [`PHUSTR_16`](#phustr_16), [`PHUSTR_17`](#phustr_17), [`PHUSTR_18`](#phustr_18), [`PHUSTR_19`](#phustr_19), [`PHUSTR_20`](#phustr_20), [`PHUSTR_21`](#phustr_21), [`PHUSTR_22`](#phustr_22), [`PHUSTR_23`](#phustr_23), [`PHUSTR_24`](#phustr_24), [`PHUSTR_25`](#phustr_25), [`PHUSTR_26`](#phustr_26), [`PHUSTR_27`](#phustr_27), [`PHUSTR_28`](#phustr_28), [`PHUSTR_29`](#phustr_29), [`PHUSTR_30`](#phustr_30), [`PHUSTR_31`](#phustr_31), [`PHUSTR_32`](#phustr_32), [`THUSTR_1`](#thustr_1), [`THUSTR_2`](#thustr_2), [`THUSTR_3`](#thustr_3), [`THUSTR_4`](#thustr_4), [`THUSTR_5`](#thustr_5), [`THUSTR_6`](#thustr_6), [`THUSTR_7`](#thustr_7), [`THUSTR_8`](#thustr_8), [`THUSTR_9`](#thustr_9), [`THUSTR_10`](#thustr_10), [`THUSTR_11`](#thustr_11), [`THUSTR_12`](#thustr_12), [`THUSTR_13`](#thustr_13), [`THUSTR_14`](#thustr_14), [`THUSTR_15`](#thustr_15), [`THUSTR_16`](#thustr_16), [`THUSTR_17`](#thustr_17), [`THUSTR_18`](#thustr_18), [`THUSTR_19`](#thustr_19), [`THUSTR_20`](#thustr_20), [`THUSTR_21`](#thustr_21), [`THUSTR_22`](#thustr_22), [`THUSTR_23`](#thustr_23), [`THUSTR_24`](#thustr_24), [`THUSTR_25`](#thustr_25), [`THUSTR_26`](#thustr_26), [`THUSTR_27`](#thustr_27), [`THUSTR_28`](#thustr_28), [`THUSTR_29`](#thustr_29), [`THUSTR_30`](#thustr_30), [`THUSTR_31`](#thustr_31), [`THUSTR_32`](#thustr_32), [`HUSTR_CHATMACRO1`](#hustr_chatmacro1), [`HUSTR_CHATMACRO2`](#hustr_chatmacro2), [`HUSTR_CHATMACRO3`](#hustr_chatmacro3), [`HUSTR_CHATMACRO4`](#hustr_chatmacro4), [`HUSTR_CHATMACRO5`](#hustr_chatmacro5), [`HUSTR_CHATMACRO6`](#hustr_chatmacro6), [`HUSTR_CHATMACRO7`](#hustr_chatmacro7), [`HUSTR_CHATMACRO8`](#hustr_chatmacro8), [`HUSTR_CHATMACRO9`](#hustr_chatmacro9), [`HUSTR_CHATMACRO0`](#hustr_chatmacro0), [`HUSTR_TALKTOSELF1`](#hustr_talktoself1), [`HUSTR_TALKTOSELF2`](#hustr_talktoself2), [`HUSTR_TALKTOSELF3`](#hustr_talktoself3), [`HUSTR_TALKTOSELF4`](#hustr_talktoself4), [`HUSTR_TALKTOSELF5`](#hustr_talktoself5), [`HUSTR_MESSAGESENT`](#hustr_messagesent), [`HUSTR_PLRGREEN`](#hustr_plrgreen), [`HUSTR_PLRINDIGO`](#hustr_plrindigo), [`HUSTR_PLRBROWN`](#hustr_plrbrown), [`HUSTR_PLRRED`](#hustr_plrred), [`HUSTR_KEYGREEN`](#hustr_keygreen), [`HUSTR_KEYINDIGO`](#hustr_keyindigo), [`HUSTR_KEYBROWN`](#hustr_keybrown), [`HUSTR_KEYRED`](#hustr_keyred), [`AMSTR_FOLLOWON`](#amstr_followon), [`AMSTR_FOLLOWOFF`](#amstr_followoff), [`AMSTR_GRIDON`](#amstr_gridon), [`AMSTR_GRIDOFF`](#amstr_gridoff), [`AMSTR_MARKEDSPOT`](#amstr_markedspot), [`AMSTR_MARKSCLEARED`](#amstr_markscleared), [`STSTR_MUS`](#ststr_mus), [`STSTR_NOMUS`](#ststr_nomus), [`STSTR_DQDON`](#ststr_dqdon), [`STSTR_DQDOFF`](#ststr_dqdoff), [`STSTR_KFAADDED`](#ststr_kfaadded), [`STSTR_FAADDED`](#ststr_faadded), [`STSTR_NCON`](#ststr_ncon), [`STSTR_NCOFF`](#ststr_ncoff), [`STSTR_BEHOLD`](#ststr_behold), [`STSTR_BEHOLDX`](#ststr_beholdx), [`STSTR_CHOPPERS`](#ststr_choppers), [`STSTR_CLEV`](#ststr_clev), [`E1TEXT`](#e1text), [`E2TEXT`](#e2text), [`E3TEXT`](#e3text), [`E4TEXT`](#e4text), [`C1TEXT`](#c1text), [`C2TEXT`](#c2text), [`C3TEXT`](#c3text), [`C4TEXT`](#c4text), [`C5TEXT`](#c5text), [`C6TEXT`](#c6text), [`P1TEXT`](#p1text), [`P2TEXT`](#p2text), [`P3TEXT`](#p3text), [`P4TEXT`](#p4text), [`P5TEXT`](#p5text), [`P6TEXT`](#p6text), [`T1TEXT`](#t1text), [`T2TEXT`](#t2text), [`T3TEXT`](#t3text), [`T4TEXT`](#t4text), [`T5TEXT`](#t5text), [`T6TEXT`](#t6text), [`CC_ZOMBIE`](#cc_zombie), [`CC_SHOTGUN`](#cc_shotgun), [`CC_HEAVY`](#cc_heavy), [`CC_IMP`](#cc_imp), [`CC_DEMON`](#cc_demon), [`CC_LOST`](#cc_lost), [`CC_CACO`](#cc_caco), [`CC_HELL`](#cc_hell), [`CC_BARON`](#cc_baron), [`CC_ARACH`](#cc_arach), [`CC_PAIN`](#cc_pain), [`CC_REVEN`](#cc_reven), [`CC_MANCU`](#cc_mancu), [`CC_ARCH`](#cc_arch), [`CC_SPIDER`](#cc_spider), [`CC_CYBER`](#cc_cyber), [`CC_HERO`](#cc_hero)

## Macros

<a id="__d_englsh__"></a>

### `__D_ENGLSH__`

`macro` | [progs/doomgeneric/d_englsh.h:21](../../progs/doomgeneric/d_englsh.h#L21)

```c
#define __D_ENGLSH__
```

---

<a id="d_devstr"></a>

### `D_DEVSTR`

`macro` | [progs/doomgeneric/d_englsh.h:30](../../progs/doomgeneric/d_englsh.h#L30)

```c
#define D_DEVSTR
```

D_Main.C

---

<a id="d_cdrom"></a>

### `D_CDROM`

`macro` | [progs/doomgeneric/d_englsh.h:31](../../progs/doomgeneric/d_englsh.h#L31)

```c
#define D_CDROM
```

---

<a id="presskey"></a>

### `PRESSKEY`

`macro` | [progs/doomgeneric/d_englsh.h:36](../../progs/doomgeneric/d_englsh.h#L36)

```c
#define PRESSKEY
```

M_Menu.C

---

<a id="pressyn"></a>

### `PRESSYN`

`macro` | [progs/doomgeneric/d_englsh.h:37](../../progs/doomgeneric/d_englsh.h#L37)

```c
#define PRESSYN
```

---

<a id="quitmsg"></a>

### `QUITMSG`

`macro` | [progs/doomgeneric/d_englsh.h:38](../../progs/doomgeneric/d_englsh.h#L38)

```c
#define QUITMSG
```

---

<a id="loadnet"></a>

### `LOADNET`

`macro` | [progs/doomgeneric/d_englsh.h:39](../../progs/doomgeneric/d_englsh.h#L39)

```c
#define LOADNET
```

---

<a id="qloadnet"></a>

### `QLOADNET`

`macro` | [progs/doomgeneric/d_englsh.h:40](../../progs/doomgeneric/d_englsh.h#L40)

```c
#define QLOADNET
```

---

<a id="qsavespot"></a>

### `QSAVESPOT`

`macro` | [progs/doomgeneric/d_englsh.h:41](../../progs/doomgeneric/d_englsh.h#L41)

```c
#define QSAVESPOT
```

---

<a id="savedead"></a>

### `SAVEDEAD`

`macro` | [progs/doomgeneric/d_englsh.h:42](../../progs/doomgeneric/d_englsh.h#L42)

```c
#define SAVEDEAD
```

---

<a id="qsprompt"></a>

### `QSPROMPT`

`macro` | [progs/doomgeneric/d_englsh.h:43](../../progs/doomgeneric/d_englsh.h#L43)

```c
#define QSPROMPT
```

---

<a id="qlprompt"></a>

### `QLPROMPT`

`macro` | [progs/doomgeneric/d_englsh.h:44](../../progs/doomgeneric/d_englsh.h#L44)

```c
#define QLPROMPT
```

---

<a id="newgame"></a>

### `NEWGAME`

`macro` | [progs/doomgeneric/d_englsh.h:46](../../progs/doomgeneric/d_englsh.h#L46)

```c
#define NEWGAME
```

---

<a id="nightmare"></a>

### `NIGHTMARE`

`macro` | [progs/doomgeneric/d_englsh.h:50](../../progs/doomgeneric/d_englsh.h#L50)

```c
#define NIGHTMARE
```

---

<a id="swstring"></a>

### `SWSTRING`

`macro` | [progs/doomgeneric/d_englsh.h:54](../../progs/doomgeneric/d_englsh.h#L54)

```c
#define SWSTRING
```

---

<a id="msgoff"></a>

### `MSGOFF`

`macro` | [progs/doomgeneric/d_englsh.h:58](../../progs/doomgeneric/d_englsh.h#L58)

```c
#define MSGOFF
```

---

<a id="msgon"></a>

### `MSGON`

`macro` | [progs/doomgeneric/d_englsh.h:59](../../progs/doomgeneric/d_englsh.h#L59)

```c
#define MSGON
```

---

<a id="netend"></a>

### `NETEND`

`macro` | [progs/doomgeneric/d_englsh.h:60](../../progs/doomgeneric/d_englsh.h#L60)

```c
#define NETEND
```

---

<a id="endgame"></a>

### `ENDGAME`

`macro` | [progs/doomgeneric/d_englsh.h:61](../../progs/doomgeneric/d_englsh.h#L61)

```c
#define ENDGAME
```

---

<a id="dosy"></a>

### `DOSY`

`macro` | [progs/doomgeneric/d_englsh.h:63](../../progs/doomgeneric/d_englsh.h#L63)

```c
#define DOSY
```

---

<a id="detailhi"></a>

### `DETAILHI`

`macro` | [progs/doomgeneric/d_englsh.h:65](../../progs/doomgeneric/d_englsh.h#L65)

```c
#define DETAILHI
```

---

<a id="detaillo"></a>

### `DETAILLO`

`macro` | [progs/doomgeneric/d_englsh.h:66](../../progs/doomgeneric/d_englsh.h#L66)

```c
#define DETAILLO
```

---

<a id="gammalvl0"></a>

### `GAMMALVL0`

`macro` | [progs/doomgeneric/d_englsh.h:67](../../progs/doomgeneric/d_englsh.h#L67)

```c
#define GAMMALVL0
```

---

<a id="gammalvl1"></a>

### `GAMMALVL1`

`macro` | [progs/doomgeneric/d_englsh.h:68](../../progs/doomgeneric/d_englsh.h#L68)

```c
#define GAMMALVL1
```

---

<a id="gammalvl2"></a>

### `GAMMALVL2`

`macro` | [progs/doomgeneric/d_englsh.h:69](../../progs/doomgeneric/d_englsh.h#L69)

```c
#define GAMMALVL2
```

---

<a id="gammalvl3"></a>

### `GAMMALVL3`

`macro` | [progs/doomgeneric/d_englsh.h:70](../../progs/doomgeneric/d_englsh.h#L70)

```c
#define GAMMALVL3
```

---

<a id="gammalvl4"></a>

### `GAMMALVL4`

`macro` | [progs/doomgeneric/d_englsh.h:71](../../progs/doomgeneric/d_englsh.h#L71)

```c
#define GAMMALVL4
```

---

<a id="emptystring"></a>

### `EMPTYSTRING`

`macro` | [progs/doomgeneric/d_englsh.h:72](../../progs/doomgeneric/d_englsh.h#L72)

```c
#define EMPTYSTRING
```

---

<a id="gotarmor"></a>

### `GOTARMOR`

`macro` | [progs/doomgeneric/d_englsh.h:77](../../progs/doomgeneric/d_englsh.h#L77)

```c
#define GOTARMOR
```

P_inter.C

---

<a id="gotmega"></a>

### `GOTMEGA`

`macro` | [progs/doomgeneric/d_englsh.h:78](../../progs/doomgeneric/d_englsh.h#L78)

```c
#define GOTMEGA
```

---

<a id="goththbonus"></a>

### `GOTHTHBONUS`

`macro` | [progs/doomgeneric/d_englsh.h:79](../../progs/doomgeneric/d_englsh.h#L79)

```c
#define GOTHTHBONUS
```

---

<a id="gotarmbonus"></a>

### `GOTARMBONUS`

`macro` | [progs/doomgeneric/d_englsh.h:80](../../progs/doomgeneric/d_englsh.h#L80)

```c
#define GOTARMBONUS
```

---

<a id="gotstim"></a>

### `GOTSTIM`

`macro` | [progs/doomgeneric/d_englsh.h:81](../../progs/doomgeneric/d_englsh.h#L81)

```c
#define GOTSTIM
```

---

<a id="gotmedineed"></a>

### `GOTMEDINEED`

`macro` | [progs/doomgeneric/d_englsh.h:82](../../progs/doomgeneric/d_englsh.h#L82)

```c
#define GOTMEDINEED
```

---

<a id="gotmedikit"></a>

### `GOTMEDIKIT`

`macro` | [progs/doomgeneric/d_englsh.h:83](../../progs/doomgeneric/d_englsh.h#L83)

```c
#define GOTMEDIKIT
```

---

<a id="gotsuper"></a>

### `GOTSUPER`

`macro` | [progs/doomgeneric/d_englsh.h:84](../../progs/doomgeneric/d_englsh.h#L84)

```c
#define GOTSUPER
```

---

<a id="gotbluecard"></a>

### `GOTBLUECARD`

`macro` | [progs/doomgeneric/d_englsh.h:86](../../progs/doomgeneric/d_englsh.h#L86)

```c
#define GOTBLUECARD
```

---

<a id="gotyelwcard"></a>

### `GOTYELWCARD`

`macro` | [progs/doomgeneric/d_englsh.h:87](../../progs/doomgeneric/d_englsh.h#L87)

```c
#define GOTYELWCARD
```

---

<a id="gotredcard"></a>

### `GOTREDCARD`

`macro` | [progs/doomgeneric/d_englsh.h:88](../../progs/doomgeneric/d_englsh.h#L88)

```c
#define GOTREDCARD
```

---

<a id="gotblueskul"></a>

### `GOTBLUESKUL`

`macro` | [progs/doomgeneric/d_englsh.h:89](../../progs/doomgeneric/d_englsh.h#L89)

```c
#define GOTBLUESKUL
```

---

<a id="gotyelwskul"></a>

### `GOTYELWSKUL`

`macro` | [progs/doomgeneric/d_englsh.h:90](../../progs/doomgeneric/d_englsh.h#L90)

```c
#define GOTYELWSKUL
```

---

<a id="gotredskull"></a>

### `GOTREDSKULL`

`macro` | [progs/doomgeneric/d_englsh.h:91](../../progs/doomgeneric/d_englsh.h#L91)

```c
#define GOTREDSKULL
```

---

<a id="gotinvul"></a>

### `GOTINVUL`

`macro` | [progs/doomgeneric/d_englsh.h:93](../../progs/doomgeneric/d_englsh.h#L93)

```c
#define GOTINVUL
```

---

<a id="gotberserk"></a>

### `GOTBERSERK`

`macro` | [progs/doomgeneric/d_englsh.h:94](../../progs/doomgeneric/d_englsh.h#L94)

```c
#define GOTBERSERK
```

---

<a id="gotinvis"></a>

### `GOTINVIS`

`macro` | [progs/doomgeneric/d_englsh.h:95](../../progs/doomgeneric/d_englsh.h#L95)

```c
#define GOTINVIS
```

---

<a id="gotsuit"></a>

### `GOTSUIT`

`macro` | [progs/doomgeneric/d_englsh.h:96](../../progs/doomgeneric/d_englsh.h#L96)

```c
#define GOTSUIT
```

---

<a id="gotmap"></a>

### `GOTMAP`

`macro` | [progs/doomgeneric/d_englsh.h:97](../../progs/doomgeneric/d_englsh.h#L97)

```c
#define GOTMAP
```

---

<a id="gotvisor"></a>

### `GOTVISOR`

`macro` | [progs/doomgeneric/d_englsh.h:98](../../progs/doomgeneric/d_englsh.h#L98)

```c
#define GOTVISOR
```

---

<a id="gotmsphere"></a>

### `GOTMSPHERE`

`macro` | [progs/doomgeneric/d_englsh.h:99](../../progs/doomgeneric/d_englsh.h#L99)

```c
#define GOTMSPHERE
```

---

<a id="gotclip"></a>

### `GOTCLIP`

`macro` | [progs/doomgeneric/d_englsh.h:101](../../progs/doomgeneric/d_englsh.h#L101)

```c
#define GOTCLIP
```

---

<a id="gotclipbox"></a>

### `GOTCLIPBOX`

`macro` | [progs/doomgeneric/d_englsh.h:102](../../progs/doomgeneric/d_englsh.h#L102)

```c
#define GOTCLIPBOX
```

---

<a id="gotrocket"></a>

### `GOTROCKET`

`macro` | [progs/doomgeneric/d_englsh.h:103](../../progs/doomgeneric/d_englsh.h#L103)

```c
#define GOTROCKET
```

---

<a id="gotrockbox"></a>

### `GOTROCKBOX`

`macro` | [progs/doomgeneric/d_englsh.h:104](../../progs/doomgeneric/d_englsh.h#L104)

```c
#define GOTROCKBOX
```

---

<a id="gotcell"></a>

### `GOTCELL`

`macro` | [progs/doomgeneric/d_englsh.h:105](../../progs/doomgeneric/d_englsh.h#L105)

```c
#define GOTCELL
```

---

<a id="gotcellbox"></a>

### `GOTCELLBOX`

`macro` | [progs/doomgeneric/d_englsh.h:106](../../progs/doomgeneric/d_englsh.h#L106)

```c
#define GOTCELLBOX
```

---

<a id="gotshells"></a>

### `GOTSHELLS`

`macro` | [progs/doomgeneric/d_englsh.h:107](../../progs/doomgeneric/d_englsh.h#L107)

```c
#define GOTSHELLS
```

---

<a id="gotshellbox"></a>

### `GOTSHELLBOX`

`macro` | [progs/doomgeneric/d_englsh.h:108](../../progs/doomgeneric/d_englsh.h#L108)

```c
#define GOTSHELLBOX
```

---

<a id="gotbackpack"></a>

### `GOTBACKPACK`

`macro` | [progs/doomgeneric/d_englsh.h:109](../../progs/doomgeneric/d_englsh.h#L109)

```c
#define GOTBACKPACK
```

---

<a id="gotbfg9000"></a>

### `GOTBFG9000`

`macro` | [progs/doomgeneric/d_englsh.h:111](../../progs/doomgeneric/d_englsh.h#L111)

```c
#define GOTBFG9000
```

---

<a id="gotchaingun"></a>

### `GOTCHAINGUN`

`macro` | [progs/doomgeneric/d_englsh.h:112](../../progs/doomgeneric/d_englsh.h#L112)

```c
#define GOTCHAINGUN
```

---

<a id="gotchainsaw"></a>

### `GOTCHAINSAW`

`macro` | [progs/doomgeneric/d_englsh.h:113](../../progs/doomgeneric/d_englsh.h#L113)

```c
#define GOTCHAINSAW
```

---

<a id="gotlauncher"></a>

### `GOTLAUNCHER`

`macro` | [progs/doomgeneric/d_englsh.h:114](../../progs/doomgeneric/d_englsh.h#L114)

```c
#define GOTLAUNCHER
```

---

<a id="gotplasma"></a>

### `GOTPLASMA`

`macro` | [progs/doomgeneric/d_englsh.h:115](../../progs/doomgeneric/d_englsh.h#L115)

```c
#define GOTPLASMA
```

---

<a id="gotshotgun"></a>

### `GOTSHOTGUN`

`macro` | [progs/doomgeneric/d_englsh.h:116](../../progs/doomgeneric/d_englsh.h#L116)

```c
#define GOTSHOTGUN
```

---

<a id="gotshotgun2"></a>

### `GOTSHOTGUN2`

`macro` | [progs/doomgeneric/d_englsh.h:117](../../progs/doomgeneric/d_englsh.h#L117)

```c
#define GOTSHOTGUN2
```

---

<a id="pd_blueo"></a>

### `PD_BLUEO`

`macro` | [progs/doomgeneric/d_englsh.h:122](../../progs/doomgeneric/d_englsh.h#L122)

```c
#define PD_BLUEO
```

P_Doors.C

---

<a id="pd_redo"></a>

### `PD_REDO`

`macro` | [progs/doomgeneric/d_englsh.h:123](../../progs/doomgeneric/d_englsh.h#L123)

```c
#define PD_REDO
```

---

<a id="pd_yellowo"></a>

### `PD_YELLOWO`

`macro` | [progs/doomgeneric/d_englsh.h:124](../../progs/doomgeneric/d_englsh.h#L124)

```c
#define PD_YELLOWO
```

---

<a id="pd_bluek"></a>

### `PD_BLUEK`

`macro` | [progs/doomgeneric/d_englsh.h:125](../../progs/doomgeneric/d_englsh.h#L125)

```c
#define PD_BLUEK
```

---

<a id="pd_redk"></a>

### `PD_REDK`

`macro` | [progs/doomgeneric/d_englsh.h:126](../../progs/doomgeneric/d_englsh.h#L126)

```c
#define PD_REDK
```

---

<a id="pd_yellowk"></a>

### `PD_YELLOWK`

`macro` | [progs/doomgeneric/d_englsh.h:127](../../progs/doomgeneric/d_englsh.h#L127)

```c
#define PD_YELLOWK
```

---

<a id="ggsaved"></a>

### `GGSAVED`

`macro` | [progs/doomgeneric/d_englsh.h:132](../../progs/doomgeneric/d_englsh.h#L132)

```c
#define GGSAVED
```

G_game.C

---

<a id="hustr_msgu"></a>

### `HUSTR_MSGU`

`macro` | [progs/doomgeneric/d_englsh.h:137](../../progs/doomgeneric/d_englsh.h#L137)

```c
#define HUSTR_MSGU
```

HU_stuff.C

---

<a id="hustr_e1m1"></a>

### `HUSTR_E1M1`

`macro` | [progs/doomgeneric/d_englsh.h:139](../../progs/doomgeneric/d_englsh.h#L139)

```c
#define HUSTR_E1M1
```

---

<a id="hustr_e1m2"></a>

### `HUSTR_E1M2`

`macro` | [progs/doomgeneric/d_englsh.h:140](../../progs/doomgeneric/d_englsh.h#L140)

```c
#define HUSTR_E1M2
```

---

<a id="hustr_e1m3"></a>

### `HUSTR_E1M3`

`macro` | [progs/doomgeneric/d_englsh.h:141](../../progs/doomgeneric/d_englsh.h#L141)

```c
#define HUSTR_E1M3
```

---

<a id="hustr_e1m4"></a>

### `HUSTR_E1M4`

`macro` | [progs/doomgeneric/d_englsh.h:142](../../progs/doomgeneric/d_englsh.h#L142)

```c
#define HUSTR_E1M4
```

---

<a id="hustr_e1m5"></a>

### `HUSTR_E1M5`

`macro` | [progs/doomgeneric/d_englsh.h:143](../../progs/doomgeneric/d_englsh.h#L143)

```c
#define HUSTR_E1M5
```

---

<a id="hustr_e1m6"></a>

### `HUSTR_E1M6`

`macro` | [progs/doomgeneric/d_englsh.h:144](../../progs/doomgeneric/d_englsh.h#L144)

```c
#define HUSTR_E1M6
```

---

<a id="hustr_e1m7"></a>

### `HUSTR_E1M7`

`macro` | [progs/doomgeneric/d_englsh.h:145](../../progs/doomgeneric/d_englsh.h#L145)

```c
#define HUSTR_E1M7
```

---

<a id="hustr_e1m8"></a>

### `HUSTR_E1M8`

`macro` | [progs/doomgeneric/d_englsh.h:146](../../progs/doomgeneric/d_englsh.h#L146)

```c
#define HUSTR_E1M8
```

---

<a id="hustr_e1m9"></a>

### `HUSTR_E1M9`

`macro` | [progs/doomgeneric/d_englsh.h:147](../../progs/doomgeneric/d_englsh.h#L147)

```c
#define HUSTR_E1M9
```

---

<a id="hustr_e2m1"></a>

### `HUSTR_E2M1`

`macro` | [progs/doomgeneric/d_englsh.h:149](../../progs/doomgeneric/d_englsh.h#L149)

```c
#define HUSTR_E2M1
```

---

<a id="hustr_e2m2"></a>

### `HUSTR_E2M2`

`macro` | [progs/doomgeneric/d_englsh.h:150](../../progs/doomgeneric/d_englsh.h#L150)

```c
#define HUSTR_E2M2
```

---

<a id="hustr_e2m3"></a>

### `HUSTR_E2M3`

`macro` | [progs/doomgeneric/d_englsh.h:151](../../progs/doomgeneric/d_englsh.h#L151)

```c
#define HUSTR_E2M3
```

---

<a id="hustr_e2m4"></a>

### `HUSTR_E2M4`

`macro` | [progs/doomgeneric/d_englsh.h:152](../../progs/doomgeneric/d_englsh.h#L152)

```c
#define HUSTR_E2M4
```

---

<a id="hustr_e2m5"></a>

### `HUSTR_E2M5`

`macro` | [progs/doomgeneric/d_englsh.h:153](../../progs/doomgeneric/d_englsh.h#L153)

```c
#define HUSTR_E2M5
```

---

<a id="hustr_e2m6"></a>

### `HUSTR_E2M6`

`macro` | [progs/doomgeneric/d_englsh.h:154](../../progs/doomgeneric/d_englsh.h#L154)

```c
#define HUSTR_E2M6
```

---

<a id="hustr_e2m7"></a>

### `HUSTR_E2M7`

`macro` | [progs/doomgeneric/d_englsh.h:155](../../progs/doomgeneric/d_englsh.h#L155)

```c
#define HUSTR_E2M7
```

---

<a id="hustr_e2m8"></a>

### `HUSTR_E2M8`

`macro` | [progs/doomgeneric/d_englsh.h:156](../../progs/doomgeneric/d_englsh.h#L156)

```c
#define HUSTR_E2M8
```

---

<a id="hustr_e2m9"></a>

### `HUSTR_E2M9`

`macro` | [progs/doomgeneric/d_englsh.h:157](../../progs/doomgeneric/d_englsh.h#L157)

```c
#define HUSTR_E2M9
```

---

<a id="hustr_e3m1"></a>

### `HUSTR_E3M1`

`macro` | [progs/doomgeneric/d_englsh.h:159](../../progs/doomgeneric/d_englsh.h#L159)

```c
#define HUSTR_E3M1
```

---

<a id="hustr_e3m2"></a>

### `HUSTR_E3M2`

`macro` | [progs/doomgeneric/d_englsh.h:160](../../progs/doomgeneric/d_englsh.h#L160)

```c
#define HUSTR_E3M2
```

---

<a id="hustr_e3m3"></a>

### `HUSTR_E3M3`

`macro` | [progs/doomgeneric/d_englsh.h:161](../../progs/doomgeneric/d_englsh.h#L161)

```c
#define HUSTR_E3M3
```

---

<a id="hustr_e3m4"></a>

### `HUSTR_E3M4`

`macro` | [progs/doomgeneric/d_englsh.h:162](../../progs/doomgeneric/d_englsh.h#L162)

```c
#define HUSTR_E3M4
```

---

<a id="hustr_e3m5"></a>

### `HUSTR_E3M5`

`macro` | [progs/doomgeneric/d_englsh.h:163](../../progs/doomgeneric/d_englsh.h#L163)

```c
#define HUSTR_E3M5
```

---

<a id="hustr_e3m6"></a>

### `HUSTR_E3M6`

`macro` | [progs/doomgeneric/d_englsh.h:164](../../progs/doomgeneric/d_englsh.h#L164)

```c
#define HUSTR_E3M6
```

---

<a id="hustr_e3m7"></a>

### `HUSTR_E3M7`

`macro` | [progs/doomgeneric/d_englsh.h:165](../../progs/doomgeneric/d_englsh.h#L165)

```c
#define HUSTR_E3M7
```

---

<a id="hustr_e3m8"></a>

### `HUSTR_E3M8`

`macro` | [progs/doomgeneric/d_englsh.h:166](../../progs/doomgeneric/d_englsh.h#L166)

```c
#define HUSTR_E3M8
```

---

<a id="hustr_e3m9"></a>

### `HUSTR_E3M9`

`macro` | [progs/doomgeneric/d_englsh.h:167](../../progs/doomgeneric/d_englsh.h#L167)

```c
#define HUSTR_E3M9
```

---

<a id="hustr_e4m1"></a>

### `HUSTR_E4M1`

`macro` | [progs/doomgeneric/d_englsh.h:169](../../progs/doomgeneric/d_englsh.h#L169)

```c
#define HUSTR_E4M1
```

---

<a id="hustr_e4m2"></a>

### `HUSTR_E4M2`

`macro` | [progs/doomgeneric/d_englsh.h:170](../../progs/doomgeneric/d_englsh.h#L170)

```c
#define HUSTR_E4M2
```

---

<a id="hustr_e4m3"></a>

### `HUSTR_E4M3`

`macro` | [progs/doomgeneric/d_englsh.h:171](../../progs/doomgeneric/d_englsh.h#L171)

```c
#define HUSTR_E4M3
```

---

<a id="hustr_e4m4"></a>

### `HUSTR_E4M4`

`macro` | [progs/doomgeneric/d_englsh.h:172](../../progs/doomgeneric/d_englsh.h#L172)

```c
#define HUSTR_E4M4
```

---

<a id="hustr_e4m5"></a>

### `HUSTR_E4M5`

`macro` | [progs/doomgeneric/d_englsh.h:173](../../progs/doomgeneric/d_englsh.h#L173)

```c
#define HUSTR_E4M5
```

---

<a id="hustr_e4m6"></a>

### `HUSTR_E4M6`

`macro` | [progs/doomgeneric/d_englsh.h:174](../../progs/doomgeneric/d_englsh.h#L174)

```c
#define HUSTR_E4M6
```

---

<a id="hustr_e4m7"></a>

### `HUSTR_E4M7`

`macro` | [progs/doomgeneric/d_englsh.h:175](../../progs/doomgeneric/d_englsh.h#L175)

```c
#define HUSTR_E4M7
```

---

<a id="hustr_e4m8"></a>

### `HUSTR_E4M8`

`macro` | [progs/doomgeneric/d_englsh.h:176](../../progs/doomgeneric/d_englsh.h#L176)

```c
#define HUSTR_E4M8
```

---

<a id="hustr_e4m9"></a>

### `HUSTR_E4M9`

`macro` | [progs/doomgeneric/d_englsh.h:177](../../progs/doomgeneric/d_englsh.h#L177)

```c
#define HUSTR_E4M9
```

---

<a id="hustr_1"></a>

### `HUSTR_1`

`macro` | [progs/doomgeneric/d_englsh.h:179](../../progs/doomgeneric/d_englsh.h#L179)

```c
#define HUSTR_1
```

---

<a id="hustr_2"></a>

### `HUSTR_2`

`macro` | [progs/doomgeneric/d_englsh.h:180](../../progs/doomgeneric/d_englsh.h#L180)

```c
#define HUSTR_2
```

---

<a id="hustr_3"></a>

### `HUSTR_3`

`macro` | [progs/doomgeneric/d_englsh.h:181](../../progs/doomgeneric/d_englsh.h#L181)

```c
#define HUSTR_3
```

---

<a id="hustr_4"></a>

### `HUSTR_4`

`macro` | [progs/doomgeneric/d_englsh.h:182](../../progs/doomgeneric/d_englsh.h#L182)

```c
#define HUSTR_4
```

---

<a id="hustr_5"></a>

### `HUSTR_5`

`macro` | [progs/doomgeneric/d_englsh.h:183](../../progs/doomgeneric/d_englsh.h#L183)

```c
#define HUSTR_5
```

---

<a id="hustr_6"></a>

### `HUSTR_6`

`macro` | [progs/doomgeneric/d_englsh.h:184](../../progs/doomgeneric/d_englsh.h#L184)

```c
#define HUSTR_6
```

---

<a id="hustr_7"></a>

### `HUSTR_7`

`macro` | [progs/doomgeneric/d_englsh.h:185](../../progs/doomgeneric/d_englsh.h#L185)

```c
#define HUSTR_7
```

---

<a id="hustr_8"></a>

### `HUSTR_8`

`macro` | [progs/doomgeneric/d_englsh.h:186](../../progs/doomgeneric/d_englsh.h#L186)

```c
#define HUSTR_8
```

---

<a id="hustr_9"></a>

### `HUSTR_9`

`macro` | [progs/doomgeneric/d_englsh.h:187](../../progs/doomgeneric/d_englsh.h#L187)

```c
#define HUSTR_9
```

---

<a id="hustr_10"></a>

### `HUSTR_10`

`macro` | [progs/doomgeneric/d_englsh.h:188](../../progs/doomgeneric/d_englsh.h#L188)

```c
#define HUSTR_10
```

---

<a id="hustr_11"></a>

### `HUSTR_11`

`macro` | [progs/doomgeneric/d_englsh.h:189](../../progs/doomgeneric/d_englsh.h#L189)

```c
#define HUSTR_11
```

---

<a id="hustr_12"></a>

### `HUSTR_12`

`macro` | [progs/doomgeneric/d_englsh.h:191](../../progs/doomgeneric/d_englsh.h#L191)

```c
#define HUSTR_12
```

---

<a id="hustr_13"></a>

### `HUSTR_13`

`macro` | [progs/doomgeneric/d_englsh.h:192](../../progs/doomgeneric/d_englsh.h#L192)

```c
#define HUSTR_13
```

---

<a id="hustr_14"></a>

### `HUSTR_14`

`macro` | [progs/doomgeneric/d_englsh.h:193](../../progs/doomgeneric/d_englsh.h#L193)

```c
#define HUSTR_14
```

---

<a id="hustr_15"></a>

### `HUSTR_15`

`macro` | [progs/doomgeneric/d_englsh.h:194](../../progs/doomgeneric/d_englsh.h#L194)

```c
#define HUSTR_15
```

---

<a id="hustr_16"></a>

### `HUSTR_16`

`macro` | [progs/doomgeneric/d_englsh.h:195](../../progs/doomgeneric/d_englsh.h#L195)

```c
#define HUSTR_16
```

---

<a id="hustr_17"></a>

### `HUSTR_17`

`macro` | [progs/doomgeneric/d_englsh.h:196](../../progs/doomgeneric/d_englsh.h#L196)

```c
#define HUSTR_17
```

---

<a id="hustr_18"></a>

### `HUSTR_18`

`macro` | [progs/doomgeneric/d_englsh.h:197](../../progs/doomgeneric/d_englsh.h#L197)

```c
#define HUSTR_18
```

---

<a id="hustr_19"></a>

### `HUSTR_19`

`macro` | [progs/doomgeneric/d_englsh.h:198](../../progs/doomgeneric/d_englsh.h#L198)

```c
#define HUSTR_19
```

---

<a id="hustr_20"></a>

### `HUSTR_20`

`macro` | [progs/doomgeneric/d_englsh.h:199](../../progs/doomgeneric/d_englsh.h#L199)

```c
#define HUSTR_20
```

---

<a id="hustr_21"></a>

### `HUSTR_21`

`macro` | [progs/doomgeneric/d_englsh.h:201](../../progs/doomgeneric/d_englsh.h#L201)

```c
#define HUSTR_21
```

---

<a id="hustr_22"></a>

### `HUSTR_22`

`macro` | [progs/doomgeneric/d_englsh.h:202](../../progs/doomgeneric/d_englsh.h#L202)

```c
#define HUSTR_22
```

---

<a id="hustr_23"></a>

### `HUSTR_23`

`macro` | [progs/doomgeneric/d_englsh.h:203](../../progs/doomgeneric/d_englsh.h#L203)

```c
#define HUSTR_23
```

---

<a id="hustr_24"></a>

### `HUSTR_24`

`macro` | [progs/doomgeneric/d_englsh.h:204](../../progs/doomgeneric/d_englsh.h#L204)

```c
#define HUSTR_24
```

---

<a id="hustr_25"></a>

### `HUSTR_25`

`macro` | [progs/doomgeneric/d_englsh.h:205](../../progs/doomgeneric/d_englsh.h#L205)

```c
#define HUSTR_25
```

---

<a id="hustr_26"></a>

### `HUSTR_26`

`macro` | [progs/doomgeneric/d_englsh.h:206](../../progs/doomgeneric/d_englsh.h#L206)

```c
#define HUSTR_26
```

---

<a id="hustr_27"></a>

### `HUSTR_27`

`macro` | [progs/doomgeneric/d_englsh.h:207](../../progs/doomgeneric/d_englsh.h#L207)

```c
#define HUSTR_27
```

---

<a id="hustr_28"></a>

### `HUSTR_28`

`macro` | [progs/doomgeneric/d_englsh.h:208](../../progs/doomgeneric/d_englsh.h#L208)

```c
#define HUSTR_28
```

---

<a id="hustr_29"></a>

### `HUSTR_29`

`macro` | [progs/doomgeneric/d_englsh.h:209](../../progs/doomgeneric/d_englsh.h#L209)

```c
#define HUSTR_29
```

---

<a id="hustr_30"></a>

### `HUSTR_30`

`macro` | [progs/doomgeneric/d_englsh.h:210](../../progs/doomgeneric/d_englsh.h#L210)

```c
#define HUSTR_30
```

---

<a id="hustr_31"></a>

### `HUSTR_31`

`macro` | [progs/doomgeneric/d_englsh.h:212](../../progs/doomgeneric/d_englsh.h#L212)

```c
#define HUSTR_31
```

---

<a id="hustr_32"></a>

### `HUSTR_32`

`macro` | [progs/doomgeneric/d_englsh.h:213](../../progs/doomgeneric/d_englsh.h#L213)

```c
#define HUSTR_32
```

---

<a id="phustr_1"></a>

### `PHUSTR_1`

`macro` | [progs/doomgeneric/d_englsh.h:215](../../progs/doomgeneric/d_englsh.h#L215)

```c
#define PHUSTR_1
```

---

<a id="phustr_2"></a>

### `PHUSTR_2`

`macro` | [progs/doomgeneric/d_englsh.h:216](../../progs/doomgeneric/d_englsh.h#L216)

```c
#define PHUSTR_2
```

---

<a id="phustr_3"></a>

### `PHUSTR_3`

`macro` | [progs/doomgeneric/d_englsh.h:217](../../progs/doomgeneric/d_englsh.h#L217)

```c
#define PHUSTR_3
```

---

<a id="phustr_4"></a>

### `PHUSTR_4`

`macro` | [progs/doomgeneric/d_englsh.h:218](../../progs/doomgeneric/d_englsh.h#L218)

```c
#define PHUSTR_4
```

---

<a id="phustr_5"></a>

### `PHUSTR_5`

`macro` | [progs/doomgeneric/d_englsh.h:219](../../progs/doomgeneric/d_englsh.h#L219)

```c
#define PHUSTR_5
```

---

<a id="phustr_6"></a>

### `PHUSTR_6`

`macro` | [progs/doomgeneric/d_englsh.h:220](../../progs/doomgeneric/d_englsh.h#L220)

```c
#define PHUSTR_6
```

---

<a id="phustr_7"></a>

### `PHUSTR_7`

`macro` | [progs/doomgeneric/d_englsh.h:221](../../progs/doomgeneric/d_englsh.h#L221)

```c
#define PHUSTR_7
```

---

<a id="phustr_8"></a>

### `PHUSTR_8`

`macro` | [progs/doomgeneric/d_englsh.h:222](../../progs/doomgeneric/d_englsh.h#L222)

```c
#define PHUSTR_8
```

---

<a id="phustr_9"></a>

### `PHUSTR_9`

`macro` | [progs/doomgeneric/d_englsh.h:223](../../progs/doomgeneric/d_englsh.h#L223)

```c
#define PHUSTR_9
```

---

<a id="phustr_10"></a>

### `PHUSTR_10`

`macro` | [progs/doomgeneric/d_englsh.h:224](../../progs/doomgeneric/d_englsh.h#L224)

```c
#define PHUSTR_10
```

---

<a id="phustr_11"></a>

### `PHUSTR_11`

`macro` | [progs/doomgeneric/d_englsh.h:225](../../progs/doomgeneric/d_englsh.h#L225)

```c
#define PHUSTR_11
```

---

<a id="phustr_12"></a>

### `PHUSTR_12`

`macro` | [progs/doomgeneric/d_englsh.h:227](../../progs/doomgeneric/d_englsh.h#L227)

```c
#define PHUSTR_12
```

---

<a id="phustr_13"></a>

### `PHUSTR_13`

`macro` | [progs/doomgeneric/d_englsh.h:228](../../progs/doomgeneric/d_englsh.h#L228)

```c
#define PHUSTR_13
```

---

<a id="phustr_14"></a>

### `PHUSTR_14`

`macro` | [progs/doomgeneric/d_englsh.h:229](../../progs/doomgeneric/d_englsh.h#L229)

```c
#define PHUSTR_14
```

---

<a id="phustr_15"></a>

### `PHUSTR_15`

`macro` | [progs/doomgeneric/d_englsh.h:230](../../progs/doomgeneric/d_englsh.h#L230)

```c
#define PHUSTR_15
```

---

<a id="phustr_16"></a>

### `PHUSTR_16`

`macro` | [progs/doomgeneric/d_englsh.h:231](../../progs/doomgeneric/d_englsh.h#L231)

```c
#define PHUSTR_16
```

---

<a id="phustr_17"></a>

### `PHUSTR_17`

`macro` | [progs/doomgeneric/d_englsh.h:232](../../progs/doomgeneric/d_englsh.h#L232)

```c
#define PHUSTR_17
```

---

<a id="phustr_18"></a>

### `PHUSTR_18`

`macro` | [progs/doomgeneric/d_englsh.h:233](../../progs/doomgeneric/d_englsh.h#L233)

```c
#define PHUSTR_18
```

---

<a id="phustr_19"></a>

### `PHUSTR_19`

`macro` | [progs/doomgeneric/d_englsh.h:234](../../progs/doomgeneric/d_englsh.h#L234)

```c
#define PHUSTR_19
```

---

<a id="phustr_20"></a>

### `PHUSTR_20`

`macro` | [progs/doomgeneric/d_englsh.h:235](../../progs/doomgeneric/d_englsh.h#L235)

```c
#define PHUSTR_20
```

---

<a id="phustr_21"></a>

### `PHUSTR_21`

`macro` | [progs/doomgeneric/d_englsh.h:237](../../progs/doomgeneric/d_englsh.h#L237)

```c
#define PHUSTR_21
```

---

<a id="phustr_22"></a>

### `PHUSTR_22`

`macro` | [progs/doomgeneric/d_englsh.h:238](../../progs/doomgeneric/d_englsh.h#L238)

```c
#define PHUSTR_22
```

---

<a id="phustr_23"></a>

### `PHUSTR_23`

`macro` | [progs/doomgeneric/d_englsh.h:239](../../progs/doomgeneric/d_englsh.h#L239)

```c
#define PHUSTR_23
```

---

<a id="phustr_24"></a>

### `PHUSTR_24`

`macro` `final` | [progs/doomgeneric/d_englsh.h:240](../../progs/doomgeneric/d_englsh.h#L240)

```c
#define PHUSTR_24
```

---

<a id="phustr_25"></a>

### `PHUSTR_25`

`macro` | [progs/doomgeneric/d_englsh.h:241](../../progs/doomgeneric/d_englsh.h#L241)

```c
#define PHUSTR_25
```

---

<a id="phustr_26"></a>

### `PHUSTR_26`

`macro` | [progs/doomgeneric/d_englsh.h:242](../../progs/doomgeneric/d_englsh.h#L242)

```c
#define PHUSTR_26
```

---

<a id="phustr_27"></a>

### `PHUSTR_27`

`macro` | [progs/doomgeneric/d_englsh.h:243](../../progs/doomgeneric/d_englsh.h#L243)

```c
#define PHUSTR_27
```

---

<a id="phustr_28"></a>

### `PHUSTR_28`

`macro` | [progs/doomgeneric/d_englsh.h:244](../../progs/doomgeneric/d_englsh.h#L244)

```c
#define PHUSTR_28
```

---

<a id="phustr_29"></a>

### `PHUSTR_29`

`macro` | [progs/doomgeneric/d_englsh.h:245](../../progs/doomgeneric/d_englsh.h#L245)

```c
#define PHUSTR_29
```

---

<a id="phustr_30"></a>

### `PHUSTR_30`

`macro` | [progs/doomgeneric/d_englsh.h:246](../../progs/doomgeneric/d_englsh.h#L246)

```c
#define PHUSTR_30
```

---

<a id="phustr_31"></a>

### `PHUSTR_31`

`macro` | [progs/doomgeneric/d_englsh.h:248](../../progs/doomgeneric/d_englsh.h#L248)

```c
#define PHUSTR_31
```

---

<a id="phustr_32"></a>

### `PHUSTR_32`

`macro` | [progs/doomgeneric/d_englsh.h:249](../../progs/doomgeneric/d_englsh.h#L249)

```c
#define PHUSTR_32
```

---

<a id="thustr_1"></a>

### `THUSTR_1`

`macro` | [progs/doomgeneric/d_englsh.h:251](../../progs/doomgeneric/d_englsh.h#L251)

```c
#define THUSTR_1
```

---

<a id="thustr_2"></a>

### `THUSTR_2`

`macro` | [progs/doomgeneric/d_englsh.h:252](../../progs/doomgeneric/d_englsh.h#L252)

```c
#define THUSTR_2
```

---

<a id="thustr_3"></a>

### `THUSTR_3`

`macro` | [progs/doomgeneric/d_englsh.h:253](../../progs/doomgeneric/d_englsh.h#L253)

```c
#define THUSTR_3
```

---

<a id="thustr_4"></a>

### `THUSTR_4`

`macro` | [progs/doomgeneric/d_englsh.h:254](../../progs/doomgeneric/d_englsh.h#L254)

```c
#define THUSTR_4
```

---

<a id="thustr_5"></a>

### `THUSTR_5`

`macro` | [progs/doomgeneric/d_englsh.h:255](../../progs/doomgeneric/d_englsh.h#L255)

```c
#define THUSTR_5
```

---

<a id="thustr_6"></a>

### `THUSTR_6`

`macro` | [progs/doomgeneric/d_englsh.h:256](../../progs/doomgeneric/d_englsh.h#L256)

```c
#define THUSTR_6
```

---

<a id="thustr_7"></a>

### `THUSTR_7`

`macro` | [progs/doomgeneric/d_englsh.h:257](../../progs/doomgeneric/d_englsh.h#L257)

```c
#define THUSTR_7
```

---

<a id="thustr_8"></a>

### `THUSTR_8`

`macro` | [progs/doomgeneric/d_englsh.h:258](../../progs/doomgeneric/d_englsh.h#L258)

```c
#define THUSTR_8
```

---

<a id="thustr_9"></a>

### `THUSTR_9`

`macro` | [progs/doomgeneric/d_englsh.h:259](../../progs/doomgeneric/d_englsh.h#L259)

```c
#define THUSTR_9
```

---

<a id="thustr_10"></a>

### `THUSTR_10`

`macro` | [progs/doomgeneric/d_englsh.h:260](../../progs/doomgeneric/d_englsh.h#L260)

```c
#define THUSTR_10
```

---

<a id="thustr_11"></a>

### `THUSTR_11`

`macro` | [progs/doomgeneric/d_englsh.h:261](../../progs/doomgeneric/d_englsh.h#L261)

```c
#define THUSTR_11
```

---

<a id="thustr_12"></a>

### `THUSTR_12`

`macro` | [progs/doomgeneric/d_englsh.h:263](../../progs/doomgeneric/d_englsh.h#L263)

```c
#define THUSTR_12
```

---

<a id="thustr_13"></a>

### `THUSTR_13`

`macro` | [progs/doomgeneric/d_englsh.h:264](../../progs/doomgeneric/d_englsh.h#L264)

```c
#define THUSTR_13
```

---

<a id="thustr_14"></a>

### `THUSTR_14`

`macro` | [progs/doomgeneric/d_englsh.h:265](../../progs/doomgeneric/d_englsh.h#L265)

```c
#define THUSTR_14
```

---

<a id="thustr_15"></a>

### `THUSTR_15`

`macro` | [progs/doomgeneric/d_englsh.h:266](../../progs/doomgeneric/d_englsh.h#L266)

```c
#define THUSTR_15
```

---

<a id="thustr_16"></a>

### `THUSTR_16`

`macro` | [progs/doomgeneric/d_englsh.h:267](../../progs/doomgeneric/d_englsh.h#L267)

```c
#define THUSTR_16
```

---

<a id="thustr_17"></a>

### `THUSTR_17`

`macro` | [progs/doomgeneric/d_englsh.h:268](../../progs/doomgeneric/d_englsh.h#L268)

```c
#define THUSTR_17
```

---

<a id="thustr_18"></a>

### `THUSTR_18`

`macro` | [progs/doomgeneric/d_englsh.h:269](../../progs/doomgeneric/d_englsh.h#L269)

```c
#define THUSTR_18
```

---

<a id="thustr_19"></a>

### `THUSTR_19`

`macro` | [progs/doomgeneric/d_englsh.h:270](../../progs/doomgeneric/d_englsh.h#L270)

```c
#define THUSTR_19
```

---

<a id="thustr_20"></a>

### `THUSTR_20`

`macro` | [progs/doomgeneric/d_englsh.h:271](../../progs/doomgeneric/d_englsh.h#L271)

```c
#define THUSTR_20
```

---

<a id="thustr_21"></a>

### `THUSTR_21`

`macro` | [progs/doomgeneric/d_englsh.h:273](../../progs/doomgeneric/d_englsh.h#L273)

```c
#define THUSTR_21
```

---

<a id="thustr_22"></a>

### `THUSTR_22`

`macro` | [progs/doomgeneric/d_englsh.h:274](../../progs/doomgeneric/d_englsh.h#L274)

```c
#define THUSTR_22
```

---

<a id="thustr_23"></a>

### `THUSTR_23`

`macro` | [progs/doomgeneric/d_englsh.h:275](../../progs/doomgeneric/d_englsh.h#L275)

```c
#define THUSTR_23
```

---

<a id="thustr_24"></a>

### `THUSTR_24`

`macro` | [progs/doomgeneric/d_englsh.h:276](../../progs/doomgeneric/d_englsh.h#L276)

```c
#define THUSTR_24
```

---

<a id="thustr_25"></a>

### `THUSTR_25`

`macro` | [progs/doomgeneric/d_englsh.h:277](../../progs/doomgeneric/d_englsh.h#L277)

```c
#define THUSTR_25
```

---

<a id="thustr_26"></a>

### `THUSTR_26`

`macro` | [progs/doomgeneric/d_englsh.h:278](../../progs/doomgeneric/d_englsh.h#L278)

```c
#define THUSTR_26
```

---

<a id="thustr_27"></a>

### `THUSTR_27`

`macro` | [progs/doomgeneric/d_englsh.h:279](../../progs/doomgeneric/d_englsh.h#L279)

```c
#define THUSTR_27
```

---

<a id="thustr_28"></a>

### `THUSTR_28`

`macro` | [progs/doomgeneric/d_englsh.h:280](../../progs/doomgeneric/d_englsh.h#L280)

```c
#define THUSTR_28
```

---

<a id="thustr_29"></a>

### `THUSTR_29`

`macro` | [progs/doomgeneric/d_englsh.h:281](../../progs/doomgeneric/d_englsh.h#L281)

```c
#define THUSTR_29
```

---

<a id="thustr_30"></a>

### `THUSTR_30`

`macro` | [progs/doomgeneric/d_englsh.h:282](../../progs/doomgeneric/d_englsh.h#L282)

```c
#define THUSTR_30
```

---

<a id="thustr_31"></a>

### `THUSTR_31`

`macro` | [progs/doomgeneric/d_englsh.h:284](../../progs/doomgeneric/d_englsh.h#L284)

```c
#define THUSTR_31
```

---

<a id="thustr_32"></a>

### `THUSTR_32`

`macro` | [progs/doomgeneric/d_englsh.h:285](../../progs/doomgeneric/d_englsh.h#L285)

```c
#define THUSTR_32
```

---

<a id="hustr_chatmacro1"></a>

### `HUSTR_CHATMACRO1`

`macro` | [progs/doomgeneric/d_englsh.h:287](../../progs/doomgeneric/d_englsh.h#L287)

```c
#define HUSTR_CHATMACRO1
```

---

<a id="hustr_chatmacro2"></a>

### `HUSTR_CHATMACRO2`

`macro` | [progs/doomgeneric/d_englsh.h:288](../../progs/doomgeneric/d_englsh.h#L288)

```c
#define HUSTR_CHATMACRO2
```

---

<a id="hustr_chatmacro3"></a>

### `HUSTR_CHATMACRO3`

`macro` | [progs/doomgeneric/d_englsh.h:289](../../progs/doomgeneric/d_englsh.h#L289)

```c
#define HUSTR_CHATMACRO3
```

---

<a id="hustr_chatmacro4"></a>

### `HUSTR_CHATMACRO4`

`macro` | [progs/doomgeneric/d_englsh.h:290](../../progs/doomgeneric/d_englsh.h#L290)

```c
#define HUSTR_CHATMACRO4
```

---

<a id="hustr_chatmacro5"></a>

### `HUSTR_CHATMACRO5`

`macro` | [progs/doomgeneric/d_englsh.h:291](../../progs/doomgeneric/d_englsh.h#L291)

```c
#define HUSTR_CHATMACRO5
```

---

<a id="hustr_chatmacro6"></a>

### `HUSTR_CHATMACRO6`

`macro` | [progs/doomgeneric/d_englsh.h:292](../../progs/doomgeneric/d_englsh.h#L292)

```c
#define HUSTR_CHATMACRO6
```

---

<a id="hustr_chatmacro7"></a>

### `HUSTR_CHATMACRO7`

`macro` | [progs/doomgeneric/d_englsh.h:293](../../progs/doomgeneric/d_englsh.h#L293)

```c
#define HUSTR_CHATMACRO7
```

---

<a id="hustr_chatmacro8"></a>

### `HUSTR_CHATMACRO8`

`macro` | [progs/doomgeneric/d_englsh.h:294](../../progs/doomgeneric/d_englsh.h#L294)

```c
#define HUSTR_CHATMACRO8
```

---

<a id="hustr_chatmacro9"></a>

### `HUSTR_CHATMACRO9`

`macro` | [progs/doomgeneric/d_englsh.h:295](../../progs/doomgeneric/d_englsh.h#L295)

```c
#define HUSTR_CHATMACRO9
```

---

<a id="hustr_chatmacro0"></a>

### `HUSTR_CHATMACRO0`

`macro` | [progs/doomgeneric/d_englsh.h:296](../../progs/doomgeneric/d_englsh.h#L296)

```c
#define HUSTR_CHATMACRO0
```

---

<a id="hustr_talktoself1"></a>

### `HUSTR_TALKTOSELF1`

`macro` | [progs/doomgeneric/d_englsh.h:298](../../progs/doomgeneric/d_englsh.h#L298)

```c
#define HUSTR_TALKTOSELF1
```

---

<a id="hustr_talktoself2"></a>

### `HUSTR_TALKTOSELF2`

`macro` | [progs/doomgeneric/d_englsh.h:299](../../progs/doomgeneric/d_englsh.h#L299)

```c
#define HUSTR_TALKTOSELF2
```

---

<a id="hustr_talktoself3"></a>

### `HUSTR_TALKTOSELF3`

`macro` | [progs/doomgeneric/d_englsh.h:300](../../progs/doomgeneric/d_englsh.h#L300)

```c
#define HUSTR_TALKTOSELF3
```

---

<a id="hustr_talktoself4"></a>

### `HUSTR_TALKTOSELF4`

`macro` | [progs/doomgeneric/d_englsh.h:301](../../progs/doomgeneric/d_englsh.h#L301)

```c
#define HUSTR_TALKTOSELF4
```

---

<a id="hustr_talktoself5"></a>

### `HUSTR_TALKTOSELF5`

`macro` | [progs/doomgeneric/d_englsh.h:302](../../progs/doomgeneric/d_englsh.h#L302)

```c
#define HUSTR_TALKTOSELF5
```

---

<a id="hustr_messagesent"></a>

### `HUSTR_MESSAGESENT`

`macro` | [progs/doomgeneric/d_englsh.h:304](../../progs/doomgeneric/d_englsh.h#L304)

```c
#define HUSTR_MESSAGESENT
```

---

<a id="hustr_plrgreen"></a>

### `HUSTR_PLRGREEN`

`macro` | [progs/doomgeneric/d_englsh.h:309](../../progs/doomgeneric/d_englsh.h#L309)

```c
#define HUSTR_PLRGREEN
```

---

<a id="hustr_plrindigo"></a>

### `HUSTR_PLRINDIGO`

`macro` | [progs/doomgeneric/d_englsh.h:310](../../progs/doomgeneric/d_englsh.h#L310)

```c
#define HUSTR_PLRINDIGO
```

---

<a id="hustr_plrbrown"></a>

### `HUSTR_PLRBROWN`

`macro` | [progs/doomgeneric/d_englsh.h:311](../../progs/doomgeneric/d_englsh.h#L311)

```c
#define HUSTR_PLRBROWN
```

---

<a id="hustr_plrred"></a>

### `HUSTR_PLRRED`

`macro` | [progs/doomgeneric/d_englsh.h:312](../../progs/doomgeneric/d_englsh.h#L312)

```c
#define HUSTR_PLRRED
```

---

<a id="hustr_keygreen"></a>

### `HUSTR_KEYGREEN`

`macro` | [progs/doomgeneric/d_englsh.h:314](../../progs/doomgeneric/d_englsh.h#L314)

```c
#define HUSTR_KEYGREEN
```

---

<a id="hustr_keyindigo"></a>

### `HUSTR_KEYINDIGO`

`macro` | [progs/doomgeneric/d_englsh.h:315](../../progs/doomgeneric/d_englsh.h#L315)

```c
#define HUSTR_KEYINDIGO
```

---

<a id="hustr_keybrown"></a>

### `HUSTR_KEYBROWN`

`macro` | [progs/doomgeneric/d_englsh.h:316](../../progs/doomgeneric/d_englsh.h#L316)

```c
#define HUSTR_KEYBROWN
```

---

<a id="hustr_keyred"></a>

### `HUSTR_KEYRED`

`macro` | [progs/doomgeneric/d_englsh.h:317](../../progs/doomgeneric/d_englsh.h#L317)

```c
#define HUSTR_KEYRED
```

---

<a id="amstr_followon"></a>

### `AMSTR_FOLLOWON`

`macro` | [progs/doomgeneric/d_englsh.h:323](../../progs/doomgeneric/d_englsh.h#L323)

```c
#define AMSTR_FOLLOWON
```

---

<a id="amstr_followoff"></a>

### `AMSTR_FOLLOWOFF`

`macro` | [progs/doomgeneric/d_englsh.h:324](../../progs/doomgeneric/d_englsh.h#L324)

```c
#define AMSTR_FOLLOWOFF
```

---

<a id="amstr_gridon"></a>

### `AMSTR_GRIDON`

`macro` | [progs/doomgeneric/d_englsh.h:326](../../progs/doomgeneric/d_englsh.h#L326)

```c
#define AMSTR_GRIDON
```

---

<a id="amstr_gridoff"></a>

### `AMSTR_GRIDOFF`

`macro` | [progs/doomgeneric/d_englsh.h:327](../../progs/doomgeneric/d_englsh.h#L327)

```c
#define AMSTR_GRIDOFF
```

---

<a id="amstr_markedspot"></a>

### `AMSTR_MARKEDSPOT`

`macro` | [progs/doomgeneric/d_englsh.h:329](../../progs/doomgeneric/d_englsh.h#L329)

```c
#define AMSTR_MARKEDSPOT
```

---

<a id="amstr_markscleared"></a>

### `AMSTR_MARKSCLEARED`

`macro` | [progs/doomgeneric/d_englsh.h:330](../../progs/doomgeneric/d_englsh.h#L330)

```c
#define AMSTR_MARKSCLEARED
```

---

<a id="ststr_mus"></a>

### `STSTR_MUS`

`macro` | [progs/doomgeneric/d_englsh.h:336](../../progs/doomgeneric/d_englsh.h#L336)

```c
#define STSTR_MUS
```

---

<a id="ststr_nomus"></a>

### `STSTR_NOMUS`

`macro` | [progs/doomgeneric/d_englsh.h:337](../../progs/doomgeneric/d_englsh.h#L337)

```c
#define STSTR_NOMUS
```

---

<a id="ststr_dqdon"></a>

### `STSTR_DQDON`

`macro` | [progs/doomgeneric/d_englsh.h:338](../../progs/doomgeneric/d_englsh.h#L338)

```c
#define STSTR_DQDON
```

---

<a id="ststr_dqdoff"></a>

### `STSTR_DQDOFF`

`macro` | [progs/doomgeneric/d_englsh.h:339](../../progs/doomgeneric/d_englsh.h#L339)

```c
#define STSTR_DQDOFF
```

---

<a id="ststr_kfaadded"></a>

### `STSTR_KFAADDED`

`macro` | [progs/doomgeneric/d_englsh.h:341](../../progs/doomgeneric/d_englsh.h#L341)

```c
#define STSTR_KFAADDED
```

---

<a id="ststr_faadded"></a>

### `STSTR_FAADDED`

`macro` | [progs/doomgeneric/d_englsh.h:342](../../progs/doomgeneric/d_englsh.h#L342)

```c
#define STSTR_FAADDED
```

---

<a id="ststr_ncon"></a>

### `STSTR_NCON`

`macro` | [progs/doomgeneric/d_englsh.h:344](../../progs/doomgeneric/d_englsh.h#L344)

```c
#define STSTR_NCON
```

---

<a id="ststr_ncoff"></a>

### `STSTR_NCOFF`

`macro` | [progs/doomgeneric/d_englsh.h:345](../../progs/doomgeneric/d_englsh.h#L345)

```c
#define STSTR_NCOFF
```

---

<a id="ststr_behold"></a>

### `STSTR_BEHOLD`

`macro` | [progs/doomgeneric/d_englsh.h:347](../../progs/doomgeneric/d_englsh.h#L347)

```c
#define STSTR_BEHOLD
```

---

<a id="ststr_beholdx"></a>

### `STSTR_BEHOLDX`

`macro` | [progs/doomgeneric/d_englsh.h:348](../../progs/doomgeneric/d_englsh.h#L348)

```c
#define STSTR_BEHOLDX
```

---

<a id="ststr_choppers"></a>

### `STSTR_CHOPPERS`

`macro` | [progs/doomgeneric/d_englsh.h:350](../../progs/doomgeneric/d_englsh.h#L350)

```c
#define STSTR_CHOPPERS
```

---

<a id="ststr_clev"></a>

### `STSTR_CLEV`

`macro` | [progs/doomgeneric/d_englsh.h:351](../../progs/doomgeneric/d_englsh.h#L351)

```c
#define STSTR_CLEV
```

---

<a id="e1text"></a>

### `E1TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:356](../../progs/doomgeneric/d_englsh.h#L356)

```c
#define E1TEXT
```

F_Finale.C

---

<a id="e2text"></a>

### `E2TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:374](../../progs/doomgeneric/d_englsh.h#L374)

```c
#define E2TEXT
```

---

<a id="e3text"></a>

### `E3TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:394](../../progs/doomgeneric/d_englsh.h#L394)

```c
#define E3TEXT
```

---

<a id="e4text"></a>

### `E4TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:414](../../progs/doomgeneric/d_englsh.h#L414)

```c
#define E4TEXT
```

---

<a id="c1text"></a>

### `C1TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:435](../../progs/doomgeneric/d_englsh.h#L435)

```c
#define C1TEXT
```

---

<a id="c2text"></a>

### `C2TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:451](../../progs/doomgeneric/d_englsh.h#L451)

```c
#define C2TEXT
```

---

<a id="c3text"></a>

### `C3TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:473](../../progs/doomgeneric/d_englsh.h#L473)

```c
#define C3TEXT
```

---

<a id="c4text"></a>

### `C4TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:487](../../progs/doomgeneric/d_englsh.h#L487)

```c
#define C4TEXT
```

---

<a id="c5text"></a>

### `C5TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:508](../../progs/doomgeneric/d_englsh.h#L508)

```c
#define C5TEXT
```

---

<a id="c6text"></a>

### `C6TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:518](../../progs/doomgeneric/d_englsh.h#L518)

```c
#define C6TEXT
```

---

<a id="p1text"></a>

### `P1TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:526](../../progs/doomgeneric/d_englsh.h#L526)

```c
#define P1TEXT
```

---

<a id="p2text"></a>

### `P2TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:543](../../progs/doomgeneric/d_englsh.h#L543)

```c
#define P2TEXT
```

---

<a id="p3text"></a>

### `P3TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:554](../../progs/doomgeneric/d_englsh.h#L554)

```c
#define P3TEXT
```

---

<a id="p4text"></a>

### `P4TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:568](../../progs/doomgeneric/d_englsh.h#L568)

```c
#define P4TEXT
```

---

<a id="p5text"></a>

### `P5TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:584](../../progs/doomgeneric/d_englsh.h#L584)

```c
#define P5TEXT
```

---

<a id="p6text"></a>

### `P6TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:592](../../progs/doomgeneric/d_englsh.h#L592)

```c
#define P6TEXT
```

---

<a id="t1text"></a>

### `T1TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:598](../../progs/doomgeneric/d_englsh.h#L598)

```c
#define T1TEXT
```

---

<a id="t2text"></a>

### `T2TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:613](../../progs/doomgeneric/d_englsh.h#L613)

```c
#define T2TEXT
```

---

<a id="t3text"></a>

### `T3TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:625](../../progs/doomgeneric/d_englsh.h#L625)

```c
#define T3TEXT
```

---

<a id="t4text"></a>

### `T4TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:635](../../progs/doomgeneric/d_englsh.h#L635)

```c
#define T4TEXT
```

---

<a id="t5text"></a>

### `T5TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:649](../../progs/doomgeneric/d_englsh.h#L649)

```c
#define T5TEXT
```

---

<a id="t6text"></a>

### `T6TEXT`

`macro` | [progs/doomgeneric/d_englsh.h:657](../../progs/doomgeneric/d_englsh.h#L657)

```c
#define T6TEXT
```

---

<a id="cc_zombie"></a>

### `CC_ZOMBIE`

`macro` | [progs/doomgeneric/d_englsh.h:674](../../progs/doomgeneric/d_englsh.h#L674)

```c
#define CC_ZOMBIE
```

Character cast strings F_FINALE.C

---

<a id="cc_shotgun"></a>

### `CC_SHOTGUN`

`macro` | [progs/doomgeneric/d_englsh.h:675](../../progs/doomgeneric/d_englsh.h#L675)

```c
#define CC_SHOTGUN
```

---

<a id="cc_heavy"></a>

### `CC_HEAVY`

`macro` | [progs/doomgeneric/d_englsh.h:676](../../progs/doomgeneric/d_englsh.h#L676)

```c
#define CC_HEAVY
```

---

<a id="cc_imp"></a>

### `CC_IMP`

`macro` | [progs/doomgeneric/d_englsh.h:677](../../progs/doomgeneric/d_englsh.h#L677)

```c
#define CC_IMP
```

---

<a id="cc_demon"></a>

### `CC_DEMON`

`macro` | [progs/doomgeneric/d_englsh.h:678](../../progs/doomgeneric/d_englsh.h#L678)

```c
#define CC_DEMON
```

---

<a id="cc_lost"></a>

### `CC_LOST`

`macro` | [progs/doomgeneric/d_englsh.h:679](../../progs/doomgeneric/d_englsh.h#L679)

```c
#define CC_LOST
```

---

<a id="cc_caco"></a>

### `CC_CACO`

`macro` | [progs/doomgeneric/d_englsh.h:680](../../progs/doomgeneric/d_englsh.h#L680)

```c
#define CC_CACO
```

---

<a id="cc_hell"></a>

### `CC_HELL`

`macro` | [progs/doomgeneric/d_englsh.h:681](../../progs/doomgeneric/d_englsh.h#L681)

```c
#define CC_HELL
```

---

<a id="cc_baron"></a>

### `CC_BARON`

`macro` | [progs/doomgeneric/d_englsh.h:682](../../progs/doomgeneric/d_englsh.h#L682)

```c
#define CC_BARON
```

---

<a id="cc_arach"></a>

### `CC_ARACH`

`macro` | [progs/doomgeneric/d_englsh.h:683](../../progs/doomgeneric/d_englsh.h#L683)

```c
#define CC_ARACH
```

---

<a id="cc_pain"></a>

### `CC_PAIN`

`macro` | [progs/doomgeneric/d_englsh.h:684](../../progs/doomgeneric/d_englsh.h#L684)

```c
#define CC_PAIN
```

---

<a id="cc_reven"></a>

### `CC_REVEN`

`macro` | [progs/doomgeneric/d_englsh.h:685](../../progs/doomgeneric/d_englsh.h#L685)

```c
#define CC_REVEN
```

---

<a id="cc_mancu"></a>

### `CC_MANCU`

`macro` | [progs/doomgeneric/d_englsh.h:686](../../progs/doomgeneric/d_englsh.h#L686)

```c
#define CC_MANCU
```

---

<a id="cc_arch"></a>

### `CC_ARCH`

`macro` | [progs/doomgeneric/d_englsh.h:687](../../progs/doomgeneric/d_englsh.h#L687)

```c
#define CC_ARCH
```

---

<a id="cc_spider"></a>

### `CC_SPIDER`

`macro` | [progs/doomgeneric/d_englsh.h:688](../../progs/doomgeneric/d_englsh.h#L688)

```c
#define CC_SPIDER
```

---

<a id="cc_cyber"></a>

### `CC_CYBER`

`macro` | [progs/doomgeneric/d_englsh.h:689](../../progs/doomgeneric/d_englsh.h#L689)

```c
#define CC_CYBER
```

---

<a id="cc_hero"></a>

### `CC_HERO`

`macro` | [progs/doomgeneric/d_englsh.h:690](../../progs/doomgeneric/d_englsh.h#L690)

```c
#define CC_HERO
```

---
