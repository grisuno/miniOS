# API

## arch/x86/ap_entry.S

### ap_stub_start
- Defined: `arch/x86/ap_entry.S:21`

### ap_pm
- Defined: `arch/x86/ap_entry.S:39`

### ap_lm
- Defined: `arch/x86/ap_entry.S:62`

### ap_patch_slot
- Defined: `arch/x86/ap_entry.S:80`

### ap_gdt32
- Defined: `arch/x86/ap_entry.S:84`

### ap_gdt32_ptr
- Defined: `arch/x86/ap_entry.S:88`
- Doc: movw %ax, %ss /* Load smp_ap_entry()'s address from the BSP-patched slot and go. mov ap_patch_slot(%rip), %rax jmp *%rax

### ap_gdt32_end
- Defined: `arch/x86/ap_entry.S:91`

### ap_gdt64_ptr
- Defined: `arch/x86/ap_entry.S:93`

### ap_stub_end
- Defined: `arch/x86/ap_entry.S:98`

## arch/x86/boot/stage1.S

### main
- Defined: `arch/x86/boot/stage1.S:28`

### normalize
- Defined: `arch/x86/boot/stage1.S:32`

### no_extensions
- Defined: `arch/x86/boot/stage1.S:78`

### read_failed
- Defined: `arch/x86/boot/stage1.S:82`

### fail
- Defined: `arch/x86/boot/stage1.S:85`

### halt
- Defined: `arch/x86/boot/stage1.S:88`

### puts
- Defined: `arch/x86/boot/stage1.S:93`

### puts_next
- Defined: `arch/x86/boot/stage1.S:97`

### puts_done
- Defined: `arch/x86/boot/stage1.S:103`

### msg_no_lba
- Defined: `arch/x86/boot/stage1.S:107`

### msg_read
- Defined: `arch/x86/boot/stage1.S:109`

## arch/x86/boot/stage2.S

### stage2_main
- Defined: `arch/x86/boot/stage2.S:39`

### a20_ready
- Defined: `arch/x86/boot/stage2.S:54`

### load_chunk
- Defined: `arch/x86/boot/stage2.S:69`

### chunk_size_ready
- Defined: `arch/x86/boot/stage2.S:74`

### read_piece
- Defined: `arch/x86/boot/stage2.S:81`

### piece_size_ready
- Defined: `arch/x86/boot/stage2.S:86`

### chunk_copy
- Defined: `arch/x86/boot/stage2.S:118`

### chunk_leave_pm
- Defined: `arch/x86/boot/stage2.S:131`

### chunk_resume
- Defined: `arch/x86/boot/stage2.S:141`

### enter_long_mode
- Defined: `arch/x86/boot/stage2.S:162`

### fill_pt0_low
- Defined: `arch/x86/boot/stage2.S:190`

### dma_uncache
- Defined: `arch/x86/boot/stage2.S:208`

### fill_pt0_kernel
- Defined: `arch/x86/boot/stage2.S:216`

### fill_pt1_kernel
- Defined: `arch/x86/boot/stage2.S:235`

### fill_pt1_bss
- Defined: `arch/x86/boot/stage2.S:244`

### fill_page_directory
- Defined: `arch/x86/boot/stage2.S:260`
- Doc: endif

### read_failed
- Defined: `arch/x86/boot/stage2.S:289`

### halt
- Defined: `arch/x86/boot/stage2.S:293`

### puts
- Defined: `arch/x86/boot/stage2.S:298`

### puts_next
- Defined: `arch/x86/boot/stage2.S:302`

### puts_done
- Defined: `arch/x86/boot/stage2.S:308`

### msg_read
- Defined: `arch/x86/boot/stage2.S:312`

### vbe_probe
- Defined: `arch/x86/boot/stage2.S:322`
- Doc: Probe VESA BIOS Extensions for a high-resolution 8-bit-palette linear framebuffer and record it for the kernel in the fi

### vbe_try_mode
- Defined: `arch/x86/boot/stage2.S:343`
- Doc: Try one VBE mode held in %bx. On success the mode is set with the linear framebuffer bit and carry is cleared; on any fa

### vbe_set_fail
- Defined: `arch/x86/boot/stage2.S:387`

### vbe_try_fail
- Defined: `arch/x86/boot/stage2.S:390`

### vbe_ok
- Defined: `arch/x86/boot/stage2.S:396`

### kaslr_pick
- Defined: `arch/x86/boot/stage2.S:405`
- Doc: Pick the kernel's physical load base: a 2 MB-aligned address in the 64-position window above the kernel heap, seeded fro

### gdt32_start
- Defined: `arch/x86/boot/stage2.S:442`

### gdt32_end
- Defined: `arch/x86/boot/stage2.S:448`

### gdt32_ptr
- Defined: `arch/x86/boot/stage2.S:449`

### gdt64_image
- Defined: `arch/x86/boot/stage2.S:454`

### gdt64_ptr
- Defined: `arch/x86/boot/stage2.S:460`

### saved_gdtr
- Defined: `arch/x86/boot/stage2.S:464`

### sectors_left
- Defined: `arch/x86/boot/stage2.S:467`

### chunk_sectors
- Defined: `arch/x86/boot/stage2.S:469`

### next_lba
- Defined: `arch/x86/boot/stage2.S:471`

### dest_addr
- Defined: `arch/x86/boot/stage2.S:473`

### kaslr_dest
- Defined: `arch/x86/boot/stage2.S:475`

## arch/x86/ctx_sw.S

### switch_to
- Defined: `arch/x86/ctx_sw.S:21`

### user_trampoline
- Defined: `arch/x86/ctx_sw.S:96`

## arch/x86/isr_stubs.S

### tf_rax
- Defined: `arch/x86/isr_stubs.S:67`

### tf_rbx
- Defined: `arch/x86/isr_stubs.S:68`

### tf_rcx
- Defined: `arch/x86/isr_stubs.S:69`

### tf_rdx
- Defined: `arch/x86/isr_stubs.S:70`

### tf_rsi
- Defined: `arch/x86/isr_stubs.S:71`

### tf_rdi
- Defined: `arch/x86/isr_stubs.S:72`

### tf_rbp
- Defined: `arch/x86/isr_stubs.S:73`

### tf_r8
- Defined: `arch/x86/isr_stubs.S:74`

### tf_r9
- Defined: `arch/x86/isr_stubs.S:75`

### tf_r10
- Defined: `arch/x86/isr_stubs.S:76`

### tf_r11
- Defined: `arch/x86/isr_stubs.S:77`

### tf_r12
- Defined: `arch/x86/isr_stubs.S:78`

### tf_r13
- Defined: `arch/x86/isr_stubs.S:79`

### tf_r14
- Defined: `arch/x86/isr_stubs.S:80`

### tf_r15
- Defined: `arch/x86/isr_stubs.S:81`

### tf_rip
- Defined: `arch/x86/isr_stubs.S:82`

### tf_cs
- Defined: `arch/x86/isr_stubs.S:83`

### tf_rflags
- Defined: `arch/x86/isr_stubs.S:84`

### tf_rsp
- Defined: `arch/x86/isr_stubs.S:85`

### tf_ss
- Defined: `arch/x86/isr_stubs.S:86`

### tf_vector
- Defined: `arch/x86/isr_stubs.S:87`

### tf_errcode
- Defined: `arch/x86/isr_stubs.S:88`

### isr_common
- Defined: `arch/x86/isr_stubs.S:96`

### isr_stub_table
- Defined: `arch/x86/isr_stubs.S:195`

## arch/x86/msr.h

### wrmsr `static inline void wrmsr(unsigned msr, unsigned long val)`
- Defined: `arch/x86/msr.h:7`
- Doc: Model-Specific Register access for x86-64. Shared by kernel.c (syscall_init, arch_prctl, k_exec_user), * paging.c (mm_se

### rdmsr `static inline unsigned long rdmsr(unsigned msr)`
- Defined: `arch/x86/msr.h:12`

## bootloader.c

### main `void main(void)`
- Defined: `bootloader.c:20`
- Doc: "gdt_start:\n" "  .quad 0\n" "  .quad 0x00CF9A000000FFFF\n" "  .quad 0x00CF92000000FFFF\n" "gdt_end:\n" ".global gdt32_p

## drivers/block.c

### bc_index `static unsigned int bc_index(unsigned int block_num)`
- Defined: `drivers/block.c:27`

### bc_invalidate `static void bc_invalidate(unsigned int block_num)`
- Defined: `drivers/block.c:31`

### block_init `void block_init(void)`
- Defined: `drivers/block.c:36`

### block_set_base `void block_set_base(unsigned int lba_base)`
- Defined: `drivers/block.c:42`

### block_read `int block_read(unsigned int block_num, void *buf)`
- Defined: `drivers/block.c:46`

### block_write `int block_write(unsigned int block_num, const void *buf)`
- Defined: `drivers/block.c:66`

### block_read_multi `int block_read_multi(unsigned int block_num, unsigned int count, void *buf)`
- Defined: `drivers/block.c:72`

### block_write_multi `int block_write_multi(unsigned int block_num, unsigned int count, const void *buf)`
- Defined: `drivers/block.c:77`

### block_flush `void block_flush(void)`
- Defined: `drivers/block.c:84`

### block_total `unsigned int block_total(void)`
- Defined: `drivers/block.c:86`

## drivers/ide.c

### ide_delay `static void ide_delay(void)`
- Defined: `drivers/ide.c:11`

### ide_read_status `static unsigned char ide_read_status(void)`
- Defined: `drivers/ide.c:21`

### ide_wait_not_busy `static int ide_wait_not_busy(unsigned int timeout)`
- Defined: `drivers/ide.c:25`

### ide_wait_drq `static int ide_wait_drq(unsigned int timeout)`
- Defined: `drivers/ide.c:33`

### ide_select_drive `static void ide_select_drive(unsigned char drive)`
- Defined: `drivers/ide.c:44`

### ide_soft_reset `static void ide_soft_reset(void)`
- Defined: `drivers/ide.c:50`

### ide_identify `static int ide_identify(void)`
- Defined: `drivers/ide.c:57`

### ide_init `void ide_init(void)`
- Defined: `drivers/ide.c:82`

### ide_present `int ide_present(void)`
- Defined: `drivers/ide.c:100`

### ide_total_sectors `unsigned int ide_total_sectors(void)`
- Defined: `drivers/ide.c:102`

### ide_read_sectors `int ide_read_sectors(unsigned int lba, unsigned int count, void *buf)`
- Defined: `drivers/ide.c:103`

### ide_write_sectors `int ide_write_sectors(unsigned int lba, unsigned int count, const void *buf)`
- Defined: `drivers/ide.c:134`

### ide_read_sector `int ide_read_sector(unsigned int lba, void *buf)`
- Defined: `drivers/ide.c:164`

### ide_write_sector `int ide_write_sector(unsigned int lba, const void *buf)`
- Defined: `drivers/ide.c:168`

## drivers/kbd.c

### kbd_q_push `void kbd_q_push(unsigned char c)`
- Defined: `drivers/kbd.c:48`

### kbd_raw_push_internal `static void kbd_raw_push_internal(unsigned char c)`
- Defined: `drivers/kbd.c:55`

### kbd_q_empty `int kbd_q_empty(void)`
- Defined: `drivers/kbd.c:62`

### kbd_q_pop `int kbd_q_pop(void)`
- Defined: `drivers/kbd.c:64`

### kbd_available `int kbd_available(void)`
- Defined: `drivers/kbd.c:71`

### kbd_raw_mode_get `int kbd_raw_mode_get(void)`
- Defined: `drivers/kbd.c:77`

### kbd_raw_mode_set `void kbd_raw_mode_set(int on)`
- Defined: `drivers/kbd.c:79`

### kbd_raw_empty `int kbd_raw_empty(void)`
- Defined: `drivers/kbd.c:80`

### kbd_raw_pop `int kbd_raw_pop(void)`
- Defined: `drivers/kbd.c:81`

### kbd_raw_push_byte `void kbd_raw_push_byte(unsigned char c)`
- Defined: `drivers/kbd.c:87`

### kbd_e0_get `int kbd_e0_get(void)`
- Defined: `drivers/kbd.c:88`

### kbd_e0_set `void kbd_e0_set(int v)`
- Defined: `drivers/kbd.c:89`

### kbd_flush_all `void kbd_flush_all(void)`
- Defined: `drivers/kbd.c:90`

### kbd_read `int kbd_read(void)`
- Defined: `drivers/kbd.c:94`

### kbd_reset_for_shell `void kbd_reset_for_shell(void)`
- Defined: `drivers/kbd.c:190`

## drivers/pcspk.c

### pcspk_init `void pcspk_init(void)`
- Defined: `drivers/pcspk.c:26`

### pcspk_set_volume `void pcspk_set_volume(unsigned volume)`
- Defined: `drivers/pcspk.c:31`

### pcspk_get_volume `unsigned pcspk_get_volume(void)`
- Defined: `drivers/pcspk.c:35`

### pcspk_tone `void pcspk_tone(unsigned freq)`
- Defined: `drivers/pcspk.c:39`

### pcspk_off `void pcspk_off(void)`
- Defined: `drivers/pcspk.c:57`

## drivers/rtc.c

### rtc_cmos_read `static inline unsigned char rtc_cmos_read(unsigned char reg)`
- Defined: `drivers/rtc.c:31`
- Doc: The RTC reports a time-of-day that is mid-update; waiting out this flag * before reading the three fields makes the snap

### rtc_from_bcd `static int rtc_from_bcd(unsigned char v)`
- Defined: `drivers/rtc.c:36`

### rtc_read_tod `int rtc_read_tod(int *hour, int *min, int *sec)`
- Defined: `drivers/rtc.c:40`

## drivers/sb16.c

### sb16_slot `static unsigned char *sb16_slot(unsigned i)`
- Defined: `drivers/sb16.c:109`

### sb16_kring_reset `static void sb16_kring_reset(void)`
- Defined: `drivers/sb16.c:115`
- Doc: Multicanal mixer streams.  Each stream has its own ring buffer and volume. sb16_mix_all sums all active streams into the

### sb16_stream_open `int sb16_stream_open(void)`
- Defined: `drivers/sb16.c:122`
- Doc: static unsigned char mix_buf[SB16_PCM_BUF]; static unsigned char *sb16_slot(unsigned i) { return (unsigned char *)(unsig

### sb16_stream_close `void sb16_stream_close(int id)`
- Defined: `drivers/sb16.c:138`

### sb16_stream_submit `int sb16_stream_submit(int id, const unsigned char *pcm, unsigned len)`
- Defined: `drivers/sb16.c:146`

### sb16_stream_volume `void sb16_stream_volume(int id, unsigned char vol)`
- Defined: `drivers/sb16.c:161`

### sb16_stream_count `int sb16_stream_count(void)`
- Defined: `drivers/sb16.c:167`

### sb16_mix_all `static void sb16_mix_all(void)`
- Defined: `drivers/sb16.c:178`
- Doc: if (!streams[id].active) return; streams[id].volume = vol; } int sb16_stream_count(void) { int i, n = 0; for (i = 0; i <

### sb16_pump `void sb16_pump(void)`
- Defined: `drivers/sb16.c:214`
- Doc: sample += (src * (int)s->volume) >> 8; if (sample > 127) sample = 127; if (sample < -128) sample = -128; mix_buf[k] = (u

### sb16_wait_dsp_write `static void sb16_wait_dsp_write(void)`
- Defined: `drivers/sb16.c:237`

### sb16_read_data `static int sb16_read_data(unsigned char *out)`
- Defined: `drivers/sb16.c:242`

### sb16_reset_dsp `static int sb16_reset_dsp(void)`
- Defined: `drivers/sb16.c:251`

### sb16_dma_play `static void sb16_dma_play(unsigned addr, unsigned len)`
- Defined: `drivers/sb16.c:265`

### sb16_refill `static void sb16_refill(int slot_index)`
- Defined: `drivers/sb16.c:281`

### sb16_arm `static void sb16_arm(int from_irq)`
- Defined: `drivers/sb16.c:297`

### sb16_present `int sb16_present(void)`
- Defined: `drivers/sb16.c:321`

### sb16_tone `void sb16_tone(unsigned freq)`
- Defined: `drivers/sb16.c:323`

### sb16_pcm_open `void sb16_pcm_open(void)`
- Defined: `drivers/sb16.c:338`

### sb16_pcm_close `void sb16_pcm_close(void)`
- Defined: `drivers/sb16.c:354`

### sb16_pcm_submit `int sb16_pcm_submit(const unsigned char *pcm, unsigned len)`
- Defined: `drivers/sb16.c:356`

### sb16_irq `void sb16_irq(void)`
- Defined: `drivers/sb16.c:379`

### sb16_poll `void sb16_poll(void)`
- Defined: `drivers/sb16.c:386`

### sb16_ring_free `unsigned sb16_ring_free(void)`
- Defined: `drivers/sb16.c:391`

### sb16_mode_active `int sb16_mode_active(void)`
- Defined: `drivers/sb16.c:393`

### sb16_counters `void sb16_counters(sb16_counters_t *out)`
- Defined: `drivers/sb16.c:394`

### sb16_init `int sb16_init(void)`
- Defined: `drivers/sb16.c:398`

## fs/kfile.c

### kfile_stdin `KFILE *kfile_stdin(void)`
- Defined: `fs/kfile.c:14`

### kfile_stdout `KFILE *kfile_stdout(void)`
- Defined: `fs/kfile.c:16`

### kfile_stderr `KFILE *kfile_stderr(void)`
- Defined: `fs/kfile.c:17`

### kfopen `KFILE *kfopen(const char *path, const char *mode)`
- Defined: `fs/kfile.c:18`

### kfclose `int kfclose(KFILE *f)`
- Defined: `fs/kfile.c:88`

### kfgetc `int kfgetc(KFILE *f)`
- Defined: `fs/kfile.c:101`

### kfgets `char *kfgets(char *buf, int size, KFILE *f)`
- Defined: `fs/kfile.c:122`

### kfungetc `int kfungetc(int c, KFILE *f)`
- Defined: `fs/kfile.c:136`

### kfread `unsigned long kfread(void *ptr, unsigned long size, unsigned long n, KFILE *f)`
- Defined: `fs/kfile.c:142`

### kfwrite `unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long n, KFILE *f)`
- Defined: `fs/kfile.c:164`

### kfseek `int kfseek(KFILE *f, long offset, int whence)`
- Defined: `fs/kfile.c:193`

### kftell `long kftell(KFILE *f)`
- Defined: `fs/kfile.c:207`

### kfflush `int kfflush(KFILE *f)`
- Defined: `fs/kfile.c:211`

### kfputs `int kfputs(const char *s, KFILE *f)`
- Defined: `fs/kfile.c:234`

### kfputc `int kfputc(int c, KFILE *f)`
- Defined: `fs/kfile.c:240`

### krewind `void krewind(KFILE *f)`
- Defined: `fs/kfile.c:245`

## fs/minifs.c

### minifs_compress `unsigned int minifs_compress(const void *src, unsigned int src_len,
                             ...`
- Defined: `fs/minifs.c:23`
- Doc: #include "block.h" #include "ide.h" #include "lz4_kernel.h" #define DE_NAME(de) ((const char *)((de) + 1)) #define DE_NA

### minifs_decompress `unsigned int minifs_decompress(const void *src, unsigned int src_len,
                           ...`
- Defined: `fs/minifs.c:33`

### minifs_crc16 `static unsigned short minifs_crc16(const void *data, unsigned int len)`
- Defined: `fs/minifs.c:44`

### minifs_crc32 `static unsigned int minifs_crc32(const void *data, unsigned int len)`
- Defined: `fs/minifs.c:56`

### roundup4 `static unsigned int roundup4(unsigned int v)`
- Defined: `fs/minifs.c:68`

### div_round_up `static unsigned int div_round_up(unsigned int n, unsigned int d)`
- Defined: `fs/minifs.c:70`

### fs_write_super `static int fs_write_super(void)`
- Defined: `fs/minifs.c:76`
- Doc: crc ^= (unsigned int)p[i]; for (j = 0; j < 8; j++) crc = (crc >> 1) ^ ((crc & 1) ? 0xEDB88320 : 0); } return crc ^ 0xFFF

### fs_read_inode `static int fs_read_inode(unsigned int num, MiniFSInode *out)`
- Defined: `fs/minifs.c:87`
- Doc: } /* ---- Superblock I/O ---- static int fs_write_super(void) { unsigned char buf[MINIFS_BLOCK_SIZE]; kmemset(buf, 0, MI

### fs_write_inode `static int fs_write_inode(unsigned int num, const MiniFSInode *in)`
- Defined: `fs/minifs.c:96`

### bm_test `static int bm_test(unsigned char *bm, unsigned int bit)`
- Defined: `fs/minifs.c:107`
- Doc: kmemcpy(out, buf + offset, sizeof(MiniFSInode)); return 0; } static int fs_write_inode(unsigned int num, const MiniFSIno

### bm_set `static void bm_set(unsigned char *bm, unsigned int bit)`
- Defined: `fs/minifs.c:111`

### bm_clear `static void bm_clear(unsigned char *bm, unsigned int bit)`
- Defined: `fs/minifs.c:115`

### minifs_alloc_block `int minifs_alloc_block(void)`
- Defined: `fs/minifs.c:121`
- Doc: static int bm_test(unsigned char *bm, unsigned int bit) { return (bm[bit / 8] >> (bit % 8)) & 1; } static void bm_set(un

### minifs_free_block `void minifs_free_block(unsigned int block)`
- Defined: `fs/minifs.c:138`

### minifs_alloc_inode `int minifs_alloc_inode(void)`
- Defined: `fs/minifs.c:146`
- Doc: fs_sb.first_free_hint = (idx + 1) % total; return (int)idx; } } return -1; } void minifs_free_block(unsigned int block) 

### minifs_free_inode `void minifs_free_inode(int num)`
- Defined: `fs/minifs.c:158`

### minifs_inode_get_block `int minifs_inode_get_block(MiniFSInode *inode, unsigned int logblk,
                           un...`
- Defined: `fs/minifs.c:166`
- Doc: fs_sb.free_inodes--; return (int)i; } } return -1; } void minifs_free_inode(int num) { if (num < 0 || (unsigned int)num 

### fs_inode_set_block `static int fs_inode_set_block(MiniFSInode *inode, unsigned int logblk,
                          ...`
- Defined: `fs/minifs.c:189`

### minifs_inode_alloc_block `int minifs_inode_alloc_block(MiniFSInode *inode, unsigned int logblk)`
- Defined: `fs/minifs.c:235`

### fs_inode_free_all_blocks `static void fs_inode_free_all_blocks(MiniFSInode *inode)`
- Defined: `fs/minifs.c:249`

### journal_load_super `static void journal_load_super(void)`
- Defined: `fs/minifs.c:319`

### journal_save_super `static void journal_save_super(unsigned int state)`
- Defined: `fs/minifs.c:335`

### journal_save_entries `static void journal_save_entries(void)`
- Defined: `fs/minifs.c:346`

### minifs_journal_begin `void minifs_journal_begin(unsigned int txn_id)`
- Defined: `fs/minifs.c:361`

### minifs_journal_add_block `void minifs_journal_add_block(unsigned int block)`
- Defined: `fs/minifs.c:368`

### minifs_journal_commit `int minifs_journal_commit(unsigned int txn_id)`
- Defined: `fs/minifs.c:393`

### minifs_journal_recover `void minifs_journal_recover(void)`
- Defined: `fs/minifs.c:411`

### fs_namecmp `static int fs_namecmp(const char *a, unsigned char alen, const char *b)`
- Defined: `fs/minifs.c:451`
- Doc: kmemcpy(&e, ebuf + slot * sizeof(MiniFSJournalEntry), sizeof(MiniFSJournalEntry)); /* Restore the original block content

### minifs_dir_lookup `int minifs_dir_lookup(int dir_ino, const char *name)`
- Defined: `fs/minifs.c:460`

### minifs_dir_add_entry `int minifs_dir_add_entry(int dir_ino, const char *name, int child_ino,
                         u...`
- Defined: `fs/minifs.c:484`

### minifs_dir_remove_entry `int minifs_dir_remove_entry(int dir_ino, const char *name)`
- Defined: `fs/minifs.c:598`

### minifs_dir_read `int minifs_dir_read(int dir_ino, int index, MiniFSDirEntry *out, char *name_out)`
- Defined: `fs/minifs.c:623`

### minifs_resolve_path `int minifs_resolve_path(const char *path)`
- Defined: `fs/minifs.c:657`
- Doc: kmemcpy(out, de, sizeof(MiniFSDirEntry)); kmemcpy(name_out, DE_NAME(de), de->name_len); name_out[de->name_len] = 0; retu

### minifs_create `int minifs_create(const char *path, unsigned short mode)`
- Defined: `fs/minifs.c:690`
- Doc: if (*p) p++; continue; } if (len > MINIFS_MAX_FILENAME) return -1; kmemcpy(namebuf, start, len); namebuf[len] = 0; ino =

### minifs_mkdir `int minifs_mkdir(const char *path, unsigned short mode)`
- Defined: `fs/minifs.c:742`

### minifs_unlink `int minifs_unlink(const char *path)`
- Defined: `fs/minifs.c:792`

### minifs_rmdir `int minifs_rmdir(const char *path)`
- Defined: `fs/minifs.c:828`

### minifs_read `int minifs_read(int inode_num, void *buf, unsigned int offset, unsigned int len)`
- Defined: `fs/minifs.c:865`

### minifs_write `int minifs_write(int inode_num, const void *buf, unsigned int offset,
                 unsigned i...`
- Defined: `fs/minifs.c:929`

### minifs_truncate `int minifs_truncate(int inode_num, unsigned int new_size)`
- Defined: `fs/minifs.c:1012`

### minifs_stat `int minifs_stat(int inode_num, MiniFSInode *out)`
- Defined: `fs/minifs.c:1028`

### minifs_access `int minifs_access(const char *path)`
- Defined: `fs/minifs.c:1032`

### minifs_init `void minifs_init(void)`
- Defined: `fs/minifs.c:1038`
- Doc: inode.size = new_size; inode.checksum = minifs_crc32(&inode, sizeof(MiniFSInode) - 4); return fs_write_inode((unsigned i

### minifs_get_lba_start `unsigned int minifs_get_lba_start(void)`
- Defined: `fs/minifs.c:1046`

### minifs_is_mounted `int minifs_is_mounted(void)`
- Defined: `fs/minifs.c:1048`

### minifs_mount `int minifs_mount(void)`
- Defined: `fs/minifs.c:1049`

### minifs_mkfs `int minifs_mkfs(unsigned int total_blocks)`
- Defined: `fs/minifs.c:1123`

### minifs_sync `int minifs_sync(void)`
- Defined: `fs/minifs.c:1194`

### minifs_file_open `MiniFSFile *minifs_file_open(int inode_num, int flags)`
- Defined: `fs/minifs.c:1209`

### minifs_file_close `int minifs_file_close(MiniFSFile *f)`
- Defined: `fs/minifs.c:1223`

### minifs_get_total_blocks `unsigned int minifs_get_total_blocks(void)`
- Defined: `fs/minifs.c:1230`

## fs/ramdisk.c

### ramdisk_reserve `static int ramdisk_reserve(unsigned long want)`
- Defined: `fs/ramdisk.c:24`

### ramdisk_setup_from `void ramdisk_setup_from(void *data, unsigned size)`
- Defined: `fs/ramdisk.c:42`

### ramdisk_init `void ramdisk_init(void)`
- Defined: `fs/ramdisk.c:94`

### ramdisk_open `RDFile *ramdisk_open(const char *name)`
- Defined: `fs/ramdisk.c:111`

### ramdisk_read `int ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len)`
- Defined: `fs/ramdisk.c:121`

### ramdisk_write `int ramdisk_write(RDFile *f, const void *buf, unsigned offset, unsigned len)`
- Defined: `fs/ramdisk.c:129`

### ramdisk_create `RDFile *ramdisk_create(const char *name, unsigned size)`
- Defined: `fs/ramdisk.c:137`

### ramdisk_resize `int ramdisk_resize(RDFile *f, unsigned newsize)`
- Defined: `fs/ramdisk.c:151`

### ramdisk_list `int ramdisk_list(RDFile **out, int max)`
- Defined: `fs/ramdisk.c:188`

### ramdisk_count `int ramdisk_count(void)`
- Defined: `fs/ramdisk.c:196`

### ramdisk_file_name `const char *ramdisk_file_name(int idx)`
- Defined: `fs/ramdisk.c:201`

### ramdisk_delete `int ramdisk_delete(RDFile *f)`
- Defined: `fs/ramdisk.c:206`

## fs/vfs.c

### vfs_init `void vfs_init(void)`
- Defined: `fs/vfs.c:19`

### vfs_register `int vfs_register(const char *prefix, const vfs_ops_t *ops)`
- Defined: `fs/vfs.c:24`

### vfs_unregister `int vfs_unregister(const char *prefix)`
- Defined: `fs/vfs.c:40`

### vfs_open `int vfs_open(const char *path, int mode, vfs_file_t *f)`
- Defined: `fs/vfs.c:52`

### ramdisk_vfs_open `static int ramdisk_vfs_open(const char *path, int mode, void **handle)`
- Defined: `fs/vfs.c:85`

### ramdisk_vfs_read `static int ramdisk_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len)`
- Defined: `fs/vfs.c:110`

### ramdisk_vfs_write `static int ramdisk_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len)`
- Defined: `fs/vfs.c:119`

### ramdisk_vfs_close `static int ramdisk_vfs_close(void *handle)`
- Defined: `fs/vfs.c:127`

### ramdisk_vfs_fstat `static int ramdisk_vfs_fstat(void *handle, unsigned long *size_out)`
- Defined: `fs/vfs.c:133`

### ramdisk_vfs_truncate `static int ramdisk_vfs_truncate(void *handle, unsigned long size)`
- Defined: `fs/vfs.c:140`

### minifs_vfs_open `static int minifs_vfs_open(const char *path, int mode, void **handle)`
- Defined: `fs/vfs.c:164`

### minifs_vfs_read `static int minifs_vfs_read(void *handle, void *buf, unsigned long pos, unsigned long len)`
- Defined: `fs/vfs.c:192`

### minifs_vfs_write `static int minifs_vfs_write(void *handle, const void *buf, unsigned long pos, unsigned long len)`
- Defined: `fs/vfs.c:201`

### minifs_vfs_close `static int minifs_vfs_close(void *handle)`
- Defined: `fs/vfs.c:209`

### minifs_vfs_fstat `static int minifs_vfs_fstat(void *handle, unsigned long *size_out)`
- Defined: `fs/vfs.c:215`

### minifs_vfs_truncate `static int minifs_vfs_truncate(void *handle, unsigned long size)`
- Defined: `fs/vfs.c:222`

### fs_resolve `int fs_resolve(const char *path, char *out, unsigned cap)`
- Defined: `fs/vfs.c:243`

### fs_dir_exists `int fs_dir_exists(const char *dir)`
- Defined: `fs/vfs.c:276`

### fs_is_dir `int fs_is_dir(const char *resolved)`
- Defined: `fs/vfs.c:301`

### minifs_mkdir_p `int minifs_mkdir_p(const char *resolved)`
- Defined: `fs/vfs.c:314`

### vfs_register_builtins `void vfs_register_builtins(void)`
- Defined: `fs/vfs.c:337`

## fs/zip.c

### zip_read_whole `static unsigned char *zip_read_whole(const char *path, unsigned long *size)`
- Defined: `fs/zip.c:25`
- Doc: Read a whole file (ramdisk first, MiniFS fallback) into a fresh kernel buffer, growing until the read stops making progr

### marker `* marker (trailing '/') is preserved by the caller, not here. */
static int zip_sanitize_name(con...`
- Defined: `fs/zip.c:50`

### zip_build_path `static int zip_build_path(const char *destdir, const char *name, char *out)`
- Defined: `fs/zip.c:79`
- Doc: Build the combined extraction path: destdir (already resolved, may be "") joined with the sanitized entry name. Returns 

### zip_ensure_dir_tree `static int zip_ensure_dir_tree(const char *dir)`
- Defined: `fs/zip.c:95`
- Doc: Create every directory component of `dir` (a resolved, slash-separated name with no trailing '/'), including `dir` itsel

### zip_do_entry `static int zip_do_entry(mz_zip_archive *zip, mz_uint idx, const char *destdir)`
- Defined: `fs/zip.c:117`
- Doc: Extract one archive entry under destdir. Junk entries (empty or '.'-only * names) are skipped and count as success. Retu

### shell_cmd_unzip `void shell_cmd_unzip(int argc, char **argv)`
- Defined: `fs/zip.c:176`
- Doc: if (!data) return 0; if (n != usize) { mz_free(data); return 0; } f = kfopen(resolved, "w"); if (!f) { mz_free(data); re

### shell_cmd_zip `void shell_cmd_zip(int argc, char **argv)`
- Defined: `fs/zip.c:254`
- Doc: zip <out.zip> <file...> — store each file (under its sanitized name) into * a new archive.

## kernel.c

### vga_get_x `int vga_get_x(void)`
- Defined: `kernel.c:29`
- Doc: ================================================================ VGA driver * ==========================================

### vga_get_y `int vga_get_y(void)`
- Defined: `kernel.c:31`

### vga_set_xy `void vga_set_xy(int x, int y)`
- Defined: `kernel.c:32`

### vga_get_color `char vga_get_color(void)`
- Defined: `kernel.c:33`

### vga_offset `static inline unsigned vga_offset(int x, int y)`
- Defined: `kernel.c:36`
- Doc: ================================================================ VGA driver * ==========================================

### vga_clear `void vga_clear(void)`
- Defined: `kernel.c:38`

### vga_set_cursor `void vga_set_cursor(int x, int y)`
- Defined: `kernel.c:49`

### vga_scroll `void vga_scroll(void)`
- Defined: `kernel.c:69`

### vga_newline `void vga_newline(void)`
- Defined: `kernel.c:88`

### vga_cursor_enable `void vga_cursor_enable(int on)`
- Defined: `kernel.c:99`
- Doc: Toggle the hardware text cursor. bit 5 of VGA index 0x0A disables the * cursor; clearing it brings the cursor back.

### vga_raw_space `static void vga_raw_space(void)`
- Defined: `kernel.c:105`

### redir_grow `static int redir_grow(void)`
- Defined: `kernel.c:128`

### redirect_active `int redirect_active(void)`
- Defined: `kernel.c:138`

### redirect_putc `static int redirect_putc(char c)`
- Defined: `kernel.c:140`

### redirect_suspend `int redirect_suspend(void)`
- Defined: `kernel.c:147`

### redirect_resume `void redirect_resume(int was)`
- Defined: `kernel.c:153`

### redirect_begin `int redirect_begin(void)`
- Defined: `kernel.c:157`

### redirect_commit `int redirect_commit(const char *path, int append_mode)`
- Defined: `kernel.c:165`

### vga_putc `void vga_putc(char c)`
- Defined: `kernel.c:182`

### vga_puts `void vga_puts(const char *s)`
- Defined: `kernel.c:220`

### syscall_init `void syscall_init(void)`
- Defined: `kernel.c:304`

### register_libc_symbols `static void register_libc_symbols(void)`
- Defined: `kernel.c:398`
- Doc: ================================================================ Libc symbol registration * ============================

### __attribute__ `__attribute__((section(".init.text")))
void kmain(void)`
- Defined: `kernel.c:473`

## kernel.h

### outb `static inline void outb(unsigned short port, unsigned char val)`
- Defined: `kernel.h:20`
- Doc: The user-window memory layout (load base, stack, brk cap, graphics back-buffers, framebuffer, kernel heap) is defined ON

### inb `static inline unsigned char inb(unsigned short port)`
- Defined: `kernel.h:23`

### outw `static inline void outw(unsigned short port, unsigned short val)`
- Defined: `kernel.h:28`

### inw `static inline unsigned short inw(unsigned short port)`
- Defined: `kernel.h:31`

## kernel/cvm_host.c

### n_strcmp `static int64_t n_strcmp(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:21`

### n_strncmp `static int64_t n_strncmp(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:27`

### n_strcpy `static int64_t n_strcpy(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:34`

### n_strncpy `static int64_t n_strncpy(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:40`

### n_memcpy `static int64_t n_memcpy(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:47`

### n_memset `static int64_t n_memset(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:54`

### n_memmove `static int64_t n_memmove(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:60`

### n_memcmp `static int64_t n_memcmp(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:67`

### n_strchr `static int64_t n_strchr(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:74`

### n_strstr `static int64_t n_strstr(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:80`

### n_malloc `static int64_t n_malloc(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:87`

### n_free `static int64_t n_free(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:92`

### n_calloc `static int64_t n_calloc(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:97`

### n_realloc `static int64_t n_realloc(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:105`

### n_exit `static int64_t n_exit(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:113`

### n_fopen `static int64_t n_fopen(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:120`

### n_fclose `static int64_t n_fclose(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:127`

### n_fread `static int64_t n_fread(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:133`

### n_fwrite `static int64_t n_fwrite(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:140`

### n_fseek `static int64_t n_fseek(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:147`

### n_ftell `static int64_t n_ftell(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:153`

### n_rewind `static int64_t n_rewind(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:159`

### n_fputs `static int64_t n_fputs(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:166`

### n_fputc `static int64_t n_fputc(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:172`

### n_fgetc `static int64_t n_fgetc(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:178`

### n_ungetc `static int64_t n_ungetc(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:184`

### n_fflush `static int64_t n_fflush(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:190`

### n_putchar `static int64_t n_putchar(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:196`

### n_write `static int64_t n_write(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:203`

### n_read `static int64_t n_read(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:212`

### n_puts `static int64_t n_puts(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:227`

### n_atol `static int64_t n_atol(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:235`

### n_strtol `static int64_t n_strtol(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:248`

### n_stderr_addr `static int64_t n_stderr_addr(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:261`

### n_stdout_addr `static int64_t n_stdout_addr(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:266`

### n_stdin_addr `static int64_t n_stdin_addr(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:271`

### kout_char `static void kout_char(void *ctx, char c)`
- Defined: `kernel/cvm_host.c:276`

### kout_uint `static void kout_uint(void *ctx, unsigned long long v, int base, int upper)`
- Defined: `kernel/cvm_host.c:282`

### kformat `static void kformat(void *ctx, const char *fmt, uint64_t *argv, int argc)`
- Defined: `kernel/cvm_host.c:295`

### n_fprintf `static int64_t n_fprintf(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:361`

### n_printf `static int64_t n_printf(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:368`

### n_sprintf `static int64_t n_sprintf(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:375`

### n_snprintf `static int64_t n_snprintf(void *vm, int ac, uint64_t *av)`
- Defined: `kernel/cvm_host.c:383`

### register_host_natives `static void register_host_natives(CvmState *vm)`
- Defined: `kernel/cvm_host.c:391`

### cvm_main `int cvm_main(int argc, char **argv)`
- Defined: `kernel/cvm_host.c:436`

## kernel/editor.c

### edit_alloc `static EditBuf *edit_alloc(const char *fname)`
- Defined: `kernel/editor.c:37`

### edit_free `static void edit_free(EditBuf *e)`
- Defined: `kernel/editor.c:54`

### edit_load `static int edit_load(EditBuf *e)`
- Defined: `kernel/editor.c:60`

### edit_save `static int edit_save(EditBuf *e)`
- Defined: `kernel/editor.c:96`

### edit_print `static void edit_print(EditBuf *e, int idx)`
- Defined: `kernel/editor.c:110`

### edit_list `static void edit_list(EditBuf *e, int start, int end)`
- Defined: `kernel/editor.c:121`
- Doc: List a (possibly empty) range [start, end], both 1-based inclusive.  A * single argument lists from that line; no argume

### edit_set_line `static int edit_set_line(EditBuf *e, int idx, const char *text)`
- Defined: `kernel/editor.c:132`

### edit_insert `static int edit_insert(EditBuf *e, int idx, const char *text)`
- Defined: `kernel/editor.c:141`

### edit_delete `static int edit_delete(EditBuf *e, int idx)`
- Defined: `kernel/editor.c:151`

### edit_line_cstr `static void edit_line_cstr(EditLine *l, char *out)`
- Defined: `kernel/editor.c:164`
- Doc: Copy a line into a NUL-terminated scratch buffer (lines are otherwise * stored length-prefixed without a terminator).

### edit_search `static void edit_search(EditBuf *e, const char *needle)`
- Defined: `kernel/editor.c:168`

### edit_status `static void edit_status(EditBuf *e)`
- Defined: `kernel/editor.c:185`

### edit_usage `static void edit_usage(void)`
- Defined: `kernel/editor.c:193`

### edit_refuse_save `static int edit_refuse_save(EditBuf *e)`
- Defined: `kernel/editor.c:205`
- Doc: A buffer that did not hold the whole file must never be written back: * saving it would drop the part that was never loa

### edit_arg_line `static int edit_arg_line(int argc, char **argv, EditBuf *e, int *out)`
- Defined: `kernel/editor.c:210`

### edit_loop `static void edit_loop(EditBuf *e)`
- Defined: `kernel/editor.c:218`

### shell_cmd_edit `void shell_cmd_edit(int argc, char **argv)`
- Defined: `kernel/editor.c:306`

## kernel/exec.c

### vga_mode_set `void vga_mode_set(int on)`
- Defined: `kernel/exec.c:59`

### vga_mode_is_active `int  vga_mode_is_active(void)`
- Defined: `kernel/exec.c:61`

### vga_gfx_ran_set `void vga_gfx_ran_set(int on)`
- Defined: `kernel/exec.c:62`

### k_user_fault_return `void k_user_fault_return(void)`
- Defined: `kernel/exec.c:65`
- Doc: VGA mode tracking: set/cleared by k_exec_user and k_run_rel when a * graphics program owns the display. static int vga_m

### setup_user_stack `unsigned long *setup_user_stack(char *sbase, unsigned long ssize,
                               ...`
- Defined: `kernel/exec.c:81`
- Doc: __asm__ volatile( "mov %[kdata], %%ax\n" "mov %%ax, %%ds\n" "mov %%ax, %%es\n" "mov %%ax, %%fs\n" "mov %%ax, %%gs\n" :: 

### k_exec_user `int k_exec_user(void *entry, int argc, char **argv)`
- Defined: `kernel/exec.c:116`

### k_run_rel `int k_run_rel(prog_entry_t entry, int argc, char **argv)`
- Defined: `kernel/exec.c:201`

### kexit `void kexit(int code)`
- Defined: `kernel/exec.c:233`

## kernel/klog.c

### klog_set_level `void klog_set_level(log_level_t level)`
- Defined: `kernel/klog.c:28`

### klog_set_subsys_level `void klog_set_subsys_level(log_subsystem_t subsys, log_level_t level)`
- Defined: `kernel/klog.c:32`

### klog_disable `void klog_disable(void)`
- Defined: `kernel/klog.c:37`

### klog_enable `void klog_enable(void)`
- Defined: `kernel/klog.c:39`

### klog `void klog(log_level_t level, log_subsystem_t subsys,
          const char *fmt, ...)`
- Defined: `kernel/klog.c:40`

### klog_hexdump `void klog_hexdump(log_level_t level, log_subsystem_t subsys,
                  const void *data, ...`
- Defined: `kernel/klog.c:118`

## kernel/loader.c

### elf_name_copy `static void elf_name_copy(char *out, unsigned out_cap, const char *tab,
                         ...`
- Defined: `kernel/loader.c:92`
- Doc: #define PF_X               1 #define ELF_MAX_SEGMENTS   64 #define ELF_NAME_MAX       64 struct exec_range { unsigned lo

### elf_load_fail `static void elf_load_fail(void *base, void **sec_addrs, const char *why)`
- Defined: `kernel/loader.c:106`

### elf_load `void *elf_load(void *data, unsigned size)`
- Defined: `kernel/loader.c:114`
- Doc: if (out[i] == '\0') break; i++; } } out[i] = '\0'; } static void elf_load_fail(void *base, void **sec_addrs, const char 

### apply_exec_relocs `static void apply_exec_relocs(void *data, unsigned size, unsigned long base,
                    ...`
- Defined: `kernel/loader.c:348`
- Doc: char sn[ELF_NAME_MAX]; elf_name_copy(sn, sizeof(sn), strtab, strtab_size, symtab[k].st_name); int alloc = (symtab[k].st_

### load_exec_elf `void *load_exec_elf(void *data, unsigned size)`
- Defined: `kernel/loader.c:431`

## kernel/lz4_kernel.c

### LZ4_read32 `static inline unsigned int LZ4_read32(const unsigned char *p)`
- Defined: `kernel/lz4_kernel.c:6`
- Doc: define HASH_BITS 12 define HASH_SIZE (1 << HASH_BITS)

### LZ4_read16 `static inline unsigned int LZ4_read16(const unsigned char *p)`
- Defined: `kernel/lz4_kernel.c:13`

### LZ4_write16 `static inline void LZ4_write16(unsigned char *dst, unsigned short v)`
- Defined: `kernel/lz4_kernel.c:20`

### LZ4_hash `static unsigned int LZ4_hash(const unsigned char *p)`
- Defined: `kernel/lz4_kernel.c:25`

### LZ4_compressBound `int LZ4_compressBound(int inputSize)`
- Defined: `kernel/lz4_kernel.c:32`

### LZ4_compress_default `int LZ4_compress_default(const char *src, char *dst, int srcSize, int dstCapacity)`
- Defined: `kernel/lz4_kernel.c:39`

### LZ4_decompress_safe `int LZ4_decompress_safe(const char *src, char *dst, int compressedSize, int dstCapacity)`
- Defined: `kernel/lz4_kernel.c:163`

## kernel/mm.c

### kallocator_init `void kallocator_init(void)`
- Defined: `kernel/mm.c:12`
- Doc: ================================================================ Memory allocator  Thin wrappers over dlmalloc 2.8.6 (th

### kmalloc `void *kmalloc(unsigned long size)`
- Defined: `kernel/mm.c:16`

### kfree `void kfree(void *ptr)`
- Defined: `kernel/mm.c:21`

### kcalloc `void *kcalloc(unsigned long nmemb, unsigned long size)`
- Defined: `kernel/mm.c:26`

### krealloc `void *krealloc(void *ptr, unsigned long size)`
- Defined: `kernel/mm.c:30`

### kmalloc_percpu `void *kmalloc_percpu(unsigned long size, unsigned long align)`
- Defined: `kernel/mm.c:47`
- Doc: Per-CPU memory allocation.  Allocates cpu_count * size bytes, aligned to `align`, zeroed. Each CPU accesses its own regi

## kernel/mm/paging.c

### mm_setup_protections `void mm_setup_protections(void)`
- Defined: `kernel/mm/paging.c:18`
- Doc: mm_setup_protections  - boot-time user-window NX + framebuffer/backbuffer mapping mm_user_pte_update    - set/clear NX o

### mm_user_pte_update `void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3)`
- Defined: `kernel/mm/paging.c:100`

### mm_user_set_exec `void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3)`
- Defined: `kernel/mm/paging.c:121`

### pt_page_alloc `void *pt_page_alloc(void)`
- Defined: `kernel/mm/paging.c:133`
- Doc: define PT_ALLOC_HDR  sizeof(void *)

### pt_page_free `void pt_page_free(void *ptr)`
- Defined: `kernel/mm/paging.c:143`

### pt_clone_user `uint64_t pt_clone_user(uint64_t parent_cr3)`
- Defined: `kernel/mm/paging.c:149`

### pt_free_user `void pt_free_user(uint64_t cr3)`
- Defined: `kernel/mm/paging.c:227`

## kernel/mm/swap.c

### swap_lba `static unsigned long swap_lba(void)`
- Defined: `kernel/mm/swap.c:23`

### swap_out `int swap_out(unsigned long window_sz)`
- Defined: `kernel/mm/swap.c:29`

### swap_in `int swap_in(void)`
- Defined: `kernel/mm/swap.c:78`

## kernel/printf.c

### putc_buf `static void putc_buf(char c, void *ctx, int *written)`
- Defined: `kernel/printf.c:6`
- Doc: ================================================================ printf family * =======================================

### putc_file `static void putc_file(char c, void *ctx, int *written)`
- Defined: `kernel/printf.c:12`

### putc_str `static void putc_str(char c, void *ctx, int *written)`
- Defined: `kernel/printf.c:18`

### emit_num `static void emit_num(void (*emit)(char, void *, int *), void *ctx, int *written,
                ...`
- Defined: `kernel/printf.c:25`

### kformat `static void kformat(void (*emit)(char, void *, int *), void *ctx,
                    int *writte...`
- Defined: `kernel/printf.c:43`

### kprintf `int kprintf(const char *fmt, ...)`
- Defined: `kernel/printf.c:142`

### kfprintf `int kfprintf(KFILE *f, const char *fmt, ...)`
- Defined: `kernel/printf.c:151`

### ksprintf `int ksprintf(char *buf, const char *fmt, ...)`
- Defined: `kernel/printf.c:160`

### putc_snbuf `static void putc_snbuf(char c, void *ctx, int *written)`
- Defined: `kernel/printf.c:173`

### ksnprintf `int ksnprintf(char *buf, unsigned long size, const char *fmt, ...)`
- Defined: `kernel/printf.c:178`

## kernel/redirect.c

### shell_report_exit `void shell_report_exit(int code)`
- Defined: `kernel/redirect.c:10`
- Doc: ================================================================ Console output capture for shell redirection  The hot-p

### shell_report `void shell_report(const char *what, const char *detail)`
- Defined: `kernel/redirect.c:16`

### shell_take_redirect `int shell_take_redirect(int *argc, char **argv, char **path, int *append_mode)`
- Defined: `kernel/redirect.c:24`

## kernel/sched.c

### read_cr3 `static inline unsigned long read_cr3(void)`
- Defined: `kernel/sched.c:29`

### __attribute__ `typedef struct __attribute__((packed))`
- Defined: `kernel/sched.c:37`
- Doc: int    cpu_count = 1; volatile uint64_t sys_ticks; volatile int user_program_active; spinlock_t sched_lock = SPINLOCK_IN

### __attribute__ `typedef struct __attribute__((packed))`
- Defined: `kernel/sched.c:49`
- Doc: /* ---- TSS ---- typedef struct __attribute__((packed)) { uint32_t res0; uint64_t rsp0, rsp1, rsp2; uint64_t res1; uint6

### alloc_kstack `static uint64_t alloc_kstack(void)`
- Defined: `kernel/sched.c:63`
- Doc: typedef struct __attribute__((packed)) { uint16_t off_lo; uint16_t sel; uint8_t ist; uint8_t type_attr; uint16_t off_mid

### free_kstack `static void free_kstack(uint64_t top)`
- Defined: `kernel/sched.c:74`

### idt_set `static void idt_set(int vec, void (*h)(void))`
- Defined: `kernel/sched.c:90`
- Doc: if (!top) return; int idx = (int)(((char *)top - (char *)kstack_pool) / (16*1024)); if (idx >= 0 && idx < MAX_PROCS) kst

### idt_init `static void idt_init(void)`
- Defined: `kernel/sched.c:100`

### pic_init `static void pic_init(void)`
- Defined: `kernel/sched.c:113`
- Doc: } static void idt_init(void) { kmemset(idt, 0, sizeof(idt)); int i; for (i = 0; i < 256; i++) if (isr_stub_table[i]) idt

### pit_init `static void pit_init(void)`
- Defined: `kernel/sched.c:126`
- Doc: Master: unmask IRQ0 (timer) + IRQ1 (keyboard) + IRQ2 (cascade) + * IRQ5 (Sound Blaster 16 DMA done).  0xD8 = ~bits 2,3,4

### pic_eoi `static void pic_eoi(int irq)`
- Defined: `kernel/sched.c:132`

### tss_init `static void tss_init(void)`
- Defined: `kernel/sched.c:140`

### isr_dispatch `void isr_dispatch(int vector, trap_frame_t *frame)`
- Defined: `kernel/sched.c:180`
- Doc: tss_gdtr_buf[2] = gdtr_base & 0xFF; tss_gdtr_buf[3] = (gdtr_base >> 8) & 0xFF; tss_gdtr_buf[4] = (gdtr_base >> 16) & 0xF

### ring `* the hardware ring (CS RPL) and the fault address. */
        if ((frame->cs & 3) == 3 &&
      ...`
- Defined: `kernel/sched.c:300`

### proc_get `proc_t *proc_get(int pid)`
- Defined: `kernel/sched.c:314`
- Doc: the hardware ring (CS RPL) and the fault address. if ((frame->cs & 3) == 3 && frame->rip >= 0x400000 && frame->rip < 0x0

### proc_create `int proc_create(const char *name, int parent_pid)`
- Defined: `kernel/sched.c:320`

### schedule `void schedule(void)`
- Defined: `kernel/sched.c:373`

### yield `void yield(void)`
- Defined: `kernel/sched.c:396`

### do_exit `void do_exit(int code)`
- Defined: `kernel/sched.c:401`

### do_waitpid `int do_waitpid(int pid)`
- Defined: `kernel/sched.c:478`

### do_kill `int do_kill(int pid)`
- Defined: `kernel/sched.c:505`

### timer_tick `void timer_tick(void)`
- Defined: `kernel/sched.c:512`

### mouse_wait_cmd `static void mouse_wait_cmd(void)`
- Defined: `kernel/sched.c:516`
- Doc: schedule(); } } int do_kill(int pid) { proc_t *p = proc_get(pid); if (!p) return -1; do_exit(-1); return 0; } void timer

### mouse_wait_data `static void mouse_wait_data(void)`
- Defined: `kernel/sched.c:522`

### mouse_write `static void mouse_write(unsigned char data)`
- Defined: `kernel/sched.c:529`

### mouse_read `static unsigned char mouse_read(void)`
- Defined: `kernel/sched.c:536`

### mouse_hw_init `static void mouse_hw_init(void)`
- Defined: `kernel/sched.c:541`

### mouse_disable `void mouse_disable(void)`
- Defined: `kernel/sched.c:585`

### mouse_enable `void mouse_enable(void)`
- Defined: `kernel/sched.c:587`

### sched_init `void sched_init(void)`
- Defined: `kernel/sched.c:588`

## kernel/scrollback.c

### sb_init `void sb_init(void)`
- Defined: `kernel/scrollback.c:16`

### sb_capture_row0 `void sb_capture_row0(void)`
- Defined: `kernel/scrollback.c:22`

### sb_reset `void sb_reset(void)`
- Defined: `kernel/scrollback.c:33`

### sb_get_count `int sb_get_count(void)`
- Defined: `kernel/scrollback.c:37`

### sb_get_head `int sb_get_head(void)`
- Defined: `kernel/scrollback.c:39`

### sb_get_char `char sb_get_char(int row, int col)`
- Defined: `kernel/scrollback.c:40`

## kernel/serial.c

### serial_init `void serial_init(void)`
- Defined: `kernel/serial.c:18`
- Doc: define COM1 0x3F8

### serial_tx_ready `static int serial_tx_ready(void)`
- Defined: `kernel/serial.c:28`

### serial_rx_ready `static int serial_rx_ready(void)`
- Defined: `kernel/serial.c:30`

### serial_putc `void serial_putc(char c)`
- Defined: `kernel/serial.c:31`

### serial_puts `void serial_puts(const char *s)`
- Defined: `kernel/serial.c:36`

### serial_available `int serial_available(void)`
- Defined: `kernel/serial.c:38`

### serial_getc `int serial_getc(void)`
- Defined: `kernel/serial.c:40`

## kernel/shell.c

### shell_queue_launch `void shell_queue_launch(const char *cmd)`
- Defined: `kernel/shell.c:65`
- Doc: Queue a desktop-icon command to run after the current user program exits. Overwrites any earlier pending launch; safe to

### shell_prompt `static void shell_prompt(void)`
- Defined: `kernel/shell.c:85`

### shell_parse_vol `static int shell_parse_vol(const char *s, unsigned *out)`
- Defined: `kernel/shell.c:93`
- Doc: Strict decimal parse for the `vol` builtin: the whole argument must be an optional sign followed by at least one digit, 

### pb_empty `static int pb_empty(void)`
- Defined: `kernel/shell.c:126`

### pb_count `static int pb_count(void)`
- Defined: `kernel/shell.c:128`

### pb_push_back `static void pb_push_back(unsigned char c)`
- Defined: `kernel/shell.c:129`

### pb_push_front `static void pb_push_front(unsigned char c)`
- Defined: `kernel/shell.c:134`

### pb_pop `static int pb_pop(void)`
- Defined: `kernel/shell.c:139`

### pb_peek `static int pb_peek(void)`
- Defined: `kernel/shell.c:145`

### raw_blocking_getc `static int raw_blocking_getc(void)`
- Defined: `kernel/shell.c:152`
- Doc: Next raw byte (kbd queue, then serial, then PS/2) without touching the * pushback FIFO; blocks until one is available.

### raw_try_getc `static int raw_try_getc(void)`
- Defined: `kernel/shell.c:171`
- Doc: int c = serial_getc(); if (c >= 0) return c; } if (kbd_available()) { int c = kbd_read(); if (c >= 0) return c; } if (vg

### consume_page_after_esc `static int consume_page_after_esc(void)`
- Defined: `kernel/shell.c:206`
- Doc: Called after an ESC byte has been read. Pulls the remainder of the sequence non-blocking and classifies it. Returns 1 (P

### console_getc `* returns console_getc() simply serves the FIFO again. */
int console_getc(void)`
- Defined: `kernel/shell.c:231`

### console_peek `static int console_peek(void)`
- Defined: `kernel/shell.c:253`
- Doc: Next buffered byte without consuming it, or -1 when nothing is available right now. Used to tell an ESC prefix from a co

### scrollback_render `static void scrollback_render(int voff, int total, const unsigned char *saved)`
- Defined: `kernel/shell.c:268`
- Doc: --- Scrollback view ----  Renders a 25-row window over (scrollback ring + live screen) into the VGA framebuffer and to t

### scrollback_view `static void scrollback_view(int initial_dir)`
- Defined: `kernel/shell.c:305`

### shell_readline_buf `void shell_readline_buf(char *buf, int size)`
- Defined: `kernel/shell.c:350`
- Doc: Read one line into buf (at most size-1 chars). Echoes input and * honours backspace. Shared by the shell prompt and the 

### shell_name_base `static const char *shell_name_base(const char *path)`
- Defined: `kernel/shell.c:379`
- Doc: The component of a ramdisk path after the last '/', or the whole path when * there is no '/'. Used to match a bare comma

### shell_complete_replace `static void shell_complete_replace(char *buf, int size, int *pos,
                               ...`
- Defined: `kernel/shell.c:389`
- Doc: Replace the current word [word_start, word_start+wlen) in `buf` with `text` and move the cursor to the end of the comple

### shell_readline `static void shell_readline(void)`
- Defined: `kernel/shell.c:406`

### shell_hist_show `static void shell_hist_show(char *buf, int size, int *pos, const char *text)`
- Defined: `kernel/shell.c:415`
- Doc: Redraw the edit line: erase what is shown, then write `text` into buf and onto the console, leaving the text cursor at `

### shell_line_repaint `static void shell_line_repaint(char *buf, int size, int pos)`
- Defined: `kernel/shell.c:437`
- Doc: Repaint the edit line after a cursor move or mid-line edit: erase the whole visible line, rewrite buf, then back the con

### shell_line_insert `static void shell_line_insert(char *buf, int size, int *pos, char c)`
- Defined: `kernel/shell.c:450`
- Doc: Insert character c into buf at `pos`, shifting the tail right. Bounds * checked; the caller repaints afterwards.

### shell_line_backspace `static void shell_line_backspace(char *buf, int size, int *pos)`
- Defined: `kernel/shell.c:459`
- Doc: Insert character c into buf at `pos`, shifting the tail right. Bounds * checked; the caller repaints afterwards. static 

### shell_line_delete `static void shell_line_delete(char *buf, int size, int *pos)`
- Defined: `kernel/shell.c:467`
- Doc: kmemmove(buf + *pos + 1, buf + *pos, (unsigned long)(len - *pos + 1)); buf[*pos] = c; (*pos)++; } /* Delete the characte

### shell_line_kill_front `static void shell_line_kill_front(char *buf, int size, int *pos)`
- Defined: `kernel/shell.c:474`
- Doc: int len = (int)kstrlen(buf); if (*pos <= 0) return; kmemmove(buf + *pos - 1, buf + *pos, (unsigned long)(len - *pos + 1)

### shell_line_kill_tail `static void shell_line_kill_tail(char *buf, int size, int *pos)`
- Defined: `kernel/shell.c:481`
- Doc: static void shell_line_delete(char *buf, int size, int *pos) { int len = (int)kstrlen(buf); if (*pos >= len) return; kme

### shell_line_kill_word `static void shell_line_kill_word(char *buf, int size, int *pos)`
- Defined: `kernel/shell.c:486`
- Doc: /* Delete from the cursor to the start of the line (Ctrl+U). static void shell_line_kill_front(char *buf, int size, int 

### shell_hist_nav `static void shell_hist_nav(char *buf, int size, int *pos, int up)`
- Defined: `kernel/shell.c:497`
- Doc: Move through the history ring: up recalls older entries, down moves * forward again and finally restores the live line.

### shell_parse `int shell_parse(char *line, char **argv, int max_args)`
- Defined: `kernel/shell.c:696`

### shell_run `void shell_run(void)`
- Defined: `kernel/shell.c:717`

### shell_load `static int shell_load(const char *fname, char *progname_out, void **entry_out)`
- Defined: `kernel/shell.c:764`
- Doc: Load an ELF file from the ramdisk and register it under its filename stem. Returns 1 for an ET_REL program, 2 for an ET_

### outw_port `static inline void outw_port(unsigned short port, unsigned short val)`
- Defined: `kernel/shell.c:822`

### shell_cmd_poweroff `static void shell_cmd_poweroff(void)`
- Defined: `kernel/shell.c:828`
- Doc: define QEMU_PM_PORT 0x604

### shell_run_dir_for `static const ShellRunDir *shell_run_dir_for(const char *name)`
- Defined: `kernel/shell.c:845`
- Doc: The toolchain directory that owns `name`, chosen by suffix. Bare names with * no recognised suffix fall through to the c

### shell_file_is_real `static int shell_file_is_real(const char *resolved)`
- Defined: `kernel/shell.c:863`
- Doc: Is `resolved` (already normalised against the cwd) a real ramdisk file? A * directory name or a non-existent path is rej

### shell_resolve_run `static int shell_resolve_run(const char *name, char *out, unsigned cap)`
- Defined: `kernel/shell.c:875`
- Doc: Resolve `name` to a full ramdisk path suitable for running. A bare name is tried first against the cwd, then through the

### shell_run_elf_buf `static int shell_run_elf_buf(const char *data, unsigned size, int argc,
                         ...`
- Defined: `kernel/shell.c:911`
- Doc: Run a raw ELF image (ET_REL, ET_EXEC or ET_DYN) already read into `data`. argv[0] is the program name the program sees. 

### shell_run_elf_file `static int shell_run_elf_file(const char *full, int argc, char **argv)`
- Defined: `kernel/shell.c:932`
- Doc: Load the ramdisk file at `full` and run it as an ELF. Returns the exit * code, or -1 when the file cannot be read or loa

### shell_run_elf_minifs `static int shell_run_elf_minifs(const char *name, int argc, char **argv)`
- Defined: `kernel/shell.c:945`
- Doc: Load a Linux ELF from the MiniFS disk and run it (preserves the historical * `run` fallback when a name is not on the ra

### shell_run_cvm `static int shell_run_cvm(const char *full, int argc, char **argv)`
- Defined: `kernel/shell.c:991`
- Doc: Run a `.cvm` module at the resolved path `full`. The interpreter is loaded from the ramdisk on first use and cached. arg

### shell_run_file `static int shell_run_file(const char *name, int argc, char **argv)`
- Defined: `kernel/shell.c:1020`
- Doc: Run `name` as a ramdisk/MiniFS file: `.cvm` modules through the interpreter, ELF files by content through the matching l

### shell_run_any `int shell_run_any(const char *name, int argc, char **argv)`
- Defined: `kernel/shell.c:1049`
- Doc: Unified dispatcher used by `run` and by bare commands: a registered program wins, then the runnable-file resolver. argv[

### gfx_parse_int `static int gfx_parse_int(const char *s, int *out)`
- Defined: `kernel/shell.c:1109`
- Doc: --- Graphics debugging (`gfx` builtin) ----  The serial console is the observability surface the BDD suite drives, but a

### gfx_read_palette `static void gfx_read_palette(unsigned char pal[768])`
- Defined: `kernel/shell.c:1129`
- Doc: Read the current 256-entry VGA DAC palette (3x6-bit per entry, read at 8-bit precision by the kernel's normalisation). U

### shell_cmd_gfx `static void shell_cmd_gfx(int argc, char **argv)`
- Defined: `kernel/shell.c:1135`

### shell_cmd_wm `static void shell_cmd_wm(int argc, char **argv)`
- Defined: `kernel/shell.c:1251`
- Doc: `wm <op>` — window-manager operations on the terminal window, exposed as a shell builtin so the tilin-WM behaviour (mini

### shell_cmd_hash `static void shell_cmd_hash(int argc, char **argv)`
- Defined: `kernel/shell.c:1272`
- Doc: `hash <file>` — XXH64 (64-bit, seed 0) of a ramdisk/MiniFS file, streamed in bounded chunks so a large MiniFS file never

### shell_exec_builtin `void shell_exec_builtin(int argc, char **argv)`
- Defined: `kernel/shell.c:1286`

## kernel/string.c

### kstrlen `unsigned long kstrlen(const char *s)`
- Defined: `kernel/string.c:16`
- Doc: string.c -- Kernel string and memory functions.  Pure functions with no dependencies beyond their own prototypes in kern

### kstrcpy `char *kstrcpy(char *dst, const char *src)`
- Defined: `kernel/string.c:22`

### kstrncpy `char *kstrncpy(char *dst, const char *src, unsigned long n)`
- Defined: `kernel/string.c:28`

### kstrncat `char *kstrncat(char *dst, const char *src, unsigned long n)`
- Defined: `kernel/string.c:34`

### kstrcmp `int kstrcmp(const char *a, const char *b)`
- Defined: `kernel/string.c:42`

### kstrncmp `int kstrncmp(const char *a, const char *b, unsigned long n)`
- Defined: `kernel/string.c:47`

### kstrchr `char *kstrchr(const char *s, int c)`
- Defined: `kernel/string.c:52`

### kstrstr `char *kstrstr(const char *hay, const char *ndl)`
- Defined: `kernel/string.c:57`

### kmemcpy `void *kmemcpy(void *dst, const void *src, unsigned long n)`
- Defined: `kernel/string.c:67`

### kmemset `void *kmemset(void *dst, int c, unsigned long n)`
- Defined: `kernel/string.c:74`

### kmemcmp `int kmemcmp(const void *a, const void *b, unsigned long n)`
- Defined: `kernel/string.c:80`

### kmemmove `void *kmemmove(void *dst, const void *src, unsigned long n)`
- Defined: `kernel/string.c:86`

### katol `long katol(const char *s)`
- Defined: `kernel/string.c:94`

## kernel/symtab.c

### k_register_symbol `void k_register_symbol(const char *name, void *addr)`
- Defined: `kernel/symtab.c:9`

### ksym_resolve `void *ksym_resolve(const char *name)`
- Defined: `kernel/symtab.c:17`

### kprog_slot `KProg *kprog_slot(const char *name)`
- Defined: `kernel/symtab.c:33`

### kprog_lookup `KProg *kprog_lookup(const char *name)`
- Defined: `kernel/symtab.c:41`

### k_register_program `void k_register_program(const char *name, prog_entry_t entry)`
- Defined: `kernel/symtab.c:48`

### k_register_process `void k_register_process(const char *name, void *proc_entry)`
- Defined: `kernel/symtab.c:56`

### k_spawn `int k_spawn(const char *name, int argc, char **argv)`
- Defined: `kernel/symtab.c:64`

## kernel/syscalls.c

### sys_minios_dns `static long sys_minios_dns(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:59`

### sys_minios_tls_handshake `static long sys_minios_tls_handshake(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:65`

### sys_minios_tls_send `static long sys_minios_tls_send(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:70`

### sys_minios_tls_recv `static long sys_minios_tls_recv(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:75`

### sys_minios_time `static long sys_minios_time(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:80`

### sys_minios_kbd `static long sys_minios_kbd(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:84`

### sys_minios_palette `static long sys_minios_palette(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:99`

### sys_minios_kbd_raw `static long sys_minios_kbd_raw(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:107`

### sys_minios_vga_mode `static long sys_minios_vga_mode(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:113`

### sys_minios_pcspk_init `static long sys_minios_pcspk_init(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:120`

### sys_minios_pcspk_tone `static long sys_minios_pcspk_tone(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:124`

### sys_minios_doom_frame `static long sys_minios_doom_frame(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:128`

### sys_minios_rtc `static long sys_minios_rtc(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:132`

### sys_minios_fb_info `static long sys_minios_fb_info(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:146`

### sys_minios_pcspk_vol `static long sys_minios_pcspk_vol(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:158`

### sys_minios_spawn `static long sys_minios_spawn(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:166`

### sys_minios_lz4_compress `static long sys_minios_lz4_compress(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:172`

### sys_minios_lz4_decompress `static long sys_minios_lz4_decompress(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:185`

### sys_minios_mouse `static long sys_minios_mouse(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:199`

### sys_minios_nk_frame `static long sys_minios_nk_frame(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:208`

### sys_minios_sb16_open `static long sys_minios_sb16_open(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:218`

### sys_minios_sb16_submit `static long sys_minios_sb16_submit(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:223`

### sys_minios_gfx_title `static long sys_minios_gfx_title(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:231`

### sys_minios_sb16_pump `static long sys_minios_sb16_pump(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:245`

### sys_minios_sb16_stream_open `static long sys_minios_sb16_stream_open(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:249`

### sys_minios_sb16_stream_close `static long sys_minios_sb16_stream_close(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:253`

### sys_minios_sb16_stream_submit `static long sys_minios_sb16_stream_submit(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:257`

### sys_minios_sb16_stream_vol `static long sys_minios_sb16_stream_vol(long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:265`

### sys_minios_clone `static long sys_minios_clone(long flags, long newsp, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:275`

### syscall_trace_enabled `long syscall_trace_enabled(void)`
- Defined: `kernel/syscalls.c:318`

### syscall_trace_set `void syscall_trace_set(int on)`
- Defined: `kernel/syscalls.c:320`

### trace_is_noisy `static int trace_is_noisy(long n)`
- Defined: `kernel/syscalls.c:331`

### ksyscall `long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:335`

### user_range_ok `int user_range_ok(unsigned long p, unsigned long len)`
- Defined: `kernel/syscalls.c:354`
- Doc: --- User-pointer validation --------------------------------------------- The syscall boundary is the hardened edge betw

### user_str_ok `int user_str_ok(unsigned long p, unsigned long maxlen)`
- Defined: `kernel/syscalls.c:360`

### ksyscall_dispatch `static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6)`
- Defined: `kernel/syscalls.c:368`

### tools `* ET_EXEC tools (lzss/lz4/aes/json/freedom) are run by the shell, not from an
 * interpreter.
 */...`
- Defined: `kernel/syscalls.c:907`

## kernel/time.c

### ktime_rdtsc `static unsigned long ktime_rdtsc(void)`
- Defined: `kernel/time.c:11`
- Imported by: `mcp/mcp_dbg_driver.py`, `mcp/mcp_dogfood.py`, `mcp/minios_addons.py`, `mcp/minios_mcp.py`, `test_http_server.py`, `tls_test.py`, `tools/gdb_repro.py`, `tools/minios_cli.py`, `tools/minios_gui.py`, `tools/qga_client.py`, `tools/repro_gui.py`

### ktime_init `static void ktime_init(void)`
- Defined: `kernel/time.c:17`
- Imported by: `mcp/mcp_dbg_driver.py`, `mcp/mcp_dogfood.py`, `mcp/minios_addons.py`, `mcp/minios_mcp.py`, `test_http_server.py`, `tls_test.py`, `tools/gdb_repro.py`, `tools/minios_cli.py`, `tools/minios_gui.py`, `tools/qga_client.py`, `tools/repro_gui.py`

### ktime_ms `unsigned long ktime_ms(void)`
- Defined: `kernel/time.c:31`
- Imported by: `mcp/mcp_dbg_driver.py`, `mcp/mcp_dogfood.py`, `mcp/minios_addons.py`, `mcp/minios_mcp.py`, `test_http_server.py`, `tls_test.py`, `tools/gdb_repro.py`, `tools/minios_cli.py`, `tools/minios_gui.py`, `tools/qga_client.py`, `tools/repro_gui.py`

## kernel/vga_fb.c

### vga_fb_boot_config `void vga_fb_boot_config(void)`
- Defined: `kernel/vga_fb.c:24`

### lg_get `static const char *lg_get(int i)`
- Defined: `kernel/vga_fb.c:79`
- Doc: as new content is added, and remain reachable in the ring.  There is deliberately no "scroll the screen up" operation. A

### lg_push `static void lg_push(const char *line, int len)`
- Defined: `kernel/vga_fb.c:85`
- Doc: Append a completed logical line to the ring. The line is stored whole (no * width-dependent wrap), so it can be re-wrapp

### line_nrows `static int line_nrows(int len)`
- Defined: `kernel/vga_fb.c:97`
- Doc: Append a completed logical line to the ring. The line is stored whole (no * width-dependent wrap), so it can be re-wrapp

### act_nrows `static int act_nrows(void)`
- Defined: `kernel/vga_fb.c:103`

### total_rows `static int total_rows(void)`
- Defined: `kernel/vga_fb.c:107`
- Doc: else lg_head = (lg_head + 1) % SB_MAX_LINES; } /* Display rows a logical line of `len` characters occupies at term_cols.

### disp_clamp `static void disp_clamp(void)`
- Defined: `kernel/vga_fb.c:115`
- Doc: return n; } static int act_nrows(void) { return line_nrows(act_len); } /* Total display rows of the whole history (compl

### line_at `static const char *line_at(int abs, int *off)`
- Defined: `kernel/vga_fb.c:133`
- Doc: Locate the logical line contributing the display row `abs`, and set *off to the character offset where that display row 

### cursor_save_bg `static void cursor_save_bg(int mx, int my)`
- Defined: `kernel/vga_fb.c:174`
- Doc: The cursor is drawn with its arrow tip at (mx, my), so the sprite spans up-left of the pointer by CURSOR_TIP offsets. Th

### cursor_draw `static void cursor_draw(int mx, int my)`
- Defined: `kernel/vga_fb.c:182`

### cursor_restore `static void cursor_restore(int mx, int my)`
- Defined: `kernel/vga_fb.c:193`

### cursor_over `static int cursor_over(int x0, int y0, int w, int h)`
- Defined: `kernel/vga_fb.c:207`
- Doc: True when the cursor sprite overlaps the given screen rectangle. Used to decide whether a partial repaint (taskbar, term

### vga_fb_set_gfx_mode `void vga_fb_set_gfx_mode(int on)`
- Defined: `kernel/vga_fb.c:231`

### vga_fb_gfx_cursor_erase `static void vga_fb_gfx_cursor_erase(void)`
- Defined: `kernel/vga_fb.c:244`
- Doc: Restore the last composite's pointer before the new frame covers it. Only meaningful in graphics mode; the desktop path 

### vga_fb_gfx_cursor_draw `static void vga_fb_gfx_cursor_draw(void)`
- Defined: `kernel/vga_fb.c:252`
- Doc: Clamp the mouse into the framebuffer (the idle loop that normally clamps * never runs in graphics mode) and draw the poi

### vga_fb_set_palette `static void vga_fb_set_palette(void)`
- Defined: `kernel/vga_fb.c:405`
- Doc: The text area starts one FONT_H below the window's top-left corner, which * is occupied by the title bar. static int ter

### vga_fb_pixel `void vga_fb_pixel(int x, int y, uint8_t color)`
- Defined: `kernel/vga_fb.c:460`
- Doc: { 15, 15, 50},   /* D  navy (desktop bg) { 60, 90,140},   /* E  title blue {  0,220,  0},   /* F  terminal green }; outb

### vga_fb_rect `void vga_fb_rect(int x, int y, int w, int h, uint8_t color)`
- Defined: `kernel/vga_fb.c:464`

### vga_fb_char `void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg)`
- Defined: `kernel/vga_fb.c:471`

### vga_fb_str `void vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg)`
- Defined: `kernel/vga_fb.c:486`

### text_px `static void text_px(int px, int py, const char *s, uint8_t fg, uint8_t bg)`
- Defined: `kernel/vga_fb.c:498`
- Doc: Blit a text string at an absolute pixel position. Used for window chrome (title bar, taskbar) which lives outside the co

### wm_draw_buttons `static void wm_draw_buttons(int px, int py, int win_w, uint8_t fg, uint8_t bg)`
- Defined: `kernel/vga_fb.c:525`
- Doc: --- Window controls ---- Three glyph buttons at the right end of a window's title bar: minimize (_), maximize (square) a

### wm_buttons_hit `static int wm_buttons_hit(int mx, int my, int win_x, int win_y, int win_w)`
- Defined: `kernel/vga_fb.c:551`
- Doc: } for (i = 1; i < WM_BTN_H - 1; i++) { vga_fb_pixel(bx + 1, by + i, fg); vga_fb_pixel(bx + WM_BTN_W - 2, by + i, fg); } 

### wm_close_pending `int wm_close_pending(void)`
- Defined: `kernel/vga_fb.c:566`
- Doc: Close request bridge: the syscall dispatcher polls this so a graphics * program's next syscall exits it on the child's o

### wm_clear_close `void wm_clear_close(void)`
- Defined: `kernel/vga_fb.c:567`

### wm_gfx_mode_active `int wm_gfx_mode_active(void)`
- Defined: `kernel/vga_fb.c:568`

### wm_button_click `static int wm_button_click(int mx, int my)`
- Defined: `kernel/vga_fb.c:573`
- Doc: Hit-test and dispatch a click on a titled window's controls. The active window is the graphics window when one is compos

### vga_fb_blit_gfx_window `void vga_fb_blit_gfx_window(void)`
- Defined: `kernel/vga_fb.c:616`

### vga_fb_clear `void vga_fb_clear(void)`
- Defined: `kernel/vga_fb.c:641`

### vga_fb_blit_nk_window `void vga_fb_blit_nk_window(void)`
- Defined: `kernel/vga_fb.c:657`
- Doc: Composite the Nuklear UI back-buffer onto the desktop as a titled window, mirroring the DOOM window: the back-buffer is 

### term_recalc `static void term_recalc(void)`
- Defined: `kernel/vga_fb.c:688`

### draw_title `static void draw_title(void)`
- Defined: `kernel/vga_fb.c:715`
- Doc: Preserve the current window position, clamping it into range so a * drag or Ctrl+arrow move is not undone by the next la

### taskbar_layout `static void taskbar_layout(void)`
- Defined: `kernel/vga_fb.c:732`

### draw_speaker_icon `static void draw_speaker_icon(int x, int y, uint8_t color)`
- Defined: `kernel/vga_fb.c:750`
- Doc: x -= TASKBAR_PAD; x -= TASKBAR_VOL_CH * FONT_W;   tb_vol_x = x; x -= TASKBAR_PAD; x -= TASKBAR_BTN_W;             tb_plu

### taskbar_render `static void taskbar_render(void)`
- Defined: `kernel/vga_fb.c:758`

### taskbar_tick `static void taskbar_tick(void)`
- Defined: `kernel/vga_fb.c:785`
- Doc: Redraw the clock only when the wall-clock second changes. Only the taskbar strip is repainted, so the cursor must be re-

### taskbar_handle_click `static void taskbar_handle_click(int mx, int my)`
- Defined: `kernel/vga_fb.c:799`
- Doc: Click handling for the speaker icon and -/+ buttons, plus the restore * button that reappears while the terminal window 

### draw_scrollbar `static void draw_scrollbar(void)`
- Defined: `kernel/vga_fb.c:833`
- Doc: return; } if (mx >= tb_minus_x && mx < tb_minus_x + TASKBAR_BTN_W) { v = pcspk_get_volume(); pcspk_set_volume(v > TASKBA

### render_row `static void render_row(int vrow, int abs)`
- Defined: `kernel/vga_fb.c:869`
- Doc: Render one display row at viewport row `vrow` for the absolute display row `abs`. Rows outside the history (above the ol

### term_render `static void term_render(void)`
- Defined: `kernel/vga_fb.c:897`
- Doc: Full repaint of the terminal window from the logical history, honouring the current scroll position. Used on desktop red

### term_render_active `static void term_render_active(void)`
- Defined: `kernel/vga_fb.c:910`
- Doc: Repaint only the bottom region that a live edit touches: from the active line's first visible display row to the bottom 

### line `* display stale bytes left over from a longer previous line (e.g. the prompt
 * would show the ta...`
- Defined: `kernel/vga_fb.c:951`

### vga_fb_puts_term `void vga_fb_puts_term(const char *s)`
- Defined: `kernel/vga_fb.c:993`

### vga_fb_text_cursor `void vga_fb_text_cursor(int col)`
- Defined: `kernel/vga_fb.c:1000`
- Doc: Show the text cursor at character column `col` of the active line, or hide * it with a negative column. The cursor is a 

### vga_fb_hide_text_cursor `void vga_fb_hide_text_cursor(void)`
- Defined: `kernel/vga_fb.c:1008`
- Doc: Show the text cursor at character column `col` of the active line, or hide * it with a negative column. The cursor is a 

### vga_fb_draw_desktop `void vga_fb_draw_desktop(void)`
- Defined: `kernel/vga_fb.c:1011`

### vga_fb_toggle_fullscreen `void vga_fb_toggle_fullscreen(void)`
- Defined: `kernel/vga_fb.c:1037`
- Doc: Any redraw changed the pixels under the cursor; force a fresh save so a * stale snapshot never leaves pointer trails beh

### vga_fb_toggle_minimize `void vga_fb_toggle_minimize(void)`
- Defined: `kernel/vga_fb.c:1047`
- Doc: Minimize/restore the terminal window. The content is not touched; the window is merely hidden and repainted on restore. 

### vga_fb_is_minimized `int vga_fb_is_minimized(void)`
- Defined: `kernel/vga_fb.c:1053`

### vga_fb_is_fullscreen `int vga_fb_is_fullscreen(void)`
- Defined: `kernel/vga_fb.c:1055`

### vga_fb_move_terminal `void vga_fb_move_terminal(int dx, int dy)`
- Defined: `kernel/vga_fb.c:1076`

### term_max_cols `static int term_max_cols(void)`
- Defined: `kernel/vga_fb.c:1105`
- Doc: --- Tiling window operations (Alt = WM modifier) ---- Snap places the window in a screen half or quadrant and sizes it t

### term_max_rows `static int term_max_rows(void)`
- Defined: `kernel/vga_fb.c:1109`

### term_finish_layout `static void term_finish_layout(void)`
- Defined: `kernel/vga_fb.c:1113`

### vga_fb_snap_window `void vga_fb_snap_window(int zone)`
- Defined: `kernel/vga_fb.c:1119`

### vga_fb_resize `void vga_fb_resize(int dcols, int drows)`
- Defined: `kernel/vga_fb.c:1141`

### vga_fb_reset_default `void vga_fb_reset_default(void)`
- Defined: `kernel/vga_fb.c:1159`
- Doc: int ncol = term_sz_cols + dcols; int nrow = term_sz_rows + drows; if (ncol < 1) ncol = 1; if (nrow < 1) nrow = 1; if (nc

### pipe_field `static const char *pipe_field(const char *line, int idx, char *buf, int buflen)`
- Defined: `kernel/vga_fb.c:1199`
- Doc: --- Desktop shortcut icons ---- Shortcuts are defined in etc/shortcuts on the ramdisk, one per line: name|icon_path|comm

### desktop_shortcuts_load `void desktop_shortcuts_load(void)`
- Defined: `kernel/vga_fb.c:1214`

### desktop_shortcuts_draw `void desktop_shortcuts_draw(void)`
- Defined: `kernel/vga_fb.c:1273`

### desktop_shortcuts_hit_test `const char *desktop_shortcuts_hit_test(int mx, int my)`
- Defined: `kernel/vga_fb.c:1295`

### vga_fb_mouse_tick `void vga_fb_mouse_tick(void)`
- Defined: `kernel/vga_fb.c:1308`
- Doc: } const char *desktop_shortcuts_hit_test(int mx, int my) { for (int i = 0; i < shortcut_count; i++) { struct desktop_sho

### vga_fb_mouse_init `void vga_fb_mouse_init(void)`
- Defined: `kernel/vga_fb.c:1431`

### vga_fb_init `void vga_fb_init(void)`
- Defined: `kernel/vga_fb.c:1446`

## mcp/mcp_dbg_driver.py

### main `def main()`
- Defined: `mcp/mcp_dbg_driver.py:62`
- Depends on: `kernel/time.c`

### __init__ `def __init__(self)`
- Defined: `mcp/mcp_dbg_driver.py:15`
- Depends on: `kernel/time.c`

### request `def request(self, method, params)`
- Defined: `mcp/mcp_dbg_driver.py:26`
- Depends on: `kernel/time.c`

### tool `def tool(self, name, params)`
- Defined: `mcp/mcp_dbg_driver.py:44`
- Depends on: `kernel/time.c`

### close `def close(self)`
- Defined: `mcp/mcp_dbg_driver.py:52`
- Depends on: `kernel/time.c`

## mcp/mcp_dogfood.py

### main `def main()`
- Defined: `mcp/mcp_dogfood.py:76`
- Depends on: `kernel/time.c`

### __init__ `def __init__(self, addons_dir)`
- Defined: `mcp/mcp_dogfood.py:19`
- Depends on: `kernel/time.c`

### request `def request(self, method, params)`
- Defined: `mcp/mcp_dogfood.py:38`
- Depends on: `kernel/time.c`

### tool `def tool(self, name, params)`
- Defined: `mcp/mcp_dogfood.py:56`
- Depends on: `kernel/time.c`

### close `def close(self)`
- Defined: `mcp/mcp_dogfood.py:66`
- Depends on: `kernel/time.c`

## mcp/minios_addons.py

### _clean `def _clean(s)`
- Defined: `mcp/minios_addons.py:48`
- Depends on: `kernel/time.c`
- Imported by: `mcp/minios_mcp.py`

### _unquote `def _unquote(v)`
- Defined: `mcp/minios_addons.py:52`
- Depends on: `kernel/time.c`
- Imported by: `mcp/minios_mcp.py`

### parse_addon_yaml `def parse_addon_yaml(text)`
- Defined: `mcp/minios_addons.py:59`
- Doc: Parse the strict YAML subset. Returns the addon dict.
- Depends on: `kernel/time.c`
- Imported by: `mcp/minios_mcp.py`

### validate_addon `def validate_addon(addon, source)`
- Defined: `mcp/minios_addons.py:189`
- Doc: Check bounds and character sets. Raises AddonError.
- Depends on: `kernel/time.c`
- Imported by: `mcp/minios_mcp.py`

### validate_addon_path `def validate_addon_path(path)`
- Defined: `mcp/minios_addons.py:250`
- Doc: dst paths live on the ramdisk: relative, no '..', bounded charset.
- Depends on: `kernel/time.c`
- Imported by: `mcp/minios_mcp.py`

### validate_shell_line `def validate_shell_line(line)`
- Defined: `mcp/minios_addons.py:264`
- Doc: Build/verify lines are single printable-ASCII shell commands.
- Depends on: `kernel/time.c`
- Imported by: `mcp/minios_mcp.py`

### load_addons_dir `def load_addons_dir(addons_dir)`
- Defined: `mcp/minios_addons.py:278`
- Doc: Load every addon yaml; each entry is a dict or an error string.
- Depends on: `kernel/time.c`
- Imported by: `mcp/minios_mcp.py`

### split_for_editor `def split_for_editor(text)`
- Defined: `mcp/minios_addons.py:302`
- Doc: Split a source into editor-sized chunks. Raises AddonError.
- Depends on: `kernel/time.c`
- Imported by: `mcp/minios_mcp.py`

### exit_code_of `def exit_code_of(text)`
- Defined: `mcp/minios_addons.py:327`
- Depends on: `kernel/time.c`
- Imported by: `mcp/minios_mcp.py`

### install_addon `def install_addon(session, addon, cfg)`
- Defined: `mcp/minios_addons.py:356`
- Doc: Install one validated addon into the booted MiniOS session.
- Depends on: `kernel/time.c`
- Imported by: `mcp/minios_mcp.py`

### fail `def fail(lineno, why)`
- Defined: `mcp/minios_addons.py:69`
- Depends on: `kernel/time.c`
- Imported by: `mcp/minios_mcp.py`

### __init__ `def __init__(self, path)`
- Defined: `mcp/minios_addons.py:335`
- Depends on: `kernel/time.c`
- Imported by: `mcp/minios_mcp.py`

### load `def load(self)`
- Defined: `mcp/minios_addons.py:338`
- Depends on: `kernel/time.c`
- Imported by: `mcp/minios_mcp.py`

### save `def save(self, addons)`
- Defined: `mcp/minios_addons.py:348`
- Depends on: `kernel/time.c`
- Imported by: `mcp/minios_mcp.py`

## mcp/minios_mcp.py

### env_config `def env_config()`
- Defined: `mcp/minios_mcp.py:68`
- Doc: Resolve the configuration: defaults overridden by the environment.
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### clamp_timeout `def clamp_timeout(ms)`
- Defined: `mcp/minios_mcp.py:86`
- Doc: Clamp a requested wait to the bounded timeout range.
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### validate_path `def validate_path(name)`
- Defined: `mcp/minios_mcp.py:99`
- Doc: Reject file names the ramdisk or the shell would mishandle.
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### validate_content `def validate_content(text)`
- Defined: `mcp/minios_mcp.py:115`
- Doc: Reject lines the kernel readline cannot carry (printable ASCII).
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### subprocess_launch `def subprocess_launch(cfg, slave_fd)`
- Defined: `mcp/minios_mcp.py:560`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### main `def main()`
- Defined: `mcp/minios_mcp.py:868`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### __init__ `def __init__(self, code, message)`
- Defined: `mcp/minios_mcp.py:137`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### __init__ `def __init__(self, cap)`
- Defined: `mcp/minios_mcp.py:146`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### append `def append(self, data)`
- Defined: `mcp/minios_mcp.py:152`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### bytes_from `def bytes_from(self, pos)`
- Defined: `mcp/minios_mcp.py:160`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### text_from `def text_from(self, pos, end)`
- Defined: `mcp/minios_mcp.py:165`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### find `def find(self, marker, start)`
- Defined: `mcp/minios_mcp.py:172`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### wait_for `def wait_for(self, marker, start, timeout_ms)`
- Defined: `mcp/minios_mcp.py:176`
- Doc: Block until marker appears at or after start; return position.
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### _find_locked `def _find_locked(self, marker, start)`
- Defined: `mcp/minios_mcp.py:189`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### __init__ `def __init__(self, cfg)`
- Defined: `mcp/minios_mcp.py:202`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### booted `def booted(self)`
- Defined: `mcp/minios_mcp.py:213`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### status `def status(self)`
- Defined: `mcp/minios_mcp.py:216`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### _reap_stale `def _reap_stale(self)`
- Defined: `mcp/minios_mcp.py:225`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### _drop_pidfile `def _drop_pidfile(self)`
- Defined: `mcp/minios_mcp.py:261`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### boot `def boot(self, timeout_ms)`
- Defined: `mcp/minios_mcp.py:267`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### _read_loop `def _read_loop(self)`
- Defined: `mcp/minios_mcp.py:302`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### _close_pty `def _close_pty(self)`
- Defined: `mcp/minios_mcp.py:312`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### _write_line `def _write_line(self, line)`
- Defined: `mcp/minios_mcp.py:322`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### _write_editor_line `def _write_editor_line(self, line)`
- Defined: `mcp/minios_mcp.py:331`
- Doc: Editor content lines may be empty (blank lines in the file).
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### send `def send(self, line, timeout_ms)`
- Defined: `mcp/minios_mcp.py:339`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### expect `def expect(self, marker, timeout_ms)`
- Defined: `mcp/minios_mcp.py:350`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### snapshot `def snapshot(self, max_bytes)`
- Defined: `mcp/minios_mcp.py:364`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### run_test `def run_test(self, commands, expect, refute, timeout_ms)`
- Defined: `mcp/minios_mcp.py:374`
- Doc: Run a generic scenario: send a list of shell commands, then assert
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### cat `def cat(self, path)`
- Defined: `mcp/minios_mcp.py:430`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### run_python `def run_python(self, script, args, timeout_ms)`
- Defined: `mcp/minios_mcp.py:436`
- Doc: Run a MicroPython script (or `-c` code) inside MiniOS and return
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### cat_body `def cat_body(self, path, missing_ok)`
- Defined: `mcp/minios_mcp.py:447`
- Doc: Read a ramdisk file and return exactly its bytes.
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### _cleanup_parts `def _cleanup_parts(self, parts)`
- Defined: `mcp/minios_mcp.py:473`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### write `def write(self, path, content)`
- Defined: `mcp/minios_mcp.py:480`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### poweroff `def poweroff(self, timeout_ms)`
- Defined: `mcp/minios_mcp.py:517`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### terminate `def terminate(self)`
- Defined: `mcp/minios_mcp.py:537`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### close `def close(self)`
- Defined: `mcp/minios_mcp.py:556`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### __init__ `def __init__(self, cfg)`
- Defined: `mcp/minios_mcp.py:714`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### run `def run(self)`
- Defined: `mcp/minios_mcp.py:718`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### _handle `def _handle(self, line)`
- Defined: `mcp/minios_mcp.py:726`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### _initialize `def _initialize(self, params)`
- Defined: `mcp/minios_mcp.py:752`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### _call `def _call(self, params)`
- Defined: `mcp/minios_mcp.py:759`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### _dispatch `def _dispatch(self, name, args)`
- Defined: `mcp/minios_mcp.py:776`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### _addons_list `def _addons_list(self)`
- Defined: `mcp/minios_mcp.py:822`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### _addon_install `def _addon_install(self, args)`
- Defined: `mcp/minios_mcp.py:843`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

### _reply `def _reply(self, msg)`
- Defined: `mcp/minios_mcp.py:864`
- Depends on: `kernel/time.c`, `mcp/minios_addons.py`

## mcp/mutate_mcp.sh

### run_one
- Defined: `mcp/mutate_mcp.sh:115`
- Doc: Each mutant runs the suite in its own directory with its own pid file and addon state, so the runs are independent and m

## mcp/test_minios_mcp.py

### load_module `def load_module()`
- Defined: `mcp/test_minios_mcp.py:29`

### have_qemu `def have_qemu()`
- Defined: `mcp/test_minios_mcp.py:52`

### __init__ `def __init__(self, env_extra)`
- Defined: `mcp/test_minios_mcp.py:61`

### initialize `def initialize(self)`
- Defined: `mcp/test_minios_mcp.py:80`

### request `def request(self, method, params)`
- Defined: `mcp/test_minios_mcp.py:84`

### raw `def raw(self, line)`
- Defined: `mcp/test_minios_mcp.py:91`

### _read_response `def _read_response(self)`
- Defined: `mcp/test_minios_mcp.py:96`

### _roundtrip `def _roundtrip(self, msg)`
- Defined: `mcp/test_minios_mcp.py:102`

### tool `def tool(self, name, params)`
- Defined: `mcp/test_minios_mcp.py:110`

### close `def close(self)`
- Defined: `mcp/test_minios_mcp.py:120`

### setUpClass `def setUpClass(cls)`
- Defined: `mcp/test_minios_mcp.py:143`

### tearDownClass `def tearDownClass(cls)`
- Defined: `mcp/test_minios_mcp.py:149`

### test_initialize `def test_initialize(self)`
- Defined: `mcp/test_minios_mcp.py:152`

### test_tools_list `def test_tools_list(self)`
- Defined: `mcp/test_minios_mcp.py:158`

### test_ping `def test_ping(self)`
- Defined: `mcp/test_minios_mcp.py:166`

### test_unknown_method `def test_unknown_method(self)`
- Defined: `mcp/test_minios_mcp.py:170`

### test_malformed_json `def test_malformed_json(self)`
- Defined: `mcp/test_minios_mcp.py:174`

### test_unknown_tool `def test_unknown_tool(self)`
- Defined: `mcp/test_minios_mcp.py:178`

### test_send_not_booted `def test_send_not_booted(self)`
- Defined: `mcp/test_minios_mcp.py:183`

### test_send_empty_line_rejected `def test_send_empty_line_rejected(self)`
- Defined: `mcp/test_minios_mcp.py:189`

### test_test_not_booted `def test_test_not_booted(self)`
- Defined: `mcp/test_minios_mcp.py:195`

### setUpClass `def setUpClass(cls)`
- Defined: `mcp/test_minios_mcp.py:207`

### test_path_accepts_plain_names `def test_path_accepts_plain_names(self)`
- Defined: `mcp/test_minios_mcp.py:212`

### test_path_rejects_unsafe `def test_path_rejects_unsafe(self)`
- Defined: `mcp/test_minios_mcp.py:216`

### test_path_rejects_long `def test_path_rejects_long(self)`
- Defined: `mcp/test_minios_mcp.py:220`

### test_content_accepts_ascii `def test_content_accepts_ascii(self)`
- Defined: `mcp/test_minios_mcp.py:223`

### test_content_rejects_non_printable `def test_content_rejects_non_printable(self)`
- Defined: `mcp/test_minios_mcp.py:226`

### test_timeout_clamped `def test_timeout_clamped(self)`
- Defined: `mcp/test_minios_mcp.py:230`

### test_write_rejects_line_too_long `def test_write_rejects_line_too_long(self)`
- Defined: `mcp/test_minios_mcp.py:234`

### test_write_rejects_too_many_lines `def test_write_rejects_too_many_lines(self)`
- Defined: `mcp/test_minios_mcp.py:243`

### setUpClass `def setUpClass(cls)`
- Defined: `mcp/test_minios_mcp.py:256`

### test_bounds `def test_bounds(self)`
- Defined: `mcp/test_minios_mcp.py:261`

### test_find_and_total `def test_find_and_total(self)`
- Defined: `mcp/test_minios_mcp.py:268`

### test_cursor_prevents_stale_match `def test_cursor_prevents_stale_match(self)`
- Defined: `mcp/test_minios_mcp.py:275`

### guard_server `def guard_server(cls)`
- Defined: `mcp/test_minios_mcp.py:295`

### setUp `def setUp(self)`
- Defined: `mcp/test_minios_mcp.py:316`

### setUpClass `def setUpClass(cls)`
- Defined: `mcp/test_minios_mcp.py:324`

### tearDownClass `def tearDownClass(cls)`
- Defined: `mcp/test_minios_mcp.py:331`

### test_t01_boot `def test_t01_boot(self)`
- Defined: `mcp/test_minios_mcp.py:335`

### test_t02_expect `def test_t02_expect(self)`
- Defined: `mcp/test_minios_mcp.py:345`

### test_t03_write_and_cat `def test_t03_write_and_cat(self)`
- Defined: `mcp/test_minios_mcp.py:352`

### test_t04_toolchain_elf `def test_t04_toolchain_elf(self)`
- Defined: `mcp/test_minios_mcp.py:362`

### test_t05_toolchain_cvm `def test_t05_toolchain_cvm(self)`
- Defined: `mcp/test_minios_mcp.py:373`

### test_t06_selfhosted_compiler `def test_t06_selfhosted_compiler(self)`
- Defined: `mcp/test_minios_mcp.py:383`

### test_t07_bin_command_path `def test_t07_bin_command_path(self)`
- Defined: `mcp/test_minios_mcp.py:389`

### test_t08_python_script `def test_t08_python_script(self)`
- Defined: `mcp/test_minios_mcp.py:397`

### test_t09_py_eval `def test_t09_py_eval(self)`
- Defined: `mcp/test_minios_mcp.py:404`

### test_t10_minios_test `def test_t10_minios_test(self)`
- Defined: `mcp/test_minios_mcp.py:409`

### test_t11_poweroff_and_reboot `def test_t11_poweroff_and_reboot(self)`
- Defined: `mcp/test_minios_mcp.py:430`

### setUpClass `def setUpClass(cls)`
- Defined: `mcp/test_minios_mcp.py:459`

### test_parse_valid `def test_parse_valid(self)`
- Defined: `mcp/test_minios_mcp.py:469`

### test_validate_accepts_valid `def test_validate_accepts_valid(self)`
- Defined: `mcp/test_minios_mcp.py:479`

### test_unknown_key_rejected `def test_unknown_key_rejected(self)`
- Defined: `mcp/test_minios_mcp.py:483`

### test_bad_indent_rejected `def test_bad_indent_rejected(self)`
- Defined: `mcp/test_minios_mcp.py:487`

### test_validate_rejects_bad_dst `def test_validate_rejects_bad_dst(self)`
- Defined: `mcp/test_minios_mcp.py:491`

### test_validate_rejects_missing_name `def test_validate_rejects_missing_name(self)`
- Defined: `mcp/test_minios_mcp.py:496`

### test_validate_rejects_long_build_line `def test_validate_rejects_long_build_line(self)`
- Defined: `mcp/test_minios_mcp.py:500`

### test_validate_rejects_control_chars `def test_validate_rejects_control_chars(self)`
- Defined: `mcp/test_minios_mcp.py:508`

### test_validate_rejects_empty_files `def test_validate_rejects_empty_files(self)`
- Defined: `mcp/test_minios_mcp.py:513`

### setUpClass `def setUpClass(cls)`
- Defined: `mcp/test_minios_mcp.py:521`

### test_split_for_editor_chunks `def test_split_for_editor_chunks(self)`
- Defined: `mcp/test_minios_mcp.py:531`

### test_split_rejects_long_line `def test_split_rejects_long_line(self)`
- Defined: `mcp/test_minios_mcp.py:538`

### test_split_rejects_non_ascii `def test_split_rejects_non_ascii(self)`
- Defined: `mcp/test_minios_mcp.py:542`

### test_exit_code_of `def test_exit_code_of(self)`
- Defined: `mcp/test_minios_mcp.py:546`

### test_state_roundtrip `def test_state_roundtrip(self)`
- Defined: `mcp/test_minios_mcp.py:551`

### __init__ `def __init__(self, exit_codes)`
- Defined: `mcp/test_minios_mcp.py:562`

### booted `def booted(self)`
- Defined: `mcp/test_minios_mcp.py:569`

### boot `def boot(self, timeout_ms)`
- Defined: `mcp/test_minios_mcp.py:572`

### write `def write(self, path, content)`
- Defined: `mcp/test_minios_mcp.py:576`

### send `def send(self, line, timeout_ms)`
- Defined: `mcp/test_minios_mcp.py:583`

### cat_body `def cat_body(self, path, missing_ok)`
- Defined: `mcp/test_minios_mcp.py:607`

### _cleanup_parts `def _cleanup_parts(self, parts)`
- Defined: `mcp/test_minios_mcp.py:619`

### setUpClass `def setUpClass(cls)`
- Defined: `mcp/test_minios_mcp.py:627`

### tearDownClass `def tearDownClass(cls)`
- Defined: `mcp/test_minios_mcp.py:659`

### make_addon `def make_addon(self)`
- Defined: `mcp/test_minios_mcp.py:664`

### test_install_success `def test_install_success(self)`
- Defined: `mcp/test_minios_mcp.py:686`

### test_install_mismatch_aborts_and_cleans `def test_install_mismatch_aborts_and_cleans(self)`
- Defined: `mcp/test_minios_mcp.py:699`

### test_install_multi_chunk_reassembly `def test_install_multi_chunk_reassembly(self)`
- Defined: `mcp/test_minios_mcp.py:713`

### test_install_verify_failure_aborts `def test_install_verify_failure_aborts(self)`
- Defined: `mcp/test_minios_mcp.py:744`

### test_install_build_failure_aborts `def test_install_build_failure_aborts(self)`
- Defined: `mcp/test_minios_mcp.py:751`

### setUpClass `def setUpClass(cls)`
- Defined: `mcp/test_minios_mcp.py:764`

### tearDownClass `def tearDownClass(cls)`
- Defined: `mcp/test_minios_mcp.py:801`

### test_addons_list `def test_addons_list(self)`
- Defined: `mcp/test_minios_mcp.py:809`

### test_install_fixture `def test_install_fixture(self)`
- Defined: `mcp/test_minios_mcp.py:815`

### test_install_unknown_addon_fails `def test_install_unknown_addon_fails(self)`
- Defined: `mcp/test_minios_mcp.py:824`

### guarded `def guarded(name, params)`
- Defined: `mcp/test_minios_mcp.py:298`

### broken_cat `def broken_cat(path, missing_ok)`
- Defined: `mcp/test_minios_mcp.py:703`

## minifs_dump.py

### u16 `def u16(d, o)`
- Defined: `minifs_dump.py:13`

### u32 `def u32(d, o)`
- Defined: `minifs_dump.py:14`

### mode_str `def mode_str(m)`
- Defined: `minifs_dump.py:16`

### main `def main()`
- Defined: `minifs_dump.py:105`

### __init__ `def __init__(self, fn)`
- Defined: `minifs_dump.py:26`

### blk `def blk(self, n)`
- Defined: `minifs_dump.py:29`

### _sb `def _sb(self)`
- Defined: `minifs_dump.py:30`

### inode `def inode(self, i)`
- Defined: `minifs_dump.py:38`

### read `def read(self, ino)`
- Defined: `minifs_dump.py:47`

### resolve `def resolve(self, path)`
- Defined: `minifs_dump.py:67`

### ls `def ls(self, ino, prefix)`
- Defined: `minifs_dump.py:86`

## minifs_fsck.py

### u16 `def u16(d, o)`
- Defined: `minifs_fsck.py:13`

### u32 `def u32(d, o)`
- Defined: `minifs_fsck.py:14`

### main `def main()`
- Defined: `minifs_fsck.py:97`

### __init__ `def __init__(self, fn)`
- Defined: `minifs_fsck.py:17`

### blk `def blk(self, n)`
- Defined: `minifs_fsck.py:23`

### _sb `def _sb(self)`
- Defined: `minifs_fsck.py:24`

### inode `def inode(self, i)`
- Defined: `minifs_fsck.py:30`

### read `def read(self, ino)`
- Defined: `minifs_fsck.py:37`

### err `def err(self, msg)`
- Defined: `minifs_fsck.py:52`

### mark_block `def mark_block(self, n)`
- Defined: `minifs_fsck.py:54`

### scan_inode `def scan_inode(self, i)`
- Defined: `minifs_fsck.py:59`

### scan_dir `def scan_dir(self, ino)`
- Defined: `minifs_fsck.py:68`

### run `def run(self)`
- Defined: `minifs_fsck.py:82`

## mkfs.minifs.py

### roundup4 `def roundup4(v)`
- Defined: `mkfs.minifs.py:22`

### div_round_up `def div_round_up(n, d)`
- Defined: `mkfs.minifs.py:25`

### crc16 `def crc16(data)`
- Defined: `mkfs.minifs.py:28`

### crc32 `def crc32(data)`
- Defined: `mkfs.minifs.py:36`

### main `def main()`
- Defined: `mkfs.minifs.py:241`

### __init__ `def __init__(self, total_blocks)`
- Defined: `mkfs.minifs.py:45`

### mark_inodes_used `def mark_inodes_used(self, start, count)`
- Defined: `mkfs.minifs.py:67`

### mark_blocks_used `def mark_blocks_used(self, start, count)`
- Defined: `mkfs.minifs.py:71`

### alloc_inode `def alloc_inode(self)`
- Defined: `mkfs.minifs.py:75`

### alloc_block `def alloc_block(self)`
- Defined: `mkfs.minifs.py:81`

### create_root `def create_root(self)`
- Defined: `mkfs.minifs.py:87`

### create_inode `def create_inode(self, mode)`
- Defined: `mkfs.minifs.py:95`

### inode_set_size `def inode_set_size(self, ino, size)`
- Defined: `mkfs.minifs.py:102`

### inode_set_block `def inode_set_block(self, ino, logblk, phys)`
- Defined: `mkfs.minifs.py:106`

### add_dir_entry `def add_dir_entry(self, dir_ino, name, child_ino, ftype)`
- Defined: `mkfs.minifs.py:136`

### write_file `def write_file(self, parent_ino, name, data)`
- Defined: `mkfs.minifs.py:174`

### write_dir `def write_dir(self, parent_ino, name)`
- Defined: `mkfs.minifs.py:191`

### serialize `def serialize(self)`
- Defined: `mkfs.minifs.py:197`

### pack_tree `def pack_tree(parent_ino, path, rel)`
- Defined: `mkfs.minifs.py:271`

## mkramdisk.py

### pack_name `def pack_name(path, common)`
- Defined: `mkramdisk.py:20`

### main `def main()`
- Defined: `mkramdisk.py:30`

## mutate.sh

### usage
- Defined: `mutate.sh:51`

### restore_sources
- Defined: `mutate.sh:87`

### cleanup
- Defined: `mutate.sh:94`

### record
- Defined: `mutate.sh:201`

### find_index
- Defined: `mutate.sh:207`
- Doc: Locate a mutant by name.

## net/net.c

### net_put16 `static void net_put16(unsigned char *p, unsigned short v)`
- Defined: `net/net.c:29`
- Doc: ================================================================ Byte helpers * ========================================

### net_put32 `static void net_put32(unsigned char *p, unsigned int v)`
- Defined: `net/net.c:34`

### net_get16 `static unsigned short net_get16(const unsigned char *p)`
- Defined: `net/net.c:41`

### net_get32 `static unsigned int net_get32(const unsigned char *p)`
- Defined: `net/net.c:45`

### net_checksum `static unsigned short net_checksum(const void *data, unsigned len)`
- Defined: `net/net.c:50`

### net_arp_store `static void net_arp_store(const unsigned char *ip, const unsigned char *mac)`
- Defined: `net/net.c:75`

### net_arp_lookup `static int net_arp_lookup(const unsigned char *ip, unsigned char *mac_out)`
- Defined: `net/net.c:90`

### net_arp_request `static void net_arp_request(const unsigned char *ip)`
- Defined: `net/net.c:101`

### net_arp_resolve `static int net_arp_resolve(const unsigned char *ip, unsigned char *mac_out)`
- Defined: `net/net.c:120`
- Doc: kmemcpy(frame + 6, net_mac, NET_ETH_ALEN); net_put16(frame + 12, NET_ETHERTYPE_ARP); net_put16(frame + 14, 1);          

### net_ip_send `static int net_ip_send(const unsigned char *dip, unsigned char proto,
                       cons...`
- Defined: `net/net.c:145`
- Doc: ================================================================ IPv4 / ICMP / UDP / DNS * =============================

### net_udp_send `static int net_udp_send(const unsigned char *dip, unsigned short sport,
                        u...`
- Defined: `net/net.c:180`

### net_dns_parse `static void net_dns_parse(const unsigned char *data, unsigned len)`
- Defined: `net/net.c:203`
- Doc: net_put16(pkt + 6, 0);                    /* checksum optional for UDP kmemcpy(pkt + 8, data, len); return net_ip_send(d

### net_dns_resolve `static int net_dns_resolve(const char *host, unsigned char ip_out[4])`
- Defined: `net/net.c:239`
- Doc: rtype = net_get16(data + pos); rdlen = net_get16(data + pos + 8); pos += 10; if (pos + rdlen > len) return; if (rtype ==

### net_udp_send `net_udp_send((const unsigned char[])`
- Defined: `net/net.c:295`

### net_icmp_rx `static void net_icmp_rx(const unsigned char *ip, unsigned len)`
- Defined: `net/net.c:309`

### net_ping `static int net_ping(const unsigned char ip[4])`
- Defined: `net/net.c:332`

### net_sock_alloc `static struct net_tcp_sock *net_sock_alloc(void)`
- Defined: `net/net.c:384`

### net_sock_index `static int net_sock_index(const struct net_tcp_sock *s)`
- Defined: `net/net.c:397`

### net_tcp_checksum `static unsigned short net_tcp_checksum(const unsigned char *src, const unsigned char *dst,
      ...`
- Defined: `net/net.c:406`
- Doc: return &net_sockets[i]; } } return 0; } static int net_sock_index(const struct net_tcp_sock *s) { int i; for (i = 0; i <

### net_udp_checksum_ok `static int net_udp_checksum_ok(const unsigned char *src, const unsigned char *dst,
              ...`
- Defined: `net/net.c:422`
- Doc: const unsigned char *seg, unsigned len) { unsigned char buf[NET_TX_MAX + 12]; unsigned total = 12 + len; kmemcpy(buf, sr

### net_tcp_xmit `static int net_tcp_xmit(struct net_tcp_sock *s, unsigned flags,
                        const uns...`
- Defined: `net/net.c:437`

### net_tcp_rx `static void net_tcp_rx(const unsigned char *ip, unsigned len)`
- Defined: `net/net.c:469`
- Doc: seg[21] = 0x04;                       /* len 4 net_put16(seg + 22, NET_TCP_MSS); } else { seg[12] = 0x50; } kmemcpy(seg 

### net_tcp_connect_into `static int net_tcp_connect_into(struct net_tcp_sock *s, const unsigned char ip[4],
              ...`
- Defined: `net/net.c:555`
- Doc: } if (flags & 0x10) {                   /* ACK: peer acks our data if (s->tx_pending && (int)(ack - (s->tx_seq + s->tx_l

### net_tcp_send `static int net_tcp_send(struct net_tcp_sock *s, const char *buf, int len)`
- Defined: `net/net.c:582`
- Doc: unsigned long retry = net_time_ms() + NET_RETRY_MS; while (net_time_ms() < retry && s->state == NET_TCP_SYN_SENT) rtl_po

### net_tcp_recv `static int net_tcp_recv(struct net_tcp_sock *s, char *buf, int len)`
- Defined: `net/net.c:608`
- Doc: net_time_ms() < deadline) { unsigned long retry = net_time_ms() + NET_RETRY_MS; while (net_time_ms() < retry && s->tx_pe

### net_tcp_close `static void net_tcp_close(struct net_tcp_sock *s)`
- Defined: `net/net.c:645`

### net_rx_handle_frame `void net_rx_handle_frame(const unsigned char *frame, unsigned len)`
- Defined: `net/net.c:665`
- Doc: ================================================================ Receive path: NIC -> ethernet -> ARP/IP -> demux * ====

### net_open `int net_open(void)`
- Defined: `net/net.c:723`
- Doc: ================================================================ Public libc-style API * ===============================

### net_connect `int net_connect(const char *host, unsigned short port)`
- Defined: `net/net.c:729`

### net_send `int net_send(int fd, const char *buf, int len)`
- Defined: `net/net.c:738`

### net_recv `int net_recv(int fd, char *buf, int len)`
- Defined: `net/net.c:743`

### net_recv_timeout `int net_recv_timeout(int fd, char *buf, int len, unsigned long timeout_ms)`
- Defined: `net/net.c:748`

### net_close `void net_close(int fd)`
- Defined: `net/net.c:753`

### net_sys_socket `long net_sys_socket(long a1, long a2, long a3)`
- Defined: `net/net.c:762`
- Doc: ================================================================ Linux syscall ABI * ===================================

### net_sys_connect `long net_sys_connect(long fd, long sockaddr, long addrlen)`
- Defined: `net/net.c:771`

### net_sys_sendto `long net_sys_sendto(long fd, long buf, long len, long flags, long to, long tolen)`
- Defined: `net/net.c:784`

### net_sys_recvfrom `long net_sys_recvfrom(long fd, long buf, long len, long flags, long from, long fromlen)`
- Defined: `net/net.c:794`

### net_sys_shutdown `long net_sys_shutdown(long fd, long how)`
- Defined: `net/net.c:804`

### net_sys_close `long net_sys_close(long fd)`
- Defined: `net/net.c:811`

### net_sys_poll `long net_sys_poll(long fds, long nfds, long timeout_ms)`
- Defined: `net/net.c:818`

### net_sys_dns `long net_sys_dns(long host)`
- Defined: `net/net.c:849`
- Doc: MiniOS syscall 200: resolve a hostname, returned as a network-order * 32-bit address (like inet_addr), or -1 on failure.

### net_parse_ip `static int net_parse_ip(const char *text, unsigned char ip[4])`
- Defined: `net/net.c:859`
- Doc: ================================================================ Shell commands * ======================================

### net_cmd_status `void net_cmd_status(void)`
- Defined: `net/net.c:884`

### net_cmd_ping `void net_cmd_ping(const char *ip_text)`
- Defined: `net/net.c:900`

### net_cmd_dns `void net_cmd_dns(const char *host)`
- Defined: `net/net.c:911`

### net_register_symbols `void net_register_symbols(void)`
- Defined: `net/net.c:924`
- Doc: ================================================================ Init and symbol registration * ========================

### net_init `void net_init(void)`
- Defined: `net/net.c:932`

## net/rtl8139.c

### outb_port `static void outb_port(unsigned short port, unsigned char val)`
- Defined: `net/rtl8139.c:23`

### inb_port `static unsigned char inb_port(unsigned short port)`
- Defined: `net/rtl8139.c:27`

### outw_port `static void outw_port(unsigned short port, unsigned short val)`
- Defined: `net/rtl8139.c:33`

### outl_port `static void outl_port(unsigned short port, unsigned int val)`
- Defined: `net/rtl8139.c:37`

### inw_port `static unsigned short inw_port(unsigned short port)`
- Defined: `net/rtl8139.c:41`

### inl_port `static unsigned int inl_port(unsigned short port)`
- Defined: `net/rtl8139.c:47`

### rtl_reg8 `static unsigned char rtl_reg8(unsigned short off)`
- Defined: `net/rtl8139.c:53`

### rtl_reg8_w `static void rtl_reg8_w(unsigned short off, unsigned char v)`
- Defined: `net/rtl8139.c:55`

### rtl_reg16 `static unsigned short rtl_reg16(unsigned short off)`
- Defined: `net/rtl8139.c:56`

### rtl_reg16_w `static void rtl_reg16_w(unsigned short off, unsigned short v)`
- Defined: `net/rtl8139.c:57`

### rtl_reg32 `static unsigned int rtl_reg32(unsigned short off)`
- Defined: `net/rtl8139.c:58`

### rtl_reg32_w `static void rtl_reg32_w(unsigned short off, unsigned int v)`
- Defined: `net/rtl8139.c:59`

### pci_read32 `static unsigned int pci_read32(unsigned bus, unsigned dev, unsigned func, unsigned reg)`
- Defined: `net/rtl8139.c:69`
- Doc: define RTL_REG_CR      0x37 define RTL_REG_TSD0    0x10 define RTL_REG_TSAD0   0x20 define RTL_REG_RBSTART 0x30 define R

### pci_write32 `static void pci_write32(unsigned bus, unsigned dev, unsigned func, unsigned reg, unsigned int val)`
- Defined: `net/rtl8139.c:74`

### rtl_find `static unsigned short rtl_find(void)`
- Defined: `net/rtl8139.c:79`

### rtl_rdtsc `static unsigned long rtl_rdtsc(void)`
- Defined: `net/rtl8139.c:101`

### net_time_init `static void net_time_init(void)`
- Defined: `net/rtl8139.c:107`

### net_time_ms `unsigned long net_time_ms(void)`
- Defined: `net/rtl8139.c:121`

### rtl_present `int rtl_present(void)`
- Defined: `net/rtl8139.c:137`

### rtl_reset `static void rtl_reset(void)`
- Defined: `net/rtl8139.c:141`

### rtl_init `void rtl_init(void)`
- Defined: `net/rtl8139.c:150`

### rtl_send `int rtl_send(const unsigned char *frame, unsigned len)`
- Defined: `net/rtl8139.c:181`

### rtl_get_mac `void rtl_get_mac(unsigned char out[NET_ETH_ALEN])`
- Defined: `net/rtl8139.c:209`

### rtl_iobase `unsigned short rtl_iobase(void)`
- Defined: `net/rtl8139.c:214`

### rtl_counters `void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames)`
- Defined: `net/rtl8139.c:218`

### rtl_rx_frame_wrapped `static void rtl_rx_frame_wrapped(unsigned length)`
- Defined: `net/rtl8139.c:226`
- Doc: Copy one received frame out of the ring into the scratch buffer, * wrapping at the ring end, then hand it to the protoco

### rtl_poll `void rtl_poll(void)`
- Defined: `net/rtl8139.c:236`

## net/tls.c

### tls_fail `static void tls_fail(struct tls_session *s, const char *stage, const char *reason)`
- Defined: `net/tls.c:24`
- Doc: Diagnostics are `freedom: tls: <stage>: <reason>` lines (freedom is the only consumer of the TLS syscalls).  #include "t

### tls_fd_of `static int tls_fd_of(const struct tls_session *s)`
- Defined: `net/tls.c:32`

### tls_free_fd `void tls_free_fd(int fd)`
- Defined: `net/tls.c:39`

### tls_aad `static void tls_aad(unsigned char aad[13], int type, unsigned long long seq,
                    ...`
- Defined: `net/tls.c:52`
- Doc: Build the TLS 1.2 AEAD additional data: seq(8) || type || 0303 || * TLSCompressed.length (the plaintext length, RFC 5288

### tls_send_record `static int tls_send_record(struct tls_session *s, int type,
                           const unsi...`
- Defined: `net/tls.c:66`
- Doc: Send one record: header || nonce_explicit(8) || ciphertext || tag. The nonce_explicit is the sequence number (RFC 5288 a

### tls_send_raw_record `static int tls_send_raw_record(struct tls_session *s, int type,
                               co...`
- Defined: `net/tls.c:95`
- Doc: for (i = 0; i < 8; i++) buf[5 + i] = (unsigned char)(s->cli_seq >> (56 - i * 8)); TLS_MEMCPY(nonce, s->cli_salt, 4); TLS

### tls_read_record `static int tls_read_record(struct tls_session *s, int fd, int deadline_ms)`
- Defined: `net/tls.c:114`
- Doc: Read one record: header into s->rec_hdr, payload into s->rec. Returns: 1 = record ready, 0 = clean TCP EOF, -1 = torn re

### exchange `* key exchange (ClientHello, ClientKeyExchange) go out in plaintext
 * records, as TLS 1.2 requir...`
- Defined: `net/tls.c:173`

### build_client_hello `static int build_client_hello(struct tls_session *s, unsigned char *out)`
- Defined: `net/tls.c:190`
- Doc: const unsigned char *body, int len) { if (len < 0 || len > 1024) return -1; s->pt[0] = (unsigned char)type; s->pt[1] = (

### client_finish_flight `static int client_finish_flight(struct tls_session *s)`
- Defined: `net/tls.c:244`
- Doc: out[pos++] = 0x00; out[pos++] = 0x06; out[pos++] = 0x04; out[pos++] = 0x01;   /* rsa_pkcs1_sha256 out[pos++] = 0x04; out

### parse_server_hello `static int parse_server_hello(struct tls_session *s,
                              const unsigned...`
- Defined: `net/tls.c:339`
- Doc: sha256_final(&hcopy, hash); } tls_prf(s->master, 48, "client finished", hash, 32, verify, 12); TLS_MEMCPY(finished + 4, 

### parse_certificate `static int parse_certificate(struct tls_session *s,
                             const unsigned c...`
- Defined: `net/tls.c:369`

### parse_server_key_exchange `static int parse_server_key_exchange(struct tls_session *s,
                                     ...`
- Defined: `net/tls.c:400`

### tls_handshake `int tls_handshake(int fd, const char *host)`
- Defined: `net/tls.c:465`
- Doc: sha256(data, 64 + params_len, digest); return ecdsa_verify(0, s->leaf_pk.qx, s->leaf_pk.qy, digest, 32, m + pos, sig_len

### tls_send `int tls_send(int fd, const char *buf, int len)`
- Defined: `net/tls.c:686`
- Doc: pre-Finished is refused tls_fail(s, "handshake", "unexpected message"); tls_sessions[fd] = 0; return -1; } } s->hs_msg_l

### tls_recv `int tls_recv(int fd, char *buf, int len)`
- Defined: `net/tls.c:695`

### tls_sys_handshake `long tls_sys_handshake(long fd, long host)`
- Defined: `net/tls.c:772`
- Doc: ifndef TLS_TEST

### tls_sys_send `long tls_sys_send(long fd, long buf, long len)`
- Defined: `net/tls.c:776`

### tls_sys_recv `long tls_sys_recv(long fd, long buf, long len)`
- Defined: `net/tls.c:781`

### tls_rdtsc `static inline unsigned long long tls_rdtsc(void)`
- Defined: `net/tls.c:788`
- Doc: return tls_handshake((int)(fd - NET_FD_BASE), (const char *)host); } long tls_sys_send(long fd, long buf, long len) { if

### tls_random `void tls_random(unsigned char *out, unsigned len)`
- Defined: `net/tls.c:794`

### outb `static inline void outb(unsigned short port, unsigned char v)`
- Defined: `net/tls.c:810`
- Doc: unsigned long long seed = tls_rdtsc() ^ ((unsigned long long)net_time_ms() << 33); unsigned i; static unsigned long long

### inb `static inline unsigned char inb(unsigned short port)`
- Defined: `net/tls.c:813`

### cmos_read `static inline unsigned char cmos_read(unsigned char reg)`
- Defined: `net/tls.c:821`
- Doc: /* The port helpers in net.c are static; these live here for the RTC. #ifndef PORT_IO_DEFINED #define PORT_IO_DEFINED st

### tls_now_days `long tls_now_days(void)`
- Defined: `net/tls.c:825`

## net/tls_crypto.c

### sha256_rotr `static unsigned sha256_rotr(unsigned x, unsigned n)`
- Defined: `net/tls_crypto.c:32`

### sha256_init `void sha256_init(struct sha256_ctx *c)`
- Defined: `net/tls_crypto.c:36`

### sha256_block `static void sha256_block(struct sha256_ctx *c, const unsigned char *p)`
- Defined: `net/tls_crypto.c:49`

### sha256_update `void sha256_update(struct sha256_ctx *c, const unsigned char *data, unsigned len)`
- Defined: `net/tls_crypto.c:79`

### sha256_final `void sha256_final(struct sha256_ctx *c, unsigned char out[32])`
- Defined: `net/tls_crypto.c:104`

### sha256 `void sha256(const unsigned char *data, unsigned len, unsigned char out[32])`
- Defined: `net/tls_crypto.c:125`

### hmac_sha256 `void hmac_sha256(const unsigned char *key, unsigned klen,
                 const unsigned char *d...`
- Defined: `net/tls_crypto.c:134`
- Doc: out[i * 4 + 1] = (unsigned char)(c->state[i] >> 16); out[i * 4 + 2] = (unsigned char)(c->state[i] >> 8); out[i * 4 + 3] 

### p_hash `static void p_hash(const unsigned char *secret, unsigned secret_len,
                   const uns...`
- Defined: `net/tls_crypto.c:164`
- Doc: opad[i] = k[i] ^ 0x5c; } sha256_init(&c); sha256_update(&c, ipad, 64); sha256_update(&c, data, dlen); sha256_final(&c, i

### tls_prf `void tls_prf(const unsigned char *secret, unsigned secret_len,
             const char *label, co...`
- Defined: `net/tls_crypto.c:187`

### aes_xtime `static unsigned aes_xtime(unsigned x)`
- Defined: `net/tls_crypto.c:229`

### aes_key_expand `static void aes_key_expand(const unsigned char key[16], unsigned rk[44])`
- Defined: `net/tls_crypto.c:234`

### aes_mixcol `static void aes_mixcol(unsigned a0, unsigned a1, unsigned a2, unsigned a3,
                      ...`
- Defined: `net/tls_crypto.c:252`

### aes128_encrypt_block `void aes128_encrypt_block(const unsigned char key[16],
                          const unsigned c...`
- Defined: `net/tls_crypto.c:262`

### gf_shift_right `static gf128 gf_shift_right(gf128 v)`
- Defined: `net/tls_crypto.c:320`

### gf_mul `static gf128 gf_mul(gf128 z, gf128 h)`
- Defined: `net/tls_crypto.c:334`
- Doc: z = z * h, in GF(2^128), MSB-first. Branches on z bits (public: * AAD/ciphertext), never on h bits (secret).

### gf_put `static gf128 gf_put(const unsigned char *p)`
- Defined: `net/tls_crypto.c:350`

### ghash_blocks `static gf128 ghash_blocks(gf128 z, gf128 h, const unsigned char *data, unsigned len)`
- Defined: `net/tls_crypto.c:360`

### gcm_tag_core `static void gcm_tag_core(const unsigned char key[16],
                         const unsigned cha...`
- Defined: `net/tls_crypto.c:384`
- Doc: if (len > 0) { unsigned char pad[16]; gf128 b; TLS_MEMSET(pad, 0, 16); TLS_MEMCPY(pad, data, len); b = gf_put(pad); z.lo

### gcm_ctr_core `static void gcm_ctr_core(const unsigned char key[16],
                         const unsigned cha...`
- Defined: `net/tls_crypto.c:426`

### tls_nonce `static void tls_nonce(const unsigned char salt[4], unsigned long long seq,
                      ...`
- Defined: `net/tls_crypto.c:450`
- Doc: TLS_MEMCPY(blk, nonce, 12); blk[12] = (unsigned char)(ctr >> 24); blk[13] = (unsigned char)(ctr >> 16); blk[14] = (unsig

### gcm_tag `static void gcm_tag(const unsigned char key[16], const unsigned char salt[4],
                   ...`
- Defined: `net/tls_crypto.c:456`

### gcm_ctr `static void gcm_ctr(const unsigned char key[16], const unsigned char salt[4],
                   ...`
- Defined: `net/tls_crypto.c:466`

### aes128_gcm_seal `int aes128_gcm_seal(const unsigned char key[16],
                    const unsigned char salt[4],...`
- Defined: `net/tls_crypto.c:474`

### aes128_gcm_open `int aes128_gcm_open(const unsigned char key[16],
                    const unsigned char salt[4],...`
- Defined: `net/tls_crypto.c:486`

### aes128_gcm_seal_core `int aes128_gcm_seal_core(const unsigned char key[16],
                         const unsigned cha...`
- Defined: `net/tls_crypto.c:504`

### aes128_gcm_open_core `int aes128_gcm_open_core(const unsigned char key[16],
                         const unsigned cha...`
- Defined: `net/tls_crypto.c:515`

### bn_zero `static void bn_zero(unsigned *a, int nw)`
- Defined: `net/tls_crypto.c:536`
- Doc: unsigned char want[16]; unsigned char diff = 0; int i; if (ct_len > TLS_REC_MAX) return -1; gcm_tag_core(key, nonce, aad

### bn_is_zero `static int bn_is_zero(const unsigned *a, int nw)`
- Defined: `net/tls_crypto.c:541`

### bn_cmp `static int bn_cmp(const unsigned *a, const unsigned *b, int nw)`
- Defined: `net/tls_crypto.c:548`

### bn_add `static unsigned bn_add(const unsigned *a, const unsigned *b, unsigned *r, int nw)`
- Defined: `net/tls_crypto.c:559`
- Doc: for (i = 0; i < nw; i++) v |= a[i]; return v == 0; } static int bn_cmp(const unsigned *a, const unsigned *b, int nw) { i

### bn_sub `static unsigned bn_sub(const unsigned *a, const unsigned *b, unsigned *r, int nw)`
- Defined: `net/tls_crypto.c:571`
- Doc: /* r = a + b; returns carry out. static unsigned bn_add(const unsigned *a, const unsigned *b, unsigned *r, int nw) { uns

### bn_dbl_mod `static void bn_dbl_mod(const unsigned *a, const unsigned *n, const unsigned *v,
                 ...`
- Defined: `net/tls_crypto.c:584`
- Doc: r = 2a mod n, for a < n. v = 2^(32nw) mod n = 2^(32nw) - n (the * Montgomery "one"): 2a + carry means 2a - 2^(32nw) + v 

### bn_mont_mul `static void bn_mont_mul(const unsigned *a, const unsigned *b, const unsigned *n,
                ...`
- Defined: `net/tls_crypto.c:596`
- Doc: Montgomery multiplication. n is odd, n0inv = -n^(-1) mod 2^32. r = a*b*R^-1 mod n, R = 2^(32nw). * a, b < n.

### bn_mont_n0inv `static unsigned bn_mont_n0inv(unsigned n0)`
- Defined: `net/tls_crypto.c:635`
- Doc: carry = v >> 32; } s = (unsigned long long)t[nw] + carry; t[nw - 1] = (unsigned)s; t[nw] = t[nw + 1] + (unsigned)(s >> 3

### bn_mont_r2 `static void bn_mont_r2(const unsigned *n, const unsigned *v, int nw,
                       unsig...`
- Defined: `net/tls_crypto.c:643`
- Doc: } else { for (i = 0; i < nw; i++) r[i] = t[i]; } } /* -n^(-1) mod 2^32 via Newton iteration (n0 must be odd). static uns

### bn_from_be `static void bn_from_be(const unsigned char *bytes, unsigned len,
                       unsigned ...`
- Defined: `net/tls_crypto.c:662`

### bn_to_be `static void bn_to_be(const unsigned *a, unsigned char *out, unsigned len)`
- Defined: `net/tls_crypto.c:670`

### mont_init `static void mont_init(struct mont_ctx *m, const unsigned char *p_bytes,
                      uns...`
- Defined: `net/tls_crypto.c:676`

### mont_to `static void mont_to(struct mont_ctx *m, const unsigned *a, unsigned *r)`
- Defined: `net/tls_crypto.c:688`

### mont_from `static void mont_from(struct mont_ctx *m, const unsigned *a, unsigned *r)`
- Defined: `net/tls_crypto.c:692`

### mont_mul `static void mont_mul(struct mont_ctx *m, const unsigned *a, const unsigned *b,
                  ...`
- Defined: `net/tls_crypto.c:699`

### mont_sqr `static void mont_sqr(struct mont_ctx *m, const unsigned *a, unsigned *r)`
- Defined: `net/tls_crypto.c:704`

### mont_add `static void mont_add(struct mont_ctx *m, const unsigned *a, const unsigned *b,
                  ...`
- Defined: `net/tls_crypto.c:712`
- Doc: Field add/sub over the mont modulus (in Montgomery domain). The carry of a+b is corrected with one = 2^(32nw) - n, and a

### mont_sub `static void mont_sub(struct mont_ctx *m, const unsigned *a, const unsigned *b,
                  ...`
- Defined: `net/tls_crypto.c:720`

### mont_inv `static void mont_inv(struct mont_ctx *m, const unsigned *a, unsigned *r)`
- Defined: `net/tls_crypto.c:736`
- Doc: Field inverse via Fermat: a^(p-2) mod p (a in Montgomery domain; * the result stays in Montgomery domain).

### ec_init `static void ec_init(struct ec_curve *c, const unsigned char *p,
                    const unsigne...`
- Defined: `net/tls_crypto.c:847`

### jpt_is_inf `static int jpt_is_inf(const struct jpt *p, int nw)`
- Defined: `net/tls_crypto.c:864`

### jpt_set_inf `static void jpt_set_inf(struct jpt *p, int nw)`
- Defined: `net/tls_crypto.c:868`

### jpt_copy `static void jpt_copy(struct jpt *d, const struct jpt *s, int nw)`
- Defined: `net/tls_crypto.c:874`

### jpt_cswap `static void jpt_cswap(struct jpt *a, struct jpt *b, unsigned mask, int nw)`
- Defined: `net/tls_crypto.c:885`
- Doc: bn_zero(p->y, nw); bn_zero(p->z, nw); } static void jpt_copy(struct jpt *d, const struct jpt *s, int nw) { int i; for (i

### jpt_dbl `static void jpt_dbl(struct ec_curve *c, const struct jpt *p1, struct jpt *p3)`
- Defined: `net/tls_crypto.c:896`
- Doc: } /* Constant-time swap of two points on a 0/~0 mask. static void jpt_cswap(struct jpt *a, struct jpt *b, unsigned mask,

### jpt_add `static void jpt_add(struct ec_curve *c, const struct jpt *p1, const struct jpt *p2,
             ...`
- Defined: `net/tls_crypto.c:936`
- Doc: mont_sqr(m, E, F); mont_add(m, D, D, t);          /* 2D mont_sub(m, F, t, p3->x);      /* X3 = F - 2D mont_sub(m, D, p3-

### jpt_scalar_mult `static void jpt_scalar_mult(struct ec_curve *c, const struct jpt *base,
                         ...`
- Defined: `net/tls_crypto.c:980`
- Doc: Constant-iteration scalar multiplication: the classic ladder. * Fixed iteration count, no table lookups indexed by secre

### jpt_to_affine `static void jpt_to_affine(struct ec_curve *c, const struct jpt *p,
                          unsi...`
- Defined: `net/tls_crypto.c:1007`
- Doc: Affine from Jacobian: x = X/Z^2, y = Y/Z^3. Bytes out are big-endian. * y_out may be NULL when only the x coordinate is 

### jpt_from_affine `static int jpt_from_affine(struct ec_curve *c, const unsigned char *x_bytes,
                    ...`
- Defined: `net/tls_crypto.c:1032`
- Doc: Affine from bytes with on-curve validation. Returns 0 when the point * is valid and not the point at infinity.

### ec_curve_by_id `static struct ec_curve *ec_curve_by_id(int curve)`
- Defined: `net/tls_crypto.c:1075`

### ec_boot `static void ec_boot(void)`
- Defined: `net/tls_crypto.c:1079`

### p256_scalar_mult `int p256_scalar_mult(const unsigned char scalar[32],
                     const unsigned char qx[...`
- Defined: `net/tls_crypto.c:1087`

### p384_scalar_mult `int p384_scalar_mult(const unsigned char scalar[48],
                     const unsigned char qx[...`
- Defined: `net/tls_crypto.c:1100`

### p256_ecdh `int p256_ecdh(const unsigned char priv[32],
              const unsigned char peer_x[32], const u...`
- Defined: `net/tls_crypto.c:1113`

### der_parse_sig `static int der_parse_sig(const unsigned char *sig, unsigned sig_len,
                         con...`
- Defined: `net/tls_crypto.c:1128`
- Doc: int p256_ecdh(const unsigned char priv[32], const unsigned char peer_x[32], const unsigned char peer_y[32], unsigned cha

### ecdsa_verify `int ecdsa_verify(int curve, const unsigned char pub_x[], const unsigned char pub_y[],
           ...`
- Defined: `net/tls_crypto.c:1162`

### rsa_verify_digestinfo `static int rsa_verify_digestinfo(const unsigned char *em, unsigned em_len,
                      ...`
- Defined: `net/tls_crypto.c:1261`
- Doc: EMSA-PKCS1-v1_5 DigestInfo check for an arbitrary hash: the encoding is 00 01 FF.. 00 <prefix><digest>. Constant-time: e

### rsa_pkcs1_verify_raw `static int rsa_pkcs1_verify_raw(const unsigned char *n, unsigned n_len,
                         ...`
- Defined: `net/tls_crypto.c:1285`
- Doc: diff |= em[i] ^ 0xff; } if (i >= em_len) return -1;         /* no separator if (i < 10) return -1;              /* paddi

### rsa_pkcs1_verify_sha256 `int rsa_pkcs1_verify_sha256(const unsigned char *n, unsigned n_len,
                            c...`
- Defined: `net/tls_crypto.c:1325`

### rsa_pkcs1_verify_sha384 `int rsa_pkcs1_verify_sha384(const unsigned char *n, unsigned n_len,
                            c...`
- Defined: `net/tls_crypto.c:1339`

### sha384_rotr `static unsigned long long sha384_rotr(unsigned long long x, unsigned n)`
- Defined: `net/tls_crypto.c:1385`

### sha384_raw `static void sha384_raw(const unsigned char *data, unsigned len,
                       unsigned c...`
- Defined: `net/tls_crypto.c:1389`

### sha384 `void sha384(const unsigned char *data, unsigned len, unsigned char out[48])`
- Defined: `net/tls_crypto.c:1505`

### p256_point_valid `int p256_point_valid(const unsigned char x[32], const unsigned char y[32])`
- Defined: `net/tls_crypto.c:1511`
- Doc: out[i * 8 + 2] = (unsigned char)(state[i] >> 40); out[i * 8 + 3] = (unsigned char)(state[i] >> 32); out[i * 8 + 4] = (un

### p256_pub `int p256_pub(const unsigned char priv[32],
             unsigned char x[32], unsigned char y[32])`
- Defined: `net/tls_crypto.c:1519`

### p256_scalar_valid `int p256_scalar_valid(const unsigned char scalar[32])`
- Defined: `net/tls_crypto.c:1538`

## net/tls_x509.c

### oid_eq `static int oid_eq(const unsigned char *bytes, unsigned len,
                  const unsigned char...`
- Defined: `net/tls_x509.c:35`

### der_next `static int der_next(const unsigned char *p, unsigned limit, unsigned *pos,
                    st...`
- Defined: `net/tls_x509.c:51`
- Doc: Parse the TLV at p[pos]; advances pos to the first byte after it. * Returns 0 on success, -1 on any bound violation.

### der_container `static int der_container(const unsigned char *p, unsigned limit, unsigned *pos,
                 ...`
- Defined: `net/tls_x509.c:82`
- Doc: len = (len << 8) | p[(*pos)++]; } } else { len = p[(*pos)++]; } if (len > limit - *pos) return -1; out->val = p + *pos; 

### days_from_civil `static long days_from_civil(int y, int m, int d)`
- Defined: `net/tls_x509.c:93`
- Doc: } /* A constructed SEQUENCE/SET whose content must parse as children. static int der_container(const unsigned char *p, u

### der_time_to_days `static long der_time_to_days(const struct der_tlv *t)`
- Defined: `net/tls_x509.c:106`
- Doc: /* ---- Time ---- static long days_from_civil(int y, int m, int d) { long era, doe, yoe; int doy; y -= m <= 2 ? 1 : 0; e

### name_find_cn `static int name_find_cn(const unsigned char *p, unsigned limit,
                        struct x5...`
- Defined: `net/tls_x509.c:135`
- Doc: } if (mon < 1 || mon > 12 || day < 1 || day > 31 || year < 1970 || year > 2100) return -1; return days_from_civil(year, 

### san_add `static void san_add(struct x509_sans *out, const unsigned char *v, unsigned len)`
- Defined: `net/tls_x509.c:177`

### san_parse `static void san_parse(const unsigned char *p, unsigned limit,
                      struct x509_s...`
- Defined: `net/tls_x509.c:186`
- Doc: struct x509_sans { unsigned char dns[TLS_SAN_MAX][64]; unsigned      len[TLS_SAN_MAX]; int           count; }; static vo

### spki_parse `static int spki_parse(const unsigned char *p, unsigned limit,
                      struct tls_pu...`
- Defined: `net/tls_x509.c:203`
- Doc: unsigned seq_len, pos = 0; out->count = 0; if (der_container(p, limit, &pos, &seq, &seq_len) != 0) return; pos = 0; whil

### cert_parse `static int cert_parse(const unsigned char *der, unsigned len,
                      struct x509_c...`
- Defined: `net/tls_x509.c:278`

### ascii_lower `static int ascii_lower(int c)`
- Defined: `net/tls_x509.c:391`
- Doc: unsigned bpos = e2pos; if (der_next(ext, ext_len, &bpos, &body) != 0) break; if (oid_eq(eoid, eoid_len, oid_san, sizeof(

### host_match_exact `static int host_match_exact(const char *host, const unsigned char *name,
                        ...`
- Defined: `net/tls_x509.c:397`
- Doc: } } } } return 0; } /* ---- Hostname matching ---- static int ascii_lower(int c) { return (c >= 'A' && c <= 'Z') ? c + (

### host_match_wildcard `static int host_match_wildcard(const char *host, const unsigned char *name,
                     ...`
- Defined: `net/tls_x509.c:410`
- Doc: Wildcard: "*.example.com" matches exactly one label ("a.example.com", * never "a.b.example.com" nor "example.com").

### host_matches `static int host_matches(const char *host, const struct x509_cert *leaf)`
- Defined: `net/tls_x509.c:430`

### tls_x509_parse_pubkey `int tls_x509_parse_pubkey(const unsigned char *der, unsigned len,
                          struc...`
- Defined: `net/tls_x509.c:451`
- Doc: return 1; } return 0;   /* SAN present and nothing matched: fail closed } if (leaf->subject.cn_len) { return host_match_

### pubkey_equal `static int pubkey_equal(const struct tls_pubkey *a, const struct tls_pubkey *b)`
- Defined: `net/tls_x509.c:468`
- Doc: Trust anchors are matched by public key, not by self-signature: a presented root is often a cross-signed copy (signed by

### cert_verify_signature `static int cert_verify_signature(const struct x509_cert *cert,
                                 c...`
- Defined: `net/tls_x509.c:479`
- Doc: signature-verified: an attacker cannot present a top cert carrying an embedded root's public key unless the chain below 

### tls_x509_verify_chain `int tls_x509_verify_chain(const unsigned char *chain, unsigned chain_len,
                       ...`
- Defined: `net/tls_x509.c:520`

## progs/asm/aes.s

### aes_rk
- Defined: `progs/asm/aes.s:3`

### aes_sb
- Defined: `progs/asm/aes.s:7`

### aes_rc
- Defined: `progs/asm/aes.s:11`

### aes_st
- Defined: `progs/asm/aes.s:15`

### aes_iv
- Defined: `progs/asm/aes.s:19`

### aes_read_all
- Defined: `progs/asm/aes.s:23`

### aes_write_all
- Defined: `progs/asm/aes.s:240`

### aes_has
- Defined: `progs/asm/aes.s:349`

### hex_val
- Defined: `progs/asm/aes.s:502`

### aes_parse_hex
- Defined: `progs/asm/aes.s:624`

### aes_gf_mul
- Defined: `progs/asm/aes.s:787`

### aes_xtime
- Defined: `progs/asm/aes.s:888`

### aes_rotl8
- Defined: `progs/asm/aes.s:937`

### aes_init_tables
- Defined: `progs/asm/aes.s:974`

### aes_key_expand
- Defined: `progs/asm/aes.s:1203`

### aes_add_round_key
- Defined: `progs/asm/aes.s:1652`

### aes_sub_bytes
- Defined: `progs/asm/aes.s:1727`

### aes_shift_rows
- Defined: `progs/asm/aes.s:1780`

### aes_mix_columns
- Defined: `progs/asm/aes.s:1999`

### aes_cipher
- Defined: `progs/asm/aes.s:2472`

### aes_iv_increment
- Defined: `progs/asm/aes.s:2571`

### aes_ctr_crypt
- Defined: `progs/asm/aes.s:2654`

### aes_hdr_put
- Defined: `progs/asm/aes.s:2797`

### aes_hdr_get
- Defined: `progs/asm/aes.s:2912`

### aes_tool_name
- Defined: `progs/asm/aes.s:3065`

### aes_run
- Defined: `progs/asm/aes.s:3083`

### main
- Defined: `progs/asm/aes.s:3816`

### _start
- Defined: `progs/asm/aes.s:4124`

## progs/asm/cp.s

### main
- Defined: `progs/asm/cp.s:3`

### _start
- Defined: `progs/asm/cp.s:328`

## progs/asm/fib.s

### fib
- Defined: `progs/asm/fib.s:3`

### main
- Defined: `progs/asm/fib.s:61`

### _start
- Defined: `progs/asm/fib.s:82`

## progs/asm/freedom.s

### f_host
- Defined: `progs/asm/freedom.s:3`

### f_path
- Defined: `progs/asm/freedom.s:7`

### f_port
- Defined: `progs/asm/freedom.s:11`

### f_secure
- Defined: `progs/asm/freedom.s:15`

### f_loc
- Defined: `progs/asm/freedom.s:19`

### f_redir
- Defined: `progs/asm/freedom.s:23`

### f_status
- Defined: `progs/asm/freedom.s:27`

### f_clen
- Defined: `progs/asm/freedom.s:31`

### f_has_clen
- Defined: `progs/asm/freedom.s:35`

### f_chunked
- Defined: `progs/asm/freedom.s:39`

### f_hdr
- Defined: `progs/asm/freedom.s:43`

### f_hlen
- Defined: `progs/asm/freedom.s:47`

### f_tag
- Defined: `progs/asm/freedom.s:51`

### f_suppress
- Defined: `progs/asm/freedom.s:55`

### f_comment
- Defined: `progs/asm/freedom.s:59`

### f_cmdash
- Defined: `progs/asm/freedom.s:63`

### f_tagn
- Defined: `progs/asm/freedom.s:67`

### f_tagnlen
- Defined: `progs/asm/freedom.s:71`

### f_ent
- Defined: `progs/asm/freedom.s:75`

### f_entlen
- Defined: `progs/asm/freedom.s:79`

### f_ws
- Defined: `progs/asm/freedom.s:83`

### f_utbuf
- Defined: `progs/asm/freedom.s:87`

### f_utlen
- Defined: `progs/asm/freedom.s:91`

### f_utrem
- Defined: `progs/asm/freedom.s:95`

### f_attr_on
- Defined: `progs/asm/freedom.s:99`

### f_waitq
- Defined: `progs/asm/freedom.s:103`

### f_inval
- Defined: `progs/asm/freedom.s:107`

### f_inval2
- Defined: `progs/asm/freedom.s:111`

### f_attr
- Defined: `progs/asm/freedom.s:115`

### f_attrlen
- Defined: `progs/asm/freedom.s:119`

### f_val
- Defined: `progs/asm/freedom.s:123`

### f_vallen
- Defined: `progs/asm/freedom.s:127`

### f_id
- Defined: `progs/asm/freedom.s:131`

### f_idlen
- Defined: `progs/asm/freedom.s:135`

### f_cls
- Defined: `progs/asm/freedom.s:139`

### f_clslen
- Defined: `progs/asm/freedom.s:143`

### f_href
- Defined: `progs/asm/freedom.s:147`

### f_hreflen
- Defined: `progs/asm/freedom.s:151`

### f_rel_ss
- Defined: `progs/asm/freedom.s:155`

### f_styleattr
- Defined: `progs/asm/freedom.s:159`

### f_stylelen
- Defined: `progs/asm/freedom.s:163`

### f_dump_css
- Defined: `progs/asm/freedom.s:167`

### f_dump_dom
- Defined: `progs/asm/freedom.s:171`

### f_mode
- Defined: `progs/asm/freedom.s:175`

### f_rawcap
- Defined: `progs/asm/freedom.s:179`

### f_depth
- Defined: `progs/asm/freedom.s:183`

### f_dom
- Defined: `progs/asm/freedom.s:187`

### f_domlen
- Defined: `progs/asm/freedom.s:191`

### f_css
- Defined: `progs/asm/freedom.s:195`

### f_csslen
- Defined: `progs/asm/freedom.s:199`

### f_linkhost
- Defined: `progs/asm/freedom.s:203`

### f_linkpath
- Defined: `progs/asm/freedom.s:207`

### f_linkn
- Defined: `progs/asm/freedom.s:211`

### f_cstage
- Defined: `progs/asm/freedom.s:215`

### f_csize
- Defined: `progs/asm/freedom.s:219`

### f_crem
- Defined: `progs/asm/freedom.s:223`

### f_bdone
- Defined: `progs/asm/freedom.s:227`

### atoi
- Defined: `progs/asm/freedom.s:231`

### append
- Defined: `progs/asm/freedom.s:317`

### ci_lower
- Defined: `progs/asm/freedom.s:402`

### ci_starts
- Defined: `progs/asm/freedom.s:451`

### ci_eq
- Defined: `progs/asm/freedom.s:524`

### ci_index
- Defined: `progs/asm/freedom.s:621`

### looks_like_url
- Defined: `progs/asm/freedom.s:681`

### has_scheme
- Defined: `progs/asm/freedom.s:755`

### make_search
- Defined: `progs/asm/freedom.s:1030`

### split_url
- Defined: `progs/asm/freedom.s:1266`

### resolve_redirect
- Defined: `progs/asm/freedom.s:1781`

### put_ws
- Defined: `progs/asm/freedom.s:2306`

### put_utf
- Defined: `progs/asm/freedom.s:2352`

### put_text
- Defined: `progs/asm/freedom.s:2888`

### put_entity
- Defined: `progs/asm/freedom.s:2991`

### css_append
- Defined: `progs/asm/freedom.s:3828`

### css_line
- Defined: `progs/asm/freedom.s:3899`

### dom_append
- Defined: `progs/asm/freedom.s:3958`

### dom_space
- Defined: `progs/asm/freedom.s:4029`

### dom_nl
- Defined: `progs/asm/freedom.s:4063`

### record_attr
- Defined: `progs/asm/freedom.s:4097`

### is_void_tag
- Defined: `progs/asm/freedom.s:4435`

### classify_tag
- Defined: `progs/asm/freedom.s:4757`

### body_byte
- Defined: `progs/asm/freedom.s:5994`

### head_line
- Defined: `progs/asm/freedom.s:7239`

### parse_head
- Defined: `progs/asm/freedom.s:7500`

### recv_body
- Defined: `progs/asm/freedom.s:7717`

### send_all
- Defined: `progs/asm/freedom.s:7778`

### fetch
- Defined: `progs/asm/freedom.s:7853`

### fetch_css
- Defined: `progs/asm/freedom.s:9331`

### print_css_dump
- Defined: `progs/asm/freedom.s:10143`

### print_dom_dump
- Defined: `progs/asm/freedom.s:10243`

### main
- Defined: `progs/asm/freedom.s:10322`

### _start
- Defined: `progs/asm/freedom.s:11800`

## progs/asm/http.s

### atoi
- Defined: `progs/asm/http.s:3`

### main
- Defined: `progs/asm/http.s:89`

### _start
- Defined: `progs/asm/http.s:698`

## progs/asm/json.s

### js_key
- Defined: `progs/asm/json.s:3`

### js_str
- Defined: `progs/asm/json.s:7`

### js_type
- Defined: `progs/asm/json.s:11`

### js_num
- Defined: `progs/asm/json.s:15`

### js_first
- Defined: `progs/asm/json.s:19`

### js_count
- Defined: `progs/asm/json.s:23`

### js_next
- Defined: `progs/asm/json.s:27`

### js_n
- Defined: `progs/asm/json.s:31`

### js_pool
- Defined: `progs/asm/json.s:35`

### js_plen
- Defined: `progs/asm/json.s:39`

### js_src
- Defined: `progs/asm/json.s:43`

### js_pos
- Defined: `progs/asm/json.s:47`

### js_len
- Defined: `progs/asm/json.s:51`

### js_err
- Defined: `progs/asm/json.s:55`

### js_read_all
- Defined: `progs/asm/json.s:59`

### js_new
- Defined: `progs/asm/json.s:276`

### js_skip_ws
- Defined: `progs/asm/json.s:308`

### js_peek
- Defined: `progs/asm/json.s:399`

### js_parse_string
- Defined: `progs/asm/json.s:439`

### js_parse_number
- Defined: `progs/asm/json.s:853`

### js_key_match
- Defined: `progs/asm/json.s:949`

### js_parse_object
- Defined: `progs/asm/json.s:986`

### js_parse_array
- Defined: `progs/asm/json.s:1338`

### js_parse_value
- Defined: `progs/asm/json.s:1597`

### js_indent
- Defined: `progs/asm/json.s:2484`

### js_print_str
- Defined: `progs/asm/json.s:2527`

### js_print_value
- Defined: `progs/asm/json.s:2750`

### js_find_member
- Defined: `progs/asm/json.s:3319`

### js_array_at
- Defined: `progs/asm/json.s:3398`

### js_query
- Defined: `progs/asm/json.s:3467`

### main
- Defined: `progs/asm/json.s:3781`

### _start
- Defined: `progs/asm/json.s:4185`

## progs/asm/ldhello.s

### main
- Defined: `progs/asm/ldhello.s:3`

### _start
- Defined: `progs/asm/ldhello.s:14`

## progs/asm/lz4.s

### lz4_has
- Defined: `progs/asm/lz4.s:3`

### lz4_read_all
- Defined: `progs/asm/lz4.s:156`

### lz4_write_all
- Defined: `progs/asm/lz4.s:373`

### lz4_compress_file
- Defined: `progs/asm/lz4.s:482`

### lz4_decompress_file
- Defined: `progs/asm/lz4.s:800`

### main
- Defined: `progs/asm/lz4.s:1244`

### _start
- Defined: `progs/asm/lz4.s:1555`

## progs/asm/lzss.s

### lz_win
- Defined: `progs/asm/lzss.s:3`

### lz_src
- Defined: `progs/asm/lzss.s:7`

### lz_srclen
- Defined: `progs/asm/lzss.s:11`

### lz_srcpos
- Defined: `progs/asm/lzss.s:15`

### lz_dst
- Defined: `progs/asm/lzss.s:19`

### lz_dstcap
- Defined: `progs/asm/lzss.s:23`

### lz_dstlen
- Defined: `progs/asm/lzss.s:27`

### lz_err
- Defined: `progs/asm/lzss.s:31`

### lz_buf
- Defined: `progs/asm/lzss.s:35`

### lz_mask
- Defined: `progs/asm/lzss.s:39`

### lz_in_getc
- Defined: `progs/asm/lzss.s:43`

### lz_out_put
- Defined: `progs/asm/lzss.s:79`

### lz_putbit1
- Defined: `progs/asm/lzss.s:116`

### lz_putbit0
- Defined: `progs/asm/lzss.s:174`

### lz_flush_bits
- Defined: `progs/asm/lzss.s:223`

### lz_out_literal
- Defined: `progs/asm/lzss.s:251`

### lz_out_pair
- Defined: `progs/asm/lzss.s:321`

### lz_encode
- Defined: `progs/asm/lzss.s:447`

### lz_getbit
- Defined: `progs/asm/lzss.s:1011`

### lz_decode
- Defined: `progs/asm/lzss.s:1131`

### lz_hdr_put
- Defined: `progs/asm/lzss.s:1474`

### lz_hdr_get
- Defined: `progs/asm/lzss.s:1589`

### lz_has
- Defined: `progs/asm/lzss.s:1742`

### lz_read_all
- Defined: `progs/asm/lzss.s:1895`

### lz_write_all
- Defined: `progs/asm/lzss.s:2112`

### lz_compress
- Defined: `progs/asm/lzss.s:2221`

### lz_decompress
- Defined: `progs/asm/lzss.s:2597`

### main
- Defined: `progs/asm/lzss.s:3155`

### _start
- Defined: `progs/asm/lzss.s:3474`

## progs/asm/w1.s

### main
- Defined: `progs/asm/w1.s:3`

### _start
- Defined: `progs/asm/w1.s:37`

## progs/doomgeneric/am_map.c

### AM_getIslope `void
AM_getIslope
( mline_t*	ml,
  islope_t*	is )`
- Defined: `progs/doomgeneric/am_map.c:273`
- Doc: Calculates the slope and slope according to the x-axis of a line segment in map coordinates (with the upright y-axis n' 

### AM_activateNewScale `void AM_activateNewScale(void)`
- Defined: `progs/doomgeneric/am_map.c:293`

### AM_saveScaleAndLoc `void AM_saveScaleAndLoc(void)`
- Defined: `progs/doomgeneric/am_map.c:308`

### AM_restoreScaleAndLoc `void AM_restoreScaleAndLoc(void)`
- Defined: `progs/doomgeneric/am_map.c:319`

### AM_addMark `void AM_addMark(void)`
- Defined: `progs/doomgeneric/am_map.c:343`
- Doc: adds a marker at the current location

### AM_findMinMaxBoundaries `void AM_findMinMaxBoundaries(void)`
- Defined: `progs/doomgeneric/am_map.c:355`
- Doc: Determines bounding box of all vertices, sets global variables controlling zoom range.

### AM_changeWindowLoc `void AM_changeWindowLoc(void)`
- Defined: `progs/doomgeneric/am_map.c:395`

### AM_initVariables `void AM_initVariables(void)`
- Defined: `progs/doomgeneric/am_map.c:424`

### AM_loadPics `void AM_loadPics(void)`
- Defined: `progs/doomgeneric/am_map.c:480`

### AM_unloadPics `void AM_unloadPics(void)`
- Defined: `progs/doomgeneric/am_map.c:492`

### AM_clearMarks `void AM_clearMarks(void)`
- Defined: `progs/doomgeneric/am_map.c:504`

### AM_LevelInit `void AM_LevelInit(void)`
- Defined: `progs/doomgeneric/am_map.c:518`
- Doc: should be called at the start of every level right now, i figure it out myself

### AM_Stop `void AM_Stop (void)`
- Defined: `progs/doomgeneric/am_map.c:541`

### AM_Start `void AM_Start (void)`
- Defined: `progs/doomgeneric/am_map.c:554`

### AM_minOutWindowScale `void AM_minOutWindowScale(void)`
- Defined: `progs/doomgeneric/am_map.c:573`
- Doc: set the window scale to the maximum size

### AM_maxOutWindowScale `void AM_maxOutWindowScale(void)`
- Defined: `progs/doomgeneric/am_map.c:583`
- Doc: set the window scale to the minimum size

### AM_Responder `boolean
AM_Responder
( event_t*	ev )`
- Defined: `progs/doomgeneric/am_map.c:594`
- Doc: Handle events (user inputs) in automap mode

### AM_changeWindowScale `void AM_changeWindowScale(void)`
- Defined: `progs/doomgeneric/am_map.c:742`
- Doc: Zooming

### AM_doFollowPlayer `void AM_doFollowPlayer(void)`
- Defined: `progs/doomgeneric/am_map.c:761`

### AM_updateLightLev `void AM_updateLightLev(void)`
- Defined: `progs/doomgeneric/am_map.c:785`

### AM_Ticker `void AM_Ticker (void)`
- Defined: `progs/doomgeneric/am_map.c:806`
- Doc: Updates on Game Tick

### AM_clearFB `void AM_clearFB(int color)`
- Defined: `progs/doomgeneric/am_map.c:834`
- Doc: Clear automap frame buffer.

### AM_clipMline `boolean
AM_clipMline
( mline_t*	ml,
  fline_t*	fl )`
- Defined: `progs/doomgeneric/am_map.c:847`
- Doc: Automap clipping of lines.  Based on Cohen-Sutherland clipping algorithm but with a slightly faster reject and precalcul

### AM_drawFline `void
AM_drawFline
( fline_t*	fl,
  int		color )`
- Defined: `progs/doomgeneric/am_map.c:983`
- Doc: Classic Bresenham w/ whatever optimizations needed for speed

### AM_drawMline `void
AM_drawMline
( mline_t*	ml,
  int		color )`
- Defined: `progs/doomgeneric/am_map.c:1061`
- Doc: Clip lines, draw visible part sof lines.

### AM_drawGrid `void AM_drawGrid(int color)`
- Defined: `progs/doomgeneric/am_map.c:1077`
- Doc: Draws flat (floor/ceiling tile) aligned grid lines.

### AM_drawWalls `void AM_drawWalls(void)`
- Defined: `progs/doomgeneric/am_map.c:1123`
- Doc: Determines visible lines, draws them. This is LineDef based, not LineSeg based.

### AM_rotate `void
AM_rotate
( fixed_t*	x,
  fixed_t*	y,
  angle_t	a )`
- Defined: `progs/doomgeneric/am_map.c:1178`
- Doc: Rotation in 2D. Used to rotate player arrow line character.

### AM_drawLineCharacter `void
AM_drawLineCharacter
( mline_t*	lineguy,
  int		lineguylines,
  fixed_t	scale,
  angle_t	ang...`
- Defined: `progs/doomgeneric/am_map.c:1196`

### AM_drawPlayers `void AM_drawPlayers(void)`
- Defined: `progs/doomgeneric/am_map.c:1245`

### AM_drawThings `void
AM_drawThings
( int	colors,
  int 	colorrange)`
- Defined: `progs/doomgeneric/am_map.c:1289`

### AM_drawMarks `void AM_drawMarks(void)`
- Defined: `progs/doomgeneric/am_map.c:1310`

### AM_drawCrosshair `void AM_drawCrosshair(int color)`
- Defined: `progs/doomgeneric/am_map.c:1331`

### AM_Drawer `void AM_Drawer (void)`
- Defined: `progs/doomgeneric/am_map.c:1337`

## progs/doomgeneric/d_event.c

### D_PostEvent `void D_PostEvent (event_t* ev)`
- Defined: `progs/doomgeneric/d_event.c:35`
- Doc: D_PostEvent Called by the I/O functions when input is detected

### D_PopEvent `event_t *D_PopEvent(void)`
- Defined: `progs/doomgeneric/d_event.c:42`
- Doc: Read an event from the queue.

## progs/doomgeneric/d_iwad.c

### AddIWADDir `static void AddIWADDir(char *dir)`
- Defined: `progs/doomgeneric/d_iwad.c:63`

### GetRegistryString `static char *GetRegistryString(registry_value_t *reg_val)`
- Defined: `progs/doomgeneric/d_iwad.c:191`

### CheckUninstallStrings `static void CheckUninstallStrings(void)`
- Defined: `progs/doomgeneric/d_iwad.c:235`
- Doc: Check for the uninstall strings from the CD versions

### CheckCollectorsEdition `static void CheckCollectorsEdition(void)`
- Defined: `progs/doomgeneric/d_iwad.c:269`
- Doc: Check for Doom: Collector's Edition

### CheckSteamEdition `static void CheckSteamEdition(void)`
- Defined: `progs/doomgeneric/d_iwad.c:296`
- Doc: Check for Doom downloaded via Steam

### CheckSteamGUSPatches `static void CheckSteamGUSPatches(void)`
- Defined: `progs/doomgeneric/d_iwad.c:323`
- Doc: The BFG edition ships with a full set of GUS patches. If we find them, we can autoconfigure to use them.

### CheckDOSDefaults `static void CheckDOSDefaults(void)`
- Defined: `progs/doomgeneric/d_iwad.c:363`
- Doc: Default install directories for DOS Doom

### DirIsFile `static boolean DirIsFile(char *path, char *filename)`
- Defined: `progs/doomgeneric/d_iwad.c:390`
- Doc: Returns true if the specified path is a path to a file of the specified name.

### CheckDirectoryHasIWAD `static char *CheckDirectoryHasIWAD(char *dir, char *iwadname)`
- Defined: `progs/doomgeneric/d_iwad.c:407`
- Doc: Check if the specified directory contains the specified IWAD file, returning the full path to the IWAD if found, or NULL

### SearchDirectoryForIWAD `static char *SearchDirectoryForIWAD(char *dir, int mask, GameMission_t *mission)`
- Defined: `progs/doomgeneric/d_iwad.c:448`
- Doc: Search a directory to try to find an IWAD Returns the location of the IWAD if found, otherwise NULL.

### IdentifyIWADByName `static GameMission_t IdentifyIWADByName(char *name, int mask)`
- Defined: `progs/doomgeneric/d_iwad.c:476`
- Doc: When given an IWAD with the '-iwad' parameter, attempt to identify it by its name.

### AddDoomWadPath `static void AddDoomWadPath(void)`
- Defined: `progs/doomgeneric/d_iwad.c:517`
- Doc: if ORIGCODE  Add directories from the list in the DOOMWADPATH environment variable.

### BuildIWADDirList `static void BuildIWADDirList(void)`
- Defined: `progs/doomgeneric/d_iwad.c:568`
- Doc: Build a list of IWAD files

### D_FindWADByName `char *D_FindWADByName(char *name)`
- Defined: `progs/doomgeneric/d_iwad.c:629`
- Doc: Searches WAD search paths for an WAD with a specific filename.

### D_TryFindWADByName `char *D_TryFindWADByName(char *filename)`
- Defined: `progs/doomgeneric/d_iwad.c:680`
- Doc: D_TryWADByName  Searches for a WAD by its filename, or passes through the filename if not found.

### D_FindIWAD `char *D_FindIWAD(int mask, GameMission_t *mission)`
- Defined: `progs/doomgeneric/d_iwad.c:703`
- Doc: FindIWAD Checks availability of IWAD files by name, to determine whether registered/commercial features should be execut

### D_FindAllIWADs `const iwad_t **D_FindAllIWADs(int mask)`
- Defined: `progs/doomgeneric/d_iwad.c:756`
- Doc: Find all IWADs in the IWAD search path matching the given mask.

### D_SaveGameIWADName `char *D_SaveGameIWADName(GameMission_t gamemission)`
- Defined: `progs/doomgeneric/d_iwad.c:795`
- Doc: Get the IWAD name used for savegames.

### D_SuggestIWADName `char *D_SuggestIWADName(GameMission_t mission, GameMode_t mode)`
- Defined: `progs/doomgeneric/d_iwad.c:819`

### D_SuggestGameName `char *D_SuggestGameName(GameMission_t mission, GameMode_t mode)`
- Defined: `progs/doomgeneric/d_iwad.c:834`

## progs/doomgeneric/d_loop.c

### GetAdjustedTime `static int GetAdjustedTime(void)`
- Defined: `progs/doomgeneric/d_loop.c:118`
- Doc: 35 fps clock adjusted by offsetms milliseconds

### BuildNewTic `static boolean BuildNewTic(void)`
- Defined: `progs/doomgeneric/d_loop.c:135`

### NetUpdate `void NetUpdate (void)`
- Defined: `progs/doomgeneric/d_loop.c:202`

### D_Disconnected `static void D_Disconnected(void)`
- Defined: `progs/doomgeneric/d_loop.c:251`

### D_ReceiveTic `void D_ReceiveTic(ticcmd_t *ticcmds, boolean *players_mask)`
- Defined: `progs/doomgeneric/d_loop.c:270`
- Doc: Invoked by the network engine when a complete set of ticcmds is available.

### D_StartGameLoop `void D_StartGameLoop(void)`
- Defined: `progs/doomgeneric/d_loop.c:304`
- Doc: Start game loop  Called after the screen is set but before the game starts running.

### BlockUntilStart `static void BlockUntilStart(net_gamesettings_t *settings,
                            netgame_sta...`
- Defined: `progs/doomgeneric/d_loop.c:314`
- Doc: if ORIGCODE  Block until the game start message is received from the server.

### D_StartNetGame `void D_StartNetGame(net_gamesettings_t *settings,
                    netgame_startup_callback_t ...`
- Defined: `progs/doomgeneric/d_loop.c:339`
- Doc: endif

### D_InitNetGame `boolean D_InitNetGame(net_connect_data_t *connect_data)`
- Defined: `progs/doomgeneric/d_loop.c:451`

### D_QuitNetGame `void D_QuitNetGame (void)`
- Defined: `progs/doomgeneric/d_loop.c:560`
- Doc: D_QuitNetGame Called before quitting to leave a net game without hanging the other players

### GetLowTic `static int GetLowTic(void)`
- Defined: `progs/doomgeneric/d_loop.c:567`

### OldNetSync `static void OldNetSync(void)`
- Defined: `progs/doomgeneric/d_loop.c:590`

### PlayersInGame `static boolean PlayersInGame(void)`
- Defined: `progs/doomgeneric/d_loop.c:641`
- Doc: Returns true if there are players in the game:

### TicdupSquash `static void TicdupSquash(ticcmd_set_t *set)`
- Defined: `progs/doomgeneric/d_loop.c:671`
- Doc: When using ticdup, certain values must be cleared out when running the duplicate ticcmds.

### SinglePlayerClear `static void SinglePlayerClear(ticcmd_set_t *set)`
- Defined: `progs/doomgeneric/d_loop.c:688`
- Doc: When running in single player mode, clear all the ingame[] array except the local player.

### TryRunTics `void TryRunTics (void)`
- Defined: `progs/doomgeneric/d_loop.c:705`
- Doc: TryRunTics

### D_RegisterLoopCallbacks `void D_RegisterLoopCallbacks(loop_interface_t *i)`
- Defined: `progs/doomgeneric/d_loop.c:821`

## progs/doomgeneric/d_main.c

### D_ProcessEvents `void D_ProcessEvents (void)`
- Defined: `progs/doomgeneric/d_main.c:139`
- Doc: D_ProcessEvents Send all the events of the given timestamp down the responder chain

### D_Display `void D_Display (void)`
- Defined: `progs/doomgeneric/d_main.c:168`

### D_BindVariables `void D_BindVariables(void)`
- Defined: `progs/doomgeneric/d_main.c:334`
- Doc: Add configuration file variable bindings.

### D_GrabMouseCallback `boolean D_GrabMouseCallback(void)`
- Defined: `progs/doomgeneric/d_main.c:387`
- Doc: D_GrabMouseCallback  Called to determine whether to grab the mouse pointer

### D_DoomLoop `void D_DoomLoop (void)`
- Defined: `progs/doomgeneric/d_main.c:408`
- Doc: D_DoomLoop

### D_PageTicker `void D_PageTicker (void)`
- Defined: `progs/doomgeneric/d_main.c:490`
- Doc: D_PageTicker Handles timing for warped projection

### D_PageDrawer `void D_PageDrawer (void)`
- Defined: `progs/doomgeneric/d_main.c:501`
- Doc: D_PageDrawer

### D_AdvanceDemo `void D_AdvanceDemo (void)`
- Defined: `progs/doomgeneric/d_main.c:511`
- Doc: D_AdvanceDemo Called after each demo or intro demosequence finishes

### D_DoAdvanceDemo `void D_DoAdvanceDemo (void)`
- Defined: `progs/doomgeneric/d_main.c:521`
- Doc: This cycles through the demo sequences. FIXME - version dependend demo numbers?

### D_StartTitle `void D_StartTitle (void)`
- Defined: `progs/doomgeneric/d_main.c:609`
- Doc: D_StartTitle

### GetGameName `static char *GetGameName(char *gamename)`
- Defined: `progs/doomgeneric/d_main.c:657`
- Doc: Get game name: if the startup banner has been replaced, use that. Otherwise, use the name given

### SetMissionForPackName `static void SetMissionForPackName(char *pack_name)`
- Defined: `progs/doomgeneric/d_main.c:700`

### D_IdentifyVersion `void D_IdentifyVersion(void)`
- Defined: `progs/doomgeneric/d_main.c:736`
- Doc: Find out what version of Doom is playing.

### D_SetGameDescription `void D_SetGameDescription(void)`
- Defined: `progs/doomgeneric/d_main.c:819`
- Doc: Set the gamedescription string

### D_AddFile `static boolean D_AddFile(char *filename)`
- Defined: `progs/doomgeneric/d_main.c:882`

### PrintDehackedBanners `void PrintDehackedBanners(void)`
- Defined: `progs/doomgeneric/d_main.c:917`
- Doc: Prints a message only if it has been modified by dehacked.

### InitGameVersion `static void InitGameVersion(void)`
- Defined: `progs/doomgeneric/d_main.c:962`
- Doc: Initialize the game version

### PrintGameVersion `void PrintGameVersion(void)`
- Defined: `progs/doomgeneric/d_main.c:1064`

### D_Endoom `static void D_Endoom(void)`
- Defined: `progs/doomgeneric/d_main.c:1081`
- Doc: Function called at exit to display the ENDOOM screen

### LoadIwadDeh `static void LoadIwadDeh(void)`
- Defined: `progs/doomgeneric/d_main.c:1105`
- Doc: if ORIGCODE Load dehacked patches needed for certain IWADs.

### D_DoomMain `void D_DoomMain (void)`
- Defined: `progs/doomgeneric/d_main.c:1178`
- Doc: D_DoomMain

## progs/doomgeneric/d_mode.c

### D_ValidGameMode `boolean D_ValidGameMode(GameMission_t mission, GameMode_t mode)`
- Defined: `progs/doomgeneric/d_mode.c:49`
- Doc: Check that a gamemode+gamemission received over the network is valid.

### D_ValidEpisodeMap `boolean D_ValidEpisodeMap(GameMission_t mission, GameMode_t mode,
                          int e...`
- Defined: `progs/doomgeneric/d_mode.c:64`

### D_GetNumEpisodes `int D_GetNumEpisodes(GameMission_t mission, GameMode_t mode)`
- Defined: `progs/doomgeneric/d_mode.c:102`
- Doc: Get the number of valid episodes for the specified mission/mode.

### D_ValidGameVersion `boolean D_ValidGameVersion(GameMission_t mission, GameVersion_t version)`
- Defined: `progs/doomgeneric/d_mode.c:134`

### D_IsEpisodeMap `boolean D_IsEpisodeMap(GameMission_t mission)`
- Defined: `progs/doomgeneric/d_mode.c:160`
- Doc: Does this mission type use ExMy form, rather than MAPxy form?

### D_GameMissionString `char *D_GameMissionString(GameMission_t mission)`
- Defined: `progs/doomgeneric/d_mode.c:181`

## progs/doomgeneric/d_net.c

### PlayerQuitGame `static void PlayerQuitGame(player_t *player)`
- Defined: `progs/doomgeneric/d_net.c:44`
- Doc: Called when a player leaves the game

### RunTic `static void RunTic(ticcmd_t *cmds, boolean *ingame)`
- Defined: `progs/doomgeneric/d_net.c:70`

### LoadGameSettings `static void LoadGameSettings(net_gamesettings_t *settings)`
- Defined: `progs/doomgeneric/d_net.c:107`
- Doc: Load game settings from the specified structure and set global variables.

### SaveGameSettings `static void SaveGameSettings(net_gamesettings_t *settings)`
- Defined: `progs/doomgeneric/d_net.c:138`
- Doc: Save the game settings from global variables to the specified game settings structure.

### InitConnectData `static void InitConnectData(net_connect_data_t *connect_data)`
- Defined: `progs/doomgeneric/d_net.c:158`

### D_ConnectNetGame `void D_ConnectNetGame(void)`
- Defined: `progs/doomgeneric/d_net.c:214`

### D_CheckNetGame `void D_CheckNetGame (void)`
- Defined: `progs/doomgeneric/d_net.c:240`
- Doc: D_CheckNetGame Works out player numbers among the net participants

## progs/doomgeneric/doomgeneric.c

### dg_Create `void dg_Create()`
- Defined: `progs/doomgeneric/doomgeneric.c:4`

## progs/doomgeneric/doomgeneric_minios.c

### mini_parse_autoframes `static void mini_parse_autoframes(int argc, char **argv)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:22`

### sys_time_ms `static long sys_time_ms(void)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:35`
- Doc: static int mini_frames; static void mini_parse_autoframes(int argc, char **argv) { int i; mini_autoframes = 0; for (i = 

### sys_kbd `static long sys_kbd(void)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:41`

### sys_palette `static long sys_palette(const unsigned char *pal)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:46`

### sys_kbd_raw `static long sys_kbd_raw(int on)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:51`

### sys_vga_mode `static long sys_vga_mode(int on)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:56`

### sys_doom_frame `static long sys_doom_frame(void)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:61`

### load_vga_palette `static void load_vga_palette(void)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:84`

### scancode_to_doom `static unsigned char scancode_to_doom(unsigned char raw)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:97`
- Doc: volatile int minios_palette_dirty = 1; static void load_vga_palette(void) { uint8_t dac[768]; int i; for (i = 0; i < 256

### kbd_enqueue `static void kbd_enqueue(unsigned char doom_key, int pressed)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:156`

### kbd_poll `static void kbd_poll(void)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:163`

### DG_Init `void DG_Init(void)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:206`

### DG_DrawFrame `void DG_DrawFrame(void)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:214`

### DG_SleepMs `void DG_SleepMs(uint32_t ms)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:244`

### DG_GetTicksMs `uint32_t DG_GetTicksMs(void)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:250`

### DG_GetKey `int DG_GetKey(int *pressed, unsigned char *key)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:254`

### DG_SetWindowTitle `void DG_SetWindowTitle(const char *title)`
- Defined: `progs/doomgeneric/doomgeneric_minios.c:265`

## progs/doomgeneric/doomgeneric_sdl.c

### convertToDoomKey `static unsigned char convertToDoomKey(unsigned int key)`
- Defined: `progs/doomgeneric/doomgeneric_sdl.c:22`

### addKeyToQueue `static void addKeyToQueue(int pressed, unsigned int keyCode)`
- Defined: `progs/doomgeneric/doomgeneric_sdl.c:62`

### handleKeyInput `static void handleKeyInput()`
- Defined: `progs/doomgeneric/doomgeneric_sdl.c:72`

### DG_Init `void DG_Init()`
- Defined: `progs/doomgeneric/doomgeneric_sdl.c:91`

### DG_DrawFrame `void DG_DrawFrame()`
- Defined: `progs/doomgeneric/doomgeneric_sdl.c:111`

### DG_SleepMs `void DG_SleepMs(uint32_t ms)`
- Defined: `progs/doomgeneric/doomgeneric_sdl.c:122`

### DG_GetTicksMs `uint32_t DG_GetTicksMs()`
- Defined: `progs/doomgeneric/doomgeneric_sdl.c:127`

### DG_GetKey `int DG_GetKey(int* pressed, unsigned char* doomKey)`
- Defined: `progs/doomgeneric/doomgeneric_sdl.c:132`

### DG_SetWindowTitle `void DG_SetWindowTitle(const char * title)`
- Defined: `progs/doomgeneric/doomgeneric_sdl.c:151`

## progs/doomgeneric/doomgeneric_soso.c

### convertToDoomKey `static unsigned char convertToDoomKey(unsigned char scancode)`
- Defined: `progs/doomgeneric/doomgeneric_soso.c:42`

### addKeyToQueue `static void addKeyToQueue(int pressed, unsigned char keyCode)`
- Defined: `progs/doomgeneric/doomgeneric_soso.c:91`

### disableRawMode `void disableRawMode()`
- Defined: `progs/doomgeneric/doomgeneric_soso.c:107`

### enableRawMode `void enableRawMode()`
- Defined: `progs/doomgeneric/doomgeneric_soso.c:113`

### DG_Init `void DG_Init()`
- Defined: `progs/doomgeneric/doomgeneric_soso.c:123`

### handleKeyInput `static void handleKeyInput()`
- Defined: `progs/doomgeneric/doomgeneric_soso.c:185`

### DG_DrawFrame `void DG_DrawFrame()`
- Defined: `progs/doomgeneric/doomgeneric_soso.c:213`

### DG_SleepMs `void DG_SleepMs(uint32_t ms)`
- Defined: `progs/doomgeneric/doomgeneric_soso.c:226`

### DG_GetTicksMs `uint32_t DG_GetTicksMs()`
- Defined: `progs/doomgeneric/doomgeneric_soso.c:231`

### DG_GetKey `int DG_GetKey(int* pressed, unsigned char* doomKey)`
- Defined: `progs/doomgeneric/doomgeneric_soso.c:236`

### DG_SetWindowTitle `void DG_SetWindowTitle(const char * title)`
- Defined: `progs/doomgeneric/doomgeneric_soso.c:257`

## progs/doomgeneric/doomgeneric_sosox.c

### convert_to_doom_key `static unsigned char convert_to_doom_key(unsigned char scancode)`
- Defined: `progs/doomgeneric/doomgeneric_sosox.c:37`

### add_key_to_queue `static void add_key_to_queue(int pressed, unsigned char key_code)`
- Defined: `progs/doomgeneric/doomgeneric_sosox.c:87`

### disable_raw_mode `void disable_raw_mode()`
- Defined: `progs/doomgeneric/doomgeneric_sosox.c:101`

### enable_raw_mode `void enable_raw_mode()`
- Defined: `progs/doomgeneric/doomgeneric_sosox.c:106`

### DG_Init `void DG_Init()`
- Defined: `progs/doomgeneric/doomgeneric_sosox.c:116`

### handle_key_input `static void handle_key_input()`
- Defined: `progs/doomgeneric/doomgeneric_sosox.c:158`

### DG_DrawFrame `void DG_DrawFrame()`
- Defined: `progs/doomgeneric/doomgeneric_sosox.c:186`

### DG_SleepMs `void DG_SleepMs(uint32_t ms)`
- Defined: `progs/doomgeneric/doomgeneric_sosox.c:224`

### DG_GetTicksMs `uint32_t DG_GetTicksMs()`
- Defined: `progs/doomgeneric/doomgeneric_sosox.c:229`

### DG_GetKey `int DG_GetKey(int* pressed, unsigned char* doomKey)`
- Defined: `progs/doomgeneric/doomgeneric_sosox.c:234`

### DG_SetWindowTitle `void DG_SetWindowTitle(const char * title)`
- Defined: `progs/doomgeneric/doomgeneric_sosox.c:255`

## progs/doomgeneric/doomgeneric_win.c

### convertToDoomKey `static unsigned char convertToDoomKey(unsigned char key)`
- Defined: `progs/doomgeneric/doomgeneric_win.c:19`

### addKeyToQueue `static void addKeyToQueue(int pressed, unsigned char keyCode)`
- Defined: `progs/doomgeneric/doomgeneric_win.c:58`

### wndProc `static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)`
- Defined: `progs/doomgeneric/doomgeneric_win.c:69`

### DG_Init `void DG_Init()`
- Defined: `progs/doomgeneric/doomgeneric_win.c:94`

### DG_DrawFrame `void DG_DrawFrame()`
- Defined: `progs/doomgeneric/doomgeneric_win.c:145`

### DG_SleepMs `void DG_SleepMs(uint32_t ms)`
- Defined: `progs/doomgeneric/doomgeneric_win.c:161`

### DG_GetTicksMs `uint32_t DG_GetTicksMs()`
- Defined: `progs/doomgeneric/doomgeneric_win.c:166`

### DG_GetKey `int DG_GetKey(int* pressed, unsigned char* doomKey)`
- Defined: `progs/doomgeneric/doomgeneric_win.c:171`

### DG_SetWindowTitle `void DG_SetWindowTitle(const char * title)`
- Defined: `progs/doomgeneric/doomgeneric_win.c:192`

## progs/doomgeneric/doomgeneric_xlib.c

### convertToDoomKey `static unsigned char convertToDoomKey(unsigned int key)`
- Defined: `progs/doomgeneric/doomgeneric_xlib.c:26`

### addKeyToQueue `static void addKeyToQueue(int pressed, unsigned int keyCode)`
- Defined: `progs/doomgeneric/doomgeneric_xlib.c:67`

### DG_Init `void DG_Init()`
- Defined: `progs/doomgeneric/doomgeneric_xlib.c:78`

### DG_DrawFrame `void DG_DrawFrame()`
- Defined: `progs/doomgeneric/doomgeneric_xlib.c:125`

### DG_SleepMs `void DG_SleepMs(uint32_t ms)`
- Defined: `progs/doomgeneric/doomgeneric_xlib.c:171`

### DG_GetTicksMs `uint32_t DG_GetTicksMs()`
- Defined: `progs/doomgeneric/doomgeneric_xlib.c:176`

### DG_GetKey `int DG_GetKey(int* pressed, unsigned char* doomKey)`
- Defined: `progs/doomgeneric/doomgeneric_xlib.c:186`

### DG_SetWindowTitle `void DG_SetWindowTitle(const char * title)`
- Defined: `progs/doomgeneric/doomgeneric_xlib.c:207`

## progs/doomgeneric/dummy.c

### I_InitTimidityConfig `void I_InitTimidityConfig(void)`
- Defined: `progs/doomgeneric/dummy.c:42`
- Doc: --------------------------------------------------------------------* public functions                                  

## progs/doomgeneric/f_finale.c

### F_StartFinale `void F_StartFinale (void)`
- Defined: `progs/doomgeneric/f_finale.c:108`
- Doc: F_StartFinale

### F_Responder `boolean F_Responder (event_t *event)`
- Defined: `progs/doomgeneric/f_finale.c:157`

### F_Ticker `void F_Ticker (void)`
- Defined: `progs/doomgeneric/f_finale.c:172`
- Doc: F_Ticker

### F_TextWrite `void F_TextWrite (void)`
- Defined: `progs/doomgeneric/f_finale.c:225`

### F_StartCast `void F_StartCast (void)`
- Defined: `progs/doomgeneric/f_finale.c:340`
- Doc: F_StartCast

### F_CastTicker `void F_CastTicker (void)`
- Defined: `progs/doomgeneric/f_finale.c:358`
- Doc: F_CastTicker

### F_CastResponder `boolean F_CastResponder (event_t* ev)`
- Defined: `progs/doomgeneric/f_finale.c:464`
- Doc: F_CastResponder

### F_CastPrint `void F_CastPrint (char* text)`
- Defined: `progs/doomgeneric/f_finale.c:484`

### F_CastDrawer `void F_CastDrawer (void)`
- Defined: `progs/doomgeneric/f_finale.c:540`
- Doc: F_CastDrawer

### F_DrawPatchCol `void
F_DrawPatchCol
( int		x,
  patch_t*	patch,
  int		col )`
- Defined: `progs/doomgeneric/f_finale.c:571`
- Doc: F_DrawPatchCol

### F_BunnyScroll `void F_BunnyScroll (void)`
- Defined: `progs/doomgeneric/f_finale.c:606`
- Doc: F_BunnyScroll

### F_ArtScreenDrawer `static void F_ArtScreenDrawer(void)`
- Defined: `progs/doomgeneric/f_finale.c:660`

### F_Drawer `void F_Drawer (void)`
- Defined: `progs/doomgeneric/f_finale.c:702`
- Doc: F_Drawer

## progs/doomgeneric/f_wipe.c

### wipe_shittyColMajorXform `void
wipe_shittyColMajorXform
( short*	array,
  int		width,
  int		height )`
- Defined: `progs/doomgeneric/f_wipe.c:40`

### wipe_initColorXForm `int
wipe_initColorXForm
( int	width,
  int	height,
  int	ticks )`
- Defined: `progs/doomgeneric/f_wipe.c:63`

### wipe_doColorXForm `int
wipe_doColorXForm
( int	width,
  int	height,
  int	ticks )`
- Defined: `progs/doomgeneric/f_wipe.c:73`

### wipe_exitColorXForm `int
wipe_exitColorXForm
( int	width,
  int	height,
  int	ticks )`
- Defined: `progs/doomgeneric/f_wipe.c:119`

### wipe_initMelt `int
wipe_initMelt
( int	width,
  int	height,
  int	ticks )`
- Defined: `progs/doomgeneric/f_wipe.c:131`

### wipe_doMelt `int
wipe_doMelt
( int	width,
  int	height,
  int	ticks )`
- Defined: `progs/doomgeneric/f_wipe.c:162`

### wipe_exitMelt `int
wipe_exitMelt
( int	width,
  int	height,
  int	ticks )`
- Defined: `progs/doomgeneric/f_wipe.c:217`

### wipe_StartScreen `int
wipe_StartScreen
( int	x,
  int	y,
  int	width,
  int	height )`
- Defined: `progs/doomgeneric/f_wipe.c:229`

### wipe_EndScreen `int
wipe_EndScreen
( int	x,
  int	y,
  int	width,
  int	height )`
- Defined: `progs/doomgeneric/f_wipe.c:241`

### wipe_ScreenWipe `int
wipe_ScreenWipe
( int	wipeno,
  int	x,
  int	y,
  int	width,
  int	height,
  int	ticks )`
- Defined: `progs/doomgeneric/f_wipe.c:254`

## progs/doomgeneric/g_game.c

### G_CmdChecksum `int G_CmdChecksum (ticcmd_t* cmd)`
- Defined: `progs/doomgeneric/g_game.c:232`

### WeaponSelectable `static boolean WeaponSelectable(weapontype_t weapon)`
- Defined: `progs/doomgeneric/g_game.c:243`

### G_NextWeapon `static int G_NextWeapon(int direction)`
- Defined: `progs/doomgeneric/g_game.c:280`

### G_BuildTiccmd `void G_BuildTiccmd (ticcmd_t* cmd, int maketic)`
- Defined: `progs/doomgeneric/g_game.c:322`
- Doc: G_BuildTiccmd Builds a ticcmd from all of the available inputs or reads it from the demo buffer. If recording a demo, wr

### G_DoLoadLevel `void G_DoLoadLevel (void)`
- Defined: `progs/doomgeneric/g_game.c:603`
- Doc: G_DoLoadLevel

### SetJoyButtons `static void SetJoyButtons(unsigned int buttons_mask)`
- Defined: `progs/doomgeneric/g_game.c:674`

### SetMouseButtons `static void SetMouseButtons(unsigned int buttons_mask)`
- Defined: `progs/doomgeneric/g_game.c:702`

### G_Responder `boolean G_Responder (event_t* ev)`
- Defined: `progs/doomgeneric/g_game.c:733`
- Doc: G_Responder Get info needed to make ticcmd_ts for the players.

### G_Ticker `void G_Ticker (void)`
- Defined: `progs/doomgeneric/g_game.c:854`
- Doc: G_Ticker Make ticcmd_ts for the players.

### G_InitPlayer `void G_InitPlayer (int player)`
- Defined: `progs/doomgeneric/g_game.c:1039`
- Doc: G_InitPlayer Called at the start. Called by the game initialization functions.

### G_PlayerFinishLevel `void G_PlayerFinishLevel (int player)`
- Defined: `progs/doomgeneric/g_game.c:1051`
- Doc: G_PlayerFinishLevel Can when a player completes a level.

### G_PlayerReborn `void G_PlayerReborn (int player)`
- Defined: `progs/doomgeneric/g_game.c:1072`
- Doc: G_PlayerReborn Called after a player dies almost everything is cleared and initialized

### G_CheckSpot `boolean
G_CheckSpot
( int		playernum,
  mapthing_t*	mthing )`
- Defined: `progs/doomgeneric/g_game.c:1114`

### G_DeathMatchSpawnPlayer `void G_DeathMatchSpawnPlayer (int playernum)`
- Defined: `progs/doomgeneric/g_game.c:1223`
- Doc: G_DeathMatchSpawnPlayer Spawns a player at one of the random death match spots called at level load and each death

### G_DoReborn `void G_DoReborn (int playernum)`
- Defined: `progs/doomgeneric/g_game.c:1250`
- Doc: G_DoReborn

### G_ScreenShot `void G_ScreenShot (void)`
- Defined: `progs/doomgeneric/g_game.c:1294`

### G_ExitLevel `void G_ExitLevel (void)`
- Defined: `progs/doomgeneric/g_game.c:1327`

### G_SecretExitLevel `void G_SecretExitLevel (void)`
- Defined: `progs/doomgeneric/g_game.c:1335`
- Doc: Here's for the german edition.

### G_DoCompleted `void G_DoCompleted (void)`
- Defined: `progs/doomgeneric/g_game.c:1345`

### G_WorldDone `void G_WorldDone (void)`
- Defined: `progs/doomgeneric/g_game.c:1494`
- Doc: G_WorldDone

### G_DoWorldDone `void G_DoWorldDone (void)`
- Defined: `progs/doomgeneric/g_game.c:1518`

### G_LoadGame `void G_LoadGame (char* name)`
- Defined: `progs/doomgeneric/g_game.c:1538`

### G_DoLoadGame `void G_DoLoadGame (void)`
- Defined: `progs/doomgeneric/g_game.c:1546`
- Doc: define VERSIONSIZE		16

### G_SaveGame `void
G_SaveGame
( int	slot,
  char*	description )`
- Defined: `progs/doomgeneric/g_game.c:1600`
- Doc: G_SaveGame Called by the menu task. Description is a 24 byte text string

### G_DoSaveGame `void G_DoSaveGame (void)`
- Defined: `progs/doomgeneric/g_game.c:1609`

### G_DeferedInitNew `void
G_DeferedInitNew
( skill_t	skill,
  int		episode,
  int		map)`
- Defined: `progs/doomgeneric/g_game.c:1696`

### G_DoNewGame `void G_DoNewGame (void)`
- Defined: `progs/doomgeneric/g_game.c:1708`

### G_InitNew `void
G_InitNew
( skill_t	skill,
  int		episode,
  int		map )`
- Defined: `progs/doomgeneric/g_game.c:1724`

### G_ReadDemoTiccmd `void G_ReadDemoTiccmd (ticcmd_t* cmd)`
- Defined: `progs/doomgeneric/g_game.c:1896`
- Doc: DEMO RECORDING  define DEMOMARKER		0x80

### IncreaseDemoBuffer `static void IncreaseDemoBuffer(void)`
- Defined: `progs/doomgeneric/g_game.c:1925`
- Doc: Increase the size of the demo buffer to allow unlimited demos

### G_WriteDemoTiccmd `void G_WriteDemoTiccmd (ticcmd_t* cmd)`
- Defined: `progs/doomgeneric/g_game.c:1955`

### G_RecordDemo `void G_RecordDemo (char *name)`
- Defined: `progs/doomgeneric/g_game.c:2010`
- Doc: G_RecordDemo

### G_VanillaVersionCode `int G_VanillaVersionCode(void)`
- Defined: `progs/doomgeneric/g_game.c:2040`
- Doc: Get the demo version code appropriate for the version set in gameversion.

### G_BeginRecording `void G_BeginRecording (void)`
- Defined: `progs/doomgeneric/g_game.c:2057`

### G_DeferedPlayDemo `void G_DeferedPlayDemo (char* name)`
- Defined: `progs/doomgeneric/g_game.c:2106`

### DemoVersionDescription `static char *DemoVersionDescription(int version)`
- Defined: `progs/doomgeneric/g_game.c:2114`
- Doc: Generate a string describing a demo version

### G_DoPlayDemo `void G_DoPlayDemo (void)`
- Defined: `progs/doomgeneric/g_game.c:2151`

### G_TimeDemo `void G_TimeDemo (char* name)`
- Defined: `progs/doomgeneric/g_game.c:2215`
- Doc: G_TimeDemo

### G_CheckDemoStatus `boolean G_CheckDemoStatus (void)`
- Defined: `progs/doomgeneric/g_game.c:2242`
- Doc: =================== = = G_CheckDemoStatus = = Called after a death or level completion to allow demos to be cleaned up =

## progs/doomgeneric/gusconf.c

### MappingIndex `static unsigned int MappingIndex(void)`
- Defined: `progs/doomgeneric/gusconf.c:42`

### SplitLine `static int SplitLine(char *line, char **fields, unsigned int max_fields)`
- Defined: `progs/doomgeneric/gusconf.c:60`

### ParseLine `static void ParseLine(gus_config_t *config, char *line)`
- Defined: `progs/doomgeneric/gusconf.c:107`

### ParseDMXConfig `static void ParseDMXConfig(char *dmxconf, gus_config_t *config)`
- Defined: `progs/doomgeneric/gusconf.c:128`

### FreeDMXConfig `static void FreeDMXConfig(gus_config_t *config)`
- Defined: `progs/doomgeneric/gusconf.c:164`

### ReadDMXConfig `static char *ReadDMXConfig(void)`
- Defined: `progs/doomgeneric/gusconf.c:174`

### WriteTimidityConfig `static boolean WriteTimidityConfig(char *path, gus_config_t *config)`
- Defined: `progs/doomgeneric/gusconf.c:196`

### GUS_WriteConfig `boolean GUS_WriteConfig(char *path)`
- Defined: `progs/doomgeneric/gusconf.c:243`

## progs/doomgeneric/hu_lib.c

### HUlib_init `void HUlib_init(void)`
- Defined: `progs/doomgeneric/hu_lib.c:35`

### HUlib_clearTextLine `void HUlib_clearTextLine(hu_textline_t* t)`
- Defined: `progs/doomgeneric/hu_lib.c:39`

### HUlib_initTextLine `void
HUlib_initTextLine
( hu_textline_t*	t,
  int			x,
  int			y,
  patch_t**		f,
  int			sc )`
- Defined: `progs/doomgeneric/hu_lib.c:46`

### HUlib_addCharToTextLine `boolean
HUlib_addCharToTextLine
( hu_textline_t*	t,
  char			ch )`
- Defined: `progs/doomgeneric/hu_lib.c:61`

### HUlib_delCharFromTextLine `boolean HUlib_delCharFromTextLine(hu_textline_t* t)`
- Defined: `progs/doomgeneric/hu_lib.c:79`

### HUlib_drawTextLine `void
HUlib_drawTextLine
( hu_textline_t*	l,
  boolean		drawcursor )`
- Defined: `progs/doomgeneric/hu_lib.c:92`

### HUlib_eraseTextLine `void HUlib_eraseTextLine(hu_textline_t* l)`
- Defined: `progs/doomgeneric/hu_lib.c:137`
- Doc: sorta called by HU_Erase and just better darn get things straight

### HUlib_initSText `void
HUlib_initSText
( hu_stext_t*	s,
  int		x,
  int		y,
  int		h,
  patch_t**	font,
  int		star...`
- Defined: `progs/doomgeneric/hu_lib.c:167`

### HUlib_addLineToSText `void HUlib_addLineToSText(hu_stext_t* s)`
- Defined: `progs/doomgeneric/hu_lib.c:191`

### HUlib_addMessageToSText `void
HUlib_addMessageToSText
( hu_stext_t*	s,
  char*		prefix,
  char*		msg )`
- Defined: `progs/doomgeneric/hu_lib.c:207`

### HUlib_drawSText `void HUlib_drawSText(hu_stext_t* s)`
- Defined: `progs/doomgeneric/hu_lib.c:222`

### HUlib_eraseSText `void HUlib_eraseSText(hu_stext_t* s)`
- Defined: `progs/doomgeneric/hu_lib.c:245`

### HUlib_initIText `void
HUlib_initIText
( hu_itext_t*	it,
  int		x,
  int		y,
  patch_t**	font,
  int		startchar,
  ...`
- Defined: `progs/doomgeneric/hu_lib.c:260`

### HUlib_delCharFromIText `void HUlib_delCharFromIText(hu_itext_t* it)`
- Defined: `progs/doomgeneric/hu_lib.c:278`
- Doc: The following deletion routines adhere to the left margin restriction

### HUlib_eraseLineFromIText `void HUlib_eraseLineFromIText(hu_itext_t* it)`
- Defined: `progs/doomgeneric/hu_lib.c:283`

### HUlib_resetIText `void HUlib_resetIText(hu_itext_t* it)`
- Defined: `progs/doomgeneric/hu_lib.c:291`
- Doc: Resets left margin as well

### HUlib_addPrefixToIText `void
HUlib_addPrefixToIText
( hu_itext_t*	it,
  char*		str )`
- Defined: `progs/doomgeneric/hu_lib.c:296`

### HUlib_keyInIText `boolean
HUlib_keyInIText
( hu_itext_t*	it,
  unsigned char ch )`
- Defined: `progs/doomgeneric/hu_lib.c:309`
- Doc: wrapper function for handling general keyed input. returns true if it ate the key

### HUlib_drawIText `void HUlib_drawIText(hu_itext_t* it)`
- Defined: `progs/doomgeneric/hu_lib.c:328`

### HUlib_eraseIText `void HUlib_eraseIText(hu_itext_t* it)`
- Defined: `progs/doomgeneric/hu_lib.c:339`

## progs/doomgeneric/hu_stuff.c

### HU_Init `void HU_Init(void)`
- Defined: `progs/doomgeneric/hu_stuff.c:285`

### HU_Stop `void HU_Stop(void)`
- Defined: `progs/doomgeneric/hu_stuff.c:302`

### HU_Start `void HU_Start(void)`
- Defined: `progs/doomgeneric/hu_stuff.c:307`

### HU_Drawer `void HU_Drawer(void)`
- Defined: `progs/doomgeneric/hu_stuff.c:382`

### HU_Erase `void HU_Erase(void)`
- Defined: `progs/doomgeneric/hu_stuff.c:392`

### HU_Ticker `void HU_Ticker(void)`
- Defined: `progs/doomgeneric/hu_stuff.c:401`

### HU_queueChatChar `void HU_queueChatChar(char c)`
- Defined: `progs/doomgeneric/hu_stuff.c:480`

### HU_dequeueChatChar `char HU_dequeueChatChar(void)`
- Defined: `progs/doomgeneric/hu_stuff.c:494`

### HU_Responder `boolean HU_Responder(event_t *ev)`
- Defined: `progs/doomgeneric/hu_stuff.c:511`

## progs/doomgeneric/i_cdmus.c

### I_CDMusInit `int I_CDMusInit(void)`
- Defined: `progs/doomgeneric/i_cdmus.c:37`

### I_CDMusPrintStartup `void I_CDMusPrintStartup(void)`
- Defined: `progs/doomgeneric/i_cdmus.c:91`
- Doc: We cannot print status messages inline during startup, they must be deferred until after I_CDMusInit has returned.

### I_CDMusPlay `int I_CDMusPlay(int track)`
- Defined: `progs/doomgeneric/i_cdmus.c:106`

### I_CDMusStop `int I_CDMusStop(void)`
- Defined: `progs/doomgeneric/i_cdmus.c:129`

### I_CDMusResume `int I_CDMusResume(void)`
- Defined: `progs/doomgeneric/i_cdmus.c:144`

### I_CDMusSetVolume `int I_CDMusSetVolume(int volume)`
- Defined: `progs/doomgeneric/i_cdmus.c:159`

### I_CDMusFirstTrack `int I_CDMusFirstTrack(void)`
- Defined: `progs/doomgeneric/i_cdmus.c:168`

### I_CDMusLastTrack `int I_CDMusLastTrack(void)`
- Defined: `progs/doomgeneric/i_cdmus.c:201`

### I_CDMusTrackLength `int I_CDMusTrackLength(int track_num)`
- Defined: `progs/doomgeneric/i_cdmus.c:218`

## progs/doomgeneric/i_endoom.c

### I_Endoom `void I_Endoom(byte *endoom_data)`
- Defined: `progs/doomgeneric/i_endoom.c:35`
- Doc: Displays the text mode ending screen after the game quits

## progs/doomgeneric/i_input.c

### TranslateKey `static unsigned char TranslateKey(unsigned char key)`
- Defined: `progs/doomgeneric/i_input.c:223`

### GetTypedChar `static unsigned char GetTypedChar(unsigned char key)`
- Defined: `progs/doomgeneric/i_input.c:241`
- Doc: Get the equivalent ASCII (Unicode?) character for a keypress.

### UpdateShiftStatus `static void UpdateShiftStatus(int pressed, unsigned char key)`
- Defined: `progs/doomgeneric/i_input.c:262`

### I_GetEvent `void I_GetEvent(void)`
- Defined: `progs/doomgeneric/i_input.c:277`

### I_InitInput `void I_InitInput(void)`
- Defined: `progs/doomgeneric/i_input.c:337`

## progs/doomgeneric/i_joystick.c

### I_ShutdownJoystick `void I_ShutdownJoystick(void)`
- Defined: `progs/doomgeneric/i_joystick.c:76`

### IsValidAxis `static boolean IsValidAxis(int axis)`
- Defined: `progs/doomgeneric/i_joystick.c:90`
- Doc: ifdef ORIGCODE

### I_InitJoystick `void I_InitJoystick(void)`
- Defined: `progs/doomgeneric/i_joystick.c:114`
- Doc: endif

### IsAxisButton `static boolean IsAxisButton(int physbutton)`
- Defined: `progs/doomgeneric/i_joystick.c:171`
- Doc: ifdef ORIGCODE

### ReadButtonState `static int ReadButtonState(int vbutton)`
- Defined: `progs/doomgeneric/i_joystick.c:202`
- Doc: Get the state of the given virtual button.

### GetButtonsState `static int GetButtonsState(void)`
- Defined: `progs/doomgeneric/i_joystick.c:227`
- Doc: Get a bitmask of all currently-pressed buttons

### GetAxisState `static int GetAxisState(int axis, int invert)`
- Defined: `progs/doomgeneric/i_joystick.c:247`
- Doc: Read the state of an axis, inverting if necessary.

### I_UpdateJoystick `void I_UpdateJoystick(void)`
- Defined: `progs/doomgeneric/i_joystick.c:321`
- Doc: endif

### I_BindJoystickVariables `void I_BindJoystickVariables(void)`
- Defined: `progs/doomgeneric/i_joystick.c:338`

## progs/doomgeneric/i_main.c

### main `int main(int argc, char **argv)`
- Defined: `progs/doomgeneric/i_main.c:38`

## progs/doomgeneric/i_minios_sound.c

### sys_tone `static long sys_tone(unsigned f)`
- Defined: `progs/doomgeneric/i_minios_sound.c:31`

### sys_time `static long sys_time(void)`
- Defined: `progs/doomgeneric/i_minios_sound.c:35`

### mus_read_varlen `static int mus_read_varlen(mus_player_t *m, unsigned long *out)`
- Defined: `progs/doomgeneric/i_minios_sound.c:100`

### mus_next_block `static int mus_next_block(mus_player_t *m, unsigned long *out)`
- Defined: `progs/doomgeneric/i_minios_sound.c:115`
- Doc: Process one full block of events at the current tick and advance pos past * its delta.  Returns the delta in *out.  Retu

### mus_note_cmp `static int mus_note_cmp(const void *a, const void *b)`
- Defined: `progs/doomgeneric/i_minios_sound.c:153`

### mus_build_chord `static void mus_build_chord(mus_player_t *m)`
- Defined: `progs/doomgeneric/i_minios_sound.c:162`
- Doc: Split the sounding notes into a bass pedal (the lowest note below the bass line) and the melody arpeggio (the highest MU

### mus_hold_tone `static void mus_hold_tone(unsigned freq, unsigned long ms)`
- Defined: `progs/doomgeneric/i_minios_sound.c:185`
- Doc: } else { if (n < 16) all[n++] = (unsigned short)note; } } m->bass = bass; m->mel_len = 0; if (n > 1) qsort(all, n, sizeo

### mus_play_chord `static void mus_play_chord(mus_player_t *m)`
- Defined: `progs/doomgeneric/i_minios_sound.c:196`
- Doc: Play one full cycle of the pseudo-polyphony: the bass pedal first, held long like the NES triangle voice, then the melod

### mus_advance `static void mus_advance(mus_player_t *m, unsigned long ms)`
- Defined: `progs/doomgeneric/i_minios_sound.c:209`

### MUS_Init `static boolean MUS_Init(void)`
- Defined: `progs/doomgeneric/i_minios_sound.c:230`

### MUS_Shutdown `static void MUS_Shutdown(void)`
- Defined: `progs/doomgeneric/i_minios_sound.c:235`

### MUS_SetMusicVolume `static void MUS_SetMusicVolume(int volume)`
- Defined: `progs/doomgeneric/i_minios_sound.c:240`

### MUS_Pause `static void MUS_Pause(void)`
- Defined: `progs/doomgeneric/i_minios_sound.c:242`

### MUS_Resume `static void MUS_Resume(void)`
- Defined: `progs/doomgeneric/i_minios_sound.c:244`

### MUS_RegisterSong `static void *MUS_RegisterSong(void *data, int len)`
- Defined: `progs/doomgeneric/i_minios_sound.c:245`

### MUS_UnRegisterSong `static void MUS_UnRegisterSong(void *handle)`
- Defined: `progs/doomgeneric/i_minios_sound.c:260`

### MUS_PlaySong `static void MUS_PlaySong(void *handle, boolean looping)`
- Defined: `progs/doomgeneric/i_minios_sound.c:266`

### MUS_StopSong `static void MUS_StopSong(void)`
- Defined: `progs/doomgeneric/i_minios_sound.c:279`

### MUS_MusicIsPlaying `static boolean MUS_MusicIsPlaying(void)`
- Defined: `progs/doomgeneric/i_minios_sound.c:284`

### MUS_Poll `static void MUS_Poll(void)`
- Defined: `progs/doomgeneric/i_minios_sound.c:288`

### PCSPK_Init `static boolean PCSPK_Init(boolean use_sfx_prefix)`
- Defined: `progs/doomgeneric/i_minios_sound.c:317`

### PCSPK_Shutdown `static void PCSPK_Shutdown(void)`
- Defined: `progs/doomgeneric/i_minios_sound.c:324`

### PCSPK_GetSfxLumpNum `static int PCSPK_GetSfxLumpNum(sfxinfo_t *sfx)`
- Defined: `progs/doomgeneric/i_minios_sound.c:329`

### free_channel `static void free_channel(int i)`
- Defined: `progs/doomgeneric/i_minios_sound.c:340`

### PCSPK_Update `static void PCSPK_Update(void)`
- Defined: `progs/doomgeneric/i_minios_sound.c:349`

### PCSPK_UpdateSoundParams `static void PCSPK_UpdateSoundParams(int ch, int v, int s)`
- Defined: `progs/doomgeneric/i_minios_sound.c:381`

### PCSPK_StartSound `static int PCSPK_StartSound(sfxinfo_t *sfx, int channel, int vol, int sep)`
- Defined: `progs/doomgeneric/i_minios_sound.c:385`

### PCSPK_StopSound `static void PCSPK_StopSound(int channel)`
- Defined: `progs/doomgeneric/i_minios_sound.c:435`

### PCSPK_SoundIsPlaying `static boolean PCSPK_SoundIsPlaying(int channel)`
- Defined: `progs/doomgeneric/i_minios_sound.c:441`

### PCSPK_CacheSounds `static void PCSPK_CacheSounds(sfxinfo_t *s, int n)`
- Defined: `progs/doomgeneric/i_minios_sound.c:447`

## progs/doomgeneric/i_scale.c

### I_InitScale `void I_InitScale(byte *_src_buffer, byte *_dest_buffer, int _dest_pitch)`
- Defined: `progs/doomgeneric/i_scale.c:60`
- Doc: Called to set the source and destination buffers before doing the scale.

### I_Scale1x `static boolean I_Scale1x(int x1, int y1, int x2, int y2)`
- Defined: `progs/doomgeneric/i_scale.c:74`
- Doc: 1x scale doesn't really do any scaling: it just copies the buffer a line at a time for when pitch != SCREENWIDTH (!nativ

### I_Scale2x `static boolean I_Scale2x(int x1, int y1, int x2, int y2)`
- Defined: `progs/doomgeneric/i_scale.c:104`
- Doc: 2x scale (640x400)

### I_Scale3x `static boolean I_Scale3x(int x1, int y1, int x2, int y2)`
- Defined: `progs/doomgeneric/i_scale.c:145`
- Doc: 3x scale (960x600)

### I_Scale4x `static boolean I_Scale4x(int x1, int y1, int x2, int y2)`
- Defined: `progs/doomgeneric/i_scale.c:190`
- Doc: 4x scale (1280x800)

### I_Scale5x `static boolean I_Scale5x(int x1, int y1, int x2, int y2)`
- Defined: `progs/doomgeneric/i_scale.c:239`
- Doc: 5x scale (1600x1000)

### FindNearestColor `static int FindNearestColor(byte *palette, int r, int g, int b)`
- Defined: `progs/doomgeneric/i_scale.c:294`
- Doc: Search through the given palette, finding the nearest color that matches the given color.

### GenerateStretchTable `static byte *GenerateStretchTable(byte *palette, int pct)`
- Defined: `progs/doomgeneric/i_scale.c:331`
- Doc: Create a stretch table.  This is a lookup table for blending colors. pct specifies the bias between the two colors: 0 = 

### I_InitStretchTables `static void I_InitStretchTables(byte *palette)`
- Defined: `progs/doomgeneric/i_scale.c:360`
- Doc: Called at startup to generate the lookup tables for aspect ratio correcting scale up.

### I_InitSquashTable `static void I_InitSquashTable(byte *palette)`
- Defined: `progs/doomgeneric/i_scale.c:386`
- Doc: Create 50%/50% table for 800x600 squash mode

### I_ResetScaleTables `void I_ResetScaleTables(byte *palette)`
- Defined: `progs/doomgeneric/i_scale.c:403`
- Doc: Destroy the scaling lookup tables. This should only ever be called if switching to a completely different palette from t

### WriteBlendedLine1x `static inline void WriteBlendedLine1x(byte *dest, byte *src1, byte *src2, 
                      ...`
- Defined: `progs/doomgeneric/i_scale.c:433`
- Doc: Aspect ratio correcting scale up functions.  These double up pixels to stretch the screen when using a 4:3 screen mode.

### I_Stretch1x `static boolean I_Stretch1x(int x1, int y1, int x2, int y2)`
- Defined: `progs/doomgeneric/i_scale.c:449`
- Doc: 1x stretch (320x240)

### WriteLine2x `static inline void WriteLine2x(byte *dest, byte *src)`
- Defined: `progs/doomgeneric/i_scale.c:506`

### WriteBlendedLine2x `static inline void WriteBlendedLine2x(byte *dest, byte *src1, byte *src2, 
                      ...`
- Defined: `progs/doomgeneric/i_scale.c:519`

### I_Stretch2x `static boolean I_Stretch2x(int x1, int y1, int x2, int y2)`
- Defined: `progs/doomgeneric/i_scale.c:538`
- Doc: 2x stretch (640x480)

### WriteLine3x `static inline void WriteLine3x(byte *dest, byte *src)`
- Defined: `progs/doomgeneric/i_scale.c:619`

### WriteBlendedLine3x `static inline void WriteBlendedLine3x(byte *dest, byte *src1, byte *src2, 
                      ...`
- Defined: `progs/doomgeneric/i_scale.c:633`

### I_Stretch3x `static boolean I_Stretch3x(int x1, int y1, int x2, int y2)`
- Defined: `progs/doomgeneric/i_scale.c:653`
- Doc: 3x stretch (960x720)

### WriteLine4x `static inline void WriteLine4x(byte *dest, byte *src)`
- Defined: `progs/doomgeneric/i_scale.c:758`

### WriteBlendedLine4x `static inline void WriteBlendedLine4x(byte *dest, byte *src1, byte *src2, 
                      ...`
- Defined: `progs/doomgeneric/i_scale.c:773`

### I_Stretch4x `static boolean I_Stretch4x(int x1, int y1, int x2, int y2)`
- Defined: `progs/doomgeneric/i_scale.c:794`
- Doc: 4x stretch (1280x960)

### WriteLine5x `static inline void WriteLine5x(byte *dest, byte *src)`
- Defined: `progs/doomgeneric/i_scale.c:923`

### I_Stretch5x `static boolean I_Stretch5x(int x1, int y1, int x2, int y2)`
- Defined: `progs/doomgeneric/i_scale.c:941`
- Doc: 5x stretch (1600x1200)

### WriteSquashedLine1x `static inline void WriteSquashedLine1x(byte *dest, byte *src)`
- Defined: `progs/doomgeneric/i_scale.c:1029`
- Doc: 1x squashed scale (256x200)

### I_Squash1x `static boolean I_Squash1x(int x1, int y1, int x2, int y2)`
- Defined: `progs/doomgeneric/i_scale.c:1060`
- Doc: 1x squashed (256x200)

### WriteSquashedLine2x `static inline void WriteSquashedLine2x(byte *dest, byte *src)`
- Defined: `progs/doomgeneric/i_scale.c:1101`

### I_Squash2x `static boolean I_Squash2x(int x1, int y1, int x2, int y2)`
- Defined: `progs/doomgeneric/i_scale.c:1159`
- Doc: 2x squash (512x400)

### WriteSquashedLine3x `static inline void WriteSquashedLine3x(byte *dest, byte *src)`
- Defined: `progs/doomgeneric/i_scale.c:1196`

### I_Squash3x `static boolean I_Squash3x(int x1, int y1, int x2, int y2)`
- Defined: `progs/doomgeneric/i_scale.c:1242`
- Doc: 3x scale squashed (800x600)  This is a special case that uses the half_stretch_table (50%) rather than the normal stretc

### WriteSquashedLine4x `static inline void WriteSquashedLine4x(byte *dest, byte *src)`
- Defined: `progs/doomgeneric/i_scale.c:1278`

### I_Squash4x `static boolean I_Squash4x(int x1, int y1, int x2, int y2)`
- Defined: `progs/doomgeneric/i_scale.c:1353`
- Doc: 4x squashed (1024x800)

### WriteSquashedLine5x `static inline void WriteSquashedLine5x(byte *dest, byte *src)`
- Defined: `progs/doomgeneric/i_scale.c:1389`

### I_Squash5x `static boolean I_Squash5x(int x1, int y1, int x2, int y2)`
- Defined: `progs/doomgeneric/i_scale.c:1418`
- Doc: 5x squashed (1280x1000)

## progs/doomgeneric/i_sound.c

### SndDeviceInList `static boolean SndDeviceInList(snddevice_t device, snddevice_t *list,
                           ...`
- Defined: `progs/doomgeneric/i_sound.c:115`
- Doc: Check if a sound device is in the given list of devices

### InitSfxModule `static void InitSfxModule(boolean use_sfx_prefix)`
- Defined: `progs/doomgeneric/i_sound.c:134`
- Doc: Find and initialize a sound_module_t appropriate for the setting in snd_sfxdevice.

### InitMusicModule `static void InitMusicModule(void)`
- Defined: `progs/doomgeneric/i_sound.c:162`
- Doc: Initialize music according to snd_musicdevice.

### I_InitSound `void I_InitSound(boolean use_sfx_prefix)`
- Defined: `progs/doomgeneric/i_sound.c:194`
- Doc: Initializes sound stuff, including volume Sets channels, SFX and music volume, allocates channel buffer, sets S_sfx look

### I_ShutdownSound `void I_ShutdownSound(void)`
- Defined: `progs/doomgeneric/i_sound.c:249`

### I_GetSfxLumpNum `int I_GetSfxLumpNum(sfxinfo_t *sfxinfo)`
- Defined: `progs/doomgeneric/i_sound.c:262`

### I_UpdateSound `void I_UpdateSound(void)`
- Defined: `progs/doomgeneric/i_sound.c:274`

### CheckVolumeSeparation `static void CheckVolumeSeparation(int *vol, int *sep)`
- Defined: `progs/doomgeneric/i_sound.c:287`

### I_UpdateSoundParams `void I_UpdateSoundParams(int channel, int vol, int sep)`
- Defined: `progs/doomgeneric/i_sound.c:308`

### I_StartSound `int I_StartSound(sfxinfo_t *sfxinfo, int channel, int vol, int sep)`
- Defined: `progs/doomgeneric/i_sound.c:317`

### I_StopSound `void I_StopSound(int channel)`
- Defined: `progs/doomgeneric/i_sound.c:330`

### I_SoundIsPlaying `boolean I_SoundIsPlaying(int channel)`
- Defined: `progs/doomgeneric/i_sound.c:338`

### I_PrecacheSounds `void I_PrecacheSounds(sfxinfo_t *sounds, int num_sounds)`
- Defined: `progs/doomgeneric/i_sound.c:350`

### I_InitMusic `void I_InitMusic(void)`
- Defined: `progs/doomgeneric/i_sound.c:358`

### I_ShutdownMusic `void I_ShutdownMusic(void)`
- Defined: `progs/doomgeneric/i_sound.c:362`

### I_SetMusicVolume `void I_SetMusicVolume(int volume)`
- Defined: `progs/doomgeneric/i_sound.c:367`

### I_PauseSong `void I_PauseSong(void)`
- Defined: `progs/doomgeneric/i_sound.c:375`

### I_ResumeSong `void I_ResumeSong(void)`
- Defined: `progs/doomgeneric/i_sound.c:383`

### I_RegisterSong `void *I_RegisterSong(void *data, int len)`
- Defined: `progs/doomgeneric/i_sound.c:391`

### I_UnRegisterSong `void I_UnRegisterSong(void *handle)`
- Defined: `progs/doomgeneric/i_sound.c:403`

### I_PlaySong `void I_PlaySong(void *handle, boolean looping)`
- Defined: `progs/doomgeneric/i_sound.c:411`

### I_StopSong `void I_StopSong(void)`
- Defined: `progs/doomgeneric/i_sound.c:419`

### I_MusicIsPlaying `boolean I_MusicIsPlaying(void)`
- Defined: `progs/doomgeneric/i_sound.c:427`

### I_BindSoundVariables `void I_BindSoundVariables(void)`
- Defined: `progs/doomgeneric/i_sound.c:439`

## progs/doomgeneric/i_system.c

### I_AtExit `void I_AtExit(atexit_func_t func, boolean run_on_error)`
- Defined: `progs/doomgeneric/i_system.c:72`

### I_Tactile `void I_Tactile(int on, int off, int total)`
- Defined: `progs/doomgeneric/i_system.c:86`
- Doc: Tactile feedback function, probably used for the Logitech Cyberman

### AutoAllocMemory `static byte *AutoAllocMemory(int *size, int default_ram, int min_ram)`
- Defined: `progs/doomgeneric/i_system.c:94`
- Doc: Zone memory auto-allocation function that allocates the zone size by trying progressively smaller zone sizes until one i

### I_ZoneBase `byte *I_ZoneBase (int *size)`
- Defined: `progs/doomgeneric/i_system.c:132`

### I_PrintBanner `void I_PrintBanner(char *msg)`
- Defined: `progs/doomgeneric/i_system.c:165`

### I_PrintDivider `void I_PrintDivider(void)`
- Defined: `progs/doomgeneric/i_system.c:176`

### I_PrintStartupBanner `void I_PrintStartupBanner(char *gamedescription)`
- Defined: `progs/doomgeneric/i_system.c:188`

### I_ConsoleStdout `boolean I_ConsoleStdout(void)`
- Defined: `progs/doomgeneric/i_system.c:209`
- Doc: I_ConsoleStdout  Returns true if stdout is a real console, false if it is a file

### I_Quit `void I_Quit (void)`
- Defined: `progs/doomgeneric/i_system.c:245`
- Doc: I_Quit

### ZenityAvailable `static int ZenityAvailable(void)`
- Defined: `progs/doomgeneric/i_system.c:271`
- Doc: returns non-zero if zenity is available

### EscapeShellString `static char *EscapeShellString(char *string)`
- Defined: `progs/doomgeneric/i_system.c:279`
- Doc: Escape special characters in the given string so that they can be safely enclosed in shell quotes.

### ZenityErrorBox `static int ZenityErrorBox(char *message)`
- Defined: `progs/doomgeneric/i_system.c:322`
- Doc: Open a native error box with a message using zenity

### I_Error `void I_Error (char *error, ...)`
- Defined: `progs/doomgeneric/i_system.c:358`

### I_GetMemoryValue `boolean I_GetMemoryValue(unsigned int offset, void *value, int size)`
- Defined: `progs/doomgeneric/i_system.c:501`

## progs/doomgeneric/i_timer.c

### I_GetTicks `int I_GetTicks(void)`
- Defined: `progs/doomgeneric/i_timer.c:35`

### I_GetTime `int  I_GetTime (void)`
- Defined: `progs/doomgeneric/i_timer.c:41`

### I_GetTimeMS `int I_GetTimeMS(void)`
- Defined: `progs/doomgeneric/i_timer.c:60`
- Doc: Same as I_GetTime, but returns time in milliseconds

### I_Sleep `void I_Sleep(int ms)`
- Defined: `progs/doomgeneric/i_timer.c:74`
- Doc: Sleep for a specified number of ms

### I_WaitVBL `void I_WaitVBL(int count)`
- Defined: `progs/doomgeneric/i_timer.c:82`

### I_InitTimer `void I_InitTimer(void)`
- Defined: `progs/doomgeneric/i_timer.c:87`

## progs/doomgeneric/i_video.c

### cmap_to_rgb565 `void cmap_to_rgb565(uint16_t * out, uint8_t * in, int in_pixels)`
- Defined: `progs/doomgeneric/i_video.c:130`

### cmap_to_fb `void cmap_to_fb(uint8_t * out, uint8_t * in, int in_pixels)`
- Defined: `progs/doomgeneric/i_video.c:151`

### I_InitGraphics `void I_InitGraphics (void)`
- Defined: `progs/doomgeneric/i_video.c:178`

### I_ShutdownGraphics `void I_ShutdownGraphics (void)`
- Defined: `progs/doomgeneric/i_video.c:231`

### I_StartFrame `void I_StartFrame (void)`
- Defined: `progs/doomgeneric/i_video.c:236`

### I_StartTic `void I_StartTic (void)`
- Defined: `progs/doomgeneric/i_video.c:241`

### I_UpdateNoBlit `void I_UpdateNoBlit (void)`
- Defined: `progs/doomgeneric/i_video.c:246`

### I_FinishUpdate `void I_FinishUpdate (void)`
- Defined: `progs/doomgeneric/i_video.c:254`
- Doc: I_FinishUpdate

### I_ReadScreen `void I_ReadScreen (byte* scr)`
- Defined: `progs/doomgeneric/i_video.c:302`
- Doc: I_ReadScreen

### I_SetPalette `void I_SetPalette (byte* palette)`
- Defined: `progs/doomgeneric/i_video.c:314`
- Doc: I_SetPalette  define GFX_RGB565(r, g, b)			((((r & 0xF8) >> 3) << 11) | (((g & 0xFC) >> 2) << 5) | ((b & 0xF8) >> 3)) de

### I_GetPaletteIndex `int I_GetPaletteIndex (int r, int g, int b)`
- Defined: `progs/doomgeneric/i_video.c:332`
- Doc: Given an RGB value, find the closest matching palette index.

### I_BeginRead `void I_BeginRead (void)`
- Defined: `progs/doomgeneric/i_video.c:368`

### I_EndRead `void I_EndRead (void)`
- Defined: `progs/doomgeneric/i_video.c:372`

### I_SetWindowTitle `void I_SetWindowTitle (char *title)`
- Defined: `progs/doomgeneric/i_video.c:376`

### I_GraphicsCheckCommandLine `void I_GraphicsCheckCommandLine (void)`
- Defined: `progs/doomgeneric/i_video.c:381`

### I_SetGrabMouseCallback `void I_SetGrabMouseCallback (grabmouse_callback_t func)`
- Defined: `progs/doomgeneric/i_video.c:385`

### I_EnableLoadingDisk `void I_EnableLoadingDisk(void)`
- Defined: `progs/doomgeneric/i_video.c:389`

### I_BindVideoVariables `void I_BindVideoVariables (void)`
- Defined: `progs/doomgeneric/i_video.c:393`

### I_DisplayFPSDots `void I_DisplayFPSDots (boolean dots_on)`
- Defined: `progs/doomgeneric/i_video.c:397`

### I_CheckIsScreensaver `void I_CheckIsScreensaver (void)`
- Defined: `progs/doomgeneric/i_video.c:401`

## progs/doomgeneric/m_argv.c

### M_CheckParmWithArgs `int M_CheckParmWithArgs(char *check, int num_args)`
- Defined: `progs/doomgeneric/m_argv.c:42`
- Doc: M_CheckParm Checks for the given parameter in the program's command line arguments. Returns the argument number (1 to ar

### M_ParmExists `boolean M_ParmExists(char *check)`
- Defined: `progs/doomgeneric/m_argv.c:62`
- Doc: M_ParmExists  Returns true if the given parameter exists in the program's command line arguments, false if not.

### M_CheckParm `int M_CheckParm(char *check)`
- Defined: `progs/doomgeneric/m_argv.c:67`

### LoadResponseFile `static void LoadResponseFile(int argv_index)`
- Defined: `progs/doomgeneric/m_argv.c:74`
- Doc: define MAXARGVS        100

### M_FindResponseFile `void M_FindResponseFile(void)`
- Defined: `progs/doomgeneric/m_argv.c:234`
- Doc: Find a Response File

### M_GetExecutableName `char *M_GetExecutableName(void)`
- Defined: `progs/doomgeneric/m_argv.c:249`
- Doc: Return the name of the executable used to start the program:

## progs/doomgeneric/m_bbox.c

### M_ClearBox `void M_ClearBox (fixed_t *box)`
- Defined: `progs/doomgeneric/m_bbox.c:25`
- Doc: include "m_bbox.h"

### M_AddToBox `void
M_AddToBox
( fixed_t*	box,
  fixed_t	x,
  fixed_t	y )`
- Defined: `progs/doomgeneric/m_bbox.c:34`

## progs/doomgeneric/m_cheat.c

### cht_CheckCheat `int
cht_CheckCheat
( cheatseq_t*	cht,
  char		key )`
- Defined: `progs/doomgeneric/m_cheat.c:34`
- Doc: Called in st_stuff module, which handles the input. Returns a 1 if the cheat was successful, 0 if failed.

### cht_GetParam `void
cht_GetParam
( cheatseq_t*	cht,
  char*		buffer )`
- Defined: `progs/doomgeneric/m_cheat.c:80`

## progs/doomgeneric/m_config.c

### SearchCollection `static default_t *SearchCollection(default_collection_t *collection, char *name)`
- Defined: `progs/doomgeneric/m_config.c:1562`
- Doc: Search a collection for a variable

### SaveDefaultCollection `static void SaveDefaultCollection(default_collection_t *collection)`
- Defined: `progs/doomgeneric/m_config.c:1607`

### ParseIntParameter `static int ParseIntParameter(char *strparm)`
- Defined: `progs/doomgeneric/m_config.c:1715`
- Doc: Parses integer values in the configuration file

### SetVariable `static void SetVariable(default_t *def, char *value)`
- Defined: `progs/doomgeneric/m_config.c:1727`

### LoadDefaultCollection `static void LoadDefaultCollection(default_collection_t *collection)`
- Defined: `progs/doomgeneric/m_config.c:1770`

### M_SetConfigFilenames `void M_SetConfigFilenames(char *main_config, char *extra_config)`
- Defined: `progs/doomgeneric/m_config.c:1835`
- Doc: Set the default filenames to use for configuration files.

### M_SaveDefaults `void M_SaveDefaults (void)`
- Defined: `progs/doomgeneric/m_config.c:1845`
- Doc: M_SaveDefaults

### M_SaveDefaultsAlternate `void M_SaveDefaultsAlternate(char *main, char *extra)`
- Defined: `progs/doomgeneric/m_config.c:1855`
- Doc: Save defaults to alternate filenames

### M_LoadDefaults `void M_LoadDefaults (void)`
- Defined: `progs/doomgeneric/m_config.c:1880`
- Doc: M_LoadDefaults

### GetDefaultForName `static default_t *GetDefaultForName(char *name)`
- Defined: `progs/doomgeneric/m_config.c:1936`
- Doc: Get a configuration file variable by its name

### M_BindVariable `void M_BindVariable(char *name, void *location)`
- Defined: `progs/doomgeneric/m_config.c:1963`
- Doc: Bind a variable to a given configuration file variable, by name.

### M_SetVariable `boolean M_SetVariable(char *name, char *value)`
- Defined: `progs/doomgeneric/m_config.c:1976`
- Doc: Set the value of a particular variable; an API function for other parts of the program to assign values to config variab

### M_GetIntVariable `int M_GetIntVariable(char *name)`
- Defined: `progs/doomgeneric/m_config.c:1994`
- Doc: Get the value of a variable.

### M_GetStrVariable `const char *M_GetStrVariable(char *name)`
- Defined: `progs/doomgeneric/m_config.c:2009`

### M_GetFloatVariable `float M_GetFloatVariable(char *name)`
- Defined: `progs/doomgeneric/m_config.c:2024`

### GetDefaultConfigDir `static char *GetDefaultConfigDir(void)`
- Defined: `progs/doomgeneric/m_config.c:2042`
- Doc: Get the path to the default configuration dir to use, if NULL is passed to M_SetConfigDir.

### M_SetConfigDir `void M_SetConfigDir(char *dir)`
- Defined: `progs/doomgeneric/m_config.c:2058`
- Doc: SetConfigDir:  Sets the location of the configuration directory, where configuration files are stored - default.cfg, cho

### M_GetSaveGameDir `char *M_GetSaveGameDir(char *iwadname)`
- Defined: `progs/doomgeneric/m_config.c:2086`
- Doc: Calculate the path to the directory to use to store save games. Creates the directory as necessary.

## progs/doomgeneric/m_controls.c

### M_BindBaseControls `void M_BindBaseControls(void)`
- Defined: `progs/doomgeneric/m_controls.c:203`
- Doc: Bind all of the common controls used by Doom and all other games.

### M_BindHereticControls `void M_BindHereticControls(void)`
- Defined: `progs/doomgeneric/m_controls.c:240`

### M_BindHexenControls `void M_BindHexenControls(void)`
- Defined: `progs/doomgeneric/m_controls.c:255`

### M_BindStrifeControls `void M_BindStrifeControls(void)`
- Defined: `progs/doomgeneric/m_controls.c:271`

### M_BindWeaponControls `void M_BindWeaponControls(void)`
- Defined: `progs/doomgeneric/m_controls.c:306`

### M_BindMapControls `void M_BindMapControls(void)`
- Defined: `progs/doomgeneric/m_controls.c:327`

### M_BindMenuControls `void M_BindMenuControls(void)`
- Defined: `progs/doomgeneric/m_controls.c:343`

### M_BindChatControls `void M_BindChatControls(unsigned int num_players)`
- Defined: `progs/doomgeneric/m_controls.c:374`

### M_ApplyPlatformDefaults `void M_ApplyPlatformDefaults(void)`
- Defined: `progs/doomgeneric/m_controls.c:393`
- Doc: Apply custom patches to the default values depending on the platform we are running on.

## progs/doomgeneric/m_fixed.c

### FixedMul `fixed_t
FixedMul
( fixed_t	a,
  fixed_t	b )`
- Defined: `progs/doomgeneric/m_fixed.c:32`
- Doc: Fixme. __USE_C_FIXED__ or something.

### FixedDiv `fixed_t FixedDiv(fixed_t a, fixed_t b)`
- Defined: `progs/doomgeneric/m_fixed.c:46`
- Doc: FixedDiv, C version.

## progs/doomgeneric/m_menu.c

### M_ReadSaveStrings `void M_ReadSaveStrings(void)`
- Defined: `progs/doomgeneric/m_menu.c:503`
- Doc: M_ReadSaveStrings read the strings from the savegame files

### M_DrawLoad `void M_DrawLoad(void)`
- Defined: `progs/doomgeneric/m_menu.c:530`
- Doc: M_LoadGame & Cie.

### M_DrawSaveLoadBorder `void M_DrawSaveLoadBorder(int x,int y)`
- Defined: `progs/doomgeneric/m_menu.c:549`
- Doc: Draw border for the savegame description

### M_LoadSelect `void M_LoadSelect(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:572`
- Doc: User wants to load this game

### M_LoadGame `void M_LoadGame (int choice)`
- Defined: `progs/doomgeneric/m_menu.c:585`
- Doc: Selected from DOOM menu

### M_DrawSave `void M_DrawSave(void)`
- Defined: `progs/doomgeneric/m_menu.c:601`
- Doc: M_SaveGame & Cie.

### M_DoSave `void M_DoSave(int slot)`
- Defined: `progs/doomgeneric/m_menu.c:622`
- Doc: M_Responder calls this when user is finished

### M_SaveSelect `void M_SaveSelect(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:635`
- Doc: User wants to save. Start string input for M_Responder

### M_SaveGame `void M_SaveGame (int choice)`
- Defined: `progs/doomgeneric/m_menu.c:650`
- Doc: Selected from DOOM menu

### M_QuickSaveResponse `void M_QuickSaveResponse(int key)`
- Defined: `progs/doomgeneric/m_menu.c:671`

### M_QuickSave `void M_QuickSave(void)`
- Defined: `progs/doomgeneric/m_menu.c:680`

### M_QuickLoadResponse `void M_QuickLoadResponse(int key)`
- Defined: `progs/doomgeneric/m_menu.c:709`
- Doc: M_QuickLoad

### M_QuickLoad `void M_QuickLoad(void)`
- Defined: `progs/doomgeneric/m_menu.c:717`

### M_DrawReadThis1 `void M_DrawReadThis1(void)`
- Defined: `progs/doomgeneric/m_menu.c:743`
- Doc: Read This Menus Had a "quick hack to fix romero bug"

### M_DrawReadThis2 `void M_DrawReadThis2(void)`
- Defined: `progs/doomgeneric/m_menu.c:820`
- Doc: Read This Menus - optional second page.

### M_DrawSound `void M_DrawSound(void)`
- Defined: `progs/doomgeneric/m_menu.c:834`
- Doc: Change Sfx & Music volumes

### M_Sound `void M_Sound(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:844`

### M_SfxVol `void M_SfxVol(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:849`

### M_MusicVol `void M_MusicVol(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:866`

### M_DrawMainMenu `void M_DrawMainMenu(void)`
- Defined: `progs/doomgeneric/m_menu.c:890`
- Doc: M_DrawMainMenu

### M_DrawNewGame `void M_DrawNewGame(void)`
- Defined: `progs/doomgeneric/m_menu.c:902`
- Doc: M_NewGame

### M_NewGame `void M_NewGame(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:907`

### M_DrawEpisode `void M_DrawEpisode(void)`
- Defined: `progs/doomgeneric/m_menu.c:929`

### M_VerifyNightmare `void M_VerifyNightmare(int key)`
- Defined: `progs/doomgeneric/m_menu.c:934`

### M_ChooseSkill `void M_ChooseSkill(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:943`

### M_Episode `void M_Episode(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:955`

### M_DrawOptions `void M_DrawOptions(void)`
- Defined: `progs/doomgeneric/m_menu.c:986`

### M_Options `void M_Options(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:1006`

### M_ChangeMessages `void M_ChangeMessages(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:1017`
- Doc: Toggle messages on/off

### M_EndGameResponse `void M_EndGameResponse(int key)`
- Defined: `progs/doomgeneric/m_menu.c:1035`
- Doc: M_EndGame

### M_EndGame `void M_EndGame(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:1044`

### M_ReadThis `void M_ReadThis(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:1069`
- Doc: M_ReadThis

### M_ReadThis2 `void M_ReadThis2(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:1074`

### M_FinishReadThis `void M_FinishReadThis(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:1092`

### M_QuitResponse `void M_QuitResponse(int key)`
- Defined: `progs/doomgeneric/m_menu.c:1128`

### M_SelectEndMessage `static char *M_SelectEndMessage(void)`
- Defined: `progs/doomgeneric/m_menu.c:1145`

### M_QuitDOOM `void M_QuitDOOM(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:1166`

### M_ChangeSensitivity `void M_ChangeSensitivity(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:1175`

### M_ChangeDetail `void M_ChangeDetail(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:1193`

### M_SizeDisplay `void M_SizeDisplay(int choice)`
- Defined: `progs/doomgeneric/m_menu.c:1209`

### M_DrawThermo `void
M_DrawThermo
( int	x,
  int	y,
  int	thermWidth,
  int	thermDot )`
- Defined: `progs/doomgeneric/m_menu.c:1243`
- Doc: Menu Functions

### M_DrawEmptyCell `void
M_DrawEmptyCell
( menu_t*	menu,
  int		item )`
- Defined: `progs/doomgeneric/m_menu.c:1266`

### M_DrawSelCell `void
M_DrawSelCell
( menu_t*	menu,
  int		item )`
- Defined: `progs/doomgeneric/m_menu.c:1277`

### M_StartMessage `void
M_StartMessage
( char*		string,
  void*		routine,
  boolean	input )`
- Defined: `progs/doomgeneric/m_menu.c:1286`

### M_StopMessage `void M_StopMessage(void)`
- Defined: `progs/doomgeneric/m_menu.c:1302`

### M_StringWidth `int M_StringWidth(char* string)`
- Defined: `progs/doomgeneric/m_menu.c:1315`
- Doc: Find string width from hu_font chars

### M_StringHeight `int M_StringHeight(char* string)`
- Defined: `progs/doomgeneric/m_menu.c:1338`
- Doc: Find string height from hu_font chars

### M_WriteText `void
M_WriteText
( int		x,
  int		y,
  char*		string)`
- Defined: `progs/doomgeneric/m_menu.c:1356`
- Doc: Write a string using the hu_font

### IsNullKey `static boolean IsNullKey(int key)`
- Defined: `progs/doomgeneric/m_menu.c:1402`
- Doc: These keys evaluate to a "null" key in Vanilla Doom that allows weird jumping in the menus. Preserve this behavior for a

### M_Responder `boolean M_Responder (event_t* ev)`
- Defined: `progs/doomgeneric/m_menu.c:1416`
- Doc: M_Responder

### M_StartControlPanel `void M_StartControlPanel (void)`
- Defined: `progs/doomgeneric/m_menu.c:1899`
- Doc: M_StartControlPanel

### M_DrawOPLDev `static void M_DrawOPLDev(void)`
- Defined: `progs/doomgeneric/m_menu.c:1913`
- Doc: if 0

### M_Drawer `void M_Drawer (void)`
- Defined: `progs/doomgeneric/m_menu.c:1951`
- Doc: M_Drawer Called after the view has been rendered, but before it has been blitted.

### M_ClearMenus `void M_ClearMenus (void)`
- Defined: `progs/doomgeneric/m_menu.c:2041`
- Doc: M_ClearMenus

### M_SetupNextMenu `void M_SetupNextMenu(menu_t *menudef)`
- Defined: `progs/doomgeneric/m_menu.c:2054`
- Doc: M_SetupNextMenu

### M_Ticker `void M_Ticker (void)`
- Defined: `progs/doomgeneric/m_menu.c:2064`
- Doc: M_Ticker

### M_Init `void M_Init (void)`
- Defined: `progs/doomgeneric/m_menu.c:2077`
- Doc: M_Init

## progs/doomgeneric/m_misc.c

### M_MakeDirectory `void M_MakeDirectory(char *path)`
- Defined: `progs/doomgeneric/m_misc.c:54`
- Doc: Create a directory

### M_FileExists `boolean M_FileExists(char *filename)`
- Defined: `progs/doomgeneric/m_misc.c:65`
- Doc: Check if a file exists

### M_FileLength `long M_FileLength(FILE *handle)`
- Defined: `progs/doomgeneric/m_misc.c:88`
- Doc: Determine the length of an open file.

### M_WriteFile `boolean M_WriteFile(char *name, void *source, int length)`
- Defined: `progs/doomgeneric/m_misc.c:110`
- Doc: M_WriteFile

### M_ReadFile `int M_ReadFile(char *name, byte **buffer)`
- Defined: `progs/doomgeneric/m_misc.c:134`
- Doc: M_ReadFile

### M_TempFile `char *M_TempFile(char *s)`
- Defined: `progs/doomgeneric/m_misc.c:165`
- Doc: Returns the path to a temporary file of the given name, stored inside the system temporary directory.  The returned valu

### M_StrToInt `boolean M_StrToInt(const char *str, int *result)`
- Defined: `progs/doomgeneric/m_misc.c:188`

### M_ExtractFileBase `void M_ExtractFileBase(char *path, char *dest)`
- Defined: `progs/doomgeneric/m_misc.c:196`

### M_ForceUppercase `void M_ForceUppercase(char *text)`
- Defined: `progs/doomgeneric/m_misc.c:241`
- Doc: --------------------------------------------------------------------------  PROC M_ForceUppercase  Change string to uppe

### M_StrCaseStr `char *M_StrCaseStr(char *haystack, char *needle)`
- Defined: `progs/doomgeneric/m_misc.c:257`
- Doc: M_StrCaseStr  Case-insensitive version of strstr()

### M_StringDuplicate `char *M_StringDuplicate(const char *orig)`
- Defined: `progs/doomgeneric/m_misc.c:290`
- Doc: Safe version of strdup() that checks the string was successfully allocated.

### M_StringReplace `char *M_StringReplace(const char *haystack, const char *needle,
                      const char ...`
- Defined: `progs/doomgeneric/m_misc.c:309`
- Doc: String replace function.

### M_StringCopy `boolean M_StringCopy(char *dest, const char *src, size_t dest_size)`
- Defined: `progs/doomgeneric/m_misc.c:371`
- Doc: Safe string copy function that works like OpenBSD's strlcpy(). Returns true if the string was not truncated.

### M_StringConcat `boolean M_StringConcat(char *dest, const char *src, size_t dest_size)`
- Defined: `progs/doomgeneric/m_misc.c:392`
- Doc: Safe string concat function that works like OpenBSD's strlcat(). Returns true if string not truncated.

### M_StringStartsWith `boolean M_StringStartsWith(const char *s, const char *prefix)`
- Defined: `progs/doomgeneric/m_misc.c:407`
- Doc: Returns true if 's' begins with the specified prefix.

### M_StringEndsWith `boolean M_StringEndsWith(const char *s, const char *suffix)`
- Defined: `progs/doomgeneric/m_misc.c:415`
- Doc: Returns true if 's' ends with the specified suffix.

### M_StringJoin `char *M_StringJoin(const char *s, ...)`
- Defined: `progs/doomgeneric/m_misc.c:424`
- Doc: Return a newly-malloced string with all the strings given as arguments concatenated together.

### M_vsnprintf `int M_vsnprintf(char *buf, size_t buf_len, const char *s, va_list args)`
- Defined: `progs/doomgeneric/m_misc.c:481`
- Doc: Safe, portable vsnprintf().

### M_snprintf `int M_snprintf(char *buf, size_t buf_len, const char *s, ...)`
- Defined: `progs/doomgeneric/m_misc.c:507`
- Doc: Safe, portable snprintf().

### M_OEMToUTF8 `char *M_OEMToUTF8(const char *oem)`
- Defined: `progs/doomgeneric/m_misc.c:518`
- Doc: ifdef _WIN32

## progs/doomgeneric/m_random.c

### P_Random `int P_Random (void)`
- Defined: `progs/doomgeneric/m_random.c:50`
- Doc: Which one is deterministic?

### M_Random `int M_Random (void)`
- Defined: `progs/doomgeneric/m_random.c:55`

### M_ClearRandom `void M_ClearRandom (void)`
- Defined: `progs/doomgeneric/m_random.c:61`

## progs/doomgeneric/memio.c

### mem_fopen_read `MEMFILE *mem_fopen_read(void *buf, size_t buflen)`
- Defined: `progs/doomgeneric/memio.c:41`
- Doc: Open a memory area for reading

### mem_fread `size_t mem_fread(void *buf, size_t size, size_t nmemb, MEMFILE *stream)`
- Defined: `progs/doomgeneric/memio.c:57`
- Doc: Read bytes

### mem_fopen_write `MEMFILE *mem_fopen_write(void)`
- Defined: `progs/doomgeneric/memio.c:89`
- Doc: Open a memory area for writing

### mem_fwrite `size_t mem_fwrite(const void *ptr, size_t size, size_t nmemb, MEMFILE *stream)`
- Defined: `progs/doomgeneric/memio.c:106`
- Doc: Write bytes to stream

### mem_get_buf `void mem_get_buf(MEMFILE *stream, void **buf, size_t *buflen)`
- Defined: `progs/doomgeneric/memio.c:142`

### mem_fclose `void mem_fclose(MEMFILE *stream)`
- Defined: `progs/doomgeneric/memio.c:148`

### mem_ftell `long mem_ftell(MEMFILE *stream)`
- Defined: `progs/doomgeneric/memio.c:158`

### mem_fseek `int mem_fseek(MEMFILE *stream, signed long position, mem_rel_t whence)`
- Defined: `progs/doomgeneric/memio.c:163`

## progs/doomgeneric/p_ceilng.c

### T_MoveCeiling `void T_MoveCeiling (ceiling_t* ceiling)`
- Defined: `progs/doomgeneric/p_ceilng.c:44`
- Doc: T_MoveCeiling

### EV_DoCeiling `int
EV_DoCeiling
( line_t*	line,
  ceiling_e	type )`
- Defined: `progs/doomgeneric/p_ceilng.c:160`
- Doc: EV_DoCeiling Move a ceiling up/down and all around!

### P_AddActiveCeiling `void P_AddActiveCeiling(ceiling_t* c)`
- Defined: `progs/doomgeneric/p_ceilng.c:240`
- Doc: Add an active ceiling

### P_RemoveActiveCeiling `void P_RemoveActiveCeiling(ceiling_t* c)`
- Defined: `progs/doomgeneric/p_ceilng.c:259`
- Doc: Remove a ceiling's thinker

### P_ActivateInStasisCeiling `void P_ActivateInStasisCeiling(line_t* line)`
- Defined: `progs/doomgeneric/p_ceilng.c:280`
- Doc: Restart a ceiling that's in-stasis

### EV_CeilingCrushStop `int	EV_CeilingCrushStop(line_t	*line)`
- Defined: `progs/doomgeneric/p_ceilng.c:303`
- Doc: EV_CeilingCrushStop Stop a ceiling from crushing!

## progs/doomgeneric/p_doors.c

### T_VerticalDoor `void T_VerticalDoor (vldoor_t* door)`
- Defined: `progs/doomgeneric/p_doors.c:57`
- Doc: T_VerticalDoor

### EV_DoLockedDoor `int
EV_DoLockedDoor
( line_t*	line,
  vldoor_e	type,
  mobj_t*	thing )`
- Defined: `progs/doomgeneric/p_doors.c:193`
- Doc: EV_DoLockedDoor Move a locked door up/down

### EV_DoDoor `int
EV_DoDoor
( line_t*	line,
  vldoor_e	type )`
- Defined: `progs/doomgeneric/p_doors.c:249`

### EV_VerticalDoor `void
EV_VerticalDoor
( line_t*	line,
  mobj_t*	thing )`
- Defined: `progs/doomgeneric/p_doors.c:336`
- Doc: EV_VerticalDoor : open a door manually, no tag value

### P_SpawnDoorCloseIn30 `void P_SpawnDoorCloseIn30 (sector_t* sec)`
- Defined: `progs/doomgeneric/p_doors.c:519`
- Doc: Spawn a door that closes after 30 seconds

### P_SpawnDoorRaiseIn5Mins `void
P_SpawnDoorRaiseIn5Mins
( sector_t*	sec,
  int		secnum )`
- Defined: `progs/doomgeneric/p_doors.c:541`
- Doc: Spawn a door that opens after 5 minutes

### P_InitSlidingDoorFrames `void P_InitSlidingDoorFrames(void)`
- Defined: `progs/doomgeneric/p_doors.c:579`

### P_FindSlidingDoorType `int P_FindSlidingDoorType(line_t*	line)`
- Defined: `progs/doomgeneric/p_doors.c:624`
- Doc: Return index into "slideFrames" array for which door type to use

### T_SlidingDoor `void T_SlidingDoor (slidedoor_t*	door)`
- Defined: `progs/doomgeneric/p_doors.c:638`

### EV_SlidingDoor `void
EV_SlidingDoor
( line_t*	line,
  mobj_t*	thing )`
- Defined: `progs/doomgeneric/p_doors.c:723`

## progs/doomgeneric/p_enemy.c

### P_RecursiveSound `void
P_RecursiveSound
( sector_t*	sec,
  int		soundblocks )`
- Defined: `progs/doomgeneric/p_enemy.c:97`

### P_NoiseAlert `void
P_NoiseAlert
( mobj_t*	target,
  mobj_t*	emmiter )`
- Defined: `progs/doomgeneric/p_enemy.c:151`
- Doc: P_NoiseAlert If a monster yells at a player, it will alert other monsters to the player.

### P_CheckMeleeRange `boolean P_CheckMeleeRange (mobj_t*	actor)`
- Defined: `progs/doomgeneric/p_enemy.c:167`
- Doc: P_CheckMeleeRange

### P_CheckMissileRange `boolean P_CheckMissileRange (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:190`
- Doc: P_CheckMissileRange

### P_Move `boolean P_Move (mobj_t*	actor)`
- Defined: `progs/doomgeneric/p_enemy.c:259`

### P_TryWalk `boolean P_TryWalk (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:337`
- Doc: TryWalk Attempts to move actor on in its current (ob->moveangle) direction. If blocked by either a wall or an actor retu

### P_NewChaseDir `void P_NewChaseDir (mobj_t*	actor)`
- Defined: `progs/doomgeneric/p_enemy.c:347`

### P_LookForPlayers `boolean
P_LookForPlayers
( mobj_t*	actor,
  boolean	allaround )`
- Defined: `progs/doomgeneric/p_enemy.c:486`
- Doc: P_LookForPlayers If allaround is false, only look 180 degrees in front. Returns true if a player is targeted.

### A_KeenDie `void A_KeenDie (mobj_t* mo)`
- Defined: `progs/doomgeneric/p_enemy.c:551`
- Doc: A_KeenDie DOOM II special, map 32. Uses special tag 666.

### A_Look `void A_Look (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:589`
- Doc: A_Look Stay in state until a player is sighted.

### A_Chase `void A_Chase (mobj_t*	actor)`
- Defined: `progs/doomgeneric/p_enemy.c:657`
- Doc: A_Chase Actor has a melee attack, so it tries to close as fast as possible

### A_FaceTarget `void A_FaceTarget (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:767`
- Doc: A_FaceTarget

### A_PosAttack `void A_PosAttack (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:787`
- Doc: A_PosAttack

### A_SPosAttack `void A_SPosAttack (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:805`

### A_CPosAttack `void A_CPosAttack (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:829`

### A_CPosRefire `void A_CPosRefire (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:849`

### A_SpidRefire `void A_SpidRefire (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:865`

### A_BspiAttack `void A_BspiAttack (mobj_t *actor)`
- Defined: `progs/doomgeneric/p_enemy.c:882`

### A_TroopAttack `void A_TroopAttack (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:898`
- Doc: A_TroopAttack

### A_SargAttack `void A_SargAttack (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:918`

### A_HeadAttack `void A_HeadAttack (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:934`

### A_CyberAttack `void A_CyberAttack (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:953`

### A_BruisAttack `void A_BruisAttack (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:962`

### A_SkelMissile `void A_SkelMissile (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:987`
- Doc: A_SkelMissile

### A_Tracer `void A_Tracer (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1005`

### A_SkelWhoosh `void A_SkelWhoosh (mobj_t*	actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1076`

### A_SkelFist `void A_SkelFist (mobj_t*	actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1085`

### PIT_VileCheck `boolean PIT_VileCheck (mobj_t*	thing)`
- Defined: `progs/doomgeneric/p_enemy.c:1113`

### A_VileChase `void A_VileChase (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1152`
- Doc: A_VileChase Check for ressurecting a body

### A_VileStart `void A_VileStart (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1218`
- Doc: A_VileStart

### A_StartFire `void A_StartFire (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1229`

### A_FireCrackle `void A_FireCrackle (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1235`

### A_Fire `void A_Fire (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1241`

### A_VileTarget `void A_VileTarget (mobj_t*	actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1273`
- Doc: A_VileTarget Spawn the hellfire

### A_VileAttack `void A_VileAttack (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1298`
- Doc: A_VileAttack

### A_FatRaise `void A_FatRaise (mobj_t *actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1338`
- Doc: Mancubus attack, firing three missiles (bruisers) in three different directions? Doesn't look like it.  define	FATSPREAD

### A_FatAttack1 `void A_FatAttack1 (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1344`

### A_FatAttack2 `void A_FatAttack2 (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1365`

### A_FatAttack3 `void A_FatAttack3 (mobj_t*	actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1384`

### A_SkullAttack `void A_SkullAttack (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1414`
- Doc: SkullAttack Fly at the player like a missile.  define	SKULLSPEED		(20*FRACUNIT)

### A_PainShootSkull `void
A_PainShootSkull
( mobj_t*	actor,
  angle_t	angle )`
- Defined: `progs/doomgeneric/p_enemy.c:1445`
- Doc: A_PainShootSkull Spawn a lost soul and launch it at the target

### A_PainAttack `void A_PainAttack (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1508`
- Doc: A_PainAttack Spawn a lost soul and launch it at the target

### A_PainDie `void A_PainDie (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1516`

### A_Scream `void A_Scream (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1525`

### A_XScream `void A_XScream (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1566`

### A_Pain `void A_Pain (mobj_t* actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1572`

### A_Fall `void A_Fall (mobj_t *actor)`
- Defined: `progs/doomgeneric/p_enemy.c:1578`

### A_Explode `void A_Explode (mobj_t* thingy)`
- Defined: `progs/doomgeneric/p_enemy.c:1594`
- Doc: A_Explode

### CheckBossEnd `static boolean CheckBossEnd(mobjtype_t motype)`
- Defined: `progs/doomgeneric/p_enemy.c:1604`
- Doc: Check whether the death of the specified monster type is allowed to trigger the end of episode special action.  This beh

### A_BossDeath `void A_BossDeath (mobj_t* mo)`
- Defined: `progs/doomgeneric/p_enemy.c:1656`
- Doc: A_BossDeath Possibly trigger special effects if on first boss level

### A_Hoof `void A_Hoof (mobj_t* mo)`
- Defined: `progs/doomgeneric/p_enemy.c:1755`

### A_Metal `void A_Metal (mobj_t* mo)`
- Defined: `progs/doomgeneric/p_enemy.c:1762`

### A_BabyMetal `void A_BabyMetal (mobj_t* mo)`
- Defined: `progs/doomgeneric/p_enemy.c:1768`

### A_OpenShotgun2 `void
A_OpenShotgun2
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_enemy.c:1774`

### A_LoadShotgun2 `void
A_LoadShotgun2
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_enemy.c:1782`

### A_CloseShotgun2 `void
A_CloseShotgun2
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_enemy.c:1795`

### A_BrainAwake `void A_BrainAwake (mobj_t* mo)`
- Defined: `progs/doomgeneric/p_enemy.c:1810`

### A_BrainPain `void A_BrainPain (mobj_t*	mo)`
- Defined: `progs/doomgeneric/p_enemy.c:1839`

### A_BrainScream `void A_BrainScream (mobj_t*	mo)`
- Defined: `progs/doomgeneric/p_enemy.c:1845`

### A_BrainExplode `void A_BrainExplode (mobj_t* mo)`
- Defined: `progs/doomgeneric/p_enemy.c:1870`

### A_BrainDie `void A_BrainDie (mobj_t*	mo)`
- Defined: `progs/doomgeneric/p_enemy.c:1892`

### A_BrainSpit `void A_BrainSpit (mobj_t*	mo)`
- Defined: `progs/doomgeneric/p_enemy.c:1898`

### A_SpawnSound `void A_SpawnSound (mobj_t* mo)`
- Defined: `progs/doomgeneric/p_enemy.c:1928`
- Doc: travelling cube sound

### A_SpawnFly `void A_SpawnFly (mobj_t* mo)`
- Defined: `progs/doomgeneric/p_enemy.c:1933`

### A_PlayerScream `void A_PlayerScream (mobj_t* mo)`
- Defined: `progs/doomgeneric/p_enemy.c:1989`

## progs/doomgeneric/p_floor.c

### T_MovePlane `result_e
T_MovePlane
( sector_t*	sector,
  fixed_t	speed,
  fixed_t	dest,
  boolean	crush,
  int	...`
- Defined: `progs/doomgeneric/p_floor.c:41`
- Doc: Move a plane (floor or ceiling) and check for crushing

### T_MoveFloor `void T_MoveFloor(floormove_t* floor)`
- Defined: `progs/doomgeneric/p_floor.c:202`
- Doc: MOVE A FLOOR TO IT'S DESTINATION (UP OR DOWN)

### EV_DoFloor `int
EV_DoFloor
( line_t*	line,
  floor_e	floortype )`
- Defined: `progs/doomgeneric/p_floor.c:250`
- Doc: HANDLE FLOOR TYPES

### EV_BuildStairs `int
EV_BuildStairs
( line_t*	line,
  stair_e	type )`
- Defined: `progs/doomgeneric/p_floor.c:443`
- Doc: BUILD A STAIRCASE!

## progs/doomgeneric/p_inter.c

### P_GiveAmmo `boolean
P_GiveAmmo
( player_t*	player,
  ammotype_t	ammo,
  int		num )`
- Defined: `progs/doomgeneric/p_inter.c:64`
- Doc: P_GiveAmmo Num is the number of clip loads, not the individual count (0= 1/2 clip). Returns false if the ammo can't be p

### P_GiveWeapon `boolean
P_GiveWeapon
( player_t*	player,
  weapontype_t	weapon,
  boolean	dropped )`
- Defined: `progs/doomgeneric/p_inter.c:159`
- Doc: P_GiveWeapon The weapon name may have a MF_DROPPED flag ored in.

### P_GiveBody `boolean
P_GiveBody
( player_t*	player,
  int		num )`
- Defined: `progs/doomgeneric/p_inter.c:222`
- Doc: P_GiveBody Returns false if the body isn't needed at all

### P_GiveArmor `boolean
P_GiveArmor
( player_t*	player,
  int		armortype )`
- Defined: `progs/doomgeneric/p_inter.c:245`
- Doc: P_GiveArmor Returns false if the armor is worse than the current armor.

### P_GiveCard `void
P_GiveCard
( player_t*	player,
  card_t	card )`
- Defined: `progs/doomgeneric/p_inter.c:267`
- Doc: P_GiveCard

### P_GivePower `boolean
P_GivePower
( player_t*	player,
  int /*powertype_t*/	power )`
- Defined: `progs/doomgeneric/p_inter.c:283`
- Doc: P_GivePower

### P_TouchSpecialThing `void
P_TouchSpecialThing
( mobj_t*	special,
  mobj_t*	toucher )`
- Defined: `progs/doomgeneric/p_inter.c:332`
- Doc: P_TouchSpecialThing

### P_KillMobj `void
P_KillMobj
( mobj_t*	source,
  mobj_t*	target )`
- Defined: `progs/doomgeneric/p_inter.c:665`
- Doc: KillMobj

### P_DamageMobj `void
P_DamageMobj
( mobj_t*	target,
  mobj_t*	inflictor,
  mobj_t*	source,
  int 		damage )`
- Defined: `progs/doomgeneric/p_inter.c:778`
- Doc: P_DamageMobj Damages both enemies and players "inflictor" is the thing that caused the damage creature or missile, can b

## progs/doomgeneric/p_lights.c

### T_FireFlicker `void T_FireFlicker (fireflicker_t* flick)`
- Defined: `progs/doomgeneric/p_lights.c:39`
- Doc: T_FireFlicker

### P_SpawnFireFlicker `void P_SpawnFireFlicker (sector_t*	sector)`
- Defined: `progs/doomgeneric/p_lights.c:61`
- Doc: P_SpawnFireFlicker

### T_LightFlash `void T_LightFlash (lightflash_t* flash)`
- Defined: `progs/doomgeneric/p_lights.c:91`
- Doc: T_LightFlash Do flashing lights.

### P_SpawnLightFlash `void P_SpawnLightFlash (sector_t*	sector)`
- Defined: `progs/doomgeneric/p_lights.c:117`
- Doc: P_SpawnLightFlash After the map has been loaded, scan each sector for specials that spawn thinkers

### T_StrobeFlash `void T_StrobeFlash (strobe_t*		flash)`
- Defined: `progs/doomgeneric/p_lights.c:148`
- Doc: T_StrobeFlash

### P_SpawnStrobeFlash `void
P_SpawnStrobeFlash
( sector_t*	sector,
  int		fastOrSlow,
  int		inSync )`
- Defined: `progs/doomgeneric/p_lights.c:173`
- Doc: P_SpawnStrobeFlash After the map has been loaded, scan each sector for specials that spawn thinkers

### EV_StartLightStrobing `void EV_StartLightStrobing(line_t*	line)`
- Defined: `progs/doomgeneric/p_lights.c:208`
- Doc: Start strobing lights (usually from a trigger)

### EV_TurnTagLightsOff `void EV_TurnTagLightsOff(line_t* line)`
- Defined: `progs/doomgeneric/p_lights.c:229`
- Doc: TURN LINE'S TAG LIGHTS OFF

### EV_LightTurnOn `void
EV_LightTurnOn
( line_t*	line,
  int		bright )`
- Defined: `progs/doomgeneric/p_lights.c:263`
- Doc: TURN LINE'S TAG LIGHTS ON

### T_Glow `void T_Glow(glow_t*	g)`
- Defined: `progs/doomgeneric/p_lights.c:306`
- Doc: Spawn glowing light

### P_SpawnGlowingLight `void P_SpawnGlowingLight(sector_t*	sector)`
- Defined: `progs/doomgeneric/p_lights.c:332`

## progs/doomgeneric/p_map.c

### PIT_StompThing `boolean PIT_StompThing (mobj_t* thing)`
- Defined: `progs/doomgeneric/p_map.c:97`
- Doc: PIT_StompThing

### P_TeleportMove `boolean
P_TeleportMove
( mobj_t*	thing,
  fixed_t	x,
  fixed_t	y )`
- Defined: `progs/doomgeneric/p_map.c:130`
- Doc: P_TeleportMove

### PIT_CheckLine `boolean PIT_CheckLine (line_t* ld)`
- Defined: `progs/doomgeneric/p_map.c:206`
- Doc: PIT_CheckLine Adjusts tmfloorz and tmceilingz as lines are contacted

### PIT_CheckThing `boolean PIT_CheckThing (mobj_t* thing)`
- Defined: `progs/doomgeneric/p_map.c:275`
- Doc: PIT_CheckThing

### P_CheckPosition `boolean
P_CheckPosition
( mobj_t*	thing,
  fixed_t	x,
  fixed_t	y )`
- Defined: `progs/doomgeneric/p_map.c:401`
- Doc: during: special things are touched if MF_PICKUP early out on solid lines?  out: newsubsec floorz ceilingz tmdropoffz the

### P_TryMove `boolean
P_TryMove
( mobj_t*	thing,
  fixed_t	x,
  fixed_t	y )`
- Defined: `progs/doomgeneric/p_map.c:477`
- Doc: P_TryMove Attempt to move to a new position, crossing special lines unless MF_TELEPORT is set.

### P_ThingHeightClip `boolean P_ThingHeightClip (mobj_t* thing)`
- Defined: `progs/doomgeneric/p_map.c:557`
- Doc: P_ThingHeightClip Takes a valid thing and adjusts the thing->floorz, thing->ceilingz, and possibly thing->z. This is cal

### P_HitSlideLine `void P_HitSlideLine (line_t* ld)`
- Defined: `progs/doomgeneric/p_map.c:611`
- Doc: P_HitSlideLine Adjusts the xmove / ymove so that the next move will slide along the wall.

### PTR_SlideTraverse `boolean PTR_SlideTraverse (intercept_t* in)`
- Defined: `progs/doomgeneric/p_map.c:663`
- Doc: PTR_SlideTraverse

### P_SlideMove `void P_SlideMove (mobj_t* mo)`
- Defined: `progs/doomgeneric/p_map.c:722`
- Doc: P_SlideMove The momx / momy move is bad, so try to slide along a wall. Find the first line hit, move flush to it, and sl

### PTR_AimTraverse `boolean
PTR_AimTraverse (intercept_t* in)`
- Defined: `progs/doomgeneric/p_map.c:842`
- Doc: PTR_AimTraverse Sets linetaget and aimslope when a target is aimed at.

### PTR_ShootTraverse `boolean PTR_ShootTraverse (intercept_t* in)`
- Defined: `progs/doomgeneric/p_map.c:928`
- Doc: PTR_ShootTraverse

### P_AimLineAttack `fixed_t
P_AimLineAttack
( mobj_t*	t1,
  angle_t	angle,
  fixed_t	distance )`
- Defined: `progs/doomgeneric/p_map.c:1067`
- Doc: P_AimLineAttack

### P_LineAttack `void
P_LineAttack
( mobj_t*	t1,
  angle_t	angle,
  fixed_t	distance,
  fixed_t	slope,
  int		dama...`
- Defined: `progs/doomgeneric/p_map.c:1109`
- Doc: P_LineAttack If damage == 0, it is just a test trace that will leave linetarget set.

### PTR_UseTraverse `boolean	PTR_UseTraverse (intercept_t* in)`
- Defined: `progs/doomgeneric/p_map.c:1141`

### P_UseLines `void P_UseLines (player_t*	player)`
- Defined: `progs/doomgeneric/p_map.c:1177`
- Doc: P_UseLines Looks for special lines in front of the player to activate.

### PIT_RadiusAttack `boolean PIT_RadiusAttack (mobj_t* thing)`
- Defined: `progs/doomgeneric/p_map.c:1211`
- Doc: PIT_RadiusAttack "bombsource" is the creature that caused the explosion at "bombspot".

### P_RadiusAttack `void
P_RadiusAttack
( mobj_t*	spot,
  mobj_t*	source,
  int		damage )`
- Defined: `progs/doomgeneric/p_map.c:1252`
- Doc: P_RadiusAttack Source is the creature that caused the explosion at spot.

### PIT_ChangeSector `boolean PIT_ChangeSector (mobj_t*	thing)`
- Defined: `progs/doomgeneric/p_map.c:1304`
- Doc: PIT_ChangeSector

### P_ChangeSector `boolean
P_ChangeSector
( sector_t*	sector,
  boolean	crunch )`
- Defined: `progs/doomgeneric/p_map.c:1367`
- Doc: P_ChangeSector

### SpechitOverrun `static void SpechitOverrun(line_t *ld)`
- Defined: `progs/doomgeneric/p_map.c:1390`
- Doc: Code to emulate the behavior of Vanilla Doom when encountering an overrun of the spechit array.  This is by Andrey Budko

## progs/doomgeneric/p_maputl.c

### P_AproxDistance `fixed_t
P_AproxDistance
( fixed_t	dx,
  fixed_t	dy )`
- Defined: `progs/doomgeneric/p_maputl.c:42`
- Doc: P_AproxDistance Gives an estimation of distance (not exact)

### P_PointOnLineSide `int
P_PointOnLineSide
( fixed_t	x,
  fixed_t	y,
  line_t*	line )`
- Defined: `progs/doomgeneric/p_maputl.c:60`
- Doc: P_PointOnLineSide Returns 0 or 1

### P_BoxOnLineSide `int
P_BoxOnLineSide
( fixed_t*	tmbox,
  line_t*	ld )`
- Defined: `progs/doomgeneric/p_maputl.c:104`
- Doc: P_BoxOnLineSide Considers the line to be infinite Returns side 0 or 1, -1 if box crosses the line.

### P_PointOnDivlineSide `int
P_PointOnDivlineSide
( fixed_t	x,
  fixed_t	y,
  divline_t*	line )`
- Defined: `progs/doomgeneric/p_maputl.c:155`
- Doc: P_PointOnDivlineSide Returns 0 or 1.

### P_MakeDivline `void
P_MakeDivline
( line_t*	li,
  divline_t*	dl )`
- Defined: `progs/doomgeneric/p_maputl.c:205`
- Doc: P_MakeDivline

### P_InterceptVector `fixed_t
P_InterceptVector
( divline_t*	v2,
  divline_t*	v1 )`
- Defined: `progs/doomgeneric/p_maputl.c:225`
- Doc: P_InterceptVector Returns the fractional intercept point along the first divline. This is only called by the addthings a

### P_LineOpening `void P_LineOpening (line_t* linedef)`
- Defined: `progs/doomgeneric/p_maputl.c:293`

### P_UnsetThingPosition `void P_UnsetThingPosition (mobj_t* thing)`
- Defined: `progs/doomgeneric/p_maputl.c:342`
- Doc: P_UnsetThingPosition Unlinks a thing from block map and sectors. On each position change, BLOCKMAP and other lookups mai

### P_SetThingPosition `void
P_SetThingPosition (mobj_t* thing)`
- Defined: `progs/doomgeneric/p_maputl.c:390`
- Doc: P_SetThingPosition Links a thing into both a block and a subsector based on it's x y. Sets thing->subsector properly

### P_BlockLinesIterator `boolean
P_BlockLinesIterator
( int			x,
  int			y,
  boolean(*func)(line_t*) )`
- Defined: `progs/doomgeneric/p_maputl.c:466`
- Doc: P_BlockLinesIterator The validcount flags are used to avoid checking lines that are marked in multiple mapblocks, so inc

### P_BlockThingsIterator `boolean
P_BlockThingsIterator
( int			x,
  int			y,
  boolean(*func)(mobj_t*) )`
- Defined: `progs/doomgeneric/p_maputl.c:507`
- Doc: P_BlockThingsIterator

### PIT_AddLineIntercepts `boolean
PIT_AddLineIntercepts (line_t* ld)`
- Defined: `progs/doomgeneric/p_maputl.c:558`
- Doc: PIT_AddLineIntercepts. Looks for lines in the given block that intercept the given trace to add to the intercepts list. 

### PIT_AddThingIntercepts `boolean PIT_AddThingIntercepts (mobj_t* thing)`
- Defined: `progs/doomgeneric/p_maputl.c:614`
- Doc: PIT_AddThingIntercepts

### P_TraverseIntercepts `boolean
P_TraverseIntercepts
( traverser_t	func,
  fixed_t	maxfrac )`
- Defined: `progs/doomgeneric/p_maputl.c:681`
- Doc: P_TraverseIntercepts Returns true if the traverser function returns true for all lines.

### InterceptsMemoryOverrun `static void InterceptsMemoryOverrun(int location, int value)`
- Defined: `progs/doomgeneric/p_maputl.c:781`
- Doc: Overwrite a specific memory location with a value.

### InterceptsOverrun `static void InterceptsOverrun(int num_intercepts, intercept_t *intercept)`
- Defined: `progs/doomgeneric/p_maputl.c:826`
- Doc: Emulate overruns of the intercepts[] array.

### P_PathTraverse `boolean
P_PathTraverse
( fixed_t		x1,
  fixed_t		y1,
  fixed_t		x2,
  fixed_t		y2,
  int			flags,...`
- Defined: `progs/doomgeneric/p_maputl.c:860`
- Doc: P_PathTraverse Traces a line from x1,y1 to x2,y2, calling the traverser function for each. Returns true if the traverser

## progs/doomgeneric/p_mobj.c

### P_SetMobjState `boolean
P_SetMobjState
( mobj_t*	mobj,
  statenum_t	state )`
- Defined: `progs/doomgeneric/p_mobj.c:46`

### P_ExplodeMissile `void P_ExplodeMissile (mobj_t* mo)`
- Defined: `progs/doomgeneric/p_mobj.c:84`
- Doc: P_ExplodeMissile

### P_XYMovement `void P_XYMovement (mobj_t* mo)`
- Defined: `progs/doomgeneric/p_mobj.c:107`
- Doc: P_XYMovement  define STOPSPEED		0x1000 define FRICTION		0xe800

### P_ZMovement `void P_ZMovement (mobj_t* mo)`
- Defined: `progs/doomgeneric/p_mobj.c:240`
- Doc: P_ZMovement

### P_NightmareRespawn `void
P_NightmareRespawn (mobj_t* mobj)`
- Defined: `progs/doomgeneric/p_mobj.c:382`
- Doc: P_NightmareRespawn

### P_MobjThinker `void P_MobjThinker (mobj_t* mobj)`
- Defined: `progs/doomgeneric/p_mobj.c:441`
- Doc: P_MobjThinker

### P_SpawnMobj `mobj_t*
P_SpawnMobj
( fixed_t	x,
  fixed_t	y,
  fixed_t	z,
  mobjtype_t	type )`
- Defined: `progs/doomgeneric/p_mobj.c:505`
- Doc: P_SpawnMobj

### P_RemoveMobj `void P_RemoveMobj (mobj_t* mobj)`
- Defined: `progs/doomgeneric/p_mobj.c:570`

### P_RespawnSpecials `void P_RespawnSpecials (void)`
- Defined: `progs/doomgeneric/p_mobj.c:604`
- Doc: P_RespawnSpecials

### P_SpawnPlayer `void P_SpawnPlayer (mapthing_t* mthing)`
- Defined: `progs/doomgeneric/p_mobj.c:668`
- Doc: P_SpawnPlayer Called when a player is spawned on the level. Most of the player structure stays unchanged between levels.

### P_SpawnMapThing `void P_SpawnMapThing (mapthing_t* mthing)`
- Defined: `progs/doomgeneric/p_mobj.c:739`
- Doc: P_SpawnMapThing The fields of the mapthing should already be in host byte order.

### P_SpawnPuff `void
P_SpawnPuff
( fixed_t	x,
  fixed_t	y,
  fixed_t	z )`
- Defined: `progs/doomgeneric/p_mobj.c:849`

### P_SpawnBlood `void
P_SpawnBlood
( fixed_t	x,
  fixed_t	y,
  fixed_t	z,
  int		damage )`
- Defined: `progs/doomgeneric/p_mobj.c:877`
- Doc: P_SpawnBlood

### P_CheckMissileSpawn `void P_CheckMissileSpawn (mobj_t* th)`
- Defined: `progs/doomgeneric/p_mobj.c:907`
- Doc: P_CheckMissileSpawn Moves the missile forward a bit and possibly explodes it right there.

### P_SubstNullMobj `mobj_t *P_SubstNullMobj(mobj_t *mobj)`
- Defined: `progs/doomgeneric/p_mobj.c:928`
- Doc: Certain functions assume that a mobj_t pointer is non-NULL, causing a crash in some situations where it is NULL.  Vanill

### P_SpawnMissile `mobj_t*
P_SpawnMissile
( mobj_t*	source,
  mobj_t*	dest,
  mobjtype_t	type )`
- Defined: `progs/doomgeneric/p_mobj.c:949`
- Doc: P_SpawnMissile

### P_SpawnPlayerMissile `void
P_SpawnPlayerMissile
( mobj_t*	source,
  mobjtype_t	type )`
- Defined: `progs/doomgeneric/p_mobj.c:995`
- Doc: P_SpawnPlayerMissile Tries to aim at a nearby monster

## progs/doomgeneric/p_plats.c

### T_PlatRaise `void T_PlatRaise(plat_t* plat)`
- Defined: `progs/doomgeneric/p_plats.c:45`
- Doc: Move a plat up and down

### EV_DoPlat `int
EV_DoPlat
( line_t*	line,
  plattype_e	type,
  int		amount )`
- Defined: `progs/doomgeneric/p_plats.c:128`
- Doc: Do Platforms "amount" is only used for SOME platforms.

### P_ActivateInStasis `void P_ActivateInStasis(int tag)`
- Defined: `progs/doomgeneric/p_plats.c:245`

### EV_StopPlat `void EV_StopPlat(line_t* line)`
- Defined: `progs/doomgeneric/p_plats.c:262`

### P_AddActivePlat `void P_AddActivePlat(plat_t* plat)`
- Defined: `progs/doomgeneric/p_plats.c:277`

### P_RemoveActivePlat `void P_RemoveActivePlat(plat_t* plat)`
- Defined: `progs/doomgeneric/p_plats.c:290`

## progs/doomgeneric/p_pspr.c

### P_SetPsprite `void
P_SetPsprite
( player_t*	player,
  int		position,
  statenum_t	stnum )`
- Defined: `progs/doomgeneric/p_pspr.c:49`
- Doc: P_SetPsprite

### P_CalcSwing `void P_CalcSwing (player_t*	player)`
- Defined: `progs/doomgeneric/p_pspr.c:102`

### P_BringUpWeapon `void P_BringUpWeapon (player_t* player)`
- Defined: `progs/doomgeneric/p_pspr.c:129`
- Doc: P_BringUpWeapon Starts bringing the pending weapon up from the bottom of the screen. Uses player

### P_CheckAmmo `boolean P_CheckAmmo (player_t* player)`
- Defined: `progs/doomgeneric/p_pspr.c:152`
- Doc: P_CheckAmmo Returns true if there is enough ammo to shoot. If not, selects the next weapon to use.

### P_FireWeapon `void P_FireWeapon (player_t* player)`
- Defined: `progs/doomgeneric/p_pspr.c:237`
- Doc: P_FireWeapon.

### P_DropWeapon `void P_DropWeapon (player_t* player)`
- Defined: `progs/doomgeneric/p_pspr.c:256`
- Doc: P_DropWeapon Player died, so put the weapon away.

### A_WeaponReady `void
A_WeaponReady
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_pspr.c:272`
- Doc: A_WeaponReady The player can fire the weapon or change to another weapon at this time. Follows after getting weapon up, 

### A_ReFire `void A_ReFire
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_pspr.c:334`
- Doc: A_ReFire The player can re-fire the weapon without lowering it entirely.

### A_CheckReload `void
A_CheckReload
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_pspr.c:354`

### A_Lower `void
A_Lower
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_pspr.c:375`
- Doc: A_Lower Lowers current weapon, and changes weapon at bottom.

### A_Raise `void
A_Raise
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_pspr.c:413`
- Doc: A_Raise

### A_GunFlash `void
A_GunFlash
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_pspr.c:439`
- Doc: A_GunFlash

### A_Punch `void
A_Punch
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_pspr.c:458`
- Doc: A_Punch

### A_Saw `void
A_Saw
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_pspr.c:492`
- Doc: A_Saw

### DecreaseAmmo `static void DecreaseAmmo(player_t *player, int ammonum, int amount)`
- Defined: `progs/doomgeneric/p_pspr.c:541`
- Doc: Doom does not check the bounds of the ammo array.  As a result, it is possible to use an ammo type > 4 that overflows in

### A_FireMissile `void
A_FireMissile
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_pspr.c:558`
- Doc: A_FireMissile

### A_FireBFG `void
A_FireBFG
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_pspr.c:571`
- Doc: A_FireBFG

### A_FirePlasma `void
A_FirePlasma
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_pspr.c:586`
- Doc: A_FirePlasma

### P_BulletSlope `void P_BulletSlope (mobj_t*	mo)`
- Defined: `progs/doomgeneric/p_pspr.c:608`

### P_GunShot `void
P_GunShot
( mobj_t*	mo,
  boolean	accurate )`
- Defined: `progs/doomgeneric/p_pspr.c:634`
- Doc: P_GunShot

### A_FirePistol `void
A_FirePistol
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_pspr.c:655`
- Doc: A_FirePistol

### A_FireShotgun `void
A_FireShotgun
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_pspr.c:677`
- Doc: A_FireShotgun

### A_FireShotgun2 `void
A_FireShotgun2
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_pspr.c:704`
- Doc: A_FireShotgun2

### A_FireCGun `void
A_FireCGun
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_pspr.c:741`
- Doc: A_FireCGun

### A_Light0 `void A_Light0 (player_t *player, pspdef_t *psp)`
- Defined: `progs/doomgeneric/p_pspr.c:770`
- Doc: ?

### A_Light1 `void A_Light1 (player_t *player, pspdef_t *psp)`
- Defined: `progs/doomgeneric/p_pspr.c:774`

### A_Light2 `void A_Light2 (player_t *player, pspdef_t *psp)`
- Defined: `progs/doomgeneric/p_pspr.c:779`

### A_BFGSpray `void A_BFGSpray (mobj_t* mo)`
- Defined: `progs/doomgeneric/p_pspr.c:790`
- Doc: A_BFGSpray Spawn a BFG explosion on every monster in view

### A_BFGsound `void
A_BFGsound
( player_t*	player,
  pspdef_t*	psp )`
- Defined: `progs/doomgeneric/p_pspr.c:826`
- Doc: A_BFGsound

### P_SetupPsprites `void P_SetupPsprites (player_t* player)`
- Defined: `progs/doomgeneric/p_pspr.c:840`
- Doc: P_SetupPsprites Called at start of level for each player.

### P_MovePsprites `void P_MovePsprites (player_t* player)`
- Defined: `progs/doomgeneric/p_pspr.c:860`
- Doc: P_MovePsprites Called every tic by player thinking routine.

## progs/doomgeneric/p_saveg.c

### P_TempSaveGameFile `char *P_TempSaveGameFile(void)`
- Defined: `progs/doomgeneric/p_saveg.c:46`
- Doc: Get the filename of a temporary file to write the savegame to.  After the file has been successfully saved, it will be r

### P_SaveGameFile `char *P_SaveGameFile(int slot)`
- Defined: `progs/doomgeneric/p_saveg.c:60`
- Doc: Get the filename of the save game file to use for the specified slot.

### saveg_read8 `static byte saveg_read8(void)`
- Defined: `progs/doomgeneric/p_saveg.c:80`
- Doc: Endian-safe integer read/write functions

### saveg_write8 `static void saveg_write8(byte value)`
- Defined: `progs/doomgeneric/p_saveg.c:98`

### saveg_read16 `static short saveg_read16(void)`
- Defined: `progs/doomgeneric/p_saveg.c:111`

### saveg_write16 `static void saveg_write16(short value)`
- Defined: `progs/doomgeneric/p_saveg.c:121`

### saveg_read32 `static int saveg_read32(void)`
- Defined: `progs/doomgeneric/p_saveg.c:127`

### saveg_write32 `static void saveg_write32(int value)`
- Defined: `progs/doomgeneric/p_saveg.c:139`

### saveg_read_pad `static void saveg_read_pad(void)`
- Defined: `progs/doomgeneric/p_saveg.c:149`
- Doc: Pad to 4-byte boundaries

### saveg_write_pad `static void saveg_write_pad(void)`
- Defined: `progs/doomgeneric/p_saveg.c:165`

### saveg_readp `static void *saveg_readp(void)`
- Defined: `progs/doomgeneric/p_saveg.c:184`
- Doc: Pointers

### saveg_writep `static void saveg_writep(void *p)`
- Defined: `progs/doomgeneric/p_saveg.c:189`

### saveg_read_mapthing_t `static void saveg_read_mapthing_t(mapthing_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:207`
- Doc: mapthing_t

### saveg_write_mapthing_t `static void saveg_write_mapthing_t(mapthing_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:225`

### saveg_read_actionf_t `static void saveg_read_actionf_t(actionf_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:247`
- Doc: actionf_t

### saveg_write_actionf_t `static void saveg_write_actionf_t(actionf_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:253`

### saveg_read_thinker_t `static void saveg_read_thinker_t(thinker_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:272`
- Doc: thinker_t

### saveg_write_thinker_t `static void saveg_write_thinker_t(thinker_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:284`

### saveg_read_mobj_t `static void saveg_read_mobj_t(mobj_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:300`
- Doc: mobj_t

### saveg_write_mobj_t `static void saveg_write_mobj_t(mobj_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:420`

### saveg_read_ticcmd_t `static void saveg_read_ticcmd_t(ticcmd_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:540`
- Doc: ticcmd_t

### saveg_write_ticcmd_t `static void saveg_write_ticcmd_t(ticcmd_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:562`

### saveg_read_pspdef_t `static void saveg_read_pspdef_t(pspdef_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:588`
- Doc: pspdef_t

### saveg_write_pspdef_t `static void saveg_write_pspdef_t(pspdef_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:614`

### saveg_read_player_t `static void saveg_read_player_t(player_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:640`
- Doc: player_t

### saveg_write_player_t `static void saveg_write_player_t(player_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:771`

### saveg_read_ceiling_t `static void saveg_read_ceiling_t(ceiling_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:907`
- Doc: ceiling_t

### saveg_write_ceiling_t `static void saveg_write_ceiling_t(ceiling_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:943`

### saveg_read_vldoor_t `static void saveg_read_vldoor_t(vldoor_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:980`
- Doc: vldoor_t

### saveg_write_vldoor_t `static void saveg_write_vldoor_t(vldoor_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:1010`

### saveg_read_floormove_t `static void saveg_read_floormove_t(floormove_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:1041`
- Doc: floormove_t

### saveg_write_floormove_t `static void saveg_write_floormove_t(floormove_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:1074`

### saveg_read_plat_t `static void saveg_read_plat_t(plat_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:1108`
- Doc: plat_t

### saveg_write_plat_t `static void saveg_write_plat_t(plat_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:1150`

### saveg_read_lightflash_t `static void saveg_read_lightflash_t(lightflash_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:1193`
- Doc: lightflash_t

### saveg_write_lightflash_t `static void saveg_write_lightflash_t(lightflash_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:1220`

### saveg_read_strobe_t `static void saveg_read_strobe_t(strobe_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:1248`
- Doc: strobe_t

### saveg_write_strobe_t `static void saveg_write_strobe_t(strobe_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:1275`

### saveg_read_glow_t `static void saveg_read_glow_t(glow_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:1303`
- Doc: glow_t

### saveg_write_glow_t `static void saveg_write_glow_t(glow_t *str)`
- Defined: `progs/doomgeneric/p_saveg.c:1324`

### P_WriteSaveGameHeader `void P_WriteSaveGameHeader(char *description)`
- Defined: `progs/doomgeneric/p_saveg.c:1346`
- Doc: Write the header for a savegame

### P_ReadSaveGameHeader `boolean P_ReadSaveGameHeader(void)`
- Defined: `progs/doomgeneric/p_saveg.c:1378`
- Doc: Read the header for a savegame

### P_ReadSaveGameEOF `boolean P_ReadSaveGameEOF(void)`
- Defined: `progs/doomgeneric/p_saveg.c:1418`
- Doc: Read the end of file marker.  Returns true if read successfully.

### P_WriteSaveGameEOF `void P_WriteSaveGameEOF(void)`
- Defined: `progs/doomgeneric/p_saveg.c:1431`
- Doc: Write the end of file marker

### P_ArchivePlayers `void P_ArchivePlayers (void)`
- Defined: `progs/doomgeneric/p_saveg.c:1440`
- Doc: P_ArchivePlayers

### P_UnArchivePlayers `void P_UnArchivePlayers (void)`
- Defined: `progs/doomgeneric/p_saveg.c:1460`
- Doc: P_UnArchivePlayers

### P_ArchiveWorld `void P_ArchiveWorld (void)`
- Defined: `progs/doomgeneric/p_saveg.c:1484`
- Doc: P_ArchiveWorld

### P_UnArchiveWorld `void P_UnArchiveWorld (void)`
- Defined: `progs/doomgeneric/p_saveg.c:1532`
- Doc: P_UnArchiveWorld

### P_ArchiveThinkers `void P_ArchiveThinkers (void)`
- Defined: `progs/doomgeneric/p_saveg.c:1592`
- Doc: P_ArchiveThinkers

### P_UnArchiveThinkers `void P_UnArchiveThinkers (void)`
- Defined: `progs/doomgeneric/p_saveg.c:1620`
- Doc: P_UnArchiveThinkers

### P_ArchiveSpecials `void P_ArchiveSpecials (void)`
- Defined: `progs/doomgeneric/p_saveg.c:1704`
- Doc: Things to handle:  T_MoveCeiling, (ceiling_t: sector_t * swizzle), - active list T_VerticalDoor, (vldoor_t: sector_t * s

### P_UnArchiveSpecials `void P_UnArchiveSpecials (void)`
- Defined: `progs/doomgeneric/p_saveg.c:1793`
- Doc: P_UnArchiveSpecials

## progs/doomgeneric/p_setup.c

### P_LoadVertexes `void P_LoadVertexes (int lump)`
- Defined: `progs/doomgeneric/p_setup.c:118`
- Doc: P_LoadVertexes

### GetSectorAtNullAddress `sector_t* GetSectorAtNullAddress(void)`
- Defined: `progs/doomgeneric/p_setup.c:153`
- Doc: GetSectorAtNullAddress

### P_LoadSegs `void P_LoadSegs (int lump)`
- Defined: `progs/doomgeneric/p_setup.c:172`
- Doc: P_LoadSegs

### P_LoadSubsectors `void P_LoadSubsectors (int lump)`
- Defined: `progs/doomgeneric/p_setup.c:236`
- Doc: P_LoadSubsectors

### P_LoadSectors `void P_LoadSectors (int lump)`
- Defined: `progs/doomgeneric/p_setup.c:265`
- Doc: P_LoadSectors

### P_LoadNodes `void P_LoadNodes (int lump)`
- Defined: `progs/doomgeneric/p_setup.c:298`
- Doc: P_LoadNodes

### P_LoadThings `void P_LoadThings (int lump)`
- Defined: `progs/doomgeneric/p_setup.c:335`
- Doc: P_LoadThings

### P_LoadLineDefs `void P_LoadLineDefs (int lump)`
- Defined: `progs/doomgeneric/p_setup.c:392`
- Doc: P_LoadLineDefs Also counts secret lines for intermissions.

### P_LoadSideDefs `void P_LoadSideDefs (int lump)`
- Defined: `progs/doomgeneric/p_setup.c:473`
- Doc: P_LoadSideDefs

### P_LoadBlockMap `void P_LoadBlockMap (int lump)`
- Defined: `progs/doomgeneric/p_setup.c:504`
- Doc: P_LoadBlockMap

### P_GroupLines `void P_GroupLines (void)`
- Defined: `progs/doomgeneric/p_setup.c:545`
- Doc: P_GroupLines Builds sector line lists and subsector sector numbers. Finds block bounding boxes for sectors.

### PadRejectArray `static void PadRejectArray(byte *array, unsigned int len)`
- Defined: `progs/doomgeneric/p_setup.c:660`
- Doc: Pad the REJECT lump with extra data when the lump is too small, to simulate a REJECT buffer overflow in Vanilla Doom.

### P_LoadReject `static void P_LoadReject(int lumpnum)`
- Defined: `progs/doomgeneric/p_setup.c:711`

### P_SetupLevel `void
P_SetupLevel
( int		episode,
  int		map,
  int		playermask,
  skill_t	skill)`
- Defined: `progs/doomgeneric/p_setup.c:743`
- Doc: P_SetupLevel

### P_Init `void P_Init (void)`
- Defined: `progs/doomgeneric/p_setup.c:847`
- Doc: P_Init

## progs/doomgeneric/p_sight.c

### P_DivlineSide `int
P_DivlineSide
( fixed_t	x,
  fixed_t	y,
  divline_t*	node )`
- Defined: `progs/doomgeneric/p_sight.c:47`
- Doc: P_DivlineSide Returns side 0 (front), 1 (back), or 2 (on).

### P_InterceptVector2 `fixed_t
P_InterceptVector2
( divline_t*	v2,
  divline_t*	v1 )`
- Defined: `progs/doomgeneric/p_sight.c:101`
- Doc: P_InterceptVector2 Returns the fractional intercept point along the first divline. This is only called by the addthings 

### P_CrossSubsector `boolean P_CrossSubsector (int num)`
- Defined: `progs/doomgeneric/p_sight.c:128`
- Doc: P_CrossSubsector Returns true if strace crosses the given subsector successfully.

### P_CrossBSPNode `boolean P_CrossBSPNode (int bspnum)`
- Defined: `progs/doomgeneric/p_sight.c:258`
- Doc: P_CrossBSPNode Returns true if strace crosses the given node successfully.

### P_CheckSight `boolean
P_CheckSight
( mobj_t*	t1,
  mobj_t*	t2 )`
- Defined: `progs/doomgeneric/p_sight.c:300`
- Doc: P_CheckSight Returns true if a straight line between t1 and t2 is unobstructed. Uses REJECT.

## progs/doomgeneric/p_spec.c

### P_InitPicAnims `void P_InitPicAnims (void)`
- Defined: `progs/doomgeneric/p_spec.c:140`

### getSide `side_t*
getSide
( int		currentSector,
  int		line,
  int		side )`
- Defined: `progs/doomgeneric/p_spec.c:202`
- Doc: getSide() Will return a side_t* given the number of the current sector, the line number, and the side (0/1) that you wan

### getSector `sector_t*
getSector
( int		currentSector,
  int		line,
  int		side )`
- Defined: `progs/doomgeneric/p_spec.c:218`
- Doc: getSector() Will return a sector_t* given the number of the current sector, the line number and the side (0/1) that you 

### twoSided `int
twoSided
( int	sector,
  int	line )`
- Defined: `progs/doomgeneric/p_spec.c:233`
- Doc: twoSided() Given the sector number and the line number, it will tell you whether the line is two-sided or not.

### getNextSector `sector_t*
getNextSector
( line_t*	line,
  sector_t*	sec )`
- Defined: `progs/doomgeneric/p_spec.c:249`
- Doc: getNextSector() Return sector_t * of sector next to current. NULL if not two-sided line

### P_FindLowestFloorSurrounding `fixed_t	P_FindLowestFloorSurrounding(sector_t* sec)`
- Defined: `progs/doomgeneric/p_spec.c:269`
- Doc: P_FindLowestFloorSurrounding() FIND LOWEST FLOOR HEIGHT IN SURROUNDING SECTORS

### P_FindHighestFloorSurrounding `fixed_t	P_FindHighestFloorSurrounding(sector_t *sec)`
- Defined: `progs/doomgeneric/p_spec.c:296`
- Doc: P_FindHighestFloorSurrounding() FIND HIGHEST FLOOR HEIGHT IN SURROUNDING SECTORS

### P_FindNextHighestFloor `fixed_t
P_FindNextHighestFloor
( sector_t* sec,
  int       currentheight )`
- Defined: `progs/doomgeneric/p_spec.c:328`
- Doc: 20 adjoining sectors max! define MAX_ADJOINING_SECTORS     20

### P_FindLowestCeilingSurrounding `fixed_t
P_FindLowestCeilingSurrounding(sector_t* sec)`
- Defined: `progs/doomgeneric/p_spec.c:391`
- Doc: FIND LOWEST CEILING IN THE SURROUNDING SECTORS

### P_FindHighestCeilingSurrounding `fixed_t	P_FindHighestCeilingSurrounding(sector_t* sec)`
- Defined: `progs/doomgeneric/p_spec.c:417`
- Doc: FIND HIGHEST CEILING IN THE SURROUNDING SECTORS

### P_FindSectorFromLineTag `int
P_FindSectorFromLineTag
( line_t*	line,
  int		start )`
- Defined: `progs/doomgeneric/p_spec.c:443`
- Doc: RETURN NEXT SECTOR # THAT LINE TAG REFERS TO

### P_FindMinSurroundingLight `int
P_FindMinSurroundingLight
( sector_t*	sector,
  int		max )`
- Defined: `progs/doomgeneric/p_spec.c:463`
- Doc: Find minimum light from an adjacent sector

### P_CrossSpecialLine `void
P_CrossSpecialLine
( int		linenum,
  int		side,
  mobj_t*	thing )`
- Defined: `progs/doomgeneric/p_spec.c:501`
- Doc: P_CrossSpecialLine - TRIGGER Called every time a thing origin is about to cross a line with a non 0 special.

### P_ShootSpecialLine `void
P_ShootSpecialLine
( mobj_t*	thing,
  line_t*	line )`
- Defined: `progs/doomgeneric/p_spec.c:968`
- Doc: P_ShootSpecialLine - IMPACT SPECIALS Called when a thing shoots a special line.

### P_PlayerInSpecialSector `void P_PlayerInSpecialSector (player_t* player)`
- Defined: `progs/doomgeneric/p_spec.c:1019`
- Doc: P_PlayerInSpecialSector Called every tic frame that the player origin is in a special sector

### P_UpdateSpecials `void P_UpdateSpecials (void)`
- Defined: `progs/doomgeneric/p_spec.c:1092`

### DonutOverrun `static void DonutOverrun(fixed_t *s3_floorheight, short *s3_floorpic,
                         li...`
- Defined: `progs/doomgeneric/p_spec.c:1177`
- Doc: define DONUT_FLOORHEIGHT_DEFAULT 0x00000000 define DONUT_FLOORPIC_DEFAULT 0x16

### EV_DoDonut `int EV_DoDonut(line_t*	line)`
- Defined: `progs/doomgeneric/p_spec.c:1257`
- Doc: Special Stuff that can not be categorized

### P_SpawnSpecials `void P_SpawnSpecials (void)`
- Defined: `progs/doomgeneric/p_spec.c:1374`
- Doc: Parses command line parameters.

## progs/doomgeneric/p_switch.c

### P_InitSwitchList `void P_InitSwitchList(void)`
- Defined: `progs/doomgeneric/p_switch.c:101`
- Doc: P_InitSwitchList Only called at game initialization.

### P_StartButton `void
P_StartButton
( line_t*	line,
  bwhere_e	w,
  int		texture,
  int		time )`
- Defined: `progs/doomgeneric/p_switch.c:148`
- Doc: Start a button counting down till it turns off.

### P_ChangeSwitchTexture `void
P_ChangeSwitchTexture
( line_t*	line,
  int 		useAgain )`
- Defined: `progs/doomgeneric/p_switch.c:194`
- Doc: Function that changes wall texture. Tell it if switch is ok to use again (1=yes, it's a button).

### P_UseSpecialLine `boolean
P_UseSpecialLine
( mobj_t*	thing,
  line_t*	line,
  int		side )`
- Defined: `progs/doomgeneric/p_switch.c:269`
- Doc: P_UseSpecialLine Called when a thing uses a special line. Only the front sides of lines are usable.

## progs/doomgeneric/p_telept.c

### EV_Teleport `int
EV_Teleport
( line_t*	line,
  int		side,
  mobj_t*	thing )`
- Defined: `progs/doomgeneric/p_telept.c:41`
- Doc: TELEPORTATION

## progs/doomgeneric/p_tick.c

### P_InitThinkers `void P_InitThinkers (void)`
- Defined: `progs/doomgeneric/p_tick.c:46`
- Doc: P_InitThinkers

### P_AddThinker `void P_AddThinker (thinker_t* thinker)`
- Defined: `progs/doomgeneric/p_tick.c:58`
- Doc: P_AddThinker Adds a new thinker at the end of the list.

### P_RemoveThinker `void P_RemoveThinker (thinker_t* thinker)`
- Defined: `progs/doomgeneric/p_tick.c:73`
- Doc: P_RemoveThinker Deallocation is lazy -- it will not actually be freed until its thinking turn comes up.

### P_AllocateThinker `void P_AllocateThinker (thinker_t*	thinker)`
- Defined: `progs/doomgeneric/p_tick.c:85`
- Doc: P_AllocateThinker Allocates memory and adds a new thinker at the end of the list.

### P_RunThinkers `void P_RunThinkers (void)`
- Defined: `progs/doomgeneric/p_tick.c:94`
- Doc: P_RunThinkers

### P_Ticker `void P_Ticker (void)`
- Defined: `progs/doomgeneric/p_tick.c:122`
- Doc: P_Ticker

## progs/doomgeneric/p_user.c

### P_Thrust `void
P_Thrust
( player_t*	player,
  angle_t	angle,
  fixed_t	move )`
- Defined: `progs/doomgeneric/p_user.c:51`
- Doc: P_Thrust Moves the given origin along a given angle.

### P_CalcHeight `void P_CalcHeight (player_t* player)`
- Defined: `progs/doomgeneric/p_user.c:70`
- Doc: P_CalcHeight Calculate the walking / running height adjustment

### P_MovePlayer `void P_MovePlayer (player_t* player)`
- Defined: `progs/doomgeneric/p_user.c:141`
- Doc: P_MovePlayer

### P_DeathThink `void P_DeathThink (player_t* player)`
- Defined: `progs/doomgeneric/p_user.c:174`
- Doc: P_DeathThink Fall on your face when dying. Decrease POV height to floor height.  define ANG5   	(ANG90/18)

### P_PlayerThink `void P_PlayerThink (player_t* player)`
- Defined: `progs/doomgeneric/p_user.c:229`
- Doc: P_PlayerThink

## progs/doomgeneric/r_bsp.c

### R_ClearDrawSegs `void R_ClearDrawSegs (void)`
- Defined: `progs/doomgeneric/r_bsp.c:61`
- Doc: R_ClearDrawSegs

### R_ClipSolidWallSegment `void
R_ClipSolidWallSegment
( int			first,
  int			last )`
- Defined: `progs/doomgeneric/r_bsp.c:96`
- Doc: R_ClipSolidWallSegment Does handle solid walls, e.g. single sided LineDefs (middle texture) that entirely block the view

### R_ClipPassWallSegment `void
R_ClipPassWallSegment
( int	first,
  int	last )`
- Defined: `progs/doomgeneric/r_bsp.c:189`
- Doc: R_ClipPassWallSegment Clips the given range of columns, but does not includes it in the clip list. Does handle windows, 

### R_ClearClipSegs `void R_ClearClipSegs (void)`
- Defined: `progs/doomgeneric/r_bsp.c:238`
- Doc: R_ClearClipSegs

### R_AddLine `void R_AddLine (seg_t*	line)`
- Defined: `progs/doomgeneric/r_bsp.c:252`
- Doc: R_AddLine Clips the given segment and adds any visible pieces to the line list.

### R_CheckBBox `boolean R_CheckBBox (fixed_t*	bspcoord)`
- Defined: `progs/doomgeneric/r_bsp.c:372`

### R_Subsector `void R_Subsector (int num)`
- Defined: `progs/doomgeneric/r_bsp.c:490`
- Doc: R_Subsector Determine floor/ceiling planes. Add sprites of things in sector. Draw one or more line segments.

### R_RenderBSPNode `void R_RenderBSPNode (int bspnum)`
- Defined: `progs/doomgeneric/r_bsp.c:545`
- Doc: RenderBSPNode Renders all subsectors below a given node, traversing subtree recursively. Just call with BSP root.

## progs/doomgeneric/r_data.c

### R_DrawColumnInCache `void
R_DrawColumnInCache
( column_t*	patch,
  byte*		cache,
  int		originy,
  int		cacheheight )`
- Defined: `progs/doomgeneric/r_data.c:185`
- Doc: R_DrawColumnInCache Clip and draw a column from a patch into a cached post.

### R_GenerateComposite `void R_GenerateComposite (int texnum)`
- Defined: `progs/doomgeneric/r_data.c:226`
- Doc: R_GenerateComposite Using the texture definition, the composite texture is created from the patches, and each column is 

### R_GenerateLookup `void R_GenerateLookup (int texnum)`
- Defined: `progs/doomgeneric/r_data.c:294`
- Doc: R_GenerateLookup

### R_GetColumn `byte*
R_GetColumn
( int		tex,
  int		col )`
- Defined: `progs/doomgeneric/r_data.c:382`
- Doc: R_GetColumn

### GenerateTextureHashTable `static void GenerateTextureHashTable(void)`
- Defined: `progs/doomgeneric/r_data.c:402`

### R_InitTextures `void R_InitTextures (void)`
- Defined: `progs/doomgeneric/r_data.c:451`
- Doc: R_InitTextures Initializes the texture list with the textures from the world map.

### R_InitFlats `void R_InitFlats (void)`
- Defined: `progs/doomgeneric/r_data.c:633`
- Doc: R_InitFlats

### R_InitSpriteLumps `void R_InitSpriteLumps (void)`
- Defined: `progs/doomgeneric/r_data.c:655`
- Doc: R_InitSpriteLumps Finds the width and hoffset of all sprites in the wad, so the sprite does not need to be cached comple

### R_InitColormaps `void R_InitColormaps (void)`
- Defined: `progs/doomgeneric/r_data.c:685`
- Doc: R_InitColormaps

### R_InitData `void R_InitData (void)`
- Defined: `progs/doomgeneric/r_data.c:703`
- Doc: R_InitData Locates all the lumps that will be used by all views Must be called after W_Init.

### R_FlatNumForName `int R_FlatNumForName (char* name)`
- Defined: `progs/doomgeneric/r_data.c:720`
- Doc: R_FlatNumForName Retrieval, get a flat number for a flat name.

### R_CheckTextureNumForName `int	R_CheckTextureNumForName (char *name)`
- Defined: `progs/doomgeneric/r_data.c:744`
- Doc: R_CheckTextureNumForName Check whether texture is available. Filter out NoTexture indicator.

### R_TextureNumForName `int	R_TextureNumForName (char* name)`
- Defined: `progs/doomgeneric/r_data.c:775`
- Doc: R_TextureNumForName Calls R_CheckTextureNumForName, aborts with error message.

### R_PrecacheLevel `void R_PrecacheLevel (void)`
- Defined: `progs/doomgeneric/r_data.c:799`

## progs/doomgeneric/r_draw.c

### R_DrawColumn `void R_DrawColumn (void)`
- Defined: `progs/doomgeneric/r_draw.c:102`
- Doc: A column is a vertical slice/span from a wall texture that, given the DOOM style restrictions on the view orientation, w

### R_DrawColumn `void R_DrawColumn (void)`
- Defined: `progs/doomgeneric/r_draw.c:152`
- Doc: UNUSED. Loop unrolled. if 0

### R_DrawColumnLow `void R_DrawColumnLow (void)`
- Defined: `progs/doomgeneric/r_draw.c:206`
- Doc: endif

### R_DrawFuzzColumn `void R_DrawFuzzColumn (void)`
- Defined: `progs/doomgeneric/r_draw.c:283`
- Doc: Framebuffer postprocessing. Creates a fuzzy image by copying pixels from adjacent ones to left and right. Used with an a

### R_DrawFuzzColumnLow `void R_DrawFuzzColumnLow (void)`
- Defined: `progs/doomgeneric/r_draw.c:341`
- Doc: low detail mode version

### R_DrawTranslatedColumn `void R_DrawTranslatedColumn (void)`
- Defined: `progs/doomgeneric/r_draw.c:423`

### R_DrawTranslatedColumnLow `void R_DrawTranslatedColumnLow (void)`
- Defined: `progs/doomgeneric/r_draw.c:467`

### R_InitTranslationTables `void R_InitTranslationTables (void)`
- Defined: `progs/doomgeneric/r_draw.c:530`
- Doc: R_InitTranslationTables Creates the translation tables to map the green color ramp to gray, brown, red. Assumes a given 

### R_DrawSpan `void R_DrawSpan (void)`
- Defined: `progs/doomgeneric/r_draw.c:590`
- Doc: Draws the actual span.

### R_DrawSpan `void R_DrawSpan (void)`
- Defined: `progs/doomgeneric/r_draw.c:646`
- Doc: UNUSED. Loop unrolled by 4. if 0

### R_DrawSpanLow `void R_DrawSpanLow (void)`
- Defined: `progs/doomgeneric/r_draw.c:719`
- Doc: Again..

### R_InitBuffer `void
R_InitBuffer
( int		width,
  int		height )`
- Defined: `progs/doomgeneric/r_draw.c:776`
- Doc: R_InitBuffer Creats lookup tables that avoid multiplies and other hazzles for getting the framebuffer address of a pixel

### R_FillBackScreen `void R_FillBackScreen (void)`
- Defined: `progs/doomgeneric/r_draw.c:812`
- Doc: R_FillBackScreen Fills the back screen with a pattern for variable screen sizes Also draws a beveled edge.

### R_VideoErase `void
R_VideoErase
( unsigned	ofs,
  int		count )`
- Defined: `progs/doomgeneric/r_draw.c:918`
- Doc: Copy a screen buffer.

### R_DrawViewBorder `void R_DrawViewBorder (void)`
- Defined: `progs/doomgeneric/r_draw.c:941`
- Doc: R_DrawViewBorder Draws the border around the view for different size windows?

## progs/doomgeneric/r_main.c

### R_AddPointToBox `void
R_AddPointToBox
( int		x,
  int		y,
  fixed_t*	box )`
- Defined: `progs/doomgeneric/r_main.c:122`
- Doc: R_AddPointToBox Expand a given bbox so that it encloses a given point.

### R_PointOnSide `int
R_PointOnSide
( fixed_t	x,
  fixed_t	y,
  node_t*	node )`
- Defined: `progs/doomgeneric/r_main.c:145`
- Doc: R_PointOnSide Traverse BSP (sub) tree, check point against partition plane. Returns side 0 (front) or 1 (back).

### R_PointOnSegSide `int
R_PointOnSegSide
( fixed_t	x,
  fixed_t	y,
  seg_t*	line )`
- Defined: `progs/doomgeneric/r_main.c:196`

### R_PointToAngle `angle_t
R_PointToAngle
( fixed_t	x,
  fixed_t	y )`
- Defined: `progs/doomgeneric/r_main.c:271`

### R_PointToAngle2 `angle_t
R_PointToAngle2
( fixed_t	x1,
  fixed_t	y1,
  fixed_t	x2,
  fixed_t	y2 )`
- Defined: `progs/doomgeneric/r_main.c:359`

### R_PointToDist `fixed_t
R_PointToDist
( fixed_t	x,
  fixed_t	y )`
- Defined: `progs/doomgeneric/r_main.c:373`

### R_InitPointToAngle `void R_InitPointToAngle (void)`
- Defined: `progs/doomgeneric/r_main.c:422`
- Doc: R_InitPointToAngle

### R_ScaleFromGlobalAngle `fixed_t R_ScaleFromGlobalAngle (angle_t visangle)`
- Defined: `progs/doomgeneric/r_main.c:449`
- Doc: R_ScaleFromGlobalAngle Returns the texture mapping scale for the current line (horizontal span) at the given angle. rw_d

### R_InitTables `void R_InitTables (void)`
- Defined: `progs/doomgeneric/r_main.c:505`
- Doc: R_InitTables

### R_InitTextureMapping `void R_InitTextureMapping (void)`
- Defined: `progs/doomgeneric/r_main.c:540`
- Doc: R_InitTextureMapping

### R_InitLightTables `void R_InitLightTables (void)`
- Defined: `progs/doomgeneric/r_main.c:609`
- Doc: R_InitLightTables Only inits the zlight table, because the scalelight table changes with view size.  define DISTMAP		2

### R_SetViewSize `void
R_SetViewSize
( int		blocks,
  int		detail )`
- Defined: `progs/doomgeneric/r_main.c:651`

### R_ExecuteSetViewSize `void R_ExecuteSetViewSize (void)`
- Defined: `progs/doomgeneric/r_main.c:667`
- Doc: R_ExecuteSetViewSize

### R_Init `void R_Init (void)`
- Defined: `progs/doomgeneric/r_main.c:764`
- Doc: R_Init

### R_PointInSubsector `subsector_t*
R_PointInSubsector
( fixed_t	x,
  fixed_t	y )`
- Defined: `progs/doomgeneric/r_main.c:793`
- Doc: R_PointInSubsector

### R_SetupFrame `void R_SetupFrame (player_t* player)`
- Defined: `progs/doomgeneric/r_main.c:823`
- Doc: R_SetupFrame

### R_RenderPlayerView `void R_RenderPlayerView (player_t* player)`
- Defined: `progs/doomgeneric/r_main.c:863`
- Doc: R_RenderView

## progs/doomgeneric/r_plane.c

### R_InitPlanes `void R_InitPlanes (void)`
- Defined: `progs/doomgeneric/r_plane.c:94`
- Doc: R_InitPlanes Only at game startup.

### R_MapPlane `void
R_MapPlane
( int		y,
  int		x1,
  int		x2 )`
- Defined: `progs/doomgeneric/r_plane.c:113`
- Doc: R_MapPlane  Uses global vars: planeheight ds_source basexscale baseyscale viewx viewy  BASIC PRIMITIVE

### R_ClearPlanes `void R_ClearPlanes (void)`
- Defined: `progs/doomgeneric/r_plane.c:178`
- Doc: R_ClearPlanes At begining of frame.

### R_FindPlane `visplane_t*
R_FindPlane
( fixed_t	height,
  int		picnum,
  int		lightlevel )`
- Defined: `progs/doomgeneric/r_plane.c:210`
- Doc: R_FindPlane

### R_CheckPlane `visplane_t*
R_CheckPlane
( visplane_t*	pl,
  int		start,
  int		stop )`
- Defined: `progs/doomgeneric/r_plane.c:258`
- Doc: R_CheckPlane

### R_MakeSpans `void
R_MakeSpans
( int		x,
  int		t1,
  int		b1,
  int		t2,
  int		b2 )`
- Defined: `progs/doomgeneric/r_plane.c:323`
- Doc: R_MakeSpans

### R_DrawPlanes `void R_DrawPlanes (void)`
- Defined: `progs/doomgeneric/r_plane.c:360`
- Doc: R_DrawPlanes At the end of each frame.

## progs/doomgeneric/r_segs.c

### R_RenderMaskedSegRange `void
R_RenderMaskedSegRange
( drawseg_t*	ds,
  int		x1,
  int		x2 )`
- Defined: `progs/doomgeneric/r_segs.c:95`
- Doc: R_RenderMaskedSegRange

### R_RenderSegLoop `void R_RenderSegLoop (void)`
- Defined: `progs/doomgeneric/r_segs.c:198`
- Doc: R_RenderSegLoop Draws zero, one, or two textures (and possibly a masked texture) for walls. Can draw or mark the startin

### R_StoreWallRange `void
R_StoreWallRange
( int	start,
  int	stop )`
- Defined: `progs/doomgeneric/r_segs.c:371`
- Doc: R_StoreWallRange A wall segment will be drawn between start and stop pixels (inclusive).

## progs/doomgeneric/r_sky.c

### R_InitSkyMap `void R_InitSkyMap (void)`
- Defined: `progs/doomgeneric/r_sky.c:47`
- Doc: R_InitSkyMap Called whenever the view size changes.

## progs/doomgeneric/r_things.c

### R_InstallSpriteLump `void
R_InstallSpriteLump
( int		lump,
  unsigned	frame,
  unsigned	rotation,
  boolean	flipped )`
- Defined: `progs/doomgeneric/r_things.c:99`
- Doc: R_InstallSpriteLump Local function for R_InitSprites.

### R_InitSpriteDefs `void R_InitSpriteDefs (char** namelist)`
- Defined: `progs/doomgeneric/r_things.c:171`
- Doc: R_InitSpriteDefs Pass a null terminated list of sprite names (4 chars exactly) to be used. Builds the sprite rotation ma

### R_InitSprites `void R_InitSprites (char** namelist)`
- Defined: `progs/doomgeneric/r_things.c:291`
- Doc: R_InitSprites Called at program start.

### R_ClearSprites `void R_ClearSprites (void)`
- Defined: `progs/doomgeneric/r_things.c:309`
- Doc: R_ClearSprites Called at frame start.

### R_NewVisSprite `vissprite_t* R_NewVisSprite (void)`
- Defined: `progs/doomgeneric/r_things.c:319`

### R_DrawMaskedColumn `void R_DrawMaskedColumn (column_t* column)`
- Defined: `progs/doomgeneric/r_things.c:342`

### R_DrawVisSprite `void
R_DrawVisSprite
( vissprite_t*		vis,
  int			x1,
  int			x2 )`
- Defined: `progs/doomgeneric/r_things.c:388`
- Doc: R_DrawVisSprite mfloorclip and mceilingclip should also be set.

### R_ProjectSprite `void R_ProjectSprite (mobj_t* thing)`
- Defined: `progs/doomgeneric/r_things.c:444`
- Doc: R_ProjectSprite Generates a vissprite for a thing if it might be visible.

### R_AddSprites `void R_AddSprites (sector_t* sec)`
- Defined: `progs/doomgeneric/r_things.c:605`
- Doc: R_AddSprites During BSP traversal, this adds sprites by sector.

### R_DrawPSprite `void R_DrawPSprite (pspdef_t* psp)`
- Defined: `progs/doomgeneric/r_things.c:638`
- Doc: R_DrawPSprite

### R_DrawPlayerSprites `void R_DrawPlayerSprites (void)`
- Defined: `progs/doomgeneric/r_things.c:738`
- Doc: R_DrawPlayerSprites

### R_SortVisSprites `void R_SortVisSprites (void)`
- Defined: `progs/doomgeneric/r_things.c:777`

### R_DrawSprite `void R_DrawSprite (vissprite_t* spr)`
- Defined: `progs/doomgeneric/r_things.c:837`

### R_DrawMasked `void R_DrawMasked (void)`
- Defined: `progs/doomgeneric/r_things.c:951`
- Doc: R_DrawMasked

## progs/doomgeneric/s_sound.c

### S_Init `void S_Init(int sfxVolume, int musicVolume)`
- Defined: `progs/doomgeneric/s_sound.c:113`
- Doc: Initializes sound stuff, including volume Sets channels, SFX and music volume, allocates channel buffer, sets S_sfx look

### S_Shutdown `void S_Shutdown(void)`
- Defined: `progs/doomgeneric/s_sound.c:145`

### S_StopChannel `static void S_StopChannel(int cnum)`
- Defined: `progs/doomgeneric/s_sound.c:151`

### S_Start `void S_Start(void)`
- Defined: `progs/doomgeneric/s_sound.c:190`
- Doc: Per level startup code. Kills playing sounds at start of level, determines music if any, changes music.

### S_StopSound `void S_StopSound(mobj_t *origin)`
- Defined: `progs/doomgeneric/s_sound.c:242`

### S_GetChannel `static int S_GetChannel(mobj_t *origin, sfxinfo_t *sfxinfo)`
- Defined: `progs/doomgeneric/s_sound.c:261`
- Doc: S_GetChannel : If none available, return -1.  Otherwise channel #.

### S_AdjustSoundParams `static int S_AdjustSoundParams(mobj_t *listener, mobj_t *source,
                               i...`
- Defined: `progs/doomgeneric/s_sound.c:322`
- Doc: Changes volume and stereo-separation variables from the norm of a sound effect to be played. If the sound is not audible

### S_StartSound `void S_StartSound(void *origin_p, int sfx_id)`
- Defined: `progs/doomgeneric/s_sound.c:390`

### S_PauseSound `void S_PauseSound(void)`
- Defined: `progs/doomgeneric/s_sound.c:481`
- Doc: Stop and resume music, during game PAUSE.

### S_ResumeSound `void S_ResumeSound(void)`
- Defined: `progs/doomgeneric/s_sound.c:490`

### S_UpdateSounds `void S_UpdateSounds(mobj_t *listener)`
- Defined: `progs/doomgeneric/s_sound.c:503`
- Doc: Updates music & sounds

### S_SetMusicVolume `void S_SetMusicVolume(int volume)`
- Defined: `progs/doomgeneric/s_sound.c:570`

### S_SetSfxVolume `void S_SetSfxVolume(int volume)`
- Defined: `progs/doomgeneric/s_sound.c:581`

### S_StartMusic `void S_StartMusic(int m_id)`
- Defined: `progs/doomgeneric/s_sound.c:595`
- Doc: Starts some music with the music id found in sounds.h.

### S_ChangeMusic `void S_ChangeMusic(int musicnum, int looping)`
- Defined: `progs/doomgeneric/s_sound.c:600`

### S_MusicPlaying `boolean S_MusicPlaying(void)`
- Defined: `progs/doomgeneric/s_sound.c:648`

### S_StopMusic `void S_StopMusic(void)`
- Defined: `progs/doomgeneric/s_sound.c:653`

## progs/doomgeneric/sha1.c

### SHA1_Init `void SHA1_Init(sha1_context_t *hd)`
- Defined: `progs/doomgeneric/sha1.c:39`
- Doc: include "i_swap.h" include "sha1.h"

### Transform `static void Transform(sha1_context_t *hd, byte *data)`
- Defined: `progs/doomgeneric/sha1.c:55`
- Doc: Transform the message X which consists of 16 32-bit-words

### SHA1_Update `void SHA1_Update(sha1_context_t *hd, byte *inbuf, size_t inlen)`
- Defined: `progs/doomgeneric/sha1.c:198`
- Doc: Update the message digest with the contents of INBUF with length INLEN.

### SHA1_Final `void SHA1_Final(sha1_digest_t digest, sha1_context_t *hd)`
- Defined: `progs/doomgeneric/sha1.c:237`
- Doc: The routine final terminates the computation and returns the digest. The handle is prepared for a new cycle, but adding 

### SHA1_UpdateInt32 `void SHA1_UpdateInt32(sha1_context_t *context, unsigned int val)`
- Defined: `progs/doomgeneric/sha1.c:302`

### SHA1_UpdateString `void SHA1_UpdateString(sha1_context_t *context, char *str)`
- Defined: `progs/doomgeneric/sha1.c:314`

## progs/doomgeneric/st_lib.c

### STlib_init `void STlib_init(void)`
- Defined: `progs/doomgeneric/st_lib.c:50`

### STlib_initNum `void
STlib_initNum
( st_number_t*		n,
  int			x,
  int			y,
  patch_t**		pl,
  int*			num,
  bool...`
- Defined: `progs/doomgeneric/st_lib.c:58`
- Doc: ?

### STlib_drawNum `void
STlib_drawNum
( st_number_t*	n,
  boolean	refresh )`
- Defined: `progs/doomgeneric/st_lib.c:83`
- Doc: A fairly efficient way to draw a number based on differences from the old number. Note: worth the trouble?

### STlib_updateNum `void
STlib_updateNum
( st_number_t*		n,
  boolean		refresh )`
- Defined: `progs/doomgeneric/st_lib.c:145`

### STlib_initPercent `void
STlib_initPercent
( st_percent_t*		p,
  int			x,
  int			y,
  patch_t**		pl,
  int*			num,
 ...`
- Defined: `progs/doomgeneric/st_lib.c:155`

### STlib_updatePercent `void
STlib_updatePercent
( st_percent_t*		per,
  int			refresh )`
- Defined: `progs/doomgeneric/st_lib.c:168`

### STlib_initMultIcon `void
STlib_initMultIcon
( st_multicon_t*	i,
  int			x,
  int			y,
  patch_t**		il,
  int*			inum,...`
- Defined: `progs/doomgeneric/st_lib.c:182`

### STlib_updateMultIcon `void
STlib_updateMultIcon
( st_multicon_t*	mi,
  boolean		refresh )`
- Defined: `progs/doomgeneric/st_lib.c:201`

### STlib_initBinIcon `void
STlib_initBinIcon
( st_binicon_t*		b,
  int			x,
  int			y,
  patch_t*		i,
  boolean*		val,
...`
- Defined: `progs/doomgeneric/st_lib.c:232`

### STlib_updateBinIcon `void
STlib_updateBinIcon
( st_binicon_t*		bi,
  boolean		refresh )`
- Defined: `progs/doomgeneric/st_lib.c:251`

## progs/doomgeneric/st_stuff.c

### ST_refreshBackground `void ST_refreshBackground(void)`
- Defined: `progs/doomgeneric/st_stuff.c:415`

### ST_Responder `boolean
ST_Responder (event_t* ev)`
- Defined: `progs/doomgeneric/st_stuff.c:438`
- Doc: Respond to keyboard input events, intercept cheats.

### ST_calcPainOffset `int ST_calcPainOffset(void)`
- Defined: `progs/doomgeneric/st_stuff.c:662`

### ST_updateFaceWidget `void ST_updateFaceWidget(void)`
- Defined: `progs/doomgeneric/st_stuff.c:688`
- Doc: This is a not-very-pretty routine which handles the face states and their timing. the precedence of expressions is: dead

### ST_updateWidgets `void ST_updateWidgets(void)`
- Defined: `progs/doomgeneric/st_stuff.c:859`

### ST_Ticker `void ST_Ticker (void)`
- Defined: `progs/doomgeneric/st_stuff.c:923`

### ST_doPaletteStuff `void ST_doPaletteStuff(void)`
- Defined: `progs/doomgeneric/st_stuff.c:935`

### ST_drawWidgets `void ST_drawWidgets(boolean refresh)`
- Defined: `progs/doomgeneric/st_stuff.c:1000`

### ST_doRefresh `void ST_doRefresh(void)`
- Defined: `progs/doomgeneric/st_stuff.c:1035`

### ST_diffDraw `void ST_diffDraw(void)`
- Defined: `progs/doomgeneric/st_stuff.c:1048`

### ST_Drawer `void ST_Drawer (boolean fullscreen, boolean refresh)`
- Defined: `progs/doomgeneric/st_stuff.c:1054`

### ST_loadUnloadGraphics `static void ST_loadUnloadGraphics(load_callback_t callback)`
- Defined: `progs/doomgeneric/st_stuff.c:1075`
- Doc: Iterates through all graphics to be loaded or unloaded, along with the variable they use, invoking the specified callbac

### ST_loadCallback `static void ST_loadCallback(char *lumpname, patch_t **variable)`
- Defined: `progs/doomgeneric/st_stuff.c:1161`

### ST_loadGraphics `void ST_loadGraphics(void)`
- Defined: `progs/doomgeneric/st_stuff.c:1166`

### ST_loadData `void ST_loadData(void)`
- Defined: `progs/doomgeneric/st_stuff.c:1171`

### ST_unloadCallback `static void ST_unloadCallback(char *lumpname, patch_t **variable)`
- Defined: `progs/doomgeneric/st_stuff.c:1177`

### ST_unloadGraphics `void ST_unloadGraphics(void)`
- Defined: `progs/doomgeneric/st_stuff.c:1183`

### ST_unloadData `void ST_unloadData(void)`
- Defined: `progs/doomgeneric/st_stuff.c:1188`

### ST_initData `void ST_initData(void)`
- Defined: `progs/doomgeneric/st_stuff.c:1193`

### ST_createWidgets `void ST_createWidgets(void)`
- Defined: `progs/doomgeneric/st_stuff.c:1224`

### ST_Start `void ST_Start (void)`
- Defined: `progs/doomgeneric/st_stuff.c:1387`

### ST_Stop `void ST_Stop (void)`
- Defined: `progs/doomgeneric/st_stuff.c:1400`

### ST_Init `void ST_Init (void)`
- Defined: `progs/doomgeneric/st_stuff.c:1410`

## progs/doomgeneric/statdump.c

### DiscoverGamemode `static void DiscoverGamemode(wbstartstruct_t *stats, int num_stats)`
- Defined: `progs/doomgeneric/statdump.c:70`
- Doc: Try to work out whether this is a Doom 1 or Doom 2 game, by looking at the episode and map, and the par times.  This is 

### GetNumPlayers `static int GetNumPlayers(wbstartstruct_t *stats)`
- Defined: `progs/doomgeneric/statdump.c:129`
- Doc: if (partime != doom1_par_times[level] * TICRATE && partime == doom2_par_times[level] * TICRATE) { discovered_gamemission

### PrintBanner `static void PrintBanner(FILE *stream)`
- Defined: `progs/doomgeneric/statdump.c:149`
- Doc: if ORIGCODE

### PrintPercentage `static void PrintPercentage(FILE *stream, int amount, int total)`
- Defined: `progs/doomgeneric/statdump.c:154`

### PrintPlayerStats `static void PrintPlayerStats(FILE *stream, wbstartstruct_t *stats,
        int player_num)`
- Defined: `progs/doomgeneric/statdump.c:179`
- Doc: statdump.exe is a 16-bit program, so very occasionally an integer overflow can occur when doing this calculation with a 

### PrintFragsTable `static void PrintFragsTable(FILE *stream, wbstartstruct_t *stats)`
- Defined: `progs/doomgeneric/statdump.c:212`
- Doc: fprintf(stream, "\n"); /* Secrets percentage fprintf(stream, "\tSecrets: "); PrintPercentage(stream, player->ssecret, st

### PrintLevelName `static void PrintLevelName(FILE *stream, int episode, int level)`
- Defined: `progs/doomgeneric/statdump.c:271`
- Doc: } fprintf(stream, "\n"); } fprintf(stream, "\t\t|\n"); fprintf(stream, "\t     KILLERS\n"); } #endif #if ORIGCODE /* Dis

### PrintStats `static void PrintStats(FILE *stream, wbstartstruct_t *stats)`
- Defined: `progs/doomgeneric/statdump.c:300`
- Doc: case none: fprintf(stream, "E%iM%i / MAP%02i\n", episode + 1, level + 1, level + 1); break; } PrintBanner(stream); } #en

### StatCopy `void StatCopy(wbstartstruct_t *stats)`
- Defined: `progs/doomgeneric/statdump.c:332`
- Doc: endif

### StatDump `void StatDump(void)`
- Defined: `progs/doomgeneric/statdump.c:342`

## progs/doomgeneric/tables.c

### SlopeDiv `int SlopeDiv(unsigned int num, unsigned int den)`
- Defined: `progs/doomgeneric/tables.c:40`
- Doc: to get a global angle from cartesian coordinates, the coordinates are flipped until they are in the first octant of the 

## progs/doomgeneric/v_video.c

### V_MarkRect `void V_MarkRect(int x, int y, int width, int height)`
- Defined: `progs/doomgeneric/v_video.c:69`
- Doc: V_MarkRect

### V_CopyRect `void V_CopyRect(int srcx, int srcy, byte *source,
                int width, int height,
        ...`
- Defined: `progs/doomgeneric/v_video.c:85`
- Doc: V_CopyRect

### V_SetPatchClipCallback `void V_SetPatchClipCallback(vpatchclipfunc_t func)`
- Defined: `progs/doomgeneric/v_video.c:129`
- Doc: V_SetPatchClipCallback  haleyjd 08/28/10: Added for Strife support. By calling this function, you can setup runtime erro

### V_DrawPatch `void V_DrawPatch(int x, int y, patch_t *patch)`
- Defined: `progs/doomgeneric/v_video.c:138`
- Doc: V_DrawPatch Masks a column based masked pic to the screen.

### V_DrawPatchFlipped `void V_DrawPatchFlipped(int x, int y, patch_t *patch)`
- Defined: `progs/doomgeneric/v_video.c:202`
- Doc: V_DrawPatchFlipped Masks a column based masked pic to the screen. Flips horizontally, e.g. to mirror face.

### V_DrawPatchDirect `void V_DrawPatchDirect(int x, int y, patch_t *patch)`
- Defined: `progs/doomgeneric/v_video.c:267`
- Doc: V_DrawPatchDirect Draws directly to the screen on the pc.

### V_DrawTLPatch `void V_DrawTLPatch(int x, int y, patch_t * patch)`
- Defined: `progs/doomgeneric/v_video.c:278`
- Doc: V_DrawTLPatch  Masks a column based translucent masked pic to the screen.

### V_DrawXlaPatch `void V_DrawXlaPatch(int x, int y, patch_t * patch)`
- Defined: `progs/doomgeneric/v_video.c:328`
- Doc: V_DrawXlaPatch  villsa [STRIFE] Masks a column based translucent masked pic to the screen.

### V_DrawAltTLPatch `void V_DrawAltTLPatch(int x, int y, patch_t * patch)`
- Defined: `progs/doomgeneric/v_video.c:377`
- Doc: V_DrawAltTLPatch  Masks a column based translucent masked pic to the screen.

### V_DrawShadowedPatch `void V_DrawShadowedPatch(int x, int y, patch_t *patch)`
- Defined: `progs/doomgeneric/v_video.c:427`
- Doc: V_DrawShadowedPatch  Masks a column based masked pic to the screen.

### V_LoadTintTable `void V_LoadTintTable(void)`
- Defined: `progs/doomgeneric/v_video.c:481`
- Doc: Load tint table from TINTTAB lump.

### V_LoadXlaTable `void V_LoadXlaTable(void)`
- Defined: `progs/doomgeneric/v_video.c:492`
- Doc: V_LoadXlaTable  villsa [STRIFE] Load xla table from XLATAB lump.

### V_DrawBlock `void V_DrawBlock(int x, int y, int width, int height, byte *src)`
- Defined: `progs/doomgeneric/v_video.c:502`
- Doc: V_DrawBlock Draw a linear block of pixels into the view buffer.

### V_DrawFilledBox `void V_DrawFilledBox(int x, int y, int w, int h, int c)`
- Defined: `progs/doomgeneric/v_video.c:528`

### V_DrawHorizLine `void V_DrawHorizLine(int x, int y, int w, int c)`
- Defined: `progs/doomgeneric/v_video.c:548`

### V_DrawVertLine `void V_DrawVertLine(int x, int y, int h, int c)`
- Defined: `progs/doomgeneric/v_video.c:561`

### V_DrawBox `void V_DrawBox(int x, int y, int w, int h, int c)`
- Defined: `progs/doomgeneric/v_video.c:575`

### V_DrawRawScreen `void V_DrawRawScreen(byte *raw)`
- Defined: `progs/doomgeneric/v_video.c:588`
- Doc: Draw a "raw" screen (lump containing raw data to blit directly to the screen)

### V_Init `void V_Init (void)`
- Defined: `progs/doomgeneric/v_video.c:597`
- Doc: V_Init

### V_UseBuffer `void V_UseBuffer(byte *buffer)`
- Defined: `progs/doomgeneric/v_video.c:605`
- Doc: Set the buffer that the code draws to.

### V_RestoreBuffer `void V_RestoreBuffer(void)`
- Defined: `progs/doomgeneric/v_video.c:612`
- Doc: Restore screen buffer to the i_video screen buffer.

### WritePCXfile `void WritePCXfile(char *filename, byte *data,
                  int width, int height,
          ...`
- Defined: `progs/doomgeneric/v_video.c:652`
- Doc: WritePCXfile

### error_fn `static void error_fn(png_structp p, png_const_charp s)`
- Defined: `progs/doomgeneric/v_video.c:710`
- Doc: ifdef HAVE_LIBPNG  WritePNGfile

### warning_fn `static void warning_fn(png_structp p, png_const_charp s)`
- Defined: `progs/doomgeneric/v_video.c:715`

### WritePNGfile `void WritePNGfile(char *filename, byte *data,
                  int width, int height,
          ...`
- Defined: `progs/doomgeneric/v_video.c:720`

### V_ScreenShot `void V_ScreenShot(char *format)`
- Defined: `progs/doomgeneric/v_video.c:790`
- Doc: V_ScreenShot

### V_DrawMouseSpeedBox `void V_DrawMouseSpeedBox(int speed)`
- Defined: `progs/doomgeneric/v_video.c:845`
- Doc: define MOUSE_SPEED_BOX_WIDTH  120 define MOUSE_SPEED_BOX_HEIGHT 9

## progs/doomgeneric/w_checksum.c

### GetFileNumber `static int GetFileNumber(wad_file_t *handle)`
- Defined: `progs/doomgeneric/w_checksum.c:30`

### ChecksumAddLump `static void ChecksumAddLump(sha1_context_t *sha1_context, lumpinfo_t *lump)`
- Defined: `progs/doomgeneric/w_checksum.c:56`

### W_Checksum `void W_Checksum(sha1_digest_t digest)`
- Defined: `progs/doomgeneric/w_checksum.c:67`

## progs/doomgeneric/w_file.c

### W_OpenFile `wad_file_t *W_OpenFile(char *path)`
- Defined: `progs/doomgeneric/w_file.c:52`

### W_CloseFile `void W_CloseFile(wad_file_t *wad)`
- Defined: `progs/doomgeneric/w_file.c:84`

### W_Read `size_t W_Read(wad_file_t *wad, unsigned int offset,
              void *buffer, size_t buffer_len)`
- Defined: `progs/doomgeneric/w_file.c:89`

## progs/doomgeneric/w_file_stdc.c

### W_StdC_OpenFile `static wad_file_t *W_StdC_OpenFile(char *path)`
- Defined: `progs/doomgeneric/w_file_stdc.c:32`

### W_StdC_CloseFile `static void W_StdC_CloseFile(wad_file_t *wad)`
- Defined: `progs/doomgeneric/w_file_stdc.c:55`

### W_StdC_Read `size_t W_StdC_Read(wad_file_t *wad, unsigned int offset,
                   void *buffer, size_t ...`
- Defined: `progs/doomgeneric/w_file_stdc.c:68`
- Doc: Read data from the specified position in the file into the provided buffer.  Returns the number of bytes read.

## progs/doomgeneric/w_main.c

### W_ParseCommandLine `boolean W_ParseCommandLine(void)`
- Defined: `progs/doomgeneric/w_main.c:29`
- Doc: Parse the command line, merging WAD files that are sppecified. Returns true if at least one file was added.

## progs/doomgeneric/w_wad.c

### W_LumpNameHash `unsigned int W_LumpNameHash(const char *s)`
- Defined: `progs/doomgeneric/w_wad.c:71`
- Doc: Hash function used for lump names.

### ExtendLumpInfo `static void ExtendLumpInfo(int newnumlumps)`
- Defined: `progs/doomgeneric/w_wad.c:89`
- Doc: Increase the size of the lumpinfo[] array to the specified size.

### W_AddFile `wad_file_t *W_AddFile (char *filename)`
- Defined: `progs/doomgeneric/w_wad.c:140`
- Doc: W_AddFile All files are optional, but at least one file must be found (PWAD, if all required lumps are present). Files w

### W_NumLumps `int W_NumLumps (void)`
- Defined: `progs/doomgeneric/w_wad.c:246`
- Doc: W_NumLumps

### W_CheckNumForName `int W_CheckNumForName (char* name)`
- Defined: `progs/doomgeneric/w_wad.c:257`
- Doc: W_CheckNumForName Returns -1 if name not found.

### W_GetNumForName `int W_GetNumForName (char* name)`
- Defined: `progs/doomgeneric/w_wad.c:308`
- Doc: W_GetNumForName Calls W_CheckNumForName, but bombs out if not found.

### W_LumpLength `int W_LumpLength (unsigned int lump)`
- Defined: `progs/doomgeneric/w_wad.c:327`
- Doc: W_LumpLength Returns the buffer size needed to load the given lump.

### W_ReadLump `void W_ReadLump(unsigned int lump, void *dest)`
- Defined: `progs/doomgeneric/w_wad.c:344`
- Doc: W_ReadLump Loads the lump into the given buffer, which must be >= W_LumpLength().

### W_CacheLumpNum `void *W_CacheLumpNum(int lumpnum, int tag)`
- Defined: `progs/doomgeneric/w_wad.c:383`
- Doc: W_CacheLumpNum  Load a lump into memory and return a pointer to a buffer containing the lump data.  'tag' is the type of

### W_CacheLumpName `void *W_CacheLumpName(char *name, int tag)`
- Defined: `progs/doomgeneric/w_wad.c:431`
- Doc: W_CacheLumpName

### W_ReleaseLumpNum `void W_ReleaseLumpNum(int lumpnum)`
- Defined: `progs/doomgeneric/w_wad.c:445`
- Doc: Release a lump back to the cache, so that it can be reused later without having to read from disk again, or alternativel

### W_ReleaseLumpName `void W_ReleaseLumpName(char *name)`
- Defined: `progs/doomgeneric/w_wad.c:466`

### W_Profile `void W_Profile (void)`
- Defined: `progs/doomgeneric/w_wad.c:479`

### W_GenerateHashTable `void W_GenerateHashTable(void)`
- Defined: `progs/doomgeneric/w_wad.c:540`
- Doc: Generate a hash table for fast lookups

### W_CheckCorrectIWAD `void W_CheckCorrectIWAD(GameMission_t mission)`
- Defined: `progs/doomgeneric/w_wad.c:587`

## progs/doomgeneric/wi_stuff.c

### WI_slamBackground `void WI_slamBackground(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:402`
- Doc: slam background

### WI_Responder `boolean WI_Responder(event_t* ev)`
- Defined: `progs/doomgeneric/wi_stuff.c:409`
- Doc: The ticker is used to detect keys because of timing issues in netgames.

### WI_drawLF `void WI_drawLF(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:416`
- Doc: Draws "<Levelname> Finished!"

### WI_drawEL `void WI_drawEL(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:452`
- Doc: Draws "Entering <LevelName>"

### WI_drawOnLnode `void
WI_drawOnLnode
( int		n,
  patch_t*	c[] )`
- Defined: `progs/doomgeneric/wi_stuff.c:469`

### WI_initAnimatedBack `void WI_initAnimatedBack(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:516`

### WI_updateAnimatedBack `void WI_updateAnimatedBack(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:547`

### WI_drawAnimatedBack `void WI_drawAnimatedBack(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:598`

### WI_drawNum `int
WI_drawNum
( int		x,
  int		y,
  int		n,
  int		digits )`
- Defined: `progs/doomgeneric/wi_stuff.c:626`
- Doc: Draws a number. If digits > 0, then use that many digits minimum, otherwise only use as many as necessary. Returns new x

### WI_drawPercent `void
WI_drawPercent
( int		x,
  int		y,
  int		p )`
- Defined: `progs/doomgeneric/wi_stuff.c:683`

### WI_drawTime `void
WI_drawTime
( int		x,
  int		y,
  int		t )`
- Defined: `progs/doomgeneric/wi_stuff.c:703`
- Doc: Display level completion time and par, or "sucks" message if overflow.

### WI_End `void WI_End(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:738`

### WI_initNoState `void WI_initNoState(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:745`

### WI_updateNoState `void WI_updateNoState(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:752`

### WI_initShowNextLoc `void WI_initShowNextLoc(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:770`

### WI_updateShowNextLoc `void WI_updateShowNextLoc(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:780`

### WI_drawShowNextLoc `void WI_drawShowNextLoc(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:790`

### WI_drawNoState `void WI_drawNoState(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:831`

### WI_fragSum `int WI_fragSum(int playernum)`
- Defined: `progs/doomgeneric/wi_stuff.c:837`

### WI_initDeathmatchStats `void WI_initDeathmatchStats(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:866`

### WI_updateDeathmatchStats `void WI_updateDeathmatchStats(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:895`

### WI_drawDeathmatchStats `void WI_drawDeathmatchStats(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:998`

### WI_initNetgameStats `void WI_initNetgameStats(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:1088`

### WI_updateNetgameStats `void WI_updateNetgameStats(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:1114`

### WI_drawNetgameStats `void WI_drawNetgameStats(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:1269`

### WI_initStats `void WI_initStats(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:1328`

### WI_updateStats `void WI_updateStats(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:1340`

### WI_drawStats `void WI_drawStats(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:1446`

### WI_checkForAccelerate `void WI_checkForAccelerate(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:1480`

### WI_Ticker `void WI_Ticker(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:1514`
- Doc: Updates stuff each tick

### WI_loadUnloadData `static void WI_loadUnloadData(load_callback_t callback)`
- Defined: `progs/doomgeneric/wi_stuff.c:1553`
- Doc: Common load/unload function.  Iterates over all the graphics lumps to be loaded/unloaded into memory.

### WI_loadCallback `static void WI_loadCallback(char *name, patch_t **variable)`
- Defined: `progs/doomgeneric/wi_stuff.c:1703`

### WI_loadData `void WI_loadData(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:1708`

### WI_unloadCallback `static void WI_unloadCallback(char *name, patch_t **variable)`
- Defined: `progs/doomgeneric/wi_stuff.c:1734`

### WI_unloadData `void WI_unloadData(void)`
- Defined: `progs/doomgeneric/wi_stuff.c:1740`

### WI_Drawer `void WI_Drawer (void)`
- Defined: `progs/doomgeneric/wi_stuff.c:1751`

### WI_initVariables `void WI_initVariables(wbstartstruct_t* wbstartstruct)`
- Defined: `progs/doomgeneric/wi_stuff.c:1774`

### WI_Start `void WI_Start(wbstartstruct_t* wbstartstruct)`
- Defined: `progs/doomgeneric/wi_stuff.c:1817`

## progs/doomgeneric/z_zone.c

### Z_ClearZone `void Z_ClearZone (memzone_t* zone)`
- Defined: `progs/doomgeneric/z_zone.c:71`
- Doc: Z_ClearZone

### Z_Init `void Z_Init (void)`
- Defined: `progs/doomgeneric/z_zone.c:97`
- Doc: Z_Init

### Z_Free `void Z_Free (void* ptr)`
- Defined: `progs/doomgeneric/z_zone.c:126`
- Doc: Z_Free

### Z_Malloc `void*
Z_Malloc
( int		size,
  int		tag,
  void*		user )`
- Defined: `progs/doomgeneric/z_zone.c:182`
- Doc: Z_Malloc You can pass a NULL user if the tag is < PU_PURGELEVEL.  define MINFRAGMENT		64

### Z_FreeTags `void
Z_FreeTags
( int		lowtag,
  int		hightag )`
- Defined: `progs/doomgeneric/z_zone.c:297`
- Doc: Z_FreeTags

### Z_DumpHeap `void
Z_DumpHeap
( int		lowtag,
  int		hightag )`
- Defined: `progs/doomgeneric/z_zone.c:327`
- Doc: Z_DumpHeap Note: TFileDumpHeap( stdout ) ?

### Z_FileDumpHeap `void Z_FileDumpHeap (FILE* f)`
- Defined: `progs/doomgeneric/z_zone.c:367`
- Doc: Z_FileDumpHeap

### Z_CheckHeap `void Z_CheckHeap (void)`
- Defined: `progs/doomgeneric/z_zone.c:400`
- Doc: Z_CheckHeap

### Z_ChangeTag2 `void Z_ChangeTag2(void *ptr, int tag, char *file, int line)`
- Defined: `progs/doomgeneric/z_zone.c:429`
- Doc: Z_ChangeTag

### Z_ChangeUser `void Z_ChangeUser(void *ptr, void **user)`
- Defined: `progs/doomgeneric/z_zone.c:445`

### Z_FreeMemory `int Z_FreeMemory (void)`
- Defined: `progs/doomgeneric/z_zone.c:466`
- Doc: Z_FreeMemory

### Z_ZoneSize `unsigned int Z_ZoneSize(void)`
- Defined: `progs/doomgeneric/z_zone.c:483`

## progs/lua/lua_main.c

### luaL_require_global `static void luaL_require_global(lua_State *L, const char *name,
                                l...`
- Defined: `progs/lua/lua_main.c:21`

### set_arg_table `static void set_arg_table(lua_State *L, int argc, char **argv, int first)`
- Defined: `progs/lua/lua_main.c:27`

### docode `static int docode(lua_State *L, const char *code)`
- Defined: `progs/lua/lua_main.c:40`

### dofile `static int dofile(lua_State *L, const char *name)`
- Defined: `progs/lua/lua_main.c:50`

### repl `static int repl(lua_State *L)`
- Defined: `progs/lua/lua_main.c:60`

### main `int main(int argc, char **argv)`
- Defined: `progs/lua/lua_main.c:104`

## progs/lua/minios.c

### msys5 `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)`
- Defined: `progs/lua/minios.c:37`
- Doc: /* ── raw syscall helpers (x86-64 Linux ABI) ─────────────────────────── static long msys(long n, long a1, long a2, long
- Imported by: `progs/micropython/variants/minios/lib/hello.py`, `progs/src/shell.py`, `progs/src/test.py`

### minios_time_ms `static int minios_time_ms(lua_State *L)`
- Defined: `progs/lua/minios.c:62`
- Doc: } /* ── MiniOS syscall numbers (canonical table from minios_abi.h) ─────── #include "minios_abi.h" #define SYS_TIME_MS  
- Imported by: `progs/micropython/variants/minios/lib/hello.py`, `progs/src/shell.py`, `progs/src/test.py`

### minios_rtc `static int minios_rtc(lua_State *L)`
- Defined: `progs/lua/minios.c:68`
- Doc: #define SYS_PCSPK_INIT  MINIOS_SYS_PCSPK_INIT #define SYS_PCSPK_TONE  MINIOS_SYS_PCSPK_TONE #define SYS_RTC         MINI
- Imported by: `progs/micropython/variants/minios/lib/hello.py`, `progs/src/shell.py`, `progs/src/test.py`

### minios_fb_info `static int minios_fb_info(lua_State *L)`
- Defined: `progs/lua/minios.c:82`
- Doc: static int minios_rtc(lua_State *L) { int h, m, s; if (msys(SYS_RTC, (long)&h, (long)&m, (long)&s) < 0) { lua_pushnil(L)
- Imported by: `progs/micropython/variants/minios/lib/hello.py`, `progs/src/shell.py`, `progs/src/test.py`

### minios_vol `static int minios_vol(lua_State *L)`
- Defined: `progs/lua/minios.c:96`
- Doc: static int minios_fb_info(lua_State *L) { int w, h, p; if (msys(SYS_FB_INFO, (long)&w, (long)&h, (long)&p) < 0) { lua_pu
- Imported by: `progs/micropython/variants/minios/lib/hello.py`, `progs/src/shell.py`, `progs/src/test.py`

### minios_pal `static int minios_pal(lua_State *L)`
- Defined: `progs/lua/minios.c:109`
- Doc: /* ── minios.vol([v]) -> current volume ─────────────────────────────── static int minios_vol(lua_State *L) { if (lua_ge
- Imported by: `progs/micropython/variants/minios/lib/hello.py`, `progs/src/shell.py`, `progs/src/test.py`

### minios_pcspeaker `static int minios_pcspeaker(lua_State *L)`
- Defined: `progs/lua/minios.c:119`
- Doc: return 1; } /* ── minios.pal(buf) -- load a 768-byte VGA DAC palette ────────────── static int minios_pal(lua_State *L) 
- Imported by: `progs/micropython/variants/minios/lib/hello.py`, `progs/src/shell.py`, `progs/src/test.py`

### minios_run `static int minios_run(lua_State *L)`
- Defined: `progs/lua/minios.c:136`
- Doc: ── minios.run(path[, args][, redirect]) -> exit code ─────────────── Runs a program through SYS_SPAWN (215), preserving 
- Imported by: `progs/micropython/variants/minios/lib/hello.py`, `progs/src/shell.py`, `progs/src/test.py`

### luaopen_minios `int luaopen_minios(lua_State *L)`
- Defined: `progs/lua/minios.c:191`
- Imported by: `progs/micropython/variants/minios/lib/hello.py`, `progs/src/shell.py`, `progs/src/test.py`

## progs/micropython/variants/minios/minios_module.c

### msys5 `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)`
- Defined: `progs/micropython/variants/minios/minios_module.c:26`
- Doc: /* ── raw syscall helper (x86-64 Linux ABI) ─────────────────────────── static long msys(long n, long a1, long a2, long 

### minios_time_ms `static mp_obj_t minios_time_ms(void)`
- Defined: `progs/micropython/variants/minios/minios_module.c:51`
- Doc: } /* ── MiniOS syscall numbers (canonical table from minios_abi.h) ─────── #include "minios_abi.h" #define SYS_TIME_MS  

### minios_rtc `static mp_obj_t minios_rtc(void)`
- Defined: `progs/micropython/variants/minios/minios_module.c:58`
- Doc: #define SYS_PCSPK_TONE  MINIOS_SYS_PCSPK_TONE #define SYS_RTC         MINIOS_SYS_RTC #define SYS_FB_INFO     MINIOS_SYS_

### minios_fb_info `static mp_obj_t minios_fb_info(void)`
- Defined: `progs/micropython/variants/minios/minios_module.c:75`
- Doc: long ret = msys(SYS_RTC, (long)&h, (long)&m, (long)&s); if (ret < 0) { mp_raise_OSError(-ret); } mp_obj_t tuple[3] = { m

### minios_pal `static mp_obj_t minios_pal(mp_obj_t buf_in)`
- Defined: `progs/micropython/variants/minios/minios_module.c:110`
- Doc: static mp_obj_t minios_vol(size_t n_args, const mp_obj_t *args) { if (n_args == 0) { /* get volume: pass -1 to signal "r

### minios_pcspeaker `static mp_obj_t minios_pcspeaker(mp_obj_t freq_in, mp_obj_t ms_in)`
- Defined: `progs/micropython/variants/minios/minios_module.c:126`
- Doc: mp_buffer_info_t bufinfo; mp_get_buffer_raise(buf_in, &bufinfo, MP_BUFFER_READ); if (bufinfo.len < 768) { mp_raise_Value

### minios_run `static mp_obj_t minios_run(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)`
- Defined: `progs/micropython/variants/minios/minios_module.c:148`
- Doc: ── minios.run(path, args=None, redirect=None) -> exit code ───────── Runs a program through the kernel SYS_SPAWN (215) b

## progs/nuklear/cvm_emit.c

### cb_push `static int cb_push(struct codebuf *cb, unsigned char c)`
- Defined: `progs/nuklear/cvm_emit.c:55`

### cb_u32 `static int cb_u32(struct codebuf *cb, unsigned long v)`
- Defined: `progs/nuklear/cvm_emit.c:67`

### cb_i64 `static int cb_i64(struct codebuf *cb, long long v)`
- Defined: `progs/nuklear/cvm_emit.c:73`

### topo_sort `static int topo_sort(const struct cvm_node *nodes, int n,
                     int *order, char *...`
- Defined: `progs/nuklear/cvm_emit.c:81`
- Doc: static int cb_u32(struct codebuf *cb, unsigned long v) { for (int i = 0; i < 4; i++) if (cb_push(cb, (unsigned char)(v >

### cvm_compile `int cvm_compile(const struct cvm_node *nodes, int n,
                unsigned char **out, size_t ...`
- Defined: `progs/nuklear/cvm_emit.c:122`

### w32 `void w32(void *p, unsigned v)`
- Defined: `progs/nuklear/cvm_emit.c:257`
- Doc: size_t ft = (size_t)nf * CVM_FUNC_ENTRY_SIZE; size_t gt = (size_t)ng * CVM_GLOBAL_ENTRY_SIZE; size_t nt = (size_t)nn * C

## progs/nuklear/node_editor.c

### graph_clear `static void graph_clear(void)`
- Defined: `progs/nuklear/node_editor.c:48`

### graph_add `static int graph_add(int kind)`
- Defined: `progs/nuklear/node_editor.c:53`

### kind_name `static const char *kind_name(int k)`
- Defined: `progs/nuklear/node_editor.c:65`

### node_inputs `static int node_inputs(int k)`
- Defined: `progs/nuklear/node_editor.c:79`

### kind_color `static struct nk_color kind_color(int k)`
- Defined: `progs/nuklear/node_editor.c:89`
- Doc: case G_EXIT:  return "Exit"; } return "?"; } static int node_inputs(int k) { switch (k) { case G_ADD: case G_SUB: case G

### graph_to_compiler `static int graph_to_compiler(struct cvm_node *out, int cap)`
- Defined: `progs/nuklear/node_editor.c:104`
- Doc: switch (k) { case G_NUM:   return nk_rgb(70, 130, 180);   /* steel blue case G_ADD:   return nk_rgb(60, 179, 113);   /* 

### compile_to `static int compile_to(const char *path)`
- Defined: `progs/nuklear/node_editor.c:122`
- Doc: (g_nodes[i].kind == G_SUB) ? NODE_SUB : (g_nodes[i].kind == G_MUL) ? NODE_MUL : (g_nodes[i].kind == G_DIV) ? NODE_DIV : 

### parse_graph_file `static int parse_graph_file(const char *path)`
- Defined: `progs/nuklear/node_editor.c:159`
- Doc: --- Headless graph text format ---- num a 5          add b a c        print b        exit b Each line: <type> <name> [va

### resolve `int resolve(const char *nme, int upto)`
- Defined: `progs/nuklear/node_editor.c:166`

### pin_y `static float pin_y(struct gnode *n, int slot, int is_output)`
- Defined: `progs/nuklear/node_editor.c:234`
- Doc: /* Link-drag state: click an output pin, drag to an input pin. static int linking_active; static int linking_src_node; s

### ui_build `static void ui_build(struct nk_context *ctx, float win_w, float win_h)`
- Defined: `progs/nuklear/node_editor.c:243`

### gui_run `static void gui_run(void)`
- Defined: `progs/nuklear/node_editor.c:487`
- Doc: circle.x = n->x - PIN_R; circle.y = pin_y(n, k, 0) - PIN_R; circle.w = PIN_DIAM; circle.h = PIN_DIAM; nk_fill_circle(can

### main `int main(int argc, char **argv)`
- Defined: `progs/nuklear/node_editor.c:535`

## progs/nuklear/nuklear_minios.c

### nk_sys_time_ms `long nk_sys_time_ms(void)`
- Defined: `progs/nuklear/nuklear_minios.c:26`
- Doc: wheel. All MiniOS-specific syscalls go through the Linux syscall ABI, so this compiles into a normal static ring-3 ELF. 

### nk_sys_kbd `long nk_sys_kbd(void)`
- Defined: `progs/nuklear/nuklear_minios.c:31`

### nk_sys_palette `long nk_sys_palette(const unsigned char *pal)`
- Defined: `progs/nuklear/nuklear_minios.c:36`

### nk_sys_kbd_raw `long nk_sys_kbd_raw(int on)`
- Defined: `progs/nuklear/nuklear_minios.c:41`

### nk_sys_vga_mode `long nk_sys_vga_mode(int on)`
- Defined: `progs/nuklear/nuklear_minios.c:46`

### nk_sys_fb_info `long nk_sys_fb_info(int *w, int *h, int *pitch)`
- Defined: `progs/nuklear/nuklear_minios.c:51`

### nk_sys_mouse `long nk_sys_mouse(int *xybw)`
- Defined: `progs/nuklear/nuklear_minios.c:58`

### nk_sys_mouse_badptr `long nk_sys_mouse_badptr(void)`
- Defined: `progs/nuklear/nuklear_minios.c:63`

### nk_sys_nk_frame `long nk_sys_nk_frame(int *origin)`
- Defined: `progs/nuklear/nuklear_minios.c:71`

### pal_prepare `static void pal_prepare(void)`
- Defined: `progs/nuklear/nuklear_minios.c:143`

### col_to_idx `static int col_to_idx(struct nk_color c)`
- Defined: `progs/nuklear/nuklear_minios.c:154`

### set_clip `static void set_clip(int x, int y, int w, int h)`
- Defined: `progs/nuklear/nuklear_minios.c:272`

### px `static void px(int x, int y, int c)`
- Defined: `progs/nuklear/nuklear_minios.c:282`

### fill_rect `static void fill_rect(int x, int y, int w, int h, int c)`
- Defined: `progs/nuklear/nuklear_minios.c:289`

### draw_line `static void draw_line(int x0, int y0, int x1, int y1, int th, int c)`
- Defined: `progs/nuklear/nuklear_minios.c:296`

### fill_circle `static void fill_circle(int cx, int cy, int r, int c)`
- Defined: `progs/nuklear/nuklear_minios.c:314`

### stroke_circle `static void stroke_circle(int cx, int cy, int r, int th, int c)`
- Defined: `progs/nuklear/nuklear_minios.c:320`

### fill_poly `static void fill_poly(int *xs, int *ys, int n, int c)`
- Defined: `progs/nuklear/nuklear_minios.c:339`
- Doc: draw_line(cx + x, cy - y, cx - x, cy - y, th, c); draw_line(cx - x, cy + y, cx - x, cy - y, th, c); draw_line(cx + x, cy

### stroke_poly `static void stroke_poly(int *xs, int *ys, int n, int th, int c)`
- Defined: `progs/nuklear/nuklear_minios.c:361`

### draw_text `static void draw_text(int x, int y, const char *s, int len, int fg, int bg)`
- Defined: `progs/nuklear/nuklear_minios.c:368`

### draw_arc `static void draw_arc(int cx, int cy, int r, float a0, float a1,
                     int filled, ...`
- Defined: `progs/nuklear/nuklear_minios.c:382`

### nk_rasterize `void nk_rasterize(struct nk_context *ctx)`
- Defined: `progs/nuklear/nuklear_minios.c:403`

### nk_foreach `nk_foreach(cmd, ctx)`
- Defined: `progs/nuklear/nuklear_minios.c:408`

### nk_minios_font_width `static float nk_minios_font_width(nk_handle handle, float height,
                               ...`
- Defined: `progs/nuklear/nuklear_minios.c:554`
- Doc: if (c->background.a > 0) bg = col_to_idx(c->background); draw_text(c->x, c->y, c->string, c->length, fg, bg); break; } c

### nk_minios_font `struct nk_user_font nk_minios_font(void)`
- Defined: `progs/nuklear/nuklear_minios.c:559`

### feed_key `static void feed_key(struct nk_context *ctx, enum nk_keys key, int down)`
- Defined: `progs/nuklear/nuklear_minios.c:593`

### handle_scancode `static void handle_scancode(struct nk_context *ctx, unsigned char sc)`
- Defined: `progs/nuklear/nuklear_minios.c:597`

### nk_poll_input `void nk_poll_input(struct nk_context *ctx)`
- Defined: `progs/nuklear/nuklear_minios.c:638`

### nk_set_window_origin `void nk_set_window_origin(int x, int y)`
- Defined: `progs/nuklear/nuklear_minios.c:675`

## progs/piano/piano.c

### sys_pcm_open `static long sys_pcm_open(long on)`
- Defined: `progs/piano/piano.c:63`
- Doc: Upper bound on audio rendered per frame, in milliseconds.  The kernel-side audio ring absorbs up to ~3 seconds of buffer

### sys_pcm_submit `static long sys_pcm_submit(const void *buf, long len)`
- Defined: `progs/piano/piano.c:67`

### sys_pcm_pump `static long sys_pcm_pump(void)`
- Defined: `progs/piano/piano.c:70`

### o3_opreg `static void o3_opreg(int op, int regbase, int val)`
- Defined: `progs/piano/piano.c:77`

### o3_chreg `static void o3_chreg(int ch, int regbase, int val)`
- Defined: `progs/piano/piano.c:82`

### o3_instrument `static void o3_instrument(int ch, int vel)`
- Defined: `progs/piano/piano.c:89`
- Doc: Program one FM patch; `vel` (1..100) biases the carrier output level so a * louder velocity is audibly less attenuated, 

### o3_note `static void o3_note(int ch, int midi, int on)`
- Defined: `progs/piano/piano.c:119`

### clamp_midi `static int clamp_midi(int m)`
- Defined: `progs/piano/piano.c:140`
- Doc: unsigned fnum = (unsigned)(t * 65536.0 / 49716.0); o3_chreg(ch, 0xA0, fnum & 0xFF); o3_chreg(ch, 0xB0, ((unsigned)block 

### pedal_set `static void pedal_set(int on)`
- Defined: `progs/piano/piano.c:148`
- Doc: static int chan_used[MAX_VOICES]; static int chan_sustained[MAX_VOICES];/* key released but pedal holds the voice static

### note_off_key `static void note_off_key(int key)`
- Defined: `progs/piano/piano.c:160`

### note_on_key `static void note_on_key(int key, int midi, int vel)`
- Defined: `progs/piano/piano.c:174`

### fx_configure `static void fx_configure(int delay_ms, int tremolo_pct, int clip, int vol)`
- Defined: `progs/piano/piano.c:216`
- Doc: #define FX_DELAY_CAP (RATE)           /* 1 s of delay at 22050 Hz #define FX_DELAY_MAX_MS 800 #define FX_FEEDBACK 0.35f 

### fx_process `static float fx_process(float x)`
- Defined: `progs/piano/piano.c:234`

### sb_flush `static void sb_flush(void)`
- Defined: `progs/piano/piano.c:265`
- Doc: Flush a fully-filled buffer to the kernel audio ring.  When the ring is full the submit is refused; the buffer is kept i

### render_audio `static void render_audio(long ms)`
- Defined: `progs/piano/piano.c:274`

### key_rect `static void key_rect(int key, int *x, int *y, int *w, int *h)`
- Defined: `progs/piano/piano.c:317`
- Doc: define NKEYS ((int)(sizeof(keys) / sizeof(keys[0])))

### hit_key `static int hit_key(int mx, int my)`
- Defined: `progs/piano/piano.c:324`

### hit_velocity `static int hit_velocity(int key, int my)`
- Defined: `progs/piano/piano.c:342`
- Doc: Velocity 1..100 from the click's vertical position inside a key: the very * top is soft, the bottom is loud.

### ctrl_hit `static int ctrl_hit(int id, int mx, int my)`
- Defined: `progs/piano/piano.c:368`
- Doc: define NCTRLS ((int)(sizeof(ctrls) / sizeof(ctrls[0])))

### ctrl_active `static int ctrl_active(int id)`
- Defined: `progs/piano/piano.c:373`

### ctrl_press `static void ctrl_press(int id)`
- Defined: `progs/piano/piano.c:382`

### ui_run `static void ui_run(int bench_ms)`
- Defined: `progs/piano/piano.c:400`
- Doc: case 1: if (octave < 2) octave++; break; case 2: if (volume > 0) volume -= 5; break; case 3: if (volume < 100) volume +=

### run_selftest `static int run_selftest(void)`
- Defined: `progs/piano/piano.c:535`
- Doc: if (audio_on) render_audio(elapsed); } unsigned t0 = (unsigned)nk_sys_time_ms(); while ((unsigned)nk_sys_time_ms() - t0 

### main `int main(int argc, char **argv)`
- Defined: `progs/piano/piano.c:619`

## progs/quake2generic/q2generic_minios.c

### SYS_DOOM_FRAME `* SYS_DOOM_FRAME (211) and the kernel composites the buffer onto the
 * hi-res desktop as a title...`
- Defined: `progs/quake2generic/q2generic_minios.c:5`

### sys_kbd `static long sys_kbd(void)`
- Defined: `progs/quake2generic/q2generic_minios.c:28`

### sys_palette `static long sys_palette(const unsigned char *pal)`
- Defined: `progs/quake2generic/q2generic_minios.c:34`

### sys_kbd_raw `static long sys_kbd_raw(int on)`
- Defined: `progs/quake2generic/q2generic_minios.c:40`

### sys_vga_mode `static long sys_vga_mode(int on)`
- Defined: `progs/quake2generic/q2generic_minios.c:46`

### sys_doom_frame `static long sys_doom_frame(void)`
- Defined: `progs/quake2generic/q2generic_minios.c:52`

### sys_mouse `static long sys_mouse(int *buf)`
- Defined: `progs/quake2generic/q2generic_minios.c:58`

### sys_set_title `static long sys_set_title(const char *t)`
- Defined: `progs/quake2generic/q2generic_minios.c:64`

### q2g_parse_autoframes `static void q2g_parse_autoframes(int argc, char **argv)`
- Defined: `progs/quake2generic/q2generic_minios.c:86`

### QG_GetMouseDiff `void QG_GetMouseDiff(int *dx, int *dy)`
- Defined: `progs/quake2generic/q2generic_minios.c:101`

### QG_CaptureMouse `void QG_CaptureMouse(void)`
- Defined: `progs/quake2generic/q2generic_minios.c:112`

### QG_ReleaseMouse `void QG_ReleaseMouse(void)`
- Defined: `progs/quake2generic/q2generic_minios.c:116`

### QG_Mkdir `void QG_Mkdir(const char *path)`
- Defined: `progs/quake2generic/q2generic_minios.c:119`

### scancode_to_q2key `static unsigned char scancode_to_q2key(unsigned char raw)`
- Defined: `progs/quake2generic/q2generic_minios.c:123`

### extended_to_q2key `static unsigned char extended_to_q2key(unsigned char sc)`
- Defined: `progs/quake2generic/q2generic_minios.c:206`

### kbd_poll `static void kbd_poll(void)`
- Defined: `progs/quake2generic/q2generic_minios.c:224`

### SWimp_SetPalette `void SWimp_SetPalette(const unsigned char *palette)`
- Defined: `progs/quake2generic/q2generic_minios.c:254`

### SWimp_SetMode `rserr_t SWimp_SetMode(int *pwidth, int *pheight, int mode, qboolean fullscreen)`
- Defined: `progs/quake2generic/q2generic_minios.c:264`

### SWimp_Init `int SWimp_Init(void *hInstance, void *wndProc)`
- Defined: `progs/quake2generic/q2generic_minios.c:281`

### SWimp_Shutdown `void SWimp_Shutdown(void)`
- Defined: `progs/quake2generic/q2generic_minios.c:287`

### SWimp_BeginFrame `void SWimp_BeginFrame(float camera_separation)`
- Defined: `progs/quake2generic/q2generic_minios.c:290`

### SWimp_EndFrame `void SWimp_EndFrame(void)`
- Defined: `progs/quake2generic/q2generic_minios.c:293`

### SWimp_AppActivate `void SWimp_AppActivate(qboolean active)`
- Defined: `progs/quake2generic/q2generic_minios.c:312`

### QG_Milliseconds `int QG_Milliseconds(void)`
- Defined: `progs/quake2generic/q2generic_minios.c:316`

### main `int main(int argc, char **argv)`
- Defined: `progs/quake2generic/q2generic_minios.c:320`

## progs/src/aes.c

### aes_read_all `static char *aes_read_all(const char *name, int *len)`
- Defined: `progs/src/aes.c:68`

### aes_write_all `static int aes_write_all(const char *name, char *data, int len)`
- Defined: `progs/src/aes.c:85`

### aes_has `static int aes_has(const char *s, const char *needle)`
- Defined: `progs/src/aes.c:95`

### hex_val `static int hex_val(int c)`
- Defined: `progs/src/aes.c:109`

### aes_parse_hex `static int aes_parse_hex(const char *s, int want, int *out)`
- Defined: `progs/src/aes.c:116`

### aes_gf_mul `static int aes_gf_mul(int a, int b)`
- Defined: `progs/src/aes.c:130`
- Doc: static int aes_parse_hex(const char *s, int want, int *out) { int i, hi, lo; if ((int)strlen(s) != want) return 0; for (

### aes_xtime `static int aes_xtime(int x)`
- Defined: `progs/src/aes.c:141`

### aes_rotl8 `static int aes_rotl8(int x, int n)`
- Defined: `progs/src/aes.c:147`

### aes_init_tables `static void aes_init_tables(void)`
- Defined: `progs/src/aes.c:155`
- Doc: Build the S-box from first principles: multiplicative inverse in GF(2^8) composed with the FIPS-197 affine transform.  Z

### aes_key_expand `static void aes_key_expand(const int *key)`
- Defined: `progs/src/aes.c:174`
- Doc: Expand the 32-byte key into AES_RK_LEN round-key bytes (FIPS-197 for Nk=8, Nr=14: RotWord plus SubWord every Nk words, a

### aes_add_round_key `static void aes_add_round_key(int round)`
- Defined: `progs/src/aes.c:208`

### aes_sub_bytes `static void aes_sub_bytes(void)`
- Defined: `progs/src/aes.c:214`

### aes_shift_rows `static void aes_shift_rows(void)`
- Defined: `progs/src/aes.c:219`

### aes_mix_columns `static void aes_mix_columns(void)`
- Defined: `progs/src/aes.c:227`

### aes_cipher `static void aes_cipher(void)`
- Defined: `progs/src/aes.c:247`

### aes_iv_increment `static void aes_iv_increment(void)`
- Defined: `progs/src/aes.c:263`
- Doc: int r; aes_add_round_key(0); for (r = 1; r < AES_ROUNDS; r++) { aes_sub_bytes(); aes_shift_rows(); aes_mix_columns(); ae

### aes_ctr_crypt `static void aes_ctr_crypt(char *data, int len)`
- Defined: `progs/src/aes.c:273`
- Doc: aes_add_round_key(AES_ROUNDS); } /* Big-endian increment of the whole counter block (SP 800-38A CTR). static void aes_iv

### aes_hdr_put `static void aes_hdr_put(char *h, int size)`
- Defined: `progs/src/aes.c:287`

### aes_hdr_get `static int aes_hdr_get(char *h)`
- Defined: `progs/src/aes.c:298`

### aes_tool_name `static const char *aes_tool_name(int decode)`
- Defined: `progs/src/aes.c:306`

### aes_run `static int aes_run(int decode, const char *keyhex, const char *noncehex,
                   const...`
- Defined: `progs/src/aes.c:311`

### main `int main(int argc, char **argv)`
- Defined: `progs/src/aes.c:383`

## progs/src/audio.c

### syscall1 `static long syscall1(long n, long a1)`
- Defined: `progs/src/audio.c:2`
- Doc: include "minios_abi.h"

### syscall2 `static long syscall2(long n, long a1, long a2)`
- Defined: `progs/src/audio.c:8`

### syscall3 `static long syscall3(long n, long a1, long a2, long a3)`
- Defined: `progs/src/audio.c:14`

### syscall0 `static long syscall0(long n)`
- Defined: `progs/src/audio.c:20`

### audio_init `int audio_init(void)`
- Defined: `progs/src/audio.c:26`

### audio_tone `void audio_tone(unsigned freq)`
- Defined: `progs/src/audio.c:30`

### audio_pcm_open `int audio_pcm_open(unsigned rate, unsigned channels, unsigned format)`
- Defined: `progs/src/audio.c:34`

### audio_pcm_submit `int audio_pcm_submit(const void *buf, unsigned len)`
- Defined: `progs/src/audio.c:39`

### audio_pcm_pump `void audio_pcm_pump(void)`
- Defined: `progs/src/audio.c:43`

### audio_pcm_close `void audio_pcm_close(void)`
- Defined: `progs/src/audio.c:47`

### audio_set_volume `void audio_set_volume(unsigned volume)`
- Defined: `progs/src/audio.c:51`

### audio_get_volume `unsigned audio_get_volume(void)`
- Defined: `progs/src/audio.c:55`

### audio_sb16_present `int audio_sb16_present(void)`
- Defined: `progs/src/audio.c:59`

### audio_stream_open `int audio_stream_open(void)`
- Defined: `progs/src/audio.c:63`

### audio_stream_close `void audio_stream_close(int id)`
- Defined: `progs/src/audio.c:67`

### audio_stream_submit `int audio_stream_submit(int id, const void *buf, unsigned len)`
- Defined: `progs/src/audio.c:71`

### audio_stream_volume `void audio_stream_volume(int id, unsigned char vol)`
- Defined: `progs/src/audio.c:75`

## progs/src/cp.c

### main `int main(int argc, char **argv)`
- Defined: `progs/src/cp.c:9`
- Doc: define CP_BUF_SIZE 4096 define CP_EXIT_FAIL 1

## progs/src/cpl.c

### read_cpl `static long read_cpl(void)`
- Defined: `progs/src/cpl.c:6`
- Doc: Ring-3 privilege probe. Reads the CS selector at runtime and exits with the CPL it is executing at. Under the isolation 

### exit_now `static void exit_now(long code)`
- Defined: `progs/src/cpl.c:11`

### _start `void _start(void)`
- Defined: `progs/src/cpl.c:15`

## progs/src/fib.c

### fib `int fib(int n)`
- Defined: `progs/src/fib.c:1`

### main `int main(void)`
- Defined: `progs/src/fib.c:5`

## progs/src/freedom.c

### atoi `static int atoi(char *s)`
- Defined: `progs/src/freedom.c:127`
- Doc: static char f_dom[FREEDOM_DOM_BUF]; static int  f_domlen; static char f_css[FREEDOM_CSS_BUF]; static int  f_csslen; stat

### append `static int append(char *dst, int pos, char *src, int cap)`
- Defined: `progs/src/freedom.c:140`
- Doc: Append src to dst at pos; returns the new length or -1 when it does * not fit.

### ci_lower `static int ci_lower(int c)`
- Defined: `progs/src/freedom.c:148`

### ci_starts `static int ci_starts(char *s, char *pre)`
- Defined: `progs/src/freedom.c:155`
- Doc: int n; n = strlen(src); if (pos + n >= cap) return -1; memcpy(dst + pos, src, n); dst[pos + n] = 0; return pos + n; } st

### ci_eq `static int ci_eq(char *a, char *b)`
- Defined: `progs/src/freedom.c:166`
- Doc: } /* Case-insensitive starts-with. static int ci_starts(char *s, char *pre) { while (*pre) { if (!*s) return 0; if (ci_l

### ci_index `static int ci_index(char *s, char *needle)`
- Defined: `progs/src/freedom.c:176`
- Doc: return 1; } /* Case-insensitive equality. static int ci_eq(char *a, char *b) { while (*a && *b) { if (ci_lower(*a) != ci

### looks_like_url `static int looks_like_url(char *s)`
- Defined: `progs/src/freedom.c:185`
- Doc: } return *a == 0 && *b == 0; } /* Case-insensitive index of needle in haystack, or -1. static int ci_index(char *s, char

### has_scheme `static int has_scheme(char *s)`
- Defined: `progs/src/freedom.c:199`
- Doc: Does s begin with "<scheme>:" per RFC 3986 (ALPHA *(ALPHA/DIGIT/+/-/.) ":")? Any such prefix makes the string a scheme, 

### make_search `static void make_search(char *out, char *query, int cap)`
- Defined: `progs/src/freedom.c:215`
- Doc: char c; c = s[0]; if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) return 0; for (i = 1; s[i]; i++) { c = s[i]; 

### split_url `static int split_url(char *url)`
- Defined: `progs/src/freedom.c:239`
- Doc: Split an http:// or https:// URL into f_host, f_path, f_port and f_secure. Returns 0 on failure. The input buffer is nev

### resolve_redirect `static int resolve_redirect(void)`
- Defined: `progs/src/freedom.c:286`
- Doc: Recompute f_host/f_path/f_port/f_secure from the last Location value. Returns 1 when the chase may continue, 0 when it m

### put_ws `static void put_ws(void)`
- Defined: `progs/src/freedom.c:338`
- Doc: if (l + 1 >= 128) return 0; f_path[0] = '/'; memcpy(f_path + 1, loc, l); f_path[l + 1] = 0; } else { if (last + 1 + l >=

### put_utf `static void put_utf(int c)`
- Defined: `progs/src/freedom.c:350`
- Doc: Print one text byte through the UTF-8 gate. Remote pages are hostile data: bytes outside a valid UTF-8 sequence (overlon

### put_text `static void put_text(int c)`
- Defined: `progs/src/freedom.c:400`
- Doc: Print one text byte: whitespace collapses, everything else goes * through the UTF-8 gate. Dump modes suppress the page t

### css_append `static void css_append(char *s, int n)`
- Defined: `progs/src/freedom.c:455`
- Doc: } else if (v >= 2048 && v < 65536) { put_text(224 | (v >> 12)); put_text(128 | ((v >> 6) & 63)); put_text(128 | (v & 63)

### css_line `static void css_line(char *s)`
- Defined: `progs/src/freedom.c:461`

### dom_append `static void dom_append(char *s, int n)`
- Defined: `progs/src/freedom.c:466`

### dom_space `static void dom_space(void)`
- Defined: `progs/src/freedom.c:472`

### dom_nl `static void dom_nl(void)`
- Defined: `progs/src/freedom.c:476`

### record_attr `static void record_attr(void)`
- Defined: `progs/src/freedom.c:482`
- Doc: int i; for (i = 0; i < n && f_domlen < FREEDOM_DOM_BUF - 1; i++) f_dom[f_domlen++] = s[i]; } static void dom_space(void)

### is_void_tag `static int is_void_tag(void)`
- Defined: `progs/src/freedom.c:507`
- Doc: f_hreflen = f_vallen < 127 ? f_vallen : 127; memcpy(f_href, f_val, f_hreflen); f_href[f_hreflen] = 0; } else if (ci_eq(f

### classify_tag `static void classify_tag(void)`
- Defined: `progs/src/freedom.c:519`
- Doc: A tag was fully collected into f_tagn (+ attributes). Decide what it * does to the stream and the dumps.

### body_byte `static void body_byte(int c)`
- Defined: `progs/src/freedom.c:604`
- Doc: } dom_nl(); if (!is_void_tag()) f_depth++; } if (ci_eq(f_tagn, "br") || ci_eq(f_tagn, "p") || ci_eq(f_tagn, "div") || ci

### head_line `static void head_line(char *line)`
- Defined: `progs/src/freedom.c:769`
- Doc: f_rel_ss = 0; return; } if (c == '&') { f_entlen = 1; f_ent[0] = 0; return; } put_text(c); } /* --- HTTP ---------------

### parse_head `static void parse_head(void)`
- Defined: `progs/src/freedom.c:794`
- Doc: Parse the collected header block f_hdr[0..f_hlen-1] (the last four * bytes are the terminating CRLF CRLF).

### recv_body `static int recv_body(int fd, char *buf, int len)`
- Defined: `progs/src/freedom.c:816`
- Doc: f_hdr[lend] = 0; if (i == 0) { char *sp; sp = strchr(f_hdr, ' '); if (sp) f_status = atoi(sp + 1); } else if (lend > i) 

### send_all `static int send_all(int fd, char *buf, int len)`
- Defined: `progs/src/freedom.c:822`
- Doc: head_line(f_hdr + i); } f_hdr[lend] = '\r'; i = lend + 2; } } /* Receive body bytes: TLS for f_secure, plain TCP otherwi

### fetch `static int fetch(char *host, char *path, int port)`
- Defined: `progs/src/freedom.c:833`
- Doc: Send one HTTP request and process the response body. Returns the status code, or 0 on transport failure. Sets f_redir wh

### fetch_css `static void fetch_css(char *host, char *path)`
- Defined: `progs/src/freedom.c:993`
- Doc: Fetch a linked stylesheet and print its raw body (through the UTF-8 * gate). No redirect chasing: the bound is one reque

### print_css_dump `static void print_css_dump(void)`
- Defined: `progs/src/freedom.c:1071`
- Doc: } continue; } f_ws = 0; put_utf(c); got++; } } close(fd); putchar('\n'); printf("freedom: %s (%d bytes)\n", host, got); 

### print_dom_dump `static void print_dom_dump(void)`
- Defined: `progs/src/freedom.c:1080`
- Doc: putchar('\n'); printf("freedom: %s (%d bytes)\n", host, got); } /* Print the collected CSS dump. static void print_css_d

### main `int main(int argc, char **argv)`
- Defined: `progs/src/freedom.c:1086`

## progs/src/ftest.c

### main `int main(int argc, char **argv)`
- Defined: `progs/src/ftest.c:9`

## progs/src/hello.c

### main `int main(int argc, char **argv)`
- Defined: `progs/src/hello.c:3`

## progs/src/http.c

### atoi `int atoi(char *s)`
- Defined: `progs/src/http.c:18`
- Doc: int socket(int domain, int type, int proto); int connect(int fd, void *addr, int addrlen); int sendto(int fd, char *buf,

### main `int main(int argc, char **argv)`
- Defined: `progs/src/http.c:28`

## progs/src/json.c

### js_read_all `static char *js_read_all(const char *name, int *len)`
- Defined: `progs/src/json.c:57`

### js_new `static int js_new(void)`
- Defined: `progs/src/json.c:75`

### js_skip_ws `static void js_skip_ws(void)`
- Defined: `progs/src/json.c:80`

### js_peek `static int js_peek(void)`
- Defined: `progs/src/json.c:88`

### js_parse_string `static int js_parse_string(void)`
- Defined: `progs/src/json.c:96`

### js_parse_number `static int js_parse_number(void)`
- Defined: `progs/src/json.c:132`

### js_key_match `static int js_key_match(int child, const char *key)`
- Defined: `progs/src/json.c:142`

### js_parse_object `static int js_parse_object(void)`
- Defined: `progs/src/json.c:146`

### js_parse_array `static int js_parse_array(void)`
- Defined: `progs/src/json.c:181`

### js_parse_value `static int js_parse_value(void)`
- Defined: `progs/src/json.c:210`

### js_indent `static void js_indent(int n)`
- Defined: `progs/src/json.c:280`
- Doc: neg = 0; if (c == '-') { neg = 1; js_pos++; } node = js_new(); if (node < 0) return -1; js_type[node] = JS_NUM; js_num[n

### js_print_str `static void js_print_str(const char *s)`
- Defined: `progs/src/json.c:285`

### js_print_value `static void js_print_value(int node, int depth)`
- Defined: `progs/src/json.c:302`

### js_find_member `static int js_find_member(int obj, const char *key)`
- Defined: `progs/src/json.c:346`
- Doc: i = 0; while (c >= 0) { js_indent(depth + 1); js_print_value(c, depth + 1); if (i < js_count[node] - 1) putchar(','); pu

### js_array_at `static int js_array_at(int arr, int idx)`
- Defined: `progs/src/json.c:356`

### js_query `static int js_query(int root, const char *path)`
- Defined: `progs/src/json.c:368`

### main `int main(int argc, char **argv)`
- Defined: `progs/src/json.c:400`

## progs/src/kmem.c

### syscall3 `static long syscall3(long n, long a1, long a2, long a3)`
- Defined: `progs/src/kmem.c:6`
- Doc: Kernel-pointer rejection probe. Passes a kernel-heap address (0x2000000, a supervisor page) to write(2). The hardened sy

### exit_now `static void exit_now(long code)`
- Defined: `progs/src/kmem.c:12`

### _start `void _start(void)`
- Defined: `progs/src/kmem.c:16`

## progs/src/ldhello.c

### main `int main(void)`
- Defined: `progs/src/ldhello.c:1`

## progs/src/lxhello.c

### lx_syscall3 `static long lx_syscall3(long n, long a1, long a2, long a3)`
- Defined: `progs/src/lxhello.c:10`
- Doc: lxhello — a genuine Linux x86-64 ELF executable.  Built with `gcc -static -no-pie -nostdlib` so it links as ET_EXEC at 0

### lx_strlen `static unsigned long lx_strlen(const char *s)`
- Defined: `progs/src/lxhello.c:22`
- Doc: define SYS_write 1 define SYS_exit  60

### lx_write `static void lx_write(const char *s)`
- Defined: `progs/src/lxhello.c:28`

### lx_write_int `static void lx_write_int(long v)`
- Defined: `progs/src/lxhello.c:32`

### lmain `int lmain(long argc, char **argv)`
- Defined: `progs/src/lxhello.c:46`
- Doc: static void lx_write_int(long v) { char buf[24]; int i = (int)sizeof(buf); int neg = 0; buf[--i] = 0; if (v < 0) { neg =

## progs/src/lz4.c

### lz4_has `static int lz4_has(const char *s, const char *needle)`
- Defined: `progs/src/lz4.c:38`
- Doc: define LZ4_EXIT_FAIL 1

### lz4_read_all `static char *lz4_read_all(const char *name, int *len)`
- Defined: `progs/src/lz4.c:52`

### lz4_write_all `static int lz4_write_all(const char *name, char *data, int len)`
- Defined: `progs/src/lz4.c:69`

### lz4_compress_file `static int lz4_compress_file(const char *src, const char *dst)`
- Defined: `progs/src/lz4.c:79`

### lz4_decompress_file `static int lz4_decompress_file(const char *src, const char *dst)`
- Defined: `progs/src/lz4.c:116`

### main `int main(int argc, char **argv)`
- Defined: `progs/src/lz4.c:163`

## progs/src/lzss.c

### lz_in_getc `static int lz_in_getc(void)`
- Defined: `progs/src/lzss.c:63`

### lz_out_put `static void lz_out_put(int c)`
- Defined: `progs/src/lzss.c:68`

### lz_putbit1 `static void lz_putbit1(void)`
- Defined: `progs/src/lzss.c:73`

### lz_putbit0 `static void lz_putbit0(void)`
- Defined: `progs/src/lzss.c:83`

### lz_flush_bits `static void lz_flush_bits(void)`
- Defined: `progs/src/lzss.c:92`

### lz_out_literal `static void lz_out_literal(int c)`
- Defined: `progs/src/lzss.c:96`

### lz_out_pair `static void lz_out_pair(int x, int y)`
- Defined: `progs/src/lzss.c:104`

### lz_encode `static int lz_encode(void)`
- Defined: `progs/src/lzss.c:115`

### lz_getbit `static int lz_getbit(int n)`
- Defined: `progs/src/lzss.c:160`

### lz_decode `static int lz_decode(void)`
- Defined: `progs/src/lzss.c:176`

### lz_hdr_put `static void lz_hdr_put(char *h, int size)`
- Defined: `progs/src/lzss.c:205`

### lz_hdr_get `static int lz_hdr_get(char *h)`
- Defined: `progs/src/lzss.c:216`

### lz_has `static int lz_has(const char *s, const char *needle)`
- Defined: `progs/src/lzss.c:224`

### lz_read_all `static char *lz_read_all(const char *name, int *len)`
- Defined: `progs/src/lzss.c:238`

### lz_write_all `static int lz_write_all(const char *name, char *data, int len)`
- Defined: `progs/src/lzss.c:255`

### lz_compress `static int lz_compress(const char *src, const char *dst)`
- Defined: `progs/src/lzss.c:265`

### lz_decompress `static int lz_decompress(const char *src, const char *dst)`
- Defined: `progs/src/lzss.c:312`

### main `int main(int argc, char **argv)`
- Defined: `progs/src/lzss.c:384`

## progs/src/mmreuse.c

### mmap_anon `static long mmap_anon(long len)`
- Defined: `progs/src/mmreuse.c:7`
- Doc: mmap/munmap reclaim stress test.  Repeatedly maps and unmaps a large region.  On a kernel whose munmap never returns add

### munmap `static long munmap(long addr, long len)`
- Defined: `progs/src/mmreuse.c:20`

### exit_now `static void exit_now(long code)`
- Defined: `progs/src/mmreuse.c:30`

### _start `void _start(void)`
- Defined: `progs/src/mmreuse.c:34`

## progs/src/nx.c

### write_str `static long write_str(const char *s, long n)`
- Defined: `progs/src/nx.c:10`

### exit_now `static void exit_now(long code)`
- Defined: `progs/src/nx.c:18`

### _start `void _start(void)`
- Defined: `progs/src/nx.c:22`

## progs/src/opl3.c

### sys_time `static long sys_time(void)`
- Defined: `progs/src/opl3.c:35`
- Doc: define F_NUM_FACTOR 65536.0 / 49716.0

### sys_open `static long sys_open(long on)`
- Defined: `progs/src/opl3.c:39`

### sys_submit `static long sys_submit(const void *buf, long len)`
- Defined: `progs/src/opl3.c:42`

### busy_ms `static void busy_ms(long ms)`
- Defined: `progs/src/opl3.c:45`

### opl3_set_instrument `static void opl3_set_instrument(opl3_chip *chip)`
- Defined: `progs/src/opl3.c:52`
- Doc: } static long sys_open(long on) { long r; __asm__ volatile("syscall":"=a"(r):"a"(SYS_SB16_OPEN),"D"(on):"rcx","r11","mem

### opl3_note `static void opl3_note(opl3_chip *chip, unsigned block, unsigned fnum, int on)`
- Defined: `progs/src/opl3.c:68`

### render `static void render(opl3_chip *chip, long ms, long *fail)`
- Defined: `progs/src/opl3.c:77`
- Doc: Render `ms` of the current note and stream it to the SB16.  Each submit is one DMA buffer of MONO_BYTES; submissions are

### main `int main(void)`
- Defined: `progs/src/opl3.c:106`

## progs/src/sbtone.c

### buffers `*
 * Exit code is the number of submitted buffers (0 on failure to open).
 */

#include <stdio.h>...`
- Defined: `progs/src/sbtone.c:13`

### main `int main(void)`
- Defined: `progs/src/sbtone.c:35`

## progs/src/shell.py

### run_capture `def run_capture(cmd, args)`
- Defined: `progs/src/shell.py:20`
- Depends on: `progs/lua/minios.c`

### expand `def expand(line, env)`
- Defined: `progs/src/shell.py:30`
- Depends on: `progs/lua/minios.c`

### main `def main()`
- Defined: `progs/src/shell.py:36`
- Depends on: `progs/lua/minios.c`

## progs/src/test.c

### add `int add(int a, int b)`
- Defined: `progs/src/test.c:1`

### main `int main(void)`
- Defined: `progs/src/test.c:2`

## progs/src/test.lua

### check
- Defined: `progs/src/test.lua:12`

### write_file
- Defined: `progs/src/test.lua:22`

### read_file
- Defined: `progs/src/test.lua:30`

### test_module_bindings
- Defined: `progs/src/test.lua:40`

### test_filesystem
- Defined: `progs/src/test.lua:53`

### test_xxhash
- Defined: `progs/src/test.lua:70`

### test_stb
- Defined: `progs/src/test.lua:75`

### test_dlmalloc
- Defined: `progs/src/test.lua:80`

### test_hello
- Defined: `progs/src/test.lua:85`

### test_ftest
- Defined: `progs/src/test.lua:90`

### test_minigcc
- Defined: `progs/src/test.lua:95`

### test_ld
- Defined: `progs/src/test.lua:100`

### test_toolchain_roundtrip
- Defined: `progs/src/test.lua:112`

### test_spawn_preserves_interpreter
- Defined: `progs/src/test.lua:122`

### test_bin_cp
- Defined: `progs/src/test.lua:135`

### test_bin_lz4
- Defined: `progs/src/test.lua:141`

### test_bin_lzss
- Defined: `progs/src/test.lua:158`

### test_bin_aes
- Defined: `progs/src/test.lua:175`

### test_bin_json
- Defined: `progs/src/test.lua:194`

### test_bin_freedom
- Defined: `progs/src/test.lua:205`

## progs/src/test.py

### check `def check(name, cond, detail)`
- Defined: `progs/src/test.py:15`
- Depends on: `progs/lua/minios.c`

### safe_run `def safe_run()`
- Defined: `progs/src/test.py:25`
- Depends on: `progs/lua/minios.c`

### test_module_bindings `def test_module_bindings()`
- Defined: `progs/src/test.py:38`
- Depends on: `progs/lua/minios.c`

### test_filesystem `def test_filesystem()`
- Defined: `progs/src/test.py:56`
- Depends on: `progs/lua/minios.c`

### test_xxhash `def test_xxhash()`
- Defined: `progs/src/test.py:72`
- Depends on: `progs/lua/minios.c`

### test_stb `def test_stb()`
- Defined: `progs/src/test.py:77`
- Depends on: `progs/lua/minios.c`

### test_dlmalloc `def test_dlmalloc()`
- Defined: `progs/src/test.py:82`
- Depends on: `progs/lua/minios.c`

### test_hello `def test_hello()`
- Defined: `progs/src/test.py:87`
- Depends on: `progs/lua/minios.c`

### test_ftest `def test_ftest()`
- Defined: `progs/src/test.py:92`
- Depends on: `progs/lua/minios.c`

### test_minigcc `def test_minigcc()`
- Defined: `progs/src/test.py:97`
- Depends on: `progs/lua/minios.c`

### test_ld `def test_ld()`
- Defined: `progs/src/test.py:102`
- Depends on: `progs/lua/minios.c`

### test_toolchain_roundtrip `def test_toolchain_roundtrip()`
- Defined: `progs/src/test.py:119`
- Depends on: `progs/lua/minios.c`

### test_spawn_preserves_interpreter `def test_spawn_preserves_interpreter()`
- Defined: `progs/src/test.py:134`
- Depends on: `progs/lua/minios.c`

### test_bin_cp `def test_bin_cp()`
- Defined: `progs/src/test.py:148`
- Depends on: `progs/lua/minios.c`

### test_bin_lz4 `def test_bin_lz4()`
- Defined: `progs/src/test.py:153`
- Depends on: `progs/lua/minios.c`

### test_bin_lzss `def test_bin_lzss()`
- Defined: `progs/src/test.py:181`
- Depends on: `progs/lua/minios.c`

### test_bin_aes `def test_bin_aes()`
- Defined: `progs/src/test.py:209`
- Depends on: `progs/lua/minios.c`

### test_bin_json `def test_bin_json()`
- Defined: `progs/src/test.py:239`
- Depends on: `progs/lua/minios.c`

### test_bin_freedom `def test_bin_freedom()`
- Defined: `progs/src/test.py:253`
- Depends on: `progs/lua/minios.c`

### main `def main()`
- Defined: `progs/src/test.py:261`
- Depends on: `progs/lua/minios.c`

## progs/src/w1.c

### main `int main(void)`
- Defined: `progs/src/w1.c:2`

## progs/topogpt3/topogpt3.c

### tg_exp `static float tg_exp(float x)`
- Defined: `progs/topogpt3/topogpt3.c:113`

### tg_tanh `static float tg_tanh(float x)`
- Defined: `progs/topogpt3/topogpt3.c:127`

### tg_sin `static float tg_sin(float x)`
- Defined: `progs/topogpt3/topogpt3.c:134`

### tg_cos `static float tg_cos(float x)`
- Defined: `progs/topogpt3/topogpt3.c:143`

### tg_fabs `static float tg_fabs(float x)`
- Defined: `progs/topogpt3/topogpt3.c:147`

### tg_log `static float tg_log(float x)`
- Defined: `progs/topogpt3/topogpt3.c:151`

### tg_fmax `static float tg_fmax(float a, float b)`
- Defined: `progs/topogpt3/topogpt3.c:163`

### tg_fmin `static float tg_fmin(float a, float b)`
- Defined: `progs/topogpt3/topogpt3.c:167`

### load_vocab `static void load_vocab(const char *path)`
- Defined: `progs/topogpt3/topogpt3.c:254`

### build_torus_graph `static void build_torus_graph(void)`
- Defined: `progs/topogpt3/topogpt3.c:295`
- Doc: ====================================================================== SECTION 4: TORUS GRAPH BUILDER * ================

### precompute_rope `static void precompute_rope(void)`
- Defined: `progs/topogpt3/topogpt3.c:326`
- Doc: ====================================================================== SECTION 5: ROPE PRECOMPUTATION * ================

### matvec `static void matvec(const float *W, const float *x, float *y, int rows, int cols)`
- Defined: `progs/topogpt3/topogpt3.c:358`
- Doc: ====================================================================== SECTION 6: MATRIX OPERATIONS * ==================

### matvec_bias `static void matvec_bias(const float *W, const float *b, const float *x, float *y,
               ...`
- Defined: `progs/topogpt3/topogpt3.c:369`

### rmsnorm `static void rmsnorm(const float *x, const float *w, float *y, int d)`
- Defined: `progs/topogpt3/topogpt3.c:381`

### softmax `static void softmax(float *x, int n)`
- Defined: `progs/topogpt3/topogpt3.c:390`

### gelu `static void gelu(float *x, int n)`
- Defined: `progs/topogpt3/topogpt3.c:399`

### silu `static void silu(float *x, int n)`
- Defined: `progs/topogpt3/topogpt3.c:409`

### swiglu `static void swiglu(const float *gate_w, const float *up_w, const float *down_w,
                 ...`
- Defined: `progs/topogpt3/topogpt3.c:417`

### quat_normalize `static void quat_normalize(float *q)`
- Defined: `progs/topogpt3/topogpt3.c:434`
- Doc: ====================================================================== SECTION 7: QUATERNION OPERATIONS * ==============

### quat_hamilton `static void quat_hamilton(const float *a, const float *b, float *c)`
- Defined: `progs/topogpt3/topogpt3.c:439`

### quat_linear `static void quat_linear(const float *Ww, const float *Wx, const float *Wy, const float *Wz,
     ...`
- Defined: `progs/topogpt3/topogpt3.c:448`
- Doc: static void quat_normalize(float *q) { float n = tg_sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]); if (n > 1e-8f) 

### ifft_radix2 `static void ifft_radix2(float *real, float *imag, int n)`
- Defined: `progs/topogpt3/topogpt3.c:504`

### rfft `static void rfft(const float *x, float *Xr, float *Xi, int n)`
- Defined: `progs/topogpt3/topogpt3.c:513`
- Doc: cur_r = nr; } } } } static void ifft_radix2(float *real, float *imag, int n) { int i; for (i = 0; i < n; i++) imag[i] = 

### irfft `static void irfft(const float *Xr, const float *Xi, float *x, int n)`
- Defined: `progs/topogpt3/topogpt3.c:522`
- Doc: fft_radix2(real, imag, n); for (i = 0; i < n; i++) { real[i] /= (float)n; imag[i] = -imag[i] / (float)n; } } /* Real FFT

### filter1d `static void filter1d(const float *x, const float *kr, const float *ki,
                      floa...`
- Defined: `progs/topogpt3/topogpt3.c:536`
- Doc: ====================================================================== SECTION 9: SPECTRAL 1D FILTER * =================

### ifft2d `static void ifft2d(float *data_r, float *data_i, int h, int w)`
- Defined: `progs/topogpt3/topogpt3.c:579`

### rfft2d_real `static void rfft2d_real(const float *data, float *out_r, float *out_i,
                         i...`
- Defined: `progs/topogpt3/topogpt3.c:602`
- Doc: ifft_radix2(row_re, row_im, w); for (c = 0; c < w; c++) { re[r*w+c] = row_re[c]; im[r*w+c] = row_im[c]; } } /* IFFT colu

### irfft2d `static void irfft2d(const float *in_r, const float *in_i, float *out,
                     int h,...`
- Defined: `progs/topogpt3/topogpt3.c:629`
- Doc: for (r = 0; r < h; r++) { col_re[r] = re[r*w+c]; col_im[r] = im[r*w+c]; } fft_radix2(col_re, col_im, h); for (r = 0; r <

### cmul `static void cmul(float ar, float ai, float cr, float di, float *rr, float *ri)`
- Defined: `progs/topogpt3/topogpt3.c:664`
- Doc: ====================================================================== SECTION 11: QUATERNION SPECTRAL LAYER 2D * ======

### spectral_contract `static void spectral_contract(const float *Wr, const float *Wi,
                               co...`
- Defined: `progs/topogpt3/topogpt3.c:670`
- Doc: ====================================================================== SECTION 11: QUATERNION SPECTRAL LAYER 2D * ======

### quat_spectral_layer_2d `static void quat_spectral_layer_2d(
    const float *x, float *y,
    const float *kr_w, const fl...`
- Defined: `progs/topogpt3/topogpt3.c:694`

### spectral_ae_encode `static void spectral_ae_encode(const float *x, float *z, const LayerWeights *lw)`
- Defined: `progs/topogpt3/topogpt3.c:784`
- Doc: ====================================================================== SECTION 12: SPECTRAL AUTOENCODER FORWARD * ======

### spectral_ae_decode `static void spectral_ae_decode(const float *z, float *x, const LayerWeights *lw)`
- Defined: `progs/topogpt3/topogpt3.c:792`

### process_torus_grid `static void process_torus_grid(const float *grid, float *out, const LayerWeights *lw)`
- Defined: `progs/topogpt3/topogpt3.c:799`

### torus_soft_assign `static void torus_soft_assign(const float *phi1, const float *phi2,
                             ...`
- Defined: `progs/topogpt3/topogpt3.c:820`
- Doc: ====================================================================== SECTION 13: TORUS BRAIN FORWARD * ===============

### message_passing `static void message_passing(const float *node_feat, float *out,
                             cons...`
- Defined: `progs/topogpt3/topogpt3.c:842`

### torus_brain_forward `static void torus_brain_forward(const float *x, float *out, float *recon_loss,
                  ...`
- Defined: `progs/topogpt3/topogpt3.c:887`

### attention_forward `static void attention_forward(const float *x, float *out, int layer_idx, int pos, int total_kv_co...`
- Defined: `progs/topogpt3/topogpt3.c:977`
- Doc: ====================================================================== SECTION 14: ATTENTION FORWARD * =================

### moe_forward `static void moe_forward(const float *x, float *out, const LayerWeights *lw)`
- Defined: `progs/topogpt3/topogpt3.c:1077`
- Doc: ====================================================================== SECTION 15: MoE ROUTING * =======================

### forward `static void forward(const int *token_ids, int seq_len, float *logits_out)`
- Defined: `progs/topogpt3/topogpt3.c:1127`
- Doc: ====================================================================== SECTION 16: FULL MODEL FORWARD  Processes tokens 

### tokenize_string `static int tokenize_string(const char *text, int *tokens, int max_tokens)`
- Defined: `progs/topogpt3/topogpt3.c:1194`

### apply_temperature `static void apply_temperature(float *logits, int n, float temp)`
- Defined: `progs/topogpt3/topogpt3.c:1209`
- Doc: ====================================================================== SECTION 18: SAMPLING * ==========================

### apply_repetition_penalty `static void apply_repetition_penalty(float *logits, int n, const int *tokens,
                   ...`
- Defined: `progs/topogpt3/topogpt3.c:1215`

### apply_top_k `static void apply_top_k(float *logits, int n, int k)`
- Defined: `progs/topogpt3/topogpt3.c:1228`

### sample `static int sample(const float *logits, int n)`
- Defined: `progs/topogpt3/topogpt3.c:1247`

### load_weights `static int load_weights(const char *path)`
- Defined: `progs/topogpt3/topogpt3.c:1281`
- Doc: ====================================================================== SECTION 19: WEIGHT LOADER  Reads the binary file 

### load_weights_fp16 `static int load_weights_fp16(const char *path)`
- Defined: `progs/topogpt3/topogpt3.c:1451`

### load_weights_auto `static int load_weights_auto(const char *path)`
- Defined: `progs/topogpt3/topogpt3.c:1583`
- Doc: printf("  Layer %d loaded\n", i); } READ_TENSOR16(W.final_norm, D_MODEL); #undef SKIP_TENSOR16 #undef READ_TENSOR16 fclo

### time_now_ms `static double time_now_ms(void)`
- Defined: `progs/topogpt3/topogpt3.c:1600`
- Doc: ====================================================================== SECTION 20: TIMING * ============================

### decode_token `static void decode_token(int tid)`
- Defined: `progs/topogpt3/topogpt3.c:1613`
- Doc: ====================================================================== SECTION 21: GENERATION * ========================

### load_token_file `static int load_token_file(const char *path, int *out_ids, int max_ids)`
- Defined: `progs/topogpt3/topogpt3.c:1629`
- Doc: if (tid < 256) { /* Map GPT-2 byte-level encoding back to original byte int n = tid; if (n < 94) n += 33; else if (n < 1

### decode_token_tiktoken `static void decode_token_tiktoken(int tid)`
- Defined: `progs/topogpt3/topogpt3.c:1652`
- Doc: if (fread(&n, 4, 1, f) != 1) { fclose(f); return 0; } if (n > (unsigned)max_ids) n = max_ids; int count = (int)n; int i;

### generate_tokens `static void generate_tokens(int *prompt_tokens, int n_prompt, int max_new_tokens,
               ...`
- Defined: `progs/topogpt3/topogpt3.c:1660`

### generate `static void generate(const char *prompt, int max_new_tokens, float temperature,
                 ...`
- Defined: `progs/topogpt3/topogpt3.c:1724`

### interactive_mode `static void interactive_mode(void)`
- Defined: `progs/topogpt3/topogpt3.c:1735`
- Doc: ====================================================================== SECTION 22: INTERACTIVE MODE * ==================

### print_help `static void print_help(void)`
- Defined: `progs/topogpt3/topogpt3.c:1849`
- Doc: ====================================================================== SECTION 23: HELP AND MAIN * =====================

### main `int main(int argc, char **argv)`
- Defined: `progs/topogpt3/topogpt3.c:1884`

## qga.c

### qga_tx_ready `static int qga_tx_ready(void)`
- Defined: `qga.c:26`
- Doc: ================================================================ COM2 UART * ===========================================

### qga_rx_ready `static int qga_rx_ready(void)`
- Defined: `qga.c:28`

### qga_putc `static void qga_putc(char c)`
- Defined: `qga.c:29`

### qga_init `void qga_init(void)`
- Defined: `qga.c:34`

### qga_ws `static int qga_ws(char c)`
- Defined: `qga.c:55`

### qga_parse_object `static int qga_parse_object(const char **pp, struct qga_pair *out, int max,
                     ...`
- Defined: `qga.c:65`
- Doc: Parse a JSON object whose members are stored flat into out[*count..]: a nested object's members keep the parent key as a

### qga_parse_flat `static int qga_parse_flat(const char *s, struct qga_pair *out, int max)`
- Defined: `qga.c:147`
- Doc: Parse a request line into the flat pair table. Returns the number of pairs, * or -1 on malformed/overflowing input.

### qga_get_str `static const char *qga_get_str(const struct qga_pair *pairs, int n, const char *key)`
- Defined: `qga.c:157`

### qga_get_int `static int qga_get_int(const struct qga_pair *pairs, int n, const char *key, long *out)`
- Defined: `qga.c:165`

### qga_resp_reset `static void qga_resp_reset(void)`
- Defined: `qga.c:183`
- Doc: ================================================================ Response writer * =====================================

### qga_resp_puts `static void qga_resp_puts(const char *s)`
- Defined: `qga.c:185`

### qga_resp_putc_enc `static void qga_resp_putc_enc(char c)`
- Defined: `qga.c:193`

### qga_resp_put_long `static void qga_resp_put_long(long v)`
- Defined: `qga.c:201`
- Doc: Append the decimal form of v (a separate helper so no varargs forwarding is * needed; the kernel formatter is not re-ent

### qga_err `static void qga_err(const char *klass, const char *desc)`
- Defined: `qga.c:209`

### qga_puts_resp `static void qga_puts_resp(void)`
- Defined: `qga.c:217`

### qga_b64_encode `static void qga_b64_encode(const unsigned char *in, int n)`
- Defined: `qga.c:230`

### qga_cmd_get_time `static void qga_cmd_get_time(void)`
- Defined: `qga.c:280`

### qga_cmd_exec `static void qga_cmd_exec(const struct qga_pair *pairs, int n)`
- Defined: `qga.c:306`
- Doc: guest-exec runs a shell command line; output goes to the console (the `>` redirect still captures it). Queued so the she

### qga_cmd_shutdown `static void qga_cmd_shutdown(const struct qga_pair *pairs, int n)`
- Defined: `qga.c:315`

### qga_file_size `static int qga_file_size(const KFILE *f)`
- Defined: `qga.c:328`

### qga_cmd_file_open `static void qga_cmd_file_open(const struct qga_pair *pairs, int n)`
- Defined: `qga.c:333`

### qga_cmd_file_read `static void qga_cmd_file_read(const struct qga_pair *pairs, int n)`
- Defined: `qga.c:359`

### qga_cmd_file_close `static void qga_cmd_file_close(const struct qga_pair *pairs, int n)`
- Defined: `qga.c:383`

### qga_dispatch `static void qga_dispatch(struct qga_pair *pairs, int n)`
- Defined: `qga.c:400`
- Doc: ================================================================ Dispatch + poll * =====================================

### qga_poll `void qga_poll(void)`
- Defined: `qga.c:446`
- Doc: Accumulate bytes until a complete line, then parse and answer it. Callers * call it once per idle spin of the shell's ra

## sched.h

### __attribute__ `typedef struct __attribute__((packed))`
- Defined: `sched.h:130`
- Doc: GS base: set to &cpus[cpu_id] for kernel execution  Shared data (protected by sched_lock): - procs[]: the process table 

## smp.c

### lapic_read `static unsigned lapic_read(unsigned off)`
- Defined: `smp.c:67`

### lapic_write `static void lapic_write(unsigned off, unsigned val)`
- Defined: `smp.c:71`

### map_lapic `static int map_lapic(void)`
- Defined: `smp.c:78`
- Doc: Map the LAPIC so the BSP can program the ICR, and the APs can read their id registers.  Extends stage 2's tables: PDPT s

### ap_delay `static void ap_delay(void)`
- Defined: `smp.c:90`

### ap_lapic_timer_init `static void ap_lapic_timer_init(void)`
- Defined: `smp.c:98`
- Doc: Configure this AP's local LAPIC timer to fire at 100 Hz (matching the * BSP's PIT rate).  Uses divide-by-16 and periodic

### smp_ap_entry `void smp_ap_entry(void)`
- Defined: `smp.c:106`
- Doc: Entry point every AP reaches from ap_entry.S.  Initializes per-CPU state, * GS base, IDTR, LAPIC timer, and enters an id

### smp_init `void smp_init(void)`
- Defined: `smp.c:147`

## spinlock.h

### spin_init `static inline void spin_init(spinlock_t *lock)`
- Defined: `spinlock.h:44`
- Doc: define SPINLOCK_INIT { .locked = 0 }

### spin_save_irq `static inline irqflags_t spin_save_irq(void)`
- Defined: `spinlock.h:50`
- Doc: typedef struct { volatile unsigned int locked; } spinlock_t; typedef unsigned long irqflags_t; #define SPINLOCK_INIT { .

### spin_restore_irq `static inline void spin_restore_irq(irqflags_t flags)`
- Defined: `spinlock.h:57`
- Doc: #define SPINLOCK_INIT { .locked = 0 } static inline void spin_init(spinlock_t *lock) { lock->locked = 0; } /* Read RFLAG

### spin_lock `static inline void spin_lock(spinlock_t *lock)`
- Defined: `spinlock.h:65`
- Doc: Acquire the lock and disable interrupts. Interrupts are disabled before the CAS loop to prevent ISR re-entry. The memory

### spin_unlock `static inline void spin_unlock(spinlock_t *lock)`
- Defined: `spinlock.h:75`
- Doc: Release the lock and re-enable interrupts. The release uses __sync_lock_release which is a store-release with * the corr

### spin_unlock_irqrestore `static inline void spin_unlock_irqrestore(spinlock_t *lock, irqflags_t flags)`
- Defined: `spinlock.h:95`
- Doc: Release the lock and restore the saved interrupt state. If the caller's interrupts were enabled before spin_lock_irqsave

## test_bdd.sh

### cleanup_stale_qemu
- Defined: `test_bdd.sh:31`

### scenario
- Defined: `test_bdd.sh:42`
- Doc: scenario <name> <script of shell commands>

### scenario_smp
- Defined: `test_bdd.sh:60`
- Doc: scenario_smp <name> <script> -- same as scenario but with -smp 2

### expect
- Defined: `test_bdd.sh:79`
- Doc: expect <marker>

### expect_count
- Defined: `test_bdd.sh:100`
- Doc: expect_count <count> <marker>: the marker must appear exactly that many times in the log. Used where a single occurrence

### refute
- Defined: `test_bdd.sh:122`
- Doc: refute <marker>: the marker must NOT appear (suppressed hostile content).

### http_server_start
- Defined: `test_bdd.sh:626`

### http_server_stop
- Defined: `test_bdd.sh:633`

### http_fixture_start
- Defined: `test_bdd.sh:638`

### http_fixture_stop
- Defined: `test_bdd.sh:645`

## test_http_server.py

### do_GET `def do_GET(self)`
- Defined: `test_http_server.py:24`
- Depends on: `kernel/time.c`

### log_message `def log_message(self, fmt)`
- Defined: `test_http_server.py:114`
- Depends on: `kernel/time.c`

## tests/host_aes.sh

### ok
- Defined: `tests/host_aes.sh:23`

### bad
- Defined: `tests/host_aes.sh:24`

### rd
- Defined: `tests/host_aes.sh:25`

## tests/host_codecs.sh

### ok
- Defined: `tests/host_codecs.sh:22`

### bad
- Defined: `tests/host_codecs.sh:23`

### gen_input
- Defined: `tests/host_codecs.sh:27`

### roundtrip
- Defined: `tests/host_codecs.sh:31`

### reject
- Defined: `tests/host_codecs.sh:40`

## tests/test_vma.c

### black_height `static int black_height(const vma_node_t *n)`
- Defined: `tests/test_vma.c:26`

### tree_valid `static int tree_valid(const vma_node_t *root)`
- Defined: `tests/test_vma.c:37`

### count_nodes `static int count_nodes(const vma_node_t *root)`
- Defined: `tests/test_vma.c:74`

### test_insert_find_delete `static void test_insert_find_delete(void)`
- Defined: `tests/test_vma.c:88`

### test_pool_exhaustion `static void test_pool_exhaustion(void)`
- Defined: `tests/test_vma.c:135`

### test_full_drain `static void test_full_drain(void)`
- Defined: `tests/test_vma.c:152`

### main `int main(void)`
- Defined: `tests/test_vma.c:166`

## tls_port.h

### tls_now_days `static inline long tls_now_days(void)`
- Defined: `tls_port.h:39`
- Doc: define TLS_SEND           tls_test_send define TLS_RECV           tls_test_recv define TLS_RECV_TIMEOUT   tls_test_recv_

### tls_random `static inline void tls_random(unsigned char *out, unsigned len)`
- Defined: `tls_port.h:43`

## tls_test.c

### tls_test_send `int tls_test_send(int fd, const char *buf, int len)`
- Defined: `tls_test.c:25`
- Doc: #include <stdio.h> #include <stdlib.h> #include <string.h> #include <unistd.h> #include <sys/socket.h> #include <sys/sel

### tls_test_recv `int tls_test_recv(int fd, char *buf, int len)`
- Defined: `tls_test.c:35`

### tls_test_recv_timeout `int tls_test_recv_timeout(int fd, char *buf, int len, unsigned long ms)`
- Defined: `tls_test.c:40`

### tls_test_close `void tls_test_close(int fd)`
- Defined: `tls_test.c:53`

### hexdigit `static int hexdigit(int c)`
- Defined: `tls_test.c:66`

### unhex `static void unhex(const char *hex, unsigned char *out, int n)`
- Defined: `tls_test.c:73`

### bytes_eq `static int bytes_eq(const unsigned char *a, const unsigned char *b, int n)`
- Defined: `tls_test.c:79`

### test_sha256 `static void test_sha256(void)`
- Defined: `tls_test.c:87`
- Doc: static void unhex(const char *hex, unsigned char *out, int n) { int i; for (i = 0; i < n; i++) out[i] = (unsigned char)(

### test_sha384 `static void test_sha384(void)`
- Defined: `tls_test.c:102`

### test_gcm `static void test_gcm(void)`
- Defined: `tls_test.c:113`

### test_p256 `static void test_p256(void)`
- Defined: `tls_test.c:153`

### test_rsa_ecdsa_vectors `static void test_rsa_ecdsa_vectors(void)`
- Defined: `tls_test.c:199`

### tcp_connect `static int tcp_connect(int port)`
- Defined: `tls_test.c:248`
- Doc: ok = ecdsa_verify(0, test_ec_x, test_ec_y, digest, 32, test_ec_sig, sizeof(test_ec_sig)) == 0; CHECK("ecdsa p256 sha256 

### http_over_tls `static int http_over_tls(int port, const char *host)`
- Defined: `tls_test.c:265`
- Doc: int fd = socket(AF_INET, SOCK_STREAM, 0); if (fd < 0) return -1; memset(&sa, 0, sizeof(sa)); sa.sin_family = AF_INET; sa

### scenario_good `static int scenario_good(int port)`
- Defined: `tls_test.c:289`

### scenario_wild_good `static int scenario_wild_good(int port)`
- Defined: `tls_test.c:295`
- Doc: total += n; printed = 1; } tls_free_fd(fd); close(fd); if (!printed) return -1; return 0; } static int scenario_good(int

### scenario_wild_root `static int scenario_wild_root(int port)`
- Defined: `tls_test.c:298`

### scenario_wild_deep `static int scenario_wild_deep(int port)`
- Defined: `tls_test.c:308`

### scenario_bad_host `static int scenario_bad_host(int port)`
- Defined: `tls_test.c:318`

### scenario_bad_ca `static int scenario_bad_ca(int port)`
- Defined: `tls_test.c:328`

### scenario_expired `static int scenario_expired(int port)`
- Defined: `tls_test.c:338`

### main `int main(int argc, char **argv)`
- Defined: `tls_test.c:348`

## tls_test.py

### run `def run(cmd)`
- Defined: `tls_test.py:26`
- Depends on: `kernel/time.c`

### check `def check(cmd)`
- Defined: `tls_test.py:30`
- Depends on: `kernel/time.c`

### gen_certs `def gen_certs()`
- Defined: `tls_test.py:37`
- Depends on: `kernel/time.c`

### der_bytes `def der_bytes(pem_path)`
- Defined: `tls_test.py:154`
- Depends on: `kernel/time.c`

### rsa_params `def rsa_params(key_path)`
- Defined: `tls_test.py:162`
- Depends on: `kernel/time.c`

### ec_pub `def ec_pub(key_path)`
- Defined: `tls_test.py:172`
- Depends on: `kernel/time.c`

### c_bytes `def c_bytes(data, name)`
- Defined: `tls_test.py:183`
- Depends on: `kernel/time.c`

### gen_header `def gen_header(p)`
- Defined: `tls_test.py:191`
- Depends on: `kernel/time.c`

### serve `def serve(cert, key)`
- Defined: `tls_test.py:280`
- Depends on: `kernel/time.c`

### serve_openssl `def serve_openssl(cert, key, chain)`
- Defined: `tls_test.py:288`
- Depends on: `kernel/time.c`

### expect `def expect(bin_path, args, want_zero, marker)`
- Defined: `tls_test.py:306`
- Depends on: `kernel/time.c`

### main `def main()`
- Defined: `tls_test.py:319`
- Depends on: `kernel/time.c`

### server_cert `def server_cert(name, algo, curve, ca_name, ca_algo, curve_ca, extra, subj)`
- Defined: `tls_test.py:61`
- Depends on: `kernel/time.c`

### __init__ `def __init__(self, cert, key, tls13_ok)`
- Defined: `tls_test.py:242`
- Depends on: `kernel/time.c`

### run `def run(self)`
- Defined: `tls_test.py:248`
- Depends on: `kernel/time.c`

## tools/check_cohesion.py

### load_cpg `def load_cpg(path)`
- Defined: `tools/check_cohesion.py:23`
- Doc: Load and parse the CPG JSON-LD file.

### compute_cohesion `def compute_cohesion(community_nodes, community_edges)`
- Defined: `tools/check_cohesion.py:31`
- Doc: Compute cohesion as internal_edges / max_possible_edges.

### extract_communities `def extract_communities(cpg)`
- Defined: `tools/check_cohesion.py:42`
- Doc: Extract communities and their internal edges from CPG.

### main `def main()`
- Defined: `tools/check_cohesion.py:58`

## tools/check_complexity.py

### count_symbols `def count_symbols(filepath)`
- Defined: `tools/check_complexity.py:24`
- Doc: Count top-level function and global variable definitions.

### load_approval `def load_approval(policy_path)`
- Defined: `tools/check_complexity.py:46`
- Doc: Load explicit complexity approval from ARCH_POLICY.yaml.

### main `def main()`
- Defined: `tools/check_complexity.py:61`

## tools/check_kb_sync.py

### regenerate_kb `def regenerate_kb()`
- Defined: `tools/check_kb_sync.py:24`
- Doc: Attempt to regenerate KNOWLEDGE_BASE.md using readmenator.

### main `def main()`
- Defined: `tools/check_kb_sync.py:43`

## tools/check_surprising.py

### load_cpg `def load_cpg(path)`
- Defined: `tools/check_surprising.py:25`
- Doc: Load and parse the CPG JSON-LD file.

### build_graph `def build_graph(cpg)`
- Defined: `tools/check_surprising.py:33`
- Doc: Build adjacency list from CPG nodes and edges.

### bfs_min_hops `def bfs_min_hops(nodes, edges, source, target_community, max_hops)`
- Defined: `tools/check_surprising.py:56`
- Doc: BFS from source to any node in target_community, returning hop count.

### find_surprising_connections `def find_surprising_connections(nodes, edges, min_hops)`
- Defined: `tools/check_surprising.py:87`
- Doc: Find connections of min_hops or more between distinct communities.

### main `def main()`
- Defined: `tools/check_surprising.py:118`

## tools/gdb_repro.py

### rs `def rs(m, t)`
- Defined: `tools/gdb_repro.py:23`
- Depends on: `kernel/time.c`

### main `def main()`
- Defined: `tools/gdb_repro.py:27`
- Depends on: `kernel/time.c`

### send `def send(line)`
- Defined: `tools/gdb_repro.py:65`
- Depends on: `kernel/time.c`

### quit_doom `def quit_doom()`
- Defined: `tools/gdb_repro.py:70`
- Depends on: `kernel/time.c`

## tools/gen_icons.py

### make_png `def make_png(pixels, palette, width, height)`
- Defined: `tools/gen_icons.py:179`
- Doc: Create a minimal indexed-colour PNG from pixel indices and a palette.

### make_chunk `def make_chunk(chunk_type, data)`
- Defined: `tools/gen_icons.py:209`

### main `def main()`
- Defined: `tools/gen_icons.py:214`

## tools/gen_zip_fixtures.py

### write_zip `def write_zip(path, entries)`
- Defined: `tools/gen_zip_fixtures.py:28`
- Doc: entries: list of (name, data_or_None).  data None marks a directory.

### main `def main()`
- Defined: `tools/gen_zip_fixtures.py:42`

## tools/minios_cli.py

### main `def main()`
- Defined: `tools/minios_cli.py:99`
- Depends on: `kernel/time.c`

### __init__ `def __init__(self)`
- Defined: `tools/minios_cli.py:38`
- Depends on: `kernel/time.c`

### request `def request(self, method, params)`
- Defined: `tools/minios_cli.py:55`
- Depends on: `kernel/time.c`

### tool `def tool(self, name, params)`
- Defined: `tools/minios_cli.py:76`
- Depends on: `kernel/time.c`

### close `def close(self)`
- Defined: `tools/minios_cli.py:86`
- Depends on: `kernel/time.c`

## tools/minios_gui.py

### read_serial `def read_serial(master, timeout)`
- Defined: `tools/minios_gui.py:42`
- Depends on: `kernel/time.c`

### main `def main()`
- Defined: `tools/minios_gui.py:110`
- Depends on: `kernel/time.c`

### __init__ `def __init__(self, path)`
- Defined: `tools/minios_gui.py:59`
- Depends on: `kernel/time.c`

### cmd `def cmd(self, obj)`
- Defined: `tools/minios_gui.py:71`
- Depends on: `kernel/time.c`

### _recv `def _recv(self)`
- Defined: `tools/minios_gui.py:75`
- Depends on: `kernel/time.c`

### mouse `def mouse(self, dx, dy, click)`
- Defined: `tools/minios_gui.py:90`
- Depends on: `kernel/time.c`

### key `def key(self, qcode, up)`
- Defined: `tools/minios_gui.py:100`
- Depends on: `kernel/time.c`

### screendump `def screendump(self, path)`
- Defined: `tools/minios_gui.py:106`
- Depends on: `kernel/time.c`

## tools/mkpak1.py

### main `def main()`
- Defined: `tools/mkpak1.py:29`

## tools/qga_client.py

### send_command `def send_command(sock, cmd, args)`
- Defined: `tools/qga_client.py:33`
- Depends on: `kernel/time.c`

### read_reply `def read_reply(sock, timeout)`
- Defined: `tools/qga_client.py:41`
- Doc: Read one newline-terminated JSON object from the agent.
- Depends on: `kernel/time.c`

### connect `def connect(path)`
- Defined: `tools/qga_client.py:57`
- Depends on: `kernel/time.c`

### main `def main(argv)`
- Defined: `tools/qga_client.py:74`
- Depends on: `kernel/time.c`

## tools/qga_test.sh

### cleanup
- Defined: `tools/qga_test.sh:25`

### check
- Defined: `tools/qga_test.sh:31`

### expect_in
- Defined: `tools/qga_test.sh:43`

## tools/repro_gui.py

### read_serial `def read_serial(master, timeout)`
- Defined: `tools/repro_gui.py:28`
- Depends on: `kernel/time.c`

### main `def main()`
- Defined: `tools/repro_gui.py:90`
- Depends on: `kernel/time.c`

### __init__ `def __init__(self, path)`
- Defined: `tools/repro_gui.py:45`
- Depends on: `kernel/time.c`

### cmd `def cmd(self, obj)`
- Defined: `tools/repro_gui.py:57`
- Depends on: `kernel/time.c`

### _recv `def _recv(self)`
- Defined: `tools/repro_gui.py:61`
- Depends on: `kernel/time.c`

### mouse `def mouse(self, dx, dy, left)`
- Defined: `tools/repro_gui.py:76`
- Depends on: `kernel/time.c`

### key `def key(self, qcode, down)`
- Defined: `tools/repro_gui.py:85`
- Depends on: `kernel/time.c`

### send `def send(line)`
- Defined: `tools/repro_gui.py:111`
- Depends on: `kernel/time.c`

### mouse_state `def mouse_state()`
- Defined: `tools/repro_gui.py:116`
- Depends on: `kernel/time.c`

## tools/test_sb16.sh

### fail_msg
- Defined: `tools/test_sb16.sh:45`

## vma.c

### vma_tree_init `void vma_tree_init(void)`
- Defined: `vma.c:21`

### vma_alloc_node `static vma_node_t *vma_alloc_node(void)`
- Defined: `vma.c:32`

### vma_rotate_left `static void vma_rotate_left(vma_node_t **root, vma_node_t *x)`
- Defined: `vma.c:37`

### vma_rotate_right `static void vma_rotate_right(vma_node_t **root, vma_node_t *x)`
- Defined: `vma.c:49`

### vma_insert_fixup `static void vma_insert_fixup(vma_node_t **root, vma_node_t *z)`
- Defined: `vma.c:61`

### vma_tree_insert `vma_node_t *vma_tree_insert(vma_node_t **root, unsigned long base, unsigned long len)`
- Defined: `vma.c:100`

### vma_tree_find `vma_node_t *vma_tree_find(vma_node_t *root, unsigned long base)`
- Defined: `vma.c:123`

### vma_transplant `static void vma_transplant(vma_node_t **root, vma_node_t *u, vma_node_t *v)`
- Defined: `vma.c:133`

### vma_tree_minimum `static vma_node_t *vma_tree_minimum(vma_node_t *x)`
- Defined: `vma.c:140`

### vma_delete_fixup `static void vma_delete_fixup(vma_node_t **root, vma_node_t *x)`
- Defined: `vma.c:145`

### vma_tree_delete `int vma_tree_delete(vma_node_t **root, unsigned long base)`
- Defined: `vma.c:200`
