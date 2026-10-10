/* syscalls.c - Linux x86-64 syscall dispatcher and SYS_SPAWN.
 *
 * Extracted from kernel.c.  Contains ksyscall (trace wrapper),
 * ksyscall_dispatch (the ABI switch), the per-process fd views plus the
 * user-pointer validation, and k_syscall_spawn (the bridge between the
 * Linux ABI and the internal ELF loaders).
 *
 * Process-management handlers (clone, seccomp, nice, yield, getpid/tid,
 * fork/vfork/execve stubs, exit, wait4, kill) live in syscalls_proc.c
 * (declared in syscalls_proc.h); the tables below reference them.
 *
 * The asm trampoline (syscall_entry / syscall_kstack) lives in
 * arch/x86/syscall_entry.S; it defines the global symbols the boot
 * code installs into MSR_LSTAR.
 */

#include "kernel.h"
#include "net.h"
#include "bootdefs.h"
#include "minifs.h"
#include "ide.h"
#include "block.h"
#include "pcache.h"
#include "sched.h"
#include "vga_fb.h"
#include "pcspk.h"
#include "sb16.h"
#include "pcm2.h"
#include "rtc.h"
#include "lz4_kernel.h"
#include "drivers/kbd.h"
#include "arch/x86/hal_io.h"
#include "arch/x86/msr.h"
#include "zip.h"
#include "futex.h"
#include "batch.h"
#include "rcu.h"
#include "sync.h"
#include "percpu_rq.h"
#include "sanitize.h"
#include "driver.h"
#include "syscalls_proc.h"
#include "shell.h"
#include "ktime.h"
#include "randmix.h"
#include "proc_sec.h"
#include "tlb.h"

/* ---- Per-process file-descriptor views (open/read/write/close) -------- */

#define KFD_MAX 32

/* Root view for the shell and every pid without its own (pid 0, AP
 * idle): .bss-zeroed entries, never freed, so NULL proc->kfd and an
 * invalid current_pid degrade to the historical shared table. */
static kfd_view_t kfd_root;

/** Docstring: View owning the caller's fds: its own on isolated procs
 * and threads, the root on pid 0 and any pid without one. */
static kfd_view_t *kfd_view_current(void) {
    if (current_pid >= 1 && current_pid < MAX_PROCS
        && procs[current_pid].state != PROC_FREE
        && procs[current_pid].kfd)
        return procs[current_pid].kfd;
    return &kfd_root;
}

/** Docstring: Static root view (shell pid 0, pids without their own):
 * entries are the historical shared table, never freed. */
kfd_view_t *kfd_view_root(void) {
    return &kfd_root;
}

/* Guards g_brk/g_brk_limit/user_mmap_cur and the VMA trees against
 * concurrent brk/mmap/munmap syscalls from threads on different CPUs.
 * Lock order: sched_lock -> mm_lock (the scheduler takes mm_lock
 * inside sched_lock for the brk/mmap view switch; syscalls take
 * mm_lock alone).  Declared extern in the scheduler via sched.c. */
spinlock_t mm_lock = SPINLOCK_INIT;

/* Leaf lock for every view's membership plus KFILE refcounts (see the
 * KFILE contract in kernel.h). Every section is a few instructions:
 * scan, assign, clear, bump or drop. File IO itself always runs
 * outside it with a held reference instead, so a close racing a
 * read drops the view slot but never frees under the reader, and
 * two racing opens can never claim the same slot twice. */
spinlock_t fd_lock = SPINLOCK_INIT;

KFILE *kfd_get(int fd) {
    irqflags_t flags;
    KFILE *f = 0;
    kfd_view_t *v = kfd_view_current();
    spin_lock_irqsave(&fd_lock, &flags);
    if (fd >= 0 && fd < KFD_MAX && v->f[fd]) {
        f = v->f[fd];
        f->ref++;
    }
    spin_unlock_irqrestore(&fd_lock, flags);
    return f;
}

void kfd_put(KFILE *f) {
    irqflags_t flags;
    int drop = 0;
    if (!f) return;
    spin_lock_irqsave(&fd_lock, &flags);
    f->ref--;
    if (f->ref <= 0) drop = 1;
    spin_unlock_irqrestore(&fd_lock, flags);
    if (drop) kfclose(f);
}

/** Docstring: Count live entries in a view (fd accounting source). */
static int kfd_view_count(kfd_view_t *v) {
    int i, n = 0;
    if (!v) return 0;
    for (i = 0; i < KFD_MAX; i++) if (v->f[i]) n++;
    return n;
}

/** Docstring: Share the caller's view with a new thread (CLONE_FILES /
 * CLONE_VM): one view refcount bump, entries untouched. The child must
 * be unpublished (PROC_SWITCHING) so no other CPU can claim it mid-way. */
void kfd_view_share(proc_t *child) {
    irqflags_t flags;
    kfd_view_t *v = kfd_view_current();
    spin_lock_irqsave(&fd_lock, &flags);
    if (v != &kfd_root) v->ref++;
    spin_unlock_irqrestore(&fd_lock, flags);
    child->kfd = (v == &kfd_root) ? 0 : v;
    child->open_files = kfd_view_count(v);
}

/** Docstring: Copy a parent's view for an isolated child (fork, spawn):
 * a fresh heap view with one KFILE ref bump per live entry, so either
 * side closing never drops the other's handle. A NULL parent (or one
 * without its own view) copies the root. Returns 0 on OOM with the
 * child untouched (caller refuses fail-closed). */
int kfd_view_copy(proc_t *child, proc_t *parent) {
    irqflags_t flags;
    kfd_view_t *v = kfd_view_root();
    kfd_view_t *nv;
    int i;
    if (parent && parent->kfd) v = parent->kfd;
    nv = (kfd_view_t *)kmalloc(sizeof(kfd_view_t));
    if (!nv) return 0;
    for (i = 0; i < KFD_MAX; i++) nv->f[i] = 0;
    nv->cloexec = 0;
    nv->ref = 1;
    spin_lock_irqsave(&fd_lock, &flags);
    for (i = 0; i < KFD_MAX; i++) {
        nv->f[i] = v->f[i];
        if (nv->f[i]) nv->f[i]->ref++;
    }
    nv->cloexec = v->cloexec;
    spin_unlock_irqrestore(&fd_lock, flags);
    child->kfd = nv;
    child->open_files = kfd_view_count(nv);
    return 1;
}

/** Docstring: Release a reaped process's view: drop one view ref and,
 * at zero, one KFILE ref per live entry (closing what the last owner
 * held) plus the view itself. The root view is never freed. Idempotent
 * on NULL (already released or never owned). */
void kfd_view_release(proc_t *p) {
    irqflags_t flags;
    kfd_view_t *v;
    KFILE *drop[KFD_MAX];
    int i, ndrop = 0, free_view = 0;
    if (!p || !p->kfd) return;
    v = p->kfd;
    p->kfd = 0;
    p->open_files = 0;
    spin_lock_irqsave(&fd_lock, &flags);
    v->ref--;
    if (v->ref <= 0 && v != &kfd_root) {
        free_view = 1;
        for (i = 0; i < KFD_MAX; i++) {
            if (v->f[i]) {
                v->f[i]->ref--;
                if (v->f[i]->ref <= 0 && ndrop < KFD_MAX)
                    drop[ndrop++] = v->f[i];
                v->f[i] = 0;
            }
        }
    }
    spin_unlock_irqrestore(&fd_lock, flags);
    for (i = 0; i < ndrop; i++) kfclose(drop[i]);
    if (free_view) kfree(v);
}

/** Docstring: Close every CLOEXEC fd in the caller's own view (execve:
 * the image is replaced, marked descriptors must not survive). Runs on
 * the live view entries with the same ref discipline as close. */
void kfd_view_cloexec(void) {
    irqflags_t flags;
    kfd_view_t *v = kfd_view_current();
    KFILE *drop[KFD_MAX];
    unsigned mask;
    int i, ndrop = 0;
    proc_t *cp = (current_pid >= 0 && current_pid < MAX_PROCS)
        ? &procs[current_pid] : 0;
    spin_lock_irqsave(&fd_lock, &flags);
    mask = v->cloexec;
    v->cloexec = 0;
    for (i = 0; i < KFD_MAX && mask; i++) {
        if ((mask & (1u << (unsigned)i)) && v->f[i]) {
            KFILE *f = v->f[i];
            v->f[i] = 0;
            f->ref--;
            if (f->ref <= 0 && ndrop < KFD_MAX) drop[ndrop++] = f;
            if (cp && cp->open_files > 0) cp->open_files--;
        }
        mask &= ~(1u << (unsigned)i);
    }
    spin_unlock_irqrestore(&fd_lock, flags);
    for (i = 0; i < ndrop; i++) kfclose(drop[i]);
}

/* ---- MiniOS custom syscall table (200-299) --------------------------------
 *
 * Each entry is a handler function for a MiniOS custom syscall.  The table
 * is indexed by (syscall_number - 200).  New syscalls are added by:
 *   1. Adding a MINIOS_SYS_* constant to progs/minios_abi.h
 *   2. Implementing a static long sys_*(long a1, ..., long a6) function here
 *   3. Adding an entry to minios_syscall_table[]
 *
 * The Linux ABI syscalls (0-199) live in linux_syscall_table[] below.
 * Numbers >= 200 that overlap real Linux ABIs (openat, exit_group,
 * newfstatat, ...) stay as switch fall-throughs after both tables, as
 * do out-of-range numbers and the default ENOSYS path. */

typedef long (*minios_syscall_fn_t)(long a1, long a2, long a3,
                                    long a4, long a5, long a6);

typedef struct {
    minios_syscall_fn_t fn;
    const char         *name;
} minios_syscall_entry_t;

#define MINIOS_SYSCALL_BASE  200
#define MINIOS_SYSCALL_COUNT 128

static int k_syscall_spawn(const char *path, const char *redirect,
                             int child_argc, const char **child_argv);

/* wall_us_now: RTC-anchored wall clock in microseconds (Phase 0.2/0.3).
 * The RTC gives whole seconds; the fraction is the free-running ktime_us
 * rebased at every RTC second edge, so successive reads order correctly
 * across the edge. Shared by gettimeofday (96), clock_gettime (228) and
 * the shell `clock` builtin: one source, never three disagreeing clocks.
 * On RTC failure the base stays 0 and time reads as small uptime-like
 * values; callers that need an epoch treat 0 as "no clock". */
unsigned long wall_us_now(void) {
    static unsigned long base_sec;
    static unsigned long base_ktime;
    unsigned long sec = 0, now;
    rtc_wall_seconds(&sec);
    now = ktime_us();
    if (sec != base_sec) { base_sec = sec; base_ktime = now; }
    return wall_us_from_parts(base_sec, base_ktime, now);
}

static long sys_minios_dns(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    SANITIZE_STR(a1, 255);
    return net_sys_dns(a1);
}
static long sys_minios_tls_retired(long a1, long a2, long a3, long a4, long a5, long a6) {
    /* Retired kernel-TLS number 203: the engine left ring 0, 202 now
     * serves Linux futex and 201 Linux time, so this always answers
     * -ENOSYS.
     * Fossil miniGCC binaries still trap them and fail closed. */
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return -38;
}
/* time (201): the retired kernel-TLS handshake number now serves Linux
 * time(2), exactly as 202 serves futex (ADR-0014 record in
 * tools/check_abi_numbers.py). Static glibc calls it when there is no vDSO;
 * -ENOSYS made OpenSSL and libcurl check certificate lifetimes against
 * (time_t)-1. Answers RTC-anchored wall seconds, stored at a1 when set. */
static long sys_linux_time(long a1, long a2, long a3, long a4, long a5, long a6) {
    long t = (long)(wall_us_now() / 1000000UL);
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    if (a1) {
        SANITIZE_RANGE(a1, sizeof(long));
        *(long *)a1 = t;
    }
    return t;
}
static long sys_linux_futex(long a1, long a2, long a3, long a4, long a5, long a6) {
    /* Linux futex(2): __NR_futex is 202, the retired MINIOS_SYS_TLS_SEND
     * number, so it is served here rather than in the Linux switch below
     * (the MiniOS table is consulted first for 200..327 and would win).
     * glibc's NPTL/malloc/resolver issue raw futex traps — e.g. a
     * WAKE|PRIVATE inside getaddrinfo, which is what `freedom google.cl`
     * needs — and answering -ENOSYS aborts the process ("The futex
     * facility returned an unexpected error code", exit 134). WAIT/WAKE
     * and their BITSET forms run on kernel/futex.c; a mismatch is -EAGAIN
     * like Linux (the MiniOS 226/227 pair keeps its own FUTEX_NOMATCH
     * convention untouched). Every other op (REQUEUE, WAKE_OP, PI...) is
     * -ENOSYS. */
    unsigned long uaddr = (unsigned long)a1;
    int cmd = futex_linux_cmd(a2);
    long n;
    (void)a5;
    if (cmd < 0) return -38;
    SANITIZE_RANGE(uaddr, 4);
    if ((cmd == LINUX_FUTEX_WAIT_BITSET || cmd == LINUX_FUTEX_WAKE_BITSET) &&
        (unsigned long)(unsigned int)a6 != LINUX_FUTEX_BITSET_MATCH_ANY)
        return -22;
    if (cmd == LINUX_FUTEX_WAKE || cmd == LINUX_FUTEX_WAKE_BITSET) {
        n = a3;
        if (n < 0) n = 0;
        if (n > FUTEX_WAKE_ALL) n = FUTEX_WAKE_ALL;
        return futex_wake(uaddr, (int)n);
    }
    if (a4) {
        /* Timed wait (docs/spec/smp-sched.md): past the deadline it is
         * -ETIMEDOUT; before it, one yield and a spurious-wakeup 0 that the
         * caller re-checks. No timer queue is needed and no waiter can
         * oversleep its deadline by more than one scheduling round. */
        const long *ts = (const long *)a4;
        unsigned long now;
        long left;
        SANITIZE_RANGE(ts, 2 * sizeof(long));
        now = (a2 & LINUX_FUTEX_CLOCK_REALTIME) ? wall_us_now() : ktime_us();
        left = futex_timeout_remaining_us(cmd, ts[0], ts[1], now);
        if (left == FUTEX_TIMEOUT_INVALID) return -22;
        if (*(volatile int *)uaddr != (int)a3) return -11;
        if (left <= 0) return -110; /* ETIMEDOUT */
        yield();
        return 0;
    }
    n = futex_wait(uaddr, (int)a3);
    if (n == FUTEX_NOMATCH) return -11; /* EAGAIN */
    if (n == FUTEX_NOPROC) return -22;  /* EINVAL */
    return n; /* FUTEX_OK == 0 */
}
static long sys_minios_time(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return (long)ktime_ms();
}
static long sys_minios_kbd(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    (void)a1;
    /* Focus-owned PS/2: an unfocused reader touches no hardware, so a
     * background game and the shell never split the scancode stream. A
     * legacy foreground program owns everything (its shell is blocked). */
    if (!vga_fb_ps2_owner(current_pid)) return -1;
    if (kbd_raw_mode_get()) {
        if (!kbd_raw_empty()) return kbd_raw_pop();
        if (!kbd_available()) return -1;
        unsigned char sc;
        sc = hal_inb(HAL_PS2_DATA);
        /* WM-first: Alt+Tab / Super+Tab / Super+arrows / Alt+close work
         * while a game owns the keyboard; consumed bytes never reach it. */
        if (kbd_sys_raw_filter(sc)) return -1;
        return (long)sc;
    }
    if (kbd_q_empty()) return -1;
    return kbd_q_pop();
}
static long sys_minios_palette(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    unsigned char *pal = (unsigned char *)a1;
    unsigned char tmp[768];
    int i;
    SANITIZE_RANGE(a1, 768);
    /* Copy in once: the caller must not mutate the palette between the
     * range check and the DAC/palette update. */
    for (i = 0; i < 768; i++) tmp[i] = pal[i];
    vga_fb_set_gfx_palette(tmp);
    return 0;
}
static long sys_minios_kbd_raw(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    kbd_raw_mode_set((int)a1);
    kbd_flush_all();
    return 0;
}
static long sys_minios_vga_mode(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    vga_mode_set((int)a1);
    if (a1) vga_gfx_ran_set(1);
    vga_fb_set_gfx_mode((int)a1);
    return 0;
}
static long sys_minios_pcspk_init(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    pcspk_init(); return 0;
}
static long sys_minios_pcspk_tone(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    pcspk_tone((unsigned)a1); return 0;
}
/* Attribute a composited frame to its program for the taskbar button: a
 * background job frames as itself (procs name), a legacy foreground run as
 * the launch name the shell recorded. Last frame wins, same as the pixels. */
static void gfx_note_compositor(void) {
    int pid = current_pid;
    if (user_program_active) return;
    if (pid > 0 && pid < MAX_PROCS && procs[pid].state != PROC_FREE &&
        procs[pid].name[0])
        vga_fb_set_gfx_program(procs[pid].name);
}
static long sys_minios_doom_frame(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    gfx_note_compositor();
    vga_fb_blit_gfx_window(); return 0;
}
/* Graphics window scale request (a1): 0 native, 1 2x nearest-neighbour
 * zoom for the 320x200 game window, 2 true fullscreen (aspect-fit to the
 * whole display, the WM view contract in wm_gfxview.h), 3 leave
 * fullscreen. Scalar only, no pointer to validate; anything else is
 * EINVAL, and 2/3 without a graphics program are EINVAL too, so an old
 * caller probing the call keeps its windowed behaviour. */
static long sys_minios_gfx_zoom(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    extern int gfx_zoom_2x;
    if (a1 == MINIOS_GFX_ZOOM_FULLSCREEN || a1 == MINIOS_GFX_ZOOM_WINDOWED)
        return vga_fb_gfx_set_fullscreen(a1 == MINIOS_GFX_ZOOM_FULLSCREEN) ? -22 : 0;
    if (a1 < MINIOS_GFX_ZOOM_NATIVE || a1 > MINIOS_GFX_ZOOM_2X) return -22;
    gfx_zoom_2x = (int)a1;
    return 0;
}
static long sys_minios_rtc(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    int *hp = (int *)(unsigned long)a1;
    int *mp = (int *)(unsigned long)a2;
    int *sp = (int *)(unsigned long)a3;
    SANITIZE_RANGE(a1, sizeof(int));
    SANITIZE_RANGE(a2, sizeof(int));
    SANITIZE_RANGE(a3, sizeof(int));
    int h, m, s;
    if (!rtc_read_tod(&h, &m, &s)) return -5;
    *hp = h; *mp = m; *sp = s;
    return 0;
}
static long sys_minios_fb_info(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a5; (void)a6;
    int *wp = (int *)(unsigned long)a1;
    int *hp = (int *)(unsigned long)a2;
    int *pp = (int *)(unsigned long)a3;
    SANITIZE_RANGE(a1, sizeof(int));
    SANITIZE_RANGE(a2, sizeof(int));
    SANITIZE_RANGE(a3, sizeof(int));
    *wp = fb_width; *hp = fb_height; *pp = fb_pitch;
    /* Optional 4th out-word: 1 when the NK RGB back-buffer (NK_RGB_ADDR,
     * presented with GFX_PRESENT id 2) is mapped. Old kernels ignore a4
     * and leave the caller's word untouched, so ring 3 pre-zeroes it and
     * treats nonzero as available: full backwards compatibility. */
    if (a4) {
        int *rp = (int *)(unsigned long)a4;
        SANITIZE_RANGE(a4, sizeof(int));
        *rp = 1;
    }
    return 0;
}
static long sys_minios_pcspk_vol(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    int v = (int)a1;
    if (v < 0) return (long)pcspk_get_volume();
    if (v > 100) v = 100;
    pcspk_set_volume((unsigned)v);
    return (long)pcspk_get_volume();
}
/* MINFO sleep support: a timed park for ring-3 monitors, so a refresh
 * loop does not burn its whole quantum polling the clock (which would
 * pin the very CPU meter it draws at 100%). The sleeper arms a flag
 * and blocks on minfo_sleep_q; the 100 Hz audio tick listener wakes
 * the queue every tick and each sleeper re-checks its own deadline,
 * so concurrent sleepers with different deadlines and spurious wakes
 * are all harmless. The flag is set once and never cleared: after the
 * first sleep every tick pays one empty-queue wake_up_all, which
 * returns on the head check. Queue and tick registration happen at
 * boot (minfo_sleep_init from sched_init); without them sel 6 fails
 * closed with -EIO instead of hanging. Same block/wake discipline as
 * futex_wait (PROC_BLOCKED + schedule, woken to PROC_READY). */
