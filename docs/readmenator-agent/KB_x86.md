# Subsystem: x86

## arch/x86/ap_entry.S
- Doc: SMP application-processor bootstrap stub.
- Layer: utility
- Language: S
- Symbols:
  - `ap_stub_start` (function, line 21)
  - `ap_pm` (function, line 39)
  - `ap_lm` (function, line 62)
  - `ap_patch_slot` (function, line 80)
  - `ap_gdt32` (function, line 84)
  - `ap_gdt32_ptr` (function, line 88)
  - `ap_gdt32_end` (function, line 91)
  - `ap_gdt64_ptr` (function, line 93)
  - `ap_stub_end` (function, line 98)
- Depends on: `headers/arch/x86/boot/bootdefs.h`

## arch/x86/ctx_sw.S
- Doc: sched_park_capture: captured the rest.
- Layer: utility
- Language: S
- Symbols:
  - `sched_park_capture` (function, line 70)
  - `switch_save_only` (function, line 82)
  - `switch_to` (function, line 91)
  - `switch_to_notrap` (function, line 134)
  - `user_trampoline` (function, line 221)
  - `fork_trampoline` (function, line 233)
  - `exec_enter` (function, line 249)
  - `resume_iretq` (function, line 278)
  - `k_run_on_stack` (function, line 318)

## arch/x86/isr_stubs.S
- Layer: testing
- Language: S
- Symbols:
  - `tf_rax` (function, line 67)
  - `tf_rbx` (function, line 68)
  - `tf_rcx` (function, line 69)
  - `tf_rdx` (function, line 70)
  - `tf_rsi` (function, line 71)
  - `tf_rdi` (function, line 72)
  - `tf_rbp` (function, line 73)
  - `tf_r8` (function, line 74)
  - `tf_r9` (function, line 75)
  - `tf_r10` (function, line 76)
  - `tf_r11` (function, line 77)
  - `tf_r12` (function, line 78)
  - `tf_r13` (function, line 79)
  - `tf_r14` (function, line 80)
  - `tf_r15` (function, line 81)
  - `tf_rip` (function, line 82)
  - `tf_cs` (function, line 83)
  - `tf_rflags` (function, line 84)
  - `tf_rsp` (function, line 85)
  - `tf_ss` (function, line 86)
  - `tf_vector` (function, line 87)
  - `tf_errcode` (function, line 88)
  - `isr_common` (function, line 96)
  - `isr_stub_table` (function, line 195)

## arch/x86/syscall_entry.S
- Layer: utility
- Language: S
- Symbols:
  - `syscall_kstack` (function, line 49)
  - `kstack_base` (function, line 52)
  - `sc_top_save_addr` (function, line 55)
  - `syscall_entry` (function, line 65)
- Depends on: `headers/syscall_asm.h`
