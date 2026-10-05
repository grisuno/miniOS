# headers

*Community 0 | 40 files | cohesion 0.55*

## Definition

This community groups 40 file(s) rooted at `headers` with dominant language c (cohesion 0.55). Central symbols: `A20_CONTROL_PORT`, `A20_ENABLE_BIT`, `A20_RESET_CLEAR_MASK`, `AP_STUB_ADDR`, `ARCH_X86_MSR_H`, `ARENA_DEFAULT_ALIGN`, `BIOS_DISK_EXT_ACK_MAGIC`, `BIOS_DISK_EXT_CHECK`. Core file: `headers/vga_fb.h` (149 symbols). Documented purpose: SMP application-processor bootstrap stub..

## Files

### `headers` (12 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/ap_stub.h` | h | testing | 0 | yes |
| `headers/arena.h` | h | utility | 15 | yes |
| `headers/block.h` | h | utility | 14 | yes |

### `fs` (7 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `fs/ext4.c` | c | utility | 38 | yes |
| `fs/fat32.c` | c | utility | 31 | yes |
| `fs/fsimg.c` | c | utility | 5 | yes |

### `kernel` (6 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/console.c` | c | utility | 27 | yes |
| `kernel/exec.c` | c | utility | 10 | yes |
| `kernel/ldso_parse.c` | c | utility | 20 | yes |

### `tests` (6 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `tests/test_arena.c` | c | testing | 2 | yes |
| `tests/test_ext4.c` | c | testing | 31 | yes |

### `.` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel.c` | c | utility | 16 | yes |
| `smp.c` | c | utility | 39 | yes |

### `arch/x86/boot` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `arch/x86/boot/stage1.S` | S | utility | 11 | yes |
| `arch/x86/boot/stage2.S` | S | utility | 40 | yes |

### `kernel/mm` (2 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `kernel/mm/cow.c` | c | utility | 16 | yes |
| `kernel/mm/paging.c` | c | utility | 28 | yes |

### `arch/x86` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `arch/x86/ap_entry.S` | S | utility | 9 | yes |

### `headers/arch/x86` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/arch/x86/msr.h` | h | utility | 9 | yes |

### `headers/arch/x86/boot` (1 files)

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/arch/x86/boot/bootdefs.h` | h | utility | 146 | yes |

*... and 20 more files in this community.*


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

- Internal resolved imports (EXTRACTED): 72
- Cross-boundary resolved imports (EXTRACTED): 60

## Connections

- [EXTRACTED] depends_on community 2 <-> 0 (strength 0.9): Extracted import edge crosses communities: drivers/block.c imports headers/block.h.
- [EXTRACTED] depends_on community 4 <-> 0 (strength 0.9): Extracted import edge crosses communities: drivers/kbd.c imports headers/vga_fb.h.
- [EXTRACTED] depends_on community 5 <-> 0 (strength 0.9): Extracted import edge crosses communities: drivers/pcm2.c imports headers/arch/x86/boot/bootdefs.h.
- [EXTRACTED] depends_on community 9 <-> 0 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports headers/ldso.h.
- [EXTRACTED] depends_on community 0 <-> 10 (strength 0.9): Extracted import edge crosses communities: headers/smp.h imports headers/spinlock.h.

## Risks

- [dataflow DEAD_STORE] `fs/kfile.c:103` `kpipe_pair` `ref`: `ref` assigned at line 103 but never read afterwards.
- [dataflow UNINIT_USE] `kernel/loader.c:925` `ldso_bind_into` `symname`: `symname` may be read before initialization (declared line 889).
- [dataflow DEAD_STORE] `kernel/loader.c:1074` `load_exec_elf` `base`: `base` assigned at line 1074 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/loader.c:1079` `load_exec_elf` `max_end`: `max_end` assigned at line 1079 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/mm/paging.c:43` `mm_setup_protections` `pd`: `pd` assigned at line 43 but never read afterwards.
- [dataflow DEAD_STORE] `kernel/mm/paging.c:638` `honest` `pt`: `pt` assigned at line 638 but never read afterwards.

## Open Questions

- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.55?

## Sources

- `arch/x86/ap_entry.S`
- `arch/x86/boot/stage1.S`
- `arch/x86/boot/stage2.S`
- `fs/ext4.c`
- `fs/fat32.c`
- `fs/fsimg.c`
- `fs/kfile.c`
- `fs/minifs.c`
- `fs/pcache.c`
- `fs/vfs.c`
- `headers/ap_stub.h`
- `headers/arch/x86/boot/bootdefs.h`
- `headers/arch/x86/msr.h`
- `headers/arena.h`
- `headers/block.h`
- `headers/ext4.h`
- `headers/fat32.h`
- `headers/fsimg.h`
- `headers/ldso.h`
- `headers/minifs.h`
- *... and 20 more*
