# Subsystem: x86

## arch/x86/ap_entry.S
- Layer: utility
- Doc: ap_entry.S - SMP application-processor bootstrap stub.
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

## arch/x86/ctx_sw.S
- Layer: utility
- Language: S
- Symbols:
  - `switch_save_only` (function, line 35)
  - `switch_to` (function, line 44)
  - `switch_to_notrap` (function, line 76)
  - `user_trampoline` (function, line 135)
  - `resume_iretq` (function, line 148)

## arch/x86/hal_io.h
- Layer: utility
- Doc: Docstring: x86 port I/O hardware abstraction contract.
- Language: h
- Symbols:
  - `hal_outb` (function, line 68) `static inline void hal_outb(unsigned short port, unsigned char val)`
  - `hal_inb` (function, line 75) `static inline unsigned char hal_inb(unsigned short port)`
  - `hal_outw` (function, line 81) `static inline void hal_outw(unsigned short port, unsigned short val)`
  - `hal_inw` (function, line 88) `static inline unsigned short hal_inw(unsigned short port)`
  - `hal_lapic_eoi` (function, line 94) `static inline void hal_lapic_eoi(void)`
  - `hal_pic_eoi` (function, line 99) `static inline void hal_pic_eoi(int irq)`
  - `hal_outb` (function, line 109) `static inline void hal_outb(unsigned short port, unsigned char val)`
  - `hal_inb` (function, line 114) `static inline unsigned char hal_inb(unsigned short port)`
  - `hal_outw` (function, line 121) `static inline void hal_outw(unsigned short port, unsigned short val)`
  - `hal_inw` (function, line 126) `static inline unsigned short hal_inw(unsigned short port)`
  - `hal_lapic_eoi` (function, line 133) `static inline void hal_lapic_eoi(void)`
  - `hal_pic_eoi` (function, line 138) `static inline void hal_pic_eoi(int irq)`
  - `HAL_IO_H` (macro, line 13)
  - `HAL_PIC1_CMD` (macro, line 16)
  - `HAL_PIC1_DATA` (macro, line 18)
  - `HAL_PIC2_CMD` (macro, line 20)
  - `HAL_PIC2_DATA` (macro, line 22)
  - `HAL_PIC_EOI` (macro, line 24)
  - `HAL_PIT_CMD` (macro, line 27)
  - `HAL_PIT_CH0` (macro, line 29)
  - `HAL_PS2_STATUS` (macro, line 32)
  - `HAL_PS2_DATA` (macro, line 34)
  - `HAL_PS2_MOUSE_OBF` (macro, line 36)
  - `HAL_PS2_IBF_EMPTY` (macro, line 38)
  - `HAL_PS2_OBF_FULL` (macro, line 40)
  - `HAL_MOUSE_SYNC_BIT` (macro, line 43)
  - `HAL_MOUSE_BUTTON_MASK` (macro, line 45)
  - `HAL_MOUSE_PACKET_LEN` (macro, line 47)
  - `HAL_MOUSE_SCALE` (macro, line 49)
  - `HAL_LAPIC_EOI_ADDR` (macro, line 52)

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
  - `MSR_KERNEL_GS_BASE` (macro, line 24)
