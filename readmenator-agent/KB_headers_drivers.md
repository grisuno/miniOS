# Subsystem: headers_drivers

## headers/drivers/kbd.h
- Doc: Keyboard layout: US qwerty (default) or Spanish (Spain) qwerty.
- Layer: infrastructure
- Language: h
- Symbols:
  - `kbd_available` (function, line 9) `int kbd_available(void);`
  - `kbd_read` (function, line 10) `int kbd_read(void);`
  - `kbd_feed_scancode` (function, line 11) `int kbd_feed_scancode(unsigned char sc);`
  - `kbd_reset_for_shell` (function, line 12) `void kbd_reset_for_shell(void);`
  - `kbd_get_layout` (function, line 15) `int kbd_get_layout(void);`
  - `kbd_set_layout` (function, line 16) `void kbd_set_layout(int layout);`
  - `kbd_toggle_layout` (function, line 17) `void kbd_toggle_layout(void);`
  - `kbd_q_empty` (function, line 27) `int kbd_q_empty(void);`
  - `kbd_q_pop` (function, line 28) `int kbd_q_pop(void);`
  - `kbd_q_push` (function, line 29) `void kbd_q_push(unsigned char c);`
  - `kbd_drop_counts` (function, line 32) `void kbd_drop_counts(unsigned long *cooked, unsigned long *raw);`
  - `kbd_raw_mode_get` (function, line 35) `int kbd_raw_mode_get(void);`
  - `kbd_raw_mode_set` (function, line 36) `void kbd_raw_mode_set(int on);`
  - `kbd_raw_empty` (function, line 37) `int kbd_raw_empty(void);`
  - `kbd_raw_pop` (function, line 38) `int kbd_raw_pop(void);`
  - `kbd_raw_push_byte` (function, line 39) `void kbd_raw_push_byte(unsigned char c);`
  - `kbd_e0_get` (function, line 40) `int kbd_e0_get(void);`
  - `kbd_e0_set` (function, line 41) `void kbd_e0_set(int v);`
  - `kbd_flush_all` (function, line 42) `void kbd_flush_all(void);`
  - `kbd_raw_flush` (function, line 43) `void kbd_raw_flush(void);`
  - `kbd_sys_raw_filter` (function, line 50) `int kbd_sys_raw_filter(unsigned char sc);`
  - `KBD_H` (macro, line 2) `#define KBD_H`
  - `KBD_LAYOUT_EN` (macro, line 6) `#define KBD_LAYOUT_EN`
  - `KBD_LAYOUT_ES` (macro, line 7) `#define KBD_LAYOUT_ES`
- Imported by: `drivers/kbd.c`, `drivers/usbhid.c`, `kernel/console_in.c`, `kernel/exec.c`, `kernel/shell.c`, `kernel/syscalls.c`, `kernel/vga_fb.c`

## headers/drivers/modifiers.h
- Doc: Docstring: Unified modifier tracking for cooked and raw paths.
- Layer: infrastructure
- Language: h
- Symbols:
  - `modifier_state_t` (struct, line 5)
  - `modifier_keys_t` (struct, line 19)
  - `modifiers_init` (function, line 37) `static inline void modifiers_init(modifier_state_t *st)`
  - `modifiers_update` (function, line 54) `static inline int modifiers_update(const modifier_keys_t *keys,
                                 ...`
  - `modifiers_match` (function, line 92) `static inline int modifiers_match(const modifier_state_t *st, int mask)`
  - `MODIFIERS_H` (macro, line 2) `#define MODIFIERS_H`
  - `MOD_SHIFT` (macro, line 30) `#define MOD_SHIFT`
  - `MOD_CTRL` (macro, line 31) `#define MOD_CTRL`
  - `MOD_ALT` (macro, line 32) `#define MOD_ALT`
  - `MOD_ALTGR` (macro, line 33) `#define MOD_ALTGR`
  - `MOD_SUPER` (macro, line 34) `#define MOD_SUPER`
