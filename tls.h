#ifndef TLS_H
#define TLS_H

/* ========== TLS 1.2 client (RFC 5246) ========== */

/* Record layer */
#define TLS_CT_CCS            20
#define TLS_CT_ALERT          21
#define TLS_CT_HANDSHAKE      22
#define TLS_CT_APPDATA        23
#define TLS_REC_HEADER        5
#define TLS_REC_MAX           16640
#define TLS_MSG_MAX           16640
#define TLS_PLAIN_MAX         16640
#define TLS_VERSION_TLS12     0x0303
#define TLS_VERSION_TLS10     0x0301

/* Handshake message types */
#define TLS_HS_CLIENT_HELLO       1
#define TLS_HS_SERVER_HELLO       2
#define TLS_HS_CERTIFICATE        11
#define TLS_HS_SERVER_KEY_EXCHANGE 12
#define TLS_HS_SERVER_HELLO_DONE  14
#define TLS_HS_CLIENT_KEY_EXCHANGE 16
#define TLS_HS_FINISHED           20

/* Cipher suites (TLS 1.2) */
#define TLS_CSUITE_ECDHE_RSA_AES128GCM   0xC02F
#define TLS_CSUITE_ECDHE_ECDSA_AES128GCM 0xC02B

/* Signature algorithms (TLS 1.2 SignatureAndHashAlgorithm) */
#define TLS_SIG_RSA_PKCS1_SHA256     0x0401
#define TLS_SIG_ECDSA_P256_SHA256    0x0403
#define TLS_SIG_ECDSA_P384_SHA384    0x0503

/* Named curve: secp256r1 (P-256) only, offered in supported_groups */
#define TLS_GROUP_SECP256R1          23

/* Extensions */
#define TLS_EXT_SERVER_NAME          0
#define TLS_EXT_SUPPORTED_GROUPS     10
#define TLS_EXT_EC_POINT_FORMATS     11
#define TLS_EXT_SIGNATURE_ALGS       13

/* Alerts */
#define TLS_ALERT_LEVEL_WARNING      1
#define TLS_ALERT_LEVEL_FATAL        2

/* Handshake deadlines: a silent peer must not hang the shell forever */
#define TLS_HS_TIMEOUT_MS            10000
#define TLS_READ_TIMEOUT_MS          10000

/* Hostname bound: matches the ramdisk filename bound used by the shell */
#define TLS_HOST_MAX                 63

/* Certificate chain bounds: 4 certs, each up to 8 KB of DER, 32 KB total */
#define TLS_CHAIN_MAX                32768
#define TLS_CERT_MAX                 8192

/* Big number word sizes (32-bit words): RSA up to 4096-bit moduli,
 * P-384 curves */
#define TLS_BN_4096_WORDS            128
#define TLS_BN_384_WORDS             12

/* Embedded roots live in tls_roots.h as DER byte arrays; the count
 * must equal the table mkroots.sh generates. The host test build
 * (tls_test.py) pads its injected table to the same count. */
#define TLS_ROOT_COUNT                8

struct tls_root {
    const unsigned char *der;
    unsigned            len;
};

extern const struct tls_root tls_roots[TLS_ROOT_COUNT];

/* ========== Session ========== */

struct sha256_ctx {
    unsigned state[8];
    unsigned count[2];
    unsigned char buf[64];
};

struct tls_pubkey {
    int  kind;              /* 0 = RSA, 1 = ECDSA P-256, 2 = ECDSA P-384 */
    unsigned char n[512];
    unsigned      n_len;
    unsigned char e[8];
    unsigned      e_len;
    unsigned char qx[48];
    unsigned char qy[48];
};

struct tls_session {
    int   active;
    int   hs_done;
    int   keys_ready;      /* after our CCS: records are encrypted */
    int   eof;            /* TCP EOF seen */
    int   truncated;      /* EOF with a torn record: reported, fail closed */
    int   state;          /* handshake stage: 0 SH, 1 cert, 2 SKE, 3 SHD, 4 fin */
    char  host[TLS_HOST_MAX + 1];

    /* Current record (header excluded) */
    unsigned char rec[TLS_REC_MAX];
    unsigned char rec_hdr[5];
    int  rec_len;
    int  rec_type;
    int  rec_pos;

