/** Docstring: sign.h -- MiniOS binary signing contract.
 *
 * Single source of truth for the Ed25519 code-signing gate
 * (docs/spec/kernel.md, signed binaries): note layout, key ids, the
 * development public key and the verifier entry points implemented in
 * kernel/ed25519.c. Header-only like pipe.h over the constants; the
 * crypto itself lives in kernel/ed25519.c so the kernel link and the
 * host suite share one source.
 *
 * Trust model: key id 0 is the public development key below, whose
 * private half is a published test seed (tools/sign_elf.py) for
 * dogfood builds only. Key id 1 is the production slot, provisioned
 * out of band; a zero slot refuses every image. Images without a
 * signature note or with a bad signature never execute. */

#ifndef SIGN_H
#define SIGN_H

#define SIGN_KEY_DEV 0u
#define SIGN_KEY_PROD 1u
#define SIGN_KEYS 2u
#define SIGN_PUB_BYTES 32u
#define SIGN_SIG_BYTES 64u
#define SIGN_DESC_BYTES 65u
#define SIGN_NOTE_TYPE 2u

/** Docstring: Development public key for key id 0. Test key only,
 * derived from the published seed in tools/sign_elf.py. */
static const unsigned char sign_pub_dev[SIGN_PUB_BYTES] = {
    0xdf, 0x96, 0x8c, 0x9d, 0x64, 0x69, 0x53, 0xed,
    0xed, 0x22, 0xba, 0xb2, 0x08, 0x66, 0x9c, 0xb7,
    0xec, 0x1a, 0x94, 0xe3, 0x2b, 0xe5, 0xeb, 0xeb,
    0x95, 0xb3, 0xae, 0xac, 0xb8, 0xd7, 0x56, 0x1e
};

/** Docstring: Production public key for key id 1. Zero until
 * provisioned; the loader refuses the slot while it is zero. */
static const unsigned char sign_pub_prod[SIGN_PUB_BYTES] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

/** Docstring: Look up the trusted public key for a key id.
 * Answers 0 for unknown ids and for the unprovisioned slot. */
static inline const unsigned char *sign_pubkey(unsigned id) {
    unsigned i;
    if (id == SIGN_KEY_DEV)
        return sign_pub_dev;
    if (id == SIGN_KEY_PROD) {
        for (i = 0; i < SIGN_PUB_BYTES; i++) {
            if (sign_pub_prod[i])
                return sign_pub_prod;
        }
        return 0;
    }
    return 0;
}

typedef struct {
    unsigned long long h[8];
    unsigned char buf[128];
    unsigned long long lo;
    unsigned long long hi;
    unsigned used;
} ed_sha;

void ed_sha512_init(ed_sha *c);
void ed_sha512_update(ed_sha *c, const unsigned char *data, unsigned long len);
void ed_sha512_final(ed_sha *c, unsigned char out[64]);

/** Docstring: Verify an Ed25519 signature, 1 valid else 0.
 * See kernel/ed25519.c for the full contract. */
int ed25519_verify(const unsigned char sig[64], const unsigned char *msg,
                   unsigned long msglen, const unsigned char pub[32]);

#endif
