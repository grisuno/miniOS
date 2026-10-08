# API (page 1 of 19)
Pages: [API.md](API.md), [API_p2.md](API_p2.md), [API_p3.md](API_p3.md), [API_p4.md](API_p4.md), [API_p5.md](API_p5.md), [API_p6.md](API_p6.md), [API_p7.md](API_p7.md), [API_p8.md](API_p8.md), [API_p9.md](API_p9.md), [API_p10.md](API_p10.md), [API_p11.md](API_p11.md), [API_p12.md](API_p12.md), [API_p13.md](API_p13.md), [API_p14.md](API_p14.md), [API_p15.md](API_p15.md), [API_p16.md](API_p16.md), [API_p17.md](API_p17.md), [API_p18.md](API_p18.md), [API_p19.md](API_p19.md)

## arch/x86/ap_entry.S
Depends on: `headers/arch/x86/boot/bootdefs.h`
- `ap_stub_start` (function) `arch/x86/ap_entry.S:21`
- `ap_pm` (function) `arch/x86/ap_entry.S:39`
- `ap_lm` (function) `arch/x86/ap_entry.S:62`
- `ap_patch_slot` (function) `arch/x86/ap_entry.S:80`
- `ap_gdt32` (function) `arch/x86/ap_entry.S:84`
- `ap_gdt32_ptr` (function) `arch/x86/ap_entry.S:88` -- movw %ax, %ss /* Load smp_ap_entry()'s address from the BSP-patched slot and go. mov ap_patch_slot(%rip), %rax jmp...
- `ap_gdt32_end` (function) `arch/x86/ap_entry.S:91`
- `ap_gdt64_ptr` (function) `arch/x86/ap_entry.S:93`
- `ap_stub_end` (function) `arch/x86/ap_entry.S:98`

## arch/x86/boot/stage1.S
Depends on: `headers/arch/x86/boot/bootdefs.h`
- `main` (function) `arch/x86/boot/stage1.S:28`
- `normalize` (function) `arch/x86/boot/stage1.S:32`
- `no_extensions` (function) `arch/x86/boot/stage1.S:78`
- `read_failed` (function) `arch/x86/boot/stage1.S:82`
- `fail` (function) `arch/x86/boot/stage1.S:85`
- `halt` (function) `arch/x86/boot/stage1.S:88`
- `puts` (function) `arch/x86/boot/stage1.S:93`
- `puts_next` (function) `arch/x86/boot/stage1.S:97`
- `puts_done` (function) `arch/x86/boot/stage1.S:103`
- `msg_no_lba` (function) `arch/x86/boot/stage1.S:107`
- `msg_read` (function) `arch/x86/boot/stage1.S:109`

## arch/x86/boot/stage2.S
Depends on: `headers/arch/x86/boot/bootdefs.h`
- `stage2_main` (function) `arch/x86/boot/stage2.S:39`
- `a20_ready` (function) `arch/x86/boot/stage2.S:54`
- `load_chunk` (function) `arch/x86/boot/stage2.S:69`
- `chunk_size_ready` (function) `arch/x86/boot/stage2.S:74`
- `read_piece` (function) `arch/x86/boot/stage2.S:81`
- `piece_size_ready` (function) `arch/x86/boot/stage2.S:86`
- `chunk_copy` (function) `arch/x86/boot/stage2.S:118`
- `chunk_leave_pm` (function) `arch/x86/boot/stage2.S:131`
- `chunk_resume` (function) `arch/x86/boot/stage2.S:141`
- `enter_long_mode` (function) `arch/x86/boot/stage2.S:162`
- `fill_pt0_low` (function) `arch/x86/boot/stage2.S:190`
- `dma_uncache` (function) `arch/x86/boot/stage2.S:208`
- `fill_pt0_kernel` (function) `arch/x86/boot/stage2.S:216`
- `fill_pt1_kernel` (function) `arch/x86/boot/stage2.S:235`
- `fill_pt1_bss` (function) `arch/x86/boot/stage2.S:244`
- `fill_page_directory` (function) `arch/x86/boot/stage2.S:260` -- endif
- `read_failed` (function) `arch/x86/boot/stage2.S:289`
- `halt` (function) `arch/x86/boot/stage2.S:293`
- `puts` (function) `arch/x86/boot/stage2.S:298`
- `puts_next` (function) `arch/x86/boot/stage2.S:302`
- `puts_done` (function) `arch/x86/boot/stage2.S:308`
- `msg_read` (function) `arch/x86/boot/stage2.S:312`
- `vbe_probe` (function) `arch/x86/boot/stage2.S:325` -- Probe VESA BIOS Extensions for a high-resolution linear framebuffer and record it for the kernel in the fixed...
- `vbe_try_mode` (function) `arch/x86/boot/stage2.S:364` -- Try one VBE mode held in %bx.
- `vbe_try_bpp_ok` (function) `arch/x86/boot/stage2.S:395`
- `vbe_set_fail` (function) `arch/x86/boot/stage2.S:420`
- `vbe_try_fail` (function) `arch/x86/boot/stage2.S:423`
- `vbe_ok` (function) `arch/x86/boot/stage2.S:429`
- `kaslr_pick` (function) `arch/x86/boot/stage2.S:438` -- Pick the kernel's physical load base: a 2 MB-aligned address in the 64-position window above the kernel heap, seeded...
- `gdt32_start` (function) `arch/x86/boot/stage2.S:475`
- `gdt32_end` (function) `arch/x86/boot/stage2.S:481`
- `gdt32_ptr` (function) `arch/x86/boot/stage2.S:482`
- `gdt64_image` (function) `arch/x86/boot/stage2.S:487`
- `gdt64_ptr` (function) `arch/x86/boot/stage2.S:493`
- `saved_gdtr` (function) `arch/x86/boot/stage2.S:497`
- `sectors_left` (function) `arch/x86/boot/stage2.S:500`
- `chunk_sectors` (function) `arch/x86/boot/stage2.S:502`
- `next_lba` (function) `arch/x86/boot/stage2.S:504`
- `dest_addr` (function) `arch/x86/boot/stage2.S:506`
- `kaslr_dest` (function) `arch/x86/boot/stage2.S:508`

## arch/x86/ctx_sw.S
- `sched_park_capture` (function) `arch/x86/ctx_sw.S:70` -- captured the rest.
- `switch_save_only` (function) `arch/x86/ctx_sw.S:82`
- `switch_to` (function) `arch/x86/ctx_sw.S:91`
- `switch_to_notrap` (function) `arch/x86/ctx_sw.S:134`
- `user_trampoline` (function) `arch/x86/ctx_sw.S:221`
- `fork_trampoline` (function) `arch/x86/ctx_sw.S:233`
- `exec_enter` (function) `arch/x86/ctx_sw.S:249`
- `resume_iretq` (function) `arch/x86/ctx_sw.S:278`
- `k_run_on_stack` (function) `arch/x86/ctx_sw.S:318`

## arch/x86/syscall_entry.S
Depends on: `headers/syscall_asm.h`
- `syscall_kstack` (function) `arch/x86/syscall_entry.S:49`
- `kstack_base` (function) `arch/x86/syscall_entry.S:52`
- `sc_top_save_addr` (function) `arch/x86/syscall_entry.S:55`
- `syscall_entry` (function) `arch/x86/syscall_entry.S:65`

## bootloader.c
- `main` (function) `bootloader.c:21` `void main(void)`

## drivers/block.c
Depends on: `headers/block.h`, `headers/driver.h`, `headers/drivers/nvme.h`, `headers/drivers/usbblk.h`, `headers/drivers/virtio_blk.h`, `headers/ide.h`
- `bc_index` (function) `drivers/block.c:64` `static unsigned int bc_index(unsigned int block_num)`
- `bc_invalidate_locked` (function) `drivers/block.c:68` `static void bc_invalidate_locked(unsigned int block_num)`
- `bc_invalidate` (function) `drivers/block.c:73` `static void bc_invalidate(unsigned int block_num)`
- `block_init` (function) `drivers/block.c:80` `void block_init(void)`
- `block_set_base` (function) `drivers/block.c:113` `void block_set_base(unsigned int lba_base)`
- `table` (function) `drivers/block.c:122` `* ops table (dev->ops->read/write), never straight at the hardware. The * virtio queue wins when block_init...`
- `block_dev_read` (function) `drivers/block.c:128` `static int block_dev_read(unsigned lba, unsigned count, void *buf)` -- Strategy consumer: sector I/O goes through the registered block device's ops table (dev->ops->read/write), never...
- `block_dev_write` (function) `drivers/block.c:146` `static int block_dev_write(unsigned lba, unsigned count, const void *buf)`
- `block_read` (function) `drivers/block.c:164` `int block_read(unsigned int block_num, void *buf)`
- `block_write` (function) `drivers/block.c:205` `int block_write(unsigned int block_num, const void *buf)`
- `block_read_multi` (function) `drivers/block.c:214` `int block_read_multi(unsigned int block_num, unsigned int count, void *buf)`
- `block_write_multi` (function) `drivers/block.c:219` `int block_write_multi(unsigned int block_num, unsigned int count, const void *buf)`
- `block_flush` (function) `drivers/block.c:234` `void block_flush(void)`
- `block_total` (function) `drivers/block.c:236` `unsigned int block_total(void)`
- `block_read_sectors` (function) `drivers/block.c:244` `int block_read_sectors(unsigned lba, unsigned count, void *buf)` -- Docstring: Absolute sector read on the active backend, with no cache and no base offset: partition tables and...
- `block_disk_sectors` (function) `drivers/block.c:255` `unsigned long block_disk_sectors(void)` -- Docstring: Size of the active backend in sectors, so scanners fence to * the USB stick when it is the backend and...

## drivers/driver.c
Depends on: `headers/driver.h`
- `dev_len` (function) `drivers/driver.c:14` `static unsigned dev_len(const char *s)`
- `dev_copy` (function) `drivers/driver.c:20` `static void dev_copy(char *dst, const char *src, unsigned cap)`
- `dev_eq` (function) `drivers/driver.c:27` `static int dev_eq(const char *a, const char *b)`
- `device_reset` (function) `drivers/driver.c:32` `void device_reset(void)`
- `device_register` (function) `drivers/driver.c:44` `int device_register(device_t *dev)`
- `device_find` (function) `drivers/driver.c:66` `device_t *device_find(const char *name)`
- `device_find_by_type` (function) `drivers/driver.c:76` `device_t *device_find_by_type(int type)`
- `device_count` (function) `drivers/driver.c:85` `int device_count(void)`

## drivers/ide.c
Depends on: `headers/driver.h`, `headers/ide.h`
- `ide_delay` (function) `drivers/ide.c:13` `static void ide_delay(void)`
- `ide_read_status` (function) `drivers/ide.c:23` `static unsigned char ide_read_status(void)`
- `ide_wait_not_busy` (function) `drivers/ide.c:27` `static int ide_wait_not_busy(unsigned int timeout)`
- `ide_wait_drq` (function) `drivers/ide.c:40` `static int ide_wait_drq(unsigned int timeout)`
- `ide_select_drive` (function) `drivers/ide.c:53` `static void ide_select_drive(unsigned char drive)`
- `ide_soft_reset` (function) `drivers/ide.c:59` `static void ide_soft_reset(void)`
- `ide_identify` (function) `drivers/ide.c:66` `static int ide_identify(void)`
- `ide_init` (function) `drivers/ide.c:91` `void ide_init(void)`
- `ide_present` (function) `drivers/ide.c:110` `int ide_present(void)`
- `ide_total_sectors` (function) `drivers/ide.c:111` `unsigned int ide_total_sectors(void)`
- `ide_ops_read` (function) `drivers/ide.c:113` `static int ide_ops_read(device_t *dev, unsigned lba, unsigned count, void *buf)`
- `ide_ops_write` (function) `drivers/ide.c:118` `static int ide_ops_write(device_t *dev, unsigned lba, unsigned count, const void *buf)`
- `ide_ops_total` (function) `drivers/ide.c:123` `static unsigned ide_ops_total(device_t *dev)`
- `ide_ops_present` (function) `drivers/ide.c:128` `static int ide_ops_present(device_t *dev)`
- `ide_register_device` (function) `drivers/ide.c:148` `void ide_register_device(void)`
- `ide_read_sectors` (function) `drivers/ide.c:152` `int ide_read_sectors(unsigned int lba, unsigned int count, void *buf)`
- `ide_write_sectors` (function) `drivers/ide.c:184` `int ide_write_sectors(unsigned int lba, unsigned int count, const void *buf)`
- `ide_read_sector` (function) `drivers/ide.c:214` `int ide_read_sector(unsigned int lba, void *buf)`
- `ide_write_sector` (function) `drivers/ide.c:218` `int ide_write_sector(unsigned int lba, const void *buf)`

## drivers/kbd.c
Depends on: `headers/arch/x86/hal_io.h`, `headers/drivers/kbd.h`, `headers/drivers/modifiers.h`, `headers/sched.h`, `headers/vga_fb.h`, `headers/wm_events.h`
- `kbd_get_layout` (function) `drivers/kbd.c:100` `int kbd_get_layout(void)`
- `kbd_set_layout` (function) `drivers/kbd.c:101` `void kbd_set_layout(int layout)`
- `kbd_toggle_layout` (function) `drivers/kbd.c:105` `void kbd_toggle_layout(void)`
- `kbd_drop_counts` (function) `drivers/kbd.c:132` `void kbd_drop_counts(unsigned long *cooked, unsigned long *raw)` -- #define kbd_super (kbd_mods.super) #define kbd_altgr (kbd_mods.altgr) #define KBD_QUEUE_LEN 8 #define KBD_SCAN_DEL...
- `kbd_q_push` (function) `drivers/kbd.c:146` `void kbd_q_push(unsigned char c)`
- `kbd_raw_push_internal` (function) `drivers/kbd.c:156` `static void kbd_raw_push_internal(unsigned char c)`
- `kbd_q_empty` (function) `drivers/kbd.c:166` `int kbd_q_empty(void)`
- `kbd_q_pop` (function) `drivers/kbd.c:168` `int kbd_q_pop(void)`
- `kbd_available` (function) `drivers/kbd.c:175` `int kbd_available(void)`
- `kbd_raw_mode_get` (function) `drivers/kbd.c:181` `int kbd_raw_mode_get(void)`
- `kbd_raw_mode_set` (function) `drivers/kbd.c:182` `void kbd_raw_mode_set(int on)`
- `kbd_raw_empty` (function) `drivers/kbd.c:183` `int kbd_raw_empty(void)`
- `kbd_raw_pop` (function) `drivers/kbd.c:184` `int kbd_raw_pop(void)`
- `kbd_raw_push_byte` (function) `drivers/kbd.c:190` `void kbd_raw_push_byte(unsigned char c)`
- `kbd_e0_get` (function) `drivers/kbd.c:191` `int kbd_e0_get(void)`
- `kbd_e0_set` (function) `drivers/kbd.c:192` `void kbd_e0_set(int v)`
- `kbd_flush_all` (function) `drivers/kbd.c:193` `void kbd_flush_all(void)`
- `kbd_raw_flush` (function) `drivers/kbd.c:200` `void kbd_raw_flush(void)` -- Drop queued raw scancodes (shell-typed while a terminal owned PS/2) so a * newly focused game never replays them as...
- `paths` (function) `drivers/kbd.c:210` `* keeps the modifier state in sync on both paths (the old raw branch never * tracked Alt/Super, so a modifier held...`
- `too` (function) `drivers/kbd.c:215` `* too (DOOM strafes with Alt+arrows);`
- `raw_track_mods` (function) `drivers/kbd.c:221` `static int raw_track_mods(int code, int brk, int e0)`
- `wm_combo_dispatch` (function) `drivers/kbd.c:226` `static int wm_combo_dispatch(int action, int zone)` -- wm_raw_combo performs the WM action and reports 1 when the byte must be swallowed.
- `wm_raw_combo` (function) `drivers/kbd.c:278` `static int wm_raw_combo(int code, int e0)`
- `bare` (function) `drivers/kbd.c:297` `* second byte is not a WM combo is delivered bare (keypad alias): games map
 * both, so play surv...`
- `key` (function) `drivers/kbd.c:333` `* navigation key (which is pushed to the cooked queue as an escape sequence
 * instead) or a key ...`
- `kbd_read` (function) `drivers/kbd.c:449` `int kbd_read(void)`
- `kbd_reset_for_shell` (function) `drivers/kbd.c:463` `void kbd_reset_for_shell(void)`

## drivers/mouse.c
Depends on: `headers/arch/x86/hal_io.h`, `headers/drivers/mouse.h`
- `mouse_wait_data` (function) `drivers/mouse.c:20` `static void mouse_wait_data(void)`
- `mouse_write` (function) `drivers/mouse.c:24` `static void mouse_write(unsigned char data)`
- `mouse_read` (function) `drivers/mouse.c:31` `static unsigned char mouse_read(void)`
- `mouse_hw_init` (function) `drivers/mouse.c:36` `void mouse_hw_init(void)`
- `wrong` (function) `drivers/mouse.c:83` `* later packet is framed wrong (a left press reads back as bit 1, * motion warps), permanently. */...`
- `mouse_disable` (function) `drivers/mouse.c:112` `void mouse_disable(void)`
- `mouse_enable` (function) `drivers/mouse.c:113` `void mouse_enable(void)`

## drivers/nvme.c
Depends on: `headers/arch/x86/hal_io.h`, `headers/drivers/nvme.h`, `headers/drivers/pci.h`
- `xnv_outl` (function) `drivers/nvme.c:48` `static void xnv_outl(unsigned short port, unsigned val)`
- `xnv_inl` (function) `drivers/nvme.c:52` `static unsigned xnv_inl(unsigned short port)`
- `nvme_present` (function) `drivers/nvme.c:58` `int nvme_present(void)`
- `nvme_version` (function) `drivers/nvme.c:62` `unsigned nvme_version(void)`
- `nvme_note` (function) `drivers/nvme.c:66` `const char *nvme_note(void)`
- `xnv_r32` (function) `drivers/nvme.c:89` `static unsigned xnv_r32(unsigned off)`
- `xnv_w32` (function) `drivers/nvme.c:93` `static void xnv_w32(unsigned off, unsigned val)`
- `xnv_r64` (function) `drivers/nvme.c:97` `static unsigned long long xnv_r64(unsigned off)`
- `xnv_w64` (function) `drivers/nvme.c:102` `static void xnv_w64(unsigned off, unsigned long long val)`
- `xnv_put16` (function) `drivers/nvme.c:106` `static void xnv_put16(unsigned char *p, unsigned short v)`
- `xnv_put32` (function) `drivers/nvme.c:111` `static void xnv_put32(unsigned char *p, unsigned long v)`
- `xnv_put64` (function) `drivers/nvme.c:118` `static void xnv_put64(unsigned char *p, unsigned long long v)`
- `xnv_get32` (function) `drivers/nvme.c:124` `static unsigned long xnv_get32(const unsigned char *p)`
- `xnv_wait_rdy` (function) `drivers/nvme.c:129` `static int xnv_wait_rdy(unsigned want)`
- `xnv_next_cid` (function) `drivers/nvme.c:139` `static unsigned short xnv_next_cid(void)`
- `xnv_poll` (function) `drivers/nvme.c:145` `static int xnv_poll(unsigned char *cq, unsigned cq_db, unsigned short *head,
        unsigned sho...`
- `xnv_cmd` (function) `drivers/nvme.c:169` `static int xnv_cmd(unsigned char *sq, unsigned sq_db, unsigned char *cq,
        unsigned cq_db, ...`
- `xnv_queues` (function) `drivers/nvme.c:196` `static int xnv_queues(void)`
- `nvme_sectors` (function) `drivers/nvme.c:286` `unsigned long nvme_sectors(void)`
- `nvme_read_sectors` (function) `drivers/nvme.c:290` `int nvme_read_sectors(unsigned lba, unsigned count, void *buf)`
- `nvme_init` (function) `drivers/nvme.c:310` `int nvme_init(void)`

## drivers/pcm2.c
Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/pcm2.h`, `headers/pcm_ring.h`, `headers/sb16.h`, `headers/sched.h`, `headers/spinlock.h`
- `pcm2_dma` (function) `drivers/pcm2.c:79` `static unsigned char *pcm2_dma(void)`
- `pcm2_wait_write` (function) `drivers/pcm2.c:83` `static int pcm2_wait_write(void)`
- `pcm2_cmd` (function) `drivers/pcm2.c:90` `static void pcm2_cmd(unsigned char c)`
- `pcm2_dma_program` (function) `drivers/pcm2.c:95` `static void pcm2_dma_program(void)`
- `pcm2_dma_stop` (function) `drivers/pcm2.c:108` `static void pcm2_dma_stop(void)`
- `pcm2_dsp_play` (function) `drivers/pcm2.c:112` `static void pcm2_dsp_play(void)`
- `pcm2_wake_owner` (function) `drivers/pcm2.c:122` `static void pcm2_wake_owner(void)`
- `pcm2_arm_block` (function) `drivers/pcm2.c:135` `static void pcm2_arm_block(void)` -- Fill the DMA block from the ring (silence on underrun) and arm one single-cycle transfer.
- `loop` (function) `drivers/pcm2.c:150` `* loop (the auto-init livelock is structurally impossible here). The IRQ
 * path rejects a stray ...`
- `pcm2_active` (function) `drivers/pcm2.c:179` `int pcm2_active(void)`
- `pcm2_open` (function) `drivers/pcm2.c:183` `int pcm2_open(unsigned flags, int owner)`
- `pcm2_owner_live` (function) `drivers/pcm2.c:221` `static int pcm2_owner_live(void)`
- `pcm2_release_locked` (function) `drivers/pcm2.c:226` `static void pcm2_release_locked(void)`
- `pcm2_write` (function) `drivers/pcm2.c:235` `int pcm2_write(const unsigned char *user, unsigned len, int owner)`
- `pcm2_close` (function) `drivers/pcm2.c:282` `void pcm2_close(int owner)`
- `pcm2_irq` (function) `drivers/pcm2.c:293` `void pcm2_irq(void)`
- `pcm2_poll` (function) `drivers/pcm2.c:306` `void pcm2_poll(void)`
- `pcm2_counters` (function) `drivers/pcm2.c:318` `void pcm2_counters(pcm2_counters_t *out)`

## drivers/pcspk.c
Depends on: `headers/driver.h`, `headers/pcspk.h`
- `pcspk_ops_tone` (function) `drivers/pcspk.c:33` `static void pcspk_ops_tone(device_t *dev, unsigned freq)`
- `pcspk_ops_off` (function) `drivers/pcspk.c:38` `static void pcspk_ops_off(device_t *dev)`
- `pcspk_ops_set_volume` (function) `drivers/pcspk.c:43` `static void pcspk_ops_set_volume(device_t *dev, unsigned vol)`
- `pcspk_ops_get_volume` (function) `drivers/pcspk.c:48` `static unsigned pcspk_ops_get_volume(device_t *dev)`
- `pcspk_init` (function) `drivers/pcspk.c:72` `void pcspk_init(void)`
- `pcspk_set_volume` (function) `drivers/pcspk.c:78` `void pcspk_set_volume(unsigned volume)`
- `pcspk_get_volume` (function) `drivers/pcspk.c:82` `unsigned pcspk_get_volume(void)`
- `pcspk_tone` (function) `drivers/pcspk.c:86` `void pcspk_tone(unsigned freq)`
- `pcspk_off` (function) `drivers/pcspk.c:104` `void pcspk_off(void)`

## drivers/rtc.c
Depends on: `headers/rtc.h`
- `rtc_cmos_read` (function) `drivers/rtc.c:35` `static inline unsigned char rtc_cmos_read(unsigned char reg)`
- `rtc_from_bcd` (function) `drivers/rtc.c:40` `static int rtc_from_bcd(unsigned char v)`
- `rtc_read_tod` (function) `drivers/rtc.c:44` `int rtc_read_tod(int *hour, int *min, int *sec)`
- `rtc_month_len` (function) `drivers/rtc.c:68` `static int rtc_month_len(long full_year, long mon)`
- `rtc_read_date` (function) `drivers/rtc.c:78` `int rtc_read_date(int *year, int *mon, int *day)`
- `rtc_wall_seconds` (function) `drivers/rtc.c:102` `int rtc_wall_seconds(unsigned long *out)`

## drivers/sb16.c
Depends on: `headers/driver.h`, `headers/pcm2.h`, `headers/sb16.h`, `headers/sync.h`
- `IRQ` (function) `drivers/sb16.c:22` `* QEMU audio backends never raise the completion IRQ (they only consume once * their engine buffer drains, which a...`
- `sb16_kring_reset` (function) `drivers/sb16.c:118` `static void sb16_kring_reset(void)` -- Mixer stream id backing the legacy sb16_pcm_open/submit API (WQ_NONE when closed).
- `sb16_slot` (function) `drivers/sb16.c:130` `static unsigned char *sb16_slot(unsigned i)`
- `sb16_stream_open` (function) `drivers/sb16.c:138` `int sb16_stream_open(void)`
- `sb16_stream_close` (function) `drivers/sb16.c:154` `void sb16_stream_close(int id)`
- `sb16_stream_submit` (function) `drivers/sb16.c:162` `int sb16_stream_submit(int id, const unsigned char *pcm, unsigned len)`
- `sb16_stream_volume` (function) `drivers/sb16.c:177` `void sb16_stream_volume(int id, unsigned char vol)`
- `sb16_stream_count` (function) `drivers/sb16.c:183` `int sb16_stream_count(void)`
- `sb16_mix_all` (function) `drivers/sb16.c:194` `static void sb16_mix_all(void)`
- `sb16_pump` (function) `drivers/sb16.c:236` `void sb16_pump(void)`
- `sb16_wait_write` (function) `drivers/sb16.c:278` `static int sb16_wait_write(void)` -- DSP write-ready: bit 7 of the status port clear means the DSP accepts a command or data byte.
- `sb16_cmd` (function) `drivers/sb16.c:282` `static void sb16_cmd(unsigned char c)`
- `sb16_read_data` (function) `drivers/sb16.c:287` `static int sb16_read_data(unsigned char *out)`
- `sb16_reset_dsp` (function) `drivers/sb16.c:297` `static int sb16_reset_dsp(void)`
- `sb16_dma_play` (function) `drivers/sb16.c:323` `static void sb16_dma_play(unsigned addr, unsigned len)`
- `sb16_refill` (function) `drivers/sb16.c:339` `static void sb16_refill(int slot_index)`
- `sb16_arm` (function) `drivers/sb16.c:355` `static void sb16_arm(int from_irq)`
- `sb16_present` (function) `drivers/sb16.c:380` `int sb16_present(void)`
- `sb16_tone` (function) `drivers/sb16.c:382` `void sb16_tone(unsigned freq)`
- `sb16_pcm_open` (function) `drivers/sb16.c:398` `void sb16_pcm_open(void)`
- `sb16_pcm_close` (function) `drivers/sb16.c:422` `void sb16_pcm_close(void)`
- `sb16_pcm_submit` (function) `drivers/sb16.c:431` `int sb16_pcm_submit(const unsigned char *pcm, unsigned len)`
- `sb16_irq` (function) `drivers/sb16.c:449` `void sb16_irq(void)`
- `sb16_poll` (function) `drivers/sb16.c:457` `void sb16_poll(void)`
- `sb16_ring_free` (function) `drivers/sb16.c:466` `unsigned sb16_ring_free(void)`
- `sb16_mode_active` (function) `drivers/sb16.c:467` `int sb16_mode_active(void)`
- `sb16_legacy_busy` (function) `drivers/sb16.c:472` `int sb16_legacy_busy(void)` -- Audible legacy ownership for the pcm2 mutual exclusion: a PCM stream is always audible-by-contract, a tone only when...
- `sb16_counters` (function) `drivers/sb16.c:479` `void sb16_counters(sb16_counters_t *out)`
- `sb16_ops_present` (function) `drivers/sb16.c:484` `static int sb16_ops_present(device_t *dev)` -- stream is always audible-by-contract, a tone only when sounding. * Silent/idle legacy state (probe-only, tone(0))...
- `sb16_ops_pcm_open` (function) `drivers/sb16.c:491` `static void sb16_ops_pcm_open(device_t *dev)` -- } void sb16_counters(sb16_counters_t *out) { if (out) *out = sb16_stat; } /** Docstring: Strategy verbs publishing...
- `sb16_ops_pcm_close` (function) `drivers/sb16.c:498` `static void sb16_ops_pcm_close(device_t *dev)` -- static int sb16_ops_present(device_t *dev) { (void)dev; return sb16_present(); } /** Docstring: Strategy verb for...
- `sb16_ops_pcm_submit` (function) `drivers/sb16.c:505` `static int sb16_ops_pcm_submit(device_t *dev, const unsigned char *pcm, unsigned len)` -- static void sb16_ops_pcm_open(device_t *dev) { (void)dev; sb16_pcm_open(); } /** Docstring: Strategy verb for PCM...
- `sb16_init` (function) `drivers/sb16.c:530` `int sb16_init(void)`
- `pending` (function) `drivers/sb16.c:535` `* reading without it eats whatever byte happens to be pending (or * times out), so the probe used to fail or misread...`

## drivers/usbblk.c
Depends on: `headers/driver.h`, `headers/drivers/usbblk.h`, `headers/drivers/xhci.h`
Imported by: `tests/test_usbblk.c`
- `ubk_counters` (function) `drivers/usbblk.c:72` `void ubk_counters(ubk_counters_t *out)`
- `ubk_cdb10` (function) `drivers/usbblk.c:80` `static void ubk_cdb10(unsigned char *cdb, unsigned char opcode,
                      unsigned lo...` -- Docstring: Ten-byte SCSI CDB at the CBW command block: opcode, LBA big-endian, transfer length big-endian.
- `ubk_build_cbw` (function) `drivers/usbblk.c:92` `void ubk_build_cbw(unsigned char *out, unsigned tag, unsigned long lba,
                   unsign...`
- `ubk_check_csw` (function) `drivers/usbblk.c:121` `int ubk_check_csw(const unsigned char *csw, unsigned tag, unsigned expect_len)`
- `ubk_command_raw` (function) `drivers/usbblk.c:187` `static int ubk_command_raw(unsigned char *cdb, unsigned cdb_len,
                           unsig...` -- Docstring: Issue one command with an optional data stage and check the status wrapper. cdb carries cdb_len bytes (6...
- `ubk_sense` (function) `drivers/usbblk.c:262` `static void ubk_sense(void)` -- Docstring: REQUEST SENSE after a failure, so a unit attention clears instead of failing every later command, and the...
- `ubk_command` (function) `drivers/usbblk.c:279` `static int ubk_command(unsigned char *cdb, unsigned cdb_len,
                       unsigned char...` -- Docstring: One command with a single recovery: on a transport failure the pipe is reset and cleared and the command...
- `ubk_unit_ready` (function) `drivers/usbblk.c:294` `static int ubk_unit_ready(void)` -- Docstring: Wait for the medium with TEST UNIT READY.
- `ubk_read_capacity` (function) `drivers/usbblk.c:311` `static int ubk_read_capacity(unsigned long *sectors)` -- Docstring: Read the sector count with READ CAPACITY(10).
- `ubk_present` (function) `drivers/usbblk.c:336` `int ubk_present(void)`
- `ubk_sectors` (function) `drivers/usbblk.c:340` `unsigned long ubk_sectors(void)`
- `ubk_xfer` (function) `drivers/usbblk.c:347` `static int ubk_xfer(unsigned long lba, unsigned count, void *buf, int read)` -- Docstring: Move whole sectors.
- `ubk_read_sectors` (function) `drivers/usbblk.c:365` `int ubk_read_sectors(unsigned long lba, unsigned count, void *buf)`
- `ubk_write_sectors` (function) `drivers/usbblk.c:370` `int ubk_write_sectors(unsigned long lba, unsigned count, const void *buf)`
- `ubk_claim_eps` (function) `drivers/usbblk.c:377` `static int ubk_claim_eps(int device, const xhc_iface_t *iface)` -- Docstring: Take a bulk OUT and a bulk IN endpoint from a claimed interface * and program them.
- `ubk_blk_read` (function) `drivers/usbblk.c:421` `static int ubk_blk_read(device_t *dev, unsigned lba, unsigned count,
                        void...` -- Docstring: Block-ops adapters so the disk registers with the existing block layer instead of growing a parallel one.
- `ubk_blk_write` (function) `drivers/usbblk.c:427` `static int ubk_blk_write(device_t *dev, unsigned lba, unsigned count,
                         co...`
- `ubk_blk_sectors` (function) `drivers/usbblk.c:433` `static unsigned ubk_blk_sectors(device_t *dev)`
- `ubk_blk_present` (function) `drivers/usbblk.c:438` `static int ubk_blk_present(device_t *dev)`
- `ubk_init` (function) `drivers/usbblk.c:457` `int ubk_init(void)`

## drivers/usbhid.c
Depends on: `headers/arch/x86/hal_io.h`, `headers/drivers/kbd.h`, `headers/drivers/modifiers.h`, `headers/drivers/usbhid.h`, `headers/drivers/xhci.h`, `headers/vga_fb.h`
Imported by: `tests/test_usbhid.c`
- `usbhid_set1_from_usage` (function) `drivers/usbhid.c:117` `int usbhid_set1_from_usage(unsigned usage, unsigned char *sc, int *e0)`
- `usbhid_usage_make` (function) `drivers/usbhid.c:128` `static int usbhid_usage_make(unsigned usage, unsigned char *sc, int *e0)` -- Docstring: Set-1 make code for any usage, 0x04..0xDD.
- `usbhid_report_has` (function) `drivers/usbhid.c:138` `static int usbhid_report_has(const unsigned char report[HID_KBD_REPORT_LEN],
                    ...` -- Docstring: True when a report lists a usage in any slot but the given one.
- `usbhid_put` (function) `drivers/usbhid.c:153` `static int usbhid_put(unsigned char *out, int max, int n, unsigned char sc)` -- Docstring: Append one scancode or return USBHID_TRUNCATED.
- `usbhid_emit_mod` (function) `drivers/usbhid.c:165` `static int usbhid_emit_mod(unsigned char *out, int max, int n, unsigned bit,
                    ...` -- Docstring: Append the make or break bytes for one modifier bit.
- `usbhid_emit_usage` (function) `drivers/usbhid.c:183` `static int usbhid_emit_usage(unsigned char *out, int max, int n,
                             uns...` -- if (pressed) { if (e0) { n = usbhid_put(out, max, n, 0xE0); if (n < 0) return n; } return usbhid_put(out, max, n...
- `usbhid_kbd_scancodes` (function) `drivers/usbhid.c:206` `int usbhid_kbd_scancodes(const unsigned char prev[HID_KBD_REPORT_LEN],
                         c...`
- `usbhid_mouse_decode` (function) `drivers/usbhid.c:241` `void usbhid_mouse_decode(const unsigned char prev[HID_MOUSE_REPORT_LEN],
                        ...`
- `usbhid_keyboard_present` (function) `drivers/usbhid.c:256` `int usbhid_keyboard_present(void)`
- `usbhid_mouse_present` (function) `drivers/usbhid.c:263` `int usbhid_mouse_present(void)`
- `usbhid_counters` (function) `drivers/usbhid.c:270` `void usbhid_counters(usbhid_counters_t *out)`
- `usbhid_press_kbd_report` (function) `drivers/usbhid.c:274` `int usbhid_press_kbd_report(const unsigned char report[HID_KBD_REPORT_LEN])`
- `usbhid_set_boot_protocol` (function) `drivers/usbhid.c:295` `static int usbhid_set_boot_protocol(int device, int iface)` -- Docstring: Ask a HID device for boot protocol, so its reports use the fixed layout this driver decodes.
- `usbhid_ep_taken` (function) `drivers/usbhid.c:312` `static int usbhid_ep_taken(int ep_index)` -- Docstring: True when an endpoint index is already spoken for.
- `usbhid_take_ep` (function) `drivers/usbhid.c:325` `static int usbhid_take_ep(int device, const xhc_iface_t *iface,
                          int *maxp)` -- Docstring: Take an interrupt IN endpoint from a claimed interface and program it, at the first free endpoint index.
- `usbhid_claim` (function) `drivers/usbhid.c:353` `static int usbhid_claim(int device, const xhc_iface_t *iface, int is_mouse)` -- Docstring: Claim a HID interface as a keyboard or a mouse.
- `usbhid_is_mouse_maxp` (function) `drivers/usbhid.c:380` `static int usbhid_is_mouse_maxp(int maxp)` -- Docstring: Endpoint packet size that distinguishes a boot keyboard (eight bytes) from a boot mouse (three or four).
- `usbhid_init` (function) `drivers/usbhid.c:384` `int usbhid_init(void)`
- `usbhid_poll_one` (function) `drivers/usbhid.c:422` `static int usbhid_poll_one(usbhid_dev_t *d)` -- Docstring: One interrupt-in report from a device and hand it to a decoder.
- `usbhid_poll_keyboard` (function) `drivers/usbhid.c:483` `int usbhid_poll_keyboard(void)`
- `usbhid_poll_mouse` (function) `drivers/usbhid.c:491` `int usbhid_poll_mouse(void)`
- `usbhid_poll` (function) `drivers/usbhid.c:499` `int usbhid_poll(void)`

## drivers/virtio_blk.c
Depends on: `headers/driver.h`, `headers/drivers/pci.h`, `headers/drivers/virtio_blk.h`
- `vblk_outl` (function) `drivers/virtio_blk.c:71` `static void vblk_outl(unsigned short port, unsigned val)`
- `vblk_inl` (function) `drivers/virtio_blk.c:75` `static unsigned vblk_inl(unsigned short port)`
- `vblk_outb` (function) `drivers/virtio_blk.c:81` `static void vblk_outb(unsigned short port, unsigned char val)`
- `vblk_inb` (function) `drivers/virtio_blk.c:85` `static unsigned char vblk_inb(unsigned short port)`
- `vblk_inw` (function) `drivers/virtio_blk.c:89` `static unsigned short vblk_inw(unsigned short port)`
- `vblk_outw` (function) `drivers/virtio_blk.c:93` `static void vblk_outw(unsigned short port, unsigned short val)`
- `vblk_init` (function) `drivers/virtio_blk.c:100` `int vblk_init(void)` -- Docstring: Probe PCI for a virtio-blk device and bring queue 0 up.
- `vblk_present` (function) `drivers/virtio_blk.c:158` `int vblk_present(void)` -- { unsigned long cap_lo = vblk_inl(vblk_iobase + 0x14); unsigned long cap_hi = vblk_inl(vblk_iobase + 0x18)...
- `vblk_sectors` (function) `drivers/virtio_blk.c:163` `unsigned long vblk_sectors(void)` -- } vblk_outb(vblk_iobase + 0x12, VBLK_F_ACK | VBLK_F_DRIVER | VBLK_F_OK | VBLK_F_DRIVER_OK); vblk_last_used = 0...
- `vblk_desc` (function) `drivers/virtio_blk.c:167` `static void vblk_desc(unsigned idx, unsigned long addr, unsigned len,
        unsigned short flag...`
- `vblk_avail_idx` (function) `drivers/virtio_blk.c:183` `static unsigned short vblk_avail_idx(void)`
- `vblk_avail_push` (function) `drivers/virtio_blk.c:188` `static void vblk_avail_push(unsigned short head)`
- `vblk_used_idx` (function) `drivers/virtio_blk.c:199` `static unsigned short vblk_used_idx(void)`
- `vblk_request` (function) `drivers/virtio_blk.c:212` `static int vblk_request(unsigned dir, unsigned long sector,
        unsigned char *buf, unsigned ...` -- Docstring: One synchronous request. dir 0 reads sectors into buf, 1 writes them out.
- `vblk_write_sectors` (function) `drivers/virtio_blk.c:266` `int vblk_write_sectors(unsigned lba, unsigned count, const void *buf)` -- Docstring: Write count sectors from buf at lba.
- `vblk_ops_read` (function) `drivers/virtio_blk.c:282` `static int vblk_ops_read(device_t *dev, unsigned lba, unsigned count,
        void *buf)` -- Docstring: Registry ops for the block layer dispatch.
- `vblk_ops_write` (function) `drivers/virtio_blk.c:289` `static int vblk_ops_write(device_t *dev, unsigned lba, unsigned count,
        const void *buf)` -- Docstring: Registry ops for the block layer dispatch.
- `vblk_ops_total` (function) `drivers/virtio_blk.c:296` `static unsigned vblk_ops_total(device_t *dev)` -- static int vblk_ops_read(device_t *dev, unsigned lba, unsigned count, void *buf) { (void)dev; return...
- `vblk_ops_present` (function) `drivers/virtio_blk.c:302` `static int vblk_ops_present(device_t *dev)` -- /** Docstring: Registry write op, const buffer through the queue. static int vblk_ops_write(device_t *dev, unsigned...
- `vblk_register_device` (function) `drivers/virtio_blk.c:327` `void vblk_register_device(void)` -- Docstring: Publish vblk0 for the block layer preference.

## drivers/virtio_net.c
Depends on: `headers/drivers/pci.h`, `headers/drivers/virtio_net.h`, `headers/net.h`
- `vnet_outb` (function) `drivers/virtio_net.c:81` `static void vnet_outb(unsigned short port, unsigned char v)`
- `vnet_outw` (function) `drivers/virtio_net.c:85` `static void vnet_outw(unsigned short port, unsigned short v)`
- `vnet_outl` (function) `drivers/virtio_net.c:89` `static void vnet_outl(unsigned short port, unsigned v)`
- `vnet_inb` (function) `drivers/virtio_net.c:93` `static unsigned char vnet_inb(unsigned short port)`
- `vnet_inw` (function) `drivers/virtio_net.c:99` `static unsigned short vnet_inw(unsigned short port)`
- `vnet_inl` (function) `drivers/virtio_net.c:105` `static unsigned vnet_inl(unsigned short port)`
- `vnet_queue_up` (function) `drivers/virtio_net.c:114` `static unsigned vnet_queue_up(unsigned qsel)` -- Docstring: Bring one queue up: negotiate no features, size it, publish its page area, return its depth.
- `vnet_desc` (function) `drivers/virtio_net.c:144` `static void vnet_desc(unsigned char *page, unsigned idx, unsigned long addr,
        unsigned len...` -- vnet_outl(vnet_io + 0x08, (unsigned)pfn); if (qsel == VNET_Q_RX) { vnet_rx_page = page; vnet_rx_used = page +...
- `vnet_avail_push` (function) `drivers/virtio_net.c:161` `static void vnet_avail_push(unsigned char *page, unsigned qnum,
        unsigned short head)` -- unsigned i; for (i = 0; i < 8; i++) d[i] = (unsigned char)((addr >> (i * 8)) & 0xFFu); d[8] = (unsigned char)(len &...
- `vnet_used_idx` (function) `drivers/virtio_net.c:174` `static unsigned short vnet_used_idx(unsigned char *used)` -- /** Docstring: Push one head descriptor index onto a queue avail ring. static void vnet_avail_push(unsigned char...
- `unusable` (function) `drivers/virtio_net.c:181` `* unusable (fail-closed, rtl8139 stays). */
int vnet_init(void)`
- `vnet_present` (function) `drivers/virtio_net.c:223` `int vnet_present(void)` -- vnet_desc(vnet_rx_page, i, (unsigned long)(vnet_rx_bufs + i * VNET_RX_SIZE), VNET_RX_SIZE, VNET_DESC_WRITE, 0u)...
- `vnet_get_mac` (function) `drivers/virtio_net.c:228` `void vnet_get_mac(unsigned char out[6])` -- vnet_outb(vnet_io + 0x12, VNET_F_ACK | VNET_F_DRIVER | VNET_F_OK | VNET_F_DRIVER_OK); vnet_rx_last = 0; vnet_tx_last...
- `vnet_iobase` (function) `drivers/virtio_net.c:234` `unsigned short vnet_iobase(void)` -- } /** Docstring: True once vnet_init brought the queues up. int vnet_present(void) { return vnet_on; } /**...
- `vnet_counters` (function) `drivers/virtio_net.c:239` `void vnet_counters(unsigned int *tx_frames, unsigned int *rx_frames)` -- } /** Docstring: Copy the NIC MAC into out (NET_ETH_ALEN bytes). void vnet_get_mac(unsigned char out[6]) { unsigned...
- `vnet_link_up` (function) `drivers/virtio_net.c:277` `int vnet_link_up(void)` -- vnet_avail_push(vnet_tx_page, vnet_tx_qnum, 0u); vnet_outw(vnet_io + 0x10, (unsigned short)VNET_Q_TX); deadline =...
- `vnet_poll` (function) `drivers/virtio_net.c:287` `void vnet_poll(void)` -- Docstring: Drain completed RX buffers into net_rx_handle_frame, reposting every descriptor.


Next: [API_p2.md](API_p2.md)
