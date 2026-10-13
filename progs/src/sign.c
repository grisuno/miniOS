/* sign.c - in-OS Ed25519 code signer for MiniOS secure boot.
 *
 * Signs ET_EXEC/ET_DYN binaries with the development key so the
 * kernel signature gate (docs/spec/kernel.md) executes them. Closes
 * the edit-compile-run loop: minigcc.o and ld.o outputs are born
 * unsigned and refused until this tool signs them.
 *
 * 32-bit miniGCC subset like aes.c: no structs, no 64-bit types,
 * flat unsigned int arrays, string-literal tables decoded at
 * startup. Field elements are eight little-endian u32 limbs with
 * products through 16-bit schoolbook rows and 38-folds, scalars
 * through binary long division. The development seed below is a
 * published test key for dogfood builds only.
 *
 * miniGCC codegen constraints honored throughout (all caught by the
 * `--selftest` differential vectors against python/PyNaCl, never by
 * review): `unsigned int` lives in 8-byte slots with 64-bit ops, so
 * a stale high half leaks into raw `>>` (sanitize with
 * `((v << 32) >> 32)` first; `&`-masked shifts like the hex printers
 * are safe as-is); ordering comparisons on full-range limbs are
 * replaced by full-adder/borrow forms; and pointer `p + N` adds raw
 * bytes while `a[i]` scales by 8, so extended-point limbs are
 * addressed only as `&p[N]`, never `p + N`.
 *
 * Usage: sign <file> [...]
 */

int printf();
int strcmp();
void *fopen();
int fclose();
int fread();
int fwrite();
int fseek();
int ftell();
void *malloc();
void free();

#define SIGN_KEY_ID 0
#define SIGN_EXIT_FAIL 1

#define SIGN_ET_EXEC 2
#define SIGN_ET_DYN 3
#define SIGN_EM_X86_64 62
#define SIGN_PT_LOAD 1
#define SIGN_PT_NOTE 4
#define SIGN_SHT_NOTE 7
#define SIGN_EHDR_SIZE 64
#define SIGN_PHDR_SIZE 56
#define SIGN_SHDR_SIZE 64
#define SIGN_NOTE_HDR 12
#define SIGN_DESC_BYTES 65
#define SIGN_SIG_BYTES 64
#define SIGN_NOTE_TOTAL 88
#define SIGN_NOTE_TYPE 2
#define SIGN_MAX_FILE (16 * 1024 * 1024)
#define SIGN_SEEK_END 2

static char sign_k0[] = "428a2f98d728ae227137449123ef65cdb5c0fbcfec4d3b2fe9b5dba58189dbbc3956c25bf348b53859f111f1b605d019923f82a4af194f9bab1c5ed5da6d8118d807aa98a303024212835b0145706fbe";
static char sign_k1[] = "243185be4ee4b28c550c7dc3d5ffb4e272be5d74f27b896f80deb1fe3b1696b19bdc06a725c71235c19bf174cf692694e49b69c19ef14ad2efbe4786384f25e30fc19dc68b8cd5b5240ca1cc77ac9c65";
static char sign_k2[] = "2de92c6f592b02754a7484aa6ea6e4835cb0a9dcbd41fbd476f988da831153b5983e5152ee66dfaba831c66d2db43210b00327c898fb213fbf597fc7beef0ee4c6e00bf33da88fc2d5a79147930aa725";
static char sign_k3[] = "06ca6351e003826f142929670a0e6e7027b70a8546d22ffc2e1b21385c26c9264d2c6dfc5ac42aed53380d139d95b3df650a73548baf63de766a0abb3c77b2a881c2c92e47edaee692722c851482353b";
static char sign_k4[] = "a2bfe8a14cf10364a81a664bbc423001c24b8b70d0f89791c76c51a30654be30d192e819d6ef5218d69906245565a910f40e35855771202a106aa07032bbd1b819a4c116b8d2d0c81e376c085141ab53";
static char sign_k5[] = "2748774cdf8eeb9934b0bcb5e19b48a8391c0cb3c5c95a634ed8aa4ae3418acb5b9cca4f7763e373682e6ff3d6b2b8a3748f82ee5defb2fc78a5636f43172f6084c87814a1f0ab728cc702081a6439ec";
static char sign_k6[] = "90befffa23631e28a4506cebde82bde9bef9a3f7b2c67915c67178f2e372532bca273eceea26619cd186b8c721c0c207eada7dd6cde0eb1ef57d4f7fee6ed17806f067aa72176fba0a637dc5a2c898a6";
static char sign_k7[] = "113f9804bef90dae1b710b35131c471b28db77f523047d8432caab7b40c724933c9ebe0a15c9bebc431d67c49c100d4c4cc5d4becb3e42b6597f299cfc657e2a5fcb6fab3ad6faec6c44198c4a475817";
static char sign_seed_hex[] = "ff0af8f46894a8f3949ff263703c48a01530e8ce42335bcd33fb0cffa4df704d";
static char sign_bx_hex[] = "216936d3cd6e53fec0a4e231fdd6dc5c692cc7609525a7b2c9562d608f25d51a";
static char sign_by_hex[] = "6666666666666666666666666666666666666666666666666666666666666658";
static char sign_ax_hex[] = "1aa42df16b69c861db1b83d0e94c277e2772d28c6370cabb91fcf7258dc34580";
static char sign_ay_hex[] = "1e56d7b8acaeb395ebebe52be3941aecb79c6608b2ba22eded5369649d8c96df";
static char sign_pub_hex[] = "df968c9d646953eded22bab208669cb7ec1a94e32be5ebeb95b3aeacb8d7561e";
static char sign_note_name[] = "MiniOS";
static char sign_section_name[] = ".note.minios.sign";

static unsigned int sign_k[160];
static unsigned int sign_h[16];
static unsigned int sign_w[160];
static char sign_buf[128];
static int sign_used;
static unsigned int sign_nlo;
static unsigned int sign_nhi;
static unsigned int sign_q4[8];
static unsigned int sign_l8[8];
static unsigned int sign_gb[32];
static unsigned int sign_ga[32];

/** Docstring: Hex digit value, 0 outside hex. */
static unsigned int sign_hexval(char c) {
    if (c >= 48 && c <= 57)
        return (unsigned int)(c - 48);
    if (c >= 97 && c <= 102)
        return (unsigned int)(c - 97 + 10);
    if (c >= 65 && c <= 70)
        return (unsigned int)(c - 65 + 10);
    return 0;
}

/** Docstring: Decode 2*n hex chars into n bytes. */
static void sign_unhex(char *out, char *in, int n) {
    int i = 0;
    while (i < n) {
        unsigned int hi = sign_hexval(in[2 * i]);
        unsigned int lo = sign_hexval(in[2 * i + 1]);
        out[i] = (char)((hi << 4) | lo);
        i++;
    }
}

/** Docstring: Unsigned byte at index, the aes.c masking idiom. */
static unsigned int sign_byte(char *p, int i) {
    int v = p[i];
    if (v < 0)
        v = v + 256;
    return (unsigned int)v;
}

/** Docstring: Copy n bytes. */
static void sign_copy(char *dst, char *src, int n) {
    int i = 0;
    while (i < n) {
        dst[i] = src[i];
        i++;
    }
}

/** Docstring: String length. */
static int sign_strlen(char *s) {
    int n = 0;
    while (s[n] != 0)
        n = n + 1;
    return n;
}

/** Docstring: Little-endian u16 at offset. */
static unsigned int sign_le16(char *p, int off) {
    return sign_byte(p, off) | (sign_byte(p, off + 1) << 8);
}

