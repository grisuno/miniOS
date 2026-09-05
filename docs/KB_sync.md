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
  the exiting process slept on (future work when drivers adopt this).

## Lock discipline

- One guard spinlock per object, always taken with irqsave. Guards are
  leaf-level: they are never held across `schedule()` and never nested
  inside another guard. Each primitive drops its guard before sleeping
  and re-acquires it in a retry loop afterwards.
- Callers loop on their predicate around every sleep (Mesa semantics):
  between the predicate check and `sleep_on`, the queue guard is dropped
  with interrupts re-enabled, so a wake-up can arrive first and the
  sleeper must re-test the condition on return.
- No priority inheritance, no deadlock detection, no recursion: locking
  a held mutex twice deadlocks exactly like a double `spin_lock`.

## Provided primitives

| Primitive | Semantics |
|-----------|-----------|
| `mutex_t` | Binary, non-recursive, owner tracked (pid). Unlock wakes one waiter; the woken sleeper retries acquisition (no handoff). |
| `sem_t` | Counting (`sem_init` clamps negatives to 0). Each `sem_post` wakes at most one waiter. |
| `cond_t` | Mesa condition variable. `cond_wait` unlocks the mutex, sleeps, relocks before returning. Always paired with a mutex. |
| `rwlock_t` | Writer-preferring: readers proceed unless a writer holds; a writer needs zero readers and no writer. Last reader out wakes one waiter; write unlock broadcasts. |

## SMP notes (separate from correctness today)

- `sys_ticks` is incremented with `__sync_fetch_and_add` because the
  BSP's PIT and every AP's LAPIC timer share `isr_dispatch` (vector 32).
- `smp_ap_entry` publishes `cpu_count` under `smp_lock` (irqsave), so
  concurrent APs cannot interleave the update.
- APs still idle in `hlt` and never enter `schedule()`; the primitives
  are correct for BSP use now and lock-correct for AP use later.

## Verification

- `make test-sync`: 8 host groups (empty-queue safety, block/wake,
  FIFO order, mutex ownership and contender handoff, semaphore counting,
  cond unlock/relock, rwlock reader/writer exclusion, no-proc no-op).
  `kernel/sync.c` is dependency-free by design (only `sched.h` plus
  `spinlock.h`), so the host build exercises the real file. Privileged
  instructions never execute on the host: `spinlock.h` takes the
  `SYNC_HOST_TEST` branch (atomics only), and `current_pid` maps to the
  test global via `SYNC_HOST_CURRENT_PID` (`sched.h` skips its own
  definition under that macro).
- `make kernel.elf`: zero warnings, `sync.o` linked into the image.
- Not yet covered: BDD boot with `-smp 2` after this change, and
  `mutate.sh` mutants for the new file (follow-up: add
  wake-up-dropped and state-not-blocked mutants).

## Deliberately deferred (with reasons)

- Futex syscalls: need user-address wait plus a table entry in
  `linux_syscall_table[]`; `wait_queue_t` is already the sleeper store.
- ABI version enforcement (`MINIOS_ABI_VERSION`/`MINIOS_EABI_MISMATCH`
  are defined but unchecked): requires the toolchain (`ld`) to stamp
  the version into binaries plus a loader-side reject. Cross-repo work,
  tracked separately; tables and canonical numbers (`progs/minios_abi.h`)
  are already in place.
- Slab allocator / page-cache split and `kmalloc_percpu` wiring: the
  API exists (`kernel/mm.c`), no caller needs it until threads arrive.
- Per-CPU run queues, `idle_proc`, AP `schedule()` plus IPIs: Phase 2.
