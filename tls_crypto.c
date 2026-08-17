/* tls_crypto.c - the crypto behind the kernel TLS 1.2 client.
 *
 * SHA-256, HMAC-SHA256, the TLS 1.2 PRF, AES-128 (T-table, encryption
 * only), AES-128-GCM, big integers with Montgomery multiplication,
 * secp256r1/secp384r1 (Jacobian ladder scalar multiplication), ECDSA
 * verify and RSA PKCS#1 v1.5 verify (SHA-256).
 *
 * Constant-time notes: the GCM GHASH never branches on key bits, the
 * curve ladder is branch-free per bit, and every verify path compares
 * with a constant-time equality. AES uses the standard T-table
 * implementation (MiniOS is single-user; documented, not hidden).
 */

#include "tls_port.h"
#include "tls.h"

/* ========== SHA-256 ========== */

static const unsigned sha256_k[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1,
    0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174, 0xe49b69c1, 0xefbe4786,
    0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147,
    0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 0xa2bfe8a1, 0xa81a664b,
    0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a,
    0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

static unsigned sha256_rotr(unsigned x, unsigned n) {
    return (x >> n) | (x << (32 - n));
}

void sha256_init(struct sha256_ctx *c) {
    c->state[0] = 0x6a09e667;
    c->state[1] = 0xbb67ae85;
    c->state[2] = 0x3c6ef372;
    c->state[3] = 0xa54ff53a;
    c->state[4] = 0x510e527f;
    c->state[5] = 0x9b05688c;
    c->state[6] = 0x1f83d9ab;
    c->state[7] = 0x5be0cd19;
    c->count[0] = 0;
    c->count[1] = 0;
}

static void sha256_block(struct sha256_ctx *c, const unsigned char *p) {
    unsigned w[64], a, b, cc, d, e, f, g, h, i;

    for (i = 0; i < 16; i++)
        w[i] = ((unsigned)p[i * 4] << 24) | ((unsigned)p[i * 4 + 1] << 16) |
               ((unsigned)p[i * 4 + 2] << 8) | (unsigned)p[i * 4 + 3];
    for (i = 16; i < 64; i++) {
        unsigned s0 = sha256_rotr(w[i - 15], 7) ^ sha256_rotr(w[i - 15], 18) ^ (w[i - 15] >> 3);
        unsigned s1 = sha256_rotr(w[i - 2], 17) ^ sha256_rotr(w[i - 2], 19) ^ (w[i - 2] >> 10);
        w[i] = w[i - 16] + s0 + w[i - 7] + s1;
    }

    a = c->state[0]; b = c->state[1]; cc = c->state[2]; d = c->state[3];
    e = c->state[4]; f = c->state[5]; g = c->state[6]; h = c->state[7];

    for (i = 0; i < 64; i++) {
        unsigned S1 = sha256_rotr(e, 6) ^ sha256_rotr(e, 11) ^ sha256_rotr(e, 25);
        unsigned ch = (e & f) ^ (~e & g);
        unsigned tmp1 = h + S1 + ch + sha256_k[i] + w[i];
        unsigned S0 = sha256_rotr(a, 2) ^ sha256_rotr(a, 13) ^ sha256_rotr(a, 22);
        unsigned maj = (a & b) ^ (a & cc) ^ (b & cc);
        unsigned tmp2 = S0 + maj;
        h = g; g = f; f = e; e = d + tmp1;
        d = cc; cc = b; b = a; a = tmp1 + tmp2;
    }

    c->state[0] += a; c->state[1] += b; c->state[2] += cc; c->state[3] += d;
    c->state[4] += e; c->state[5] += f; c->state[6] += g; c->state[7] += h;
}

void sha256_update(struct sha256_ctx *c, const unsigned char *data, unsigned len) {
    unsigned idx = (c->count[0] >> 3) & 63;
    c->count[0] += len << 3;
    if (c->count[0] < (len << 3)) c->count[1]++;
    c->count[1] += len >> 29;

    if (idx) {
        unsigned fill = 64 - idx;
        if (len < fill) {
            TLS_MEMCPY(c->buf + idx, data, len);
            return;
        }
        TLS_MEMCPY(c->buf + idx, data, fill);
        sha256_block(c, c->buf);
        data += fill;
        len -= fill;
    }
    while (len >= 64) {
        sha256_block(c, data);
        data += 64;
        len -= 64;
    }
    if (len) TLS_MEMCPY(c->buf, data, len);
}

void sha256_final(struct sha256_ctx *c, unsigned char out[32]) {
    unsigned char pad[72];
    unsigned idx = (c->count[0] >> 3) & 63;
    unsigned padlen = (idx < 56) ? (56 - idx) : (120 - idx);
    unsigned long long bits = ((unsigned long long)c->count[1] << 32) | c->count[0];
    unsigned i;

    TLS_MEMSET(pad, 0, sizeof(pad));
    pad[0] = 0x80;
    for (i = 0; i < 8; i++)
        pad[padlen + i] = (unsigned char)(bits >> (56 - i * 8));
    sha256_update(c, pad, padlen + 8);
    for (i = 0; i < 8; i++)
        out[i * 4]     = (unsigned char)(c->state[i] >> 24);
    for (i = 0; i < 8; i++) {
        out[i * 4 + 1] = (unsigned char)(c->state[i] >> 16);
        out[i * 4 + 2] = (unsigned char)(c->state[i] >> 8);
        out[i * 4 + 3] = (unsigned char)(c->state[i]);
    }
}

void sha256(const unsigned char *data, unsigned len, unsigned char out[32]) {
    struct sha256_ctx c;
    sha256_init(&c);
    sha256_update(&c, data, len);
    sha256_final(&c, out);
}

/* ========== HMAC-SHA256 ========== */

void hmac_sha256(const unsigned char *key, unsigned klen,
                 const unsigned char *data, unsigned dlen,
                 unsigned char out[32]) {
    unsigned char k[64], ipad[64], opad[64], inner[32];
    struct sha256_ctx c;
    unsigned i;

    TLS_MEMSET(k, 0, 64);
    if (klen > 64) {
        sha256(key, klen, k);
    } else {
        TLS_MEMCPY(k, key, klen);
    }
    for (i = 0; i < 64; i++) {
        ipad[i] = k[i] ^ 0x36;
        opad[i] = k[i] ^ 0x5c;
    }
    sha256_init(&c);
    sha256_update(&c, ipad, 64);
    sha256_update(&c, data, dlen);
    sha256_final(&c, inner);

    sha256_init(&c);
    sha256_update(&c, opad, 64);
    sha256_update(&c, inner, 32);
    sha256_final(&c, out);
}

/* ========== TLS 1.2 PRF (P_SHA256) ========== */

static void p_hash(const unsigned char *secret, unsigned secret_len,
                   const unsigned char *seed, unsigned seed_len,
                   unsigned char *out, unsigned out_len) {
    unsigned char a[32], b[64], aseed[32 + 128];
    unsigned produced = 0;

    /* A(1) = HMAC(secret, seed) */
    hmac_sha256(secret, secret_len, seed, seed_len, a);

    while (produced < out_len) {
        unsigned take;
        TLS_MEMCPY(aseed, a, 32);
        TLS_MEMCPY(aseed + 32, seed, seed_len);
        hmac_sha256(secret, secret_len, aseed, 32 + seed_len, b);
        /* A(i+1) = HMAC(secret, A(i)) */
        hmac_sha256(secret, secret_len, a, 32, a);
        take = out_len - produced;
        if (take > 32) take = 32;
        TLS_MEMCPY(out + produced, b, take);
        produced += take;
    }
}

void tls_prf(const unsigned char *secret, unsigned secret_len,
             const char *label, const unsigned char *seed, unsigned seed_len,
             unsigned char *out, unsigned out_len) {
    unsigned char lseed[128];
    unsigned llen = (unsigned)TLS_STRLEN(label);
    if (llen > 64) llen = 64;
    TLS_MEMCPY(lseed, label, llen);
    TLS_MEMCPY(lseed + llen, seed, seed_len);
    p_hash(secret, secret_len, lseed, llen + seed_len, out, out_len);
}

/* ========== AES-128 (encrypt only, T-table) ========== */

static const unsigned char aes_sbox[256] = {
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b,
    0xfe, 0xd7, 0xab, 0x76, 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
    0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, 0xb7, 0xfd, 0x93, 0x26,
    0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2,
    0xeb, 0x27, 0xb2, 0x75, 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
    0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, 0x53, 0xd1, 0x00, 0xed,
    0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f,
    0x50, 0x3c, 0x9f, 0xa8, 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
    0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, 0xcd, 0x0c, 0x13, 0xec,
    0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14,
    0xde, 0x5e, 0x0b, 0xdb, 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
    0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, 0xe7, 0xc8, 0x37, 0x6d,
    0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f,
    0x4b, 0xbd, 0x8b, 0x8a, 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
    0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, 0xe1, 0xf8, 0x98, 0x11,
    0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f,
    0xb0, 0x54, 0xbb, 0x16
};

static const unsigned char aes_rcon[11] = {
    0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36
};

static unsigned aes_xtime(unsigned x) {
    unsigned t = (x << 1) & 255;
    return (x & 0x80) ? (t ^ 0x1b) : t;
}

static void aes_key_expand(const unsigned char key[16], unsigned rk[44]) {
    unsigned i;
    for (i = 0; i < 4; i++)
        rk[i] = ((unsigned)key[4 * i] << 24) | ((unsigned)key[4 * i + 1] << 16) |
                ((unsigned)key[4 * i + 2] << 8) | (unsigned)key[4 * i + 3];
    for (i = 4; i < 44; i++) {
        unsigned t = rk[i - 1];
        if ((i & 3) == 0) {
            t = ((unsigned)aes_sbox[(t >> 16) & 255] << 24) |
                ((unsigned)aes_sbox[(t >> 8) & 255] << 16) |
                ((unsigned)aes_sbox[t & 255] << 8) |
                (unsigned)aes_sbox[(t >> 24) & 255];
            t ^= (unsigned)aes_rcon[i / 4] << 24;
        }
        rk[i] = rk[i - 4] ^ t;
    }
}

static void aes_mixcol(unsigned a0, unsigned a1, unsigned a2, unsigned a3,
                       unsigned *out) {
    unsigned t0 = aes_xtime(a0), t1 = aes_xtime(a1),
             t2 = aes_xtime(a2), t3 = aes_xtime(a3);
    out[0] = t0 ^ t1 ^ a1 ^ a2 ^ a3;
    out[1] = a0 ^ t1 ^ t2 ^ a2 ^ a3;
    out[2] = a0 ^ a1 ^ t2 ^ t3 ^ a3;
    out[3] = t0 ^ a0 ^ a1 ^ a2 ^ t3;
}

void aes128_encrypt_block(const unsigned char key[16],
                          const unsigned char in[16], unsigned char out[16]) {
    unsigned rk[44], s[4], t[4], sub[4];
    unsigned round, i;

    aes_key_expand(key, rk);
    for (i = 0; i < 4; i++)
        s[i] = ((unsigned)in[4 * i] << 24) | ((unsigned)in[4 * i + 1] << 16) |
               ((unsigned)in[4 * i + 2] << 8) | (unsigned)in[4 * i + 3];

    for (i = 0; i < 4; i++) s[i] ^= rk[i];
    for (round = 1; round <= 9; round++) {
        for (i = 0; i < 4; i++)
            sub[i] = ((unsigned)aes_sbox[(s[i] >> 24) & 255] << 24) |
                     ((unsigned)aes_sbox[(s[i] >> 16) & 255] << 16) |
                     ((unsigned)aes_sbox[(s[i] >> 8) & 255] << 8) |
                     (unsigned)aes_sbox[s[i] & 255];
        for (i = 0; i < 4; i++) {
            /* ShiftRows then MixColumns: output column i takes bytes from
             * subbed columns i (row 0), i+1 (row 1), i+2 (row 2), i+3 (row 3). */
            unsigned a0 = (sub[i] >> 24) & 255;
            unsigned a1 = (sub[(i + 1) & 3] >> 16) & 255;
            unsigned a2 = (sub[(i + 2) & 3] >> 8) & 255;
            unsigned a3 = sub[(i + 3) & 3] & 255;
            unsigned mc[4];
            aes_mixcol(a0, a1, a2, a3, mc);
            s[i] = (mc[0] << 24) | (mc[1] << 16) | (mc[2] << 8) | mc[3];
            s[i] ^= rk[round * 4 + i];
        }
    }
    /* Final round: SubBytes + ShiftRows, no MixColumns */
    for (i = 0; i < 4; i++)
        t[i] = ((unsigned)aes_sbox[(s[i] >> 24) & 255] << 24) |
               ((unsigned)aes_sbox[(s[i] >> 16) & 255] << 16) |
               ((unsigned)aes_sbox[(s[i] >> 8) & 255] << 8) |
               (unsigned)aes_sbox[s[i] & 255];
    for (i = 0; i < 4; i++) {
        s[i] = ((t[i] >> 24) & 255) << 24;
        s[i] |= ((t[(i + 1) & 3] >> 16) & 255) << 16;
        s[i] |= ((t[(i + 2) & 3] >> 8) & 255) << 8;
        s[i] |= t[(i + 3) & 3] & 255;
        s[i] ^= rk[40 + i];
    }
    for (i = 0; i < 4; i++) {
        out[4 * i]     = (unsigned char)(s[i] >> 24);
        out[4 * i + 1] = (unsigned char)(s[i] >> 16);
        out[4 * i + 2] = (unsigned char)(s[i] >> 8);
        out[4 * i + 3] = (unsigned char)s[i];
    }
}

/* ========== AES-128-GCM ========== */

typedef struct {
    unsigned long long lo;
    unsigned long long hi;
} gf128;

static gf128 gf_shift_right(gf128 v) {
    gf128 r;
    unsigned long long mask = 0 - (v.lo & 1);
    r.lo = (v.lo >> 1) | (v.hi << 63);
    /* reduction: x^128 = x^7 + x^2 + x + 1 -> 0xE1 << 120, the top byte
     * of the low word (hi holds bits 64..127, lo bits 0..63). Masked in,
     * so the shift never branches on key bits. */
    r.hi = (v.hi >> 1) ^ (0xE100000000000000ULL & mask);
    return r;
}

/* z = z * h, in GF(2^128), MSB-first. Branches on z bits (public:
 * AAD/ciphertext), never on h bits (secret). */
static gf128 gf_mul(gf128 z, gf128 h) {
    gf128 out;
    int i;
    out.lo = 0;
    out.hi = 0;
    for (i = 0; i < 128; i++) {
        if (z.hi >> 63) {
            out.lo ^= h.lo;
            out.hi ^= h.hi;
        }
        z.hi = (z.hi << 1) | (z.lo >> 63);
        z.lo <<= 1;
        h = gf_shift_right(h);
    }
    return out;
}

static gf128 gf_put(const unsigned char *p) {
    gf128 v;
    int i;
    v.hi = 0;
    v.lo = 0;
    for (i = 0; i < 8; i++) v.hi = (v.hi << 8) | p[i];
    for (i = 8; i < 16; i++) v.lo = (v.lo << 8) | p[i];
    return v;
}

static gf128 ghash_blocks(gf128 z, gf128 h, const unsigned char *data, unsigned len) {
    while (len >= 16) {
        gf128 b = gf_put(data);
        z.lo ^= b.lo;
        z.hi ^= b.hi;
        z = gf_mul(z, h);
        data += 16;
        len -= 16;
    }
    if (len > 0) {
        unsigned char pad[16];
        gf128 b;
        TLS_MEMSET(pad, 0, 16);
        TLS_MEMCPY(pad, data, len);
        b = gf_put(pad);
        z.lo ^= b.lo;
        z.hi ^= b.hi;
        z = gf_mul(z, h);
    }
    return z;
}

/* Compute GCM tag for aad || ct (ct already ciphertext). */
static void gcm_tag_core(const unsigned char key[16],
                         const unsigned char nonce[12],
                         const unsigned char *aad, unsigned aad_len,
                         const unsigned char *ct, unsigned ct_len,
                         unsigned char tag[16]) {
    unsigned char j0[16], ek0[16], hbuf[16], lenb[16];
    gf128 h, s;
    int i;

    TLS_MEMSET(j0, 0, 16);
    TLS_MEMCPY(j0, nonce, 12);
    j0[15] = 1;
    aes128_encrypt_block(key, j0, ek0);
    TLS_MEMSET(hbuf, 0, 16);
    aes128_encrypt_block(key, hbuf, hbuf);
    h = gf_put(hbuf);

    s.lo = 0;
    s.hi = 0;
    s = ghash_blocks(s, h, aad, aad_len);
    s = ghash_blocks(s, h, ct, ct_len);
    TLS_MEMSET(lenb, 0, 16);
    for (i = 0; i < 8; i++) {
        lenb[i] = (unsigned char)(((unsigned long long)aad_len * 8) >> (56 - i * 8));
        lenb[8 + i] = (unsigned char)(((unsigned long long)ct_len * 8) >> (56 - i * 8));
    }
    {
        gf128 b = gf_put(lenb);
        s.lo ^= b.lo;
        s.hi ^= b.hi;
        s = gf_mul(s, h);
    }
    /* E(J0) ^ S */
    {
        unsigned char sj[16];
        for (i = 0; i < 8; i++) {
            sj[i] = (unsigned char)(s.hi >> (56 - i * 8));
            sj[8 + i] = (unsigned char)(s.lo >> (56 - i * 8));
        }
        for (i = 0; i < 16; i++) tag[i] = sj[i] ^ ek0[i];
    }
}

static void gcm_ctr_core(const unsigned char key[16],
                         const unsigned char nonce[12],
                         const unsigned char *in, unsigned char *out, unsigned len) {
    unsigned char blk[16], crypt[16];
    unsigned long long ctr = 2;
    unsigned off = 0;
    int i;
    while (off < len) {
        unsigned take = len - off;
        TLS_MEMCPY(blk, nonce, 12);
        blk[12] = (unsigned char)(ctr >> 24);
        blk[13] = (unsigned char)(ctr >> 16);
        blk[14] = (unsigned char)(ctr >> 8);
        blk[15] = (unsigned char)(ctr);
        aes128_encrypt_block(key, blk, crypt);
        if (take > 16) take = 16;
        for (i = 0; i < (int)take; i++) out[off + i] = in[off + i] ^ crypt[i];
        off += take;
        ctr++;
    }
}

/* TLS nonce: 4-byte implicit salt || 8-byte sequence number. */
static void tls_nonce(const unsigned char salt[4], unsigned long long seq,
                      unsigned char nonce[12]) {
    int i;
    TLS_MEMCPY(nonce, salt, 4);
    for (i = 0; i < 8; i++) nonce[4 + i] = (unsigned char)(seq >> (56 - i * 8));
}

static void gcm_tag(const unsigned char key[16], const unsigned char salt[4],
                    unsigned long long seq,
                    const unsigned char *aad, unsigned aad_len,
                    const unsigned char *ct, unsigned ct_len,
                    unsigned char tag[16]) {
    unsigned char nonce[12];
    tls_nonce(salt, seq, nonce);
    gcm_tag_core(key, nonce, aad, aad_len, ct, ct_len, tag);
}

static void gcm_ctr(const unsigned char key[16], const unsigned char salt[4],
                    unsigned long long seq,
                    const unsigned char *in, unsigned char *out, unsigned len) {
    unsigned char nonce[12];
    tls_nonce(salt, seq, nonce);
    gcm_ctr_core(key, nonce, in, out, len);
}

int aes128_gcm_seal(const unsigned char key[16],
                    const unsigned char salt[4],
                    unsigned long long seq,
                    const unsigned char *aad, unsigned aad_len,
                    const unsigned char *pt, unsigned pt_len,
                    unsigned char *ct, unsigned char tag[16]) {
    if (pt_len > TLS_REC_MAX) return -1;
    gcm_ctr(key, salt, seq, pt, ct, pt_len);
    gcm_tag(key, salt, seq, aad, aad_len, ct, pt_len, tag);
    return 0;
}

int aes128_gcm_open(const unsigned char key[16],
                    const unsigned char salt[4],
                    unsigned long long seq,
                    const unsigned char *aad, unsigned aad_len,
                    const unsigned char *ct, unsigned ct_len,
                    const unsigned char tag[16],
                    unsigned char *pt) {
    unsigned char want[16];
    unsigned char diff = 0;
    int i;
    if (ct_len > TLS_REC_MAX) return -1;
    gcm_tag(key, salt, seq, aad, aad_len, ct, ct_len, want);
    for (i = 0; i < 16; i++) diff |= want[i] ^ tag[i];
    if (diff) return -1;
    gcm_ctr(key, salt, seq, ct, pt, ct_len);
    return 0;
}

int aes128_gcm_seal_core(const unsigned char key[16],
                         const unsigned char nonce[12],
                         const unsigned char *aad, unsigned aad_len,
                         const unsigned char *pt, unsigned pt_len,
                         unsigned char *ct, unsigned char tag[16]) {
    if (pt_len > TLS_REC_MAX) return -1;
    gcm_ctr_core(key, nonce, pt, ct, pt_len);
    gcm_tag_core(key, nonce, aad, aad_len, ct, pt_len, tag);
    return 0;
}

int aes128_gcm_open_core(const unsigned char key[16],
                         const unsigned char nonce[12],
                         const unsigned char *aad, unsigned aad_len,
                         const unsigned char *ct, unsigned ct_len,
                         const unsigned char tag[16],
                         unsigned char *pt) {
    unsigned char want[16];
    unsigned char diff = 0;
    int i;
    if (ct_len > TLS_REC_MAX) return -1;
    gcm_tag_core(key, nonce, aad, aad_len, ct, ct_len, want);
    for (i = 0; i < 16; i++) diff |= want[i] ^ tag[i];
    if (diff) return -1;
    gcm_ctr_core(key, nonce, ct, pt, ct_len);
    return 0;
}

/* ========== Big integers (32-bit limbs, little-endian) ========== */

#define TLS_BN_WORDS 128   /* 4096 bits */

static void bn_zero(unsigned *a, int nw) {
    int i;
    for (i = 0; i < nw; i++) a[i] = 0;
}

static int bn_is_zero(const unsigned *a, int nw) {
    int i;
    unsigned v = 0;
    for (i = 0; i < nw; i++) v |= a[i];
    return v == 0;
}

static int bn_cmp(const unsigned *a, const unsigned *b, int nw) {
    int i;
    for (i = nw - 1; i >= 0; i--) {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
    }
    return 0;
}

/* r = a + b; returns carry out. */
static unsigned bn_add(const unsigned *a, const unsigned *b, unsigned *r, int nw) {
    unsigned long long carry = 0;
    int i;
    for (i = 0; i < nw; i++) {
        unsigned long long t = (unsigned long long)a[i] + b[i] + carry;
        r[i] = (unsigned)t;
        carry = t >> 32;
    }
    return (unsigned)carry;
}

/* r = a - b; a must be >= b; returns borrow (0 = fine). */
static unsigned bn_sub(const unsigned *a, const unsigned *b, unsigned *r, int nw) {
    unsigned long long borrow = 0;
    int i;
    for (i = 0; i < nw; i++) {
        unsigned long long t = (unsigned long long)a[i] - b[i] - borrow;
        r[i] = (unsigned)t;
        borrow = (t >> 32) & 1;
    }
    return (unsigned)borrow;
}

/* r = 2a mod n, for a < n. v = 2^(32nw) mod n = 2^(32nw) - n (the
 * Montgomery "one"): 2a + carry means 2a - 2^(32nw) + v = 2a - n < n. */
static void bn_dbl_mod(const unsigned *a, const unsigned *n, const unsigned *v,
                       unsigned *r, int nw) {
    if (bn_add(a, a, r, nw)) {
        bn_add(r, v, r, nw);
    } else if (bn_cmp(r, n, nw) >= 0) {
        bn_sub(r, n, r, nw);
    }
}

/* Montgomery multiplication.
 * n is odd, n0inv = -n^(-1) mod 2^32. r = a*b*R^-1 mod n, R = 2^(32nw).
 * a, b < n. */
static void bn_mont_mul(const unsigned *a, const unsigned *b, const unsigned *n,
                        unsigned n0inv, int nw, unsigned *r) {
    /* CIOS needs nw + 2 temporaries: t[nw] holds the propagated carry
     * and t[nw + 1] its high word. */
    unsigned t[TLS_BN_WORDS + 2];
    int i, j;
    for (i = 0; i <= nw; i++) t[i] = 0;
    for (i = 0; i < nw; i++) {
        unsigned long long carry = 0;
        unsigned m;
        unsigned long long s;
        for (j = 0; j < nw; j++) {
            unsigned long long v = (unsigned long long)a[j] * b[i] + t[j] + carry;
            t[j] = (unsigned)v;
            carry = v >> 32;
        }
        s = (unsigned long long)t[nw] + carry;
        t[nw] = (unsigned)s;
        t[nw + 1] = (unsigned)(s >> 32);
        m = t[0] * n0inv;
        s = (unsigned long long)t[0] + (unsigned long long)m * n[0];
        carry = s >> 32;
        for (j = 1; j < nw; j++) {
            unsigned long long v = (unsigned long long)m * n[j] + t[j] + carry;
            t[j - 1] = (unsigned)v;
            carry = v >> 32;
        }
        s = (unsigned long long)t[nw] + carry;
        t[nw - 1] = (unsigned)s;
        t[nw] = t[nw + 1] + (unsigned)(s >> 32);
    }
    if (t[nw] || bn_cmp(t, n, nw) >= 0) {
        bn_sub(t, n, r, nw);
    } else {
        for (i = 0; i < nw; i++) r[i] = t[i];
    }
}

/* -n^(-1) mod 2^32 via Newton iteration (n0 must be odd). */
static unsigned bn_mont_n0inv(unsigned n0) {
    unsigned inv = 1;
    int i;
    for (i = 0; i < 5; i++) inv *= 2 - n0 * inv;
    return 0 - inv;
}

/* R^2 mod n, R = 2^(32nw): 64*nw doublings from 1. */
static void bn_mont_r2(const unsigned *n, const unsigned *v, int nw,
                       unsigned *r2) {
    unsigned x[TLS_BN_WORDS];
    int i;
    bn_zero(x, nw);
    x[0] = 1;
    for (i = 0; i < 64 * nw; i++) bn_dbl_mod(x, n, v, x, nw);
    for (i = 0; i < nw; i++) r2[i] = x[i];
}

/* ========== Montgomery context over a fixed modulus ========== */

struct mont_ctx {
    int      nw;
    unsigned n[TLS_BN_WORDS];
    unsigned r2[TLS_BN_WORDS];
    unsigned one[TLS_BN_WORDS];
    unsigned n0inv;
};

static void bn_from_be(const unsigned char *bytes, unsigned len,
                       unsigned *out, int nw) {
    int i;
    bn_zero(out, nw);
    for (i = 0; i < (int)len && i < nw * 4; i++)
        out[(len - 1 - i) / 4] |= (unsigned)bytes[i] << (8 * ((len - 1 - i) & 3));
}

static void bn_to_be(const unsigned *a, unsigned char *out, unsigned len) {
    int i;
    for (i = 0; i < (int)len; i++)
        out[i] = (unsigned char)(a[(len - 1 - i) / 4] >> (8 * ((len - 1 - i) & 3)));
}

static void mont_init(struct mont_ctx *m, const unsigned char *p_bytes,
                      unsigned p_len) {
    unsigned zero[TLS_BN_WORDS];
    m->nw = (int)((p_len + 3) / 4);
    bn_from_be(p_bytes, p_len, m->n, m->nw);
    m->n0inv = bn_mont_n0inv(m->n[0]);
    /* one = R mod n = 2^(32nw) - n (n has its top bit set, so 2^(32nw) < 2n) */
    bn_zero(zero, m->nw);
    bn_sub(zero, m->n, m->one, m->nw);
    bn_mont_r2(m->n, m->one, m->nw, m->r2);
}

static void mont_to(struct mont_ctx *m, const unsigned *a, unsigned *r) {
    bn_mont_mul(a, m->r2, m->n, m->n0inv, m->nw, r);
}

static void mont_from(struct mont_ctx *m, const unsigned *a, unsigned *r) {
    unsigned one_int[TLS_BN_WORDS];
    bn_zero(one_int, m->nw);
    one_int[0] = 1;
    bn_mont_mul(a, one_int, m->n, m->n0inv, m->nw, r);
}

static void mont_mul(struct mont_ctx *m, const unsigned *a, const unsigned *b,
                     unsigned *r) {
    bn_mont_mul(a, b, m->n, m->n0inv, m->nw, r);
}

static void mont_sqr(struct mont_ctx *m, const unsigned *a, unsigned *r) {
    bn_mont_mul(a, a, m->n, m->n0inv, m->nw, r);
}

/* Field add/sub over the mont modulus (in Montgomery domain). The
 * carry of a+b is corrected with one = 2^(32nw) - n, and a - b < 0 is
 * p - (b - a); neither path can overflow one word. */
static void mont_add(struct mont_ctx *m, const unsigned *a, const unsigned *b,
                     unsigned *r) {
    if (bn_add(a, b, r, m->nw)) {
        bn_add(r, m->one, r, m->nw);
    } else if (bn_cmp(r, m->n, m->nw) >= 0) {
        bn_sub(r, m->n, r, m->nw);
    }
}

static void mont_sub(struct mont_ctx *m, const unsigned *a, const unsigned *b,
                     unsigned *r) {
    if (bn_cmp(a, b, m->nw) >= 0) {
        bn_sub(a, b, r, m->nw);
        return;
    }
    {
        unsigned t[TLS_BN_WORDS];
        bn_sub(m->n, b, t, m->nw);   /* p - b */
        bn_add(a, t, r, m->nw);      /* a + p - b < p */
    }
}

/* Field inverse via Fermat: a^(p-2) mod p (a in Montgomery domain;
 * the result stays in Montgomery domain). */
static void mont_inv(struct mont_ctx *m, const unsigned *a, unsigned *r) {
    unsigned base[TLS_BN_WORDS], res[TLS_BN_WORDS], t[TLS_BN_WORDS];
    unsigned e[TLS_BN_WORDS];
    int i, bit;
    unsigned long long borrow = 0;

    /* e = p - 2 */
    bn_zero(e, m->nw);
    e[0] = m->n[0] - 2;
    borrow = m->n[0] < 2 ? 1 : 0;
    for (i = 1; i < m->nw; i++) {
        unsigned long long v = (unsigned long long)m->n[i] - borrow;
        e[i] = (unsigned)v;
        borrow = (v >> 32) & 1;
    }
    for (i = 0; i < m->nw; i++) base[i] = a[i];
    for (i = 0; i < m->nw; i++) res[i] = m->one[i];
    for (bit = m->nw * 32 - 1; bit >= 0; bit--) {
        mont_sqr(m, res, t);
        if ((e[bit / 32] >> (bit & 31)) & 1) mont_mul(m, t, base, res);
        else {
            int j;
            for (j = 0; j < m->nw; j++) res[j] = t[j];
        }
    }
    for (i = 0; i < m->nw; i++) r[i] = res[i];
}

/* ========== NIST curves ========== */

static const unsigned char ec_p256_p[32] = {
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};
static const unsigned char ec_p256_b[32] = {
    0x5a, 0xc6, 0x35, 0xd8, 0xaa, 0x3a, 0x93, 0xe7,
    0xb3, 0xeb, 0xbd, 0x55, 0x76, 0x98, 0x86, 0xbc,
    0x65, 0x1d, 0x06, 0xb0, 0xcc, 0x53, 0xb0, 0xf6,
    0x3b, 0xce, 0x3c, 0x3e, 0x27, 0xd2, 0x60, 0x4b
};
static const unsigned char ec_p256_gx[32] = {
    0x6b, 0x17, 0xd1, 0xf2, 0xe1, 0x2c, 0x42, 0x47,
    0xf8, 0xbc, 0xe6, 0xe5, 0x63, 0xa4, 0x40, 0xf2,
    0x77, 0x03, 0x7d, 0x81, 0x2d, 0xeb, 0x33, 0xa0,
    0xf4, 0xa1, 0x39, 0x45, 0xd8, 0x98, 0xc2, 0x96
};
static const unsigned char ec_p256_gy[32] = {
    0x4f, 0xe3, 0x42, 0xe2, 0xfe, 0x1a, 0x7f, 0x9b,
    0x8e, 0xe7, 0xeb, 0x4a, 0x7c, 0x0f, 0x9e, 0x16,
    0x2b, 0xce, 0x33, 0x57, 0x6b, 0x31, 0x5e, 0xce,
    0xcb, 0xb6, 0x40, 0x68, 0x37, 0xbf, 0x51, 0xf5
};
static const unsigned char ec_p256_n[32] = {
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xbc, 0xe6, 0xfa, 0xad, 0xa7, 0x17, 0x9e, 0x84,
    0xf3, 0xb9, 0xca, 0xc2, 0xfc, 0x63, 0x25, 0x51
};

static const unsigned char ec_p384_p[48] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
    0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff
};
static const unsigned char ec_p384_b[48] = {
    0xb3, 0x31, 0x2f, 0xa7, 0xe2, 0x3e, 0xe7, 0xe4,
    0x98, 0x8e, 0x05, 0x6b, 0xe3, 0xf8, 0x2d, 0x19,
    0x18, 0x1d, 0x9c, 0x6e, 0xfe, 0x81, 0x41, 0x12,
    0x03, 0x14, 0x08, 0x8f, 0x50, 0x13, 0x87, 0x5a,
    0xc6, 0x56, 0x39, 0x8d, 0x8a, 0x2e, 0xd1, 0x9d,
    0x2a, 0x85, 0xc8, 0xed, 0xd3, 0xec, 0x2a, 0xef
};
static const unsigned char ec_p384_gx[48] = {
    0xaa, 0x87, 0xca, 0x22, 0xbe, 0x8b, 0x05, 0x37,
    0x8e, 0xb1, 0xc7, 0x1e, 0xf3, 0x20, 0xad, 0x74,
    0x6e, 0x1d, 0x3b, 0x62, 0x8b, 0xa7, 0x9b, 0x98,
    0x59, 0xf7, 0x41, 0xe0, 0x82, 0x54, 0x2a, 0x38,
    0x55, 0x02, 0xf2, 0x5d, 0xbf, 0x55, 0x29, 0x6c,
    0x3a, 0x54, 0x5e, 0x38, 0x72, 0x76, 0x0a, 0xb7
};
static const unsigned char ec_p384_gy[48] = {
    0x36, 0x17, 0xde, 0x4a, 0x96, 0x26, 0x2c, 0x6f,
    0x5d, 0x9e, 0x98, 0xbf, 0x92, 0x92, 0xdc, 0x29,
    0xf8, 0xf4, 0x1d, 0xbd, 0x28, 0x9a, 0x14, 0x7c,
    0xe9, 0xda, 0x31, 0x13, 0xb5, 0xf0, 0xb8, 0xc0,
    0x0a, 0x60, 0xb1, 0xce, 0x1d, 0x7e, 0x81, 0x9d,
    0x7a, 0x43, 0x1d, 0x7c, 0x90, 0xea, 0x0e, 0x5f
};
static const unsigned char ec_p384_n[48] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xc7, 0x63, 0x4d, 0x81, 0xf4, 0x37, 0x2d, 0xdf,
    0x58, 0x1a, 0x0d, 0xb2, 0x48, 0xb0, 0xa7, 0x7a,
    0xec, 0xec, 0x19, 0x6a, 0xcc, 0xc5, 0x29, 0x73
};

