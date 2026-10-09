# SMP, scheduler, tick bus, HAL, preemption, job control and execve

Moved verbatim from CLAUDE.md (2026-09-29 compaction); CLAUDE.md keeps the
rules and hazards and indexes this file.

### SMP (Symmetric Multiprocessing) Foundation

The kernel brings up application processors (APs) at boot using the
standard INIT-edge/SIPI/SIPI sequence through the local APIC.  With
`-smp N` in QEMU, the BSP wakes N-1 APs; without it, the system runs
single-CPU exactly as before.

**Per-CPU data (`sched.h` + `sched.c`):** `cpu_t` stores the LAPIC ID,
`cur_pid`, `syscall_kstack`, idle flag, and BSP flag for each CPU.
`cpus[MAX_CPUS]` (max 8) is the global array; `cpu_count` tracks how many
 CPUs are online.  `this_cpu()` reads the current `cpu_t` via the GS base;
`current_pid` is a macro that expands to `this_cpu()->cur_pid`, so all
scheduler paths (isr_dispatch, schedule, yield, do_exit, do_waitpid)
automatically operate on the correct CPU's state.

**GS base per-CPU (`sched.c` + `syscall_entry` in `arch/x86/syscall_entry.S`):** the BSP
sets `MSR_GSBASE` to `&cpus[0]` during `sched_init()`.  `syscall_entry`
uses `swapgs` to switch to the kernel GS base on entry and back on
`sysretq`/`klongjmp`, so ring-3 code never sees the kernel's per-CPU
data.  APs set their own GS base in `smp_ap_entry()`.

**AP bring-up (`smp.c`):** the BSP maps the local APIC at `0xFEE00000`
(uncached 2 MB in PDPT slot 3), enables the SVR, copies the flat AP
bootstrap stub (`ap_entry.S`) to `AP_STUB_ADDR` (0x6000, below 1 MB for
SIPI), patches the C entry point address, and sends INIT (edge-triggered,
all-excluding-self) followed by two SIPIs.  Each AP runs the stub (real
mode -> protected mode -> long mode), calls `smp_ap_entry()`, initializes
its `cpu_t`, sets GS base, loads the BSP's IDTR, enables its LAPIC SVR
(so it can receive IPIs) with the local timer and both LINT pins masked,
and enters the AP idle loop (`smp_ap_idle_loop`, which claims READY
CLONE_VM threads and otherwise halts).  The AP has no periodic timer of
its own by design: its only tick is the BSP's 100 Hz IPI broadcast, which
wakes the halted AP and drives its preemption ISR.  A LAPIC timer count
derived from `PIT_HZ` must never be used: the LAPIC counts bus clocks, so
that count fires ~84 kHz under QEMU and wedges the machine under an
interrupt storm (measured 2.6x slowdown + 176% host CPU on an idle guest).
The AP does NOT print to the serial console
during init: `kprintf`'s stack usage plus the LAPIC timer ISR trap frame
overflows the identity-mapped low-memory stub stack and cascading
exceptions result.  The BSP prints "SMP: Brought up N CPUs" after
`ap_count` confirms the APs initialized.

**LAPIC ICR bit layout (xAPIC):** the destination shorthand for
"all excluding self" is at bits 19:18 (`0xC0000`), NOT bits 17:16
(`0x30000`, reserved).  The INIT delivery mode is at bits 10:8 (`0x500`).
Level-assert is bit 14 (`0x4000`), level-trigger is bit 15 (`0x8000`).
QEMU 11 hangs on level-triggered INIT (delivery status never clears), so
edge-triggered INIT is used.

**ISR AP-awareness (`sched.c` `isr_dispatch`):** vector 32 (timer) checks
`this_cpu()->is_bsp` to decide whether to send PIC EOI + run `sb16_poll`
(BSP) or LAPIC EOI at `0xFEE000B0` (AP).  The context-switch path is
guarded by `is_bsp` so APs never corrupt the shared `procs[]` table.
APs do not own the PIC, the PS/2 mouse, or the SB16 DMA ring.

**GS validation in the timer ISR (`sched.c` `cpu_or_null`):** a ring-0
context running with a user/stale GS base makes `this_cpu()` read garbage
(typically the mapped IVT at linear 0), and the first field dereference
faults with #GP instead of failing safe.  The vector-32 path validates
the pointer against `cpus[]` first; on failure it EOIs both controllers
best-effort, counts `smp_dbg_bad_gs` (reported by the `smp` builtin, zero
in a healthy boot) and takes no scheduling action.  The known producer of
such a state is the `swapgs` dance in `k_exec_user`, which runs with
interrupts off from the dance through the `iretq` for exactly this
reason.

