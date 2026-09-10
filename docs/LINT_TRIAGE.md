# LINT_TRIAGE — linter findings and verdicts (2026-09)

Every finding below was triaged: **fixed** (code changed) or **accepted**
(false positive or by-design, with reason). An accepted finding needs a
reason; "noisy tool" is not a reason.

## cppcheck (warning,performance,portability)

- `kernel/shell.c:1198 autoVariables` (error): `shell_run_cvm` handed a
  stack local's address to the interpreter through `argv[0]`. Real bug,
  **fixed** with a `kmalloc` buffer (recursion-safe, freed after the call).
- `tls_u_port.c constParameterPointer` (`net_dns_resolve(char *host)`):
  real, **fixed**: the parameter is now `const char *` in the definition
  (`tls_u_port.c`), both `freedom.c` declarations (ring-3 and miniGCC
  branches) and `http.c`. The old "miniGCC subset risk" excuse was wrong:
  `progs/src/aes.c` already uses `const char *` all over and builds
  through miniGCC+ld, and the rebuilt `freedom-mini`/`http.elf` prove it.
  The callee chain was already const-clean (`tls_u_resolve`,
  `u_minios_dns`, `getaddrinfo`), so no warnings introduced.
- `fs/minifs.c subtractPointers` (error): `&ramdisk_end[0] -
  &ramdisk_start[0]`. Real (subtraction between distinct objects is
  undefined behaviour no matter what the linker layout is), **fixed**:
  `kernel.ld` now provides the absolute symbol `ramdisk_size =
  ramdisk_end - ramdisk_start` (subtraction legal at link time) and both
  C sites (`kernel.c`, `fs/minifs.c` fallback path) read the size by
  address. The inline suppressions are gone.
- `net/net.c oppositeInnerCondition` (style): `if (pos >= len) return;`
  at the top of a `for (... && pos < len ...)` DNS answer loop. Real dead
  code (the for-condition guards every iteration entry), **removed**.
- `tls_u_main.c knownConditionTrueFalse` (`port<=0`, `port>65535` always
  false): **false positive**, confirmed by re-running with
  `--check-level=exhaustive` (clean). Default branch analysis does not
  model the `atoi`/`parse_port` reassignment.

## clang-tidy (curated gate set)

- `cert-err34-c atoi` (`tls_u_main.c`): real, **fixed** with strict
  `parse_port` (all digits, 1..65535, rejects trailing garbage and
  overflow that `atoi` swallows).
- `cert-err34-c sscanf %u` (`tls_u_port.c` dotted quad): real
  (overflow is UB before the `<256` check), **fixed** with strict
  `parse_quad` (digits+dots only, per-octet bound, full consumption).
 - `cert-err33-c` (unchecked `fprintf`/`fwrite` returns in CLI tools):
   real, **fixed**: `tls_u_main.c` routes every `stderr` diagnostic
   through `diag()`, which exits 3 fail-closed when the write fails
   (exit codes: 0 ok, 1 fetch failure, 2 usage, 3 blind operator);
   the body `fwrite` to stdout was already checked. Test harnesses
   (`test_fault.c`, `test_vma_bench.c`) check their reporting prints
   the same way. Enforced in the gate: `cert-err33-c` is now part of
   `LINT_TIDY_CHECKS`. The kernel side (`kprintf`) stays void-return
   by design, so there is no return to check there.
- `bugprone-reserved-identifier` (`_POSIX_C_SOURCE`, `_DEFAULT_SOURCE`):
  **accepted by necessity**. Feature-test macros are reserved by design;
  required to expose `getaddrinfo`/`poll` declarations.
- `bugprone-easily-swappable-parameters` (`u_raw_syscall3`,
  `tls_u_recv_timeout`): **accepted by design**. Positional `long`
  parameters mirror the syscall ABI; reordering would break the shared
  `TLS_RECV_TIMEOUT` port signature the kernel and host builds share.

## flawfinder

- `[4] printf` (`freedom.c:55`): the `printf` *declaration* for the
  miniGCC/ld path, not a call. All 60+ call sites use string literals
  (verified by grep). **False positive by construction** (stub ABI).
- `[1-2]` (`strlen`/`memcpy`/loop reads, ~60 hits): the miniGCC-subset
  sources use bounded static buffers with explicit caps by contract
  (`FREEDOM_*_MAX`, `RAMDISK_FNAME_LEN`); flawfinder is
  syntactically blind to bounds. Triaged by inspection, no change.

## gcc -Wextra (informational, 15 pre-existing)

`kernel/shell.c` (11: unused `size`/`total` params in fixed-signature
line-editor callbacks; `i < SHELL_RUN_DIRS` sign-compare),
`kernel/sched.c` (2: `?:` signedness), `net/net.c` (2: unused `sport`/
`dport` in a fixed-signature demux). All predate this work; none in
added lines (new code casts to `unsigned`). Grandfathered: the build
gate stays `-Wall` zero-warnings; `-Wextra` must stay clean on new
files only (enforced by `make lint` on the ring-3 set).
