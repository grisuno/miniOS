/* node_editor.c — visual low-code editor that compiles to CVM bytecode.
 *
 * A ring-3 Nuklear application (built exactly like DOOM: host gcc -static,
 * ships on MiniFS) that lets you place dataflow nodes on a canvas, wire
 * outputs to inputs, edit every parameter in an inspector, and compile the
 * graph into a .cvm module that the CVM interpreter runs in the OS.
 *
 *     nuklear                      -> GUI node editor
 *     nuklear --demo cvm/demo.cvm  -> compile a fixed demo graph, write it
 *     nuklear --compile g.txt out  -> compile a text-described graph
 *     nuklear --selftest           -> render one UI frame (BDD smoke test)
 *
 * The GUI uses the MiniOS platform layer (nuklear_minios.c) to rasterize
 * into the kernel back-buffer and composite it as a desktop window.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "minios_abi.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "nuklear.h"
#include "nuklear_minios.h"
#include "cvm_emit.h"

/* ---- Graph model (mirrors cvm_node, plus canvas position) ---- */
#define MAX_NODES 64
#define STR_MAX CVM_NODE_STR_MAX

enum {
    G_NUM, G_STR, G_ADD, G_SUB, G_MUL, G_DIV, G_MOD, G_NEG,
    G_AND, G_OR, G_XOR, G_NOT, G_SHL, G_SHR,
    G_EQ, G_NE, G_LT, G_LE, G_GT, G_GE, G_LNOT, G_IF,
    G_PRINT, G_PRINTS, G_EXIT,
    G_COUNT
};

struct gnode {
    int kind;
    long long ival;
    char sval[STR_MAX];
    int in[3];
    long long lit[3];
    int use_lit[3];
    float x, y;
};

/* Single registry: name, text-format word, inputs, outputs, color. */
struct nodedef {
    const char *name;
    const char *pname;
    int ni;
    int no;
    struct nk_color col;
};

static const struct nodedef node_defs[G_COUNT] = {
    [G_NUM]    = { "Number", "num",    0, 1, { 70,130,180,255 } },
    [G_STR]    = { "String", "str",    0, 1, { 90,160,120,255 } },
    [G_ADD]    = { "Add",    "add",    2, 1, { 60,179,113,255 } },
    [G_SUB]    = { "Sub",    "sub",    2, 1, { 210,105,105,255 } },
    [G_MUL]    = { "Mul",    "mul",    2, 1, { 186,135, 89,255 } },
    [G_DIV]    = { "Div",    "div",    2, 1, { 147,112,219,255 } },
    [G_MOD]    = { "Mod",    "mod",    2, 1, { 160,120,200,255 } },
    [G_NEG]    = { "Neg",    "neg",    1, 1, { 255,165,  0,255 } },
    [G_AND]    = { "And",    "and",    2, 1, { 60,140,140,255 } },
    [G_OR]     = { "Or",     "or",     2, 1, { 60,160,180,255 } },
    [G_XOR]    = { "Xor",    "xor",    2, 1, { 120,140,200,255 } },
    [G_NOT]    = { "Not",    "not",    1, 1, { 200,150, 60,255 } },
    [G_SHL]    = { "Shl",    "shl",    2, 1, { 110,170,110,255 } },
    [G_SHR]    = { "Shr",    "shr",    2, 1, { 170,170,110,255 } },
    [G_EQ]     = { "Eq",     "eq",     2, 1, { 100,180,220,255 } },
    [G_NE]     = { "Ne",     "ne",     2, 1, { 220,180,100,255 } },
    [G_LT]     = { "Lt",     "lt",     2, 1, { 140,200,140,255 } },
    [G_LE]     = { "Le",     "le",     2, 1, { 140,180,200,255 } },
    [G_GT]     = { "Gt",     "gt",     2, 1, { 200,140,180,255 } },
    [G_GE]     = { "Ge",     "ge",     2, 1, { 180,200,140,255 } },
    [G_LNOT]   = { "LNot",   "lnot",   1, 1, { 220,160, 80,255 } },
    [G_IF]     = { "If",     "if",     3, 1, { 240,200, 80,255 } },
    [G_PRINT]  = { "Print",  "print",  1, 0, { 100,149,237,255 } },
    [G_PRINTS] = { "PrStr",  "prints", 1, 0, { 130,170,240,255 } },
    [G_EXIT]   = { "Exit",   "exit",   1, 0, { 220, 80, 60,255 } },
};

static struct gnode g_nodes[MAX_NODES];
static int g_count;
static char g_status[192];
static int g_selected = -1;

static int node_inputs(int k) {
    if (k < 0 || k >= G_COUNT) return 0;
    return node_defs[k].ni;
}

static int node_outputs(int k) {
    if (k < 0 || k >= G_COUNT) return 0;
    return node_defs[k].no;
}

static const char *kind_name(int k) {
    if (k < 0 || k >= G_COUNT) return "?";
    return node_defs[k].name;
}

static struct nk_color kind_color(int k) {
    if (k < 0 || k >= G_COUNT) return nk_rgb(150, 150, 150);
    return node_defs[k].col;
}

static void graph_clear(void) {
    g_count = 0;
    g_selected = -1;
    g_status[0] = '\0';
}

static int graph_add(int kind) {
    if (kind < 0 || kind >= G_COUNT) return -1;
    if (g_count >= MAX_NODES) return -1;
    struct gnode *n = &g_nodes[g_count];
    memset(n, 0, sizeof(*n));
    n->kind = kind;
    n->in[0] = n->in[1] = n->in[2] = -1;
    n->x = 30.0f + (float)(g_count % 6) * 160.0f;
    n->y = 60.0f + (float)(g_count / 6) * 120.0f;
    if (kind == G_NUM) n->ival = 1;
    if (kind == G_STR) snprintf(n->sval, sizeof(n->sval), "hi");
    return g_count++;
}

