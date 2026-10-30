# API (page 8 of 21)
Previous: [API_p7.md](API_p7.md)

## kernel/syscalls.c
Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/arch/x86/hal_io.h`, `headers/arch/x86/msr.h`, `headers/batch.h`, `headers/block.h`, `headers/driver.h`, `headers/drivers/kbd.h`, `headers/futex.h`, `headers/ide.h`, `headers/ktime.h`, `headers/lz4_kernel.h`, `headers/minifs.h`, `headers/net.h`, `headers/pcache.h`, `headers/pcm2.h`, `headers/pcspk.h`, `headers/percpu_rq.h`, `headers/proc_sec.h`, `headers/randmix.h`, `headers/rcu.h`, `headers/rtc.h`, `headers/sanitize.h`, `headers/sb16.h`, `headers/sched.h`, `headers/select_map.h`, `headers/shell.h`, `headers/spawn.h`, `headers/sync.h`, `headers/syscalls_proc.h`, `headers/tlb.h`, `headers/vga_fb.h`, `headers/zip.h`
- `kfd_view_current` (function) `kernel/syscalls.c:61` `static kfd_view_t *kfd_view_current(void)` -- Docstring: View owning the caller's fds: its own on isolated procs * and threads, the root on pid 0 and any pid...
- `kfd_view_root` (function) `kernel/syscalls.c:71` `kfd_view_t *kfd_view_root(void)` -- Docstring: Static root view (shell pid 0, pids without their own): * entries are the historical shared table, never...
- `kfd_get` (function) `kernel/syscalls.c:90` `KFILE *kfd_get(int fd)`
- `kfd_put` (function) `kernel/syscalls.c:103` `void kfd_put(KFILE *f)`
- `kfd_view_count` (function) `kernel/syscalls.c:115` `static int kfd_view_count(kfd_view_t *v)` -- } void kfd_put(KFILE *f) { irqflags_t flags; int drop = 0; if (!f) return; spin_lock_irqsave(&fd_lock, &flags)...
- `untouched` (function) `kernel/syscalls.c:139` `* child untouched (caller refuses fail-closed). */
int kfd_view_copy(proc_t *child, proc_t *parent)`
- `NULL` (function) `kernel/syscalls.c:166` `* on NULL (already released or never owned). */
void kfd_view_release(proc_t *p)`
- `kfd_view_cloexec` (function) `kernel/syscalls.c:197` `void kfd_view_cloexec(void)` -- Docstring: Close every CLOEXEC fd in the caller's own view (execve: the image is replaced, marked descriptors must...
- `by` (function) `kernel/syscalls.c:225` `* is indexed by (syscall_number - 200). New syscalls are added by: * 1. Adding a MINIOS_SYS_* constant to...`
- `wall_us_now` (function) `kernel/syscalls.c:256` `unsigned long wall_us_now(void)` -- wall_us_now: RTC-anchored wall clock in microseconds (Phase 0.2/0.3).
- `sys_minios_dns` (function) `kernel/syscalls.c:266` `static long sys_minios_dns(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_tls_retired` (function) `kernel/syscalls.c:271` `static long sys_minios_tls_retired(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_time` (function) `kernel/syscalls.c:284` `static long sys_linux_time(long a1, long a2, long a3, long a4, long a5, long a6)` -- time (201): the retired kernel-TLS handshake number now serves Linux time(2), exactly as 202 serves futex (ADR-0014...
- `sys_linux_futex` (function) `kernel/syscalls.c:293` `static long sys_linux_futex(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_time` (function) `kernel/syscalls.c:342` `static long sys_minios_time(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_kbd` (function) `kernel/syscalls.c:346` `static long sys_minios_kbd(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_palette` (function) `kernel/syscalls.c:366` `static long sys_minios_palette(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_kbd_raw` (function) `kernel/syscalls.c:378` `static long sys_minios_kbd_raw(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_vga_mode` (function) `kernel/syscalls.c:384` `static long sys_minios_vga_mode(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_pcspk_init` (function) `kernel/syscalls.c:391` `static long sys_minios_pcspk_init(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_pcspk_tone` (function) `kernel/syscalls.c:395` `static long sys_minios_pcspk_tone(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_doom_frame` (function) `kernel/syscalls.c:409` `static long sys_minios_doom_frame(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_gfx_zoom` (function) `kernel/syscalls.c:420` `static long sys_minios_gfx_zoom(long a1, long a2, long a3, long a4, long a5, long a6)` -- Graphics window scale request (a1): 0 native, 1 2x nearest-neighbour zoom for the 320x200 game window, 2 true...
- `sys_minios_rtc` (function) `kernel/syscalls.c:429` `static long sys_minios_rtc(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_fb_info` (function) `kernel/syscalls.c:442` `static long sys_minios_fb_info(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_pcspk_vol` (function) `kernel/syscalls.c:462` `static long sys_minios_pcspk_vol(long a1, long a2, long a3, long a4, long a5, long a6)`
- `boot` (function) `kernel/syscalls.c:479` `* boot (minfo_sleep_init from sched_init);`
- `minfo_sleep_init` (function) `kernel/syscalls.c:486` `void minfo_sleep_init(int tick_ok)`
- `minfo_tick_wake` (function) `kernel/syscalls.c:491` `void minfo_tick_wake(void *ctx)`
- `view` (function) `kernel/syscalls.c:503` `* view (same as the `clear` builtin). Anything else is -EINVAL. Each
 * out-word is range-checked...`
- `sys_minios_spawn` (function) `kernel/syscalls.c:594` `static long sys_minios_spawn(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_lz4_compress` (function) `kernel/syscalls.c:605` `static long sys_minios_lz4_compress(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_lz4_decompress` (function) `kernel/syscalls.c:618` `static long sys_minios_lz4_decompress(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_mouse` (function) `kernel/syscalls.c:632` `static long sys_minios_mouse(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_nk_frame` (function) `kernel/syscalls.c:656` `static long sys_minios_nk_frame(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sb16_audio_device` (function) `kernel/syscalls.c:669` `static device_t *sb16_audio_device(void)` -- } static long sys_minios_nk_frame(long a1, long a2, long a3, long a4, long a5, long a6) { (void)a2; (void)a3...
- `sys_minios_sb16_open` (function) `kernel/syscalls.c:675` `static long sys_minios_sb16_open(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_sb16_submit` (function) `kernel/syscalls.c:687` `static long sys_minios_sb16_submit(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_gfx_title` (function) `kernel/syscalls.c:698` `static long sys_minios_gfx_title(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_sb16_pump` (function) `kernel/syscalls.c:712` `static long sys_minios_sb16_pump(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_sb16_stream_open` (function) `kernel/syscalls.c:716` `static long sys_minios_sb16_stream_open(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_sb16_stream_close` (function) `kernel/syscalls.c:720` `static long sys_minios_sb16_stream_close(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_sb16_stream_submit` (function) `kernel/syscalls.c:724` `static long sys_minios_sb16_stream_submit(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_pcm2_open` (function) `kernel/syscalls.c:737` `static long sys_minios_pcm2_open(long a1, long a2, long a3, long a4, long a5, long a6)` -- Low-latency PCM path (pcm2, syscalls 246-248): OPEN takes flags, WRITE returns bytes taken (blocking unless...
- `sys_minios_pcm2_write` (function) `kernel/syscalls.c:742` `static long sys_minios_pcm2_write(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_pcm2_close` (function) `kernel/syscalls.c:750` `static long sys_minios_pcm2_close(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_clip_set` (function) `kernel/syscalls.c:760` `static long sys_minios_clip_set(long a1, long a2, long a3, long a4, long a5, long a6)` -- Shared text clipboard (syscalls 249-250): SET copies len bytes in (refused past 4096, never truncated), GET copies...
- `sys_minios_clip_get` (function) `kernel/syscalls.c:770` `static long sys_minios_clip_get(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_sb16_stream_vol` (function) `kernel/syscalls.c:786` `static long sys_minios_sb16_stream_vol(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_futex_wait` (function) `kernel/syscalls.c:799` `static long sys_minios_futex_wait(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_futex_wake` (function) `kernel/syscalls.c:805` `static long sys_minios_futex_wake(long a1, long a2, long a3, long a4, long a5, long a6)`
- `batch_kdispatch` (function) `kernel/syscalls.c:814` `static long batch_kdispatch(uint32_t opcode)`
- `DOOM_FRAME` (function) `kernel/syscalls.c:829` `* DOOM_FRAME (211) and NK_FRAME (220) stay as compat aliases. */
static long sys_minios_gfx_prese...`
- `sys_minios_getc_raw` (function) `kernel/syscalls.c:863` `static long sys_minios_getc_raw(long a1, long a2, long a3, long a4, long a5, long a6)` -- Raw keystroke read for fullscreen ring-3 programs (vedit): one byte from the serial + PS/2 multiplexer with no line...
- `sys_minios_submit_batch` (function) `kernel/syscalls.c:874` `static long sys_minios_submit_batch(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_rlimit` (function) `kernel/syscalls.c:897` `static long sys_minios_rlimit(long a1, long a2, long a3, long a4, long a5, long a6)` -- RLIMIT/cgroups-lite (240): a1 = op (SET/GET), a2 = resource (AS/CPU/NOFILE), a3 = value for SET.
- `sys_linux_getdents64` (function) `kernel/syscalls.c:976` `static long sys_linux_getdents64(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_dir_list` (function) `kernel/syscalls.c:1069` `static long sys_minios_dir_list(long a1, long a2, long a3, long a4, long a5, long a6)`
- `syscall_trace_enabled` (function) `kernel/syscalls.c:1241` `long syscall_trace_enabled(void)`
- `syscall_trace_set` (function) `kernel/syscalls.c:1242` `void syscall_trace_set(int on)`
- `syscall_trace_verbose_enabled` (function) `kernel/syscalls.c:1243` `long syscall_trace_verbose_enabled(void)`
- `syscall_trace_verbose_set` (function) `kernel/syscalls.c:1244` `void syscall_trace_verbose_set(int on)`
- `syscall_trace_shown` (function) `kernel/syscalls.c:1245` `unsigned long syscall_trace_shown(void)`
- `unchanged` (function) `kernel/syscalls.c:1260` `* unchanged (same code, same order of checks). Numbers >= 200 that * overlap real Linux ABIs stay in the switch as...`
- `sys_linux_read` (function) `kernel/syscalls.c:1271` `static long sys_linux_read(long a1, long a2, long a3, long a4, long a5, long a6)`
- `EAGAIN` (function) `kernel/syscalls.c:1287` `* writer open is EAGAIN (-11, retry);`
- `EOF` (function) `kernel/syscalls.c:1288` `* is EOF (0). */ KFILE *o = kfd_get(0);`
- `fd_write` (function) `kernel/syscalls.c:1327` `static long fd_write(long fd, const char *buf, long cnt)` -- Write cnt validated user bytes to fd: a dup2/pipe override on fd 1/2 (pipeline stage stdout) is served instead of...
- `sys_linux_write` (function) `kernel/syscalls.c:1351` `static long sys_linux_write(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_writev` (function) `kernel/syscalls.c:1358` `static long sys_linux_writev(long a1, long a2, long a3, long a4, long a5, long a6)`
- `kfd_install` (function) `kernel/syscalls.c:1403` `static long kfd_install(KFILE *f, int cloexec)` -- Install an open description as the lowest free fd (>= 3), honouring * close-on-exec; shared by do_open_path's file...
- `do_open_kpath` (function) `kernel/syscalls.c:1426` `static long do_open_kpath(const char *path, long flags)` -- Trusted core: `path` is already a kernel string (syscall argument that * passed SANITIZE_STR, or an *at(2) join...
- `do_open_path` (function) `kernel/syscalls.c:1452` `static long do_open_path(const char *path, long flags)`
- `sys_linux_open` (function) `kernel/syscalls.c:1457` `static long sys_linux_open(long a1, long a2, long a3, long a4, long a5, long a6)`
- `cwd` (function) `kernel/syscalls.c:1466` `* ENAMETOOLONG instead of silently resolving against the cwd (the bug
 * that broke shutil.rmtree...`
- `kfd_claim_from` (function) `kernel/syscalls.c:1529` `static long kfd_claim_from(KFILE *f, long minfd, int cloexec)` -- Claim the lowest free fd slot >= minfd for an already-opened KFILE (pipes, dup, eventfd), arming close-on-exec when...
- `kfd_claim` (function) `kernel/syscalls.c:1554` `static long kfd_claim(KFILE *f)`
- `sys_linux_pipe2` (function) `kernel/syscalls.c:1578` `static long sys_linux_pipe2(long a1, long a2, long a3, long a4, long a5, long a6)` -- pipe2 (293): O_CLOEXEC arms close-on-exec on both ends, O_NONBLOCK makes * both descriptions non-blocking; O_DIRECT...
- `sys_linux_pipe` (function) `kernel/syscalls.c:1606` `static long sys_linux_pipe(long a1, long a2, long a3, long a4, long a5, long a6)`
- `kfd_cloexec_get` (function) `kernel/syscalls.c:1612` `static int kfd_cloexec_get(long fd)` -- kfclose(w); return wfd; } ufd[0] = (int)rfd; ufd[1] = (int)wfd; return 0; } static long sys_linux_pipe(long a1, long...
- `kfd_cloexec_set` (function) `kernel/syscalls.c:1622` `static void kfd_cloexec_set(long fd, int on)`
- `kfile_status_flags` (function) `kernel/syscalls.c:1633` `static long kfile_status_flags(KFILE *f)` -- Linux open-file status flags of a description: access mode from its * kind plus O_APPEND and O_NONBLOCK.
- `sys_linux_dup3` (function) `kernel/syscalls.c:1684` `static long sys_linux_dup3(long a1, long a2, long a3, long a4, long a5, long a6)` -- break; case LINUX_F_SETFL: if (f) f->nonblock = (a3 & LINUX_O_NONBLOCK) ?
- `sys_linux_close_range` (function) `kernel/syscalls.c:1694` `static long sys_linux_close_range(long a1, long a2, long a3, long a4, long a5, long a6)` -- return r; } /* dup3 (292): dup2 with O_CLOEXEC as the only flag; old == new is EINVAL. static long...
- `sys_linux_eventfd2` (function) `kernel/syscalls.c:1718` `static long sys_linux_eventfd2(long a1, long a2, long a3, long a4, long a5, long a6)` -- spin_lock_irqsave(&fd_lock, &flags_irq); for (fd = lo; fd <= hi && fd < KFD_MAX; fd++) if (v->f[fd]) v->cloexec |=...
- `sys_linux_eventfd` (function) `kernel/syscalls.c:1731` `static long sys_linux_eventfd(long a1, long a2, long a3, long a4, long a5, long a6)`
- `kfd_poll_revents` (function) `kernel/syscalls.c:1739` `int kfd_poll_revents(int fd)` -- Docstring: poll(2) readiness of a non-socket descriptor (pipes, eventfds, files, console), masked by nothing: the...
- `kfile_user_read` (function) `kernel/syscalls.c:1774` `static long kfile_user_read(KFILE *f, char *buf, long cnt)` -- Linux read on a description: an eventfd takes its counter, a pipe read end blocks (yielding) while empty with the...
- `kfile_user_write` (function) `kernel/syscalls.c:1804` `static long kfile_user_write(KFILE *f, const char *buf, long cnt)` -- Linux write on a description: an eventfd adds to its counter, a pipe write end blocks (yielding) while full unless...
- `sys_linux_dup` (function) `kernel/syscalls.c:1833` `static long sys_linux_dup(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_dup2` (function) `kernel/syscalls.c:1848` `static long sys_linux_dup2(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_close` (function) `kernel/syscalls.c:1882` `static long sys_linux_close(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_lseek` (function) `kernel/syscalls.c:1905` `static long sys_linux_lseek(long a1, long a2, long a3, long a4, long a5, long a6)`
- `mm_ensure_cur` (function) `kernel/syscalls.c:1923` `static int mm_ensure_cur(unsigned long start, unsigned long end)` -- Back isolated user windows (mrun/proc_spawn_elf): their page tables start with only segments + stack mapped, so...
- `sys_linux_brk` (function) `kernel/syscalls.c:1932` `static long sys_linux_brk(long a1, long a2, long a3, long a4, long a5, long a6)`
- `mmap_tag_file` (function) `kernel/syscalls.c:1973` `static int mmap_tag_file(unsigned long base, int ino, unsigned long off)` -- Docstring: Tag a freshly carved live node as file-backed.
- `mmap_range_free` (function) `kernel/syscalls.c:1988` `static int mmap_range_free(unsigned long base, unsigned long len)` -- Invariant guard for every range mmap hands out: it must not overlap a live mapping or reach below the brk heap.
- `sys_linux_mmap` (function) `kernel/syscalls.c:1997` `static long sys_linux_mmap(long a1, long a2, long a3, long a4, long a5, long a6)`
- `vma_live_first_overlap` (function) `kernel/syscalls.c:2095` `static vma_node_t *vma_live_first_overlap(unsigned long base, unsigned long end)` -- Lowest live mapping overlapping [base, end), or VMA_NIL.
- `vma_live_remainder` (function) `kernel/syscalls.c:2112` `static int vma_live_remainder(unsigned long base, unsigned long len,
        int file, int ino, u...` -- int sp = 0; vma_node_t *x = vma_live_root; while (x != VMA_NIL || sp > 0) { while (x != VMA_NIL) { if (sp < 64)...
- `split` (function) `kernel/syscalls.c:2126` `* hold a split (the mapping is restored untouched). */
static long sys_linux_munmap(long a1, long...`
- `mprotect_pte` (function) `kernel/syscalls.c:2176` `static volatile unsigned long *mprotect_pte(unsigned long cr3,
        unsigned long va)` -- Docstring: Locate the PTE for a user address in the caller's live tables (syscall entry keeps the caller CR3 loaded...
- `first` (function) `kernel/syscalls.c:2200` `* passes under mm_lock: validate every page first (present, user,
 * private), then apply, so a h...`
- `vma_free_cover` (function) `kernel/syscalls.c:2281` `static vma_node_t *vma_free_cover(unsigned long base, unsigned long len)` -- Free-tree node covering [base, base+len) entirely, or VMA_NIL.
- `vma_live_overlap` (function) `kernel/syscalls.c:2300` `static int vma_live_overlap(unsigned long base, unsigned long len)` -- while (x != VMA_NIL || sp > 0) { while (x != VMA_NIL) { if (sp < 64) stack[sp++] = x; x = x->left; } x =...
- `node` (function) `kernel/syscalls.c:2322` `* mapping is one exact live VMA node (what mmap inserts);`
- `sys_linux_mremap` (function) `kernel/syscalls.c:2327` `static long sys_linux_mremap(long a1, long a2, long a3, long a4, long a5, long a6)` -- Linux mremap(25): resize or move one mmap region. glibc's realloc calls it when growing large mmap'd chunks (the...
- `sys_linux_sigaction` (function) `kernel/syscalls.c:2593` `static long sys_linux_sigaction(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_sigprocmask` (function) `kernel/syscalls.c:2598` `static long sys_linux_sigprocmask(long a1, long a2, long a3, long a4, long a5, long a6)`
- `kfile_readable_bytes` (function) `kernel/syscalls.c:2617` `static int kfile_readable_bytes(KFILE *f)` -- #define LINUX_TCGETS     0x5401 #define LINUX_TIOCGWINSZ 0x5413 #define LINUX_FIONREAD   0x541B #define...
- `FIONREAD` (function) `kernel/syscalls.c:2633` `* descriptor answers FIONREAD (bytes readable now), FIONBIO (O_NONBLOCK),
 * FIOCLEX/FIONCLEX (FD...`
- `sys_linux_access` (function) `kernel/syscalls.c:2673` `static long sys_linux_access(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_socket` (function) `kernel/syscalls.c:2695` `static long sys_linux_socket(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_connect` (function) `kernel/syscalls.c:2700` `static long sys_linux_connect(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_bind` (function) `kernel/syscalls.c:2706` `static long sys_linux_bind(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_listen` (function) `kernel/syscalls.c:2712` `static long sys_linux_listen(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_accept` (function) `kernel/syscalls.c:2717` `static long sys_linux_accept(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_sendto` (function) `kernel/syscalls.c:2723` `static long sys_linux_sendto(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_recvfrom` (function) `kernel/syscalls.c:2728` `static long sys_linux_recvfrom(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_shutdown` (function) `kernel/syscalls.c:2733` `static long sys_linux_shutdown(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_prlimit64` (function) `kernel/syscalls.c:2768` `static long sys_linux_prlimit64(long a1, long a2, long a3, long a4, long a5, long a6)` -- prlimit64(pid, resource, new, old): pid 0 or a live pid.
- `sys_linux_sched_getaffinity` (function) `kernel/syscalls.c:2801` `static long sys_linux_sched_getaffinity(long a1, long a2, long a3, long a4, long a5, long a6)` -- sched_getaffinity(pid, size, mask): every task may run on every CPU, so the mask has the low cpu_count bits set; the...
- `linux_timespec_us` (function) `kernel/syscalls.c:2823` `static long linux_timespec_us(long ts)` -- Microseconds of a user timespec, or -EINVAL when it is malformed * (negative, or tv_nsec outside [0, 1e9)); huge...
- `sys_linux_pause` (function) `kernel/syscalls.c:2840` `static long sys_linux_pause(long a1, long a2, long a3, long a4, long a5, long a6)` -- pause(34): wait for a signal.
- `sys_linux_nanosleep` (function) `kernel/syscalls.c:2848` `static long sys_linux_nanosleep(long a1, long a2, long a3, long a4, long a5, long a6)` -- nanosleep(35): sleep the relative interval at *req on the monotonic * clock; -EINVAL for a malformed interval...
- `clock` (function) `kernel/syscalls.c:2859` `* clock (the monotonic TSC clock times it, as Linux does: glibc sends * every nanosleep here as a relative...`
- `clock_gettime` (function) `kernel/syscalls.c:2863` `* clock_gettime(1) reads. */
static long sys_linux_clock_nanosleep(long a1, long a2, long a3, lon...`
- `long` (function) `kernel/syscalls.c:2865` `unsigned long (*now)(void);`
- `sys_linux_setsockopt` (function) `kernel/syscalls.c:2880` `static long sys_linux_setsockopt(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_getsockopt` (function) `kernel/syscalls.c:2887` `static long sys_linux_getsockopt(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_getsockname` (function) `kernel/syscalls.c:2894` `static long sys_linux_getsockname(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_getpeername` (function) `kernel/syscalls.c:2900` `static long sys_linux_getpeername(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_sendmsg` (function) `kernel/syscalls.c:2906` `static long sys_linux_sendmsg(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_sendmmsg` (function) `kernel/syscalls.c:2912` `static long sys_linux_sendmmsg(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_poll` (function) `kernel/syscalls.c:2920` `static long sys_linux_poll(long a1, long a2, long a3, long a4, long a5, long a6)`
- `select_timeout_ms` (function) `kernel/syscalls.c:2946` `static int select_timeout_ms(const long *t, int pselect, long *out)` -- Convert a sanitized timeval/timespec to a net_sys_poll budget: 0 polls once, -1 waits forever (net_sys_poll's...
- `sys_linux_select` (function) `kernel/syscalls.c:3031` `static long sys_linux_select(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_pselect6` (function) `kernel/syscalls.c:3036` `static long sys_linux_pselect6(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_flock` (function) `kernel/syscalls.c:3041` `static long sys_linux_flock(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_fsync` (function) `kernel/syscalls.c:3050` `static long sys_linux_fsync(long a1, long a2, long a3, long a4, long a5, long a6)` -- fsync/fdatasync: the ramdisk is memory (always durable) and MiniFS persists through kfclose/minifs_sync, so there is...
- `sys_linux_fdatasync` (function) `kernel/syscalls.c:3055` `static long sys_linux_fdatasync(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_getcwd` (function) `kernel/syscalls.c:3060` `static long sys_linux_getcwd(long a1, long a2, long a3, long a4, long a5, long a6)`
- `unlink_kpath` (function) `kernel/syscalls.c:3073` `static long unlink_kpath(const char *path)` -- static long sys_linux_getcwd(long a1, long a2, long a3, long a4, long a5, long a6) { (void)a3; (void)a4; (void)a5...
- `sys_linux_unlink` (function) `kernel/syscalls.c:3089` `static long sys_linux_unlink(long a1, long a2, long a3, long a4, long a5, long a6)`
- `readlink_path` (function) `kernel/syscalls.c:3101` `static long readlink_path(const char *path, char *buf, long bufsz)` -- readlink of /proc/self/exe answers the caller's image path (absolute, no NUL, truncated to the buffer like Linux)...
- `sys_linux_readlink` (function) `kernel/syscalls.c:3117` `static long sys_linux_readlink(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_prctl` (function) `kernel/syscalls.c:3123` `static long sys_linux_prctl(long a1, long a2, long a3, long a4, long a5, long a6)` -- if (!exe[0]) return -2; len = (long)kstrlen(exe) + 1; if (len > bufsz) len = bufsz; buf[0] = '/'; for (i = 1; i <...
- `sys_linux_rename` (function) `kernel/syscalls.c:3132` `static long sys_linux_rename(long a1, long a2, long a3, long a4, long a5, long a6)` -- rename(82): same-filesystem file move through fs_rename (ramdisk in-place, MiniFS entry move).
- `sys_linux_fstat` (function) `kernel/syscalls.c:3146` `static long sys_linux_fstat(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_gettimeofday` (function) `kernel/syscalls.c:3171` `static long sys_linux_gettimeofday(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_arch_prctl` (function) `kernel/syscalls.c:3194` `static long sys_linux_arch_prctl(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_uname` (function) `kernel/syscalls.c:3206` `static long sys_linux_uname(long a1, long a2, long a3, long a4, long a5, long a6)`
- `answer` (function) `kernel/syscalls.c:3230` `* made glibc answer (uid_t)-1, which CPython's startup reads. */
#define LINUX_UID_GID_ROOT 0

st...`
- `sys_linux_getgid` (function) `kernel/syscalls.c:3238` `static long sys_linux_getgid(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_geteuid` (function) `kernel/syscalls.c:3243` `static long sys_linux_geteuid(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_getegid` (function) `kernel/syscalls.c:3248` `static long sys_linux_getegid(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_madvise` (function) `kernel/syscalls.c:3255` `static long sys_linux_madvise(long a1, long a2, long a3, long a4, long a5, long a6)` -- madvise (28): advice only; glibc frees thread stacks with it and * ignores the result, MiniOS keeps the pages, so 0...
- `sys_linux_mkdir` (function) `kernel/syscalls.c:3263` `static long sys_linux_mkdir(long a1, long a2, long a3, long a4, long a5, long a6)` -- mkdir (83): a MiniFS directory.
- `rmdir_kpath` (function) `kernel/syscalls.c:3299` `static long rmdir_kpath(const char *path)` -- rmdir (84): remove one empty MiniFS directory (the ramdisk carries no directories of its own; its prefixes come from...
- `sys_linux_rmdir` (function) `kernel/syscalls.c:3320` `static long sys_linux_rmdir(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_umask` (function) `kernel/syscalls.c:3334` `static long sys_linux_umask(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_fchmod` (function) `kernel/syscalls.c:3357` `static long sys_linux_fchmod(long a1, long a2, long a3, long a4, long a5, long a6)`
- `trace_is_noisy` (function) `kernel/syscalls.c:3443` `static int trace_is_noisy(long n)`
- `syscall_name` (function) `kernel/syscalls.c:3472` `const char *syscall_name(long n)` -- define SC_EXTRA_COUNT (sizeof(sc_extra_names) / sizeof(sc_extra_names[0]))
- `trace_hint_print` (function) `kernel/syscalls.c:3513` `static void trace_hint_print(long n, int kind, const char *path,
                             lon...`
- `sc_record` (function) `kernel/syscalls.c:3537` `static void sc_record(long n, long a1, long a2, long a3, long ret)`
- `sc_hex` (function) `kernel/syscalls.c:3557` `static void sc_hex(unsigned long v)`
- `sc_record_dump` (function) `kernel/syscalls.c:3567` `void sc_record_dump(int pid)` -- e->a3 = a3; e->ret = ret; } static void sc_hex(unsigned long v) { static const char digits[] = "0123456789abcdef"...
- `ksyscall` (function) `kernel/syscalls.c:3585` `long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6)`
- `user_range_ok` (function) `kernel/syscalls.c:3624` `int user_range_ok(unsigned long p, unsigned long len)`
- `Discipline` (function) `kernel/syscalls.c:3637` `* * Discipline (audit 2026-09, kept as comment, not a deprecation: both * primitives are legitimate): user_range_ok...`
- `products` (function) `kernel/syscalls.c:3641` `* products (writev cnt*sizeof, poll a2*8, spawn (argc+1)*sizeof) are
 * pre-bounded against (END-...`
- `ksyscall_dispatch` (function) `kernel/syscalls.c:3654` `static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6)`
- `readlink` (function) `kernel/syscalls.c:3801` `* readlink (89). */ return readlink_path((const char *)a2, (char *)a3, a4);`
- `proc_spawn_elf` (function) `kernel/syscalls.c:3923` `* proc_spawn_elf (the same path mrun uses) and the caller blocks in * do_waitpid, so the parent address space is...`
- `k_syscall_spawn` (function) `kernel/syscalls.c:3932` `static int k_syscall_spawn(const char *path, const char *redirect,
                             i...`

## kernel/syscalls_proc.c
Depends on: `headers/proc_sec.h`, `headers/sanitize.h`, `headers/sched.h`, `headers/syscalls_proc.h`
- `state` (function) `kernel/syscalls_proc.c:5` `* touches only scheduler state (current_pid, procs[], do_* / * seccomp_* / yield) plus the kernel-wide user_range_ok...`
- `sys_minios_clone` (function) `kernel/syscalls_proc.c:18` `long sys_minios_clone(long flags, long newsp, long a3, long a4, long a5, long a6)`
- `sys_minios_thread_spawn` (function) `kernel/syscalls_proc.c:24` `long sys_minios_thread_spawn(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_minios_seccomp` (function) `kernel/syscalls_proc.c:37` `long sys_minios_seccomp(long a1, long a2, long a3, long a4, long a5, long a6)` -- Seccomp-basic (238): a1 = op (1 deny-one, 2 allow-one, 3 deny-all), a2 = syscall number (ops 1-2).
- `sys_minios_nice` (function) `kernel/syscalls_proc.c:53` `long sys_minios_nice(long a1, long a2, long a3, long a4, long a5, long a6)` -- int pid = current_pid; if (a1 == SECCOMP_OP_DENY_ONE) return seccomp_deny_one(pid, (int)a2); if (a1 ==...
- `sys_linux_yield` (function) `kernel/syscalls_proc.c:66` `long sys_linux_yield(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_getpid` (function) `kernel/syscalls_proc.c:75` `long sys_linux_getpid(long a1, long a2, long a3, long a4, long a5, long a6)` -- getpid answers the thread group: a CLONE_THREAD member reports its leader, a process its own pid.
- `sys_linux_clone` (function) `kernel/syscalls_proc.c:83` `long sys_linux_clone(long a1, long a2, long a3, long a4, long a5, long a6)` -- getpid answers the thread group: a CLONE_THREAD member reports its leader, a process its own pid.
- `sys_linux_fork` (function) `kernel/syscalls_proc.c:89` `long sys_linux_fork(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_vfork` (function) `kernel/syscalls_proc.c:94` `long sys_linux_vfork(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_execve` (function) `kernel/syscalls_proc.c:99` `long sys_linux_execve(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_exit` (function) `kernel/syscalls_proc.c:184` `long sys_linux_exit(long a1, long a2, long a3, long a4, long a5, long a6)`
- `kill` (function) `kernel/syscalls_proc.c:192` `* historic kill (SIGKILL), -N is signal N (a seccomp kill is -SIGSYS). */
#define LINUX_WNOHANG  ...`
- `groups` (function) `kernel/syscalls_proc.c:213` `* groups (pid 0 and < -1) are not modelled and wait for any child. */
long sys_linux_wait4(long a...`
- `sig` (function) `kernel/syscalls_proc.c:245` `* the target as killed by sig (wait4 reports WTERMSIG);`
- `sys_linux_kill` (function) `kernel/syscalls_proc.c:248` `long sys_linux_kill(long a1, long a2, long a3, long a4, long a5, long a6)` -- kill(pid, sig): sig 0 only probes that pid exists; a fatal signal ends the target as killed by sig (wait4 reports...
- `sys_linux_gettid` (function) `kernel/syscalls_proc.c:259` `long sys_linux_gettid(long a1, long a2, long a3, long a4, long a5, long a6)`

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
Imported by: `headers/tls_port.h`, `mcp/mcp_dbg_driver.py`, `mcp/mcp_dogfood.py`, `mcp/minios_addons.py`, `mcp/minios_mcp.py`, `progs/doomgeneric/doomgeneric_xlib.c`, `progs/src/lxabi.c`, `progs/src/lxsel.c`, `progs/src/test_py.py`, `progs/tls_u/tls_u_port.c`, `tests/test_vma_bench.c`, `tools/boot_wl.py`, `tools/gdb_repro.py`, `tools/minios_cli.py`, `tools/minios_gui.py`, `tools/minios_hyper.py`, `tools/probe_compute_vga.py`, `tools/probe_minicraft.py`, `tools/qga_client.py`, `tools/repro_gui.py`, `tools/test_gui_fashion.py`, `tools/test_gui_freedom.py`, `tools/test_gui_gfxview.py`, `tools/test_gui_icon_cwd.py`, `tools/test_gui_menu.py`, `tools/test_gui_wm.py`, `tools/test_gui_zoom.py`, `tools/test_http_server.py`, `tools/test_readme_shot.py`, `tools/tls_test.py`
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


Next: [API_p9.md](API_p9.md)
