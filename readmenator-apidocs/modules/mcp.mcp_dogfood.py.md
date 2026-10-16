# `mcp.mcp_dogfood`

> Source: [mcp/mcp_dogfood.py:1](../../mcp/mcp_dogfood.py#L1) | language `py` | coverage 14.3% | [API index](../index.md)

Dogfood: drive minios_mcp.py over stdio JSON-RPC and install the freedom addon from a git repo, then browse with the installed binary.

Stdlib only. Usage: python3 mcp_dogfood.py <addons-dir>

## Contents

- **Classes:** [`Client`](#client)
- **Functions:** [`main`](#main)
- **Constants:** [`HERE`](#here), [`TMO`](#tmo)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_mcp_mcp_dogfood_py__main(["main"])
    n_mcp_mcp_dogfood_py__Client___init__(["Client.__init__"])
    n_mcp_mcp_dogfood_py__Client_tool(["Client.tool"])
    n_mcp_mcp_dbg_driver_py__Client_request["mcp_dbg_driver.Client.request"]
    n_mcp_mcp_dbg_driver_py__Client_close["mcp_dbg_driver.Client.close"]
    n_mcp_mcp_dbg_driver_py__Client_tool["mcp_dbg_driver.Client.tool"]
    n_mcp_mcp_dogfood_py__main --> n_mcp_mcp_dogfood_py__Client___init__
    n_mcp_mcp_dogfood_py__Client_tool -.-> n_mcp_mcp_dbg_driver_py__Client_request
    n_mcp_mcp_dogfood_py__main -.-> n_mcp_mcp_dbg_driver_py__Client_close
    n_mcp_mcp_dogfood_py__main -.-> n_mcp_mcp_dbg_driver_py__Client_request
    n_mcp_mcp_dogfood_py__main -.-> n_mcp_mcp_dbg_driver_py__Client_tool
```

## Classes

<a id="client"></a>

### `Client`

`class` | [mcp/mcp_dogfood.py:19](../../mcp/mcp_dogfood.py#L19)

```python
class Client
```

**Members**

| Member | Kind | Summary |
|---|---|---|
| [`__init__`](#client-__init__) | constructor |  |
| [`request`](#client-request) | method |  |
| [`tool`](#client-tool) | method |  |
| [`close`](#client-close) | method |  |

<a id="client-__init__"></a>

#### `Client.__init__`

`constructor` | [mcp/mcp_dogfood.py:20](../../mcp/mcp_dogfood.py#L20)

```python
def __init__(self, addons_dir)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `addons_dir` |  |  |  |

*Called by:* [`main`](#main)

<a id="client-request"></a>

#### `Client.request`

`method` | [mcp/mcp_dogfood.py:40](../../mcp/mcp_dogfood.py#L40)

```python
def request(self, method, params=None)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `method` |  |  |  |
| `params` |  | `None` |  |

**Raises**

- `TimeoutError`: (raised in the body, not documented)

<a id="client-tool"></a>

#### `Client.tool`

`method` | [mcp/mcp_dogfood.py:58](../../mcp/mcp_dogfood.py#L58)

```python
def tool(self, name, params=None)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `name` |  |  |  |
| `params` |  | `None` |  |

**Raises**

- `AssertionError`: (raised in the body, not documented)

*Calls:* [`Client.request`](mcp.mcp_dbg_driver.py.md#client-request)

<a id="client-close"></a>

#### `Client.close`

`method` | [mcp/mcp_dogfood.py:68](../../mcp/mcp_dogfood.py#L68)

```python
def close(self)
```

---

## Functions

<a id="main"></a>

### `main`

`function` | [mcp/mcp_dogfood.py:78](../../mcp/mcp_dogfood.py#L78)

```python
def main()
```

*Calls:* [`Client.close`](mcp.mcp_dbg_driver.py.md#client-close), [`Client.request`](mcp.mcp_dbg_driver.py.md#client-request), [`Client.tool`](mcp.mcp_dbg_driver.py.md#client-tool), [`Client.__init__`](#client-__init__)

---

## Constants

<a id="here"></a>

### `HERE`

`constant` | [mcp/mcp_dogfood.py:15](../../mcp/mcp_dogfood.py#L15)

```python
HERE = os.path.dirname(os.path.abspath(__file__))
```

---

<a id="tmo"></a>

### `TMO`

`constant` | [mcp/mcp_dogfood.py:16](../../mcp/mcp_dogfood.py#L16)

```python
TMO = 240.0
```

---
