/** Docstring: Host test for sanitize.h (make test-sanitize).
 *
 * Stubs the four symbols the macros name and asserts every refusal path:
 * negative lengths, out-of-window ranges and strings, wrapped
 * count-by-size products, and the exact EFAULT value on every refusal.
 * A mutant that drops any check returns success where this test demands
 * EFAULT, so it dies here with no QEMU boot.
 */

#include <stdio.h>
#include <string.h>

#define EFAULT (-14)

static int range_ok_result = 1;
static int str_ok_result = 1;
static int copied_bytes = -1;
static unsigned long last_range_len = 0;

int user_range_ok(unsigned long p, unsigned long len) {
    (void)p;
    last_range_len = len;
    return range_ok_result;
}

int user_str_ok(unsigned long p, unsigned long maxlen) {
    (void)p;
    (void)maxlen;
    return str_ok_result;
}

void *kmemcpy(void *dst, const void *src, unsigned long n) {
    copied_bytes = (int)n;
    return memcpy(dst, src, (unsigned long)n);
}

#include "sanitize.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

static long range_probe(unsigned long p, long len) {
    SANITIZE_LEN_NEG(len);
    SANITIZE_RANGE(p, len);
    return 0;
}

static long str_probe(unsigned long p) {
    SANITIZE_STR(p, 255);
    return 0;
}

static char kbuf[64];

static long copy_probe(unsigned long uptr, long count, unsigned long elemsz) {
    copied_bytes = -1;
    SANITIZE_COPY_IN(kbuf, uptr, count, elemsz);
    return 0;
}

int main(void) {
    {
        range_ok_result = 1;
        CHECK(range_probe(0x400000UL, 8) == 0, "valid range passes");
        range_ok_result = 0;
        CHECK(range_probe(0x400000UL, 8) == EFAULT, "bad range is EFAULT");
        CHECK(range_probe(0x400000UL, 8) != -EFAULT, "refusal is negative");
        CHECK(range_probe(0x400000UL, -1) == EFAULT, "negative len refused");
    }
    {
        str_ok_result = 1;
        CHECK(str_probe(0x400000UL) == 0, "valid string passes");
        str_ok_result = 0;
        CHECK(str_probe(0x400000UL) == EFAULT, "bad string is EFAULT");
    }
    {
        static char src[32];
        int i;
        for (i = 0; i < 32; i++)
            src[i] = (char)(i + 1);
        range_ok_result = 1;
        CHECK(copy_probe((unsigned long)src, 8, 4) == 0, "copy passes");
        CHECK(copied_bytes == 32, "copy moves count times size");
        CHECK(copy_probe((unsigned long)src, -2, 4) == EFAULT,
              "negative count refused before copy");
        CHECK(copied_bytes == -1, "refused copy moves nothing");
        last_range_len = 0;
        range_ok_result = 0;
        CHECK(copy_probe((unsigned long)src, -1, 1) == EFAULT,
              "negative unit count refused");
        CHECK(last_range_len == 0,
              "negative count never reaches the range check");
        range_ok_result = 1;
        CHECK(copy_probe((unsigned long)src, 4, 0) == EFAULT,
              "zero element size refused");
        CHECK(copy_probe((unsigned long)src, 0x100000000L, 0x100000000UL) == EFAULT,
              "wrapped product refused");
        range_ok_result = 0;
        CHECK(copy_probe((unsigned long)src, 8, 4) == EFAULT,
              "out-of-window copy refused");
    }
    if (failures == 0)
        printf("sanitize: ok\n");
    else
        printf("sanitize: %d failures\n", failures);
    return failures != 0;
}
