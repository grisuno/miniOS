# Symbols (page 11 of 26)
Previous: [SYMBOLS_p10.md](SYMBOLS_p10.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
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
| `DMAP_HISTORY` | macro | `progs/doomedit/doomedit.c:111` | `#define DMAP_HISTORY` |
| `DMAP_LEVEL_COUNT` | macro | `progs/doomedit/doomedit.c:70` | `#define DMAP_LEVEL_COUNT` |
| `DMAP_LIGHT` | macro | `progs/doomedit/doomedit.c:102` | `#define DMAP_LIGHT` |
| `DMAP_MAX_H` | macro | `progs/doomedit/doomedit.c:56` | `#define DMAP_MAX_H` |
| `DMAP_MAX_LINES` | macro | `progs/doomedit/doomedit.c:79` | `#define DMAP_MAX_LINES` |
| `DMAP_MAX_SECTORS` | macro | `progs/doomedit/doomedit.c:72` | `#define DMAP_MAX_SECTORS` |
| `DMAP_MAX_THINGS` | macro | `progs/doomedit/doomedit.c:81` | `#define DMAP_MAX_THINGS` |
| `DMAP_MAX_VERTS` | macro | `progs/doomedit/doomedit.c:80` | `#define DMAP_MAX_VERTS` |
| `DMAP_MAX_W` | macro | `progs/doomedit/doomedit.c:55` | `#define DMAP_MAX_W` |
| `DMAP_MOVE_STEP` | macro | `progs/doomedit/doomedit.c:77` | `#define DMAP_MOVE_STEP` |
| `DMAP_NODE_LEAF` | macro | `progs/doomedit/doomedit.c:106` | `#define DMAP_NODE_LEAF` |
| `DMAP_NO_SIDE` | macro | `progs/doomedit/doomedit.c:88` | `#define DMAP_NO_SIDE` |
| `DMAP_NUKE_FLAT` | macro | `progs/doomedit/doomedit.c:96` | `#define DMAP_NUKE_FLAT` |
| `DMAP_NUKE_FLOOR` | macro | `progs/doomedit/doomedit.c:99` | `#define DMAP_NUKE_FLOOR` |
| `DMAP_NUKE_MID` | macro | `progs/doomedit/doomedit.c:93` | `#define DMAP_NUKE_MID` |
| `DMAP_NUKE_SPECIAL` | macro | `progs/doomedit/doomedit.c:105` | `#define DMAP_NUKE_SPECIAL` |
| `DMAP_PANEL_MIN_H` | macro | `progs/doomedit/doomedit.c:62` | `#define DMAP_PANEL_MIN_H` |
| `DMAP_PLAYER_TYPE` | macro | `progs/doomedit/doomedit.c:82` | `#define DMAP_PLAYER_TYPE` |
| `DMAP_PREV_H` | macro | `progs/doomedit/doomedit.c:64` | `#define DMAP_PREV_H` |
| `DMAP_PREV_W` | macro | `progs/doomedit/doomedit.c:63` | `#define DMAP_PREV_W` |
| `DMAP_RANDOM_ATTEMPTS` | macro | `progs/doomedit/doomedit.c:71` | `#define DMAP_RANDOM_ATTEMPTS` |
| `DMAP_ROOM_MAX` | macro | `progs/doomedit/doomedit.c:73` | `#define DMAP_ROOM_MAX` |
| `DMAP_ROOM_TRIES` | macro | `progs/doomedit/doomedit.c:74` | `#define DMAP_ROOM_TRIES` |
| `DMAP_SAVE_TXT` | macro | `progs/doomedit/doomedit.c:108` | `#define DMAP_SAVE_TXT` |
| `DMAP_SAVE_WAD` | macro | `progs/doomedit/doomedit.c:109` | `#define DMAP_SAVE_WAD` |
| `DMAP_SLOTS` | macro | `progs/doomedit/doomedit.c:69` | `#define DMAP_SLOTS` |
| `DMAP_STATUS_MAX` | macro | `progs/doomedit/doomedit.c:68` | `#define DMAP_STATUS_MAX` |
| `DMAP_THING_OPT` | macro | `progs/doomedit/doomedit.c:83` | `#define DMAP_THING_OPT` |
| `DMAP_TILE` | macro | `progs/doomedit/doomedit.c:59` | `#define DMAP_TILE` |
| `DMAP_TITLE` | macro | `progs/doomedit/doomedit.c:110` | `#define DMAP_TITLE` |
| `DMAP_TOOL_DOOM` | macro | `progs/doomedit/doomedit.c:107` | `#define DMAP_TOOL_DOOM` |
| `DMAP_TOOL_FILL` | macro | `progs/doomedit/doomedit.c:115` | `#define DMAP_TOOL_FILL` |
| `DMAP_TOOL_LINE` | macro | `progs/doomedit/doomedit.c:113` | `#define DMAP_TOOL_LINE` |
| `DMAP_TOOL_PAINT` | macro | `progs/doomedit/doomedit.c:112` | `#define DMAP_TOOL_PAINT` |
| `DMAP_TOOL_RECT` | macro | `progs/doomedit/doomedit.c:114` | `#define DMAP_TOOL_RECT` |
| `DMAP_TURN_STEP` | macro | `progs/doomedit/doomedit.c:76` | `#define DMAP_TURN_STEP` |
| `DMAP_UI_MEMORY` | macro | `progs/doomedit/doomedit.c:65` | `#define DMAP_UI_MEMORY` |
| `DMAP_UNUSED_TEX` | macro | `progs/doomedit/doomedit.c:94` | `#define DMAP_UNUSED_TEX` |
| `DMAP_WAD_MAX` | macro | `progs/doomedit/doomedit.c:66` | `#define DMAP_WAD_MAX` |
| `DMAP_WALL_MID` | macro | `progs/doomedit/doomedit.c:89` | `#define DMAP_WALL_MID` |
| `areas` | function | `progs/doomedit/doomedit.c:1150` | `* floor areas (doors stand alone, dark and nukage never merge);` |
| `dmap_apply_cell` | function | `progs/doomedit/doomedit.c:326` | `static void dmap_apply_cell(int r, int c, int brush)` |
| `dmap_brush_combo` | function | `progs/doomedit/doomedit.c:1760` | `static void dmap_brush_combo(struct nk_context *ctx)` |
| `dmap_build_wad` | function | `progs/doomedit/doomedit.c:1343` | `static int dmap_build_wad(int *size_out)` |
| `dmap_canvas` | function | `progs/doomedit/doomedit.c:1773` | `static void dmap_canvas(struct nk_context *ctx)` |
| `dmap_cell_class` | function | `progs/doomedit/doomedit.c:583` | `static int dmap_cell_class(int cell)` |
| `dmap_cell_color` | function | `progs/doomedit/doomedit.c:594` | `static struct nk_color dmap_cell_color(int cell)` |
| `dmap_check_wad` | function | `progs/doomedit/doomedit.c:1675` | `static int dmap_check_wad(const char *path)` |
| `dmap_demo_room` | function | `progs/doomedit/doomedit.c:2110` | `static void dmap_demo_room(void)` |
| `dmap_draw_line` | function | `progs/doomedit/doomedit.c:383` | `static void dmap_draw_line(int r0, int c0, int r1, int c1, int cell)` |
| `dmap_draw_rect` | function | `progs/doomedit/doomedit.c:411` | `static void dmap_draw_rect(int r0, int c0, int r1, int c1, int cell)` |
| `dmap_export_wad` | function | `progs/doomedit/doomedit.c:1660` | `static int dmap_export_wad(const char *path)` |
| `dmap_flood_fill` | function | `progs/doomedit/doomedit.c:344` | `static void dmap_flood_fill(int sr, int sc, int new_cell)` |
| `dmap_free_cell` | function | `progs/doomedit/doomedit.c:857` | `static int dmap_free_cell(int *r, int *c)` |
| `dmap_gui_run` | function | `progs/doomedit/doomedit.c:2056` | `static void dmap_gui_run(void)` |
| `dmap_is_wall` | function | `progs/doomedit/doomedit.c:570` | `static int dmap_is_wall(int row, int col)` |
| `dmap_label_regions` | function | `progs/doomedit/doomedit.c:1163` | `static int dmap_label_regions(void)` |
| `dmap_load` | function | `progs/doomedit/doomedit.c:1077` | `static int dmap_load(const char *path)` |
| `dmap_load_preset` | function | `progs/doomedit/doomedit.c:816` | `static int dmap_load_preset(int idx)` |
| `dmap_new` | function | `progs/doomedit/doomedit.c:639` | `static void dmap_new(void)` |
| `dmap_path_len` | function | `progs/doomedit/doomedit.c:480` | `static int dmap_path_len(void)` |
| `dmap_preview` | function | `progs/doomedit/doomedit.c:1693` | `static void dmap_preview(struct nk_command_buffer *canvas, struct nk_rect area)` |
| `dmap_preview_row` | function | `progs/doomedit/doomedit.c:1863` | `static void dmap_preview_row(struct nk_context *ctx)` |
| `dmap_push_history` | function | `progs/doomedit/doomedit.c:272` | `static void dmap_push_history(void)` |
| `dmap_rand` | function | `progs/doomedit/doomedit.c:849` | `static unsigned dmap_rand(void)` |
| `dmap_random_map` | function | `progs/doomedit/doomedit.c:871` | `static void dmap_random_map(unsigned seed)` |
| `dmap_reach_map` | function | `progs/doomedit/doomedit.c:440` | `static void dmap_reach_map(int seen[DMAP_MAX_H][DMAP_MAX_W])` |
| `dmap_recenter` | function | `progs/doomedit/doomedit.c:804` | `static void dmap_recenter(void)` |
| `dmap_redo` | function | `progs/doomedit/doomedit.c:307` | `static int dmap_redo(void)` |
| `dmap_run_map` | function | `progs/doomedit/doomedit.c:1898` | `static void dmap_run_map(void)` |
| `dmap_save_txt` | function | `progs/doomedit/doomedit.c:1129` | `static int dmap_save_txt(const char *path)` |
| `dmap_scancode` | function | `progs/doomedit/doomedit.c:2037` | `static void dmap_scancode(int code, int make, int e0, void *ud)` |
| `dmap_seg_angle` | function | `progs/doomedit/doomedit.c:1333` | `static int dmap_seg_angle(int dx, int dy)` |
| `dmap_selftest` | function | `progs/doomedit/doomedit.c:2122` | `static int dmap_selftest(void)` |
| `dmap_spawn` | function | `progs/doomedit/doomedit.c:550` | `static long dmap_spawn(const char *path, int argc, const char **argv)` |
| `dmap_stats` | function | `progs/doomedit/doomedit.c:522` | `static void dmap_stats(char *out, int max)` |
| `dmap_thing_type` | function | `progs/doomedit/doomedit.c:165` | `static int dmap_thing_type(int cell)` |
| `dmap_undo` | function | `progs/doomedit/doomedit.c:289` | `static int dmap_undo(void)` |
| `dmap_validate` | function | `progs/doomedit/doomedit.c:1244` | `static int dmap_validate(char *msg, int max)` |
| `dmap_vga` | function | `progs/doomedit/doomedit.c:561` | `static long dmap_vga(int on)` |
| `dmap_w16` | function | `progs/doomedit/doomedit.c:1318` | `static void dmap_w16(int v)` |
| `dmap_w32` | function | `progs/doomedit/doomedit.c:1322` | `static void dmap_w32(int v)` |
| `dmap_w8` | function | `progs/doomedit/doomedit.c:1317` | `static void dmap_w8(unsigned v)` |
| `dmap_walkable` | function | `progs/doomedit/doomedit.c:577` | `static int dmap_walkable(int cell)` |
| `dmap_wtex` | function | `progs/doomedit/doomedit.c:1326` | `static void dmap_wtex(const char *name)` |
| `main` | function | `progs/doomedit/doomedit.c:2246` | `int main(int argc, char **argv)` |
| `AM_Drawer` | function | `progs/doomgeneric/am_map.c:1338` | `void AM_Drawer (void)` |
| `AM_LevelInit` | function | `progs/doomgeneric/am_map.c:518` | `void AM_LevelInit(void)` |
| `AM_NUMMARKPOINTS` | macro | `progs/doomgeneric/am_map.c:87` | `#define AM_NUMMARKPOINTS` |
| `AM_Responder` | function | `progs/doomgeneric/am_map.c:595` | `boolean AM_Responder ( event_t*	ev )` |
| `AM_Start` | function | `progs/doomgeneric/am_map.c:554` | `void AM_Start (void)` |
| `AM_Stop` | function | `progs/doomgeneric/am_map.c:541` | `void AM_Stop (void)` |
| `AM_Ticker` | function | `progs/doomgeneric/am_map.c:806` | `void AM_Ticker (void)` |
| `AM_activateNewScale` | function | `progs/doomgeneric/am_map.c:293` | `void AM_activateNewScale(void)` |
| `AM_addMark` | function | `progs/doomgeneric/am_map.c:343` | `void AM_addMark(void)` |
| `AM_changeWindowLoc` | function | `progs/doomgeneric/am_map.c:395` | `void AM_changeWindowLoc(void)` |
| `AM_changeWindowScale` | function | `progs/doomgeneric/am_map.c:742` | `void AM_changeWindowScale(void)` |
| `AM_clearFB` | function | `progs/doomgeneric/am_map.c:834` | `void AM_clearFB(int color)` |
| `AM_clearMarks` | function | `progs/doomgeneric/am_map.c:505` | `void AM_clearMarks(void)` |
| `AM_clipMline` | function | `progs/doomgeneric/am_map.c:848` | `boolean AM_clipMline ( mline_t*	ml,   fline_t*	fl )` |
| `AM_doFollowPlayer` | function | `progs/doomgeneric/am_map.c:761` | `void AM_doFollowPlayer(void)` |
| `AM_drawCrosshair` | function | `progs/doomgeneric/am_map.c:1332` | `void AM_drawCrosshair(int color)` |
| `AM_drawFline` | function | `progs/doomgeneric/am_map.c:984` | `void AM_drawFline ( fline_t*	fl,   int		color )` |
| `AM_drawGrid` | function | `progs/doomgeneric/am_map.c:1077` | `void AM_drawGrid(int color)` |
| `AM_drawLineCharacter` | function | `progs/doomgeneric/am_map.c:1198` | `void AM_drawLineCharacter ( mline_t*	lineguy,   int		lineguylines,   fixed_t	scale,   angle_t	ang...` |
| `AM_drawMarks` | function | `progs/doomgeneric/am_map.c:1311` | `void AM_drawMarks(void)` |
| `AM_drawMline` | function | `progs/doomgeneric/am_map.c:1062` | `void AM_drawMline ( mline_t*	ml,   int		color )` |
| `AM_drawPlayers` | function | `progs/doomgeneric/am_map.c:1246` | `void AM_drawPlayers(void)` |
| `AM_drawThings` | function | `progs/doomgeneric/am_map.c:1291` | `void AM_drawThings ( int	colors,   int 	colorrange)` |
| `AM_drawWalls` | function | `progs/doomgeneric/am_map.c:1123` | `void AM_drawWalls(void)` |
| `AM_findMinMaxBoundaries` | function | `progs/doomgeneric/am_map.c:355` | `void AM_findMinMaxBoundaries(void)` |
| `AM_getIslope` | function | `progs/doomgeneric/am_map.c:275` | `void AM_getIslope ( mline_t*	ml,   islope_t*	is )` |
| `AM_initVariables` | function | `progs/doomgeneric/am_map.c:424` | `void AM_initVariables(void)` |
| `AM_loadPics` | function | `progs/doomgeneric/am_map.c:480` | `void AM_loadPics(void)` |
| `AM_maxOutWindowScale` | function | `progs/doomgeneric/am_map.c:583` | `void AM_maxOutWindowScale(void)` |
| `AM_minOutWindowScale` | function | `progs/doomgeneric/am_map.c:573` | `void AM_minOutWindowScale(void)` |
| `AM_restoreScaleAndLoc` | function | `progs/doomgeneric/am_map.c:319` | `void AM_restoreScaleAndLoc(void)` |
| `AM_rotate` | function | `progs/doomgeneric/am_map.c:1179` | `void AM_rotate ( fixed_t*	x,   fixed_t*	y,   angle_t	a )` |
| `AM_saveScaleAndLoc` | function | `progs/doomgeneric/am_map.c:308` | `void AM_saveScaleAndLoc(void)` |
| `AM_unloadPics` | function | `progs/doomgeneric/am_map.c:493` | `void AM_unloadPics(void)` |
| `AM_updateLightLev` | function | `progs/doomgeneric/am_map.c:785` | `void AM_updateLightLev(void)` |
| `BACKGROUND` | macro | `progs/doomgeneric/am_map.c:66` | `#define BACKGROUND` |
| `BLACK` | macro | `progs/doomgeneric/am_map.c:62` | `#define BLACK` |
| `BLUERANGE` | macro | `progs/doomgeneric/am_map.c:53` | `#define BLUERANGE` |
| `BLUES` | macro | `progs/doomgeneric/am_map.c:52` | `#define BLUES` |
| `BROWNRANGE` | macro | `progs/doomgeneric/am_map.c:59` | `#define BROWNRANGE` |
| `BROWNS` | macro | `progs/doomgeneric/am_map.c:58` | `#define BROWNS` |
| `CDWALLCOLORS` | macro | `progs/doomgeneric/am_map.c:75` | `#define CDWALLCOLORS` |
| `CDWALLRANGE` | macro | `progs/doomgeneric/am_map.c:76` | `#define CDWALLRANGE` |
| `CXMTOF` | macro | `progs/doomgeneric/am_map.c:105` | `#define CXMTOF(x)` |
| `CYMTOF` | macro | `progs/doomgeneric/am_map.c:106` | `#define CYMTOF(y)` |
| `DOOUTCODE` | macro | `progs/doomgeneric/am_map.c:869` | `#define DOOUTCODE(oc, mx, my)` |
| `FDWALLCOLORS` | macro | `progs/doomgeneric/am_map.c:73` | `#define FDWALLCOLORS` |
| `FDWALLRANGE` | macro | `progs/doomgeneric/am_map.c:74` | `#define FDWALLRANGE` |
| `FTOM` | macro | `progs/doomgeneric/am_map.c:102` | `#define FTOM(x)` |
| `F_PANINC` | macro | `progs/doomgeneric/am_map.c:93` | `#define F_PANINC` |
| `GRAYS` | macro | `progs/doomgeneric/am_map.c:56` | `#define GRAYS` |
| `GRAYSRANGE` | macro | `progs/doomgeneric/am_map.c:57` | `#define GRAYSRANGE` |
| `GREENRANGE` | macro | `progs/doomgeneric/am_map.c:55` | `#define GREENRANGE` |
| `GREENS` | macro | `progs/doomgeneric/am_map.c:54` | `#define GREENS` |
| `GRIDCOLORS` | macro | `progs/doomgeneric/am_map.c:81` | `#define GRIDCOLORS` |
| `GRIDRANGE` | macro | `progs/doomgeneric/am_map.c:82` | `#define GRIDRANGE` |
| `INITSCALEMTOF` | macro | `progs/doomgeneric/am_map.c:90` | `#define INITSCALEMTOF` |
| `LINE_NEVERSEE` | macro | `progs/doomgeneric/am_map.c:109` | `#define LINE_NEVERSEE` |
| `MTOF` | macro | `progs/doomgeneric/am_map.c:103` | `#define MTOF(x)` |
| `M_ZOOMIN` | macro | `progs/doomgeneric/am_map.c:96` | `#define M_ZOOMIN` |
| `M_ZOOMOUT` | macro | `progs/doomgeneric/am_map.c:99` | `#define M_ZOOMOUT` |
| `PUTDOT` | macro | `progs/doomgeneric/am_map.c:1010` | `#define PUTDOT(xx,yy,cc)` |
| `R` | macro | `progs/doomgeneric/am_map.c:143` | `#define R` |
| `R` | macro | `progs/doomgeneric/am_map.c:155` | `#define R` |
| `R` | macro | `progs/doomgeneric/am_map.c:176` | `#define R` |
| `R` | macro | `progs/doomgeneric/am_map.c:184` | `#define R` |
| `REDRANGE` | macro | `progs/doomgeneric/am_map.c:51` | `#define REDRANGE` |
| `REDS` | macro | `progs/doomgeneric/am_map.c:50` | `#define REDS` |
| `SECRETWALLCOLORS` | macro | `progs/doomgeneric/am_map.c:79` | `#define SECRETWALLCOLORS` |
| `SECRETWALLRANGE` | macro | `progs/doomgeneric/am_map.c:80` | `#define SECRETWALLRANGE` |
| `THINGCOLORS` | macro | `progs/doomgeneric/am_map.c:77` | `#define THINGCOLORS` |
| `THINGRANGE` | macro | `progs/doomgeneric/am_map.c:78` | `#define THINGRANGE` |
| `TSWALLCOLORS` | macro | `progs/doomgeneric/am_map.c:71` | `#define TSWALLCOLORS` |
| `TSWALLRANGE` | macro | `progs/doomgeneric/am_map.c:72` | `#define TSWALLRANGE` |
| `WALLCOLORS` | macro | `progs/doomgeneric/am_map.c:69` | `#define WALLCOLORS` |
| `WALLRANGE` | macro | `progs/doomgeneric/am_map.c:70` | `#define WALLRANGE` |
| `WHITE` | macro | `progs/doomgeneric/am_map.c:63` | `#define WHITE` |
| `XHAIRCOLORS` | macro | `progs/doomgeneric/am_map.c:83` | `#define XHAIRCOLORS` |
| `YELLOWRANGE` | macro | `progs/doomgeneric/am_map.c:61` | `#define YELLOWRANGE` |
| `YELLOWS` | macro | `progs/doomgeneric/am_map.c:60` | `#define YELLOWS` |
| `YOURCOLORS` | macro | `progs/doomgeneric/am_map.c:67` | `#define YOURCOLORS` |

Next: [SYMBOLS_p12.md](SYMBOLS_p12.md)
