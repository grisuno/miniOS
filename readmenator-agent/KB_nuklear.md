# Subsystem: nuklear

## progs/nuklear/cvm_emit.c
- Layer: utility
- Doc: cvm_emit.c — node-graph to CVM bytecode compiler.
- Language: c
- Symbols:
  - `codebuf` (struct, line 73)
  - `code` (function, line 8) `* exit code (OP_HALT leaves the operand-stack top as the exit status, which
 * the shell reports ...`
  - `cb_push` (function, line 79) `static int cb_push(struct codebuf *cb, unsigned char c)`
  - `cb_u32` (function, line 91) `static int cb_u32(struct codebuf *cb, unsigned long v)`
  - `cb_i64` (function, line 97) `static int cb_i64(struct codebuf *cb, long long v)`
  - `cb_patch_u32` (function, line 103) `static void cb_patch_u32(struct codebuf *cb, size_t pos, unsigned long v)`
  - `cb_imm` (function, line 111) `static int cb_imm(struct codebuf *cb, long long v)`
  - `req_inputs` (function, line 126) `static int req_inputs(enum cvm_node_type t)`
  - `is_sink` (function, line 145) `static int is_sink(enum cvm_node_type t)`
  - `topo_sort` (function, line 150) `static int topo_sort(const struct cvm_node *nodes, int n,
                     int *order, char *...`
  - `emit_operand` (function, line 213) `static int emit_operand(struct codebuf *code, const struct cvm_node *nodes,
                     ...`
  - `emit_jz` (function, line 224) `static int emit_jz(struct codebuf *code, size_t *rel_pos)`
  - `emit_jmp` (function, line 230) `static int emit_jmp(struct codebuf *code, size_t *rel_pos)`
  - `cvm_compile` (function, line 236) `int cvm_compile(const struct cvm_node *nodes, int n,
                unsigned char **out, size_t ...`
  - `w32` (function, line 491) `void w32(void *p, unsigned v)`
  - `module` (function, line 3) `* * Emits a cvm2 module (format v2) from a dataflow graph. Nodes are * topologically sorted (a true DAG order, so the editor can connect nodes in * any sequence);`
  - `CVM_MAGIC_0` (macro, line 29) `#define CVM_MAGIC_0`
  - `CVM_MAGIC_1` (macro, line 30) `#define CVM_MAGIC_1`
  - `CVM_MAGIC_2` (macro, line 31) `#define CVM_MAGIC_2`
  - `CVM_MAGIC_3` (macro, line 32) `#define CVM_MAGIC_3`
  - `CVM_VERSION_MAJOR` (macro, line 33) `#define CVM_VERSION_MAJOR`
  - `CVM_MODULE_HEADER_SIZE` (macro, line 34) `#define CVM_MODULE_HEADER_SIZE`
  - `CVM_FUNC_ENTRY_SIZE` (macro, line 35) `#define CVM_FUNC_ENTRY_SIZE`
  - `CVM_GLOBAL_ENTRY_SIZE` (macro, line 36) `#define CVM_GLOBAL_ENTRY_SIZE`
  - `CVM_NATIVE_ENTRY_SIZE` (macro, line 37) `#define CVM_NATIVE_ENTRY_SIZE`
  - `OP_PUSH_IMM64` (macro, line 40) `#define OP_PUSH_IMM64`
  - `OP_PUSH_IMM32` (macro, line 41) `#define OP_PUSH_IMM32`
  - `OP_PUSH_IMM8` (macro, line 42) `#define OP_PUSH_IMM8`
  - `OP_PUSH_ZERO` (macro, line 43) `#define OP_PUSH_ZERO`
  - `OP_PUSH_LOCAL` (macro, line 44) `#define OP_PUSH_LOCAL`
  - `OP_STORE_LOCAL` (macro, line 45) `#define OP_STORE_LOCAL`
  - `OP_ADD` (macro, line 46) `#define OP_ADD`
  - `OP_SUB` (macro, line 47) `#define OP_SUB`
  - `OP_MUL` (macro, line 48) `#define OP_MUL`
  - `OP_DIV` (macro, line 49) `#define OP_DIV`
  - `OP_MOD` (macro, line 50) `#define OP_MOD`
  - `OP_NEG` (macro, line 51) `#define OP_NEG`
  - `OP_AND` (macro, line 52) `#define OP_AND`
  - `OP_OR` (macro, line 53) `#define OP_OR`
  - `OP_XOR` (macro, line 54) `#define OP_XOR`
  - `OP_NOT` (macro, line 55) `#define OP_NOT`
  - `OP_SHL` (macro, line 56) `#define OP_SHL`
  - `OP_SHR` (macro, line 57) `#define OP_SHR`
  - `OP_CMP_EQ` (macro, line 58) `#define OP_CMP_EQ`
  - `OP_CMP_NE` (macro, line 59) `#define OP_CMP_NE`
  - `OP_CMP_LT` (macro, line 60) `#define OP_CMP_LT`
  - `OP_CMP_LE` (macro, line 61) `#define OP_CMP_LE`
  - `OP_CMP_GT` (macro, line 62) `#define OP_CMP_GT`
  - `OP_CMP_GE` (macro, line 63) `#define OP_CMP_GE`
  - `OP_LNOT` (macro, line 64) `#define OP_LNOT`
  - `OP_JMP` (macro, line 65) `#define OP_JMP`
  - `OP_JZ` (macro, line 66) `#define OP_JZ`
  - `OP_CALL_NATIVE` (macro, line 67) `#define OP_CALL_NATIVE`
  - `OP_LEA_DATA` (macro, line 68) `#define OP_LEA_DATA`
  - `OP_HALT` (macro, line 69) `#define OP_HALT`
  - `CVM_MAX_NODES` (macro, line 71) `#define CVM_MAX_NODES`