    /* Handshake message reassembly (messages may span records) */
    unsigned char hs_msg[TLS_MSG_MAX];
    int  hs_msg_len;
    int  hs_msg_type;
    int  hs_msg_want;      /* full message length, 0 = waiting for header */

    /* Handshake transcript hash (every handshake message, ever) */
    struct sha256_ctx hs_hash;

    /* Client random (sent in ClientHello, reseeded per handshake) */
    unsigned char cli_random[32];

    /* Certificate chain (parsed from the Certificate message) */
    unsigned char chain[TLS_CHAIN_MAX];
    unsigned      cert_lens[4];
    int           n_certs;

    /* Decrypted application plaintext not yet consumed by tls_recv */
    unsigned char pt[TLS_PLAIN_MAX];
    int  pt_head;
    int  pt_tail;

    /* Cipher state: AES-128-GCM, implicit 4-byte nonce salts */
    unsigned char cli_key[16];
    unsigned char srv_key[16];
    unsigned char cli_salt[4];
    unsigned char srv_salt[4];
    unsigned long long cli_seq;
    unsigned long long srv_seq;

    /* ServerHello values */
    unsigned char srv_random[32];
    int  cipher_suite;
    int  sig_alg;          /* negotiated ServerKeyExchange signature */

    /* Server ephemeral ECDHE key (P-256 affine) */
    unsigned char srv_pub_x[32];
    unsigned char srv_pub_y[32];

    /* Our ECDHE private scalar and public point */
    unsigned char cli_priv[32];
    unsigned char cli_pub_x[32];
    unsigned char cli_pub_y[32];

    /* Leaf certificate public key (for the SKE signature) */
    struct tls_pubkey leaf_pk;
    int  leaf_pk_ok;

    /* Master secret (48 bytes) */
    unsigned char master[48];

    /* Outgoing record assembly buffer */
    unsigned char tx[TLS_REC_MAX + 64];
};

/* ========== Crypto (tls_crypto.c) ========== */

void sha256_init(struct sha256_ctx *c);
void sha256_update(struct sha256_ctx *c, const unsigned char *data, unsigned len);
void sha256_final(struct sha256_ctx *c, unsigned char out[32]);
void sha256(const unsigned char *data, unsigned len, unsigned char out[32]);
void sha384(const unsigned char *data, unsigned len, unsigned char out[48]);

void hmac_sha256(const unsigned char *key, unsigned klen,
                 const unsigned char *data, unsigned dlen,
                 unsigned char out[32]);

/* TLS 1.2 PRF with SHA-256 */
void tls_prf(const unsigned char *secret, unsigned secret_len,
             const char *label, const unsigned char *seed, unsigned seed_len,
             unsigned char *out, unsigned out_len);

/* AES-128 block cipher (key expansion internal; T-table implementation) */
void aes128_encrypt_block(const unsigned char key[16],
                          const unsigned char in[16], unsigned char out[16]);

/* GCM. Each call seals one record: tag = 16 bytes appended to ct.
 * Returns 0 on success, -1 on overflow (len > TLS_REC_MAX). */
int aes128_gcm_seal(const unsigned char key[16],
                    const unsigned char salt[4],
                    unsigned long long seq,
                    const unsigned char *aad, unsigned aad_len,
                    const unsigned char *pt, unsigned pt_len,
                    unsigned char *ct, unsigned char tag[16]);

/* Returns 0 when the tag verifies, -1 otherwise (constant-time compare). */
int aes128_gcm_open(const unsigned char key[16],
                    const unsigned char salt[4],
                    unsigned long long seq,
                    const unsigned char *aad, unsigned aad_len,
                    const unsigned char *ct, unsigned ct_len,
                    const unsigned char tag[16],
                    unsigned char *pt);

/* Core GCM with an arbitrary 12-byte nonce (the TLS API above is the
 * 4-byte salt + 8-byte sequence special case). Used by the host tests
 * against the NIST vectors. */
int aes128_gcm_seal_core(const unsigned char key[16],
                         const unsigned char nonce[12],
                         const unsigned char *aad, unsigned aad_len,
                         const unsigned char *pt, unsigned pt_len,
                         unsigned char *ct, unsigned char tag[16]);
