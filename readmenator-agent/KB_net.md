# Subsystem: net

## net/net.c
- Layer: utility
- Doc: MiniOS network stack: rtl8139 under QEMU slirp user networking.
- Language: c
- Symbols:
  - `net_arp_entry` (struct, line 69)
  - `net_dns_state` (struct, line 195)
  - `net_tcp_sock` (struct, line 382)
  - `net_put16` (function, line 31) `static void net_put16(unsigned char *p, unsigned short v)`
  - `net_put32` (function, line 36) `static void net_put32(unsigned char *p, unsigned int v)`
  - `net_get16` (function, line 43) `static unsigned short net_get16(const unsigned char *p)`
  - `net_get32` (function, line 47) `static unsigned int net_get32(const unsigned char *p)`
  - `net_checksum` (function, line 52) `static unsigned short net_checksum(const void *data, unsigned len)`
  - `net_arp_store` (function, line 77) `static void net_arp_store(const unsigned char *ip, const unsigned char *mac)`
  - `net_arp_lookup` (function, line 92) `static int net_arp_lookup(const unsigned char *ip, unsigned char *mac_out)`
  - `net_arp_request` (function, line 103) `static void net_arp_request(const unsigned char *ip)`
  - `net_arp_resolve` (function, line 121) `static int net_arp_resolve(const unsigned char *ip, unsigned char *mac_out)`
  - `net_ip_send` (function, line 146) `static int net_ip_send(const unsigned char *dip, unsigned char proto,
                       cons...`
  - `net_udp_send` (function, line 182) `static int net_udp_send(const unsigned char *dip, unsigned short sport,
                        u...`
  - `net_dns_parse` (function, line 204) `static void net_dns_parse(const unsigned char *data, unsigned len)`
  - `net_dns_resolve` (function, line 242) `static int net_dns_resolve(const char *host, unsigned char ip_out[4])`
  - `net_udp_send` (function, line 303) `net_udp_send((const unsigned char[])`
  - `net_icmp_rx` (function, line 322) `static void net_icmp_rx(const unsigned char *ip, unsigned len)`
  - `net_ping` (function, line 351) `static int net_ping(const unsigned char ip[4])`
  - `net_sock_alloc` (function, line 410) `static struct net_tcp_sock *net_sock_alloc(void)`
  - `net_sock_index` (function, line 425) `static int net_sock_index(const struct net_tcp_sock *s)`
  - `net_tcp_checksum` (function, line 434) `static unsigned short net_tcp_checksum(const unsigned char *src, const unsigned char *dst,
      ...`
  - `net_udp_checksum_ok` (function, line 450) `static int net_udp_checksum_ok(const unsigned char *src, const unsigned char *dst,
              ...`
  - `net_tcp_xmit` (function, line 466) `static int net_tcp_xmit(struct net_tcp_sock *s, unsigned flags,
                        const uns...`
  - `net_tcp_rx` (function, line 500) `static void net_tcp_rx(const unsigned char *ip, unsigned len)`
  - `net_tcp_passive_open` (function, line 628) `static int net_tcp_passive_open(struct net_tcp_sock *ls,
        const unsigned char peer[4], uns...`
  - `net_tcp_connect_into` (function, line 652) `static int net_tcp_connect_into(struct net_tcp_sock *s, const unsigned char ip[4],
              ...`
  - `net_tcp_send` (function, line 679) `static int net_tcp_send(struct net_tcp_sock *s, const char *buf, int len)`
  - `net_tcp_recv` (function, line 705) `static int net_tcp_recv(struct net_tcp_sock *s, char *buf, int len)`
  - `net_tcp_close` (function, line 743) `static void net_tcp_close(struct net_tcp_sock *s)`
  - `net_rx_handle_frame` (function, line 763) `void net_rx_handle_frame(const unsigned char *frame, unsigned len)`
  - `net_open` (function, line 821) `int net_open(void)`
  - `net_connect` (function, line 827) `int net_connect(const char *host, unsigned short port)`
  - `net_send` (function, line 836) `int net_send(int fd, const char *buf, int len)`
  - `net_recv` (function, line 841) `int net_recv(int fd, char *buf, int len)`
  - `net_recv_timeout` (function, line 846) `int net_recv_timeout(int fd, char *buf, int len, unsigned long timeout_ms)`
  - `net_close` (function, line 851) `void net_close(int fd)`
  - `net_listen` (function, line 862) `int net_listen(unsigned short port)`
  - `net_accept_nb` (function, line 877) `int net_accept_nb(int fd)`
  - `polling` (function, line 894) `* without polling (the peer's ACK arrives through rtl_poll). */
int net_accept(int fd, unsigned l...`
  - `net_sock_state` (function, line 911) `int net_sock_state(int fd)`
  - `net_sys_socket` (function, line 963) `long net_sys_socket(long a1, long a2, long a3)`
  - `net_sys_connect` (function, line 972) `long net_sys_connect(long fd, long sockaddr, long addrlen)`
  - `net_sys_bind` (function, line 985) `long net_sys_bind(long fd, long sockaddr, long addrlen)`
  - `net_sys_listen` (function, line 1000) `long net_sys_listen(long fd, long backlog)`
  - `net_sys_accept` (function, line 1011) `long net_sys_accept(long fd, long sockaddr, long addrlen)`
  - `net_sys_sendto` (function, line 1030) `long net_sys_sendto(long fd, long buf, long len, long flags, long to, long tolen)`
  - `net_sys_recvfrom` (function, line 1039) `long net_sys_recvfrom(long fd, long buf, long len, long flags, long from, long fromlen)`
  - `net_sys_shutdown` (function, line 1049) `long net_sys_shutdown(long fd, long how)`
  - `net_sys_close` (function, line 1056) `long net_sys_close(long fd)`
  - `net_sys_poll` (function, line 1063) `long net_sys_poll(long fds, long nfds, long timeout_ms)`
  - `net_sys_dns` (function, line 1100) `long net_sys_dns(long host)`
  - `net_parse_ip` (function, line 1111) `static int net_parse_ip(const char *text, unsigned char ip[4])`
  - `net_cmd_status` (function, line 1136) `void net_cmd_status(void)`
  - `net_get_addrs` (function, line 1153) `void net_get_addrs(unsigned char mac_out[NET_ETH_ALEN], unsigned char ip_out[4])`
  - `net_cmd_ping` (function, line 1159) `void net_cmd_ping(const char *ip_text)`
  - `net_cmd_dns` (function, line 1170) `void net_cmd_dns(const char *host)`
  - `net_register_symbols` (function, line 1183) `void net_register_symbols(void)`
  - `net_init` (function, line 1191) `void net_init(void)`
  - `NET_TCP_CLOSED` (macro, line 374) `#define NET_TCP_CLOSED`
  - `NET_TCP_SYN_SENT` (macro, line 375) `#define NET_TCP_SYN_SENT`
  - `NET_TCP_ESTABLISHED` (macro, line 376) `#define NET_TCP_ESTABLISHED`
  - `NET_TCP_FIN_SENT` (macro, line 377) `#define NET_TCP_FIN_SENT`
  - `NET_TCP_DEAD` (macro, line 378) `#define NET_TCP_DEAD`
  - `NET_TCP_LISTEN` (macro, line 379) `#define NET_TCP_LISTEN`
  - `NET_TCP_SYN_RCVD` (macro, line 380) `#define NET_TCP_SYN_RCVD`
