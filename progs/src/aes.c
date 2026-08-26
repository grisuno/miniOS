/* aes.c - command path AES-256-CTR encryption tools: aes and unaes.
 * One source builds both binaries; the linker emits the same program as
 * bin/aes and bin/unaes and the program picks its mode from argv[0] (any
 * invocation path containing "unaes" decrypts, and -d forces decrypt).
 *
 * The cipher is AES-256 (NIST FIPS-197) written in the miniGCC subset: no
 * structs, flat int arrays masked to bytes on every step, and an S-box
 * generated procedurally from the GF(2^8) multiplicative inverse plus the
 * FIPS-197 affine transform, so the file carries no magic tables.  The mode
 * is CTR (NIST SP 800-38A): no padding, encrypt and decrypt share one code
 * path, and a nonce must never repeat under the same key.
 *
 * The container is fail-closed: 4-byte magic "AES1", the original size as a
 * little-endian u32, then the raw keystream XOR.  Decoding refuses a bad
 * magic, a truncated header, and any body whose length does not equal the
 * declared size exactly.  CTR provides confidentiality only, not
 * authentication: a flipped ciphertext byte flips the matching plaintext
 * byte, so integrity needs a MAC layered above this tool.
 *
 * Usage: aes [-d] <key-hex64> <nonce-hex32> <src> <dst>
 *        unaes <key-hex64> <nonce-hex32> <src> <dst>
 */

int printf();
int putchar();
int strcmp();
int strlen();
void *fopen();
int fclose();
int fread();
int fwrite();
int fseek();
int ftell();
void rewind();
void *malloc();
void free();

#define AES_MAGIC0 'A'
#define AES_MAGIC1 'E'
#define AES_MAGIC2 'S'
#define AES_MAGIC3 '1'
#define AES_HDR_SIZE 8

#define AES_BLOCK 16
#define AES_KEY_BYTES 32
#define AES_NONCE_BYTES 16
#define AES_ROUNDS 14
#define AES_RK_LEN ((AES_ROUNDS + 1) * AES_BLOCK)
#define AES_SBOX_SIZE 256
#define AES_RCON_SIZE 11

#define AES_POLY 0x11b
#define AES_AFFINE_C 0x63
#define AES_RCON_PAD 0x8d

#define HEX_KEY_LEN (AES_KEY_BYTES * 2)
#define HEX_NONCE_LEN (AES_NONCE_BYTES * 2)

#define AES_SEEK_END 2

#define AES_EXIT_FAIL 1

static int aes_rk[AES_RK_LEN];
static int aes_sb[AES_SBOX_SIZE];
static int aes_rc[AES_RCON_SIZE];
static int aes_st[AES_BLOCK];
static int aes_iv[AES_BLOCK];

static char *aes_read_all(const char *name, int *len) {
    char *data;
    int got;
    void *f = fopen((char *)name, "r");
    if (!f) return 0;
    fseek(f, 0, AES_SEEK_END);
    *len = ftell(f);
    rewind(f);
    if (*len < 0) { fclose(f); return 0; }
    data = malloc(*len > 0 ? *len : 1);
    if (!data) { fclose(f); return 0; }
    got = fread(data, 1, *len, f);
    fclose(f);
    if (got != *len) { free(data); return 0; }
    return data;
}

static int aes_write_all(const char *name, char *data, int len) {
    int n;
    void *f = fopen((char *)name, "w");
    if (!f) return 0;
    n = fwrite(data, 1, len, f);
    if (n != len) { fclose(f); return 0; }
    if (fclose(f) != 0) return 0;
    return 1;
}

static int aes_has(const char *s, const char *needle) {
    int i, j, n;
    n = strlen(needle);
    if (n <= 0) return 0;
    for (i = 0; s[i] != 0; i++) {
        for (j = 0; j < n; j++) {
            if (s[i + j] == 0) return 0;
            if (s[i + j] != needle[j]) break;
        }
        if (j == n) return 1;
    }
    return 0;
}

