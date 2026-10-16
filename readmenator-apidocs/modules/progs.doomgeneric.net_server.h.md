# `progs/doomgeneric/net_server.h`

> Source: [progs/doomgeneric/net_server.h:1](../../progs/doomgeneric/net_server.h#L1) | language `h` | coverage 16.7% | [API index](../index.md)

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  Network server code    initialize server and wait for connections

## Contents

- **Functions:** [`NET_SV_Init`](#net_sv_init), [`NET_SV_Run`](#net_sv_run), [`NET_SV_Shutdown`](#net_sv_shutdown), [`NET_SV_AddModule`](#net_sv_addmodule), [`NET_SV_RegisterWithMaster`](#net_sv_registerwithmaster)

## Functions

<a id="net_sv_init"></a>

### `NET_SV_Init`

`function` | [progs/doomgeneric/net_server.h:22](../../progs/doomgeneric/net_server.h#L22)

```c
void NET_SV_Init(void);
```

*Called by:* [`D_InitNetGame`](progs.doomgeneric.d_loop.c.md#d_initnetgame)

---

<a id="net_sv_run"></a>

### `NET_SV_Run`

`function` | [progs/doomgeneric/net_server.h:26](../../progs/doomgeneric/net_server.h#L26)

```c
void NET_SV_Run(void);
```

*Called by:* [`NetUpdate`](progs.doomgeneric.d_loop.c.md#netupdate)

---

<a id="net_sv_shutdown"></a>

### `NET_SV_Shutdown`

`function` | [progs/doomgeneric/net_server.h:31](../../progs/doomgeneric/net_server.h#L31)

```c
void NET_SV_Shutdown(void);
```

*Called by:* [`D_QuitNetGame`](progs.doomgeneric.d_loop.c.md#d_quitnetgame)

---

<a id="net_sv_addmodule"></a>

### `NET_SV_AddModule`

`function` | [progs/doomgeneric/net_server.h:35](../../progs/doomgeneric/net_server.h#L35)

```c
void NET_SV_AddModule(net_module_t *module);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `module` | `net_module_t *` |  |  |

*Called by:* [`D_InitNetGame`](progs.doomgeneric.d_loop.c.md#d_initnetgame)

---

<a id="net_sv_registerwithmaster"></a>

### `NET_SV_RegisterWithMaster`

`function` | [progs/doomgeneric/net_server.h:39](../../progs/doomgeneric/net_server.h#L39)

```c
void NET_SV_RegisterWithMaster(void);
```

*Called by:* [`D_InitNetGame`](progs.doomgeneric.d_loop.c.md#d_initnetgame)

---
