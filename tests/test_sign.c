/** Docstring: Host test for kernel/ed25519.c plus headers/sign.h.
 *
 * Drives SHA-512 against the "abc" vector, Ed25519 verification
 * against independent PyNaCl vectors (empty, short and 1024-byte
 * messages under the development key) and every fail-closed refusal:
 * flipped signature, message and key bytes, S at or above L,
 * non-canonical R and the unprovisioned production slot. A mutant
 * that skips any check dies here with no QEMU boot.
 *
 * Run through `make test-sign`.
 */

#include <stdio.h>
#include <string.h>

#include "sign.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

static unsigned hexval(char c) {
    if (c >= '0' && c <= '9')
        return (unsigned)(c - '0');
    return (unsigned)(c - 'a' + 10);
}

static void unhex(unsigned char *out, const char *in, unsigned n) {
    unsigned i;
    for (i = 0; i < n; i++)
        out[i] = (unsigned char)((hexval(in[2u * i]) << 4) | hexval(in[2u * i + 1u]));
}

static const char kPub[] =
    "df968c9d646953eded22bab208669cb7ec1a94e32be5ebeb95b3aeacb8d7561e";
static const char kSigEmpty[] =
    "c068a9e87df86834fb653af138111d3ac0b2ce7ace29126cd7066641a366b"
    "e0a2399f6a0242df52bfd5782a415af3c8f6c8c184367c1cc902d932cb4c7568808";
static const char kSigShort[] =
    "2215e0b03e3e0a2ad5de3dcf08dec0e7b6d46e887bc87361676a95a12558c6f"
    "2e88249396a20be5ef44af524abaa420e981137bfb69e58c2a1744f5f193bf409";
static const char kSigLong[] =
    "eb34ea43b3b46beb78e8a656e5d575b23d37050e5be65a28de3cd7ae996506"
    "4de3ff1683aba6d56278a19f225ead0083b2fbb57034b8fe6e5300a0b350d28200";

int main(void) {
    unsigned char pub[32];
    unsigned char sig[64];
    unsigned char msg[1024];
    unsigned char bad[64];
    unsigned char digest[64];
    ed_sha c;
    unsigned i;
    static const char abcWant[] =
        "ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a"
        "2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f";
    unsigned char abc[64];
    unhex(abc, abcWant, 64);
    ed_sha512_init(&c);
    ed_sha512_update(&c, (const unsigned char *)"abc", 3ul);
    ed_sha512_final(&c, digest);
    CHECK(memcmp(digest, abc, 64) == 0, "sha512 abc");
    ed_sha512_init(&c);
    ed_sha512_update(&c, (const unsigned char *)"abc", 2ul);
    ed_sha512_update(&c, (const unsigned char *)"c", 1ul);
    ed_sha512_final(&c, digest);
    CHECK(memcmp(digest, abc, 64) == 0, "sha512 split");
    CHECK(sign_pubkey(0) != 0, "dev slot present");
    CHECK(sign_pubkey(1) == 0, "prod slot refused while zero");
    CHECK(sign_pubkey(7) == 0, "unknown slot refused");
    unhex(pub, kPub, 32);
    CHECK(memcmp(sign_pubkey(0), pub, 32) == 0, "dev key pinned");
    unhex(sig, kSigEmpty, 64);
    CHECK(ed25519_verify(sig, msg, 0, pub) == 1, "empty verifies");
    memcpy(msg, "miniOS-sign-test", 16);
    unhex(sig, kSigShort, 64);
    CHECK(ed25519_verify(sig, msg, 16, pub) == 1, "short verifies");
    for (i = 0; i < 1024u; i++)
        msg[i] = (unsigned char)(i & 255u);
    unhex(sig, kSigLong, 64);
    CHECK(ed25519_verify(sig, msg, 1024, pub) == 1, "long verifies");
    memcpy(bad, sig, 64);
    bad[0] ^= 1;
    CHECK(ed25519_verify(bad, msg, 1024, pub) == 0, "flipped R refused");
    memcpy(bad, sig, 64);
    bad[63] ^= 4;
    CHECK(ed25519_verify(bad, msg, 1024, pub) == 0, "flipped S refused");
    msg[7] ^= 1;
    CHECK(ed25519_verify(sig, msg, 1024, pub) == 0, "flipped msg refused");
    msg[7] ^= 1;
    {
        unsigned char pub2[32];
        memcpy(pub2, pub, 32);
        pub2[0] ^= 1;
        CHECK(ed25519_verify(sig, msg, 1024, pub2) == 0, "flipped key refused");
    }
    {
        unsigned char bigS[64];
        memcpy(bigS, sig, 64);
        memset(bigS + 32, 0xff, 32);
        CHECK(ed25519_verify(bigS, msg, 1024, pub) == 0, "S all-ff refused");
    }
    {
        unsigned char bigS[64];
        static const char lStr[] =
            "edd3f55c1a631258d69cf7a2def9de1400000000000000000000000000000010";
        unsigned char lb[32];
        memcpy(bigS, sig, 64);
        unhex(lb, lStr, 32);
        memcpy(bigS + 32, lb, 32);
        CHECK(ed25519_verify(bigS, msg, 1024, pub) == 0, "S equals L refused");
    }
    {
        unsigned char shortSig[64];
        unsigned char plusS[64];
        unsigned char shortMsg[16];
        static const char sPlusL[] =
            "d5563f968483d0b6cae7ecc789a42123981137bfb69e58c2a1744f5f193bf419";
        unhex(shortSig, kSigShort, 64);
        memcpy(shortMsg, "miniOS-sign-test", 16);
        CHECK(ed25519_verify(shortSig, shortMsg, 16, pub) == 1, "short recheck");
        memcpy(plusS, shortSig, 32);
        unhex(plusS + 32, sPlusL, 32);
        CHECK(ed25519_verify(plusS, shortMsg, 16, pub) == 0, "S plus L refused");
    }
    {
        unsigned char bigR[64];
        unsigned char q[32];
        memcpy(bigR, sig, 64);
        memset(q, 0xff, 32);
        q[0] = 0xed;
        q[31] = 0x7f;
        memcpy(bigR, q, 32);
        CHECK(ed25519_verify(bigR, msg, 1024, pub) == 0, "R equals q refused");
    }
    CHECK(ed25519_verify(sig, msg, 1023, pub) == 0, "short len refused");
    CHECK(ed25519_verify(0, msg, 1024, pub) == 0, "null sig refused");
    CHECK(ed25519_verify(sig, 0, 1024, pub) == 0, "null msg refused");
    CHECK(ed25519_verify(sig, msg, 1024, 0) == 0, "null key refused");
    if (failures) {
        fprintf(stderr, "sign: %d failures\n", failures);
        return 1;
    }
    printf("sign: ok\n");
    return 0;
}
