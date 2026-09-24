# headers

*Community 0 | 33 files | cohesion 0.48*

## Definition

This community groups 33 file(s) rooted at `headers` with dominant language c (cohesion 0.48). Central symbols: `A20_CONTROL_PORT`, `A20_ENABLE_BIT`, `A20_RESET_CLEAR_MASK`, `AP_STUB_ADDR`, `BIOS_DISK_EXT_ACK_MAGIC`, `BIOS_DISK_EXT_CHECK`, `BIOS_DISK_EXT_PACKET_BIT`, `BIOS_DISK_EXT_REQ_MAGIC`. Core file: `headers/arch/x86/boot/bootdefs.h` (143 symbols). Documented purpose: SMP application-processor bootstrap stub..

## Files

### `headers` (13 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/futex.h` | h | utility | 17 | yes |
| `headers/ktime.h` | h | utility | 3 | yes |
| `headers/pcm2.h` | h | utility | 21 | yes |
| `headers/pcm_ring.h` | h | utility | 7 | yes |
| `headers/percpu_rq.h` | h | utility | 14 | yes |

### `tests` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_futex.c` | c | testing | 6 | yes |
| `tests/test_ktime.c` | c | testing | 2 | yes |
| `tests/test_pcm.c` | c | testing | 9 | yes |
| `tests/test_percpu_rq.c` | c | testing | 2 | yes |
| `tests/test_randmix.c` | c | testing | 3 | yes |

### `kernel` (6 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/futex.c` | c | utility | 7 | yes |
| `kernel/percpu_rq.c` | c | utility | 9 | yes |
| `kernel/rcu.c` | c | utility | 14 | yes |
| `kernel/sched.c` | c | utility | 97 | no |

### `arch/x86/boot` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `arch/x86/boot/stage1.S` | S | utility | 11 | yes |
| `arch/x86/boot/stage2.S` | S | utility | 40 | yes |

### `drivers` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/pcm2.c` | c | infrastructure | 43 | yes |
| `drivers/sb16.c` | c | infrastructure | 64 | yes |

### `arch/x86` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `arch/x86/ap_entry.S` | S | utility | 9 | yes |

### `headers/arch/x86/boot` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/arch/x86/boot/bootdefs.h` | h | utility | 143 | yes |

*... and 13 more files in this community.*


## Key Symbols

