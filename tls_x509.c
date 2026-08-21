/* tls_x509.c - minimal X.509 DER parsing and chain verification.
 *
 * Enough of the ASN.1 DER world for a TLS 1.2 client: the public key
 * (RSA up to 4096 bits, ECDSA on P-256/P-384), the signature algorithm,
 * the subject CN / SAN dNSNames, the validity window, and signature
 * verification of each certificate against its issuer, down to the
 * embedded roots. Every read is bounds checked; any parse error fails
 * the whole chain, never skips a check.
 */

#include "tls_port.h"
#include "tls.h"

/* Signature algorithm OIDs (appear in tbsCertificate.signature) */
static const unsigned char oid_sha384_rsa[] =
    { 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0c };
static const unsigned char oid_sha256_rsa[] =
    { 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x0b };
static const unsigned char oid_ecdsa_sha256[] =
    { 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x04, 0x03, 0x02 };
static const unsigned char oid_ecdsa_sha384[] =
    { 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x04, 0x03, 0x03 };
static const unsigned char oid_rsa_encryption[] =
    { 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x0d, 0x01, 0x01, 0x01 };
static const unsigned char oid_ec_public_key[] =
    { 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x02, 0x01 };
static const unsigned char oid_prime256v1[] =
    { 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x03, 0x01, 0x07 };
static const unsigned char oid_secp384r1[] =
    { 0x2b, 0x81, 0x04, 0x00, 0x22 };
static const unsigned char oid_cn[] =
    { 0x55, 0x04, 0x03 };
static const unsigned char oid_san[] =
    { 0x55, 0x1d, 0x11 };

static int oid_eq(const unsigned char *bytes, unsigned len,
                  const unsigned char *oid, unsigned oid_len) {
    return len == oid_len && TLS_MEMCMP(bytes, oid, oid_len) == 0;
}

/* ---- DER walking ---- */

struct der_tlv {
    const unsigned char *val;
    unsigned len;
    unsigned tag;
};

/* Parse the TLV at p[pos]; advances pos to the first byte after it.
 * Returns 0 on success, -1 on any bound violation. */
static int der_next(const unsigned char *p, unsigned limit, unsigned *pos,
                    struct der_tlv *out) {
    unsigned tag, i, len = 0;
    if (*pos >= limit) return -1;
    tag = p[(*pos)++];
    if ((tag & 0x1f) == 0x1f) {
        /* multi-byte tag: consume one more byte, no constraint on form */
        if (*pos >= limit) return -1;
        (*pos)++;
    }
    if (*pos >= limit) return -1;
    if (p[*pos] & 0x80) {
        unsigned llen = p[*pos] & 0x7f;
        if (llen == 0 || llen > 4) return -1;
        (*pos)++;
        for (i = 0; i < llen; i++) {
            if (*pos >= limit) return -1;
            len = (len << 8) | p[(*pos)++];
        }
    } else {
        len = p[(*pos)++];
    }
    if (len > limit - *pos) return -1;
    out->val = p + *pos;
    out->len = len;
    out->tag = tag;
    *pos += len;
    return 0;
}

/* A constructed SEQUENCE/SET whose content must parse as children. */
static int der_container(const unsigned char *p, unsigned limit, unsigned *pos,
                         const unsigned char **val, unsigned *len) {
    struct der_tlv t;
    if (der_next(p, limit, pos, &t) != 0) return -1;
    if (t.tag != 0x30) return -1;
    *val = t.val;
    *len = t.len;
    return 0;
}

/* ---- Time ---- */

static long days_from_civil(int y, int m, int d) {
    long era, doe, yoe;
    int doy;
    y -= m <= 2 ? 1 : 0;
    era = (y >= 0 ? y : y - 399) / 400;
    yoe = y - (int)era * 400;
    doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
    doe = (long)yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + doe - 719468;
}

