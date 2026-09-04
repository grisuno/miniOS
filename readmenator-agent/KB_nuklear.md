# Subsystem: nuklear

## progs/nuklear/cvm_emit.c
- Layer: utility
- Doc: cvm_emit.c — node-graph to CVM bytecode compiler.
- Language: c
- Symbols:
  - `codebuf` (struct, line 50)
  - `cb_push` (function, line 55) `static int cb_push(struct codebuf *cb, unsigned char c)`
  - `cb_u32` (function, line 67) `static int cb_u32(struct codebuf *cb, unsigned long v)`
  - `cb_i64` (function, line 73) `static int cb_i64(struct codebuf *cb, long long v)`
  - `topo_sort` (function, line 81) `static int topo_sort(const struct cvm_node *nodes, int n,
                     int *order, char *...`
  - `cvm_compile` (function, line 122) `int cvm_compile(const struct cvm_node *nodes, int n,
                unsigned char **out, size_t ...`
  - `w32` (function, line 257) `void w32(void *p, unsigned v)`
  - `CVM_MAGIC_0` (macro, line 23)
  - `CVM_MAGIC_1` (macro, line 24)
  - `CVM_MAGIC_2` (macro, line 25)
  - `CVM_MAGIC_3` (macro, line 26)
  - `CVM_VERSION_MAJOR` (macro, line 27)
  - `CVM_MODULE_HEADER_SIZE` (macro, line 28)
  - `CVM_FUNC_ENTRY_SIZE` (macro, line 29)
  - `CVM_GLOBAL_ENTRY_SIZE` (macro, line 30)
  - `CVM_NATIVE_ENTRY_SIZE` (macro, line 31)
  - `OP_PUSH_IMM64` (macro, line 34)
  - `OP_PUSH_IMM32` (macro, line 35)
  - `OP_PUSH_IMM8` (macro, line 36)
  - `OP_PUSH_LOCAL` (macro, line 37)
  - `OP_STORE_LOCAL` (macro, line 38)
  - `OP_ADD` (macro, line 39)
  - `OP_SUB` (macro, line 40)
  - `OP_MUL` (macro, line 41)
  - `OP_DIV` (macro, line 42)
  - `OP_NEG` (macro, line 43)
  - `OP_LEA_DATA` (macro, line 44)
  - `OP_CALL_NATIVE` (macro, line 45)
  - `OP_HALT` (macro, line 46)
  - `CVM_MAX_NODES` (macro, line 47)

## progs/nuklear/cvm_emit.h
- Layer: utility
- Doc: ifndef CVM_EMIT_H define CVM_EMIT_H  cvm_emit.h — node-graph compiler for CVM (cvm2 module format v2).
- Language: h
- Symbols:
  - `cvm_node` (struct, line 29)
  - `CVM_EMIT_H` (macro, line 2)

## progs/nuklear/node_editor.c
- Layer: infrastructure
- Doc: node_editor.c — visual node editor that compiles to CVM bytecode.
- Language: c
- Symbols:
  - `gnode` (struct, line 38)
  - `graph_clear` (function, line 48) `static void graph_clear(void)`
  - `graph_add` (function, line 53) `static int graph_add(int kind)`
  - `kind_name` (function, line 65) `static const char *kind_name(int k)`
  - `node_inputs` (function, line 79) `static int node_inputs(int k)`
  - `kind_color` (function, line 89) `static struct nk_color kind_color(int k)`
  - `graph_to_compiler` (function, line 104) `static int graph_to_compiler(struct cvm_node *out, int cap)`
  - `compile_to` (function, line 122) `static int compile_to(const char *path)`
  - `parse_graph_file` (function, line 159) `static int parse_graph_file(const char *path)`
  - `resolve` (function, line 166) `int resolve(const char *nme, int upto)`
  - `pin_y` (function, line 234) `static float pin_y(struct gnode *n, int slot, int is_output)`
  - `ui_build` (function, line 243) `static void ui_build(struct nk_context *ctx, float win_w, float win_h)`
  - `gui_run` (function, line 487) `static void gui_run(void)`
  - `main` (function, line 535) `int main(int argc, char **argv)`
  - `MAX_NODES` (macro, line 32)
  - `UI_MEMORY` (macro, line 213)
  - `NODE_W` (macro, line 226)
  - `TITLE_H` (macro, line 227)
  - `PIN_R` (macro, line 228)
  - `PIN_DIAM` (macro, line 229)
  - `BEZIER_PAD` (macro, line 230)
  - `GRID_SIZE` (macro, line 231)

