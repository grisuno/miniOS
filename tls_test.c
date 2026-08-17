/* tls_test.c - host-side tests for the kernel TLS stack.
 *
 * Compiled with -DTLS_TEST against the host libc (never into the
 * kernel image). Part one: fixed vectors (SHA-256, AES-128-GCM,
 * P-256 ECDH from RFC 5903, RSA PKCS#1 v1.5 and ECDSA verifies against
 * openssl-generated signatures embedded by tls_test.py). Part two:
 * full TLS 1.2 handshakes against python ssl servers (RSA chain,
 * ECDSA P-256 leaf over a P-384 CA), plus the negative set.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "tls_port.h"
#include "tls.h"
#include "tls_test_roots.h"

/* ---- transport: the TLS stack talks to POSIX sockets here ---- */

int tls_test_send(int fd, const char *buf, int len) {
    int sent = 0;
    while (sent < len) {
        int r = (int)send(fd, buf + sent, (size_t)(len - sent), 0);
        if (r <= 0) return -1;
        sent += r;
    }
    return sent;
}

int tls_test_recv(int fd, char *buf, int len) {
    int r = (int)recv(fd, buf, (size_t)len, 0);
    return r;
}

int tls_test_recv_timeout(int fd, char *buf, int len, unsigned long ms) {
    struct timeval tv;
    fd_set fds;
    int r;
    tv.tv_sec = (long)(ms / 1000);
    tv.tv_usec = (long)((ms % 1000) * 1000);
    FD_ZERO(&fds);
    FD_SET(fd, &fds);
    r = select(fd + 1, &fds, 0, 0, &tv);
    if (r <= 0) return -1;
    return (int)recv(fd, buf, (size_t)len, 0);
}

void tls_test_close(int fd) {
    close(fd);
}

/* ---- helpers ---- */

static int failures = 0;

#define CHECK(name, cond) do { \
    if (cond) printf("  PASS  %s\n", name); \
    else { printf("  FAIL  %s\n", name); failures++; } \
} while (0)

