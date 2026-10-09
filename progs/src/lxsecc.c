/** lxsecc.c - Linux seccomp-bpf, prctl and /proc/self/exe probe (FreeDom
 * readiness step 5, docs/spec/kernel.md "Linux seccomp-bpf, prctl and
 * /proc/self/exe").
 *
 * Exercises exactly what FreeDom's tab worker relies on: re-exec through
 * /proc/self/exe, no_new_privs, the dumpable flag, and a seccomp filter whose
 * allowlist, ERRNO and KILL actions, W^X argument check, inheritance across
 * fork, stacking and strict mode all behave like Linux. Every filter is
 * installed in a forked child so the probe itself stays unconfined. Prints
 * "lxsecc: <check> ok" or "lxsecc: <check> FAIL <detail>", then "lxsecc: all
 * ok" with exit 0, or "lxsecc: <n> failed" with exit 1.
 */
#define _GNU_SOURCE
#include <errno.h>
#include <linux/audit.h>
#include <linux/filter.h>
#include <linux/seccomp.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <unistd.h>

#define LXSECC_EXEC_FLAG    "--exec-child"
#define LXSECC_EXEC_CODE    42
#define LXSECC_OK_CODE      0
#define LXSECC_BAD_CODE     3
#define LXSECC_EXE_MAX      256
#define LXSECC_NAME         "lxsecc-name"
#define LXSECC_NAME_MAX     16
#define LXSECC_ERRNO_A      EPERM
#define LXSECC_ERRNO_B      EACCES
#define LXSECC_PAGE         4096
#define LXSECC_STATUS_MASK  0x7f
#define LXSECC_STATUS_SHIFT 8
#define LXSECC_STATUS_BYTE  0xff

static int failures;

static void report(const char *name, int ok, const char *detail) {
    if (ok) printf("lxsecc: %s ok\n", name);
    else { printf("lxsecc: %s FAIL %s\n", name, detail ? detail : ""); failures++; }
    fflush(stdout);
}

/* Exit code of a reaped child under both encodings: Linux's status word
 * (code << 8, signal in the low bits) and MiniOS's raw code. A signal death
 * reads as its nonzero signal number. */
static int exit_code_of(int st) {
    if ((st & LXSECC_STATUS_MASK) == 0) return (st >> LXSECC_STATUS_SHIFT) & LXSECC_STATUS_BYTE;
    return st;
}

static int run_child(void (*body)(void)) {
    pid_t pid = fork();
    if (pid == 0) {
        body();
        syscall(SYS_exit_group, LXSECC_BAD_CODE);
    }
    if (pid < 0) return -1;
    int st = -1;
    if (waitpid(pid, &st, 0) != pid) return -1;
    return exit_code_of(st);
}

/* Filter: arch guard, getpid -> ERRNO(err_getpid), write/exit/exit_group/
 * rt_sigreturn/mprotect(no PROT_EXEC)/fork paths allowed, all else KILL. */
static int install_filter(unsigned getpid_action) {
    struct sock_filter f[] = {
        BPF_STMT(BPF_LD | BPF_W | BPF_ABS, offsetof(struct seccomp_data, arch)),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, AUDIT_ARCH_X86_64, 1, 0),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL_PROCESS),
        BPF_STMT(BPF_LD | BPF_W | BPF_ABS, offsetof(struct seccomp_data, nr)),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SYS_getpid, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, getpid_action),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SYS_mprotect, 0, 4),
        BPF_STMT(BPF_LD | BPF_W | BPF_ABS, offsetof(struct seccomp_data, args[2])),
        BPF_JUMP(BPF_JMP | BPF_JSET | BPF_K, PROT_EXEC, 0, 1),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL_PROCESS),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SYS_write, 7, 0),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SYS_exit, 6, 0),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SYS_exit_group, 5, 0),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SYS_rt_sigreturn, 4, 0),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SYS_clone, 3, 0),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SYS_wait4, 2, 0),
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SYS_set_robust_list, 1, 0),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL_PROCESS),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW),
    };
    struct sock_fprog prog = { (unsigned short)(sizeof f / sizeof f[0]), f };
    if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) != 0) return -1;
    return prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog, 0, 0);
}

