/* MiniOS network stack: virtio-net preferred, rtl8139 fallback, under
 * QEMU slirp user networking.
 *
 * Polled NIC drivers (no interrupt controller is configured): TX waits
 * on completion with a deadline, RX drains completed buffers into the
 * demux below. On top: Ethernet + ARP cache, IPv4 (checksums
 * verified, fragments dropped fail-closed), ICMP echo, UDP (DNS) and a
 * minimal client TCP: SYN handshake, stop-and-wait retransmission with a
 * PIT-calibrated TSC clock, FIN teardown, 536-byte MSS.
 *
 * Programs reach the stack through the libc-style symbols registered by
 * net_register_symbols (ET_REL) and through the Linux socket syscalls.
 */

#include "kernel.h"
#include "net.h"
#include "tls.h"
#include "net/rtl8139.h"
#include "drivers/virtio_net.h"
#include "sched.h"

/* ================================================================
 *  Protocol state shared with the driver
 * ================================================================ */

static unsigned char net_our_ip[4] = { NET_IP_ADDR };
static unsigned char net_mac[NET_ETH_ALEN];
unsigned int net_rx_dropped;
unsigned int net6_rx_dropped;

/** Docstring: Backend preference, frozen at net_init: a virtio-net
 * device wins when present, the rtl8139 stays as the fallback. All
 * frame I/O below goes through these three verbs, so no caller names
 * a driver; adding a NIC means registering its verbs here, never
 * rewriting the callers (Open/Closed Principle). */
static int net_use_virtio;

static int net_drv_send(const unsigned char *frame, unsigned len) {
    if (net_use_virtio) return vnet_send(frame, len);
    return rtl_send(frame, len);
}

static void net_drv_poll(void) {
    if (net_use_virtio) vnet_poll();
    else rtl_poll();
}

static int net_drv_present(void) {
    if (net_use_virtio) return vnet_present();
    return rtl_present();
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
    net_drv_send(frame, 42);
}