- Imported by: `drivers/kbd.c`, `drivers/usbhid.c`, `headers/wm_events.h`, `tests/test_modifiers.c`

## headers/drivers/mouse.h
- Doc: Docstring: mouse.h -- boundary of the PS/2 mouse device driver
- Layer: infrastructure
- Language: h
- Symbols:
  - `mouse_hw_init` (function, line 11) `void mouse_hw_init(void);`
  - `mouse_disable` (function, line 14) `void mouse_disable(void);`
  - `mouse_enable` (function, line 17) `void mouse_enable(void);`
  - `MOUSE_H` (macro, line 2) `#define MOUSE_H`
- Imported by: `drivers/mouse.c`, `kernel/sched.c`

## headers/drivers/nvme.h
- Layer: infrastructure
- Language: h
- Symbols:
  - `nvme_init` (function, line 4) `int nvme_init(void);`
  - `nvme_present` (function, line 5) `int nvme_present(void);`
  - `nvme_version` (function, line 6) `unsigned nvme_version(void);`
  - `nvme_note` (function, line 7) `const char *nvme_note(void);`
  - `nvme_sectors` (function, line 8) `unsigned long nvme_sectors(void);`
  - `nvme_read_sectors` (function, line 9) `int nvme_read_sectors(unsigned lba, unsigned count, void *buf);`
  - `DRIVERS_NVME_H` (macro, line 2) `#define DRIVERS_NVME_H`
- Imported by: `drivers/block.c`, `drivers/nvme.c`, `kernel/shell.c`

