/* tls.c - TLS 1.2 client sessions for MiniOS.
 *
 * One heap-allocated session per socket that ran tls_handshake; a
 * socket without TLS costs nothing. The handshake is the fixed
 * TLS_ECDHE_RSA/ECDSA_WITH_AES_128_GCM_SHA256 pair: SNI, secp256r1
 * only, RSA PKCS#1 v1.5 or ECDSA signatures, no downgrade, no
 * fallback, no resumption. Every read during the handshake is
 * deadline-bounded; every parse error aborts the session and frees it.
 *
 * Diagnostics are `freedom: tls: <stage>: <reason>` lines (freedom is
 * the only consumer of the TLS syscalls).
 */

#include "tls_port.h"
#include "tls.h"

#ifndef TLS_TEST
#include "tls_roots.h"
#endif

static struct tls_session *tls_sessions[TLS_FD_MAX];

/* ---- diagnostics and teardown ---- */

static void tls_fail(struct tls_session *s, const char *stage, const char *reason) {
    TLS_PRINTF("freedom: tls: %s: %s\n", stage, reason);
    if (s) {
        TLS_FREE(s);
        s = 0;
    }
}

static int tls_fd_of(const struct tls_session *s) {
    int i;
    for (i = 0; i < TLS_FD_MAX; i++)
        if (tls_sessions[i] == s) return i;
    return -1;
}

void tls_free_fd(int fd) {
    if (fd < 0 || fd >= TLS_FD_MAX) return;
    if (tls_sessions[fd]) {
        TLS_FREE(tls_sessions[fd]);
        tls_sessions[fd] = 0;
    }
}

/* ---- record layer ---- */

/* Build the TLS 1.2 AEAD additional data: seq(8) || type || 0303 ||
 * TLSCompressed.length (the plaintext length, RFC 5288 section 3). */
static void tls_aad(unsigned char aad[13], int type, unsigned long long seq,
                    int plain_len) {
    int i;
    for (i = 0; i < 8; i++) aad[i] = (unsigned char)(seq >> (56 - i * 8));
    aad[8] = (unsigned char)type;
    aad[9] = 0x03;
    aad[10] = 0x03;
    aad[11] = (unsigned char)(plain_len >> 8);
    aad[12] = (unsigned char)plain_len;
}

/* Send one record: header || nonce_explicit(8) || ciphertext || tag.
 * The nonce_explicit is the sequence number (RFC 5288 allows it and
 * OpenSSL uses it); the nonce is salt || nonce_explicit. */
static int tls_send_record(struct tls_session *s, int type,
                           const unsigned char *payload, int len) {
    unsigned char *buf = s->tx;
    unsigned char aad[13];
    unsigned char nonce[12];
    int clen = len + 8 + 16;
    int total = len + 5 + 8 + 16;
    int i;
    if (len < 0 || len > TLS_REC_MAX - 32) return -1;
    tls_aad(aad, type, s->cli_seq, len);
    buf[0] = (unsigned char)type;
    buf[1] = 0x03;
    buf[2] = 0x03;
    buf[3] = (unsigned char)(clen >> 8);
    buf[4] = (unsigned char)clen;
    for (i = 0; i < 8; i++)
        buf[5 + i] = (unsigned char)(s->cli_seq >> (56 - i * 8));
    TLS_MEMCPY(nonce, s->cli_salt, 4);
    TLS_MEMCPY(nonce + 4, buf + 5, 8);
    if (aes128_gcm_seal_core(s->cli_key, nonce,
                             aad, 13, payload, (unsigned)len,
                             buf + 5 + 8, buf + 5 + 8 + len) != 0)
        return -1;
    s->cli_seq++;
    if (TLS_SEND(tls_fd_of(s), (const char *)buf, total) != total) return -1;
    return 0;
}

/* Send one plaintext record (ChangeCipherSpec is never encrypted). */
static int tls_send_raw_record(struct tls_session *s, int type,
                               const unsigned char *payload, int len) {
    unsigned char *buf = s->tx;
    int total = len + 5;
    if (len < 0 || len > TLS_REC_MAX - 32) return -1;
    buf[0] = (unsigned char)type;
    buf[1] = 0x03;
    buf[2] = 0x03;
    buf[3] = (unsigned char)(len >> 8);
    buf[4] = (unsigned char)len;
    TLS_MEMCPY(buf + 5, payload, (unsigned)len);
    if (TLS_SEND(tls_fd_of(s), (const char *)buf, total) != total) return -1;
    return 0;
}

