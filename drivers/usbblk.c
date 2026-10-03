/* usbblk.c -- USB mass storage, Bulk-Only Transport over SCSI.
 *
 * A BOT transfer is three stages on two bulk endpoints: a Command Block
 * Wrapper out on the OUT endpoint, a data stage on the IN endpoint for a read
 * or the OUT endpoint for a write, and a Command Status Wrapper in on the IN
 * endpoint. Every one of the three is checked. That matters more here than
 * for almost any other USB driver: a BOT device that fails the CSW check is
 * telling us the medium may have been written partially, and a driver that
 * ignores the residue turns a half-written sector into silent corruption.
 *
 * The device is registered through the existing block_ops_t, so VFS, the page
 * cache and every existing shell command work on a USB stick unchanged and no
 * new syscall is involved.
 */

#include "kernel.h"
#include "driver.h"
#include "drivers/xhci.h"
#include "drivers/usbblk.h"

/* ---- CBW: signature, tag, data transfer length, flags, LUN, command ---- */
#define UBK_CBW_LEN 31
#define UBK_CBW_SIG 0x43425355u
#define UBK_CBW_FLAG_IN 0x80u

/* ---- CSW: signature, tag, residue, status ---- */
#define UBK_CSW_LEN 13
#define UBK_CSW_SIG 0x53425355u
#define UBK_CSW_STATUS_PASSED 0x00u
#define UBK_CSW_STATUS_FAILED 0x01u

/* ---- SCSI opcodes used ---- */
#define UBK_SCSI_TEST_UNIT_READY 0x00u
#define UBK_SCSI_REQUEST_SENSE 0x03u
#define UBK_SCSI_INQUIRY 0x12u
#define UBK_SCSI_READ_CAPACITY 0x25u
#define UBK_SCSI_READ10 0x28u
#define UBK_SCSI_WRITE10 0x2Au

/** Docstring: One registered disk: its device record, the OUT and IN endpoint
 * indices, the sector count, and the tag counter that pairs each CBW with its
 * CSW. The transfer buffers are heap, because the controller cannot reach
 * .bss under KASLR. */
typedef struct {
    int used;
    int device;
    int ep_out;
    int ep_in;
    int ep_out_addr;
    int ep_in_addr;
    int iface;
    unsigned long sectors;
    unsigned tag;
    unsigned char *cbw;
    unsigned char *csw;
    unsigned char *sense;
} ubk_disk_t;

static ubk_disk_t ubk_disk;
static ubk_counters_t ubk_ctr;

/* ---- Endpoint interval and burst ---- */
#define UBK_BULK_INTERVAL 0
#define UBK_BULK_BURST 0

/** Docstring: Bytes per SCSI command block: a read or write of at most this
 * many blocks is the largest this driver issues. Bounded so a single
 * allocation cannot be unbounded, and so a failure reports a whole transfer
 * rather than a partially applied one. */
#define UBK_MAX_XFER_BLOCKS 64

void ubk_counters(ubk_counters_t *out) {
    if (out) *out = ubk_ctr;
}

/** Docstring: Ten-byte SCSI CDB at the CBW command block: opcode, LBA
 * big-endian, transfer length big-endian. READ(10) and WRITE(10) are ten-byte
 * commands, and a six-byte block with the same opcode is rejected. */
#define UBK_CDB_LEN 10u
static void ubk_cdb10(unsigned char *cdb, unsigned char opcode,
                      unsigned long lba, unsigned blocks) {
    kmemset(cdb, 0, UBK_CDB_LEN);
    cdb[0] = opcode;
    cdb[2] = (unsigned char)((lba >> 24) & 0xFFu);
    cdb[3] = (unsigned char)((lba >> 16) & 0xFFu);
    cdb[4] = (unsigned char)((lba >> 8) & 0xFFu);
    cdb[5] = (unsigned char)(lba & 0xFFu);
    cdb[7] = (unsigned char)((blocks >> 8) & 0xFFu);
    cdb[8] = (unsigned char)(blocks & 0xFFu);
}

