# headers

*Community 2 | 5 files | cohesion 0.44*

## Definition

This community groups 5 file(s) rooted at `headers` with dominant language c (cohesion 0.44). Central symbols: `CHECK`, `QGA_BAUD_DIVISOR`, `QGA_COM2_BASE`, `QGA_COM2_IRQ`, `QGA_FILE_MAX`, `QGA_FILE_READ_MAX`, `QGA_H`, `QGA_KEY_MAX`. Core file: `headers/qga.h` (29 symbols). Documented purpose: CMOS RTC time-of-day reader. The desktop clock and the shell `date` builtin.

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/rtc.c` | c | infrastructure | 25 | yes |
| `headers/qga.h` | h | utility | 29 | yes |
| `headers/rtc.h` | h | utility | 6 | no |
| `qga.c` | c | utility | 27 | yes |
| `tests/test_rtc.c` | c | testing | 2 | yes |

## Key Symbols

- `RTC_CMOS_ADDR` (macro, `drivers/rtc.c:9`) `#define RTC_CMOS_ADDR`
- `RTC_CMOS_DATA` (macro, `drivers/rtc.c:10`) `#define RTC_CMOS_DATA`
- `RTC_REG_SEC` (macro, `drivers/rtc.c:12`) `#define RTC_REG_SEC`
- `RTC_REG_MIN` (macro, `drivers/rtc.c:13`) `#define RTC_REG_MIN`
- `RTC_REG_HOUR` (macro, `drivers/rtc.c:14`) `#define RTC_REG_HOUR`
- `RTC_REG_DAY` (macro, `drivers/rtc.c:15`) `#define RTC_REG_DAY`
- `RTC_REG_MON` (macro, `drivers/rtc.c:16`) `#define RTC_REG_MON`
- `RTC_REG_YEAR` (macro, `drivers/rtc.c:17`) `#define RTC_REG_YEAR`
- `RTC_REG_STATUS_A` (macro, `drivers/rtc.c:18`) `#define RTC_REG_STATUS_A`
- `RTC_REG_STATUS_B` (macro, `drivers/rtc.c:19`) `#define RTC_REG_STATUS_B`
- `RTC_UPDATE_IN_PROGRESS` (macro, `drivers/rtc.c:21`) `#define RTC_UPDATE_IN_PROGRESS`
- `RTC_BCD_FLAG` (macro, `drivers/rtc.c:22`) `#define RTC_BCD_FLAG`
- `RTC_HOUR_MIN` (macro, `drivers/rtc.c:24`) `#define RTC_HOUR_MIN`
- `RTC_HOUR_MAX` (macro, `drivers/rtc.c:25`) `#define RTC_HOUR_MAX`
- `RTC_MIN_MIN` (macro, `drivers/rtc.c:26`) `#define RTC_MIN_MIN`
- `RTC_MIN_MAX` (macro, `drivers/rtc.c:27`) `#define RTC_MIN_MAX`
- `RTC_SEC_MIN` (macro, `drivers/rtc.c:28`) `#define RTC_SEC_MIN`
- `RTC_SEC_MAX` (macro, `drivers/rtc.c:29`) `#define RTC_SEC_MAX`
- `RTC_UPDATE_WAIT` (macro, `drivers/rtc.c:33`) `#define RTC_UPDATE_WAIT`
- `rtc_cmos_read` (function, `drivers/rtc.c:35`) `static inline unsigned char rtc_cmos_read(unsigned char reg)`
- `rtc_from_bcd` (function, `drivers/rtc.c:40`) `static int rtc_from_bcd(unsigned char v)`
- `rtc_read_tod` (function, `drivers/rtc.c:44`) `int rtc_read_tod(int *hour, int *min, int *sec)`
- `rtc_month_len` (function, `drivers/rtc.c:68`) `static int rtc_month_len(long full_year, long mon)`
- `rtc_read_date` (function, `drivers/rtc.c:78`) `int rtc_read_date(int *year, int *mon, int *day)`
- `rtc_wall_seconds` (function, `drivers/rtc.c:102`) `int rtc_wall_seconds(unsigned long *out)`
- `QGA_H` (macro, `headers/qga.h:2`) `#define QGA_H`
- `QGA_COM2_BASE` (macro, `headers/qga.h:5`) `#define QGA_COM2_BASE`
- `QGA_COM2_IRQ` (macro, `headers/qga.h:6`) `#define QGA_COM2_IRQ`
- `QGA_UART_THR` (macro, `headers/qga.h:9`) `#define QGA_UART_THR`
- `QGA_UART_RBR` (macro, `headers/qga.h:10`) `#define QGA_UART_RBR`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 4
- Cross-boundary resolved imports (EXTRACTED): 5

## Connections

- [EXTRACTED] depends_on community 2 <-> 0 (strength 0.9): Extracted import edge crosses communities: drivers/rtc.c imports headers/kernel.h.
- [INFERRED] shares_context community 1 <-> 2 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 1 (headers) and community 2 (headers).

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 1 file(s) lack file-level docs (e.g. `headers/rtc.h`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.44?

## Sources

- `drivers/rtc.c`
- `headers/qga.h`
- `headers/rtc.h`
- `qga.c`
- `tests/test_rtc.c`
