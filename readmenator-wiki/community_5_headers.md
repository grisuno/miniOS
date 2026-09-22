# headers

*Community 5 | 13 files | cohesion 0.63*

## Definition

This community groups 13 file(s) rooted at `headers` with dominant language c (cohesion 0.63). Central symbols: `CHECK`, `NET_ARP_CACHE`, `NET_ARP_REPLY`, `NET_ARP_REQUEST`, `NET_CONNECT_TMO_S`, `NET_DNS`, `NET_DNS_PORT`, `NET_DNS_TMO_MS`. Core file: `net/tls_crypto.c` (78 symbols). Documented purpose: Portability shim between the MiniOS kernel and the host-side test.

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/net.h` | h | utility | 59 | yes |
| `headers/net/rtl8139.h` | h | utility | 8 | no |
| `headers/tls.h` | h | utility | 73 | yes |
| `headers/tls_port.h` | h | utility | 49 | yes |
| `headers/tls_roots.h` | h | utility | 0 | yes |
| `headers/tls_test_roots.h` | h | testing | 0 | yes |
| `net/net.c` | c | utility | 56 | yes |
| `net/rtl8139.c` | c | utility | 31 | no |
| `net/tls.c` | c | utility | 27 | yes |
| `net/tls_crypto.c` | c | utility | 78 | yes |
| `net/tls_x509.c` | c | utility | 23 | yes |
| `progs/tls_u/tls_u_main.c` | c | utility | 5 | yes |
| `tls_test.c` | c | testing | 23 | yes |

## Key Symbols

- `NET_H` (macro, `headers/net.h:2`) `#define NET_H`
- `NET_IP_ADDR` (macro, `headers/net.h:5`) `#define NET_IP_ADDR`
- `NET_NETMASK` (macro, `headers/net.h:6`) `#define NET_NETMASK`
- `NET_GATEWAY` (macro, `headers/net.h:7`) `#define NET_GATEWAY`
- `NET_DNS` (macro, `headers/net.h:8`) `#define NET_DNS`
- `NET_PCI_VENDOR` (macro, `headers/net.h:11`) `#define NET_PCI_VENDOR`
- `NET_PCI_DEVICE` (macro, `headers/net.h:12`) `#define NET_PCI_DEVICE`
- `NET_RX_BUF_LEN` (macro, `headers/net.h:18`) `#define NET_RX_BUF_LEN`
- `NET_RX_ALIGN` (macro, `headers/net.h:19`) `#define NET_RX_ALIGN`
- `NET_RCR` (macro, `headers/net.h:22`) `#define NET_RCR`
- `NET_MAX_FRAME` (macro, `headers/net.h:23`) `#define NET_MAX_FRAME`
- `NET_TX_SLOTS` (macro, `headers/net.h:24`) `#define NET_TX_SLOTS`
- `NET_ETH_ALEN` (macro, `headers/net.h:27`) `#define NET_ETH_ALEN`
- `NET_ETHERTYPE_IP` (macro, `headers/net.h:28`) `#define NET_ETHERTYPE_IP`
- `NET_ETHERTYPE_ARP` (macro, `headers/net.h:29`) `#define NET_ETHERTYPE_ARP`
- `NET_PROTO_ICMP` (macro, `headers/net.h:32`) `#define NET_PROTO_ICMP`
- `NET_PROTO_TCP` (macro, `headers/net.h:33`) `#define NET_PROTO_TCP`
- `NET_PROTO_UDP` (macro, `headers/net.h:34`) `#define NET_PROTO_UDP`
- `NET_ARP_CACHE` (macro, `headers/net.h:37`) `#define NET_ARP_CACHE`
- `NET_ARP_REQUEST` (macro, `headers/net.h:38`) `#define NET_ARP_REQUEST`
- `NET_ARP_REPLY` (macro, `headers/net.h:39`) `#define NET_ARP_REPLY`
- `NET_TCP_MSS` (macro, `headers/net.h:42`) `#define NET_TCP_MSS`
- `NET_TCP_WINDOW` (macro, `headers/net.h:43`) `#define NET_TCP_WINDOW`
- `ring` (function, `headers/net.h:45`) `* ring (below) is the rtl8139's 8 KB hardware ring, unrelated. */ #define NET_SO`
- `NET_SOCK_RX_BUF` (macro, `headers/net.h:46`) `#define NET_SOCK_RX_BUF`
- `NET_RX_RING_SIZE` (macro, `headers/net.h:47`) `#define NET_RX_RING_SIZE`
- `NET_SOCKETS` (macro, `headers/net.h:48`) `#define NET_SOCKETS`
- `NET_DNS_PORT` (macro, `headers/net.h:49`) `#define NET_DNS_PORT`
- `NET_EPHEMERAL_MIN` (macro, `headers/net.h:50`) `#define NET_EPHEMERAL_MIN`
- `NET_DNS_TRIES` (macro, `headers/net.h:51`) `#define NET_DNS_TRIES`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 19
- Cross-boundary resolved imports (EXTRACTED): 11

## Connections

- [EXTRACTED] depends_on community 5 <-> 3 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports kernel/string.c.
- [EXTRACTED] depends_on community 5 <-> 7 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports kernel/time.c.
- [EXTRACTED] depends_on community 5 <-> 0 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports headers/kernel.h.
- [EXTRACTED] depends_on community 1 <-> 5 (strength 0.9): Extracted import edge crosses communities: kernel/shell.c imports headers/net.h.

## Risks

- [dataflow DEAD_STORE] `net/net.c:276` `net_dns_resolve` `rc`: `rc` assigned at line 276 but never read afterwards.
- [dataflow UNINIT_USE] `net/tls_crypto.c:1227` `ecdsa_verify` `gen`: `gen` may be read before initialization (declared line 1223).

## Open Questions

- Why do 2 file(s) lack file-level docs (e.g. `headers/net/rtl8139.h`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.63?

## Sources

- `headers/net.h`
- `headers/net/rtl8139.h`
- `headers/tls.h`
- `headers/tls_port.h`
- `headers/tls_roots.h`
- `headers/tls_test_roots.h`
- `net/net.c`
- `net/rtl8139.c`
- `net/tls.c`
- `net/tls_crypto.c`
- `net/tls_x509.c`
- `progs/tls_u/tls_u_main.c`
- `tls_test.c`
