# `headers/tls_port.h`

> Source: [headers/tls_port.h:1](../../headers/tls_port.h#L1) | language `h` | coverage 2.0% | [API index](../index.md)

Portability shim between the MiniOS kernel and the host-side test

## Contents

- **Functions:** [`these`](#these), [`tls_test_recv`](#tls_test_recv), [`tls_test_recv_timeout`](#tls_test_recv_timeout), [`tls_test_close`](#tls_test_close), [`tls_now_days`](#tls_now_days), [`tls_random`](#tls_random), [`sockets`](#sockets), [`gettimeofday`](#gettimeofday), [`tls_u_recv`](#tls_u_recv), [`tls_u_recv_timeout`](#tls_u_recv_timeout), [`tls_u_close`](#tls_u_close), [`syscall`](#syscall)
- **Macros:** [`TLS_FD_MAX`](#tls_fd_max), [`TLS_PRINTF`](#tls_printf), [`TLS_MALLOC`](#tls_malloc), [`TLS_FREE`](#tls_free), [`TLS_MEMCPY`](#tls_memcpy), [`TLS_MEMSET`](#tls_memset), [`TLS_MEMCMP`](#tls_memcmp), [`TLS_STRLEN`](#tls_strlen), [`TLS_SEND`](#tls_send), [`TLS_RECV`](#tls_recv), [`TLS_RECV_TIMEOUT`](#tls_recv_timeout), [`TLS_CLOSE`](#tls_close), [`TLS_FD_MAX`](#tls_fd_max), [`TLS_PRINTF`](#tls_printf), [`TLS_MALLOC`](#tls_malloc), [`TLS_FREE`](#tls_free), [`TLS_MEMCPY`](#tls_memcpy), [`TLS_MEMSET`](#tls_memset), [`TLS_MEMCMP`](#tls_memcmp), [`TLS_STRLEN`](#tls_strlen), [`TLS_SEND`](#tls_send), [`TLS_RECV`](#tls_recv), [`TLS_RECV_TIMEOUT`](#tls_recv_timeout), [`TLS_CLOSE`](#tls_close), [`TLS_PRINTF`](#tls_printf), [`TLS_MALLOC`](#tls_malloc), [`TLS_FREE`](#tls_free), [`TLS_MEMCPY`](#tls_memcpy), [`TLS_MEMSET`](#tls_memset), [`TLS_MEMCMP`](#tls_memcmp), [`TLS_STRLEN`](#tls_strlen), [`TLS_SEND`](#tls_send), [`TLS_RECV`](#tls_recv), [`TLS_RECV_TIMEOUT`](#tls_recv_timeout), [`TLS_CLOSE`](#tls_close), [`TLS_FD_MAX`](#tls_fd_max)

## Call Graph

Solid arrows stay in this module, dashed arrows leave it.

```mermaid
flowchart LR
    n_headers_tls_port_h__tls_now_days(["tls_now_days"])
    n_kernel_loader_c__time["loader.time"]
    n_headers_tls_port_h__tls_now_days -.-> n_kernel_loader_c__time
```

## Functions

<a id="these"></a>

### `these`

`function` | [headers/tls_port.h:29](../../headers/tls_port.h#L29)

```c
* of these (tls_test.c). */ extern int tls_test_send(int fd, const char *buf, int len);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `c` | `tls_test.` |  |  |

**Returns:** `* of`

---

<a id="tls_test_recv"></a>

### `tls_test_recv`

`function` `extern` | [headers/tls_port.h:31](../../headers/tls_port.h#L31)

```c
extern int tls_test_recv(int fd, char *buf, int len);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |
| `buf` | `char *` |  |  |
| `len` | `int` |  |  |

**Returns:** `int`

---

<a id="tls_test_recv_timeout"></a>

### `tls_test_recv_timeout`

`function` `extern` | [headers/tls_port.h:32](../../headers/tls_port.h#L32)

```c
extern int tls_test_recv_timeout(int fd, char *buf, int len, unsigned long ms);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |
| `buf` | `char *` |  |  |
| `len` | `int` |  |  |
| `ms` | `unsigned long` |  |  |

**Returns:** `int`

---

<a id="tls_test_close"></a>

### `tls_test_close`

`function` `extern` | [headers/tls_port.h:33](../../headers/tls_port.h#L33)

```c
extern void tls_test_close(int fd);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |

---

<a id="tls_now_days"></a>

### `tls_now_days`

`function` `inline` `static` | [headers/tls_port.h:40](../../headers/tls_port.h#L40)

```c
static inline long tls_now_days(void)
```

**Returns:** `long`

*Calls:* [`time`](kernel.loader.c.md#time)

---

<a id="tls_random"></a>

### `tls_random`

`function` `inline` `static` | [headers/tls_port.h:44](../../headers/tls_port.h#L44)

```c
static inline void tls_random(unsigned char *out, unsigned len)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `out` | `unsigned char *` |  |  |
| `len` | `unsigned` |  |  |

---

<a id="sockets"></a>

### `sockets`

`function` | [headers/tls_port.h:62](../../headers/tls_port.h#L62)

```c
* sockets (glibc maps socket/connect/send/recv/poll onto the MiniOS * Linux ABI numbers the kernel implements);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `implements` | `glibc maps socket/connect/send/recv/poll onto the MiniOS * Linux ABI numbers the kernel` |  |  |

**Returns:** `*`

---

<a id="gettimeofday"></a>

### `gettimeofday`

`function` | [headers/tls_port.h:64](../../headers/tls_port.h#L64)

```c
* gettimeofday(96) and entropy from /dev/urandom with a time/pid * fallback. Session slots are indexed by raw OS fd, so TLS_FD_MAX * covers both the MiniOS socket range (100+) and host small fds. */ #
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `96` |  |  |  |

**Returns:** `*`

*Called by:* [`DG_GetTicksMs`](progs.doomgeneric.doomgeneric_xlib.c.md#dg_getticksms), [`tls_now_days`](progs.tls_u.tls_u_port.c.md#tls_now_days)

---

<a id="tls_u_recv"></a>

### `tls_u_recv`

`function` | [headers/tls_port.h:82](../../headers/tls_port.h#L82)

```c
int tls_u_recv(int fd, char *buf, int len);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |
| `buf` | `char *` |  |  |
| `len` | `int` |  |  |

**Returns:** `int`

---

<a id="tls_u_recv_timeout"></a>

### `tls_u_recv_timeout`

`function` | [headers/tls_port.h:83](../../headers/tls_port.h#L83)

```c
int tls_u_recv_timeout(int fd, char *buf, int len, unsigned long ms);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |
| `buf` | `char *` |  |  |
| `len` | `int` |  |  |
| `ms` | `unsigned long` |  |  |

**Returns:** `int`

---

<a id="tls_u_close"></a>

### `tls_u_close`

`function` | [headers/tls_port.h:84](../../headers/tls_port.h#L84)

```c
void tls_u_close(int fd);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |

---

<a id="syscall"></a>

### `syscall`

`function` | [headers/tls_port.h:95](../../headers/tls_port.h#L95)

```c
* the MiniOS DNS syscall (200, invoked sig-0-safe). 0 on success. */ int tls_u_resolve(const char *host, unsigned *ip_out);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `200` |  |  |  |
| `safe` | `invoked sig-0-` |  |  |

**Returns:** `* the MiniOS DNS`

---

## Macros

<a id="tls_fd_max"></a>

### `TLS_FD_MAX`

`macro` | [headers/tls_port.h:18](../../headers/tls_port.h#L18)

```c
#define TLS_FD_MAX
```

---

<a id="tls_printf"></a>

### `TLS_PRINTF`

`macro` | [headers/tls_port.h:20](../../headers/tls_port.h#L20)

```c
#define TLS_PRINTF
```

*Called by:* [`tls_handshake`](net.tls.c.md#tls_handshake), [`tls_recv`](net.tls.c.md#tls_recv)

---

<a id="tls_malloc"></a>

### `TLS_MALLOC`

`macro` | [headers/tls_port.h:21](../../headers/tls_port.h#L21)

```c
#define TLS_MALLOC(n)
```

*Called by:* [`tls_handshake`](net.tls.c.md#tls_handshake), [`tls_x509_verify_chain`](net.tls_x509.c.md#tls_x509_verify_chain)

---

<a id="tls_free"></a>

### `TLS_FREE`

`macro` | [headers/tls_port.h:22](../../headers/tls_port.h#L22)

```c
#define TLS_FREE(p)
```

*Called by:* [`tls_free_fd`](net.tls.c.md#tls_free_fd), [`tls_x509_verify_chain`](net.tls_x509.c.md#tls_x509_verify_chain)

---

<a id="tls_memcpy"></a>

### `TLS_MEMCPY`

`macro` | [headers/tls_port.h:23](../../headers/tls_port.h#L23)

```c
#define TLS_MEMCPY
```

*Called by:* [`exchange`](net.tls.c.md#exchange), [`number`](net.tls.c.md#number), [`tls_handshake`](net.tls.c.md#tls_handshake), [`tls_recv`](net.tls.c.md#tls_recv), [`ecdsa_verify`](net.tls_crypto.c.md#ecdsa_verify), [`hmac_sha256`](net.tls_crypto.c.md#hmac_sha256), [`sha256_update`](net.tls_crypto.c.md#sha256_update), [`tls_prf`](net.tls_crypto.c.md#tls_prf), [`tls_x509_parse_pubkey`](net.tls_x509.c.md#tls_x509_parse_pubkey)

---

<a id="tls_memset"></a>

### `TLS_MEMSET`

`macro` | [headers/tls_port.h:24](../../headers/tls_port.h#L24)

```c
#define TLS_MEMSET
```

*Called by:* [`tls_handshake`](net.tls.c.md#tls_handshake), [`ecdsa_verify`](net.tls_crypto.c.md#ecdsa_verify), [`hmac_sha256`](net.tls_crypto.c.md#hmac_sha256), [`sha256_final`](net.tls_crypto.c.md#sha256_final)

---

<a id="tls_memcmp"></a>

### `TLS_MEMCMP`

`macro` | [headers/tls_port.h:25](../../headers/tls_port.h#L25)

```c
#define TLS_MEMCMP
```

---

<a id="tls_strlen"></a>

### `TLS_STRLEN`

`macro` | [headers/tls_port.h:26](../../headers/tls_port.h#L26)

```c
#define TLS_STRLEN
```

*Called by:* [`tls_handshake`](net.tls.c.md#tls_handshake), [`tls_prf`](net.tls_crypto.c.md#tls_prf)

---

<a id="tls_send"></a>

### `TLS_SEND`

`macro` | [headers/tls_port.h:35](../../headers/tls_port.h#L35)

```c
#define TLS_SEND
```

*Called by:* [`number`](net.tls.c.md#number)

---

<a id="tls_recv"></a>

### `TLS_RECV`

`macro` | [headers/tls_port.h:36](../../headers/tls_port.h#L36)

```c
#define TLS_RECV
```

---

<a id="tls_recv_timeout"></a>

### `TLS_RECV_TIMEOUT`

`macro` | [headers/tls_port.h:37](../../headers/tls_port.h#L37)

```c
#define TLS_RECV_TIMEOUT
```

---

<a id="tls_close"></a>

### `TLS_CLOSE`

`macro` | [headers/tls_port.h:38](../../headers/tls_port.h#L38)

```c
#define TLS_CLOSE
```

---

<a id="tls_fd_max"></a>

### `TLS_FD_MAX`

`macro` | [headers/tls_port.h:71](../../headers/tls_port.h#L71)

```c
#define TLS_FD_MAX
```

---

<a id="tls_printf"></a>

### `TLS_PRINTF`

`macro` | [headers/tls_port.h:73](../../headers/tls_port.h#L73)

```c
#define TLS_PRINTF
```

---

<a id="tls_malloc"></a>

### `TLS_MALLOC`

`macro` | [headers/tls_port.h:74](../../headers/tls_port.h#L74)

```c
#define TLS_MALLOC(n)
```

---

<a id="tls_free"></a>

### `TLS_FREE`

`macro` | [headers/tls_port.h:75](../../headers/tls_port.h#L75)

```c
#define TLS_FREE(p)
```

---

<a id="tls_memcpy"></a>

### `TLS_MEMCPY`

`macro` | [headers/tls_port.h:76](../../headers/tls_port.h#L76)

```c
#define TLS_MEMCPY
```

---

<a id="tls_memset"></a>

### `TLS_MEMSET`

`macro` | [headers/tls_port.h:77](../../headers/tls_port.h#L77)

```c
#define TLS_MEMSET
```

---

<a id="tls_memcmp"></a>

### `TLS_MEMCMP`

`macro` | [headers/tls_port.h:78](../../headers/tls_port.h#L78)

```c
#define TLS_MEMCMP
```

---

<a id="tls_strlen"></a>

### `TLS_STRLEN`

`macro` | [headers/tls_port.h:79](../../headers/tls_port.h#L79)

```c
#define TLS_STRLEN
```

---

<a id="tls_send"></a>

### `TLS_SEND`

`macro` | [headers/tls_port.h:86](../../headers/tls_port.h#L86)

```c
#define TLS_SEND
```

---

<a id="tls_recv"></a>

### `TLS_RECV`

`macro` | [headers/tls_port.h:87](../../headers/tls_port.h#L87)

```c
#define TLS_RECV
```

---

<a id="tls_recv_timeout"></a>

### `TLS_RECV_TIMEOUT`

`macro` | [headers/tls_port.h:88](../../headers/tls_port.h#L88)

```c
#define TLS_RECV_TIMEOUT
```

---

<a id="tls_close"></a>

### `TLS_CLOSE`

`macro` | [headers/tls_port.h:89](../../headers/tls_port.h#L89)

```c
#define TLS_CLOSE
```

---

<a id="tls_printf"></a>

### `TLS_PRINTF`

`macro` | [headers/tls_port.h:103](../../headers/tls_port.h#L103)

```c
#define TLS_PRINTF
```

---

<a id="tls_malloc"></a>

### `TLS_MALLOC`

`macro` | [headers/tls_port.h:104](../../headers/tls_port.h#L104)

```c
#define TLS_MALLOC(n)
```

---

<a id="tls_free"></a>

### `TLS_FREE`

`macro` | [headers/tls_port.h:105](../../headers/tls_port.h#L105)

```c
#define TLS_FREE(p)
```

---

<a id="tls_memcpy"></a>

### `TLS_MEMCPY`

`macro` | [headers/tls_port.h:106](../../headers/tls_port.h#L106)

```c
#define TLS_MEMCPY
```

---

<a id="tls_memset"></a>

### `TLS_MEMSET`

`macro` | [headers/tls_port.h:107](../../headers/tls_port.h#L107)

```c
#define TLS_MEMSET
```

---

<a id="tls_memcmp"></a>

### `TLS_MEMCMP`

`macro` | [headers/tls_port.h:108](../../headers/tls_port.h#L108)

```c
#define TLS_MEMCMP
```

---

<a id="tls_strlen"></a>

### `TLS_STRLEN`

`macro` | [headers/tls_port.h:109](../../headers/tls_port.h#L109)

```c
#define TLS_STRLEN
```

---

<a id="tls_send"></a>

### `TLS_SEND`

`macro` | [headers/tls_port.h:111](../../headers/tls_port.h#L111)

```c
#define TLS_SEND
```

---

<a id="tls_recv"></a>

### `TLS_RECV`

`macro` | [headers/tls_port.h:112](../../headers/tls_port.h#L112)

```c
#define TLS_RECV
```

---

<a id="tls_recv_timeout"></a>

### `TLS_RECV_TIMEOUT`

`macro` | [headers/tls_port.h:113](../../headers/tls_port.h#L113)

```c
#define TLS_RECV_TIMEOUT
```

---

<a id="tls_close"></a>

### `TLS_CLOSE`

`macro` | [headers/tls_port.h:114](../../headers/tls_port.h#L114)

```c
#define TLS_CLOSE
```

---

<a id="tls_fd_max"></a>

### `TLS_FD_MAX`

`macro` | [headers/tls_port.h:115](../../headers/tls_port.h#L115)

```c
#define TLS_FD_MAX
```

---
