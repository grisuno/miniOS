/* lz4.c - command path LZ4 (de)compression tools: lz4 and unlz4.
 * One source builds both binaries; the linker emits the same program as
 * bin/lz4 and bin/unlz4 and the program picks its mode from argv[0] (any
 * invocation path containing "unlz4" decodes, and -d forces decode).
 *
 * The codec lives in the kernel (lz4_kernel.c, the same one MiniFS uses), so
 * these tools are thin front-ends over the two MiniOS syscalls 216
 * (lz4_compress) and 217 (lz4_decompress), which mirror
 * minifs_compress/minifs_decompress byte for byte.  The on-disk block is
 * therefore the MiniFS LZ4 block format: a 4-byte little-endian original
 * size, then the raw LZ4 stream.  Every shortfall and implausible declared
 * size is a diagnostic plus a nonzero exit code, never a partial write. */

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

int lz4_compress(char *src, int srclen, char *dst, int dstcap);
int lz4_decompress(char *src, int srclen, char *dst, int dstcap);

#define LZ4_HDR_SIZE 4
#define LZ4_BOUND_DEN 255
#define LZ4_BOUND_SLACK 16
#define LZ4_MAX_BLOCK (16 * 1024 * 1024)

#define LZ4_SEEK_END 2

#define LZ4_EXIT_FAIL 1

static int lz4_has(const char *s, const char *needle) {
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

static char *lz4_read_all(const char *name, int *len) {
    char *data;
    int got;
    void *f = fopen((char *)name, "r");
    if (!f) return 0;
    fseek(f, 0, LZ4_SEEK_END);
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

static int lz4_write_all(const char *name, char *data, int len) {
    int n;
    void *f = fopen((char *)name, "w");
    if (!f) return 0;
    n = fwrite(data, 1, len, f);
    if (n != len) { fclose(f); return 0; }
    if (fclose(f) != 0) return 0;
    return 1;
}

static int lz4_compress_file(const char *src, const char *dst) {
    char *data;
    char *out;
    int in_len;
    int cap;
    int res;
    data = lz4_read_all(src, &in_len);
    if (!data) {
        printf("lz4: cannot open %s\n", src);
        return LZ4_EXIT_FAIL;
    }
    cap = LZ4_HDR_SIZE + in_len + in_len / LZ4_BOUND_DEN + LZ4_BOUND_SLACK;
    out = malloc(cap > 0 ? cap : 1);
    if (!out) {
        free(data);
        printf("lz4: out of memory\n");
        return LZ4_EXIT_FAIL;
    }
    res = lz4_compress(data, in_len, out, cap);
    if (res <= 0) {
        free(data);
        free(out);
        printf("lz4: %s: not compressible\n", src);
        return LZ4_EXIT_FAIL;
    }
    if (!lz4_write_all(dst, out, res)) {
        free(data);
        free(out);
        printf("lz4: cannot create %s\n", dst);
        return LZ4_EXIT_FAIL;
    }
    printf("lz4: %s -> %s (%d -> %d bytes)\n", src, dst, in_len, res);
    free(data);
    free(out);
    return 0;
}

static int lz4_decompress_file(const char *src, const char *dst) {
    char *data;
    char *out;
    int in_len;
    int orig;
    int res;
    data = lz4_read_all(src, &in_len);
    if (!data) {
        printf("unlz4: cannot open %s\n", src);
        return LZ4_EXIT_FAIL;
    }
    if (in_len < LZ4_HDR_SIZE) {
        free(data);
        printf("unlz4: %s: truncated header\n", src);
        return LZ4_EXIT_FAIL;
    }
    orig = (data[0] & 255) | ((data[1] & 255) << 8) | ((data[2] & 255) << 16) | ((data[3] & 255) << 24);
    if (orig <= 0 || orig > LZ4_MAX_BLOCK) {
        free(data);
        printf("unlz4: %s: implausible size\n", src);
        return LZ4_EXIT_FAIL;
    }
    out = malloc(orig);
    if (!out) {
        free(data);
        printf("unlz4: out of memory\n");
        return LZ4_EXIT_FAIL;
    }
    res = lz4_decompress(data, in_len, out, orig);
    if (res != orig) {
        free(data);
        free(out);
        printf("unlz4: %s: invalid stream\n", src);
        return LZ4_EXIT_FAIL;
    }
    if (!lz4_write_all(dst, out, orig)) {
        free(data);
        free(out);
        printf("unlz4: cannot create %s\n", dst);
        return LZ4_EXIT_FAIL;
    }
    printf("unlz4: %s -> %s (%d -> %d bytes)\n", src, dst, in_len, orig);
    free(data);
    free(out);
    return 0;
}

int main(int argc, char **argv) {
    int decode;
    int a;
    decode = (argc >= 1 && lz4_has(argv[0], "unlz4"));
    a = 1;
    if (!decode && argc >= 2 && strcmp(argv[1], "-d") == 0) {
        decode = 1;
        a = 2;
    }
    if (argc - a != 2) {
        if (decode) printf("usage: unlz4 <src> <dst>\n");
        else printf("usage: lz4 [-d] <src> <dst>\n");
        return LZ4_EXIT_FAIL;
    }
    if (decode) return lz4_decompress_file(argv[a], argv[a + 1]);
    return lz4_compress_file(argv[a], argv[a + 1]);
}
