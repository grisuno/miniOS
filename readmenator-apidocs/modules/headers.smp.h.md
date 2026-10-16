# `headers/smp.h`

> Source: [headers/smp.h:1](../../headers/smp.h#L1) | language `h` | coverage 60.0% | [API index](../index.md)

SMP bring-up: wake the application processors (APs) via the LAPIC INIT/SIPI

## Contents

- **Functions:** [`smp_init`](#smp_init), [`smp_ap_entry`](#smp_ap_entry), [`smp_ipi_broadcast`](#smp_ipi_broadcast), [`smp_nmi_broadcast`](#smp_nmi_broadcast)
- **Variables:** [`smp_lock`](#smp_lock), [`smp_dbg_svr`](#smp_dbg_svr), [`smp_dbg_lvt`](#smp_dbg_lvt), [`smp_dbg_ipis`](#smp_dbg_ipis), [`smp_dbg_sent`](#smp_dbg_sent), [`lapic_cal_10ms`](#lapic_cal_10ms), [`lapic_cal_valid`](#lapic_cal_valid)

## Functions

<a id="smp_init"></a>

### `smp_init`

`function` | [headers/smp.h:41](../../headers/smp.h#L41)

```c
void smp_init(void);
```

*Called by:* [`__attribute__`](kernel.c.md#__attribute__)

---

<a id="smp_ap_entry"></a>

### `smp_ap_entry`

`function` | [headers/smp.h:42](../../headers/smp.h#L42)

```c
void smp_ap_entry(void);
```

---

<a id="smp_ipi_broadcast"></a>

### `smp_ipi_broadcast`

`function` | [headers/smp.h:43](../../headers/smp.h#L43)

```c
void smp_ipi_broadcast(int vector);
```

entry point each AP jumps to from ap_entry.S

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `vector` | `int` |  |  |

*Called by:* [`isr_dispatch`](kernel.sched.c.md#isr_dispatch), [`smp_init`](smp.c.md#smp_init)

---

<a id="smp_nmi_broadcast"></a>

### `smp_nmi_broadcast`

`function` | [headers/smp.h:44](../../headers/smp.h#L44)

```c
void smp_nmi_broadcast(void);
```

fixed-delivery IPI, all except self

*Called by:* [`tlb_shootdown`](kernel.mm.tlb.c.md#tlb_shootdown)

---

## Variables

<a id="smp_lock"></a>

### `smp_lock`

`variable` `extern` | [headers/smp.h:25](../../headers/smp.h#L25)

```c
extern spinlock_t smp_lock;
```

---

<a id="smp_dbg_svr"></a>

### `smp_dbg_svr`

`variable` `extern` | [headers/smp.h:30](../../headers/smp.h#L30)

```c
extern volatile unsigned smp_dbg_svr;
```

Read-back diagnostics written by the AP after its LAPIC setup; the `smp` builtin prints them so a dead AP's APIC state is visible over the serial console.

---

<a id="smp_dbg_lvt"></a>

### `smp_dbg_lvt`

`variable` `extern` | [headers/smp.h:31](../../headers/smp.h#L31)

```c
extern volatile unsigned smp_dbg_lvt;
```

---

<a id="smp_dbg_ipis"></a>

### `smp_dbg_ipis`

`variable` `extern` | [headers/smp.h:32](../../headers/smp.h#L32)

```c
extern volatile unsigned smp_dbg_ipis;
```

---

<a id="smp_dbg_sent"></a>

### `smp_dbg_sent`

`variable` `extern` | [headers/smp.h:33](../../headers/smp.h#L33)

```c
extern volatile unsigned smp_dbg_sent;
```

vector-32 ISRs run on APs

---

<a id="lapic_cal_10ms"></a>

### `lapic_cal_10ms`

`variable` `extern` | [headers/smp.h:38](../../headers/smp.h#L38)

```c
extern unsigned lapic_cal_10ms;
```

PIT-anchored LAPIC calibration (ticks per 10 ms at divide-by-16).

Measured once by the BSP in smp_init; the AP periodic timer uses it when MINIOS_AP_TIMER is set. lapic_cal_valid is 0 on the fixed 625000-tick fallback.

---

<a id="lapic_cal_valid"></a>

### `lapic_cal_valid`

`variable` `extern` | [headers/smp.h:39](../../headers/smp.h#L39)

```c
extern int lapic_cal_valid;
```

---
