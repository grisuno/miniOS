# `progs/lua/minios.c`

> Source: [progs/lua/minios.c:1](../../progs/lua/minios.c#L1) | language `c` | coverage 10.0% | [API index](../index.md)

## Contents

- **Functions:** [`luaopen_minios`](#luaopen_minios)
- **Macros:** [`SYS_TIME_MS`](#sys_time_ms), [`SYS_PALETTE`](#sys_palette), [`SYS_PCSPK_INIT`](#sys_pcspk_init), [`SYS_PCSPK_TONE`](#sys_pcspk_tone), [`SYS_RTC`](#sys_rtc), [`SYS_FB_INFO`](#sys_fb_info), [`SYS_PCSPK_VOL`](#sys_pcspk_vol), [`SYS_SPAWN`](#sys_spawn)

## Functions

<a id="luaopen_minios"></a>

### `luaopen_minios`

`function` | [progs/lua/minios.c:192](../../progs/lua/minios.c#L192)

```c
int luaopen_minios(lua_State *L)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `L` | `lua_State *` |  |  |

**Returns:** `int`

---

## Macros

<a id="sys_time_ms"></a>

### `SYS_TIME_MS`

`macro` | [progs/lua/minios.c:52](../../progs/lua/minios.c#L52)

```c
#define SYS_TIME_MS
```

--- Compatibility aliases for runtime bindings ---

> **Inherited:** Documentation from [`SYS_TIME_MS`](#sys_time_ms) (progs/minios_abi.h:424).

---

<a id="sys_palette"></a>

### `SYS_PALETTE`

`macro` | [progs/lua/minios.c:53](../../progs/lua/minios.c#L53)

```c
#define SYS_PALETTE
```

---

<a id="sys_pcspk_init"></a>

### `SYS_PCSPK_INIT`

`macro` | [progs/lua/minios.c:54](../../progs/lua/minios.c#L54)

```c
#define SYS_PCSPK_INIT
```

---

<a id="sys_pcspk_tone"></a>

### `SYS_PCSPK_TONE`

`macro` | [progs/lua/minios.c:55](../../progs/lua/minios.c#L55)

```c
#define SYS_PCSPK_TONE
```

---

<a id="sys_rtc"></a>

### `SYS_RTC`

`macro` | [progs/lua/minios.c:56](../../progs/lua/minios.c#L56)

```c
#define SYS_RTC
```

---

<a id="sys_fb_info"></a>

### `SYS_FB_INFO`

`macro` | [progs/lua/minios.c:57](../../progs/lua/minios.c#L57)

```c
#define SYS_FB_INFO
```

---

<a id="sys_pcspk_vol"></a>

### `SYS_PCSPK_VOL`

`macro` | [progs/lua/minios.c:58](../../progs/lua/minios.c#L58)

```c
#define SYS_PCSPK_VOL
```

---

<a id="sys_spawn"></a>

### `SYS_SPAWN`

`macro` | [progs/lua/minios.c:59](../../progs/lua/minios.c#L59)

```c
#define SYS_SPAWN
```

---
