# MiniOS Unified Architectural Improvement Plan

> Source-of-truth note: completed decisions live in `docs/adr/` as
> Architectural Decision Records (ADR-0001..0013) with the formal VMA
> analysis in `docs/vma-complexity.md`. This document tracks future work
> only; its "Completed Work" section below is retained as history and
> must not grow. New decisions add an ADR, never a retrospective here.
> ADR index: Phase 0.1 spinlocks (code comment, no ADR) · 0.2 CI
> governance (workflows, no ADR) · 0.3 VFS invariants (kernel.h, no ADR)
> · 0.4 SMP → ADR-0003 · 1.4 extraction/dirs → ADR-0011 · 1.1 ABI →
> code (`minios_abi.h`) · 3.1 syscall table → code · 3.2 CVM hardening
> → code · 4.x testing → workflows/tests · 5.x resiliency → BDD/mutants
> · 6.x god-object → ADR-0011 · Strategy/Facade → ADR-0012 · priority
> inheritance → ADR-0013 · VMA → ADR-0005 + proof.

## Methodology

Every task follows SDD + TDD + BDD:
- SDD: spec written before code
- TDD: failing test written first, then implementation
- BDD: test_bdd.sh scenario proves observable behaviour
- Mutation testing: every change validated with mutate.sh

Boy Scout Rule: tech debt and security defects found during any phase are fixed
immediately, never deferred. Documentation (README.md, CLAUDE.md) updated after
each completed phase.

## Definition of Done (per task)

1. English only, no emojis, no inline comments, docstrings above code
2. DRY, SOLID principles, single file per contract
3. Self-contained, production-ready, secure
4. No hardcoding, no magic numbers, everything in config constants
5. SDD spec + TDD failing test + BDD scenario
6. Mutation test validates the change kills at least one mutant
7. Documentation updated

---

## Completed Work

### Phase 0.1: Spinlock IRQ Safety (DONE)

**What changed:** `spinlock.h` now provides two acquisition modes:
- `spin_lock` / `spin_unlock`: for ISR context (interrupts already off)
- `spin_lock_irqsave` / `spin_unlock_irqrestore`: saves RFLAGS.IF before
  disabling, restores on release. Safe for nested critical sections.

**Why it matters:** The old `spin_lock`/`spin_unlock` pair did unconditional
`cli`/`sti`, which deadlocks when a spinlock is taken inside another critical
section that already has IF=0. The irqsave variant preserves the outer
interrupt state, so the inner restore keeps IF disabled until the outer
spin_unlock re-enables it exactly once.

**Files:** `spinlock.h`

### Phase 0.2: CI Governance Consolidation (DONE)

**What changed:** Merged `governance.yml` and `test.yml` into three workflows:
- `ci.yml`: build, BDD, codecs, TLS, MCP, SMP matrix, runtime integration
- `architecture.yml`: KB sync, cohesion gate, complexity gate, surprising connections
- `nightly.yml`: mutation tests, MCP mutation, stress tests (8 cores)

Removed `|| true` from cohesion and surprising connections jobs so they
actually gate merges. Mutation tests moved to nightly (they take 60+ min).

**Files:** `.github/workflows/ci.yml`, `.github/workflows/architecture.yml`,
`.github/workflows/nightly.yml` (new); `governance.yml`, `test.yml` (deleted)

### Phase 0.3: VFS Invariant Documentation (DONE)

**What changed:** `kernel.h` already contains comprehensive docstrings for
`vfs_ops_t`, `vfs_file_t`, and `KFILE` (lines 178-283). Every field has a
semantic contract, invariants are stated, and failure modes are documented.

**Files:** `kernel.h` (no changes needed, already complete)

### Phase 0.4: SMP Foundation (DONE)

**What changed:** Per-CPU data structures, SMP-aware ISR, AP bring-up,
syscall table refactoring, and per-CPU allocator API.

1. **Per-CPU data (`sched.h` + `sched.c`):** `cpu_t` struct with LAPIC ID,
   `cur_pid`, `syscall_kstack`, idle/BSP flags.  `cpus[MAX_CPUS]` array,
   `current_pid` macro routes through `this_cpu()->cur_pid`.