static void child_errno_action(void) {
    if (install_filter(SECCOMP_RET_ERRNO | LXSECC_ERRNO_A) != 0) syscall(SYS_exit_group, LXSECC_BAD_CODE);
    errno = 0;
    long r = syscall(SYS_getpid);
    syscall(SYS_exit_group, (r == -1 && errno == LXSECC_ERRNO_A) ? LXSECC_OK_CODE : LXSECC_BAD_CODE);
}

static void child_kill_action(void) {
    if (install_filter(SECCOMP_RET_ERRNO | LXSECC_ERRNO_A) != 0) syscall(SYS_exit_group, LXSECC_BAD_CODE);
    syscall(SYS_getppid);
    syscall(SYS_exit_group, LXSECC_OK_CODE);
}

/* The page is the child's own anonymous mapping, made before the filter
 * (which forbids mmap): a copy-on-write page shared with the parent would
 * test the kernel's CoW rules instead of the filter's argument check. */
static void child_wx(void) {
    void *page = mmap(NULL, LXSECC_PAGE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (page == MAP_FAILED) syscall(SYS_exit_group, LXSECC_BAD_CODE);
    ((volatile unsigned char *)page)[0] = 1;
    if (install_filter(SECCOMP_RET_ERRNO | LXSECC_ERRNO_A) != 0) syscall(SYS_exit_group, LXSECC_BAD_CODE);
    if (syscall(SYS_mprotect, page, LXSECC_PAGE, PROT_READ | PROT_WRITE) != 0)
        syscall(SYS_exit_group, LXSECC_BAD_CODE);
    syscall(SYS_mprotect, page, LXSECC_PAGE, PROT_READ | PROT_EXEC);
    syscall(SYS_exit_group, LXSECC_OK_CODE);
}

static void grandchild_inherits(void) {
    errno = 0;
    long r = syscall(SYS_getpid);
    syscall(SYS_exit_group, (r == -1 && errno == LXSECC_ERRNO_A) ? LXSECC_OK_CODE : LXSECC_BAD_CODE);
}

static void child_inherit(void) {
    if (install_filter(SECCOMP_RET_ERRNO | LXSECC_ERRNO_A) != 0) syscall(SYS_exit_group, LXSECC_BAD_CODE);
    long pid = syscall(SYS_clone, SIGCHLD, 0, 0, 0, 0);
    if (pid == 0) grandchild_inherits();
    int st = -1;
    syscall(SYS_wait4, pid, &st, 0, 0);
    syscall(SYS_exit_group, exit_code_of(st) == LXSECC_OK_CODE ? LXSECC_OK_CODE : LXSECC_BAD_CODE);
}

static void child_stacked(void) {
    /* Older filter kills getpid, newer one only fails it: KILL wins. */
    if (install_filter(SECCOMP_RET_KILL_PROCESS) != 0) syscall(SYS_exit_group, LXSECC_BAD_CODE);
    if (install_filter(SECCOMP_RET_ERRNO | LXSECC_ERRNO_B) != 0) syscall(SYS_exit_group, LXSECC_BAD_CODE);
    syscall(SYS_getpid);
    syscall(SYS_exit_group, LXSECC_OK_CODE);
}

static void child_strict(void) {
    if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_STRICT, 0, 0, 0) != 0) syscall(SYS_exit_group, LXSECC_BAD_CODE);
    if (syscall(SYS_write, 1, "", 0) != 0) syscall(SYS_exit_group, LXSECC_BAD_CODE);
    syscall(SYS_getpid);
    syscall(SYS_exit, LXSECC_OK_CODE);
}

static void child_no_nnp(void) {
    struct sock_filter f[] = { BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW) };
    struct sock_fprog prog = { 1, f };
    errno = 0;
    int r = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog, 0, 0);
    syscall(SYS_exit_group, (r == -1 && errno == EACCES) ? LXSECC_OK_CODE : LXSECC_BAD_CODE);
}

static void child_bad_program(void) {
    struct sock_filter f[] = {
        BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, 0, 9, 0),
        BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW),
    };
    struct sock_fprog prog = { 2, f };
    if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) != 0) syscall(SYS_exit_group, LXSECC_BAD_CODE);
    errno = 0;
    int r = prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &prog, 0, 0);
    syscall(SYS_exit_group, (r == -1 && errno == EINVAL) ? LXSECC_OK_CODE : LXSECC_BAD_CODE);
}

