# drivers

*Community 2 | 12 files | cohesion 0.41*

## Definition

This community groups 12 file(s) rooted at `drivers` with dominant language c (cohesion 0.41). Central symbols: `BC_LINE`, `BC_MASK`, `BC_WAYS`, `CHECK`, `DRIVERS_NVME_H`, `DRIVERS_PCI_H`, `DRIVERS_VIRTIO_BLK_H`, `FAKE_BUSES`. Core file: `headers/drivers/pci.h` (54 symbols). Documented purpose: Block device layer for MiniFS..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/block.c` | c | infrastructure | 19 | yes |
| `drivers/ide.c` | c | infrastructure | 19 | yes |
| `drivers/nvme.c` | c | infrastructure | 50 | no |
| `drivers/virtio_blk.c` | c | infrastructure | 39 | yes |
| `headers/drivers/nvme.h` | h | infrastructure | 7 | no |
| `headers/drivers/pci.h` | h | infrastructure | 54 | yes |
| `headers/drivers/virtio_blk.h` | h | infrastructure | 7 | yes |
| `headers/ide.h` | h | utility | 35 | yes |
| `headers/lz4_kernel.h` | h | utility | 4 | no |
| `kernel/lz4_kernel.c` | c | utility | 10 | no |
| `kernel/mm/swap.c` | c | utility | 11 | yes |
| `tests/test_pci.c` | c | testing | 7 | yes |

## Key Symbols

- `BC_WAYS` (macro, `drivers/block.c:53`) `#define BC_WAYS`
- `BC_MASK` (macro, `drivers/block.c:54`) `#define BC_MASK`
- `BC_LINE` (macro, `drivers/block.c:62`) `#define BC_LINE(idx)`
- `bc_index` (function, `drivers/block.c:64`) `static unsigned int bc_index(unsigned int block_num)`
- `bc_invalidate_locked` (function, `drivers/block.c:68`) `static void bc_invalidate_locked(unsigned int block_num)`
- `bc_invalidate` (function, `drivers/block.c:73`) `static void bc_invalidate(unsigned int block_num)`
- `block_init` (function, `drivers/block.c:80`) `void block_init(void)`
- `block_set_base` (function, `drivers/block.c:113`) `void block_set_base(unsigned int lba_base)`
- `table` (function, `drivers/block.c:122`) `* ops table (dev->ops->read/write), never straight at the hardware. The * virtio`
- `block_dev_read` (function, `drivers/block.c:128`) `static int block_dev_read(unsigned lba, unsigned count, void *buf)` - Strategy consumer: sector I/O goes through the registered block device's ops table (dev->ops->read/w
- `block_dev_write` (function, `drivers/block.c:146`) `static int block_dev_write(unsigned lba, unsigned count, const void *buf)`
- `block_read` (function, `drivers/block.c:164`) `int block_read(unsigned int block_num, void *buf)`
- `block_write` (function, `drivers/block.c:205`) `int block_write(unsigned int block_num, const void *buf)`
- `block_read_multi` (function, `drivers/block.c:214`) `int block_read_multi(unsigned int block_num, unsigned int count, void *buf)`
- `block_write_multi` (function, `drivers/block.c:219`) `int block_write_multi(unsigned int block_num, unsigned int count, const void *bu`
- `block_flush` (function, `drivers/block.c:234`) `void block_flush(void)`
- `block_total` (function, `drivers/block.c:236`) `unsigned int block_total(void)`
- `block_read_sectors` (function, `drivers/block.c:244`) `int block_read_sectors(unsigned lba, unsigned count, void *buf)` - Docstring: Absolute sector read on the active backend, with no cache and no base offset: partition t
- `block_disk_sectors` (function, `drivers/block.c:255`) `unsigned long block_disk_sectors(void)` - Docstring: Size of the active backend in sectors, so scanners fence to * the USB stick when it is th
- `ide_delay` (function, `drivers/ide.c:13`) `static void ide_delay(void)`
- `ide_read_status` (function, `drivers/ide.c:23`) `static unsigned char ide_read_status(void)`
- `ide_wait_not_busy` (function, `drivers/ide.c:27`) `static int ide_wait_not_busy(unsigned int timeout)`
- `ide_wait_drq` (function, `drivers/ide.c:40`) `static int ide_wait_drq(unsigned int timeout)`
- `ide_select_drive` (function, `drivers/ide.c:53`) `static void ide_select_drive(unsigned char drive)`
- `ide_soft_reset` (function, `drivers/ide.c:59`) `static void ide_soft_reset(void)`
- `ide_identify` (function, `drivers/ide.c:66`) `static int ide_identify(void)`
- `ide_init` (function, `drivers/ide.c:91`) `void ide_init(void)`
- `ide_present` (function, `drivers/ide.c:110`) `int ide_present(void)`
- `ide_total_sectors` (function, `drivers/ide.c:111`) `unsigned int ide_total_sectors(void)`
- `ide_ops_read` (function, `drivers/ide.c:113`) `static int ide_ops_read(device_t *dev, unsigned lba, unsigned count, void *buf)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 12
- Cross-boundary resolved imports (EXTRACTED): 17

## Connections

- [EXTRACTED] depends_on community 2 <-> 3 (strength 0.9): Extracted import edge crosses communities: drivers/block.c imports headers/drivers/usbblk.h.
- [EXTRACTED] depends_on community 2 <-> 0 (strength 0.9): Extracted import edge crosses communities: drivers/block.c imports headers/block.h.
- [EXTRACTED] depends_on community 2 <-> 4 (strength 0.9): Extracted import edge crosses communities: drivers/nvme.c imports headers/arch/x86/hal_io.h.
- [EXTRACTED] depends_on community 5 <-> 2 (strength 0.9): Extracted import edge crosses communities: drivers/virtio_net.c imports headers/drivers/pci.h.

## Risks

- [dataflow DEAD_STORE] `drivers/virtio_blk.c:169` `vblk_desc` `d`: `d` assigned at line 169 but never read afterwards.
- [dataflow DEAD_STORE] `drivers/virtio_blk.c:189` `vblk_avail_push` `a`: `a` assigned at line 189 but never read afterwards.

## Open Questions

- Why do 4 file(s) lack file-level docs (e.g. `drivers/nvme.c`)? What purpose do they serve?
- What would break if the most connected file in drivers changed?
- Should drivers be split, given cohesion 0.41?

## Sources

- `drivers/block.c`
- `drivers/ide.c`
- `drivers/nvme.c`
- `drivers/virtio_blk.c`
- `headers/drivers/nvme.h`
- `headers/drivers/pci.h`
- `headers/drivers/virtio_blk.h`
- `headers/ide.h`
- `headers/lz4_kernel.h`
- `kernel/lz4_kernel.c`
- `kernel/mm/swap.c`
- `tests/test_pci.c`
