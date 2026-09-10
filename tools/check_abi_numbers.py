#!/usr/bin/env python3
"""check_abi_numbers.py -- MiniOS syscall numbers vs Linux x86-64 truth.

Phase 0.6 of the FreeDom readiness plan: a browser is the first program
that depends on syscalls telling the truth, and several MiniOS numbers
drifted from the Linux table (the class that bit us at [74] = flock
while Linux x86-64 74 = fsync, 73 = flock). A static host-compiled ELF
traps the Linux number and gets whatever MiniOS registered there.

Ground truth is Linux arch/x86/entry/syscalls/syscall_64.tbl
(x86-64 common range), frozen here so the gate needs no kernel headers.
Two checks, both fail-closed (exit 1) on undocumented drift:

Rule A -- compat claims in progs/minios_abi.h: a MINIOS_SYS_FOO whose
  normalized name exists in the Linux table and whose value is < 200
  must equal the Linux number exactly.
Rule B -- MiniOS-wins shadows: a MiniOS number that collides with a
  *different* Linux syscall must be listed in DEVIATIONS with the ADR
  that justifies it (fix or documented deviation, never silence).
Rule C -- dispatch site in kernel/syscalls.c: every
  `[N] = { fn, "name" }` entry of linux_syscall_table and every
  `case N:` fall-through in ksyscall_dispatch must resolve N to the
  Linux number for "name".

Usage: python3 tools/check_abi_numbers.py [--abi PATH] [--syscalls PATH]
Exits 0 printing "abi: ok" when every number is either exact or listed.
"""
import re
import sys

LINUX_X86_64 = {
    "read": 0, "write": 1, "open": 2, "close": 3, "stat": 4,
    "fstat": 5, "lstat": 6, "poll": 7, "lseek": 8, "mmap": 9,
    "mprotect": 10, "munmap": 11, "brk": 12, "rt_sigaction": 13,
    "rt_sigprocmask": 14, "rt_sigreturn": 15, "ioctl": 16,
    "pread64": 17, "pwrite64": 18, "readv": 19, "writev": 20,
    "access": 21, "pipe": 22, "select": 23, "sched_yield": 24,
    "mremap": 25, "msync": 26, "mincore": 27, "madvise": 28,
    "dup": 32, "dup2": 33, "pause": 34, "nanosleep": 35,
    "getpid": 39, "socket": 41, "connect": 42, "accept": 43,
    "sendto": 44, "recvfrom": 45, "sendmsg": 46, "recvmsg": 47,
    "shutdown": 48, "bind": 49, "listen": 50, "getsockname": 51,
    "getpeername": 52, "socketpair": 53, "clone": 56, "fork": 57,
    "vfork": 58, "execve": 59, "exit": 60, "wait4": 61, "kill": 62,
    "uname": 63, "fcntl": 72, "flock": 73, "fsync": 74,
    "fdatasync": 75, "truncate": 76, "ftruncate": 77, "getdents": 78,
    "getcwd": 79, "chdir": 80, "fchdir": 81, "rename": 82,
    "mkdir": 83, "rmdir": 84, "creat": 85, "link": 86, "unlink": 87,
    "symlink": 88, "readlink": 89, "chmod": 90, "fchmod": 91,
    "chown": 92, "fchown": 93, "gettimeofday": 96, "getrlimit": 97,
    "getrusage": 98, "sysinfo": 99, "times": 100, "arch_prctl": 158,
    "gettid": 186, "tkill": 200, "time": 201, "futex": 202,
    "sched_setaffinity": 203, "sched_getaffinity": 204,
    "set_thread_area": 205, "io_setup": 206, "io_destroy": 207,
    "io_getevents": 208, "io_submit": 209, "io_cancel": 210,
    "get_thread_area": 211, "lookup_dcookie": 212, "epoll_create": 213,
    "epoll_ctl_old": 214, "epoll_wait_old": 215,
    "remap_file_pages": 216, "getdents64": 217,
    "set_tid_address": 218, "restart_syscall": 219, "semtimedop": 220,
    "fadvise64": 221, "timer_create": 222, "timer_settime": 223,
    "timer_gettime": 224, "timer_getoverrun": 225, "timer_delete": 226,
    "clock_settime": 227, "clock_gettime": 228, "clock_getres": 229,
    "clock_nanosleep": 230, "exit_group": 231, "epoll_wait": 232,
    "epoll_ctl": 233, "tgkill": 234, "utimes": 235, "vserver": 236,
    "mbind": 237, "set_mempolicy": 238, "get_mempolicy": 239,
    "mq_open": 240, "openat": 257, "mkdirat": 258, "newfstatat": 262,
    "unlinkat": 263, "renameat": 264, "readlinkat": 267,
    "fchmodat": 268, "faccessat": 269, "pselect6": 270, "ppoll": 271,
    "unshare": 272, "set_robust_list": 273, "get_robust_list": 274,
    "utimensat": 280, "epoll_pwait": 281, "eventfd": 284,
    "fallocate": 285, "accept4": 288, "epoll_create1": 291,
    "dup3": 292, "pipe2": 293, "inotify_init1": 294, "preadv": 295,
    "pwritev": 296, "perf_event_open": 298, "recvmmsg": 299,
    "fanotify_init": 300, "fanotify_mark": 301, "prlimit64": 302,
    "renameat2": 316, "seccomp": 317, "getrandom": 318,
    "memfd_create": 319, "statx": 332, "rseq": 334,
}

