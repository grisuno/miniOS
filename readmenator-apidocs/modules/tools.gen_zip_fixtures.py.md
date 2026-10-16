# `tools.gen_zip_fixtures`

> Source: [tools/gen_zip_fixtures.py:1](../../tools/gen_zip_fixtures.py#L1) | language `py` | coverage 66.7% | [API index](../index.md)

gen_zip_fixtures.py -- generate the zip test fixtures shipped on the ramdisk.

Two small ZIP archives, built with the host's standard zipfile so the in-OS
extractor is tested against bytes produced by a reference implementation, not
just by its own writer:

  host.zip    a well-formed archive with a directory and two files, proving
              the in-OS extractor interops with host-produced ZIPs.

  hostile.zip an archive whose entry names try to escape the extraction
              root: a traversal ("../escape.txt"), an absolute path
              ("/abs.txt") and a directory marker ("dir/") beside one plain
              file.  The in-OS extractor must create only good.txt, dir/ and
              abs.txt (the absolute name is sanitized to relative) and must
              never create escape.txt.

Timestamps are fixed so the build is reproducible.

## Contents

- **Functions:** [`write_zip`](#write_zip), [`main`](#main)
- **Constants:** [`FIXED_TIME`](#fixed_time)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_tools_gen_zip_fixtures_py__main(["main"])
    n_tools_gen_zip_fixtures_py__write_zip(["write_zip"])
    n_tools_gen_zip_fixtures_py__main --> n_tools_gen_zip_fixtures_py__write_zip
```

## Functions

<a id="write_zip"></a>

### `write_zip`

`function` | [tools/gen_zip_fixtures.py:28](../../tools/gen_zip_fixtures.py#L28)

```python
def write_zip(path, entries)
```

entries: list of (name, data_or_None).  data None marks a directory.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `path` |  |  |  |
| `entries` |  |  |  |

*Called by:* [`main`](#main)

---

<a id="main"></a>

### `main`

`function` | [tools/gen_zip_fixtures.py:42](../../tools/gen_zip_fixtures.py#L42)

```python
def main()
```

*Calls:* [`write_zip`](#write_zip)

---

## Constants

<a id="fixed_time"></a>

### `FIXED_TIME`

`constant` | [tools/gen_zip_fixtures.py:25](../../tools/gen_zip_fixtures.py#L25)

```python
FIXED_TIME = (2000, 1, 1, 0, 0, 0)
```

---
