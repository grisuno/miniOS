/** Docstring: Host test for headers/panic.h (make test-panic).
 *
 * Drives panic_backtrace with canned frame chains on the stack.
 * Verifies the full chain, null-rbp stop, invalid-frame stop,
 * non-advancing stop, null-return stop, max clamping, and the
 * fail-closed null predicate/out/garbage-max paths, so a mutant that
 * drops a stop condition dies on the host with no QEMU boot.
 */

#include <stdio.h>

#include "panic.h"

static int failures = 0;

#define CHECK(cond, msg) do { \
    if (!(cond)) { \
        failures++; \
        fprintf(stderr, "FAIL: %s (line %d)\n", (msg), __LINE__); \
    } \
} while (0)

static int always_valid(unsigned long addr) {
    (void)addr;
    return 1;
}

static int never_valid(unsigned long addr) {
    (void)addr;
    return 0;
}

static unsigned long deny_hi;

static int deny_valid(unsigned long addr) {
    return addr < deny_hi;
}

int main(void) {
    unsigned long f1[2], f2[2], f3[2];
    unsigned long out[8];
    int i;

    f1[0] = (unsigned long)&f2[0];
    f1[1] = 0x1111u;
    f2[0] = (unsigned long)&f3[0];
    f2[1] = 0x2222u;
    f3[0] = 0u;
    f3[1] = 0x3333u;

    CHECK(panic_backtrace((unsigned long)&f1[0], always_valid, out, 8) == 3, "full chain");
    CHECK(out[0] == 0x1111u && out[1] == 0x2222u && out[2] == 0x3333u, "chain order");
    CHECK(panic_backtrace(0u, always_valid, out, 8) == 0, "null rbp");
    CHECK(panic_backtrace((unsigned long)&f1[0], never_valid, out, 8) == 0, "invalid first");
    CHECK(panic_backtrace((unsigned long)&f1[0], 0, out, 8) == 0, "null predicate");
    CHECK(panic_backtrace((unsigned long)&f1[0], always_valid, 0, 8) == 0, "null out");
    CHECK(panic_backtrace((unsigned long)&f1[0], always_valid, out, 0) == 0, "zero max");
    CHECK(panic_backtrace((unsigned long)&f1[0], always_valid, out, 2) == 2, "max clamp");
    CHECK(out[0] == 0x1111u && out[1] == 0x2222u, "clamp order");

    f2[0] = (unsigned long)&f2[0];
    CHECK(panic_backtrace((unsigned long)&f1[0], always_valid, out, 8) == 2, "self-loop stops");
    f2[0] = (unsigned long)&f3[0];

    f2[1] = 0u;
    CHECK(panic_backtrace((unsigned long)&f1[0], always_valid, out, 8) == 1, "null ret stops");
    CHECK(out[0] == 0x1111u, "null ret keeps prior");
    f2[1] = 0x2222u;

    deny_hi = (unsigned long)&f2[0];
    CHECK(panic_backtrace((unsigned long)&f1[0], deny_valid, out, 8) == 1, "invalid mid stops");
    CHECK(out[0] == 0x1111u, "mid stop keeps prior");

    for (i = 0; i < 8; i++)
        out[i] = 0u;
    CHECK(panic_backtrace((unsigned long)&f1[0], always_valid, out, 100) == 3, "huge max clamps");

    /* Hex formatting: the widest field must write its digits plus the
     * terminator and nothing else. A 16-digit field used to write one
     * byte past a 16-byte buffer, landing on the caller's saved frame
     * pointer; the canary below proves the bound holds. */
    {
        struct {
            char buf[PANIC_HEX_MAX_DIGITS + 1];
            char canary;
        } cell;
        cell.canary = (char)0x5A;
        CHECK(panic_hex_str(cell.buf, (int)sizeof(cell.buf), 0xdeadbeefcafe1234UL, 16) == 16,
              "widest field writes 16 digits");
        CHECK(cell.canary == (char)0x5A, "widest field leaves the canary alone");
        CHECK(cell.buf[16] == 0, "widest field terminates inside the buffer");
        CHECK(panic_hex_str(cell.buf, (int)sizeof(cell.buf), 0xABUL, 2) == 2, "narrow field");
        CHECK(cell.buf[0] == 'a' && cell.buf[1] == 'b' && cell.buf[2] == 0, "narrow field digits");
        CHECK(panic_hex_str(cell.buf, (int)sizeof(cell.buf), 0xFFUL, 99) == 16, "digits clamp to 16");
        CHECK(panic_hex_str(cell.buf, (int)sizeof(cell.buf), 0xFFUL, -3) == 0, "negative digits give 0");
        CHECK(panic_hex_str(cell.buf, (int)sizeof(cell.buf), 0xFFUL, 0) == 0, "zero digits give 0");
        CHECK(cell.buf[0] == 0, "zero digits still terminate");
        CHECK(panic_hex_str(cell.buf, 4, 0x1234UL, 16) == 3, "capacity clamps the field");
        CHECK(panic_hex_str(cell.buf, 0, 0x1234UL, 16) == 0, "no capacity writes nothing");
        CHECK(panic_hex_str(0, 16, 0x1234UL, 16) == 0, "null buffer writes nothing");
    }

    if (failures == 0)
        printf("panic: ok\n");
    return failures != 0;
}