DEVIATIONS = {
    200: ("dns", "tkill", "ADR-0014: MiniOS net block owns 200+; glibc never traps tkill directly (uses tgkill 234)"),
    201: ("tls_retired", "time", "ADR-0014: retired kernel-TLS slot, always -ENOSYS; glibc time() falls back on ENOSYS"),
    202: ("futex", "futex", "ADR-0014: SHARED, not shadowed: 202 serves Linux futex(2); a fossil tls_send trap fails closed on pointer validation"),
    203: ("tls_retired", "sched_setaffinity", "ADR-0014: retired kernel-TLS slot, always -ENOSYS"),
    204: ("time", "sched_getaffinity", "ADR-0014: MiniOS SYS_TIME shadows affinity; pthread_getaffinity_np sees ms clock, accepted until the 200-block moves"),
    205: ("kbd", "set_thread_area", "ADR-0014: x86-64 threads use arch_prctl 158, never set_thread_area"),
    206: ("palette", "io_setup", "ADR-0014: kernel AIO not implemented; glibc aio path gets palette validation, fail-closed"),
    207: ("kbd_raw", "io_destroy", "ADR-0014: same class as 206"),
    208: ("vga_mode", "io_getevents", "ADR-0014: same class as 206"),
    209: ("pcspk_init", "io_submit", "ADR-0014: same class as 206"),
    210: ("pcspk_tone", "io_cancel", "ADR-0014: same class as 206"),
    211: ("doom_frame", "get_thread_area", "ADR-0014: x86-64 threads use arch_prctl 158, never get_thread_area"),
    212: ("rtc", "lookup_dcookie", "ADR-0014: oprofile-only number, never trapped by libc"),
    213: ("fb_info", "epoll_create", "ADR-0014: modern glibc uses epoll_create1 291; a 213 trap fails closed on pointer validation, never a forged fd"),
    214: ("pcspk_vol", "epoll_ctl_old", "ADR-0014: obsolete number, never trapped"),
    215: ("spawn", "epoll_wait_old", "ADR-0014: obsolete number, never trapped"),
    216: ("lz4_compress", "remap_file_pages", "ADR-0014: exotic number, never trapped by libc"),
    217: ("lz4_decompress", "getdents64", "ADR-0014: REAL conflict, fix scheduled in Phase 1.A: getdents64 takes 217, lz4 pair relocates"),
    219: ("mouse", "restart_syscall", "ADR-0014: kernel-internal number, never trapped by libc"),
    220: ("nk_frame", "semtimedop", "ADR-0014: sysv-ipc number; MiniOS has no sysv ipc, glibc traps it only for shm users"),
    221: ("sb16_open", "fadvise64", "ADR-0014: fadvise is advisory; a trapped call gets stream validation, fail-closed"),
    222: ("sb16_submit", "timer_create", "ADR-0014: posix-timers unimplemented; trap fails closed on validation"),
    223: ("gfx_title", "timer_settime", "ADR-0014: same class as 222"),
    224: ("sb16_pump", "timer_gettime", "ADR-0014: same class as 222"),
    225: ("thread_spawn", "timer_getoverrun", "ADR-0014: same class as 222"),
    226: ("futex_wait", "timer_delete", "ADR-0014: same class as 222"),
    227: ("futex_wake", "clock_settime", "ADR-0014: needs privilege; trap fails closed on validation"),
    229: ("sb16_stream_open", "clock_getres", "ADR-0014: REAL conflict, fix scheduled in Phase 1.B with clock_nanosleep 230"),
    230: ("sb16_stream_close", "clock_nanosleep", "ADR-0014: REAL conflict, fix scheduled in Phase 1.B: timed sleeps take 230, sb16 stream calls relocate"),
    232: ("sb16_stream_submit", "epoll_wait", "ADR-0014: REAL conflict, fix scheduled in Phase 2.2 with the poll wake-up work"),
    233: ("sb16_stream_vol", "epoll_ctl", "ADR-0014: REAL conflict, fix scheduled in Phase 2.2 with the poll wake-up work"),
    235: ("submit_batch", "utimes", "ADR-0014: utimes unimplemented; trap fails closed on opcode validation"),
    236: ("getc_raw", "vserver", "ADR-0014: container-only number, never trapped by libc"),
    237: ("gfx_present", "mbind", "ADR-0014: NUMA not present; trap fails closed on buffer-id validation"),
    238: ("seccomp", "set_mempolicy", "ADR-0014: NUMA not present; MiniOS seccomp-basic owns 238 in-guest"),
    239: ("nice", "get_mempolicy", "ADR-0014: NUMA not present; MiniOS nice owns 239 in-guest"),
    240: ("rlimit", "mq_open", "ADR-0014: posix-mqueue unimplemented; trap fails closed on op validation"),
    300: ("clone", "fanotify_init", "ADR-0014: MiniOS clone alias; Linux clone is 56 (Phase 1.B); fanotify never trapped by libc implicitly"),
    301: ("robust_fossil", "fanotify_mark", "ADR-0014: fossil set_robust_list alias, still answers 0; the true number is 273"),
    302: ("rlimit64", "prlimit64", "ADR-0014: same number, custom semantics (AS/CPU/NOFILE); glibc getrlimit sees 0 = unlimited, which is true"),
}

