# headers

*Community 14 | 3 files | cohesion 0.40*

## Definition

This community groups 3 file(s) rooted at `headers` with dominant language c (cohesion 0.40). Central symbols: `CHECK`, `EFAULT`, `SANITIZE_COPY_IN`, `SANITIZE_H`, `SANITIZE_LEN_NEG`, `SANITIZE_RANGE`, `SANITIZE_STR`, `code`. Core file: `kernel/syscalls_proc.c` (14 symbols). Documented purpose: Docstring: sanitize.h -- Single choke point for syscall argument checks..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/sanitize.h` | h | utility | 5 | yes |
| `kernel/syscalls_proc.c` | c | utility | 14 | yes |
| `tests/test_sanitize.c` | c | testing | 9 | yes |

## Key Symbols

- `SANITIZE_H` (macro, `headers/sanitize.h:2`) `#define SANITIZE_H`
- `SANITIZE_LEN_NEG` (macro, `headers/sanitize.h:32`) `#define SANITIZE_LEN_NEG(var)`
- `SANITIZE_RANGE` (macro, `headers/sanitize.h:37`) `#define SANITIZE_RANGE(ptr, len)`
- `SANITIZE_STR` (macro, `headers/sanitize.h:43`) `#define SANITIZE_STR(ptr, maxlen)`
- `SANITIZE_COPY_IN` (macro, `headers/sanitize.h:49`) `#define SANITIZE_COPY_IN(kbuf, uptr, count, elemsz)`
- `state` (function, `kernel/syscalls_proc.c:5`) `* touches only scheduler state (current_pid, procs[], do_* / * seccomp_* / yield`
- `sys_minios_clone` (function, `kernel/syscalls_proc.c:16`) `long sys_minios_clone(long flags, long newsp, long a3, long a4, long a5, long a6`
- `sys_minios_thread_spawn` (function, `kernel/syscalls_proc.c:22`) `long sys_minios_thread_spawn(long a1, long a2, long a3, long a4, long a5, long a`
- `sys_minios_seccomp` (function, `kernel/syscalls_proc.c:35`) `long sys_minios_seccomp(long a1, long a2, long a3, long a4, long a5, long a6)` - Seccomp-basic (238): a1 = op (1 deny-one, 2 allow-one, 3 deny-all), a2 = syscall number (ops 1-2). A
- `sys_minios_nice` (function, `kernel/syscalls_proc.c:52`) `long sys_minios_nice(long a1, long a2, long a3, long a4, long a5, long a6)` - if (a1 == SECCOMP_OP_DENY_ONE) return seccomp_deny_one(pid, (int)a2); if (a1 == SECCOMP_OP_ALLOW_ONE
- `sys_linux_yield` (function, `kernel/syscalls_proc.c:65`) `long sys_linux_yield(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_getpid` (function, `kernel/syscalls_proc.c:70`) `long sys_linux_getpid(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_fork` (function, `kernel/syscalls_proc.c:75`) `long sys_linux_fork(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_vfork` (function, `kernel/syscalls_proc.c:80`) `long sys_linux_vfork(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_execve` (function, `kernel/syscalls_proc.c:85`) `long sys_linux_execve(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_exit` (function, `kernel/syscalls_proc.c:161`) `long sys_linux_exit(long a1, long a2, long a3, long a4, long a5, long a6)`
- `code` (function, `kernel/syscalls_proc.c:169`) `* exit code (no WEXITSTATUS encoding: MiniOS reports codes directly). */ long sy`
- `sys_linux_kill` (function, `kernel/syscalls_proc.c:188`) `long sys_linux_kill(long a1, long a2, long a3, long a4, long a5, long a6)`
- `sys_linux_gettid` (function, `kernel/syscalls_proc.c:193`) `long sys_linux_gettid(long a1, long a2, long a3, long a4, long a5, long a6)`
- `EFAULT` (macro, `tests/test_sanitize.c:13`) `#define EFAULT`
- `user_range_ok` (function, `tests/test_sanitize.c:20`) `int user_range_ok(unsigned long p, unsigned long len)`
- `user_str_ok` (function, `tests/test_sanitize.c:26`) `int user_str_ok(unsigned long p, unsigned long maxlen)`
- `kmemcpy` (function, `tests/test_sanitize.c:32`) `void *kmemcpy(void *dst, const void *src, unsigned long n)`
- `CHECK` (macro, `tests/test_sanitize.c:41`) `#define CHECK(cond, msg)`
- `range_probe` (function, `tests/test_sanitize.c:48`) `static long range_probe(unsigned long p, long len)`
- `str_probe` (function, `tests/test_sanitize.c:54`) `static long str_probe(unsigned long p)`
- `copy_probe` (function, `tests/test_sanitize.c:61`) `static long copy_probe(unsigned long uptr, long count, unsigned long elemsz)`
- `main` (function, `tests/test_sanitize.c:67`) `int main(void)`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 2
- Cross-boundary resolved imports (EXTRACTED): 3

## Connections

- No cross-community bridges recorded. This community is self-contained.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.40?

## Sources

- `headers/sanitize.h`
- `kernel/syscalls_proc.c`
- `tests/test_sanitize.c`