/* Read one record: header into s->rec_hdr, payload into s->rec.
 * Returns: 1 = record ready, 0 = clean TCP EOF, -1 = torn record or
 * bad header, -2 = timeout. A non-positive deadline blocks forever
 * (application-data reads behave like plain TCP). */
static int tls_read_record(struct tls_session *s, int fd, int deadline_ms) {
    unsigned char hdr[5];
    int got = 0, started = 0;
    unsigned len;
    while (got < 5) {
        int r = deadline_ms > 0
                    ? TLS_RECV_TIMEOUT(fd, (char *)hdr + got, 5 - got,
                                       (unsigned long)deadline_ms)
                    : TLS_RECV(fd, (char *)hdr + got, 5 - got);
        if (r == 0) return started ? -1 : 0;
        if (r < 0) return -2;
        got += r;
        started = 1;
    }
    if (hdr[1] != 0x03 || hdr[2] != 0x03) return -1;
    len = ((unsigned)hdr[3] << 8) | hdr[4];
    if (len == 0 || len > TLS_REC_MAX) return -1;
    TLS_MEMCPY(s->rec_hdr, hdr, 5);
    s->rec_type = hdr[0];
    s->rec_len = (int)len;
    s->rec_pos = 0;
    while (s->rec_pos < s->rec_len) {
        int r = deadline_ms > 0
                    ? TLS_RECV_TIMEOUT(fd, (char *)s->rec + s->rec_pos,
                                       s->rec_len - s->rec_pos,
                                       (unsigned long)deadline_ms)
                    : TLS_RECV(fd, (char *)s->rec + s->rec_pos,
                               s->rec_len - s->rec_pos);
        if (r == 0) return -1;   /* torn record: fail closed */
        if (r < 0) return -2;
        s->rec_pos += r;
    }
    return 1;
}

/* Decrypt the current record in place with the server keys. The
 * payload is nonce_explicit(8) || ciphertext || tag(16). */
static int tls_decrypt_record(struct tls_session *s) {
    unsigned char aad[13];
    unsigned char nonce[12];
    int plain_len = s->rec_len - 24;
    if (plain_len < 0) return -1;
    tls_aad(aad, s->rec_type, s->srv_seq, plain_len);
    TLS_MEMCPY(nonce, s->srv_salt, 4);
    TLS_MEMCPY(nonce + 4, s->rec, 8);
    if (aes128_gcm_open_core(s->srv_key, nonce,
                             aad, 13, s->rec + 8, (unsigned)plain_len,
                             s->rec + 8 + plain_len, s->rec) != 0)
        return -1;
    s->srv_seq++;
    s->rec_len = plain_len;
    return 0;
}

/* ---- handshake message framing ---- */

/* Send one handshake message (header + body). The message is staged in
 * the session plaintext buffer, so the GCM seal (which writes into the
 * transmit buffer) never overlaps the payload. Messages sent before the
 * key exchange (ClientHello, ClientKeyExchange) go out in plaintext
 * records, as TLS 1.2 requires. */
static int tls_send_hs(struct tls_session *s, int type,
                       const unsigned char *body, int len) {
    if (len < 0 || len > 1024) return -1;
    s->pt[0] = (unsigned char)type;
    s->pt[1] = (unsigned char)(len >> 16);
    s->pt[2] = (unsigned char)(len >> 8);
    s->pt[3] = (unsigned char)len;
    TLS_MEMCPY(s->pt + 4, body, (unsigned)len);
    sha256_update(&s->hs_hash, s->pt, (unsigned)(len + 4));
    if (!s->keys_ready)
        return tls_send_raw_record(s, TLS_CT_HANDSHAKE, s->pt, len + 4);
    return tls_send_record(s, TLS_CT_HANDSHAKE, s->pt, len + 4);
}