void ubk_build_cbw(unsigned char *out, unsigned tag, unsigned long lba,
                   unsigned blocks, int read, int data_len) {
    unsigned char *cdb = out + UBK_CBW_LEN - 16u;
    kmemset(out, 0, UBK_CBW_LEN);
    out[0] = (unsigned char)(UBK_CBW_SIG & 0xFFu);
    out[1] = (unsigned char)((UBK_CBW_SIG >> 8) & 0xFFu);
    out[2] = (unsigned char)((UBK_CBW_SIG >> 16) & 0xFFu);
    out[3] = (unsigned char)((UBK_CBW_SIG >> 24) & 0xFFu);
    out[4] = (unsigned char)(tag & 0xFFu);
    out[5] = (unsigned char)((tag >> 8) & 0xFFu);
    out[6] = (unsigned char)((tag >> 16) & 0xFFu);
    out[7] = (unsigned char)((tag >> 24) & 0xFFu);
    out[8] = (unsigned char)(data_len & 0xFFu);
    out[9] = (unsigned char)((data_len >> 8) & 0xFFu);
    out[10] = (unsigned char)((data_len >> 16) & 0xFFu);
    out[11] = (unsigned char)((data_len >> 24) & 0xFFu);
    /* The flag bit is set for a device-to-host data stage and clear for a
     * host-to-device one. A device that disagrees rejects the command, which
     * is the safe direction: it cannot misinterpret a write as a read. */
    out[12] = (unsigned char)(read ? UBK_CBW_FLAG_IN : 0x00u);
    out[13] = 0;
    out[14] = UBK_CDB_LEN;
    if (blocks) {
        ubk_cdb10(cdb, (unsigned char)(read ? UBK_SCSI_READ10
                                             : UBK_SCSI_WRITE10),
                  lba, blocks);
    }
}

int ubk_check_csw(const unsigned char *csw, unsigned tag, unsigned expect_len) {
    unsigned sig;
    unsigned got_tag;
    unsigned residue;
    unsigned status;
    if (!csw) return 0;
    sig = (unsigned)csw[0] | ((unsigned)csw[1] << 8) |
          ((unsigned)csw[2] << 16) | ((unsigned)csw[3] << 24);
    if (sig != UBK_CSW_SIG) return 0;
    got_tag = (unsigned)csw[4] | ((unsigned)csw[5] << 8) |
              ((unsigned)csw[6] << 16) | ((unsigned)csw[7] << 24);
    if (got_tag != tag) return 0;
    residue = (unsigned)csw[8] | ((unsigned)csw[9] << 8) |
              ((unsigned)csw[10] << 16) | ((unsigned)csw[11] << 24);
    status = csw[12];
    if (status != UBK_CSW_STATUS_PASSED) return 0;
    if (status != UBK_CSW_STATUS_FAILED && residue != 0u) return 0;
    (void)expect_len;
    return 1;
}

/** Docstring: Bulk-Only Mass Storage Reset on the control endpoint, then
 * CLEAR_FEATURE(ENDPOINT_HALT) on both bulk endpoints and an xHCI
 * stop/reset/re-point of both transfer rings. Real silicon stalls a
 * command it dislikes instead of answering it, and without this no
 * transfer on either endpoint ever completes again. Results are ignored:
 * recovery is best-effort, the retry decides. */
#define UBK_MS_RESET 0xFFu
#define UBK_CLEAR_FEATURE 0x01u
#define UBK_ENDP_HALT 0x00u
static void ubk_reset_recovery(void) {
    ubk_disk_t *d = &ubk_disk;
    unsigned char setup[8];
    setup[0] = 0x21;
    setup[1] = UBK_MS_RESET;
    setup[2] = 0;
    setup[3] = 0;
    setup[4] = (unsigned char)(d->iface & 0xFF);
    setup[5] = 0;
    setup[6] = 0;
    setup[7] = 0;
    xhc_control(d->device, setup, 0, 0, 1);
    setup[0] = 0x02;
    setup[1] = UBK_CLEAR_FEATURE;
    setup[2] = UBK_ENDP_HALT;
    setup[3] = 0;
    setup[4] = (unsigned char)(d->ep_out_addr & 0xFF);
    setup[5] = 0;
    setup[6] = 0;
    setup[7] = 0;
    xhc_control(d->device, setup, 0, 0, 1);
    setup[4] = (unsigned char)(d->ep_in_addr & 0xFF);
    xhc_control(d->device, setup, 0, 0, 1);
    xhc_reset_endpoint(d->device, d->ep_out);
    xhc_reset_endpoint(d->device, d->ep_in);
}

