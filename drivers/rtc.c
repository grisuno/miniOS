#include "kernel.h"
#include "rtc.h"

/* CMOS RTC time-of-day reader. The desktop clock and the shell `date` builtin
 * both pull from here, so the framebuffer taskbar and the serial console can
 * never disagree about the wall-clock time. Every port and register number is
 * named; nothing is a bare literal. */

#define RTC_CMOS_ADDR    0x70
#define RTC_CMOS_DATA    0x71

#define RTC_REG_SEC      0x00
#define RTC_REG_MIN      0x02
#define RTC_REG_HOUR     0x04
#define RTC_REG_DAY      0x07
#define RTC_REG_MON      0x08
#define RTC_REG_YEAR     0x09
#define RTC_REG_STATUS_A 0x0A
#define RTC_REG_STATUS_B 0x0B

#define RTC_UPDATE_IN_PROGRESS 0x80
#define RTC_BCD_FLAG           0x04

#define RTC_HOUR_MIN 0
#define RTC_HOUR_MAX 23
#define RTC_MIN_MIN  0
#define RTC_MIN_MAX  59
#define RTC_SEC_MIN  0
#define RTC_SEC_MAX  59

/* The RTC reports a time-of-day that is mid-update; waiting out this flag
 * before reading the three fields makes the snapshot consistent. */
#define RTC_UPDATE_WAIT 100000

static inline unsigned char rtc_cmos_read(unsigned char reg) {
    outb(RTC_CMOS_ADDR, reg);
    return inb(RTC_CMOS_DATA);
}

static int rtc_from_bcd(unsigned char v) {
    return (int)((v & 0x0F) + ((v >> 4) * 10));
}

int rtc_read_tod(int *hour, int *min, int *sec) {
    int spins;
    int hr, mn, sc;
    if (!hour || !min || !sec) return 0;
    for (spins = 0; spins < RTC_UPDATE_WAIT; spins++)
        if (!(rtc_cmos_read(RTC_REG_STATUS_A) & RTC_UPDATE_IN_PROGRESS)) break;
    hr = rtc_cmos_read(RTC_REG_HOUR);
    mn = rtc_cmos_read(RTC_REG_MIN);
    sc = rtc_cmos_read(RTC_REG_SEC);
    if (!(rtc_cmos_read(RTC_REG_STATUS_B) & RTC_BCD_FLAG)) {
        hr = rtc_from_bcd((unsigned char)hr);
        mn = rtc_from_bcd((unsigned char)mn);
        sc = rtc_from_bcd((unsigned char)sc);
    }
    if (hr < RTC_HOUR_MIN || hr > RTC_HOUR_MAX ||
        mn < RTC_MIN_MIN || mn > RTC_MIN_MAX ||
        sc < RTC_SEC_MIN || sc > RTC_SEC_MAX)
        return 0;
    *hour = hr;
    *min = mn;
    *sec = sc;
    return 1;
}

static int rtc_month_len(long full_year, long mon) {
    static const unsigned char lens[12] =
        { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    unsigned char n = lens[mon - 1];
    if (mon == 2 && full_year % 4 == 0 &&
        (full_year % 100 != 0 || full_year % 400 == 0))
        n = 29;
    return (int)n;
}

int rtc_read_date(int *year, int *mon, int *day) {
    int spins;
    int yy, mo, dy;
    long full;
    if (!year || !mon || !day) return 0;
    for (spins = 0; spins < RTC_UPDATE_WAIT; spins++)
        if (!(rtc_cmos_read(RTC_REG_STATUS_A) & RTC_UPDATE_IN_PROGRESS)) break;
    dy = rtc_cmos_read(RTC_REG_DAY);
    mo = rtc_cmos_read(RTC_REG_MON);
    yy = rtc_cmos_read(RTC_REG_YEAR);
    if (!(rtc_cmos_read(RTC_REG_STATUS_B) & RTC_BCD_FLAG)) {
        dy = rtc_from_bcd((unsigned char)dy);
        mo = rtc_from_bcd((unsigned char)mo);
        yy = rtc_from_bcd((unsigned char)yy);
    }
    if (yy < 0 || yy > 99 || mo < 1 || mo > 12) return 0;
    full = 2000L + (long)yy;
    if (dy < 1 || dy > rtc_month_len(full, (long)mo)) return 0;
    *year = (int)full;
    *mon = mo;
    *day = dy;
    return 1;
}

int rtc_wall_seconds(unsigned long *out) {
    int h, m, s, y, mo, dy;
    long days;
    if (!out) return 0;
    if (!rtc_read_tod(&h, &m, &s)) return 0;
    if (!rtc_read_date(&y, &mo, &dy)) return 0;
    days = rtc_days_from_civil((long)y, (long)mo, (long)dy);
    if (days < 0) return 0;
    *out = (unsigned long)days * 86400UL +
           (unsigned long)h * 3600UL +
           (unsigned long)m * 60UL + (unsigned long)s;
    return 1;
}
