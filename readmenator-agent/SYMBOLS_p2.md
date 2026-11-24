# Symbols (page 2 of 28)
Previous: [SYMBOLS.md](SYMBOLS.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `RTC_REG_YEAR` | macro | `drivers/rtc.c:17` | `#define RTC_REG_YEAR` |
| `RTC_SEC_MAX` | macro | `drivers/rtc.c:29` | `#define RTC_SEC_MAX` |
| `RTC_SEC_MIN` | macro | `drivers/rtc.c:28` | `#define RTC_SEC_MIN` |
| `RTC_UPDATE_IN_PROGRESS` | macro | `drivers/rtc.c:21` | `#define RTC_UPDATE_IN_PROGRESS` |
| `RTC_UPDATE_WAIT` | macro | `drivers/rtc.c:33` | `#define RTC_UPDATE_WAIT` |
| `rtc_cmos_read` | function | `drivers/rtc.c:35` | `static inline unsigned char rtc_cmos_read(unsigned char reg)` |
| `rtc_from_bcd` | function | `drivers/rtc.c:40` | `static int rtc_from_bcd(unsigned char v)` |
| `rtc_month_len` | function | `drivers/rtc.c:68` | `static int rtc_month_len(long full_year, long mon)` |
| `rtc_read_date` | function | `drivers/rtc.c:78` | `int rtc_read_date(int *year, int *mon, int *day)` |
| `rtc_read_tod` | function | `drivers/rtc.c:44` | `int rtc_read_tod(int *hour, int *min, int *sec)` |
| `rtc_wall_seconds` | function | `drivers/rtc.c:102` | `int rtc_wall_seconds(unsigned long *out)` |
| `DMA_CH1_ADDR` | macro | `drivers/sb16.c:75` | `#define DMA_CH1_ADDR` |
| `DMA_CH1_CNT` | macro | `drivers/sb16.c:76` | `#define DMA_CH1_CNT` |
| `DMA_CH1_MASK` | macro | `drivers/sb16.c:81` | `#define DMA_CH1_MASK` |
| `DMA_CH1_PAGE` | macro | `drivers/sb16.c:77` | `#define DMA_CH1_PAGE` |
| `DMA_CH1_SINGLE_READ` | macro | `drivers/sb16.c:68` | `#define DMA_CH1_SINGLE_READ` |
| `DMA_CH1_UNMASK` | macro | `drivers/sb16.c:80` | `#define DMA_CH1_UNMASK` |
| `DMA_FF_CLR` | macro | `drivers/sb16.c:79` | `#define DMA_FF_CLR` |
| `DMA_MASK` | macro | `drivers/sb16.c:78` | `#define DMA_MASK` |
| `DMA_MODE_PORT` | macro | `drivers/sb16.c:67` | `#define DMA_MODE_PORT` |
| `IRQ` | function | `drivers/sb16.c:22` | `* QEMU audio backends never raise the completion IRQ (they only consume once * their engine buffer drains, which a...` |
| `SB16_BASE_PORT` | macro | `drivers/sb16.c:48` | `#define SB16_BASE_PORT` |
| `SB16_BUF` | macro | `drivers/sb16.c:85` | `#define SB16_BUF` |
| `SB16_CMD_PLAY8` | macro | `drivers/sb16.c:57` | `#define SB16_CMD_PLAY8` |
| `SB16_CMD_READ_VER` | macro | `drivers/sb16.c:55` | `#define SB16_CMD_READ_VER` |
| `SB16_CMD_SET_FREQ` | macro | `drivers/sb16.c:56` | `#define SB16_CMD_SET_FREQ` |
| `SB16_CMD_SPK_OFF` | macro | `drivers/sb16.c:59` | `#define SB16_CMD_SPK_OFF` |
| `SB16_CMD_SPK_ON` | macro | `drivers/sb16.c:58` | `#define SB16_CMD_SPK_ON` |
| `SB16_DMA_BUF0` | macro | `drivers/sb16.c:83` | `#define SB16_DMA_BUF0` |
| `SB16_DSP_RDSTATUS` | macro | `drivers/sb16.c:61` | `#define SB16_DSP_RDSTATUS` |
| `SB16_DSP_READY_MASK` | macro | `drivers/sb16.c:73` | `#define SB16_DSP_READY_MASK` |
| `SB16_DSP_READ_DATA` | macro | `drivers/sb16.c:50` | `#define SB16_DSP_READ_DATA` |
| `SB16_DSP_RESET` | macro | `drivers/sb16.c:49` | `#define SB16_DSP_RESET` |
| `SB16_DSP_STATUS` | macro | `drivers/sb16.c:52` | `#define SB16_DSP_STATUS` |
| `SB16_DSP_WRITE_DATA` | macro | `drivers/sb16.c:51` | `#define SB16_DSP_WRITE_DATA` |
| `SB16_FREQ_HI` | macro | `drivers/sb16.c:71` | `#define SB16_FREQ_HI` |
| `SB16_FREQ_LO` | macro | `drivers/sb16.c:70` | `#define SB16_FREQ_LO` |
| `SB16_IRQ_ACK` | macro | `drivers/sb16.c:53` | `#define SB16_IRQ_ACK` |
| `SB16_MODE_PCM` | macro | `drivers/sb16.c:89` | `#define SB16_MODE_PCM` |
| `SB16_MODE_TONE` | macro | `drivers/sb16.c:88` | `#define SB16_MODE_TONE` |
| `SB16_SILENCE_SLOT` | macro | `drivers/sb16.c:84` | `#define SB16_SILENCE_SLOT` |
| `SB16_SQ_CYCLE` | macro | `drivers/sb16.c:91` | `#define SB16_SQ_CYCLE` |
| `pending` | function | `drivers/sb16.c:535` | `* reading without it eats whatever byte happens to be pending (or * times out), so the probe used to fail or misread...` |
| `sb16_arm` | function | `drivers/sb16.c:355` | `static void sb16_arm(int from_irq)` |
| `sb16_cmd` | function | `drivers/sb16.c:282` | `static void sb16_cmd(unsigned char c)` |
| `sb16_counters` | function | `drivers/sb16.c:479` | `void sb16_counters(sb16_counters_t *out)` |
| `sb16_dma_play` | function | `drivers/sb16.c:323` | `static void sb16_dma_play(unsigned addr, unsigned len)` |
| `sb16_init` | function | `drivers/sb16.c:530` | `int sb16_init(void)` |
| `sb16_irq` | function | `drivers/sb16.c:449` | `void sb16_irq(void)` |
| `sb16_kring_reset` | function | `drivers/sb16.c:118` | `static void sb16_kring_reset(void)` |
| `sb16_legacy_busy` | function | `drivers/sb16.c:472` | `int sb16_legacy_busy(void)` |
| `sb16_mix_all` | function | `drivers/sb16.c:194` | `static void sb16_mix_all(void)` |
| `sb16_mode_active` | function | `drivers/sb16.c:467` | `int sb16_mode_active(void)` |
| `sb16_ops_pcm_close` | function | `drivers/sb16.c:498` | `static void sb16_ops_pcm_close(device_t *dev)` |
| `sb16_ops_pcm_open` | function | `drivers/sb16.c:491` | `static void sb16_ops_pcm_open(device_t *dev)` |
| `sb16_ops_pcm_submit` | function | `drivers/sb16.c:505` | `static int sb16_ops_pcm_submit(device_t *dev, const unsigned char *pcm, unsigned len)` |
| `sb16_ops_present` | function | `drivers/sb16.c:484` | `static int sb16_ops_present(device_t *dev)` |
| `sb16_pcm_close` | function | `drivers/sb16.c:422` | `void sb16_pcm_close(void)` |
| `sb16_pcm_open` | function | `drivers/sb16.c:398` | `void sb16_pcm_open(void)` |
| `sb16_pcm_submit` | function | `drivers/sb16.c:431` | `int sb16_pcm_submit(const unsigned char *pcm, unsigned len)` |
| `sb16_poll` | function | `drivers/sb16.c:457` | `void sb16_poll(void)` |
| `sb16_present` | function | `drivers/sb16.c:380` | `int sb16_present(void)` |
| `sb16_pump` | function | `drivers/sb16.c:236` | `void sb16_pump(void)` |
| `sb16_read_data` | function | `drivers/sb16.c:287` | `static int sb16_read_data(unsigned char *out)` |
| `sb16_refill` | function | `drivers/sb16.c:339` | `static void sb16_refill(int slot_index)` |
| `sb16_reset_dsp` | function | `drivers/sb16.c:297` | `static int sb16_reset_dsp(void)` |
| `sb16_ring_free` | function | `drivers/sb16.c:466` | `unsigned sb16_ring_free(void)` |
| `sb16_slot` | function | `drivers/sb16.c:130` | `static unsigned char *sb16_slot(unsigned i)` |
| `sb16_stream_close` | function | `drivers/sb16.c:154` | `void sb16_stream_close(int id)` |
| `sb16_stream_count` | function | `drivers/sb16.c:183` | `int sb16_stream_count(void)` |
| `sb16_stream_open` | function | `drivers/sb16.c:138` | `int sb16_stream_open(void)` |
| `sb16_stream_submit` | function | `drivers/sb16.c:162` | `int sb16_stream_submit(int id, const unsigned char *pcm, unsigned len)` |
| `sb16_stream_volume` | function | `drivers/sb16.c:177` | `void sb16_stream_volume(int id, unsigned char vol)` |
| `sb16_tone` | function | `drivers/sb16.c:382` | `void sb16_tone(unsigned freq)` |
| `sb16_wait_write` | function | `drivers/sb16.c:278` | `static int sb16_wait_write(void)` |
| `UBK_BULK_BURST` | macro | `drivers/usbblk.c:64` | `#define UBK_BULK_BURST` |
| `UBK_BULK_INTERVAL` | macro | `drivers/usbblk.c:63` | `#define UBK_BULK_INTERVAL` |
| `UBK_CBW_FLAG_IN` | macro | `drivers/usbblk.c:24` | `#define UBK_CBW_FLAG_IN` |
| `UBK_CBW_LEN` | macro | `drivers/usbblk.c:22` | `#define UBK_CBW_LEN` |
| `UBK_CBW_SIG` | macro | `drivers/usbblk.c:23` | `#define UBK_CBW_SIG` |
| `UBK_CDB6_LEN` | macro | `drivers/usbblk.c:181` | `#define UBK_CDB6_LEN` |
| `UBK_CDB_LEN` | macro | `drivers/usbblk.c:79` | `#define UBK_CDB_LEN` |
| `UBK_CLEAR_FEATURE` | macro | `drivers/usbblk.c:149` | `#define UBK_CLEAR_FEATURE` |
| `UBK_CSW_LEN` | macro | `drivers/usbblk.c:27` | `#define UBK_CSW_LEN` |
| `UBK_CSW_SIG` | macro | `drivers/usbblk.c:28` | `#define UBK_CSW_SIG` |
| `UBK_CSW_STATUS_FAILED` | macro | `drivers/usbblk.c:30` | `#define UBK_CSW_STATUS_FAILED` |
| `UBK_CSW_STATUS_PASSED` | macro | `drivers/usbblk.c:29` | `#define UBK_CSW_STATUS_PASSED` |
| `UBK_ENDP_HALT` | macro | `drivers/usbblk.c:150` | `#define UBK_ENDP_HALT` |
| `UBK_MAX_XFER_BLOCKS` | macro | `drivers/usbblk.c:70` | `#define UBK_MAX_XFER_BLOCKS` |
| `UBK_MS_RESET` | macro | `drivers/usbblk.c:148` | `#define UBK_MS_RESET` |
| `UBK_READY_TRIES` | macro | `drivers/usbblk.c:293` | `#define UBK_READY_TRIES` |
| `UBK_SCSI_INQUIRY` | macro | `drivers/usbblk.c:35` | `#define UBK_SCSI_INQUIRY` |
| `UBK_SCSI_READ10` | macro | `drivers/usbblk.c:37` | `#define UBK_SCSI_READ10` |
| `UBK_SCSI_READ_CAPACITY` | macro | `drivers/usbblk.c:36` | `#define UBK_SCSI_READ_CAPACITY` |
| `UBK_SCSI_REQUEST_SENSE` | macro | `drivers/usbblk.c:34` | `#define UBK_SCSI_REQUEST_SENSE` |
| `UBK_SCSI_TEST_UNIT_READY` | macro | `drivers/usbblk.c:33` | `#define UBK_SCSI_TEST_UNIT_READY` |
| `UBK_SCSI_WRITE10` | macro | `drivers/usbblk.c:38` | `#define UBK_SCSI_WRITE10` |
| `UBK_SENSE_LEN` | macro | `drivers/usbblk.c:261` | `#define UBK_SENSE_LEN` |
| `ubk_blk_present` | function | `drivers/usbblk.c:438` | `static int ubk_blk_present(device_t *dev)` |
| `ubk_blk_read` | function | `drivers/usbblk.c:421` | `static int ubk_blk_read(device_t *dev, unsigned lba, unsigned count,                         void...` |
| `ubk_blk_sectors` | function | `drivers/usbblk.c:433` | `static unsigned ubk_blk_sectors(device_t *dev)` |
| `ubk_blk_write` | function | `drivers/usbblk.c:427` | `static int ubk_blk_write(device_t *dev, unsigned lba, unsigned count,                          co...` |
| `ubk_build_cbw` | function | `drivers/usbblk.c:92` | `void ubk_build_cbw(unsigned char *out, unsigned tag, unsigned long lba,                    unsign...` |
| `ubk_cdb10` | function | `drivers/usbblk.c:80` | `static void ubk_cdb10(unsigned char *cdb, unsigned char opcode,                       unsigned lo...` |
| `ubk_check_csw` | function | `drivers/usbblk.c:121` | `int ubk_check_csw(const unsigned char *csw, unsigned tag, unsigned expect_len)` |
| `ubk_claim_eps` | function | `drivers/usbblk.c:377` | `static int ubk_claim_eps(int device, const xhc_iface_t *iface)` |
| `ubk_command` | function | `drivers/usbblk.c:279` | `static int ubk_command(unsigned char *cdb, unsigned cdb_len,                        unsigned char...` |
| `ubk_command_raw` | function | `drivers/usbblk.c:187` | `static int ubk_command_raw(unsigned char *cdb, unsigned cdb_len,                            unsig...` |
| `ubk_counters` | function | `drivers/usbblk.c:72` | `void ubk_counters(ubk_counters_t *out)` |
| `ubk_disk_t` | struct | `drivers/usbblk.c:44` | `` |
| `ubk_init` | function | `drivers/usbblk.c:457` | `int ubk_init(void)` |
| `ubk_present` | function | `drivers/usbblk.c:336` | `int ubk_present(void)` |
| `ubk_read_capacity` | function | `drivers/usbblk.c:311` | `static int ubk_read_capacity(unsigned long *sectors)` |
| `ubk_read_sectors` | function | `drivers/usbblk.c:365` | `int ubk_read_sectors(unsigned long lba, unsigned count, void *buf)` |
| `ubk_sectors` | function | `drivers/usbblk.c:340` | `unsigned long ubk_sectors(void)` |
| `ubk_sense` | function | `drivers/usbblk.c:262` | `static void ubk_sense(void)` |
| `ubk_unit_ready` | function | `drivers/usbblk.c:294` | `static int ubk_unit_ready(void)` |
| `ubk_write_sectors` | function | `drivers/usbblk.c:370` | `int ubk_write_sectors(unsigned long lba, unsigned count, const void *buf)` |
| `ubk_xfer` | function | `drivers/usbblk.c:347` | `static int ubk_xfer(unsigned long lba, unsigned count, void *buf, int read)` |
| `USBHID_INTERVAL` | macro | `drivers/usbhid.c:55` | `#define USBHID_INTERVAL` |
| `USBHID_MAX_DEVS` | macro | `drivers/usbhid.c:35` | `#define USBHID_MAX_DEVS` |
| `USBHID_MAX_SCANCODES` | macro | `drivers/usbhid.c:204` | `#define USBHID_MAX_SCANCODES` |
| `usbhid_claim` | function | `drivers/usbhid.c:353` | `static int usbhid_claim(int device, const xhc_iface_t *iface, int is_mouse)` |
| `usbhid_counters` | function | `drivers/usbhid.c:270` | `void usbhid_counters(usbhid_counters_t *out)` |
| `usbhid_dev_t` | struct | `drivers/usbhid.c:40` | `` |
| `usbhid_emit_mod` | function | `drivers/usbhid.c:165` | `static int usbhid_emit_mod(unsigned char *out, int max, int n, unsigned bit,                     ...` |
| `usbhid_emit_usage` | function | `drivers/usbhid.c:183` | `static int usbhid_emit_usage(unsigned char *out, int max, int n,                              uns...` |
| `usbhid_ep_taken` | function | `drivers/usbhid.c:312` | `static int usbhid_ep_taken(int ep_index)` |
| `usbhid_init` | function | `drivers/usbhid.c:384` | `int usbhid_init(void)` |
| `usbhid_is_mouse_maxp` | function | `drivers/usbhid.c:380` | `static int usbhid_is_mouse_maxp(int maxp)` |
| `usbhid_kbd_scancodes` | function | `drivers/usbhid.c:206` | `int usbhid_kbd_scancodes(const unsigned char prev[HID_KBD_REPORT_LEN],                          c...` |
| `usbhid_keyboard_present` | function | `drivers/usbhid.c:256` | `int usbhid_keyboard_present(void)` |
| `usbhid_mouse_decode` | function | `drivers/usbhid.c:241` | `void usbhid_mouse_decode(const unsigned char prev[HID_MOUSE_REPORT_LEN],                         ...` |
| `usbhid_mouse_present` | function | `drivers/usbhid.c:263` | `int usbhid_mouse_present(void)` |
| `usbhid_poll` | function | `drivers/usbhid.c:501` | `int usbhid_poll(void)` |
| `usbhid_poll_keyboard` | function | `drivers/usbhid.c:485` | `int usbhid_poll_keyboard(void)` |
| `usbhid_poll_mouse` | function | `drivers/usbhid.c:493` | `int usbhid_poll_mouse(void)` |
| `usbhid_poll_one` | function | `drivers/usbhid.c:422` | `static int usbhid_poll_one(usbhid_dev_t *d)` |
| `usbhid_press_kbd_report` | function | `drivers/usbhid.c:274` | `int usbhid_press_kbd_report(const unsigned char report[HID_KBD_REPORT_LEN])` |
| `usbhid_put` | function | `drivers/usbhid.c:153` | `static int usbhid_put(unsigned char *out, int max, int n, unsigned char sc)` |
| `usbhid_report_has` | function | `drivers/usbhid.c:138` | `static int usbhid_report_has(const unsigned char report[HID_KBD_REPORT_LEN],                     ...` |
| `usbhid_set1_from_usage` | function | `drivers/usbhid.c:117` | `int usbhid_set1_from_usage(unsigned usage, unsigned char *sc, int *e0)` |
| `usbhid_set_boot_protocol` | function | `drivers/usbhid.c:295` | `static int usbhid_set_boot_protocol(int device, int iface)` |
| `usbhid_take_ep` | function | `drivers/usbhid.c:325` | `static int usbhid_take_ep(int device, const xhc_iface_t *iface,                           int *maxp)` |
| `usbhid_usage_make` | function | `drivers/usbhid.c:128` | `static int usbhid_usage_make(unsigned usage, unsigned char *sc, int *e0)` |
| `VBLK_AVAIL_OFF` | macro | `drivers/virtio_blk.c:43` | `#define VBLK_AVAIL_OFF` |
| `VBLK_DESC_NEXT` | macro | `drivers/virtio_blk.c:47` | `#define VBLK_DESC_NEXT` |
| `VBLK_DESC_SZ` | macro | `drivers/virtio_blk.c:38` | `#define VBLK_DESC_SZ` |
| `VBLK_DESC_WRITE` | macro | `drivers/virtio_blk.c:48` | `#define VBLK_DESC_WRITE` |
| `VBLK_DEV_LEGACY` | macro | `drivers/virtio_blk.c:29` | `#define VBLK_DEV_LEGACY` |
| `VBLK_DEV_TRANS` | macro | `drivers/virtio_blk.c:30` | `#define VBLK_DEV_TRANS` |
| `VBLK_F_ACK` | macro | `drivers/virtio_blk.c:32` | `#define VBLK_F_ACK` |
| `VBLK_F_DRIVER` | macro | `drivers/virtio_blk.c:33` | `#define VBLK_F_DRIVER` |
| `VBLK_F_DRIVER_OK` | macro | `drivers/virtio_blk.c:35` | `#define VBLK_F_DRIVER_OK` |
| `VBLK_F_OK` | macro | `drivers/virtio_blk.c:34` | `#define VBLK_F_OK` |
| `VBLK_QAREA` | macro | `drivers/virtio_blk.c:45` | `#define VBLK_QAREA` |
| `VBLK_QNUM` | macro | `drivers/virtio_blk.c:37` | `#define VBLK_QNUM` |
| `VBLK_REQ_IN` | macro | `drivers/virtio_blk.c:50` | `#define VBLK_REQ_IN` |
| `VBLK_REQ_OUT` | macro | `drivers/virtio_blk.c:51` | `#define VBLK_REQ_OUT` |
| `VBLK_SECTOR` | macro | `drivers/virtio_blk.c:54` | `#define VBLK_SECTOR` |
| `VBLK_TMO_MS` | macro | `drivers/virtio_blk.c:53` | `#define VBLK_TMO_MS` |
| `VBLK_USED_OFF` | macro | `drivers/virtio_blk.c:44` | `#define VBLK_USED_OFF` |
| `VBLK_VENDOR` | macro | `drivers/virtio_blk.c:28` | `#define VBLK_VENDOR` |
| `vblk_avail_idx` | function | `drivers/virtio_blk.c:183` | `static unsigned short vblk_avail_idx(void)` |
| `vblk_avail_push` | function | `drivers/virtio_blk.c:188` | `static void vblk_avail_push(unsigned short head)` |
| `vblk_desc` | function | `drivers/virtio_blk.c:167` | `static void vblk_desc(unsigned idx, unsigned long addr, unsigned len,         unsigned short flag...` |
| `vblk_inb` | function | `drivers/virtio_blk.c:85` | `static unsigned char vblk_inb(unsigned short port)` |
| `vblk_init` | function | `drivers/virtio_blk.c:100` | `int vblk_init(void)` |
| `vblk_inl` | function | `drivers/virtio_blk.c:75` | `static unsigned vblk_inl(unsigned short port)` |
| `vblk_inw` | function | `drivers/virtio_blk.c:89` | `static unsigned short vblk_inw(unsigned short port)` |
| `vblk_ops_present` | function | `drivers/virtio_blk.c:302` | `static int vblk_ops_present(device_t *dev)` |
| `vblk_ops_read` | function | `drivers/virtio_blk.c:282` | `static int vblk_ops_read(device_t *dev, unsigned lba, unsigned count,         void *buf)` |
| `vblk_ops_total` | function | `drivers/virtio_blk.c:296` | `static unsigned vblk_ops_total(device_t *dev)` |
| `vblk_ops_write` | function | `drivers/virtio_blk.c:289` | `static int vblk_ops_write(device_t *dev, unsigned lba, unsigned count,         const void *buf)` |
| `vblk_outb` | function | `drivers/virtio_blk.c:81` | `static void vblk_outb(unsigned short port, unsigned char val)` |
| `vblk_outl` | function | `drivers/virtio_blk.c:71` | `static void vblk_outl(unsigned short port, unsigned val)` |
| `vblk_outw` | function | `drivers/virtio_blk.c:93` | `static void vblk_outw(unsigned short port, unsigned short val)` |
| `vblk_present` | function | `drivers/virtio_blk.c:158` | `int vblk_present(void)` |
| `vblk_register_device` | function | `drivers/virtio_blk.c:327` | `void vblk_register_device(void)` |
| `vblk_req_t` | struct | `drivers/virtio_blk.c:56` | `` |
| `vblk_request` | function | `drivers/virtio_blk.c:212` | `static int vblk_request(unsigned dir, unsigned long sector,         unsigned char *buf, unsigned ...` |
| `vblk_sectors` | function | `drivers/virtio_blk.c:163` | `unsigned long vblk_sectors(void)` |
| `vblk_used_idx` | function | `drivers/virtio_blk.c:199` | `static unsigned short vblk_used_idx(void)` |
| `vblk_write_sectors` | function | `drivers/virtio_blk.c:266` | `int vblk_write_sectors(unsigned lba, unsigned count, const void *buf)` |
| `VNET_AVAIL_OFF` | macro | `drivers/virtio_net.c:40` | `#define VNET_AVAIL_OFF` |
| `VNET_CFG_MAC` | macro | `drivers/virtio_net.c:59` | `#define VNET_CFG_MAC` |
| `VNET_CFG_STATUS` | macro | `drivers/virtio_net.c:60` | `#define VNET_CFG_STATUS` |
| `VNET_DESC_NEXT` | macro | `drivers/virtio_net.c:44` | `#define VNET_DESC_NEXT` |
| `VNET_DESC_SZ` | macro | `drivers/virtio_net.c:39` | `#define VNET_DESC_SZ` |
| `VNET_DESC_WRITE` | macro | `drivers/virtio_net.c:45` | `#define VNET_DESC_WRITE` |
| `VNET_DEV_LEGACY` | macro | `drivers/virtio_net.c:30` | `#define VNET_DEV_LEGACY` |
| `VNET_DEV_TRANS` | macro | `drivers/virtio_net.c:31` | `#define VNET_DEV_TRANS` |
| `VNET_F_ACK` | macro | `drivers/virtio_net.c:33` | `#define VNET_F_ACK` |
| `VNET_F_DRIVER` | macro | `drivers/virtio_net.c:34` | `#define VNET_F_DRIVER` |
| `VNET_F_DRIVER_OK` | macro | `drivers/virtio_net.c:36` | `#define VNET_F_DRIVER_OK` |
| `VNET_F_OK` | macro | `drivers/virtio_net.c:35` | `#define VNET_F_OK` |
| `VNET_HDR_LEN` | macro | `drivers/virtio_net.c:50` | `#define VNET_HDR_LEN` |
| `VNET_MAX_FRAME` | macro | `drivers/virtio_net.c:55` | `#define VNET_MAX_FRAME` |
| `VNET_MIN_FRAME` | macro | `drivers/virtio_net.c:54` | `#define VNET_MIN_FRAME` |
| `VNET_POLL_MAX` | macro | `drivers/virtio_net.c:57` | `#define VNET_POLL_MAX` |
| `VNET_QAREA` | macro | `drivers/virtio_net.c:42` | `#define VNET_QAREA` |
| `VNET_QNUM` | macro | `drivers/virtio_net.c:38` | `#define VNET_QNUM` |
| `VNET_Q_RX` | macro | `drivers/virtio_net.c:47` | `#define VNET_Q_RX` |
| `VNET_Q_TX` | macro | `drivers/virtio_net.c:48` | `#define VNET_Q_TX` |
| `VNET_RX_BUFS` | macro | `drivers/virtio_net.c:51` | `#define VNET_RX_BUFS` |
| `VNET_RX_SIZE` | macro | `drivers/virtio_net.c:52` | `#define VNET_RX_SIZE` |
| `VNET_ST_LINK_UP` | macro | `drivers/virtio_net.c:61` | `#define VNET_ST_LINK_UP` |
| `VNET_TMO_MS` | macro | `drivers/virtio_net.c:56` | `#define VNET_TMO_MS` |
| `VNET_TX_SIZE` | macro | `drivers/virtio_net.c:53` | `#define VNET_TX_SIZE` |
| `VNET_USED_OFF` | macro | `drivers/virtio_net.c:41` | `#define VNET_USED_OFF` |
| `VNET_VENDOR` | macro | `drivers/virtio_net.c:29` | `#define VNET_VENDOR` |
| `unusable` | function | `drivers/virtio_net.c:181` | `* unusable (fail-closed, rtl8139 stays). */ int vnet_init(void)` |
| `vnet_avail_push` | function | `drivers/virtio_net.c:161` | `static void vnet_avail_push(unsigned char *page, unsigned qnum,         unsigned short head)` |
| `vnet_counters` | function | `drivers/virtio_net.c:239` | `void vnet_counters(unsigned int *tx_frames, unsigned int *rx_frames)` |
| `vnet_desc` | function | `drivers/virtio_net.c:144` | `static void vnet_desc(unsigned char *page, unsigned idx, unsigned long addr,         unsigned len...` |
| `vnet_get_mac` | function | `drivers/virtio_net.c:228` | `void vnet_get_mac(unsigned char out[6])` |
| `vnet_inb` | function | `drivers/virtio_net.c:93` | `static unsigned char vnet_inb(unsigned short port)` |
| `vnet_inl` | function | `drivers/virtio_net.c:105` | `static unsigned vnet_inl(unsigned short port)` |
| `vnet_inw` | function | `drivers/virtio_net.c:99` | `static unsigned short vnet_inw(unsigned short port)` |
| `vnet_iobase` | function | `drivers/virtio_net.c:234` | `unsigned short vnet_iobase(void)` |
| `vnet_link_up` | function | `drivers/virtio_net.c:277` | `int vnet_link_up(void)` |
| `vnet_outb` | function | `drivers/virtio_net.c:81` | `static void vnet_outb(unsigned short port, unsigned char v)` |
| `vnet_outl` | function | `drivers/virtio_net.c:89` | `static void vnet_outl(unsigned short port, unsigned v)` |
| `vnet_outw` | function | `drivers/virtio_net.c:85` | `static void vnet_outw(unsigned short port, unsigned short v)` |
| `vnet_poll` | function | `drivers/virtio_net.c:287` | `void vnet_poll(void)` |
| `vnet_present` | function | `drivers/virtio_net.c:223` | `int vnet_present(void)` |
| `vnet_queue_up` | function | `drivers/virtio_net.c:114` | `static unsigned vnet_queue_up(unsigned qsel)` |
| `vnet_used_idx` | function | `drivers/virtio_net.c:174` | `static unsigned short vnet_used_idx(unsigned char *used)` |
| `XF_LINK_TC` | macro | `drivers/xhci.c:455` | `#define XF_LINK_TC` |
| `XHC_CAP_DBOFF` | macro | `drivers/xhci.c:86` | `#define XHC_CAP_DBOFF` |
| `XHC_CAP_HCCP1` | macro | `drivers/xhci.c:85` | `#define XHC_CAP_HCCP1` |
| `XHC_CAP_HCSP1` | macro | `drivers/xhci.c:82` | `#define XHC_CAP_HCSP1` |
| `XHC_CAP_HCSP2` | macro | `drivers/xhci.c:83` | `#define XHC_CAP_HCSP2` |
| `XHC_CAP_HCSP3` | macro | `drivers/xhci.c:84` | `#define XHC_CAP_HCSP3` |
| `XHC_CAP_OFF` | macro | `drivers/xhci.c:55` | `#define XHC_CAP_OFF` |
| `XHC_CAP_RTSOFF` | macro | `drivers/xhci.c:87` | `#define XHC_CAP_RTSOFF` |
| `XHC_CC_SHORT_PACKET` | macro | `drivers/xhci.c:132` | `#define XHC_CC_SHORT_PACKET` |
| `XHC_CC_SUCCESS` | macro | `drivers/xhci.c:131` | `#define XHC_CC_SUCCESS` |
| `XHC_CFG_TOTAL_LEN_OFF` | macro | `drivers/xhci.c:227` | `#define XHC_CFG_TOTAL_LEN_OFF` |
| `XHC_CMD_RESET` | macro | `drivers/xhci.c:93` | `#define XHC_CMD_RESET` |
| `XHC_CMD_RUN` | macro | `drivers/xhci.c:92` | `#define XHC_CMD_RUN` |
| `XHC_CONTROL_TRIES` | macro | `drivers/xhci.c:1047` | `#define XHC_CONTROL_TRIES` |
| `XHC_CTX_DEVICE_BYTES` | macro | `drivers/xhci.c:175` | `#define XHC_CTX_DEVICE_BYTES` |
| `XHC_CTX_EP_BYTES` | macro | `drivers/xhci.c:176` | `#define XHC_CTX_EP_BYTES` |
| `XHC_CTX_SLOT_STRIDE` | macro | `drivers/xhci.c:173` | `#define XHC_CTX_SLOT_STRIDE` |
| `XHC_CTX_SLOT_STRIDE64` | macro | `drivers/xhci.c:174` | `#define XHC_CTX_SLOT_STRIDE64` |
| `XHC_DB_COMMAND` | macro | `drivers/xhci.c:515` | `#define XHC_DB_COMMAND` |
| `XHC_DB_STRIDE` | macro | `drivers/xhci.c:514` | `#define XHC_DB_STRIDE` |
| `XHC_DCBAA_ENTRIES` | macro | `drivers/xhci.c:193` | `#define XHC_DCBAA_ENTRIES` |
| `XHC_DEV_DESC_LEN_OFF` | macro | `drivers/xhci.c:224` | `#define XHC_DEV_DESC_LEN_OFF` |
| `XHC_DEV_DESC_NUM_CFG_OFF` | macro | `drivers/xhci.c:226` | `#define XHC_DEV_DESC_NUM_CFG_OFF` |
| `XHC_DEV_DESC_TYPE_OFF` | macro | `drivers/xhci.c:225` | `#define XHC_DEV_DESC_TYPE_OFF` |
| `XHC_DMA_ALIGN` | macro | `drivers/xhci.c:212` | `#define XHC_DMA_ALIGN` |
| `XHC_DT_CONFIG` | macro | `drivers/xhci.c:219` | `#define XHC_DT_CONFIG` |
| `XHC_DT_DEVICE` | macro | `drivers/xhci.c:218` | `#define XHC_DT_DEVICE` |
| `XHC_DT_ENDPOINT` | macro | `drivers/xhci.c:221` | `#define XHC_DT_ENDPOINT` |
| `XHC_DT_INTERFACE` | macro | `drivers/xhci.c:220` | `#define XHC_DT_INTERFACE` |
| `XHC_EPT_BULK_IN` | macro | `drivers/xhci.c:167` | `#define XHC_EPT_BULK_IN` |
| `XHC_EPT_BULK_OUT` | macro | `drivers/xhci.c:164` | `#define XHC_EPT_BULK_OUT` |
| `XHC_EPT_CONTROL` | macro | `drivers/xhci.c:162` | `#define XHC_EPT_CONTROL` |
| `XHC_EPT_INT_IN` | macro | `drivers/xhci.c:168` | `#define XHC_EPT_INT_IN` |
| `XHC_EPT_INT_OUT` | macro | `drivers/xhci.c:165` | `#define XHC_EPT_INT_OUT` |
| `XHC_EPT_ISO_IN` | macro | `drivers/xhci.c:166` | `#define XHC_EPT_ISO_IN` |
| `XHC_EPT_ISO_OUT` | macro | `drivers/xhci.c:163` | `#define XHC_EPT_ISO_OUT` |
| `XHC_EP_AVG_OFF` | macro | `drivers/xhci.c:153` | `#define XHC_EP_AVG_OFF` |
| `XHC_EP_BURST_SHIFT` | macro | `drivers/xhci.c:157` | `#define XHC_EP_BURST_SHIFT` |
| `XHC_EP_CERR` | macro | `drivers/xhci.c:169` | `#define XHC_EP_CERR` |
| `XHC_EP_DCS_BIT` | macro | `drivers/xhci.c:159` | `#define XHC_EP_DCS_BIT` |
| `XHC_EP_DEQ_OFF` | macro | `drivers/xhci.c:152` | `#define XHC_EP_DEQ_OFF` |
| `XHC_EP_DESC_ADDR_OFF` | macro | `drivers/xhci.c:232` | `#define XHC_EP_DESC_ADDR_OFF` |
| `XHC_EP_DESC_MAXP_OFF` | macro | `drivers/xhci.c:234` | `#define XHC_EP_DESC_MAXP_OFF` |
| `XHC_EP_DESC_TYPE_OFF` | macro | `drivers/xhci.c:233` | `#define XHC_EP_DESC_TYPE_OFF` |
| `XHC_EP_DW0_OFF` | macro | `drivers/xhci.c:150` | `#define XHC_EP_DW0_OFF` |
| `XHC_EP_DW1_OFF` | macro | `drivers/xhci.c:151` | `#define XHC_EP_DW1_OFF` |
| `XHC_EP_INTERVAL_SHIFT` | macro | `drivers/xhci.c:155` | `#define XHC_EP_INTERVAL_SHIFT` |
| `XHC_EP_MAXP_SHIFT` | macro | `drivers/xhci.c:158` | `#define XHC_EP_MAXP_SHIFT` |
| `XHC_EP_MULT_SHIFT` | macro | `drivers/xhci.c:154` | `#define XHC_EP_MULT_SHIFT` |
| `XHC_EP_TYPE_SHIFT` | macro | `drivers/xhci.c:156` | `#define XHC_EP_TYPE_SHIFT` |
| `XHC_ERDP_EHB` | macro | `drivers/xhci.c:79` | `#define XHC_ERDP_EHB` |
| `XHC_ERST_BYTES` | macro | `drivers/xhci.c:200` | `#define XHC_ERST_BYTES` |
| `XHC_ERST_CYCLE` | macro | `drivers/xhci.c:199` | `#define XHC_ERST_CYCLE` |
| `XHC_ERST_RING_HI` | macro | `drivers/xhci.c:197` | `#define XHC_ERST_RING_HI` |
| `XHC_ERST_RING_LO` | macro | `drivers/xhci.c:196` | `#define XHC_ERST_RING_LO` |
| `XHC_ERST_SIZE` | macro | `drivers/xhci.c:198` | `#define XHC_ERST_SIZE` |
| `XHC_EVT_CC` | macro | `drivers/xhci.c:136` | `#define XHC_EVT_CC(e)` |
| `XHC_EVT_CMD_COMPLETION` | macro | `drivers/xhci.c:140` | `#define XHC_EVT_CMD_COMPLETION` |
| `XHC_EVT_LEN` | macro | `drivers/xhci.c:138` | `#define XHC_EVT_LEN(e)` |
| `XHC_EVT_SLOT` | macro | `drivers/xhci.c:137` | `#define XHC_EVT_SLOT(e)` |
| `XHC_EVT_TRANSFER` | macro | `drivers/xhci.c:139` | `#define XHC_EVT_TRANSFER` |
| `XHC_EVT_TYPE` | macro | `drivers/xhci.c:135` | `#define XHC_EVT_TYPE(e)` |
| `XHC_HCC_AC64` | macro | `drivers/xhci.c:88` | `#define XHC_HCC_AC64` |
| `XHC_HCC_CSZ` | macro | `drivers/xhci.c:89` | `#define XHC_HCC_CSZ` |
| `XHC_ICTX_ADD_OFF` | macro | `drivers/xhci.c:190` | `#define XHC_ICTX_ADD_OFF` |
| `XHC_ICTX_BYTES` | macro | `drivers/xhci.c:177` | `#define XHC_ICTX_BYTES` |
| `XHC_ICTX_DROP_OFF` | macro | `drivers/xhci.c:189` | `#define XHC_ICTX_DROP_OFF` |
| `XHC_IFACE_CLASS_OFF` | macro | `drivers/xhci.c:229` | `#define XHC_IFACE_CLASS_OFF` |
| `XHC_IFACE_OFF` | macro | `drivers/xhci.c:228` | `#define XHC_IFACE_OFF` |
| `XHC_IFACE_PROTO_OFF` | macro | `drivers/xhci.c:231` | `#define XHC_IFACE_PROTO_OFF` |
| `XHC_IFACE_SUBCLASS_OFF` | macro | `drivers/xhci.c:230` | `#define XHC_IFACE_SUBCLASS_OFF` |
| `XHC_IMAN_IE` | macro | `drivers/xhci.c:78` | `#define XHC_IMAN_IE` |
| `XHC_IMAN_IP` | macro | `drivers/xhci.c:77` | `#define XHC_IMAN_IP` |
| `XHC_OP_CONFIG` | macro | `drivers/xhci.c:63` | `#define XHC_OP_CONFIG` |
| `XHC_OP_CRCR` | macro | `drivers/xhci.c:61` | `#define XHC_OP_CRCR` |
| `XHC_OP_DCBAAP` | macro | `drivers/xhci.c:62` | `#define XHC_OP_DCBAAP` |
| `XHC_OP_PAGESIZE` | macro | `drivers/xhci.c:60` | `#define XHC_OP_PAGESIZE` |
| `XHC_OP_PORTSC` | macro | `drivers/xhci.c:64` | `#define XHC_OP_PORTSC` |
| `XHC_OP_USBCMD` | macro | `drivers/xhci.c:58` | `#define XHC_OP_USBCMD` |
| `XHC_OP_USBSTS` | macro | `drivers/xhci.c:59` | `#define XHC_OP_USBSTS` |
| `XHC_PORT_CCS` | macro | `drivers/xhci.c:100` | `#define XHC_PORT_CCS` |
| `XHC_PORT_CHG_MASK` | macro | `drivers/xhci.c:106` | `#define XHC_PORT_CHG_MASK` |
| `XHC_PORT_PED` | macro | `drivers/xhci.c:101` | `#define XHC_PORT_PED` |
| `XHC_PORT_PP` | macro | `drivers/xhci.c:103` | `#define XHC_PORT_PP` |
| `XHC_PORT_PR` | macro | `drivers/xhci.c:102` | `#define XHC_PORT_PR` |
| `XHC_PORT_SPEED_MASK` | macro | `drivers/xhci.c:105` | `#define XHC_PORT_SPEED_MASK` |
| `XHC_PORT_SPEED_SHIFT` | macro | `drivers/xhci.c:104` | `#define XHC_PORT_SPEED_SHIFT` |
| `XHC_PORT_STRIDE` | macro | `drivers/xhci.c:65` | `#define XHC_PORT_STRIDE` |
| `XHC_RING_USABLE` | macro | `drivers/xhci.c:215` | `#define XHC_RING_USABLE` |
| `XHC_RUN_ERDP` | macro | `drivers/xhci.c:76` | `#define XHC_RUN_ERDP` |
| `XHC_RUN_ERSTBA` | macro | `drivers/xhci.c:75` | `#define XHC_RUN_ERSTBA` |
| `XHC_RUN_ERSTSZ` | macro | `drivers/xhci.c:74` | `#define XHC_RUN_ERSTSZ` |
| `XHC_RUN_IMAN` | macro | `drivers/xhci.c:72` | `#define XHC_RUN_IMAN` |
| `XHC_RUN_IMOD` | macro | `drivers/xhci.c:73` | `#define XHC_RUN_IMOD` |
| `XHC_RUN_INTR0` | macro | `drivers/xhci.c:71` | `#define XHC_RUN_INTR0` |
| `XHC_SLOT_ADDR_OFF` | macro | `drivers/xhci.c:183` | `#define XHC_SLOT_ADDR_OFF` |
| `XHC_SLOT_DW0_OFF` | macro | `drivers/xhci.c:181` | `#define XHC_SLOT_DW0_OFF` |
| `XHC_SLOT_DW1_OFF` | macro | `drivers/xhci.c:182` | `#define XHC_SLOT_DW1_OFF` |
| `XHC_SLOT_ENTRIES_SHIFT` | macro | `drivers/xhci.c:185` | `#define XHC_SLOT_ENTRIES_SHIFT` |
| `XHC_SLOT_RHPORT_SHIFT` | macro | `drivers/xhci.c:186` | `#define XHC_SLOT_RHPORT_SHIFT` |
| `XHC_SLOT_SPEED_SHIFT` | macro | `drivers/xhci.c:184` | `#define XHC_SLOT_SPEED_SHIFT` |
| `XHC_STS_ATE` | macro | `drivers/xhci.c:97` | `#define XHC_STS_ATE` |
| `XHC_STS_HALTED` | macro | `drivers/xhci.c:96` | `#define XHC_STS_HALTED` |
| `XHC_TRB_CYCLE` | macro | `drivers/xhci.c:110` | `#define XHC_TRB_CYCLE(t)` |
| `XHC_TRB_DIR` | macro | `drivers/xhci.c:926` | `#define XHC_TRB_DIR` |
| `XHC_TRB_IDT` | macro | `drivers/xhci.c:925` | `#define XHC_TRB_IDT` |
| `XHC_TRB_IOC` | macro | `drivers/xhci.c:924` | `#define XHC_TRB_IOC` |
| `XHC_TRB_MAKE_TYPE` | macro | `drivers/xhci.c:111` | `#define XHC_TRB_MAKE_TYPE(v)` |
| `XHC_TRB_TYPE` | macro | `drivers/xhci.c:109` | `#define XHC_TRB_TYPE(t)` |
| `XHC_TRB_TYPE_ADDRESS_DEVICE` | macro | `drivers/xhci.c:120` | `#define XHC_TRB_TYPE_ADDRESS_DEVICE` |
| `XHC_TRB_TYPE_CMD_COMPLETION` | macro | `drivers/xhci.c:127` | `#define XHC_TRB_TYPE_CMD_COMPLETION` |
| `XHC_TRB_TYPE_CONFIGURE_ENDPOINT` | macro | `drivers/xhci.c:121` | `#define XHC_TRB_TYPE_CONFIGURE_ENDPOINT` |
| `XHC_TRB_TYPE_DATA` | macro | `drivers/xhci.c:115` | `#define XHC_TRB_TYPE_DATA` |
| `XHC_TRB_TYPE_ENABLE_SLOT` | macro | `drivers/xhci.c:119` | `#define XHC_TRB_TYPE_ENABLE_SLOT` |
| `XHC_TRB_TYPE_LINK` | macro | `drivers/xhci.c:117` | `#define XHC_TRB_TYPE_LINK` |
| `XHC_TRB_TYPE_NOOP_CMD` | macro | `drivers/xhci.c:125` | `#define XHC_TRB_TYPE_NOOP_CMD` |
| `XHC_TRB_TYPE_NOOP_TRB` | macro | `drivers/xhci.c:118` | `#define XHC_TRB_TYPE_NOOP_TRB` |
| `XHC_TRB_TYPE_NORMAL` | macro | `drivers/xhci.c:113` | `#define XHC_TRB_TYPE_NORMAL` |
| `XHC_TRB_TYPE_PORT_STATUS` | macro | `drivers/xhci.c:128` | `#define XHC_TRB_TYPE_PORT_STATUS` |
| `XHC_TRB_TYPE_RESET_ENDPOINT` | macro | `drivers/xhci.c:122` | `#define XHC_TRB_TYPE_RESET_ENDPOINT` |
| `XHC_TRB_TYPE_SETUP` | macro | `drivers/xhci.c:114` | `#define XHC_TRB_TYPE_SETUP` |
| `XHC_TRB_TYPE_SET_DEQUEUE` | macro | `drivers/xhci.c:124` | `#define XHC_TRB_TYPE_SET_DEQUEUE` |
| `XHC_TRB_TYPE_STATUS` | macro | `drivers/xhci.c:116` | `#define XHC_TRB_TYPE_STATUS` |
| `XHC_TRB_TYPE_STOP_ENDPOINT` | macro | `drivers/xhci.c:123` | `#define XHC_TRB_TYPE_STOP_ENDPOINT` |
| `XHC_TRB_TYPE_TRANSFER_EVENT` | macro | `drivers/xhci.c:126` | `#define XHC_TRB_TYPE_TRANSFER_EVENT` |
| `XHC_TRT_IN` | macro | `drivers/xhci.c:928` | `#define XHC_TRT_IN` |
| `XHC_TRT_OUT` | macro | `drivers/xhci.c:927` | `#define XHC_TRT_OUT` |
| `xhc_address` | function | `drivers/xhci.c:1261` | `static int xhc_address(int index, int slot, int port, int speed)` |
| `xhc_alloc_all` | function | `drivers/xhci.c:1494` | `static int xhc_alloc_all(unsigned max_slots)` |
| `xhc_arm_link` | function | `drivers/xhci.c:465` | `static void xhc_arm_link(void)` |
| `xhc_arm_link_trb` | function | `drivers/xhci.c:458` | `static void xhc_arm_link_trb(xhc_trb_t *ring, unsigned gen)` |
| `xhc_cmd_maybe_arm` | function | `drivers/xhci.c:483` | `static void xhc_cmd_maybe_arm(void)` |
| `xhc_cmd_ring_doorbell` | function | `drivers/xhci.c:506` | `static void xhc_cmd_ring_doorbell(void)` |
| `xhc_cmd_run` | function | `drivers/xhci.c:709` | `static int xhc_cmd_run(unsigned type, unsigned long long param, unsigned slot,                   ...` |
| `xhc_cmd_run_ep` | function | `drivers/xhci.c:663` | `static int xhc_cmd_run_ep(unsigned type, unsigned long long param,                             un...` |
| `xhc_cmd_slot` | function | `drivers/xhci.c:494` | `static xhc_trb_t *xhc_cmd_slot(void)` |
| `xhc_cmd_wrap` | function | `drivers/xhci.c:477` | `static void xhc_cmd_wrap(void)` |
| `xhc_configure_endpoint` | function | `drivers/xhci.c:1100` | `int xhc_configure_endpoint(int index, int ep_index, int ep_addr, int ep_type,                    ...` |
| `xhc_control` | function | `drivers/xhci.c:1048` | `int xhc_control(int index, const unsigned char setup[8], void *data,                 unsigned len...` |
| `xhc_control_stage` | function | `drivers/xhci.c:979` | `static int xhc_control_stage(int index, const unsigned char setup[8],                            ...` |
| `xhc_counters` | function | `drivers/xhci.c:1790` | `void xhc_counters(xhc_counters_t *out)` |
| `xhc_dci` | function | `drivers/xhci.c:1093` | `static int xhc_dci(int ep_addr)` |
| `xhc_dev_alloc` | function | `drivers/xhci.c:833` | `static int xhc_dev_alloc(void)` |
| `xhc_dev_release` | function | `drivers/xhci.c:843` | `static void xhc_dev_release(int index)` |
| `xhc_device_count` | function | `drivers/xhci.c:806` | `int xhc_device_count(void)` |
| `xhc_device_info` | function | `drivers/xhci.c:814` | `int xhc_device_info(int index, xhc_dev_t *out)` |
| `xhc_devrec_t` | struct | `drivers/xhci.c:276` | `` |
| `xhc_enumerate` | function | `drivers/xhci.c:1358` | `int xhc_enumerate(int port)` |
| `xhc_enumerate_all` | function | `drivers/xhci.c:1444` | `int xhc_enumerate_all(void)` |
| `xhc_ep0_bump` | function | `drivers/xhci.c:971` | `static void xhc_ep0_bump(int index)` |
| `xhc_ep0_slot` | function | `drivers/xhci.c:959` | `static xhc_trb_t *xhc_ep0_slot(int index)` |
| `xhc_ep_b` | function | `drivers/xhci.c:296` | `static unsigned xhc_ep_b(void)` |
| `xhc_ep_command` | function | `drivers/xhci.c:719` | `static int xhc_ep_command(unsigned type, int slot, int dci)` |
| `xhc_ep_ctx` | function | `drivers/xhci.c:404` | `static unsigned char *xhc_ep_ctx(int slot, int ep)` |
| `xhc_ep_ctx_build` | function | `drivers/xhci.c:418` | `static void xhc_ep_ctx_build(unsigned char *ep, unsigned type,                              unsig...` |
| `xhc_ep_post` | function | `drivers/xhci.c:1162` | `static int xhc_ep_post(int index, int ep_index, void *buf, unsigned len)` |
| `xhc_evt_advance` | function | `drivers/xhci.c:559` | `static void xhc_evt_advance(void)` |
| `xhc_evt_next` | function | `drivers/xhci.c:535` | `static xhc_trb_t *xhc_evt_next(void)` |
| `xhc_evt_trb_ptr` | function | `drivers/xhci.c:552` | `static xhc_trb_t *xhc_evt_trb_ptr(xhc_trb_t *ev)` |
| `xhc_flush` | function | `drivers/xhci.c:386` | `static void xhc_flush(const void *p, unsigned long len)` |
| `xhc_free_all` | function | `drivers/xhci.c:1464` | `static void xhc_free_all(void)` |
| `xhc_get32` | function | `drivers/xhci.c:334` | `static unsigned xhc_get32(const unsigned char *base, unsigned off)` |
| `xhc_get_config_desc` | function | `drivers/xhci.c:1333` | `static int xhc_get_config_desc(int index, unsigned char *buf, unsigned *len)` |
| `xhc_get_device_desc` | function | `drivers/xhci.c:1316` | `static int xhc_get_device_desc(int index, unsigned char *buf)` |
| `xhc_got` | function | `drivers/xhci.c:1197` | `static int xhc_got(int token)` |
| `xhc_idle` | function | `drivers/xhci.c:393` | `static void xhc_idle(unsigned spin)` |
| `xhc_in_ep` | function | `drivers/xhci.c:413` | `static unsigned char *xhc_in_ep(int ci)` |
| `xhc_in_slot` | function | `drivers/xhci.c:409` | `static unsigned char *xhc_in_slot(void)` |
| `xhc_info` | function | `drivers/xhci.c:1798` | `int xhc_info(unsigned *version, unsigned *slots, unsigned *ports,              unsigned *caplength)` |
| `xhc_init` | function | `drivers/xhci.c:1658` | `int xhc_init(void)` |
| `xhc_inl` | function | `drivers/xhci.c:1458` | `static unsigned xhc_inl(unsigned short port)` |
| `xhc_now_ms` | function | `drivers/xhci.c:375` | `static unsigned long xhc_now_ms(void)` |
| `xhc_op_read32` | function | `drivers/xhci.c:359` | `static unsigned xhc_op_read32(unsigned off)` |
| `xhc_op_write32` | function | `drivers/xhci.c:363` | `static void xhc_op_write32(unsigned off, unsigned val)` |
| `xhc_open_interface` | function | `drivers/xhci.c:863` | `int xhc_open_interface(int index, unsigned cls, unsigned sub, unsigned proto,                    ...` |
| `xhc_outl` | function | `drivers/xhci.c:1454` | `static void xhc_outl(unsigned short port, unsigned val)` |
| `xhc_pending_claim` | function | `drivers/xhci.c:586` | `static int xhc_pending_claim(xhc_trb_t *trb)` |
| `xhc_pending_claim_len` | function | `drivers/xhci.c:570` | `static int xhc_pending_claim_len(xhc_trb_t *trb, unsigned len)` |
| `xhc_pending_drop` | function | `drivers/xhci.c:590` | `static void xhc_pending_drop(int token)` |
| `xhc_pending_t` | struct | `drivers/xhci.c:264` | `` |
| `xhc_poll` | function | `drivers/xhci.c:595` | `int xhc_poll(void)` |
| `xhc_poll_token` | function | `drivers/xhci.c:1252` | `int xhc_poll_token(int token)` |
| `xhc_poll_token_limit` | function | `drivers/xhci.c:1233` | `int xhc_poll_token_limit(int token, unsigned budget_ms)` |
| `xhc_port_count` | function | `drivers/xhci.c:749` | `int xhc_port_count(void)` |
| `xhc_port_reset` | function | `drivers/xhci.c:776` | `int xhc_port_reset(int port)` |
| `xhc_port_state` | function | `drivers/xhci.c:753` | `int xhc_port_state(int port, xhc_port_t *out)` |
| `xhc_probe_note` | function | `drivers/xhci.c:1794` | `const char *xhc_probe_note(void)` |
| `xhc_put16` | function | `drivers/xhci.c:345` | `static void xhc_put16(unsigned char *base, unsigned off, unsigned val)` |
| `xhc_put32` | function | `drivers/xhci.c:327` | `static void xhc_put32(unsigned char *base, unsigned off, unsigned val)` |
| `xhc_put64` | function | `drivers/xhci.c:339` | `static void xhc_put64(unsigned char *base, unsigned off,                       unsigned long long...` |
| `xhc_puttrb` | function | `drivers/xhci.c:350` | `static void xhc_puttrb(xhc_trb_t *trb, unsigned long long param,                        unsigned ...` |
| `xhc_reset_endpoint` | function | `drivers/xhci.c:723` | `int xhc_reset_endpoint(int index, int ep_index)` |
| `xhc_ring_maybe_arm` | function | `drivers/xhci.c:949` | `static void xhc_ring_maybe_arm(xhc_ring_t *ring)` |
| `xhc_ring_t` | struct | `drivers/xhci.c:250` | `` |
| `xhc_ring_wrap` | function | `drivers/xhci.c:936` | `static void xhc_ring_wrap(int index, xhc_ring_t *ring, int ep)` |
| `xhc_run_read32` | function | `drivers/xhci.c:371` | `static unsigned xhc_run_read32(unsigned off)` |
| `xhc_run_write32` | function | `drivers/xhci.c:367` | `static void xhc_run_write32(unsigned off, unsigned val)` |
| `xhc_setup_data` | function | `drivers/xhci.c:1082` | `static void xhc_setup_data(unsigned char *setup, unsigned char type,                            u...` |
| `xhc_setup_nodata` | function | `drivers/xhci.c:1069` | `static void xhc_setup_nodata(unsigned char *setup, unsigned char type,                           ...` |
| `xhc_slot_ctx` | function | `drivers/xhci.c:400` | `static unsigned char *xhc_slot_ctx(int slot)` |
| `xhc_slot_ctx_build` | function | `drivers/xhci.c:439` | `static void xhc_slot_ctx_build(unsigned char *sc, unsigned speed,                                ...` |
| `xhc_slot_doorbell` | function | `drivers/xhci.c:519` | `static void xhc_slot_doorbell(int slot, int ep)` |
| `xhc_start` | function | `drivers/xhci.c:1593` | `static int xhc_start(unsigned contexts)` |
| `xhc_status` | function | `drivers/xhci.c:654` | `static int xhc_status(int token)` |
| `xhc_stride` | function | `drivers/xhci.c:300` | `static unsigned xhc_stride(void)` |
| `xhc_transfer` | function | `drivers/xhci.c:1202` | `int xhc_transfer(int index, int ep_index, void *buf, unsigned len, int *got)` |
| `xhc_transfer_async` | function | `drivers/xhci.c:1222` | `int xhc_transfer_async(int index, int ep_index, void *buf, unsigned len)` |
| `xhc_trb_t` | struct | `drivers/xhci.c:239` | `` |
| `xhc_wait` | function | `drivers/xhci.c:638` | `static int xhc_wait(int token, unsigned budget_ms)` |
| `EXT4_ENCRYPT_FL` | macro | `fs/ext4.c:27` | `#define EXT4_ENCRYPT_FL` |
| `EXT4_EXTENTS_FL` | macro | `fs/ext4.c:25` | `#define EXT4_EXTENTS_FL` |
| `EXT4_EXT_MAGIC` | macro | `fs/ext4.c:20` | `#define EXT4_EXT_MAGIC` |
| `EXT4_EXT_UNINIT` | macro | `fs/ext4.c:29` | `#define EXT4_EXT_UNINIT` |
| `EXT4_INDEX_FL` | macro | `fs/ext4.c:26` | `#define EXT4_INDEX_FL` |
| `EXT4_INLINE_FL` | macro | `fs/ext4.c:28` | `#define EXT4_INLINE_FL` |
| `EXT4_MAGIC` | macro | `fs/ext4.c:19` | `#define EXT4_MAGIC` |
| `EXT4_MBR_LINUX` | macro | `fs/ext4.c:30` | `#define EXT4_MBR_LINUX` |
| `EXT4_SUPER_OFF` | macro | `fs/ext4.c:18` | `#define EXT4_SUPER_OFF` |
| `EXT4_S_IFDIR` | macro | `fs/ext4.c:23` | `#define EXT4_S_IFDIR` |
| `EXT4_S_IFLNK` | macro | `fs/ext4.c:24` | `#define EXT4_S_IFLNK` |
| `EXT4_S_IFMT` | macro | `fs/ext4.c:21` | `#define EXT4_S_IFMT` |
| `EXT4_S_IFREG` | macro | `fs/ext4.c:22` | `#define EXT4_S_IFREG` |
| `ext4_list` | function | `fs/ext4.c:485` | `int ext4_list(const char *imgpath, const char *dirpath,               char names[][EXT4_NAME_MAX ...` |
| `ext4_vfs_close` | function | `fs/ext4.c:675` | `int ext4_vfs_close(void *handle)` |
| `ext4_vfs_fstat` | function | `fs/ext4.c:680` | `int ext4_vfs_fstat(void *handle, unsigned long *size_out)` |
| `ext4_vfs_open` | function | `fs/ext4.c:585` | `int ext4_vfs_open(const char *path, int mode, void **handle)` |
| `ext4_vfs_read` | function | `fs/ext4.c:626` | `int ext4_vfs_read(void *handle, void *buf, unsigned long pos,                   unsigned long len)` |
| `ext4_vfs_readdir` | function | `fs/ext4.c:696` | `static int ext4_vfs_readdir(const char *path, vfs_dirent_t *ents,         int cap)` |
| `ext4_vfs_truncate` | function | `fs/ext4.c:687` | `int ext4_vfs_truncate(void *handle, unsigned long size)` |
| `ext4_vfs_write` | function | `fs/ext4.c:666` | `int ext4_vfs_write(void *handle, const void *buf, unsigned long pos,                    unsigned ...` |
| `ext_dev_base` | function | `fs/ext4.c:791` | `long ext_dev_base(void)` |
| `ext_file_block` | function | `fs/ext4.c:464` | `static int ext_file_block(const fsimg_t *img, const ext_geo_t *g,                           const...` |
| `ext_geo_t` | struct | `fs/ext4.c:44` | `` |
| `ext_ino_t` | struct | `fs/ext4.c:115` | `` |
| `ext_inode_off` | function | `fs/ext4.c:92` | `static int ext_inode_off(const fsimg_t *img, const ext_geo_t *g,                          unsigne...` |
| `ext_ld16` | function | `fs/ext4.c:32` | `static unsigned ext_ld16(const unsigned char *p)` |
| `ext_ld32` | function | `fs/ext4.c:36` | `static unsigned long ext_ld32(const unsigned char *p)` |
| `ext_map` | function | `fs/ext4.c:171` | `static int ext_map(const fsimg_t *img, const ext_geo_t *g,                    const unsigned char...` |
| `ext_map_down` | function | `fs/ext4.c:168` | `static int ext_map_down(const fsimg_t *img, const ext_geo_t *g, const unsigned char *root, unsigned nent, unsigned...` |
| `ext_map_leaf` | function | `fs/ext4.c:211` | `static int ext_map_leaf(const fsimg_t *img, const ext_geo_t *g,                         const uns...` |
| `ext_mbr_entry` | function | `fs/ext4.c:745` | `static int ext_mbr_entry(const unsigned char *mbr, int idx,                          unsigned lon...` |
| `ext_parse_sb` | function | `fs/ext4.c:55` | `static int ext_parse_sb(const fsimg_t *img, ext_geo_t *g)` |
| `ext_read_inode` | function | `fs/ext4.c:122` | `static int ext_read_inode(const fsimg_t *img, const ext_geo_t *g,                           unsig...` |
| `ext_resolve` | function | `fs/ext4.c:356` | `static int ext_resolve(const fsimg_t *img, const ext_geo_t *g,                        const char ...` |
| `ext_scan_dev` | function | `fs/ext4.c:770` | `static int ext_scan_dev(unsigned long total_sec,                         unsigned long *base_out)` |
| `ext_split` | function | `fs/ext4.c:580` | `static int ext_split(const char *path, char *img, char *extp)` |
| `only` | function | `fs/ext4.c:352` | `* listings only ('.' skipped, '..' refused). "" or "/" is root (2). */ static int ext_file_block(const fsimg_t *img...` |
| `FAT_MBR_COUNT_OFF` | macro | `fs/fat32.c:117` | `#define FAT_MBR_COUNT_OFF` |
| `FAT_MBR_ENTRY_SZ` | macro | `fs/fat32.c:113` | `#define FAT_MBR_ENTRY_SZ` |
| `FAT_MBR_GPT_PROT` | macro | `fs/fat32.c:118` | `#define FAT_MBR_GPT_PROT` |
| `FAT_MBR_NENTRY` | macro | `fs/fat32.c:114` | `#define FAT_MBR_NENTRY` |
| `FAT_MBR_SIG_OFF` | macro | `fs/fat32.c:111` | `#define FAT_MBR_SIG_OFF` |
| `FAT_MBR_START_OFF` | macro | `fs/fat32.c:116` | `#define FAT_MBR_START_OFF` |
| `FAT_MBR_TAB_OFF` | macro | `fs/fat32.c:112` | `#define FAT_MBR_TAB_OFF` |
| `FAT_MBR_TYPE_OFF` | macro | `fs/fat32.c:115` | `#define FAT_MBR_TYPE_OFF` |
| `fat32_list` | function | `fs/fat32.c:421` | `int fat32_list(const char *imgpath, const char *dirpath,                char names[][FAT32_NAME_M...` |
| `fat32_vfs_close` | function | `fs/fat32.c:630` | `int fat32_vfs_close(void *handle)` |
| `fat32_vfs_fstat` | function | `fs/fat32.c:635` | `int fat32_vfs_fstat(void *handle, unsigned long *size_out)` |
| `fat32_vfs_open` | function | `fs/fat32.c:496` | `int fat32_vfs_open(const char *path, int mode, void **handle)` |
| `fat32_vfs_read` | function | `fs/fat32.c:581` | `int fat32_vfs_read(void *handle, void *buf, unsigned long pos,                    unsigned long len)` |
| `fat32_vfs_truncate` | function | `fs/fat32.c:642` | `int fat32_vfs_truncate(void *handle, unsigned long size)` |
| `fat32_vfs_write` | function | `fs/fat32.c:621` | `int fat32_vfs_write(void *handle, const void *buf, unsigned long pos,                     unsigne...` |
| `fat_badch` | function | `fs/fat32.c:262` | `static int fat_badch(char c)` |
| `fat_clus_ok` | function | `fs/fat32.c:224` | `static int fat_clus_ok(const fat_geo_t *g, unsigned c)` |
| `fat_dev_base` | function | `fs/fat32.c:192` | `long fat_dev_base(void)` |

Next: [SYMBOLS_p3.md](SYMBOLS_p3.md)
