# `progs/file/file.c`

> Source: [progs/file/file.c:1](../../progs/file/file.c#L1) | language `c` | coverage 10.0% | [API index](../index.md)

Docstring: MiniOS file browser (Nuklear ring-3 app, MiniFS: file/file.elf).

## Contents

- **Structs:** [`file_assoc`](#file_assoc)
- **Functions:** [`main`](#main)
- **Macros:** [`STB_IMAGE_IMPLEMENTATION`](#stb_image_implementation), [`STBI_ONLY_PNG`](#stbi_only_png), [`STBI_NO_STDIO`](#stbi_no_stdio), [`MINIOS_LEAKCHECK_IMPL`](#minios_leakcheck_impl), [`MINIOS_LK_ENABLE`](#minios_lk_enable), [`FILE_MAX_PATH`](#file_max_path), [`FILE_MAX_ENTRIES`](#file_max_entries), [`FILE_NAME_MAX`](#file_name_max), [`FILE_LIST_CAP`](#file_list_cap), [`FILE_ASSOC_PATH`](#file_assoc_path), [`FILE_EXT_MAX`](#file_ext_max), [`FILE_PROG_MAX`](#file_prog_max), [`FILE_TOOL_VEDIT`](#file_tool_vedit), [`FILE_TOOL_CVM`](#file_tool_cvm), [`FILE_STATUS_MAX`](#file_status_max), [`FILE_UI_MEMORY`](#file_ui_memory), [`FILE_PREVIEW_W`](#file_preview_w), [`FILE_PREVIEW_FILE_MAX`](#file_preview_file_max), [`FILE_TITLE`](#file_title), [`FILE_ACTION_SHELL`](#file_action_shell), [`FILE_LOG_LINE`](#file_log_line), [`FILE_ICON_SMALL`](#file_icon_small), [`FILE_ICON_BIG`](#file_icon_big), [`FILE_ICON_MAX`](#file_icon_max), [`FILE_ICON_N`](#file_icon_n), [`FILE_ICON_FOLDER`](#file_icon_folder), [`FILE_ICON_FILES`](#file_icon_files), [`FILE_ICON_IMAGE`](#file_icon_image), [`FILE_ICON_OBJECT`](#file_icon_object), [`FILE_ICON_PATH_FOLDER`](#file_icon_path_folder), [`FILE_ICON_PATH_FILES`](#file_icon_path_files), [`FILE_ICON_PATH_IMAGE`](#file_icon_path_image), [`FILE_ICON_PATH_OBJECT`](#file_icon_path_object), [`FILE_ACT_TEXT`](#file_act_text), [`FILE_ACT_SHELL`](#file_act_shell), [`FILE_ACT_INTERNAL`](#file_act_internal), [`FILE_ACT_UNKNOWN`](#file_act_unknown)

## Structs

<a id="file_assoc"></a>

### `file_assoc`

`struct` | [progs/file/file.c:76](../../progs/file/file.c#L76)

```c
struct file_assoc
```

---

## Functions

<a id="main"></a>

### `main`

`function` | [progs/file/file.c:838](../../progs/file/file.c#L838)

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

`macro` | [progs/file/file.c:24](../../progs/file/file.c#L24)

```c
#define STB_IMAGE_IMPLEMENTATION
```

---

<a id="stbi_only_png"></a>

### `STBI_ONLY_PNG`

`macro` | [progs/file/file.c:25](../../progs/file/file.c#L25)

```c
#define STBI_ONLY_PNG
```

---

<a id="stbi_no_stdio"></a>

### `STBI_NO_STDIO`

`macro` | [progs/file/file.c:26](../../progs/file/file.c#L26)

```c
#define STBI_NO_STDIO
```

---

<a id="minios_leakcheck_impl"></a>

### `MINIOS_LEAKCHECK_IMPL`

`macro` | [progs/file/file.c:28](../../progs/file/file.c#L28)

```c
#define MINIOS_LEAKCHECK_IMPL
```

---

<a id="minios_lk_enable"></a>

### `MINIOS_LK_ENABLE`

`macro` | [progs/file/file.c:29](../../progs/file/file.c#L29)

```c
#define MINIOS_LK_ENABLE
```

---

<a id="file_max_path"></a>

### `FILE_MAX_PATH`

`macro` | [progs/file/file.c:33](../../progs/file/file.c#L33)

```c
#define FILE_MAX_PATH
```

Central configuration: every bound, tool, directory, label and limit.

---

<a id="file_max_entries"></a>

### `FILE_MAX_ENTRIES`

`macro` | [progs/file/file.c:34](../../progs/file/file.c#L34)

```c
#define FILE_MAX_ENTRIES
```

---

<a id="file_name_max"></a>

### `FILE_NAME_MAX`

`macro` | [progs/file/file.c:35](../../progs/file/file.c#L35)

```c
#define FILE_NAME_MAX
```

---

<a id="file_list_cap"></a>

### `FILE_LIST_CAP`

`macro` | [progs/file/file.c:36](../../progs/file/file.c#L36)

```c
#define FILE_LIST_CAP
```

---

<a id="file_assoc_path"></a>

### `FILE_ASSOC_PATH`

`macro` | [progs/file/file.c:37](../../progs/file/file.c#L37)

```c
#define FILE_ASSOC_PATH
```

---

<a id="file_ext_max"></a>

### `FILE_EXT_MAX`

`macro` | [progs/file/file.c:38](../../progs/file/file.c#L38)

```c
#define FILE_EXT_MAX
```

---

<a id="file_prog_max"></a>

### `FILE_PROG_MAX`

`macro` | [progs/file/file.c:39](../../progs/file/file.c#L39)

```c
#define FILE_PROG_MAX
```

---

<a id="file_tool_vedit"></a>

### `FILE_TOOL_VEDIT`

`macro` | [progs/file/file.c:40](../../progs/file/file.c#L40)

```c
#define FILE_TOOL_VEDIT
```

---

<a id="file_tool_cvm"></a>

### `FILE_TOOL_CVM`

`macro` | [progs/file/file.c:41](../../progs/file/file.c#L41)

```c
#define FILE_TOOL_CVM
```

---

<a id="file_status_max"></a>

### `FILE_STATUS_MAX`

`macro` | [progs/file/file.c:42](../../progs/file/file.c#L42)

```c
#define FILE_STATUS_MAX
```

---

<a id="file_ui_memory"></a>

### `FILE_UI_MEMORY`

`macro` | [progs/file/file.c:43](../../progs/file/file.c#L43)

```c
#define FILE_UI_MEMORY
```

---

<a id="file_preview_w"></a>

### `FILE_PREVIEW_W`

`macro` | [progs/file/file.c:44](../../progs/file/file.c#L44)

```c
#define FILE_PREVIEW_W
```

---

<a id="file_preview_file_max"></a>

### `FILE_PREVIEW_FILE_MAX`

`macro` | [progs/file/file.c:46](../../progs/file/file.c#L46)

```c
#define FILE_PREVIEW_FILE_MAX
```

---

<a id="file_title"></a>

### `FILE_TITLE`

`macro` | [progs/file/file.c:47](../../progs/file/file.c#L47)

```c
#define FILE_TITLE
```

---

<a id="file_action_shell"></a>

### `FILE_ACTION_SHELL`

`macro` | [progs/file/file.c:48](../../progs/file/file.c#L48)

```c
#define FILE_ACTION_SHELL
```

---

<a id="file_log_line"></a>

### `FILE_LOG_LINE`

`macro` | [progs/file/file.c:50](../../progs/file/file.c#L50)

```c
#define FILE_LOG_LINE
```

---

<a id="file_icon_small"></a>

### `FILE_ICON_SMALL`

`macro` | [progs/file/file.c:57](../../progs/file/file.c#L57)

```c
#define FILE_ICON_SMALL
```

Entry icons: indexed pixels plus a 0/1 alpha mask, decoded once from /icons at startup through the backend NK_COMMAND_IMAGE path.

Small is the default grid; big is the toggled grid. Buffers hold the big size and decode scales into the live prefix, so the toggle is one reload with no extra memory.

---

<a id="file_icon_big"></a>

### `FILE_ICON_BIG`

`macro` | [progs/file/file.c:58](../../progs/file/file.c#L58)

```c
#define FILE_ICON_BIG
```

---

<a id="file_icon_max"></a>

### `FILE_ICON_MAX`

`macro` | [progs/file/file.c:59](../../progs/file/file.c#L59)

```c
#define FILE_ICON_MAX
```

---

<a id="file_icon_n"></a>

### `FILE_ICON_N`

`macro` | [progs/file/file.c:60](../../progs/file/file.c#L60)

```c
#define FILE_ICON_N
```

---

<a id="file_icon_folder"></a>

### `FILE_ICON_FOLDER`

`macro` | [progs/file/file.c:61](../../progs/file/file.c#L61)

```c
#define FILE_ICON_FOLDER
```

---

<a id="file_icon_files"></a>

### `FILE_ICON_FILES`

`macro` | [progs/file/file.c:62](../../progs/file/file.c#L62)

```c
#define FILE_ICON_FILES
```

---

<a id="file_icon_image"></a>

### `FILE_ICON_IMAGE`

`macro` | [progs/file/file.c:63](../../progs/file/file.c#L63)

```c
#define FILE_ICON_IMAGE
```

---

<a id="file_icon_object"></a>

### `FILE_ICON_OBJECT`

`macro` | [progs/file/file.c:64](../../progs/file/file.c#L64)

```c
#define FILE_ICON_OBJECT
```

---

<a id="file_icon_path_folder"></a>

### `FILE_ICON_PATH_FOLDER`

`macro` | [progs/file/file.c:65](../../progs/file/file.c#L65)

```c
#define FILE_ICON_PATH_FOLDER
```

---

<a id="file_icon_path_files"></a>

### `FILE_ICON_PATH_FILES`

`macro` | [progs/file/file.c:66](../../progs/file/file.c#L66)

```c
#define FILE_ICON_PATH_FILES
```

---

<a id="file_icon_path_image"></a>

### `FILE_ICON_PATH_IMAGE`

`macro` | [progs/file/file.c:67](../../progs/file/file.c#L67)

```c
#define FILE_ICON_PATH_IMAGE
```

---

<a id="file_icon_path_object"></a>

### `FILE_ICON_PATH_OBJECT`

`macro` | [progs/file/file.c:68](../../progs/file/file.c#L68)

```c
#define FILE_ICON_PATH_OBJECT
```

---

<a id="file_act_text"></a>

### `FILE_ACT_TEXT`

`macro` | [progs/file/file.c:71](../../progs/file/file.c#L71)

```c
#define FILE_ACT_TEXT
```

Dispatch kinds resolved from the association table.

---

<a id="file_act_shell"></a>

### `FILE_ACT_SHELL`

`macro` | [progs/file/file.c:72](../../progs/file/file.c#L72)

```c
#define FILE_ACT_SHELL
```

---

<a id="file_act_internal"></a>

### `FILE_ACT_INTERNAL`

`macro` | [progs/file/file.c:73](../../progs/file/file.c#L73)

```c
#define FILE_ACT_INTERNAL
```

---

<a id="file_act_unknown"></a>

### `FILE_ACT_UNKNOWN`

`macro` | [progs/file/file.c:74](../../progs/file/file.c#L74)

```c
#define FILE_ACT_UNKNOWN
```

---
