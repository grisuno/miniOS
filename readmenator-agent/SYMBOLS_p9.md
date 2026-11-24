# Symbols (page 9 of 28)
Previous: [SYMBOLS_p8.md](SYMBOLS_p8.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `elf_sign_u64` | function | `kernel/loader.c:1172` | `static void elf_sign_u64(ed_sha *c, unsigned long v)` |
| `elf_wants_process` | function | `kernel/loader.c:1432` | `int elf_wants_process(const void *data, unsigned size)` |
| `exec_range` | struct | `kernel/loader.c:104` | `` |
| `images` | function | `kernel/loader.c:790` | `* Static images (no dynamic section, or none needed) return 0 at * once, so the legacy paths never observe a...` |
| `inodes` | function | `kernel/loader.c:381` | `* Pseudo inodes (LDSO_INO_BASE + slot) keep registry pages apart from * MiniFS inodes in the shared cache. No unload...` |
| `ldso_bind_into` | function | `kernel/loader.c:794` | `int ldso_bind_into(void *data, unsigned size, unsigned long base,         unsigned long cr3, vma_...` |
| `ldso_ensure_slot` | function | `kernel/loader.c:483` | `static int ldso_ensure_slot(const char *needed, int *slot_out)` |
| `ldso_pseudo_read` | function | `kernel/loader.c:416` | `int ldso_pseudo_read(int ino, void *dst, unsigned long off, unsigned len)` |
| `ldso_pseudo_stat` | function | `kernel/loader.c:402` | `int ldso_pseudo_stat(int ino, unsigned long *size_out)` |
| `ldso_read_file` | function | `kernel/loader.c:441` | `static int ldso_read_file(const char *name, unsigned char **out,         unsigned *size_out)` |
| `load_exec_elf` | function | `kernel/loader.c:1262` | `void *load_exec_elf(void *data, unsigned size)` |
| `load_exec_elf_into` | function | `kernel/loader.c:1456` | `void *load_exec_elf_into(void *data, unsigned size, unsigned long cr3,                          u...` |
| `process` | function | `kernel/loader.c:1288` | `* atomic section: a 100 Hz tick between two segments would switch * CR3 into another process (copies landing in its...` |
| `time` | function | `kernel/loader.c:1520` | `* time (with the failing offset);` |
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
| `KMALLOC_REPORT_EVERY` | macro | `kernel/mm.c:50` | `#define KMALLOC_REPORT_EVERY` |
| `kallocator_init` | function | `kernel/mm.c:32` | `void kallocator_init(void)` |
| `kcalloc` | function | `kernel/mm.c:111` | `void *kcalloc(unsigned long nmemb, unsigned long size)` |
| `kfree` | function | `kernel/mm.c:90` | `void kfree(void *ptr)` |
| `kfree_aligned` | function | `kernel/mm.c:143` | `void kfree_aligned(void *ptr)` |
| `kheap_ram_top` | function | `kernel/mm.c:19` | `static unsigned long kheap_ram_top(void)` |
| `kmalloc` | function | `kernel/mm.c:66` | `void *kmalloc(unsigned long size)` |
| `kmalloc_aligned` | function | `kernel/mm.c:127` | `void *kmalloc_aligned(unsigned long size, unsigned long align)` |
| `kmalloc_page` | function | `kernel/mm.c:81` | `void *kmalloc_page(void)` |
| `kmalloc_report_failure` | function | `kernel/mm.c:53` | `static void kmalloc_report_failure(unsigned long size)` |
| `krealloc` | function | `kernel/mm.c:115` | `void *krealloc(void *ptr, unsigned long size)` |
| `COW_BITS` | macro | `kernel/mm/cow.c:34` | `#define COW_BITS` |
| `COW_CAP` | macro | `kernel/mm/cow.c:35` | `#define COW_CAP` |
| `COW_EMPTY` | macro | `kernel/mm/cow.c:39` | `#define COW_EMPTY` |
| `COW_HASH_MUL` | macro | `kernel/mm/cow.c:41` | `#define COW_HASH_MUL` |
| `COW_LOAD_MAX` | macro | `kernel/mm/cow.c:37` | `#define COW_LOAD_MAX` |
| `COW_MASK` | macro | `kernel/mm/cow.c:36` | `#define COW_MASK` |
| `COW_TOMB` | macro | `kernel/mm/cow.c:40` | `#define COW_TOMB` |
| `COW_TOMB_MAX` | macro | `kernel/mm/cow.c:38` | `#define COW_TOMB_MAX` |
| `CPU` | function | `kernel/mm/cow.c:287` | `* address space down on every other CPU (tlb_shootdown in do_fork_ex). */ unsigned long cow_fork_...` |
| `PT_PTE_RW` | macro | `kernel/mm/cow.c:48` | `#define PT_PTE_RW` |
| `PT_USER_RO` | macro | `kernel/mm/cow.c:46` | `#define PT_USER_RO` |
| `PT_USER_RW_ENTRY` | macro | `kernel/mm/cow.c:47` | `#define PT_USER_RW_ENTRY` |
| `alternative` | function | `kernel/mm/cow.c:20` | `* window is one instruction wide and the alternative (no CoW) is * documented, so the trade stands. */ #include...` |
| `cow_copy_demand` | function | `kernel/mm/cow.c:166` | `static void cow_copy_demand(unsigned long pcr3, unsigned long ccr3)` |
| `cow_entry_t` | struct | `kernel/mm/cow.c:58` | `` |
| `cow_find` | function | `kernel/mm/cow.c:73` | `static int cow_find(unsigned long phys)` |
| `cow_fork_one` | function | `kernel/mm/cow.c:255` | `static void cow_fork_one(unsigned long pcr3, unsigned long va,         volatile unsigned long *ppte)` |
| `cow_page_shared` | function | `kernel/mm/cow.c:132` | `int cow_page_shared(unsigned long phys)` |
| `cow_rehash` | function | `kernel/mm/cow.c:110` | `static void cow_rehash(void)` |
| `cow_release_window` | function | `kernel/mm/cow.c:421` | `void cow_release_window(unsigned long cr3)` |
| `cow_remove` | function | `kernel/mm/cow.c:85` | `static void cow_remove(int idx)` |
| `cow_resolve` | function | `kernel/mm/cow.c:356` | `int cow_resolve(unsigned long cr3, unsigned long va)` |
| `cow_shared` | function | `kernel/mm/cow.c:464` | `int cow_shared(void)` |
| `cow_slot` | function | `kernel/mm/cow.c:68` | `static unsigned long cow_slot(unsigned long phys)` |
| `cow_table_ensure` | function | `kernel/mm/cow.c:98` | `static void cow_table_ensure(void)` |
| `cow_track` | function | `kernel/mm/cow.c:191` | `static int cow_track(unsigned long phys)` |
| `cow_walk` | function | `kernel/mm/cow.c:221` | `static void cow_walk(unsigned long cr3, cow_walk_fn fn)` |
| `private` | function | `kernel/mm/cow.c:217` | `* for every present page in a private (non-graphics) slot. Shared * graphics slots are never CoW: the compositor...` |
| `KMM_DEVICE_FLAGS` | macro | `kernel/mm/paging.c:211` | `#define KMM_DEVICE_FLAGS` |
| `KMM_DEVICE_MAX` | macro | `kernel/mm/paging.c:200` | `#define KMM_DEVICE_MAX` |
| `KMM_DEVICE_WINDOWS` | macro | `kernel/mm/paging.c:286` | `#define KMM_DEVICE_WINDOWS` |
| `KMM_MAX_IDENTITY` | macro | `kernel/mm/paging.c:204` | `#define KMM_MAX_IDENTITY` |
| `PTE` | function | `kernel/mm/paging.c:1055` | `* PTE (a cache page stays cached, but no stale writer may reach it).  * Never allocates. */ void ...` |
| `PT_OWNED_BYTES` | macro | `kernel/mm/paging.c:411` | `#define PT_OWNED_BYTES` |
| `_kernel_end` | variable | `kernel/mm/paging.c:49` | `extern char _kernel_end[];` |
| `coherent` | function | `kernel/mm/paging.c:245` | `* for memory a device reads and writes by DMA: a controller that is not cache  * coherent (and an...` |
| `explicitly` | function | `kernel/mm/paging.c:1051` | `* teardown passes the dying window explicitly (zombie-exclusive, no * lock needed). unmap == 0 drops refs only...` |
| `honest` | function | `kernel/mm/paging.c:695` | `* and invlpg keeps the local TLB honest (cross-CPU shootdown rides  * the documented T5 follow-up...` |
| `kmm_ensure_pt` | function | `kernel/mm/paging.c:221` | `static volatile unsigned long *kmm_ensure_pt(unsigned long phys)` |
| `mm_anon_fault` | function | `kernel/mm/paging.c:819` | `int mm_anon_fault(unsigned long cr3, unsigned long va, int write)` |
| `mm_anon_frame` | function | `kernel/mm/paging.c:755` | `static int mm_anon_frame(unsigned long phys)` |
| `mm_copy_user_page` | function | `kernel/mm/paging.c:1189` | `int mm_copy_user_page(unsigned long dst_cr3, unsigned long src_cr3, unsigned long va)` |
| `mm_demand_pte` | function | `kernel/mm/paging.c:744` | `unsigned long mm_demand_pte(unsigned long prot)` |
| `mm_file_break` | function | `kernel/mm/paging.c:1110` | `int mm_file_break(unsigned long cr3, unsigned long va)` |
| `mm_file_page_phys` | function | `kernel/mm/paging.c:901` | `unsigned long mm_file_page_phys(unsigned long cr3, unsigned long va)` |
| `mm_file_pte` | function | `kernel/mm/paging.c:920` | `static volatile unsigned long *mm_file_pte(unsigned long cr3,         unsigned long va)` |
| `mm_lock` | variable | `kernel/mm/paging.c:736` | `extern spinlock_t mm_lock;` |
| `mm_page_aligned_alloc` | function | `kernel/mm/paging.c:32` | `static unsigned char *mm_page_aligned_alloc(unsigned size,                                       ...` |
| `mm_setup_protections` | function | `kernel/mm/paging.c:41` | `void mm_setup_protections(void)` |
| `mm_user_ensure_page` | function | `kernel/mm/paging.c:665` | `int mm_user_ensure_page(unsigned long cr3, unsigned long va)` |
| `mm_user_pte_update` | function | `kernel/mm/paging.c:376` | `void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3)` |
| `mm_user_set_exec` | function | `kernel/mm/paging.c:396` | `void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3)` |
| `mt_shared_slot` | function | `kernel/mm/paging.c:589` | `static int mt_shared_slot(unsigned long pd_idx)` |
| `pt_clone_user` | function | `kernel/mm/paging.c:460` | `uint64_t pt_clone_user(uint64_t parent_cr3)` |
| `pt_clone_user_empty` | function | `kernel/mm/paging.c:608` | `unsigned long pt_clone_user_empty(void)` |
| `pt_free_user` | function | `kernel/mm/paging.c:1267` | `void pt_free_user(uint64_t cr3)` |
| `pt_owned_index` | function | `kernel/mm/paging.c:414` | `static int pt_owned_index(unsigned long phys, unsigned long *byte, unsigned *bit)` |
| `pt_page_alloc` | function | `kernel/mm/paging.c:432` | `void *pt_page_alloc(void)` |
| `pt_page_free` | function | `kernel/mm/paging.c:451` | `void pt_page_free(void *ptr)` |
| `pt_page_owned` | function | `kernel/mm/paging.c:425` | `int pt_page_owned(unsigned long phys)` |
| `tables` | function | `kernel/mm/paging.c:1050` | `* tables (munmap/mremap in caller context, under their mm_lock);` |
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
| `TLB_SHOOT_SPIN_MAX` | macro | `kernel/mm/tlb.c:24` | `#define TLB_SHOOT_SPIN_MAX` |
| `tlb_others_on` | function | `kernel/mm/tlb.c:36` | `static int tlb_others_on(unsigned long cr3)` |
| `tlb_shootdown` | function | `kernel/mm/tlb.c:49` | `void tlb_shootdown(unsigned long cr3)` |
| `tlb_shootdown_count` | function | `kernel/mm/tlb.c:71` | `unsigned long tlb_shootdown_count(void)` |
| `tlb_shootdown_timeouts` | function | `kernel/mm/tlb.c:75` | `unsigned long tlb_shootdown_timeouts(void)` |
| `panic_fb_hex` | function | `kernel/panic.c:61` | `static void panic_fb_hex(unsigned long v, int digits)` |
| `panic_fb_puts` | function | `kernel/panic.c:30` | `static void panic_fb_puts(const char *s)` |
| `panic_hex` | function | `kernel/panic.c:23` | `static void panic_hex(unsigned long v, int digits)` |
| `panic_screen` | function | `kernel/panic.c:98` | `void panic_screen(unsigned long vector, unsigned long err,         unsigned long rip, unsigned lo...` |
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
| `BSP` | function | `kernel/sched.c:1780` | `* CPU believe it is the BSP (wrong per-CPU identity, two CPUs          * running the shell contex...` |
| `FSBASE` | function | `kernel/sched.c:913` | `* for FSBASE (per-proc TLS): a thread preempted after arch_prctl * would otherwise resume with whatever base the...` |
| `IRQ4` | function | `kernel/sched.c:796` | `* IRQ4 (COM1, UART IER stays 0 so it never fires) + * IRQ5 (Sound Blaster 16 DMA done). In the mask register a bit...` |
| `KSTACK_CANARY` | macro | `kernel/sched.c:169` | `#define KSTACK_CANARY` |
| `KSTACK_PAINT` | macro | `kernel/sched.c:168` | `#define KSTACK_PAINT` |
| `KSTACK_SZ` | macro | `kernel/sched.c:155` | `#define KSTACK_SZ` |
| `MSR` | function | `kernel/sched.c:2633` | `* in the MSR (the PCB field refreshes on switch-out) and its FPU * regs live in the CPU (the PCB image refreshes on...` |
| `MXCSR` | function | `kernel/sched.c:306` | `* A fresh image is explicit zeros plus the default MXCSR (0x1F80, all  * exceptions masked): fxsa...` |
| `MY_SYS_KSTK_TOP` | macro | `kernel/sched.c:53` | `#define MY_SYS_KSTK_TOP` |
| `MY_USER_LOAD_BASE` | macro | `kernel/sched.c:55` | `#define MY_USER_LOAD_BASE` |
| `MY_USER_STACK_TOP` | macro | `kernel/sched.c:54` | `#define MY_USER_STACK_TOP` |
| `NMI_IST_SLOT` | macro | `kernel/sched.c:125` | `#define NMI_IST_SLOT` |
| `NMI_IST_STACK_SZ` | macro | `kernel/sched.c:123` | `#define NMI_IST_STACK_SZ` |
| `NMI_VECTOR` | macro | `kernel/sched.c:124` | `#define NMI_VECTOR` |
| `PROC_KSTACK_OFF` | function | `kernel/sched.c:82` | `* PROC_KSTACK_OFF (it cannot use C here). The asm derives both * immediates from headers/syscall_asm.h, so this...` |
| `PROC_SWITCHING` | function | `kernel/sched.c:2180` | `* while the thread is still PROC_SWITCHING (never claimable), * then set the resume point and publish. A...` |
| `__attribute__` | function | `kernel/sched.c:109` | `typedef struct __attribute__((packed))` |
| `__attribute__` | function | `kernel/sched.c:143` | `typedef struct __attribute__((packed))` |
| `adopt` | function | `kernel/sched.c:2922` | `* adopt (armed by Linux O_CLOEXEC on open);` |
| `alloc_kstack` | function | `kernel/sched.c:262` | `static uint64_t alloc_kstack(void)` |
| `alloc_pid_locked` | function | `kernel/sched.c:3180` | `static int alloc_pid_locked(void)` |
| `aslr_brk_pages` | function | `kernel/sched.c:2897` | `unsigned long aslr_brk_pages(void)` |
| `aslr_dyn_base` | function | `kernel/sched.c:2899` | `unsigned long aslr_dyn_base(void)` |
| `aslr_mix` | function | `kernel/sched.c:2887` | `static unsigned long aslr_mix(unsigned long salt)` |
| `aslr_mmap_pages` | function | `kernel/sched.c:2898` | `unsigned long aslr_mmap_pages(void)` |
| `aslr_stack_bytes` | function | `kernel/sched.c:2896` | `unsigned long aslr_stack_bytes(void)` |
| `cli` | function | `kernel/sched.c:2908` | `* cli (disk PIO must never run with the timer held off);` |
| `context` | function | `kernel/sched.c:888` | `* context (anything entered via k_exec_user) is inside a syscall  * (entry swapped 0 in), and a c...` |
| `copy` | function | `kernel/sched.c:362` | `* copy (fail closed, fork refuses) instead of forging pointers. */ /* Name the link a fork could ...` |
| `ctx_from_frame` | function | `kernel/sched.c:2537` | `static void ctx_from_frame(ctx_regs_t *c, const syscall_frame_t *f)` |
| `descriptor` | function | `kernel/sched.c:97` | `* descriptor (two slots) per CPU past the 5 stage-2 entries. */ _Static_assert((5 + 2 * MAX_CPUS) * 8 ==...` |
| `do_clone_thread` | function | `kernel/sched.c:2724` | `static long do_clone_thread(unsigned long flags, unsigned long newsp,                            ...` |
| `do_execve` | function | `kernel/sched.c:2926` | `long do_execve(char *kpath, int kargc, char **kargv)` |
| `do_exit` | function | `kernel/sched.c:2250` | `void do_exit(int code)` |
| `do_fork` | function | `kernel/sched.c:2564` | `long do_fork(void)` |
| `do_fork_ex` | function | `kernel/sched.c:2577` | `long do_fork_ex(uint64_t set_tid, uint64_t clear_tid)` |
| `do_group_exit` | function | `kernel/sched.c:2859` | `void do_group_exit(int code)` |
| `do_kill` | function | `kernel/sched.c:3324` | `int do_kill(int pid)` |
| `do_kill_code` | function | `kernel/sched.c:3330` | `int do_kill_code(int pid, int code)` |
| `do_thread_spawn` | function | `kernel/sched.c:2314` | `long do_thread_spawn(unsigned long fn, unsigned long stack,                      unsigned long arg)` |
| `do_waitpid` | function | `kernel/sched.c:3224` | `int do_waitpid(int pid)` |
| `do_waitpid_linux` | function | `kernel/sched.c:3255` | `int do_waitpid_linux(int pid, int nohang, int *found)` |
| `exec_enter` | function | `kernel/sched.c:72` | `extern void exec_enter(unsigned long frame);` |
| `fork_child_settid` | function | `kernel/sched.c:2555` | `void fork_child_settid(void)` |
| `fork_report` | function | `kernel/sched.c:2570` | `static void fork_report(const char *what)` |
| `fork_trampoline` | function | `kernel/sched.c:67` | `extern void fork_trampoline(void);` |
| `fpu_alloc_clean` | function | `kernel/sched.c:318` | `static void *fpu_alloc_clean(void)` |
| `fpu_free_proc` | function | `kernel/sched.c:336` | `static void fpu_free_proc(proc_t *p)` |
| `fpu_restore_from` | function | `kernel/sched.c:314` | `static inline void fpu_restore_from(void *area)` |
| `gdb_dump_report` | function | `kernel/sched.c:697` | `void gdb_dump_report(unsigned long addr, unsigned long len)` |
| `group_threads_live_locked` | function | `kernel/sched.c:3192` | `static int group_threads_live_locked(int tgid)` |
| `here` | function | `kernel/sched.c:128` | `* smp_ap_idle_loop here (idle_proc ctx.rsp points at the top). */ static char ap_idle_stack[MAX_CPUS][4096]...` |
| `idt_init` | function | `kernel/sched.c:756` | `static void idt_init(void)` |
| `idt_set` | function | `kernel/sched.c:745` | `static void idt_set(int vec, void (*h)(void))` |
| `irqstat_report` | function | `kernel/sched.c:631` | `void irqstat_report(void)` |
| `isr_dispatch` | function | `kernel/sched.c:1203` | `void isr_dispatch(int vector, trap_frame_t *frame)` |
| `isr_stub_table` | variable | `kernel/sched.c:152` | `extern void *isr_stub_table[];` |
| `it` | function | `kernel/sched.c:3370` | `* it (SPAWN/exec point proc 0 here transiently);` |
| `itself` | function | `kernel/sched.c:2514` | `* the shell itself (use mrun first), and a CLONE_VM thread forking  * would duplicate shared stat...` |
| `kill_group_threads_locked` | function | `kernel/sched.c:2838` | `static void kill_group_threads_locked(int tgid, int except)` |
| `kstack_is_slot_end` | function | `kernel/sched.c:199` | `static int kstack_is_slot_end(uint64_t v)` |
| `kstack_of` | function | `kernel/sched.c:209` | `static uint64_t kstack_of(int j)` |
| `kstack_owner` | function | `kernel/sched.c:216` | `static int kstack_owner(uint64_t top)` |
| `kstack_paint` | function | `kernel/sched.c:171` | `static void kstack_paint(uint64_t top, unsigned long size)` |
| `kstack_report` | function | `kernel/sched.c:520` | `void kstack_report(void)` |
| `kstack_scan_serial` | function | `kernel/sched.c:231` | `static void kstack_scan_serial(void)` |
| `kstack_usage` | function | `kernel/sched.c:180` | `static int kstack_usage(uint64_t top, unsigned long size,                         unsigned long *...` |
| `live` | function | `kernel/sched.c:286` | `* every reap leaked its own stack and released a neighbour that could  * still be live (two procs...` |
| `mm_lock` | variable | `kernel/sched.c:882` | `extern spinlock_t mm_lock;` |
| `mm_owner` | function | `kernel/sched.c:472` | `static proc_t *mm_owner(proc_t *p)` |
| `mm_view_claim_current` | function | `kernel/sched.c:513` | `void mm_view_claim_current(void)` |
| `mm_view_enter` | function | `kernel/sched.c:494` | `static void mm_view_enter(proc_t *nxt)` |
| `net_rx_dropped` | variable | `kernel/sched.c:635` | `extern unsigned int net_rx_dropped;` |
| `off_lo` | type_alias | `kernel/sched.c:143` | `typedef struct __attribute__((packed)) { uint16_t off_lo;` |
| `park` | function | `kernel/sched.c:3422` | `* an image its live FPU registers would be dropped by the preempt * park (the save path skips a null area). */...` |
| `pic_eoi` | function | `kernel/sched.c:814` | `static void pic_eoi(int irq)` |
| `pic_init` | function | `kernel/sched.c:772` | `static void pic_init(void)` |
| `pit_init` | function | `kernel/sched.c:807` | `static void pit_init(void)` |
| `point` | function | `kernel/sched.c:901` | `* return address as the resume point ("continue the ISR"), which  * required the stranded ISR fra...` |
| `proc_create` | function | `kernel/sched.c:1827` | `int proc_create(const char *name, int parent_pid)` |
| `proc_get` | function | `kernel/sched.c:1821` | `proc_t *proc_get(int pid)` |
| `proc_running_anywhere` | function | `kernel/sched.c:3159` | `static int proc_running_anywhere(int pid)` |
| `proc_spawn_elf` | function | `kernel/sched.c:2105` | `int proc_spawn_elf(const char *name, void *data, unsigned size,                    int argc, char...` |
| `proc_spawn_elf_inner` | function | `kernel/sched.c:1945` | `static int proc_spawn_elf_inner(const char *name, void *data, unsigned size,                    i...` |
| `read_cr3` | function | `kernel/sched.c:74` | `static inline unsigned long read_cr3(void)` |
| `reap_autoreap_locked` | function | `kernel/sched.c:3168` | `static void reap_autoreap_locked(int tgid)` |
| `registers` | function | `kernel/sched.c:2345` | `* registers (float args would need XMM inheritance, which the * arg-passing contract does not carry: fn takes one...` |
| `res0` | type_alias | `kernel/sched.c:109` | `typedef struct __attribute__((packed)) { uint32_t res0;` |
| `returns` | function | `kernel/sched.c:2243` | `* that returns (and the resumed thread returns with IF=1). */ __asm__ volatile("cli");` |
| `rlimit_cpu_exceeded` | function | `kernel/sched.c:1182` | `int rlimit_cpu_exceeded(int pid)` |
| `rtl_counters` | function | `kernel/sched.c:634` | `extern void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames);` |
| `rtl_present` | function | `kernel/sched.c:636` | `extern int rtl_present(void);` |
| `sc_top_save` | variable | `kernel/sched.c:69` | `extern unsigned long sc_top_save[];` |
| `sched_ap_preempt` | function | `kernel/sched.c:1076` | `static void sched_ap_preempt(trap_frame_t *frame)` |
| `sched_idle_on_kernel_cr3` | function | `kernel/sched.c:723` | `int sched_idle_on_kernel_cr3(int cpu)` |
| `sched_init` | function | `kernel/sched.c:3362` | `void sched_init(void)` |
| `sched_lock` | function | `kernel/sched.c:452` | `* hold sched_lock (+mm_lock at the swap sites);` |
| `sched_next_locked` | function | `kernel/sched.c:930` | `static int sched_next_locked(int start, int vm_only)` |
| `sched_set_nice` | function | `kernel/sched.c:948` | `int sched_set_nice(int pid, int nice)` |
| `sched_tick_audio` | function | `kernel/sched.c:26` | `static void sched_tick_audio(void *ctx)` |
| `sched_tick_desktop` | function | `kernel/sched.c:32` | `static void sched_tick_desktop(void *ctx)` |
| `sched_tick_usb` | function | `kernel/sched.c:43` | `static void sched_tick_usb(void *ctx)` |
| `schedtop_report` | function | `kernel/sched.c:563` | `void schedtop_report(void)` |
| `schedule` | function | `kernel/sched.c:2147` | `* that keeps schedule()'s own rbp runs the caller's frame accesses  * (locals, leave/ret) on the ...` |
| `schedule` | function | `kernel/sched.c:2154` | `void schedule(void)` |
| `seccomp_allow_one` | function | `kernel/sched.c:964` | `int seccomp_allow_one(int pid, int n)` |
| `seccomp_denied` | function | `kernel/sched.c:971` | `int seccomp_denied(int pid, int n)` |
| `seccomp_deny_one` | function | `kernel/sched.c:957` | `int seccomp_deny_one(int pid, int n)` |
| `shares` | function | `kernel/sched.c:2595` | `* thread on another CPU kept its writable translation and wrote straight * into frames the child now shares (the...` |
| `shell_nchildren` | function | `kernel/sched.c:3298` | `int shell_nchildren(void)` |
| `shell_reap_nb` | function | `kernel/sched.c:3272` | `int shell_reap_nb(int *pid_out, int *code_out)` |
| `shell_reap_one` | function | `kernel/sched.c:3286` | `int shell_reap_one(int pid, int *code_out)` |
| `slot` | function | `kernel/sched.c:567` | `* must not eat a quarter of a 16 KB slot (see the stack discipline * contract in CLAUDE.md). Fail-closed on OOM. */...` |
| `smp_any_ap_idle` | function | `kernel/sched.c:1146` | `static int smp_any_ap_idle(void)` |
| `smp_ap_idle_loop` | function | `kernel/sched.c:1042` | `void smp_ap_idle_loop(void)` |
| `smp_claim_thread_v` | function | `kernel/sched.c:996` | `static int smp_claim_thread_v(int vm_only)` |
| `smp_try_claim_hint` | function | `kernel/sched.c:980` | `static int smp_try_claim_hint(int pid, int vm_only)` |
| `stop_row` | struct | `kernel/sched.c:564` | `` |
| `stub` | function | `kernel/sched.c:650` | `* gdb stub (`make gdb`, then `target remote :1234` from the host). These  * helpers are the seria...` |
| `sys_ticks` | function | `kernel/sched.c:627` | `* sys_ticks (PIT 100 Hz on the BSP, broadcast as IPIs to APs);` |
| `syscall` | function | `kernel/sched.c:1320` | `* outgoing syscall (see sched_rearm_kgs). Without * this the next entry swapgs puts garbage under GS * and the pid...` |
| `timer_tick` | function | `kernel/sched.c:3357` | `void timer_tick(void)` |
| `trap_frame_t` | struct | `kernel/sched.c:729` | `` |
| `tss_init` | function | `kernel/sched.c:838` | `static void tss_init(void)` |
| `tss_init_ap` | function | `kernel/sched.c:870` | `void tss_init_ap(int cpu)` |
| `tss_write_desc` | function | `kernel/sched.c:821` | `static void tss_write_desc(int cpu)` |
| `user_trampoline` | function | `kernel/sched.c:66` | `extern void user_trampoline(void);` |
| `vma_ctx_alloc` | function | `kernel/sched.c:342` | `vma_ctx_t *vma_ctx_alloc(void)` |
| `vma_ctx_copy` | function | `kernel/sched.c:371` | `static vma_ctx_t *vma_ctx_copy(vma_ctx_t *src)` |
| `vma_ctx_free` | function | `kernel/sched.c:352` | `void vma_ctx_free(vma_ctx_t *c)` |
| `vma_load_proc` | function | `kernel/sched.c:458` | `static void vma_load_proc(proc_t *p)` |
| `vma_owned` | function | `kernel/sched.c:446` | `static int vma_owned(proc_t *p)` |
| `vma_save_proc` | function | `kernel/sched.c:454` | `static void vma_save_proc(proc_t *p)` |
| `waitpid_has_child` | function | `kernel/sched.c:3241` | `static int waitpid_has_child(int pid)` |
| `waitpid_scan` | function | `kernel/sched.c:3203` | `static int waitpid_scan(int pid, int *found)` |
| `yield` | function | `kernel/sched.c:2235` | `void yield(void)` |
| `zeroed` | function | `kernel/sched.c:3433` | `* still zeroed (kmemset happens inside idt_init) faults through a * null gate. Handlers for 32/33/44 are safe...` |
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
| `HTTPD_IO_CHUNK` | macro | `kernel/shell.c:2575` | `#define HTTPD_IO_CHUNK` |
| `HTTPD_REQ_CAP` | macro | `kernel/shell.c:2574` | `#define HTTPD_REQ_CAP` |
| `PIPE_HOP_MAX` | macro | `kernel/shell.c:4178` | `#define PIPE_HOP_MAX` |
| `QEMU_PM_PORT` | macro | `kernel/shell.c:1034` | `#define QEMU_PM_PORT` |
| `SHELL_BUILTIN_COUNT` | macro | `kernel/shell.c:233` | `#define SHELL_BUILTIN_COUNT` |
| `SHELL_CVM_INTERP` | macro | `kernel/shell.c:54` | `#define SHELL_CVM_INTERP` |
| `SHELL_HIST_MAX` | macro | `kernel/shell.c:99` | `#define SHELL_HIST_MAX` |
| `SHELL_LS_CAP` | macro | `kernel/shell.c:2832` | `#define SHELL_LS_CAP` |
| `SHELL_RUN_DIRS` | macro | `kernel/shell.c:73` | `#define SHELL_RUN_DIRS` |
| `ShellRunDir` | struct | `kernel/shell.c:62` | `` |
| `VMA` | function | `kernel/shell.c:2219` | `* plus the live VMA (mmap) tree. The walk is bounded (64-deep explicit  * stack, 128 regions prin...` |
| `XXH_STATIC_LINKING_ONLY` | macro | `kernel/shell.c:26` | `#define XXH_STATIC_LINKING_ONLY` |
| `code` | function | `kernel/shell.c:1413` | `* the last exit code (130 when interrupted). */ static int shell_wait_fg(int *pids, int n, int ki...` |
| `context` | function | `kernel/shell.c:1706` | `* ISR context (which corrupts the running program's state) or * nesting a second foreground run inside the wait. */...` |
| `desktop_flag` | function | `kernel/shell.c:1567` | `static void desktop_flag(const char *name)` |
| `desktop_flag_on` | function | `kernel/shell.c:1577` | `static int desktop_flag_on(const char *name)` |
| `desktop_path` | function | `kernel/shell.c:1558` | `static void desktop_path(const char *name, char *dst, unsigned cap)` |
| `desktop_srv_alive` | function | `kernel/shell.c:1599` | `static int desktop_srv_alive(void)` |
| `desktop_unflag` | function | `kernel/shell.c:849` | `static void desktop_unflag(const char *name);` |
| `driver` | function | `kernel/shell.c:3342` | `* stream through the fat: VFS driver ("img:fatpath" per open,      * registered at boot beside me...` |
| `etrel_path_trusted` | function | `kernel/shell.c:1124` | `static int etrel_path_trusted(const char *full)` |
| `flows` | function | `kernel/shell.c:1591` | `* and external flows (make wl) set it themselves. */ static void desktop_unflag(const char *name)` |
| `frame` | function | `kernel/shell.c:3799` | `* not live in this frame (stack discipline, CLAUDE.md). */ struct ps_row *snap = (struct ps_row...` |
| `gfx_parse_int` | function | `kernel/shell.c:1752` | `static int gfx_parse_int(const char *s, int *out)` |
| `gfx_read_palette` | function | `kernel/shell.c:1772` | `static void gfx_read_palette(unsigned char pal[768])` |
| `job_row` | struct | `kernel/shell.c:2090` | `` |
| `line` | function | `kernel/shell.c:447` | `* to the live line (handled by the caller resetting shell_hist_idx). */ static void shell_hist_na...` |
| `outw_port` | function | `kernel/shell.c:1030` | `static inline void outw_port(unsigned short port, unsigned short val)` |
| `ps_row` | struct | `kernel/shell.c:3797` | `` |
| `root` | function | `kernel/shell.c:666` | `* MiniFS root (where the big ELFs live under bare names), * and only the highest-priority non-empty tier is kept. An...` |
| `shell_cmd_desktop` | function | `kernel/shell.c:1615` | `static void shell_cmd_desktop(int argc, char **argv)` |
| `shell_cmd_gdb` | function | `kernel/shell.c:2413` | `static void shell_cmd_gdb(int argc, char **argv)` |
| `shell_cmd_gfx` | function | `kernel/shell.c:1779` | `static void shell_cmd_gfx(int argc, char **argv)` |
| `shell_cmd_hash` | function | `kernel/shell.c:2456` | `static void shell_cmd_hash(int argc, char **argv)` |
| `shell_cmd_jobs` | function | `kernel/shell.c:2089` | `static void shell_cmd_jobs(void)` |
| `shell_cmd_kill` | function | `kernel/shell.c:2163` | `static void shell_cmd_kill(int argc, char **argv)` |
| `shell_cmd_mem` | function | `kernel/shell.c:2186` | `static void shell_cmd_mem(void)` |
| `shell_cmd_mrun` | function | `kernel/shell.c:1467` | `static void shell_cmd_mrun(int argc, char **argv)` |
| `shell_cmd_poweroff` | function | `kernel/shell.c:1036` | `static void shell_cmd_poweroff(void)` |
| `shell_cmd_wait` | function | `kernel/shell.c:2128` | `static void shell_cmd_wait(int argc, char **argv)` |
| `shell_cmd_wm` | function | `kernel/shell.c:1931` | `static void shell_cmd_wm(int argc, char **argv)` |
| `shell_complete_minifs_arg` | function | `kernel/shell.c:272` | `static void shell_complete_minifs_arg(const char *word, unsigned long wlen,                      ...` |
| `shell_complete_replace` | function | `kernel/shell.c:251` | `static void shell_complete_replace(char *buf, int size, int *pos,                                ...` |
| `shell_complete_tier` | function | `kernel/shell.c:239` | `static int shell_complete_tier(const char *nm)` |
| `shell_cross_cat` | function | `kernel/shell.c:2874` | `static void shell_cross_cat(const char *drv, const char *imgarg,                             cons...` |
| `shell_cross_ls` | function | `kernel/shell.c:2833` | `static void shell_cross_ls(const char *drv, const char *imgarg,                            const ...` |
| `shell_exec_builtin` | function | `kernel/shell.c:2916` | `void shell_exec_builtin(int argc, char **argv)` |
| `shell_file_is_real` | function | `kernel/shell.c:1070` | `static int shell_file_is_real(const char *resolved)` |
| `shell_focus_park` | function | `kernel/shell.c:117` | `void shell_focus_park(void)` |
| `shell_focus_restore` | function | `kernel/shell.c:122` | `void shell_focus_restore(void)` |
| `shell_has_child` | function | `kernel/shell.c:2118` | `static int shell_has_child(int pid)` |
| `shell_hist_newest_match` | function | `kernel/shell.c:430` | `static int shell_hist_newest_match(const char *prefix, unsigned long plen)` |
| `shell_hist_show` | function | `kernel/shell.c:347` | `static void shell_hist_show(char *buf, int size, int *pos, const char *text)` |
| `shell_httpd_one` | function | `kernel/shell.c:2581` | `static void shell_httpd_one(int child, const char *root)` |
| `shell_httpd_serve` | function | `kernel/shell.c:2666` | `static void shell_httpd_serve(unsigned short port, const char *root,         int max_conn)` |
| `shell_is_pipe_tok` | function | `kernel/shell.c:4180` | `static int shell_is_pipe_tok(const char *a)` |
| `shell_line_backspace` | function | `kernel/shell.c:391` | `static void shell_line_backspace(char *buf, int size, int *pos)` |
| `shell_line_delete` | function | `kernel/shell.c:399` | `static void shell_line_delete(char *buf, int size, int *pos)` |
| `shell_line_insert` | function | `kernel/shell.c:382` | `static void shell_line_insert(char *buf, int size, int *pos, char c)` |
| `shell_line_kill_front` | function | `kernel/shell.c:406` | `static void shell_line_kill_front(char *buf, int size, int *pos)` |
| `shell_line_kill_tail` | function | `kernel/shell.c:413` | `static void shell_line_kill_tail(char *buf, int size, int *pos)` |
| `shell_line_kill_word` | function | `kernel/shell.c:418` | `static void shell_line_kill_word(char *buf, int size, int *pos)` |
| `shell_line_repaint` | function | `kernel/shell.c:369` | `static void shell_line_repaint(char *buf, int size, int pos)` |
| `shell_load` | function | `kernel/shell.c:967` | `static int shell_load(const char *fname, char *progname_out, void **entry_out)` |
| `shell_name_base` | function | `kernel/shell.c:214` | `static const char *shell_name_base(const char *path)` |
| `shell_parse` | function | `kernel/shell.c:827` | `int shell_parse(char *line, char **argv, int max_args)` |
| `shell_parse_long` | function | `kernel/shell.c:2377` | `int shell_parse_long(const char *s, long *out)` |
| `shell_parse_pid` | function | `kernel/shell.c:2398` | `int shell_parse_pid(const char *s, int min_pid, int *out)` |
| `shell_parse_u64` | function | `kernel/shell.c:2361` | `static int shell_parse_u64(const char *s, unsigned long *out)` |
| `shell_parse_vol` | function | `kernel/shell.c:159` | `static int shell_parse_vol(const char *s, unsigned *out)` |
| `shell_prompt` | function | `kernel/shell.c:149` | `static void shell_prompt(void)` |
| `shell_queue_launch` | function | `kernel/shell.c:88` | `void shell_queue_launch(const char *cmd)` |
| `shell_read_elf_bytes` | function | `kernel/shell.c:1347` | `static int shell_read_elf_bytes(const char *name, unsigned char **out,                           ...` |
| `shell_readline` | function | `kernel/shell.c:339` | `static void shell_readline(void)` |
| `shell_readline_active` | function | `kernel/shell.c:116` | `int shell_readline_active(void)` |
| `shell_readline_buf` | function | `kernel/shell.c:185` | `void shell_readline_buf(char *buf, int size)` |
| `shell_readline_hist` | function | `kernel/shell.c:492` | `static void shell_readline_hist(char *buf, int size)` |
| `shell_resolve_arg` | function | `kernel/shell.c:2475` | `static int shell_resolve_arg(const char *cmd, const char *arg,                              const...` |
| `shell_resolve_run` | function | `kernel/shell.c:1082` | `static int shell_resolve_run(const char *name, char *out, unsigned cap)` |
| `shell_run` | function | `kernel/shell.c:895` | `void shell_run(void)` |
| `shell_run_any` | function | `kernel/shell.c:1679` | `int shell_run_any(const char *name, int argc, char **argv)` |
| `shell_run_bg` | function | `kernel/shell.c:1515` | `static void shell_run_bg(const char *name, int argc, char **argv)` |
| `shell_run_cvm` | function | `kernel/shell.c:1267` | `static int shell_run_cvm(const char *full, int argc, char **argv)` |
| `shell_run_dir_for` | function | `kernel/shell.c:1052` | `static const ShellRunDir *shell_run_dir_for(const char *name)` |
| `shell_run_elf_buf_path` | function | `kernel/shell.c:1164` | `static int shell_run_elf_buf_path(const char *data, unsigned size, int argc,                     ...` |
| `shell_run_elf_file` | function | `kernel/shell.c:1197` | `static int shell_run_elf_file(const char *full, int argc, char **argv)` |
| `shell_run_elf_minifs` | function | `kernel/shell.c:1210` | `static int shell_run_elf_minifs(const char *name, int argc, char **argv)` |
| `shell_run_file` | function | `kernel/shell.c:1303` | `static int shell_run_file(const char *name, int argc, char **argv)` |
| `shell_run_init` | function | `kernel/shell.c:856` | `static void shell_run_init(void)` |
| `shell_run_pipeline` | function | `kernel/shell.c:152` | `static int shell_run_pipeline(char **argv, int argc, const char *redir_path, int redir_append, int redirected);` |
| `shell_run_stage` | function | `kernel/shell.c:4219` | `static char *shell_run_stage(char **sargv, int sargc,         const char *input, unsigned long in...` |
| `stdout` | function | `kernel/shell.c:4168` | `* the pipe exactly like stdout (`2>` is an alias of `>`). * Per-stage `exit code:` lines report to the console...` |
| `terminal` | function | `kernel/shell.c:2991` | `* sequence clears serial consoles and is swallowed without * garbage by the framebuffer terminal (vedit pattern). */...` |
| `text` | function | `kernel/shell.c:595` | `* swallowed the sequence as plain text ("5~" in the * line) and the history was unreachable from the * prompt. */...` |
| `this` | function | `kernel/shell.c:1545` | `* boot into the tiled Wayland desktop: every NK app started after * this (paint, vedit, file, nuklear, doomedit...` |
| `to` | function | `kernel/shell.c:2292` | `* actually trap to (brk/mmap/munmap/mprotect) and says so up front. */ static void shell_cmd_trac...` |
| `tree` | function | `kernel/shell.c:2076` | `* tree (mmap-heavy jobs stay best-effort), legacy blocking `run` ignores  * Ctrl+C (it never poll...` |
| `window` | function | `kernel/shell.c:1340` | `* window (proc_spawn_elf) and waits for all of them. The 100 Hz timer * preempts the BSP across the READY set, so...` |
| `spawn_backup` | function | `kernel/spawn.c:11` | `int spawn_backup(spawn_ctx_t *ctx)` |
| `spawn_copy_argv` | function | `kernel/spawn.c:99` | `char **spawn_copy_argv(int argc, const char **uargv)` |
| `spawn_execute` | function | `kernel/spawn.c:268` | `int spawn_execute(const char *resolved, const char *redirect,                   unsigned char *da...` |
| `spawn_free_argv` | function | `kernel/spawn.c:87` | `void spawn_free_argv(char **kargv, int argc)` |
| `spawn_load_image` | function | `kernel/spawn.c:161` | `unsigned char *spawn_load_image(const char *resolved, unsigned *size_out)` |
| `spawn_restore` | function | `kernel/spawn.c:38` | `void spawn_restore(spawn_ctx_t *ctx)` |
| `spawn_run_exec` | function | `kernel/spawn.c:222` | `static int spawn_run_exec(const char *resolved, const char *redirect,                            ...` |
| `spawn_run_rel` | function | `kernel/spawn.c:196` | `static int spawn_run_rel(const char *resolved, const char *redirect,                          uns...` |
| `spawn_validate_argv` | function | `kernel/spawn.c:143` | `int spawn_validate_argv(int argc, const char **uargv)` |
| `NO_LOOP_IDIOM` | macro | `kernel/string.c:68` | `#define NO_LOOP_IDIOM` |
| `katol` | function | `kernel/string.c:120` | `long katol(const char *s)` |
| `kmemcmp` | function | `kernel/string.c:86` | `int kmemcmp(const void *a, const void *b, unsigned long n)` |
| `kmemcpy` | function | `kernel/string.c:73` | `NO_LOOP_IDIOM void *kmemcpy(void *dst, const void *src, unsigned long n)` |
| `kmemmove` | function | `kernel/string.c:92` | `NO_LOOP_IDIOM void *kmemmove(void *dst, const void *src, unsigned long n)` |
| `kmemset` | function | `kernel/string.c:80` | `NO_LOOP_IDIOM void *kmemset(void *dst, int c, unsigned long n)` |
| `kstrchr` | function | `kernel/string.c:53` | `char *kstrchr(const char *s, int c)` |
| `kstrcmp` | function | `kernel/string.c:43` | `int kstrcmp(const char *a, const char *b)` |
| `kstrcpy` | function | `kernel/string.c:23` | `char *kstrcpy(char *dst, const char *src)` |
| `kstrlen` | function | `kernel/string.c:17` | `unsigned long kstrlen(const char *s)` |
| `kstrncat` | function | `kernel/string.c:35` | `char *kstrncat(char *dst, const char *src, unsigned long n)` |
| `kstrncmp` | function | `kernel/string.c:48` | `int kstrncmp(const char *a, const char *b, unsigned long n)` |
| `kstrncpy` | function | `kernel/string.c:29` | `char *kstrncpy(char *dst, const char *src, unsigned long n)` |
| `kstrstr` | function | `kernel/string.c:58` | `char *kstrstr(const char *hay, const char *ndl)` |
| `memcmp` | function | `kernel/string.c:116` | `int memcmp(const void *a, const void *b, unsigned long n)` |
| `memcpy` | function | `kernel/string.c:104` | `void *memcpy(void *dst, const void *src, unsigned long n)` |
| `memmove` | function | `kernel/string.c:108` | `void *memmove(void *dst, const void *src, unsigned long n)` |
| `memset` | function | `kernel/string.c:112` | `void *memset(void *dst, int c, unsigned long n)` |
| `k_register_process` | function | `kernel/symtab.c:57` | `void k_register_process(const char *name, void *proc_entry)` |

Next: [SYMBOLS_p10.md](SYMBOLS_p10.md)