/* ClientHello body (without the handshake header). Returns length. */
static int build_client_hello(struct tls_session *s, unsigned char *out) {
    int pos = 0;
    unsigned hl = (unsigned)TLS_STRLEN(s->host);

    out[pos++] = 0x03;
    out[pos++] = 0x03;                          /* client_version */
    TLS_MEMCPY(out + pos, s->cli_random, 32); pos += 32;
    out[pos++] = 0;                             /* session_id length */
    out[pos++] = 0x00;
    out[pos++] = 0x04;                          /* cipher suites length */
    out[pos++] = 0xC0; out[pos++] = 0x2F;       /* ECDHE-RSA-AES128GCM */
    out[pos++] = 0xC0; out[pos++] = 0x2B;       /* ECDHE-ECDSA-AES128GCM */
    out[pos++] = 1;                             /* compression methods */
    out[pos++] = 0;
    /* extensions */
    {
        int ext_start = pos;
        pos += 2;
        /* server_name (SNI) */
        out[pos++] = 0x00; out[pos++] = (unsigned char)TLS_EXT_SERVER_NAME;
        out[pos++] = (unsigned char)((hl + 5) >> 8);
        out[pos++] = (unsigned char)(hl + 5);
        out[pos++] = (unsigned char)((hl + 3) >> 8);
        out[pos++] = (unsigned char)(hl + 3);
        out[pos++] = 0;
        out[pos++] = (unsigned char)(hl >> 8);
        out[pos++] = (unsigned char)hl;
        TLS_MEMCPY(out + pos, s->host, hl); pos += (int)hl;
        /* supported_groups: secp256r1 */
        out[pos++] = 0x00; out[pos++] = (unsigned char)TLS_EXT_SUPPORTED_GROUPS;
        out[pos++] = 0x00; out[pos++] = 0x04;
        out[pos++] = 0x00; out[pos++] = 0x02;
        out[pos++] = 0x00; out[pos++] = (unsigned char)TLS_GROUP_SECP256R1;
        /* ec_point_formats: uncompressed */
        out[pos++] = 0x00; out[pos++] = (unsigned char)TLS_EXT_EC_POINT_FORMATS;
        out[pos++] = 0x00; out[pos++] = 0x02;
        out[pos++] = 0x01; out[pos++] = 0x00;
        /* signature_algorithms */
        out[pos++] = 0x00; out[pos++] = (unsigned char)TLS_EXT_SIGNATURE_ALGS;
        out[pos++] = 0x00; out[pos++] = 0x08;
        out[pos++] = 0x00; out[pos++] = 0x06;
        out[pos++] = 0x04; out[pos++] = 0x01;   /* rsa_pkcs1_sha256 */
        out[pos++] = 0x04; out[pos++] = 0x03;   /* ecdsa_p256_sha256 */
        out[pos++] = 0x05; out[pos++] = 0x03;   /* ecdsa_p384_sha384 */
        {
            int extlen = pos - ext_start - 2;
            out[ext_start] = (unsigned char)(extlen >> 8);
            out[ext_start + 1] = (unsigned char)extlen;
        }
    }
    return pos;
}

/* Derive all keys and send ClientKeyExchange, CCS, Finished. */
static int client_finish_flight(struct tls_session *s) {
    unsigned char cke[1 + 65];
    unsigned char pre_master[32];
    unsigned char seed[64];
    unsigned char key_block[40];
    unsigned char finished[4 + 12];
    unsigned char verify[12];
    unsigned char hash[32];
    int tries;

    /* ephemeral pair: private scalar must be a valid non-zero scalar */
    for (tries = 0; tries < 8; tries++) {
        tls_random(s->cli_priv, 32);
        if (p256_scalar_valid(s->cli_priv) == 0) break;
    }
    if (p256_scalar_valid(s->cli_priv) != 0) {
        tls_fail(s, "key exchange", "no valid scalar");
        return -1;
    }
    p256_pub(s->cli_priv, s->cli_pub_x, s->cli_pub_y);

    /* shared secret: reject the degenerate all-zero result */
    if (p256_ecdh(s->cli_priv, s->srv_pub_x, s->srv_pub_y, pre_master) != 0) {
        tls_fail(s, "key exchange", "bad server point");
        return -1;
    }
    {
        int i, zzero = 1;
        for (i = 0; i < 32; i++) if (pre_master[i]) { zzero = 0; break; }
        if (zzero) {
            tls_fail(s, "key exchange", "zero shared secret");
            return -1;
        }
    }

    TLS_MEMCPY(seed, s->cli_random, 32);
    TLS_MEMCPY(seed + 32, s->srv_random, 32);
    tls_prf(pre_master, 32, "master secret", seed, 64, s->master, 48);

    /* key_block = PRF(master, "key expansion", server_random||client_random) */
    TLS_MEMCPY(seed, s->srv_random, 32);
    TLS_MEMCPY(seed + 32, s->cli_random, 32);
    tls_prf(s->master, 48, "key expansion", seed, 64, key_block, 40);
    TLS_MEMCPY(s->cli_key, key_block, 16);
    TLS_MEMCPY(s->srv_key, key_block + 16, 16);
    TLS_MEMCPY(s->cli_salt, key_block + 32, 4);
    TLS_MEMCPY(s->srv_salt, key_block + 36, 4);
    s->cli_seq = 0;
    s->srv_seq = 0;

    /* ClientKeyExchange: pubkey length byte, then the uncompressed point */
    cke[0] = 65;
    cke[1] = 0x04;
    TLS_MEMCPY(cke + 2, s->cli_pub_x, 32);
    TLS_MEMCPY(cke + 34, s->cli_pub_y, 32);
    if (tls_send_hs(s, TLS_HS_CLIENT_KEY_EXCHANGE, cke, 66) != 0) {
        tls_fail(s, "send", "client key exchange");
        return -1;
    }

    /* ChangeCipherSpec (plaintext) */
    {
        unsigned char ccs[1] = { 1 };
        if (tls_send_raw_record(s, TLS_CT_CCS, ccs, 1) != 0) {
            tls_fail(s, "send", "change cipher spec");
            return -1;
        }
    }
    /* everything after our CCS is encrypted */
    s->keys_ready = 1;

    /* Finished: verify_data = PRF(master, "client finished",
     * Hash(handshake messages up to, not including, this one). The
     * hash is finalized on a copy: the live transcript keeps running
     * for the server Finished. */
    finished[0] = TLS_HS_FINISHED;
    finished[1] = 0;
    finished[2] = 0;
    finished[3] = 12;
    {
        struct sha256_ctx hcopy = s->hs_hash;
        sha256_final(&hcopy, hash);
    }
    tls_prf(s->master, 48, "client finished", hash, 32, verify, 12);
    TLS_MEMCPY(finished + 4, verify, 12);
    if (tls_send_record(s, TLS_CT_HANDSHAKE, finished, 16) != 0) {
        tls_fail(s, "send", "client finished");
        return -1;
    }
    /* the server Finished covers the transcript including our Finished */
    sha256_update(&s->hs_hash, finished, 16);
    return 0;
}

