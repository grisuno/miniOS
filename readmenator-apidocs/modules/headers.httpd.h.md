# `headers/httpd.h`

> Source: [headers/httpd.h:1](../../headers/httpd.h#L1) | language `h` | coverage 30.0% | [API index](../index.md)

Docstring: httpd.h -- Minimal static HTTP/1.0 server contract.

## Contents

- **Functions:** [`httpd_ctype`](#httpd_ctype), [`httpd_header`](#httpd_header)
- **Macros:** [`HTTPD_MAX_PATH`](#httpd_max_path), [`HTTPD_MAX_REQ`](#httpd_max_req), [`HTTPD_HEAD_MAX`](#httpd_head_max), [`HTTPD_ERR_BOUND`](#httpd_err_bound), [`HTTPD_ERR_METHOD`](#httpd_err_method), [`HTTPD_ERR_PATH`](#httpd_err_path), [`HTTPD_ERR_VERSION`](#httpd_err_version)

## Functions

<a id="httpd_ctype"></a>

### `httpd_ctype`

`function` `const` `inline` `static` | [headers/httpd.h:28](../../headers/httpd.h#L28)

```c
static inline const char *httpd_ctype(const char *path)
```

Docstring: Content type by file suffix.

Unknown suffixes serve as application/octet-stream, never refused. Null path reads as octet.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `path` | `char *` |  |  |

**Returns:** `char *`

*Called by:* [`HTTPD_IO_CHUNK`](kernel.shell.c.md#httpd_io_chunk)

---

<a id="httpd_header"></a>

### `httpd_header`

`function` `inline` `static` | [headers/httpd.h:121](../../headers/httpd.h#L121)

```c
static inline int httpd_header(int code, const char *reason, const char *ctype, unsigned long body_len, char *out, unsigned cap)
```

Docstring: Emit a response head into out.

Returns the head length, or HTTPD_ERR_BOUND past cap. body_len is the exact Content-Length; the caller streams the body after the head.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `code` | `int` |  |  |
| `reason` | `char *` |  |  |
| `ctype` | `char *` |  |  |
| `body_len` | `unsigned long` |  |  |
| `out` | `char *` |  |  |
| `cap` | `unsigned` |  |  |

**Returns:** `int`

*Called by:* [`HTTPD_IO_CHUNK`](kernel.shell.c.md#httpd_io_chunk)

---

## Macros

<a id="httpd_max_path"></a>

### `HTTPD_MAX_PATH`

`macro` | [headers/httpd.h:17](../../headers/httpd.h#L17)

```c
#define HTTPD_MAX_PATH
```

---

<a id="httpd_max_req"></a>

### `HTTPD_MAX_REQ`

`macro` | [headers/httpd.h:18](../../headers/httpd.h#L18)

```c
#define HTTPD_MAX_REQ
```

---

<a id="httpd_head_max"></a>

### `HTTPD_HEAD_MAX`

`macro` | [headers/httpd.h:19](../../headers/httpd.h#L19)

```c
#define HTTPD_HEAD_MAX
```

---

<a id="httpd_err_bound"></a>

### `HTTPD_ERR_BOUND`

`macro` | [headers/httpd.h:21](../../headers/httpd.h#L21)

```c
#define HTTPD_ERR_BOUND
```

---

<a id="httpd_err_method"></a>

### `HTTPD_ERR_METHOD`

`macro` | [headers/httpd.h:22](../../headers/httpd.h#L22)

```c
#define HTTPD_ERR_METHOD
```

---

<a id="httpd_err_path"></a>

### `HTTPD_ERR_PATH`

`macro` | [headers/httpd.h:23](../../headers/httpd.h#L23)

```c
#define HTTPD_ERR_PATH
```

---

<a id="httpd_err_version"></a>

### `HTTPD_ERR_VERSION`

`macro` | [headers/httpd.h:24](../../headers/httpd.h#L24)

```c
#define HTTPD_ERR_VERSION
```

---
