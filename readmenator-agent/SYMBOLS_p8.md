# Symbols (page 8 of 26)
Previous: [SYMBOLS_p7.md](SYMBOLS_p7.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `n_ftell` | function | `kernel/cvm_host.c:154` | `static int64_t n_ftell(void *vm, int ac, uint64_t *av)` |
| `n_fwrite` | function | `kernel/cvm_host.c:141` | `static int64_t n_fwrite(void *vm, int ac, uint64_t *av)` |
| `n_malloc` | function | `kernel/cvm_host.c:88` | `static int64_t n_malloc(void *vm, int ac, uint64_t *av)` |
| `n_memcmp` | function | `kernel/cvm_host.c:68` | `static int64_t n_memcmp(void *vm, int ac, uint64_t *av)` |
| `n_memcpy` | function | `kernel/cvm_host.c:48` | `static int64_t n_memcpy(void *vm, int ac, uint64_t *av)` |
| `n_memmove` | function | `kernel/cvm_host.c:61` | `static int64_t n_memmove(void *vm, int ac, uint64_t *av)` |
| `n_memset` | function | `kernel/cvm_host.c:55` | `static int64_t n_memset(void *vm, int ac, uint64_t *av)` |
| `n_printf` | function | `kernel/cvm_host.c:369` | `static int64_t n_printf(void *vm, int ac, uint64_t *av)` |
| `n_putchar` | function | `kernel/cvm_host.c:197` | `static int64_t n_putchar(void *vm, int ac, uint64_t *av)` |
| `n_puts` | function | `kernel/cvm_host.c:228` | `static int64_t n_puts(void *vm, int ac, uint64_t *av)` |
| `n_read` | function | `kernel/cvm_host.c:213` | `static int64_t n_read(void *vm, int ac, uint64_t *av)` |
| `n_realloc` | function | `kernel/cvm_host.c:106` | `static int64_t n_realloc(void *vm, int ac, uint64_t *av)` |
| `n_rewind` | function | `kernel/cvm_host.c:160` | `static int64_t n_rewind(void *vm, int ac, uint64_t *av)` |
| `n_snprintf` | function | `kernel/cvm_host.c:384` | `static int64_t n_snprintf(void *vm, int ac, uint64_t *av)` |
| `n_sprintf` | function | `kernel/cvm_host.c:376` | `static int64_t n_sprintf(void *vm, int ac, uint64_t *av)` |
| `n_stderr_addr` | function | `kernel/cvm_host.c:262` | `static int64_t n_stderr_addr(void *vm, int ac, uint64_t *av)` |
| `n_stdin_addr` | function | `kernel/cvm_host.c:272` | `static int64_t n_stdin_addr(void *vm, int ac, uint64_t *av)` |
| `n_stdout_addr` | function | `kernel/cvm_host.c:267` | `static int64_t n_stdout_addr(void *vm, int ac, uint64_t *av)` |
| `n_strchr` | function | `kernel/cvm_host.c:75` | `static int64_t n_strchr(void *vm, int ac, uint64_t *av)` |
| `n_strcmp` | function | `kernel/cvm_host.c:22` | `static int64_t n_strcmp(void *vm, int ac, uint64_t *av)` |
| `n_strcpy` | function | `kernel/cvm_host.c:35` | `static int64_t n_strcpy(void *vm, int ac, uint64_t *av)` |
| `n_strncmp` | function | `kernel/cvm_host.c:28` | `static int64_t n_strncmp(void *vm, int ac, uint64_t *av)` |
| `n_strncpy` | function | `kernel/cvm_host.c:41` | `static int64_t n_strncpy(void *vm, int ac, uint64_t *av)` |
| `n_strstr` | function | `kernel/cvm_host.c:81` | `static int64_t n_strstr(void *vm, int ac, uint64_t *av)` |
| `n_strtol` | function | `kernel/cvm_host.c:249` | `static int64_t n_strtol(void *vm, int ac, uint64_t *av)` |
| `n_ungetc` | function | `kernel/cvm_host.c:185` | `static int64_t n_ungetc(void *vm, int ac, uint64_t *av)` |
| `n_write` | function | `kernel/cvm_host.c:204` | `static int64_t n_write(void *vm, int ac, uint64_t *av)` |
| `register_host_natives` | function | `kernel/cvm_host.c:392` | `static void register_host_natives(CvmState *vm)` |
| `EDIT_FILE_MAX` | macro | `kernel/editor.c:22` | `#define EDIT_FILE_MAX` |
| `EDIT_LINE_MAX` | macro | `kernel/editor.c:21` | `#define EDIT_LINE_MAX` |
| `EDIT_MAX_LINES` | macro | `kernel/editor.c:20` | `#define EDIT_MAX_LINES` |
| `EditBuf` | struct | `kernel/editor.c:29` | `` |
| `EditLine` | struct | `kernel/editor.c:24` | `` |
| `edit_alloc` | function | `kernel/editor.c:38` | `static EditBuf *edit_alloc(const char *fname)` |
| `edit_arg_line` | function | `kernel/editor.c:213` | `static int edit_arg_line(int argc, char **argv, EditBuf *e, int *out)` |
| `edit_delete` | function | `kernel/editor.c:154` | `static int edit_delete(EditBuf *e, int idx)` |
| `edit_free` | function | `kernel/editor.c:55` | `static void edit_free(EditBuf *e)` |
| `edit_insert` | function | `kernel/editor.c:144` | `static int edit_insert(EditBuf *e, int idx, const char *text)` |
| `edit_line_cstr` | function | `kernel/editor.c:166` | `static void edit_line_cstr(EditLine *l, char *out)` |
| `edit_list` | function | `kernel/editor.c:123` | `static void edit_list(EditBuf *e, int start, int end)` |
| `edit_load` | function | `kernel/editor.c:61` | `static int edit_load(EditBuf *e)` |
| `edit_loop` | function | `kernel/editor.c:224` | `static void edit_loop(EditBuf *e)` |
| `edit_print` | function | `kernel/editor.c:113` | `static void edit_print(EditBuf *e, int idx)` |
| `edit_refuse_save` | function | `kernel/editor.c:207` | `static int edit_refuse_save(EditBuf *e)` |
| `edit_save` | function | `kernel/editor.c:99` | `static int edit_save(EditBuf *e)` |
| `edit_search` | function | `kernel/editor.c:171` | `static void edit_search(EditBuf *e, const char *needle)` |
| `edit_set_line` | function | `kernel/editor.c:135` | `static int edit_set_line(EditBuf *e, int idx, const char *text)` |
| `edit_status` | function | `kernel/editor.c:188` | `static void edit_status(EditBuf *e)` |
| `edit_usage` | function | `kernel/editor.c:196` | `static void edit_usage(void)` |
| `shell_cmd_edit` | function | `kernel/editor.c:329` | `void shell_cmd_edit(int argc, char **argv)` |
| `ETREL_CHILD_STACK_SZ` | macro | `kernel/exec.c:133` | `#define ETREL_CHILD_STACK_SZ` |
| `EXEC_KSTACK_SZ` | macro | `kernel/exec.c:124` | `#define EXEC_KSTACK_SZ` |
| `k_run_rel` | function | `kernel/exec.c:233` | `int k_run_rel(prog_entry_t entry, int argc, char **argv)` |
| `k_user_fault_return` | function | `kernel/exec.c:66` | `void k_user_fault_return(void)` |
| `kexit` | function | `kernel/exec.c:284` | `void kexit(int code)` |
| `setup_user_stack` | function | `kernel/exec.c:83` | `unsigned long *setup_user_stack(char *sbase, unsigned long ssize,                                ...` |
| `syscall_kstack` | variable | `kernel/exec.c:116` | `extern unsigned long syscall_kstack;` |
| `vga_gfx_ran_set` | function | `kernel/exec.c:63` | `void vga_gfx_ran_set(int on)` |
| `vga_mode_is_active` | function | `kernel/exec.c:62` | `int  vga_mode_is_active(void)` |
| `vga_mode_set` | function | `kernel/exec.c:61` | `void vga_mode_set(int on)` |
| `futex_bucket` | function | `kernel/futex.c:31` | `static futex_bucket_t *futex_bucket(unsigned long uaddr)` |
| `futex_hash` | function | `kernel/futex.c:23` | `static unsigned long futex_hash(unsigned long uaddr)` |
| `futex_init` | function | `kernel/futex.c:36` | `void futex_init(void)` |
| `futex_linux_cmd` | function | `kernel/futex.c:84` | `int futex_linux_cmd(long op)` |
| `futex_table_t` | struct | `kernel/futex.c:16` | `` |
| `futex_timeout_remaining_us` | function | `kernel/futex.c:95` | `long futex_timeout_remaining_us(int cmd, long sec, long nsec, unsigned long now_us)` |
| `futex_wake` | function | `kernel/futex.c:112` | `long futex_wake(unsigned long uaddr, int n)` |
| `t_cur_pid` | variable | `kernel/futex.c:13` | `extern int t_cur_pid;` |
| `klog` | function | `kernel/klog.c:41` | `void klog(log_level_t level, log_subsystem_t subsys,           const char *fmt, ...)` |
| `klog_disable` | function | `kernel/klog.c:38` | `void klog_disable(void)` |
| `klog_enable` | function | `kernel/klog.c:39` | `void klog_enable(void)` |
| `klog_hexdump` | function | `kernel/klog.c:119` | `void klog_hexdump(log_level_t level, log_subsystem_t subsys,                   const void *data, ...` |
| `klog_set_level` | function | `kernel/klog.c:29` | `void klog_set_level(log_level_t level)` |
| `klog_set_subsys_level` | function | `kernel/klog.c:33` | `void klog_set_subsys_level(log_subsystem_t subsys, log_level_t level)` |
| `LDSO_DYN_ENT` | macro | `kernel/ldso_parse.c:15` | `#define LDSO_DYN_ENT` |
| `LDSO_EHSIZE` | macro | `kernel/ldso_parse.c:13` | `#define LDSO_EHSIZE` |
| `LDSO_HASH_HDR` | macro | `kernel/ldso_parse.c:16` | `#define LDSO_HASH_HDR` |
| `LDSO_PHENTSZ` | macro | `kernel/ldso_parse.c:14` | `#define LDSO_PHENTSZ` |
| `ldso_basename` | function | `kernel/ldso_parse.c:331` | `void ldso_basename(char *out, const char *src)` |
| `ldso_copy_str` | function | `kernel/ldso_parse.c:227` | `int ldso_copy_str(const unsigned char *file, unsigned long long fsize,         unsigned long long...` |
| `ldso_find_dynamic` | function | `kernel/ldso_parse.c:120` | `int ldso_find_dynamic(const unsigned char *file, unsigned long long fsize,         unsigned long ...` |
| `ldso_name_eq` | function | `kernel/ldso_parse.c:250` | `static int ldso_name_eq(const unsigned char *tab, unsigned long long strsz,         unsigned long...` |
| `ldso_rd16` | function | `kernel/ldso_parse.c:18` | `static unsigned ldso_rd16(const unsigned char *p)` |
| `ldso_rd32` | function | `kernel/ldso_parse.c:22` | `static unsigned long ldso_rd32(const unsigned char *p)` |
| `ldso_rd64` | function | `kernel/ldso_parse.c:27` | `static unsigned long long ldso_rd64(const unsigned char *p)` |
| `ldso_read_rela` | function | `kernel/ldso_parse.c:309` | `int ldso_read_rela(const unsigned char *file, unsigned long long fsize,         unsigned long lon...` |
| `ldso_rela_count` | function | `kernel/ldso_parse.c:296` | `int ldso_rela_count(const LdsoDynInfo *info, unsigned *nrela)` |
| `ldso_scan_dynamic` | function | `kernel/ldso_parse.c:150` | `int ldso_scan_dynamic(const unsigned char *file, unsigned long long fsize,         unsigned long ...` |
| `ldso_segments` | function | `kernel/ldso_parse.c:86` | `int ldso_segments(const unsigned char *file, unsigned long long fsize,         LdsoSeg *segs, uns...` |
| `ldso_slice` | function | `kernel/ldso_parse.c:32` | `static int ldso_slice(const unsigned char *file, unsigned long long fsize,         unsigned long ...` |
| `ldso_sym_count` | function | `kernel/ldso_parse.c:213` | `int ldso_sym_count(const unsigned char *file, unsigned long long fsize,         unsigned long lon...` |
| `ldso_sym_lookup` | function | `kernel/ldso_parse.c:263` | `int ldso_sym_lookup(const unsigned char *file, unsigned long long fsize,         unsigned long lo...` |
| `ldso_vaddr_to_offset` | function | `kernel/ldso_parse.c:54` | `int ldso_vaddr_to_offset(const unsigned char *file,         unsigned long long fsize, unsigned lo...` |
| `ldso_valid_ehdr` | function | `kernel/ldso_parse.c:40` | `static int ldso_valid_ehdr(const unsigned char *file,         unsigned long long fsize)` |
| `ELF64_R_SYM` | macro | `kernel/loader.c:61` | `#define ELF64_R_SYM(i)` |
| `ELF64_R_TYPE` | macro | `kernel/loader.c:62` | `#define ELF64_R_TYPE(i)` |
| `ELF_MAX_SEGMENTS` | macro | `kernel/loader.c:94` | `#define ELF_MAX_SEGMENTS` |
| `ELF_NAME_MAX` | macro | `kernel/loader.c:95` | `#define ELF_NAME_MAX` |
| `EM_X86_64` | macro | `kernel/loader.c:80` | `#define EM_X86_64` |
| `ETREL_IMAGE_MAX` | macro | `kernel/loader.c:70` | `#define ETREL_IMAGE_MAX` |
| `Elf64_Phdr` | struct | `kernel/loader.c:50` | `` |
| `Elf64_Rela` | struct | `kernel/loader.c:44` | `` |
| `Elf64_Shdr` | struct | `kernel/loader.c:22` | `` |
| `Elf64_Sym` | struct | `kernel/loader.c:35` | `` |
| `LdsoLibEnt` | struct | `kernel/loader.c:381` | `` |
| `PF_X` | macro | `kernel/loader.c:93` | `#define PF_X` |
| `PT_LOAD` | macro | `kernel/loader.c:81` | `#define PT_LOAD` |
| `R_X86_64_32` | macro | `kernel/loader.c:89` | `#define R_X86_64_32` |
| `R_X86_64_32S` | macro | `kernel/loader.c:90` | `#define R_X86_64_32S` |
| `R_X86_64_64` | macro | `kernel/loader.c:83` | `#define R_X86_64_64` |
| `R_X86_64_GLOB_DAT` | macro | `kernel/loader.c:86` | `#define R_X86_64_GLOB_DAT` |
| `R_X86_64_IRELATIVE` | macro | `kernel/loader.c:91` | `#define R_X86_64_IRELATIVE` |
| `R_X86_64_JUMP_SLOT` | macro | `kernel/loader.c:87` | `#define R_X86_64_JUMP_SLOT` |
| `R_X86_64_PC32` | macro | `kernel/loader.c:84` | `#define R_X86_64_PC32` |
| `R_X86_64_PLT32` | macro | `kernel/loader.c:85` | `#define R_X86_64_PLT32` |
| `R_X86_64_RELATIVE` | macro | `kernel/loader.c:88` | `#define R_X86_64_RELATIVE` |
| `SHF_ALLOC` | macro | `kernel/loader.c:77` | `#define SHF_ALLOC` |
| `SHF_EXECINSTR` | macro | `kernel/loader.c:78` | `#define SHF_EXECINSTR` |
| `SHN_UNDEF` | macro | `kernel/loader.c:63` | `#define SHN_UNDEF` |
| `SHT_NOBITS` | macro | `kernel/loader.c:76` | `#define SHT_NOBITS` |
| `SHT_PROGBITS` | macro | `kernel/loader.c:75` | `#define SHT_PROGBITS` |
| `SHT_RELA` | macro | `kernel/loader.c:74` | `#define SHT_RELA` |
| `SHT_STRTAB` | macro | `kernel/loader.c:73` | `#define SHT_STRTAB` |
| `SHT_SYMTAB` | macro | `kernel/loader.c:72` | `#define SHT_SYMTAB` |
| `apply_exec_relocs` | function | `kernel/loader.c:977` | `static void apply_exec_relocs(void *data, unsigned size, unsigned long base,                     ...` |
| `base_out` | function | `kernel/loader.c:1191` | `* the link base via base_out (0 when the caller runs static images  * only: the dynamic binder ne...` |
| `consistent` | function | `kernel/loader.c:572` | `* consistent (the next exec forgets them, a dying window frees them),  * and only reports. */ sta...` |
| `elf_load` | function | `kernel/loader.c:129` | `void *elf_load(void *data, unsigned size, void **base_out)` |
| `elf_load_fail` | function | `kernel/loader.c:121` | `static void elf_load_fail(void *base, void **sec_addrs, const char *why)` |
| `elf_name_copy` | function | `kernel/loader.c:107` | `static void elf_name_copy(char *out, unsigned out_cap, const char *tab,                          ...` |
| `exec_range` | struct | `kernel/loader.c:97` | `` |
| `images` | function | `kernel/loader.c:783` | `* Static images (no dynamic section, or none needed) return 0 at * once, so the legacy paths never observe a...` |
| `inodes` | function | `kernel/loader.c:374` | `* Pseudo inodes (LDSO_INO_BASE + slot) keep registry pages apart from * MiniFS inodes in the shared cache. No unload...` |
| `ldso_bind_into` | function | `kernel/loader.c:787` | `int ldso_bind_into(void *data, unsigned size, unsigned long base,         unsigned long cr3, vma_...` |
| `ldso_ensure_slot` | function | `kernel/loader.c:476` | `static int ldso_ensure_slot(const char *needed, int *slot_out)` |
| `ldso_pseudo_read` | function | `kernel/loader.c:409` | `int ldso_pseudo_read(int ino, void *dst, unsigned long off, unsigned len)` |
| `ldso_pseudo_stat` | function | `kernel/loader.c:395` | `int ldso_pseudo_stat(int ino, unsigned long *size_out)` |
| `ldso_read_file` | function | `kernel/loader.c:434` | `static int ldso_read_file(const char *name, unsigned char **out,         unsigned *size_out)` |
| `load_exec_elf` | function | `kernel/loader.c:1060` | `void *load_exec_elf(void *data, unsigned size)` |
| `process` | function | `kernel/loader.c:1084` | `* atomic section: a 100 Hz tick between two segments would switch * CR3 into another process (copies landing in its...` |
| `time` | function | `kernel/loader.c:1262` | `* time (with the failing offset);` |
| `HASH_BITS` | macro | `kernel/lz4_kernel.c:4` | `#define HASH_BITS` |
| `HASH_SIZE` | macro | `kernel/lz4_kernel.c:5` | `#define HASH_SIZE` |
| `LZ4_compressBound` | function | `kernel/lz4_kernel.c:33` | `int LZ4_compressBound(int inputSize)` |
| `LZ4_compress_default` | function | `kernel/lz4_kernel.c:40` | `int LZ4_compress_default(const char *src, char *dst, int srcSize, int dstCapacity)` |
| `LZ4_decompress_safe` | function | `kernel/lz4_kernel.c:176` | `int LZ4_decompress_safe(const char *src, char *dst, int compressedSize, int dstCapacity)` |
| `LZ4_hash` | function | `kernel/lz4_kernel.c:26` | `static unsigned int LZ4_hash(const unsigned char *p)` |
| `LZ4_read16` | function | `kernel/lz4_kernel.c:14` | `static inline unsigned int LZ4_read16(const unsigned char *p)` |
| `LZ4_read32` | function | `kernel/lz4_kernel.c:7` | `static inline unsigned int LZ4_read32(const unsigned char *p)` |
| `LZ4_write16` | function | `kernel/lz4_kernel.c:21` | `static inline void LZ4_write16(unsigned char *dst, unsigned short v)` |
| `slots` | function | `kernel/lz4_kernel.c:43` | `* runs from file writes on 16 KB proc slots (stack discipline, * CLAUDE.md). OOM returns 0 and the caller stores...` |
| `frame` | function | `kernel/minifetch.c:159` | `* frame (stack discipline, CLAUDE.md). Fail-closed on OOM. */ char (*specs)[96] = (char (*)[96])kmalloc(20 * 96);` |
| `minifetch_cfg` | struct | `kernel/minifetch.c:21` | `` |
| `minifetch_logo` | function | `kernel/minifetch.c:81` | `static void minifetch_logo(char rows[16][33])` |
| `minifetch_row` | function | `kernel/minifetch.c:57` | `static void minifetch_row(const unsigned char *img, int w, int h, int row,                       ...` |
| `minifetch_specs` | function | `kernel/minifetch.c:101` | `static int minifetch_specs(char lines[20][96])` |
| `shell_cmd_minifetch` | function | `kernel/minifetch.c:156` | `void shell_cmd_minifetch(void)` |
| `kallocator_init` | function | `kernel/mm.c:13` | `void kallocator_init(void)` |
| `kcalloc` | function | `kernel/mm.c:49` | `void *kcalloc(unsigned long nmemb, unsigned long size)` |
| `kfree` | function | `kernel/mm.c:28` | `void kfree(void *ptr)` |
| `kfree_aligned` | function | `kernel/mm.c:81` | `void kfree_aligned(void *ptr)` |
| `kmalloc` | function | `kernel/mm.c:21` | `void *kmalloc(unsigned long size)` |
| `kmalloc_aligned` | function | `kernel/mm.c:65` | `void *kmalloc_aligned(unsigned long size, unsigned long align)` |
| `krealloc` | function | `kernel/mm.c:53` | `void *krealloc(void *ptr, unsigned long size)` |
| `COW_MAX` | macro | `kernel/mm/cow.c:28` | `#define COW_MAX` |
| `PT_PTE_RW` | macro | `kernel/mm/cow.c:35` | `#define PT_PTE_RW` |
| `PT_USER_RO` | macro | `kernel/mm/cow.c:33` | `#define PT_USER_RO` |
| `PT_USER_RW_ENTRY` | macro | `kernel/mm/cow.c:34` | `#define PT_USER_RW_ENTRY` |
| `alternative` | function | `kernel/mm/cow.c:20` | `* window is one instruction wide and the alternative (no CoW) is * documented, so the trade stands. */ #include...` |
| `cow_entry_t` | struct | `kernel/mm/cow.c:45` | `` |
| `cow_find` | function | `kernel/mm/cow.c:53` | `static int cow_find(unsigned long phys)` |
| `cow_fork_one` | function | `kernel/mm/cow.c:132` | `static void cow_fork_one(unsigned long pcr3, unsigned long va,         volatile unsigned long *ppte)` |
| `cow_page_shared` | function | `kernel/mm/cow.c:65` | `int cow_page_shared(unsigned long phys)` |
| `cow_release_window` | function | `kernel/mm/cow.c:292` | `void cow_release_window(unsigned long cr3)` |
| `cow_resolve` | function | `kernel/mm/cow.c:228` | `int cow_resolve(unsigned long cr3, unsigned long va)` |
| `cow_shared` | function | `kernel/mm/cow.c:336` | `int cow_shared(void)` |
| `cow_track` | function | `kernel/mm/cow.c:76` | `static int cow_track(unsigned long phys)` |
| `cow_walk` | function | `kernel/mm/cow.c:98` | `static void cow_walk(unsigned long cr3, cow_walk_fn fn)` |
| `private` | function | `kernel/mm/cow.c:94` | `* for every present page in a private (non-graphics) slot. Shared * graphics slots are never CoW: the compositor...` |
| `published` | function | `kernel/mm/cow.c:162` | `* with nothing published (the half-built window is freed). The caller  * flushes the parent TLB a...` |
| `KMM_DEVICE_FLAGS` | macro | `kernel/mm/paging.c:210` | `#define KMM_DEVICE_FLAGS` |
| `KMM_DEVICE_MAX` | macro | `kernel/mm/paging.c:199` | `#define KMM_DEVICE_MAX` |
| `KMM_MAX_IDENTITY` | macro | `kernel/mm/paging.c:203` | `#define KMM_MAX_IDENTITY` |
| `PT_ALLOC_HDR` | macro | `kernel/mm/paging.c:365` | `#define PT_ALLOC_HDR` |
| `_kernel_end` | variable | `kernel/mm/paging.c:48` | `extern char _kernel_end[];` |
| `coherent` | function | `kernel/mm/paging.c:258` | `* for memory a device reads and writes by DMA: a controller that is not cache  * coherent (and an...` |
| `explicitly` | function | `kernel/mm/paging.c:819` | `* teardown passes the dying window explicitly (zombie-exclusive, no * lock needed). unmap == 0 drops refs only...` |
| `honest` | function | `kernel/mm/paging.c:618` | `* and invlpg keeps the local TLB honest (cross-CPU shootdown rides  * the documented T5 follow-up...` |
| `kmm_ensure_pt` | function | `kernel/mm/paging.c:234` | `static volatile unsigned long *kmm_ensure_pt(unsigned long phys)` |
| `kmm_map_device` | function | `kernel/mm/paging.c:295` | `unsigned long kmm_map_device(unsigned long phys, unsigned long len)` |
| `mm_copy_user_page` | function | `kernel/mm/paging.c:950` | `int mm_copy_user_page(unsigned long dst_cr3, unsigned long src_cr3, unsigned long va)` |
| `mm_file_break` | function | `kernel/mm/paging.c:871` | `int mm_file_break(unsigned long cr3, unsigned long va)` |
| `mm_file_page_phys` | function | `kernel/mm/paging.c:669` | `unsigned long mm_file_page_phys(unsigned long cr3, unsigned long va)` |
| `mm_file_pte` | function | `kernel/mm/paging.c:688` | `static volatile unsigned long *mm_file_pte(unsigned long cr3,         unsigned long va)` |
| `mm_file_range_release` | function | `kernel/mm/paging.c:823` | `void mm_file_range_release(unsigned long cr3, unsigned long base,         unsigned long len, int ...` |
| `mm_lock` | variable | `kernel/mm/paging.c:659` | `extern spinlock_t mm_lock;` |
| `mm_page_aligned_alloc` | function | `kernel/mm/paging.c:31` | `static unsigned char *mm_page_aligned_alloc(unsigned size,                                       ...` |
| `mm_setup_protections` | function | `kernel/mm/paging.c:40` | `void mm_setup_protections(void)` |
| `mm_user_ensure_page` | function | `kernel/mm/paging.c:588` | `int mm_user_ensure_page(unsigned long cr3, unsigned long va)` |
| `mm_user_pte_update` | function | `kernel/mm/paging.c:335` | `void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3)` |
| `mm_user_set_exec` | function | `kernel/mm/paging.c:355` | `void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3)` |
| `mt_shared_slot` | function | `kernel/mm/paging.c:512` | `static int mt_shared_slot(unsigned long pd_idx)` |
| `pt_clone_user` | function | `kernel/mm/paging.c:383` | `uint64_t pt_clone_user(uint64_t parent_cr3)` |
| `pt_clone_user_empty` | function | `kernel/mm/paging.c:531` | `unsigned long pt_clone_user_empty(void)` |
| `pt_free_user` | function | `kernel/mm/paging.c:1032` | `void pt_free_user(uint64_t cr3)` |
| `pt_page_alloc` | function | `kernel/mm/paging.c:367` | `void *pt_page_alloc(void)` |
| `pt_page_free` | function | `kernel/mm/paging.c:377` | `void pt_page_free(void *ptr)` |
| `tables` | function | `kernel/mm/paging.c:818` | `* tables (munmap/mremap in caller context, under their mm_lock);` |
| `SWAP_CHUNK_CMP` | macro | `kernel/mm/swap.c:18` | `#define SWAP_CHUNK_CMP` |
| `SWAP_CHUNK_RAW` | macro | `kernel/mm/swap.c:17` | `#define SWAP_CHUNK_RAW` |
| `SWAP_CHUNK_SECTORS` | macro | `kernel/mm/swap.c:19` | `#define SWAP_CHUNK_SECTORS` |
| `SWAP_HDR_SECTORS` | macro | `kernel/mm/swap.c:20` | `#define SWAP_HDR_SECTORS` |
| `SWAP_MAGIC` | macro | `kernel/mm/swap.c:22` | `#define SWAP_MAGIC` |
| `SWAP_MAX_SECTORS` | macro | `kernel/mm/swap.c:21` | `#define SWAP_MAX_SECTORS` |
| `swap_ensure` | function | `kernel/mm/swap.c:28` | `static int swap_ensure(void)` |
| `swap_in` | function | `kernel/mm/swap.c:97` | `int swap_in(void)` |
| `swap_lba` | function | `kernel/mm/swap.c:41` | `static unsigned long swap_lba(void)` |
| `swap_out` | function | `kernel/mm/swap.c:47` | `int swap_out(unsigned long window_sz)` |
| `unwired` | function | `kernel/mm/swap.c:7` | `* * Currently unwired (the isolated-window spawn path superseded the * swap-out design);` |
| `panic_fb_hex` | function | `kernel/panic.c:61` | `static void panic_fb_hex(unsigned long v, int digits)` |
| `panic_fb_puts` | function | `kernel/panic.c:30` | `static void panic_fb_puts(const char *s)` |
| `panic_hex` | function | `kernel/panic.c:23` | `static void panic_hex(unsigned long v, int digits)` |
| `panic_screen` | function | `kernel/panic.c:96` | `void panic_screen(unsigned long vector, unsigned long err,         unsigned long rip, unsigned lo...` |
| `rq_cpu_valid` | function | `kernel/percpu_rq.c:14` | `static int rq_cpu_valid(int cpu)` |
| `rq_empty` | function | `kernel/percpu_rq.c:115` | `int rq_empty(int cpu)` |
| `rq_enqueue` | function | `kernel/percpu_rq.c:41` | `void rq_enqueue(int cpu, int pid)` |
| `rq_init` | function | `kernel/percpu_rq.c:19` | `void rq_init(void)` |
| `rq_note_poll` | function | `kernel/percpu_rq.c:127` | `void rq_note_poll(int cpu)` |
| `rq_pop_local` | function | `kernel/percpu_rq.c:61` | `int rq_pop_local(int cpu)` |
| `rq_should_rescan` | function | `kernel/percpu_rq.c:137` | `int rq_should_rescan(int cpu)` |
| `rq_stats` | function | `kernel/percpu_rq.c:152` | `void rq_stats(int cpu, unsigned long *hits, unsigned long *steals,               unsigned long *d...` |
| `rq_steal_once` | function | `kernel/percpu_rq.c:89` | `int rq_steal_once(int self_cpu, int *from_cpu)` |
| `emit_num` | function | `kernel/printf.c:26` | `static void emit_num(void (*emit)(char, void *, int *), void *ctx, int *written,                 ...` |
| `kformat` | function | `kernel/printf.c:44` | `static void kformat(void (*emit)(char, void *, int *), void *ctx,                     int *writte...` |
| `kfprintf` | function | `kernel/printf.c:157` | `int kfprintf(KFILE *f, const char *fmt, ...)` |
| `ksnprintf` | function | `kernel/printf.c:184` | `int ksnprintf(char *buf, unsigned long size, const char *fmt, ...)` |
| `ksprintf` | function | `kernel/printf.c:166` | `int ksprintf(char *buf, const char *fmt, ...)` |
| `putc_buf` | function | `kernel/printf.c:7` | `static void putc_buf(char c, void *ctx, int *written)` |
| `putc_file` | function | `kernel/printf.c:13` | `static void putc_file(char c, void *ctx, int *written)` |
| `putc_snbuf` | function | `kernel/printf.c:178` | `static void putc_snbuf(char c, void *ctx, int *written)` |
| `putc_str` | function | `kernel/printf.c:19` | `static void putc_str(char c, void *ctx, int *written)` |
| `snctx` | struct | `kernel/printf.c:177` | `` |
| `ERR_EACCES` | macro | `kernel/proc_sec.c:43` | `#define ERR_EACCES` |
| `ERR_EINVAL` | macro | `kernel/proc_sec.c:44` | `#define ERR_EINVAL` |
| `ERR_ENOMEM` | macro | `kernel/proc_sec.c:42` | `#define ERR_ENOMEM` |
| `ERR_ENOSYS` | macro | `kernel/proc_sec.c:45` | `#define ERR_ENOSYS` |
| `ERR_EOPNOTSUPP` | macro | `kernel/proc_sec.c:46` | `#define ERR_EOPNOTSUPP` |
| `LINUX_ERRNO_MAX` | macro | `kernel/proc_sec.c:36` | `#define LINUX_ERRNO_MAX` |
| `LINUX_NR_EXIT` | macro | `kernel/proc_sec.c:35` | `#define LINUX_NR_EXIT` |
| `LINUX_NR_READ` | macro | `kernel/proc_sec.c:32` | `#define LINUX_NR_READ` |
| `LINUX_NR_RT_SIGRETURN` | macro | `kernel/proc_sec.c:34` | `#define LINUX_NR_RT_SIGRETURN` |
| `LINUX_NR_WRITE` | macro | `kernel/proc_sec.c:33` | `#define LINUX_NR_WRITE` |
| `LINUX_PR_GET_DUMPABLE` | macro | `kernel/proc_sec.c:18` | `#define LINUX_PR_GET_DUMPABLE` |
| `LINUX_PR_GET_NAME` | macro | `kernel/proc_sec.c:21` | `#define LINUX_PR_GET_NAME` |
| `LINUX_PR_GET_NO_NEW_PRIVS` | macro | `kernel/proc_sec.c:25` | `#define LINUX_PR_GET_NO_NEW_PRIVS` |
| `LINUX_PR_GET_SECCOMP` | macro | `kernel/proc_sec.c:22` | `#define LINUX_PR_GET_SECCOMP` |
| `LINUX_PR_SET_DUMPABLE` | macro | `kernel/proc_sec.c:19` | `#define LINUX_PR_SET_DUMPABLE` |
| `LINUX_PR_SET_NAME` | macro | `kernel/proc_sec.c:20` | `#define LINUX_PR_SET_NAME` |
| `LINUX_PR_SET_NO_NEW_PRIVS` | macro | `kernel/proc_sec.c:24` | `#define LINUX_PR_SET_NO_NEW_PRIVS` |
| `LINUX_PR_SET_SECCOMP` | macro | `kernel/proc_sec.c:23` | `#define LINUX_PR_SET_SECCOMP` |
| `LINUX_SECCOMP_GET_ACTION_AVAIL` | macro | `kernel/proc_sec.c:31` | `#define LINUX_SECCOMP_GET_ACTION_AVAIL` |
| `LINUX_SECCOMP_MODE_DISABLED` | macro | `kernel/proc_sec.c:26` | `#define LINUX_SECCOMP_MODE_DISABLED` |
| `LINUX_SECCOMP_MODE_FILTER` | macro | `kernel/proc_sec.c:28` | `#define LINUX_SECCOMP_MODE_FILTER` |
| `LINUX_SECCOMP_MODE_STRICT` | macro | `kernel/proc_sec.c:27` | `#define LINUX_SECCOMP_MODE_STRICT` |
| `LINUX_SECCOMP_SET_MODE_FILTER` | macro | `kernel/proc_sec.c:30` | `#define LINUX_SECCOMP_SET_MODE_FILTER` |
| `LINUX_SECCOMP_SET_MODE_STRICT` | macro | `kernel/proc_sec.c:29` | `#define LINUX_SECCOMP_SET_MODE_STRICT` |
| `LINUX_TASK_COMM_LEN` | macro | `kernel/proc_sec.c:37` | `#define LINUX_TASK_COMM_LEN` |
| `SEC_STRICT_LEN` | macro | `kernel/proc_sec.c:72` | `#define SEC_STRICT_LEN` |
| `SOCK_FPROG_FILTER_OFF` | macro | `kernel/proc_sec.c:40` | `#define SOCK_FPROG_FILTER_OFF` |
| `SOCK_FPROG_SIZE` | macro | `kernel/proc_sec.c:39` | `#define SOCK_FPROG_SIZE` |
| `chain_put` | function | `kernel/proc_sec.c:78` | `static void chain_put(sec_filter_t *f)` |
| `pid_ok` | function | `kernel/proc_sec.c:74` | `static int pid_ok(int pid)` |
| `proc_sec_exe` | function | `kernel/proc_sec.c:125` | `const char *proc_sec_exe(int pid)` |
| `proc_sec_exec` | function | `kernel/proc_sec.c:115` | `void proc_sec_exec(int pid)` |
| `proc_sec_filter` | function | `kernel/proc_sec.c:136` | `int proc_sec_filter(long n, long a1, long a2, long a3, long a4, long a5, long a6, long *ret)` |
| `proc_sec_inherit` | function | `kernel/proc_sec.c:87` | `void proc_sec_inherit(int child, int parent)` |
| `proc_sec_prctl` | function | `kernel/proc_sec.c:235` | `long proc_sec_prctl(long option, long a2, long a3, long a4, long a5)` |
| `proc_sec_release` | function | `kernel/proc_sec.c:101` | `void proc_sec_release(int pid)` |
| `proc_sec_seccomp` | function | `kernel/proc_sec.c:290` | `long proc_sec_seccomp(long op, long flags, long uargs)` |
| `proc_sec_set_exe` | function | `kernel/proc_sec.c:119` | `void proc_sec_set_exe(int pid, const char *resolved)` |
| `ref` | type_alias | `kernel/proc_sec.c:47` | `typedef struct sec_filter { int ref;` |
| `sec_filter` | struct | `kernel/proc_sec.c:48` | `` |
| `sec_install` | function | `kernel/proc_sec.c:191` | `static long sec_install(const sbpf_insn *prog, unsigned len, int strict)` |
| `sec_install_user` | function | `kernel/proc_sec.c:224` | `static long sec_install_user(long ufprog)` |
| `sec_kill` | function | `kernel/proc_sec.c:130` | `static void sec_kill(long n, int whole_group)` |
| `expires` | function | `kernel/rcu.c:193` | `* expires (ticks stalled, never a hang). No completion assert is  * possible here by design: a re...` |
| `rcu_cpu_valid` | function | `kernel/rcu.c:40` | `static int rcu_cpu_valid(int cpu)` |
| `rcu_deref` | function | `kernel/rcu.c:88` | `void *rcu_deref(void *volatile *pp)` |
| `rcu_init` | function | `kernel/rcu.c:45` | `void rcu_init(void)` |
| `rcu_me` | function | `kernel/rcu.c:13` | `static cpu_t *rcu_me(void)` |
| `rcu_me` | function | `kernel/rcu.c:17` | `static cpu_t *rcu_me(void)` |
| `rcu_note_idle` | function | `kernel/rcu.c:137` | `void rcu_note_idle(int cpu)` |
| `rcu_note_tick` | function | `kernel/rcu.c:126` | `void rcu_note_tick(int cpu)` |
| `rcu_poll` | function | `kernel/rcu.c:152` | `void rcu_poll(void)` |
| `rcu_publish` | function | `kernel/rcu.c:94` | `void rcu_publish(void *volatile *pp, void *v)` |
| `rcu_read_lock` | function | `kernel/rcu.c:63` | `void rcu_read_lock(void)` |
| `rcu_read_unlock` | function | `kernel/rcu.c:75` | `void rcu_read_unlock(void)` |
| `rcu_slot_t` | struct | `kernel/rcu.c:22` | `` |
| `rcu_state_t` | struct | `kernel/rcu.c:28` | `` |
| `shell_report` | function | `kernel/redirect.c:17` | `void shell_report(const char *what, const char *detail)` |
| `shell_report_exit` | function | `kernel/redirect.c:11` | `void shell_report_exit(int code)` |
| `shell_take_redirect` | function | `kernel/redirect.c:25` | `int shell_take_redirect(int *argc, char **argv, char **path, int *append_mode)` |
| `BSP` | function | `kernel/sched.c:1606` | `* CPU believe it is the BSP (wrong per-CPU identity, two CPUs          * running the shell contex...` |
| `FSBASE` | function | `kernel/sched.c:744` | `* for FSBASE (per-proc TLS): a thread preempted after arch_prctl * would otherwise resume with whatever base the...` |
| `IRQ4` | function | `kernel/sched.c:628` | `* IRQ4 (COM1, UART IER stays 0 so it never fires) + * IRQ5 (Sound Blaster 16 DMA done). In the mask register a bit...` |
| `KSTACK_CANARY` | macro | `kernel/sched.c:162` | `#define KSTACK_CANARY` |
| `KSTACK_PAINT` | macro | `kernel/sched.c:161` | `#define KSTACK_PAINT` |
| `KSTACK_SZ` | macro | `kernel/sched.c:148` | `#define KSTACK_SZ` |
| `MSR` | function | `kernel/sched.c:2418` | `* in the MSR (the PCB field refreshes on switch-out) and its FPU * regs live in the CPU (the PCB image refreshes on...` |
| `MXCSR` | function | `kernel/sched.c:224` | `* A fresh image is explicit zeros plus the default MXCSR (0x1F80, all  * exceptions masked): fxsa...` |
| `MY_SYS_KSTK_TOP` | macro | `kernel/sched.c:52` | `#define MY_SYS_KSTK_TOP` |
| `MY_USER_LOAD_BASE` | macro | `kernel/sched.c:54` | `#define MY_USER_LOAD_BASE` |
| `MY_USER_STACK_TOP` | macro | `kernel/sched.c:53` | `#define MY_USER_STACK_TOP` |
| `PROC_KSTACK_OFF` | function | `kernel/sched.c:81` | `* PROC_KSTACK_OFF (it cannot use C here). The asm derives both * immediates from headers/syscall_asm.h, so this...` |
| `PROC_SWITCHING` | function | `kernel/sched.c:1990` | `* while the thread is still PROC_SWITCHING (never claimable), * then set the resume point and publish. A...` |
| `__attribute__` | function | `kernel/sched.c:108` | `typedef struct __attribute__((packed))` |
| `__attribute__` | function | `kernel/sched.c:136` | `typedef struct __attribute__((packed))` |
| `adopt` | function | `kernel/sched.c:2683` | `* adopt (armed by Linux O_CLOEXEC on open);` |
| `alloc_kstack` | function | `kernel/sched.c:188` | `static uint64_t alloc_kstack(void)` |
| `alloc_pid_locked` | function | `kernel/sched.c:2938` | `static int alloc_pid_locked(void)` |
| `aslr_brk_pages` | function | `kernel/sched.c:2658` | `unsigned long aslr_brk_pages(void)` |
| `aslr_dyn_base` | function | `kernel/sched.c:2660` | `unsigned long aslr_dyn_base(void)` |
| `aslr_mix` | function | `kernel/sched.c:2648` | `static unsigned long aslr_mix(unsigned long salt)` |
| `aslr_mmap_pages` | function | `kernel/sched.c:2659` | `unsigned long aslr_mmap_pages(void)` |
| `aslr_stack_bytes` | function | `kernel/sched.c:2657` | `unsigned long aslr_stack_bytes(void)` |
| `cli` | function | `kernel/sched.c:2669` | `* cli (disk PIO must never run with the timer held off);` |
| `context` | function | `kernel/sched.c:719` | `* context (anything entered via k_exec_user) is inside a syscall  * (entry swapped 0 in), and a c...` |
| `copy` | function | `kernel/sched.c:280` | `* copy (fail closed, fork refuses) instead of forging pointers. */ static vma_ctx_t *vma_ctx_copy...` |
| `ctx_from_frame` | function | `kernel/sched.c:2337` | `static void ctx_from_frame(ctx_regs_t *c, const syscall_frame_t *f)` |
| `descriptor` | function | `kernel/sched.c:96` | `* descriptor (two slots) per CPU past the 5 stage-2 entries. */ _Static_assert((5 + 2 * MAX_CPUS) * 8 ==...` |
| `do_clone_thread` | function | `kernel/sched.c:2504` | `static long do_clone_thread(unsigned long flags, unsigned long newsp,                            ...` |
| `do_execve` | function | `kernel/sched.c:2687` | `long do_execve(char *kpath, int kargc, char **kargv)` |
| `do_exit` | function | `kernel/sched.c:2061` | `void do_exit(int code)` |
| `do_exit_group_threads` | function | `kernel/sched.c:2632` | `void do_exit_group_threads(void)` |
| `do_fork` | function | `kernel/sched.c:2364` | `long do_fork(void)` |
| `do_fork_ex` | function | `kernel/sched.c:2368` | `long do_fork_ex(uint64_t set_tid, uint64_t clear_tid)` |
| `do_kill` | function | `kernel/sched.c:3065` | `int do_kill(int pid)` |
| `do_thread_spawn` | function | `kernel/sched.c:2115` | `long do_thread_spawn(unsigned long fn, unsigned long stack,                      unsigned long arg)` |
| `do_waitpid` | function | `kernel/sched.c:2965` | `int do_waitpid(int pid)` |
| `do_waitpid_linux` | function | `kernel/sched.c:2996` | `int do_waitpid_linux(int pid, int nohang, int *found)` |
| `exec_enter` | function | `kernel/sched.c:71` | `extern void exec_enter(unsigned long frame);` |
| `fork_child_settid` | function | `kernel/sched.c:2355` | `void fork_child_settid(void)` |
| `fork_trampoline` | function | `kernel/sched.c:66` | `extern void fork_trampoline(void);` |
| `fpu_alloc_clean` | function | `kernel/sched.c:236` | `static void *fpu_alloc_clean(void)` |
| `fpu_free_proc` | function | `kernel/sched.c:254` | `static void fpu_free_proc(proc_t *p)` |
| `fpu_restore_from` | function | `kernel/sched.c:232` | `static inline void fpu_restore_from(void *area)` |
| `gdb_dump_report` | function | `kernel/sched.c:548` | `void gdb_dump_report(unsigned long addr, unsigned long len)` |
| `here` | function | `kernel/sched.c:121` | `* smp_ap_idle_loop here (idle_proc ctx.rsp points at the top). */ static char ap_idle_stack[MAX_CPUS][4096]...` |
| `idt_init` | function | `kernel/sched.c:592` | `static void idt_init(void)` |
| `idt_set` | function | `kernel/sched.c:581` | `static void idt_set(int vec, void (*h)(void))` |
| `irqstat_report` | function | `kernel/sched.c:482` | `void irqstat_report(void)` |
| `isr_dispatch` | function | `kernel/sched.c:1027` | `void isr_dispatch(int vector, trap_frame_t *frame)` |
| `isr_stub_table` | variable | `kernel/sched.c:145` | `extern void *isr_stub_table[];` |
| `it` | function | `kernel/sched.c:3104` | `* it (SPAWN/exec point proc 0 here transiently);` |
| `itself` | function | `kernel/sched.c:2315` | `* the shell itself (use mrun first), and a CLONE_VM thread forking  * would duplicate shared stat...` |
| `kill_group_threads_locked` | function | `kernel/sched.c:2618` | `static void kill_group_threads_locked(int tgid, int except)` |
| `kstack_paint` | function | `kernel/sched.c:164` | `static void kstack_paint(uint64_t top, unsigned long size)` |
| `kstack_report` | function | `kernel/sched.c:371` | `void kstack_report(void)` |
| `kstack_usage` | function | `kernel/sched.c:173` | `static int kstack_usage(uint64_t top, unsigned long size,                         unsigned long *...` |
| `live` | function | `kernel/sched.c:204` | `* every reap leaked its own stack and released a neighbour that could  * still be live (two procs...` |
| `mm_lock` | variable | `kernel/sched.c:713` | `extern spinlock_t mm_lock;` |
| `net_rx_dropped` | variable | `kernel/sched.c:486` | `extern unsigned int net_rx_dropped;` |
| `off_lo` | type_alias | `kernel/sched.c:136` | `typedef struct __attribute__((packed)) { uint16_t off_lo;` |
| `park` | function | `kernel/sched.c:3155` | `* an image its live FPU registers would be dropped by the preempt * park (the save path skips a null area). */...` |
| `pic_eoi` | function | `kernel/sched.c:646` | `static void pic_eoi(int irq)` |
| `pic_init` | function | `kernel/sched.c:604` | `static void pic_init(void)` |
| `pit_init` | function | `kernel/sched.c:639` | `static void pit_init(void)` |
| `point` | function | `kernel/sched.c:732` | `* return address as the resume point ("continue the ISR"), which  * required the stranded ISR fra...` |
| `proc_create` | function | `kernel/sched.c:1637` | `int proc_create(const char *name, int parent_pid)` |
| `proc_get` | function | `kernel/sched.c:1631` | `proc_t *proc_get(int pid)` |
| `proc_running_anywhere` | function | `kernel/sched.c:2917` | `static int proc_running_anywhere(int pid)` |
| `proc_spawn_elf` | function | `kernel/sched.c:1915` | `int proc_spawn_elf(const char *name, void *data, unsigned size,                    int argc, char...` |
| `proc_spawn_elf_inner` | function | `kernel/sched.c:1755` | `static int proc_spawn_elf_inner(const char *name, void *data, unsigned size,                    i...` |
| `read_cr3` | function | `kernel/sched.c:73` | `static inline unsigned long read_cr3(void)` |
| `reap_autoreap_locked` | function | `kernel/sched.c:2926` | `static void reap_autoreap_locked(int tgid)` |
| `registers` | function | `kernel/sched.c:2146` | `* registers (float args would need XMM inheritance, which the * arg-passing contract does not carry: fn takes one...` |
| `res0` | type_alias | `kernel/sched.c:108` | `typedef struct __attribute__((packed)) { uint32_t res0;` |
| `returns` | function | `kernel/sched.c:2054` | `* that returns (and the resumed thread returns with IF=1). */ __asm__ volatile("cli");` |
| `rlimit_cpu_exceeded` | function | `kernel/sched.c:1006` | `int rlimit_cpu_exceeded(int pid)` |
| `rtl_counters` | function | `kernel/sched.c:485` | `extern void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames);` |
| `rtl_present` | function | `kernel/sched.c:487` | `extern int rtl_present(void);` |
| `sc_top_save` | variable | `kernel/sched.c:68` | `extern unsigned long sc_top_save[];` |
| `sched_ap_preempt` | function | `kernel/sched.c:900` | `static void sched_ap_preempt(trap_frame_t *frame)` |
| `sched_init` | function | `kernel/sched.c:3096` | `void sched_init(void)` |
| `sched_lock` | function | `kernel/sched.c:358` | `* hold sched_lock (+mm_lock at the swap sites);` |
| `sched_next_locked` | function | `kernel/sched.c:761` | `static int sched_next_locked(int start, int vm_only)` |
| `sched_set_nice` | function | `kernel/sched.c:779` | `int sched_set_nice(int pid, int nice)` |
| `sched_tick_audio` | function | `kernel/sched.c:25` | `static void sched_tick_audio(void *ctx)` |
| `sched_tick_desktop` | function | `kernel/sched.c:31` | `static void sched_tick_desktop(void *ctx)` |
| `sched_tick_usb` | function | `kernel/sched.c:42` | `static void sched_tick_usb(void *ctx)` |
| `schedtop_report` | function | `kernel/sched.c:414` | `void schedtop_report(void)` |
| `schedule` | function | `kernel/sched.c:1957` | `* that keeps schedule()'s own rbp runs the caller's frame accesses  * (locals, leave/ret) on the ...` |
| `schedule` | function | `kernel/sched.c:1964` | `void schedule(void)` |
| `seccomp_allow_one` | function | `kernel/sched.c:795` | `int seccomp_allow_one(int pid, int n)` |
| `seccomp_denied` | function | `kernel/sched.c:802` | `int seccomp_denied(int pid, int n)` |
| `seccomp_deny_one` | function | `kernel/sched.c:788` | `int seccomp_deny_one(int pid, int n)` |
| `shell_nchildren` | function | `kernel/sched.c:3039` | `int shell_nchildren(void)` |
| `shell_reap_nb` | function | `kernel/sched.c:3013` | `int shell_reap_nb(int *pid_out, int *code_out)` |
| `shell_reap_one` | function | `kernel/sched.c:3027` | `int shell_reap_one(int pid, int *code_out)` |
| `slot` | function | `kernel/sched.c:418` | `* must not eat a quarter of a 16 KB slot (see the stack discipline * contract in CLAUDE.md). Fail-closed on OOM. */...` |
| `smp_any_ap_idle` | function | `kernel/sched.c:970` | `static int smp_any_ap_idle(void)` |
| `smp_ap_idle_loop` | function | `kernel/sched.c:866` | `void smp_ap_idle_loop(void)` |
| `smp_claim_thread_v` | function | `kernel/sched.c:827` | `static int smp_claim_thread_v(int vm_only)` |
| `smp_try_claim_hint` | function | `kernel/sched.c:811` | `static int smp_try_claim_hint(int pid, int vm_only)` |
| `stop_row` | struct | `kernel/sched.c:415` | `` |
| `stub` | function | `kernel/sched.c:501` | `* gdb stub (`make gdb`, then `target remote :1234` from the host). These  * helpers are the seria...` |
| `sys_ticks` | function | `kernel/sched.c:478` | `* sys_ticks (PIT 100 Hz on the BSP, broadcast as IPIs to APs);` |
| `syscall` | function | `kernel/sched.c:1151` | `* outgoing syscall (see sched_rearm_kgs). Without * this the next entry swapgs puts garbage under GS * and the pid...` |
| `timer_tick` | function | `kernel/sched.c:3091` | `void timer_tick(void)` |
| `trap_frame_t` | struct | `kernel/sched.c:565` | `` |
| `tss_init` | function | `kernel/sched.c:670` | `static void tss_init(void)` |
| `tss_init_ap` | function | `kernel/sched.c:701` | `void tss_init_ap(int cpu)` |
| `tss_write_desc` | function | `kernel/sched.c:653` | `static void tss_write_desc(int cpu)` |
| `user_trampoline` | function | `kernel/sched.c:65` | `extern void user_trampoline(void);` |
| `vma_ctx_alloc` | function | `kernel/sched.c:260` | `vma_ctx_t *vma_ctx_alloc(void)` |
| `vma_ctx_free` | function | `kernel/sched.c:270` | `void vma_ctx_free(vma_ctx_t *c)` |
| `vma_load_proc` | function | `kernel/sched.c:364` | `static void vma_load_proc(proc_t *p)` |
| `vma_owned` | function | `kernel/sched.c:352` | `static int vma_owned(proc_t *p)` |
| `vma_save_proc` | function | `kernel/sched.c:360` | `static void vma_save_proc(proc_t *p)` |
| `waitpid_has_child` | function | `kernel/sched.c:2982` | `static int waitpid_has_child(int pid)` |
| `waitpid_scan` | function | `kernel/sched.c:2946` | `static int waitpid_scan(int pid, int *found)` |
| `yield` | function | `kernel/sched.c:2046` | `void yield(void)` |
| `zeroed` | function | `kernel/sched.c:3165` | `* still zeroed (kmemset happens inside idt_init) faults through a * null gate. Handlers for 32/33/44 are safe...` |
| `SCROLLBACK_ROWS` | macro | `kernel/scrollback.c:12` | `#define SCROLLBACK_ROWS` |
| `sb_capture_row0` | function | `kernel/scrollback.c:23` | `void sb_capture_row0(void)` |
| `sb_get_char` | function | `kernel/scrollback.c:41` | `char sb_get_char(int row, int col)` |
| `sb_get_count` | function | `kernel/scrollback.c:38` | `int sb_get_count(void)` |
| `sb_get_head` | function | `kernel/scrollback.c:39` | `int sb_get_head(void)` |
| `sb_init` | function | `kernel/scrollback.c:17` | `void sb_init(void)` |
| `sb_reset` | function | `kernel/scrollback.c:34` | `void sb_reset(void)` |
| `vga_scroll` | function | `kernel/scrollback.c:4` | `* Captured lazily from vga_scroll();` |
| `SBPF_MEM_ALL` | macro | `kernel/seccomp_bpf.c:14` | `#define SBPF_MEM_ALL` |
| `SBPF_MISC_MASK` | macro | `kernel/seccomp_bpf.c:13` | `#define SBPF_MISC_MASK` |
| `SBPF_MODE_MASK` | macro | `kernel/seccomp_bpf.c:11` | `#define SBPF_MODE_MASK` |
| `SBPF_OP_MASK` | macro | `kernel/seccomp_bpf.c:8` | `#define SBPF_OP_MASK` |
| `SBPF_RVAL_MASK` | macro | `kernel/seccomp_bpf.c:12` | `#define SBPF_RVAL_MASK` |
| `SBPF_SIZE_MASK` | macro | `kernel/seccomp_bpf.c:10` | `#define SBPF_SIZE_MASK` |
| `SBPF_SRC_MASK` | macro | `kernel/seccomp_bpf.c:9` | `#define SBPF_SRC_MASK` |
| `sbpf_action_rank` | function | `kernel/seccomp_bpf.c:194` | `int sbpf_action_rank(unsigned int action)` |
| `sbpf_check` | function | `kernel/seccomp_bpf.c:69` | `int sbpf_check(const sbpf_insn *prog, unsigned len, unsigned short *scratch)` |
| `sbpf_load_word` | function | `kernel/seccomp_bpf.c:114` | `static unsigned int sbpf_load_word(const sbpf_data *d, unsigned off)` |
| `sbpf_opcode_ok` | function | `kernel/seccomp_bpf.c:17` | `static int sbpf_opcode_ok(const sbpf_insn *in)` |
| `sbpf_run` | function | `kernel/seccomp_bpf.c:120` | `unsigned int sbpf_run(const sbpf_insn *prog, unsigned len, const sbpf_data *d)` |
| `COM1` | macro | `kernel/serial.c:18` | `#define COM1` |
| `serial_available` | function | `kernel/serial.c:42` | `int serial_available(void)` |
| `serial_e_count` | function | `kernel/serial.c:38` | `unsigned long serial_e_count(void)` |
| `serial_getc` | function | `kernel/serial.c:44` | `int serial_getc(void)` |
| `serial_init` | function | `kernel/serial.c:20` | `void serial_init(void)` |
| `serial_putc` | function | `kernel/serial.c:33` | `void serial_putc(char c)` |
| `serial_puts` | function | `kernel/serial.c:40` | `void serial_puts(const char *s)` |
| `serial_rx_ready` | function | `kernel/serial.c:31` | `static int serial_rx_ready(void)` |
| `serial_tx_ready` | function | `kernel/serial.c:30` | `static int serial_tx_ready(void)` |
| `HTTPD_IO_CHUNK` | macro | `kernel/shell.c:2505` | `#define HTTPD_IO_CHUNK` |
| `HTTPD_REQ_CAP` | macro | `kernel/shell.c:2504` | `#define HTTPD_REQ_CAP` |
| `PIPE_HOP_MAX` | macro | `kernel/shell.c:4018` | `#define PIPE_HOP_MAX` |
| `QEMU_PM_PORT` | macro | `kernel/shell.c:1013` | `#define QEMU_PM_PORT` |
| `SHELL_BUILTIN_COUNT` | macro | `kernel/shell.c:229` | `#define SHELL_BUILTIN_COUNT` |
| `SHELL_CVM_INTERP` | macro | `kernel/shell.c:50` | `#define SHELL_CVM_INTERP` |
| `SHELL_HIST_MAX` | macro | `kernel/shell.c:95` | `#define SHELL_HIST_MAX` |
| `SHELL_LS_CAP` | macro | `kernel/shell.c:2762` | `#define SHELL_LS_CAP` |
| `SHELL_RUN_DIRS` | macro | `kernel/shell.c:69` | `#define SHELL_RUN_DIRS` |
| `ShellRunDir` | struct | `kernel/shell.c:58` | `` |
| `VMA` | function | `kernel/shell.c:2149` | `* plus the live VMA (mmap) tree. The walk is bounded (64-deep explicit  * stack, 128 regions prin...` |
| `XXH_STATIC_LINKING_ONLY` | macro | `kernel/shell.c:25` | `#define XXH_STATIC_LINKING_ONLY` |
| `code` | function | `kernel/shell.c:1356` | `* the last exit code (130 when interrupted). */ static int shell_wait_fg(int *pids, int n, int ki...` |
| `context` | function | `kernel/shell.c:1647` | `* from ISR context (which corrupts the running program's state). */ shell_queue_launch(cmd);` |
| `desktop_flag` | function | `kernel/shell.c:1509` | `static void desktop_flag(const char *name)` |
| `desktop_flag_on` | function | `kernel/shell.c:1519` | `static int desktop_flag_on(const char *name)` |
| `desktop_path` | function | `kernel/shell.c:1500` | `static void desktop_path(const char *name, char *dst, unsigned cap)` |
| `desktop_srv_alive` | function | `kernel/shell.c:1541` | `static int desktop_srv_alive(void)` |
| `desktop_unflag` | function | `kernel/shell.c:830` | `static void desktop_unflag(const char *name);` |
| `driver` | function | `kernel/shell.c:3264` | `* stream through the fat: VFS driver ("img:fatpath" per open,      * registered at boot beside me...` |
| `etrel_path_trusted` | function | `kernel/shell.c:1103` | `static int etrel_path_trusted(const char *full)` |
| `flows` | function | `kernel/shell.c:1533` | `* and external flows (make wl) set it themselves. */ static void desktop_unflag(const char *name)` |
| `frame` | function | `kernel/shell.c:3658` | `* not live in this frame (stack discipline, CLAUDE.md). */ struct ps_row *snap = (struct ps_row...` |
| `gfx_parse_int` | function | `kernel/shell.c:1692` | `static int gfx_parse_int(const char *s, int *out)` |
| `gfx_read_palette` | function | `kernel/shell.c:1712` | `static void gfx_read_palette(unsigned char pal[768])` |
| `job_row` | struct | `kernel/shell.c:2020` | `` |
| `line` | function | `kernel/shell.c:443` | `* to the live line (handled by the caller resetting shell_hist_idx). */ static void shell_hist_na...` |
| `outw_port` | function | `kernel/shell.c:1009` | `static inline void outw_port(unsigned short port, unsigned short val)` |
| `ps_row` | struct | `kernel/shell.c:3656` | `` |
| `root` | function | `kernel/shell.c:648` | `* MiniFS root (where the big ELFs live under bare names), * and only the highest-priority non-empty tier is kept. An...` |
| `shell_cmd_desktop` | function | `kernel/shell.c:1557` | `static void shell_cmd_desktop(int argc, char **argv)` |
| `shell_cmd_gdb` | function | `kernel/shell.c:2343` | `static void shell_cmd_gdb(int argc, char **argv)` |
| `shell_cmd_gfx` | function | `kernel/shell.c:1719` | `static void shell_cmd_gfx(int argc, char **argv)` |
| `shell_cmd_hash` | function | `kernel/shell.c:2386` | `static void shell_cmd_hash(int argc, char **argv)` |
| `shell_cmd_jobs` | function | `kernel/shell.c:2019` | `static void shell_cmd_jobs(void)` |
| `shell_cmd_kill` | function | `kernel/shell.c:2093` | `static void shell_cmd_kill(int argc, char **argv)` |
| `shell_cmd_mem` | function | `kernel/shell.c:2116` | `static void shell_cmd_mem(void)` |
| `shell_cmd_mrun` | function | `kernel/shell.c:1409` | `static void shell_cmd_mrun(int argc, char **argv)` |
| `shell_cmd_poweroff` | function | `kernel/shell.c:1015` | `static void shell_cmd_poweroff(void)` |
| `shell_cmd_wait` | function | `kernel/shell.c:2058` | `static void shell_cmd_wait(int argc, char **argv)` |
| `shell_cmd_wm` | function | `kernel/shell.c:1871` | `static void shell_cmd_wm(int argc, char **argv)` |

Next: [SYMBOLS_p9.md](SYMBOLS_p9.md)