2. **GS base isolation (`kernel.c`):** `swapgs` at syscall entry/exit.
   BSP sets `MSR_GSBASE` to `&cpus[0]` in `sched_init()`.  APs set their
   own GS base in `smp_ap_entry()`.

3. **Context switch (`ctx_sw.S`):** removed global `switch_to_next` variable;
   register-only rdi/rsi restore using `xchgq`.

4. **AP bring-up (`smp.c` + `ap_entry.S`):** flat binary stub at 0x6000
   (SIPI vector 6), INIT-edge/SIPI/SIPI through xAPIC ICR, per-CPU init
   in `smp_ap_entry()` (cpu_t, GS base, IDTR, LAPIC timer at 100 Hz),
   identity-mapped stub stack at 0x78000.

5. **ISR AP-awareness (`sched.c`):** vector-32 handler checks `is_bsp` to
   choose PIC EOI + sb16_poll (BSP) or LAPIC EOI (AP).  Context-switch
   path guarded by `is_bsp` so APs never corrupt `procs[]`.

6. **Syscall table (`syscalls.c`):** extracted MiniOS custom syscalls
   (200+) into `minios_syscall_table[]` with `sys_minios_*` handlers.
   Table dispatch before the switch; Linux ABI (0-199) stays in switch.

7. **Per-CPU allocator (`kernel/mm.c`):** `kmalloc_percpu(size, align)`
   allocates `cpu_count * size` aligned, zeroed; returns NULL on failure.

**LAPIC ICR fix:** destination shorthand "all excluding self" is bits
19:18 (`0xC0000`), not bits 17:16 (`0x30000`, reserved).  The old value
caused SIPI ICR writes to be accepted (readback matched) but never
delivered to the APs.  Level-triggered INIT hangs QEMU 11 (delivery
status never clears), so edge-triggered INIT is used.

**BDD:** `scenario_smp` boots with `-smp 2` and asserts
"SMP: Brought up 2 CPUs"; single-CPU scenario asserts "SMP: 1 CPU".

**Mutations:** `smp-icr-shorthand-broken`, `smp-init-missing`,
`smp-sipi-vector-zero`, `smp-ap-no-lapic-eoi`,
`smp-bsp-ctx-switch-not-guarded`, `smp-gs-base-not-set`.

**Files:** `sched.h`, `kernel/sched.c`, `kernel.c`, `arch/x86/ctx_sw.S`,
`smp.c`, `smp.h`, `arch/x86/ap_entry.S`, `kernel/syscalls.c`,
`kernel/mm.c`, `kernel.h`, `test_bdd.sh`, `mutate.sh`

### Phase 1.4: Serial + String Extraction (DONE)

**What changed:** Extracted from `kernel.c` into standalone compilation units:
- `serial.c`: COM1 16550 UART driver (init, putc, getc, available, puts)
- `string.c`: kernel string/memory functions (kstrlen, kstrcpy, kmemcpy, etc.)
  plus `katol` (now non-static, declared in kernel.h)

**Why it matters:** These are the cleanest extractions -- pure functions with
zero dependencies on kernel internals. They prove the extraction pattern works
before tackling more coupled code. `kernel.c` loses ~90 lines.

**Files:** `serial.c`, `string.c` (new); `kernel.c` (functions removed);
`kernel.h` (`katol` declaration added); `Makefile` (compilation + link rules)

### Phase 1.5: Syscall Trampoline Hardening + Proc-Leaf Split (DONE)

**What changed:**
- `syscall_entry` return discriminates on caller RIP, never RSP
  (`8(%rsp)` frame slot at exit, `%rcx` at the `21f` tail). RSP is
  attacker-settable without faulting; RIP is constrained to executable
  mappings, so an `RSP=0` spoof now takes the `sysretq` path and can no
  longer retain CPL0 via `jmp *%rcx`.
- Entry pid gate (`13f`: `cmpl $MAX_PROCS`, `jae 98f`): fail closed with
  `-EFAULT` touching no memory, so a corrupt `cur_pid` can neither index
  `sc_top_save` OOB nor `xchg` onto a wild kstack.
