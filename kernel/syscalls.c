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
    if (!user_str_ok((unsigned long)a1, 255)) return EFAULT;
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
    if (!user_range_ok(uaddr, 4)) return EFAULT;
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
    if (!user_range_ok((unsigned long)a1, sizeof(int)) ||
        !user_range_ok((unsigned long)a2, sizeof(int)) ||
        !user_range_ok((unsigned long)a3, sizeof(int)))
        return EFAULT;
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
    if (!user_range_ok((unsigned long)a1, sizeof(int)) ||
        !user_range_ok((unsigned long)a2, sizeof(int)) ||
        !user_range_ok((unsigned long)a3, sizeof(int)))
        return EFAULT;
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
    if (!user_str_ok((unsigned long)path, RAMDISK_FNAME_LEN)) return EFAULT;
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
    if (!user_range_ok((unsigned long)src, (unsigned long)src_len)) return EFAULT;
    if (!user_range_ok((unsigned long)dst, (unsigned long)dst_cap)) return EFAULT;
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
    if (!user_range_ok((unsigned long)src, (unsigned long)src_len)) return EFAULT;
    unsigned int orig = (unsigned int)((unsigned char)src[0] | ((unsigned char)src[1] << 8) |
                                       ((unsigned char)src[2] << 16) | ((unsigned char)src[3] << 24));
    if (orig > (unsigned int)dst_cap) return 0;
    if (dst_cap > 0 && !user_range_ok((unsigned long)dst, (unsigned long)dst_cap)) return EFAULT;
    int ret = LZ4_decompress_safe(src + 4, dst, src_len - 4, dst_cap);
    if (ret < 0 || (unsigned int)ret != orig) return 0;
    return ret;
}
static long sys_minios_mouse(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    int *m = (int *)(unsigned long)a1;
    if (!user_range_ok((unsigned long)a1, 4 * sizeof(int))) return EFAULT;
    m[0] = mouse_state.x; m[1] = mouse_state.y;
    m[2] = mouse_state.buttons; m[3] = mouse_state.wheel;
    mouse_state.wheel = 0;
    return 0;
}
static long sys_minios_nk_frame(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    if (a1) {
        int *o = (int *)(unsigned long)a1;
        if (!user_range_ok((unsigned long)a1, 2 * sizeof(int))) return EFAULT;
        o[0] = nk_win_x; o[1] = nk_win_y + FONT_H;
    }
    gfx_note_compositor();
    vga_fb_blit_nk_window();
    return 0;
}
static long sys_minios_sb16_open(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    if (a1) sb16_pcm_open(); else sb16_pcm_close();
    return sb16_present() ? 1 : 0;
}
static long sys_minios_sb16_submit(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    const unsigned char *pcm = (const unsigned char *)a1;
    long len = a2;
    SANITIZE_LEN_NEG(len);
    SANITIZE_RANGE(a1, len);
    return sb16_pcm_submit(pcm, (unsigned)len);
}
static long sys_minios_gfx_title(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    const char *t = (const char *)(unsigned long)a1;
    if (!t) return EFAULT;
    if (!user_str_ok((unsigned long)t, 31)) return EFAULT;
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
            if (!user_range_ok((unsigned long)a2, 2 * sizeof(int))) return EFAULT;
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
    if (a1 == 0) return (long)console_raw_try();
    return (long)console_raw_get();
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
};

struct kiovec { const char *iov_base; unsigned long iov_len; };

#define SYSCALL_TRACE 0

static int s_trace_enabled = SYSCALL_TRACE;

long syscall_trace_enabled(void) { return s_trace_enabled; }
void syscall_trace_set(int on) { s_trace_enabled = on ? 1 : 0; }

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
    if (cnt > 0 && !user_range_ok((unsigned long)buf, (unsigned long)cnt)) return EFAULT;
    if (a1 == 1 || a1 == 2) { for (i = 0; i < cnt; i++) vga_putc(buf[i]); return cnt; }
    if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1])
        return (long)kfwrite(buf, 1, (unsigned long)cnt, kfd_table[a1]);
    return -9;
}