- Depends on: `headers/kernel.h`, `headers/net.h`, `headers/net/rtl8139.h`, `headers/tls.h`

## net/rtl8139.c
- Layer: utility
- Language: c
- Symbols:
  - `outl_port` (function, line 27) `static void outl_port(unsigned short port, unsigned int val)`
  - `inl_port` (function, line 31) `static unsigned int inl_port(unsigned short port)`
  - `rtl_reg8` (function, line 37) `static unsigned char rtl_reg8(unsigned short off)`
  - `rtl_reg8_w` (function, line 38) `static void rtl_reg8_w(unsigned short off, unsigned char v)`
  - `rtl_reg16` (function, line 39) `static unsigned short rtl_reg16(unsigned short off)`
  - `rtl_reg16_w` (function, line 40) `static void rtl_reg16_w(unsigned short off, unsigned short v)`
  - `rtl_reg32` (function, line 41) `static unsigned int rtl_reg32(unsigned short off)`
  - `rtl_reg32_w` (function, line 42) `static void rtl_reg32_w(unsigned short off, unsigned int v)`
  - `rtl_find` (function, line 56) `static unsigned short rtl_find(void)`
  - `rtl_rdtsc` (function, line 77) `static unsigned long rtl_rdtsc(void)`
  - `net_time_init` (function, line 83) `static void net_time_init(void)`
  - `net_time_ms` (function, line 97) `unsigned long net_time_ms(void)`
  - `rtl_present` (function, line 113) `int rtl_present(void)`
  - `rtl_reset` (function, line 117) `static void rtl_reset(void)`
  - `rtl_init` (function, line 126) `void rtl_init(void)`
  - `rtl_send` (function, line 157) `int rtl_send(const unsigned char *frame, unsigned len)`
  - `rtl_get_mac` (function, line 185) `void rtl_get_mac(unsigned char out[NET_ETH_ALEN])`
  - `rtl_iobase` (function, line 190) `unsigned short rtl_iobase(void)`
  - `rtl_counters` (function, line 194) `void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames)`
  - `rtl_rx_frame_wrapped` (function, line 201) `static void rtl_rx_frame_wrapped(unsigned length)`
  - `rtl_poll` (function, line 212) `void rtl_poll(void)`
  - `RTL_REG_CR` (macro, line 44) `#define RTL_REG_CR`
  - `RTL_REG_TSD0` (macro, line 45) `#define RTL_REG_TSD0`
  - `RTL_REG_TSAD0` (macro, line 46) `#define RTL_REG_TSAD0`
  - `RTL_REG_RBSTART` (macro, line 47) `#define RTL_REG_RBSTART`
  - `RTL_REG_CAPR` (macro, line 48) `#define RTL_REG_CAPR`
  - `RTL_REG_CBR` (macro, line 49) `#define RTL_REG_CBR`
  - `RTL_REG_9346CR` (macro, line 50) `#define RTL_REG_9346CR`
  - `RTL_REG_CONFIG1` (macro, line 51) `#define RTL_REG_CONFIG1`
