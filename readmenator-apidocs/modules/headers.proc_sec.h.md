# `headers/proc_sec.h`

> Source: [headers/proc_sec.h:1](../../headers/proc_sec.h#L1) | language `h` | coverage 50.0% | [API index](../index.md)

Docstring: proc_sec.h -- per-process security state behind the Linux

## Contents

- **Functions:** [`proc_sec_inherit`](#proc_sec_inherit), [`proc_sec_release`](#proc_sec_release), [`proc_sec_exec`](#proc_sec_exec), [`proc_sec_set_exe`](#proc_sec_set_exe), [`proc_sec_exe`](#proc_sec_exe), [`it`](#it), [`proc_sec_filter`](#proc_sec_filter), [`proc_sec_prctl`](#proc_sec_prctl), [`proc_sec_seccomp`](#proc_sec_seccomp)
- **Macros:** [`SECCOMP_FILTERS_MAX`](#seccomp_filters_max), [`SECCOMP_KILL_EXIT`](#seccomp_kill_exit)

## Functions

<a id="proc_sec_inherit"></a>

### `proc_sec_inherit`

`function` | [headers/proc_sec.h:23](../../headers/proc_sec.h#L23)

```c
void proc_sec_inherit(int child, int parent);
```

Lifecycle (callers hold sched_lock where noted in sched.c).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `child` | `int` |  |  |
| `parent` | `int` |  |  |

*Called by:* [`do_fork_ex`](kernel.sched.c.md#do_fork_ex), [`do_thread_spawn`](kernel.sched.c.md#do_thread_spawn)

---

<a id="proc_sec_release"></a>

### `proc_sec_release`

`function` | [headers/proc_sec.h:24](../../headers/proc_sec.h#L24)

```c
void proc_sec_release(int pid);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pid` | `int` |  |  |

*Called by:* [`ETREL_CHILD_STACK_SZ`](kernel.exec.c.md#etrel_child_stack_sz)

---

<a id="proc_sec_exec"></a>

### `proc_sec_exec`

`function` | [headers/proc_sec.h:25](../../headers/proc_sec.h#L25)

```c
void proc_sec_exec(int pid);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pid` | `int` |  |  |

*Called by:* [`do_execve`](kernel.sched.c.md#do_execve)

---

<a id="proc_sec_set_exe"></a>

### `proc_sec_set_exe`

`function` | [headers/proc_sec.h:26](../../headers/proc_sec.h#L26)

```c
void proc_sec_set_exe(int pid, const char *resolved);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pid` | `int` |  |  |
| `resolved` | `char *` |  |  |

*Called by:* [`do_execve`](kernel.sched.c.md#do_execve)

---

<a id="proc_sec_exe"></a>

### `proc_sec_exe`

`function` `const` | [headers/proc_sec.h:28](../../headers/proc_sec.h#L28)

```c
const char *proc_sec_exe(int pid);
```

Resolved image path of pid ("" when unknown).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pid` | `int` |  |  |

**Returns:** `char *`

*Called by:* [`PROC_SELF_EXE`](kernel.syscalls.c.md#proc_self_exe), [`sys_linux_execve`](kernel.syscalls_proc.c.md#sys_linux_execve)

---

<a id="it"></a>

### `it`

`function` | [headers/proc_sec.h:31](../../headers/proc_sec.h#L31)

```c
* the syscall must answer in *ret when a filter decided it (ERRNO, TRACE, * USER_NOTIF);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `USER_NOTIF` |  |  |  |

**Returns:** `* the syscall must answer in *ret when a filter decided`

---

<a id="proc_sec_filter"></a>

### `proc_sec_filter`

`function` | [headers/proc_sec.h:34](../../headers/proc_sec.h#L34)

```c
int proc_sec_filter(long n, long a1, long a2, long a3, long a4, long a5, long a6, long *ret);
```

Run the caller's filters for syscall n.

Returns 1 and stores the value the syscall must answer in *ret when a filter decided it (ERRNO, TRACE, USER_NOTIF); kills the caller for KILL and TRAP; returns 0 to let the syscall run.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `n` | `long` |  |  |
| `a1` | `long` |  |  |
| `a2` | `long` |  |  |
| `a3` | `long` |  |  |
| `a4` | `long` |  |  |
| `a5` | `long` |  |  |
| `a6` | `long` |  |  |
| `ret` | `long *` |  |  |

**Returns:** `int`

---

<a id="proc_sec_prctl"></a>

### `proc_sec_prctl`

`function` | [headers/proc_sec.h:36](../../headers/proc_sec.h#L36)

```c
long proc_sec_prctl(long option, long a2, long a3, long a4, long a5);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `option` | `long` |  |  |
| `a2` | `long` |  |  |
| `a3` | `long` |  |  |
| `a4` | `long` |  |  |
| `a5` | `long` |  |  |

**Returns:** `long`

---

<a id="proc_sec_seccomp"></a>

### `proc_sec_seccomp`

`function` | [headers/proc_sec.h:37](../../headers/proc_sec.h#L37)

```c
long proc_sec_seccomp(long op, long flags, long uargs);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `op` | `long` |  |  |
| `flags` | `long` |  |  |
| `uargs` | `long` |  |  |

**Returns:** `long`

---

## Macros

<a id="seccomp_filters_max"></a>

### `SECCOMP_FILTERS_MAX`

`macro` | [headers/proc_sec.h:16](../../headers/proc_sec.h#L16)

```c
#define SECCOMP_FILTERS_MAX
```

Stacked filters per process and instructions per filter.

---

<a id="seccomp_kill_exit"></a>

### `SECCOMP_KILL_EXIT`

`macro` | [headers/proc_sec.h:20](../../headers/proc_sec.h#L20)

```c
#define SECCOMP_KILL_EXIT
```

Exit code of a process or thread a filter kills: a death by SIGSYS (31), recorded negative like every MiniOS signal death, so wait4 reports WIFSIGNALED with WTERMSIG == SIGSYS.

---
