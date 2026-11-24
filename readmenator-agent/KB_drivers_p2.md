# Subsystem: drivers (page 2 of 3)
Previous: [KB_drivers.md](KB_drivers.md)

## drivers/sb16.c
- Doc: Sound Blaster 16 DMA audio driver.
- Layer: infrastructure
- Language: c
- Symbols:
  - `sb16_kring_reset` (function, line 118) `static void sb16_kring_reset(void)`
  - `sb16_slot` (function, line 130) `static unsigned char *sb16_slot(unsigned i)`
  - `sb16_stream_open` (function, line 138) `int sb16_stream_open(void)`
  - `sb16_stream_close` (function, line 154) `void sb16_stream_close(int id)`
  - `sb16_stream_submit` (function, line 162) `int sb16_stream_submit(int id, const unsigned char *pcm, unsigned len)`
  - `sb16_stream_volume` (function, line 177) `void sb16_stream_volume(int id, unsigned char vol)`
  - `sb16_stream_count` (function, line 183) `int sb16_stream_count(void)`
  - `sb16_mix_all` (function, line 194) `static void sb16_mix_all(void)`
  - `sb16_pump` (function, line 236) `void sb16_pump(void)`
  - `sb16_wait_write` (function, line 278) `static int sb16_wait_write(void)`
  - `sb16_cmd` (function, line 282) `static void sb16_cmd(unsigned char c)`
  - `sb16_read_data` (function, line 287) `static int sb16_read_data(unsigned char *out)`
  - `sb16_reset_dsp` (function, line 297) `static int sb16_reset_dsp(void)`
  - `sb16_dma_play` (function, line 323) `static void sb16_dma_play(unsigned addr, unsigned len)`
  - `sb16_refill` (function, line 339) `static void sb16_refill(int slot_index)`
  - `sb16_arm` (function, line 355) `static void sb16_arm(int from_irq)`
  - `sb16_present` (function, line 380) `int sb16_present(void)`
  - `sb16_tone` (function, line 382) `void sb16_tone(unsigned freq)`
  - `sb16_pcm_open` (function, line 398) `void sb16_pcm_open(void)`
  - `sb16_pcm_close` (function, line 422) `void sb16_pcm_close(void)`
  - `sb16_pcm_submit` (function, line 431) `int sb16_pcm_submit(const unsigned char *pcm, unsigned len)`
  - `sb16_irq` (function, line 449) `void sb16_irq(void)`
  - `sb16_poll` (function, line 457) `void sb16_poll(void)`
  - `sb16_ring_free` (function, line 466) `unsigned sb16_ring_free(void)`
  - `sb16_mode_active` (function, line 467) `int sb16_mode_active(void)`
  - `sb16_legacy_busy` (function, line 472) `int sb16_legacy_busy(void)`
  - `sb16_counters` (function, line 479) `void sb16_counters(sb16_counters_t *out)`
  - `sb16_ops_present` (function, line 484) `static int sb16_ops_present(device_t *dev)`
  - `sb16_ops_pcm_open` (function, line 491) `static void sb16_ops_pcm_open(device_t *dev)`
  - `sb16_ops_pcm_close` (function, line 498) `static void sb16_ops_pcm_close(device_t *dev)`
  - `sb16_ops_pcm_submit` (function, line 505) `static int sb16_ops_pcm_submit(device_t *dev, const unsigned char *pcm, unsigned len)`
  - `sb16_init` (function, line 530) `int sb16_init(void)`
  - `IRQ` (function, line 22) `* QEMU audio backends never raise the completion IRQ (they only consume once * their engine buffer drains, which a...`
  - `pending` (function, line 535) `* reading without it eats whatever byte happens to be pending (or * times out), so the probe used to fail or misread...`
  - `SB16_BASE_PORT` (macro, line 48) `#define SB16_BASE_PORT`
  - `SB16_DSP_RESET` (macro, line 49) `#define SB16_DSP_RESET`
  - `SB16_DSP_READ_DATA` (macro, line 50) `#define SB16_DSP_READ_DATA`
  - `SB16_DSP_WRITE_DATA` (macro, line 51) `#define SB16_DSP_WRITE_DATA`
  - `SB16_DSP_STATUS` (macro, line 52) `#define SB16_DSP_STATUS`
  - `SB16_IRQ_ACK` (macro, line 53) `#define SB16_IRQ_ACK`
  - `SB16_CMD_READ_VER` (macro, line 55) `#define SB16_CMD_READ_VER`
  - `SB16_CMD_SET_FREQ` (macro, line 56) `#define SB16_CMD_SET_FREQ`
  - `SB16_CMD_PLAY8` (macro, line 57) `#define SB16_CMD_PLAY8`
  - `SB16_CMD_SPK_ON` (macro, line 58) `#define SB16_CMD_SPK_ON`
  - `SB16_CMD_SPK_OFF` (macro, line 59) `#define SB16_CMD_SPK_OFF`
  - `SB16_DSP_RDSTATUS` (macro, line 61) `#define SB16_DSP_RDSTATUS`
  - `DMA_MODE_PORT` (macro, line 67) `#define DMA_MODE_PORT`
  - `DMA_CH1_SINGLE_READ` (macro, line 68) `#define DMA_CH1_SINGLE_READ`
  - `SB16_FREQ_LO` (macro, line 70) `#define SB16_FREQ_LO`
  - `SB16_FREQ_HI` (macro, line 71) `#define SB16_FREQ_HI`
  - `SB16_DSP_READY_MASK` (macro, line 73) `#define SB16_DSP_READY_MASK`
  - `DMA_CH1_ADDR` (macro, line 75) `#define DMA_CH1_ADDR`
  - `DMA_CH1_CNT` (macro, line 76) `#define DMA_CH1_CNT`
  - `DMA_CH1_PAGE` (macro, line 77) `#define DMA_CH1_PAGE`
  - `DMA_MASK` (macro, line 78) `#define DMA_MASK`
  - `DMA_FF_CLR` (macro, line 79) `#define DMA_FF_CLR`
  - `DMA_CH1_UNMASK` (macro, line 80) `#define DMA_CH1_UNMASK`
  - `DMA_CH1_MASK` (macro, line 81) `#define DMA_CH1_MASK`
  - `SB16_DMA_BUF0` (macro, line 83) `#define SB16_DMA_BUF0`
  - `SB16_SILENCE_SLOT` (macro, line 84) `#define SB16_SILENCE_SLOT`
  - `SB16_BUF` (macro, line 85) `#define SB16_BUF`
  - `SB16_MODE_TONE` (macro, line 88) `#define SB16_MODE_TONE`
  - `SB16_MODE_PCM` (macro, line 89) `#define SB16_MODE_PCM`
  - `SB16_SQ_CYCLE` (macro, line 91) `#define SB16_SQ_CYCLE`