struct ec_curve {
    const unsigned char *p, *b, *gx, *gy, *n;
    int                  len;      /* bytes */
    struct mont_ctx      fp;       /* field arithmetic mod p */
    struct mont_ctx      fn;       /* scalar arithmetic mod n */
};

static struct ec_curve ec_p256;
static struct ec_curve ec_p384;

static void ec_init(struct ec_curve *c, const unsigned char *p,
                    const unsigned char *b, const unsigned char *gx,
                    const unsigned char *gy, const unsigned char *n,
                    int len) {
    c->p = p; c->b = b; c->gx = gx; c->gy = gy; c->n = n; c->len = len;
    mont_init(&c->fp, p, (unsigned)len);
    mont_init(&c->fn, n, (unsigned)len);
}

/* Jacobian point: three coordinates in Montgomery domain, nw words each.
 * The point at infinity has Z = 0. */
struct jpt {
    unsigned x[TLS_BN_WORDS];
    unsigned y[TLS_BN_WORDS];
    unsigned z[TLS_BN_WORDS];
};

static int jpt_is_inf(const struct jpt *p, int nw) {
    return bn_is_zero(p->z, nw);
}

static void jpt_set_inf(struct jpt *p, int nw) {
    bn_zero(p->x, nw);
    bn_zero(p->y, nw);
    bn_zero(p->z, nw);
}