static wait_queue_t minfo_sleep_q;
static volatile int minfo_sleep_armed;
static int minfo_sleep_ready;

void minfo_sleep_init(int tick_ok) {
    wq_init(&minfo_sleep_q);
    minfo_sleep_ready = tick_ok ? 1 : 0;
}

void minfo_tick_wake(void *ctx) {
    (void)ctx;
    if (minfo_sleep_armed)
        wake_up_all(&minfo_sleep_q);
}

/* MINFO (251): multiplexed kernel-statistics read for ring-3 monitors.
 * a1 selects, a2/a3 take two long out-words (two only, so every call
 * fits the three-argument inline-syscall form miniGCC supports):
 * 0 = heap used/free KB, 1 = ramdisk used/cap KB, 2 = MiniFS
 * free/total blocks (0/0 when unmounted), 3 = cpu total/idle 100 Hz
 * ticks, 4 = cpu count/uptime seconds, 5 = clear the caller's terminal
 * view (same as the `clear` builtin). Anything else is -EINVAL. Each
 * out-word is range-checked before it is written, so a bad pointer is
 * -EFAULT with nothing stored. Snapshot discipline like schedtop:
 * counters are read without locks (single aligned words) and values
 * may skew by one tick, never corrupt. */
static long sys_minios_minfo(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    if (a1 == 0) {
        unsigned long *used = (unsigned long *)(unsigned long)a2;
        unsigned long *freeb = (unsigned long *)(unsigned long)a3;
        unsigned long hu = 0, hf = 0, ha = 0;
        SANITIZE_RANGE(a2, sizeof(unsigned long));
        SANITIZE_RANGE(a3, sizeof(unsigned long));
        dlmalloc_usage(&hu, &hf, &ha);
        (void)ha;
        *used = hu / 1024;
        *freeb = hf / 1024;
        return 0;
    }
    if (a1 == 1) {
        unsigned long *rd_used = (unsigned long *)(unsigned long)a2;
        unsigned long *rd_cap = (unsigned long *)(unsigned long)a3;
        unsigned ru = 0, rc = 0, rm = 0;
        SANITIZE_RANGE(a2, sizeof(unsigned long));
        SANITIZE_RANGE(a3, sizeof(unsigned long));
        ramdisk_usage(&ru, &rc, &rm);
        (void)rm;
        *rd_used = ru / 1024;
        *rd_cap = rc / 1024;
        return 0;
    }
    if (a1 == 2) {
        unsigned long *fs_free = (unsigned long *)(unsigned long)a2;
        unsigned long *fs_total = (unsigned long *)(unsigned long)a3;
        SANITIZE_RANGE(a2, sizeof(unsigned long));
        SANITIZE_RANGE(a3, sizeof(unsigned long));
        *fs_free = 0;
        *fs_total = 0;
        if (minifs_is_mounted()) {
            unsigned int fb = 0, tb = 0, fi = 0, ti = 0;
            minifs_usage(&fb, &tb, &fi, &ti);
            (void)fi; (void)ti;
            *fs_free = fb;
            *fs_total = tb;
        }
        return 0;
    }
    if (a1 == 3) {
        unsigned long *ticks = (unsigned long *)(unsigned long)a2;
        unsigned long *idle = (unsigned long *)(unsigned long)a3;
        unsigned long id = 0;
        int c;
        SANITIZE_RANGE(a2, sizeof(unsigned long));
        SANITIZE_RANGE(a3, sizeof(unsigned long));
        for (c = 0; c < cpu_count && c < MAX_CPUS; c++)
            id += cpu_idle_ticks[c];
        *ticks = (unsigned long)sys_ticks;
        *idle = id;
        return 0;
    }
    if (a1 == 4) {
        unsigned long *count = (unsigned long *)(unsigned long)a2;
        unsigned long *up = (unsigned long *)(unsigned long)a3;
        SANITIZE_RANGE(a2, sizeof(unsigned long));
        SANITIZE_RANGE(a3, sizeof(unsigned long));
        *count = (unsigned long)cpu_count;
        *up = (unsigned long)(sys_ticks / 100);
        return 0;
    }
    if (a1 == 5) {
        if (vga_fb_active)
            term_clear();
        else
            vga_clear();
        return 0;
    }
    if (a1 == 6) {
        long ms = a2;
        unsigned long until;
        if (!minfo_sleep_ready) return -5;
        if (ms < 0) ms = 0;
        if (ms > 60000) ms = 60000;
        if (ms == 0) return 0;
        until = (unsigned long)sys_ticks + (unsigned long)(ms / 10) + 1;
        minfo_sleep_armed = 1;
        while ((long)((unsigned long)sys_ticks - until) < 0)
            sleep_on(&minfo_sleep_q);
        return 0;
    }
    return -22;
}
static long sys_minios_spawn(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a5; (void)a6;
    const char *path = (const char *)a1;
    SANITIZE_STR(path, RAMDISK_FNAME_LEN);
    /* SPAWN saves and replaces the shared user-window view (brk/mmap
     * cursors, VMA trees, fd table): it is a BSP-only operation.  A
     * thread running on an AP shares its address space with siblings,
     * so replacing it would corrupt them; fail closed instead. */
    if (!this_cpu()->is_bsp) return EFAULT;
    return k_syscall_spawn(path, (const char *)a2, (int)a3, (const char **)a4);
}
static long sys_minios_lz4_compress(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a5; (void)a6;
    char *src = (char *)a1; char *dst = (char *)a3;
    int src_len = (int)a2; int dst_cap = (int)a4;
    if (src_len <= 0 || dst_cap <= 4) return 0;
    SANITIZE_RANGE(src, (unsigned long)src_len);
    SANITIZE_RANGE(dst, (unsigned long)dst_cap);
    int ret = LZ4_compress_default(src, dst + 4, src_len, dst_cap - 4);
    if (ret <= 0 || ret >= src_len) return 0;
    dst[0] = (char)(src_len & 255); dst[1] = (char)((src_len >> 8) & 255);
    dst[2] = (char)((src_len >> 16) & 255); dst[3] = (char)((src_len >> 24) & 255);
    return ret + 4;
}
static long sys_minios_lz4_decompress(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a5; (void)a6;
    char *src = (char *)a1; char *dst = (char *)a3;
    int src_len = (int)a2; int dst_cap = (int)a4;
    if (src_len <= 4) return 0;
    SANITIZE_RANGE(src, (unsigned long)src_len);
    unsigned int orig = (unsigned int)((unsigned char)src[0] | ((unsigned char)src[1] << 8) |
                                       ((unsigned char)src[2] << 16) | ((unsigned char)src[3] << 24));
    if (orig > (unsigned int)dst_cap) return 0;
    if (dst_cap > 0) { SANITIZE_RANGE(dst, (unsigned long)dst_cap); }
    int ret = LZ4_decompress_safe(src + 4, dst, src_len - 4, dst_cap);
    if (ret < 0 || (unsigned int)ret != orig) return 0;
    return ret;
}
static long sys_minios_mouse(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    int *m = (int *)(unsigned long)a1;
    int mx;
    int my;
    int mb;
    int mw;
    irqflags_t flags;
    SANITIZE_RANGE(a1, 4 * sizeof(int));
    if (!vga_fb_ps2_owner(current_pid)) return -1;
    flags = spin_save_irq();
    mx = mouse_state.x;
    my = mouse_state.y;
    mb = mouse_state.buttons;
    mw = mouse_state.wheel;
    mouse_state.wheel = 0;
    spin_restore_irq(flags);
    vga_fb_gfx_map_mouse(&mx, &my);
    m[0] = mx;
    m[1] = my;
    m[2] = mb;
    m[3] = mw;
    return 0;
}
static long sys_minios_nk_frame(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    if (a1)
        SANITIZE_RANGE(a1, 2 * sizeof(int));
    gfx_note_compositor();
    vga_fb_blit_nk_window();
    if (a1) {
        int *o = (int *)(unsigned long)a1;
        vga_fb_gfx_origin(&o[0], &o[1]);
    }
    return 0;
}
/** Docstring: Resolve the registered PCM sink, 0 when absent. */
static device_t *sb16_audio_device(void)
{
    device_t *dev = device_find("sb160");
    if (!dev || !dev->audio || !dev->audio->pcm_submit) return 0;
    return dev;
}
static long sys_minios_sb16_open(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    device_t *dev = sb16_audio_device();
    if (!dev) return 0;
    if (a1) {
        if (dev->audio->pcm_open) dev->audio->pcm_open(dev);
    } else {
        if (dev->audio->pcm_close) dev->audio->pcm_close(dev);
    }
    if (dev->audio->present) return dev->audio->present(dev) ? 1 : 0;
    return 0;
}
static long sys_minios_sb16_submit(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    const unsigned char *pcm = (const unsigned char *)a1;
    long len = a2;
    device_t *dev;
    SANITIZE_LEN_NEG(len);
    SANITIZE_RANGE(a1, len);
    dev = sb16_audio_device();
    if (!dev) return -1;
    return dev->audio->pcm_submit(dev, pcm, (unsigned)len);
}
static long sys_minios_gfx_title(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    const char *t = (const char *)(unsigned long)a1;
    if (!t) return EFAULT;
    SANITIZE_STR(t, 31);
    extern const char *gfx_win_title;
    static char title_buf[32];
    int i;
    for (i = 0; i < 31 && ((const char *)t)[i]; i++)
        title_buf[i] = ((const char *)t)[i];
    title_buf[i] = 0;
    gfx_win_title = title_buf;
    return 0;
}
static long sys_minios_sb16_pump(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    sb16_pump(); return 0;
}
static long sys_minios_sb16_stream_open(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return sb16_stream_open();
}
static long sys_minios_sb16_stream_close(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    sb16_stream_close((int)a1); return 0;
}
static long sys_minios_sb16_stream_submit(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    const unsigned char *pcm = (const unsigned char *)a2;
    long len = a3;
    SANITIZE_LEN_NEG(len);
    SANITIZE_RANGE(a2, len);
    return sb16_stream_submit((int)a1, pcm, (unsigned)len);
}
/* Low-latency PCM path (pcm2, syscalls 246-248): OPEN takes flags,
 * WRITE returns bytes taken (blocking unless NONBLOCK), CLOSE
 * releases. Pointer/length validated at the boundary like every
 * other dispatcher case; the driver copies in fragment chunks and
 * blocks with the scheduler, never with a spin. */
static long sys_minios_pcm2_open(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    if (a1 < 0) return PCM2_ERR_INVAL;
    return pcm2_open((unsigned)a1, current_pid);
}
static long sys_minios_pcm2_write(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    const unsigned char *pcm = (const unsigned char *)a1;
    long len = a2;
    SANITIZE_LEN_NEG(len);
    SANITIZE_RANGE(a1, len);
    return pcm2_write(pcm, (unsigned)len, current_pid);
}
static long sys_minios_pcm2_close(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    pcm2_close(current_pid);
    return 0;
}
/* Shared text clipboard (syscalls 249-250): SET copies len bytes in
 * (refused past 4096, never truncated), GET copies out up to cap
 * (refused when empty or undersize, never a partial paste). All
 * pointers validated at the boundary; kernel addresses fail with
 * -EFAULT before entry. */
static long sys_minios_clip_set(long a1, long a2, long a3, long a4, long a5, long a6) {
    const char *data = (const char *)a1;
    long len = a2;
    (void)a3; (void)a4; (void)a5; (void)a6;
    SANITIZE_LEN_NEG(len);
    if (len == 0) { clip_clear(); return 0; }
    SANITIZE_RANGE(a1, len);
    if ((unsigned long)len > 4096u) return -22;
    return clip_set(data, (unsigned long)len);
}
static long sys_minios_clip_get(long a1, long a2, long a3, long a4, long a5, long a6) {
    char *out = (char *)a1;
    long cap = a2;
    char *kbuf;
    int n;
    (void)a3; (void)a4; (void)a5; (void)a6;
    SANITIZE_LEN_NEG(cap);
    if (cap == 0) return -22;
    SANITIZE_RANGE(a1, cap);
    kbuf = kmalloc((unsigned)cap);
    if (!kbuf) return -12;
    n = clip_get(kbuf, (unsigned long)cap);
    if (n >= 0) kmemcpy(out, kbuf, (unsigned long)n);
    kfree(kbuf);
    return n;
}
static long sys_minios_sb16_stream_vol(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    sb16_stream_volume((int)a1, (unsigned char)a2); return 0;
}

/* clone(flags, newsp) - create a thread or process.
 * CLONE_VM: share address space (same CR3).
 * CLONE_FILES: share fd table.
 * Returns child PID to parent, 0 to child. */
/* Process-management handlers (clone, seccomp, nice, yield, getpid/tid,
 * fork/vfork/execve stubs, exit, wait4, kill) live in syscalls_proc.c;
 * the tables below reference them via syscalls_proc.h. */

static long sys_minios_futex_wait(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    SANITIZE_RANGE(a1, 4);
    return futex_wait((unsigned long)a1, (int)a2);
}

static long sys_minios_futex_wake(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    long n = a2;
    SANITIZE_RANGE(a1, 4);
    if (n < 0) n = 0;
    if (n > FUTEX_WAKE_ALL) n = FUTEX_WAKE_ALL;
    return futex_wake((unsigned long)a1, (int)n);
}

static long batch_kdispatch(uint32_t opcode) {
    if (opcode == BATCH_OP_NOP) return 0;
    if (opcode == BATCH_OP_YIELD) {
        yield();
        return 0;
    }
    if (opcode == BATCH_OP_TIME) return (long)ktime_ms();
    if (opcode == BATCH_OP_GETPID) return (long)current_pid;
    return BATCH_ERR_OPCODE;
}

/* Generic window present (boyscout fix for app-specific syscalls):
 * a1 = buffer id (0 = 320x200 game buffer, 1 = 800x360 indexed NK buffer,
 *      2 = 800x360 RGB NK buffer at NK_RGB_ADDR),
 * a2 = optional user int[2] for the content origin (NK paths only).
 * DOOM_FRAME (211) and NK_FRAME (220) stay as compat aliases. */
static long sys_minios_gfx_present(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    if (a1 == 1) {
        if (a2)
            SANITIZE_RANGE(a2, 2 * sizeof(int));
        gfx_note_compositor();
        vga_fb_blit_nk_window();
        if (a2) {
            int *o = (int *)(unsigned long)a2;
            vga_fb_gfx_origin(&o[0], &o[1]);
        }
        return 0;
    }
    if (a1 == MINIOS_GFX_BUF_NK_RGB) {
        if (a2)
            SANITIZE_RANGE(a2, 2 * sizeof(int));
        gfx_note_compositor();
        vga_fb_blit_nk_rgb_window();
        if (a2) {
            int *o = (int *)(unsigned long)a2;
            vga_fb_gfx_origin(&o[0], &o[1]);
        }
        return 0;
    }
    gfx_note_compositor();
    vga_fb_blit_gfx_window();
    return 0;
}
/* Raw keystroke read for fullscreen ring-3 programs (vedit): one byte
 * from the serial + PS/2 multiplexer with no line buffering, no echo and
 * no scrollback detour. a1 == 0 polls (-1 when idle, so user space can
 * bound its own escape-sequence timeout); otherwise blocks until a byte.
 * Bytes are the same CSI form both consoles carry, PS/2 included. */
static long sys_minios_getc_raw(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    if (!vga_fb_ps2_owner(current_pid)) return -1;
    if (current_pid == 0 || user_program_active || shell_fg_active) {
        if (a1 == 0) return (long)console_raw_try();
        return (long)console_raw_get();
    }
    if (a1 == 0) return (long)console_job_try();
    return (long)console_job_get();
}

static long sys_minios_submit_batch(long a1, long a2, long a3, long a4, long a5, long a6) {    batch_op_t kops[BATCH_MAX_OPS];
    long kresults[BATCH_MAX_OPS];
    int completed = 0;
    long r;
    int i;
    int count = (int)a3;
    (void)a4; (void)a5; (void)a6;
    if (count < 0 || count > BATCH_MAX_OPS) return BATCH_ERR_COUNT;
    if (count == 0) return BATCH_OK;
    SANITIZE_COPY_IN(kops, a1, count, sizeof(batch_op_t));
    SANITIZE_RANGE(a2, (unsigned long)count * sizeof(long));
    r = batch_exec(kops, kresults, count, &completed, batch_kdispatch);
    for (i = 0; i < completed; i++)
        ((long *)a2)[i] = kresults[i];
    if (r < 0) return r;
    return completed;
}

/* RLIMIT/cgroups-lite (240): a1 = op (SET/GET), a2 = resource
 * (AS/CPU/NOFILE), a3 = value for SET. Values are bytes, ticks, count;
 * 0 clears (unlimited). Only lowers... no: any non-negative value sets
 * (raising allowed; the threat model is cooperative containment, not
 * privilege). Returns the old value on SET, current on GET. */
static long sys_minios_rlimit(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    int pid = current_pid;
    proc_t *p;
    unsigned long v = (unsigned long)a3;
    if (pid < 0 || pid >= MAX_PROCS) return -3;
    p = &procs[pid];
    if (p->state == PROC_FREE) return -3;
    if (a2 == RLIM_AS) {
        long old = (long)p->rl_as_max;
        if (a1 == RLIM_OP_SET) p->rl_as_max = v;
        else if (a1 != RLIM_OP_GET) return -22;
        return old;
    }
    if (a2 == RLIM_CPU) {
        long old = (long)p->rl_cpu_max;
        if (a1 == RLIM_OP_SET) { p->rl_cpu_max = v; p->cpu_ticks = 0; p->cpu_kill_pending = 0; }
        else if (a1 != RLIM_OP_GET) return -22;
        return old;
    }
    if (a2 == RLIM_NOFILE) {
        long old = (long)p->rl_nofile_max;
        if (a1 == RLIM_OP_SET) {
            if (v > (unsigned long)KFD_MAX) return -22;
            p->rl_nofile_max = v;
        } else if (a1 != RLIM_OP_GET) return -22;
        return old;
    }
    return -22;
}

/** Docstring: unified directory listing for the ring-3 file browser.
 *
 * a1 = path, a2 = user buffer, a3 = buffer capacity. The buffer is
 * filled with NUL-separated entry names relative to the directory;
 * subdirectory names carry a trailing '/'. Returns the entry count, or
 * a negative errno on failure. Ramdisk entries win; MiniFS entries
 * merge underneath with exact-name dedupe. Truncation is safe: the
 * call stops before an entry that would not fit and returns the
 * entries that did fit. Paths resolve through fs_resolve, so '..'
 * cannot escape, and overlong names fail closed. */
