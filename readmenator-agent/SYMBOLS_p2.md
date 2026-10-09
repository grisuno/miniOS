# Symbols (page 2 of 26)
Previous: [SYMBOLS.md](SYMBOLS.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `usbhid_keyboard_present` | function | `drivers/usbhid.c:256` | `int usbhid_keyboard_present(void)` |
| `usbhid_mouse_decode` | function | `drivers/usbhid.c:241` | `void usbhid_mouse_decode(const unsigned char prev[HID_MOUSE_REPORT_LEN],                         ...` |
| `usbhid_mouse_present` | function | `drivers/usbhid.c:263` | `int usbhid_mouse_present(void)` |
| `usbhid_poll` | function | `drivers/usbhid.c:499` | `int usbhid_poll(void)` |
| `usbhid_poll_keyboard` | function | `drivers/usbhid.c:483` | `int usbhid_poll_keyboard(void)` |
| `usbhid_poll_mouse` | function | `drivers/usbhid.c:491` | `int usbhid_poll_mouse(void)` |
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
| `fat_entry` | function | `fs/fat32.c:231` | `static int fat_entry(const fsimg_t *img, const fat_geo_t *g,                      unsigned clus, ...` |
| `fat_eoc` | function | `fs/fat32.c:248` | `static int fat_eoc(unsigned v)` |
| `fat_geo_t` | struct | `fs/fat32.c:51` | `` |
| `fat_img_open` | function | `fs/fat32.c:29` | `static int fat_img_open(const char *resolved, fsimg_t *img)` |
| `fat_ld16` | function | `fs/fat32.c:18` | `static unsigned fat_ld16(const unsigned char *p)` |
| `fat_ld32` | function | `fs/fat32.c:22` | `static unsigned fat_ld32(const unsigned char *p)` |
| `fat_match` | function | `fs/fat32.c:305` | `static int fat_match(const unsigned char *de, const char name8[8],                      const cha...` |
| `fat_mbr_is_fat` | function | `fs/fat32.c:120` | `static int fat_mbr_is_fat(unsigned char t)` |
| `fat_parse_bpb` | function | `fs/fat32.c:62` | `static int fat_parse_bpb(const fsimg_t *img, fat_geo_t *g)` |
| `fat_qword` | function | `fs/fat32.c:274` | `static int fat_qword(const char *q, unsigned qlen, char name8[8],                      char ext3[3])` |
| `fat_resolve` | function | `fs/fat32.c:321` | `static int fat_resolve(const fsimg_t *img, const fat_geo_t *g,                        const char ...` |
| `fat_seek` | function | `fs/fat32.c:556` | `static int fat_seek(const fat32_handle_t *h, unsigned long pos,                     unsigned *clu...` |
| `fat_views` | function | `fs/fat32.c:537` | `static void fat_views(const fat32_handle_t *h, fsimg_t *img,                       fat_geo_t *g)` |
| `fsimg_dev_read` | function | `fs/fsimg.c:72` | `static int fsimg_dev_read(const fsimg_t *img, unsigned long off,                           void *...` |
| `fsimg_open_dev` | function | `fs/fsimg.c:51` | `int fsimg_open_dev(unsigned long base_lba, unsigned long nsec,                    fsimg_t *img)` |
| `fsimg_open_file` | function | `fs/fsimg.c:15` | `int fsimg_open_file(const char *resolved, fsimg_t *img)` |
| `fsimg_read` | function | `fs/fsimg.c:96` | `int fsimg_read(const fsimg_t *img, unsigned long off, void *buf,                unsigned long len)` |
| `fsimg_split` | function | `fs/fsimg.c:112` | `int fsimg_split(const char *path, char *left, unsigned llen,                 char *right, unsigne...` |
| `entry` | function | `fs/kfile.c:355` | `* directory with a volatile ramdisk entry (the kfopen misroute class) or  * need a copy+delete th...` |
| `fs_drop` | function | `fs/kfile.c:70` | `static inline void fs_drop(irqflags_t flags)` |
| `fs_rename_on_minifs` | function | `fs/kfile.c:336` | `static int fs_rename_on_minifs(const char *dst)` |
| `fs_take` | function | `fs/kfile.c:66` | `static inline void fs_take(irqflags_t *flags)` |
| `kevent_create` | function | `fs/kfile.c:148` | `KFILE *kevent_create(unsigned long long initval, int semaphore)` |
| `kevent_read` | function | `fs/kfile.c:163` | `long kevent_read(KFILE *f, unsigned long long *out)` |
| `kevent_readable` | function | `fs/kfile.c:199` | `int kevent_readable(KFILE *f)` |
| `kevent_writable` | function | `fs/kfile.c:204` | `int kevent_writable(KFILE *f)` |
| `kfclose` | function | `fs/kfile.c:397` | `int kfclose(KFILE *f)` |
| `kfflush` | function | `fs/kfile.c:641` | `int kfflush(KFILE *f)` |
| `kfgetc` | function | `fs/kfile.c:442` | `int kfgetc(KFILE *f)` |
| `kfgets` | function | `fs/kfile.c:483` | `char *kfgets(char *buf, int size, KFILE *f)` |
| `kfile_corrupt` | function | `fs/kfile.c:33` | `static int kfile_corrupt(const KFILE *f)` |
| `kfile_stderr` | function | `fs/kfile.c:17` | `KFILE *kfile_stderr(void)` |
| `kfile_stdin` | function | `fs/kfile.c:15` | `KFILE *kfile_stdin(void)` |
| `kfile_stdout` | function | `fs/kfile.c:16` | `KFILE *kfile_stdout(void)` |
| `kfopen` | function | `fs/kfile.c:239` | `KFILE *kfopen(const char *path, const char *mode)` |
| `kfputc` | function | `fs/kfile.c:673` | `int kfputc(int c, KFILE *f)` |
| `kfputs` | function | `fs/kfile.c:667` | `int kfputs(const char *s, KFILE *f)` |
| `kfread` | function | `fs/kfile.c:504` | `unsigned long kfread(void *ptr, unsigned long size, unsigned long n, KFILE *f)` |
| `kfseek` | function | `fs/kfile.c:616` | `int kfseek(KFILE *f, long offset, int whence)` |
| `kftell` | function | `fs/kfile.c:637` | `long kftell(KFILE *f)` |
| `kfungetc` | function | `fs/kfile.c:497` | `int kfungetc(int c, KFILE *f)` |
| `kfwrite` | function | `fs/kfile.c:550` | `unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long n, KFILE *f)` |
| `kpipe_grow` | function | `fs/kfile.c:216` | `static int kpipe_grow(pipe_ring_t *ring)` |
| `kpipe_is_write_end` | function | `fs/kfile.c:209` | `int kpipe_is_write_end(KFILE *f)` |
| `kpipe_pair` | function | `fs/kfile.c:78` | `int kpipe_pair(KFILE **rend_out, KFILE **wend_out)` |
| `kpipe_state` | function | `fs/kfile.c:130` | `int kpipe_state(KFILE *f, unsigned *avail, unsigned *space, int *wopen, int *ropen)` |
| `krewind` | function | `fs/kfile.c:678` | `void krewind(KFILE *f)` |
| `recovery` | function | `fs/kfile.c:28` | `* halts the machine with no recovery (the DOOM ABI-drift black screen),  * so every public KFILE ...` |
| `DE_NAME` | macro | `fs/minifs.c:13` | `#define DE_NAME(de)` |
| `DE_NAME_W` | macro | `fs/minifs.c:14` | `#define DE_NAME_W(de)` |
| `MINIFS_INODE_CRC_OFF` | macro | `fs/minifs.c:130` | `#define MINIFS_INODE_CRC_OFF` |
| `blk_free` | function | `fs/minifs.c:100` | `static void blk_free(unsigned char *b)` |
| `blk_new` | function | `fs/minifs.c:22` | `static unsigned char *blk_new(void);` |
| `blocks` | function | `fs/minifs.c:555` | `* blocks (self-protection);` |
| `bm_clear` | function | `fs/minifs.c:209` | `static void bm_clear(unsigned char *bm, unsigned int bit)` |
| `bm_set` | function | `fs/minifs.c:205` | `static void bm_set(unsigned char *bm, unsigned int bit)` |
| `bm_test` | function | `fs/minifs.c:201` | `static int bm_test(unsigned char *bm, unsigned int bit)` |
| `div_round_up` | function | `fs/minifs.c:83` | `static unsigned int div_round_up(unsigned int n, unsigned int d)` |
| `first` | function | `fs/minifs.c:556` | `* keep the first (oldest) snapshot. */ void minifs_journal_touch(unsigned int phys)` |
| `fs_inode_check` | function | `fs/minifs.c:142` | `static int fs_inode_check(const MiniFSInode *in)` |
| `fs_inode_free_all_blocks` | function | `fs/minifs.c:364` | `static void fs_inode_free_all_blocks(MiniFSInode *inode)` |
| `fs_inode_set_block` | function | `fs/minifs.c:289` | `static int fs_inode_set_block(MiniFSInode *inode, unsigned int logblk,                           ...` |
| `fs_namecmp` | function | `fs/minifs.c:683` | `static int fs_namecmp(const char *a, unsigned char alen, const char *b)` |
| `fs_read_inode` | function | `fs/minifs.c:167` | `static int fs_read_inode(unsigned int num, MiniFSInode *out)` |
| `fs_write_inode` | function | `fs/minifs.c:179` | `static int fs_write_inode(unsigned int num, const MiniFSInode *in)` |
| `fs_write_super` | function | `fs/minifs.c:107` | `static int fs_write_super(void)` |
| `instead` | function | `fs/minifs.c:127` | `* kernel stored the same crc at offset 76 instead (byte order the old  * write path used), so a r...` |
| `journal_load_super` | function | `fs/minifs.c:446` | `static void journal_load_super(void)` |
| `journal_save_entries` | function | `fs/minifs.c:478` | `static void journal_save_entries(void)` |
| `journal_save_super` | function | `fs/minifs.c:464` | `static void journal_save_super(unsigned int state)` |
| `minifs_access` | function | `fs/minifs.c:1395` | `int minifs_access(const char *path)` |
| `minifs_alloc_block` | function | `fs/minifs.c:215` | `int minifs_alloc_block(void)` |
| `minifs_alloc_inode` | function | `fs/minifs.c:240` | `int minifs_alloc_inode(void)` |
| `minifs_compress` | function | `fs/minifs.c:35` | `unsigned int minifs_compress(const void *src, unsigned int src_len,                              ...` |
| `minifs_crc16` | function | `fs/minifs.c:57` | `static unsigned short minifs_crc16(const void *data, unsigned int len)` |
| `minifs_crc32` | function | `fs/minifs.c:69` | `static unsigned int minifs_crc32(const void *data, unsigned int len)` |
| `minifs_create` | function | `fs/minifs.c:974` | `int minifs_create(const char *path, unsigned short mode)` |
| `minifs_decompress` | function | `fs/minifs.c:46` | `unsigned int minifs_decompress(const void *src, unsigned int src_len,                            ...` |
| `minifs_dir_add_entry` | function | `fs/minifs.c:722` | `int minifs_dir_add_entry(int dir_ino, const char *name, int child_ino,                           ...` |
| `minifs_dir_lookup` | function | `fs/minifs.c:692` | `int minifs_dir_lookup(int dir_ino, const char *name)` |
| `minifs_dir_read` | function | `fs/minifs.c:891` | `int minifs_dir_read(int dir_ino, int index, MiniFSDirEntry *out, char *name_out)` |
| `minifs_dir_remove_entry` | function | `fs/minifs.c:860` | `int minifs_dir_remove_entry(int dir_ino, const char *name)` |
| `minifs_file_close` | function | `fs/minifs.c:1597` | `int minifs_file_close(MiniFSFile *f)` |
| `minifs_file_open` | function | `fs/minifs.c:1583` | `MiniFSFile *minifs_file_open(int inode_num, int flags)` |
| `minifs_free_block` | function | `fs/minifs.c:232` | `void minifs_free_block(unsigned int block)` |
| `minifs_free_inode` | function | `fs/minifs.c:252` | `void minifs_free_inode(int num)` |
| `minifs_get_lba_start` | function | `fs/minifs.c:1409` | `unsigned int minifs_get_lba_start(void)` |
| `minifs_get_total_blocks` | function | `fs/minifs.c:1604` | `unsigned int minifs_get_total_blocks(void)` |
| `minifs_init` | function | `fs/minifs.c:1401` | `void minifs_init(void)` |
| `minifs_inode_alloc_block` | function | `fs/minifs.c:343` | `int minifs_inode_alloc_block(MiniFSInode *inode, unsigned int logblk)` |
| `minifs_inode_get_block` | function | `fs/minifs.c:260` | `int minifs_inode_get_block(MiniFSInode *inode, unsigned int logblk,                            un...` |
| `minifs_is_mounted` | function | `fs/minifs.c:1410` | `int minifs_is_mounted(void)` |
| `minifs_journal_abort` | function | `fs/minifs.c:531` | `void minifs_journal_abort(void)` |
| `minifs_journal_add_block` | function | `fs/minifs.c:504` | `void minifs_journal_add_block(unsigned int block)` |
| `minifs_journal_begin` | function | `fs/minifs.c:495` | `void minifs_journal_begin(unsigned int txn_id)` |
| `minifs_journal_clear` | function | `fs/minifs.c:521` | `void minifs_journal_clear(void)` |
| `minifs_journal_commit` | function | `fs/minifs.c:511` | `int minifs_journal_commit(unsigned int txn_id)` |
| `minifs_journal_recover` | function | `fs/minifs.c:597` | `void minifs_journal_recover(void)` |
| `minifs_journal_touch` | function | `fs/minifs.c:16` | `void minifs_journal_touch(unsigned int phys);` |
| `minifs_mkdir` | function | `fs/minifs.c:1027` | `int minifs_mkdir(const char *path, unsigned short mode)` |
| `minifs_mount` | function | `fs/minifs.c:1418` | `int minifs_mount(void)` |
| `minifs_read` | function | `fs/minifs.c:1216` | `int minifs_read(int inode_num, void *buf, unsigned int offset, unsigned int len)` |
| `minifs_rename` | function | `fs/minifs.c:1144` | `int minifs_rename(const char *oldpath, const char *newpath)` |
| `minifs_resolve_path` | function | `fs/minifs.c:941` | `int minifs_resolve_path(const char *path)` |
| `minifs_rmdir` | function | `fs/minifs.c:1176` | `int minifs_rmdir(const char *path)` |
| `minifs_split_parent` | function | `fs/minifs.c:1119` | `static int minifs_split_parent(const char *path, char *parent_out,                               ...` |
| `minifs_stat` | function | `fs/minifs.c:1391` | `int minifs_stat(int inode_num, MiniFSInode *out)` |
| `minifs_sync` | function | `fs/minifs.c:1568` | `int minifs_sync(void)` |
| `minifs_truncate` | function | `fs/minifs.c:1374` | `int minifs_truncate(int inode_num, unsigned int new_size)` |
| `minifs_unlink` | function | `fs/minifs.c:1076` | `int minifs_unlink(const char *path)` |
| `minifs_usage` | function | `fs/minifs.c:1609` | `void minifs_usage(unsigned int *free_b, unsigned int *total_b,                   unsigned int *fr...` |
| `minifs_write` | function | `fs/minifs.c:1287` | `int minifs_write(int inode_num, const void *buf, unsigned int offset,                  unsigned i...` |
| `returns` | function | `fs/minifs.c:92` | `* overflowed the slot and smashed returns (measured ring-0 #UD on  * lua->lua->cp). Every scratch...` |
| `roundup4` | function | `fs/minifs.c:81` | `static unsigned int roundup4(unsigned int v)` |
| `match` | function | `fs/pcache.c:230` | `* a phys match (owned, ref dropped unless already zero), 0  * otherwise. */ int pcache_put_if(int...` |
| `pcache_data` | function | `fs/pcache.c:285` | `unsigned char *pcache_data(int slot)` |
| `pcache_get` | function | `fs/pcache.c:71` | `int pcache_get(int ino, unsigned index, int *is_new)` |
| `pcache_init` | function | `fs/pcache.c:42` | `void pcache_init(void)` |
| `pcache_invalidate_ino` | function | `fs/pcache.c:299` | `void pcache_invalidate_ino(int ino)` |
| `pcache_lookup` | function | `fs/pcache.c:54` | `int pcache_lookup(int ino, unsigned index)` |
| `pcache_mark_dirty` | function | `fs/pcache.c:291` | `void pcache_mark_dirty(int slot)` |
| `pcache_owns_phys` | function | `fs/pcache.c:277` | `int pcache_owns_phys(unsigned long phys)` |
| `pcache_publish` | function | `fs/pcache.c:128` | `int pcache_publish(int ino, unsigned index, const unsigned char *data)` |
| `pcache_put` | function | `fs/pcache.c:179` | `void pcache_put(int slot)` |
| `pcache_ref` | function | `fs/pcache.c:192` | `int pcache_ref(int ino, unsigned index)` |
| `pcache_ref_if` | function | `fs/pcache.c:255` | `int pcache_ref_if(int ino, unsigned index, unsigned long phys)` |
| `pcache_slot_phys` | function | `fs/pcache.c:222` | `static unsigned long pcache_slot_phys(int slot)` |
| `pcache_slot_t` | struct | `fs/pcache.c:17` | `` |
| `pcache_stats` | function | `fs/pcache.c:314` | `void pcache_stats(unsigned long *pages_out, unsigned long *hits_out,         unsigned long *miss_...` |
| `pcache_unmap` | function | `fs/pcache.c:216` | `void pcache_unmap(int ino, unsigned index)` |
| `RDSuper` | struct | `fs/ramdisk.c:26` | `` |

Next: [SYMBOLS_p3.md](SYMBOLS_p3.md)