static long sys_linux_writev(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    struct kiovec *iov = (struct kiovec *)a2; long cnt = a3, total = 0, k;
    if (cnt < 0 || (unsigned long)cnt > (USER_LOAD_END - USER_LOAD_BASE) / sizeof(struct kiovec))
        return -22;
    if (cnt > 0 && !user_range_ok((unsigned long)iov, (unsigned long)cnt * sizeof(struct kiovec)))
        return EFAULT;
    for (k = 0; k < cnt; k++) {
        unsigned long j;
        if (iov[k].iov_len > 0 &&
            !user_range_ok((unsigned long)iov[k].iov_base, iov[k].iov_len))
            return EFAULT;
        if (a1 == 1 || a1 == 2)
            for (j = 0; j < iov[k].iov_len; j++) vga_putc(iov[k].iov_base[j]);
        total += (long)iov[k].iov_len;
    }
    return total;
}

/* Shared by sys_linux_open (2) and the openat fall-through (257). */
static long do_open_path(const char *path, long flags) {
    const char *mode = ((flags & 1) || (flags & 0x40)) ? "w" : "r";
    int fd;
    if (!user_str_ok((unsigned long)path, RAMDISK_FNAME_LEN)) {
        return EFAULT;
    }
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
    if (!user_str_ok((unsigned long)path, RAMDISK_FNAME_LEN)) return EFAULT;
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
    if (!user_range_ok((unsigned long)a2, 16)) return EFAULT;
    return net_sys_connect(a1, a2, a3);
}

static long sys_linux_sendto(long a1, long a2, long a3, long a4, long a5, long a6) {
    if (a3 > 0 && !user_range_ok((unsigned long)a2, (unsigned long)a3)) return EFAULT;
    return net_sys_sendto(a1, a2, a3, a4, a5, a6);
}

static long sys_linux_recvfrom(long a1, long a2, long a3, long a4, long a5, long a6) {
    if (a3 > 0 && !user_range_ok((unsigned long)a2, (unsigned long)a3)) return EFAULT;
    return net_sys_recvfrom(a1, a2, a3, a4, a5, a6);
}

static long sys_linux_shutdown(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    return net_sys_shutdown(a1, a2);
}

static long sys_linux_poll(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    if (a2 < 0 || (unsigned long)a2 > (USER_LOAD_END - USER_LOAD_BASE) / 8) return -22;
    if (a2 > 0 && !user_range_ok((unsigned long)a1, (unsigned long)a2 * 8)) return EFAULT;
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
    if (!user_range_ok((unsigned long)buf, sz)) return EFAULT;
    unsigned long cwd_len = (unsigned long)kstrlen(fs_cwd);
    if (sz < cwd_len + 1) return -34;
    for (unsigned long i = 0; i <= cwd_len; i++) buf[i] = fs_cwd[i];
    return (long)(cwd_len + 1);
}

