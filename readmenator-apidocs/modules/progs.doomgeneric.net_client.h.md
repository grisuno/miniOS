# `progs/doomgeneric/net_client.h`

> Source: [progs/doomgeneric/net_client.h:1](../../progs/doomgeneric/net_client.h#L1) | language `h` | coverage 11.1% | [API index](../index.md)

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  Network client code

## Contents

- **Functions:** [`NET_CL_Disconnect`](#net_cl_disconnect), [`NET_CL_Run`](#net_cl_run), [`NET_CL_Init`](#net_cl_init), [`NET_CL_LaunchGame`](#net_cl_launchgame), [`NET_CL_StartGame`](#net_cl_startgame), [`NET_CL_SendTiccmd`](#net_cl_sendticcmd), [`NET_Init`](#net_init), [`NET_BindVariables`](#net_bindvariables)
- **Variables:** [`net_client_connected`](#net_client_connected), [`net_client_received_wait_data`](#net_client_received_wait_data), [`net_client_wait_data`](#net_client_wait_data), [`net_waiting_for_launch`](#net_waiting_for_launch), [`net_player_name`](#net_player_name), [`net_server_wad_sha1sum`](#net_server_wad_sha1sum), [`net_server_deh_sha1sum`](#net_server_deh_sha1sum), [`net_server_is_freedoom`](#net_server_is_freedoom), [`net_local_wad_sha1sum`](#net_local_wad_sha1sum), [`net_local_deh_sha1sum`](#net_local_deh_sha1sum), [`net_local_is_freedoom`](#net_local_is_freedoom), [`drone`](#drone)

## Functions

<a id="net_cl_disconnect"></a>

### `NET_CL_Disconnect`

`function` | [progs/doomgeneric/net_client.h:26](../../progs/doomgeneric/net_client.h#L26)

```c
void NET_CL_Disconnect(void);
```

*Called by:* [`D_QuitNetGame`](progs.doomgeneric.d_loop.c.md#d_quitnetgame)

---

<a id="net_cl_run"></a>

### `NET_CL_Run`

`function` | [progs/doomgeneric/net_client.h:27](../../progs/doomgeneric/net_client.h#L27)

```c
void NET_CL_Run(void);
```

*Called by:* [`NetUpdate`](progs.doomgeneric.d_loop.c.md#netupdate)

---

<a id="net_cl_init"></a>

### `NET_CL_Init`

`function` | [progs/doomgeneric/net_client.h:28](../../progs/doomgeneric/net_client.h#L28)

```c
void NET_CL_Init(void);
```

---

<a id="net_cl_launchgame"></a>

### `NET_CL_LaunchGame`

`function` | [progs/doomgeneric/net_client.h:29](../../progs/doomgeneric/net_client.h#L29)

```c
void NET_CL_LaunchGame(void);
```

---

<a id="net_cl_startgame"></a>

### `NET_CL_StartGame`

`function` | [progs/doomgeneric/net_client.h:30](../../progs/doomgeneric/net_client.h#L30)

```c
void NET_CL_StartGame(net_gamesettings_t *settings);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `settings` | `net_gamesettings_t *` |  |  |

*Called by:* [`D_StartNetGame`](progs.doomgeneric.d_loop.c.md#d_startnetgame)

---

<a id="net_cl_sendticcmd"></a>

### `NET_CL_SendTiccmd`

`function` | [progs/doomgeneric/net_client.h:31](../../progs/doomgeneric/net_client.h#L31)

```c
void NET_CL_SendTiccmd(ticcmd_t *ticcmd, int maketic);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ticcmd` | `ticcmd_t *` |  |  |
| `maketic` | `int` |  |  |

---

<a id="net_init"></a>

### `NET_Init`

`function` | [progs/doomgeneric/net_client.h:33](../../progs/doomgeneric/net_client.h#L33)

```c
void NET_Init(void);
```

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="net_bindvariables"></a>

### `NET_BindVariables`

`function` | [progs/doomgeneric/net_client.h:35](../../progs/doomgeneric/net_client.h#L35)

```c
void NET_BindVariables(void);
```

*Called by:* [`D_BindVariables`](progs.doomgeneric.d_main.c.md#d_bindvariables)

---

## Variables

<a id="net_client_connected"></a>

### `net_client_connected`

`variable` `extern` | [progs/doomgeneric/net_client.h:37](../../progs/doomgeneric/net_client.h#L37)

```c
extern boolean net_client_connected;
```

---

<a id="net_client_received_wait_data"></a>

### `net_client_received_wait_data`

`variable` `extern` | [progs/doomgeneric/net_client.h:38](../../progs/doomgeneric/net_client.h#L38)

```c
extern boolean net_client_received_wait_data;
```

---

<a id="net_client_wait_data"></a>

### `net_client_wait_data`

`variable` `extern` | [progs/doomgeneric/net_client.h:39](../../progs/doomgeneric/net_client.h#L39)

```c
extern net_waitdata_t net_client_wait_data;
```

---

<a id="net_waiting_for_launch"></a>

### `net_waiting_for_launch`

`variable` `extern` | [progs/doomgeneric/net_client.h:40](../../progs/doomgeneric/net_client.h#L40)

```c
extern boolean net_waiting_for_launch;
```

---

<a id="net_player_name"></a>

### `net_player_name`

`variable` `extern` | [progs/doomgeneric/net_client.h:41](../../progs/doomgeneric/net_client.h#L41)

```c
extern char *net_player_name;
```

---

<a id="net_server_wad_sha1sum"></a>

### `net_server_wad_sha1sum`

`variable` `extern` | [progs/doomgeneric/net_client.h:43](../../progs/doomgeneric/net_client.h#L43)

```c
extern sha1_digest_t net_server_wad_sha1sum;
```

---

<a id="net_server_deh_sha1sum"></a>

### `net_server_deh_sha1sum`

`variable` `extern` | [progs/doomgeneric/net_client.h:44](../../progs/doomgeneric/net_client.h#L44)

```c
extern sha1_digest_t net_server_deh_sha1sum;
```

---

<a id="net_server_is_freedoom"></a>

### `net_server_is_freedoom`

`variable` `extern` | [progs/doomgeneric/net_client.h:45](../../progs/doomgeneric/net_client.h#L45)

```c
extern unsigned int net_server_is_freedoom;
```

---

<a id="net_local_wad_sha1sum"></a>

### `net_local_wad_sha1sum`

`variable` `extern` | [progs/doomgeneric/net_client.h:46](../../progs/doomgeneric/net_client.h#L46)

```c
extern sha1_digest_t net_local_wad_sha1sum;
```

---

<a id="net_local_deh_sha1sum"></a>

### `net_local_deh_sha1sum`

`variable` `extern` | [progs/doomgeneric/net_client.h:47](../../progs/doomgeneric/net_client.h#L47)

```c
extern sha1_digest_t net_local_deh_sha1sum;
```

---

<a id="net_local_is_freedoom"></a>

### `net_local_is_freedoom`

`variable` `extern` | [progs/doomgeneric/net_client.h:48](../../progs/doomgeneric/net_client.h#L48)

```c
extern unsigned int net_local_is_freedoom;
```

---

<a id="drone"></a>

### `drone`

`variable` `extern` | [progs/doomgeneric/net_client.h:50](../../progs/doomgeneric/net_client.h#L50)

```c
extern boolean drone;
```

---
