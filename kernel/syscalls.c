/* syscalls.c - Linux x86-64 syscall dispatcher and SYS_SPAWN.
 *
 * Extracted from kernel.c.  Contains ksyscall (trace wrapper),
 * ksyscall_dispatch (the ABI switch), the file-descriptor table (kfd_table),
 * user-pointer validation, and k_syscall_spawn (the bridge between the
 * Linux ABI and the internal ELF loaders).
 *
 * Process-management handlers (clone, seccomp, nice, yield, getpid/tid,
 * fork/vfork/execve stubs, exit, wait4, kill) live in syscalls_proc.c
 * (declared in syscalls_proc.h); the tables below reference them.
 *
 * The asm trampoline (syscall_entry / syscall_kstack) stays in kernel.c
 * because it defines the global symbols the boot code installs into MSR_LSTAR.
 */

#include "kernel.h"
#include "net.h"
#include "bootdefs.h"
#include "minifs.h"
#include "ide.h"
#include "block.h"
#include "sched.h"
#include "vga_fb.h"
#include "pcspk.h"
#include "sb16.h"
#include "rtc.h"
#include "lz4_kernel.h"
#include "drivers/kbd.h"
#include "arch/x86/msr.h"
#include "zip.h"
#include "futex.h"
#include "batch.h"
#include "rcu.h"
#include "percpu_rq.h"
#include "sanitize.h"
#include "driver.h"
#include "syscalls_proc.h"
#include "shell.h"
#include "ktime.h"
#include "randmix.h"

/* ---- File descriptor table for open/read/write/close -------------------- */

#define KFD_MAX 32
KFILE *kfd_table[KFD_MAX];

/* Guards g_brk/g_brk_limit/user_mmap_cur and the VMA trees against
 * concurrent brk/mmap/munmap syscalls from threads on different CPUs.
 * Lock order: sched_lock -> mm_lock (the scheduler takes mm_lock
 * inside sched_lock for the brk/mmap view switch; syscalls take
 * mm_lock alone).  Declared extern in the scheduler via sched.c. */