static void graph_del(int idx) {
    if (idx < 0 || idx >= g_count) return;
    memmove(&g_nodes[idx], &g_nodes[idx + 1],
            (size_t)(g_count - idx - 1) * sizeof(g_nodes[0]));
    g_count--;
    for (int i = 0; i < g_count; i++)
        for (int k = 0; k < 3; k++) {
            if (g_nodes[i].in[k] == idx) {
                g_nodes[i].in[k] = -1;
            } else if (g_nodes[i].in[k] > idx) {
                g_nodes[i].in[k]--;
            }
        }
    if (g_selected == idx) g_selected = -1;
    else if (g_selected > idx) g_selected--;
}

/* Map the graph into the compiler's node array. Returns node count or <0. */
static int graph_to_compiler(struct cvm_node *out, int cap) {
    if (g_count > cap) return -1;
    for (int i = 0; i < g_count; i++) {
        struct gnode *g = &g_nodes[i];
        out[i].type = (enum cvm_node_type)g->kind;
        out[i].ival = g->ival;
        memcpy(out[i].sval, g->sval, sizeof(out[i].sval));
        out[i].sval[sizeof(out[i].sval) - 1] = '\0';
        for (int k = 0; k < 3; k++) {
            out[i].in[k] = g->in[k];
            out[i].lit[k] = g->lit[k];
            out[i].use_lit[k] = g->use_lit[k];
        }
    }
    return g_count;
}

/* Pre-compile pass: repair every open data input with a const 0 fallback
 * (an open PrStr prints an empty line), so Compile always writes a module
 * instead of refusing. Repairs are loud (rep), and *bad selects the first
 * touched node. Only unrepairable problems (herr: bad type, dangling wire,
 * sink used as a source, PrStr wired to a non-string) still refuse. */
static int repair_graph(char *rep, size_t repcap, char *herr, size_t herrcap,
                        int *bad) {
    int nhard = 0;
    int first_bad = -1;
    size_t rl = 0, hl = 0;
    rep[0] = '\0';
    herr[0] = '\0';
    void addrep(const char *s) {
        size_t sl = strlen(s);
        int room = (int)repcap - (int)rl - 12;
        if (room <= 0) return;
        if (rl > 0 && room > 3) { memcpy(rep + rl, " | ", 3); rl += 3; room -= 3; }
        if ((int)sl > room) sl = (size_t)room;
        memcpy(rep + rl, s, sl);
        rl += sl;
        rep[rl] = '\0';
    }
    void adderr(const char *s) {
        size_t sl = strlen(s);
        int room = (int)herrcap - (int)hl - 12;
        if (room <= 0) return;
        if (hl > 0 && room > 3) { memcpy(herr + hl, " | ", 3); hl += 3; room -= 3; }
        if ((int)sl > room) sl = (size_t)room;
        memcpy(herr + hl, s, sl);
        hl += sl;
        herr[hl] = '\0';
    }
    for (int i = 0; i < g_count; i++) {
        struct gnode *g = &g_nodes[i];
        if (g->kind < 0 || g->kind >= G_COUNT) {
            char m[64];
            snprintf(m, sizeof(m), "node %d: bad type", i);
            adderr(m);
            if (first_bad < 0) first_bad = i;
            nhard++;
            continue;
        }
        int ni = node_inputs(g->kind);
        for (int k = 0; k < ni; k++) {
            if (g->in[k] >= 0) {
                if (g->in[k] >= g_count) {
                    char m[96];
                    snprintf(m, sizeof(m), "node %d (%s): in%d out of range",
                             i, kind_name(g->kind), k);
                    adderr(m);
                    if (first_bad < 0) first_bad = i;
                    nhard++;
                } else if (node_outputs(g_nodes[g->in[k]].kind) == 0 &&
                           g_nodes[g->in[k]].kind != G_NUM &&
                           g_nodes[g->in[k]].kind != G_STR) {
                    /* A sink (Print/PrStr/Exit) has no output pin. */
                    char m[96];
                    snprintf(m, sizeof(m),
                             "node %d (%s): in%d fed by %s (no output pin)",
                             i, kind_name(g->kind), k,
                             kind_name(g_nodes[g->in[k]].kind));
                    adderr(m);
                    if (first_bad < 0) first_bad = i;
                    nhard++;
                }
            } else if (!g->use_lit[k]) {
                const char *inname = "in";
                char nm[16];
                if (g->kind == G_IF)
                    inname = k == 0 ? "cond" : k == 1 ? "then" : "else";
                else {
                    snprintf(nm, sizeof(nm), "in%d", k);
                    inname = nm;
                }
                if (g->kind == G_PRINTS) {
                    char m[96];
                    snprintf(m, sizeof(m),
                             "node %d (PrStr): no input -> prints empty line",
                             i);
                    addrep(m);
                } else {
                    char m[128];
                    snprintf(m, sizeof(m),
                             "node %d (%s): %s was open -> using 0",
                             i, kind_name(g->kind), inname);
                    addrep(m);
                    g->use_lit[k] = 1;
                    g->lit[k] = 0;
                }
                if (first_bad < 0) first_bad = i;
            }
        }
        if (g->kind == G_PRINTS && g->in[0] >= 0 && g->in[0] < g_count) {
            int sk = g_nodes[g->in[0]].kind;
            if (sk != G_STR && sk != G_IF) {
                char m[96];
                snprintf(m, sizeof(m),
                         "node %d (PrStr): needs a String, not %s",
                         i, kind_name(sk));
                adderr(m);
                if (first_bad < 0) first_bad = i;
                nhard++;
            }
        }
    }
    if (bad) *bad = first_bad;
    return nhard;
}

/* Compile the current graph to a file. Returns 0 on success. Open inputs
 * are auto-repaired (const 0 / empty line) and reported, so this refuses
 * only on unrepairable problems. */
