# arch/x86

*Community 1 | 2 files | cohesion 0.50*

## Definition

This community groups 2 file(s) rooted at `arch/x86` with dominant language S (cohesion 0.50). Central symbols: `SYSCALL_ASM_H`, `SYSCALL_CPU_CUR_PID_OFF`, `SYSCALL_CPU_SC_N_OFF`, `SYSCALL_CPU_SC_PID_OFF`, `SYSCALL_CPU_SC_RET_OFF`, `SYSCALL_CPU_SC_RIP_OFF`, `SYSCALL_CPU_SC_TMP_OFF`, `SYSCALL_MAX_PROCS`. Core file: `headers/syscall_asm.h` (12 symbols). Documented purpose: numeric contract for arch/x86/syscall_entry.S..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `arch/x86/syscall_entry.S` | S | utility | 4 | no |
| `headers/syscall_asm.h` | h | utility | 12 | yes |

## Key Symbols

- `syscall_kstack` (function, `arch/x86/syscall_entry.S:49`)
- `kstack_base` (function, `arch/x86/syscall_entry.S:52`)
- `sc_top_save_addr` (function, `arch/x86/syscall_entry.S:55`)
- `syscall_entry` (function, `arch/x86/syscall_entry.S:65`)
- `SYSCALL_ASM_H` (macro, `headers/syscall_asm.h:2`) `#define SYSCALL_ASM_H`
- `SYSCALL_USER_WIN_LO` (macro, `headers/syscall_asm.h:15`) `#define SYSCALL_USER_WIN_LO`
- `SYSCALL_USER_WIN_HI` (macro, `headers/syscall_asm.h:16`) `#define SYSCALL_USER_WIN_HI`
- `SYSCALL_PROC_T_SIZE` (macro, `headers/syscall_asm.h:17`) `#define SYSCALL_PROC_T_SIZE`
- `SYSCALL_PROC_KSTACK_OFF` (macro, `headers/syscall_asm.h:18`) `#define SYSCALL_PROC_KSTACK_OFF`
- `SYSCALL_MAX_PROCS` (macro, `headers/syscall_asm.h:19`) `#define SYSCALL_MAX_PROCS`
- `SYSCALL_CPU_CUR_PID_OFF` (macro, `headers/syscall_asm.h:20`) `#define SYSCALL_CPU_CUR_PID_OFF`
- `SYSCALL_CPU_SC_N_OFF` (macro, `headers/syscall_asm.h:21`) `#define SYSCALL_CPU_SC_N_OFF`
- `SYSCALL_CPU_SC_RIP_OFF` (macro, `headers/syscall_asm.h:22`) `#define SYSCALL_CPU_SC_RIP_OFF`
- `SYSCALL_CPU_SC_PID_OFF` (macro, `headers/syscall_asm.h:23`) `#define SYSCALL_CPU_SC_PID_OFF`
- `SYSCALL_CPU_SC_RET_OFF` (macro, `headers/syscall_asm.h:24`) `#define SYSCALL_CPU_SC_RET_OFF`
- `SYSCALL_CPU_SC_TMP_OFF` (macro, `headers/syscall_asm.h:25`) `#define SYSCALL_CPU_SC_TMP_OFF`

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 1
- Cross-boundary resolved imports (EXTRACTED): 1

## Connections

- [EXTRACTED] depends_on community 0 <-> 1 (strength 0.9): Extracted import edge crosses communities: kernel.c imports headers/syscall_asm.h.
- [INFERRED] shares_context community 1 <-> 2 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (arch/x86) and community 2 (progs/doomgeneric).
- [INFERRED] shares_context community 1 <-> 3 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (arch/x86) and community 3 (headers).
- [INFERRED] shares_context community 1 <-> 4 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (arch/x86) and community 4 (tools).
- [INFERRED] shares_context community 1 <-> 5 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (arch/x86) and community 5 (headers).
- [INFERRED] shares_context community 1 <-> 6 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (arch/x86) and community 6 (headers).
- [INFERRED] shares_context community 1 <-> 7 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (arch/x86) and community 7 (progs/doomgeneric).
- [INFERRED] shares_context community 1 <-> 8 (strength 0.5): Inferred shared context (layer utility) with no import path between community 1 (arch/x86) and community 8 (progs/src).

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 1 file(s) lack file-level docs (e.g. `arch/x86/syscall_entry.S`)? What purpose do they serve?
- What would break if the most connected file in arch/x86 changed?
- Should arch/x86 be split, given cohesion 0.50?

## Sources

- `arch/x86/syscall_entry.S`
- `headers/syscall_asm.h`