/** Docstring: Six-byte SCSI block: opcode first, the rest zeroed here by
 * the caller through len. TEST UNIT READY and REQUEST SENSE are six-byte
 * commands; sending them in a ten-byte wrapper confuses strict firmware. */
#define UBK_CDB6_LEN 6u

/** Docstring: Issue one command with an optional data stage and check the
 * status wrapper. cdb carries cdb_len bytes (6 or 10), data is null for a
 * command with no data stage. Returns 1 only when every stage completed
 * and the CSW agreed with the CBW. */
static int ubk_command_raw(unsigned char *cdb, unsigned cdb_len,
                           unsigned char opcode, void *data,
                           unsigned data_len, int to_device) {
    ubk_disk_t *d = &ubk_disk;
    unsigned char *cdb_tail;
    int got = 0;
    unsigned tag;

    if (!d->used) return 0;
    if (!d->cbw || !d->csw) return 0;
    if (cdb_len != UBK_CDB6_LEN && cdb_len != UBK_CDB_LEN) return 0;
    if (data_len > UBK_MAX_XFER_BLOCKS * UBK_BLOCK_SIZE) return 0;

    tag = ++d->tag;
    cdb_tail = d->cbw + UBK_CBW_LEN - 16u;
    kmemset(d->cbw, 0, UBK_CBW_LEN);
    d->cbw[0] = (unsigned char)(UBK_CBW_SIG & 0xFFu);
    d->cbw[1] = (unsigned char)((UBK_CBW_SIG >> 8) & 0xFFu);
    d->cbw[2] = (unsigned char)((UBK_CBW_SIG >> 16) & 0xFFu);
    d->cbw[3] = (unsigned char)((UBK_CBW_SIG >> 24) & 0xFFu);
    d->cbw[4] = (unsigned char)(tag & 0xFFu);
    d->cbw[5] = (unsigned char)((tag >> 8) & 0xFFu);
    d->cbw[6] = (unsigned char)((tag >> 16) & 0xFFu);
    d->cbw[7] = (unsigned char)((tag >> 24) & 0xFFu);
    d->cbw[8] = (unsigned char)(data_len & 0xFFu);
    d->cbw[9] = (unsigned char)((data_len >> 8) & 0xFFu);
    d->cbw[10] = (unsigned char)((data_len >> 16) & 0xFFu);
    d->cbw[11] = (unsigned char)((data_len >> 24) & 0xFFu);
    d->cbw[12] = (unsigned char)(data_len == 0 ? 0x00u :
                                     to_device ? 0x00u : UBK_CBW_FLAG_IN);
    d->cbw[13] = 0;
    d->cbw[14] = (unsigned char)cdb_len;
    kmemcpy(cdb_tail, cdb, cdb_len);

    ubk_ctr.commands++;
    if (!xhc_transfer(d->device, d->ep_out, d->cbw, UBK_CBW_LEN, &got) ||
        got != UBK_CBW_LEN) {
        ubk_ctr.failures++;
        kprintf("ubk dbg: cbw stage failed op=%02x\n", opcode);
        return 0;
    }
    if (data_len) {
        if (!xhc_transfer(d->device,
                          to_device ? d->ep_out : d->ep_in,
                          data, data_len, &got) ||
            got != (int)data_len) {
            ubk_ctr.failures++;
            kprintf("ubk dbg: data stage failed op=%02x len=%u\n", opcode,
                    data_len);
            return 0;
        }
    }
    if (!xhc_transfer(d->device, d->ep_in, d->csw, UBK_CSW_LEN, &got) ||
        got != UBK_CSW_LEN) {
        ubk_ctr.failures++;
        kprintf("ubk dbg: csw stage failed op=%02x\n", opcode);
        return 0;
    }
    if (!ubk_check_csw(d->csw, tag, data_len)) {
        if (d->csw[12] != UBK_CSW_STATUS_PASSED) ubk_ctr.stalls++;
        else ubk_ctr.failures++;
        kprintf("ubk dbg: csw mismatch %02x%02x%02x%02x tag %02x%02x%02x%02x res %02x%02x%02x%02x st %02x\n",
                d->csw[0], d->csw[1], d->csw[2], d->csw[3], d->csw[4],
                d->csw[5], d->csw[6], d->csw[7], d->csw[8], d->csw[9],
                d->csw[10], d->csw[11], d->csw[12]);
        return 0;
    }
    return 1;
}