spinlock_t mm_lock = SPINLOCK_INIT;

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
    /* Retired kernel-TLS numbers (201/203): the engine left ring 0 and
     * 202 now serves Linux futex, so these always answer -ENOSYS.
     * Fossil miniGCC binaries still trap them and fail closed. */
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return -38;
}
static long sys_linux_futex(long a1, long a2, long a3, long a4, long a5, long a6) {
    /* Linux futex(2): __NR_futex is 202, the retired MINIOS_SYS_TLS_SEND
     * number, so it is served here rather than in the Linux switch below
     * (the MiniOS table is consulted first for 200..327 and would win).
     * glibc's NPTL/malloc/resolver issue raw futex traps — e.g. a
     * WAKE|PRIVATE inside getaddrinfo, which is what `freedom google.cl`
     * needs — and answering -ENOSYS aborts the process ("The futex
     * facility returned an unexpected error code", exit 134). WAIT/WAKE
     * run on kernel/futex.c; a mismatch is -EAGAIN like Linux (the
     * MiniOS 226/227 pair keeps its own FUTEX_NOMATCH convention
     * untouched). No timeout support: a WAIT with a deadline sleeps
     * until woken. Every other op (REQUEUE, BITSET, PI...) is -ENOSYS. */
    unsigned long uaddr = (unsigned long)a1;
    int cmd = futex_linux_cmd(a2);
    long n;
    (void)a4; (void)a5; (void)a6;
    if (cmd < 0) return -38;
    SANITIZE_RANGE(uaddr, 4);
    if (cmd == LINUX_FUTEX_WAKE) {
        n = a3;
        if (n < 0) n = 0;
        if (n > FUTEX_WAKE_ALL) n = FUTEX_WAKE_ALL;
        return futex_wake(uaddr, (int)n);
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
        __asm__ volatile("inb $0x60, %0" : "=a"(sc));
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
    (void)a4; (void)a5; (void)a6;
    int *wp = (int *)(unsigned long)a1;
    int *hp = (int *)(unsigned long)a2;
    int *pp = (int *)(unsigned long)a3;
    SANITIZE_RANGE(a1, sizeof(int));
    SANITIZE_RANGE(a2, sizeof(int));
    SANITIZE_RANGE(a3, sizeof(int));
    *wp = fb_width; *hp = fb_height; *pp = fb_pitch;
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
    m[0] = mx;
    m[1] = my;
    m[2] = mb;
    m[3] = mw;
    return 0;
}
static long sys_minios_nk_frame(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    if (a1) {
        int *o = (int *)(unsigned long)a1;
        SANITIZE_RANGE(a1, 2 * sizeof(int));
        o[0] = nk_win_x; o[1] = nk_win_y + FONT_H;
    }
    gfx_note_compositor();
    vga_fb_blit_nk_window();
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
 * a1 = buffer id (0 = 320x200 game buffer, 1 = 800x360 NK buffer),
 * a2 = optional user int[2] for the content origin (NK path only).
 * DOOM_FRAME (211) and NK_FRAME (220) stay as compat aliases. */
static long sys_minios_gfx_present(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    if (a1 == 1) {
        if (a2) {
            int *o = (int *)(unsigned long)a2;
            SANITIZE_RANGE(a2, 2 * sizeof(int));
            o[0] = nk_win_x; o[1] = nk_win_y + FONT_H;
        }
        vga_fb_blit_nk_window();
        return 0;
    }
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
        unsigned plen = (unsigned)kstrlen(dir);
        RDFile *files[RAMDISK_MAX_FILES];
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
    return count;
}

static const minios_syscall_entry_t minios_syscall_table[MINIOS_SYSCALL_COUNT] = {
    [MINIOS_SYS_DNS - MINIOS_SYSCALL_BASE]         = { sys_minios_dns,         "dns" },
    [MINIOS_SYS_TLS_HANDSHAKE - MINIOS_SYSCALL_BASE] = { sys_minios_tls_retired, "tls_retired" },
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

static long sys_linux_read(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    char *buf = (char *)a2; long cnt = a3, i = 0;
    if (cnt > 0 && !user_range_ok((unsigned long)buf, (unsigned long)cnt)) {
        kprintf("READ: EFAULT fd=%ld buf=%lx cnt=%ld\n", a1, a2, a3);
        return EFAULT;
    }
    if (a1 == 0) {
        if (!vga_fb_ps2_owner(current_pid)) return -11;
        while (i < cnt) {
            int c = console_getc();
            if (c < 0) continue;
            if (c == '\r') c = '\n';
            vga_putc((char)c);
            buf[i++] = (char)c;
            if (c == '\n') break;
        }
        return i;
    }
    if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1]) {
        return (long)kfread(buf, 1, (unsigned long)cnt, kfd_table[a1]);
    }
    kprintf("READ: bad fd=%ld\n", a1);
    return -9;
}

static long sys_linux_write(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    const char *buf = (const char *)a2; long cnt = a3, i;
    if (cnt > 0) { SANITIZE_RANGE(buf, (unsigned long)cnt); }
    if (a1 == 1 || a1 == 2) { for (i = 0; i < cnt; i++) vga_putc(buf[i]); return cnt; }
    if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1])
        return (long)kfwrite(buf, 1, (unsigned long)cnt, kfd_table[a1]);
    return -9;
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
        unsigned long j;
        if (kc[k].iov_len > 0 &&
            !user_range_ok((unsigned long)kc[k].iov_base, kc[k].iov_len)) {
            kfree(kc);
            return EFAULT;
        }
        if (a1 == 1 || a1 == 2)
            for (j = 0; j < kc[k].iov_len; j++) vga_putc(kc[k].iov_base[j]);
        total += (long)kc[k].iov_len;
    }
    if (kc) kfree(kc);
    return total;
}

