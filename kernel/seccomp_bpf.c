/** Docstring: seccomp_bpf.c -- classic BPF checker and interpreter for Linux
 * seccomp filters. Contract in headers/seccomp_bpf.h and docs/spec/kernel.md.
 * Freestanding: no libc, no kernel state; the same object links into the
 * kernel and into the host test.
 */
#include "seccomp_bpf.h"

#define SBPF_OP_MASK   0xf0u
#define SBPF_SRC_MASK  0x08u
#define SBPF_SIZE_MASK 0x18u
#define SBPF_MODE_MASK 0xe0u
#define SBPF_RVAL_MASK 0x18u
#define SBPF_MISC_MASK 0xf8u
#define SBPF_MEM_ALL   0xffffu

/* Is code one of the classic opcodes Linux accepts in a seccomp filter? */
static int sbpf_opcode_ok(const sbpf_insn *in) {
    unsigned code = in->code;
    switch (SBPF_CLASS(code)) {
    case SBPF_LD:
        if (code == (SBPF_LD | SBPF_W | SBPF_ABS))
            return in->k < SBPF_DATA_SIZE && (in->k % SBPF_WORD) == 0;
        if (code == (SBPF_LD | SBPF_W | SBPF_LEN)) return 1;
        if (code == (SBPF_LD | SBPF_IMM)) return 1;
        if (code == (SBPF_LD | SBPF_MEM)) return in->k < SBPF_MEMWORDS;
        return 0;
    case SBPF_LDX:
        if (code == (SBPF_LDX | SBPF_W | SBPF_LEN)) return 1;
        if (code == (SBPF_LDX | SBPF_IMM)) return 1;
        if (code == (SBPF_LDX | SBPF_MEM)) return in->k < SBPF_MEMWORDS;
        return 0;
    case SBPF_ST:
    case SBPF_STX:
        return (code & ~0x07u) == 0 && in->k < SBPF_MEMWORDS;
    case SBPF_ALU:
        if ((code & ~(SBPF_OP_MASK | SBPF_SRC_MASK | 0x07u)) != 0) return 0;
        switch (code & SBPF_OP_MASK) {
        case SBPF_ADD: case SBPF_SUB: case SBPF_MUL: case SBPF_OR:
        case SBPF_AND: case SBPF_XOR:
            return 1;
        case SBPF_DIV: case SBPF_MOD:
            return (code & SBPF_SRC_MASK) == SBPF_X || in->k != 0;
        case SBPF_LSH: case SBPF_RSH:
            return (code & SBPF_SRC_MASK) == SBPF_X || in->k < SBPF_SHIFT_MAX;
        case SBPF_NEG:
            return (code & SBPF_SRC_MASK) == SBPF_K;
        default:
            return 0;
        }
    case SBPF_JMP:
        if ((code & ~(SBPF_OP_MASK | SBPF_SRC_MASK | 0x07u)) != 0) return 0;
        switch (code & SBPF_OP_MASK) {
        case SBPF_JA:
            return (code & SBPF_SRC_MASK) == SBPF_K;
        case SBPF_JEQ: case SBPF_JGT: case SBPF_JGE: case SBPF_JSET:
            return 1;
        default:
            return 0;
        }
    case SBPF_RET:
        return code == (SBPF_RET | SBPF_K) || code == (SBPF_RET | SBPF_A);
    case SBPF_MISC:
        return code == (SBPF_MISC | SBPF_TAX) || code == (SBPF_MISC | SBPF_TXA);
    default:
        return 0;
    }
}

int sbpf_check(const sbpf_insn *prog, unsigned len, unsigned short *scratch) {
    unsigned pc;
    unsigned memvalid = 0;
    if (!prog || !scratch || len == 0 || len > SBPF_MAX_INSNS) return SBPF_ERR_INVALID;
    for (pc = 0; pc < len; pc++) {
        const sbpf_insn *in = &prog[pc];
        if (!sbpf_opcode_ok(in)) return SBPF_ERR_INVALID;
        if (SBPF_CLASS(in->code) == SBPF_JMP) {
            unsigned room = len - pc - 1u;
            if ((in->code & SBPF_OP_MASK) == SBPF_JA) {
                if (in->k >= room) return SBPF_ERR_INVALID;
            } else if (in->jt >= room || in->jf >= room) {
                return SBPF_ERR_INVALID;
            }
        }
    }
    if (SBPF_CLASS(prog[len - 1].code) != SBPF_RET) return SBPF_ERR_INVALID;

    /* Scratch-initialization flow (Linux check_load_and_stores): every
     * path into a scratch load must have stored that word first. */
    for (pc = 0; pc < len; pc++) scratch[pc] = (unsigned short)SBPF_MEM_ALL;
    for (pc = 0; pc < len; pc++) {
        const sbpf_insn *in = &prog[pc];
        unsigned cls = SBPF_CLASS(in->code);
        memvalid &= scratch[pc];
        if (cls == SBPF_ST || cls == SBPF_STX) {
            memvalid |= 1u << in->k;
        } else if (in->code == (SBPF_LD | SBPF_MEM) || in->code == (SBPF_LDX | SBPF_MEM)) {
            if (!(memvalid & (1u << in->k))) return SBPF_ERR_INVALID;
        } else if (cls == SBPF_JMP) {
            if ((in->code & SBPF_OP_MASK) == SBPF_JA) {
                scratch[pc + 1u + in->k] &= (unsigned short)memvalid;
            } else {
                scratch[pc + 1u + in->jt] &= (unsigned short)memvalid;
                scratch[pc + 1u + in->jf] &= (unsigned short)memvalid;
            }
            memvalid = SBPF_MEM_ALL;
        } else if (cls == SBPF_RET) {
            memvalid = SBPF_MEM_ALL;
        }
    }
    return 0;
}

