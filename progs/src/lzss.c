/* lzss.c - command path LZSS (de)compression tools: lzss and unlzss.
 * One source builds both binaries; the linker emits the same program as
 * bin/lzss and bin/unlzss and the program picks its mode from argv[0] (any
 * invocation path containing "unlzss" decodes, and -d forces decode).
 *
 * The codec is Okumura LZSS over an in-memory whole-file buffer so the OS
 * rebuild can operate without per-byte syscalls.  The on-disk container is
 * fail-closed: 4-byte magic "LZS1", the original size as a little-endian
 * u32, then the MSB-first bit stream.  Decoding rejects a bad magic, a
 * declared size beyond the expansion bound derived from the input length,
 * and any stream that would write past the declared size. */

void *malloc();
void free();
int printf();
int strcmp();
int strlen();
void *fopen();
int fclose();
int fread();
int fwrite();
int fseek();
int ftell();
void rewind();

#define LZSS_EI 11
#define LZSS_EJ 4
#define LZSS_P 1
#define LZSS_N (1 << LZSS_EI)
#define LZSS_F ((1 << LZSS_EJ) + LZSS_P)
#define LZSS_WIN (LZSS_N * 2)

#define LZSS_MAGIC0 'L'
#define LZSS_MAGIC1 'Z'
#define LZSS_MAGIC2 'S'
#define LZSS_MAGIC3 '1'
#define LZSS_HDR_SIZE 8

#define LZSS_ENC_SLACK 8
#define LZSS_EXPAND_NUM 17
#define LZSS_EXPAND_DEN 2

#define LZSS_SEEK_END 2

#define LZSS_ERR_NONE 0
#define LZSS_ERR_OVERFLOW 1

#define LZSS_EXIT_FAIL 1

static char lz_win[LZSS_WIN];

static char *lz_src;
static int lz_srclen;
static int lz_srcpos;

static char *lz_dst;
static int lz_dstcap;
static int lz_dstlen;
static int lz_err;

static int lz_buf;
static int lz_mask;

static int lz_in_getc(void) {
    if (lz_srcpos >= lz_srclen) return -1;
    return lz_src[lz_srcpos++] & 255;
}

static void lz_out_put(int c) {
    if (lz_dstlen >= lz_dstcap) { lz_err = LZSS_ERR_OVERFLOW; return; }
    lz_dst[lz_dstlen++] = (char)c;
}

static void lz_putbit1(void) {
    lz_buf = lz_buf | lz_mask;
    lz_mask = lz_mask >> 1;
    if (lz_mask == 0) {
        lz_out_put(lz_buf);
        lz_buf = 0;
        lz_mask = 128;
    }
}

static void lz_putbit0(void) {
    lz_mask = lz_mask >> 1;
    if (lz_mask == 0) {
        lz_out_put(lz_buf);
        lz_buf = 0;
        lz_mask = 128;
    }
}

static void lz_flush_bits(void) {
    if (lz_mask != 128) lz_out_put(lz_buf);
}

static void lz_out_literal(int c) {
    int m;
    lz_putbit1();
    for (m = 128; m != 0; m = m >> 1) {
        if (c & m) lz_putbit1(); else lz_putbit0();
    }
}

static void lz_out_pair(int x, int y) {
    int m;
    lz_putbit0();
    for (m = 1024; m != 0; m = m >> 1) {
        if (x & m) lz_putbit1(); else lz_putbit0();
    }
    for (m = 8; m != 0; m = m >> 1) {
        if (y & m) lz_putbit1(); else lz_putbit0();
    }
}

