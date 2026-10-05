# drivers

*Community 3 | 6 files | cohesion 0.37*

## Definition

This community groups 6 file(s) rooted at `drivers` with dominant language c (cohesion 0.37). Central symbols: `CHECK`, `DEV_MAX`, `DEV_NAME_LEN`, `DEV_TYPE_AUDIO`, `DEV_TYPE_BLOCK`, `DEV_TYPE_CHAR`, `DEV_TYPE_NET`, `DRIVERS_USBBLK_H`. Core file: `drivers/usbblk.c` (44 symbols). Documented purpose: Device registry for the Strategy-pattern driver layer..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/driver.c` | c | infrastructure | 8 | yes |
| `drivers/usbblk.c` | c | infrastructure | 44 | yes |
| `headers/driver.h` | h | infrastructure | 16 | yes |
| `headers/drivers/usbblk.h` | h | infrastructure | 13 | yes |
| `tests/test_driver.c` | c | testing | 5 | yes |
| `tests/test_usbblk.c` | c | testing | 4 | yes |

## Key Symbols

- `dev_len` (function, `drivers/driver.c:14`) `static unsigned dev_len(const char *s)`
- `dev_copy` (function, `drivers/driver.c:20`) `static void dev_copy(char *dst, const char *src, unsigned cap)`
- `dev_eq` (function, `drivers/driver.c:27`) `static int dev_eq(const char *a, const char *b)`
- `device_reset` (function, `drivers/driver.c:32`) `void device_reset(void)`
- `device_register` (function, `drivers/driver.c:44`) `int device_register(device_t *dev)`
- `device_find` (function, `drivers/driver.c:66`) `device_t *device_find(const char *name)`
- `device_find_by_type` (function, `drivers/driver.c:76`) `device_t *device_find_by_type(int type)`
- `device_count` (function, `drivers/driver.c:85`) `int device_count(void)`
- `UBK_CBW_LEN` (macro, `drivers/usbblk.c:22`) `#define UBK_CBW_LEN`
- `UBK_CBW_SIG` (macro, `drivers/usbblk.c:23`) `#define UBK_CBW_SIG`
- `UBK_CBW_FLAG_IN` (macro, `drivers/usbblk.c:24`) `#define UBK_CBW_FLAG_IN`
- `UBK_CSW_LEN` (macro, `drivers/usbblk.c:27`) `#define UBK_CSW_LEN`
- `UBK_CSW_SIG` (macro, `drivers/usbblk.c:28`) `#define UBK_CSW_SIG`
- `UBK_CSW_STATUS_PASSED` (macro, `drivers/usbblk.c:29`) `#define UBK_CSW_STATUS_PASSED`
- `UBK_CSW_STATUS_FAILED` (macro, `drivers/usbblk.c:30`) `#define UBK_CSW_STATUS_FAILED`
- `UBK_SCSI_TEST_UNIT_READY` (macro, `drivers/usbblk.c:33`) `#define UBK_SCSI_TEST_UNIT_READY`
- `UBK_SCSI_REQUEST_SENSE` (macro, `drivers/usbblk.c:34`) `#define UBK_SCSI_REQUEST_SENSE`
- `UBK_SCSI_INQUIRY` (macro, `drivers/usbblk.c:35`) `#define UBK_SCSI_INQUIRY`
- `UBK_SCSI_READ_CAPACITY` (macro, `drivers/usbblk.c:36`) `#define UBK_SCSI_READ_CAPACITY`
- `UBK_SCSI_READ10` (macro, `drivers/usbblk.c:37`) `#define UBK_SCSI_READ10`
- `UBK_SCSI_WRITE10` (macro, `drivers/usbblk.c:38`) `#define UBK_SCSI_WRITE10`
- `ubk_disk_t` (struct, `drivers/usbblk.c:44`) - Docstring: One registered disk: its device record, the OUT and IN endpoint indices, the sector count
- `UBK_BULK_INTERVAL` (macro, `drivers/usbblk.c:63`) `#define UBK_BULK_INTERVAL`
- `UBK_BULK_BURST` (macro, `drivers/usbblk.c:64`) `#define UBK_BULK_BURST`
- `UBK_MAX_XFER_BLOCKS` (macro, `drivers/usbblk.c:70`) `#define UBK_MAX_XFER_BLOCKS`
- `ubk_counters` (function, `drivers/usbblk.c:72`) `void ubk_counters(ubk_counters_t *out)`
- `UBK_CDB_LEN` (macro, `drivers/usbblk.c:79`) `#define UBK_CDB_LEN`
- `ubk_cdb10` (function, `drivers/usbblk.c:80`) `static void ubk_cdb10(unsigned char *cdb, unsigned char opcode,` - Docstring: Ten-byte SCSI CDB at the CBW command block: opcode, LBA big-endian, transfer length big-e
- `ubk_build_cbw` (function, `drivers/usbblk.c:92`) `void ubk_build_cbw(unsigned char *out, unsigned tag, unsigned long lba,`
- `ubk_check_csw` (function, `drivers/usbblk.c:121`) `int ubk_check_csw(const unsigned char *csw, unsigned tag, unsigned expect_len)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 7
- Cross-boundary resolved imports (EXTRACTED): 12

## Connections

- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: drivers/block.c imports headers/drivers/usbblk.h.
- [EXTRACTED] depends_on community 5 <-> 3 (strength 0.9): Extracted import edge crosses communities: drivers/pcspk.c imports headers/driver.h.
- [EXTRACTED] depends_on community 3 <-> 4 (strength 0.9): Extracted import edge crosses communities: drivers/usbblk.c imports headers/drivers/xhci.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- What would break if the most connected file in drivers changed?
- Should drivers be split, given cohesion 0.37?

## Sources

- `drivers/driver.c`
- `drivers/usbblk.c`
- `headers/driver.h`
- `headers/drivers/usbblk.h`
- `tests/test_driver.c`
- `tests/test_usbblk.c`
