# KB_sync: Blocking Synchronization (Roadmap Phase 3.1)

Theory and implementation notes for the blocking sync layer:
`sync.h` (API), `kernel/sync.c` (implementation), `tests/test_sync.c`
(host suite, `make test-sync`).

## Why this layer exists

`spinlock.h` gives single-level mutual exclusion with interrupts off, but
a spinlock must never be held across a blocking operation: a driver that
spins waiting for a disk or a keyboard wastes the whole CPU and, under
SMP, can deadlock against the CPU holding the data. The blocking layer
solves this by parking the waiter in the scheduler instead of spinning:

- `wait_queue_t`: an intrusive FIFO of PIDs chained through the new
  `proc_t.wq_next` field (`sched.h`, `WQ_NONE` sentinel). No allocation,
  no overflow: at most `MAX_PROCS` entries can ever be queued.
- `sleep_on(q)`: marks the current process `PROC_BLOCKED` while holding
  the queue lock with interrupts disabled, enqueues it, drops the lock,
  then calls `schedule()`. The timer-ISR dispatch only picks `PROC_READY`,
  so the sleeper can neither be lost nor double-scheduled.
- `wake_up(q)` / `wake_up_all(q)`: dequeue from the head (FIFO) and mark
  `PROC_READY`. Waking a non-blocked entry only fixes the state if it is
  still `PROC_BLOCKED`, so a PID reused between sleep and wake cannot be
  corrupted into `READY` by a stale queue entry... except a PID slot that
  was freed and re-created: callers must pair every sleep site with a
  wake site on all exit paths, and `do_exit` must drain or disown queues
  the exiting process slept on. The futex layer unlinks a reaped slot
  (`futex_forget`, called from the proc free path), but a generic
  `wait_queue_t` still has no exit-time drain: a driver that sleeps a
  process on its own queue must pair every sleep with a wake.

## Lock discipline

- One guard spinlock per object, always taken with irqsave. Guards are
  leaf-level: they are never held across `schedule()` and never nested
  inside another guard. Each primitive drops its guard before sleeping
  and re-acquires it in a retry loop afterwards.
- Callers loop on their predicate around every sleep (Mesa semantics):
  between the predicate check and `sleep_on`, the queue guard is dropped
  with interrupts re-enabled, so a wake-up can arrive first and the
  sleeper must re-test the condition on return.
- No deadlock detection and no recursion: locking a held mutex twice
  deadlocks exactly like a double `spin_lock`. `mutex_trylock` probes
  without blocking.
- Priority inheritance is implemented: a holder blocked by a
  higher-priority waiter is boosted to the waiter's effective priority,
  transitively along the blocked-on chain, and drops back to its base
  when it releases (`pi_boost`/`pi_recompute` in `kernel/sync.c`).

## Provided primitives

| Primitive | Semantics |
|-----------|-----------|
| `mutex_t` | Binary, non-recursive, owner tracked (pid). Unlock wakes one waiter; the woken sleeper retries acquisition (no handoff). Priority inheritance lifts a low-priority holder to its highest waiter's level until it releases. |
| `mutex_trylock` | Non-blocking acquire: 0 on success, -1 when the mutex is held. Never sleeps. |
| `sem_t` | Counting (`sem_init` clamps negatives to 0). Each `sem_post` wakes at most one waiter. |
| `cond_t` | Mesa condition variable. `cond_wait` unlocks the mutex, sleeps, relocks before returning. Always paired with a mutex. |
| `rwlock_t` | Writer-preferring: a queued writer announces itself and new readers yield, so a reader stream cannot starve it. A writer needs zero readers and no writer. Last reader out wakes the waiters; write unlock broadcasts. `rwlock_read_trylock`/`rwlock_write_trylock` are the non-blocking forms. |

## SMP notes

- `sys_ticks` is incremented with `__sync_fetch_and_add` because the
  BSP's PIT and every AP's LAPIC timer share `isr_dispatch` (vector 32).
- `smp_ap_entry` publishes `cpu_count` under `smp_lock` (irqsave), so
  concurrent APs cannot interleave the update.
- APs no longer only idle: `smp_ap_idle_loop` claims CLONE_VM threads
  and switches to them, so the primitives now run on more than one CPU.
  An AP never claims a non-CLONE_VM process (its brk/mmap/VMA view
  stays with the BSP), and the BSP idle remains the fallback runner.

## Verification

- `make test-sync`: 10 host groups (empty-queue safety, block/wake,
  FIFO order, mutex ownership and contender handoff, semaphore counting,
  cond unlock/relock, rwlock reader/writer exclusion, no-proc no-op,
  priority inheritance with `trylock`, transitive inheritance).
  `kernel/sync.c` is dependency-free by design (only `sched.h` plus
  `spinlock.h`), so the host build exercises the real file. Privileged
  instructions never execute on the host: `spinlock.h` takes the
  `SYNC_HOST_TEST` branch (atomics only), and `current_pid` maps to the
  test global via `SYNC_HOST_CURRENT_PID` (`sched.h` skips its own
  definition under that macro).
- `make kernel.elf`: zero warnings, `sync.o` linked into the image.
- Not yet covered: a BDD boot that exercises the primitives on an AP
  under `-smp 2`, and `mutate.sh` mutants for `kernel/sync.c` (the file
  is still absent from the `SOURCES` allowlist, so the wake-up-dropped
  and state-not-blocked mutants are still owed).

## Deliberately deferred (with reasons)

Each item below was deferred when the layer landed; the first word says
where it stands today.

- Futex syscalls: shipped. `kernel/futex.c` reuses `wait_queue_t` for
  its sleepers; 202 serves Linux `futex(2)`, and the MiniOS pair
  226/227 (`futex_wait`/`futex_wake`) rides the same queues.
- ABI version enforcement: half shipped. The version and the checksum
  are stamped into the ramdisk manifest `etc/abi` and checked at boot
  (`kernel/abi.c` halts on a mismatch), but the loader still reads
  neither: Linux-ABI binaries carry no MiniOS version note, so a
  load-time gate stays cross-repo work (a version note emitted by `ld`
  plus a loader check scoped to MiniOS-toolchain binaries).
- Slab allocator / page-cache split and `kmalloc_percpu` wiring: no
  such API exists in `kernel/mm.c`; the page cache (`fs/pcache.c`) and
  the per-CPU run queues (`kernel/percpu_rq.c`) are there, but nothing
  needs a per-CPU allocator yet.
- Per-CPU run queues, `idle_proc`, AP `schedule()` plus IPIs: shipped.
  `kernel/percpu_rq.c` keeps the per-CPU rings with work stealing, the
  AP idle context is `ap_idle_proc[]`, APs run CLONE_VM threads, and
  `smp_ipi_broadcast` delivers the wake-up vector.
