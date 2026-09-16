#ifndef RTC_H
#define RTC_H

int rtc_read_tod(int *hour, int *min, int *sec);

/* Calendar date from the CMOS RTC (registers 0x07-0x09). Full year
 * (CMOS carries two digits; 0..99 maps to 2000..2099). Fail-closed like
 * the time reader: impossible month/day (including Feb 29 on a
 * non-leap year) or a clock that never stops updating returns 0 and
 * writes nothing. */
int rtc_read_date(int *year, int *mon, int *day);

/* Days since 1970-01-01 for a civil date (Howard Hinnant's algorithm,
 * pure integer arithmetic, no tables). Powers rtc_wall_seconds and the
 * host suite (tests/test_rtc.c); valid for the full 2000..2099 CMOS
 * window and far beyond. Lives here (not in rtc.c) so the host test can
 * compile it without the port-I/O half of the driver. */
static inline long rtc_days_from_civil(long y, long m, long d) {
    long era, yoe, mp, doy, doe;
    y -= m <= 2;
    era = (y >= 0 ? y : y - 399) / 400;
    yoe = y - era * 400;
    mp = m + (m > 2 ? -3 : 9);
    doy = (153 * mp + 2) / 5 + d - 1;
    doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + doe - 719468;
}

/* Wall-clock seconds since the Unix epoch from one RTC snapshot.
 * Returns 1 and stores the value, or 0 on any RTC failure (caller
 * decides the fallback; TLS treats 0 as "no clock" and fails the
 * chain check closed downstream). */
int rtc_wall_seconds(unsigned long *out);

#endif