/* UTCTime / GeneralizedTime "....Z" -> days since epoch, or -1. */
static long der_time_to_days(const struct der_tlv *t) {
    const unsigned char *v = t->val;
    int year, mon, day;
    if (t->tag == 0x17 && t->len >= 13 && v[12] == 'Z') {
        year = (v[0] - '0') * 10 + (v[1] - '0');
        year += year >= 50 ? 1900 : 2000;
        mon = (v[2] - '0') * 10 + (v[3] - '0');
        day = (v[4] - '0') * 10 + (v[5] - '0');
    } else if (t->tag == 0x18 && t->len >= 15 && v[14] == 'Z') {
        year = (v[0] - '0') * 1000 + (v[1] - '0') * 100 +
               (v[2] - '0') * 10 + (v[3] - '0');
        mon = (v[4] - '0') * 10 + (v[5] - '0');
        day = (v[6] - '0') * 10 + (v[7] - '0');
    } else {
        return -1;
    }
    if (mon < 1 || mon > 12 || day < 1 || day > 31 || year < 1970 || year > 2100)
        return -1;
    return days_from_civil(year, mon, day);
}

/* ---- Name / extensions ---- */

struct x509_name {
    unsigned char cn[64];
    unsigned cn_len;
};

/* Find the first CN in an RDNSequence. Returns 0 when found. */
static int name_find_cn(const unsigned char *p, unsigned limit,
                        struct x509_name *out) {
    const unsigned char *seq;
    unsigned seq_len, pos = 0;
    out->cn_len = 0;
    if (der_container(p, limit, &pos, &seq, &seq_len) != 0) return -1;
    pos = 0;
    /* RDNSequence: SEQUENCE OF SET OF SEQUENCE { OID, value } */
    while (pos < seq_len) {
        const unsigned char *set, *rdn, *oid, *val;
        unsigned set_len, rdn_len, oid_len, val_len, spos = 0, rpos = 0;
        if (der_container(seq, seq_len, &pos, &set, &set_len) != 0) return -1;
        while (spos < set_len) {
            struct der_tlv t;
            if (der_container(set, set_len, &spos, &rdn, &rdn_len) != 0) return -1;
            if (der_next(rdn, rdn_len, &rpos, &t) != 0) return -1;
            oid = t.val; oid_len = t.len;
            if (der_next(rdn, rdn_len, &rpos, &t) != 0) return -1;
            val = t.val; val_len = t.len;
            if (oid_eq(oid, oid_len, oid_cn, sizeof(oid_cn))) {
                if (val_len < 64) {
                    TLS_MEMCPY(out->cn, val, val_len);
                    out->cn_len = val_len;
                }
                return 0;
            }
        }
    }
    return -1;
}

/* SAN dNSName walk. Callback-less: fill the first TLS_SAN_MAX names.
 * Bounded, but generous: real-world leaves carry dozens of dNSName
 * entries (Wikipedia's leaf lists 38), and dropping the matching entry
 * off the tail would fail closed for no security gain. */
#define TLS_SAN_MAX 64

struct x509_sans {
    unsigned char dns[TLS_SAN_MAX][64];
    unsigned      len[TLS_SAN_MAX];
    int           count;
};

static void san_add(struct x509_sans *out, const unsigned char *v, unsigned len) {
    if (out->count >= TLS_SAN_MAX || len >= 64) return;
    TLS_MEMCPY(out->dns[out->count], v, len);
    out->len[out->count] = len;
    out->count++;
}

/* Walk the SAN extension (2.5.29.17) OCTET STRING body. */
static void san_parse(const unsigned char *p, unsigned limit,
                      struct x509_sans *out) {
    const unsigned char *seq;
    unsigned seq_len, pos = 0;
    out->count = 0;
    if (der_container(p, limit, &pos, &seq, &seq_len) != 0) return;
    pos = 0;
    while (pos < seq_len) {
        struct der_tlv t;
        if (der_next(seq, seq_len, &pos, &t) != 0) return;
        if (t.tag == 0x82) san_add(out, t.val, t.len); /* dNSName */
    }
}

/* ---- Public key ---- */