static int compile_to(const char *path) {
    char rep[192], herr[192];
    int bad = -1;
    int nhard = repair_graph(rep, sizeof(rep), herr, sizeof(herr), &bad);
    if (bad >= 0) g_selected = bad;
    if (nhard > 0) {
        snprintf(g_status, sizeof(g_status), "!! NOT COMPILED (%d): %.140s",
                 nhard, herr);
        return -1;
    }
    struct cvm_node cvm[MAX_NODES];
    int n = graph_to_compiler(cvm, MAX_NODES);
    if (n < 0) { snprintf(g_status, sizeof(g_status), "!! graph too large"); return -1; }
    unsigned char *mod;
    size_t sz;
    char err[128];
    if (cvm_compile(cvm, n, &mod, &sz, err, sizeof(err)) < 0) {
        snprintf(g_status, sizeof(g_status), "!! NOT COMPILED: %.100s", err);
        return -1;
    }
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        snprintf(g_status, sizeof(g_status),
                 "!! NOT SAVED: cannot create %s (check the directory)", path);
        free(mod);
        return -1;
    }
    size_t off = 0;
    while (off < sz) {
        ssize_t w = write(fd, mod + off, sz - off);
        if (w <= 0) break;
        off += (size_t)w;
    }
    close(fd);
    free(mod);
    if (off != sz) {
        snprintf(g_status, sizeof(g_status), "!! NOT SAVED: write error on %s", path);
        return -1;
    }
    snprintf(g_status, sizeof(g_status), "OK: wrote %s (%zu bytes)", path, sz);
    if (rep[0]) {
        /* Repairs happened: keep the file, but say what was auto-filled. */
        char ok[192];
        snprintf(ok, sizeof(ok), "%s", g_status);
        snprintf(g_status, sizeof(g_status), "%s | REPAIRED: %.90s", ok, rep);
    }
    return 0;
}

/* ---- Headless graph text format (v2, backward compatible) ----
 *   num a 5          str s "hi"       add b a c      add c a #5
 *   neg n a          if r c t e       print p e      print p e "%d ms\n"
 *   prints s2 s      exit x e
 * Inputs are earlier-defined node names or #integer literals (wire or
 * const). Forward references are rejected. A quoted "..." token carries
 * C-like escapes (\\ \" \n \t). The print format is an optional 4th token. */
static void write_quoted(FILE *f, const char *s) {
    fputc('"', f);
    for (; *s; s++) {
        if (*s == '\\' || *s == '"') { fputc('\\', f); fputc(*s, f); }
        else if (*s == '\n') { fputc('\\', f); fputc('n', f); }
        else if (*s == '\t') { fputc('\\', f); fputc('t', f); }
        else fputc(*s, f);
    }
    fputc('"', f);
}

/* Tokenize a line into tokens; quoted tokens honour backslash escapes.
 * Returns token count (0..maxtok). */
