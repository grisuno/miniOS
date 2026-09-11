# Issue #22: Isolation: full namespaces beyond seccomp/rlimit/nice

- **State:** open
- **Created:** 2026-09-10T03:54:52Z
- **Updated:** 2026-09-10T03:54:52Z
- **Labels:** enhancement,isolation

---

ABI v4 already ships SECCOMP (238, deny/allow per-syscall), RLIMIT (240: AS bytes, CPU ticks, NOFILE) and NICE (239, fair-share) — see docs/ABI.md and kernel/syscalls.c dispatch. What is missing vs Linux: mount/pid/net namespaces, i.e. a compromised ring-3 process still sees the single shared filesystem and process table.\n\nScope: decide the namespace subset that fits the single-address-space model (per-process CR3 is the documented Phase 5 prerequisite in CLAUDE.md); implement incrementally behind ABI version bump + _Static_asserts in kernel.c.