/** Docstring: Little-endian u32 at offset. */
static unsigned int sign_le32(char *p, int off) {
    return sign_byte(p, off) | (sign_byte(p, off + 1) << 8) |
           (sign_byte(p, off + 2) << 16) | (sign_byte(p, off + 3) << 24);
}

/** Docstring: Store u32 little-endian. */
static void sign_put32(char *p, int off, unsigned int v) {
    p[off] = (char)(v & 255);
    p[off + 1] = (char)((v >> 8) & 255);
    p[off + 2] = (char)((v >> 16) & 255);
    p[off + 3] = (char)((v >> 24) & 255);
}

/** Docstring: Emit bytes as lowercase hex into out.
 *
 * Dirt-safe under miniGCC's 8-byte slots: `sign_byte` returns a
 * clean 0..255 and every shift below is masked to its nibble, so a
 * stale high half can never reach the output (all selftest prints
 * rely on this). */
static void sign_hexout(char *out, char *bin, int n) {
    int i = 0;
    while (i < n) {
        unsigned int v = sign_byte(bin, i);
        unsigned int hi = (v >> 4) & 15;
        unsigned int lo = v & 15;
        if (hi < 10)
            out[2 * i] = (char)(48 + hi);
        else
            out[2 * i] = (char)(87 + hi);
        if (lo < 10)
            out[2 * i + 1] = (char)(48 + lo);
        else
            out[2 * i + 1] = (char)(87 + lo);
        i = i + 1;
    }
    out[2 * n] = 0;
}

/** Docstring: Load a file offset field, refusing high parts. */
static int sign_offok(char *p, int off, int *lo) {
    unsigned int hi = sign_le32(p, off + 4);
    if (hi != 0)
        return 0;
    *lo = (int)sign_le32(p, off);
    return 1;
}

/** Docstring: Rotate a 64-bit pair right by n, n below 64.
 *
 * The entry sanitize matters: miniGCC keeps `unsigned int` locals in
 * 8-byte stack slots with 64-bit loads/stores, so a slot's high half
 * holds stale garbage and a raw 64-bit `>>` leaks it into the result
 * (caught by the EZT vector: `y1 >> 6` gained bit 28). Shifting left
 * by 32 then right by 32 clears the high half with exact operations;
 * every other op below (`|`, `<<`) is low-32 exact. */
static void sign_rotr(unsigned int *lo, unsigned int *hi, int n) {
    unsigned int a = ((*lo << 32) >> 32);
    unsigned int b = ((*hi << 32) >> 32);
    int k = n;
    if (k >= 32) {
        a = ((*hi << 32) >> 32);
        b = ((*lo << 32) >> 32);
        k = k - 32;
    }
    if (k == 0) {
        *lo = a;
        *hi = b;
        return;
    }
    *lo = (a >> k) | (b << (32 - k));
    *hi = (b >> k) | (a << (32 - k));
}

/** Docstring: Carry out of x plus y into s, without comparisons.
 *
 * miniGCC keeps `unsigned int` in 8-byte slots with 64-bit ops, so
 * ordering comparisons misfire on stale high halves (the ADD3-CY
 * vector caught the first one) and a raw `>> 31` leaks a dirty high
 * half into bit 0 (the EZT vector). The full-adder form uses only
 * low-32-exact ops, and the final `<< 32 >> 63` (both counts below
 * 64) extracts bit 31 with a zero high half. */
static unsigned int sign_carry2(unsigned int x, unsigned int y, unsigned int s) {
    unsigned int t = (x & y) | ((x ^ y) & ~s);
    t = (t << 32) >> 32;
    return (t >> 31) & 1;
}

/** Docstring: Borrow out of x minus y into s, without comparisons.
 * Same miniGCC rationale as sign_carry2: sanitize before shifting. */
static unsigned int sign_borrow2(unsigned int x, unsigned int y, unsigned int s) {
    unsigned int t = (~x & y) | ((~(x ^ y)) & s);
    t = (t << 32) >> 32;
    return (t >> 31) & 1;
}

/** Docstring: Add three words with carry, returning the new carry. */
static unsigned int sign_add3(unsigned int *s, unsigned int a, unsigned int b, unsigned int c) {
    unsigned int t = a + b;
    unsigned int cy = sign_carry2(a, b, t);
    unsigned int u = t + c;
    cy = cy + sign_carry2(t, c, u);
    *s = u;
    return cy;
}

/** Docstring: Big-endian u32 at byte offset. */
static unsigned int sign_be32(char *p, int off) {
    return (sign_byte(p, off) << 24) | (sign_byte(p, off + 1) << 16) |
           (sign_byte(p, off + 2) << 8) | sign_byte(p, off + 3);
}

/** Docstring: One SHA-512 compression over the 128-byte buffer. */
static void sign_block(void) {
    unsigned int st[16];
    int i = 0;
    while (i < 16) {
        int k = i * 8;
        sign_w[2 * i] = sign_be32(sign_buf, k + 4);
        sign_w[2 * i + 1] = sign_be32(sign_buf, k);
        i = i + 1;
    }
    i = 16;
    while (i < 80) {
        unsigned int x0 = sign_w[2 * (i - 15)];
        unsigned int x1 = sign_w[2 * (i - 15) + 1];
        unsigned int y0 = sign_w[2 * (i - 2)];
        unsigned int y1 = sign_w[2 * (i - 2) + 1];
        unsigned int r0 = 0;
        unsigned int r1 = 0;
        unsigned int a0 = 0;
        unsigned int a1 = 0;
        unsigned int q0 = 0;
        unsigned int q1 = 0;
        unsigned int b0 = 0;
        unsigned int b1 = 0;
        unsigned int s0 = 0;
        unsigned int s1 = 0;
        unsigned int cy = 0;
        x0 = (x0 << 32) >> 32;
        x1 = (x1 << 32) >> 32;
        y0 = (y0 << 32) >> 32;
        y1 = (y1 << 32) >> 32;
        r0 = x0;
        r1 = x1;
        a0 = x0;
        a1 = x1;
        q0 = y0;
        q1 = y1;
        b0 = y0;
        b1 = y1;
        sign_rotr(&r0, &r1, 1);
        sign_rotr(&a0, &a1, 8);
        s0 = r0 ^ a0 ^ ((x1 << 25) | (x0 >> 7));
        s1 = r1 ^ a1 ^ (x1 >> 7);
        sign_rotr(&q0, &q1, 19);
        sign_rotr(&b0, &b1, 61);
            q0 = q0 ^ b0 ^ ((y1 << 26) | (y0 >> 6));
            {
                unsigned int tA = y1 >> 6;
                q1 = q1 ^ b1;
                q1 = q1 ^ tA;
            }
        cy = sign_add3(&s0, sign_w[2 * (i - 16)], s0, q0);
        cy = cy + sign_add3(&s0, s0, sign_w[2 * (i - 7)], 0);
        s1 = sign_w[2 * (i - 16) + 1] + s1 + q1 + sign_w[2 * (i - 7) + 1] + cy;
        sign_w[2 * i] = s0;
        sign_w[2 * i + 1] = s1;
        i++;
    }
    i = 0;
    while (i < 16) {
        st[i] = sign_h[i];
        i++;
    }
    i = 0;
    while (i < 80) {
        unsigned int e0 = st[8];
        unsigned int e1 = st[9];
        unsigned int r0 = e0;
        unsigned int r1 = e1;
        unsigned int a0 = e0;
        unsigned int a1 = e1;
        unsigned int v0 = e0;
        unsigned int v1 = e1;
        unsigned int chl = (e0 & st[10]) ^ (~e0 & st[12]);
        unsigned int chh = (e1 & st[11]) ^ (~e1 & st[13]);
        unsigned int u0 = st[0];
        unsigned int u1 = st[1];
        unsigned int q0 = st[0];
        unsigned int q1 = st[1];
        unsigned int w0 = st[0];
        unsigned int w1 = st[1];
        unsigned int mjl = (st[0] & st[2]) ^ (st[0] & st[4]) ^ (st[2] & st[4]);
        unsigned int mjh = (st[1] & st[3]) ^ (st[1] & st[5]) ^ (st[3] & st[5]);
        unsigned int t1l = 0;
        unsigned int t1h = 0;
        unsigned int t2l = 0;
        unsigned int t2h = 0;
        unsigned int cy = 0;
        sign_rotr(&r0, &r1, 14);
        sign_rotr(&a0, &a1, 18);
        sign_rotr(&v0, &v1, 41);
        r0 = r0 ^ a0 ^ v0;
        r1 = r1 ^ a1 ^ v1;
        sign_rotr(&u0, &u1, 28);
        sign_rotr(&q0, &q1, 34);
        sign_rotr(&w0, &w1, 39);
        u0 = u0 ^ q0 ^ w0;
        u1 = u1 ^ q1 ^ w1;
        cy = sign_add3(&t1l, st[14], r0, chl);
        cy = cy + sign_add3(&t1l, t1l, sign_k[2 * i], sign_w[2 * i]);
        t1h = st[15] + r1 + chh + sign_k[2 * i + 1] + sign_w[2 * i + 1] + cy;
        cy = sign_add3(&t2l, u0, mjl, 0);
        t2h = u1 + mjh + cy;
        st[14] = st[12];
        st[15] = st[13];
        st[12] = st[10];
        st[13] = st[11];
        st[10] = e0;
        st[11] = e1;
        cy = sign_add3(&st[8], st[6], t1l, 0);
        st[9] = st[7] + t1h + cy;
        st[6] = st[4];
        st[7] = st[5];
        st[4] = st[2];
        st[5] = st[3];
        st[2] = st[0];
        st[3] = st[1];
        cy = sign_add3(&st[0], t1l, t2l, 0);
        st[1] = t1h + t2h + cy;
        i++;
    }
    i = 0;
    while (i < 16) {
        unsigned int n = sign_h[i] + st[i];
        unsigned int cy = 0;
        cy = sign_carry2(sign_h[i], st[i], n);
        sign_h[i] = n;
        i++;
        n = sign_h[i] + st[i] + cy;
        sign_h[i] = n;
        i++;
    }
}

