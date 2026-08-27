#ifndef CVM_EMIT_H
#define CVM_EMIT_H

/* cvm_emit.h — node-graph compiler for CVM (cvm2 module format v2).
 *
 * A node graph (constants and arithmetic operations feeding output nodes) is
 * compiled into a self-contained .cvm module: a single entry function whose
 * bytecode computes every node value into a local slot and prints/exits at
 * the output nodes. The emitted module is loadable by the CVM interpreter
 * (objects/cvm.o) exactly like one produced by `ld -f cvm`, so `run` can
 * execute it. Output uses the `printf` native (registered by cvm_host.c);
 * exit codes come from the operand stack via OP_HALT.
 */

/* Node types the graph compiler understands. */
enum cvm_node_type {
    NODE_NUM,   /* constant, value in .ival */
    NODE_ADD,
    NODE_SUB,
    NODE_MUL,
    NODE_DIV,
    NODE_NEG,
    NODE_PRINT, /* writes the value to stdout via printf */
    NODE_EXIT,  /* halts with the value as exit code */
};

/* One node in the graph. Inputs are indices of other nodes; output nodes
 * (PRINT/EXIT) terminate the compiled program. */
struct cvm_node {
    enum cvm_node_type type;
    long long ival;       /* NODE_NUM constant */
    int in[2];            /* input node indices, -1 when unset */
};

/* Compile a node graph into a .cvm module. Returns the module size (>=0) or
 * a negative CVM-style error; on failure writes a message into err (err_cap
 * bytes). The module is heap-allocated and owned by the caller (free it). */
int cvm_compile(const struct cvm_node *nodes, int n,
                unsigned char **out, size_t *out_size,
                char *err, size_t err_cap);

#endif