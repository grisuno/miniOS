# Symbols (page 5 of 28)
Previous: [SYMBOLS_p4.md](SYMBOLS_p4.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `PTE_DEMAND_WRITE` | macro | `headers/kernel.h:800` | `#define PTE_DEMAND_WRITE` |
| `RAMDISK_FNAME_LEN` | macro | `headers/kernel.h:279` | `#define RAMDISK_FNAME_LEN` |
| `RAMDISK_FNAME_LEN` | function | `headers/kernel.h:295` | `* RAMDISK_FNAME_LEN (fs_resolve guarantees it);` |
| `RAMDISK_MAX_FILES` | macro | `headers/kernel.h:269` | `#define RAMDISK_MAX_FILES` |
| `RDFile` | struct | `headers/kernel.h:281` | `` |
| `RD_DATA_MAX` | macro | `headers/kernel.h:305` | `#define RD_DATA_MAX` |
| `SYS_KSTK_BASE` | macro | `headers/kernel.h:202` | `#define SYS_KSTK_BASE` |
| `SYS_KSTK_TOP` | macro | `headers/kernel.h:201` | `#define SYS_KSTK_TOP` |
| `USER_BRK_END` | macro | `headers/kernel.h:190` | `#define USER_BRK_END` |
| `USER_HEAP_CEIL` | macro | `headers/kernel.h:764` | `#define USER_HEAP_CEIL` |
| `USER_LOAD_BASE` | macro | `headers/kernel.h:185` | `#define USER_LOAD_BASE` |
| `USER_LOAD_END` | macro | `headers/kernel.h:186` | `#define USER_LOAD_END` |
| `USER_STACK_BASE` | macro | `headers/kernel.h:189` | `#define USER_STACK_BASE` |
| `USER_STACK_SIZE` | macro | `headers/kernel.h:187` | `#define USER_STACK_SIZE` |
| `USER_STACK_TOP` | macro | `headers/kernel.h:188` | `#define USER_STACK_TOP` |
| `VFS_DRIVER_LEN` | macro | `headers/kernel.h:421` | `#define VFS_DRIVER_LEN` |
| `VFS_MAX_MOUNTS` | macro | `headers/kernel.h:419` | `#define VFS_MAX_MOUNTS` |
| `VFS_NAME_MAX` | macro | `headers/kernel.h:382` | `#define VFS_NAME_MAX` |
| `VFS_PREFIX_LEN` | macro | `headers/kernel.h:420` | `#define VFS_PREFIX_LEN` |
| `VGA_BASE` | macro | `headers/kernel.h:90` | `#define VGA_BASE` |
| `VGA_COLS` | macro | `headers/kernel.h:91` | `#define VGA_COLS` |
| `VGA_ROWS` | macro | `headers/kernel.h:92` | `#define VGA_ROWS` |
| `block_init` | function | `headers/kernel.h:940` | `void block_init(void);` |
| `block_read` | function | `headers/kernel.h:941` | `int block_read(unsigned int block_num, void *buf);` |
| `block_read_multi` | function | `headers/kernel.h:943` | `int block_read_multi(unsigned int block_num, unsigned int count, void *buf);` |
| `block_total` | function | `headers/kernel.h:945` | `unsigned int block_total(void);` |
| `block_write` | function | `headers/kernel.h:942` | `int block_write(unsigned int block_num, const void *buf);` |
| `block_write_multi` | function | `headers/kernel.h:944` | `int block_write_multi(unsigned int block_num, unsigned int count, const void *buf);` |
| `bootlog_mark` | function | `headers/kernel.h:917` | `void bootlog_mark(const char *name);` |
| `bootlog_report` | function | `headers/kernel.h:918` | `void bootlog_report(void);` |
| `clip_clear` | function | `headers/kernel.h:613` | `void clip_clear(void);` |
| `clip_get` | function | `headers/kernel.h:612` | `int clip_get(char *out, unsigned long cap);` |
| `clip_len_get` | function | `headers/kernel.h:614` | `int clip_len_get(void);` |
| `clip_set` | function | `headers/kernel.h:611` | `int clip_set(const char *data, unsigned long len);` |
| `console_getc` | function | `headers/kernel.h:590` | `int console_getc(void);` |
| `console_lock` | variable | `headers/kernel.h:105` | `extern spinlock_t console_lock;` |
| `console_peek` | function | `headers/kernel.h:591` | `int console_peek(void);` |
| `console_stdin_active` | function | `headers/kernel.h:604` | `int console_stdin_active(void);` |
| `console_stdin_clear` | function | `headers/kernel.h:603` | `void console_stdin_clear(void);` |
| `console_stdin_push` | function | `headers/kernel.h:602` | `int console_stdin_push(const char *data, unsigned long len);` |
| `cow_drop_ref` | function | `headers/kernel.h:811` | `int cow_drop_ref(unsigned long phys);` |
| `cow_page_shared` | function | `headers/kernel.h:831` | `int cow_page_shared(unsigned long phys);` |
| `cow_release_window` | function | `headers/kernel.h:829` | `void cow_release_window(unsigned long cr3);` |
| `cow_resolve` | function | `headers/kernel.h:827` | `int cow_resolve(unsigned long cr3, unsigned long va);` |
| `cow_shared` | function | `headers/kernel.h:830` | `int cow_shared(void);` |
| `desktop_launch` | function | `headers/kernel.h:678` | `void desktop_launch(const char *cmd);` |
| `dlmalloc_calloc` | function | `headers/kernel.h:233` | `void *dlmalloc_calloc(unsigned long nmemb, unsigned long size);` |
| `dlmalloc_free` | function | `headers/kernel.h:232` | `void dlmalloc_free(void *ptr);` |
| `dlmalloc_init` | function | `headers/kernel.h:226` | `void dlmalloc_init(unsigned long size);` |
| `dlmalloc_malloc` | function | `headers/kernel.h:230` | `void *dlmalloc_malloc(unsigned long size);` |
| `dlmalloc_memalign` | function | `headers/kernel.h:231` | `void *dlmalloc_memalign(unsigned long align, unsigned long size);` |
| `dlmalloc_realloc` | function | `headers/kernel.h:234` | `void *dlmalloc_realloc(void *ptr, unsigned long size);` |
| `dlmalloc_usage` | function | `headers/kernel.h:236` | `void dlmalloc_usage(unsigned long *used, unsigned long *free_b, unsigned long *arena);` |
| `elf_load` | function | `headers/kernel.h:766` | `void *elf_load(void *data, unsigned size, void **base_out);` |
| `elf_wants_process` | function | `headers/kernel.h:768` | `int elf_wants_process(const void *data, unsigned size);` |
| `exec_exit_code` | variable | `headers/kernel.h:670` | `extern int exec_exit_code;` |
| `exec_return` | variable | `headers/kernel.h:669` | `extern kjmpbuf exec_return;` |
| `fault` | function | `headers/kernel.h:824` | `* fixes one write fault (0 = resume), cow_release_window drops a * dying window's shares ahead of pt_free_user. */...` |
| `fd_lock` | variable | `headers/kernel.h:864` | `extern spinlock_t fd_lock;` |
| `fd_lock` | function | `headers/kernel.h:889` | `* fd_lock (never nested, never held across yields);` |
| `file_operations` | type_alias | `headers/kernel.h:414` | `typedef vfs_ops_t file_operations;` |
| `fs_cwd` | variable | `headers/kernel.h:434` | `extern char fs_cwd[];` |
| `fs_dir_exists` | function | `headers/kernel.h:312` | `int fs_dir_exists(const char *dir);` |
| `fs_is_dir` | function | `headers/kernel.h:313` | `int fs_is_dir(const char *resolved);` |
| `fs_lock` | variable | `headers/kernel.h:891` | `extern spinlock_t fs_lock;` |
| `fs_rename` | function | `headers/kernel.h:524` | `int fs_rename(const char *oldr, const char *newr);` |
| `fs_resolve` | function | `headers/kernel.h:311` | `int fs_resolve(const char *path, char *out, unsigned cap);` |
| `g_brk` | variable | `headers/kernel.h:723` | `extern unsigned long g_brk;` |
| `g_brk_limit` | variable | `headers/kernel.h:724` | `extern unsigned long g_brk_limit;` |
| `ide_init` | function | `headers/kernel.h:931` | `void ide_init(void);` |
| `ide_present` | function | `headers/kernel.h:937` | `int ide_present(void);` |
| `ide_read_sector` | function | `headers/kernel.h:934` | `int ide_read_sector(unsigned int lba, void *buf);` |
| `ide_read_sectors` | function | `headers/kernel.h:932` | `int ide_read_sectors(unsigned int lba, unsigned int count, void *buf);` |
| `ide_total_sectors` | function | `headers/kernel.h:936` | `unsigned int ide_total_sectors(void);` |
| `ide_write_sector` | function | `headers/kernel.h:935` | `int ide_write_sector(unsigned int lba, const void *buf);` |
| `ide_write_sectors` | function | `headers/kernel.h:933` | `int ide_write_sectors(unsigned int lba, unsigned int count, const void *buf);` |
| `inb` | function | `headers/kernel.h:29` | `static inline unsigned char inb(unsigned short port)` |
| `insw` | function | `headers/kernel.h:47` | `static inline void insw(unsigned short port, unsigned short *buf,                         unsigne...` |
| `inw` | function | `headers/kernel.h:37` | `static inline unsigned short inw(unsigned short port)` |
| `k_exec_user` | function | `headers/kernel.h:657` | `int k_exec_user(void *entry, int argc, char **argv);` |
| `k_register_process` | function | `headers/kernel.h:649` | `void k_register_process(const char *name, void *proc_entry);` |
| `k_register_program` | function | `headers/kernel.h:648` | `void k_register_program(const char *name, prog_entry_t entry);` |
| `k_register_symbol` | function | `headers/kernel.h:650` | `void k_register_symbol(const char *name, void *addr);` |
| `k_run_on_stack` | function | `headers/kernel.h:662` | `int k_run_on_stack(void *stack_top, prog_entry_t entry, int argc, char **argv);` |
| `k_run_rel` | function | `headers/kernel.h:658` | `int k_run_rel(prog_entry_t entry, int argc, char **argv);` |
| `k_spawn` | function | `headers/kernel.h:647` | `int k_spawn(const char *name, int argc, char **argv);` |
| `k_user_fault_return` | function | `headers/kernel.h:948` | `void k_user_fault_return(void);` |
| `kallocator_init` | function | `headers/kernel.h:218` | `void kallocator_init(void);` |
| `katol` | function | `headers/kernel.h:557` | `long katol(const char *s);` |
| `kbd_available` | function | `headers/kernel.h:174` | `int kbd_available(void);` |
| `kbd_read` | function | `headers/kernel.h:173` | `int kbd_read(void);` |
| `kbd_reset_for_shell` | function | `headers/kernel.h:175` | `void kbd_reset_for_shell(void);` |
| `kcalloc` | function | `headers/kernel.h:216` | `void *kcalloc(unsigned long nmemb, unsigned long size);` |
| `kernel_end` | variable | `headers/kernel.h:894` | `extern unsigned long kernel_end;` |
| `kerrno` | variable | `headers/kernel.h:521` | `extern int kerrno;` |
| `kevent_create` | function | `headers/kernel.h:882` | `KFILE *kevent_create(unsigned long long initval, int semaphore);` |
| `kevent_read` | function | `headers/kernel.h:883` | `long kevent_read(KFILE *f, unsigned long long *out);` |
| `kevent_readable` | function | `headers/kernel.h:885` | `int kevent_readable(KFILE *f);` |
| `kevent_writable` | function | `headers/kernel.h:886` | `int kevent_writable(KFILE *f);` |
| `kevent_write` | function | `headers/kernel.h:884` | `long kevent_write(KFILE *f, unsigned long long v);` |
| `kexit` | function | `headers/kernel.h:659` | `void kexit(int code);` |
| `kfclose` | function | `headers/kernel.h:500` | `int kfclose(KFILE *f);` |
| `kfd_get` | function | `headers/kernel.h:865` | `KFILE *kfd_get(int fd);` |
| `kfd_override` | function | `headers/kernel.h:867` | `KFILE *kfd_override(int fd, KFILE *f);` |
| `kfd_poll_revents` | function | `headers/kernel.h:876` | `int kfd_poll_revents(int fd);` |
| `kfd_put` | function | `headers/kernel.h:866` | `void kfd_put(KFILE *f);` |
| `kfd_view` | struct | `headers/kernel.h:855` | `` |
| `kfflush` | function | `headers/kernel.h:534` | `int kfflush(KFILE *f);` |
| `kfgetc` | function | `headers/kernel.h:525` | `int kfgetc(KFILE *f);` |
| `kfgets` | function | `headers/kernel.h:526` | `char *kfgets(char *buf, int size, KFILE *f);` |
| `kfile_stderr` | function | `headers/kernel.h:542` | `KFILE *kfile_stderr(void);` |
| `kfile_stdin` | function | `headers/kernel.h:540` | `KFILE *kfile_stdin(void);` |
| `kfile_stdout` | function | `headers/kernel.h:541` | `KFILE *kfile_stdout(void);` |
| `kfopen` | function | `headers/kernel.h:495` | `KFILE *kfopen(const char *path, const char *mode);` |
| `kfopen_dir` | function | `headers/kernel.h:499` | `KFILE *kfopen_dir(const char *resolved);` |
| `kfprintf` | function | `headers/kernel.h:561` | `int kfprintf(KFILE *f, const char *fmt, ...);` |
| `kfputc` | function | `headers/kernel.h:533` | `int kfputc(int c, KFILE *f);` |
| `kfputs` | function | `headers/kernel.h:532` | `int kfputs(const char *s, KFILE *f);` |
| `kfread` | function | `headers/kernel.h:528` | `unsigned long kfread(void *ptr, unsigned long size, unsigned long nmemb, KFILE *f);` |
| `kfree` | function | `headers/kernel.h:215` | `void kfree(void *ptr);` |
| `kfree_aligned` | function | `headers/kernel.h:222` | `void kfree_aligned(void *ptr);` |
| `kfseek` | function | `headers/kernel.h:530` | `int kfseek(KFILE *f, long offset, int whence);` |
| `kftell` | function | `headers/kernel.h:531` | `long kftell(KFILE *f);` |
| `kfungetc` | function | `headers/kernel.h:527` | `int kfungetc(int c, KFILE *f);` |
| `kfwrite` | function | `headers/kernel.h:529` | `unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long nmemb, KFILE *f);` |
| `kheap_size` | variable | `headers/kernel.h:229` | `extern unsigned long kheap_size;` |
| `kjmpbuf` | struct | `headers/kernel.h:666` | `` |
| `klog` | function | `headers/kernel.h:578` | `void klog(log_level_t level, log_subsystem_t subsys, const char *fmt, ...);` |
| `klog_disable` | function | `headers/kernel.h:584` | `void klog_disable(void);` |
| `klog_enable` | function | `headers/kernel.h:585` | `void klog_enable(void);` |
| `klog_hexdump` | function | `headers/kernel.h:580` | `void klog_hexdump(log_level_t level, log_subsystem_t subsys, const void *data, unsigned long len, const char *label);` |
| `klog_set_level` | function | `headers/kernel.h:582` | `void klog_set_level(log_level_t level);` |
| `klog_set_subsys_level` | function | `headers/kernel.h:583` | `void klog_set_subsys_level(log_subsystem_t subsys, log_level_t level);` |
| `klongjmp` | function | `headers/kernel.h:668` | `void klongjmp(void *buf, int val) __attribute__((noreturn));` |
| `kmalloc` | function | `headers/kernel.h:213` | `void *kmalloc(unsigned long size);` |
| `kmalloc_aligned` | function | `headers/kernel.h:219` | `void *kmalloc_aligned(unsigned long size, unsigned long align);` |
| `kmalloc_fail_after` | variable | `headers/kernel.h:214` | `extern long kmalloc_fail_after;` |
| `kmalloc_page` | function | `headers/kernel.h:221` | `void *kmalloc_page(void);` |
| `kmemcmp` | function | `headers/kernel.h:555` | `int kmemcmp(const void *a, const void *b, unsigned long n);` |
| `kmemcpy` | function | `headers/kernel.h:553` | `void *kmemcpy(void *dst, const void *src, unsigned long n);` |
| `kmemmove` | function | `headers/kernel.h:556` | `void *kmemmove(void *dst, const void *src, unsigned long n);` |
| `kmemset` | function | `headers/kernel.h:554` | `void *kmemset(void *dst, int c, unsigned long n);` |
| `kmm_make_uncached` | function | `headers/kernel.h:819` | `int kmm_make_uncached(unsigned long phys, unsigned long len);` |
| `kpipe_empty_wopen` | function | `headers/kernel.h:869` | `int kpipe_empty_wopen(KFILE *f);` |
| `kpipe_is_write_end` | function | `headers/kernel.h:870` | `int kpipe_is_write_end(KFILE *f);` |
| `kpipe_pair` | function | `headers/kernel.h:868` | `int kpipe_pair(KFILE **rend_out, KFILE **wend_out);` |
| `kpipe_state` | function | `headers/kernel.h:873` | `int kpipe_state(KFILE *f, unsigned *avail, unsigned *space, int *wopen, int *ropen);` |
| `kprintf` | function | `headers/kernel.h:560` | `int kprintf(const char *fmt, ...);` |
| `kprog_count` | variable | `headers/kernel.h:642` | `extern int kprog_count;` |
| `kprog_lookup` | function | `headers/kernel.h:645` | `KProg *kprog_lookup(const char *name);` |
| `kprog_slot` | function | `headers/kernel.h:644` | `KProg *kprog_slot(const char *name);` |
| `kprog_table` | variable | `headers/kernel.h:641` | `extern KProg kprog_table[];` |
| `krealloc` | function | `headers/kernel.h:217` | `void *krealloc(void *ptr, unsigned long size);` |
| `krewind` | function | `headers/kernel.h:535` | `void krewind(KFILE *f);` |
| `ksetjmp` | function | `headers/kernel.h:667` | `int ksetjmp(void *buf) __attribute__((returns_twice));` |
| `ksnprintf` | function | `headers/kernel.h:563` | `int ksnprintf(char *buf, unsigned long size, const char *fmt, ...);` |
| `ksprintf` | function | `headers/kernel.h:562` | `int ksprintf(char *buf, const char *fmt, ...);` |
| `kstderr` | variable | `headers/kernel.h:539` | `extern KFILE *kstderr;` |
| `kstdin` | variable | `headers/kernel.h:537` | `extern KFILE *kstdin;` |
| `kstdout` | variable | `headers/kernel.h:538` | `extern KFILE *kstdout;` |
| `kstrchr` | function | `headers/kernel.h:551` | `char *kstrchr(const char *s, int c);` |
| `kstrcmp` | function | `headers/kernel.h:549` | `int kstrcmp(const char *a, const char *b);` |
| `kstrcpy` | function | `headers/kernel.h:546` | `char *kstrcpy(char *dst, const char *src);` |
| `kstrlen` | function | `headers/kernel.h:545` | `unsigned long kstrlen(const char *s);` |
| `kstrncat` | function | `headers/kernel.h:548` | `char *kstrncat(char *dst, const char *src, unsigned long n);` |
| `kstrncmp` | function | `headers/kernel.h:550` | `int kstrncmp(const char *a, const char *b, unsigned long n);` |
| `kstrncpy` | function | `headers/kernel.h:547` | `char *kstrncpy(char *dst, const char *src, unsigned long n);` |
| `kstrstr` | function | `headers/kernel.h:552` | `char *kstrstr(const char *hay, const char *ndl);` |
| `ksym_count` | variable | `headers/kernel.h:640` | `extern int ksym_count;` |
| `ksym_resolve` | function | `headers/kernel.h:646` | `void *ksym_resolve(const char *name);` |
| `ksym_table` | variable | `headers/kernel.h:639` | `extern KSym ksym_table[];` |
| `ksyscall` | function | `headers/kernel.h:838` | `long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);` |
| `ktime_ms` | function | `headers/kernel.h:25` | `unsigned long ktime_ms(void);` |
| `ktime_us` | function | `headers/kernel.h:913` | `unsigned long ktime_us(void);` |
| `ldso_bind_into` | function | `headers/kernel.h:778` | `int ldso_bind_into(void *data, unsigned size, unsigned long base, unsigned long cr3, vma_ctx_t *vma);` |
| `ldso_pseudo_read` | function | `headers/kernel.h:781` | `int ldso_pseudo_read(int ino, void *dst, unsigned long off, unsigned len);` |
| `ldso_pseudo_stat` | function | `headers/kernel.h:780` | `int ldso_pseudo_stat(int ino, unsigned long *size_out);` |
| `load_exec_elf` | function | `headers/kernel.h:767` | `void *load_exec_elf(void *data, unsigned size);` |
| `load_exec_elf_into` | function | `headers/kernel.h:769` | `void *load_exec_elf_into(void *data, unsigned size, unsigned long cr3, unsigned long *brk_out, unsigned long *base_out);` |
| `minfo_sleep_init` | function | `headers/kernel.h:116` | `void minfo_sleep_init(int tick_ok);` |
| `minfo_tick_wake` | function | `headers/kernel.h:117` | `void minfo_tick_wake(void *ctx);` |
| `minifs_mkdir_p` | function | `headers/kernel.h:433` | `int minifs_mkdir_p(const char *resolved);` |
| `mm_anon_fault` | function | `headers/kernel.h:808` | `int mm_anon_fault(unsigned long cr3, unsigned long va, int write);` |
| `mm_anon_release` | function | `headers/kernel.h:810` | `void mm_anon_release(unsigned long cr3, unsigned long base, unsigned long len);` |
| `mm_anon_reserve` | function | `headers/kernel.h:806` | `int mm_anon_reserve(unsigned long cr3, unsigned long base, unsigned long len, unsigned long prot);` |
| `mm_copy_user_page` | function | `headers/kernel.h:820` | `int mm_copy_user_page(unsigned long dst_cr3, unsigned long src_cr3, unsigned long va);` |
| `mm_demand_pte` | function | `headers/kernel.h:805` | `unsigned long mm_demand_pte(unsigned long prot);` |
| `mm_file_break` | function | `headers/kernel.h:787` | `int mm_file_break(unsigned long cr3, unsigned long va);` |
| `mm_file_fault` | function | `headers/kernel.h:786` | `int mm_file_fault(unsigned long cr3, unsigned long va);` |
| `mm_file_page_phys` | function | `headers/kernel.h:788` | `unsigned long mm_file_page_phys(unsigned long cr3, unsigned long va);` |
| `mm_file_range_release` | function | `headers/kernel.h:789` | `void mm_file_range_release(unsigned long cr3, unsigned long base, unsigned long len, int ino, unsigned long off, int...` |
| `mm_setup_protections` | function | `headers/kernel.h:712` | `void mm_setup_protections(void);` |
| `mm_user_ensure_page` | function | `headers/kernel.h:783` | `int mm_user_ensure_page(unsigned long cr3, unsigned long va);` |
| `mm_user_map_page` | function | `headers/kernel.h:784` | `int mm_user_map_page(unsigned long cr3, unsigned long va, unsigned long phys, int write, int exec);` |
| `mm_user_pte_update` | function | `headers/kernel.h:715` | `void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3);` |
| `mm_user_set_exec` | function | `headers/kernel.h:716` | `void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3);` |
| `name` | type_alias | `headers/kernel.h:383` | `typedef struct vfs_dirent { char name[VFS_NAME_MAX + 1];` |
| `outb` | function | `headers/kernel.h:26` | `static inline void outb(unsigned short port, unsigned char val)` |
| `outsw` | function | `headers/kernel.h:54` | `static inline void outsw(unsigned short port, const unsigned short *buf,                         ...` |
| `outw` | function | `headers/kernel.h:34` | `static inline void outw(unsigned short port, unsigned short val)` |
| `panic_screen` | function | `headers/kernel.h:607` | `void panic_screen(unsigned long vector, unsigned long err, unsigned long rip, unsigned long rsp, unsigned long rbp...` |
| `pcspk_get_volume` | function | `headers/kernel.h:925` | `unsigned pcspk_get_volume(void);` |
| `pcspk_init` | function | `headers/kernel.h:921` | `void pcspk_init(void);` |
| `pcspk_off` | function | `headers/kernel.h:923` | `void pcspk_off(void);` |
| `pcspk_set_volume` | function | `headers/kernel.h:924` | `void pcspk_set_volume(unsigned volume);` |
| `pcspk_tone` | function | `headers/kernel.h:922` | `void pcspk_tone(unsigned freq);` |
| `pt_clone_user_empty` | function | `headers/kernel.h:782` | `unsigned long pt_clone_user_empty(void);` |
| `pt_page_alloc` | function | `headers/kernel.h:713` | `void *pt_page_alloc(void);` |
| `pt_page_free` | function | `headers/kernel.h:714` | `void pt_page_free(void *ptr);` |
| `pt_page_owned` | function | `headers/kernel.h:809` | `int pt_page_owned(unsigned long phys);` |
| `ramdisk_count` | function | `headers/kernel.h:300` | `int ramdisk_count(void);` |
| `ramdisk_create` | function | `headers/kernel.h:291` | `RDFile *ramdisk_create(const char *name, unsigned size);` |
| `ramdisk_delete` | function | `headers/kernel.h:293` | `int ramdisk_delete(RDFile *f);` |
| `ramdisk_end` | variable | `headers/kernel.h:896` | `extern char ramdisk_end[];` |
| `ramdisk_file_name` | function | `headers/kernel.h:301` | `const char *ramdisk_file_name(int idx);` |
| `ramdisk_init` | function | `headers/kernel.h:287` | `void ramdisk_init(void);` |
| `ramdisk_list` | function | `headers/kernel.h:298` | `int ramdisk_list(RDFile **out, int max);` |
| `ramdisk_open` | function | `headers/kernel.h:288` | `RDFile *ramdisk_open(const char *name);` |
| `ramdisk_read` | function | `headers/kernel.h:289` | `int ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len);` |
| `ramdisk_rename` | function | `headers/kernel.h:297` | `int ramdisk_rename(const char *oldname, const char *newname);` |
| `ramdisk_resize` | function | `headers/kernel.h:292` | `int ramdisk_resize(RDFile *f, unsigned newsize);` |
| `ramdisk_setup_from` | function | `headers/kernel.h:299` | `void ramdisk_setup_from(void *data, unsigned size);` |
| `ramdisk_size` | variable | `headers/kernel.h:897` | `extern char ramdisk_size[];` |
| `ramdisk_start` | variable | `headers/kernel.h:895` | `extern char ramdisk_start[];` |
| `ramdisk_usage` | function | `headers/kernel.h:303` | `void ramdisk_usage(unsigned *used, unsigned *cap, unsigned *max);` |
| `ramdisk_write` | function | `headers/kernel.h:290` | `int ramdisk_write(RDFile *f, const void *buf, unsigned offset, unsigned len);` |
| `redirect_active` | function | `headers/kernel.h:601` | `int redirect_active(void);` |
| `redirect_begin` | function | `headers/kernel.h:594` | `int redirect_begin(void);` |
| `redirect_commit` | function | `headers/kernel.h:595` | `int redirect_commit(const char *path, int append_mode);` |
| `redirect_discard` | function | `headers/kernel.h:600` | `void redirect_discard(void);` |
| `redirect_pending` | function | `headers/kernel.h:597` | `unsigned long redirect_pending(void);` |
| `redirect_resume` | function | `headers/kernel.h:593` | `void redirect_resume(int was);` |
| `redirect_suspend` | function | `headers/kernel.h:592` | `int redirect_suspend(void);` |
| `redirect_take` | function | `headers/kernel.h:596` | `char *redirect_take(unsigned long *len_out);` |
| `redirect_take_into` | function | `headers/kernel.h:598` | `unsigned long redirect_take_into(char *dst, unsigned long cap, unsigned long *len_out);` |
| `refused` | function | `headers/kernel.h:817` | `* refused (see kernel/mm/paging.c for the fail-closed list). */ unsigned long kmm_map_device(unsigned long phys...` |
| `register_libc_symbols` | function | `headers/kernel.h:654` | `void register_libc_symbols(void);` |
| `rtc_read_tod` | function | `headers/kernel.h:928` | `int rtc_read_tod(int *hour, int *min, int *sec);` |
| `sb_capture_row0` | function | `headers/kernel.h:121` | `void sb_capture_row0(void);` |
| `sb_get_char` | function | `headers/kernel.h:125` | `char sb_get_char(int row, int col);` |
| `sb_get_count` | function | `headers/kernel.h:123` | `int sb_get_count(void);` |
| `sb_get_head` | function | `headers/kernel.h:124` | `int sb_get_head(void);` |
| `sb_init` | function | `headers/kernel.h:120` | `void sb_init(void);` |
| `sb_reset` | function | `headers/kernel.h:122` | `void sb_reset(void);` |
| `sc_record_dump` | function | `headers/kernel.h:131` | `void sc_record_dump(int pid);` |
| `ser_e_cpu` | variable | `headers/kernel.h:133` | `extern unsigned long ser_e_ra, ser_e_cpu;` |
| `serial_available` | function | `headers/kernel.h:134` | `int serial_available(void);` |
| `serial_e_count` | function | `headers/kernel.h:132` | `unsigned long serial_e_count(void);` |
| `serial_getc` | function | `headers/kernel.h:135` | `int serial_getc(void);` |
| `serial_init` | function | `headers/kernel.h:128` | `void serial_init(void);` |
| `serial_putc` | function | `headers/kernel.h:129` | `void serial_putc(char c);` |
| `serial_puts` | function | `headers/kernel.h:130` | `void serial_puts(const char *s);` |
| `setup_user_stack` | function | `headers/kernel.h:671` | `unsigned long *setup_user_stack(char *sbase, unsigned long ssize, int argc, char **argv);` |
| `shell_exec_builtin` | function | `headers/kernel.h:617` | `void shell_exec_builtin(int argc, char **argv);` |
| `shell_fg_active` | variable | `headers/kernel.h:705` | `extern volatile int shell_fg_active;` |
| `shell_focus_park` | function | `headers/kernel.h:702` | `void shell_focus_park(void);` |
| `shell_focus_restore` | function | `headers/kernel.h:703` | `void shell_focus_restore(void);` |
| `shell_init` | function | `headers/kernel.h:588` | `void shell_init(void);` |
| `shell_queue_launch` | function | `headers/kernel.h:679` | `void shell_queue_launch(const char *cmd);` |
| `shell_readline_active` | function | `headers/kernel.h:701` | `int shell_readline_active(void);` |
| `shell_report` | function | `headers/kernel.h:619` | `void shell_report(const char *what, const char *detail);` |
| `shell_report_exit` | function | `headers/kernel.h:618` | `void shell_report_exit(int code);` |
| `shell_run` | function | `headers/kernel.h:589` | `void shell_run(void);` |
| `shell_run_any` | function | `headers/kernel.h:616` | `int shell_run_any(const char *name, int argc, char **argv);` |
| `shell_take_redirect` | function | `headers/kernel.h:615` | `int shell_take_redirect(int *argc, char **argv, char **path, int *append_mode);` |
| `swap_in` | function | `headers/kernel.h:720` | `int swap_in(void);` |
| `swap_out` | function | `headers/kernel.h:719` | `int swap_out(unsigned long window_sz);` |
| `syscall_init` | function | `headers/kernel.h:834` | `void syscall_init(void);` |
| `syscall_name` | function | `headers/kernel.h:844` | `const char *syscall_name(long n);` |
| `syscall_trace_enabled` | function | `headers/kernel.h:839` | `long syscall_trace_enabled(void);` |
| `syscall_trace_set` | function | `headers/kernel.h:840` | `void syscall_trace_set(int on);` |
| `syscall_trace_shown` | function | `headers/kernel.h:843` | `unsigned long syscall_trace_shown(void);` |
| `syscall_trace_verbose_enabled` | function | `headers/kernel.h:841` | `long syscall_trace_verbose_enabled(void);` |
| `syscall_trace_verbose_set` | function | `headers/kernel.h:842` | `void syscall_trace_verbose_set(int on);` |
| `today` | function | `headers/kernel.h:505` | `* cell is correct today (single shared ET_REL window, no miniGCC * threads);` |
| `user_mmap_cur` | variable | `headers/kernel.h:725` | `extern unsigned long user_mmap_cur;` |
| `user_page_present` | function | `headers/kernel.h:828` | `int user_page_present(unsigned long cr3, unsigned long va);` |
| `user_range_ok` | function | `headers/kernel.h:708` | `int user_range_ok(unsigned long p, unsigned long len);` |
| `user_str_ok` | function | `headers/kernel.h:709` | `int user_str_ok(unsigned long p, unsigned long maxlen);` |
| `vfs_close` | function | `headers/kernel.h:428` | `int vfs_close(vfs_file_t *f);` |
| `vfs_dirent` | struct | `headers/kernel.h:383` | `` |
| `vfs_file` | struct | `headers/kernel.h:398` | `` |
| `vfs_fstat` | function | `headers/kernel.h:429` | `int vfs_fstat(vfs_file_t *f, unsigned long *size_out);` |
| `vfs_init` | function | `headers/kernel.h:431` | `void vfs_init(void);` |
| `vfs_list` | function | `headers/kernel.h:422` | `int vfs_list(char prefixes[][VFS_PREFIX_LEN], char drivers[][VFS_DRIVER_LEN], int refs[], int cap);` |
| `vfs_mount_driver` | function | `headers/kernel.h:424` | `int vfs_mount_driver(const char *prefix, const char *driver);` |
| `vfs_open` | function | `headers/kernel.h:425` | `int vfs_open(const char *path, int mode, vfs_file_t *f);` |
| `vfs_ops` | struct | `headers/kernel.h:388` | `` |
| `vfs_read` | function | `headers/kernel.h:426` | `int vfs_read(vfs_file_t *f, void *buf, unsigned long len);` |
| `vfs_readdir` | function | `headers/kernel.h:430` | `int vfs_readdir(const char *path, vfs_dirent_t *ents, int cap);` |
| `vfs_register` | function | `headers/kernel.h:417` | `int vfs_register(const char *prefix, const vfs_ops_t *ops, const char *driver);` |
| `vfs_register_builtins` | function | `headers/kernel.h:432` | `void vfs_register_builtins(void);` |
| `vfs_unregister` | function | `headers/kernel.h:418` | `int vfs_unregister(const char *prefix);` |
| `vfs_write` | function | `headers/kernel.h:427` | `int vfs_write(vfs_file_t *f, const void *buf, unsigned long len);` |
| `vga_clear` | function | `headers/kernel.h:94` | `void vga_clear(void);` |
| `vga_cursor_enable` | function | `headers/kernel.h:100` | `void vga_cursor_enable(int on);` |
| `vga_fb_act_empty` | function | `headers/kernel.h:693` | `int vga_fb_act_empty(void);` |
| `vga_fb_clear_prompt` | function | `headers/kernel.h:696` | `void vga_fb_clear_prompt(void);` |
| `vga_fb_focus_get` | function | `headers/kernel.h:684` | `int vga_fb_focus_get(void);` |
| `vga_fb_focus_id` | function | `headers/kernel.h:683` | `int vga_fb_focus_id(int id);` |
| `vga_fb_focus_next` | function | `headers/kernel.h:682` | `void vga_fb_focus_next(void);` |
| `vga_fb_list_windows` | function | `headers/kernel.h:689` | `void vga_fb_list_windows(void);` |
| `vga_fb_note_prompt` | function | `headers/kernel.h:695` | `void vga_fb_note_prompt(void);` |
| `vga_fb_nterms_get` | function | `headers/kernel.h:685` | `int vga_fb_nterms_get(void);` |
| `vga_fb_park_line` | function | `headers/kernel.h:690` | `void vga_fb_park_line(const char *b, int p);` |
| `vga_fb_prompt_live` | function | `headers/kernel.h:694` | `int vga_fb_prompt_live(void);` |
| `vga_fb_prompted` | function | `headers/kernel.h:697` | `int vga_fb_prompted(void);` |
| `vga_fb_set_gfx_program` | function | `headers/kernel.h:692` | `void vga_fb_set_gfx_program(const char *name);` |
| `vga_fb_term_close_focused` | function | `headers/kernel.h:687` | `int vga_fb_term_close_focused(void);` |
| `vga_fb_term_split` | function | `headers/kernel.h:686` | `int vga_fb_term_split(void);` |
| `vga_fb_tile_all` | function | `headers/kernel.h:688` | `void vga_fb_tile_all(void);` |
| `vga_fb_unpark_line` | function | `headers/kernel.h:691` | `int vga_fb_unpark_line(char *b, int *p);` |
| `vga_get_color` | function | `headers/kernel.h:111` | `char vga_get_color(void);` |
| `vga_get_x` | function | `headers/kernel.h:108` | `int vga_get_x(void);` |
| `vga_get_y` | function | `headers/kernel.h:109` | `int vga_get_y(void);` |
| `vga_gfx_ran_set` | function | `headers/kernel.h:675` | `void vga_gfx_ran_set(int on);` |
| `vga_mode_is_active` | function | `headers/kernel.h:674` | `int vga_mode_is_active(void);` |
| `vga_mode_set` | function | `headers/kernel.h:673` | `void vga_mode_set(int on);` |
| `vga_newline` | function | `headers/kernel.h:99` | `void vga_newline(void);` |
| `vga_putc` | function | `headers/kernel.h:95` | `void vga_putc(char c);` |
| `vga_puts` | function | `headers/kernel.h:96` | `void vga_puts(const char *s);` |
| `vga_scroll` | function | `headers/kernel.h:97` | `void vga_scroll(void);` |
| `vga_set_cursor` | function | `headers/kernel.h:98` | `void vga_set_cursor(int x, int y);` |
| `vga_set_xy` | function | `headers/kernel.h:110` | `void vga_set_xy(int x, int y);` |
| `vnode_t` | type_alias | `headers/kernel.h:415` | `typedef vfs_file_t vnode_t;` |
| `waits` | function | `headers/kernel.h:64` | `* and mouse_hw_init issues dozens of waits (measured 5 s of boot).  This  * polls the port once p...` |
| `wall_us_now` | function | `headers/kernel.h:914` | `unsigned long wall_us_now(void);` |
| `CONSOLE_IN_H` | macro | `headers/kernel/console_in.h:2` | `#define CONSOLE_IN_H` |
| `Consumers` | function | `headers/kernel/console_in.h:7` | `* Consumers (shell prompt, editor, SPAWN waits, GETC_RAW syscall) include * this header instead of reaching into...` |
| `console_history_page` | function | `headers/kernel/console_in.h:19` | `void console_history_page(int dir);` |
| `console_job_get` | function | `headers/kernel/console_in.h:31` | `int console_job_get(void);` |
| `console_job_try` | function | `headers/kernel/console_in.h:30` | `int console_job_try(void);` |
| `console_peek` | function | `headers/kernel/console_in.h:22` | `int console_peek(void);` |
| `console_raw_get` | function | `headers/kernel/console_in.h:27` | `int console_raw_get(void);` |
| `console_raw_try` | function | `headers/kernel/console_in.h:26` | `int console_raw_try(void);` |
| `console_stdin_active` | function | `headers/kernel/console_in.h:44` | `int console_stdin_active(void);` |
| `console_stdin_clear` | function | `headers/kernel/console_in.h:43` | `void console_stdin_clear(void);` |
| `console_stdin_push` | function | `headers/kernel/console_in.h:42` | `int console_stdin_push(const char *data, unsigned long len);` |
| `console_ungetc` | function | `headers/kernel/console_in.h:35` | `void console_ungetc(unsigned char c);` |
| `CURSOR_H` | macro | `headers/kernel/vga_cursor.h:13` | `#define CURSOR_H` |
| `CURSOR_W` | macro | `headers/kernel/vga_cursor.h:12` | `#define CURSOR_W` |
| `VGA_CURSOR_H` | macro | `headers/kernel/vga_cursor.h:2` | `#define VGA_CURSOR_H` |
| `cursor_erase` | function | `headers/kernel/vga_cursor.h:25` | `void cursor_erase(void);` |
| `cursor_invalidate` | function | `headers/kernel/vga_cursor.h:28` | `void cursor_invalidate(void);` |
| `cursor_move` | function | `headers/kernel/vga_cursor.h:22` | `void cursor_move(int mx, int my);` |
| `cursor_note_repaint` | function | `headers/kernel/vga_cursor.h:31` | `void cursor_note_repaint(int x0, int y0, int w, int h);` |
| `cursor_over` | function | `headers/kernel/vga_cursor.h:16` | `int cursor_over(int x0, int y0, int w, int h);` |
| `cursor_place` | function | `headers/kernel/vga_cursor.h:19` | `void cursor_place(int mx, int my);` |
| `KTIME_H` | macro | `headers/ktime.h:2` | `#define KTIME_H` |
| `ktime_us_from_delta` | function | `headers/ktime.h:19` | `static inline unsigned long ktime_us_from_delta(unsigned long delta_ticks,                       ...` |
| `wall_us_from_parts` | function | `headers/ktime.h:30` | `static inline unsigned long wall_us_from_parts(unsigned long base_sec,                           ...` |
| `LDSO_DT_HASH` | macro | `headers/ldso.h:33` | `#define LDSO_DT_HASH` |
| `LDSO_DT_NEEDED` | macro | `headers/ldso.h:32` | `#define LDSO_DT_NEEDED` |
| `LDSO_DT_NULL` | macro | `headers/ldso.h:31` | `#define LDSO_DT_NULL` |
| `LDSO_DT_RELA` | macro | `headers/ldso.h:36` | `#define LDSO_DT_RELA` |
| `LDSO_DT_RELAENT` | macro | `headers/ldso.h:38` | `#define LDSO_DT_RELAENT` |
| `LDSO_DT_RELASZ` | macro | `headers/ldso.h:37` | `#define LDSO_DT_RELASZ` |
| `LDSO_DT_SONAME` | macro | `headers/ldso.h:41` | `#define LDSO_DT_SONAME` |
| `LDSO_DT_STRSZ` | macro | `headers/ldso.h:39` | `#define LDSO_DT_STRSZ` |
| `LDSO_DT_STRTAB` | macro | `headers/ldso.h:34` | `#define LDSO_DT_STRTAB` |
| `LDSO_DT_SYMENT` | macro | `headers/ldso.h:40` | `#define LDSO_DT_SYMENT` |
| `LDSO_DT_SYMTAB` | macro | `headers/ldso.h:35` | `#define LDSO_DT_SYMTAB` |
| `LDSO_EM_X86_64` | macro | `headers/ldso.h:26` | `#define LDSO_EM_X86_64` |
| `LDSO_ET_DYN` | macro | `headers/ldso.h:25` | `#define LDSO_ET_DYN` |
| `LDSO_ET_EXEC` | macro | `headers/ldso.h:24` | `#define LDSO_ET_EXEC` |
| `LDSO_FILE_MAX` | macro | `headers/ldso.h:21` | `#define LDSO_FILE_MAX` |
| `LDSO_H` | macro | `headers/ldso.h:15` | `#define LDSO_H` |
| `LDSO_INO_BASE` | macro | `headers/ldso.h:22` | `#define LDSO_INO_BASE` |
| `LDSO_MAX_DYN` | macro | `headers/ldso.h:20` | `#define LDSO_MAX_DYN` |
| `LDSO_MAX_LIBS` | macro | `headers/ldso.h:17` | `#define LDSO_MAX_LIBS` |
| `LDSO_MAX_NEEDED` | macro | `headers/ldso.h:18` | `#define LDSO_MAX_NEEDED` |
| `LDSO_NAME_LEN` | macro | `headers/ldso.h:19` | `#define LDSO_NAME_LEN` |
| `LDSO_PF_X` | macro | `headers/ldso.h:29` | `#define LDSO_PF_X` |
| `LDSO_PT_DYNAMIC` | macro | `headers/ldso.h:28` | `#define LDSO_PT_DYNAMIC` |
| `LDSO_PT_LOAD` | macro | `headers/ldso.h:27` | `#define LDSO_PT_LOAD` |
| `LDSO_RELA_SIZE` | macro | `headers/ldso.h:51` | `#define LDSO_RELA_SIZE` |
| `LDSO_R_GLOB_DAT` | macro | `headers/ldso.h:43` | `#define LDSO_R_GLOB_DAT` |
| `LDSO_R_JUMP_SLOT` | macro | `headers/ldso.h:44` | `#define LDSO_R_JUMP_SLOT` |
| `LDSO_SHN_UNDEF` | macro | `headers/ldso.h:49` | `#define LDSO_SHN_UNDEF` |
| `LDSO_STB_GLOBAL` | macro | `headers/ldso.h:46` | `#define LDSO_STB_GLOBAL` |
| `LDSO_STT_FUNC` | macro | `headers/ldso.h:48` | `#define LDSO_STT_FUNC` |
| `LDSO_STT_NOTYPE` | macro | `headers/ldso.h:47` | `#define LDSO_STT_NOTYPE` |
| `LDSO_SYM_SIZE` | macro | `headers/ldso.h:50` | `#define LDSO_SYM_SIZE` |
| `LdsoDynInfo` | struct | `headers/ldso.h:61` | `` |
| `LdsoRelaRow` | struct | `headers/ldso.h:77` | `` |
| `LdsoSeg` | struct | `headers/ldso.h:53` | `` |
| `ldso_basename` | function | `headers/ldso.h:144` | `void ldso_basename(char *out, const char *src);` |
| `ldso_copy_str` | function | `headers/ldso.h:116` | `int ldso_copy_str(const unsigned char *file, unsigned long long fsize, unsigned long long strtab_off, unsigned long...` |
| `ldso_find_dynamic` | function | `headers/ldso.h:86` | `int ldso_find_dynamic(const unsigned char *file, unsigned long long fsize, unsigned long long *dyn_off, unsigned...` |
| `ldso_read_rela` | function | `headers/ldso.h:137` | `int ldso_read_rela(const unsigned char *file, unsigned long long fsize, unsigned long long rela_off, unsigned nrela...` |
| `ldso_rela_count` | function | `headers/ldso.h:132` | `int ldso_rela_count(const LdsoDynInfo *info, unsigned *nrela);` |
| `ldso_scan_dynamic` | function | `headers/ldso.h:103` | `int ldso_scan_dynamic(const unsigned char *file, unsigned long long fsize, unsigned long long dyn_off, unsigned long...` |
| `ldso_segments` | function | `headers/ldso.h:97` | `int ldso_segments(const unsigned char *file, unsigned long long fsize, LdsoSeg *segs, unsigned ncap, unsigned *nseg);` |
| `ldso_sym_count` | function | `headers/ldso.h:110` | `int ldso_sym_count(const unsigned char *file, unsigned long long fsize, unsigned long long hash_off, unsigned *nsyms);` |
| `ldso_sym_lookup` | function | `headers/ldso.h:124` | `int ldso_sym_lookup(const unsigned char *file, unsigned long long fsize, unsigned long long symtab_off, unsigned...` |
| `ldso_vaddr_to_offset` | function | `headers/ldso.h:92` | `int ldso_vaddr_to_offset(const unsigned char *file, unsigned long long fsize, unsigned long long va, unsigned long...` |
| `MINIOS_LEAKCHECK_H` | macro | `headers/leakcheck.h:28` | `#define MINIOS_LEAKCHECK_H` |
| `MINIOS_LK_PIPE` | macro | `headers/leakcheck.h:42` | `#define MINIOS_LK_PIPE` |
| `MINIOS_LK_PIPE` | macro | `headers/leakcheck.h:44` | `#define MINIOS_LK_PIPE` |
| `MINIOS_LK_RAW_ALLOC` | macro | `headers/leakcheck.h:82` | `#define MINIOS_LK_RAW_ALLOC(sz)` |
| `MINIOS_LK_RAW_ALLOC` | macro | `headers/leakcheck.h:88` | `#define MINIOS_LK_RAW_ALLOC(sz)` |
| `MINIOS_LK_RAW_FREE` | macro | `headers/leakcheck.h:83` | `#define MINIOS_LK_RAW_FREE(p)` |
| `MINIOS_LK_RAW_FREE` | macro | `headers/leakcheck.h:89` | `#define MINIOS_LK_RAW_FREE(p)` |
| `free` | macro | `headers/leakcheck.h:236` | `#define free(p)` |
| `kfree` | function | `headers/leakcheck.h:80` | `extern void kfree(void *ptr);` |
| `kmalloc` | function | `headers/leakcheck.h:79` | `extern void *kmalloc(unsigned long size);` |
| `kprintf` | function | `headers/leakcheck.h:81` | `extern int kprintf(const char *fmt, ...);` |
| `lk_block` | struct | `headers/leakcheck.h:50` | `` |
| `lk_block_t` | type_alias | `headers/leakcheck.h:49` | `typedef struct lk_block lk_block_t;` |
| `lk_dumpmem` | function | `headers/leakcheck.h:197` | `void lk_dumpmem(void)` |
| `lk_find` | function | `headers/leakcheck.h:120` | `static lk_block_t *lk_find(void *ptr)` |
| `lk_free` | function | `headers/leakcheck.h:130` | `void lk_free(void *ptr)` |
| `lk_live_bytes` | function | `headers/leakcheck.h:217` | `unsigned long lk_live_bytes(void)` |
| `lk_live_count` | function | `headers/leakcheck.h:206` | `unsigned long lk_live_count(void)` |
| `lk_malloc` | function | `headers/leakcheck.h:96` | `void *lk_malloc(size_t size, const char *file, int line)` |
| `lk_print` | function | `headers/leakcheck.h:186` | `static void lk_print(const char *reason, const lk_block_t *b)` |
| `lk_realloc` | function | `headers/leakcheck.h:143` | `void *lk_realloc(void *ptr, size_t size, const char *file, int line)` |
| `lk_unlink` | function | `headers/leakcheck.h:110` | `static void lk_unlink(lk_block_t *b)` |
| `malloc` | macro | `headers/leakcheck.h:235` | `#define malloc(sz)` |
| `realloc` | macro | `headers/leakcheck.h:237` | `#define realloc(p, sz)` |
| `LZ4_KERNEL_H` | macro | `headers/lz4_kernel.h:2` | `#define LZ4_KERNEL_H` |
| `LZ4_compressBound` | function | `headers/lz4_kernel.h:5` | `int LZ4_compressBound(int inputSize);` |
| `LZ4_compress_default` | function | `headers/lz4_kernel.h:4` | `int LZ4_compress_default(const char *src, char *dst, int srcSize, int dstCapacity);` |
| `LZ4_decompress_safe` | function | `headers/lz4_kernel.h:6` | `int LZ4_decompress_safe(const char *src, char *dst, int compressedSize, int dstCapacity);` |
| `MINIFETCH_H` | macro | `headers/minifetch.h:12` | `#define MINIFETCH_H` |
| `shell_cmd_minifetch` | function | `headers/minifetch.h:14` | `void shell_cmd_minifetch(void);` |
| `MINIFS_BLOCK_SIZE` | macro | `headers/minifs.h:10` | `#define MINIFS_BLOCK_SIZE` |
| `MINIFS_DIR_ENTRIES_PER_BLOCK` | macro | `headers/minifs.h:14` | `#define MINIFS_DIR_ENTRIES_PER_BLOCK` |
| `MINIFS_DIR_ENTRY_HDR_SIZE` | macro | `headers/minifs.h:75` | `#define MINIFS_DIR_ENTRY_HDR_SIZE` |
| `MINIFS_FT_DIR` | macro | `headers/minifs.h:25` | `#define MINIFS_FT_DIR` |
| `MINIFS_FT_FILE` | macro | `headers/minifs.h:24` | `#define MINIFS_FT_FILE` |
| `MINIFS_FT_SYMLINK` | macro | `headers/minifs.h:26` | `#define MINIFS_FT_SYMLINK` |
| `MINIFS_H` | macro | `headers/minifs.h:2` | `#define MINIFS_H` |
| `MINIFS_INODES_PER_BLOCK` | macro | `headers/minifs.h:13` | `#define MINIFS_INODES_PER_BLOCK` |
| `MINIFS_INODE_COMPRESSED` | macro | `headers/minifs.h:28` | `#define MINIFS_INODE_COMPRESSED` |
| `MINIFS_JOP_COMMIT` | macro | `headers/minifs.h:85` | `#define MINIFS_JOP_COMMIT` |
| `MINIFS_JOP_CREATE` | macro | `headers/minifs.h:80` | `#define MINIFS_JOP_CREATE` |
| `MINIFS_JOP_DELETE` | macro | `headers/minifs.h:81` | `#define MINIFS_JOP_DELETE` |
| `MINIFS_JOP_MKDIR` | macro | `headers/minifs.h:82` | `#define MINIFS_JOP_MKDIR` |
| `MINIFS_JOP_RMDIR` | macro | `headers/minifs.h:83` | `#define MINIFS_JOP_RMDIR` |
| `MINIFS_JOP_TRUNCATE` | macro | `headers/minifs.h:84` | `#define MINIFS_JOP_TRUNCATE` |
| `MINIFS_JOP_WRITE` | macro | `headers/minifs.h:79` | `#define MINIFS_JOP_WRITE` |
| `MINIFS_JOURNAL_BLOCKS` | macro | `headers/minifs.h:77` | `#define MINIFS_JOURNAL_BLOCKS` |
| `MINIFS_JOURNAL_MAX_ENTRIES` | macro | `headers/minifs.h:78` | `#define MINIFS_JOURNAL_MAX_ENTRIES` |
| `MINIFS_JSTATE_CLEAN` | macro | `headers/minifs.h:87` | `#define MINIFS_JSTATE_CLEAN` |
| `MINIFS_JSTATE_DIRTY` | macro | `headers/minifs.h:88` | `#define MINIFS_JSTATE_DIRTY` |
| `MINIFS_MAGIC` | macro | `headers/minifs.h:8` | `#define MINIFS_MAGIC` |
| `MINIFS_MAX_FILENAME` | macro | `headers/minifs.h:11` | `#define MINIFS_MAX_FILENAME` |
| `MINIFS_ROOT_INODE` | macro | `headers/minifs.h:12` | `#define MINIFS_ROOT_INODE` |
| `MINIFS_S_IFDIR` | macro | `headers/minifs.h:18` | `#define MINIFS_S_IFDIR` |
| `MINIFS_S_IFLNK` | macro | `headers/minifs.h:19` | `#define MINIFS_S_IFLNK` |
| `MINIFS_S_IFMT` | macro | `headers/minifs.h:16` | `#define MINIFS_S_IFMT` |
| `MINIFS_S_IFREG` | macro | `headers/minifs.h:17` | `#define MINIFS_S_IFREG` |
| `MINIFS_S_IRWXG` | macro | `headers/minifs.h:21` | `#define MINIFS_S_IRWXG` |
| `MINIFS_S_IRWXO` | macro | `headers/minifs.h:22` | `#define MINIFS_S_IRWXO` |
| `MINIFS_S_IRWXU` | macro | `headers/minifs.h:20` | `#define MINIFS_S_IRWXU` |
| `MINIFS_VERSION` | macro | `headers/minifs.h:9` | `#define MINIFS_VERSION` |
| `MiniFSDirEntry` | struct | `headers/minifs.h:68` | `` |
| `MiniFSFile` | struct | `headers/minifs.h:110` | `` |
| `MiniFSInode` | struct | `headers/minifs.h:52` | `` |
| `MiniFSJournalEntry` | struct | `headers/minifs.h:98` | `` |
| `MiniFSJournalSuper` | struct | `headers/minifs.h:90` | `` |
| `MiniFSSuper` | struct | `headers/minifs.h:33` | `` |
| `minifs_access` | function | `headers/minifs.h:135` | `int minifs_access(const char *path);` |
| `minifs_alloc_block` | function | `headers/minifs.h:143` | `int minifs_alloc_block(void);` |
| `minifs_alloc_inode` | function | `headers/minifs.h:145` | `int minifs_alloc_inode(void);` |
| `minifs_compress` | function | `headers/minifs.h:30` | `unsigned int minifs_compress(const void *src, unsigned int src_len, void *dst, unsigned int dst_cap);` |
| `minifs_create` | function | `headers/minifs.h:122` | `int minifs_create(const char *path, unsigned short mode);` |
| `minifs_decompress` | function | `headers/minifs.h:31` | `unsigned int minifs_decompress(const void *src, unsigned int src_len, void *dst, unsigned int dst_cap);` |
| `minifs_dir_add_entry` | function | `headers/minifs.h:139` | `int minifs_dir_add_entry(int dir_inode, const char *name, int child_inode, unsigned char type);` |
| `minifs_dir_lookup` | function | `headers/minifs.h:138` | `int minifs_dir_lookup(int dir_inode, const char *name);` |
| `minifs_dir_read` | function | `headers/minifs.h:141` | `int minifs_dir_read(int dir_inode, int index, MiniFSDirEntry *out, char *name_out);` |
| `minifs_dir_remove_entry` | function | `headers/minifs.h:140` | `int minifs_dir_remove_entry(int dir_inode, const char *name);` |
| `minifs_file_close` | function | `headers/minifs.h:159` | `int minifs_file_close(MiniFSFile *f);` |
| `minifs_file_open` | function | `headers/minifs.h:158` | `MiniFSFile *minifs_file_open(int inode_num, int flags);` |
| `minifs_free_block` | function | `headers/minifs.h:144` | `void minifs_free_block(unsigned int block);` |
| `minifs_free_inode` | function | `headers/minifs.h:146` | `void minifs_free_inode(int inode_num);` |
| `minifs_get_lba_start` | function | `headers/minifs.h:161` | `unsigned int minifs_get_lba_start(void);` |
| `minifs_get_total_blocks` | function | `headers/minifs.h:162` | `unsigned int minifs_get_total_blocks(void);` |
| `minifs_init` | function | `headers/minifs.h:117` | `void minifs_init(void);` |
| `minifs_inode_alloc_block` | function | `headers/minifs.h:148` | `int minifs_inode_alloc_block(MiniFSInode *inode, unsigned int logical_block);` |
| `minifs_inode_get_block` | function | `headers/minifs.h:147` | `int minifs_inode_get_block(MiniFSInode *inode, unsigned int logical_block, unsigned int *phys_block);` |
| `minifs_is_mounted` | function | `headers/minifs.h:120` | `int minifs_is_mounted(void);` |
| `minifs_journal_abort` | function | `headers/minifs.h:155` | `void minifs_journal_abort(void);` |
| `minifs_journal_add_block` | function | `headers/minifs.h:151` | `void minifs_journal_add_block(unsigned int block);` |
| `minifs_journal_begin` | function | `headers/minifs.h:150` | `void minifs_journal_begin(unsigned int txn_id);` |
| `minifs_journal_clear` | function | `headers/minifs.h:154` | `void minifs_journal_clear(void);` |
| `minifs_journal_commit` | function | `headers/minifs.h:153` | `int minifs_journal_commit(unsigned int txn_id);` |
| `minifs_journal_recover` | function | `headers/minifs.h:156` | `void minifs_journal_recover(void);` |
| `minifs_journal_touch` | function | `headers/minifs.h:152` | `void minifs_journal_touch(unsigned int phys);` |
| `minifs_mkdir` | function | `headers/minifs.h:123` | `int minifs_mkdir(const char *path, unsigned short mode);` |
| `minifs_mount` | function | `headers/minifs.h:118` | `int minifs_mount(void);` |
| `minifs_read` | function | `headers/minifs.h:131` | `int minifs_read(int inode_num, void *buf, unsigned int offset, unsigned int len);` |

Next: [SYMBOLS_p6.md](SYMBOLS_p6.md)
