/* node_editor.c — visual node editor that compiles to CVM bytecode.
 *
 * A ring-3 Nuklear application (built exactly like DOOM: host gcc -static,
 * ships on MiniFS) that lets you place dataflow nodes on a canvas, wire
 * outputs to inputs, and compile the graph into a .cvm module that the CVM
 * interpreter runs in the OS. It is the "low-code tool for the CVM":
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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "nuklear.h"
#include "nuklear_minios.h"
#include "cvm_emit.h"

/* ---- Graph model ---- */
#define MAX_NODES 64

enum {
    G_NUM, G_ADD, G_SUB, G_MUL, G_DIV, G_NEG, G_PRINT, G_EXIT
};

struct gnode {
    int kind;
    long long ival;
    int in[2];
    float x, y;
};

static struct gnode g_nodes[MAX_NODES];
static int g_count;
static char g_status[128];

static void graph_clear(void) {
    g_count = 0;
    g_status[0] = '\0';
}

static int graph_add(int kind) {
    if (g_count >= MAX_NODES) return -1;
    struct gnode *n = &g_nodes[g_count];
    memset(n, 0, sizeof(*n));
    n->kind = kind;
    n->in[0] = n->in[1] = -1;
    n->x = 30.0f + (float)(g_count % 6) * 160.0f;
    n->y = 60.0f + (float)(g_count / 6) * 120.0f;
    if (kind == G_NUM) n->ival = 1;
    return g_count++;
}

static const char *kind_name(int k) {
    switch (k) {
    case G_NUM:   return "Number";
    case G_ADD:   return "Add";
    case G_SUB:   return "Sub";
    case G_MUL:   return "Mul";
    case G_DIV:   return "Div";
    case G_NEG:   return "Neg";
    case G_PRINT: return "Print";
    case G_EXIT:  return "Exit";
    }
    return "?";
}

static int node_inputs(int k) {
    switch (k) {
    case G_ADD: case G_SUB: case G_MUL: case G_DIV: return 2;
    case G_NEG: case G_PRINT: case G_EXIT: return 1;
    }
    return 0;
}

/* Node colors: distinct hue per type, low saturation for readability. */
static struct nk_color kind_color(int k) {
    switch (k) {
    case G_NUM:   return nk_rgb(70, 130, 180);   /* steel blue */
    case G_ADD:   return nk_rgb(60, 179, 113);   /* medium sea green */
    case G_SUB:   return nk_rgb(210, 105, 105);  /* indian red */
    case G_MUL:   return nk_rgb(186, 135, 89);   /* peru */
    case G_DIV:   return nk_rgb(147, 112, 219);  /* medium purple */
    case G_NEG:   return nk_rgb(255, 165, 0);    /* orange */
    case G_PRINT: return nk_rgb(100, 149, 237);  /* cornflower blue */
    case G_EXIT:  return nk_rgb(220, 80, 60);    /* tomato */
    }
    return nk_rgb(150, 150, 150);
}

/* Map the graph into the compiler's node array. Returns node count or <0. */
static int graph_to_compiler(struct cvm_node *out, int cap) {
    if (g_count > cap) return -1;
    for (int i = 0; i < g_count; i++) {
        out[i].type = (g_nodes[i].kind == G_ADD) ? NODE_ADD :
                      (g_nodes[i].kind == G_SUB) ? NODE_SUB :
                      (g_nodes[i].kind == G_MUL) ? NODE_MUL :
                      (g_nodes[i].kind == G_DIV) ? NODE_DIV :
                      (g_nodes[i].kind == G_NEG) ? NODE_NEG :
                      (g_nodes[i].kind == G_PRINT) ? NODE_PRINT :
                      (g_nodes[i].kind == G_EXIT) ? NODE_EXIT : NODE_NUM;
        out[i].ival = g_nodes[i].ival;
        out[i].in[0] = g_nodes[i].in[0];
        out[i].in[1] = g_nodes[i].in[1];
    }
    return g_count;
}

