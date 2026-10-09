/** Docstring: proc_sec.c -- per-process security state: the Linux seccomp
 * filter chain, no_new_privs, the dumpable flag and the resolved path of the
 * running image. Contract in headers/proc_sec.h and docs/spec/kernel.md
 * ("Linux seccomp-bpf, prctl and /proc/self/exe").
 *
 * Filters are immutable once installed and shared by reference: a node holds
 * one reference on the node below it, a process holds one on its head, so
 * fork and clone inherit a chain with a single increment and the last
 * release frees exactly the nodes nobody else stacks on.
 */
#include "kernel.h"
#include "sched.h"
#include "sanitize.h"
#include "syscalls_proc.h"
#include "seccomp_bpf.h"
#include "proc_sec.h"

#define LINUX_PR_GET_DUMPABLE      3
#define LINUX_PR_SET_DUMPABLE      4
#define LINUX_PR_SET_NAME          15
#define LINUX_PR_GET_NAME          16
#define LINUX_PR_GET_SECCOMP       21
#define LINUX_PR_SET_SECCOMP       22
#define LINUX_PR_SET_NO_NEW_PRIVS  38
#define LINUX_PR_GET_NO_NEW_PRIVS  39
#define LINUX_SECCOMP_MODE_DISABLED 0
#define LINUX_SECCOMP_MODE_STRICT   1
#define LINUX_SECCOMP_MODE_FILTER   2
#define LINUX_SECCOMP_SET_MODE_STRICT  0
#define LINUX_SECCOMP_SET_MODE_FILTER  1
#define LINUX_SECCOMP_GET_ACTION_AVAIL 2
#define LINUX_NR_READ          0
#define LINUX_NR_WRITE         1
#define LINUX_NR_RT_SIGRETURN  15
#define LINUX_NR_EXIT          60
#define LINUX_ERRNO_MAX        4095
#define LINUX_TASK_COMM_LEN    16
/* struct sock_fprog: u16 len, 6 bytes padding, struct sock_filter *. */
#define SOCK_FPROG_SIZE        16
#define SOCK_FPROG_FILTER_OFF  8

#define ERR_ENOMEM  (-12)
#define ERR_EACCES  (-13)
#define ERR_EINVAL  (-22)
#define ERR_ENOSYS  (-38)
#define ERR_EOPNOTSUPP (-95)

typedef struct sec_filter {
    int                ref;
    unsigned           len;
    unsigned           depth;  /* filters in the chain, this one included */
    struct sec_filter *prev;
    sbpf_insn          prog[];
} sec_filter_t;

static sec_filter_t *sec_chain[MAX_PROCS];
static unsigned char sec_nnp[MAX_PROCS];
static unsigned char sec_undumpable[MAX_PROCS];
static unsigned char sec_mode[MAX_PROCS];
static char          sec_exe[MAX_PROCS][RAMDISK_FNAME_LEN];

/* The strict-mode program: read, write, exit and rt_sigreturn only. */
static const sbpf_insn sec_strict_prog[] = {
    { SBPF_LD | SBPF_W | SBPF_ABS, 0, 0, 0 },
    { SBPF_JMP | SBPF_JEQ | SBPF_K, 4, 0, LINUX_NR_READ },
    { SBPF_JMP | SBPF_JEQ | SBPF_K, 3, 0, LINUX_NR_WRITE },
    { SBPF_JMP | SBPF_JEQ | SBPF_K, 2, 0, LINUX_NR_EXIT },
    { SBPF_JMP | SBPF_JEQ | SBPF_K, 1, 0, LINUX_NR_RT_SIGRETURN },
    { SBPF_RET | SBPF_K, 0, 0, SBPF_RET_KILL_PROCESS },
    { SBPF_RET | SBPF_K, 0, 0, SBPF_RET_ALLOW },
};
#define SEC_STRICT_LEN (sizeof(sec_strict_prog) / sizeof(sec_strict_prog[0]))

static int pid_ok(int pid) {
    return pid >= 0 && pid < MAX_PROCS;
}

static void chain_put(sec_filter_t *f) {
    while (f) {
        sec_filter_t *prev = f->prev;
        if (__sync_sub_and_fetch(&f->ref, 1) != 0) return;
        kfree(f);
        f = prev;
    }
}

void proc_sec_inherit(int child, int parent) {
    sec_filter_t *f;
    if (!pid_ok(child)) return;
    proc_sec_release(child);
    if (!pid_ok(parent)) return;
    f = sec_chain[parent];
    if (f) __sync_fetch_and_add(&f->ref, 1);
    sec_chain[child] = f;
    sec_nnp[child] = sec_nnp[parent];
    sec_undumpable[child] = sec_undumpable[parent];
    sec_mode[child] = sec_mode[parent];
    kmemcpy(sec_exe[child], sec_exe[parent], RAMDISK_FNAME_LEN);
}