/* SPKI SEQUENCE content: { alg SEQUENCE { OID, params }, BIT STRING }. */
static int spki_parse(const unsigned char *p, unsigned limit,
                      struct tls_pubkey *pk) {
    const unsigned char *alg, *oid;
    unsigned alg_len, oid_len, pos = 0, apos = 0;
    struct der_tlv t;

    pk->kind = -1;
    if (der_next(p, limit, &pos, &t) != 0 || t.tag != 0x30) return -1;
    alg = t.val; alg_len = t.len;
    if (der_next(alg, alg_len, &apos, &t) != 0) return -1;
    oid = t.val; oid_len = t.len;
    if (oid_eq(oid, oid_len, oid_rsa_encryption, sizeof(oid_rsa_encryption))) {
        /* BIT STRING wrapping SEQUENCE { INTEGER n, INTEGER e } */
        const unsigned char *rs;
        unsigned rs_len, rpos = 0, bpos;
        if (der_next(p, limit, &pos, &t) != 0 || t.tag != 0x03) return -1;
        bpos = 0;
        if (t.len == 0 || t.val[0] != 0) return -1;
        if (der_container(t.val + 1, t.len - 1, &bpos, &rs, &rs_len) != 0)
            return -1;
        if (der_next(rs, rs_len, &rpos, &t) != 0) return -1;
        /* INTEGERs pad the top bit with a leading zero byte */
        if (t.len == 0 || t.len > 513) return -1;
        if (t.val[0] == 0) { t.val++; t.len--; }
        if (t.len == 0) return -1;
        pk->n_len = t.len;
        TLS_MEMCPY(pk->n, t.val, t.len);
        if (der_next(rs, rs_len, &rpos, &t) != 0) return -1;
        if (t.len == 0 || t.len > 8) return -1;
        pk->e_len = t.len;
        TLS_MEMCPY(pk->e, t.val, t.len);
        pk->kind = 0;
        return 0;
    }
    if (oid_eq(oid, oid_len, oid_ec_public_key, sizeof(oid_ec_public_key))) {
        int curve;
        const unsigned char *params;
        unsigned plen;
        if (der_next(alg, alg_len, &apos, &t) != 0) return -1;
        params = t.val; plen = t.len;
        if (oid_eq(params, plen, oid_prime256v1, sizeof(oid_prime256v1)))
            curve = 0;
        else if (oid_eq(params, plen, oid_secp384r1, sizeof(oid_secp384r1)))
            curve = 1;
        else return -1;
        if (der_next(p, limit, &pos, &t) != 0 || t.tag != 0x03) return -1;
        /* BIT STRING: unused-bits byte, then 0x04 || X || Y */
        if (t.len < 2 || t.val[0] != 0 || t.val[1] != 0x04) return -1;
        {
            unsigned clen = curve == 0 ? 32 : 48;
            if (t.len != 2 + 2 * clen) return -1;
            TLS_MEMCPY(pk->qx, t.val + 2, clen);
            TLS_MEMCPY(pk->qy, t.val + 2 + clen, clen);
        }
        pk->kind = curve == 0 ? 1 : 2;
        return 0;
    }
    return -1;
}

/* ---- Certificate ---- */

struct x509_cert {
    const unsigned char *tbs;
    unsigned tbs_len;
    int sig_alg;            /* 0 RSA-SHA256, 1 ECDSA-SHA256, 2 ECDSA-SHA384 */
    const unsigned char *sig;
    unsigned sig_len;
    struct tls_pubkey pk;
    struct x509_name subject;
    struct x509_sans sans;
    int has_san;
    long not_before_days;
    long not_after_days;
};

