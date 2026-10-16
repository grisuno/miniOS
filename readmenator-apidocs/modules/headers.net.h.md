# `headers/net.h`

> Source: [headers/net.h:1](../../headers/net.h#L1) | language `h` | coverage 21.8% | [API index](../index.md)

## Contents

- **Functions:** [`ring`](#ring), [`net_sys_is_socket`](#net_sys_is_socket), [`net_sys_setsockopt`](#net_sys_setsockopt), [`net_sys_getsockopt`](#net_sys_getsockopt), [`net_sys_getsockname`](#net_sys_getsockname), [`net_sys_getpeername`](#net_sys_getpeername), [`net_sys_sendmsg`](#net_sys_sendmsg), [`net_sys_sendmmsg`](#net_sys_sendmmsg), [`net_sys_fcntl`](#net_sys_fcntl), [`net_sys_ioctl`](#net_sys_ioctl), [`net_register_symbols`](#net_register_symbols), [`net_cmd_status`](#net_cmd_status), [`net_cmd_ping`](#net_cmd_ping), [`net_get_addrs`](#net_get_addrs), [`net_cmd_dns`](#net_cmd_dns), [`net_open`](#net_open), [`net_connect`](#net_connect), [`net_send`](#net_send), [`net_recv`](#net_recv), [`net_recv_timeout`](#net_recv_timeout), [`net_close`](#net_close), [`demux`](#demux), [`net_accept_nb`](#net_accept_nb), [`net_accept`](#net_accept), [`net_sock_state`](#net_sock_state), [`net_sock_seq`](#net_sock_seq), [`net_test_inject_tcp`](#net_test_inject_tcp), [`net_sys_socket`](#net_sys_socket), [`net_sys_connect`](#net_sys_connect), [`net_sys_bind`](#net_sys_bind), [`net_sys_listen`](#net_sys_listen), [`net_sys_accept`](#net_sys_accept), [`net_sys_sendto`](#net_sys_sendto), [`net_sys_recvfrom`](#net_sys_recvfrom), [`net_sys_shutdown`](#net_sys_shutdown), [`net_sys_close`](#net_sys_close), [`net_sys_poll`](#net_sys_poll), [`net_sys_dns`](#net_sys_dns), [`net_time_ms`](#net_time_ms), [`net_rx_handle_frame`](#net_rx_handle_frame), [`stack`](#stack), [`tls_free_fd`](#tls_free_fd)
- **Macros:** [`NET_IP_ADDR`](#net_ip_addr), [`NET_NETMASK`](#net_netmask), [`NET_GATEWAY`](#net_gateway), [`NET_DNS`](#net_dns), [`NET_POLLIN`](#net_pollin), [`NET_POLLOUT`](#net_pollout), [`NET_POLLERR`](#net_pollerr), [`NET_POLLHUP`](#net_pollhup), [`NET_POLLNVAL`](#net_pollnval), [`NET_PCI_VENDOR`](#net_pci_vendor), [`NET_PCI_DEVICE`](#net_pci_device), [`NET_RX_BUF_LEN`](#net_rx_buf_len), [`NET_RX_ALIGN`](#net_rx_align), [`NET_RX_RING_PAD`](#net_rx_ring_pad), [`NET_RCR`](#net_rcr), [`NET_MAX_FRAME`](#net_max_frame), [`NET_TX_SLOTS`](#net_tx_slots), [`NET_ETH_ALEN`](#net_eth_alen), [`NET_ETHERTYPE_IP`](#net_ethertype_ip), [`NET_ETHERTYPE_ARP`](#net_ethertype_arp), [`NET_ETHERTYPE_IPV6`](#net_ethertype_ipv6), [`NET_PROTO_ICMP`](#net_proto_icmp), [`NET_PROTO_TCP`](#net_proto_tcp), [`NET_PROTO_UDP`](#net_proto_udp), [`NET_ARP_CACHE`](#net_arp_cache), [`NET_ARP_REQUEST`](#net_arp_request), [`NET_ARP_REPLY`](#net_arp_reply), [`NET_TCP_MSS`](#net_tcp_mss), [`NET_TCP_WINDOW`](#net_tcp_window), [`NET_SOCK_RX_BUF`](#net_sock_rx_buf), [`NET_RX_RING_SIZE`](#net_rx_ring_size), [`NET_SOCKETS`](#net_sockets), [`NET_DNS_PORT`](#net_dns_port), [`NET_EPHEMERAL_MIN`](#net_ephemeral_min), [`NET_DNS_TRIES`](#net_dns_tries), [`NET_DNS_TMO_MS`](#net_dns_tmo_ms), [`NET_CONNECT_TMO_S`](#net_connect_tmo_s), [`NET_RETRY_MS`](#net_retry_ms), [`NET_ACCEPT_TMO_MS`](#net_accept_tmo_ms), [`NET_TX_MAX`](#net_tx_max), [`NET_FD_BASE`](#net_fd_base), [`NET_UDP_SOCKETS`](#net_udp_sockets), [`NET_UDP_QUEUE`](#net_udp_queue), [`NET_UDP_DGRAM_MAX`](#net_udp_dgram_max), [`NET_UDP_FD_BASE`](#net_udp_fd_base), [`NET_UDP_EPHEMERAL_MIN`](#net_udp_ephemeral_min), [`NET_UDP_EPHEMERAL_MAX`](#net_udp_ephemeral_max), [`NET_SOCKADDR_IN_LEN`](#net_sockaddr_in_len), [`NET_MSGHDR_LEN`](#net_msghdr_len), [`NET_MMSGHDR_LEN`](#net_mmsghdr_len), [`NET_MSGHDR_NAME_OFF`](#net_msghdr_name_off), [`NET_MSGHDR_NAMELEN_OFF`](#net_msghdr_namelen_off), [`NET_MSGHDR_IOV_OFF`](#net_msghdr_iov_off), [`NET_MSGHDR_IOVLEN_OFF`](#net_msghdr_iovlen_off), [`NET_MMSGHDR_LEN_OFF`](#net_mmsghdr_len_off), [`NET_IOV_LEN`](#net_iov_len), [`NET_IOV_MAX`](#net_iov_max), [`NET_MMSG_MAX`](#net_mmsg_max)
- **Variables:** [`net_rx_dropped`](#net_rx_dropped), [`net6_rx_dropped`](#net6_rx_dropped)

## Functions

<a id="ring"></a>

### `ring`

`function` | [headers/net.h:58](../../headers/net.h#L58)

```c
* ring (below) is the rtl8139's 8 KB hardware ring, unrelated. */ #define NET_SOCK_RX_BUF 16384 #define NET_RX_RING_SIZE 8192 #define NET_SOCKETS 16 #define NET_DNS_PORT 53 #define NET_EPHEMERAL_MIN 4
```

**Returns:** `*`

*Called by:* [`vga_fb_init`](kernel.vga_fb.c.md#vga_fb_init)

---

<a id="net_sys_is_socket"></a>

### `net_sys_is_socket`

`function` | [headers/net.h:101](../../headers/net.h#L101)

```c
int net_sys_is_socket(long fd);
```

Linux socket ABI entry points (kernel/syscalls.c routes to them).

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |

**Returns:** `int`

*Called by:* [`FIONREAD`](kernel.syscalls.c.md#fionread)

---

<a id="net_sys_setsockopt"></a>

### `net_sys_setsockopt`

`function` | [headers/net.h:102](../../headers/net.h#L102)

```c
long net_sys_setsockopt(long fd, long level, long name, long val, long len);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |
| `level` | `long` |  |  |
| `name` | `long` |  |  |
| `val` | `long` |  |  |
| `len` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_getsockopt"></a>

### `net_sys_getsockopt`

`function` | [headers/net.h:103](../../headers/net.h#L103)

```c
long net_sys_getsockopt(long fd, long level, long name, long val, long lenp);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |
| `level` | `long` |  |  |
| `name` | `long` |  |  |
| `val` | `long` |  |  |
| `lenp` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_getsockname"></a>

### `net_sys_getsockname`

`function` | [headers/net.h:104](../../headers/net.h#L104)

```c
long net_sys_getsockname(long fd, long addr, long lenp);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |
| `addr` | `long` |  |  |
| `lenp` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_getpeername"></a>

### `net_sys_getpeername`

`function` | [headers/net.h:105](../../headers/net.h#L105)

```c
long net_sys_getpeername(long fd, long addr, long lenp);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |
| `addr` | `long` |  |  |
| `lenp` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_sendmsg"></a>

### `net_sys_sendmsg`

`function` | [headers/net.h:106](../../headers/net.h#L106)

```c
long net_sys_sendmsg(long fd, long msg, long flags);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |
| `msg` | `long` |  |  |
| `flags` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_sendmmsg"></a>

### `net_sys_sendmmsg`

`function` | [headers/net.h:107](../../headers/net.h#L107)

```c
long net_sys_sendmmsg(long fd, long vec, long vlen, long flags);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |
| `vec` | `long` |  |  |
| `vlen` | `long` |  |  |
| `flags` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_fcntl"></a>

### `net_sys_fcntl`

`function` | [headers/net.h:108](../../headers/net.h#L108)

```c
long net_sys_fcntl(long fd, long cmd, long arg);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |
| `cmd` | `long` |  |  |
| `arg` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_ioctl"></a>

### `net_sys_ioctl`

`function` | [headers/net.h:109](../../headers/net.h#L109)

```c
long net_sys_ioctl(long fd, long req, long arg);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |
| `req` | `long` |  |  |
| `arg` | `long` |  |  |

**Returns:** `long`

*Called by:* [`FIONREAD`](kernel.syscalls.c.md#fionread)

---

<a id="net_register_symbols"></a>

### `net_register_symbols`

`function` | [headers/net.h:110](../../headers/net.h#L110)

```c
void net_register_symbols(void);
```

---

<a id="net_cmd_status"></a>

### `net_cmd_status`

`function` | [headers/net.h:113](../../headers/net.h#L113)

```c
void net_cmd_status(void);
```

Shell commands

---

<a id="net_cmd_ping"></a>

### `net_cmd_ping`

`function` | [headers/net.h:114](../../headers/net.h#L114)

```c
void net_cmd_ping(const char *ip_text);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `ip_text` | `char *` |  |  |

---

<a id="net_get_addrs"></a>

### `net_get_addrs`

`function` | [headers/net.h:115](../../headers/net.h#L115)

```c
void net_get_addrs(unsigned char mac_out[NET_ETH_ALEN], unsigned char ip_out[4]);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `NET_ETH_ALEN` | `unsigned char mac_out[ ]` |  |  |
| `ip_out` | `unsigned char [4]` |  |  |

---

<a id="net_cmd_dns"></a>

### `net_cmd_dns`

`function` | [headers/net.h:116](../../headers/net.h#L116)

```c
void net_cmd_dns(const char *host);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `host` | `char *` |  |  |

---

<a id="net_open"></a>

### `net_open`

`function` | [headers/net.h:119](../../headers/net.h#L119)

```c
int net_open(void);
```

Libc-style API for ET_REL programs

**Returns:** `int`

---

<a id="net_connect"></a>

### `net_connect`

`function` | [headers/net.h:120](../../headers/net.h#L120)

```c
int net_connect(const char *host, unsigned short port);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `host` | `char *` |  |  |
| `port` | `unsigned short` |  |  |

**Returns:** `int`

---

<a id="net_send"></a>

### `net_send`

`function` | [headers/net.h:121](../../headers/net.h#L121)

```c
int net_send(int fd, const char *buf, int len);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |
| `buf` | `char *` |  |  |
| `len` | `int` |  |  |

**Returns:** `int`

*Called by:* [`HTTPD_IO_CHUNK`](kernel.shell.c.md#httpd_io_chunk)

---

<a id="net_recv"></a>

### `net_recv`

`function` | [headers/net.h:122](../../headers/net.h#L122)

```c
int net_recv(int fd, char *buf, int len);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |
| `buf` | `char *` |  |  |
| `len` | `int` |  |  |

**Returns:** `int`

---

<a id="net_recv_timeout"></a>

### `net_recv_timeout`

`function` | [headers/net.h:124](../../headers/net.h#L124)

```c
int net_recv_timeout(int fd, char *buf, int len, unsigned long timeout_ms);
```

Blocking receive with a deadline: like net_recv, but -1 on timeout.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |
| `buf` | `char *` |  |  |
| `len` | `int` |  |  |
| `timeout_ms` | `unsigned long` |  |  |

**Returns:** `int`

*Called by:* [`HTTPD_IO_CHUNK`](kernel.shell.c.md#httpd_io_chunk)

---

<a id="net_close"></a>

### `net_close`

`function` | [headers/net.h:125](../../headers/net.h#L125)

```c
void net_close(int fd);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |

---

<a id="demux"></a>

### `demux`

`function` | [headers/net.h:131](../../headers/net.h#L131)

```c
* segment through the production demux (httpd selftest). */ int net_listen(unsigned short port);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `selftest` | `httpd` |  |  |

**Returns:** `* segment through the production`

---

<a id="net_accept_nb"></a>

### `net_accept_nb`

`function` | [headers/net.h:133](../../headers/net.h#L133)

```c
int net_accept_nb(int fd);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |

**Returns:** `int`

---

<a id="net_accept"></a>

### `net_accept`

`function` | [headers/net.h:134](../../headers/net.h#L134)

```c
int net_accept(int fd, unsigned long timeout_ms);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |
| `timeout_ms` | `unsigned long` |  |  |

**Returns:** `int`

*Called by:* [`net_sys_accept`](net.net.c.md#net_sys_accept), [`polling`](net.net.c.md#polling)

---

<a id="net_sock_state"></a>

### `net_sock_state`

`function` | [headers/net.h:135](../../headers/net.h#L135)

```c
int net_sock_state(int fd);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |

**Returns:** `int`

---

<a id="net_sock_seq"></a>

### `net_sock_seq`

`function` | [headers/net.h:136](../../headers/net.h#L136)

```c
int net_sock_seq(int fd, unsigned *seq_out, unsigned *ack_out);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |
| `seq_out` | `unsigned *` |  |  |
| `ack_out` | `unsigned *` |  |  |

**Returns:** `int`

---

<a id="net_test_inject_tcp"></a>

### `net_test_inject_tcp`

`function` | [headers/net.h:137](../../headers/net.h#L137)

```c
int net_test_inject_tcp(const unsigned char peer[4], unsigned short pport, unsigned short lport, unsigned char flags, unsigned int seq, unsigned int ack, const unsigned char *data, unsigned datalen);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `peer` | `unsigned char [4]` |  |  |
| `pport` | `unsigned short` |  |  |
| `lport` | `unsigned short` |  |  |
| `flags` | `unsigned char` |  |  |
| `seq` | `unsigned int` |  |  |
| `ack` | `unsigned int` |  |  |
| `data` | `unsigned char *` |  |  |
| `datalen` | `unsigned` |  |  |

**Returns:** `int`

---

<a id="net_sys_socket"></a>

### `net_sys_socket`

`function` | [headers/net.h:142](../../headers/net.h#L142)

```c
long net_sys_socket(long a1, long a2, long a3);
```

Linux syscall ABI (sockaddr_in layout matches Linux)

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `a1` | `long` |  |  |
| `a2` | `long` |  |  |
| `a3` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_connect"></a>

### `net_sys_connect`

`function` | [headers/net.h:143](../../headers/net.h#L143)

```c
long net_sys_connect(long fd, long sockaddr, long addrlen);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |
| `sockaddr` | `long` |  |  |
| `addrlen` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_bind"></a>

### `net_sys_bind`

`function` | [headers/net.h:144](../../headers/net.h#L144)

```c
long net_sys_bind(long fd, long sockaddr, long addrlen);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |
| `sockaddr` | `long` |  |  |
| `addrlen` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_listen"></a>

### `net_sys_listen`

`function` | [headers/net.h:145](../../headers/net.h#L145)

```c
long net_sys_listen(long fd, long backlog);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |
| `backlog` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_accept"></a>

### `net_sys_accept`

`function` | [headers/net.h:146](../../headers/net.h#L146)

```c
long net_sys_accept(long fd, long sockaddr, long addrlen);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |
| `sockaddr` | `long` |  |  |
| `addrlen` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_sendto"></a>

### `net_sys_sendto`

`function` | [headers/net.h:147](../../headers/net.h#L147)

```c
long net_sys_sendto(long fd, long buf, long len, long flags, long to, long tolen);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |
| `buf` | `long` |  |  |
| `len` | `long` |  |  |
| `flags` | `long` |  |  |
| `to` | `long` |  |  |
| `tolen` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_recvfrom"></a>

### `net_sys_recvfrom`

`function` | [headers/net.h:148](../../headers/net.h#L148)

```c
long net_sys_recvfrom(long fd, long buf, long len, long flags, long from, long fromlen);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |
| `buf` | `long` |  |  |
| `len` | `long` |  |  |
| `flags` | `long` |  |  |
| `from` | `long` |  |  |
| `fromlen` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_shutdown"></a>

### `net_sys_shutdown`

`function` | [headers/net.h:149](../../headers/net.h#L149)

```c
long net_sys_shutdown(long fd, long how);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |
| `how` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_close"></a>

### `net_sys_close`

`function` | [headers/net.h:150](../../headers/net.h#L150)

```c
long net_sys_close(long fd);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_poll"></a>

### `net_sys_poll`

`function` | [headers/net.h:151](../../headers/net.h#L151)

```c
long net_sys_poll(long fds, long nfds, long timeout_ms);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fds` | `long` |  |  |
| `nfds` | `long` |  |  |
| `timeout_ms` | `long` |  |  |

**Returns:** `long`

---

<a id="net_sys_dns"></a>

### `net_sys_dns`

`function` | [headers/net.h:152](../../headers/net.h#L152)

```c
long net_sys_dns(long host);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `host` | `long` |  |  |

**Returns:** `long`

---

<a id="net_time_ms"></a>

### `net_time_ms`

`function` | [headers/net.h:155](../../headers/net.h#L155)

```c
unsigned long net_time_ms(void);
```

Milliseconds since net_init (PIT-calibrated TSC).

**Returns:** `unsigned long`

*Called by:* [`net_sys_connect`](net.net.c.md#net_sys_connect), [`net_sys_poll`](net.net.c.md#net_sys_poll), [`polling`](net.net.c.md#polling), [`RTL_TX_YIELD_EVERY`](net.rtl8139.c.md#rtl_tx_yield_every), [`deleted`](net.rtl8139.c.md#deleted), [`rtl_send`](net.rtl8139.c.md#rtl_send), [`tls_random`](net.tls.c.md#tls_random)

---

<a id="net_rx_handle_frame"></a>

### `net_rx_handle_frame`

`function` | [headers/net.h:159](../../headers/net.h#L159)

```c
void net_rx_handle_frame(const unsigned char *frame, unsigned len);
```

Demux entry point the rtl8139 driver (rtl8139.c) calls for every frame drained from the RX ring; lives in net.c.

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `frame` | `unsigned char *` |  |  |
| `len` | `unsigned` |  |  |

*Called by:* [`vnet_poll`](drivers.virtio_net.c.md#vnet_poll)

---

<a id="stack"></a>

### `stack`

`function` | [headers/net.h:162](../../headers/net.h#L162)

```c
* the stack (dropped fragments);
```

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fragments` | `dropped` |  |  |

**Returns:** `* the`

---

<a id="tls_free_fd"></a>

### `tls_free_fd`

`function` | [headers/net.h:170](../../headers/net.h#L170)

```c
void tls_free_fd(int fd);
```

TLS sessions attached to socket fds (tls.c); net_sys_close frees them.

With MINIOS_NO_TLS the engine is unlinked and tls.h carries the inline * no-op; this declaration would collide with it, so it is omitted. ifndef MINIOS_NO_TLS

**Parameters**

| Name | Type | Default | Description |
|---|---|---|---|
| `fd` | `int` |  |  |

*Called by:* [`net_sys_close`](net.net.c.md#net_sys_close)

---

## Macros

<a id="net_ip_addr"></a>

### `NET_IP_ADDR`

`macro` | [headers/net.h:5](../../headers/net.h#L5)

```c
#define NET_IP_ADDR
```

========== Fixed slirp configuration (QEMU -nic user) ==========

---

<a id="net_netmask"></a>

### `NET_NETMASK`

`macro` | [headers/net.h:6](../../headers/net.h#L6)

```c
#define NET_NETMASK
```

---

<a id="net_gateway"></a>

### `NET_GATEWAY`

`macro` | [headers/net.h:7](../../headers/net.h#L7)

```c
#define NET_GATEWAY
```

---

<a id="net_dns"></a>

### `NET_DNS`

`macro` | [headers/net.h:8](../../headers/net.h#L8)

```c
#define NET_DNS
```

---

<a id="net_pollin"></a>

### `NET_POLLIN`

`macro` | [headers/net.h:12](../../headers/net.h#L12)

```c
#define NET_POLLIN
```

Linux poll(2) event bits (struct pollfd), shared by net_sys_poll and kfd_poll_revents.

---

<a id="net_pollout"></a>

### `NET_POLLOUT`

`macro` | [headers/net.h:13](../../headers/net.h#L13)

```c
#define NET_POLLOUT
```

---

<a id="net_pollerr"></a>

### `NET_POLLERR`

`macro` | [headers/net.h:14](../../headers/net.h#L14)

```c
#define NET_POLLERR
```

---

<a id="net_pollhup"></a>

### `NET_POLLHUP`

`macro` | [headers/net.h:15](../../headers/net.h#L15)

```c
#define NET_POLLHUP
```

---

<a id="net_pollnval"></a>

### `NET_POLLNVAL`

`macro` | [headers/net.h:16](../../headers/net.h#L16)

```c
#define NET_POLLNVAL
```

---

<a id="net_pci_vendor"></a>

### `NET_PCI_VENDOR`

`macro` | [headers/net.h:19](../../headers/net.h#L19)

```c
#define NET_PCI_VENDOR
```

========== rtl8139 ==========

---

<a id="net_pci_device"></a>

### `NET_PCI_DEVICE`

`macro` | [headers/net.h:20](../../headers/net.h#L20)

```c
#define NET_PCI_DEVICE
```

---

<a id="net_rx_buf_len"></a>

### `NET_RX_BUF_LEN`

`macro` | [headers/net.h:26](../../headers/net.h#L26)

```c
#define NET_RX_BUF_LEN
```

QEMU masks the RCR ring-size bits (11-12) out of writes, so its legacy receive ring is always 8 KB.

The guest ring must match: with a larger ring the guest read pointer and QEMU's 8 KB write wrap disagree and the tail of every frame that crosses 8192 is lost.

---

<a id="net_rx_align"></a>

### `NET_RX_ALIGN`

`macro` | [headers/net.h:27](../../headers/net.h#L27)

```c
#define NET_RX_ALIGN
```

---

<a id="net_rx_ring_pad"></a>

### `NET_RX_RING_PAD`

`macro` | [headers/net.h:31](../../headers/net.h#L31)

```c
#define NET_RX_RING_PAD
```

The RTL8139 ring is 8K + 16 bytes (datasheet, RBLEN 00): the chip may write up to 16 bytes past the 8 KB the reader indexes, so the buffer carries that tail, or the NIC writes into the next heap chunk.

---

<a id="net_rcr"></a>

### `NET_RCR`

`macro` | [headers/net.h:34](../../headers/net.h#L34)

```c
#define NET_RCR
```

RCR: accept broadcast/multicast/phys (the ring size bits are ignored by QEMU anyway).

---

<a id="net_max_frame"></a>

### `NET_MAX_FRAME`

`macro` | [headers/net.h:35](../../headers/net.h#L35)

```c
#define NET_MAX_FRAME
```

---

<a id="net_tx_slots"></a>

### `NET_TX_SLOTS`

`macro` | [headers/net.h:36](../../headers/net.h#L36)

```c
#define NET_TX_SLOTS
```

---

<a id="net_eth_alen"></a>

### `NET_ETH_ALEN`

`macro` | [headers/net.h:39](../../headers/net.h#L39)

```c
#define NET_ETH_ALEN
```

========== Ethernet ==========

---

<a id="net_ethertype_ip"></a>

### `NET_ETHERTYPE_IP`

`macro` | [headers/net.h:40](../../headers/net.h#L40)

```c
#define NET_ETHERTYPE_IP
```

---

<a id="net_ethertype_arp"></a>

### `NET_ETHERTYPE_ARP`

`macro` | [headers/net.h:41](../../headers/net.h#L41)

```c
#define NET_ETHERTYPE_ARP
```

---

<a id="net_ethertype_ipv6"></a>

### `NET_ETHERTYPE_IPV6`

`macro` | [headers/net.h:42](../../headers/net.h#L42)

```c
#define NET_ETHERTYPE_IPV6
```

---

<a id="net_proto_icmp"></a>

### `NET_PROTO_ICMP`

`macro` | [headers/net.h:45](../../headers/net.h#L45)

```c
#define NET_PROTO_ICMP
```

========== IP protocols ==========

---

<a id="net_proto_tcp"></a>

### `NET_PROTO_TCP`

`macro` | [headers/net.h:46](../../headers/net.h#L46)

```c
#define NET_PROTO_TCP
```

---

<a id="net_proto_udp"></a>

### `NET_PROTO_UDP`

`macro` | [headers/net.h:47](../../headers/net.h#L47)

```c
#define NET_PROTO_UDP
```

---

<a id="net_arp_cache"></a>

### `NET_ARP_CACHE`

`macro` | [headers/net.h:50](../../headers/net.h#L50)

```c
#define NET_ARP_CACHE
```

========== ARP ==========

---

<a id="net_arp_request"></a>

### `NET_ARP_REQUEST`

`macro` | [headers/net.h:51](../../headers/net.h#L51)

```c
#define NET_ARP_REQUEST
```

---

<a id="net_arp_reply"></a>

### `NET_ARP_REPLY`

`macro` | [headers/net.h:52](../../headers/net.h#L52)

```c
#define NET_ARP_REPLY
```

---

<a id="net_tcp_mss"></a>

### `NET_TCP_MSS`

`macro` | [headers/net.h:55](../../headers/net.h#L55)

```c
#define NET_TCP_MSS
```

========== Protocol bounds ==========

---

<a id="net_tcp_window"></a>

### `NET_TCP_WINDOW`

`macro` | [headers/net.h:56](../../headers/net.h#L56)

```c
#define NET_TCP_WINDOW
```

---

<a id="net_sock_rx_buf"></a>

### `NET_SOCK_RX_BUF`

`macro` | [headers/net.h:59](../../headers/net.h#L59)

```c
#define NET_SOCK_RX_BUF
```

The receive window and each socket's receive buffer match: the NIC ring (below) is the rtl8139's 8 KB hardware ring, unrelated.

---

<a id="net_rx_ring_size"></a>

### `NET_RX_RING_SIZE`

`macro` | [headers/net.h:60](../../headers/net.h#L60)

```c
#define NET_RX_RING_SIZE
```

---

<a id="net_sockets"></a>

### `NET_SOCKETS`

`macro` | [headers/net.h:61](../../headers/net.h#L61)

```c
#define NET_SOCKETS
```

---

<a id="net_dns_port"></a>

### `NET_DNS_PORT`

`macro` | [headers/net.h:62](../../headers/net.h#L62)

```c
#define NET_DNS_PORT
```

---

<a id="net_ephemeral_min"></a>

### `NET_EPHEMERAL_MIN`

`macro` | [headers/net.h:63](../../headers/net.h#L63)

```c
#define NET_EPHEMERAL_MIN
```

---

<a id="net_dns_tries"></a>

### `NET_DNS_TRIES`

`macro` | [headers/net.h:64](../../headers/net.h#L64)

```c
#define NET_DNS_TRIES
```

---

<a id="net_dns_tmo_ms"></a>

### `NET_DNS_TMO_MS`

`macro` | [headers/net.h:65](../../headers/net.h#L65)

```c
#define NET_DNS_TMO_MS
```

---

<a id="net_connect_tmo_s"></a>

### `NET_CONNECT_TMO_S`

`macro` | [headers/net.h:66](../../headers/net.h#L66)

```c
#define NET_CONNECT_TMO_S
```

---

<a id="net_retry_ms"></a>

### `NET_RETRY_MS`

`macro` | [headers/net.h:67](../../headers/net.h#L67)

```c
#define NET_RETRY_MS
```

---

<a id="net_accept_tmo_ms"></a>

### `NET_ACCEPT_TMO_MS`

`macro` | [headers/net.h:68](../../headers/net.h#L68)

```c
#define NET_ACCEPT_TMO_MS
```

---

<a id="net_tx_max"></a>

### `NET_TX_MAX`

`macro` | [headers/net.h:69](../../headers/net.h#L69)

```c
#define NET_TX_MAX
```

---

<a id="net_fd_base"></a>

### `NET_FD_BASE`

`macro` | [headers/net.h:72](../../headers/net.h#L72)

```c
#define NET_FD_BASE
```

========== Socket layer ==========

---

<a id="net_udp_sockets"></a>

### `NET_UDP_SOCKETS`

`macro` | [headers/net.h:77](../../headers/net.h#L77)

```c
#define NET_UDP_SOCKETS
```

Datagram sockets (docs/spec/network.md, Linux socket ABI): a second table after the stream one, its own descriptor range and ephemeral ports clear of the kernel's internal DNS client (NET_EPHEMERAL_MIN up).

---

<a id="net_udp_queue"></a>

### `NET_UDP_QUEUE`

`macro` | [headers/net.h:78](../../headers/net.h#L78)

```c
#define NET_UDP_QUEUE
```

---

<a id="net_udp_dgram_max"></a>

### `NET_UDP_DGRAM_MAX`

`macro` | [headers/net.h:79](../../headers/net.h#L79)

```c
#define NET_UDP_DGRAM_MAX
```

---

<a id="net_udp_fd_base"></a>

### `NET_UDP_FD_BASE`

`macro` | [headers/net.h:80](../../headers/net.h#L80)

```c
#define NET_UDP_FD_BASE
```

---

<a id="net_udp_ephemeral_min"></a>

### `NET_UDP_EPHEMERAL_MIN`

`macro` | [headers/net.h:81](../../headers/net.h#L81)

```c
#define NET_UDP_EPHEMERAL_MIN
```

---

<a id="net_udp_ephemeral_max"></a>

### `NET_UDP_EPHEMERAL_MAX`

`macro` | [headers/net.h:82](../../headers/net.h#L82)

```c
#define NET_UDP_EPHEMERAL_MAX
```

---

<a id="net_sockaddr_in_len"></a>

### `NET_SOCKADDR_IN_LEN`

`macro` | [headers/net.h:83](../../headers/net.h#L83)

```c
#define NET_SOCKADDR_IN_LEN
```

---

<a id="net_msghdr_len"></a>

### `NET_MSGHDR_LEN`

`macro` | [headers/net.h:85](../../headers/net.h#L85)

```c
#define NET_MSGHDR_LEN
```

struct msghdr / struct mmsghdr layout on x86-64.

---

<a id="net_mmsghdr_len"></a>

### `NET_MMSGHDR_LEN`

`macro` | [headers/net.h:86](../../headers/net.h#L86)

```c
#define NET_MMSGHDR_LEN
```

---

<a id="net_msghdr_name_off"></a>

### `NET_MSGHDR_NAME_OFF`

`macro` | [headers/net.h:87](../../headers/net.h#L87)

```c
#define NET_MSGHDR_NAME_OFF
```

---

<a id="net_msghdr_namelen_off"></a>

### `NET_MSGHDR_NAMELEN_OFF`

`macro` | [headers/net.h:88](../../headers/net.h#L88)

```c
#define NET_MSGHDR_NAMELEN_OFF
```

---

<a id="net_msghdr_iov_off"></a>

### `NET_MSGHDR_IOV_OFF`

`macro` | [headers/net.h:89](../../headers/net.h#L89)

```c
#define NET_MSGHDR_IOV_OFF
```

---

<a id="net_msghdr_iovlen_off"></a>

### `NET_MSGHDR_IOVLEN_OFF`

`macro` | [headers/net.h:90](../../headers/net.h#L90)

```c
#define NET_MSGHDR_IOVLEN_OFF
```

---

<a id="net_mmsghdr_len_off"></a>

### `NET_MMSGHDR_LEN_OFF`

`macro` | [headers/net.h:91](../../headers/net.h#L91)

```c
#define NET_MMSGHDR_LEN_OFF
```

---

<a id="net_iov_len"></a>

### `NET_IOV_LEN`

`macro` | [headers/net.h:92](../../headers/net.h#L92)

```c
#define NET_IOV_LEN
```

---

<a id="net_iov_max"></a>

### `NET_IOV_MAX`

`macro` | [headers/net.h:93](../../headers/net.h#L93)

```c
#define NET_IOV_MAX
```

---

<a id="net_mmsg_max"></a>

### `NET_MMSG_MAX`

`macro` | [headers/net.h:94](../../headers/net.h#L94)

```c
#define NET_MMSG_MAX
```

---

## Variables

<a id="net_rx_dropped"></a>

### `net_rx_dropped`

`variable` `extern` | [headers/net.h:163](../../headers/net.h#L163)

```c
extern unsigned int net_rx_dropped;
```

Aggregate RX drop counter shared between the driver (bad frames) and the stack (dropped fragments); defined in net.c.

---

<a id="net6_rx_dropped"></a>

### `net6_rx_dropped`

`variable` `extern` | [headers/net.h:164](../../headers/net.h#L164)

```c
extern unsigned int net6_rx_dropped;
```

---
