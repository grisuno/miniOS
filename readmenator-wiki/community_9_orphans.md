# orphans

*Community 9 | 109 files | cohesion 0.00*

## Definition

This community groups 109 file(s) rooted at `tools` with dominant language c (cohesion 0.00). Central symbols: `AES_AFFINE_C`, `AES_BLOCK`, `AES_EXIT_FAIL`, `AES_HDR_SIZE`, `AES_KEY_BYTES`, `AES_MAGIC0`, `AES_MAGIC1`, `AES_MAGIC2`. Core file: `mcp/test_minios_mcp.py` (104 symbols). Documented purpose: Docstring: boot/uefi_stub.c -- Minimal MiniOS UEFI stub (Phase 1)..

## Files

### `tools` (40 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tools/boot_run.sh` | sh | utility | 0 | yes |
| `tools/check_abi_numbers.py` | py | utility | 4 | yes |

### `progs/src` (31 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/src/aes.c` | c | utility | 54 | yes |
| `progs/src/aslr.c` | c | utility | 10 | yes |

### `progs/asm` (11 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/asm/aes.s` | s | utility | 30 | no |
| `progs/asm/cp.s` | s | utility | 2 | no |

### `kernel` (7 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/clip.c` | c | utility | 4 | yes |
| `kernel/cvm_host.c` | c | utility | 45 | no |

### `mcp` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `mcp/__init__.py` | py | utility | 0 | no |
| `mcp/mutate_mcp.sh` | sh | utility | 1 | yes |

### `progs/doomgeneric` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomgeneric/doom.h` | h | utility | 2 | no |

### `tests` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/host_aes.sh` | sh | testing | 3 | yes |

### `arch/x86` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `arch/x86/ctx_sw.S` | S | utility | 9 | no |

### `fs` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fs/ramdisk.c` | c | utility | 25 | yes |

### `progs/micropython/variants/minios` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/micropython/variants/minios/manifest.py` | py | utility | 0 | yes |

### `.` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `bootloader.c` | c | utility | 2 | no |

### `boot` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `boot/uefi_stub.c` | c | testing | 50 | yes |

### `progs/lisp` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/lisp/tin.c` | c | utility | 1 | no |

### `progs/micropython/variants/minios/lib` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/micropython/variants/minios/lib/__init__.py` | py | utility | 0 | yes |

### `progs/pokemon` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/pokemon/fetch.sh` | sh | utility | 0 | yes |

*... and 89 more files in this community.*


## Key Symbols

- `sched_park_capture` (function, `arch/x86/ctx_sw.S:70`) - captured the rest. Offsets mirror CTX_*_OFF in headers/sched.h (asserted in C). Requires frame point
- `switch_save_only` (function, `arch/x86/ctx_sw.S:82`)
- `switch_to` (function, `arch/x86/ctx_sw.S:91`)
- `switch_to_notrap` (function, `arch/x86/ctx_sw.S:134`)
- `user_trampoline` (function, `arch/x86/ctx_sw.S:221`)
- `fork_trampoline` (function, `arch/x86/ctx_sw.S:233`)
- `exec_enter` (function, `arch/x86/ctx_sw.S:273`)
- `resume_iretq` (function, `arch/x86/ctx_sw.S:302`)
- `k_run_on_stack` (function, `arch/x86/ctx_sw.S:342`)
- `tf_rax` (function, `arch/x86/isr_stubs.S:67`)
- `tf_rbx` (function, `arch/x86/isr_stubs.S:68`)
- `tf_rcx` (function, `arch/x86/isr_stubs.S:69`)
- `tf_rdx` (function, `arch/x86/isr_stubs.S:70`)
- `tf_rsi` (function, `arch/x86/isr_stubs.S:71`)
- `tf_rdi` (function, `arch/x86/isr_stubs.S:72`)
- `tf_rbp` (function, `arch/x86/isr_stubs.S:73`)
- `tf_r8` (function, `arch/x86/isr_stubs.S:74`)
- `tf_r9` (function, `arch/x86/isr_stubs.S:75`)
- `tf_r10` (function, `arch/x86/isr_stubs.S:76`)
- `tf_r11` (function, `arch/x86/isr_stubs.S:77`)
- `tf_r12` (function, `arch/x86/isr_stubs.S:78`)
- `tf_r13` (function, `arch/x86/isr_stubs.S:79`)
- `tf_r14` (function, `arch/x86/isr_stubs.S:80`)
- `tf_r15` (function, `arch/x86/isr_stubs.S:81`)
- `tf_rip` (function, `arch/x86/isr_stubs.S:82`)
- `tf_cs` (function, `arch/x86/isr_stubs.S:83`)
- `tf_rflags` (function, `arch/x86/isr_stubs.S:84`)
- `tf_rsp` (function, `arch/x86/isr_stubs.S:85`)
- `tf_ss` (function, `arch/x86/isr_stubs.S:86`)
- `tf_vector` (function, `arch/x86/isr_stubs.S:87`)

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 0
- Cross-boundary resolved imports (EXTRACTED): 0

## Connections

- [INFERRED] shares_context community 0 <-> 9 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 0 (headers: kernel) and community 9 (orphans).
- [INFERRED] shares_context community 1 <-> 9 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (progs/doomgeneric: d_englsh) and community 9 (orphans).

## Risks

- [taint high] `mcp/test_minios_mcp.py` -> `mcp/test_minios_mcp.py` via `subprocess` (0 hops)
- [taint high] `tests/test_minifs_tools.py` -> `tests/test_minifs_tools.py` via `subprocess` (0 hops)
- [taint high] `tools/check_kb_sync.py` -> `tools/check_kb_sync.py` via `subprocess` (0 hops)
- [taint high] `tools/check_mutant_anchors.py` -> `tools/check_mutant_anchors.py` via `subprocess` (0 hops)
- [dataflow UNCHECKED_ALLOC] `boot/uefi_stub.c:518` `efi_main` `rc`: Result of allocator stored in `rc` is never checked against NULL.

## Open Questions

- Why do 32 file(s) lack file-level docs (e.g. `arch/x86/ctx_sw.S`)? What purpose do they serve?
- Is the dangerous import `subprocess` in `mcp/test_minios_mcp.py` still required, or can it be isolated?
- What would break if the most connected file in orphans changed?
- Should orphans be split, given cohesion 0.00?

## Sources

- `arch/x86/ctx_sw.S`
- `arch/x86/isr_stubs.S`
- `boot/uefi_stub.c`
- `bootloader.c`
- `fs/ramdisk.c`
- `fs/zip.c`
- `kernel/clip.c`
- `kernel/cvm_host.c`
- `kernel/klog.c`
- `kernel/printf.c`
- `kernel/redirect.c`
- `kernel/scrollback.c`
- `kernel/symtab.c`
- `mcp/__init__.py`
- `mcp/mutate_mcp.sh`
- `mcp/test_minios_mcp.py`
- `progs/asm/aes.s`
- `progs/asm/cp.s`
- `progs/asm/fib.s`
- `progs/asm/freedom.s`
- *... and 89 more*