/* Resolve an IP on the 10.0.2.0/24 link. Retries, bounded timeout. */
static int net_arp_resolve(const unsigned char *ip, unsigned char *mac_out) {
    unsigned long deadline = net_time_ms() + NET_CONNECT_TMO_S * 1000;
    while (1) {
        if (net_arp_lookup(ip, mac_out)) return 1;
        net_arp_request(ip);
        unsigned long wait = net_time_ms() + NET_RETRY_MS;
        while (net_time_ms() < wait) {
            net_drv_poll();
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
    if (!net_drv_send(frame, (unsigned)(14 + total))) return 0;
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
        /* No pos>=len guard here: the for-condition already guarantees
         * pos<len at the top of every iteration (cppcheck
         * oppositeInnerCondition: the old check was dead code). */
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

    /* Heap query: 1536 B must not live in this frame — DNS resolves
     * from ring-3 connect on 16 KB proc slots (stack discipline,
     * CLAUDE.md). One buffer reused across tries, fail-closed. */
    unsigned char *q = (unsigned char *)kmalloc(NET_MAX_FRAME);
    int rc = 0;
    if (!q) return 0;
    for (tries = 0; tries < NET_DNS_TRIES; tries++) {
        const char *p = host;
        unsigned pos = 12;
        unsigned long deadline;
        kmemset(q, 0, NET_MAX_FRAME);
        net_dns.id = (unsigned short)(net_ip_id + 0x9E3);
        net_put16(q, net_dns.id);
        net_put16(q + 2, 0x0100);
        net_put16(q + 4, 1);
        while (*p && pos < NET_MAX_FRAME - 6) {
            const char *dot = kstrchr(p, '.');
            unsigned seg = dot ? (unsigned)(dot - p) : (unsigned)kstrlen(p);
            if (seg > 63) goto out;
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
        while (!net_dns.done && net_time_ms() < deadline) net_drv_poll();
        if (net_dns.done) {
            kmemcpy(ip_out, net_dns.ip, 4);
            rc = 1;
            goto out;
        }
    }
    rc = 0;
out:
    kfree(q);
    return rc;
}

static int net_ping_active;
static unsigned char net_ping_ip[4];
static int net_ping_got_reply;

static void net_icmp_rx(const unsigned char *ip, unsigned len) {
    const unsigned char *icmp = ip + 20;
    unsigned icmp_len = len - 20;
    /* Heap reply: 3 KB must not live in this frame — RX runs nested
     * under ring-3 socket syscalls on 16 KB proc slots (stack
     * discipline, CLAUDE.md). OOM drops the reply, never corrupts. */
    unsigned short *reply;
    if (icmp_len < 8) return;
    if (net_checksum(icmp, icmp_len) != 0) return;
    if (icmp[0] == 0) {                       /* echo reply */
        if (net_ping_active && kmemcmp(ip + 12, net_ping_ip, 4) == 0 &&
            net_get16(icmp + 4) == net_icmp_id) {
            net_ping_got_reply = 1;
        }
    } else if (icmp[0] == 8) {                /* echo request: reply to us */
        if (kmemcmp(ip + 16, net_our_ip, 4) == 0) {
            reply = (unsigned short *)kmalloc(NET_MAX_FRAME * sizeof(unsigned short));
            if (!reply) return;
            kmemset(reply, 0, NET_MAX_FRAME * sizeof(unsigned short));
            kmemcpy((unsigned char *)reply, icmp, icmp_len);
            ((unsigned char *)reply)[0] = 0;
            net_put16((unsigned char *)reply + 2, 0);
            net_put16((unsigned char *)reply + 2, net_checksum(reply, icmp_len));
            net_ip_send(ip, NET_PROTO_ICMP, (const unsigned char *)reply, icmp_len);
            kfree(reply);
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
    while (!net_ping_got_reply && net_time_ms() < deadline) net_drv_poll();
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
#define NET_TCP_LISTEN      5
#define NET_TCP_SYN_RCVD    6

struct net_tcp_sock {
    int           state;
    int           in_use;
    int           bound;      /* bind() claimed a local port */
    int           pending;    /* LISTEN: child index awaiting accept, -1 none */
    unsigned char dip[4];
    unsigned short dport;
    unsigned short sport;
    unsigned int  seq;
    unsigned int  ack;
    unsigned int  rx_next;
    unsigned char rx[NET_SOCK_RX_BUF];
    unsigned int  rx_head;
    unsigned int  rx_tail;
    int           rx_eof;
    int           tx_pending;
    unsigned char tx_buf[NET_TX_MAX];
    unsigned int  tx_len;
    unsigned int  tx_seq;
    /* Linux socket ABI state (docs/spec/network.md). */
    int           nonblock;   /* O_NONBLOCK on the socket */
    int           cloexec;    /* FD_CLOEXEC as recorded by fcntl/SOCK_CLOEXEC */
    int           connecting; /* a non-blocking connect is in flight */
    int           so_error;   /* pending error for SO_ERROR (positive errno) */
    unsigned long syn_deadline;
    unsigned long syn_retry;
};

/* One received datagram. */
struct net_udp_dgram {
    unsigned short len;
    unsigned short sport;
    unsigned char  sip[4];
    unsigned char  data[NET_UDP_DGRAM_MAX];
};

/* Datagram socket: a bounded ring of received datagrams. */
struct net_udp_sock {
    int            in_use;
    int            nonblock;
    int            cloexec;
    unsigned short lport;
    int            connected;
    unsigned char  pip[4];
    unsigned short pport;
    unsigned       head, count;
    struct net_udp_dgram q[NET_UDP_QUEUE];
};

/** Docstring: Socket table, heap-owned since the .bss diet: 16 x 18 KB.
 * Null means the allocation failed and the stack stays down; every entry
 * point fails closed (alloc returns 0, fd checks refuse, the demux drops). */
static struct net_tcp_sock *net_sockets = 0;
static struct net_udp_sock *net_udp_sockets = 0;
static int net_udp_deliver(const unsigned char sip[4], unsigned short sport,
                           unsigned short dport, const unsigned char *data,
                           unsigned len);
static unsigned short net_udp_sport = NET_UDP_EPHEMERAL_MIN;
static unsigned short net_tcp_sport = NET_EPHEMERAL_MIN;
static unsigned int   net_tcp_seq = 0x6D696E69;

static struct net_tcp_sock *net_sock_alloc(void) {
    int i;
    if (!net_sockets) return 0;
    for (i = 0; i < NET_SOCKETS; i++) {
        if (!net_sockets[i].in_use) {
            kmemset(&net_sockets[i], 0, sizeof(net_sockets[i]));
            net_sockets[i].in_use = 1;
            net_sockets[i].state = NET_TCP_CLOSED;
            net_sockets[i].pending = -1;
            return &net_sockets[i];
        }
    }
    return 0;
}

static int net_sock_index(const struct net_tcp_sock *s) {
    int i;
    if (!net_sockets) return -1;
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
static int net_tcp_passive_open(struct net_tcp_sock *ls,
        const unsigned char peer[4], unsigned short pport,
        unsigned short lport, unsigned int pseq);
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
    if (!net_sockets) return;
    for (i = 0; i < NET_SOCKETS; i++) {
        if (net_sockets[i].in_use &&
            kmemcmp(net_sockets[i].dip, ip + 12, 4) == 0 &&
            net_sockets[i].sport == dport && net_sockets[i].dport == sport) {
            found = (int)i;
            break;
        }
    }
    if (found < 0) {
        /* Passive open, first knock: a bare SYN to a listening port
         * allocates the child, answers SYN-ACK and parks it on the
         * listener for accept. Anything else (stray ACK/RST/data to
         * no socket) is dropped, never answered. */
        unsigned i;
        if ((seg[13] & 0x12) != 0x02) return;
        if (!net_sockets) return;
        for (i = 0; i < NET_SOCKETS; i++) {
            if (net_sockets[i].in_use &&
                net_sockets[i].state == NET_TCP_LISTEN &&
                net_sockets[i].sport == dport) {
                net_tcp_passive_open(&net_sockets[i], ip + 12, sport,
                        dport, seq);
                return;
            }
        }
        return;
    }
    {
        struct net_tcp_sock *s = &net_sockets[found];
        unsigned flags = seg[13];
        unsigned data_off = hlen;
        unsigned data_len = seg_len - hlen;

        if (flags & 0x04) {                   /* RST */
            s->state = NET_TCP_DEAD;
            return;
        }
        if (s->state == NET_TCP_SYN_RCVD) {
            /* Passive open, second knock: a bare ACK completing the
             * SYN-ACK handshake establishes; a SYN retransmit replays
             * the SYN-ACK; anything else (early data, stray FIN) is
             * dropped, never half-processed. */
            if ((flags & 0x12) == 0x10 && ack == s->seq) {
                s->state = NET_TCP_ESTABLISHED;
                return;
            }
            if ((flags & 0x12) == 0x02 && seq + 1 == s->rx_next) {
                net_tcp_xmit(s, 0x12, 0, 0, 0);
                return;
            }
            return;
        }
        if (s->state == NET_TCP_LISTEN)
            return;
        if ((flags & 0x02) && s->state == NET_TCP_SYN_SENT) {  /* SYN */
            s->rx_next = seq + 1;
            s->ack = seq + 1;
            if (flags & 0x10) {               /* SYN+ACK */
                net_tcp_xmit(s, 0x10, 0, 0, 1);
                s->state = NET_TCP_ESTABLISHED;
            }
            return;
        }
        if (s->state != NET_TCP_ESTABLISHED && s->state != NET_TCP_FIN_SENT)
            return;
        if (data_len > 0) {
            if (seq == s->rx_next) {
                if (s->rx_tail > 0 && s->rx_head + data_len > sizeof(s->rx)) {
                    kmemmove(s->rx, s->rx + s->rx_tail, s->rx_head - s->rx_tail);
                    s->rx_head -= s->rx_tail;
                    s->rx_tail = 0;
                }
                if (s->rx_head + data_len <= sizeof(s->rx)) {
                    kmemcpy(s->rx + s->rx_head, seg + data_off, data_len);
                    s->rx_head += data_len;
                    s->rx_next += data_len;
                    s->ack = s->rx_next;
                    net_tcp_xmit(s, 0x10, 0, 0, 1);  /* ACK */
                }
            } else if ((int)(seq - s->rx_next) < 0) {
                net_tcp_xmit(s, 0x10, 0, 0, 1);  /* duplicate: re-ACK */
            }
        }
        if (flags & 0x01) {                   /* FIN */
            /* An out-of-order FIN (its sequence is still ahead of the
             * next expected byte) must not report EOF: unread data is
             * still in flight, and rx_eof would make recv return 0 in
             * the middle of a record. The peer retransmits the FIN
             * after the missing data is re-ACKed. */
            if (seq == s->rx_next) {
                s->rx_next++;
                s->rx_eof = 1;
            }
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

/* Passive open: park a SYN_RCVD child on a LISTEN socket and answer
 * SYN-ACK. Single backlog slot: a second SYN while one pends is
 * dropped (the peer retransmits), never queued unbounded. The SYN-ACK
 * transmit fails closed without an ARP entry; the peer's SYN retry
 * replays it once the entry resolves. */
static int net_tcp_passive_open(struct net_tcp_sock *ls,
        const unsigned char peer[4], unsigned short pport,
        unsigned short lport, unsigned int pseq) {
    struct net_tcp_sock *c;
    int idx;
    if (!ls || ls->state != NET_TCP_LISTEN || ls->pending >= 0) return 0;
    c = net_sock_alloc();
    if (!c) return 0;
    idx = net_sock_index(c);
    if (idx < 0) { c->in_use = 0; return 0; }
    kmemcpy(c->dip, peer, 4);
    c->dport = pport;
    c->sport = lport;
    c->seq = net_tcp_seq;
    net_tcp_seq += 0x1000;
    c->rx_next = pseq + 1;
    c->ack = pseq + 1;
    c->state = NET_TCP_SYN_RCVD;
    net_tcp_xmit(c, 0x12, 0, 0, 1);
    ls->pending = idx;
    return 1;
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
            net_drv_poll();
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
            while (net_time_ms() < retry && s->tx_pending) net_drv_poll();
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
        net_drv_poll();
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

/* Blocking receive with a deadline: -1 when the deadline passes with no
 * data (the caller decides whether that is fatal). The TLS handshake
 * uses it so a silent peer cannot hang the shell forever. */
static int net_tcp_recv_deadline(struct net_tcp_sock *s, char *buf, int len,
                                 unsigned long timeout_ms) {
    unsigned long deadline = net_time_ms() + timeout_ms;
    while (s->state != NET_TCP_DEAD) {
        net_drv_poll();
        if (s->rx_tail < s->rx_head) {
            unsigned avail = s->rx_head - s->rx_tail;
            unsigned take = avail > (unsigned)len ? (unsigned)len : avail;
            kmemcpy(buf, s->rx + s->rx_tail, take);
            s->rx_tail += take;
            if (s->rx_tail == s->rx_head) { s->rx_tail = 0; s->rx_head = 0; }
            return (int)take;
        }
        if (s->rx_eof && s->rx_tail == s->rx_head) return 0;
        if (net_time_ms() > deadline) return -1;
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
                net_drv_poll();
            if (s->state == NET_TCP_FIN_SENT) net_tcp_xmit(s, 0x11, 0, 0, 0);
        }
    }
    s->in_use = 0;
    s->state = NET_TCP_CLOSED;
}

/* ================================================================
 *  Receive path: NIC -> ethernet -> ARP/IP -> demux
 * ================================================================ */

void net_rx_handle_frame(const unsigned char *frame, unsigned len) {
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
            net_drv_send(reply, 42);
        } else if (net_get16(frame + 20) == NET_ARP_REPLY) {
            net_arp_store(frame + 28, frame + 22);
        }
        return;
    }
    if (etype == NET_ETHERTYPE_IPV6) {
        net6_rx_dropped++;
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
            if (udplen >= 8 && ihl + udplen <= iplen &&
                net_udp_checksum_ok(ip + 12, net_our_ip, udp, udplen)) {
                if (!net_udp_deliver(ip + 12, net_get16(udp), net_get16(udp + 2),
                                     udp + 8, udplen - 8) &&
                    net_get16(udp) == NET_DNS_PORT)
                    net_dns_parse(udp + 8, udplen - 8);
            }
        }
    }
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
    if (!net_sockets || fd < 0 || fd >= NET_SOCKETS || !net_sockets[fd].in_use) return -1;
    return net_tcp_send(&net_sockets[fd], buf, len);
}

int net_recv(int fd, char *buf, int len) {
    if (!net_sockets || fd < 0 || fd >= NET_SOCKETS || !net_sockets[fd].in_use) return -1;
    return net_tcp_recv(&net_sockets[fd], buf, len);
}

int net_recv_timeout(int fd, char *buf, int len, unsigned long timeout_ms) {
    if (!net_sockets || fd < 0 || fd >= NET_SOCKETS || !net_sockets[fd].in_use) return -1;
    return net_tcp_recv_deadline(&net_sockets[fd], buf, len, timeout_ms);
}

void net_close(int fd) {
    if (!net_sockets || fd < 0 || fd >= NET_SOCKETS || !net_sockets[fd].in_use) return;
    net_tcp_close(&net_sockets[fd]);
}

/* ================================================================
 *  Server side: bind / listen / accept
 * ================================================================ */

/** Docstring: Allocate a socket bound to a local port and listening.
 * Returns the socket index, or -1 when the table is full. */
int net_listen(unsigned short port) {
    struct net_tcp_sock *s;
    if (port == 0) return -1;
    s = net_sock_alloc();
    if (!s) return -1;
    s->sport = port;
    s->bound = 1;
    s->pending = -1;
    s->state = NET_TCP_LISTEN;
    return net_sock_index(s);
}

/** Docstring: Take a pending child off a LISTEN socket without
 * waiting. Returns the child index, or -1 when no handshake has
 * completed yet. The child is ESTABLISHED and owned by the caller. */
int net_accept_nb(int fd) {
    int child;
    if (!net_sockets || fd < 0 || fd >= NET_SOCKETS) return -1;
    if (!net_sockets[fd].in_use || net_sockets[fd].state != NET_TCP_LISTEN)
        return -1;
    child = net_sockets[fd].pending;
    if (child < 0 || child >= NET_SOCKETS) return -1;
    if (!net_sockets[child].in_use ||
        net_sockets[child].state != NET_TCP_ESTABLISHED)
        return -1;
    net_sockets[fd].pending = -1;
    return child;
}

/** Docstring: Blocking accept with a deadline: poll the NIC until a
 * child establishes or timeout_ms passes. Returns the child index,
 * or -1 on timeout. Never blocks past the deadline, never spins
 * without polling (the peer's ACK arrives through the driver poll). */
int net_accept(int fd, unsigned long timeout_ms) {
    unsigned long deadline = net_time_ms() + timeout_ms;
    int child;
    if (!net_sockets || fd < 0 || fd >= NET_SOCKETS) return -1;
    if (!net_sockets[fd].in_use || net_sockets[fd].state != NET_TCP_LISTEN)
        return -1;
    for (;;) {
        net_drv_poll();
        child = net_accept_nb(fd);
        if (child >= 0) return child;
        if (net_time_ms() > deadline) return -1;
    }
}

/** Docstring: Socket state for diagnostics (the `net` builtin and the
 * httpd selftest). -1 on a wild fd. */
int net_sock_state(int fd) {
    if (!net_sockets || fd < 0 || fd >= NET_SOCKETS) return -1;
    if (!net_sockets[fd].in_use) return -1;
    return net_sockets[fd].state;
}

/** Docstring: Live sequence numbers for the httpd selftest's injected
 * ACK (the only in-OS reader of another socket's seq). -1 on a wild
 * fd, else 0 with both values stored. */
int net_sock_seq(int fd, unsigned *seq_out, unsigned *ack_out) {
    if (!net_sockets || fd < 0 || fd >= NET_SOCKETS) return -1;
    if (!net_sockets[fd].in_use) return -1;
    if (seq_out) *seq_out = net_sockets[fd].seq;
    if (ack_out) *ack_out = net_sockets[fd].ack;
    return 0;
}

/** Docstring: Test hook: feed one TCP segment from a fake peer through
 * the production demux (checksums computed with the stack's own
 * helpers, so a malformed injection is dropped exactly like wire
 * garbage). The httpd selftest owns this: SYN, ACK, data and FIN walk
 * the real handshake with no NIC involved. Bounded by NET_TX_MAX,
 * fail-closed past it. */
int net_test_inject_tcp(const unsigned char peer[4], unsigned short pport,
        unsigned short lport, unsigned char flags, unsigned int seq,
        unsigned int ack, const unsigned char *data, unsigned datalen) {
    unsigned char ip[20 + 20 + NET_TCP_MSS];
    unsigned char *seg = ip + 20;
    if (!peer || datalen > NET_TCP_MSS) return -1;
    kmemset(ip, 0, 20);
    ip[0] = 0x45;
    kmemcpy(ip + 12, peer, 4);
    kmemcpy(ip + 16, net_our_ip, 4);
    kmemset(seg, 0, 20);
    net_put16(seg, pport);
    net_put16(seg + 2, lport);
    net_put32(seg + 4, seq);
    net_put32(seg + 8, ack);
    seg[12] = 0x50;
    seg[13] = flags;
    net_put16(seg + 14, NET_TCP_WINDOW);
    if (data && datalen > 0) kmemcpy(seg + 20, data, datalen);
    net_put16(seg + 16, net_tcp_checksum(peer, net_our_ip, pport, lport,
            seg, 20 + datalen));
    net_tcp_rx(ip, 20 + 20 + datalen);
    return 0;
}

/* ================================================================
 *  Linux syscall ABI (docs/spec/network.md, "Linux socket ABI")
 * ================================================================ */

#define LNX_AF_INET          2
#define LNX_SOCK_STREAM      1
#define LNX_SOCK_DGRAM       2
#define LNX_SOCK_TYPE_MASK   0xf
#define LNX_SOCK_NONBLOCK    0x800
#define LNX_SOCK_CLOEXEC     0x80000
#define LNX_IPPROTO_TCP      6
#define LNX_IPPROTO_UDP      17
#define LNX_MSG_PEEK         0x2
#define LNX_MSG_DONTWAIT     0x40
#define LNX_MSG_NOSIGNAL     0x4000
#define LNX_SOL_SOCKET       1
#define LNX_SO_REUSEADDR     2
#define LNX_SO_TYPE          3
#define LNX_SO_ERROR         4
#define LNX_SO_SNDBUF        7
#define LNX_SO_RCVBUF        8
#define LNX_SO_KEEPALIVE     9
#define LNX_SO_LINGER        13
#define LNX_SO_RCVTIMEO      20
#define LNX_SO_SNDTIMEO      21
#define LNX_IPPROTO_IP       0
#define LNX_IP_TOS           1
#define LNX_IP_TTL           2
#define LNX_IP_MTU_DISCOVER  10
#define LNX_IP_RECVERR       11
#define NET_IP_DEFAULT_TTL   64
#define LNX_TCP_NODELAY      1
#define LNX_TCP_KEEPIDLE     4
#define LNX_TCP_KEEPINTVL    5
#define LNX_TCP_KEEPCNT      6
#define LNX_O_RDWR           2
#define LNX_O_NONBLOCK       0x800
#define LNX_FD_CLOEXEC       1
#define LNX_F_GETFD          1
#define LNX_F_SETFD          2
#define LNX_F_GETFL          3
#define LNX_F_SETFL          4
#define LNX_POLLIN           0x001
#define LNX_POLLOUT          0x004
#define LNX_POLLERR          0x008
#define LNX_POLLHUP          0x010
#define LNX_POLLNVAL         0x020
#define LNX_EBADF            9
#define LNX_EAGAIN           11
#define LNX_EFAULT           14
#define LNX_EINVAL           22
#define LNX_EPIPE            32
#define LNX_EDESTADDRREQ     89
#define LNX_EMSGSIZE         90
#define LNX_ENOPROTOOPT      92
#define LNX_EPROTONOSUPPORT  93
#define LNX_EOPNOTSUPP       95
#define LNX_EAFNOSUPPORT     97
#define LNX_EISCONN          106
#define LNX_ENOTCONN         107
#define LNX_ETIMEDOUT        110
#define LNX_ECONNREFUSED     111
#define LNX_EALREADY         114
#define LNX_EINPROGRESS      115
#define NET_SEND_FLAGS_OK    (LNX_MSG_DONTWAIT | LNX_MSG_NOSIGNAL)
#define NET_RECV_FLAGS_OK    (LNX_MSG_PEEK | LNX_MSG_DONTWAIT | LNX_MSG_NOSIGNAL)

static int net_fd_tcp(long fd) {
    return net_sockets && fd >= NET_FD_BASE && fd < NET_FD_BASE + NET_SOCKETS &&
           net_sockets[fd - NET_FD_BASE].in_use;
}

static int net_fd_udp(long fd) {
    return net_udp_sockets && fd >= NET_UDP_FD_BASE &&
           fd < NET_UDP_FD_BASE + NET_UDP_SOCKETS &&
           net_udp_sockets[fd - NET_UDP_FD_BASE].in_use;
}

int net_sys_is_socket(long fd) {
    return net_fd_tcp(fd) || net_fd_udp(fd);
}

static struct net_udp_sock *net_udp_alloc(void) {
    int i;
    if (!net_udp_sockets) return 0;
    for (i = 0; i < NET_UDP_SOCKETS; i++) {
        if (!net_udp_sockets[i].in_use) {
            kmemset(&net_udp_sockets[i], 0, sizeof(net_udp_sockets[i]));
            net_udp_sockets[i].in_use = 1;
            return &net_udp_sockets[i];
        }
    }
    return 0;
}

/* Next free datagram port in the user ephemeral range. */
static unsigned short net_udp_ephemeral(void) {
    int tries;
    for (tries = 0; tries <= NET_UDP_EPHEMERAL_MAX - NET_UDP_EPHEMERAL_MIN; tries++) {
        unsigned short p = net_udp_sport++;
        int i, used = 0;
        if (net_udp_sport > NET_UDP_EPHEMERAL_MAX) net_udp_sport = NET_UDP_EPHEMERAL_MIN;
        for (i = 0; i < NET_UDP_SOCKETS; i++)
            if (net_udp_sockets[i].in_use && net_udp_sockets[i].lport == p) used = 1;
        if (!used) return p;
    }
    return 0;
}

/* Queue a received datagram on the user socket bound to dport (and, when
 * connected, from that peer only). 1 when a socket owned the port (full
 * queues drop the datagram, like a full Linux receive buffer). */
static int net_udp_deliver(const unsigned char sip[4], unsigned short sport,
                           unsigned short dport, const unsigned char *data,
                           unsigned len) {
    int i;
    if (!net_udp_sockets) return 0;
    for (i = 0; i < NET_UDP_SOCKETS; i++) {
        struct net_udp_sock *u = &net_udp_sockets[i];
        struct net_udp_dgram *g;
        if (!u->in_use || u->lport != dport) continue;
        if (u->connected && (kmemcmp(u->pip, sip, 4) != 0 || u->pport != sport)) continue;
        if (u->count >= NET_UDP_QUEUE || len > NET_UDP_DGRAM_MAX) return 1;
        g = &u->q[(u->head + u->count) % NET_UDP_QUEUE];
        g->len = (unsigned short)len;
        g->sport = sport;
        kmemcpy(g->sip, sip, 4);
        kmemcpy(g->data, data, len);
        u->count++;
        return 1;
    }
    return 0;
}

static void net_put_sockaddr(unsigned char *sa, const unsigned char ip[4], unsigned short port) {
    sa[0] = LNX_AF_INET;
    sa[1] = 0;
    net_put16(sa + 2, port);
    kmemcpy(sa + 4, ip, 4);
    kmemset(sa + 8, 0, 8);
}

/* Store a sockaddr_in at a user address with a user socklen_t length
 * pointer, truncating like Linux and reporting the full length. */
static long net_store_sockaddr(long addr, long lenp, const unsigned char ip[4],
                               unsigned short port) {
    unsigned char sa[NET_SOCKADDR_IN_LEN];
    int len;
    if (!addr || !lenp) return 0;
    if (!user_range_ok((unsigned long)lenp, sizeof(int))) return -LNX_EFAULT;
    len = *(int *)lenp;
    if (len < 0) return -LNX_EINVAL;
    if (len > NET_SOCKADDR_IN_LEN) len = NET_SOCKADDR_IN_LEN;
    if (len > 0 && !user_range_ok((unsigned long)addr, (unsigned long)len)) return -LNX_EFAULT;
    net_put_sockaddr(sa, ip, port);
    kmemcpy((void *)addr, sa, (unsigned long)len);
    *(int *)lenp = NET_SOCKADDR_IN_LEN;
    return 0;
}

/* Read a user sockaddr_in (AF_INET, at least 16 bytes). */
static long net_load_sockaddr(long addr, long len, unsigned char ip[4], unsigned short *port) {
    const unsigned char *sa = (const unsigned char *)addr;
    if (len < NET_SOCKADDR_IN_LEN) return -LNX_EINVAL;
    if (!user_range_ok((unsigned long)addr, NET_SOCKADDR_IN_LEN)) return -LNX_EFAULT;
    if (sa[0] != LNX_AF_INET || sa[1] != 0) return -LNX_EAFNOSUPPORT;
    *port = net_get16(sa + 2);
    kmemcpy(ip, sa + 4, 4);
    return 0;
}

/* Drive a non-blocking connect: retransmit the SYN on schedule, fail it at
 * the deadline (ETIMEDOUT) or on a reset (ECONNREFUSED). */
static void net_tcp_progress(struct net_tcp_sock *s) {
    unsigned long now;
    if (!s->connecting) return;
    net_drv_poll();
    now = net_time_ms();
    if (s->state == NET_TCP_ESTABLISHED) {
        s->connecting = 0;
        return;
    }
    if (s->state == NET_TCP_SYN_SENT) {
        if (now >= s->syn_deadline) {
            s->connecting = 0;
            s->so_error = LNX_ETIMEDOUT;
            s->state = NET_TCP_CLOSED;
        } else if (now >= s->syn_retry) {
            net_tcp_xmit(s, 0x02, 0, 0, 0);
            s->syn_retry = now + NET_RETRY_MS;
        }
        return;
    }
    s->connecting = 0;
    s->so_error = LNX_ECONNREFUSED;
    s->state = NET_TCP_CLOSED;
}

long net_sys_socket(long a1, long a2, long a3) {
    long type = a2 & LNX_SOCK_TYPE_MASK;
    int nonblock = (a2 & LNX_SOCK_NONBLOCK) != 0;
    int cloexec = (a2 & LNX_SOCK_CLOEXEC) != 0;
    if (a1 != LNX_AF_INET) return -LNX_EAFNOSUPPORT;
    if (a2 & ~(long)(LNX_SOCK_TYPE_MASK | LNX_SOCK_NONBLOCK | LNX_SOCK_CLOEXEC)) return -LNX_EINVAL;
    if (type == LNX_SOCK_STREAM) {
        struct net_tcp_sock *s;
        if (a3 != 0 && a3 != LNX_IPPROTO_TCP) return -LNX_EPROTONOSUPPORT;
        s = net_sock_alloc();
        if (!s) return -12;
        s->nonblock = nonblock;
        s->cloexec = cloexec;
        return NET_FD_BASE + net_sock_index(s);
    }
    if (type == LNX_SOCK_DGRAM) {
        struct net_udp_sock *u;
        if (a3 != 0 && a3 != LNX_IPPROTO_UDP) return -LNX_EPROTONOSUPPORT;
        u = net_udp_alloc();
        if (!u) return -12;
        u->nonblock = nonblock;
        u->cloexec = cloexec;
        return NET_UDP_FD_BASE + (long)(u - net_udp_sockets);
    }
    return -LNX_EPROTONOSUPPORT;
}

long net_sys_connect(long fd, long sockaddr, long addrlen) {
    unsigned char ip[4];
    unsigned short port;
    long rc;
    if (!net_sys_is_socket(fd)) return -LNX_EBADF;
    rc = net_load_sockaddr(sockaddr, addrlen, ip, &port);
    if (rc) return rc;
    if (net_fd_udp(fd)) {
        struct net_udp_sock *u = &net_udp_sockets[fd - NET_UDP_FD_BASE];
        if (!u->lport) u->lport = net_udp_ephemeral();
        if (!u->lport) return -12;
        kmemcpy(u->pip, ip, 4);
        u->pport = port;
        u->connected = 1;
        return 0;
    }
    {
        struct net_tcp_sock *s = &net_sockets[fd - NET_FD_BASE];
        if (s->connecting) {
            net_tcp_progress(s);
            if (s->connecting) return -LNX_EALREADY;
        }
        if (s->state == NET_TCP_ESTABLISHED) return -LNX_EISCONN;
        if (!s->nonblock) {
            if (!net_tcp_connect_into(s, ip, port)) {
                s->in_use = 1;
                return -LNX_ECONNREFUSED;
            }
            return 0;
        }
        kmemcpy(s->dip, ip, 4);
        s->dport = port;
        s->sport = net_tcp_sport++;
        s->seq = net_tcp_seq;
        net_tcp_seq += 0x1000;
        s->ack = 0;
        s->so_error = 0;
        s->state = NET_TCP_SYN_SENT;
        s->connecting = 1;
        s->syn_deadline = net_time_ms() + NET_CONNECT_TMO_S * 1000UL;
        s->syn_retry = net_time_ms() + NET_RETRY_MS;
        net_tcp_xmit(s, 0x02, 0, 0, 1);
        net_tcp_progress(s);
        return s->state == NET_TCP_ESTABLISHED ? 0 : -LNX_EINPROGRESS;
    }
}

long net_sys_bind(long fd, long sockaddr, long addrlen) {
    unsigned char ip[4];
    unsigned short port;
    long rc;
    if (!net_sys_is_socket(fd)) return -LNX_EBADF;
    rc = net_load_sockaddr(sockaddr, addrlen, ip, &port);
    if (rc) return rc;
    if (net_fd_udp(fd)) {
        struct net_udp_sock *u = &net_udp_sockets[fd - NET_UDP_FD_BASE];
        if (u->lport) return -LNX_EINVAL;
        u->lport = port ? port : net_udp_ephemeral();
        return u->lport ? 0 : -12;
    }
    {
        struct net_tcp_sock *s = &net_sockets[fd - NET_FD_BASE];
        if (s->state != NET_TCP_CLOSED || s->bound || port == 0) return -LNX_EINVAL;
        s->sport = port;
        s->bound = 1;
        return 0;
    }
}

long net_sys_listen(long fd, long backlog) {
    struct net_tcp_sock *s;
    (void)backlog;
    if (!net_fd_tcp(fd)) return net_fd_udp(fd) ? -LNX_EOPNOTSUPP : -LNX_EBADF;
    s = &net_sockets[fd - NET_FD_BASE];
    if (!s->bound || s->state != NET_TCP_CLOSED) return -LNX_EINVAL;
    s->pending = -1;
    s->state = NET_TCP_LISTEN;
    return 0;
}

long net_sys_accept(long fd, long sockaddr, long addrlen) {
    struct net_tcp_sock *s;
    int child;
    if (!net_fd_tcp(fd)) return net_fd_udp(fd) ? -LNX_EOPNOTSUPP : -LNX_EBADF;
    s = &net_sockets[fd - NET_FD_BASE];
    if (s->state != NET_TCP_LISTEN) return -LNX_EINVAL;
    child = net_accept(fd - NET_FD_BASE, NET_ACCEPT_TMO_MS);
    if (child < 0) return -LNX_EAGAIN;
    if (sockaddr && addrlen) {
        struct net_tcp_sock *c = &net_sockets[child];
        long rc = net_store_sockaddr(sockaddr, addrlen, c->dip, c->dport);
        if (rc) return rc;
    }
    return NET_FD_BASE + child;
}

/* Send len validated bytes: a stream sends synchronously (stop-and-wait),
 * a datagram goes out as one UDP datagram to `to` or the connected peer. */
static long net_send_bytes(long fd, const unsigned char *buf, long len,
                           const unsigned char *to_ip, unsigned short to_port) {
    if (net_fd_udp(fd)) {
        struct net_udp_sock *u = &net_udp_sockets[fd - NET_UDP_FD_BASE];
        const unsigned char *ip = to_ip;
        unsigned short port = to_port;
        if (!ip) {
            if (!u->connected) return -LNX_EDESTADDRREQ;
            ip = u->pip;
            port = u->pport;
        }
        if (len > NET_UDP_DGRAM_MAX) return -LNX_EMSGSIZE;
        if (!u->lport) u->lport = net_udp_ephemeral();
        if (!u->lport) return -12;
        if (!net_udp_send(ip, u->lport, port, buf, (unsigned)len)) return -LNX_EAGAIN;
        return len;
    }
    {
        struct net_tcp_sock *s = &net_sockets[fd - NET_FD_BASE];
        int rc;
        net_tcp_progress(s);
        if (s->connecting) return -LNX_EAGAIN;
        if (s->state != NET_TCP_ESTABLISHED) return s->rx_eof ? -LNX_EPIPE : -LNX_ENOTCONN;
        rc = net_tcp_send(s, (const char *)buf, (int)len);
        return rc < 0 ? -LNX_EPIPE : rc;
    }
}

long net_sys_sendto(long fd, long buf, long len, long flags, long to, long tolen) {
    unsigned char ip[4];
    unsigned short port = 0;
    if (!net_sys_is_socket(fd)) return -LNX_EBADF;
    if (flags & ~(long)NET_SEND_FLAGS_OK) return -LNX_EOPNOTSUPP;
    if (len < 0) return -LNX_EINVAL;
    if (len > 0 && !user_range_ok((unsigned long)buf, (unsigned long)len)) return -LNX_EFAULT;
    if (to && net_fd_udp(fd)) {
        long rc = net_load_sockaddr(to, tolen, ip, &port);
        if (rc) return rc;
        return net_send_bytes(fd, (const unsigned char *)buf, len, ip, port);
    }
    return net_send_bytes(fd, (const unsigned char *)buf, len, 0, 0);
}

long net_sys_recvfrom(long fd, long buf, long len, long flags, long from, long fromlen) {
    int nonblock;
    if (!net_sys_is_socket(fd)) return -LNX_EBADF;
    if (flags & ~(long)NET_RECV_FLAGS_OK) return -LNX_EOPNOTSUPP;
    if (len < 0) return -LNX_EINVAL;
    if (len > 0 && !user_range_ok((unsigned long)buf, (unsigned long)len)) return -LNX_EFAULT;
    if (net_fd_udp(fd)) {
        struct net_udp_sock *u = &net_udp_sockets[fd - NET_UDP_FD_BASE];
        struct net_udp_dgram *g;
        long n;
        nonblock = u->nonblock || (flags & LNX_MSG_DONTWAIT);
        for (;;) {
            net_drv_poll();
            if (u->count) break;
            if (nonblock) return -LNX_EAGAIN;
            yield();
        }
        g = &u->q[u->head];
        n = g->len < len ? g->len : len;
        kmemcpy((void *)buf, g->data, (unsigned long)n);
        if (from) {
            long rc = net_store_sockaddr(from, fromlen, g->sip, g->sport);
            if (rc) return rc;
        }
        if (!(flags & LNX_MSG_PEEK)) {
            u->head = (u->head + 1) % NET_UDP_QUEUE;
            u->count--;
        }
        return n;
    }
    {
        struct net_tcp_sock *s = &net_sockets[fd - NET_FD_BASE];
        nonblock = s->nonblock || (flags & LNX_MSG_DONTWAIT);
        for (;;) {
            unsigned avail;
            net_tcp_progress(s);
            net_drv_poll();
            avail = s->rx_head - s->rx_tail;
            if (avail) {
                unsigned take = avail > (unsigned)len ? (unsigned)len : avail;
                kmemcpy((void *)buf, s->rx + s->rx_tail, take);
                if (!(flags & LNX_MSG_PEEK)) {
                    s->rx_tail += take;
                    if (s->rx_tail == s->rx_head) { s->rx_tail = 0; s->rx_head = 0; }
                }
                if (from) {
                    long rc = net_store_sockaddr(from, fromlen, s->dip, s->dport);
                    if (rc) return rc;
                }
                return (long)take;
            }
            if (s->rx_eof || s->state == NET_TCP_DEAD) return 0;
            if (!s->connecting && s->state != NET_TCP_ESTABLISHED) return -LNX_ENOTCONN;
            if (nonblock) return -LNX_EAGAIN;
            yield();
        }
    }
}

/* Gather one msghdr's iovecs (validated) into kbuf, at most cap bytes. */
static long net_gather_msg(long msg, unsigned char *kbuf, long cap) {
    long iov, iovlen, i, total = 0;
    if (!user_range_ok((unsigned long)msg, NET_MSGHDR_LEN)) return -LNX_EFAULT;
    iov = *(const long *)(msg + NET_MSGHDR_IOV_OFF);
    iovlen = *(const long *)(msg + NET_MSGHDR_IOVLEN_OFF);
    if (iovlen < 0 || iovlen > NET_IOV_MAX) return -LNX_EMSGSIZE;
    if (iovlen && !user_range_ok((unsigned long)iov, (unsigned long)iovlen * NET_IOV_LEN))
        return -LNX_EFAULT;
    for (i = 0; i < iovlen; i++) {
        long base = *(const long *)(iov + i * NET_IOV_LEN);
        long n = *(const long *)(iov + i * NET_IOV_LEN + 8);
        if (n < 0) return -LNX_EINVAL;
        if (n > cap - total) return -LNX_EMSGSIZE;
        if (n && !user_range_ok((unsigned long)base, (unsigned long)n)) return -LNX_EFAULT;
        kmemcpy(kbuf + total, (const void *)base, (unsigned long)n);
        total += n;
    }
    return total;
}

long net_sys_sendmsg(long fd, long msg, long flags) {
    unsigned char *kbuf;
    unsigned char ip[4];
    unsigned short port = 0;
    long name, namelen, n, rc;
    long cap = net_fd_udp(fd) ? NET_UDP_DGRAM_MAX : NET_SOCK_RX_BUF;
    if (!net_sys_is_socket(fd)) return -LNX_EBADF;
    if (flags & ~(long)NET_SEND_FLAGS_OK) return -LNX_EOPNOTSUPP;
    if (!user_range_ok((unsigned long)msg, NET_MSGHDR_LEN)) return -LNX_EFAULT;
    name = *(const long *)(msg + NET_MSGHDR_NAME_OFF);
    namelen = (long)*(const unsigned int *)(msg + NET_MSGHDR_NAMELEN_OFF);
    kbuf = (unsigned char *)kmalloc((unsigned long)cap);
    if (!kbuf) return -12;
    n = net_gather_msg(msg, kbuf, cap);
    if (n < 0) { kfree(kbuf); return n; }
    if (name && net_fd_udp(fd)) {
        rc = net_load_sockaddr(name, namelen, ip, &port);
        rc = rc ? rc : net_send_bytes(fd, kbuf, n, ip, port);
    } else {
        rc = net_send_bytes(fd, kbuf, n, 0, 0);
    }
    kfree(kbuf);
    return rc;
}

/* sendmmsg (307): glibc's resolver sends its A and AAAA queries together
 * and treats ENOSYS as a failed lookup. Returns the messages sent, storing
 * each one's byte count in msg_len; an error on the first is returned. */
long net_sys_sendmmsg(long fd, long vec, long vlen, long flags) {
    long i;
    if (!net_sys_is_socket(fd)) return -LNX_EBADF;
    if (vlen < 0) return -LNX_EINVAL;
    if (vlen > NET_MMSG_MAX) vlen = NET_MMSG_MAX;
    if (vlen && !user_range_ok((unsigned long)vec, (unsigned long)vlen * NET_MMSGHDR_LEN))
        return -LNX_EFAULT;
    for (i = 0; i < vlen; i++) {
        long m = vec + i * NET_MMSGHDR_LEN;
        long rc = net_sys_sendmsg(fd, m, flags);
        if (rc < 0) return i ? i : rc;
        *(unsigned int *)(m + NET_MMSGHDR_LEN_OFF) = (unsigned int)rc;
    }
    return vlen;
}

long net_sys_shutdown(long fd, long how) {
    (void)how;
    if (net_fd_udp(fd)) return 0;
    if (!net_fd_tcp(fd)) return -LNX_EBADF;
    net_tcp_close(&net_sockets[fd - NET_FD_BASE]);
    net_sockets[fd - NET_FD_BASE].in_use = 1;
    return 0;
}

long net_sys_close(long fd) {
    if (net_fd_udp(fd)) {
        net_udp_sockets[fd - NET_UDP_FD_BASE].in_use = 0;
        return 0;
    }
    if (!net_fd_tcp(fd)) return -LNX_EBADF;
    tls_free_fd((int)(fd - NET_FD_BASE));
    net_tcp_close(&net_sockets[fd - NET_FD_BASE]);
    return 0;
}

long net_sys_setsockopt(long fd, long level, long name, long val, long len) {
    if (!net_sys_is_socket(fd)) return -LNX_EBADF;
    if (len < 0) return -LNX_EINVAL;
    if (len > 0 && !user_range_ok((unsigned long)val, (unsigned long)len)) return -LNX_EFAULT;
    if (level == LNX_SOL_SOCKET) {
        switch (name) {
        case LNX_SO_REUSEADDR: case LNX_SO_KEEPALIVE: case LNX_SO_SNDBUF:
        case LNX_SO_RCVBUF: case LNX_SO_LINGER: case LNX_SO_RCVTIMEO:
        case LNX_SO_SNDTIMEO:
            return 0;
        default:
            return -LNX_ENOPROTOOPT;
        }
    }
    if (level == LNX_IPPROTO_TCP && net_fd_tcp(fd)) {
        switch (name) {
        case LNX_TCP_NODELAY: case LNX_TCP_KEEPIDLE: case LNX_TCP_KEEPINTVL:
        case LNX_TCP_KEEPCNT:
            return 0;
        default:
            return -LNX_ENOPROTOOPT;
        }
    }
    if (level == LNX_IPPROTO_IP) {
        switch (name) {
        case LNX_IP_TOS: case LNX_IP_TTL: case LNX_IP_MTU_DISCOVER:
        case LNX_IP_RECVERR:
            return 0;
        default:
            return -LNX_ENOPROTOOPT;
        }
    }
    return -LNX_ENOPROTOOPT;
}

long net_sys_getsockopt(long fd, long level, long name, long val, long lenp) {
    int v, len;
    if (!net_sys_is_socket(fd)) return -LNX_EBADF;
    if (!user_range_ok((unsigned long)lenp, sizeof(int))) return -LNX_EFAULT;
    len = *(int *)lenp;
    if (len < (int)sizeof(int)) return -LNX_EINVAL;
    if (!user_range_ok((unsigned long)val, sizeof(int))) return -LNX_EFAULT;
    if (level == LNX_SOL_SOCKET) {
        switch (name) {
        case LNX_SO_ERROR:
            v = 0;
            if (net_fd_tcp(fd)) {
                struct net_tcp_sock *s = &net_sockets[fd - NET_FD_BASE];
                net_tcp_progress(s);
                v = s->so_error;
                s->so_error = 0;
            }
            break;
        case LNX_SO_TYPE:
            v = net_fd_udp(fd) ? LNX_SOCK_DGRAM : LNX_SOCK_STREAM;
            break;
        case LNX_SO_RCVBUF:
            v = net_fd_udp(fd) ? NET_UDP_QUEUE * NET_UDP_DGRAM_MAX : NET_SOCK_RX_BUF;
            break;
        case LNX_SO_SNDBUF:
            v = NET_TX_MAX;
            break;
        case LNX_SO_KEEPALIVE: case LNX_SO_REUSEADDR:
            v = 0;
            break;
        default:
            return -LNX_ENOPROTOOPT;
        }
    } else if (level == LNX_IPPROTO_TCP && net_fd_tcp(fd) && name == LNX_TCP_NODELAY) {
        v = 1;
    } else if (level == LNX_IPPROTO_IP && (name == LNX_IP_TOS || name == LNX_IP_RECVERR)) {
        v = 0;
    } else if (level == LNX_IPPROTO_IP && name == LNX_IP_TTL) {
        v = NET_IP_DEFAULT_TTL;
    } else {
        return -LNX_ENOPROTOOPT;
    }
    *(int *)val = v;
    *(int *)lenp = (int)sizeof(int);
    return 0;
}

long net_sys_getsockname(long fd, long addr, long lenp) {
    if (net_fd_udp(fd)) {
        struct net_udp_sock *u = &net_udp_sockets[fd - NET_UDP_FD_BASE];
        return net_store_sockaddr(addr, lenp, net_our_ip, u->lport);
    }
    if (!net_fd_tcp(fd)) return -LNX_EBADF;
    return net_store_sockaddr(addr, lenp, net_our_ip, net_sockets[fd - NET_FD_BASE].sport);
}

long net_sys_getpeername(long fd, long addr, long lenp) {
    if (net_fd_udp(fd)) {
        struct net_udp_sock *u = &net_udp_sockets[fd - NET_UDP_FD_BASE];
        if (!u->connected) return -LNX_ENOTCONN;
        return net_store_sockaddr(addr, lenp, u->pip, u->pport);
    }
    if (!net_fd_tcp(fd)) return -LNX_EBADF;
    {
        struct net_tcp_sock *s = &net_sockets[fd - NET_FD_BASE];
        net_tcp_progress(s);
        if (s->state != NET_TCP_ESTABLISHED) return -LNX_ENOTCONN;
        return net_store_sockaddr(addr, lenp, s->dip, s->dport);
    }
}

/* fcntl on a socket: O_NONBLOCK through F_GETFL/F_SETFL, FD_CLOEXEC
 * recorded through F_GETFD/F_SETFD (sockets live in one table shared by
 * fork, so execve keeps them; docs/spec/network.md). */
long net_sys_fcntl(long fd, long cmd, long arg) {
    int *nb, *ce;
    if (net_fd_udp(fd)) {
        nb = &net_udp_sockets[fd - NET_UDP_FD_BASE].nonblock;
        ce = &net_udp_sockets[fd - NET_UDP_FD_BASE].cloexec;
    } else if (net_fd_tcp(fd)) {
        nb = &net_sockets[fd - NET_FD_BASE].nonblock;
        ce = &net_sockets[fd - NET_FD_BASE].cloexec;
    } else {
        return -LNX_EBADF;
    }
    switch (cmd) {
    case LNX_F_GETFL: return LNX_O_RDWR | (*nb ? LNX_O_NONBLOCK : 0);
    case LNX_F_SETFL: *nb = (arg & LNX_O_NONBLOCK) != 0; return 0;
    case LNX_F_GETFD: return *ce ? LNX_FD_CLOEXEC : 0;
    case LNX_F_SETFD: *ce = (arg & LNX_FD_CLOEXEC) != 0; return 0;
    default: return -LNX_EINVAL;
    }
}

#define LNX_FIONREAD  0x541B
#define LNX_FIONBIO   0x5421
#define LNX_FIONCLEX  0x5450
#define LNX_FIOCLEX   0x5451
#define LNX_ENOTTY    25

/* ioctl on a socket: FIONREAD answers the bytes a read would return now
 * (a stream's buffered bytes, the size of a datagram socket's next
 * datagram), FIONBIO sets O_NONBLOCK from the int at arg, FIOCLEX and
 * FIONCLEX record FD_CLOEXEC; terminal and every other request is ENOTTY,
 * as Linux answers it for a socket. arg is validated by the caller. */
long net_sys_ioctl(long fd, long req, long arg) {
    int *nb, *ce;
    if (net_fd_udp(fd)) {
        struct net_udp_sock *u = &net_udp_sockets[fd - NET_UDP_FD_BASE];
        nb = &u->nonblock;
        ce = &u->cloexec;
        if (req == LNX_FIONREAD) {
            net_drv_poll();
            *(int *)arg = u->count ? (int)u->q[u->head].len : 0;
            return 0;
        }
    } else if (net_fd_tcp(fd)) {
        struct net_tcp_sock *s = &net_sockets[fd - NET_FD_BASE];
        nb = &s->nonblock;
        ce = &s->cloexec;
        if (req == LNX_FIONREAD) {
            net_tcp_progress(s);
            net_drv_poll();
            *(int *)arg = (int)(s->rx_head - s->rx_tail);
            return 0;
        }
    } else {
        return -LNX_EBADF;
    }
    switch (req) {
    case LNX_FIONBIO: *nb = *(const int *)arg != 0; return 0;
    case LNX_FIOCLEX: *ce = 1; return 0;
    case LNX_FIONCLEX: *ce = 0; return 0;
    default: return -LNX_ENOTTY;
    }
}

/* poll(2) readiness of a socket descriptor. */
static unsigned short net_socket_revents(long fd) {
    unsigned short rev = 0;
    if (net_fd_udp(fd)) {
        net_drv_poll();
        if (net_udp_sockets[fd - NET_UDP_FD_BASE].count) rev |= LNX_POLLIN;
        return (unsigned short)(rev | LNX_POLLOUT);
    }
    if (!net_fd_tcp(fd)) return LNX_POLLNVAL;
    {
        struct net_tcp_sock *s = &net_sockets[fd - NET_FD_BASE];
        net_tcp_progress(s);
        if (s->rx_tail < s->rx_head || s->rx_eof) rev |= LNX_POLLIN;
        if (s->state == NET_TCP_LISTEN && s->pending >= 0) rev |= LNX_POLLIN;
        if (s->state == NET_TCP_ESTABLISHED && !s->tx_pending) rev |= LNX_POLLOUT;
        if (s->so_error) rev |= LNX_POLLERR | LNX_POLLHUP;
        if (s->state == NET_TCP_DEAD) rev |= LNX_POLLHUP;
        return rev;
    }
}

long net_sys_poll(long fds, long nfds, long timeout_ms) {
    /* Linux pollfd: int fd; short events; short revents. Every entry's
     * revents is written (zero when not ready), a negative fd is skipped,
     * sockets report through net_socket_revents and every other
     * descriptor (pipes, eventfds, files, console) through
     * kfd_poll_revents; POLLERR, POLLHUP and POLLNVAL are reported even
     * when not requested, like Linux. The wait yields between rounds so
     * the writer it waits for can run. */
    unsigned long deadline = net_time_ms() + (timeout_ms > 0 ? (unsigned long)timeout_ms : 0);
    long n, ready;
    for (;;) {
        ready = 0;
        for (n = 0; n < nfds; n++) {
            /* Host order: pollfd is a CPU struct, not a wire format. */
            char *entry = (char *)fds + n * 8;
            int fd;
            unsigned short events;
            unsigned short revents = 0;
            kmemcpy(&fd, entry, 4);
            kmemcpy(&events, entry + 4, 2);
            if (fd >= NET_FD_BASE && fd < NET_UDP_FD_BASE + NET_UDP_SOCKETS) {
                revents = (unsigned short)(net_socket_revents(fd) &
                    (events | LNX_POLLERR | LNX_POLLHUP | LNX_POLLNVAL));
            } else if (fd >= 0) {
                revents = (unsigned short)(kfd_poll_revents(fd) &
                    (events | LNX_POLLERR | LNX_POLLHUP | LNX_POLLNVAL));
            }
            kmemcpy(entry + 6, &revents, 2);
            if (revents) ready++;
        }
        if (ready > 0) return ready;
        if (timeout_ms == 0) return 0;
        net_drv_poll();
        if (timeout_ms > 0 && net_time_ms() > deadline) return 0;
        yield();
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
    unsigned int tx_frames, rx_frames;
    if (!net_drv_present()) {
        vga_puts("net: no NIC found\n");
        return;
    }
    if (net_use_virtio) {
        vnet_counters(&tx_frames, &rx_frames);
        kprintf("virtio-net iobase 0x%x\n", vnet_iobase());
    } else {
        rtl_counters(&tx_frames, &rx_frames);
        kprintf("rtl8139  iobase 0x%x\n", rtl_iobase());
    }
    kprintf("mac      %02x:%02x:%02x:%02x:%02x:%02x\n",
            net_mac[0], net_mac[1], net_mac[2], net_mac[3], net_mac[4], net_mac[5]);
    kprintf("ip       %u.%u.%u.%u/24\n", net_our_ip[0], net_our_ip[1], net_our_ip[2], net_our_ip[3]);
    vga_puts("gateway  10.0.2.2  dns 10.0.2.3\n");
    kprintf("tx       %u frames, %u bytes\n", tx_frames, net_tx_bytes);
    kprintf("rx       %u frames, %u bytes, %u dropped, %u v6 dropped\n", rx_frames, net_rx_bytes, net_rx_dropped, net6_rx_dropped);
}

/** Docstring: Copy the station MAC and IP out for status screens. */
void net_get_addrs(unsigned char mac_out[NET_ETH_ALEN], unsigned char ip_out[4]) {
    int i;
    for (i = 0; i < NET_ETH_ALEN; i++) mac_out[i] = net_mac[i];
    for (i = 0; i < 4; i++) ip_out[i] = net_our_ip[i];
}

void net_cmd_ping(const char *ip_text) {
    unsigned char ip[4];
    if (!net_drv_present()) { vga_puts("net: no NIC found\n"); return; }
    if (!net_parse_ip(ip_text, ip)) {
        vga_puts("usage: net ping <ip>\n");
        return;
    }
    if (net_ping(ip)) kprintf("reply from %s\n", ip_text);
    else kprintf("no reply from %s\n", ip_text);
}

void net_cmd_dns(const char *host) {
    unsigned char ip[4];
    if (!net_drv_present()) { vga_puts("net: no NIC found\n"); return; }
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
    rtl_init();
    net_use_virtio = vnet_init() ? 1 : 0;
    if (net_use_virtio) {
        vnet_get_mac(net_mac);
    } else {
        rtl_get_mac(net_mac);
    }
    kprintf("net: backend=%s\n", net_use_virtio ? "virtio" : "rtl8139");
    net_sockets = (struct net_tcp_sock *)kmalloc(NET_SOCKETS *
                                                 sizeof(*net_sockets));
    if (!net_sockets) kprintf("net: no socket table (out of memory)\n");
    net_udp_sockets = (struct net_udp_sock *)kmalloc(NET_UDP_SOCKETS *
                                                     sizeof(*net_udp_sockets));
    if (net_udp_sockets)
        kmemset(net_udp_sockets, 0, NET_UDP_SOCKETS * sizeof(*net_udp_sockets));
    else
        kprintf("net: no datagram socket table (out of memory)\n");
    net_register_symbols();
}
