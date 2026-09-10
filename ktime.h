#ifndef KTIME_H
#define KTIME_H

/* ktime.h -- pure time-conversion helpers shared by the kernel clock
 * (kernel/time.c) and the host suite (tests/test_ktime.c).
 *
 * The PIT-calibrated TSC gives ticks; tsc_per_ms converts them to
 * milliseconds. Microsecond resolution needs the same ratio without a
 * 64-bit overflow: delta_ticks can approach 2^64 on a long-lived
 * machine, and delta*1000 would wrap past the range check class the
 * file-I/O overflow guards were written for. The split-quotient form
 * below never multiplies by more than 1000x a sub-per-ms remainder.
 *
 * Lives here (not in time.c) so the host test pins the arithmetic
 * without port I/O; the in-guest proof is the `clock` builtin and the
 * BDD clock scenario. Phase 0.2/0.3 of the FreeDom readiness plan.
 */

static inline unsigned long ktime_us_from_delta(unsigned long delta_ticks,
                                                unsigned long tsc_per_ms) {
    if (!tsc_per_ms) return 0;
    return (delta_ticks / tsc_per_ms) * 1000UL +
           ((delta_ticks % tsc_per_ms) * 1000UL) / tsc_per_ms;
}

/* wall_us_from_parts: wall-clock microseconds from an RTC-anchored base.
 * base_sec is the last seen RTC second, base_ktime_us the monotonic
 * clock then, now_ktime_us the monotonic clock now. Pure so the host
 * suite pins the rollover math; the kernel feeds it live values. */
static inline unsigned long wall_us_from_parts(unsigned long base_sec,
                                               unsigned long base_ktime_us,
                                               unsigned long now_ktime_us) {
    return base_sec * 1000000UL + (now_ktime_us - base_ktime_us);
}

#endif