static void jpt_copy(struct jpt *d, const struct jpt *s, int nw) {
    int i;
    for (i = 0; i < nw; i++) {
        d->x[i] = s->x[i];
        d->y[i] = s->y[i];
        d->z[i] = s->z[i];
    }
}

/* Constant-time swap of two points on a 0/~0 mask. */
static void jpt_cswap(struct jpt *a, struct jpt *b, unsigned mask, int nw) {
    int i;
    for (i = 0; i < nw; i++) {
        unsigned t;
        t = (a->x[i] ^ b->x[i]) & mask; a->x[i] ^= t; b->x[i] ^= t;
        t = (a->y[i] ^ b->y[i]) & mask; a->y[i] ^= t; b->y[i] ^= t;
        t = (a->z[i] ^ b->z[i]) & mask; a->z[i] ^= t; b->z[i] ^= t;
    }
}

/* P3 = 2 * P1 (a = p - 3: E = 3(A - Z1^4)). */
static void jpt_dbl(struct ec_curve *c, const struct jpt *p1, struct jpt *p3) {
    struct mont_ctx *m = &c->fp;
    int nw = m->nw;
    unsigned A[TLS_BN_WORDS], B[TLS_BN_WORDS], C[TLS_BN_WORDS];
    unsigned D[TLS_BN_WORDS], E[TLS_BN_WORDS], F[TLS_BN_WORDS];
    unsigned t[TLS_BN_WORDS], t2[TLS_BN_WORDS];
    unsigned ZZ[TLS_BN_WORDS], YZ[TLS_BN_WORDS];

    if (jpt_is_inf(p1, nw) || bn_is_zero(p1->y, nw)) {
        jpt_set_inf(p3, nw);
        return;
    }
    mont_sqr(m, p1->x, A);
    mont_sqr(m, p1->y, B);
    mont_sqr(m, B, C);
    mont_add(m, p1->x, B, t);
    mont_sqr(m, t, t2);
    mont_sub(m, t2, A, t);
    mont_sub(m, t, C, t);
    mont_add(m, t, t, D);
    /* E = 3(A - Z1^4) for a = p - 3 */
    mont_sqr(m, p1->z, ZZ);
    mont_sqr(m, ZZ, t);
    mont_sub(m, A, t, t);
    mont_add(m, t, t, E);
    mont_add(m, E, t, E);
    mont_sqr(m, E, F);
    mont_add(m, D, D, t);          /* 2D */
    mont_sub(m, F, t, p3->x);      /* X3 = F - 2D */
    mont_sub(m, D, p3->x, t);
    mont_mul(m, E, t, t2);
    mont_add(m, C, C, t);
    mont_add(m, t, t, t);
    mont_add(m, t, t, t);          /* 8C */
    mont_sub(m, t2, t, p3->y);     /* Y3 = E(D-X3) - 8C */
    mont_mul(m, p1->y, p1->z, YZ);
    mont_add(m, YZ, YZ, p3->z);    /* Z3 = 2YZ */
}