static int tokenize(char *line, char *toks[], int maxtok, char *buf, size_t bufsz) {
    int nt = 0;
    char *p = line;
    char *w = buf;
    char *wend = buf + bufsz - 1;
    while (*p && nt < maxtok) {
        while (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n') p++;
        if (!*p) break;
        /* A '#' starts a comment, unless it opens a literal (#5, #-). */
        if (*p == '#' && !(p[1] == '-' || (p[1] >= '0' && p[1] <= '9')))
            break;
        if (*p == '"') {
            p++;
            toks[nt++] = w;
            while (*p && *p != '"' && w < wend) {
                if (*p == '\\' && p[1]) {
                    p++;
                    if (*p == 'n') *w++ = '\n';
                    else if (*p == 't') *w++ = '\t';
                    else *w++ = *p;
                    p++;
                } else {
                    *w++ = *p++;
                }
            }
            if (*p == '"') p++;
            if (w < wend) *w++ = '\0';
            else *buf = '\0';
        } else {
            toks[nt++] = w;
            while (*p && *p != ' ' && *p != '\t' && *p != '\r' && *p != '\n'
                   && w < wend)
                *w++ = *p++;
            if (w < wend) *w++ = '\0';
            else *buf = '\0';
        }
    }
    return nt;
}

static int save_graph_file(const char *path) {
    FILE *f = fopen(path, "w");
    if (!f) { snprintf(g_status, sizeof(g_status), "cannot open %s", path); return -1; }
    static char names[MAX_NODES][16];
    for (int i = 0; i < g_count; i++)
        snprintf(names[i], sizeof(names[i]), "n%d", i);
    for (int i = 0; i < g_count; i++) {
        struct gnode *g = &g_nodes[i];
        const char *pn = node_defs[g->kind].pname;
        if (g->kind == G_NUM) {
            fprintf(f, "num %s %lld\n", names[i], g->ival);
        } else if (g->kind == G_STR) {
            fprintf(f, "str %s ", names[i]);
            write_quoted(f, g->sval);
            fputc('\n', f);
        } else {
            fprintf(f, "%s %s", pn, names[i]);
            int ni = node_inputs(g->kind);
            for (int k = 0; k < ni; k++) {
                if (g->in[k] >= 0 && g->in[k] < g_count)
                    fprintf(f, " %s", names[g->in[k]]);
                else if (g->use_lit[k])
                    fprintf(f, " #%lld", g->lit[k]);
                else
                    fprintf(f, " #-");
            }
            if (g->kind == G_PRINT && g->sval[0]) {
                fputc(' ', f);
                write_quoted(f, g->sval);
            }
            fputc('\n', f);
        }
    }
    fclose(f);
    snprintf(g_status, sizeof(g_status), "saved %s (%d nodes)", path, g_count);
    return 0;
}

static int parse_graph_file(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return -1;
    graph_clear();
    static char names[MAX_NODES][16];
    char line[512];
    int rc = 0;
    int resolve(const char *nme, int upto) {
        for (int k = 0; k < upto; k++)
            if (strcmp(names[k], nme) == 0) return k;
        return -2;
    }
    /* Parse one input token: name, #literal, or #- (open, no literal). */
    int parse_input(const char *tok, int idx, int k) {
        if (tok[0] == '#') {
            if (!strcmp(tok, "#-")) {
                g_nodes[idx].in[k] = -1;
                g_nodes[idx].use_lit[k] = 0;
                return 0;
            }
            g_nodes[idx].in[k] = -1;
            g_nodes[idx].lit[k] = atoll(tok + 1);
            g_nodes[idx].use_lit[k] = 1;
            return 0;
        }
        int r = resolve(tok, idx);
        if (r < 0) return -1;
        g_nodes[idx].in[k] = r;
        return 0;
    }
    while (fgets(line, sizeof(line), f)) {
        char *toks[8];
        char buf[512];
        int nt = tokenize(line, toks, 8, buf, sizeof(buf));
        if (nt == 0) continue;
        int kind = -1;
        for (int k = 0; k < G_COUNT; k++)
            if (!strcmp(toks[0], node_defs[k].pname)) { kind = k; break; }
        if (kind < 0 || nt < 2) { rc = -1; break; }
        if (g_count >= MAX_NODES) { rc = -1; break; }
        int idx = g_count;
        snprintf(names[idx], sizeof(names[idx]), "%s", toks[1]);
        graph_add(kind);
        if (kind == G_NUM) {
            if (nt < 3) { rc = -1; break; }
            g_nodes[idx].ival = atoll(toks[2]);
        } else if (kind == G_STR) {
            if (nt < 3) { rc = -1; break; }
            snprintf(g_nodes[idx].sval, sizeof(g_nodes[idx].sval), "%s", toks[2]);
        } else {
            int ni = node_inputs(kind);
            if (nt < 2) { rc = -1; break; }
            for (int k = 0; k < ni; k++) {
                /* A missing trailing token is an open input (auto-repair
                 * fills const 0 at compile time); a bad name still fails. */
                const char *tok = (2 + k < nt) ? toks[2 + k] : "#-";
                if (parse_input(tok, idx, k) < 0) { rc = -1; break; }
            }
            if (rc) break;
            if (kind == G_PRINT && nt > 2 + ni)
                snprintf(g_nodes[idx].sval, sizeof(g_nodes[idx].sval), "%s",
                         toks[2 + ni]);
        }
    }
    fclose(f);
    if (rc) graph_clear();
    return rc;
}

/* ---- Nuklear UI state ---- */
#define UI_MEMORY (4 * 1024 * 1024)
static char ui_memory[UI_MEMORY];

static int ui_quit;
static int drag_node = -1;
static float drag_ox, drag_oy;
static int add_sel;

/* Link-drag state: click an output pin, drag to an input pin. */
static int linking_active;
static int linking_src_node;
static int linking_src_slot;

/* Node geometry constants. */
#define NODE_W       130.0f
#define TITLE_H      20.0f
#define PIN_R        5
#define PIN_DIAM     (PIN_R * 2 + 1)
#define BEZIER_PAD   50.0f
#define GRID_SIZE    32.0f

/* Compute the Y positions of input and output pins for a node. */
static float pin_y(struct gnode *n, int slot, int is_output) {
    int ni = node_inputs(n->kind);
    int no = node_outputs(n->kind);
    int count = is_output ? no : ni;
    if (is_output && n->kind == G_IF) count = 1;
    if (count <= 0) count = 1;
    float body_h = (float)(ni > 3 ? ni : 3) * 18.0f + 8.0f;
    float total = TITLE_H + body_h;
    float space = total / (float)(count + 1);
    return n->y + space * (float)(slot + 1);
}

static float node_h(struct gnode *n) {
    int ni = node_inputs(n->kind);
    if (ni < 1 && n->kind != G_NUM && n->kind != G_STR) ni = 1;
    int rows = ni > 3 ? ni : 3;
    if (n->kind == G_NUM || n->kind == G_STR) rows = 3;
    return TITLE_H + (float)rows * 18.0f + 8.0f;
}

static void ui_inspector(struct nk_context *ctx) {
    nk_layout_row_dynamic(ctx, 16, 1);
    if (g_selected < 0 || g_selected >= g_count) {
        nk_label(ctx, "select a node to edit its parameters",
                 NK_TEXT_LEFT);
        return;
    }
    struct gnode *n = &g_nodes[g_selected];
    char head[64];
    snprintf(head, sizeof(head), "node %d: %s", g_selected, kind_name(n->kind));
    nk_label(ctx, head, NK_TEXT_LEFT);
    if (n->kind == G_NUM) {
        nk_layout_row_dynamic(ctx, 20, 1);
        int v = (int)n->ival;
        nk_property_int(ctx, "value:", -2147483647, &v, 2147483647, 1, 10);
        n->ival = v;
    } else if (n->kind == G_STR) {
        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "text:", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 24, 1);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, n->sval,
                                       (int)sizeof(n->sval), 0);
    } else if (n->kind == G_PRINT) {
        nk_layout_row_dynamic(ctx, 20, 1);
        nk_label(ctx, "format (empty = %d):", NK_TEXT_LEFT);
        nk_layout_row_dynamic(ctx, 24, 1);
        nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, n->sval,
                                       (int)sizeof(n->sval), 0);
    }
    int ni = node_inputs(n->kind);
    for (int k = 0; k < ni; k++) {
        nk_layout_row_begin(ctx, NK_STATIC, 20, 3);
        nk_layout_row_push(ctx, 110);
        char lab[48];
        if (n->kind == G_IF)
            snprintf(lab, sizeof(lab), "%s:",
                     k == 0 ? "cond" : k == 1 ? "then" : "else");
        else
            snprintf(lab, sizeof(lab), "in%d:", k);
        nk_label(ctx, lab, NK_TEXT_LEFT);
        nk_layout_row_push(ctx, 110);
        char src[48];
        if (n->in[k] >= 0) snprintf(src, sizeof(src), "<- node %d", n->in[k]);
        else if (n->use_lit[k]) snprintf(src, sizeof(src), "const %lld", n->lit[k]);
        else snprintf(src, sizeof(src), "(open)");
        nk_label(ctx, src, NK_TEXT_LEFT);
        nk_layout_row_push(ctx, 70);
        char xb[8];
        snprintf(xb, sizeof(xb), "x%d", k);
        if (nk_button_label(ctx, xb)) n->in[k] = -1;
        nk_layout_row_end(ctx);
        if (n->kind == G_PRINTS) continue;
        nk_layout_row_dynamic(ctx, 20, 2);
        int ul = n->use_lit[k];
        char clab[16];
        snprintf(clab, sizeof(clab), "const%d", k);
        int nul = nk_check_label(ctx, clab, ul);
        n->use_lit[k] = nul;
        if (nul) {
            int v = (int)n->lit[k];
            char plab[16];
            snprintf(plab, sizeof(plab), "#%d:", k);
            nk_property_int(ctx, plab, -2147483647, &v, 2147483647, 1, 10);
            n->lit[k] = v;
        } else {
            nk_label(ctx, "", NK_TEXT_LEFT);
        }
    }
    nk_layout_row_static(ctx, 22, 90, 3);
    if (nk_button_label(ctx, "Unlink")) {
        n->in[0] = n->in[1] = n->in[2] = -1;
    }
    if (nk_button_label(ctx, "Delete")) {
        graph_del(g_selected);
    }
    if (nk_button_label(ctx, "Deselect")) {
        g_selected = -1;
    }
}