/* ---- handshake message parsers ---- */

static int parse_server_hello(struct tls_session *s,
                              const unsigned char *m, int len) {
    int pos = 0;
    int cs;
    if (len < 38) return -1;
    if (m[pos] != 0x03 || m[pos + 1] != 0x03) return -1;   /* TLS 1.2 only */
    pos += 2;
    TLS_MEMCPY(s->srv_random, m + pos, 32); pos += 32;
    {
        unsigned sid_len = m[pos++];
        if (sid_len > 32 || pos + (int)sid_len > len) return -1;
        pos += (int)sid_len;
    }
    if (pos + 3 > len) return -1;
    cs = (m[pos] << 8) | m[pos + 1]; pos += 2;
    if (cs != TLS_CSUITE_ECDHE_RSA_AES128GCM &&
        cs != TLS_CSUITE_ECDHE_ECDSA_AES128GCM) return -1;
    s->cipher_suite = cs;
    if (m[pos] != 0) return -1;              /* compression */
    pos++;
    if (pos + 2 > len) return -1;
    {
        unsigned ext_len = (unsigned)(m[pos] << 8) | m[pos + 1];
        pos += 2;
        if (pos + (int)ext_len != len) return -1;
        /* extensions: consumed and ignored (we offered none that matter) */
    }
    return 0;
}

static int parse_certificate(struct tls_session *s,
                             const unsigned char *m, int len) {
    int pos = 0;
    unsigned total;
    if (len < 3) return -1;
    total = ((unsigned)m[0] << 16) | ((unsigned)m[1] << 8) | m[2];
    if ((int)total != len - 3) return -1;
    pos = 3;
    s->n_certs = 0;
    {
        /* Certs are stored contiguously: tls_x509_verify_chain walks
         * the chain at consecutive offsets. */
        unsigned stored = 0;
        while (pos < len) {
            unsigned cl;
            if (pos + 3 > len) return -1;
            cl = ((unsigned)m[pos] << 16) | ((unsigned)m[pos + 1] << 8) | m[pos + 2];
            pos += 3;
            if (cl == 0 || cl > TLS_CERT_MAX || pos + (int)cl > len) return -1;
            if (s->n_certs >= 4) return -1;
            if (stored + cl > TLS_CHAIN_MAX) return -1;
            TLS_MEMCPY(s->chain + stored, m + pos, cl);
            s->cert_lens[s->n_certs] = cl;
            s->n_certs++;
            stored += cl;
            pos += (int)cl;
        }
    }
    return 0;
}

