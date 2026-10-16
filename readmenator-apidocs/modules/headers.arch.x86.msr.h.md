# `headers/arch/x86/msr.h`

> Source: [headers/arch/x86/msr.h:1](../../headers/arch/x86/msr.h#L1) | language `h` | coverage 11.1% | [API index](../index.md)

Model-Specific Register access for x86-64.

## Contents

- **Functions:** [`wrmsr`](#wrmsr), [`rdmsr`](#rdmsr)
- **Macros:** [`MSR_STAR`](#msr_star), [`MSR_LSTAR`](#msr_lstar), [`MSR_SFMASK`](#msr_sfmask), [`MSR_FSBASE`](#msr_fsbase), [`MSR_GSBASE`](#msr_gsbase), [`MSR_KERNEL_GS_BASE`](#msr_kernel_gs_base)

## Functions

<a id="wrmsr"></a>

### `wrmsr`

`function` `inline` `static` | [headers/arch/x86/msr.h:8](../../headers/arch/x86/msr.h#L8)

```c
static inline void wrmsr(unsigned msr, unsigned long val)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `msr` | `unsigned` |  |  |
| `val` | `unsigned long` |  |  |

*Called by:* [`syscall_init`](kernel.c.md#syscall_init), [`ETREL_CHILD_STACK_SZ`](kernel.exec.c.md#etrel_child_stack_sz), [`k_user_fault_return`](kernel.exec.c.md#k_user_fault_return), [`mm_setup_protections`](kernel.mm.paging.c.md#mm_setup_protections), [`context`](kernel.sched.c.md#context), [`do_execve`](kernel.sched.c.md#do_execve), [`sched_init`](kernel.sched.c.md#sched_init), [`spawn_restore`](kernel.spawn.c.md#spawn_restore)

---

<a id="rdmsr"></a>

### `rdmsr`

`function` `inline` `static` | [headers/arch/x86/msr.h:13](../../headers/arch/x86/msr.h#L13)

```c
static inline unsigned long rdmsr(unsigned msr)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `msr` | `unsigned` |  |  |

**Returns:** `unsigned long`

*Called by:* [`syscall_init`](kernel.c.md#syscall_init), [`mm_setup_protections`](kernel.mm.paging.c.md#mm_setup_protections), [`do_fork_ex`](kernel.sched.c.md#do_fork_ex), [`isr_dispatch`](kernel.sched.c.md#isr_dispatch), [`point`](kernel.sched.c.md#point), [`spawn_backup`](kernel.spawn.c.md#spawn_backup)

---

## Macros

<a id="msr_star"></a>

### `MSR_STAR`

`macro` | [headers/arch/x86/msr.h:19](../../headers/arch/x86/msr.h#L19)

```c
#define MSR_STAR
```

---

<a id="msr_lstar"></a>

### `MSR_LSTAR`

`macro` | [headers/arch/x86/msr.h:20](../../headers/arch/x86/msr.h#L20)

```c
#define MSR_LSTAR
```

---

<a id="msr_sfmask"></a>

### `MSR_SFMASK`

`macro` | [headers/arch/x86/msr.h:21](../../headers/arch/x86/msr.h#L21)

```c
#define MSR_SFMASK
```

---

<a id="msr_fsbase"></a>

### `MSR_FSBASE`

`macro` | [headers/arch/x86/msr.h:22](../../headers/arch/x86/msr.h#L22)

```c
#define MSR_FSBASE
```

---

<a id="msr_gsbase"></a>

### `MSR_GSBASE`

`macro` | [headers/arch/x86/msr.h:23](../../headers/arch/x86/msr.h#L23)

```c
#define MSR_GSBASE
```

---

<a id="msr_kernel_gs_base"></a>

### `MSR_KERNEL_GS_BASE`

`macro` | [headers/arch/x86/msr.h:24](../../headers/arch/x86/msr.h#L24)

```c
#define MSR_KERNEL_GS_BASE
```

---