int aes128_gcm_open_core(const unsigned char key[16],
                         const unsigned char nonce[12],
                         const unsigned char *aad, unsigned aad_len,
                         const unsigned char *ct, unsigned ct_len,
                         const unsigned char tag[16],
                         unsigned char *pt);

/* secp256r1 / secp384r1: shared Jacobian point arithmetic over NIST
 * primes. curve: 0 = P-256, 1 = P-384. */
int  p256_scalar_mult(const unsigned char scalar[32],
                      const unsigned char qx[32], const unsigned char qy[32],
                      unsigned char rx[32], unsigned char ry[32]);
int  p384_scalar_mult(const unsigned char scalar[48],
                      const unsigned char qx[48], const unsigned char qy[48],
                      unsigned char rx[48], unsigned char ry[48]);

/* ECDH shared secret: Z = priv * peer_pub (P-256). Returns 0 on success,
 * -1 when the peer point is not on the curve (fail closed). */
int  p256_ecdh(const unsigned char priv[32],
               const unsigned char peer_x[32], const unsigned char peer_y[32],
               unsigned char z[32]);

/* P-256 point validation and helpers for the handshake */
int  p256_point_valid(const unsigned char x[32], const unsigned char y[32]);
int  p256_pub(const unsigned char priv[32],
              unsigned char x[32], unsigned char y[32]);
int  p256_scalar_valid(const unsigned char scalar[32]);

/* ECDSA verify over a SHA-256 or SHA-384 digest. curve: 0 = P-256,
 * 1 = P-384. Returns 0 when the signature verifies. */
int  ecdsa_verify(int curve, const unsigned char pub_x[], const unsigned char pub_y[],
                  const unsigned char digest[], unsigned digest_len,
                  const unsigned char sig[], unsigned sig_len);

/* RSA PKCS#1 v1.5 signature verify with SHA-256. modulus up to 4096 bits.
 * digest is the SHA-256 of the signed data. Returns 0 on success. */
int  rsa_pkcs1_verify_sha256(const unsigned char *n, unsigned n_len,
                             const unsigned char *e, unsigned e_len,
                             const unsigned char digest[32],
                             const unsigned char *sig, unsigned sig_len);
int  rsa_pkcs1_verify_sha384(const unsigned char *n, unsigned n_len,
                             const unsigned char *e, unsigned e_len,
                             const unsigned char digest[48],
                             const unsigned char *sig, unsigned sig_len);

/* ========== X.509 (tls_x509.c) ========== */

/* Parse one DER certificate into a public key. Returns 0 on success. */
int tls_x509_parse_pubkey(const unsigned char *der, unsigned len,
                          struct tls_pubkey *pk);

/* Verify the full chain: each cert[1..] signed by cert[i-1]; the last
 * signer must be an embedded root. Also checks hostname against SAN
 * dNSName / subject CN (exact or single-label wildcard) and the validity
 * window against now (days since epoch). Returns 0 on success. */
int tls_x509_verify_chain(const unsigned char *chain, unsigned chain_len,
                          unsigned cert_lens[], int n_certs,
                          const char *host, long now_days);

/* ========== Session (tls.c) ========== */

/* Blocking TLS 1.2 handshake over an open TCP socket (net fd index).
 * host is the SNI + certificate hostname. Returns 0 on success, -1 with
 * a diagnostic on the console. The session lives on the kernel heap. */
int tls_handshake(int fd, const char *host);

/* Send len plaintext bytes as one TLS record. All-or-error. */
int tls_send(int fd, const char *buf, int len);

/* Receive decrypted application bytes. 0 = clean EOF (close_notify or FIN
 * at a record boundary); -1 = protocol error / truncation (diagnostic). */
int tls_recv(int fd, char *buf, int len);

/* Free the session attached to fd. A socket without TLS costs nothing. */
void tls_free_fd(int fd);

/* ========== Syscalls (kernel wiring in tls.c) ========== */
long tls_sys_handshake(long fd, long host);
long tls_sys_send(long fd, long buf, long len);
long tls_sys_recv(long fd, long buf, long len);

#endif
