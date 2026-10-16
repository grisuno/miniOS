# `kernel/klog.c`

> Source: [kernel/klog.c:1](../../kernel/klog.c#L1) | language `c` | coverage 14.3% | [API index](../index.md)

klog.c - Structured kernel logging with levels and subsystems.

## Contents

- **Functions:** [`klog_set_level`](#klog_set_level), [`klog_set_subsys_level`](#klog_set_subsys_level), [`klog_disable`](#klog_disable), [`klog_enable`](#klog_enable), [`klog`](#klog), [`klog_hexdump`](#klog_hexdump)

## Functions

<a id="klog_set_level"></a>

### `klog_set_level`

`function` | [kernel/klog.c:29](../../kernel/klog.c#L29)

```c
void klog_set_level(log_level_t level)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `level` | `log_level_t` |  |  |

---

<a id="klog_set_subsys_level"></a>

### `klog_set_subsys_level`

`function` | [kernel/klog.c:33](../../kernel/klog.c#L33)

```c
void klog_set_subsys_level(log_subsystem_t subsys, log_level_t level)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `subsys` | `log_subsystem_t` |  |  |
| `level` | `log_level_t` |  |  |

---

<a id="klog_disable"></a>

### `klog_disable`

`function` | [kernel/klog.c:38](../../kernel/klog.c#L38)

```c
void klog_disable(void)
```

---

<a id="klog_enable"></a>

### `klog_enable`

`function` | [kernel/klog.c:39](../../kernel/klog.c#L39)

```c
void klog_enable(void)
```

---

<a id="klog"></a>

### `klog`

`function` | [kernel/klog.c:41](../../kernel/klog.c#L41)

```c
void klog(log_level_t level, log_subsystem_t subsys, const char *fmt, ...)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `level` | `log_level_t` |  |  |
| `subsys` | `log_subsystem_t` |  |  |
| `fmt` | `char *` |  |  |
| `...` |  |  |  |

---

<a id="klog_hexdump"></a>

### `klog_hexdump`

`function` | [kernel/klog.c:119](../../kernel/klog.c#L119)

```c
void klog_hexdump(log_level_t level, log_subsystem_t subsys, const void *data, unsigned long len, const char *label)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `level` | `log_level_t` |  |  |
| `subsys` | `log_subsystem_t` |  |  |
| `data` | `void *` |  |  |
| `len` | `unsigned long` |  |  |
| `label` | `char *` |  |  |

---
