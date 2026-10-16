# `progs/doomgeneric/d_loop.h`

> Source: [progs/doomgeneric/d_loop.h:1](../../progs/doomgeneric/d_loop.h#L1) | language `h` | coverage 66.7% | [API index](../index.md)

Copyright(C) 1993-1996 Id Software, Inc.

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Main loop stuff.     Callback function invoked while waiting for the netgame to start. The callback is invoked when new players are ready. The callback should return true, or return false to abort startup.

## Contents

- **Structs:** [`loop_interface_t`](#loop_interface_t)
- **Functions:** [`D_RegisterLoopCallbacks`](#d_registerloopcallbacks), [`NetUpdate`](#netupdate), [`D_QuitNetGame`](#d_quitnetgame), [`TryRunTics`](#tryruntics), [`D_StartGameLoop`](#d_startgameloop), [`D_StartNetGame`](#d_startnetgame)
- **Macros:** [`__D_LOOP__`](#__d_loop__)
- **Variables:** [`singletics`](#singletics), [`ticdup`](#ticdup)

## Structs

<a id="loop_interface_t"></a>

### `loop_interface_t`

`struct` | [progs/doomgeneric/d_loop.h:31](../../progs/doomgeneric/d_loop.h#L31)

```c
typedef struct
```

---

## Functions

<a id="d_registerloopcallbacks"></a>

### `D_RegisterLoopCallbacks`

`function` | [progs/doomgeneric/d_loop.h:52](../../progs/doomgeneric/d_loop.h#L52)

```c
void D_RegisterLoopCallbacks(loop_interface_t *i);
```

Register callback functions for the main loop code to use.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `i` | `loop_interface_t *` |  |  |

*Called by:* [`D_CheckNetGame`](progs.doomgeneric.d_net.c.md#d_checknetgame)

---

<a id="netupdate"></a>

### `NetUpdate`

`function` | [progs/doomgeneric/d_loop.h:55](../../progs/doomgeneric/d_loop.h#L55)

```c
void NetUpdate (void);
```

Create any new ticcmds and broadcast to other players.

*Called by:* [`R_RenderPlayerView`](progs.doomgeneric.r_main.c.md#r_renderplayerview)

---

<a id="d_quitnetgame"></a>

### `D_QuitNetGame`

`function` | [progs/doomgeneric/d_loop.h:59](../../progs/doomgeneric/d_loop.h#L59)

```c
void D_QuitNetGame (void);
```

Broadcasts special packets to other players to notify of game exit

---

<a id="tryruntics"></a>

### `TryRunTics`

`function` | [progs/doomgeneric/d_loop.h:62](../../progs/doomgeneric/d_loop.h#L62)

```c
void TryRunTics (void);
```

? how many ticks to run?

---

<a id="d_startgameloop"></a>

### `D_StartGameLoop`

`function` | [progs/doomgeneric/d_loop.h:65](../../progs/doomgeneric/d_loop.h#L65)

```c
void D_StartGameLoop(void);
```

Called at start of game loop to initialize timers

---

<a id="d_startnetgame"></a>

### `D_StartNetGame`

`function` | [progs/doomgeneric/d_loop.h:74](../../progs/doomgeneric/d_loop.h#L74)

```c
void D_StartNetGame(net_gamesettings_t *settings, netgame_startup_callback_t callback);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `settings` | `net_gamesettings_t *` |  |  |
| `callback` | `netgame_startup_callback_t` |  |  |

*Called by:* [`D_CheckNetGame`](progs.doomgeneric.d_net.c.md#d_checknetgame)

---

## Macros

<a id="__d_loop__"></a>

### `__D_LOOP__`

`macro` | [progs/doomgeneric/d_loop.h:20](../../progs/doomgeneric/d_loop.h#L20)

```c
#define __D_LOOP__
```

---

## Variables

<a id="singletics"></a>

### `singletics`

`variable` `extern` | [progs/doomgeneric/d_loop.h:77](../../progs/doomgeneric/d_loop.h#L77)

```c
extern boolean singletics;
```

---

<a id="ticdup"></a>

### `ticdup`

`variable` `extern` | [progs/doomgeneric/d_loop.h:78](../../progs/doomgeneric/d_loop.h#L78)

```c
extern int gametic, ticdup;
```

---
