/* cvm_emit.c — node-graph to CVM bytecode compiler.
 *
 * Emits a cvm2 module (format v2) from a dataflow graph. Nodes are
 * topologically sorted (a true DAG order, so the editor can connect nodes in
 * any sequence); every value node is computed into a local slot; PRINT nodes
 * call the `printf` native with an editable format string, PRINTS nodes call
 * `puts` with a string constant, and EXIT nodes halt with the value as the
 * exit code (OP_HALT leaves the operand-stack top as the exit status, which
 * the shell reports as `exit code: N`).
 *
 * Module layout follows cvm_load_module exactly:
 *   header | func table | global table | native table | string table |
 *   code | RLE-compressed data | string pool
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cvm_emit.h"

static size_t xstrnlen(const char *s, size_t cap) {
    size_t n = 0;
    while (n < cap && s[n]) n++;
    return n;
}

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
#define OP_PUSH_ZERO   0x04
#define OP_PUSH_LOCAL  0x10
#define OP_STORE_LOCAL 0x11
#define OP_ADD         0x20
#define OP_SUB         0x21
#define OP_MUL         0x22
#define OP_DIV         0x23
#define OP_MOD         0x24
#define OP_NEG         0x25
#define OP_AND         0x30
#define OP_OR          0x31
#define OP_XOR         0x32
#define OP_NOT         0x33
#define OP_SHL         0x34
#define OP_SHR         0x35
#define OP_CMP_EQ      0x40
#define OP_CMP_NE      0x41
#define OP_CMP_LT      0x42
#define OP_CMP_LE      0x43
#define OP_CMP_GT      0x44
#define OP_CMP_GE      0x45
#define OP_LNOT        0x46
#define OP_JMP         0x50
#define OP_JZ          0x51
#define OP_CALL_NATIVE 0x62
#define OP_LEA_DATA    0x82
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

static void cb_patch_u32(struct codebuf *cb, size_t pos, unsigned long v) {
    cb->b[pos + 0] = (unsigned char)(v & 255);
    cb->b[pos + 1] = (unsigned char)((v >> 8) & 255);
    cb->b[pos + 2] = (unsigned char)((v >> 16) & 255);
    cb->b[pos + 3] = (unsigned char)((v >> 24) & 255);
}

/* Push an integer literal with the shortest encoding. */
static int cb_imm(struct codebuf *cb, long long v) {
    if (v >= -128 && v <= 127) {
        if (cb_push(cb, OP_PUSH_IMM8) < 0) return -1;
        if (cb_push(cb, (unsigned char)(v & 0xFF)) < 0) return -1;
    } else if (v >= -2147483648LL && v <= 2147483647LL) {
        if (cb_push(cb, OP_PUSH_IMM32) < 0) return -1;
        if (cb_u32(cb, (unsigned long)(unsigned long long)v) < 0) return -1;
    } else {
        if (cb_push(cb, OP_PUSH_IMM64) < 0) return -1;
        if (cb_i64(cb, v) < 0) return -1;
    }
    return 0;
}

/* Number of required inputs for a node type. */
static int req_inputs(enum cvm_node_type t) {
    switch (t) {
    case NODE_NUM:
    case NODE_STR:
        return 0;
    case NODE_NEG:
    case NODE_NOT:
    case NODE_LNOT:
    case NODE_PRINT:
    case NODE_PRINTS:
    case NODE_EXIT:
        return 1;
    case NODE_IF:
        return 3;
    default:
        return 2;
    }
}

static int is_sink(enum cvm_node_type t) {
    return t == NODE_PRINT || t == NODE_PRINTS || t == NODE_EXIT;
}