static int lz_encode(void) {
    int i, j, f1, x, y, r, s, bufferend, c;
    for (i = 0; i < LZSS_N - LZSS_F; i++) lz_win[i] = 32;
    for (i = LZSS_N - LZSS_F; i < LZSS_WIN; i++) {
        if ((c = lz_in_getc()) == -1) break;
        lz_win[i] = (char)c;
    }
    bufferend = i;
    r = LZSS_N - LZSS_F;
    s = 0;
    while (r < bufferend && lz_err == LZSS_ERR_NONE) {
        f1 = (LZSS_F <= bufferend - r) ? LZSS_F : bufferend - r;
        x = 0;
        y = 1;
        c = lz_win[r] & 255;
        for (i = r - 1; i >= s; i--) {
            if ((lz_win[i] & 255) == c) {
                for (j = 1; j < f1; j++) {
                    if (lz_win[i + j] != lz_win[r + j]) break;
                }
                if (j > y) { x = i; y = j; }
            }
        }
        if (y <= LZSS_P) {
            lz_out_literal(c);
        } else {
            lz_out_pair(x & (LZSS_N - 1), y - 2);
        }
        r += y;
        s += y;
        if (r >= LZSS_WIN - LZSS_F) {
            for (i = 0; i < LZSS_N; i++) lz_win[i] = lz_win[i + LZSS_N];
            bufferend -= LZSS_N;
            r -= LZSS_N;
            s -= LZSS_N;
            while (bufferend < LZSS_WIN && lz_err == LZSS_ERR_NONE) {
                if ((c = lz_in_getc()) == -1) break;
                lz_win[bufferend++] = (char)c;
            }
        }
    }
    if (lz_err == LZSS_ERR_NONE) lz_flush_bits();
    return lz_err;
}

static int lz_getbit(int n) {
    int i, x;
    x = 0;
    for (i = 0; i < n; i++) {
        if (lz_mask == 0) {
            if (lz_srcpos >= lz_srclen) return -1;
            lz_buf = lz_src[lz_srcpos++] & 255;
            lz_mask = 128;
        }
        x = x << 1;
        if (lz_buf & lz_mask) x++;
        lz_mask = lz_mask >> 1;
    }
    return x;
}

static int lz_decode(void) {
    int i, j, k, r, c;
    for (i = 0; i < LZSS_N - LZSS_F; i++) lz_win[i] = 32;
    r = LZSS_N - LZSS_F;
    lz_mask = 0;
    lz_buf = 0;
    while (lz_err == LZSS_ERR_NONE) {
        if ((c = lz_getbit(1)) == -1) break;
        if (c) {
            if ((c = lz_getbit(8)) == -1) break;
            lz_out_put(c);
            if (lz_err != LZSS_ERR_NONE) break;
            lz_win[r] = (char)c;
            r = (r + 1) & (LZSS_N - 1);
        } else {
            if ((i = lz_getbit(LZSS_EI)) == -1) break;
            if ((j = lz_getbit(LZSS_EJ)) == -1) break;
            for (k = 0; k <= j + 1; k++) {
                c = lz_win[(i + k) & (LZSS_N - 1)] & 255;
                lz_out_put(c);
                if (lz_err != LZSS_ERR_NONE) break;
                lz_win[r] = (char)c;
                r = (r + 1) & (LZSS_N - 1);
            }
        }
    }
    return lz_err;
}

static void lz_hdr_put(char *h, int size) {
    h[0] = LZSS_MAGIC0;
    h[1] = LZSS_MAGIC1;
    h[2] = LZSS_MAGIC2;
    h[3] = LZSS_MAGIC3;
    h[4] = (char)(size & 255);
    h[5] = (char)((size >> 8) & 255);
    h[6] = (char)((size >> 16) & 255);
    h[7] = (char)((size >> 24) & 255);
}

static int lz_hdr_get(char *h) {
    if (h[0] != LZSS_MAGIC0) return -1;
    if (h[1] != LZSS_MAGIC1) return -1;
    if (h[2] != LZSS_MAGIC2) return -1;
    if (h[3] != LZSS_MAGIC3) return -1;
    return (h[4] & 255) | ((h[5] & 255) << 8) | ((h[6] & 255) << 16) | ((h[7] & 255) << 24);
}