/** Docstring: REQUEST SENSE after a failure, so a unit attention clears
 * instead of failing every later command, and the key lands in the log.
 * Six-byte command, eighteen bytes of sense. Best-effort: its own failure
 * changes nothing. */
#define UBK_SENSE_LEN 18u
static void ubk_sense(void) {
    ubk_disk_t *d = &ubk_disk;
    unsigned char cdb[UBK_CDB6_LEN];
    if (!d->used || !d->sense) return;
    kmemset(cdb, 0, UBK_CDB6_LEN);
    cdb[0] = UBK_SCSI_REQUEST_SENSE;
    cdb[4] = UBK_SENSE_LEN;
    if (ubk_command_raw(cdb, UBK_CDB6_LEN, UBK_SCSI_REQUEST_SENSE, d->sense,
                        UBK_SENSE_LEN, 0))
        kprintf("ubk dbg: sense %02x %02x %02x\n", d->sense[0], d->sense[2],
                d->sense[12]);
}

/** Docstring: One command with a single recovery: on a transport failure
 * the pipe is reset and cleared and the command runs once more, because
 * real silicon stalls commands an emulator accepts. A second failure, or
 * a CSW that disagrees, is reported as-is. */
static int ubk_command(unsigned char *cdb, unsigned cdb_len,
                       unsigned char opcode, void *data, unsigned data_len,
                       int to_device) {
    if (ubk_command_raw(cdb, cdb_len, opcode, data, data_len, to_device))
        return 1;
    ubk_reset_recovery();
    ubk_sense();
    return ubk_command_raw(cdb, cdb_len, opcode, data, data_len, to_device);
}

/** Docstring: Wait for the medium with TEST UNIT READY. Real devices answer
 * CHECK CONDITION until the media is up; without this the first capacity
 * read runs against a device that is not there yet. Bounded, so a dead
 * device costs tries, never the boot. */
#define UBK_READY_TRIES 5u
static int ubk_unit_ready(void) {
    unsigned i;
    unsigned char cdb[UBK_CDB6_LEN];
    kmemset(cdb, 0, UBK_CDB6_LEN);
    cdb[0] = UBK_SCSI_TEST_UNIT_READY;
    for (i = 0; i < UBK_READY_TRIES; i++) {
        if (ubk_command_raw(cdb, UBK_CDB6_LEN, UBK_SCSI_TEST_UNIT_READY, 0,
                            0, 0))
            return 1;
        ubk_sense();
    }
    return 0;
}

/** Docstring: Read the sector count with READ CAPACITY(10). Returns 1 on a
 * successful command with a plausible count. Both fields arrive big-endian,
 * so a little-endian read reports a capacity the medium does not have. */
