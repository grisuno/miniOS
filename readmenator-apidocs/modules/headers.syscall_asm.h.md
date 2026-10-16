# `headers/syscall_asm.h`

> Source: [headers/syscall_asm.h:1](../../headers/syscall_asm.h#L1) | language `h` | coverage 92.3% | [API index](../index.md)

syscall_asm.h -- numeric contract for arch/x86/syscall_entry.S.

## Contents

- **Macros:** [`SYSCALL_USER_WIN_LO`](#syscall_user_win_lo), [`SYSCALL_USER_WIN_HI`](#syscall_user_win_hi), [`SYSCALL_PROC_T_SIZE`](#syscall_proc_t_size), [`SYSCALL_PROC_KSTACK_OFF`](#syscall_proc_kstack_off), [`SYSCALL_MAX_PROCS`](#syscall_max_procs), [`SYSCALL_CPU_CUR_PID_OFF`](#syscall_cpu_cur_pid_off), [`SYSCALL_CPU_SC_N_OFF`](#syscall_cpu_sc_n_off), [`SYSCALL_CPU_SC_RIP_OFF`](#syscall_cpu_sc_rip_off), [`SYSCALL_CPU_SC_PID_OFF`](#syscall_cpu_sc_pid_off), [`SYSCALL_CPU_SC_RET_OFF`](#syscall_cpu_sc_ret_off), [`SYSCALL_CPU_SC_TMP_OFF`](#syscall_cpu_sc_tmp_off), [`SYSCALL_FRAME_WORDS`](#syscall_frame_words)

## Macros

<a id="syscall_user_win_lo"></a>

### `SYSCALL_USER_WIN_LO`

`macro` | [headers/syscall_asm.h:15](../../headers/syscall_asm.h#L15)

```c
#define SYSCALL_USER_WIN_LO
```

---

<a id="syscall_user_win_hi"></a>

### `SYSCALL_USER_WIN_HI`

`macro` | [headers/syscall_asm.h:16](../../headers/syscall_asm.h#L16)

```c
#define SYSCALL_USER_WIN_HI
```

== MINIOS_USER_LOAD_BASE

---

<a id="syscall_proc_t_size"></a>

### `SYSCALL_PROC_T_SIZE`

`macro` | [headers/syscall_asm.h:17](../../headers/syscall_asm.h#L17)

```c
#define SYSCALL_PROC_T_SIZE
```

== MINIOS_USER_LOAD_END

---

<a id="syscall_proc_kstack_off"></a>

### `SYSCALL_PROC_KSTACK_OFF`

`macro` | [headers/syscall_asm.h:18](../../headers/syscall_asm.h#L18)

```c
#define SYSCALL_PROC_KSTACK_OFF
```

== PROC_T_SIZE (sched.h)

---

<a id="syscall_max_procs"></a>

### `SYSCALL_MAX_PROCS`

`macro` | [headers/syscall_asm.h:19](../../headers/syscall_asm.h#L19)

```c
#define SYSCALL_MAX_PROCS
```

== PROC_KSTACK_OFF

---

<a id="syscall_cpu_cur_pid_off"></a>

### `SYSCALL_CPU_CUR_PID_OFF`

`macro` | [headers/syscall_asm.h:20](../../headers/syscall_asm.h#L20)

```c
#define SYSCALL_CPU_CUR_PID_OFF
```

== MAX_PROCS

---

<a id="syscall_cpu_sc_n_off"></a>

### `SYSCALL_CPU_SC_N_OFF`

`macro` | [headers/syscall_asm.h:21](../../headers/syscall_asm.h#L21)

```c
#define SYSCALL_CPU_SC_N_OFF
```

offsetof(cpu_t, cur_pid)

---

<a id="syscall_cpu_sc_rip_off"></a>

### `SYSCALL_CPU_SC_RIP_OFF`

`macro` | [headers/syscall_asm.h:22](../../headers/syscall_asm.h#L22)

```c
#define SYSCALL_CPU_SC_RIP_OFF
```

offsetof(cpu_t, sc_n)

---

<a id="syscall_cpu_sc_pid_off"></a>

### `SYSCALL_CPU_SC_PID_OFF`

`macro` | [headers/syscall_asm.h:23](../../headers/syscall_asm.h#L23)

```c
#define SYSCALL_CPU_SC_PID_OFF
```

offsetof(cpu_t, sc_rip)

---

<a id="syscall_cpu_sc_ret_off"></a>

### `SYSCALL_CPU_SC_RET_OFF`

`macro` | [headers/syscall_asm.h:24](../../headers/syscall_asm.h#L24)

```c
#define SYSCALL_CPU_SC_RET_OFF
```

offsetof(cpu_t, sc_pid)

---

<a id="syscall_cpu_sc_tmp_off"></a>

### `SYSCALL_CPU_SC_TMP_OFF`

`macro` | [headers/syscall_asm.h:25](../../headers/syscall_asm.h#L25)

```c
#define SYSCALL_CPU_SC_TMP_OFF
```

offsetof(cpu_t, sc_ret)

---

<a id="syscall_frame_words"></a>

### `SYSCALL_FRAME_WORDS`

`macro` | [headers/syscall_asm.h:29](../../headers/syscall_asm.h#L29)

```c
#define SYSCALL_FRAME_WORDS
```

Words the entry pushes per syscall, top down: the six user callee-saved registers, then &PCB.kstack, pid, a6..a1, n, user rip, user rflags. == sizeof(syscall_frame_t) / 8 (sched.h).

---
