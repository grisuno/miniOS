/** Docstring: drivers/usbblk.h -- boundary of the USB mass-storage driver.
 *
 * Speaks Bulk-Only Transport and SCSI to a USB disk and registers it with the
 * existing block layer, so VFS, the page cache and ls/cat work on a USB stick
 * with no change and no new syscall. A disk whose capacity cannot be read is
 * not registered, so it can never become the backend and cannot be handed a
 * sector count that is wrong.
 */

#ifndef DRIVERS_USBBLK_H
#define DRIVERS_USBBLK_H

/* ---- SCSI logical block size and the READ(10)/WRITE(10) ceiling ---- */
#define UBK_BLOCK_SIZE 512
#define UBK_MAX_BLOCKS 0x200000u
#define UBK_MAX_SECTORS ((unsigned long)UBK_MAX_BLOCKS * UBK_BLOCK_SIZE)

/** Docstring: Bring up mass storage on every enumerated device. Returns the
 * number of disks registered, which is 0 on a machine with none and is not an
 * error. */
int ubk_init(void);

/** Docstring: True when a USB disk was registered and is the active backend. */
int ubk_present(void);

/** Docstring: Sector count of the registered disk. */
unsigned long ubk_sectors(void);

/** Docstring: Read or write whole 512-byte sectors. Returns 1 on success,
 * 0 on a refused request: a range outside the disk, a short transfer, a
 * command failure or a stale CSW. Never reports a partial block as read. */
int ubk_read_sectors(unsigned long lba, unsigned count, void *buf);
int ubk_write_sectors(unsigned long lba, unsigned count, const void *buf);

/** Docstring: Counters, so a disk that is absent is distinguishable from a
 * driver that is broken. */
typedef struct {
    unsigned long commands;
    unsigned long read_blocks;
    unsigned long write_blocks;
    unsigned long failures;
    unsigned long stalls;
} ubk_counters_t;

/** Docstring: Snapshot the counters. */
void ubk_counters(ubk_counters_t *out);

/** Docstring: Build a Command Block Wrapper into out, which must have room for
 * UBK_CBW_LEN bytes. Pure, for the host test: a CBW whose fields disagree
 * with its arguments is a command the device must reject, and getting the
 * residue wrong makes a short write look complete. */
void ubk_build_cbw(unsigned char *out, unsigned tag, unsigned long lba,
                   unsigned blocks, int read, int data_len);

/** Docstring: Check a Command Status Wrapper. Returns 1 when the CSW matches
 * the CBW it was sent with and reports success, 0 otherwise. Pure, for the
 * same reason. The residue check is what catches a device that moved fewer
 * bytes than asked for: without it a truncated sector read would be handed
 * back as good data. */
int ubk_check_csw(const unsigned char *csw, unsigned tag, unsigned expect_len);

#endif