# `headers/pcache.h`

> Source: [headers/pcache.h:1](../../headers/pcache.h#L1) | language `h` | coverage 94.1% | [API index](../index.md)

Docstring: pcache.h -- page cache for MiniFS, slice 1 (store only).

## Contents

- **Functions:** [`pcache_init`](#pcache_init), [`pcache_lookup`](#pcache_lookup), [`pcache_get`](#pcache_get), [`pcache_publish`](#pcache_publish), [`pcache_put`](#pcache_put), [`pcache_ref`](#pcache_ref), [`pcache_unmap`](#pcache_unmap), [`match`](#match), [`pcache_ref_if`](#pcache_ref_if), [`pcache_owns_phys`](#pcache_owns_phys), [`pcache_data`](#pcache_data), [`pcache_mark_dirty`](#pcache_mark_dirty), [`pcache_invalidate_ino`](#pcache_invalidate_ino), [`pcache_stats`](#pcache_stats)
- **Macros:** [`PCACHE_PAGES`](#pcache_pages), [`PCACHE_PAGE`](#pcache_page)

## Functions

<a id="pcache_init"></a>

### `pcache_init`

`function` | [headers/pcache.h:28](../../headers/pcache.h#L28)

```c
void pcache_init(void);
```

Docstring: Allocate the page pool; disabled (all calls fail closed) when the heap cannot spare it, exactly like the block cache.

Prints one boot marker either way.

*Called by:* [`__attribute__`](kernel.c.md#__attribute__)

---

<a id="pcache_lookup"></a>

### `pcache_lookup`

`function` | [headers/pcache.h:32](../../headers/pcache.h#L32)

```c
int pcache_lookup(int ino, unsigned index);
```

Docstring: Find a cached page without reserving.

Returns the slot or -1. Never allocates, never evicts.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ino` | `int` |  |  |
| `index` | `unsigned` |  |  |

**Returns:** `int`

*Called by:* [`mm_file_break`](kernel.mm.paging.c.md#mm_file_break)

---

<a id="pcache_get"></a>

### `pcache_get`

`function` | [headers/pcache.h:42](../../headers/pcache.h#L42)

```c
int pcache_get(int ino, unsigned index, int *is_new);
```

Docstring: Get a page, pinned with one ref.

Hit returns the live slot; miss reserves an empty or evicted slot (ref 1, clean, *is_new 1, data uninitialized: the caller fills it before any reader sees it) or -1 when every slot is pinned or the pool is disabled, in which case the caller falls back to direct block I/O, fail-open correct. Racy fills must use publish below, never a reserved-then-filled get: a concurrent faulter would map the half-written page.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ino` | `int` |  |  |
| `index` | `unsigned` |  |  |
| `is_new` | `int *` |  |  |

**Returns:** `int`

---

<a id="pcache_publish"></a>

### `pcache_publish`

`function` | [headers/pcache.h:51](../../headers/pcache.h#L51)

```c
int pcache_publish(int ino, unsigned index, const unsigned char *data);
```

Docstring: Publish a privately filled page into the cache atomically.

Copies data into a reserved slot and marks it valid under one lock hold, or refs the slot a racing publisher won first; either way the returned slot is complete before any other holder can see it. Returns the slot (ref 1 for this mapping) or -1 when no slot is free, in which case the caller maps its private page and takes no ref.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ino` | `int` |  |  |
| `index` | `unsigned` |  |  |
| `data` | `unsigned char *` |  |  |

**Returns:** `int`

*Called by:* [`consistent`](kernel.loader.c.md#consistent)

---

<a id="pcache_put"></a>

### `pcache_put`

`function` | [headers/pcache.h:55](../../headers/pcache.h#L55)

```c
void pcache_put(int slot);
```

Docstring: Drop one ref taken by get.

A zero ref is a no-op, never negative.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `slot` | `int` |  |  |

---

<a id="pcache_ref"></a>

### `pcache_ref`

`function` | [headers/pcache.h:61](../../headers/pcache.h#L61)

```c
int pcache_ref(int ino, unsigned index);
```

Docstring: Take one more ref on a cached page without allocating.

Fork uses this for every file-backed page the child inherits, so the child teardown drops exactly what the copy added. Returns the slot or -1 when the page is not cached.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ino` | `int` |  |  |
| `index` | `unsigned` |  |  |

**Returns:** `int`

---

<a id="pcache_unmap"></a>

### `pcache_unmap`

`function` | [headers/pcache.h:69](../../headers/pcache.h#L69)

```c
void pcache_unmap(int ino, unsigned index);
```

Docstring: Drop the ref a mapping holds on one cached page.

The munmap and teardown walks derive (ino, index) from the VMA node and call this per page; unknown pages are a silent no-op so a partially populated mapping unmaps cleanly. Prefer put_if below wherever the PTE is at hand: blind drops can steal another mapping's ref after a private fallback.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ino` | `int` |  |  |
| `index` | `unsigned` |  |  |

---

<a id="match"></a>

### `match`

`function` | [headers/pcache.h:75](../../headers/pcache.h#L75)

```c
* a phys match (owned, ref dropped unless already zero), 0 * otherwise. */ int pcache_put_if(int ino, unsigned index, unsigned long phys);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `zero` | `dropped unless already` |  |  |

**Returns:** `* a phys`

---

<a id="pcache_ref_if"></a>

### `pcache_ref_if`

`function` | [headers/pcache.h:83](../../headers/pcache.h#L83)

```c
int pcache_ref_if(int ino, unsigned index, unsigned long phys);
```

Docstring: Take one more ref only when the cached page is the exact phys the caller shares.

Fork proves sharing through the parent PTE before inheriting, so a stale VMA tag never pins a recycled slot. Returns the slot or -1.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ino` | `int` |  |  |
| `index` | `unsigned` |  |  |
| `phys` | `unsigned long` |  |  |

**Returns:** `int`

---

<a id="pcache_owns_phys"></a>

### `pcache_owns_phys`

`function` | [headers/pcache.h:88](../../headers/pcache.h#L88)

```c
int pcache_owns_phys(unsigned long phys);
```

Docstring: True when phys is a cache pool page.

The teardown sweeper skips those instead of freeing pool memory as if it were a private data page.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `phys` | `unsigned long` |  |  |

**Returns:** `int`

*Called by:* [`PTE`](kernel.mm.paging.c.md#pte)

---

<a id="pcache_data"></a>

### `pcache_data`

`function` | [headers/pcache.h:93](../../headers/pcache.h#L93)

```c
unsigned char *pcache_data(int slot);
```

Docstring: Page data for a slot from get/lookup, 0 on a bad slot.

The pointer stays valid until put drops the last ref and the slot is recycled.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `slot` | `int` |  |  |

**Returns:** `unsigned char *`

*Called by:* [`consistent`](kernel.loader.c.md#consistent), [`mm_file_break`](kernel.mm.paging.c.md#mm_file_break)

---

<a id="pcache_mark_dirty"></a>

### `pcache_mark_dirty`

`function` | [headers/pcache.h:98](../../headers/pcache.h#L98)

```c
void pcache_mark_dirty(int slot);
```

Docstring: Mark a pinned page dirty.

Slice 3 flushes it; slice 1 only records. Recycled slots bump a generation counter (slice 3 exposes it so holders can validate across put).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `slot` | `int` |  |  |

---

<a id="pcache_invalidate_ino"></a>

### `pcache_invalidate_ino`

`function` | [headers/pcache.h:102](../../headers/pcache.h#L102)

```c
void pcache_invalidate_ino(int ino);
```

Docstring: Drop every page of an inode (truncate/unlink).

Dirty pages drop with them until slice 3 teaches writeback.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ino` | `int` |  |  |

*Called by:* [`minifs_truncate`](fs.minifs.c.md#minifs_truncate), [`minifs_unlink`](fs.minifs.c.md#minifs_unlink)

---

<a id="pcache_stats"></a>

### `pcache_stats`

`function` | [headers/pcache.h:106](../../headers/pcache.h#L106)

```c
void pcache_stats(unsigned long *pages_out, unsigned long *hits_out, unsigned long *miss_out, unsigned long *evicted_out, unsigned long *dirty_out);
```

Docstring: Snapshot for the mem builtin and BDD: live pages, cumulative hits/misses/evictions, dirty count.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `pages_out` | `unsigned long *` |  |  |
| `hits_out` | `unsigned long *` |  |  |
| `miss_out` | `unsigned long *` |  |  |
| `evicted_out` | `unsigned long *` |  |  |
| `dirty_out` | `unsigned long *` |  |  |

---

## Macros

<a id="pcache_pages"></a>

### `PCACHE_PAGES`

`macro` | [headers/pcache.h:20](../../headers/pcache.h#L20)

```c
#define PCACHE_PAGES
```

Docstring: Pool size in pages (256 x 4 KB = 1 MB of heap).

---

<a id="pcache_page"></a>

### `PCACHE_PAGE`

`macro` | [headers/pcache.h:23](../../headers/pcache.h#L23)

```c
#define PCACHE_PAGE
```

Docstring: Cache page size, always the MiniFS block size.

---
