/** Docstring: Host-test stand-in for headers/kernel.h (tests/stubs first on
 * the include path, so driver sources built for make test-usb* see this
 * instead of the kernel header).
 *
 * Provides the kernel services the USB drivers need with hosted
 * equivalents: malloc-backed heap, memset/memcpy maps, a controllable
 * millisecond clock, printf logging and no-op interrupt flags. Anything
 * the tests must observe (fed scancodes, queued bytes, registered devices)
 * is recorded in variables the test files own. Never included by kernel
 * code: the Makefile only adds tests/stubs to the host-test builds.
 */

#ifndef TEST_STUB_KERNEL_H
#define TEST_STUB_KERNEL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdarg.h>

#define PCI_MMIO_SIZE 0x00040000UL

static __attribute__((unused)) void *kmalloc(unsigned long size) {
    return malloc(size ? size : 1);
}

/** Docstring: Aligned blocks from kmalloc_aligned are not freed by the
 * host tests, so no base-pointer recovery is needed here. */
static __attribute__((unused)) void kfree(void *p) {
    free(p);
}

static __attribute__((unused)) void *kmalloc_aligned(unsigned long size, unsigned long align) {
    uintptr_t raw;
    uintptr_t aligned;
    void **slot;
    if (align < sizeof(void *)) align = sizeof(void *);
    if (size == 0) size = 1;
    raw = (uintptr_t)malloc(size + align);
    if (!raw) return 0;
    aligned = (raw + sizeof(void *) + align - 1u) & ~(uintptr_t)(align - 1u);
    slot = (void **)(aligned - sizeof(void *));
    *slot = (void *)raw;
    return (void *)aligned;
}

#define kmemset memset
#define kmemcpy memcpy

static __attribute__((unused)) int kprintf(const char *fmt, ...) {
    va_list ap;
    int n;
    va_start(ap, fmt);
    n = vprintf(fmt, ap);
    va_end(ap);
    return n;
}

static __attribute__((unused)) int kmm_make_uncached(unsigned long phys, unsigned long len) {
    (void)phys;
    (void)len;
    return 1;
}

static __attribute__((unused)) unsigned long kmm_map_device(unsigned long phys,
                                            unsigned long len) {
    (void)len;
    return phys;
}

extern unsigned long stub_ms_now;

static __attribute__((unused)) unsigned long ktime_ms(void) {
    return stub_ms_now;
}

typedef unsigned long irqflags_t;

static __attribute__((unused)) irqflags_t spin_save_irq(void) {
    return 0;
}

static __attribute__((unused)) void spin_restore_irq(irqflags_t flags) {
    (void)flags;
}

#endif
