# `arch/x86/ap_entry.S`

> Source: [arch/x86/ap_entry.S:1](../../arch/x86/ap_entry.S#L1) | language `S` | coverage 20.0% | [API index](../index.md)

ap_entry.S - SMP application-processor bootstrap stub.

## Contents

- **Functions:** [`ap_stub_start`](#ap_stub_start), [`ap_pm`](#ap_pm), [`ap_lm`](#ap_lm), [`ap_patch_slot`](#ap_patch_slot), [`ap_gdt32`](#ap_gdt32), [`ap_gdt32_ptr`](#ap_gdt32_ptr), [`ap_gdt32_end`](#ap_gdt32_end), [`ap_gdt64_ptr`](#ap_gdt64_ptr), [`ap_stub_end`](#ap_stub_end)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_arch_x86_ap_entry_S__ap_lm(["ap_lm"])
    n_arch_x86_ap_entry_S__ap_patch_slot(["ap_patch_slot"])
    n_arch_x86_ap_entry_S__ap_lm --> n_arch_x86_ap_entry_S__ap_patch_slot
```

## Functions

<a id="ap_stub_start"></a>

### `ap_stub_start`

`function` | [arch/x86/ap_entry.S:21](../../arch/x86/ap_entry.S#L21)

```asm
ap_stub_start:
```

---

<a id="ap_pm"></a>

### `ap_pm`

`function` | [arch/x86/ap_entry.S:39](../../arch/x86/ap_entry.S#L39)

```asm
ap_pm:
```

---

<a id="ap_lm"></a>

### `ap_lm`

`function` | [arch/x86/ap_entry.S:62](../../arch/x86/ap_entry.S#L62)

```asm
ap_lm:
```

*Calls:* [`ap_patch_slot`](#ap_patch_slot)

---

<a id="ap_patch_slot"></a>

### `ap_patch_slot`

`function` | [arch/x86/ap_entry.S:80](../../arch/x86/ap_entry.S#L80)

```asm
ap_patch_slot:
```

*Called by:* [`ap_lm`](#ap_lm)

---

<a id="ap_gdt32"></a>

### `ap_gdt32`

`function` | [arch/x86/ap_entry.S:84](../../arch/x86/ap_entry.S#L84)

```asm
ap_gdt32:
```

---

<a id="ap_gdt32_ptr"></a>

### `ap_gdt32_ptr`

`function` | [arch/x86/ap_entry.S:88](../../arch/x86/ap_entry.S#L88)

```asm
ap_gdt32_ptr:
```

data32 base 0 limit 4G

---

<a id="ap_gdt32_end"></a>

### `ap_gdt32_end`

`function` | [arch/x86/ap_entry.S:91](../../arch/x86/ap_entry.S#L91)

```asm
ap_gdt32_end:
```

---

<a id="ap_gdt64_ptr"></a>

### `ap_gdt64_ptr`

`function` | [arch/x86/ap_entry.S:93](../../arch/x86/ap_entry.S#L93)

```asm
ap_gdt64_ptr:
```

---

<a id="ap_stub_end"></a>

### `ap_stub_end`

`function` | [arch/x86/ap_entry.S:98](../../arch/x86/ap_entry.S#L98)

```asm
ap_stub_end:
```

---
