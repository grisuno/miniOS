# `tools.check_spin_discipline`

> Source: [tools/check_spin_discipline.py:1](../../tools/check_spin_discipline.py#L1) | language `py` | coverage 80.0% | [API index](../index.md)

Check spinlock call-site discipline across kernel C sources.

Rules, derived from the headers/spinlock.h contract:
  S1  No orphaned acquire or release: a function using spin_lock must
      reach a spin_unlock on some path (and vice versa); same for the
      irqsave/irqrestore pair. Early-return style (one acquire, many
      releases) is idiomatic here, so exact counts are not enforced.
      Functions using spin_trylock follow the conditional-unlock idiom
      and are exempt from pairing.
  S2  No plain spin_lock inside interrupt context: isr_dispatch and any
      function whose name carries isr/irq may only use the irqsave form,
      because spin_unlock re-enables interrupts unconditionally.

Usage: python3 tools/check_spin_discipline.py [dir ...]
Exit 1 with a diagnostic on the first violation, else prints ok.

## Contents

- **Classes:** [`Config`](#config)
- **Functions:** [`iter_functions`](#iter_functions), [`check_file`](#check_file), [`main`](#main)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_tools_check_spin_discipline_py__check_file(["check_file"])
    n_tools_check_spin_discipline_py__iter_functions(["iter_functions"])
    n_tools_check_spin_discipline_py__main(["main"])
    n_tools_check_spin_discipline_py__check_file --> n_tools_check_spin_discipline_py__iter_functions
    n_tools_check_spin_discipline_py__main --> n_tools_check_spin_discipline_py__check_file
```

## Classes

<a id="config"></a>

### `Config`

`class` | [tools/check_spin_discipline.py:23](../../tools/check_spin_discipline.py#L23)

```python
class Config
```

**Attributes**

| Name | Type | Default | Description |
|---|---|---|---|
| [`roots`](#config-roots) |  | `('kernel', 'drivers', 'fs', 'net')` |  |
| [`suffix`](#config-suffix) |  | `'.c'` |  |
| [`handoff`](#config-handoff) |  | `frozenset(('fs_take', 'fs_drop'))` |  |
| [`isr_name`](#config-isr_name) |  | `re.compile('isr\|irq', re.IGNORECASE)` |  |
| [`plain_acq`](#config-plain_acq) |  | `re.compile('(?<![\\w])spin_lock\\s*\\(')` |  |
| [`plain_rel`](#config-plain_rel) |  | `re.compile('(?<![\\w])spin_unlock\\s*\\(')` |  |
| [`save_acq`](#config-save_acq) |  | `re.compile('(?<![\\w])spin_lock_irqsave\\s*\\(')` |  |
| [`save_rel`](#config-save_rel) |  | `re.compile('(?<![\\w])spin_unlock_irqrestore\\s*\\(')` |  |
| [`keep_rel`](#config-keep_rel) |  | `re.compile('(?<![\\w])spin_unlock_keep_irq\\s*\\(')` |  |
| [`try_acq`](#config-try_acq) |  | `re.compile('(?<![\\w])spin_trylock\\s*\\(')` |  |
| [`func_head`](#config-func_head) |  | `re.compile('^([A-Za-z_][\\w\\s\\*]*?)\\b([A-Za-z_]\\w*)\\s*\\([^;]*\\)\\s*\\{?\\s*$')` |  |

---

## Functions

<a id="iter_functions"></a>

### `iter_functions`

`function` `generator` | [tools/check_spin_discipline.py:38](../../tools/check_spin_discipline.py#L38)

```python
def iter_functions(path)
```

Yield (name, first_line, body_lines) with a brace-depth split.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `path` |  |  |  |

*Called by:* [`check_file`](#check_file)

---

<a id="check_file"></a>

### `check_file`

`function` | [tools/check_spin_discipline.py:64](../../tools/check_spin_discipline.py#L64)

```python
def check_file(path)
```

Return a list of violation strings for one translation unit.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `path` |  |  |  |

*Calls:* [`iter_functions`](#iter_functions)

*Called by:* [`main`](#main)

---

<a id="main"></a>

### `main`

`function` | [tools/check_spin_discipline.py:99](../../tools/check_spin_discipline.py#L99)

```python
def main(argv)
```

Walk the configured roots and fail closed on any violation.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argv` |  |  |  |

*Calls:* [`check_file`](#check_file)

---
