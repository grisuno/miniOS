# `progs/doomgeneric/net_io.h`

> Source: [progs/doomgeneric/net_io.h:1](../../progs/doomgeneric/net_io.h#L1) | language `h` | coverage 12.5% | [API index](../index.md)

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Network packet manipulation (net_packet_t)

## Contents

- **Functions:** [`NET_NewContext`](#net_newcontext), [`NET_AddModule`](#net_addmodule), [`NET_SendPacket`](#net_sendpacket), [`NET_SendBroadcast`](#net_sendbroadcast), [`NET_AddrToString`](#net_addrtostring), [`NET_FreeAddress`](#net_freeaddress), [`NET_ResolveAddress`](#net_resolveaddress)
- **Variables:** [`net_broadcast_addr`](#net_broadcast_addr)

## Functions

<a id="net_newcontext"></a>

### `NET_NewContext`

`function` | [progs/doomgeneric/net_io.h:25](../../progs/doomgeneric/net_io.h#L25)

```c
net_context_t *NET_NewContext(void);
```

**Returns:** `net_context_t *`

---

<a id="net_addmodule"></a>

### `NET_AddModule`

`function` | [progs/doomgeneric/net_io.h:26](../../progs/doomgeneric/net_io.h#L26)

```c
void NET_AddModule(net_context_t *context, net_module_t *module);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `context` | `net_context_t *` |  |  |
| `module` | `net_module_t *` |  |  |

---

<a id="net_sendpacket"></a>

### `NET_SendPacket`

`function` | [progs/doomgeneric/net_io.h:27](../../progs/doomgeneric/net_io.h#L27)

```c
void NET_SendPacket(net_addr_t *addr, net_packet_t *packet);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `addr` | `net_addr_t *` |  |  |
| `packet` | `net_packet_t *` |  |  |

---

<a id="net_sendbroadcast"></a>

### `NET_SendBroadcast`

`function` | [progs/doomgeneric/net_io.h:28](../../progs/doomgeneric/net_io.h#L28)

```c
void NET_SendBroadcast(net_context_t *context, net_packet_t *packet);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `context` | `net_context_t *` |  |  |
| `packet` | `net_packet_t *` |  |  |

---

<a id="net_addrtostring"></a>

### `NET_AddrToString`

`function` | [progs/doomgeneric/net_io.h:31](../../progs/doomgeneric/net_io.h#L31)

```c
char *NET_AddrToString(net_addr_t *addr);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `addr` | `net_addr_t *` |  |  |

**Returns:** `char *`

*Called by:* [`D_InitNetGame`](progs.doomgeneric.d_loop.c.md#d_initnetgame)

---

<a id="net_freeaddress"></a>

### `NET_FreeAddress`

`function` | [progs/doomgeneric/net_io.h:32](../../progs/doomgeneric/net_io.h#L32)

```c
void NET_FreeAddress(net_addr_t *addr);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `addr` | `net_addr_t *` |  |  |

---

<a id="net_resolveaddress"></a>

### `NET_ResolveAddress`

`function` | [progs/doomgeneric/net_io.h:33](../../progs/doomgeneric/net_io.h#L33)

```c
net_addr_t *NET_ResolveAddress(net_context_t *context, char *address);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `context` | `net_context_t *` |  |  |
| `address` | `char *` |  |  |

**Returns:** `net_addr_t *`

---

## Variables

<a id="net_broadcast_addr"></a>

### `net_broadcast_addr`

`variable` `extern` | [progs/doomgeneric/net_io.h:23](../../progs/doomgeneric/net_io.h#L23)

```c
extern net_addr_t net_broadcast_addr;
```

---
