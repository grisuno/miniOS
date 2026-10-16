# `progs/vedit/vedit.c`

> Source: [progs/vedit/vedit.c:1](../../progs/vedit/vedit.c#L1) | language `c` | coverage 7.7% | [API index](../index.md)

vedit IDE build and run contract.

## Contents

- **Functions:** [`definitions`](#definitions), [`separators`](#separators), [`strcmp`](#strcmp), [`main`](#main)
- **Macros:** [`MINIOS_LEAKCHECK_IMPL`](#minios_leakcheck_impl), [`MINIOS_LK_ENABLE`](#minios_lk_enable), [`VEDIT_MAX_LINES`](#vedit_max_lines), [`VEDIT_LINE_MAX`](#vedit_line_max), [`VEDIT_LINE_USED`](#vedit_line_used), [`VEDIT_FILE_MAX`](#vedit_file_max), [`VEDIT_FNAME_MAX`](#vedit_fname_max), [`VEDIT_DEFAULT_FILE`](#vedit_default_file), [`VEDIT_MSG_MAX`](#vedit_msg_max), [`VEDIT_WORD_MAX`](#vedit_word_max), [`VEDIT_TAB_W`](#vedit_tab_w), [`VEDIT_ESC_MS`](#vedit_esc_ms), [`VEDIT_FRAME_MS`](#vedit_frame_ms), [`VEDIT_UI_MEMORY`](#vedit_ui_memory), [`VEDIT_KEY_RUN`](#vedit_key_run), [`VEDIT_KEY_LINK`](#vedit_key_link), [`VEDIT_KEY_DUMP`](#vedit_key_dump), [`VEDIT_TOOL_MINIGCC`](#vedit_tool_minigcc), [`VEDIT_TOOL_LD`](#vedit_tool_ld), [`VEDIT_TOOL_SIGN`](#vedit_tool_sign), [`VEDIT_TOOL_CVM`](#vedit_tool_cvm), [`VEDIT_TOOL_LUA`](#vedit_tool_lua), [`VEDIT_TOOL_PY`](#vedit_tool_py), [`VEDIT_TOOL_LISP`](#vedit_tool_lisp), [`VEDIT_DIR_ASM`](#vedit_dir_asm), [`VEDIT_DIR_BIN`](#vedit_dir_bin), [`VEDIT_DIR_CVM`](#vedit_dir_cvm), [`VEDIT_BUILD_LOG`](#vedit_build_log), [`VEDIT_LINK_ELF`](#vedit_link_elf), [`VEDIT_LINK_CVM`](#vedit_link_cvm), [`VEDIT_STATUS_MAX`](#vedit_status_max), [`VEDIT_BASE_MAX`](#vedit_base_max), [`VEDIT_PATH_MAX`](#vedit_path_max), [`VEDIT_LOG_TAIL`](#vedit_log_tail), [`VEDIT_LANG_TEXT`](#vedit_lang_text), [`VEDIT_LANG_C`](#vedit_lang_c), [`VEDIT_LANG_PY`](#vedit_lang_py), [`VEDIT_LANG_LUA`](#vedit_lang_lua), [`VEDIT_LANG_ASM`](#vedit_lang_asm), [`VEDIT_LANG_LISP`](#vedit_lang_lisp), [`VEDIT_COL_DEFAULT`](#vedit_col_default), [`VEDIT_COL_KEYWORD`](#vedit_col_keyword), [`VEDIT_COL_STRING`](#vedit_col_string), [`VEDIT_COL_COMMENT`](#vedit_col_comment), [`VEDIT_COL_NUMBER`](#vedit_col_number), [`VEDIT_COL_PREPROC`](#vedit_col_preproc), [`VEDIT_ST_BLOCK`](#vedit_st_block), [`VEDIT_ST_PY3S`](#vedit_st_py3s), [`VEDIT_ST_PY3D`](#vedit_st_py3d), [`VEDIT_ST_LUABLK`](#vedit_st_luablk), [`VEDIT_ST_LUASTR`](#vedit_st_luastr), [`VEDIT_KEY_UP`](#vedit_key_up), [`VEDIT_KEY_DOWN`](#vedit_key_down), [`VEDIT_KEY_LEFT`](#vedit_key_left), [`VEDIT_KEY_RIGHT`](#vedit_key_right), [`VEDIT_KEY_HOME`](#vedit_key_home), [`VEDIT_KEY_END`](#vedit_key_end), [`VEDIT_KEY_PGUP`](#vedit_key_pgup), [`VEDIT_KEY_PGDN`](#vedit_key_pgdn), [`VEDIT_KEY_DEL`](#vedit_key_del), [`VEDIT_KEY_ESC`](#vedit_key_esc), [`VEDIT_NBUF`](#vedit_nbuf), [`VEDIT_KILL_N`](#vedit_kill_n), [`VEDIT_KILL_MAX`](#vedit_kill_max), [`VEDIT_MACRO_MAX`](#vedit_macro_max), [`VEDIT_HIST_N`](#vedit_hist_n), [`VEDIT_CMD_MAX`](#vedit_cmd_max), [`VEDIT_MAGIC_MAX`](#vedit_magic_max), [`VEDIT_KEY_META`](#vedit_key_meta), [`VEDIT_KEY_ARG`](#vedit_key_arg), [`VEDIT_KEY_MARK`](#vedit_key_mark), [`VEDIT_KEY_KILL_LINE`](#vedit_key_kill_line), [`VEDIT_KEY_YANK`](#vedit_key_yank), [`VEDIT_KEY_TRANSPOSE`](#vedit_key_transpose), [`VEDIT_KEY_FENCE`](#vedit_key_fence), [`VEDIT_KEY_BOL`](#vedit_key_bol), [`VEDIT_KEY_EOL`](#vedit_key_eol), [`vedit_pool`](#vedit_pool), [`vedit_used`](#vedit_used), [`vedit_count`](#vedit_count), [`vedit_cx`](#vedit_cx), [`vedit_cy`](#vedit_cy), [`vedit_top`](#vedit_top), [`vedit_hoff`](#vedit_hoff), [`vedit_dirty`](#vedit_dirty), [`vedit_trunc`](#vedit_trunc), [`vedit_lang`](#vedit_lang), [`vedit_fname`](#vedit_fname), [`vedit_msg`](#vedit_msg), [`VEDIT_PROMPT_FIND`](#vedit_prompt_find), [`VEDIT_PROMPT_GOTO`](#vedit_prompt_goto), [`VEDIT_PROMPT_NAME`](#vedit_prompt_name), [`VEDIT_PROMPT_LINK`](#vedit_prompt_link), [`VEDIT_PROMPT_CMD`](#vedit_prompt_cmd), [`VEDIT_PROMPT_ISEARCH_F`](#vedit_prompt_isearch_f), [`VEDIT_PROMPT_ISEARCH_R`](#vedit_prompt_isearch_r), [`VEDIT_PROMPT_REP_OLD`](#vedit_prompt_rep_old), [`VEDIT_PROMPT_REP_NEW`](#vedit_prompt_rep_new), [`VEDIT_PROMPT_QREP`](#vedit_prompt_qrep), [`VEDIT_PROMPT_SHELLCMD`](#vedit_prompt_shellcmd), [`VEDIT_PROMPT_FILTER`](#vedit_prompt_filter), [`VEDIT_PROMPT_SELECT`](#vedit_prompt_select), [`VEDIT_PROMPT_GREP`](#vedit_prompt_grep), [`VEDIT_PROMPT_BINDKEY`](#vedit_prompt_bindkey), [`VEDIT_PROMPT_BINDCMD`](#vedit_prompt_bindcmd), [`VEDIT_FILL_COL`](#vedit_fill_col), [`VEDIT_TMP_OUT`](#vedit_tmp_out), [`VEDIT_TMP_IN`](#vedit_tmp_in), [`VEDIT_TMP_F`](#vedit_tmp_f), [`VEDIT_SH_ARGS`](#vedit_sh_args), [`VEDIT_SH_LINE`](#vedit_sh_line), [`VEDIT_CLIP_MAX`](#vedit_clip_max)

## Functions

<a id="definitions"></a>

### `definitions`

`function` | [progs/vedit/vedit.c:268](../../progs/vedit/vedit.c#L268)

```c
* definitions (C99, one file, no headers). */ static void vedit_str_case(char *s, int mode);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `file` | `one` |  |  |
| `headers` | `no` |  |  |

**Returns:** `*`

---

<a id="separators"></a>

### `separators`

`function` | [progs/vedit/vedit.c:403](../../progs/vedit/vedit.c#L403)

```c
* allow_quote exists because C digit separators (1'000'000) are not * valid in Python/Lua number...
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `1'000'000` |  |  |  |

**Returns:** `* allow_quote exists because C digit`

---

<a id="strcmp"></a>

### `strcmp`

`function` | [progs/vedit/vedit.c:3196](../../progs/vedit/vedit.c#L3196)

```c
strcmp(name, "describe-bindings") == 0)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `bindings` | `"describe- "` |  |  |

---

<a id="main"></a>

### `main`

`function` | [progs/vedit/vedit.c:4839](../../progs/vedit/vedit.c#L4839)

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

<a id="minios_leakcheck_impl"></a>

### `MINIOS_LEAKCHECK_IMPL`

`macro` | [progs/vedit/vedit.c:33](../../progs/vedit/vedit.c#L33)

```c
#define MINIOS_LEAKCHECK_IMPL
```

---

<a id="minios_lk_enable"></a>

### `MINIOS_LK_ENABLE`

`macro` | [progs/vedit/vedit.c:34](../../progs/vedit/vedit.c#L34)

```c
#define MINIOS_LK_ENABLE
```

---

<a id="vedit_max_lines"></a>

### `VEDIT_MAX_LINES`

`macro` | [progs/vedit/vedit.c:114](../../progs/vedit/vedit.c#L114)

```c
#define VEDIT_MAX_LINES
```

Central configuration: every bound, key, tool, directory and label.

---

<a id="vedit_line_max"></a>

### `VEDIT_LINE_MAX`

`macro` | [progs/vedit/vedit.c:115](../../progs/vedit/vedit.c#L115)

```c
#define VEDIT_LINE_MAX
```

---

<a id="vedit_line_used"></a>

### `VEDIT_LINE_USED`

`macro` | [progs/vedit/vedit.c:116](../../progs/vedit/vedit.c#L116)

```c
#define VEDIT_LINE_USED
```

---

<a id="vedit_file_max"></a>

### `VEDIT_FILE_MAX`

`macro` | [progs/vedit/vedit.c:117](../../progs/vedit/vedit.c#L117)

```c
#define VEDIT_FILE_MAX
```

---

<a id="vedit_fname_max"></a>

### `VEDIT_FNAME_MAX`

`macro` | [progs/vedit/vedit.c:118](../../progs/vedit/vedit.c#L118)

```c
#define VEDIT_FNAME_MAX
```

---

<a id="vedit_default_file"></a>

### `VEDIT_DEFAULT_FILE`

`macro` | [progs/vedit/vedit.c:119](../../progs/vedit/vedit.c#L119)

```c
#define VEDIT_DEFAULT_FILE
```

---

<a id="vedit_msg_max"></a>

### `VEDIT_MSG_MAX`

`macro` | [progs/vedit/vedit.c:120](../../progs/vedit/vedit.c#L120)

```c
#define VEDIT_MSG_MAX
```

---

<a id="vedit_word_max"></a>

### `VEDIT_WORD_MAX`

`macro` | [progs/vedit/vedit.c:121](../../progs/vedit/vedit.c#L121)

```c
#define VEDIT_WORD_MAX
```

---

<a id="vedit_tab_w"></a>

### `VEDIT_TAB_W`

`macro` | [progs/vedit/vedit.c:122](../../progs/vedit/vedit.c#L122)

```c
#define VEDIT_TAB_W
```

---

<a id="vedit_esc_ms"></a>

### `VEDIT_ESC_MS`

`macro` | [progs/vedit/vedit.c:123](../../progs/vedit/vedit.c#L123)

```c
#define VEDIT_ESC_MS
```

---

<a id="vedit_frame_ms"></a>

### `VEDIT_FRAME_MS`

`macro` | [progs/vedit/vedit.c:124](../../progs/vedit/vedit.c#L124)

```c
#define VEDIT_FRAME_MS
```

---

<a id="vedit_ui_memory"></a>

### `VEDIT_UI_MEMORY`

`macro` | [progs/vedit/vedit.c:125](../../progs/vedit/vedit.c#L125)

```c
#define VEDIT_UI_MEMORY
```

---

<a id="vedit_key_run"></a>

### `VEDIT_KEY_RUN`

`macro` | [progs/vedit/vedit.c:126](../../progs/vedit/vedit.c#L126)

```c
#define VEDIT_KEY_RUN
```

---

<a id="vedit_key_link"></a>

### `VEDIT_KEY_LINK`

`macro` | [progs/vedit/vedit.c:127](../../progs/vedit/vedit.c#L127)

```c
#define VEDIT_KEY_LINK
```

---

<a id="vedit_key_dump"></a>

### `VEDIT_KEY_DUMP`

`macro` | [progs/vedit/vedit.c:128](../../progs/vedit/vedit.c#L128)

```c
#define VEDIT_KEY_DUMP
```

---

<a id="vedit_tool_minigcc"></a>

### `VEDIT_TOOL_MINIGCC`

`macro` | [progs/vedit/vedit.c:129](../../progs/vedit/vedit.c#L129)

```c
#define VEDIT_TOOL_MINIGCC
```

---

<a id="vedit_tool_ld"></a>

### `VEDIT_TOOL_LD`

`macro` | [progs/vedit/vedit.c:130](../../progs/vedit/vedit.c#L130)

```c
#define VEDIT_TOOL_LD
```

---

<a id="vedit_tool_sign"></a>

### `VEDIT_TOOL_SIGN`

`macro` | [progs/vedit/vedit.c:131](../../progs/vedit/vedit.c#L131)

```c
#define VEDIT_TOOL_SIGN
```

---

<a id="vedit_tool_cvm"></a>

### `VEDIT_TOOL_CVM`

`macro` | [progs/vedit/vedit.c:132](../../progs/vedit/vedit.c#L132)

```c
#define VEDIT_TOOL_CVM
```

---

<a id="vedit_tool_lua"></a>

### `VEDIT_TOOL_LUA`

`macro` | [progs/vedit/vedit.c:133](../../progs/vedit/vedit.c#L133)

```c
#define VEDIT_TOOL_LUA
```

---

<a id="vedit_tool_py"></a>

### `VEDIT_TOOL_PY`

`macro` | [progs/vedit/vedit.c:134](../../progs/vedit/vedit.c#L134)

```c
#define VEDIT_TOOL_PY
```

---

<a id="vedit_tool_lisp"></a>

### `VEDIT_TOOL_LISP`

`macro` | [progs/vedit/vedit.c:135](../../progs/vedit/vedit.c#L135)

```c
#define VEDIT_TOOL_LISP
```

---

<a id="vedit_dir_asm"></a>

### `VEDIT_DIR_ASM`

`macro` | [progs/vedit/vedit.c:136](../../progs/vedit/vedit.c#L136)

```c
#define VEDIT_DIR_ASM
```

---

<a id="vedit_dir_bin"></a>

### `VEDIT_DIR_BIN`

`macro` | [progs/vedit/vedit.c:137](../../progs/vedit/vedit.c#L137)

```c
#define VEDIT_DIR_BIN
```

---

<a id="vedit_dir_cvm"></a>

### `VEDIT_DIR_CVM`

`macro` | [progs/vedit/vedit.c:138](../../progs/vedit/vedit.c#L138)

```c
#define VEDIT_DIR_CVM
```

---

<a id="vedit_build_log"></a>

### `VEDIT_BUILD_LOG`

`macro` | [progs/vedit/vedit.c:139](../../progs/vedit/vedit.c#L139)

```c
#define VEDIT_BUILD_LOG
```

---

<a id="vedit_link_elf"></a>

### `VEDIT_LINK_ELF`

`macro` | [progs/vedit/vedit.c:140](../../progs/vedit/vedit.c#L140)

```c
#define VEDIT_LINK_ELF
```

---

<a id="vedit_link_cvm"></a>

### `VEDIT_LINK_CVM`

`macro` | [progs/vedit/vedit.c:141](../../progs/vedit/vedit.c#L141)

```c
#define VEDIT_LINK_CVM
```

---

<a id="vedit_status_max"></a>

### `VEDIT_STATUS_MAX`

`macro` | [progs/vedit/vedit.c:142](../../progs/vedit/vedit.c#L142)

```c
#define VEDIT_STATUS_MAX
```

---

<a id="vedit_base_max"></a>

### `VEDIT_BASE_MAX`

`macro` | [progs/vedit/vedit.c:143](../../progs/vedit/vedit.c#L143)

```c
#define VEDIT_BASE_MAX
```

---

<a id="vedit_path_max"></a>

### `VEDIT_PATH_MAX`

`macro` | [progs/vedit/vedit.c:144](../../progs/vedit/vedit.c#L144)

```c
#define VEDIT_PATH_MAX
```

---

<a id="vedit_log_tail"></a>

### `VEDIT_LOG_TAIL`

`macro` | [progs/vedit/vedit.c:145](../../progs/vedit/vedit.c#L145)

```c
#define VEDIT_LOG_TAIL
```

---

<a id="vedit_lang_text"></a>

### `VEDIT_LANG_TEXT`

`macro` | [progs/vedit/vedit.c:148](../../progs/vedit/vedit.c#L148)

```c
#define VEDIT_LANG_TEXT
```

---- Languages ----

---

<a id="vedit_lang_c"></a>

### `VEDIT_LANG_C`

`macro` | [progs/vedit/vedit.c:149](../../progs/vedit/vedit.c#L149)

```c
#define VEDIT_LANG_C
```

---

<a id="vedit_lang_py"></a>

### `VEDIT_LANG_PY`

`macro` | [progs/vedit/vedit.c:150](../../progs/vedit/vedit.c#L150)

```c
#define VEDIT_LANG_PY
```

---

<a id="vedit_lang_lua"></a>

### `VEDIT_LANG_LUA`

`macro` | [progs/vedit/vedit.c:151](../../progs/vedit/vedit.c#L151)

```c
#define VEDIT_LANG_LUA
```

---

<a id="vedit_lang_asm"></a>

### `VEDIT_LANG_ASM`

`macro` | [progs/vedit/vedit.c:152](../../progs/vedit/vedit.c#L152)

```c
#define VEDIT_LANG_ASM
```

---

<a id="vedit_lang_lisp"></a>

### `VEDIT_LANG_LISP`

`macro` | [progs/vedit/vedit.c:153](../../progs/vedit/vedit.c#L153)

```c
#define VEDIT_LANG_LISP
```

---

<a id="vedit_col_default"></a>

### `VEDIT_COL_DEFAULT`

`macro` | [progs/vedit/vedit.c:156](../../progs/vedit/vedit.c#L156)

```c
#define VEDIT_COL_DEFAULT
```

---- Token colours (theme; RGB mirrors of the desktop/icon palette) ----

---

<a id="vedit_col_keyword"></a>

### `VEDIT_COL_KEYWORD`

`macro` | [progs/vedit/vedit.c:157](../../progs/vedit/vedit.c#L157)

```c
#define VEDIT_COL_KEYWORD
```

---

<a id="vedit_col_string"></a>

### `VEDIT_COL_STRING`

`macro` | [progs/vedit/vedit.c:158](../../progs/vedit/vedit.c#L158)

```c
#define VEDIT_COL_STRING
```

---

<a id="vedit_col_comment"></a>

### `VEDIT_COL_COMMENT`

`macro` | [progs/vedit/vedit.c:159](../../progs/vedit/vedit.c#L159)

```c
#define VEDIT_COL_COMMENT
```

---

<a id="vedit_col_number"></a>

### `VEDIT_COL_NUMBER`

`macro` | [progs/vedit/vedit.c:160](../../progs/vedit/vedit.c#L160)

```c
#define VEDIT_COL_NUMBER
```

---

<a id="vedit_col_preproc"></a>

### `VEDIT_COL_PREPROC`

`macro` | [progs/vedit/vedit.c:161](../../progs/vedit/vedit.c#L161)

```c
#define VEDIT_COL_PREPROC
```

---

<a id="vedit_st_block"></a>

### `VEDIT_ST_BLOCK`

`macro` | [progs/vedit/vedit.c:164](../../progs/vedit/vedit.c#L164)

```c
#define VEDIT_ST_BLOCK
```

---- Cross-line scanner state ----

---

<a id="vedit_st_py3s"></a>

### `VEDIT_ST_PY3S`

`macro` | [progs/vedit/vedit.c:165](../../progs/vedit/vedit.c#L165)

```c
#define VEDIT_ST_PY3S
```

---

<a id="vedit_st_py3d"></a>

### `VEDIT_ST_PY3D`

`macro` | [progs/vedit/vedit.c:166](../../progs/vedit/vedit.c#L166)

```c
#define VEDIT_ST_PY3D
```

---

<a id="vedit_st_luablk"></a>

### `VEDIT_ST_LUABLK`

`macro` | [progs/vedit/vedit.c:167](../../progs/vedit/vedit.c#L167)

```c
#define VEDIT_ST_LUABLK
```

---

<a id="vedit_st_luastr"></a>

### `VEDIT_ST_LUASTR`

`macro` | [progs/vedit/vedit.c:168](../../progs/vedit/vedit.c#L168)

```c
#define VEDIT_ST_LUASTR
```

---

<a id="vedit_key_up"></a>

### `VEDIT_KEY_UP`

`macro` | [progs/vedit/vedit.c:171](../../progs/vedit/vedit.c#L171)

```c
#define VEDIT_KEY_UP
```

---- Decoded keys above any byte ----

---

<a id="vedit_key_down"></a>

### `VEDIT_KEY_DOWN`

`macro` | [progs/vedit/vedit.c:172](../../progs/vedit/vedit.c#L172)

```c
#define VEDIT_KEY_DOWN
```

---

<a id="vedit_key_left"></a>

### `VEDIT_KEY_LEFT`

`macro` | [progs/vedit/vedit.c:173](../../progs/vedit/vedit.c#L173)

```c
#define VEDIT_KEY_LEFT
```

---

<a id="vedit_key_right"></a>

### `VEDIT_KEY_RIGHT`

`macro` | [progs/vedit/vedit.c:174](../../progs/vedit/vedit.c#L174)

```c
#define VEDIT_KEY_RIGHT
```

---

<a id="vedit_key_home"></a>

### `VEDIT_KEY_HOME`

`macro` | [progs/vedit/vedit.c:175](../../progs/vedit/vedit.c#L175)

```c
#define VEDIT_KEY_HOME
```

---

<a id="vedit_key_end"></a>

### `VEDIT_KEY_END`

`macro` | [progs/vedit/vedit.c:176](../../progs/vedit/vedit.c#L176)

```c
#define VEDIT_KEY_END
```

---

<a id="vedit_key_pgup"></a>

### `VEDIT_KEY_PGUP`

`macro` | [progs/vedit/vedit.c:177](../../progs/vedit/vedit.c#L177)

```c
#define VEDIT_KEY_PGUP
```

---

<a id="vedit_key_pgdn"></a>

### `VEDIT_KEY_PGDN`

`macro` | [progs/vedit/vedit.c:178](../../progs/vedit/vedit.c#L178)

```c
#define VEDIT_KEY_PGDN
```

---

<a id="vedit_key_del"></a>

### `VEDIT_KEY_DEL`

`macro` | [progs/vedit/vedit.c:179](../../progs/vedit/vedit.c#L179)

```c
#define VEDIT_KEY_DEL
```

---

<a id="vedit_key_esc"></a>

### `VEDIT_KEY_ESC`

`macro` | [progs/vedit/vedit.c:180](../../progs/vedit/vedit.c#L180)

```c
#define VEDIT_KEY_ESC
```

---

<a id="vedit_nbuf"></a>

### `VEDIT_NBUF`

`macro` | [progs/vedit/vedit.c:251](../../progs/vedit/vedit.c#L251)

```c
#define VEDIT_NBUF
```

---- IDE (uemacs adoption): every new bound lives here, never inline ---

---

<a id="vedit_kill_n"></a>

### `VEDIT_KILL_N`

`macro` | [progs/vedit/vedit.c:252](../../progs/vedit/vedit.c#L252)

```c
#define VEDIT_KILL_N
```

---

<a id="vedit_kill_max"></a>

### `VEDIT_KILL_MAX`

`macro` | [progs/vedit/vedit.c:253](../../progs/vedit/vedit.c#L253)

```c
#define VEDIT_KILL_MAX
```

---

<a id="vedit_macro_max"></a>

### `VEDIT_MACRO_MAX`

`macro` | [progs/vedit/vedit.c:254](../../progs/vedit/vedit.c#L254)

```c
#define VEDIT_MACRO_MAX
```

---

<a id="vedit_hist_n"></a>

### `VEDIT_HIST_N`

`macro` | [progs/vedit/vedit.c:255](../../progs/vedit/vedit.c#L255)

```c
#define VEDIT_HIST_N
```

---

<a id="vedit_cmd_max"></a>

### `VEDIT_CMD_MAX`

`macro` | [progs/vedit/vedit.c:256](../../progs/vedit/vedit.c#L256)

```c
#define VEDIT_CMD_MAX
```

---

<a id="vedit_magic_max"></a>

### `VEDIT_MAGIC_MAX`

`macro` | [progs/vedit/vedit.c:257](../../progs/vedit/vedit.c#L257)

```c
#define VEDIT_MAGIC_MAX
```

---

<a id="vedit_key_meta"></a>

### `VEDIT_KEY_META`

`macro` | [progs/vedit/vedit.c:258](../../progs/vedit/vedit.c#L258)

```c
#define VEDIT_KEY_META(c)
```

---

<a id="vedit_key_arg"></a>

### `VEDIT_KEY_ARG`

`macro` | [progs/vedit/vedit.c:259](../../progs/vedit/vedit.c#L259)

```c
#define VEDIT_KEY_ARG
```

---

<a id="vedit_key_mark"></a>

### `VEDIT_KEY_MARK`

`macro` | [progs/vedit/vedit.c:260](../../progs/vedit/vedit.c#L260)

```c
#define VEDIT_KEY_MARK
```

---

<a id="vedit_key_kill_line"></a>

### `VEDIT_KEY_KILL_LINE`

`macro` | [progs/vedit/vedit.c:261](../../progs/vedit/vedit.c#L261)

```c
#define VEDIT_KEY_KILL_LINE
```

---

<a id="vedit_key_yank"></a>

### `VEDIT_KEY_YANK`

`macro` | [progs/vedit/vedit.c:262](../../progs/vedit/vedit.c#L262)

```c
#define VEDIT_KEY_YANK
```

---

<a id="vedit_key_transpose"></a>

### `VEDIT_KEY_TRANSPOSE`

`macro` | [progs/vedit/vedit.c:263](../../progs/vedit/vedit.c#L263)

```c
#define VEDIT_KEY_TRANSPOSE
```

---

<a id="vedit_key_fence"></a>

### `VEDIT_KEY_FENCE`

`macro` | [progs/vedit/vedit.c:264](../../progs/vedit/vedit.c#L264)

```c
#define VEDIT_KEY_FENCE
```

---

<a id="vedit_key_bol"></a>

### `VEDIT_KEY_BOL`

`macro` | [progs/vedit/vedit.c:265](../../progs/vedit/vedit.c#L265)

```c
#define VEDIT_KEY_BOL
```

---

<a id="vedit_key_eol"></a>

### `VEDIT_KEY_EOL`

`macro` | [progs/vedit/vedit.c:266](../../progs/vedit/vedit.c#L266)

```c
#define VEDIT_KEY_EOL
```

---

<a id="vedit_pool"></a>

### `vedit_pool`

`macro` | [progs/vedit/vedit.c:293](../../progs/vedit/vedit.c#L293)

```c
#define vedit_pool
```

---

<a id="vedit_used"></a>

### `vedit_used`

`macro` | [progs/vedit/vedit.c:294](../../progs/vedit/vedit.c#L294)

```c
#define vedit_used
```

---

<a id="vedit_count"></a>

### `vedit_count`

`macro` | [progs/vedit/vedit.c:295](../../progs/vedit/vedit.c#L295)

```c
#define vedit_count
```

---

<a id="vedit_cx"></a>

### `vedit_cx`

`macro` | [progs/vedit/vedit.c:296](../../progs/vedit/vedit.c#L296)

```c
#define vedit_cx
```

---

<a id="vedit_cy"></a>

### `vedit_cy`

`macro` | [progs/vedit/vedit.c:297](../../progs/vedit/vedit.c#L297)

```c
#define vedit_cy
```

---

<a id="vedit_top"></a>

### `vedit_top`

`macro` | [progs/vedit/vedit.c:298](../../progs/vedit/vedit.c#L298)

```c
#define vedit_top
```

---

<a id="vedit_hoff"></a>

### `vedit_hoff`

`macro` | [progs/vedit/vedit.c:299](../../progs/vedit/vedit.c#L299)

```c
#define vedit_hoff
```

---

<a id="vedit_dirty"></a>

### `vedit_dirty`

`macro` | [progs/vedit/vedit.c:300](../../progs/vedit/vedit.c#L300)

```c
#define vedit_dirty
```

---

<a id="vedit_trunc"></a>

### `vedit_trunc`

`macro` | [progs/vedit/vedit.c:301](../../progs/vedit/vedit.c#L301)

```c
#define vedit_trunc
```

---

<a id="vedit_lang"></a>

### `vedit_lang`

`macro` | [progs/vedit/vedit.c:302](../../progs/vedit/vedit.c#L302)

```c
#define vedit_lang
```

---

<a id="vedit_fname"></a>

### `vedit_fname`

`macro` | [progs/vedit/vedit.c:303](../../progs/vedit/vedit.c#L303)

```c
#define vedit_fname
```

---

<a id="vedit_msg"></a>

### `vedit_msg`

`macro` | [progs/vedit/vedit.c:304](../../progs/vedit/vedit.c#L304)

```c
#define vedit_msg
```

---

<a id="vedit_prompt_find"></a>

### `VEDIT_PROMPT_FIND`

`macro` | [progs/vedit/vedit.c:313](../../progs/vedit/vedit.c#L313)

```c
#define VEDIT_PROMPT_FIND
```

---

<a id="vedit_prompt_goto"></a>

### `VEDIT_PROMPT_GOTO`

`macro` | [progs/vedit/vedit.c:314](../../progs/vedit/vedit.c#L314)

```c
#define VEDIT_PROMPT_GOTO
```

---

<a id="vedit_prompt_name"></a>

### `VEDIT_PROMPT_NAME`

`macro` | [progs/vedit/vedit.c:315](../../progs/vedit/vedit.c#L315)

```c
#define VEDIT_PROMPT_NAME
```

---

<a id="vedit_prompt_link"></a>

### `VEDIT_PROMPT_LINK`

`macro` | [progs/vedit/vedit.c:316](../../progs/vedit/vedit.c#L316)

```c
#define VEDIT_PROMPT_LINK
```

---

<a id="vedit_prompt_cmd"></a>

### `VEDIT_PROMPT_CMD`

`macro` | [progs/vedit/vedit.c:317](../../progs/vedit/vedit.c#L317)

```c
#define VEDIT_PROMPT_CMD
```

---

<a id="vedit_prompt_isearch_f"></a>

### `VEDIT_PROMPT_ISEARCH_F`

`macro` | [progs/vedit/vedit.c:318](../../progs/vedit/vedit.c#L318)

```c
#define VEDIT_PROMPT_ISEARCH_F
```

---

<a id="vedit_prompt_isearch_r"></a>

### `VEDIT_PROMPT_ISEARCH_R`

`macro` | [progs/vedit/vedit.c:319](../../progs/vedit/vedit.c#L319)

```c
#define VEDIT_PROMPT_ISEARCH_R
```

---

<a id="vedit_prompt_rep_old"></a>

### `VEDIT_PROMPT_REP_OLD`

`macro` | [progs/vedit/vedit.c:320](../../progs/vedit/vedit.c#L320)

```c
#define VEDIT_PROMPT_REP_OLD
```

---

<a id="vedit_prompt_rep_new"></a>

### `VEDIT_PROMPT_REP_NEW`

`macro` | [progs/vedit/vedit.c:321](../../progs/vedit/vedit.c#L321)

```c
#define VEDIT_PROMPT_REP_NEW
```

---

<a id="vedit_prompt_qrep"></a>

### `VEDIT_PROMPT_QREP`

`macro` | [progs/vedit/vedit.c:322](../../progs/vedit/vedit.c#L322)

```c
#define VEDIT_PROMPT_QREP
```

---

<a id="vedit_prompt_shellcmd"></a>

### `VEDIT_PROMPT_SHELLCMD`

`macro` | [progs/vedit/vedit.c:323](../../progs/vedit/vedit.c#L323)

```c
#define VEDIT_PROMPT_SHELLCMD
```

---

<a id="vedit_prompt_filter"></a>

### `VEDIT_PROMPT_FILTER`

`macro` | [progs/vedit/vedit.c:324](../../progs/vedit/vedit.c#L324)

```c
#define VEDIT_PROMPT_FILTER
```

---

<a id="vedit_prompt_select"></a>

### `VEDIT_PROMPT_SELECT`

`macro` | [progs/vedit/vedit.c:325](../../progs/vedit/vedit.c#L325)

```c
#define VEDIT_PROMPT_SELECT
```

---

<a id="vedit_prompt_grep"></a>

### `VEDIT_PROMPT_GREP`

`macro` | [progs/vedit/vedit.c:326](../../progs/vedit/vedit.c#L326)

```c
#define VEDIT_PROMPT_GREP
```

---

<a id="vedit_prompt_bindkey"></a>

### `VEDIT_PROMPT_BINDKEY`

`macro` | [progs/vedit/vedit.c:327](../../progs/vedit/vedit.c#L327)

```c
#define VEDIT_PROMPT_BINDKEY
```

---

<a id="vedit_prompt_bindcmd"></a>

### `VEDIT_PROMPT_BINDCMD`

`macro` | [progs/vedit/vedit.c:328](../../progs/vedit/vedit.c#L328)

```c
#define VEDIT_PROMPT_BINDCMD
```

---

<a id="vedit_fill_col"></a>

### `VEDIT_FILL_COL`

`macro` | [progs/vedit/vedit.c:1612](../../progs/vedit/vedit.c#L1612)

```c
#define VEDIT_FILL_COL
```

---- uemacs F2: magic search, isearch, replace, fill ----

---

<a id="vedit_tmp_out"></a>

### `VEDIT_TMP_OUT`

`macro` | [progs/vedit/vedit.c:3273](../../progs/vedit/vedit.c#L3273)

```c
#define VEDIT_TMP_OUT
```

---- uemacs F5: shell capture, filter, grep (spawn.c + IDE) ----

---

<a id="vedit_tmp_in"></a>

### `VEDIT_TMP_IN`

`macro` | [progs/vedit/vedit.c:3274](../../progs/vedit/vedit.c#L3274)

```c
#define VEDIT_TMP_IN
```

---

<a id="vedit_tmp_f"></a>

### `VEDIT_TMP_F`

`macro` | [progs/vedit/vedit.c:3275](../../progs/vedit/vedit.c#L3275)

```c
#define VEDIT_TMP_F
```

---

<a id="vedit_sh_args"></a>

### `VEDIT_SH_ARGS`

`macro` | [progs/vedit/vedit.c:3276](../../progs/vedit/vedit.c#L3276)

```c
#define VEDIT_SH_ARGS
```

---

<a id="vedit_sh_line"></a>

### `VEDIT_SH_LINE`

`macro` | [progs/vedit/vedit.c:3277](../../progs/vedit/vedit.c#L3277)

```c
#define VEDIT_SH_LINE
```

---

<a id="vedit_clip_max"></a>

### `VEDIT_CLIP_MAX`

`macro` | [progs/vedit/vedit.c:3278](../../progs/vedit/vedit.c#L3278)

```c
#define VEDIT_CLIP_MAX
```

---
