/* syscalls_proc.c - Process-management syscall handlers.
 *
 * First increment of the syscalls.c decomposition: the proc-leaf
 * handlers move here verbatim from kernel/syscalls.c.  Each handler
 * touches only scheduler state (current_pid, procs[], do_* /
 * seccomp_* / yield) plus the kernel-wide user_range_ok validator, so
 * this TU includes only kernel.h and sched.h.  The dispatch tables in
 * syscalls.c keep referencing these functions by their original names
 * (declared in syscalls_proc.h); no behaviour changes.
 */

#include "kernel.h"
#include "sched.h"

long sys_minios_clone(long flags, long newsp, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    if (newsp && !user_range_ok((unsigned long)newsp, 8)) return EFAULT;
    return do_clone(flags, newsp);
}

long sys_minios_thread_spawn(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a4; (void)a5; (void)a6;
    unsigned long fn = (unsigned long)a1;
    unsigned long stack = (unsigned long)a2;
    if (!fn || !stack) return -1;
    if (!user_range_ok(fn, 1)) return EFAULT;
    if (!user_range_ok(stack - 8, 8)) return EFAULT;
    return do_thread_spawn(fn, stack, (unsigned long)a3);
}

/* Seccomp-basic (238): a1 = op (1 deny-one, 2 allow-one, 3 deny-all),
 * a2 = syscall number (ops 1-2). Applies to current_pid only; the
 * 200..231 window is filterable, Linux numbers never are. */
long sys_minios_seccomp(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    int pid = current_pid;
    if (a1 == SECCOMP_OP_DENY_ONE) return seccomp_deny_one(pid, (int)a2);
    if (a1 == SECCOMP_OP_ALLOW_ONE) return seccomp_allow_one(pid, (int)a2);
    if (a1 == SECCOMP_OP_DENY_ALL) {
        int n;
        if (pid < 0 || pid >= MAX_PROCS) return -1;
        if (procs[pid].state == PROC_FREE) return -1;
        for (n = SECCOMP_MIN; n <= SECCOMP_MAX; n++) procs[pid].seccomp_deny |= SECCOMP_BIT(n);
        procs[pid].seccomp_deny &= ~SECCOMP_BIT(MINIOS_SYS_TIME);
        return 0;
    }
    return -22;
}

/* Nice (239): a1 = new nice when a2 != 0, else query. Clamped NICE_MIN..NICE_MAX. */
long sys_minios_nice(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a3; (void)a4; (void)a5; (void)a6;
    int pid = current_pid;
    if (pid < 0 || pid >= MAX_PROCS || procs[pid].state == PROC_FREE) return -3;
    if (a2) {
        int n = (int)a1;
        if (n < NICE_MIN) n = NICE_MIN;
        if (n > NICE_MAX) n = NICE_MAX;
        procs[pid].nice = n;
    }
    return procs[pid].nice;
}

long sys_linux_yield(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    yield(); return 0;
}

long sys_linux_getpid(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return 1;
}

long sys_linux_fork(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return -38;
}

long sys_linux_vfork(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return -38;
}

long sys_linux_execve(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return -38;
}

/* Shared by sys_linux_exit (60) and the exit_group fall-through (231).
 * pid 0 is the k_exec_user context (the shell running an ET_EXEC
 * program, or a SYS_SPAWN child): its exit must klongjmp back to the
 * shell.  proc_count is the wrong discriminator there: threads
 * registered by the program make it > 1 even though this context is
 * still the exec frame.  Every other pid (forked children, threads)
 * exits through the scheduler as a ZOMBIE for the parent to reap. */
long do_proc_exit(long code) {
    if (current_pid != 0) {
        do_exit((int)code);
        return 0;
    }
    exec_exit_code = (int)code;
    klongjmp(&exec_return, 1);
    return 0;
}

long sys_linux_exit(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return do_proc_exit(a1);
}

/* wait4(pid, status, options, rusage): options bit 0 is WNOHANG (Linux
 * ABI value 1). Non-blocking returns 0 when no child exited yet (status
 * untouched); blocking reaps like before. The status word carries the raw
 * exit code (no WEXITSTATUS encoding: MiniOS reports codes directly). */
long sys_linux_wait4(long a1, long a2, long a3, long a4, long a5, long a6) {
    int *status = (int *)a2;
    int options = (int)a3;
    (void)a4; (void)a5; (void)a6;
    if (a2 && !user_range_ok((unsigned long)a2, sizeof(int))) return EFAULT;
    if (options & 1) {
        int code = do_waitpid_nb((int)a1);
        if (code == WAITPID_NONE) return 0;
        if (status) *status = code;
        return (int)a1 >= 0 ? (int)a1 : 0;
    }
    {
        int code = do_waitpid((int)a1);
        if (status) *status = code;
        return code;
    }
}

long sys_linux_kill(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return do_kill((int)a1);
}

long sys_linux_gettid(long a1, long a2, long a3, long a4, long a5, long a6) {
    /* Phase 0.4: the thread's own pid, not a constant 1. Every
     * thread_spawn/clone child owns a distinct pid and current_pid
     * resolves per-CPU via the GS base, so pthread_self layers on top. */
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return (long)current_pid;
}