static long sys_minios_dir_list(long a1, long a2, long a3, long a4, long a5, long a6) {
    char resolved[RAMDISK_FNAME_LEN];
    char dir[RAMDISK_FNAME_LEN];
    char *out;
    unsigned long cap;
    unsigned long used = 0;
    long count = 0;
    int i, n;
    irqflags_t flags;
    (void)a4; (void)a5; (void)a6;
    SANITIZE_STR(a1, RAMDISK_FNAME_LEN);
    if (a3 <= 0 || a3 > 65536) return -22;
    cap = (unsigned long)a3;
    SANITIZE_RANGE(a2, cap);
    if (!fs_resolve((const char *)a1, resolved, sizeof(resolved))) return -36;
    {
        unsigned len = (unsigned)kstrlen(resolved);
        if (len + 2 >= sizeof(dir)) return -36;
        kmemcpy(dir, resolved, len + 1);
        if (len > 0 && dir[len - 1] != '/') { dir[len] = '/'; dir[len + 1] = 0; len++; }
        else if (len == 0) { dir[0] = 0; len = 0; }
        if (!fs_dir_exists(len ? dir : "")) {
            if (len == 0) { }
            else return -2;
        }
    }
    out = (char *)a2;
    {
        unsigned plen;
        RDFile *files[RAMDISK_MAX_FILES];
        spin_lock_irqsave(&fs_lock, &flags);
        plen = (unsigned)kstrlen(dir);
        n = ramdisk_list(files, RAMDISK_MAX_FILES);
        for (i = 0; i < n; i++) {
            const char *nm = files[i]->name;
            unsigned long nl;
            const char *rel;
            const char *slash;
            unsigned long comp_len;
            int k, dup = 0;
            if (plen && kstrncmp(nm, dir, plen) != 0) continue;
            rel = nm + plen;
            if (!rel[0]) continue;
            slash = kstrchr(rel, '/');
            if (slash) comp_len = (unsigned long)(slash - rel) + 1;
            else comp_len = (unsigned long)kstrlen(rel);
            if (comp_len == 0 || comp_len >= RAMDISK_FNAME_LEN) continue;
            for (k = 0; k < (int)used; ) {
                unsigned long el = kstrlen(out + k) + 1;
                if (el == comp_len + 1 && kstrncmp(out + k, rel, comp_len) == 0) { dup = 1; break; }
                k += (int)el;
            }
            if (dup) continue;
            nl = comp_len + 1;
            if (used + nl > cap) break;
            kmemcpy(out + used, rel, comp_len);
            out[used + comp_len] = 0;
            used += nl;
            count++;
        }
    }
    if (minifs_is_mounted()) {
        char bare[RAMDISK_FNAME_LEN];
        unsigned dl = (unsigned)kstrlen(dir);
        int ino = MINIFS_ROOT_INODE;
        kmemcpy(bare, dir, dl + 1);
        while (dl > 0 && bare[dl - 1] == '/') bare[--dl] = 0;
        if (dl > 0) {
            int r = minifs_resolve_path(bare);
            MiniFSInode st;
            if (r < 0 || minifs_stat(r, &st) < 0 ||
                (st.mode & MINIFS_S_IFDIR) != MINIFS_S_IFDIR)
                ino = -1;
            else ino = r;
        }
        if (ino >= 0) {
            MiniFSDirEntry de;
            char mname[RAMDISK_FNAME_LEN];
            int idx = 0;
            while (minifs_dir_read(ino, idx, &de, mname) == 0) {
                MiniFSInode st;
                int isdir = 0;
                unsigned long ml, nl;
                int k, dup = 0;
                idx++;
                if (de.inode == 0 || !mname[0]) continue;
                if (minifs_stat(de.inode, &st) < 0) continue;
                isdir = ((st.mode & MINIFS_S_IFDIR) == MINIFS_S_IFDIR);
                ml = (unsigned long)kstrlen(mname);
                if (ml == 0 || ml + (unsigned long)(isdir ? 1 : 0) >= RAMDISK_FNAME_LEN) continue;
                for (k = 0; k < (int)used; ) {
                    unsigned long el = kstrlen(out + k) + 1;
                    unsigned long base = el - ((out[k + el - 2] == '/') ? 1 : 0) - 1;
                    if (base == ml && kstrncmp(out + k, mname, ml) == 0) { dup = 1; break; }
                    k += (int)el;
                }
                if (dup) continue;
                nl = ml + (unsigned long)(isdir ? 1 : 0) + 1;
                if (used + nl > cap) break;
                kmemcpy(out + used, mname, ml);
                if (isdir) out[used + ml] = '/';
                out[used + nl - 1] = 0;
                used += nl;
                count++;
            }
        }
    }
    spin_unlock_irqrestore(&fs_lock, flags);
    return count;
}

static const minios_syscall_entry_t minios_syscall_table[MINIOS_SYSCALL_COUNT] = {
    [MINIOS_SYS_DNS - MINIOS_SYSCALL_BASE]         = { sys_minios_dns,         "dns" },
    [MINIOS_SYS_TLS_HANDSHAKE - MINIOS_SYSCALL_BASE] = { sys_linux_time, "time" },
    [MINIOS_SYS_TLS_SEND - MINIOS_SYSCALL_BASE]    = { sys_linux_futex,    "futex" },
    [MINIOS_SYS_TLS_RECV - MINIOS_SYSCALL_BASE]    = { sys_minios_tls_retired, "tls_retired" },
    [MINIOS_SYS_TIME - MINIOS_SYSCALL_BASE]        = { sys_minios_time,        "time" },
    [MINIOS_SYS_KBD - MINIOS_SYSCALL_BASE]         = { sys_minios_kbd,         "kbd" },
    [MINIOS_SYS_PALETTE - MINIOS_SYSCALL_BASE]     = { sys_minios_palette,     "palette" },
    [MINIOS_SYS_KBD_RAW - MINIOS_SYSCALL_BASE]     = { sys_minios_kbd_raw,     "kbd_raw" },
    [MINIOS_SYS_VGA_MODE - MINIOS_SYSCALL_BASE]    = { sys_minios_vga_mode,    "vga_mode" },
    [MINIOS_SYS_PCSPK_INIT - MINIOS_SYSCALL_BASE]  = { sys_minios_pcspk_init,  "pcspk_init" },
    [MINIOS_SYS_PCSPK_TONE - MINIOS_SYSCALL_BASE]  = { sys_minios_pcspk_tone,  "pcspk_tone" },
    [MINIOS_SYS_DOOM_FRAME - MINIOS_SYSCALL_BASE]  = { sys_minios_doom_frame,  "doom_frame" },
    [MINIOS_SYS_RTC - MINIOS_SYSCALL_BASE]         = { sys_minios_rtc,         "rtc" },
    [MINIOS_SYS_FB_INFO - MINIOS_SYSCALL_BASE]     = { sys_minios_fb_info,     "fb_info" },
    [MINIOS_SYS_PCSPK_VOL - MINIOS_SYSCALL_BASE]   = { sys_minios_pcspk_vol,   "pcspk_vol" },
    [MINIOS_SYS_SPAWN - MINIOS_SYSCALL_BASE]       = { sys_minios_spawn,       "spawn" },
    [MINIOS_SYS_LZ4_COMPRESS - MINIOS_SYSCALL_BASE]   = { sys_minios_lz4_compress, "lz4_compress" },
    [MINIOS_SYS_LZ4_DECOMPRESS - MINIOS_SYSCALL_BASE] = { sys_minios_lz4_decompress, "lz4_decompress" },
    [MINIOS_SYS_MOUSE - MINIOS_SYSCALL_BASE]       = { sys_minios_mouse,       "mouse" },
    [MINIOS_SYS_NK_FRAME - MINIOS_SYSCALL_BASE]    = { sys_minios_nk_frame,    "nk_frame" },
    [MINIOS_SYS_SB16_OPEN - MINIOS_SYSCALL_BASE]   = { sys_minios_sb16_open,   "sb16_open" },
    [MINIOS_SYS_SB16_SUBMIT - MINIOS_SYSCALL_BASE] = { sys_minios_sb16_submit, "sb16_submit" },
    [MINIOS_SYS_GFX_SET_TITLE - MINIOS_SYSCALL_BASE] = { sys_minios_gfx_title,  "gfx_title" },
    [MINIOS_SYS_SB16_PUMP - MINIOS_SYSCALL_BASE]   = { sys_minios_sb16_pump,   "sb16_pump" },
    [MINIOS_SYS_SB16_STREAM_OPEN - MINIOS_SYSCALL_BASE]   = { sys_minios_sb16_stream_open,   "sb16_stream_open" },
    [MINIOS_SYS_SB16_STREAM_CLOSE - MINIOS_SYSCALL_BASE]  = { sys_minios_sb16_stream_close,  "sb16_stream_close" },
    [MINIOS_SYS_SB16_STREAM_SUBMIT - MINIOS_SYSCALL_BASE] = { sys_minios_sb16_stream_submit, "sb16_stream_submit" },
    [MINIOS_SYS_SB16_STREAM_VOLUME - MINIOS_SYSCALL_BASE] = { sys_minios_sb16_stream_vol,    "sb16_stream_vol" },
    [MINIOS_SYS_CLONE - MINIOS_SYSCALL_BASE] = { sys_minios_clone,    "clone" },
    [MINIOS_SYS_THREAD_SPAWN - MINIOS_SYSCALL_BASE] = { sys_minios_thread_spawn, "thread_spawn" },
    [MINIOS_SYS_FUTEX_WAIT - MINIOS_SYSCALL_BASE] = { sys_minios_futex_wait, "futex_wait" },
    [MINIOS_SYS_FUTEX_WAKE - MINIOS_SYSCALL_BASE] = { sys_minios_futex_wake, "futex_wake" },
    [MINIOS_SYS_SUBMIT_BATCH - MINIOS_SYSCALL_BASE] = { sys_minios_submit_batch, "submit_batch" },
    [MINIOS_SYS_GETC_RAW - MINIOS_SYSCALL_BASE] = { sys_minios_getc_raw, "getc_raw" },
    [MINIOS_SYS_RLIMIT - MINIOS_SYSCALL_BASE] = { sys_minios_rlimit, "rlimit" },
    [MINIOS_SYS_GFX_PRESENT - MINIOS_SYSCALL_BASE] = { sys_minios_gfx_present, "gfx_present" },
    [MINIOS_SYS_SECCOMP - MINIOS_SYSCALL_BASE] = { sys_minios_seccomp, "seccomp" },
    [MINIOS_SYS_NICE - MINIOS_SYSCALL_BASE] = { sys_minios_nice, "nice" },
    [MINIOS_SYS_DIR_LIST - MINIOS_SYSCALL_BASE] = { sys_minios_dir_list, "dir_list" },
    [MINIOS_SYS_GFX_ZOOM - MINIOS_SYSCALL_BASE] = { sys_minios_gfx_zoom, "gfx_zoom" },
    [MINIOS_SYS_PCM2_OPEN - MINIOS_SYSCALL_BASE] = { sys_minios_pcm2_open, "pcm2_open" },
    [MINIOS_SYS_PCM2_WRITE - MINIOS_SYSCALL_BASE] = { sys_minios_pcm2_write, "pcm2_write" },
    [MINIOS_SYS_PCM2_CLOSE - MINIOS_SYSCALL_BASE] = { sys_minios_pcm2_close, "pcm2_close" },
    [MINIOS_SYS_CLIP_SET - MINIOS_SYSCALL_BASE] = { sys_minios_clip_set, "clip_set" },
    [MINIOS_SYS_CLIP_GET - MINIOS_SYSCALL_BASE] = { sys_minios_clip_get, "clip_get" },
    [MINIOS_SYS_MINFO - MINIOS_SYSCALL_BASE] = { sys_minios_minfo, "minfo" },
};

struct kiovec { const char *iov_base; unsigned long iov_len; };

#define SYSCALL_TRACE 0

static int s_trace_enabled = SYSCALL_TRACE;
static int s_trace_verbose = 0;
/* Shown-syscall odometer for `strace`/`ltrace`: incremented once per
 * traced (non-noisy) syscall while tracing is on. Lets the shell tell
 * "your command made no syscalls" (a ring-0 builtin) apart from "the
 * tracer is broken". SMP-safe increment; shell-time read. */
static volatile unsigned long s_trace_shown;

long syscall_trace_enabled(void) { return s_trace_enabled; }
void syscall_trace_set(int on) { s_trace_enabled = on ? 1 : 0; }
long syscall_trace_verbose_enabled(void) { return s_trace_verbose; }
void syscall_trace_verbose_set(int on) { s_trace_verbose = on ? 1 : 0; }
unsigned long syscall_trace_shown(void) { return s_trace_shown; }

/* Syscall numbers that are poll/clock reads: tracing them floods the console
 * (SYS_TIME is called inside every pacing spin loop), which made `trace on`
 * turn an interactive program into a 100 ms-per-syscall crawl.  Other syscalls
 * are traced one-to-one so a short program's full dialogue stays visible. */
#define SYS_NOISY_TIME   204
#define SYS_NOISY_KBD    205
#define SYS_NOISY_MOUSE  219
#define SYS_NOISY_GETC_RAW 236

/* =====================================================================
 * Linux ABI handlers (0-199), table-driven.
 *
 * Migrated verbatim from the switch in ksyscall_dispatch; behavior is
 * unchanged (same code, same order of checks). Numbers >= 200 that
 * overlap real Linux ABIs stay in the switch as documented
 * fall-throughs, as do out-of-range numbers (e.g. 334) and the
 * default ENOSYS path.
 * ===================================================================== */

static long kfile_user_read(KFILE *f, char *buf, long cnt);
static long kfile_user_write(KFILE *f, const char *buf, long cnt);
static long sys_linux_dup2(long a1, long a2, long a3, long a4, long a5, long a6);
static long sys_linux_close(long a1, long a2, long a3, long a4, long a5, long a6);

static long sys_linux_read(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    char *buf = (char *)a2; long cnt = a3, i = 0;
    if (cnt > 0 && !user_range_ok((unsigned long)buf, (unsigned long)cnt)) {
        kprintf("READ: EFAULT fd=%ld buf=%lx cnt=%ld\n", a1, a2, a3);
        return EFAULT;
    }
    if (net_sys_is_socket(a1)) {
        if (a3 > 0) { SANITIZE_RANGE(a2, (unsigned long)a3); }
        return net_sys_recvfrom(a1, a2, a3, 0, 0, 0);
    }
    if (a1 == 0) {
        if (!vga_fb_ps2_owner(current_pid)) return -11;
        {
            /* A dup2/pipe override on fd 0 (pipeline stage stdin):
             * serve it instead of the live console. Drained with the
             * writer open is EAGAIN (-11, retry); drained and closed
             * is EOF (0). */
            KFILE *o = kfd_get(0);
            if (o) {
                long r = (long)kfread(buf, 1, (unsigned long)cnt, o);
                int retry = (r == 0 && kpipe_empty_wopen(o)) ? 1 : 0;
                kfd_put(o);
                if (retry) return -11;
                return r;
            }
        }
        while (i < cnt) {
            int c = console_getc();
            if (c < 0) {
                if (console_stdin_active()) break;
                continue;
            }
            if (c == '\r') c = '\n';
            vga_putc((char)c);
            buf[i++] = (char)c;
            if (c == '\n') break;
        }
        return i;
    }
    {
        KFILE *f = kfd_get((int)a1);
        if (f) {
            long r = kfile_user_read(f, buf, cnt);
            kfd_put(f);
            return r;
        }
    }
    kprintf("READ: bad fd=%ld\n", a1);
    return -9;
}

/* Write cnt validated user bytes to fd: a dup2/pipe override on fd 1/2
 * (pipeline stage stdout) is served instead of the console, no override
 * means the historical console path byte for byte, and every other
 * description goes through kfile_user_write. */
static long fd_write(long fd, const char *buf, long cnt) {
    long i;
    if (net_sys_is_socket(fd)) return net_sys_sendto(fd, (long)buf, cnt, 0, 0, 0);
    if (fd == 1 || fd == 2) {
        KFILE *o = kfd_get((int)fd);
        if (o) {
            long r = kfile_user_write(o, buf, cnt);
            kfd_put(o);
            return r;
        }
        for (i = 0; i < cnt; i++) vga_putc(buf[i]);
        return cnt;
    }
    {
        KFILE *f = kfd_get((int)fd);
        if (f) {
            long r = kfile_user_write(f, buf, cnt);
            kfd_put(f);
            return r;
        }
    }
    return -9;
}

static long sys_linux_write(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    const char *buf = (const char *)a2; long cnt = a3;
    if (cnt > 0) { SANITIZE_RANGE(buf, (unsigned long)cnt); }
    return fd_write(a1, buf, cnt);
}

static long sys_linux_writev(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    struct kiovec *iov = (struct kiovec *)a2; long cnt = a3, total = 0, k;
    struct kiovec *kc = 0;
    if (cnt < 0 || (unsigned long)cnt > (USER_LOAD_END - USER_LOAD_BASE) / sizeof(struct kiovec))
        return -22;
    if (cnt > 0) {
        unsigned long span = (unsigned long)cnt * sizeof(struct kiovec);
        if (span / sizeof(struct kiovec) != (unsigned long)cnt) return EFAULT;
        SANITIZE_RANGE(iov, span);
        kc = (struct kiovec *)kmalloc(span ? span : 1);
        if (!kc) return EFAULT;
        kmemcpy(kc, iov, span);
    }
    for (k = 0; k < cnt; k++) {
        if (kc[k].iov_len > 0 &&
            !user_range_ok((unsigned long)kc[k].iov_base, kc[k].iov_len)) {
            kfree(kc);
            return total > 0 ? total : EFAULT;
        }
    }
    /* Every iovec reaches the descriptor (pipes and files included, not
     * just the console), stopping at the first short or failed write. */
    for (k = 0; k < cnt; k++) {
        long r;
        if (kc[k].iov_len == 0) continue;
        r = fd_write(a1, (const char *)kc[k].iov_base, (long)kc[k].iov_len);
        if (r < 0) {
            if (total == 0) total = r;
            break;
        }
        total += r;
        if ((unsigned long)r < kc[k].iov_len) break;
    }
    if (kc) kfree(kc);
    return total;
}

/* Shared by sys_linux_open (2) and the openat fall-through (257). The
 * slot scan and the publish re-check under fd_lock, so two racing
 * opens can never claim the same slot; the slow kfopen runs outside
 * the lock with nothing published yet. Linux O_CLOEXEC (0x80000) arms
 * the close-on-exec bit without disturbing the mode selection. */
static long do_open_path(const char *path, long flags) {
    const char *mode = ((flags & 1) || (flags & 0x40)) ? "w" : "r";
    int fd, cloexec = (flags & 0x80000) ? 1 : 0;
    irqflags_t flags_irq;
    kfd_view_t *v;
    SANITIZE_STR(path, RAMDISK_FNAME_LEN);
    {
        proc_t *op = (current_pid >= 0 && current_pid < MAX_PROCS) ? &procs[current_pid] : 0;
        if (op && op->rl_nofile_max && (unsigned long)op->open_files >= op->rl_nofile_max)
            return -24;
    }
    KFILE *f = kfopen(path, mode);
    if (!f) {
        return -2;
    }
    v = kfd_view_current();
    spin_lock_irqsave(&fd_lock, &flags_irq);
    for (fd = 3; fd < KFD_MAX; fd++) if (!v->f[fd]) break;
    if (fd >= KFD_MAX) {
        spin_unlock_irqrestore(&fd_lock, flags_irq);
        kfclose(f);
        return -24;
    }
    v->f[fd] = f;
    if (cloexec) v->cloexec |= (1u << (unsigned)fd);
    spin_unlock_irqrestore(&fd_lock, flags_irq);
    {
        proc_t *op = (current_pid >= 0 && current_pid < MAX_PROCS) ? &procs[current_pid] : 0;
        if (op && op->open_files < KFD_MAX) op->open_files++;
    }
    return fd;
}

static long sys_linux_open(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    return do_open_path((const char *)a1, a2);
}

/* Linux descriptor-flag ABI values (docs/spec/smp-sched.md, Linux
 * process, thread and descriptor ABI). Named, never bare. */