/* Compile the current graph to a file. Returns 0 on success. */
static int compile_to(const char *path) {
    struct cvm_node cvm[MAX_NODES];
    int n = graph_to_compiler(cvm, MAX_NODES);
    if (n < 0) { snprintf(g_status, sizeof(g_status), "graph too large"); return -1; }
    unsigned char *mod;
    size_t sz;
    char err[128];
    if (cvm_compile(cvm, n, &mod, &sz, err, sizeof(err)) < 0) {
        snprintf(g_status, sizeof(g_status), "compile: %.100s", err);
        return -1;
    }
    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        snprintf(g_status, sizeof(g_status), "cannot open %s", path);
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
        snprintf(g_status, sizeof(g_status), "write error");
        return -1;
    }
    snprintf(g_status, sizeof(g_status), "wrote %s (%zu bytes)", path, sz);
    return 0;
}

/* ---- Headless graph text format ----
 *   num a 5          add b a c        print b        exit b
 * Each line: <type> <name> [value|in1 [in2]]. Inputs are earlier-defined
 * node names; forward references are rejected. */
static int parse_graph_file(const char *path) {
    FILE *f = fopen(path, "r");
    if (!f) return -1;
    graph_clear();
    static char names[MAX_NODES][16];
    char line[128];
    int rc = 0;
    int resolve(const char *nme, int upto) {
        for (int k = 0; k < upto; k++)
            if (strcmp(names[k], nme) == 0) return k;
        return -2;
    }
    while (fgets(line, sizeof(line), f)) {
        char *p = line;
        while (*p == ' ' || *p == '\t') p++;
        if (*p == '#' || *p == '\n' || *p == '\r' || *p == 0) continue;
        char type[16], name[16], a[16], b[16];
        int consumed = sscanf(p, "%15s %15s %15s %15s", type, name, a, b);
        if (consumed < 2) { rc = -1; break; }
        int kind;
        if      (!strcmp(type, "num"))   kind = G_NUM;
        else if (!strcmp(type, "add"))   kind = G_ADD;
        else if (!strcmp(type, "sub"))   kind = G_SUB;
        else if (!strcmp(type, "mul"))   kind = G_MUL;
        else if (!strcmp(type, "div"))   kind = G_DIV;
        else if (!strcmp(type, "neg"))   kind = G_NEG;
        else if (!strcmp(type, "print")) kind = G_PRINT;
        else if (!strcmp(type, "exit"))  kind = G_EXIT;
        else { rc = -1; break; }
        if (g_count >= MAX_NODES) { rc = -1; break; }
        int idx = g_count;
        snprintf(names[idx], sizeof(names[idx]), "%s", name);
        graph_add(kind);
        if (kind == G_NUM) {
            if (consumed < 3) { rc = -1; break; }
            g_nodes[idx].ival = atoll(a);
        } else {
            if (node_inputs(kind) == 2) {
                if (consumed < 4) { rc = -1; break; }
                g_nodes[idx].in[0] = resolve(a, idx);
                g_nodes[idx].in[1] = resolve(b, idx);
                if (g_nodes[idx].in[0] < 0 || g_nodes[idx].in[1] < 0) { rc = -1; break; }
            } else {
                if (consumed < 3) { rc = -1; break; }
                g_nodes[idx].in[0] = resolve(a, idx);
                if (g_nodes[idx].in[0] < 0) { rc = -1; break; }
            }
        }
    }
    fclose(f);
    return rc;
}

/* ---- Nuklear UI state ---- */
#define UI_MEMORY (4 * 1024 * 1024)
static char ui_memory[UI_MEMORY];

static int ui_quit;
static int drag_node = -1;
static float drag_ox, drag_oy;

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
    int no = (n->kind == G_NUM) ? 0 : 1;
    int count = is_output ? no : ni;
    float body_h = (float)count * 20.0f + 8.0f;
    float total = TITLE_H + body_h;
    float space = total / (float)(count + 1);
    return n->y + space * (float)(slot + 1);
}

