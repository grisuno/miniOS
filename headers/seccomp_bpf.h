/** Docstring: seccomp_bpf.h -- classic BPF checker and interpreter for
 * Linux seccomp filters (docs/spec/kernel.md, "Linux seccomp-bpf, prctl and
 * /proc/self/exe").
 *
 * Pure: no kernel state, no allocation, so tests/test_seccomp_bpf.c (make
 * test-seccomp-bpf) drives it on the host. The kernel copies a user
 * sock_fprog, runs sbpf_check once at install time and sbpf_run on every
 * syscall of a filtered process. The instruction and data layouts are the
 * Linux ABI ones (struct sock_filter, struct seccomp_data).
 */
#ifndef SECCOMP_BPF_H
#define SECCOMP_BPF_H

/* struct sock_filter: 8 bytes. */
typedef struct {
    unsigned short code;
    unsigned char  jt;
    unsigned char  jf;
    unsigned int   k;
} sbpf_insn;

/* struct seccomp_data: 64 bytes. */
typedef struct {
    int                nr;
    unsigned int       arch;
    unsigned long long instruction_pointer;
    unsigned long long args[6];
} sbpf_data;

#define SBPF_MAX_INSNS 4096u
#define SBPF_DATA_SIZE 64u
#define SBPF_MEMWORDS  16u
#define SBPF_WORD      4u
#define SBPF_SHIFT_MAX 32u
#define SBPF_ERR_INVALID (-1)

/* Seccomp return actions (high 16 bits) and the data mask. */
#define SBPF_RET_KILL_PROCESS 0x80000000u
#define SBPF_RET_KILL_THREAD  0x00000000u
#define SBPF_RET_TRAP         0x00030000u
#define SBPF_RET_ERRNO        0x00050000u
#define SBPF_RET_USER_NOTIF   0x7fc00000u
#define SBPF_RET_TRACE        0x7ff00000u
#define SBPF_RET_LOG          0x7ffc0000u
#define SBPF_RET_ALLOW        0x7fff0000u
#define SBPF_RET_ACTION_FULL  0xffff0000u
#define SBPF_RET_DATA         0x0000ffffu

#define SBPF_AUDIT_ARCH_X86_64 0xC000003Eu

/* Classic BPF opcode fields. */
#define SBPF_CLASS(c) ((c) & 0x07u)
#define SBPF_LD   0x00u
#define SBPF_LDX  0x01u
#define SBPF_ST   0x02u
#define SBPF_STX  0x03u
#define SBPF_ALU  0x04u
#define SBPF_JMP  0x05u
#define SBPF_RET  0x06u
#define SBPF_MISC 0x07u
#define SBPF_W    0x00u
#define SBPF_IMM  0x00u
#define SBPF_ABS  0x20u
#define SBPF_MEM  0x60u
#define SBPF_LEN  0x80u
#define SBPF_ADD  0x00u
#define SBPF_SUB  0x10u
#define SBPF_MUL  0x20u
#define SBPF_DIV  0x30u
#define SBPF_OR   0x40u
#define SBPF_AND  0x50u
#define SBPF_LSH  0x60u
#define SBPF_RSH  0x70u
#define SBPF_NEG  0x80u
#define SBPF_MOD  0x90u
#define SBPF_XOR  0xa0u
#define SBPF_JA   0x00u
#define SBPF_JEQ  0x10u
#define SBPF_JGT  0x20u
#define SBPF_JGE  0x30u
#define SBPF_JSET 0x40u
#define SBPF_K    0x00u
#define SBPF_X    0x08u
#define SBPF_A    0x10u
#define SBPF_TAX  0x00u
#define SBPF_TXA  0x80u

/* Validate a program before it ever runs: 1..SBPF_MAX_INSNS instructions,
 * only the opcodes Linux accepts for seccomp, word loads inside
 * seccomp_data at aligned offsets, scratch indices below SBPF_MEMWORDS,
 * no constant zero divisor or modulus, constant shifts below 32, every
 * jump landing inside the program, no scratch word read before every path
 * wrote it, and a RET last. scratch must hold len entries (the per-pc
 * initialized-scratch masks). 0 when valid, SBPF_ERR_INVALID otherwise. */
int sbpf_check(const sbpf_insn *prog, unsigned len, unsigned short *scratch);

/* Run a program sbpf_check accepted over one syscall's data; returns the
 * 32-bit action. A runtime division or modulus by a zero X returns
 * SBPF_RET_KILL_PROCESS. */
unsigned int sbpf_run(const sbpf_insn *prog, unsigned len, const sbpf_data *d);

/* Restrictiveness rank of an action (0 = most restrictive): the order
 * stacked filters are combined in. Unknown actions rank as KILL_PROCESS. */
int sbpf_action_rank(unsigned int action);

#endif