- First `syscalls.c` split increment: proc-leaf handlers (clone,
  thread_spawn, seccomp, nice, yield, getpid/gettid, fork/vfork/execve
  stubs, exit/`do_proc_exit`, wait4, kill) move verbatim to
  `kernel/syscalls_proc.c` with boundary header `syscalls_proc.h`;
  dispatch tables reference the original names, no behaviour change
  (`syscalls.c` 1568 -> 1444 lines).
- Boy scout: `NICE_MIN`/`NICE_MAX` named in `sched.h`,
  `ide_wait_drq` `s` -> `status`, rtl8139 byte/word port I/O unified onto
  `kernel.h` (dword pair stays local: no shared `outl`/`inl`).
- vedit scanner DRY: shared `vedit_parse_string`/`vedit_parse_number`
  (C-only `allow_quote`)/`vedit_parse_keyword` helpers; per-language
  quirks (C `#`/`/* */`, Python triple-quote, Lua long brackets) stay in
  the caller. Host/guest build-contract mirror documented with a
  `t_lang_of` pin in `tests/test_vedit_build.c`.

**Why it matters:** the RSP-spoof escalation is closed with a minimal
asm diff (no `proc_t` growth: pid 0 is shared by `k_exec_user` and
`k_run_rel`, so per-pid mode cannot discriminate the legacy paths); the
proc split proves the syscalls.c decomposition pattern before riskier
increments (fd table, spawn, mm, net, gfx).

**Files:** `kernel.c` (trampoline), `kernel/syscalls_proc.c`,
`syscalls_proc.h` (new), `kernel/syscalls.c`, `sched.h`, `drivers/ide.c`,
`net/rtl8139.c`, `progs/vedit/vedit.c`, `tests/test_vedit_build.c`,
`Makefile` (rule + link + lint list)

**Validation:** `make` zero warnings, `kernel.elf` links, `make check-size`
ok, `make test-vedit` ok, vedit `--selftest-build` ok, `os.img` builds
with `saves/` preserved. BDD/QEMU stays in the maintainer gate.

### Directory Reorganization (DONE)

**What changed:** Restructured the project from a flat layout into a
Linux/BSD-style directory hierarchy. All headers remain in the project root
(accessed via `-I.`); source files live in subdirectories. The Makefile uses
`VPATH` so make finds sources in subdirs while `.o` files stay in root.

```
arch/x86/boot/    stage1.S, stage2.S, bootdefs.h, linker scripts
arch/x86/         isr_stubs.S, ctx_sw.S, ap_entry.S
kernel/            string.c, serial.c, sched.c, vga_fb.c, lz4_kernel.c, cvm_host.c
drivers/           ide.c, block.c, pcspk.c, sb16.c, rtc.c
fs/                minifs.c, zip.c
net/               net.c, tls.c, tls_crypto.c, tls_x509.c
third_party/       xxhash, stb, dlmalloc, miniz
```

Cross-boundary shell functions (`console_getc`, `redirect_*`,
`shell_run_any`, `shell_exec_builtin`, `shell_report`) made non-static
with declarations in `kernel.h`, ready for future extraction to `shell.c`.

**Why it matters:** The flat layout made it impossible to see subsystem
boundaries. The new layout follows kernel convention (arch/, drivers/,
fs/, net/) and makes the dependency graph visible at the directory level.

**Files:** All moved `.c`/`.S` files; `Makefile` (VPATH + updated rules);
`kernel.h` (new declarations); `kernel.c` (forward decls removed,
functions made non-static); `CLAUDE.md`, `ARCHITECTURE_PLAN.md` (updated)

### WM Header Contracts (DONE)

**What changed:** The window manager inside `kernel/vga_fb.c` was a God
Object: one 2900-line file owned terminal rendering, focus, drag, desktop
icons, taskbar, graphics compositing and cursor handling, with hit-testing
logic duplicated per window type and drag state hidden in function-static
variables that a focus change could never reset. Six header-only contracts
now own the pure logic, each in one file with a centralized config struct,
integer-only and kernel-dependency-free so they compile on the host:

