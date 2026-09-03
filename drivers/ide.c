/* IDE/ATA PIO driver for MiniOS.
 *
 * Polled I/O on the primary controller (0x1F0/0x3F6).  No interrupts,
 * no DMA.  Enough to read/write sectors on a QEMU IDE disk. */

#include "kernel.h"
#include "ide.h"

static int          ide_disk_present;
static unsigned int ide_disk_sectors;

static void ide_delay(void) {
    volatile unsigned i;
    /* A short CPU spin, NOT a port read.  The old loop read the IDE control
     * register 1000 times as a crude timer, which under KVM turns every one of
     * those reads into a VM-exit.  ide_select_drive calls this twice per
     * sector, so reading a 4 MB WAD ran into millions of exits and took
     * minutes.  A pause loop keeps the small settle delay without any I/O. */
    for (i = 0; i < 200; i++) __asm__ volatile("pause");
}

static unsigned char ide_read_status(void) {
    return inb(IDE_PRIMARY_BASE + IDE_REG_STATUS);
}

static int ide_wait_not_busy(unsigned int timeout) {
    unsigned int i;
    for (i = 0; i < timeout; i++) {
        if (!(ide_read_status() & IDE_STATUS_BSY)) return 0;
    }
    return -1;
}

static int ide_wait_drq(unsigned int timeout) {
    unsigned int i;
    for (i = 0; i < timeout; i++) {
        unsigned char s = ide_read_status();
        if (s & IDE_STATUS_ERR) return -1;
        if (s & IDE_STATUS_DF)  return -1;
        if (s & IDE_STATUS_DRQ) return 0;
    }
    return -1;
}

static void ide_select_drive(unsigned char drive) {
    outb(IDE_PRIMARY_BASE + IDE_REG_DRIVE,
         IDE_DRIVE_LBA | (drive ? IDE_DRIVE_SLAVE : IDE_DRIVE_MASTER));
    ide_delay();
}

static void ide_soft_reset(void) {
    outb(IDE_PRIMARY_CTRL, 0x04);
    ide_delay();
    outb(IDE_PRIMARY_CTRL, 0x00);
    ide_delay();
}

static int ide_identify(void) {
    unsigned short buf[256];
    unsigned int i;

    ide_select_drive(0);
    outb(IDE_PRIMARY_BASE + IDE_REG_SECCOUNT, 0);
    outb(IDE_PRIMARY_BASE + IDE_REG_LBA_LO, 0);
    outb(IDE_PRIMARY_BASE + IDE_REG_LBA_MID, 0);
    outb(IDE_PRIMARY_BASE + IDE_REG_LBA_HI, 0);
    outb(IDE_PRIMARY_BASE + IDE_REG_STATUS, IDE_CMD_IDENTIFY);

    if (ide_wait_drq(IDE_TIMEOUT) < 0) return -1;

    for (i = 0; i < 256; i++)
        buf[i] = inw(IDE_PRIMARY_BASE + IDE_REG_DATA);

    if (buf[0] == 0 || buf[0] == 0xFFFF) return -1;

    ide_disk_sectors = ((unsigned int)buf[61] << 16) | buf[60];
    if (ide_disk_sectors == 0 && (buf[83] & 0x0400))
        ide_disk_sectors = ((unsigned int)buf[103] << 16) | buf[102];

    return 0;
}

void ide_init(void) {
    ide_disk_present = 0;
    ide_disk_sectors = 0;

    ide_soft_reset();
    ide_wait_not_busy(IDE_TIMEOUT);
    ide_select_drive(0);
    ide_delay();

    if (ide_identify() == 0) {
        ide_disk_present = 1;
        kprintf("IDE: disk detected, %u sectors (%u MB)\n",
                ide_disk_sectors, ide_disk_sectors / 2048);
    } else {
        kprintf("IDE: no disk on primary master\n");
    }
}

int ide_present(void) { return ide_disk_present; }
unsigned int ide_total_sectors(void) { return ide_disk_sectors; }

