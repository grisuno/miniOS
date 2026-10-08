# API (page 7 of 19)
Previous: [API_p6.md](API_p6.md)

## kernel/syscalls.c
Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/arch/x86/hal_io.h`, `headers/arch/x86/msr.h`, `headers/batch.h`, `headers/block.h`, `headers/driver.h`, `headers/drivers/kbd.h`, `headers/futex.h`, `headers/ide.h`, `headers/ktime.h`, `headers/lz4_kernel.h`, `headers/minifs.h`, `headers/net.h`, `headers/pcache.h`, `headers/pcm2.h`, `headers/pcspk.h`, `headers/percpu_rq.h`, `headers/randmix.h`, `headers/rcu.h`, `headers/rtc.h`, `headers/sanitize.h`, `headers/sb16.h`, `headers/sched.h`, `headers/shell.h`, `headers/spawn.h`, `headers/sync.h`, `headers/syscalls_proc.h`, `headers/vga_fb.h`, `headers/zip.h`
- `kfd_view_current` (function) `kernel/syscalls.c:58` `static kfd_view_t *kfd_view_current(void)` -- Docstring: View owning the caller's fds: its own on isolated procs * and threads, the root on pid 0 and any pid...
- `kfd_view_root` (function) `kernel/syscalls.c:68` `kfd_view_t *kfd_view_root(void)` -- Docstring: Static root view (shell pid 0, pids without their own): * entries are the historical shared table, never...
- `kfd_get` (function) `kernel/syscalls.c:87` `KFILE *kfd_get(int fd)`
- `kfd_put` (function) `kernel/syscalls.c:100` `void kfd_put(KFILE *f)`
- `kfd_view_count` (function) `kernel/syscalls.c:112` `static int kfd_view_count(kfd_view_t *v)` -- } void kfd_put(KFILE *f) { irqflags_t flags; int drop = 0; if (!f) return; spin_lock_irqsave(&fd_lock, &flags)...
- `untouched` (function) `kernel/syscalls.c:136` `* child untouched (caller refuses fail-closed). */
int kfd_view_copy(proc_t *child, proc_t *parent)`
- `NULL` (function) `kernel/syscalls.c:163` `* on NULL (already released or never owned). */
void kfd_view_release(proc_t *p)`
- `kfd_view_cloexec` (function) `kernel/syscalls.c:194` `void kfd_view_cloexec(void)` -- Docstring: Close every CLOEXEC fd in the caller's own view (execve: the image is replaced, marked descriptors must...
- `by` (function) `kernel/syscalls.c:222` `* is indexed by (syscall_number - 200). New syscalls are added by: * 1. Adding a MINIOS_SYS_* constant to...`
- `wall_us_now` (function) `kernel/syscalls.c:253` `unsigned long wall_us_now(void)` -- wall_us_now: RTC-anchored wall clock in microseconds (Phase 0.2/0.3).
- `sys_minios_dns` (function) `kernel/syscalls.c:263` `static long sys_minios_dns(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_tls_retired` (function) `kernel/syscalls.c:268` `static long sys_minios_tls_retired(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_futex` (function) `kernel/syscalls.c:275` `static long sys_linux_futex(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_time` (function) `kernel/syscalls.c:304` `static long sys_minios_time(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_kbd` (function) `kernel/syscalls.c:308` `static long sys_minios_kbd(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_palette` (function) `kernel/syscalls.c:328` `static long sys_minios_palette(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_kbd_raw` (function) `kernel/syscalls.c:340` `static long sys_minios_kbd_raw(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_vga_mode` (function) `kernel/syscalls.c:346` `static long sys_minios_vga_mode(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_pcspk_init` (function) `kernel/syscalls.c:353` `static long sys_minios_pcspk_init(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_pcspk_tone` (function) `kernel/syscalls.c:357` `static long sys_minios_pcspk_tone(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_doom_frame` (function) `kernel/syscalls.c:371` `static long sys_minios_doom_frame(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_gfx_zoom` (function) `kernel/syscalls.c:382` `static long sys_minios_gfx_zoom(long a1, long a2, long a3, long a4, long a5, long a6)` -- Graphics window scale request (a1): 0 native, 1 2x nearest-neighbour zoom for the 320x200 game window, 2 true...
- `sys_minios_rtc` (function) `kernel/syscalls.c:391` `static long sys_minios_rtc(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_fb_info` (function) `kernel/syscalls.c:404` `static long sys_minios_fb_info(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_pcspk_vol` (function) `kernel/syscalls.c:424` `static long sys_minios_pcspk_vol(long a1, long a2, long a3, long a4, long a5, long a6)`
- `boot` (function) `kernel/syscalls.c:441` `* boot (minfo_sleep_init from sched_init);`
- `minfo_sleep_init` (function) `kernel/syscalls.c:448` `void minfo_sleep_init(int tick_ok)`
- `minfo_tick_wake` (function) `kernel/syscalls.c:453` `void minfo_tick_wake(void *ctx)`
- `view` (function) `kernel/syscalls.c:465` `* view (same as the `clear` builtin). Anything else is -EINVAL. Each
 * out-word is range-checked...`
- `sys_minios_spawn` (function) `kernel/syscalls.c:556` `static long sys_minios_spawn(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_lz4_compress` (function) `kernel/syscalls.c:567` `static long sys_minios_lz4_compress(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_lz4_decompress` (function) `kernel/syscalls.c:580` `static long sys_minios_lz4_decompress(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_mouse` (function) `kernel/syscalls.c:594` `static long sys_minios_mouse(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_nk_frame` (function) `kernel/syscalls.c:618` `static long sys_minios_nk_frame(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sb16_audio_device` (function) `kernel/syscalls.c:631` `static device_t *sb16_audio_device(void)` -- } static long sys_minios_nk_frame(long a1, long a2, long a3, long a4, long a5, long a6) { (void)a2; (void)a3...
- `sys_minios_sb16_open` (function) `kernel/syscalls.c:637` `static long sys_minios_sb16_open(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_sb16_submit` (function) `kernel/syscalls.c:649` `static long sys_minios_sb16_submit(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_gfx_title` (function) `kernel/syscalls.c:660` `static long sys_minios_gfx_title(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_sb16_pump` (function) `kernel/syscalls.c:674` `static long sys_minios_sb16_pump(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_sb16_stream_open` (function) `kernel/syscalls.c:678` `static long sys_minios_sb16_stream_open(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_sb16_stream_close` (function) `kernel/syscalls.c:682` `static long sys_minios_sb16_stream_close(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_sb16_stream_submit` (function) `kernel/syscalls.c:686` `static long sys_minios_sb16_stream_submit(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_pcm2_open` (function) `kernel/syscalls.c:699` `static long sys_minios_pcm2_open(long a1, long a2, long a3, long a4, long a5, long a6)` -- Low-latency PCM path (pcm2, syscalls 246-248): OPEN takes flags, WRITE returns bytes taken (blocking unless...
- `sys_minios_pcm2_write` (function) `kernel/syscalls.c:704` `static long sys_minios_pcm2_write(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_pcm2_close` (function) `kernel/syscalls.c:712` `static long sys_minios_pcm2_close(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_clip_set` (function) `kernel/syscalls.c:722` `static long sys_minios_clip_set(long a1, long a2, long a3, long a4, long a5, long a6)` -- Shared text clipboard (syscalls 249-250): SET copies len bytes in (refused past 4096, never truncated), GET copies...
- `sys_minios_clip_get` (function) `kernel/syscalls.c:732` `static long sys_minios_clip_get(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_sb16_stream_vol` (function) `kernel/syscalls.c:748` `static long sys_minios_sb16_stream_vol(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_futex_wait` (function) `kernel/syscalls.c:761` `static long sys_minios_futex_wait(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_futex_wake` (function) `kernel/syscalls.c:767` `static long sys_minios_futex_wake(long a1, long a2, long a3, long a4, long a5, long a6)`
- `batch_kdispatch` (function) `kernel/syscalls.c:776` `static long batch_kdispatch(uint32_t opcode)`
- `DOOM_FRAME` (function) `kernel/syscalls.c:791` `* DOOM_FRAME (211) and NK_FRAME (220) stay as compat aliases. */
static long sys_minios_gfx_prese...`
- `sys_minios_getc_raw` (function) `kernel/syscalls.c:825` `static long sys_minios_getc_raw(long a1, long a2, long a3, long a4, long a5, long a6)` -- Raw keystroke read for fullscreen ring-3 programs (vedit): one byte from the serial + PS/2 multiplexer with no line...
- `sys_minios_submit_batch` (function) `kernel/syscalls.c:836` `static long sys_minios_submit_batch(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_rlimit` (function) `kernel/syscalls.c:859` `static long sys_minios_rlimit(long a1, long a2, long a3, long a4, long a5, long a6)` -- RLIMIT/cgroups-lite (240): a1 = op (SET/GET), a2 = resource (AS/CPU/NOFILE), a3 = value for SET.
- `sys_minios_dir_list` (function) `kernel/syscalls.c:900` `static long sys_minios_dir_list(long a1, long a2, long a3, long a4, long a5, long a6)` -- Docstring: unified directory listing for the ring-3 file browser.  a1 = path, a2 = user buffer, a3 = buffer capacity.
- `syscall_trace_enabled` (function) `kernel/syscalls.c:1072` `long syscall_trace_enabled(void)`
- `syscall_trace_set` (function) `kernel/syscalls.c:1073` `void syscall_trace_set(int on)`
- `syscall_trace_verbose_enabled` (function) `kernel/syscalls.c:1074` `long syscall_trace_verbose_enabled(void)`
- `syscall_trace_verbose_set` (function) `kernel/syscalls.c:1075` `void syscall_trace_verbose_set(int on)`
- `syscall_trace_shown` (function) `kernel/syscalls.c:1076` `unsigned long syscall_trace_shown(void)`
- `EAGAIN` (function) `kernel/syscalls.c:1109` `* writer open is EAGAIN (-11, retry);`
- `EOF` (function) `kernel/syscalls.c:1110` `* is EOF (0). */ KFILE *o = kfd_get(0);`
- `sys_linux_write` (function) `kernel/syscalls.c:1145` `static long sys_linux_write(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_writev` (function) `kernel/syscalls.c:1173` `static long sys_linux_writev(long a1, long a2, long a3, long a4, long a5, long a6)`
- `do_open_path` (function) `kernel/syscalls.c:1207` `static long do_open_path(const char *path, long flags)` -- Shared by sys_linux_open (2) and the openat fall-through (257).
- `sys_linux_open` (function) `kernel/syscalls.c:1240` `static long sys_linux_open(long a1, long a2, long a3, long a4, long a5, long a6)`
- `kfd_claim` (function) `kernel/syscalls.c:1248` `static long kfd_claim(KFILE *f)` -- Claim the lowest free fd slot for an already-opened KFILE (pipes, dup).
- `sys_linux_pipe` (function) `kernel/syscalls.c:1287` `static long sys_linux_pipe(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_dup` (function) `kernel/syscalls.c:1312` `static long sys_linux_dup(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_dup2` (function) `kernel/syscalls.c:1327` `static long sys_linux_dup2(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_close` (function) `kernel/syscalls.c:1360` `static long sys_linux_close(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_lseek` (function) `kernel/syscalls.c:1383` `static long sys_linux_lseek(long a1, long a2, long a3, long a4, long a5, long a6)`
- `mm_ensure_cur` (function) `kernel/syscalls.c:1401` `static int mm_ensure_cur(unsigned long start, unsigned long end)` -- Back isolated user windows (mrun/proc_spawn_elf): their page tables start with only segments + stack mapped, so...
- `sys_linux_brk` (function) `kernel/syscalls.c:1410` `static long sys_linux_brk(long a1, long a2, long a3, long a4, long a5, long a6)`
- `mmap_tag_file` (function) `kernel/syscalls.c:1451` `static int mmap_tag_file(unsigned long base, int ino, unsigned long off)` -- Docstring: Tag a freshly carved live node as file-backed.
- `sys_linux_mmap` (function) `kernel/syscalls.c:1460` `static long sys_linux_mmap(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_munmap` (function) `kernel/syscalls.c:1548` `static long sys_linux_munmap(long a1, long a2, long a3, long a4, long a5, long a6)`
- `mprotect_pte` (function) `kernel/syscalls.c:1580` `static volatile unsigned long *mprotect_pte(unsigned long cr3,
        unsigned long va)` -- Docstring: Locate the PTE for a user address in the caller's live tables (syscall entry keeps the caller CR3 loaded...
- `first` (function) `kernel/syscalls.c:1604` `* passes under mm_lock: validate every page first (present, user,
 * private), then apply, so a h...`
- `vma_free_cover` (function) `kernel/syscalls.c:1676` `static vma_node_t *vma_free_cover(unsigned long base, unsigned long len)` -- Free-tree node covering [base, base+len) entirely, or VMA_NIL.
- `vma_live_overlap` (function) `kernel/syscalls.c:1695` `static int vma_live_overlap(unsigned long base, unsigned long len)` -- while (x != VMA_NIL || sp > 0) { while (x != VMA_NIL) { if (sp < 64) stack[sp++] = x; x = x->left; } x =...
- `node` (function) `kernel/syscalls.c:1717` `* mapping is one exact live VMA node (what mmap inserts);`
- `sys_linux_mremap` (function) `kernel/syscalls.c:1722` `static long sys_linux_mremap(long a1, long a2, long a3, long a4, long a5, long a6)` -- Linux mremap(25): resize or move one mmap region. glibc's realloc calls it when growing large mmap'd chunks (the...
- `sys_linux_sigaction` (function) `kernel/syscalls.c:1982` `static long sys_linux_sigaction(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_sigprocmask` (function) `kernel/syscalls.c:1987` `static long sys_linux_sigprocmask(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_ioctl` (function) `kernel/syscalls.c:1992` `static long sys_linux_ioctl(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_access` (function) `kernel/syscalls.c:1997` `static long sys_linux_access(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_socket` (function) `kernel/syscalls.c:2019` `static long sys_linux_socket(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_connect` (function) `kernel/syscalls.c:2024` `static long sys_linux_connect(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_bind` (function) `kernel/syscalls.c:2030` `static long sys_linux_bind(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_listen` (function) `kernel/syscalls.c:2036` `static long sys_linux_listen(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_accept` (function) `kernel/syscalls.c:2041` `static long sys_linux_accept(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_sendto` (function) `kernel/syscalls.c:2047` `static long sys_linux_sendto(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_recvfrom` (function) `kernel/syscalls.c:2052` `static long sys_linux_recvfrom(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_shutdown` (function) `kernel/syscalls.c:2057` `static long sys_linux_shutdown(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_poll` (function) `kernel/syscalls.c:2062` `static long sys_linux_poll(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_flock` (function) `kernel/syscalls.c:2069` `static long sys_linux_flock(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_fsync` (function) `kernel/syscalls.c:2078` `static long sys_linux_fsync(long a1, long a2, long a3, long a4, long a5, long a6)` -- fsync/fdatasync: the ramdisk is memory (always durable) and MiniFS persists through kfclose/minifs_sync, so there is...
- `sys_linux_fdatasync` (function) `kernel/syscalls.c:2083` `static long sys_linux_fdatasync(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_getcwd` (function) `kernel/syscalls.c:2088` `static long sys_linux_getcwd(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_unlink` (function) `kernel/syscalls.c:2100` `static long sys_linux_unlink(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_readlink` (function) `kernel/syscalls.c:2119` `static long sys_linux_readlink(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_rename` (function) `kernel/syscalls.c:2128` `static long sys_linux_rename(long a1, long a2, long a3, long a4, long a5, long a6)` -- rename(82): same-filesystem file move through fs_rename (ramdisk in-place, MiniFS entry move).
- `sys_linux_fstat` (function) `kernel/syscalls.c:2142` `static long sys_linux_fstat(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_gettimeofday` (function) `kernel/syscalls.c:2165` `static long sys_linux_gettimeofday(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_arch_prctl` (function) `kernel/syscalls.c:2188` `static long sys_linux_arch_prctl(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_uname` (function) `kernel/syscalls.c:2200` `static long sys_linux_uname(long a1, long a2, long a3, long a4, long a5, long a6)`
- `trace_is_noisy` (function) `kernel/syscalls.c:2275` `static int trace_is_noisy(long n)`
- `syscall_name` (function) `kernel/syscalls.c:2303` `const char *syscall_name(long n)` -- define SC_EXTRA_COUNT (sizeof(sc_extra_names) / sizeof(sc_extra_names[0]))
- `trace_hint_print` (function) `kernel/syscalls.c:2344` `static void trace_hint_print(long n, int kind, const char *path,
                             lon...`
- `ksyscall` (function) `kernel/syscalls.c:2357` `long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6)`
- `user_range_ok` (function) `kernel/syscalls.c:2395` `int user_range_ok(unsigned long p, unsigned long len)`
- `Discipline` (function) `kernel/syscalls.c:2408` `* * Discipline (audit 2026-09, kept as comment, not a deprecation: both * primitives are legitimate): user_range_ok...`
- `products` (function) `kernel/syscalls.c:2412` `* products (writev cnt*sizeof, poll a2*8, spawn (argc+1)*sizeof) are
 * pre-bounded against (END-...`
- `ksyscall_dispatch` (function) `kernel/syscalls.c:2425` `static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6)`
- `proc_spawn_elf` (function) `kernel/syscalls.c:2622` `* proc_spawn_elf (the same path mrun uses) and the caller blocks in * do_waitpid, so the parent address space is...`
- `k_syscall_spawn` (function) `kernel/syscalls.c:2631` `static int k_syscall_spawn(const char *path, const char *redirect,
                             i...`

## kernel/syscalls_proc.c
Depends on: `headers/sanitize.h`, `headers/sched.h`
- `state` (function) `kernel/syscalls_proc.c:5` `* touches only scheduler state (current_pid, procs[], do_* / * seccomp_* / yield) plus the kernel-wide user_range_ok...`
- `sys_minios_clone` (function) `kernel/syscalls_proc.c:16` `long sys_minios_clone(long flags, long newsp, long a3, long a4, long a5, long a6)`
- `sys_minios_thread_spawn` (function) `kernel/syscalls_proc.c:22` `long sys_minios_thread_spawn(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_seccomp` (function) `kernel/syscalls_proc.c:35` `long sys_minios_seccomp(long a1, long a2, long a3, long a4, long a5, long a6)` -- Seccomp-basic (238): a1 = op (1 deny-one, 2 allow-one, 3 deny-all), a2 = syscall number (ops 1-2).
- `sys_minios_nice` (function) `kernel/syscalls_proc.c:52` `long sys_minios_nice(long a1, long a2, long a3, long a4, long a5, long a6)` -- if (a1 == SECCOMP_OP_DENY_ONE) return seccomp_deny_one(pid, (int)a2); if (a1 == SECCOMP_OP_ALLOW_ONE) return...
- `sys_linux_yield` (function) `kernel/syscalls_proc.c:65` `long sys_linux_yield(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_getpid` (function) `kernel/syscalls_proc.c:70` `long sys_linux_getpid(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_fork` (function) `kernel/syscalls_proc.c:75` `long sys_linux_fork(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_vfork` (function) `kernel/syscalls_proc.c:80` `long sys_linux_vfork(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_execve` (function) `kernel/syscalls_proc.c:85` `long sys_linux_execve(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_exit` (function) `kernel/syscalls_proc.c:161` `long sys_linux_exit(long a1, long a2, long a3, long a4, long a5, long a6)`
- `code` (function) `kernel/syscalls_proc.c:169` `* exit code (no WEXITSTATUS encoding: MiniOS reports codes directly). */
long sys_linux_wait4(lon...`
- `sys_linux_kill` (function) `kernel/syscalls_proc.c:188` `long sys_linux_kill(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_gettid` (function) `kernel/syscalls_proc.c:193` `long sys_linux_gettid(long a1, long a2, long a3, long a4, long a5, long a6)`

## kernel/tick.c
Depends on: `headers/tick.h`
- `tick_reset` (function) `kernel/tick.c:34` `void tick_reset(void)` -- /** Docstring: Audio listener table. static tick_slot_t tick_audio_slots[TICK_MAX_AUDIO_LISTENERS]; /** Docstring...
- `tick_register_audio` (function) `kernel/tick.c:58` `int tick_register_audio(tick_fn_t fn, void *ctx)` -- Docstring: Register an unconditional BSP audio effect.
- `tick_register_desktop` (function) `kernel/tick.c:76` `int tick_register_desktop(tick_fn_t fn, void *ctx)` -- Docstring: Register a gated desktop effect.
- `tick_register_usb` (function) `kernel/tick.c:89` `int tick_register_usb(tick_fn_t fn, void *ctx)`
- `tick_run_usb` (function) `kernel/tick.c:103` `void tick_run_usb(void)` -- int tick_register_usb(tick_fn_t fn, void *ctx) { if (fn == NULL) { return -1; } if (tick_usb_used < 0 ||...
- `tick_run_audio` (function) `kernel/tick.c:113` `void tick_run_audio(void)` -- return 0; } /** Docstring: Run USB listeners in registration order. void tick_run_usb(void) { int i; for (i = 0; i <...
- `tick_run_desktop` (function) `kernel/tick.c:123` `void tick_run_desktop(void)` -- } } /** Docstring: Run audio listeners in registration order. void tick_run_audio(void) { int i; for (i = 0; i <...
- `tick_audio_count` (function) `kernel/tick.c:133` `int tick_audio_count(void)` -- } } /** Docstring: Run desktop listeners in registration order. void tick_run_desktop(void) { int i; for (i = 0; i <...
- `tick_desktop_count` (function) `kernel/tick.c:144` `int tick_desktop_count(void)` -- } /** Docstring: Count registered audio listeners. int tick_audio_count(void) { if (tick_audio_used < 0) { return 0...
- `tick_desktop_due` (function) `kernel/tick.c:160` `int tick_desktop_due(unsigned long long ticks, unsigned interval)` -- Docstring: Pure desktop gating predicate.

## kernel/time.c
Depends on: `headers/ktime.h`
Imported by: `headers/tls_port.h`, `mcp/mcp_dbg_driver.py`, `mcp/mcp_dogfood.py`, `mcp/minios_addons.py`, `mcp/minios_mcp.py`, `progs/doomgeneric/doomgeneric_xlib.c`, `progs/tls_u/tls_u_port.c`, `tests/test_vma_bench.c`, `tools/boot_wl.py`, `tools/gdb_repro.py`, `tools/minios_cli.py`, `tools/minios_gui.py`, `tools/minios_hyper.py`, `tools/probe_compute_vga.py`, `tools/probe_minicraft.py`, `tools/qga_client.py`, `tools/repro_gui.py`, `tools/test_gui_fashion.py`, `tools/test_gui_gfxview.py`, `tools/test_gui_icon_cwd.py`, `tools/test_gui_menu.py`, `tools/test_gui_wm.py`, `tools/test_gui_zoom.py`, `tools/test_http_server.py`, `tools/tls_test.py`
- `ktime_rdtsc` (function) `kernel/time.c:13` `static unsigned long ktime_rdtsc(void)`
- `ktime_init` (function) `kernel/time.c:19` `static void ktime_init(void)`
- `ktime_ms` (function) `kernel/time.c:33` `unsigned long ktime_ms(void)`
- `ktime_us` (function) `kernel/time.c:41` `unsigned long ktime_us(void)` -- Microsecond resolution over the same calibrated ratio (Phase 0.2/0.3: clock_gettime nsec and gettimeofday usec both...

## kernel/vga_cursor.c
Depends on: `headers/kernel/vga_cursor.h`, `headers/vga_fb.h`
- `cursor_save_bg` (function) `kernel/vga_cursor.c:40` `static void cursor_save_bg(int mx, int my)` -- The cursor is drawn with its top-left corner at (mx, my), so the sprite spans down-right of the pointer.
- `cursor_is_set` (function) `kernel/vga_cursor.c:50` `static int cursor_is_set(int i, int j)` -- spans down-right of the pointer.
- `cursor_has_set_neighbour` (function) `kernel/vga_cursor.c:57` `static int cursor_has_set_neighbour(int i, int j)` -- int y0 = my - CURSOR_TIP_Y; for (j = 0; j < 8; j++) for (i = 0; i < 8; i++) cursor_save[j][i] = fb_read_packed(x0 +...
- `cursor_draw` (function) `kernel/vga_cursor.c:68` `static void cursor_draw(int mx, int my)`
- `cursor_restore` (function) `kernel/vga_cursor.c:81` `static void cursor_restore(int mx, int my)`
- `cursor_over` (function) `kernel/vga_cursor.c:96` `int cursor_over(int x0, int y0, int w, int h)` -- Docstring: True when the cursor sprite overlaps the given screen rectangle.
- `cursor_place` (function) `kernel/vga_cursor.c:106` `void cursor_place(int mx, int my)` -- Docstring: Paint the pointer at mx/my unconditionally: save the * background, draw the sprite, record the position.
- `cursor_move` (function) `kernel/vga_cursor.c:116` `void cursor_move(int mx, int my)` -- Docstring: Desktop-tick pointer update: repaint only when the position * moved since the last paint, otherwise keep...
- `cursor_erase` (function) `kernel/vga_cursor.c:133` `void cursor_erase(void)` -- Docstring: Restore the saved background when the pointer is up, then mark it hidden.
- `cursor_invalidate` (function) `kernel/vga_cursor.c:141` `void cursor_invalidate(void)` -- Docstring: Mark the pointer hidden without touching the framebuffer. * Used after any repaint that may have covered...
- `cursor_note_repaint` (function) `kernel/vga_cursor.c:147` `void cursor_note_repaint(int x0, int y0, int w, int h)` -- Docstring: Invalidate the pointer when it overlaps a repainted screen * rectangle, so the next move re-saves a fresh...

## kernel/vga_fb.c
Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/desktop_icons.h`, `headers/desktop_shortcuts.h`, `headers/drivers/kbd.h`, `headers/kernel/vga_cursor.h`, `headers/sched.h`, `headers/vga_fb.h`, `headers/vga_fx.h`, `headers/wm_events.h`, `headers/wm_focus.h`, `headers/wm_geom.h`, `headers/wm_gfxview.h`, `headers/wm_layout.h`, `headers/wm_notify.h`, `headers/wm_render.h`, `headers/wm_tiling.h`, `headers/wm_window.h`
- `wm_geom_cfg` (function) `kernel/vga_fb.c:49` `static wm_geom_config_t wm_geom_cfg(void)` -- /** Docstring: Focus ids share one space across terminals and graphics. _Static_assert(WM_FOCUS_GFX ==...
- `wm_event_cfg` (function) `kernel/vga_fb.c:60` `static wm_event_config_t wm_event_cfg(void)` -- static int wm_ggy; /** Docstring: Geometry config derived once from the font layout. static wm_geom_config_t...
- `wm_drag_reset` (function) `kernel/vga_fb.c:69` `static void wm_drag_reset(void)` -- cfg.title_h = FONT_H; return cfg; } /** Docstring: Event config for the PS/2 mouse button mask. static...
- `vga_fb_boot_config` (function) `kernel/vga_fb.c:90` `void vga_fb_boot_config(void)`
- `fb_bytes_per_pixel` (function) `kernel/vga_fb.c:117` `int fb_bytes_per_pixel(void)`
- `compositions` (function) `kernel/vga_fb.c:133` `* compositions (an ISR tick composing inside a syscall composition) draw * into the same shadow and leave the...`
- `fb_copy_bytes` (function) `kernel/vga_fb.c:151` `static void fb_copy_bytes(volatile void *dst, const volatile void *src, unsigned long n)` -- Docstring: Bulk copy through the string engine: quadwords first (rep movsq, an eighth of the iterations, which is...
- `fb_fill_u32` (function) `kernel/vga_fb.c:169` `static void fb_fill_u32(volatile void *dst, unsigned int v, unsigned long n)` -- Docstring: Fill n 32-bit words with one value: pairs as quadwords * (rep stosq), then the odd word.
- `fb_frame_bytes` (function) `kernel/vga_fb.c:183` `static unsigned long fb_frame_bytes(void)` -- static void fb_fill_u32(volatile void *dst, unsigned int v, unsigned long n) { void *d = (void *)dst; unsigned long...
- `fb_shadow_ready` (function) `kernel/vga_fb.c:189` `static int fb_shadow_ready(void)` -- : "+D"(d), "+c"(q) : "a"(pat) : "memory"); if (n & 1UL) (volatile unsigned int *)d = v; } /** Docstring: Bytes one...
- `fb_present_shadow` (function) `kernel/vga_fb.c:210` `static void fb_present_shadow(void)` -- return 1; } if (fb_shadow) { return 0; } fb_shadow = (uint8_t *)kmalloc(need); if (!fb_shadow) { return 0; }...
- `fb_compose_begin` (function) `kernel/vga_fb.c:221` `static int fb_compose_begin(void)` -- Docstring: Enter a composition.
- `fb_compose_end` (function) `kernel/vga_fb.c:234` `static void fb_compose_end(int owner)` -- entry that must not present. static int fb_compose_begin(void) { if (fb_compose_depth++ > 0) { return 0; } if...
- `lg_get` (function) `kernel/vga_fb.c:305` `static const char *lg_get(int i)` -- Docstring: Completed-logical-lines ring, heap-owned since the .bss diet (256 x TERM_MAX_COLS).
- `lg_push` (function) `kernel/vga_fb.c:312` `static void lg_push(const char *line, int len)` -- Append a completed logical line to the ring.
- `line_nrows` (function) `kernel/vga_fb.c:327` `static int line_nrows(int len)` -- int k, idx; char *dst; if (!lg) return; if (len >= SB_LINE_MAX) len = SB_LINE_MAX - 1; idx = lg_tail; dst =...
- `act_nrows` (function) `kernel/vga_fb.c:334` `static int act_nrows(void)`
- `total_rows` (function) `kernel/vga_fb.c:337` `static int total_rows(void)` -- else lg_head = (lg_head + 1) % SB_MAX_LINES; } /* Display rows a logical line of `len` characters occupies at...
- `disp_clamp` (function) `kernel/vga_fb.c:345` `static void disp_clamp(void)` -- return n; } static int act_nrows(void) { return line_nrows(act_len); } /* Total display rows of the whole history...
- `line_at` (function) `kernel/vga_fb.c:363` `static const char *line_at(int abs, int *off)` -- Locate the logical line contributing the display row `abs`, and set *off to the character offset where that display...
- `first` (function) `kernel/vga_fb.c:419` `* screen ever showing it whole first (the old flash-then-melt). */
static unsigned int *fx_start_...`
- `flag` (function) `kernel/vga_fb.c:496` `* is the minimized flag (the program keeps running, nothing composites);`
- `letterbox` (function) `kernel/vga_fb.c:500` `* present to repaint chrome plus letterbox (after a desktop redraw or a * view change);`
- `gfx_covers_screen` (function) `kernel/vga_fb.c:527` `static int gfx_covers_screen(void)` -- Docstring: 1 while a visible fullscreen graphics window owns every * pixel: the terminals, taskbar and dock must not...
- `gfx_keep_save` (function) `kernel/vga_fb.c:533` `static void gfx_keep_save(const volatile uint8_t *src, int kind, int sw, int sh)` -- Docstring: 1 while a visible fullscreen graphics window owns every * pixel: the terminals, taskbar and dock must not...
- `vga_fb_set_gfx_program` (function) `kernel/vga_fb.c:559` `void vga_fb_set_gfx_program(const char *name)`
- `shcmd_base` (function) `kernel/vga_fb.c:578` `static void shcmd_base(const char *cmd, char *out, unsigned long cap)` -- Basename of a shortcut command's program: first token after an optional `run`, then past the last '/'. "run...
- `ci_eq` (function) `kernel/vga_fb.c:595` `static int ci_eq(const char *a, const char *b)`
- `gfx_prog_icon` (function) `kernel/vga_fb.c:608` `static const uint8_t *gfx_prog_icon(void)` -- Icon of the running program via the shortcuts config: whoever composited * last, resolved through its launch command.
- `vga_fb_set_gfx_mode` (function) `kernel/vga_fb.c:621` `void vga_fb_set_gfx_mode(int on)`
- `gfx_view_for` (function) `kernel/vga_fb.c:667` `static int gfx_view_for(int sw, int sh, wm_gfxview_t *v)` -- Docstring: Compute the view for a sw x sh source under the current mode.
- `gfx_view_publish` (function) `kernel/vga_fb.c:679` `static void gfx_view_publish(const wm_gfxview_t *v)` -- mode.
- `gfx_float_frame` (function) `kernel/vga_fb.c:693` `static int gfx_float_frame(wm_gfxview_rect_t *out)` -- Docstring: Floating-mode frame of the current source, used by the * snap and drag math, which move the native...
- `vga_fb_gfx_origin` (function) `kernel/vga_fb.c:709` `void vga_fb_gfx_origin(int *x, int *y)` -- Docstring: Content origin of the graphics window (the point an app * subtracts from SYS_MOUSE coordinates), for the...
- `coordinates` (function) `kernel/vga_fb.c:723` `* windows keep the exact historical coordinates (including outside the * window);`
- `vga_fb_gfx_map_mouse` (function) `kernel/vga_fb.c:726` `void vga_fb_gfx_map_mouse(int *x, int *y)` -- Docstring: Map a desktop pointer into the graphics app's back-buffer space when its view is scaled.
- `vga_fb_gfx_cursor_erase` (function) `kernel/vga_fb.c:741` `static void vga_fb_gfx_cursor_erase(void)` -- Restore the last composite's pointer before the new frame covers it.
- `vga_fb_gfx_cursor_draw` (function) `kernel/vga_fb.c:751` `static void vga_fb_gfx_cursor_draw(void)` -- Clamp the mouse into the framebuffer (the idle loop that normally clamps never runs in graphics mode) and draw the...
- `gfx_transition` (function) `kernel/vga_fb.c:917` `static void gfx_transition(const wm_gfxview_rect_t *from, int from_titled);`
- `wm_focus_cursor_sync` (function) `kernel/vga_fb.c:942` `static void wm_focus_cursor_sync(const wm_notify_event_t *e)` -- char eline[WM_ELINE_SZ]; int epos, has_line; int prompted; } termwin_t; static termwin_t twins[WM_MAX_TERMS]; static...
- `wm_emit_focus_moved` (function) `kernel/vga_fb.c:949` `static void wm_emit_focus_moved(int before, int source)` -- static int wm_term; static int wm_inited; /** Docstring: Single focus event bus owned by the desktop. static...
- `vga_fb_focus_event` (function) `kernel/vga_fb.c:961` `const wm_notify_event_t *vga_fb_focus_event(void)` -- /** Docstring: Emit one focus event when the id actually moved. static void wm_emit_focus_moved(int before, int...
- `vga_fb_focus_report` (function) `kernel/vga_fb.c:967` `void vga_fb_focus_report(int before, int source)` -- e.type = WM_NOTIFY_FOCUS; e.old_focus = before; e.new_focus = wm_focus; e.source = source; wm_notify_emit(&wm_bus...
- `tw_park` (function) `kernel/vga_fb.c:976` `static void tw_park(int i)`
- `tw_unpark` (function) `kernel/vga_fb.c:1006` `static void tw_unpark(int i)`
- `wm_init_once` (function) `kernel/vga_fb.c:1041` `static void wm_init_once(void)`
- `tw_select` (function) `kernel/vga_fb.c:1066` `static void tw_select(int i)` -- twins[k].has_line = 0; twins[k].eline[0] = '\0'; twins[k].epos = 0; twins[k].prompted = 0; } twins[0].lg = lg; if...
- `vga_fb_focus_get` (function) `kernel/vga_fb.c:1078` `int vga_fb_focus_get(void)`
- `vga_fb_nterms_get` (function) `kernel/vga_fb.c:1079` `int vga_fb_nterms_get(void)`
- `wm_snapshot_state` (function) `kernel/vga_fb.c:1082` `static void wm_snapshot_state(wm_focus_state_t *st)` -- if (!twins[i].present) return; if (shell_readline_active()) shell_focus_park(); tw_park(wm_term); wm_focus = i...
- `vga_fb_focus_next` (function) `kernel/vga_fb.c:1095` `void vga_fb_focus_next(void)` -- /** Docstring: Single snapshot of every window for focus decisions. static void wm_snapshot_state(wm_focus_state_t...
- `app` (function) `kernel/vga_fb.c:1136` `* a gfx child spawned from another gfx app (file -> vedit) keeps the * terminal focused, so its keys and wheel keep...`
- `wm_gfx_focus_sync` (function) `kernel/vga_fb.c:1141` `static void wm_gfx_focus_sync(int on)` -- Docstring: Route WM focus with the graphics mode switch.
- `vga_fb_focus_id` (function) `kernel/vga_fb.c:1160` `int vga_fb_focus_id(int id)` -- tw_park(wm_term); wm_focus = WM_FOCUS_GFX; kbd_raw_flush(); wm_emit_focus_moved(before, WM_FOCUS_SRC_MODE); } } else...
- `content` (function) `kernel/vga_fb.c:1193` `* windows would share content (same prompt/output on both) and a park
 * would alias src == dst. ...`
- `vga_fb_layout_set` (function) `kernel/vga_fb.c:1274` `int vga_fb_layout_set(int mode)` -- twins[1].lg = 0; twins[1].present = 0; twins[1].has_line = 0; twins[1].eline[0] = '\0'; twins[1].epos = 0...
- `vga_fb_layout_cycle` (function) `kernel/vga_fb.c:1285` `void vga_fb_layout_cycle(void)` -- /** Docstring: Tile terminals through the tiling contract, graphics right. /** Docstring: Set active layout mode...
- `vga_fb_layout_get` (function) `kernel/vga_fb.c:1301` `int vga_fb_layout_get(void)` -- if (wm_layout_mode == WM_LAYOUT_TILE) { wm_layout_mode = WM_LAYOUT_BSP; } else if (wm_layout_mode == WM_LAYOUT_BSP)...
- `vga_fb_layout_name` (function) `kernel/vga_fb.c:1307` `const char *vga_fb_layout_name(void)` -- } else { wm_layout_mode = WM_LAYOUT_TILE; } wm_last_n = -1; vga_fb_tile_all(); } /** Docstring: Active layout mode...
- `alone` (function) `kernel/vga_fb.c:1319` `* window alone (an unfocused graphics window minimizes to the taskbar,
 * exactly like the hidden...`
- `vga_fb_list_windows` (function) `kernel/vga_fb.c:1446` `void vga_fb_list_windows(void)`
- `vga_fb_act_empty` (function) `kernel/vga_fb.c:1504` `int vga_fb_act_empty(void)` -- vn ? vn : "floating", gfx_view_valid ? gfx_view.content.x : gfx_win_x, gfx_view_valid ? gfx_view.content.y...
- `vga_fb_note_prompt` (function) `kernel/vga_fb.c:1508` `void vga_fb_note_prompt(void)` -- The shell loop calls note after printing a prompt (it is live in the * focused window) and clear once the line is...
- `vga_fb_clear_prompt` (function) `kernel/vga_fb.c:1513` `void vga_fb_clear_prompt(void)`
- `vga_fb_prompted` (function) `kernel/vga_fb.c:1518` `int vga_fb_prompted(void)`
- `vga_fb_prompt_live` (function) `kernel/vga_fb.c:1527` `int vga_fb_prompt_live(void)` -- 1 when the active line is empty or holds exactly a fresh prompt, so printing another one would stack duplicate...
- `vga_fb_park_line` (function) `kernel/vga_fb.c:1534` `void vga_fb_park_line(const char *b, int p)` -- 1 when the active line is empty or holds exactly a fresh prompt, so printing another one would stack duplicate...
- `vga_fb_unpark_line` (function) `kernel/vga_fb.c:1549` `int vga_fb_unpark_line(char *b, int *p)` -- A fresh prompt parks empty: record no line, so `wm list` does not * claim a half-typed command that never existed....
- `tw_hit` (function) `kernel/vga_fb.c:1564` `static int tw_hit(int i, int mx, int my)` -- termwin_t *t; int k; wm_init_once(); if (wm_focus < 0 || wm_focus >= WM_MAX_TERMS) return 0; t = &twins[wm_focus]...
- `vga_fb_set_gfx_palette` (function) `kernel/vga_fb.c:1670` `void vga_fb_set_gfx_palette(const unsigned char *pal)`
- `fb_pack_idx` (function) `kernel/vga_fb.c:1685` `static unsigned long fb_pack_idx(unsigned idx)` -- --- True-color pixel layer ---- VBE true-color framebuffers store pixels natively as B,G,R(,X) bytes, so the DAC is...
- `fb_write_packed` (function) `kernel/vga_fb.c:1701` `void fb_write_packed(int x, int y, unsigned long rgb)`
- `fb_read_packed` (function) `kernel/vga_fb.c:1721` `unsigned long fb_read_packed(int x, int y)`
- `vga_fb_read_rgb` (function) `kernel/vga_fb.c:1745` `unsigned long vga_fb_read_rgb(int x, int y)`
- `fb_write_row_packed` (function) `kernel/vga_fb.c:1750` `void fb_write_row_packed(int x, int y, const unsigned int *src, int n)` -- Docstring: Write n packed pixels (0x00RRGGBB, or raw indices in 8-bit mode) to row y from column x, clipped once.
- `fb_read_row_packed` (function) `kernel/vga_fb.c:1780` `void fb_read_row_packed(int x, int y, unsigned int *dst, int n)` -- Docstring: Read n packed pixels of row y from column x into dst, * clipped once; pixels outside the screen read as 0.
- `fb_fill_run` (function) `kernel/vga_fb.c:1802` `static void fb_fill_run(int x, int y, int n, unsigned long px)` -- int xx = x + i; if (xx < 0 || xx >= fb_width) continue; if (fb_bpp == 32) { dst[i] = *(volatile unsigned int *)(p +...
- `wall_level` (function) `kernel/vga_fb.c:1828` `static int wall_level(int v)` -- for (i = 0; i < n; i++) { q[0] = (uint8_t)(px & 0xFF); q[1] = (uint8_t)((px >> 8) & 0xFF); q[2] = (uint8_t)((px >>...
- `vga_fb_set_palette` (function) `kernel/vga_fb.c:1837` `static void vga_fb_set_palette(void)`
- `fb_glyph` (function) `kernel/vga_fb.c:1890` `static const uint8_t *fb_glyph(unsigned char c)` -- Resolve one byte to its 8-row glyph: ASCII through font8x8, Spanish Latin-1 through the table above, anything else...
- `vga_fb_pixel` (function) `kernel/vga_fb.c:1911` `void vga_fb_pixel(int x, int y, uint8_t color)` -- case 0xAC: return glyph_notsign; case 0xB4: return glyph_acute; case 0xB7: return glyph_middot; case 0xBA: return...
- `vga_fb_clear` (function) `kernel/vga_fb.c:1921` `void vga_fb_clear(void)` -- } } /* ---- Drawing primitives ---- void vga_fb_pixel(int x, int y, uint8_t color) { if (fb_bpp == 8) { if (x >= 0...
- `vga_fb_rect` (function) `kernel/vga_fb.c:1931` `void vga_fb_rect(int x, int y, int w, int h, uint8_t color)` -- Docstring: Solid rectangle: the color resolves once, every row is one * clipped run fill instead of a per-pixel...
- `vga_fb_pixel_rgb` (function) `kernel/vga_fb.c:1946` `void vga_fb_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b)` -- Direct RGB pixel: full color depth in true-color modes, best-effort quantization in 8-bit mode.
- `vga_fb_rect_rgb` (function) `kernel/vga_fb.c:1955` `void vga_fb_rect_rgb(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b)`
- `vga_fb_char` (function) `kernel/vga_fb.c:1962` `void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg)`
- `vga_fb_str` (function) `kernel/vga_fb.c:1976` `void vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg)`
- `text_px` (function) `kernel/vga_fb.c:1987` `static void text_px(int px, int py, const char *s, uint8_t fg, uint8_t bg)` -- Blit a text string at an absolute pixel position.
- `wm_draw_buttons` (function) `kernel/vga_fb.c:2013` `static void wm_draw_buttons(int px, int py, int win_w, uint8_t fg, uint8_t bg)` -- --- Window controls ---- Three glyph buttons at the right end of a window's title bar: minimize (_), maximize...
- `wm_buttons_hit` (function) `kernel/vga_fb.c:2039` `static int wm_buttons_hit(int mx, int my, int win_x, int win_y, int win_w)` -- } for (i = 1; i < WM_BTN_H - 1; i++) { vga_fb_pixel(bx + 1, by + i, fg); vga_fb_pixel(bx + WM_BTN_W - 2, by + i...
- `wm_close_pending` (function) `kernel/vga_fb.c:2054` `int wm_close_pending(void)` -- Close request bridge: the syscall dispatcher polls this so a graphics * program's next syscall exits it on the...
- `wm_clear_close` (function) `kernel/vga_fb.c:2055` `void wm_clear_close(void)`
- `wm_gfx_mode_active` (function) `kernel/vga_fb.c:2056` `int wm_gfx_mode_active(void)`
- `vga_fb_ps2_owner` (function) `kernel/vga_fb.c:2059` `int vga_fb_ps2_owner(int pid)` -- Close request bridge: the syscall dispatcher polls this so a graphics * program's next syscall exits it on the...
- `taskbar` (function) `kernel/vga_fb.c:2079` `* minimize hides the app to the taskbar (it never closes it), maximize
 * toggles true fullscreen...`
- `directly` (function) `kernel/vga_fb.c:2127` `* RGB sources pack directly (quantized to the wallpaper cube in 8-bit). */
static void gfx_scale_...`
- `gfx_letterbox` (function) `kernel/vga_fb.c:2232` `static void gfx_letterbox(const wm_gfxview_t *v)` -- Docstring: Clear the frame area the content does not cover (the * letterbox bars of a tiled or fullscreen view) to...
- `gfx_title` (function) `kernel/vga_fb.c:2251` `static void gfx_title(const wm_gfxview_t *v)` -- int ah = v->frame.h - v->title_h; const wm_gfxview_rect_t *c = &v->content; if (aw <= 0 || ah <= 0) return; if (c->y...
- `gfx_compose` (function) `kernel/vga_fb.c:2263` `static void gfx_compose(const volatile uint8_t *src, int kind, int sw, int sh,
                  ...` -- Docstring: Compose one graphics frame at a view into the render target: * title, letterbox (when full is set) and...
- `vga_fb_blit_gfx_window` (function) `kernel/vga_fb.c:2326` `void vga_fb_blit_gfx_window(void)`
- `vga_fb_blit_nk_window` (function) `kernel/vga_fb.c:2335` `void vga_fb_blit_nk_window(void)`
- `vga_fb_blit_nk_rgb_window` (function) `kernel/vga_fb.c:2341` `void vga_fb_blit_nk_rgb_window(void)` -- Composite the Nuklear RGB back-buffer (NK_RGB_ADDR, NK_W x NK_H x 3 bytes) * through the same present path as the...
- `term_recalc` (function) `kernel/vga_fb.c:2350` `static void term_recalc(void)`
- `draw_title_win` (function) `kernel/vga_fb.c:2376` `static void draw_title_win(int idx, int focused)` -- Preserve the current window position, clamping it into range so a * drag or Ctrl+arrow move is not undone by the...
- `taskbar_layout` (function) `kernel/vga_fb.c:2407` `static void taskbar_layout(void)`
- `draw_speaker_icon` (function) `kernel/vga_fb.c:2438` `static void draw_speaker_icon(int x, int y, uint8_t color)` -- Running-app button right after it: mini icon + title while a graphics program owns the display.
- `taskbar_render` (function) `kernel/vga_fb.c:2447` `static void taskbar_render(void)`
- `title` (function) `kernel/vga_fb.c:2457` `* 8px row plus its title (bright when focused). The hint line * starts after it instead of underneath. */ const...`
- `taskbar_tick` (function) `kernel/vga_fb.c:2526` `static void taskbar_tick(void)` -- Redraw the clock only when the wall-clock second changes.
- `vga_fb_theme_name` (function) `kernel/vga_fb.c:2542` `int vga_fb_theme_name(char *dst, int cap)` -- Docstring: Active Nuklear theme name for the taskbar widget.
- `taskbar_theme_cycle` (function) `kernel/vga_fb.c:2563` `static void taskbar_theme_cycle(void)` -- Cycle the active theme to the next etc/themes/ entry (ramdisk).
- `taskbar_handle_click` (function) `kernel/vga_fb.c:2603` `static void taskbar_handle_click(int mx, int my)` -- Click handling for the keyboard widget, the speaker icon and -/+ buttons, plus the restore button that reappears...
- `draw_scrollbar` (function) `kernel/vga_fb.c:2663` `static void draw_scrollbar(void)` -- return; } if (mx >= tb_minus_x && mx < tb_minus_x + TASKBAR_BTN_W) { v = pcspk_get_volume(); pcspk_set_volume(v >...
- `render_blank_row` (function) `kernel/vga_fb.c:2698` `static void render_blank_row(int vrow)` -- Blank one viewport row: every cell is repainted with the terminal background. vga_fb_str with an empty string would...
- `render_row` (function) `kernel/vga_fb.c:2708` `static void render_row(int vrow, int abs)` -- Render one display row at viewport row `vrow` for the absolute display row `abs`.
- `term_render` (function) `kernel/vga_fb.c:2743` `static void term_render(void)`
- `buffer` (function) `kernel/vga_fb.c:2758` `* owns the buffer (indices reset, render reads an empty ring). */
void term_clear(void)`
- `term_render_active` (function) `kernel/vga_fb.c:2775` `static void term_render_active(void)` -- Repaint only the bottom region that a live edit touches: from the active line's first visible display row to the...
- `line` (function) `kernel/vga_fb.c:2818` `* display stale bytes left over from a longer previous line (e.g. the prompt
 * would show the ta...`
- `escapes` (function) `kernel/vga_fb.c:2827` `* swallowing them here keeps the escapes (which the serial side needs)
     * from printing as li...`
- `vga_fb_puts_term` (function) `kernel/vga_fb.c:2884` `void vga_fb_puts_term(const char *s)`
- `vga_fb_text_cursor` (function) `kernel/vga_fb.c:2890` `void vga_fb_text_cursor(int col)` -- Show the text cursor at character column `col` of the active line, or hide * it with a negative column.
- `vga_fb_hide_text_cursor` (function) `kernel/vga_fb.c:2898` `void vga_fb_hide_text_cursor(void)` -- Show the text cursor at character column `col` of the active line, or hide * it with a negative column.
- `vga_fb_draw_desktop` (function) `kernel/vga_fb.c:2922` `void vga_fb_draw_desktop(void)` -- Docstring: Repaint the desktop through the shared render plan.
- `gfx_view_in_rect` (function) `kernel/vga_fb.c:3017` `static void gfx_view_in_rect(const wm_gfxview_rect_t *r, int titled, wm_gfxview_t *v)` -- Docstring: View of the persistent source inside an arbitrary frame, * titled when the frame is tall enough to carry...
- `gfx_animate` (function) `kernel/vga_fb.c:3036` `static void gfx_animate(const wm_gfxview_rect_t *from, const wm_gfxview_rect_t *to,
             ...` -- Docstring: Glide the persistent source frame from one rect to * another over the desktop, then settle with a plain...
- `gfx_taskbar_rect` (function) `kernel/vga_fb.c:3086` `static void gfx_taskbar_rect(wm_gfxview_rect_t *r)` -- fb_tgt = fb_shadow; gfx_compose(gfx_keep, gfx_keep_kind, gfx_keep_sw, gfx_keep_sh, &v, 0); fb_tgt = 0...
- `gfx_drop_focus` (function) `kernel/vga_fb.c:3123` `static void gfx_drop_focus(int source)` -- Docstring: Hand keyboard focus to the graphics window without a * redraw (callers repaint once afterwards). static...
- `from` (function) `kernel/vga_fb.c:3134` `* leaving returns to the view it came from (floating or tiled). Returns
 * 0 on success, -1 witho...`
- `vga_fb_gfx_set_hidden` (function) `kernel/vga_fb.c:3168` `int vga_fb_gfx_set_hidden(int hide)` -- Docstring: Minimize (hide) or restore the graphics window.
- `vga_fb_gfx_view_name` (function) `kernel/vga_fb.c:3196` `const char *vga_fb_gfx_view_name(void)` -- if (gfx_view_valid) gfx_animate(&from, &btn, titled, 0); else vga_fb_draw_desktop(); return 0; } gfx_hidden = 0...
- `term_toggle_fullscreen` (function) `kernel/vga_fb.c:3208` `static void term_toggle_fullscreen(void)` -- /** Docstring: Graphics view state for `wm state`/`wm list`. const char *vga_fb_gfx_view_name(void) { const char *n...
- `vga_fb_toggle_fullscreen` (function) `kernel/vga_fb.c:3220` `void vga_fb_toggle_fullscreen(void)` -- Docstring: Toggle fullscreen on the focused window: the graphics * window scales to the whole display, a terminal...
- `term_toggle_minimize` (function) `kernel/vga_fb.c:3231` `static void term_toggle_minimize(void)` -- Minimize/restore the terminal window.
- `vga_fb_toggle_minimize` (function) `kernel/vga_fb.c:3241` `void vga_fb_toggle_minimize(void)` -- Minimize/restore the terminal window.
- `vga_fb_is_minimized` (function) `kernel/vga_fb.c:3249` `int vga_fb_is_minimized(void)`
- `vga_fb_is_fullscreen` (function) `kernel/vga_fb.c:3250` `int vga_fb_is_fullscreen(void)`
- `gfx_snap` (function) `kernel/vga_fb.c:3255` `static void gfx_snap(int zone)` -- Snap the focused graphics window into a screen region (halves place it against that edge, quadrants into that...
- `term_close_default` (function) `kernel/vga_fb.c:3288` `static void term_close_default(void)` -- Docstring: Terminal close button: restore the default geometry (the * shell cannot be closed).
- `vga_fb_close_active` (function) `kernel/vga_fb.c:3304` `int vga_fb_close_active(void)` -- Close the focused window.
- `vga_fb_move_terminal` (function) `kernel/vga_fb.c:3318` `void vga_fb_move_terminal(int dx, int dy)`
- `term_max_cols` (function) `kernel/vga_fb.c:3363` `static int term_max_cols(void)` -- --- Tiling window operations (Alt = WM modifier) ---- Snap places the window in a screen half or quadrant and sizes...
- `term_max_rows` (function) `kernel/vga_fb.c:3367` `static int term_max_rows(void)`
- `term_finish_layout` (function) `kernel/vga_fb.c:3372` `static void term_finish_layout(void)`
- `vga_fb_snap_window` (function) `kernel/vga_fb.c:3378` `void vga_fb_snap_window(int zone)`
- `vga_fb_resize` (function) `kernel/vga_fb.c:3406` `void vga_fb_resize(int dcols, int drows)`
- `vga_fb_reset_default` (function) `kernel/vga_fb.c:3426` `void vga_fb_reset_default(void)` -- int ncol = term_sz_cols + dcols; int nrow = term_sz_rows + drows; if (ncol < 1) ncol = 1; if (nrow < 1) nrow = 1; if...
- `wallpaper_ensure` (function) `kernel/vga_fb.c:3480` `static void wallpaper_ensure(void)`
- `wallpaper_usable` (function) `kernel/vga_fb.c:3532` `static int wallpaper_usable(void)` -- d[2] = px[0]; if (bpx == 4) d[3] = 0; } } } stbi_image_free(img); wall_native = cache; wall_cw = fb_width; wall_ch =...
- `wallpaper_draw` (function) `kernel/vga_fb.c:3537` `static void wallpaper_draw(void)`
- `pipe_field` (function) `kernel/vga_fb.c:3563` `static const char *pipe_field(const char *line, int idx, char *buf, int buflen)` -- --- Desktop shortcut icons ---- Shortcuts are defined in etc/shortcuts on the ramdisk, one per line...
- `icon_nearest` (function) `kernel/vga_fb.c:3581` `static int icon_nearest(int r, int g, int b)` -- Nearest entry in the 16-colour icon palette (squared RGB distance, * integer-only: at most 3*255*255 per entry, far...
- `icon_embedded` (function) `kernel/vga_fb.c:3597` `static const uint8_t *icon_embedded(const char *name)` -- for (i = 0; i < ICON_PAL_SIZE; i++) { int dr = r - icon_pal[i][0]; int dg = g - icon_pal[i][1]; int db = b...
- `icon_decode` (function) `kernel/vga_fb.c:3617` `static const uint8_t *icon_decode(const char *path)` -- Decode a shortcut's PNG to raw 32x32 RGBA pixels.
- `icon_embedded_rgba` (function) `kernel/vga_fb.c:3651` `static const uint8_t *icon_embedded_rgba(const uint8_t *idx)` -- Expand an embedded index icon (desktop_icons.h, transparent 0) to RGBA through the icon palette, so fallback art...
- `dock_label_px` (function) `kernel/vga_fb.c:3679` `static int dock_label_px(const struct desktop_shortcut *sc)` -- Width of the longest shortcut label in pixels (cached after load).
- `shortcuts_layout` (function) `kernel/vga_fb.c:3688` `static void shortcuts_layout(void)` -- Dock layout: one centred row just above the taskbar.
- `shortcut_cell_left` (function) `kernel/vga_fb.c:3706` `static int shortcut_cell_left(int i)` -- dock_h = ICON_H + DOCK_LABEL_GAP + ICON_LABEL_H + 2 * DOCK_PAD_Y; x0 = (fb_width - dock_w) / 2; if (x0 < 0) x0 = 0...
- `desktop_shortcuts_load` (function) `kernel/vga_fb.c:3713` `void desktop_shortcuts_load(void)`
- `shortcut_draw_scaled` (function) `kernel/vga_fb.c:3769` `static void shortcut_draw_scaled(const struct desktop_shortcut *sc,
                             ...` -- Blit one shortcut icon scaled to dw x dh at (dx, dy), nearest neighbour from the cached 32x32 RGBA source.
- `dock_hover_index` (function) `kernel/vga_fb.c:3794` `static int dock_hover_index(int mx, int my)` -- Index of the shortcut column under (mx, my), or -1.
- `dock_bounce_counts` (function) `kernel/vga_fb.c:3821` `void dock_bounce_counts(unsigned long *kicks, unsigned long *paints)`
- `dock_click_count` (function) `kernel/vga_fb.c:3831` `void dock_click_count(unsigned long *edges)`
- `dock_bounce_elapsed` (function) `kernel/vga_fb.c:3837` `static unsigned long dock_bounce_elapsed(void)` -- Ticks elapsed since the bounce click, capped so the subtraction can * never wrap on a late read.
- `dock_bounce_live` (function) `kernel/vga_fb.c:3845` `static int dock_bounce_live(void)` -- Ticks elapsed since the bounce click, capped so the subtraction can * never wrap on a late read. static unsigned...
- `dock_pending_active` (function) `kernel/vga_fb.c:3895` `int dock_pending_active(void)`
- `dock_paint_icons` (function) `kernel/vga_fb.c:3903` `static void dock_paint_icons(int hover)` -- Paint every shortcut icon and label at the given hover sizes.
- `desktop_shortcuts_draw` (function) `kernel/vga_fb.c:3939` `void desktop_shortcuts_draw(void)`
- `wallpaper_rect` (function) `kernel/vga_fb.c:3966` `static void wallpaper_rect(int x0, int y0, int w, int h)` -- Paint one wallpaper rectangle from the cache (solid fill when the cache * is absent or stale): the strip-erase...
- `dock_paint_hover` (function) `kernel/vga_fb.c:3997` `static void dock_paint_hover(int hover)` -- Hover repaint without the fullscreen flash: erase only the dock strip (bar plus the overflow the magnified icons...
- `command` (function) `kernel/vga_fb.c:4028` `* its launch command (config-driven, covers apps that never set a window * title);`
- `gfx_task_icon` (function) `kernel/vga_fb.c:4033` `static const uint8_t *gfx_task_icon(void)` -- Icon for the taskbar running-app button.
- `desktop_shortcuts_hit_test` (function) `kernel/vga_fb.c:4054` `const char *desktop_shortcuts_hit_test(int mx, int my)`
- `mouse_focus_topmost` (function) `kernel/vga_fb.c:4068` `static int mouse_focus_topmost(int mx, int my)` -- const char *desktop_shortcuts_hit_test(int mx, int my) { shortcuts_layout(); for (int i = 0; i < shortcut_count...
- `mouse_apply_wheel` (function) `kernel/vga_fb.c:4094` `static void mouse_apply_wheel(int wheel, int step)` -- if (!twins[f].present) continue; if (tw_hit(f, mx, my)) { if (f == wm_focus) return 0; before = wm_focus...
- `pointer` (function) `kernel/vga_fb.c:4115` `* tiled window floats it at native size under the pointer (the grab point * keeps its relative position along the...`
- `mouse_drag_gfx` (function) `kernel/vga_fb.c:4118` `static void mouse_drag_gfx(const wm_geom_config_t *gcfg, int mx, int my)` -- Docstring: Title-bar drag of the graphics window.
- `mouse_drag_term` (function) `kernel/vga_fb.c:4170` `static void mouse_drag_term(const wm_geom_config_t *gcfg, int win_w, int mx, int my, int gfx_cursor)` -- Docstring: Title-bar drag of the focused terminal window.
- `mouse_scrollbar` (function) `kernel/vga_fb.c:4193` `static void mouse_scrollbar(const wm_geom_config_t *gcfg, int mx, int my)` -- wm_grab_cx = (mx - term_px_x) / FONT_W; } } else { wm_dragging = 0; } if (wm_dragging) { vga_fb_drag_terminal(mx...
- `vga_fb_mouse_tick` (function) `kernel/vga_fb.c:4216` `void vga_fb_mouse_tick(void)` -- total = total_rows(); visible = term_rows; if (total <= visible || sh <= 0) return; max_off = total - visible...
- `path` (function) `kernel/vga_fb.c:4227` `* present path (blit_gfx_buf) is the sole cursor painter. The tick * used to share the sprite state with it and...`
- `state` (function) `kernel/vga_fb.c:4339` `* ignores the button state (the arming press is consumed) and settles
     * once on expiry, so t...`
- `vga_fb_mouse_init` (function) `kernel/vga_fb.c:4417` `void vga_fb_mouse_init(void)`
- `vga_fb_init` (function) `kernel/vga_fb.c:4445` `void vga_fb_init(void)`

## kernel/vga_fx.c
Depends on: `headers/vga_fb.h`, `headers/vga_fx.h`
- `vga_fx_set_enabled` (function) `kernel/vga_fx.c:22` `void vga_fx_set_enabled(int on)`
- `vga_fx_enabled` (function) `kernel/vga_fx.c:27` `int vga_fx_enabled(void)`
- `fx_wait_until` (function) `kernel/vga_fx.c:35` `static void fx_wait_until(unsigned long deadline)` -- Deadline pacing over the PIT-calibrated TSC clock.
- `vga_fx_snap_rect` (function) `kernel/vga_fx.c:41` `unsigned int *vga_fx_snap_rect(int x, int y, int w, int h)`
- `vga_fx_restore_rect` (function) `kernel/vga_fx.c:63` `void vga_fx_restore_rect(int x, int y, int w, int h, const unsigned int *buf)`
- `vga_fx_free` (function) `kernel/vga_fx.c:77` `void vga_fx_free(unsigned int *buf)`
- `once` (function) `kernel/vga_fx.c:90` `* once (prev[] tracks the revealed frontier per column), then the final
 * restore guarantees the...`
- `vga_fx_melt_rect` (function) `kernel/vga_fx.c:150` `void vga_fx_melt_rect(int x, int y, int w, int h,
    const unsigned int *oldb, const unsigned in...` -- Drive one old->new melt.
- `vga_fx_melt_from_black` (function) `kernel/vga_fx.c:159` `void vga_fx_melt_from_black(int x, int y, int w, int h, const unsigned int *newb)` -- Boot melt: the framebuffer is already cleared to black on entry, so no * old snapshot is needed; the new frame...

## mcp/mcp_dbg_driver.py
Depends on: `kernel/time.c`
- `Client.__init__` (method) `mcp/mcp_dbg_driver.py:16` `def __init__(self)`
- `Client.request` (method) `mcp/mcp_dbg_driver.py:28` `def request(self, method, params)`
- `Client.tool` (method) `mcp/mcp_dbg_driver.py:46` `def tool(self, name, params)`
- `Client.close` (method) `mcp/mcp_dbg_driver.py:54` `def close(self)`
- `Client.main` (method) `mcp/mcp_dbg_driver.py:64` `def main()`

## mcp/mcp_dogfood.py
Depends on: `kernel/time.c`
- `Client.__init__` (method) `mcp/mcp_dogfood.py:20` `def __init__(self, addons_dir)`
- `Client.request` (method) `mcp/mcp_dogfood.py:40` `def request(self, method, params)`
- `Client.tool` (method) `mcp/mcp_dogfood.py:58` `def tool(self, name, params)`
- `Client.close` (method) `mcp/mcp_dogfood.py:68` `def close(self)`
- `Client.main` (method) `mcp/mcp_dogfood.py:78` `def main()`

## mcp/minios_addons.py
Depends on: `kernel/time.c`
Imported by: `mcp/minios_mcp.py`
- `AddonError.parse_addon_yaml` (method) `mcp/minios_addons.py:73` `def parse_addon_yaml(text)` -- Parse the strict YAML subset.
- `AddonError.fail` (method) `mcp/minios_addons.py:85` `def fail(lineno, why)`
- `AddonError.validate_addon` (method) `mcp/minios_addons.py:205` `def validate_addon(addon, source)` -- Check bounds and character sets.
- `AddonError.validate_addon_path` (method) `mcp/minios_addons.py:295` `def validate_addon_path(path)` -- dst paths live on the ramdisk: relative, no '..', bounded charset.
- `AddonError.validate_shell_line` (method) `mcp/minios_addons.py:309` `def validate_shell_line(line)` -- Build/verify lines are single printable-ASCII shell commands.
- `AddonError.load_addons_dir` (method) `mcp/minios_addons.py:323` `def load_addons_dir(addons_dir)` -- Load every addon yaml; each entry is a dict or an error string.
- `AddonError.split_for_editor` (method) `mcp/minios_addons.py:347` `def split_for_editor(text)` -- Split a source into editor-sized chunks.
- `AddonError.exit_code_of` (method) `mcp/minios_addons.py:372` `def exit_code_of(text)`
- `AddonState.__init__` (method) `mcp/minios_addons.py:380` `def __init__(self, path)`
- `AddonState.load` (method) `mcp/minios_addons.py:383` `def load(self)`
- `AddonState.save` (method) `mcp/minios_addons.py:393` `def save(self, addons)`
- `AddonState.install_addon` (method) `mcp/minios_addons.py:401` `def install_addon(session, addon, cfg)` -- Install one validated addon into the booted MiniOS session.

## mcp/minios_mcp.py
Depends on: `kernel/time.c`, `mcp/minios_addons.py`
- `env_config` (function) `mcp/minios_mcp.py:68` `def env_config()` -- Resolve the configuration: defaults overridden by the environment.
- `clamp_timeout` (function) `mcp/minios_mcp.py:86` `def clamp_timeout(ms)` -- Clamp a requested wait to the bounded timeout range.
- `validate_path` (function) `mcp/minios_mcp.py:99` `def validate_path(name)` -- Reject file names the ramdisk or the shell would mishandle.
- `validate_content` (function) `mcp/minios_mcp.py:115` `def validate_content(text)` -- Reject lines the kernel readline cannot carry (printable ASCII).
- `RPCError.__init__` (method) `mcp/minios_mcp.py:137` `def __init__(self, code, message)`
- `LogBuffer.__init__` (method) `mcp/minios_mcp.py:146` `def __init__(self, cap)`
- `LogBuffer.append` (method) `mcp/minios_mcp.py:152` `def append(self, data)`
- `LogBuffer.bytes_from` (method) `mcp/minios_mcp.py:160` `def bytes_from(self, pos)`
- `LogBuffer.text_from` (method) `mcp/minios_mcp.py:165` `def text_from(self, pos, end)`
- `LogBuffer.find` (method) `mcp/minios_mcp.py:172` `def find(self, marker, start)`
- `LogBuffer.wait_for` (method) `mcp/minios_mcp.py:176` `def wait_for(self, marker, start, timeout_ms)` -- Block until marker appears at or after start; return position.
- `MiniOSSession.__init__` (method) `mcp/minios_mcp.py:202` `def __init__(self, cfg)`
- `MiniOSSession.booted` (method) `mcp/minios_mcp.py:213` `def booted(self)`
- `MiniOSSession.status` (method) `mcp/minios_mcp.py:216` `def status(self)`
- `MiniOSSession.boot` (method) `mcp/minios_mcp.py:267` `def boot(self, timeout_ms)`
- `MiniOSSession.send` (method) `mcp/minios_mcp.py:339` `def send(self, line, timeout_ms)`
- `MiniOSSession.expect` (method) `mcp/minios_mcp.py:350` `def expect(self, marker, timeout_ms)`
- `MiniOSSession.snapshot` (method) `mcp/minios_mcp.py:364` `def snapshot(self, max_bytes)`
- `MiniOSSession.run_test` (method) `mcp/minios_mcp.py:374` `def run_test(self, commands, expect, refute, timeout_ms)` -- Run a generic scenario: send a list of shell commands, then assert that each expected marker appears (and each...
- `MiniOSSession.cat` (method) `mcp/minios_mcp.py:430` `def cat(self, path)`
- `MiniOSSession.run_python` (method) `mcp/minios_mcp.py:436` `def run_python(self, script, args, timeout_ms)` -- Run a MicroPython script (or `-c` code) inside MiniOS and return its output, including the `exit code: N` line.
- `MiniOSSession.cat_body` (method) `mcp/minios_mcp.py:447` `def cat_body(self, path, missing_ok)` -- Read a ramdisk file and return exactly its bytes.
- `MiniOSSession.write` (method) `mcp/minios_mcp.py:480` `def write(self, path, content)`
- `MiniOSSession.poweroff` (method) `mcp/minios_mcp.py:517` `def poweroff(self, timeout_ms)`
- `MiniOSSession.terminate` (method) `mcp/minios_mcp.py:537` `def terminate(self)`
- `MiniOSSession.close` (method) `mcp/minios_mcp.py:556` `def close(self)`
- `MiniOSSession.subprocess_launch` (method) `mcp/minios_mcp.py:560` `def subprocess_launch(cfg, slave_fd)`
- `MCPServer.__init__` (method) `mcp/minios_mcp.py:714` `def __init__(self, cfg)`
- `MCPServer.run` (method) `mcp/minios_mcp.py:718` `def run(self)`
- `MCPServer.main` (method) `mcp/minios_mcp.py:868` `def main()`

## mcp/mutate_mcp.sh
- `run_one` (function) `mcp/mutate_mcp.sh:115` -- Each mutant runs the suite in its own directory with its own pid file and addon state, so the runs are independent...


Next: [API_p8.md](API_p8.md)