**AP stub stack (`ap_entry.S`):** the AP's temporary stack is at 0x78000
(identity-mapped low memory, below the LAPIC PD at 0x70000, above the
syscall kernel stack at 0x88000).  This is only needed until
`smp_ap_entry()` sets up the per-CPU context; the idle loop runs on this
same stack.  A stack at 0x80000 overlaps the syscall kernel stack and
causes exception cascades when the LAPIC timer ISR fires.

**BDD tests (`test_bdd.sh`):** `scenario_smp` boots with `-smp 2` and
asserts "SMP: Brought up 2 CPUs"; a single-CPU scenario asserts
"SMP: 1 CPU".  The SMP scenarios run alongside the existing suite.

**Mutation tests (`mutate.sh`):** `smp-icr-shorthand-broken` (wrong bit
position), `smp-init-missing` (no INIT before SIPI), `smp-sipi-vector-zero`
(zero vector), `smp-ap-no-lapic-eoi` (missing AP EOI), `smp-bsp-ctx-switch-not-guarded`
(AP corrupts process table), `smp-gs-base-not-set` (missing GS base).

### SMP Beyond Threads: Per-CPU Memory Views (SDD spec, not yet built)
APs run `CLONE_VM` threads only; isolated processes never leave the
BSP. Lifting that needs no new IPI and no CR3/TLB machinery
(`switch_to` already swaps CR3/FPU/FSBASE, and `mov %cr3` flushes
non-global TLB entries, so a freed window can never haunt the CPU
that frees it: only zombies are freed and zombies never run). The
blocker is the memory-management VIEW, which is global today:
`g_brk`/`g_brk_limit`/`user_mmap_cur` plus `vma_live_root`/
`vma_free_root` (112 use sites across `sched.c`, `syscalls.c`,
`loader.c`, `spawn.c`, `shell.c` and the headers, `vma.c` host-tested
against the globals). Two CPUs running two isolated procs would
clobber each other's view on every preempt. Token/gang workarounds
were considered and rejected: a single shared view serializes all
non-VM execution through one owner, which is uniprocessor
throughput with migration overhead. The build is per-CPU views
(`cpu_view[cpu]` carrying brk/brk-limit/mmap-cur plus live/free
roots, bound at the existing save/load sites, `vma.c` host suite
re-homed first), then AP claim/preempt with `vm_only=0` plus the
`smp_ap_nonvm` counter. Proof is `progs/src/burn.c`: brk+mmap+CPU
with checksum `417386880`, already in-tree and BDD-pinned under
`-smp 2` beside `smp`/`kstack` (today it pins coexistence while APs
take threads only; post-views the same scenario with an
`ap_nonvm=[1-9]` expect proves APs ran isolated procs). Mutants:
`smp-ap-vm-only` (APs refuse non-VM, counter stays 0) and
`smp-ap-no-view` (AP skips the brk restore, burn checksum breaks).
`munmap` needs no shootdown (it only edits the VMA tree, never
clears a PTE), and CoW needs none either once the upgrade path is
idempotent (an RW PTE means another CPU already upgraded: flush
local and resume instead of killing). Until views land, treat
overlapping heavyweight ring-3 processes as the known-red
configuration (characterized under Shell, same section).

### SMP Scaling: Per-CPU Runqueues, Futexes, Batch, RCU-Lite

Four additive contracts that remove SMP contention and trap overhead
without changing the scheduling model (1:1 CLONE_VM threads, shared
address space, non-preemptible kernel outside explicit points). All four
are host-tested (`make test-futex test-percpu-rq test-batch test-rcu`),
mutation-covered in `mutate.sh`, and wired into the ABI as version 2
(`MINIOS_ABI_VERSION`, checksum extended with the new numbers). Each
contract lives in exactly one kernel file plus a minimal header carrying
its config; cross-file layout constants stay in `progs/minios_abi.h`.