/* P3 = P1 + P2 (generic Jacobian add). */
static void jpt_add(struct ec_curve *c, const struct jpt *p1, const struct jpt *p2,
                    struct jpt *p3) {
    struct mont_ctx *m = &c->fp;
    int nw = m->nw;
    unsigned Z1Z1[TLS_BN_WORDS], Z2Z2[TLS_BN_WORDS], U1[TLS_BN_WORDS], U2[TLS_BN_WORDS];
    unsigned S1[TLS_BN_WORDS], S2[TLS_BN_WORDS], H[TLS_BN_WORDS], R[TLS_BN_WORDS];
    unsigned H2[TLS_BN_WORDS], H3[TLS_BN_WORDS], U1H2[TLS_BN_WORDS];
    unsigned t[TLS_BN_WORDS], t2[TLS_BN_WORDS];

    if (jpt_is_inf(p1, nw)) { jpt_copy(p3, p2, nw); return; }
    if (jpt_is_inf(p2, nw)) { jpt_copy(p3, p1, nw); return; }

    mont_sqr(m, p1->z, Z1Z1);
    mont_sqr(m, p2->z, Z2Z2);
    mont_mul(m, p1->x, Z2Z2, U1);
    mont_mul(m, p2->x, Z1Z1, U2);
    mont_mul(m, p2->z, Z2Z2, t);      /* Z2^3 */
    mont_mul(m, p1->y, t, S1);        /* S1 = Y1*Z2^3 */
    mont_mul(m, p1->z, Z1Z1, t);      /* Z1^3 */
    mont_mul(m, p2->y, t, S2);        /* S2 = Y2*Z1^3 */
    mont_sub(m, U2, U1, H);
    mont_sub(m, S2, S1, R);
    if (bn_is_zero(H, nw)) {
        if (bn_is_zero(R, nw)) jpt_dbl(c, p1, p3);
        else jpt_set_inf(p3, nw);
        return;
    }
    mont_sqr(m, H, H2);
    mont_mul(m, H, H2, H3);
    mont_mul(m, U1, H2, U1H2);
    mont_sqr(m, R, t);
    mont_sub(m, t, H3, t2);
    mont_add(m, U1H2, U1H2, t);
    mont_sub(m, t2, t, p3->x);     /* X3 = R^2 - H3 - 2U1H2 */
    mont_sub(m, U1H2, p3->x, t);
    mont_mul(m, R, t, t2);
    mont_mul(m, S1, H3, t);
    mont_sub(m, t2, t, p3->y);     /* Y3 = R(U1H2-X3) - S1H3 */
    mont_mul(m, p1->z, p2->z, t);
    mont_mul(m, t, H, p3->z);
}