/** Docstring: Start a SHA-512 digest. */
static void sign_sha_init(void) {
    sign_h[0] = 0xf3bcc908;
    sign_h[1] = 0x6a09e667;
    sign_h[2] = 0x84caa73b;
    sign_h[3] = 0xbb67ae85;
    sign_h[4] = 0xfe94f82b;
    sign_h[5] = 0x3c6ef372;
    sign_h[6] = 0x5f1d36f1;
    sign_h[7] = 0xa54ff53a;
    sign_h[8] = 0xade682d1;
    sign_h[9] = 0x510e527f;
    sign_h[10] = 0x2b3e6c1f;
    sign_h[11] = 0x9b05688c;
    sign_h[12] = 0xfb41bd6b;
    sign_h[13] = 0x1f83d9ab;
    sign_h[14] = 0x137e2179;
    sign_h[15] = 0x5be0cd19;
    sign_nlo = 0;
    sign_nhi = 0;
    sign_used = 0;
}

/** Docstring: Feed bytes into the running digest. */
static void sign_sha_update(char *data, int len) {
    int i = 0;
    unsigned int bits = (unsigned int)len << 3;
    unsigned int nlo = sign_nlo + bits;
    if (nlo < sign_nlo)
        sign_nhi = sign_nhi + 1;
    sign_nlo = nlo;
    sign_nhi = sign_nhi + ((unsigned int)len >> 29);
    while (i < len) {
        int take = 128 - sign_used;
        int left = len - i;
        int k = 0;
        if (take > left)
            take = left;
        while (k < take) {
            sign_buf[sign_used + k] = data[i + k];
            k = k + 1;
        }
        sign_used = sign_used + take;
        i = i + take;
        if (sign_used == 128) {
            sign_block();
            sign_used = 0;
        }
    }
}

/** Docstring: Finish the digest into 64 bytes.
 *
 * The bit counter never exceeds 2^27 (files cap at 16 MB), so the
 * high length word is constant zero and only safe sub-32 shifts
 * appear below. */
static void sign_sha_final(char *out) {
    int k = 0;
    int i = 0;
    sign_buf[sign_used] = (char)128;
    sign_used = sign_used + 1;
    if (sign_used > 112) {
        while (sign_used < 128) {
            sign_buf[sign_used] = 0;
            sign_used = sign_used + 1;
        }
        sign_block();
        sign_used = 0;
    }
    while (sign_used < 112) {
        sign_buf[sign_used] = 0;
        sign_used = sign_used + 1;
    }
    while (k < 8) {
        sign_buf[112 + k] = 0;
        k = k + 1;
    }
    k = 0;
    while (k < 4) {
        sign_buf[120 + k] = 0;
        k = k + 1;
    }
    while (k < 8) {
        sign_buf[120 + k] = (char)((sign_nlo >> (56 - 8 * k)) & 255);
        k = k + 1;
    }
    sign_block();
    while (i < 8) {
        int b = i * 8;
        int s = 0;
        while (s < 8) {
            int ww = 0;
            if (s < 4)
                ww = (int)((sign_h[2 * i + 1] >> (24 - 8 * s)) & 255);
            else
                ww = (int)((sign_h[2 * i] >> (56 - 8 * s)) & 255);
            out[b + s] = (char)ww;
            s = s + 1;
        }
        i = i + 1;
    }
}

/** Docstring: Feed a u32 into the digest little-endian. */
static void sign_feed32(unsigned int v) {
    char b[4];
    b[0] = (char)(v & 255);
    b[1] = (char)((v >> 8) & 255);
    b[2] = (char)((v >> 16) & 255);
    b[3] = (char)((v >> 24) & 255);
    sign_sha_update(b, 4);
}

/** Docstring: Decode the K table chunks into 160 words. */
static void sign_key_init(void) {
    char tmp[80];
    int c = 0;
    while (c < 8) {
        char *src = sign_k0;
        int i = 0;
        if (c == 1)
            src = sign_k1;
        if (c == 2)
            src = sign_k2;
        if (c == 3)
            src = sign_k3;
        if (c == 4)
            src = sign_k4;
        if (c == 5)
            src = sign_k5;
        if (c == 6)
            src = sign_k6;
        if (c == 7)
            src = sign_k7;
        sign_unhex(tmp, src, 80);
        while (i < 10) {
            unsigned int lo = sign_be32(tmp, 8 * i + 4);
            unsigned int hi = sign_be32(tmp, 8 * i);
            sign_k[c * 20 + 2 * i] = lo;
            sign_k[c * 20 + 2 * i + 1] = hi;
            i = i + 1;
        }
        c = c + 1;
    }
    sign_q4[0] = 4294967277;
    sign_q4[1] = 4294967295;
    sign_q4[2] = 4294967295;
    sign_q4[3] = 4294967295;
    sign_q4[4] = 4294967295;
    sign_q4[5] = 4294967295;
    sign_q4[6] = 4294967295;
    sign_q4[7] = 2147483647;
    sign_l8[0] = 1559614445;
    sign_l8[1] = 1477600026;
    sign_l8[2] = 2734136534;
    sign_l8[3] = 350157278;
    sign_l8[4] = 0;
    sign_l8[5] = 0;
    sign_l8[6] = 0;
    sign_l8[7] = 268435456;
}

