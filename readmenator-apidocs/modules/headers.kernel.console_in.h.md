# `headers/kernel/console_in.h`

> Source: [headers/kernel/console_in.h:1](../../headers/kernel/console_in.h#L1) | language `h` | coverage 58.3% | [API index](../index.md)

Docstring: console_in.h -- boundary of the console input device

## Contents

- **Functions:** [`Consumers`](#consumers), [`console_history_page`](#console_history_page), [`console_peek`](#console_peek), [`console_raw_try`](#console_raw_try), [`console_raw_get`](#console_raw_get), [`console_job_try`](#console_job_try), [`console_job_get`](#console_job_get), [`console_ungetc`](#console_ungetc), [`console_stdin_push`](#console_stdin_push), [`console_stdin_clear`](#console_stdin_clear), [`console_stdin_active`](#console_stdin_active)

## Functions

<a id="consumers"></a>

### `Consumers`

`function` | [headers/kernel/console_in.h:7](../../headers/kernel/console_in.h#L7)

```c
* Consumers (shell prompt, editor, SPAWN waits, GETC_RAW syscall) include * this header instead of reaching into kernel/shell.c. */ #include "kernel.h" /** Docstring: Blocking read from PS/2 or COM1 w
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `prompt` | `shell` |  |  |
| `waits` | `SPAWN` |  |  |
| `syscall` | `GETC_RAW` |  |  |

**Returns:** `*`

---

<a id="console_history_page"></a>

### `console_history_page`

`function` | [headers/kernel/console_in.h:19](../../headers/kernel/console_in.h#L19)

```c
void console_history_page(int dir);
```

Docstring: Page the console history by one screen (dir -1 up, +1 down).

The framebuffer terminal keeps its own logical ring and the text-mode console the legacy VGA scrollback ring; this picks the one that is up.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `dir` | `int` |  |  |

---

<a id="console_peek"></a>

### `console_peek`

`function` | [headers/kernel/console_in.h:22](../../headers/kernel/console_in.h#L22)

```c
int console_peek(void);
```

Docstring: Next buffered byte without consuming it, or -1.

**Returns:** `int`

*Called by:* [`code`](kernel.shell.c.md#code)

---

<a id="console_raw_try"></a>

### `console_raw_try`

`function` | [headers/kernel/console_in.h:26](../../headers/kernel/console_in.h#L26)

```c
int console_raw_try(void);
```

Docstring: Raw console multiplexer backing GETC_RAW: same sources, no line buffering, echo or scrollback. try returns -1 when idle.

**Returns:** `int`

---

<a id="console_raw_get"></a>

### `console_raw_get`

`function` | [headers/kernel/console_in.h:27](../../headers/kernel/console_in.h#L27)

```c
int console_raw_get(void);
```

**Returns:** `int`

---

<a id="console_job_try"></a>

### `console_job_try`

`function` | [headers/kernel/console_in.h:30](../../headers/kernel/console_in.h#L30)

```c
int console_job_try(void);
```

Docstring: PS/2-only GETC_RAW source for background jobs.

**Returns:** `int`

---

<a id="console_job_get"></a>

### `console_job_get`

`function` | [headers/kernel/console_in.h:31](../../headers/kernel/console_in.h#L31)

```c
int console_job_get(void);
```

**Returns:** `int`

---

<a id="console_ungetc"></a>

### `console_ungetc`

`function` | [headers/kernel/console_in.h:35](../../headers/kernel/console_in.h#L35)

```c
void console_ungetc(unsigned char c);
```

Docstring: Push one byte back into the console FIFO; the next console_getc/console_peek serves it first.

Drops the byte when full.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `unsigned char` |  |  |

---

<a id="console_stdin_push"></a>

### `console_stdin_push`

`function` | [headers/kernel/console_in.h:42](../../headers/kernel/console_in.h#L42)

```c
int console_stdin_push(const char *data, unsigned long len);
```

Docstring: Pipeline stdin override: the next console_getc calls serve len bytes from data, then report EOF (-1) instead of blocking on the live console until console_stdin_clear runs.

The shell pipeline runner owns this: stage N+1 reads stage N's captured output as its stdin. Bounded by PIPE_CAP_MAX, fail-closed (0) past it or on OOM.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `data` | `char *` |  |  |
| `len` | `unsigned long` |  |  |

**Returns:** `int`

---

<a id="console_stdin_clear"></a>

### `console_stdin_clear`

`function` | [headers/kernel/console_in.h:43](../../headers/kernel/console_in.h#L43)

```c
void console_stdin_clear(void);
```

---

<a id="console_stdin_active"></a>

### `console_stdin_active`

`function` | [headers/kernel/console_in.h:44](../../headers/kernel/console_in.h#L44)

```c
int console_stdin_active(void);
```

**Returns:** `int`

*Called by:* [`shell_exec_builtin`](kernel.shell.c.md#shell_exec_builtin)

---