## headers/drivers/pci.h
- Doc: Docstring: drivers/pci.h -- PCI configuration-space access.
- Layer: infrastructure
- Language: h
- Symbols:
  - `pci_bdf_t` (struct, line 71)
  - `pci_cfg_read` (function, line 80) `static inline unsigned pci_cfg_read(unsigned bus, unsigned dev,
        unsigned func, unsigned r...`
  - `pci_cfg_write` (function, line 90) `static inline void pci_cfg_write(unsigned bus, unsigned dev,
        unsigned func, unsigned reg,...`
  - `pci_cfg_read8` (function, line 100) `static inline unsigned char pci_cfg_read8(unsigned bus, unsigned dev,
        unsigned func, unsi...`
  - `pci_cfg_write8` (function, line 109) `static inline void pci_cfg_write8(unsigned bus, unsigned dev,
        unsigned func, unsigned reg...`
  - `pci_present` (function, line 122) `static inline int pci_present(unsigned bus, unsigned dev, unsigned func,
        void (*outl)(uns...`
  - `xHCI` (function, line 134) `* base class: an xHCI (0x0C/0x03/0x30) would look for class 0x03, and a PCI
 * bridge (0x06/0x04)...`
  - `pci_is_multifunction` (function, line 152) `static inline int pci_is_multifunction(unsigned bus, unsigned dev,
        void (*outl)(unsigned ...`
  - `pci_find` (function, line 165) `static inline int pci_find(unsigned vendor, unsigned device,
        unsigned (*inl)(unsigned sho...`
  - `pci_find_class` (function, line 193) `static inline int pci_find_class(pci_bdf_t *out,
        unsigned cls, unsigned subclass, unsigne...`
  - `pci_bar_count` (function, line 248) `static inline unsigned pci_bar_count(unsigned bus, unsigned dev, unsigned func,
        void (*ou...`
  - `pci_bar_is_io` (function, line 263) `static inline int pci_bar_is_io(unsigned bus, unsigned dev, unsigned func,
        unsigned bar,
...`
  - `pci_bar_is_64bit` (function, line 274) `static inline int pci_bar_is_64bit(unsigned bus, unsigned dev, unsigned func,
        unsigned ba...`
  - `pci_bar_ctz32` (function, line 284) `static inline unsigned pci_bar_ctz32(unsigned val)`
  - `pci_bar_size_from_mask` (function, line 315) `static inline unsigned long long pci_bar_size_from_mask(unsigned long long mask)`
  - `pci_bar_size` (function, line 346) `static inline unsigned long long pci_bar_size(unsigned bus, unsigned dev,
        unsigned func, ...`
  - `pci_bar_relocate` (function, line 382) `static inline int pci_bar_relocate(unsigned bus, unsigned dev, unsigned func,
        unsigned ba...`
  - `pci_bar_base` (function, line 406) `static inline unsigned long long pci_bar_base(unsigned bus, unsigned dev,
        unsigned func, ...`
  - `pci_bar_restore` (function, line 424) `static inline void pci_bar_restore(unsigned bus, unsigned dev,
        unsigned func, unsigned ba...`
  - `DRIVERS_PCI_H` (macro, line 11) `#define DRIVERS_PCI_H`
  - `PCI_CFG_ADDR` (macro, line 13) `#define PCI_CFG_ADDR`
  - `PCI_CFG_DATA` (macro, line 14) `#define PCI_CFG_DATA`
  - `PCI_MAX_BUS` (macro, line 15) `#define PCI_MAX_BUS`
  - `PCI_MAX_DEV` (macro, line 16) `#define PCI_MAX_DEV`
  - `PCI_MAX_FUNC` (macro, line 17) `#define PCI_MAX_FUNC`
  - `PCI_REG_VENDOR_ID` (macro, line 20) `#define PCI_REG_VENDOR_ID`
  - `PCI_REG_COMMAND` (macro, line 21) `#define PCI_REG_COMMAND`
  - `PCI_REG_CLASS_REV` (macro, line 22) `#define PCI_REG_CLASS_REV`
  - `PCI_REG_CLASS_PROGIF` (macro, line 23) `#define PCI_REG_CLASS_PROGIF`
  - `PCI_REG_HEADER_TYPE` (macro, line 24) `#define PCI_REG_HEADER_TYPE`
  - `PCI_REG_BAR0` (macro, line 25) `#define PCI_REG_BAR0`
  - `PCI_REG_CARD_BUS` (macro, line 26) `#define PCI_REG_CARD_BUS`
  - `PCI_REG_BRIDGE_SECONDARY` (macro, line 27) `#define PCI_REG_BRIDGE_SECONDARY`
  - `PCI_REG_CAP_PTR` (macro, line 28) `#define PCI_REG_CAP_PTR`
  - `PCI_REG_BAR_COUNT` (macro, line 29) `#define PCI_REG_BAR_COUNT`
  - `PCI_COMMAND_IO` (macro, line 32) `#define PCI_COMMAND_IO`
  - `PCI_COMMAND_MEMORY` (macro, line 33) `#define PCI_COMMAND_MEMORY`
  - `PCI_COMMAND_BUS_MASTER` (macro, line 34) `#define PCI_COMMAND_BUS_MASTER`
  - `PCI_BAR_TYPE_MASK` (macro, line 37) `#define PCI_BAR_TYPE_MASK`
  - `PCI_BAR_IO` (macro, line 38) `#define PCI_BAR_IO`
  - `PCI_BAR_64BIT` (macro, line 39) `#define PCI_BAR_64BIT`
  - `PCI_BAR_PREFETCH` (macro, line 40) `#define PCI_BAR_PREFETCH`
  - `PCI_BAR_ADDR_MASK` (macro, line 41) `#define PCI_BAR_ADDR_MASK`
  - `PCI_ABSENT_ID` (macro, line 44) `#define PCI_ABSENT_ID`
  - `PCI_HEADER_MULTIFUNC` (macro, line 45) `#define PCI_HEADER_MULTIFUNC`
  - `PCI_HEADER_TYPE_MASK` (macro, line 46) `#define PCI_HEADER_TYPE_MASK`
  - `PCI_HDR_TYPE_BRIDGE` (macro, line 47) `#define PCI_HDR_TYPE_BRIDGE`
  - `PCI_CLASS_BRIDGE` (macro, line 55) `#define PCI_CLASS_BRIDGE`
  - `PCI_SUBCLASS_PCI_BRIDGE` (macro, line 56) `#define PCI_SUBCLASS_PCI_BRIDGE`
  - `PCI_CLASS_XHCI` (macro, line 57) `#define PCI_CLASS_XHCI`
  - `PCI_SUBCLASS_XHCI` (macro, line 58) `#define PCI_SUBCLASS_XHCI`
  - `PCI_PROGIF_XHCI` (macro, line 59) `#define PCI_PROGIF_XHCI`
  - `PCI_CLASS_ANY` (macro, line 62) `#define PCI_CLASS_ANY`
  - `PCI_CLASS_MAX_PASSES` (macro, line 68) `#define PCI_CLASS_MAX_PASSES`