/* ---- topological sort (Kahn, stable) ---- */
static int topo_sort(const struct cvm_node *nodes, int n,
                     int *order, char *err, size_t err_cap) {
    static unsigned char indeg[CVM_MAX_NODES];
    static int queue[CVM_MAX_NODES];
    memset(indeg, 0, (size_t)n);
    int qh = 0, qt = 0;
    for (int i = 0; i < n; i++) {
        if (nodes[i].type < 0 || nodes[i].type >= NODE_COUNT) {
            if (err_cap) snprintf(err, err_cap,
                                  "node %d: bad type", i);
            return -1;
        }
        int req = req_inputs(nodes[i].type);
        for (int k = 0; k < req; k++) {
            int in = nodes[i].in[k];
            if (in < 0) {
                /* Open PRINTS prints an empty line; every other open
                 * input needs its const fallback. */
                if (nodes[i].type == NODE_PRINTS) continue;
                if (!nodes[i].use_lit[k]) {
                    if (err_cap) snprintf(err, err_cap,
                                          "node %d: input %d is open", i, k);
                    return -1;
                }
                continue;
            }
            if (in >= n) {
                if (err_cap) snprintf(err, err_cap,
                                      "node %d: input %d out of range", i, in);
                return -1;
            }
            if (is_sink(nodes[in].type)) {
                if (err_cap) snprintf(err, err_cap,
                                      "node %d: cannot feed an output node", i);
                return -1;
            }
            indeg[i]++;
        }
        /* An open PRINTS prints an empty line (auto-repair layer); a wired
         * non-string source is still refused at validate time below. */
    }
    for (int i = 0; i < n; i++)
        if (indeg[i] == 0) queue[qt++] = i;
    int out_n = 0;
    while (qh < qt) {
        int v = queue[qh++];
        order[out_n++] = v;
        for (int i = 0; i < n; i++) {
            int req = req_inputs(nodes[i].type);
            for (int k = 0; k < req; k++) {
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

/* Emit one operand: the wired local slot or the fallback literal. The caller
 * guarantees validation passed, so an open input always has use_lit set. */
static int emit_operand(struct codebuf *code, const struct cvm_node *nodes,
                        const int *slot, int i, int k) {
    if (nodes[i].in[k] >= 0) {
        if (cb_push(code, OP_PUSH_LOCAL) < 0) return -1;
        if (cb_u32(code, (unsigned long)slot[nodes[i].in[k]]) < 0) return -1;
    } else {
        if (cb_imm(code, nodes[i].lit[k]) < 0) return -1;
    }
    return 0;
}

static int emit_jz(struct codebuf *code, size_t *rel_pos) {
    if (cb_push(code, OP_JZ) < 0) return -1;
    *rel_pos = code->len;
    return cb_u32(code, 0);
}

static int emit_jmp(struct codebuf *code, size_t *rel_pos) {
    if (cb_push(code, OP_JMP) < 0) return -1;
    *rel_pos = code->len;
    return cb_u32(code, 0);
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

    /* Validate string payloads before emitting code. */
    for (int i = 0; i < n; i++) {
        if (nodes[i].type == NODE_STR) {
            size_t L = xstrnlen(nodes[i].sval, sizeof(nodes[i].sval));
            if (L >= sizeof(nodes[i].sval)) {
                if (err_cap) snprintf(err, err_cap,
                                      "node %d: string too long", i);
                return -1;
            }
        }
        if (nodes[i].type == NODE_PRINT && nodes[i].sval[0]) {
            size_t L = xstrnlen(nodes[i].sval, sizeof(nodes[i].sval));
            if (L >= sizeof(nodes[i].sval)) {
                if (err_cap) snprintf(err, err_cap,
                                      "node %d: format too long", i);
                return -1;
            }
            if (L == 0) {
                if (err_cap) snprintf(err, err_cap,
                                      "node %d: empty format", i);
                return -1;
            }
        }
        if (nodes[i].type == NODE_PRINTS && nodes[i].in[0] >= 0) {
            enum cvm_node_type st = nodes[nodes[i].in[0]].type;
            if (st != NODE_STR && st != NODE_IF) {
                if (err_cap) snprintf(err, err_cap,
                                      "node %d: prints needs a string input", i);
                return -1;
            }
        }
    }

    /* Assign data-section offsets for STR constants and PRINT formats. */
    static unsigned str_off[CVM_MAX_NODES];
    static unsigned fmt_off[CVM_MAX_NODES];
    unsigned data_cur = 0;
    unsigned empty_off = 0;
    int need_empty = 0;
    for (int i = 0; i < n; i++) {
        if (nodes[i].type == NODE_PRINTS && nodes[i].in[0] < 0)
            need_empty = 1;
    }
    for (int i = 0; i < n; i++) {
        str_off[i] = 0;
        fmt_off[i] = 0;
        if (nodes[i].type == NODE_STR) {
            str_off[i] = data_cur;
            data_cur += (unsigned)strlen(nodes[i].sval) + 1;
        } else if (nodes[i].type == NODE_PRINT) {
            const char *f = nodes[i].sval[0] ? nodes[i].sval : "%d\n";
            fmt_off[i] = data_cur;
            data_cur += (unsigned)strlen(f) + 1;
        }
    }
    if (need_empty) {
        empty_off = data_cur;
        data_cur += 1;  /* one NUL byte: the empty line */
    }

    struct codebuf code = {0};
    struct codebuf ds = {0};
    unsigned char *blob = NULL;

    /* Pass 1: value nodes in topo order. */
    for (int oi = 0; oi < n; oi++) {
        int i = order[oi];
        if (is_sink(nodes[i].type)) continue;
        switch (nodes[i].type) {
        case NODE_NUM: {
            if (cb_imm(&code, nodes[i].ival) < 0) goto oom;
            if (cb_push(&code, OP_STORE_LOCAL) < 0) goto oom;
            if (cb_u32(&code, (unsigned long)slot[i]) < 0) goto oom;
            break;
        }
        case NODE_STR: {
            if (cb_push(&code, OP_LEA_DATA) < 0) goto oom;
            if (cb_u32(&code, str_off[i]) < 0) goto oom;
            if (cb_push(&code, OP_STORE_LOCAL) < 0) goto oom;
            if (cb_u32(&code, (unsigned long)slot[i]) < 0) goto oom;
            break;
        }
        case NODE_ADD: case NODE_SUB: case NODE_MUL: case NODE_DIV:
        case NODE_MOD: case NODE_AND: case NODE_OR: case NODE_XOR:
        case NODE_SHL: case NODE_SHR:
        case NODE_EQ: case NODE_NE: case NODE_LT: case NODE_LE:
        case NODE_GT: case NODE_GE: {
            for (int k = 0; k < 2; k++)
                if (emit_operand(&code, nodes, slot, i, k) < 0) goto oom;
            int op = OP_ADD;
            switch (nodes[i].type) {
            case NODE_ADD: op = OP_ADD; break;
            case NODE_SUB: op = OP_SUB; break;
            case NODE_MUL: op = OP_MUL; break;
            case NODE_DIV: op = OP_DIV; break;
            case NODE_MOD: op = OP_MOD; break;
            case NODE_AND: op = OP_AND; break;
            case NODE_OR:  op = OP_OR; break;
            case NODE_XOR: op = OP_XOR; break;
            case NODE_SHL: op = OP_SHL; break;
            case NODE_SHR: op = OP_SHR; break;
            case NODE_EQ: op = OP_CMP_EQ; break;
            case NODE_NE: op = OP_CMP_NE; break;
            case NODE_LT: op = OP_CMP_LT; break;
            case NODE_LE: op = OP_CMP_LE; break;
            case NODE_GT: op = OP_CMP_GT; break;
            default: op = OP_CMP_GE; break;
            }
            if (cb_push(&code, (unsigned char)op) < 0) goto oom;
            if (cb_push(&code, OP_STORE_LOCAL) < 0) goto oom;
            if (cb_u32(&code, (unsigned long)slot[i]) < 0) goto oom;
            break;
        }
        case NODE_NEG: case NODE_NOT: case NODE_LNOT: {
            if (emit_operand(&code, nodes, slot, i, 0) < 0) goto oom;
            int op = (nodes[i].type == NODE_NEG) ? OP_NEG :
                     (nodes[i].type == NODE_NOT) ? OP_NOT : OP_LNOT;
            if (cb_push(&code, (unsigned char)op) < 0) goto oom;
            if (cb_push(&code, OP_STORE_LOCAL) < 0) goto oom;
            if (cb_u32(&code, (unsigned long)slot[i]) < 0) goto oom;
            break;
        }
        case NODE_IF: {
            /* cond ? then : else — JZ over the then-branch. Targets are
             * bytecode IPs: rel = target - (rel_pos + 4). */
            if (emit_operand(&code, nodes, slot, i, 0) < 0) goto oom;
            size_t jz_pos = 0, jmp_pos = 0;
            if (emit_jz(&code, &jz_pos) < 0) goto oom;
            if (emit_operand(&code, nodes, slot, i, 1) < 0) goto oom;
            if (emit_jmp(&code, &jmp_pos) < 0) goto oom;
            cb_patch_u32(&code, jz_pos,
                         (unsigned long)(code.len - (jz_pos + 4)));
            if (emit_operand(&code, nodes, slot, i, 2) < 0) goto oom;
            cb_patch_u32(&code, jmp_pos,
                         (unsigned long)(code.len - (jmp_pos + 4)));
            if (cb_push(&code, OP_STORE_LOCAL) < 0) goto oom;
            if (cb_u32(&code, (unsigned long)slot[i]) < 0) goto oom;
            break;
        }
        default: break;
        }
    }

    /* Pass 2: PRINT/PRINTS nodes (side effects, topo order). */
    for (int oi = 0; oi < n; oi++) {
        int i = order[oi];
        if (nodes[i].type == NODE_PRINT) {
            if (cb_push(&code, OP_LEA_DATA) < 0) goto oom;
            if (cb_u32(&code, fmt_off[i]) < 0) goto oom;
            if (emit_operand(&code, nodes, slot, i, 0) < 0) goto oom;
            if (cb_push(&code, OP_CALL_NATIVE) < 0) goto oom;
            if (cb_u32(&code, 0) < 0) goto oom;   /* printf native index */
            if (cb_push(&code, 2) < 0) goto oom;  /* argc */
        } else if (nodes[i].type == NODE_PRINTS) {
            if (nodes[i].in[0] < 0) {
                /* Open input: print the empty string (auto-repair). The
                 * blob is calloc-zeroed, so empty_off holds one NUL. */
                if (cb_push(&code, OP_LEA_DATA) < 0) goto oom;
                if (cb_u32(&code, empty_off) < 0) goto oom;
            } else if (emit_operand(&code, nodes, slot, i, 0) < 0) goto oom;
            if (cb_push(&code, OP_CALL_NATIVE) < 0) goto oom;
            if (cb_u32(&code, 1) < 0) goto oom;   /* puts native index */
            if (cb_push(&code, 1) < 0) goto oom;  /* argc */
        }
    }

    /* Pass 3: EXIT nodes last (the first one reached halts the VM). */
    for (int oi = 0; oi < n; oi++) {
        int i = order[oi];
        if (nodes[i].type != NODE_EXIT) continue;
        if (emit_operand(&code, nodes, slot, i, 0) < 0) goto oom;
        if (cb_push(&code, OP_HALT) < 0) goto oom;
    }

    /* A program that ends without an EXIT node must still stop cleanly:
     * reach the end of the code section with the stack balanced (printf
     * leaves its return value on the stack, so push a zero on top). */
    if (cb_push(&code, OP_PUSH_ZERO) < 0) goto oom;
    if (cb_push(&code, OP_HALT) < 0) goto oom;

    /* Data blob: STR bytes + PRINT formats, each NUL-terminated. */
    if (data_cur > 0) {
        blob = (unsigned char *)calloc(1, data_cur);
        if (!blob) goto oom;
        for (int i = 0; i < n; i++) {
            if (nodes[i].type == NODE_STR) {
                size_t L = strlen(nodes[i].sval) + 1;
                memcpy(blob + str_off[i], nodes[i].sval, L);
            } else if (nodes[i].type == NODE_PRINT) {
                const char *f = nodes[i].sval[0] ? nodes[i].sval : "%d\n";
                size_t L = strlen(f) + 1;
                memcpy(blob + fmt_off[i], f, L);
            }
        }
    }

    /* RLE: literal runs (tag 0xFE + length + bytes), chunked at 255. */
    if (data_cur > 0) {
        size_t o = 0;
        while (o < data_cur) {
            size_t chunk = data_cur - o > 255 ? 255 : data_cur - o;
            if (cb_push(&ds, 0xFE) < 0) goto oom;
            if (cb_push(&ds, (unsigned char)chunk) < 0) goto oom;
            for (size_t k = 0; k < chunk; k++)
                if (cb_push(&ds, blob[o + k]) < 0) goto oom;
            o += chunk;
        }
    }
    free(blob);
    blob = NULL;

    /* Layout. */
    static const char pool[] = "printf\0puts\0";
    size_t pool_len = sizeof(pool) - 1;  /* 12: two NUL-terminated names */

    unsigned nf = 1;
    unsigned ng = 0;
    unsigned nn = 2;
    unsigned ns = 0;
    unsigned cs = (unsigned)code.len;
    unsigned sp = (unsigned)pool_len;
    unsigned dsz = data_cur;
    unsigned ef = 0;

    size_t ft = (size_t)nf * CVM_FUNC_ENTRY_SIZE;
    size_t gt = (size_t)ng * CVM_GLOBAL_ENTRY_SIZE;
    size_t nt = (size_t)nn * CVM_NATIVE_ENTRY_SIZE;
    size_t st = (size_t)ns * 8;
    size_t code_off = CVM_MODULE_HEADER_SIZE + ft + gt + nt + st;
    size_t total = code_off + (size_t)cs + ds.len + (size_t)sp;

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

    /* Native table: printf at pool off 0, puts at pool off 7. */
    unsigned char *ne = mod + CVM_MODULE_HEADER_SIZE + ft + gt;
    w32(ne + 0, 0);
    w32(ne + 4, 7);

    /* Code. */
    if (code.len) memcpy(mod + code_off, code.b, code.len);

    /* Data section (RLE-compressed). */
    if (ds.len) memcpy(mod + code_off + cs, ds.b, ds.len);

    /* String pool. */
    memcpy(mod + code_off + cs + ds.len, pool, pool_len);

    free(code.b);
    free(ds.b);
    *out = mod;
    *out_size = total;
    return 0;

oom:
    free(code.b);
    free(ds.b);
    free(blob);
    if (err_cap) snprintf(err, err_cap, "out of memory");
    return -1;
}
