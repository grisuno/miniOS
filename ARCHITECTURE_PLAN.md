# MiniOS Unified Architectural Improvement Plan

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

## Phase 1: Stabilize Existing Abstractions (Weeks 1-3, CRITICAL)

### 1.1 ABI Versioning

**Spec:** Add `MINIOS_ABI_VERSION` (monotonic integer) and `MINIOS_ABIChecksum`
(computed from layout constants) to `minios_abi.h`. The ELF loader verifies
both before accepting a binary. Mismatch returns `-EABI_MISMATCH`.

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

---

## Phase 6: God Object Reduction (Weeks 10-16, LOW but STRATEGIC)

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