/** Docstring: Copy eight limbs. */
static void fe_copy(unsigned int *r, unsigned int *a) {
    int i = 0;
    while (i < 8) {
        r[i] = a[i];
        i = i + 1;
    }
}

/** Docstring: Zero eight limbs. */
static void fe_zero(unsigned int *r) {
    int i = 0;
    while (i < 8) {
        r[i] = 0;
        i = i + 1;
    }
}

/** Docstring: One as eight limbs. */
static void fe_one(unsigned int *r) {
    fe_zero(r);
    r[0] = 1;
}

/** Docstring: Masked select between limb arrays, no secret branches. */
static void fe_cmov(unsigned int *r, unsigned int *b, unsigned int flag) {
    unsigned int m = 0 - (flag & 1);
    int i = 0;
    while (i < 8) {
        r[i] = r[i] ^ (m & (r[i] ^ b[i]));
        i = i + 1;
    }
}

/** Docstring: 1 when a holds at least b, else 0.
 *
 * Runs the subtraction limb by limb and returns the inverted final
 * borrow, so no ordering comparison touches full-range limbs. */
static unsigned int fe_ge(unsigned int *a, unsigned int *b) {
    unsigned int borrow = 0;
    int i = 0;
    while (i < 8) {
        unsigned int t1 = a[i] - borrow;
        unsigned int c0 = sign_borrow2(a[i], borrow, t1);
        unsigned int t2 = t1 - b[i];
        unsigned int c1 = sign_borrow2(t1, b[i], t2);
        borrow = c0 | c1;
        i = i + 1;
    }
    return borrow ^ 1;
}

/** Docstring: Raw subtract, caller guarantees no borrow out. */
static void fe_rawsub(unsigned int *r, unsigned int *a, unsigned int *b) {
    unsigned int borrow = 0;
    int i = 0;
    while (i < 8) {
        unsigned int ai = a[i];
        unsigned int t1 = ai - borrow;
        unsigned int c0 = sign_borrow2(ai, borrow, t1);
        unsigned int t2 = t1 - b[i];
        unsigned int c1 = sign_borrow2(t1, b[i], t2);
        r[i] = t2;
        borrow = c0 | c1;
        i = i + 1;
    }
}

/** Docstring: Add mod q with one conditional subtract. */
static void fe_add(unsigned int *r, unsigned int *a, unsigned int *b) {
    unsigned int carry = 0;
    unsigned int t[8];
    int i = 0;
    while (i < 8) {
        unsigned int s1 = a[i] + b[i];
        unsigned int c0 = sign_carry2(a[i], b[i], s1);
        unsigned int s2 = s1 + carry;
        unsigned int c1 = sign_carry2(s1, carry, s2);
        t[i] = s2;
        carry = c0 | c1;
        i = i + 1;
    }
    if (carry == 1 || fe_ge(t, sign_q4) == 1)
        fe_rawsub(t, t, sign_q4);
    fe_copy(r, t);
}

/** Docstring: Subtract mod q with borrow folded back. */
static void fe_sub(unsigned int *r, unsigned int *a, unsigned int *b) {
    unsigned int borrow = 0;
    unsigned int t[8];
    int i = 0;
    while (i < 8) {
        unsigned int ai = a[i];
        unsigned int t1 = ai - borrow;
        unsigned int c0 = sign_borrow2(ai, borrow, t1);
        unsigned int t2 = t1 - b[i];
        unsigned int c1 = sign_borrow2(t1, b[i], t2);
        t[i] = t2;
        borrow = c0 | c1;
        i = i + 1;
    }
    if (borrow == 1) {
        unsigned int carry = 0;
        i = 0;
        while (i < 8) {
            unsigned int s1 = t[i] + sign_q4[i];
            unsigned int c0 = sign_carry2(t[i], sign_q4[i], s1);
            unsigned int s2 = s1 + carry;
            unsigned int c1 = sign_carry2(s1, carry, s2);
            t[i] = s2;
            carry = c0 | c1;
            i = i + 1;
        }
    }
    fe_copy(r, t);
}

/** Docstring: Add a sub-2^32 value into a 16-bit row, rippling carries.
 *
 * Row limbs stay below 2^16: each step keeps the low 16 bits and
 * carries the rest, so no bit is ever dropped or double counted.
 * Both inputs are sanitized first: with miniGCC's 8-byte slots a
 * raw `>> 16` would leak a stale high half into the carry. True
 * values here always fit 32 bits (limbs below 2^16, carries and
 * products below 2^32), so the sanitize is exact. */
static void fe_rowadd(unsigned int *row, int at, unsigned int v) {
    int i = at;
    unsigned int carry = 0;
    carry = (v << 32) >> 32;
    while (i < 32 && carry != 0) {
        unsigned int rv = 0;
        unsigned int s = 0;
        rv = (row[i] << 32) >> 32;
        s = rv + carry;
        row[i] = s & 65535;
        carry = s >> 16;
        i = i + 1;
    }
}

/** Docstring: Fold 38 times a sub-2^16 limb into a 16-bit row. */
static void fe_foldadd(unsigned int *row, int at, unsigned int x) {
    unsigned int v = (x << 5) + (x << 2) + (x << 1);
    fe_rowadd(row, at, v);
}

/** Docstring: Multiply mod q through 16-bit rows and 38-folds. */
static void fe_mul(unsigned int *r, unsigned int *a, unsigned int *b) {
    unsigned int x[16];
    unsigned int y[16];
    unsigned int acc[32];
    int i = 0;
    int j = 0;
    int k = 0;
    int round = 0;
    while (i < 8) {
        x[2 * i] = a[i] & 65535;
        x[2 * i + 1] = (a[i] >> 16) & 65535;
        y[2 * i] = b[i] & 65535;
        y[2 * i + 1] = (b[i] >> 16) & 65535;
        i = i + 1;
    }
    while (k < 32) {
        acc[k] = 0;
        k = k + 1;
    }
    i = 0;
    while (i < 16) {
        j = 0;
        while (j < 16) {
            unsigned int p = x[i] * y[j];
            fe_rowadd(acc, i + j, p);
            j = j + 1;
        }
        i = i + 1;
    }
    while (round < 16) {
        int t = 0;
        int any = 0;
        while (t < 16) {
            if (acc[t + 16] != 0)
                any = 1;
            t = t + 1;
        }
        if (any == 0)
            break;
        t = 0;
        while (t < 16) {
            unsigned int hi = acc[t + 16];
            acc[t + 16] = 0;
            fe_foldadd(acc, t, hi);
            t = t + 1;
        }
        round = round + 1;
    }
    {
        unsigned int t[8];
        unsigned int back[8];
        i = 0;
        while (i < 8) {
            t[i] = (acc[2 * i] & 65535) | (acc[2 * i + 1] << 16);
            i = i + 1;
        }
        fe_zero(back);
        back[0] = acc[16] * 38;
        fe_add(t, t, back);
        k = 0;
        while (k < 3) {
            if (fe_ge(t, sign_q4) == 1)
                fe_rawsub(t, t, sign_q4);
            k = k + 1;
        }
        fe_copy(r, t);
    }
}

/** Docstring: Square mod q. */
static void fe_sq(unsigned int *r, unsigned int *a) {
    fe_mul(r, a, a);
}