static long sys_linux_unlink(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    const char *path = (const char *)a1;
    if (!user_str_ok((unsigned long)path, RAMDISK_FNAME_LEN)) return EFAULT;
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
    if (!user_range_ok((unsigned long)a2, 144)) return EFAULT;
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
        if (!user_range_ok((unsigned long)a1, 2 * sizeof(unsigned long))) return EFAULT;
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
    if (!user_range_ok((unsigned long)a1, 390)) return EFAULT;
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

long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
    long ret;
    int show = s_trace_enabled && !trace_is_noisy(n);
    if (show)
        kprintf("syscall %d(%ld, %ld, %ld, %ld, %ld, %ld)",
                (int)n, a1, a2, a3, a4, a5, a6);
    ret = ksyscall_dispatch(n, a1, a2, a3, a4, a5, a6);
    /* Full 64-bit result: printing (int)ret once hid a valid DNS answer
     * (an IPv4 >= 128.0.0.0 looks negative in 32 bits) and sent a debug
     * session down the wrong path. */
    if (show) kprintf(" = %ld\n", ret);
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
            if (!user_range_ok((unsigned long)ts, 2 * sizeof(unsigned long))) return EFAULT;
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
        if (cnt > 0 && !user_range_ok((unsigned long)buf, cnt)) return EFAULT;
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
        if (!user_str_ok((unsigned long)path, RAMDISK_FNAME_LEN)) return EFAULT;
        if (!user_range_ok((unsigned long)st, 144)) return EFAULT;
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
 * k_run_rel; ET_EXEC/ET_DYN children run at ring 3 via k_exec_user.
 *
 * KNOWN LIMITATION (pre-existing): SYS_SPAWN of an ET_EXEC/ET_DYN child from
 * a ring-3 interpreter (lua/micropython) must save the parent's user window,
 * whose full span cannot fit in the kernel heap alongside the ramdisk, and the
 * klongjmp/syscall-stack unwind after the child exits is not robust in the
 * single shared address space.  Such a spawn therefore returns -EFAULT cleanly
 * (the interpreter gets nil) rather than running or crashing.  This is why the
 * in-OS interpreter suites exercise only the ET_REL toolchain (minigcc/ld);
 * ET_EXEC tools (lzss/lz4/aes/json/freedom) are run by the shell, not from an
 * interpreter.
 */

static int k_syscall_spawn(const char *path, const char *redirect,
                            int child_argc, const char **child_argv) {
    if (!path || !user_str_ok((unsigned long)path, RAMDISK_FNAME_LEN))
        return EFAULT;

    if (child_argc > 0 && child_argv) {
        if (!user_range_ok((unsigned long)child_argv,
                           (unsigned long)(child_argc + 1) * sizeof(char *)))
            return EFAULT;
        for (int i = 0; i < child_argc; i++) {
            if (!child_argv[i]) break;
            unsigned long s = (unsigned long)child_argv[i];
            if (s < USER_LOAD_BASE || s >= USER_LOAD_END) return EFAULT;
            if (!user_str_ok(s, USER_LOAD_END - s)) return EFAULT;
        }
    }

    char **kargv = 0;
    if (child_argc > 0 && child_argv) {
        kargv = (char **)kmalloc((unsigned)(child_argc + 1) * sizeof(char *));
        if (!kargv) return EFAULT;
        for (int i = 0; i <= child_argc; i++) kargv[i] = 0;
        for (int i = 0; i < child_argc; i++) {
            if (!child_argv[i]) break;
            unsigned slen = (unsigned)kstrlen(child_argv[i]) + 1;
            kargv[i] = (char *)kmalloc(slen);
            if (!kargv[i]) { for (int j = 0; j < i; j++) kfree(kargv[j]); kfree(kargv); return EFAULT; }
            kmemcpy(kargv[i], child_argv[i], slen);
        }
        kargv[child_argc] = 0;
    }

    char resolved[RAMDISK_FNAME_LEN];
    if (!fs_resolve(path, resolved, sizeof(resolved))) {
        if (kargv) { for (int i = 0; i < child_argc; i++) if (kargv[i]) kfree(kargv[i]); kfree(kargv); }
        return EFAULT;
    }

    RDFile *f = ramdisk_open(resolved);
    unsigned char *data = 0;
    unsigned data_size = 0;
    if (f) {
        data_size = f->size ? f->size : 1;
        data = (unsigned char *)kmalloc(data_size);
        if (!data) {
            if (kargv) { for (int i = 0; i < child_argc; i++) if (kargv[i]) kfree(kargv[i]); kfree(kargv); }
            return EFAULT;
        }
        ramdisk_read(f, data, 0, f->size);
    } else if (minifs_is_mounted()) {
        int ino = minifs_resolve_path(resolved);
        if (ino < 0) {
            const char *base = resolved;
            const char *p;
            for (p = resolved; *p; p++)
                if (*p == '/') base = p + 1;
            ino = minifs_resolve_path(base);
        }
        if (ino >= 0) {
            MiniFSInode mi;
            if (minifs_stat(ino, &mi) >= 0 && mi.size > 0) {
                data_size = mi.size;
                data = (unsigned char *)kmalloc(data_size);
                if (data) minifs_read(ino, data, 0, data_size);
            }
        }
    }
    if (!data) {
        if (kargv) { for (int i = 0; i < child_argc; i++) if (kargv[i]) kfree(kargv[i]); kfree(kargv); }
        return EFAULT;
    }

    if (data_size < EI_NIDENT ||
        !(data[0] == 0x7F && data[1] == 'E' && data[2] == 'L' && data[3] == 'F')) {
        kfree(data);
        if (kargv) { for (int i = 0; i < child_argc; i++) if (kargv[i]) kfree(kargv[i]); kfree(kargv); }
        return EFAULT;
    }
    Elf64_Half etype = ((const Elf64_Ehdr *)data)->e_type;

    unsigned long saved_brk      = g_brk;
    unsigned long saved_brk_lim  = g_brk_limit;
    unsigned long saved_mmap     = user_mmap_cur;
    unsigned long saved_fsbase   = rdmsr(MSR_FSBASE);
    unsigned long saved_gsbase   = rdmsr(MSR_GSBASE);
    /* An ET_REL child runs at ring 0 and exits through do_proc_exit's
     * klongjmp, which bypasses syscall_entry's write-back of the per-proc
     * stack top.  Left uncorrected, procs[0].kstack drifts down on every
     * nested spawn and the parent's own exit longjmps into a corrupt
     * frame.  Save and restore it so a spawn from a ring-3 program (the
     * vedit IDE) is transparent to the caller. */
    uint64_t saved_p0_kstack = procs[0].kstack;

    static vma_node_t parent_vma_pool_copy[VMA_MAX];
    for (int i = 0; i < vma_pool_n; i++)
        parent_vma_pool_copy[i] = vma_pool[i];
    vma_node_t *parent_live_root = vma_live_root;
    vma_node_t *parent_free_root = vma_free_root;
    int parent_pool_n = vma_pool_n;

    KFILE *saved_kfd[KFD_MAX];
    for (int i = 0; i < KFD_MAX; i++) saved_kfd[i] = kfd_table[i];

    int rc = EFAULT;
    if (etype == ET_REL) {
        /* Same gate as shell.c, same constant: `resolved` is fs_resolve()
         * output (normalised, no symlinks), and the bytes in `data` were
         * snapshotted from that same path above, so a concurrent rename
         * only selects different bytes -- hostile bytes still face the
         * ELF/reloc validators and ETREL_IMAGE_MAX. */
        const char *rp = resolved;
        if (rp[0] == '/') rp++;
        if (kstrncmp(rp, ETREL_TRUSTED_DIR, ETREL_TRUSTED_LEN) != 0) {
            kprintf("SPAWN: refusing untrusted ET_REL");
            kfree(data);
            if (kargv) { for (int i = 0; i < child_argc; i++) if (kargv[i]) kfree(kargv[i]); kfree(kargv); }
            return EFAULT;
        }
        prog_entry_t entry = elf_load((void *)data, data_size);
        kprintf("SPAWN: ET_REL entry=%lx argc=%d\n",
                (unsigned long)entry, child_argc);
        if (entry) {
            unsigned char *code = (unsigned char *)entry;
            kprintf("  [%lx]: ", (unsigned long)entry);
            for (int _i = 0; _i < 16; _i++) kprintf("%02x ", code[_i]);
            kprintf("\n");
        }
        int did_redirect = 0;
        if (redirect && redirect[0]) did_redirect = redirect_begin();
        if (entry)
            rc = k_run_rel(entry, child_argc, kargv ? kargv : (char **)child_argv);
        if (did_redirect) redirect_commit(redirect, 0);
    } else if (etype == ET_EXEC || etype == ET_DYN) {
        /* Run the child in its own window through the same isolated spawn
         * path `mrun` uses, then block until it exits.  The legacy
         * swap_out + k_exec_user route re-cloned the boot page tables,
         * discarding the freshly loaded image, so a ring-3 interpreter
         * (lua/micropython/vedit) could not spawn an ET_EXEC child.  The
         * isolated process has private heap-owned pages, its own CR3 and
         * a user_trampoline entry, so the parent is left byte-for-byte
         * intact. */
        int did_redirect = 0;
        int pid;
        if (redirect && redirect[0]) did_redirect = redirect_begin();
        pid = proc_spawn_elf(resolved, data, data_size, child_argc,
                             kargv ? kargv : (char **)child_argv);
        if (pid > 0)
            rc = do_waitpid(pid);
        if (did_redirect) redirect_commit(redirect, 0);
    }

    procs[0].kstack = saved_p0_kstack;
    kfree(data);

    if (kargv) {
        for (int i = 0; i < child_argc; i++) if (kargv[i]) kfree(kargv[i]);
        kfree(kargv);
    }

    g_brk       = saved_brk;
    g_brk_limit = saved_brk_lim;
    user_mmap_cur = saved_mmap;
    for (int i = 0; i < parent_pool_n; i++) vma_pool[i] = parent_vma_pool_copy[i];
    vma_pool_n = parent_pool_n;
    vma_live_root = parent_live_root;
    vma_free_root = parent_free_root;
    wrmsr(MSR_FSBASE, saved_fsbase);
    wrmsr(MSR_GSBASE, saved_gsbase);
    for (int i = 0; i < KFD_MAX; i++) kfd_table[i] = saved_kfd[i];

    return rc;
}
