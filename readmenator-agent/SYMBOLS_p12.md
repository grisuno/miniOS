# Symbols (page 12 of 28)
Previous: [SYMBOLS_p11.md](SYMBOLS_p11.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `rtl_find` | function | `net/rtl8139.c:58` | `static unsigned short rtl_find(void)` |
| `rtl_get_mac` | function | `net/rtl8139.c:205` | `void rtl_get_mac(unsigned char out[NET_ETH_ALEN])` |
| `rtl_init` | function | `net/rtl8139.c:120` | `void rtl_init(void)` |
| `rtl_iobase` | function | `net/rtl8139.c:210` | `unsigned short rtl_iobase(void)` |
| `rtl_poll` | function | `net/rtl8139.c:238` | `void rtl_poll(void)` |
| `rtl_present` | function | `net/rtl8139.c:107` | `int rtl_present(void)` |
| `rtl_reg16` | function | `net/rtl8139.c:41` | `static unsigned short rtl_reg16(unsigned short off)` |
| `rtl_reg16_w` | function | `net/rtl8139.c:42` | `static void rtl_reg16_w(unsigned short off, unsigned short v)` |
| `rtl_reg32` | function | `net/rtl8139.c:43` | `static unsigned int rtl_reg32(unsigned short off)` |
| `rtl_reg32_w` | function | `net/rtl8139.c:44` | `static void rtl_reg32_w(unsigned short off, unsigned int v)` |
| `rtl_reg8` | function | `net/rtl8139.c:39` | `static unsigned char rtl_reg8(unsigned short off)` |
| `rtl_reg8_w` | function | `net/rtl8139.c:40` | `static void rtl_reg8_w(unsigned short off, unsigned char v)` |
| `rtl_reset` | function | `net/rtl8139.c:111` | `static void rtl_reset(void)` |
| `rtl_send` | function | `net/rtl8139.c:177` | `int rtl_send(const unsigned char *frame, unsigned len)` |
| `rtl_tx_wait` | function | `net/rtl8139.c:168` | `static int rtl_tx_wait(unsigned slot, unsigned long deadline)` |
| `PORT_IO_DEFINED` | macro | `net/tls.c:809` | `#define PORT_IO_DEFINED` |
| `build_client_hello` | function | `net/tls.c:190` | `static int build_client_hello(struct tls_session *s, unsigned char *out)` |
| `client_finish_flight` | function | `net/tls.c:244` | `static int client_finish_flight(struct tls_session *s)` |
| `cmos_read` | function | `net/tls.c:821` | `static inline unsigned char cmos_read(unsigned char reg)` |
| `exchange` | function | `net/tls.c:173` | `* key exchange (ClientHello, ClientKeyExchange) go out in plaintext  * records, as TLS 1.2 requir...` |
| `inb` | function | `net/tls.c:813` | `static inline unsigned char inb(unsigned short port)` |
| `number` | function | `net/tls.c:64` | `* The nonce_explicit is the sequence number (RFC 5288 allows it and * OpenSSL uses it);` |
| `outb` | function | `net/tls.c:810` | `static inline void outb(unsigned short port, unsigned char v)` |
| `parse_certificate` | function | `net/tls.c:370` | `static int parse_certificate(struct tls_session *s,                              const unsigned c...` |
| `parse_server_hello` | function | `net/tls.c:340` | `static int parse_server_hello(struct tls_session *s,                               const unsigned...` |
| `parse_server_key_exchange` | function | `net/tls.c:401` | `static int parse_server_key_exchange(struct tls_session *s,                                      ...` |
| `tls_aad` | function | `net/tls.c:52` | `static void tls_aad(unsigned char aad[13], int type, unsigned long long seq,                     ...` |
| `tls_fail` | function | `net/tls.c:25` | `static void tls_fail(struct tls_session *s, const char *stage, const char *reason)` |
| `tls_fd_of` | function | `net/tls.c:33` | `static int tls_fd_of(const struct tls_session *s)` |
| `tls_free_fd` | function | `net/tls.c:40` | `void tls_free_fd(int fd)` |
| `tls_handshake` | function | `net/tls.c:466` | `int tls_handshake(int fd, const char *host)` |
| `tls_now_days` | function | `net/tls.c:826` | `long tls_now_days(void)` |
| `tls_random` | function | `net/tls.c:795` | `void tls_random(unsigned char *out, unsigned len)` |
| `tls_rdtsc` | function | `net/tls.c:789` | `static inline unsigned long long tls_rdtsc(void)` |
| `tls_read_record` | function | `net/tls.c:114` | `static int tls_read_record(struct tls_session *s, int fd, int deadline_ms)` |
| `tls_recv` | function | `net/tls.c:696` | `int tls_recv(int fd, char *buf, int len)` |
| `tls_send` | function | `net/tls.c:687` | `int tls_send(int fd, const char *buf, int len)` |
| `tls_send_raw_record` | function | `net/tls.c:95` | `static int tls_send_raw_record(struct tls_session *s, int type,                                co...` |
| `tls_send_record` | function | `net/tls.c:66` | `static int tls_send_record(struct tls_session *s, int type,                            const unsi...` |
| `tls_sys_handshake` | function | `net/tls.c:772` | `long tls_sys_handshake(long fd, long host)` |
| `tls_sys_recv` | function | `net/tls.c:782` | `long tls_sys_recv(long fd, long buf, long len)` |
| `tls_sys_send` | function | `net/tls.c:777` | `long tls_sys_send(long fd, long buf, long len)` |
| `TLS_BN_WORDS` | macro | `net/tls_crypto.c:535` | `#define TLS_BN_WORDS` |
| `aes128_encrypt_block` | function | `net/tls_crypto.c:263` | `void aes128_encrypt_block(const unsigned char key[16],                           const unsigned c...` |
| `aes128_gcm_open` | function | `net/tls_crypto.c:487` | `int aes128_gcm_open(const unsigned char key[16],                     const unsigned char salt[4],...` |
| `aes128_gcm_open_core` | function | `net/tls_crypto.c:516` | `int aes128_gcm_open_core(const unsigned char key[16],                          const unsigned cha...` |
| `aes128_gcm_seal` | function | `net/tls_crypto.c:475` | `int aes128_gcm_seal(const unsigned char key[16],                     const unsigned char salt[4],...` |
| `aes128_gcm_seal_core` | function | `net/tls_crypto.c:505` | `int aes128_gcm_seal_core(const unsigned char key[16],                          const unsigned cha...` |
| `aes_key_expand` | function | `net/tls_crypto.c:235` | `static void aes_key_expand(const unsigned char key[16], unsigned rk[44])` |
| `aes_mixcol` | function | `net/tls_crypto.c:253` | `static void aes_mixcol(unsigned a0, unsigned a1, unsigned a2, unsigned a3,                       ...` |
| `aes_xtime` | function | `net/tls_crypto.c:230` | `static unsigned aes_xtime(unsigned x)` |
| `bn_add` | function | `net/tls_crypto.c:559` | `static unsigned bn_add(const unsigned *a, const unsigned *b, unsigned *r, int nw)` |
| `bn_cmp` | function | `net/tls_crypto.c:549` | `static int bn_cmp(const unsigned *a, const unsigned *b, int nw)` |
| `bn_dbl_mod` | function | `net/tls_crypto.c:584` | `static void bn_dbl_mod(const unsigned *a, const unsigned *n, const unsigned *v,                  ...` |
| `bn_from_be` | function | `net/tls_crypto.c:663` | `static void bn_from_be(const unsigned char *bytes, unsigned len,                        unsigned ...` |
| `bn_is_zero` | function | `net/tls_crypto.c:542` | `static int bn_is_zero(const unsigned *a, int nw)` |
| `bn_mont_mul` | function | `net/tls_crypto.c:596` | `static void bn_mont_mul(const unsigned *a, const unsigned *b, const unsigned *n,                 ...` |
| `bn_mont_n0inv` | function | `net/tls_crypto.c:635` | `static unsigned bn_mont_n0inv(unsigned n0)` |
| `bn_mont_r2` | function | `net/tls_crypto.c:643` | `static void bn_mont_r2(const unsigned *n, const unsigned *v, int nw,                        unsig...` |
| `bn_sub` | function | `net/tls_crypto.c:571` | `static unsigned bn_sub(const unsigned *a, const unsigned *b, unsigned *r, int nw)` |
| `bn_to_be` | function | `net/tls_crypto.c:671` | `static void bn_to_be(const unsigned *a, unsigned char *out, unsigned len)` |
| `bn_zero` | function | `net/tls_crypto.c:537` | `static void bn_zero(unsigned *a, int nw)` |
| `der_parse_sig` | function | `net/tls_crypto.c:1129` | `static int der_parse_sig(const unsigned char *sig, unsigned sig_len,                          con...` |
| `ec_boot` | function | `net/tls_crypto.c:1080` | `static void ec_boot(void)` |
| `ec_curve` | struct | `net/tls_crypto.c:838` | `` |
| `ec_curve_by_id` | function | `net/tls_crypto.c:1076` | `static struct ec_curve *ec_curve_by_id(int curve)` |
| `ec_init` | function | `net/tls_crypto.c:848` | `static void ec_init(struct ec_curve *c, const unsigned char *p,                     const unsigne...` |
| `ecdsa_verify` | function | `net/tls_crypto.c:1163` | `int ecdsa_verify(int curve, const unsigned char pub_x[], const unsigned char pub_y[],            ...` |
| `gcm_ctr` | function | `net/tls_crypto.c:467` | `static void gcm_ctr(const unsigned char key[16], const unsigned char salt[4],                    ...` |
| `gcm_ctr_core` | function | `net/tls_crypto.c:427` | `static void gcm_ctr_core(const unsigned char key[16],                          const unsigned cha...` |
| `gcm_tag` | function | `net/tls_crypto.c:457` | `static void gcm_tag(const unsigned char key[16], const unsigned char salt[4],                    ...` |
| `gcm_tag_core` | function | `net/tls_crypto.c:384` | `static void gcm_tag_core(const unsigned char key[16],                          const unsigned cha...` |
| `gf128` | struct | `net/tls_crypto.c:316` | `` |
| `gf_mul` | function | `net/tls_crypto.c:334` | `static gf128 gf_mul(gf128 z, gf128 h)` |
| `gf_put` | function | `net/tls_crypto.c:351` | `static gf128 gf_put(const unsigned char *p)` |
| `gf_shift_right` | function | `net/tls_crypto.c:321` | `static gf128 gf_shift_right(gf128 v)` |
| `ghash_blocks` | function | `net/tls_crypto.c:361` | `static gf128 ghash_blocks(gf128 z, gf128 h, const unsigned char *data, unsigned len)` |
| `hmac_sha256` | function | `net/tls_crypto.c:135` | `void hmac_sha256(const unsigned char *key, unsigned klen,                  const unsigned char *d...` |
| `jpt` | struct | `net/tls_crypto.c:859` | `` |
| `jpt_add` | function | `net/tls_crypto.c:936` | `static void jpt_add(struct ec_curve *c, const struct jpt *p1, const struct jpt *p2,              ...` |
| `jpt_copy` | function | `net/tls_crypto.c:875` | `static void jpt_copy(struct jpt *d, const struct jpt *s, int nw)` |
| `jpt_cswap` | function | `net/tls_crypto.c:885` | `static void jpt_cswap(struct jpt *a, struct jpt *b, unsigned mask, int nw)` |
| `jpt_dbl` | function | `net/tls_crypto.c:896` | `static void jpt_dbl(struct ec_curve *c, const struct jpt *p1, struct jpt *p3)` |
| `jpt_from_affine` | function | `net/tls_crypto.c:1032` | `static int jpt_from_affine(struct ec_curve *c, const unsigned char *x_bytes,                     ...` |
| `jpt_is_inf` | function | `net/tls_crypto.c:865` | `static int jpt_is_inf(const struct jpt *p, int nw)` |
| `jpt_scalar_mult` | function | `net/tls_crypto.c:980` | `static void jpt_scalar_mult(struct ec_curve *c, const struct jpt *base,                          ...` |
| `jpt_set_inf` | function | `net/tls_crypto.c:869` | `static void jpt_set_inf(struct jpt *p, int nw)` |
| `jpt_to_affine` | function | `net/tls_crypto.c:1007` | `static void jpt_to_affine(struct ec_curve *c, const struct jpt *p,                           unsi...` |
| `mont_add` | function | `net/tls_crypto.c:712` | `static void mont_add(struct mont_ctx *m, const unsigned *a, const unsigned *b,                   ...` |
| `mont_ctx` | struct | `net/tls_crypto.c:655` | `` |
| `mont_from` | function | `net/tls_crypto.c:693` | `static void mont_from(struct mont_ctx *m, const unsigned *a, unsigned *r)` |
| `mont_init` | function | `net/tls_crypto.c:677` | `static void mont_init(struct mont_ctx *m, const unsigned char *p_bytes,                       uns...` |
| `mont_inv` | function | `net/tls_crypto.c:736` | `static void mont_inv(struct mont_ctx *m, const unsigned *a, unsigned *r)` |
| `mont_mul` | function | `net/tls_crypto.c:700` | `static void mont_mul(struct mont_ctx *m, const unsigned *a, const unsigned *b,                   ...` |
| `mont_sqr` | function | `net/tls_crypto.c:705` | `static void mont_sqr(struct mont_ctx *m, const unsigned *a, unsigned *r)` |
| `mont_sub` | function | `net/tls_crypto.c:721` | `static void mont_sub(struct mont_ctx *m, const unsigned *a, const unsigned *b,                   ...` |
| `mont_to` | function | `net/tls_crypto.c:689` | `static void mont_to(struct mont_ctx *m, const unsigned *a, unsigned *r)` |
| `p256_ecdh` | function | `net/tls_crypto.c:1114` | `int p256_ecdh(const unsigned char priv[32],               const unsigned char peer_x[32], const u...` |
| `p256_point_valid` | function | `net/tls_crypto.c:1512` | `int p256_point_valid(const unsigned char x[32], const unsigned char y[32])` |
| `p256_pub` | function | `net/tls_crypto.c:1520` | `int p256_pub(const unsigned char priv[32],              unsigned char x[32], unsigned char y[32])` |
| `p256_scalar_mult` | function | `net/tls_crypto.c:1088` | `int p256_scalar_mult(const unsigned char scalar[32],                      const unsigned char qx[...` |
| `p256_scalar_valid` | function | `net/tls_crypto.c:1539` | `int p256_scalar_valid(const unsigned char scalar[32])` |
| `p384_scalar_mult` | function | `net/tls_crypto.c:1101` | `int p384_scalar_mult(const unsigned char scalar[48],                      const unsigned char qx[...` |
| `p_hash` | function | `net/tls_crypto.c:165` | `static void p_hash(const unsigned char *secret, unsigned secret_len,                    const uns...` |
| `rsa_pkcs1_verify_raw` | function | `net/tls_crypto.c:1285` | `static int rsa_pkcs1_verify_raw(const unsigned char *n, unsigned n_len,                          ...` |
| `rsa_pkcs1_verify_sha256` | function | `net/tls_crypto.c:1326` | `int rsa_pkcs1_verify_sha256(const unsigned char *n, unsigned n_len,                             c...` |
| `rsa_pkcs1_verify_sha384` | function | `net/tls_crypto.c:1340` | `int rsa_pkcs1_verify_sha384(const unsigned char *n, unsigned n_len,                             c...` |
| `rsa_verify_digestinfo` | function | `net/tls_crypto.c:1261` | `static int rsa_verify_digestinfo(const unsigned char *em, unsigned em_len,                       ...` |
| `sha256` | function | `net/tls_crypto.c:126` | `void sha256(const unsigned char *data, unsigned len, unsigned char out[32])` |
| `sha256_block` | function | `net/tls_crypto.c:50` | `static void sha256_block(struct sha256_ctx *c, const unsigned char *p)` |
| `sha256_final` | function | `net/tls_crypto.c:105` | `void sha256_final(struct sha256_ctx *c, unsigned char out[32])` |
| `sha256_init` | function | `net/tls_crypto.c:37` | `void sha256_init(struct sha256_ctx *c)` |
| `sha256_rotr` | function | `net/tls_crypto.c:33` | `static unsigned sha256_rotr(unsigned x, unsigned n)` |
| `sha256_update` | function | `net/tls_crypto.c:80` | `void sha256_update(struct sha256_ctx *c, const unsigned char *data, unsigned len)` |
| `sha384` | function | `net/tls_crypto.c:1506` | `void sha384(const unsigned char *data, unsigned len, unsigned char out[48])` |
| `sha384_raw` | function | `net/tls_crypto.c:1390` | `static void sha384_raw(const unsigned char *data, unsigned len,                        unsigned c...` |
| `sha384_rotr` | function | `net/tls_crypto.c:1386` | `static unsigned long long sha384_rotr(unsigned long long x, unsigned n)` |
| `tls_nonce` | function | `net/tls_crypto.c:450` | `static void tls_nonce(const unsigned char salt[4], unsigned long long seq,                       ...` |
| `tls_prf` | function | `net/tls_crypto.c:188` | `void tls_prf(const unsigned char *secret, unsigned secret_len,              const char *label, co...` |
| `word` | function | `net/tls_crypto.c:326` | `* of the low word (hi holds bits 64..127, lo bits 0..63). Masked in, * so the shift never branches on key bits. */...` |
| `TLS_SAN_MAX` | macro | `net/tls_x509.c:170` | `#define TLS_SAN_MAX` |
| `ascii_lower` | function | `net/tls_x509.c:392` | `static int ascii_lower(int c)` |
| `cert_parse` | function | `net/tls_x509.c:279` | `static int cert_parse(const unsigned char *der, unsigned len,                       struct x509_c...` |
| `cert_verify_signature` | function | `net/tls_x509.c:479` | `static int cert_verify_signature(const struct x509_cert *cert,                                  c...` |
| `days_from_civil` | function | `net/tls_x509.c:94` | `static long days_from_civil(int y, int m, int d)` |
| `der_container` | function | `net/tls_x509.c:82` | `static int der_container(const unsigned char *p, unsigned limit, unsigned *pos,                  ...` |
| `der_next` | function | `net/tls_x509.c:51` | `static int der_next(const unsigned char *p, unsigned limit, unsigned *pos,                     st...` |
| `der_time_to_days` | function | `net/tls_x509.c:106` | `static long der_time_to_days(const struct der_tlv *t)` |
| `der_tlv` | struct | `net/tls_x509.c:43` | `` |
| `host_match_exact` | function | `net/tls_x509.c:397` | `static int host_match_exact(const char *host, const unsigned char *name,                         ...` |
| `host_match_wildcard` | function | `net/tls_x509.c:410` | `static int host_match_wildcard(const char *host, const unsigned char *name,                      ...` |
| `host_matches` | function | `net/tls_x509.c:431` | `static int host_matches(const char *host, const struct x509_cert *leaf)` |
| `name_find_cn` | function | `net/tls_x509.c:135` | `static int name_find_cn(const unsigned char *p, unsigned limit,                         struct x5...` |
| `oid_eq` | function | `net/tls_x509.c:36` | `static int oid_eq(const unsigned char *bytes, unsigned len,                   const unsigned char...` |
| `pubkey_equal` | function | `net/tls_x509.c:468` | `static int pubkey_equal(const struct tls_pubkey *a, const struct tls_pubkey *b)` |
| `san_add` | function | `net/tls_x509.c:178` | `static void san_add(struct x509_sans *out, const unsigned char *v, unsigned len)` |
| `san_parse` | function | `net/tls_x509.c:186` | `static void san_parse(const unsigned char *p, unsigned limit,                       struct x509_s...` |
| `spki_parse` | function | `net/tls_x509.c:203` | `static int spki_parse(const unsigned char *p, unsigned limit,                       struct tls_pu...` |
| `tls_x509_parse_pubkey` | function | `net/tls_x509.c:452` | `int tls_x509_parse_pubkey(const unsigned char *der, unsigned len,                           struc...` |
| `tls_x509_verify_chain` | function | `net/tls_x509.c:521` | `int tls_x509_verify_chain(const unsigned char *chain, unsigned chain_len,                        ...` |
| `x509_cert` | struct | `net/tls_x509.c:265` | `` |
| `x509_name` | struct | `net/tls_x509.c:129` | `` |
| `x509_sans` | struct | `net/tls_x509.c:172` | `` |
| `__sl_3` | function | `progs/asm/aes.s:3087` | `` |
| `__sl_4` | function | `progs/asm/aes.s:3091` | `` |
| `_start` | function | `progs/asm/aes.s:4113` | `` |
| `aes_add_round_key` | function | `progs/asm/aes.s:1646` | `` |
| `aes_cipher` | function | `progs/asm/aes.s:2466` | `` |
| `aes_ctr_crypt` | function | `progs/asm/aes.s:2648` | `` |
| `aes_gf_mul` | function | `progs/asm/aes.s:783` | `` |
| `aes_has` | function | `progs/asm/aes.s:345` | `` |
| `aes_hdr_get` | function | `progs/asm/aes.s:2906` | `` |
| `aes_hdr_put` | function | `progs/asm/aes.s:2791` | `` |
| `aes_init_tables` | function | `progs/asm/aes.s:970` | `` |
| `aes_iv` | function | `progs/asm/aes.s:19` | `` |
| `aes_iv_increment` | function | `progs/asm/aes.s:2565` | `` |
| `aes_key_expand` | function | `progs/asm/aes.s:1197` | `` |
| `aes_mix_columns` | function | `progs/asm/aes.s:1993` | `` |
| `aes_parse_hex` | function | `progs/asm/aes.s:620` | `` |
| `aes_rc` | function | `progs/asm/aes.s:11` | `` |
| `aes_read_all` | function | `progs/asm/aes.s:23` | `` |
| `aes_rk` | function | `progs/asm/aes.s:3` | `` |
| `aes_rotl8` | function | `progs/asm/aes.s:933` | `` |
| `aes_run` | function | `progs/asm/aes.s:3077` | `` |
| `aes_sb` | function | `progs/asm/aes.s:7` | `` |
| `aes_shift_rows` | function | `progs/asm/aes.s:1774` | `` |
| `aes_st` | function | `progs/asm/aes.s:15` | `` |
| `aes_sub_bytes` | function | `progs/asm/aes.s:1721` | `` |
| `aes_tool_name` | function | `progs/asm/aes.s:3059` | `` |
| `aes_write_all` | function | `progs/asm/aes.s:238` | `` |
| `aes_xtime` | function | `progs/asm/aes.s:884` | `` |
| `hex_val` | function | `progs/asm/aes.s:498` | `` |
| `main` | function | `progs/asm/aes.s:3807` | `` |
| `_start` | function | `progs/asm/cp.s:322` | `` |
| `main` | function | `progs/asm/cp.s:3` | `` |
| `_start` | function | `progs/asm/cvmfmt.s:245` | `` |
| `fcanary` | function | `progs/asm/cvmfmt.s:7` | `` |
| `fwin` | function | `progs/asm/cvmfmt.s:3` | `` |
| `main` | function | `progs/asm/cvmfmt.s:11` | `` |
| `_start` | function | `progs/asm/fib.s:82` | `` |
| `fib` | function | `progs/asm/fib.s:3` | `` |
| `main` | function | `progs/asm/fib.s:61` | `` |
| `_start` | function | `progs/asm/freedom.s:11761` | `` |
| `append` | function | `progs/asm/freedom.s:338` | `` |
| `atoi` | function | `progs/asm/freedom.s:252` | `` |
| `body_byte` | function | `progs/asm/freedom.s:5961` | `` |
| `ci_eq` | function | `progs/asm/freedom.s:559` | `` |
| `ci_index` | function | `progs/asm/freedom.s:656` | `` |
| `ci_lower` | function | `progs/asm/freedom.s:437` | `` |
| `ci_starts` | function | `progs/asm/freedom.s:486` | `` |
| `classify_tag` | function | `progs/asm/freedom.s:4757` | `` |
| `css_append` | function | `progs/asm/freedom.s:3849` | `` |
| `css_line` | function | `progs/asm/freedom.s:3920` | `` |
| `dom_append` | function | `progs/asm/freedom.s:3978` | `` |
| `dom_nl` | function | `progs/asm/freedom.s:4083` | `` |
| `dom_space` | function | `progs/asm/freedom.s:4049` | `` |
| `f_attr` | function | `progs/asm/freedom.s:136` | `` |
| `f_attr_on` | function | `progs/asm/freedom.s:120` | `` |
| `f_attrlen` | function | `progs/asm/freedom.s:140` | `` |
| `f_bdone` | function | `progs/asm/freedom.s:248` | `` |
| `f_chunked` | function | `progs/asm/freedom.s:60` | `` |
| `f_clen` | function | `progs/asm/freedom.s:52` | `` |
| `f_cls` | function | `progs/asm/freedom.s:160` | `` |
| `f_clslen` | function | `progs/asm/freedom.s:164` | `` |
| `f_cmdash` | function | `progs/asm/freedom.s:84` | `` |
| `f_comment` | function | `progs/asm/freedom.s:80` | `` |
| `f_crem` | function | `progs/asm/freedom.s:244` | `` |
| `f_csize` | function | `progs/asm/freedom.s:240` | `` |
| `f_css` | function | `progs/asm/freedom.s:216` | `` |
| `f_csslen` | function | `progs/asm/freedom.s:220` | `` |
| `f_cstage` | function | `progs/asm/freedom.s:236` | `` |
| `f_depth` | function | `progs/asm/freedom.s:204` | `` |
| `f_dom` | function | `progs/asm/freedom.s:208` | `` |
| `f_domlen` | function | `progs/asm/freedom.s:212` | `` |
| `f_dump_css` | function | `progs/asm/freedom.s:188` | `` |
| `f_dump_dom` | function | `progs/asm/freedom.s:192` | `` |
| `f_ent` | function | `progs/asm/freedom.s:96` | `` |
| `f_entlen` | function | `progs/asm/freedom.s:100` | `` |
| `f_has_clen` | function | `progs/asm/freedom.s:56` | `` |
| `f_hdr` | function | `progs/asm/freedom.s:64` | `` |
| `f_hlen` | function | `progs/asm/freedom.s:68` | `` |
| `f_host` | function | `progs/asm/freedom.s:24` | `` |
| `f_href` | function | `progs/asm/freedom.s:168` | `` |
| `f_hreflen` | function | `progs/asm/freedom.s:172` | `` |
| `f_id` | function | `progs/asm/freedom.s:152` | `` |
| `f_idlen` | function | `progs/asm/freedom.s:156` | `` |
| `f_inval` | function | `progs/asm/freedom.s:128` | `` |
| `f_inval2` | function | `progs/asm/freedom.s:132` | `` |
| `f_linkhost` | function | `progs/asm/freedom.s:224` | `` |
| `f_linkn` | function | `progs/asm/freedom.s:232` | `` |
| `f_linkpath` | function | `progs/asm/freedom.s:228` | `` |
| `f_loc` | function | `progs/asm/freedom.s:40` | `` |
| `f_mode` | function | `progs/asm/freedom.s:196` | `` |
| `f_path` | function | `progs/asm/freedom.s:28` | `` |
| `f_port` | function | `progs/asm/freedom.s:32` | `` |
| `f_rawcap` | function | `progs/asm/freedom.s:200` | `` |
| `f_redir` | function | `progs/asm/freedom.s:44` | `` |
| `f_rel_ss` | function | `progs/asm/freedom.s:176` | `` |
| `f_secure` | function | `progs/asm/freedom.s:36` | `` |
| `f_status` | function | `progs/asm/freedom.s:48` | `` |
| `f_styleattr` | function | `progs/asm/freedom.s:180` | `` |
| `f_stylelen` | function | `progs/asm/freedom.s:184` | `` |
| `f_suppress` | function | `progs/asm/freedom.s:76` | `` |
| `f_tag` | function | `progs/asm/freedom.s:72` | `` |
| `f_tagn` | function | `progs/asm/freedom.s:88` | `` |
| `f_tagnlen` | function | `progs/asm/freedom.s:92` | `` |
| `f_utbuf` | function | `progs/asm/freedom.s:108` | `` |
| `f_utlen` | function | `progs/asm/freedom.s:112` | `` |
| `f_utrem` | function | `progs/asm/freedom.s:116` | `` |
| `f_val` | function | `progs/asm/freedom.s:144` | `` |
| `f_vallen` | function | `progs/asm/freedom.s:148` | `` |
| `f_waitq` | function | `progs/asm/freedom.s:124` | `` |
| `f_ws` | function | `progs/asm/freedom.s:104` | `` |
| `fetch` | function | `progs/asm/freedom.s:7810` | `` |
| `fetch_css` | function | `progs/asm/freedom.s:9293` | `` |
| `has_scheme` | function | `progs/asm/freedom.s:789` | `` |
| `head_line` | function | `progs/asm/freedom.s:7203` | `` |
| `is_void_tag` | function | `progs/asm/freedom.s:4449` | `` |
| `looks_like_url` | function | `progs/asm/freedom.s:715` | `` |
| `main` | function | `progs/asm/freedom.s:10291` | `` |
| `make_search` | function | `progs/asm/freedom.s:1064` | `` |
| `parse_head` | function | `progs/asm/freedom.s:7460` | `` |
| `print_css_dump` | function | `progs/asm/freedom.s:10112` | `` |
| `print_dom_dump` | function | `progs/asm/freedom.s:10212` | `` |
| `put_entity` | function | `progs/asm/freedom.s:3018` | `` |
| `put_text` | function | `progs/asm/freedom.s:2915` | `` |
| `put_utf` | function | `progs/asm/freedom.s:2379` | `` |
| `put_ws` | function | `progs/asm/freedom.s:2333` | `` |
| `record_attr` | function | `progs/asm/freedom.s:4117` | `` |
| `recv_body` | function | `progs/asm/freedom.s:7676` | `` |
| `resolve_redirect` | function | `progs/asm/freedom.s:1810` | `` |
| `send_all` | function | `progs/asm/freedom.s:7736` | `` |
| `split_url` | function | `progs/asm/freedom.s:1295` | `` |
| `tls_close` | function | `progs/asm/freedom.s:3` | `` |
| `_start` | function | `progs/asm/http.s:709` | `` |
| `atoi` | function | `progs/asm/http.s:3` | `` |
| `main` | function | `progs/asm/http.s:89` | `` |
| `_start` | function | `progs/asm/json.s:4169` | `` |
| `js_array_at` | function | `progs/asm/json.s:3391` | `` |
| `js_count` | function | `progs/asm/json.s:23` | `` |
| `js_err` | function | `progs/asm/json.s:55` | `` |
| `js_find_member` | function | `progs/asm/json.s:3313` | `` |
| `js_first` | function | `progs/asm/json.s:19` | `` |
| `js_indent` | function | `progs/asm/json.s:2481` | `` |
| `js_key` | function | `progs/asm/json.s:3` | `` |
| `js_key_match` | function | `progs/asm/json.s:947` | `` |
| `js_len` | function | `progs/asm/json.s:51` | `` |
| `js_n` | function | `progs/asm/json.s:31` | `` |
| `js_new` | function | `progs/asm/json.s:274` | `` |
| `js_next` | function | `progs/asm/json.s:27` | `` |
| `js_num` | function | `progs/asm/json.s:15` | `` |
| `js_parse_array` | function | `progs/asm/json.s:1335` | `` |
| `js_parse_number` | function | `progs/asm/json.s:851` | `` |
| `js_parse_object` | function | `progs/asm/json.s:983` | `` |
| `js_parse_string` | function | `progs/asm/json.s:437` | `` |
| `js_parse_value` | function | `progs/asm/json.s:1594` | `` |
| `js_peek` | function | `progs/asm/json.s:397` | `` |
| `js_plen` | function | `progs/asm/json.s:39` | `` |
| `js_pool` | function | `progs/asm/json.s:35` | `` |
| `js_pos` | function | `progs/asm/json.s:47` | `` |
| `js_print_str` | function | `progs/asm/json.s:2524` | `` |
| `js_print_value` | function | `progs/asm/json.s:2747` | `` |
| `js_query` | function | `progs/asm/json.s:3460` | `` |
| `js_read_all` | function | `progs/asm/json.s:59` | `` |
| `js_skip_ws` | function | `progs/asm/json.s:306` | `` |
| `js_src` | function | `progs/asm/json.s:43` | `` |
| `js_str` | function | `progs/asm/json.s:7` | `` |
| `js_type` | function | `progs/asm/json.s:11` | `` |
| `main` | function | `progs/asm/json.s:3772` | `` |
| `_start` | function | `progs/asm/ldhello.s:14` | `` |
| `main` | function | `progs/asm/ldhello.s:3` | `` |
| `_start` | function | `progs/asm/lz4.s:1535` | `` |
| `lz4_compress_file` | function | `progs/asm/lz4.s:478` | `` |
| `lz4_decompress_file` | function | `progs/asm/lz4.s:791` | `` |
| `lz4_has` | function | `progs/asm/lz4.s:3` | `` |
| `lz4_read_all` | function | `progs/asm/lz4.s:156` | `` |
| `lz4_write_all` | function | `progs/asm/lz4.s:371` | `` |
| `main` | function | `progs/asm/lz4.s:1228` | `` |
| `_start` | function | `progs/asm/lzss.s:3497` | `` |
| `lz_buf` | function | `progs/asm/lzss.s:35` | `` |
| `lz_compress` | function | `progs/asm/lzss.s:2257` | `` |
| `lz_decode` | function | `progs/asm/lzss.s:1171` | `` |
| `lz_decompress` | function | `progs/asm/lzss.s:2628` | `` |
| `lz_dst` | function | `progs/asm/lzss.s:19` | `` |
| `lz_dstcap` | function | `progs/asm/lzss.s:23` | `` |
| `lz_dstlen` | function | `progs/asm/lzss.s:27` | `` |
| `lz_encode` | function | `progs/asm/lzss.s:451` | `` |
| `lz_err` | function | `progs/asm/lzss.s:31` | `` |
| `lz_flush_bits` | function | `progs/asm/lzss.s:223` | `` |
| `lz_getbit` | function | `progs/asm/lzss.s:1051` | `` |
| `lz_has` | function | `progs/asm/lzss.s:1782` | `` |
| `lz_hdr_get` | function | `progs/asm/lzss.s:1629` | `` |
| `lz_hdr_put` | function | `progs/asm/lzss.s:1514` | `` |
| `lz_in_getc` | function | `progs/asm/lzss.s:43` | `` |
| `lz_mask` | function | `progs/asm/lzss.s:39` | `` |
| `lz_next_mb` | function | `progs/asm/lzss.s:447` | `` |
| `lz_out_literal` | function | `progs/asm/lzss.s:251` | `` |
| `lz_out_pair` | function | `progs/asm/lzss.s:321` | `` |
| `lz_out_put` | function | `progs/asm/lzss.s:79` | `` |
| `lz_putbit0` | function | `progs/asm/lzss.s:174` | `` |
| `lz_putbit1` | function | `progs/asm/lzss.s:116` | `` |
| `lz_read_all` | function | `progs/asm/lzss.s:1935` | `` |
| `lz_src` | function | `progs/asm/lzss.s:7` | `` |
| `lz_srclen` | function | `progs/asm/lzss.s:11` | `` |
| `lz_srcpos` | function | `progs/asm/lzss.s:15` | `` |
| `lz_win` | function | `progs/asm/lzss.s:3` | `` |
| `lz_write_all` | function | `progs/asm/lzss.s:2150` | `` |
| `main` | function | `progs/asm/lzss.s:3178` | `` |
| `_start` | function | `progs/asm/mtop.s:4781` | `` |
| `disk_f` | function | `progs/asm/mtop.s:39` | `` |
| `disk_path` | function | `progs/asm/mtop.s:43` | `` |
| `emit` | function | `progs/asm/mtop.s:206` | `` |
| `h_cpu` | function | `progs/asm/mtop.s:3` | `` |
| `h_fill` | function | `progs/asm/mtop.s:11` | `` |
| `h_mem` | function | `progs/asm/mtop.s:7` | `` |
| `have_prev` | function | `progs/asm/mtop.s:35` | `` |
| `last_dns` | function | `progs/asm/mtop.s:15` | `` |
| `last_dns_ms` | function | `progs/asm/mtop.s:19` | `` |
| `last_sock` | function | `progs/asm/mtop.s:23` | `` |
| `main` | function | `progs/asm/mtop.s:3831` | `` |
| `mtop_atoi` | function | `progs/asm/mtop.s:443` | `` |
| `mtop_bar` | function | `progs/asm/mtop.s:887` | `` |
| `mtop_clear` | function | `progs/asm/mtop.s:401` | `` |
| `mtop_clear_ansi` | function | `progs/asm/mtop.s:317` | `` |
| `mtop_cpu` | function | `progs/asm/mtop.s:1556` | `` |
| `mtop_disk_open` | function | `progs/asm/mtop.s:1842` | `` |
| `mtop_disk_read` | function | `progs/asm/mtop.s:1966` | `` |
| `mtop_frame` | function | `progs/asm/mtop.s:2275` | `` |
| `mtop_hist_max` | function | `progs/asm/mtop.s:1038` | `` |
| `mtop_hist_push` | function | `progs/asm/mtop.s:1106` | `` |
| `mtop_key` | function | `progs/asm/mtop.s:137` | `` |
| `mtop_mem` | function | `progs/asm/mtop.s:1452` | `` |
| `mtop_minfo` | function | `progs/asm/mtop.s:165` | `` |
| `mtop_net_probe` | function | `progs/asm/mtop.s:2128` | `` |
| `mtop_put2` | function | `progs/asm/mtop.s:725` | `` |
| `mtop_put_kb` | function | `progs/asm/mtop.s:765` | `` |
| `mtop_putu` | function | `progs/asm/mtop.s:569` | `` |
| `mtop_quit_key` | function | `progs/asm/mtop.s:241` | `` |
| `mtop_rtc` | function | `progs/asm/mtop.s:106` | `` |
| `mtop_spark` | function | `progs/asm/mtop.s:1201` | `` |
| `mtop_time` | function | `progs/asm/mtop.s:78` | `` |
| `prev_idle` | function | `progs/asm/mtop.s:31` | `` |
| `prev_total` | function | `progs/asm/mtop.s:27` | `` |
| `sc3` | function | `progs/asm/mtop.s:47` | `` |
| `_start` | function | `progs/asm/sign.s:14926` | `` |
| `fe_add` | function | `progs/asm/sign.s:4837` | `` |
| `fe_cmov` | function | `progs/asm/sign.s:4505` | `` |
| `fe_copy` | function | `progs/asm/sign.s:4387` | `` |
| `fe_curved` | function | `progs/asm/sign.s:6586` | `` |
| `fe_foldadd` | function | `progs/asm/sign.s:5426` | `` |
| `fe_frombytes` | function | `progs/asm/sign.s:6284` | `` |
| `fe_ge` | function | `progs/asm/sign.s:4589` | `` |
| `fe_inv` | function | `progs/asm/sign.s:6135` | `` |
| `fe_mul` | function | `progs/asm/sign.s:5481` | `` |
| `fe_off` | function | `progs/asm/sign.s:6760` | `` |
| `fe_one` | function | `progs/asm/sign.s:4476` | `` |
| `fe_rawsub` | function | `progs/asm/sign.s:4713` | `` |
| `fe_rowadd` | function | `progs/asm/sign.s:5297` | `` |
| `fe_sq` | function | `progs/asm/sign.s:6109` | `` |
| `fe_sub` | function | `progs/asm/sign.s:5031` | `` |
| `fe_tobytes` | function | `progs/asm/sign.s:6432` | `` |
| `fe_zero` | function | `progs/asm/sign.s:4435` | `` |
| `ge_add` | function | `progs/asm/sign.s:6864` | `` |
| `ge_cmov` | function | `progs/asm/sign.s:6780` | `` |
| `ge_copy` | function | `progs/asm/sign.s:6712` | `` |
| `ge_double` | function | `progs/asm/sign.s:7325` | `` |
| `ge_scalarmult` | function | `progs/asm/sign.s:7701` | `` |
| `main` | function | `progs/asm/sign.s:14647` | `` |
| `sc_mod_l` | function | `progs/asm/sign.s:7916` | `` |
| `sc_mul_add` | function | `progs/asm/sign.s:8461` | `` |
| `sign_add3` | function | `progs/asm/sign.s:1218` | `` |
| `sign_append` | function | `progs/asm/sign.s:12154` | `` |
| `sign_ax_hex` | function | `progs/asm/sign.s:47` | `` |
| `sign_ay_hex` | function | `progs/asm/sign.s:51` | `` |
| `sign_be32` | function | `progs/asm/sign.s:1292` | `` |
| `sign_block` | function | `progs/asm/sign.s:1394` | `` |
| `sign_borrow2` | function | `progs/asm/sign.s:1158` | `` |
| `sign_buf` | function | `progs/asm/sign.s:79` | `` |
| `sign_bx_hex` | function | `progs/asm/sign.s:39` | `` |
| `sign_by_hex` | function | `progs/asm/sign.s:43` | `` |
| `sign_byte` | function | `progs/asm/sign.s:325` | `` |
| `sign_carry2` | function | `progs/asm/sign.s:1099` | `` |
| `sign_copy` | function | `progs/asm/sign.s:363` | `` |
| `sign_digest` | function | `progs/asm/sign.s:9485` | `` |
| `sign_digest_of` | function | `progs/asm/sign.s:11374` | `` |
| `sign_feed32` | function | `progs/asm/sign.s:3871` | `` |
| `sign_file` | function | `progs/asm/sign.s:13433` | `` |
| `sign_ga` | function | `progs/asm/sign.s:107` | `` |
| `sign_gb` | function | `progs/asm/sign.s:103` | `` |
| `sign_h` | function | `progs/asm/sign.s:71` | `` |
| `sign_hexout` | function | `progs/asm/sign.s:688` | `` |
| `sign_hexval` | function | `progs/asm/sign.s:111` | `` |
| `sign_k` | function | `progs/asm/sign.s:67` | `` |
| `sign_k0` | function | `progs/asm/sign.s:3` | `` |
| `sign_k1` | function | `progs/asm/sign.s:7` | `` |
| `sign_k2` | function | `progs/asm/sign.s:11` | `` |
| `sign_k3` | function | `progs/asm/sign.s:15` | `` |
| `sign_k4` | function | `progs/asm/sign.s:19` | `` |
| `sign_k5` | function | `progs/asm/sign.s:23` | `` |
| `sign_k6` | function | `progs/asm/sign.s:27` | `` |
| `sign_k7` | function | `progs/asm/sign.s:31` | `` |
| `sign_key_init` | function | `progs/asm/sign.s:3962` | `` |
| `sign_l8` | function | `progs/asm/sign.s:99` | `` |
| `sign_le16` | function | `progs/asm/sign.s:444` | `` |
| `sign_le32` | function | `progs/asm/sign.s:494` | `` |
| `sign_nhi` | function | `progs/asm/sign.s:91` | `` |
| `sign_nlo` | function | `progs/asm/sign.s:87` | `` |
| `sign_note_name` | function | `progs/asm/sign.s:59` | `` |
| `sign_note_span` | function | `progs/asm/sign.s:11061` | `` |
| `sign_offok` | function | `progs/asm/sign.s:866` | `` |
| `sign_patch_notes` | function | `progs/asm/sign.s:11834` | `` |
| `sign_points_init` | function | `progs/asm/sign.s:9084` | `` |
| `sign_pub_hex` | function | `progs/asm/sign.s:55` | `` |
| `sign_put32` | function | `progs/asm/sign.s:596` | `` |
| `sign_q4` | function | `progs/asm/sign.s:95` | `` |
| `sign_read` | function | `progs/asm/sign.s:10733` | `` |
| `sign_rev32` | function | `progs/asm/sign.s:9013` | `` |
| `sign_rotr` | function | `progs/asm/sign.s:927` | `` |
| `sign_section_name` | function | `progs/asm/sign.s:63` | `` |
| `sign_seed_hex` | function | `progs/asm/sign.s:35` | `` |
| `sign_selftest` | function | `progs/asm/sign.s:14501` | `` |
| `sign_sha_final` | function | `progs/asm/sign.s:3477` | `` |
| `sign_sha_init` | function | `progs/asm/sign.s:3105` | `` |
| `sign_sha_update` | function | `progs/asm/sign.s:3287` | `` |
| `sign_strlen` | function | `progs/asm/sign.s:405` | `` |
| `sign_unhex` | function | `progs/asm/sign.s:232` | `` |
| `sign_used` | function | `progs/asm/sign.s:83` | `` |
| `sign_w` | function | `progs/asm/sign.s:75` | `` |
| `sign_write` | function | `progs/asm/sign.s:10972` | `` |
| `_start` | function | `progs/asm/w1.s:37` | `` |
| `main` | function | `progs/asm/w1.s:3` | `` |
| `DMAP_BRUSH_COUNT` | macro | `progs/doomedit/doomedit.c:230` | `#define DMAP_BRUSH_COUNT` |
| `DMAP_CANVAS_W` | macro | `progs/doomedit/doomedit.c:61` | `#define DMAP_CANVAS_W` |
| `DMAP_CEIL_FLAT` | macro | `progs/doomedit/doomedit.c:97` | `#define DMAP_CEIL_FLAT` |
| `DMAP_CEIL_H` | macro | `progs/doomedit/doomedit.c:100` | `#define DMAP_CEIL_H` |
| `DMAP_CELL_PX` | macro | `progs/doomedit/doomedit.c:60` | `#define DMAP_CELL_PX` |
| `DMAP_DARK_LIGHT` | macro | `progs/doomedit/doomedit.c:103` | `#define DMAP_DARK_LIGHT` |
| `DMAP_DARK_MID` | macro | `progs/doomedit/doomedit.c:92` | `#define DMAP_DARK_MID` |
| `DMAP_DEF_H` | macro | `progs/doomedit/doomedit.c:58` | `#define DMAP_DEF_H` |
| `DMAP_DEF_W` | macro | `progs/doomedit/doomedit.c:57` | `#define DMAP_DEF_W` |
| `DMAP_DOOR_CEIL` | macro | `progs/doomedit/doomedit.c:101` | `#define DMAP_DOOR_CEIL` |
| `DMAP_DOOR_LIGHT` | macro | `progs/doomedit/doomedit.c:104` | `#define DMAP_DOOR_LIGHT` |
| `DMAP_DOOR_SPECIAL` | macro | `progs/doomedit/doomedit.c:85` | `#define DMAP_DOOR_SPECIAL` |
| `DMAP_DOOR_UPPER` | macro | `progs/doomedit/doomedit.c:91` | `#define DMAP_DOOR_UPPER` |
| `DMAP_EXIT_MID` | macro | `progs/doomedit/doomedit.c:90` | `#define DMAP_EXIT_MID` |
| `DMAP_EXIT_SPECIAL` | macro | `progs/doomedit/doomedit.c:84` | `#define DMAP_EXIT_SPECIAL` |
| `DMAP_FLAG_BLOCKING` | macro | `progs/doomedit/doomedit.c:86` | `#define DMAP_FLAG_BLOCKING` |
| `DMAP_FLAG_TWOSIDED` | macro | `progs/doomedit/doomedit.c:87` | `#define DMAP_FLAG_TWOSIDED` |
| `DMAP_FLOOR_FLAT` | macro | `progs/doomedit/doomedit.c:95` | `#define DMAP_FLOOR_FLAT` |
| `DMAP_FLOOR_H` | macro | `progs/doomedit/doomedit.c:98` | `#define DMAP_FLOOR_H` |
| `DMAP_FNAME_MAX` | macro | `progs/doomedit/doomedit.c:67` | `#define DMAP_FNAME_MAX` |
| `DMAP_FOV_PLANE` | macro | `progs/doomedit/doomedit.c:78` | `#define DMAP_FOV_PLANE` |
| `DMAP_FRAME_MS` | macro | `progs/doomedit/doomedit.c:75` | `#define DMAP_FRAME_MS` |

Next: [SYMBOLS_p13.md](SYMBOLS_p13.md)