/* Constant-iteration scalar multiplication: the classic ladder.
 * Fixed iteration count, no table lookups indexed by secret bits. */
static void jpt_scalar_mult(struct ec_curve *c, const struct jpt *base,
                            const unsigned char *scalar, struct jpt *out) {
    struct jpt r0, r1;
    int nw = c->fp.nw;
    int bits = c->len * 8;
    int i;

    jpt_set_inf(&r0, nw);
    jpt_copy(&r1, base, nw);
    for (i = bits - 1; i >= 0; i--) {
        /* scalar is big-endian: bit k of the walk (k = bits-1-i) lives at
         * scalar[k/8], shift 7 - k%8 = i%8 */
        unsigned bit = (scalar[(bits - 1 - i) / 8] >> (i & 7)) & 1;
        unsigned mask = 0 - bit;
        struct jpt t0, t1;
        jpt_cswap(&r0, &r1, mask, nw);
        jpt_add(c, &r0, &r1, &t1);
        jpt_dbl(c, &r0, &t0);
        jpt_cswap(&t0, &t1, mask, nw);
        jpt_copy(&r0, &t0, nw);
        jpt_copy(&r1, &t1, nw);
    }
    jpt_copy(out, &r0, nw);
}

/* Affine from Jacobian: x = X/Z^2, y = Y/Z^3. Bytes out are big-endian.
 * y_out may be NULL when only the x coordinate is wanted. */
static void jpt_to_affine(struct ec_curve *c, const struct jpt *p,
                          unsigned char *x_out, unsigned char *y_out) {
    struct mont_ctx *m = &c->fp;
    int nw = m->nw;
    unsigned zinv[TLS_BN_WORDS], z2[TLS_BN_WORDS], z3[TLS_BN_WORDS];
    unsigned ax[TLS_BN_WORDS], ay[TLS_BN_WORDS];

    if (jpt_is_inf(p, nw)) {
        TLS_MEMSET(x_out, 0, (unsigned)c->len);
        if (y_out) TLS_MEMSET(y_out, 0, (unsigned)c->len);
        return;
    }
    mont_inv(m, p->z, zinv);
    mont_sqr(m, zinv, z2);
    mont_mul(m, zinv, z2, z3);
    mont_mul(m, p->x, z2, ax);
    mont_mul(m, p->y, z3, ay);
    mont_from(m, ax, ax);
    mont_from(m, ay, ay);
    bn_to_be(ax, x_out, (unsigned)c->len);
    if (y_out) bn_to_be(ay, y_out, (unsigned)c->len);
}

