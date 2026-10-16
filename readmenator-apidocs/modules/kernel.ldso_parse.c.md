# `kernel/ldso_parse.c`

> Source: [kernel/ldso_parse.c:1](../../kernel/ldso_parse.c#L1) | language `c` | coverage 73.3% | [API index](../index.md)

Docstring: kernel/ldso_parse.c -- pure dynamic-table parsing (T8 ld.so).

## Contents

- **Functions:** [`ldso_vaddr_to_offset`](#ldso_vaddr_to_offset), [`ldso_segments`](#ldso_segments), [`ldso_find_dynamic`](#ldso_find_dynamic), [`ldso_scan_dynamic`](#ldso_scan_dynamic), [`ldso_sym_count`](#ldso_sym_count), [`ldso_copy_str`](#ldso_copy_str), [`ldso_sym_lookup`](#ldso_sym_lookup), [`ldso_rela_count`](#ldso_rela_count), [`ldso_read_rela`](#ldso_read_rela), [`ldso_basename`](#ldso_basename)
- **Macros:** [`LDSO_EHSIZE`](#ldso_ehsize), [`LDSO_PHENTSZ`](#ldso_phentsz), [`LDSO_DYN_ENT`](#ldso_dyn_ent), [`LDSO_HASH_HDR`](#ldso_hash_hdr)

## Functions

<a id="ldso_vaddr_to_offset"></a>

### `ldso_vaddr_to_offset`

`function` | [kernel/ldso_parse.c:54](../../kernel/ldso_parse.c#L54)

```c
int ldso_vaddr_to_offset(const unsigned char *file, unsigned long long fsize, unsigned long long va, unsigned long long *off)
```

Docstring: Translate a link VA through PT_LOAD into a file offset.

Returns 0 with the offset on success, -1 when no segment contains it or any arithmetic overflows.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `file` | `unsigned char *` |  |  |
| `fsize` | `unsigned long long` |  |  |
| `va` | `unsigned long long` |  |  |
| `off` | `unsigned long long *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`ldso_vaddr_to_offset`](#ldso_vaddr_to_offset) (headers/ldso.h:92).

---

<a id="ldso_segments"></a>

### `ldso_segments`

`function` | [kernel/ldso_parse.c:86](../../kernel/ldso_parse.c#L86)

```c
int ldso_segments(const unsigned char *file, unsigned long long fsize, LdsoSeg *segs, unsigned ncap, unsigned *nseg)
```

Docstring: Collect PT_LOAD spans (at most ncap) for reservation and GOT-range checks.

Returns 0 with the count, -1 on corrupt headers.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `file` | `unsigned char *` |  |  |
| `fsize` | `unsigned long long` |  |  |
| `segs` | `LdsoSeg *` |  |  |
| `ncap` | `unsigned` |  |  |
| `nseg` | `unsigned *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`ldso_segments`](#ldso_segments) (headers/ldso.h:97).

---

<a id="ldso_find_dynamic"></a>

### `ldso_find_dynamic`

`function` | [kernel/ldso_parse.c:120](../../kernel/ldso_parse.c#L120)

```c
int ldso_find_dynamic(const unsigned char *file, unsigned long long fsize, unsigned long long *dyn_off, unsigned long long *dyn_size)
```

Docstring: Locate the PT_DYNAMIC file range.

Returns 1 with offsets on success, 0 when the image carries no dynamic section (static binary, not an error), -1 when any header, count or bound is corrupt.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `file` | `unsigned char *` |  |  |
| `fsize` | `unsigned long long` |  |  |
| `dyn_off` | `unsigned long long *` |  |  |
| `dyn_size` | `unsigned long long *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`ldso_find_dynamic`](#ldso_find_dynamic) (headers/ldso.h:86).

---

<a id="ldso_scan_dynamic"></a>

### `ldso_scan_dynamic`

`function` | [kernel/ldso_parse.c:150](../../kernel/ldso_parse.c#L150)

```c
int ldso_scan_dynamic(const unsigned char *file, unsigned long long fsize, unsigned long long dyn_off, unsigned long long dyn_size, LdsoDynInfo *info)
```

Docstring: Walk the dynamic array into info.

Caps entries at LDSO_MAX_DYN, keeps the first SONAME, records up to LDSO_MAX_NEEDED NEEDED offsets. Returns 0 on success, -1 on truncation or overflow.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `file` | `unsigned char *` |  |  |
| `fsize` | `unsigned long long` |  |  |
| `dyn_off` | `unsigned long long` |  |  |
| `dyn_size` | `unsigned long long` |  |  |
| `info` | `LdsoDynInfo *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`ldso_scan_dynamic`](#ldso_scan_dynamic) (headers/ldso.h:103).

---

<a id="ldso_sym_count"></a>

### `ldso_sym_count`

`function` | [kernel/ldso_parse.c:213](../../kernel/ldso_parse.c#L213)

```c
int ldso_sym_count(const unsigned char *file, unsigned long long fsize, unsigned long long hash_off, unsigned *nsyms)
```

Docstring: Read the SYSV hash header at a file offset into bucket and chain counts.

The chain count is the dynamic symbol count. Returns 0 on success, -1 when the table is truncated or claims no symbols.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `file` | `unsigned char *` |  |  |
| `fsize` | `unsigned long long` |  |  |
| `hash_off` | `unsigned long long` |  |  |
| `nsyms` | `unsigned *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`ldso_sym_count`](#ldso_sym_count) (headers/ldso.h:110).

---

<a id="ldso_copy_str"></a>

### `ldso_copy_str`

`function` | [kernel/ldso_parse.c:227](../../kernel/ldso_parse.c#L227)

```c
int ldso_copy_str(const unsigned char *file, unsigned long long fsize, unsigned long long strtab_off, unsigned long long strsz, unsigned long long name_off, char *out, unsigned out_cap)
```

Docstring: Bounded copy of one dynamic string (NEEDED/SONAME/symbol).

The NUL must land inside strsz. Returns 0 with a terminated buffer, -1 on any out-of-range offset or missing terminator.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `file` | `unsigned char *` |  |  |
| `fsize` | `unsigned long long` |  |  |
| `strtab_off` | `unsigned long long` |  |  |
| `strsz` | `unsigned long long` |  |  |
| `name_off` | `unsigned long long` |  |  |
| `out` | `char *` |  |  |
| `out_cap` | `unsigned` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`ldso_copy_str`](#ldso_copy_str) (headers/ldso.h:116).

---

<a id="ldso_sym_lookup"></a>

### `ldso_sym_lookup`

`function` | [kernel/ldso_parse.c:263](../../kernel/ldso_parse.c#L263)

```c
int ldso_sym_lookup(const unsigned char *file, unsigned long long fsize, unsigned long long symtab_off, unsigned nsyms, unsigned long long strtab_off, unsigned long long strsz, const char *name, unsigned long long *value)
```

Docstring: Linear search of a dynamic symbol table by name.

Accepts GLOBAL FUNC/NOTYPE definitions only (v1 links functions, nothing else). Returns 1 with st_value on hit, 0 on clean miss, -1 on any corrupt table bound.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `file` | `unsigned char *` |  |  |
| `fsize` | `unsigned long long` |  |  |
| `symtab_off` | `unsigned long long` |  |  |
| `nsyms` | `unsigned` |  |  |
| `strtab_off` | `unsigned long long` |  |  |
| `strsz` | `unsigned long long` |  |  |
| `name` | `char *` |  |  |
| `value` | `unsigned long long *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`ldso_sym_lookup`](#ldso_sym_lookup) (headers/ldso.h:124).

---

<a id="ldso_rela_count"></a>

### `ldso_rela_count`

`function` | [kernel/ldso_parse.c:296](../../kernel/ldso_parse.c#L296)

```c
int ldso_rela_count(const LdsoDynInfo *info, unsigned *nrela)
```

Docstring: Validate the RELA header triple and report the row count.

Only 24-byte entries are supported (v1 emits exactly those). Returns 0 with the count, -1 on any mismatch or overflow.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `info` | `LdsoDynInfo *` |  |  |
| `nrela` | `unsigned *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`ldso_rela_count`](#ldso_rela_count) (headers/ldso.h:132).

---

<a id="ldso_read_rela"></a>

### `ldso_read_rela`

`function` | [kernel/ldso_parse.c:309](../../kernel/ldso_parse.c#L309)

```c
int ldso_read_rela(const unsigned char *file, unsigned long long fsize, unsigned long long rela_off, unsigned nrela, unsigned idx, unsigned nsyms, LdsoRelaRow *row)
```

Docstring: Read one RELA row with full validation: row inside the table, type GLOB_DAT/JUMP_SLOT (anything else is -2, unsupported), symbol index below nsyms.

Returns 0 on success.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `file` | `unsigned char *` |  |  |
| `fsize` | `unsigned long long` |  |  |
| `rela_off` | `unsigned long long` |  |  |
| `nrela` | `unsigned` |  |  |
| `idx` | `unsigned` |  |  |
| `nsyms` | `unsigned` |  |  |
| `row` | `LdsoRelaRow *` |  |  |

**Returns:** `int`

> **Inherited:** Documentation from [`ldso_read_rela`](#ldso_read_rela) (headers/ldso.h:137).

---

<a id="ldso_basename"></a>

### `ldso_basename`

`function` | [kernel/ldso_parse.c:331](../../kernel/ldso_parse.c#L331)

```c
void ldso_basename(char *out, const char *src)
```

Docstring: Basename normalization for registry keys ("a/b.so" to "b.so", bounded, always terminated).

Two spellings of one library share one registry slot and one load.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `out` | `char *` |  |  |
| `src` | `char *` |  |  |

> **Inherited:** Documentation from [`ldso_basename`](#ldso_basename) (headers/ldso.h:144).

---

## Macros

<a id="ldso_ehsize"></a>

### `LDSO_EHSIZE`

`macro` | [kernel/ldso_parse.c:13](../../kernel/ldso_parse.c#L13)

```c
#define LDSO_EHSIZE
```

---

<a id="ldso_phentsz"></a>

### `LDSO_PHENTSZ`

`macro` | [kernel/ldso_parse.c:14](../../kernel/ldso_parse.c#L14)

```c
#define LDSO_PHENTSZ
```

---

<a id="ldso_dyn_ent"></a>

### `LDSO_DYN_ENT`

`macro` | [kernel/ldso_parse.c:15](../../kernel/ldso_parse.c#L15)

```c
#define LDSO_DYN_ENT
```

---

<a id="ldso_hash_hdr"></a>

### `LDSO_HASH_HDR`

`macro` | [kernel/ldso_parse.c:16](../../kernel/ldso_parse.c#L16)

```c
#define LDSO_HASH_HDR
```

---
