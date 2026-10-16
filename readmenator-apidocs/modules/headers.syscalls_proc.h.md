# `headers/syscalls_proc.h`

> Source: [headers/syscalls_proc.h:1](../../headers/syscalls_proc.h#L1) | language `h` | coverage 20.0% | [API index](../index.md)

syscalls_proc.h -- process-management syscall handlers shared with the

## Contents

- **Functions:** [`dispatcher`](#dispatcher), [`sys_minios_nice`](#sys_minios_nice), [`sys_minios_clone`](#sys_minios_clone), [`sys_minios_thread_spawn`](#sys_minios_thread_spawn), [`sys_linux_yield`](#sys_linux_yield), [`sys_linux_getpid`](#sys_linux_getpid), [`sys_linux_gettid`](#sys_linux_gettid), [`sys_linux_fork`](#sys_linux_fork), [`sys_linux_clone`](#sys_linux_clone), [`sys_linux_vfork`](#sys_linux_vfork), [`sys_linux_execve`](#sys_linux_execve), [`sys_linux_exit`](#sys_linux_exit), [`sys_linux_wait4`](#sys_linux_wait4), [`sys_linux_kill`](#sys_linux_kill), [`linux_signal_fatal`](#linux_signal_fatal), [`do_proc_exit`](#do_proc_exit)
- **Macros:** [`LINUX_SIGNAL_MAX`](#linux_signal_max), [`LINUX_SIGNAL_EXIT_BASE`](#linux_signal_exit_base), [`LINUX_EXIT_STATUS_MASK`](#linux_exit_status_mask)

## Functions

<a id="dispatcher"></a>

### `dispatcher`

`function` | [headers/syscalls_proc.h:5](../../headers/syscalls_proc.h#L5)

```c
* dispatcher (kernel/syscalls.c). These handlers touch only scheduler * state (current_pid, procs[], do_* / seccomp_* / yield) plus the * kernel-wide user_range_ok validator, so they live in their own
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `kernel/syscalls.` |  |  |

**Returns:** `*`

---

<a id="sys_minios_nice"></a>

### `sys_minios_nice`

`function` | [headers/syscalls_proc.h:12](../../headers/syscalls_proc.h#L12)

```c
long sys_minios_nice(long a1, long a2, long a3, long a4, long a5, long a6);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a1` | `long` |  |  |
| `a2` | `long` |  |  |
| `a3` | `long` |  |  |
| `a4` | `long` |  |  |
| `a5` | `long` |  |  |
| `a6` | `long` |  |  |

**Returns:** `long`

---

<a id="sys_minios_clone"></a>

### `sys_minios_clone`

`function` | [headers/syscalls_proc.h:13](../../headers/syscalls_proc.h#L13)

```c
long sys_minios_clone(long flags, long newsp, long a3, long a4, long a5, long a6);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `flags` | `long` |  |  |
| `newsp` | `long` |  |  |
| `a3` | `long` |  |  |
| `a4` | `long` |  |  |
| `a5` | `long` |  |  |
| `a6` | `long` |  |  |

**Returns:** `long`

---

<a id="sys_minios_thread_spawn"></a>

### `sys_minios_thread_spawn`

`function` | [headers/syscalls_proc.h:14](../../headers/syscalls_proc.h#L14)

```c
long sys_minios_thread_spawn(long a1, long a2, long a3, long a4, long a5, long a6);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a1` | `long` |  |  |
| `a2` | `long` |  |  |
| `a3` | `long` |  |  |
| `a4` | `long` |  |  |
| `a5` | `long` |  |  |
| `a6` | `long` |  |  |

**Returns:** `long`

---

<a id="sys_linux_yield"></a>

### `sys_linux_yield`

`function` | [headers/syscalls_proc.h:15](../../headers/syscalls_proc.h#L15)

```c
long sys_linux_yield(long a1, long a2, long a3, long a4, long a5, long a6);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a1` | `long` |  |  |
| `a2` | `long` |  |  |
| `a3` | `long` |  |  |
| `a4` | `long` |  |  |
| `a5` | `long` |  |  |
| `a6` | `long` |  |  |

**Returns:** `long`

---

<a id="sys_linux_getpid"></a>

### `sys_linux_getpid`

`function` | [headers/syscalls_proc.h:16](../../headers/syscalls_proc.h#L16)

```c
long sys_linux_getpid(long a1, long a2, long a3, long a4, long a5, long a6);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a1` | `long` |  |  |
| `a2` | `long` |  |  |
| `a3` | `long` |  |  |
| `a4` | `long` |  |  |
| `a5` | `long` |  |  |
| `a6` | `long` |  |  |

**Returns:** `long`

---

<a id="sys_linux_gettid"></a>

### `sys_linux_gettid`

`function` | [headers/syscalls_proc.h:17](../../headers/syscalls_proc.h#L17)

```c
long sys_linux_gettid(long a1, long a2, long a3, long a4, long a5, long a6);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a1` | `long` |  |  |
| `a2` | `long` |  |  |
| `a3` | `long` |  |  |
| `a4` | `long` |  |  |
| `a5` | `long` |  |  |
| `a6` | `long` |  |  |

**Returns:** `long`

---

<a id="sys_linux_fork"></a>

### `sys_linux_fork`

`function` | [headers/syscalls_proc.h:18](../../headers/syscalls_proc.h#L18)

```c
long sys_linux_fork(long a1, long a2, long a3, long a4, long a5, long a6);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a1` | `long` |  |  |
| `a2` | `long` |  |  |
| `a3` | `long` |  |  |
| `a4` | `long` |  |  |
| `a5` | `long` |  |  |
| `a6` | `long` |  |  |

**Returns:** `long`

---

<a id="sys_linux_clone"></a>

### `sys_linux_clone`

`function` | [headers/syscalls_proc.h:19](../../headers/syscalls_proc.h#L19)

```c
long sys_linux_clone(long a1, long a2, long a3, long a4, long a5, long a6);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a1` | `long` |  |  |
| `a2` | `long` |  |  |
| `a3` | `long` |  |  |
| `a4` | `long` |  |  |
| `a5` | `long` |  |  |
| `a6` | `long` |  |  |

**Returns:** `long`

---

<a id="sys_linux_vfork"></a>

### `sys_linux_vfork`

`function` | [headers/syscalls_proc.h:20](../../headers/syscalls_proc.h#L20)

```c
long sys_linux_vfork(long a1, long a2, long a3, long a4, long a5, long a6);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a1` | `long` |  |  |
| `a2` | `long` |  |  |
| `a3` | `long` |  |  |
| `a4` | `long` |  |  |
| `a5` | `long` |  |  |
| `a6` | `long` |  |  |

**Returns:** `long`

---

<a id="sys_linux_execve"></a>

### `sys_linux_execve`

`function` | [headers/syscalls_proc.h:21](../../headers/syscalls_proc.h#L21)

```c
long sys_linux_execve(long a1, long a2, long a3, long a4, long a5, long a6);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a1` | `long` |  |  |
| `a2` | `long` |  |  |
| `a3` | `long` |  |  |
| `a4` | `long` |  |  |
| `a5` | `long` |  |  |
| `a6` | `long` |  |  |

**Returns:** `long`

---

<a id="sys_linux_exit"></a>

### `sys_linux_exit`

`function` | [headers/syscalls_proc.h:22](../../headers/syscalls_proc.h#L22)

```c
long sys_linux_exit(long a1, long a2, long a3, long a4, long a5, long a6);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a1` | `long` |  |  |
| `a2` | `long` |  |  |
| `a3` | `long` |  |  |
| `a4` | `long` |  |  |
| `a5` | `long` |  |  |
| `a6` | `long` |  |  |

**Returns:** `long`

---

<a id="sys_linux_wait4"></a>

### `sys_linux_wait4`

`function` | [headers/syscalls_proc.h:23](../../headers/syscalls_proc.h#L23)

```c
long sys_linux_wait4(long a1, long a2, long a3, long a4, long a5, long a6);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a1` | `long` |  |  |
| `a2` | `long` |  |  |
| `a3` | `long` |  |  |
| `a4` | `long` |  |  |
| `a5` | `long` |  |  |
| `a6` | `long` |  |  |

**Returns:** `long`

*Called by:* [`groups`](kernel.syscalls_proc.c.md#groups)

---

<a id="sys_linux_kill"></a>

### `sys_linux_kill`

`function` | [headers/syscalls_proc.h:24](../../headers/syscalls_proc.h#L24)

```c
long sys_linux_kill(long a1, long a2, long a3, long a4, long a5, long a6);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a1` | `long` |  |  |
| `a2` | `long` |  |  |
| `a3` | `long` |  |  |
| `a4` | `long` |  |  |
| `a5` | `long` |  |  |
| `a6` | `long` |  |  |

**Returns:** `long`

---

<a id="linux_signal_fatal"></a>

### `linux_signal_fatal`

`function` | [headers/syscalls_proc.h:31](../../headers/syscalls_proc.h#L31)

```c
int linux_signal_fatal(long sig);
```

Linux signal numbers 1..LINUX_SIGNAL_MAX; a fatal one ends its target. * The foreground shell reports a signal death as exit code 128 + sig. define LINUX_SIGNAL_MAX       64 define LINUX_SIGNAL_EXIT_BASE 128 define LINUX_EXIT_STATUS_MASK 0xff

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `sig` | `long` |  |  |

**Returns:** `int`

*Called by:* [`sys_linux_kill`](kernel.syscalls_proc.c.md#sys_linux_kill)

---

<a id="do_proc_exit"></a>

### `do_proc_exit`

`function` | [headers/syscalls_proc.h:34](../../headers/syscalls_proc.h#L34)

```c
long do_proc_exit(long code);
```

Shared exit path for sys_linux_exit and the exit_group fall-through.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `code` | `long` |  |  |

**Returns:** `long`

*Called by:* [`sys_linux_exit`](kernel.syscalls_proc.c.md#sys_linux_exit)

---

## Macros

<a id="linux_signal_max"></a>

### `LINUX_SIGNAL_MAX`

`macro` | [headers/syscalls_proc.h:28](../../headers/syscalls_proc.h#L28)

```c
#define LINUX_SIGNAL_MAX
```

Linux signal numbers 1..LINUX_SIGNAL_MAX; a fatal one ends its target.

The foreground shell reports a signal death as exit code 128 + sig.

---

<a id="linux_signal_exit_base"></a>

### `LINUX_SIGNAL_EXIT_BASE`

`macro` | [headers/syscalls_proc.h:29](../../headers/syscalls_proc.h#L29)

```c
#define LINUX_SIGNAL_EXIT_BASE
```

---

<a id="linux_exit_status_mask"></a>

### `LINUX_EXIT_STATUS_MASK`

`macro` | [headers/syscalls_proc.h:30](../../headers/syscalls_proc.h#L30)

```c
#define LINUX_EXIT_STATUS_MASK
```

---