void proc_sec_release(int pid) {
    sec_filter_t *f;
    if (!pid_ok(pid)) return;
    f = sec_chain[pid];
    sec_chain[pid] = 0;
    chain_put(f);
    sec_nnp[pid] = 0;
    sec_undumpable[pid] = 0;
    sec_mode[pid] = LINUX_SECCOMP_MODE_DISABLED;
    sec_exe[pid][0] = 0;
}

/* execve keeps the filters and no_new_privs (Linux) and makes the fresh
 * image dumpable again. */
void proc_sec_exec(int pid) {
    if (pid_ok(pid)) sec_undumpable[pid] = 0;
}

void proc_sec_set_exe(int pid, const char *resolved) {
    if (!pid_ok(pid) || !resolved) return;
    kstrncpy(sec_exe[pid], resolved, RAMDISK_FNAME_LEN - 1);
    sec_exe[pid][RAMDISK_FNAME_LEN - 1] = 0;
}

const char *proc_sec_exe(int pid) {
    return pid_ok(pid) ? sec_exe[pid] : "";
}

/* Kill per the action: the calling thread, or its whole thread group. */
static void sec_kill(long n, int whole_group) {
    kprintf("seccomp: pid %d killed on syscall %ld\n", current_pid, n);
    if (whole_group) do_group_exit(SECCOMP_KILL_EXIT);
    do_proc_exit(SECCOMP_KILL_EXIT);
}

int proc_sec_filter(long n, long a1, long a2, long a3, long a4, long a5, long a6, long *ret) {
    int pid = current_pid;
    sec_filter_t *f;
    sbpf_data d;
    const syscall_frame_t *sf;
    unsigned best = SBPF_RET_ALLOW;
    int best_rank;
    if (!pid_ok(pid)) return 0;
    f = sec_chain[pid];
    if (!f) return 0;
    d.nr = (int)n;
    d.arch = SBPF_AUDIT_ARCH_X86_64;
    sf = syscall_frame_current();
    d.instruction_pointer = sf ? sf->rip : 0;
    d.args[0] = (unsigned long long)a1;
    d.args[1] = (unsigned long long)a2;
    d.args[2] = (unsigned long long)a3;
    d.args[3] = (unsigned long long)a4;
    d.args[4] = (unsigned long long)a5;
    d.args[5] = (unsigned long long)a6;
    best_rank = sbpf_action_rank(best);
    /* Newest first; a strictly more restrictive action replaces the best,
     * so among equals the most recently installed filter's data wins. */
    for (; f; f = f->prev) {
        unsigned a = sbpf_run(f->prog, f->len, &d);
        int r = sbpf_action_rank(a);
        if (r < best_rank) { best = a; best_rank = r; }
    }
    switch (best & SBPF_RET_ACTION_FULL) {
    case SBPF_RET_ALLOW:
    case SBPF_RET_LOG:
        return 0;
    case SBPF_RET_ERRNO: {
        unsigned e = best & SBPF_RET_DATA;
        if (e > LINUX_ERRNO_MAX) e = LINUX_ERRNO_MAX;
        *ret = -(long)e;
        return 1;
    }
    case SBPF_RET_TRACE:
    case SBPF_RET_USER_NOTIF:
        *ret = ERR_ENOSYS;
        return 1;
    case SBPF_RET_KILL_THREAD:
        sec_kill(n, 0);
        *ret = ERR_ENOSYS;
        return 1;
    default:
        sec_kill(n, 1);
        *ret = ERR_ENOSYS;
        return 1;
    }
}

/* Validate and push one program onto the caller's chain. strict skips the
 * no_new_privs requirement, as Linux strict mode does. */
static long sec_install(const sbpf_insn *prog, unsigned len, int strict) {
    int pid = current_pid;
    sec_filter_t *head, *node;
    unsigned short *scratch;
    unsigned depth;
    if (!pid_ok(pid)) return ERR_EINVAL;
    if (!strict && !sec_nnp[pid]) return ERR_EACCES;
    if (len == 0 || len > SBPF_MAX_INSNS) return ERR_EINVAL;
    head = sec_chain[pid];
    depth = head ? head->depth + 1u : 1u;
    if (depth > SECCOMP_FILTERS_MAX) return ERR_ENOMEM;
    node = (sec_filter_t *)kmalloc(sizeof(sec_filter_t) + len * sizeof(sbpf_insn));
    if (!node) return ERR_ENOMEM;
    kmemcpy(node->prog, prog, len * sizeof(sbpf_insn));
    scratch = (unsigned short *)kmalloc(len * sizeof(unsigned short));
    if (!scratch) { kfree(node); return ERR_ENOMEM; }
    if (sbpf_check(node->prog, len, scratch) != 0) {
        kfree(scratch);
        kfree(node);
        return ERR_EINVAL;
    }
    kfree(scratch);
    node->ref = 1;
    node->len = len;
    node->depth = depth;
    node->prev = head;
    sec_chain[pid] = node;
    if (sec_mode[pid] != LINUX_SECCOMP_MODE_FILTER)
        sec_mode[pid] = strict ? LINUX_SECCOMP_MODE_STRICT : LINUX_SECCOMP_MODE_FILTER;
    return 0;
}