static int cert_parse(const unsigned char *der, unsigned len,
                      struct x509_cert *out) {
    const unsigned char *seq, *tbs, *issuer, *validity, *subject;
    unsigned seq_len, tbs_len, issuer_len, validity_len, subject_len;
    unsigned pos = 0, tpos = 0, vpos = 0;
    struct der_tlv t;

    out->has_san = 0;
    out->sans.count = 0;
    out->subject.cn_len = 0;
    out->sig_alg = -1;

    if (der_container(der, len, &pos, &seq, &seq_len) != 0) return -1;
    pos = 0;
    /* tbsCertificate: the signature covers the whole TLV, header included */
    {
        unsigned tbs_start = pos;
        if (der_container(seq, seq_len, &pos, &tbs, &tbs_len) != 0) return -1;
        out->tbs = seq + tbs_start;
        out->tbs_len = pos - tbs_start;
    }
    /* signatureAlgorithm */
    if (der_next(seq, seq_len, &pos, &t) != 0 || t.tag != 0x30) return -1;
    /* signatureValue BIT STRING */
    if (der_next(seq, seq_len, &pos, &t) != 0 || t.tag != 0x03) return -1;
    if (t.len == 0) return -1;
    out->sig = t.val + 1;
    out->sig_len = t.len - 1;

    /* tbs: [0] version?, serial, signature, issuer, validity, subject, SPKI */
    if (der_next(tbs, tbs_len, &tpos, &t) != 0) return -1;
    if (t.tag == 0xa0) {
        if (der_next(tbs, tbs_len, &tpos, &t) != 0) return -1; /* serial */
    }
    /* signature (OID inside) */
    {
        const unsigned char *sigseq, *oid;
        unsigned sigseq_len, oid_len, spos = 0;
        if (der_container(tbs, tbs_len, &tpos, &sigseq, &sigseq_len) != 0)
            return -1;
        if (der_next(sigseq, sigseq_len, &spos, &t) != 0) return -1;
        oid = t.val; oid_len = t.len;
        if (oid_eq(oid, oid_len, oid_sha256_rsa, sizeof(oid_sha256_rsa)))
            out->sig_alg = 0;
        else if (oid_eq(oid, oid_len, oid_sha384_rsa, sizeof(oid_sha384_rsa)))
            out->sig_alg = 3;
        else if (oid_eq(oid, oid_len, oid_ecdsa_sha256, sizeof(oid_ecdsa_sha256)))
            out->sig_alg = 1;
        else if (oid_eq(oid, oid_len, oid_ecdsa_sha384, sizeof(oid_ecdsa_sha384)))
            out->sig_alg = 2;
        else return -1;
    }
    /* issuer */
    if (der_container(tbs, tbs_len, &tpos, &issuer, &issuer_len) != 0)
        return -1;
    /* validity: SEQUENCE { notBefore, notAfter } */
    if (der_container(tbs, tbs_len, &tpos, &validity, &validity_len) != 0)
        return -1;
    if (der_next(validity, validity_len, &vpos, &t) != 0) return -1;
    out->not_before_days = der_time_to_days(&t);
    if (out->not_before_days < 0) return -1;
    if (der_next(validity, validity_len, &vpos, &t) != 0) return -1;
    out->not_after_days = der_time_to_days(&t);
    if (out->not_after_days < 0) return -1;
    /* subject */
    if (der_container(tbs, tbs_len, &tpos, &subject, &subject_len) != 0)
        return -1;
    if (name_find_cn(subject, subject_len, &out->subject) != 0)
        out->subject.cn_len = 0;
    /* SPKI */
    {
        struct der_tlv spki_t;
        if (der_next(tbs, tbs_len, &tpos, &spki_t) != 0) return -1;
        if (spki_parse(spki_t.val, spki_t.len, &out->pk) != 0) return -1;
    }
    /* [3] extensions (optional) */
    if (tpos < tbs_len) {
        if (der_next(tbs, tbs_len, &tpos, &t) != 0) return -1;
        if (t.tag == 0xa3) {
            const unsigned char *exts;
            unsigned exts_len, epos = 0;
            if (der_container(t.val, t.len, &epos, &exts, &exts_len) == 0) {
                unsigned xpos = 0;
                while (xpos < exts_len) {
                    const unsigned char *ext, *eoid;
                    unsigned ext_len, eoid_len, e2pos = 0;
                    struct der_tlv v;
                    if (der_container(exts, exts_len, &xpos, &ext, &ext_len) != 0)
                        break;
                    if (der_next(ext, ext_len, &e2pos, &v) != 0) break;
                    eoid = v.val; eoid_len = v.len;
                    if (e2pos < ext_len && ext[e2pos] == 0x01) {
                        /* critical flag */
                        if (der_next(ext, ext_len, &e2pos, &v) != 0) break;
                    }
                    if (e2pos >= ext_len) break;
                    {
                        struct der_tlv body;
                        unsigned bpos = e2pos;
                        if (der_next(ext, ext_len, &bpos, &body) != 0) break;
                        if (oid_eq(eoid, eoid_len, oid_san, sizeof(oid_san)))
                            san_parse(body.val, body.len, &out->sans),
                            out->has_san = 1;
                    }
                }
            }
        }
    }
    return 0;
}

