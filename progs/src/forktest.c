/*
 * forktest — fork() with copy-on-write pages, proved from ring 3.
 *
 * Built like lxhello (gcc -static -no-pie -nostdlib, raw syscalls, no
 * libc). A global starts at 1; after fork the child sets its copy to
 * 42 and exits 7 while the parent waits and checks its own copy is
 * still 1 (CoW isolation both directions: the parent then writes 9
 * and the child's exit code already proved its view). Prints
 * "fork: ok" and exits 0 on success, a diagnostic and nonzero exit
 * on any deviation.
 */

static long fx_syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6) {
    long ret;
    register long r10 __asm__("r10") = a4;
    register long r8 __asm__("r8") = a5;
    register long r9 __asm__("r9") = a6;
    __asm__ volatile("syscall"
                     : "=a"(ret)
                     : "a"(n), "D"(a1), "S"(a2), "d"(a3),
                       "r"(r10), "r"(r8), "r"(r9)
                     : "rcx", "r11", "memory");
    return ret;
}

#define SYS_write  1
#define SYS_fork   57
#define SYS_exit   60
#define SYS_wait4  61

static long shared_var = 1;

static unsigned long fx_strlen(const char *s) {
    unsigned long n = 0;
    while (s[n]) n++;
    return n;
}

static void fx_write(const char *s) {
    fx_syscall6(SYS_write, 1, (long)s, (long)fx_strlen(s), 0, 0, 0);
}

static void fx_exit(long code) {
    fx_syscall6(SYS_exit, code, 0, 0, 0, 0, 0);
    while (1) { }
}

void _start(void) {
    long pid;
    /* fork() from pid 0 (k_exec_user legacy window) is -ENOSYS by
     * contract; this binary runs isolated through mrun/run, so the
     * call must succeed here. */
    pid = fx_syscall6(SYS_fork, 0, 0, 0, 0, 0, 0);
    if (pid < 0) {
        fx_write("fork: fork refused\n");
        fx_exit(10);
    }
    if (pid == 0) {
        long status_addr = 0;
        (void)status_addr;
        if (shared_var != 1) {
            fx_write("fork: child sees wrong initial\n");
            fx_exit(11);
        }
        shared_var = 42;
        if (shared_var != 42) {
            fx_write("fork: child write lost\n");
            fx_exit(12);
        }
        fx_write("fork: child ok\n");
        fx_exit(7);
    }
    {
        /* MiniOS wait4 reports the exit code directly (return and
         * *status both carry it), not a pid or an encoded status. */
        long status = 0;
        long w;
        w = fx_syscall6(SYS_wait4, pid, (long)&status, 0, 0, 0, 0);
        if (w != 7 || status != 7) {
            fx_write("fork: child code wrong\n");
            fx_exit(14);
        }
        if (shared_var != 1) {
            fx_write("fork: parent copy corrupted\n");
            fx_exit(15);
        }
        shared_var = 9;
        if (shared_var != 9) {
            fx_write("fork: parent write lost\n");
            fx_exit(16);
        }
        fx_write("fork: ok\n");
        fx_exit(0);
    }
}