static void ui_build(struct nk_context *ctx, float win_w, float win_h) {
    if (nk_begin_titled(ctx, "nuklear", "Node Editor", nk_rect(0, 0, win_w, win_h),
                        NK_WINDOW_NO_SCROLLBAR)) {

        /* Processor palette: combo + Add, then actions. */
        static const char *items[G_COUNT];
        static int items_init;
        if (!items_init) {
            for (int k = 0; k < G_COUNT; k++) items[k] = node_defs[k].name;
            items_init = 1;
        }
        nk_layout_row_begin(ctx, NK_STATIC, 24, 5);
        nk_layout_row_push(ctx, 150);
        nk_combobox(ctx, items, G_COUNT, &add_sel, 20, nk_vec2(150, 300));
        nk_layout_row_push(ctx, 60);
        if (nk_button_label(ctx, "Add")) {
            int id = graph_add(add_sel);
            if (id >= 0) g_selected = id;
            else snprintf(g_status, sizeof(g_status), "graph full (%d nodes)", MAX_NODES);
        }
        nk_layout_row_push(ctx, 80);
        if (nk_button_label(ctx, "Compile")) compile_to("/cvm/nodes.cvm");
        nk_layout_row_push(ctx, 60);
        if (nk_button_label(ctx, "Save")) save_graph_file("/cvm/graph.txt");
        nk_layout_row_push(ctx, 60);
        if (nk_button_label(ctx, "Load")) {
            if (parse_graph_file("/cvm/graph.txt") < 0)
                snprintf(g_status, sizeof(g_status), "cannot parse cvm/graph.txt");
            else
                snprintf(g_status, sizeof(g_status), "loaded cvm/graph.txt (%d nodes)",
                         g_count);
        }
        nk_layout_row_end(ctx);

        nk_layout_row_static(ctx, 24, 80, 4);
        if (nk_button_label(ctx, "Run")) {
            compile_to("/cvm/nodes.cvm");
        }
        if (nk_button_label(ctx, "Clear"))  graph_clear();
        if (nk_button_label(ctx, "Delete")) graph_del(g_selected);
        if (nk_button_label(ctx, "Quit"))   ui_quit = 1;

        /* Status line: errors (!!) shout in red and wrap, repair notes in
         * orange, otherwise the plain hint. A refusal or repair always
         * says what to do. */
        if (g_status[0] == '!' && g_status[1] == '!') {
            nk_layout_row_dynamic(ctx, 32, 1);
            nk_label_colored_wrap(ctx, g_status, nk_rgb(255, 120, 120));
        } else if (strstr(g_status, "REPAIRED:") != NULL) {
            nk_layout_row_dynamic(ctx, 32, 1);
            nk_label_colored_wrap(ctx, g_status, nk_rgb(255, 200, 100));
        } else {
            nk_layout_row_dynamic(ctx, 16, 1);
            nk_label(ctx, g_status[0] ? g_status : "pick a processor, Add, wire pins, edit below",
                     NK_TEXT_LEFT);
        }

        ui_inspector(ctx);

        /* Canvas with absolute node placement. */
        float canvas_h = win_h - 250.0f;
        if (canvas_h < 80) canvas_h = 80;
        nk_layout_space_begin(ctx, NK_STATIC, canvas_h, g_count + 32);

        struct nk_command_buffer *canvas = nk_window_get_canvas(ctx);
        struct nk_rect canvas_bounds = nk_layout_space_bounds(ctx);
        struct nk_input *in = &ctx->input;

        /* Manual canvas drawing and hit-testing live in window coordinates
         * while node positions are layout-space local: shift every local
         * point by the space origin. Without it pins, curves and clicks
         * land canvas_bounds away from the visible nodes and the mouse
         * never hits anything. */
        float ox = canvas_bounds.x;
        float oy = canvas_bounds.y;

        /* ---- Grid background ---- */
        {
            struct nk_color grid_col = nk_rgb(50, 50, 55);
            float x, y;
            for (x = fmod(canvas_bounds.x, GRID_SIZE); x < canvas_bounds.w; x += GRID_SIZE)
                nk_stroke_line(canvas, x + canvas_bounds.x, canvas_bounds.y,
                               x + canvas_bounds.x, canvas_bounds.y + canvas_bounds.h,
                               1.0f, grid_col);
            for (y = fmod(canvas_bounds.y, GRID_SIZE); y < canvas_bounds.h; y += GRID_SIZE)
                nk_stroke_line(canvas, canvas_bounds.x, y + canvas_bounds.y,
                               canvas_bounds.x + canvas_bounds.w, y + canvas_bounds.y,
                               1.0f, grid_col);
        }

        /* ---- Draw connecting curves (from stored links) ---- */
        for (int i = 0; i < g_count; i++) {
            struct gnode *n = &g_nodes[i];
            for (int k = 0; k < node_inputs(n->kind); k++) {
                int src = n->in[k];
                if (src < 0 || src >= g_count) continue;
                struct gnode *sn = &g_nodes[src];
                float sx = sn->x + NODE_W + ox;
                float sy = pin_y(sn, 0, 1) + oy;
                float dx = n->x + ox;
                float dy = pin_y(n, k, 0) + oy;
                nk_stroke_curve(canvas, sx, sy, sx + BEZIER_PAD, sy,
                                dx - BEZIER_PAD, dy, dx, dy,
                                2.0f, nk_rgb(180, 180, 180));
            }
        }

        /* ---- Draw temporary curve while linking ---- */
        if (linking_active) {
            struct gnode *sn = &g_nodes[linking_src_node];
            float sx = sn->x + NODE_W + ox;
            float sy = pin_y(sn, linking_src_slot, 1) + oy;
            float mx = in->mouse.pos.x;
            float my = in->mouse.pos.y;
            nk_stroke_curve(canvas, sx, sy, sx + BEZIER_PAD, sy,
                            mx - BEZIER_PAD, my, mx, my,
                            2.0f, nk_rgb(255, 255, 0));
        }

        /* ---- Process input and draw nodes ---- */
        int mx = (int)in->mouse.pos.x;
        int my = (int)in->mouse.pos.y;
        int mouse_click = nk_input_mouse_clicked(in, NK_BUTTON_LEFT,
                                                 nk_layout_space_bounds(ctx));
        int mouse_down = nk_input_is_mouse_down(in, NK_BUTTON_LEFT);

        if (mouse_click) {
            drag_node = -1;
            /* Check output pin hit (right edge of node). */
            for (int i = 0; i < g_count; i++) {
                struct gnode *n = &g_nodes[i];
                if (node_outputs(n->kind) == 0) continue;
                float px = n->x + NODE_W - PIN_R + ox;
                float py = pin_y(n, 0, 1) + oy;
                float dx = (float)mx - px;
                float dy = (float)my - py;
                if (dx * dx + dy * dy <= (float)(PIN_R + 3) * (float)(PIN_R + 3)) {
                    linking_active = 1;
                    linking_src_node = i;
                    linking_src_slot = 0;
                    break;
                }
            }
            /* Check input pin hit (left edge of node) — clear the link. */
            if (!linking_active) {
                for (int i = 0; i < g_count; i++) {
                    struct gnode *n = &g_nodes[i];
                    int ni = node_inputs(n->kind);
                    for (int k = 0; k < ni; k++) {
                        float px = n->x + PIN_R + ox;
                        float py = pin_y(n, k, 0) + oy;
                        float dx = (float)mx - px;
                        float dy = (float)my - py;
                        if (dx * dx + dy * dy <= (float)(PIN_R + 3) * (float)(PIN_R + 3)) {
                            n->in[k] = -1;
                            g_selected = i;
                            drag_node = -2; /* sentinel: hit a pin, skip body drag */
                            break;
                        }
                    }
                    if (drag_node == -2) break;
                }
            }
            /* Check body hit — select and start dragging. */
            if (!linking_active && drag_node != -2) {
                for (int i = 0; i < g_count; i++) {
                    struct gnode *n = &g_nodes[i];
                    float h = node_h(n);
                    float bx = n->x + ox, by = n->y + oy;
                    if ((float)mx >= bx && (float)mx <= bx + NODE_W &&
                        (float)my >= by && (float)my <= by + h) {
                        drag_node = i;
                        g_selected = i;
                        drag_ox = (float)mx - bx;
                        drag_oy = (float)my - by;
                        break;
                    }
                }
            }
        }

        /* Complete link on mouse release over an input pin. */
        if (linking_active && nk_input_is_mouse_released(in, NK_BUTTON_LEFT)) {
            for (int i = 0; i < g_count; i++) {
                struct gnode *n = &g_nodes[i];
                int ni = node_inputs(n->kind);
                for (int k = 0; k < ni; k++) {
                    float px = n->x + PIN_R + ox;
                    float py = pin_y(n, k, 0) + oy;
                    float dx = (float)mx - px;
                    float dy = (float)my - py;
                    if (dx * dx + dy * dy <= (float)(PIN_R + 4) * (float)(PIN_R + 4)) {
                        if (i != linking_src_node)
                            n->in[k] = linking_src_node;
                        g_selected = i;
                    }
                }
            }
            linking_active = 0;
        }

        /* Cancel linking on release outside any input pin. */
        if (linking_active && !mouse_down) {
            linking_active = 0;
        }

        /* Drag node body. */
        if (mouse_down && drag_node >= 0 && drag_node < g_count) {
            struct gnode *n = &g_nodes[drag_node];
            n->x = (float)mx - drag_ox - ox;
            n->y = (float)my - drag_oy - oy;
        }
        if (!mouse_down) drag_node = -1;

        /* ---- Draw nodes (groups + pin circles) ---- */
        for (int i = 0; i < g_count; i++) {
            struct gnode *n = &g_nodes[i];
            int ni = node_inputs(n->kind);
            int no = node_outputs(n->kind);
            float h = node_h(n);

            nk_layout_space_push(ctx, nk_rect(n->x, n->y, NODE_W, h));
            if (nk_group_begin_titled(ctx, (const char *)&i, kind_name(n->kind),
                                      NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR)) {
                /* Title bar colour strip + selection outline. */
                struct nk_color col = kind_color(n->kind);
                struct nk_rect title_bounds = nk_layout_space_rect_to_screen(
                    ctx, nk_rect(n->x, n->y, NODE_W, TITLE_H));
                nk_fill_rect(canvas, title_bounds, 0, col);
                if (i == g_selected)
                    nk_stroke_rect(canvas, nk_layout_space_rect_to_screen(
                        ctx, nk_rect(n->x, n->y, NODE_W, h)), 0, 2.0f,
                        nk_rgb(255, 255, 0));

                /* Node content. */
                if (n->kind == G_NUM) {
                    nk_layout_row_dynamic(ctx, 14, 1);
                    char buf[32];
                    snprintf(buf, sizeof(buf), "%lld", n->ival);
                    nk_label(ctx, buf, NK_TEXT_LEFT);
                    if (no > 0) {
                        nk_layout_row_dynamic(ctx, 14, 1);
                        nk_label(ctx, "-> output", NK_TEXT_LEFT);
                    }
                } else if (n->kind == G_STR) {
                    nk_layout_row_dynamic(ctx, 14, 1);
                    char buf[40];
                    snprintf(buf, sizeof(buf), "\"%.20s\"", n->sval);
                    nk_label(ctx, buf, NK_TEXT_LEFT);
                    if (no > 0) {
                        nk_layout_row_dynamic(ctx, 14, 1);
                        nk_label(ctx, "-> output", NK_TEXT_LEFT);
                    }
                } else {
                    int rows = ni > 3 ? ni : 3;
                    for (int k = 0; k < rows && k < 3; k++) {
                        nk_layout_row_dynamic(ctx, 14, 1);
                        char pin[40];
                        if (k < ni) {
                            if (n->in[k] >= 0)
                                snprintf(pin, sizeof(pin), "<- node %d", n->in[k]);
                            else if (n->use_lit[k])
                                snprintf(pin, sizeof(pin), "=%lld", n->lit[k]);
                            else
                                snprintf(pin, sizeof(pin), "(open)");
                        } else {
                            snprintf(pin, sizeof(pin), " ");
                        }
                        nk_label(ctx, pin, NK_TEXT_LEFT);
                    }
                    if (n->kind == G_PRINT && n->sval[0]) {
                        nk_layout_row_dynamic(ctx, 14, 1);
                        char fb[40];
                        snprintf(fb, sizeof(fb), "fmt %.20s", n->sval);
                        nk_label(ctx, fb, NK_TEXT_LEFT);
                    } else if (no > 0) {
                        nk_layout_row_dynamic(ctx, 14, 1);
                        nk_label(ctx, "-> output", NK_TEXT_LEFT);
                    }
                }
                nk_group_end(ctx);
            }

            /* ---- Draw pin circles on canvas ---- */
            for (int s = 0; s < no; s++) {
                struct nk_rect circle;
                circle.x = n->x + NODE_W - PIN_R + ox;
                circle.y = pin_y(n, s, 1) - PIN_R + oy;
                circle.w = PIN_DIAM;
                circle.h = PIN_DIAM;
                nk_fill_circle(canvas, circle, nk_rgb(100, 100, 100));
            }
            for (int k = 0; k < ni; k++) {
                struct nk_rect circle;
                circle.x = n->x - PIN_R + ox;
                circle.y = pin_y(n, k, 0) - PIN_R + oy;
                circle.w = PIN_DIAM;
                circle.h = PIN_DIAM;
                nk_fill_circle(canvas, circle,
                    n->in[k] >= 0 ? nk_rgb(80, 200, 80) : nk_rgb(100, 100, 100));
            }
        }

        nk_layout_space_end(ctx);
        nk_end(ctx);
    }
}