```
wm_geom.h      rectangles: title, content, scrollbar, clamp
wm_events.h    click/release/scroll/move translation, stateless
wm_window.h    unified terminal/graphics model, hit-test, focus rotation, paint order
wm_render.h    back-to-front composition plan (graphics always last)
wm_tiling.h    terminal cell layout (split, stack beside graphics, fullscreen single)
wm_focus.h     validated focus transitions (invalid ids refused)
```

`kernel/vga_fb.c` consumes them (hit tests, edge detection, paint order,
tiling cells, focus selection) and keeps owning only the pixel work and the
kernel state. Drag grabs moved to file scope so `tw_select` resets them on
every focus change.

**Why it matters:** Title height, scrollbar edges and focus rotation each
had one definition instead of five copies; every rectangle and transition
is host-testable without booting QEMU.

**Files:** `wm_geom.h`, `wm_events.h`, `wm_window.h`, `wm_render.h`,
`wm_tiling.h`, `wm_focus.h`; `tests/test_wm.c` (`make test-wm`,
mutation-covered); `kernel/vga_fb.c`; `Makefile`; `docs/adr/0020-wm-contracts.md`;
`CLAUDE.md`, `README.md` (gates list `test-wm`)

---

## Phase 1: Stabilize Existing Abstractions (Weeks 1-3, CRITICAL)

### 1.1 ABI Versioning (PARTIAL: build-time gate done, load-time gate open)

**Spec:** Add `MINIOS_ABI_VERSION` (monotonic integer) and `MINIOS_ABIChecksum`
(computed from layout constants) to `minios_abi.h`. The ELF loader verifies
both before accepting a binary. Mismatch returns `-EABI_MISMATCH`.

**Status (audit 2026-09):** the version integer and the checksum exist and
the kernel side is pinned by `_Static_assert`s, but no loader code reads
them and `-EABI_MISMATCH` exists nowhere: the header comment promised a
load-time gate that was never built, so the comment was rewritten to state
the honest mechanism (build-time drift instrument, both sides rebuild from
the same header). A load-time gate cannot reuse this scheme directly:
Linux-ABI binaries carry no MiniOS version note, and rejecting them would
break Linux compatibility, which is a hard requirement. The remaining work
is a version note emitted by `ld` for MiniOS-toolchain binaries plus a
loader check scoped to those binaries only; Linux ELFs stay ungated.

**Files:** `progs/minios_abi.h`, `kernel.c` (ELF loader), `test_bdd.sh`

**TDD:** Write a BDD scenario that boots with current ABI, compiles a test
binary with the current ABI, runs it successfully. Then manually bump the
version and verify the loader rejects the old binary.

**DOD:**
- `MINIOS_ABI_VERSION` integer defined in `minios_abi.h`
- `MINIOS_ABI_CHECKSUM` computed from layout constants
- ELF loader checks version + checksum, rejects mismatch with diagnostic
- BDD scenario: `abi-version-mismatch` proves rejection
- Zero silent crashes from ABI drift

### 1.2 VFS Audit

**Spec:** Grep exhaustively for `outb`/`inb`/`outw`/`inw` calls outside the
HAL layer (kernel.c port I/O section, ide.c, sb16.c, pcspk.c, rtc.c).
Migrate orphaned direct hardware accesses to VFS ops or documented HAL
exceptions.

**Files:** all `.c` files, `kernel.h`

**TDD:** Document every direct port I/O call site with its justification.
Any call not in the HAL list is a test failure.

**DOD:**
- Audit report listing every `outb`/`inb` call site with file:line
- Each call classified: HAL-justified or needs migration
- Orphaned accesses migrated to vfs_ops or HAL
- 100% of I/O passes through registered paths or documented HAL

### 1.3 SMP Synchronization Review

**Spec:** Analyze `sched.c` and `smp.c` for data races. Add spinlock
primitives to shared structures (`proc_table`, `ready_queue`, scheduler
state). Document which structures are per-CPU vs shared.

**Files:** `sched.c`, `sched.h`, `smp.c`, `smp.h`

