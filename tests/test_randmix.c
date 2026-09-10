/* test_randmix.c -- host test for the getrandom mixer in randmix.h
 * (make test-randmix). The old handler emitted TSC XOR loop index,
 * predictable from boot time; the new one folds every seed through
 * splitmix64. This pins three properties: determinism (same seed,
 * same stream), diffusion (one input bit flips about half the output
 * bits, so a weak source still spreads), and monobit frequency (the
 * output is not visibly biased). RDRAND gathering stays kernel-only
 * inline asm in kernel/syscalls.c; only the pure mixer is pinned here.
 * The in-guest proof is a getrandom BDD probe plus the statistical
 * shape of real output. */
#include <stdio.h>

#include "randmix.h"

static int failures = 0;
#define CHECK(c, m) do { if (!(c)) { failures++; fprintf(stderr, "FAIL: %s:%d: %s\n", __FILE__, __LINE__, m); } } while (0)

static int popcount64(unsigned long x) {
    int n = 0;
    while (x) { n += (int)(x & 1UL); x >>= 1; }
    return n;
}

int main(void) {
    CHECK(randmix64(0) == randmix64(0), "deterministic");
    CHECK(randmix64(0) != 0, "zero seed still walks");
    CHECK(randmix64(1) != randmix64(2), "distinct seeds differ");
    {
        int i, min_flip = 64, max_flip = 0;
        unsigned long base = randmix64(0x123456789ABCDEFUL);
        for (i = 0; i < 64; i++) {
            unsigned long v = randmix64(0x123456789ABCDEFUL ^ (1UL << i));
            int flips = popcount64(base ^ v);
            if (flips < min_flip) min_flip = flips;
            if (flips > max_flip) max_flip = flips;
        }
        CHECK(min_flip >= 16, "single-bit input flips at least a quarter of outputs");
        CHECK(max_flip <= 48, "single-bit input flips at most three quarters");
    }
    {
        unsigned long i, ones = 0, total = 0;
        for (i = 0; i < 4096; i++) {
            unsigned long v = randmix64(i * 0x9E3779B97F4A7C15UL + 0x12345UL);
            ones += (unsigned long)popcount64(v);
            total += 64;
        }
        CHECK(ones * 2 > total * 9 / 10, "monobit frequency above 0.45");
        CHECK(ones * 2 < total * 11 / 10, "monobit frequency below 0.55");
    }
    if (!failures) printf("randmix: ok\n");
    return failures ? 1 : 0;
}