/** Docstring: Power with the q-minus-2 bit pattern, always square. */
static void fe_inv(unsigned int *r, unsigned int *a) {
    unsigned int acc[8];
    unsigned int tmp[8];
    int i = 0;
    fe_one(acc);
    while (i < 255) {
        unsigned int bit = 1;
        if (i == 252 || i == 250)
            bit = 0;
        fe_sq(tmp, acc);
        fe_copy(acc, tmp);
        fe_mul(tmp, acc, a);
        fe_cmov(acc, tmp, bit);
        i = i + 1;
    }
    fe_copy(r, acc);
}

/** Docstring: Load 32 bytes into eight limbs. */
static void fe_frombytes(unsigned int *r, char *b) {
    int i = 0;
    while (i < 8) {
        r[i] = sign_byte(b, 4 * i) | (sign_byte(b, 4 * i + 1) << 8) |
               (sign_byte(b, 4 * i + 2) << 16) | (sign_byte(b, 4 * i + 3) << 24);
        i = i + 1;
    }
}

/** Docstring: Store eight limbs as 32 bytes. */
static void fe_tobytes(char *b, unsigned int *a) {
    int i = 0;
    while (i < 8) {
        b[4 * i] = (char)(a[i] & 255);
        b[4 * i + 1] = (char)((a[i] >> 8) & 255);
        b[4 * i + 2] = (char)((a[i] >> 16) & 255);
        b[4 * i + 3] = (char)((a[i] >> 24) & 255);
        i = i + 1;
    }
}

/** Docstring: Recover d from minus 121665 over 121666. */
static void fe_curved(unsigned int *d, unsigned int *d2) {
    unsigned int num[8];
    unsigned int den[8];
    unsigned int inv[8];
    unsigned int zero[8];
    fe_zero(num);
    fe_zero(den);
    num[0] = 121665;
    den[0] = 121666;
    fe_inv(inv, den);
    fe_mul(d, num, inv);
    fe_zero(zero);
    fe_sub(d, zero, d);
    fe_add(d2, d, d);
}

/** Docstring: Copy one extended point of 32 limbs. */
static void ge_copy(unsigned int *r, unsigned int *a) {
    int i = 0;
    while (i < 32) {
        r[i] = a[i];
        i = i + 1;
    }
}

/** Docstring: Address of limb n from a limb base.
 *
 * miniGCC scales `a[i]` by 8 (its `unsigned int` slot) but adds raw
 * bytes for `p + N`, and parses `&p[N]` on a pointer as `(&p) + 8N`
 * (the address of the pointer variable, caught by a wild-rsp crash
 * in `ge_scalarmult`). `&arr[N]` on arrays happens to work, but this
 * helper is the only sanctioned limb addressing: `p + n * 8` is byte
 * addition of an exact scaled offset. Never use it on `char *`. */
static unsigned int *fe_off(unsigned int *p, int n) {
    return p + n * 8;
}

/** Docstring: Masked point select, no secret branches. */
static void ge_cmov(unsigned int *r, unsigned int *b, unsigned int flag) {
    unsigned int m = 0 - (flag & 1);
    int i = 0;
    while (i < 32) {
        r[i] = r[i] ^ (m & (r[i] ^ b[i]));
        i = i + 1;
    }
}

/** Docstring: Complete twisted-Edwards addition. */
static void ge_add(unsigned int *r, unsigned int *p, unsigned int *q, unsigned int *d2) {
    unsigned int a[8];
    unsigned int b[8];
    unsigned int c[8];
    unsigned int d[8];
    unsigned int e[8];
    unsigned int f[8];
    unsigned int g[8];
    unsigned int h[8];
    unsigned int t0[8];
    unsigned int t1[8];
    fe_sub(t0, fe_off(p, 8), p);
    fe_sub(t1, fe_off(q, 8), q);
    fe_mul(a, t0, t1);
    fe_add(t0, fe_off(p, 8), p);
    fe_add(t1, fe_off(q, 8), q);
    fe_mul(b, t0, t1);
    fe_mul(t0, fe_off(p, 24), fe_off(q, 24));
    fe_mul(c, t0, d2);
    fe_add(t0, fe_off(p, 16), fe_off(p, 16));
    fe_mul(d, t0, fe_off(q, 16));
    fe_sub(e, b, a);
    fe_sub(f, d, c);
    fe_add(g, d, c);
    fe_add(h, b, a);
    fe_mul(r, e, f);
    fe_mul(fe_off(r, 8), g, h);
    fe_mul(fe_off(r, 16), f, g);
    fe_mul(fe_off(r, 24), e, h);
}

/** Docstring: Twisted-Edwards doubling for a fixed at minus one. */
static void ge_double(unsigned int *r, unsigned int *p) {
    unsigned int a[8];
    unsigned int b[8];
    unsigned int c[8];
    unsigned int e[8];
    unsigned int f[8];
    unsigned int g[8];
    unsigned int h[8];
    unsigned int t0[8];
    unsigned int t1[8];
    unsigned int na[8];
    unsigned int nb[8];
    fe_sq(a, p);
    fe_sq(b, fe_off(p, 8));
    fe_sq(t0, fe_off(p, 16));
    fe_add(c, t0, t0);
    fe_add(t0, p, fe_off(p, 8));
    fe_sq(t0, t0);
    fe_sub(t1, t0, a);
    fe_sub(e, t1, b);
    fe_zero(na);
    fe_sub(na, na, a);
    fe_add(g, na, b);
    fe_sub(f, g, c);
    fe_zero(nb);
    fe_sub(nb, nb, b);
    fe_add(h, na, nb);
    fe_mul(r, e, f);
    fe_mul(fe_off(r, 8), g, h);
    fe_mul(fe_off(r, 16), f, g);
    fe_mul(fe_off(r, 24), e, h);
}

/** Docstring: Multiply a point by a 32-byte scalar. */
static void ge_scalarmult(unsigned int *r, unsigned int *p, char *s, unsigned int *d2) {
    unsigned int qq[32];
    unsigned int dbl[32];
    int i = 0;
    while (i < 32) {
        qq[i] = 0;
        i = i + 1;
    }
    qq[8] = 1;
    qq[16] = 1;
    i = 254;
    while (i >= 0) {
        unsigned int bit = 0;
        if (((sign_byte(s, i >> 3) >> (i & 7)) & 1) == 1)
            bit = 1;
        ge_double(dbl, qq);
        ge_copy(qq, dbl);
        ge_add(dbl, qq, p, d2);
        ge_cmov(qq, dbl, bit);
        i = i - 1;
    }
    ge_copy(r, qq);
}

/** Docstring: Reduce sixteen limbs mod L by binary long division. */
static void sc_mod_l(unsigned int *r, unsigned int *t16) {
    unsigned int rem[9];
    int b = 0;
    int k = 0;
    int s = 0;
    int nk = 0;
    while (k < 9) {
        rem[k] = 0;
        k = k + 1;
    }
    while (b < 512) {
        int src = 63 - (b / 8);
        int bit = 7 - (b % 8);
        unsigned int carry = 0;
        int limb = src / 4;
        int off = src % 4;
        unsigned int tv = 0;
        tv = (t16[limb] << 32) >> 32;
        carry = (tv >> (8 * off + bit)) & 1;
        nk = 0;
        while (nk < 9) {
            unsigned int nc = 0;
            if ((((rem[nk] << 32) >> 32) >> 31) != 0)
                nc = 1;
            rem[nk] = (rem[nk] << 1) | carry;
            carry = nc;
            nk = nk + 1;
        }
        s = 0;
        while (s < 4) {
            unsigned int ge = 0;
            if (((rem[8] << 32) >> 32) > 0)
                ge = 1;
            else if (fe_ge(rem, sign_l8) == 1)
                ge = 1;
            if (ge == 1) {
                unsigned int borrow = 0;
                nk = 0;
                while (nk < 8) {
                    unsigned int cur = rem[nk];
                    unsigned int t1 = cur - borrow;
                    unsigned int c0 = sign_borrow2(cur, borrow, t1);
                    unsigned int t2 = t1 - sign_l8[nk];
                    unsigned int c1 = sign_borrow2(t1, sign_l8[nk], t2);
                    rem[nk] = t2;
                    borrow = c0 | c1;
                    nk = nk + 1;
                }
                rem[8] = rem[8] - borrow;
            }
            s = s + 1;
        }
        b = b + 1;
    }
    k = 0;
    while (k < 8) {
        r[k] = rem[k];
        k = k + 1;
    }
}

