# `tools.probe_minicraft`

> Source: [tools/probe_minicraft.py:1](../../tools/probe_minicraft.py#L1) | language `py` | coverage 50.0% | [API index](../index.md)

probe_minicraft.py -- numeric minicraft probe without any PNG.

Boots os.img headless (display none), runs minicraft in the background so
the shell stays usable, and verifies rendering + movement purely through
serial-observable numbers:

  - `gfx frames` must climb (real compositing, like DOOM autoframes)
  - `wm list` gives the gfx window rect; `gfx rect` over the upper and
    lower content halves reports histograms (sky vs ground orientation)
  - QMP holds `w` for 2s, then the `P` key tap makes minicraft print
    `minicraft: pos X Y Z ... wood N`; X must have advanced vs before

No PIL, no screendump, no PNG: everything is parsed serial text.

Usage: python3 tools/probe_minicraft.py [--hold SECS]

## Contents

- **Functions:** [`main`](#main)
- **Constants:** [`HERE`](#here), [`WORK`](#work), [`QMP`](#qmp), [`SER`](#ser), [`HOLD`](#hold)

## Functions

<a id="main"></a>

### `main`

`function` | [tools/probe_minicraft.py:34](../../tools/probe_minicraft.py#L34)

```python
def main()
```

---

## Constants

<a id="here"></a>

### `HERE`

`constant` | [tools/probe_minicraft.py:27](../../tools/probe_minicraft.py#L27)

```python
HERE = os.path.dirname(os.path.abspath(__file__)) + '/..'
```

---

<a id="work"></a>

### `WORK`

`constant` | [tools/probe_minicraft.py:28](../../tools/probe_minicraft.py#L28)

```python
WORK = tempfile.mkdtemp(prefix='probe_mc_')
```

---

<a id="qmp"></a>

### `QMP`

`constant` | [tools/probe_minicraft.py:29](../../tools/probe_minicraft.py#L29)

```python
QMP = os.path.join(WORK, 'qmp.sock')
```

---

<a id="ser"></a>

### `SER`

`constant` | [tools/probe_minicraft.py:30](../../tools/probe_minicraft.py#L30)

```python
SER = os.path.join(WORK, 'ser.sock')
```

---

<a id="hold"></a>

### `HOLD`

`constant` | [tools/probe_minicraft.py:31](../../tools/probe_minicraft.py#L31)

```python
HOLD = os.path.join(WORK, 'stdin.hold')
```

---