- Depends on: `headers/driver.h`, `headers/pcm2.h`, `headers/sb16.h`, `headers/sync.h`

## drivers/usbblk.c
- Doc: USB mass storage, Bulk-Only Transport over SCSI.
- Layer: infrastructure
- Language: c
- Symbols:
  - `ubk_disk_t` (struct, line 44)
  - `ubk_counters` (function, line 72) `void ubk_counters(ubk_counters_t *out)`
  - `ubk_cdb10` (function, line 80) `static void ubk_cdb10(unsigned char *cdb, unsigned char opcode,
                      unsigned lo...`
  - `ubk_build_cbw` (function, line 92) `void ubk_build_cbw(unsigned char *out, unsigned tag, unsigned long lba,
                   unsign...`
  - `ubk_check_csw` (function, line 121) `int ubk_check_csw(const unsigned char *csw, unsigned tag, unsigned expect_len)`
  - `ubk_command_raw` (function, line 187) `static int ubk_command_raw(unsigned char *cdb, unsigned cdb_len,
                           unsig...`
  - `ubk_sense` (function, line 262) `static void ubk_sense(void)`
  - `ubk_command` (function, line 279) `static int ubk_command(unsigned char *cdb, unsigned cdb_len,
                       unsigned char...`
  - `ubk_unit_ready` (function, line 294) `static int ubk_unit_ready(void)`
  - `ubk_read_capacity` (function, line 311) `static int ubk_read_capacity(unsigned long *sectors)`
  - `ubk_present` (function, line 336) `int ubk_present(void)`
  - `ubk_sectors` (function, line 340) `unsigned long ubk_sectors(void)`
  - `ubk_xfer` (function, line 347) `static int ubk_xfer(unsigned long lba, unsigned count, void *buf, int read)`
  - `ubk_read_sectors` (function, line 365) `int ubk_read_sectors(unsigned long lba, unsigned count, void *buf)`
  - `ubk_write_sectors` (function, line 370) `int ubk_write_sectors(unsigned long lba, unsigned count, const void *buf)`
  - `ubk_claim_eps` (function, line 377) `static int ubk_claim_eps(int device, const xhc_iface_t *iface)`
  - `ubk_blk_read` (function, line 421) `static int ubk_blk_read(device_t *dev, unsigned lba, unsigned count,
                        void...`
  - `ubk_blk_write` (function, line 427) `static int ubk_blk_write(device_t *dev, unsigned lba, unsigned count,
                         co...`
  - `ubk_blk_sectors` (function, line 433) `static unsigned ubk_blk_sectors(device_t *dev)`
  - `ubk_blk_present` (function, line 438) `static int ubk_blk_present(device_t *dev)`
  - `ubk_init` (function, line 457) `int ubk_init(void)`
  - `UBK_CBW_LEN` (macro, line 22) `#define UBK_CBW_LEN`
  - `UBK_CBW_SIG` (macro, line 23) `#define UBK_CBW_SIG`
  - `UBK_CBW_FLAG_IN` (macro, line 24) `#define UBK_CBW_FLAG_IN`
  - `UBK_CSW_LEN` (macro, line 27) `#define UBK_CSW_LEN`
  - `UBK_CSW_SIG` (macro, line 28) `#define UBK_CSW_SIG`
  - `UBK_CSW_STATUS_PASSED` (macro, line 29) `#define UBK_CSW_STATUS_PASSED`
  - `UBK_CSW_STATUS_FAILED` (macro, line 30) `#define UBK_CSW_STATUS_FAILED`
  - `UBK_SCSI_TEST_UNIT_READY` (macro, line 33) `#define UBK_SCSI_TEST_UNIT_READY`
  - `UBK_SCSI_REQUEST_SENSE` (macro, line 34) `#define UBK_SCSI_REQUEST_SENSE`
  - `UBK_SCSI_INQUIRY` (macro, line 35) `#define UBK_SCSI_INQUIRY`
  - `UBK_SCSI_READ_CAPACITY` (macro, line 36) `#define UBK_SCSI_READ_CAPACITY`
  - `UBK_SCSI_READ10` (macro, line 37) `#define UBK_SCSI_READ10`
  - `UBK_SCSI_WRITE10` (macro, line 38) `#define UBK_SCSI_WRITE10`
  - `UBK_BULK_INTERVAL` (macro, line 63) `#define UBK_BULK_INTERVAL`
  - `UBK_BULK_BURST` (macro, line 64) `#define UBK_BULK_BURST`
  - `UBK_MAX_XFER_BLOCKS` (macro, line 70) `#define UBK_MAX_XFER_BLOCKS`
  - `UBK_CDB_LEN` (macro, line 79) `#define UBK_CDB_LEN`
  - `UBK_MS_RESET` (macro, line 148) `#define UBK_MS_RESET`
  - `UBK_CLEAR_FEATURE` (macro, line 149) `#define UBK_CLEAR_FEATURE`
  - `UBK_ENDP_HALT` (macro, line 150) `#define UBK_ENDP_HALT`
  - `UBK_CDB6_LEN` (macro, line 181) `#define UBK_CDB6_LEN`
  - `UBK_SENSE_LEN` (macro, line 261) `#define UBK_SENSE_LEN`
  - `UBK_READY_TRIES` (macro, line 293) `#define UBK_READY_TRIES`
