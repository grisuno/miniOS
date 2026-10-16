# API (page 3 of 21)
Previous: [API_p2.md](API_p2.md)

## headers/driver.h
Imported by: `drivers/block.c`, `drivers/driver.c`, `drivers/ide.c`, `drivers/pcspk.c`, `drivers/sb16.c`, `drivers/usbblk.c`, `drivers/virtio_blk.c`, `kernel/syscalls.c`, `tests/test_driver.c`, `tests/test_usbblk.c`
- `device_register` (function) `headers/driver.h:56` `int device_register(device_t *dev);`
- `device_find` (function) `headers/driver.h:57` `device_t *device_find(const char *name);`
- `device_find_by_type` (function) `headers/driver.h:58` `device_t *device_find_by_type(int type);`
- `device_count` (function) `headers/driver.h:59` `int device_count(void);`
- `device_reset` (function) `headers/driver.h:60` `void device_reset(void);`

## headers/drivers/kbd.h
Imported by: `drivers/kbd.c`, `drivers/usbhid.c`, `kernel/console_in.c`, `kernel/exec.c`, `kernel/shell.c`, `kernel/syscalls.c`, `kernel/vga_fb.c`
- `kbd_available` (function) `headers/drivers/kbd.h:9` `int kbd_available(void);`
- `kbd_read` (function) `headers/drivers/kbd.h:10` `int kbd_read(void);`
- `kbd_feed_scancode` (function) `headers/drivers/kbd.h:11` `int kbd_feed_scancode(unsigned char sc);`
- `kbd_reset_for_shell` (function) `headers/drivers/kbd.h:12` `void kbd_reset_for_shell(void);`
- `kbd_get_layout` (function) `headers/drivers/kbd.h:15` `int kbd_get_layout(void);` -- Keyboard layout: US qwerty (default) or Spanish (Spain) qwerty.
- `kbd_set_layout` (function) `headers/drivers/kbd.h:16` `void kbd_set_layout(int layout);`
- `kbd_toggle_layout` (function) `headers/drivers/kbd.h:17` `void kbd_toggle_layout(void);`
- `kbd_q_empty` (function) `headers/drivers/kbd.h:27` `int kbd_q_empty(void);` -- Printable test for console input: ASCII 32..126 plus Latin-1 160..255 (the ES layout emits single-byte Latin-1 for ñ...
- `kbd_q_pop` (function) `headers/drivers/kbd.h:28` `int kbd_q_pop(void);`
- `kbd_q_push` (function) `headers/drivers/kbd.h:29` `void kbd_q_push(unsigned char c);`
- `kbd_drop_counts` (function) `headers/drivers/kbd.h:32` `void kbd_drop_counts(unsigned long *cooked, unsigned long *raw);` -- Printable test for console input: ASCII 32..126 plus Latin-1 160..255 (the ES layout emits single-byte Latin-1 for ñ...
- `kbd_raw_mode_get` (function) `headers/drivers/kbd.h:35` `int kbd_raw_mode_get(void);` -- DEL (127) and the C1 controls (128..159) are never input. static inline int kbd_is_printable(int c) { return (c >=...
- `kbd_raw_mode_set` (function) `headers/drivers/kbd.h:36` `void kbd_raw_mode_set(int on);`
- `kbd_raw_empty` (function) `headers/drivers/kbd.h:37` `int kbd_raw_empty(void);`
- `kbd_raw_pop` (function) `headers/drivers/kbd.h:38` `int kbd_raw_pop(void);`
- `kbd_raw_push_byte` (function) `headers/drivers/kbd.h:39` `void kbd_raw_push_byte(unsigned char c);`
- `kbd_e0_get` (function) `headers/drivers/kbd.h:40` `int kbd_e0_get(void);`
- `kbd_e0_set` (function) `headers/drivers/kbd.h:41` `void kbd_e0_set(int v);`
- `kbd_flush_all` (function) `headers/drivers/kbd.h:42` `void kbd_flush_all(void);`
- `kbd_raw_flush` (function) `headers/drivers/kbd.h:43` `void kbd_raw_flush(void);`
- `kbd_sys_raw_filter` (function) `headers/drivers/kbd.h:50` `int kbd_sys_raw_filter(unsigned char sc);` -- Raw-path WM filter for the SYS_KBD direct-port read (DOOM/Quake/Nuklear read scancodes one byte per syscall...

## headers/drivers/modifiers.h
Imported by: `drivers/kbd.c`, `drivers/usbhid.c`, `headers/wm_events.h`, `tests/test_modifiers.c`
- `modifiers_init` (function) `headers/drivers/modifiers.h:37` `static inline void modifiers_init(modifier_state_t *st)` -- int ctrl_r; int alt_l; int alt_r; int super_l; int super_r; } modifier_keys_t; #define MOD_SHIFT (1 << 0) #define...
- `modifiers_update` (function) `headers/drivers/modifiers.h:54` `static inline int modifiers_update(const modifier_keys_t *keys,
                                 ...` -- Docstring: Track one make or break code, 1 when consumed.
- `modifiers_match` (function) `headers/drivers/modifiers.h:92` `static inline int modifiers_match(const modifier_state_t *st, int mask)` -- return 1; } if (code == keys->alt_r) { st->altgr = pressed; return 1; } if (code == keys->super_l || code ==...

## headers/drivers/mouse.h
Imported by: `drivers/mouse.c`, `kernel/sched.c`
- `mouse_hw_init` (function) `headers/drivers/mouse.h:11` `void mouse_hw_init(void);` -- Docstring: mouse.h -- boundary of the PS/2 mouse device driver (drivers/mouse.c).
- `mouse_disable` (function) `headers/drivers/mouse.h:14` `void mouse_disable(void);` -- Docstring: mouse.h -- boundary of the PS/2 mouse device driver (drivers/mouse.c).
- `mouse_enable` (function) `headers/drivers/mouse.h:17` `void mouse_enable(void);` -- Docstring: mouse.h -- boundary of the PS/2 mouse device driver (drivers/mouse.c).

## headers/drivers/nvme.h
Imported by: `drivers/block.c`, `drivers/nvme.c`, `kernel/shell.c`
- `nvme_init` (function) `headers/drivers/nvme.h:4` `int nvme_init(void);`
- `nvme_present` (function) `headers/drivers/nvme.h:5` `int nvme_present(void);`
- `nvme_version` (function) `headers/drivers/nvme.h:6` `unsigned nvme_version(void);`
- `nvme_note` (function) `headers/drivers/nvme.h:7` `const char *nvme_note(void);`
- `nvme_sectors` (function) `headers/drivers/nvme.h:8` `unsigned long nvme_sectors(void);`
- `nvme_read_sectors` (function) `headers/drivers/nvme.h:9` `int nvme_read_sectors(unsigned lba, unsigned count, void *buf);`

## headers/drivers/pci.h
Imported by: `drivers/nvme.c`, `drivers/virtio_blk.c`, `drivers/virtio_net.c`, `drivers/xhci.c`, `net/rtl8139.c`, `tests/test_pci.c`
- `pci_cfg_read` (function) `headers/drivers/pci.h:80` `static inline unsigned pci_cfg_read(unsigned bus, unsigned dev,
        unsigned func, unsigned r...` -- Docstring: Read one config dword.
- `pci_cfg_write` (function) `headers/drivers/pci.h:90` `static inline void pci_cfg_write(unsigned bus, unsigned dev,
        unsigned func, unsigned reg,...` -- Docstring: Read one config dword.
- `pci_cfg_read8` (function) `headers/drivers/pci.h:100` `static inline unsigned char pci_cfg_read8(unsigned bus, unsigned dev,
        unsigned func, unsi...` -- Docstring: Read a config byte.
- `pci_cfg_write8` (function) `headers/drivers/pci.h:109` `static inline void pci_cfg_write8(unsigned bus, unsigned dev,
        unsigned func, unsigned reg...` -- Docstring: Read a config byte.
- `pci_present` (function) `headers/drivers/pci.h:122` `static inline int pci_present(unsigned bus, unsigned dev, unsigned func,
        void (*outl)(uns...` -- Docstring: True when a function is populated.
- `xHCI` (function) `headers/drivers/pci.h:134` `* base class: an xHCI (0x0C/0x03/0x30) would look for class 0x03, and a PCI
 * bridge (0x06/0x04)...`
- `pci_is_multifunction` (function) `headers/drivers/pci.h:152` `static inline int pci_is_multifunction(unsigned bus, unsigned dev,
        void (*outl)(unsigned ...` -- Docstring: True when a function advertises more than one function in its * slot, so the walk must visit every...
- `pci_find` (function) `headers/drivers/pci.h:165` `static inline int pci_find(unsigned vendor, unsigned device,
        unsigned (*inl)(unsigned sho...` -- Docstring: Find a device by vendor/device ID on bus 0.
- `pci_find_class` (function) `headers/drivers/pci.h:193` `static inline int pci_find_class(pci_bdf_t *out,
        unsigned cls, unsigned subclass, unsigne...` -- The walk starts at bus 0 and follows each PCI-to-PCI bridge's secondary bus number, so a controller behind a chipset...
- `pci_bar_count` (function) `headers/drivers/pci.h:248` `static inline unsigned pci_bar_count(unsigned bus, unsigned dev, unsigned func,
        void (*ou...` -- outl, inl)) { unsigned sec = pci_cfg_read8(bus, dev, 0, PCI_REG_BRIDGE_SECONDARY, outl, inl); if (sec != 0u && sec <...
- `pci_bar_is_io` (function) `headers/drivers/pci.h:263` `static inline int pci_bar_is_io(unsigned bus, unsigned dev, unsigned func,
        unsigned bar,
...` -- void (*outl)(unsigned short, unsigned), unsigned (*inl)(unsigned short)) { unsigned n = 0; while (n <...
- `pci_bar_is_64bit` (function) `headers/drivers/pci.h:274` `static inline int pci_bar_is_64bit(unsigned bus, unsigned dev, unsigned func,
        unsigned ba...` -- Docstring: True when a BAR is a 64-bit memory BAR, so its high dword is * the next BAR slot and must be programmed...
- `pci_bar_ctz32` (function) `headers/drivers/pci.h:284` `static inline unsigned pci_bar_ctz32(unsigned val)` -- Docstring: True when a BAR is a 64-bit memory BAR, so its high dword is * the next BAR slot and must be programmed...
- `pci_bar_size_from_mask` (function) `headers/drivers/pci.h:315` `static inline unsigned long long pci_bar_size_from_mask(unsigned long long mask)` -- A BAR that fits below 4 GB has its unimplemented lines in the low half and an all-ones high half.
- `pci_bar_size` (function) `headers/drivers/pci.h:346` `static inline unsigned long long pci_bar_size(unsigned bus, unsigned dev,
        unsigned func, ...` -- The mask is what proves the region is big enough; a size is never assumed from a spec table because a wrong answer...
- `pci_bar_relocate` (function) `headers/drivers/pci.h:382` `static inline int pci_bar_relocate(unsigned bus, unsigned dev, unsigned func,
        unsigned ba...` -- Docstring: Program a memory BAR with a physical base address.
- `pci_bar_base` (function) `headers/drivers/pci.h:406` `static inline unsigned long long pci_bar_base(unsigned bus, unsigned dev,
        unsigned func, ...` -- Docstring: Physical base a memory BAR is programmed with, read back from the device.
- `pci_bar_restore` (function) `headers/drivers/pci.h:424` `static inline void pci_bar_restore(unsigned bus, unsigned dev,
        unsigned func, unsigned ba...` -- Docstring: Restore a BAR pair to previously saved raw values.

## headers/drivers/usbblk.h
Imported by: `drivers/block.c`, `drivers/usbblk.c`, `kernel.c`, `kernel/shell.c`, `tests/test_usbblk.c`
- `ubk_init` (function) `headers/drivers/usbblk.h:21` `int ubk_init(void);` -- Docstring: Bring up mass storage on every enumerated device.
- `ubk_present` (function) `headers/drivers/usbblk.h:24` `int ubk_present(void);` -- Docstring: Bring up mass storage on every enumerated device.
- `ubk_sectors` (function) `headers/drivers/usbblk.h:27` `unsigned long ubk_sectors(void);` -- Docstring: Bring up mass storage on every enumerated device.
- `ubk_read_sectors` (function) `headers/drivers/usbblk.h:32` `int ubk_read_sectors(unsigned long lba, unsigned count, void *buf);` -- Docstring: Read or write whole 512-byte sectors.
- `ubk_write_sectors` (function) `headers/drivers/usbblk.h:33` `int ubk_write_sectors(unsigned long lba, unsigned count, const void *buf);`
- `ubk_counters` (function) `headers/drivers/usbblk.h:46` `void ubk_counters(ubk_counters_t *out);` -- Docstring: Counters, so a disk that is absent is distinguishable from a * driver that is broken. typedef struct {...
- `ubk_build_cbw` (function) `headers/drivers/usbblk.h:52` `void ubk_build_cbw(unsigned char *out, unsigned tag, unsigned long lba, unsigned blocks, int read, int data_len);` -- Docstring: Build a Command Block Wrapper into out, which must have room for UBK_CBW_LEN bytes.
- `ubk_check_csw` (function) `headers/drivers/usbblk.h:60` `int ubk_check_csw(const unsigned char *csw, unsigned tag, unsigned expect_len);` -- Docstring: Check a Command Status Wrapper.

## headers/drivers/usbhid.h
Imported by: `drivers/usbhid.c`, `kernel.c`, `kernel/console_in.c`, `kernel/shell.c`, `tests/test_usbhid.c`
- `usbhid_init` (function) `headers/drivers/usbhid.h:60` `int usbhid_init(void);` -- Docstring: Bring up HID on every enumerated device and report what was found.
- `usbhid_poll_keyboard` (function) `headers/drivers/usbhid.h:64` `int usbhid_poll_keyboard(void);` -- Docstring: Service the interrupt endpoint of a claimed keyboard.
- `usbhid_poll_mouse` (function) `headers/drivers/usbhid.h:68` `int usbhid_poll_mouse(void);` -- Docstring: Service the interrupt endpoint of a claimed mouse.
- `usbhid_poll` (function) `headers/drivers/usbhid.h:71` `int usbhid_poll(void);` -- Docstring: Service the interrupt endpoint of a claimed mouse.
- `usbhid_keyboard_present` (function) `headers/drivers/usbhid.h:76` `int usbhid_keyboard_present(void);` -- Docstring: True when a USB keyboard is driving the input path, so the keyboard driver can skip the PS/2 port instead...
- `usbhid_mouse_present` (function) `headers/drivers/usbhid.h:79` `int usbhid_mouse_present(void);` -- Docstring: True when a USB keyboard is driving the input path, so the keyboard driver can skip the PS/2 port instead...
- `usbhid_press_kbd_report` (function) `headers/drivers/usbhid.h:84` `int usbhid_press_kbd_report(const unsigned char report[HID_KBD_REPORT_LEN]);` -- Docstring: Feed a boot keyboard report through the differ, for the host test and the in-OS self test.
- `usbhid_kbd_scancodes` (function) `headers/drivers/usbhid.h:94` `int usbhid_kbd_scancodes(const unsigned char prev[HID_KBD_REPORT_LEN], const unsigned char cur[HID_KBD_REPORT_LEN]...` -- Docstring: Set-1 scancode stream for one keyboard report transition.
- `usbhid_mouse_decode` (function) `headers/drivers/usbhid.h:102` `void usbhid_mouse_decode(const unsigned char prev[HID_MOUSE_REPORT_LEN], const unsigned char...` -- Docstring: Decode one boot mouse report transition into screen-space motion, buttons and wheel.
- `usbhid_counters` (function) `headers/drivers/usbhid.h:116` `void usbhid_counters(usbhid_counters_t *out);` -- Docstring: Counters, so a device that is absent is distinguishable from a * driver that is broken. typedef struct {...
- `usbhid_set1_from_usage` (function) `headers/drivers/usbhid.h:127` `int usbhid_set1_from_usage(unsigned usage, unsigned char *sc, int *e0);` -- Docstring: Translate a HID usage code to its PS/2 set-1 make code and whether it needs the 0xE0 prefix.

## headers/drivers/virtio_blk.h
Imported by: `drivers/block.c`, `drivers/virtio_blk.c`, `kernel.c`, `kernel/shell.c`
- `vblk_init` (function) `headers/drivers/virtio_blk.h:11` `int vblk_init(void);`
- `vblk_present` (function) `headers/drivers/virtio_blk.h:12` `int vblk_present(void);`
- `vblk_sectors` (function) `headers/drivers/virtio_blk.h:13` `unsigned long vblk_sectors(void);`
- `vblk_read_sectors` (function) `headers/drivers/virtio_blk.h:14` `int vblk_read_sectors(unsigned lba, unsigned count, void *buf);`
- `vblk_write_sectors` (function) `headers/drivers/virtio_blk.h:15` `int vblk_write_sectors(unsigned lba, unsigned count, const void *buf);`
- `vblk_register_device` (function) `headers/drivers/virtio_blk.h:18` `void vblk_register_device(void);` -- sector contract: probe once, then read/write 512-byte sectors by LBA.

## headers/drivers/virtio_net.h
Imported by: `drivers/virtio_net.c`, `kernel/shell.c`, `net/net.c`
- `vnet_init` (function) `headers/drivers/virtio_net.h:16` `int vnet_init(void);` -- Docstring: Probe PCI for a virtio-net device and bring both queues up.
- `vnet_present` (function) `headers/drivers/virtio_net.h:19` `int vnet_present(void);` -- Docstring: Probe PCI for a virtio-net device and bring both queues up.
- `failure` (function) `headers/drivers/virtio_net.h:22` `* 0 on failure (no device, oversize, or TX deadline expiry). Pads * short frames to 60 bytes like the rtl8139 path....`
- `vnet_poll` (function) `headers/drivers/virtio_net.h:28` `void vnet_poll(void);` -- Docstring: Drain completed RX buffers into net_rx_handle_frame, * reposting every descriptor.
- `vnet_get_mac` (function) `headers/drivers/virtio_net.h:31` `void vnet_get_mac(unsigned char out[6]);` -- Docstring: Drain completed RX buffers into net_rx_handle_frame, * reposting every descriptor.
- `vnet_iobase` (function) `headers/drivers/virtio_net.h:34` `unsigned short vnet_iobase(void);` -- Docstring: Drain completed RX buffers into net_rx_handle_frame, * reposting every descriptor.
- `vnet_counters` (function) `headers/drivers/virtio_net.h:37` `void vnet_counters(unsigned int *tx_frames, unsigned int *rx_frames);` -- Docstring: Drain completed RX buffers into net_rx_handle_frame, * reposting every descriptor.
- `vnet_link_up` (function) `headers/drivers/virtio_net.h:40` `int vnet_link_up(void);` -- Docstring: Drain completed RX buffers into net_rx_handle_frame, * reposting every descriptor.

## headers/drivers/xhci.h
Imported by: `drivers/usbblk.c`, `drivers/usbhid.c`, `drivers/xhci.c`, `kernel.c`, `kernel/console_in.c`, `kernel/sched.c`, `kernel/shell.c`, `tests/test_xhci.c`
- `xhc_init` (function) `headers/drivers/xhci.h:140` `int xhc_init(void);` -- Docstring: Bring up the first xHCI controller found.
- `xhc_poll` (function) `headers/drivers/xhci.h:146` `int xhc_poll(void);` -- Docstring: Service the event ring.
- `xhc_port_count` (function) `headers/drivers/xhci.h:150` `int xhc_port_count(void);` -- Docstring: Number of root ports the controller reports, bounded by * XHC_MAX_PORTS.
- `xhc_port_state` (function) `headers/drivers/xhci.h:154` `int xhc_port_state(int port, xhc_port_t *out);` -- Docstring: Read a root port's live state.
- `xhc_port_reset` (function) `headers/drivers/xhci.h:159` `int xhc_port_reset(int port);` -- Docstring: Reset a port and wait for the device on it to be addressable.
- `xhc_enumerate` (function) `headers/drivers/xhci.h:165` `int xhc_enumerate(int port);` -- Docstring: Reset, address, describe and register the device on a port.
- `xhc_enumerate_all` (function) `headers/drivers/xhci.h:169` `int xhc_enumerate_all(void);` -- Docstring: Enumerate every port that has something attached.
- `xhc_device_count` (function) `headers/drivers/xhci.h:172` `int xhc_device_count(void);` -- Docstring: Enumerate every port that has something attached.
- `xhc_device_info` (function) `headers/drivers/xhci.h:175` `int xhc_device_info(int index, xhc_dev_t *out);` -- Docstring: Enumerate every port that has something attached.
- `xhc_open_interface` (function) `headers/drivers/xhci.h:186` `int xhc_open_interface(int index, unsigned cls, unsigned sub, unsigned proto, xhc_iface_t *out);` -- Docstring: Find an interface of an enumerated device by class triple and copy out its endpoints.
- `xhc_control` (function) `headers/drivers/xhci.h:193` `int xhc_control(int index, const unsigned char setup[8], void *data, unsigned len, int host_to_device);` -- Docstring: Issue a control transfer on the control endpoint of a device. setup is the eight setup bytes, already...
- `xhc_configure_endpoint` (function) `headers/drivers/xhci.h:200` `int xhc_configure_endpoint(int index, int ep_index, int ep_addr, int ep_type, int max_packet, int mult, int...` -- Docstring: Configure one non-control endpoint and give it a transfer ring. ep_index is the endpoint context index...
- `xhc_transfer` (function) `headers/drivers/xhci.h:211` `int xhc_transfer(int index, int ep_index, void *buf, unsigned len, int *got);` -- Docstring: Move data on a configured endpoint and wait for its transfer event. len must be exactly what the...
- `xhc_reset_endpoint` (function) `headers/drivers/xhci.h:216` `int xhc_reset_endpoint(int index, int ep_index);` -- Docstring: Stop, reset and re-point one endpoint's transfer ring after a stall or a timeout, so Bulk-Only recovery...
- `xhc_transfer_async` (function) `headers/drivers/xhci.h:220` `int xhc_transfer_async(int index, int ep_index, void *buf, unsigned len);` -- Docstring: Post one endpoint transfer without waiting.
- `xhc_poll_token_limit` (function) `headers/drivers/xhci.h:225` `int xhc_poll_token_limit(int token, unsigned budget_ms);` -- Docstring: Non-blocking completion check: 1 on success, -1 on a failed completion, -2 past the transfer budget, 0...
- `xhc_poll_token` (function) `headers/drivers/xhci.h:226` `int xhc_poll_token(int token);`
- `xhc_counters` (function) `headers/drivers/xhci.h:229` `void xhc_counters(xhc_counters_t *out);` -- Docstring: Non-blocking completion check: 1 on success, -1 on a failed completion, -2 past the transfer budget, 0...
- `xhc_probe_note` (function) `headers/drivers/xhci.h:234` `const char *xhc_probe_note(void);` -- Docstring: Why the last xhc_init failed, or NULL when it succeeded.
- `xhc_info` (function) `headers/drivers/xhci.h:238` `int xhc_info(unsigned *version, unsigned *slots, unsigned *ports, unsigned *caplength);` -- Docstring: Controller version and capability-derived limits for the usb * builtin.

## headers/editor.h
Depends on: `headers/kernel.h`
Imported by: `kernel/editor.c`, `kernel/shell.c`
- `shell_cmd_edit` (function) `headers/editor.h:15` `void shell_cmd_edit(int argc, char **argv);`

## headers/ext4.h
Imported by: `fs/ext4.c`, `fs/vfs.c`, `kernel/shell.c`, `tests/test_ext4.c`
- `ext4_list` (function) `headers/ext4.h:35` `int ext4_list(const char *imgpath, const char *dirpath, char names[][EXT4_NAME_MAX + 1], int *isdir, int cap);` -- List one directory: names (dirs with trailing '/') up to cap. * Returns the entry count, or -1 when the image, path...
- `ext4_vfs_open` (function) `headers/ext4.h:40` `int ext4_vfs_open(const char *path, int mode, void **handle);` -- VFS verbs: open "imgpath:extpath" (first ':' splits), read, close, * fstat.
- `ext4_vfs_read` (function) `headers/ext4.h:41` `int ext4_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len);`
- `ext4_vfs_write` (function) `headers/ext4.h:43` `int ext4_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len);`
- `ext4_vfs_close` (function) `headers/ext4.h:45` `int ext4_vfs_close(void *handle);`
- `ext4_vfs_fstat` (function) `headers/ext4.h:46` `int ext4_vfs_fstat(void *handle, unsigned long *size_out);`
- `ext4_vfs_truncate` (function) `headers/ext4.h:47` `int ext4_vfs_truncate(void *handle, unsigned long size);`
- `first` (function) `headers/ext4.h:50` `* MBR 0x83 entry first (proven by a superblock read), then a magic * scan over 2048-aligned LBAs for superfloppy...`

## headers/fat32.h
Imported by: `fs/fat32.c`, `fs/vfs.c`, `kernel/shell.c`, `tests/test_fat32.c`
- `file` (function) `headers/fat32.h:6` `* * A FAT32 disk image stored as a regular file (built on the host with * mkfs.vfat, packed into minifs.bin) is...`
- `fat32_list` (function) `headers/fat32.h:45` `int fat32_list(const char *imgpath, const char *dirpath, char names[][FAT32_NAME_MAX], int *isdir, int cap);` -- List one directory: names (dirs with trailing '/') up to cap. * Returns the entry count, or -1 when the image, path...
- `fat_dev_base` (function) `headers/fat32.h:54` `long fat_dev_base(void);` -- Locate the first FAT32 partition on the primary IDE master: a real MBR FAT32 entry first (real hardware with a...
- `fat32_vfs_open` (function) `headers/fat32.h:58` `int fat32_vfs_open(const char *path, int mode, void **handle);` -- VFS verbs: open "imgpath:fatpath" (first ':' splits), read, close, * fstat.
- `fat32_vfs_read` (function) `headers/fat32.h:59` `int fat32_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len);`
- `fat32_vfs_write` (function) `headers/fat32.h:61` `int fat32_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len);`
- `fat32_vfs_close` (function) `headers/fat32.h:63` `int fat32_vfs_close(void *handle);`
- `fat32_vfs_fstat` (function) `headers/fat32.h:64` `int fat32_vfs_fstat(void *handle, unsigned long *size_out);`
- `fat32_vfs_truncate` (function) `headers/fat32.h:65` `int fat32_vfs_truncate(void *handle, unsigned long size);`

## headers/fsimg.h
Imported by: `fs/ext4.c`, `fs/fat32.c`, `fs/fsimg.c`, `tests/test_ext4.c`, `tests/test_fat32.c`
- `fsimg_open_file` (function) `headers/fsimg.h:23` `int fsimg_open_file(const char *resolved, fsimg_t *img);` -- Open a resolved path as a loopback image.
- `fsimg_open_dev` (function) `headers/fsimg.h:27` `int fsimg_open_dev(unsigned long base_lba, unsigned long nsec, fsimg_t *img);` -- Open an absolute disk region [base_lba, base_lba + nsec) as an * image.
- `fsimg_read` (function) `headers/fsimg.h:32` `int fsimg_read(const fsimg_t *img, unsigned long off, void *buf, unsigned long len);` -- Read len bytes at off into buf.
- `fsimg_split` (function) `headers/fsimg.h:40` `int fsimg_split(const char *path, char *left, unsigned llen, char *right, unsigned rlen);` -- Split "left:right" at the first ':' (image names never carry one).

## headers/futex.h
Depends on: `headers/sched.h`, `headers/spinlock.h`, `headers/sync.h`
Imported by: `kernel/futex.c`, `kernel/sched.c`, `kernel/syscalls.c`, `tests/test_futex.c`
- `futex_init` (function) `headers/futex.h:86` `void futex_init(void);`
- `futex_wait` (function) `headers/futex.h:87` `long futex_wait(unsigned long uaddr, int val);`
- `futex_wake` (function) `headers/futex.h:88` `long futex_wake(unsigned long uaddr, int n);`
- `futex_forget` (function) `headers/futex.h:91` `void futex_forget(int pid);` -- Unlink pid from whatever futex queue still holds it and clear its * recorded address; a no-op for a pid that is not...
- `FUTEX_CLOCK_REALTIME` (function) `headers/futex.h:96` `* FUTEX_CLOCK_REALTIME (it only selects the clock of a BITSET deadline). * Returns -1 for anything unserved...`
- `futex_linux_cmd` (function) `headers/futex.h:100` `int futex_linux_cmd(long op);` -- Decode a Linux futex(2) op to LINUX_FUTEX_WAIT/WAKE/WAIT_BITSET/ WAKE_BITSET, masking FUTEX_PRIVATE_FLAG...
- `futex_timeout_remaining_us` (function) `headers/futex.h:107` `long futex_timeout_remaining_us(int cmd, long sec, long nsec, unsigned long now_us);` -- Microseconds left before a futex timeout: relative for WAIT, absolute (against now_us on the op's clock) for...

## headers/httpd.h
Imported by: `kernel/shell.c`, `tests/test_httpd.c`
- `httpd_ctype` (function) `headers/httpd.h:28` `static inline const char *httpd_ctype(const char *path)` -- Docstring: Content type by file suffix.
- `httpd_header` (function) `headers/httpd.h:121` `static inline int httpd_header(int code, const char *reason,
        const char *ctype, unsigned ...` -- Docstring: Emit a response head into out.

## headers/ide.h
Imported by: `drivers/block.c`, `drivers/ide.c`, `fs/minifs.c`, `kernel.c`, `kernel/mm/swap.c`, `kernel/syscalls.c`
- `ide_init` (function) `headers/ide.h:49` `void ide_init(void);` -- #define IDE_CMD_FLUSH       0xE7    /* FLUSH CACHE /* Drive/Head register bits #define IDE_DRIVE_LBA       0x40...
- `ide_read_sectors` (function) `headers/ide.h:53` `int ide_read_sectors(unsigned int lba, unsigned int count, void *buf);` -- Read/write sectors using 28-bit LBA. * Returns 0 on success, -1 on error.
- `ide_write_sectors` (function) `headers/ide.h:54` `int ide_write_sectors(unsigned int lba, unsigned int count, const void *buf);`
- `ide_read_sector` (function) `headers/ide.h:57` `int ide_read_sector(unsigned int lba, void *buf);` -- Read/write sectors using 28-bit LBA. * Returns 0 on success, -1 on error. int ide_read_sectors(unsigned int lba...
- `ide_write_sector` (function) `headers/ide.h:58` `int ide_write_sector(unsigned int lba, const void *buf);`
- `ide_total_sectors` (function) `headers/ide.h:61` `unsigned int ide_total_sectors(void);` -- Read/write sectors using 28-bit LBA. * Returns 0 on success, -1 on error. int ide_read_sectors(unsigned int lba...
- `ide_present` (function) `headers/ide.h:64` `int ide_present(void);` -- Read/write sectors using 28-bit LBA. * Returns 0 on success, -1 on error. int ide_read_sectors(unsigned int lba...
- `ide_register_device` (function) `headers/ide.h:68` `void ide_register_device(void);` -- Publish the Strategy ops table to the device registry (driver.h). * Called from ide_init; re-registration is a no-op...


Next: [API_p4.md](API_p4.md)
