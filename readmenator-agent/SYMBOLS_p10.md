# Symbols (page 10 of 27)
Previous: [SYMBOLS_p9.md](SYMBOLS_p9.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `sb16_audio_device` | function | `kernel/syscalls.c:669` | `static device_t *sb16_audio_device(void)` |
| `sc_extra_name` | struct | `kernel/syscalls.c:3455` | `` |
| `sc_hex` | function | `kernel/syscalls.c:3557` | `static void sc_hex(unsigned long v)` |
| `sc_log` | struct | `kernel/syscalls.c:3534` | `` |
| `sc_record` | struct | `kernel/syscalls.c:3533` | `` |
| `sc_record` | function | `kernel/syscalls.c:3537` | `static void sc_record(long n, long a1, long a2, long a3, long ret)` |
| `sc_record_dump` | function | `kernel/syscalls.c:3567` | `void sc_record_dump(int pid)` |
| `select_timeout_ms` | function | `kernel/syscalls.c:2946` | `static int select_timeout_ms(const long *t, int pselect, long *out)` |
| `split` | function | `kernel/syscalls.c:2126` | `* hold a split (the mapping is restored untouched). */ static long sys_linux_munmap(long a1, long...` |
| `sys_linux_accept` | function | `kernel/syscalls.c:2717` | `static long sys_linux_accept(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_access` | function | `kernel/syscalls.c:2673` | `static long sys_linux_access(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_arch_prctl` | function | `kernel/syscalls.c:3194` | `static long sys_linux_arch_prctl(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_bind` | function | `kernel/syscalls.c:2706` | `static long sys_linux_bind(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_brk` | function | `kernel/syscalls.c:1932` | `static long sys_linux_brk(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_close` | function | `kernel/syscalls.c:1882` | `static long sys_linux_close(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_close_range` | function | `kernel/syscalls.c:1694` | `static long sys_linux_close_range(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_connect` | function | `kernel/syscalls.c:2700` | `static long sys_linux_connect(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_dup` | function | `kernel/syscalls.c:1833` | `static long sys_linux_dup(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_dup2` | function | `kernel/syscalls.c:1848` | `static long sys_linux_dup2(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_dup3` | function | `kernel/syscalls.c:1684` | `static long sys_linux_dup3(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_eventfd` | function | `kernel/syscalls.c:1731` | `static long sys_linux_eventfd(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_eventfd2` | function | `kernel/syscalls.c:1718` | `static long sys_linux_eventfd2(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fchmod` | function | `kernel/syscalls.c:3357` | `static long sys_linux_fchmod(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fdatasync` | function | `kernel/syscalls.c:3055` | `static long sys_linux_fdatasync(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_flock` | function | `kernel/syscalls.c:3041` | `static long sys_linux_flock(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fstat` | function | `kernel/syscalls.c:3146` | `static long sys_linux_fstat(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fsync` | function | `kernel/syscalls.c:3050` | `static long sys_linux_fsync(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_futex` | function | `kernel/syscalls.c:293` | `static long sys_linux_futex(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getcwd` | function | `kernel/syscalls.c:3060` | `static long sys_linux_getcwd(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getdents64` | function | `kernel/syscalls.c:976` | `static long sys_linux_getdents64(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getegid` | function | `kernel/syscalls.c:3248` | `static long sys_linux_getegid(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_geteuid` | function | `kernel/syscalls.c:3243` | `static long sys_linux_geteuid(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getgid` | function | `kernel/syscalls.c:3238` | `static long sys_linux_getgid(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getpeername` | function | `kernel/syscalls.c:2900` | `static long sys_linux_getpeername(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getsockname` | function | `kernel/syscalls.c:2894` | `static long sys_linux_getsockname(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getsockopt` | function | `kernel/syscalls.c:2887` | `static long sys_linux_getsockopt(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_gettimeofday` | function | `kernel/syscalls.c:3171` | `static long sys_linux_gettimeofday(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_listen` | function | `kernel/syscalls.c:2712` | `static long sys_linux_listen(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_lseek` | function | `kernel/syscalls.c:1905` | `static long sys_linux_lseek(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_madvise` | function | `kernel/syscalls.c:3255` | `static long sys_linux_madvise(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_mkdir` | function | `kernel/syscalls.c:3263` | `static long sys_linux_mkdir(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_mmap` | function | `kernel/syscalls.c:1997` | `static long sys_linux_mmap(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_mremap` | function | `kernel/syscalls.c:2327` | `static long sys_linux_mremap(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_nanosleep` | function | `kernel/syscalls.c:2848` | `static long sys_linux_nanosleep(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_open` | function | `kernel/syscalls.c:1457` | `static long sys_linux_open(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_pause` | function | `kernel/syscalls.c:2840` | `static long sys_linux_pause(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_pipe` | function | `kernel/syscalls.c:1606` | `static long sys_linux_pipe(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_pipe2` | function | `kernel/syscalls.c:1578` | `static long sys_linux_pipe2(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_poll` | function | `kernel/syscalls.c:2920` | `static long sys_linux_poll(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_prctl` | function | `kernel/syscalls.c:3123` | `static long sys_linux_prctl(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_prlimit64` | function | `kernel/syscalls.c:2768` | `static long sys_linux_prlimit64(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_pselect6` | function | `kernel/syscalls.c:3036` | `static long sys_linux_pselect6(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_read` | function | `kernel/syscalls.c:1271` | `static long sys_linux_read(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_readlink` | function | `kernel/syscalls.c:3117` | `static long sys_linux_readlink(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_recvfrom` | function | `kernel/syscalls.c:2728` | `static long sys_linux_recvfrom(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_rename` | function | `kernel/syscalls.c:3132` | `static long sys_linux_rename(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_rmdir` | function | `kernel/syscalls.c:3320` | `static long sys_linux_rmdir(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sched_getaffinity` | function | `kernel/syscalls.c:2801` | `static long sys_linux_sched_getaffinity(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_select` | function | `kernel/syscalls.c:3031` | `static long sys_linux_select(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sendmmsg` | function | `kernel/syscalls.c:2912` | `static long sys_linux_sendmmsg(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sendmsg` | function | `kernel/syscalls.c:2906` | `static long sys_linux_sendmsg(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sendto` | function | `kernel/syscalls.c:2723` | `static long sys_linux_sendto(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_setsockopt` | function | `kernel/syscalls.c:2880` | `static long sys_linux_setsockopt(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_shutdown` | function | `kernel/syscalls.c:2733` | `static long sys_linux_shutdown(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sigaction` | function | `kernel/syscalls.c:2593` | `static long sys_linux_sigaction(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_sigprocmask` | function | `kernel/syscalls.c:2598` | `static long sys_linux_sigprocmask(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_socket` | function | `kernel/syscalls.c:2695` | `static long sys_linux_socket(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_time` | function | `kernel/syscalls.c:284` | `static long sys_linux_time(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_umask` | function | `kernel/syscalls.c:3334` | `static long sys_linux_umask(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_uname` | function | `kernel/syscalls.c:3206` | `static long sys_linux_uname(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_unlink` | function | `kernel/syscalls.c:3089` | `static long sys_linux_unlink(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_write` | function | `kernel/syscalls.c:1351` | `static long sys_linux_write(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_writev` | function | `kernel/syscalls.c:1358` | `static long sys_linux_writev(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_clip_get` | function | `kernel/syscalls.c:770` | `static long sys_minios_clip_get(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_clip_set` | function | `kernel/syscalls.c:760` | `static long sys_minios_clip_set(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_dir_list` | function | `kernel/syscalls.c:1069` | `static long sys_minios_dir_list(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_dns` | function | `kernel/syscalls.c:266` | `static long sys_minios_dns(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_doom_frame` | function | `kernel/syscalls.c:409` | `static long sys_minios_doom_frame(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_fb_info` | function | `kernel/syscalls.c:442` | `static long sys_minios_fb_info(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_futex_wait` | function | `kernel/syscalls.c:799` | `static long sys_minios_futex_wait(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_futex_wake` | function | `kernel/syscalls.c:805` | `static long sys_minios_futex_wake(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_getc_raw` | function | `kernel/syscalls.c:863` | `static long sys_minios_getc_raw(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_gfx_title` | function | `kernel/syscalls.c:698` | `static long sys_minios_gfx_title(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_gfx_zoom` | function | `kernel/syscalls.c:420` | `static long sys_minios_gfx_zoom(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_kbd` | function | `kernel/syscalls.c:346` | `static long sys_minios_kbd(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_kbd_raw` | function | `kernel/syscalls.c:378` | `static long sys_minios_kbd_raw(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_lz4_compress` | function | `kernel/syscalls.c:605` | `static long sys_minios_lz4_compress(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_lz4_decompress` | function | `kernel/syscalls.c:618` | `static long sys_minios_lz4_decompress(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_mouse` | function | `kernel/syscalls.c:632` | `static long sys_minios_mouse(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_nk_frame` | function | `kernel/syscalls.c:656` | `static long sys_minios_nk_frame(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_palette` | function | `kernel/syscalls.c:366` | `static long sys_minios_palette(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcm2_close` | function | `kernel/syscalls.c:750` | `static long sys_minios_pcm2_close(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcm2_open` | function | `kernel/syscalls.c:737` | `static long sys_minios_pcm2_open(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcm2_write` | function | `kernel/syscalls.c:742` | `static long sys_minios_pcm2_write(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcspk_init` | function | `kernel/syscalls.c:391` | `static long sys_minios_pcspk_init(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcspk_tone` | function | `kernel/syscalls.c:395` | `static long sys_minios_pcspk_tone(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_pcspk_vol` | function | `kernel/syscalls.c:462` | `static long sys_minios_pcspk_vol(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_rlimit` | function | `kernel/syscalls.c:897` | `static long sys_minios_rlimit(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_rtc` | function | `kernel/syscalls.c:429` | `static long sys_minios_rtc(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_open` | function | `kernel/syscalls.c:675` | `static long sys_minios_sb16_open(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_pump` | function | `kernel/syscalls.c:712` | `static long sys_minios_sb16_pump(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_stream_close` | function | `kernel/syscalls.c:720` | `static long sys_minios_sb16_stream_close(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_stream_open` | function | `kernel/syscalls.c:716` | `static long sys_minios_sb16_stream_open(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_stream_submit` | function | `kernel/syscalls.c:724` | `static long sys_minios_sb16_stream_submit(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_stream_vol` | function | `kernel/syscalls.c:786` | `static long sys_minios_sb16_stream_vol(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_sb16_submit` | function | `kernel/syscalls.c:687` | `static long sys_minios_sb16_submit(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_spawn` | function | `kernel/syscalls.c:594` | `static long sys_minios_spawn(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_submit_batch` | function | `kernel/syscalls.c:874` | `static long sys_minios_submit_batch(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_time` | function | `kernel/syscalls.c:342` | `static long sys_minios_time(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_tls_retired` | function | `kernel/syscalls.c:271` | `static long sys_minios_tls_retired(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_vga_mode` | function | `kernel/syscalls.c:384` | `static long sys_minios_vga_mode(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `syscall_name` | function | `kernel/syscalls.c:3472` | `const char *syscall_name(long n)` |
| `syscall_trace_enabled` | function | `kernel/syscalls.c:1241` | `long syscall_trace_enabled(void)` |
| `syscall_trace_set` | function | `kernel/syscalls.c:1242` | `void syscall_trace_set(int on)` |
| `syscall_trace_shown` | function | `kernel/syscalls.c:1245` | `unsigned long syscall_trace_shown(void)` |
| `syscall_trace_verbose_enabled` | function | `kernel/syscalls.c:1243` | `long syscall_trace_verbose_enabled(void)` |
| `syscall_trace_verbose_set` | function | `kernel/syscalls.c:1244` | `void syscall_trace_verbose_set(int on)` |
| `trace_hint_print` | function | `kernel/syscalls.c:3513` | `static void trace_hint_print(long n, int kind, const char *path,                              lon...` |
| `trace_is_noisy` | function | `kernel/syscalls.c:3443` | `static int trace_is_noisy(long n)` |
| `unchanged` | function | `kernel/syscalls.c:1260` | `* unchanged (same code, same order of checks). Numbers >= 200 that * overlap real Linux ABIs stay in the switch as...` |
| `unlink_kpath` | function | `kernel/syscalls.c:3073` | `static long unlink_kpath(const char *path)` |
| `untouched` | function | `kernel/syscalls.c:139` | `* child untouched (caller refuses fail-closed). */ int kfd_view_copy(proc_t *child, proc_t *parent)` |
| `user_range_ok` | function | `kernel/syscalls.c:3624` | `int user_range_ok(unsigned long p, unsigned long len)` |
| `view` | function | `kernel/syscalls.c:503` | `* view (same as the `clear` builtin). Anything else is -EINVAL. Each  * out-word is range-checked...` |
| `vma_free_cover` | function | `kernel/syscalls.c:2281` | `static vma_node_t *vma_free_cover(unsigned long base, unsigned long len)` |
| `vma_live_first_overlap` | function | `kernel/syscalls.c:2095` | `static vma_node_t *vma_live_first_overlap(unsigned long base, unsigned long end)` |
| `vma_live_overlap` | function | `kernel/syscalls.c:2300` | `static int vma_live_overlap(unsigned long base, unsigned long len)` |
| `vma_live_remainder` | function | `kernel/syscalls.c:2112` | `static int vma_live_remainder(unsigned long base, unsigned long len,         int file, int ino, u...` |
| `wall_us_now` | function | `kernel/syscalls.c:256` | `unsigned long wall_us_now(void)` |
| `LINUX_ECHILD` | macro | `kernel/syscalls_proc.c:197` | `#define LINUX_ECHILD` |
| `LINUX_EINVAL` | macro | `kernel/syscalls_proc.c:198` | `#define LINUX_EINVAL` |
| `LINUX_ESRCH` | macro | `kernel/syscalls_proc.c:199` | `#define LINUX_ESRCH` |
| `LINUX_SIGKILL` | macro | `kernel/syscalls_proc.c:194` | `#define LINUX_SIGKILL` |
| `LINUX_STATUS_CODE` | macro | `kernel/syscalls_proc.c:196` | `#define LINUX_STATUS_CODE` |
| `LINUX_STATUS_SHIFT` | macro | `kernel/syscalls_proc.c:195` | `#define LINUX_STATUS_SHIFT` |
| `LINUX_WNOHANG` | macro | `kernel/syscalls_proc.c:193` | `#define LINUX_WNOHANG` |
| `groups` | function | `kernel/syscalls_proc.c:213` | `* groups (pid 0 and < -1) are not modelled and wait for any child. */ long sys_linux_wait4(long a...` |
| `kill` | function | `kernel/syscalls_proc.c:192` | `* historic kill (SIGKILL), -N is signal N (a seccomp kill is -SIGSYS). */ #define LINUX_WNOHANG  ...` |
| `sig` | function | `kernel/syscalls_proc.c:245` | `* the target as killed by sig (wait4 reports WTERMSIG);` |
| `state` | function | `kernel/syscalls_proc.c:5` | `* touches only scheduler state (current_pid, procs[], do_* / * seccomp_* / yield) plus the kernel-wide user_range_ok...` |
| `sys_linux_clone` | function | `kernel/syscalls_proc.c:83` | `long sys_linux_clone(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_execve` | function | `kernel/syscalls_proc.c:99` | `long sys_linux_execve(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_exit` | function | `kernel/syscalls_proc.c:184` | `long sys_linux_exit(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_fork` | function | `kernel/syscalls_proc.c:89` | `long sys_linux_fork(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_getpid` | function | `kernel/syscalls_proc.c:75` | `long sys_linux_getpid(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_gettid` | function | `kernel/syscalls_proc.c:259` | `long sys_linux_gettid(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_kill` | function | `kernel/syscalls_proc.c:248` | `long sys_linux_kill(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_vfork` | function | `kernel/syscalls_proc.c:94` | `long sys_linux_vfork(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_linux_yield` | function | `kernel/syscalls_proc.c:66` | `long sys_linux_yield(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_clone` | function | `kernel/syscalls_proc.c:18` | `long sys_minios_clone(long flags, long newsp, long a3, long a4, long a5, long a6)` |
| `sys_minios_nice` | function | `kernel/syscalls_proc.c:53` | `long sys_minios_nice(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_seccomp` | function | `kernel/syscalls_proc.c:37` | `long sys_minios_seccomp(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `sys_minios_thread_spawn` | function | `kernel/syscalls_proc.c:24` | `long sys_minios_thread_spawn(long a1, long a2, long a3, long a4, long a5, long a6)` |
| `tick_audio_count` | function | `kernel/tick.c:133` | `int tick_audio_count(void)` |
| `tick_desktop_count` | function | `kernel/tick.c:144` | `int tick_desktop_count(void)` |
| `tick_desktop_due` | function | `kernel/tick.c:160` | `int tick_desktop_due(unsigned long long ticks, unsigned interval)` |
| `tick_register_audio` | function | `kernel/tick.c:58` | `int tick_register_audio(tick_fn_t fn, void *ctx)` |
| `tick_register_desktop` | function | `kernel/tick.c:76` | `int tick_register_desktop(tick_fn_t fn, void *ctx)` |
| `tick_register_usb` | function | `kernel/tick.c:89` | `int tick_register_usb(tick_fn_t fn, void *ctx)` |
| `tick_reset` | function | `kernel/tick.c:34` | `void tick_reset(void)` |
| `tick_run_audio` | function | `kernel/tick.c:113` | `void tick_run_audio(void)` |
| `tick_run_desktop` | function | `kernel/tick.c:123` | `void tick_run_desktop(void)` |
| `tick_run_usb` | function | `kernel/tick.c:103` | `void tick_run_usb(void)` |
| `tick_slot_t` | struct | `kernel/tick.c:15` | `` |
| `ktime_init` | function | `kernel/time.c:19` | `static void ktime_init(void)` |
| `ktime_ms` | function | `kernel/time.c:33` | `unsigned long ktime_ms(void)` |
| `ktime_rdtsc` | function | `kernel/time.c:13` | `static unsigned long ktime_rdtsc(void)` |
| `ktime_us` | function | `kernel/time.c:41` | `unsigned long ktime_us(void)` |
| `CURSOR_TIP_X` | macro | `kernel/vga_cursor.c:28` | `#define CURSOR_TIP_X` |
| `CURSOR_TIP_Y` | macro | `kernel/vga_cursor.c:29` | `#define CURSOR_TIP_Y` |
| `cursor_draw` | function | `kernel/vga_cursor.c:68` | `static void cursor_draw(int mx, int my)` |
| `cursor_erase` | function | `kernel/vga_cursor.c:133` | `void cursor_erase(void)` |
| `cursor_has_set_neighbour` | function | `kernel/vga_cursor.c:57` | `static int cursor_has_set_neighbour(int i, int j)` |
| `cursor_invalidate` | function | `kernel/vga_cursor.c:141` | `void cursor_invalidate(void)` |
| `cursor_is_set` | function | `kernel/vga_cursor.c:50` | `static int cursor_is_set(int i, int j)` |
| `cursor_move` | function | `kernel/vga_cursor.c:116` | `void cursor_move(int mx, int my)` |
| `cursor_note_repaint` | function | `kernel/vga_cursor.c:147` | `void cursor_note_repaint(int x0, int y0, int w, int h)` |
| `cursor_over` | function | `kernel/vga_cursor.c:96` | `int cursor_over(int x0, int y0, int w, int h)` |
| `cursor_place` | function | `kernel/vga_cursor.c:106` | `void cursor_place(int mx, int my)` |
| `cursor_restore` | function | `kernel/vga_cursor.c:81` | `static void cursor_restore(int mx, int my)` |
| `cursor_save_bg` | function | `kernel/vga_cursor.c:40` | `static void cursor_save_bg(int mx, int my)` |
| `DOCK_GLOW_PAD` | macro | `kernel/vga_fb.c:2236` | `#define DOCK_GLOW_PAD` |
| `FBT` | macro | `kernel/vga_fb.c:151` | `#define FBT` |
| `FB_OFFSET` | macro | `kernel/vga_fb.c:1773` | `#define FB_OFFSET(x,y)` |
| `GFX_CURSOR_FOLLOW_TICKS` | macro | `kernel/vga_fb.c:631` | `#define GFX_CURSOR_FOLLOW_TICKS` |
| `GFX_CURSOR_IDLE_TICKS` | macro | `kernel/vga_fb.c:625` | `#define GFX_CURSOR_IDLE_TICKS` |
| `GFX_KEEP_BYTES` | macro | `kernel/vga_fb.c:599` | `#define GFX_KEEP_BYTES` |
| `GFX_PROG_LEN` | macro | `kernel/vga_fb.c:683` | `#define GFX_PROG_LEN` |
| `GFX_SRC_IDX` | macro | `kernel/vga_fb.c:597` | `#define GFX_SRC_IDX` |
| `GFX_SRC_RGB` | macro | `kernel/vga_fb.c:598` | `#define GFX_SRC_RGB` |
| `JELLY_BLOCK` | macro | `kernel/vga_fb.c:3550` | `#define JELLY_BLOCK` |
| `JELLY_ROW_MAX` | macro | `kernel/vga_fb.c:3552` | `#define JELLY_ROW_MAX` |
| `JELLY_SUBSTEPS` | macro | `kernel/vga_fb.c:3551` | `#define JELLY_SUBSTEPS` |
| `LG_LINE` | macro | `kernel/vga_fb.c:310` | `#define LG_LINE(a)` |
| `PROFILE_MARGIN` | macro | `kernel/vga_fb.c:2239` | `#define PROFILE_MARGIN` |
| `PROFILE_PAD` | macro | `kernel/vga_fb.c:2237` | `#define PROFILE_PAD` |
| `PROFILE_RING` | macro | `kernel/vga_fb.c:2238` | `#define PROFILE_RING` |
| `PROFILE_TEXT_COLS` | macro | `kernel/vga_fb.c:2240` | `#define PROFILE_TEXT_COLS` |
| `TB_GFX_TITLE_MAX` | macro | `kernel/vga_fb.c:3020` | `#define TB_GFX_TITLE_MAX` |
| `TEXT_BG_NONE` | macro | `kernel/vga_fb.c:2164` | `#define TEXT_BG_NONE` |
| `WIN_DEF_COLS` | macro | `kernel/vga_fb.c:1016` | `#define WIN_DEF_COLS` |
| `WIN_DEF_ROWS` | macro | `kernel/vga_fb.c:1017` | `#define WIN_DEF_ROWS` |
| `WIN_DEF_X` | macro | `kernel/vga_fb.c:1018` | `#define WIN_DEF_X` |
| `WIN_DEF_Y` | macro | `kernel/vga_fb.c:1019` | `#define WIN_DEF_Y` |
| `WM_ELINE_SZ` | macro | `kernel/vga_fb.c:1049` | `#define WM_ELINE_SZ` |
| `WM_MAX_TERMS` | macro | `kernel/vga_fb.c:1047` | `#define WM_MAX_TERMS` |
| `act_nrows` | function | `kernel/vga_fb.c:385` | `static int act_nrows(void)` |
| `alone` | function | `kernel/vga_fb.c:1485` | `* window alone (an unfocused graphics window minimizes to the taskbar,  * exactly like the hidden...` |
| `app` | function | `kernel/vga_fb.c:1276` | `* a gfx child spawned from another gfx app (file -> vedit) keeps the * terminal focused, so its keys and wheel keep...` |
| `buffer` | function | `kernel/vga_fb.c:3375` | `* owns the buffer (indices reset, render reads an empty ring). */ void term_clear(void)` |
| `chrome_color` | function | `kernel/vga_fb.c:2243` | `static unsigned long chrome_color(unsigned idx)` |
| `chrome_corner_origin` | function | `kernel/vga_fb.c:2322` | `static void chrome_corner_origin(const chrome_win_t *c, int k, int *ox, int *oy)` |
| `chrome_disc` | function | `kernel/vga_fb.c:2528` | `static void chrome_disc(int cx2, int cy2, int r2, unsigned long color, int alpha)` |
| `chrome_glass` | function | `kernel/vga_fb.c:2496` | `static void chrome_glass(int x, int y, int w, int h)` |
| `chrome_glow` | function | `kernel/vga_fb.c:2566` | `static void chrome_glow(int x, int y, int w, int h)` |
| `chrome_panel_coverage` | function | `kernel/vga_fb.c:2483` | `static int chrome_panel_coverage(int xx, int yy, int x, int y, int w, int h)` |
| `chrome_profile_card` | function | `kernel/vga_fb.c:2586` | `static void chrome_profile_card(void)` |
| `chrome_term_fill` | function | `kernel/vga_fb.c:2467` | `static int chrome_term_fill(void)` |
| `chrome_tint_capture` | function | `kernel/vga_fb.c:2421` | `static void chrome_tint_capture(int idx, int x, int y, int w, int h)` |
| `chrome_tint_live` | function | `kernel/vga_fb.c:2453` | `static const chrome_tint_t *chrome_tint_live(void)` |
| `chrome_tint_t` | struct | `kernel/vga_fb.c:434` | `` |
| `chrome_title_strip` | function | `kernel/vga_fb.c:2283` | `static int chrome_title_strip(int x, int y, int w, int focused)` |
| `chrome_traffic_lights` | function | `kernel/vga_fb.c:2550` | `static int chrome_traffic_lights(int bx, int by)` |
| `chrome_win_capture` | function | `kernel/vga_fb.c:2341` | `static void chrome_win_capture(int idx, int x, int y, int w, int h)` |
| `chrome_win_cut` | function | `kernel/vga_fb.c:2371` | `static void chrome_win_cut(const chrome_win_t *c, int k)` |
| `chrome_win_live` | function | `kernel/vga_fb.c:2392` | `static chrome_win_t *chrome_win_live(void)` |
| `chrome_win_rect` | function | `kernel/vga_fb.c:2310` | `static int chrome_win_rect(int id, int *x, int *y, int *w, int *h)` |
| `chrome_win_recut_bottom` | function | `kernel/vga_fb.c:2407` | `static void chrome_win_recut_bottom(int corner)` |
| `chrome_win_t` | struct | `kernel/vga_fb.c:2299` | `` |
| `chrome_wins_reset` | function | `kernel/vga_fb.c:2330` | `static void chrome_wins_reset(void)` |
| `ci_eq` | function | `kernel/vga_fb.c:722` | `static int ci_eq(const char *a, const char *b)` |
| `command` | function | `kernel/vga_fb.c:4962` | `* its launch command (config-driven, covers apps that never set a window * title);` |
| `compositions` | function | `kernel/vga_fb.c:139` | `* compositions (an ISR tick composing inside a syscall composition) draw * into the same shadow and leave the...` |
| `content` | function | `kernel/vga_fb.c:1350` | `* windows would share content (same prompt/output on both) and a park  * would alias src == dst. ...` |
| `coordinates` | function | `kernel/vga_fb.c:862` | `* windows keep the exact historical coordinates (including outside the * window);` |
| `desktop_shortcuts_draw` | function | `kernel/vga_fb.c:4887` | `void desktop_shortcuts_draw(void)` |
| `desktop_shortcuts_hit_test` | function | `kernel/vga_fb.c:4988` | `const char *desktop_shortcuts_hit_test(int mx, int my)` |
| `desktop_shortcuts_load` | function | `kernel/vga_fb.c:4648` | `void desktop_shortcuts_load(void)` |
| `directly` | function | `kernel/vga_fb.c:2704` | `* RGB sources pack directly (quantized to the wallpaper cube in 8-bit). */ static void gfx_scale_...` |
| `disp_clamp` | function | `kernel/vga_fb.c:396` | `static void disp_clamp(void)` |
| `dock_bounce_counts` | function | `kernel/vga_fb.c:4756` | `void dock_bounce_counts(unsigned long *kicks, unsigned long *paints)` |
| `dock_bounce_elapsed` | function | `kernel/vga_fb.c:4772` | `static unsigned long dock_bounce_elapsed(void)` |
| `dock_bounce_live` | function | `kernel/vga_fb.c:4780` | `static int dock_bounce_live(void)` |
| `dock_click_count` | function | `kernel/vga_fb.c:4766` | `void dock_click_count(unsigned long *edges)` |
| `dock_hover_index` | function | `kernel/vga_fb.c:4729` | `static int dock_hover_index(int mx, int my)` |
| `dock_label_px` | function | `kernel/vga_fb.c:4614` | `static int dock_label_px(const struct desktop_shortcut *sc)` |
| `dock_paint_backing` | function | `kernel/vga_fb.c:4880` | `static void dock_paint_backing(int x0, int y0, int dock_w, int dock_h, int with_shadow)` |
| `dock_paint_hover` | function | `kernel/vga_fb.c:4938` | `static void dock_paint_hover(int hover)` |
| `dock_paint_icons` | function | `kernel/vga_fb.c:4838` | `static void dock_paint_icons(int hover)` |
| `dock_pending_active` | function | `kernel/vga_fb.c:4830` | `int dock_pending_active(void)` |
| `draw_scrollbar` | function | `kernel/vga_fb.c:3278` | `static void draw_scrollbar(void)` |
| `draw_speaker_icon` | function | `kernel/vga_fb.c:3053` | `static void draw_speaker_icon(int x, int y, uint8_t color)` |
| `draw_title_win` | function | `kernel/vga_fb.c:2989` | `static void draw_title_win(int idx, int focused)` |
| `escapes` | function | `kernel/vga_fb.c:3444` | `* swallowing them here keeps the escapes (which the serial side needs)      * from printing as li...` |
| `fb_bytes_per_pixel` | function | `kernel/vga_fb.c:123` | `int fb_bytes_per_pixel(void)` |
| `fb_compose_begin` | function | `kernel/vga_fb.c:233` | `static int fb_compose_begin(void)` |
| `fb_compose_end` | function | `kernel/vga_fb.c:246` | `static void fb_compose_end(int owner)` |
| `fb_copy_bytes` | function | `kernel/vga_fb.c:157` | `static void fb_copy_bytes(volatile void *dst, const volatile void *src, unsigned long n)` |
| `fb_fill_run` | function | `kernel/vga_fb.c:1968` | `static void fb_fill_run(int x, int y, int n, unsigned long px)` |
| `fb_fill_u32` | function | `kernel/vga_fb.c:175` | `static void fb_fill_u32(volatile void *dst, unsigned int v, unsigned long n)` |
| `fb_frame_bytes` | function | `kernel/vga_fb.c:189` | `static unsigned long fb_frame_bytes(void)` |
| `fb_glyph` | function | `kernel/vga_fb.c:2056` | `static const uint8_t *fb_glyph(unsigned char c)` |
| `fb_pack_idx` | function | `kernel/vga_fb.c:1851` | `static unsigned long fb_pack_idx(unsigned idx)` |
| `fb_present_shadow` | function | `kernel/vga_fb.c:219` | `static void fb_present_shadow(void)` |
| `fb_read_packed` | function | `kernel/vga_fb.c:1887` | `unsigned long fb_read_packed(int x, int y)` |
| `fb_read_row_packed` | function | `kernel/vga_fb.c:1946` | `void fb_read_row_packed(int x, int y, unsigned int *dst, int n)` |
| `fb_shadow_ready` | function | `kernel/vga_fb.c:195` | `static int fb_shadow_ready(void)` |
| `fb_write_packed` | function | `kernel/vga_fb.c:1867` | `void fb_write_packed(int x, int y, unsigned long rgb)` |
| `fb_write_row_packed` | function | `kernel/vga_fb.c:1916` | `void fb_write_row_packed(int x, int y, const unsigned int *src, int n)` |
| `first` | function | `kernel/vga_fb.c:512` | `* screen ever showing it whole first (the old flash-then-melt). */ static unsigned int *fx_start_...` |
| `flag` | function | `kernel/vga_fb.c:606` | `* is the minimized flag (the program keeps running, nothing composites);` |
| `from` | function | `kernel/vga_fb.c:4020` | `* leaving returns to the view it came from (floating or tiled). Returns  * 0 on success, -1 witho...` |
| `fx_plan_burn` | function | `kernel/vga_fb.c:494` | `static void fx_plan_burn(int x, int y, int w, int h)` |
| `fx_plan_genie` | function | `kernel/vga_fb.c:500` | `static void fx_plan_genie(int x, int y, int w, int h, int tx, int ty, int reverse)` |
| `gfx_animate` | function | `kernel/vga_fb.c:3922` | `static void gfx_animate(const wm_gfxview_rect_t *from, const wm_gfxview_rect_t *to,              ...` |
| `gfx_compose` | function | `kernel/vga_fb.c:2842` | `static void gfx_compose(const volatile uint8_t *src, int kind, int sw, int sh,                   ...` |
| `gfx_covers_screen` | function | `kernel/vga_fb.c:654` | `static int gfx_covers_screen(void)` |
| `gfx_cursor_follow_idle` | function | `kernel/vga_fb.c:2926` | `static void gfx_cursor_follow_idle(void)` |
| `gfx_drop_focus` | function | `kernel/vga_fb.c:4009` | `static void gfx_drop_focus(int source)` |
| `gfx_float_frame` | function | `kernel/vga_fb.c:832` | `static int gfx_float_frame(wm_gfxview_rect_t *out)` |
| `gfx_keep_save` | function | `kernel/vga_fb.c:660` | `static void gfx_keep_save(const volatile uint8_t *src, int kind, int sw, int sh)` |
| `gfx_letterbox` | function | `kernel/vga_fb.c:2809` | `static void gfx_letterbox(const wm_gfxview_t *v)` |
| `gfx_present` | function | `kernel/vga_fb.c:2910` | `static void gfx_present(const volatile uint8_t *bb, int kind, int sw, int sh)` |
| `gfx_prog_icon` | function | `kernel/vga_fb.c:735` | `static const uint8_t *gfx_prog_icon(void)` |
| `gfx_snap` | function | `kernel/vga_fb.c:4175` | `static void gfx_snap(int zone)` |
| `gfx_task_icon` | function | `kernel/vga_fb.c:4967` | `static const uint8_t *gfx_task_icon(void)` |
| `gfx_taskbar_rect` | function | `kernel/vga_fb.c:3972` | `static void gfx_taskbar_rect(wm_gfxview_rect_t *r)` |
| `gfx_title` | function | `kernel/vga_fb.c:2828` | `static void gfx_title(const wm_gfxview_t *v)` |
| `gfx_transition` | function | `kernel/vga_fb.c:1057` | `static void gfx_transition(const wm_gfxview_rect_t *from, int from_titled);` |
| `gfx_view_cfg` | function | `kernel/vga_fb.c:645` | `static wm_gfxview_config_t gfx_view_cfg(void)` |
| `gfx_view_for` | function | `kernel/vga_fb.c:806` | `static int gfx_view_for(int sw, int sh, wm_gfxview_t *v)` |
| `gfx_view_in_rect` | function | `kernel/vga_fb.c:3903` | `static void gfx_view_in_rect(const wm_gfxview_rect_t *r, int titled, wm_gfxview_t *v)` |
| `gfx_view_publish` | function | `kernel/vga_fb.c:818` | `static void gfx_view_publish(const wm_gfxview_t *v)` |
| `icon_decode` | function | `kernel/vga_fb.c:4552` | `static const uint8_t *icon_decode(const char *path)` |
| `icon_embedded` | function | `kernel/vga_fb.c:4532` | `static const uint8_t *icon_embedded(const char *name)` |
| `icon_embedded_rgba` | function | `kernel/vga_fb.c:4586` | `static const uint8_t *icon_embedded_rgba(const uint8_t *idx)` |
| `icon_nearest` | function | `kernel/vga_fb.c:4516` | `static int icon_nearest(int r, int g, int b)` |
| `jelly_advance` | function | `kernel/vga_fb.c:3755` | `static void jelly_advance(void)` |
| `jelly_arm` | function | `kernel/vga_fb.c:3629` | `static void jelly_arm(void)` |
| `jelly_begin` | function | `kernel/vga_fb.c:3577` | `static void jelly_begin(int kind, int gx, int gy)` |
| `jelly_cancel` | function | `kernel/vga_fb.c:3568` | `static void jelly_cancel(void)` |
| `jelly_kick` | function | `kernel/vga_fb.c:3612` | `static void jelly_kick(int mx, int my)` |
| `jelly_live` | function | `kernel/vga_fb.c:3621` | `static int jelly_live(void)` |
| `jelly_present` | function | `kernel/vga_fb.c:3720` | `static void jelly_present(void)` |
| `jelly_put_row` | function | `kernel/vga_fb.c:3665` | `static void jelly_put_row(int x, int y, const unsigned int *src, int n)` |
| `jelly_rect` | function | `kernel/vga_fb.c:3589` | `static int jelly_rect(int *x, int *y, int *w, int *h)` |
| `jelly_shadow_px` | function | `kernel/vga_fb.c:3655` | `static unsigned int jelly_shadow_px(int x, int y)` |
| `jelly_tick` | function | `kernel/vga_fb.c:3768` | `static void jelly_tick(int held)` |
| `jelly_try_present` | function | `kernel/vga_fb.c:3744` | `static int jelly_try_present(void)` |
| `jelly_warp_band` | function | `kernel/vga_fb.c:3687` | `static void jelly_warp_band(void)` |
| `letterbox` | function | `kernel/vga_fb.c:610` | `* present to repaint chrome plus letterbox (after a desktop redraw or a * view change);` |
| `lg_alloc` | function | `kernel/vga_fb.c:347` | `static void lg_alloc(void)` |
| `lg_get` | function | `kernel/vga_fb.c:319` | `static const char *lg_get(int i)` |
| `lg_push` | function | `kernel/vga_fb.c:326` | `static void lg_push(const char *line, int len)` |
| `line` | function | `kernel/vga_fb.c:3435` | `* display stale bytes left over from a longer previous line (e.g. the prompt  * would show the ta...` |
| `line_at` | function | `kernel/vga_fb.c:414` | `static const char *line_at(int abs, int *off)` |
| `line_nrows` | function | `kernel/vga_fb.c:378` | `static int line_nrows(int len)` |
| `mouse_apply_wheel` | function | `kernel/vga_fb.c:5028` | `static void mouse_apply_wheel(int wheel, int step)` |
| `mouse_drag_gfx` | function | `kernel/vga_fb.c:5052` | `static void mouse_drag_gfx(const wm_geom_config_t *gcfg, int mx, int my)` |
| `mouse_drag_term` | function | `kernel/vga_fb.c:5109` | `static void mouse_drag_term(const wm_geom_config_t *gcfg, int win_w, int mx, int my, int gfx_cursor)` |
| `mouse_focus_topmost` | function | `kernel/vga_fb.c:5002` | `static int mouse_focus_topmost(int mx, int my)` |
| `mouse_scrollbar` | function | `kernel/vga_fb.c:5132` | `static void mouse_scrollbar(const wm_geom_config_t *gcfg, int mx, int my)` |
| `path` | function | `kernel/vga_fb.c:5181` | `* present path (blit_gfx_buf) is the sole cursor painter. The tick * used to share the sprite state with it and...` |
| `pipe_field` | function | `kernel/vga_fb.c:4498` | `static const char *pipe_field(const char *line, int idx, char *buf, int buflen)` |
| `pointer` | function | `kernel/vga_fb.c:5049` | `* tiled window floats it at native size under the pointer (the grab point * keeps its relative position along the...` |
| `render_blank_row` | function | `kernel/vga_fb.c:3314` | `static void render_blank_row(int vrow)` |
| `render_row` | function | `kernel/vga_fb.c:3324` | `static void render_row(int vrow, int abs)` |
| `shcmd_base` | function | `kernel/vga_fb.c:705` | `static void shcmd_base(const char *cmd, char *out, unsigned long cap)` |
| `shortcut_cell_left` | function | `kernel/vga_fb.c:4641` | `static int shortcut_cell_left(int i)` |
| `shortcut_draw_scaled` | function | `kernel/vga_fb.c:4704` | `static void shortcut_draw_scaled(const struct desktop_shortcut *sc,                              ...` |
| `shortcuts_layout` | function | `kernel/vga_fb.c:4623` | `static void shortcuts_layout(void)` |
| `state` | function | `kernel/vga_fb.c:5295` | `* ignores the button state (the arming press is consumed) and settles      * once on expiry, so t...` |
| `taskbar` | function | `kernel/vga_fb.c:2656` | `* minimize hides the app to the taskbar (it never closes it), maximize  * toggles true fullscreen...` |
| `taskbar_handle_click` | function | `kernel/vga_fb.c:3218` | `static void taskbar_handle_click(int mx, int my)` |
| `taskbar_layout` | function | `kernel/vga_fb.c:3022` | `static void taskbar_layout(void)` |
| `taskbar_render` | function | `kernel/vga_fb.c:3062` | `static void taskbar_render(void)` |
| `taskbar_theme_cycle` | function | `kernel/vga_fb.c:3178` | `static void taskbar_theme_cycle(void)` |
| `taskbar_tick` | function | `kernel/vga_fb.c:3141` | `static void taskbar_tick(void)` |
| `term_close_default` | function | `kernel/vga_fb.c:4208` | `static void term_close_default(void)` |
| `term_finish_layout` | function | `kernel/vga_fb.c:4292` | `static void term_finish_layout(void)` |
| `term_max_cols` | function | `kernel/vga_fb.c:4283` | `static int term_max_cols(void)` |
| `term_max_rows` | function | `kernel/vga_fb.c:4287` | `static int term_max_rows(void)` |
| `term_recalc` | function | `kernel/vga_fb.c:2963` | `static void term_recalc(void)` |
| `term_render` | function | `kernel/vga_fb.c:3359` | `static void term_render(void)` |
| `term_render_active` | function | `kernel/vga_fb.c:3392` | `static void term_render_active(void)` |
| `term_toggle_fullscreen` | function | `kernel/vga_fb.c:4116` | `static void term_toggle_fullscreen(void)` |
| `term_toggle_minimize` | function | `kernel/vga_fb.c:4139` | `static void term_toggle_minimize(void)` |
| `termwin_t` | struct | `kernel/vga_fb.c:1059` | `` |
| `text_px` | function | `kernel/vga_fb.c:2169` | `static void text_px(int px, int py, const char *s, uint8_t fg, uint8_t bg)` |
| `title` | function | `kernel/vga_fb.c:3072` | `* 8px row plus its title (bright when focused). The hint line * starts after it instead of underneath. */ const...` |
| `total_rows` | function | `kernel/vga_fb.c:388` | `static int total_rows(void)` |
| `tw_hit` | function | `kernel/vga_fb.c:1730` | `static int tw_hit(int i, int mx, int my)` |
| `tw_park` | function | `kernel/vga_fb.c:1116` | `static void tw_park(int i)` |
| `tw_select` | function | `kernel/vga_fb.c:1206` | `static void tw_select(int i)` |
| `tw_unpark` | function | `kernel/vga_fb.c:1146` | `static void tw_unpark(int i)` |
| `vga_fb_act_empty` | function | `kernel/vga_fb.c:1670` | `int vga_fb_act_empty(void)` |
| `vga_fb_blit_gfx_window` | function | `kernel/vga_fb.c:2939` | `void vga_fb_blit_gfx_window(void)` |
| `vga_fb_blit_nk_rgb_window` | function | `kernel/vga_fb.c:2954` | `void vga_fb_blit_nk_rgb_window(void)` |
| `vga_fb_blit_nk_window` | function | `kernel/vga_fb.c:2948` | `void vga_fb_blit_nk_window(void)` |
| `vga_fb_boot_config` | function | `kernel/vga_fb.c:96` | `void vga_fb_boot_config(void)` |
| `vga_fb_boot_history_to_active` | function | `kernel/vga_fb.c:1335` | `static void vga_fb_boot_history_to_active(void)` |
| `vga_fb_char` | function | `kernel/vga_fb.c:2128` | `void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg)` |
| `vga_fb_clear` | function | `kernel/vga_fb.c:2087` | `void vga_fb_clear(void)` |
| `vga_fb_clear_prompt` | function | `kernel/vga_fb.c:1679` | `void vga_fb_clear_prompt(void)` |
| `vga_fb_close_active` | function | `kernel/vga_fb.c:4224` | `int vga_fb_close_active(void)` |
| `vga_fb_draw_desktop` | function | `kernel/vga_fb.c:3791` | `void vga_fb_draw_desktop(void)` |
| `vga_fb_focus_event` | function | `kernel/vga_fb.c:1101` | `const wm_notify_event_t *vga_fb_focus_event(void)` |
| `vga_fb_focus_get` | function | `kernel/vga_fb.c:1218` | `int vga_fb_focus_get(void)` |
| `vga_fb_focus_id` | function | `kernel/vga_fb.c:1300` | `int vga_fb_focus_id(int id)` |
| `vga_fb_focus_next` | function | `kernel/vga_fb.c:1235` | `void vga_fb_focus_next(void)` |
| `vga_fb_focus_report` | function | `kernel/vga_fb.c:1107` | `void vga_fb_focus_report(int before, int source)` |
| `vga_fb_gfx_cursor_draw` | function | `kernel/vga_fb.c:890` | `static void vga_fb_gfx_cursor_draw(void)` |
| `vga_fb_gfx_cursor_erase` | function | `kernel/vga_fb.c:880` | `static void vga_fb_gfx_cursor_erase(void)` |
| `vga_fb_gfx_map_mouse` | function | `kernel/vga_fb.c:865` | `void vga_fb_gfx_map_mouse(int *x, int *y)` |
| `vga_fb_gfx_origin` | function | `kernel/vga_fb.c:848` | `void vga_fb_gfx_origin(int *x, int *y)` |
| `vga_fb_gfx_set_hidden` | function | `kernel/vga_fb.c:4054` | `int vga_fb_gfx_set_hidden(int hide)` |
| `vga_fb_gfx_view_name` | function | `kernel/vga_fb.c:4104` | `const char *vga_fb_gfx_view_name(void)` |
| `vga_fb_hide_text_cursor` | function | `kernel/vga_fb.c:3515` | `void vga_fb_hide_text_cursor(void)` |
| `vga_fb_history_page` | function | `kernel/vga_fb.c:5427` | `void vga_fb_history_page(int dir)` |
| `vga_fb_init` | function | `kernel/vga_fb.c:5439` | `void vga_fb_init(void)` |
| `vga_fb_is_fullscreen` | function | `kernel/vga_fb.c:4170` | `int vga_fb_is_fullscreen(void)` |
| `vga_fb_is_minimized` | function | `kernel/vga_fb.c:4169` | `int vga_fb_is_minimized(void)` |
| `vga_fb_layout_cycle` | function | `kernel/vga_fb.c:1451` | `void vga_fb_layout_cycle(void)` |
| `vga_fb_layout_get` | function | `kernel/vga_fb.c:1467` | `int vga_fb_layout_get(void)` |
| `vga_fb_layout_name` | function | `kernel/vga_fb.c:1473` | `const char *vga_fb_layout_name(void)` |
| `vga_fb_layout_set` | function | `kernel/vga_fb.c:1440` | `int vga_fb_layout_set(int mode)` |
| `vga_fb_list_windows` | function | `kernel/vga_fb.c:1612` | `void vga_fb_list_windows(void)` |
| `vga_fb_mouse_init` | function | `kernel/vga_fb.c:5373` | `void vga_fb_mouse_init(void)` |
| `vga_fb_mouse_tick` | function | `kernel/vga_fb.c:5170` | `void vga_fb_mouse_tick(void)` |
| `vga_fb_move_terminal` | function | `kernel/vga_fb.c:4238` | `void vga_fb_move_terminal(int dx, int dy)` |
| `vga_fb_note_prompt` | function | `kernel/vga_fb.c:1674` | `void vga_fb_note_prompt(void)` |
| `vga_fb_nterms_get` | function | `kernel/vga_fb.c:1219` | `int vga_fb_nterms_get(void)` |
| `vga_fb_park_line` | function | `kernel/vga_fb.c:1700` | `void vga_fb_park_line(const char *b, int p)` |
| `vga_fb_pixel` | function | `kernel/vga_fb.c:2077` | `void vga_fb_pixel(int x, int y, uint8_t color)` |
| `vga_fb_pixel_rgb` | function | `kernel/vga_fb.c:2112` | `void vga_fb_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b)` |
| `vga_fb_prompt_live` | function | `kernel/vga_fb.c:1693` | `int vga_fb_prompt_live(void)` |
| `vga_fb_prompted` | function | `kernel/vga_fb.c:1684` | `int vga_fb_prompted(void)` |
| `vga_fb_ps2_owner` | function | `kernel/vga_fb.c:2636` | `int vga_fb_ps2_owner(int pid)` |
| `vga_fb_puts_term` | function | `kernel/vga_fb.c:3501` | `void vga_fb_puts_term(const char *s)` |
| `vga_fb_read_rgb` | function | `kernel/vga_fb.c:1911` | `unsigned long vga_fb_read_rgb(int x, int y)` |
| `vga_fb_rect` | function | `kernel/vga_fb.c:2097` | `void vga_fb_rect(int x, int y, int w, int h, uint8_t color)` |
| `vga_fb_rect_rgb` | function | `kernel/vga_fb.c:2121` | `void vga_fb_rect_rgb(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b)` |
| `vga_fb_reset_default` | function | `kernel/vga_fb.c:4346` | `void vga_fb_reset_default(void)` |
| `vga_fb_resize` | function | `kernel/vga_fb.c:4326` | `void vga_fb_resize(int dcols, int drows)` |
| `vga_fb_set_gfx_mode` | function | `kernel/vga_fb.c:748` | `void vga_fb_set_gfx_mode(int on)` |
| `vga_fb_set_gfx_palette` | function | `kernel/vga_fb.c:1836` | `void vga_fb_set_gfx_palette(const unsigned char *pal)` |
| `vga_fb_set_gfx_program` | function | `kernel/vga_fb.c:686` | `void vga_fb_set_gfx_program(const char *name)` |
| `vga_fb_set_palette` | function | `kernel/vga_fb.c:2003` | `static void vga_fb_set_palette(void)` |
| `vga_fb_snap_window` | function | `kernel/vga_fb.c:4298` | `void vga_fb_snap_window(int zone)` |
| `vga_fb_str` | function | `kernel/vga_fb.c:2154` | `void vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg)` |
| `vga_fb_term_feed` | function | `kernel/vga_fb.c:371` | `void vga_fb_term_feed(const char *line, int len)` |
| `vga_fb_term_ring_init` | function | `kernel/vga_fb.c:363` | `void vga_fb_term_ring_init(void)` |
| `vga_fb_text_cursor` | function | `kernel/vga_fb.c:3507` | `void vga_fb_text_cursor(int col)` |
| `vga_fb_theme_name` | function | `kernel/vga_fb.c:3157` | `int vga_fb_theme_name(char *dst, int cap)` |
| `vga_fb_toggle_fullscreen` | function | `kernel/vga_fb.c:4128` | `void vga_fb_toggle_fullscreen(void)` |
| `vga_fb_toggle_minimize` | function | `kernel/vga_fb.c:4161` | `void vga_fb_toggle_minimize(void)` |
| `vga_fb_unpark_line` | function | `kernel/vga_fb.c:1715` | `int vga_fb_unpark_line(char *b, int *p)` |
| `vga_fb_wait_tick` | function | `kernel/vga_fb.c:5161` | `void vga_fb_wait_tick(void)` |
| `wall_level` | function | `kernel/vga_fb.c:1994` | `static int wall_level(int v)` |
| `wallpaper_draw` | function | `kernel/vga_fb.c:4460` | `static void wallpaper_draw(void)` |
| `wallpaper_ensure` | function | `kernel/vga_fb.c:4403` | `static void wallpaper_ensure(void)` |
| `wallpaper_packed` | function | `kernel/vga_fb.c:4476` | `static int wallpaper_packed(int x, int y, unsigned int *out)` |
| `wallpaper_rect` | function | `kernel/vga_fb.c:4907` | `static void wallpaper_rect(int x0, int y0, int w, int h)` |
| `wallpaper_usable` | function | `kernel/vga_fb.c:4455` | `static int wallpaper_usable(void)` |
| `wm_buttons_hit` | function | `kernel/vga_fb.c:2616` | `static int wm_buttons_hit(int mx, int my, int win_x, int win_y, int win_w)` |
| `wm_clear_close` | function | `kernel/vga_fb.c:2632` | `void wm_clear_close(void)` |
| `wm_close_pending` | function | `kernel/vga_fb.c:2631` | `int wm_close_pending(void)` |
| `wm_drag_reset` | function | `kernel/vga_fb.c:74` | `static void wm_drag_reset(void)` |
| `wm_draw_buttons` | function | `kernel/vga_fb.c:2198` | `static void wm_draw_buttons(int px, int py, int win_w, uint8_t fg, uint8_t bg)` |
| `wm_emit_focus_moved` | function | `kernel/vga_fb.c:1089` | `static void wm_emit_focus_moved(int before, int source)` |
| `wm_event_cfg` | function | `kernel/vga_fb.c:65` | `static wm_event_config_t wm_event_cfg(void)` |
| `wm_focus_cursor_sync` | function | `kernel/vga_fb.c:1082` | `static void wm_focus_cursor_sync(const wm_notify_event_t *e)` |
| `wm_geom_cfg` | function | `kernel/vga_fb.c:54` | `static wm_geom_config_t wm_geom_cfg(void)` |
| `wm_gfx_focus_sync` | function | `kernel/vga_fb.c:1281` | `static void wm_gfx_focus_sync(int on)` |
| `wm_gfx_mode_active` | function | `kernel/vga_fb.c:2633` | `int wm_gfx_mode_active(void)` |
| `wm_init_once` | function | `kernel/vga_fb.c:1181` | `static void wm_init_once(void)` |
| `wm_snapshot_state` | function | `kernel/vga_fb.c:1222` | `static void wm_snapshot_state(wm_focus_state_t *st)` |
| `fx_wait_until` | function | `kernel/vga_fx.c:40` | `static void fx_wait_until(unsigned long deadline)` |
| `once` | function | `kernel/vga_fx.c:95` | `* once (prev[] tracks the revealed frontier per column), then the final  * restore guarantees the...` |
| `vga_fx_enabled` | function | `kernel/vga_fx.c:32` | `int vga_fx_enabled(void)` |
| `vga_fx_free` | function | `kernel/vga_fx.c:82` | `void vga_fx_free(unsigned int *buf)` |
| `vga_fx_melt_from_black` | function | `kernel/vga_fx.c:164` | `void vga_fx_melt_from_black(int x, int y, int w, int h, const unsigned int *newb)` |
| `vga_fx_melt_rect` | function | `kernel/vga_fx.c:155` | `void vga_fx_melt_rect(int x, int y, int w, int h,     const unsigned int *oldb, const unsigned in...` |
| `vga_fx_restore_rect` | function | `kernel/vga_fx.c:68` | `void vga_fx_restore_rect(int x, int y, int w, int h, const unsigned int *buf)` |
| `vga_fx_set_enabled` | function | `kernel/vga_fx.c:27` | `void vga_fx_set_enabled(int on)` |
| `vga_fx_snap_rect` | function | `kernel/vga_fx.c:46` | `unsigned int *vga_fx_snap_rect(int x, int y, int w, int h)` |
| `Client` | class | `mcp/mcp_dbg_driver.py:15` | `class Client` |
| `__init__` | method | `mcp/mcp_dbg_driver.py:16` | `def __init__(self)` |
| `close` | method | `mcp/mcp_dbg_driver.py:54` | `def close(self)` |
| `main` | function | `mcp/mcp_dbg_driver.py:64` | `def main()` |
| `request` | method | `mcp/mcp_dbg_driver.py:28` | `def request(self, method, params)` |
| `tool` | method | `mcp/mcp_dbg_driver.py:46` | `def tool(self, name, params)` |
| `Client` | class | `mcp/mcp_dogfood.py:19` | `class Client` |
| `__init__` | method | `mcp/mcp_dogfood.py:20` | `def __init__(self, addons_dir)` |
| `close` | method | `mcp/mcp_dogfood.py:68` | `def close(self)` |
| `main` | function | `mcp/mcp_dogfood.py:78` | `def main()` |
| `request` | method | `mcp/mcp_dogfood.py:40` | `def request(self, method, params)` |
| `tool` | method | `mcp/mcp_dogfood.py:58` | `def tool(self, name, params)` |
| `AddonError` | class | `mcp/minios_addons.py:56` | `class AddonError(Exception)` |
| `AddonState` | class | `mcp/minios_addons.py:377` | `class AddonState` |
| `__init__` | method | `mcp/minios_addons.py:380` | `def __init__(self, path)` |
| `_clean` | function | `mcp/minios_addons.py:62` | `def _clean(s)` |
| `_unquote` | function | `mcp/minios_addons.py:66` | `def _unquote(v)` |
| `exit_code_of` | function | `mcp/minios_addons.py:372` | `def exit_code_of(text)` |
| `fail` | function | `mcp/minios_addons.py:85` | `def fail(lineno, why)` |
| `install_addon` | function | `mcp/minios_addons.py:401` | `def install_addon(session, addon, cfg)` |
| `load` | method | `mcp/minios_addons.py:383` | `def load(self)` |
| `load_addons_dir` | function | `mcp/minios_addons.py:323` | `def load_addons_dir(addons_dir)` |
| `parse_addon_yaml` | function | `mcp/minios_addons.py:73` | `def parse_addon_yaml(text)` |
| `save` | method | `mcp/minios_addons.py:393` | `def save(self, addons)` |
| `split_for_editor` | function | `mcp/minios_addons.py:347` | `def split_for_editor(text)` |
| `validate_addon` | function | `mcp/minios_addons.py:205` | `def validate_addon(addon, source)` |
| `validate_addon_path` | function | `mcp/minios_addons.py:295` | `def validate_addon_path(path)` |
| `validate_shell_line` | function | `mcp/minios_addons.py:309` | `def validate_shell_line(line)` |
| `LogBuffer` | class | `mcp/minios_mcp.py:146` | `class LogBuffer` |
| `MCPServer` | class | `mcp/minios_mcp.py:731` | `class MCPServer` |
| `MiniOSSession` | class | `mcp/minios_mcp.py:216` | `class MiniOSSession` |
| `RPCError` | class | `mcp/minios_mcp.py:137` | `class RPCError(Exception)` |
| `ToolError` | class | `mcp/minios_mcp.py:131` | `class ToolError(Exception)` |
| `__init__` | method | `mcp/minios_mcp.py:140` | `def __init__(self, code, message)` |
| `__init__` | method | `mcp/minios_mcp.py:149` | `def __init__(self, cap)` |
| `__init__` | method | `mcp/minios_mcp.py:219` | `def __init__(self, cfg)` |
| `__init__` | method | `mcp/minios_mcp.py:734` | `def __init__(self, cfg)` |
| `_addon_install` | method | `mcp/minios_mcp.py:863` | `def _addon_install(self, args)` |
| `_addons_list` | method | `mcp/minios_mcp.py:842` | `def _addons_list(self)` |
| `_call` | method | `mcp/minios_mcp.py:779` | `def _call(self, params)` |
| `_cleanup_parts` | method | `mcp/minios_mcp.py:493` | `def _cleanup_parts(self, parts)` |
| `_close_pty` | method | `mcp/minios_mcp.py:329` | `def _close_pty(self)` |
| `_dispatch` | method | `mcp/minios_mcp.py:796` | `def _dispatch(self, name, args)` |
| `_drop_pidfile` | method | `mcp/minios_mcp.py:278` | `def _drop_pidfile(self)` |
| `_find_locked` | method | `mcp/minios_mcp.py:206` | `def _find_locked(self, marker, start)` |
| `_handle` | method | `mcp/minios_mcp.py:746` | `def _handle(self, line)` |
| `_initialize` | method | `mcp/minios_mcp.py:772` | `def _initialize(self, params)` |

Next: [SYMBOLS_p11.md](SYMBOLS_p11.md)
