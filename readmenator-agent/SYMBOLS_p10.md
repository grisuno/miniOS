# Symbols (page 10 of 28)
Previous: [SYMBOLS_p9.md](SYMBOLS_p9.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `k_register_program` | function | `kernel/symtab.c:49` | `void k_register_program(const char *name, prog_entry_t entry)` |
| `k_register_symbol` | function | `kernel/symtab.c:10` | `void k_register_symbol(const char *name, void *addr)` |
| `k_spawn` | function | `kernel/symtab.c:65` | `int k_spawn(const char *name, int argc, char **argv)` |
| `kprog_lookup` | function | `kernel/symtab.c:42` | `KProg *kprog_lookup(const char *name)` |
| `kprog_slot` | function | `kernel/symtab.c:34` | `KProg *kprog_slot(const char *name)` |
| `ksym_resolve` | function | `kernel/symtab.c:18` | `void *ksym_resolve(const char *name)` |
| `cond_broadcast` | function | `kernel/sync.c:251` | `void cond_broadcast(cond_t *c)` |
| `cond_init` | function | `kernel/sync.c:237` | `void cond_init(cond_t *c)` |
| `cond_signal` | function | `kernel/sync.c:247` | `void cond_signal(cond_t *c)` |
| `cond_wait` | function | `kernel/sync.c:241` | `void cond_wait(cond_t *c, mutex_t *m)` |
| `mutex_init` | function | `kernel/sync.c:78` | `void mutex_init(mutex_t *m)` |
| `mutex_lock` | function | `kernel/sync.c:152` | `void mutex_lock(mutex_t *m)` |
| `mutex_trylock` | function | `kernel/sync.c:172` | `int mutex_trylock(mutex_t *m)` |
| `mutex_unlock` | function | `kernel/sync.c:188` | `void mutex_unlock(mutex_t *m)` |
| `pi_boost` | function | `kernel/sync.c:126` | `static void pi_boost(int waiter, int owner)` |
| `pi_get_eff` | function | `kernel/sync.c:110` | `int pi_get_eff(int pid)` |
| `pi_recompute` | function | `kernel/sync.c:115` | `static void pi_recompute(int pid)` |
| `pi_set_base` | function | `kernel/sync.c:101` | `void pi_set_base(int pid, int prio)` |
| `pi_valid` | function | `kernel/sync.c:95` | `static int pi_valid(int pid)` |
| `rwlock_init` | function | `kernel/sync.c:255` | `void rwlock_init(rwlock_t *rw)` |
| `rwlock_read_lock` | function | `kernel/sync.c:289` | `void rwlock_read_lock(rwlock_t *rw)` |
| `rwlock_read_trylock` | function | `kernel/sync.c:263` | `int rwlock_read_trylock(rwlock_t *rw)` |
| `rwlock_read_unlock` | function | `kernel/sync.c:296` | `void rwlock_read_unlock(rwlock_t *rw)` |
| `rwlock_write_lock` | function | `kernel/sync.c:306` | `void rwlock_write_lock(rwlock_t *rw)` |
| `rwlock_write_trylock` | function | `kernel/sync.c:277` | `int rwlock_write_trylock(rwlock_t *rw)` |
| `rwlock_write_unlock` | function | `kernel/sync.c:328` | `void rwlock_write_unlock(rwlock_t *rw)` |
| `sem_init` | function | `kernel/sync.c:209` | `void sem_init(sem_t *s, int value)` |
| `sem_post` | function | `kernel/sync.c:229` | `void sem_post(sem_t *s)` |
| `sem_wait` | function | `kernel/sync.c:215` | `void sem_wait(sem_t *s)` |
| `sleep_on` | function | `kernel/sync.c:35` | `void sleep_on(wait_queue_t *q)` |
| `t_cur_pid` | variable | `kernel/sync.c:26` | `extern int t_cur_pid;` |
| `wake_up` | function | `kernel/sync.c:56` | `int wake_up(wait_queue_t *q)` |
| `wake_up_all` | function | `kernel/sync.c:72` | `int wake_up_all(wait_queue_t *q)` |
| `wq_init` | function | `kernel/sync.c:29` | `void wq_init(wait_queue_t *q)` |
| `DOOM_FRAME` | function | `kernel/syscalls.c:829` | `* DOOM_FRAME (211) and NK_FRAME (220) stay as compat aliases. */ static long sys_minios_gfx_prese...` |
| `Discipline` | function | `kernel/syscalls.c:3637` | `* * Discipline (audit 2026-09, kept as comment, not a deprecation: both * primitives are legitimate): user_range_ok...` |
| `EAGAIN` | function | `kernel/syscalls.c:1287` | `* writer open is EAGAIN (-11, retry);` |
| `EOF` | function | `kernel/syscalls.c:1288` | `* is EOF (0). */ KFILE *o = kfd_get(0);` |
| `FD_STD_COUNT` | macro | `kernel/syscalls.c:1523` | `#define FD_STD_COUNT` |
| `FIONREAD` | function | `kernel/syscalls.c:2633` | `* descriptor answers FIONREAD (bytes readable now), FIONBIO (O_NONBLOCK),  * FIOCLEX/FIONCLEX (FD...` |
| `GETDENTS64_ALIGN` | macro | `kernel/syscalls.c:950` | `#define GETDENTS64_ALIGN` |
| `GETDENTS64_NAME_OFF` | macro | `kernel/syscalls.c:949` | `#define GETDENTS64_NAME_OFF` |
| `KFD_MAX` | macro | `kernel/syscalls.c:52` | `#define KFD_MAX` |
| `LINUX_AT_FDCWD` | macro | `kernel/syscalls.c:1468` | `#define LINUX_AT_FDCWD` |
| `LINUX_CLOCK_BOOTTIME` | macro | `kernel/syscalls.c:2814` | `#define LINUX_CLOCK_BOOTTIME` |
| `LINUX_CLOCK_MONOTONIC` | macro | `kernel/syscalls.c:2813` | `#define LINUX_CLOCK_MONOTONIC` |
| `LINUX_CLOCK_REALTIME` | macro | `kernel/syscalls.c:2812` | `#define LINUX_CLOCK_REALTIME` |
| `LINUX_CLOSE_RANGE_CLOEXEC` | macro | `kernel/syscalls.c:1518` | `#define LINUX_CLOSE_RANGE_CLOEXEC` |
| `LINUX_CLOSE_RANGE_UNSHARE` | macro | `kernel/syscalls.c:1517` | `#define LINUX_CLOSE_RANGE_UNSHARE` |
| `LINUX_CPUMASK_BYTES` | macro | `kernel/syscalls.c:2747` | `#define LINUX_CPUMASK_BYTES` |
| `LINUX_DT_DIR` | macro | `kernel/syscalls.c:947` | `#define LINUX_DT_DIR` |
| `LINUX_DT_REG` | macro | `kernel/syscalls.c:948` | `#define LINUX_DT_REG` |
| `LINUX_EFD_CLOEXEC` | macro | `kernel/syscalls.c:1521` | `#define LINUX_EFD_CLOEXEC` |
| `LINUX_EFD_NONBLOCK` | macro | `kernel/syscalls.c:1520` | `#define LINUX_EFD_NONBLOCK` |
| `LINUX_EFD_SEMAPHORE` | macro | `kernel/syscalls.c:1519` | `#define LINUX_EFD_SEMAPHORE` |
| `LINUX_ENOTTY` | macro | `kernel/syscalls.c:2610` | `#define LINUX_ENOTTY` |
| `LINUX_EVENTFD_WORD` | macro | `kernel/syscalls.c:1522` | `#define LINUX_EVENTFD_WORD` |
| `LINUX_FD_CLOEXEC` | macro | `kernel/syscalls.c:1510` | `#define LINUX_FD_CLOEXEC` |
| `LINUX_FIOCLEX` | macro | `kernel/syscalls.c:2608` | `#define LINUX_FIOCLEX` |
| `LINUX_FIONBIO` | macro | `kernel/syscalls.c:2606` | `#define LINUX_FIONBIO` |
| `LINUX_FIONCLEX` | macro | `kernel/syscalls.c:2607` | `#define LINUX_FIONCLEX` |
| `LINUX_FIONREAD` | macro | `kernel/syscalls.c:2605` | `#define LINUX_FIONREAD` |
| `LINUX_F_DUPFD` | macro | `kernel/syscalls.c:1511` | `#define LINUX_F_DUPFD` |
| `LINUX_F_DUPFD_CLOEXEC` | macro | `kernel/syscalls.c:1516` | `#define LINUX_F_DUPFD_CLOEXEC` |
| `LINUX_F_GETFD` | macro | `kernel/syscalls.c:1512` | `#define LINUX_F_GETFD` |
| `LINUX_F_GETFL` | macro | `kernel/syscalls.c:1514` | `#define LINUX_F_GETFL` |
| `LINUX_F_SETFD` | macro | `kernel/syscalls.c:1513` | `#define LINUX_F_SETFD` |
| `LINUX_F_SETFL` | macro | `kernel/syscalls.c:1515` | `#define LINUX_F_SETFL` |
| `LINUX_IOCTL_INT` | macro | `kernel/syscalls.c:2614` | `#define LINUX_IOCTL_INT` |
| `LINUX_MAP_ANONYMOUS` | macro | `kernel/syscalls.c:1968` | `#define LINUX_MAP_ANONYMOUS` |
| `LINUX_MAP_FIXED` | macro | `kernel/syscalls.c:1967` | `#define LINUX_MAP_FIXED` |
| `LINUX_MAP_PRIVATE` | macro | `kernel/syscalls.c:1966` | `#define LINUX_MAP_PRIVATE` |
| `LINUX_MAP_SHARED` | macro | `kernel/syscalls.c:1965` | `#define LINUX_MAP_SHARED` |
| `LINUX_MREMAP_FIXED` | macro | `kernel/syscalls.c:2277` | `#define LINUX_MREMAP_FIXED` |
| `LINUX_MREMAP_MAYMOVE` | macro | `kernel/syscalls.c:2276` | `#define LINUX_MREMAP_MAYMOVE` |
| `LINUX_NS_PER_S` | macro | `kernel/syscalls.c:2818` | `#define LINUX_NS_PER_S` |
| `LINUX_NS_PER_US` | macro | `kernel/syscalls.c:2816` | `#define LINUX_NS_PER_US` |
| `LINUX_O_APPEND` | macro | `kernel/syscalls.c:1506` | `#define LINUX_O_APPEND` |
| `LINUX_O_CLOEXEC` | macro | `kernel/syscalls.c:1509` | `#define LINUX_O_CLOEXEC` |
| `LINUX_O_DIRECT` | macro | `kernel/syscalls.c:1508` | `#define LINUX_O_DIRECT` |
| `LINUX_O_NONBLOCK` | macro | `kernel/syscalls.c:1507` | `#define LINUX_O_NONBLOCK` |
| `LINUX_O_RDONLY` | macro | `kernel/syscalls.c:1503` | `#define LINUX_O_RDONLY` |
| `LINUX_O_RDWR` | macro | `kernel/syscalls.c:1505` | `#define LINUX_O_RDWR` |
| `LINUX_O_WRONLY` | macro | `kernel/syscalls.c:1504` | `#define LINUX_O_WRONLY` |
| `LINUX_RLIMIT_AS` | macro | `kernel/syscalls.c:2741` | `#define LINUX_RLIMIT_AS` |
| `LINUX_RLIMIT_CPU` | macro | `kernel/syscalls.c:2738` | `#define LINUX_RLIMIT_CPU` |
| `LINUX_RLIMIT_NLIMITS` | macro | `kernel/syscalls.c:2742` | `#define LINUX_RLIMIT_NLIMITS` |
| `LINUX_RLIMIT_NOFILE` | macro | `kernel/syscalls.c:2740` | `#define LINUX_RLIMIT_NOFILE` |
| `LINUX_RLIMIT_PAIR` | macro | `kernel/syscalls.c:2744` | `#define LINUX_RLIMIT_PAIR` |
| `LINUX_RLIMIT_STACK` | macro | `kernel/syscalls.c:2739` | `#define LINUX_RLIMIT_STACK` |
| `LINUX_RLIMIT_TICKS_PER_S` | macro | `kernel/syscalls.c:2746` | `#define LINUX_RLIMIT_TICKS_PER_S` |
| `LINUX_RLIM_INFINITY` | macro | `kernel/syscalls.c:2743` | `#define LINUX_RLIM_INFINITY` |
| `LINUX_SLEEP_MAX_S` | macro | `kernel/syscalls.c:2819` | `#define LINUX_SLEEP_MAX_S` |
| `LINUX_SYSCALL_COUNT` | macro | `kernel/syscalls.c:3368` | `#define LINUX_SYSCALL_COUNT` |
| `LINUX_TCGETS` | macro | `kernel/syscalls.c:2603` | `#define LINUX_TCGETS` |
| `LINUX_TCGETS2` | macro | `kernel/syscalls.c:2609` | `#define LINUX_TCGETS2` |
| `LINUX_TERMIOS2_LEN` | macro | `kernel/syscalls.c:2613` | `#define LINUX_TERMIOS2_LEN` |
| `LINUX_TERMIOS_LEN` | macro | `kernel/syscalls.c:2612` | `#define LINUX_TERMIOS_LEN` |
| `LINUX_TIMER_ABSTIME` | macro | `kernel/syscalls.c:2815` | `#define LINUX_TIMER_ABSTIME` |
| `LINUX_TIOCGWINSZ` | macro | `kernel/syscalls.c:2604` | `#define LINUX_TIOCGWINSZ` |
| `LINUX_UID_GID_ROOT` | macro | `kernel/syscalls.c:3231` | `#define LINUX_UID_GID_ROOT` |
| `LINUX_US_PER_S` | macro | `kernel/syscalls.c:2817` | `#define LINUX_US_PER_S` |
| `LINUX_WINSIZE_LEN` | macro | `kernel/syscalls.c:2611` | `#define LINUX_WINSIZE_LEN` |
| `MINIOS_SYSCALL_BASE` | macro | `kernel/syscalls.c:243` | `#define MINIOS_SYSCALL_BASE` |
| `MINIOS_SYSCALL_COUNT` | macro | `kernel/syscalls.c:244` | `#define MINIOS_SYSCALL_COUNT` |
| `NULL` | function | `kernel/syscalls.c:166` | `* on NULL (already released or never owned). */ void kfd_view_release(proc_t *p)` |
| `PROC_SELF_EXE` | macro | `kernel/syscalls.c:3096` | `#define PROC_SELF_EXE` |
| `SC_EXTRA_COUNT` | macro | `kernel/syscalls.c:3471` | `#define SC_EXTRA_COUNT` |
| `SC_RECORD_LEN` | macro | `kernel/syscalls.c:3532` | `#define SC_RECORD_LEN` |
| `SELECT_NFDS_MAX` | macro | `kernel/syscalls.c:2935` | `#define SELECT_NFDS_MAX` |
| `SELECT_TIMEOUT_MS_MAX` | macro | `kernel/syscalls.c:2940` | `#define SELECT_TIMEOUT_MS_MAX` |
| `SELECT_TIMESPEC_BYTES` | macro | `kernel/syscalls.c:2937` | `#define SELECT_TIMESPEC_BYTES` |
| `SELECT_TIMEVAL_BYTES` | macro | `kernel/syscalls.c:2936` | `#define SELECT_TIMEVAL_BYTES` |
| `SYSCALL_TRACE` | macro | `kernel/syscalls.c:1231` | `#define SYSCALL_TRACE` |
| `SYS_NOISY_GETC_RAW` | macro | `kernel/syscalls.c:1254` | `#define SYS_NOISY_GETC_RAW` |
| `SYS_NOISY_KBD` | macro | `kernel/syscalls.c:1252` | `#define SYS_NOISY_KBD` |
| `SYS_NOISY_MOUSE` | macro | `kernel/syscalls.c:1253` | `#define SYS_NOISY_MOUSE` |
| `SYS_NOISY_TIME` | macro | `kernel/syscalls.c:1251` | `#define SYS_NOISY_TIME` |
| `TRACE_HINT_NONE` | macro | `kernel/syscalls.c:3493` | `#define TRACE_HINT_NONE` |
| `TRACE_HINT_PATH` | macro | `kernel/syscalls.c:3494` | `#define TRACE_HINT_PATH` |
| `answer` | function | `kernel/syscalls.c:3230` | `* made glibc answer (uid_t)-1, which CPython's startup reads. */ #define LINUX_UID_GID_ROOT 0  st...` |
| `batch_kdispatch` | function | `kernel/syscalls.c:814` | `static long batch_kdispatch(uint32_t opcode)` |
| `boot` | function | `kernel/syscalls.c:479` | `* boot (minfo_sleep_init from sched_init);` |
| `by` | function | `kernel/syscalls.c:225` | `* is indexed by (syscall_number - 200). New syscalls are added by: * 1. Adding a MINIOS_SYS_* constant to...` |
| `clock` | function | `kernel/syscalls.c:2859` | `* clock (the monotonic TSC clock times it, as Linux does: glibc sends * every nanosleep here as a relative...` |
| `clock_gettime` | function | `kernel/syscalls.c:2863` | `* clock_gettime(1) reads. */ static long sys_linux_clock_nanosleep(long a1, long a2, long a3, lon...` |
| `cwd` | function | `kernel/syscalls.c:1466` | `* ENAMETOOLONG instead of silently resolving against the cwd (the bug  * that broke shutil.rmtree...` |
| `do_open_kpath` | function | `kernel/syscalls.c:1426` | `static long do_open_kpath(const char *path, long flags)` |
| `do_open_path` | function | `kernel/syscalls.c:1452` | `static long do_open_path(const char *path, long flags)` |
| `fd_write` | function | `kernel/syscalls.c:1327` | `static long fd_write(long fd, const char *buf, long cnt)` |
| `first` | function | `kernel/syscalls.c:2200` | `* passes under mm_lock: validate every page first (present, user,  * private), then apply, so a h...` |
| `gfx_win_title` | variable | `kernel/syscalls.c:703` | `extern const char *gfx_win_title;` |
| `gfx_zoom_2x` | variable | `kernel/syscalls.c:422` | `extern int gfx_zoom_2x;` |
| `k_syscall_spawn` | function | `kernel/syscalls.c:3932` | `static int k_syscall_spawn(const char *path, const char *redirect,                              i...` |
| `kfd_claim` | function | `kernel/syscalls.c:1554` | `static long kfd_claim(KFILE *f)` |
| `kfd_claim_from` | function | `kernel/syscalls.c:1529` | `static long kfd_claim_from(KFILE *f, long minfd, int cloexec)` |
| `kfd_cloexec_get` | function | `kernel/syscalls.c:1612` | `static int kfd_cloexec_get(long fd)` |
| `kfd_cloexec_set` | function | `kernel/syscalls.c:1622` | `static void kfd_cloexec_set(long fd, int on)` |
| `kfd_get` | function | `kernel/syscalls.c:90` | `KFILE *kfd_get(int fd)` |
| `kfd_install` | function | `kernel/syscalls.c:1403` | `static long kfd_install(KFILE *f, int cloexec)` |
| `kfd_poll_revents` | function | `kernel/syscalls.c:1739` | `int kfd_poll_revents(int fd)` |
| `kfd_put` | function | `kernel/syscalls.c:103` | `void kfd_put(KFILE *f)` |
| `kfd_view_cloexec` | function | `kernel/syscalls.c:197` | `void kfd_view_cloexec(void)` |
| `kfd_view_count` | function | `kernel/syscalls.c:115` | `static int kfd_view_count(kfd_view_t *v)` |
| `kfd_view_current` | function | `kernel/syscalls.c:61` | `static kfd_view_t *kfd_view_current(void)` |
| `kfd_view_root` | function | `kernel/syscalls.c:71` | `kfd_view_t *kfd_view_root(void)` |
| `kfile_readable_bytes` | function | `kernel/syscalls.c:2617` | `static int kfile_readable_bytes(KFILE *f)` |
| `kfile_status_flags` | function | `kernel/syscalls.c:1633` | `static long kfile_status_flags(KFILE *f)` |
| `kfile_user_read` | function | `kernel/syscalls.c:1774` | `static long kfile_user_read(KFILE *f, char *buf, long cnt)` |
| `kfile_user_write` | function | `kernel/syscalls.c:1804` | `static long kfile_user_write(KFILE *f, const char *buf, long cnt)` |
| `kiovec` | struct | `kernel/syscalls.c:1229` | `` |
| `ksyscall` | function | `kernel/syscalls.c:3585` | `long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6)` |
| `ksyscall_dispatch` | function | `kernel/syscalls.c:3654` | `static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6)` |
| `linux_timespec_us` | function | `kernel/syscalls.c:2823` | `static long linux_timespec_us(long ts)` |
| `long` | function | `kernel/syscalls.c:2865` | `unsigned long (*now)(void);` |
| `minfo_sleep_init` | function | `kernel/syscalls.c:486` | `void minfo_sleep_init(int tick_ok)` |
| `minfo_tick_wake` | function | `kernel/syscalls.c:491` | `void minfo_tick_wake(void *ctx)` |
| `minios_syscall_entry_t` | struct | `kernel/syscalls.c:238` | `` |
| `mm_ensure_cur` | function | `kernel/syscalls.c:1923` | `static int mm_ensure_cur(unsigned long start, unsigned long end)` |
| `mmap_range_free` | function | `kernel/syscalls.c:1988` | `static int mmap_range_free(unsigned long base, unsigned long len)` |
| `mmap_tag_file` | function | `kernel/syscalls.c:1973` | `static int mmap_tag_file(unsigned long base, int ino, unsigned long off)` |
| `mprotect_pte` | function | `kernel/syscalls.c:2176` | `static volatile unsigned long *mprotect_pte(unsigned long cr3,         unsigned long va)` |
| `node` | function | `kernel/syscalls.c:2322` | `* mapping is one exact live VMA node (what mmap inserts);` |
| `proc_spawn_elf` | function | `kernel/syscalls.c:3923` | `* proc_spawn_elf (the same path mrun uses) and the caller blocks in * do_waitpid, so the parent address space is...` |
| `products` | function | `kernel/syscalls.c:3641` | `* products (writev cnt*sizeof, poll a2*8, spawn (argc+1)*sizeof) are  * pre-bounded against (END-...` |
| `readlink` | function | `kernel/syscalls.c:3801` | `* readlink (89). */ return readlink_path((const char *)a2, (char *)a3, a4);` |
| `readlink_path` | function | `kernel/syscalls.c:3101` | `static long readlink_path(const char *path, char *buf, long bufsz)` |
| `rmdir_kpath` | function | `kernel/syscalls.c:3299` | `static long rmdir_kpath(const char *path)` |
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
| `DOCK_GLOW_PAD` | macro | `kernel/vga_fb.c:2326` | `#define DOCK_GLOW_PAD` |
| `FBT` | macro | `kernel/vga_fb.c:153` | `#define FBT` |
| `FB_OFFSET` | macro | `kernel/vga_fb.c:1775` | `#define FB_OFFSET(x,y)` |
| `GFX_CURSOR_FOLLOW_TICKS` | macro | `kernel/vga_fb.c:633` | `#define GFX_CURSOR_FOLLOW_TICKS` |
| `GFX_CURSOR_IDLE_TICKS` | macro | `kernel/vga_fb.c:627` | `#define GFX_CURSOR_IDLE_TICKS` |
| `GFX_KEEP_BYTES` | macro | `kernel/vga_fb.c:601` | `#define GFX_KEEP_BYTES` |
| `GFX_PROG_LEN` | macro | `kernel/vga_fb.c:685` | `#define GFX_PROG_LEN` |
| `GFX_SRC_IDX` | macro | `kernel/vga_fb.c:599` | `#define GFX_SRC_IDX` |
| `GFX_SRC_RGB` | macro | `kernel/vga_fb.c:600` | `#define GFX_SRC_RGB` |
| `JELLY_BLOCK` | macro | `kernel/vga_fb.c:3648` | `#define JELLY_BLOCK` |
| `JELLY_ROW_MAX` | macro | `kernel/vga_fb.c:3650` | `#define JELLY_ROW_MAX` |
| `JELLY_SUBSTEPS` | macro | `kernel/vga_fb.c:3649` | `#define JELLY_SUBSTEPS` |
| `LG_LINE` | macro | `kernel/vga_fb.c:312` | `#define LG_LINE(a)` |
| `PROFILE_MARGIN` | macro | `kernel/vga_fb.c:2329` | `#define PROFILE_MARGIN` |
| `PROFILE_PAD` | macro | `kernel/vga_fb.c:2327` | `#define PROFILE_PAD` |
| `PROFILE_RING` | macro | `kernel/vga_fb.c:2328` | `#define PROFILE_RING` |
| `PROFILE_TEXT_COLS` | macro | `kernel/vga_fb.c:2330` | `#define PROFILE_TEXT_COLS` |
| `TB_GFX_TITLE_MAX` | macro | `kernel/vga_fb.c:3118` | `#define TB_GFX_TITLE_MAX` |
| `TEXT_BG_NONE` | macro | `kernel/vga_fb.c:2166` | `#define TEXT_BG_NONE` |
| `WIN_DEF_COLS` | macro | `kernel/vga_fb.c:1018` | `#define WIN_DEF_COLS` |
| `WIN_DEF_ROWS` | macro | `kernel/vga_fb.c:1019` | `#define WIN_DEF_ROWS` |
| `WIN_DEF_X` | macro | `kernel/vga_fb.c:1020` | `#define WIN_DEF_X` |
| `WIN_DEF_Y` | macro | `kernel/vga_fb.c:1021` | `#define WIN_DEF_Y` |
| `WM_ELINE_SZ` | macro | `kernel/vga_fb.c:1051` | `#define WM_ELINE_SZ` |
| `WM_MAX_TERMS` | macro | `kernel/vga_fb.c:1049` | `#define WM_MAX_TERMS` |
| `act_nrows` | function | `kernel/vga_fb.c:387` | `static int act_nrows(void)` |
| `alone` | function | `kernel/vga_fb.c:1487` | `* window alone (an unfocused graphics window minimizes to the taskbar,  * exactly like the hidden...` |
| `app` | function | `kernel/vga_fb.c:1278` | `* a gfx child spawned from another gfx app (file -> vedit) keeps the * terminal focused, so its keys and wheel keep...` |
| `blur_reserve` | function | `kernel/vga_fb.c:2260` | `static void blur_reserve(void)` |
| `blur_usable` | function | `kernel/vga_fb.c:2278` | `static int blur_usable(int w, int h)` |
| `buffer` | function | `kernel/vga_fb.c:3473` | `* owns the buffer (indices reset, render reads an empty ring). */ void term_clear(void)` |
| `chrome_blur_counts` | function | `kernel/vga_fb.c:2252` | `void chrome_blur_counts(int *active, unsigned long *panels)` |
| `chrome_color` | function | `kernel/vga_fb.c:2333` | `static unsigned long chrome_color(unsigned idx)` |
| `chrome_corner_origin` | function | `kernel/vga_fb.c:2412` | `static void chrome_corner_origin(const chrome_win_t *c, int k, int *ox, int *oy)` |
| `chrome_disc` | function | `kernel/vga_fb.c:2626` | `static void chrome_disc(int cx2, int cy2, int r2, unsigned long color, int alpha)` |
| `chrome_frost_begin` | function | `kernel/vga_fb.c:2300` | `static const unsigned int *chrome_frost_begin(int x, int y, int w, int h)` |
| `chrome_frost_buffer` | function | `kernel/vga_fb.c:2287` | `static void chrome_frost_buffer(unsigned int *px, int w, int h)` |
| `chrome_frost_end` | function | `kernel/vga_fb.c:2318` | `static void chrome_frost_end(const unsigned int *frost)` |
| `chrome_glass` | function | `kernel/vga_fb.c:2588` | `static void chrome_glass(int x, int y, int w, int h)` |
| `chrome_glow` | function | `kernel/vga_fb.c:2664` | `static void chrome_glow(int x, int y, int w, int h)` |
| `chrome_panel_coverage` | function | `kernel/vga_fb.c:2574` | `static int chrome_panel_coverage(int xx, int yy, int x, int y, int w, int h)` |
| `chrome_profile_card` | function | `kernel/vga_fb.c:2684` | `static void chrome_profile_card(void)` |
| `chrome_term_fill` | function | `kernel/vga_fb.c:2558` | `static int chrome_term_fill(void)` |
| `chrome_tint_capture` | function | `kernel/vga_fb.c:2511` | `static void chrome_tint_capture(int idx, int x, int y, int w, int h)` |
| `chrome_tint_live` | function | `kernel/vga_fb.c:2544` | `static const chrome_tint_t *chrome_tint_live(void)` |
| `chrome_tint_t` | struct | `kernel/vga_fb.c:436` | `` |
| `chrome_title_strip` | function | `kernel/vga_fb.c:2373` | `static int chrome_title_strip(int x, int y, int w, int focused)` |
| `chrome_traffic_lights` | function | `kernel/vga_fb.c:2648` | `static int chrome_traffic_lights(int bx, int by)` |
| `chrome_win_capture` | function | `kernel/vga_fb.c:2431` | `static void chrome_win_capture(int idx, int x, int y, int w, int h)` |
| `chrome_win_cut` | function | `kernel/vga_fb.c:2461` | `static void chrome_win_cut(const chrome_win_t *c, int k)` |
| `chrome_win_live` | function | `kernel/vga_fb.c:2482` | `static chrome_win_t *chrome_win_live(void)` |
| `chrome_win_rect` | function | `kernel/vga_fb.c:2400` | `static int chrome_win_rect(int id, int *x, int *y, int *w, int *h)` |
| `chrome_win_recut_bottom` | function | `kernel/vga_fb.c:2497` | `static void chrome_win_recut_bottom(int corner)` |
| `chrome_win_t` | struct | `kernel/vga_fb.c:2389` | `` |
| `chrome_wins_reset` | function | `kernel/vga_fb.c:2420` | `static void chrome_wins_reset(void)` |
| `ci_eq` | function | `kernel/vga_fb.c:724` | `static int ci_eq(const char *a, const char *b)` |
| `command` | function | `kernel/vga_fb.c:5185` | `* its launch command (config-driven, covers apps that never set a window * title);` |
| `compositions` | function | `kernel/vga_fb.c:141` | `* compositions (an ISR tick composing inside a syscall composition) draw * into the same shadow and leave the...` |
| `content` | function | `kernel/vga_fb.c:1352` | `* windows would share content (same prompt/output on both) and a park  * would alias src == dst. ...` |
| `coordinates` | function | `kernel/vga_fb.c:864` | `* windows keep the exact historical coordinates (including outside the * window);` |
| `desktop_shortcuts_draw` | function | `kernel/vga_fb.c:5072` | `void desktop_shortcuts_draw(void)` |
| `desktop_shortcuts_hit_test` | function | `kernel/vga_fb.c:5211` | `const char *desktop_shortcuts_hit_test(int mx, int my)` |
| `desktop_shortcuts_load` | function | `kernel/vga_fb.c:4747` | `void desktop_shortcuts_load(void)` |
| `directly` | function | `kernel/vga_fb.c:2802` | `* RGB sources pack directly (quantized to the wallpaper cube in 8-bit). */ static void gfx_scale_...` |
| `disp_clamp` | function | `kernel/vga_fb.c:398` | `static void disp_clamp(void)` |
| `dock_bounce_counts` | function | `kernel/vga_fb.c:4869` | `void dock_bounce_counts(unsigned long *kicks, unsigned long *paints)` |
| `dock_bounce_elapsed` | function | `kernel/vga_fb.c:4885` | `static unsigned long dock_bounce_elapsed(void)` |
| `dock_bounce_live` | function | `kernel/vga_fb.c:4893` | `static int dock_bounce_live(void)` |
| `dock_click_count` | function | `kernel/vga_fb.c:4879` | `void dock_click_count(unsigned long *edges)` |
| `dock_hover_index` | function | `kernel/vga_fb.c:4842` | `static int dock_hover_index(int mx, int my)` |
| `dock_icon_size` | function | `kernel/vga_fb.c:4982` | `static int dock_icon_size(int i, int level)` |
| `dock_label_px` | function | `kernel/vga_fb.c:4713` | `static int dock_label_px(const struct desktop_shortcut *sc)` |
| `dock_mag_counts` | function | `kernel/vga_fb.c:5004` | `void dock_mag_counts(int *level, unsigned long *paints)` |
| `dock_mag_dirty` | function | `kernel/vga_fb.c:4993` | `static int dock_mag_dirty(void)` |
| `dock_mag_level` | function | `kernel/vga_fb.c:4961` | `static int dock_mag_level(void)` |
| `dock_mag_track` | function | `kernel/vga_fb.c:4970` | `static void dock_mag_track(int hover, int mx)` |
| `dock_paint_backing` | function | `kernel/vga_fb.c:5065` | `static void dock_paint_backing(int x0, int y0, int dock_w, int dock_h, int with_shadow)` |
| `dock_paint_hover` | function | `kernel/vga_fb.c:5158` | `static void dock_paint_hover(int hover)` |
| `dock_paint_icon` | function | `kernel/vga_fb.c:5012` | `static void dock_paint_icon(int i, int hover, int size)` |
| `dock_paint_icons` | function | `kernel/vga_fb.c:5045` | `static void dock_paint_icons(int hover)` |
| `dock_pending_active` | function | `kernel/vga_fb.c:4943` | `int dock_pending_active(void)` |
| `draw_scrollbar` | function | `kernel/vga_fb.c:3376` | `static void draw_scrollbar(void)` |
| `draw_speaker_icon` | function | `kernel/vga_fb.c:3151` | `static void draw_speaker_icon(int x, int y, uint8_t color)` |
| `draw_title_win` | function | `kernel/vga_fb.c:3087` | `static void draw_title_win(int idx, int focused)` |
| `escapes` | function | `kernel/vga_fb.c:3542` | `* swallowing them here keeps the escapes (which the serial side needs)      * from printing as li...` |
| `fb_bytes_per_pixel` | function | `kernel/vga_fb.c:125` | `int fb_bytes_per_pixel(void)` |
| `fb_compose_begin` | function | `kernel/vga_fb.c:235` | `static int fb_compose_begin(void)` |
| `fb_compose_end` | function | `kernel/vga_fb.c:248` | `static void fb_compose_end(int owner)` |
| `fb_copy_bytes` | function | `kernel/vga_fb.c:159` | `static void fb_copy_bytes(volatile void *dst, const volatile void *src, unsigned long n)` |
| `fb_fill_run` | function | `kernel/vga_fb.c:1970` | `static void fb_fill_run(int x, int y, int n, unsigned long px)` |
| `fb_fill_u32` | function | `kernel/vga_fb.c:177` | `static void fb_fill_u32(volatile void *dst, unsigned int v, unsigned long n)` |
| `fb_frame_bytes` | function | `kernel/vga_fb.c:191` | `static unsigned long fb_frame_bytes(void)` |
| `fb_glyph` | function | `kernel/vga_fb.c:2058` | `static const uint8_t *fb_glyph(unsigned char c)` |
| `fb_pack_idx` | function | `kernel/vga_fb.c:1853` | `static unsigned long fb_pack_idx(unsigned idx)` |
| `fb_present_shadow` | function | `kernel/vga_fb.c:221` | `static void fb_present_shadow(void)` |
| `fb_read_packed` | function | `kernel/vga_fb.c:1889` | `unsigned long fb_read_packed(int x, int y)` |
| `fb_read_row_packed` | function | `kernel/vga_fb.c:1948` | `void fb_read_row_packed(int x, int y, unsigned int *dst, int n)` |
| `fb_shadow_ready` | function | `kernel/vga_fb.c:197` | `static int fb_shadow_ready(void)` |
| `fb_write_packed` | function | `kernel/vga_fb.c:1869` | `void fb_write_packed(int x, int y, unsigned long rgb)` |
| `fb_write_row_packed` | function | `kernel/vga_fb.c:1918` | `void fb_write_row_packed(int x, int y, const unsigned int *src, int n)` |
| `first` | function | `kernel/vga_fb.c:514` | `* screen ever showing it whole first (the old flash-then-melt). */ static unsigned int *fx_start_...` |
| `flag` | function | `kernel/vga_fb.c:608` | `* is the minimized flag (the program keeps running, nothing composites);` |
| `from` | function | `kernel/vga_fb.c:4119` | `* leaving returns to the view it came from (floating or tiled). Returns  * 0 on success, -1 witho...` |
| `fx_plan_burn` | function | `kernel/vga_fb.c:496` | `static void fx_plan_burn(int x, int y, int w, int h)` |
| `fx_plan_genie` | function | `kernel/vga_fb.c:502` | `static void fx_plan_genie(int x, int y, int w, int h, int tx, int ty, int reverse)` |
| `gfx_animate` | function | `kernel/vga_fb.c:4021` | `static void gfx_animate(const wm_gfxview_rect_t *from, const wm_gfxview_rect_t *to,              ...` |
| `gfx_compose` | function | `kernel/vga_fb.c:2940` | `static void gfx_compose(const volatile uint8_t *src, int kind, int sw, int sh,                   ...` |
| `gfx_covers_screen` | function | `kernel/vga_fb.c:656` | `static int gfx_covers_screen(void)` |
| `gfx_cursor_follow_idle` | function | `kernel/vga_fb.c:3024` | `static void gfx_cursor_follow_idle(void)` |
| `gfx_drop_focus` | function | `kernel/vga_fb.c:4108` | `static void gfx_drop_focus(int source)` |
| `gfx_float_frame` | function | `kernel/vga_fb.c:834` | `static int gfx_float_frame(wm_gfxview_rect_t *out)` |
| `gfx_keep_save` | function | `kernel/vga_fb.c:662` | `static void gfx_keep_save(const volatile uint8_t *src, int kind, int sw, int sh)` |
| `gfx_letterbox` | function | `kernel/vga_fb.c:2907` | `static void gfx_letterbox(const wm_gfxview_t *v)` |
| `gfx_present` | function | `kernel/vga_fb.c:3008` | `static void gfx_present(const volatile uint8_t *bb, int kind, int sw, int sh)` |
| `gfx_prog_icon` | function | `kernel/vga_fb.c:737` | `static const uint8_t *gfx_prog_icon(void)` |
| `gfx_snap` | function | `kernel/vga_fb.c:4274` | `static void gfx_snap(int zone)` |
| `gfx_task_icon` | function | `kernel/vga_fb.c:5190` | `static const uint8_t *gfx_task_icon(void)` |
| `gfx_taskbar_rect` | function | `kernel/vga_fb.c:4071` | `static void gfx_taskbar_rect(wm_gfxview_rect_t *r)` |
| `gfx_title` | function | `kernel/vga_fb.c:2926` | `static void gfx_title(const wm_gfxview_t *v)` |
| `gfx_transition` | function | `kernel/vga_fb.c:1059` | `static void gfx_transition(const wm_gfxview_rect_t *from, int from_titled);` |
| `gfx_view_cfg` | function | `kernel/vga_fb.c:647` | `static wm_gfxview_config_t gfx_view_cfg(void)` |
| `gfx_view_for` | function | `kernel/vga_fb.c:808` | `static int gfx_view_for(int sw, int sh, wm_gfxview_t *v)` |
| `gfx_view_in_rect` | function | `kernel/vga_fb.c:4002` | `static void gfx_view_in_rect(const wm_gfxview_rect_t *r, int titled, wm_gfxview_t *v)` |
| `gfx_view_publish` | function | `kernel/vga_fb.c:820` | `static void gfx_view_publish(const wm_gfxview_t *v)` |
| `icon_decode` | function | `kernel/vga_fb.c:4651` | `static const uint8_t *icon_decode(const char *path)` |
| `icon_embedded` | function | `kernel/vga_fb.c:4631` | `static const uint8_t *icon_embedded(const char *name)` |
| `icon_embedded_rgba` | function | `kernel/vga_fb.c:4685` | `static const uint8_t *icon_embedded_rgba(const uint8_t *idx)` |
| `icon_nearest` | function | `kernel/vga_fb.c:4615` | `static int icon_nearest(int r, int g, int b)` |
| `jelly_advance` | function | `kernel/vga_fb.c:3853` | `static void jelly_advance(void)` |
| `jelly_arm` | function | `kernel/vga_fb.c:3727` | `static void jelly_arm(void)` |
| `jelly_begin` | function | `kernel/vga_fb.c:3675` | `static void jelly_begin(int kind, int gx, int gy)` |
| `jelly_cancel` | function | `kernel/vga_fb.c:3666` | `static void jelly_cancel(void)` |
| `jelly_kick` | function | `kernel/vga_fb.c:3710` | `static void jelly_kick(int mx, int my)` |
| `jelly_live` | function | `kernel/vga_fb.c:3719` | `static int jelly_live(void)` |
| `jelly_present` | function | `kernel/vga_fb.c:3818` | `static void jelly_present(void)` |
| `jelly_put_row` | function | `kernel/vga_fb.c:3763` | `static void jelly_put_row(int x, int y, const unsigned int *src, int n)` |
| `jelly_rect` | function | `kernel/vga_fb.c:3687` | `static int jelly_rect(int *x, int *y, int *w, int *h)` |
| `jelly_shadow_px` | function | `kernel/vga_fb.c:3753` | `static unsigned int jelly_shadow_px(int x, int y)` |
| `jelly_tick` | function | `kernel/vga_fb.c:3866` | `static void jelly_tick(int held)` |
| `jelly_try_present` | function | `kernel/vga_fb.c:3842` | `static int jelly_try_present(void)` |
| `jelly_warp_band` | function | `kernel/vga_fb.c:3785` | `static void jelly_warp_band(void)` |
| `letterbox` | function | `kernel/vga_fb.c:612` | `* present to repaint chrome plus letterbox (after a desktop redraw or a * view change);` |
| `lg_alloc` | function | `kernel/vga_fb.c:349` | `static void lg_alloc(void)` |
| `lg_get` | function | `kernel/vga_fb.c:321` | `static const char *lg_get(int i)` |

Next: [SYMBOLS_p11.md](SYMBOLS_p11.md)
