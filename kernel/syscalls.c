/* syscalls.c - Linux x86-64 syscall dispatcher and SYS_SPAWN.
 *
 * Extracted from kernel.c.  Contains ksyscall (trace wrapper),
 * ksyscall_dispatch (the ABI switch), the file-descriptor table (kfd_table),
 * user-pointer validation, and k_syscall_spawn (the bridge between the
 * Linux ABI and the internal ELF loaders).
 *
 * The asm trampoline (syscall_entry / syscall_kstack) stays in kernel.c
 * because it defines the global symbols the boot code installs into MSR_LSTAR.
 */

#include "kernel.h"
#include "net.h"
#include "tls.h"
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

/* ---- File descriptor table for open/read/write/close -------------------- */

#define KFD_MAX 32
KFILE *kfd_table[KFD_MAX];

/* ---- Linux x86-64 syscall dispatcher ------------------------------------ */

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

static int k_syscall_spawn(const char *path, const char *redirect,
                            int child_argc, const char **child_argv);
static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6);

static int trace_is_noisy(long n) {
    return n == SYS_NOISY_TIME || n == SYS_NOISY_KBD || n == SYS_NOISY_MOUSE;
}

long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
    long ret;
    int show = s_trace_enabled && !trace_is_noisy(n);
    if (show)
        kprintf("syscall %d(%d, %d, %d, %d, %d, %d)",
                (int)n, (int)a1, (int)a2, (int)a3, (int)a4, (int)a5, (int)a6);
    ret = ksyscall_dispatch(n, a1, a2, a3, a4, a5, a6);
    if (show) kprintf(" = %d\n", (int)ret);
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
        exec_exit_code = 130;
        klongjmp(&exec_return, 1);
        return 0;
    }
    switch (n) {
    case 0: { /* read */
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
    case 1: { /* write */
        const char *buf = (const char *)a2; long cnt = a3, i;
        if (cnt > 0 && !user_range_ok((unsigned long)buf, (unsigned long)cnt)) return EFAULT;
        if (a1 == 1 || a1 == 2) { for (i = 0; i < cnt; i++) vga_putc(buf[i]); return cnt; }
        if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1])
            return (long)kfwrite(buf, 1, (unsigned long)cnt, kfd_table[a1]);
        return -9;
    }
    case 20: { /* writev */
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
    case 2: case 257: { /* open / openat */
        const char *path = (const char *)(n == 257 ? a2 : a1);
        long flags = (n == 257 ? a3 : a2);
        const char *mode = ((flags & 1) || (flags & 0x40)) ? "w" : "r";
        int fd;
        if (!user_str_ok((unsigned long)path, RAMDISK_FNAME_LEN)) {
            return EFAULT;
        }
        for (fd = 3; fd < KFD_MAX; fd++) if (!kfd_table[fd]) break;
        if (fd >= KFD_MAX) return -24;
        KFILE *f = kfopen(path, mode);
        if (!f) {
            return -2;
        }
        kfd_table[fd] = f;
        return fd;
    }
    case 3: /* close */
        if (a1 >= NET_FD_BASE) return net_sys_close(a1);
        if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1]) {
            kfclose(kfd_table[a1]); kfd_table[a1] = 0;
        }
        return 0;
    case 8: { /* lseek */
        if (a1 >= 3 && a1 < KFD_MAX && kfd_table[a1]) {
            kfseek(kfd_table[a1], a2, (int)a3);
            long pos = kftell(kfd_table[a1]);
            return pos;
        }
        return -9;
    }
    case 12: { /* brk */
        unsigned long addr = (unsigned long)a1;
        if (addr == 0) return (long)g_brk;
        if (addr >= USER_LOAD_BASE && addr <= g_brk_limit
            && addr <= user_mmap_cur)
            g_brk = addr;
        return (long)g_brk;
    }
    case 9: { /* mmap (anonymous only) */
        unsigned long len = (unsigned long)a2;
        unsigned long n = ALIGN_UP(len ? len : 1, 0x1000);
        if (n > user_mmap_cur - USER_LOAD_BASE) return -12;
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
                return (long)addr;
            }
        }
        if (user_mmap_cur - n < g_brk) return -12;
        user_mmap_cur -= n;
        vma_tree_insert(&vma_live_root, user_mmap_cur, n);
        return (long)user_mmap_cur;
    }
    case 11: { /* munmap */
        unsigned long base = (unsigned long)a1;
        unsigned long n = ALIGN_UP((unsigned long)a2, 0x1000);
        if (n == 0) return 0;
        vma_node_t *fnd = vma_tree_find(vma_live_root, base);
        if (fnd != VMA_NIL && n <= fnd->len) {
            vma_tree_insert(&vma_free_root, fnd->base, fnd->len);
            vma_tree_delete(&vma_live_root, base);
            return 0;
        }
        return -1;
    }
    case 158: /* arch_prctl */
        if (a1 == 0x1002 || a1 == 0x1001) {
            unsigned long v = (unsigned long)a2;
            unsigned long sign = (v >> 47) & 1;
            if (((v >> 48) & 0xFFFF) != (sign ? 0xFFFF : 0)) return -22;
            wrmsr(a1 == 0x1002 ? MSR_FSBASE : MSR_GSBASE, v);
            return 0;
        }
        return -22;
    case 218: return 1;
    case 228: /* clock_gettime */
        if (a2) {
            unsigned long *ts = (unsigned long *)a2;
            if (!user_range_ok((unsigned long)ts, 2 * sizeof(unsigned long))) return EFAULT;
            ts[0] = 0; ts[1] = 0;
        }
        return 0;
    case 16: return 0;
    case 24: yield(); return 0;
    case 39: return 1;
    case 57: return 0;
    case 58: return 0;
    case 59: return 0;
    case 60: case 231:
        if (proc_count > 1) {
            do_exit((int)a1);
            return 0;
        }
        exec_exit_code = (int)a1;
        klongjmp(&exec_return, 1);
        return 0;
    case 61: return do_waitpid((int)a1);
    case 62: return do_kill((int)a1);
    case 41:
        return net_sys_socket(a1, a2, a3);
    case 42:
        if (!user_range_ok((unsigned long)a2, 16)) return EFAULT;
        return net_sys_connect(a1, a2, a3);
    case 44:
        if (a3 > 0 && !user_range_ok((unsigned long)a2, (unsigned long)a3)) return EFAULT;
        return net_sys_sendto(a1, a2, a3, a4, a5, a6);
    case 45:
        if (a3 > 0 && !user_range_ok((unsigned long)a2, (unsigned long)a3)) return EFAULT;
        return net_sys_recvfrom(a1, a2, a3, a4, a5, a6);
    case 48:
        return net_sys_shutdown(a1, a2);
    case 7:
        if (a2 < 0 || (unsigned long)a2 > (USER_LOAD_END - USER_LOAD_BASE) / 8) return -22;
        if (a2 > 0 && !user_range_ok((unsigned long)a1, (unsigned long)a2 * 8)) return EFAULT;
        return net_sys_poll(a1, a2, a3);
    case 200:
        if (!user_str_ok((unsigned long)a1, 255)) return EFAULT;
        return net_sys_dns(a1);
    case 201:
        if (!user_str_ok((unsigned long)a2, 255)) return EFAULT;
        return tls_sys_handshake(a1, a2);
    case 202:
        if (a3 > 0 && !user_range_ok((unsigned long)a2, (unsigned long)a3)) return EFAULT;
        return tls_sys_send(a1, a2, a3);
    case 203:
        if (a3 > 0 && !user_range_ok((unsigned long)a2, (unsigned long)a3)) return EFAULT;
        return tls_sys_recv(a1, a2, a3);
    case 204: return (long)ktime_ms();
    case 205: { /* SYS_KBD */
        if (kbd_raw_mode_get()) {
            if (!kbd_raw_empty()) return kbd_raw_pop();
            if (!kbd_available()) return -1;
            unsigned char sc;
            __asm__ volatile("inb $0x60, %0" : "=a"(sc));
            if (sc == KEY_E0) { kbd_e0_set(1); return 0xE0; }
            if (kbd_e0_get()) {
                kbd_e0_set(0);
                return (long)sc;
            }
            return (long)sc;
        }
        if (kbd_q_empty()) return -1;
        return kbd_q_pop();
    }
    case 207:
        kbd_raw_mode_set((int)a1);
        kbd_flush_all();
        return 0;
    case 208: {
        vga_mode_set((int)a1);
        if (a1) vga_gfx_ran_set(1);
        vga_fb_set_gfx_mode((int)a1);
        return 0;
    }
    case 209: pcspk_init(); return 0;
    case 210: pcspk_tone((unsigned)a1); return 0;
    case 211: vga_fb_blit_gfx_window(); return 0;
    case 212: { /* SYS_RTC */
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
    case 213: { /* SYS_FB_INFO */
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
    case 214: {
        int v = (int)a1;
        if (v < 0) return (long)pcspk_get_volume();
        if (v > 100) v = 100;
        pcspk_set_volume((unsigned)v);
        return (long)pcspk_get_volume();
    }
    case 215: { /* SYS_SPAWN */
        const char *path = (const char *)a1;
        if (!user_str_ok((unsigned long)path, RAMDISK_FNAME_LEN)) return EFAULT;
        return k_syscall_spawn(path, (const char *)a2, (int)a3,
                               (const char **)a4);
    }
    case 216: { /* LZ4 compress */
        char *src = (char *)a1;
        char *dst = (char *)a3;
        int src_len = (int)a2;
        int dst_cap = (int)a4;
        int ret;
        if (src_len <= 0 || dst_cap <= 4) return 0;
        if (!user_range_ok((unsigned long)src, (unsigned long)src_len)) return EFAULT;
        if (!user_range_ok((unsigned long)dst, (unsigned long)dst_cap)) return EFAULT;
        ret = LZ4_compress_default(src, dst + 4, src_len, dst_cap - 4);
        if (ret <= 0 || ret >= src_len) return 0;
        dst[0] = (char)(src_len & 255);
        dst[1] = (char)((src_len >> 8) & 255);
        dst[2] = (char)((src_len >> 16) & 255);
        dst[3] = (char)((src_len >> 24) & 255);
        return ret + 4;
    }
    case 217: { /* LZ4 decompress */
        char *src = (char *)a1;
        char *dst = (char *)a3;
        int src_len = (int)a2;
        int dst_cap = (int)a4;
        unsigned int orig;
        int ret;
        if (src_len <= 4) return 0;
        if (!user_range_ok((unsigned long)src, (unsigned long)src_len)) return EFAULT;
        orig = (unsigned int)((unsigned char)src[0] | ((unsigned char)src[1] << 8) |
                              ((unsigned char)src[2] << 16) | ((unsigned char)src[3] << 24));
        if (orig > (unsigned int)dst_cap) return 0;
        if (dst_cap > 0 && !user_range_ok((unsigned long)dst, (unsigned long)dst_cap)) return EFAULT;
        ret = LZ4_decompress_safe(src + 4, dst, src_len - 4, dst_cap);
        if (ret < 0 || (unsigned int)ret != orig) return 0;
        return ret;
    }
    case 219: { /* SYS_MOUSE */
        int *m = (int *)(unsigned long)a1;
        if (!user_range_ok((unsigned long)a1, 4 * sizeof(int))) return EFAULT;
        m[0] = mouse_state.x;
        m[1] = mouse_state.y;
        m[2] = mouse_state.buttons;
        m[3] = mouse_state.wheel;
        mouse_state.wheel = 0;
        return 0;
    }
    case 220: { /* SYS_NK_FRAME */
        vga_fb_blit_nk_window();
        if (a1) {
            int *o = (int *)(unsigned long)a1;
            if (!user_range_ok((unsigned long)a1, 2 * sizeof(int))) return EFAULT;
            o[0] = nk_win_x;
            o[1] = nk_win_y + FONT_H;
        }
        return 0;
    }
    case 221: {
        if (a1) sb16_pcm_open();
        else    sb16_pcm_close();
        return sb16_present() ? 1 : 0;
    }
    case 222: {
        const unsigned char *pcm = (const unsigned char *)a1;
        long len = a2;
        if (len < 0) return -EFAULT;
        if (!user_range_ok((unsigned long)a1, (unsigned long)len)) return -EFAULT;
        return sb16_pcm_submit(pcm, (unsigned)len);
    }
    case 224: sb16_pump(); return 0;
    case 229: return sb16_stream_open();
    case 230: sb16_stream_close((int)a1); return 0;
    case 232: {
        const unsigned char *pcm = (const unsigned char *)a2;
        long len = a3;
        if (len < 0) return -EFAULT;
        if (!user_range_ok((unsigned long)a2, (unsigned long)len)) return -EFAULT;
        return sb16_stream_submit((int)a1, pcm, (unsigned)len);
    }
    case 233:
        sb16_stream_volume((int)a1, (unsigned char)a2);
        return 0;
    case 206: { /* SYS_PALETTE */
        unsigned char *pal = (unsigned char *)a1;
        if (!user_range_ok((unsigned long)a1, 768)) return -EFAULT;
        outb(0x3C8, 0);
        for (int i = 0; i < 768; i++) {
            outb(0x3C9, pal[i] >> 2);
        }
        return 0;
    }
    case 5: { /* fstat */
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
    case 10: return 0;
    case 13: return 0;
    case 14: return 0;
    case 186: return 1;
    case 234: { /* tgkill */
        int sig = (int)a3;
        static const int fatal[] = {1,2,3,4,5,6,7,8,9,11,13,14,15};
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
    case 87: { /* unlink */
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
    case 74: return 0;
    case 21: { /* access */
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
    case 89: return -22;
    case 96: /* gettimeofday */
        if (a1) {
            unsigned long *tv = (unsigned long *)a1;
            if (!user_range_ok((unsigned long)a1, 2 * sizeof(unsigned long))) return EFAULT;
            unsigned long lo = 0, hi = 0;
            __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
            unsigned long tsc = ((unsigned long)hi << 32) | lo;
            unsigned long ms = tsc / 1000000UL;
            tv[0] = ms / 1000;
            tv[1] = (ms % 1000) * 1000;
        }
        return 0;
    case 267: return -2;
    case 273: return 0;
    case 301: return 0;
    case 302: return 0;
    case 318: { /* getrandom */
        unsigned char *buf = (unsigned char *)a1;
        unsigned long cnt = a2;
        if (cnt > 0 && !user_range_ok((unsigned long)buf, cnt)) return EFAULT;
        unsigned long lo = 0, hi = 0;
        for (unsigned long i = 0; i < cnt; i++) {
            if ((i & 7) == 0) {
                __asm__ volatile("rdtsc" : "=a"(lo), "=d"(hi));
            }
            buf[i] = (unsigned char)((lo >> (8 * (i & 7))) ^ (hi & 0xFF) ^ i);
        }
        return (long)cnt;
    }
    case 334: return -1;
    case 79: { /* getcwd */
        char *buf = (char *)a1;
        unsigned long sz = (unsigned long)a2;
        if (!buf || sz == 0) return -22;
        if (!user_range_ok((unsigned long)buf, sz)) return EFAULT;
        unsigned long cwd_len = (unsigned long)kstrlen(fs_cwd);
        if (sz < cwd_len + 1) return -34;
        for (unsigned long i = 0; i <= cwd_len; i++) buf[i] = fs_cwd[i];
        return (long)(cwd_len + 1);
    }
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
    case 223: { /* SYS_GFX_SET_TITLE */
        const char *t = (const char *)(unsigned long)a1;
        if (!t) return EFAULT;
        if (!user_range_ok((unsigned long)t, 1)) return EFAULT;
        extern const char *gfx_win_title;
        static char title_buf[32];
        int i;
        for (i = 0; i < 31 && ((const char *)t)[i]; i++)
            title_buf[i] = ((const char *)t)[i];
        title_buf[i] = 0;
        gfx_win_title = title_buf;
        return 0;
    }
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

    static vma_node_t parent_vma_pool_copy[VMA_MAX];
    for (int i = 0; i < vma_pool_n; i++)
        parent_vma_pool_copy[i] = vma_pool[i];
    vma_node_t *parent_live_root = vma_live_root;
    vma_node_t *parent_free_root = vma_free_root;
    int parent_pool_n = vma_pool_n;

    KFILE *saved_kfd[KFD_MAX];
    for (int i = 0; i < KFD_MAX; i++) saved_kfd[i] = kfd_table[i];

    int swap_saved = 0;
    unsigned long window_sz = 0;
    if (etype == ET_EXEC || etype == ET_DYN) {
        unsigned long parent_top = USER_LOAD_BASE + 0x1000;
        volatile unsigned long *scan =
            (volatile unsigned long *)USER_LOAD_END;
        while (scan > (volatile unsigned long *)USER_LOAD_BASE) {
            scan = (volatile unsigned long *)((unsigned long)scan - 0x1000);
            int all_zero = 1;
            for (int j = 0; j < 512; j++) {
                if (scan[j] != 0) { all_zero = 0; break; }
            }
            if (!all_zero) {
                parent_top = (unsigned long)scan + 0x1000;
                break;
            }
        }
        if (g_brk > parent_top) parent_top = g_brk;
        if (parent_top < USER_STACK_BASE) parent_top = USER_STACK_BASE;
        window_sz = parent_top - USER_LOAD_BASE;
        if (window_sz < 0x1000) window_sz = 0x1000;
        if (window_sz > 64UL * 1024 * 1024) window_sz = 64UL * 1024 * 1024;

        swap_saved = swap_out(window_sz);
    }

    int rc = EFAULT;
    if (etype == ET_REL) {
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
        void *entry = load_exec_elf((void *)data, data_size);
        int did_redirect = 0;
        if (redirect && redirect[0]) did_redirect = redirect_begin();
        if (entry)
            rc = k_exec_user(entry, child_argc,
                             kargv ? (char **)kargv : (char **)child_argv);
        if (did_redirect) redirect_commit(redirect, 0);
    }

    if (swap_saved) {
        swap_in();
    }
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