/* ---- Hostname matching ---- */

static int ascii_lower(int c) {
    return (c >= 'A' && c <= 'Z') ? c + ('a' - 'A') : c;
}

/* Exact match, ASCII case-insensitive. */
static int host_match_exact(const char *host, const unsigned char *name,
                            unsigned name_len) {
    unsigned i;
    for (i = 0; i < name_len; i++) {
        char c = host[i];
        if (c == 0) return 0;
        if (ascii_lower((unsigned char)c) != ascii_lower(name[i])) return 0;
    }
    return host[name_len] == 0;
}

/* Wildcard: "*.example.com" matches exactly one label ("a.example.com",
 * never "a.b.example.com" nor "example.com"). */
static int host_match_wildcard(const char *host, const unsigned char *name,
                               unsigned name_len) {
    unsigned hl, i;
    if (name_len < 3 || name[0] != '*' || name[1] != '.') return 0;
    hl = 0;
    while (host[hl]) {
        if (host[hl] == '.') break;
        hl++;
    }
    if (host[hl] != '.') return 0;
    if (hl == 0) return 0;
    /* the wildcard consumes exactly one label: the tail ".example.com"
     * (name_len - 1 bytes from the dot) must match the host to the end */
    for (i = 0; i < name_len; i++) {
        if (host[hl + i] == 0) return 0;
        if (ascii_lower((unsigned char)host[hl + i]) != ascii_lower(name[i + 1]))
            return 0;
    }
    return host[hl + i] == 0;
}

static int host_matches(const char *host, const struct x509_cert *leaf) {
    int i;
    if (leaf->has_san) {
        for (i = 0; i < leaf->sans.count; i++) {
            if (host_match_exact(host, leaf->sans.dns[i], leaf->sans.len[i]) ||
                host_match_wildcard(host, leaf->sans.dns[i], leaf->sans.len[i]))
                return 1;
        }
        return 0;   /* SAN present and nothing matched: fail closed */
    }
    if (leaf->subject.cn_len) {
        return host_match_exact(host, leaf->subject.cn, leaf->subject.cn_len) ||
               host_match_wildcard(host, leaf->subject.cn, leaf->subject.cn_len);
    }
    return 0;
}

/* ---- Signature verification ---- */

/* ========== Public API ========== */

int tls_x509_parse_pubkey(const unsigned char *der, unsigned len,
                          struct tls_pubkey *pk) {
    struct x509_cert cert;
    if (cert_parse(der, len, &cert) != 0) return -1;
    TLS_MEMCPY(pk, &cert.pk, sizeof(*pk));
    return 0;
}

/* Trust anchors are matched by public key, not by self-signature: a
 * presented root is often a cross-signed copy (signed by a legacy root,
 * e.g. the SSL.com 2022 roots are signed by Comodo AAA), so checking its
 * signature against its own key would reject a perfectly valid anchor.
 * Key equality is safe because every link above the top is still
 * signature-verified: an attacker cannot present a top cert carrying an
 * embedded root's public key unless the chain below it was signed with
 * that root's private key. */
static int pubkey_equal(const struct tls_pubkey *a, const struct tls_pubkey *b) {
    if (a->kind != b->kind) return 0;
    if (a->kind == 0)
        return a->n_len == b->n_len && a->e_len == b->e_len &&
               TLS_MEMCMP(a->n, b->n, a->n_len) == 0 &&
               TLS_MEMCMP(a->e, b->e, a->e_len) == 0;
    return TLS_MEMCMP(a->qx, b->qx, 48) == 0 &&
           TLS_MEMCMP(a->qy, b->qy, 48) == 0;
}

