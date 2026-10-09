/** Docstring: proc_sec.h -- per-process security state behind the Linux
 * prctl/seccomp ABI and /proc/self/exe (docs/spec/kernel.md, "Linux
 * seccomp-bpf, prctl and /proc/self/exe").
 *
 * Kept beside the PCB, indexed by pid, so proc_t (whose size the syscall
 * entry assembly hardcodes) does not grow: the seccomp filter chain,
 * no_new_privs, the dumpable flag and the resolved path of the running
 * image. sched.c calls the lifecycle hooks (inherit on fork/clone, keep on
 * execve, release on reap); syscalls.c calls the filter on every syscall and
 * routes prctl, seccomp and the /proc/self/exe lookups here.
 */
#ifndef PROC_SEC_H
#define PROC_SEC_H

/* Stacked filters per process and instructions per filter. */
#define SECCOMP_FILTERS_MAX 32
/* Exit code of a process or thread a filter kills: a death by SIGSYS
 * (31), recorded negative like every MiniOS signal death, so wait4 reports
 * WIFSIGNALED with WTERMSIG == SIGSYS. */
#define SECCOMP_KILL_EXIT (-31)

/* Lifecycle (callers hold sched_lock where noted in sched.c). */
void proc_sec_inherit(int child, int parent);
void proc_sec_release(int pid);
void proc_sec_exec(int pid);
void proc_sec_set_exe(int pid, const char *resolved);
/* Resolved image path of pid ("" when unknown). */
const char *proc_sec_exe(int pid);

/* Run the caller's filters for syscall n. Returns 1 and stores the value
 * the syscall must answer in *ret when a filter decided it (ERRNO, TRACE,
 * USER_NOTIF); kills the caller for KILL and TRAP; returns 0 to let the
 * syscall run. */
int proc_sec_filter(long n, long a1, long a2, long a3, long a4, long a5, long a6, long *ret);

long proc_sec_prctl(long option, long a2, long a3, long a4, long a5);
long proc_sec_seccomp(long op, long flags, long uargs);

#endif
