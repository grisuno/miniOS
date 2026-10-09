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
#include "sanitize.h"
#include "proc_sec.h"
#include "syscalls_proc.h"

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

/* getpid answers the thread group: a CLONE_THREAD member reports its
 * leader, a process its own pid. The pid-0 exec frame (a foreground `run`)
 * and threads it created keep answering 1, the value programs saw before
 * there were real pids. */
long sys_linux_getpid(long a1, long a2, long a3, long a4, long a5, long a6) {
    proc_t *p = proc_get(current_pid);
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    if (p && p->autoreap) return p->tgid > 0 ? p->tgid : 1;
    return current_pid > 0 ? current_pid : 1;
}

/* Linux clone(2): (flags, newsp, parent_tid, child_tid, tls). */
long sys_linux_clone(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a6;
    return do_linux_clone((unsigned long)a1, (unsigned long)a2, (unsigned long)a3,
                          (unsigned long)a4, (unsigned long)a5);
}

long sys_linux_fork(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return do_fork();
}

long sys_linux_vfork(long a1, long a2, long a3, long a4, long a5, long a6) {
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return -38;
}

long sys_linux_execve(long a1, long a2, long a3, long a4, long a5, long a6) {
    const char *upath = (const char *)a1;
    const char *const *uargv = (const char *const *)a2;
    char resolved[RAMDISK_FNAME_LEN];
    char *kargv[EXECVE_MAX_ARGS + 1];
    char *strbuf = 0;
    int kargc = 0;
    long rc;
    (void)a3; (void)a4; (void)a5; (void)a6;
    /* a3 (envp) is ignored: setup_user_stack builds argc/argv only, so
     * every execve starts with an empty environment. Documented, not
     * silent: no caller-supplied pointer is dereferenced. */
    SANITIZE_STR(upath, RAMDISK_FNAME_LEN);
    /* /proc/self/exe re-runs the caller's own image (FreeDom re-execs
     * itself as a tab worker); docs/spec/kernel.md. */
    if (kstrcmp(upath, "/proc/self/exe") == 0) {
        const char *exe = proc_sec_exe(current_pid);
        if (!exe[0]) return -2;
        kstrncpy(resolved, exe, sizeof(resolved) - 1);
        resolved[sizeof(resolved) - 1] = 0;
    } else if (!fs_resolve(upath, resolved, sizeof(resolved))) {
        return -36;
    }
    if (uargv) {
        if (!user_range_ok((unsigned long)uargv, sizeof(char *)))
            return EFAULT;
        strbuf = (char *)kmalloc(
            (unsigned long)EXECVE_MAX_ARGS * EXECVE_MAX_ARG);
        if (!strbuf) return -12;
        for (kargc = 0; kargc <= EXECVE_MAX_ARGS; kargc++) {
            const char *w;
            char *dst;
            unsigned long n;
            if (!user_range_ok((unsigned long)(uargv + kargc),
                               sizeof(char *))) {
                rc = EFAULT;
                goto execve_out;
            }
            w = uargv[kargc];
            if (!w) break;
            if (kargc >= EXECVE_MAX_ARGS) { rc = -7; goto execve_out; }
            /* Bounded per-byte copy: a racing sibling thread can only
             * change content inside the validated window, never push
             * the copy past strbuf (the NUL is guaranteed by
             * construction, overlong words refuse with -E2BIG). */
            dst = strbuf + (unsigned long)kargc * EXECVE_MAX_ARG;
            for (n = 0; n < EXECVE_MAX_ARG; n++) {
                if (!user_range_ok((unsigned long)(w + n), 1)) {
                    rc = EFAULT;
                    goto execve_out;
                }
                dst[n] = w[n];
                if (!w[n]) break;
            }
            if (n >= EXECVE_MAX_ARG) { rc = -7; goto execve_out; }
            kargv[kargc] = dst;
        }
        if (kargc > EXECVE_MAX_ARGS) { rc = -7; goto execve_out; }
    }
    kargv[kargc] = 0;
    /* Success never returns (ring-3 entry through user_trampoline);
     * failure frees strbuf below with the caller untouched. */
    rc = do_execve(resolved, kargc, kargv);
execve_out:
    if (strbuf) kfree(strbuf);
    return rc;
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

/* Linux wait status words (docs/spec/smp-sched.md): a normal exit carries
 * its code in bits 8..15, a death by signal the signal number in bits
 * 0..6. MiniOS records a signal death as a negative exit code: -1 is the
 * historic kill (SIGKILL), -N is signal N (a seccomp kill is -SIGSYS). */
#define LINUX_WNOHANG        1
#define LINUX_SIGKILL        9
#define LINUX_STATUS_SHIFT   8
#define LINUX_STATUS_CODE    0xff
#define LINUX_ECHILD         (-10)
#define LINUX_EINVAL         (-22)
#define LINUX_ESRCH          (-3)

static int linux_wait_status(int code) {
    if (code < 0) {
        int sig = (code == -1) ? LINUX_SIGKILL : -code;
        if (sig <= 0 || sig > LINUX_SIGNAL_MAX) sig = LINUX_SIGKILL;
        return sig;
    }
    return (code & LINUX_STATUS_CODE) << LINUX_STATUS_SHIFT;
}

/* wait4(pid, status, options, rusage): returns the reaped child's pid and
 * stores the Linux status word; WNOHANG returns 0 while nothing has
 * exited; -ECHILD with no matching child. pid -1 is any child; process
 * groups (pid 0 and < -1) are not modelled and wait for any child. */
long sys_linux_wait4(long a1, long a2, long a3, long a4, long a5, long a6) {
    int *status = (int *)a2;
    int options = (int)a3;
    int pid = (int)a1;
    int found = 0;
    int code;
    (void)a4; (void)a5; (void)a6;
    if (a2 && !user_range_ok((unsigned long)a2, sizeof(int))) return EFAULT;
    if (options & ~LINUX_WNOHANG) return LINUX_EINVAL;
    if (pid == 0 || pid < -1) pid = -1;
    code = do_waitpid_linux(pid, (options & LINUX_WNOHANG) != 0, &found);
    if (code == WAITPID_NOCHILD) return LINUX_ECHILD;
    if (code == WAITPID_NONE) return 0;
    if (status) *status = linux_wait_status(code);
    return found;
}

/* Signals whose default action terminates the process. MiniOS installs
 * no user handlers (rt_sigaction is accepted and recorded nowhere), so the
 * default action is the only one: these terminate, every other signal
 * (SIGCHLD, SIGWINCH, SIGCONT, SIGURG, real-time signals) is ignored. */
int linux_signal_fatal(long sig) {
    static const long fatal[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13,
                                  14, 15, 24, 25, 26, 27, 29, 30, 31 };
    unsigned i;
    for (i = 0; i < sizeof(fatal) / sizeof(fatal[0]); i++)
        if (fatal[i] == sig) return 1;
    return 0;
}

/* kill(pid, sig): sig 0 only probes that pid exists; a fatal signal ends
 * the target as killed by sig (wait4 reports WTERMSIG); any other signal
 * is delivered to its default action, ignore. Process groups (pid <= 0)
 * are not modelled. */
long sys_linux_kill(long a1, long a2, long a3, long a4, long a5, long a6) {
    proc_t *t;
    (void)a3; (void)a4; (void)a5; (void)a6;
    if (a2 < 0 || a2 > LINUX_SIGNAL_MAX) return LINUX_EINVAL;
    if (a1 <= 0 || a1 >= MAX_PROCS) return LINUX_ESRCH;
    t = proc_get((int)a1);
    if (!t || t->state == PROC_FREE || t->state == PROC_ZOMBIE) return LINUX_ESRCH;
    if (a2 == 0 || !linux_signal_fatal(a2)) return 0;
    return do_kill_code((int)a1, (int)-a2) == 0 ? 0 : LINUX_ESRCH;
}

long sys_linux_gettid(long a1, long a2, long a3, long a4, long a5, long a6) {
    /* Phase 0.4: the thread's own pid, not a constant 1. Every
     * thread_spawn/clone child owns a distinct pid and current_pid
     * resolves per-CPU via the GS base, so pthread_self layers on top. */
    (void)a1; (void)a2; (void)a3; (void)a4; (void)a5; (void)a6;
    return (long)current_pid;
}
