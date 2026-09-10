# ADR-0013: Priority inheritance on blocking mutexes

Status: accepted

## Context

Futex-backed mutexes and `rwlock_t` had no inversion control: a
low-priority holder blocking a high-priority waiter could starve the
system with no bound, unacceptable for real-time claims.

## Decision

`kernel/sync.c`: transitive priority inheritance on `mutex_t`.
`pi_set_base` assigns base priorities (default 0); contention records a
waiter-to-owner edge and `pi_boost` donates up the blocked-on chain
(bounded `MAX_PROCS` walk); `mutex_unlock` clears queued edges and
`pi_recompute` restores each holder to `max(base, live donations)`.
`mutex_trylock` is the non-blocking, never-deadlocking acquisition for
re-enterable paths. State lives in pid-indexed parallel arrays because
`proc_t` was 248 bytes by asm contract when written (312 since the
Phase 0 FPU work in ADR-0014; `sched.c` asserts, `syscall_entry`
derives) and must not grow carelessly. Scheduler policy honoring `pi_get_eff` in
the pick path is explicit future work, not silent scope: the mechanism
is complete and host-tested, the policy hook is documented.

## Consequences

Inversion is bounded by the holder's critical section, never by
unrelated medium-priority work. Host-tested (`make test-sync`: boost,
transitive propagation, base restore, trylock); kernel callers
unchanged (no in-kernel `mutex_*` users yet besides tests).