- Imported by: `drivers/nvme.c`, `drivers/virtio_blk.c`, `drivers/virtio_net.c`, `drivers/xhci.c`, `net/rtl8139.c`, `tests/test_pci.c`

## headers/drivers/usbblk.h
- Doc: Docstring: drivers/usbblk.h -- boundary of the USB mass-storage driver.
- Layer: infrastructure
- Language: h
- Symbols:
  - `ubk_counters_t` (struct, line 37)
  - `ubk_init` (function, line 21) `int ubk_init(void);`
  - `ubk_present` (function, line 24) `int ubk_present(void);`
  - `ubk_sectors` (function, line 27) `unsigned long ubk_sectors(void);`
  - `ubk_read_sectors` (function, line 32) `int ubk_read_sectors(unsigned long lba, unsigned count, void *buf);`
  - `ubk_write_sectors` (function, line 33) `int ubk_write_sectors(unsigned long lba, unsigned count, const void *buf);`
  - `ubk_counters` (function, line 46) `void ubk_counters(ubk_counters_t *out);`
  - `ubk_build_cbw` (function, line 52) `void ubk_build_cbw(unsigned char *out, unsigned tag, unsigned long lba, unsigned blocks, int read, int data_len);`
  - `ubk_check_csw` (function, line 60) `int ubk_check_csw(const unsigned char *csw, unsigned tag, unsigned expect_len);`
  - `DRIVERS_USBBLK_H` (macro, line 11) `#define DRIVERS_USBBLK_H`
  - `UBK_BLOCK_SIZE` (macro, line 14) `#define UBK_BLOCK_SIZE`
  - `UBK_MAX_BLOCKS` (macro, line 15) `#define UBK_MAX_BLOCKS`
  - `UBK_MAX_SECTORS` (macro, line 16) `#define UBK_MAX_SECTORS`
- Imported by: `drivers/block.c`, `drivers/usbblk.c`, `kernel.c`, `kernel/shell.c`, `tests/test_usbblk.c`

