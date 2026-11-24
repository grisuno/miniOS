/** Docstring: drivers/ahci.h -- AHCI (SATA) host controller, polled.
 *
 * The SATA path of real hardware: every Intel PCH and AMD chipset since
 * ~2008 exposes its SATA ports as an AHCI function (PCI class 01:06:01),
 * and most firmware no longer offers an IDE compatibility mode. The
 * driver claims the first ATA disk with an established link and serves
 * 512-byte sectors through READ/WRITE DMA EXT on command slot 0, polled,
 * with no interrupt vector. */

#ifndef DRIVERS_AHCI_H
#define DRIVERS_AHCI_H

/** Docstring: Probe PCI for an AHCI function and bring up the first ATA
 * disk. Idempotent: a second call returns the cached result. Returns 1
 * when a disk is ready for I/O, 0 otherwise (ahci_note says why). */
int ahci_init(void);

/** Docstring: True once ahci_init brought a disk up. */
int ahci_present(void);

/** Docstring: HBA version register (major in bits 31:16, minor 15:0). */
unsigned ahci_version(void);

/** Docstring: Port number of the claimed disk, or -1 when none. */
int ahci_port(void);

/** Docstring: Bitmap of ports the HBA implements (PI register). */
unsigned ahci_ports_implemented(void);

/** Docstring: Human-readable state of the last probe. */
const char *ahci_note(void);

/** Docstring: Capacity of the claimed disk in 512-byte sectors. */
unsigned long ahci_sectors(void);

/** Docstring: Read count sectors starting at lba into buf. Any count is
 * accepted; it is split into AHCI_MAX_SECTORS commands. Returns 0 on
 * success, -1 on a bad argument, a range past the disk, a device error or
 * a timeout. */
int ahci_read_sectors(unsigned lba, unsigned count, void *buf);

/** Docstring: Write count sectors starting at lba from buf, followed by
 * FLUSH CACHE EXT so the data survives a power cut. Same contract as the
 * read. */
int ahci_write_sectors(unsigned lba, unsigned count, const void *buf);

/** Docstring: Publish the disk as "ahci0" in the device registry. */
void ahci_register_device(void);

#endif