static int parse_server_key_exchange(struct tls_session *s,
                                     const unsigned char *m, int len) {
    int pos = 0;
    int sig_alg;
    unsigned sig_len;
    unsigned params_len;
    unsigned char digest[48];
    unsigned char data[64 + 4 + 65];

    if (len < 4) return -1;
    if (m[pos] != 3) return -1;                       /* named_curve */
    pos++;
    if (m[pos] != 0 || m[pos + 1] != TLS_GROUP_SECP256R1) return -1;
    pos += 2;
    if (pos + 1 > len) return -1;
    if (m[pos] != 65) return -1;                      /* uncompressed point */
    pos++;
    if (pos + 64 > len) return -1;
    if (m[pos] != 0x04) return -1;
    TLS_MEMCPY(s->srv_pub_x, m + pos + 1, 32);
    TLS_MEMCPY(s->srv_pub_y, m + pos + 33, 32);
    pos += 65;
    if (p256_point_valid(s->srv_pub_x, s->srv_pub_y) != 0) return -1;
    if (pos + 2 > len) return -1;
    sig_alg = (m[pos] << 8) | m[pos + 1];
    pos += 2;
    if (pos + 2 > len) return -1;
    sig_len = ((unsigned)m[pos] << 8) | m[pos + 1];
    pos += 2;
    if (sig_len == 0 || pos + (int)sig_len != len) return -1;

    s->sig_alg = sig_alg;
    if (!s->leaf_pk_ok) return -1;
    /* signed data: client_random || server_random || SKE params (the
     * exact bytes from curve_type through the point; sig_alg and the
     * signature length are excluded) */
    params_len = len - sig_len - 4;
    if (params_len > sizeof(data) - 64) return -1;
    TLS_MEMCPY(data, s->cli_random, 32);
    TLS_MEMCPY(data + 32, s->srv_random, 32);
    TLS_MEMCPY(data + 64, m, params_len);
    if (sig_alg == TLS_SIG_RSA_PKCS1_SHA256) {
        if (s->leaf_pk.kind != 0) return -1;
        sha256(data, 64 + params_len, digest);
        return rsa_pkcs1_verify_sha256(s->leaf_pk.n, s->leaf_pk.n_len,
                                       s->leaf_pk.e, s->leaf_pk.e_len,
                                       digest, m + pos, sig_len);
    }
    if (sig_alg == TLS_SIG_ECDSA_P256_SHA256) {
        if (s->leaf_pk.kind != 1) return -1;
        sha256(data, 64 + params_len, digest);
        return ecdsa_verify(0, s->leaf_pk.qx, s->leaf_pk.qy,
                            digest, 32, m + pos, sig_len);
    }
    if (sig_alg == TLS_SIG_ECDSA_P384_SHA384) {
        if (s->leaf_pk.kind != 2) return -1;
        sha384(data, 64 + params_len, digest);
        return ecdsa_verify(1, s->leaf_pk.qx, s->leaf_pk.qy,
                            digest, 48, m + pos, sig_len);
    }
    return -1;
}

/* ---- handshake driver ---- */

