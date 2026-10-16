# `progs/doomgeneric/m_controls.h`

> Source: [progs/doomgeneric/m_controls.h:1](../../progs/doomgeneric/m_controls.h#L1) | language `h` | coverage 10.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 1993-2008 Raven Software Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

## Contents

- **Functions:** [`M_BindBaseControls`](#m_bindbasecontrols), [`M_BindHereticControls`](#m_bindhereticcontrols), [`M_BindHexenControls`](#m_bindhexencontrols), [`M_BindStrifeControls`](#m_bindstrifecontrols), [`M_BindWeaponControls`](#m_bindweaponcontrols), [`M_BindMapControls`](#m_bindmapcontrols), [`M_BindMenuControls`](#m_bindmenucontrols), [`M_BindChatControls`](#m_bindchatcontrols), [`M_ApplyPlatformDefaults`](#m_applyplatformdefaults)
- **Variables:** [`key_right`](#key_right), [`key_left`](#key_left), [`key_up`](#key_up), [`key_down`](#key_down), [`key_strafeleft`](#key_strafeleft), [`key_straferight`](#key_straferight), [`key_fire`](#key_fire), [`key_use`](#key_use), [`key_strafe`](#key_strafe), [`key_speed`](#key_speed), [`key_jump`](#key_jump), [`key_flyup`](#key_flyup), [`key_flydown`](#key_flydown), [`key_flycenter`](#key_flycenter), [`key_lookup`](#key_lookup), [`key_lookdown`](#key_lookdown), [`key_lookcenter`](#key_lookcenter), [`key_invleft`](#key_invleft), [`key_invright`](#key_invright), [`key_useartifact`](#key_useartifact), [`key_usehealth`](#key_usehealth), [`key_invquery`](#key_invquery), [`key_mission`](#key_mission), [`key_invpop`](#key_invpop), [`key_invkey`](#key_invkey), [`key_invhome`](#key_invhome), [`key_invend`](#key_invend), [`key_invuse`](#key_invuse), [`key_invdrop`](#key_invdrop), [`key_message_refresh`](#key_message_refresh), [`key_pause`](#key_pause), [`key_multi_msg`](#key_multi_msg), [`key_multi_msgplayer`](#key_multi_msgplayer), [`key_weapon1`](#key_weapon1), [`key_weapon2`](#key_weapon2), [`key_weapon3`](#key_weapon3), [`key_weapon4`](#key_weapon4), [`key_weapon5`](#key_weapon5), [`key_weapon6`](#key_weapon6), [`key_weapon7`](#key_weapon7), [`key_weapon8`](#key_weapon8), [`key_arti_all`](#key_arti_all), [`key_arti_health`](#key_arti_health), [`key_arti_poisonbag`](#key_arti_poisonbag), [`key_arti_blastradius`](#key_arti_blastradius), [`key_arti_teleport`](#key_arti_teleport), [`key_arti_teleportother`](#key_arti_teleportother), [`key_arti_egg`](#key_arti_egg), [`key_arti_invulnerability`](#key_arti_invulnerability), [`key_demo_quit`](#key_demo_quit), [`key_spy`](#key_spy), [`key_prevweapon`](#key_prevweapon), [`key_nextweapon`](#key_nextweapon), [`key_map_north`](#key_map_north), [`key_map_south`](#key_map_south), [`key_map_east`](#key_map_east), [`key_map_west`](#key_map_west), [`key_map_zoomin`](#key_map_zoomin), [`key_map_zoomout`](#key_map_zoomout), [`key_map_toggle`](#key_map_toggle), [`key_map_maxzoom`](#key_map_maxzoom), [`key_map_follow`](#key_map_follow), [`key_map_grid`](#key_map_grid), [`key_map_mark`](#key_map_mark), [`key_map_clearmark`](#key_map_clearmark), [`key_menu_activate`](#key_menu_activate), [`key_menu_up`](#key_menu_up), [`key_menu_down`](#key_menu_down), [`key_menu_left`](#key_menu_left), [`key_menu_right`](#key_menu_right), [`key_menu_back`](#key_menu_back), [`key_menu_forward`](#key_menu_forward), [`key_menu_confirm`](#key_menu_confirm), [`key_menu_abort`](#key_menu_abort), [`key_menu_help`](#key_menu_help), [`key_menu_save`](#key_menu_save), [`key_menu_load`](#key_menu_load), [`key_menu_volume`](#key_menu_volume), [`key_menu_detail`](#key_menu_detail), [`key_menu_qsave`](#key_menu_qsave), [`key_menu_endgame`](#key_menu_endgame), [`key_menu_messages`](#key_menu_messages), [`key_menu_qload`](#key_menu_qload), [`key_menu_quit`](#key_menu_quit), [`key_menu_gamma`](#key_menu_gamma), [`key_menu_incscreen`](#key_menu_incscreen), [`key_menu_decscreen`](#key_menu_decscreen), [`key_menu_screenshot`](#key_menu_screenshot), [`mousebfire`](#mousebfire), [`mousebstrafe`](#mousebstrafe), [`mousebforward`](#mousebforward), [`mousebjump`](#mousebjump), [`mousebstrafeleft`](#mousebstrafeleft), [`mousebstraferight`](#mousebstraferight), [`mousebbackward`](#mousebbackward), [`mousebuse`](#mousebuse), [`mousebprevweapon`](#mousebprevweapon), [`mousebnextweapon`](#mousebnextweapon), [`joybfire`](#joybfire), [`joybstrafe`](#joybstrafe), [`joybuse`](#joybuse), [`joybspeed`](#joybspeed), [`joybjump`](#joybjump), [`joybstrafeleft`](#joybstrafeleft), [`joybstraferight`](#joybstraferight), [`joybprevweapon`](#joybprevweapon), [`joybnextweapon`](#joybnextweapon), [`joybmenu`](#joybmenu), [`dclick_use`](#dclick_use)

## Functions

<a id="m_bindbasecontrols"></a>

### `M_BindBaseControls`

`function` | [progs/doomgeneric/m_controls.h:156](../../progs/doomgeneric/m_controls.h#L156)

```c
void M_BindBaseControls(void);
```

*Called by:* [`D_BindVariables`](progs.doomgeneric.d_main.c.md#d_bindvariables)

---

<a id="m_bindhereticcontrols"></a>

### `M_BindHereticControls`

`function` | [progs/doomgeneric/m_controls.h:157](../../progs/doomgeneric/m_controls.h#L157)

```c
void M_BindHereticControls(void);
```

---

<a id="m_bindhexencontrols"></a>

### `M_BindHexenControls`

`function` | [progs/doomgeneric/m_controls.h:158](../../progs/doomgeneric/m_controls.h#L158)

```c
void M_BindHexenControls(void);
```

---

<a id="m_bindstrifecontrols"></a>

### `M_BindStrifeControls`

`function` | [progs/doomgeneric/m_controls.h:159](../../progs/doomgeneric/m_controls.h#L159)

```c
void M_BindStrifeControls(void);
```

---

<a id="m_bindweaponcontrols"></a>

### `M_BindWeaponControls`

`function` | [progs/doomgeneric/m_controls.h:160](../../progs/doomgeneric/m_controls.h#L160)

```c
void M_BindWeaponControls(void);
```

*Called by:* [`D_BindVariables`](progs.doomgeneric.d_main.c.md#d_bindvariables)

---

<a id="m_bindmapcontrols"></a>

### `M_BindMapControls`

`function` | [progs/doomgeneric/m_controls.h:161](../../progs/doomgeneric/m_controls.h#L161)

```c
void M_BindMapControls(void);
```

*Called by:* [`D_BindVariables`](progs.doomgeneric.d_main.c.md#d_bindvariables)

---

<a id="m_bindmenucontrols"></a>

### `M_BindMenuControls`

`function` | [progs/doomgeneric/m_controls.h:162](../../progs/doomgeneric/m_controls.h#L162)

```c
void M_BindMenuControls(void);
```

*Called by:* [`D_BindVariables`](progs.doomgeneric.d_main.c.md#d_bindvariables)

---

<a id="m_bindchatcontrols"></a>

### `M_BindChatControls`

`function` | [progs/doomgeneric/m_controls.h:163](../../progs/doomgeneric/m_controls.h#L163)

```c
void M_BindChatControls(unsigned int num_players);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `num_players` | `unsigned int` |  |  |

*Called by:* [`D_BindVariables`](progs.doomgeneric.d_main.c.md#d_bindvariables)

---

<a id="m_applyplatformdefaults"></a>

### `M_ApplyPlatformDefaults`

`function` | [progs/doomgeneric/m_controls.h:165](../../progs/doomgeneric/m_controls.h#L165)

```c
void M_ApplyPlatformDefaults(void);
```

*Called by:* [`D_BindVariables`](progs.doomgeneric.d_main.c.md#d_bindvariables)

---

## Variables

<a id="key_right"></a>

### `key_right`

`variable` `extern` | [progs/doomgeneric/m_controls.h:20](../../progs/doomgeneric/m_controls.h#L20)

```c
extern int key_right;
```

---

<a id="key_left"></a>

### `key_left`

`variable` `extern` | [progs/doomgeneric/m_controls.h:21](../../progs/doomgeneric/m_controls.h#L21)

```c
extern int key_left;
```

---

<a id="key_up"></a>

### `key_up`

`variable` `extern` | [progs/doomgeneric/m_controls.h:23](../../progs/doomgeneric/m_controls.h#L23)

```c
extern int key_up;
```

---

<a id="key_down"></a>

### `key_down`

`variable` `extern` | [progs/doomgeneric/m_controls.h:24](../../progs/doomgeneric/m_controls.h#L24)

```c
extern int key_down;
```

---

<a id="key_strafeleft"></a>

### `key_strafeleft`

`variable` `extern` | [progs/doomgeneric/m_controls.h:25](../../progs/doomgeneric/m_controls.h#L25)

```c
extern int key_strafeleft;
```

---

<a id="key_straferight"></a>

### `key_straferight`

`variable` `extern` | [progs/doomgeneric/m_controls.h:26](../../progs/doomgeneric/m_controls.h#L26)

```c
extern int key_straferight;
```

---

<a id="key_fire"></a>

### `key_fire`

`variable` `extern` | [progs/doomgeneric/m_controls.h:27](../../progs/doomgeneric/m_controls.h#L27)

```c
extern int key_fire;
```

---

<a id="key_use"></a>

### `key_use`

`variable` `extern` | [progs/doomgeneric/m_controls.h:28](../../progs/doomgeneric/m_controls.h#L28)

```c
extern int key_use;
```

---

<a id="key_strafe"></a>

### `key_strafe`

`variable` `extern` | [progs/doomgeneric/m_controls.h:29](../../progs/doomgeneric/m_controls.h#L29)

```c
extern int key_strafe;
```

---

<a id="key_speed"></a>

### `key_speed`

`variable` `extern` | [progs/doomgeneric/m_controls.h:30](../../progs/doomgeneric/m_controls.h#L30)

```c
extern int key_speed;
```

---

<a id="key_jump"></a>

### `key_jump`

`variable` `extern` | [progs/doomgeneric/m_controls.h:32](../../progs/doomgeneric/m_controls.h#L32)

```c
extern int key_jump;
```

---

<a id="key_flyup"></a>

### `key_flyup`

`variable` `extern` | [progs/doomgeneric/m_controls.h:34](../../progs/doomgeneric/m_controls.h#L34)

```c
extern int key_flyup;
```

---

<a id="key_flydown"></a>

### `key_flydown`

`variable` `extern` | [progs/doomgeneric/m_controls.h:35](../../progs/doomgeneric/m_controls.h#L35)

```c
extern int key_flydown;
```

---

<a id="key_flycenter"></a>

### `key_flycenter`

`variable` `extern` | [progs/doomgeneric/m_controls.h:36](../../progs/doomgeneric/m_controls.h#L36)

```c
extern int key_flycenter;
```

---

<a id="key_lookup"></a>

### `key_lookup`

`variable` `extern` | [progs/doomgeneric/m_controls.h:37](../../progs/doomgeneric/m_controls.h#L37)

```c
extern int key_lookup;
```

---

<a id="key_lookdown"></a>

### `key_lookdown`

`variable` `extern` | [progs/doomgeneric/m_controls.h:38](../../progs/doomgeneric/m_controls.h#L38)

```c
extern int key_lookdown;
```

---

<a id="key_lookcenter"></a>

### `key_lookcenter`

`variable` `extern` | [progs/doomgeneric/m_controls.h:39](../../progs/doomgeneric/m_controls.h#L39)

```c
extern int key_lookcenter;
```

---

<a id="key_invleft"></a>

### `key_invleft`

`variable` `extern` | [progs/doomgeneric/m_controls.h:40](../../progs/doomgeneric/m_controls.h#L40)

```c
extern int key_invleft;
```

---

<a id="key_invright"></a>

### `key_invright`

`variable` `extern` | [progs/doomgeneric/m_controls.h:41](../../progs/doomgeneric/m_controls.h#L41)

```c
extern int key_invright;
```

---

<a id="key_useartifact"></a>

### `key_useartifact`

`variable` `extern` | [progs/doomgeneric/m_controls.h:42](../../progs/doomgeneric/m_controls.h#L42)

```c
extern int key_useartifact;
```

---

<a id="key_usehealth"></a>

### `key_usehealth`

`variable` `extern` | [progs/doomgeneric/m_controls.h:45](../../progs/doomgeneric/m_controls.h#L45)

```c
extern int key_usehealth;
```

villsa [STRIFE] strife keys

---

<a id="key_invquery"></a>

### `key_invquery`

`variable` `extern` | [progs/doomgeneric/m_controls.h:46](../../progs/doomgeneric/m_controls.h#L46)

```c
extern int key_invquery;
```

---

<a id="key_mission"></a>

### `key_mission`

`variable` `extern` | [progs/doomgeneric/m_controls.h:47](../../progs/doomgeneric/m_controls.h#L47)

```c
extern int key_mission;
```

---

<a id="key_invpop"></a>

### `key_invpop`

`variable` `extern` | [progs/doomgeneric/m_controls.h:48](../../progs/doomgeneric/m_controls.h#L48)

```c
extern int key_invpop;
```

---

<a id="key_invkey"></a>

### `key_invkey`

`variable` `extern` | [progs/doomgeneric/m_controls.h:49](../../progs/doomgeneric/m_controls.h#L49)

```c
extern int key_invkey;
```

---

<a id="key_invhome"></a>

### `key_invhome`

`variable` `extern` | [progs/doomgeneric/m_controls.h:50](../../progs/doomgeneric/m_controls.h#L50)

```c
extern int key_invhome;
```

---

<a id="key_invend"></a>

### `key_invend`

`variable` `extern` | [progs/doomgeneric/m_controls.h:51](../../progs/doomgeneric/m_controls.h#L51)

```c
extern int key_invend;
```

---

<a id="key_invuse"></a>

### `key_invuse`

`variable` `extern` | [progs/doomgeneric/m_controls.h:52](../../progs/doomgeneric/m_controls.h#L52)

```c
extern int key_invuse;
```

---

<a id="key_invdrop"></a>

### `key_invdrop`

`variable` `extern` | [progs/doomgeneric/m_controls.h:53](../../progs/doomgeneric/m_controls.h#L53)

```c
extern int key_invdrop;
```

---

<a id="key_message_refresh"></a>

### `key_message_refresh`

`variable` `extern` | [progs/doomgeneric/m_controls.h:55](../../progs/doomgeneric/m_controls.h#L55)

```c
extern int key_message_refresh;
```

---

<a id="key_pause"></a>

### `key_pause`

`variable` `extern` | [progs/doomgeneric/m_controls.h:56](../../progs/doomgeneric/m_controls.h#L56)

```c
extern int key_pause;
```

---

<a id="key_multi_msg"></a>

### `key_multi_msg`

`variable` `extern` | [progs/doomgeneric/m_controls.h:58](../../progs/doomgeneric/m_controls.h#L58)

```c
extern int key_multi_msg;
```

---

<a id="key_multi_msgplayer"></a>

### `key_multi_msgplayer`

`variable` `extern` | [progs/doomgeneric/m_controls.h:59](../../progs/doomgeneric/m_controls.h#L59)

```c
extern int key_multi_msgplayer[8];
```

---

<a id="key_weapon1"></a>

### `key_weapon1`

`variable` `extern` | [progs/doomgeneric/m_controls.h:61](../../progs/doomgeneric/m_controls.h#L61)

```c
extern int key_weapon1;
```

---

<a id="key_weapon2"></a>

### `key_weapon2`

`variable` `extern` | [progs/doomgeneric/m_controls.h:62](../../progs/doomgeneric/m_controls.h#L62)

```c
extern int key_weapon2;
```

---

<a id="key_weapon3"></a>

### `key_weapon3`

`variable` `extern` | [progs/doomgeneric/m_controls.h:63](../../progs/doomgeneric/m_controls.h#L63)

```c
extern int key_weapon3;
```

---

<a id="key_weapon4"></a>

### `key_weapon4`

`variable` `extern` | [progs/doomgeneric/m_controls.h:64](../../progs/doomgeneric/m_controls.h#L64)

```c
extern int key_weapon4;
```

---

<a id="key_weapon5"></a>

### `key_weapon5`

`variable` `extern` | [progs/doomgeneric/m_controls.h:65](../../progs/doomgeneric/m_controls.h#L65)

```c
extern int key_weapon5;
```

---

<a id="key_weapon6"></a>

### `key_weapon6`

`variable` `extern` | [progs/doomgeneric/m_controls.h:66](../../progs/doomgeneric/m_controls.h#L66)

```c
extern int key_weapon6;
```

---

<a id="key_weapon7"></a>

### `key_weapon7`

`variable` `extern` | [progs/doomgeneric/m_controls.h:67](../../progs/doomgeneric/m_controls.h#L67)

```c
extern int key_weapon7;
```

---

<a id="key_weapon8"></a>

### `key_weapon8`

`variable` `extern` | [progs/doomgeneric/m_controls.h:68](../../progs/doomgeneric/m_controls.h#L68)

```c
extern int key_weapon8;
```

---

<a id="key_arti_all"></a>

### `key_arti_all`

`variable` `extern` | [progs/doomgeneric/m_controls.h:70](../../progs/doomgeneric/m_controls.h#L70)

```c
extern int key_arti_all;
```

---

<a id="key_arti_health"></a>

### `key_arti_health`

`variable` `extern` | [progs/doomgeneric/m_controls.h:71](../../progs/doomgeneric/m_controls.h#L71)

```c
extern int key_arti_health;
```

---

<a id="key_arti_poisonbag"></a>

### `key_arti_poisonbag`

`variable` `extern` | [progs/doomgeneric/m_controls.h:72](../../progs/doomgeneric/m_controls.h#L72)

```c
extern int key_arti_poisonbag;
```

---

<a id="key_arti_blastradius"></a>

### `key_arti_blastradius`

`variable` `extern` | [progs/doomgeneric/m_controls.h:73](../../progs/doomgeneric/m_controls.h#L73)

```c
extern int key_arti_blastradius;
```

---

<a id="key_arti_teleport"></a>

### `key_arti_teleport`

`variable` `extern` | [progs/doomgeneric/m_controls.h:74](../../progs/doomgeneric/m_controls.h#L74)

```c
extern int key_arti_teleport;
```

---

<a id="key_arti_teleportother"></a>

### `key_arti_teleportother`

`variable` `extern` | [progs/doomgeneric/m_controls.h:75](../../progs/doomgeneric/m_controls.h#L75)

```c
extern int key_arti_teleportother;
```

---

<a id="key_arti_egg"></a>

### `key_arti_egg`

`variable` `extern` | [progs/doomgeneric/m_controls.h:76](../../progs/doomgeneric/m_controls.h#L76)

```c
extern int key_arti_egg;
```

---

<a id="key_arti_invulnerability"></a>

### `key_arti_invulnerability`

`variable` `extern` | [progs/doomgeneric/m_controls.h:77](../../progs/doomgeneric/m_controls.h#L77)

```c
extern int key_arti_invulnerability;
```

---

<a id="key_demo_quit"></a>

### `key_demo_quit`

`variable` `extern` | [progs/doomgeneric/m_controls.h:79](../../progs/doomgeneric/m_controls.h#L79)

```c
extern int key_demo_quit;
```

---

<a id="key_spy"></a>

### `key_spy`

`variable` `extern` | [progs/doomgeneric/m_controls.h:80](../../progs/doomgeneric/m_controls.h#L80)

```c
extern int key_spy;
```

---

<a id="key_prevweapon"></a>

### `key_prevweapon`

`variable` `extern` | [progs/doomgeneric/m_controls.h:81](../../progs/doomgeneric/m_controls.h#L81)

```c
extern int key_prevweapon;
```

---

<a id="key_nextweapon"></a>

### `key_nextweapon`

`variable` `extern` | [progs/doomgeneric/m_controls.h:82](../../progs/doomgeneric/m_controls.h#L82)

```c
extern int key_nextweapon;
```

---

<a id="key_map_north"></a>

### `key_map_north`

`variable` `extern` | [progs/doomgeneric/m_controls.h:84](../../progs/doomgeneric/m_controls.h#L84)

```c
extern int key_map_north;
```

---

<a id="key_map_south"></a>

### `key_map_south`

`variable` `extern` | [progs/doomgeneric/m_controls.h:85](../../progs/doomgeneric/m_controls.h#L85)

```c
extern int key_map_south;
```

---

<a id="key_map_east"></a>

### `key_map_east`

`variable` `extern` | [progs/doomgeneric/m_controls.h:86](../../progs/doomgeneric/m_controls.h#L86)

```c
extern int key_map_east;
```

---

<a id="key_map_west"></a>

### `key_map_west`

`variable` `extern` | [progs/doomgeneric/m_controls.h:87](../../progs/doomgeneric/m_controls.h#L87)

```c
extern int key_map_west;
```

---

<a id="key_map_zoomin"></a>

### `key_map_zoomin`

`variable` `extern` | [progs/doomgeneric/m_controls.h:88](../../progs/doomgeneric/m_controls.h#L88)

```c
extern int key_map_zoomin;
```

---

<a id="key_map_zoomout"></a>

### `key_map_zoomout`

`variable` `extern` | [progs/doomgeneric/m_controls.h:89](../../progs/doomgeneric/m_controls.h#L89)

```c
extern int key_map_zoomout;
```

---

<a id="key_map_toggle"></a>

### `key_map_toggle`

`variable` `extern` | [progs/doomgeneric/m_controls.h:90](../../progs/doomgeneric/m_controls.h#L90)

```c
extern int key_map_toggle;
```

---

<a id="key_map_maxzoom"></a>

### `key_map_maxzoom`

`variable` `extern` | [progs/doomgeneric/m_controls.h:91](../../progs/doomgeneric/m_controls.h#L91)

```c
extern int key_map_maxzoom;
```

---

<a id="key_map_follow"></a>

### `key_map_follow`

`variable` `extern` | [progs/doomgeneric/m_controls.h:92](../../progs/doomgeneric/m_controls.h#L92)

```c
extern int key_map_follow;
```

---

<a id="key_map_grid"></a>

### `key_map_grid`

`variable` `extern` | [progs/doomgeneric/m_controls.h:93](../../progs/doomgeneric/m_controls.h#L93)

```c
extern int key_map_grid;
```

---

<a id="key_map_mark"></a>

### `key_map_mark`

`variable` `extern` | [progs/doomgeneric/m_controls.h:94](../../progs/doomgeneric/m_controls.h#L94)

```c
extern int key_map_mark;
```

---

<a id="key_map_clearmark"></a>

### `key_map_clearmark`

`variable` `extern` | [progs/doomgeneric/m_controls.h:95](../../progs/doomgeneric/m_controls.h#L95)

```c
extern int key_map_clearmark;
```

---

<a id="key_menu_activate"></a>

### `key_menu_activate`

`variable` `extern` | [progs/doomgeneric/m_controls.h:99](../../progs/doomgeneric/m_controls.h#L99)

```c
extern int key_menu_activate;
```

---

<a id="key_menu_up"></a>

### `key_menu_up`

`variable` `extern` | [progs/doomgeneric/m_controls.h:100](../../progs/doomgeneric/m_controls.h#L100)

```c
extern int key_menu_up;
```

---

<a id="key_menu_down"></a>

### `key_menu_down`

`variable` `extern` | [progs/doomgeneric/m_controls.h:101](../../progs/doomgeneric/m_controls.h#L101)

```c
extern int key_menu_down;
```

---

<a id="key_menu_left"></a>

### `key_menu_left`

`variable` `extern` | [progs/doomgeneric/m_controls.h:102](../../progs/doomgeneric/m_controls.h#L102)

```c
extern int key_menu_left;
```

---

<a id="key_menu_right"></a>

### `key_menu_right`

`variable` `extern` | [progs/doomgeneric/m_controls.h:103](../../progs/doomgeneric/m_controls.h#L103)

```c
extern int key_menu_right;
```

---

<a id="key_menu_back"></a>

### `key_menu_back`

`variable` `extern` | [progs/doomgeneric/m_controls.h:104](../../progs/doomgeneric/m_controls.h#L104)

```c
extern int key_menu_back;
```

---

<a id="key_menu_forward"></a>

### `key_menu_forward`

`variable` `extern` | [progs/doomgeneric/m_controls.h:105](../../progs/doomgeneric/m_controls.h#L105)

```c
extern int key_menu_forward;
```

---

<a id="key_menu_confirm"></a>

### `key_menu_confirm`

`variable` `extern` | [progs/doomgeneric/m_controls.h:106](../../progs/doomgeneric/m_controls.h#L106)

```c
extern int key_menu_confirm;
```

---

<a id="key_menu_abort"></a>

### `key_menu_abort`

`variable` `extern` | [progs/doomgeneric/m_controls.h:107](../../progs/doomgeneric/m_controls.h#L107)

```c
extern int key_menu_abort;
```

---

<a id="key_menu_help"></a>

### `key_menu_help`

`variable` `extern` | [progs/doomgeneric/m_controls.h:109](../../progs/doomgeneric/m_controls.h#L109)

```c
extern int key_menu_help;
```

---

<a id="key_menu_save"></a>

### `key_menu_save`

`variable` `extern` | [progs/doomgeneric/m_controls.h:110](../../progs/doomgeneric/m_controls.h#L110)

```c
extern int key_menu_save;
```

---

<a id="key_menu_load"></a>

### `key_menu_load`

`variable` `extern` | [progs/doomgeneric/m_controls.h:111](../../progs/doomgeneric/m_controls.h#L111)

```c
extern int key_menu_load;
```

---

<a id="key_menu_volume"></a>

### `key_menu_volume`

`variable` `extern` | [progs/doomgeneric/m_controls.h:112](../../progs/doomgeneric/m_controls.h#L112)

```c
extern int key_menu_volume;
```

---

<a id="key_menu_detail"></a>

### `key_menu_detail`

`variable` `extern` | [progs/doomgeneric/m_controls.h:113](../../progs/doomgeneric/m_controls.h#L113)

```c
extern int key_menu_detail;
```

---

<a id="key_menu_qsave"></a>

### `key_menu_qsave`

`variable` `extern` | [progs/doomgeneric/m_controls.h:114](../../progs/doomgeneric/m_controls.h#L114)

```c
extern int key_menu_qsave;
```

---

<a id="key_menu_endgame"></a>

### `key_menu_endgame`

`variable` `extern` | [progs/doomgeneric/m_controls.h:115](../../progs/doomgeneric/m_controls.h#L115)

```c
extern int key_menu_endgame;
```

---

<a id="key_menu_messages"></a>

### `key_menu_messages`

`variable` `extern` | [progs/doomgeneric/m_controls.h:116](../../progs/doomgeneric/m_controls.h#L116)

```c
extern int key_menu_messages;
```

---

<a id="key_menu_qload"></a>

### `key_menu_qload`

`variable` `extern` | [progs/doomgeneric/m_controls.h:117](../../progs/doomgeneric/m_controls.h#L117)

```c
extern int key_menu_qload;
```

---

<a id="key_menu_quit"></a>

### `key_menu_quit`

`variable` `extern` | [progs/doomgeneric/m_controls.h:118](../../progs/doomgeneric/m_controls.h#L118)

```c
extern int key_menu_quit;
```

---

<a id="key_menu_gamma"></a>

### `key_menu_gamma`

`variable` `extern` | [progs/doomgeneric/m_controls.h:119](../../progs/doomgeneric/m_controls.h#L119)

```c
extern int key_menu_gamma;
```

---

<a id="key_menu_incscreen"></a>

### `key_menu_incscreen`

`variable` `extern` | [progs/doomgeneric/m_controls.h:121](../../progs/doomgeneric/m_controls.h#L121)

```c
extern int key_menu_incscreen;
```

---

<a id="key_menu_decscreen"></a>

### `key_menu_decscreen`

`variable` `extern` | [progs/doomgeneric/m_controls.h:122](../../progs/doomgeneric/m_controls.h#L122)

```c
extern int key_menu_decscreen;
```

---

<a id="key_menu_screenshot"></a>

### `key_menu_screenshot`

`variable` `extern` | [progs/doomgeneric/m_controls.h:123](../../progs/doomgeneric/m_controls.h#L123)

```c
extern int key_menu_screenshot;
```

---

<a id="mousebfire"></a>

### `mousebfire`

`variable` `extern` | [progs/doomgeneric/m_controls.h:125](../../progs/doomgeneric/m_controls.h#L125)

```c
extern int mousebfire;
```

---

<a id="mousebstrafe"></a>

### `mousebstrafe`

`variable` `extern` | [progs/doomgeneric/m_controls.h:126](../../progs/doomgeneric/m_controls.h#L126)

```c
extern int mousebstrafe;
```

---

<a id="mousebforward"></a>

### `mousebforward`

`variable` `extern` | [progs/doomgeneric/m_controls.h:127](../../progs/doomgeneric/m_controls.h#L127)

```c
extern int mousebforward;
```

---

<a id="mousebjump"></a>

### `mousebjump`

`variable` `extern` | [progs/doomgeneric/m_controls.h:129](../../progs/doomgeneric/m_controls.h#L129)

```c
extern int mousebjump;
```

---

<a id="mousebstrafeleft"></a>

### `mousebstrafeleft`

`variable` `extern` | [progs/doomgeneric/m_controls.h:131](../../progs/doomgeneric/m_controls.h#L131)

```c
extern int mousebstrafeleft;
```

---

<a id="mousebstraferight"></a>

### `mousebstraferight`

`variable` `extern` | [progs/doomgeneric/m_controls.h:132](../../progs/doomgeneric/m_controls.h#L132)

```c
extern int mousebstraferight;
```

---

<a id="mousebbackward"></a>

### `mousebbackward`

`variable` `extern` | [progs/doomgeneric/m_controls.h:133](../../progs/doomgeneric/m_controls.h#L133)

```c
extern int mousebbackward;
```

---

<a id="mousebuse"></a>

### `mousebuse`

`variable` `extern` | [progs/doomgeneric/m_controls.h:134](../../progs/doomgeneric/m_controls.h#L134)

```c
extern int mousebuse;
```

---

<a id="mousebprevweapon"></a>

### `mousebprevweapon`

`variable` `extern` | [progs/doomgeneric/m_controls.h:136](../../progs/doomgeneric/m_controls.h#L136)

```c
extern int mousebprevweapon;
```

---

<a id="mousebnextweapon"></a>

### `mousebnextweapon`

`variable` `extern` | [progs/doomgeneric/m_controls.h:137](../../progs/doomgeneric/m_controls.h#L137)

```c
extern int mousebnextweapon;
```

---

<a id="joybfire"></a>

### `joybfire`

`variable` `extern` | [progs/doomgeneric/m_controls.h:139](../../progs/doomgeneric/m_controls.h#L139)

```c
extern int joybfire;
```

---

<a id="joybstrafe"></a>

### `joybstrafe`

`variable` `extern` | [progs/doomgeneric/m_controls.h:140](../../progs/doomgeneric/m_controls.h#L140)

```c
extern int joybstrafe;
```

---

<a id="joybuse"></a>

### `joybuse`

`variable` `extern` | [progs/doomgeneric/m_controls.h:141](../../progs/doomgeneric/m_controls.h#L141)

```c
extern int joybuse;
```

---

<a id="joybspeed"></a>

### `joybspeed`

`variable` `extern` | [progs/doomgeneric/m_controls.h:142](../../progs/doomgeneric/m_controls.h#L142)

```c
extern int joybspeed;
```

---

<a id="joybjump"></a>

### `joybjump`

`variable` `extern` | [progs/doomgeneric/m_controls.h:144](../../progs/doomgeneric/m_controls.h#L144)

```c
extern int joybjump;
```

---

<a id="joybstrafeleft"></a>

### `joybstrafeleft`

`variable` `extern` | [progs/doomgeneric/m_controls.h:146](../../progs/doomgeneric/m_controls.h#L146)

```c
extern int joybstrafeleft;
```

---

<a id="joybstraferight"></a>

### `joybstraferight`

`variable` `extern` | [progs/doomgeneric/m_controls.h:147](../../progs/doomgeneric/m_controls.h#L147)

```c
extern int joybstraferight;
```

---

<a id="joybprevweapon"></a>

### `joybprevweapon`

`variable` `extern` | [progs/doomgeneric/m_controls.h:149](../../progs/doomgeneric/m_controls.h#L149)

```c
extern int joybprevweapon;
```

---

<a id="joybnextweapon"></a>

### `joybnextweapon`

`variable` `extern` | [progs/doomgeneric/m_controls.h:150](../../progs/doomgeneric/m_controls.h#L150)

```c
extern int joybnextweapon;
```

---

<a id="joybmenu"></a>

### `joybmenu`

`variable` `extern` | [progs/doomgeneric/m_controls.h:152](../../progs/doomgeneric/m_controls.h#L152)

```c
extern int joybmenu;
```

---

<a id="dclick_use"></a>

### `dclick_use`

`variable` `extern` | [progs/doomgeneric/m_controls.h:154](../../progs/doomgeneric/m_controls.h#L154)

```c
extern int dclick_use;
```

---
