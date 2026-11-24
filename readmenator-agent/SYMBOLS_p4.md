# Symbols (page 4 of 28)
Previous: [SYMBOLS_p3.md](SYMBOLS_p3.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `BATCH_ERR_COUNT` | macro | `headers/batch.h:49` | `#define BATCH_ERR_COUNT` |
| `BATCH_ERR_OPCODE` | macro | `headers/batch.h:51` | `#define BATCH_ERR_OPCODE` |
| `BATCH_ERR_PTR` | macro | `headers/batch.h:50` | `#define BATCH_ERR_PTR` |
| `BATCH_H` | macro | `headers/batch.h:2` | `#define BATCH_H` |
| `BATCH_MAX_OPS` | macro | `headers/batch.h:41` | `#define BATCH_MAX_OPS` |
| `BATCH_OK` | macro | `headers/batch.h:48` | `#define BATCH_OK` |
| `BATCH_OP_GETPID` | macro | `headers/batch.h:46` | `#define BATCH_OP_GETPID` |
| `BATCH_OP_NOP` | macro | `headers/batch.h:43` | `#define BATCH_OP_NOP` |
| `BATCH_OP_TIME` | macro | `headers/batch.h:45` | `#define BATCH_OP_TIME` |
| `BATCH_OP_YIELD` | macro | `headers/batch.h:44` | `#define BATCH_OP_YIELD` |
| `batch_exec` | function | `headers/batch.h:62` | `long batch_exec(const batch_op_t *ops, long *results, int count, int *completed, batch_handler_t dispatch);` |
| `batch_op_t` | struct | `headers/batch.h:53` | `` |
| `BLOCK_H` | macro | `headers/block.h:2` | `#define BLOCK_H` |
| `BLOCK_SHIFT` | macro | `headers/block.h:8` | `#define BLOCK_SHIFT` |
| `BLOCK_SIZE` | macro | `headers/block.h:7` | `#define BLOCK_SIZE` |
| `SECTORS_PER_BLOCK` | macro | `headers/block.h:9` | `#define SECTORS_PER_BLOCK` |
| `block_disk_sectors` | function | `headers/block.h:40` | `unsigned long block_disk_sectors(void);` |
| `block_flush` | function | `headers/block.h:27` | `void block_flush(void);` |
| `block_init` | function | `headers/block.h:12` | `void block_init(void);` |
| `block_read` | function | `headers/block.h:18` | `int block_read(unsigned int block_num, void *buf);` |
| `block_read_multi` | function | `headers/block.h:23` | `int block_read_multi(unsigned int block_num, unsigned int count, void *buf);` |
| `block_read_sectors` | function | `headers/block.h:37` | `int block_read_sectors(unsigned lba, unsigned count, void *buf);` |
| `block_set_base` | function | `headers/block.h:15` | `void block_set_base(unsigned int lba_base);` |
| `block_total` | function | `headers/block.h:30` | `unsigned int block_total(void);` |
| `block_write` | function | `headers/block.h:19` | `int block_write(unsigned int block_num, const void *buf);` |
| `block_write_multi` | function | `headers/block.h:24` | `int block_write_multi(unsigned int block_num, unsigned int count, const void *buf);` |
| `DESKTOP_ICONS_H` | macro | `headers/desktop_icons.h:8` | `#define DESKTOP_ICONS_H` |
| `ICON_EMBEDDED_H` | macro | `headers/desktop_icons.h:13` | `#define ICON_EMBEDDED_H` |
| `ICON_EMBEDDED_W` | macro | `headers/desktop_icons.h:12` | `#define ICON_EMBEDDED_W` |
| `DESKTOP_SHORTCUTS_H` | macro | `headers/desktop_shortcuts.h:13` | `#define DESKTOP_SHORTCUTS_H` |
| `DOCK_BOUNCE_H` | macro | `headers/desktop_shortcuts.h:58` | `#define DOCK_BOUNCE_H` |
| `DOCK_BOUNCE_TICKS` | macro | `headers/desktop_shortcuts.h:59` | `#define DOCK_BOUNCE_TICKS` |
| `DOCK_CRYSTAL_STEP` | macro | `headers/desktop_shortcuts.h:41` | `#define DOCK_CRYSTAL_STEP` |
| `DOCK_GAP` | macro | `headers/desktop_shortcuts.h:35` | `#define DOCK_GAP` |
| `DOCK_LABEL_GAP` | macro | `headers/desktop_shortcuts.h:36` | `#define DOCK_LABEL_GAP` |
| `DOCK_MAG_H` | macro | `headers/desktop_shortcuts.h:50` | `#define DOCK_MAG_H` |
| `DOCK_MAG_REACH_CELLS` | macro | `headers/desktop_shortcuts.h:51` | `#define DOCK_MAG_REACH_CELLS` |
| `DOCK_MAG_TICKS` | macro | `headers/desktop_shortcuts.h:52` | `#define DOCK_MAG_TICKS` |
| `DOCK_MAG_W` | macro | `headers/desktop_shortcuts.h:49` | `#define DOCK_MAG_W` |
| `DOCK_PAD_X` | macro | `headers/desktop_shortcuts.h:33` | `#define DOCK_PAD_X` |
| `DOCK_PAD_Y` | macro | `headers/desktop_shortcuts.h:34` | `#define DOCK_PAD_Y` |
| `ICON_H` | macro | `headers/desktop_shortcuts.h:25` | `#define ICON_H` |
| `ICON_LABEL_H` | macro | `headers/desktop_shortcuts.h:28` | `#define ICON_LABEL_H` |
| `ICON_PAD_X` | macro | `headers/desktop_shortcuts.h:26` | `#define ICON_PAD_X` |
| `ICON_PAD_Y` | macro | `headers/desktop_shortcuts.h:27` | `#define ICON_PAD_Y` |
| `ICON_PAL_BASE` | macro | `headers/desktop_shortcuts.h:66` | `#define ICON_PAL_BASE` |
| `ICON_PAL_SIZE` | macro | `headers/desktop_shortcuts.h:67` | `#define ICON_PAL_SIZE` |
| `ICON_W` | macro | `headers/desktop_shortcuts.h:24` | `#define ICON_W` |
| `MAX_SHORTCUTS` | macro | `headers/desktop_shortcuts.h:18` | `#define MAX_SHORTCUTS` |
| `SHORTCUT_CMD_LEN` | macro | `headers/desktop_shortcuts.h:20` | `#define SHORTCUT_CMD_LEN` |
| `SHORTCUT_NAME_LEN` | macro | `headers/desktop_shortcuts.h:19` | `#define SHORTCUT_NAME_LEN` |
| `SHORTCUT_PATH_LEN` | macro | `headers/desktop_shortcuts.h:21` | `#define SHORTCUT_PATH_LEN` |
| `desktop_shortcut` | struct | `headers/desktop_shortcuts.h:73` | `` |
| `desktop_shortcuts_draw` | function | `headers/desktop_shortcuts.h:86` | `void desktop_shortcuts_draw(void);` |
| `desktop_shortcuts_hit_test` | function | `headers/desktop_shortcuts.h:90` | `const char *desktop_shortcuts_hit_test(int mx, int my);` |
| `desktop_shortcuts_load` | function | `headers/desktop_shortcuts.h:83` | `void desktop_shortcuts_load(void);` |
| `DEV_MAX` | macro | `headers/driver.h:19` | `#define DEV_MAX` |
| `DEV_NAME_LEN` | macro | `headers/driver.h:18` | `#define DEV_NAME_LEN` |
| `DEV_TYPE_AUDIO` | macro | `headers/driver.h:22` | `#define DEV_TYPE_AUDIO` |
| `DEV_TYPE_BLOCK` | macro | `headers/driver.h:21` | `#define DEV_TYPE_BLOCK` |
| `DEV_TYPE_CHAR` | macro | `headers/driver.h:24` | `#define DEV_TYPE_CHAR` |
| `DEV_TYPE_NET` | macro | `headers/driver.h:23` | `#define DEV_TYPE_NET` |
| `DRIVER_H` | macro | `headers/driver.h:2` | `#define DRIVER_H` |
| `audio_ops_t` | struct | `headers/driver.h:37` | `` |
| `block_ops_t` | struct | `headers/driver.h:28` | `` |
| `device` | struct | `headers/driver.h:48` | `` |
| `device_count` | function | `headers/driver.h:59` | `int device_count(void);` |
| `device_find` | function | `headers/driver.h:57` | `device_t *device_find(const char *name);` |
| `device_find_by_type` | function | `headers/driver.h:58` | `device_t *device_find_by_type(int type);` |
| `device_register` | function | `headers/driver.h:56` | `int device_register(device_t *dev);` |
| `device_reset` | function | `headers/driver.h:60` | `void device_reset(void);` |
| `device_t` | type_alias | `headers/driver.h:25` | `typedef struct device device_t;` |
| `DRIVERS_AHCI_H` | macro | `headers/drivers/ahci.h:11` | `#define DRIVERS_AHCI_H` |
| `ahci_init` | function | `headers/drivers/ahci.h:16` | `int ahci_init(void);` |
| `ahci_note` | function | `headers/drivers/ahci.h:31` | `const char *ahci_note(void);` |
| `ahci_port` | function | `headers/drivers/ahci.h:25` | `int ahci_port(void);` |
| `ahci_ports_implemented` | function | `headers/drivers/ahci.h:28` | `unsigned ahci_ports_implemented(void);` |
| `ahci_present` | function | `headers/drivers/ahci.h:19` | `int ahci_present(void);` |
| `ahci_read_sectors` | function | `headers/drivers/ahci.h:40` | `int ahci_read_sectors(unsigned lba, unsigned count, void *buf);` |
| `ahci_register_device` | function | `headers/drivers/ahci.h:48` | `void ahci_register_device(void);` |
| `ahci_sectors` | function | `headers/drivers/ahci.h:34` | `unsigned long ahci_sectors(void);` |
| `ahci_version` | function | `headers/drivers/ahci.h:22` | `unsigned ahci_version(void);` |
| `ahci_write_sectors` | function | `headers/drivers/ahci.h:45` | `int ahci_write_sectors(unsigned lba, unsigned count, const void *buf);` |
| `KBD_H` | macro | `headers/drivers/kbd.h:2` | `#define KBD_H` |
| `KBD_LAYOUT_EN` | macro | `headers/drivers/kbd.h:6` | `#define KBD_LAYOUT_EN` |
| `KBD_LAYOUT_ES` | macro | `headers/drivers/kbd.h:7` | `#define KBD_LAYOUT_ES` |
| `kbd_available` | function | `headers/drivers/kbd.h:9` | `int kbd_available(void);` |
| `kbd_drop_counts` | function | `headers/drivers/kbd.h:32` | `void kbd_drop_counts(unsigned long *cooked, unsigned long *raw);` |
| `kbd_e0_get` | function | `headers/drivers/kbd.h:40` | `int kbd_e0_get(void);` |
| `kbd_e0_set` | function | `headers/drivers/kbd.h:41` | `void kbd_e0_set(int v);` |
| `kbd_feed_scancode` | function | `headers/drivers/kbd.h:11` | `int kbd_feed_scancode(unsigned char sc);` |
| `kbd_flush_all` | function | `headers/drivers/kbd.h:42` | `void kbd_flush_all(void);` |
| `kbd_get_layout` | function | `headers/drivers/kbd.h:15` | `int kbd_get_layout(void);` |
| `kbd_q_empty` | function | `headers/drivers/kbd.h:27` | `int kbd_q_empty(void);` |
| `kbd_q_pop` | function | `headers/drivers/kbd.h:28` | `int kbd_q_pop(void);` |
| `kbd_q_push` | function | `headers/drivers/kbd.h:29` | `void kbd_q_push(unsigned char c);` |
| `kbd_raw_empty` | function | `headers/drivers/kbd.h:37` | `int kbd_raw_empty(void);` |
| `kbd_raw_flush` | function | `headers/drivers/kbd.h:43` | `void kbd_raw_flush(void);` |
| `kbd_raw_mode_get` | function | `headers/drivers/kbd.h:35` | `int kbd_raw_mode_get(void);` |
| `kbd_raw_mode_set` | function | `headers/drivers/kbd.h:36` | `void kbd_raw_mode_set(int on);` |
| `kbd_raw_pop` | function | `headers/drivers/kbd.h:38` | `int kbd_raw_pop(void);` |
| `kbd_raw_push_byte` | function | `headers/drivers/kbd.h:39` | `void kbd_raw_push_byte(unsigned char c);` |
| `kbd_read` | function | `headers/drivers/kbd.h:10` | `int kbd_read(void);` |
| `kbd_reset_for_shell` | function | `headers/drivers/kbd.h:12` | `void kbd_reset_for_shell(void);` |
| `kbd_set_layout` | function | `headers/drivers/kbd.h:16` | `void kbd_set_layout(int layout);` |
| `kbd_sys_raw_filter` | function | `headers/drivers/kbd.h:50` | `int kbd_sys_raw_filter(unsigned char sc);` |
| `kbd_toggle_layout` | function | `headers/drivers/kbd.h:17` | `void kbd_toggle_layout(void);` |
| `MODIFIERS_H` | macro | `headers/drivers/modifiers.h:2` | `#define MODIFIERS_H` |
| `MOD_ALT` | macro | `headers/drivers/modifiers.h:32` | `#define MOD_ALT` |
| `MOD_ALTGR` | macro | `headers/drivers/modifiers.h:33` | `#define MOD_ALTGR` |
| `MOD_CTRL` | macro | `headers/drivers/modifiers.h:31` | `#define MOD_CTRL` |
| `MOD_SHIFT` | macro | `headers/drivers/modifiers.h:30` | `#define MOD_SHIFT` |
| `MOD_SUPER` | macro | `headers/drivers/modifiers.h:34` | `#define MOD_SUPER` |
| `modifier_keys_t` | struct | `headers/drivers/modifiers.h:19` | `` |
| `modifier_state_t` | struct | `headers/drivers/modifiers.h:5` | `` |
| `modifiers_init` | function | `headers/drivers/modifiers.h:37` | `static inline void modifiers_init(modifier_state_t *st)` |
| `modifiers_match` | function | `headers/drivers/modifiers.h:92` | `static inline int modifiers_match(const modifier_state_t *st, int mask)` |
| `modifiers_update` | function | `headers/drivers/modifiers.h:54` | `static inline int modifiers_update(const modifier_keys_t *keys,                                  ...` |
| `MOUSE_H` | macro | `headers/drivers/mouse.h:2` | `#define MOUSE_H` |
| `mouse_disable` | function | `headers/drivers/mouse.h:14` | `void mouse_disable(void);` |
| `mouse_enable` | function | `headers/drivers/mouse.h:17` | `void mouse_enable(void);` |
| `mouse_hw_init` | function | `headers/drivers/mouse.h:11` | `void mouse_hw_init(void);` |
| `DRIVERS_NVME_H` | macro | `headers/drivers/nvme.h:2` | `#define DRIVERS_NVME_H` |
| `nvme_init` | function | `headers/drivers/nvme.h:4` | `int nvme_init(void);` |
| `nvme_note` | function | `headers/drivers/nvme.h:7` | `const char *nvme_note(void);` |
| `nvme_present` | function | `headers/drivers/nvme.h:5` | `int nvme_present(void);` |
| `nvme_read_sectors` | function | `headers/drivers/nvme.h:9` | `int nvme_read_sectors(unsigned lba, unsigned count, void *buf);` |
| `nvme_sectors` | function | `headers/drivers/nvme.h:8` | `unsigned long nvme_sectors(void);` |
| `nvme_version` | function | `headers/drivers/nvme.h:6` | `unsigned nvme_version(void);` |
| `DRIVERS_PCI_H` | macro | `headers/drivers/pci.h:11` | `#define DRIVERS_PCI_H` |
| `PCI_ABSENT_ID` | macro | `headers/drivers/pci.h:44` | `#define PCI_ABSENT_ID` |
| `PCI_BAR_64BIT` | macro | `headers/drivers/pci.h:39` | `#define PCI_BAR_64BIT` |
| `PCI_BAR_ADDR_MASK` | macro | `headers/drivers/pci.h:41` | `#define PCI_BAR_ADDR_MASK` |
| `PCI_BAR_IO` | macro | `headers/drivers/pci.h:38` | `#define PCI_BAR_IO` |
| `PCI_BAR_PREFETCH` | macro | `headers/drivers/pci.h:40` | `#define PCI_BAR_PREFETCH` |
| `PCI_BAR_TYPE_MASK` | macro | `headers/drivers/pci.h:37` | `#define PCI_BAR_TYPE_MASK` |
| `PCI_CFG_ADDR` | macro | `headers/drivers/pci.h:13` | `#define PCI_CFG_ADDR` |
| `PCI_CFG_DATA` | macro | `headers/drivers/pci.h:14` | `#define PCI_CFG_DATA` |
| `PCI_CLASS_ANY` | macro | `headers/drivers/pci.h:62` | `#define PCI_CLASS_ANY` |
| `PCI_CLASS_BRIDGE` | macro | `headers/drivers/pci.h:55` | `#define PCI_CLASS_BRIDGE` |
| `PCI_CLASS_MAX_PASSES` | macro | `headers/drivers/pci.h:68` | `#define PCI_CLASS_MAX_PASSES` |
| `PCI_CLASS_XHCI` | macro | `headers/drivers/pci.h:57` | `#define PCI_CLASS_XHCI` |
| `PCI_COMMAND_BUS_MASTER` | macro | `headers/drivers/pci.h:34` | `#define PCI_COMMAND_BUS_MASTER` |
| `PCI_COMMAND_IO` | macro | `headers/drivers/pci.h:32` | `#define PCI_COMMAND_IO` |
| `PCI_COMMAND_MEMORY` | macro | `headers/drivers/pci.h:33` | `#define PCI_COMMAND_MEMORY` |
| `PCI_HDR_TYPE_BRIDGE` | macro | `headers/drivers/pci.h:47` | `#define PCI_HDR_TYPE_BRIDGE` |
| `PCI_HEADER_MULTIFUNC` | macro | `headers/drivers/pci.h:45` | `#define PCI_HEADER_MULTIFUNC` |
| `PCI_HEADER_TYPE_MASK` | macro | `headers/drivers/pci.h:46` | `#define PCI_HEADER_TYPE_MASK` |
| `PCI_MAX_BUS` | macro | `headers/drivers/pci.h:15` | `#define PCI_MAX_BUS` |
| `PCI_MAX_DEV` | macro | `headers/drivers/pci.h:16` | `#define PCI_MAX_DEV` |
| `PCI_MAX_FUNC` | macro | `headers/drivers/pci.h:17` | `#define PCI_MAX_FUNC` |
| `PCI_PROGIF_XHCI` | macro | `headers/drivers/pci.h:59` | `#define PCI_PROGIF_XHCI` |
| `PCI_REG_BAR0` | macro | `headers/drivers/pci.h:25` | `#define PCI_REG_BAR0` |
| `PCI_REG_BAR_COUNT` | macro | `headers/drivers/pci.h:29` | `#define PCI_REG_BAR_COUNT` |
| `PCI_REG_BRIDGE_SECONDARY` | macro | `headers/drivers/pci.h:27` | `#define PCI_REG_BRIDGE_SECONDARY` |
| `PCI_REG_CAP_PTR` | macro | `headers/drivers/pci.h:28` | `#define PCI_REG_CAP_PTR` |
| `PCI_REG_CARD_BUS` | macro | `headers/drivers/pci.h:26` | `#define PCI_REG_CARD_BUS` |
| `PCI_REG_CLASS_PROGIF` | macro | `headers/drivers/pci.h:23` | `#define PCI_REG_CLASS_PROGIF` |
| `PCI_REG_CLASS_REV` | macro | `headers/drivers/pci.h:22` | `#define PCI_REG_CLASS_REV` |
| `PCI_REG_COMMAND` | macro | `headers/drivers/pci.h:21` | `#define PCI_REG_COMMAND` |
| `PCI_REG_HEADER_TYPE` | macro | `headers/drivers/pci.h:24` | `#define PCI_REG_HEADER_TYPE` |
| `PCI_REG_VENDOR_ID` | macro | `headers/drivers/pci.h:20` | `#define PCI_REG_VENDOR_ID` |
| `PCI_SUBCLASS_PCI_BRIDGE` | macro | `headers/drivers/pci.h:56` | `#define PCI_SUBCLASS_PCI_BRIDGE` |
| `PCI_SUBCLASS_XHCI` | macro | `headers/drivers/pci.h:58` | `#define PCI_SUBCLASS_XHCI` |
| `number` | function | `headers/drivers/pci.h:186` | `* bus number (a bridge on any function, since PCIe root ports are functions  * of one multifuncti...` |
| `pci_bar_base` | function | `headers/drivers/pci.h:412` | `static inline unsigned long long pci_bar_base(unsigned bus, unsigned dev,         unsigned func, ...` |
| `pci_bar_count` | function | `headers/drivers/pci.h:254` | `static inline unsigned pci_bar_count(unsigned bus, unsigned dev, unsigned func,         void (*ou...` |
| `pci_bar_ctz32` | function | `headers/drivers/pci.h:290` | `static inline unsigned pci_bar_ctz32(unsigned val)` |
| `pci_bar_is_64bit` | function | `headers/drivers/pci.h:280` | `static inline int pci_bar_is_64bit(unsigned bus, unsigned dev, unsigned func,         unsigned ba...` |
| `pci_bar_is_io` | function | `headers/drivers/pci.h:269` | `static inline int pci_bar_is_io(unsigned bus, unsigned dev, unsigned func,         unsigned bar, ...` |
| `pci_bar_relocate` | function | `headers/drivers/pci.h:388` | `static inline int pci_bar_relocate(unsigned bus, unsigned dev, unsigned func,         unsigned ba...` |
| `pci_bar_restore` | function | `headers/drivers/pci.h:430` | `static inline void pci_bar_restore(unsigned bus, unsigned dev,         unsigned func, unsigned ba...` |
| `pci_bar_size` | function | `headers/drivers/pci.h:352` | `static inline unsigned long long pci_bar_size(unsigned bus, unsigned dev,         unsigned func, ...` |
| `pci_bar_size_from_mask` | function | `headers/drivers/pci.h:321` | `static inline unsigned long long pci_bar_size_from_mask(unsigned long long mask)` |
| `pci_bdf_t` | struct | `headers/drivers/pci.h:71` | `` |
| `pci_cfg_read` | function | `headers/drivers/pci.h:80` | `static inline unsigned pci_cfg_read(unsigned bus, unsigned dev,         unsigned func, unsigned r...` |
| `pci_cfg_read8` | function | `headers/drivers/pci.h:100` | `static inline unsigned char pci_cfg_read8(unsigned bus, unsigned dev,         unsigned func, unsi...` |
| `pci_cfg_write` | function | `headers/drivers/pci.h:90` | `static inline void pci_cfg_write(unsigned bus, unsigned dev,         unsigned func, unsigned reg,...` |
| `pci_cfg_write8` | function | `headers/drivers/pci.h:109` | `static inline void pci_cfg_write8(unsigned bus, unsigned dev,         unsigned func, unsigned reg...` |
| `pci_find` | function | `headers/drivers/pci.h:170` | `static inline int pci_find(unsigned vendor, unsigned device,         unsigned (*inl)(unsigned sho...` |
| `pci_is_multifunction` | function | `headers/drivers/pci.h:156` | `static inline int pci_is_multifunction(unsigned bus, unsigned dev,         void (*outl)(unsigned ...` |
| `pci_present` | function | `headers/drivers/pci.h:122` | `static inline int pci_present(unsigned bus, unsigned dev, unsigned func,         void (*outl)(uns...` |
| `xHCI` | function | `headers/drivers/pci.h:134` | `* base class: an xHCI (0x0C/0x03/0x30) would look for class 0x03, and a PCI  * bridge (0x06/0x04)...` |
| `DRIVERS_USBBLK_H` | macro | `headers/drivers/usbblk.h:11` | `#define DRIVERS_USBBLK_H` |
| `UBK_BLOCK_SIZE` | macro | `headers/drivers/usbblk.h:14` | `#define UBK_BLOCK_SIZE` |
| `UBK_MAX_BLOCKS` | macro | `headers/drivers/usbblk.h:15` | `#define UBK_MAX_BLOCKS` |
| `UBK_MAX_SECTORS` | macro | `headers/drivers/usbblk.h:16` | `#define UBK_MAX_SECTORS` |
| `ubk_build_cbw` | function | `headers/drivers/usbblk.h:52` | `void ubk_build_cbw(unsigned char *out, unsigned tag, unsigned long lba, unsigned blocks, int read, int data_len);` |
| `ubk_check_csw` | function | `headers/drivers/usbblk.h:60` | `int ubk_check_csw(const unsigned char *csw, unsigned tag, unsigned expect_len);` |
| `ubk_counters` | function | `headers/drivers/usbblk.h:46` | `void ubk_counters(ubk_counters_t *out);` |
| `ubk_counters_t` | struct | `headers/drivers/usbblk.h:37` | `` |
| `ubk_init` | function | `headers/drivers/usbblk.h:21` | `int ubk_init(void);` |
| `ubk_present` | function | `headers/drivers/usbblk.h:24` | `int ubk_present(void);` |
| `ubk_read_sectors` | function | `headers/drivers/usbblk.h:32` | `int ubk_read_sectors(unsigned long lba, unsigned count, void *buf);` |
| `ubk_sectors` | function | `headers/drivers/usbblk.h:27` | `unsigned long ubk_sectors(void);` |
| `ubk_write_sectors` | function | `headers/drivers/usbblk.h:33` | `int ubk_write_sectors(unsigned long lba, unsigned count, const void *buf);` |
| `DRIVERS_USBHID_H` | macro | `headers/drivers/usbhid.h:12` | `#define DRIVERS_USBHID_H` |
| `HID_KBD_REPORT_LEN` | macro | `headers/drivers/usbhid.h:29` | `#define HID_KBD_REPORT_LEN` |
| `HID_KBD_SLOTS` | macro | `headers/drivers/usbhid.h:30` | `#define HID_KBD_SLOTS` |
| `HID_MODIFIER_BIT` | macro | `headers/drivers/usbhid.h:17` | `#define HID_MODIFIER_BIT(n)` |
| `HID_MOD_LEFT_ALT` | macro | `headers/drivers/usbhid.h:20` | `#define HID_MOD_LEFT_ALT` |
| `HID_MOD_LEFT_CTRL` | macro | `headers/drivers/usbhid.h:18` | `#define HID_MOD_LEFT_CTRL` |
| `HID_MOD_LEFT_GUI` | macro | `headers/drivers/usbhid.h:21` | `#define HID_MOD_LEFT_GUI` |
| `HID_MOD_LEFT_SHIFT` | macro | `headers/drivers/usbhid.h:19` | `#define HID_MOD_LEFT_SHIFT` |
| `HID_MOD_RIGHT_ALT` | macro | `headers/drivers/usbhid.h:24` | `#define HID_MOD_RIGHT_ALT` |
| `HID_MOD_RIGHT_CTRL` | macro | `headers/drivers/usbhid.h:22` | `#define HID_MOD_RIGHT_CTRL` |
| `HID_MOD_RIGHT_GUI` | macro | `headers/drivers/usbhid.h:25` | `#define HID_MOD_RIGHT_GUI` |
| `HID_MOD_RIGHT_SHIFT` | macro | `headers/drivers/usbhid.h:23` | `#define HID_MOD_RIGHT_SHIFT` |
| `HID_MOUSE_BUTTON_MASK` | macro | `headers/drivers/usbhid.h:37` | `#define HID_MOUSE_BUTTON_MASK` |
| `HID_MOUSE_REPORT_LEN` | macro | `headers/drivers/usbhid.h:36` | `#define HID_MOUSE_REPORT_LEN` |
| `HID_PROTOCOL_BOOT` | macro | `headers/drivers/usbhid.h:55` | `#define HID_PROTOCOL_BOOT` |
| `HID_REQ_SET_PROTOCOL` | macro | `headers/drivers/usbhid.h:54` | `#define HID_REQ_SET_PROTOCOL` |
| `HID_USAGE_MAX` | macro | `headers/drivers/usbhid.h:16` | `#define HID_USAGE_MAX` |
| `HID_USAGE_MIN` | macro | `headers/drivers/usbhid.h:15` | `#define HID_USAGE_MIN` |
| `USBHID_MAX_REPORT_LEN` | macro | `headers/drivers/usbhid.h:41` | `#define USBHID_MAX_REPORT_LEN` |
| `USBHID_PROTO_NONE` | macro | `headers/drivers/usbhid.h:51` | `#define USBHID_PROTO_NONE` |
| `USBHID_TRUNCATED` | macro | `headers/drivers/usbhid.h:46` | `#define USBHID_TRUNCATED` |
| `usbhid_counters` | function | `headers/drivers/usbhid.h:116` | `void usbhid_counters(usbhid_counters_t *out);` |
| `usbhid_counters_t` | struct | `headers/drivers/usbhid.h:108` | `` |
| `usbhid_init` | function | `headers/drivers/usbhid.h:60` | `int usbhid_init(void);` |
| `usbhid_kbd_scancodes` | function | `headers/drivers/usbhid.h:94` | `int usbhid_kbd_scancodes(const unsigned char prev[HID_KBD_REPORT_LEN], const unsigned char cur[HID_KBD_REPORT_LEN]...` |
| `usbhid_keyboard_present` | function | `headers/drivers/usbhid.h:76` | `int usbhid_keyboard_present(void);` |
| `usbhid_mouse_decode` | function | `headers/drivers/usbhid.h:102` | `void usbhid_mouse_decode(const unsigned char prev[HID_MOUSE_REPORT_LEN], const unsigned char...` |
| `usbhid_mouse_present` | function | `headers/drivers/usbhid.h:79` | `int usbhid_mouse_present(void);` |
| `usbhid_poll` | function | `headers/drivers/usbhid.h:71` | `int usbhid_poll(void);` |
| `usbhid_poll_keyboard` | function | `headers/drivers/usbhid.h:64` | `int usbhid_poll_keyboard(void);` |
| `usbhid_poll_mouse` | function | `headers/drivers/usbhid.h:68` | `int usbhid_poll_mouse(void);` |
| `usbhid_press_kbd_report` | function | `headers/drivers/usbhid.h:84` | `int usbhid_press_kbd_report(const unsigned char report[HID_KBD_REPORT_LEN]);` |
| `usbhid_set1_from_usage` | function | `headers/drivers/usbhid.h:127` | `int usbhid_set1_from_usage(unsigned usage, unsigned char *sc, int *e0);` |
| `DRIVERS_VIRTIO_BLK_H` | macro | `headers/drivers/virtio_blk.h:9` | `#define DRIVERS_VIRTIO_BLK_H` |
| `vblk_init` | function | `headers/drivers/virtio_blk.h:11` | `int vblk_init(void);` |
| `vblk_present` | function | `headers/drivers/virtio_blk.h:12` | `int vblk_present(void);` |
| `vblk_read_sectors` | function | `headers/drivers/virtio_blk.h:14` | `int vblk_read_sectors(unsigned lba, unsigned count, void *buf);` |
| `vblk_register_device` | function | `headers/drivers/virtio_blk.h:18` | `void vblk_register_device(void);` |
| `vblk_sectors` | function | `headers/drivers/virtio_blk.h:13` | `unsigned long vblk_sectors(void);` |
| `vblk_write_sectors` | function | `headers/drivers/virtio_blk.h:15` | `int vblk_write_sectors(unsigned lba, unsigned count, const void *buf);` |
| `DRIVERS_VIRTIO_NET_H` | macro | `headers/drivers/virtio_net.h:10` | `#define DRIVERS_VIRTIO_NET_H` |
| `failure` | function | `headers/drivers/virtio_net.h:22` | `* 0 on failure (no device, oversize, or TX deadline expiry). Pads * short frames to 60 bytes like the rtl8139 path....` |
| `vnet_counters` | function | `headers/drivers/virtio_net.h:37` | `void vnet_counters(unsigned int *tx_frames, unsigned int *rx_frames);` |
| `vnet_get_mac` | function | `headers/drivers/virtio_net.h:31` | `void vnet_get_mac(unsigned char out[6]);` |
| `vnet_init` | function | `headers/drivers/virtio_net.h:16` | `int vnet_init(void);` |
| `vnet_iobase` | function | `headers/drivers/virtio_net.h:34` | `unsigned short vnet_iobase(void);` |
| `vnet_link_up` | function | `headers/drivers/virtio_net.h:40` | `int vnet_link_up(void);` |
| `vnet_poll` | function | `headers/drivers/virtio_net.h:28` | `void vnet_poll(void);` |
| `vnet_present` | function | `headers/drivers/virtio_net.h:19` | `int vnet_present(void);` |
| `DRIVERS_XHCI_H` | macro | `headers/drivers/xhci.h:23` | `#define DRIVERS_XHCI_H` |
| `XHC_CAPLENGTH_MIN` | macro | `headers/drivers/xhci.h:68` | `#define XHC_CAPLENGTH_MIN` |
| `XHC_CLASS_HID` | macro | `headers/drivers/xhci.h:86` | `#define XHC_CLASS_HID` |
| `XHC_CLASS_MASS_STORAGE` | macro | `headers/drivers/xhci.h:88` | `#define XHC_CLASS_MASS_STORAGE` |
| `XHC_CMD_BUDGET_MS` | macro | `headers/drivers/xhci.h:62` | `#define XHC_CMD_BUDGET_MS` |
| `XHC_EP_BULK` | macro | `headers/drivers/xhci.h:79` | `#define XHC_EP_BULK` |
| `XHC_EP_CONTROL` | macro | `headers/drivers/xhci.h:77` | `#define XHC_EP_CONTROL` |
| `XHC_EP_DIR_IN` | macro | `headers/drivers/xhci.h:83` | `#define XHC_EP_DIR_IN` |
| `XHC_EP_INDEX_LIMIT` | macro | `headers/drivers/xhci.h:43` | `#define XHC_EP_INDEX_LIMIT` |
| `XHC_EP_INTERRUPT` | macro | `headers/drivers/xhci.h:80` | `#define XHC_EP_INTERRUPT` |
| `XHC_EP_ISOCHRONOUS` | macro | `headers/drivers/xhci.h:78` | `#define XHC_EP_ISOCHRONOUS` |
| `XHC_MAX_CONFIG_DESC` | macro | `headers/drivers/xhci.h:51` | `#define XHC_MAX_CONFIG_DESC` |
| `XHC_MAX_DEVICES` | macro | `headers/drivers/xhci.h:29` | `#define XHC_MAX_DEVICES` |
| `XHC_MAX_EPS` | macro | `headers/drivers/xhci.h:38` | `#define XHC_MAX_EPS` |
| `XHC_MAX_PENDING` | macro | `headers/drivers/xhci.h:47` | `#define XHC_MAX_PENDING` |
| `XHC_MAX_PORTS` | macro | `headers/drivers/xhci.h:34` | `#define XHC_MAX_PORTS` |
| `XHC_PORT_BUDGET_MS` | macro | `headers/drivers/xhci.h:64` | `#define XHC_PORT_BUDGET_MS` |
| `XHC_PROTOCOL_BULK_ONLY` | macro | `headers/drivers/xhci.h:90` | `#define XHC_PROTOCOL_BULK_ONLY` |
| `XHC_RESET_BUDGET_MS` | macro | `headers/drivers/xhci.h:61` | `#define XHC_RESET_BUDGET_MS` |
| `XHC_SPEED_FULL` | macro | `headers/drivers/xhci.h:71` | `#define XHC_SPEED_FULL` |
| `XHC_SPEED_HIGH` | macro | `headers/drivers/xhci.h:73` | `#define XHC_SPEED_HIGH` |
| `XHC_SPEED_LOW` | macro | `headers/drivers/xhci.h:72` | `#define XHC_SPEED_LOW` |
| `XHC_SPEED_SUPER` | macro | `headers/drivers/xhci.h:74` | `#define XHC_SPEED_SUPER` |
| `XHC_SUBCLASS_BOOT` | macro | `headers/drivers/xhci.h:87` | `#define XHC_SUBCLASS_BOOT` |
| `XHC_SUBCLASS_SCSI` | macro | `headers/drivers/xhci.h:89` | `#define XHC_SUBCLASS_SCSI` |
| `XHC_TRB_RING_TRBS` | macro | `headers/drivers/xhci.h:56` | `#define XHC_TRB_RING_TRBS` |
| `XHC_XFER_BUDGET_MS` | macro | `headers/drivers/xhci.h:63` | `#define XHC_XFER_BUDGET_MS` |
| `xhc_configure_endpoint` | function | `headers/drivers/xhci.h:200` | `int xhc_configure_endpoint(int index, int ep_index, int ep_addr, int ep_type, int max_packet, int mult, int...` |
| `xhc_control` | function | `headers/drivers/xhci.h:193` | `int xhc_control(int index, const unsigned char setup[8], void *data, unsigned len, int host_to_device);` |
| `xhc_counters` | function | `headers/drivers/xhci.h:229` | `void xhc_counters(xhc_counters_t *out);` |
| `xhc_counters_t` | struct | `headers/drivers/xhci.h:124` | `` |
| `xhc_dev_t` | struct | `headers/drivers/xhci.h:115` | `` |
| `xhc_device_count` | function | `headers/drivers/xhci.h:172` | `int xhc_device_count(void);` |
| `xhc_device_info` | function | `headers/drivers/xhci.h:175` | `int xhc_device_info(int index, xhc_dev_t *out);` |
| `xhc_enumerate` | function | `headers/drivers/xhci.h:165` | `int xhc_enumerate(int port);` |
| `xhc_enumerate_all` | function | `headers/drivers/xhci.h:169` | `int xhc_enumerate_all(void);` |
| `xhc_iface_t` | struct | `headers/drivers/xhci.h:94` | `` |
| `xhc_info` | function | `headers/drivers/xhci.h:238` | `int xhc_info(unsigned *version, unsigned *slots, unsigned *ports, unsigned *caplength);` |
| `xhc_init` | function | `headers/drivers/xhci.h:140` | `int xhc_init(void);` |
| `xhc_open_interface` | function | `headers/drivers/xhci.h:186` | `int xhc_open_interface(int index, unsigned cls, unsigned sub, unsigned proto, xhc_iface_t *out);` |
| `xhc_poll` | function | `headers/drivers/xhci.h:146` | `int xhc_poll(void);` |
| `xhc_poll_token` | function | `headers/drivers/xhci.h:226` | `int xhc_poll_token(int token);` |
| `xhc_poll_token_limit` | function | `headers/drivers/xhci.h:225` | `int xhc_poll_token_limit(int token, unsigned budget_ms);` |
| `xhc_port_count` | function | `headers/drivers/xhci.h:150` | `int xhc_port_count(void);` |
| `xhc_port_reset` | function | `headers/drivers/xhci.h:159` | `int xhc_port_reset(int port);` |
| `xhc_port_state` | function | `headers/drivers/xhci.h:154` | `int xhc_port_state(int port, xhc_port_t *out);` |
| `xhc_port_t` | struct | `headers/drivers/xhci.h:107` | `` |
| `xhc_probe_note` | function | `headers/drivers/xhci.h:234` | `const char *xhc_probe_note(void);` |
| `xhc_reset_endpoint` | function | `headers/drivers/xhci.h:216` | `int xhc_reset_endpoint(int index, int ep_index);` |
| `xhc_transfer` | function | `headers/drivers/xhci.h:211` | `int xhc_transfer(int index, int ep_index, void *buf, unsigned len, int *got);` |
| `xhc_transfer_async` | function | `headers/drivers/xhci.h:220` | `int xhc_transfer_async(int index, int ep_index, void *buf, unsigned len);` |
| `EDITOR_H` | macro | `headers/editor.h:2` | `#define EDITOR_H` |
| `shell_cmd_edit` | function | `headers/editor.h:15` | `void shell_cmd_edit(int argc, char **argv);` |
| `EXT4_H` | macro | `headers/ext4.h:2` | `#define EXT4_H` |
| `EXT4_LIST_CAP` | macro | `headers/ext4.h:18` | `#define EXT4_LIST_CAP` |
| `EXT4_MAX_DEPTH` | macro | `headers/ext4.h:17` | `#define EXT4_MAX_DEPTH` |
| `EXT4_NAME_MAX` | macro | `headers/ext4.h:16` | `#define EXT4_NAME_MAX` |
| `EXT4_PATH_MAX` | macro | `headers/ext4.h:19` | `#define EXT4_PATH_MAX` |
| `ext4_handle_t` | struct | `headers/ext4.h:22` | `` |
| `ext4_list` | function | `headers/ext4.h:35` | `int ext4_list(const char *imgpath, const char *dirpath, char names[][EXT4_NAME_MAX + 1], int *isdir, int cap);` |
| `ext4_vfs_close` | function | `headers/ext4.h:45` | `int ext4_vfs_close(void *handle);` |
| `ext4_vfs_fstat` | function | `headers/ext4.h:46` | `int ext4_vfs_fstat(void *handle, unsigned long *size_out);` |
| `ext4_vfs_open` | function | `headers/ext4.h:40` | `int ext4_vfs_open(const char *path, int mode, void **handle);` |
| `ext4_vfs_ops` | variable | `headers/ext4.h:55` | `extern const vfs_ops_t ext4_vfs_ops;` |
| `ext4_vfs_read` | function | `headers/ext4.h:41` | `int ext4_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len);` |
| `ext4_vfs_truncate` | function | `headers/ext4.h:47` | `int ext4_vfs_truncate(void *handle, unsigned long size);` |
| `ext4_vfs_write` | function | `headers/ext4.h:43` | `int ext4_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len);` |
| `first` | function | `headers/ext4.h:50` | `* MBR 0x83 entry first (proven by a superblock read), then a magic * scan over 2048-aligned LBAs for superfloppy...` |
| `FAT32_CLUS_MAX` | macro | `headers/fat32.h:19` | `#define FAT32_CLUS_MAX` |
| `FAT32_H` | macro | `headers/fat32.h:2` | `#define FAT32_H` |
| `FAT32_LIST_CAP` | macro | `headers/fat32.h:18` | `#define FAT32_LIST_CAP` |
| `FAT32_MAX_DEPTH` | macro | `headers/fat32.h:17` | `#define FAT32_MAX_DEPTH` |
| `FAT32_NAME_MAX` | macro | `headers/fat32.h:16` | `#define FAT32_NAME_MAX` |
| `fat32_handle_t` | struct | `headers/fat32.h:25` | `` |
| `fat32_list` | function | `headers/fat32.h:45` | `int fat32_list(const char *imgpath, const char *dirpath, char names[][FAT32_NAME_MAX], int *isdir, int cap);` |
| `fat32_vfs_close` | function | `headers/fat32.h:63` | `int fat32_vfs_close(void *handle);` |
| `fat32_vfs_fstat` | function | `headers/fat32.h:64` | `int fat32_vfs_fstat(void *handle, unsigned long *size_out);` |
| `fat32_vfs_open` | function | `headers/fat32.h:58` | `int fat32_vfs_open(const char *path, int mode, void **handle);` |
| `fat32_vfs_ops` | variable | `headers/fat32.h:67` | `extern const vfs_ops_t fat32_vfs_ops;` |
| `fat32_vfs_read` | function | `headers/fat32.h:59` | `int fat32_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len);` |
| `fat32_vfs_truncate` | function | `headers/fat32.h:65` | `int fat32_vfs_truncate(void *handle, unsigned long size);` |
| `fat32_vfs_write` | function | `headers/fat32.h:61` | `int fat32_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len);` |
| `fat_dev_base` | function | `headers/fat32.h:54` | `long fat_dev_base(void);` |
| `file` | function | `headers/fat32.h:6` | `* * A FAT32 disk image stored as a regular file (built on the host with * mkfs.vfat, packed into minifs.bin) is...` |
| `FSIMG_H` | macro | `headers/fsimg.h:2` | `#define FSIMG_H` |
| `fsimg_open_dev` | function | `headers/fsimg.h:27` | `int fsimg_open_dev(unsigned long base_lba, unsigned long nsec, fsimg_t *img);` |
| `fsimg_open_file` | function | `headers/fsimg.h:23` | `int fsimg_open_file(const char *resolved, fsimg_t *img);` |
| `fsimg_read` | function | `headers/fsimg.h:32` | `int fsimg_read(const fsimg_t *img, unsigned long off, void *buf, unsigned long len);` |
| `fsimg_split` | function | `headers/fsimg.h:40` | `int fsimg_split(const char *path, char *left, unsigned llen, char *right, unsigned rlen);` |
| `fsimg_t` | struct | `headers/fsimg.h:13` | `` |
| `FUTEX_BUCKETS` | macro | `headers/futex.h:51` | `#define FUTEX_BUCKETS` |
| `FUTEX_BUCKET_MASK` | macro | `headers/futex.h:52` | `#define FUTEX_BUCKET_MASK` |
| `FUTEX_CLOCK_REALTIME` | function | `headers/futex.h:96` | `* FUTEX_CLOCK_REALTIME (it only selects the clock of a BITSET deadline). * Returns -1 for anything unserved...` |
| `FUTEX_H` | macro | `headers/futex.h:2` | `#define FUTEX_H` |
| `FUTEX_HASH_GOLDEN` | macro | `headers/futex.h:53` | `#define FUTEX_HASH_GOLDEN` |
| `FUTEX_NOMATCH` | macro | `headers/futex.h:56` | `#define FUTEX_NOMATCH` |
| `FUTEX_NOPROC` | macro | `headers/futex.h:57` | `#define FUTEX_NOPROC` |
| `FUTEX_NS_PER_S` | macro | `headers/futex.h:74` | `#define FUTEX_NS_PER_S` |
| `FUTEX_NS_PER_US` | macro | `headers/futex.h:73` | `#define FUTEX_NS_PER_US` |
| `FUTEX_OK` | macro | `headers/futex.h:55` | `#define FUTEX_OK` |
| `FUTEX_TIMEOUT_FOREVER` | macro | `headers/futex.h:78` | `#define FUTEX_TIMEOUT_FOREVER` |
| `FUTEX_TIMEOUT_INVALID` | macro | `headers/futex.h:77` | `#define FUTEX_TIMEOUT_INVALID` |
| `FUTEX_US_PER_S` | macro | `headers/futex.h:72` | `#define FUTEX_US_PER_S` |
| `FUTEX_WAKE_ALL` | macro | `headers/futex.h:58` | `#define FUTEX_WAKE_ALL` |
| `LINUX_FUTEX_BITSET_MATCH_ANY` | macro | `headers/futex.h:71` | `#define LINUX_FUTEX_BITSET_MATCH_ANY` |
| `LINUX_FUTEX_CLOCK_REALTIME` | macro | `headers/futex.h:70` | `#define LINUX_FUTEX_CLOCK_REALTIME` |
| `LINUX_FUTEX_PRIVATE_FLAG` | macro | `headers/futex.h:69` | `#define LINUX_FUTEX_PRIVATE_FLAG` |
| `LINUX_FUTEX_WAIT` | macro | `headers/futex.h:65` | `#define LINUX_FUTEX_WAIT` |
| `LINUX_FUTEX_WAIT_BITSET` | macro | `headers/futex.h:67` | `#define LINUX_FUTEX_WAIT_BITSET` |
| `LINUX_FUTEX_WAKE` | macro | `headers/futex.h:66` | `#define LINUX_FUTEX_WAKE` |
| `LINUX_FUTEX_WAKE_BITSET` | macro | `headers/futex.h:68` | `#define LINUX_FUTEX_WAKE_BITSET` |
| `futex_bucket_t` | struct | `headers/futex.h:80` | `` |
| `futex_forget` | function | `headers/futex.h:91` | `void futex_forget(int pid);` |
| `futex_init` | function | `headers/futex.h:86` | `void futex_init(void);` |
| `futex_linux_cmd` | function | `headers/futex.h:100` | `int futex_linux_cmd(long op);` |
| `futex_timeout_remaining_us` | function | `headers/futex.h:107` | `long futex_timeout_remaining_us(int cmd, long sec, long nsec, unsigned long now_us);` |
| `futex_wait` | function | `headers/futex.h:87` | `long futex_wait(unsigned long uaddr, int val);` |
| `futex_wake` | function | `headers/futex.h:88` | `long futex_wake(unsigned long uaddr, int n);` |
| `HTTPD_ERR_BOUND` | macro | `headers/httpd.h:21` | `#define HTTPD_ERR_BOUND` |
| `HTTPD_ERR_METHOD` | macro | `headers/httpd.h:22` | `#define HTTPD_ERR_METHOD` |
| `HTTPD_ERR_PATH` | macro | `headers/httpd.h:23` | `#define HTTPD_ERR_PATH` |
| `HTTPD_ERR_VERSION` | macro | `headers/httpd.h:24` | `#define HTTPD_ERR_VERSION` |
| `HTTPD_H` | macro | `headers/httpd.h:15` | `#define HTTPD_H` |
| `HTTPD_HEAD_MAX` | macro | `headers/httpd.h:19` | `#define HTTPD_HEAD_MAX` |
| `HTTPD_MAX_PATH` | macro | `headers/httpd.h:17` | `#define HTTPD_MAX_PATH` |
| `HTTPD_MAX_REQ` | macro | `headers/httpd.h:18` | `#define HTTPD_MAX_REQ` |
| `httpd_ctype` | function | `headers/httpd.h:28` | `static inline const char *httpd_ctype(const char *path)` |
| `httpd_header` | function | `headers/httpd.h:121` | `static inline int httpd_header(int code, const char *reason,         const char *ctype, unsigned ...` |
| `IDE_CMD_FLUSH` | macro | `headers/ide.h:35` | `#define IDE_CMD_FLUSH` |
| `IDE_CMD_IDENTIFY` | macro | `headers/ide.h:34` | `#define IDE_CMD_IDENTIFY` |
| `IDE_CMD_READ` | macro | `headers/ide.h:32` | `#define IDE_CMD_READ` |
| `IDE_CMD_WRITE` | macro | `headers/ide.h:33` | `#define IDE_CMD_WRITE` |
| `IDE_DRIVE_LBA` | macro | `headers/ide.h:38` | `#define IDE_DRIVE_LBA` |
| `IDE_DRIVE_MASTER` | macro | `headers/ide.h:39` | `#define IDE_DRIVE_MASTER` |
| `IDE_DRIVE_SLAVE` | macro | `headers/ide.h:40` | `#define IDE_DRIVE_SLAVE` |
| `IDE_H` | macro | `headers/ide.h:2` | `#define IDE_H` |
| `IDE_PRIMARY_BASE` | macro | `headers/ide.h:9` | `#define IDE_PRIMARY_BASE` |
| `IDE_PRIMARY_CTRL` | macro | `headers/ide.h:10` | `#define IDE_PRIMARY_CTRL` |
| `IDE_REG_ALTSTATUS` | macro | `headers/ide.h:21` | `#define IDE_REG_ALTSTATUS` |
| `IDE_REG_DATA` | macro | `headers/ide.h:13` | `#define IDE_REG_DATA` |
| `IDE_REG_DRIVE` | macro | `headers/ide.h:19` | `#define IDE_REG_DRIVE` |
| `IDE_REG_ERROR` | macro | `headers/ide.h:14` | `#define IDE_REG_ERROR` |
| `IDE_REG_LBA_HI` | macro | `headers/ide.h:18` | `#define IDE_REG_LBA_HI` |
| `IDE_REG_LBA_LO` | macro | `headers/ide.h:16` | `#define IDE_REG_LBA_LO` |
| `IDE_REG_LBA_MID` | macro | `headers/ide.h:17` | `#define IDE_REG_LBA_MID` |
| `IDE_REG_SECCOUNT` | macro | `headers/ide.h:15` | `#define IDE_REG_SECCOUNT` |
| `IDE_REG_STATUS` | macro | `headers/ide.h:20` | `#define IDE_REG_STATUS` |
| `IDE_SECTOR_SIZE` | macro | `headers/ide.h:46` | `#define IDE_SECTOR_SIZE` |
| `IDE_STATUS_BSY` | macro | `headers/ide.h:29` | `#define IDE_STATUS_BSY` |
| `IDE_STATUS_DF` | macro | `headers/ide.h:27` | `#define IDE_STATUS_DF` |
| `IDE_STATUS_DRQ` | macro | `headers/ide.h:25` | `#define IDE_STATUS_DRQ` |
| `IDE_STATUS_ERR` | macro | `headers/ide.h:24` | `#define IDE_STATUS_ERR` |
| `IDE_STATUS_RDY` | macro | `headers/ide.h:28` | `#define IDE_STATUS_RDY` |
| `IDE_STATUS_SRV` | macro | `headers/ide.h:26` | `#define IDE_STATUS_SRV` |
| `IDE_TIMEOUT` | macro | `headers/ide.h:43` | `#define IDE_TIMEOUT` |
| `ide_init` | function | `headers/ide.h:49` | `void ide_init(void);` |
| `ide_present` | function | `headers/ide.h:64` | `int ide_present(void);` |
| `ide_read_sector` | function | `headers/ide.h:57` | `int ide_read_sector(unsigned int lba, void *buf);` |
| `ide_read_sectors` | function | `headers/ide.h:53` | `int ide_read_sectors(unsigned int lba, unsigned int count, void *buf);` |
| `ide_register_device` | function | `headers/ide.h:68` | `void ide_register_device(void);` |
| `ide_total_sectors` | function | `headers/ide.h:61` | `unsigned int ide_total_sectors(void);` |
| `ide_write_sector` | function | `headers/ide.h:58` | `int ide_write_sector(unsigned int lba, const void *buf);` |
| `ide_write_sectors` | function | `headers/ide.h:54` | `int ide_write_sectors(unsigned int lba, unsigned int count, const void *buf);` |
| `ALIGN_UP` | macro | `headers/kernel.h:20` | `#define ALIGN_UP(x, a)` |
| `C` | function | `headers/kernel.h:903` | `* it with pointer subtraction in C (undefined behaviour). The value is  * a link-time difference,...` |
| `DEV_MMIO_VBASE` | macro | `headers/kernel.h:210` | `#define DEV_MMIO_VBASE` |
| `EBADF` | macro | `headers/kernel.h:511` | `#define EBADF` |
| `EFAULT` | macro | `headers/kernel.h:4` | `#define EFAULT` |
| `EFBIG` | macro | `headers/kernel.h:516` | `#define EFBIG` |
| `EINVAL` | macro | `headers/kernel.h:515` | `#define EINVAL` |
| `EIO` | macro | `headers/kernel.h:510` | `#define EIO` |
| `EISDIR` | macro | `headers/kernel.h:514` | `#define EISDIR` |
| `EI_NIDENT` | macro | `headers/kernel.h:730` | `#define EI_NIDENT` |
| `ENAMETOOLONG` | macro | `headers/kernel.h:519` | `#define ENAMETOOLONG` |
| `ENOENT` | macro | `headers/kernel.h:509` | `#define ENOENT` |
| `ENOMEM` | macro | `headers/kernel.h:512` | `#define ENOMEM` |
| `ENOSPC` | macro | `headers/kernel.h:517` | `#define ENOSPC` |
| `ENOTDIR` | macro | `headers/kernel.h:513` | `#define ENOTDIR` |
| `EOF` | macro | `headers/kernel.h:468` | `#define EOF` |
| `ESPIPE` | macro | `headers/kernel.h:518` | `#define ESPIPE` |
| `ETREL_TRUSTED_DIR` | macro | `headers/kernel.h:322` | `#define ETREL_TRUSTED_DIR` |
| `ETREL_TRUSTED_LEN` | macro | `headers/kernel.h:323` | `#define ETREL_TRUSTED_LEN` |
| `ET_DYN` | macro | `headers/kernel.h:757` | `#define ET_DYN` |
| `ET_EXEC` | macro | `headers/kernel.h:756` | `#define ET_EXEC` |
| `ET_REL` | macro | `headers/kernel.h:755` | `#define ET_REL` |
| `Elf64_Addr` | type_alias | `headers/kernel.h:731` | `typedef unsigned long long Elf64_Addr;` |
| `Elf64_Ehdr` | struct | `headers/kernel.h:738` | `` |
| `Elf64_Half` | type_alias | `headers/kernel.h:734` | `typedef unsigned short Elf64_Half;` |
| `Elf64_Off` | type_alias | `headers/kernel.h:732` | `typedef unsigned long long Elf64_Off;` |
| `Elf64_Sxword` | type_alias | `headers/kernel.h:736` | `typedef long long Elf64_Sxword;` |
| `Elf64_Word` | type_alias | `headers/kernel.h:733` | `typedef unsigned int Elf64_Word;` |
| `Elf64_Xword` | type_alias | `headers/kernel.h:735` | `typedef unsigned long long Elf64_Xword;` |
| `HEAP_BASE` | macro | `headers/kernel.h:204` | `#define HEAP_BASE` |
| `HEAP_SIZE` | macro | `headers/kernel.h:205` | `#define HEAP_SIZE` |
| `KERNEL_H` | macro | `headers/kernel.h:2` | `#define KERNEL_H` |
| `KEVENT_MAX` | macro | `headers/kernel.h:881` | `#define KEVENT_MAX` |
| `KEY_ARR_DOWN` | macro | `headers/kernel.h:151` | `#define KEY_ARR_DOWN` |
| `KEY_ARR_LEFT` | macro | `headers/kernel.h:153` | `#define KEY_ARR_LEFT` |
| `KEY_ARR_RIGHT` | macro | `headers/kernel.h:152` | `#define KEY_ARR_RIGHT` |
| `KEY_ARR_UP` | macro | `headers/kernel.h:150` | `#define KEY_ARR_UP` |
| `KEY_BACKSPACE` | macro | `headers/kernel.h:138` | `#define KEY_BACKSPACE` |
| `KEY_CAPS` | macro | `headers/kernel.h:142` | `#define KEY_CAPS` |
| `KEY_CSI` | macro | `headers/kernel.h:149` | `#define KEY_CSI` |
| `KEY_DOWN` | macro | `headers/kernel.h:145` | `#define KEY_DOWN` |
| `KEY_E0` | macro | `headers/kernel.h:143` | `#define KEY_E0` |
| `KEY_END` | macro | `headers/kernel.h:168` | `#define KEY_END` |
| `KEY_END_SEQ` | macro | `headers/kernel.h:155` | `#define KEY_END_SEQ` |
| `KEY_ENTER` | macro | `headers/kernel.h:139` | `#define KEY_ENTER` |
| `KEY_ESC` | macro | `headers/kernel.h:148` | `#define KEY_ESC` |
| `KEY_F11` | macro | `headers/kernel.h:163` | `#define KEY_F11` |
| `KEY_F5` | macro | `headers/kernel.h:162` | `#define KEY_F5` |
| `KEY_HOME` | macro | `headers/kernel.h:167` | `#define KEY_HOME` |
| `KEY_HOME_SEQ` | macro | `headers/kernel.h:154` | `#define KEY_HOME_SEQ` |
| `KEY_LALT` | macro | `headers/kernel.h:165` | `#define KEY_LALT` |
| `KEY_LCTRL` | macro | `headers/kernel.h:160` | `#define KEY_LCTRL` |
| `KEY_LEFT` | macro | `headers/kernel.h:158` | `#define KEY_LEFT` |
| `KEY_LSHIFT` | macro | `headers/kernel.h:140` | `#define KEY_LSHIFT` |
| `KEY_PGDN` | macro | `headers/kernel.h:147` | `#define KEY_PGDN` |
| `KEY_PGDN_SEQ` | macro | `headers/kernel.h:157` | `#define KEY_PGDN_SEQ` |
| `KEY_PGUP` | macro | `headers/kernel.h:146` | `#define KEY_PGUP` |
| `KEY_PGUP_SEQ` | macro | `headers/kernel.h:156` | `#define KEY_PGUP_SEQ` |
| `KEY_RALT` | macro | `headers/kernel.h:166` | `#define KEY_RALT` |
| `KEY_RCTRL` | macro | `headers/kernel.h:161` | `#define KEY_RCTRL` |
| `KEY_RIGHT` | macro | `headers/kernel.h:159` | `#define KEY_RIGHT` |
| `KEY_RSHIFT` | macro | `headers/kernel.h:141` | `#define KEY_RSHIFT` |
| `KEY_SUPER_L` | macro | `headers/kernel.h:170` | `#define KEY_SUPER_L` |
| `KEY_SUPER_R` | macro | `headers/kernel.h:171` | `#define KEY_SUPER_R` |
| `KEY_TAB` | macro | `headers/kernel.h:169` | `#define KEY_TAB` |
| `KEY_TILDE` | macro | `headers/kernel.h:164` | `#define KEY_TILDE` |
| `KEY_UP` | macro | `headers/kernel.h:144` | `#define KEY_UP` |
| `KFD_MAX` | macro | `headers/kernel.h:845` | `#define KFD_MAX` |
| `KFILE` | struct | `headers/kernel.h:470` | `` |
| `KMALLOC_PAGE` | macro | `headers/kernel.h:220` | `#define KMALLOC_PAGE` |
| `KPROG_MAX` | macro | `headers/kernel.h:625` | `#define KPROG_MAX` |
| `KProg` | struct | `headers/kernel.h:632` | `` |
| `KSYM_MAX` | macro | `headers/kernel.h:624` | `#define KSYM_MAX` |
| `KSym` | struct | `headers/kernel.h:627` | `` |
| `LDSO_REGION_BASE` | macro | `headers/kernel.h:194` | `#define LDSO_REGION_BASE` |
| `LDSO_REGION_END` | macro | `headers/kernel.h:196` | `#define LDSO_REGION_END` |
| `LDSO_REGION_SIZE` | macro | `headers/kernel.h:195` | `#define LDSO_REGION_SIZE` |
| `LINUX_PROT_EXEC` | macro | `headers/kernel.h:804` | `#define LINUX_PROT_EXEC` |
| `LINUX_PROT_READ` | macro | `headers/kernel.h:802` | `#define LINUX_PROT_READ` |
| `LINUX_PROT_WRITE` | macro | `headers/kernel.h:803` | `#define LINUX_PROT_WRITE` |
| `PCI_MMIO_SIZE` | macro | `headers/kernel.h:211` | `#define PCI_MMIO_SIZE` |
| `PORT_IO_DEFINED` | macro | `headers/kernel.h:22` | `#define PORT_IO_DEFINED` |
| `PTE_DEMAND` | macro | `headers/kernel.h:798` | `#define PTE_DEMAND` |
| `PTE_DEMAND_EXEC` | macro | `headers/kernel.h:801` | `#define PTE_DEMAND_EXEC` |
| `PTE_DEMAND_READ` | macro | `headers/kernel.h:799` | `#define PTE_DEMAND_READ` |

Next: [SYMBOLS_p5.md](SYMBOLS_p5.md)
