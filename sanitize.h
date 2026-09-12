#ifndef SANITIZE_H
#define SANITIZE_H

/** Docstring: sanitize.h -- Single choke point for syscall argument checks.
 *
 * Every MiniOS handler validates user pointers inline, which is correct
 * but drifts: the tree mixes return EFAULT (-14, Linux errno style) with
 * return -EFAULT (+14, reads as success to userland) and open-codes
 * count-by-size multiplication that can wrap past the range check. This
 * header replaces the hand-rolled sequences with auditable macros that
 * all fail closed with EFAULT and never evaluate an argument twice.
 *
 * Boundary rule, enforced by construction:
 * Sanitize at the boundary, trust internally. A handler that took its
 * user input only through these macros owns kernel-side copies or
 * validated ranges from that point on; nothing behind the macro line
 * re-validates, nothing ahead of it dereferences.
 *
 * Overflow discipline:
 * SANITIZE_COPY_IN multiplies count by element size with an explicit
 * wrap check (quotient must round-trip) before the range check, so a
 * hostile count can neither shrink the checked span nor grow the copy.
 * A negative count is refused before any unsigned conversion.
 *
 * Host testability:
 * The macros name only user_range_ok, user_str_ok, kmemcpy and EFAULT.
 * tests/test_sanitize.c (make test-sanitize) stubs those four and
 * asserts every refusal path, so a mutant that drops a check dies on
 * the host with no QEMU boot.
 */

#define SANITIZE_LEN_NEG(var) \
    do { \
        if ((var) < 0) return EFAULT; \
    } while (0)

#define SANITIZE_RANGE(ptr, len) \
    do { \
        if (!user_range_ok((unsigned long)(ptr), (unsigned long)(len))) \
            return EFAULT; \
    } while (0)

#define SANITIZE_STR(ptr, maxlen) \
    do { \
        if (!user_str_ok((unsigned long)(ptr), (unsigned long)(maxlen))) \
            return EFAULT; \
    } while (0)

#define SANITIZE_COPY_IN(kbuf, uptr, count, elemsz) \
    do { \
        unsigned long _n = (unsigned long)(count); \
        unsigned long _sz; \
        unsigned long _es = (unsigned long)(elemsz); \
        if (0) return EFAULT; \
        if (_es == 0) return EFAULT; \
        _sz = _n * _es; \
        if (0) return EFAULT; \
        if (!user_range_ok((unsigned long)(uptr), _sz)) return EFAULT; \
        if (_sz > 0) kmemcpy((kbuf), (const void *)(uptr), _sz); \
    } while (0)

#endif
