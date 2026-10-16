# `progs/doomgeneric/doomgeneric_sdl.c`

> Source: [progs/doomgeneric/doomgeneric_sdl.c:1](../../progs/doomgeneric/doomgeneric_sdl.c#L1) | language `c` | coverage 12.5% | [API index](../index.md)

doomgeneric for soso os

## Contents

- **Functions:** [`DG_Init`](#dg_init), [`DG_DrawFrame`](#dg_drawframe), [`DG_SleepMs`](#dg_sleepms), [`DG_GetTicksMs`](#dg_getticksms), [`DG_GetKey`](#dg_getkey), [`DG_SetWindowTitle`](#dg_setwindowtitle)
- **Macros:** [`KEYQUEUE_SIZE`](#keyqueue_size)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_progs_doomgeneric_doomgeneric_sdl_c__DG_SleepMs(["DG_SleepMs"])
    n_progs_pokemon_minios_stubs_SDL_h__SDL_Delay["SDL.SDL_Delay"]
    n_progs_doomgeneric_doomgeneric_sdl_c__DG_GetTicksMs(["DG_GetTicksMs"])
    n_progs_pokemon_minios_stubs_SDL_h__SDL_GetTicks["SDL.SDL_GetTicks"]
    n_progs_doomgeneric_doomgeneric_sdl_c__DG_SleepMs -.-> n_progs_pokemon_minios_stubs_SDL_h__SDL_Delay
    n_progs_doomgeneric_doomgeneric_sdl_c__DG_GetTicksMs -.-> n_progs_pokemon_minios_stubs_SDL_h__SDL_GetTicks
```

## Functions

<a id="dg_init"></a>

### `DG_Init`

`function` | [progs/doomgeneric/doomgeneric_sdl.c:93](../../progs/doomgeneric/doomgeneric_sdl.c#L93)

```c
void DG_Init()
```

---

<a id="dg_drawframe"></a>

### `DG_DrawFrame`

`function` | [progs/doomgeneric/doomgeneric_sdl.c:112](../../progs/doomgeneric/doomgeneric_sdl.c#L112)

```c
void DG_DrawFrame()
```

---

<a id="dg_sleepms"></a>

### `DG_SleepMs`

`function` | [progs/doomgeneric/doomgeneric_sdl.c:123](../../progs/doomgeneric/doomgeneric_sdl.c#L123)

```c
void DG_SleepMs(uint32_t ms)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ms` | `uint32_t` |  |  |

*Calls:* [`SDL_Delay`](progs.pokemon.minios_stubs.SDL.h.md#sdl_delay)

---

<a id="dg_getticksms"></a>

### `DG_GetTicksMs`

`function` | [progs/doomgeneric/doomgeneric_sdl.c:128](../../progs/doomgeneric/doomgeneric_sdl.c#L128)

```c
uint32_t DG_GetTicksMs()
```

**Returns:** `uint32_t`

*Calls:* [`SDL_GetTicks`](progs.pokemon.minios_stubs.SDL.h.md#sdl_getticks)

---

<a id="dg_getkey"></a>

### `DG_GetKey`

`function` | [progs/doomgeneric/doomgeneric_sdl.c:133](../../progs/doomgeneric/doomgeneric_sdl.c#L133)

```c
int DG_GetKey(int* pressed, unsigned char* doomKey)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pressed` | `int*` |  |  |
| `doomKey` | `unsigned char*` |  |  |

**Returns:** `int`

---

<a id="dg_setwindowtitle"></a>

### `DG_SetWindowTitle`

`function` | [progs/doomgeneric/doomgeneric_sdl.c:152](../../progs/doomgeneric/doomgeneric_sdl.c#L152)

```c
void DG_SetWindowTitle(const char * title)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `title` | `char *` |  |  |

---

## Macros

<a id="keyqueue_size"></a>

### `KEYQUEUE_SIZE`

`macro` | [progs/doomgeneric/doomgeneric_sdl.c:17](../../progs/doomgeneric/doomgeneric_sdl.c#L17)

```c
#define KEYQUEUE_SIZE
```

---
