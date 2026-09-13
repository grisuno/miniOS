/** Docstring: tools/abi_stamp.c -- Build-time ABI manifest generator.
 *
 * Prints the etc/abi manifest for the ramdisk: the MINIOS_ABI_VERSION
 * and MINIOS_ABI_CHECKSUM the image is built from. Both values come
 * from progs/minios_abi.h, so the stamp can never disagree with the
 * sources; the kernel recomputes the same pair at boot and halts on
 * any difference.
 */

#include <stdio.h>

#include "progs/minios_abi.h"

int main(void) {
    printf("v=%d c=%lu\n", MINIOS_ABI_VERSION,
           (unsigned long)MINIOS_ABI_CHECKSUM);
    return 0;
}