- Depends on: `headers/driver.h`, `headers/drivers/usbblk.h`, `headers/drivers/xhci.h`
- Imported by: `tests/test_usbblk.c`

## drivers/usbhid.c
- Doc: USB HID boot-protocol keyboard and mouse.
- Layer: infrastructure
- Language: c
- Symbols:
  - `usbhid_dev_t` (struct, line 40)
  - `usbhid_set1_from_usage` (function, line 117) `int usbhid_set1_from_usage(unsigned usage, unsigned char *sc, int *e0)`
  - `usbhid_usage_make` (function, line 128) `static int usbhid_usage_make(unsigned usage, unsigned char *sc, int *e0)`
  - `usbhid_report_has` (function, line 138) `static int usbhid_report_has(const unsigned char report[HID_KBD_REPORT_LEN],
                    ...`
  - `usbhid_put` (function, line 153) `static int usbhid_put(unsigned char *out, int max, int n, unsigned char sc)`
  - `usbhid_emit_mod` (function, line 165) `static int usbhid_emit_mod(unsigned char *out, int max, int n, unsigned bit,
                    ...`
  - `usbhid_emit_usage` (function, line 183) `static int usbhid_emit_usage(unsigned char *out, int max, int n,
                             uns...`
  - `usbhid_kbd_scancodes` (function, line 206) `int usbhid_kbd_scancodes(const unsigned char prev[HID_KBD_REPORT_LEN],
                         c...`
  - `usbhid_mouse_decode` (function, line 241) `void usbhid_mouse_decode(const unsigned char prev[HID_MOUSE_REPORT_LEN],
                        ...`
  - `usbhid_keyboard_present` (function, line 256) `int usbhid_keyboard_present(void)`
  - `usbhid_mouse_present` (function, line 263) `int usbhid_mouse_present(void)`
  - `usbhid_counters` (function, line 270) `void usbhid_counters(usbhid_counters_t *out)`
  - `usbhid_press_kbd_report` (function, line 274) `int usbhid_press_kbd_report(const unsigned char report[HID_KBD_REPORT_LEN])`
  - `usbhid_set_boot_protocol` (function, line 295) `static int usbhid_set_boot_protocol(int device, int iface)`
  - `usbhid_ep_taken` (function, line 312) `static int usbhid_ep_taken(int ep_index)`
  - `usbhid_take_ep` (function, line 325) `static int usbhid_take_ep(int device, const xhc_iface_t *iface,
                          int *maxp)`
  - `usbhid_claim` (function, line 353) `static int usbhid_claim(int device, const xhc_iface_t *iface, int is_mouse)`
  - `usbhid_is_mouse_maxp` (function, line 380) `static int usbhid_is_mouse_maxp(int maxp)`
  - `usbhid_init` (function, line 384) `int usbhid_init(void)`
  - `usbhid_poll_one` (function, line 422) `static int usbhid_poll_one(usbhid_dev_t *d)`
  - `usbhid_poll_keyboard` (function, line 485) `int usbhid_poll_keyboard(void)`
  - `usbhid_poll_mouse` (function, line 493) `int usbhid_poll_mouse(void)`
  - `usbhid_poll` (function, line 501) `int usbhid_poll(void)`
  - `USBHID_MAX_DEVS` (macro, line 35) `#define USBHID_MAX_DEVS`
  - `USBHID_INTERVAL` (macro, line 55) `#define USBHID_INTERVAL`
  - `USBHID_MAX_SCANCODES` (macro, line 204) `#define USBHID_MAX_SCANCODES`
