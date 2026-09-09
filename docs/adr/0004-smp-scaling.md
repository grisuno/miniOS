# ADR-0004: SMP scaling (futex, per-CPU runqueues, batch, RCU-lite)

Status: accepted

## Context

SMP bring-up (ADR-0003) left one global `sched_lock`, one trap per
syscall, and reader locking on shared paths: correct but contended.
The scheduling model stays 1:1 CLONE_VM threads with a non-preemptible
kernel outside explicit points; the goal was to remove contention and
trap overhead without changing that model.

## Decision

Four additive contracts, each in one kernel file plus a minimal header,
layout constants in `progs/minios_abi.h`, ABI bumped to version 2:
futexes (`FUTEX_WAIT/WAKE`, syscalls 226/227, lost-wakeup-free via a
shared bucket lock, userland 0/1/2-state mutex with `-ENOSYS`
degradation); per-CPU runqueues with one non-blocking steal per remote
ring (`kernel/percpu_rq.c`); batched submission of side-effect-light
opcodes (syscall 235, descriptors copied in, no TOCTOU); RCU-lite epoch
grace periods over the 100 Hz ticks (`kernel/rcu.c`, bounded queues,
`RCU_ERR_TIMEOUT` never hangs).

## Consequences

Host-tested (`make test-futex test-percpu-rq test-batch test-rcu`),
mutation-covered, BDD-proved by `thdemo` (futex mutexes, AP steals
visible in the `smp` builtin). Deliberately out of scope: lock-free
everything, kernel preemption, M:N threading, per-CPU allocators.
