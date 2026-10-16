# `progs/src/lxnet.c`

> Source: [progs/src/lxnet.c:1](../../progs/src/lxnet.c#L1) | language `c` | coverage 11.1% | [API index](../index.md)

## Contents

- **Functions:** [`main`](#main)
- **Macros:** [`_GNU_SOURCE`](#_gnu_source), [`LXNET_WAIT_MS`](#lxnet_wait_ms), [`LXNET_BUF`](#lxnet_buf), [`LXNET_UDP_MSG`](#lxnet_udp_msg), [`LXNET_TCP_MSG`](#lxnet_tcp_msg), [`LXNET_LOOPBACK`](#lxnet_loopback), [`LXNET_IP_UNKNOWN`](#lxnet_ip_unknown)

## Functions

<a id="main"></a>

### `main`

`function` | [progs/src/lxnet.c:280](../../progs/src/lxnet.c#L280)

```c
int main(int argc, char **argv)
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `argc` | `int` |  |  |
| `argv` | `char **` |  |  |

**Returns:** `int`

---

## Macros

<a id="_gnu_source"></a>

### `_GNU_SOURCE`

`macro` | [progs/src/lxnet.c:24](../../progs/src/lxnet.c#L24)

```c
#define _GNU_SOURCE
```

lxnet.c - Linux socket ABI probe (FreeDom readiness step 6, docs/spec/network.md "Linux socket ABI").

Exercises what static glibc's resolver, libcurl and OpenSSL need from the
socket layer, against the host fixture tools/test_net_fixture.py (UDP and
TCP echo on one port, reached as 10.0.2.2 through QEMU slirp): datagram
sockets with sendto/recvfrom and connect/send/recv, socket type flags,
non-blocking connect completed through poll(POLLOUT) and SO_ERROR,
setsockopt/getsockopt/getsockname/getpeername, send flags MSG_NOSIGNAL and
MSG_DONTWAIT, read/write on a socket, AF_INET6 refusal, and getaddrinfo
through /etc/hosts.

Usage: lxnet <host-ip> <port>
Prints "lxnet: <check> ok" or "lxnet: <check> FAIL <detail>", then
"lxnet: all ok" with exit 0, or "lxnet: <n> failed" with exit 1.

Diagnostic mode: lxnet --dial <host> <port>
Resolves host through getaddrinfo (resolv.conf, hosts, nsswitch.conf)
and dials the first IPv4 answer with libcurl's sequence (non-blocking
connect, poll for POLLOUT, SO_ERROR). Prints "lxnet: resolve <host> ->
<ip>" or the resolver error, then "lxnet: dial ok" with exit 0 or
"lxnet: dial FAIL <reason>" with exit 1.

---

<a id="lxnet_wait_ms"></a>

### `LXNET_WAIT_MS`

`macro` | [progs/src/lxnet.c:40](../../progs/src/lxnet.c#L40)

```c
#define LXNET_WAIT_MS
```

---

<a id="lxnet_buf"></a>

### `LXNET_BUF`

`macro` | [progs/src/lxnet.c:41](../../progs/src/lxnet.c#L41)

```c
#define LXNET_BUF
```

---

<a id="lxnet_udp_msg"></a>

### `LXNET_UDP_MSG`

`macro` | [progs/src/lxnet.c:42](../../progs/src/lxnet.c#L42)

```c
#define LXNET_UDP_MSG
```

---

<a id="lxnet_tcp_msg"></a>

### `LXNET_TCP_MSG`

`macro` | [progs/src/lxnet.c:43](../../progs/src/lxnet.c#L43)

```c
#define LXNET_TCP_MSG
```

---

<a id="lxnet_loopback"></a>

### `LXNET_LOOPBACK`

`macro` | [progs/src/lxnet.c:44](../../progs/src/lxnet.c#L44)

```c
#define LXNET_LOOPBACK
```

---

<a id="lxnet_ip_unknown"></a>

### `LXNET_IP_UNKNOWN`

`macro` | [progs/src/lxnet.c:45](../../progs/src/lxnet.c#L45)

```c
#define LXNET_IP_UNKNOWN
```

---