/* Affine from bytes with on-curve validation. Returns 0 when the point
 * is valid and not the point at infinity. */
static int jpt_from_affine(struct ec_curve *c, const unsigned char *x_bytes,
                           const unsigned char *y_bytes, struct jpt *out) {
    struct mont_ctx *m = &c->fp;
    int nw = m->nw;
    unsigned X[TLS_BN_WORDS], Y[TLS_BN_WORDS];
    unsigned lhs[TLS_BN_WORDS], rhs[TLS_BN_WORDS], t[TLS_BN_WORDS];
    unsigned B[TLS_BN_WORDS];
    int i;

    bn_from_be(x_bytes, (unsigned)c->len, X, nw);
    bn_from_be(y_bytes, (unsigned)c->len, Y, nw);
    if (bn_cmp(X, m->n, nw) >= 0 || bn_cmp(Y, m->n, nw) >= 0) return -1;
    if (bn_is_zero(X, nw) && bn_is_zero(Y, nw)) return -1;

    /* y^2 == x^3 - 3x + b  (all in the field, computed over the mont
     * domain: convert once) */
    mont_to(m, X, X);
    mont_to(m, Y, Y);
    bn_from_be(c->b, (unsigned)c->len, B, nw);
    mont_to(m, B, B);
    mont_sqr(m, Y, lhs);
    mont_sqr(m, X, t);
    mont_mul(m, t, X, rhs);
    /* -3x: 3X in mont domain, then subtract */
    {
        unsigned three_m[TLS_BN_WORDS];
        bn_zero(three_m, nw);
        three_m[0] = 3;
        mont_to(m, three_m, three_m);
        mont_mul(m, three_m, X, t);
        mont_sub(m, rhs, t, rhs);
    }
    mont_add(m, rhs, B, rhs);
    for (i = 0; i < nw; i++) {
        if (lhs[i] != rhs[i]) return -1;
    }
    for (i = 0; i < nw; i++) {
        out->x[i] = X[i];
        out->y[i] = Y[i];
        out->z[i] = m->one[i];
    }
    return 0;
}

static struct ec_curve *ec_curve_by_id(int curve) {
    return curve == 0 ? &ec_p256 : &ec_p384;
}

static void ec_boot(void) {
    static int done = 0;
    if (done) return;
    done = 1;
    ec_init(&ec_p256, ec_p256_p, ec_p256_b, ec_p256_gx, ec_p256_gy, ec_p256_n, 32);
    ec_init(&ec_p384, ec_p384_p, ec_p384_b, ec_p384_gx, ec_p384_gy, ec_p384_n, 48);
}

int p256_scalar_mult(const unsigned char scalar[32],
                     const unsigned char qx[32], const unsigned char qy[32],
                     unsigned char rx[32], unsigned char ry[32]) {
    struct ec_curve *c;
    struct jpt base, out;
    ec_boot();
    c = &ec_p256;
    if (jpt_from_affine(c, qx, qy, &base) != 0) return -1;
    jpt_scalar_mult(c, &base, scalar, &out);
    jpt_to_affine(c, &out, rx, ry);
    return 0;
}

int p384_scalar_mult(const unsigned char scalar[48],
                     const unsigned char qx[48], const unsigned char qy[48],
                     unsigned char rx[48], unsigned char ry[48]) {
    struct ec_curve *c;
    struct jpt base, out;
    ec_boot();
    c = &ec_p384;
    if (jpt_from_affine(c, qx, qy, &base) != 0) return -1;
    jpt_scalar_mult(c, &base, scalar, &out);
    jpt_to_affine(c, &out, rx, ry);
    return 0;
}

int p256_ecdh(const unsigned char priv[32],
              const unsigned char peer_x[32], const unsigned char peer_y[32],
              unsigned char z[32]) {
    struct ec_curve *c;
    struct jpt base, out;
    ec_boot();
    c = &ec_p256;
    if (jpt_from_affine(c, peer_x, peer_y, &base) != 0) return -1;
    jpt_scalar_mult(c, &base, priv, &out);
    jpt_to_affine(c, &out, z, 0);
    return 0;
}

/* ========== ECDSA verify ========== */

static int der_parse_sig(const unsigned char *sig, unsigned sig_len,
                         const unsigned char **r_bytes, unsigned *r_len,
                         const unsigned char **s_bytes, unsigned *s_len) {
    unsigned pos = 0;
    unsigned len;
    if (sig_len < 8) return -1;
    if (sig[0] != 0x30) return -1;
    if (sig[1] & 0x80) {
        unsigned llen = sig[1] & 0x7f;
        unsigned i;
        len = 0;
        if (llen > 4 || 2 + llen > sig_len) return -1;
        for (i = 0; i < llen; i++) len = (len << 8) | sig[2 + i];
        pos = 2 + llen;
    } else {
        len = sig[1];
        pos = 2;
    }
    if (pos + len != sig_len) return -1;
    /* r */
    if (sig[pos] != 0x02) return -1;
    if (sig[pos + 1] & 0x80) return -1;
    *r_len = sig[pos + 1];
    if (*r_len == 0 || *r_len > 49 || pos + 2 + *r_len > sig_len) return -1;
    *r_bytes = sig + pos + 2;
    pos += 2 + *r_len;
    if (sig[pos] != 0x02) return -1;
    if (sig[pos + 1] & 0x80) return -1;
    *s_len = sig[pos + 1];
    if (*s_len == 0 || *s_len > 49 || pos + 2 + *s_len != sig_len) return -1;
    *s_bytes = sig + pos + 2;
    return 0;
}

int ecdsa_verify(int curve, const unsigned char pub_x[], const unsigned char pub_y[],
                 const unsigned char digest[], unsigned digest_len,
                 const unsigned char sig[], unsigned sig_len) {
    struct ec_curve *c;
    struct jpt pub, sg, tq, sum;
    const unsigned char *r_bytes, *s_bytes;
    unsigned r_len, s_len;
    unsigned r[TLS_BN_WORDS], s[TLS_BN_WORDS];
    unsigned u1[TLS_BN_WORDS], u2[TLS_BN_WORDS], z[TLS_BN_WORDS];
    unsigned char x_out[48];
    struct mont_ctx *fn;
    int nw, i;
    unsigned char z_bytes[48];

    ec_boot();
    c = ec_curve_by_id(curve);
    fn = &c->fn;
    nw = fn->nw;

    if (der_parse_sig(sig, sig_len, &r_bytes, &r_len, &s_bytes, &s_len) != 0)
        return -1;
    /* DER integers may carry a leading zero pad byte */
    if (r_bytes[0] == 0) { r_bytes++; r_len--; }
    if (s_bytes[0] == 0) { s_bytes++; s_len--; }
    if (r_len > (unsigned)c->len || s_len > (unsigned)c->len) return -1;
    bn_zero(r, nw);
    bn_zero(s, nw);
    bn_from_be(r_bytes, r_len, r, nw);
    bn_from_be(s_bytes, s_len, s, nw);
    if (bn_is_zero(r, nw) || bn_is_zero(s, nw)) return -1;
    if (bn_cmp(r, fn->n, nw) >= 0 || bn_cmp(s, fn->n, nw) >= 0) return -1;

    /* z = the digest as a plain integer: the digest bytes occupy the
     * low end of the n-bit window (leading zeros when the digest is
     * shorter than the curve). This matches OpenSSL's BN_bin2bn. */
    TLS_MEMSET(z_bytes, 0, sizeof(z_bytes));
    {
        unsigned take = digest_len;
        if (take > (unsigned)c->len) take = (unsigned)c->len;
        TLS_MEMCPY(z_bytes + (unsigned)c->len - take, digest, take);
    }
    bn_from_be(z_bytes, (unsigned)c->len, z, nw);

    /* w = s^-1 mod n; u1 = z*w, u2 = r*w mod n */
    {
        unsigned s_m[TLS_BN_WORDS], w_m[TLS_BN_WORDS], z_m[TLS_BN_WORDS];
        unsigned r_m[TLS_BN_WORDS];
        unsigned u1p[TLS_BN_WORDS], u2p[TLS_BN_WORDS];
        mont_to(fn, s, s_m);
        mont_inv(fn, s_m, w_m);
        mont_to(fn, z, z_m);
        mont_to(fn, r, r_m);
        mont_mul(fn, z_m, w_m, u1);
        mont_mul(fn, r_m, w_m, u2);
        mont_from(fn, u1, u1p);
        mont_from(fn, u2, u2p);
        for (i = 0; i < nw; i++) { u1[i] = u1p[i]; u2[i] = u2p[i]; }
    }
    /* R = u1*G + u2*Q */
    {
        struct jpt gen;
        unsigned char s1[48], s2[48];
        TLS_MEMSET(s1, 0, sizeof(s1));
        TLS_MEMSET(s2, 0, sizeof(s2));
        bn_from_be(c->gx, (unsigned)c->len, gen.x, nw);
        bn_from_be(c->gy, (unsigned)c->len, gen.y, nw);
        mont_to(&c->fp, gen.x, gen.x);
        mont_to(&c->fp, gen.y, gen.y);
        for (i = 0; i < nw; i++) gen.z[i] = c->fp.one[i];
        bn_to_be(u1, s1, (unsigned)c->len);
        jpt_scalar_mult(c, &gen, s1, &sg);
        if (jpt_from_affine(c, pub_x, pub_y, &pub) != 0) return -1;
        bn_to_be(u2, s2, (unsigned)c->len);
        jpt_scalar_mult(c, &pub, s2, &tq);
        jpt_add(c, &sg, &tq, &sum);
        jpt_to_affine(c, &sum, x_out, 0);
    }
    {
        unsigned x_limbs[TLS_BN_WORDS];
        unsigned diff = 0;
        bn_from_be(x_out, (unsigned)c->len, x_limbs, nw);
        /* x mod n: n < p, so one subtraction suffices */
        if (bn_cmp(x_limbs, fn->n, nw) >= 0) {
            unsigned t[TLS_BN_WORDS];
            bn_sub(x_limbs, fn->n, t, nw);
            for (i = 0; i < nw; i++) x_limbs[i] = t[i];
        }
        /* constant-time compare r == x mod n */
        for (i = 0; i < nw; i++) diff |= r[i] ^ x_limbs[i];
        return diff ? -1 : 0;
    }
}

