# `progs/doomgeneric/statdump.c`

> Source: [progs/doomgeneric/statdump.c:1](../../progs/doomgeneric/statdump.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`StatCopy`](#statcopy), [`StatDump`](#statdump)
- **Macros:** [`MAX_CAPTURES`](#max_captures)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_progs_doomgeneric_statdump_c__StatCopy(["StatCopy"])
    n_kernel_string_c__memcpy["string.memcpy"]
    n_progs_doomgeneric_m_argv_c__M_ParmExists["m_argv.M_ParmExists"]
    n_progs_doomgeneric_statdump_c__StatDump(["StatDump"])
    n_progs_doomgeneric_m_argv_h__M_CheckParmWithArgs["m_argv.M_CheckParmWithArgs"]
    n_progs_doomgeneric_statdump_c__StatCopy -.-> n_kernel_string_c__memcpy
    n_progs_doomgeneric_statdump_c__StatCopy -.-> n_progs_doomgeneric_m_argv_c__M_ParmExists
    n_progs_doomgeneric_statdump_c__StatDump -.-> n_progs_doomgeneric_m_argv_h__M_CheckParmWithArgs
```

## Functions

<a id="statcopy"></a>

### `StatCopy`

`function` | [progs/doomgeneric/statdump.c:333](../../progs/doomgeneric/statdump.c#L333)

```c
void StatCopy(wbstartstruct_t *stats)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `stats` | `wbstartstruct_t *` |  |  |

*Calls:* [`memcpy`](kernel.string.c.md#memcpy), [`M_ParmExists`](progs.doomgeneric.m_argv.c.md#m_parmexists)

---

<a id="statdump"></a>

### `StatDump`

`function` | [progs/doomgeneric/statdump.c:343](../../progs/doomgeneric/statdump.c#L343)

```c
void StatDump(void)
```

*Calls:* [`M_CheckParmWithArgs`](progs.doomgeneric.m_argv.h.md#m_checkparmwithargs)

---

## Macros

<a id="max_captures"></a>

### `MAX_CAPTURES`

`macro` | [progs/doomgeneric/statdump.c:56](../../progs/doomgeneric/statdump.c#L56)

```c
#define MAX_CAPTURES
```

---
