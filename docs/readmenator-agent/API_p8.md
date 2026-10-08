# API (page 8 of 19)
Previous: [API_p7.md](API_p7.md)

## net/net.c
Depends on: `headers/drivers/virtio_net.h`, `headers/net.h`, `headers/net/rtl8139.h`, `headers/tls.h`
- `net_drv_send` (function) `net/net.c:37` `static int net_drv_send(const unsigned char *frame, unsigned len)`
- `net_drv_poll` (function) `net/net.c:42` `static void net_drv_poll(void)`
- `net_drv_present` (function) `net/net.c:47` `static int net_drv_present(void)`
- `net_put16` (function) `net/net.c:56` `static void net_put16(unsigned char *p, unsigned short v)`
- `net_put32` (function) `net/net.c:61` `static void net_put32(unsigned char *p, unsigned int v)`
- `net_get16` (function) `net/net.c:68` `static unsigned short net_get16(const unsigned char *p)`
- `net_get32` (function) `net/net.c:72` `static unsigned int net_get32(const unsigned char *p)`
- `net_checksum` (function) `net/net.c:77` `static unsigned short net_checksum(const void *data, unsigned len)`
- `net_arp_store` (function) `net/net.c:102` `static void net_arp_store(const unsigned char *ip, const unsigned char *mac)`
- `net_arp_lookup` (function) `net/net.c:117` `static int net_arp_lookup(const unsigned char *ip, unsigned char *mac_out)`
- `net_arp_request` (function) `net/net.c:128` `static void net_arp_request(const unsigned char *ip)`
- `net_arp_resolve` (function) `net/net.c:146` `static int net_arp_resolve(const unsigned char *ip, unsigned char *mac_out)` -- kmemcpy(frame + 6, net_mac, NET_ETH_ALEN); net_put16(frame + 12, NET_ETHERTYPE_ARP); net_put16(frame + 14, 1)...
- `net_ip_send` (function) `net/net.c:171` `static int net_ip_send(const unsigned char *dip, unsigned char proto,
                       cons...`
- `net_udp_send` (function) `net/net.c:207` `static int net_udp_send(const unsigned char *dip, unsigned short sport,
                        u...`