#define LINUX_O_RDONLY          0
#define LINUX_O_WRONLY          1
#define LINUX_O_RDWR            2
#define LINUX_O_APPEND          0x400
#define LINUX_O_NONBLOCK        0x800
#define LINUX_O_DIRECT          0x4000
#define LINUX_O_CLOEXEC         0x80000
#define LINUX_FD_CLOEXEC        1
#define LINUX_F_DUPFD           0
#define LINUX_F_GETFD           1
#define LINUX_F_SETFD           2
#define LINUX_F_GETFL           3
#define LINUX_F_SETFL           4
#define LINUX_F_DUPFD_CLOEXEC   1030
#define LINUX_CLOSE_RANGE_UNSHARE 2
#define LINUX_CLOSE_RANGE_CLOEXEC 4
#define LINUX_EFD_SEMAPHORE     1
#define LINUX_EFD_NONBLOCK      0x800
#define LINUX_EFD_CLOEXEC       0x80000
#define LINUX_EVENTFD_WORD      8
#define FD_STD_COUNT            3

/* Claim the lowest free fd slot >= minfd for an already-opened KFILE
 * (pipes, dup, eventfd), arming close-on-exec when asked. The slot scan
 * and publish re-check under fd_lock like do_open_path; the caller keeps
 * ownership on failure. Slots 0..2 stay the console's. */
static long kfd_claim_from(KFILE *f, long minfd, int cloexec) {
    int fd;
    irqflags_t flags_irq;
    kfd_view_t *v;
    if (!f) return -9;
    if (minfd < FD_STD_COUNT) minfd = FD_STD_COUNT;
    if (minfd >= KFD_MAX) return -22;
    v = kfd_view_current();
    spin_lock_irqsave(&fd_lock, &flags_irq);
    for (fd = (int)minfd; fd < KFD_MAX; fd++) if (!v->f[fd]) break;
    if (fd >= KFD_MAX) {
        spin_unlock_irqrestore(&fd_lock, flags_irq);
        return -24;
    }
    v->f[fd] = f;
    if (cloexec) v->cloexec |= (1u << (unsigned)fd);
    else v->cloexec &= ~(1u << (unsigned)fd);
    spin_unlock_irqrestore(&fd_lock, flags_irq);
    {
        proc_t *op = (current_pid >= 0 && current_pid < MAX_PROCS) ? &procs[current_pid] : 0;
        if (op && op->open_files < KFD_MAX) op->open_files++;
    }
    return fd;
}

static long kfd_claim(KFILE *f) {
    return kfd_claim_from(f, FD_STD_COUNT, 0);
}

/** Docstring: Install f as the live mapping for fd 0..KFD_MAX (dup2
 * target or pipeline override), returning the previous mapping without
 * dropping its reference (the caller restores or closes it). Fail-closed
 * on a wild fd. The table takes no new reference: the caller lends its
 * own (a held kfd_get reference or a fresh pipe end). */
KFILE *kfd_override(int fd, KFILE *f) {
    irqflags_t flags_irq;
    KFILE *old = 0;
    kfd_view_t *v;
    if (fd < 0 || fd >= KFD_MAX) return 0;
    v = kfd_view_current();
    spin_lock_irqsave(&fd_lock, &flags_irq);
    old = v->f[fd];
    v->f[fd] = f;
    spin_unlock_irqrestore(&fd_lock, flags_irq);
    return old;
}

/* pipe2 (293): O_CLOEXEC arms close-on-exec on both ends, O_NONBLOCK makes
 * both descriptions non-blocking; O_DIRECT packet pipes are refused. */
static long sys_linux_pipe2(long a1, long a2, long a3, long a4, long a5, long a6) {
    int *ufd = (int *)a1;
    KFILE *r = 0, *w = 0;
    long rfd, wfd;
    int cloexec = (a2 & LINUX_O_CLOEXEC) ? 1 : 0;
    (void)a3; (void)a4; (void)a5; (void)a6;
    if (a2 & ~(long)(LINUX_O_CLOEXEC | LINUX_O_NONBLOCK)) return -22;
    SANITIZE_RANGE(ufd, 2u * sizeof(int));
    if (kpipe_pair(&r, &w) != 0) return -24;
    if (a2 & LINUX_O_NONBLOCK) { r->nonblock = 1; w->nonblock = 1; }
    rfd = kfd_claim_from(r, FD_STD_COUNT, cloexec);
    if (rfd < 0) { kfclose(r); kfclose(w); return rfd; }
    wfd = kfd_claim_from(w, FD_STD_COUNT, cloexec);
    if (wfd < 0) {
        irqflags_t flags_irq;
        kfd_view_t *v = kfd_view_current();
        spin_lock_irqsave(&fd_lock, &flags_irq);
        if (rfd >= 0 && rfd < KFD_MAX && v->f[rfd] == r) v->f[rfd] = 0;
        spin_unlock_irqrestore(&fd_lock, flags_irq);
        kfclose(r);
        kfclose(w);
        return wfd;
    }
    ufd[0] = (int)rfd;
    ufd[1] = (int)wfd;
    return 0;
}

static long sys_linux_pipe(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2;
    return sys_linux_pipe2(a1, 0, a3, a4, a5, a6);
}

/* close-on-exec bit of fd in the caller's view (fd < KFD_MAX). */
static int kfd_cloexec_get(long fd) {
    irqflags_t flags_irq;
    kfd_view_t *v = kfd_view_current();
    int on;
    spin_lock_irqsave(&fd_lock, &flags_irq);
    on = (v->cloexec & (1u << (unsigned)fd)) ? 1 : 0;
    spin_unlock_irqrestore(&fd_lock, flags_irq);
    return on;
}

static void kfd_cloexec_set(long fd, int on) {
    irqflags_t flags_irq;
    kfd_view_t *v = kfd_view_current();
    spin_lock_irqsave(&fd_lock, &flags_irq);
    if (on) v->cloexec |= (1u << (unsigned)fd);
    else v->cloexec &= ~(1u << (unsigned)fd);
    spin_unlock_irqrestore(&fd_lock, flags_irq);
}

/* Linux open-file status flags of a description: access mode from its
 * kind plus O_APPEND and O_NONBLOCK. */
static long kfile_status_flags(KFILE *f) {
    long fl;
    if (f->is_eventfd) fl = LINUX_O_RDWR;
    else if (f->is_pipe) fl = f->pipe_write ? LINUX_O_WRONLY : LINUX_O_RDONLY;
    else if (f->mode == 0) fl = LINUX_O_RDONLY;
    else fl = LINUX_O_WRONLY | ((f->mode == 2) ? LINUX_O_APPEND : 0);
    if (f->nonblock) fl |= LINUX_O_NONBLOCK;
    return fl;
}

/* fcntl (72): DUPFD/DUPFD_CLOEXEC, GETFD/SETFD (FD_CLOEXEC), GETFL, and
 * SETFL (O_NONBLOCK only, other bits ignored like Linux). The console
 * descriptors 0..2 answer read-write, never close-on-exec. */
static long sys_linux_fcntl(long a1, long a2, long a3, long a4, long a5, long a6) {
    KFILE *f;
    long r;
    (void)a4; (void)a5; (void)a6;
    if (net_sys_is_socket(a1)) return net_sys_fcntl(a1, a2, a3);
    if (a1 < 0 || a1 >= KFD_MAX) return -9;
    f = kfd_get((int)a1);
    if (!f && a1 >= FD_STD_COUNT) return -9;
    switch (a2) {
    case LINUX_F_DUPFD:
    case LINUX_F_DUPFD_CLOEXEC:
        if (!f) return -22;
        r = kfd_claim_from(f, a3, a2 == LINUX_F_DUPFD_CLOEXEC);
        if (r < 0) kfd_put(f);
        return r;
    case LINUX_F_GETFD:
        r = f ? (kfd_cloexec_get(a1) ? LINUX_FD_CLOEXEC : 0) : 0;
        break;
    case LINUX_F_SETFD:
        if (f) kfd_cloexec_set(a1, (a3 & LINUX_FD_CLOEXEC) ? 1 : 0);
        r = 0;
        break;
    case LINUX_F_GETFL:
        r = f ? kfile_status_flags(f) : LINUX_O_RDWR;
        break;
    case LINUX_F_SETFL:
        if (f) f->nonblock = (a3 & LINUX_O_NONBLOCK) ? 1 : 0;
        r = 0;
        break;
    default:
        r = -22;
        break;
    }
    if (f) kfd_put(f);
    return r;
}

/* dup3 (292): dup2 with O_CLOEXEC as the only flag; old == new is EINVAL. */
static long sys_linux_dup3(long a1, long a2, long a3, long a4, long a5, long a6) {
    long r;
    if (a3 & ~(long)LINUX_O_CLOEXEC) return -22;
    if (a1 == a2) return -22;
    r = sys_linux_dup2(a1, a2, 0, a4, a5, a6);
    if (r >= 0 && r < KFD_MAX) kfd_cloexec_set(r, (a3 & LINUX_O_CLOEXEC) ? 1 : 0);
    return r;
}

/* close_range (436): mark [first, last] close-on-exec, or close it. */
static long sys_linux_close_range(long a1, long a2, long a3, long a4, long a5, long a6) {
    unsigned long lo = (unsigned long)(unsigned int)a1;
    unsigned long hi = (unsigned long)(unsigned int)a2;
    unsigned long fd;
    (void)a4; (void)a5; (void)a6;
    if (a3 & ~(long)(LINUX_CLOSE_RANGE_UNSHARE | LINUX_CLOSE_RANGE_CLOEXEC)) return -22;
    if (lo > hi) return -22;
    if (a3 & LINUX_CLOSE_RANGE_CLOEXEC) {
        irqflags_t flags_irq;
        kfd_view_t *v = kfd_view_current();
        spin_lock_irqsave(&fd_lock, &flags_irq);
        for (fd = lo; fd <= hi && fd < KFD_MAX; fd++)
            if (v->f[fd]) v->cloexec |= (1u << (unsigned)fd);
        spin_unlock_irqrestore(&fd_lock, flags_irq);
        return 0;
    }
    for (fd = lo; fd <= hi && fd < KFD_MAX; fd++)
        if (fd >= FD_STD_COUNT) sys_linux_close((long)fd, 0, 0, 0, 0, 0);
    for (fd = NET_FD_BASE; fd < (unsigned long)(NET_UDP_FD_BASE + NET_UDP_SOCKETS); fd++)
        if (fd >= lo && fd <= hi && net_sys_is_socket((long)fd)) net_sys_close((long)fd);
    return 0;
}

/* eventfd2 (290) / eventfd (284): a counter description (kevent_*). */
static long sys_linux_eventfd2(long a1, long a2, long a3, long a4, long a5, long a6) {
    KFILE *f;
    long fd;
    (void)a3; (void)a4; (void)a5; (void)a6;
    if (a2 & ~(long)(LINUX_EFD_SEMAPHORE | LINUX_EFD_NONBLOCK | LINUX_EFD_CLOEXEC)) return -22;
    f = kevent_create((unsigned long long)(unsigned int)a1, (a2 & LINUX_EFD_SEMAPHORE) != 0);
    if (!f) return -12;
    f->nonblock = (a2 & LINUX_EFD_NONBLOCK) ? 1 : 0;
    fd = kfd_claim_from(f, FD_STD_COUNT, (a2 & LINUX_EFD_CLOEXEC) != 0);
    if (fd < 0) kfclose(f);
    return fd;
}

static long sys_linux_eventfd(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2;
    return sys_linux_eventfd2(a1, 0, a3, a4, a5, a6);
}

/** Docstring: poll(2) readiness of a non-socket descriptor (pipes,
 * eventfds, files, console), masked by nothing: the caller keeps the
 * requested bits plus POLLERR/POLLHUP/POLLNVAL. POLLNVAL for a closed fd. */
int kfd_poll_revents(int fd) {
    KFILE *f;
    int rev = 0;
    if (fd < 0 || fd >= KFD_MAX) return NET_POLLNVAL;
    f = kfd_get(fd);
    if (!f) {
        if (fd >= FD_STD_COUNT) return NET_POLLNVAL;
        return fd == 0 ? 0 : NET_POLLOUT;
    }
    if (f->is_eventfd) {
        if (kevent_readable(f)) rev |= NET_POLLIN;
        if (kevent_writable(f)) rev |= NET_POLLOUT;
    } else if (f->is_pipe) {
        unsigned avail = 0, space = 0;
        int wopen = 0, ropen = 0;
        if (kpipe_state(f, &avail, &space, &wopen, &ropen) == 0) {
            if (!f->pipe_write) {
                if (avail > 0u) rev |= NET_POLLIN;
                if (!wopen) rev |= NET_POLLHUP;
            } else {
                if (!ropen) rev |= NET_POLLERR;
                else if (space > 0u) rev |= NET_POLLOUT;
            }
        }
    } else {
        rev = NET_POLLIN | NET_POLLOUT;
    }
    kfd_put(f);
    return rev;
}

/* Linux read on a description: an eventfd takes its counter, a pipe read
 * end blocks (yielding) while empty with the writer open unless
 * O_NONBLOCK (-EAGAIN), and reports EOF once the writer closed; every
 * other file reads through kfread. */
static long kfile_user_read(KFILE *f, char *buf, long cnt) {
    if (f->is_eventfd) {
        unsigned long long v = 0;
        if (cnt < LINUX_EVENTFD_WORD) return -22;
        for (;;) {
            if (kevent_read(f, &v) == 0) {
                kmemcpy(buf, &v, LINUX_EVENTFD_WORD);
                return LINUX_EVENTFD_WORD;
            }
            if (f->nonblock) return -11;
            yield();
        }
    }
    if (cnt <= 0) return 0;
    if (f->is_pipe && !f->pipe_write) {
        for (;;) {
            long r = (long)kfread(buf, 1, (unsigned long)cnt, f);
            if (r > 0) return r;
            if (!kpipe_empty_wopen(f)) return 0;
            if (f->nonblock) return -11;
            yield();
        }
    }
    return (long)kfread(buf, 1, (unsigned long)cnt, f);
}

/* Linux write on a description: an eventfd adds to its counter, a pipe
 * write end blocks (yielding) while full unless O_NONBLOCK and answers
 * -EPIPE once the reader closed; every other file writes through
 * kfwrite. */
static long kfile_user_write(KFILE *f, const char *buf, long cnt) {
    if (f->is_eventfd) {
        unsigned long long v = 0;
        long rc;
        if (cnt < LINUX_EVENTFD_WORD) return -22;
        kmemcpy(&v, buf, LINUX_EVENTFD_WORD);
        for (;;) {
            rc = kevent_write(f, v);
            if (rc == 0) return LINUX_EVENTFD_WORD;
            if (rc != -11 || f->nonblock) return rc;
            yield();
        }
    }
    if (cnt <= 0) return 0;
    if (f->is_pipe && f->pipe_write) {
        long done = 0;
        for (;;) {
            int wopen = 0, ropen = 0;
            if (kpipe_state(f, 0, 0, &wopen, &ropen) != 0) return -5;
            if (!ropen) return done > 0 ? done : -32;
            done += (long)kfwrite(buf + done, 1, (unsigned long)(cnt - done), f);
            if (done >= cnt) return done;
            if (f->nonblock) return done > 0 ? done : -11;
            yield();
        }
    }
    return (long)kfwrite(buf, 1, (unsigned long)cnt, f);
}

static long sys_linux_dup(long a1, long a2, long a3, long a4, long a5, long a6) {
    KFILE *f;
    long fd;
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    if (a1 >= NET_FD_BASE || a1 < 0) return -9;
    f = kfd_get((int)a1);
    if (!f) {
        if (a1 < 3) return a1;
        return -9;
    }
    fd = kfd_claim(f);
    if (fd < 0) kfd_put(f);
    return fd;
}

static long sys_linux_dup2(long a1, long a2, long a3, long a4, long a5, long a6) {
    KFILE *f, *old;
    irqflags_t flags_irq;
    kfd_view_t *v;
    (void)a3; (void)a4; (void)a5; (void)a6;
    if (a1 >= NET_FD_BASE || a1 < 0 || a2 < 0 || a2 >= KFD_MAX) return -9;
    if (a1 == a2) {
        kfd_view_t *vv = kfd_view_current();
        if (a1 >= 3 && !vv->f[(int)a1]) return -9;
        return a2;
    }
    f = kfd_get((int)a1);
    if (!f) {
        if (a1 < 3) {
            v = kfd_view_current();
            spin_lock_irqsave(&fd_lock, &flags_irq);
            old = v->f[(int)a2];
            v->f[(int)a2] = 0;
            spin_unlock_irqrestore(&fd_lock, flags_irq);
            if (old) kfd_put(old);
            return a2;
        }
        return -9;
    }
    v = kfd_view_current();
    spin_lock_irqsave(&fd_lock, &flags_irq);
    old = v->f[(int)a2];
    v->f[(int)a2] = f;
    v->cloexec &= ~(1u << (unsigned)a2);
    spin_unlock_irqrestore(&fd_lock, flags_irq);
    if (old) kfd_put(old);
    return a2;
}

static long sys_linux_close(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    if (a1 >= NET_FD_BASE) return net_sys_close(a1);
    {
        irqflags_t flags_irq;
        KFILE *f = 0;
        kfd_view_t *v = kfd_view_current();
        spin_lock_irqsave(&fd_lock, &flags_irq);
        if (a1 >= 0 && a1 < KFD_MAX && v->f[a1]) {
            f = v->f[a1];
            v->f[a1] = 0;
            v->cloexec &= ~(1u << (unsigned)a1);
        }
        spin_unlock_irqrestore(&fd_lock, flags_irq);
        if (f) {
            proc_t *cp = (current_pid >= 0 && current_pid < MAX_PROCS) ? &procs[current_pid] : 0;
            kfd_put(f);
            if (cp && cp->open_files > 0) cp->open_files--;
        }
    }
    return 0;
}

static long sys_linux_lseek(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    {
        KFILE *f = kfd_get((int)a1);
        if (f) {
            kfseek(f, a2, (int)a3);
            long pos = kftell(f);
            kfd_put(f);
            return pos;
        }
    }
    return -9;
}

/* Back isolated user windows (mrun/proc_spawn_elf): their page tables
 * start with only segments + stack mapped, so heap/mmap growth must
 * materialize pages. Shared-window PTEs are already present and the call
 * below is a no-op there: zero behavior change on the legacy path. */
static int mm_ensure_cur(unsigned long start, unsigned long end) {
    unsigned long cr3, p;
    __asm__ volatile("mov %%cr3, %0" : "=r"(cr3));
    for (p = start & ~0xFFFUL; p < end; p += 0x1000)
        if (mm_user_ensure_page(cr3, p)) return -1;
    __asm__ volatile("mov %%cr3, %%rax; mov %%rax, %%cr3" ::: "rax", "memory");
    return 0;
}

static long sys_linux_brk(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    unsigned long addr = (unsigned long)a1;
    irqflags_t flags;
    proc_t *bp;
    spin_lock_irqsave(&mm_lock, &flags);
    if (addr == 0) { long r = (long)g_brk; spin_unlock_irqrestore(&mm_lock, flags); return r; }
    bp = (current_pid >= 0 && current_pid < MAX_PROCS) ? &procs[current_pid] : 0;
    if (bp && bp->rl_as_max && addr > USER_LOAD_BASE &&
        addr - USER_LOAD_BASE > bp->rl_as_max) {
        long r = (long)g_brk;
        spin_unlock_irqrestore(&mm_lock, flags);
        return r;
    }
    if (addr >= USER_LOAD_BASE && addr <= g_brk_limit
        && addr <= user_mmap_cur) {
        unsigned long old = g_brk;
        g_brk = addr;
        if (addr > old && mm_ensure_cur(old, addr)) {
            g_brk = old;
            spin_unlock_irqrestore(&mm_lock, flags);
            return -12;
        }
    }
    long r = (long)g_brk;
    spin_unlock_irqrestore(&mm_lock, flags);
    return r;
}

