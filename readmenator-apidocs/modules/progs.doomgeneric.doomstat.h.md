# `progs/doomgeneric/doomstat.h`

> Source: [progs/doomgeneric/doomstat.h:1](../../progs/doomgeneric/doomstat.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: All the global variables that store the internal state. Theoretically speaking, the internal state of the engine should be found by looking at the variables collected here, and every relevant module will have to include this header file. In practice, things are a bit messy.     We need globally shared data structures, for defining the global state variables.

## Contents

- **Macros:** [`__D_STATE__`](#__d_state__), [`logical_gamemission`](#logical_gamemission), [`MAX_DM_STARTS`](#max_dm_starts)
- **Variables:** [`nomonsters`](#nomonsters), [`respawnparm`](#respawnparm), [`fastparm`](#fastparm), [`devparm`](#devparm), [`gamemode`](#gamemode), [`gamemission`](#gamemission), [`gameversion`](#gameversion), [`gamedescription`](#gamedescription), [`bfgedition`](#bfgedition), [`modifiedgame`](#modifiedgame), [`startskill`](#startskill), [`startepisode`](#startepisode), [`startmap`](#startmap), [`startloadgame`](#startloadgame), [`autostart`](#autostart), [`gameskill`](#gameskill), [`gameepisode`](#gameepisode), [`gamemap`](#gamemap), [`timelimit`](#timelimit), [`respawnmonsters`](#respawnmonsters), [`netgame`](#netgame), [`deathmatch`](#deathmatch), [`sfxVolume`](#sfxvolume), [`musicVolume`](#musicvolume), [`snd_MusicDevice`](#snd_musicdevice), [`snd_SfxDevice`](#snd_sfxdevice), [`snd_DesiredMusicDevice`](#snd_desiredmusicdevice), [`snd_DesiredSfxDevice`](#snd_desiredsfxdevice), [`statusbaractive`](#statusbaractive), [`automapactive`](#automapactive), [`menuactive`](#menuactive), [`paused`](#paused), [`viewactive`](#viewactive), [`nodrawers`](#nodrawers), [`testcontrols`](#testcontrols), [`testcontrols_mousespeed`](#testcontrols_mousespeed), [`viewangleoffset`](#viewangleoffset), [`consoleplayer`](#consoleplayer), [`displayplayer`](#displayplayer), [`totalkills`](#totalkills), [`totalitems`](#totalitems), [`totalsecret`](#totalsecret), [`levelstarttic`](#levelstarttic), [`leveltime`](#leveltime), [`usergame`](#usergame), [`demoplayback`](#demoplayback), [`demorecording`](#demorecording), [`lowres_turn`](#lowres_turn), [`singledemo`](#singledemo), [`gamestate`](#gamestate), [`players`](#players), [`playeringame`](#playeringame), [`deathmatchstarts`](#deathmatchstarts), [`deathmatch_p`](#deathmatch_p), [`playerstarts`](#playerstarts), [`wminfo`](#wminfo), [`savegamedir`](#savegamedir), [`basedefault`](#basedefault), [`precache`](#precache), [`wipegamestate`](#wipegamestate), [`mouseSensitivity`](#mousesensitivity), [`bodyqueslot`](#bodyqueslot), [`skyflatnum`](#skyflatnum), [`rndindex`](#rndindex), [`netcmds`](#netcmds)

## Macros

<a id="__d_state__"></a>

### `__D_STATE__`

`macro` | [progs/doomgeneric/doomstat.h:26](../../progs/doomgeneric/doomstat.h#L26)

```c
#define __D_STATE__
```

---

<a id="logical_gamemission"></a>

### `logical_gamemission`

`macro` | [progs/doomgeneric/doomstat.h:69](../../progs/doomgeneric/doomstat.h#L69)

```c
#define logical_gamemission
```

---

<a id="max_dm_starts"></a>

### `MAX_DM_STARTS`

`macro` | [progs/doomgeneric/doomstat.h:227](../../progs/doomgeneric/doomstat.h#L227)

```c
#define MAX_DM_STARTS
```

Player spawn spots for deathmatch.

---

## Variables

<a id="nomonsters"></a>

### `nomonsters`

`variable` `extern` | [progs/doomgeneric/doomstat.h:46](../../progs/doomgeneric/doomstat.h#L46)

```c
extern boolean nomonsters;
```

Command line parameters.

---

<a id="respawnparm"></a>

### `respawnparm`

`variable` `extern` | [progs/doomgeneric/doomstat.h:47](../../progs/doomgeneric/doomstat.h#L47)

```c
extern boolean respawnparm;
```

---

<a id="fastparm"></a>

### `fastparm`

`variable` `extern` | [progs/doomgeneric/doomstat.h:48](../../progs/doomgeneric/doomstat.h#L48)

```c
extern boolean fastparm;
```

---

<a id="devparm"></a>

### `devparm`

`variable` `extern` | [progs/doomgeneric/doomstat.h:50](../../progs/doomgeneric/doomstat.h#L50)

```c
extern boolean devparm;
```

---

<a id="gamemode"></a>

### `gamemode`

`variable` `extern` | [progs/doomgeneric/doomstat.h:56](../../progs/doomgeneric/doomstat.h#L56)

```c
extern GameMode_t gamemode;
```

Game Mode - identify IWAD as shareware, retail etc.

---

<a id="gamemission"></a>

### `gamemission`

`variable` `extern` | [progs/doomgeneric/doomstat.h:57](../../progs/doomgeneric/doomstat.h#L57)

```c
extern GameMission_t gamemission;
```

---

<a id="gameversion"></a>

### `gameversion`

`variable` `extern` | [progs/doomgeneric/doomstat.h:58](../../progs/doomgeneric/doomstat.h#L58)

```c
extern GameVersion_t gameversion;
```

---

<a id="gamedescription"></a>

### `gamedescription`

`variable` `extern` | [progs/doomgeneric/doomstat.h:59](../../progs/doomgeneric/doomstat.h#L59)

```c
extern char *gamedescription;
```

---

<a id="bfgedition"></a>

### `bfgedition`

`variable` `extern` | [progs/doomgeneric/doomstat.h:62](../../progs/doomgeneric/doomstat.h#L62)

```c
extern boolean bfgedition;
```

If true, we're using one of the mangled BFG edition IWADs.

---

<a id="modifiedgame"></a>

### `modifiedgame`

`variable` `extern` | [progs/doomgeneric/doomstat.h:74](../../progs/doomgeneric/doomstat.h#L74)

```c
extern boolean modifiedgame;
```

Set if homebrew PWAD stuff has been added.

---

<a id="startskill"></a>

### `startskill`

`variable` `extern` | [progs/doomgeneric/doomstat.h:82](../../progs/doomgeneric/doomstat.h#L82)

```c
extern skill_t startskill;
```

Defaults for menu, methinks.

---

<a id="startepisode"></a>

### `startepisode`

`variable` `extern` | [progs/doomgeneric/doomstat.h:83](../../progs/doomgeneric/doomstat.h#L83)

```c
extern int startepisode;
```

---

<a id="startmap"></a>

### `startmap`

`variable` `extern` | [progs/doomgeneric/doomstat.h:84](../../progs/doomgeneric/doomstat.h#L84)

```c
extern int startmap;
```

---

<a id="startloadgame"></a>

### `startloadgame`

`variable` `extern` | [progs/doomgeneric/doomstat.h:89](../../progs/doomgeneric/doomstat.h#L89)

```c
extern int startloadgame;
```

---

<a id="autostart"></a>

### `autostart`

`variable` `extern` | [progs/doomgeneric/doomstat.h:91](../../progs/doomgeneric/doomstat.h#L91)

```c
extern boolean autostart;
```

---

<a id="gameskill"></a>

### `gameskill`

`variable` `extern` | [progs/doomgeneric/doomstat.h:94](../../progs/doomgeneric/doomstat.h#L94)

```c
extern skill_t gameskill;
```

Selected by user.

---

<a id="gameepisode"></a>

### `gameepisode`

`variable` `extern` | [progs/doomgeneric/doomstat.h:95](../../progs/doomgeneric/doomstat.h#L95)

```c
extern int gameepisode;
```

---

<a id="gamemap"></a>

### `gamemap`

`variable` `extern` | [progs/doomgeneric/doomstat.h:96](../../progs/doomgeneric/doomstat.h#L96)

```c
extern int gamemap;
```

---

<a id="timelimit"></a>

### `timelimit`

`variable` `extern` | [progs/doomgeneric/doomstat.h:99](../../progs/doomgeneric/doomstat.h#L99)

```c
extern int timelimit;
```

If non-zero, exit the level after this number of minutes

---

<a id="respawnmonsters"></a>

### `respawnmonsters`

`variable` `extern` | [progs/doomgeneric/doomstat.h:102](../../progs/doomgeneric/doomstat.h#L102)

```c
extern boolean respawnmonsters;
```

Nightmare mode flag, single player.

---

<a id="netgame"></a>

### `netgame`

`variable` `extern` | [progs/doomgeneric/doomstat.h:105](../../progs/doomgeneric/doomstat.h#L105)

```c
extern boolean netgame;
```

Netgame?

Only true if >1 player.

---

<a id="deathmatch"></a>

### `deathmatch`

`variable` `extern` | [progs/doomgeneric/doomstat.h:108](../../progs/doomgeneric/doomstat.h#L108)

```c
extern int deathmatch;
```

0=Cooperative; 1=Deathmatch; 2=Altdeath

---

<a id="sfxvolume"></a>

### `sfxVolume`

`variable` `extern` | [progs/doomgeneric/doomstat.h:120](../../progs/doomgeneric/doomstat.h#L120)

```c
extern int sfxVolume;
```

From m_menu.c: Sound FX volume has default, 0 - 15 Music volume has default, 0 - 15 These are multiplied by 8.

---

<a id="musicvolume"></a>

### `musicVolume`

`variable` `extern` | [progs/doomgeneric/doomstat.h:121](../../progs/doomgeneric/doomstat.h#L121)

```c
extern int musicVolume;
```

---

<a id="snd_musicdevice"></a>

### `snd_MusicDevice`

`variable` `extern` | [progs/doomgeneric/doomstat.h:127](../../progs/doomgeneric/doomstat.h#L127)

```c
extern int snd_MusicDevice;
```

Current music/sfx card - index useless w/o a reference LUT in a sound module.

Ideally, this would use indices found in: /usr/include/linux/soundcard.h

---

<a id="snd_sfxdevice"></a>

### `snd_SfxDevice`

`variable` `extern` | [progs/doomgeneric/doomstat.h:128](../../progs/doomgeneric/doomstat.h#L128)

```c
extern int snd_SfxDevice;
```

---

<a id="snd_desiredmusicdevice"></a>

### `snd_DesiredMusicDevice`

`variable` `extern` | [progs/doomgeneric/doomstat.h:130](../../progs/doomgeneric/doomstat.h#L130)

```c
extern int snd_DesiredMusicDevice;
```

Config file?

Same disclaimer as above.

---

<a id="snd_desiredsfxdevice"></a>

### `snd_DesiredSfxDevice`

`variable` `extern` | [progs/doomgeneric/doomstat.h:131](../../progs/doomgeneric/doomstat.h#L131)

```c
extern int snd_DesiredSfxDevice;
```

---

<a id="statusbaractive"></a>

### `statusbaractive`

`variable` `extern` | [progs/doomgeneric/doomstat.h:141](../../progs/doomgeneric/doomstat.h#L141)

```c
extern boolean statusbaractive;
```

Depending on view size - no status bar?

Note that there is no way to disable the status bar explicitely.

---

<a id="automapactive"></a>

### `automapactive`

`variable` `extern` | [progs/doomgeneric/doomstat.h:143](../../progs/doomgeneric/doomstat.h#L143)

```c
extern boolean automapactive;
```

---

<a id="menuactive"></a>

### `menuactive`

`variable` `extern` | [progs/doomgeneric/doomstat.h:144](../../progs/doomgeneric/doomstat.h#L144)

```c
extern boolean menuactive;
```

---

<a id="paused"></a>

### `paused`

`variable` `extern` | [progs/doomgeneric/doomstat.h:145](../../progs/doomgeneric/doomstat.h#L145)

```c
extern boolean paused;
```

---

<a id="viewactive"></a>

### `viewactive`

`variable` `extern` | [progs/doomgeneric/doomstat.h:148](../../progs/doomgeneric/doomstat.h#L148)

```c
extern boolean viewactive;
```

---

<a id="nodrawers"></a>

### `nodrawers`

`variable` `extern` | [progs/doomgeneric/doomstat.h:150](../../progs/doomgeneric/doomstat.h#L150)

```c
extern boolean nodrawers;
```

---

<a id="testcontrols"></a>

### `testcontrols`

`variable` `extern` | [progs/doomgeneric/doomstat.h:153](../../progs/doomgeneric/doomstat.h#L153)

```c
extern boolean testcontrols;
```

---

<a id="testcontrols_mousespeed"></a>

### `testcontrols_mousespeed`

`variable` `extern` | [progs/doomgeneric/doomstat.h:154](../../progs/doomgeneric/doomstat.h#L154)

```c
extern int testcontrols_mousespeed;
```

---

<a id="viewangleoffset"></a>

### `viewangleoffset`

`variable` `extern` | [progs/doomgeneric/doomstat.h:161](../../progs/doomgeneric/doomstat.h#L161)

```c
extern int viewangleoffset;
```

This one is related to the 3-screen display mode.

ANG90 = left side, ANG270 = right

---

<a id="consoleplayer"></a>

### `consoleplayer`

`variable` `extern` | [progs/doomgeneric/doomstat.h:164](../../progs/doomgeneric/doomstat.h#L164)

```c
extern int consoleplayer;
```

Player taking events, and displaying.

---

<a id="displayplayer"></a>

### `displayplayer`

`variable` `extern` | [progs/doomgeneric/doomstat.h:165](../../progs/doomgeneric/doomstat.h#L165)

```c
extern int displayplayer;
```

---

<a id="totalkills"></a>

### `totalkills`

`variable` `extern` | [progs/doomgeneric/doomstat.h:172](../../progs/doomgeneric/doomstat.h#L172)

```c
extern int totalkills;
```

Scores, rating.

Statistics on a given map, for intermission.

---

<a id="totalitems"></a>

### `totalitems`

`variable` `extern` | [progs/doomgeneric/doomstat.h:173](../../progs/doomgeneric/doomstat.h#L173)

```c
extern int totalitems;
```

---

<a id="totalsecret"></a>

### `totalsecret`

`variable` `extern` | [progs/doomgeneric/doomstat.h:174](../../progs/doomgeneric/doomstat.h#L174)

```c
extern int totalsecret;
```

---

<a id="levelstarttic"></a>

### `levelstarttic`

`variable` `extern` | [progs/doomgeneric/doomstat.h:177](../../progs/doomgeneric/doomstat.h#L177)

```c
extern int levelstarttic;
```

Timer, for scores.

---

<a id="leveltime"></a>

### `leveltime`

`variable` `extern` | [progs/doomgeneric/doomstat.h:178](../../progs/doomgeneric/doomstat.h#L178)

```c
extern int leveltime;
```

---

<a id="usergame"></a>

### `usergame`

`variable` `extern` | [progs/doomgeneric/doomstat.h:186](../../progs/doomgeneric/doomstat.h#L186)

```c
extern boolean usergame;
```

DEMO playback/recording related stuff.

No demo, there is a human player in charge? Disable save/end game?

---

<a id="demoplayback"></a>

### `demoplayback`

`variable` `extern` | [progs/doomgeneric/doomstat.h:189](../../progs/doomgeneric/doomstat.h#L189)

```c
extern boolean demoplayback;
```

?

---

<a id="demorecording"></a>

### `demorecording`

`variable` `extern` | [progs/doomgeneric/doomstat.h:190](../../progs/doomgeneric/doomstat.h#L190)

```c
extern boolean demorecording;
```

---

<a id="lowres_turn"></a>

### `lowres_turn`

`variable` `extern` | [progs/doomgeneric/doomstat.h:195](../../progs/doomgeneric/doomstat.h#L195)

```c
extern boolean lowres_turn;
```

---

<a id="singledemo"></a>

### `singledemo`

`variable` `extern` | [progs/doomgeneric/doomstat.h:198](../../progs/doomgeneric/doomstat.h#L198)

```c
extern boolean singledemo;
```

Quit after playing a demo from cmdline.

---

<a id="gamestate"></a>

### `gamestate`

`variable` `extern` | [progs/doomgeneric/doomstat.h:204](../../progs/doomgeneric/doomstat.h#L204)

```c
extern gamestate_t gamestate;
```

?

---

<a id="players"></a>

### `players`

`variable` `extern` | [progs/doomgeneric/doomstat.h:220](../../progs/doomgeneric/doomstat.h#L220)

```c
extern player_t players[MAXPLAYERS];
```

Bookkeeping on players - state.

---

<a id="playeringame"></a>

### `playeringame`

`variable` `extern` | [progs/doomgeneric/doomstat.h:223](../../progs/doomgeneric/doomstat.h#L223)

```c
extern boolean playeringame[MAXPLAYERS];
```

Alive?

Disconnected?

---

<a id="deathmatchstarts"></a>

### `deathmatchstarts`

`variable` `extern` | [progs/doomgeneric/doomstat.h:228](../../progs/doomgeneric/doomstat.h#L228)

```c
extern mapthing_t deathmatchstarts[MAX_DM_STARTS];
```

Player spawn spots for deathmatch. define MAX_DM_STARTS   10

---

<a id="deathmatch_p"></a>

### `deathmatch_p`

`variable` `extern` | [progs/doomgeneric/doomstat.h:229](../../progs/doomgeneric/doomstat.h#L229)

```c
extern mapthing_t* deathmatch_p;
```

---

<a id="playerstarts"></a>

### `playerstarts`

`variable` `extern` | [progs/doomgeneric/doomstat.h:232](../../progs/doomgeneric/doomstat.h#L232)

```c
extern mapthing_t playerstarts[MAXPLAYERS];
```

Player spawn spots.

---

<a id="wminfo"></a>

### `wminfo`

`variable` `extern` | [progs/doomgeneric/doomstat.h:236](../../progs/doomgeneric/doomstat.h#L236)

```c
extern wbstartstruct_t wminfo;
```

Intermission stats.

Parameters for world map / intermission.

---

<a id="savegamedir"></a>

### `savegamedir`

`variable` `extern` | [progs/doomgeneric/doomstat.h:249](../../progs/doomgeneric/doomstat.h#L249)

```c
extern char * savegamedir;
```

File handling stuff.

---

<a id="basedefault"></a>

### `basedefault`

`variable` `extern` | [progs/doomgeneric/doomstat.h:250](../../progs/doomgeneric/doomstat.h#L250)

```c
extern char basedefault[1024];
```

---

<a id="precache"></a>

### `precache`

`variable` `extern` | [progs/doomgeneric/doomstat.h:253](../../progs/doomgeneric/doomstat.h#L253)

```c
extern boolean precache;
```

if true, load all graphics at level load

---

<a id="wipegamestate"></a>

### `wipegamestate`

`variable` `extern` | [progs/doomgeneric/doomstat.h:258](../../progs/doomgeneric/doomstat.h#L258)

```c
extern gamestate_t wipegamestate;
```

wipegamestate can be set to -1 to force a wipe on the next draw

---

<a id="mousesensitivity"></a>

### `mouseSensitivity`

`variable` `extern` | [progs/doomgeneric/doomstat.h:260](../../progs/doomgeneric/doomstat.h#L260)

```c
extern int mouseSensitivity;
```

---

<a id="bodyqueslot"></a>

### `bodyqueslot`

`variable` `extern` | [progs/doomgeneric/doomstat.h:262](../../progs/doomgeneric/doomstat.h#L262)

```c
extern int bodyqueslot;
```

---

<a id="skyflatnum"></a>

### `skyflatnum`

`variable` `extern` | [progs/doomgeneric/doomstat.h:269](../../progs/doomgeneric/doomstat.h#L269)

```c
extern int skyflatnum;
```

Needed to store the number of the dummy sky flat.

Used for rendering, as well as tracking projectiles etc.

---

<a id="rndindex"></a>

### `rndindex`

`variable` `extern` | [progs/doomgeneric/doomstat.h:276](../../progs/doomgeneric/doomstat.h#L276)

```c
extern int rndindex;
```

---

<a id="netcmds"></a>

### `netcmds`

`variable` `extern` | [progs/doomgeneric/doomstat.h:278](../../progs/doomgeneric/doomstat.h#L278)

```c
extern ticcmd_t *netcmds;
```

---