int ide_read_sectors(unsigned int lba, unsigned int count, void *buf) {
    unsigned char *p = (unsigned char *)buf;
    unsigned int i;

    if (!ide_disk_present) return -1;
    if (lba + count > ide_disk_sectors) return -1;

    /* Issue ONE multi-sector read command (SECCOUNT = count) instead of one
     * command per sector, then pull the data with a DRQ wait before each
     * sector's worth of words.  Under QEMU every port access is a VM-exit, so
     * collapsing count command setups into one measurably speeds bulk loads. */
    if (ide_wait_not_busy(IDE_TIMEOUT) < 0) return -1;
    ide_select_drive(0);
    outb(IDE_PRIMARY_BASE + IDE_REG_SECCOUNT, (unsigned char)count);
    outb(IDE_PRIMARY_BASE + IDE_REG_LBA_LO, (unsigned char)(lba));
    outb(IDE_PRIMARY_BASE + IDE_REG_LBA_MID, (unsigned char)(lba >> 8));
    outb(IDE_PRIMARY_BASE + IDE_REG_LBA_HI, (unsigned char)(lba >> 16));
    outb(IDE_PRIMARY_BASE + IDE_REG_DRIVE,
         IDE_DRIVE_LBA | IDE_DRIVE_MASTER | (unsigned char)((lba >> 24) & 0x0F));
    outb(IDE_PRIMARY_BASE + IDE_REG_STATUS, IDE_CMD_READ);

    for (i = 0; i < count; i++) {
        unsigned int j;
        if (ide_wait_drq(IDE_TIMEOUT) < 0) return -1;
        for (j = 0; j < IDE_SECTOR_SIZE / 2; j++)
            ((unsigned short *)p)[j] = inw(IDE_PRIMARY_BASE + IDE_REG_DATA);
        p += IDE_SECTOR_SIZE;
    }
    return 0;
}

int ide_write_sectors(unsigned int lba, unsigned int count, const void *buf) {
    const unsigned char *p = (const unsigned char *)buf;
    unsigned int i;

    if (!ide_disk_present) return -1;
    if (lba + count > ide_disk_sectors) return -1;

    if (ide_wait_not_busy(IDE_TIMEOUT) < 0) return -1;
    ide_select_drive(0);
    outb(IDE_PRIMARY_BASE + IDE_REG_SECCOUNT, (unsigned char)count);
    outb(IDE_PRIMARY_BASE + IDE_REG_LBA_LO, (unsigned char)(lba));
    outb(IDE_PRIMARY_BASE + IDE_REG_LBA_MID, (unsigned char)(lba >> 8));
    outb(IDE_PRIMARY_BASE + IDE_REG_LBA_HI, (unsigned char)(lba >> 16));
    outb(IDE_PRIMARY_BASE + IDE_REG_DRIVE,
         IDE_DRIVE_LBA | IDE_DRIVE_MASTER | (unsigned char)((lba >> 24) & 0x0F));
    outb(IDE_PRIMARY_BASE + IDE_REG_STATUS, IDE_CMD_WRITE);

    for (i = 0; i < count; i++) {
        unsigned int j;
        if (ide_wait_drq(IDE_TIMEOUT) < 0) return -1;
        for (j = 0; j < IDE_SECTOR_SIZE / 2; j++)
            outw(IDE_PRIMARY_BASE + IDE_REG_DATA, ((const unsigned short *)p)[j]);
        p += IDE_SECTOR_SIZE;
    }
    if (ide_wait_not_busy(IDE_TIMEOUT) < 0) return -1;
    outb(IDE_PRIMARY_BASE + IDE_REG_STATUS, IDE_CMD_FLUSH);
    ide_wait_not_busy(IDE_TIMEOUT);
    return 0;
}

int ide_read_sector(unsigned int lba, void *buf) {
    return ide_read_sectors(lba, 1, buf);
}

int ide_write_sector(unsigned int lba, const void *buf) {
    return ide_write_sectors(lba, 1, buf);
}