/* Shared by sys_linux_open (2) and the openat fall-through (257). */
static long do_open_path(const char *path, long flags) {
    const char *mode = ((flags & 1) || (flags & 0x40)) ? "w" : "r";
    int fd;
    SANITIZE_STR(path, RAMDISK_FNAME_LEN);
    for (fd = 3; fd < KFD_MAX; fd++) if (!kfd_table[fd]) break;
    if (fd >= KFD_MAX) return -24;
    {
        proc_t *op = (current_pid >= 0 && current_pid < MAX_PROCS) ? &procs[current_pid] : 0;
        if (op && op->rl_nofile_max && (unsigned long)op->open_files >= op->rl_nofile_max)
            return -24;
    }
    KFILE *f = kfopen(path, mode);
    if (!f) {
        return -2;
    }
    kfd_table[fd] = f;
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

static long sys_linux_close(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    if (a1 >= NET_FD_BASE) return net_sys_close(a1);
    if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1]) {
        proc_t *cp = (current_pid >= 0 && current_pid < MAX_PROCS) ? &procs[current_pid] : 0;
        kfclose(kfd_table[a1]); kfd_table[a1] = 0;
        if (cp && cp->open_files > 0) cp->open_files--;
    }
    return 0;
}

static long sys_linux_lseek(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1]) {
        kfseek(kfd_table[a1], a2, (int)a3);
        long pos = kftell(kfd_table[a1]);
        return pos;
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

static long sys_linux_mmap(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a3; (void)a4; (void)a5; (void)a6;
    unsigned long len = (unsigned long)a2;
    unsigned long n = ALIGN_UP(len ? len : 1, 0x1000);
    irqflags_t flags;
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
            vma_tree_delete(&vma_free_root, best->base);
            if (rem_len > 0)
                vma_tree_insert(&vma_free_root, rem_base, rem_len);
            vma_tree_insert(&vma_live_root, addr, n);
            ret = (long)addr;
            goto mmap_out;
        }
    }
    if (user_mmap_cur - n < g_brk) { ret = -12; goto mmap_out; }
    user_mmap_cur -= n;
    if (mm_ensure_cur(user_mmap_cur, user_mmap_cur + n)) {
        user_mmap_cur += n;
        ret = -12;
        goto mmap_out;
    }
    vma_tree_insert(&vma_live_root, user_mmap_cur, n);
    ret = (long)user_mmap_cur;
mmap_out:
    spin_unlock_irqrestore(&mm_lock, flags);
    return ret;
}

static long sys_linux_munmap(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    unsigned long base = (unsigned long)a1;
    unsigned long n = ALIGN_UP((unsigned long)a2, 0x1000);
    if (n == 0) return 0;
    irqflags_t flags;
    spin_lock_irqsave(&mm_lock, &flags);
    vma_node_t *fnd = vma_tree_find(vma_live_root, base);
    long ret = -1;
    if (fnd != VMA_NIL && n <= fnd->len) {
        vma_tree_insert(&vma_free_root, fnd->base, fnd->len);
        vma_tree_delete(&vma_live_root, base);
        ret = 0;
    }
    spin_unlock_irqrestore(&mm_lock, flags);
    return ret;
}

static long sys_linux_mprotect(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return 0;
}

static long sys_linux_sigaction(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return 0;
}

static long sys_linux_sigprocmask(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return 0;
}

static long sys_linux_ioctl(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return 0;
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
    RDFile *f = ramdisk_open(resolved);
    if (f) { ramdisk_delete(f); return 0; }
    if (minifs_is_mounted() && minifs_unlink(resolved) == 0) return 0;
    return -2;
}

