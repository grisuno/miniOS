# `progs/doomgeneric/net_packet.h`

> Source: [progs/doomgeneric/net_packet.h:1](../../progs/doomgeneric/net_packet.h#L1) | language `h` | coverage 11.1% | [API index](../index.md)

Copyright(C) 2005-2014 Simon Howard  This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.  DESCRIPTION: Definitions for use in networking code.

## Contents

- **Functions:** [`NET_NewPacket`](#net_newpacket), [`NET_PacketDup`](#net_packetdup), [`NET_FreePacket`](#net_freepacket), [`NET_ReadString`](#net_readstring), [`NET_WriteInt8`](#net_writeint8), [`NET_WriteInt16`](#net_writeint16), [`NET_WriteInt32`](#net_writeint32), [`NET_WriteString`](#net_writestring)

## Functions

<a id="net_newpacket"></a>

### `NET_NewPacket`

`function` | [progs/doomgeneric/net_packet.h:23](../../progs/doomgeneric/net_packet.h#L23)

```c
net_packet_t *NET_NewPacket(int initial_size);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `initial_size` | `int` |  |  |

**Returns:** `net_packet_t *`

---

<a id="net_packetdup"></a>

### `NET_PacketDup`

`function` | [progs/doomgeneric/net_packet.h:24](../../progs/doomgeneric/net_packet.h#L24)

```c
net_packet_t *NET_PacketDup(net_packet_t *packet);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `packet` | `net_packet_t *` |  |  |

**Returns:** `net_packet_t *`

---

<a id="net_freepacket"></a>

### `NET_FreePacket`

`function` | [progs/doomgeneric/net_packet.h:25](../../progs/doomgeneric/net_packet.h#L25)

```c
void NET_FreePacket(net_packet_t *packet);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `packet` | `net_packet_t *` |  |  |

---

<a id="net_readstring"></a>

### `NET_ReadString`

`function` | [progs/doomgeneric/net_packet.h:35](../../progs/doomgeneric/net_packet.h#L35)

```c
char *NET_ReadString(net_packet_t *packet);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `packet` | `net_packet_t *` |  |  |

**Returns:** `char *`

---

<a id="net_writeint8"></a>

### `NET_WriteInt8`

`function` | [progs/doomgeneric/net_packet.h:37](../../progs/doomgeneric/net_packet.h#L37)

```c
void NET_WriteInt8(net_packet_t *packet, unsigned int i);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `packet` | `net_packet_t *` |  |  |
| `i` | `unsigned int` |  |  |

---

<a id="net_writeint16"></a>

### `NET_WriteInt16`

`function` | [progs/doomgeneric/net_packet.h:38](../../progs/doomgeneric/net_packet.h#L38)

```c
void NET_WriteInt16(net_packet_t *packet, unsigned int i);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `packet` | `net_packet_t *` |  |  |
| `i` | `unsigned int` |  |  |

---

<a id="net_writeint32"></a>

### `NET_WriteInt32`

`function` | [progs/doomgeneric/net_packet.h:39](../../progs/doomgeneric/net_packet.h#L39)

```c
void NET_WriteInt32(net_packet_t *packet, unsigned int i);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `packet` | `net_packet_t *` |  |  |
| `i` | `unsigned int` |  |  |

---

<a id="net_writestring"></a>

### `NET_WriteString`

`function` | [progs/doomgeneric/net_packet.h:41](../../progs/doomgeneric/net_packet.h#L41)

```c
void NET_WriteString(net_packet_t *packet, char *string);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `packet` | `net_packet_t *` |  |  |
| `string` | `char *` |  |  |

---