/* 32-bit word of seccomp_data at a checked, aligned offset. */
static unsigned int sbpf_load_word(const sbpf_data *d, unsigned off) {
    const unsigned char *b = (const unsigned char *)d + off;
    return (unsigned int)b[0] | ((unsigned int)b[1] << 8) |
           ((unsigned int)b[2] << 16) | ((unsigned int)b[3] << 24);
}

unsigned int sbpf_run(const sbpf_insn *prog, unsigned len, const sbpf_data *d) {
    unsigned int a = 0, x = 0;
    unsigned int mem[SBPF_MEMWORDS];
    unsigned pc = 0, i;
    for (i = 0; i < SBPF_MEMWORDS; i++) mem[i] = 0;
    if (!prog || !d) return SBPF_RET_KILL_PROCESS;
    while (pc < len) {
        const sbpf_insn *in = &prog[pc];
        unsigned code = in->code;
        unsigned int src = ((code & SBPF_SRC_MASK) == SBPF_X) ? x : in->k;
        pc++;
        switch (SBPF_CLASS(code)) {
        case SBPF_LD:
            if (code == (SBPF_LD | SBPF_W | SBPF_ABS)) a = sbpf_load_word(d, in->k);
            else if (code == (SBPF_LD | SBPF_W | SBPF_LEN)) a = SBPF_DATA_SIZE;
            else if (code == (SBPF_LD | SBPF_IMM)) a = in->k;
            else a = mem[in->k];
            break;
        case SBPF_LDX:
            if (code == (SBPF_LDX | SBPF_W | SBPF_LEN)) x = SBPF_DATA_SIZE;
            else if (code == (SBPF_LDX | SBPF_IMM)) x = in->k;
            else x = mem[in->k];
            break;
        case SBPF_ST:
            mem[in->k] = a;
            break;
        case SBPF_STX:
            mem[in->k] = x;
            break;
        case SBPF_ALU:
            switch (code & SBPF_OP_MASK) {
            case SBPF_ADD: a += src; break;
            case SBPF_SUB: a -= src; break;
            case SBPF_MUL: a *= src; break;
            case SBPF_DIV:
                if (src == 0) return SBPF_RET_KILL_PROCESS;
                a /= src;
                break;
            case SBPF_MOD:
                if (src == 0) return SBPF_RET_KILL_PROCESS;
                a %= src;
                break;
            case SBPF_OR:  a |= src; break;
            case SBPF_AND: a &= src; break;
            case SBPF_XOR: a ^= src; break;
            case SBPF_LSH: a = (src < SBPF_SHIFT_MAX) ? (a << src) : 0; break;
            case SBPF_RSH: a = (src < SBPF_SHIFT_MAX) ? (a >> src) : 0; break;
            case SBPF_NEG: a = 0u - a; break;
            default: return SBPF_RET_KILL_PROCESS;
            }
            break;
        case SBPF_JMP:
            switch (code & SBPF_OP_MASK) {
            case SBPF_JA:   pc += in->k; break;
            case SBPF_JEQ:  pc += (a == src) ? in->jt : in->jf; break;
            case SBPF_JGT:  pc += (a > src) ? in->jt : in->jf; break;
            case SBPF_JGE:  pc += (a >= src) ? in->jt : in->jf; break;
            case SBPF_JSET: pc += (a & src) ? in->jt : in->jf; break;
            default: return SBPF_RET_KILL_PROCESS;
            }
            break;
        case SBPF_RET:
            return (code == (SBPF_RET | SBPF_A)) ? a : in->k;
        case SBPF_MISC:
            if (code == (SBPF_MISC | SBPF_TAX)) x = a;
            else a = x;
            break;
        default:
            return SBPF_RET_KILL_PROCESS;
        }
    }
    return SBPF_RET_KILL_PROCESS;
}

int sbpf_action_rank(unsigned int action) {
    switch (action & SBPF_RET_ACTION_FULL) {
    case SBPF_RET_KILL_PROCESS: return 0;
    case SBPF_RET_KILL_THREAD:  return 1;
    case SBPF_RET_TRAP:         return 2;
    case SBPF_RET_ERRNO:        return 3;
    case SBPF_RET_USER_NOTIF:   return 4;
    case SBPF_RET_TRACE:        return 5;
    case SBPF_RET_LOG:          return 6;
    case SBPF_RET_ALLOW:        return 7;
    default:                    return 0;
    }
}
