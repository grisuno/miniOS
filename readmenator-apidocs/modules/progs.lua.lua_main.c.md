# `progs/lua/lua_main.c`

> Source: [progs/lua/lua_main.c:1](../../progs/lua/lua_main.c#L1) | language `c` | coverage 0.0% | [API index](../index.md)

## Contents

- **Functions:** [`module`](#module), [`main`](#main)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_progs_lua_lua_main_c__main(["main"])
    n_tools_minios_hyper_py__repl["minios_hyper.repl"]
    n_progs_lua_lua_main_c__main -.-> n_tools_minios_hyper_py__repl
```

## Functions

<a id="module"></a>

### `module`

`function` | [progs/lua/lua_main.c:5](../../progs/lua/lua_main.c#L5)

```c
* C module (minios.c) can be registered globally before any script runs: * `minios.run(...)`, `minios.time_ms()`, etc. are available as a plain global * table, exactly like `import minios` in MicroPyt
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `minios.` |  |  |

**Returns:** `* C`

---

<a id="main"></a>

### `main`

`function` | [progs/lua/lua_main.c:105](../../progs/lua/lua_main.c#L105)

```c
int main(int argc, char **argv)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `argv` | `char **` |  |  |

**Returns:** `int`

*Calls:* [`repl`](tools.minios_hyper.py.md#repl)

---
