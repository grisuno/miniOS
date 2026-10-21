/** Docstring: panic.h -- Kernel panic backtrace contract (header-only).
 *
 * Single source of truth for the frame-pointer chain walk shared by the
 * fault handler (kernel/sched.c via kernel/panic.c) and the `panic`
 * builtin demo. Header-only like pipe.h: the walk core is pure pointer
 * arithmetic over a caller-supplied validity predicate, so
 * tests/test_panic.c (make test-panic) drives it on the host with canned
 * frames and no kernel stubs.
 *
 * The walk never dereferences anything the predicate refuses. A null,
 * unchanged or invalid rbp stops the chain; at most PANIC_BT_MAX
 * return addresses are reported, never more. */

#ifndef PANIC_H
#define PANIC_H

#define PANIC_BT_MAX 5

/** Docstring: Widest hex field the banner prints: a 64-bit value. */
#define PANIC_HEX_MAX_DIGITS 16

/** Docstring: Format an unsigned long as fixed-width lowercase hex into
 * buf, writing exactly digits characters plus a NUL terminator, so the
 * buffer must hold digits + 1 bytes. digits is clamped to
 * [0, PANIC_HEX_MAX_DIGITS] and to the buffer capacity, so the widest
 * field never writes past the terminator. Returns the number of
 * characters written. */
static inline int panic_hex_str(char *buf, int cap, unsigned long v, int digits) {
    static const char d[] = "0123456789abcdef";
    int i;
    if (!buf || cap <= 0)
        return 0;
    if (digits < 0)
        digits = 0;
    if (digits > PANIC_HEX_MAX_DIGITS)
        digits = PANIC_HEX_MAX_DIGITS;
    if (cap < digits + 1)
        digits = cap - 1;
    for (i = 0; i < digits; i++)
        buf[i] = d[(v >> ((digits - 1 - i) * 4)) & 0xF];
    buf[digits] = 0;
    return digits;
}

typedef int (*panic_valid_fn)(unsigned long addr);

/** Docstring: Walk up to max frame pointers from rbp, storing each
 * frame's return address (*(rbp+8)) into out. Stops on null rbp,
 * failed predicate, a non-advancing frame or a null return address.
 * Returns the stored count. Fail-closed on null out or null predicate. */
static inline int panic_backtrace(unsigned long rbp, panic_valid_fn valid,
        unsigned long *out, int max) {
    int n = 0;
    if (!valid || !out || max <= 0)
        return 0;
    if (max > PANIC_BT_MAX)
        max = PANIC_BT_MAX;
    while (n < max) {
        unsigned long *fp;
        unsigned long next;
        unsigned long ret;
        if (rbp == 0u)
            break;
        if (!valid(rbp) || !valid(rbp + 8u))
            break;
        fp = (unsigned long *)rbp;
        next = fp[0];
        ret = fp[1];
        if (ret == 0u)
            break;
        out[n++] = ret;
        if (next == 0u || next == rbp)
            break;
        rbp = next;
    }
    return n;
}

#endif