- **Futexes (`futex.h`, `kernel/futex.c`, syscalls 226/227).** A 32-bit
  user word is the key: `FUTEX_WAIT` sleeps while `*addr == val`,
  `FUTEX_WAKE` wakes up to `n` sleepers on that address. Waiters chain
  intrusively through `proc_t.wq_next` on one of `FUTEX_BUCKETS` hash
  buckets; each sleeper records its address in a pid-indexed table so
  colliding buckets wake by address only. The value check and the enqueue
  share the bucket lock, which makes lost wakeups impossible; the lock is
  released before `schedule()`. The syscall layer rejects kernel
  addresses with `-EFAULT` before entry. Userland (`progs/src/mthreads.h`)
  runs a 0/1/2-state mutex on top: uncontended acquire/release never
  trap, contention sleeps in the kernel, and an `-ENOSYS` reply degrades
  to the old spin+yield loop so old kernels keep working. BDD proof is
  the existing `thdemo` scenario, which now runs 10 threads over futex
  mutexes (`produced=1000 consumed=1000`).
- **Per-CPU runqueues + work stealing (`percpu_rq.h`,
  `kernel/percpu_rq.c`).** Every CPU owns a ring of `RQ_DEPTH` pid hints.
  `do_thread_spawn`/`do_clone(CLONE_VM)` record the child on the
  spawner's ring; the AP idle path pops local hints, attempts one
  non-blocking steal per remote ring (`spin_trylock`, never waited on),
  and only then takes `sched_lock` to validate a hint
  (`procs[pid].state == PROC_READY`, VM-only) or to run the legacy
  global scan. Hints are advisory: full rings drop (counted), stale hints
  are discarded, and an idle CPU that finds nothing skips `sched_lock`
  entirely until every `RQ_RESCAN_PERIOD` polls, which bounds staleness
  and keeps a hintless READY thread dispatchable. The BSP keeps the
  global scan (it owns non-VM processes, which are never hinted and never
  stolen). The `smp` builtin reports `rq_hits`/`rq_steals`/`rq_drops` per
  CPU; the BDD suite asserts they appear and that the AP steals during
  `thdemo`.
- **Batched submission (`batch.h`, `kernel/batch.c`, syscall 235).**
  `SYS_SUBMIT_BATCH(ops, results, count)` runs up to `BATCH_MAX_OPS`
  descriptors in one trap, in order, stopping at the first error with
  `completed` reporting the successes. Only side-effect-light,
  non-blocking, pointer-free opcodes are batchable (`NOP`, `YIELD`,
  `TIME`, `GETPID`); anything else is `BATCH_ERR_OPCODE` and stops the
  batch. The syscall wrapper validates both arrays against the user
  window, copies the descriptors into kernel memory (no TOCTOU through
  user-mutable opcodes), and copies results out. Number 235 was chosen
  because 228 is `clock_gettime` in the Linux switch.
- **RCU-lite (`rcu.h`, `kernel/rcu.c`).** Epoch grace periods over the
  existing 100 Hz ticks: readers bracket with `rcu_read_lock/unlock`
  (nesting, tracked depth per CPU) and never lock; writers publish with
  `rcu_publish` and retire with `rcu_call`; `rcu_note_tick`/`rcu_note_idle`
  feed quiescent states from the timer ISR and `rcu_poll` closes the grace
  and runs due callbacks in tick context. The callback queue is bounded
  (`RCU_CB_MAX`, full refuses with ownership kept) and `rcu_synchronize`
  is spin-bounded (`RCU_SYNC_SPINS`, expiry is `RCU_ERR_TIMEOUT`, never a
  hang). The timer ISR feeds ticks on both BSP and AP paths and polls on
  the BSP. Deliberately out of scope, as documented in the improvement
  plan: lock-free everything, kernel preemption, M:N threading and
  per-CPU allocators.

### ISR-driven desktop event loop (`sched.c` + `vga_fb.c`)

