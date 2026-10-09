/** Docstring: Host test for kernel/seccomp_bpf.c (make test-seccomp-bpf).
 *
 * Builds the exact filter shape FreeDom's tab worker installs (arch guard,
 * allowlist, W^X check on mmap/mprotect prot) and checks every verdict, then
 * covers the checker's refusals (length, opcodes, alignment, bounds, jumps,
 * zero divisors, shifts, uninitialized scratch, last RET) and the
 * interpreter's arithmetic, jumps, scratch memory and fail-closed division.
 */
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "seccomp_bpf.h"

static int failures;

#define CHECK(cond, msg) do { \
    if (!(cond)) { printf("FAIL: %s\n", msg); failures++; } \
} while (0)

#define STMT(c, k)        ((sbpf_insn){ (unsigned short)(c), 0, 0, (unsigned int)(k) })
#define JUMP(c, k, t, f)  ((sbpf_insn){ (unsigned short)(c), (unsigned char)(t), (unsigned char)(f), (unsigned int)(k) })

#define NR_READ     0
#define NR_WRITE    1
#define NR_OPEN     2
#define NR_MMAP     9
#define NR_MPROTECT 10
#define PROT_EXEC   4
#define ARGS2_OFF   (offsetof(sbpf_data, args) + 2 * sizeof(unsigned long long))

static unsigned short scratch[SBPF_MAX_INSNS];

static sbpf_data data_for(int nr, unsigned long long a2) {
    sbpf_data d;
    memset(&d, 0, sizeof d);
    d.nr = nr;
    d.arch = SBPF_AUDIT_ARCH_X86_64;
    d.args[2] = a2;
    return d;
}

static void test_freedom_shape(void) {
    sbpf_insn p[16];
    unsigned n = 0, at_mmap, at_mprot, prot;
    unsigned deny = SBPF_RET_ERRNO | 1u;
    sbpf_data d;
    p[n++] = STMT(SBPF_LD | SBPF_W | SBPF_ABS, offsetof(sbpf_data, arch));
    p[n++] = JUMP(SBPF_JMP | SBPF_JEQ | SBPF_K, SBPF_AUDIT_ARCH_X86_64, 1, 0);
    p[n++] = STMT(SBPF_RET | SBPF_K, SBPF_RET_KILL_PROCESS);
    p[n++] = STMT(SBPF_LD | SBPF_W | SBPF_ABS, offsetof(sbpf_data, nr));
    at_mmap = n;
    p[n++] = JUMP(SBPF_JMP | SBPF_JEQ | SBPF_K, NR_MMAP, 0, 0);
    at_mprot = n;
    p[n++] = JUMP(SBPF_JMP | SBPF_JEQ | SBPF_K, NR_MPROTECT, 0, 0);
    p[n++] = JUMP(SBPF_JMP | SBPF_JEQ | SBPF_K, NR_READ, 0, 1);
    p[n++] = STMT(SBPF_RET | SBPF_K, SBPF_RET_ALLOW);
    p[n++] = JUMP(SBPF_JMP | SBPF_JEQ | SBPF_K, NR_WRITE, 0, 1);
    p[n++] = STMT(SBPF_RET | SBPF_K, SBPF_RET_ALLOW);
    p[n++] = STMT(SBPF_RET | SBPF_K, deny);
    prot = n;
    p[n++] = STMT(SBPF_LD | SBPF_W | SBPF_ABS, ARGS2_OFF);
    p[n++] = STMT(SBPF_ALU | SBPF_AND | SBPF_K, PROT_EXEC);
    p[n++] = JUMP(SBPF_JMP | SBPF_JEQ | SBPF_K, 0, 1, 0);
    p[n++] = STMT(SBPF_RET | SBPF_K, deny);
    p[n++] = STMT(SBPF_RET | SBPF_K, SBPF_RET_ALLOW);
    p[at_mmap].jt = (unsigned char)(prot - (at_mmap + 1));
    p[at_mprot].jt = (unsigned char)(prot - (at_mprot + 1));

    CHECK(sbpf_check(p, n, scratch) == 0, "freedom filter accepted");
    d = data_for(NR_READ, 0);
    CHECK(sbpf_run(p, n, &d) == SBPF_RET_ALLOW, "read allowed");
    d = data_for(NR_WRITE, 0);
    CHECK(sbpf_run(p, n, &d) == SBPF_RET_ALLOW, "write allowed");
    d = data_for(NR_OPEN, 0);
    CHECK(sbpf_run(p, n, &d) == deny, "open denied");
    d = data_for(NR_MMAP, 3);
    CHECK(sbpf_run(p, n, &d) == SBPF_RET_ALLOW, "mmap rw allowed");
    d = data_for(NR_MMAP, 3 | PROT_EXEC);
    CHECK(sbpf_run(p, n, &d) == deny, "mmap exec denied");
    d = data_for(NR_MPROTECT, PROT_EXEC);
    CHECK(sbpf_run(p, n, &d) == deny, "mprotect exec denied");
    d = data_for(NR_READ, 0);
    d.arch = 0x40000003u;
    CHECK(sbpf_run(p, n, &d) == SBPF_RET_KILL_PROCESS, "foreign arch killed");
}

