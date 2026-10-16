# `headers/kernel/vga_cursor.h`

> Source: [headers/kernel/vga_cursor.h:1](../../headers/kernel/vga_cursor.h#L1) | language `h` | coverage 100.0% | [API index](../index.md)

Docstring: vga_cursor.h -- boundary of the pointer sprite layer

## Contents

- **Functions:** [`cursor_over`](#cursor_over), [`cursor_place`](#cursor_place), [`cursor_move`](#cursor_move), [`cursor_erase`](#cursor_erase), [`cursor_invalidate`](#cursor_invalidate), [`cursor_note_repaint`](#cursor_note_repaint)
- **Macros:** [`CURSOR_W`](#cursor_w)

## Functions

<a id="cursor_over"></a>

### `cursor_over`

`function` | [headers/kernel/vga_cursor.h:16](../../headers/kernel/vga_cursor.h#L16)

```c
int cursor_over(int x0, int y0, int w, int h);
```

Docstring: True when the sprite overlaps the given screen rectangle.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x0` | `int` |  |  |
| `y0` | `int` |  |  |
| `w` | `int` |  |  |
| `h` | `int` |  |  |

**Returns:** `int`

---

<a id="cursor_place"></a>

### `cursor_place`

`function` | [headers/kernel/vga_cursor.h:19](../../headers/kernel/vga_cursor.h#L19)

```c
void cursor_place(int mx, int my);
```

Docstring: Paint the pointer at mx/my unconditionally.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `mx` | `int` |  |  |
| `my` | `int` |  |  |

---

<a id="cursor_move"></a>

### `cursor_move`

`function` | [headers/kernel/vga_cursor.h:22](../../headers/kernel/vga_cursor.h#L22)

```c
void cursor_move(int mx, int my);
```

Docstring: Desktop-tick update: repaint only when the position moved.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `mx` | `int` |  |  |
| `my` | `int` |  |  |

*Called by:* [`vga_fb_mouse_tick`](kernel.vga_fb.c.md#vga_fb_mouse_tick)

---

<a id="cursor_erase"></a>

### `cursor_erase`

`function` | [headers/kernel/vga_cursor.h:25](../../headers/kernel/vga_cursor.h#L25)

```c
void cursor_erase(void);
```

Docstring: Restore the saved background and mark the pointer hidden.

*Called by:* [`first`](kernel.vga_fb.c.md#first), [`vga_fb_draw_desktop`](kernel.vga_fb.c.md#vga_fb_draw_desktop), [`vga_fb_set_gfx_mode`](kernel.vga_fb.c.md#vga_fb_set_gfx_mode)

---

<a id="cursor_invalidate"></a>

### `cursor_invalidate`

`function` | [headers/kernel/vga_cursor.h:28](../../headers/kernel/vga_cursor.h#L28)

```c
void cursor_invalidate(void);
```

Docstring: Mark the pointer hidden without touching the framebuffer.

*Called by:* [`vga_fb_draw_desktop`](kernel.vga_fb.c.md#vga_fb_draw_desktop), [`vga_fb_init`](kernel.vga_fb.c.md#vga_fb_init), [`vga_fb_mouse_init`](kernel.vga_fb.c.md#vga_fb_mouse_init), [`vga_fb_mouse_tick`](kernel.vga_fb.c.md#vga_fb_mouse_tick), [`vga_fb_set_gfx_mode`](kernel.vga_fb.c.md#vga_fb_set_gfx_mode)

---

<a id="cursor_note_repaint"></a>

### `cursor_note_repaint`

`function` | [headers/kernel/vga_cursor.h:31](../../headers/kernel/vga_cursor.h#L31)

```c
void cursor_note_repaint(int x0, int y0, int w, int h);
```

Docstring: Invalidate when the pointer overlaps a repainted rectangle.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `x0` | `int` |  |  |
| `y0` | `int` |  |  |
| `w` | `int` |  |  |
| `h` | `int` |  |  |

---

## Macros

<a id="cursor_w"></a>

### `CURSOR_W`

`macro` | [headers/kernel/vga_cursor.h:12](../../headers/kernel/vga_cursor.h#L12)

```c
#define CURSOR_W
```

Docstring: Pointer sprite dimensions in pixels.

---
