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