- `net_dns_parse` (function) `net/net.c:229` `static void net_dns_parse(const unsigned char *data, unsigned len)` -- net_put16(pkt + 6, 0);                    /* checksum optional for UDP kmemcpy(pkt + 8, data, len); return...
- `net_dns_resolve` (function) `net/net.c:267` `static int net_dns_resolve(const char *host, unsigned char ip_out[4])` -- rtype = net_get16(data + pos); rdlen = net_get16(data + pos + 8); pos += 10; if (pos + rdlen > len) return; if...
- `net_udp_send` (function) `net/net.c:328` `net_udp_send((const unsigned char[])`
- `net_icmp_rx` (function) `net/net.c:347` `static void net_icmp_rx(const unsigned char *ip, unsigned len)`
- `net_ping` (function) `net/net.c:376` `static int net_ping(const unsigned char ip[4])`
- `net_sock_alloc` (function) `net/net.c:435` `static struct net_tcp_sock *net_sock_alloc(void)`
- `net_sock_index` (function) `net/net.c:450` `static int net_sock_index(const struct net_tcp_sock *s)`
- `net_tcp_checksum` (function) `net/net.c:459` `static unsigned short net_tcp_checksum(const unsigned char *src, const unsigned char *dst,
      ...` -- } } return 0; } static int net_sock_index(const struct net_tcp_sock *s) { int i; if (!net_sockets) return -1; for (i...
- `net_udp_checksum_ok` (function) `net/net.c:475` `static int net_udp_checksum_ok(const unsigned char *src, const unsigned char *dst,
              ...` -- const unsigned char *seg, unsigned len) { unsigned char buf[NET_TX_MAX + 12]; unsigned total = 12 + len...
- `net_tcp_xmit` (function) `net/net.c:491` `static int net_tcp_xmit(struct net_tcp_sock *s, unsigned flags,
                        const uns...`
- `net_tcp_rx` (function) `net/net.c:525` `static void net_tcp_rx(const unsigned char *ip, unsigned len)`
- `net_tcp_passive_open` (function) `net/net.c:653` `static int net_tcp_passive_open(struct net_tcp_sock *ls,
        const unsigned char peer[4], uns...` -- Passive open: park a SYN_RCVD child on a LISTEN socket and answer SYN-ACK.
- `net_tcp_connect_into` (function) `net/net.c:677` `static int net_tcp_connect_into(struct net_tcp_sock *s, const unsigned char ip[4],
              ...` -- kmemcpy(c->dip, peer, 4); c->dport = pport; c->sport = lport; c->seq = net_tcp_seq; net_tcp_seq += 0x1000...
- `net_tcp_send` (function) `net/net.c:704` `static int net_tcp_send(struct net_tcp_sock *s, const char *buf, int len)` -- unsigned long retry = net_time_ms() + NET_RETRY_MS; while (net_time_ms() < retry && s->state == NET_TCP_SYN_SENT)...
- `net_tcp_recv` (function) `net/net.c:730` `static int net_tcp_recv(struct net_tcp_sock *s, char *buf, int len)` -- net_time_ms() < deadline) { unsigned long retry = net_time_ms() + NET_RETRY_MS; while (net_time_ms() < retry &&...
- `net_tcp_close` (function) `net/net.c:768` `static void net_tcp_close(struct net_tcp_sock *s)`
- `net_rx_handle_frame` (function) `net/net.c:788` `void net_rx_handle_frame(const unsigned char *frame, unsigned len)`
- `net_open` (function) `net/net.c:850` `int net_open(void)`
- `net_connect` (function) `net/net.c:856` `int net_connect(const char *host, unsigned short port)`
- `net_send` (function) `net/net.c:865` `int net_send(int fd, const char *buf, int len)`
- `net_recv` (function) `net/net.c:870` `int net_recv(int fd, char *buf, int len)`
- `net_recv_timeout` (function) `net/net.c:875` `int net_recv_timeout(int fd, char *buf, int len, unsigned long timeout_ms)`
- `net_close` (function) `net/net.c:880` `void net_close(int fd)`
- `net_listen` (function) `net/net.c:891` `int net_listen(unsigned short port)` -- Docstring: Allocate a socket bound to a local port and listening. * Returns the socket index, or -1 when the table...
- `net_accept_nb` (function) `net/net.c:906` `int net_accept_nb(int fd)` -- Docstring: Take a pending child off a LISTEN socket without waiting.
- `polling` (function) `net/net.c:923` `* without polling (the peer's ACK arrives through the driver poll). */
int net_accept(int fd, uns...`
- `net_sock_state` (function) `net/net.c:940` `int net_sock_state(int fd)` -- Docstring: Socket state for diagnostics (the `net` builtin and the * httpd selftest). -1 on a wild fd.
- `net_sys_socket` (function) `net/net.c:992` `long net_sys_socket(long a1, long a2, long a3)`
- `net_sys_connect` (function) `net/net.c:1001` `long net_sys_connect(long fd, long sockaddr, long addrlen)`
- `net_sys_bind` (function) `net/net.c:1014` `long net_sys_bind(long fd, long sockaddr, long addrlen)`
- `net_sys_listen` (function) `net/net.c:1029` `long net_sys_listen(long fd, long backlog)`
- `net_sys_accept` (function) `net/net.c:1040` `long net_sys_accept(long fd, long sockaddr, long addrlen)`
- `net_sys_sendto` (function) `net/net.c:1059` `long net_sys_sendto(long fd, long buf, long len, long flags, long to, long tolen)`
- `net_sys_recvfrom` (function) `net/net.c:1068` `long net_sys_recvfrom(long fd, long buf, long len, long flags, long from, long fromlen)`
- `net_sys_shutdown` (function) `net/net.c:1078` `long net_sys_shutdown(long fd, long how)`
- `net_sys_close` (function) `net/net.c:1085` `long net_sys_close(long fd)`
- `net_sys_poll` (function) `net/net.c:1092` `long net_sys_poll(long fds, long nfds, long timeout_ms)`
- `net_sys_dns` (function) `net/net.c:1129` `long net_sys_dns(long host)` -- MiniOS syscall 200: resolve a hostname, returned as a network-order * 32-bit address (like inet_addr), or -1 on failure.
- `net_parse_ip` (function) `net/net.c:1140` `static int net_parse_ip(const char *text, unsigned char ip[4])`
- `net_cmd_status` (function) `net/net.c:1165` `void net_cmd_status(void)`
- `net_get_addrs` (function) `net/net.c:1187` `void net_get_addrs(unsigned char mac_out[NET_ETH_ALEN], unsigned char ip_out[4])` -- kprintf("virtio-net iobase 0x%x\n", vnet_iobase()); } else { rtl_counters(&tx_frames, &rx_frames); kprintf("rtl8139...
- `net_cmd_ping` (function) `net/net.c:1193` `void net_cmd_ping(const char *ip_text)`
- `net_cmd_dns` (function) `net/net.c:1204` `void net_cmd_dns(const char *host)`
- `net_register_symbols` (function) `net/net.c:1217` `void net_register_symbols(void)`
- `net_init` (function) `net/net.c:1225` `void net_init(void)`

## net/rtl8139.c
Depends on: `headers/drivers/pci.h`, `headers/net.h`, `headers/net/rtl8139.h`, `headers/sched.h`
- `outl_port` (function) `net/rtl8139.c:29` `static void outl_port(unsigned short port, unsigned int val)` -- Byte/word port I/O comes from kernel.h (outb/inb/outw/inw, same asm). * Only the dword pair stays local: the shared...
- `inl_port` (function) `net/rtl8139.c:33` `static unsigned int inl_port(unsigned short port)`
- `rtl_reg8` (function) `net/rtl8139.c:39` `static unsigned char rtl_reg8(unsigned short off)`
- `rtl_reg8_w` (function) `net/rtl8139.c:40` `static void rtl_reg8_w(unsigned short off, unsigned char v)`
- `rtl_reg16` (function) `net/rtl8139.c:41` `static unsigned short rtl_reg16(unsigned short off)`
- `rtl_reg16_w` (function) `net/rtl8139.c:42` `static void rtl_reg16_w(unsigned short off, unsigned short v)`
- `rtl_reg32` (function) `net/rtl8139.c:43` `static unsigned int rtl_reg32(unsigned short off)`
- `rtl_reg32_w` (function) `net/rtl8139.c:44` `static void rtl_reg32_w(unsigned short off, unsigned int v)`
- `rtl_find` (function) `net/rtl8139.c:58` `static unsigned short rtl_find(void)` -- PCI config space lives in drivers/pci.h now (shared with virtio-blk and future devices); only the dword port pair...
- `deleted` (function) `net/rtl8139.c:79` `* been deleted (a second base/per-ms pair beside ktime's is a second
 * clock, and drivers must n...`
- `rtl_present` (function) `net/rtl8139.c:99` `int rtl_present(void)`
- `rtl_reset` (function) `net/rtl8139.c:103` `static void rtl_reset(void)`
- `rtl_init` (function) `net/rtl8139.c:112` `void rtl_init(void)`
- `rtl_tx_wait` (function) `net/rtl8139.c:149` `static int rtl_tx_wait(unsigned slot, unsigned long deadline)`
- `rtl_send` (function) `net/rtl8139.c:158` `int rtl_send(const unsigned char *frame, unsigned len)`
- `rtl_get_mac` (function) `net/rtl8139.c:182` `void rtl_get_mac(unsigned char out[NET_ETH_ALEN])`
- `rtl_iobase` (function) `net/rtl8139.c:187` `unsigned short rtl_iobase(void)`
- `rtl_counters` (function) `net/rtl8139.c:191` `void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames)`
- `rtl_poll` (function) `net/rtl8139.c:215` `void rtl_poll(void)`

## net/tls.c
Depends on: `headers/tls.h`, `headers/tls_port.h`, `headers/tls_roots.h`
- `tls_fail` (function) `net/tls.c:25` `static void tls_fail(struct tls_session *s, const char *stage, const char *reason)`
- `tls_fd_of` (function) `net/tls.c:33` `static int tls_fd_of(const struct tls_session *s)`
- `tls_free_fd` (function) `net/tls.c:40` `void tls_free_fd(int fd)`
- `tls_aad` (function) `net/tls.c:52` `static void tls_aad(unsigned char aad[13], int type, unsigned long long seq,
                    ...` -- Build the TLS 1.2 AEAD additional data: seq(8) || type || 0303 || * TLSCompressed.length (the plaintext length, RFC...
- `number` (function) `net/tls.c:64` `* The nonce_explicit is the sequence number (RFC 5288 allows it and * OpenSSL uses it);`
- `tls_send_record` (function) `net/tls.c:66` `static int tls_send_record(struct tls_session *s, int type,
                           const unsi...` -- Send one record: header || nonce_explicit(8) || ciphertext || tag.
- `tls_send_raw_record` (function) `net/tls.c:95` `static int tls_send_raw_record(struct tls_session *s, int type,
                               co...` -- for (i = 0; i < 8; i++) buf[5 + i] = (unsigned char)(s->cli_seq >> (56 - i * 8)); TLS_MEMCPY(nonce, s->cli_salt, 4)...
- `tls_read_record` (function) `net/tls.c:114` `static int tls_read_record(struct tls_session *s, int fd, int deadline_ms)` -- Read one record: header into s->rec_hdr, payload into s->rec.
- `exchange` (function) `net/tls.c:173` `* key exchange (ClientHello, ClientKeyExchange) go out in plaintext
 * records, as TLS 1.2 requir...`
- `build_client_hello` (function) `net/tls.c:190` `static int build_client_hello(struct tls_session *s, unsigned char *out)` -- const unsigned char *body, int len) { if (len < 0 || len > 1024) return -1; s->pt[0] = (unsigned char)type; s->pt[1]...
- `client_finish_flight` (function) `net/tls.c:244` `static int client_finish_flight(struct tls_session *s)` -- out[pos++] = 0x00; out[pos++] = 0x06; out[pos++] = 0x04; out[pos++] = 0x01;   /* rsa_pkcs1_sha256 out[pos++] = 0x04...
- `parse_server_hello` (function) `net/tls.c:340` `static int parse_server_hello(struct tls_session *s,
                              const unsigned...`
- `parse_certificate` (function) `net/tls.c:370` `static int parse_certificate(struct tls_session *s,
                             const unsigned c...`
- `parse_server_key_exchange` (function) `net/tls.c:401` `static int parse_server_key_exchange(struct tls_session *s,
                                     ...`
- `tls_handshake` (function) `net/tls.c:466` `int tls_handshake(int fd, const char *host)`
- `tls_send` (function) `net/tls.c:687` `int tls_send(int fd, const char *buf, int len)`
- `tls_recv` (function) `net/tls.c:696` `int tls_recv(int fd, char *buf, int len)`
- `tls_sys_handshake` (function) `net/tls.c:772` `long tls_sys_handshake(long fd, long host)` -- if !defined(TLS_TEST) && !defined(TLS_RING3)
- `tls_sys_send` (function) `net/tls.c:777` `long tls_sys_send(long fd, long buf, long len)`
- `tls_sys_recv` (function) `net/tls.c:782` `long tls_sys_recv(long fd, long buf, long len)`
- `tls_rdtsc` (function) `net/tls.c:789` `static inline unsigned long long tls_rdtsc(void)`
- `tls_random` (function) `net/tls.c:795` `void tls_random(unsigned char *out, unsigned len)`
- `outb` (function) `net/tls.c:810` `static inline void outb(unsigned short port, unsigned char v)` -- unsigned long long seed = tls_rdtsc() ^ ((unsigned long long)net_time_ms() << 33); unsigned i; static unsigned long...
- `inb` (function) `net/tls.c:813` `static inline unsigned char inb(unsigned short port)`
- `cmos_read` (function) `net/tls.c:821` `static inline unsigned char cmos_read(unsigned char reg)` -- /* The port helpers in net.c are static; these live here for the RTC. #ifndef PORT_IO_DEFINED #define...
- `tls_now_days` (function) `net/tls.c:826` `long tls_now_days(void)`

## net/tls_crypto.c
Depends on: `headers/tls.h`, `headers/tls_port.h`
- `sha256_rotr` (function) `net/tls_crypto.c:33` `static unsigned sha256_rotr(unsigned x, unsigned n)`
- `sha256_init` (function) `net/tls_crypto.c:37` `void sha256_init(struct sha256_ctx *c)`
- `sha256_block` (function) `net/tls_crypto.c:50` `static void sha256_block(struct sha256_ctx *c, const unsigned char *p)`
- `sha256_update` (function) `net/tls_crypto.c:80` `void sha256_update(struct sha256_ctx *c, const unsigned char *data, unsigned len)`
- `sha256_final` (function) `net/tls_crypto.c:105` `void sha256_final(struct sha256_ctx *c, unsigned char out[32])`
- `sha256` (function) `net/tls_crypto.c:126` `void sha256(const unsigned char *data, unsigned len, unsigned char out[32])`
- `hmac_sha256` (function) `net/tls_crypto.c:135` `void hmac_sha256(const unsigned char *key, unsigned klen,
                 const unsigned char *d...`
- `p_hash` (function) `net/tls_crypto.c:165` `static void p_hash(const unsigned char *secret, unsigned secret_len,
                   const uns...`
- `tls_prf` (function) `net/tls_crypto.c:188` `void tls_prf(const unsigned char *secret, unsigned secret_len,
             const char *label, co...`
- `aes_xtime` (function) `net/tls_crypto.c:230` `static unsigned aes_xtime(unsigned x)`
- `aes_key_expand` (function) `net/tls_crypto.c:235` `static void aes_key_expand(const unsigned char key[16], unsigned rk[44])`
- `aes_mixcol` (function) `net/tls_crypto.c:253` `static void aes_mixcol(unsigned a0, unsigned a1, unsigned a2, unsigned a3,
                      ...`
- `aes128_encrypt_block` (function) `net/tls_crypto.c:263` `void aes128_encrypt_block(const unsigned char key[16],
                          const unsigned c...`
- `gf_shift_right` (function) `net/tls_crypto.c:321` `static gf128 gf_shift_right(gf128 v)`
- `word` (function) `net/tls_crypto.c:326` `* of the low word (hi holds bits 64..127, lo bits 0..63). Masked in, * so the shift never branches on key bits. */...`
- `gf_mul` (function) `net/tls_crypto.c:334` `static gf128 gf_mul(gf128 z, gf128 h)` -- z = z * h, in GF(2^128), MSB-first.
- `gf_put` (function) `net/tls_crypto.c:351` `static gf128 gf_put(const unsigned char *p)`
- `ghash_blocks` (function) `net/tls_crypto.c:361` `static gf128 ghash_blocks(gf128 z, gf128 h, const unsigned char *data, unsigned len)`
- `gcm_tag_core` (function) `net/tls_crypto.c:384` `static void gcm_tag_core(const unsigned char key[16],
                         const unsigned cha...` -- if (len > 0) { unsigned char pad[16]; gf128 b; TLS_MEMSET(pad, 0, 16); TLS_MEMCPY(pad, data, len); b = gf_put(pad)...
- `gcm_ctr_core` (function) `net/tls_crypto.c:427` `static void gcm_ctr_core(const unsigned char key[16],
                         const unsigned cha...`
- `tls_nonce` (function) `net/tls_crypto.c:450` `static void tls_nonce(const unsigned char salt[4], unsigned long long seq,
                      ...` -- TLS_MEMCPY(blk, nonce, 12); blk[12] = (unsigned char)(ctr >> 24); blk[13] = (unsigned char)(ctr >> 16); blk[14] =...
- `gcm_tag` (function) `net/tls_crypto.c:457` `static void gcm_tag(const unsigned char key[16], const unsigned char salt[4],
                   ...`
- `gcm_ctr` (function) `net/tls_crypto.c:467` `static void gcm_ctr(const unsigned char key[16], const unsigned char salt[4],
                   ...`
- `aes128_gcm_seal` (function) `net/tls_crypto.c:475` `int aes128_gcm_seal(const unsigned char key[16],
                    const unsigned char salt[4],...`
- `aes128_gcm_open` (function) `net/tls_crypto.c:487` `int aes128_gcm_open(const unsigned char key[16],
                    const unsigned char salt[4],...`
- `aes128_gcm_seal_core` (function) `net/tls_crypto.c:505` `int aes128_gcm_seal_core(const unsigned char key[16],
                         const unsigned cha...`
- `aes128_gcm_open_core` (function) `net/tls_crypto.c:516` `int aes128_gcm_open_core(const unsigned char key[16],
                         const unsigned cha...`
- `bn_zero` (function) `net/tls_crypto.c:537` `static void bn_zero(unsigned *a, int nw)`
- `bn_is_zero` (function) `net/tls_crypto.c:542` `static int bn_is_zero(const unsigned *a, int nw)`
- `bn_cmp` (function) `net/tls_crypto.c:549` `static int bn_cmp(const unsigned *a, const unsigned *b, int nw)`
- `bn_add` (function) `net/tls_crypto.c:559` `static unsigned bn_add(const unsigned *a, const unsigned *b, unsigned *r, int nw)` -- for (i = 0; i < nw; i++) v |= a[i]; return v == 0; } static int bn_cmp(const unsigned *a, const unsigned *b, int nw)...
- `bn_sub` (function) `net/tls_crypto.c:571` `static unsigned bn_sub(const unsigned *a, const unsigned *b, unsigned *r, int nw)` -- /* r = a + b; returns carry out. static unsigned bn_add(const unsigned *a, const unsigned *b, unsigned *r, int nw) {...
- `bn_dbl_mod` (function) `net/tls_crypto.c:584` `static void bn_dbl_mod(const unsigned *a, const unsigned *n, const unsigned *v,
                 ...` -- r = 2a mod n, for a < n. v = 2^(32nw) mod n = 2^(32nw) - n (the * Montgomery "one"): 2a + carry means 2a - 2^(32nw)...
- `bn_mont_mul` (function) `net/tls_crypto.c:596` `static void bn_mont_mul(const unsigned *a, const unsigned *b, const unsigned *n,
                ...` -- Montgomery multiplication. n is odd, n0inv = -n^(-1) mod 2^32. r = a*b*R^-1 mod n, R = 2^(32nw). * a, b < n.
- `bn_mont_n0inv` (function) `net/tls_crypto.c:635` `static unsigned bn_mont_n0inv(unsigned n0)` -- carry = v >> 32; } s = (unsigned long long)t[nw] + carry; t[nw - 1] = (unsigned)s; t[nw] = t[nw + 1] + (unsigned)(s...
- `bn_mont_r2` (function) `net/tls_crypto.c:643` `static void bn_mont_r2(const unsigned *n, const unsigned *v, int nw,
                       unsig...` -- } else { for (i = 0; i < nw; i++) r[i] = t[i]; } } /* -n^(-1) mod 2^32 via Newton iteration (n0 must be odd). static...
- `bn_from_be` (function) `net/tls_crypto.c:663` `static void bn_from_be(const unsigned char *bytes, unsigned len,
                       unsigned ...`
- `bn_to_be` (function) `net/tls_crypto.c:671` `static void bn_to_be(const unsigned *a, unsigned char *out, unsigned len)`
- `mont_init` (function) `net/tls_crypto.c:677` `static void mont_init(struct mont_ctx *m, const unsigned char *p_bytes,
                      uns...`
- `mont_to` (function) `net/tls_crypto.c:689` `static void mont_to(struct mont_ctx *m, const unsigned *a, unsigned *r)`
- `mont_from` (function) `net/tls_crypto.c:693` `static void mont_from(struct mont_ctx *m, const unsigned *a, unsigned *r)`
- `mont_mul` (function) `net/tls_crypto.c:700` `static void mont_mul(struct mont_ctx *m, const unsigned *a, const unsigned *b,
                  ...`
- `mont_sqr` (function) `net/tls_crypto.c:705` `static void mont_sqr(struct mont_ctx *m, const unsigned *a, unsigned *r)`
- `mont_add` (function) `net/tls_crypto.c:712` `static void mont_add(struct mont_ctx *m, const unsigned *a, const unsigned *b,
                  ...` -- Field add/sub over the mont modulus (in Montgomery domain).
- `mont_sub` (function) `net/tls_crypto.c:721` `static void mont_sub(struct mont_ctx *m, const unsigned *a, const unsigned *b,
                  ...`
- `mont_inv` (function) `net/tls_crypto.c:736` `static void mont_inv(struct mont_ctx *m, const unsigned *a, unsigned *r)` -- Field inverse via Fermat: a^(p-2) mod p (a in Montgomery domain; * the result stays in Montgomery domain).
- `ec_init` (function) `net/tls_crypto.c:848` `static void ec_init(struct ec_curve *c, const unsigned char *p,
                    const unsigne...`
- `jpt_is_inf` (function) `net/tls_crypto.c:865` `static int jpt_is_inf(const struct jpt *p, int nw)`
- `jpt_set_inf` (function) `net/tls_crypto.c:869` `static void jpt_set_inf(struct jpt *p, int nw)`
- `jpt_copy` (function) `net/tls_crypto.c:875` `static void jpt_copy(struct jpt *d, const struct jpt *s, int nw)`
- `jpt_cswap` (function) `net/tls_crypto.c:885` `static void jpt_cswap(struct jpt *a, struct jpt *b, unsigned mask, int nw)` -- bn_zero(p->y, nw); bn_zero(p->z, nw); } static void jpt_copy(struct jpt *d, const struct jpt *s, int nw) { int i...
- `jpt_dbl` (function) `net/tls_crypto.c:896` `static void jpt_dbl(struct ec_curve *c, const struct jpt *p1, struct jpt *p3)` -- } /* Constant-time swap of two points on a 0/~0 mask. static void jpt_cswap(struct jpt *a, struct jpt *b, unsigned...
- `jpt_add` (function) `net/tls_crypto.c:936` `static void jpt_add(struct ec_curve *c, const struct jpt *p1, const struct jpt *p2,
             ...` -- mont_sqr(m, E, F); mont_add(m, D, D, t);          /* 2D mont_sub(m, F, t, p3->x);      /* X3 = F - 2D mont_sub(m, D...
- `jpt_scalar_mult` (function) `net/tls_crypto.c:980` `static void jpt_scalar_mult(struct ec_curve *c, const struct jpt *base,
                         ...` -- Constant-iteration scalar multiplication: the classic ladder. * Fixed iteration count, no table lookups indexed by...
- `jpt_to_affine` (function) `net/tls_crypto.c:1007` `static void jpt_to_affine(struct ec_curve *c, const struct jpt *p,
                          unsi...` -- Affine from Jacobian: x = X/Z^2, y = Y/Z^3.
- `jpt_from_affine` (function) `net/tls_crypto.c:1032` `static int jpt_from_affine(struct ec_curve *c, const unsigned char *x_bytes,
                    ...` -- Affine from bytes with on-curve validation.
- `ec_curve_by_id` (function) `net/tls_crypto.c:1076` `static struct ec_curve *ec_curve_by_id(int curve)`
- `ec_boot` (function) `net/tls_crypto.c:1080` `static void ec_boot(void)`
- `p256_scalar_mult` (function) `net/tls_crypto.c:1088` `int p256_scalar_mult(const unsigned char scalar[32],
                     const unsigned char qx[...`
- `p384_scalar_mult` (function) `net/tls_crypto.c:1101` `int p384_scalar_mult(const unsigned char scalar[48],
                     const unsigned char qx[...`
- `p256_ecdh` (function) `net/tls_crypto.c:1114` `int p256_ecdh(const unsigned char priv[32],
              const unsigned char peer_x[32], const u...`
- `der_parse_sig` (function) `net/tls_crypto.c:1129` `static int der_parse_sig(const unsigned char *sig, unsigned sig_len,
                         con...`
- `ecdsa_verify` (function) `net/tls_crypto.c:1163` `int ecdsa_verify(int curve, const unsigned char pub_x[], const unsigned char pub_y[],
           ...`
- `rsa_verify_digestinfo` (function) `net/tls_crypto.c:1261` `static int rsa_verify_digestinfo(const unsigned char *em, unsigned em_len,
                      ...` -- EMSA-PKCS1-v1_5 DigestInfo check for an arbitrary hash: the encoding is 00 01 FF..
- `rsa_pkcs1_verify_raw` (function) `net/tls_crypto.c:1285` `static int rsa_pkcs1_verify_raw(const unsigned char *n, unsigned n_len,
                         ...` -- diff |= em[i] ^ 0xff; } if (i >= em_len) return -1;         /* no separator if (i < 10) return -1;              /*...
- `rsa_pkcs1_verify_sha256` (function) `net/tls_crypto.c:1326` `int rsa_pkcs1_verify_sha256(const unsigned char *n, unsigned n_len,
                            c...`
- `rsa_pkcs1_verify_sha384` (function) `net/tls_crypto.c:1340` `int rsa_pkcs1_verify_sha384(const unsigned char *n, unsigned n_len,
                            c...`
- `sha384_rotr` (function) `net/tls_crypto.c:1386` `static unsigned long long sha384_rotr(unsigned long long x, unsigned n)`
- `sha384_raw` (function) `net/tls_crypto.c:1390` `static void sha384_raw(const unsigned char *data, unsigned len,
                       unsigned c...`
- `sha384` (function) `net/tls_crypto.c:1506` `void sha384(const unsigned char *data, unsigned len, unsigned char out[48])`
- `p256_point_valid` (function) `net/tls_crypto.c:1512` `int p256_point_valid(const unsigned char x[32], const unsigned char y[32])`
- `p256_pub` (function) `net/tls_crypto.c:1520` `int p256_pub(const unsigned char priv[32],
             unsigned char x[32], unsigned char y[32])`
- `p256_scalar_valid` (function) `net/tls_crypto.c:1539` `int p256_scalar_valid(const unsigned char scalar[32])`

## net/tls_x509.c
Depends on: `headers/tls.h`, `headers/tls_port.h`
- `oid_eq` (function) `net/tls_x509.c:36` `static int oid_eq(const unsigned char *bytes, unsigned len,
                  const unsigned char...`
- `der_next` (function) `net/tls_x509.c:51` `static int der_next(const unsigned char *p, unsigned limit, unsigned *pos,
                    st...` -- Parse the TLV at p[pos]; advances pos to the first byte after it. * Returns 0 on success, -1 on any bound violation.
- `der_container` (function) `net/tls_x509.c:82` `static int der_container(const unsigned char *p, unsigned limit, unsigned *pos,
                 ...` -- len = (len << 8) | p[(*pos)++]; } } else { len = p[(*pos)++]; } if (len > limit - *pos) return -1; out->val = p +...
- `days_from_civil` (function) `net/tls_x509.c:94` `static long days_from_civil(int y, int m, int d)`
- `der_time_to_days` (function) `net/tls_x509.c:106` `static long der_time_to_days(const struct der_tlv *t)` -- /* ---- Time ---- static long days_from_civil(int y, int m, int d) { long era, doe, yoe; int doy; y -= m <= 2 ?
- `name_find_cn` (function) `net/tls_x509.c:135` `static int name_find_cn(const unsigned char *p, unsigned limit,
                        struct x5...` -- } if (mon < 1 || mon > 12 || day < 1 || day > 31 || year < 1970 || year > 2100) return -1; return...
- `san_add` (function) `net/tls_x509.c:178` `static void san_add(struct x509_sans *out, const unsigned char *v, unsigned len)`
- `san_parse` (function) `net/tls_x509.c:186` `static void san_parse(const unsigned char *p, unsigned limit,
                      struct x509_s...` -- struct x509_sans { unsigned char dns[TLS_SAN_MAX][64]; unsigned      len[TLS_SAN_MAX]; int           count; }...
- `spki_parse` (function) `net/tls_x509.c:203` `static int spki_parse(const unsigned char *p, unsigned limit,
                      struct tls_pu...` -- unsigned seq_len, pos = 0; out->count = 0; if (der_container(p, limit, &pos, &seq, &seq_len) != 0) return; pos = 0...
- `cert_parse` (function) `net/tls_x509.c:279` `static int cert_parse(const unsigned char *der, unsigned len,
                      struct x509_c...`
- `ascii_lower` (function) `net/tls_x509.c:392` `static int ascii_lower(int c)`
- `host_match_exact` (function) `net/tls_x509.c:397` `static int host_match_exact(const char *host, const unsigned char *name,
                        ...` -- } } } } return 0; } /* ---- Hostname matching ---- static int ascii_lower(int c) { return (c >= 'A' && c <= 'Z') ? c...
- `host_match_wildcard` (function) `net/tls_x509.c:410` `static int host_match_wildcard(const char *host, const unsigned char *name,
                     ...` -- Wildcard: "*.example.com" matches exactly one label ("a.example.com", * never "a.b.example.com" nor "example.com").
- `host_matches` (function) `net/tls_x509.c:431` `static int host_matches(const char *host, const struct x509_cert *leaf)`
- `tls_x509_parse_pubkey` (function) `net/tls_x509.c:452` `int tls_x509_parse_pubkey(const unsigned char *der, unsigned len,
                          struc...`
- `pubkey_equal` (function) `net/tls_x509.c:468` `static int pubkey_equal(const struct tls_pubkey *a, const struct tls_pubkey *b)` -- Trust anchors are matched by public key, not by self-signature: a presented root is often a cross-signed copy...
- `cert_verify_signature` (function) `net/tls_x509.c:479` `static int cert_verify_signature(const struct x509_cert *cert,
                                 c...` -- signature-verified: an attacker cannot present a top cert carrying an embedded root's public key unless the chain...
- `tls_x509_verify_chain` (function) `net/tls_x509.c:521` `int tls_x509_verify_chain(const unsigned char *chain, unsigned chain_len,
                       ...`

## progs/asm/aes.s
- `aes_rk` (function) `progs/asm/aes.s:3`
- `aes_sb` (function) `progs/asm/aes.s:7`
- `aes_rc` (function) `progs/asm/aes.s:11`
- `aes_st` (function) `progs/asm/aes.s:15`
- `aes_iv` (function) `progs/asm/aes.s:19`
- `aes_read_all` (function) `progs/asm/aes.s:23`
- `aes_write_all` (function) `progs/asm/aes.s:238`
- `aes_has` (function) `progs/asm/aes.s:345`
- `hex_val` (function) `progs/asm/aes.s:498`
- `aes_parse_hex` (function) `progs/asm/aes.s:620`
- `aes_gf_mul` (function) `progs/asm/aes.s:783`
- `aes_xtime` (function) `progs/asm/aes.s:884`
- `aes_rotl8` (function) `progs/asm/aes.s:933`
- `aes_init_tables` (function) `progs/asm/aes.s:970`
- `aes_key_expand` (function) `progs/asm/aes.s:1197`
- `aes_add_round_key` (function) `progs/asm/aes.s:1646`
- `aes_sub_bytes` (function) `progs/asm/aes.s:1721`
- `aes_shift_rows` (function) `progs/asm/aes.s:1774`
- `aes_mix_columns` (function) `progs/asm/aes.s:1993`
- `aes_cipher` (function) `progs/asm/aes.s:2466`
- `aes_iv_increment` (function) `progs/asm/aes.s:2565`
- `aes_ctr_crypt` (function) `progs/asm/aes.s:2648`
- `aes_hdr_put` (function) `progs/asm/aes.s:2791`
- `aes_hdr_get` (function) `progs/asm/aes.s:2906`
- `aes_tool_name` (function) `progs/asm/aes.s:3059`
- `aes_run` (function) `progs/asm/aes.s:3077`
- `main` (function) `progs/asm/aes.s:3807`

## progs/asm/cp.s
- `main` (function) `progs/asm/cp.s:3`

## progs/asm/fib.s
- `fib` (function) `progs/asm/fib.s:3`
- `main` (function) `progs/asm/fib.s:61`

## progs/asm/freedom.s
- `tls_close` (function) `progs/asm/freedom.s:3`
- `f_host` (function) `progs/asm/freedom.s:24`
- `f_path` (function) `progs/asm/freedom.s:28`
- `f_port` (function) `progs/asm/freedom.s:32`
- `f_secure` (function) `progs/asm/freedom.s:36`
- `f_loc` (function) `progs/asm/freedom.s:40`
- `f_redir` (function) `progs/asm/freedom.s:44`
- `f_status` (function) `progs/asm/freedom.s:48`
- `f_clen` (function) `progs/asm/freedom.s:52`
- `f_has_clen` (function) `progs/asm/freedom.s:56`
- `f_chunked` (function) `progs/asm/freedom.s:60`
- `f_hdr` (function) `progs/asm/freedom.s:64`
- `f_hlen` (function) `progs/asm/freedom.s:68`
- `f_tag` (function) `progs/asm/freedom.s:72`
- `f_suppress` (function) `progs/asm/freedom.s:76`
- `f_comment` (function) `progs/asm/freedom.s:80`
- `f_cmdash` (function) `progs/asm/freedom.s:84`
- `f_tagn` (function) `progs/asm/freedom.s:88`
- `f_tagnlen` (function) `progs/asm/freedom.s:92`
- `f_ent` (function) `progs/asm/freedom.s:96`
- `f_entlen` (function) `progs/asm/freedom.s:100`
- `f_ws` (function) `progs/asm/freedom.s:104`
- `f_utbuf` (function) `progs/asm/freedom.s:108`
- `f_utlen` (function) `progs/asm/freedom.s:112`
- `f_utrem` (function) `progs/asm/freedom.s:116`
- `f_attr_on` (function) `progs/asm/freedom.s:120`
- `f_waitq` (function) `progs/asm/freedom.s:124`
- `f_inval` (function) `progs/asm/freedom.s:128`
- `f_inval2` (function) `progs/asm/freedom.s:132`
- `f_attr` (function) `progs/asm/freedom.s:136`
- `f_attrlen` (function) `progs/asm/freedom.s:140`
- `f_val` (function) `progs/asm/freedom.s:144`
- `f_vallen` (function) `progs/asm/freedom.s:148`
- `f_id` (function) `progs/asm/freedom.s:152`
- `f_idlen` (function) `progs/asm/freedom.s:156`
- `f_cls` (function) `progs/asm/freedom.s:160`
- `f_clslen` (function) `progs/asm/freedom.s:164`
- `f_href` (function) `progs/asm/freedom.s:168`
- `f_hreflen` (function) `progs/asm/freedom.s:172`
- `f_rel_ss` (function) `progs/asm/freedom.s:176`
- `f_styleattr` (function) `progs/asm/freedom.s:180`
- `f_stylelen` (function) `progs/asm/freedom.s:184`
- `f_dump_css` (function) `progs/asm/freedom.s:188`
- `f_dump_dom` (function) `progs/asm/freedom.s:192`
- `f_mode` (function) `progs/asm/freedom.s:196`
- `f_rawcap` (function) `progs/asm/freedom.s:200`
- `f_depth` (function) `progs/asm/freedom.s:204`
- `f_dom` (function) `progs/asm/freedom.s:208`
- `f_domlen` (function) `progs/asm/freedom.s:212`
- `f_css` (function) `progs/asm/freedom.s:216`
- `f_csslen` (function) `progs/asm/freedom.s:220`
- `f_linkhost` (function) `progs/asm/freedom.s:224`
- `f_linkpath` (function) `progs/asm/freedom.s:228`
- `f_linkn` (function) `progs/asm/freedom.s:232`
- `f_cstage` (function) `progs/asm/freedom.s:236`
- `f_csize` (function) `progs/asm/freedom.s:240`
- `f_crem` (function) `progs/asm/freedom.s:244`
- `f_bdone` (function) `progs/asm/freedom.s:248`
- `atoi` (function) `progs/asm/freedom.s:252`
- `append` (function) `progs/asm/freedom.s:338`
- `ci_lower` (function) `progs/asm/freedom.s:437`
- `ci_starts` (function) `progs/asm/freedom.s:486`
- `ci_eq` (function) `progs/asm/freedom.s:559`
- `ci_index` (function) `progs/asm/freedom.s:656`
- `looks_like_url` (function) `progs/asm/freedom.s:715`
- `has_scheme` (function) `progs/asm/freedom.s:789`
- `make_search` (function) `progs/asm/freedom.s:1064`
- `split_url` (function) `progs/asm/freedom.s:1295`
- `resolve_redirect` (function) `progs/asm/freedom.s:1810`
- `put_ws` (function) `progs/asm/freedom.s:2333`
- `put_utf` (function) `progs/asm/freedom.s:2379`
- `put_text` (function) `progs/asm/freedom.s:2915`
- `put_entity` (function) `progs/asm/freedom.s:3018`
- `css_append` (function) `progs/asm/freedom.s:3849`
- `css_line` (function) `progs/asm/freedom.s:3920`
- `dom_append` (function) `progs/asm/freedom.s:3978`
- `dom_space` (function) `progs/asm/freedom.s:4049`
- `dom_nl` (function) `progs/asm/freedom.s:4083`
- `record_attr` (function) `progs/asm/freedom.s:4117`
- `is_void_tag` (function) `progs/asm/freedom.s:4449`
- `classify_tag` (function) `progs/asm/freedom.s:4757`
- `body_byte` (function) `progs/asm/freedom.s:5961`
- `head_line` (function) `progs/asm/freedom.s:7203`
- `parse_head` (function) `progs/asm/freedom.s:7460`
- `recv_body` (function) `progs/asm/freedom.s:7676`
- `send_all` (function) `progs/asm/freedom.s:7736`
- `fetch` (function) `progs/asm/freedom.s:7810`
- `fetch_css` (function) `progs/asm/freedom.s:9293`
- `print_css_dump` (function) `progs/asm/freedom.s:10112`
- `print_dom_dump` (function) `progs/asm/freedom.s:10212`
- `main` (function) `progs/asm/freedom.s:10291`

## progs/asm/http.s
- `atoi` (function) `progs/asm/http.s:3`
- `main` (function) `progs/asm/http.s:89`

## progs/asm/json.s
- `js_key` (function) `progs/asm/json.s:3`
- `js_str` (function) `progs/asm/json.s:7`
- `js_type` (function) `progs/asm/json.s:11`
- `js_num` (function) `progs/asm/json.s:15`
- `js_first` (function) `progs/asm/json.s:19`
- `js_count` (function) `progs/asm/json.s:23`
- `js_next` (function) `progs/asm/json.s:27`
- `js_n` (function) `progs/asm/json.s:31`
- `js_pool` (function) `progs/asm/json.s:35`
- `js_plen` (function) `progs/asm/json.s:39`
- `js_src` (function) `progs/asm/json.s:43`
- `js_pos` (function) `progs/asm/json.s:47`
- `js_len` (function) `progs/asm/json.s:51`
- `js_err` (function) `progs/asm/json.s:55`
- `js_read_all` (function) `progs/asm/json.s:59`
- `js_new` (function) `progs/asm/json.s:274`
- `js_skip_ws` (function) `progs/asm/json.s:306`
- `js_peek` (function) `progs/asm/json.s:397`
- `js_parse_string` (function) `progs/asm/json.s:437`
- `js_parse_number` (function) `progs/asm/json.s:851`
- `js_key_match` (function) `progs/asm/json.s:947`
- `js_parse_object` (function) `progs/asm/json.s:983`
- `js_parse_array` (function) `progs/asm/json.s:1335`
- `js_parse_value` (function) `progs/asm/json.s:1594`
- `js_indent` (function) `progs/asm/json.s:2481`
- `js_print_str` (function) `progs/asm/json.s:2524`
- `js_print_value` (function) `progs/asm/json.s:2747`
- `js_find_member` (function) `progs/asm/json.s:3313`
- `js_array_at` (function) `progs/asm/json.s:3391`
- `js_query` (function) `progs/asm/json.s:3460`
- `main` (function) `progs/asm/json.s:3772`

## progs/asm/ldhello.s
- `main` (function) `progs/asm/ldhello.s:3`

## progs/asm/lz4.s
- `lz4_has` (function) `progs/asm/lz4.s:3`
- `lz4_read_all` (function) `progs/asm/lz4.s:156`
- `lz4_write_all` (function) `progs/asm/lz4.s:371`
- `lz4_compress_file` (function) `progs/asm/lz4.s:478`
- `lz4_decompress_file` (function) `progs/asm/lz4.s:791`
- `main` (function) `progs/asm/lz4.s:1228`

## progs/asm/lzss.s
- `lz_win` (function) `progs/asm/lzss.s:3`
- `lz_src` (function) `progs/asm/lzss.s:7`
- `lz_srclen` (function) `progs/asm/lzss.s:11`
- `lz_srcpos` (function) `progs/asm/lzss.s:15`
- `lz_dst` (function) `progs/asm/lzss.s:19`
- `lz_dstcap` (function) `progs/asm/lzss.s:23`
- `lz_dstlen` (function) `progs/asm/lzss.s:27`
- `lz_err` (function) `progs/asm/lzss.s:31`
- `lz_buf` (function) `progs/asm/lzss.s:35`
- `lz_mask` (function) `progs/asm/lzss.s:39`
- `lz_in_getc` (function) `progs/asm/lzss.s:43`
- `lz_out_put` (function) `progs/asm/lzss.s:79`
- `lz_putbit1` (function) `progs/asm/lzss.s:116`
- `lz_putbit0` (function) `progs/asm/lzss.s:174`
- `lz_flush_bits` (function) `progs/asm/lzss.s:223`
- `lz_out_literal` (function) `progs/asm/lzss.s:251`
- `lz_out_pair` (function) `progs/asm/lzss.s:321`
- `lz_next_mb` (function) `progs/asm/lzss.s:447`
- `lz_encode` (function) `progs/asm/lzss.s:451`
- `lz_getbit` (function) `progs/asm/lzss.s:1051`
- `lz_decode` (function) `progs/asm/lzss.s:1171`
- `lz_hdr_put` (function) `progs/asm/lzss.s:1514`
- `lz_hdr_get` (function) `progs/asm/lzss.s:1629`
- `lz_has` (function) `progs/asm/lzss.s:1782`
- `lz_read_all` (function) `progs/asm/lzss.s:1935`
- `lz_write_all` (function) `progs/asm/lzss.s:2150`
- `lz_compress` (function) `progs/asm/lzss.s:2257`
- `lz_decompress` (function) `progs/asm/lzss.s:2628`
- `main` (function) `progs/asm/lzss.s:3178`


Next: [API_p9.md](API_p9.md)