The desktop event loop (`vga_fb_mouse_tick`) must run continuously regardless
of whether the shell or a user program owns the CPU.  Historically it ran
only inside `raw_blocking_getc` (the shell's idle poll), so the desktop froze
whenever `k_exec_user` entered ring 3 for a child process.  The mouse cursor,
taskbar clock, window drag and scrollbar all stopped responding.

The fix is a timer-ISR-driven tick: the 100 Hz PIT handler (`isr_dispatch`,
vector 32) runs the registered desktop listeners through the tick bus
(`tick.h` + `kernel/tick.c`, predicate `tick_desktop_due`) at a configurable
interval (`DESKTOP_TICK_INTERVAL`, default 4 = 25 Hz) whenever
`user_program_active` is set.  The flag is set in `k_exec_user` before the `iretq` into ring 3 and
cleared after `klongjmp` returns, so the desktop ticks for the entire
 duration of any user program.  When no user program is active the flag is
 clear and the ISR skips the tick; the shell drives the desktop from its own
 idle loop as before. The tick stands apart from the preemption branch in
 the ISR: chained as an else-if it never ran while threads existed
 (`proc_count > 1` always took the preempt arm), freezing the cursor for
 whole threaded workloads, so it is an independent `if` behind the same
 predicate and flag.

The PS/2 mouse is no longer disabled around `k_exec_user`.  Disabling the
mouse stopped IRQ12 delivery and froze `mouse_state` for the whole child
execution, which defeated the ISR tick.  With the mouse always enabled the
IRQ12 handler updates `mouse_state` continuously, and the ISR tick or the
shell idle loop consumes it.  There is no reentrancy hazard: the timer ISR
preempts ring-3 code and the IRQ12 handler runs at a lower priority; both
access the same `mouse_state` struct, but x86 field-width stores are atomic
and the consumer (tick or shell) is the sole reader.

The iretq frame now uses `RFLAGS=0x202` (IF=1) instead of the original
`0x002` (IF=0).  With IF=0 the CPU ignores all maskable hardware interrupts
while a ring-3 user program runs, so neither the timer ISR nor the PS/2
mouse IRQ fires and the desktop is completely frozen.  With IF=1 the timer
fires at 100 Hz from ring 3, driving the desktop tick, and IRQ12 delivers
mouse packets continuously.  The kernel's IDT (installed by `sched_init`
before any user program runs) handles all interrupts from ring 3; the user
program does not need its own IDT.

Configuration constants:
- `DESKTOP_TICK_INTERVAL` (`sched.h`): ISR ticks between desktop updates
  when a user program is active.  4 = 25 Hz at 100 Hz PIT.  Lower values
  produce smoother cursor tracking at the cost of ISR overhead; higher
  values reduce overhead at the cost of visible cursor lag.

The `user_program_active` flag is `volatile int` declared in `sched.h` and
defined in `sched.c`.  It is set only in `k_exec_user` and read only in
`isr_dispatch`, both in ring 0, so no memory barrier is needed beyond the
`volatile` qualifier.

### Tick listener bus (`tick.h` + `kernel/tick.c`)

The ISR no longer calls periodic effects directly. `sched_init` registers
two adapters, `sched_tick_audio` (forwards to `sb16_poll`) and
`sched_tick_desktop` (forwards to `vga_fb_mouse_tick`), and `isr_dispatch`
(vector 32) runs `tick_run_audio()` unconditionally on the BSP and
`tick_run_desktop()` when `tick_desktop_due(sys_ticks,
DESKTOP_TICK_INTERVAL)` and `user_program_active` hold. Call order,
gating and branch structure are unchanged; only the call path moved, so a
new periodic effect registers without editing the ISR. The bus is two
fixed tables (`TICK_MAX_AUDIO_LISTENERS` / `TICK_MAX_DESKTOP_LISTENERS`,
no heap, no locks): registration is boot-time only before `sti`,
dispatch only reads, a null or full registration returns -1 and changes
nothing, and `tick_reset` empties both lists. Host-tested (`make
test-tick`, mutation-covered); the live-boot proof is the existing SMP
(`SMP: Brought up 2 CPUs`) and sb16 scenarios, which exercise both
dispatch paths.

### Port I/O HAL (`arch/x86/hal_io.h`)

Header-only, single-file contract centralizing every port number,
controller command and device address the kernel touches
(`HAL_PIC1_CMD`, `HAL_PIC1_DATA`, `HAL_PIC2_CMD`, `HAL_PIC2_DATA`,
`HAL_PIC_EOI`, `HAL_PIT_CMD`, `HAL_PIT_CH0`, `HAL_PS2_STATUS`,
`HAL_PS2_DATA`, `HAL_PS2_MOUSE_OBF`, `HAL_PS2_IBF_EMPTY`,
`HAL_PS2_OBF_FULL`, the `HAL_PS2_CMD_*` controller commands, the
`HAL_MOUSE_CMD_*` device commands, the Intellimouse knock rates and id,
`HAL_MOUSE_HW_TIMEOUT`, `HAL_MOUSE_SYNC_BIT`,
`HAL_MOUSE_BUTTON_MASK`, `HAL_MOUSE_SCALE`, `HAL_MOUSE_PACKET_LEN`,
`HAL_LAPIC_EOI_ADDR`). The `hal_outb`/`hal_inb`/`hal_outw`/`hal_inw`
accessors emit the same instructions as the open-coded sites they
replaced; `hal_pic_eoi`/`hal_lapic_eoi` own the EOI sequences. No bare
port literal or raw port-asm site remains on the scheduler, keyboard or
syscall paths (serial/SB16/IDE drivers keep the legacy `kernel.h`
accessors until their own HAL slices land). Under `HAL_IO_HOST_TEST` the
accessors log to stub counters, which makes the mapping host-testable
(`make test-hal`).