ABI_RE = re.compile(r"#define\s+(MINIOS_SYS_[A-Z0-9_]+)\s+(\d+)")
TABLE_RE = re.compile(r"\[\s*(\d+)\s*\]\s*=\s*\{\s*\w+\s*,\s*\"([a-z0-9_]+)\"\s*\}")
CASE_RE = re.compile(r"^\s*case\s+(\d+)\s*:[^/]*(?:/\*\s*([a-z0-9_]+))?")


def normalize(minios_name):
    return minios_name[len("MINIOS_SYS_"):].lower()


def parse_abi(path):
    found = {}
    with open(path) as f:
        for line in f:
            m = ABI_RE.search(line)
            if m:
                name, num = m.group(1), int(m.group(2))
                found.setdefault(name, num)
    return found


def parse_dispatch(path):
    table, cases = {}, []
    with open(path) as f:
        for line in f:
            m = TABLE_RE.search(line)
            if m:
                table[int(m.group(1))] = m.group(2)
            m = CASE_RE.match(line)
            if m:
                cases.append((int(m.group(1)), m.group(2) or ""))
    return table, cases


def main():
    import os
    root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    abi_path = sys.argv[sys.argv.index("--abi") + 1] if "--abi" in sys.argv else os.path.join(root, "progs", "minios_abi.h")
    sys_path = sys.argv[sys.argv.index("--syscalls") + 1] if "--syscalls" in sys.argv else os.path.join(root, "kernel", "syscalls.c")
    failures = []

    abi = parse_abi(abi_path)
    linux_by_num = {v: k for k, v in LINUX_X86_64.items()}
    for name, num in sorted(abi.items(), key=lambda kv: kv[1]):
        norm = normalize(name)
        if norm in LINUX_X86_64:
            want = LINUX_X86_64[norm]
            if num != want:
                if num in DEVIATIONS and DEVIATIONS[num][0] in (norm, norm.replace("_", "")):
                    continue
                failures.append("RULE A: %s is %d, Linux x86-64 %s is %d" % (name, num, norm, want))
        else:
            if num in LINUX_X86_64.values() and num not in DEVIATIONS:
                failures.append("RULE B: %s=%d shadows Linux %s with no DEVIATIONS entry" % (name, num, linux_by_num[num]))

    table, cases = parse_dispatch(sys_path)
    for num, disp_name in sorted(table.items()):
        if disp_name in LINUX_X86_64 and LINUX_X86_64[disp_name] != num:
            failures.append("RULE C: dispatch [%d] names %s, Linux number is %d" % (num, disp_name, LINUX_X86_64[disp_name]))

    for num, comment in cases:
        if num not in linux_by_num:
            continue
        want = linux_by_num[num]
        if comment == want:
            continue
        if num in DEVIATIONS:
            continue
        failures.append("RULE C: dispatch case %d (%s) %s" % (
            num, want,
            "has no /* name */ comment" if not comment
            else "comment names %s" % comment))

    mini_os_numbers = set(abi.values())
    abi_name_by_num = {}
    for name, num in abi.items():
        abi_name_by_num.setdefault(num, normalize(name))
    for num in sorted(mini_os_numbers):
        if num not in linux_by_num:
            continue
        if abi_name_by_num.get(num) == linux_by_num[num]:
            continue
        if num in DEVIATIONS:
            continue
        failures.append("RULE B: MiniOS number %d collides with Linux %s, unlisted" % (num, linux_by_num[num]))

    if failures:
        print("abi: DRIFT")
        for f in failures:
            print("  " + f)
        return 1
    print("abi: ok")
    return 0


if __name__ == "__main__":
    sys.exit(main())
