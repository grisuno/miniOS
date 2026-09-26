# orphans

*Community 11 | 93 files | cohesion 0.00*

## Definition

This community groups 93 file(s) rooted at `tools` with dominant language c (cohesion 0.00). Central symbols: `AES_AFFINE_C`, `AES_BLOCK`, `AES_EXIT_FAIL`, `AES_HDR_SIZE`, `AES_KEY_BYTES`, `AES_MAGIC0`, `AES_MAGIC1`, `AES_MAGIC2`. Core file: `mcp/test_minios_mcp.py` (104 symbols). Documented purpose: Docstring: boot/uefi_stub.c -- Minimal MiniOS UEFI stub (Phase 1)..

## Files

### `tools` (37 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tools/boot_run.sh` | sh | utility | 0 | yes |
| `tools/check_abi_numbers.py` | py | utility | 4 | yes |

### `progs/src` (28 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/src/aes.c` | c | utility | 54 | yes |
| `progs/src/aslr.c` | c | utility | 10 | yes |

### `progs/asm` (10 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/asm/aes.s` | s | utility | 30 | no |
| `progs/asm/cp.s` | s | utility | 2 | no |

### `mcp` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `mcp/__init__.py` | py | utility | 0 | no |
| `mcp/mutate_mcp.sh` | sh | utility | 1 | yes |

### `progs/doomgeneric` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/doomgeneric/doom.h` | h | utility | 2 | no |
| `progs/doomgeneric/icon.c` | c | utility | 0 | no |

### `arch/x86` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `arch/x86/ctx_sw.S` | S | utility | 8 | no |
| `arch/x86/isr_stubs.S` | S | testing | 24 | no |

### `progs/micropython/variants/minios` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/micropython/variants/minios/manifest.py` | py | utility | 0 | yes |

### `tests` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/host_aes.sh` | sh | testing | 3 | yes |

### `.` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `bootloader.c` | c | utility | 2 | no |

### `boot` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `boot/uefi_stub.c` | c | testing | 29 | yes |

### `kernel` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/cvm_host.c` | c | utility | 45 | no |

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

*... and 73 more files in this community.*


## Key Symbols

- `switch_save_only` (function, `arch/x86/ctx_sw.S:44`)
- `switch_to` (function, `arch/x86/ctx_sw.S:53`)
- `switch_to_notrap` (function, `arch/x86/ctx_sw.S:96`)
- `user_trampoline` (function, `arch/x86/ctx_sw.S:185`)
- `fork_trampoline` (function, `arch/x86/ctx_sw.S:197`)
- `exec_enter` (function, `arch/x86/ctx_sw.S:213`)
- `resume_iretq` (function, `arch/x86/ctx_sw.S:242`)
- `k_run_on_stack` (function, `arch/x86/ctx_sw.S:282`)
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
- `tf_errcode` (function, `arch/x86/isr_stubs.S:88`)

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 0
- Cross-boundary resolved imports (EXTRACTED): 0

## Connections

- [INFERRED] shares_context community 0 <-> 11 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 0 (headers) and community 11 (orphans).

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 31 file(s) lack file-level docs (e.g. `arch/x86/ctx_sw.S`)? What purpose do they serve?
- What would break if the most connected file in orphans changed?
- Should orphans be split, given cohesion 0.00?

## Sources

- `arch/x86/ctx_sw.S`
- `arch/x86/isr_stubs.S`
- `boot/uefi_stub.c`
- `bootloader.c`
- `kernel/cvm_host.c`
- `mcp/__init__.py`
- `mcp/mutate_mcp.sh`
- `mcp/test_minios_mcp.py`
- `progs/asm/aes.s`
- `progs/asm/cp.s`
- `progs/asm/fib.s`
- `progs/asm/freedom.s`
- `progs/asm/http.s`
- `progs/asm/json.s`
- `progs/asm/ldhello.s`
- `progs/asm/lz4.s`
- `progs/asm/lzss.s`
- `progs/asm/w1.s`
- `progs/doomgeneric/doom.h`
- `progs/doomgeneric/icon.c`
- *... and 73 more*