- Depends on: `kernel/string.c`, `progs/nuklear/cvm_emit.h`

## progs/nuklear/cvm_emit.h
- Layer: utility
- Doc: cvm_emit.h — node-graph compiler for CVM (cvm2 module format v2).
- Language: h
- Symbols:
  - `cvm_node` (struct, line 56)
  - `cvm_node_type` (enum, line 22)
  - `graph` (function, line 6) `* * A node graph (constants, arithmetic, bitwise, comparisons, a conditional * select, and string constants feeding PRINT/PRINTS/EXIT sinks) is compiled * into a self-contained .cvm module: a single e`
  - `err` (function, line 67) `* err (err_cap bytes). The module is heap-allocated and owned by the caller * (free it). */ int cvm_compile(const struct cvm_node *nodes, int n, unsigned char **out, size_t *out_size, char *err, size_`
  - `CVM_EMIT_H` (macro, line 2) `#define CVM_EMIT_H`
  - `CVM_NODE_STR_MAX` (macro, line 19) `#define CVM_NODE_STR_MAX`
- Imported by: `progs/nuklear/cvm_emit.c`, `progs/nuklear/node_editor.c`

## progs/nuklear/font8x8.c
- Layer: utility
- Doc: font8x8 - shared 8x8 bitmap font for MiniOS ring-3 graphics programs.
- Language: c
- Depends on: `progs/nuklear/nuklear_minios.h`

