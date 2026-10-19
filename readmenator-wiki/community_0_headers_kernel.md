# headers: kernel

*Community 0 | 137 files | cohesion 0.90*

## Definition

This community groups 137 file(s) rooted at `headers` with dominant language c (cohesion 0.90). Central symbols: `A20_CONTROL_PORT`, `A20_ENABLE_BIT`, `A20_RESET_CLEAR_MASK`, `ALIGN_UP`, `AP_STUB_ADDR`, `ARCH_X86_CPU_SETUP_H`, `ARCH_X86_MSR_H`, `BC_LINE`. Core file: `headers/kernel.h` (412 symbols). Documented purpose: SMP application-processor bootstrap stub..

## Files

### `headers` (41 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/ap_stub.h` | h | testing | 0 | yes |
| `headers/block.h` | h | utility | 14 | yes |

### `tests` (23 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_driver.c` | c | testing | 5 | yes |
| `tests/test_ext4.c` | c | testing | 31 | yes |

### `kernel` (21 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/console.c` | c | utility | 27 | yes |
| `kernel/console_in.c` | c | utility | 31 | yes |

### `drivers` (15 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `drivers/block.c` | c | infrastructure | 19 | yes |
| `drivers/driver.c` | c | infrastructure | 8 | yes |

### `headers/drivers` (10 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/drivers/kbd.h` | h | infrastructure | 24 | yes |
| `headers/drivers/modifiers.h` | h | infrastructure | 11 | yes |

### `fs` (7 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fs/ext4.c` | c | utility | 38 | yes |

### `.` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel.c` | c | utility | 15 | yes |

### `kernel/mm` (4 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/mm/cow.c` | c | utility | 28 | yes |

### `headers/arch/x86` (3 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/arch/x86/cpu_setup.h` | h | infrastructure | 2 | yes |

### `arch/x86` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `arch/x86/ap_entry.S` | S | utility | 9 | yes |

### `arch/x86/boot` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `arch/x86/boot/stage1.S` | S | utility | 11 | yes |

### `net` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `net/net.c` | c | utility | 157 | yes |

### `headers/arch/x86/boot` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/arch/x86/boot/bootdefs.h` | h | utility | 157 | yes |

### `headers/kernel` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/kernel/console_in.h` | h | utility | 11 | yes |

### `headers/net` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/net/rtl8139.h` | h | utility | 8 | no |

*... and 117 more files in this community.*


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

- Internal resolved imports (EXTRACTED): 319
- Cross-boundary resolved imports (EXTRACTED): 37

## Connections

- [EXTRACTED] depends_on community 0 <-> 5 (strength 0.9): Extracted import edge crosses communities: drivers/kbd.c imports headers/wm_events.h.
- [EXTRACTED] depends_on community 0 <-> 2 (strength 0.9): Extracted import edge crosses communities: drivers/pcm2.c imports headers/pcm_ring.h.
- [EXTRACTED] depends_on community 4 <-> 0 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports headers/kernel.h.
- [EXTRACTED] depends_on community 0 <-> 8 (strength 0.9): Extracted import edge crosses communities: kernel/sched.c imports headers/tick.h.
- [EXTRACTED] depends_on community 0 <-> 7 (strength 0.9): Extracted import edge crosses communities: kernel/syscalls.c imports headers/batch.h.
- [INFERRED] shares_context community 0 <-> 6 (strength 0.5): Inferred shared context (layer utility) with no import path between community 0 (headers: kernel) and community 6 (progs/doomgeneric: net_defs).
- [INFERRED] shares_context community 0 <-> 10 (strength 0.5): Inferred shared context (language c and layer utility) with no import path between community 0 (headers: kernel) and community 10 (orphans).

## Risks

- [dataflow DEAD_STORE] `drivers/sb16.c:259` `sb16_pump` `dst`: `dst` assigned at line 259 but never read afterwards.
- [dataflow DEAD_STORE] `drivers/sb16.c:531` `sb16_init` `major`: `major` assigned at line 531 but never read afterwards.
- [dataflow DEAD_STORE] `drivers/virtio_blk.c:169` `vblk_desc` `d`: `d` assigned at line 169 but never read afterwards.
- [dataflow DEAD_STORE] `drivers/virtio_blk.c:189` `vblk_avail_push` `a`: `a` assigned at line 189 but never read afterwards.
- [dataflow DEAD_STORE] `drivers/virtio_net.c:146` `vnet_desc` `d`: `d` assigned at line 146 but never read afterwards.
- [dataflow DEAD_STORE] `fs/kfile.c:103` `kpipe_pair` `ref`: `ref` assigned at line 103 but never read afterwards.
- [dataflow UNINIT_USE] `kernel/loader.c:932` `ldso_bind_into` `symname`: `symname` may be read before initialization (declared line 896).
- [dataflow DEAD_STORE] `kernel/loader.c:1278` `load_exec_elf` `base`: `base` assigned at line 1278 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/loader.c:1283` `load_exec_elf` `max_end`: `max_end` assigned at line 1283 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/mm/cow.c:117` `cow_rehash` `ref`: `ref` assigned at line 117 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/mm/paging.c:44` `mm_setup_protections` `pd`: `pd` assigned at line 44 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/mm/paging.c:686` `honest` `pt`: `pt` assigned at line 686 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:632` `irqstat_report` `txf`: `txf` assigned at line 632 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:1399` `syscall` `wheel`: `wheel` assigned at line 1399 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/sched.c:2080` `proc_spawn_elf_inner` `frame`: `frame` assigned at line 2080 but never read afterwards.

## Open Questions

- Why do 14 file(s) lack file-level docs (e.g. `arch/x86/syscall_entry.S`)? What purpose do they serve?
- What would break if the most connected file in headers: kernel changed?
- Should headers: kernel be split, given cohesion 0.90?

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
- `drivers/virtio_net.c`
- `drivers/xhci.c`
- `fs/ext4.c`
- *... and 117 more*
