#ifndef NET_H
#define NET_H

/* ========== Fixed slirp configuration (QEMU -nic user) ========== */
#define NET_IP_ADDR   10, 0, 2, 15
#define NET_NETMASK   255, 255, 255, 0
#define NET_GATEWAY   10, 0, 2, 2
#define NET_DNS       10, 0, 2, 3

/* ========== rtl8139 ========== */
#define NET_PCI_VENDOR    0x10EC
#define NET_PCI_DEVICE    0x8139

/* QEMU masks the RCR ring-size bits (11-12) out of writes, so its
 * legacy receive ring is always 8 KB. The guest ring must match: with a
 * larger ring the guest read pointer and QEMU's 8 KB write wrap disagree
 * and the tail of every frame that crosses 8192 is lost. */
#define NET_RX_BUF_LEN    0x2000
#define NET_RX_ALIGN      256
/* RCR: accept broadcast/multicast/phys (the ring size bits are ignored
 * by QEMU anyway). */
#define NET_RCR           (0x000F)
#define NET_MAX_FRAME     1536
#define NET_TX_SLOTS      4

/* ========== Ethernet ========== */
#define NET_ETH_ALEN      6
#define NET_ETHERTYPE_IP  0x0800
#define NET_ETHERTYPE_ARP 0x0806

/* ========== IP protocols ========== */
#define NET_PROTO_ICMP    1
#define NET_PROTO_TCP     6
#define NET_PROTO_UDP     17

/* ========== ARP ========== */
#define NET_ARP_CACHE     8
#define NET_ARP_REQUEST   1
#define NET_ARP_REPLY     2

/* ========== Protocol bounds ========== */
#define NET_TCP_MSS       536
#define NET_TCP_WINDOW    16384
/* The receive window and each socket's receive buffer match: the NIC
 * ring (below) is the rtl8139's 8 KB hardware ring, unrelated. */
#define NET_SOCK_RX_BUF   16384
#define NET_RX_RING_SIZE  8192
#define NET_SOCKETS       16
#define NET_DNS_PORT      53
#define NET_EPHEMERAL_MIN 40000
#define NET_DNS_TRIES     3
#define NET_DNS_TMO_MS    1500
#define NET_CONNECT_TMO_S 5
#define NET_RETRY_MS      1000
#define NET_TX_MAX        1536

/* ========== Socket layer ========== */
#define NET_FD_BASE       100

/* net_connect / socket fds are NET_FD_BASE + index for Linux syscalls and
 * 0..NET_SOCKETS-1 for the libc-style symbols. */

void net_init(void);
void net_register_symbols(void);

/* Shell commands */
void net_cmd_status(void);
void net_cmd_ping(const char *ip_text);
void net_cmd_dns(const char *host);

/* Libc-style API for ET_REL programs */
int  net_open(void);
int  net_connect(const char *host, unsigned short port);
int  net_send(int fd, const char *buf, int len);
int  net_recv(int fd, char *buf, int len);
/* Blocking receive with a deadline: like net_recv, but -1 on timeout. */
int  net_recv_timeout(int fd, char *buf, int len, unsigned long timeout_ms);
void net_close(int fd);

/* Linux syscall ABI (sockaddr_in layout matches Linux) */
long net_sys_socket(long a1, long a2, long a3);
long net_sys_connect(long fd, long sockaddr, long addrlen);
long net_sys_sendto(long fd, long buf, long len, long flags, long to, long tolen);
long net_sys_recvfrom(long fd, long buf, long len, long flags, long from, long fromlen);
long net_sys_shutdown(long fd, long how);
long net_sys_close(long fd);
long net_sys_poll(long fds, long nfds, long timeout_ms);
long net_sys_dns(long host);

/* Milliseconds since net_init (PIT-calibrated TSC). */
unsigned long net_time_ms(void);

/* Demux entry point the rtl8139 driver (rtl8139.c) calls for every
 * frame drained from the RX ring; lives in net.c. */
void net_rx_handle_frame(const unsigned char *frame, unsigned len);

/* Aggregate RX drop counter shared between the driver (bad frames) and
 * the stack (dropped fragments); defined in net.c. */
extern unsigned int net_rx_dropped;

/* TLS sessions attached to socket fds (tls.c); net_sys_close frees them. */
void tls_free_fd(int fd);

#endif