## progs/nuklear/node_editor.c
- Layer: infrastructure
- Doc: node_editor.c — visual low-code editor that compiles to CVM bytecode.
- Language: c
- Symbols:
  - `gnode` (struct, line 44)
  - `nodedef` (struct, line 55)
  - `node_inputs` (function, line 96) `static int node_inputs(int k)`
  - `node_outputs` (function, line 101) `static int node_outputs(int k)`
  - `kind_name` (function, line 106) `static const char *kind_name(int k)`
  - `kind_color` (function, line 111) `static struct nk_color kind_color(int k)`
  - `graph_clear` (function, line 116) `static void graph_clear(void)`
  - `graph_add` (function, line 122) `static int graph_add(int kind)`
  - `graph_del` (function, line 136) `static void graph_del(int idx)`
  - `graph_to_compiler` (function, line 154) `static int graph_to_compiler(struct cvm_node *out, int cap)`
  - `repair_graph` (function, line 176) `static int repair_graph(char *rep, size_t repcap, char *herr, size_t herrcap,
                   ...`
  - `addrep` (function, line 183) `void addrep(const char *s)`
  - `adderr` (function, line 193) `void adderr(const char *s)`
  - `compile_to` (function, line 283) `static int compile_to(const char *path)`
  - `write_quoted` (function, line 339) `static void write_quoted(FILE *f, const char *s)`
  - `save_graph_file` (function, line 392) `static int save_graph_file(const char *path)`
  - `parse_graph_file` (function, line 430) `static int parse_graph_file(const char *path)`
  - `resolve` (function, line 437) `int resolve(const char *nme, int upto)`
  - `parse_input` (function, line 443) `int parse_input(const char *tok, int idx, int k)`
  - `pin_y` (function, line 522) `static float pin_y(struct gnode *n, int slot, int is_output)`
  - `node_h` (function, line 534) `static float node_h(struct gnode *n)`
  - `ui_inspector` (function, line 542) `static void ui_inspector(struct nk_context *ctx)`
  - `ui_build` (function, line 622) `static void ui_build(struct nk_context *ctx, float win_w, float win_h)`
  - `gui_run` (function, line 931) `static void gui_run(void)`
  - `main` (function, line 983) `int main(int argc, char **argv)`
  - `MAX_NODES` (macro, line 33) `#define MAX_NODES`
  - `STR_MAX` (macro, line 34) `#define STR_MAX`
  - `UI_MEMORY` (macro, line 500) `#define UI_MEMORY`
  - `NODE_W` (macro, line 514) `#define NODE_W`
  - `TITLE_H` (macro, line 515) `#define TITLE_H`
  - `PIN_R` (macro, line 516) `#define PIN_R`
  - `PIN_DIAM` (macro, line 517) `#define PIN_DIAM`
  - `BEZIER_PAD` (macro, line 518) `#define BEZIER_PAD`
  - `GRID_SIZE` (macro, line 519) `#define GRID_SIZE`
- Depends on: `kernel/string.c`, `progs/minios_abi.h`, `progs/nuklear/cvm_emit.h`, `progs/nuklear/nuklear_minios.h`, `progs/nuklear/nuklear_theme.h`

## progs/nuklear/nuklear_minios.c
- Layer: utility
- Doc: nuklear_minios.c — MiniOS platform layer for Nuklear.
- Language: c
- Symbols:
  - `nk_sys_time_ms` (function, line 33) `long nk_sys_time_ms(void)`
  - `nk_sys_kbd` (function, line 38) `long nk_sys_kbd(void)`
  - `nk_sys_palette` (function, line 43) `long nk_sys_palette(const unsigned char *pal)`
  - `nk_sys_kbd_raw` (function, line 48) `long nk_sys_kbd_raw(int on)`
  - `nk_sys_getpid` (function, line 53) `long nk_sys_getpid(void)`
  - `nk_client_probe` (function, line 72) `static int nk_client_probe(void)`
  - `nk_sys_vga_mode` (function, line 114) `long nk_sys_vga_mode(int on)`
  - `nk_sys_fb_info` (function, line 121) `long nk_sys_fb_info(int *w, int *h, int *pitch)`
  - `nk_sys_mouse` (function, line 128) `long nk_sys_mouse(int *xybw)`
  - `nk_sys_mouse_badptr` (function, line 133) `long nk_sys_mouse_badptr(void)`
  - `nk_client_hash` (function, line 151) `static unsigned nk_client_hash(const unsigned char *p, unsigned n)`
  - `nk_client_publish` (function, line 162) `static int nk_client_publish(void)`
  - `nk_sys_nk_frame` (function, line 215) `long nk_sys_nk_frame(int *origin)`
  - `nk_mirror_box` (function, line 243) `static void nk_mirror_box(char *dst, int cap)`
  - `nk_mirror_emit` (function, line 264) `static int nk_mirror_emit(const char *box, unsigned seq,
        const unsigned char *msg, int mlen)`
  - `nk_mirror_tick` (function, line 281) `static void nk_mirror_tick(void)`
  - `nk_sys_gfx_set_title` (function, line 338) `long nk_sys_gfx_set_title(const char *t)`
  - `nk_build_palette` (function, line 347) `void nk_build_palette(unsigned char *pal768)`
  - `pal_prepare` (function, line 356) `static void pal_prepare(void)`
  - `col_to_idx` (function, line 367) `static int col_to_idx(struct nk_color c)`
  - `set_clip` (function, line 385) `static void set_clip(int x, int y, int w, int h)`
  - `px` (function, line 395) `static void px(int x, int y, int c)`
  - `fill_rect` (function, line 402) `static void fill_rect(int x, int y, int w, int h, int c)`
  - `draw_line` (function, line 409) `static void draw_line(int x0, int y0, int x1, int y1, int th, int c)`
  - `fill_circle` (function, line 427) `static void fill_circle(int cx, int cy, int r, int c)`
  - `stroke_circle` (function, line 433) `static void stroke_circle(int cx, int cy, int r, int th, int c)`
  - `fill_poly` (function, line 451) `static void fill_poly(int *xs, int *ys, int n, int c)`
  - `stroke_poly` (function, line 474) `static void stroke_poly(int *xs, int *ys, int n, int th, int c)`
  - `draw_text` (function, line 481) `static void draw_text(int x, int y, const char *s, int len, int fg, int bg)`
  - `draw_arc` (function, line 495) `static void draw_arc(int cx, int cy, int r, float a0, float a1,
                     int filled, ...`
  - `nk_rasterize` (function, line 516) `void nk_rasterize(struct nk_context *ctx)`
  - `nk_foreach` (function, line 520) `nk_foreach(cmd, ctx)`
  - `nk_minios_font_width` (function, line 683) `static float nk_minios_font_width(nk_handle handle, float height,
                               ...`
  - `nk_minios_font` (function, line 689) `struct nk_user_font nk_minios_font(void)`
  - `feed_key` (function, line 724) `static void feed_key(struct nk_context *ctx, enum nk_keys key, int down)`
  - `nk_set_scancode_hook` (function, line 731) `void nk_set_scancode_hook(nk_scancode_cb cb, void *ud)`
  - `handle_scancode` (function, line 736) `static void handle_scancode(struct nk_context *ctx, unsigned char sc)`
  - `nk_client_poll` (function, line 784) `static void nk_client_poll(struct nk_context *ctx)`
  - `nk_poll_input` (function, line 831) `void nk_poll_input(struct nk_context *ctx)`
  - `nk_set_window_origin` (function, line 870) `void nk_set_window_origin(int x, int y)`
  - `nk_quit_requested` (function, line 878) `int nk_quit_requested(void)`
  - `list` (function, line 4) `* abstract draw command list (nk__begin/nk__next);`
  - `program_invocation_short_name` (variable, line 27) `extern char *program_invocation_short_name;`
  - `NK_IMPLEMENTATION` (macro, line 17) `#define NK_IMPLEMENTATION`