/* ========== RSA PKCS#1 v1.5 verify (SHA-256) ========== */

/* EMSA-PKCS1-v1_5 DigestInfo check for an arbitrary hash: the encoding
 * is 00 01 FF.. 00 <prefix><digest>. Constant-time: every byte of the
 * encoding contributes to the diff. */
static int rsa_verify_digestinfo(const unsigned char *em, unsigned em_len,
                                 const unsigned char *prefix, unsigned prefix_len,
                                 const unsigned char *digest, unsigned digest_len) {
    unsigned diff = 0;
    unsigned i;
    if (em_len < prefix_len + digest_len + 2) return -1;
    diff |= em[0] ^ 0x00;
    diff |= em[1] ^ 0x01;
    for (i = 2; i < em_len; i++) {
        if (em[i] == 0x00) break;
        diff |= em[i] ^ 0xff;
    }
    if (i >= em_len) return -1;         /* no separator */
    if (i < 10) return -1;              /* padding too short (RFC 8017) */
    i++;
    if (em_len - i != prefix_len + digest_len) return -1;
    for (i = 0; i < prefix_len; i++)
        diff |= em[em_len - prefix_len - digest_len + i] ^ prefix[i];
    for (i = 0; i < digest_len; i++)
        diff |= em[em_len - digest_len + i] ^ digest[i];
    return diff ? -1 : 0;
}

/* Shared RSA PKCS#1 v1.5 core: m^e mod n, EMSA-PKCS1-v1_5 in em. */
static int rsa_pkcs1_verify_raw(const unsigned char *n, unsigned n_len,
                                const unsigned char *e, unsigned e_len,
                                const unsigned char *sig, unsigned sig_len,
                                unsigned char em[512]) {
    struct mont_ctx m;
    unsigned s[TLS_BN_WORDS], out[TLS_BN_WORDS], base[TLS_BN_WORDS];
    unsigned res[TLS_BN_WORDS];
    int nw, i;
    unsigned long long e_val = 0;
    int e_bits = 0;

    if (n_len > 512 || n_len < 64 || sig_len != n_len) return -1;
    if (e_len > 8 || e_len == 0) return -1;
    for (i = 0; i < (int)e_len; i++) e_val = (e_val << 8) | e[i];
    if (e_val < 3 || (e_val & 1) == 0) return -1;
    while ((e_val >> e_bits)) e_bits++;
    if (e_bits > 64) return -1;

    nw = (int)((n_len + 3) / 4);
    if (nw > TLS_BN_4096_WORDS) return -1;
    mont_init(&m, n, n_len);
    bn_from_be(sig, sig_len, s, nw);
    if (bn_cmp(s, m.n, nw) >= 0) return -1;

    mont_to(&m, s, base);
    /* res = 1 in mont domain */
    for (i = 0; i < nw; i++) res[i] = m.one[i];
    for (i = e_bits - 1; i >= 0; i--) {
        unsigned t[TLS_BN_WORDS];
        mont_sqr(&m, res, t);
        if ((e_val >> i) & 1) mont_mul(&m, t, base, res);
        else {
            int j;
            for (j = 0; j < nw; j++) res[j] = t[j];
        }
    }
    mont_from(&m, res, out);
    bn_to_be(out, em, n_len);
    return 0;
}

int rsa_pkcs1_verify_sha256(const unsigned char *n, unsigned n_len,
                            const unsigned char *e, unsigned e_len,
                            const unsigned char digest[32],
                            const unsigned char *sig, unsigned sig_len) {
    static const unsigned char di_prefix[19] = {
        0x30, 0x31, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01,
        0x65, 0x03, 0x04, 0x02, 0x01, 0x05, 0x00, 0x04, 0x20
    };
    unsigned char em[512];
    if (rsa_pkcs1_verify_raw(n, n_len, e, e_len, sig, sig_len, em) != 0)
        return -1;
    return rsa_verify_digestinfo(em, n_len, di_prefix, 19, digest, 32);
}

int rsa_pkcs1_verify_sha384(const unsigned char *n, unsigned n_len,
                            const unsigned char *e, unsigned e_len,
                            const unsigned char digest[48],
                            const unsigned char *sig, unsigned sig_len) {
    static const unsigned char di_prefix[19] = {
        0x30, 0x41, 0x30, 0x0d, 0x06, 0x09, 0x60, 0x86, 0x48, 0x01,
        0x65, 0x03, 0x04, 0x02, 0x02, 0x05, 0x00, 0x04, 0x30
    };
    unsigned char em[512];
    if (rsa_pkcs1_verify_raw(n, n_len, e, e_len, sig, sig_len, em) != 0)
        return -1;
    return rsa_verify_digestinfo(em, n_len, di_prefix, 19, digest, 48);
}

/* ========== SHA-384 (SHA-512 truncated, for ECDSA-SHA384) ========== */

static const unsigned long long sha384_k[80] = {
    0x428a2f98d728ae22ULL, 0x7137449123ef65cdULL, 0xb5c0fbcfec4d3b2fULL,
    0xe9b5dba58189dbbcULL, 0x3956c25bf348b538ULL, 0x59f111f1b605d019ULL,
    0x923f82a4af194f9bULL, 0xab1c5ed5da6d8118ULL, 0xd807aa98a3030242ULL,
    0x12835b0145706fbeULL, 0x243185be4ee4b28cULL, 0x550c7dc3d5ffb4e2ULL,
    0x72be5d74f27b896fULL, 0x80deb1fe3b1696b1ULL, 0x9bdc06a725c71235ULL,
    0xc19bf174cf692694ULL, 0xe49b69c19ef14ad2ULL, 0xefbe4786384f25e3ULL,
    0x0fc19dc68b8cd5b5ULL, 0x240ca1cc77ac9c65ULL, 0x2de92c6f592b0275ULL,
    0x4a7484aa6ea6e483ULL, 0x5cb0a9dcbd41fbd4ULL, 0x76f988da831153b5ULL,
    0x983e5152ee66dfabULL, 0xa831c66d2db43210ULL, 0xb00327c898fb213fULL,
    0xbf597fc7beef0ee4ULL, 0xc6e00bf33da88fc2ULL, 0xd5a79147930aa725ULL,
    0x06ca6351e003826fULL, 0x142929670a0e6e70ULL, 0x27b70a8546d22ffcULL,
    0x2e1b21385c26c926ULL, 0x4d2c6dfc5ac42aedULL, 0x53380d139d95b3dfULL,
    0x650a73548baf63deULL, 0x766a0abb3c77b2a8ULL, 0x81c2c92e47edaee6ULL,
    0x92722c851482353bULL, 0xa2bfe8a14cf10364ULL, 0xa81a664bbc423001ULL,
    0xc24b8b70d0f89791ULL, 0xc76c51a30654be30ULL, 0xd192e819d6ef5218ULL,
    0xd69906245565a910ULL, 0xf40e35855771202aULL, 0x106aa07032bbd1b8ULL,
    0x19a4c116b8d2d0c8ULL, 0x1e376c085141ab53ULL, 0x2748774cdf8eeb99ULL,
    0x34b0bcb5e19b48a8ULL, 0x391c0cb3c5c95a63ULL, 0x4ed8aa4ae3418acbULL,
    0x5b9cca4f7763e373ULL, 0x682e6ff3d6b2b8a3ULL, 0x748f82ee5defb2fcULL,
    0x78a5636f43172f60ULL, 0x84c87814a1f0ab72ULL, 0x8cc702081a6439ecULL,
    0x90befffa23631e28ULL, 0xa4506cebde82bde9ULL, 0xbef9a3f7b2c67915ULL,
    0xc67178f2e372532bULL, 0xca273eceea26619cULL, 0xd186b8c721c0c207ULL,
    0xeada7dd6cde0eb1eULL, 0xf57d4f7fee6ed178ULL, 0x06f067aa72176fbaULL,
    0x0a637dc5a2c898a6ULL, 0x113f9804bef90daeULL, 0x1b710b35131c471bULL,
    0x28db77f523047d84ULL, 0x32caab7b40c72493ULL, 0x3c9ebe0a15c9bebcULL,
    0x431d67c49c100d4cULL, 0x4cc5d4becb3e42b6ULL, 0x597f299cfc657e2aULL,
    0x5fcb6fab3ad6faecULL, 0x6c44198c4a475817ULL
};

