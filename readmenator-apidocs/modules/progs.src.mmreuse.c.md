# `progs/src/mmreuse.c`

> Source: [progs/src/mmreuse.c:1](../../progs/src/mmreuse.c#L1) | language `c` | coverage 33.3% | [API index](../index.md)

mmap/munmap reclaim stress test.

Repeatedly maps and unmaps a large

## Contents

- **Functions:** [`ENOMEM`](#enomem), [`_start`](#_start)

## Functions

<a id="enomem"></a>

### `ENOMEM`

`function` | [progs/src/mmreuse.c:3](../../progs/src/mmreuse.c#L3)

```c
* downward mmap cursor drains until a map fails with ENOMEM (-12);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `-12` |  |  |  |

**Returns:** `* downward mmap cursor drains until a map fails with`

---

<a id="_start"></a>

### `_start`

`function` | [progs/src/mmreuse.c:35](../../progs/src/mmreuse.c#L35)

```c
void _start(void)
```

---