## headers/drivers/usbhid.h
- Doc: Docstring: drivers/usbhid.h -- boundary of the USB HID boot-protocol driver.
- Layer: infrastructure
- Language: h
- Symbols:
  - `usbhid_counters_t` (struct, line 108)
  - `usbhid_init` (function, line 60) `int usbhid_init(void);`
  - `usbhid_poll_keyboard` (function, line 64) `int usbhid_poll_keyboard(void);`
  - `usbhid_poll_mouse` (function, line 68) `int usbhid_poll_mouse(void);`
  - `usbhid_poll` (function, line 71) `int usbhid_poll(void);`
  - `usbhid_keyboard_present` (function, line 76) `int usbhid_keyboard_present(void);`
  - `usbhid_mouse_present` (function, line 79) `int usbhid_mouse_present(void);`
  - `usbhid_press_kbd_report` (function, line 84) `int usbhid_press_kbd_report(const unsigned char report[HID_KBD_REPORT_LEN]);`
  - `usbhid_kbd_scancodes` (function, line 94) `int usbhid_kbd_scancodes(const unsigned char prev[HID_KBD_REPORT_LEN], const unsigned char cur[HID_KBD_REPORT_LEN]...`
  - `usbhid_mouse_decode` (function, line 102) `void usbhid_mouse_decode(const unsigned char prev[HID_MOUSE_REPORT_LEN], const unsigned char...`
  - `usbhid_counters` (function, line 116) `void usbhid_counters(usbhid_counters_t *out);`
  - `usbhid_set1_from_usage` (function, line 127) `int usbhid_set1_from_usage(unsigned usage, unsigned char *sc, int *e0);`
  - `DRIVERS_USBHID_H` (macro, line 12) `#define DRIVERS_USBHID_H`
  - `HID_USAGE_MIN` (macro, line 15) `#define HID_USAGE_MIN`
  - `HID_USAGE_MAX` (macro, line 16) `#define HID_USAGE_MAX`
  - `HID_MODIFIER_BIT` (macro, line 17) `#define HID_MODIFIER_BIT(n)`
  - `HID_MOD_LEFT_CTRL` (macro, line 18) `#define HID_MOD_LEFT_CTRL`
  - `HID_MOD_LEFT_SHIFT` (macro, line 19) `#define HID_MOD_LEFT_SHIFT`
  - `HID_MOD_LEFT_ALT` (macro, line 20) `#define HID_MOD_LEFT_ALT`
  - `HID_MOD_LEFT_GUI` (macro, line 21) `#define HID_MOD_LEFT_GUI`
  - `HID_MOD_RIGHT_CTRL` (macro, line 22) `#define HID_MOD_RIGHT_CTRL`
  - `HID_MOD_RIGHT_SHIFT` (macro, line 23) `#define HID_MOD_RIGHT_SHIFT`
  - `HID_MOD_RIGHT_ALT` (macro, line 24) `#define HID_MOD_RIGHT_ALT`
  - `HID_MOD_RIGHT_GUI` (macro, line 25) `#define HID_MOD_RIGHT_GUI`
  - `HID_KBD_REPORT_LEN` (macro, line 29) `#define HID_KBD_REPORT_LEN`
  - `HID_KBD_SLOTS` (macro, line 30) `#define HID_KBD_SLOTS`
  - `HID_MOUSE_REPORT_LEN` (macro, line 36) `#define HID_MOUSE_REPORT_LEN`
  - `HID_MOUSE_BUTTON_MASK` (macro, line 37) `#define HID_MOUSE_BUTTON_MASK`
  - `USBHID_MAX_REPORT_LEN` (macro, line 41) `#define USBHID_MAX_REPORT_LEN`
  - `USBHID_TRUNCATED` (macro, line 46) `#define USBHID_TRUNCATED`
  - `USBHID_PROTO_NONE` (macro, line 51) `#define USBHID_PROTO_NONE`
  - `HID_REQ_SET_PROTOCOL` (macro, line 54) `#define HID_REQ_SET_PROTOCOL`
  - `HID_PROTOCOL_BOOT` (macro, line 55) `#define HID_PROTOCOL_BOOT`
- Imported by: `drivers/usbhid.c`, `kernel.c`, `kernel/console_in.c`, `kernel/shell.c`, `tests/test_usbhid.c`

## headers/drivers/virtio_blk.h
- Doc: Docstring: drivers/virtio_blk.h -- virtio-blk boundary.
- Layer: infrastructure
- Language: h
- Symbols:
  - `vblk_init` (function, line 11) `int vblk_init(void);`
  - `vblk_present` (function, line 12) `int vblk_present(void);`
  - `vblk_sectors` (function, line 13) `unsigned long vblk_sectors(void);`
  - `vblk_read_sectors` (function, line 14) `int vblk_read_sectors(unsigned lba, unsigned count, void *buf);`
  - `vblk_write_sectors` (function, line 15) `int vblk_write_sectors(unsigned lba, unsigned count, const void *buf);`
  - `vblk_register_device` (function, line 18) `void vblk_register_device(void);`
  - `DRIVERS_VIRTIO_BLK_H` (macro, line 9) `#define DRIVERS_VIRTIO_BLK_H`