- Depends on: `kernel/string.c`, `progs/nk_palette.h`, `progs/nuklear/nuklear_minios.h`, `progs/wl/wl_client.h`, `progs/wl/wl_mbox.h`

## progs/nuklear/nuklear_minios.h
- Layer: utility
- Doc: nuklear_minios.h — MiniOS platform layer for Nuklear.
- Language: h
- Symbols:
  - `nk_context` (struct, line 20)
  - `nk_user_font` (struct, line 21)
  - `nk_command_buffer` (struct, line 22)
  - `nk_minios_img` (struct, line 62)
  - `nk_sys_time_ms` (function, line 29) `long nk_sys_time_ms(void);`
  - `nk_sys_kbd` (function, line 30) `long nk_sys_kbd(void);`
  - `nk_sys_palette` (function, line 31) `long nk_sys_palette(const unsigned char *pal768);`
  - `nk_sys_kbd_raw` (function, line 32) `long nk_sys_kbd_raw(int on);`
  - `nk_sys_vga_mode` (function, line 33) `long nk_sys_vga_mode(int on);`
  - `nk_sys_fb_info` (function, line 34) `long nk_sys_fb_info(int *w, int *h, int *pitch);`
  - `nk_sys_mouse` (function, line 35) `long nk_sys_mouse(int *xybw);`
  - `nk_sys_mouse_badptr` (function, line 39) `long nk_sys_mouse_badptr(void);`
  - `nk_sys_nk_frame` (function, line 40) `long nk_sys_nk_frame(int *origin);`
  - `nk_sys_gfx_set_title` (function, line 41) `long nk_sys_gfx_set_title(const char *t);`
  - `nk_build_palette` (function, line 45) `void nk_build_palette(unsigned char *pal768);`
  - `nk_minios_font` (function, line 51) `struct nk_user_font nk_minios_font(void);`
  - `nk_rasterize` (function, line 54) `void nk_rasterize(struct nk_context *ctx);`
  - `SYS_NK_FRAME` (function, line 73) `* SYS_NK_FRAME (nk_set_window_origin). */ void nk_set_window_origin(int x, int y);`
  - `nk_poll_input` (function, line 75) `void nk_poll_input(struct nk_context *ctx);`
  - `nk_quit_requested` (function, line 80) `int nk_quit_requested(void);`
  - `nk_set_scancode_hook` (function, line 89) `void nk_set_scancode_hook(nk_scancode_cb cb, void *ud);`
  - `NUKLEAR_MINIOS_H` (macro, line 2) `#define NUKLEAR_MINIOS_H`
  - `NK_W` (macro, line 24) `#define NK_W`
  - `NK_H` (macro, line 25) `#define NK_H`
  - `NK_BACKBUF` (macro, line 26) `#define NK_BACKBUF`
  - `NK_MINIOS_IMG_MAX` (macro, line 61) `#define NK_MINIOS_IMG_MAX`
