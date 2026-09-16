#ifndef RANDMIX_H
#define RANDMIX_H

/* randmix.h -- entropy mixer for getrandom (318).
 *
 * The old handler emitted TSC XOR loop index: fully predictable to any
 * peer that knows the boot time. The new handler gathers RDRAND when
 * the CPU offers it plus TSC, tick and pid jitter, and folds every
 * 64-bit seed through splitmix64, whose avalanche makes each output
 * bit depend on every input bit. A weak source still diffuses; a dead
 * source (all-zero seed) still walks, because the increment is inside
 * the mixer, not in the caller.
 *
 * Only the pure mixer lives here so the host suite (tests/test_randmix.c,
 * make test-randmix) pins distribution and avalanche without RDRAND or
 * port I/O. RDRAND gathering stays in kernel/syscalls.c (kernel-only
 * inline asm). Phase 0.5 of the FreeDom readiness plan.
 */

static inline unsigned long randmix64(unsigned long x) {
    x += 0x9E3779B97F4A7C15UL;
    x = (x ^ (x >> 30)) * 0xBF58476D1CE4E5B9UL;
    x = (x ^ (x >> 27)) * 0x94D049BB133111EBUL;
    return x ^ (x >> 31);
}

#endif
