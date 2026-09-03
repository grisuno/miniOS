#include "kernel.h"
#include "lz4_kernel.h"

#define HASH_BITS 12
#define HASH_SIZE (1 << HASH_BITS)

static inline unsigned int LZ4_read32(const unsigned char *p)
{
    unsigned int v;
    kmemcpy(&v, p, 4);
    return v;
}

static inline unsigned int LZ4_read16(const unsigned char *p)
{
    unsigned short v;
    kmemcpy(&v, p, 2);
    return v;
}

static inline void LZ4_write16(unsigned char *dst, unsigned short v)
{
    kmemcpy(dst, &v, 2);
}

static unsigned int LZ4_hash(const unsigned char *p)
{
    unsigned int v = LZ4_read32(p);
    v *= 0x9E3779B9u;
    return v >> (32 - HASH_BITS);
}

int LZ4_compressBound(int inputSize)
{
    if (inputSize <= 0)
        return 1;
    return inputSize + (inputSize / 255) + 16;
}

int LZ4_compress_default(const char *src, char *dst, int srcSize, int dstCapacity)
{
    int hash_table[HASH_SIZE];
    const unsigned char *input = (const unsigned char *)src;
    unsigned char *op = (unsigned char *)dst;
    const unsigned char *anchor = input;
    const unsigned char *ip;
    const unsigned char *iend = input + srcSize;
    int ml_field, ll_field, token;

    if (srcSize <= 0)
        return 0;
    if (dstCapacity < LZ4_compressBound(srcSize))
        return 0;

    kmemset(hash_table, 0, sizeof(hash_table));

    if (srcSize < 13)
        goto _last_literals;

    ip = input + 5;

    while (ip + 8 <= iend) {
        unsigned int h = LZ4_hash(ip);
        int seq = hash_table[h];
        unsigned int match_off;
        const unsigned char *mstart;
        int match_len = 0;

        hash_table[h] = (int)(ip - input);

        if (seq < 0)
            goto _next_literal;
        match_off = (unsigned int)seq;
        mstart = input + match_off;

        if (LZ4_read32(mstart) == LZ4_read32(ip)) {
            match_len = 4;
            while (ip + match_len + 4 <= iend &&
                   LZ4_read32(ip + match_len) == LZ4_read32(mstart + match_len))
                match_len += 4;
            while (ip + match_len < iend && mstart[match_len] == ip[match_len])
                match_len++;
        }

        if (match_len < 4) {
_next_literal:
            ip++;
            continue;
        }

        {
            int literal_len = (int)(ip - anchor);
            int max_dist = (int)(ip - mstart);
            int ml = match_len - 4;

            if (max_dist > 65535)
                max_dist = 0;

            ll_field = literal_len < 15 ? literal_len : 15;
            ml_field = ml < 15 ? ml : 15;
            token = (ll_field << 4) | ml_field;
            *op++ = (unsigned char)token;

            if (ll_field == 15) {
                int rem = literal_len - 15;
                while (rem >= 255) {
                    *op++ = 255;
                    rem -= 255;
                }
                *op++ = (unsigned char)rem;
            }

            kmemcpy(op, anchor, (unsigned long)literal_len);
            op += literal_len;

            LZ4_write16(op, (unsigned short)max_dist);
            op += 2;

            if (ml_field == 15) {
                int rem = ml - 15;
                while (rem >= 255) {
                    *op++ = 255;
                    rem -= 255;
                }
                *op++ = (unsigned char)rem;
            }

            ip += match_len;
            anchor = ip;

            {
                unsigned int h2 = LZ4_hash(ip);
                hash_table[h2] = (int)(ip - input);
            }
            ip++;
            continue;
        }
    }

_last_literals:
    {
        int remaining = (int)(iend - anchor);

        ll_field = remaining < 15 ? remaining : 15;
        token = ll_field << 4;
        *op++ = (unsigned char)token;

        if (ll_field == 15) {
            int rem = remaining - 15;
            while (rem >= 255) {
                *op++ = 255;
                rem -= 255;
            }
            *op++ = (unsigned char)rem;
        }

        kmemcpy(op, anchor, (unsigned long)remaining);
        op += remaining;
    }

    return (int)(op - (unsigned char *)dst);
}

int LZ4_decompress_safe(const char *src, char *dst, int compressedSize, int dstCapacity)
{
    const unsigned char *ip = (const unsigned char *)src;
    unsigned char *op = (unsigned char *)dst;
    const unsigned char *iend = ip + compressedSize;
    unsigned char *oend = op + dstCapacity;

    if (compressedSize < 0 || dstCapacity < 0)
        return -1;

    while (ip < iend) {
        const unsigned char *match;
        int token, literal_len, match_len, offset;

        token = *ip++;
        literal_len = (token >> 4) & 0x0F;
        match_len = token & 0x0F;

        if (literal_len == 15) {
            int extra;
            do {
                if (ip >= iend)
                    return -1;
                extra = *ip++;
                literal_len += extra;
            } while (extra == 255);
        }

        if (ip + literal_len > iend)
            return -1;
        if (op + literal_len + 2 > oend)
            return -1;

        kmemcpy(op, ip, (unsigned long)literal_len);
        op += literal_len;
        ip += literal_len;

        if (ip >= iend)
            break;          /* final literal-only sequence: clean end */
        if (ip + 2 > iend)
            return -1;

        offset = LZ4_read16(ip);
        ip += 2;

        if (offset == 0)
            return -1;

        match_len += 4;

        if (match_len == 19) {
            int extra;
            do {
                if (ip >= iend)
                    return -1;
                extra = *ip++;
                match_len += extra;
            } while (extra == 255);
        }

        match = op - offset;
        if (match < (unsigned char *)dst)
            return -1;

        if (op + match_len > oend)
            return -1;

        {
            int i;
            for (i = 0; i < match_len; i++)
                op[i] = match[i];
        }
        op += match_len;
    }

    return (int)(op - (unsigned char *)dst);
}
