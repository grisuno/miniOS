# headers

*Community 0 | 154 files | cohesion 0.94*

## Definition

This community groups 154 file(s) rooted at `headers` with dominant language c (cohesion 0.94). Central symbols: `A20_CONTROL_PORT`, `A20_ENABLE_BIT`, `A20_RESET_CLEAR_MASK`, `ABI_BAD_FORMAT`, `ABI_CHECKSUM_MISMATCH`, `ABI_H`, `ABI_MANIFEST_MAX`, `ABI_MANIFEST_NAME`. Core file: `headers/kernel.h` (376 symbols). Documented purpose: SMP application-processor bootstrap stub..

## Files

### `headers` (53 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/abi.h` | h | utility | 10 | yes |
| `headers/ap_stub.h` | h | testing | 0 | yes |

### `kernel` (30 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/abi.c` | c | utility | 3 | yes |
| `kernel/clip.c` | c | utility | 4 | yes |

### `tests` (27 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_abi.c` | c | testing | 2 | yes |
| `tests/test_arena.c` | c | testing | 2 | yes |

### `drivers` (11 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/block.c` | c | infrastructure | 17 | yes |
| `drivers/driver.c` | c | infrastructure | 8 | yes |

### `fs` (9 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fs/ext4.c` | c | utility | 38 | yes |
| `fs/fat32.c` | c | utility | 31 | yes |

### `headers/drivers` (6 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/drivers/kbd.h` | h | infrastructure | 23 | yes |

### `.` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel.c` | c | utility | 15 | yes |

### `kernel/mm` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/mm/cow.c` | c | utility | 16 | yes |

### `arch/x86/boot` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `arch/x86/boot/stage1.S` | S | utility | 11 | yes |

### `headers/arch/x86` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/arch/x86/hal_io.h` | h | utility | 59 | yes |

### `headers/kernel` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/kernel/console_in.h` | h | utility | 11 | yes |

### `net` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `net/net.c` | c | utility | 69 | yes |

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

*... and 134 more files in this community.*


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

- Internal resolved imports (EXTRACTED): 359
- Cross-boundary resolved imports (EXTRACTED): 24

## Connections

- [EXTRACTED] depends_on community 0 <-> 2 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 6 <-> 0 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports headers/kernel.h.
- [EXTRACTED] depends_on community 0 <-> 5 (strength 0.9): Extracted import edge crosses communities: kernel/sched.c imports headers/tick.h.
- [EXTRACTED] depends_on community 0 <-> 3 (strength 0.9): Extracted import edge crosses communities: kernel/syscalls.c imports headers/batch.h.
- [EXTRACTED] depends_on community 0 <-> 4 (strength 0.9): Extracted import edge crosses communities: kernel/syscalls.c imports headers/ktime.h.
- [EXTRACTED] depends_on community 0 <-> 1 (strength 0.9): Extracted import edge crosses communities: kernel.c imports headers/syscall_asm.h.
- [INFERRED] shares_context community 0 <-> 8 (strength 0.5): Inferred shared context (layer utility) with no import path between community 0 (headers) and community 8 (progs/src).
- [INFERRED] shares_context community 0 <-> 10 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 0 (headers) and community 10 (orphans).

## Risks

- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/kernel.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/spinlock.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/vma.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/pipe.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dbg_driver.py` -> `headers/ldso.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/kernel.h` via `subprocess` (2 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/spinlock.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/vma.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/pipe.h` via `subprocess` (3 hops)
- [taint high] `mcp/mcp_dogfood.py` -> `headers/ldso.h` via `subprocess` (3 hops)
- [layer strict] `tests/test_httpd.c` (testing) -> `headers/httpd.h` (presentation)
- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_render.h` (presentation)
- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_layout.h` (presentation)
- [layer strict] `tests/test_wm.c` (testing) -> `headers/wm_gfxview.h` (presentation)
- [dataflow DEAD_STORE] `drivers/sb16.c:259` `sb16_pump` `dst`: `dst` assigned at line 259 but never read afterwards.

## Open Questions

- Why do 12 file(s) lack file-level docs (e.g. `headers/lz4_kernel.h`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.94?

## Sources

- `arch/x86/ap_entry.S`
- `arch/x86/boot/stage1.S`
- `arch/x86/boot/stage2.S`
- `drivers/block.c`
- `drivers/driver.c`
- `drivers/ide.c`
- `drivers/kbd.c`
- `drivers/mouse.c`
- `drivers/pcm2.c`
- `drivers/pcspk.c`
- `drivers/rtc.c`
- `drivers/sb16.c`
- `drivers/virtio_blk.c`
- `drivers/virtio_net.c`
- `fs/ext4.c`
- `fs/fat32.c`
- `fs/fsimg.c`
- `fs/kfile.c`
- `fs/minifs.c`
- `fs/pcache.c`
- *... and 134 more*
