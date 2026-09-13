/** Docstring: kernel/abi.c -- Boot-time ABI manifest gate.
 *
 * Strict parser for the etc/abi manifest plus the ramdisk-backed check
 * kmain runs before the shell. The accepted text is exactly
 * "v=<decimal> c=<decimal>\n": any deviation (missing field, swapped
 * order, junk, overflow, missing newline) fails closed as BAD_FORMAT.
 * Number parsing carries its own overflow guard so a hostile manifest
 * can never wrap into a false match. The file has no kernel dependency
 * beyond the manifest check itself, so the host test compiles it with
 * ABI_HOST_TEST and covers every branch without a QEMU boot.
 */

#include "abi.h"

#ifndef ABI_HOST_TEST
#include "kernel.h"
#endif

/** Docstring: Parse one decimal field, overflow-guarded. */
static int abi_parse_num(const char **pp, const char *end, unsigned long *out) {
    const char *p = *pp;
    unsigned long v = 0;
    if (p >= end || *p < '0' || *p > '9')
        return 0;
    while (p < end && *p >= '0' && *p <= '9') {
        unsigned digit = (unsigned)(*p - '0');
        if (v > (0xFFFFFFFFFFFFFFFFUL - digit) / 10)
            return 0;
        v = v * 10 + digit;
        p++;
    }
    *pp = p;
    *out = v;
    return 1;
}

/** Docstring: Verify manifest text against the running ABI. */
int abi_verify(const char *text, long version, unsigned long checksum) {
    const char *p, *end;
    unsigned long v = 0, c = 0;
    int i;
    if (!text)
        return ABI_BAD_FORMAT;
    for (i = 0; i < ABI_MANIFEST_MAX && text[i]; i++)
        ;
    if (i >= ABI_MANIFEST_MAX)
        return ABI_BAD_FORMAT;
    p = text;
    end = text + i;
    if (p + 2 > end || p[0] != 'v' || p[1] != '=')
        return ABI_BAD_FORMAT;
    p += 2;
    if (!abi_parse_num(&p, end, &v))
        return ABI_BAD_FORMAT;
    if (p >= end || *p != ' ')
        return ABI_BAD_FORMAT;
    p++;
    if (p + 2 > end || p[0] != 'c' || p[1] != '=')
        return ABI_BAD_FORMAT;
    p += 2;
    if (!abi_parse_num(&p, end, &c))
        return ABI_BAD_FORMAT;
    if (p + 1 != end || *p != '\n')
        return ABI_BAD_FORMAT;
    if ((long)v != version)
        return ABI_VERSION_MISMATCH;
    if (c != checksum)
        return ABI_CHECKSUM_MISMATCH;
    return ABI_OK;
}

#ifndef ABI_HOST_TEST
/** Docstring: Read etc/abi from the ramdisk and verify the running ABI. */
int abi_check_manifest(void) {
    RDFile *f = ramdisk_open(ABI_MANIFEST_NAME);
    char buf[ABI_MANIFEST_MAX];
    int i, rc;
    if (!f)
        return ABI_NO_MANIFEST;
    if (f->size == 0 || f->size >= (unsigned)ABI_MANIFEST_MAX)
        return ABI_BAD_FORMAT;
    for (i = 0; i < ABI_MANIFEST_MAX; i++)
        buf[i] = 0;
    if (ramdisk_read(f, buf, 0, f->size) != (int)f->size)
        return ABI_BAD_FORMAT;
    buf[f->size] = 0;
    rc = abi_verify(buf, (long)MINIOS_ABI_VERSION,
                    (unsigned long)MINIOS_ABI_CHECKSUM);
    return rc;
}
#endif