/** Docstring: Multiply two scalars with r added, all mod L. */
static void sc_mul_add(unsigned int *r, unsigned int *a, unsigned int *b, unsigned int *c) {
    unsigned int x[16];
    unsigned int y[16];
    unsigned int acc[32];
    unsigned int t16[16];
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < 8) {
        x[2 * i] = a[i] & 65535;
        x[2 * i + 1] = (a[i] >> 16) & 65535;
        y[2 * i] = b[i] & 65535;
        y[2 * i + 1] = (b[i] >> 16) & 65535;
        i = i + 1;
    }
    while (k < 32) {
        acc[k] = 0;
        k = k + 1;
    }
    i = 0;
    while (i < 16) {
        j = 0;
        while (j < 16) {
            unsigned int p = x[i] * y[j];
            fe_rowadd(acc, i + j, p);
            j = j + 1;
        }
        i = i + 1;
    }
    i = 0;
    while (i < 16) {
        t16[i] = (acc[2 * i] & 65535) | (acc[2 * i + 1] << 16);
        i = i + 1;
    }
    {
        unsigned int carry = 0;
        i = 0;
        while (i < 8) {
            unsigned int s1 = t16[i] + c[i];
            unsigned int c0 = sign_carry2(t16[i], c[i], s1);
            unsigned int s2 = s1 + carry;
            unsigned int c1 = sign_carry2(s1, carry, s2);
            t16[i] = s2;
            carry = c0 | c1;
            i = i + 1;
        }
        while (i < 16) {
            unsigned int s = t16[i] + carry;
            carry = sign_carry2(t16[i], carry, s);
            t16[i] = s;
            i = i + 1;
        }
    }
    sc_mod_l(r, t16);
}

/** Docstring: Reverse 32 bytes in place, big-endian hex to limbs. */
static void sign_rev32(char *b) {
    int i = 0;
    while (i < 16) {
        char t = b[i];
        b[i] = b[31 - i];
        b[31 - i] = t;
        i = i + 1;
    }
}

/** Docstring: Load the embedded base and key points. */
static void sign_points_init(void) {
    char bx[32];
    char by[32];
    char ax[32];
    char ay[32];
    unsigned int t[8];
    sign_unhex(bx, sign_bx_hex, 32);
    sign_unhex(by, sign_by_hex, 32);
    sign_unhex(ax, sign_ax_hex, 32);
    sign_unhex(ay, sign_ay_hex, 32);
    sign_rev32(bx);
    sign_rev32(by);
    sign_rev32(ax);
    sign_rev32(ay);
    fe_frombytes(t, bx);
    fe_copy(sign_gb, t);
    fe_frombytes(t, by);
    fe_copy(fe_off(sign_gb, 8), t);
    fe_one(fe_off(sign_gb, 16));
    fe_mul(t, sign_gb, fe_off(sign_gb, 8));
    fe_copy(fe_off(sign_gb, 24), t);
    fe_frombytes(t, ax);
    fe_copy(sign_ga, t);
    fe_frombytes(t, ay);
    fe_copy(fe_off(sign_ga, 8), t);
    fe_one(fe_off(sign_ga, 16));
    fe_mul(t, sign_ga, fe_off(sign_ga, 8));
    fe_copy(fe_off(sign_ga, 24), t);
}

/** Docstring: Sign a 64-byte digest with the embedded seed. */
static void sign_digest(char *sig, char *digest) {
    char seed[32];
    char h1[64];
    char rbytes[64];
    char renc[32];
    char hrambytes[64];
    char abuf[32];
    char s32[32];
    char h32[32];
    unsigned int a[8];
    unsigned int rr[8];
    unsigned int hram[8];
    unsigned int ss[8];
    unsigned int d[8];
    unsigned int d2[8];
    unsigned int pr[32];
    unsigned int rx[8];
    unsigned int rz[8];
    unsigned int rzi[8];
    unsigned int t16[16];
    int i = 0;
    sign_unhex(seed, sign_seed_hex, 32);
    sign_sha_init();
    sign_sha_update(seed, 32);
    sign_sha_final(h1);
    i = 0;
    while (i < 32) {
        abuf[i] = h1[i];
        i = i + 1;
    }
    abuf[0] = (char)((int)abuf[0] & 248);
    abuf[31] = (char)(((int)abuf[31] & 63) | 64);
    fe_frombytes(a, abuf);
    {
        unsigned int ta[16];
        i = 0;
        while (i < 16) {
            ta[i] = 0;
            i = i + 1;
        }
        fe_tobytes(abuf, a);
        i = 0;
        while (i < 8) {
            ta[i] = sign_byte(abuf, 4 * i) | (sign_byte(abuf, 4 * i + 1) << 8) |
                    (sign_byte(abuf, 4 * i + 2) << 16) | (sign_byte(abuf, 4 * i + 3) << 24);
            i = i + 1;
        }
        sc_mod_l(a, ta);
    }
    fe_tobytes(abuf, a);
    i = 0;
    while (i < 32) {
        seed[i] = h1[32 + i];
        i = i + 1;
    }
    sign_sha_init();
    sign_sha_update(seed, 32);
    sign_sha_update(digest, 64);
    sign_sha_final(rbytes);
    i = 0;
    while (i < 16) {
        t16[i] = 0;
        i = i + 1;
    }
    i = 0;
    while (i < 16) {
        t16[i] = sign_byte(rbytes, 4 * i) | (sign_byte(rbytes, 4 * i + 1) << 8) |
                 (sign_byte(rbytes, 4 * i + 2) << 16) | (sign_byte(rbytes, 4 * i + 3) << 24);
        i = i + 1;
    }
    sc_mod_l(rr, t16);
    fe_tobytes(s32, rr);
    fe_curved(d, d2);
    fe_tobytes(h32, d2);
    ge_scalarmult(pr, sign_gb, s32, d2);
    fe_copy(rx, pr);
    fe_copy(rz, fe_off(pr, 16));
    fe_tobytes(abuf, rx);
    fe_tobytes(abuf, rz);
    fe_inv(rzi, rz);
    fe_mul(rx, rx, rzi);
    {
        unsigned int ry[8];
        unsigned int bit = 0;
        fe_copy(ry, fe_off(pr, 8));
        fe_mul(ry, ry, rzi);
        fe_tobytes(renc, ry);
        if ((rx[0] & 1) == 1)
            bit = 128;
        renc[31] = (char)((int)renc[31] | (int)bit);
    }
    {
        char pub[32];
        sign_unhex(pub, sign_pub_hex, 32);
        sign_sha_init();
        sign_sha_update(renc, 32);
        sign_sha_update(pub, 32);
        sign_sha_update(digest, 64);
        sign_sha_final(hrambytes);
    }
    i = 0;
    while (i < 16) {
        t16[i] = 0;
        i = i + 1;
    }
    i = 0;
    while (i < 16) {
        t16[i] = sign_byte(hrambytes, 4 * i) | (sign_byte(hrambytes, 4 * i + 1) << 8) |
                 (sign_byte(hrambytes, 4 * i + 2) << 16) | (sign_byte(hrambytes, 4 * i + 3) << 24);
        i = i + 1;
    }
    sc_mod_l(hram, t16);
    fe_tobytes(h32, hram);
    sc_mul_add(ss, hram, a, rr);
    sign_copy(sig, renc, 32);
    fe_tobytes(abuf, ss);
    sign_copy(sig + 32, abuf, 32);
}

