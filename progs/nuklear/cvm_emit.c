/* cvm_emit.c — node-graph to CVM bytecode compiler.
 *
 * Emits a cvm2 module (format v2) from a small dataflow graph. Nodes are
 * topologically sorted (a true DAG order, so the editor can connect nodes in
 * any sequence); every node value is computed into a local slot; PRINT nodes
 * call the `printf` native (registered by cvm_host.c) with a "%d\n" format
 * string kept in the module data section, and EXIT nodes halt with the value
 * as the exit code (OP_HALT leaves the operand-stack top as the exit status,
 * which the shell reports as `exit code: N`).
 *
 * Module layout follows cvm_load_module exactly:
 *   header | func table | global table | native table | string table |
 *   code | RLE-compressed data | string pool
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cvm_emit.h"

/* cvm2 constants mirrored here so the emitter needs no cvm headers. */
#define CVM_MAGIC_0 0x43
#define CVM_MAGIC_1 0x56
#define CVM_MAGIC_2 0x4D
#define CVM_MAGIC_3 0x04
#define CVM_VERSION_MAJOR 1
#define CVM_MODULE_HEADER_SIZE 40
#define CVM_FUNC_ENTRY_SIZE 20
#define CVM_GLOBAL_ENTRY_SIZE 8
#define CVM_NATIVE_ENTRY_SIZE 4

/* Opcodes (cvm.h). */
#define OP_PUSH_IMM64  0x01
#define OP_PUSH_IMM32  0x02
#define OP_PUSH_IMM8   0x03
#define OP_PUSH_LOCAL  0x10
#define OP_STORE_LOCAL 0x11
#define OP_ADD         0x20
#define OP_SUB         0x21
#define OP_MUL         0x22
#define OP_DIV         0x23
#define OP_NEG         0x25
#define OP_LEA_DATA    0x82
#define OP_CALL_NATIVE 0x62
#define OP_HALT        0xFF

#define CVM_MAX_NODES 512

struct codebuf {
    unsigned char *b;
    size_t len;
    size_t cap;
};

static int cb_push(struct codebuf *cb, unsigned char c) {
    if (cb->len >= cb->cap) {
        size_t nc = cb->cap ? cb->cap * 2 : 256;
        unsigned char *nb = (unsigned char *)realloc(cb->b, nc);
        if (!nb) return -1;
        cb->b = nb;
        cb->cap = nc;
    }
    cb->b[cb->len++] = c;
    return 0;
}

static int cb_u32(struct codebuf *cb, unsigned long v) {
    for (int i = 0; i < 4; i++)
        if (cb_push(cb, (unsigned char)(v >> (8 * i))) < 0) return -1;
    return 0;
}

static int cb_i64(struct codebuf *cb, long long v) {
    for (int i = 0; i < 8; i++)
        if (cb_push(cb, (unsigned char)(v >> (8 * i))) < 0) return -1;
    return 0;
}

/* ---- topological sort (Kahn, stable) ---- */
static int topo_sort(const struct cvm_node *nodes, int n,
                     int *order, char *err, size_t err_cap) {
    static unsigned char indeg[CVM_MAX_NODES];
    static int queue[CVM_MAX_NODES];
    memset(indeg, 0, (size_t)n);
    int qh = 0, qt = 0;
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < 2; k++) {
            int in = nodes[i].in[k];
            if (in < 0) continue;
            if (in >= n) {
                if (err_cap) snprintf(err, err_cap,
                                      "node %d: input %d out of range", i, in);
                return -1;
            }
            if (nodes[in].type == NODE_PRINT || nodes[in].type == NODE_EXIT) {
                if (err_cap) snprintf(err, err_cap,
                                      "node %d: cannot feed an output node", i);
                return -1;
            }
            indeg[i]++;
        }
    }
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0) queue[qt++] = i;
    int out_n = 0;
    while (qh < qt) {
        int v = queue[qh++];
        order[out_n++] = v;
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < 2; k++) {
                if (nodes[i].in[k] == v && --indeg[i] == 0) queue[qt++] = i;
            }
        }
    }
    if (out_n != n) {
        if (err_cap) snprintf(err, err_cap, "graph contains a cycle");
        return -1;
    }
    return 0;
}