static long sys_linux_readlink(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return -22;
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
        if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1]) {
            KFILE *kf = kfd_table[a1];
            if (kf->rf)
                ((unsigned long *)(unsigned long)a2)[6] = (unsigned long)kf->rf->size;
            else if (kf->minifs_ino >= 0)
                ((unsigned long *)(unsigned long)a2)[6] = (unsigned long)kf->minifs_size;
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
    [24]  = { sys_linux_yield,        "yield" },
    [39]  = { sys_linux_getpid,       "getpid" },
    [41]  = { sys_linux_socket,       "socket" },
    [42]  = { sys_linux_connect,      "connect" },
    [44]  = { sys_linux_sendto,       "sendto" },
    [45]  = { sys_linux_recvfrom,     "recvfrom" },
    [48]  = { sys_linux_shutdown,     "shutdown" },
    [57]  = { sys_linux_fork,         "fork" },
    [58]  = { sys_linux_vfork,        "vfork" },
    [59]  = { sys_linux_execve,       "execve" },
    [60]  = { sys_linux_exit,         "exit" },
    [61]  = { sys_linux_wait4,        "wait4" },
    [62]  = { sys_linux_kill,         "kill" },
    [63]  = { sys_linux_uname,        "uname" },
    [73]  = { sys_linux_flock,        "flock" },
    [74]  = { sys_linux_fsync,        "fsync" },
    [75]  = { sys_linux_fdatasync,    "fdatasync" },
    [79]  = { sys_linux_getcwd,       "getcwd" },
    [87]  = { sys_linux_unlink,       "unlink" },
    [89]  = { sys_linux_readlink,     "readlink" },
    [96]  = { sys_linux_gettimeofday, "gettimeofday" },
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
    { 17, "pread64" }, { 18, "pwrite64" }, { 22, "pipe" },
    { 23, "select" }, { 25, "mremap" }, { 28, "madvise" },
    { 32, "dup" }, { 33, "dup2" }, { 35, "nanosleep" },
    { 56, "clone" }, { 72, "fcntl" }, { 78, "getdents" },
    { 97, "getrlimit" }, { 102, "getuid" }, { 104, "getgid" },
    { 107, "geteuid" }, { 108, "getegid" }, { 157, "prctl" },
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
    if (n == 2 || n == 21 || n == 87 || n == 89) p = (const char *)a1;
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
    case 231: /* exit_group (exit/60 is table-driven) */
        return do_proc_exit(a1);
    case 234: { /* tgkill */
        int sig = (int)a3;        static const int fatal[] = {1,2,3,4,5,6,7,8,9,11,13,14,15};
        if (sig <= 0) return -22;
        for (unsigned _i = 0; _i < sizeof(fatal)/sizeof(fatal[0]); _i++)
            if (sig == fatal[_i]) {
                if (proc_count > 1) {
                    do_exit(128 + sig);
                    return 0;
                }
                exec_exit_code = 128 + sig;
                klongjmp(&exec_return, 1);
                return 0;
            }
        return 0;
    }
    /* 87, 73, 74, 75, 21, 89, 96 now live in linux_syscall_table. */
    case 267: /* readlinkat: MiniOS has no symlinks, so dirfd+path can
        * never resolve to one; EINVAL like readlink (89), never a
        * forged link length. A real readlinkat arrives in Phase 1.A. */
        return -22;
    case 273: /* set_robust_list: recorded nowhere yet (Phase 1.B either
        * stores the per-thread list or ADRs the no-op); answering 0
        * lets thread init proceed, and robust-mutex owner-death is the
        * documented gap. */
        return 0;
    case 301: /* fanotify_mark shadow: fossil set_robust_list alias kept
        * answering 0 so old binaries keep booting; new code uses 273. */
        return 0;
    case 302: /* prlimit64: unimplemented (ENOSYS, not the old 0: the
        * MiniOS RLIMIT custom semantics live at 240 under their own
        * name, and 302 must not masquerade as success). */
        return -38;
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
    spawn_backup(&ctx);
    rc = spawn_execute(resolved, redirect, data, data_size,
                       child_argc, kargv, child_argv);
    kfree(data);
    spawn_free_argv(kargv, child_argc);
    spawn_restore(&ctx);
    return rc;
}
