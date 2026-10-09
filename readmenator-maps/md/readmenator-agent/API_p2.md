# API (page 2 of 19)
Previous: [API.md](API.md)

## drivers/xhci.c
Depends on: `headers/arch/x86/hal_io.h`, `headers/drivers/pci.h`, `headers/drivers/xhci.h`
Imported by: `tests/test_usbblk.c`, `tests/test_usbhid.c`, `tests/test_xhci.c`
- `xhc_ep_b` (function) `drivers/xhci.c:296` `static unsigned xhc_ep_b(void)`
- `xhc_stride` (function) `drivers/xhci.c:300` `static unsigned xhc_stride(void)`
- `xhc_put32` (function) `drivers/xhci.c:327` `static void xhc_put32(unsigned char *base, unsigned off, unsigned val)`
- `xhc_get32` (function) `drivers/xhci.c:334` `static unsigned xhc_get32(const unsigned char *base, unsigned off)`
- `xhc_put64` (function) `drivers/xhci.c:339` `static void xhc_put64(unsigned char *base, unsigned off,
                      unsigned long long...`
- `xhc_put16` (function) `drivers/xhci.c:345` `static void xhc_put16(unsigned char *base, unsigned off, unsigned val)`
- `xhc_puttrb` (function) `drivers/xhci.c:350` `static void xhc_puttrb(xhc_trb_t *trb, unsigned long long param,
                       unsigned ...`