/* Linux mmap(9) flags. Named, never bare. File-backed mappings
 * are MAP_PRIVATE over a MiniFS file at a page-aligned offset;
 * MAP_SHARED refuses until slice 3 proves writeback ordering, and
 * ramdisk/pipe/console fds refuse (identity without sharing). */
#define LINUX_MAP_SHARED 1
#define LINUX_MAP_PRIVATE 2
#define LINUX_MAP_FIXED 0x10
#define LINUX_MAP_ANONYMOUS 0x20

/** Docstring: Tag a freshly carved live node as file-backed. The
 * node was just inserted at base, so the exact find hits; failure
 * leaves it anonymous and fails the call, never half-tagged. */
static int mmap_tag_file(unsigned long base, int ino, unsigned long off) {
    vma_node_t *fnd = vma_tree_find(vma_live_root, base);
    if (fnd == VMA_NIL) return -1;
    fnd->f_file = 1;
    fnd->f_ino = ino;
    fnd->f_off = off;
    return 0;
}

static int vma_live_overlap(unsigned long base, unsigned long len);

/* Invariant guard for every range mmap hands out: it must not overlap a
 * live mapping or reach below the brk heap. A hit means the VMA trees or
 * the bump pointer are corrupt; handing the range out would give one page
 * two owners, so the mapping is refused and the defect reported. */
static int mmap_range_free(unsigned long base, unsigned long len) {
    if (base < g_brk || vma_live_overlap(base, len)) {
        kprintf("mmap: refusing %lx+%lx: overlaps a live mapping or the brk heap (pid %d, brk %lx)\n",
                base, len, current_pid, g_brk);
        return 0;
    }
    return 1;
}

static long sys_linux_mmap(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1;
    unsigned long len = (unsigned long)a2;
    unsigned long n = ALIGN_UP(len ? len : 1, 0x1000);
    unsigned long mflags = (unsigned long)a4;
    irqflags_t flags;
    int is_file = 0;
    int fino = -1;
    unsigned long foff = 0;
    if (!(mflags & (unsigned long)LINUX_MAP_ANONYMOUS)) {
        KFILE *f;
        if ((mflags & (unsigned long)LINUX_MAP_SHARED) ||
                !(mflags & (unsigned long)LINUX_MAP_PRIVATE))
            return -22;
        if (((unsigned long)a6) & 0xFFFUL) return -22;
        f = kfd_get((int)a5);
        if (!f) return -EBADF;
        if (f->is_pipe || f->is_console || f->minifs_ino < 0) {
            kfd_put(f);
            return -22;
        }
        fino = f->minifs_ino;
        foff = (unsigned long)a6;
        kfd_put(f);
        is_file = 1;
    }
    spin_lock_irqsave(&mm_lock, &flags);
    long ret;
    if (n > user_mmap_cur - USER_LOAD_BASE) { ret = -12; goto mmap_out; }
    {
        proc_t *mp = (current_pid >= 0 && current_pid < MAX_PROCS) ? &procs[current_pid] : 0;
        if (mp && mp->rl_as_max) {
            unsigned long used = 0;
            if (g_brk > USER_LOAD_BASE) used += g_brk - USER_LOAD_BASE;
            if (USER_BRK_END > user_mmap_cur) used += USER_BRK_END - user_mmap_cur;
            if (used + n > mp->rl_as_max) { ret = -12; goto mmap_out; }
        }
    }
    {
        vma_node_t *best = VMA_NIL;
        vma_node_t *stack[64];
        int sp = 0;
        vma_node_t *x = vma_free_root;
        while (x != VMA_NIL || sp > 0) {
            while (x != VMA_NIL) { if (sp < 64) stack[sp++] = x; x = x->left; }
            x = stack[--sp];
            if (x->len >= n && (best == VMA_NIL || x->base < best->base))
                best = x;
            x = x->right;
        }
        if (best != VMA_NIL) {
            unsigned long addr = best->base + best->len - n;
            unsigned long rem_base = best->base;
            unsigned long rem_len = best->len - n;
            if (!mmap_range_free(addr, n)) { ret = -12; goto mmap_out; }
            vma_tree_delete(&vma_free_root, best->base);
            if (rem_len > 0)
                vma_tree_insert(&vma_free_root, rem_base, rem_len);
            vma_tree_insert(&vma_live_root, addr, n);
            if (!is_file && mm_anon_reserve(0, addr, n, (unsigned long)a3)) {
                vma_tree_delete(&vma_live_root, addr);
                vma_tree_insert(&vma_free_root, addr, n);
                ret = -12;
                goto mmap_out;
            }
            if (is_file && mmap_tag_file(addr, fino, foff)) {
                vma_tree_delete(&vma_live_root, addr);
                vma_tree_insert(&vma_free_root, addr, n);
                ret = -12;
                goto mmap_out;
            }
            ret = (long)addr;
            goto mmap_out;
        }
    }
    if (user_mmap_cur - n < g_brk) { ret = -12; goto mmap_out; }
    if (!mmap_range_free(user_mmap_cur - n, n)) { ret = -12; goto mmap_out; }
    user_mmap_cur -= n;
    if (!is_file && mm_anon_reserve(0, user_mmap_cur, n, (unsigned long)a3)) {
        user_mmap_cur += n;
        ret = -12;
        goto mmap_out;
    }
    vma_tree_insert(&vma_live_root, user_mmap_cur, n);
    if (is_file && mmap_tag_file(user_mmap_cur, fino, foff)) {
        vma_tree_delete(&vma_live_root, user_mmap_cur);
        user_mmap_cur += n;
        ret = -12;
        goto mmap_out;
    }
    ret = (long)user_mmap_cur;
mmap_out:
    spin_unlock_irqrestore(&mm_lock, flags);
    return ret;
}

/* Lowest live mapping overlapping [base, end), or VMA_NIL. Bounded
 * explicit-stack walk like the mmap best-fit search. */
static vma_node_t *vma_live_first_overlap(unsigned long base, unsigned long end) {
    vma_node_t *best = VMA_NIL;
    vma_node_t *stack[64];
    int sp = 0;
    vma_node_t *x = vma_live_root;
    while (x != VMA_NIL || sp > 0) {
        while (x != VMA_NIL) { if (sp < 64) stack[sp++] = x; x = x->left; }
        x = stack[--sp];
        if (x->base < end && x->base + x->len > base &&
                (best == VMA_NIL || x->base < best->base))
            best = x;
        x = x->right;
    }
    return best;
}

/* Insert a live remainder of a split mapping, keeping its file identity. */
static int vma_live_remainder(unsigned long base, unsigned long len,
        int file, int ino, unsigned long off) {
    vma_node_t *r = vma_tree_insert(&vma_live_root, base, len);
    if (r == VMA_NIL) return -1;
    if (file) { r->f_file = 1; r->f_ino = ino; r->f_off = off; }
    return 0;
}

/* Linux munmap(11): every mapping overlapping [base, base + len) loses
 * the overlap, which may be its head, tail, middle or all of it; the
 * survivors stay live (file mappings keep their offsets) and only the
 * unmapped pages are released and returned to the free tree. Unmapping
 * a hole is not an error. -EINVAL for an unaligned base, a zero length
 * or a range leaving the user window; -ENOMEM when the node pool cannot
 * hold a split (the mapping is restored untouched). */
static long sys_linux_munmap(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    unsigned long base = (unsigned long)a1;
    unsigned long n = ALIGN_UP((unsigned long)a2, 0x1000);
    unsigned long end = base + n;
    irqflags_t flags;
    vma_node_t *v;
    long ret = 0;
    if (base & 0xFFFUL || n == 0 || end < base) return -22;
    if (base < USER_LOAD_BASE || end > USER_LOAD_END) return -22;
    /* The shared-library region is kernel-managed (registry bases,
     * shared text): user munmap there refuses, never half-unmaps. */
    if (base < LDSO_REGION_END && end > LDSO_REGION_BASE)
        return -1;
    spin_lock_irqsave(&mm_lock, &flags);
    while ((v = vma_live_first_overlap(base, end)) != VMA_NIL) {
        unsigned long vb = v->base, ve = v->base + v->len;
        unsigned long lo = vb > base ? vb : base;
        unsigned long hi = ve < end ? ve : end;
        int file = v->f_file, ino = v->f_ino;
        unsigned long off = v->f_off;
        vma_tree_delete(&vma_live_root, vb);
        if (vb < lo && vma_live_remainder(vb, lo - vb, file, ino, off)) {
            vma_live_remainder(vb, ve - vb, file, ino, off);
            ret = -12;
            break;
        }
        if (hi < ve && vma_live_remainder(hi, ve - hi, file, ino, off + (hi - vb))) {
            if (vb < lo) vma_tree_delete(&vma_live_root, vb);
            vma_live_remainder(vb, ve - vb, file, ino, off);
            ret = -12;
            break;
        }
        if (file)
            mm_file_range_release(0, lo, hi - lo, ino, off + (lo - vb), 1);
        else
            mm_anon_release(0, lo, hi - lo);
        vma_tree_insert(&vma_free_root, lo, hi - lo);
    }
    spin_unlock_irqrestore(&mm_lock, flags);
    return ret;
}

/** Docstring: Locate the PTE for a user address in the caller's live
 * tables (syscall entry keeps the caller CR3 loaded, so no KPTI swap
 * is needed). Mirrors the cow_resolve walk exactly: PML4 entry 0,
 * PDPT entry 0, 4 KB PT pages only. Returns 0 for any missing level
 * or huge page; the caller turns that into -ENOMEM without touching
 * a single bit, so a half-mapped range never applies half. */
static volatile unsigned long *mprotect_pte(unsigned long cr3,
        unsigned long va) {
    volatile unsigned long *pml4;
    volatile unsigned long *pdpt;
    volatile unsigned long *pd;
    volatile unsigned long *pt;
    if (!cr3) return 0;
    pml4 = (volatile unsigned long *)(cr3 & (unsigned long)PT_ADDR_MASK);
    if (!(pml4[0] & (unsigned long)PT_FLAGS_PRESENT_RW)) return 0;
    pdpt = (volatile unsigned long *)(pml4[0] & (unsigned long)PT_ADDR_MASK);
    if (!(pdpt[0] & (unsigned long)PT_FLAGS_PRESENT_RW)) return 0;
    if (pdpt[0] & (unsigned long)PT_FLAGS_PS) return 0;
    pd = (volatile unsigned long *)(pdpt[0] & (unsigned long)PT_ADDR_MASK);
    if (!(pd[va >> PT_PD_INDEX_SHIFT] & (unsigned long)PT_FLAGS_PRESENT_RW))
        return 0;
    if (pd[va >> PT_PD_INDEX_SHIFT] & (unsigned long)PT_FLAGS_PS) return 0;
    pt = (volatile unsigned long *)
        ((pd[va >> PT_PD_INDEX_SHIFT]) & (unsigned long)PT_ADDR_MASK);
    return &pt[(va >> 12) & 0x1FF];
}

/** Docstring: Linux mprotect(10), enforced for real. Toggles the RW
 * and NX bits page by page with a local invlpg each, then one
 * tlb_shootdown so a sibling thread on another CPU loses the old rights. Two
 * passes under mm_lock: validate every page first (present, user,
 * private), then apply, so a half-mapped range reports -ENOMEM
 * without changing anything. -EINVAL for unaligned base or unknown
 * prot bits. A write fault on a cleared page falls through
 * cow_resolve (not a CoW page) into the kill path, exactly like nx.
 * A demand-paging reservation (never touched) just takes the new
 * protection in its marker, committing no memory: glibc reserves thread
 * stacks and malloc arenas PROT_NONE and opens them up this way. Two
 * documented deviations on present pages: PROT_NONE stays present
 * (denies write and exec, reads still succeed) because the reaper only
 * frees present data pages, and CoW-shared pages refuse with -ENOMEM
 * (upgrading them in place would let one window write another's
 * bytes past cow_resolve). Cache-shared file pages refuse the same
 * way: touch-write them first (the fault breaks a private copy) and
 * then protect the private pages. */
static long sys_linux_mprotect(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    unsigned long base = (unsigned long)a1;
    unsigned long n = ALIGN_UP((unsigned long)a2, 0x1000);
    unsigned long prot = (unsigned long)a3;
    unsigned long cr3 = 0;
    unsigned long va;
    irqflags_t flags;
    int want_write;
    int want_exec;
    if (prot & ~(unsigned long)7) return -22;
    if (base & 0xFFFUL) return -22;
    if (base < USER_LOAD_BASE || base >= USER_LOAD_END) return -12;
    if (n == 0) return 0;
    if (base + n < base || base + n > USER_LOAD_END) return -12;
    want_write = (prot & 2u) != 0;
    want_exec = (prot & 4u) != 0;
    __asm__ volatile("mov %%cr3, %0" : "=r"(cr3));
    spin_lock_irqsave(&mm_lock, &flags);
    for (va = base; va < base + n; va += 0x1000) {
        volatile unsigned long *pp = mprotect_pte(cr3, va);
        unsigned long pte;
        unsigned long phys;
        if (!pp) { spin_unlock_irqrestore(&mm_lock, flags); return -12; }
        pte = *pp;
        if (!(pte & 1u) && (pte & PTE_DEMAND)) continue;
        if (!(pte & 1u) || !(pte & (unsigned long)PT_FLAGS_USER)) {
            spin_unlock_irqrestore(&mm_lock, flags);
            return -12;
        }
        phys = pte & (unsigned long)PT_ADDR_MASK;
        if (!phys) { spin_unlock_irqrestore(&mm_lock, flags); return -12; }
        if (want_write && cow_page_shared(phys)) {
            spin_unlock_irqrestore(&mm_lock, flags);
            return -12;
        }
        if (want_write && pcache_owns_phys(phys)) {
            spin_unlock_irqrestore(&mm_lock, flags);
            return -12;
        }
    }
    for (va = base; va < base + n; va += 0x1000) {
        volatile unsigned long *pp = mprotect_pte(cr3, va);
        unsigned long pte = *pp;
        if (!(pte & 1u) && (pte & PTE_DEMAND)) {
            *pp = mm_demand_pte(prot);
            continue;
        }
        pte &= ~((unsigned long)0x002 | (unsigned long)PT_FLAGS_NX);
        if (want_write) pte |= (unsigned long)0x002;
        if (!want_exec) pte |= (unsigned long)PT_FLAGS_NX;
        *pp = pte;
        __asm__ volatile("invlpg (%0)" :: "r"(va) : "memory");
    }
    tlb_shootdown(cr3);
    spin_unlock_irqrestore(&mm_lock, flags);
    return 0;
}

/* Linux mremap(25) flags. Named, never bare: FIXED needs MAYMOVE plus the
 * 5th-arg target, anything outside the two is EINVAL. */
#define LINUX_MREMAP_MAYMOVE 1
#define LINUX_MREMAP_FIXED 2

/* Free-tree node covering [base, base+len) entirely, or VMA_NIL. Bounded
 * explicit-stack walk like the mmap best-fit search above. */
static vma_node_t *vma_free_cover(unsigned long base, unsigned long len) {
    unsigned long end = base + len;
    vma_node_t *stack[64];
    int sp = 0;
    vma_node_t *x = vma_free_root;
    while (x != VMA_NIL || sp > 0) {
        while (x != VMA_NIL) {
            if (sp < 64) stack[sp++] = x;
            x = x->left;
        }
        x = stack[--sp];
        if (x->base <= base && end - x->base <= x->len)
            return x;
        x = x->right;
    }
    return VMA_NIL;
}

/* 1 when any live node intersects [base, base+len). Bounded walk. */
static int vma_live_overlap(unsigned long base, unsigned long len) {
    unsigned long end = base + len;
    vma_node_t *stack[64];
    int sp = 0;
    vma_node_t *x = vma_live_root;
    while (x != VMA_NIL || sp > 0) {
        while (x != VMA_NIL) {
            if (sp < 64) stack[sp++] = x;
            x = x->left;
        }
        x = stack[--sp];
        if (x->base < end && base < x->base + x->len)
            return 1;
        x = x->right;
    }
    return 0;
}

/* Linux mremap(25): resize or move one mmap region. glibc's realloc calls
 * it when growing large mmap'd chunks (the file-browser PNG preview hits
 * it three times per wallpaper decode), so ENOSYS here silently breaks
 * every big realloc even though malloc has no fallback left. The old
 * mapping is one exact live VMA node (what mmap inserts); anything else
 * is EFAULT, never a partial move. Shrink splits precisely, grow extends
 * in place when the adjacent pages are free, otherwise MAYMOVE relocates
 * (copy + free old, old untouched on ENOMEM) and FIXED relocates only to
 * a free-covered target. new_size 0 unmaps like munmap. */