static void test_check_refusals(void) {
    sbpf_insn ok[1] = { STMT(SBPF_RET | SBPF_K, SBPF_RET_ALLOW) };
    sbpf_insn p[4];
    CHECK(sbpf_check(ok, 1, scratch) == 0, "single RET accepted");
    CHECK(sbpf_check(ok, 0, scratch) == SBPF_ERR_INVALID, "empty refused");
    CHECK(sbpf_check(ok, SBPF_MAX_INSNS + 1, scratch) == SBPF_ERR_INVALID, "too long refused");
    CHECK(sbpf_check(NULL, 1, scratch) == SBPF_ERR_INVALID, "null program refused");
    CHECK(sbpf_check(ok, 1, NULL) == SBPF_ERR_INVALID, "null scratch refused");

    p[0] = STMT(SBPF_LD | SBPF_W | SBPF_ABS, 2);
    p[1] = STMT(SBPF_RET | SBPF_A, 0);
    CHECK(sbpf_check(p, 2, scratch) == SBPF_ERR_INVALID, "misaligned load refused");
    p[0] = STMT(SBPF_LD | SBPF_W | SBPF_ABS, SBPF_DATA_SIZE);
    CHECK(sbpf_check(p, 2, scratch) == SBPF_ERR_INVALID, "load past data refused");
    p[0] = STMT(SBPF_LD | 0x08u | SBPF_ABS, 0);
    CHECK(sbpf_check(p, 2, scratch) == SBPF_ERR_INVALID, "half-word load refused");
    p[0] = STMT(SBPF_LD | SBPF_W | 0x40u, 0);
    CHECK(sbpf_check(p, 2, scratch) == SBPF_ERR_INVALID, "indirect load refused");
    p[0] = STMT(SBPF_ALU | SBPF_DIV | SBPF_K, 0);
    CHECK(sbpf_check(p, 2, scratch) == SBPF_ERR_INVALID, "constant divide by zero refused");
    p[0] = STMT(SBPF_ALU | SBPF_MOD | SBPF_K, 0);
    CHECK(sbpf_check(p, 2, scratch) == SBPF_ERR_INVALID, "constant modulus zero refused");
    p[0] = STMT(SBPF_ALU | SBPF_LSH | SBPF_K, SBPF_SHIFT_MAX);
    CHECK(sbpf_check(p, 2, scratch) == SBPF_ERR_INVALID, "shift of 32 refused");
    p[0] = STMT(SBPF_ST, SBPF_MEMWORDS);
    CHECK(sbpf_check(p, 2, scratch) == SBPF_ERR_INVALID, "scratch index past 15 refused");
    p[0] = STMT(SBPF_LD | SBPF_MEM, 3);
    CHECK(sbpf_check(p, 2, scratch) == SBPF_ERR_INVALID, "uninitialized scratch read refused");
    p[0] = JUMP(SBPF_JMP | SBPF_JEQ | SBPF_K, 0, 5, 0);
    CHECK(sbpf_check(p, 2, scratch) == SBPF_ERR_INVALID, "jump past end refused");
    p[0] = STMT(SBPF_JMP | SBPF_JA, 1);
    CHECK(sbpf_check(p, 2, scratch) == SBPF_ERR_INVALID, "JA past end refused");
    p[0] = STMT(SBPF_LD | SBPF_IMM, 1);
    p[1] = STMT(SBPF_ALU | SBPF_ADD | SBPF_K, 1);
    CHECK(sbpf_check(p, 2, scratch) == SBPF_ERR_INVALID, "missing final RET refused");
    p[0] = STMT(0x07u | 0x40u, 0);
    p[1] = STMT(SBPF_RET | SBPF_A, 0);
    CHECK(sbpf_check(p, 2, scratch) == SBPF_ERR_INVALID, "unknown misc refused");
    p[0] = STMT(SBPF_RET | SBPF_X, 0);
    CHECK(sbpf_check(p, 1, scratch) == SBPF_ERR_INVALID, "RET X refused");
}

