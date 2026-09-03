#include "kernel.h"

/* ================================================================
 *  PIT-calibrated TSC for SYS_TIME (syscall 204)
 *  PIT channel 2 one-shot measures real TSC ticks per millisecond
 *  so the timer works regardless of the host CPU frequency.
 * ================================================================ */

static unsigned long tsc_per_ms;
static unsigned long tsc_base_ms;

static unsigned long ktime_rdtsc(void) {
    unsigned int lo, hi;
    __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long)hi << 32) | lo;
}

static void ktime_init(void) {
    unsigned long t0, t1;
    outb(0x61, (unsigned char)((inb(0x61) & 0x0F) | 0x01));
    outb(0x43, 0xB0);
    outb(0x42, 0x96);
    outb(0x42, 0x04);
    t0 = ktime_rdtsc();
    while (!(inb(0x61) & 0x20));
    t1 = ktime_rdtsc();
    outb(0x61, (unsigned char)(inb(0x61) & 0x0F));
    tsc_per_ms  = t1 - t0;
    tsc_base_ms = t0;
}

unsigned long ktime_ms(void) {
    if (!tsc_per_ms) ktime_init();
    return (ktime_rdtsc() - tsc_base_ms) / tsc_per_ms;
}