### Userspace desktop architecture (design spec, future implementation)

The long-term goal is to move the desktop compositor to a ring-3 userspace
process, achieving proper separation of concerns: the kernel owns scheduling
and hardware access, the desktop process owns rendering and input routing,
and user programs run concurrently under preemptive scheduling.

**Desktop process:** a static ELF binary compiled on the host, shipped on
MiniFS as `bin/desktop`.  It runs at ring 3 through `k_exec_user` and
renders the desktop background, taskbar, terminal window, and composites
DOOM/Nuklear back-buffers.  The framebuffer is already mapped user-accessible
at `FB_ADDR` (0x0B200000), so the desktop process writes pixels directly
without kernel mediation.

**Input routing:** the desktop process reads mouse events via `SYS_MOUSE`
(219) and keyboard events via `SYS_KBD` (205).  Keyboard events that belong
to the shell (typing) are forwarded through a shared ring buffer at a fixed
address in the user window (`DESKTOP_KBD_BUF`, size `DESKTOP_KBD_BUF_SZ`).
The shell reads from this buffer instead of polling the PS/2 keyboard
directly.  The desktop process owns the keyboard and decides what reaches
the shell.

**Shell output routing:** the shell writes text output to a shared terminal
ring buffer at `DESKTOP_TERM_BUF` (size `DESKTOP_TERM_BUF_SZ`).  The
desktop process reads from this buffer and renders it in the terminal window.
This replaces the current path where `vga_putc` writes directly to the
framebuffer.  The kernel's `vga_fb_putc_term` writes to the ring buffer
instead; the desktop process handles line wrapping, scrollback, and
rendering.

**Window compositing:** DOOM and Nuklear already render to kernel-heap
back-buffers and call `SYS_DOOM_FRAME`/`SYS_NK_FRAME` to composite.  In the
userspace model, the desktop process reads these back-buffers (mapped
read-only in the user window) and composites them itself, removing the
kernel-side compositing code.

**Preemptive scheduling:** the timer ISR preempts the desktop process,
giving CPU time to DOOM, Nuklear, or other user programs.  The desktop
process yields explicitly via `SYS_SCHED_YIELD` (24) when idle.  The
scheduler's round-robin policy ensures all processes get fair CPU time.

**Security model:** the desktop process runs at ring 3 with user page
protections.  It cannot access kernel memory, page tables, or hardware
ports directly.  All hardware access goes through syscalls with validated
user pointers.  The shared ring buffers live in the user window, so a
compromised desktop process cannot corrupt kernel state.  The kernel
validates all buffer addresses against `USER_LOAD_BASE..USER_LOAD_END`.

**Phased implementation:**
1. Phase 1 (done): ISR-driven desktop tick keeps the desktop responsive
   during user program execution.
2. Phase 2: add `SYS_DESKTOP_KBD_READ` and `SYS_DESKTOP_TERM_READ` syscalls
   that expose the shared ring buffers.
3. Phase 3: create the desktop binary, route shell I/O through ring buffers.
4. Phase 4: remove kernel-side compositing, let the desktop process own it.
5. Phase 5: enable preemptive scheduling for all user processes.

**Preemption blocker (lifted, revision 1):** the single-address-space limit
that deferred Phase 5 is gone for the `mrun` path. `pt_clone_user_empty`
builds a fresh user window per process (heap-owned data pages, graphics
slots re-shared), `load_exec_elf_into` loads segments into that window
without touching the live one, and `proc_spawn_elf` starts the result as a
non-`CLONE_VM` process through `user_trampoline` + `iretq`. The existing
machinery already did the rest: `switch_to` swaps CR3, the BSP timer
preempt swaps the per-process brk/mmap view, and `do_waitpid` reaps through
the extended `pt_free_user` (heap pages freed, identity pages and shared
graphics slots untouched). `mrun a.elf b.elf ...` runs isolated ELFs
concurrently; the BDD suite pins `mrun: pid 1 exit code: 55` beside `Hello`.
The legacy `run`/`k_exec_user` path is byte-for-byte unchanged.

