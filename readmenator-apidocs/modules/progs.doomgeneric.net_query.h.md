# `progs/doomgeneric/net_query.h`

> Source: [progs/doomgeneric/net_query.h:1](../../progs/doomgeneric/net_query.h#L1) | language `h` | coverage 8.3% | [API index](../index.md)

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Querying servers to find their current status.

## Contents

- **Functions:** [`NET_StartLANQuery`](#net_startlanquery), [`NET_StartMasterQuery`](#net_startmasterquery), [`NET_LANQuery`](#net_lanquery), [`NET_MasterQuery`](#net_masterquery), [`NET_QueryAddress`](#net_queryaddress), [`NET_FindLANServer`](#net_findlanserver), [`NET_Query_Poll`](#net_query_poll), [`NET_Query_ResolveMaster`](#net_query_resolvemaster), [`NET_Query_AddToMaster`](#net_query_addtomaster), [`NET_Query_CheckAddedToMaster`](#net_query_checkaddedtomaster), [`NET_Query_MasterResponse`](#net_query_masterresponse)

## Functions

<a id="net_startlanquery"></a>

### `NET_StartLANQuery`

`function` `extern` | [progs/doomgeneric/net_query.h:28](../../progs/doomgeneric/net_query.h#L28)

```c
extern int NET_StartLANQuery(void);
```

**Returns:** `int`

---

<a id="net_startmasterquery"></a>

### `NET_StartMasterQuery`

`function` `extern` | [progs/doomgeneric/net_query.h:29](../../progs/doomgeneric/net_query.h#L29)

```c
extern int NET_StartMasterQuery(void);
```

**Returns:** `int`

---

<a id="net_lanquery"></a>

### `NET_LANQuery`

`function` `extern` | [progs/doomgeneric/net_query.h:31](../../progs/doomgeneric/net_query.h#L31)

```c
extern void NET_LANQuery(void);
```

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="net_masterquery"></a>

### `NET_MasterQuery`

`function` `extern` | [progs/doomgeneric/net_query.h:32](../../progs/doomgeneric/net_query.h#L32)

```c
extern void NET_MasterQuery(void);
```

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="net_queryaddress"></a>

### `NET_QueryAddress`

`function` `extern` | [progs/doomgeneric/net_query.h:33](../../progs/doomgeneric/net_query.h#L33)

```c
extern void NET_QueryAddress(char *addr);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `addr` | `char *` |  |  |

*Called by:* [`D_DoomMain`](progs.doomgeneric.d_main.c.md#d_doommain)

---

<a id="net_findlanserver"></a>

### `NET_FindLANServer`

`function` `extern` | [progs/doomgeneric/net_query.h:34](../../progs/doomgeneric/net_query.h#L34)

```c
extern net_addr_t *NET_FindLANServer(void);
```

**Returns:** `net_addr_t *`

*Called by:* [`D_InitNetGame`](progs.doomgeneric.d_loop.c.md#d_initnetgame)

---

<a id="net_query_poll"></a>

### `NET_Query_Poll`

`function` `extern` | [progs/doomgeneric/net_query.h:36](../../progs/doomgeneric/net_query.h#L36)

```c
extern int NET_Query_Poll(net_query_callback_t callback, void *user_data);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `callback` | `net_query_callback_t` |  |  |
| `user_data` | `void *` |  |  |

**Returns:** `int`

---

<a id="net_query_resolvemaster"></a>

### `NET_Query_ResolveMaster`

`function` `extern` | [progs/doomgeneric/net_query.h:38](../../progs/doomgeneric/net_query.h#L38)

```c
extern net_addr_t *NET_Query_ResolveMaster(net_context_t *context);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `context` | `net_context_t *` |  |  |

**Returns:** `net_addr_t *`

---

<a id="net_query_addtomaster"></a>

### `NET_Query_AddToMaster`

`function` `extern` | [progs/doomgeneric/net_query.h:39](../../progs/doomgeneric/net_query.h#L39)

```c
extern void NET_Query_AddToMaster(net_addr_t *master_addr);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `master_addr` | `net_addr_t *` |  |  |

---

<a id="net_query_checkaddedtomaster"></a>

### `NET_Query_CheckAddedToMaster`

`function` `extern` | [progs/doomgeneric/net_query.h:40](../../progs/doomgeneric/net_query.h#L40)

```c
extern boolean NET_Query_CheckAddedToMaster(boolean *result);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `result` | `boolean *` |  |  |

**Returns:** `boolean`

---

<a id="net_query_masterresponse"></a>

### `NET_Query_MasterResponse`

`function` `extern` | [progs/doomgeneric/net_query.h:41](../../progs/doomgeneric/net_query.h#L41)

```c
extern void NET_Query_MasterResponse(net_packet_t *packet);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `packet` | `net_packet_t *` |  |  |

---