/* Copy a user struct sock_fprog and install it. */
static long sec_install_user(long ufprog) {
    unsigned short len;
    unsigned long uprog;
    SANITIZE_RANGE(ufprog, SOCK_FPROG_SIZE);
    len = *(const unsigned short *)ufprog;
    uprog = *(const unsigned long *)(ufprog + SOCK_FPROG_FILTER_OFF);
    if (len == 0 || len > SBPF_MAX_INSNS) return ERR_EINVAL;
    SANITIZE_RANGE(uprog, (unsigned long)len * sizeof(sbpf_insn));
    return sec_install((const sbpf_insn *)uprog, len, 0);
}

long proc_sec_prctl(long option, long a2, long a3, long a4, long a5) {
    int pid = current_pid;
    proc_t *p = proc_get(pid);
    if (!pid_ok(pid)) return ERR_EINVAL;
    switch (option) {
    case LINUX_PR_SET_NO_NEW_PRIVS:
        if (a2 != 1 || a3 || a4 || a5) return ERR_EINVAL;
        sec_nnp[pid] = 1;
        return 0;
    case LINUX_PR_GET_NO_NEW_PRIVS:
        if (a2 || a3 || a4 || a5) return ERR_EINVAL;
        return sec_nnp[pid];
    case LINUX_PR_SET_DUMPABLE:
        if (a2 != 0 && a2 != 1) return ERR_EINVAL;
        sec_undumpable[pid] = (unsigned char)(a2 == 0);
        return 0;
    case LINUX_PR_GET_DUMPABLE:
        return sec_undumpable[pid] ? 0 : 1;
    case LINUX_PR_SET_NAME: {
        char name[LINUX_TASK_COMM_LEN];
        unsigned long i;
        SANITIZE_RANGE(a2, 1);
        for (i = 0; i + 1 < LINUX_TASK_COMM_LEN; i++) {
            if (!user_range_ok((unsigned long)a2 + i, 1)) break;
            name[i] = ((const char *)a2)[i];
            if (!name[i]) break;
        }
        name[i < LINUX_TASK_COMM_LEN ? i : LINUX_TASK_COMM_LEN - 1] = 0;
        if (p) {
            kstrncpy(p->name, name, sizeof(p->name) - 1);
            p->name[sizeof(p->name) - 1] = 0;
        }
        return 0;
    }
    case LINUX_PR_GET_NAME: {
        char *out = (char *)a2;
        unsigned long i;
        SANITIZE_RANGE(out, LINUX_TASK_COMM_LEN);
        for (i = 0; i < LINUX_TASK_COMM_LEN; i++)
            out[i] = (p && i + 1 < LINUX_TASK_COMM_LEN) ? p->name[i] : 0;
        out[LINUX_TASK_COMM_LEN - 1] = 0;
        return 0;
    }
    case LINUX_PR_GET_SECCOMP:
        return sec_mode[pid];
    case LINUX_PR_SET_SECCOMP:
        if (a2 == LINUX_SECCOMP_MODE_STRICT)
            return sec_install(sec_strict_prog, SEC_STRICT_LEN, 1);
        if (a2 == LINUX_SECCOMP_MODE_FILTER) return sec_install_user(a3);
        return ERR_EINVAL;
    default:
        return ERR_EINVAL;
    }
}

long proc_sec_seccomp(long op, long flags, long uargs) {
    switch (op) {
    case LINUX_SECCOMP_SET_MODE_STRICT:
        if (flags || uargs) return ERR_EINVAL;
        return sec_install(sec_strict_prog, SEC_STRICT_LEN, 1);
    case LINUX_SECCOMP_SET_MODE_FILTER:
        if (flags) return ERR_EINVAL;
        return sec_install_user(uargs);
    case LINUX_SECCOMP_GET_ACTION_AVAIL: {
        unsigned action;
        if (flags) return ERR_EINVAL;
        SANITIZE_RANGE(uargs, sizeof(unsigned));
        action = *(const unsigned *)uargs;
        switch (action) {
        case SBPF_RET_KILL_PROCESS: case SBPF_RET_KILL_THREAD: case SBPF_RET_TRAP:
        case SBPF_RET_ERRNO: case SBPF_RET_USER_NOTIF: case SBPF_RET_TRACE:
        case SBPF_RET_LOG: case SBPF_RET_ALLOW:
            return 0;
        default:
            return ERR_EOPNOTSUPP;
        }
    }
    default:
        return ERR_EINVAL;
    }
}
