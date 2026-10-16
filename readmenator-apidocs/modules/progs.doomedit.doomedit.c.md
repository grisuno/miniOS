# `progs/doomedit/doomedit.c`

> Source: [progs/doomedit/doomedit.c:1](../../progs/doomedit/doomedit.c#L1) | language `c` | coverage 3.4% | [API index](../index.md)

doomedit.c - tile map editor that builds playable Doom PWADs.

## Contents

- **Functions:** [`areas`](#areas), [`main`](#main)
- **Macros:** [`DMAP_MAX_W`](#dmap_max_w), [`DMAP_DEF_W`](#dmap_def_w), [`DMAP_TILE`](#dmap_tile), [`DMAP_CELL_PX`](#dmap_cell_px), [`DMAP_CANVAS_W`](#dmap_canvas_w), [`DMAP_PREV_W`](#dmap_prev_w), [`DMAP_UI_MEMORY`](#dmap_ui_memory), [`DMAP_WAD_MAX`](#dmap_wad_max), [`DMAP_FNAME_MAX`](#dmap_fname_max), [`DMAP_STATUS_MAX`](#dmap_status_max), [`DMAP_SLOTS`](#dmap_slots), [`DMAP_LEVEL_COUNT`](#dmap_level_count), [`DMAP_RANDOM_ATTEMPTS`](#dmap_random_attempts), [`DMAP_MAX_SECTORS`](#dmap_max_sectors), [`DMAP_ROOM_MAX`](#dmap_room_max), [`DMAP_ROOM_TRIES`](#dmap_room_tries), [`DMAP_FRAME_MS`](#dmap_frame_ms), [`DMAP_TURN_STEP`](#dmap_turn_step), [`DMAP_MOVE_STEP`](#dmap_move_step), [`DMAP_FOV_PLANE`](#dmap_fov_plane), [`DMAP_MAX_LINES`](#dmap_max_lines), [`DMAP_MAX_VERTS`](#dmap_max_verts), [`DMAP_MAX_THINGS`](#dmap_max_things), [`DMAP_PLAYER_TYPE`](#dmap_player_type), [`DMAP_THING_OPT`](#dmap_thing_opt), [`DMAP_EXIT_SPECIAL`](#dmap_exit_special), [`DMAP_DOOR_SPECIAL`](#dmap_door_special), [`DMAP_FLAG_BLOCKING`](#dmap_flag_blocking), [`DMAP_FLAG_TWOSIDED`](#dmap_flag_twosided), [`DMAP_NO_SIDE`](#dmap_no_side), [`DMAP_WALL_MID`](#dmap_wall_mid), [`DMAP_EXIT_MID`](#dmap_exit_mid), [`DMAP_DOOR_UPPER`](#dmap_door_upper), [`DMAP_DARK_MID`](#dmap_dark_mid), [`DMAP_NUKE_MID`](#dmap_nuke_mid), [`DMAP_UNUSED_TEX`](#dmap_unused_tex), [`DMAP_FLOOR_FLAT`](#dmap_floor_flat), [`DMAP_NUKE_FLAT`](#dmap_nuke_flat), [`DMAP_CEIL_FLAT`](#dmap_ceil_flat), [`DMAP_NUKE_FLOOR`](#dmap_nuke_floor), [`DMAP_DOOR_CEIL`](#dmap_door_ceil), [`DMAP_LIGHT`](#dmap_light), [`DMAP_DARK_LIGHT`](#dmap_dark_light), [`DMAP_DOOR_LIGHT`](#dmap_door_light), [`DMAP_NUKE_SPECIAL`](#dmap_nuke_special), [`DMAP_NODE_LEAF`](#dmap_node_leaf), [`DMAP_TOOL_DOOM`](#dmap_tool_doom), [`DMAP_SAVE_TXT`](#dmap_save_txt), [`DMAP_SAVE_WAD`](#dmap_save_wad), [`DMAP_TITLE`](#dmap_title), [`DMAP_HISTORY`](#dmap_history), [`DMAP_TOOL_PAINT`](#dmap_tool_paint), [`DMAP_TOOL_LINE`](#dmap_tool_line), [`DMAP_TOOL_RECT`](#dmap_tool_rect), [`DMAP_TOOL_FILL`](#dmap_tool_fill), [`DMAP_BRUSH_COUNT`](#dmap_brush_count)

## Functions

<a id="areas"></a>

### `areas`

`function` | [progs/doomedit/doomedit.c:1150](../../progs/doomedit/doomedit.c#L1150)

```c
* floor areas (doors stand alone, dark and nukage never merge);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `alone` | `doors stand` |  |  |
| `merge` | `dark and nukage never` |  |  |

**Returns:** `* floor`

---

<a id="main"></a>

### `main`

`function` | [progs/doomedit/doomedit.c:2246](../../progs/doomedit/doomedit.c#L2246)

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

<a id="dmap_max_w"></a>

### `DMAP_MAX_W`

`macro` | [progs/doomedit/doomedit.c:55](../../progs/doomedit/doomedit.c#L55)

```c
#define DMAP_MAX_W
```

Central configuration: every bound, path, id and label in one place.

The window is 800x360, so the canvas column (32 tiles at 14 px) plus the side panel must fit beside the toolbar and status rows without scrolling: 22 + 16 + max(canvas, panel) stays under 360.

---

<a id="dmap_def_w"></a>

### `DMAP_DEF_W`

`macro` | [progs/doomedit/doomedit.c:57](../../progs/doomedit/doomedit.c#L57)

```c
#define DMAP_DEF_W
```

---

<a id="dmap_tile"></a>

### `DMAP_TILE`

`macro` | [progs/doomedit/doomedit.c:59](../../progs/doomedit/doomedit.c#L59)

```c
#define DMAP_TILE
```

---

<a id="dmap_cell_px"></a>

### `DMAP_CELL_PX`

`macro` | [progs/doomedit/doomedit.c:60](../../progs/doomedit/doomedit.c#L60)

```c
#define DMAP_CELL_PX
```

---

<a id="dmap_canvas_w"></a>

### `DMAP_CANVAS_W`

`macro` | [progs/doomedit/doomedit.c:61](../../progs/doomedit/doomedit.c#L61)

```c
#define DMAP_CANVAS_W
```

---

<a id="dmap_prev_w"></a>

### `DMAP_PREV_W`

`macro` | [progs/doomedit/doomedit.c:63](../../progs/doomedit/doomedit.c#L63)

```c
#define DMAP_PREV_W
```

---

<a id="dmap_ui_memory"></a>

### `DMAP_UI_MEMORY`

`macro` | [progs/doomedit/doomedit.c:65](../../progs/doomedit/doomedit.c#L65)

```c
#define DMAP_UI_MEMORY
```

---

<a id="dmap_wad_max"></a>

### `DMAP_WAD_MAX`

`macro` | [progs/doomedit/doomedit.c:66](../../progs/doomedit/doomedit.c#L66)

```c
#define DMAP_WAD_MAX
```

---

<a id="dmap_fname_max"></a>

### `DMAP_FNAME_MAX`

`macro` | [progs/doomedit/doomedit.c:67](../../progs/doomedit/doomedit.c#L67)

```c
#define DMAP_FNAME_MAX
```

---

<a id="dmap_status_max"></a>

### `DMAP_STATUS_MAX`

`macro` | [progs/doomedit/doomedit.c:68](../../progs/doomedit/doomedit.c#L68)

```c
#define DMAP_STATUS_MAX
```

---

<a id="dmap_slots"></a>

### `DMAP_SLOTS`

`macro` | [progs/doomedit/doomedit.c:69](../../progs/doomedit/doomedit.c#L69)

```c
#define DMAP_SLOTS
```

---

<a id="dmap_level_count"></a>

### `DMAP_LEVEL_COUNT`

`macro` | [progs/doomedit/doomedit.c:70](../../progs/doomedit/doomedit.c#L70)

```c
#define DMAP_LEVEL_COUNT
```

---

<a id="dmap_random_attempts"></a>

### `DMAP_RANDOM_ATTEMPTS`

`macro` | [progs/doomedit/doomedit.c:71](../../progs/doomedit/doomedit.c#L71)

```c
#define DMAP_RANDOM_ATTEMPTS
```

---

<a id="dmap_max_sectors"></a>

### `DMAP_MAX_SECTORS`

`macro` | [progs/doomedit/doomedit.c:72](../../progs/doomedit/doomedit.c#L72)

```c
#define DMAP_MAX_SECTORS
```

---

<a id="dmap_room_max"></a>

### `DMAP_ROOM_MAX`

`macro` | [progs/doomedit/doomedit.c:73](../../progs/doomedit/doomedit.c#L73)

```c
#define DMAP_ROOM_MAX
```

---

<a id="dmap_room_tries"></a>

### `DMAP_ROOM_TRIES`

`macro` | [progs/doomedit/doomedit.c:74](../../progs/doomedit/doomedit.c#L74)

```c
#define DMAP_ROOM_TRIES
```

---

<a id="dmap_frame_ms"></a>

### `DMAP_FRAME_MS`

`macro` | [progs/doomedit/doomedit.c:75](../../progs/doomedit/doomedit.c#L75)

```c
#define DMAP_FRAME_MS
```

---

<a id="dmap_turn_step"></a>

### `DMAP_TURN_STEP`

`macro` | [progs/doomedit/doomedit.c:76](../../progs/doomedit/doomedit.c#L76)

```c
#define DMAP_TURN_STEP
```

---

<a id="dmap_move_step"></a>

### `DMAP_MOVE_STEP`

`macro` | [progs/doomedit/doomedit.c:77](../../progs/doomedit/doomedit.c#L77)

```c
#define DMAP_MOVE_STEP
```

---

<a id="dmap_fov_plane"></a>

### `DMAP_FOV_PLANE`

`macro` | [progs/doomedit/doomedit.c:78](../../progs/doomedit/doomedit.c#L78)

```c
#define DMAP_FOV_PLANE
```

---

<a id="dmap_max_lines"></a>

### `DMAP_MAX_LINES`

`macro` | [progs/doomedit/doomedit.c:79](../../progs/doomedit/doomedit.c#L79)

```c
#define DMAP_MAX_LINES
```

---

<a id="dmap_max_verts"></a>

### `DMAP_MAX_VERTS`

`macro` | [progs/doomedit/doomedit.c:80](../../progs/doomedit/doomedit.c#L80)

```c
#define DMAP_MAX_VERTS
```

---

<a id="dmap_max_things"></a>

### `DMAP_MAX_THINGS`

`macro` | [progs/doomedit/doomedit.c:81](../../progs/doomedit/doomedit.c#L81)

```c
#define DMAP_MAX_THINGS
```

---

<a id="dmap_player_type"></a>

### `DMAP_PLAYER_TYPE`

`macro` | [progs/doomedit/doomedit.c:82](../../progs/doomedit/doomedit.c#L82)

```c
#define DMAP_PLAYER_TYPE
```

---

<a id="dmap_thing_opt"></a>

### `DMAP_THING_OPT`

`macro` | [progs/doomedit/doomedit.c:83](../../progs/doomedit/doomedit.c#L83)

```c
#define DMAP_THING_OPT
```

---

<a id="dmap_exit_special"></a>

### `DMAP_EXIT_SPECIAL`

`macro` | [progs/doomedit/doomedit.c:84](../../progs/doomedit/doomedit.c#L84)

```c
#define DMAP_EXIT_SPECIAL
```

---

<a id="dmap_door_special"></a>

### `DMAP_DOOR_SPECIAL`

`macro` | [progs/doomedit/doomedit.c:85](../../progs/doomedit/doomedit.c#L85)

```c
#define DMAP_DOOR_SPECIAL
```

---

<a id="dmap_flag_blocking"></a>

### `DMAP_FLAG_BLOCKING`

`macro` | [progs/doomedit/doomedit.c:86](../../progs/doomedit/doomedit.c#L86)

```c
#define DMAP_FLAG_BLOCKING
```

---

<a id="dmap_flag_twosided"></a>

### `DMAP_FLAG_TWOSIDED`

`macro` | [progs/doomedit/doomedit.c:87](../../progs/doomedit/doomedit.c#L87)

```c
#define DMAP_FLAG_TWOSIDED
```

---

<a id="dmap_no_side"></a>

### `DMAP_NO_SIDE`

`macro` | [progs/doomedit/doomedit.c:88](../../progs/doomedit/doomedit.c#L88)

```c
#define DMAP_NO_SIDE
```

---

<a id="dmap_wall_mid"></a>

### `DMAP_WALL_MID`

`macro` | [progs/doomedit/doomedit.c:89](../../progs/doomedit/doomedit.c#L89)

```c
#define DMAP_WALL_MID
```

---

<a id="dmap_exit_mid"></a>

### `DMAP_EXIT_MID`

`macro` | [progs/doomedit/doomedit.c:90](../../progs/doomedit/doomedit.c#L90)

```c
#define DMAP_EXIT_MID
```

---

<a id="dmap_door_upper"></a>

### `DMAP_DOOR_UPPER`

`macro` | [progs/doomedit/doomedit.c:91](../../progs/doomedit/doomedit.c#L91)

```c
#define DMAP_DOOR_UPPER
```

---

<a id="dmap_dark_mid"></a>

### `DMAP_DARK_MID`

`macro` | [progs/doomedit/doomedit.c:92](../../progs/doomedit/doomedit.c#L92)

```c
#define DMAP_DARK_MID
```

---

<a id="dmap_nuke_mid"></a>

### `DMAP_NUKE_MID`

`macro` | [progs/doomedit/doomedit.c:93](../../progs/doomedit/doomedit.c#L93)

```c
#define DMAP_NUKE_MID
```

---

<a id="dmap_unused_tex"></a>

### `DMAP_UNUSED_TEX`

`macro` | [progs/doomedit/doomedit.c:94](../../progs/doomedit/doomedit.c#L94)

```c
#define DMAP_UNUSED_TEX
```

---

<a id="dmap_floor_flat"></a>

### `DMAP_FLOOR_FLAT`

`macro` | [progs/doomedit/doomedit.c:95](../../progs/doomedit/doomedit.c#L95)

```c
#define DMAP_FLOOR_FLAT
```

---

<a id="dmap_nuke_flat"></a>

### `DMAP_NUKE_FLAT`

`macro` | [progs/doomedit/doomedit.c:96](../../progs/doomedit/doomedit.c#L96)

```c
#define DMAP_NUKE_FLAT
```

---

<a id="dmap_ceil_flat"></a>

### `DMAP_CEIL_FLAT`

`macro` | [progs/doomedit/doomedit.c:97](../../progs/doomedit/doomedit.c#L97)

```c
#define DMAP_CEIL_FLAT
```

---

<a id="dmap_nuke_floor"></a>

### `DMAP_NUKE_FLOOR`

`macro` | [progs/doomedit/doomedit.c:99](../../progs/doomedit/doomedit.c#L99)

```c
#define DMAP_NUKE_FLOOR
```

---

<a id="dmap_door_ceil"></a>

### `DMAP_DOOR_CEIL`

`macro` | [progs/doomedit/doomedit.c:101](../../progs/doomedit/doomedit.c#L101)

```c
#define DMAP_DOOR_CEIL
```

---

<a id="dmap_light"></a>

### `DMAP_LIGHT`

`macro` | [progs/doomedit/doomedit.c:102](../../progs/doomedit/doomedit.c#L102)

```c
#define DMAP_LIGHT
```

---

<a id="dmap_dark_light"></a>

### `DMAP_DARK_LIGHT`

`macro` | [progs/doomedit/doomedit.c:103](../../progs/doomedit/doomedit.c#L103)

```c
#define DMAP_DARK_LIGHT
```

---

<a id="dmap_door_light"></a>

### `DMAP_DOOR_LIGHT`

`macro` | [progs/doomedit/doomedit.c:104](../../progs/doomedit/doomedit.c#L104)

```c
#define DMAP_DOOR_LIGHT
```

---

<a id="dmap_nuke_special"></a>

### `DMAP_NUKE_SPECIAL`

`macro` | [progs/doomedit/doomedit.c:105](../../progs/doomedit/doomedit.c#L105)

```c
#define DMAP_NUKE_SPECIAL
```

---

<a id="dmap_node_leaf"></a>

### `DMAP_NODE_LEAF`

`macro` | [progs/doomedit/doomedit.c:106](../../progs/doomedit/doomedit.c#L106)

```c
#define DMAP_NODE_LEAF
```

---

<a id="dmap_tool_doom"></a>

### `DMAP_TOOL_DOOM`

`macro` | [progs/doomedit/doomedit.c:107](../../progs/doomedit/doomedit.c#L107)

```c
#define DMAP_TOOL_DOOM
```

---

<a id="dmap_save_txt"></a>

### `DMAP_SAVE_TXT`

`macro` | [progs/doomedit/doomedit.c:108](../../progs/doomedit/doomedit.c#L108)

```c
#define DMAP_SAVE_TXT
```

---

<a id="dmap_save_wad"></a>

### `DMAP_SAVE_WAD`

`macro` | [progs/doomedit/doomedit.c:109](../../progs/doomedit/doomedit.c#L109)

```c
#define DMAP_SAVE_WAD
```

---

<a id="dmap_title"></a>

### `DMAP_TITLE`

`macro` | [progs/doomedit/doomedit.c:110](../../progs/doomedit/doomedit.c#L110)

```c
#define DMAP_TITLE
```

---

<a id="dmap_history"></a>

### `DMAP_HISTORY`

`macro` | [progs/doomedit/doomedit.c:111](../../progs/doomedit/doomedit.c#L111)

```c
#define DMAP_HISTORY
```

---

<a id="dmap_tool_paint"></a>

### `DMAP_TOOL_PAINT`

`macro` | [progs/doomedit/doomedit.c:112](../../progs/doomedit/doomedit.c#L112)

```c
#define DMAP_TOOL_PAINT
```

---

<a id="dmap_tool_line"></a>

### `DMAP_TOOL_LINE`

`macro` | [progs/doomedit/doomedit.c:113](../../progs/doomedit/doomedit.c#L113)

```c
#define DMAP_TOOL_LINE
```

---

<a id="dmap_tool_rect"></a>

### `DMAP_TOOL_RECT`

`macro` | [progs/doomedit/doomedit.c:114](../../progs/doomedit/doomedit.c#L114)

```c
#define DMAP_TOOL_RECT
```

---

<a id="dmap_tool_fill"></a>

### `DMAP_TOOL_FILL`

`macro` | [progs/doomedit/doomedit.c:115](../../progs/doomedit/doomedit.c#L115)

```c
#define DMAP_TOOL_FILL
```

---

<a id="dmap_brush_count"></a>

### `DMAP_BRUSH_COUNT`

`macro` | [progs/doomedit/doomedit.c:230](../../progs/doomedit/doomedit.c#L230)

```c
#define DMAP_BRUSH_COUNT
```

---