- Depends on: `headers/drivers/pci.h`, `headers/kernel.h`, `headers/net.h`, `headers/net/rtl8139.h`

## net/tls.c
- Layer: utility
- Doc: tls.c - TLS 1.2 client sessions for MiniOS.
- Language: c
- Symbols:
  - `tls_fail` (function, line 25) `static void tls_fail(struct tls_session *s, const char *stage, const char *reason)`
  - `tls_fd_of` (function, line 33) `static int tls_fd_of(const struct tls_session *s)`
  - `tls_free_fd` (function, line 40) `void tls_free_fd(int fd)`
  - `tls_aad` (function, line 52) `static void tls_aad(unsigned char aad[13], int type, unsigned long long seq,
                    ...`
  - `tls_send_record` (function, line 66) `static int tls_send_record(struct tls_session *s, int type,
                           const unsi...`
  - `tls_send_raw_record` (function, line 95) `static int tls_send_raw_record(struct tls_session *s, int type,
                               co...`
  - `tls_read_record` (function, line 114) `static int tls_read_record(struct tls_session *s, int fd, int deadline_ms)`
  - `exchange` (function, line 173) `* key exchange (ClientHello, ClientKeyExchange) go out in plaintext
 * records, as TLS 1.2 requir...`
  - `build_client_hello` (function, line 190) `static int build_client_hello(struct tls_session *s, unsigned char *out)`
  - `client_finish_flight` (function, line 244) `static int client_finish_flight(struct tls_session *s)`
  - `parse_server_hello` (function, line 340) `static int parse_server_hello(struct tls_session *s,
                              const unsigned...`
  - `parse_certificate` (function, line 370) `static int parse_certificate(struct tls_session *s,
                             const unsigned c...`
  - `parse_server_key_exchange` (function, line 401) `static int parse_server_key_exchange(struct tls_session *s,
                                     ...`
  - `tls_handshake` (function, line 466) `int tls_handshake(int fd, const char *host)`
  - `tls_send` (function, line 687) `int tls_send(int fd, const char *buf, int len)`
  - `tls_recv` (function, line 696) `int tls_recv(int fd, char *buf, int len)`
  - `tls_sys_handshake` (function, line 772) `long tls_sys_handshake(long fd, long host)`
  - `tls_sys_send` (function, line 777) `long tls_sys_send(long fd, long buf, long len)`
  - `tls_sys_recv` (function, line 782) `long tls_sys_recv(long fd, long buf, long len)`
  - `tls_rdtsc` (function, line 789) `static inline unsigned long long tls_rdtsc(void)`
  - `tls_random` (function, line 795) `void tls_random(unsigned char *out, unsigned len)`
  - `outb` (function, line 810) `static inline void outb(unsigned short port, unsigned char v)`
  - `inb` (function, line 813) `static inline unsigned char inb(unsigned short port)`
  - `cmos_read` (function, line 821) `static inline unsigned char cmos_read(unsigned char reg)`
  - `tls_now_days` (function, line 826) `long tls_now_days(void)`
  - `number` (function, line 64) `* The nonce_explicit is the sequence number (RFC 5288 allows it and * OpenSSL uses it);`
  - `PORT_IO_DEFINED` (macro, line 809) `#define PORT_IO_DEFINED`