- Depends on: `headers/arch/x86/hal_io.h`, `headers/drivers/kbd.h`, `headers/drivers/modifiers.h`, `headers/drivers/usbhid.h`, `headers/drivers/xhci.h`, `headers/vga_fb.h`
- Imported by: `tests/test_usbhid.c`

## drivers/virtio_blk.c
- Doc: Docstring: drivers/virtio_blk.c -- Polled legacy virtio-blk driver.
- Layer: infrastructure
- Language: c
- Symbols:
  - `vblk_req_t` (struct, line 56)
  - `vblk_outl` (function, line 71) `static void vblk_outl(unsigned short port, unsigned val)`
  - `vblk_inl` (function, line 75) `static unsigned vblk_inl(unsigned short port)`
  - `vblk_outb` (function, line 81) `static void vblk_outb(unsigned short port, unsigned char val)`
  - `vblk_inb` (function, line 85) `static unsigned char vblk_inb(unsigned short port)`
  - `vblk_inw` (function, line 89) `static unsigned short vblk_inw(unsigned short port)`
  - `vblk_outw` (function, line 93) `static void vblk_outw(unsigned short port, unsigned short val)`
  - `vblk_init` (function, line 100) `int vblk_init(void)`
  - `vblk_present` (function, line 158) `int vblk_present(void)`
  - `vblk_sectors` (function, line 163) `unsigned long vblk_sectors(void)`
  - `vblk_desc` (function, line 167) `static void vblk_desc(unsigned idx, unsigned long addr, unsigned len,
        unsigned short flag...`
  - `vblk_avail_idx` (function, line 183) `static unsigned short vblk_avail_idx(void)`
  - `vblk_avail_push` (function, line 188) `static void vblk_avail_push(unsigned short head)`
  - `vblk_used_idx` (function, line 199) `static unsigned short vblk_used_idx(void)`
  - `vblk_request` (function, line 212) `static int vblk_request(unsigned dir, unsigned long sector,
        unsigned char *buf, unsigned ...`
  - `vblk_write_sectors` (function, line 266) `int vblk_write_sectors(unsigned lba, unsigned count, const void *buf)`
  - `vblk_ops_read` (function, line 282) `static int vblk_ops_read(device_t *dev, unsigned lba, unsigned count,
        void *buf)`
  - `vblk_ops_write` (function, line 289) `static int vblk_ops_write(device_t *dev, unsigned lba, unsigned count,
        const void *buf)`
  - `vblk_ops_total` (function, line 296) `static unsigned vblk_ops_total(device_t *dev)`
  - `vblk_ops_present` (function, line 302) `static int vblk_ops_present(device_t *dev)`
  - `vblk_register_device` (function, line 327) `void vblk_register_device(void)`
  - `VBLK_VENDOR` (macro, line 28) `#define VBLK_VENDOR`
  - `VBLK_DEV_LEGACY` (macro, line 29) `#define VBLK_DEV_LEGACY`
  - `VBLK_DEV_TRANS` (macro, line 30) `#define VBLK_DEV_TRANS`
  - `VBLK_F_ACK` (macro, line 32) `#define VBLK_F_ACK`
  - `VBLK_F_DRIVER` (macro, line 33) `#define VBLK_F_DRIVER`
  - `VBLK_F_OK` (macro, line 34) `#define VBLK_F_OK`
  - `VBLK_F_DRIVER_OK` (macro, line 35) `#define VBLK_F_DRIVER_OK`
  - `VBLK_QNUM` (macro, line 37) `#define VBLK_QNUM`
  - `VBLK_DESC_SZ` (macro, line 38) `#define VBLK_DESC_SZ`
  - `VBLK_AVAIL_OFF` (macro, line 43) `#define VBLK_AVAIL_OFF`
  - `VBLK_USED_OFF` (macro, line 44) `#define VBLK_USED_OFF`
  - `VBLK_QAREA` (macro, line 45) `#define VBLK_QAREA`
  - `VBLK_DESC_NEXT` (macro, line 47) `#define VBLK_DESC_NEXT`
  - `VBLK_DESC_WRITE` (macro, line 48) `#define VBLK_DESC_WRITE`
  - `VBLK_REQ_IN` (macro, line 50) `#define VBLK_REQ_IN`
  - `VBLK_REQ_OUT` (macro, line 51) `#define VBLK_REQ_OUT`
  - `VBLK_TMO_MS` (macro, line 53) `#define VBLK_TMO_MS`
  - `VBLK_SECTOR` (macro, line 54) `#define VBLK_SECTOR`
