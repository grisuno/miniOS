/* test_ktime.c -- host test for the pure conversion math in ktime.h
 * (make test-ktime). ktime_us_from_delta must convert calibrated TSC
 * deltas to microseconds without the 64-bit overflow a naive delta*1000
 * would hit on a long-lived machine, and wall_us_from_parts must anchor
 * a monotonic fraction to the last RTC second so gettimeofday ordering
 * holds across the second edge. The port I/O and RTC reads stay
 * kernel-only; only the arithmetic is pinned here. The in-guest proof
 * is the `clock` builtin plus the BDD clock scenario. */
#include <stdio.h>

#include "ktime.h"

static int failures = 0;
#define CHECK(c, m) do { if (!(c)) { failures++; fprintf(stderr, "FAIL: %s:%d: %s\n", __FILE__, __LINE__, m); } } while (0)

int main(void) {
    CHECK(ktime_us_from_delta(0, 3000000UL) == 0, "zero delta");
    CHECK(ktime_us_from_delta(3000000UL, 3000000UL) == 1000UL, "one ms is 1000 us");
    CHECK(ktime_us_from_delta(1500000UL, 3000000UL) == 500UL, "half ms");
    CHECK(ktime_us_from_delta(1, 3000000UL) == 0, "sub-us tick truncates");
    CHECK(ktime_us_from_delta(3000UL, 3000000UL) == 1UL, "one us");
    CHECK(ktime_us_from_delta(0, 0) == 0, "zero ratio fails closed");
    CHECK(ktime_us_from_delta(3000001UL, 3000000UL) == 1000UL, "remainder path");
    CHECK(ktime_us_from_delta(6000000UL, 3000000UL) == 2000UL, "multi-ms");
    {
        unsigned long huge = 0xFFFFFFFFFFFFFFFFUL;
        unsigned long got = ktime_us_from_delta(huge, 3000000UL);
        unsigned long want = (huge / 3000000UL) * 1000UL +
                             ((huge % 3000000UL) * 1000UL) / 3000000UL;
        CHECK(got == want, "near-2^64 delta never wraps");
        CHECK(got > 1000000UL * 1000000UL, "huge delta stays huge");
    }
    CHECK(wall_us_from_parts(100, 5000UL, 5000UL) == 100000000UL, "anchored base");
    CHECK(wall_us_from_parts(100, 5000UL, 5500UL) == 100000500UL, "fraction advances");
    CHECK(wall_us_from_parts(101, 9999000UL, 2000UL) == 101000000UL + 2000UL - 9999000UL,
          "rebase arithmetic is caller-driven");
    if (!failures) printf("ktime: ok\n");
    return failures ? 1 : 0;
}
