# headers: tls_crypto

*Community 7 | 15 files | cohesion 0.63*

## Definition

This community groups 15 file(s) rooted at `headers` with dominant language c (cohesion 0.63). Central symbols: `CHECK`, `DRIVERS_VIRTIO_NET_H`, `NET_ACCEPT_TMO_MS`, `NET_ARP_CACHE`, `NET_ARP_REPLY`, `NET_ARP_REQUEST`, `NET_CONNECT_TMO_S`, `NET_DNS`. Core file: `net/tls_crypto.c` (78 symbols). Documented purpose: Docstring: drivers/virtio_net.c -- Polled legacy virtio-net driver..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/virtio_net.c` | c | infrastructure | 44 | yes |
| `headers/drivers/virtio_net.h` | h | infrastructure | 9 | yes |
| `headers/net.h` | h | utility | 71 | yes |
| `headers/net/rtl8139.h` | h | utility | 8 | no |
| `headers/tls.h` | h | utility | 73 | yes |
| `headers/tls_port.h` | h | utility | 49 | yes |
| `headers/tls_roots.h` | h | utility | 0 | yes |
| `headers/tls_test_roots.h` | h | testing | 0 | yes |
| `net/net.c` | c | utility | 69 | yes |
| `net/rtl8139.c` | c | utility | 28 | no |
| `net/tls.c` | c | utility | 27 | yes |
| `net/tls_crypto.c` | c | utility | 78 | yes |
| `net/tls_x509.c` | c | utility | 23 | yes |
| `progs/tls_u/tls_u_main.c` | c | utility | 5 | yes |
| `tls_test.c` | c | testing | 23 | yes |

## Key Symbols

- `VNET_VENDOR` (macro, `drivers/virtio_net.c:29`) `#define VNET_VENDOR`
- `VNET_DEV_LEGACY` (macro, `drivers/virtio_net.c:30`) `#define VNET_DEV_LEGACY`
- `VNET_DEV_TRANS` (macro, `drivers/virtio_net.c:31`) `#define VNET_DEV_TRANS`
- `VNET_F_ACK` (macro, `drivers/virtio_net.c:33`) `#define VNET_F_ACK`
- `VNET_F_DRIVER` (macro, `drivers/virtio_net.c:34`) `#define VNET_F_DRIVER`
- `VNET_F_OK` (macro, `drivers/virtio_net.c:35`) `#define VNET_F_OK`
- `VNET_F_DRIVER_OK` (macro, `drivers/virtio_net.c:36`) `#define VNET_F_DRIVER_OK`
- `VNET_QNUM` (macro, `drivers/virtio_net.c:38`) `#define VNET_QNUM`
- `VNET_DESC_SZ` (macro, `drivers/virtio_net.c:39`) `#define VNET_DESC_SZ`
- `VNET_AVAIL_OFF` (macro, `drivers/virtio_net.c:40`) `#define VNET_AVAIL_OFF`
- `VNET_USED_OFF` (macro, `drivers/virtio_net.c:41`) `#define VNET_USED_OFF`
- `VNET_QAREA` (macro, `drivers/virtio_net.c:42`) `#define VNET_QAREA`
- `VNET_DESC_NEXT` (macro, `drivers/virtio_net.c:44`) `#define VNET_DESC_NEXT`
- `VNET_DESC_WRITE` (macro, `drivers/virtio_net.c:45`) `#define VNET_DESC_WRITE`
- `VNET_Q_RX` (macro, `drivers/virtio_net.c:47`) `#define VNET_Q_RX`
- `VNET_Q_TX` (macro, `drivers/virtio_net.c:48`) `#define VNET_Q_TX`
- `VNET_HDR_LEN` (macro, `drivers/virtio_net.c:50`) `#define VNET_HDR_LEN`
- `VNET_RX_BUFS` (macro, `drivers/virtio_net.c:51`) `#define VNET_RX_BUFS`
- `VNET_RX_SIZE` (macro, `drivers/virtio_net.c:52`) `#define VNET_RX_SIZE`
- `VNET_TX_SIZE` (macro, `drivers/virtio_net.c:53`) `#define VNET_TX_SIZE`
- `VNET_MIN_FRAME` (macro, `drivers/virtio_net.c:54`) `#define VNET_MIN_FRAME`
- `VNET_MAX_FRAME` (macro, `drivers/virtio_net.c:55`) `#define VNET_MAX_FRAME`
- `VNET_TMO_MS` (macro, `drivers/virtio_net.c:56`) `#define VNET_TMO_MS`
- `VNET_POLL_MAX` (macro, `drivers/virtio_net.c:57`) `#define VNET_POLL_MAX`
- `VNET_CFG_MAC` (macro, `drivers/virtio_net.c:59`) `#define VNET_CFG_MAC`
- `VNET_CFG_STATUS` (macro, `drivers/virtio_net.c:60`) `#define VNET_CFG_STATUS`
- `VNET_ST_LINK_UP` (macro, `drivers/virtio_net.c:61`) `#define VNET_ST_LINK_UP`
- `vnet_outb` (function, `drivers/virtio_net.c:81`) `static void vnet_outb(unsigned short port, unsigned char v)`
- `vnet_outw` (function, `drivers/virtio_net.c:85`) `static void vnet_outw(unsigned short port, unsigned short v)`
- `vnet_outl` (function, `drivers/virtio_net.c:89`) `static void vnet_outl(unsigned short port, unsigned v)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 22
- Cross-boundary resolved imports (EXTRACTED): 13

## Connections

- [EXTRACTED] depends_on community 7 <-> 0 (strength 0.9): Extracted import edge crosses communities: drivers/virtio_net.c imports headers/drivers/pci.h.
- [EXTRACTED] depends_on community 7 <-> 2 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports kernel/string.c.
- [EXTRACTED] depends_on community 7 <-> 4 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports kernel/time.c.
- [INFERRED] shares_context community 1 <-> 7 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (progs/doomgeneric: d_englsh) and community 7 (headers: tls_crypto).

## Risks

- [dataflow DEAD_STORE] `drivers/virtio_net.c:146` `vnet_desc` `d`: `d` assigned at line 146 but never read afterwards.
- [dataflow DEAD_STORE] `net/net.c:301` `net_dns_resolve` `rc`: `rc` assigned at line 301 but never read afterwards.
- [dataflow UNINIT_USE] `net/tls_crypto.c:1227` `ecdsa_verify` `gen`: `gen` may be read before initialization (declared line 1223).

## Open Questions

- Why do 2 file(s) lack file-level docs (e.g. `headers/net/rtl8139.h`)? What purpose do they serve?
- What would break if the most connected file in headers: tls_crypto changed?
- Should headers: tls_crypto be split, given cohesion 0.63?

## Sources

- `drivers/virtio_net.c`
- `headers/drivers/virtio_net.h`
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
