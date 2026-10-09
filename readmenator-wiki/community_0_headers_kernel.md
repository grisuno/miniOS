# headers: kernel

*Community 0 | 143 files | cohesion 0.88*

## Definition

This community groups 143 file(s) rooted at `headers` with dominant language c (cohesion 0.88). Central symbols: `A20_CONTROL_PORT`, `A20_ENABLE_BIT`, `A20_RESET_CLEAR_MASK`, `ABI_BAD_FORMAT`, `ABI_CHECKSUM_MISMATCH`, `ABI_H`, `ABI_MANIFEST_MAX`, `ABI_MANIFEST_NAME`. Core file: `headers/kernel.h` (410 symbols). Documented purpose: SMP application-processor bootstrap stub..

## Files

### `headers` (46 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/abi.h` | h | utility | 10 | yes |
| `headers/ap_stub.h` | h | testing | 0 | yes |

### `tests` (28 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_abi.c` | c | testing | 2 | yes |
| `tests/test_arena.c` | c | testing | 2 | yes |

### `kernel` (25 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/abi.c` | c | utility | 3 | yes |
| `kernel/batch.c` | c | utility | 1 | yes |

### `drivers` (14 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/block.c` | c | infrastructure | 19 | yes |
| `drivers/driver.c` | c | infrastructure | 8 | yes |

### `headers/drivers` (8 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/drivers/kbd.h` | h | infrastructure | 24 | yes |
| `headers/drivers/modifiers.h` | h | infrastructure | 11 | yes |

### `fs` (7 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fs/ext4.c` | c | utility | 38 | yes |
| `fs/fat32.c` | c | utility | 31 | yes |

### `.` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel.c` | c | utility | 16 | yes |
| `qga.c` | c | utility | 27 | yes |

### `kernel/mm` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/mm/cow.c` | c | utility | 28 | yes |

### `arch/x86` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `arch/x86/ap_entry.S` | S | utility | 9 | yes |

### `arch/x86/boot` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `arch/x86/boot/stage1.S` | S | utility | 11 | yes |

### `headers/arch/x86` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/arch/x86/hal_io.h` | h | utility | 69 | yes |

### `headers/arch/x86/boot` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/arch/x86/boot/bootdefs.h` | h | utility | 151 | yes |

### `headers/kernel` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/kernel/console_in.h` | h | utility | 11 | yes |

*... and 123 more files in this community.*


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

- Internal resolved imports (EXTRACTED): 301
- Cross-boundary resolved imports (EXTRACTED): 42

## Connections

- [EXTRACTED] depends_on community 0 <-> 6 (strength 0.9): Extracted import edge crosses communities: drivers/nvme.c imports headers/drivers/pci.h.
- [EXTRACTED] depends_on community 0 <-> 3 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 0 <-> 5 (strength 0.9): Extracted import edge crosses communities: headers/vga_fb.h imports headers/wm_notify.h.
- [EXTRACTED] depends_on community 0 <-> 4 (strength 0.9): Extracted import edge crosses communities: kernel/syscalls.c imports headers/ktime.h.
- [INFERRED] shares_context community 0 <-> 7 (strength 0.5): Inferred shared context (layer utility) with no import path between community 0 (headers: kernel) and community 7 (progs/doomgeneric: net_defs).
- [INFERRED] shares_context community 0 <-> 8 (strength 0.5): Inferred shared context (layer utility) with no import path between community 0 (headers: kernel) and community 8 (tools: doom_pwad).
- [INFERRED] shares_context community 0 <-> 9 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 0 (headers: kernel) and community 9 (orphans).

## Risks

- [layer strict] `tests/test_httpd.c` (testing) -> `headers/httpd.h` (presentation)
- [dataflow DEAD_STORE] `drivers/sb16.c:259` `sb16_pump` `dst`: `dst` assigned at line 259 but never read afterwards.
- [dataflow DEAD_STORE] `drivers/sb16.c:531` `sb16_init` `major`: `major` assigned at line 531 but never read afterwards.
- [dataflow DEAD_STORE] `drivers/virtio_blk.c:169` `vblk_desc` `d`: `d` assigned at line 169 but never read afterwards.
- [dataflow DEAD_STORE] `drivers/virtio_blk.c:189` `vblk_avail_push` `a`: `a` assigned at line 189 but never read afterwards.
- [dataflow DEAD_STORE] `fs/kfile.c:103` `kpipe_pair` `ref`: `ref` assigned at line 103 but never read afterwards.
- [dataflow UNINIT_USE] `kernel/loader.c:925` `ldso_bind_into` `symname`: `symname` may be read before initialization (declared line 889).
- [dataflow DEAD_STORE] `kernel/loader.c:1074` `load_exec_elf` `base`: `base` assigned at line 1074 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/loader.c:1079` `load_exec_elf` `max_end`: `max_end` assigned at line 1079 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/mm/cow.c:116` `cow_rehash` `ref`: `ref` assigned at line 116 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/mm/paging.c:43` `mm_setup_protections` `pd`: `pd` assigned at line 43 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/mm/paging.c:685` `honest` `pt`: `pt` assigned at line 685 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:625` `irqstat_report` `txf`: `txf` assigned at line 625 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:1372` `syscall` `wheel`: `wheel` assigned at line 1372 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:2053` `proc_spawn_elf_inner` `frame`: `frame` assigned at line 2053 but never read afterwards.

## Open Questions

- Why do 11 file(s) lack file-level docs (e.g. `arch/x86/syscall_entry.S`)? What purpose do they serve?
- What would break if the most connected file in headers: kernel changed?
- Should headers: kernel be split, given cohesion 0.88?

## Sources

- `arch/x86/ap_entry.S`
- `arch/x86/boot/stage1.S`
- `arch/x86/boot/stage2.S`
- `arch/x86/syscall_entry.S`
- `drivers/block.c`
- `drivers/driver.c`
- `drivers/ide.c`
- `drivers/kbd.c`
- `drivers/mouse.c`
- `drivers/nvme.c`
- `drivers/pcm2.c`
- `drivers/pcspk.c`
- `drivers/rtc.c`
- `drivers/sb16.c`
- `drivers/usbblk.c`
- `drivers/usbhid.c`
- `drivers/virtio_blk.c`
- `drivers/xhci.c`
- `fs/ext4.c`
- `fs/fat32.c`
- *... and 123 more*