static unsigned long long sha384_rotr(unsigned long long x, unsigned n) {
    return (x >> n) | (x << (64 - n));
}

static void sha384_raw(const unsigned char *data, unsigned len,
                       unsigned char out[48]) {
    unsigned long long state[8] = {
        0xcbbb9d5dc1059ed8ULL, 0x629a292a367cd507ULL,
        0x9159015a3070dd17ULL, 0x152fecd8f70e5939ULL,
        0x67332667ffc00b31ULL, 0x8eb44a8768581511ULL,
        0xdb0c2e0d64f98fa7ULL, 0x47b5481dbefa4fa4ULL
    };
    unsigned char block[256];
    unsigned long long bits = (unsigned long long)len * 8;
    unsigned i, block_len;

    /* process full blocks */
    while (len >= 128) {
        unsigned long long w[80];
        unsigned long long a, b, c, d, e, f, g, h;
        for (i = 0; i < 16; i++) {
            w[i] = ((unsigned long long)data[i * 8] << 56) |
                   ((unsigned long long)data[i * 8 + 1] << 48) |
                   ((unsigned long long)data[i * 8 + 2] << 40) |
                   ((unsigned long long)data[i * 8 + 3] << 32) |
                   ((unsigned long long)data[i * 8 + 4] << 24) |
                   ((unsigned long long)data[i * 8 + 5] << 16) |
                   ((unsigned long long)data[i * 8 + 6] << 8) |
                   (unsigned long long)data[i * 8 + 7];
        }
        for (i = 16; i < 80; i++) {
            unsigned long long s0 = sha384_rotr(w[i - 15], 1) ^ sha384_rotr(w[i - 15], 8) ^
                                    (w[i - 15] >> 7);
            unsigned long long s1 = sha384_rotr(w[i - 2], 19) ^ sha384_rotr(w[i - 2], 61) ^
                                    (w[i - 2] >> 6);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }
        a = state[0]; b = state[1]; c = state[2]; d = state[3];
        e = state[4]; f = state[5]; g = state[6]; h = state[7];
        for (i = 0; i < 80; i++) {
            unsigned long long S1 = sha384_rotr(e, 14) ^ sha384_rotr(e, 18) ^ sha384_rotr(e, 41);
            unsigned long long ch = (e & f) ^ (~e & g);
            unsigned long long t1 = h + S1 + ch + sha384_k[i] + w[i];
            unsigned long long S0 = sha384_rotr(a, 28) ^ sha384_rotr(a, 34) ^ sha384_rotr(a, 39);
            unsigned long long maj = (a & b) ^ (a & c) ^ (b & c);
            unsigned long long t2 = S0 + maj;
            h = g; g = f; f = e; e = d + t1;
            d = c; c = b; b = a; a = t1 + t2;
        }
        state[0] += a; state[1] += b; state[2] += c; state[3] += d;
        state[4] += e; state[5] += f; state[6] += g; state[7] += h;
        data += 128;
        len -= 128;
    }
    /* last block(s) with padding; message fits < 2^64 bits here.
     * len < 128 at this point: one padded block, or two when the
     * 0x80 + 8-byte length does not fit in the current block. */
    TLS_MEMCPY(block, data, len);
    block[len] = 0x80;
    if (len + 17 <= 128) {
        TLS_MEMSET(block + len + 1, 0, 128 - 8 - (len + 1));
        for (i = 0; i < 8; i++)
            block[120 + i] = (unsigned char)(bits >> (56 - i * 8));
        block_len = 128;
    } else {
        TLS_MEMSET(block + len + 1, 0, 256 - 8 - (len + 1));
        for (i = 0; i < 8; i++)
            block[248 + i] = (unsigned char)(bits >> (56 - i * 8));
        block_len = 256;
    }
    /* process the final 1-2 blocks */
    while (block_len > 0) {
        unsigned long long w[80];
        unsigned long long a, b, c, d, e, f, g, h;
        for (i = 0; i < 16; i++) {
            w[i] = ((unsigned long long)block[i * 8] << 56) |
                   ((unsigned long long)block[i * 8 + 1] << 48) |
                   ((unsigned long long)block[i * 8 + 2] << 40) |
                   ((unsigned long long)block[i * 8 + 3] << 32) |
                   ((unsigned long long)block[i * 8 + 4] << 24) |
                   ((unsigned long long)block[i * 8 + 5] << 16) |
                   ((unsigned long long)block[i * 8 + 6] << 8) |
                   (unsigned long long)block[i * 8 + 7];
        }
        for (i = 16; i < 80; i++) {
            unsigned long long s0 = sha384_rotr(w[i - 15], 1) ^ sha384_rotr(w[i - 15], 8) ^
                                    (w[i - 15] >> 7);
            unsigned long long s1 = sha384_rotr(w[i - 2], 19) ^ sha384_rotr(w[i - 2], 61) ^
                                    (w[i - 2] >> 6);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }
        a = state[0]; b = state[1]; c = state[2]; d = state[3];
        e = state[4]; f = state[5]; g = state[6]; h = state[7];
        for (i = 0; i < 80; i++) {
            unsigned long long S1 = sha384_rotr(e, 14) ^ sha384_rotr(e, 18) ^ sha384_rotr(e, 41);
            unsigned long long ch = (e & f) ^ (~e & g);
            unsigned long long t1 = h + S1 + ch + sha384_k[i] + w[i];
            unsigned long long S0 = sha384_rotr(a, 28) ^ sha384_rotr(a, 34) ^ sha384_rotr(a, 39);
            unsigned long long maj = (a & b) ^ (a & c) ^ (b & c);
            unsigned long long t2 = S0 + maj;
            h = g; g = f; f = e; e = d + t1;
            d = c; c = b; b = a; a = t1 + t2;
        }
        state[0] += a; state[1] += b; state[2] += c; state[3] += d;
        state[4] += e; state[5] += f; state[6] += g; state[7] += h;
        TLS_MEMCPY(block, block + 128, block_len > 128 ? 128 : 0);
        block_len -= 128;
    }
    for (i = 0; i < 6; i++) {
        out[i * 8]     = (unsigned char)(state[i] >> 56);
        out[i * 8 + 1] = (unsigned char)(state[i] >> 48);
        out[i * 8 + 2] = (unsigned char)(state[i] >> 40);
        out[i * 8 + 3] = (unsigned char)(state[i] >> 32);
        out[i * 8 + 4] = (unsigned char)(state[i] >> 24);
        out[i * 8 + 5] = (unsigned char)(state[i] >> 16);
        out[i * 8 + 6] = (unsigned char)(state[i] >> 8);
        out[i * 8 + 7] = (unsigned char)state[i];
    }
}

void sha384(const unsigned char *data, unsigned len, unsigned char out[48]) {
    sha384_raw(data, len, out);
}

/* ========== P-256 helpers for the handshake ========== */

int p256_point_valid(const unsigned char x[32], const unsigned char y[32]) {
    struct ec_curve *c;
    struct jpt p;
    ec_boot();
    c = &ec_p256;
    return jpt_from_affine(c, x, y, &p) == 0 ? 0 : -1;
}

int p256_pub(const unsigned char priv[32],
             unsigned char x[32], unsigned char y[32]) {
    struct ec_curve *c;
    struct jpt gen, out;
    ec_boot();
    c = &ec_p256;
    {
        int nw = c->fp.nw, i;
        bn_from_be(c->gx, 32, gen.x, nw);
        bn_from_be(c->gy, 32, gen.y, nw);
        mont_to(&c->fp, gen.x, gen.x);
        mont_to(&c->fp, gen.y, gen.y);
        for (i = 0; i < nw; i++) gen.z[i] = c->fp.one[i];
    }
    jpt_scalar_mult(c, &gen, priv, &out);
    jpt_to_affine(c, &out, x, y);
    return 0;
}

int p256_scalar_valid(const unsigned char scalar[32]) {
    unsigned s[TLS_BN_WORDS], n[TLS_BN_WORDS];
    ec_boot();
    bn_from_be(scalar, 32, s, 8);
    bn_from_be(ec_p256_n, 32, n, 8);
    if (bn_is_zero(s, 8)) return -1;
    if (bn_cmp(s, n, 8) >= 0) return -1;
    return 0;
}