int cvm_compile(const struct cvm_node *nodes, int n,
                unsigned char **out, size_t *out_size,
                char *err, size_t err_cap) {
    if (!nodes || n <= 0) {
        if (err_cap) snprintf(err, err_cap, "empty graph");
        return -1;
    }
    if (n > CVM_MAX_NODES) {
        if (err_cap) snprintf(err, err_cap, "too many nodes");
        return -1;
    }

    static int order[CVM_MAX_NODES];
    static int slot[CVM_MAX_NODES];
    if (topo_sort(nodes, n, order, err, err_cap) < 0) return -1;
    for (int i = 0; i < n; i++) slot[order[i]] = i;

    struct codebuf code = {0};

    /* Pass 1: value nodes (NUM and the arithmetic ops) in topo order. */
    for (int oi = 0; oi < n; oi++) {
        int i = order[oi];
        if (nodes[i].type == NODE_PRINT || nodes[i].type == NODE_EXIT) continue;
        switch (nodes[i].type) {
        case NODE_NUM: {
            long long v = nodes[i].ival;
            if (v >= -128 && v <= 127) {
                if (cb_push(&code, OP_PUSH_IMM8) < 0) goto oom;
                if (cb_push(&code, (unsigned char)(v & 0xFF)) < 0) goto oom;
            } else if (v >= -2147483648LL && v <= 2147483647LL) {
                if (cb_push(&code, OP_PUSH_IMM32) < 0) goto oom;
                if (cb_u32(&code, (unsigned long)(unsigned long long)v) < 0) goto oom;
            } else {
                if (cb_push(&code, OP_PUSH_IMM64) < 0) goto oom;
                if (cb_i64(&code, v) < 0) goto oom;
            }
            if (cb_push(&code, OP_STORE_LOCAL) < 0) goto oom;
            if (cb_u32(&code, (unsigned long)slot[i]) < 0) goto oom;
            break;
        }
        case NODE_ADD: case NODE_SUB: case NODE_MUL: case NODE_DIV: {
            for (int k = 0; k < 2; k++) {
                if (cb_push(&code, OP_PUSH_LOCAL) < 0) goto oom;
                if (cb_u32(&code, (unsigned long)slot[nodes[i].in[k]]) < 0) goto oom;
            }
            int op = (nodes[i].type == NODE_ADD) ? OP_ADD :
                     (nodes[i].type == NODE_SUB) ? OP_SUB :
                     (nodes[i].type == NODE_MUL) ? OP_MUL : OP_DIV;
            if (cb_push(&code, (unsigned char)op) < 0) goto oom;
            if (cb_push(&code, OP_STORE_LOCAL) < 0) goto oom;
            if (cb_u32(&code, (unsigned long)slot[i]) < 0) goto oom;
            break;
        }
        case NODE_NEG: {
            if (cb_push(&code, OP_PUSH_LOCAL) < 0) goto oom;
            if (cb_u32(&code, (unsigned long)slot[nodes[i].in[0]]) < 0) goto oom;
            if (cb_push(&code, OP_NEG) < 0) goto oom;
            if (cb_push(&code, OP_STORE_LOCAL) < 0) goto oom;
            if (cb_u32(&code, (unsigned long)slot[i]) < 0) goto oom;
            break;
        }
        default: break;
        }
    }

    /* Pass 2: PRINT nodes (write to stdout via printf). */
    for (int oi = 0; oi < n; oi++) {
        int i = order[oi];
        if (nodes[i].type != NODE_PRINT) continue;
        /* printf("%d\n", val): args[0]=fmt, args[1]=val, so push fmt first
         * then val. fmt lives at data offset 0. */
        if (cb_push(&code, OP_LEA_DATA) < 0) goto oom;
        if (cb_u32(&code, 0) < 0) goto oom;
        if (cb_push(&code, OP_PUSH_LOCAL) < 0) goto oom;
        if (cb_u32(&code, (unsigned long)slot[nodes[i].in[0]]) < 0) goto oom;
        if (cb_push(&code, OP_CALL_NATIVE) < 0) goto oom;
        if (cb_u32(&code, 0) < 0) goto oom;   /* printf native index */
        if (cb_push(&code, 2) < 0) goto oom;  /* argc */
    }

    /* Pass 3: EXIT nodes last (the first one reached halts the VM). */
    for (int oi = 0; oi < n; oi++) {
        int i = order[oi];
        if (nodes[i].type != NODE_EXIT) continue;
        if (cb_push(&code, OP_PUSH_LOCAL) < 0) goto oom;
        if (cb_u32(&code, (unsigned long)slot[nodes[i].in[0]]) < 0) goto oom;
        if (cb_push(&code, OP_HALT) < 0) goto oom;
    }

    /* A program that ends without an EXIT node must still stop cleanly:
     * reach the end of the code section with the stack balanced (printf
     * leaves its return value on the stack, so push a zero on top). */
    if (cb_push(&code, 0x04) < 0) goto oom;   /* OP_PUSH_ZERO */
    if (cb_push(&code, OP_HALT) < 0) goto oom;

    /* Layout. */
    const char *fmt = "%d\n\0";        /* data section content */
    size_t fmt_len = 4;                /* "%d\n" + NUL */
    const char *printf_name = "printf\0";
    size_t printf_name_len = 7;

    unsigned char ds[16];
    size_t ds_len = 0;
    /* RLE: literal run tag 0xFE + length + bytes. */
    if (fmt_len > 254) goto oom;
    ds[ds_len++] = 0xFE;
    ds[ds_len++] = (unsigned char)fmt_len;
    if (ds_len + fmt_len > sizeof(ds)) goto oom;
    memcpy(ds + ds_len, fmt, fmt_len);
    ds_len += fmt_len;

    unsigned nf = 1;
    unsigned ng = 0;
    unsigned nn = 1;
    unsigned ns = 0;
    unsigned cs = (unsigned)code.len;
    unsigned sp = (unsigned)printf_name_len;
    unsigned dsz = (unsigned)fmt_len;      /* decompressed data size */
    unsigned ef = 0;

    size_t ft = (size_t)nf * CVM_FUNC_ENTRY_SIZE;
    size_t gt = (size_t)ng * CVM_GLOBAL_ENTRY_SIZE;
    size_t nt = (size_t)nn * CVM_NATIVE_ENTRY_SIZE;
    size_t st = (size_t)ns * 8;
    size_t code_off = CVM_MODULE_HEADER_SIZE + ft + gt + nt + st;
    size_t total = code_off + (size_t)cs + ds_len + (size_t)sp;

    unsigned char *mod = (unsigned char *)calloc(1, total);
    if (!mod) goto oom;

    mod[0] = CVM_MAGIC_0; mod[1] = CVM_MAGIC_1;
    mod[2] = CVM_MAGIC_2; mod[3] = CVM_MAGIC_3;
    mod[4] = (unsigned char)CVM_VERSION_MAJOR;
    mod[5] = 0;                      /* minor */
    void w32(void *p, unsigned v) {
        unsigned char *b = (unsigned char *)p;
        b[0] = (unsigned char)(v & 255);
        b[1] = (unsigned char)((v >> 8) & 255);
        b[2] = (unsigned char)((v >> 16) & 255);
        b[3] = (unsigned char)((v >> 24) & 255);
    }
    w32(mod + 8, nf);
    w32(mod + 12, ng);
    w32(mod + 16, nn);
    w32(mod + 20, ns);
    w32(mod + 24, cs);
    w32(mod + 28, sp);
    w32(mod + 32, dsz);
    w32(mod + 36, ef);

    /* Function table: name_off, code_off, num_locals, argc, flags. */
    unsigned char *fe = mod + CVM_MODULE_HEADER_SIZE;
    w32(fe + 0, 0);                 /* name_off */
    w32(fe + 4, 0);                 /* code_off */
    w32(fe + 8, (unsigned)n);       /* num_locals: one slot per node */
    w32(fe + 12, 0);                /* argc */
    w32(fe + 16, 0);                /* flags */

    /* Native table: printf at name_off 0 in the string pool. */
    unsigned char *ne = mod + CVM_MODULE_HEADER_SIZE + ft + gt;
    w32(ne + 0, 0);

    /* Code. */
    if (code.len) memcpy(mod + code_off, code.b, code.len);

    /* Data section (RLE-compressed). */
    memcpy(mod + code_off + cs, ds, ds_len);

    /* String pool. */
    memcpy(mod + code_off + cs + ds_len, printf_name, printf_name_len);

    free(code.b);
    *out = mod;
    *out_size = total;
    return 0;

oom:
    free(code.b);
    if (err_cap) snprintf(err, err_cap, "out of memory");
    return -1;
}