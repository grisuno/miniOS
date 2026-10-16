# `tools.mkpak1`

> Source: [tools/mkpak1.py:1](../../tools/mkpak1.py#L1) | language `py` | coverage 50.0% | [API index](../index.md)

Build baseq2/pak1.pak carrying the player model.

The Quake 2 shareware pak0.pak omits the player model (players/male/tris.md2,
grunt.pcx, weapon.md2, grunt_i.pcx are loose files in the retail game).  The
q2generic client must find them in a pak, so this script packages the loose
player model (from the Quake 2 install, held under progs/quake2generic/players)
into a small second pak the game loads after pak0.pak.

Quake 2 pak format: 4-byte "PACK", u32 directory offset, u32 directory length,
then 64-byte directory entries (56-byte NUL-padded name, u32 filepos, u32
filelen), then the concatenated file data.

## Contents

- **Functions:** [`main`](#main)
- **Constants:** [`BASE`](#base), [`SRC`](#src), [`OUT`](#out), [`FILES`](#files)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_tools_mkpak1_py__main(["main"])
    n_headers_sched_h__bytes["sched.bytes"]
    n_tools_mkpak1_py__main -.-> n_headers_sched_h__bytes
```

## Functions

<a id="main"></a>

### `main`

`function` | [tools/mkpak1.py:29](../../tools/mkpak1.py#L29)

```python
def main()
```

*Calls:* [`bytes`](headers.sched.h.md#bytes)

---

## Constants

<a id="base"></a>

### `BASE`

`constant` | [tools/mkpak1.py:17](../../tools/mkpak1.py#L17)

```python
BASE = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
```

---

<a id="src"></a>

### `SRC`

`constant` | [tools/mkpak1.py:18](../../tools/mkpak1.py#L18)

```python
SRC = os.path.join(BASE, 'progs/quake2generic/players/male')
```

---

<a id="out"></a>

### `OUT`

`constant` | [tools/mkpak1.py:19](../../tools/mkpak1.py#L19)

```python
OUT = os.path.join(BASE, 'progs/baseq2/pak1.pak')
```

---

<a id="files"></a>

### `FILES`

`constant` | [tools/mkpak1.py:21](../../tools/mkpak1.py#L21)

```python
FILES
```

---
