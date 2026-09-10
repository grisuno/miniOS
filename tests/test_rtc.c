/* test_rtc.c -- host test for the pure date math in drivers/rtc.c
 * (make test-rtc). rtc_days_from_civil must agree with the Unix
 * calendar on known vectors, including the year-2000 leap day (the
 * CMOS window is 2000..2099, and 2000 % 400 == 0, the exact case a
 * naive %4-and-not-%100 leap rule gets wrong). Vectors cross-checked
 * with `date -u -d <iso> +%s` / 86400. The CMOS register reads stay
 * kernel-only (inb/outb); only the arithmetic is pinned here. The
 * in-guest proof of the whole chain (RTC -> gettimeofday -> TLS
 * validity window) is `freedom google.cl` succeeding against a real
 * server, which needs external network and is not automated. */
#include <stdio.h>

#include "rtc.h"

static int failures = 0;
#define CHECK(c, m) do { if (!(c)) { failures++; fprintf(stderr, "FAIL: %s:%d: %s\n", __FILE__, __LINE__, m); } } while (0)

int main(void) {
    CHECK(rtc_days_from_civil(1970, 1, 1) == 0, "epoch is day zero");
    CHECK(rtc_days_from_civil(1970, 1, 2) == 1, "day after epoch");
    CHECK(rtc_days_from_civil(1969, 12, 31) == -1, "day before epoch");
    CHECK(rtc_days_from_civil(2000, 1, 1) == 10957, "y2k");
    CHECK(rtc_days_from_civil(2000, 2, 29) == 11016, "2000 leap day exists");
    CHECK(rtc_days_from_civil(2000, 3, 1) == 11017, "day after leap day");
    CHECK(rtc_days_from_civil(2001, 2, 28) == 11381, "non-leap feb end");
    CHECK(rtc_days_from_civil(2024, 2, 29) == 19782, "2024 leap day");
    CHECK(rtc_days_from_civil(2025, 6, 15) == 20254, "arbitrary date");
    CHECK(rtc_days_from_civil(2026, 9, 10) == 20706, "recent date");
    CHECK(rtc_days_from_civil(2099, 12, 31) == 47481, "cmos window end");
    CHECK(rtc_days_from_civil(2026, 9, 11) - rtc_days_from_civil(2026, 9, 10) == 1,
          "consecutive days differ by one");
    if (!failures) printf("rtc: ok\n");
    return failures ? 1 : 0;
}