- Depends on: `progs/minios_abi.h`
- Imported by: `progs/doomedit/doomedit.c`, `progs/file/file.c`, `progs/nuklear/font8x8.c`, `progs/nuklear/node_editor.c`, `progs/nuklear/nuklear_minios.c`, `progs/paint/paint.c`, `progs/piano/piano.c`, `progs/vedit/vedit.c`

## progs/nuklear/nuklear_theme.c
- Layer: utility
- Doc: Docstring: shared Nuklear theme loader, linked by every NK app.
- Language: c
- Symbols:
  - `nk_theme_slot` (struct, line 15)
  - `nk_theme_name_ok` (function, line 37) `static int nk_theme_name_ok(const char *name)`
  - `nk_theme_active` (function, line 49) `int nk_theme_active(char *dst, int cap)`
  - `nk_theme_parse_line` (function, line 73) `static int nk_theme_parse_line(const char *line,
                               unsigned char rgb...`
  - `nk_theme_probe` (function, line 105) `int nk_theme_probe(const char *name, unsigned char rgb[NK_THEME_KEY_COUNT][3])`
  - `nk_theme_apply` (function, line 141) `int nk_theme_apply(struct nk_context *ctx, const char *name)`
  - `X` (macro, line 21) `#define X(k, i)`
- Depends on: `kernel/string.c`, `progs/nuklear/nuklear_theme.h`

## progs/nuklear/nuklear_theme.h
- Layer: utility
- Doc: Docstring: shared Nuklear theme contract for every MiniOS NK app.
- Language: h
- Symbols:
  - `nk_context` (struct, line 59)
  - `nk_theme_active` (function, line 62) `int nk_theme_active(char *dst, int cap);`
  - `nk_theme_probe` (function, line 65) `int nk_theme_probe(const char *name, unsigned char rgb[NK_THEME_KEY_COUNT][3]);`
  - `nk_theme_apply` (function, line 68) `int nk_theme_apply(struct nk_context *ctx, const char *name);`
  - `NUKLEAR_THEME_H` (macro, line 2) `#define NUKLEAR_THEME_H`
  - `NK_THEME_NAME_MAX` (macro, line 15) `#define NK_THEME_NAME_MAX`
  - `NK_THEME_KEY_MAX` (macro, line 16) `#define NK_THEME_KEY_MAX`
  - `NK_THEME_LINE_MAX` (macro, line 17) `#define NK_THEME_LINE_MAX`
  - `NK_THEME_PATH_DIR` (macro, line 18) `#define NK_THEME_PATH_DIR`
  - `NK_THEME_PATH_CURRENT` (macro, line 19) `#define NK_THEME_PATH_CURRENT`
  - `NK_THEME_DEFAULT` (macro, line 20) `#define NK_THEME_DEFAULT`
  - `NK_THEME_KEY_LIST` (macro, line 23) `#define NK_THEME_KEY_LIST`
  - `NK_THEME_KEY_COUNT` (macro, line 57) `#define NK_THEME_KEY_COUNT`
- Imported by: `progs/doomedit/doomedit.c`, `progs/file/file.c`, `progs/nuklear/node_editor.c`, `progs/nuklear/nuklear_theme.c`, `progs/paint/paint.c`, `progs/piano/piano.c`, `progs/vedit/vedit.c`, `tests/test_theme.c`