### Preemptive multitasking + job control (OSDev model)
MiniOS follows the OSDev recommended model — kernel stack per task (the
16 KB `kstack_pool` slot per proc, TCB in `procs[]`, CR3 in `ctx`) with
preemptive multitasking: involuntary switches from the 100 Hz timer ISR
plus voluntary `yield()`s in every wait loop, so most switches stay
cooperative and preemption is the backstop, not the norm.

- **Background jobs:** `run p.elf &` / `mrun a b &` spawn isolated
  processes and return the prompt at once; the shell stays usable while
  jobs run (proven: `echo` answers mid-`thdemo` with its 10 futex
  threads, DOOM boots its WAD while the prompt serves). `jobs` lists
  them, `wait [pid]` reaps (blocking), `kill <pid>` terminates a real
  target (the old `do_kill` exited the caller; now the victim goes
  ZOMBIE for its parent, abandoned by the BSP/AP preempt paths so no
  corpse keeps running). Unreaped exits surface as `job done: pid N
  code: C` before the next prompt, so pid slots never leak. `wait4`
  honors `WNOHANG` with a `WAITPID_NONE` sentinel (a killed job's -1
  still reaps distinctly).
- **Per-process VMA (`vma.h`/`vma.c` + `sched.c`):** every non-`CLONE_VM`
  process owns a heap-backed `vma_ctx_t` (private 4096-node pool); the
  globals are a view rebound on each brk/mmap switch, and `brk`/`mmap`
  materialize pages via `mm_user_ensure_page` (no-op on the shared
  window). This fixed the DOOM-in-isolation #GP (fresh window over a
  stale shared tree with `VMA_NIL == NULL`). Threads share the pointer.
- **Signals, minimal and honest:** Ctrl+C kills the foreground set
  (prompt bell when there is none; `^C` + exit 130 path), Ctrl+D is EOF
  (empty line submits, non-empty bells). Semantics are SIGKILL-like:
  `rt_sigaction` stays a stub, no guest handler ever runs. Legacy
  blocking `run` never polls the console, so it ignores Ctrl+C.