static int lz_has(const char *s, const char *needle) {
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

static char *lz_read_all(const char *name, int *len) {
    char *data;
    int got;
    void *f = fopen((char *)name, "r");
    if (!f) return 0;
    fseek(f, 0, LZSS_SEEK_END);
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

static int lz_write_all(const char *name, char *data, int len) {
    int n;
    void *f = fopen((char *)name, "w");
    if (!f) return 0;
    n = fwrite(data, 1, len, f);
    if (n != len) { fclose(f); return 0; }
    if (fclose(f) != 0) return 0;
    return 1;
}

static int lz_compress(const char *src, const char *dst) {
    char *data;
    char *out;
    int in_len;
    int out_cap;
    int out_len;
    data = lz_read_all(src, &in_len);
    if (!data) {
        printf("lzss: cannot open %s\n", src);
        return LZSS_EXIT_FAIL;
    }
    out_cap = in_len + in_len / 8 + LZSS_ENC_SLACK;
    out = malloc(LZSS_HDR_SIZE + (out_cap > 0 ? out_cap : 1));
    if (!out) {
        free(data);
        printf("lzss: out of memory\n");
        return LZSS_EXIT_FAIL;
    }
    lz_src = data;
    lz_srclen = in_len;
    lz_srcpos = 0;
    lz_dst = out + LZSS_HDR_SIZE;
    lz_dstcap = out_cap;
    lz_dstlen = 0;
    lz_err = LZSS_ERR_NONE;
    lz_buf = 0;
    lz_mask = 128;
    if (lz_encode() != LZSS_ERR_NONE) {
        free(data);
        free(out);
        printf("lzss: %s: encode failed\n", src);
        return LZSS_EXIT_FAIL;
    }
    out_len = lz_dstlen;
    lz_hdr_put(out, in_len);
    if (!lz_write_all(dst, out, LZSS_HDR_SIZE + out_len)) {
        free(data);
        free(out);
        printf("lzss: cannot create %s\n", dst);
        return LZSS_EXIT_FAIL;
    }
    printf("lzss: %s -> %s (%d -> %d bytes)\n", src, dst, in_len, out_len + LZSS_HDR_SIZE);
    free(data);
    free(out);
    return 0;
}

static int lz_decompress(const char *src, const char *dst) {
    char hdr[LZSS_HDR_SIZE];
    char *data;
    char *out;
    int in_len;
    int size;
    int bound;
    int got;
    data = lz_read_all(src, &in_len);
    if (!data) {
        printf("unlzss: cannot open %s\n", src);
        return LZSS_EXIT_FAIL;
    }
    if (in_len < LZSS_HDR_SIZE) {
        free(data);
        printf("unlzss: %s: truncated header\n", src);
        return LZSS_EXIT_FAIL;
    }
    got = 0;
    while (got < LZSS_HDR_SIZE) {
        hdr[got] = data[got];
        got++;
    }
    size = lz_hdr_get(hdr);
    if (size < 0) {
        free(data);
        printf("unlzss: %s: bad magic\n", src);
        return LZSS_EXIT_FAIL;
    }
    bound = (in_len - LZSS_HDR_SIZE) * LZSS_EXPAND_NUM / LZSS_EXPAND_DEN + LZSS_F;
    if (size > bound) {
        free(data);
        printf("unlzss: %s: declared size out of range\n", src);
        return LZSS_EXIT_FAIL;
    }
    out = malloc(size > 0 ? size : 1);
    if (!out) {
        free(data);
        printf("unlzss: out of memory\n");
        return LZSS_EXIT_FAIL;
    }
    lz_src = data + LZSS_HDR_SIZE;
    lz_srclen = in_len - LZSS_HDR_SIZE;
    lz_srcpos = 0;
    lz_dst = out;
    lz_dstcap = size;
    lz_dstlen = 0;
    lz_err = LZSS_ERR_NONE;
    if (lz_decode() != LZSS_ERR_NONE) {
        free(data);
        free(out);
        printf("unlzss: %s: truncated stream\n", src);
        return LZSS_EXIT_FAIL;
    }
    if (lz_dstlen != size) {
        free(data);
        free(out);
        printf("unlzss: %s: truncated stream\n", src);
        return LZSS_EXIT_FAIL;
    }
    if (!lz_write_all(dst, out, size)) {
        free(data);
        free(out);
        printf("unlzss: cannot create %s\n", dst);
        return LZSS_EXIT_FAIL;
    }
    printf("unlzss: %s -> %s (%d -> %d bytes)\n", src, dst, in_len, size);
    free(data);
    free(out);
    return 0;
}

int main(int argc, char **argv) {
    int decode;
    int a;
    decode = (argc >= 1 && lz_has(argv[0], "unlzss"));
    a = 1;
    if (!decode && argc >= 2 && strcmp(argv[1], "-d") == 0) {
        decode = 1;
        a = 2;
    }
    if (argc - a != 2) {
        if (decode) printf("usage: unlzss <src> <dst>\n");
        else printf("usage: lzss [-d] <src> <dst>\n");
        return LZSS_EXIT_FAIL;
    }
    if (decode) return lz_decompress(argv[a], argv[a + 1]);
    return lz_compress(argv[a], argv[a + 1]);
}