- Depends on: `headers/tls.h`, `headers/tls_port.h`, `headers/tls_roots.h`

## net/tls_crypto.c
- Layer: utility
- Doc: tls_crypto.c - the crypto behind the kernel TLS 1.2 client.
- Language: c
- Symbols:
  - `mont_ctx` (struct, line 655)
  - `ec_curve` (struct, line 838)
  - `jpt` (struct, line 859)
  - `gf128` (struct, line 316)
  - `sha256_rotr` (function, line 33) `static unsigned sha256_rotr(unsigned x, unsigned n)`
  - `sha256_init` (function, line 37) `void sha256_init(struct sha256_ctx *c)`
  - `sha256_block` (function, line 50) `static void sha256_block(struct sha256_ctx *c, const unsigned char *p)`
  - `sha256_update` (function, line 80) `void sha256_update(struct sha256_ctx *c, const unsigned char *data, unsigned len)`
  - `sha256_final` (function, line 105) `void sha256_final(struct sha256_ctx *c, unsigned char out[32])`
  - `sha256` (function, line 126) `void sha256(const unsigned char *data, unsigned len, unsigned char out[32])`
  - `hmac_sha256` (function, line 135) `void hmac_sha256(const unsigned char *key, unsigned klen,
                 const unsigned char *d...`
  - `p_hash` (function, line 165) `static void p_hash(const unsigned char *secret, unsigned secret_len,
                   const uns...`
  - `tls_prf` (function, line 188) `void tls_prf(const unsigned char *secret, unsigned secret_len,
             const char *label, co...`
  - `aes_xtime` (function, line 230) `static unsigned aes_xtime(unsigned x)`
  - `aes_key_expand` (function, line 235) `static void aes_key_expand(const unsigned char key[16], unsigned rk[44])`
  - `aes_mixcol` (function, line 253) `static void aes_mixcol(unsigned a0, unsigned a1, unsigned a2, unsigned a3,
                      ...`
  - `aes128_encrypt_block` (function, line 263) `void aes128_encrypt_block(const unsigned char key[16],
                          const unsigned c...`
  - `gf_shift_right` (function, line 321) `static gf128 gf_shift_right(gf128 v)`
  - `gf_mul` (function, line 334) `static gf128 gf_mul(gf128 z, gf128 h)`
  - `gf_put` (function, line 351) `static gf128 gf_put(const unsigned char *p)`
  - `ghash_blocks` (function, line 361) `static gf128 ghash_blocks(gf128 z, gf128 h, const unsigned char *data, unsigned len)`
  - `gcm_tag_core` (function, line 384) `static void gcm_tag_core(const unsigned char key[16],
                         const unsigned cha...`
  - `gcm_ctr_core` (function, line 427) `static void gcm_ctr_core(const unsigned char key[16],
                         const unsigned cha...`
  - `tls_nonce` (function, line 450) `static void tls_nonce(const unsigned char salt[4], unsigned long long seq,
                      ...`
  - `gcm_tag` (function, line 457) `static void gcm_tag(const unsigned char key[16], const unsigned char salt[4],
                   ...`
  - `gcm_ctr` (function, line 467) `static void gcm_ctr(const unsigned char key[16], const unsigned char salt[4],
                   ...`
  - `aes128_gcm_seal` (function, line 475) `int aes128_gcm_seal(const unsigned char key[16],
                    const unsigned char salt[4],...`
  - `aes128_gcm_open` (function, line 487) `int aes128_gcm_open(const unsigned char key[16],
                    const unsigned char salt[4],...`
  - `aes128_gcm_seal_core` (function, line 505) `int aes128_gcm_seal_core(const unsigned char key[16],
                         const unsigned cha...`
  - `aes128_gcm_open_core` (function, line 516) `int aes128_gcm_open_core(const unsigned char key[16],
                         const unsigned cha...`
  - `bn_zero` (function, line 537) `static void bn_zero(unsigned *a, int nw)`
  - `bn_is_zero` (function, line 542) `static int bn_is_zero(const unsigned *a, int nw)`
  - `bn_cmp` (function, line 549) `static int bn_cmp(const unsigned *a, const unsigned *b, int nw)`
  - `bn_add` (function, line 559) `static unsigned bn_add(const unsigned *a, const unsigned *b, unsigned *r, int nw)`
  - `bn_sub` (function, line 571) `static unsigned bn_sub(const unsigned *a, const unsigned *b, unsigned *r, int nw)`
  - `bn_dbl_mod` (function, line 584) `static void bn_dbl_mod(const unsigned *a, const unsigned *n, const unsigned *v,
                 ...`
  - `bn_mont_mul` (function, line 596) `static void bn_mont_mul(const unsigned *a, const unsigned *b, const unsigned *n,
                ...`
  - `bn_mont_n0inv` (function, line 635) `static unsigned bn_mont_n0inv(unsigned n0)`
  - `bn_mont_r2` (function, line 643) `static void bn_mont_r2(const unsigned *n, const unsigned *v, int nw,
                       unsig...`
  - `bn_from_be` (function, line 663) `static void bn_from_be(const unsigned char *bytes, unsigned len,
                       unsigned ...`
  - `bn_to_be` (function, line 671) `static void bn_to_be(const unsigned *a, unsigned char *out, unsigned len)`
  - `mont_init` (function, line 677) `static void mont_init(struct mont_ctx *m, const unsigned char *p_bytes,
                      uns...`
  - `mont_to` (function, line 689) `static void mont_to(struct mont_ctx *m, const unsigned *a, unsigned *r)`
  - `mont_from` (function, line 693) `static void mont_from(struct mont_ctx *m, const unsigned *a, unsigned *r)`
  - `mont_mul` (function, line 700) `static void mont_mul(struct mont_ctx *m, const unsigned *a, const unsigned *b,
                  ...`
  - `mont_sqr` (function, line 705) `static void mont_sqr(struct mont_ctx *m, const unsigned *a, unsigned *r)`
  - `mont_add` (function, line 712) `static void mont_add(struct mont_ctx *m, const unsigned *a, const unsigned *b,
                  ...`
  - `mont_sub` (function, line 721) `static void mont_sub(struct mont_ctx *m, const unsigned *a, const unsigned *b,
                  ...`
  - `mont_inv` (function, line 736) `static void mont_inv(struct mont_ctx *m, const unsigned *a, unsigned *r)`
  - `ec_init` (function, line 848) `static void ec_init(struct ec_curve *c, const unsigned char *p,
                    const unsigne...`
  - `jpt_is_inf` (function, line 865) `static int jpt_is_inf(const struct jpt *p, int nw)`
  - `jpt_set_inf` (function, line 869) `static void jpt_set_inf(struct jpt *p, int nw)`
  - `jpt_copy` (function, line 875) `static void jpt_copy(struct jpt *d, const struct jpt *s, int nw)`
  - `jpt_cswap` (function, line 885) `static void jpt_cswap(struct jpt *a, struct jpt *b, unsigned mask, int nw)`
  - `jpt_dbl` (function, line 896) `static void jpt_dbl(struct ec_curve *c, const struct jpt *p1, struct jpt *p3)`
  - `jpt_add` (function, line 936) `static void jpt_add(struct ec_curve *c, const struct jpt *p1, const struct jpt *p2,
             ...`
  - `jpt_scalar_mult` (function, line 980) `static void jpt_scalar_mult(struct ec_curve *c, const struct jpt *base,
                         ...`
  - `jpt_to_affine` (function, line 1007) `static void jpt_to_affine(struct ec_curve *c, const struct jpt *p,
                          unsi...`
  - `jpt_from_affine` (function, line 1032) `static int jpt_from_affine(struct ec_curve *c, const unsigned char *x_bytes,
                    ...`
  - `ec_curve_by_id` (function, line 1076) `static struct ec_curve *ec_curve_by_id(int curve)`
  - `ec_boot` (function, line 1080) `static void ec_boot(void)`
  - `p256_scalar_mult` (function, line 1088) `int p256_scalar_mult(const unsigned char scalar[32],
                     const unsigned char qx[...`
  - `p384_scalar_mult` (function, line 1101) `int p384_scalar_mult(const unsigned char scalar[48],
                     const unsigned char qx[...`
  - `p256_ecdh` (function, line 1114) `int p256_ecdh(const unsigned char priv[32],
              const unsigned char peer_x[32], const u...`
  - `der_parse_sig` (function, line 1129) `static int der_parse_sig(const unsigned char *sig, unsigned sig_len,
                         con...`
  - `ecdsa_verify` (function, line 1163) `int ecdsa_verify(int curve, const unsigned char pub_x[], const unsigned char pub_y[],
           ...`
  - `rsa_verify_digestinfo` (function, line 1261) `static int rsa_verify_digestinfo(const unsigned char *em, unsigned em_len,
                      ...`
  - `rsa_pkcs1_verify_raw` (function, line 1285) `static int rsa_pkcs1_verify_raw(const unsigned char *n, unsigned n_len,
                         ...`
  - `rsa_pkcs1_verify_sha256` (function, line 1326) `int rsa_pkcs1_verify_sha256(const unsigned char *n, unsigned n_len,
                            c...`
  - `rsa_pkcs1_verify_sha384` (function, line 1340) `int rsa_pkcs1_verify_sha384(const unsigned char *n, unsigned n_len,
                            c...`
  - `sha384_rotr` (function, line 1386) `static unsigned long long sha384_rotr(unsigned long long x, unsigned n)`
  - `sha384_raw` (function, line 1390) `static void sha384_raw(const unsigned char *data, unsigned len,
                       unsigned c...`
  - `sha384` (function, line 1506) `void sha384(const unsigned char *data, unsigned len, unsigned char out[48])`
  - `p256_point_valid` (function, line 1512) `int p256_point_valid(const unsigned char x[32], const unsigned char y[32])`
  - `p256_pub` (function, line 1520) `int p256_pub(const unsigned char priv[32],
             unsigned char x[32], unsigned char y[32])`
  - `p256_scalar_valid` (function, line 1539) `int p256_scalar_valid(const unsigned char scalar[32])`
  - `word` (function, line 326) `* of the low word (hi holds bits 64..127, lo bits 0..63). Masked in, * so the shift never branches on key bits. */ r.hi = (v.hi >> 1) ^ (0xE100000000000000ULL & mask);`
  - `TLS_BN_WORDS` (macro, line 535) `#define TLS_BN_WORDS`
