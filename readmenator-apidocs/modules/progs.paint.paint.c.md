# `progs/paint/paint.c`

> Source: [progs/paint/paint.c:1](../../progs/paint/paint.c#L1) | language `c` | coverage 10.7% | [API index](../index.md)

Docstring: MiniOS paint program (Nuklear ring-3 app, MiniFS: paint/paint.elf).

## Contents

- **Functions:** [`main`](#main)
- **Macros:** [`STB_IMAGE_IMPLEMENTATION`](#stb_image_implementation), [`STBI_ONLY_PNG`](#stbi_only_png), [`STBI_NO_STDIO`](#stbi_no_stdio), [`PAINT_W`](#paint_w), [`PAINT_N`](#paint_n), [`PAINT_PATH_MAX`](#paint_path_max), [`PAINT_FILE_MAX`](#paint_file_max), [`PAINT_STATUS_MAX`](#paint_status_max), [`PAINT_UI_MEMORY`](#paint_ui_memory), [`PAINT_PNG_MAX`](#paint_png_max), [`PAINT_PNG_MAX_DIM`](#paint_png_max_dim), [`PAINT_TITLE`](#paint_title), [`PAINT_DEFAULT_PATH`](#paint_default_path), [`PAINT_PANEL_TITLE`](#paint_panel_title), [`PAINT_FILE_BTN_W`](#paint_file_btn_w), [`PAINT_FRAME_MS`](#paint_frame_ms), [`PAINT_FRAME_ATTEMPTS`](#paint_frame_attempts), [`PAINT_NCOLORS`](#paint_ncolors), [`PAINT_NSIZES`](#paint_nsizes), [`PAINT_NTOOLS`](#paint_ntools), [`PAINT_TOOL_BRUSH`](#paint_tool_brush), [`PAINT_TOOL_LINE`](#paint_tool_line), [`PAINT_TOOL_RECT`](#paint_tool_rect), [`PAINT_TOOL_CIRCLE`](#paint_tool_circle), [`PAINT_TOOL_FILL`](#paint_tool_fill), [`PAINT_TOOL_ERASER`](#paint_tool_eraser)

## Functions

<a id="main"></a>

### `main`

`function` | [progs/paint/paint.c:992](../../progs/paint/paint.c#L992)

```c
int main(int argc, char **argv)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `argv` | `char **` |  |  |

**Returns:** `int`

---

## Macros

<a id="stb_image_implementation"></a>

### `STB_IMAGE_IMPLEMENTATION`

`macro` | [progs/paint/paint.c:26](../../progs/paint/paint.c#L26)

```c
#define STB_IMAGE_IMPLEMENTATION
```

---

<a id="stbi_only_png"></a>

### `STBI_ONLY_PNG`

`macro` | [progs/paint/paint.c:27](../../progs/paint/paint.c#L27)

```c
#define STBI_ONLY_PNG
```

---

<a id="stbi_no_stdio"></a>

### `STBI_NO_STDIO`

`macro` | [progs/paint/paint.c:28](../../progs/paint/paint.c#L28)

```c
#define STBI_NO_STDIO
```

---

<a id="paint_w"></a>

### `PAINT_W`

`macro` | [progs/paint/paint.c:32](../../progs/paint/paint.c#L32)

```c
#define PAINT_W
```

Central configuration: every bound, tool, path, label and limit.

---

<a id="paint_n"></a>

### `PAINT_N`

`macro` | [progs/paint/paint.c:34](../../progs/paint/paint.c#L34)

```c
#define PAINT_N
```

---

<a id="paint_path_max"></a>

### `PAINT_PATH_MAX`

`macro` | [progs/paint/paint.c:35](../../progs/paint/paint.c#L35)

```c
#define PAINT_PATH_MAX
```

---

<a id="paint_file_max"></a>

### `PAINT_FILE_MAX`

`macro` | [progs/paint/paint.c:36](../../progs/paint/paint.c#L36)

```c
#define PAINT_FILE_MAX
```

---

<a id="paint_status_max"></a>

### `PAINT_STATUS_MAX`

`macro` | [progs/paint/paint.c:37](../../progs/paint/paint.c#L37)

```c
#define PAINT_STATUS_MAX
```

---

<a id="paint_ui_memory"></a>

### `PAINT_UI_MEMORY`

`macro` | [progs/paint/paint.c:38](../../progs/paint/paint.c#L38)

```c
#define PAINT_UI_MEMORY
```

---

<a id="paint_png_max"></a>

### `PAINT_PNG_MAX`

`macro` | [progs/paint/paint.c:39](../../progs/paint/paint.c#L39)

```c
#define PAINT_PNG_MAX
```

---

<a id="paint_png_max_dim"></a>

### `PAINT_PNG_MAX_DIM`

`macro` | [progs/paint/paint.c:40](../../progs/paint/paint.c#L40)

```c
#define PAINT_PNG_MAX_DIM
```

---

<a id="paint_title"></a>

### `PAINT_TITLE`

`macro` | [progs/paint/paint.c:41](../../progs/paint/paint.c#L41)

```c
#define PAINT_TITLE
```

---

<a id="paint_default_path"></a>

### `PAINT_DEFAULT_PATH`

`macro` | [progs/paint/paint.c:42](../../progs/paint/paint.c#L42)

```c
#define PAINT_DEFAULT_PATH
```

---

<a id="paint_panel_title"></a>

### `PAINT_PANEL_TITLE`

`macro` | [progs/paint/paint.c:43](../../progs/paint/paint.c#L43)

```c
#define PAINT_PANEL_TITLE
```

---

<a id="paint_file_btn_w"></a>

### `PAINT_FILE_BTN_W`

`macro` | [progs/paint/paint.c:44](../../progs/paint/paint.c#L44)

```c
#define PAINT_FILE_BTN_W
```

---

<a id="paint_frame_ms"></a>

### `PAINT_FRAME_MS`

`macro` | [progs/paint/paint.c:45](../../progs/paint/paint.c#L45)

```c
#define PAINT_FRAME_MS
```

---

<a id="paint_frame_attempts"></a>

### `PAINT_FRAME_ATTEMPTS`

`macro` | [progs/paint/paint.c:46](../../progs/paint/paint.c#L46)

```c
#define PAINT_FRAME_ATTEMPTS
```

---

<a id="paint_ncolors"></a>

### `PAINT_NCOLORS`

`macro` | [progs/paint/paint.c:47](../../progs/paint/paint.c#L47)

```c
#define PAINT_NCOLORS
```

---

<a id="paint_nsizes"></a>

### `PAINT_NSIZES`

`macro` | [progs/paint/paint.c:48](../../progs/paint/paint.c#L48)

```c
#define PAINT_NSIZES
```

---

<a id="paint_ntools"></a>

### `PAINT_NTOOLS`

`macro` | [progs/paint/paint.c:49](../../progs/paint/paint.c#L49)

```c
#define PAINT_NTOOLS
```

---

<a id="paint_tool_brush"></a>

### `PAINT_TOOL_BRUSH`

`macro` | [progs/paint/paint.c:52](../../progs/paint/paint.c#L52)

```c
#define PAINT_TOOL_BRUSH
```

Tool ids in toolbar order.

---

<a id="paint_tool_line"></a>

### `PAINT_TOOL_LINE`

`macro` | [progs/paint/paint.c:53](../../progs/paint/paint.c#L53)

```c
#define PAINT_TOOL_LINE
```

---

<a id="paint_tool_rect"></a>

### `PAINT_TOOL_RECT`

`macro` | [progs/paint/paint.c:54](../../progs/paint/paint.c#L54)

```c
#define PAINT_TOOL_RECT
```

---

<a id="paint_tool_circle"></a>

### `PAINT_TOOL_CIRCLE`

`macro` | [progs/paint/paint.c:55](../../progs/paint/paint.c#L55)

```c
#define PAINT_TOOL_CIRCLE
```

---

<a id="paint_tool_fill"></a>

### `PAINT_TOOL_FILL`

`macro` | [progs/paint/paint.c:56](../../progs/paint/paint.c#L56)

```c
#define PAINT_TOOL_FILL
```

---

<a id="paint_tool_eraser"></a>

### `PAINT_TOOL_ERASER`

`macro` | [progs/paint/paint.c:57](../../progs/paint/paint.c#L57)

```c
#define PAINT_TOOL_ERASER
```

---
