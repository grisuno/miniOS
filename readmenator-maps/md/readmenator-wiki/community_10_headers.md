# headers

*Community 10 | 20 files | cohesion 0.38*

## Definition

This community groups 20 file(s) rooted at `headers` with dominant language c (cohesion 0.38). Central symbols: `BOOT_CPU`, `BSP`, `CHECK`, `CLONE_FILES`, `CLONE_VM`, `COM1`, `COND_INIT`, `CTX_RBP_OFF`. Core file: `kernel/syscalls.c` (141 symbols). Documented purpose: Docstring: futex.h -- Fast userspace mutex sleep/wake contract..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/futex.h` | h | utility | 17 | yes |
| `headers/percpu_rq.h` | h | utility | 14 | yes |
| `headers/rcu.h` | h | utility | 17 | yes |
| `headers/sched.h` | h | utility | 120 | yes |
| `headers/spawn.h` | h | utility | 9 | yes |
| `headers/spinlock.h` | h | utility | 19 | yes |
| `headers/sync.h` | h | utility | 36 | yes |
| `headers/syscalls_proc.h` | h | utility | 15 | yes |
| `kernel/futex.c` | c | utility | 7 | yes |
| `kernel/mm.c` | c | utility | 7 | yes |
| `kernel/percpu_rq.c` | c | utility | 9 | yes |
| `kernel/rcu.c` | c | utility | 14 | yes |
| `kernel/sched.c` | c | utility | 107 | no |
| `kernel/serial.c` | c | utility | 9 | yes |
| `kernel/sync.c` | c | utility | 26 | yes |
| `kernel/syscalls.c` | c | utility | 141 | yes |
| `tests/test_futex.c` | c | testing | 6 | yes |
| `tests/test_percpu_rq.c` | c | testing | 2 | yes |
| `tests/test_rcu.c` | c | testing | 4 | yes |
| `tests/test_sync.c` | c | testing | 6 | yes |

## Key Symbols

- `FUTEX_H` (macro, `headers/futex.h:2`) `#define FUTEX_H`
- `FUTEX_BUCKETS` (macro, `headers/futex.h:51`) `#define FUTEX_BUCKETS`
- `FUTEX_BUCKET_MASK` (macro, `headers/futex.h:52`) `#define FUTEX_BUCKET_MASK`
- `FUTEX_HASH_GOLDEN` (macro, `headers/futex.h:53`) `#define FUTEX_HASH_GOLDEN`
- `FUTEX_OK` (macro, `headers/futex.h:55`) `#define FUTEX_OK`
- `FUTEX_NOMATCH` (macro, `headers/futex.h:56`) `#define FUTEX_NOMATCH`
- `FUTEX_NOPROC` (macro, `headers/futex.h:57`) `#define FUTEX_NOPROC`
- `FUTEX_WAKE_ALL` (macro, `headers/futex.h:58`) `#define FUTEX_WAKE_ALL`
- `LINUX_FUTEX_WAIT` (macro, `headers/futex.h:64`) `#define LINUX_FUTEX_WAIT`
- `LINUX_FUTEX_WAKE` (macro, `headers/futex.h:65`) `#define LINUX_FUTEX_WAKE`
- `LINUX_FUTEX_PRIVATE_FLAG` (macro, `headers/futex.h:66`) `#define LINUX_FUTEX_PRIVATE_FLAG`
- `futex_bucket_t` (struct, `headers/futex.h:68`)
- `futex_init` (function, `headers/futex.h:74`) `void futex_init(void);`
- `futex_wait` (function, `headers/futex.h:75`) `long futex_wait(unsigned long uaddr, int val);`
- `futex_wake` (function, `headers/futex.h:76`) `long futex_wake(unsigned long uaddr, int n);`
- `FUTEX_PRIVATE_FLAG` (function, `headers/futex.h:79`) `* FUTEX_PRIVATE_FLAG (process-private is served on the same global * buckets: sa`
- `futex_linux_cmd` (function, `headers/futex.h:84`) `int futex_linux_cmd(long op);` - Decode a Linux futex(2) op to LINUX_FUTEX_WAIT/WAKE, masking FUTEX_PRIVATE_FLAG (process-private is
- `PERCPU_RQ_H` (macro, `headers/percpu_rq.h:2`) `#define PERCPU_RQ_H`
- `RQ_DEPTH` (macro, `headers/percpu_rq.h:45`) `#define RQ_DEPTH`
- `RQ_RESCAN_PERIOD` (macro, `headers/percpu_rq.h:46`) `#define RQ_RESCAN_PERIOD`
- `RQ_VALIDATE_ATTEMPTS` (macro, `headers/percpu_rq.h:47`) `#define RQ_VALIDATE_ATTEMPTS`
- `WQ_NONE_HINT` (macro, `headers/percpu_rq.h:48`) `#define WQ_NONE_HINT`
- `percpu_rq_t` (struct, `headers/percpu_rq.h:50`)
- `rq_init` (function, `headers/percpu_rq.h:61`) `void rq_init(void);`
- `rq_enqueue` (function, `headers/percpu_rq.h:62`) `void rq_enqueue(int cpu, int pid);`
- `rq_pop_local` (function, `headers/percpu_rq.h:63`) `int rq_pop_local(int cpu);`
- `rq_steal_once` (function, `headers/percpu_rq.h:64`) `int rq_steal_once(int self_cpu, int *from_cpu);`
- `rq_empty` (function, `headers/percpu_rq.h:65`) `int rq_empty(int cpu);`
- `rq_should_rescan` (function, `headers/percpu_rq.h:66`) `int rq_should_rescan(int cpu);`
- `rq_note_poll` (function, `headers/percpu_rq.h:67`) `void rq_note_poll(int cpu);`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 35
- Cross-boundary resolved imports (EXTRACTED): 57

## Connections

- [EXTRACTED] depends_on community 4 <-> 10 (strength 0.9): Extracted import edge crosses communities: drivers/kbd.c imports headers/sched.h.
- [EXTRACTED] depends_on community 5 <-> 10 (strength 0.9): Extracted import edge crosses communities: drivers/pcm2.c imports headers/sched.h.
- [EXTRACTED] depends_on community 9 <-> 10 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports headers/spinlock.h.
- [EXTRACTED] depends_on community 0 <-> 10 (strength 0.9): Extracted import edge crosses communities: headers/smp.h imports headers/spinlock.h.

## Risks

- [dataflow DEAD_STORE] `kernel/sched.c:465` `irqstat_report` `txf`: `txf` assigned at line 465 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:1212` `syscall` `wheel`: `wheel` assigned at line 1212 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:1865` `proc_spawn_elf_inner` `frame`: `frame` assigned at line 1865 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:1963` `schedule` `cpu`: `cpu` assigned at line 1963 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:2384` `MSR` `frame`: `frame` assigned at line 2384 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:2594` `do_execve` `frame`: `frame` assigned at line 2594 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:2793` `it` `cr3`: `cr3` assigned at line 2793 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/syscalls.c:388` `sys_minios_gfx_zoom` `gfx_zoom_2x`: `gfx_zoom_2x` assigned at line 388 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/syscalls.c:671` `sys_minios_gfx_title` `gfx_win_title`: `gfx_win_title` assigned at line 671 but never read afterwards.

## Open Questions

- Why do 1 file(s) lack file-level docs (e.g. `kernel/sched.c`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.38?

## Sources

- `headers/futex.h`
- `headers/percpu_rq.h`
- `headers/rcu.h`
- `headers/sched.h`
- `headers/spawn.h`
- `headers/spinlock.h`
- `headers/sync.h`
- `headers/syscalls_proc.h`
- `kernel/futex.c`
- `kernel/mm.c`
- `kernel/percpu_rq.c`
- `kernel/rcu.c`
- `kernel/sched.c`
- `kernel/serial.c`
- `kernel/sync.c`
- `kernel/syscalls.c`
- `tests/test_futex.c`
- `tests/test_percpu_rq.c`
- `tests/test_rcu.c`
- `tests/test_sync.c`