/** Docstring: Read a whole file, capped, returning its bytes or zero. */
static char *sign_read(char *name, int *len) {
    void *f = fopen(name, "r");
    int got = 0;
    char *buf = 0;
    if (f == 0)
        return 0;
    fseek(f, 0, SIGN_SEEK_END);
    *len = ftell(f);
    fseek(f, 0, 0);
    if (*len < 0 || *len > SIGN_MAX_FILE) {
        fclose(f);
        return 0;
    }
    if (*len == 0)
        *len = 1;
    buf = malloc(*len);
    if (buf == 0) {
        fclose(f);
        return 0;
    }
    got = fread(buf, 1, *len, f);
    fclose(f);
    if (got != *len)
        return 0;
    return buf;
}

/** Docstring: Write a whole file, 0 on success. */
static int sign_write(char *name, char *data, int len) {
    void *f = fopen(name, "w");
    int got = 0;
    if (f == 0)
        return 1;
    got = fwrite(data, 1, len, f);
    fclose(f);
    if (got != len)
        return 1;
    return 0;
}

/** Docstring: Scan one PT_NOTE span for the signature descriptor. */
static int sign_note_span(char *img, int off, int len, int *desc) {
    int pos = 0;
    while (len - pos >= SIGN_NOTE_HDR) {
        unsigned int namesz = sign_le32(img, off + pos);
        unsigned int descsz = sign_le32(img, off + pos + 4);
        unsigned int type = sign_le32(img, off + pos + 8);
        int rest = len - pos - SIGN_NOTE_HDR;
        int padn = ((int)namesz + 3) / 4 * 4;
        int ok = 0;
        int k = 0;
        if (padn + (int)descsz > rest)
            return -1;
        if (namesz == 7 && type == SIGN_NOTE_TYPE && descsz == SIGN_DESC_BYTES) {
            ok = 1;
            while (k < 6) {
                if (img[off + pos + SIGN_NOTE_HDR + k] != sign_note_name[k])
                    ok = 0;
                k = k + 1;
            }
            if (ok == 1) {
                *desc = off + pos + SIGN_NOTE_HDR + padn;
                return 1;
            }
        }
        pos = pos + SIGN_NOTE_HDR + padn + ((int)descsz + 3) / 4 * 4;
    }
    return 0;
}

/** Docstring: Build the canonical digest over entry plus PT_LOADs.
 *
 * File bytes below the ELF header size are excluded from the
 * segment feeds while the entry stays bound as a value, matching
 * the kernel gate and tools/sign_elf.py. */
static int sign_digest_of(char *img, int size, int entry, char *ph, int phnum, char *digest) {
    int i = 0;
    char zb[4];
    zb[0] = 0;
    zb[1] = 0;
    zb[2] = 0;
    zb[3] = 0;
    sign_sha_init();
    sign_feed32((unsigned int)entry);
    sign_feed32(0);
    while (i < phnum) {
        int base = i * SIGN_PHDR_SIZE;
        unsigned int ptype = sign_le32(ph, base);
        int poff = 0;
        int pfilesz = 0;
        unsigned int pvaddr = 0;
        unsigned int pflags = 0;
        int start = 0;
        int end = 0;
        if (ptype != SIGN_PT_LOAD) {
            i = i + 1;
            continue;
        }
        if (sign_offok(ph, base + 8, &poff) == 0)
            return 1;
        pvaddr = sign_le32(ph, base + 16);
        pflags = sign_le32(ph, base + 4);
        if (sign_offok(ph, base + 32, &pfilesz) == 0)
            return 1;
        if (poff < 0 || pfilesz < 0 || poff + pfilesz > size || poff + pfilesz < poff)
            return 1;
        sign_feed32(pvaddr);
        sign_feed32(0);
        sign_feed32(pflags);
        sign_feed32((unsigned int)pfilesz);
        sign_feed32(0);
        start = poff;
        if (start < SIGN_EHDR_SIZE)
            start = SIGN_EHDR_SIZE;
        end = poff + pfilesz;
        if (start < end)
            sign_sha_update(img + start, end - start);
        i = i + 1;
    }
    sign_sha_final(digest);
    return 0;
}

/** Docstring: Patch an own-key PT_NOTE slot, 1 when patched. */
static int sign_patch_notes(char *img, int size, char *ph, int phnum, char *desc) {
    int n = 0;
    int patched = 0;
    while (n < phnum) {
        int base = n * SIGN_PHDR_SIZE;
        unsigned int ptype = sign_le32(ph, base);
        int poff = 0;
        int pfilesz = 0;
        int slot = 0;
        int rc = 0;
        int k = 0;
        if (ptype != SIGN_PT_NOTE) {
            n = n + 1;
            continue;
        }
        if (sign_offok(ph, base + 8, &poff) == 0 || sign_offok(ph, base + 32, &pfilesz) == 0) {
            n = n + 1;
            continue;
        }
        if (poff < 0 || pfilesz < 0 || poff + pfilesz > size) {
            n = n + 1;
            continue;
        }
        rc = sign_note_span(img, poff, pfilesz, &slot);
        if (rc == 1 && img[slot] == SIGN_KEY_ID) {
            while (k < SIGN_DESC_BYTES) {
                img[slot + k] = desc[k];
                k = k + 1;
            }
            patched = 1;
        }
        n = n + 1;
    }
    return patched;
}

