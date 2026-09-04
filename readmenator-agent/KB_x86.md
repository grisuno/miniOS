# Subsystem: x86

## arch/x86/ap_entry.S
- Layer: utility
- Doc: ap_entry.S - SMP application-processor bootstrap stub.
- Language: S
- Symbols:
  - `ap_stub_start` (function, line 21)
  - `ap_pm` (function, line 39)
  - `ap_lm` (function, line 62)
  - `ap_patch_slot` (function, line 77)
  - `ap_gdt32` (function, line 81)
  - `ap_gdt32_ptr` (function, line 85)
  - `ap_gdt32_end` (function, line 88)
  - `ap_gdt64_ptr` (function, line 90)
  - `ap_stub_end` (function, line 95)

## arch/x86/ctx_sw.S
- Layer: utility
- Language: S
- Symbols:
  - `switch_to_next` (function, line 21)
  - `switch_to` (function, line 26)
  - `user_trampoline` (function, line 103)

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
  - `isr_stub_table` (function, line 181)

## arch/x86/msr.h
- Layer: utility
- Doc: ifndef ARCH_X86_MSR_H define ARCH_X86_MSR_H  Model-Specific Register access for x86-64.
- Language: h
- Symbols:
  - `wrmsr` (function, line 7) `static inline void wrmsr(unsigned msr, unsigned long val)`
  - `rdmsr` (function, line 12) `static inline unsigned long rdmsr(unsigned msr)`
  - `ARCH_X86_MSR_H` (macro, line 2)
  - `MSR_STAR` (macro, line 18)
  - `MSR_LSTAR` (macro, line 20)
  - `MSR_SFMASK` (macro, line 21)
  - `MSR_FSBASE` (macro, line 22)
  - `MSR_GSBASE` (macro, line 23)
