# `tools/wl_scoped.sh`

> Source: [tools/wl_scoped.sh:1](../../tools/wl_scoped.sh#L1) | language `sh` | coverage 20.0% | [API index](../index.md)

Docstring: Scoped Wayland-mini validation for the tiled ring-3 compositor.

Runs host wire, mailbox and palette tests, rebuilds the guest wlcomp binary with zero warnings, and asserts scoped mutants die. Fails closed.

## Contents

- **Functions:** [`say`](#say), [`die`](#die), [`mut`](#mut), [`mutm`](#mutm)

## Functions

<a id="say"></a>

### `say`

`function` | [tools/wl_scoped.sh:8](../../tools/wl_scoped.sh#L8)

```bash
say() { printf '%s\n' "$1"; }
```

---

<a id="die"></a>

### `die`

`function` | [tools/wl_scoped.sh:9](../../tools/wl_scoped.sh#L9)

```bash
die() { say "FAIL: $1"; fail=1; }
```

---

<a id="mut"></a>

### `mut`

`function` | [tools/wl_scoped.sh:77](../../tools/wl_scoped.sh#L77)

```bash
mut()
```

---

<a id="mutm"></a>

### `mutm`

`function` | [tools/wl_scoped.sh:84](../../tools/wl_scoped.sh#L84)

```bash
mutm()
```

---