/** Docstring: Append a fresh signature section, 0 on success. */
static int sign_append(char *name, char *img, int size, int shoff, int shnum, int shentsize,
                       int shstrndx, char *desc) {
    int stab_off = 0;
    int stab_size = 0;
    int stab_base = shoff + shstrndx * shentsize;
    int namelen = 0;
    int nameoff = 0;
    int noteoff = size;
    int stroff = 0;
    int newshoff = 0;
    int newsize = 0;
    char *out = 0;
    char *oldstr = 0;
    int i = 0;
    int k = 0;
    if (sign_offok(img, stab_base + 24, &stab_off) == 0 ||
        sign_offok(img, stab_base + 32, &stab_size) == 0 || stab_off < 0 ||
        stab_size < 0 || stab_off + stab_size > size) {
        printf("sign: %s: bad string table\n", name);
        return 1;
    }
    namelen = sign_strlen(sign_section_name) + 1;
    nameoff = stab_size;
    while (noteoff % 8 != 0)
        noteoff = noteoff + 1;
    stroff = noteoff + SIGN_NOTE_TOTAL;
    while (stroff % 8 != 0)
        stroff = stroff + 1;
    newshoff = stroff + stab_size + namelen;
    while (newshoff % 8 != 0)
        newshoff = newshoff + 1;
    newsize = newshoff + (shnum + 1) * shentsize;
    out = malloc(newsize + 1);
    if (out == 0) {
        printf("sign: out of memory\n");
        return 1;
    }
    while (i < size) {
        out[i] = img[i];
        i = i + 1;
    }
    while (i < newsize) {
        out[i] = 0;
        i = i + 1;
    }
    oldstr = malloc(stab_size + 1);
    if (oldstr == 0) {
        printf("sign: out of memory\n");
        return 1;
    }
    i = 0;
    while (i < stab_size) {
        oldstr[i] = img[stab_off + i];
        i = i + 1;
    }
    k = 0;
    while (k < SIGN_NOTE_TOTAL) {
        out[noteoff + k] = 0;
        k = k + 1;
    }
    sign_put32(out, noteoff, 7);
    sign_put32(out, noteoff + 4, SIGN_DESC_BYTES);
    sign_put32(out, noteoff + 8, SIGN_NOTE_TYPE);
    k = 0;
    while (k < 6) {
        out[noteoff + 12 + k] = sign_note_name[k];
        k = k + 1;
    }
    k = 0;
    while (k < SIGN_DESC_BYTES) {
        out[noteoff + 20 + k] = desc[k];
        k = k + 1;
    }
    k = 0;
    while (k < stab_size) {
        out[stroff + k] = oldstr[k];
        k = k + 1;
    }
    k = 0;
    while (k < namelen) {
        out[stroff + stab_size + k] = sign_section_name[k];
        k = k + 1;
    }
    i = 0;
    while (i < shnum) {
        int sbase = shoff + i * shentsize;
        k = 0;
        while (k < shentsize) {
            out[newshoff + i * shentsize + k] = img[sbase + k];
            k = k + 1;
        }
        i = i + 1;
    }
    {
        int ns = newshoff + shnum * shentsize;
        int v = 0;
        while (v < shentsize) {
            out[ns + v] = 0;
            v = v + 1;
        }
        sign_put32(out, ns, nameoff);
        sign_put32(out, ns + 4, SIGN_SHT_NOTE);
        sign_put32(out, ns + 24, noteoff);
        sign_put32(out, ns + 32, SIGN_NOTE_TOTAL);
        sign_put32(out, ns + 52, 4);
    }
    {
        int sbase = shoff + shstrndx * shentsize;
        int ns = newshoff + shstrndx * shentsize;
        sign_put32(out, ns + 24, stroff);
        sign_put32(out, ns + 32, stab_size + namelen);
        sbase = sbase + 0;
    }
    {
        int v = 0;
        int sh = newshoff;
        while (v < 8) {
            out[40 + v] = (char)(sh & 255);
            sh = sh >> 8;
            v = v + 1;
        }
        {
            int sn = shnum + 1;
            out[60] = (char)(sn & 255);
            out[61] = (char)((sn >> 8) & 255);
        }
    }
    if (sign_write(name, out, newsize) != 0) {
        printf("sign: cannot write %s\n", name);
        return 1;
    }
    printf("sign: %s: signed (key %d)\n", name, SIGN_KEY_ID);
    return 0;
}

/** Docstring: Sign one file in place, returning an exit-style code. */
static int sign_file(char *name) {
    char *img = 0;
    int size = 0;
    int entry = 0;
    int phoff = 0;
    int phnum = 0;
    int phentsize = 0;
    char *ph = 0;
    char digest[64];
    char sig[64];
    char desc[SIGN_DESC_BYTES];
    int i = 0;
    img = sign_read(name, &size);
    if (img == 0) {
        printf("sign: cannot read %s\n", name);
        return 1;
    }
    if (size < SIGN_EHDR_SIZE || img[0] != 127 || img[1] != 69 || img[2] != 76 || img[3] != 70) {
        printf("sign: %s: not an ELF image, skipped\n", name);
        return 0;
    }
    {
        int etype = sign_le16(img, 16);
        int em = sign_le16(img, 18);
        if (em != SIGN_EM_X86_64) {
            printf("sign: %s: not x86-64, skipped\n", name);
            return 0;
        }
        if (etype != SIGN_ET_EXEC && etype != SIGN_ET_DYN) {
            printf("sign: %s: not an executable, skipped\n", name);
            return 0;
        }
    }
    if (sign_offok(img, 24, &entry) == 0) {
        printf("sign: %s: bad entry\n", name);
        return 1;
    }
    if (sign_offok(img, 32, &phoff) == 0) {
        printf("sign: %s: bad phoff\n", name);
        return 1;
    }
    phentsize = sign_le16(img, 54);
    phnum = sign_le16(img, 56);
    if (phentsize < SIGN_PHDR_SIZE || phoff < 0 || phnum < 0 ||
        phoff + phnum * phentsize > size || phoff + phnum * phentsize < phoff) {
        printf("sign: %s: bad program headers\n", name);
        return 1;
    }
    ph = malloc(phnum * phentsize + 1);
    if (ph == 0) {
        printf("sign: out of memory\n");
        return 1;
    }
    i = 0;
    while (i < phnum * phentsize) {
        ph[i] = img[phoff + i];
        i = i + 1;
    }
    if (sign_digest_of(img, size, entry, ph, phnum, digest) != 0) {
        printf("sign: %s: digest failed\n", name);
        return 1;
    }
    sign_digest(sig, digest);
    desc[0] = (char)SIGN_KEY_ID;
    i = 0;
    while (i < SIGN_SIG_BYTES) {
        desc[1 + i] = sig[i];
        i = i + 1;
    }
    if (sign_patch_notes(img, size, ph, phnum, desc) == 1) {
        if (sign_write(name, img, size) != 0) {
            printf("sign: cannot write %s\n", name);
            return 1;
        }
        printf("sign: %s: signed (key %d)\n", name, SIGN_KEY_ID);
        return 0;
    }
    {
        int shoff = 0;
        int shnum = 0;
        int shentsize = 0;
        int shstrndx = 0;
        if (sign_offok(img, 40, &shoff) == 0 || shoff < 0) {
            printf("sign: %s: no section table to extend\n", name);
            return 1;
        }
        shentsize = sign_le16(img, 58);
        shnum = sign_le16(img, 60);
        shstrndx = sign_le16(img, 62);
        if (shentsize < SIGN_SHDR_SIZE || shnum <= 0 || shstrndx < 0 || shstrndx >= shnum ||
            shoff < 0 || shoff + shnum * shentsize > size) {
            printf("sign: %s: no section table to extend\n", name);
            return 1;
        }
        return sign_append(name, img, size, shoff, shnum, shentsize, shstrndx, desc);
    }
}

/** Docstring: Selftest vectors for host-vs-guest differential. */
/** Docstring: In-OS differential selftest, pinned by BDD.
 *
 * Prints the SHA-512 of "abc" and an Ed25519 signature of the
 * 64-zero-byte digest under the embedded development key. The BDD
 * suite pins both lines byte-exact against python/PyNaCl oracles,
 * so any miniGCC codegen regression in the SHA, field, curve or
 * digest paths fails the boot suite instead of shipping bad
 * signatures (every primitive below was differential-tested during
 * bringup; see the file header for the constraints they pin). */
static int sign_selftest(void) {
    char out[129];
    char digest[64];
    char sig[64];
    int i = 0;
    sign_sha_init();
    sign_sha_update("abc", 3);
    sign_sha_final(digest);
    sign_hexout(out, digest, 64);
    printf("SHA-ABC %s\n", out);
    while (i < 64) {
        digest[i] = 0;
        i = i + 1;
    }
    sign_digest(sig, digest);
    sign_hexout(out, sig, 64);
    printf("SIG-ZERO %s\n", out);
    return 0;
}

int main(int argc, char **argv) {
    int fails = 0;
    int i = 1;
    sign_key_init();
    sign_points_init();
    if (argc >= 2 && strcmp(argv[1], "--selftest") == 0)
        return sign_selftest();
    if (argc < 2) {
        printf("usage: sign <file> [...]\n");
        return SIGN_EXIT_FAIL;
    }
    while (i < argc) {
        if (sign_file(argv[i]) != 0)
            fails = fails + 1;
        i = i + 1;
    }
    if (fails != 0)
        return SIGN_EXIT_FAIL;
    return 0;
}