**TDD:** Stress test with 2+ cores in QEMU, verify no corruption of
`proc_table` or `ready_queue`.

**DOD:**
- Spinlock/mutex primitives defined in `sched.h`
- All shared scheduler structures protected
- Per-CPU vs shared documentation in headers
- SMP stress test passes without corruption

### 1.4 VFS Invariant Documentation

**Spec:** Document explicit contracts for `vfs_ops_t`, `vfs_file_t`, and
`KFILE` in their header definitions. Every field gets a semantic contract.

**Files:** `kernel.h`

**DOD:**
- Every field in `vfs_ops_t`, `vfs_file_t`, `KFILE` has a docstring
- Invariants documented: what must be true before/after each operation
- Contracts enforceable by assertion in debug builds

---

## Phase 2: Active Architectural Governance (Weeks 2-4, HIGH)

### 2.1 Knowledge Base CI Integration

**Spec:** Create `.github/workflows/kb.yml` that runs readmenator on every
push, regenerates `KNOWLEDGE_BASE.md`, and fails the build if the file
differs from what was committed.

**Files:** `.github/workflows/kb.yml`, `tools/check_kb_sync.py`

**DOD:**
- GitHub Actions workflow triggers on push
- readmenator runs and regenerates KB
- Build fails if KB is out of sync
- KB never drifts from code

### 2.2 Cohesion Gate

**Spec:** Create `tools/check_cohesion.py` that parses the CPG JSON-LD output
from readmenator. If any root community's cohesion drops below 0.25, CI fails.

**Files:** `tools/check_cohesion.py`, `.github/workflows/kb.yml`

**DOD:**
- Script parses JSON-LD, extracts community cohesion scores
- Threshold configurable in `ARCH_POLICY.yaml`
- CI fails on cohesion regression
- Architectural degradation detected before merge

### 2.3 Complexity Gate

**Spec:** Validate that `kernel.c` does not exceed 350 symbols without
explicit approval recorded in `ARCH_POLICY.yaml`.

**Files:** `tools/check_complexity.py`, `ARCH_POLICY.yaml`

**DOD:**
- Script counts symbols in kernel.c from JSON-LD
- Threshold enforced in CI
- Exception requires explicit YAML entry
- God object growth controlled

### 2.4 Surprising Connections Alert

**Spec:** Parse CPG JSON-LD for new connections of 5+ hops between distinct
communities. Create GitHub issues or CI warnings for each.

**Files:** `tools/check_surprising.py`

**DOD:**
- Script detects cross-community long-range connections
- New connections flagged as warnings or issues
- Coupling debt visible and priorizable

---

## Phase 3: Multi-Runtime Unification (Weeks 4-7, MEDIUM-HIGH)

### 3.1 Canonical Syscall Table

**Spec:** Define a single syscall table in `minios_abi.h` with stable
numbering. CVM, Lua (`minios.c`), and MicroPython (`minios_module.c`)
must use this table without duplicating bindings.

**Files:** `progs/minios_abi.h`, `cvm_host.c`, `progs/lua/minios.c`,
`progs/micropython/variants/minios/minios_module.c`

**DOD:**
- Single `MINIOS_SYS_*` table in `minios_abi.h` with all syscall numbers
- All runtime bindings reference the canonical table
- No duplicate syscall number definitions
- One source of truth for kernel calls

### 3.2 CVM Bytecode Hardening

**Spec:** Add bounds checking and validation in the CVM interpreter before
execution. Validate jump targets, memory accesses, and stack operations.

**Files:** `cvm_host.c`

**DOD:**
- All jump targets validated against code bounds
- Memory accesses checked against module arena
- Stack overflow/underflow detected
- Malformed CVM module cannot corrupt kernel

---

## Phase 4: Observability and Unified Testing (Weeks 6-9, MEDIUM)

### 4.1 Unified Test Pipeline

**Spec:** Integrate `test_bdd.sh`, `mcp/test_minios_mcp.py`, `mutate.sh`,
and `tools/test_codecs.sh` into a single CI workflow with consolidated
reports.

**Files:** `.github/workflows/test.yml`, `tools/run_all_tests.sh`