static void ui_build(struct nk_context *ctx, float win_w, float win_h) {
    if (nk_begin_titled(ctx, "nuklear", "Node Editor", nk_rect(0, 0, win_w, win_h),
                        NK_WINDOW_NO_SCROLLBAR)) {

        nk_menubar_begin(ctx);
        nk_layout_row_static(ctx, 24, 70, 8);
        if (nk_button_label(ctx, "Number")) graph_add(G_NUM);
        if (nk_button_label(ctx, "Add"))    graph_add(G_ADD);
        if (nk_button_label(ctx, "Sub"))    graph_add(G_SUB);
        if (nk_button_label(ctx, "Mul"))    graph_add(G_MUL);
        if (nk_button_label(ctx, "Div"))    graph_add(G_DIV);
        if (nk_button_label(ctx, "Neg"))    graph_add(G_NEG);
        if (nk_button_label(ctx, "Print"))  graph_add(G_PRINT);
        if (nk_button_label(ctx, "Exit"))   graph_add(G_EXIT);
        nk_menubar_end(ctx);

        nk_layout_row_static(ctx, 24, 80, 4);
        if (nk_button_label(ctx, "Compile")) compile_to("cvm/nodes.cvm");
        if (nk_button_label(ctx, "Run")) {
            compile_to("cvm/nodes.cvm");
        }
        if (nk_button_label(ctx, "Clear"))  graph_clear();
        if (nk_button_label(ctx, "Quit"))   ui_quit = 1;

        nk_layout_row_dynamic(ctx, 16, 1);
        nk_label(ctx, g_status[0] ? g_status : "connect nodes, then Compile",
                 NK_TEXT_LEFT);

        /* Canvas with absolute node placement. */
        float canvas_h = win_h - 80.0f;
        if (canvas_h < 100) canvas_h = 100;
        nk_layout_space_begin(ctx, NK_STATIC, canvas_h, g_count + 32);

        struct nk_command_buffer *canvas = nk_window_get_canvas(ctx);
        struct nk_rect canvas_bounds = nk_layout_space_bounds(ctx);
        struct nk_input *in = &ctx->input;

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
                float sx = sn->x + NODE_W;
                float sy = pin_y(sn, 0, 1);
                float dx = n->x;
                float dy = pin_y(n, k, 0);
                nk_stroke_curve(canvas, sx, sy, sx + BEZIER_PAD, sy,
                                dx - BEZIER_PAD, dy, dx, dy,
                                2.0f, nk_rgb(180, 180, 180));
            }
        }

        /* ---- Draw temporary curve while linking ---- */
        if (linking_active) {
            struct gnode *sn = &g_nodes[linking_src_node];
            float sx = sn->x + NODE_W;
            float sy = pin_y(sn, linking_src_slot, 1);
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
                float px = n->x + NODE_W - PIN_R;
                float py = pin_y(n, 0, 1);
                float dx = (float)mx - px;
                float dy = (float)my - py;
                if (dx * dx + dy * dy <= (float)(PIN_R + 3) * (float)(PIN_R + 3)) {
                    linking_active = 1;
                    linking_src_node = i;
                    linking_src_slot = 0;
                    break;
                }
            }
            /* Check input pin hit (left edge of node) — complete a link. */
            if (!linking_active) {
                for (int i = 0; i < g_count; i++) {
                    struct gnode *n = &g_nodes[i];
                    int ni = node_inputs(n->kind);
                    for (int k = 0; k < ni; k++) {
                        float px = n->x + PIN_R;
                        float py = pin_y(n, k, 0);
                        float dx = (float)mx - px;
                        float dy = (float)my - py;
                        if (dx * dx + dy * dy <= (float)(PIN_R + 3) * (float)(PIN_R + 3)) {
                            /* Remove existing link on this slot. */
                            n->in[k] = -1;
                            drag_node = -2; /* sentinel: we hit a pin, skip body drag */
                            break;
                        }
                    }
                    if (drag_node == -2) break;
                }
            }
            /* Check body hit — start dragging. */
            if (!linking_active && drag_node != -2) {
                for (int i = 0; i < g_count; i++) {
                    struct gnode *n = &g_nodes[i];
                    int ni = node_inputs(n->kind);
                    float body_h = TITLE_H + (float)ni * 20.0f + 8.0f;
                    if ((float)mx >= n->x && (float)mx <= n->x + NODE_W &&
                        (float)my >= n->y && (float)my <= n->y + body_h) {
                        drag_node = i;
                        drag_ox = (float)mx - n->x;
                        drag_oy = (float)my - n->y;
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
                    float px = n->x + PIN_R;
                    float py = pin_y(n, k, 0);
                    float dx = (float)mx - px;
                    float dy = (float)my - py;
                    if (dx * dx + dy * dy <= (float)(PIN_R + 4) * (float)(PIN_R + 4)) {
                        if (i != linking_src_node)
                            n->in[k] = linking_src_node;
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
            n->x = (float)mx - drag_ox;
            n->y = (float)my - drag_oy;
        }
        if (!mouse_down) drag_node = -1;

        /* ---- Draw nodes (groups + pin circles) ---- */
        for (int i = 0; i < g_count; i++) {
            struct gnode *n = &g_nodes[i];
            int ni = node_inputs(n->kind);
            int no = (n->kind == G_NUM) ? 0 : 1;
            float body_h = (float)ni * 20.0f + 8.0f;
            float h = TITLE_H + body_h;

            nk_layout_space_push(ctx, nk_rect(n->x, n->y, NODE_W, h));
            if (nk_group_begin_titled(ctx, (const char *)&i, kind_name(n->kind),
                                      NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR)) {
                /* Title bar colour strip. */
                struct nk_color col = kind_color(n->kind);
                struct nk_rect title_bounds = nk_layout_space_rect_to_screen(
                    ctx, nk_rect(n->x, n->y, NODE_W, TITLE_H));
                nk_fill_rect(canvas, title_bounds, 0, col);

                /* Node content. */
                if (n->kind == G_NUM) {
                    nk_layout_row_dynamic(ctx, 14, 1);
                    char buf[32];
                    snprintf(buf, sizeof(buf), "%lld", n->ival);
                    nk_label(ctx, buf, NK_TEXT_LEFT);
                    nk_layout_row_dynamic(ctx, 18, 1);
                    nk_property_int(ctx, "#", -2147483647, (int *)&n->ival,
                                    2147483647, 1, 1);
                } else {
                    for (int k = 0; k < ni; k++) {
                        nk_layout_row_dynamic(ctx, 16, 1);
                        char pin[32];
                        if (n->in[k] >= 0)
                            snprintf(pin, sizeof(pin), "<- node %d", n->in[k]);
                        else
                            snprintf(pin, sizeof(pin), "(open)");
                        nk_label(ctx, pin, NK_TEXT_LEFT);
                    }
                    if (no > 0) {
                        nk_layout_row_dynamic(ctx, 16, 1);
                        nk_label(ctx, "-> output", NK_TEXT_LEFT);
                    }
                }
                nk_group_end(ctx);
            }

            /* ---- Draw pin circles on canvas ---- */
            /* Output pin (right edge). */
            for (int s = 0; s < no; s++) {
                struct nk_rect circle;
                circle.x = n->x + NODE_W - PIN_R;
                circle.y = pin_y(n, s, 1) - PIN_R;
                circle.w = PIN_DIAM;
                circle.h = PIN_DIAM;
                nk_fill_circle(canvas, circle, nk_rgb(100, 100, 100));
            }
            /* Input pins (left edge). */
            for (int k = 0; k < ni; k++) {
                struct nk_rect circle;
                circle.x = n->x - PIN_R;
                circle.y = pin_y(n, k, 0) - PIN_R;
                circle.w = PIN_DIAM;
                circle.h = PIN_DIAM;
                nk_fill_circle(canvas, circle, nk_rgb(100, 100, 100));
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
        volatile uint8_t *fb = (volatile uint8_t *)0x0B200000UL;
        int ox = origin[0], oy = origin[1];
        if (ox < 0 || oy < 0 || ox >= fw || oy >= fh ||
            fb[oy * fp + ox] != NK_BACKBUF[0]) {
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
        volatile uint8_t *fb = (volatile uint8_t *)0x0B200000UL;
        int mx = mouse[0], my = mouse[1];
        if (mx < 0 || my < 0 || mx >= fw || my >= fh) {
            printf("nuklear: mouse position out of range (%d,%d)\n", mx, my);
            nk_sys_kbd_raw(0);
            nk_sys_vga_mode(0);
            return 1;
        }
        int ok = 0;
        for (int k = 0; k < 8; k++) {
            int px = mx - 6 + k;
            int py = my;
            if (px < 0 || px >= fw || py < 0 || py >= fh) continue;
            if (fb[py * fp + px] == 10) { ok = 1; break; }
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
