#ifndef IDE_H
#define IDE_H

/* IDE/ATA PIO driver for MiniOS.
 * Primary controller: base 0x1F0, control 0x3F6.
 * Polled I/O (no interrupts), PIO mode only. */

/* Primary ATA controller ports */
#define IDE_PRIMARY_BASE    0x1F0
#define IDE_PRIMARY_CTRL    0x3F6

/* Register offsets from base */
#define IDE_REG_DATA        0   /* R/W: data port (16-bit) */
#define IDE_REG_ERROR       1   /* R: error, W: features */
#define IDE_REG_SECCOUNT    2   /* R/W: sector count / LBA low (48-bit) */
#define IDE_REG_LBA_LO      3   /* R/W: LBA bits 0-7 */
#define IDE_REG_LBA_MID     4   /* R/W: LBA bits 8-15 */
#define IDE_REG_LBA_HI      5   /* R/W: LBA bits 16-23 */
#define IDE_REG_DRIVE       6   /* R/W: drive/head register */
#define IDE_REG_STATUS      7   /* R: status, W: command */
#define IDE_REG_ALTSTATUS   6   /* R: alternate status (control port) */

/* Status register bits */
#define IDE_STATUS_ERR      0x01
#define IDE_STATUS_DRQ      0x08
#define IDE_STATUS_SRV      0x10
#define IDE_STATUS_DF       0x20
#define IDE_STATUS_RDY      0x40
#define IDE_STATUS_BSY      0x80

/* Commands */
#define IDE_CMD_READ        0x20    /* READ SECTORS (28-bit LBA) */
#define IDE_CMD_WRITE       0x30    /* WRITE SECTORS (28-bit LBA) */
#define IDE_CMD_IDENTIFY    0xEC    /* IDENTIFY DEVICE */
#define IDE_CMD_FLUSH       0xE7    /* FLUSH CACHE */

/* Drive/Head register bits */
#define IDE_DRIVE_LBA       0x40    /* LBA mode */
#define IDE_DRIVE_MASTER    0xA0    /* master drive */
#define IDE_DRIVE_SLAVE     0xB0    /* slave drive */

/* Timeout in PIT ticks (approximate) */
#define IDE_TIMEOUT         1000000

/* Sector size in bytes */
#define IDE_SECTOR_SIZE     512

/* Initialize the IDE driver: probe, IDENTIFY, report geometry. */
void ide_init(void);

/* Read/write sectors using 28-bit LBA.
 * Returns 0 on success, -1 on error. */
int ide_read_sectors(unsigned int lba, unsigned int count, void *buf);
int ide_write_sectors(unsigned int lba, unsigned int count, const void *buf);

/* Convenience: single sector read/write. */
int ide_read_sector(unsigned int lba, void *buf);
int ide_write_sector(unsigned int lba, const void *buf);

/* Returns total sectors on the disk, or 0 if not detected. */
unsigned int ide_total_sectors(void);

/* Returns 1 if a disk was successfully detected. */
int ide_present(void);

#endif
