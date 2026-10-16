# `tools/wm_scoped.sh`

> Source: [tools/wm_scoped.sh:1](../../tools/wm_scoped.sh#L1) | language `sh` | coverage 33.3% | [API index](../index.md)

Docstring: Scoped WM validation for Alt-Tab and tile across all windows.

Runs host WM unit tests, rebuilds touched kernel objects with zero warnings, and asserts scoped mutants die. Fails closed on first gap.

## Contents

- **Functions:** [`say`](#say), [`die`](#die)

## Functions

<a id="say"></a>

### `say`

`function` | [tools/wm_scoped.sh:8](../../tools/wm_scoped.sh#L8)

```bash
say() { printf '%s\n' "$1"; }
```

---

<a id="die"></a>

### `die`

`function` | [tools/wm_scoped.sh:9](../../tools/wm_scoped.sh#L9)

```bash
die() { say "FAIL: $1"; fail=1; }
```

---
