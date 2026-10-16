# `headers/arch/x86/cpu_setup.h`

> Source: [headers/arch/x86/cpu_setup.h:1](../../headers/arch/x86/cpu_setup.h#L1) | language `h` | coverage 100.0% | [API index](../index.md)

cpu_setup.h - per-CPU control-register setup shared by the BSP (kmain)

## Contents

- **Functions:** [`cpu_enable_caches`](#cpu_enable_caches)

## Functions

<a id="cpu_enable_caches"></a>

### `cpu_enable_caches`

`function` `inline` `static` | [headers/arch/x86/cpu_setup.h:30](../../headers/arch/x86/cpu_setup.h#L30)

```c
static inline void cpu_enable_caches(void)
```

Turn caching on (CR0.CD and CR0.NW clear), then write back and invalidate so no line filled under the reset policy survives.

---