static int ubk_read_capacity(unsigned long *sectors) {
    unsigned char cdb[UBK_CDB_LEN];
    unsigned char *cap;
    unsigned last;
    unsigned block_size;
    int ok;
    cap = (unsigned char *)kmalloc(8);
    if (!cap) return 0;
    kmm_make_uncached((unsigned long)cap, 8);
    ubk_cdb10(cdb, UBK_SCSI_READ_CAPACITY, 0, 0);
    ok = ubk_command(cdb, UBK_CDB_LEN, UBK_SCSI_READ_CAPACITY, cap, 8, 0);
    if (ok) {
        last = ((unsigned)cap[0] << 24) | ((unsigned)cap[1] << 16) |
               ((unsigned)cap[2] << 8) | (unsigned)cap[3];
        block_size = ((unsigned)cap[4] << 24) | ((unsigned)cap[5] << 16) |
                     ((unsigned)cap[6] << 8) | (unsigned)cap[7];
        if (block_size != UBK_BLOCK_SIZE || last == 0xFFFFFFFFu) {
            kprintf("ubk dbg: capacity last=%08x bs=%u\n", last, block_size);
            ok = 0;
        } else *sectors = (unsigned long)last + 1u;
    }
    kfree(cap);
    return ok;
}

int ubk_present(void) {
    return ubk_disk.used;
}

unsigned long ubk_sectors(void) {
    return ubk_disk.used ? ubk_disk.sectors : 0u;
}

/** Docstring: Move whole sectors. Every refusal is checked before the command
 * is built, so a bad range never reaches the device, and a failed CSW never
 * leaves a buffer described as valid. */
static int ubk_xfer(unsigned long lba, unsigned count, void *buf, int read) {
    unsigned char cdb[UBK_CDB_LEN];
    unsigned long end;
    if (!ubk_disk.used) return 0;
    if (count == 0 || count > UBK_MAX_XFER_BLOCKS) return 0;
    end = lba + count;
    if (end < lba) return 0;
    if (end > ubk_disk.sectors) return 0;
    ubk_cdb10(cdb, (unsigned char)(read ? UBK_SCSI_READ10 : UBK_SCSI_WRITE10),
              lba, count);
    if (!ubk_command(cdb, UBK_CDB_LEN, cdb[0], buf, count * UBK_BLOCK_SIZE,
                     !read))
        return 0;
    if (read) ubk_ctr.read_blocks += count;
    else ubk_ctr.write_blocks += count;
    return 1;
}

int ubk_read_sectors(unsigned long lba, unsigned count, void *buf) {
    if (!buf) return 0;
    return ubk_xfer(lba, count, buf, 1);
}

int ubk_write_sectors(unsigned long lba, unsigned count, const void *buf) {
    if (!buf) return 0;
    return ubk_xfer(lba, count, (void *)(unsigned long)buf, 0);
}

/** Docstring: Take a bulk OUT and a bulk IN endpoint from a claimed interface
 * and program them. Returns 1 on success. */
static int ubk_claim_eps(int device, const xhc_iface_t *iface) {
    int i;
    int out_addr = 0;
    int in_addr = 0;
    int out_maxp = 0;
    int in_maxp = 0;
    for (i = 0; i < iface->num_eps; i++) {
        if (iface->ep_type[i] != XHC_EP_BULK) continue;
        if (iface->ep_addr[i] & XHC_EP_DIR_IN) {
            if (!in_addr) {
                in_addr = iface->ep_addr[i];
                in_maxp = iface->ep_maxp[i];
            }
        } else {
            if (!out_addr) {
                out_addr = iface->ep_addr[i];
                out_maxp = iface->ep_maxp[i];
            }
        }
    }
    if (!in_addr || !out_addr) return 0;
    if (out_maxp > 1024 || in_maxp > 1024) return 0;
    /* Endpoint indices 1 and 2 are the OUT and IN contexts, matching the
     * order every BOT interface uses, and are free unless HID claimed them. */
    if (!xhc_configure_endpoint(device, 1, out_addr, XHC_EP_BULK,
                                out_maxp, 1, UBK_BULK_INTERVAL, UBK_BULK_BURST))
        return 0;
    if (!xhc_configure_endpoint(device, 2, in_addr, XHC_EP_BULK,
                                in_maxp, 1, UBK_BULK_INTERVAL, UBK_BULK_BURST))
        return 0;
    ubk_disk.ep_out = 1;
    ubk_disk.ep_in = 2;
    ubk_disk.ep_out_addr = out_addr;
    ubk_disk.ep_in_addr = in_addr;
    ubk_disk.iface = iface->iface;
    return 1;
}