- `xhc_op_read32` (function) `drivers/xhci.c:359` `static unsigned xhc_op_read32(unsigned off)`
- `xhc_op_write32` (function) `drivers/xhci.c:363` `static void xhc_op_write32(unsigned off, unsigned val)`
- `xhc_run_write32` (function) `drivers/xhci.c:367` `static void xhc_run_write32(unsigned off, unsigned val)`
- `xhc_run_read32` (function) `drivers/xhci.c:371` `static unsigned xhc_run_read32(unsigned off)`
- `xhc_now_ms` (function) `drivers/xhci.c:375` `static unsigned long xhc_now_ms(void)`
- `xhc_flush` (function) `drivers/xhci.c:386` `static void xhc_flush(const void *p, unsigned long len)` -- Docstring: Write back and invalidate the cache lines covering a range the controller can reach.
- `xhc_idle` (function) `drivers/xhci.c:393` `static void xhc_idle(unsigned spin)`
- `xhc_slot_ctx` (function) `drivers/xhci.c:400` `static unsigned char *xhc_slot_ctx(int slot)` -- --- Context addressing ---- * Device context N lives at xhc_ctx + N * stride; slot 0 is unused.
- `xhc_ep_ctx` (function) `drivers/xhci.c:404` `static unsigned char *xhc_ep_ctx(int slot, int ep)`
- `xhc_in_slot` (function) `drivers/xhci.c:409` `static unsigned char *xhc_in_slot(void)`
- `xhc_in_ep` (function) `drivers/xhci.c:413` `static unsigned char *xhc_in_ep(int ci)`
- `xhc_ep_ctx_build` (function) `drivers/xhci.c:418` `static void xhc_ep_ctx_build(unsigned char *ep, unsigned type,
                             unsig...` -- static unsigned char *xhc_ep_ctx(int slot, int ep) { return xhc_slot_ctx(slot) + xhc_ep_b() + (unsigned...
- `xhc_slot_ctx_build` (function) `drivers/xhci.c:439` `static void xhc_slot_ctx_build(unsigned char *sc, unsigned speed,
                               ...` -- dw0 = ((mult & 0x3u) << XHC_EP_MULT_SHIFT) | ((interval & 0xFFu) << XHC_EP_INTERVAL_SHIFT); dw1 = (XHC_EP_CERR &...
- `xhc_arm_link_trb` (function) `drivers/xhci.c:458` `static void xhc_arm_link_trb(xhc_trb_t *ring, unsigned gen)` -- Docstring: Toggle-cycle bit of a Link TRB.
- `xhc_arm_link` (function) `drivers/xhci.c:465` `static void xhc_arm_link(void)`
- `xhc_cmd_wrap` (function) `drivers/xhci.c:477` `static void xhc_cmd_wrap(void)`
- `xhc_cmd_maybe_arm` (function) `drivers/xhci.c:483` `static void xhc_cmd_maybe_arm(void)`
- `xhc_cmd_slot` (function) `drivers/xhci.c:494` `static xhc_trb_t *xhc_cmd_slot(void)` -- Docstring: Fill one command-ring slot without ringing the doorbell.
- `xhc_cmd_ring_doorbell` (function) `drivers/xhci.c:506` `static void xhc_cmd_ring_doorbell(void)` -- Docstring: Ring the command doorbell.
- `xhc_slot_doorbell` (function) `drivers/xhci.c:519` `static void xhc_slot_doorbell(int slot, int ep)` -- Docstring: Ring a slot doorbell for endpoint context index ep: DCI is the * index plus one, and EP0 rings target 1.
- `xhc_evt_next` (function) `drivers/xhci.c:535` `static xhc_trb_t *xhc_evt_next(void)` -- Docstring: Next event TRB, or 0 when the ring is empty.
- `xhc_evt_trb_ptr` (function) `drivers/xhci.c:552` `static xhc_trb_t *xhc_evt_trb_ptr(xhc_trb_t *ev)` -- Docstring: The TRB a completion names, as a host pointer.
- `xhc_evt_advance` (function) `drivers/xhci.c:559` `static void xhc_evt_advance(void)` -- Docstring: Tell the controller the event ring was drained: ERDP advances to the dequeue pointer with EHB set to...
- `xhc_pending_claim_len` (function) `drivers/xhci.c:570` `static int xhc_pending_claim_len(xhc_trb_t *trb, unsigned len)`
- `xhc_pending_claim` (function) `drivers/xhci.c:586` `static int xhc_pending_claim(xhc_trb_t *trb)`
- `xhc_pending_drop` (function) `drivers/xhci.c:590` `static void xhc_pending_drop(int token)`
- `xhc_poll` (function) `drivers/xhci.c:595` `int xhc_poll(void)`
- `xhc_wait` (function) `drivers/xhci.c:638` `static int xhc_wait(int token, unsigned budget_ms)` -- Docstring: Wait for a pending transfer to complete.
- `xhc_status` (function) `drivers/xhci.c:654` `static int xhc_status(int token)` -- if (token < 1 || token > XHC_MAX_PENDING) return 0; end = xhc_now_ms() + budget_ms; for (;;) { xhc_poll(); if...
- `xhc_cmd_run_ep` (function) `drivers/xhci.c:663` `static int xhc_cmd_run_ep(unsigned type, unsigned long long param,
                            un...` -- Docstring: Submit one command TRB and wait for its completion, by TRB pointer so a completion for anything else is...
- `xhc_cmd_run` (function) `drivers/xhci.c:709` `static int xhc_cmd_run(unsigned type, unsigned long long param, unsigned slot,
                  ...`
- `xhc_ep_command` (function) `drivers/xhci.c:719` `static int xhc_ep_command(unsigned type, int slot, int dci)` -- Docstring: Stop, reset and re-point one endpoint's transfer ring.
- `xhc_reset_endpoint` (function) `drivers/xhci.c:723` `int xhc_reset_endpoint(int index, int ep_index)`
- `xhc_port_count` (function) `drivers/xhci.c:749` `int xhc_port_count(void)`
- `xhc_port_state` (function) `drivers/xhci.c:753` `int xhc_port_state(int port, xhc_port_t *out)`
- `xhc_port_reset` (function) `drivers/xhci.c:776` `int xhc_port_reset(int port)` -- Docstring: Ask a port to reset, and wait for it to settle.
- `xhc_device_count` (function) `drivers/xhci.c:806` `int xhc_device_count(void)`
- `xhc_device_info` (function) `drivers/xhci.c:814` `int xhc_device_info(int index, xhc_dev_t *out)`
- `xhc_dev_alloc` (function) `drivers/xhci.c:833` `static int xhc_dev_alloc(void)` -- out->address = 0; } if (index < 0 || index >= XHC_MAX_DEVICES) return 0; if (!xhc_devs[index].used) return 0; if...
- `xhc_dev_release` (function) `drivers/xhci.c:843` `static void xhc_dev_release(int index)` -- Docstring: Release one device record after a failed enumeration: its EP0 ring and cached descriptor go back, so a...
- `xhc_open_interface` (function) `drivers/xhci.c:863` `int xhc_open_interface(int index, unsigned cls, unsigned sub, unsigned proto,
                   ...`
- `xhc_ring_wrap` (function) `drivers/xhci.c:936` `static void xhc_ring_wrap(int index, xhc_ring_t *ring, int ep)` -- Docstring: Wrap a transfer ring instead of refusing after a thousand transfers: the producer goes back to slot zero...
- `xhc_ring_maybe_arm` (function) `drivers/xhci.c:949` `static void xhc_ring_maybe_arm(xhc_ring_t *ring)`
- `xhc_ep0_slot` (function) `drivers/xhci.c:959` `static xhc_trb_t *xhc_ep0_slot(int index)` -- Docstring: Post one TRB on a device EP0 transfer ring, wrapping instead of refusing.
- `xhc_ep0_bump` (function) `drivers/xhci.c:971` `static void xhc_ep0_bump(int index)`
- `xhc_control_stage` (function) `drivers/xhci.c:979` `static int xhc_control_stage(int index, const unsigned char setup[8],
                           ...` -- Docstring: One control transfer on the device EP0 transfer ring: a setup TRB with IDT, an optional data TRB and a...
- `xhc_control` (function) `drivers/xhci.c:1048` `int xhc_control(int index, const unsigned char setup[8], void *data,
                unsigned len...` -- Docstring: USB is lossy and emulated controllers occasionally drop a completion, so a control transfer retries its...
- `xhc_setup_nodata` (function) `drivers/xhci.c:1069` `static void xhc_setup_nodata(unsigned char *setup, unsigned char type,
                          ...` -- Docstring: Pack a standard request with no data stage: bmRequestType, * bRequest, wValue, wIndex.
- `xhc_setup_data` (function) `drivers/xhci.c:1082` `static void xhc_setup_data(unsigned char *setup, unsigned char type,
                           u...` -- Docstring: Pack a standard request with a data stage of a known length: * same as above with wLength filled in.
- `xhc_dci` (function) `drivers/xhci.c:1093` `static int xhc_dci(int ep_addr)` -- Docstring: Endpoint context index for a USB endpoint address: DCI is one * plus twice the endpoint number plus the...
- `xhc_configure_endpoint` (function) `drivers/xhci.c:1100` `int xhc_configure_endpoint(int index, int ep_index, int ep_addr, int ep_type,
                   ...`
- `xhc_ep_post` (function) `drivers/xhci.c:1162` `static int xhc_ep_post(int index, int ep_index, void *buf, unsigned len)` -- Docstring: Post one Normal TRB with IOC on an endpoint's ring and ring its * slot doorbell.
- `xhc_got` (function) `drivers/xhci.c:1197` `static int xhc_got(int token)` -- len & 0x1FFFFu, (unsigned)(XHC_TRB_MAKE_TYPE(XHC_TRB_TYPE_NORMAL) | ring->gen | XHC_TRB_IOC)); xhc_flush(trb...
- `xhc_transfer` (function) `drivers/xhci.c:1202` `int xhc_transfer(int index, int ep_index, void *buf, unsigned len, int *got)`
- `xhc_transfer_async` (function) `drivers/xhci.c:1222` `int xhc_transfer_async(int index, int ep_index, void *buf, unsigned len)` -- Docstring: Post one endpoint transfer without waiting: the completion arrives on the event ring and is collected by...
- `xhc_poll_token_limit` (function) `drivers/xhci.c:1233` `int xhc_poll_token_limit(int token, unsigned budget_ms)` -- Docstring: Non-blocking completion check for xhc_transfer_async.
- `xhc_poll_token` (function) `drivers/xhci.c:1252` `int xhc_poll_token(int token)`
- `xhc_address` (function) `drivers/xhci.c:1261` `static int xhc_address(int index, int slot, int port, int speed)` -- Docstring: Enable a slot and build its device context with a working control endpoint on its own transfer ring.
- `xhc_get_device_desc` (function) `drivers/xhci.c:1316` `static int xhc_get_device_desc(int index, unsigned char *buf)` -- Docstring: Fetch the device descriptor. wValue packs the descriptor type * above the index: a device descriptor is...
- `xhc_get_config_desc` (function) `drivers/xhci.c:1333` `static int xhc_get_config_desc(int index, unsigned char *buf, unsigned *len)` -- Docstring: Fetch the configuration descriptor.
- `xhc_enumerate` (function) `drivers/xhci.c:1358` `int xhc_enumerate(int port)`
- `xhc_enumerate_all` (function) `drivers/xhci.c:1444` `int xhc_enumerate_all(void)`
- `xhc_outl` (function) `drivers/xhci.c:1454` `static void xhc_outl(unsigned short port, unsigned val)`
- `xhc_inl` (function) `drivers/xhci.c:1458` `static unsigned xhc_inl(unsigned short port)`
- `xhc_free_all` (function) `drivers/xhci.c:1464` `static void xhc_free_all(void)`
- `xhc_alloc_all` (function) `drivers/xhci.c:1494` `static int xhc_alloc_all(unsigned max_slots)` -- Docstring: Allocate the command ring, the event ring, the ERST, the DCBAA and the context array.
- `xhc_start` (function) `drivers/xhci.c:1593` `static int xhc_start(unsigned contexts)` -- Docstring: Reset the controller, program its ring state, and bring it to run.
- `xhc_init` (function) `drivers/xhci.c:1658` `int xhc_init(void)`
- `xhc_counters` (function) `drivers/xhci.c:1790` `void xhc_counters(xhc_counters_t *out)`
- `xhc_probe_note` (function) `drivers/xhci.c:1794` `const char *xhc_probe_note(void)`
- `xhc_info` (function) `drivers/xhci.c:1798` `int xhc_info(unsigned *version, unsigned *slots, unsigned *ports,
             unsigned *caplength)`

## fs/ext4.c
Depends on: `headers/block.h`, `headers/ext4.h`, `headers/fsimg.h`, `headers/minifs.h`
Imported by: `tests/test_ext4.c`
- `ext_ld16` (function) `fs/ext4.c:32` `static unsigned ext_ld16(const unsigned char *p)`
- `ext_ld32` (function) `fs/ext4.c:36` `static unsigned long ext_ld32(const unsigned char *p)`
- `ext_parse_sb` (function) `fs/ext4.c:55` `static int ext_parse_sb(const fsimg_t *img, ext_geo_t *g)`
- `ext_inode_off` (function) `fs/ext4.c:92` `static int ext_inode_off(const fsimg_t *img, const ext_geo_t *g,
                         unsigne...` -- Byte offset of an inode.
- `ext_read_inode` (function) `fs/ext4.c:122` `static int ext_read_inode(const fsimg_t *img, const ext_geo_t *g,
                          unsig...`
- `ext_map_down` (function) `fs/ext4.c:168` `static int ext_map_down(const fsimg_t *img, const ext_geo_t *g, const unsigned char *root, unsigned nent, unsigned...`
- `ext_map` (function) `fs/ext4.c:171` `static int ext_map(const fsimg_t *img, const ext_geo_t *g,
                   const unsigned char...`
- `ext_map_leaf` (function) `fs/ext4.c:211` `static int ext_map_leaf(const fsimg_t *img, const ext_geo_t *g,
                        const uns...` -- } r = ext_map_down(img, g, root, nent, lblk, node); if (r <= 0) break; for (d = 0; d < 60 && d < g->bs; d++) root[d]...
- `only` (function) `fs/ext4.c:352` `* listings only ('.' skipped, '..' refused). "" or "/" is root (2). */ static int ext_file_block(const fsimg_t *img...`
- `ext_resolve` (function) `fs/ext4.c:356` `static int ext_resolve(const fsimg_t *img, const ext_geo_t *g,
                       const char ...`
- `ext_file_block` (function) `fs/ext4.c:464` `static int ext_file_block(const fsimg_t *img, const ext_geo_t *g,
                          const...` -- Read one logical file block of an open inode into blk (block * sized).
- `ext4_list` (function) `fs/ext4.c:485` `int ext4_list(const char *imgpath, const char *dirpath,
              char names[][EXT4_NAME_MAX ...`
- `ext_split` (function) `fs/ext4.c:580` `static int ext_split(const char *path, char *img, char *extp)` -- Split "imgpath:extpath" (first ':' wins; image names never carry * one). ext paths run deeper than FAT, hence the...
- `ext4_vfs_open` (function) `fs/ext4.c:585` `int ext4_vfs_open(const char *path, int mode, void **handle)`
- `ext4_vfs_read` (function) `fs/ext4.c:626` `int ext4_vfs_read(void *handle, void *buf, unsigned long pos,
                  unsigned long len)`
- `ext4_vfs_write` (function) `fs/ext4.c:666` `int ext4_vfs_write(void *handle, const void *buf, unsigned long pos,
                   unsigned ...`
- `ext4_vfs_close` (function) `fs/ext4.c:675` `int ext4_vfs_close(void *handle)`
- `ext4_vfs_fstat` (function) `fs/ext4.c:680` `int ext4_vfs_fstat(void *handle, unsigned long *size_out)`
- `ext4_vfs_truncate` (function) `fs/ext4.c:687` `int ext4_vfs_truncate(void *handle, unsigned long size)`
- `ext4_vfs_readdir` (function) `fs/ext4.c:696` `static int ext4_vfs_readdir(const char *path, vfs_dirent_t *ents,
        int cap)` -- Docstring: List one ext4 directory through the VFS verb.
- `ext_mbr_entry` (function) `fs/ext4.c:745` `static int ext_mbr_entry(const unsigned char *mbr, int idx,
                         unsigned lon...` -- First Linux-native partition: MBR 0x83 first (proven by a superblock read), then a magic scan for superfloppy...
- `ext_scan_dev` (function) `fs/ext4.c:770` `static int ext_scan_dev(unsigned long total_sec,
                        unsigned long *base_out)`
- `ext_dev_base` (function) `fs/ext4.c:791` `long ext_dev_base(void)`

## fs/fat32.c
Depends on: `headers/block.h`, `headers/fat32.h`, `headers/fsimg.h`, `headers/minifs.h`
Imported by: `tests/test_fat32.c`
- `fat_ld16` (function) `fs/fat32.c:18` `static unsigned fat_ld16(const unsigned char *p)`
- `fat_ld32` (function) `fs/fat32.c:22` `static unsigned fat_ld32(const unsigned char *p)`
- `fat_img_open` (function) `fs/fat32.c:29` `static int fat_img_open(const char *resolved, fsimg_t *img)` -- Open by resolved path: files first (a real file named hd0 keeps * working), the hd0 disk device only as a fallback.
- `fat_parse_bpb` (function) `fs/fat32.c:62` `static int fat_parse_bpb(const fsimg_t *img, fat_geo_t *g)`
- `fat_mbr_is_fat` (function) `fs/fat32.c:120` `static int fat_mbr_is_fat(unsigned char t)`
- `fat_dev_base` (function) `fs/fat32.c:192` `long fat_dev_base(void)`
- `fat_clus_ok` (function) `fs/fat32.c:224` `static int fat_clus_ok(const fat_geo_t *g, unsigned c)`
- `fat_entry` (function) `fs/fat32.c:231` `static int fat_entry(const fsimg_t *img, const fat_geo_t *g,
                     unsigned clus, ...` -- One FAT32 entry (low 28 bits).
- `fat_eoc` (function) `fs/fat32.c:248` `static int fat_eoc(unsigned v)`
- `fat_badch` (function) `fs/fat32.c:262` `static int fat_badch(char c)` -- FAT 8.3 forbids these in a query word (plus '/' and extra dots, handled by the splitter).
- `fat_qword` (function) `fs/fat32.c:274` `static int fat_qword(const char *q, unsigned qlen, char name8[8],
                     char ext3[3])` -- Uppercase one 8.3 query word ("name.ext", "name", never ".ext") into * padded 8+3 for raw comparison.
- `fat_match` (function) `fs/fat32.c:305` `static int fat_match(const unsigned char *de, const char name8[8],
                     const cha...` -- Match one 32-byte directory entry against padded 8+3.
- `fat_resolve` (function) `fs/fat32.c:321` `static int fat_resolve(const fsimg_t *img, const fat_geo_t *g,
                       const char ...` -- Resolve a FAT path to its first cluster, size and subdir bit.
- `fat32_list` (function) `fs/fat32.c:421` `int fat32_list(const char *imgpath, const char *dirpath,
               char names[][FAT32_NAME_M...`
- `fat32_vfs_open` (function) `fs/fat32.c:496` `int fat32_vfs_open(const char *path, int mode, void **handle)`
- `fat_views` (function) `fs/fat32.c:537` `static void fat_views(const fat32_handle_t *h, fsimg_t *img,
                      fat_geo_t *g)` -- h->sec_per_clus = g.sec_per_clus; h->rsvd_sec = g.rsvd_sec; h->num_fats = g.num_fats; h->fatsz_sec = g.fatsz_sec...
- `fat_seek` (function) `fs/fat32.c:556` `static int fat_seek(const fat32_handle_t *h, unsigned long pos,
                    unsigned *clu...` -- Advance from the file's first cluster to the one holding `pos`, * step-bounded by the cluster count so a cyclic FAT...
- `fat32_vfs_read` (function) `fs/fat32.c:581` `int fat32_vfs_read(void *handle, void *buf, unsigned long pos,
                   unsigned long len)`
- `fat32_vfs_write` (function) `fs/fat32.c:621` `int fat32_vfs_write(void *handle, const void *buf, unsigned long pos,
                    unsigne...`
- `fat32_vfs_close` (function) `fs/fat32.c:630` `int fat32_vfs_close(void *handle)`
- `fat32_vfs_fstat` (function) `fs/fat32.c:635` `int fat32_vfs_fstat(void *handle, unsigned long *size_out)`
- `fat32_vfs_truncate` (function) `fs/fat32.c:642` `int fat32_vfs_truncate(void *handle, unsigned long size)`

## fs/fsimg.c
Depends on: `headers/block.h`, `headers/fsimg.h`, `headers/minifs.h`
Imported by: `tests/test_ext4.c`, `tests/test_fat32.c`
- `fsimg_open_file` (function) `fs/fsimg.c:15` `int fsimg_open_file(const char *resolved, fsimg_t *img)`
- `fsimg_open_dev` (function) `fs/fsimg.c:51` `int fsimg_open_dev(unsigned long base_lba, unsigned long nsec,
                   fsimg_t *img)`
- `fsimg_dev_read` (function) `fs/fsimg.c:72` `static int fsimg_dev_read(const fsimg_t *img, unsigned long off,
                          void *...` -- Docstring: Sector reads off the active backend through the block layer, so a device image on USB reads from USB.
- `fsimg_read` (function) `fs/fsimg.c:96` `int fsimg_read(const fsimg_t *img, unsigned long off, void *buf,
               unsigned long len)`
- `fsimg_split` (function) `fs/fsimg.c:112` `int fsimg_split(const char *path, char *left, unsigned llen,
                char *right, unsigne...`

## fs/kfile.c
Depends on: `headers/minifs.h`
- `kfile_stdin` (function) `fs/kfile.c:15` `KFILE *kfile_stdin(void)`
- `kfile_stdout` (function) `fs/kfile.c:16` `KFILE *kfile_stdout(void)`
- `kfile_stderr` (function) `fs/kfile.c:17` `KFILE *kfile_stderr(void)`
- `recovery` (function) `fs/kfile.c:28` `* halts the machine with no recovery (the DOOM ABI-drift black screen),
 * so every public KFILE ...`
- `kfile_corrupt` (function) `fs/kfile.c:33` `static int kfile_corrupt(const KFILE *f)`
- `fs_take` (function) `fs/kfile.c:66` `static inline void fs_take(irqflags_t *flags)`
- `fs_drop` (function) `fs/kfile.c:70` `static inline void fs_drop(irqflags_t flags)`
- `kpipe_pair` (function) `fs/kfile.c:78` `int kpipe_pair(KFILE **rend_out, KFILE **wend_out)` -- Docstring: Create a connected pipe pair sharing one ring.
- `kpipe_state` (function) `fs/kfile.c:130` `int kpipe_state(KFILE *f, unsigned *avail, unsigned *space, int *wopen, int *ropen)` -- open (retry later, EAGAIN-style), false on EOF, on the write end, or on any non-pipe file.
- `kevent_create` (function) `fs/kfile.c:148` `KFILE *kevent_create(unsigned long long initval, int semaphore)` -- Docstring: New eventfd description with counter initval.
- `kevent_read` (function) `fs/kfile.c:163` `long kevent_read(KFILE *f, unsigned long long *out)` -- KFILE *f; if (initval > KEVENT_MAX) return 0; f = kmalloc(sizeof(KFILE)); if (!f) return 0; kmemset(f, 0...
- `kevent_readable` (function) `fs/kfile.c:199` `int kevent_readable(KFILE *f)` -- irqflags_t flags; long rc = -11; if (!f || !f->is_eventfd) return -22; if (v == ~0ULL) return -22; fs_take(&flags)...
- `kevent_writable` (function) `fs/kfile.c:204` `int kevent_writable(KFILE *f)` -- if (v <= KEVENT_MAX - f->efd_count) { f->efd_count += v; rc = 0; } fs_drop(flags); return rc; } /** Docstring: 1...
- `kpipe_is_write_end` (function) `fs/kfile.c:209` `int kpipe_is_write_end(KFILE *f)` -- return rc; } /** Docstring: 1 when a read would not block. int kevent_readable(KFILE *f) { return f && f->is_eventfd...
- `kpipe_grow` (function) `fs/kfile.c:216` `static int kpipe_grow(pipe_ring_t *ring)` -- Docstring: Grow a pipe ring buffer, linearizing wrapped bytes first.
- `kfopen` (function) `fs/kfile.c:239` `KFILE *kfopen(const char *path, const char *mode)`
- `fs_rename_on_minifs` (function) `fs/kfile.c:336` `static int fs_rename_on_minifs(const char *dst)` -- True when `dst` can live on MiniFS: no directory part (root), or its * parent resolves there.
- `entry` (function) `fs/kfile.c:355` `* directory with a volatile ramdisk entry (the kfopen misroute class) or
 * need a copy+delete th...`
- `kfclose` (function) `fs/kfile.c:397` `int kfclose(KFILE *f)`
- `kfgetc` (function) `fs/kfile.c:442` `int kfgetc(KFILE *f)`
- `kfgets` (function) `fs/kfile.c:483` `char *kfgets(char *buf, int size, KFILE *f)`
- `kfungetc` (function) `fs/kfile.c:497` `int kfungetc(int c, KFILE *f)`
- `kfread` (function) `fs/kfile.c:504` `unsigned long kfread(void *ptr, unsigned long size, unsigned long n, KFILE *f)`
- `kfwrite` (function) `fs/kfile.c:550` `unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long n, KFILE *f)`
- `kfseek` (function) `fs/kfile.c:616` `int kfseek(KFILE *f, long offset, int whence)`
- `kftell` (function) `fs/kfile.c:637` `long kftell(KFILE *f)`
- `kfflush` (function) `fs/kfile.c:641` `int kfflush(KFILE *f)`
- `kfputs` (function) `fs/kfile.c:667` `int kfputs(const char *s, KFILE *f)`
- `kfputc` (function) `fs/kfile.c:673` `int kfputc(int c, KFILE *f)`
- `krewind` (function) `fs/kfile.c:678` `void krewind(KFILE *f)`

## fs/minifs.c
Depends on: `headers/block.h`, `headers/ide.h`, `headers/lz4_kernel.h`, `headers/minifs.h`, `headers/pcache.h`
- `minifs_journal_touch` (function) `fs/minifs.c:16` `void minifs_journal_touch(unsigned int phys);`
- `blk_new` (function) `fs/minifs.c:22` `static unsigned char *blk_new(void);`
- `minifs_compress` (function) `fs/minifs.c:35` `unsigned int minifs_compress(const void *src, unsigned int src_len,
                             ...` -- unsigned int *phys_block); static unsigned char *blk_new(void); static void blk_free(unsigned char *b); static...
- `minifs_decompress` (function) `fs/minifs.c:46` `unsigned int minifs_decompress(const void *src, unsigned int src_len,
                           ...`
- `minifs_crc16` (function) `fs/minifs.c:57` `static unsigned short minifs_crc16(const void *data, unsigned int len)`
- `minifs_crc32` (function) `fs/minifs.c:69` `static unsigned int minifs_crc32(const void *data, unsigned int len)`
- `roundup4` (function) `fs/minifs.c:81` `static unsigned int roundup4(unsigned int v)`
- `div_round_up` (function) `fs/minifs.c:83` `static unsigned int div_round_up(unsigned int n, unsigned int d)`
- `returns` (function) `fs/minifs.c:92` `* overflowed the slot and smashed returns (measured ring-0 #UD on
 * lua->lua->cp). Every scratch...`
- `blk_free` (function) `fs/minifs.c:100` `static void blk_free(unsigned char *b)`
- `fs_write_super` (function) `fs/minifs.c:107` `static int fs_write_super(void)`
- `instead` (function) `fs/minifs.c:127` `* kernel stored the same crc at offset 76 instead (byte order the old
 * write path used), so a r...`
- `fs_inode_check` (function) `fs/minifs.c:142` `static int fs_inode_check(const MiniFSInode *in)`
- `fs_read_inode` (function) `fs/minifs.c:167` `static int fs_read_inode(unsigned int num, MiniFSInode *out)`
- `fs_write_inode` (function) `fs/minifs.c:179` `static int fs_write_inode(unsigned int num, const MiniFSInode *in)`
- `bm_test` (function) `fs/minifs.c:201` `static int bm_test(unsigned char *bm, unsigned int bit)`
- `bm_set` (function) `fs/minifs.c:205` `static void bm_set(unsigned char *bm, unsigned int bit)`
- `bm_clear` (function) `fs/minifs.c:209` `static void bm_clear(unsigned char *bm, unsigned int bit)`
- `minifs_alloc_block` (function) `fs/minifs.c:215` `int minifs_alloc_block(void)`
- `minifs_free_block` (function) `fs/minifs.c:232` `void minifs_free_block(unsigned int block)`
- `minifs_alloc_inode` (function) `fs/minifs.c:240` `int minifs_alloc_inode(void)`
- `minifs_free_inode` (function) `fs/minifs.c:252` `void minifs_free_inode(int num)`
- `minifs_inode_get_block` (function) `fs/minifs.c:260` `int minifs_inode_get_block(MiniFSInode *inode, unsigned int logblk,
                           un...`
- `fs_inode_set_block` (function) `fs/minifs.c:289` `static int fs_inode_set_block(MiniFSInode *inode, unsigned int logblk,
                          ...`
- `minifs_inode_alloc_block` (function) `fs/minifs.c:343` `int minifs_inode_alloc_block(MiniFSInode *inode, unsigned int logblk)`
- `fs_inode_free_all_blocks` (function) `fs/minifs.c:364` `static void fs_inode_free_all_blocks(MiniFSInode *inode)`
- `journal_load_super` (function) `fs/minifs.c:446` `static void journal_load_super(void)`
- `journal_save_super` (function) `fs/minifs.c:464` `static void journal_save_super(unsigned int state)`
- `journal_save_entries` (function) `fs/minifs.c:478` `static void journal_save_entries(void)`
- `minifs_journal_begin` (function) `fs/minifs.c:495` `void minifs_journal_begin(unsigned int txn_id)`
- `minifs_journal_add_block` (function) `fs/minifs.c:504` `void minifs_journal_add_block(unsigned int block)` -- Deprecated alias: historically took an inode number (wrong layer). * Takes a physical block now; prefer...
- `minifs_journal_commit` (function) `fs/minifs.c:511` `int minifs_journal_commit(unsigned int txn_id)` -- Pre-write barrier: persist the entry array and mark the journal DIRTY before any protected data block is modified.
- `minifs_journal_clear` (function) `fs/minifs.c:521` `void minifs_journal_clear(void)` -- Post-write barrier: the protected writes are all on disk, so the undo * log is no longer needed.
- `minifs_journal_abort` (function) `fs/minifs.c:531` `void minifs_journal_abort(void)` -- Error path after the DIRTY barrier: restore every snapshotted block from the journal data area, then clear.
- `blocks` (function) `fs/minifs.c:555` `* blocks (self-protection);`
- `first` (function) `fs/minifs.c:556` `* keep the first (oldest) snapshot. */
void minifs_journal_touch(unsigned int phys)`
- `minifs_journal_recover` (function) `fs/minifs.c:597` `void minifs_journal_recover(void)` -- Mount-time recovery: replays the undo log left by a crash between the DIRTY barrier and the CLEAN mark.
- `fs_namecmp` (function) `fs/minifs.c:683` `static int fs_namecmp(const char *a, unsigned char alen, const char *b)`
- `minifs_dir_lookup` (function) `fs/minifs.c:692` `int minifs_dir_lookup(int dir_ino, const char *name)`
- `minifs_dir_add_entry` (function) `fs/minifs.c:722` `int minifs_dir_add_entry(int dir_ino, const char *name, int child_ino,
                          ...`
- `minifs_dir_remove_entry` (function) `fs/minifs.c:860` `int minifs_dir_remove_entry(int dir_ino, const char *name)`
- `minifs_dir_read` (function) `fs/minifs.c:891` `int minifs_dir_read(int dir_ino, int index, MiniFSDirEntry *out, char *name_out)`
- `minifs_resolve_path` (function) `fs/minifs.c:941` `int minifs_resolve_path(const char *path)`
- `minifs_create` (function) `fs/minifs.c:974` `int minifs_create(const char *path, unsigned short mode)`
- `minifs_mkdir` (function) `fs/minifs.c:1027` `int minifs_mkdir(const char *path, unsigned short mode)`
- `minifs_unlink` (function) `fs/minifs.c:1076` `int minifs_unlink(const char *path)`
- `minifs_split_parent` (function) `fs/minifs.c:1119` `static int minifs_split_parent(const char *path, char *parent_out,
                              ...` -- Split a resolved path into its parent directory path ("" for root) and its leaf name.
- `minifs_rename` (function) `fs/minifs.c:1144` `int minifs_rename(const char *oldpath, const char *newpath)`
- `minifs_rmdir` (function) `fs/minifs.c:1176` `int minifs_rmdir(const char *path)`
- `minifs_read` (function) `fs/minifs.c:1216` `int minifs_read(int inode_num, void *buf, unsigned int offset, unsigned int len)`
- `minifs_write` (function) `fs/minifs.c:1287` `int minifs_write(int inode_num, const void *buf, unsigned int offset,
                 unsigned i...`
- `minifs_truncate` (function) `fs/minifs.c:1374` `int minifs_truncate(int inode_num, unsigned int new_size)`
- `minifs_stat` (function) `fs/minifs.c:1391` `int minifs_stat(int inode_num, MiniFSInode *out)`
- `minifs_access` (function) `fs/minifs.c:1395` `int minifs_access(const char *path)`
- `minifs_init` (function) `fs/minifs.c:1401` `void minifs_init(void)`
- `minifs_get_lba_start` (function) `fs/minifs.c:1409` `unsigned int minifs_get_lba_start(void)`
- `minifs_is_mounted` (function) `fs/minifs.c:1410` `int minifs_is_mounted(void)`
- `minifs_mount` (function) `fs/minifs.c:1418` `int minifs_mount(void)` -- Boot-time exemption from the -Wframe-larger-than=2048 gate: mount and mkfs run once on deep boot stacks, never on 16...
- `minifs_sync` (function) `fs/minifs.c:1568` `int minifs_sync(void)`
- `minifs_file_open` (function) `fs/minifs.c:1583` `MiniFSFile *minifs_file_open(int inode_num, int flags)`
- `minifs_file_close` (function) `fs/minifs.c:1597` `int minifs_file_close(MiniFSFile *f)`
- `minifs_get_total_blocks` (function) `fs/minifs.c:1604` `unsigned int minifs_get_total_blocks(void)`
- `minifs_usage` (function) `fs/minifs.c:1609` `void minifs_usage(unsigned int *free_b, unsigned int *total_b,
                  unsigned int *fr...` -- } int minifs_file_close(MiniFSFile *f) { if (!f) return 0; if (f->inode_cache) kfree(f->inode_cache); kfree(f)...

## fs/pcache.c
Depends on: `headers/pcache.h`
Imported by: `tests/test_pcache.c`
- `pcache_init` (function) `fs/pcache.c:42` `void pcache_init(void)`
- `pcache_lookup` (function) `fs/pcache.c:54` `int pcache_lookup(int ino, unsigned index)`
- `pcache_get` (function) `fs/pcache.c:71` `int pcache_get(int ino, unsigned index, int *is_new)`
- `pcache_publish` (function) `fs/pcache.c:128` `int pcache_publish(int ino, unsigned index, const unsigned char *data)` -- Docstring: Publish a privately filled page into the cache atomically.
- `pcache_put` (function) `fs/pcache.c:179` `void pcache_put(int slot)`
- `pcache_ref` (function) `fs/pcache.c:192` `int pcache_ref(int ino, unsigned index)` -- Docstring: Take one more ref on a cached page without allocating.
- `pcache_unmap` (function) `fs/pcache.c:216` `void pcache_unmap(int ino, unsigned index)` -- Docstring: Drop the ref a mapping holds on one cached page.
- `pcache_slot_phys` (function) `fs/pcache.c:222` `static unsigned long pcache_slot_phys(int slot)` -- Docstring: Drop the ref a mapping holds on one cached page.
- `match` (function) `fs/pcache.c:230` `* a phys match (owned, ref dropped unless already zero), 0
 * otherwise. */
int pcache_put_if(int...`
- `pcache_ref_if` (function) `fs/pcache.c:255` `int pcache_ref_if(int ino, unsigned index, unsigned long phys)` -- Docstring: Take one more ref only when the cached page is the exact phys the caller shares.
- `pcache_owns_phys` (function) `fs/pcache.c:277` `int pcache_owns_phys(unsigned long phys)` -- Docstring: True when phys is a cache pool page.
- `pcache_data` (function) `fs/pcache.c:285` `unsigned char *pcache_data(int slot)`
- `pcache_mark_dirty` (function) `fs/pcache.c:291` `void pcache_mark_dirty(int slot)`
- `pcache_invalidate_ino` (function) `fs/pcache.c:299` `void pcache_invalidate_ino(int ino)`
- `pcache_stats` (function) `fs/pcache.c:314` `void pcache_stats(unsigned long *pages_out, unsigned long *hits_out,
        unsigned long *miss_...`

## fs/ramdisk.c
- `ramdisk_reserve` (function) `fs/ramdisk.c:37` `static int ramdisk_reserve(unsigned long want)`
- `ramdisk_setup_from` (function) `fs/ramdisk.c:55` `void ramdisk_setup_from(void *data, unsigned size)`
- `ramdisk_init` (function) `fs/ramdisk.c:128` `void ramdisk_init(void)`
- `ramdisk_open` (function) `fs/ramdisk.c:145` `RDFile *ramdisk_open(const char *name)`
- `ramdisk_read` (function) `fs/ramdisk.c:155` `int ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len)`
- `ramdisk_write` (function) `fs/ramdisk.c:163` `int ramdisk_write(RDFile *f, const void *buf, unsigned offset, unsigned len)`
- `ramdisk_create` (function) `fs/ramdisk.c:171` `RDFile *ramdisk_create(const char *name, unsigned size)`
- `ramdisk_resize` (function) `fs/ramdisk.c:185` `int ramdisk_resize(RDFile *f, unsigned newsize)`
- `ramdisk_list` (function) `fs/ramdisk.c:222` `int ramdisk_list(RDFile **out, int max)`
- `ramdisk_count` (function) `fs/ramdisk.c:230` `int ramdisk_count(void)`
- `ramdisk_usage` (function) `fs/ramdisk.c:236` `void ramdisk_usage(unsigned *used, unsigned *cap, unsigned *max)` -- int ramdisk_list(RDFile **out, int max) { if (!rd) return 0; int n = (int)rd->count < max ?
- `ramdisk_file_name` (function) `fs/ramdisk.c:242` `const char *ramdisk_file_name(int idx)`
- `ramdisk_delete` (function) `fs/ramdisk.c:247` `int ramdisk_delete(RDFile *f)`
- `ramdisk_rename` (function) `fs/ramdisk.c:269` `int ramdisk_rename(const char *oldname, const char *newname)`

## fs/vfs.c
Depends on: `headers/ext4.h`, `headers/fat32.h`, `headers/minifs.h`
- `vfs_init` (function) `fs/vfs.c:22` `void vfs_init(void)`
- `vfs_register` (function) `fs/vfs.c:27` `int vfs_register(const char *prefix, const vfs_ops_t *ops, const char *driver)`
- `vfs_unregister` (function) `fs/vfs.c:62` `int vfs_unregister(const char *prefix)`
- `vfs_open` (function) `fs/vfs.c:106` `int vfs_open(const char *path, int mode, vfs_file_t *f)`
- `taken` (function) `fs/vfs.c:160` `* refcount is taken (ops tables are static, never freed), so a
 * listing can never pin an unmoun...`
- `ramdisk_vfs_open` (function) `fs/vfs.c:212` `static int ramdisk_vfs_open(const char *path, int mode, void **handle)`
- `ramdisk_vfs_read` (function) `fs/vfs.c:238` `static int ramdisk_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len)`
- `ramdisk_vfs_write` (function) `fs/vfs.c:247` `static int ramdisk_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len)`
- `ramdisk_vfs_close` (function) `fs/vfs.c:255` `static int ramdisk_vfs_close(void *handle)`
- `ramdisk_vfs_fstat` (function) `fs/vfs.c:261` `static int ramdisk_vfs_fstat(void *handle, unsigned long *size_out)`
- `ramdisk_vfs_truncate` (function) `fs/vfs.c:268` `static int ramdisk_vfs_truncate(void *handle, unsigned long size)`
- `ramdisk_vfs_readdir` (function) `fs/vfs.c:278` `static int ramdisk_vfs_readdir(const char *path, vfs_dirent_t *ents,
        int cap)` -- Docstring: List ramdisk leaves under dir ("" or "/" is root).
- `minifs_vfs_open` (function) `fs/vfs.c:351` `static int minifs_vfs_open(const char *path, int mode, void **handle)`
- `minifs_vfs_read` (function) `fs/vfs.c:379` `static int minifs_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len)`
- `minifs_vfs_write` (function) `fs/vfs.c:388` `static int minifs_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len)`
- `minifs_vfs_close` (function) `fs/vfs.c:396` `static int minifs_vfs_close(void *handle)`
- `minifs_vfs_fstat` (function) `fs/vfs.c:402` `static int minifs_vfs_fstat(void *handle, unsigned long *size_out)`
- `minifs_vfs_truncate` (function) `fs/vfs.c:409` `static int minifs_vfs_truncate(void *handle, unsigned long size)`
- `mem_lookup` (function) `fs/vfs.c:470` `static int mem_lookup(const char *path)`
- `mem_open` (function) `fs/vfs.c:478` `static int mem_open(const char *path, int mode, void **handle)`
- `mem_slot` (function) `fs/vfs.c:498` `static int mem_slot(void *handle)`
- `mem_read` (function) `fs/vfs.c:505` `static int mem_read(void *handle, void *buf, unsigned long pos, unsigned long len)`
- `mem_write` (function) `fs/vfs.c:515` `static int mem_write(void *handle, const void *buf, unsigned long pos, unsigned long len)`
- `mem_close` (function) `fs/vfs.c:526` `static int mem_close(void *handle)`
- `mem_fstat` (function) `fs/vfs.c:530` `static int mem_fstat(void *handle, unsigned long *size_out)`
- `mem_truncate` (function) `fs/vfs.c:537` `static int mem_truncate(void *handle, unsigned long size)`
- `mem_readdir` (function) `fs/vfs.c:548` `static int mem_readdir(const char *path, vfs_dirent_t *ents, int cap)` -- Docstring: List the flat mem: namespace (root only, files only). * Anything below root refuses: there are no...
- `fs_resolve` (function) `fs/vfs.c:580` `int fs_resolve(const char *path, char *out, unsigned cap)`
- `fs_dir_exists` (function) `fs/vfs.c:613` `int fs_dir_exists(const char *dir)`
- `fs_is_dir` (function) `fs/vfs.c:638` `int fs_is_dir(const char *resolved)`
- `minifs_mkdir_p` (function) `fs/vfs.c:651` `int minifs_mkdir_p(const char *resolved)`
- `vfs_register_builtins` (function) `fs/vfs.c:674` `void vfs_register_builtins(void)`
- `open` (function) `fs/vfs.c:688` `* open (loopback image file plus in-image path), so one registration
 * serves every image. */
in...`
- `vfs_read` (function) `fs/vfs.c:709` `int vfs_read(vfs_file_t *f, void *buf, unsigned long len)`
- `vfs_write` (function) `fs/vfs.c:718` `int vfs_write(vfs_file_t *f, const void *buf, unsigned long len)`
- `vfs_close` (function) `fs/vfs.c:734` `int vfs_close(vfs_file_t *f)`
- `vfs_fstat` (function) `fs/vfs.c:752` `int vfs_fstat(vfs_file_t *f, unsigned long *size_out)`

## fs/zip.c
- `root` (function) `fs/zip.c:8` `* names are hostile data: each is normalized to forward slashes and rejected * when it escapes the extraction root...`
- `mz_zip_writer_mem_ptr` (function) `fs/zip.c:18` `void *mz_zip_writer_mem_ptr(mz_zip_archive *pZip);`
- `mz_zip_writer_mem_size` (function) `fs/zip.c:19` `size_t mz_zip_writer_mem_size(mz_zip_archive *pZip);`
- `zip_read_whole` (function) `fs/zip.c:25` `static unsigned char *zip_read_whole(const char *path, unsigned long *size)` -- Read a whole file (ramdisk first, MiniFS fallback) into a fresh kernel buffer, growing until the read stops making...
- `marker` (function) `fs/zip.c:50` `* marker (trailing '/') is preserved by the caller, not here. */
static int zip_sanitize_name(con...`
- `zip_build_path` (function) `fs/zip.c:79` `static int zip_build_path(const char *destdir, const char *name, char *out)` -- Build the combined extraction path: destdir (already resolved, may be "") joined with the sanitized entry name.
- `zip_ensure_dir_tree` (function) `fs/zip.c:95` `static int zip_ensure_dir_tree(const char *dir)` -- Create every directory component of `dir` (a resolved, slash-separated name with no trailing '/'), including `dir`...
- `zip_do_entry` (function) `fs/zip.c:117` `static int zip_do_entry(mz_zip_archive *zip, mz_uint idx, const char *destdir)` -- Extract one archive entry under destdir.
- `shell_cmd_unzip` (function) `fs/zip.c:176` `void shell_cmd_unzip(int argc, char **argv)` -- if (!data) return 0; if (n != usize) { mz_free(data); return 0; } f = kfopen(resolved, "w"); if (!f) {...
- `shell_cmd_zip` (function) `fs/zip.c:254` `void shell_cmd_zip(int argc, char **argv)` -- zip <out.zip> <file...> — store each file (under its sanitized name) into * a new archive.

## headers/abi.h
Imported by: `kernel.c`, `kernel/abi.c`, `tests/test_abi.c`
- `abi_verify` (function) `headers/abi.h:25` `int abi_verify(const char *text, long version, unsigned long checksum);`
- `abi_check_manifest` (function) `headers/abi.h:28` `int abi_check_manifest(void);` -- ifndef ABI_HOST_TEST

## headers/arch/x86/boot/bootdefs.h
Imported by: `arch/x86/ap_entry.S`, `arch/x86/boot/stage1.S`, `arch/x86/boot/stage2.S`, `drivers/pcm2.c`, `kernel.c`, `kernel/exec.c`, `kernel/mm.c`, `kernel/mm/cow.c`, `kernel/mm/paging.c`, `kernel/sched.c`, `kernel/syscalls.c`, `kernel/vga_fb.c`, `smp.c`
- `address` (function) `headers/arch/x86/boot/bootdefs.h:191` `* address (below 1 MB so a real-mode SIPI can reach it) and executed by every * AP. It reuses the page tables and...`

## headers/arch/x86/hal_io.h
Imported by: `drivers/kbd.c`, `drivers/mouse.c`, `drivers/nvme.c`, `drivers/usbhid.c`, `drivers/xhci.c`, `kernel/sched.c`, `kernel/syscalls.c`, `tests/test_hal_io.c`
- `hal_mmio_write32` (function) `headers/arch/x86/hal_io.h:123` `static inline void hal_mmio_write32(volatile unsigned *addr, unsigned val)` -- A device region must be mapped uncached (see kmm_map_uncached): a write-back mapping lets a register read be...
- `hal_mmio_read64` (function) `headers/arch/x86/hal_io.h:128` `static inline unsigned long long hal_mmio_read64(const volatile unsigned long long *addr)` -- bit is released for reuse.  /** Docstring: Read a 32-bit device register. static inline unsigned...
- `hal_mmio_write64` (function) `headers/arch/x86/hal_io.h:133` `static inline void hal_mmio_write64(volatile unsigned long long *addr,
                          ...` -- return *addr; } /** Docstring: Write a 32-bit device register. static inline void hal_mmio_write32(volatile unsigned...
- `hal_mmio_read16` (function) `headers/arch/x86/hal_io.h:139` `static inline unsigned short hal_mmio_read16(const volatile unsigned short *addr)` -- } /** Docstring: Read a 64-bit device register. static inline unsigned long long hal_mmio_read64(const volatile...
- `hal_mmio_write16` (function) `headers/arch/x86/hal_io.h:144` `static inline void hal_mmio_write16(volatile unsigned short *addr,
                              ...` -- } /** Docstring: Write a 64-bit device register. static inline void hal_mmio_write64(volatile unsigned long long...
- `hal_mmio_read8` (function) `headers/arch/x86/hal_io.h:150` `static inline unsigned char hal_mmio_read8(const volatile unsigned char *addr)` -- } /** Docstring: Read a 16-bit device register. static inline unsigned short hal_mmio_read16(const volatile unsigned...
- `hal_mmio_write8` (function) `headers/arch/x86/hal_io.h:155` `static inline void hal_mmio_write8(volatile unsigned char *addr,
                                ...` -- } /** Docstring: Write a 16-bit device register. static inline void hal_mmio_write16(volatile unsigned short *addr...
- `hal_mmio_wmb` (function) `headers/arch/x86/hal_io.h:161` `static inline void hal_mmio_wmb(void)` -- } /** Docstring: Read an 8-bit device register. static inline unsigned char hal_mmio_read8(const volatile unsigned...
- `hal_mmio_rmb` (function) `headers/arch/x86/hal_io.h:166` `static inline void hal_mmio_rmb(void)` -- } /** Docstring: Write an 8-bit device register. static inline void hal_mmio_write8(volatile unsigned char *addr...
- `hal_mmio_mb` (function) `headers/arch/x86/hal_io.h:171` `static inline void hal_mmio_mb(void)` -- addr = val; } /** Docstring: Write memory barrier, orders prior stores before later stores. static inline void...
- `hal_outb` (function) `headers/arch/x86/hal_io.h:189` `static inline void hal_outb(unsigned short port, unsigned char val)` -- #ifdef HAL_IO_HOST_TEST /** Docstring: Stub log for host tests, counts port writes. extern unsigned...
- `hal_inb` (function) `headers/arch/x86/hal_io.h:196` `static inline unsigned char hal_inb(unsigned short port)` -- extern unsigned hal_io_stub_last_val; /** Docstring: Stub log for host tests, counts LAPIC EOI calls. extern...
- `hal_outw` (function) `headers/arch/x86/hal_io.h:202` `static inline void hal_outw(unsigned short port, unsigned short val)` -- /** Docstring: Stub port byte write, records port and value. static inline void hal_outb(unsigned short port...
- `hal_inw` (function) `headers/arch/x86/hal_io.h:209` `static inline unsigned short hal_inw(unsigned short port)` -- /** Docstring: Stub port byte read, returns the canned value. static inline unsigned char hal_inb(unsigned short...
- `hal_lapic_eoi` (function) `headers/arch/x86/hal_io.h:215` `static inline void hal_lapic_eoi(void)` -- /** Docstring: Stub port word write, records port and low byte. static inline void hal_outw(unsigned short port...
- `hal_pic_eoi` (function) `headers/arch/x86/hal_io.h:220` `static inline void hal_pic_eoi(int irq)` -- } /** Docstring: Stub port word read, returns the canned value. static inline unsigned short hal_inw(unsigned short...
- `hal_outb` (function) `headers/arch/x86/hal_io.h:230` `static inline void hal_outb(unsigned short port, unsigned char val)` -- hal_io_stub_lapic_eois++; } /** Docstring: Stub PIC EOI for an IRQ line. static inline void hal_pic_eoi(int irq) {...
- `hal_inb` (function) `headers/arch/x86/hal_io.h:235` `static inline unsigned char hal_inb(unsigned short port)` -- if (irq >= 8) { hal_outb(HAL_PIC2_CMD, HAL_PIC_EOI); } hal_outb(HAL_PIC1_CMD, HAL_PIC_EOI); } #else /** Docstring...
- `hal_outw` (function) `headers/arch/x86/hal_io.h:242` `static inline void hal_outw(unsigned short port, unsigned short val)` -- /** Docstring: Emit a port byte write. static inline void hal_outb(unsigned short port, unsigned char val) { __asm__...
- `hal_inw` (function) `headers/arch/x86/hal_io.h:247` `static inline unsigned short hal_inw(unsigned short port)` -- /** Docstring: Emit a port byte read. static inline unsigned char hal_inb(unsigned short port) { unsigned char r...
- `hal_lapic_eoi` (function) `headers/arch/x86/hal_io.h:254` `static inline void hal_lapic_eoi(void)` -- /** Docstring: Emit a port word write. static inline void hal_outw(unsigned short port, unsigned short val) {...
- `hal_pic_eoi` (function) `headers/arch/x86/hal_io.h:259` `static inline void hal_pic_eoi(int irq)` -- /** Docstring: Emit a port word read. static inline unsigned short hal_inw(unsigned short port) { unsigned short r...

## headers/arch/x86/msr.h
Imported by: `kernel.c`, `kernel/exec.c`, `kernel/mm/paging.c`, `kernel/sched.c`, `kernel/spawn.c`, `kernel/syscalls.c`, `smp.c`
- `wrmsr` (function) `headers/arch/x86/msr.h:8` `static inline void wrmsr(unsigned msr, unsigned long val)`
- `rdmsr` (function) `headers/arch/x86/msr.h:13` `static inline unsigned long rdmsr(unsigned msr)`

## headers/arena.h
Imported by: `kernel/spawn.c`, `tests/test_arena.c`
- `kmalloc` (function) `headers/arena.h:3` `* * A bump arena serves one kmalloc (kernel) or malloc (ring-3) with pointer * bumps instead of N allocator round...`
- `kfree` (function) `headers/arena.h:25` `* kfree(back);`
- `arena_init` (function) `headers/arena.h:48` `static inline void arena_init(arena_t *a, void *block, size_t size)` -- #include <stddef.h> /** Docstring: default borrow alignment when the caller passes align 0. #define...
- `arena_align_up` (function) `headers/arena.h:62` `static inline size_t arena_align_up(size_t n, size_t align)` -- static inline void arena_init(arena_t *a, void *block, size_t size) { if (!a) return; if (!block || size == 0) {...
- `arena_bytes_for` (function) `headers/arena.h:74` `static inline size_t arena_bytes_for(size_t count, size_t elem_size)` -- /** Docstring: round n up to align, 0 on overflow or non-power-of-two align. static inline size_t...
- `arena_alloc` (function) `headers/arena.h:81` `static inline void *arena_alloc(arena_t *a, size_t size, size_t align)` -- mask = align - 1; if (n > (size_t)-1 - mask) return 0; up = (n + mask) & ~mask; return up; } /** Docstring: overflow...
- `arena_used` (function) `headers/arena.h:95` `static inline size_t arena_used(const arena_t *a)` -- static inline void *arena_alloc(arena_t *a, size_t size, size_t align) { size_t off; size_t up; if (!a || !a->base...
- `arena_free_bytes` (function) `headers/arena.h:101` `static inline size_t arena_free_bytes(const arena_t *a)` -- if (up == 0 && off != 0) return 0; if (up > (size_t)(a->end - a->base)) return 0; if (size > (size_t)(a->end...
- `arena_reset` (function) `headers/arena.h:107` `static inline void arena_reset(arena_t *a)` -- /** Docstring: bytes borrowed so far, 0 for a null or empty arena. static inline size_t arena_used(const arena_t *a)...
- `arena_checkpoint` (function) `headers/arena.h:113` `static inline size_t arena_checkpoint(const arena_t *a)` -- /** Docstring: bytes still borrowable, 0 for a null or empty arena. static inline size_t arena_free_bytes(const...
- `arena_rewind` (function) `headers/arena.h:119` `static inline int arena_rewind(arena_t *a, size_t checkpoint)` -- /** Docstring: rewind the scope to empty without releasing the backing block. static inline void arena_reset(arena_t...
- `arena_contains` (function) `headers/arena.h:128` `static inline int arena_contains(const arena_t *a, const void *ptr)` -- if (!a || !a->base) return 0; return (size_t)(a->cur - a->base); } /** Docstring: rewind to a checkpoint, -1 when...

## headers/audio.h
Imported by: `progs/pokemon/platform_minios.c`
- `audio_init` (function) `headers/audio.h:21` `int audio_init(void);` -- PC speaker (square wave, syscalls 209/210/214) - Sound Blaster 16 (8-bit mono PCM DMA, syscalls 221/222/224) - SB16...
- `audio_tone` (function) `headers/audio.h:24` `void audio_tone(unsigned freq);` -- Ring-3 programs use these wrappers instead of calling raw syscalls.
- `audio_pcm_open` (function) `headers/audio.h:27` `int audio_pcm_open(unsigned rate, unsigned channels, unsigned format);` -- #define AUDIO_RATE_DEFAULT  22050 #define AUDIO_CHANNELS_MONO 1 #define AUDIO_FORMAT_U8     0 #define...
- `audio_pcm_submit` (function) `headers/audio.h:28` `int audio_pcm_submit(const void *buf, unsigned len);`
- `audio_pcm_pump` (function) `headers/audio.h:29` `void audio_pcm_pump(void);`
- `audio_pcm_close` (function) `headers/audio.h:30` `void audio_pcm_close(void);`
- `audio_set_volume` (function) `headers/audio.h:33` `void audio_set_volume(unsigned volume);` -- /* Initialize the audio subsystem.
- `audio_get_volume` (function) `headers/audio.h:34` `unsigned audio_get_volume(void);`
- `audio_sb16_present` (function) `headers/audio.h:37` `int audio_sb16_present(void);` -- /* Tone mode: play a square wave at `freq` Hz.
- `audio_stream_open` (function) `headers/audio.h:40` `int audio_stream_open(void);` -- /* PCM streaming mode (SB16). int  audio_pcm_open(unsigned rate, unsigned channels, unsigned format); int...
- `audio_stream_close` (function) `headers/audio.h:41` `void audio_stream_close(int id);`
- `audio_stream_submit` (function) `headers/audio.h:42` `int audio_stream_submit(int id, const void *buf, unsigned len);`
- `audio_stream_volume` (function) `headers/audio.h:43` `void audio_stream_volume(int id, unsigned char vol);`

## headers/batch.h
Imported by: `kernel/batch.c`, `kernel/syscalls.c`, `tests/test_batch.c`
- `batch_exec` (function) `headers/batch.h:62` `long batch_exec(const batch_op_t *ops, long *results, int count, int *completed, batch_handler_t dispatch);`

## headers/block.h
Imported by: `drivers/block.c`, `fs/ext4.c`, `fs/fat32.c`, `fs/fsimg.c`, `fs/minifs.c`, `kernel.c`, `kernel/syscalls.c`
- `block_init` (function) `headers/block.h:12` `void block_init(void);` -- Block device abstraction for MiniFS. * Maps 4096-byte logical blocks to 512-byte IDE sectors. #define BLOCK_SIZE...
- `block_set_base` (function) `headers/block.h:15` `void block_set_base(unsigned int lba_base);` -- Block device abstraction for MiniFS. * Maps 4096-byte logical blocks to 512-byte IDE sectors. #define BLOCK_SIZE...
- `block_read` (function) `headers/block.h:18` `int block_read(unsigned int block_num, void *buf);` -- Block device abstraction for MiniFS. * Maps 4096-byte logical blocks to 512-byte IDE sectors. #define BLOCK_SIZE...
- `block_write` (function) `headers/block.h:19` `int block_write(unsigned int block_num, const void *buf);`
- `block_read_multi` (function) `headers/block.h:23` `int block_read_multi(unsigned int block_num, unsigned int count, void *buf);` -- Read/write multiple contiguous blocks. * Returns 0 on success.
- `block_write_multi` (function) `headers/block.h:24` `int block_write_multi(unsigned int block_num, unsigned int count, const void *buf);`
- `block_flush` (function) `headers/block.h:27` `void block_flush(void);` -- Read/write multiple contiguous blocks. * Returns 0 on success. int block_read_multi(unsigned int block_num, unsigned...
- `block_total` (function) `headers/block.h:30` `unsigned int block_total(void);` -- Read/write multiple contiguous blocks. * Returns 0 on success. int block_read_multi(unsigned int block_num, unsigned...
- `block_read_sectors` (function) `headers/block.h:37` `int block_read_sectors(unsigned lba, unsigned count, void *buf);` -- Docstring: Backend-aware sector I/O on absolute LBAs, bypassing the block cache and the MiniFS base offset.
- `block_disk_sectors` (function) `headers/block.h:40` `unsigned long block_disk_sectors(void);` -- Docstring: Backend-aware sector I/O on absolute LBAs, bypassing the block cache and the MiniFS base offset.

## headers/desktop_shortcuts.h
Imported by: `kernel/vga_fb.c`
- `desktop_shortcuts_load` (function) `headers/desktop_shortcuts.h:82` `void desktop_shortcuts_load(void);` -- Load shortcuts from etc/shortcuts, decode icons, compute layout. * Called once from vga_fb_draw_desktop on first draw.
- `desktop_shortcuts_draw` (function) `headers/desktop_shortcuts.h:85` `void desktop_shortcuts_draw(void);` -- Load shortcuts from etc/shortcuts, decode icons, compute layout. * Called once from vga_fb_draw_desktop on first...
- `desktop_shortcuts_hit_test` (function) `headers/desktop_shortcuts.h:89` `const char *desktop_shortcuts_hit_test(int mx, int my);` -- Handle a left-click at (mx, my).

## headers/driver.h
Imported by: `drivers/block.c`, `drivers/driver.c`, `drivers/ide.c`, `drivers/pcspk.c`, `drivers/sb16.c`, `drivers/usbblk.c`, `drivers/virtio_blk.c`, `kernel/syscalls.c`, `tests/test_driver.c`, `tests/test_usbblk.c`
- `device_register` (function) `headers/driver.h:56` `int device_register(device_t *dev);`
- `device_find` (function) `headers/driver.h:57` `device_t *device_find(const char *name);`
- `device_find_by_type` (function) `headers/driver.h:58` `device_t *device_find_by_type(int type);`
- `device_count` (function) `headers/driver.h:59` `int device_count(void);`
- `device_reset` (function) `headers/driver.h:60` `void device_reset(void);`


Next: [API_p3.md](API_p3.md)