static int hexdigit(int c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static void unhex(const char *hex, unsigned char *out, int n) {
    int i;
    for (i = 0; i < n; i++)
        out[i] = (unsigned char)((hexdigit(hex[2 * i]) << 4) | hexdigit(hex[2 * i + 1]));
}

static int bytes_eq(const unsigned char *a, const unsigned char *b, int n) {
    int i, d = 0;
    for (i = 0; i < n; i++) d |= a[i] ^ b[i];
    return d == 0;
}

/* ---- fixed vectors ---- */

static void test_sha256(void) {
    unsigned char out[32];
    static const char *abc =
        "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";
    static const char *empty =
        "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855";
    unsigned char want[32];
    sha256((const unsigned char *)"abc", 3, out);
    unhex(abc, want, 32);
    CHECK("sha256 abc", bytes_eq(out, want, 32));
    sha256((const unsigned char *)"", 0, out);
    unhex(empty, want, 32);
    CHECK("sha256 empty", bytes_eq(out, want, 32));
}

static void test_sha384(void) {
    unsigned char out[48];
    static const char *abc =
        "cb00753f45a35e8bb5a03d699ac65007272c32ab0eded1631a8b605a43ff5bed"
        "8086072ba1e7cc2358baeca134c825a7";
    unsigned char want[48];
    sha384((const unsigned char *)"abc", 3, out);
    unhex(abc, want, 48);
    CHECK("sha384 abc", bytes_eq(out, want, 48));
}

static void test_gcm(void) {
    /* NIST GCM spec test case 3 */
    static const char *keyhex =
        "feffe9928665731c6d6a8f9467308308";
    static const char *ivhex = "cafebabefacedbaddecaf888";
    static const char *pthex =
        "d9313225f88406e5a55909c5aff5269a"
        "86a7a9531534f7da2e4c303d8a318a72"
        "1c3c0c95956809532fcf0e2449a6b525"
        "b16aedf5aa0de657ba637b391aafd255";
    static const char *cthex =
        "42831ec2217774244b7221b784d0d49c"
        "e3aa212f2c02a4e035c17e2329aca12e"
        "21d514b25466931c7d8f6a5aac84aa05"
        "1ba30b396a0aac973d58e091473f5985";
    static const char *taghex = "4d5c2af327cd64a62cf35abd2ba6fab4";
    unsigned char key[16], nonce[12], pt[64], ct[64], tag[16], want[64], wt[16];
    int ok;

    unhex(keyhex, key, 16);
    unhex(ivhex, nonce, 12);
    unhex(pthex, pt, 64);
    unhex(cthex, want, 64);
    unhex(taghex, wt, 16);

    /* the NIST case carries no AAD */
    ok = aes128_gcm_seal_core(key, nonce, 0, 0, pt, 64, ct, tag) == 0 &&
         bytes_eq(ct, want, 64) && bytes_eq(tag, wt, 16);
    CHECK("aes128 gcm seal", ok);

    ok = aes128_gcm_open_core(key, nonce, 0, 0, want, 64, wt, ct) == 0 &&
         bytes_eq(ct, pt, 64);
    CHECK("aes128 gcm open", ok);

    /* tampered tag must fail */
    wt[0] ^= 0x40;
    ok = aes128_gcm_open_core(key, nonce, 0, 0, want, 64, wt, ct) == -1;
    CHECK("aes128 gcm bad tag", ok);
}

static void test_p256(void) {
    /* RFC 5903 section 2.1: ECDH with P-256 */
    static const char *alice_priv =
        "C88F01F510D9AC3F70A292DAA2316DE5"
        "44E9AAB8AFE84049C62A9C57862D1433";
    static const char *alice_pub_x =
        "DAD0B65394221CF9B051E1FECA5787D0"
        "98DFE637FC90B9EF945D0C3772581180";
    static const char *alice_pub_y =
        "5271A0461CDB8252D61F1C456FA3E59AB"
        "1F45B33ACCF5F58389E0577B8990BB3";
    static const char *bob_pub_x =
        "D12DFB5289C8D4F81208B70270398C342"
        "296970A0BCCB74C736FC7554494BF63";
    static const char *bob_pub_y =
        "56FBF3CA366CC23E8157854C13C58D6A"
        "AC23F046ADA30F8353E74F33039872AB";
    static const char *zhex =
        "D6840F6B42F6EDAFD13116E0E1256520"
        "2FEF8E9ECE7DCE03812464D04B9442DE";
    unsigned char priv[32], px[32], py[32], bx[32], by[32], want[32], ay[32];

    unhex(alice_priv, priv, 32);
    unhex(alice_pub_x, want, 32);
    unhex(alice_pub_y, ay, 32);
    unhex(bob_pub_x, bx, 32);
    unhex(bob_pub_y, by, 32);

    CHECK("p256 scalar valid", p256_scalar_valid(priv) == 0);
    CHECK("p256 pubkey", p256_pub(priv, px, py) == 0 &&
          bytes_eq(px, want, 32) && bytes_eq(py, ay, 32));
    {
        unsigned char z[32];
        unhex(zhex, z, 32);
        CHECK("p256 ecdh z", p256_ecdh(priv, bx, by, px) == 0 &&
              bytes_eq(px, z, 32));
    }
    /* a point off the curve must be refused */
    {
        unsigned char ox[32], oy[32];
        memset(ox, 0, 32); memset(oy, 0, 32);
        oy[31] = 5;
        CHECK("p256 rejects bad point", p256_point_valid(ox, oy) == -1);
    }
}

static void test_rsa_ecdsa_vectors(void) {
    unsigned char digest[32];
    int ok;
    sha256(test_payload, (unsigned)sizeof(test_payload), digest);
    ok = rsa_pkcs1_verify_sha256(test_rsa_n, sizeof(test_rsa_n),
                                 test_rsa_e, sizeof(test_rsa_e),
                                 digest, test_rsa_sig, sizeof(test_rsa_sig)) == 0;
    CHECK("rsa pkcs1v15 sha256 verify", ok);
    /* flipping one signature byte must fail */
    {
        unsigned char bad[256];
        memcpy(bad, test_rsa_sig, sizeof(test_rsa_sig));
        bad[0] ^= 0x01;
        ok = rsa_pkcs1_verify_sha256(test_rsa_n, sizeof(test_rsa_n),
                                     test_rsa_e, sizeof(test_rsa_e),
                                     digest, bad, sizeof(test_rsa_sig)) == -1;
        CHECK("rsa rejects tampered sig", ok);
    }
    ok = ecdsa_verify(0, test_ec_x, test_ec_y, digest, 32,
                      test_ec_sig, sizeof(test_ec_sig)) == 0;
    CHECK("ecdsa p256 sha256 verify", ok);
    {
        unsigned char bad[256];
        memcpy(bad, test_ec_sig, sizeof(test_ec_sig));
        bad[2] ^= 0x01;
        ok = ecdsa_verify(0, test_ec_x, test_ec_y, digest, 32,
                          bad, sizeof(test_ec_sig)) == -1;
        CHECK("ecdsa rejects tampered sig", ok);
    }
}

/* ---- network scenarios ---- */

static int tcp_connect(int port) {
    struct sockaddr_in sa;
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return -1;
    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons((unsigned short)port);
    sa.sin_addr.s_addr = htonl(0x7f000001UL);
    if (connect(fd, (struct sockaddr *)&sa, sizeof(sa)) != 0) {
        close(fd);
        return -1;
    }
    return fd;
}

/* Full handshake + one HTTP round trip. Returns 0 on success. */
static int http_over_tls(int port, const char *host) {
    int fd = tcp_connect(port);
    char buf[512];
    int n, total = 0, printed = 0;
    if (fd < 0) return -1;
    if (tls_handshake(fd, host) != 0) return -1;
    {
        static const char *req =
            "GET / HTTP/1.0\r\nHost: localhost\r\n\r\n";
        if (tls_send(fd, req, (int)strlen(req)) != (int)strlen(req)) return -1;
    }
    for (;;) {
        n = tls_recv(fd, buf, sizeof(buf));
        if (n < 0) return -1;
        if (n == 0) break;
        fwrite(buf, 1, (size_t)n, stdout);
        total += n;
        printed = 1;
    }
    tls_free_fd(fd);
    close(fd);
    if (!printed) return -1;
    return 0;
}

static int scenario_good(int port) {
    return http_over_tls(port, "localhost") == 0 ? 0 : -1;
}

/* "*.example.com" matches exactly one label. */
static int scenario_wild_good(int port) {
    return http_over_tls(port, "sub.example.com") == 0 ? 0 : -1;
}

static int scenario_wild_root(int port) {
    int fd = tcp_connect(port);
    int rc;
    if (fd < 0) return 1;
    rc = tls_handshake(fd, "example.com");
    tls_free_fd(fd);
    close(fd);
    return rc == 0 ? 1 : 0;   /* the bare domain must not match */
}

static int scenario_wild_deep(int port) {
    int fd = tcp_connect(port);
    int rc;
    if (fd < 0) return 1;
    rc = tls_handshake(fd, "a.b.example.com");
    tls_free_fd(fd);
    close(fd);
    return rc == 0 ? 1 : 0;   /* two labels must not match */
}

static int scenario_bad_host(int port) {
    int fd = tcp_connect(port);
    int rc;
    if (fd < 0) return 1;
    rc = tls_handshake(fd, "other.example");
    tls_free_fd(fd);
    close(fd);
    return rc == 0 ? 1 : 0;   /* handshake must fail */
}

static int scenario_bad_ca(int port) {
    int fd = tcp_connect(port);
    int rc;
    if (fd < 0) return 1;
    rc = tls_handshake(fd, "localhost");
    tls_free_fd(fd);
    close(fd);
    return rc == 0 ? 1 : 0;
}

static int scenario_expired(int port) {
    int fd = tcp_connect(port);
    int rc;
    if (fd < 0) return 1;
    rc = tls_handshake(fd, "localhost");
    tls_free_fd(fd);
    close(fd);
    return rc == 0 ? 1 : 0;
}

int main(int argc, char **argv) {
    printf("tls_test\n");
    if (argc < 2) {
        test_sha256();
        test_sha384();
        test_gcm();
        test_p256();
        test_rsa_ecdsa_vectors();
        printf("=== unit vectors %s ===\n", failures ? "FAIL" : "all vectors pass");
        return failures ? 1 : 0;
    }
    if (strcmp(argv[1], "good-rsa") == 0)
        return scenario_good(atoi(argv[2])) == 0 ? 0 : 1;
    if (strcmp(argv[1], "good-ec") == 0)
        return scenario_good(atoi(argv[2])) == 0 ? 0 : 1;
    if (strcmp(argv[1], "bad-host") == 0)
        return scenario_bad_host(atoi(argv[2]));
    if (strcmp(argv[1], "bad-ca") == 0)
        return scenario_bad_ca(atoi(argv[2]));
    if (strcmp(argv[1], "expired") == 0)
        return scenario_expired(atoi(argv[2]));
    if (strcmp(argv[1], "wild-good") == 0)
        return scenario_wild_good(atoi(argv[2])) == 0 ? 0 : 1;
    if (strcmp(argv[1], "wild-root") == 0)
        return scenario_wild_root(atoi(argv[2]));
    if (strcmp(argv[1], "wild-deep") == 0)
        return scenario_wild_deep(atoi(argv[2]));
    if (strcmp(argv[1], "chain-good") == 0)
        return scenario_good(atoi(argv[2])) == 0 ? 0 : 1;
    return 2;
}
