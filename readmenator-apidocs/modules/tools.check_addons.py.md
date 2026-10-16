# `tools.check_addons`

> Source: [tools/check_addons.py:1](../../tools/check_addons.py#L1) | language `py` | coverage 33.3% | [API index](../index.md)

check_addons.py -- validate the MiniOS addon marketplace index.

Loads every addons/*.yaml through the strict stdlib-only parser in
mcp/minios_addons.py (no PyYAML) and reports each addon's kind. Any
unparseable file, failed validation or installer refusal for a guest
addon fails closed with a diagnostic and a nonzero exit, so the index
can never drift from the dialect the MCP server speaks.

Usage:
  python3 tools/check_addons.py [--addons-dir DIR]

Exit status: 0 when every file validates, 1 otherwise.

## Contents

- **Functions:** [`load_parser`](#load_parser), [`main`](#main)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_tools_check_addons_py__main(["main"])
    n_tools_check_addons_py__load_parser(["load_parser"])
    n_tools_check_addons_py__main --> n_tools_check_addons_py__load_parser
```

## Functions

<a id="load_parser"></a>

### `load_parser`

`function` | [tools/check_addons.py:22](../../tools/check_addons.py#L22)

```python
def load_parser()
```

*Called by:* [`main`](#main)

---

<a id="main"></a>

### `main`

`function` | [tools/check_addons.py:31](../../tools/check_addons.py#L31)

```python
def main()
```

*Calls:* [`load_parser`](#load_parser)

---
