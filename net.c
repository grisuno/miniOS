/* MiniOS network stack: rtl8139 under QEMU slirp user networking.
 *
 * Polled NIC driver (no interrupt controller is configured): TX waits on
 * the descriptor owner bit, RX drains the classic ring by comparing CBR
 * against our CAPR. On top: Ethernet + ARP cache, IPv4 (checksums
 * verified, fragments dropped fail-closed), ICMP echo, UDP (DNS) and a
 * minimal client TCP: SYN handshake, stop-and-wait retransmission with a
 * PIT-calibrated TSC clock, FIN teardown, 536-byte MSS.
 *
 * Programs reach the stack through the libc-style symbols registered by
 * net_register_symbols (ET_REL) and through the Linux socket syscalls.
 */

#include "kernel.h"
#include "net.h"

void net_poll_rx(void);

/* ================================================================
 *  Ports, PCI, time
 * ================================================================ */

static unsigned short net_iobase;

static void outb_port(unsigned short port, unsigned char val) {
    __asm__ volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static unsigned char inb_port(unsigned short port) {
    unsigned char v;
    __asm__ volatile("inb %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

static void outw_port(unsigned short port, unsigned short val) {
    __asm__ volatile("outw %0, %1" : : "a"(val), "Nd"(port));
}

static void outl_port(unsigned short port, unsigned int val) {
    __asm__ volatile("outl %0, %1" : : "a"(val), "Nd"(port));
}

static unsigned short inw_port(unsigned short port) {
    unsigned short v;
    __asm__ volatile("inw %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

static unsigned int inl_port(unsigned short port) {
    unsigned int v;
    __asm__ volatile("inl %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}

static unsigned char net_reg8(unsigned short off) { return inb_port((unsigned short)(net_iobase + off)); }
static void net_reg8_w(unsigned short off, unsigned char v) { outb_port((unsigned short)(net_iobase + off), v); }
static unsigned short net_reg16(unsigned short off) { return inw_port((unsigned short)(net_iobase + off)); }
static void net_reg16_w(unsigned short off, unsigned short v) { outw_port((unsigned short)(net_iobase + off), v); }
static unsigned int net_reg32(unsigned short off) { return inl_port((unsigned short)(net_iobase + off)); }
static void net_reg32_w(unsigned short off, unsigned int v) { outl_port((unsigned short)(net_iobase + off), v); }

#define NET_REG_CR      0x37
#define NET_REG_TSD0    0x10
#define NET_REG_TSAD0   0x20
#define NET_REG_RBSTART 0x30
#define NET_REG_CAPR    0x38
#define NET_REG_CBR     0x3A
#define NET_REG_9346CR  0x50

static unsigned int pci_read32(unsigned bus, unsigned dev, unsigned func, unsigned reg) {
    outl_port(0xCF8, 0x80000000u | (bus << 16) | (dev << 11) | (func << 8) | (reg & 0xFC));
    return inl_port(0xCFC);
}

static void pci_write32(unsigned bus, unsigned dev, unsigned func, unsigned reg, unsigned int val) {
    outl_port(0xCF8, 0x80000000u | (bus << 16) | (dev << 11) | (func << 8) | (reg & 0xFC));
    outl_port(0xCFC, val);
}

/* Find the rtl8139 and return its I/O base, 0 when absent. */
static unsigned short net_find_rtl8139(void) {
    unsigned dev;
    for (dev = 0; dev < 32; dev++) {
        unsigned int id = pci_read32(0, dev, 0, 0);
        if ((id & 0xFFFF) == NET_PCI_VENDOR && ((id >> 16) & 0xFFFF) == NET_PCI_DEVICE) {
            unsigned int cmd = pci_read32(0, dev, 0, 4);
            pci_write32(0, dev, 0, 4, cmd | 0x7);
            unsigned int bar0 = pci_read32(0, dev, 0, 0x10);
            if (bar0 & 1) return (unsigned short)(bar0 & ~3u);
            return 0;
        }
    }
    return 0;
}

/* TSC clock calibrated once against a PIT channel 2 one-shot. */
static unsigned long net_tsc_base;
static unsigned long net_tsc_per_ms;

static unsigned long net_rdtsc(void) {
    unsigned int lo, hi;
    __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long)hi << 32) | lo;
}

static void net_time_init(void) {
    unsigned long t0, t1;
    outb_port(0x61, (unsigned char)((inb_port(0x61) & 0x0F) | 0x01));
    outb_port(0x43, 0xB0);
    outb_port(0x42, 0x96);
    outb_port(0x42, 0x04);
    t0 = net_rdtsc();
    while (!(inb_port(0x61) & 0x20));
    t1 = net_rdtsc();
    outb_port(0x61, (unsigned char)(inb_port(0x61) & 0x0F));
    net_tsc_per_ms = t1 - t0;
    net_tsc_base = t1;
}

unsigned long net_time_ms(void) {
    return net_tsc_per_ms ? (net_rdtsc() - net_tsc_base) / net_tsc_per_ms : 0;
}

/* ================================================================
 *  rtl8139 driver
 * ================================================================ */

static unsigned char *net_rx_ring;      /* NET_RX_BUF_LEN bytes, aligned */
static unsigned char net_our_ip[4] = { NET_IP_ADDR };
static unsigned short net_rx_capr;
static unsigned char  net_mac[NET_ETH_ALEN];
static unsigned int   net_tx_packets;
static unsigned int   net_rx_packets;
static unsigned int   net_rx_dropped;

static void net_rtl_reset(void) {
    unsigned long deadline;
    net_reg8_w(NET_REG_CR, 0x10);                       /* reset */
    deadline = net_time_ms() + 200;
    while (net_reg8(NET_REG_CR) & 0x10) {
        if (net_time_ms() > deadline) break;
    }
}

static void net_rtl_init(void) {
    unsigned long ptr;
    net_iobase = net_find_rtl8139();
    if (!net_iobase) return;

    net_rtl_reset();

    net_reg8_w(NET_REG_9346CR, 0xC0);                   /* unlock config */
    net_reg8_w(0x52, 0x00);                             /* CONFIG1: defaults */

    net_rx_ring = kmalloc(NET_RX_BUF_LEN + NET_RX_ALIGN);
    if (!net_rx_ring) return;
    ptr = (unsigned long)net_rx_ring;
    ptr = (ptr + NET_RX_ALIGN - 1) & ~(unsigned long)(NET_RX_ALIGN - 1);
    net_rx_ring = (unsigned char *)ptr;
    net_reg32_w(NET_REG_RBSTART, (unsigned int)ptr);
    net_rx_capr = 0;

    net_mac[0] = net_reg8(0x00);
    net_mac[1] = net_reg8(0x01);
    net_mac[2] = net_reg8(0x02);
    net_mac[3] = net_reg8(0x03);
    net_mac[4] = net_reg8(0x04);
    net_mac[5] = net_reg8(0x05);

    net_reg16_w(0x3C, 0x0000);                          /* no interrupts */
    net_reg16_w(0x44, 0x000F);                          /* RCR: accept all */
    net_reg8_w(NET_REG_CR, 0x0D);                       /* BUFE | TE | RE */
}

static unsigned net_tx_slot;

static int net_tx_frame(const unsigned char *frame, unsigned len) {
    unsigned long deadline;
    unsigned attempt;
    if (!net_iobase) return 0;
    if (len < 60) len = 60;                             /* min ethernet frame */
    if (len > NET_TX_MAX) return 0;
    /* QEMU rotates descriptors: use them in order and wait for the
     * selected one to come back into host ownership. */
    for (attempt = 0; attempt < NET_TX_SLOTS; attempt++) {
        unsigned slot = net_tx_slot;
        unsigned int tsd = net_reg32((unsigned short)(NET_REG_TSD0 + slot * 4));
        if (!(tsd & 0x2000)) {
            deadline = net_time_ms() + 2000;
            while (!(net_reg32((unsigned short)(NET_REG_TSD0 + slot * 4)) & 0x2000)) {
                if (net_time_ms() > deadline) return 0;
            }
        }
        net_reg32_w((unsigned short)(NET_REG_TSAD0 + slot * 4), (unsigned int)(unsigned long)frame);
        net_reg32_w((unsigned short)(NET_REG_TSD0 + slot * 4), len & 0x1FFF);
        deadline = net_time_ms() + 2000;
        while (!(net_reg32((unsigned short)(NET_REG_TSD0 + slot * 4)) & 0x2000)) {
            if (net_time_ms() > deadline) return 0;
        }
        net_tx_slot = (slot + 1) % NET_TX_SLOTS;
        net_tx_packets++;
        return 1;
    }
    return 0;
}

/* ================================================================
 *  Byte helpers
 * ================================================================ */

static void net_put16(unsigned char *p, unsigned short v) {
    p[0] = (unsigned char)(v >> 8);
    p[1] = (unsigned char)v;
}

static void net_put32(unsigned char *p, unsigned int v) {
    p[0] = (unsigned char)(v >> 24);
    p[1] = (unsigned char)(v >> 16);
    p[2] = (unsigned char)(v >> 8);
    p[3] = (unsigned char)v;
}

static unsigned short net_get16(const unsigned char *p) {
    return (unsigned short)((p[0] << 8) | p[1]);
}

static unsigned int net_get32(const unsigned char *p) {
    return ((unsigned int)p[0] << 24) | ((unsigned int)p[1] << 16) |
           ((unsigned int)p[2] << 8) | p[3];
}

static unsigned short net_checksum(const void *data, unsigned len) {
    const unsigned char *p = (const unsigned char *)data;
    unsigned int sum = 0;
    while (len > 1) {
        sum += net_get16(p);
        p += 2;
        len -= 2;
    }
    if (len) sum += ((unsigned int)p[0]) << 8;
    while (sum >> 16) sum = (sum & 0xFFFF) + (sum >> 16);
    return (unsigned short)~sum;
}

/* ================================================================
 *  ARP
 * ================================================================ */

struct net_arp_entry {
    unsigned char ip[4];
    unsigned char mac[NET_ETH_ALEN];
    int           valid;
};

static struct net_arp_entry net_arp_cache[NET_ARP_CACHE];

static void net_arp_store(const unsigned char *ip, const unsigned char *mac) {
    int i, free = -1;
    for (i = 0; i < NET_ARP_CACHE; i++) {
        if (net_arp_cache[i].valid && kmemcmp(net_arp_cache[i].ip, ip, 4) == 0) {
            kmemcpy(net_arp_cache[i].mac, mac, NET_ETH_ALEN);
            return;
        }
        if (!net_arp_cache[i].valid && free < 0) free = i;
    }
    if (free < 0) free = 0;
    kmemcpy(net_arp_cache[free].ip, ip, 4);
    kmemcpy(net_arp_cache[free].mac, mac, NET_ETH_ALEN);
    net_arp_cache[free].valid = 1;
}

static int net_arp_lookup(const unsigned char *ip, unsigned char *mac_out) {
    int i;
    for (i = 0; i < NET_ARP_CACHE; i++) {
        if (net_arp_cache[i].valid && kmemcmp(net_arp_cache[i].ip, ip, 4) == 0) {
            kmemcpy(mac_out, net_arp_cache[i].mac, NET_ETH_ALEN);
            return 1;
        }
    }
    return 0;
}

static void net_arp_request(const unsigned char *ip) {
    unsigned char frame[64];
    kmemset(frame, 0, sizeof(frame));
    kmemset(frame, 0xFF, NET_ETH_ALEN);
    kmemcpy(frame + 6, net_mac, NET_ETH_ALEN);
    net_put16(frame + 12, NET_ETHERTYPE_ARP);
    net_put16(frame + 14, 1);                 /* ethernet */
    net_put16(frame + 16, 0x0800);            /* IPv4 */
    frame[18] = 6;
    frame[19] = 4;
    net_put16(frame + 20, NET_ARP_REQUEST);
    kmemcpy(frame + 22, net_mac, NET_ETH_ALEN);
    kmemcpy(frame + 28, net_our_ip, 4);
    kmemcpy(frame + 38, ip, 4);
    net_tx_frame(frame, 42);
}

/* Resolve an IP on the 10.0.2.0/24 link. Retries, bounded timeout. */
static int net_arp_resolve(const unsigned char *ip, unsigned char *mac_out) {
    unsigned long deadline = net_time_ms() + NET_CONNECT_TMO_S * 1000;
    while (1) {
        if (net_arp_lookup(ip, mac_out)) return 1;
        net_arp_request(ip);
        unsigned long wait = net_time_ms() + NET_RETRY_MS;
        while (net_time_ms() < wait) {
            net_poll_rx();
            if (net_arp_lookup(ip, mac_out)) return 1;
        }
        if (net_time_ms() > deadline) return 0;
    }
}

/* ================================================================
 *  IPv4 / ICMP / UDP / DNS
 * ================================================================ */

static unsigned short net_ip_id;
static unsigned short net_icmp_id = 0x4D49;
static unsigned short net_udp_port = NET_EPHEMERAL_MIN;
static unsigned int   net_tx_bytes;
static unsigned int   net_rx_bytes;

/* Send a frame on the link: dst IP decides the destination MAC. */
static int net_ip_send(const unsigned char *dip, unsigned char proto,
                       const unsigned char *payload, unsigned len) {
    unsigned char frame[NET_MAX_FRAME];
    unsigned char dst_mac[NET_ETH_ALEN];
    unsigned char *ip;
    unsigned total = 20 + len;
    if (total > NET_MAX_FRAME - 14) return 0;

    if (dip[0] == 10 && dip[1] == 0 && dip[2] == 2) {
        if (!net_arp_resolve(dip, dst_mac)) return 0;
    } else {
        unsigned char gw[4] = { NET_GATEWAY };
        if (!net_arp_resolve(gw, dst_mac)) return 0;
    }

    kmemcpy(frame, dst_mac, NET_ETH_ALEN);
    kmemcpy(frame + 6, net_mac, NET_ETH_ALEN);
    net_put16(frame + 12, NET_ETHERTYPE_IP);
    ip = frame + 14;
    ip[0] = 0x45;
    ip[1] = 0;
    net_put16(ip + 2, (unsigned short)total);
    net_put16(ip + 4, net_ip_id++);
    net_put16(ip + 6, 0x4000);                /* DF, no fragmentation */
    ip[8] = 64;
    ip[9] = proto;
    kmemcpy(ip + 12, net_our_ip, 4);
    kmemcpy(ip + 16, dip, 4);
    net_put16(ip + 10, 0);                    /* field must be zero for the sum */
    net_put16(ip + 10, net_checksum(ip, 20));
    kmemcpy(ip + 20, payload, len);
    if (!net_tx_frame(frame, (unsigned)(14 + total))) return 0;
    net_tx_bytes += total;
    return 1;
}

static int net_udp_send(const unsigned char *dip, unsigned short sport,
                        unsigned short dport, const unsigned char *data, unsigned len) {
    unsigned char pkt[NET_MAX_FRAME];
    unsigned total = 8 + len;
    if (total > NET_MAX_FRAME - 34) return 0;
    net_put16(pkt, sport);
    net_put16(pkt + 2, dport);
    net_put16(pkt + 4, (unsigned short)total);
    net_put16(pkt + 6, 0);                    /* checksum optional for UDP */
    kmemcpy(pkt + 8, data, len);
    return net_ip_send(dip, NET_PROTO_UDP, pkt, total);
}

struct net_dns_state {
    unsigned short id;
    unsigned char  ip[4];
    int            done;
};

static struct net_dns_state net_dns;

/* Parse a DNS response for the first A record. */
static void net_dns_parse(const unsigned char *data, unsigned len) {
    unsigned short qd, an, i;
    unsigned pos = 12;
    if (len < 12) return;
    if (!(net_get16(data + 2) & 0x8000)) return; /* not a response */
    if (net_get16(data) != net_dns.id) return;
    qd = net_get16(data + 4);
    an = net_get16(data + 6);
    for (i = 0; i < qd && pos < len; i++) {
        while (pos < len && data[pos]) pos += data[pos] + 1;
        pos += 5;                             /* skip zero + qtype/qclass */
    }
    for (i = 0; i < an && pos < len; i++) {
        unsigned short rtype, rdlen;
        if (pos >= len) return;
        if ((data[pos] & 0xC0) == 0xC0) {     /* compressed name pointer */
            pos += 2;
        } else {
            while (pos < len && data[pos]) pos += data[pos] + 1;
            pos += 1;
        }
        if (pos + 10 > len) return;
        rtype = net_get16(data + pos);
        rdlen = net_get16(data + pos + 8);
        pos += 10;
        if (pos + rdlen > len) return;
        if (rtype == 1 && rdlen == 4) {
            kmemcpy(net_dns.ip, data + pos, 4);
            net_dns.done = 1;
            return;
        }
        pos += rdlen;
    }
}

/* Blocking A-record lookup against NET_DNS. */
static int net_dns_resolve(const char *host, unsigned char ip_out[4]) {
    int tries, i, hl = (int)kstrlen(host);
    if (hl < 1 || hl > 253) return 0;
    for (i = 0; i < 4; i++) {                 /* dotted quad already? */
        unsigned v = 0;
        int dot = 0;
        const char *p = host;
        unsigned char parts[4] = {0, 0, 0, 0};
        int part = 0;
        while (*p) {
            if (*p == '.') {
                if (part >= 3) break;
                part++;
                p++;
                v = 0;
                continue;
            }
            if (*p < '0' || *p > '9') { dot = -1; break; }
            v = v * 10 + (unsigned)(*p - '0');
            if (v > 255) { dot = -1; break; }
            parts[part] = (unsigned char)v;
            p++;
        }
        (void)dot;
        if (p == host + hl && part == 3) {
            kmemcpy(ip_out, parts, 4);
            return 1;
        }
    }

    for (tries = 0; tries < NET_DNS_TRIES; tries++) {
        unsigned char q[NET_MAX_FRAME];
        const char *p = host;
        unsigned pos = 12;
        unsigned long deadline;
        kmemset(q, 0, sizeof(q));
        net_dns.id = (unsigned short)(net_ip_id + 0x9E3);
        net_put16(q, net_dns.id);
        net_put16(q + 2, 0x0100);
        net_put16(q + 4, 1);
        while (*p && pos < sizeof(q) - 6) {
            const char *dot = kstrchr(p, '.');
            unsigned seg = dot ? (unsigned)(dot - p) : (unsigned)kstrlen(p);
            if (seg > 63) return 0;
            q[pos++] = (unsigned char)seg;
            kmemcpy(q + pos, p, seg);
            pos += seg;
            if (!dot) break;
            p = dot + 1;
        }
        q[pos++] = 0;
        net_put16(q + pos, 1);                /* A */
        net_put16(q + pos + 2, 1);            /* IN */
        pos += 4;

        net_dns.done = 0;
        net_udp_send((const unsigned char[]){ NET_DNS }, net_udp_port++, NET_DNS_PORT, q, pos);
        deadline = net_time_ms() + NET_DNS_TMO_MS;
        while (!net_dns.done && net_time_ms() < deadline) net_poll_rx();
        if (net_dns.done) {
            kmemcpy(ip_out, net_dns.ip, 4);
            return 1;
        }
    }
    return 0;
}

static int net_ping_active;
static unsigned char net_ping_ip[4];
static int net_ping_got_reply;

static void net_icmp_rx(const unsigned char *ip, unsigned len) {
    const unsigned char *icmp = ip + 20;
    unsigned icmp_len = len - 20;
    unsigned short reply[NET_MAX_FRAME];
    if (icmp_len < 8) return;
    if (net_checksum(icmp, icmp_len) != 0) return;
    if (icmp[0] == 0) {                       /* echo reply */
        if (net_ping_active && kmemcmp(ip + 12, net_ping_ip, 4) == 0 &&
            net_get16(icmp + 4) == net_icmp_id) {
            net_ping_got_reply = 1;
        }
    } else if (icmp[0] == 8) {                /* echo request: reply to us */
        if (kmemcmp(ip + 16, net_our_ip, 4) == 0) {
            kmemset(reply, 0, sizeof(reply));
            kmemcpy((unsigned char *)reply, icmp, icmp_len);
            ((unsigned char *)reply)[0] = 0;
            net_put16((unsigned char *)reply + 2, 0);
            net_put16((unsigned char *)reply + 2, net_checksum(reply, icmp_len));
            net_ip_send(ip, NET_PROTO_ICMP, (const unsigned char *)reply, icmp_len);
        }
    }
}

static int net_ping(const unsigned char ip[4]) {
    unsigned char req[48];
    unsigned long deadline;
    kmemset(req, 0, sizeof(req));
    req[0] = 8;
    req[1] = 0;
    net_put16(req + 4, net_icmp_id);
    net_put16(req + 6, 1);
    net_put16(req + 2, net_checksum(req, sizeof(req)));
    net_ping_active = 1;
    net_ping_got_reply = 0;
    kmemcpy(net_ping_ip, ip, 4);
    net_ip_send(ip, NET_PROTO_ICMP, req, sizeof(req));
    deadline = net_time_ms() + NET_CONNECT_TMO_S * 1000;
    while (!net_ping_got_reply && net_time_ms() < deadline) net_poll_rx();
    net_ping_active = 0;
    return net_ping_got_reply;
}

/* ================================================================
 *  TCP (minimal client)
 * ================================================================ */

#define NET_TCP_CLOSED      0
#define NET_TCP_SYN_SENT    1
#define NET_TCP_ESTABLISHED 2
#define NET_TCP_FIN_SENT    3
#define NET_TCP_DEAD        4

struct net_tcp_sock {
    int           state;
    int           in_use;
    unsigned char dip[4];
    unsigned short dport;
    unsigned short sport;
    unsigned int  seq;
    unsigned int  ack;
    unsigned int  rx_next;
    unsigned char rx[NET_RX_RING_SIZE];
    unsigned int  rx_head;
    unsigned int  rx_tail;
    int           rx_eof;
    int           tx_pending;
    unsigned char tx_buf[NET_TX_MAX];
    unsigned int  tx_len;
    unsigned int  tx_seq;
};

static struct net_tcp_sock net_sockets[NET_SOCKETS];
static unsigned short net_tcp_sport = NET_EPHEMERAL_MIN;
static unsigned int   net_tcp_seq = 0x6D696E69;

static struct net_tcp_sock *net_sock_alloc(void) {
    int i;
    for (i = 0; i < NET_SOCKETS; i++) {
        if (!net_sockets[i].in_use) {
            kmemset(&net_sockets[i], 0, sizeof(net_sockets[i]));
            net_sockets[i].in_use = 1;
            net_sockets[i].state = NET_TCP_CLOSED;
            return &net_sockets[i];
        }
    }
    return 0;
}

static int net_sock_index(const struct net_tcp_sock *s) {
    int i;
    for (i = 0; i < NET_SOCKETS; i++)
        if (&net_sockets[i] == s) return i;
    return -1;
}

/* Compute the TCP checksum over a pseudo header + segment. */
static unsigned short net_tcp_checksum(const unsigned char *src, const unsigned char *dst,
                                       unsigned short sport, unsigned short dport,
                                       const unsigned char *seg, unsigned len) {
    unsigned char buf[NET_TX_MAX + 12];
    unsigned total = 12 + len;
    kmemcpy(buf, src, 4);
    kmemcpy(buf + 4, dst, 4);
    buf[8] = 0;
    buf[9] = NET_PROTO_TCP;
    net_put16(buf + 10, (unsigned short)len);
    kmemcpy(buf + 12, seg, len);
    if (total & 1) buf[total++] = 0;
    return net_checksum(buf, total);
}

/* UDP checksum over pseudo header + datagram (may be 0 = not computed). */
static int net_udp_checksum_ok(const unsigned char *src, const unsigned char *dst,
                               const unsigned char *udp, unsigned len) {
    unsigned char buf[NET_TX_MAX + 12];
    unsigned total = 12 + len;
    unsigned short csum = net_get16(udp + 6);
    if (csum == 0) return 1;
    kmemcpy(buf, src, 4);
    kmemcpy(buf + 4, dst, 4);
    buf[8] = 0;
    buf[9] = NET_PROTO_UDP;
    net_put16(buf + 10, (unsigned short)len);
    kmemcpy(buf + 12, udp, len);
    if (total & 1) buf[total++] = 0;
    return net_checksum(buf, total) == 0;
}

static int net_tcp_xmit(struct net_tcp_sock *s, unsigned flags,
                        const unsigned char *data, unsigned len, int fresh) {
    unsigned char seg[NET_TX_MAX];
    unsigned hlen = 20;
    if (20 + len > sizeof(seg)) return 0;
    unsigned xmit_seq = (fresh || !s->tx_pending) ? s->seq : s->tx_seq;
    kmemset(seg, 0, 24);
    net_put16(seg, s->sport);
    net_put16(seg + 2, s->dport);
    net_put32(seg + 4, xmit_seq);
    net_put32(seg + 8, s->ack);
    seg[13] = (unsigned char)flags;
    net_put16(seg + 14, NET_TCP_WINDOW);
    if (flags & 0x02) {                       /* SYN carries an MSS option */
        hlen = 24;
        seg[12] = 0x60;
        seg[20] = 0x02;                       /* kind MSS */
        seg[21] = 0x04;                       /* len 4 */
        net_put16(seg + 22, NET_TCP_MSS);
    } else {
        seg[12] = 0x50;
    }
    kmemcpy(seg + hlen, data, len);
    net_put16(seg + 16, net_tcp_checksum(net_our_ip, s->dip, s->sport, s->dport, seg, hlen + len));
    if (!net_ip_send(s->dip, NET_PROTO_TCP, seg, hlen + len)) return 0;
    if (fresh && (flags & (0x02 | 0x08 | 0x01)))
        s->seq += len + ((flags & (0x02 | 0x01)) ? 1 : 0);
    return 1;
}

/* Process one received TCP segment. */
static void net_tcp_rx(const unsigned char *ip, unsigned len) {
    const unsigned char *seg = ip + 20;
    unsigned seg_len = len - 20;
    unsigned short sport, dport;
    unsigned int seq, ack, hlen, i;
    int found = -1;
    if (seg_len < 20) return;
    sport = net_get16(seg);
    dport = net_get16(seg + 2);
    if (net_tcp_checksum(ip + 12, net_our_ip, sport, dport, seg, seg_len) != 0) return;
    hlen = (seg[12] >> 4) * 4;
    if (hlen < 20 || hlen > seg_len) return;
    seq = net_get32(seg + 4);
    ack = net_get32(seg + 8);
    for (i = 0; i < NET_SOCKETS; i++) {
        if (net_sockets[i].in_use &&
            kmemcmp(net_sockets[i].dip, ip + 12, 4) == 0 &&
            net_sockets[i].sport == dport && net_sockets[i].dport == sport) {
            found = (int)i;
            break;
        }
    }
    if (found < 0) return;
    {
        struct net_tcp_sock *s = &net_sockets[found];
        unsigned flags = seg[13];
        unsigned data_off = hlen;
        unsigned data_len = seg_len - hlen;

        if (flags & 0x04) {                   /* RST */
            s->state = NET_TCP_DEAD;
            return;
        }
        if (flags & 0x02) {                   /* SYN */
            s->rx_next = seq + 1;
            s->ack = seq + 1;
            if (flags & 0x10) {               /* SYN+ACK */
                net_tcp_xmit(s, 0x10, 0, 0, 1);
                s->state = NET_TCP_ESTABLISHED;
            }
            return;
        }
        if (data_len > 0) {
            if (seq == s->rx_next && s->rx_head + data_len <= sizeof(s->rx)) {
                kmemcpy(s->rx + s->rx_head, seg + data_off, data_len);
                s->rx_head += data_len;
                s->rx_next += data_len;
                net_tcp_xmit(s, 0x10, 0, 0, 1);  /* ACK */
            } else if ((int)(seq - s->rx_next) < 0) {
                net_tcp_xmit(s, 0x10, 0, 0, 1);  /* duplicate: re-ACK */
            }
        }
        if (flags & 0x01) {                   /* FIN */
            if (seq == s->rx_next) s->rx_next++;
            s->rx_eof = 1;
            s->ack = s->rx_next;
            net_tcp_xmit(s, 0x10, 0, 0, 1);
        }
        if (flags & 0x10) {                   /* ACK: peer acks our data */
            if (s->tx_pending &&
                (int)(ack - (s->tx_seq + s->tx_len)) >= 0) {
                s->tx_pending = 0;
            }
            if (s->state == NET_TCP_FIN_SENT && (int)(ack - (s->seq)) >= 0) {
                s->state = NET_TCP_DEAD;
            }
        }
    }
}

/* Blocking connect of an allocated socket to an IPv4 address. */
static int net_tcp_connect_into(struct net_tcp_sock *s, const unsigned char ip[4],
                                unsigned short port) {
    unsigned long deadline;
    kmemcpy(s->dip, ip, 4);
    s->dport = port;
    s->sport = net_tcp_sport++;
    s->seq = net_tcp_seq;
    net_tcp_seq += 0x1000;
    s->ack = 0;
    s->state = NET_TCP_SYN_SENT;
    net_tcp_xmit(s, 0x02, 0, 0, 1);              /* SYN */
    deadline = net_time_ms() + NET_CONNECT_TMO_S * 1000;
    while (s->state == NET_TCP_SYN_SENT && net_time_ms() < deadline) {
        unsigned long retry = net_time_ms() + NET_RETRY_MS;
        while (net_time_ms() < retry && s->state == NET_TCP_SYN_SENT)
            net_poll_rx();
        if (s->state == NET_TCP_SYN_SENT) net_tcp_xmit(s, 0x02, 0, 0, 0);
    }
    if (s->state != NET_TCP_ESTABLISHED) {
        s->in_use = 0;
        s->state = NET_TCP_CLOSED;
        return 0;
    }
    return 1;
}

/* Blocking send (stop-and-wait, one outstanding segment). */
static int net_tcp_send(struct net_tcp_sock *s, const char *buf, int len) {
    int sent = 0;
    while (len > 0 && s->state == NET_TCP_ESTABLISHED) {
        unsigned chunk = (unsigned)len > NET_TCP_MSS ? NET_TCP_MSS : (unsigned)len;
        unsigned long deadline;
        kmemcpy(s->tx_buf, buf, chunk);
        s->tx_len = chunk;
        s->tx_seq = s->seq;
        s->tx_pending = 1;
        net_tcp_xmit(s, 0x18, s->tx_buf, chunk, 1);   /* PSH|ACK */
        deadline = net_time_ms() + NET_CONNECT_TMO_S * 1000;
        while (s->tx_pending && s->state == NET_TCP_ESTABLISHED &&
               net_time_ms() < deadline) {
            unsigned long retry = net_time_ms() + NET_RETRY_MS;
            while (net_time_ms() < retry && s->tx_pending) net_poll_rx();
            if (s->tx_pending) net_tcp_xmit(s, 0x18, s->tx_buf, chunk, 0);
        }
        if (s->tx_pending || s->state != NET_TCP_ESTABLISHED) return sent ? sent : -1;
        buf += chunk;
        len -= (int)chunk;
        sent += (int)chunk;
    }
    return sent;
}

/* Blocking receive; 0 = EOF (FIN). */
static int net_tcp_recv(struct net_tcp_sock *s, char *buf, int len) {
    while (s->state != NET_TCP_DEAD) {
        net_poll_rx();
        if (s->rx_tail < s->rx_head) {
            unsigned avail = s->rx_head - s->rx_tail;
            unsigned take = avail > (unsigned)len ? (unsigned)len : avail;
            kmemcpy(buf, s->rx + s->rx_tail, take);
            s->rx_tail += take;
            if (s->rx_tail == s->rx_head) { s->rx_tail = 0; s->rx_head = 0; }
            return (int)take;
        }
        if (s->rx_eof && s->rx_tail == s->rx_head) return 0;
    }
    return -1;
}

static void net_tcp_close(struct net_tcp_sock *s) {
    if (s->state == NET_TCP_ESTABLISHED) {
        unsigned long deadline = net_time_ms() + NET_CONNECT_TMO_S * 1000;
        s->state = NET_TCP_FIN_SENT;
        net_tcp_xmit(s, 0x11, 0, 0, 1);          /* FIN|ACK */
        while (s->state == NET_TCP_FIN_SENT && net_time_ms() < deadline) {
            unsigned long retry = net_time_ms() + NET_RETRY_MS;
            while (net_time_ms() < retry && s->state == NET_TCP_FIN_SENT)
                net_poll_rx();
            if (s->state == NET_TCP_FIN_SENT) net_tcp_xmit(s, 0x11, 0, 0, 0);
        }
    }
    s->in_use = 0;
    s->state = NET_TCP_CLOSED;
}

/* ================================================================
 *  Receive path: NIC -> ethernet -> ARP/IP -> demux
 * ================================================================ */

static void net_rx_handle_frame(const unsigned char *frame, unsigned len) {
    unsigned short etype;
    if (len < 14) return;
    etype = net_get16(frame + 12);
    if (etype == NET_ETHERTYPE_ARP && len >= 42) {
        if (net_get16(frame + 20) == NET_ARP_REQUEST &&
            kmemcmp(frame + 38, net_our_ip, 4) == 0) {
            unsigned char reply[64];
            kmemset(reply, 0, sizeof(reply));
            kmemcpy(reply, frame + 6, NET_ETH_ALEN);
            kmemcpy(reply + 6, net_mac, NET_ETH_ALEN);
            net_put16(reply + 12, NET_ETHERTYPE_ARP);
            net_put16(reply + 14, 1);
            net_put16(reply + 16, 0x0800);
            reply[18] = 6;
            reply[19] = 4;
            net_put16(reply + 20, NET_ARP_REPLY);
            kmemcpy(reply + 22, net_mac, NET_ETH_ALEN);
            kmemcpy(reply + 28, net_our_ip, 4);
            kmemcpy(reply + 32, frame + 22, NET_ETH_ALEN);
            kmemcpy(reply + 38, frame + 28, 4);
            net_tx_frame(reply, 42);
        } else if (net_get16(frame + 20) == NET_ARP_REPLY) {
            net_arp_store(frame + 28, frame + 22);
        }
        return;
    }
    if (etype == NET_ETHERTYPE_IP) {
        const unsigned char *ip = frame + 14;
        unsigned ihl, iplen, proto;
        if (len < 34) return;
        if (ip[0] != 0x45) return;
        if (net_checksum(ip, 20) != 0) return;
        ihl = (ip[0] & 0x0F) * 4;
        iplen = net_get16(ip + 2);
        if (ihl < 20 || iplen < ihl || 14 + iplen > len) return;
        if (kmemcmp(ip + 16, net_our_ip, 4) != 0) return;
        if (net_get16(ip + 6) & 0x3FFF) { net_rx_dropped++; return; } /* fragment */
        proto = ip[9];
        net_rx_bytes += iplen;
        if (proto == NET_PROTO_ICMP) net_icmp_rx(ip, iplen);
        else if (proto == NET_PROTO_TCP) net_tcp_rx(ip, iplen);
        else if (proto == NET_PROTO_UDP) {
            const unsigned char *udp = ip + ihl;
            unsigned udplen = net_get16(udp + 4);
            if (udplen >= 8 && ihl + udplen <= iplen) {
                if (net_get16(udp) == NET_DNS_PORT &&
                    net_udp_checksum_ok(ip + 12, net_our_ip, udp, udplen))
                    net_dns_parse(udp + 8, udplen - 8);
            }
        }
    }
}

/* Drain the RX ring once; returns 1 when a frame was handled. */
void net_poll_rx(void) {
    unsigned short cbr;
    unsigned i = 0;
    if (!net_iobase) return;
    cbr = net_reg16(NET_REG_CBR);
    while (net_rx_capr != cbr) {
        unsigned char *hdr = net_rx_ring + net_rx_capr;
        unsigned short status = (unsigned short)(hdr[0] | (hdr[1] << 8));
        unsigned short length = (unsigned short)(hdr[2] | (hdr[3] << 8));
        if (status & 0x1) {                   /* ROK */
            if (length >= 14 && length <= NET_MAX_FRAME) {
                net_rx_packets++;
                net_rx_handle_frame(net_rx_ring + net_rx_capr + 4, (unsigned)length - 4);
            } else {
                net_rx_dropped++;
            }
        }
        net_rx_capr = (unsigned short)((net_rx_capr + length + 4 + 3) & ~3u);
        if (net_rx_capr >= NET_RX_BUF_LEN) net_rx_capr = 0;
        /* QEMU stores CAPR + 16 and gates receive on the free space:
         * CAPR is written 1514 bytes ahead so the ring always advertises
         * room for one frame. */
        net_reg16_w(NET_REG_CAPR, (unsigned short)(net_rx_capr - 16));
        cbr = net_reg16(NET_REG_CBR);
        if (++i > 64) break;
    }
    net_reg16_w(NET_REG_CAPR, (unsigned short)(net_rx_capr - 16));
}

/* ================================================================
 *  Public libc-style API
 * ================================================================ */

int net_open(void) {
    struct net_tcp_sock *s = net_sock_alloc();
    if (!s) return -1;
    return net_sock_index(s);
}

int net_connect(const char *host, unsigned short port) {
    unsigned char ip[4];
    struct net_tcp_sock *s = net_sock_alloc();
    if (!s) return -1;
    if (!net_dns_resolve(host, ip)) { s->in_use = 0; return -1; }
    if (!net_tcp_connect_into(s, ip, port)) return -1;
    return net_sock_index(s);
}

int net_send(int fd, const char *buf, int len) {
    if (fd < 0 || fd >= NET_SOCKETS || !net_sockets[fd].in_use) return -1;
    return net_tcp_send(&net_sockets[fd], buf, len);
}

int net_recv(int fd, char *buf, int len) {
    if (fd < 0 || fd >= NET_SOCKETS || !net_sockets[fd].in_use) return -1;
    return net_tcp_recv(&net_sockets[fd], buf, len);
}

void net_close(int fd) {
    if (fd < 0 || fd >= NET_SOCKETS || !net_sockets[fd].in_use) return;
    net_tcp_close(&net_sockets[fd]);
}

/* ================================================================
 *  Linux syscall ABI
 * ================================================================ */

long net_sys_socket(long a1, long a2, long a3) {
    struct net_tcp_sock *s;
    (void)a3;
    if (a1 != 2 || a2 != 1) return -22;        /* AF_INET, SOCK_STREAM */
    s = net_sock_alloc();
    if (!s) return -12;
    return NET_FD_BASE + net_sock_index(s);
}

long net_sys_connect(long fd, long sockaddr, long addrlen) {
    const unsigned char *sa = (const unsigned char *)sockaddr;
    unsigned short port;
    struct net_tcp_sock *s;
    if (fd < NET_FD_BASE || fd >= NET_FD_BASE + NET_SOCKETS || addrlen < 16) return -22;
    s = &net_sockets[fd - NET_FD_BASE];
    if (!s->in_use) return -9;
    if (sa[0] != 2 || sa[1] != 0) return -22; /* AF_INET */
    port = net_get16(sa + 2);
    if (!net_tcp_connect_into(s, sa + 4, port)) return -111;
    return 0;
}

long net_sys_sendto(long fd, long buf, long len, long flags, long to, long tolen) {
    int rc;
    (void)to; (void)tolen;
    if (flags) return -22;
    if (fd < NET_FD_BASE || fd >= NET_FD_BASE + NET_SOCKETS) return -9;
    if (len < 0) return -22;
    rc = net_tcp_send(&net_sockets[fd - NET_FD_BASE], (const char *)buf, (int)len);
    return rc;
}

long net_sys_recvfrom(long fd, long buf, long len, long flags, long from, long fromlen) {
    int rc;
    (void)from; (void)fromlen;
    if (flags) return -22;
    if (fd < NET_FD_BASE || fd >= NET_FD_BASE + NET_SOCKETS) return -9;
    if (len < 0) return -22;
    rc = net_tcp_recv(&net_sockets[fd - NET_FD_BASE], (char *)buf, (int)len);
    return rc;
}

long net_sys_shutdown(long fd, long how) {
    (void)how;
    if (fd < NET_FD_BASE || fd >= NET_FD_BASE + NET_SOCKETS) return -9;
    net_tcp_close(&net_sockets[fd - NET_FD_BASE]);
    return 0;
}

long net_sys_close(long fd) {
    if (fd < NET_FD_BASE || fd >= NET_FD_BASE + NET_SOCKETS) return -9;
    net_tcp_close(&net_sockets[fd - NET_FD_BASE]);
    return 0;
}

long net_sys_poll(long fds, long nfds, long timeout_ms) {
    /* Linux pollfd: int fd; short events; short revents. */
    unsigned long deadline = net_time_ms() + (timeout_ms > 0 ? (unsigned long)timeout_ms : 0);
    long n, ready = 0;
    for (;;) {
        for (n = 0; n < nfds; n++) {
            const char *entry = (const char *)fds + n * 8;
            int fd = (int)net_get32((const unsigned char *)entry);
            unsigned short events = net_get16((const unsigned char *)entry + 4);
            unsigned short revents = 0;
            if (fd >= NET_FD_BASE && fd < NET_FD_BASE + NET_SOCKETS) {
                struct net_tcp_sock *s = &net_sockets[fd - NET_FD_BASE];
                if (s->in_use) {
                    if (s->rx_tail < s->rx_head || s->rx_eof) revents |= 0x1; /* POLLIN */
                }
            }
            if (events & revents) {
                net_put16((unsigned char *)entry + 6, revents);
                ready++;
            }
        }
        if (ready > 0) return ready;
        if (timeout_ms == 0) return 0;
        net_poll_rx();
        if (timeout_ms > 0 && net_time_ms() > deadline) return 0;
    }
}

/* MiniOS syscall 200: resolve a hostname, returned as a network-order
 * 32-bit address (like inet_addr), or -1 on failure. */
long net_sys_dns(long host) {
    unsigned char ip[4];
    if (!host) return -1;
    if (!net_dns_resolve((const char *)host, ip)) return -1;
    return ((long)ip[0] << 24) | ((long)ip[1] << 16) | ((long)ip[2] << 8) | ip[3];
}

/* ================================================================
 *  Shell commands
 * ================================================================ */

static int net_parse_ip(const char *text, unsigned char ip[4]) {
    unsigned parts[4] = {0, 0, 0, 0};
    int part = 0;
    const char *p = text;
    if (!text) return 0;
    while (*p) {
        if (*p == '.') {
            if (part >= 3) return 0;
            part++;
            p++;
            continue;
        }
        if (*p < '0' || *p > '9') return 0;
        parts[part] = parts[part] * 10 + (unsigned)(*p - '0');
        if (parts[part] > 255) return 0;
        p++;
    }
    if (part != 3) return 0;
    ip[0] = (unsigned char)parts[0];
    ip[1] = (unsigned char)parts[1];
    ip[2] = (unsigned char)parts[2];
    ip[3] = (unsigned char)parts[3];
    return 1;
}

void net_cmd_status(void) {
    if (!net_iobase) {
        vga_puts("net: no rtl8139 found\n");
        return;
    }
    kprintf("rtl8139  iobase 0x%x\n", net_iobase);
    kprintf("mac      %02x:%02x:%02x:%02x:%02x:%02x\n",
            net_mac[0], net_mac[1], net_mac[2], net_mac[3], net_mac[4], net_mac[5]);
    kprintf("ip       %u.%u.%u.%u/24\n", net_our_ip[0], net_our_ip[1], net_our_ip[2], net_our_ip[3]);
    vga_puts("gateway  10.0.2.2  dns 10.0.2.3\n");
    kprintf("tx       %u frames, %u bytes\n", net_tx_packets, net_tx_bytes);
    kprintf("rx       %u frames, %u bytes, %u dropped\n", net_rx_packets, net_rx_bytes, net_rx_dropped);
}

void net_cmd_ping(const char *ip_text) {
    unsigned char ip[4];
    if (!net_iobase) { vga_puts("net: no rtl8139 found\n"); return; }
    if (!net_parse_ip(ip_text, ip)) {
        vga_puts("usage: net ping <ip>\n");
        return;
    }
    if (net_ping(ip)) kprintf("reply from %s\n", ip_text);
    else kprintf("no reply from %s\n", ip_text);
}

void net_cmd_dns(const char *host) {
    unsigned char ip[4];
    if (!net_iobase) { vga_puts("net: no rtl8139 found\n"); return; }
    if (net_dns_resolve(host, ip))
        kprintf("%s = %u.%u.%u.%u\n", host, ip[0], ip[1], ip[2], ip[3]);
    else
        kprintf("dns: no answer for %s\n", host);
}

/* ================================================================
 *  Init and symbol registration
 * ================================================================ */

void net_register_symbols(void) {
    k_register_symbol("net_open", (void *)net_open);
    k_register_symbol("net_connect", (void *)net_connect);
    k_register_symbol("net_send", (void *)net_send);
    k_register_symbol("net_recv", (void *)net_recv);
    k_register_symbol("net_close", (void *)net_close);
}

void net_init(void) {
    net_time_init();
    net_rtl_init();
    net_register_symbols();
}
