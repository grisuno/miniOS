# API (page 3 of 19)
Previous: [API_p2.md](API_p2.md)

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
- `FUTEX_CLOCK_REALTIME` (function) `headers/futex.h:93` `* FUTEX_CLOCK_REALTIME (it only selects the clock of a BITSET deadline). * Returns -1 for anything unserved...`
- `futex_linux_cmd` (function) `headers/futex.h:97` `int futex_linux_cmd(long op);` -- Decode a Linux futex(2) op to LINUX_FUTEX_WAIT/WAKE/WAIT_BITSET/ WAKE_BITSET, masking FUTEX_PRIVATE_FLAG...
- `futex_timeout_remaining_us` (function) `headers/futex.h:104` `long futex_timeout_remaining_us(int cmd, long sec, long nsec, unsigned long now_us);` -- Microseconds left before a futex timeout: relative for WAIT, absolute (against now_us on the op's clock) for...

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

## headers/kernel.h
Depends on: `headers/ldso.h`, `headers/pipe.h`, `headers/spinlock.h`, `headers/vma.h`, `progs/minios_abi.h`
Imported by: `headers/editor.h`, `headers/shell.h`, `headers/spawn.h`, `headers/tls_port.h`
- `ktime_ms` (function) `headers/kernel.h:25` `unsigned long ktime_ms(void);` -- Forward: PIT-calibrated wall clock (defined in kernel/time.c); valid * once pit_init has run.
- `outb` (function) `headers/kernel.h:26` `static inline void outb(unsigned short port, unsigned char val)`
- `inb` (function) `headers/kernel.h:29` `static inline unsigned char inb(unsigned short port)`
- `outw` (function) `headers/kernel.h:34` `static inline void outw(unsigned short port, unsigned short val)`
- `inw` (function) `headers/kernel.h:37` `static inline unsigned short inw(unsigned short port)`
- `insw` (function) `headers/kernel.h:47` `static inline void insw(unsigned short port, unsigned short *buf,
                        unsigne...` -- String port I/O: one instruction moves `count` words between the port and the buffer.
- `outsw` (function) `headers/kernel.h:54` `static inline void outsw(unsigned short port, const unsigned short *buf,
                        ...`
- `waits` (function) `headers/kernel.h:64` `* and mouse_hw_init issues dozens of waits (measured 5 s of boot).  This
 * polls the port once p...`
- `vga_clear` (function) `headers/kernel.h:94` `void vga_clear(void);`
- `vga_putc` (function) `headers/kernel.h:95` `void vga_putc(char c);`
- `vga_puts` (function) `headers/kernel.h:96` `void vga_puts(const char *s);`
- `vga_scroll` (function) `headers/kernel.h:97` `void vga_scroll(void);`
- `vga_set_cursor` (function) `headers/kernel.h:98` `void vga_set_cursor(int x, int y);`
- `vga_newline` (function) `headers/kernel.h:99` `void vga_newline(void);`
- `vga_cursor_enable` (function) `headers/kernel.h:100` `void vga_cursor_enable(int on);`
- `vga_get_x` (function) `headers/kernel.h:108` `int vga_get_x(void);` -- Console output lock (kernel/console.c): serializes SMP console output across CPUs.
- `vga_get_y` (function) `headers/kernel.h:109` `int vga_get_y(void);`
- `vga_set_xy` (function) `headers/kernel.h:110` `void vga_set_xy(int x, int y);`
- `vga_get_color` (function) `headers/kernel.h:111` `char vga_get_color(void);`
- `minfo_sleep_init` (function) `headers/kernel.h:116` `void minfo_sleep_init(int tick_ok);` -- MINFO sleep support (kernel/syscalls.c): timed park for ring-3 monitors. sched_init passes the tick-registration...
- `minfo_tick_wake` (function) `headers/kernel.h:117` `void minfo_tick_wake(void *ctx);`
- `sb_init` (function) `headers/kernel.h:120` `void sb_init(void);` -- MINFO sleep support (kernel/syscalls.c): timed park for ring-3 monitors. sched_init passes the tick-registration...
- `sb_capture_row0` (function) `headers/kernel.h:121` `void sb_capture_row0(void);`
- `sb_reset` (function) `headers/kernel.h:122` `void sb_reset(void);`
- `sb_get_count` (function) `headers/kernel.h:123` `int sb_get_count(void);`
- `sb_get_head` (function) `headers/kernel.h:124` `int sb_get_head(void);`
- `sb_get_char` (function) `headers/kernel.h:125` `char sb_get_char(int row, int col);`
- `serial_init` (function) `headers/kernel.h:128` `void serial_init(void);` -- monitors. sched_init passes the tick-registration result; without a * registered waker sel 6 fails closed instead of...
- `serial_putc` (function) `headers/kernel.h:129` `void serial_putc(char c);`
- `serial_puts` (function) `headers/kernel.h:130` `void serial_puts(const char *s);`
- `sc_record_dump` (function) `headers/kernel.h:131` `void sc_record_dump(int pid);`
- `serial_e_count` (function) `headers/kernel.h:132` `unsigned long serial_e_count(void);`
- `serial_available` (function) `headers/kernel.h:134` `int serial_available(void);` -- void sb_init(void); void sb_capture_row0(void); void sb_reset(void); int  sb_get_count(void); int...
- `serial_getc` (function) `headers/kernel.h:135` `int serial_getc(void);`
- `kbd_read` (function) `headers/kernel.h:173` `int kbd_read(void);`
- `kbd_available` (function) `headers/kernel.h:174` `int kbd_available(void);`
- `kbd_reset_for_shell` (function) `headers/kernel.h:175` `void kbd_reset_for_shell(void);`
- `kmalloc` (function) `headers/kernel.h:213` `void *kmalloc(unsigned long size);`
- `kfree` (function) `headers/kernel.h:215` `void kfree(void *ptr);`
- `kcalloc` (function) `headers/kernel.h:216` `void *kcalloc(unsigned long nmemb, unsigned long size);`
- `krealloc` (function) `headers/kernel.h:217` `void *krealloc(void *ptr, unsigned long size);`
- `kallocator_init` (function) `headers/kernel.h:218` `void kallocator_init(void);`
- `kmalloc_aligned` (function) `headers/kernel.h:219` `void *kmalloc_aligned(unsigned long size, unsigned long align);`
- `kmalloc_page` (function) `headers/kernel.h:221` `void *kmalloc_page(void);` -- define KMALLOC_PAGE 0x1000UL
- `kfree_aligned` (function) `headers/kernel.h:222` `void kfree_aligned(void *ptr);`
- `dlmalloc_init` (function) `headers/kernel.h:226` `void dlmalloc_init(unsigned long size);` -- dlmalloc backend (third_party/dlmalloc): an mspace rooted over the fixed * kernel heap.
- `dlmalloc_malloc` (function) `headers/kernel.h:230` `void *dlmalloc_malloc(unsigned long size);`
- `dlmalloc_memalign` (function) `headers/kernel.h:231` `void *dlmalloc_memalign(unsigned long align, unsigned long size);`
- `dlmalloc_free` (function) `headers/kernel.h:232` `void dlmalloc_free(void *ptr);`
- `dlmalloc_calloc` (function) `headers/kernel.h:233` `void *dlmalloc_calloc(unsigned long nmemb, unsigned long size);`
- `dlmalloc_realloc` (function) `headers/kernel.h:234` `void *dlmalloc_realloc(void *ptr, unsigned long size);`
- `dlmalloc_usage` (function) `headers/kernel.h:236` `void dlmalloc_usage(unsigned long *used, unsigned long *free_b, unsigned long *arena);` -- Bytes of kernel heap actually in use as the dlmalloc space: HEAP_SIZE * clamped to the RAM installed above...
- `ramdisk_init` (function) `headers/kernel.h:278` `void ramdisk_init(void);`
- `ramdisk_open` (function) `headers/kernel.h:279` `RDFile *ramdisk_open(const char *name);`
- `ramdisk_read` (function) `headers/kernel.h:280` `int ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len);`
- `ramdisk_write` (function) `headers/kernel.h:281` `int ramdisk_write(RDFile *f, const void *buf, unsigned offset, unsigned len);`
- `ramdisk_create` (function) `headers/kernel.h:282` `RDFile *ramdisk_create(const char *name, unsigned size);`
- `ramdisk_resize` (function) `headers/kernel.h:283` `int ramdisk_resize(RDFile *f, unsigned newsize);`
- `ramdisk_delete` (function) `headers/kernel.h:284` `int ramdisk_delete(RDFile *f);`
- `RAMDISK_FNAME_LEN` (function) `headers/kernel.h:286` `* RAMDISK_FNAME_LEN (fs_resolve guarantees it);`
- `ramdisk_rename` (function) `headers/kernel.h:288` `int ramdisk_rename(const char *oldname, const char *newname);` -- Docstring: In-place rename of one ramdisk entry.
- `ramdisk_list` (function) `headers/kernel.h:289` `int ramdisk_list(RDFile **out, int max);`
- `ramdisk_setup_from` (function) `headers/kernel.h:290` `void ramdisk_setup_from(void *data, unsigned size);`
- `ramdisk_count` (function) `headers/kernel.h:291` `int ramdisk_count(void);`
- `ramdisk_file_name` (function) `headers/kernel.h:292` `const char *ramdisk_file_name(int idx);`
- `ramdisk_usage` (function) `headers/kernel.h:294` `void ramdisk_usage(unsigned *used, unsigned *cap, unsigned *max);` -- Docstring: In-place rename of one ramdisk entry.
- `fs_resolve` (function) `headers/kernel.h:302` `int fs_resolve(const char *path, char *out, unsigned cap);` -- Path resolution choke point shared by the shell builtins and the zip builtins. fs_resolve resolves a path against...
- `fs_dir_exists` (function) `headers/kernel.h:303` `int fs_dir_exists(const char *dir);`
- `fs_is_dir` (function) `headers/kernel.h:304` `int fs_is_dir(const char *resolved);`
- `vfs_register` (function) `headers/kernel.h:408` `int vfs_register(const char *prefix, const vfs_ops_t *ops, const char *driver);`
- `vfs_unregister` (function) `headers/kernel.h:409` `int vfs_unregister(const char *prefix);`
- `vfs_list` (function) `headers/kernel.h:413` `int vfs_list(char prefixes[][VFS_PREFIX_LEN], char drivers[][VFS_DRIVER_LEN], int refs[], int cap);` -- define VFS_MAX_MOUNTS 8 define VFS_PREFIX_LEN 32 define VFS_DRIVER_LEN 16
- `vfs_mount_driver` (function) `headers/kernel.h:415` `int vfs_mount_driver(const char *prefix, const char *driver);`
- `vfs_open` (function) `headers/kernel.h:416` `int vfs_open(const char *path, int mode, vfs_file_t *f);`
- `vfs_read` (function) `headers/kernel.h:417` `int vfs_read(vfs_file_t *f, void *buf, unsigned long len);`
- `vfs_write` (function) `headers/kernel.h:418` `int vfs_write(vfs_file_t *f, const void *buf, unsigned long len);`
- `vfs_close` (function) `headers/kernel.h:419` `int vfs_close(vfs_file_t *f);`
- `vfs_fstat` (function) `headers/kernel.h:420` `int vfs_fstat(vfs_file_t *f, unsigned long *size_out);`
- `vfs_readdir` (function) `headers/kernel.h:421` `int vfs_readdir(const char *path, vfs_dirent_t *ents, int cap);`
- `vfs_init` (function) `headers/kernel.h:422` `void vfs_init(void);`
- `vfs_register_builtins` (function) `headers/kernel.h:423` `void vfs_register_builtins(void);`
- `minifs_mkdir_p` (function) `headers/kernel.h:424` `int minifs_mkdir_p(const char *resolved);`
- `kfopen` (function) `headers/kernel.h:483` `KFILE *kfopen(const char *path, const char *mode);`
- `kfclose` (function) `headers/kernel.h:484` `int kfclose(KFILE *f);`
- `today` (function) `headers/kernel.h:489` `* cell is correct today (single shared ET_REL window, no miniGCC * threads);`
- `fs_rename` (function) `headers/kernel.h:508` `int fs_rename(const char *oldr, const char *newr);` -- Rename one file within its filesystem; see fs/kfile.c for the contract: * 0 ok, -2 missing src, -21 directory, -17...
- `kfgetc` (function) `headers/kernel.h:509` `int kfgetc(KFILE *f);`
- `kfgets` (function) `headers/kernel.h:510` `char *kfgets(char *buf, int size, KFILE *f);`
- `kfungetc` (function) `headers/kernel.h:511` `int kfungetc(int c, KFILE *f);`
- `kfread` (function) `headers/kernel.h:512` `unsigned long kfread(void *ptr, unsigned long size, unsigned long nmemb, KFILE *f);`
- `kfwrite` (function) `headers/kernel.h:513` `unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long nmemb, KFILE *f);`
- `kfseek` (function) `headers/kernel.h:514` `int kfseek(KFILE *f, long offset, int whence);`
- `kftell` (function) `headers/kernel.h:515` `long kftell(KFILE *f);`
- `kfputs` (function) `headers/kernel.h:516` `int kfputs(const char *s, KFILE *f);`
- `kfputc` (function) `headers/kernel.h:517` `int kfputc(int c, KFILE *f);`
- `kfflush` (function) `headers/kernel.h:518` `int kfflush(KFILE *f);`
- `krewind` (function) `headers/kernel.h:519` `void krewind(KFILE *f);`
- `kfile_stdin` (function) `headers/kernel.h:524` `KFILE *kfile_stdin(void);`
- `kfile_stdout` (function) `headers/kernel.h:525` `KFILE *kfile_stdout(void);`
- `kfile_stderr` (function) `headers/kernel.h:526` `KFILE *kfile_stderr(void);`
- `kstrlen` (function) `headers/kernel.h:529` `unsigned long kstrlen(const char *s);` -- long   kftell(KFILE *f); int    kfputs(const char *s, KFILE *f); int    kfputc(int c, KFILE *f); int...
- `kstrcpy` (function) `headers/kernel.h:530` `char *kstrcpy(char *dst, const char *src);`
- `kstrncpy` (function) `headers/kernel.h:531` `char *kstrncpy(char *dst, const char *src, unsigned long n);`
- `kstrncat` (function) `headers/kernel.h:532` `char *kstrncat(char *dst, const char *src, unsigned long n);`
- `kstrcmp` (function) `headers/kernel.h:533` `int kstrcmp(const char *a, const char *b);`
- `kstrncmp` (function) `headers/kernel.h:534` `int kstrncmp(const char *a, const char *b, unsigned long n);`
- `kstrchr` (function) `headers/kernel.h:535` `char *kstrchr(const char *s, int c);`
- `kstrstr` (function) `headers/kernel.h:536` `char *kstrstr(const char *hay, const char *ndl);`
- `kmemcpy` (function) `headers/kernel.h:537` `void *kmemcpy(void *dst, const void *src, unsigned long n);`
- `kmemset` (function) `headers/kernel.h:538` `void *kmemset(void *dst, int c, unsigned long n);`
- `kmemcmp` (function) `headers/kernel.h:539` `int kmemcmp(const void *a, const void *b, unsigned long n);`
- `kmemmove` (function) `headers/kernel.h:540` `void *kmemmove(void *dst, const void *src, unsigned long n);`
- `katol` (function) `headers/kernel.h:541` `long katol(const char *s);`
- `kprintf` (function) `headers/kernel.h:544` `int kprintf(const char *fmt, ...);` -- char *kstrcpy(char *dst, const char *src); char *kstrncpy(char *dst, const char *src, unsigned long n); char...
- `kfprintf` (function) `headers/kernel.h:545` `int kfprintf(KFILE *f, const char *fmt, ...);`
- `ksprintf` (function) `headers/kernel.h:546` `int ksprintf(char *buf, const char *fmt, ...);`
- `ksnprintf` (function) `headers/kernel.h:547` `int ksnprintf(char *buf, unsigned long size, const char *fmt, ...);`
- `klog` (function) `headers/kernel.h:562` `void klog(log_level_t level, log_subsystem_t subsys, const char *fmt, ...);`
- `klog_hexdump` (function) `headers/kernel.h:564` `void klog_hexdump(log_level_t level, log_subsystem_t subsys, const void *data, unsigned long len, const char *label);`
- `klog_set_level` (function) `headers/kernel.h:566` `void klog_set_level(log_level_t level);`
- `klog_set_subsys_level` (function) `headers/kernel.h:567` `void klog_set_subsys_level(log_subsystem_t subsys, log_level_t level);`
- `klog_disable` (function) `headers/kernel.h:568` `void klog_disable(void);`
- `klog_enable` (function) `headers/kernel.h:569` `void klog_enable(void);`
- `shell_init` (function) `headers/kernel.h:572` `void shell_init(void);` -- LOG_SUBSYS_SHELL, LOG_SUBSYS_BOOT, LOG_SUBSYS_GENERAL, LOG_SUBSYS_COUNT } log_subsystem_t; void klog(log_level_t...
- `shell_run` (function) `headers/kernel.h:573` `void shell_run(void);`
- `console_getc` (function) `headers/kernel.h:574` `int console_getc(void);`
- `console_peek` (function) `headers/kernel.h:575` `int console_peek(void);`
- `redirect_suspend` (function) `headers/kernel.h:576` `int redirect_suspend(void);`
- `redirect_resume` (function) `headers/kernel.h:577` `void redirect_resume(int was);`
- `redirect_begin` (function) `headers/kernel.h:578` `int redirect_begin(void);`
- `redirect_commit` (function) `headers/kernel.h:579` `int redirect_commit(const char *path, int append_mode);`
- `redirect_take` (function) `headers/kernel.h:580` `char *redirect_take(unsigned long *len_out);`
- `redirect_pending` (function) `headers/kernel.h:581` `unsigned long redirect_pending(void);`
- `redirect_take_into` (function) `headers/kernel.h:582` `unsigned long redirect_take_into(char *dst, unsigned long cap, unsigned long *len_out);`
- `redirect_discard` (function) `headers/kernel.h:584` `void redirect_discard(void);`
- `redirect_active` (function) `headers/kernel.h:585` `int redirect_active(void);`
- `console_stdin_push` (function) `headers/kernel.h:586` `int console_stdin_push(const char *data, unsigned long len);`
- `console_stdin_clear` (function) `headers/kernel.h:587` `void console_stdin_clear(void);`
- `console_stdin_active` (function) `headers/kernel.h:588` `int console_stdin_active(void);`
- `panic_screen` (function) `headers/kernel.h:591` `void panic_screen(unsigned long vector, unsigned long err, unsigned long rip, unsigned long rsp, unsigned long rbp...` -- void redirect_resume(int was); int  redirect_begin(void); int  redirect_commit(const char *path, int append_mode)...
- `clip_set` (function) `headers/kernel.h:595` `int clip_set(const char *data, unsigned long len);` -- unsigned long redirect_pending(void); unsigned long redirect_take_into(char *dst, unsigned long cap, unsigned long...
- `clip_get` (function) `headers/kernel.h:596` `int clip_get(char *out, unsigned long cap);`
- `clip_clear` (function) `headers/kernel.h:597` `void clip_clear(void);`
- `clip_len_get` (function) `headers/kernel.h:598` `int clip_len_get(void);`
- `shell_take_redirect` (function) `headers/kernel.h:599` `int shell_take_redirect(int *argc, char **argv, char **path, int *append_mode);`
- `shell_run_any` (function) `headers/kernel.h:600` `int shell_run_any(const char *name, int argc, char **argv);`
- `shell_exec_builtin` (function) `headers/kernel.h:601` `void shell_exec_builtin(int argc, char **argv);`
- `shell_report_exit` (function) `headers/kernel.h:602` `void shell_report_exit(int code);`
- `shell_report` (function) `headers/kernel.h:603` `void shell_report(const char *what, const char *detail);`
- `kprog_slot` (function) `headers/kernel.h:628` `KProg *kprog_slot(const char *name);`
- `kprog_lookup` (function) `headers/kernel.h:629` `KProg *kprog_lookup(const char *name);`
- `ksym_resolve` (function) `headers/kernel.h:630` `void *ksym_resolve(const char *name);`
- `k_spawn` (function) `headers/kernel.h:631` `int k_spawn(const char *name, int argc, char **argv);`
- `k_register_program` (function) `headers/kernel.h:632` `void k_register_program(const char *name, prog_entry_t entry);`
- `k_register_process` (function) `headers/kernel.h:633` `void k_register_process(const char *name, void *proc_entry);`
- `k_register_symbol` (function) `headers/kernel.h:634` `void k_register_symbol(const char *name, void *addr);`
- `register_libc_symbols` (function) `headers/kernel.h:638` `void register_libc_symbols(void);` -- Libc name table for ET_REL programs (kernel/console.c).
- `k_exec_user` (function) `headers/kernel.h:641` `int k_exec_user(void *entry, int argc, char **argv);` -- Libc name table for ET_REL programs (kernel/console.c).
- `k_run_rel` (function) `headers/kernel.h:642` `int k_run_rel(prog_entry_t entry, int argc, char **argv);`
- `kexit` (function) `headers/kernel.h:643` `void kexit(int code);`
- `k_run_on_stack` (function) `headers/kernel.h:646` `int k_run_on_stack(void *stack_top, prog_entry_t entry, int argc, char **argv);` -- ET_REL stack switch (arch/x86/ctx_sw.S): runs entry(argc, argv) on * the 64 KB stack ending at stack_top.
- `ksetjmp` (function) `headers/kernel.h:651` `int ksetjmp(void *buf) __attribute__((returns_twice));`
- `klongjmp` (function) `headers/kernel.h:652` `void klongjmp(void *buf, int val) __attribute__((noreturn));`
- `setup_user_stack` (function) `headers/kernel.h:655` `unsigned long *setup_user_stack(char *sbase, unsigned long ssize, int argc, char **argv);`
- `vga_mode_set` (function) `headers/kernel.h:657` `void vga_mode_set(int on);`
- `vga_mode_is_active` (function) `headers/kernel.h:658` `int vga_mode_is_active(void);`
- `vga_gfx_ran_set` (function) `headers/kernel.h:659` `void vga_gfx_ran_set(int on);`
- `desktop_launch` (function) `headers/kernel.h:662` `void desktop_launch(const char *cmd);`
- `shell_queue_launch` (function) `headers/kernel.h:663` `void shell_queue_launch(const char *cmd);`
- `vga_fb_focus_next` (function) `headers/kernel.h:666` `void vga_fb_focus_next(void);` -- void klongjmp(void *buf, int val) __attribute__((noreturn)); extern kjmpbuf exec_return; extern int...
- `vga_fb_focus_id` (function) `headers/kernel.h:667` `int vga_fb_focus_id(int id);`
- `vga_fb_focus_get` (function) `headers/kernel.h:668` `int vga_fb_focus_get(void);`
- `vga_fb_nterms_get` (function) `headers/kernel.h:669` `int vga_fb_nterms_get(void);`
- `vga_fb_term_split` (function) `headers/kernel.h:670` `int vga_fb_term_split(void);`
- `vga_fb_term_close_focused` (function) `headers/kernel.h:671` `int vga_fb_term_close_focused(void);`
- `vga_fb_tile_all` (function) `headers/kernel.h:672` `void vga_fb_tile_all(void);`
- `vga_fb_list_windows` (function) `headers/kernel.h:673` `void vga_fb_list_windows(void);`
- `vga_fb_park_line` (function) `headers/kernel.h:674` `void vga_fb_park_line(const char *b, int p);`
- `vga_fb_unpark_line` (function) `headers/kernel.h:675` `int vga_fb_unpark_line(char *b, int *p);`
- `vga_fb_set_gfx_program` (function) `headers/kernel.h:676` `void vga_fb_set_gfx_program(const char *name);`
- `vga_fb_act_empty` (function) `headers/kernel.h:677` `int vga_fb_act_empty(void);`
- `vga_fb_prompt_live` (function) `headers/kernel.h:678` `int vga_fb_prompt_live(void);`
- `vga_fb_note_prompt` (function) `headers/kernel.h:679` `void vga_fb_note_prompt(void);`
- `vga_fb_clear_prompt` (function) `headers/kernel.h:680` `void vga_fb_clear_prompt(void);`
- `vga_fb_prompted` (function) `headers/kernel.h:681` `int vga_fb_prompted(void);`
- `shell_readline_active` (function) `headers/kernel.h:685` `int shell_readline_active(void);` -- Shell side of window focus: park/restore the half-typed input line so it * travels with its window.
- `shell_focus_park` (function) `headers/kernel.h:686` `void shell_focus_park(void);`
- `shell_focus_restore` (function) `headers/kernel.h:687` `void shell_focus_restore(void);`
- `user_range_ok` (function) `headers/kernel.h:692` `int user_range_ok(unsigned long p, unsigned long len);` -- Shell side of window focus: park/restore the half-typed input line so it * travels with its window.
- `user_str_ok` (function) `headers/kernel.h:693` `int user_str_ok(unsigned long p, unsigned long maxlen);`
- `mm_setup_protections` (function) `headers/kernel.h:696` `void mm_setup_protections(void);` -- Shell side of window focus: park/restore the half-typed input line so it * travels with its window.
- `pt_page_alloc` (function) `headers/kernel.h:697` `void *pt_page_alloc(void);`
- `pt_page_free` (function) `headers/kernel.h:698` `void pt_page_free(void *ptr);`
- `mm_user_pte_update` (function) `headers/kernel.h:699` `void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3);`
- `mm_user_set_exec` (function) `headers/kernel.h:700` `void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3);`
- `swap_out` (function) `headers/kernel.h:703` `int swap_out(unsigned long window_sz);` -- extern volatile int shell_fg_active; /*
- `swap_in` (function) `headers/kernel.h:704` `int swap_in(void);`
- `elf_load` (function) `headers/kernel.h:750` `void *elf_load(void *data, unsigned size, void **base_out);`
- `load_exec_elf` (function) `headers/kernel.h:751` `void *load_exec_elf(void *data, unsigned size);` -- Heap/mmap ceiling: the shared-library region starts here with the graphics tail above it, so brk growth and the mmap...
- `load_exec_elf_into` (function) `headers/kernel.h:752` `void *load_exec_elf_into(void *data, unsigned size, unsigned long cr3, unsigned long *brk_out, unsigned long *base_out);` -- Heap/mmap ceiling: the shared-library region starts here with the graphics tail above it, so brk growth and the mmap...
- `ldso_bind_into` (function) `headers/kernel.h:761` `int ldso_bind_into(void *data, unsigned size, unsigned long base, unsigned long cr3, vma_ctx_t *vma);` -- Minimal dynamic linker (T8 ld.so, kernel/loader.c). bind_into maps the DT_NEEDED libraries of an already-copied...
- `ldso_pseudo_stat` (function) `headers/kernel.h:763` `int ldso_pseudo_stat(int ino, unsigned long *size_out);`
- `ldso_pseudo_read` (function) `headers/kernel.h:764` `int ldso_pseudo_read(int ino, void *dst, unsigned long off, unsigned len);`
- `pt_clone_user_empty` (function) `headers/kernel.h:765` `unsigned long pt_clone_user_empty(void);`
- `mm_user_ensure_page` (function) `headers/kernel.h:766` `int mm_user_ensure_page(unsigned long cr3, unsigned long va);`
- `mm_user_map_page` (function) `headers/kernel.h:767` `int mm_user_map_page(unsigned long cr3, unsigned long va, unsigned long phys, int write, int exec);`
- `mm_file_fault` (function) `headers/kernel.h:769` `int mm_file_fault(unsigned long cr3, unsigned long va);`
- `mm_file_break` (function) `headers/kernel.h:770` `int mm_file_break(unsigned long cr3, unsigned long va);`
- `mm_file_page_phys` (function) `headers/kernel.h:771` `unsigned long mm_file_page_phys(unsigned long cr3, unsigned long va);`
- `mm_file_range_release` (function) `headers/kernel.h:772` `void mm_file_range_release(unsigned long cr3, unsigned long base, unsigned long len, int ino, unsigned long off, int...`
- `mm_demand_pte` (function) `headers/kernel.h:788` `unsigned long mm_demand_pte(unsigned long prot);` -- Anonymous demand paging (docs/spec/kernel.md): a reserved page is a non-present PTE carrying PTE_DEMAND and the...
- `mm_anon_reserve` (function) `headers/kernel.h:789` `int mm_anon_reserve(unsigned long cr3, unsigned long base, unsigned long len, unsigned long prot);`
- `mm_anon_fault` (function) `headers/kernel.h:791` `int mm_anon_fault(unsigned long cr3, unsigned long va, int write);`
- `pt_page_owned` (function) `headers/kernel.h:792` `int pt_page_owned(unsigned long phys);`
- `mm_anon_release` (function) `headers/kernel.h:793` `void mm_anon_release(unsigned long cr3, unsigned long base, unsigned long len);`
- `cow_drop_ref` (function) `headers/kernel.h:794` `int cow_drop_ref(unsigned long phys);`
- `refused` (function) `headers/kernel.h:800` `* refused (see kernel/mm/paging.c for the fail-closed list). */ unsigned long kmm_map_device(unsigned long phys...`
- `kmm_make_uncached` (function) `headers/kernel.h:802` `int kmm_make_uncached(unsigned long phys, unsigned long len);`
- `mm_copy_user_page` (function) `headers/kernel.h:803` `int mm_copy_user_page(unsigned long dst_cr3, unsigned long src_cr3, unsigned long va);`
- `fault` (function) `headers/kernel.h:807` `* fixes one write fault (0 = resume), cow_release_window drops a * dying window's shares ahead of pt_free_user. */...`
- `cow_resolve` (function) `headers/kernel.h:810` `int cow_resolve(unsigned long cr3, unsigned long va);`
- `user_page_present` (function) `headers/kernel.h:811` `int user_page_present(unsigned long cr3, unsigned long va);`
- `cow_release_window` (function) `headers/kernel.h:812` `void cow_release_window(unsigned long cr3);`
- `cow_shared` (function) `headers/kernel.h:813` `int cow_shared(void);`
- `cow_page_shared` (function) `headers/kernel.h:814` `int cow_page_shared(unsigned long phys);`
- `syscall_init` (function) `headers/kernel.h:817` `void syscall_init(void);` -- Copy-on-write fork (kernel/mm/cow.c): share on fork, privatize on first write. cow_fork_window builds the child...
- `ksyscall` (function) `headers/kernel.h:821` `long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);`
- `syscall_trace_enabled` (function) `headers/kernel.h:822` `long syscall_trace_enabled(void);`
- `syscall_trace_set` (function) `headers/kernel.h:823` `void syscall_trace_set(int on);`
- `syscall_trace_verbose_enabled` (function) `headers/kernel.h:824` `long syscall_trace_verbose_enabled(void);`
- `syscall_trace_verbose_set` (function) `headers/kernel.h:825` `void syscall_trace_verbose_set(int on);`
- `syscall_trace_shown` (function) `headers/kernel.h:826` `unsigned long syscall_trace_shown(void);`
- `syscall_name` (function) `headers/kernel.h:827` `const char *syscall_name(long n);`
- `kfd_get` (function) `headers/kernel.h:848` `KFILE *kfd_get(int fd);`
- `kfd_put` (function) `headers/kernel.h:849` `void kfd_put(KFILE *f);`
- `kfd_override` (function) `headers/kernel.h:850` `KFILE *kfd_override(int fd, KFILE *f);`
- `kpipe_pair` (function) `headers/kernel.h:851` `int kpipe_pair(KFILE **rend_out, KFILE **wend_out);`
- `kpipe_empty_wopen` (function) `headers/kernel.h:852` `int kpipe_empty_wopen(KFILE *f);`
- `kpipe_is_write_end` (function) `headers/kernel.h:853` `int kpipe_is_write_end(KFILE *f);`
- `kpipe_state` (function) `headers/kernel.h:856` `int kpipe_state(KFILE *f, unsigned *avail, unsigned *space, int *wopen, int *ropen);` -- Pipe snapshot for poll and the blocking syscall layer: bytes waiting, * free space, writer open, reader open. -1 on...
- `kfd_poll_revents` (function) `headers/kernel.h:859` `int kfd_poll_revents(int fd);` -- poll(2) readiness bits of a non-socket descriptor (kernel/syscalls.c): * pipes, eventfds, files and the console...
- `kevent_create` (function) `headers/kernel.h:865` `KFILE *kevent_create(unsigned long long initval, int semaphore);` -- eventfd(2) descriptions (docs/spec/smp-sched.md): create with an initial counter, read (0 or -EAGAIN when the...
- `kevent_read` (function) `headers/kernel.h:866` `long kevent_read(KFILE *f, unsigned long long *out);`
- `kevent_write` (function) `headers/kernel.h:867` `long kevent_write(KFILE *f, unsigned long long v);`
- `kevent_readable` (function) `headers/kernel.h:868` `int kevent_readable(KFILE *f);`
- `kevent_writable` (function) `headers/kernel.h:869` `int kevent_writable(KFILE *f);`
- `fd_lock` (function) `headers/kernel.h:872` `* fd_lock (never nested, never held across yields);`
- `C` (function) `headers/kernel.h:886` `* it with pointer subtraction in C (undefined behaviour). The value is
 * a link-time difference,...`
- `ktime_us` (function) `headers/kernel.h:896` `unsigned long ktime_us(void);`
- `wall_us_now` (function) `headers/kernel.h:897` `unsigned long wall_us_now(void);`
- `bootlog_mark` (function) `headers/kernel.h:900` `void bootlog_mark(const char *name);` -- it with pointer subtraction in C (undefined behaviour).
- `bootlog_report` (function) `headers/kernel.h:901` `void bootlog_report(void);`
- `pcspk_init` (function) `headers/kernel.h:904` `void pcspk_init(void);` -- static inline unsigned long ramdisk_image_size(void) { return (unsigned long)ramdisk_size; } /*
- `pcspk_tone` (function) `headers/kernel.h:905` `void pcspk_tone(unsigned freq);`
- `pcspk_off` (function) `headers/kernel.h:906` `void pcspk_off(void);`
- `pcspk_set_volume` (function) `headers/kernel.h:907` `void pcspk_set_volume(unsigned volume);`
- `pcspk_get_volume` (function) `headers/kernel.h:908` `unsigned pcspk_get_volume(void);`
- `rtc_read_tod` (function) `headers/kernel.h:911` `int rtc_read_tod(int *hour, int *min, int *sec);` -- unsigned long wall_us_now(void); /*
- `ide_init` (function) `headers/kernel.h:914` `void ide_init(void);` -- void bootlog_mark(const char *name); void bootlog_report(void); /*
- `ide_read_sectors` (function) `headers/kernel.h:915` `int ide_read_sectors(unsigned int lba, unsigned int count, void *buf);`
- `ide_write_sectors` (function) `headers/kernel.h:916` `int ide_write_sectors(unsigned int lba, unsigned int count, const void *buf);`
- `ide_read_sector` (function) `headers/kernel.h:917` `int ide_read_sector(unsigned int lba, void *buf);`
- `ide_write_sector` (function) `headers/kernel.h:918` `int ide_write_sector(unsigned int lba, const void *buf);`
- `ide_total_sectors` (function) `headers/kernel.h:919` `unsigned int ide_total_sectors(void);`
- `ide_present` (function) `headers/kernel.h:920` `int ide_present(void);`
- `block_init` (function) `headers/kernel.h:923` `void block_init(void);`
- `block_read` (function) `headers/kernel.h:924` `int block_read(unsigned int block_num, void *buf);`
- `block_write` (function) `headers/kernel.h:925` `int block_write(unsigned int block_num, const void *buf);`
- `block_read_multi` (function) `headers/kernel.h:926` `int block_read_multi(unsigned int block_num, unsigned int count, void *buf);`
- `block_write_multi` (function) `headers/kernel.h:927` `int block_write_multi(unsigned int block_num, unsigned int count, const void *buf);`
- `block_total` (function) `headers/kernel.h:928` `unsigned int block_total(void);`
- `k_user_fault_return` (function) `headers/kernel.h:931` `void k_user_fault_return(void);` -- int  ide_read_sector(unsigned int lba, void *buf); int  ide_write_sector(unsigned int lba, const void *buf)...


Next: [API_p4.md](API_p4.md)
