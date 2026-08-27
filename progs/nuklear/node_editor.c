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
    n->x = 30.0f + (float)(g_count % 6) * 130.0f;
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
static int link_src = -1;
static int link_src_is_out = 0;

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
        nk_layout_space_begin(ctx, NK_STATIC, canvas_h, MAX_NODES);

        struct nk_input *in = &ctx->input;
        int mx = (int)in->mouse.pos.x;
        int my = (int)in->mouse.pos.y;
        int mouse_down = nk_input_is_mouse_down(in, NK_BUTTON_LEFT);
        int mouse_click = nk_input_mouse_clicked(in, NK_BUTTON_LEFT, nk_rect(0,0,win_w,win_h));

        /* Handle node drag and pin connection by manual hit testing. */
        if (mouse_click) {
            drag_node = -1;
            link_src = -1;
            for (int i = 0; i < g_count; i++) {
                struct gnode *n = &g_nodes[i];
                float nx = n->x, ny = n->y;
                /* output pin on the right edge */
                if (mx >= nx + 120 && mx <= nx + 140 &&
                    my >= ny + 16 && my <= ny + 32) {
                    link_src = i;
                    link_src_is_out = 1;
                    break;
                }
                /* input pins on the left edge */
                int ni = node_inputs(n->kind);
                for (int k = 0; k < ni; k++) {
                    if (mx >= nx - 20 && mx <= nx &&
                        my >= ny + 16 + k * 24 && my <= ny + 32 + k * 24) {
                        if (link_src >= 0 && link_src_is_out && i != link_src) {
                            n->in[k] = link_src;
                        }
                        link_src = -1;
                        break;
                    }
                }
                /* body: start dragging */
                if (mx >= nx && mx <= nx + 120 && my >= ny && my <= ny + 16 + ni * 24) {
                    if (!(mx >= nx + 120 && mx <= nx + 140)) {
                        drag_node = i;
                        drag_ox = mx - nx;
                        drag_oy = my - ny;
                    }
                }
            }
        }
        if (mouse_down && drag_node >= 0) {
            struct gnode *n = &g_nodes[drag_node];
            n->x = (float)(mx - drag_ox);
            n->y = (float)(my - drag_oy);
        }
        if (!mouse_down) drag_node = -1;

        /* Draw the nodes. */
        for (int i = 0; i < g_count; i++) {
            struct gnode *n = &g_nodes[i];
            int ni = node_inputs(n->kind);
            float h = 16.0f + (float)ni * 24.0f + 12.0f;
            nk_layout_space_push(ctx, nk_rect(n->x, n->y, 120, h));
            if (nk_group_begin_titled(ctx, (const char *)&i, kind_name(n->kind),
                                      NK_WINDOW_BORDER | NK_WINDOW_NO_SCROLLBAR)) {
                nk_layout_row_dynamic(ctx, 14, 1);
                if (n->kind == G_NUM) {
                    char buf[32];
                    snprintf(buf, sizeof(buf), "%lld", n->ival);
                    nk_label(ctx, buf, NK_TEXT_LEFT);
                    nk_layout_row_dynamic(ctx, 18, 1);
                    nk_property_int(ctx, "#", -2147483647, (int *)&n->ival,
                                    2147483647, 1, 1);
                } else {
                    for (int k = 0; k < ni; k++) {
                        char pin[32];
                        if (n->in[k] >= 0) snprintf(pin, sizeof(pin), "in %d", n->in[k]);
                        else snprintf(pin, sizeof(pin), "(open)");
                        nk_label(ctx, pin, NK_TEXT_LEFT);
                    }
                }
            }
            nk_group_end(ctx);
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

        if (nk_input_is_key_pressed(&ctx.input, NK_KEY_SCROLL_DOWN))
            ui_quit = 0; /* placeholder: wheel does not quit */

        nk_rasterize(&ctx);
        if (nk_sys_nk_frame(origin) == 0)
            nk_set_window_origin(origin[0], origin[1]);
        nk_clear(&ctx);

        /* Small frame delay (about 60 fps). */
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
        /* One frame through the whole graphics pipeline, no interaction.
         * The kernel composites the back-buffer into the desktop framebuffer
         * at the window content origin, so writing a marker pixel into the
         * back-buffer and reading it back from the framebuffer proves the
         * full chain: rasterize -> SYS_NK_FRAME -> composite -> visible. */
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
        volatile uint8_t *fb = (volatile uint8_t *)0x1F00000UL;
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
        /* One composite with the compositor pointer contract exercised: while
         * a graphics program owns the display the kernel draws the desktop
         * pointer on the frame syscall path (SYS_NK_FRAME), so the pointer
         * stays visible instead of vanishing when Nuklear takes over. We
         * composite a frame, then read the framebuffer at the arrow tip of
         * the current mouse position and require the cursor colour (desktop
         * white, index 10). A mutant that drops the cursor draw is killed. */
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
        volatile uint8_t *fb = (volatile uint8_t *)0x1F00000UL;
        int mx = mouse[0], my = mouse[1];
        if (mx < 0 || my < 0 || mx >= fw || my >= fh) {
            printf("nuklear: mouse position out of range (%d,%d)\n", mx, my);
            nk_sys_kbd_raw(0);
            nk_sys_vga_mode(0);
            return 1;
        }
        /* The arrow sprite's tip row (bitmap row 7) is drawn at the mouse
         * position; its set bits land at sprite columns 4-5, i.e. pixels
         * (mx-2, my) and (mx-1, my). The cursor colour is desktop white
         * (index 10). */
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
        graph_add(G_NUM); g_nodes[0].ival = 2;          /* 0: 2 */
        graph_add(G_NUM); g_nodes[1].ival = 3;          /* 1: 3 */
        graph_add(G_ADD); g_nodes[2].in[0] = 0; g_nodes[2].in[1] = 1; /* 2: 2+3 */
        graph_add(G_NUM); g_nodes[3].ival = 4;          /* 3: 4 */
        graph_add(G_MUL); g_nodes[4].in[0] = 2; g_nodes[4].in[1] = 3; /* 4: (2+3)*4 */
        graph_add(G_PRINT); g_nodes[5].in[0] = 4;       /* 5: print */
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