- Depends on: `headers/driver.h`, `headers/drivers/pci.h`, `headers/drivers/virtio_blk.h`

## drivers/virtio_net.c
- Doc: Docstring: drivers/virtio_net.c -- Polled legacy virtio-net driver.
- Layer: infrastructure
- Language: c
- Symbols:
  - `vnet_outb` (function, line 81) `static void vnet_outb(unsigned short port, unsigned char v)`
  - `vnet_outw` (function, line 85) `static void vnet_outw(unsigned short port, unsigned short v)`
  - `vnet_outl` (function, line 89) `static void vnet_outl(unsigned short port, unsigned v)`
  - `vnet_inb` (function, line 93) `static unsigned char vnet_inb(unsigned short port)`
  - `vnet_inw` (function, line 99) `static unsigned short vnet_inw(unsigned short port)`
  - `vnet_inl` (function, line 105) `static unsigned vnet_inl(unsigned short port)`
  - `vnet_queue_up` (function, line 114) `static unsigned vnet_queue_up(unsigned qsel)`
  - `vnet_desc` (function, line 144) `static void vnet_desc(unsigned char *page, unsigned idx, unsigned long addr,
        unsigned len...`
  - `vnet_avail_push` (function, line 161) `static void vnet_avail_push(unsigned char *page, unsigned qnum,
        unsigned short head)`
  - `vnet_used_idx` (function, line 174) `static unsigned short vnet_used_idx(unsigned char *used)`
  - `unusable` (function, line 181) `* unusable (fail-closed, rtl8139 stays). */
int vnet_init(void)`
  - `vnet_present` (function, line 223) `int vnet_present(void)`
  - `vnet_get_mac` (function, line 228) `void vnet_get_mac(unsigned char out[6])`
  - `vnet_iobase` (function, line 234) `unsigned short vnet_iobase(void)`
  - `vnet_counters` (function, line 239) `void vnet_counters(unsigned int *tx_frames, unsigned int *rx_frames)`
  - `vnet_link_up` (function, line 277) `int vnet_link_up(void)`
  - `vnet_poll` (function, line 287) `void vnet_poll(void)`
  - `VNET_VENDOR` (macro, line 29) `#define VNET_VENDOR`
  - `VNET_DEV_LEGACY` (macro, line 30) `#define VNET_DEV_LEGACY`
  - `VNET_DEV_TRANS` (macro, line 31) `#define VNET_DEV_TRANS`
  - `VNET_F_ACK` (macro, line 33) `#define VNET_F_ACK`
  - `VNET_F_DRIVER` (macro, line 34) `#define VNET_F_DRIVER`
  - `VNET_F_OK` (macro, line 35) `#define VNET_F_OK`
  - `VNET_F_DRIVER_OK` (macro, line 36) `#define VNET_F_DRIVER_OK`
  - `VNET_QNUM` (macro, line 38) `#define VNET_QNUM`
  - `VNET_DESC_SZ` (macro, line 39) `#define VNET_DESC_SZ`
  - `VNET_AVAIL_OFF` (macro, line 40) `#define VNET_AVAIL_OFF`
  - `VNET_USED_OFF` (macro, line 41) `#define VNET_USED_OFF`
  - `VNET_QAREA` (macro, line 42) `#define VNET_QAREA`
  - `VNET_DESC_NEXT` (macro, line 44) `#define VNET_DESC_NEXT`
  - `VNET_DESC_WRITE` (macro, line 45) `#define VNET_DESC_WRITE`
  - `VNET_Q_RX` (macro, line 47) `#define VNET_Q_RX`
  - `VNET_Q_TX` (macro, line 48) `#define VNET_Q_TX`
  - `VNET_HDR_LEN` (macro, line 50) `#define VNET_HDR_LEN`
  - `VNET_RX_BUFS` (macro, line 51) `#define VNET_RX_BUFS`
  - `VNET_RX_SIZE` (macro, line 52) `#define VNET_RX_SIZE`
  - `VNET_TX_SIZE` (macro, line 53) `#define VNET_TX_SIZE`
  - `VNET_MIN_FRAME` (macro, line 54) `#define VNET_MIN_FRAME`
  - `VNET_MAX_FRAME` (macro, line 55) `#define VNET_MAX_FRAME`
  - `VNET_TMO_MS` (macro, line 56) `#define VNET_TMO_MS`
  - `VNET_POLL_MAX` (macro, line 57) `#define VNET_POLL_MAX`
  - `VNET_CFG_MAC` (macro, line 59) `#define VNET_CFG_MAC`
  - `VNET_CFG_STATUS` (macro, line 60) `#define VNET_CFG_STATUS`
  - `VNET_ST_LINK_UP` (macro, line 61) `#define VNET_ST_LINK_UP`
- Depends on: `headers/drivers/pci.h`, `headers/drivers/virtio_net.h`, `headers/net.h`


Next: [KB_drivers_p3.md](KB_drivers_p3.md)
