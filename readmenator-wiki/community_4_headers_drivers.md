# headers/drivers

*Community 4 | 4 files | cohesion 0.50*

## Definition

This community groups 4 file(s) rooted at `headers/drivers` with dominant language c (cohesion 0.50). Central symbols: `CHECK`, `DRIVERS_PCI_H`, `DRIVERS_VIRTIO_BLK_H`, `PCI_CFG_ADDR`, `PCI_CFG_DATA`, `PCI_MAX_BUS`, `PCI_MAX_DEV`, `PCI_MAX_FUNC`. Core file: `drivers/virtio_blk.c` (35 symbols). Documented purpose: Docstring: drivers/virtio_blk.c -- Polled legacy virtio-blk driver..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/virtio_blk.c` | c | infrastructure | 35 | yes |
| `headers/drivers/pci.h` | h | infrastructure | 9 | yes |
| `headers/drivers/virtio_blk.h` | h | infrastructure | 6 | yes |
| `tests/test_pci.c` | c | testing | 4 | yes |

## Key Symbols

- `VBLK_VENDOR` (macro, `drivers/virtio_blk.c:27`) `#define VBLK_VENDOR`
- `VBLK_DEV_LEGACY` (macro, `drivers/virtio_blk.c:28`) `#define VBLK_DEV_LEGACY`
- `VBLK_DEV_TRANS` (macro, `drivers/virtio_blk.c:29`) `#define VBLK_DEV_TRANS`
- `VBLK_F_ACK` (macro, `drivers/virtio_blk.c:31`) `#define VBLK_F_ACK`
- `VBLK_F_DRIVER` (macro, `drivers/virtio_blk.c:32`) `#define VBLK_F_DRIVER`
- `VBLK_F_OK` (macro, `drivers/virtio_blk.c:33`) `#define VBLK_F_OK`
- `VBLK_F_DRIVER_OK` (macro, `drivers/virtio_blk.c:34`) `#define VBLK_F_DRIVER_OK`
- `VBLK_QNUM` (macro, `drivers/virtio_blk.c:36`) `#define VBLK_QNUM`
- `VBLK_DESC_SZ` (macro, `drivers/virtio_blk.c:37`) `#define VBLK_DESC_SZ`
- `VBLK_AVAIL_OFF` (macro, `drivers/virtio_blk.c:42`) `#define VBLK_AVAIL_OFF`
- `VBLK_USED_OFF` (macro, `drivers/virtio_blk.c:43`) `#define VBLK_USED_OFF`
- `VBLK_QAREA` (macro, `drivers/virtio_blk.c:44`) `#define VBLK_QAREA`
- `VBLK_DESC_NEXT` (macro, `drivers/virtio_blk.c:46`) `#define VBLK_DESC_NEXT`
- `VBLK_DESC_WRITE` (macro, `drivers/virtio_blk.c:47`) `#define VBLK_DESC_WRITE`
- `VBLK_REQ_IN` (macro, `drivers/virtio_blk.c:49`) `#define VBLK_REQ_IN`
- `VBLK_REQ_OUT` (macro, `drivers/virtio_blk.c:50`) `#define VBLK_REQ_OUT`
- `VBLK_TMO_MS` (macro, `drivers/virtio_blk.c:52`) `#define VBLK_TMO_MS`
- `VBLK_SECTOR` (macro, `drivers/virtio_blk.c:53`) `#define VBLK_SECTOR`
- `vblk_req_t` (struct, `drivers/virtio_blk.c:55`)
- `vblk_outl` (function, `drivers/virtio_blk.c:70`) `static void vblk_outl(unsigned short port, unsigned val)`
- `vblk_inl` (function, `drivers/virtio_blk.c:74`) `static unsigned vblk_inl(unsigned short port)`
- `vblk_outb` (function, `drivers/virtio_blk.c:80`) `static void vblk_outb(unsigned short port, unsigned char val)`
- `vblk_inb` (function, `drivers/virtio_blk.c:84`) `static unsigned char vblk_inb(unsigned short port)`
- `vblk_inw` (function, `drivers/virtio_blk.c:88`) `static unsigned short vblk_inw(unsigned short port)`
- `vblk_outw` (function, `drivers/virtio_blk.c:92`) `static void vblk_outw(unsigned short port, unsigned short val)`
- `vblk_init` (function, `drivers/virtio_blk.c:99`) `int vblk_init(void)` - Docstring: Probe PCI for a virtio-blk device and bring queue 0 up. Idempotent: a second call reuses
- `vblk_present` (function, `drivers/virtio_blk.c:157`) `int vblk_present(void)` - { unsigned long cap_lo = vblk_inl(vblk_iobase + 0x14); unsigned long cap_hi = vblk_inl(vblk_iobase +
- `vblk_sectors` (function, `drivers/virtio_blk.c:162`) `unsigned long vblk_sectors(void)` - } vblk_outb(vblk_iobase + 0x12, VBLK_F_ACK \| VBLK_F_DRIVER \| VBLK_F_OK \| VBLK_F_DRIVER_OK); vblk_las
- `vblk_desc` (function, `drivers/virtio_blk.c:166`) `static void vblk_desc(unsigned idx, unsigned long addr, unsigned len,         un`
- `vblk_avail_idx` (function, `drivers/virtio_blk.c:182`) `static unsigned short vblk_avail_idx(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 3
- Cross-boundary resolved imports (EXTRACTED): 3

## Connections

- [EXTRACTED] depends_on community 4 <-> 2 (strength 0.9): Extracted import edge crosses communities: drivers/virtio_blk.c imports headers/kernel.h.
- [INFERRED] shares_context community 0 <-> 4 (strength 0.5): Inferred shared context (language c) with no import path between community 0 (headers) and community 4 (headers/drivers).

## Risks

- [dataflow DEAD_STORE] `drivers/virtio_blk.c:168` `vblk_desc` `d`: `d` assigned at line 168 but never read afterwards.
- [dataflow DEAD_STORE] `drivers/virtio_blk.c:188` `vblk_avail_push` `a`: `a` assigned at line 188 but never read afterwards.

## Open Questions

- What would break if the most connected file in headers/drivers changed?
- Should headers/drivers be split, given cohesion 0.50?

## Sources

- `drivers/virtio_blk.c`
- `headers/drivers/pci.h`
- `headers/drivers/virtio_blk.h`
- `tests/test_pci.c`