- **Build discipline:** the Makefile carries explicit per-object header
  dependencies (see the `shell.o:`/`syscalls.o:` rules), so touching a
  listed `.h` rebuilds its dependents. When a change adds a new `#include`,
  update that object's rule in the same edit; when in doubt run `rm
  *.o && make` — a stale `kernel.o` keeps the old `PROC_T_SIZE` in the
  syscall-entry trampoline while `sched.o` moves on, and every spawned
  child hangs in its first syscall with no diagnostic.
- **Construction race closed:** a newborn slot stays `PROC_SWITCHING`
  (never claimable) until fully built; publishing `READY` early let a
  tick claim a half-built context (the 192 KB pool alloc widened that
  window to a whole tick, hanging the machine with no output).
- Honest limits remaining: one shared fd table (no CLOEXEC in v1, so
  `execve` keeps descriptors like `fork`), no `vfork`
  (`sys_linux_vfork` answers `-ENOSYS`, never success: a stub
  that returned 0 let userland believe a child existed when none did;
  `tools/check_fork_stubs.py` gates this; `mm_copy_user_page`
  waits for it), APs claim `CLONE_VM` threads only, no Alt-Tab
  mid-`edit`, serial sees one interleaved console (use `wm list`).
- **Known race, root-caused 2026-09-25 (not a regression): `run thdemo`
  faults deterministically in this environment (`EXCEPTION 0e`,
  user read of `0x10` in `_IO_puts`, i.e. `%fs:0x10` with FSBASE 0)
  and fails byte-identically on a clean-HEAD baseline image, so no
  session change is implicated (verified by stashing the whole tree,
  rebuilding and rerunning). Mechanism: the main thread's first
  `printf` runs single-threaded (no FS read); once producers spawn,
  any tick that runs a thread (whose PCB `fsbase` is 0, never set)
  `wrmsr`s 0, and the resume onto pid 0 skips the FSBASE restore
  (`ctx_sw.S` restores it for every pid except 0), so the next
  `printf` reads TLS through base 0. Whether the tick lands inside
  the spawn loop is boot-timing dependent, which is why the suite
  historically flakes here instead of failing always. The honest fix
  (save FSBASE on every park including `switch_save_only`, restore
  for pid 0 too) touches every context switch and waits for its own
  SDD cycle with fptest/thdemo validation, so it is scoped as
  follow-up work, never a drive-by.
- **`execve(59)` replaces the caller's image in place** (`do_execve` in
  `kernel/sched.c`, entered through `arch/x86/ctx_sw.S` `exec_enter`):
  the caller keeps pid/parent/children/fds/limits while window, VMA,
  brk view, stack, FPU, FSBASE and name rebuild around the new
  ET_EXEC/ET_DYN program, entered directly through `user_trampoline`
  (never returns on success). ET_REL refuses `-ENOEXEC` (ring-0 trust
  gate stays SPAWN-only), a thread calling `execve` refuses `-ENOSYS`
  (it would keep `CLONE_VM` on a private window) while sibling
  threads die with the old image like Linux (zombied at adopt for
  their parent, so a spawn racing the adopt lock either dies first
  or shares the new window), argv is
  bounded (32 x 255, `-E2BIG` past) and copied per-byte so a racing
  sibling can only change content, never overflow. Mechanism lessons
  from proving it: a C inline asm cannot zero GPRs around an
  address operand (GCC may allocate it into a zeroed register and land
  rsp at 0, iretq'ing out of the IVT alive and silent), hence the
  dedicated `exec_enter`; and debug scaffolding that returns past the
  adopt point leaves the caller on a freed window, so every breadcrumb
  dies before the merge. Proven by `progs/src/execho.c`
  (`mrun bin/execho.elf`: fork, exec lxhello with argc=2, reap 2 then
  a ghost-exec 42, `execho: ok` exit 0).

### Linux process, thread and descriptor ABI (FreeDom readiness, step 4)
The full FreeDom GUI (`freedom-gui`, docs/spec/network.md) is a static
glibc program that forks a re-exec'd tab worker over two pipes, runs fetch
and prefetch work on NPTL threads and waits on condition variables. glibc
reaches the kernel through numbers MiniOS did not answer (`pipe()` is
`pipe2`, `fork()` is `clone`, `pthread_create` is `clone3` then `clone`,
condition variables are `FUTEX_WAIT_BITSET`) and relies on Linux pipe
semantics. Each point below is pinned by `progs/src/lxabi.c` (`run
bin/lxabi`, one `lxabi: <check> ok` line per point, `lxabi: all ok`, exit 0)
and its BDD scenario.

- **Full user register state at syscall entry.** `syscall_entry.S` pushes
  the callee-saved user registers (`rbx`, `rbp`, `r12`-`r15`) at the top of
  the per-proc kernel stack before the existing frame, so every frame offset
  is unchanged and the exit (which restores the top from `sc_top_save`)
  needs no pops. A fork or clone child copies them, plus the argument
  registers already in the frame (`rdi`, `rsi`, `rdx`, `r10`, `r8`, `r9`),
  into its PCB, so it resumes after the `syscall` instruction with every
  register Linux preserves (only `rax` = 0, `rcx` and `r11` differ).
- **`clone` (56).** Two shapes, decided by `CLONE_VM`:
  - Without it (glibc `fork`): `do_fork` copy-on-write, `SIGCHLD` accepted
    as the exit signal, `CLONE_CHILD_SETTID` / `CLONE_CHILD_CLEARTID`
    recorded for the child. `CLONE_CHILD_SETTID` is written by the child
    itself on its first return to user mode (its own window, never the
    parent's COW page).
  - With it (NPTL threads, `CLONE_VM|CLONE_FS|CLONE_FILES|CLONE_SIGHAND|
    CLONE_THREAD|CLONE_SYSVSEM|CLONE_SETTLS|CLONE_PARENT_SETTID|
    CLONE_CHILD_CLEARTID`): same window, shared fd view, `rsp` = the new
    stack, FSBASE = `tls`, `*parent_tid` = child tid before the parent
    returns. A `CLONE_THREAD` child carries the leader's `tgid` (`getpid`
    answers it, `gettid` answers the thread's own pid), exits alone on
    `exit` (60), writes 0 to `clear_child_tid` and wakes one futex waiter
    there (what `pthread_join` sleeps on), and is reaped automatically: its
    slot is freed by the next clone that needs one and when its group leader
    is reaped, never left for a `waitpid` nobody issues. `exit_group` (231)
    zombifies every thread of the group before the caller exits.
  - Unsupported flag combinations (`CLONE_VFORK`, namespaces, `CLONE_PIDFD`,
    `CLONE_THREAD` without `CLONE_VM|CLONE_SIGHAND`) fail `-EINVAL`, never a
    half-built child. `clone3` (435) answers `-ENOSYS`, which glibc treats as
    "use clone".
- **Futex.** `FUTEX_WAIT_BITSET` (9) and `FUTEX_WAKE_BITSET` (10) with
  `FUTEX_BITSET_MATCH_ANY` map to WAIT/WAKE; any other bitset is `-EINVAL`.
  `FUTEX_CLOCK_REALTIME` is accepted. A WAIT with a timeout (relative for
  op 0, absolute on the requested clock for op 9) that passes its deadline
  returns `-ETIMEDOUT`; before the deadline it yields and returns 0, which
  futex callers already treat as a spurious wakeup to recheck.
- **Pipes.** A user `read` on an empty pipe whose writer is open blocks
  (yielding) unless the description is `O_NONBLOCK`, which answers
  `-EAGAIN`; empty with the writer closed is 0 (EOF). A user `write` to a
  full pipe blocks until space or until the reader closes; a pipe whose
  read end is closed answers `-EPIPE`. The kernel `kfread`/`kfwrite`
  contract (never blocks, used by the shell pipeline runner) is unchanged:
  the blocking lives in the syscall layer. `pipe2` (293) honours
  `O_CLOEXEC` and `O_NONBLOCK`; `pipe` (22) is `pipe2` with no flags.
  `O_NONBLOCK` belongs to the open file description (`KFILE`), so `dup`
  copies share it, like Linux.
- **`fcntl` (72).** `F_DUPFD`, `F_DUPFD_CLOEXEC`, `F_GETFD`, `F_SETFD`
  (`FD_CLOEXEC`), `F_GETFL` (access mode plus `O_NONBLOCK`), `F_SETFL`
  (`O_NONBLOCK` only; other bits ignored like Linux). Anything else
  `-EINVAL`; a bad fd `-EBADF`. `dup3` (292) and `close_range` (436, with
  `CLOSE_RANGE_CLOEXEC` or plain close) complete the set.
- **`eventfd2` (290) / `eventfd` (284).** A 64-bit counter description:
  `write` adds (overflow past `2^64-2` blocks or `-EAGAIN`), `read` of 8
  bytes returns and clears it (`EFD_SEMAPHORE` returns 1 and decrements),
  empty blocks or `-EAGAIN` with `EFD_NONBLOCK`; `EFD_CLOEXEC` arms the
  close-on-exec bit. Reads or writes shorter than 8 bytes are `-EINVAL`.
- **`poll` (7).** Pipes and eventfds report readiness beside sockets:
  `POLLIN` when bytes (or a nonzero counter) wait, `POLLOUT` when space,
  `POLLHUP` on a pipe whose writer closed, `POLLERR` on a write end whose
  reader closed. A negative fd is skipped and every other entry's
  `revents` is written (zero when not ready), as Linux does.
- **`writev` (20)** writes every iovec to the descriptor (pipes and files,
  not just the console), stopping at the first short write.
- **`time` (201).** Retired kernel-TLS number reclaimed for Linux `time(2)`,
  exactly as 202 was for `futex`: it answers the RTC-anchored wall clock in
  seconds (what static glibc calls when there is no vDSO), so OpenSSL and
  libcurl validate certificate lifetimes against a real date. 203 stays
  retired.
- **`mkdir` (83)** creates a MiniFS directory (parent must exist, `-EEXIST`
  when present); `mode` is accepted and ignored (MiniFS has no permission
  bits).
- **Cheap answers.** `madvise` (28) answers 0 (advice only); `statfs` (137)
  / `fstatfs` (138) answer `-ENOSYS` (callers fall back); `prlimit64` keeps
  `-ENOSYS`. Linux numbers inside the MiniOS 200-block stay shadowed per
  ADR-0014 and are not reclaimed here: `sched_getaffinity` (204, SYS_TIME),
  `fadvise64` (221, SB16 open) and `getdents64` (217, LZ4) keep their
  documented deviations until the block moves.