static void check_prctl_flags(void) {
    int nnp0 = prctl(PR_GET_NO_NEW_PRIVS, 0, 0, 0, 0);
    int dump0 = prctl(PR_GET_DUMPABLE, 0, 0, 0, 0);
    int dump_set = prctl(PR_SET_DUMPABLE, 0, 0, 0, 0) == 0 && prctl(PR_GET_DUMPABLE, 0, 0, 0, 0) == 0;
    prctl(PR_SET_DUMPABLE, 1, 0, 0, 0);
    errno = 0;
    int dump_bad = prctl(PR_SET_DUMPABLE, 7, 0, 0, 0) == -1 && errno == EINVAL;
    char name[LXSECC_NAME_MAX + 1];
    memset(name, 0, sizeof name);
    int name_ok = prctl(PR_SET_NAME, LXSECC_NAME, 0, 0, 0) == 0 &&
                  prctl(PR_GET_NAME, name, 0, 0, 0) == 0 && strcmp(name, LXSECC_NAME) == 0;
    errno = 0;
    int unknown = prctl(0x7fff, 0, 0, 0, 0) == -1 && errno == EINVAL;
    report("prctl-nnp-default", nnp0 == 0, "no_new_privs set before anyone asked");
    report("prctl-dumpable", dump0 == 1 && dump_set, "dumpable flag not recorded");
    report("prctl-dumpable-bad", dump_bad, "dumpable 7 not EINVAL");
    report("prctl-name", name_ok, "PR_SET_NAME/PR_GET_NAME mismatch");
    report("prctl-unknown", unknown, "unknown option not EINVAL");
}

static void check_proc_self_exe(const char *argv0) {
    char exe[LXSECC_EXE_MAX];
    ssize_t n = readlink("/proc/self/exe", exe, sizeof exe - 1);
    if (n > 0) exe[n] = '\0';
    const char *base = (n > 0) ? strrchr(exe, '/') : NULL;
    base = base ? base + 1 : exe;
    report("readlink-proc-self-exe", n > 0 && strncmp(base, "lxsecc", 6) == 0, "unexpected target");
    pid_t pid = fork();
    if (pid == 0) {
        char *const av[] = { (char *)argv0, (char *)LXSECC_EXEC_FLAG, NULL };
        execv("/proc/self/exe", av);
        _exit(LXSECC_BAD_CODE);
    }
    int st = -1;
    if (pid > 0) waitpid(pid, &st, 0);
    report("execve-proc-self-exe", pid > 0 && exit_code_of(st) == LXSECC_EXEC_CODE, "re-exec did not run this image");
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], LXSECC_EXEC_FLAG) == 0) {
        printf("lxsecc: exec child ran\n");
        return LXSECC_EXEC_CODE;
    }
    check_prctl_flags();
    report("seccomp-needs-nnp", run_child(child_no_nnp) == LXSECC_OK_CODE, "filter installed without no_new_privs");
    check_proc_self_exe(argv[0]);
    report("seccomp-errno-action", run_child(child_errno_action) == LXSECC_OK_CODE, "getpid did not fail EPERM");
    int killed = run_child(child_kill_action);
    report("seccomp-kill-action", killed != LXSECC_OK_CODE && killed != LXSECC_BAD_CODE && killed > 0,
           "forbidden syscall did not kill");
    int wx = run_child(child_wx);
    report("seccomp-wx-arg-check", wx != LXSECC_OK_CODE && wx != LXSECC_BAD_CODE && wx > 0,
           "PROT_EXEC mprotect did not kill");
    report("seccomp-inherited-by-fork", run_child(child_inherit) == LXSECC_OK_CODE, "child lost the filter");
    int stacked = run_child(child_stacked);
    report("seccomp-stacked-most-restrictive", stacked != LXSECC_OK_CODE && stacked != LXSECC_BAD_CODE && stacked > 0,
           "newer ERRNO filter overrode an older KILL");
    int strict = run_child(child_strict);
    report("seccomp-strict-mode", strict != LXSECC_OK_CODE && strict != LXSECC_BAD_CODE && strict > 0,
           "strict mode let getpid through");
    report("seccomp-invalid-program", run_child(child_bad_program) == LXSECC_OK_CODE, "bad program not EINVAL");
    if (failures == 0) {
        printf("lxsecc: all ok\n");
        return 0;
    }
    printf("lxsecc: %d failed\n", failures);
    return 1;
}