static void test_scratch_flow(void) {
    sbpf_insn p[6];
    sbpf_data d = data_for(NR_READ, 0);
    /* Written on one branch only: the read after the join is refused. */
    p[0] = JUMP(SBPF_JMP | SBPF_JEQ | SBPF_K, 0, 0, 1);
    p[1] = STMT(SBPF_ST, 2);
    p[2] = STMT(SBPF_LD | SBPF_MEM, 2);
    p[3] = STMT(SBPF_RET | SBPF_A, 0);
    CHECK(sbpf_check(p, 4, scratch) == SBPF_ERR_INVALID, "one-branch store refused");
    /* Written before the branch: accepted and read back. */
    p[0] = STMT(SBPF_LD | SBPF_IMM, 0x1234);
    p[1] = STMT(SBPF_ST, 2);
    p[2] = STMT(SBPF_LD | SBPF_IMM, 0);
    p[3] = STMT(SBPF_LDX | SBPF_MEM, 2);
    p[4] = STMT(SBPF_MISC | SBPF_TXA, 0);
    p[5] = STMT(SBPF_RET | SBPF_A, 0);
    CHECK(sbpf_check(p, 6, scratch) == 0, "store-then-load accepted");
    CHECK(sbpf_run(p, 6, &d) == 0x1234u, "scratch round trip");
}

