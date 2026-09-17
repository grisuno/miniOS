# orphans

*Community 15 | 84 files | cohesion 0.00*

## Definition

This community groups 84 file(s) rooted at `tools` with dominant language py (cohesion 0.00). Central symbols: `AES_AFFINE_C`, `AES_BLOCK`, `AES_EXIT_FAIL`, `AES_HDR_SIZE`, `AES_KEY_BYTES`, `AES_MAGIC0`, `AES_MAGIC1`, `AES_MAGIC2`. Core file: `mcp/test_minios_mcp.py` (104 symbols). Documented purpose: Docstring: Scoped WM validation for Alt-Tab and tile across all windows. Runs host WM unit tests, rebuilds touched kernel objects with zero warnings, and assert.

## Files

### `tools` (36 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tools/boot_run.sh` | sh | utility | 0 | yes |
| `tools/check_abi_numbers.py` | py | utility | 4 | yes |

### `progs/src` (21 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/src/aes.c` | c | utility | 55 | yes |
| `progs/src/cp.c` | c | utility | 8 | no |

### `progs/asm` (10 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/asm/aes.s` | s | utility | 28 | no |
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
| `arch/x86/ctx_sw.S` | S | utility | 6 | no |
| `arch/x86/isr_stubs.S` | S | testing | 24 | no |

### `progs/micropython/variants/minios` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `progs/micropython/variants/minios/manifest.py` | py | utility | 0 | yes |
| `progs/micropython/variants/minios/mpconfigvariant.h` | h | infrastructure | 38 | no |

### `tests` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/host_aes.sh` | sh | testing | 3 | yes |

### `.` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `bootloader.c` | c | utility | 4 | no |

### `kernel` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/cvm_host.c` | c | utility | 55 | no |

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

*... and 64 more files in this community.*


## Key Symbols

- `switch_save_only` (function, `arch/x86/ctx_sw.S:44`)
- `switch_to` (function, `arch/x86/ctx_sw.S:53`)
- `switch_to_notrap` (function, `arch/x86/ctx_sw.S:96`)
- `user_trampoline` (function, `arch/x86/ctx_sw.S:181`)
- `resume_iretq` (function, `arch/x86/ctx_sw.S:194`)
- `k_run_on_stack` (function, `arch/x86/ctx_sw.S:234`)
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
- `isr_common` (function, `arch/x86/isr_stubs.S:96`)
- `isr_stub_table` (function, `arch/x86/isr_stubs.S:195`)

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 0
- Cross-boundary resolved imports (EXTRACTED): 0

## Connections

- No cross-community bridges recorded. This community is self-contained.

## Risks

- [critical] `mcp/mutate_mcp.sh:85` S001: Command injection via eval — can execute arbitrary commands Fix: Avoid shell=True and string-built commands; use argument arrays and input allowlists.
- [critical] `tools/check_abi_numbers.py:122` PY002: Use of eval/exec — can lead to arbitrary code execution Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- [critical] `tools/check_abi_numbers.py:123` PY002: Use of eval/exec — can lead to arbitrary code execution Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- [critical] `tools/check_abi_numbers.py:124` PY002: Use of eval/exec — can lead to arbitrary code execution Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- [critical] `tools/check_fork_stubs.py:19` (in `Config`) PY002: Use of eval/exec — can lead to arbitrary code execution Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- [critical] `tools/check_fork_stubs.py:24` (in `handler_body`) PY002: Use of eval/exec — can lead to arbitrary code execution Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- [critical] `tools/check_syscall_sanitize.py:22` (in `Config`) PY002: Use of eval/exec — can lead to arbitrary code execution Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- [critical] `tools/check_syscall_sanitize.py:25` (in `Config`) PY002: Use of eval/exec — can lead to arbitrary code execution Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- [critical] `tools/check_syscall_sanitize.py:29` (in `Config`) PY002: Use of eval/exec — can lead to arbitrary code execution Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- [critical] `tools/check_syscall_sanitize.py:30` (in `Config`) PY002: Use of eval/exec — can lead to arbitrary code execution Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- [critical] `tools/check_syscall_sanitize.py:35` (in `Config`) PY002: Use of eval/exec — can lead to arbitrary code execution Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- [critical] `tools/check_syscall_sanitize.py:36` (in `Config`) PY002: Use of eval/exec — can lead to arbitrary code execution Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- [critical] `tools/check_syscall_sanitize.py:37` (in `Config`) PY002: Use of eval/exec — can lead to arbitrary code execution Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- [critical] `tools/check_syscall_sanitize.py:74` (in `split_functions`) PY002: Use of eval/exec — can lead to arbitrary code execution Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.
- [critical] `tools/kernel_feature_survey.py:24` (in `SurveyConfig`) PY002: Use of eval/exec — can lead to arbitrary code execution Fix: Replace eval/exec with JSON parsing, dispatch tables, or ast.literal_eval.

## Open Questions

- Why do 29 file(s) lack file-level docs (e.g. `arch/x86/ctx_sw.S`)? What purpose do they serve?
- What would break if the most connected file in orphans changed?
- Should orphans be split, given cohesion 0.00?

## Sources

- `arch/x86/ctx_sw.S`
- `arch/x86/isr_stubs.S`
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
- `progs/doomgeneric/m_random.c`
- *... and 64 more*
