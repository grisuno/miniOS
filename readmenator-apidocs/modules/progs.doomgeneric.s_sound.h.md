# `progs/doomgeneric/s_sound.h`

> Source: [progs/doomgeneric/s_sound.h:1](../../progs/doomgeneric/s_sound.h#L1) | language `h` | coverage 46.7% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: The not so system specific sound interface.       Initializes sound stuff, including volume Sets channels, SFX and music volume, allocates channel buffer, sets S_sfx lookup.

## Contents

- **Functions:** [`S_Init`](#s_init), [`S_Shutdown`](#s_shutdown), [`S_Start`](#s_start), [`S_StartSound`](#s_startsound), [`S_StopSound`](#s_stopsound), [`S_StartMusic`](#s_startmusic), [`S_ChangeMusic`](#s_changemusic), [`S_StopMusic`](#s_stopmusic), [`S_PauseSound`](#s_pausesound), [`S_ResumeSound`](#s_resumesound), [`S_UpdateSounds`](#s_updatesounds), [`S_SetMusicVolume`](#s_setmusicvolume), [`S_SetSfxVolume`](#s_setsfxvolume)
- **Macros:** [`__S_SOUND__`](#__s_sound__)
- **Variables:** [`snd_channels`](#snd_channels)

## Functions

<a id="s_init"></a>

### `S_Init`

`function` | [progs/doomgeneric/s_sound.h:32](../../progs/doomgeneric/s_sound.h#L32)

```c
void S_Init(int sfxVolume, int musicVolume);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `sfxVolume` | `int` |  |  |
| `musicVolume` | `int` |  |  |

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="s_shutdown"></a>

### `S_Shutdown`

`function` | [progs/doomgeneric/s_sound.h:37](../../progs/doomgeneric/s_sound.h#L37)

```c
void S_Shutdown(void);
```

*Called by:* [`DG_DrawFrame`](progs.doomgeneric.doomgeneric_minios.c.md#dg_drawframe)

---

<a id="s_start"></a>

### `S_Start`

`function` | [progs/doomgeneric/s_sound.h:47](../../progs/doomgeneric/s_sound.h#L47)

```c
void S_Start(void);
```

*Called by:* [`P_SetupLevel`](progs.doomgeneric.p_setup.c.md#p_setuplevel)

---

<a id="s_startsound"></a>

### `S_StartSound`

`function` | [progs/doomgeneric/s_sound.h:54](../../progs/doomgeneric/s_sound.h#L54)

```c
void S_StartSound(void *origin, int sound_id);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `origin` | `void *` |  |  |
| `sound_id` | `int` |  |  |

*Called by:* [`F_BunnyScroll`](progs.doomgeneric.f_finale.c.md#f_bunnyscroll), [`F_CastResponder`](progs.doomgeneric.f_finale.c.md#f_castresponder), [`F_CastTicker`](progs.doomgeneric.f_finale.c.md#f_castticker), [`G_CheckSpot`](progs.doomgeneric.g_game.c.md#g_checkspot), [`HU_Ticker`](progs.doomgeneric.hu_stuff.c.md#hu_ticker), [`M_EndGame`](progs.doomgeneric.m_menu.c.md#m_endgame), [`M_QuickLoadResponse`](progs.doomgeneric.m_menu.c.md#m_quickloadresponse), [`M_QuickSave`](progs.doomgeneric.m_menu.c.md#m_quicksave), [`M_QuickSaveResponse`](progs.doomgeneric.m_menu.c.md#m_quicksaveresponse), [`M_QuitResponse`](progs.doomgeneric.m_menu.c.md#m_quitresponse), [`M_Responder`](progs.doomgeneric.m_menu.c.md#m_responder), [`T_MoveCeiling`](progs.doomgeneric.p_ceilng.c.md#t_moveceiling) and 62 more

---

<a id="s_stopsound"></a>

### `S_StopSound`

`function` | [progs/doomgeneric/s_sound.h:57](../../progs/doomgeneric/s_sound.h#L57)

```c
void S_StopSound(mobj_t *origin);
```

Stop sound for thing at <origin>

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `origin` | `mobj_t *` |  |  |

*Called by:* [`P_RemoveMobj`](progs.doomgeneric.p_mobj.c.md#p_removemobj)

---

<a id="s_startmusic"></a>

### `S_StartMusic`

`function` | [progs/doomgeneric/s_sound.h:61](../../progs/doomgeneric/s_sound.h#L61)

```c
void S_StartMusic(int music_id);
```

Start music using <music_id> from sounds.h

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `music_id` | `int` |  |  |

*Called by:* [`D_DoAdvanceDemo`](progs.doomgeneric.d_main.c.md#d_doadvancedemo), [`F_Ticker`](progs.doomgeneric.f_finale.c.md#f_ticker)

---

<a id="s_changemusic"></a>

### `S_ChangeMusic`

`function` | [progs/doomgeneric/s_sound.h:65](../../progs/doomgeneric/s_sound.h#L65)

```c
void S_ChangeMusic(int music_id, int looping);
```

Start music using <music_id> from sounds.h, and set whether looping

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `music_id` | `int` |  |  |
| `looping` | `int` |  |  |

*Called by:* [`F_StartCast`](progs.doomgeneric.f_finale.c.md#f_startcast), [`F_StartFinale`](progs.doomgeneric.f_finale.c.md#f_startfinale), [`ST_Responder`](progs.doomgeneric.st_stuff.c.md#st_responder), [`WI_Ticker`](progs.doomgeneric.wi_stuff.c.md#wi_ticker)

---

<a id="s_stopmusic"></a>

### `S_StopMusic`

`function` | [progs/doomgeneric/s_sound.h:71](../../progs/doomgeneric/s_sound.h#L71)

```c
void S_StopMusic(void);
```

Stops the music fer sure.

---

<a id="s_pausesound"></a>

### `S_PauseSound`

`function` | [progs/doomgeneric/s_sound.h:74](../../progs/doomgeneric/s_sound.h#L74)

```c
void S_PauseSound(void);
```

Stop and resume music, during game PAUSE.

*Called by:* [`G_Ticker`](progs.doomgeneric.g_game.c.md#g_ticker)

---

<a id="s_resumesound"></a>

### `S_ResumeSound`

`function` | [progs/doomgeneric/s_sound.h:75](../../progs/doomgeneric/s_sound.h#L75)

```c
void S_ResumeSound(void);
```

*Called by:* [`G_InitNew`](progs.doomgeneric.g_game.c.md#g_initnew), [`G_Ticker`](progs.doomgeneric.g_game.c.md#g_ticker)

---

<a id="s_updatesounds"></a>

### `S_UpdateSounds`

`function` | [progs/doomgeneric/s_sound.h:81](../../progs/doomgeneric/s_sound.h#L81)

```c
void S_UpdateSounds(mobj_t *listener);
```

Updates music & sounds

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `listener` | `mobj_t *` |  |  |

*Called by:* [`D_DoomLoop`](progs.doomgeneric.d_main.c.md#d_doomloop)

---

<a id="s_setmusicvolume"></a>

### `S_SetMusicVolume`

`function` | [progs/doomgeneric/s_sound.h:83](../../progs/doomgeneric/s_sound.h#L83)

```c
void S_SetMusicVolume(int volume);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `volume` | `int` |  |  |

*Called by:* [`M_MusicVol`](progs.doomgeneric.m_menu.c.md#m_musicvol)

---

<a id="s_setsfxvolume"></a>

### `S_SetSfxVolume`

`function` | [progs/doomgeneric/s_sound.h:84](../../progs/doomgeneric/s_sound.h#L84)

```c
void S_SetSfxVolume(int volume);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `volume` | `int` |  |  |

*Called by:* [`M_SfxVol`](progs.doomgeneric.m_menu.c.md#m_sfxvol)

---

## Macros

<a id="__s_sound__"></a>

### `__S_SOUND__`

`macro` | [progs/doomgeneric/s_sound.h:21](../../progs/doomgeneric/s_sound.h#L21)

```c
#define __S_SOUND__
```

---

## Variables

<a id="snd_channels"></a>

### `snd_channels`

`variable` `extern` | [progs/doomgeneric/s_sound.h:86](../../progs/doomgeneric/s_sound.h#L86)

```c
extern int snd_channels;
```

---
