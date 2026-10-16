# `arch/x86/syscall_entry.S`

> Source: [arch/x86/syscall_entry.S:1](../../arch/x86/syscall_entry.S#L1) | language `S` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`syscall_kstack`](#syscall_kstack), [`kstack_base`](#kstack_base), [`sc_top_save_addr`](#sc_top_save_addr), [`syscall_entry`](#syscall_entry)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_arch_x86_syscall_entry_S__syscall_entry(["syscall_entry"])
    n_arch_x86_syscall_entry_S__kstack_base(["kstack_base"])
    n_arch_x86_syscall_entry_S__syscall_entry --> n_arch_x86_syscall_entry_S__kstack_base
```

## Functions

<a id="syscall_kstack"></a>

### `syscall_kstack`

`function` | [arch/x86/syscall_entry.S:49](../../arch/x86/syscall_entry.S#L49)

```asm
syscall_kstack:
```

---

<a id="kstack_base"></a>

### `kstack_base`

`function` | [arch/x86/syscall_entry.S:52](../../arch/x86/syscall_entry.S#L52)

```asm
kstack_base:
```

*Called by:* [`syscall_entry`](#syscall_entry)

---

<a id="sc_top_save_addr"></a>

### `sc_top_save_addr`

`function` | [arch/x86/syscall_entry.S:55](../../arch/x86/syscall_entry.S#L55)

```asm
sc_top_save_addr:
```

---

<a id="syscall_entry"></a>

### `syscall_entry`

`function` | [arch/x86/syscall_entry.S:65](../../arch/x86/syscall_entry.S#L65)

```asm
syscall_entry:
```

*Calls:* [`kstack_base`](#kstack_base)

---