**DOD:**
- Single CI workflow runs all test suites
- Consolidated pass/fail report
- One view of system health
- Regression caught in single pipeline

### 4.2 GUI Testing via MCP

**Spec:** Extend MCP bridge with framebuffer assertions using the `gfx`
builtin. Validate desktop environment automatically.

**Files:** `mcp/minios_mcp.py`, `mcp/test_minios_mcp.py`

**DOD:**
- MCP tool for framebuffer pixel inspection
- BDD scenarios validate desktop rendering
- Automated GUI regression detection

---

## Phase 5: Testing and Resiliency (Weeks 8-11, MEDIUM-LOW)

### 5.1 SMP Regression Tests

**Spec:** Boot with 1, 2, and 4 cores in CI matrix. Verify all scenarios
pass without timeout or panic.

**Files:** `.github/workflows/test.yml` (matrix), `test_bdd.sh`

**DOD:**
- CI matrix: QEMU with 1, 2, 4 cores
- All BDD scenarios pass in each configuration
- No timeout, no panic, no corruption

### 5.2 Runtime Integration Tests

**Spec:** Compile and execute hello world in C, Lua, MicroPython, and CVM
on each push.

**Files:** `test_bdd.sh` (new scenarios)

**DOD:**
- Four runtimes produce expected output
- Regression caught per-commit
- All runtimes verified functional

### 5.3 Network End-to-End Tests

**Spec:** DNS + TCP + TLS handshake against local fixture. Full round-trip
verified in CI.

**Files:** `test_bdd.sh`, `test_http_server.py`

**DOD:**
- TLS 1.2 handshake completes successfully
- DNS resolution works
- TCP data transfer verified
- End-to-end network stack proven

### 5.4 Mutation Testing Expansion

**Spec:** Extend `mutate.sh` to cover `sched.c`, `smp.c`, and `vfs_ops`
code paths. Target mutation score > 70% on critical modules.

**Files:** `mutate.sh`

**DOD:**
- Mutants for sched.c, smp.c, VFS dispatch
- Mutation score > 70% on critical modules
- Every surviving mutant documented as equivalent or test gap

### 5.5 Documented non-goals (audit 2026-09)

**Spec:** record the items an external audit flagged that are deliberate
design scope, not defects, so future audits stop re-flagging them.
- Polled RTL8139 + stop-and-wait TCP/536-byte MSS: the teaching/bare-metal
  contract (`net/net.c`, `net/rtl8139.c` headers). An IRQ-driven NIC with
  sliding windows is a new feature, not a fix; no interrupt controller is
  configured by design.
- No VFS buffer cache: the ramdisk is memory (always durable) and MiniFS
  persists through close/sync; `sys_linux_fsync` documents this. A cache
  is future perf work, not a correctness gap.
- `sys_linux_flock` answers 0: advisory-only scope, same class as fsync.
  If real locking is ever needed it becomes `-ENOSYS`, never a silent lie.

**Files:** `ARCHITECTURE_PLAN.md` (this entry)

---

## Phase 6: God Object Reduction (Weeks 10-16, LOW but STRATEGIC)

### 6.0 Decompose syscalls.c, proc-leaf increment (DONE)

**Spec:** move the proc-leaf handlers out of the `syscalls.c`
mega-dispatcher into `kernel/syscalls_proc.c` + `syscalls_proc.h`,
keeping dispatch-table names stable. Done (see Phase 1.5). Next
increments in risk order: fd table, spawn bridge, mm (brk/mmap),
net handlers, gfx handlers. Each increment keeps table names stable
and must pass the full validation gate before the next starts.

### 6.0a Fail-closed process stubs (DONE)

**Spec:** `sys_linux_fork`, `sys_linux_vfork` and `sys_linux_execve`
have no implementation. They answered 0 (success), which let userland
believe a child existed when none did. All three now answer `-ENOSYS`
(-38, the same code the dispatch default and `prlimit64` use), never
success. `tools/check_fork_stubs.py` gates this in `make lint`: any
success return in those handlers fails the build.

**Files:** `kernel/syscalls_proc.c`, `tools/check_fork_stubs.py` (new),
`Makefile` (lint rule), `CLAUDE.md` (honest-limits line + lint contract)

