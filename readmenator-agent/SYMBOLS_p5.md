# Symbols (page 5 of 26)
Previous: [SYMBOLS_p4.md](SYMBOLS_p4.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `kstderr` | variable | `headers/kernel.h:523` | `extern KFILE *kstderr;` |
| `kstdin` | variable | `headers/kernel.h:521` | `extern KFILE *kstdin;` |
| `kstdout` | variable | `headers/kernel.h:522` | `extern KFILE *kstdout;` |
| `kstrchr` | function | `headers/kernel.h:535` | `char *kstrchr(const char *s, int c);` |
| `kstrcmp` | function | `headers/kernel.h:533` | `int kstrcmp(const char *a, const char *b);` |
| `kstrcpy` | function | `headers/kernel.h:530` | `char *kstrcpy(char *dst, const char *src);` |
| `kstrlen` | function | `headers/kernel.h:529` | `unsigned long kstrlen(const char *s);` |
| `kstrncat` | function | `headers/kernel.h:532` | `char *kstrncat(char *dst, const char *src, unsigned long n);` |
| `kstrncmp` | function | `headers/kernel.h:534` | `int kstrncmp(const char *a, const char *b, unsigned long n);` |
| `kstrncpy` | function | `headers/kernel.h:531` | `char *kstrncpy(char *dst, const char *src, unsigned long n);` |
| `kstrstr` | function | `headers/kernel.h:536` | `char *kstrstr(const char *hay, const char *ndl);` |
| `ksym_count` | variable | `headers/kernel.h:624` | `extern int ksym_count;` |
| `ksym_resolve` | function | `headers/kernel.h:630` | `void *ksym_resolve(const char *name);` |
| `ksym_table` | variable | `headers/kernel.h:623` | `extern KSym ksym_table[];` |
| `ksyscall` | function | `headers/kernel.h:821` | `long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);` |
| `ktime_ms` | function | `headers/kernel.h:25` | `unsigned long ktime_ms(void);` |
| `ktime_us` | function | `headers/kernel.h:896` | `unsigned long ktime_us(void);` |
| `ldso_bind_into` | function | `headers/kernel.h:761` | `int ldso_bind_into(void *data, unsigned size, unsigned long base, unsigned long cr3, vma_ctx_t *vma);` |
| `ldso_pseudo_read` | function | `headers/kernel.h:764` | `int ldso_pseudo_read(int ino, void *dst, unsigned long off, unsigned len);` |
| `ldso_pseudo_stat` | function | `headers/kernel.h:763` | `int ldso_pseudo_stat(int ino, unsigned long *size_out);` |
| `load_exec_elf` | function | `headers/kernel.h:751` | `void *load_exec_elf(void *data, unsigned size);` |
| `load_exec_elf_into` | function | `headers/kernel.h:752` | `void *load_exec_elf_into(void *data, unsigned size, unsigned long cr3, unsigned long *brk_out, unsigned long *base_out);` |
| `minfo_sleep_init` | function | `headers/kernel.h:116` | `void minfo_sleep_init(int tick_ok);` |
| `minfo_tick_wake` | function | `headers/kernel.h:117` | `void minfo_tick_wake(void *ctx);` |
| `minifs_mkdir_p` | function | `headers/kernel.h:424` | `int minifs_mkdir_p(const char *resolved);` |
| `mm_anon_fault` | function | `headers/kernel.h:791` | `int mm_anon_fault(unsigned long cr3, unsigned long va, int write);` |
| `mm_anon_release` | function | `headers/kernel.h:793` | `void mm_anon_release(unsigned long cr3, unsigned long base, unsigned long len);` |
| `mm_anon_reserve` | function | `headers/kernel.h:789` | `int mm_anon_reserve(unsigned long cr3, unsigned long base, unsigned long len, unsigned long prot);` |
| `mm_copy_user_page` | function | `headers/kernel.h:803` | `int mm_copy_user_page(unsigned long dst_cr3, unsigned long src_cr3, unsigned long va);` |
| `mm_demand_pte` | function | `headers/kernel.h:788` | `unsigned long mm_demand_pte(unsigned long prot);` |
| `mm_file_break` | function | `headers/kernel.h:770` | `int mm_file_break(unsigned long cr3, unsigned long va);` |
| `mm_file_fault` | function | `headers/kernel.h:769` | `int mm_file_fault(unsigned long cr3, unsigned long va);` |
| `mm_file_page_phys` | function | `headers/kernel.h:771` | `unsigned long mm_file_page_phys(unsigned long cr3, unsigned long va);` |
| `mm_file_range_release` | function | `headers/kernel.h:772` | `void mm_file_range_release(unsigned long cr3, unsigned long base, unsigned long len, int ino, unsigned long off, int...` |
| `mm_setup_protections` | function | `headers/kernel.h:696` | `void mm_setup_protections(void);` |
| `mm_user_ensure_page` | function | `headers/kernel.h:766` | `int mm_user_ensure_page(unsigned long cr3, unsigned long va);` |
| `mm_user_map_page` | function | `headers/kernel.h:767` | `int mm_user_map_page(unsigned long cr3, unsigned long va, unsigned long phys, int write, int exec);` |
| `mm_user_pte_update` | function | `headers/kernel.h:699` | `void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3);` |
| `mm_user_set_exec` | function | `headers/kernel.h:700` | `void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3);` |
| `name` | type_alias | `headers/kernel.h:374` | `typedef struct vfs_dirent { char name[VFS_NAME_MAX + 1];` |
| `outb` | function | `headers/kernel.h:26` | `static inline void outb(unsigned short port, unsigned char val)` |
| `outsw` | function | `headers/kernel.h:54` | `static inline void outsw(unsigned short port, const unsigned short *buf,                         ...` |
| `outw` | function | `headers/kernel.h:34` | `static inline void outw(unsigned short port, unsigned short val)` |
| `panic_screen` | function | `headers/kernel.h:591` | `void panic_screen(unsigned long vector, unsigned long err, unsigned long rip, unsigned long rsp, unsigned long rbp...` |
| `pcspk_get_volume` | function | `headers/kernel.h:908` | `unsigned pcspk_get_volume(void);` |
| `pcspk_init` | function | `headers/kernel.h:904` | `void pcspk_init(void);` |
| `pcspk_off` | function | `headers/kernel.h:906` | `void pcspk_off(void);` |
| `pcspk_set_volume` | function | `headers/kernel.h:907` | `void pcspk_set_volume(unsigned volume);` |
| `pcspk_tone` | function | `headers/kernel.h:905` | `void pcspk_tone(unsigned freq);` |
| `pt_clone_user_empty` | function | `headers/kernel.h:765` | `unsigned long pt_clone_user_empty(void);` |
| `pt_page_alloc` | function | `headers/kernel.h:697` | `void *pt_page_alloc(void);` |
| `pt_page_free` | function | `headers/kernel.h:698` | `void pt_page_free(void *ptr);` |
| `pt_page_owned` | function | `headers/kernel.h:792` | `int pt_page_owned(unsigned long phys);` |
| `ramdisk_count` | function | `headers/kernel.h:291` | `int ramdisk_count(void);` |
| `ramdisk_create` | function | `headers/kernel.h:282` | `RDFile *ramdisk_create(const char *name, unsigned size);` |
| `ramdisk_delete` | function | `headers/kernel.h:284` | `int ramdisk_delete(RDFile *f);` |
| `ramdisk_end` | variable | `headers/kernel.h:879` | `extern char ramdisk_end[];` |
| `ramdisk_file_name` | function | `headers/kernel.h:292` | `const char *ramdisk_file_name(int idx);` |
| `ramdisk_init` | function | `headers/kernel.h:278` | `void ramdisk_init(void);` |
| `ramdisk_list` | function | `headers/kernel.h:289` | `int ramdisk_list(RDFile **out, int max);` |
| `ramdisk_open` | function | `headers/kernel.h:279` | `RDFile *ramdisk_open(const char *name);` |
| `ramdisk_read` | function | `headers/kernel.h:280` | `int ramdisk_read(RDFile *f, void *buf, unsigned offset, unsigned len);` |
| `ramdisk_rename` | function | `headers/kernel.h:288` | `int ramdisk_rename(const char *oldname, const char *newname);` |
| `ramdisk_resize` | function | `headers/kernel.h:283` | `int ramdisk_resize(RDFile *f, unsigned newsize);` |
| `ramdisk_setup_from` | function | `headers/kernel.h:290` | `void ramdisk_setup_from(void *data, unsigned size);` |
| `ramdisk_size` | variable | `headers/kernel.h:880` | `extern char ramdisk_size[];` |
| `ramdisk_start` | variable | `headers/kernel.h:878` | `extern char ramdisk_start[];` |
| `ramdisk_usage` | function | `headers/kernel.h:294` | `void ramdisk_usage(unsigned *used, unsigned *cap, unsigned *max);` |
| `ramdisk_write` | function | `headers/kernel.h:281` | `int ramdisk_write(RDFile *f, const void *buf, unsigned offset, unsigned len);` |
| `redirect_active` | function | `headers/kernel.h:585` | `int redirect_active(void);` |
| `redirect_begin` | function | `headers/kernel.h:578` | `int redirect_begin(void);` |
| `redirect_commit` | function | `headers/kernel.h:579` | `int redirect_commit(const char *path, int append_mode);` |
| `redirect_discard` | function | `headers/kernel.h:584` | `void redirect_discard(void);` |
| `redirect_pending` | function | `headers/kernel.h:581` | `unsigned long redirect_pending(void);` |
| `redirect_resume` | function | `headers/kernel.h:577` | `void redirect_resume(int was);` |
| `redirect_suspend` | function | `headers/kernel.h:576` | `int redirect_suspend(void);` |
| `redirect_take` | function | `headers/kernel.h:580` | `char *redirect_take(unsigned long *len_out);` |
| `redirect_take_into` | function | `headers/kernel.h:582` | `unsigned long redirect_take_into(char *dst, unsigned long cap, unsigned long *len_out);` |
| `refused` | function | `headers/kernel.h:800` | `* refused (see kernel/mm/paging.c for the fail-closed list). */ unsigned long kmm_map_device(unsigned long phys...` |
| `register_libc_symbols` | function | `headers/kernel.h:638` | `void register_libc_symbols(void);` |
| `rtc_read_tod` | function | `headers/kernel.h:911` | `int rtc_read_tod(int *hour, int *min, int *sec);` |
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
| `setup_user_stack` | function | `headers/kernel.h:655` | `unsigned long *setup_user_stack(char *sbase, unsigned long ssize, int argc, char **argv);` |
| `shell_exec_builtin` | function | `headers/kernel.h:601` | `void shell_exec_builtin(int argc, char **argv);` |
| `shell_fg_active` | variable | `headers/kernel.h:689` | `extern volatile int shell_fg_active;` |
| `shell_focus_park` | function | `headers/kernel.h:686` | `void shell_focus_park(void);` |
| `shell_focus_restore` | function | `headers/kernel.h:687` | `void shell_focus_restore(void);` |
| `shell_init` | function | `headers/kernel.h:572` | `void shell_init(void);` |
| `shell_queue_launch` | function | `headers/kernel.h:663` | `void shell_queue_launch(const char *cmd);` |
| `shell_readline_active` | function | `headers/kernel.h:685` | `int shell_readline_active(void);` |
| `shell_report` | function | `headers/kernel.h:603` | `void shell_report(const char *what, const char *detail);` |
| `shell_report_exit` | function | `headers/kernel.h:602` | `void shell_report_exit(int code);` |
| `shell_run` | function | `headers/kernel.h:573` | `void shell_run(void);` |
| `shell_run_any` | function | `headers/kernel.h:600` | `int shell_run_any(const char *name, int argc, char **argv);` |
| `shell_take_redirect` | function | `headers/kernel.h:599` | `int shell_take_redirect(int *argc, char **argv, char **path, int *append_mode);` |
| `swap_in` | function | `headers/kernel.h:704` | `int swap_in(void);` |
| `swap_out` | function | `headers/kernel.h:703` | `int swap_out(unsigned long window_sz);` |
| `syscall_init` | function | `headers/kernel.h:817` | `void syscall_init(void);` |
| `syscall_name` | function | `headers/kernel.h:827` | `const char *syscall_name(long n);` |
| `syscall_trace_enabled` | function | `headers/kernel.h:822` | `long syscall_trace_enabled(void);` |
| `syscall_trace_set` | function | `headers/kernel.h:823` | `void syscall_trace_set(int on);` |
| `syscall_trace_shown` | function | `headers/kernel.h:826` | `unsigned long syscall_trace_shown(void);` |
| `syscall_trace_verbose_enabled` | function | `headers/kernel.h:824` | `long syscall_trace_verbose_enabled(void);` |
| `syscall_trace_verbose_set` | function | `headers/kernel.h:825` | `void syscall_trace_verbose_set(int on);` |
| `today` | function | `headers/kernel.h:489` | `* cell is correct today (single shared ET_REL window, no miniGCC * threads);` |
| `user_mmap_cur` | variable | `headers/kernel.h:709` | `extern unsigned long user_mmap_cur;` |
| `user_page_present` | function | `headers/kernel.h:811` | `int user_page_present(unsigned long cr3, unsigned long va);` |
| `user_range_ok` | function | `headers/kernel.h:692` | `int user_range_ok(unsigned long p, unsigned long len);` |
| `user_str_ok` | function | `headers/kernel.h:693` | `int user_str_ok(unsigned long p, unsigned long maxlen);` |
| `vfs_close` | function | `headers/kernel.h:419` | `int vfs_close(vfs_file_t *f);` |
| `vfs_dirent` | struct | `headers/kernel.h:374` | `` |
| `vfs_file` | struct | `headers/kernel.h:389` | `` |
| `vfs_fstat` | function | `headers/kernel.h:420` | `int vfs_fstat(vfs_file_t *f, unsigned long *size_out);` |
| `vfs_init` | function | `headers/kernel.h:422` | `void vfs_init(void);` |
| `vfs_list` | function | `headers/kernel.h:413` | `int vfs_list(char prefixes[][VFS_PREFIX_LEN], char drivers[][VFS_DRIVER_LEN], int refs[], int cap);` |
| `vfs_mount_driver` | function | `headers/kernel.h:415` | `int vfs_mount_driver(const char *prefix, const char *driver);` |
| `vfs_open` | function | `headers/kernel.h:416` | `int vfs_open(const char *path, int mode, vfs_file_t *f);` |
| `vfs_ops` | struct | `headers/kernel.h:379` | `` |
| `vfs_read` | function | `headers/kernel.h:417` | `int vfs_read(vfs_file_t *f, void *buf, unsigned long len);` |
| `vfs_readdir` | function | `headers/kernel.h:421` | `int vfs_readdir(const char *path, vfs_dirent_t *ents, int cap);` |
| `vfs_register` | function | `headers/kernel.h:408` | `int vfs_register(const char *prefix, const vfs_ops_t *ops, const char *driver);` |
| `vfs_register_builtins` | function | `headers/kernel.h:423` | `void vfs_register_builtins(void);` |
| `vfs_unregister` | function | `headers/kernel.h:409` | `int vfs_unregister(const char *prefix);` |
| `vfs_write` | function | `headers/kernel.h:418` | `int vfs_write(vfs_file_t *f, const void *buf, unsigned long len);` |
| `vga_clear` | function | `headers/kernel.h:94` | `void vga_clear(void);` |
| `vga_cursor_enable` | function | `headers/kernel.h:100` | `void vga_cursor_enable(int on);` |
| `vga_fb_act_empty` | function | `headers/kernel.h:677` | `int vga_fb_act_empty(void);` |
| `vga_fb_clear_prompt` | function | `headers/kernel.h:680` | `void vga_fb_clear_prompt(void);` |
| `vga_fb_focus_get` | function | `headers/kernel.h:668` | `int vga_fb_focus_get(void);` |
| `vga_fb_focus_id` | function | `headers/kernel.h:667` | `int vga_fb_focus_id(int id);` |
| `vga_fb_focus_next` | function | `headers/kernel.h:666` | `void vga_fb_focus_next(void);` |
| `vga_fb_list_windows` | function | `headers/kernel.h:673` | `void vga_fb_list_windows(void);` |
| `vga_fb_note_prompt` | function | `headers/kernel.h:679` | `void vga_fb_note_prompt(void);` |
| `vga_fb_nterms_get` | function | `headers/kernel.h:669` | `int vga_fb_nterms_get(void);` |
| `vga_fb_park_line` | function | `headers/kernel.h:674` | `void vga_fb_park_line(const char *b, int p);` |
| `vga_fb_prompt_live` | function | `headers/kernel.h:678` | `int vga_fb_prompt_live(void);` |
| `vga_fb_prompted` | function | `headers/kernel.h:681` | `int vga_fb_prompted(void);` |
| `vga_fb_set_gfx_program` | function | `headers/kernel.h:676` | `void vga_fb_set_gfx_program(const char *name);` |
| `vga_fb_term_close_focused` | function | `headers/kernel.h:671` | `int vga_fb_term_close_focused(void);` |
| `vga_fb_term_split` | function | `headers/kernel.h:670` | `int vga_fb_term_split(void);` |
| `vga_fb_tile_all` | function | `headers/kernel.h:672` | `void vga_fb_tile_all(void);` |
| `vga_fb_unpark_line` | function | `headers/kernel.h:675` | `int vga_fb_unpark_line(char *b, int *p);` |
| `vga_get_color` | function | `headers/kernel.h:111` | `char vga_get_color(void);` |
| `vga_get_x` | function | `headers/kernel.h:108` | `int vga_get_x(void);` |
| `vga_get_y` | function | `headers/kernel.h:109` | `int vga_get_y(void);` |
| `vga_gfx_ran_set` | function | `headers/kernel.h:659` | `void vga_gfx_ran_set(int on);` |
| `vga_mode_is_active` | function | `headers/kernel.h:658` | `int vga_mode_is_active(void);` |
| `vga_mode_set` | function | `headers/kernel.h:657` | `void vga_mode_set(int on);` |
| `vga_newline` | function | `headers/kernel.h:99` | `void vga_newline(void);` |
| `vga_putc` | function | `headers/kernel.h:95` | `void vga_putc(char c);` |
| `vga_puts` | function | `headers/kernel.h:96` | `void vga_puts(const char *s);` |
| `vga_scroll` | function | `headers/kernel.h:97` | `void vga_scroll(void);` |
| `vga_set_cursor` | function | `headers/kernel.h:98` | `void vga_set_cursor(int x, int y);` |
| `vga_set_xy` | function | `headers/kernel.h:110` | `void vga_set_xy(int x, int y);` |
| `vnode_t` | type_alias | `headers/kernel.h:406` | `typedef vfs_file_t vnode_t;` |
| `waits` | function | `headers/kernel.h:64` | `* and mouse_hw_init issues dozens of waits (measured 5 s of boot).  This  * polls the port once p...` |
| `wall_us_now` | function | `headers/kernel.h:897` | `unsigned long wall_us_now(void);` |
| `CONSOLE_IN_H` | macro | `headers/kernel/console_in.h:2` | `#define CONSOLE_IN_H` |
| `Consumers` | function | `headers/kernel/console_in.h:7` | `* Consumers (shell prompt, editor, SPAWN waits, GETC_RAW syscall) include * this header instead of reaching into...` |
| `console_job_get` | function | `headers/kernel/console_in.h:26` | `int console_job_get(void);` |
| `console_job_try` | function | `headers/kernel/console_in.h:25` | `int console_job_try(void);` |
| `console_peek` | function | `headers/kernel/console_in.h:17` | `int console_peek(void);` |
| `console_raw_get` | function | `headers/kernel/console_in.h:22` | `int console_raw_get(void);` |
| `console_raw_try` | function | `headers/kernel/console_in.h:21` | `int console_raw_try(void);` |
| `console_stdin_active` | function | `headers/kernel/console_in.h:39` | `int console_stdin_active(void);` |
| `console_stdin_clear` | function | `headers/kernel/console_in.h:38` | `void console_stdin_clear(void);` |
| `console_stdin_push` | function | `headers/kernel/console_in.h:37` | `int console_stdin_push(const char *data, unsigned long len);` |
| `console_ungetc` | function | `headers/kernel/console_in.h:30` | `void console_ungetc(unsigned char c);` |
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
| `minifs_rename` | function | `headers/minifs.h:130` | `int minifs_rename(const char *oldpath, const char *newpath);` |
| `minifs_resolve_path` | function | `headers/minifs.h:137` | `int minifs_resolve_path(const char *path);` |
| `minifs_rmdir` | function | `headers/minifs.h:125` | `int minifs_rmdir(const char *path);` |
| `minifs_stat` | function | `headers/minifs.h:134` | `int minifs_stat(int inode_num, MiniFSInode *out);` |
| `minifs_sync` | function | `headers/minifs.h:119` | `int minifs_sync(void);` |
| `minifs_truncate` | function | `headers/minifs.h:133` | `int minifs_truncate(int inode_num, unsigned int new_size);` |
| `minifs_unlink` | function | `headers/minifs.h:124` | `int minifs_unlink(const char *path);` |
| `minifs_usage` | function | `headers/minifs.h:164` | `void minifs_usage(unsigned int *free_b, unsigned int *total_b, unsigned int *free_i, unsigned int *total_i);` |
| `minifs_write` | function | `headers/minifs.h:132` | `int minifs_write(int inode_num, const void *buf, unsigned int offset, unsigned int len);` |
| `refuses` | function | `headers/minifs.h:128` | `* An existing file dst refuses (no silent overwrite);` |
| `NET_ACCEPT_TMO_MS` | macro | `headers/net.h:68` | `#define NET_ACCEPT_TMO_MS` |
| `NET_ARP_CACHE` | macro | `headers/net.h:50` | `#define NET_ARP_CACHE` |
| `NET_ARP_REPLY` | macro | `headers/net.h:52` | `#define NET_ARP_REPLY` |
| `NET_ARP_REQUEST` | macro | `headers/net.h:51` | `#define NET_ARP_REQUEST` |
| `NET_CONNECT_TMO_S` | macro | `headers/net.h:66` | `#define NET_CONNECT_TMO_S` |
| `NET_DNS` | macro | `headers/net.h:8` | `#define NET_DNS` |
| `NET_DNS_PORT` | macro | `headers/net.h:62` | `#define NET_DNS_PORT` |
| `NET_DNS_TMO_MS` | macro | `headers/net.h:65` | `#define NET_DNS_TMO_MS` |
| `NET_DNS_TRIES` | macro | `headers/net.h:64` | `#define NET_DNS_TRIES` |
| `NET_EPHEMERAL_MIN` | macro | `headers/net.h:63` | `#define NET_EPHEMERAL_MIN` |
| `NET_ETHERTYPE_ARP` | macro | `headers/net.h:41` | `#define NET_ETHERTYPE_ARP` |
| `NET_ETHERTYPE_IP` | macro | `headers/net.h:40` | `#define NET_ETHERTYPE_IP` |
| `NET_ETHERTYPE_IPV6` | macro | `headers/net.h:42` | `#define NET_ETHERTYPE_IPV6` |
| `NET_ETH_ALEN` | macro | `headers/net.h:39` | `#define NET_ETH_ALEN` |
| `NET_FD_BASE` | macro | `headers/net.h:72` | `#define NET_FD_BASE` |
| `NET_GATEWAY` | macro | `headers/net.h:7` | `#define NET_GATEWAY` |
| `NET_H` | macro | `headers/net.h:2` | `#define NET_H` |
| `NET_IOV_LEN` | macro | `headers/net.h:92` | `#define NET_IOV_LEN` |
| `NET_IOV_MAX` | macro | `headers/net.h:93` | `#define NET_IOV_MAX` |
| `NET_IP_ADDR` | macro | `headers/net.h:5` | `#define NET_IP_ADDR` |
| `NET_MAX_FRAME` | macro | `headers/net.h:35` | `#define NET_MAX_FRAME` |
| `NET_MMSGHDR_LEN` | macro | `headers/net.h:86` | `#define NET_MMSGHDR_LEN` |
| `NET_MMSGHDR_LEN_OFF` | macro | `headers/net.h:91` | `#define NET_MMSGHDR_LEN_OFF` |
| `NET_MMSG_MAX` | macro | `headers/net.h:94` | `#define NET_MMSG_MAX` |
| `NET_MSGHDR_IOVLEN_OFF` | macro | `headers/net.h:90` | `#define NET_MSGHDR_IOVLEN_OFF` |
| `NET_MSGHDR_IOV_OFF` | macro | `headers/net.h:89` | `#define NET_MSGHDR_IOV_OFF` |
| `NET_MSGHDR_LEN` | macro | `headers/net.h:85` | `#define NET_MSGHDR_LEN` |
| `NET_MSGHDR_NAMELEN_OFF` | macro | `headers/net.h:88` | `#define NET_MSGHDR_NAMELEN_OFF` |
| `NET_MSGHDR_NAME_OFF` | macro | `headers/net.h:87` | `#define NET_MSGHDR_NAME_OFF` |
| `NET_NETMASK` | macro | `headers/net.h:6` | `#define NET_NETMASK` |
| `NET_PCI_DEVICE` | macro | `headers/net.h:20` | `#define NET_PCI_DEVICE` |
| `NET_PCI_VENDOR` | macro | `headers/net.h:19` | `#define NET_PCI_VENDOR` |
| `NET_POLLERR` | macro | `headers/net.h:14` | `#define NET_POLLERR` |
| `NET_POLLHUP` | macro | `headers/net.h:15` | `#define NET_POLLHUP` |
| `NET_POLLIN` | macro | `headers/net.h:12` | `#define NET_POLLIN` |
| `NET_POLLNVAL` | macro | `headers/net.h:16` | `#define NET_POLLNVAL` |
| `NET_POLLOUT` | macro | `headers/net.h:13` | `#define NET_POLLOUT` |
| `NET_PROTO_ICMP` | macro | `headers/net.h:45` | `#define NET_PROTO_ICMP` |
| `NET_PROTO_TCP` | macro | `headers/net.h:46` | `#define NET_PROTO_TCP` |
| `NET_PROTO_UDP` | macro | `headers/net.h:47` | `#define NET_PROTO_UDP` |
| `NET_RCR` | macro | `headers/net.h:34` | `#define NET_RCR` |
| `NET_RETRY_MS` | macro | `headers/net.h:67` | `#define NET_RETRY_MS` |
| `NET_RX_ALIGN` | macro | `headers/net.h:27` | `#define NET_RX_ALIGN` |
| `NET_RX_BUF_LEN` | macro | `headers/net.h:26` | `#define NET_RX_BUF_LEN` |
| `NET_RX_RING_PAD` | macro | `headers/net.h:31` | `#define NET_RX_RING_PAD` |
| `NET_RX_RING_SIZE` | macro | `headers/net.h:60` | `#define NET_RX_RING_SIZE` |
| `NET_SOCKADDR_IN_LEN` | macro | `headers/net.h:83` | `#define NET_SOCKADDR_IN_LEN` |
| `NET_SOCKETS` | macro | `headers/net.h:61` | `#define NET_SOCKETS` |
| `NET_SOCK_RX_BUF` | macro | `headers/net.h:59` | `#define NET_SOCK_RX_BUF` |
| `NET_TCP_MSS` | macro | `headers/net.h:55` | `#define NET_TCP_MSS` |
| `NET_TCP_WINDOW` | macro | `headers/net.h:56` | `#define NET_TCP_WINDOW` |
| `NET_TX_MAX` | macro | `headers/net.h:69` | `#define NET_TX_MAX` |
| `NET_TX_SLOTS` | macro | `headers/net.h:36` | `#define NET_TX_SLOTS` |
| `NET_UDP_DGRAM_MAX` | macro | `headers/net.h:79` | `#define NET_UDP_DGRAM_MAX` |
| `NET_UDP_EPHEMERAL_MAX` | macro | `headers/net.h:82` | `#define NET_UDP_EPHEMERAL_MAX` |
| `NET_UDP_EPHEMERAL_MIN` | macro | `headers/net.h:81` | `#define NET_UDP_EPHEMERAL_MIN` |
| `NET_UDP_FD_BASE` | macro | `headers/net.h:80` | `#define NET_UDP_FD_BASE` |
| `NET_UDP_QUEUE` | macro | `headers/net.h:78` | `#define NET_UDP_QUEUE` |
| `NET_UDP_SOCKETS` | macro | `headers/net.h:77` | `#define NET_UDP_SOCKETS` |
| `demux` | function | `headers/net.h:131` | `* segment through the production demux (httpd selftest). */ int net_listen(unsigned short port);` |
| `net6_rx_dropped` | variable | `headers/net.h:164` | `extern unsigned int net6_rx_dropped;` |
| `net_accept` | function | `headers/net.h:134` | `int net_accept(int fd, unsigned long timeout_ms);` |
| `net_accept_nb` | function | `headers/net.h:133` | `int net_accept_nb(int fd);` |
| `net_close` | function | `headers/net.h:125` | `void net_close(int fd);` |
| `net_cmd_dns` | function | `headers/net.h:116` | `void net_cmd_dns(const char *host);` |
| `net_cmd_ping` | function | `headers/net.h:114` | `void net_cmd_ping(const char *ip_text);` |
| `net_cmd_status` | function | `headers/net.h:113` | `void net_cmd_status(void);` |
| `net_connect` | function | `headers/net.h:120` | `int net_connect(const char *host, unsigned short port);` |
| `net_get_addrs` | function | `headers/net.h:115` | `void net_get_addrs(unsigned char mac_out[NET_ETH_ALEN], unsigned char ip_out[4]);` |
| `net_open` | function | `headers/net.h:119` | `int net_open(void);` |
| `net_recv` | function | `headers/net.h:122` | `int net_recv(int fd, char *buf, int len);` |
| `net_recv_timeout` | function | `headers/net.h:124` | `int net_recv_timeout(int fd, char *buf, int len, unsigned long timeout_ms);` |
| `net_register_symbols` | function | `headers/net.h:110` | `void net_register_symbols(void);` |
| `net_rx_dropped` | variable | `headers/net.h:163` | `extern unsigned int net_rx_dropped;` |
| `net_rx_handle_frame` | function | `headers/net.h:159` | `void net_rx_handle_frame(const unsigned char *frame, unsigned len);` |
| `net_send` | function | `headers/net.h:121` | `int net_send(int fd, const char *buf, int len);` |
| `net_sock_seq` | function | `headers/net.h:136` | `int net_sock_seq(int fd, unsigned *seq_out, unsigned *ack_out);` |
| `net_sock_state` | function | `headers/net.h:135` | `int net_sock_state(int fd);` |
| `net_sys_accept` | function | `headers/net.h:146` | `long net_sys_accept(long fd, long sockaddr, long addrlen);` |
| `net_sys_bind` | function | `headers/net.h:144` | `long net_sys_bind(long fd, long sockaddr, long addrlen);` |
| `net_sys_close` | function | `headers/net.h:150` | `long net_sys_close(long fd);` |
| `net_sys_connect` | function | `headers/net.h:143` | `long net_sys_connect(long fd, long sockaddr, long addrlen);` |
| `net_sys_dns` | function | `headers/net.h:152` | `long net_sys_dns(long host);` |
| `net_sys_fcntl` | function | `headers/net.h:108` | `long net_sys_fcntl(long fd, long cmd, long arg);` |
| `net_sys_getpeername` | function | `headers/net.h:105` | `long net_sys_getpeername(long fd, long addr, long lenp);` |
| `net_sys_getsockname` | function | `headers/net.h:104` | `long net_sys_getsockname(long fd, long addr, long lenp);` |
| `net_sys_getsockopt` | function | `headers/net.h:103` | `long net_sys_getsockopt(long fd, long level, long name, long val, long lenp);` |
| `net_sys_ioctl` | function | `headers/net.h:109` | `long net_sys_ioctl(long fd, long req, long arg);` |
| `net_sys_is_socket` | function | `headers/net.h:101` | `int net_sys_is_socket(long fd);` |
| `net_sys_listen` | function | `headers/net.h:145` | `long net_sys_listen(long fd, long backlog);` |
| `net_sys_poll` | function | `headers/net.h:151` | `long net_sys_poll(long fds, long nfds, long timeout_ms);` |
| `net_sys_recvfrom` | function | `headers/net.h:148` | `long net_sys_recvfrom(long fd, long buf, long len, long flags, long from, long fromlen);` |
| `net_sys_sendmmsg` | function | `headers/net.h:107` | `long net_sys_sendmmsg(long fd, long vec, long vlen, long flags);` |
| `net_sys_sendmsg` | function | `headers/net.h:106` | `long net_sys_sendmsg(long fd, long msg, long flags);` |
| `net_sys_sendto` | function | `headers/net.h:147` | `long net_sys_sendto(long fd, long buf, long len, long flags, long to, long tolen);` |
| `net_sys_setsockopt` | function | `headers/net.h:102` | `long net_sys_setsockopt(long fd, long level, long name, long val, long len);` |
| `net_sys_shutdown` | function | `headers/net.h:149` | `long net_sys_shutdown(long fd, long how);` |
| `net_sys_socket` | function | `headers/net.h:142` | `long net_sys_socket(long a1, long a2, long a3);` |
| `net_test_inject_tcp` | function | `headers/net.h:137` | `int net_test_inject_tcp(const unsigned char peer[4], unsigned short pport, unsigned short lport, unsigned char...` |
| `net_time_ms` | function | `headers/net.h:155` | `unsigned long net_time_ms(void);` |
| `ring` | function | `headers/net.h:58` | `* ring (below) is the rtl8139's 8 KB hardware ring, unrelated. */ #define NET_SOCK_RX_BUF 16384 #define...` |
| `stack` | function | `headers/net.h:162` | `* the stack (dropped fragments);` |
| `tls_free_fd` | function | `headers/net.h:170` | `void tls_free_fd(int fd);` |
| `RTL8139_H` | macro | `headers/net/rtl8139.h:2` | `#define RTL8139_H` |
| `net_rx_handle_frame` | function | `headers/net/rtl8139.h:28` | `* net_rx_handle_frame (the protocol demux in net.c). */ void rtl_poll(void);` |
| `rtl_counters` | function | `headers/net/rtl8139.h:38` | `void rtl_counters(unsigned int *tx_frames, unsigned int *rx_frames);` |
| `rtl_get_mac` | function | `headers/net/rtl8139.h:32` | `void rtl_get_mac(unsigned char out[NET_ETH_ALEN]);` |
| `rtl_init` | function | `headers/net/rtl8139.h:21` | `void rtl_init(void);` |
| `rtl_iobase` | function | `headers/net/rtl8139.h:35` | `unsigned short rtl_iobase(void);` |
| `rtl_present` | function | `headers/net/rtl8139.h:18` | `int rtl_present(void);` |
| `rtl_send` | function | `headers/net/rtl8139.h:25` | `int rtl_send(const unsigned char *frame, unsigned len);` |
| `PANIC_BT_MAX` | macro | `headers/panic.h:17` | `#define PANIC_BT_MAX` |
| `PANIC_H` | macro | `headers/panic.h:15` | `#define PANIC_H` |
| `panic_backtrace` | function | `headers/panic.h:25` | `static inline int panic_backtrace(unsigned long rbp, panic_valid_fn valid,         unsigned long ...` |
| `PCACHE_H` | macro | `headers/pcache.h:17` | `#define PCACHE_H` |
| `PCACHE_PAGE` | macro | `headers/pcache.h:23` | `#define PCACHE_PAGE` |
| `PCACHE_PAGES` | macro | `headers/pcache.h:20` | `#define PCACHE_PAGES` |
| `match` | function | `headers/pcache.h:75` | `* a phys match (owned, ref dropped unless already zero), 0 * otherwise. */ int pcache_put_if(int ino, unsigned...` |
| `pcache_data` | function | `headers/pcache.h:93` | `unsigned char *pcache_data(int slot);` |
| `pcache_get` | function | `headers/pcache.h:42` | `int pcache_get(int ino, unsigned index, int *is_new);` |
| `pcache_init` | function | `headers/pcache.h:28` | `void pcache_init(void);` |
| `pcache_invalidate_ino` | function | `headers/pcache.h:102` | `void pcache_invalidate_ino(int ino);` |
| `pcache_lookup` | function | `headers/pcache.h:32` | `int pcache_lookup(int ino, unsigned index);` |
| `pcache_mark_dirty` | function | `headers/pcache.h:98` | `void pcache_mark_dirty(int slot);` |
| `pcache_owns_phys` | function | `headers/pcache.h:88` | `int pcache_owns_phys(unsigned long phys);` |
| `pcache_publish` | function | `headers/pcache.h:51` | `int pcache_publish(int ino, unsigned index, const unsigned char *data);` |
| `pcache_put` | function | `headers/pcache.h:55` | `void pcache_put(int slot);` |
| `pcache_ref` | function | `headers/pcache.h:61` | `int pcache_ref(int ino, unsigned index);` |
| `pcache_ref_if` | function | `headers/pcache.h:83` | `int pcache_ref_if(int ino, unsigned index, unsigned long phys);` |
| `pcache_stats` | function | `headers/pcache.h:106` | `void pcache_stats(unsigned long *pages_out, unsigned long *hits_out, unsigned long *miss_out, unsigned long...` |
| `pcache_unmap` | function | `headers/pcache.h:69` | `void pcache_unmap(int ino, unsigned index);` |
| `PCM2_DMA_BYTES` | macro | `headers/pcm2.h:55` | `#define PCM2_DMA_BYTES` |
| `PCM2_ERR_BUSY` | macro | `headers/pcm2.h:60` | `#define PCM2_ERR_BUSY` |
| `PCM2_ERR_INVAL` | macro | `headers/pcm2.h:65` | `#define PCM2_ERR_INVAL` |
| `PCM2_ERR_NODEV` | macro | `headers/pcm2.h:61` | `#define PCM2_ERR_NODEV` |
| `PCM2_ERR_NOMEM` | macro | `headers/pcm2.h:62` | `#define PCM2_ERR_NOMEM` |
| `PCM2_ERR_PERM` | macro | `headers/pcm2.h:63` | `#define PCM2_ERR_PERM` |
| `PCM2_ERR_PIPE` | macro | `headers/pcm2.h:64` | `#define PCM2_ERR_PIPE` |
| `PCM2_FLAG_NONBLOCK` | macro | `headers/pcm2.h:58` | `#define PCM2_FLAG_NONBLOCK` |
| `PCM2_FRAG` | macro | `headers/pcm2.h:53` | `#define PCM2_FRAG` |
| `PCM2_FRAGS` | macro | `headers/pcm2.h:54` | `#define PCM2_FRAGS` |
| `PCM2_H` | macro | `headers/pcm2.h:2` | `#define PCM2_H` |
| `PCM2_RATE` | macro | `headers/pcm2.h:52` | `#define PCM2_RATE` |
| `PCM2_RING` | macro | `headers/pcm2.h:56` | `#define PCM2_RING` |
| `pcm2_active` | function | `headers/pcm2.h:77` | `int pcm2_active(void);` |
| `pcm2_close` | function | `headers/pcm2.h:80` | `void pcm2_close(int owner);` |
| `pcm2_counters` | function | `headers/pcm2.h:83` | `void pcm2_counters(pcm2_counters_t *out);` |
| `pcm2_counters_t` | struct | `headers/pcm2.h:67` | `` |

Next: [SYMBOLS_p6.md](SYMBOLS_p6.md)