static void test_alu_and_jumps(void) {
    sbpf_insn p[16];
    sbpf_data d = data_for(7, 0);
    unsigned n = 0;
    p[n++] = STMT(SBPF_LD | SBPF_W | SBPF_ABS, offsetof(sbpf_data, nr));
    p[n++] = STMT(SBPF_ALU | SBPF_MUL | SBPF_K, 6);
    p[n++] = STMT(SBPF_ALU | SBPF_SUB | SBPF_K, 2);
    p[n++] = STMT(SBPF_ALU | SBPF_LSH | SBPF_K, 1);
    p[n++] = STMT(SBPF_ALU | SBPF_XOR | SBPF_K, 0xf);
    p[n++] = STMT(SBPF_MISC | SBPF_TAX, 0);
    p[n++] = STMT(SBPF_LD | SBPF_IMM, 1000);
    p[n++] = STMT(SBPF_ALU | SBPF_MOD | SBPF_X, 0);
    p[n++] = JUMP(SBPF_JMP | SBPF_JGT | SBPF_K, 20, 1, 0);
    p[n++] = STMT(SBPF_RET | SBPF_K, 1);
    p[n++] = JUMP(SBPF_JMP | SBPF_JSET | SBPF_K, 0x2, 0, 1);
    p[n++] = STMT(SBPF_RET | SBPF_A, 0);
    CHECK(sbpf_check(p, n, scratch) == SBPF_ERR_INVALID, "fallthrough past last RET refused");
    p[n++] = STMT(SBPF_RET | SBPF_K, 2);
    CHECK(sbpf_check(p, n, scratch) == 0, "alu program accepted");
    /* ((7*6-2)<<1)^0xf = 80^15 = 95; 1000 % 95 = 50; 50 > 20; 50 & 2 -> RET A. */
    CHECK(sbpf_run(p, n, &d) == 50u, "alu result");

    p[0] = STMT(SBPF_LDX | SBPF_IMM, 0);
    p[1] = STMT(SBPF_LD | SBPF_IMM, 9);
    p[2] = STMT(SBPF_ALU | SBPF_DIV | SBPF_X, 0);
    p[3] = STMT(SBPF_RET | SBPF_A, 0);
    CHECK(sbpf_check(p, 4, scratch) == 0, "divide by X accepted");
    CHECK(sbpf_run(p, 4, &d) == SBPF_RET_KILL_PROCESS, "runtime divide by zero kills");

    p[0] = STMT(SBPF_LD | SBPF_W | SBPF_LEN, 0);
    p[1] = STMT(SBPF_RET | SBPF_A, 0);
    CHECK(sbpf_check(p, 2, scratch) == 0 && sbpf_run(p, 2, &d) == SBPF_DATA_SIZE, "LEN is 64");

    p[0] = STMT(SBPF_LD | SBPF_IMM, 5);
    p[1] = STMT(SBPF_ALU | SBPF_NEG, 0);
    p[2] = STMT(SBPF_RET | SBPF_A, 0);
    CHECK(sbpf_check(p, 3, scratch) == 0 && sbpf_run(p, 3, &d) == 0xfffffffbu, "NEG");

    p[0] = STMT(SBPF_JMP | SBPF_JA, 1);
    p[1] = STMT(SBPF_RET | SBPF_K, 1);
    p[2] = STMT(SBPF_RET | SBPF_K, 2);
    CHECK(sbpf_check(p, 3, scratch) == 0 && sbpf_run(p, 3, &d) == 2u, "JA skips");

    d.args[2] = 0x1122334455667788ULL;
    p[0] = STMT(SBPF_LD | SBPF_W | SBPF_ABS, ARGS2_OFF + SBPF_WORD);
    p[1] = STMT(SBPF_RET | SBPF_A, 0);
    CHECK(sbpf_check(p, 2, scratch) == 0 && sbpf_run(p, 2, &d) == 0x11223344u, "high arg word");
}

static void test_action_rank(void) {
    CHECK(sbpf_action_rank(SBPF_RET_KILL_PROCESS) < sbpf_action_rank(SBPF_RET_KILL_THREAD), "kill process first");
    CHECK(sbpf_action_rank(SBPF_RET_KILL_THREAD) < sbpf_action_rank(SBPF_RET_TRAP), "kill thread before trap");
    CHECK(sbpf_action_rank(SBPF_RET_TRAP) < sbpf_action_rank(SBPF_RET_ERRNO | 5u), "trap before errno");
    CHECK(sbpf_action_rank(SBPF_RET_ERRNO) < sbpf_action_rank(SBPF_RET_USER_NOTIF), "errno before notif");
    CHECK(sbpf_action_rank(SBPF_RET_USER_NOTIF) < sbpf_action_rank(SBPF_RET_TRACE), "notif before trace");
    CHECK(sbpf_action_rank(SBPF_RET_TRACE) < sbpf_action_rank(SBPF_RET_LOG), "trace before log");
    CHECK(sbpf_action_rank(SBPF_RET_LOG) < sbpf_action_rank(SBPF_RET_ALLOW), "log before allow");
    CHECK(sbpf_action_rank(0x12340000u) == sbpf_action_rank(SBPF_RET_KILL_PROCESS), "unknown ranks as kill");
}

int main(void) {
    test_freedom_shape();
    test_check_refusals();
    test_scratch_flow();
    test_alu_and_jumps();
    test_action_rank();
    if (failures == 0)
        printf("seccomp_bpf: ok\n");
    else
        printf("seccomp_bpf: %d failures\n", failures);
    return failures != 0;
}