/** Docstring: Block-ops adapters so the disk registers with the existing block
 * layer instead of growing a parallel one. The device argument is unused: a
 * second USB disk is not supported and the bound is enforced in ubk_init, so
 * routing the registry through a device pointer would be a parameter that
 * cannot carry a distinction. Every call is a refusal unless the range is
 * inside the disk, which keeps a bad LBA from the page cache off the device. */
static int ubk_blk_read(device_t *dev, unsigned lba, unsigned count,
                        void *buf) {
    (void)dev;
    return ubk_read_sectors((unsigned long)lba, count, buf);
}

static int ubk_blk_write(device_t *dev, unsigned lba, unsigned count,
                         const void *buf) {
    (void)dev;
    return ubk_write_sectors((unsigned long)lba, count, buf);
}

static unsigned ubk_blk_sectors(device_t *dev) {
    (void)dev;
    return (unsigned)ubk_sectors();
}

static int ubk_blk_present(device_t *dev) {
    (void)dev;
    return ubk_present();
}

/** Docstring: The block device record handed to device_register. */
static block_ops_t ubk_block_ops = {
    .read_sectors = ubk_blk_read,
    .write_sectors = ubk_blk_write,
    .total_sectors = ubk_blk_sectors,
    .present = ubk_blk_present
};

static device_t ubk_device = {
    .name = "usb",
    .type = DEV_TYPE_BLOCK,
    .block = &ubk_block_ops
};

int ubk_init(void) {
    int n = xhc_device_count();
    int d;
    unsigned long sectors = 0;
    for (d = 0; d < n; d++) {
        xhc_iface_t iface;
        if (ubk_disk.used) break;
        if (!xhc_open_interface(d, XHC_CLASS_MASS_STORAGE, XHC_SUBCLASS_SCSI,
                                XHC_PROTOCOL_BULK_ONLY, &iface))
            continue;
        if (!ubk_disk.cbw) {
            ubk_disk.cbw = (unsigned char *)kmalloc(UBK_CBW_LEN);
            ubk_disk.csw = (unsigned char *)kmalloc(UBK_CSW_LEN);
            ubk_disk.sense = (unsigned char *)kmalloc(UBK_SENSE_LEN);
            if (!ubk_disk.cbw || !ubk_disk.csw || !ubk_disk.sense) {
                if (ubk_disk.cbw) kfree(ubk_disk.cbw);
                if (ubk_disk.csw) kfree(ubk_disk.csw);
                if (ubk_disk.sense) kfree(ubk_disk.sense);
                ubk_disk.cbw = 0;
                ubk_disk.csw = 0;
                ubk_disk.sense = 0;
                continue;
            }
            kmm_make_uncached((unsigned long)ubk_disk.cbw, UBK_CBW_LEN);
            kmm_make_uncached((unsigned long)ubk_disk.csw, UBK_CSW_LEN);
            kmm_make_uncached((unsigned long)ubk_disk.sense, UBK_SENSE_LEN);
        }
        if (!ubk_claim_eps(d, &iface)) {
            kprintf("ubk dbg: dev %d claim eps failed\n", d);
            continue;
        }
        ubk_disk.used = 1;
        ubk_disk.device = d;
        ubk_disk.tag = 0;
        if (!ubk_unit_ready()) {
            kprintf("ubk dbg: dev %d not ready\n", d);
            ubk_disk.used = 0;
            continue;
        }
        if (!ubk_read_capacity(&sectors)) {
            kprintf("ubk dbg: dev %d capacity failed\n", d);
            ubk_disk.used = 0;
            continue;
        }
        if (sectors == 0 || sectors > UBK_MAX_SECTORS) {
            ubk_disk.used = 0;
            continue;
        }
        ubk_disk.sectors = sectors;
        if (device_register(&ubk_device) != 0) {
            ubk_disk.used = 0;
            continue;
        }
        return 1;
    }
    return 0;
}