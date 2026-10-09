/*
 * forktest — fork() with copy-on-write pages, proved from ring 3.
 *
 * Built like lxhello (gcc -static -no-pie -nostdlib, raw syscalls, no
 * libc). A global starts at 1; after fork the child sets its copy to
 * 42 and exits 7 while the parent waits and checks its own copy is
 * still 1 (CoW isolation both directions: the parent then writes 9
 * and the child's exit code already proved its view). A pipe made
 * before the fork proves fd-view isolation the same way: the parent
 * closes its write end at once, the child writes after 2000 yields
 * (a shared table would have lost its slot to the parent's close),
 * and the parent reads the bytes back after the child's closes
 * (prints "fork: fd ok"). Prints "fork: ok" and exits 0 on success,
 * a diagnostic and nonzero exit on any deviation.
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

#define SYS_read   0
#define SYS_write  1
#define SYS_close  3
#define SYS_pipe   22
#define SYS_yield  24
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
    /* Linux pipe() fills int[2], not long[2]: a long array reads both
     * fds packed into one word (seen live as fd 0x400000003). */
    int pfd[2];
    /* Pipe before fork: the fd-isolation leg below proves the child
     * owns a private view (a close on either side never drops the
     * other's handle and written bytes survive the writer's exit). */
    if (fx_syscall6(SYS_pipe, (long)pfd, 0, 0, 0, 0, 0) != 0) {
        fx_write("fork: pipe refused\n");
        fx_exit(9);
    }
    /* fork() from pid 0 (k_exec_user legacy window) is -ENOSYS by
     * contract; this binary runs isolated through mrun/run, so the
     * call must succeed here. */
    pid = fx_syscall6(SYS_fork, 0, 0, 0, 0, 0, 0);
    if (pid < 0) {
        fx_write("fork: fork refused\n");
        fx_exit(10);
    }
    if (pid == 0) {
        long i, w;
        char msg[2];
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
        fx_syscall6(SYS_close, pfd[0], 0, 0, 0, 0, 0);
        /* Let the parent close its write end first: with a shared
         * table that clear would land on our slot too and the write
         * below would fail, which is exactly the regression this leg
         * pins. With private views the order is irrelevant. */
        for (i = 0; i < 2000; i++)
            fx_syscall6(SYS_yield, 0, 0, 0, 0, 0, 0);
        msg[0] = 'h'; msg[1] = 'i';
        w = fx_syscall6(SYS_write, pfd[1], (long)msg, 2, 0, 0, 0);
        if (w != 2) {
            fx_write("fork: fd child write lost\n");
            fx_exit(17);
        }
        fx_syscall6(SYS_close, pfd[1], 0, 0, 0, 0, 0);
        fx_write("fork: child ok\n");
        fx_exit(7);
    }
    {
        /* wait4 follows Linux: it returns the reaped pid and stores the
         * exit code in bits 8..15 of the status word. */
        long status = 0;
        long w;
        char buf[2];
        long r;
        /* Close our write end at once: the child's copy must survive
         * this (and the child's closes must survive below). */
        fx_syscall6(SYS_close, pfd[1], 0, 0, 0, 0, 0);
        w = fx_syscall6(SYS_wait4, pid, (long)&status, 0, 0, 0, 0);
        if (w != pid || status != (7 << 8)) {
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
        /* The child closed both its ends before exiting; our read end
         * must be intact and carry its bytes. */
        r = fx_syscall6(SYS_read, pfd[0], (long)buf, 2, 0, 0, 0);
        if (r != 2 || buf[0] != 'h' || buf[1] != 'i') {
            fx_write("fork: fd read wrong\n");
            fx_exit(18);
        }
        fx_syscall6(SYS_close, pfd[0], 0, 0, 0, 0, 0);
        fx_write("fork: fd ok\n");
        fx_write("fork: ok\n");
        fx_exit(0);
    }
}