int tls_handshake(int fd, const char *host) {
    struct tls_session *s;
    unsigned char hello[256];
    int hello_len;
    unsigned hl;

    if (fd < 0 || fd >= TLS_FD_MAX) return -1;
    if (!host || !host[0]) return -1;
    hl = (unsigned)TLS_STRLEN(host);
    if (hl > TLS_HOST_MAX) return -1;
    if (tls_sessions[fd]) {
        TLS_PRINTF("freedom: tls: handshake: session already exists\n");
        return -1;
    }
    s = (struct tls_session *)TLS_MALLOC(sizeof(struct tls_session));
    if (!s) {
        TLS_PRINTF("freedom: tls: handshake: out of memory\n");
        return -1;
    }
    TLS_MEMSET(s, 0, sizeof(*s));
    s->active = 1;
    s->state = 0;
    s->leaf_pk_ok = 0;
    TLS_MEMCPY(s->host, host, hl);
    s->host[hl] = 0;
    tls_sessions[fd] = s;

    tls_random(s->cli_random, 32);
    sha256_init(&s->hs_hash);

    hello_len = build_client_hello(s, hello);
    if (tls_send_hs(s, TLS_HS_CLIENT_HELLO, hello, hello_len) != 0) {
        tls_fail(s, "send", "client hello");
        tls_sessions[fd] = 0;
        return -1;
    }

    for (;;) {
        int r = tls_read_record(s, fd, TLS_HS_TIMEOUT_MS);
        if (r == 0) { tls_fail(s, "handshake", "peer closed"); tls_sessions[fd] = 0; return -1; }
        if (r == -2) { tls_fail(s, "handshake", "timeout"); tls_sessions[fd] = 0; return -1; }
        if (r != 1) { tls_fail(s, "record", "read error"); tls_sessions[fd] = 0; return -1; }

        if (s->rec_type == TLS_CT_CCS) {
            if (s->rec_len != 1 || s->rec[0] != 1) {
                tls_fail(s, "record", "bad change cipher spec");
                tls_sessions[fd] = 0;
                return -1;
            }
            continue;
        }
        if (s->rec_type == TLS_CT_ALERT) {
            TLS_PRINTF("freedom: tls: handshake: peer alert %d %d\n",
                       s->rec_len >= 1 ? s->rec[0] : -1,
                       s->rec_len >= 2 ? s->rec[1] : -1);
            tls_sessions[fd] = 0;
            return -1;
        }
        if (s->rec_type != TLS_CT_HANDSHAKE) {
            tls_fail(s, "handshake", "unexpected record");
            tls_sessions[fd] = 0;
            return -1;
        }
        /* after our CCS everything from the server is encrypted */
        if (s->state >= 4) {
            if (tls_decrypt_record(s) != 0) {
                tls_fail(s, "finished", "bad record mac");
                tls_sessions[fd] = 0;
                return -1;
            }
        }

        /* reassemble the handshake message (may span records) */
        {
            int off = 0;
            while (off < s->rec_len) {
                int need, take;
                if (s->hs_msg_len < 4) {
                    need = 4 - s->hs_msg_len;
                    take = s->rec_len - off < need ? s->rec_len - off : need;
                    TLS_MEMCPY(s->hs_msg + s->hs_msg_len, s->rec + off, (unsigned)take);
                    s->hs_msg_len += take;
                    off += take;
                    if (s->hs_msg_len < 4) continue;
                    s->hs_msg_type = s->hs_msg[0];
                    s->hs_msg_want = 4 + ((s->hs_msg[1] << 16) |
                                          (s->hs_msg[2] << 8) | s->hs_msg[3]);
                    if (s->hs_msg_want > TLS_MSG_MAX) {
                        tls_fail(s, "handshake", "message too large");
                        tls_sessions[fd] = 0;
                        return -1;
                    }
                }
                need = s->hs_msg_want - s->hs_msg_len;
                take = s->rec_len - off < need ? s->rec_len - off : need;
                TLS_MEMCPY(s->hs_msg + s->hs_msg_len, s->rec + off, (unsigned)take);
                s->hs_msg_len += take;
                off += take;
                if (s->hs_msg_len < s->hs_msg_want) continue;

                /* full message: dispatch */
                {
                    const unsigned char *body = s->hs_msg + 4;
                    int blen = s->hs_msg_want - 4;
                    struct sha256_ctx hs_before = s->hs_hash;
                    sha256_update(&s->hs_hash, s->hs_msg, (unsigned)s->hs_msg_want);
                    switch (s->hs_msg_type) {
                    case TLS_HS_SERVER_HELLO:
                        if (s->state != 0 || parse_server_hello(s, body, blen) != 0) {
                            tls_fail(s, "server hello", "bad message");
                            tls_sessions[fd] = 0;
                            return -1;
                        }
                        s->state = 1;
                        break;
                    case TLS_HS_CERTIFICATE:
                        if (s->state != 1 ||
                            parse_certificate(s, body, blen) != 0) {
                            tls_fail(s, "certificate", "bad message");
                            tls_sessions[fd] = 0;
                            return -1;
                        }
                        if (s->n_certs == 0) {
                            tls_fail(s, "certificate", "empty chain");
                            tls_sessions[fd] = 0;
                            return -1;
                        }
                        {
                            unsigned total = 0;
                            int ci;
                            for (ci = 0; ci < s->n_certs; ci++)
                                total += s->cert_lens[ci];
                            if (tls_x509_verify_chain(s->chain, total,
                                                      s->cert_lens, s->n_certs,
                                                      s->host,
                                                      tls_now_days()) != 0) {
                                tls_fail(s, "chain", "verification failed");
                                tls_sessions[fd] = 0;
                                return -1;
                            }
                        }
                        if (tls_x509_parse_pubkey(s->chain, s->cert_lens[0],
                                                  &s->leaf_pk) != 0) {
                            tls_fail(s, "chain", "leaf key unreadable");
                            tls_sessions[fd] = 0;
                            return -1;
                        }
                        s->leaf_pk_ok = 1;
                        s->state = 2;
                        break;
                    case TLS_HS_SERVER_KEY_EXCHANGE:
                        if (s->state != 2 ||
                            parse_server_key_exchange(s, body, blen) != 0) {
                            tls_fail(s, "server key exchange", "bad signature");
                            tls_sessions[fd] = 0;
                            return -1;
                        }
                        s->state = 3;
                        break;
                    case TLS_HS_SERVER_HELLO_DONE:
                        if (s->state != 3) {
                            tls_fail(s, "handshake", "unexpected server done");
                            tls_sessions[fd] = 0;
                            return -1;
                        }
                        if (client_finish_flight(s) != 0) {
                            tls_sessions[fd] = 0;
                            return -1;
                        }
                        s->state = 4;
                        break;
                    case TLS_HS_FINISHED:
                        if (s->state != 4) {
                            tls_fail(s, "finished", "unexpected");
                            tls_sessions[fd] = 0;
                            return -1;
                        }
                        {
                            unsigned char hash[32], want[12];
                            unsigned diff = 0;
                            int k;
                            if (blen != 12) {
                                tls_fail(s, "finished", "bad length");
                                tls_sessions[fd] = 0;
                                return -1;
                            }
                            /* transcript up to, not including, this Finished */
                            sha256_final(&hs_before, hash);
                            tls_prf(s->master, 48, "server finished", hash, 32, want, 12);
                            for (k = 0; k < 12; k++) diff |= want[k] ^ body[k];
                            if (diff) {
                                tls_fail(s, "finished", "verify failed");
                                tls_sessions[fd] = 0;
                                return -1;
                            }
                        }
                        s->hs_done = 1;
                        s->state = 5;
                        if (off != s->rec_len) {
                            tls_fail(s, "finished", "trailing data");
                            tls_sessions[fd] = 0;
                            return -1;
                        }
                        return 0;
                    default:
                        /* NewSessionTicket (4) or anything unexpected
                         * pre-Finished is refused */
                        tls_fail(s, "handshake", "unexpected message");
                        tls_sessions[fd] = 0;
                        return -1;
                    }
                }
                s->hs_msg_len = 0;
                s->hs_msg_want = 0;
            }
        }
    }
}

