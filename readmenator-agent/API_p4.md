# API (page 4 of 21)
Previous: [API_p3.md](API_p3.md)

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
- `ramdisk_init` (function) `headers/kernel.h:287` `void ramdisk_init(void);`
- `ramdisk_open` (function) `headers/kernel.h:288` `RDFile *ramdisk_open(const char *name);`
- `ramdisk_read` (function) `headers/kernel.h:289` `int ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len);`
- `ramdisk_write` (function) `headers/kernel.h:290` `int ramdisk_write(RDFile *f, const void *buf, unsigned offset, unsigned len);`
- `ramdisk_create` (function) `headers/kernel.h:291` `RDFile *ramdisk_create(const char *name, unsigned size);`
- `ramdisk_resize` (function) `headers/kernel.h:292` `int ramdisk_resize(RDFile *f, unsigned newsize);`
- `ramdisk_delete` (function) `headers/kernel.h:293` `int ramdisk_delete(RDFile *f);`
- `RAMDISK_FNAME_LEN` (function) `headers/kernel.h:295` `* RAMDISK_FNAME_LEN (fs_resolve guarantees it);`
- `ramdisk_rename` (function) `headers/kernel.h:297` `int ramdisk_rename(const char *oldname, const char *newname);` -- Docstring: In-place rename of one ramdisk entry.
- `ramdisk_list` (function) `headers/kernel.h:298` `int ramdisk_list(RDFile **out, int max);`
- `ramdisk_setup_from` (function) `headers/kernel.h:299` `void ramdisk_setup_from(void *data, unsigned size);`
- `ramdisk_count` (function) `headers/kernel.h:300` `int ramdisk_count(void);`
- `ramdisk_file_name` (function) `headers/kernel.h:301` `const char *ramdisk_file_name(int idx);`
- `ramdisk_usage` (function) `headers/kernel.h:303` `void ramdisk_usage(unsigned *used, unsigned *cap, unsigned *max);` -- Docstring: In-place rename of one ramdisk entry.
- `fs_resolve` (function) `headers/kernel.h:311` `int fs_resolve(const char *path, char *out, unsigned cap);` -- Path resolution choke point shared by the shell builtins and the zip builtins. fs_resolve resolves a path against...
- `fs_dir_exists` (function) `headers/kernel.h:312` `int fs_dir_exists(const char *dir);`
- `fs_is_dir` (function) `headers/kernel.h:313` `int fs_is_dir(const char *resolved);`
- `vfs_register` (function) `headers/kernel.h:417` `int vfs_register(const char *prefix, const vfs_ops_t *ops, const char *driver);`
- `vfs_unregister` (function) `headers/kernel.h:418` `int vfs_unregister(const char *prefix);`
- `vfs_list` (function) `headers/kernel.h:422` `int vfs_list(char prefixes[][VFS_PREFIX_LEN], char drivers[][VFS_DRIVER_LEN], int refs[], int cap);` -- define VFS_MAX_MOUNTS 8 define VFS_PREFIX_LEN 32 define VFS_DRIVER_LEN 16
- `vfs_mount_driver` (function) `headers/kernel.h:424` `int vfs_mount_driver(const char *prefix, const char *driver);`
- `vfs_open` (function) `headers/kernel.h:425` `int vfs_open(const char *path, int mode, vfs_file_t *f);`
- `vfs_read` (function) `headers/kernel.h:426` `int vfs_read(vfs_file_t *f, void *buf, unsigned long len);`
- `vfs_write` (function) `headers/kernel.h:427` `int vfs_write(vfs_file_t *f, const void *buf, unsigned long len);`
- `vfs_close` (function) `headers/kernel.h:428` `int vfs_close(vfs_file_t *f);`
- `vfs_fstat` (function) `headers/kernel.h:429` `int vfs_fstat(vfs_file_t *f, unsigned long *size_out);`
- `vfs_readdir` (function) `headers/kernel.h:430` `int vfs_readdir(const char *path, vfs_dirent_t *ents, int cap);`
- `vfs_init` (function) `headers/kernel.h:431` `void vfs_init(void);`
- `vfs_register_builtins` (function) `headers/kernel.h:432` `void vfs_register_builtins(void);`
- `minifs_mkdir_p` (function) `headers/kernel.h:433` `int minifs_mkdir_p(const char *resolved);`
- `kfopen` (function) `headers/kernel.h:495` `KFILE *kfopen(const char *path, const char *mode);`
- `kfopen_dir` (function) `headers/kernel.h:499` `KFILE *kfopen_dir(const char *resolved);` -- Directory handle for getdents64: kfopen refuses directories (EISDIR), so open(2) on a directory takes this path...
- `kfclose` (function) `headers/kernel.h:500` `int kfclose(KFILE *f);`
- `today` (function) `headers/kernel.h:505` `* cell is correct today (single shared ET_REL window, no miniGCC * threads);`
- `fs_rename` (function) `headers/kernel.h:524` `int fs_rename(const char *oldr, const char *newr);` -- Rename one file within its filesystem; see fs/kfile.c for the contract: * 0 ok, -2 missing src, -21 directory, -17...
- `kfgetc` (function) `headers/kernel.h:525` `int kfgetc(KFILE *f);`
- `kfgets` (function) `headers/kernel.h:526` `char *kfgets(char *buf, int size, KFILE *f);`
- `kfungetc` (function) `headers/kernel.h:527` `int kfungetc(int c, KFILE *f);`
- `kfread` (function) `headers/kernel.h:528` `unsigned long kfread(void *ptr, unsigned long size, unsigned long nmemb, KFILE *f);`
- `kfwrite` (function) `headers/kernel.h:529` `unsigned long kfwrite(const void *ptr, unsigned long size, unsigned long nmemb, KFILE *f);`
- `kfseek` (function) `headers/kernel.h:530` `int kfseek(KFILE *f, long offset, int whence);`
- `kftell` (function) `headers/kernel.h:531` `long kftell(KFILE *f);`
- `kfputs` (function) `headers/kernel.h:532` `int kfputs(const char *s, KFILE *f);`
- `kfputc` (function) `headers/kernel.h:533` `int kfputc(int c, KFILE *f);`
- `kfflush` (function) `headers/kernel.h:534` `int kfflush(KFILE *f);`
- `krewind` (function) `headers/kernel.h:535` `void krewind(KFILE *f);`
- `kfile_stdin` (function) `headers/kernel.h:540` `KFILE *kfile_stdin(void);`
- `kfile_stdout` (function) `headers/kernel.h:541` `KFILE *kfile_stdout(void);`
- `kfile_stderr` (function) `headers/kernel.h:542` `KFILE *kfile_stderr(void);`
- `kstrlen` (function) `headers/kernel.h:545` `unsigned long kstrlen(const char *s);` -- long   kftell(KFILE *f); int    kfputs(const char *s, KFILE *f); int    kfputc(int c, KFILE *f); int...
- `kstrcpy` (function) `headers/kernel.h:546` `char *kstrcpy(char *dst, const char *src);`
- `kstrncpy` (function) `headers/kernel.h:547` `char *kstrncpy(char *dst, const char *src, unsigned long n);`
- `kstrncat` (function) `headers/kernel.h:548` `char *kstrncat(char *dst, const char *src, unsigned long n);`
- `kstrcmp` (function) `headers/kernel.h:549` `int kstrcmp(const char *a, const char *b);`
- `kstrncmp` (function) `headers/kernel.h:550` `int kstrncmp(const char *a, const char *b, unsigned long n);`
- `kstrchr` (function) `headers/kernel.h:551` `char *kstrchr(const char *s, int c);`
- `kstrstr` (function) `headers/kernel.h:552` `char *kstrstr(const char *hay, const char *ndl);`
- `kmemcpy` (function) `headers/kernel.h:553` `void *kmemcpy(void *dst, const void *src, unsigned long n);`
- `kmemset` (function) `headers/kernel.h:554` `void *kmemset(void *dst, int c, unsigned long n);`
- `kmemcmp` (function) `headers/kernel.h:555` `int kmemcmp(const void *a, const void *b, unsigned long n);`
- `kmemmove` (function) `headers/kernel.h:556` `void *kmemmove(void *dst, const void *src, unsigned long n);`
- `katol` (function) `headers/kernel.h:557` `long katol(const char *s);`
- `kprintf` (function) `headers/kernel.h:560` `int kprintf(const char *fmt, ...);` -- char *kstrcpy(char *dst, const char *src); char *kstrncpy(char *dst, const char *src, unsigned long n); char...
- `kfprintf` (function) `headers/kernel.h:561` `int kfprintf(KFILE *f, const char *fmt, ...);`
- `ksprintf` (function) `headers/kernel.h:562` `int ksprintf(char *buf, const char *fmt, ...);`
- `ksnprintf` (function) `headers/kernel.h:563` `int ksnprintf(char *buf, unsigned long size, const char *fmt, ...);`
- `klog` (function) `headers/kernel.h:578` `void klog(log_level_t level, log_subsystem_t subsys, const char *fmt, ...);`
- `klog_hexdump` (function) `headers/kernel.h:580` `void klog_hexdump(log_level_t level, log_subsystem_t subsys, const void *data, unsigned long len, const char *label);`
- `klog_set_level` (function) `headers/kernel.h:582` `void klog_set_level(log_level_t level);`
- `klog_set_subsys_level` (function) `headers/kernel.h:583` `void klog_set_subsys_level(log_subsystem_t subsys, log_level_t level);`
- `klog_disable` (function) `headers/kernel.h:584` `void klog_disable(void);`
- `klog_enable` (function) `headers/kernel.h:585` `void klog_enable(void);`
- `shell_init` (function) `headers/kernel.h:588` `void shell_init(void);` -- LOG_SUBSYS_SHELL, LOG_SUBSYS_BOOT, LOG_SUBSYS_GENERAL, LOG_SUBSYS_COUNT } log_subsystem_t; void klog(log_level_t...
- `shell_run` (function) `headers/kernel.h:589` `void shell_run(void);`
- `console_getc` (function) `headers/kernel.h:590` `int console_getc(void);`
- `console_peek` (function) `headers/kernel.h:591` `int console_peek(void);`
- `redirect_suspend` (function) `headers/kernel.h:592` `int redirect_suspend(void);`
- `redirect_resume` (function) `headers/kernel.h:593` `void redirect_resume(int was);`
- `redirect_begin` (function) `headers/kernel.h:594` `int redirect_begin(void);`
- `redirect_commit` (function) `headers/kernel.h:595` `int redirect_commit(const char *path, int append_mode);`
- `redirect_take` (function) `headers/kernel.h:596` `char *redirect_take(unsigned long *len_out);`
- `redirect_pending` (function) `headers/kernel.h:597` `unsigned long redirect_pending(void);`
- `redirect_take_into` (function) `headers/kernel.h:598` `unsigned long redirect_take_into(char *dst, unsigned long cap, unsigned long *len_out);`
- `redirect_discard` (function) `headers/kernel.h:600` `void redirect_discard(void);`
- `redirect_active` (function) `headers/kernel.h:601` `int redirect_active(void);`
- `console_stdin_push` (function) `headers/kernel.h:602` `int console_stdin_push(const char *data, unsigned long len);`
- `console_stdin_clear` (function) `headers/kernel.h:603` `void console_stdin_clear(void);`
- `console_stdin_active` (function) `headers/kernel.h:604` `int console_stdin_active(void);`
- `panic_screen` (function) `headers/kernel.h:607` `void panic_screen(unsigned long vector, unsigned long err, unsigned long rip, unsigned long rsp, unsigned long rbp...` -- void redirect_resume(int was); int  redirect_begin(void); int  redirect_commit(const char *path, int append_mode)...
- `clip_set` (function) `headers/kernel.h:611` `int clip_set(const char *data, unsigned long len);` -- unsigned long redirect_pending(void); unsigned long redirect_take_into(char *dst, unsigned long cap, unsigned long...
- `clip_get` (function) `headers/kernel.h:612` `int clip_get(char *out, unsigned long cap);`
- `clip_clear` (function) `headers/kernel.h:613` `void clip_clear(void);`
- `clip_len_get` (function) `headers/kernel.h:614` `int clip_len_get(void);`
- `shell_take_redirect` (function) `headers/kernel.h:615` `int shell_take_redirect(int *argc, char **argv, char **path, int *append_mode);`
- `shell_run_any` (function) `headers/kernel.h:616` `int shell_run_any(const char *name, int argc, char **argv);`
- `shell_exec_builtin` (function) `headers/kernel.h:617` `void shell_exec_builtin(int argc, char **argv);`
- `shell_report_exit` (function) `headers/kernel.h:618` `void shell_report_exit(int code);`
- `shell_report` (function) `headers/kernel.h:619` `void shell_report(const char *what, const char *detail);`
- `kprog_slot` (function) `headers/kernel.h:644` `KProg *kprog_slot(const char *name);`
- `kprog_lookup` (function) `headers/kernel.h:645` `KProg *kprog_lookup(const char *name);`
- `ksym_resolve` (function) `headers/kernel.h:646` `void *ksym_resolve(const char *name);`
- `k_spawn` (function) `headers/kernel.h:647` `int k_spawn(const char *name, int argc, char **argv);`
- `k_register_program` (function) `headers/kernel.h:648` `void k_register_program(const char *name, prog_entry_t entry);`
- `k_register_process` (function) `headers/kernel.h:649` `void k_register_process(const char *name, void *proc_entry);`
- `k_register_symbol` (function) `headers/kernel.h:650` `void k_register_symbol(const char *name, void *addr);`
- `register_libc_symbols` (function) `headers/kernel.h:654` `void register_libc_symbols(void);` -- Libc name table for ET_REL programs (kernel/console.c).
- `k_exec_user` (function) `headers/kernel.h:657` `int k_exec_user(void *entry, int argc, char **argv);` -- Libc name table for ET_REL programs (kernel/console.c).
- `k_run_rel` (function) `headers/kernel.h:658` `int k_run_rel(prog_entry_t entry, int argc, char **argv);`
- `kexit` (function) `headers/kernel.h:659` `void kexit(int code);`
- `k_run_on_stack` (function) `headers/kernel.h:662` `int k_run_on_stack(void *stack_top, prog_entry_t entry, int argc, char **argv);` -- ET_REL stack switch (arch/x86/ctx_sw.S): runs entry(argc, argv) on * the 64 KB stack ending at stack_top.
- `ksetjmp` (function) `headers/kernel.h:667` `int ksetjmp(void *buf) __attribute__((returns_twice));`
- `klongjmp` (function) `headers/kernel.h:668` `void klongjmp(void *buf, int val) __attribute__((noreturn));`
- `setup_user_stack` (function) `headers/kernel.h:671` `unsigned long *setup_user_stack(char *sbase, unsigned long ssize, int argc, char **argv);`
- `vga_mode_set` (function) `headers/kernel.h:673` `void vga_mode_set(int on);`
- `vga_mode_is_active` (function) `headers/kernel.h:674` `int vga_mode_is_active(void);`
- `vga_gfx_ran_set` (function) `headers/kernel.h:675` `void vga_gfx_ran_set(int on);`
- `desktop_launch` (function) `headers/kernel.h:678` `void desktop_launch(const char *cmd);`
- `shell_queue_launch` (function) `headers/kernel.h:679` `void shell_queue_launch(const char *cmd);`
- `vga_fb_focus_next` (function) `headers/kernel.h:682` `void vga_fb_focus_next(void);` -- void klongjmp(void *buf, int val) __attribute__((noreturn)); extern kjmpbuf exec_return; extern int...
- `vga_fb_focus_id` (function) `headers/kernel.h:683` `int vga_fb_focus_id(int id);`
- `vga_fb_focus_get` (function) `headers/kernel.h:684` `int vga_fb_focus_get(void);`
- `vga_fb_nterms_get` (function) `headers/kernel.h:685` `int vga_fb_nterms_get(void);`
- `vga_fb_term_split` (function) `headers/kernel.h:686` `int vga_fb_term_split(void);`
- `vga_fb_term_close_focused` (function) `headers/kernel.h:687` `int vga_fb_term_close_focused(void);`
- `vga_fb_tile_all` (function) `headers/kernel.h:688` `void vga_fb_tile_all(void);`
- `vga_fb_list_windows` (function) `headers/kernel.h:689` `void vga_fb_list_windows(void);`
- `vga_fb_park_line` (function) `headers/kernel.h:690` `void vga_fb_park_line(const char *b, int p);`
- `vga_fb_unpark_line` (function) `headers/kernel.h:691` `int vga_fb_unpark_line(char *b, int *p);`
- `vga_fb_set_gfx_program` (function) `headers/kernel.h:692` `void vga_fb_set_gfx_program(const char *name);`
- `vga_fb_act_empty` (function) `headers/kernel.h:693` `int vga_fb_act_empty(void);`
- `vga_fb_prompt_live` (function) `headers/kernel.h:694` `int vga_fb_prompt_live(void);`
- `vga_fb_note_prompt` (function) `headers/kernel.h:695` `void vga_fb_note_prompt(void);`
- `vga_fb_clear_prompt` (function) `headers/kernel.h:696` `void vga_fb_clear_prompt(void);`
- `vga_fb_prompted` (function) `headers/kernel.h:697` `int vga_fb_prompted(void);`
- `shell_readline_active` (function) `headers/kernel.h:701` `int shell_readline_active(void);` -- Shell side of window focus: park/restore the half-typed input line so it * travels with its window.
- `shell_focus_park` (function) `headers/kernel.h:702` `void shell_focus_park(void);`
- `shell_focus_restore` (function) `headers/kernel.h:703` `void shell_focus_restore(void);`
- `user_range_ok` (function) `headers/kernel.h:708` `int user_range_ok(unsigned long p, unsigned long len);` -- Shell side of window focus: park/restore the half-typed input line so it * travels with its window.
- `user_str_ok` (function) `headers/kernel.h:709` `int user_str_ok(unsigned long p, unsigned long maxlen);`
- `mm_setup_protections` (function) `headers/kernel.h:712` `void mm_setup_protections(void);` -- Shell side of window focus: park/restore the half-typed input line so it * travels with its window.
- `pt_page_alloc` (function) `headers/kernel.h:713` `void *pt_page_alloc(void);`
- `pt_page_free` (function) `headers/kernel.h:714` `void pt_page_free(void *ptr);`
- `mm_user_pte_update` (function) `headers/kernel.h:715` `void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3);`
- `mm_user_set_exec` (function) `headers/kernel.h:716` `void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3);`
- `swap_out` (function) `headers/kernel.h:719` `int swap_out(unsigned long window_sz);` -- extern volatile int shell_fg_active; /*
- `swap_in` (function) `headers/kernel.h:720` `int swap_in(void);`
- `elf_load` (function) `headers/kernel.h:766` `void *elf_load(void *data, unsigned size, void **base_out);`
- `load_exec_elf` (function) `headers/kernel.h:767` `void *load_exec_elf(void *data, unsigned size);` -- Heap/mmap ceiling: the shared-library region starts here with the graphics tail above it, so brk growth and the mmap...
- `elf_wants_process` (function) `headers/kernel.h:768` `int elf_wants_process(const void *data, unsigned size);` -- Heap/mmap ceiling: the shared-library region starts here with the graphics tail above it, so brk growth and the mmap...
- `load_exec_elf_into` (function) `headers/kernel.h:769` `void *load_exec_elf_into(void *data, unsigned size, unsigned long cr3, unsigned long *brk_out, unsigned long *base_out);` -- Heap/mmap ceiling: the shared-library region starts here with the graphics tail above it, so brk growth and the mmap...
- `ldso_bind_into` (function) `headers/kernel.h:778` `int ldso_bind_into(void *data, unsigned size, unsigned long base, unsigned long cr3, vma_ctx_t *vma);` -- Minimal dynamic linker (T8 ld.so, kernel/loader.c). bind_into maps the DT_NEEDED libraries of an already-copied...
- `ldso_pseudo_stat` (function) `headers/kernel.h:780` `int ldso_pseudo_stat(int ino, unsigned long *size_out);`
- `ldso_pseudo_read` (function) `headers/kernel.h:781` `int ldso_pseudo_read(int ino, void *dst, unsigned long off, unsigned len);`
- `pt_clone_user_empty` (function) `headers/kernel.h:782` `unsigned long pt_clone_user_empty(void);`
- `mm_user_ensure_page` (function) `headers/kernel.h:783` `int mm_user_ensure_page(unsigned long cr3, unsigned long va);`
- `mm_user_map_page` (function) `headers/kernel.h:784` `int mm_user_map_page(unsigned long cr3, unsigned long va, unsigned long phys, int write, int exec);`
- `mm_file_fault` (function) `headers/kernel.h:786` `int mm_file_fault(unsigned long cr3, unsigned long va);`
- `mm_file_break` (function) `headers/kernel.h:787` `int mm_file_break(unsigned long cr3, unsigned long va);`
- `mm_file_page_phys` (function) `headers/kernel.h:788` `unsigned long mm_file_page_phys(unsigned long cr3, unsigned long va);`
- `mm_file_range_release` (function) `headers/kernel.h:789` `void mm_file_range_release(unsigned long cr3, unsigned long base, unsigned long len, int ino, unsigned long off, int...`
- `mm_demand_pte` (function) `headers/kernel.h:805` `unsigned long mm_demand_pte(unsigned long prot);` -- Anonymous demand paging (docs/spec/kernel.md): a reserved page is a non-present PTE carrying PTE_DEMAND and the...
- `mm_anon_reserve` (function) `headers/kernel.h:806` `int mm_anon_reserve(unsigned long cr3, unsigned long base, unsigned long len, unsigned long prot);`
- `mm_anon_fault` (function) `headers/kernel.h:808` `int mm_anon_fault(unsigned long cr3, unsigned long va, int write);`
- `pt_page_owned` (function) `headers/kernel.h:809` `int pt_page_owned(unsigned long phys);`
- `mm_anon_release` (function) `headers/kernel.h:810` `void mm_anon_release(unsigned long cr3, unsigned long base, unsigned long len);`
- `cow_drop_ref` (function) `headers/kernel.h:811` `int cow_drop_ref(unsigned long phys);`
- `refused` (function) `headers/kernel.h:817` `* refused (see kernel/mm/paging.c for the fail-closed list). */ unsigned long kmm_map_device(unsigned long phys...`
- `kmm_make_uncached` (function) `headers/kernel.h:819` `int kmm_make_uncached(unsigned long phys, unsigned long len);`
- `mm_copy_user_page` (function) `headers/kernel.h:820` `int mm_copy_user_page(unsigned long dst_cr3, unsigned long src_cr3, unsigned long va);`
- `fault` (function) `headers/kernel.h:824` `* fixes one write fault (0 = resume), cow_release_window drops a * dying window's shares ahead of pt_free_user. */...`
- `cow_resolve` (function) `headers/kernel.h:827` `int cow_resolve(unsigned long cr3, unsigned long va);`
- `user_page_present` (function) `headers/kernel.h:828` `int user_page_present(unsigned long cr3, unsigned long va);`
- `cow_release_window` (function) `headers/kernel.h:829` `void cow_release_window(unsigned long cr3);`
- `cow_shared` (function) `headers/kernel.h:830` `int cow_shared(void);`
- `cow_page_shared` (function) `headers/kernel.h:831` `int cow_page_shared(unsigned long phys);`
- `syscall_init` (function) `headers/kernel.h:834` `void syscall_init(void);` -- Copy-on-write fork (kernel/mm/cow.c): share on fork, privatize on first write. cow_fork_window builds the child...
- `ksyscall` (function) `headers/kernel.h:838` `long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);`
- `syscall_trace_enabled` (function) `headers/kernel.h:839` `long syscall_trace_enabled(void);`
- `syscall_trace_set` (function) `headers/kernel.h:840` `void syscall_trace_set(int on);`
- `syscall_trace_verbose_enabled` (function) `headers/kernel.h:841` `long syscall_trace_verbose_enabled(void);`
- `syscall_trace_verbose_set` (function) `headers/kernel.h:842` `void syscall_trace_verbose_set(int on);`
- `syscall_trace_shown` (function) `headers/kernel.h:843` `unsigned long syscall_trace_shown(void);`
- `syscall_name` (function) `headers/kernel.h:844` `const char *syscall_name(long n);`
- `kfd_get` (function) `headers/kernel.h:865` `KFILE *kfd_get(int fd);`
- `kfd_put` (function) `headers/kernel.h:866` `void kfd_put(KFILE *f);`
- `kfd_override` (function) `headers/kernel.h:867` `KFILE *kfd_override(int fd, KFILE *f);`
- `kpipe_pair` (function) `headers/kernel.h:868` `int kpipe_pair(KFILE **rend_out, KFILE **wend_out);`
- `kpipe_empty_wopen` (function) `headers/kernel.h:869` `int kpipe_empty_wopen(KFILE *f);`
- `kpipe_is_write_end` (function) `headers/kernel.h:870` `int kpipe_is_write_end(KFILE *f);`
- `kpipe_state` (function) `headers/kernel.h:873` `int kpipe_state(KFILE *f, unsigned *avail, unsigned *space, int *wopen, int *ropen);` -- Pipe snapshot for poll and the blocking syscall layer: bytes waiting, * free space, writer open, reader open. -1 on...
- `kfd_poll_revents` (function) `headers/kernel.h:876` `int kfd_poll_revents(int fd);` -- poll(2) readiness bits of a non-socket descriptor (kernel/syscalls.c): * pipes, eventfds, files and the console...
- `kevent_create` (function) `headers/kernel.h:882` `KFILE *kevent_create(unsigned long long initval, int semaphore);` -- eventfd(2) descriptions (docs/spec/smp-sched.md): create with an initial counter, read (0 or -EAGAIN when the...
- `kevent_read` (function) `headers/kernel.h:883` `long kevent_read(KFILE *f, unsigned long long *out);`
- `kevent_write` (function) `headers/kernel.h:884` `long kevent_write(KFILE *f, unsigned long long v);`
- `kevent_readable` (function) `headers/kernel.h:885` `int kevent_readable(KFILE *f);`
- `kevent_writable` (function) `headers/kernel.h:886` `int kevent_writable(KFILE *f);`
- `fd_lock` (function) `headers/kernel.h:889` `* fd_lock (never nested, never held across yields);`
- `C` (function) `headers/kernel.h:903` `* it with pointer subtraction in C (undefined behaviour). The value is
 * a link-time difference,...`
- `ktime_us` (function) `headers/kernel.h:913` `unsigned long ktime_us(void);`
- `wall_us_now` (function) `headers/kernel.h:914` `unsigned long wall_us_now(void);`
- `bootlog_mark` (function) `headers/kernel.h:917` `void bootlog_mark(const char *name);` -- it with pointer subtraction in C (undefined behaviour).
- `bootlog_report` (function) `headers/kernel.h:918` `void bootlog_report(void);`
- `pcspk_init` (function) `headers/kernel.h:921` `void pcspk_init(void);` -- static inline unsigned long ramdisk_image_size(void) { return (unsigned long)ramdisk_size; } /*
- `pcspk_tone` (function) `headers/kernel.h:922` `void pcspk_tone(unsigned freq);`
- `pcspk_off` (function) `headers/kernel.h:923` `void pcspk_off(void);`
- `pcspk_set_volume` (function) `headers/kernel.h:924` `void pcspk_set_volume(unsigned volume);`
- `pcspk_get_volume` (function) `headers/kernel.h:925` `unsigned pcspk_get_volume(void);`
- `rtc_read_tod` (function) `headers/kernel.h:928` `int rtc_read_tod(int *hour, int *min, int *sec);` -- unsigned long wall_us_now(void); /*
- `ide_init` (function) `headers/kernel.h:931` `void ide_init(void);` -- void bootlog_mark(const char *name); void bootlog_report(void); /*
- `ide_read_sectors` (function) `headers/kernel.h:932` `int ide_read_sectors(unsigned int lba, unsigned int count, void *buf);`
- `ide_write_sectors` (function) `headers/kernel.h:933` `int ide_write_sectors(unsigned int lba, unsigned int count, const void *buf);`
- `ide_read_sector` (function) `headers/kernel.h:934` `int ide_read_sector(unsigned int lba, void *buf);`
- `ide_write_sector` (function) `headers/kernel.h:935` `int ide_write_sector(unsigned int lba, const void *buf);`
- `ide_total_sectors` (function) `headers/kernel.h:936` `unsigned int ide_total_sectors(void);`
- `ide_present` (function) `headers/kernel.h:937` `int ide_present(void);`
- `block_init` (function) `headers/kernel.h:940` `void block_init(void);`
- `block_read` (function) `headers/kernel.h:941` `int block_read(unsigned int block_num, void *buf);`
- `block_write` (function) `headers/kernel.h:942` `int block_write(unsigned int block_num, const void *buf);`
- `block_read_multi` (function) `headers/kernel.h:943` `int block_read_multi(unsigned int block_num, unsigned int count, void *buf);`
- `block_write_multi` (function) `headers/kernel.h:944` `int block_write_multi(unsigned int block_num, unsigned int count, const void *buf);`
- `block_total` (function) `headers/kernel.h:945` `unsigned int block_total(void);`
- `k_user_fault_return` (function) `headers/kernel.h:948` `void k_user_fault_return(void);` -- int  ide_read_sector(unsigned int lba, void *buf); int  ide_write_sector(unsigned int lba, const void *buf)...

## headers/kernel/console_in.h
Imported by: `headers/shell.h`, `kernel/console_in.c`, `kernel/shell.c`
- `Consumers` (function) `headers/kernel/console_in.h:7` `* Consumers (shell prompt, editor, SPAWN waits, GETC_RAW syscall) include * this header instead of reaching into...`
- `console_history_page` (function) `headers/kernel/console_in.h:19` `void console_history_page(int dir);` -- Docstring: Page the console history by one screen (dir -1 up, +1 down).
- `console_peek` (function) `headers/kernel/console_in.h:22` `int console_peek(void);` -- Docstring: Page the console history by one screen (dir -1 up, +1 down).
- `console_raw_try` (function) `headers/kernel/console_in.h:26` `int console_raw_try(void);` -- Docstring: Raw console multiplexer backing GETC_RAW: same sources, * no line buffering, echo or scrollback. try...
- `console_raw_get` (function) `headers/kernel/console_in.h:27` `int console_raw_get(void);`
- `console_job_try` (function) `headers/kernel/console_in.h:30` `int console_job_try(void);` -- Docstring: Raw console multiplexer backing GETC_RAW: same sources, * no line buffering, echo or scrollback. try...
- `console_job_get` (function) `headers/kernel/console_in.h:31` `int console_job_get(void);`
- `console_ungetc` (function) `headers/kernel/console_in.h:35` `void console_ungetc(unsigned char c);` -- Docstring: Push one byte back into the console FIFO; the next * console_getc/console_peek serves it first.
- `console_stdin_push` (function) `headers/kernel/console_in.h:42` `int console_stdin_push(const char *data, unsigned long len);` -- Docstring: Pipeline stdin override: the next console_getc calls serve len bytes from data, then report EOF (-1)...
- `console_stdin_clear` (function) `headers/kernel/console_in.h:43` `void console_stdin_clear(void);`
- `console_stdin_active` (function) `headers/kernel/console_in.h:44` `int console_stdin_active(void);`

## headers/kernel/vga_cursor.h
Imported by: `kernel/vga_cursor.c`, `kernel/vga_fb.c`
- `cursor_over` (function) `headers/kernel/vga_cursor.h:16` `int cursor_over(int x0, int y0, int w, int h);` -- Docstring: vga_cursor.h -- boundary of the pointer sprite layer (kernel/vga_cursor.c).
- `cursor_place` (function) `headers/kernel/vga_cursor.h:19` `void cursor_place(int mx, int my);` -- (kernel/vga_cursor.c).
- `cursor_move` (function) `headers/kernel/vga_cursor.h:22` `void cursor_move(int mx, int my);` -- #include "kernel.h" /** Docstring: Pointer sprite dimensions in pixels. #define CURSOR_W 8 #define CURSOR_H 8 /**...
- `cursor_erase` (function) `headers/kernel/vga_cursor.h:25` `void cursor_erase(void);` -- /** Docstring: Pointer sprite dimensions in pixels. #define CURSOR_W 8 #define CURSOR_H 8 /** Docstring: True when...
- `cursor_invalidate` (function) `headers/kernel/vga_cursor.h:28` `void cursor_invalidate(void);` -- /** Docstring: True when the sprite overlaps the given screen rectangle. int cursor_over(int x0, int y0, int w, int...
- `cursor_note_repaint` (function) `headers/kernel/vga_cursor.h:31` `void cursor_note_repaint(int x0, int y0, int w, int h);` -- /** Docstring: Paint the pointer at mx/my unconditionally. void cursor_place(int mx, int my); /** Docstring...

## headers/ktime.h
Imported by: `kernel/syscalls.c`, `kernel/time.c`, `tests/test_ktime.c`
- `ktime_us_from_delta` (function) `headers/ktime.h:19` `static inline unsigned long ktime_us_from_delta(unsigned long delta_ticks,
                      ...`
- `wall_us_from_parts` (function) `headers/ktime.h:30` `static inline unsigned long wall_us_from_parts(unsigned long base_sec,
                          ...` -- wall_us_from_parts: wall-clock microseconds from an RTC-anchored base. base_sec is the last seen RTC second...

## headers/ldso.h
Imported by: `headers/kernel.h`, `kernel/ldso_parse.c`, `kernel/loader.c`, `kernel/mm/paging.c`, `tests/test_ldso.c`
- `ldso_find_dynamic` (function) `headers/ldso.h:86` `int ldso_find_dynamic(const unsigned char *file, unsigned long long fsize, unsigned long long *dyn_off, unsigned...` -- Docstring: Locate the PT_DYNAMIC file range.
- `ldso_vaddr_to_offset` (function) `headers/ldso.h:92` `int ldso_vaddr_to_offset(const unsigned char *file, unsigned long long fsize, unsigned long long va, unsigned long...` -- Docstring: Translate a link VA through PT_LOAD into a file offset.
- `ldso_segments` (function) `headers/ldso.h:97` `int ldso_segments(const unsigned char *file, unsigned long long fsize, LdsoSeg *segs, unsigned ncap, unsigned *nseg);` -- Docstring: Collect PT_LOAD spans (at most ncap) for reservation and * GOT-range checks.
- `ldso_scan_dynamic` (function) `headers/ldso.h:103` `int ldso_scan_dynamic(const unsigned char *file, unsigned long long fsize, unsigned long long dyn_off, unsigned long...` -- Docstring: Walk the dynamic array into info.
- `ldso_sym_count` (function) `headers/ldso.h:110` `int ldso_sym_count(const unsigned char *file, unsigned long long fsize, unsigned long long hash_off, unsigned *nsyms);` -- Docstring: Read the SYSV hash header at a file offset into bucket and chain counts.
- `ldso_copy_str` (function) `headers/ldso.h:116` `int ldso_copy_str(const unsigned char *file, unsigned long long fsize, unsigned long long strtab_off, unsigned long...` -- Docstring: Bounded copy of one dynamic string (NEEDED/SONAME/symbol).
- `ldso_sym_lookup` (function) `headers/ldso.h:124` `int ldso_sym_lookup(const unsigned char *file, unsigned long long fsize, unsigned long long symtab_off, unsigned...` -- Docstring: Linear search of a dynamic symbol table by name.
- `ldso_rela_count` (function) `headers/ldso.h:132` `int ldso_rela_count(const LdsoDynInfo *info, unsigned *nrela);` -- Docstring: Validate the RELA header triple and report the row count.
- `ldso_read_rela` (function) `headers/ldso.h:137` `int ldso_read_rela(const unsigned char *file, unsigned long long fsize, unsigned long long rela_off, unsigned nrela...` -- Docstring: Read one RELA row with full validation: row inside the table, type GLOB_DAT/JUMP_SLOT (anything else is...
- `ldso_basename` (function) `headers/ldso.h:144` `void ldso_basename(char *out, const char *src);` -- Docstring: Basename normalization for registry keys ("a/b.so" to "b.so", bounded, always terminated).

## headers/leakcheck.h
Depends on: `kernel/string.c`
Imported by: `progs/file/file.c`, `progs/vedit/vedit.c`, `tests/test_leakcheck.c`
- `kmalloc` (function) `headers/leakcheck.h:79` `extern void *kmalloc(unsigned long size);` -- ifdef MINIOS_LK_KERNEL
- `kfree` (function) `headers/leakcheck.h:80` `extern void kfree(void *ptr);`
- `kprintf` (function) `headers/leakcheck.h:81` `extern int kprintf(const char *fmt, ...);`
- `lk_malloc` (function) `headers/leakcheck.h:96` `void *lk_malloc(size_t size, const char *file, int line)` -- #define MINIOS_LK_RAW_ALLOC(sz) kmalloc((unsigned long)(sz)) #define MINIOS_LK_RAW_FREE(p) kfree(p) #else #include...
- `lk_unlink` (function) `headers/leakcheck.h:110` `static void lk_unlink(lk_block_t *b)` -- void *lk_malloc(size_t size, const char *file, int line) { lk_block_t *b = (lk_block_t *)MINIOS_LK_RAW_ALLOC(size +...
- `lk_find` (function) `headers/leakcheck.h:120` `static lk_block_t *lk_find(void *ptr)` -- return b + 1; } /** Docstring: unlink one record from the live-block list. static void lk_unlink(lk_block_t *b) { if...
- `lk_free` (function) `headers/leakcheck.h:130` `void lk_free(void *ptr)` -- if (b->next) b->next->prev = b->prev; } /** Docstring: find the record owning ptr by scanning for its payload base....
- `lk_realloc` (function) `headers/leakcheck.h:143` `void *lk_realloc(void *ptr, size_t size, const char *file, int line)` -- /** Docstring: tracked free, passes unknown blocks to the raw backend. void lk_free(void *ptr) { lk_block_t *b; if...
- `lk_print` (function) `headers/leakcheck.h:186` `static void lk_print(const char *reason, const lk_block_t *b)` -- return ptr; } q = lk_malloc(size, file, line); if (q) { d = (unsigned char *)q; s = (unsigned char *)ptr; keep =...
- `lk_dumpmem` (function) `headers/leakcheck.h:197` `void lk_dumpmem(void)` -- } /** Docstring: print one live record on the configured pipe. static void lk_print(const char *reason, const...
- `lk_live_count` (function) `headers/leakcheck.h:206` `unsigned long lk_live_count(void)` -- b->file, b->line, (unsigned long)b->size, (const void *)(b + 1)); #endif } /** Docstring: report every block still...
- `lk_live_bytes` (function) `headers/leakcheck.h:217` `unsigned long lk_live_bytes(void)` -- } /** Docstring: count of blocks still live. unsigned long lk_live_count(void) { unsigned long n = 0; lk_block_t *b...

## headers/lz4_kernel.h
Imported by: `fs/minifs.c`, `kernel/lz4_kernel.c`, `kernel/mm/swap.c`, `kernel/syscalls.c`
- `LZ4_compress_default` (function) `headers/lz4_kernel.h:4` `int LZ4_compress_default(const char *src, char *dst, int srcSize, int dstCapacity);`
- `LZ4_compressBound` (function) `headers/lz4_kernel.h:5` `int LZ4_compressBound(int inputSize);`
- `LZ4_decompress_safe` (function) `headers/lz4_kernel.h:6` `int LZ4_decompress_safe(const char *src, char *dst, int compressedSize, int dstCapacity);`

## headers/minifetch.h
Imported by: `kernel/minifetch.c`, `kernel/shell.c`
- `shell_cmd_minifetch` (function) `headers/minifetch.h:14` `void shell_cmd_minifetch(void);`

## headers/minifs.h
Imported by: `fs/ext4.c`, `fs/fat32.c`, `fs/fsimg.c`, `fs/kfile.c`, `fs/minifs.c`, `fs/vfs.c`, `kernel.c`, `kernel/loader.c`, `kernel/minifetch.c`, `kernel/mm/paging.c`, `kernel/shell.c`, `kernel/spawn.c`, `kernel/syscalls.c`, `tests/test_ext4.c`, `tests/test_fat32.c`
- `minifs_compress` (function) `headers/minifs.h:30` `unsigned int minifs_compress(const void *src, unsigned int src_len, void *dst, unsigned int dst_cap);`
- `minifs_decompress` (function) `headers/minifs.h:31` `unsigned int minifs_decompress(const void *src, unsigned int src_len, void *dst, unsigned int dst_cap);`
- `minifs_init` (function) `headers/minifs.h:117` `void minifs_init(void);`
- `minifs_mount` (function) `headers/minifs.h:118` `int minifs_mount(void);`
- `minifs_sync` (function) `headers/minifs.h:119` `int minifs_sync(void);`
- `minifs_is_mounted` (function) `headers/minifs.h:120` `int minifs_is_mounted(void);`
- `minifs_create` (function) `headers/minifs.h:122` `int minifs_create(const char *path, unsigned short mode);`
- `minifs_mkdir` (function) `headers/minifs.h:123` `int minifs_mkdir(const char *path, unsigned short mode);`
- `minifs_unlink` (function) `headers/minifs.h:124` `int minifs_unlink(const char *path);`
- `minifs_rmdir` (function) `headers/minifs.h:125` `int minifs_rmdir(const char *path);`
- `refuses` (function) `headers/minifs.h:128` `* An existing file dst refuses (no silent overwrite);`
- `minifs_rename` (function) `headers/minifs.h:130` `int minifs_rename(const char *oldpath, const char *newpath);` -- Docstring: Move one MiniFS directory entry to a new parent/name, keeping its inode (no data moves).
- `minifs_read` (function) `headers/minifs.h:131` `int minifs_read(int inode_num, void *buf, unsigned int offset, unsigned int len);`
- `minifs_write` (function) `headers/minifs.h:132` `int minifs_write(int inode_num, const void *buf, unsigned int offset, unsigned int len);`
- `minifs_truncate` (function) `headers/minifs.h:133` `int minifs_truncate(int inode_num, unsigned int new_size);`
- `minifs_stat` (function) `headers/minifs.h:134` `int minifs_stat(int inode_num, MiniFSInode *out);`
- `minifs_access` (function) `headers/minifs.h:135` `int minifs_access(const char *path);`
- `minifs_resolve_path` (function) `headers/minifs.h:137` `int minifs_resolve_path(const char *path);`
- `minifs_dir_lookup` (function) `headers/minifs.h:138` `int minifs_dir_lookup(int dir_inode, const char *name);`
- `minifs_dir_add_entry` (function) `headers/minifs.h:139` `int minifs_dir_add_entry(int dir_inode, const char *name, int child_inode, unsigned char type);`
- `minifs_dir_remove_entry` (function) `headers/minifs.h:140` `int minifs_dir_remove_entry(int dir_inode, const char *name);`
- `minifs_dir_read` (function) `headers/minifs.h:141` `int minifs_dir_read(int dir_inode, int index, MiniFSDirEntry *out, char *name_out);`
- `minifs_alloc_block` (function) `headers/minifs.h:143` `int minifs_alloc_block(void);`
- `minifs_free_block` (function) `headers/minifs.h:144` `void minifs_free_block(unsigned int block);`
- `minifs_alloc_inode` (function) `headers/minifs.h:145` `int minifs_alloc_inode(void);`
- `minifs_free_inode` (function) `headers/minifs.h:146` `void minifs_free_inode(int inode_num);`
- `minifs_inode_get_block` (function) `headers/minifs.h:147` `int minifs_inode_get_block(MiniFSInode *inode, unsigned int logical_block, unsigned int *phys_block);`
- `minifs_inode_alloc_block` (function) `headers/minifs.h:148` `int minifs_inode_alloc_block(MiniFSInode *inode, unsigned int logical_block);`
- `minifs_journal_begin` (function) `headers/minifs.h:150` `void minifs_journal_begin(unsigned int txn_id);`
- `minifs_journal_add_block` (function) `headers/minifs.h:151` `void minifs_journal_add_block(unsigned int block);`
- `minifs_journal_touch` (function) `headers/minifs.h:152` `void minifs_journal_touch(unsigned int phys);`
- `minifs_journal_commit` (function) `headers/minifs.h:153` `int minifs_journal_commit(unsigned int txn_id);`
- `minifs_journal_clear` (function) `headers/minifs.h:154` `void minifs_journal_clear(void);`
- `minifs_journal_abort` (function) `headers/minifs.h:155` `void minifs_journal_abort(void);`
- `minifs_journal_recover` (function) `headers/minifs.h:156` `void minifs_journal_recover(void);`
- `minifs_file_open` (function) `headers/minifs.h:158` `MiniFSFile *minifs_file_open(int inode_num, int flags);`
- `minifs_file_close` (function) `headers/minifs.h:159` `int minifs_file_close(MiniFSFile *f);`
- `minifs_get_lba_start` (function) `headers/minifs.h:161` `unsigned int minifs_get_lba_start(void);`
- `minifs_get_total_blocks` (function) `headers/minifs.h:162` `unsigned int minifs_get_total_blocks(void);`
- `minifs_usage` (function) `headers/minifs.h:164` `void minifs_usage(unsigned int *free_b, unsigned int *total_b, unsigned int *free_i, unsigned int *total_i);` -- void minifs_journal_begin(unsigned int txn_id); void minifs_journal_add_block(unsigned int block); void...

## headers/net.h
Imported by: `drivers/virtio_net.c`, `headers/net/rtl8139.h`, `headers/tls_port.h`, `kernel.c`, `kernel/minifetch.c`, `kernel/shell.c`, `kernel/syscalls.c`, `net/net.c`, `net/rtl8139.c`
- `ring` (function) `headers/net.h:58` `* ring (below) is the rtl8139's 8 KB hardware ring, unrelated. */ #define NET_SOCK_RX_BUF 16384 #define...`
- `net_sys_is_socket` (function) `headers/net.h:101` `int net_sys_is_socket(long fd);` -- net_connect / socket fds are NET_FD_BASE + index for Linux syscalls and * 0..NET_SOCKETS-1 for the libc-style...
- `net_sys_setsockopt` (function) `headers/net.h:102` `long net_sys_setsockopt(long fd, long level, long name, long val, long len);`
- `net_sys_getsockopt` (function) `headers/net.h:103` `long net_sys_getsockopt(long fd, long level, long name, long val, long lenp);`
- `net_sys_getsockname` (function) `headers/net.h:104` `long net_sys_getsockname(long fd, long addr, long lenp);`
- `net_sys_getpeername` (function) `headers/net.h:105` `long net_sys_getpeername(long fd, long addr, long lenp);`
- `net_sys_sendmsg` (function) `headers/net.h:106` `long net_sys_sendmsg(long fd, long msg, long flags);`
- `net_sys_sendmmsg` (function) `headers/net.h:107` `long net_sys_sendmmsg(long fd, long vec, long vlen, long flags);`
- `net_sys_fcntl` (function) `headers/net.h:108` `long net_sys_fcntl(long fd, long cmd, long arg);`
- `net_sys_ioctl` (function) `headers/net.h:109` `long net_sys_ioctl(long fd, long req, long arg);`
- `net_register_symbols` (function) `headers/net.h:110` `void net_register_symbols(void);`
- `net_cmd_status` (function) `headers/net.h:113` `void net_cmd_status(void);` -- void net_init(void); /* Linux socket ABI entry points (kernel/syscalls.c routes to them). int...
- `net_cmd_ping` (function) `headers/net.h:114` `void net_cmd_ping(const char *ip_text);`
- `net_get_addrs` (function) `headers/net.h:115` `void net_get_addrs(unsigned char mac_out[NET_ETH_ALEN], unsigned char ip_out[4]);`
- `net_cmd_dns` (function) `headers/net.h:116` `void net_cmd_dns(const char *host);`
- `net_open` (function) `headers/net.h:119` `int net_open(void);` -- long net_sys_getpeername(long fd, long addr, long lenp); long net_sys_sendmsg(long fd, long msg, long flags); long...
- `net_connect` (function) `headers/net.h:120` `int net_connect(const char *host, unsigned short port);`
- `net_send` (function) `headers/net.h:121` `int net_send(int fd, const char *buf, int len);`
- `net_recv` (function) `headers/net.h:122` `int net_recv(int fd, char *buf, int len);`
- `net_recv_timeout` (function) `headers/net.h:124` `int net_recv_timeout(int fd, char *buf, int len, unsigned long timeout_ms);` -- void net_register_symbols(void); /* Shell commands void net_cmd_status(void); void net_cmd_ping(const char...
- `net_close` (function) `headers/net.h:125` `void net_close(int fd);`
- `demux` (function) `headers/net.h:131` `* segment through the production demux (httpd selftest). */ int net_listen(unsigned short port);`
- `net_accept_nb` (function) `headers/net.h:133` `int net_accept_nb(int fd);`
- `net_accept` (function) `headers/net.h:134` `int net_accept(int fd, unsigned long timeout_ms);`
- `net_sock_state` (function) `headers/net.h:135` `int net_sock_state(int fd);`
- `net_sock_seq` (function) `headers/net.h:136` `int net_sock_seq(int fd, unsigned *seq_out, unsigned *ack_out);`
- `net_test_inject_tcp` (function) `headers/net.h:137` `int net_test_inject_tcp(const unsigned char peer[4], unsigned short pport, unsigned short lport, unsigned char...`
- `net_sys_socket` (function) `headers/net.h:142` `long net_sys_socket(long a1, long a2, long a3);` -- index, or -1). net_accept_nb takes an established child without waiting; net_accept waits up to timeout_ms....
- `net_sys_connect` (function) `headers/net.h:143` `long net_sys_connect(long fd, long sockaddr, long addrlen);`
- `net_sys_bind` (function) `headers/net.h:144` `long net_sys_bind(long fd, long sockaddr, long addrlen);`
- `net_sys_listen` (function) `headers/net.h:145` `long net_sys_listen(long fd, long backlog);`
- `net_sys_accept` (function) `headers/net.h:146` `long net_sys_accept(long fd, long sockaddr, long addrlen);`
- `net_sys_sendto` (function) `headers/net.h:147` `long net_sys_sendto(long fd, long buf, long len, long flags, long to, long tolen);`
- `net_sys_recvfrom` (function) `headers/net.h:148` `long net_sys_recvfrom(long fd, long buf, long len, long flags, long from, long fromlen);`
- `net_sys_shutdown` (function) `headers/net.h:149` `long net_sys_shutdown(long fd, long how);`
- `net_sys_close` (function) `headers/net.h:150` `long net_sys_close(long fd);`
- `net_sys_poll` (function) `headers/net.h:151` `long net_sys_poll(long fds, long nfds, long timeout_ms);`
- `net_sys_dns` (function) `headers/net.h:152` `long net_sys_dns(long host);`
- `net_time_ms` (function) `headers/net.h:155` `unsigned long net_time_ms(void);` -- /* Linux syscall ABI (sockaddr_in layout matches Linux) long net_sys_socket(long a1, long a2, long a3); long...
- `net_rx_handle_frame` (function) `headers/net.h:159` `void net_rx_handle_frame(const unsigned char *frame, unsigned len);` -- Demux entry point the rtl8139 driver (rtl8139.c) calls for every * frame drained from the RX ring; lives in net.c.
- `stack` (function) `headers/net.h:162` `* the stack (dropped fragments);`
- `tls_free_fd` (function) `headers/net.h:170` `void tls_free_fd(int fd);` -- TLS sessions attached to socket fds (tls.c); net_sys_close frees them.

## headers/net/rtl8139.h
Depends on: `headers/net.h`
Imported by: `net/net.c`, `net/rtl8139.c`
- `rtl_present` (function) `headers/net/rtl8139.h:18` `int rtl_present(void);` -- rtl8139 NIC driver interface.
- `rtl_init` (function) `headers/net/rtl8139.h:21` `void rtl_init(void);` -- This header is the boundary between the polled rtl8139 driver (rtl8139.c) and the protocol stack (net.c).
- `rtl_send` (function) `headers/net/rtl8139.h:25` `int rtl_send(const unsigned char *frame, unsigned len);` -- Transmit one raw Ethernet frame.
- `net_rx_handle_frame` (function) `headers/net/rtl8139.h:28` `* net_rx_handle_frame (the protocol demux in net.c). */ void rtl_poll(void);`
- `rtl_get_mac` (function) `headers/net/rtl8139.h:32` `void rtl_get_mac(unsigned char out[NET_ETH_ALEN]);` -- Drain the RX ring once; every received frame is handed to * net_rx_handle_frame (the protocol demux in net.c). void...
- `rtl_iobase` (function) `headers/net/rtl8139.h:35` `unsigned short rtl_iobase(void);` -- Drain the RX ring once; every received frame is handed to * net_rx_handle_frame (the protocol demux in net.c). void...
- `rtl_counters` (function) `headers/net/rtl8139.h:38` `void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames);` -- Drain the RX ring once; every received frame is handed to * net_rx_handle_frame (the protocol demux in net.c). void...

## headers/panic.h
Imported by: `kernel/panic.c`, `tests/test_panic.c`
- `panic_hex_str` (function) `headers/panic.h:28` `static inline int panic_hex_str(char *buf, int cap, unsigned long v, int digits)` -- Docstring: Format an unsigned long as fixed-width lowercase hex into buf, writing exactly digits characters plus a...
- `panic_backtrace` (function) `headers/panic.h:51` `static inline int panic_backtrace(unsigned long rbp, panic_valid_fn valid,
        unsigned long ...` -- Docstring: Walk up to max frame pointers from rbp, storing each frame's return address (*(rbp+8)) into out.

## headers/pcache.h
Imported by: `fs/minifs.c`, `fs/pcache.c`, `kernel.c`, `kernel/loader.c`, `kernel/mm/paging.c`, `kernel/sched.c`, `kernel/shell.c`, `kernel/syscalls.c`, `tests/test_pcache.c`
- `pcache_init` (function) `headers/pcache.h:28` `void pcache_init(void);` -- Docstring: Allocate the page pool; disabled (all calls fail closed) when the heap cannot spare it, exactly like the...
- `pcache_lookup` (function) `headers/pcache.h:32` `int pcache_lookup(int ino, unsigned index);` -- Docstring: Find a cached page without reserving.
- `pcache_get` (function) `headers/pcache.h:42` `int pcache_get(int ino, unsigned index, int *is_new);` -- Docstring: Get a page, pinned with one ref.
- `pcache_publish` (function) `headers/pcache.h:51` `int pcache_publish(int ino, unsigned index, const unsigned char *data);` -- Docstring: Publish a privately filled page into the cache atomically.
- `pcache_put` (function) `headers/pcache.h:55` `void pcache_put(int slot);` -- Docstring: Drop one ref taken by get.
- `pcache_ref` (function) `headers/pcache.h:61` `int pcache_ref(int ino, unsigned index);` -- Docstring: Take one more ref on a cached page without allocating.
- `pcache_unmap` (function) `headers/pcache.h:69` `void pcache_unmap(int ino, unsigned index);` -- Docstring: Drop the ref a mapping holds on one cached page.
- `match` (function) `headers/pcache.h:75` `* a phys match (owned, ref dropped unless already zero), 0 * otherwise. */ int pcache_put_if(int ino, unsigned...`
- `pcache_ref_if` (function) `headers/pcache.h:83` `int pcache_ref_if(int ino, unsigned index, unsigned long phys);` -- Docstring: Take one more ref only when the cached page is the exact phys the caller shares.
- `pcache_owns_phys` (function) `headers/pcache.h:88` `int pcache_owns_phys(unsigned long phys);` -- Docstring: True when phys is a cache pool page.
- `pcache_data` (function) `headers/pcache.h:93` `unsigned char *pcache_data(int slot);` -- Docstring: Page data for a slot from get/lookup, 0 on a bad slot.
- `pcache_mark_dirty` (function) `headers/pcache.h:98` `void pcache_mark_dirty(int slot);` -- Docstring: Mark a pinned page dirty.
- `pcache_invalidate_ino` (function) `headers/pcache.h:102` `void pcache_invalidate_ino(int ino);` -- Docstring: Drop every page of an inode (truncate/unlink). * Dirty pages drop with them until slice 3 teaches writeback.
- `pcache_stats` (function) `headers/pcache.h:106` `void pcache_stats(unsigned long *pages_out, unsigned long *hits_out, unsigned long *miss_out, unsigned long...` -- Docstring: Snapshot for the mem builtin and BDD: live pages, * cumulative hits/misses/evictions, dirty count.

## headers/pcm2.h
Imported by: `drivers/pcm2.c`, `drivers/sb16.c`, `kernel/sched.c`, `kernel/shell.c`, `kernel/syscalls.c`
- `pcm2_active` (function) `headers/pcm2.h:77` `int pcm2_active(void);`
- `pcm2_open` (function) `headers/pcm2.h:78` `int pcm2_open(unsigned flags, int owner);`
- `pcm2_write` (function) `headers/pcm2.h:79` `int pcm2_write(const unsigned char *user, unsigned len, int owner);`
- `pcm2_close` (function) `headers/pcm2.h:80` `void pcm2_close(int owner);`
- `pcm2_irq` (function) `headers/pcm2.h:81` `void pcm2_irq(void);`
- `pcm2_poll` (function) `headers/pcm2.h:82` `void pcm2_poll(void);`
- `pcm2_counters` (function) `headers/pcm2.h:83` `void pcm2_counters(pcm2_counters_t *out);`

## headers/pcm_ring.h
Imported by: `drivers/pcm2.c`, `tests/test_pcm.c`
- `pcm_ring_init` (function) `headers/pcm_ring.h:36` `static inline void pcm_ring_init(pcm_ring_t *r, unsigned char *buf,
                             ...`
- `pcm_ring_used` (function) `headers/pcm_ring.h:47` `static inline unsigned pcm_ring_used(const pcm_ring_t *r)`
- `pcm_ring_free` (function) `headers/pcm_ring.h:51` `static inline unsigned pcm_ring_free(const pcm_ring_t *r)`
- `pcm_ring_write` (function) `headers/pcm_ring.h:55` `static inline unsigned pcm_ring_write(pcm_ring_t *r, const unsigned char *src,
                  ...`
- `pcm_ring_read` (function) `headers/pcm_ring.h:76` `static inline unsigned pcm_ring_read(pcm_ring_t *r, unsigned char *dst,
                         ...`


Next: [API_p5.md](API_p5.md)
