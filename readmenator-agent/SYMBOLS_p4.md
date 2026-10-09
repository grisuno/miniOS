# Symbols (page 4 of 25)
Previous: [SYMBOLS_p3.md](SYMBOLS_p3.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `PCI_SUBCLASS_XHCI` | macro | `headers/drivers/pci.h:58` | `#define PCI_SUBCLASS_XHCI` |
| `pci_bar_base` | function | `headers/drivers/pci.h:406` | `static inline unsigned long long pci_bar_base(unsigned bus, unsigned dev,         unsigned func, ...` |
| `pci_bar_count` | function | `headers/drivers/pci.h:248` | `static inline unsigned pci_bar_count(unsigned bus, unsigned dev, unsigned func,         void (*ou...` |
| `pci_bar_ctz32` | function | `headers/drivers/pci.h:284` | `static inline unsigned pci_bar_ctz32(unsigned val)` |
| `pci_bar_is_64bit` | function | `headers/drivers/pci.h:274` | `static inline int pci_bar_is_64bit(unsigned bus, unsigned dev, unsigned func,         unsigned ba...` |
| `pci_bar_is_io` | function | `headers/drivers/pci.h:263` | `static inline int pci_bar_is_io(unsigned bus, unsigned dev, unsigned func,         unsigned bar, ...` |
| `pci_bar_relocate` | function | `headers/drivers/pci.h:382` | `static inline int pci_bar_relocate(unsigned bus, unsigned dev, unsigned func,         unsigned ba...` |
| `pci_bar_restore` | function | `headers/drivers/pci.h:424` | `static inline void pci_bar_restore(unsigned bus, unsigned dev,         unsigned func, unsigned ba...` |
| `pci_bar_size` | function | `headers/drivers/pci.h:346` | `static inline unsigned long long pci_bar_size(unsigned bus, unsigned dev,         unsigned func, ...` |
| `pci_bar_size_from_mask` | function | `headers/drivers/pci.h:315` | `static inline unsigned long long pci_bar_size_from_mask(unsigned long long mask)` |
| `pci_bdf_t` | struct | `headers/drivers/pci.h:71` | `` |
| `pci_cfg_read` | function | `headers/drivers/pci.h:80` | `static inline unsigned pci_cfg_read(unsigned bus, unsigned dev,         unsigned func, unsigned r...` |
| `pci_cfg_read8` | function | `headers/drivers/pci.h:100` | `static inline unsigned char pci_cfg_read8(unsigned bus, unsigned dev,         unsigned func, unsi...` |
| `pci_cfg_write` | function | `headers/drivers/pci.h:90` | `static inline void pci_cfg_write(unsigned bus, unsigned dev,         unsigned func, unsigned reg,...` |
| `pci_cfg_write8` | function | `headers/drivers/pci.h:109` | `static inline void pci_cfg_write8(unsigned bus, unsigned dev,         unsigned func, unsigned reg...` |
| `pci_find` | function | `headers/drivers/pci.h:165` | `static inline int pci_find(unsigned vendor, unsigned device,         unsigned (*inl)(unsigned sho...` |
| `pci_find_class` | function | `headers/drivers/pci.h:193` | `static inline int pci_find_class(pci_bdf_t *out,         unsigned cls, unsigned subclass, unsigne...` |
| `pci_is_multifunction` | function | `headers/drivers/pci.h:152` | `static inline int pci_is_multifunction(unsigned bus, unsigned dev,         void (*outl)(unsigned ...` |
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
| `FUTEX_H` | macro | `headers/futex.h:2` | `#define FUTEX_H` |
| `FUTEX_HASH_GOLDEN` | macro | `headers/futex.h:53` | `#define FUTEX_HASH_GOLDEN` |
| `FUTEX_NOMATCH` | macro | `headers/futex.h:56` | `#define FUTEX_NOMATCH` |
| `FUTEX_NOPROC` | macro | `headers/futex.h:57` | `#define FUTEX_NOPROC` |
| `FUTEX_OK` | macro | `headers/futex.h:55` | `#define FUTEX_OK` |
| `FUTEX_PRIVATE_FLAG` | function | `headers/futex.h:79` | `* FUTEX_PRIVATE_FLAG (process-private is served on the same global * buckets: same semantics, no isolation...` |
| `FUTEX_WAKE_ALL` | macro | `headers/futex.h:58` | `#define FUTEX_WAKE_ALL` |
| `LINUX_FUTEX_PRIVATE_FLAG` | macro | `headers/futex.h:66` | `#define LINUX_FUTEX_PRIVATE_FLAG` |
| `LINUX_FUTEX_WAIT` | macro | `headers/futex.h:64` | `#define LINUX_FUTEX_WAIT` |
| `LINUX_FUTEX_WAKE` | macro | `headers/futex.h:65` | `#define LINUX_FUTEX_WAKE` |
| `futex_bucket_t` | struct | `headers/futex.h:68` | `` |
| `futex_init` | function | `headers/futex.h:74` | `void futex_init(void);` |
| `futex_linux_cmd` | function | `headers/futex.h:84` | `int futex_linux_cmd(long op);` |
| `futex_wait` | function | `headers/futex.h:75` | `long futex_wait(unsigned long uaddr, int val);` |
| `futex_wake` | function | `headers/futex.h:76` | `long futex_wake(unsigned long uaddr, int n);` |
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
| `C` | function | `headers/kernel.h:837` | `* it with pointer subtraction in C (undefined behaviour). The value is  * a link-time difference,...` |
| `DEV_MMIO_VBASE` | macro | `headers/kernel.h:209` | `#define DEV_MMIO_VBASE` |
| `EBADF` | macro | `headers/kernel.h:484` | `#define EBADF` |
| `EFAULT` | macro | `headers/kernel.h:4` | `#define EFAULT` |
| `EFBIG` | macro | `headers/kernel.h:489` | `#define EFBIG` |
| `EINVAL` | macro | `headers/kernel.h:488` | `#define EINVAL` |
| `EIO` | macro | `headers/kernel.h:483` | `#define EIO` |
| `EISDIR` | macro | `headers/kernel.h:487` | `#define EISDIR` |
| `EI_NIDENT` | macro | `headers/kernel.h:703` | `#define EI_NIDENT` |
| `ENAMETOOLONG` | macro | `headers/kernel.h:492` | `#define ENAMETOOLONG` |
| `ENOENT` | macro | `headers/kernel.h:482` | `#define ENOENT` |
| `ENOMEM` | macro | `headers/kernel.h:485` | `#define ENOMEM` |
| `ENOSPC` | macro | `headers/kernel.h:490` | `#define ENOSPC` |
| `ENOTDIR` | macro | `headers/kernel.h:486` | `#define ENOTDIR` |
| `EOF` | macro | `headers/kernel.h:452` | `#define EOF` |
| `ESPIPE` | macro | `headers/kernel.h:491` | `#define ESPIPE` |
| `ETREL_TRUSTED_DIR` | macro | `headers/kernel.h:306` | `#define ETREL_TRUSTED_DIR` |
| `ETREL_TRUSTED_LEN` | macro | `headers/kernel.h:307` | `#define ETREL_TRUSTED_LEN` |
| `ET_DYN` | macro | `headers/kernel.h:730` | `#define ET_DYN` |
| `ET_EXEC` | macro | `headers/kernel.h:729` | `#define ET_EXEC` |
| `ET_REL` | macro | `headers/kernel.h:728` | `#define ET_REL` |
| `Elf64_Addr` | type_alias | `headers/kernel.h:704` | `typedef unsigned long long Elf64_Addr;` |
| `Elf64_Ehdr` | struct | `headers/kernel.h:711` | `` |
| `Elf64_Half` | type_alias | `headers/kernel.h:707` | `typedef unsigned short Elf64_Half;` |
| `Elf64_Off` | type_alias | `headers/kernel.h:705` | `typedef unsigned long long Elf64_Off;` |
| `Elf64_Sxword` | type_alias | `headers/kernel.h:709` | `typedef long long Elf64_Sxword;` |
| `Elf64_Word` | type_alias | `headers/kernel.h:706` | `typedef unsigned int Elf64_Word;` |
| `Elf64_Xword` | type_alias | `headers/kernel.h:708` | `typedef unsigned long long Elf64_Xword;` |
| `HEAP_BASE` | macro | `headers/kernel.h:203` | `#define HEAP_BASE` |
| `HEAP_SIZE` | macro | `headers/kernel.h:204` | `#define HEAP_SIZE` |
| `KERNEL_H` | macro | `headers/kernel.h:2` | `#define KERNEL_H` |
| `KEY_ARR_DOWN` | macro | `headers/kernel.h:150` | `#define KEY_ARR_DOWN` |
| `KEY_ARR_LEFT` | macro | `headers/kernel.h:152` | `#define KEY_ARR_LEFT` |
| `KEY_ARR_RIGHT` | macro | `headers/kernel.h:151` | `#define KEY_ARR_RIGHT` |
| `KEY_ARR_UP` | macro | `headers/kernel.h:149` | `#define KEY_ARR_UP` |
| `KEY_BACKSPACE` | macro | `headers/kernel.h:137` | `#define KEY_BACKSPACE` |
| `KEY_CAPS` | macro | `headers/kernel.h:141` | `#define KEY_CAPS` |
| `KEY_CSI` | macro | `headers/kernel.h:148` | `#define KEY_CSI` |
| `KEY_DOWN` | macro | `headers/kernel.h:144` | `#define KEY_DOWN` |
| `KEY_E0` | macro | `headers/kernel.h:142` | `#define KEY_E0` |
| `KEY_END` | macro | `headers/kernel.h:167` | `#define KEY_END` |
| `KEY_END_SEQ` | macro | `headers/kernel.h:154` | `#define KEY_END_SEQ` |
| `KEY_ENTER` | macro | `headers/kernel.h:138` | `#define KEY_ENTER` |
| `KEY_ESC` | macro | `headers/kernel.h:147` | `#define KEY_ESC` |
| `KEY_F11` | macro | `headers/kernel.h:162` | `#define KEY_F11` |
| `KEY_F5` | macro | `headers/kernel.h:161` | `#define KEY_F5` |
| `KEY_HOME` | macro | `headers/kernel.h:166` | `#define KEY_HOME` |
| `KEY_HOME_SEQ` | macro | `headers/kernel.h:153` | `#define KEY_HOME_SEQ` |
| `KEY_LALT` | macro | `headers/kernel.h:164` | `#define KEY_LALT` |
| `KEY_LCTRL` | macro | `headers/kernel.h:159` | `#define KEY_LCTRL` |
| `KEY_LEFT` | macro | `headers/kernel.h:157` | `#define KEY_LEFT` |
| `KEY_LSHIFT` | macro | `headers/kernel.h:139` | `#define KEY_LSHIFT` |
| `KEY_PGDN` | macro | `headers/kernel.h:146` | `#define KEY_PGDN` |
| `KEY_PGDN_SEQ` | macro | `headers/kernel.h:156` | `#define KEY_PGDN_SEQ` |
| `KEY_PGUP` | macro | `headers/kernel.h:145` | `#define KEY_PGUP` |
| `KEY_PGUP_SEQ` | macro | `headers/kernel.h:155` | `#define KEY_PGUP_SEQ` |
| `KEY_RALT` | macro | `headers/kernel.h:165` | `#define KEY_RALT` |
| `KEY_RCTRL` | macro | `headers/kernel.h:160` | `#define KEY_RCTRL` |
| `KEY_RIGHT` | macro | `headers/kernel.h:158` | `#define KEY_RIGHT` |
| `KEY_RSHIFT` | macro | `headers/kernel.h:140` | `#define KEY_RSHIFT` |
| `KEY_SUPER_L` | macro | `headers/kernel.h:169` | `#define KEY_SUPER_L` |
| `KEY_SUPER_R` | macro | `headers/kernel.h:170` | `#define KEY_SUPER_R` |
| `KEY_TAB` | macro | `headers/kernel.h:168` | `#define KEY_TAB` |
| `KEY_TILDE` | macro | `headers/kernel.h:163` | `#define KEY_TILDE` |
| `KEY_UP` | macro | `headers/kernel.h:143` | `#define KEY_UP` |
| `KFD_MAX` | macro | `headers/kernel.h:795` | `#define KFD_MAX` |
| `KFILE` | struct | `headers/kernel.h:454` | `` |
| `KPROG_MAX` | macro | `headers/kernel.h:598` | `#define KPROG_MAX` |
| `KProg` | struct | `headers/kernel.h:605` | `` |
| `KSYM_MAX` | macro | `headers/kernel.h:597` | `#define KSYM_MAX` |
| `KSym` | struct | `headers/kernel.h:600` | `` |
| `LDSO_REGION_BASE` | macro | `headers/kernel.h:193` | `#define LDSO_REGION_BASE` |
| `LDSO_REGION_END` | macro | `headers/kernel.h:195` | `#define LDSO_REGION_END` |
| `LDSO_REGION_SIZE` | macro | `headers/kernel.h:194` | `#define LDSO_REGION_SIZE` |
| `PCI_MMIO_SIZE` | macro | `headers/kernel.h:210` | `#define PCI_MMIO_SIZE` |
| `PORT_IO_DEFINED` | macro | `headers/kernel.h:22` | `#define PORT_IO_DEFINED` |
| `RAMDISK_FNAME_LEN` | macro | `headers/kernel.h:263` | `#define RAMDISK_FNAME_LEN` |
| `RAMDISK_FNAME_LEN` | function | `headers/kernel.h:279` | `* RAMDISK_FNAME_LEN (fs_resolve guarantees it);` |
| `RAMDISK_MAX_FILES` | macro | `headers/kernel.h:262` | `#define RAMDISK_MAX_FILES` |
| `RDFile` | struct | `headers/kernel.h:265` | `` |
| `RD_DATA_MAX` | macro | `headers/kernel.h:289` | `#define RD_DATA_MAX` |
| `SYS_KSTK_BASE` | macro | `headers/kernel.h:201` | `#define SYS_KSTK_BASE` |
| `SYS_KSTK_TOP` | macro | `headers/kernel.h:200` | `#define SYS_KSTK_TOP` |
| `USER_BRK_END` | macro | `headers/kernel.h:189` | `#define USER_BRK_END` |
| `USER_HEAP_CEIL` | macro | `headers/kernel.h:737` | `#define USER_HEAP_CEIL` |
| `USER_LOAD_BASE` | macro | `headers/kernel.h:184` | `#define USER_LOAD_BASE` |
| `USER_LOAD_END` | macro | `headers/kernel.h:185` | `#define USER_LOAD_END` |
| `USER_STACK_BASE` | macro | `headers/kernel.h:188` | `#define USER_STACK_BASE` |
| `USER_STACK_SIZE` | macro | `headers/kernel.h:186` | `#define USER_STACK_SIZE` |
| `USER_STACK_TOP` | macro | `headers/kernel.h:187` | `#define USER_STACK_TOP` |
| `VFS_DRIVER_LEN` | macro | `headers/kernel.h:405` | `#define VFS_DRIVER_LEN` |
| `VFS_MAX_MOUNTS` | macro | `headers/kernel.h:403` | `#define VFS_MAX_MOUNTS` |
| `VFS_NAME_MAX` | macro | `headers/kernel.h:366` | `#define VFS_NAME_MAX` |
| `VFS_PREFIX_LEN` | macro | `headers/kernel.h:404` | `#define VFS_PREFIX_LEN` |
| `VGA_BASE` | macro | `headers/kernel.h:90` | `#define VGA_BASE` |
| `VGA_COLS` | macro | `headers/kernel.h:91` | `#define VGA_COLS` |
| `VGA_ROWS` | macro | `headers/kernel.h:92` | `#define VGA_ROWS` |
| `block_init` | function | `headers/kernel.h:874` | `void block_init(void);` |
| `block_read` | function | `headers/kernel.h:875` | `int block_read(unsigned int block_num, void *buf);` |
| `block_read_multi` | function | `headers/kernel.h:877` | `int block_read_multi(unsigned int block_num, unsigned int count, void *buf);` |
| `block_total` | function | `headers/kernel.h:879` | `unsigned int block_total(void);` |
| `block_write` | function | `headers/kernel.h:876` | `int block_write(unsigned int block_num, const void *buf);` |
| `block_write_multi` | function | `headers/kernel.h:878` | `int block_write_multi(unsigned int block_num, unsigned int count, const void *buf);` |
| `bootlog_mark` | function | `headers/kernel.h:851` | `void bootlog_mark(const char *name);` |
| `bootlog_report` | function | `headers/kernel.h:852` | `void bootlog_report(void);` |
| `clip_clear` | function | `headers/kernel.h:586` | `void clip_clear(void);` |
| `clip_get` | function | `headers/kernel.h:585` | `int clip_get(char *out, unsigned long cap);` |
| `clip_len_get` | function | `headers/kernel.h:587` | `int clip_len_get(void);` |
| `clip_set` | function | `headers/kernel.h:584` | `int clip_set(const char *data, unsigned long len);` |
| `console_getc` | function | `headers/kernel.h:563` | `int console_getc(void);` |
| `console_lock` | variable | `headers/kernel.h:105` | `extern spinlock_t console_lock;` |
| `console_peek` | function | `headers/kernel.h:564` | `int console_peek(void);` |
| `console_stdin_active` | function | `headers/kernel.h:577` | `int console_stdin_active(void);` |
| `console_stdin_clear` | function | `headers/kernel.h:576` | `void console_stdin_clear(void);` |
| `console_stdin_push` | function | `headers/kernel.h:575` | `int console_stdin_push(const char *data, unsigned long len);` |
| `cow_page_shared` | function | `headers/kernel.h:781` | `int cow_page_shared(unsigned long phys);` |
| `cow_release_window` | function | `headers/kernel.h:779` | `void cow_release_window(unsigned long cr3);` |
| `cow_resolve` | function | `headers/kernel.h:778` | `int cow_resolve(unsigned long cr3, unsigned long va);` |
| `cow_shared` | function | `headers/kernel.h:780` | `int cow_shared(void);` |
| `desktop_launch` | function | `headers/kernel.h:651` | `void desktop_launch(const char *cmd);` |
| `dlmalloc_calloc` | function | `headers/kernel.h:226` | `void *dlmalloc_calloc(unsigned long nmemb, unsigned long size);` |
| `dlmalloc_free` | function | `headers/kernel.h:225` | `void dlmalloc_free(void *ptr);` |
| `dlmalloc_init` | function | `headers/kernel.h:223` | `void dlmalloc_init(void);` |
| `dlmalloc_malloc` | function | `headers/kernel.h:224` | `void *dlmalloc_malloc(unsigned long size);` |
| `dlmalloc_realloc` | function | `headers/kernel.h:227` | `void *dlmalloc_realloc(void *ptr, unsigned long size);` |
| `dlmalloc_usage` | function | `headers/kernel.h:229` | `void dlmalloc_usage(unsigned long *used, unsigned long *free_b, unsigned long *arena);` |
| `elf_load` | function | `headers/kernel.h:739` | `void *elf_load(void *data, unsigned size, void **base_out);` |
| `exec_exit_code` | variable | `headers/kernel.h:643` | `extern int exec_exit_code;` |
| `exec_return` | variable | `headers/kernel.h:642` | `extern kjmpbuf exec_return;` |
| `fault` | function | `headers/kernel.h:775` | `* fixes one write fault (0 = resume), cow_release_window drops a * dying window's shares ahead of pt_free_user. */...` |
| `fd_lock` | variable | `headers/kernel.h:814` | `extern spinlock_t fd_lock;` |
| `fd_lock` | function | `headers/kernel.h:823` | `* fd_lock (never nested, never held across yields);` |
| `file_operations` | type_alias | `headers/kernel.h:398` | `typedef vfs_ops_t file_operations;` |
| `fs_cwd` | variable | `headers/kernel.h:418` | `extern char fs_cwd[];` |
| `fs_dir_exists` | function | `headers/kernel.h:296` | `int fs_dir_exists(const char *dir);` |
| `fs_is_dir` | function | `headers/kernel.h:297` | `int fs_is_dir(const char *resolved);` |
| `fs_lock` | variable | `headers/kernel.h:825` | `extern spinlock_t fs_lock;` |
| `fs_rename` | function | `headers/kernel.h:497` | `int fs_rename(const char *oldr, const char *newr);` |
| `fs_resolve` | function | `headers/kernel.h:295` | `int fs_resolve(const char *path, char *out, unsigned cap);` |
| `g_brk` | variable | `headers/kernel.h:696` | `extern unsigned long g_brk;` |
| `g_brk_limit` | variable | `headers/kernel.h:697` | `extern unsigned long g_brk_limit;` |
| `ide_init` | function | `headers/kernel.h:865` | `void ide_init(void);` |
| `ide_present` | function | `headers/kernel.h:871` | `int ide_present(void);` |
| `ide_read_sector` | function | `headers/kernel.h:868` | `int ide_read_sector(unsigned int lba, void *buf);` |
| `ide_read_sectors` | function | `headers/kernel.h:866` | `int ide_read_sectors(unsigned int lba, unsigned int count, void *buf);` |
| `ide_total_sectors` | function | `headers/kernel.h:870` | `unsigned int ide_total_sectors(void);` |
| `ide_write_sector` | function | `headers/kernel.h:869` | `int ide_write_sector(unsigned int lba, const void *buf);` |
| `ide_write_sectors` | function | `headers/kernel.h:867` | `int ide_write_sectors(unsigned int lba, unsigned int count, const void *buf);` |
| `inb` | function | `headers/kernel.h:29` | `static inline unsigned char inb(unsigned short port)` |
| `insw` | function | `headers/kernel.h:47` | `static inline void insw(unsigned short port, unsigned short *buf,                         unsigne...` |
| `inw` | function | `headers/kernel.h:37` | `static inline unsigned short inw(unsigned short port)` |
| `k_exec_user` | function | `headers/kernel.h:630` | `int k_exec_user(void *entry, int argc, char **argv);` |
| `k_register_process` | function | `headers/kernel.h:622` | `void k_register_process(const char *name, void *proc_entry);` |
| `k_register_program` | function | `headers/kernel.h:621` | `void k_register_program(const char *name, prog_entry_t entry);` |
| `k_register_symbol` | function | `headers/kernel.h:623` | `void k_register_symbol(const char *name, void *addr);` |
| `k_run_on_stack` | function | `headers/kernel.h:635` | `int k_run_on_stack(void *stack_top, prog_entry_t entry, int argc, char **argv);` |
| `k_run_rel` | function | `headers/kernel.h:631` | `int k_run_rel(prog_entry_t entry, int argc, char **argv);` |
| `k_spawn` | function | `headers/kernel.h:620` | `int k_spawn(const char *name, int argc, char **argv);` |
| `k_user_fault_return` | function | `headers/kernel.h:882` | `void k_user_fault_return(void);` |
| `kallocator_init` | function | `headers/kernel.h:217` | `void kallocator_init(void);` |
| `katol` | function | `headers/kernel.h:530` | `long katol(const char *s);` |
| `kbd_available` | function | `headers/kernel.h:173` | `int kbd_available(void);` |
| `kbd_read` | function | `headers/kernel.h:172` | `int kbd_read(void);` |
| `kbd_reset_for_shell` | function | `headers/kernel.h:174` | `void kbd_reset_for_shell(void);` |
| `kcalloc` | function | `headers/kernel.h:215` | `void *kcalloc(unsigned long nmemb, unsigned long size);` |
| `kernel_end` | variable | `headers/kernel.h:828` | `extern unsigned long kernel_end;` |
| `kerrno` | variable | `headers/kernel.h:494` | `extern int kerrno;` |
| `kexit` | function | `headers/kernel.h:632` | `void kexit(int code);` |
| `kfclose` | function | `headers/kernel.h:473` | `int kfclose(KFILE *f);` |
| `kfd_get` | function | `headers/kernel.h:815` | `KFILE *kfd_get(int fd);` |
| `kfd_override` | function | `headers/kernel.h:817` | `KFILE *kfd_override(int fd, KFILE *f);` |
| `kfd_put` | function | `headers/kernel.h:816` | `void kfd_put(KFILE *f);` |
| `kfd_view` | struct | `headers/kernel.h:805` | `` |
| `kfflush` | function | `headers/kernel.h:507` | `int kfflush(KFILE *f);` |
| `kfgetc` | function | `headers/kernel.h:498` | `int kfgetc(KFILE *f);` |
| `kfgets` | function | `headers/kernel.h:499` | `char *kfgets(char *buf, int size, KFILE *f);` |
| `kfile_stderr` | function | `headers/kernel.h:515` | `KFILE *kfile_stderr(void);` |
| `kfile_stdin` | function | `headers/kernel.h:513` | `KFILE *kfile_stdin(void);` |
| `kfile_stdout` | function | `headers/kernel.h:514` | `KFILE *kfile_stdout(void);` |
| `kfopen` | function | `headers/kernel.h:472` | `KFILE *kfopen(const char *path, const char *mode);` |
| `kfprintf` | function | `headers/kernel.h:534` | `int kfprintf(KFILE *f, const char *fmt, ...);` |
| `kfputc` | function | `headers/kernel.h:506` | `int kfputc(int c, KFILE *f);` |
| `kfputs` | function | `headers/kernel.h:505` | `int kfputs(const char *s, KFILE *f);` |
| `kfread` | function | `headers/kernel.h:501` | `unsigned long kfread(void *ptr, unsigned long size, unsigned long nmemb, KFILE *f);` |
| `kfree` | function | `headers/kernel.h:214` | `void kfree(void *ptr);` |
| `kfree_aligned` | function | `headers/kernel.h:219` | `void kfree_aligned(void *ptr);` |
| `kfseek` | function | `headers/kernel.h:503` | `int kfseek(KFILE *f, long offset, int whence);` |
| `kftell` | function | `headers/kernel.h:504` | `long kftell(KFILE *f);` |
| `kfungetc` | function | `headers/kernel.h:500` | `int kfungetc(int c, KFILE *f);` |
| `kfwrite` | function | `headers/kernel.h:502` | `unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long nmemb, KFILE *f);` |
| `kjmpbuf` | struct | `headers/kernel.h:639` | `` |
| `klog` | function | `headers/kernel.h:551` | `void klog(log_level_t level, log_subsystem_t subsys, const char *fmt, ...);` |
| `klog_disable` | function | `headers/kernel.h:557` | `void klog_disable(void);` |
| `klog_enable` | function | `headers/kernel.h:558` | `void klog_enable(void);` |
| `klog_hexdump` | function | `headers/kernel.h:553` | `void klog_hexdump(log_level_t level, log_subsystem_t subsys, const void *data, unsigned long len, const char *label);` |
| `klog_set_level` | function | `headers/kernel.h:555` | `void klog_set_level(log_level_t level);` |
| `klog_set_subsys_level` | function | `headers/kernel.h:556` | `void klog_set_subsys_level(log_subsystem_t subsys, log_level_t level);` |
| `klongjmp` | function | `headers/kernel.h:641` | `void klongjmp(void *buf, int val) __attribute__((noreturn));` |
| `kmalloc` | function | `headers/kernel.h:212` | `void *kmalloc(unsigned long size);` |
| `kmalloc_aligned` | function | `headers/kernel.h:218` | `void *kmalloc_aligned(unsigned long size, unsigned long align);` |
| `kmalloc_fail_after` | variable | `headers/kernel.h:213` | `extern long kmalloc_fail_after;` |
| `kmemcmp` | function | `headers/kernel.h:528` | `int kmemcmp(const void *a, const void *b, unsigned long n);` |
| `kmemcpy` | function | `headers/kernel.h:526` | `void *kmemcpy(void *dst, const void *src, unsigned long n);` |
| `kmemmove` | function | `headers/kernel.h:529` | `void *kmemmove(void *dst, const void *src, unsigned long n);` |
| `kmemset` | function | `headers/kernel.h:527` | `void *kmemset(void *dst, int c, unsigned long n);` |
| `kmm_make_uncached` | function | `headers/kernel.h:770` | `int kmm_make_uncached(unsigned long phys, unsigned long len);` |
| `kpipe_empty_wopen` | function | `headers/kernel.h:819` | `int kpipe_empty_wopen(KFILE *f);` |
| `kpipe_is_write_end` | function | `headers/kernel.h:820` | `int kpipe_is_write_end(KFILE *f);` |
| `kpipe_pair` | function | `headers/kernel.h:818` | `int kpipe_pair(KFILE **rend_out, KFILE **wend_out);` |
| `kprintf` | function | `headers/kernel.h:533` | `int kprintf(const char *fmt, ...);` |
| `kprog_count` | variable | `headers/kernel.h:615` | `extern int kprog_count;` |
| `kprog_lookup` | function | `headers/kernel.h:618` | `KProg *kprog_lookup(const char *name);` |
| `kprog_slot` | function | `headers/kernel.h:617` | `KProg *kprog_slot(const char *name);` |
| `kprog_table` | variable | `headers/kernel.h:614` | `extern KProg kprog_table[];` |
| `krealloc` | function | `headers/kernel.h:216` | `void *krealloc(void *ptr, unsigned long size);` |
| `krewind` | function | `headers/kernel.h:508` | `void krewind(KFILE *f);` |
| `ksetjmp` | function | `headers/kernel.h:640` | `int ksetjmp(void *buf) __attribute__((returns_twice));` |
| `ksnprintf` | function | `headers/kernel.h:536` | `int ksnprintf(char *buf, unsigned long size, const char *fmt, ...);` |
| `ksprintf` | function | `headers/kernel.h:535` | `int ksprintf(char *buf, const char *fmt, ...);` |
| `kstderr` | variable | `headers/kernel.h:512` | `extern KFILE *kstderr;` |
| `kstdin` | variable | `headers/kernel.h:510` | `extern KFILE *kstdin;` |
| `kstdout` | variable | `headers/kernel.h:511` | `extern KFILE *kstdout;` |
| `kstrchr` | function | `headers/kernel.h:524` | `char *kstrchr(const char *s, int c);` |
| `kstrcmp` | function | `headers/kernel.h:522` | `int kstrcmp(const char *a, const char *b);` |
| `kstrcpy` | function | `headers/kernel.h:519` | `char *kstrcpy(char *dst, const char *src);` |
| `kstrlen` | function | `headers/kernel.h:518` | `unsigned long kstrlen(const char *s);` |
| `kstrncat` | function | `headers/kernel.h:521` | `char *kstrncat(char *dst, const char *src, unsigned long n);` |
| `kstrncmp` | function | `headers/kernel.h:523` | `int kstrncmp(const char *a, const char *b, unsigned long n);` |
| `kstrncpy` | function | `headers/kernel.h:520` | `char *kstrncpy(char *dst, const char *src, unsigned long n);` |
| `kstrstr` | function | `headers/kernel.h:525` | `char *kstrstr(const char *hay, const char *ndl);` |
| `ksym_count` | variable | `headers/kernel.h:613` | `extern int ksym_count;` |
| `ksym_resolve` | function | `headers/kernel.h:619` | `void *ksym_resolve(const char *name);` |
| `ksym_table` | variable | `headers/kernel.h:612` | `extern KSym ksym_table[];` |
| `ksyscall` | function | `headers/kernel.h:788` | `long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);` |
| `ktime_ms` | function | `headers/kernel.h:25` | `unsigned long ktime_ms(void);` |
| `ktime_us` | function | `headers/kernel.h:847` | `unsigned long ktime_us(void);` |
| `ldso_bind_into` | function | `headers/kernel.h:750` | `int ldso_bind_into(void *data, unsigned size, unsigned long base, unsigned long cr3, vma_ctx_t *vma);` |
| `ldso_pseudo_read` | function | `headers/kernel.h:753` | `int ldso_pseudo_read(int ino, void *dst, unsigned long off, unsigned len);` |
| `ldso_pseudo_stat` | function | `headers/kernel.h:752` | `int ldso_pseudo_stat(int ino, unsigned long *size_out);` |
| `load_exec_elf` | function | `headers/kernel.h:740` | `void *load_exec_elf(void *data, unsigned size);` |
| `load_exec_elf_into` | function | `headers/kernel.h:741` | `void *load_exec_elf_into(void *data, unsigned size, unsigned long cr3, unsigned long *brk_out, unsigned long *base_out);` |
| `minfo_sleep_init` | function | `headers/kernel.h:116` | `void minfo_sleep_init(int tick_ok);` |
| `minfo_tick_wake` | function | `headers/kernel.h:117` | `void minfo_tick_wake(void *ctx);` |
| `minifs_mkdir_p` | function | `headers/kernel.h:417` | `int minifs_mkdir_p(const char *resolved);` |
| `mm_copy_user_page` | function | `headers/kernel.h:771` | `int mm_copy_user_page(unsigned long dst_cr3, unsigned long src_cr3, unsigned long va);` |
| `mm_file_break` | function | `headers/kernel.h:759` | `int mm_file_break(unsigned long cr3, unsigned long va);` |
| `mm_file_fault` | function | `headers/kernel.h:758` | `int mm_file_fault(unsigned long cr3, unsigned long va);` |
| `mm_file_page_phys` | function | `headers/kernel.h:760` | `unsigned long mm_file_page_phys(unsigned long cr3, unsigned long va);` |
| `mm_file_range_release` | function | `headers/kernel.h:761` | `void mm_file_range_release(unsigned long cr3, unsigned long base, unsigned long len, int ino, unsigned long off, int...` |
| `mm_setup_protections` | function | `headers/kernel.h:685` | `void mm_setup_protections(void);` |
| `mm_user_ensure_page` | function | `headers/kernel.h:755` | `int mm_user_ensure_page(unsigned long cr3, unsigned long va);` |
| `mm_user_map_page` | function | `headers/kernel.h:756` | `int mm_user_map_page(unsigned long cr3, unsigned long va, unsigned long phys, int write, int exec);` |
| `mm_user_pte_update` | function | `headers/kernel.h:688` | `void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3);` |
| `mm_user_set_exec` | function | `headers/kernel.h:689` | `void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3);` |
| `name` | type_alias | `headers/kernel.h:367` | `typedef struct vfs_dirent { char name[VFS_NAME_MAX + 1];` |
| `outb` | function | `headers/kernel.h:26` | `static inline void outb(unsigned short port, unsigned char val)` |
| `outsw` | function | `headers/kernel.h:54` | `static inline void outsw(unsigned short port, const unsigned short *buf,                         ...` |
| `outw` | function | `headers/kernel.h:34` | `static inline void outw(unsigned short port, unsigned short val)` |

Next: [SYMBOLS_p5.md](SYMBOLS_p5.md)