- Depends on: `headers/tls.h`, `headers/tls_port.h`

## net/tls_x509.c
- Layer: utility
- Doc: tls_x509.c - minimal X.509 DER parsing and chain verification.
- Language: c
- Symbols:
  - `der_tlv` (struct, line 43)
  - `x509_name` (struct, line 129)
  - `x509_sans` (struct, line 172)
  - `x509_cert` (struct, line 265)
  - `oid_eq` (function, line 36) `static int oid_eq(const unsigned char *bytes, unsigned len,
                  const unsigned char...`
  - `der_next` (function, line 51) `static int der_next(const unsigned char *p, unsigned limit, unsigned *pos,
                    st...`
  - `der_container` (function, line 82) `static int der_container(const unsigned char *p, unsigned limit, unsigned *pos,
                 ...`
  - `days_from_civil` (function, line 94) `static long days_from_civil(int y, int m, int d)`
  - `der_time_to_days` (function, line 106) `static long der_time_to_days(const struct der_tlv *t)`
  - `name_find_cn` (function, line 135) `static int name_find_cn(const unsigned char *p, unsigned limit,
                        struct x5...`
  - `san_add` (function, line 178) `static void san_add(struct x509_sans *out, const unsigned char *v, unsigned len)`
  - `san_parse` (function, line 186) `static void san_parse(const unsigned char *p, unsigned limit,
                      struct x509_s...`
  - `spki_parse` (function, line 203) `static int spki_parse(const unsigned char *p, unsigned limit,
                      struct tls_pu...`
  - `cert_parse` (function, line 279) `static int cert_parse(const unsigned char *der, unsigned len,
                      struct x509_c...`
  - `ascii_lower` (function, line 392) `static int ascii_lower(int c)`
  - `host_match_exact` (function, line 397) `static int host_match_exact(const char *host, const unsigned char *name,
                        ...`
  - `host_match_wildcard` (function, line 410) `static int host_match_wildcard(const char *host, const unsigned char *name,
                     ...`
  - `host_matches` (function, line 431) `static int host_matches(const char *host, const struct x509_cert *leaf)`
  - `tls_x509_parse_pubkey` (function, line 452) `int tls_x509_parse_pubkey(const unsigned char *der, unsigned len,
                          struc...`
  - `pubkey_equal` (function, line 468) `static int pubkey_equal(const struct tls_pubkey *a, const struct tls_pubkey *b)`
  - `cert_verify_signature` (function, line 479) `static int cert_verify_signature(const struct x509_cert *cert,
                                 c...`
  - `tls_x509_verify_chain` (function, line 521) `int tls_x509_verify_chain(const unsigned char *chain, unsigned chain_len,
                       ...`
  - `TLS_SAN_MAX` (macro, line 170) `#define TLS_SAN_MAX`
- Depends on: `headers/tls.h`, `headers/tls_port.h`