static long sys_linux_mremap(long a1, long a2, long a3, long a4, long a5, long a6) {
    unsigned long old = (unsigned long)a1;
    unsigned long old_len = ALIGN_UP((unsigned long)a2, 0x1000);
    unsigned long new_len = ALIGN_UP((unsigned long)a3, 0x1000);
    unsigned long flags = (unsigned long)a4;
    unsigned long fixed = (unsigned long)a5;
    unsigned long fnd_base = 0, fnd_len = 0;
    int fnd_file = 0;
    int fnd_ino = -1;
    unsigned long fnd_off = 0;
    irqflags_t mflags;
    vma_node_t *fnd;
    long ret;
    (void)a6;
    if (old & 0xFFFUL) return -22;
    if (flags & ~(unsigned long)(LINUX_MREMAP_MAYMOVE | LINUX_MREMAP_FIXED))
        return -22;
    if ((flags & LINUX_MREMAP_FIXED) && !(flags & LINUX_MREMAP_MAYMOVE))
        return -22;
    if (old_len == 0 || old_len > USER_LOAD_END - USER_LOAD_BASE) return -22;
    SANITIZE_RANGE(a1, old_len);
    if (new_len == 0) {
        spin_lock_irqsave(&mm_lock, &mflags);
        fnd = vma_tree_find(vma_live_root, old);
        ret = -14;
        if (fnd != VMA_NIL && old_len <= fnd->len) {
            if (fnd->f_file)
                mm_file_range_release(0, fnd->base, fnd->len, fnd->f_ino,
                    fnd->f_off, 1);
            else
                mm_anon_release(0, fnd->base, fnd->len);
            vma_tree_insert(&vma_free_root, fnd->base, fnd->len);
            vma_tree_delete(&vma_live_root, old);
            ret = (long)old;
        }
        spin_unlock_irqrestore(&mm_lock, mflags);
        return ret;
    }
    if (new_len > USER_LOAD_END - USER_LOAD_BASE) return -12;
    if ((flags & LINUX_MREMAP_FIXED) != 0) {
        if (fixed & 0xFFFUL) return -22;
        SANITIZE_RANGE(a5, new_len);
    }
    spin_lock_irqsave(&mm_lock, &mflags);
    fnd = vma_tree_find(vma_live_root, old);
    ret = -14;
    if (fnd == VMA_NIL || old_len > fnd->len) goto mremap_out;
    fnd_base = fnd->base;
    fnd_len = fnd->len;
    fnd_file = fnd->f_file;
    fnd_ino = fnd->f_ino;
    fnd_off = fnd->f_off;
    if (new_len <= fnd_len && new_len <= old_len) {
        unsigned long tail = fnd_len - new_len;
        unsigned long tail_base = fnd_base + new_len;
        vma_node_t *shrunk = VMA_NIL;
        vma_tree_delete(&vma_live_root, old);
        shrunk = vma_tree_insert(&vma_live_root, old, new_len);
        if (shrunk == VMA_NIL) {
            vma_node_t *restored =
                vma_tree_insert(&vma_live_root, fnd_base, fnd_len);
            if (restored != VMA_NIL && fnd_file) {
                restored->f_file = 1;
                restored->f_ino = fnd_ino;
                restored->f_off = fnd_off;
            }
            ret = -12;
            goto mremap_out;
        }
        if (fnd_file) {
            shrunk->f_file = 1;
            shrunk->f_ino = fnd_ino;
            shrunk->f_off = fnd_off;
            if (tail > 0) {
                mm_file_range_release(0, tail_base, tail, fnd_ino,
                    fnd_off + new_len, 1);
            }
        }
        if (tail > 0 && !fnd_file)
            mm_anon_release(0, tail_base, tail);
        if (tail > 0)
            vma_tree_insert(&vma_free_root, tail_base, tail);
        ret = (long)old;
        goto mremap_out;
    }
    if (new_len <= fnd_len) {
        ret = (long)old;
        goto mremap_out;
    }
    {
        proc_t *mp = (current_pid >= 0 && current_pid < MAX_PROCS) ? &procs[current_pid] : 0;
        if (mp && mp->rl_as_max) {
            unsigned long used = 0;
            if (g_brk > USER_LOAD_BASE) used += g_brk - USER_LOAD_BASE;
            if (USER_BRK_END > user_mmap_cur) used += USER_BRK_END - user_mmap_cur;
            if (used + (new_len - old_len) > mp->rl_as_max) {
                ret = -12;
                goto mremap_out;
            }
        }
    }
    if ((flags & LINUX_MREMAP_FIXED) != 0 && fixed != old) {
        vma_node_t *cov = vma_free_cover(fixed, new_len);
        unsigned long move_n = old_len < new_len ? old_len : new_len;
        unsigned long cb, cl, rem;
        if (cov == VMA_NIL || vma_live_overlap(fixed, new_len)) {
            ret = -12;
            goto mremap_out;
        }
        /* File mappings never move by bytes: the destination would be
         * a private snapshot instead of the shared pages, silently
         * breaking every other mapper. Refuse; shrink/grow keep the
         * tags and stay shared. */
        if (fnd_file) {
            ret = -22;
            goto mremap_out;
        }
        cb = cov->base;
        cl = cov->len;
        rem = (cb + cl) - (fixed + new_len);
        if (mm_ensure_cur(fixed, fixed + new_len)) {
            ret = -12;
            goto mremap_out;
        }
        vma_tree_delete(&vma_free_root, cb);
        if (fixed > cb)
            vma_tree_insert(&vma_free_root, cb, fixed - cb);
        if (rem > 0)
            vma_tree_insert(&vma_free_root, fixed + new_len, rem);
        if (vma_tree_insert(&vma_live_root, fixed, new_len) == VMA_NIL) {
            if (fixed > cb)
                vma_tree_delete(&vma_free_root, cb);
            if (rem > 0)
                vma_tree_delete(&vma_free_root, fixed + new_len);
            vma_tree_insert(&vma_free_root, cb, cl);
            ret = -12;
            goto mremap_out;
        }
        kmemcpy((void *)fixed, (void *)old, move_n);
        if (!fnd_file) mm_anon_release(0, fnd_base, fnd_len);
        vma_tree_insert(&vma_free_root, fnd_base, fnd_len);
        vma_tree_delete(&vma_live_root, old);
        ret = (long)fixed;
        goto mremap_out;
    }
    {
        unsigned long delta = new_len - fnd_len;
        unsigned long adj = fnd_base + fnd_len;
        vma_node_t *cov = VMA_NIL;
        if (delta <= USER_LOAD_END - adj)
            cov = vma_free_cover(adj, delta);
        if (cov != VMA_NIL) {
            unsigned long cb = cov->base, cl = cov->len;
            unsigned long rem_base = adj + delta;
            unsigned long rem_len = (cb + cl) - rem_base;
            unsigned long grown = fnd_len + delta;
            vma_node_t *big = VMA_NIL;
            vma_node_t *restored = VMA_NIL;
            vma_tree_delete(&vma_live_root, old);
            big = vma_tree_insert(&vma_live_root, old, grown);
            if (big == VMA_NIL) {
                restored = vma_tree_insert(&vma_live_root, fnd_base,
                    fnd_len);
                if (restored != VMA_NIL && fnd_file) {
                    restored->f_file = 1;
                    restored->f_ino = fnd_ino;
                    restored->f_off = fnd_off;
                }
                ret = -12;
                goto mremap_out;
            }
            if (fnd_file) {
                big->f_file = 1;
                big->f_ino = fnd_ino;
                big->f_off = fnd_off;
            }
            vma_tree_delete(&vma_free_root, cb);
            if (rem_len > 0)
                vma_tree_insert(&vma_free_root, rem_base, rem_len);
            if (mm_ensure_cur(adj, adj + delta)) {
                vma_tree_delete(&vma_live_root, old);
                vma_tree_insert(&vma_live_root, fnd_base, fnd_len);
                if (rem_len > 0)
                    vma_tree_delete(&vma_free_root, rem_base);
                vma_tree_insert(&vma_free_root, cb, cl);
                ret = -12;
                goto mremap_out;
            }
            ret = (long)old;
            goto mremap_out;
        }
    }
    if (!(flags & LINUX_MREMAP_MAYMOVE)) {
        ret = -12;
        goto mremap_out;
    }
    {
        unsigned long n = new_len;
        unsigned long addr = 0;
        unsigned long move_n = old_len < new_len ? old_len : new_len;
        unsigned long rb = 0, rl = 0, rem = 0;
        int carved = 0;
        vma_node_t *best = VMA_NIL;
        vma_node_t *stack[64];
        int sp = 0;
        vma_node_t *x = vma_free_root;
        while (x != VMA_NIL || sp > 0) {
            while (x != VMA_NIL) {
                if (sp < 64) stack[sp++] = x;
                x = x->left;
            }
            x = stack[--sp];
            if (x->len >= n && (best == VMA_NIL || x->base < best->base))
                best = x;
            x = x->right;
        }
        if (best != VMA_NIL) {
            rb = best->base;
            rl = best->len;
            rem = rl - n;
            addr = rb + rem;
            vma_tree_delete(&vma_free_root, rb);
            if (rem > 0)
                vma_tree_insert(&vma_free_root, rb, rem);
            carved = 1;
        } else {
            if (n > user_mmap_cur - USER_LOAD_BASE || user_mmap_cur - n < g_brk) {
                ret = -12;
                goto mremap_out;
            }
            user_mmap_cur -= n;
            addr = user_mmap_cur;
        }
        if (mm_ensure_cur(addr, addr + n)) {
            if (carved) {
                if (rem > 0)
                    vma_tree_delete(&vma_free_root, rb);
                vma_tree_insert(&vma_free_root, rb, rl);
            } else {
                user_mmap_cur += n;
            }
            ret = -12;
            goto mremap_out;
        }
        if (vma_tree_insert(&vma_live_root, addr, n) == VMA_NIL) {
            if (carved) {
                if (rem > 0)
                    vma_tree_delete(&vma_free_root, rb);
                vma_tree_insert(&vma_free_root, rb, rl);
            } else {
                user_mmap_cur += n;
            }
            ret = -12;
            goto mremap_out;
        }
        kmemcpy((void *)addr, (void *)old, move_n);
        if (!fnd_file) mm_anon_release(0, fnd_base, fnd_len);
        vma_tree_insert(&vma_free_root, fnd_base, fnd_len);
        vma_tree_delete(&vma_live_root, old);
        ret = (long)addr;
    }
mremap_out:
    spin_unlock_irqrestore(&mm_lock, mflags);
    return ret;
}

static long sys_linux_sigaction(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return 0;
}

static long sys_linux_sigprocmask(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return 0;
}

#define LINUX_TCGETS     0x5401
#define LINUX_TIOCGWINSZ 0x5413
#define LINUX_FIONREAD   0x541B
#define LINUX_FIONBIO    0x5421
#define LINUX_FIONCLEX   0x5450
#define LINUX_FIOCLEX    0x5451
#define LINUX_TCGETS2    0x802C542AL
#define LINUX_ENOTTY     25
#define LINUX_WINSIZE_LEN 8
#define LINUX_TERMIOS_LEN  36
#define LINUX_TERMIOS2_LEN 44
#define LINUX_IOCTL_INT  ((unsigned long)sizeof(int))

/* Bytes a read of f would return now (FIONREAD). */
static int kfile_readable_bytes(KFILE *f) {
    unsigned avail = 0;
    if (f->is_eventfd) return f->efd_count ? (int)sizeof(f->efd_count) : 0;
    if (f->is_pipe) {
        if (kpipe_state(f, &avail, 0, 0, 0) != 0) return 0;
        return (int)avail;
    }
    if (f->rf) return f->pos < f->rf->size ? (int)(f->rf->size - f->pos) : 0;
    if (f->minifs_ino >= 0) return f->pos < f->minifs_size ? (int)(f->minifs_size - f->pos) : 0;
    return 0;
}

/* Linux ioctl(16). The console (fds 0-2 with no redirection) is the one
 * terminal: TCGETS/TCGETS2 succeed (isatty) with a zeroed attribute block
 * of the caller's size, TIOCGWINSZ answers the console geometry, and every
 * other request is accepted as before. Every other
 * descriptor answers FIONREAD (bytes readable now), FIONBIO (O_NONBLOCK),
 * FIOCLEX/FIONCLEX (FD_CLOEXEC), and ENOTTY for terminal and unknown
 * requests, never a silent success that leaves the caller's buffer
 * uninitialized. Sockets answer through net_sys_ioctl. */
static long sys_linux_ioctl(long a1, long a2, long a3, long a4, long a5, long a6) {
    KFILE *f;
    long r;
    (void)a4; (void)a5; (void)a6;
    if (a2 == LINUX_FIONREAD || a2 == LINUX_FIONBIO) { SANITIZE_RANGE(a3, LINUX_IOCTL_INT); }
    if (net_sys_is_socket(a1)) return net_sys_ioctl(a1, a2, a3);
    if (a1 < 0 || a1 >= KFD_MAX) return -9;
    f = kfd_get((int)a1);
    if (!f) {
        if (a1 >= FD_STD_COUNT) return -9;
        if (a2 == LINUX_TCGETS || a2 == LINUX_TCGETS2) {
            unsigned long len = a2 == LINUX_TCGETS ? LINUX_TERMIOS_LEN : LINUX_TERMIOS2_LEN;
            SANITIZE_RANGE(a3, len);
            kmemset((void *)a3, 0, len);
        }
        if (a2 == LINUX_TIOCGWINSZ) {
            unsigned short *ws = (unsigned short *)a3;
            SANITIZE_RANGE(a3, LINUX_WINSIZE_LEN);
            ws[0] = (unsigned short)term_rows;
            ws[1] = (unsigned short)term_cols;
            ws[2] = 0;
            ws[3] = 0;
        }
        return 0;
    }
    switch (a2) {
    case LINUX_FIONREAD: *(int *)a3 = kfile_readable_bytes(f); r = 0; break;
    case LINUX_FIONBIO: f->nonblock = *(const int *)a3 != 0; r = 0; break;
    case LINUX_FIOCLEX: kfd_cloexec_set(a1, 1); r = 0; break;
    case LINUX_FIONCLEX: kfd_cloexec_set(a1, 0); r = 0; break;
    default: r = -LINUX_ENOTTY; break;
    }
    kfd_put(f);
    return r;
}

static long sys_linux_access(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    const char *path = (const char *)a1;
    SANITIZE_STR(path, RAMDISK_FNAME_LEN);
    char resolved[RAMDISK_FNAME_LEN];
    if (!fs_resolve(path, resolved, sizeof(resolved))) return -2;
    RDFile *f = ramdisk_open(resolved);
    if (f) return 0;
    if (minifs_is_mounted()) {
        int ino = minifs_resolve_path(resolved);
        if (ino < 0 && kstrchr(resolved, '/')) {
            const char *base = resolved;
            const char *p;
            for (p = resolved; *p; p++)
                if (*p == '/') base = p + 1;
            ino = minifs_resolve_path(base);
        }
        if (ino >= 0) return 0;
    }
    return -2;
}

static long sys_linux_socket(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    return net_sys_socket(a1, a2, a3);
}

static long sys_linux_connect(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    SANITIZE_RANGE(a2, 16);
    return net_sys_connect(a1, a2, a3);
}

static long sys_linux_bind(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    SANITIZE_RANGE(a2, 16);
    return net_sys_bind(a1, a2, a3);
}

static long sys_linux_listen(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return net_sys_listen(a1, a2);
}

static long sys_linux_accept(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    if (a2 && a3 >= 16) { SANITIZE_RANGE(a2, 16); }
    return net_sys_accept(a1, a2, a3);
}

static long sys_linux_sendto(long a1, long a2, long a3, long a4, long a5, long a6) {
    if (a3 > 0) { SANITIZE_RANGE(a2, (unsigned long)a3); }
    return net_sys_sendto(a1, a2, a3, a4, a5, a6);
}

static long sys_linux_recvfrom(long a1, long a2, long a3, long a4, long a5, long a6) {
    if (a3 > 0) { SANITIZE_RANGE(a2, (unsigned long)a3); }
    return net_sys_recvfrom(a1, a2, a3, a4, a5, a6);
}

static long sys_linux_shutdown(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    return net_sys_shutdown(a1, a2);
}

#define LINUX_RLIMIT_CPU      0
#define LINUX_RLIMIT_STACK    3
#define LINUX_RLIMIT_NOFILE   7
#define LINUX_RLIMIT_AS       9
#define LINUX_RLIMIT_NLIMITS  16
#define LINUX_RLIM_INFINITY   (~0UL)
#define LINUX_RLIMIT_PAIR     (2 * sizeof(unsigned long))
/* RLIMIT_CPU is counted in scheduler ticks (the 100 Hz PIT). */
#define LINUX_RLIMIT_TICKS_PER_S 100UL
#define LINUX_CPUMASK_BYTES   ((unsigned long)sizeof(unsigned long))

/* One resource's limits as Linux reports them: the real main stack size
 * for RLIMIT_STACK (glibc sizes every thread stack from it, so the old
 * "unlimited" made each thread reserve 8 MB of a ~140 MB window), the
 * per-process MiniOS limits for NOFILE, AS and CPU (CPU counted in ticks
 * here, reported in seconds), infinity for the rest. */
static void linux_rlimit_get(const proc_t *p, long res, unsigned long out[2]) {
    unsigned long v = LINUX_RLIM_INFINITY;
    if (res == LINUX_RLIMIT_STACK) v = MINIOS_USER_STACK_SIZE;
    else if (res == LINUX_RLIMIT_NOFILE) v = p->rl_nofile_max ? p->rl_nofile_max : KFD_MAX;
    else if (res == LINUX_RLIMIT_AS && p->rl_as_max) v = p->rl_as_max;
    else if (res == LINUX_RLIMIT_CPU && p->rl_cpu_max) v = p->rl_cpu_max / LINUX_RLIMIT_TICKS_PER_S;
    out[0] = v;
    out[1] = v;
}

/* prlimit64(pid, resource, new, old): pid 0 or a live pid. Setting NOFILE
 * (at most KFD_MAX), AS and CPU updates the MiniOS limit; the stack is
 * fixed by the window layout, so only a value at or below it is accepted
 * (and changes nothing). */
static long sys_linux_prlimit64(long a1, long a2, long a3, long a4, long a5, long a6) {
    proc_t *p;
    (void)a5; (void)a6;
    p = proc_get(a1 == 0 ? current_pid : (int)a1);
    if (!p || a1 < 0) return -3;
    if (a2 < 0 || a2 >= LINUX_RLIMIT_NLIMITS) return -22;
    if (a4) {
        SANITIZE_RANGE(a4, LINUX_RLIMIT_PAIR);
        linux_rlimit_get(p, a2, (unsigned long *)a4);
    }
    if (a3) {
        const unsigned long *nv = (const unsigned long *)a3;
        unsigned long cur;
        SANITIZE_RANGE(a3, LINUX_RLIMIT_PAIR);
        cur = nv[0];
        if (nv[0] > nv[1]) return -22;
        if (a2 == LINUX_RLIMIT_NOFILE) {
            if (cur != LINUX_RLIM_INFINITY && cur > KFD_MAX) return -1;
            p->rl_nofile_max = cur == LINUX_RLIM_INFINITY ? 0 : cur;
        } else if (a2 == LINUX_RLIMIT_AS) {
            p->rl_as_max = cur == LINUX_RLIM_INFINITY ? 0 : cur;
        } else if (a2 == LINUX_RLIMIT_CPU) {
            p->rl_cpu_max = cur == LINUX_RLIM_INFINITY ? 0 : cur * LINUX_RLIMIT_TICKS_PER_S;
        } else if (a2 == LINUX_RLIMIT_STACK) {
            if (cur != LINUX_RLIM_INFINITY && cur > MINIOS_USER_STACK_SIZE) return -1;
        }
    }
    return 0;
}

/* sched_getaffinity(pid, size, mask): every task may run on every CPU,
 * so the mask has the low cpu_count bits set; the return value is the
 * mask size written, as Linux reports it. */
static long sys_linux_sched_getaffinity(long a1, long a2, long a3, long a4, long a5, long a6) {
    unsigned long mask;
    (void)a4; (void)a5; (void)a6;
    if (a1 < 0 || (a1 != 0 && !proc_get((int)a1))) return -3;
    if (a2 < (long)LINUX_CPUMASK_BYTES || (a2 & (long)(LINUX_CPUMASK_BYTES - 1))) return -22;
    SANITIZE_RANGE(a3, LINUX_CPUMASK_BYTES);
    mask = cpu_count >= (int)(8 * LINUX_CPUMASK_BYTES) ? ~0UL : ((1UL << cpu_count) - 1UL);
    *(unsigned long *)a3 = mask;
    return (long)LINUX_CPUMASK_BYTES;
}

#define LINUX_CLOCK_REALTIME  0
#define LINUX_CLOCK_MONOTONIC 1
#define LINUX_CLOCK_BOOTTIME  7
#define LINUX_TIMER_ABSTIME   1
#define LINUX_NS_PER_US       1000L
#define LINUX_US_PER_S        1000000L
#define LINUX_NS_PER_S        1000000000L
#define LINUX_SLEEP_MAX_S     (0x7fffffffffffffffL / LINUX_US_PER_S - 1)

/* Microseconds of a user timespec, or -EINVAL when it is malformed
 * (negative, or tv_nsec outside [0, 1e9)); huge intervals saturate. */
static long linux_timespec_us(long ts) {
    long sec = ((const long *)ts)[0];
    long nsec = ((const long *)ts)[1];
    if (sec < 0 || nsec < 0 || nsec >= LINUX_NS_PER_S) return -22;
    if (sec > LINUX_SLEEP_MAX_S) sec = LINUX_SLEEP_MAX_S;
    return sec * LINUX_US_PER_S + nsec / LINUX_NS_PER_US;
}

/* Wait, yielding, until the clock read by now() reaches deadline_us. No
 * signal handlers exist, so nothing interrupts the wait: rem is never
 * written (Linux writes it only on EINTR). */
static void linux_sleep_until(unsigned long (*now)(void), unsigned long deadline_us) {
    while (now() < deadline_us) yield();
}

/* pause(34): wait for a signal. MiniOS installs no handlers, so the only
 * signal that ends the wait is a fatal one, which ends the caller. */
static long sys_linux_pause(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    for (;;) yield();
    return 0;
}

/* nanosleep(35): sleep the relative interval at *req on the monotonic
 * clock; -EINVAL for a malformed interval, -EFAULT for a bad pointer. */
static long sys_linux_nanosleep(long a1, long a2, long a3, long a4, long a5, long a6) {
    long us;
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    SANITIZE_RANGE(a1, 2 * sizeof(long));
    us = linux_timespec_us(a1);
    if (us < 0) return us;
    linux_sleep_until(ktime_us, ktime_us() + (unsigned long)us);
    return 0;
}

