# ADR-0014: Syscall truthfulness pass (FreeDom readiness Phase 0)

Status: accepted

## Context

A browser is the first program that depends on syscalls telling the
truth. Games tolerate lies by omission; a real userspace does not. The
audit found six classes of untruth in the Linux-ABI surface, plus three
latent scheduler bugs and two mutation-harness bugs that the work
exposed on the way. MiniOS ABI version is bumped 5 -> 6; the checksum
covers the corrected numbers.

## Decision

**0.1 Per-thread FPU/SSE state.** `ctx_sw.S` saved GPRs only, so two
float-heavy threads corrupted each other's XMM/x87 on every preempt.
Each `proc_t` now owns a 512-byte fxsave image (`fpu_save`, heap so the
64-entry table grows by 8 bytes/slot, never 512: a 32 KB `.bss` growth
would overflow `USER_LOAD_BASE`). The switch asm fxsave/fxrstors around
the GPR move (null skips for idle contexts); the preempt park
(`sched_save_preempt`) saves before parking because `switch_to_notrap`
restores but never saves. Fresh images carry the architectural default
(x87 CW `0x037F`, tag `0xFF`, MXCSR `0x1F80`): an all-zero image would
run new threads at single precision with unmasked exceptions.
`progs/bin/fptest` (2 threads x 4000 SSE+x87 iters across yields and
timer/AP preempts, MXCSR control-bit check, distinct-tid and getrandom
smoke) is the BDD proof; it also kills the no-restore, preempt-no-save
and stack-misalignment mutants.

**0.2/0.3 One clock.** `clock_gettime` returned zeros and `gettimeofday`
pinned `tv_usec` to 0. Both now derive from `wall_us_now()`: the CMOS
RTC anchors whole seconds, the calibrated TSC (`ktime_us`, overflow-safe
split-quotient conversion in `ktime.h`, host-tested) supplies the
fraction, rebased at every RTC edge so ordering holds across it.
`CLOCK_MONOTONIC` reads the TSC directly. The shell `clock` builtin and
BDD scenario pin monotonicity; `make test-ktime` pins the arithmetic.

**0.4 Real tids.** `gettid` returned 1 and `set_tid_address` returned 1
without recording. Both return `current_pid` now (per-CPU via the GS
base); the robust-list slot itself arrives in Phase 1.B, documented at
the stub. `fptest` asserts distinct positive tids.

**0.5 Real entropy.** `getrandom` emitted TSC XOR loop index, predictable
from boot time. It now folds RDRAND (when CPUID offers it, 10-try
bounded) with TSC/tick/pid jitter through splitmix64 (`randmix.h`,
host-tested distribution and avalanche). A dead source still walks
because the increment lives inside the mixer.

**0.6 ABI audit.** `tools/check_abi_numbers.py` freezes the Linux x86-64
table and fails the build (via `make lint`) on undocumented drift.
Fixed: flock 74->73, fsync/fdatasync added at 74/75, statx 267->332,
set_robust_list 301->273 (301 stays a fossil alias answering 0).
Deviations (the 200-block shadows, 202-as-futex, 213, 238-240, 300-302)
are listed in the script with justification; the REAL conflicts
(getdents64/217, clock_getres/229, clock_nanosleep/230,
epoll_wait/232, epoll_ctl/233) are marked with their Phase 1.A/1.B/2.2
fix schedule instead of being silently accepted.

## Bugs found on the way (fixed in the same pass)

- **Stale `imulq $304` in `syscall_entry`** (`kernel.c`): the exit path
  hardcoded the pre-FPU stride while the entry derived it from
  `PROC_T_SIZE`, so every thread resolved to the wrong kstack (waitpid
  returned parked return addresses as exit codes). Both immediates now
  derive from the macros; `kstack_base` too.
- **`sched_park_as_returned` read one frame too deep**: the noinline
  leaf had no frame of its own, so the walk parked the caller's return
  address as the resume rip and waitpid resumed past its own reap. It is
  `always_inline` now, built on `__builtin_return_address` /
  `__builtin_frame_address`, and also restores the caller's rbp.
- **Voluntary switches lost callee-saved registers**: the switch saves
  `schedule()`'s live regs, not its caller's; a resumed `do_waitpid`
  inherited `schedule()`'s r13d as its pid and matched nothing forever
  (the thdemo hang). `sched.o` builds with `-ffixed-rbx/r12-r15`, so the
  caller's set rides through untouched; the Makefile comment names the
  exact hang a removed flag reopens.
- **Thread stacks violated SysV alignment**: the kernel enters through
  `iretq` (no pushed return address), so the raw top left every frame 8
  bytes off and glibc's first `movaps` spill faulted. `mthreads.h`
  reserves the phantom return address (`-8`); the fptest movaps canary
  kills the regression.

## Harness fixes (same pass)

- `mutate.sh` only backed up `SOURCES`; mutants touching `ctx_sw.S`,
  `minios_abi.h`, `ktime.h`, `randmix.h`, `sched.h` or `mthreads.h` were
  never restored (the fpu residue disabled fxsave/fxrstor in-tree for
  days). All touched files are backed up now.
- `--match` selected mutants AND filtered BDD scenarios through the same
  `MATCH` variable, so a targeted mutant run skipped every scenario and
  SURVIVED vacuously. The suite now always runs with `MATCH=""`, and a
  BDD log with a "0 passed" summary is BROKEN, never SURVIVED.

## Consequences

A host-built static ELF now gets Linux numbers for time, tids, random
and the corrected file syscalls; the FPU, clock, tid and ABI proofs run
in `make lint` (checker), `make test-host` (ktime, randmix) and the BDD
suite (fptest, clock). The 200-block shadows remain until their
scheduled phases; each carries its ADR reference in the checker so a
future fix removes the entry instead of rediscovering the conflict.
`proc_t` is 312 bytes (was 248 at ADR-0013 time, then 304); the asm
contract (macros + `_Static_assert`s) holds by construction.
