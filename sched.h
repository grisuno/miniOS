#ifndef SCHED_H
#define SCHED_H

#include <stdint.h>

/* ---- Process states ---- */
#define PROC_FREE       0
#define PROC_READY      1
#define PROC_RUNNING    2
#define PROC_BLOCKED    3
#define PROC_ZOMBIE     4

/* ---- Limits ---- */
#define MAX_PROCS       64
#define PROC_KSTACK_SZ  (16UL * 1024)

/* ---- Per-process saved registers (offsets must match ctx_sw.S) ---- */
typedef struct {
    uint64_t rax, rbx, rcx, rdx;
    uint64_t rsi, rdi, rbp;
    uint64_t r8, r9, r10, r11;
    uint64_t r12, r13, r14, r15;
    uint64_t rip, rsp, rflags;
    uint64_t cr3;
} ctx_regs_t;

/* ---- Process Control Block ---- */
typedef struct {
    ctx_regs_t  ctx;
    int         pid;
    int         state;
    int         parent_pid;
    int         exit_code;
    uint64_t    kstack;         /* top of kernel stack for this proc */
    uint64_t    brk;
    char        name[32];
} proc_t;

/* ---- Global state ---- */
extern proc_t  procs[MAX_PROCS];
extern int     proc_count;
extern int     current_pid;
extern volatile uint64_t sys_ticks;

/* ---- Functions ---- */
void     sched_init(void);
int      proc_create(const char *name, int parent_pid);
proc_t  *proc_get(int pid);
void     schedule(void);
void     switch_to(proc_t *prev, proc_t *next);
void     yield(void);
void     do_exit(int code);
int      do_waitpid(int pid);
int      do_kill(int pid);
void     timer_tick(void);

/* ---- Per-process page tables ---- */
uint64_t pt_clone_user(uint64_t parent_cr3);
void     pt_free_user(uint64_t cr3);

#endif
