/** Docstring: abi.h -- Boot-time ABI manifest gate contract.
 *
 * The ramdisk carries etc/abi, stamped at build time with the
 * MINIOS_ABI_VERSION and MINIOS_ABI_CHECKSUM the whole image was built
 * from. The kernel compares the manifest against its own compiled
 * constants before starting the shell: a ramdisk from a different source
 * generation halts the boot with a diagnostic instead of running
 * mismatched binaries. Linux-ABI binaries carry no MiniOS version note
 * and stay ungated; the gate covers the kernel/ramdisk generation match,
 * which is the drift this repository can produce.
 */

#ifndef ABI_H
#define ABI_H

#define ABI_OK 0
#define ABI_NO_MANIFEST 1
#define ABI_BAD_FORMAT 2
#define ABI_VERSION_MISMATCH 3
#define ABI_CHECKSUM_MISMATCH 4

#define ABI_MANIFEST_NAME "etc/abi"
#define ABI_MANIFEST_MAX 64

int abi_verify(const char *text, long version, unsigned long checksum);

#ifndef ABI_HOST_TEST
int abi_check_manifest(void);
#endif

#endif