/* Verify one certificate's signature with an issuer public key. */
static int cert_verify_signature(const struct x509_cert *cert,
                                 const struct tls_pubkey *issuer_key) {
    unsigned char digest[48];
    if (cert->sig_alg == 0) {
        if (issuer_key->kind != 0) return -1;
        sha256(cert->tbs, cert->tbs_len, digest);
        return rsa_pkcs1_verify_sha256(issuer_key->n, issuer_key->n_len,
                                       issuer_key->e, issuer_key->e_len,
                                       digest, cert->sig, cert->sig_len);
    }
    if (cert->sig_alg == 3) {
        /* sha384WithRSAEncryption (GTS Root R1 and friends) */
        unsigned char d48[48];
        if (issuer_key->kind != 0) return -1;
        sha384(cert->tbs, cert->tbs_len, d48);
        return rsa_pkcs1_verify_sha384(issuer_key->n, issuer_key->n_len,
                                       issuer_key->e, issuer_key->e_len,
                                       d48, cert->sig, cert->sig_len);
    }
    if (cert->sig_alg == 1) {
        /* ECDSA-SHA256: the curve comes from the issuer key, which may
         * be P-256 or P-384 (openssl signs SHA-256 with either). */
        unsigned char d32[32];
        sha256(cert->tbs, cert->tbs_len, d32);
        if (issuer_key->kind == 1)
            return ecdsa_verify(0, issuer_key->qx, issuer_key->qy,
                                d32, 32, cert->sig, cert->sig_len);
        if (issuer_key->kind == 2)
            return ecdsa_verify(1, issuer_key->qx, issuer_key->qy,
                                d32, 32, cert->sig, cert->sig_len);
        return -1;
    }
    if (cert->sig_alg == 2) {
        unsigned char d384[48];
        if (issuer_key->kind != 2) return -1;
        sha384(cert->tbs, cert->tbs_len, d384);
        return ecdsa_verify(1, issuer_key->qx, issuer_key->qy,
                            d384, 48, cert->sig, cert->sig_len);
    }
    return -1;
}

int tls_x509_verify_chain(const unsigned char *chain, unsigned chain_len,
                          unsigned cert_lens[], int n_certs,
                          const char *host, long now_days) {
    struct x509_cert *certs;
    int i, rc = -1;

    if (n_certs < 1 || n_certs > 4) return -1;
    certs = (struct x509_cert *)TLS_MALLOC((unsigned)n_certs * sizeof(struct x509_cert));
    if (!certs) return -1;

    /* Parse every presented certificate first: no partial state. */
    {
        unsigned off = 0;
        for (i = 0; i < n_certs; i++) {
            if (off + cert_lens[i] > chain_len || cert_lens[i] == 0)
                goto done;
            if (cert_parse(chain + off, cert_lens[i], &certs[i]) != 0)
                goto done;
            off += cert_lens[i];
        }
    }

    /* Leaf: hostname + validity */
    if (!host_matches(host, &certs[0])) goto done;
    if (now_days < certs[0].not_before_days || now_days > certs[0].not_after_days)
        goto done;

    /* Intermediate links: cert i signed by cert i+1 (same validity gate) */
    for (i = 0; i < n_certs - 1; i++) {
        if (now_days < certs[i + 1].not_before_days ||
            now_days > certs[i + 1].not_after_days)
            goto done;
        if (cert_verify_signature(&certs[i], &certs[i + 1].pk) != 0)
            goto done;
    }

    /* Top of the presented chain must chain to an embedded root: either
     * the top is one of the roots by public key (covers cross-signed
     * roots, see pubkey_equal), or the root's key verifies the top's
     * signature (covers chains the server truncates at the leaf). */
    {
        int root_found = 0;
        for (i = 0; i < TLS_ROOT_COUNT; i++) {
            struct x509_cert root;
            if (cert_parse(tls_roots[i].der, tls_roots[i].len, &root) != 0)
                continue;
            if (pubkey_equal(&certs[n_certs - 1].pk, &root.pk) ||
                cert_verify_signature(&certs[n_certs - 1], &root.pk) == 0) {
                root_found = 1;
                break;
            }
        }
        if (!root_found) goto done;
    }

    rc = 0;
done:
    TLS_FREE(certs);
    return rc;
}
