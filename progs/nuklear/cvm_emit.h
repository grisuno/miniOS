#ifndef CVM_EMIT_H
#define CVM_EMIT_H

/* cvm_emit.h — node-graph compiler for CVM (cvm2 module format v2).
 *
 * A node graph (constants, arithmetic, bitwise, comparisons, a conditional
 * select, and string constants feeding PRINT/PRINTS/EXIT sinks) is compiled
 * into a self-contained .cvm module: a single entry function whose bytecode
 * computes every node value into a local slot and prints/exits at the output
 * nodes. The emitted module is loadable by the CVM interpreter
 * (objects/cvm.o) exactly like one produced by `ld -f cvm`, so `run` can
 * execute it. Output uses the `printf`/`puts` natives (registered by
 * cvm_host.c); exit codes come from the operand stack via OP_HALT.
 */

#include <stddef.h>

/* String payload bound for STR constants and PRINT formats. */
#define CVM_NODE_STR_MAX 128

/* Node types the graph compiler understands. */
enum cvm_node_type {
    NODE_NUM,    /* constant, value in .ival */
    NODE_STR,    /* string constant, bytes in .sval (NUL-terminated) */
    NODE_ADD,
    NODE_SUB,
    NODE_MUL,
    NODE_DIV,
    NODE_MOD,
    NODE_NEG,    /* one input: in[0] */
    NODE_AND,
    NODE_OR,
    NODE_XOR,
    NODE_NOT,    /* one input: in[0] */
    NODE_SHL,
    NODE_SHR,
    NODE_EQ,
    NODE_NE,
    NODE_LT,
    NODE_LE,
    NODE_GT,
    NODE_GE,
    NODE_LNOT,   /* one input: in[0] */
    NODE_IF,     /* three inputs: cond, then, else */
    NODE_PRINT,  /* one input + format in .sval (default "%d\n") */
    NODE_PRINTS, /* one input: string address (STR node or literal?) */
    NODE_EXIT,   /* one input: exit code */
    NODE_COUNT
};

/* One node in the graph. Inputs are indices of other nodes; a negative input
 * means open, in which case the per-input literal is used when use_lit[k] is
 * set, otherwise compilation fails with a node-context diagnostic. Output
 * nodes (PRINT/PRINTS/EXIT) terminate the compiled program and can never be
 * used as an input source. */
struct cvm_node {
    enum cvm_node_type type;
    long long ival;                      /* NODE_NUM constant */
    char sval[CVM_NODE_STR_MAX];         /* NODE_STR bytes / NODE_PRINT fmt */
    int in[3];                           /* input node indices, -1 when open */
    long long lit[3];                    /* fallback literal per input */
    int use_lit[3];                      /* nonzero: use lit[k] when open */
};

/* Compile a node graph into a .cvm module. Returns 0 on success (module in
 * out and out_size, caller frees); on failure returns -1 with a message in
 * err (err_cap bytes). The module is heap-allocated and owned by the caller
 * (free it). */
int cvm_compile(const struct cvm_node *nodes, int n,
                unsigned char **out, size_t *out_size,
                char *err, size_t err_cap);

#endif
