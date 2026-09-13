/** Docstring: tests/test_abi.c -- Host test for the ABI manifest gate.
 *
 * Compiles kernel/abi.c with ABI_HOST_TEST and asserts every verify
 * outcome: a matching manifest passes, version drift, checksum drift and
 * every malformed input fail closed with distinct codes. Prints
 * "abi: ok" only when all vectors hold.
 */

#include <stdio.h>

#include "abi.h"
#include "progs/minios_abi.h"

static int fails = 0;

static void expect(const char *name, const char *manifest, int want) {
    int got = abi_verify(manifest, MINIOS_ABI_VERSION,
                         (unsigned long)MINIOS_ABI_CHECKSUM);
    if (got != want) {
        printf("FAIL: %s: want %d got %d\n", name, want, got);
        fails++;
    }
}

int main(void) {
    char good[ABI_MANIFEST_MAX];
    char tmp[ABI_MANIFEST_MAX];
    unsigned long sum = (unsigned long)MINIOS_ABI_CHECKSUM;
    int v = MINIOS_ABI_VERSION;
    int n, i;

    n = snprintf(good, sizeof(good), "v=%d c=%lu\n", v, sum);
    if (n <= 0 || n >= (int)sizeof(good)) {
        printf("FAIL: fixture did not fit\n");
        return 1;
    }
    expect("match", good, ABI_OK);

    n = snprintf(tmp, sizeof(tmp), "v=%d c=%lu\n", v + 1, sum);
    if (n > 0 && n < (int)sizeof(tmp))
        expect("version drift", tmp, ABI_VERSION_MISMATCH);
    n = snprintf(tmp, sizeof(tmp), "v=%d c=%lu\n", v, sum + 1);
    if (n > 0 && n < (int)sizeof(tmp))
        expect("checksum drift", tmp, ABI_CHECKSUM_MISMATCH);

    expect("null", 0, ABI_BAD_FORMAT);
    expect("empty", "", ABI_BAD_FORMAT);
    expect("garbage", "hello\n", ABI_BAD_FORMAT);
    expect("version only", "v=6\n", ABI_BAD_FORMAT);
    expect("checksum only", "c=123\n", ABI_BAD_FORMAT);
    expect("swapped", "c=1 v=2\n", ABI_BAD_FORMAT);
    expect("trailing junk", "v=6 c=1 xyz\n", ABI_BAD_FORMAT);
    expect("leading junk", "x v=6 c=1\n", ABI_BAD_FORMAT);
    expect("negative", "v=-1 c=1\n", ABI_BAD_FORMAT);
    expect("huge version", "v=99999999999999999999 c=1\n", ABI_BAD_FORMAT);
    expect("huge checksum", "v=6 c=99999999999999999999\n", ABI_BAD_FORMAT);
    expect("no newline", "v=6 c=1", ABI_BAD_FORMAT);

    for (i = 0; i < 40; i++) tmp[i] = 'A';
    tmp[40] = 0;
    expect("long garbage", tmp, ABI_BAD_FORMAT);

    if (fails) {
        printf("abi: %d failures\n", fails);
        return 1;
    }
    printf("abi: ok\n");
    return 0;
}