/* ---- application data ---- */

int tls_send(int fd, const char *buf, int len) {
    struct tls_session *s = tls_sessions[fd];
    if (!s || !s->hs_done) return -1;
    if (len < 0 || len > TLS_REC_MAX - 32) return -1;
    if (tls_send_record(s, TLS_CT_APPDATA, (const unsigned char *)buf, len) != 0)
        return -1;
    return len;
}

int tls_recv(int fd, char *buf, int len) {
    struct tls_session *s = tls_sessions[fd];
    if (!s || !s->hs_done) return -1;
    if (len <= 0) return 0;

    /* drain pending plaintext first */
    if (s->pt_head < s->pt_tail) {
        int avail = s->pt_tail - s->pt_head;
        int take = avail > len ? len : avail;
        TLS_MEMCPY(buf, s->pt + s->pt_head, (unsigned)take);
        s->pt_head += take;
        if (s->pt_head == s->pt_tail) { s->pt_head = 0; s->pt_tail = 0; }
        return take;
    }
    if (s->eof) return 0;

    for (;;) {
        int r = tls_read_record(s, tls_fd_of(s), 0);
        if (r == 0) {
            /* TCP EOF: clean only at a record boundary with nothing
             * pending; a torn record is a truncation attack. */
            s->eof = 1;
            return 0;
        }
        if (r == -2) { TLS_PRINTF("freedom: tls: recv: timeout\n"); return -1; }
        if (r != 1) { TLS_PRINTF("freedom: tls: recv: torn record\n"); return -1; }

        if (s->rec_type == TLS_CT_APPDATA) {
            if (tls_decrypt_record(s) != 0) {
                TLS_PRINTF("freedom: tls: recv: bad record mac\n");
                return -1;
            }
            {
                int take = s->rec_len > len ? len : s->rec_len;
                TLS_MEMCPY(buf, s->rec, (unsigned)take);
                if (take < s->rec_len) {
                    TLS_MEMCPY(s->pt, s->rec + take, (unsigned)(s->rec_len - take));
                    s->pt_head = 0;
                    s->pt_tail = s->rec_len - take;
                }
                return take;
            }
        }
        if (s->rec_type == TLS_CT_CCS) continue;
        if (s->rec_type == TLS_CT_ALERT) {
            /* Alerts are encrypted after the key exchange: decrypt first,
             * then read the plaintext level/description. */
            if (tls_decrypt_record(s) != 0) {
                TLS_PRINTF("freedom: tls: recv: bad record mac\n");
                return -1;
            }
            /* close_notify = clean EOF; anything else is fatal */
            if (s->rec_len == 2 && s->rec[1] == 0) {
                s->eof = 1;
                return 0;
            }
            TLS_PRINTF("freedom: tls: recv: peer alert %d\n", s->rec_len ? s->rec[1] : -1);
            return -1;
        }
        /* post-handshake handshake records (NewSessionTicket etc.) are
         * decrypted and skipped */
        if (s->rec_type == TLS_CT_HANDSHAKE) {
            if (tls_decrypt_record(s) != 0) {
                TLS_PRINTF("freedom: tls: recv: bad record mac\n");
                return -1;
            }
            continue;
        }
        TLS_PRINTF("freedom: tls: recv: unknown record\n");
        return -1;
    }
}