- Imported by: `drivers/block.c`, `drivers/virtio_blk.c`, `kernel.c`, `kernel/shell.c`

## headers/drivers/virtio_net.h
- Doc: Docstring: drivers/virtio_net.h -- virtio-net boundary.
- Layer: infrastructure
- Language: h
- Symbols:
  - `vnet_init` (function, line 16) `int vnet_init(void);`
  - `vnet_present` (function, line 19) `int vnet_present(void);`
  - `failure` (function, line 22) `* 0 on failure (no device, oversize, or TX deadline expiry). Pads * short frames to 60 bytes like the rtl8139 path....`
  - `vnet_poll` (function, line 28) `void vnet_poll(void);`
  - `vnet_get_mac` (function, line 31) `void vnet_get_mac(unsigned char out[6]);`
  - `vnet_iobase` (function, line 34) `unsigned short vnet_iobase(void);`
  - `vnet_counters` (function, line 37) `void vnet_counters(unsigned int *tx_frames, unsigned int *rx_frames);`
  - `vnet_link_up` (function, line 40) `int vnet_link_up(void);`
  - `DRIVERS_VIRTIO_NET_H` (macro, line 10) `#define DRIVERS_VIRTIO_NET_H`
- Imported by: `drivers/virtio_net.c`, `kernel/shell.c`, `net/net.c`