/* clock_nanosleep(230): a relative interval is elapsed time whatever the
 * clock (the monotonic TSC clock times it, as Linux does: glibc sends
 * every nanosleep here as a relative CLOCK_REALTIME sleep); TIMER_ABSTIME
 * waits for the named clock to reach the deadline: CLOCK_REALTIME on the
 * wall clock, CLOCK_MONOTONIC and CLOCK_BOOTTIME on the TSC clock that
 * clock_gettime(1) reads. */
static long sys_linux_clock_nanosleep(long a1, long a2, long a3, long a4, long a5, long a6) {
    unsigned long (*now)(void);
    long us;
    (void)a4; (void)a5; (void)a6;
    if (a1 == LINUX_CLOCK_REALTIME) now = wall_us_now;
    else if (a1 == LINUX_CLOCK_MONOTONIC || a1 == LINUX_CLOCK_BOOTTIME) now = ktime_us;
    else return -22;
    if (a2 & ~(long)LINUX_TIMER_ABSTIME) return -22;
    SANITIZE_RANGE(a3, 2 * sizeof(long));
    us = linux_timespec_us(a3);
    if (us < 0) return us;
    if (a2 & LINUX_TIMER_ABSTIME) linux_sleep_until(now, (unsigned long)us);
    else linux_sleep_until(ktime_us, ktime_us() + (unsigned long)us);
    return 0;
}

static long sys_linux_setsockopt(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a6;
    if (a5 < 0) return -22;
    if (a5 > 0) { SANITIZE_RANGE(a4, (unsigned long)a5); }
    return net_sys_setsockopt(a1, a2, a3, a4, a5);
}

static long sys_linux_getsockopt(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a6;
    SANITIZE_RANGE(a5, sizeof(int));
    SANITIZE_RANGE(a4, sizeof(int));
    return net_sys_getsockopt(a1, a2, a3, a4, a5);
}

static long sys_linux_getsockname(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    SANITIZE_RANGE(a3, sizeof(int));
    return net_sys_getsockname(a1, a2, a3);
}

static long sys_linux_getpeername(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    SANITIZE_RANGE(a3, sizeof(int));
    return net_sys_getpeername(a1, a2, a3);
}

static long sys_linux_sendmsg(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    SANITIZE_RANGE(a2, NET_MSGHDR_LEN);
    return net_sys_sendmsg(a1, a2, a3);
}

static long sys_linux_sendmmsg(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a5; (void)a6;
    if (a3 < 0) return -22;
    if (a3 > NET_MMSG_MAX) a3 = NET_MMSG_MAX;
    if (a3 > 0) { SANITIZE_RANGE(a2, (unsigned long)a3 * NET_MMSGHDR_LEN); }
    return net_sys_sendmmsg(a1, a2, a3, a4);
}

static long sys_linux_poll(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    if (a2 < 0 || (unsigned long)a2 > (USER_LOAD_END - USER_LOAD_BASE) / 8) return -22;
    if (a2 > 0) { SANITIZE_RANGE(a1, (unsigned long)a2 * 8); }
    return net_sys_poll(a1, a2, a3);
}

static long sys_linux_flock(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return 0;
}

/* fsync/fdatasync: the ramdisk is memory (always durable) and MiniFS
 * persists through kfclose/minifs_sync, so there is nothing to flush
 * that close would not already flush. Success is truthful here, not a
 * lie: no write-back cache sits between the caller and the medium. */
static long sys_linux_fsync(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return 0;
}

static long sys_linux_fdatasync(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return 0;
}

static long sys_linux_getcwd(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    char *buf = (char *)a1;
    unsigned long sz = (unsigned long)a2;
    if (!buf || sz == 0) return -22;
    SANITIZE_RANGE(buf, sz);
    unsigned long cwd_len = (unsigned long)kstrlen(fs_cwd);
    if (sz < cwd_len + 1) return -34;
    for (unsigned long i = 0; i <= cwd_len; i++) buf[i] = fs_cwd[i];
    return (long)(cwd_len + 1);
}

static long sys_linux_unlink(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    const char *path = (const char *)a1;
    SANITIZE_STR(path, RAMDISK_FNAME_LEN);
    char resolved[RAMDISK_FNAME_LEN];
    if (!fs_resolve(path, resolved, sizeof(resolved))) return -36;
    if (fs_is_dir(resolved)) return -21;
    {
        irqflags_t flags;
        int r = -2;
        spin_lock_irqsave(&fs_lock, &flags);
        RDFile *f = ramdisk_open(resolved);
        if (f) { ramdisk_delete(f); r = 0; }
        else if (minifs_is_mounted() && minifs_unlink(resolved) == 0) r = 0;
        spin_unlock_irqrestore(&fs_lock, flags);
        return r;
    }
}

#define PROC_SELF_EXE "/proc/self/exe"

/* readlink of /proc/self/exe answers the caller's image path (absolute,
 * no NUL, truncated to the buffer like Linux); MiniOS has no other links,
 * so every other path is -EINVAL. */
static long readlink_path(const char *path, char *buf, long bufsz) {
    const char *exe;
    long len, i;
    SANITIZE_STR(path, RAMDISK_FNAME_LEN);
    if (kstrcmp(path, PROC_SELF_EXE) != 0) return -22;
    if (bufsz <= 0) return -22;
    SANITIZE_RANGE(buf, (unsigned long)bufsz);
    exe = proc_sec_exe(current_pid);
    if (!exe[0]) return -2;
    len = (long)kstrlen(exe) + 1;
    if (len > bufsz) len = bufsz;
    buf[0] = '/';
    for (i = 1; i < len; i++) buf[i] = exe[i - 1];
    return len;
}

static long sys_linux_readlink(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    return readlink_path((const char *)a1, (char *)a2, a3);
}

/* prctl (157): no_new_privs, dumpable, name and seccomp (proc_sec.c). */
static long sys_linux_prctl(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a6;
    return proc_sec_prctl(a1, a2, a3, a4, a5);
}

/* rename(82): same-filesystem file move through fs_rename (ramdisk
 * in-place, MiniFS entry move). Both paths sanitize as user strings and
 * resolve against the shell cwd like unlink; directories, existing dst
 * and cross-filesystem dsts refuse with their errno, never half-moved. */
static long sys_linux_rename(long a1, long a2, long a3, long a4, long a5, long a6) {
    const char *oldp = (const char *)a1;
    const char *newp = (const char *)a2;
    (void)a3; (void)a4; (void)a5; (void)a6;
    SANITIZE_STR(oldp, RAMDISK_FNAME_LEN);
    SANITIZE_STR(newp, RAMDISK_FNAME_LEN);
    {
        char oldr[RAMDISK_FNAME_LEN], newr[RAMDISK_FNAME_LEN];
        if (!fs_resolve(oldp, oldr, sizeof(oldr))) return -36;
        if (!fs_resolve(newp, newr, sizeof(newr))) return -36;
        return fs_rename(oldr, newr);
    }
}

static long sys_linux_fstat(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    unsigned long *st = (unsigned long *)a2;
    SANITIZE_RANGE(a2, 144);
    for (int i = 0; i < 18; i++) st[i] = 0;
    if (a1 == 0 || a1 == 1 || a1 == 2) {
        ((unsigned int *)(unsigned long)a2)[6] = 0020666;
    } else {
        ((unsigned int *)(unsigned long)a2)[6] = 0100666;
        {
            KFILE *kf = kfd_get((int)a1);
            if (kf) {
                if (kf->rf)
                    ((unsigned long *)(unsigned long)a2)[6] = (unsigned long)kf->rf->size;
                else if (kf->minifs_ino >= 0)
                    ((unsigned long *)(unsigned long)a2)[6] = (unsigned long)kf->minifs_size;
                kfd_put(kf);
            }
        }
    }
    return 0;
}

static long sys_linux_gettimeofday(long a1, long a2, long a3, long a4, long a5, long a6) {
    /* Wall-clock epoch seconds from the CMOS RTC plus a monotonic
     * microsecond fraction from the calibrated TSC (Phase 0.3). The old
     * code pinned tv_usec to 0, so two calls inside one second compared
     * equal. The fraction is free-running (ktime_us mod 1e6), NOT phase
     * aligned to the RTC second edge: the wall_us_from_parts rebase
     * below re-anchors every RTC second, so ordering holds across the
     * edge instead of inverting for half a second. On RTC failure the
     * fields stay 0/0 and the call still returns 0; TLS treats epoch 0
     * as "no clock" and fails the chain check closed downstream. */
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    if (a1) {
        unsigned long *tv = (unsigned long *)a1;
        SANITIZE_RANGE(a1, 2 * sizeof(unsigned long));
        {
            unsigned long total = wall_us_now();
            tv[0] = total / 1000000UL;
            tv[1] = total % 1000000UL;
        }
    }
    return 0;
}

static long sys_linux_arch_prctl(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    if (a1 == 0x1002 || a1 == 0x1001) {
        unsigned long v = (unsigned long)a2;
        unsigned long sign = (v >> 47) & 1;
        if (((v >> 48) & 0xFFFF) != (sign ? 0xFFFF : 0)) return -22;
        wrmsr(a1 == 0x1002 ? MSR_FSBASE : MSR_GSBASE, v);
        return 0;
    }
    return -22;
}

static long sys_linux_uname(long a1, long a2, long a3, long a4, long a5, long a6) {
    /* Every static glibc binary calls uname(63) during startup; answering
     * ENOSYS printed a scary UNIMPL line for programs that then ran fine.
     * struct utsname is six 65-byte fields (390 total): validate the whole
     * span, zero it, then copy literals that always fit. Honest values,
     * no host facts leaked. */
    char *u;
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    if (!a1) return EFAULT;
    SANITIZE_RANGE(a1, 390);
    u = (char *)a1;
    kmemset(u, 0, 390);
    kstrcpy(u, "MiniOS");
    kstrcpy(u + 65, "minios");
    kstrcpy(u + 130, "1");
    kstrcpy(u + 195, "#1 MiniOS");
    kstrcpy(u + 260, "x86_64");
    kstrcpy(u + 325, "(none)");
    return 0;
}

/* madvise (28): advice only; glibc frees thread stacks with it and
 * ignores the result, MiniOS keeps the pages, so 0 is truthful. */
static long sys_linux_madvise(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return 0;
}

/* mkdir (83): a MiniFS directory. The parent must exist (-ENOENT), an
 * existing name is -EEXIST, the mode is accepted and ignored (MiniFS has
 * no permission bits). Runs under fs_lock like unlink. */
static long sys_linux_mkdir(long a1, long a2, long a3, long a4, long a5, long a6) {
    const char *path = (const char *)a1;
    char resolved[RAMDISK_FNAME_LEN];
    char parent[RAMDISK_FNAME_LEN];
    unsigned len, cut;
    irqflags_t flags;
    int r;
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    SANITIZE_STR(path, RAMDISK_FNAME_LEN);
    if (!fs_resolve(path, resolved, sizeof(resolved))) return -36;
    len = (unsigned)kstrlen(resolved);
    while (len > 0 && resolved[len - 1] == '/') resolved[--len] = 0;
    if (len == 0) return -17;
    if (!minifs_is_mounted()) return -30;
    if (fs_is_dir(resolved) || ramdisk_open(resolved) || minifs_resolve_path(resolved) >= 0)
        return -17;
    cut = len;
    while (cut > 0 && resolved[cut - 1] != '/') cut--;
    if (cut > 0) {
        kmemcpy(parent, resolved, cut);
        parent[cut] = 0;
        if (!fs_dir_exists(parent)) return -2;
    }
    spin_lock_irqsave(&fs_lock, &flags);
    r = minifs_mkdir(resolved, 0755);
    if (r >= 0) minifs_sync();
    spin_unlock_irqrestore(&fs_lock, flags);
    return r >= 0 ? 0 : -5;
}

#define LINUX_SYSCALL_COUNT 200

static const minios_syscall_entry_t linux_syscall_table[LINUX_SYSCALL_COUNT] = {
    [0]   = { sys_linux_read,         "read" },
    [1]   = { sys_linux_write,        "write" },
    [2]   = { sys_linux_open,         "open" },
    [3]   = { sys_linux_close,        "close" },
    [5]   = { sys_linux_fstat,        "fstat" },
    [7]   = { sys_linux_poll,         "poll" },
    [8]   = { sys_linux_lseek,        "lseek" },
    [9]   = { sys_linux_mmap,         "mmap" },
    [10]  = { sys_linux_mprotect,     "mprotect" },
    [11]  = { sys_linux_munmap,       "munmap" },
    [12]  = { sys_linux_brk,          "brk" },
    [13]  = { sys_linux_sigaction,    "sigaction" },
    [14]  = { sys_linux_sigprocmask,  "sigprocmask" },
    [16]  = { sys_linux_ioctl,        "ioctl" },
    [20]  = { sys_linux_writev,       "writev" },
    [21]  = { sys_linux_access,       "access" },
    [22]  = { sys_linux_pipe,         "pipe" },
    [24]  = { sys_linux_yield,        "yield" },
    [25]  = { sys_linux_mremap,       "mremap" },
    [28]  = { sys_linux_madvise,      "madvise" },
    [32]  = { sys_linux_dup,          "dup" },
    [33]  = { sys_linux_dup2,         "dup2" },
    [39]  = { sys_linux_getpid,       "getpid" },
    [41]  = { sys_linux_socket,       "socket" },
    [42]  = { sys_linux_connect,      "connect" },
    [43]  = { sys_linux_accept,       "accept" },
    [44]  = { sys_linux_sendto,       "sendto" },
    [45]  = { sys_linux_recvfrom,     "recvfrom" },
    [34]  = { sys_linux_pause,        "pause" },
    [35]  = { sys_linux_nanosleep,    "nanosleep" },
    [46]  = { sys_linux_sendmsg,      "sendmsg" },
    [48]  = { sys_linux_shutdown,     "shutdown" },
    [49]  = { sys_linux_bind,         "bind" },
    [50]  = { sys_linux_listen,       "listen" },
    [51]  = { sys_linux_getsockname,  "getsockname" },
    [52]  = { sys_linux_getpeername,  "getpeername" },
    [54]  = { sys_linux_setsockopt,   "setsockopt" },
    [55]  = { sys_linux_getsockopt,   "getsockopt" },
    [56]  = { sys_linux_clone,        "clone" },
    [57]  = { sys_linux_fork,         "fork" },
    [58]  = { sys_linux_vfork,        "vfork" },
    [59]  = { sys_linux_execve,       "execve" },
    [60]  = { sys_linux_exit,         "exit" },
    [61]  = { sys_linux_wait4,        "wait4" },
    [62]  = { sys_linux_kill,         "kill" },
    [63]  = { sys_linux_uname,        "uname" },
    [72]  = { sys_linux_fcntl,        "fcntl" },
    [73]  = { sys_linux_flock,        "flock" },
    [74]  = { sys_linux_fsync,        "fsync" },
    [75]  = { sys_linux_fdatasync,    "fdatasync" },
    [79]  = { sys_linux_getcwd,       "getcwd" },
    [82]  = { sys_linux_rename,       "rename" },
    [83]  = { sys_linux_mkdir,        "mkdir" },
    [87]  = { sys_linux_unlink,       "unlink" },
    [89]  = { sys_linux_readlink,     "readlink" },
    [96]  = { sys_linux_gettimeofday, "gettimeofday" },
    [157] = { sys_linux_prctl,        "prctl" },
    [158] = { sys_linux_arch_prctl,   "arch_prctl" },
    [186] = { sys_linux_gettid,       "gettid" },
};

static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6);

static int trace_is_noisy(long n) {
    return n == SYS_NOISY_TIME || n == SYS_NOISY_KBD || n == SYS_NOISY_MOUSE ||
           n == SYS_NOISY_GETC_RAW;
}

/* strace-style name resolver: Linux table first, then the MiniOS window,
 * then the out-of-table Linux numbers the dispatcher answers (openat,
 * newfstatat, clock_gettime, ...). The tail is a data table, not a switch:
 * a `case N:` ladder would trip tools/check_abi_numbers.py (its CASE_RE
 * parses every `case N:` in this file as a dispatch site) and forces a
 * comment per number to satisfy Rule C. Unknown numbers stay numeric so a
 * new stub never prints a wrong name. */
struct sc_extra_name { long n; const char *name; };
static const struct sc_extra_name sc_extra_names[] = {
    { 4, "stat" }, { 6, "lstat" }, { 15, "rt_sigreturn" },
    { 17, "pread64" }, { 18, "pwrite64" },
    { 23, "select" },
 { 78, "getdents" },
    { 97, "getrlimit" }, { 102, "getuid" }, { 104, "getgid" },
    { 107, "geteuid" }, { 108, "getegid" },
    { 159, "getcpu" }, { 218, "set_tid_address" },
    { 228, "clock_gettime" }, { 231, "exit_group" }, { 234, "tgkill" },
    { 257, "openat" }, { 262, "newfstatat" }, { 267, "readlinkat" },
    { 273, "set_robust_list" }, { 302, "prlimit64" }, { 318, "getrandom" },
    { 332, "statx" }, { 334, "rseq" },
};
#define SC_EXTRA_COUNT (sizeof(sc_extra_names) / sizeof(sc_extra_names[0]))
const char *syscall_name(long n) {
    unsigned i;
    if (n >= 0 && n < LINUX_SYSCALL_COUNT && linux_syscall_table[n].name)
        return linux_syscall_table[n].name;
    if (n >= MINIOS_SYSCALL_BASE &&
        n < MINIOS_SYSCALL_BASE + MINIOS_SYSCALL_COUNT &&
        minios_syscall_table[n - MINIOS_SYSCALL_BASE].name)
        return minios_syscall_table[n - MINIOS_SYSCALL_BASE].name;
    for (i = 0; i < SC_EXTRA_COUNT; i++)
        if (sc_extra_names[i].n == n) return sc_extra_names[i].name;
    return 0;
}

/* Verbose-tracer hint, split in two halves so a traced line never
 * interleaves with the program's own output. The snapshot runs BEFORE
 * dispatch (the only moment user memory may be read: a path argument is
 * copied, at most 48 bytes, only after user_str_ok, non-printables
 * folded to '?', "<bad-ptr>" when it does not validate). The print runs
 * AFTER dispatch returns, so `syscall write(...) "..." = N` lands as one
 * atomic line after the program's bytes instead of wrapping them. Scalar
 * hints (code=/addr=/len=/fd/pid=) need no snapshot and print post-hoc. */
#define TRACE_HINT_NONE 0
#define TRACE_HINT_PATH 1
static int trace_hint_snapshot(long n, long a1, long a2, char *out) {
    const char *p = 0;
    unsigned long i;
    if (n == 2 || n == 21 || n == 82 || n == 87 || n == 89) p = (const char *)a1;
    else if (n == 257 || n == 262) p = (const char *)a2;
    else return TRACE_HINT_NONE;
    if (!user_str_ok((unsigned long)p, 49)) {
        out[0] = '<'; out[1] = 'b'; out[2] = 'a'; out[3] = 'd';
        out[4] = '-'; out[5] = 'p'; out[6] = 't'; out[7] = 'r';
        out[8] = '>'; out[9] = 0;
        return TRACE_HINT_PATH;
    }
    for (i = 0; i < 48 && p[i]; i++)
        out[i] = (p[i] < 32 || p[i] > 126) ? '?' : p[i];
    out[i] = 0;
    return TRACE_HINT_PATH;
}

static void trace_hint_print(long n, int kind, const char *path,
                             long a1, long a2, long a3) {
    if (kind == TRACE_HINT_PATH) {
        kprintf(" \"%s\"", path);
        return;
    }
    if (n == 60 || n == 231) kprintf(" code=%ld", a1);
    else if (n == 12) kprintf(" addr=0x%lx", (unsigned long)a1);
    else if (n == 9) kprintf(" len=%ld", a2);
    else if (n == 0 || n == 1) kprintf(" fd=%ld len=%ld", a1, a3);
    else if (n == 62 || n == 61) kprintf(" pid=%ld", a1);
}

