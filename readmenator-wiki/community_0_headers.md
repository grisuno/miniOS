# headers

*Community 0 | 100 files | cohesion 0.84*

## Definition

This community groups 100 file(s) rooted at `headers` with dominant language c (cohesion 0.84). Central symbols: `A20_CONTROL_PORT`, `A20_ENABLE_BIT`, `A20_RESET_CLEAR_MASK`, `ABI_BAD_FORMAT`, `ABI_CHECKSUM_MISMATCH`, `ABI_H`, `ABI_MANIFEST_MAX`, `ABI_MANIFEST_NAME`. Core file: `headers/kernel.h` (317 symbols). Documented purpose: SMP application-processor bootstrap stub..

## Files

### `headers` (31 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/abi.h` | h | utility | 10 | yes |
| `headers/ap_stub.h` | h | testing | 0 | yes |

### `kernel` (25 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/abi.c` | c | utility | 3 | yes |
| `kernel/console.c` | c | utility | 24 | yes |

### `tests` (16 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_abi.c` | c | testing | 2 | yes |
| `tests/test_fault.c` | c | testing | 11 | yes |

### `drivers` (6 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/kbd.c` | c | infrastructure | 34 | yes |
| `drivers/mouse.c` | c | infrastructure | 7 | yes |

### `.` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel.c` | c | utility | 20 | yes |
| `qga.c` | c | utility | 27 | yes |

### `fs` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fs/kfile.c` | c | utility | 20 | yes |

### `arch/x86/boot` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `arch/x86/boot/stage1.S` | S | utility | 11 | yes |

### `headers/arch/x86` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/arch/x86/hal_io.h` | h | utility | 52 | yes |

### `headers/drivers` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/drivers/kbd.h` | h | infrastructure | 23 | yes |

### `headers/kernel` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/kernel/console_in.h` | h | utility | 8 | yes |

### `net` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `net/net.c` | c | utility | 56 | yes |

### `arch/x86` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `arch/x86/ap_entry.S` | S | utility | 9 | yes |

### `headers/arch/x86/boot` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/arch/x86/boot/bootdefs.h` | h | utility | 143 | yes |

### `headers/net` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/net/rtl8139.h` | h | utility | 8 | no |

### `kernel/mm` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/mm/paging.c` | c | utility | 14 | yes |

*... and 80 more files in this community.*


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

- Internal resolved imports (EXTRACTED): 214
- Cross-boundary resolved imports (EXTRACTED): 41

## Connections

- [EXTRACTED] depends_on community 1 <-> 0 (strength 0.9): Extracted import edge crosses communities: drivers/block.c imports headers/kernel.h.
- [EXTRACTED] depends_on community 0 <-> 5 (strength 0.9): Extracted import edge crosses communities: drivers/kbd.c imports headers/drivers/modifiers.h.
- [EXTRACTED] depends_on community 0 <-> 4 (strength 0.9): Extracted import edge crosses communities: drivers/kbd.c imports headers/wm_events.h.
- [EXTRACTED] depends_on community 0 <-> 8 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 7 <-> 0 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports headers/kernel.h.
- [EXTRACTED] depends_on community 0 <-> 6 (strength 0.9): Extracted import edge crosses communities: kernel/sched.c imports headers/tick.h.
- [EXTRACTED] depends_on community 0 <-> 3 (strength 0.9): Extracted import edge crosses communities: kernel/syscalls.c imports headers/batch.h.
- [EXTRACTED] depends_on community 9 <-> 0 (strength 0.9): Extracted import edge crosses communities: kernel/time.c imports headers/kernel.h.
- [INFERRED] shares_context community 0 <-> 11 (strength 0.5): Inferred shared context (layer utility) with no import path between community 0 (headers) and community 11 (tests).
- [INFERRED] shares_context community 0 <-> 12 (strength 0.5): Inferred shared context (layer utility) with no import path between community 0 (headers) and community 12 (orphans).

## Risks

- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/kernel.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/spinlock.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/vma.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/kernel.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/spinlock.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/vma.h` via `subprocess` (3 hops)
- [taint high] `mcp/minios_addons.py` -> `headers/ktime.h` via `subprocess` (2 hops)
- [taint high] `mcp/minios_addons.py` -> `headers/kernel.h` via `subprocess` (2 hops)
- [taint high] `mcp/minios_addons.py` -> `headers/spinlock.h` via `subprocess` (3 hops)
- [taint high] `mcp/minios_addons.py` -> `headers/vma.h` via `subprocess` (3 hops)
- [dataflow DEAD_STORE] `drivers/sb16.c:259` `sb16_pump` `dst`: `dst` assigned at line 259 but never read afterwards.
- [dataflow DEAD_STORE] `drivers/sb16.c:531` `sb16_init` `major`: `major` assigned at line 531 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/loader.c:458` `load_exec_elf` `base`: `base` assigned at line 458 but never read afterwards.

## Open Questions

- Why do 8 file(s) lack file-level docs (e.g. `headers/net/rtl8139.h`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.84?

## Sources

- `arch/x86/ap_entry.S`
- `arch/x86/boot/stage1.S`
- `arch/x86/boot/stage2.S`
- `drivers/kbd.c`
- `drivers/mouse.c`
- `drivers/pcm2.c`
- `drivers/pcspk.c`
- `drivers/rtc.c`
- `drivers/sb16.c`
- `fs/kfile.c`
- `fs/ramdisk.c`
- `fs/vfs.c`
- `fs/zip.c`
- `headers/abi.h`
- `headers/ap_stub.h`
- `headers/arch/x86/boot/bootdefs.h`
- `headers/arch/x86/hal_io.h`
- `headers/arch/x86/msr.h`
- `headers/drivers/kbd.h`
- `headers/drivers/mouse.h`
- *... and 80 more*