/* ========== Syscalls ========== */

#ifndef TLS_TEST
long tls_sys_handshake(long fd, long host) {
    if (fd < NET_FD_BASE || fd >= NET_FD_BASE + NET_SOCKETS || !host) return -1;
    return tls_handshake((int)(fd - NET_FD_BASE), (const char *)host);
}

long tls_sys_send(long fd, long buf, long len) {
    if (fd < NET_FD_BASE || fd >= NET_FD_BASE + NET_SOCKETS || !buf) return -1;
    return tls_send((int)(fd - NET_FD_BASE), (const char *)buf, (int)len);
}

long tls_sys_recv(long fd, long buf, long len) {
    if (fd < NET_FD_BASE || fd >= NET_FD_BASE + NET_SOCKETS || !buf) return -1;
    return tls_recv((int)(fd - NET_FD_BASE), (char *)buf, (int)len);
}

/* ---- kernel entropy and clock ---- */

static inline unsigned long long tls_rdtsc(void) {
    unsigned lo, hi;
    __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long long)hi << 32) | lo;
}

void tls_random(unsigned char *out, unsigned len) {
    unsigned long long seed = tls_rdtsc() ^ ((unsigned long long)net_time_ms() << 33);
    unsigned i;
    static unsigned long long counter = 0x6D696E69544C53ULL;
    counter ^= seed;
    for (i = 0; i < len; i++) {
        seed = seed * 6364136223846793005ULL + 1442695040888963407ULL;
        out[i] = (unsigned char)((seed >> 33) ^ (counter >> (i & 7) * 8));
        counter = counter * 6364136223846793005ULL + 1;
    }
}

/* The port helpers in net.c are static; these live here for the RTC. */
#ifndef PORT_IO_DEFINED
#define PORT_IO_DEFINED
static inline void outb(unsigned short port, unsigned char v) {
    __asm__ volatile("outb %0, %1" : : "a"(v), "Nd"(port));
}
static inline unsigned char inb(unsigned short port) {
    unsigned char v;
    __asm__ volatile("inb %1, %0" : "=a"(v) : "Nd"(port));
    return v;
}
#endif

/* CMOS RTC -> days since epoch. Registers are BCD. */
static inline unsigned char cmos_read(unsigned char reg) {
    outb(0x70, reg);
    return inb(0x71);
}

long tls_now_days(void) {
    static long fallback = 0;
    unsigned char sec, min, hour, day, month, year, century;
    int y, m, d;
    /* wait out the update-in-progress flag */
    {
        int spins;
        for (spins = 0; spins < 100000; spins++)
            if (!(cmos_read(0x0A) & 0x80)) break;
    }
    sec = cmos_read(0x00);
    min = cmos_read(0x02);
    hour = cmos_read(0x04);
    day = cmos_read(0x07);
    month = cmos_read(0x08);
    year = cmos_read(0x09);
    century = cmos_read(0x32);
    (void)sec; (void)min; (void)hour;
    if (!(cmos_read(0x0B) & 0x04)) {
        year = (unsigned char)((year & 0xF) + ((year >> 4) * 10));
        month = (unsigned char)((month & 0xF) + ((month >> 4) * 10));
        day = (unsigned char)((day & 0xF) + ((day >> 4) * 10));
        century = (unsigned char)((century & 0xF) + ((century >> 4) * 10));
    }
    /* QEMU sets the century register; a garbage century falls back to
     * the 2000s so a machine without 0x32 still gets a sane clock. */
    if (century >= 20 && century <= 21) y = century * 100 + year;
    else y = 2000 + year;
    m = month;
    d = day;
    if (y < 2020 || y > 2100 || m < 1 || m > 12 || d < 1 || d > 31)
        return fallback;
    {
        long era, doe, yoe;
        int doy, yy = y;
        yy -= m <= 2 ? 1 : 0;
        era = (yy >= 0 ? yy : yy - 399) / 400;
        yoe = yy - (int)era * 400;
        doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
        doe = (long)yoe * 365 + yoe / 4 - yoe / 100 + doy;
        return era * 146097 + doe - 719468;
    }
}

#endif
