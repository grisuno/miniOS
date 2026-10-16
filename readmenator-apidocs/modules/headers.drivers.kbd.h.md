# `headers/drivers/kbd.h`

> Source: [headers/drivers/kbd.h:1](../../headers/drivers/kbd.h#L1) | language `h` | coverage 25.0% | [API index](../index.md)

## Contents

- **Functions:** [`kbd_available`](#kbd_available), [`kbd_read`](#kbd_read), [`kbd_feed_scancode`](#kbd_feed_scancode), [`kbd_reset_for_shell`](#kbd_reset_for_shell), [`kbd_get_layout`](#kbd_get_layout), [`kbd_set_layout`](#kbd_set_layout), [`kbd_toggle_layout`](#kbd_toggle_layout), [`kbd_q_empty`](#kbd_q_empty), [`kbd_q_pop`](#kbd_q_pop), [`kbd_q_push`](#kbd_q_push), [`kbd_drop_counts`](#kbd_drop_counts), [`kbd_raw_mode_get`](#kbd_raw_mode_get), [`kbd_raw_mode_set`](#kbd_raw_mode_set), [`kbd_raw_empty`](#kbd_raw_empty), [`kbd_raw_pop`](#kbd_raw_pop), [`kbd_raw_push_byte`](#kbd_raw_push_byte), [`kbd_e0_get`](#kbd_e0_get), [`kbd_e0_set`](#kbd_e0_set), [`kbd_flush_all`](#kbd_flush_all), [`kbd_raw_flush`](#kbd_raw_flush), [`kbd_sys_raw_filter`](#kbd_sys_raw_filter)
- **Macros:** [`KBD_LAYOUT_EN`](#kbd_layout_en), [`KBD_LAYOUT_ES`](#kbd_layout_es)

## Functions

<a id="kbd_available"></a>

### `kbd_available`

`function` | [headers/drivers/kbd.h:9](../../headers/drivers/kbd.h#L9)

```c
int kbd_available(void);
```

**Returns:** `int`

---

<a id="kbd_read"></a>

### `kbd_read`

`function` | [headers/drivers/kbd.h:10](../../headers/drivers/kbd.h#L10)

```c
int kbd_read(void);
```

**Returns:** `int`

*Called by:* [`console_job_try`](kernel.console_in.c.md#console_job_try)

---

<a id="kbd_feed_scancode"></a>

### `kbd_feed_scancode`

`function` | [headers/drivers/kbd.h:11](../../headers/drivers/kbd.h#L11)

```c
int kbd_feed_scancode(unsigned char sc);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `sc` | `unsigned char` |  |  |

**Returns:** `int`

*Called by:* [`kbd_read`](drivers.kbd.c.md#kbd_read), [`key`](drivers.kbd.c.md#key), [`usbhid_press_kbd_report`](drivers.usbhid.c.md#usbhid_press_kbd_report)

---

<a id="kbd_reset_for_shell"></a>

### `kbd_reset_for_shell`

`function` | [headers/drivers/kbd.h:12](../../headers/drivers/kbd.h#L12)

```c
void kbd_reset_for_shell(void);
```

*Called by:* [`ETREL_CHILD_STACK_SZ`](kernel.exec.c.md#etrel_child_stack_sz), [`k_run_rel`](kernel.exec.c.md#k_run_rel)

---

<a id="kbd_get_layout"></a>

### `kbd_get_layout`

`function` | [headers/drivers/kbd.h:15](../../headers/drivers/kbd.h#L15)

```c
int kbd_get_layout(void);
```

Layout selection

**Returns:** `int`

---

<a id="kbd_set_layout"></a>

### `kbd_set_layout`

`function` | [headers/drivers/kbd.h:16](../../headers/drivers/kbd.h#L16)

```c
void kbd_set_layout(int layout);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `layout` | `int` |  |  |

---

<a id="kbd_toggle_layout"></a>

### `kbd_toggle_layout`

`function` | [headers/drivers/kbd.h:17](../../headers/drivers/kbd.h#L17)

```c
void kbd_toggle_layout(void);
```

---

<a id="kbd_q_empty"></a>

### `kbd_q_empty`

`function` | [headers/drivers/kbd.h:27](../../headers/drivers/kbd.h#L27)

```c
int kbd_q_empty(void);
```

Translated queue (shell input)

**Returns:** `int`

---

<a id="kbd_q_pop"></a>

### `kbd_q_pop`

`function` | [headers/drivers/kbd.h:28](../../headers/drivers/kbd.h#L28)

```c
int kbd_q_pop(void);
```

**Returns:** `int`

---

<a id="kbd_q_push"></a>

### `kbd_q_push`

`function` | [headers/drivers/kbd.h:29](../../headers/drivers/kbd.h#L29)

```c
void kbd_q_push(unsigned char c);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `unsigned char` |  |  |

*Called by:* [`usbhid_press_kbd_report`](drivers.usbhid.c.md#usbhid_press_kbd_report)

---

<a id="kbd_drop_counts"></a>

### `kbd_drop_counts`

`function` | [headers/drivers/kbd.h:32](../../headers/drivers/kbd.h#L32)

```c
void kbd_drop_counts(unsigned long *cooked, unsigned long *raw);
```

Docstring: Drop counters for full cooked and raw queues.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `cooked` | `unsigned long *` |  |  |
| `raw` | `unsigned long *` |  |  |

---

<a id="kbd_raw_mode_get"></a>

### `kbd_raw_mode_get`

`function` | [headers/drivers/kbd.h:35](../../headers/drivers/kbd.h#L35)

```c
int kbd_raw_mode_get(void);
```

Raw queue (DOOM / SYS_KBD)

**Returns:** `int`

---

<a id="kbd_raw_mode_set"></a>

### `kbd_raw_mode_set`

`function` | [headers/drivers/kbd.h:36](../../headers/drivers/kbd.h#L36)

```c
void kbd_raw_mode_set(int on);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `on` | `int` |  |  |

---

<a id="kbd_raw_empty"></a>

### `kbd_raw_empty`

`function` | [headers/drivers/kbd.h:37](../../headers/drivers/kbd.h#L37)

```c
int kbd_raw_empty(void);
```

**Returns:** `int`

---

<a id="kbd_raw_pop"></a>

### `kbd_raw_pop`

`function` | [headers/drivers/kbd.h:38](../../headers/drivers/kbd.h#L38)

```c
int kbd_raw_pop(void);
```

**Returns:** `int`

---

<a id="kbd_raw_push_byte"></a>

### `kbd_raw_push_byte`

`function` | [headers/drivers/kbd.h:39](../../headers/drivers/kbd.h#L39)

```c
void kbd_raw_push_byte(unsigned char c);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `unsigned char` |  |  |

---

<a id="kbd_e0_get"></a>

### `kbd_e0_get`

`function` | [headers/drivers/kbd.h:40](../../headers/drivers/kbd.h#L40)

```c
int kbd_e0_get(void);
```

**Returns:** `int`

---

<a id="kbd_e0_set"></a>

### `kbd_e0_set`

`function` | [headers/drivers/kbd.h:41](../../headers/drivers/kbd.h#L41)

```c
void kbd_e0_set(int v);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `v` | `int` |  |  |

---

<a id="kbd_flush_all"></a>

### `kbd_flush_all`

`function` | [headers/drivers/kbd.h:42](../../headers/drivers/kbd.h#L42)

```c
void kbd_flush_all(void);
```

---

<a id="kbd_raw_flush"></a>

### `kbd_raw_flush`

`function` | [headers/drivers/kbd.h:43](../../headers/drivers/kbd.h#L43)

```c
void kbd_raw_flush(void);
```

*Called by:* [`app`](kernel.vga_fb.c.md#app), [`vga_fb_focus_id`](kernel.vga_fb.c.md#vga_fb_focus_id), [`vga_fb_focus_next`](kernel.vga_fb.c.md#vga_fb_focus_next)

---

<a id="kbd_sys_raw_filter"></a>

### `kbd_sys_raw_filter`

`function` | [headers/drivers/kbd.h:50](../../headers/drivers/kbd.h#L50)

```c
int kbd_sys_raw_filter(unsigned char sc);
```

Raw-path WM filter for the SYS_KBD direct-port read (DOOM/Quake/Nuklear read scancodes one byte per syscall, bypassing kbd_read): tracks E0 and modifiers, performs Alt+Tab / Super+Tab / Super+arrows / Alt+Enter,M,X,Q and swallows the consumed bytes.

Returns 1 when sc must not reach the app. Declared here so kernel/syscalls.c shares the one implementation.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `sc` | `unsigned char` |  |  |

**Returns:** `int`

*Called by:* [`bare`](drivers.kbd.c.md#bare)

---

## Macros

<a id="kbd_layout_en"></a>

### `KBD_LAYOUT_EN`

`macro` | [headers/drivers/kbd.h:6](../../headers/drivers/kbd.h#L6)

```c
#define KBD_LAYOUT_EN
```

Keyboard layout: US qwerty (default) or Spanish (Spain) qwerty.

Toggled from the taskbar widget or the `kbd` shell builtin.

---

<a id="kbd_layout_es"></a>

### `KBD_LAYOUT_ES`

`macro` | [headers/drivers/kbd.h:7](../../headers/drivers/kbd.h#L7)

```c
#define KBD_LAYOUT_ES
```

---