### 6.0b Syscall sanitize audit + clone hardening (DONE)

**Spec:** the audit asked for a line-by-line proof that every user pointer
is checked before first dereference. `tools/check_syscall_sanitize.py`
provides it: pointer aliases of a1..a6 must appear in a SANITIZE_* or
user_* check in the same case-block, and raw args reaching known
dereferencing callees (`futex_wait`, `net_sys_*`, `do_clone`) must be
checked at the boundary. Callees that sanitize internally
(`k_syscall_spawn`, `do_open_path`) stay delegated. The sweep found one
real gap: `sys_minios_clone` passed `newsp` to `do_clone` unchecked; it
now fails closed with `EFAULT` (0 still means inherit). futex/net
boundaries were all present; `net_sys_sendto/recvfrom` ignore `to`/`from`
by design (TCP-only), so no hidden hole there.

**Files:** `tools/check_syscall_sanitize.py` (new),
`kernel/syscalls_proc.c` (clone check), `Makefile` (lint rule)

**DOD:**
- Audit green on the tree
- Three mutants killed (futex check, sendto check, clone check removed)
- `make test-sanitize`, `make test-futex` green

**DOD:**
- fork/vfork/execve answer -ENOSYS
- Stub gate green, mutant (stub back to 0) killed by the gate
- `make test-sanitize`, `check_abi_numbers` green

### 6.1 Extract Shell to shell.c

**Spec:** Move `shell_run`, `shell_cmd_*`, `shell_exec_builtin` and all
shell builtins to `shell.c`/`shell.h`. kernel.c loses ~80 functions.

**Files:** `shell.c` (new), `shell.h` (new), `kernel.c`, `kernel.h`,
`Makefile`

**DOD:**
- `shell.c` compiles independently
- kernel.c loses shell functions
- All BDD shell scenarios pass
- `shell.c` is testable in isolation

### 6.2 Extract Editor to editor.c

**Spec:** Move `edit_*` functions to `editor.c`/`editor.h`.

**Files:** `editor.c` (new), `editor.h` (new), `kernel.c`, `Makefile`

**DOD:**
- `editor.c` compiles independently
- All BDD editor scenarios pass
- Editor testable without full boot

### 6.3 Extract ELF Loader to loader.c

**Spec:** Move `shell_load`, relocation logic, libc registration to
`loader.c`/`loader.h`.

**Files:** `loader.c` (new), `loader.h` (new), `kernel.c`, `Makefile`

**DOD:**
- `loader.c` compiles independently
- Loader testable with binary fixtures
- All ELF-related BDD scenarios pass

### 6.4 Extract Memory Management to mm.c

**Spec:** Move heap, mmap, VMA management to `mm.c`/`mm.h`.

**Files:** `mm.c` (new), `mm.h` (new), `kernel.c`, `Makefile`

**DOD:**
- `mm.c` compiles independently
- kernel.c drops below 200 symbols
- Memory BDD scenarios pass

### 6.5 Validate with readmenator

**Spec:** Confirm kernel.c PageRank score dropped from 61.4 to below 30
in the regenerated KNOWLEDGE_BASE.md.

**DOD:**
- readmenator confirms score reduction
- KNOWLEDGE_BASE.md updated
- CPG proves deconcentration

---

## Execution Order

```
Month 1: Phase 1 (Stabilize) + Phase 2 (Governance in CI)
Month 2: Phase 3 (Unify runtimes) + Phase 4 (Unified testing)
Month 3: Phase 5 (Resiliency) + Phase 6 (God object reduction)
```

Critical gate: After Phase 2, KNOWLEDGE_BASE.md must auto-generate and
validate on every push, acting as the architectural arbiter.

## Dependency Map

```
Phase 1 ──> Phase 3 ──> Phase 6
  |            |
  v            v
Phase 2 ──> Phase 4 ──> Phase 5
```

Rule: No later phase begins without the prior phase complete.
Phases 2, 4, 5 can run in parallel with their dependencies met.
Phase 6 goes last because it needs Phase 5's test safety net.
