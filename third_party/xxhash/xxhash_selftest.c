/* xxhash_selftest.c — ring-0 ET_REL self-test for the kernel's XXH64 symbol.
 *
 * Runs three known-answer vectors (empty string seed-0, "hello\n" seed-0,
 * "hello\n" seed-1) against the kernel-registered XXH64 and prints a single
 * pass/fail string.  A wrong vector or a resolution failure is a hard error
 * with a diagnostic; the success string is the BDD hook.
 *
 * Build: gcc -c -ffreestanding -m64 -mno-red-zone -fno-pic -o objects/xxhash.o xxhash_selftest.c
 * Ship on the ramdisk as objects/xxhash.o.
 * Usage: run objects/xxhash.o
 */
extern unsigned long long XXH64(const void *input, unsigned long length,
                                unsigned long long seed);
extern int printf(const char *fmt, ...);

int main(void) {
    unsigned long long h;

    h = XXH64("", 0, 0);
    if (h != 0xEF46DB3751D8E999ULL) {
        printf("xxhash: empty seed0 FAIL (%016llx)\n", h);
        return 1;
    }

    h = XXH64("hello\n", 6, 0);
    if (h != 0xE4C191D091BD8853ULL) {
        printf("xxhash: hello seed0 FAIL (%016llx)\n", h);
        return 1;
    }

    h = XXH64("hello\n", 6, 1);
    if (h != 0xC3196D5BC6356E3BULL) {
        printf("xxhash: hello seed1 FAIL (%016llx)\n", h);
        return 1;
    }

    printf("xxhash: ok (3 vectors pass)\n");
    return 0;
}