/* Syscall flight recorder: each process's last SC_RECORD_LEN syscalls
 * (number, first three arguments, result), written on every call with no
 * I/O so it never perturbs timing the way tracing does. Per process, so a
 * busy poll loop elsewhere cannot flush a dying worker's history; kept
 * after exit until the slot is reused. The exception dump prints the
 * faulting process's log and `sclog <pid>` any process's. Heap-owned. */
#define SC_RECORD_LEN 32
struct sc_record { long n, a1, a2, a3, ret; };
struct sc_log { unsigned long next; struct sc_record r[SC_RECORD_LEN]; };
static struct sc_log *sc_logs;

static void sc_record(long n, long a1, long a2, long a3, long ret) {
    struct sc_log *l;
    struct sc_record *e;
    int pid = current_pid;
    if (pid < 0 || pid >= MAX_PROCS) return;
    if (!sc_logs) {
        struct sc_log *t = (struct sc_log *)kmalloc(MAX_PROCS * sizeof(struct sc_log));
        if (!t) return;
        kmemset(t, 0, MAX_PROCS * sizeof(struct sc_log));
        if (__sync_val_compare_and_swap(&sc_logs, (struct sc_log *)0, t) != 0) kfree(t);
    }
    l = &sc_logs[pid];
    e = &l->r[__sync_fetch_and_add(&l->next, 1UL) % SC_RECORD_LEN];
    e->n = n;
    e->a1 = a1;
    e->a2 = a2;
    e->a3 = a3;
    e->ret = ret;
}

static void sc_hex(unsigned long v) {
    static const char digits[] = "0123456789abcdef";
    char h[17];
    int i;
    for (i = 15; i >= 0; i--) { h[i] = digits[v & 0xF]; v >>= 4; }
    h[16] = 0;
    serial_puts(h);
}

/* Serial-only, safe from the exception path: pid's log, oldest first. */
void sc_record_dump(int pid) {
    const struct sc_log *l;
    unsigned long start, k;
    if (!sc_logs || pid < 0 || pid >= MAX_PROCS) return;
    l = &sc_logs[pid];
    start = l->next > SC_RECORD_LEN ? l->next - SC_RECORD_LEN : 0;
    serial_puts("  last syscalls (n a1 a2 a3 = ret):\n");
    for (k = start; k < l->next; k++) {
        const struct sc_record *r = &l->r[k % SC_RECORD_LEN];
        serial_puts("   ");
        sc_hex((unsigned long)r->n); serial_puts(" ");
        sc_hex((unsigned long)r->a1); serial_puts(" ");
        sc_hex((unsigned long)r->a2); serial_puts(" ");
        sc_hex((unsigned long)r->a3); serial_puts(" = ");
        sc_hex((unsigned long)r->ret); serial_puts("\n");
    }
}

long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
    long ret;
    int show = s_trace_enabled && !trace_is_noisy(n);
    const char *nm = 0;
    char path_hint[49];
    int hint = TRACE_HINT_NONE;
    path_hint[0] = 0;
    if (show && s_trace_verbose) {
        nm = syscall_name(n);
        if (nm) hint = trace_hint_snapshot(n, a1, a2, path_hint);
    }
    ret = ksyscall_dispatch(n, a1, a2, a3, a4, a5, a6);
    sc_record(n, a1, a2, a3, ret);
    if (show) {
        __sync_fetch_and_add(&s_trace_shown, 1);
        /* Full 64-bit result: printing (int)ret once hid a valid DNS
         * answer (an IPv4 >= 128.0.0.0 looks negative in 32 bits) and
         * sent a debug session down the wrong path. */
        if (nm) {
            kprintf("syscall %s(%ld, %ld, %ld, %ld, %ld, %ld)",
                    nm, a1, a2, a3, a4, a5, a6);
            trace_hint_print(n, hint, path_hint, a1, a2, a3);
        } else {
            kprintf("syscall %d(%ld, %ld, %ld, %ld, %ld, %ld)",
                    (int)n, a1, a2, a3, a4, a5, a6);
        }
        kprintf(" = %ld\n", ret);
    }
    return ret;
}

/* ---- User-pointer validation ---------------------------------------------
 * The syscall boundary is the hardened edge between ring 3 and ring 0.
 * Every pointer a Linux ABI program hands the kernel must lie inside the
 * user window [USER_LOAD_BASE, USER_LOAD_END), because that is the only
 * memory the page tables marked user-accessible. Anything else — kernel
 * heap, kernel image, page tables, MMIO — must be rejected before a single
 * dereference. All arithmetic is overflow checked. */

int user_range_ok(unsigned long p, unsigned long len) {
    if (p < USER_LOAD_BASE) return 0;
    if (len > USER_LOAD_END - p) return 0;
    return p + len <= USER_LOAD_END;
}

/* user_str_ok(p, maxlen): 1 iff a NUL byte sits within [p, p+maxlen) and
 * the whole span stays inside the user window; 0 otherwise (no NUL in
 * the first maxlen bytes, or the span would leave the window). Callers
 * must then read at most maxlen bytes: the check and the copy share the
 * same bound, so the gfx_title over-read class (validate 1, read 31)
 * cannot recur.
 *
 * Discipline (audit 2026-09, kept as comment, not a deprecation: both
 * primitives are legitimate): user_range_ok is ONLY for exact-size
 * buffers (sizeof(int), 144-byte stat, fixed PCM length); every NUL-
 * terminated string goes through user_str_ok/SANITIZE_STR. Count-by-size
 * products (writev cnt*sizeof, poll a2*8, spawn (argc+1)*sizeof) are
 * pre-bounded against (END-BASE)/elemsz BEFORE the multiply, so the
 * product cannot wrap past the range check. New handlers must use the
 * SANITIZE_* macros, which encode all three rules. */

int user_str_ok(unsigned long p, unsigned long maxlen) {
    unsigned long i;
    if (p < USER_LOAD_BASE || p >= USER_LOAD_END) return 0;
    for (i = 0; i < maxlen && p + i < USER_LOAD_END; i++)
        if (((unsigned char *)p)[i] == 0) return 1;
    return 0;
}

static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
    if (wm_close_pending()) {
        wm_clear_close();
        /* A background job has no fg exec frame to unwind: reaping it as
         * a 130 exit is the same outcome without hijacking the shell's
         * klongjmp target (which would corrupt whoever owns it). */
        if (current_pid != 0) {
            do_exit(130);
            return 0;
        }
        exec_exit_code = 130;
        klongjmp(&exec_return, 1);
        return 0;
    }
    /* RLIMIT_CPU edge for the exec frame (pid 0 has no scheduler slot to
     * zombify in the ISR, so the pending flag lands here, exactly like a
     * window-close request). Threads die synchronously in the ISR paths. */
    if (n != MINIOS_SYS_RLIMIT && rlimit_cpu_exceeded(current_pid)) {
        proc_t *kp = &procs[current_pid < 0 ? 0 : current_pid];
        kp->cpu_kill_pending = 0;
        if (current_pid != 0) {
            do_exit(RLIM_EXIT_CPU);
            return 0;
        }
        exec_exit_code = RLIM_EXIT_CPU;
        klongjmp(&exec_return, 1);
        return 0;
    }
    /* seccomp-bpf (docs/spec/kernel.md): a filtered process's syscall is
     * judged before any dispatch; ERRNO/TRACE answers return here, KILL
     * never comes back. */
    {
        long sec_ret = 0;
        if (proc_sec_filter(n, a1, a2, a3, a4, a5, a6, &sec_ret)) return sec_ret;
    }
    /* Linux ABI syscalls (0-199): table-driven dispatch.  A miss falls
     * through to the switch below (default ENOSYS), exactly like an
     * unmatched case did before the migration. */
    if (n >= 0 && n < LINUX_SYSCALL_COUNT) {
        const minios_syscall_entry_t *e = &linux_syscall_table[(int)n];
        if (e->fn) return e->fn(a1, a2, a3, a4, a5, a6);
    }
    /* MiniOS custom syscalls (200+): table-driven dispatch.  The numeric
     * range [MINIOS_SYSCALL_BASE, MINIOS_SYSCALL_BASE + MINIOS_SYSCALL_COUNT)
     * overlaps real Linux syscalls (openat=257, exit_group=231, newfstatat=262,
     * ...).  A number in that range with no MiniOS handler registered must fall
     * through to the Linux switch below, never be swallowed by an ENOSYS, or no
     * Linux binary could ever open or exit. */
    if (n >= MINIOS_SYSCALL_BASE && n < MINIOS_SYSCALL_BASE + MINIOS_SYSCALL_COUNT) {
        const minios_syscall_entry_t *e = &minios_syscall_table[n - MINIOS_SYSCALL_BASE];
        if (e->fn) {
            if (n != MINIOS_SYS_SECCOMP && n != MINIOS_SYS_NICE &&
                n != MINIOS_SYS_TLS_SEND && /* now Linux futex: filtering
                it would abort any glibc program that locks */
                n >= SECCOMP_MIN && n <= SECCOMP_MAX &&
                seccomp_denied(current_pid, (int)n))
                return -1;
            return e->fn(a1, a2, a3, a4, a5, a6);
        }
    }
    switch (n) {
    /* 0, 1, 20, 2 now live in linux_syscall_table; 257 shares
     * do_open_path with open. */
    case 257: /* openat (open/2 is table-driven) */
        return do_open_path((const char *)a2, a3);
    /* 12, 9, 11, 158 now live in linux_syscall_table. */
    case 218: /* set_tid_address: record nothing (single robust-list slot
        * arrives in Phase 1.B); return the caller tid like Linux. */
        return (long)current_pid;
    case 228: /* clock_gettime: id 1 (MONOTONIC) reads the calibrated TSC
        * directly; every other id reads the RTC-anchored wall clock
        * (Phase 0.2: two successive reads differ and order correctly). */
        if (a2) {
            unsigned long *ts = (unsigned long *)a2;
            SANITIZE_RANGE(ts, 2 * sizeof(unsigned long));
            if (a1 == 1) {
                unsigned long us = ktime_us();
                ts[0] = us / 1000000UL; ts[1] = (us % 1000000UL) * 1000UL;
            } else {
                unsigned long total = wall_us_now();
                ts[0] = total / 1000000UL;
                ts[1] = (total % 1000000UL) * 1000UL;
            }
        }
        return 0;
    /* 16, 24, 39, 57, 58, 59, 60, 61, 62, 41, 42, 44, 45, 48, 7 now
     * live in linux_syscall_table; 231 shares do_proc_exit. */
    case 231: /* exit_group (exit/60 is table-driven): the rest of the
        * thread group dies first, then the caller exits. */
        do_group_exit((int)(a1 & LINUX_EXIT_STATUS_MASK));
        return do_proc_exit(a1);
    case 435: /* clone3: -ENOSYS, which glibc treats as "use clone" (56). */
        return -38;
    case 284: /* eventfd */
        return sys_linux_eventfd(a1, a2, a3, a4, a5, a6);
    case 229: /* clock_getres: both clocks tick in microseconds */
        if (a1 != LINUX_CLOCK_REALTIME && a1 != LINUX_CLOCK_MONOTONIC &&
                a1 != LINUX_CLOCK_BOOTTIME)
            return -22;
        if (a2) {
            SANITIZE_RANGE(a2, 2 * sizeof(long));
            ((long *)a2)[0] = 0;
            ((long *)a2)[1] = LINUX_NS_PER_US;
        }
        return 0;
    case 230: /* clock_nanosleep */
        return sys_linux_clock_nanosleep(a1, a2, a3, a4, a5, a6);
    case 307: /* sendmmsg: glibc's resolver sends A and AAAA together */
        return sys_linux_sendmmsg(a1, a2, a3, a4, a5, a6);
    case 290: /* eventfd2 */
        return sys_linux_eventfd2(a1, a2, a3, a4, a5, a6);
    case 292: /* dup3 */
        return sys_linux_dup3(a1, a2, a3, a4, a5, a6);
    case 293: /* pipe2 */
        return sys_linux_pipe2(a1, a2, a3, a4, a5, a6);
    case 436: /* close_range */
        return sys_linux_close_range(a1, a2, a3, a4, a5, a6);
    case 137: /* statfs: MiniOS has no filesystem statistics; callers
        * (glibc, the selinux probe) fall back on ENOSYS. */
        return -38;
    case 138: /* fstatfs */
        return -38;
    case 234: /* tgkill: a fatal signal ends the whole group */
        if (a3 < 0 || a3 > LINUX_SIGNAL_MAX) return -22;
        if (a3 == 0 || !linux_signal_fatal(a3)) return 0;
        if (current_pid != 0) {
            do_group_exit((int)-a3);
            do_exit((int)-a3);
            return 0;
        }
        do_group_exit((int)-a3);
        exec_exit_code = LINUX_SIGNAL_EXIT_BASE + (int)a3;
        klongjmp(&exec_return, 1);
        return 0;
    /* 87, 73, 74, 75, 21, 89, 96 now live in linux_syscall_table. */
    case 267: /* readlinkat: MiniOS has no symlinks; the only link is
        * /proc/self/exe (absolute, so dirfd is irrelevant), served like
        * readlink (89). */
        return readlink_path((const char *)a2, (char *)a3, a4);
    case 317: /* seccomp */
        return proc_sec_seccomp(a1, a2, a3);
    case 272: /* unshare: no namespaces; callers treat it as best-effort
        * defense in depth beside seccomp. */
        return -38;
    case 444: /* landlock_create_ruleset: no Landlock; best-effort like
        * unshare, seccomp stays the mandatory boundary. */
        return -38;
    case 445: /* landlock_add_rule */
        return -38;
    case 446: /* landlock_restrict_self */
        return -38;
    case 273: /* set_robust_list: recorded nowhere yet (Phase 1.B either
        * stores the per-thread list or ADRs the no-op); answering 0
        * lets thread init proceed, and robust-mutex owner-death is the
        * documented gap. */
        return 0;
    case 301: /* fanotify_mark shadow: fossil set_robust_list alias kept
        * answering 0 so old binaries keep booting; new code uses 273. */
        return 0;
    case 302: /* prlimit64 */
        return sys_linux_prlimit64(a1, a2, a3, a4, a5, a6);
    case 204: /* sched_getaffinity */
        return sys_linux_sched_getaffinity(a1, a2, a3, a4, a5, a6);
    case 318: { /* getrandom: RDRAND when the CPU offers it, folded with
        * TSC/tick/pid jitter through splitmix64 (Phase 0.5). The old
        * TSC-XOR-index stream was predictable from boot time. */
        unsigned char *buf = (unsigned char *)a1;
        unsigned long cnt = (unsigned long)a2;
        unsigned long i, word = 0;
        int have_rdrand = 0;
        if (cnt > 0) { SANITIZE_RANGE(buf, cnt); }
        {
            unsigned int ecx = 0;
            __asm__ volatile("mov $1, %%eax; cpuid; mov %%ecx, %0"
                             : "=r"(ecx) :: "eax", "ebx", "edx");
            have_rdrand = (ecx & (1u << 30)) != 0;
        }
        for (i = 0; i < cnt; i++) {
            if ((i & 7) == 0) {
                unsigned long long r = 0;
                unsigned long lo = 0, hi = 0;
                int ok = 0;
                if (have_rdrand) {
                    int tries;
                    for (tries = 0; tries < 10; tries++) {
                        unsigned char cf = 0;
                        __asm__ volatile(
                            "rdrand %1; setc %0"
                            : "=r"(cf), "=r"(r) :: "cc");
                        if (cf) { ok = 1; break; }
                    }
                }
                __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
                word = randmix64(((unsigned long)r ^ (ok ? 0x9E3779B97F4A7C15UL : 0UL)) +
                                 (lo ^ (hi << 1)) + sys_ticks +
                                 (unsigned long)current_pid + i);
            }
            buf[i] = (unsigned char)(word >> (8 * (i & 7)));
        }
        return (long)cnt;
    }
    case 334: /* rseq: restartable sequences unsupported; glibc probes,
        * sees an error and runs without them. -1, never a forged area. */
        return -1;
    /* 79 now lives in linux_syscall_table. */
    case 262: { /* newfstatat */
        const char *path = (const char *)a2;
        unsigned long *st = (unsigned long *)a3;
        SANITIZE_STR(path, RAMDISK_FNAME_LEN);
        SANITIZE_RANGE(st, 144);
        for (int i = 0; i < 18; i++) st[i] = 0;
        char resolved[RAMDISK_FNAME_LEN];
        if (!fs_resolve(path, resolved, sizeof(resolved))) return -2;
        if (fs_is_dir(resolved)) {
            ((unsigned int *)(unsigned long)st)[5] = 0040755;
        } else {
            RDFile *rf = ramdisk_open(resolved);
            if (!rf) {
                if (minifs_is_mounted()) {
                    int ino = minifs_resolve_path(resolved);
                    MiniFSInode mi;
                    if (ino >= 0 && minifs_stat(ino, &mi) >= 0) {
                        ((unsigned int *)(unsigned long)st)[5] = 0100666;
                        ((unsigned long *)(unsigned long)st)[6] = (unsigned long)mi.size;
                        return 0;
                    }
                }
                return -2;
            }
            ((unsigned int *)(unsigned long)st)[5] = 0100666;
            ((unsigned long *)(unsigned long)st)[6] = (unsigned long)rf->size;
        }
        return 0;
    }
    /* 223 is table-driven (minios_syscall_table); switch copy was dead. */
    default:
        kprintf("UNIMPL SYSCALL %ld\n", n);
        return -38;
    }
}


/* SYS_SPAWN (215): run a ramdisk program from inside the OS.
 * Saves the parent's user window, loads the child, runs it via k_exec_user,
 * and restores the parent on return. ET_REL children run at ring 0 via
 * k_run_rel; ET_EXEC/ET_DYN children run in an isolated window via
 * proc_spawn_elf (the same path mrun uses) and the caller blocks in
 * do_waitpid, so the parent address space is left intact.
 */

#include "spawn.h"

static int k_syscall_spawn(const char *path, const char *redirect,
                             int child_argc, const char **child_argv);

static int k_syscall_spawn(const char *path, const char *redirect,
                             int child_argc, const char **child_argv) {
    char resolved[RAMDISK_FNAME_LEN];
    char **kargv = 0;
    unsigned char *data = 0;
    unsigned data_size = 0;
    spawn_ctx_t ctx;
    int rc;
    if (!path) return EFAULT;
    SANITIZE_STR(path, RAMDISK_FNAME_LEN);
    if (!spawn_validate_argv(child_argc, child_argv)) return EFAULT;
    kargv = spawn_copy_argv(child_argc, child_argv);
    if (child_argc > 0 && child_argv && !kargv) return EFAULT;
    if (!fs_resolve(path, resolved, sizeof(resolved))) {
        spawn_free_argv(kargv, child_argc);
        return EFAULT;
    }
    data = spawn_load_image(resolved, &data_size);
    if (!data) {
        spawn_free_argv(kargv, child_argc);
        return EFAULT;
    }
    if (data_size < EI_NIDENT ||
        !(data[0] == 0x7F && data[1] == 'E' && data[2] == 'L' && data[3] == 'F')) {
        kfree(data);
        spawn_free_argv(kargv, child_argc);
        return EFAULT;
    }
    if (!spawn_backup(&ctx)) {
        kprintf("SPAWN: out of memory\n");
        kfree(data);
        spawn_free_argv(kargv, child_argc);
        return -1;
    }
    rc = spawn_execute(resolved, redirect, data, data_size,
                       child_argc, kargv, child_argv);
    kfree(data);
    spawn_free_argv(kargv, child_argc);
    spawn_restore(&ctx);
    return rc;
}