/* ---- main loop ---- */
static void gui_run(void) {
    unsigned char pal768[768];
    int fw, fh, fp;

    nk_sys_vga_mode(1);
    nk_sys_kbd_raw(1);
    nk_build_palette(pal768);
    nk_sys_palette(pal768);
    nk_sys_fb_info(&fw, &fh, &fp);

    struct nk_user_font font = nk_minios_font();
    struct nk_context ctx;
    if (!nk_init_fixed(&ctx, ui_memory, UI_MEMORY, &font)) {
        printf("nuklear: init failed\n");
        nk_sys_kbd_raw(0);
        nk_sys_vga_mode(0);
        return;
    }

    graph_add(G_NUM); g_nodes[0].ival = 2;
    graph_add(G_NUM); g_nodes[1].ival = 3;
    graph_add(G_ADD); g_nodes[2].in[0] = 0; g_nodes[2].in[1] = 1;
    graph_add(G_MUL); g_nodes[3].in[0] = 2; g_nodes[3].in[1] = 2;
    graph_add(G_PRINT); g_nodes[4].in[0] = 3;

    int origin[2] = {0, 0};
    while (!ui_quit) {
        nk_input_begin(&ctx);
        nk_poll_input(&ctx);
        nk_input_end(&ctx);

        ui_build(&ctx, (float)NK_W, (float)NK_H);

        nk_rasterize(&ctx);
        if (nk_sys_nk_frame(origin) == 0)
            nk_set_window_origin(origin[0], origin[1]);
        nk_clear(&ctx);

        unsigned t0 = (unsigned)nk_sys_time_ms();
        while ((unsigned)nk_sys_time_ms() - t0 < 8) {
            __asm__ volatile("pause");
        }
    }

    nk_free(&ctx);
    nk_sys_kbd_raw(0);
    nk_sys_vga_mode(0);
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "--selftest") == 0) {
        unsigned char pal768[768];
        int fw, fh, fp;
        nk_sys_vga_mode(1);
        nk_sys_kbd_raw(1);
        nk_build_palette(pal768);
        nk_sys_palette(pal768);
        nk_sys_fb_info(&fw, &fh, &fp);
        struct nk_user_font font = nk_minios_font();
        struct nk_context ctx;
        if (!nk_init_fixed(&ctx, ui_memory, UI_MEMORY, &font)) {
            printf("nuklear: init failed\n");
            return 1;
        }
        nk_input_begin(&ctx);
        nk_input_end(&ctx);
        ui_build(&ctx, (float)NK_W, (float)NK_H);
        nk_rasterize(&ctx);
        NK_BACKBUF[0] = 0xF0;
        int origin[2] = {0, 0};
        if (nk_sys_nk_frame(origin) != 0) {
            printf("nuklear: frame syscall failed\n");
            return 1;
        }
        int mouse[4] = {0, 0, 0, 0};
        if (nk_sys_mouse(mouse) != 0) {
            printf("nuklear: mouse syscall failed\n");
            return 1;
        }
        if (nk_sys_mouse_badptr() >= 0) {
            printf("nuklear: mouse accepted a kernel pointer\n");
            return 1;
        }
        volatile uint8_t *fb = (volatile uint8_t *)MINIOS_FB_ADDR;
        int ox = origin[0], oy = origin[1];
        /* Bytes per pixel from the pitch heuristic (pitch is bytes per
         * scanline): 1 in the 8-bit mode, 3/4 in true color. In true color
         * the composited pixel is the palette RGB, not the index. */
        int bpx = (fw > 0 && fp % fw == 0) ? fp / fw : 1;
        int landed = 0;
        if (ox >= 0 && oy >= 0 && ox < fw && oy < fh) {
            volatile uint8_t *px = fb + oy * fp + ox * bpx;
            if (bpx == 1) {
                landed = (px[0] == NK_BACKBUF[0]);
            } else {
                unsigned pi = (unsigned)NK_BACKBUF[0] * 3;
                landed = (px[0] == pal768[pi + 2] &&
                          px[1] == pal768[pi + 1] &&
                          px[2] == pal768[pi + 0]);
            }
        }
        if (!landed) {
            printf("nuklear: composite did not land at the window origin\n");
            return 1;
        }
        nk_free(&ctx);
        nk_sys_kbd_raw(0);
        nk_sys_vga_mode(0);
        printf("nuklear: frame ok (%dx%d)\n", NK_W, NK_H);
        return 0;
    }

    if (argc > 1 && strcmp(argv[1], "--pointer-test") == 0) {
        unsigned char pal768[768];
        int fw, fh, fp;
        nk_sys_vga_mode(1);
        nk_sys_kbd_raw(1);
        nk_build_palette(pal768);
        nk_sys_palette(pal768);
        nk_sys_fb_info(&fw, &fh, &fp);
        int mouse[4] = {0, 0, 0, 0};
        if (nk_sys_mouse(mouse) != 0) {
            printf("nuklear: mouse syscall failed\n");
            nk_sys_kbd_raw(0);
            nk_sys_vga_mode(0);
            return 1;
        }
        int origin[2] = {0, 0};
        if (nk_sys_nk_frame(origin) != 0) {
            printf("nuklear: frame syscall failed\n");
            nk_sys_kbd_raw(0);
            nk_sys_vga_mode(0);
            return 1;
        }
        volatile uint8_t *fb = (volatile uint8_t *)MINIOS_FB_ADDR;
        int mx = mouse[0], my = mouse[1];
        if (mx < 0 || my < 0 || mx >= fw || my >= fh) {
            printf("nuklear: mouse position out of range (%d,%d)\n", mx, my);
            nk_sys_kbd_raw(0);
            nk_sys_vga_mode(0);
            return 1;
        }
        int ok = 0;
        int bpx = (fw > 0 && fp % fw == 0) ? fp / fw : 1;
        for (int k = 0; k < 8; k++) {
            int px = mx - 6 + k;
            int py = my;
            volatile uint8_t *pp;
            if (px < 0 || px >= fw || py < 0 || py >= fh) continue;
            pp = fb + py * fp + px * bpx;
            /* Cursor white is index 10 (255,255,255): a bare index match
             * in 8-bit mode, an RGB-white match in true color. */
            if (bpx == 1) {
                if (pp[0] == 10) { ok = 1; break; }
            } else if (pp[0] == 255 && pp[1] == 255 && pp[2] == 255) {
                ok = 1; break;
            }
        }
        if (!ok) {
            printf("nuklear: pointer missing near (%d,%d)\n", mx, my);
            nk_sys_kbd_raw(0);
            nk_sys_vga_mode(0);
            return 1;
        }
        nk_sys_kbd_raw(0);
        nk_sys_vga_mode(0);
        printf("nuklear: pointer ok (%d,%d)\n", mx, my);
        return 0;
    }

    if (argc > 1 && strcmp(argv[1], "--demo") == 0) {
        if (argc < 3) { printf("usage: nuklear --demo <out.cvm>\n"); return 2; }
        graph_clear();
        graph_add(G_NUM); g_nodes[0].ival = 2;
        graph_add(G_NUM); g_nodes[1].ival = 3;
        graph_add(G_ADD); g_nodes[2].in[0] = 0; g_nodes[2].in[1] = 1;
        graph_add(G_NUM); g_nodes[3].ival = 4;
        graph_add(G_MUL); g_nodes[4].in[0] = 2; g_nodes[4].in[1] = 3;
        graph_add(G_PRINT); g_nodes[5].in[0] = 4;
        int rc = compile_to(argv[2]);
        printf("%s\n", g_status);
        return rc == 0 ? 0 : 1;
    }

    if (argc > 1 && strcmp(argv[1], "--compile") == 0) {
        if (argc < 4) { printf("usage: nuklear --compile <graph.txt> <out.cvm>\n"); return 2; }
        if (parse_graph_file(argv[2]) < 0) {
            printf("nuklear: cannot parse %s\n", argv[2]);
            return 1;
        }
        int rc = compile_to(argv[3]);
        printf("%s\n", g_status);
        return rc == 0 ? 0 : 1;
    }

    if (argc > 1 && strcmp(argv[1], "--help") == 0) {
        printf("nuklear: node editor that compiles graphs to CVM bytecode\n");
        printf("  (no args)        GUI editor\n");
        printf("  --demo out.cvm   compile a demo graph\n");
        printf("  --compile g out  compile a text graph\n");
        printf("  --selftest       render one frame and exit\n");
        return 0;
    }

    gui_run();
    return 0;
}
