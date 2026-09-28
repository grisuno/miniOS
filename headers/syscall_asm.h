#ifndef SYSCALL_ASM_H
#define SYSCALL_ASM_H

/* syscall_asm.h -- numeric contract for arch/x86/syscall_entry.S.
 *
 * The syscall trampoline is raw assembly and cannot use C, so every
 * immediate it needs lives here as a plain number. This file carries
 * NO C declarations on purpose: it is #included both by kernel.c and
 * by the .S file, and anything beyond #defines would choke the
 * assembler. Each value mirrors a C macro (named in the comment);
 * kernel.c proves the equality with _Static_asserts, so editing the
 * C side without this file fails the build instead of stranding a
 * stale stride in the entry path (the 0a92118 imulq drift). */

#define SYSCALL_USER_WIN_LO     0x00400000  /* == MINIOS_USER_LOAD_BASE */
#define SYSCALL_USER_WIN_HI     0x0C000000  /* == MINIOS_USER_LOAD_END */
#define SYSCALL_PROC_T_SIZE     336         /* == PROC_T_SIZE (sched.h) */
#define SYSCALL_PROC_KSTACK_OFF 168         /* == PROC_KSTACK_OFF */
#define SYSCALL_MAX_PROCS       64          /* == MAX_PROCS */
#define SYSCALL_CPU_CUR_PID_OFF 12          /* offsetof(cpu_t, cur_pid) */
#define SYSCALL_CPU_SC_N_OFF    72          /* offsetof(cpu_t, sc_n) */
#define SYSCALL_CPU_SC_RIP_OFF  80          /* offsetof(cpu_t, sc_rip) */
#define SYSCALL_CPU_SC_PID_OFF  88          /* offsetof(cpu_t, sc_pid) */
#define SYSCALL_CPU_SC_RET_OFF  96          /* offsetof(cpu_t, sc_ret) */
#define SYSCALL_CPU_SC_TMP_OFF  112         /* offsetof(cpu_t, sc_tmp) */

#endif