## progs/nuklear/nuklear_minios.c
- Layer: utility
- Doc: nuklear_minios.c — MiniOS platform layer for Nuklear.
- Language: c
- Symbols:
  - `nk_sys_time_ms` (function, line 26) `long nk_sys_time_ms(void)`
  - `nk_sys_kbd` (function, line 31) `long nk_sys_kbd(void)`
  - `nk_sys_palette` (function, line 36) `long nk_sys_palette(const unsigned char *pal)`
  - `nk_sys_kbd_raw` (function, line 41) `long nk_sys_kbd_raw(int on)`
  - `nk_sys_vga_mode` (function, line 46) `long nk_sys_vga_mode(int on)`
  - `nk_sys_fb_info` (function, line 51) `long nk_sys_fb_info(int *w, int *h, int *pitch)`
  - `nk_sys_mouse` (function, line 58) `long nk_sys_mouse(int *xybw)`
  - `nk_sys_mouse_badptr` (function, line 63) `long nk_sys_mouse_badptr(void)`
  - `nk_sys_nk_frame` (function, line 71) `long nk_sys_nk_frame(int *origin)`
  - `pal_prepare` (function, line 143) `static void pal_prepare(void)`
  - `col_to_idx` (function, line 154) `static int col_to_idx(struct nk_color c)`
  - `set_clip` (function, line 272) `static void set_clip(int x, int y, int w, int h)`
  - `px` (function, line 282) `static void px(int x, int y, int c)`
  - `fill_rect` (function, line 289) `static void fill_rect(int x, int y, int w, int h, int c)`
  - `draw_line` (function, line 296) `static void draw_line(int x0, int y0, int x1, int y1, int th, int c)`
  - `fill_circle` (function, line 314) `static void fill_circle(int cx, int cy, int r, int c)`
  - `stroke_circle` (function, line 320) `static void stroke_circle(int cx, int cy, int r, int th, int c)`
  - `fill_poly` (function, line 339) `static void fill_poly(int *xs, int *ys, int n, int c)`
  - `stroke_poly` (function, line 361) `static void stroke_poly(int *xs, int *ys, int n, int th, int c)`
  - `draw_text` (function, line 368) `static void draw_text(int x, int y, const char *s, int len, int fg, int bg)`
  - `draw_arc` (function, line 382) `static void draw_arc(int cx, int cy, int r, float a0, float a1,
                     int filled, ...`
  - `nk_rasterize` (function, line 403) `void nk_rasterize(struct nk_context *ctx)`
  - `nk_foreach` (function, line 408) `nk_foreach(cmd, ctx)`
  - `nk_minios_font_width` (function, line 554) `static float nk_minios_font_width(nk_handle handle, float height,
                               ...`
  - `nk_minios_font` (function, line 559) `struct nk_user_font nk_minios_font(void)`
  - `feed_key` (function, line 593) `static void feed_key(struct nk_context *ctx, enum nk_keys key, int down)`
  - `handle_scancode` (function, line 597) `static void handle_scancode(struct nk_context *ctx, unsigned char sc)`
  - `nk_poll_input` (function, line 638) `void nk_poll_input(struct nk_context *ctx)`
  - `nk_set_window_origin` (function, line 675) `void nk_set_window_origin(int x, int y)`
  - `NK_IMPLEMENTATION` (macro, line 15)

## progs/nuklear/nuklear_minios.h
- Layer: utility
- Doc: ifndef NUKLEAR_MINIOS_H define NUKLEAR_MINIOS_H  nuklear_minios.h — MiniOS platform layer for Nuklear.
- Language: h
- Symbols:
  - `NUKLEAR_MINIOS_H` (macro, line 2)
  - `NK_W` (macro, line 17)
  - `NK_H` (macro, line 19)
  - `NK_BACKBUF` (macro, line 20)