## headers/drivers/xhci.h
- Doc: Docstring: drivers/xhci.h -- boundary of the xHCI host controller driver.
- Layer: infrastructure
- Language: h
- Symbols:
  - `xhc_iface_t` (struct, line 94)
  - `xhc_port_t` (struct, line 107)
  - `xhc_dev_t` (struct, line 115)
  - `xhc_counters_t` (struct, line 124)
  - `xhc_init` (function, line 140) `int xhc_init(void);`
  - `xhc_poll` (function, line 146) `int xhc_poll(void);`
  - `xhc_port_count` (function, line 150) `int xhc_port_count(void);`
  - `xhc_port_state` (function, line 154) `int xhc_port_state(int port, xhc_port_t *out);`
  - `xhc_port_reset` (function, line 159) `int xhc_port_reset(int port);`
  - `xhc_enumerate` (function, line 165) `int xhc_enumerate(int port);`
  - `xhc_enumerate_all` (function, line 169) `int xhc_enumerate_all(void);`
  - `xhc_device_count` (function, line 172) `int xhc_device_count(void);`
  - `xhc_device_info` (function, line 175) `int xhc_device_info(int index, xhc_dev_t *out);`
  - `xhc_open_interface` (function, line 186) `int xhc_open_interface(int index, unsigned cls, unsigned sub, unsigned proto, xhc_iface_t *out);`
  - `xhc_control` (function, line 193) `int xhc_control(int index, const unsigned char setup[8], void *data, unsigned len, int host_to_device);`
  - `xhc_configure_endpoint` (function, line 200) `int xhc_configure_endpoint(int index, int ep_index, int ep_addr, int ep_type, int max_packet, int mult, int...`
  - `xhc_transfer` (function, line 211) `int xhc_transfer(int index, int ep_index, void *buf, unsigned len, int *got);`
  - `xhc_reset_endpoint` (function, line 216) `int xhc_reset_endpoint(int index, int ep_index);`
  - `xhc_transfer_async` (function, line 220) `int xhc_transfer_async(int index, int ep_index, void *buf, unsigned len);`
  - `xhc_poll_token_limit` (function, line 225) `int xhc_poll_token_limit(int token, unsigned budget_ms);`
  - `xhc_poll_token` (function, line 226) `int xhc_poll_token(int token);`
  - `xhc_counters` (function, line 229) `void xhc_counters(xhc_counters_t *out);`
  - `xhc_probe_note` (function, line 234) `const char *xhc_probe_note(void);`
  - `xhc_info` (function, line 238) `int xhc_info(unsigned *version, unsigned *slots, unsigned *ports, unsigned *caplength);`
  - `DRIVERS_XHCI_H` (macro, line 23) `#define DRIVERS_XHCI_H`
  - `XHC_MAX_DEVICES` (macro, line 29) `#define XHC_MAX_DEVICES`
  - `XHC_MAX_PORTS` (macro, line 34) `#define XHC_MAX_PORTS`
  - `XHC_MAX_EPS` (macro, line 38) `#define XHC_MAX_EPS`
  - `XHC_EP_INDEX_LIMIT` (macro, line 43) `#define XHC_EP_INDEX_LIMIT`
  - `XHC_MAX_PENDING` (macro, line 47) `#define XHC_MAX_PENDING`
  - `XHC_MAX_CONFIG_DESC` (macro, line 51) `#define XHC_MAX_CONFIG_DESC`
  - `XHC_TRB_RING_TRBS` (macro, line 56) `#define XHC_TRB_RING_TRBS`
  - `XHC_RESET_BUDGET_MS` (macro, line 61) `#define XHC_RESET_BUDGET_MS`
  - `XHC_CMD_BUDGET_MS` (macro, line 62) `#define XHC_CMD_BUDGET_MS`
  - `XHC_XFER_BUDGET_MS` (macro, line 63) `#define XHC_XFER_BUDGET_MS`
  - `XHC_PORT_BUDGET_MS` (macro, line 64) `#define XHC_PORT_BUDGET_MS`
  - `XHC_CAPLENGTH_MIN` (macro, line 68) `#define XHC_CAPLENGTH_MIN`
  - `XHC_SPEED_FULL` (macro, line 71) `#define XHC_SPEED_FULL`
  - `XHC_SPEED_LOW` (macro, line 72) `#define XHC_SPEED_LOW`
  - `XHC_SPEED_HIGH` (macro, line 73) `#define XHC_SPEED_HIGH`
  - `XHC_SPEED_SUPER` (macro, line 74) `#define XHC_SPEED_SUPER`
  - `XHC_EP_CONTROL` (macro, line 77) `#define XHC_EP_CONTROL`
  - `XHC_EP_ISOCHRONOUS` (macro, line 78) `#define XHC_EP_ISOCHRONOUS`
  - `XHC_EP_BULK` (macro, line 79) `#define XHC_EP_BULK`
  - `XHC_EP_INTERRUPT` (macro, line 80) `#define XHC_EP_INTERRUPT`
  - `XHC_EP_DIR_IN` (macro, line 83) `#define XHC_EP_DIR_IN`
  - `XHC_CLASS_HID` (macro, line 86) `#define XHC_CLASS_HID`
  - `XHC_SUBCLASS_BOOT` (macro, line 87) `#define XHC_SUBCLASS_BOOT`
  - `XHC_CLASS_MASS_STORAGE` (macro, line 88) `#define XHC_CLASS_MASS_STORAGE`
  - `XHC_SUBCLASS_SCSI` (macro, line 89) `#define XHC_SUBCLASS_SCSI`
  - `XHC_PROTOCOL_BULK_ONLY` (macro, line 90) `#define XHC_PROTOCOL_BULK_ONLY`
- Imported by: `drivers/usbblk.c`, `drivers/usbhid.c`, `drivers/xhci.c`, `kernel.c`, `kernel/console_in.c`, `kernel/sched.c`, `kernel/shell.c`, `tests/test_xhci.c`