static int hex_val(int c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static int aes_parse_hex(const char *s, int want, int *out) {
    int i, hi, lo;
    if ((int)strlen(s) != want) return 0;
    for (i = 0; i < want; i += 2) {
        hi = hex_val(s[i]);
        lo = hex_val(s[i + 1]);
        if (hi < 0 || lo < 0) return 0;
        out[i / 2] = hi * 16 + lo;
    }
    return 1;
}

/* Multiply in GF(2^8) modulo the AES polynomial; both operands are 0..255. */
static int aes_gf_mul(int a, int b) {
    int p;
    p = 0;
    while (b > 0) {
        if ((b & 1) != 0) p = p ^ a;
        a = a << 1;
        if ((a & 256) != 0) a = a ^ AES_POLY;
        b = b >> 1;
    }
    return p & 255;
}

static int aes_xtime(int x) {
    x = x << 1;
    if ((x & 256) != 0) x = x ^ AES_POLY;
    return x & 255;
}

static int aes_rotl8(int x, int n) {
    return ((x << n) | (x >> (8 - n))) & 255;
}

/* Build the S-box from first principles: multiplicative inverse in GF(2^8)
 * composed with the FIPS-197 affine transform.  Zero maps straight to the
 * affine constant because 0 has no inverse. */
static void aes_init_tables(void) {
    int i, j, inv, s;
    aes_sb[0] = AES_AFFINE_C;
    for (i = 1; i < AES_SBOX_SIZE; i++) {
        inv = 0;
        for (j = 1; j < AES_SBOX_SIZE; j++) {
            if (aes_gf_mul(i, j) == 1) { inv = j; break; }
        }
        s = inv;
        for (j = 1; j <= 4; j++) s = s ^ aes_rotl8(inv, j);
        aes_sb[i] = s ^ AES_AFFINE_C;
    }
    aes_rc[0] = AES_RCON_PAD;
    for (i = 1; i < AES_RCON_SIZE; i++) aes_rc[i] = aes_xtime(aes_rc[i - 1]);
}

/* Expand the 32-byte key into AES_RK_LEN round-key bytes (FIPS-197 for
 * Nk=8, Nr=14: RotWord plus SubWord every Nk words, an extra SubWord pass
 * every Nk/2 words). */
static void aes_key_expand(const int *key) {
    int i, t0, t1, t2, t3, k, j;
    for (i = 0; i < AES_KEY_BYTES; i++) aes_rk[i] = key[i];
    for (i = AES_KEY_BYTES / 4; i < AES_RK_LEN / 4; i++) {
        k = (i - 1) * 4;
        t0 = aes_rk[k];
        t1 = aes_rk[k + 1];
        t2 = aes_rk[k + 2];
        t3 = aes_rk[k + 3];
        if ((i % 8) == 0) {
            j = t0;
            t0 = t1;
            t1 = t2;
            t2 = t3;
            t3 = j;
            t0 = aes_sb[t0] ^ aes_rc[i / 8];
            t1 = aes_sb[t1];
            t2 = aes_sb[t2];
            t3 = aes_sb[t3];
        }
        if ((i % 8) == 4) {
            t0 = aes_sb[t0];
            t1 = aes_sb[t1];
            t2 = aes_sb[t2];
            t3 = aes_sb[t3];
        }
        j = i * 4;
        k = (i - 8) * 4;
        aes_rk[j] = aes_rk[k] ^ t0;
        aes_rk[j + 1] = aes_rk[k + 1] ^ t1;
        aes_rk[j + 2] = aes_rk[k + 2] ^ t2;
        aes_rk[j + 3] = aes_rk[k + 3] ^ t3;
    }
}

static void aes_add_round_key(int round) {
    int i, base;
    base = round * AES_BLOCK;
    for (i = 0; i < AES_BLOCK; i++) aes_st[i] = (aes_st[i] ^ aes_rk[base + i]) & 255;
}

static void aes_sub_bytes(void) {
    int i;
    for (i = 0; i < AES_BLOCK; i++) aes_st[i] = aes_sb[aes_st[i]];
}

static void aes_shift_rows(void) {
    int t;
    t = aes_st[1]; aes_st[1] = aes_st[5]; aes_st[5] = aes_st[9]; aes_st[9] = aes_st[13]; aes_st[13] = t;
    t = aes_st[2]; aes_st[2] = aes_st[10]; aes_st[10] = t;
    t = aes_st[6]; aes_st[6] = aes_st[14]; aes_st[14] = t;
    t = aes_st[3]; aes_st[3] = aes_st[15]; aes_st[15] = aes_st[11]; aes_st[11] = aes_st[7]; aes_st[7] = t;
}

static void aes_mix_columns(void) {
    int c, t, m, tmp;
    for (c = 0; c < 4; c++) {
        t = aes_st[c * 4];
        tmp = aes_st[c * 4] ^ aes_st[c * 4 + 1] ^ aes_st[c * 4 + 2] ^ aes_st[c * 4 + 3];
        m = aes_st[c * 4] ^ aes_st[c * 4 + 1];
        m = aes_xtime(m);
        aes_st[c * 4] = (aes_st[c * 4] ^ tmp ^ m) & 255;
        m = aes_st[c * 4 + 1] ^ aes_st[c * 4 + 2];
        m = aes_xtime(m);
        aes_st[c * 4 + 1] = (aes_st[c * 4 + 1] ^ tmp ^ m) & 255;
        m = aes_st[c * 4 + 2] ^ aes_st[c * 4 + 3];
        m = aes_xtime(m);
        aes_st[c * 4 + 2] = (aes_st[c * 4 + 2] ^ tmp ^ m) & 255;
        m = aes_st[c * 4 + 3] ^ t;
        m = aes_xtime(m);
        aes_st[c * 4 + 3] = (aes_st[c * 4 + 3] ^ tmp ^ m) & 255;
    }
}

static void aes_cipher(void) {
    int r;
    aes_add_round_key(0);
    for (r = 1; r < AES_ROUNDS; r++) {
        aes_sub_bytes();
        aes_shift_rows();
        aes_mix_columns();
        aes_add_round_key(r);
    }
    aes_sub_bytes();
    aes_shift_rows();
    aes_add_round_key(AES_ROUNDS);
}

/* Big-endian increment of the whole counter block (SP 800-38A CTR). */
static void aes_iv_increment(void) {
    int b;
    for (b = AES_BLOCK - 1; b >= 0; b--) {
        aes_iv[b] = aes_iv[b] + 1;
        if (aes_iv[b] <= 255) break;
        aes_iv[b] = 0;
    }
}

/* XOR data in place with the keystream Cipher(nonce), Cipher(nonce+1)... */
static void aes_ctr_crypt(char *data, int len) {
    int i, j, bi;
    bi = AES_BLOCK;
    for (i = 0; i < len; i++) {
        if (bi == AES_BLOCK) {
            for (j = 0; j < AES_BLOCK; j++) aes_st[j] = aes_iv[j] & 255;
            aes_cipher();
            aes_iv_increment();
            bi = 0;
        }
        data[i] = (char)((data[i] & 255) ^ aes_st[bi]);
        bi++;
    }
}

static void aes_hdr_put(char *h, int size) {
    h[0] = AES_MAGIC0;
    h[1] = AES_MAGIC1;
    h[2] = AES_MAGIC2;
    h[3] = AES_MAGIC3;
    h[4] = (char)(size & 255);
    h[5] = (char)((size >> 8) & 255);
    h[6] = (char)((size >> 16) & 255);
    h[7] = (char)((size >> 24) & 255);
}

static int aes_hdr_get(char *h) {
    if (h[0] != AES_MAGIC0) return -1;
    if (h[1] != AES_MAGIC1) return -1;
    if (h[2] != AES_MAGIC2) return -1;
    if (h[3] != AES_MAGIC3) return -1;
    return (h[4] & 255) | ((h[5] & 255) << 8) | ((h[6] & 255) << 16) | ((h[7] & 255) << 24);
}

static const char *aes_tool_name(int decode) {
    if (decode) return "unaes";
    return "aes";
}

static int aes_run(int decode, const char *keyhex, const char *noncehex,
                   const char *src, const char *dst) {
    static int key[AES_KEY_BYTES];
    static int nonce[AES_NONCE_BYTES];
    char *data;
    int n;
    int size;
    if (!aes_parse_hex(keyhex, HEX_KEY_LEN, key)) {
        printf("%s: %s: key must be %d hex digits\n", aes_tool_name(decode), keyhex, HEX_KEY_LEN);
        return AES_EXIT_FAIL;
    }
    if (!aes_parse_hex(noncehex, HEX_NONCE_LEN, nonce)) {
        printf("%s: %s: nonce must be %d hex digits\n", aes_tool_name(decode), noncehex, HEX_NONCE_LEN);
        return AES_EXIT_FAIL;
    }
    aes_init_tables();
    aes_key_expand(key);
    for (n = 0; n < AES_NONCE_BYTES; n++) aes_iv[n] = nonce[n] & 255;
    data = aes_read_all(src, &n);
    if (!data) {
        printf("%s: cannot open %s\n", aes_tool_name(decode), src);
        return AES_EXIT_FAIL;
    }
    if (decode) {
        if (n < AES_HDR_SIZE) {
            free(data);
            printf("unaes: %s: truncated header\n", src);
            return AES_EXIT_FAIL;
        }
        size = aes_hdr_get(data);
        if (size < 0) {
            free(data);
            printf("unaes: %s: bad magic\n", src);
            return AES_EXIT_FAIL;
        }
        if (size != n - AES_HDR_SIZE) {
            free(data);
            printf("unaes: %s: size mismatch\n", src);
            return AES_EXIT_FAIL;
        }
        aes_ctr_crypt(data + AES_HDR_SIZE, size);
        if (!aes_write_all(dst, data + AES_HDR_SIZE, size)) {
            free(data);
            printf("unaes: cannot create %s\n", dst);
            return AES_EXIT_FAIL;
        }
        printf("unaes: %s -> %s (%d -> %d bytes)\n", src, dst, n, size);
    } else {
        char *out;
        int i;
        out = malloc(AES_HDR_SIZE + (n > 0 ? n : 1));
        if (!out) {
            free(data);
            printf("aes: out of memory\n");
            return AES_EXIT_FAIL;
        }
        for (i = 0; i < n; i++) out[i + AES_HDR_SIZE] = data[i];
        aes_hdr_put(out, n);
        aes_ctr_crypt(out + AES_HDR_SIZE, n);
        if (!aes_write_all(dst, out, AES_HDR_SIZE + n)) {
            free(data);
            free(out);
            printf("aes: cannot create %s\n", dst);
            return AES_EXIT_FAIL;
        }
        printf("aes: %s -> %s (%d -> %d bytes)\n", src, dst, n, n + AES_HDR_SIZE);
        free(out);
    }
    free(data);
    return 0;
}

int main(int argc, char **argv) {
    int decode;
    int a;
    decode = (argc >= 1 && aes_has(argv[0], "unaes"));
    a = 1;
    if (!decode && argc >= 2 && strcmp(argv[1], "-d") == 0) {
        decode = 1;
        a = 2;
    }
    if (argc - a != 4) {
        if (decode) printf("usage: unaes <key-hex64> <nonce-hex32> <src> <dst>\n");
        else printf("usage: aes [-d] <key-hex64> <nonce-hex32> <src> <dst>\n");
        return AES_EXIT_FAIL;
    }
    return aes_run(decode, argv[a], argv[a + 1], argv[a + 2], argv[a + 3]);
}
