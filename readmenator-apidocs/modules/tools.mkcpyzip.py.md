# `tools.mkcpyzip`

> Source: [tools/mkcpyzip.py:1](../../tools/mkcpyzip.py#L1) | language `py` | coverage 66.7% | [API index](../index.md)

mkcpyzip.py -- pack a CPython Lib tree into a zipimport stdlib.

Usage: mkcpyzip.py <lib_dir> <out_zip> [skip_dir ...]

CPython's sys.path already names <prefix>/lib/python312.zip, so one
stored (uncompressed) zip carries the whole pure-Python standard library
onto MiniFS as a single inode, and zipimport needs no zlib module inside
the guest for stored entries. Directories named in skip (typically test,
idlelib, tkinter, ensurepip, venv) and every __pycache__ are pruned;
compiled .py/.pyo files are not shipped (zipimport compiles on the fly).

Exit 0 with one summary line on success; a missing input or an empty
result exits 1 with the reason on stderr.

## Contents

- **Functions:** [`build_zip`](#build_zip), [`main`](#main)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_tools_mkcpyzip_py__main(["main"])
    n_tools_mkcpyzip_py__build_zip(["build_zip"])
    n_tools_mkcpyzip_py__main --> n_tools_mkcpyzip_py__build_zip
```

## Functions

<a id="build_zip"></a>

### `build_zip`

`function` | [tools/mkcpyzip.py:22](../../tools/mkcpyzip.py#L22)

```python
def build_zip(lib_dir, out_zip, skip)
```

Write out_zip with the Lib tree minus skip dirs; return file count.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `lib_dir` |  |  |  |
| `out_zip` |  |  |  |
| `skip` |  |  |  |

*Called by:* [`main`](#main)

---

<a id="main"></a>

### `main`

`function` | [tools/mkcpyzip.py:41](../../tools/mkcpyzip.py#L41)

```python
def main()
```

*Calls:* [`build_zip`](#build_zip)

---