- `ap_stub_start` (function, `arch/x86/ap_entry.S:21`)
- `ap_pm` (function, `arch/x86/ap_entry.S:39`)
- `ap_lm` (function, `arch/x86/ap_entry.S:62`)
- `ap_patch_slot` (function, `arch/x86/ap_entry.S:80`)
- `ap_gdt32` (function, `arch/x86/ap_entry.S:84`)
- `ap_gdt32_ptr` (function, `arch/x86/ap_entry.S:88`) - movw %ax, %ss /* Load smp_ap_entry()'s address from the BSP-patched slot and go. mov ap_patch_slot(%
- `ap_gdt32_end` (function, `arch/x86/ap_entry.S:91`)
- `ap_gdt64_ptr` (function, `arch/x86/ap_entry.S:93`)
- `ap_stub_end` (function, `arch/x86/ap_entry.S:98`)
- `main` (function, `arch/x86/boot/stage1.S:28`)
- `normalize` (function, `arch/x86/boot/stage1.S:32`)
- `no_extensions` (function, `arch/x86/boot/stage1.S:78`)
- `read_failed` (function, `arch/x86/boot/stage1.S:82`)
- `fail` (function, `arch/x86/boot/stage1.S:85`)
- `halt` (function, `arch/x86/boot/stage1.S:88`)
- `puts` (function, `arch/x86/boot/stage1.S:93`)
- `puts_next` (function, `arch/x86/boot/stage1.S:97`)
- `puts_done` (function, `arch/x86/boot/stage1.S:103`)
- `msg_no_lba` (function, `arch/x86/boot/stage1.S:107`)
- `msg_read` (function, `arch/x86/boot/stage1.S:109`)
- `stage2_main` (function, `arch/x86/boot/stage2.S:39`)
- `a20_ready` (function, `arch/x86/boot/stage2.S:54`)
- `load_chunk` (function, `arch/x86/boot/stage2.S:69`)
- `chunk_size_ready` (function, `arch/x86/boot/stage2.S:74`)
- `read_piece` (function, `arch/x86/boot/stage2.S:81`)
- `piece_size_ready` (function, `arch/x86/boot/stage2.S:86`)
- `chunk_copy` (function, `arch/x86/boot/stage2.S:118`)
- `chunk_leave_pm` (function, `arch/x86/boot/stage2.S:131`)
- `chunk_resume` (function, `arch/x86/boot/stage2.S:141`)
- `enter_long_mode` (function, `arch/x86/boot/stage2.S:162`)

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 47
- Cross-boundary resolved imports (EXTRACTED): 50

## Connections

- [EXTRACTED] depends_on community 0 <-> 2 (strength 0.9): Extracted import edge crosses communities: drivers/pcm2.c imports headers/kernel.h.
- [EXTRACTED] depends_on community 0 <-> 1 (strength 0.9): Extracted import edge crosses communities: drivers/sb16.c imports headers/driver.h.
- [EXTRACTED] depends_on community 0 <-> 8 (strength 0.9): Extracted import edge crosses communities: kernel/sched.c imports headers/tick.h.
- [EXTRACTED] depends_on community 0 <-> 3 (strength 0.9): Extracted import edge crosses communities: kernel/sched.c imports headers/arch/x86/hal_io.h.
- [EXTRACTED] depends_on community 0 <-> 7 (strength 0.9): Extracted import edge crosses communities: kernel/syscalls.c imports headers/batch.h.
- [EXTRACTED] depends_on community 9 <-> 0 (strength 0.9): Extracted import edge crosses communities: kernel/time.c imports headers/ktime.h.
- [EXTRACTED] depends_on community 0 <-> 6 (strength 0.9): Extracted import edge crosses communities: tests/test_pcm.c imports kernel/string.c.
- [INFERRED] shares_context community 0 <-> 4 (strength 0.5): Inferred shared context (language c) with no import path between community 0 (headers) and community 4 (headers/drivers).
- [INFERRED] shares_context community 0 <-> 5 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 0 (headers) and community 5 (headers).
- [INFERRED] shares_context community 0 <-> 10 (strength 0.5): Inferred shared context (layer utility) with no import path between community 0 (headers) and community 10 (progs/src).

## Risks

- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/spinlock.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/spinlock.h` via `subprocess` (3 hops)
- [taint high] `mcp/minios_addons.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [dataflow DEAD_STORE] `drivers/sb16.c:259` `sb16_pump` `dst`: `dst` assigned at line 259 but never read afterwards.
- [dataflow DEAD_STORE] `drivers/sb16.c:531` `sb16_init` `major`: `major` assigned at line 531 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:411` `irqstat_report` `txf`: `txf` assigned at line 411 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:1151` `syscall` `wheel`: `wheel` assigned at line 1151 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:1740` `proc_spawn_elf_inner` `frame`: `frame` assigned at line 1740 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:1828` `schedule` `cpu`: `cpu` assigned at line 1828 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:2215` `MSR` `frame`: `frame` assigned at line 2215 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:2381` `it` `cr3`: `cr3` assigned at line 2381 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/syscalls.c:250` `sys_minios_gfx_zoom` `gfx_zoom_2x`: `gfx_zoom_2x` assigned at line 250 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/syscalls.c:408` `sys_minios_gfx_title` `gfx_win_title`: `gfx_win_title` assigned at line 408 but never read afterwards.

## Open Questions

- Why do 1 file(s) lack file-level docs (e.g. `kernel/sched.c`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.48?

## Sources

- `arch/x86/ap_entry.S`
- `arch/x86/boot/stage1.S`
- `arch/x86/boot/stage2.S`
- `drivers/pcm2.c`
- `drivers/sb16.c`
- `headers/arch/x86/boot/bootdefs.h`
- `headers/futex.h`
- `headers/ktime.h`
- `headers/pcm2.h`
- `headers/pcm_ring.h`
- `headers/percpu_rq.h`
- `headers/randmix.h`
- `headers/rcu.h`
- `headers/sanitize.h`
- `headers/sb16.h`
- `headers/spinlock.h`
- `headers/sync.h`
- `headers/syscalls_proc.h`
- `headers/zip.h`
- `kernel/futex.c`
- *... and 13 more*
