# `headers/tlb.h`

> Source: [headers/tlb.h:1](../../headers/tlb.h#L1) | language `h` | coverage 66.7% | [API index](../index.md)

tlb.h - cross-CPU TLB shootdown (docs/spec/smp-sched.md, "TLB shootdown").

## Contents

- **Functions:** [`space`](#space), [`tlb_shootdown_count`](#tlb_shootdown_count), [`tlb_shootdown_timeouts`](#tlb_shootdown_timeouts), [`tlb_nmi_entry`](#tlb_nmi_entry)
- **Macros:** [`TLB_RELEASE_BATCH`](#tlb_release_batch)
- **Variables:** [`tlb_shoot_acks`](#tlb_shoot_acks)

## Functions

<a id="space"></a>

### `space`

`function` | [headers/tlb.h:4](../../headers/tlb.h#L4)

```c
* while that CPU keeps running the same address space (CLONE_VM threads on * an AP). Callers clear the PTEs, flush locally, call tlb_shootdown with the * address space, and only then release the frame
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `AP` | `CLONE_VM threads on * an` |  |  |

**Returns:** `* while that CPU keeps running the same address`

---

<a id="tlb_shootdown_count"></a>

### `tlb_shootdown_count`

`function` | [headers/tlb.h:22](../../headers/tlb.h#L22)

```c
unsigned long tlb_shootdown_count(void);
```

Shootdowns broadcast and acknowledgement waits that ran out of budget (reported by the smp builtin).

**Returns:** `unsigned long`

---

<a id="tlb_shootdown_timeouts"></a>

### `tlb_shootdown_timeouts`

`function` | [headers/tlb.h:23](../../headers/tlb.h#L23)

```c
unsigned long tlb_shootdown_timeouts(void);
```

**Returns:** `unsigned long`

---

<a id="tlb_nmi_entry"></a>

### `tlb_nmi_entry`

`function` | [headers/tlb.h:26](../../headers/tlb.h#L26)

```c
void tlb_nmi_entry(void);
```

The vector-2 gate (arch/x86/tlb_nmi.S) and its acknowledgement counter.

---

## Macros

<a id="tlb_release_batch"></a>

### `TLB_RELEASE_BATCH`

`macro` | [headers/tlb.h:13](../../headers/tlb.h#L13)

```c
#define TLB_RELEASE_BATCH
```

Pages a release path clears before one shootdown releases them.

---

## Variables

<a id="tlb_shoot_acks"></a>

### `tlb_shoot_acks`

`variable` `extern` | [headers/tlb.h:27](../../headers/tlb.h#L27)

```c
extern volatile unsigned int tlb_shoot_acks;
```

---
