#ifndef SYSCALLS_PROC_H
#define SYSCALLS_PROC_H

/* syscalls_proc.h -- process-management syscall handlers shared with the
 * dispatcher (kernel/syscalls.c).  These handlers touch only scheduler
 * state (current_pid, procs[], do_* / seccomp_* / yield) plus the
 * kernel-wide user_range_ok validator, so they live in their own TU
 * (kernel/syscalls_proc.c) instead of the syscalls.c mega-dispatcher.
 * The dispatch tables keep referencing them by these names. */

long sys_minios_seccomp(long a1, long a2, long a3, long a4, long a5, long a6);
long sys_minios_nice(long a1, long a2, long a3, long a4, long a5, long a6);
long sys_minios_clone(long flags, long newsp, long a3, long a4, long a5, long a6);
long sys_minios_thread_spawn(long a1, long a2, long a3, long a4, long a5, long a6);
long sys_linux_yield(long a1, long a2, long a3, long a4, long a5, long a6);
long sys_linux_getpid(long a1, long a2, long a3, long a4, long a5, long a6);
long sys_linux_gettid(long a1, long a2, long a3, long a4, long a5, long a6);
long sys_linux_fork(long a1, long a2, long a3, long a4, long a5, long a6);
long sys_linux_vfork(long a1, long a2, long a3, long a4, long a5, long a6);
long sys_linux_execve(long a1, long a2, long a3, long a4, long a5, long a6);
long sys_linux_exit(long a1, long a2, long a3, long a4, long a5, long a6);
long sys_linux_wait4(long a1, long a2, long a3, long a4, long a5, long a6);
long sys_linux_kill(long a1, long a2, long a3, long a4, long a5, long a6);

/* Shared exit path for sys_linux_exit and the exit_group fall-through. */
long do_proc_exit(long code);

#endif
