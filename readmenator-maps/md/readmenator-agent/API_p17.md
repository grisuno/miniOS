# API (page 17 of 21)
Previous: [API_p16.md](API_p16.md)

## progs/minicraft/minicraft.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`
- `best_tool_for` (function) `progs/minicraft/minicraft.c:231` `static int best_tool_for(unsigned char b)`
- `break_time_ms` (function) `progs/minicraft/minicraft.c:250` `static long break_time_ms(unsigned char b, int tool)`
- `break_beep_for` (function) `progs/minicraft/minicraft.c:275` `static long break_beep_for(unsigned char b)`
- `mc_toggle_zoom` (function) `progs/minicraft/minicraft.c:316` `static void mc_toggle_zoom(void)`
- `save_world` (function) `progs/minicraft/minicraft.c:330` `static int save_world(void);`
- `s_time_ms` (function) `progs/minicraft/minicraft.c:337` `static long s_time_ms(void)`
- `s_kbd` (function) `progs/minicraft/minicraft.c:342` `static long s_kbd(void)`
- `s_kbd_raw` (function) `progs/minicraft/minicraft.c:347` `static long s_kbd_raw(long on)`
- `s_getc_raw` (function) `progs/minicraft/minicraft.c:359` `static long s_getc_raw(void)` -- Serial fallback for menus: SYS_KBD in raw mode carries PS/2 only, so a serial console can never drive a scancode...
- `ser_get` (function) `progs/minicraft/minicraft.c:373` `static long ser_get(void)`
- `ser_unget` (function) `progs/minicraft/minicraft.c:386` `static void ser_unget(unsigned char b)`
- `menu_ser_key` (function) `progs/minicraft/minicraft.c:391` `static long menu_ser_key(long b)`
- `kbd_drain` (function) `progs/minicraft/minicraft.c:428` `static void kbd_drain(void)` -- Drain stale scancodes (typematic repeats, a release that arrived with * its press) before leaving a menu, so they...
- `s_vga` (function) `progs/minicraft/minicraft.c:433` `static long s_vga(long on)`
- `s_pal` (function) `progs/minicraft/minicraft.c:438` `static long s_pal(const unsigned char *p)`
- `s_present` (function) `progs/minicraft/minicraft.c:443` `static long s_present(void)`
- `s_title` (function) `progs/minicraft/minicraft.c:448` `static long s_title(const char *t)`
- `s_mouse` (function) `progs/minicraft/minicraft.c:453` `static long s_mouse(int *m)`
- `s_zoom` (function) `progs/minicraft/minicraft.c:458` `static long s_zoom(long on)`
- `s_yield` (function) `progs/minicraft/minicraft.c:463` `static void s_yield(void)`
- `s_pcspk_init` (function) `progs/minicraft/minicraft.c:468` `static long s_pcspk_init(void)`
- `beep` (function) `progs/minicraft/minicraft.c:478` `static void beep(long freq, long dur_ms)`
- `pal_set` (function) `progs/minicraft/minicraft.c:497` `static void pal_set(int i, int r, int g, int b)`
- `build_palette` (function) `progs/minicraft/minicraft.c:503` `static void build_palette(void)`
- `in_world` (function) `progs/minicraft/minicraft.c:562` `static int in_world(int x, int y, int z)`
- `chunk_of` (function) `progs/minicraft/minicraft.c:577` `static int chunk_of(int v)` -- (void)x; (void)y; return z >= 0 && z < MC_H; } static unsigned int hash2(int x, int y); static unsigned int...
- `chunk_local` (function) `progs/minicraft/minicraft.c:581` `static int chunk_local(int v)`
- `chunk_lidx` (function) `progs/minicraft/minicraft.c:586` `static int chunk_lidx(int lx, int ly, int z)`
- `chunk_find` (function) `progs/minicraft/minicraft.c:592` `static int chunk_find(int cx, int cy)` -- O(1) fast path: DDA walks neighbours, so the last chunk almost always * hits; the 49-slot scan is the rare slow...
- `world_max_recompute` (function) `progs/minicraft/minicraft.c:606` `static void world_max_recompute(void)`
- `chunk_evict_slot` (function) `progs/minicraft/minicraft.c:615` `static int chunk_evict_slot(int cx, int cy)`
- `chunk_ensure` (function) `progs/minicraft/minicraft.c:635` `static int chunk_ensure(int cx, int cy)`
- `chunk_build_meta` (function) `progs/minicraft/minicraft.c:658` `static void chunk_build_meta(int slot)`
- `col_recompute` (function) `progs/minicraft/minicraft.c:703` `static void col_recompute(int x, int y)`
- `col_top_at` (function) `progs/minicraft/minicraft.c:728` `static int col_top_at(int x, int y)`
- `light_recompute_col` (function) `progs/minicraft/minicraft.c:735` `static void light_recompute_col(int x, int y)`
- `get_b` (function) `progs/minicraft/minicraft.c:764` `static unsigned char get_b(int x, int y, int z)`
- `set_b` (function) `progs/minicraft/minicraft.c:774` `static void set_b(int x, int y, int z, unsigned char b)`
- `set_b_raw` (function) `progs/minicraft/minicraft.c:790` `static void set_b_raw(int x, int y, int z, unsigned char b)`
- `sky_light` (function) `progs/minicraft/minicraft.c:801` `static float sky_light(int x, int y, int z)` -- world_dirty = 1; } static void set_b_raw(int x, int y, int z, unsigned char b) { int s; if (z < 0 || z >= MC_H)...
- `is_solid` (function) `progs/minicraft/minicraft.c:811` `static int is_solid(unsigned char b)`
- `in_water_at` (function) `progs/minicraft/minicraft.c:814` `static int in_water_at(float x, float y, float z)`
- `is_visible` (function) `progs/minicraft/minicraft.c:819` `static int is_visible(unsigned char b)`
- `hash2` (function) `progs/minicraft/minicraft.c:823` `static unsigned int hash2(int x, int y)`
- `hash2_seed` (function) `progs/minicraft/minicraft.c:830` `static unsigned int hash2_seed(int x, int y, unsigned int seed)`
- `mc_smoothstep` (function) `progs/minicraft/minicraft.c:839` `static float mc_smoothstep(float t)`
- `biome_fdiv` (function) `progs/minicraft/minicraft.c:846` `static int biome_fdiv(int v, int c)` -- Voronoi biome lattice: floor division so negatives land right.
- `voro_site` (function) `progs/minicraft/minicraft.c:861` `static void voro_site(int cx, int cy, unsigned int seed, int cell,
    int *sx, int *sy)`
- `biome_voro` (function) `progs/minicraft/minicraft.c:869` `static int biome_voro(int x, int y, unsigned int seed, int cell,
    int ox, int oy, unsigned int...`
- `biome_desert` (function) `progs/minicraft/minicraft.c:893` `static int biome_desert(int x, int y, unsigned int seed)`
- `biome_snow` (function) `progs/minicraft/minicraft.c:897` `static int biome_snow(int x, int y, unsigned int seed)`
- `is_cave` (function) `progs/minicraft/minicraft.c:901` `static int is_cave(int x, int y, int z, unsigned int seed)`
- `ground_h_seed` (function) `progs/minicraft/minicraft.c:909` `static int ground_h_seed(int x, int y, unsigned int seed)`
- `inv_add` (function) `progs/minicraft/minicraft.c:931` `static int inv_add(int b, int n)`
- `inv_remove` (function) `progs/minicraft/minicraft.c:945` `static int inv_remove(int b, int n)`
- `decorate_column` (function) `progs/minicraft/minicraft.c:995` `static void decorate_column(int x, int y, unsigned int seed)`
- `gen_terrain_chunk` (function) `progs/minicraft/minicraft.c:1034` `static void gen_terrain_chunk(int slot)`
- `decorate_chunk` (function) `progs/minicraft/minicraft.c:1043` `static void decorate_chunk(int slot)`
- `ensure_around_px` (function) `progs/minicraft/minicraft.c:1056` `static void ensure_around_px(float px, float py)` -- Keep a (2R+1)^2 ring of terrain around the player, an inner ring decorated, drop the rest (dirty chunks hit disk first).
- `ensure_around` (function) `progs/minicraft/minicraft.c:1090` `static void ensure_around(void)`
- `new_world` (function) `progs/minicraft/minicraft.c:1095` `static void new_world(unsigned int seed)` -- save_chunk_file(i); ch_used[i] = 0; if (ch_cache == i) ch_cache = -1; } } world_max_recompute(); } static void...
- `mob_spawn_one` (function) `progs/minicraft/minicraft.c:1191` `static void mob_spawn_one(Pig *m, int id, int hp, long now)`
- `pig_collides` (function) `progs/minicraft/minicraft.c:1243` `static int pig_collides(float x, float y, float z)`
- `creeper_explode` (function) `progs/minicraft/minicraft.c:1257` `static void creeper_explode(Pig *c, long now)`
- `creep_sense` (function) `progs/minicraft/minicraft.c:1325` `static void creep_sense(Pig *c, float *pdx, float *pdy, float *pdz, float *pd3)` -- Creeper perception in 3D: planar delta, eye-height delta and full distance.
- `creep_has_los` (function) `progs/minicraft/minicraft.c:1337` `static int creep_has_los(Pig *c)` -- Voxel line of sight between creeper eyes and player eyes, sampled every half block.
- `creep_separate` (function) `progs/minicraft/minicraft.c:1361` `static void creep_separate(Pig *p, int id, float dt)` -- Herd separation: creepers inside MC_CREEP_SEP_D push apart so the pack * never stacks on one tile and every one of...
- `tick_mob` (function) `progs/minicraft/minicraft.c:1386` `static void tick_mob(Pig *p, int id, float dt, long now)`
- `tick_pigs` (function) `progs/minicraft/minicraft.c:1512` `static void tick_pigs(float dt, long now)`
- `face_color` (function) `progs/minicraft/minicraft.c:1520` `static unsigned char face_color(unsigned char b, int face)`
- `sky_color` (function) `progs/minicraft/minicraft.c:1569` `static unsigned char sky_color(float dz, float sun_dot, int x, int y, float tsec)`
- `shade_block` (function) `progs/minicraft/minicraft.c:1602` `static unsigned char shade_block(unsigned char b, int face, int bx, int by, int bz,
             ...`
- `cast_ray` (function) `progs/minicraft/minicraft.c:1659` `static RayHit cast_ray(float ox, float oy, float oz, float dx, float dy, float dz, float maxd)`
- `eye_z` (function) `progs/minicraft/minicraft.c:1750` `static float eye_z(void)`
- `mc_glyph` (function) `progs/minicraft/minicraft.c:1817` `static int mc_glyph(char ch)`
- `mc_pixel` (function) `progs/minicraft/minicraft.c:1825` `static void mc_pixel(int x, int y, unsigned char c)`
- `mc_text` (function) `progs/minicraft/minicraft.c:1831` `static void mc_text(int x, int y, const char *s, unsigned char fg)`
- `mc_text_bg` (function) `progs/minicraft/minicraft.c:1844` `static void mc_text_bg(int x, int y, const char *s, unsigned char fg, unsigned char bg)`
- `mc_block_name` (function) `progs/minicraft/minicraft.c:1857` `static const char *mc_block_name(unsigned char b)`
- `mc_facing` (function) `progs/minicraft/minicraft.c:1877` `static char mc_facing(void)`
- `cam_build` (function) `progs/minicraft/minicraft.c:1892` `static void cam_build(void)`
- `render_terrain` (function) `progs/minicraft/minicraft.c:1910` `static void render_terrain(RayHit tgt, float cyaw, float syaw, float cpit,
                      ...`
- `mob_pixel` (function) `progs/minicraft/minicraft.c:1945` `static unsigned char mob_pixel(Pig *m, int id, int px, int py, int x0, int x1, int y0, int y1)`
- `render_mob_array` (function) `progs/minicraft/minicraft.c:1979` `static void render_mob_array(Pig *arr, int n, float fx, float fy, float fz,
    float rx, float r...`
- `render_pigs` (function) `progs/minicraft/minicraft.c:2030` `static void render_pigs(float cyaw, float syaw, float cpit, float spit, float ez)`
- `render_frame` (function) `progs/minicraft/minicraft.c:2038` `static void render_frame(void)`
- `sc_hist_push` (function) `progs/minicraft/minicraft.c:2151` `static void sc_hist_push(unsigned char b)`
- `poll_kbd` (function) `progs/minicraft/minicraft.c:2162` `static void poll_kbd(void)`
- `player_collides` (function) `progs/minicraft/minicraft.c:2355` `static int player_collides(float x, float y, float z)`
- `move_x` (function) `progs/minicraft/minicraft.c:2379` `static void move_x(float nx)`
- `move_y` (function) `progs/minicraft/minicraft.c:2384` `static void move_y(float ny)`
- `move_z_abs` (function) `progs/minicraft/minicraft.c:2389` `static MoveResult move_z_abs(float nz)`
- `block_intersects_player` (function) `progs/minicraft/minicraft.c:2404` `static int block_intersects_player(int bx, int by, int bz)`
- `try_autostep` (function) `progs/minicraft/minicraft.c:2413` `static void try_autostep(float tx, float ty)`
- `hurt` (function) `progs/minicraft/minicraft.c:2424` `static void hurt(int dmg, const char *why)`
- `tick_player` (function) `progs/minicraft/minicraft.c:2449` `static void tick_player(float dt)`
- `tick_water` (function) `progs/minicraft/minicraft.c:2548` `static void tick_water(long now)`
- `tick_hunger` (function) `progs/minicraft/minicraft.c:2596` `static void tick_hunger(long now)`
- `goal_text` (function) `progs/minicraft/minicraft.c:2608` `static const char *goal_text(void)`
- `tick_goals` (function) `progs/minicraft/minicraft.c:2619` `static void tick_goals(void)`
- `tick_discover` (function) `progs/minicraft/minicraft.c:2630` `static void tick_discover(long now)`
- `tick_interact` (function) `progs/minicraft/minicraft.c:2668` `static void tick_interact(void)`
- `mc_crc32` (function) `progs/minicraft/minicraft.c:2919` `static uint32_t mc_crc32(const void *data, size_t len, uint32_t crc)`
- `save_compute_crc` (function) `progs/minicraft/minicraft.c:2932` `static uint32_t save_compute_crc(const SaveHeader *hd)`
- `chunk_path` (function) `progs/minicraft/minicraft.c:2938` `static void chunk_path(int cx, int cy, char *out, size_t n)`
- `save_chunk_file` (function) `progs/minicraft/minicraft.c:2942` `static int save_chunk_file(int slot)`
- `load_chunk_file` (function) `progs/minicraft/minicraft.c:2974` `static int load_chunk_file(int slot, int cx, int cy)`
- `save_validate_loaded` (function) `progs/minicraft/minicraft.c:3056` `static int save_validate_loaded(void)`
- `load_reset_runtime` (function) `progs/minicraft/minicraft.c:3075` `static void load_reset_runtime(void)`
- `carve_blob` (function) `progs/minicraft/minicraft.c:3108` `static void carve_blob(const unsigned char *blob)` -- Import a 64x64x32 legacy blob into chunks (0..3, 0..3), then dirty so * region files persist it.
- `load_world_legacy` (function) `progs/minicraft/minicraft.c:3137` `static int load_world_legacy(FILE *f)` -- Legacy raw save: fixed old_inv[12] layout is fragile if B_COUNT grows; * kept read-only for ancient saves, never...
- `load_apply_player` (function) `progs/minicraft/minicraft.c:3175` `static void load_apply_player(const SaveHeader *hd)`
- `load_world_v3` (function) `progs/minicraft/minicraft.c:3194` `static int load_world_v3(FILE *f, SaveHeader *hd)`
- `load_world_v2` (function) `progs/minicraft/minicraft.c:3234` `static int load_world_v2(FILE *f, SaveHeader *hd)`
- `load_world` (function) `progs/minicraft/minicraft.c:3271` `static int load_world(void)`
- `selftest` (function) `progs/minicraft/minicraft.c:3345` `static int selftest(void)`
- `census` (function) `progs/minicraft/minicraft.c:3606` `static int census(void)` -- 128x128 columns (64 biome cells): a 64-wide patch covers too few * 16-block biome cells and the desert rate...
- `dumpstats` (function) `progs/minicraft/minicraft.c:3670` `static int dumpstats(void)`
- `title_menu` (function) `progs/minicraft/minicraft.c:3754` `static int title_menu(int have_save, int *seed_io)`
- `pause_menu` (function) `progs/minicraft/minicraft.c:3922` `static int pause_menu(int *seed_io)` -- Pause menu on ESC (Alt+F4 still kills the process kernel-side): * 0 = resume, 1 = new world with *seed_io, 2 = save...
- `main` (function) `progs/minicraft/minicraft.c:4095` `int main(int argc, char **argv)`

## progs/minios_abi.h
Imported by: `headers/kernel.h`, `headers/vga_fb.h`, `progs/doomedit/doomedit.c`, `progs/doomgeneric/doomgeneric_minios.c`, `progs/doomgeneric/i_minios_sound.c`, `progs/file/file.c`, `progs/freedomui/freedomui_minios.c`, `progs/freedomui/platform_minios.c`, `progs/lisp/lisp.c`, `progs/lua/minios.c`, `progs/micropython/variants/minios/minios_module.c`, `progs/minicraft/minicraft.c`, `progs/nuklear/node_editor.c`, `progs/nuklear/nuklear_minios.h`, `progs/paint/paint.c`, `progs/piano/piano.c`, `progs/pokemon/platform_minios.c`, `progs/quake2generic/q2generic_minios.c`, `progs/quake2generic/snddma_minios.c`, `progs/src/audio.c`, `progs/src/fptest.c`, `progs/src/freedom_wl.c`, `progs/src/lxproc.c`, `progs/src/mthreads.h`, `progs/src/opl3.c`, `progs/src/sbtone.c`, `progs/src/thdemo.c`, `progs/wl/wlcomp.c`, `tests/test_abi.c`, `tests/test_wl.c`, `tools/abi_stamp.c`
- `DOOM_BACKBUF_ADDR` (function) `progs/minios_abi.h:128` `* * All three sit in the reserved tail above DOOM_BACKBUF_ADDR (the brk cap), * so a growing heap or mmap region can...`
- `clock_nanosleep` (function) `progs/minios_abi.h:338` `* clock_nanosleep (static glibc's sleep, usleep and nanosleep). */ #define MINIOS_SYS_SB16_STREAM_OPEN 252 #define...`

## progs/minios_png.h
Imported by: `progs/file/file.c`, `progs/pokemon/platform_minios.c`, `tests/test_minios_png.c`
- `mpng_332_idx` (function) `progs/minios_png.h:58` `static int mpng_332_idx(unsigned r, unsigned g, unsigned b)` -- static const char *mpng_left_candidates[MPNG_LEFT_N] = { "/icons/doom.png", "/icons/doomedit.png"...
- `mpng_nearest` (function) `progs/minios_png.h:63` `static int mpng_nearest(const unsigned char *pal, long pal_n, unsigned r,
                       ...` -- "/icons/nuklear.png", "/icons/vedit.png", "/icons/file.png", "/icons/shell.png", "/icons/paint.png"...
- `mpng_center` (function) `progs/minios_png.h:84` `static int mpng_center(int outer, int inner)` -- for (k = 0; k < pal_n; k++) { long dr = (long)pal[k * 3] - (long)r; long dg = (long)pal[k * 3 + 1] - (long)g; long...
- `mpng_fit_scale` (function) `progs/minios_png.h:93` `static int mpng_fit_scale(int sw, int sh, int boxw, int boxh)` -- } return (int)best; } /** Docstring: centered offset of inner inside outer, negative when unfit. static int...
- `mpng_rgb_to_idx_scaled` (function) `progs/minios_png.h:108` `static int mpng_rgb_to_idx_scaled(const unsigned char *rgb, int sw, int sh,
                     ...` -- int s = 1; int best = 1; if (sw <= 0 || sh <= 0 || boxw <= 0 || boxh <= 0) return -1; for (s = 1; s <= boxw && s <=...
- `bound` (function) `progs/minios_png.h:140` `* its 512 source bound (pinned by the host suite), so icon and policy
 * art never grow through t...`
- `mpng_rgb_to_332_scaled` (function) `progs/minios_png.h:172` `static int mpng_rgb_to_332_scaled(const unsigned char *rgb, int sw, int sh,
                     ...` -- int sy = y * sh / dh; for (x = 0; x < dw; x++) { int sx = x * sw / dw; const unsigned char *p = rgb + (sy * sw + sx)...
- `mpng_blit_idx` (function) `progs/minios_png.h:196` `static int mpng_blit_idx(unsigned char *fb, int fw, int fh,
                         const unsign...` -- if (dw > MPNG_MAX_DIM || dh > MPNG_MAX_DIM) return MPNG_ERR_BOUND; for (y = 0; y < dh; y++) { int sy = y * sh / dh...
- `mpng_load_file` (function) `progs/minios_png.h:222` `static int mpng_load_file(const char *path, unsigned char **out, long *out_n,
                   ...` -- int dy = oy + y; if (dy < 0 || dy >= fh) continue; for (x = 0; x < tw; x++) { int dx = ox + x; if (dx < 0 || dx >=...

## progs/nk_palette.h
Imported by: `progs/freedomui/freedomui_minios.c`, `progs/nuklear/nuklear_minios.c`, `progs/src/freedom_wl.c`, `progs/wl/wlcomp.c`, `tests/test_wl.c`
- `nk_palette_build` (function) `progs/nk_palette.h:22` `static int nk_palette_build(unsigned char *pal, long cap)`

## progs/nuklear/cvm_emit.c
Depends on: `kernel/string.c`, `progs/nuklear/cvm_emit.h`
- `module` (function) `progs/nuklear/cvm_emit.c:3` `* * Emits a cvm2 module (format v2) from a dataflow graph. Nodes are * topologically sorted (a true DAG order, so...`
- `code` (function) `progs/nuklear/cvm_emit.c:8` `* exit code (OP_HALT leaves the operand-stack top as the exit status, which
 * the shell reports ...`
- `cb_push` (function) `progs/nuklear/cvm_emit.c:79` `static int cb_push(struct codebuf *cb, unsigned char c)`
- `cb_u32` (function) `progs/nuklear/cvm_emit.c:91` `static int cb_u32(struct codebuf *cb, unsigned long v)`
- `cb_i64` (function) `progs/nuklear/cvm_emit.c:97` `static int cb_i64(struct codebuf *cb, long long v)`
- `cb_patch_u32` (function) `progs/nuklear/cvm_emit.c:103` `static void cb_patch_u32(struct codebuf *cb, size_t pos, unsigned long v)`
- `cb_imm` (function) `progs/nuklear/cvm_emit.c:111` `static int cb_imm(struct codebuf *cb, long long v)` -- static int cb_i64(struct codebuf *cb, long long v) { for (int i = 0; i < 8; i++) if (cb_push(cb, (unsigned char)(v...
- `req_inputs` (function) `progs/nuklear/cvm_emit.c:126` `static int req_inputs(enum cvm_node_type t)` -- if (v >= -128 && v <= 127) { if (cb_push(cb, OP_PUSH_IMM8) < 0) return -1; if (cb_push(cb, (unsigned char)(v &...
- `is_sink` (function) `progs/nuklear/cvm_emit.c:145` `static int is_sink(enum cvm_node_type t)`
- `topo_sort` (function) `progs/nuklear/cvm_emit.c:150` `static int topo_sort(const struct cvm_node *nodes, int n,
                     int *order, char *...` -- case NODE_EXIT: return 1; case NODE_IF: return 3; default: return 2; } } static int is_sink(enum cvm_node_type t) {...
- `emit_operand` (function) `progs/nuklear/cvm_emit.c:213` `static int emit_operand(struct codebuf *code, const struct cvm_node *nodes,
                     ...` -- Emit one operand: the wired local slot or the fallback literal.
- `emit_jz` (function) `progs/nuklear/cvm_emit.c:224` `static int emit_jz(struct codebuf *code, size_t *rel_pos)`
- `emit_jmp` (function) `progs/nuklear/cvm_emit.c:230` `static int emit_jmp(struct codebuf *code, size_t *rel_pos)`
- `cvm_compile` (function) `progs/nuklear/cvm_emit.c:236` `int cvm_compile(const struct cvm_node *nodes, int n,
                unsigned char **out, size_t ...`
- `w32` (function) `progs/nuklear/cvm_emit.c:491` `void w32(void *p, unsigned v)` -- size_t ft = (size_t)nf * CVM_FUNC_ENTRY_SIZE; size_t gt = (size_t)ng * CVM_GLOBAL_ENTRY_SIZE; size_t nt = (size_t)nn...

## progs/nuklear/cvm_emit.h
Imported by: `progs/nuklear/cvm_emit.c`, `progs/nuklear/node_editor.c`
- `graph` (function) `progs/nuklear/cvm_emit.h:6` `* * A node graph (constants, arithmetic, bitwise, comparisons, a conditional * select, and string constants feeding...`
- `err` (function) `progs/nuklear/cvm_emit.h:67` `* err (err_cap bytes). The module is heap-allocated and owned by the caller * (free it). */ int cvm_compile(const...`

## progs/nuklear/node_editor.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`, `progs/nuklear/cvm_emit.h`, `progs/nuklear/nuklear_minios.h`, `progs/nuklear/nuklear_theme.h`
- `node_inputs` (function) `progs/nuklear/node_editor.c:96` `static int node_inputs(int k)`
- `node_outputs` (function) `progs/nuklear/node_editor.c:101` `static int node_outputs(int k)`
- `kind_name` (function) `progs/nuklear/node_editor.c:106` `static const char *kind_name(int k)`
- `kind_color` (function) `progs/nuklear/node_editor.c:111` `static struct nk_color kind_color(int k)`
- `graph_clear` (function) `progs/nuklear/node_editor.c:116` `static void graph_clear(void)`
- `graph_add` (function) `progs/nuklear/node_editor.c:122` `static int graph_add(int kind)`
- `graph_del` (function) `progs/nuklear/node_editor.c:136` `static void graph_del(int idx)`
- `graph_to_compiler` (function) `progs/nuklear/node_editor.c:154` `static int graph_to_compiler(struct cvm_node *out, int cap)` -- g_count--; for (int i = 0; i < g_count; i++) for (int k = 0; k < 3; k++) { if (g_nodes[i].in[k] == idx) {...
- `repair_graph` (function) `progs/nuklear/node_editor.c:176` `static int repair_graph(char *rep, size_t repcap, char *herr, size_t herrcap,
                   ...` -- Pre-compile pass: repair every open data input with a const 0 fallback (an open PrStr prints an empty line), so...
- `addrep` (function) `progs/nuklear/node_editor.c:183` `void addrep(const char *s)`
- `adderr` (function) `progs/nuklear/node_editor.c:193` `void adderr(const char *s)`
- `compile_to` (function) `progs/nuklear/node_editor.c:283` `static int compile_to(const char *path)` -- Compile the current graph to a file.
- `write_quoted` (function) `progs/nuklear/node_editor.c:339` `static void write_quoted(FILE *f, const char *s)` -- --- Headless graph text format (v2, backward compatible) ---- num a 5          str s "hi"       add b a c      add c...
- `save_graph_file` (function) `progs/nuklear/node_editor.c:392` `static int save_graph_file(const char *path)`
- `parse_graph_file` (function) `progs/nuklear/node_editor.c:430` `static int parse_graph_file(const char *path)`
- `resolve` (function) `progs/nuklear/node_editor.c:437` `int resolve(const char *nme, int upto)`
- `parse_input` (function) `progs/nuklear/node_editor.c:443` `int parse_input(const char *tok, int idx, int k)` -- static int parse_graph_file(const char *path) { FILE *f = fopen(path, "r"); if (!f) return -1; graph_clear(); static...
- `pin_y` (function) `progs/nuklear/node_editor.c:522` `static float pin_y(struct gnode *n, int slot, int is_output)` -- /* Link-drag state: click an output pin, drag to an input pin. static int linking_active; static int...
- `node_h` (function) `progs/nuklear/node_editor.c:534` `static float node_h(struct gnode *n)`
- `ui_inspector` (function) `progs/nuklear/node_editor.c:542` `static void ui_inspector(struct nk_context *ctx)`
- `ui_build` (function) `progs/nuklear/node_editor.c:622` `static void ui_build(struct nk_context *ctx, float win_w, float win_h)`
- `gui_run` (function) `progs/nuklear/node_editor.c:931` `static void gui_run(void)` -- circle.y = pin_y(n, k, 0) - PIN_R + oy; circle.w = PIN_DIAM; circle.h = PIN_DIAM; nk_fill_circle(canvas, circle...
- `main` (function) `progs/nuklear/node_editor.c:983` `int main(int argc, char **argv)`

## progs/nuklear/nuklear_minios.c
Depends on: `kernel/string.c`, `progs/nk_palette.h`, `progs/nuklear/nuklear_minios.h`, `progs/wl/wl_client.h`, `progs/wl/wl_mbox.h`
- `list` (function) `progs/nuklear/nuklear_minios.c:4` `* abstract draw command list (nk__begin/nk__next);`
- `nk_sys_time_ms` (function) `progs/nuklear/nuklear_minios.c:33` `long nk_sys_time_ms(void)` -- #include <string.h> #include <stdio.h> #include <math.h> #include "nuklear_minios.h" /* glibc program name for the...
- `nk_sys_kbd` (function) `progs/nuklear/nuklear_minios.c:38` `long nk_sys_kbd(void)`
- `nk_sys_palette` (function) `progs/nuklear/nuklear_minios.c:43` `long nk_sys_palette(const unsigned char *pal)`
- `nk_sys_kbd_raw` (function) `progs/nuklear/nuklear_minios.c:48` `long nk_sys_kbd_raw(int on)`
- `nk_sys_getpid` (function) `progs/nuklear/nuklear_minios.c:53` `long nk_sys_getpid(void)`
- `nk_client_probe` (function) `progs/nuklear/nuklear_minios.c:72` `static int nk_client_probe(void)`
- `nk_sys_vga_mode` (function) `progs/nuklear/nuklear_minios.c:114` `long nk_sys_vga_mode(int on)`
- `nk_sys_fb_info` (function) `progs/nuklear/nuklear_minios.c:121` `long nk_sys_fb_info(int *w, int *h, int *pitch)`
- `nk_sys_fb_info_rgb` (function) `progs/nuklear/nuklear_minios.c:137` `static long nk_sys_fb_info_rgb(int *w, int *h, int *pitch, int *rgb)`
- `nk_rgb_available` (function) `progs/nuklear/nuklear_minios.c:147` `int nk_rgb_available(void)`
- `rgb256_prepare` (function) `progs/nuklear/nuklear_minios.c:162` `static void rgb256_prepare(void)`
- `nk_idx_to_rgb` (function) `progs/nuklear/nuklear_minios.c:170` `void nk_idx_to_rgb(int idx, unsigned char *r, unsigned char *g,
                   unsigned char *b)`
- `cur_set` (function) `progs/nuklear/nuklear_minios.c:186` `static void cur_set(struct nk_color c)`
- `cur_bg_set` (function) `progs/nuklear/nuklear_minios.c:190` `static void cur_bg_set(struct nk_color c)`
- `nk_sys_mouse` (function) `progs/nuklear/nuklear_minios.c:193` `long nk_sys_mouse(int *xybw)`
- `nk_sys_mouse_badptr` (function) `progs/nuklear/nuklear_minios.c:198` `long nk_sys_mouse_badptr(void)`
- `nk_client_hash` (function) `progs/nuklear/nuklear_minios.c:216` `static unsigned nk_client_hash(const unsigned char *p, unsigned n)`
- `nk_client_publish` (function) `progs/nuklear/nuklear_minios.c:227` `static int nk_client_publish(void)`
- `nk_sys_nk_frame` (function) `progs/nuklear/nuklear_minios.c:280` `long nk_sys_nk_frame(int *origin)`
- `nk_mirror_box` (function) `progs/nuklear/nuklear_minios.c:314` `static void nk_mirror_box(char *dst, int cap)`
- `nk_mirror_emit` (function) `progs/nuklear/nuklear_minios.c:335` `static int nk_mirror_emit(const char *box, unsigned seq,
        const unsigned char *msg, int mlen)`
- `nk_mirror_tick` (function) `progs/nuklear/nuklear_minios.c:352` `static void nk_mirror_tick(void)`
- `nk_sys_gfx_set_title` (function) `progs/nuklear/nuklear_minios.c:409` `long nk_sys_gfx_set_title(const char *t)`
- `nk_build_palette` (function) `progs/nuklear/nuklear_minios.c:418` `void nk_build_palette(unsigned char *pal768)` -- The desktop-exact hybrid palette lives once in progs/nk_palette.h; * this wrapper keeps the platform signature while...
- `pal_prepare` (function) `progs/nuklear/nuklear_minios.c:427` `static void pal_prepare(void)`
- `col_to_idx` (function) `progs/nuklear/nuklear_minios.c:438` `static int col_to_idx(struct nk_color c)`
- `set_clip` (function) `progs/nuklear/nuklear_minios.c:469` `static void set_clip(int x, int y, int w, int h)`
- `px` (function) `progs/nuklear/nuklear_minios.c:479` `static void px(int x, int y, int c)`
- `px_bg` (function) `progs/nuklear/nuklear_minios.c:492` `static void px_bg(int x, int y, int c)` -- static void px(int x, int y, int c) { volatile uint8_t *d; if (x < clip_x || x >= clip_x + clip_w) return; if (y <...
- `px_idx` (function) `progs/nuklear/nuklear_minios.c:506` `static void px_idx(int x, int y, int c)` -- Index-owned pixels (IMAGE commands): RGB resolves through the exact * rgb256 table, so both buffers agree without a...
- `fill_rect` (function) `progs/nuklear/nuklear_minios.c:522` `static void fill_rect(int x, int y, int w, int h, int c)`
- `draw_line` (function) `progs/nuklear/nuklear_minios.c:529` `static void draw_line(int x0, int y0, int x1, int y1, int th, int c)`
- `fill_circle` (function) `progs/nuklear/nuklear_minios.c:547` `static void fill_circle(int cx, int cy, int r, int c)`
- `stroke_circle` (function) `progs/nuklear/nuklear_minios.c:553` `static void stroke_circle(int cx, int cy, int r, int th, int c)`
- `fill_poly` (function) `progs/nuklear/nuklear_minios.c:571` `static void fill_poly(int *xs, int *ys, int n, int c)` -- draw_line(cx + x, cy - y, cx - x, cy - y, th, c); draw_line(cx - x, cy + y, cx - x, cy - y, th, c); draw_line(cx +...
- `stroke_poly` (function) `progs/nuklear/nuklear_minios.c:594` `static void stroke_poly(int *xs, int *ys, int n, int th, int c)`
- `draw_text` (function) `progs/nuklear/nuklear_minios.c:601` `static void draw_text(int x, int y, const char *s, int len, int fg, int bg)`
- `draw_arc` (function) `progs/nuklear/nuklear_minios.c:615` `static void draw_arc(int cx, int cy, int r, float a0, float a1,
                     int filled, ...`
- `nk_rasterize` (function) `progs/nuklear/nuklear_minios.c:636` `void nk_rasterize(struct nk_context *ctx)`
- `nk_foreach` (function) `progs/nuklear/nuklear_minios.c:641` `nk_foreach(cmd, ctx)`
- `nk_minios_font_width` (function) `progs/nuklear/nuklear_minios.c:813` `static float nk_minios_font_width(nk_handle handle, float height,
                               ...` -- im->px[iy * im->w + ix]); } } break; } case NK_COMMAND_CUSTOM: break; default: break; } } } /* ---- Font (8x8...
- `nk_minios_font` (function) `progs/nuklear/nuklear_minios.c:819` `struct nk_user_font nk_minios_font(void)`
- `feed_key` (function) `progs/nuklear/nuklear_minios.c:854` `static void feed_key(struct nk_context *ctx, enum nk_keys key, int down)`
- `nk_set_scancode_hook` (function) `progs/nuklear/nuklear_minios.c:861` `void nk_set_scancode_hook(nk_scancode_cb cb, void *ud)`
- `handle_scancode` (function) `progs/nuklear/nuklear_minios.c:866` `static void handle_scancode(struct nk_context *ctx, unsigned char sc)`
- `nk_client_poll` (function) `progs/nuklear/nuklear_minios.c:914` `static void nk_client_poll(struct nk_context *ctx)` -- Client input pump: feed the pending .ev batch when its seq advanced, else hold the last state.
- `nk_poll_input` (function) `progs/nuklear/nuklear_minios.c:961` `void nk_poll_input(struct nk_context *ctx)`
- `nk_set_window_origin` (function) `progs/nuklear/nuklear_minios.c:1000` `void nk_set_window_origin(int x, int y)`
- `nk_quit_requested` (function) `progs/nuklear/nuklear_minios.c:1008` `int nk_quit_requested(void)` -- WM quit gesture latch: ESC or Alt+F4 pressed since the last poll.

## progs/nuklear/nuklear_minios.h
Depends on: `progs/minios_abi.h`
Imported by: `progs/doomedit/doomedit.c`, `progs/file/file.c`, `progs/nuklear/font8x8.c`, `progs/nuklear/node_editor.c`, `progs/nuklear/nuklear_minios.c`, `progs/paint/paint.c`, `progs/piano/piano.c`, `progs/vedit/vedit.c`
- `nk_rgb_available` (function) `progs/nuklear/nuklear_minios.h:33` `int nk_rgb_available(void);` -- RGB companion buffer (R,G,B byte order, NK_W x NK_H).
- `nk_idx_to_rgb` (function) `progs/nuklear/nuklear_minios.h:37` `void nk_idx_to_rgb(int idx, unsigned char *r, unsigned char *g, unsigned char *b);` -- Resolve one hybrid palette index to its exact RGB triple (canvas and preview mirrors that own indexed pixels reuse...
- `nk_sys_time_ms` (function) `progs/nuklear/nuklear_minios.h:41` `long nk_sys_time_ms(void);` -- Resolve one hybrid palette index to its exact RGB triple (canvas and preview mirrors that own indexed pixels reuse...
- `nk_sys_kbd` (function) `progs/nuklear/nuklear_minios.h:42` `long nk_sys_kbd(void);`
- `nk_sys_palette` (function) `progs/nuklear/nuklear_minios.h:43` `long nk_sys_palette(const unsigned char *pal768);`
- `nk_sys_kbd_raw` (function) `progs/nuklear/nuklear_minios.h:44` `long nk_sys_kbd_raw(int on);`
- `nk_sys_vga_mode` (function) `progs/nuklear/nuklear_minios.h:45` `long nk_sys_vga_mode(int on);`
- `nk_sys_fb_info` (function) `progs/nuklear/nuklear_minios.h:46` `long nk_sys_fb_info(int *w, int *h, int *pitch);`
- `nk_sys_mouse` (function) `progs/nuklear/nuklear_minios.h:47` `long nk_sys_mouse(int *xybw);`
- `nk_sys_mouse_badptr` (function) `progs/nuklear/nuklear_minios.h:51` `long nk_sys_mouse_badptr(void);` -- Call SYS_MOUSE with a pointer that is NOT in the user window; the kernel must reject it with -EFAULT.
- `nk_sys_nk_frame` (function) `progs/nuklear/nuklear_minios.h:52` `long nk_sys_nk_frame(int *origin);`
- `nk_sys_gfx_set_title` (function) `progs/nuklear/nuklear_minios.h:53` `long nk_sys_gfx_set_title(const char *t);` -- Call SYS_MOUSE with a pointer that is NOT in the user window; the kernel must reject it with -EFAULT.
- `nk_build_palette` (function) `progs/nuklear/nuklear_minios.h:57` `void nk_build_palette(unsigned char *pal768);` -- Hybrid palette: indices 0-14 are the desktop colors (kept so the desktop * behind the window never recolors); 15-255...
- `nk_minios_font` (function) `progs/nuklear/nuklear_minios.h:63` `struct nk_user_font nk_minios_font(void);` -- Hybrid palette: indices 0-14 are the desktop colors (kept so the desktop * behind the window never recolors); 15-255...
- `nk_rasterize` (function) `progs/nuklear/nuklear_minios.h:66` `void nk_rasterize(struct nk_context *ctx);` -- Hybrid palette: indices 0-14 are the desktop colors (kept so the desktop * behind the window never recolors); 15-255...
- `SYS_NK_FRAME` (function) `progs/nuklear/nuklear_minios.h:85` `* SYS_NK_FRAME (nk_set_window_origin). */ void nk_set_window_origin(int x, int y);`
- `nk_poll_input` (function) `progs/nuklear/nuklear_minios.h:87` `void nk_poll_input(struct nk_context *ctx);`
- `nk_quit_requested` (function) `progs/nuklear/nuklear_minios.h:92` `int nk_quit_requested(void);` -- WM quit gesture: ESC or Alt+F4 since the last poll (1 once, then clears).
- `nk_set_scancode_hook` (function) `progs/nuklear/nuklear_minios.h:101` `void nk_set_scancode_hook(nk_scancode_cb cb, void *ud);`

## progs/nuklear/nuklear_theme.c
Depends on: `kernel/string.c`, `progs/nuklear/nuklear_theme.h`
- `nk_theme_name_ok` (function) `progs/nuklear/nuklear_theme.c:37` `static int nk_theme_name_ok(const char *name)`
- `nk_theme_active` (function) `progs/nuklear/nuklear_theme.c:49` `int nk_theme_active(char *dst, int cap)`
- `nk_theme_parse_line` (function) `progs/nuklear/nuklear_theme.c:73` `static int nk_theme_parse_line(const char *line,
                               unsigned char rgb...`
- `nk_theme_probe` (function) `progs/nuklear/nuklear_theme.c:105` `int nk_theme_probe(const char *name, unsigned char rgb[NK_THEME_KEY_COUNT][3])`
- `nk_theme_apply` (function) `progs/nuklear/nuklear_theme.c:141` `int nk_theme_apply(struct nk_context *ctx, const char *name)`

## progs/nuklear/nuklear_theme.h
Imported by: `progs/doomedit/doomedit.c`, `progs/file/file.c`, `progs/nuklear/node_editor.c`, `progs/nuklear/nuklear_theme.c`, `progs/paint/paint.c`, `progs/piano/piano.c`, `progs/vedit/vedit.c`, `tests/test_theme.c`
- `nk_theme_active` (function) `progs/nuklear/nuklear_theme.h:62` `int nk_theme_active(char *dst, int cap);` -- X(scrollbar_cursor, 24) \ X(scrollbar_cursor_hover, 25) \ X(scrollbar_cursor_active, 26) \ X(tab_header, 27) \...
- `nk_theme_probe` (function) `progs/nuklear/nuklear_theme.h:65` `int nk_theme_probe(const char *name, unsigned char rgb[NK_THEME_KEY_COUNT][3]);` -- X(tab_header, 27) \ X(knob, 28) \ X(knob_cursor, 29) \ X(knob_cursor_hover, 30) \ X(knob_cursor_active, 31) #define...
- `nk_theme_apply` (function) `progs/nuklear/nuklear_theme.h:68` `int nk_theme_apply(struct nk_context *ctx, const char *name);` -- X(knob_cursor_hover, 30) \ X(knob_cursor_active, 31) #define NK_THEME_KEY_COUNT 32 struct nk_context; /** Resolve...

## progs/paint/paint.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`, `progs/nuklear/nuklear_minios.h`, `progs/nuklear/nuklear_theme.h`
- `paint_clamp` (function) `progs/paint/paint.c:92` `static int paint_clamp(int v, int lo, int hi)` -- static int paint_size = 0; static int paint_down = 0; static int paint_lastx; static int paint_lasty; static int...
- `paint_plot` (function) `progs/paint/paint.c:99` `static int paint_plot(unsigned char *buf, int w, int h, int x, int y,
                      unsig...` -- static float paint_recty; static char paint_path[PAINT_PATH_MAX] = PAINT_DEFAULT_PATH; static char...
- `paint_dab` (function) `progs/paint/paint.c:108` `static void paint_dab(unsigned char *buf, int w, int h, int x, int y,
                      unsig...` -- if (v > hi) return hi; return v; } /** Bound-checked pixel plot, fail closed outside the canvas. static int...
- `paint_line` (function) `progs/paint/paint.c:119` `static int paint_line(unsigned char *buf, int w, int h, int x0, int y0,
                      int...` -- } /** Filled square dab of side s centered on (x, y). static void paint_dab(unsigned char *buf, int w, int h, int x...
- `paint_rect_fill` (function) `progs/paint/paint.c:144` `static int paint_rect_fill(unsigned char *buf, int w, int h, int x0, int y0,
                    ...` -- paint_dab(buf, w, h, x0, y0, c, s); n++; } if (x0 == x1 && y0 == y1) break; { int e2 = 2 * err; if (e2 > -dy) { err...
- `paint_circle_fill` (function) `progs/paint/paint.c:161` `static int paint_circle_fill(unsigned char *buf, int w, int h, int cx,
                          ...` -- int xb = x0 < x1 ? x1 : x0; int ya = y0 < y1 ? y0 : y1; int yb = y0 < y1 ? y1 : y0; int x; int y; int n = 0; if...
- `paint_flood` (function) `progs/paint/paint.c:179` `static int paint_flood(unsigned char *buf, int w, int h, int x, int y,
                       uns...` -- Bounded flood fill with mark-on-push: every cell is marked once, so * the explicit stack never exceeds the canvas size.
- `paint_nearest` (function) `progs/paint/paint.c:223` `static int paint_nearest(const unsigned char *pal, unsigned r, unsigned g,
                      ...` -- } if (cy + 1 < h && buf[(cy + 1) * w + cx] == oc) { buf[(cy + 1) * w + cx] = nc; sx[top] = cx; sy[top] = cy + 1...
- `paint_pal` (function) `progs/paint/paint.c:240` `static const unsigned char *paint_pal(void)` -- unsigned long bd = 0xFFFFFFFFUL; unsigned k; if (!pal) return -1; for (k = 0; k < 256; k++) { long dr = (long)pal[k...
- `paint_path_ok` (function) `progs/paint/paint.c:251` `static int paint_path_ok(const char *p)` -- } /** Cached hybrid palette: built once, shared by picker, save and load. static const unsigned char...
- `paint_crc_init` (function) `progs/paint/paint.c:272` `static void paint_crc_init(void)`
- `paint_crc_update` (function) `progs/paint/paint.c:285` `static unsigned long paint_crc_update(unsigned long c,
                                      cons...`
- `paint_adler` (function) `progs/paint/paint.c:296` `static unsigned long paint_adler(const unsigned char *p, unsigned long n)` -- paint_crc_ready = 1; } static unsigned long paint_crc_update(unsigned long c, const unsigned char *p, unsigned long...
- `paint_put_u32` (function) `progs/paint/paint.c:308` `static int paint_put_u32(unsigned char *dst, unsigned long cap,
                         unsigned...` -- /** Adler-32 over one buffer (the zlib trailer of a single IDAT). static unsigned long paint_adler(const unsigned...
- `paint_put_bytes` (function) `progs/paint/paint.c:320` `static int paint_put_bytes(unsigned char *dst, unsigned long cap,
                           unsi...` -- /** Bound-checked big-endian u32 store for the PNG writer. static int paint_put_u32(unsigned char *dst, unsigned...
- `paint_png_encode` (function) `progs/paint/paint.c:333` `static long paint_png_encode(unsigned char *dst, unsigned long cap,
                             ...` -- Encode indexed pixels as 8-bit truecolor PNG (stored deflate blocks). * Returns the byte count or a negative code on...
- `paint_load_file` (function) `progs/paint/paint.c:461` `static int paint_load_file(const char *path)` -- Decode a PNG file into the canvas (top-left, clamped, nearest-mapped). * Reports through the status line, never a...
- `paint_save_file` (function) `progs/paint/paint.c:514` `static int paint_save_file(const char *path)` -- for (x = 0; x < cw; x++) { int v = paint_nearest(pal768, px[(y * w + x) * 3], px[(y * w + x) * 3 + 1], px[(y * w +...
- `paint_blit` (function) `progs/paint/paint.c:549` `static void paint_blit(int ox, int oy)` -- Blit the canvas into the NK back-buffer after rasterize (and its RGB * twin when the kernel maps it, so the canvas...
- `paint_ink` (function) `progs/paint/paint.c:570` `static unsigned char paint_ink(void)` -- int dx = ox + x; int dy = oy + y; unsigned char r, g, b; volatile uint8_t *d; if (dx < 0 || dx >= NK_W || dy < 0 ||...
- `paint_handle_input` (function) `progs/paint/paint.c:577` `static void paint_handle_input(struct nk_context *ctx)` -- nk_idx_to_rgb(paint_px[y * PAINT_W + x], &r, &g, &b); d = NK_RGB_BUF + ((dy * NK_W) + dx) * 3; d[0] = r; d[1] = g...
- `paint_ui_build` (function) `progs/paint/paint.c:636` `static void paint_ui_build(struct nk_context *ctx)` -- Build the file row, the exact-size canvas beside the tool panel, and the status row.
- `paint_pattern_present` (function) `progs/paint/paint.c:720` `static int paint_pattern_present(int fw, int fh, int fp, int *ox, int *oy)` -- Scan the whole framebuffer for the canvas marker run (first four swatches consecutive).
- `paint_selftest` (function) `progs/paint/paint.c:755` `static int paint_selftest(void)` -- break; } } if (hit) { ox = x; oy = y; return 1; } } } return 0; } /** Headless selftest for BDD: core vectors, PNG...
- `paint_gui_run` (function) `progs/paint/paint.c:942` `static void paint_gui_run(void)` -- printf("paint: composite did not land (canvas %d,%d origin %d,%d)\n", (int)paint_rectx, (int)paint_recty, origin[0]...
- `main` (function) `progs/paint/paint.c:992` `int main(int argc, char **argv)`

## progs/piano/piano.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`, `progs/nuklear/nuklear_minios.h`, `progs/nuklear/nuklear_theme.h`, `progs/src/opl3.c`
- `sys_pcm_open` (function) `progs/piano/piano.c:93` `static long sys_pcm_open(long flags)`
- `sys_pcm_write` (function) `progs/piano/piano.c:98` `static long sys_pcm_write(const void *buf, long len)` -- Returns bytes taken (NONBLOCK short count on backpressure, never a * stall), or negative on a dead path.
- `sys_pcm_close` (function) `progs/piano/piano.c:101` `static void sys_pcm_close(void)`
- `sys_yield` (function) `progs/piano/piano.c:104` `static void sys_yield(void)`
- `sys_present_idx` (function) `progs/piano/piano.c:112` `static long sys_present_idx(int *origin)` -- Indexed present (buffer id 1): the 288 KB indexed copy instead of the 864 KB RGB twin.
- `o3_op` (function) `progs/piano/piano.c:127` `static int o3_op(int ch, int is_car)`
- `o3_opreg` (function) `progs/piano/piano.c:131` `static void o3_opreg(int ch, int is_car, int regbase, int val)`
- `o3_chreg` (function) `progs/piano/piano.c:135` `static void o3_chreg(int ch, int regbase, int val)`
- `o3_note` (function) `progs/piano/piano.c:173` `static void o3_note(int ch, int midi, int on)`
- `midi_to_key` (function) `progs/piano/piano.c:211` `static int midi_to_key(int midi)`
- `clamp_midi` (function) `progs/piano/piano.c:234` `static int clamp_midi(int m)`
- `pedal_set` (function) `progs/piano/piano.c:241` `static void pedal_set(int on)` -- pressed scancode owns its channel until release.
- `voice_alloc` (function) `progs/piano/piano.c:255` `static int voice_alloc(void)`
- `note_off_key` (function) `progs/piano/piano.c:268` `static void note_off_key(int key)`
- `note_on_key` (function) `progs/piano/piano.c:281` `static void note_on_key(int key, int midi, int vel)`
- `kbd_semitone` (function) `progs/piano/piano.c:298` `static int kbd_semitone(int code)` -- ── PC-keyboard MIDI map (Fruity Loops style) ───────────────────────── PS/2 set-1 scancodes (7-bit code, E0 clear)...
- `kbd_all_off` (function) `progs/piano/piano.c:333` `static void kbd_all_off(void)`
- `note_on_sc` (function) `progs/piano/piano.c:339` `static void note_on_sc(int code, int vel)`
- `note_off_sc` (function) `progs/piano/piano.c:353` `static void note_off_sc(int code)`
- `piano_scancode` (function) `progs/piano/piano.c:369` `static void piano_scancode(int code, int make, int e0, void *ud)` -- Raw scancode hook (registered with nk_set_scancode_hook): note on/off * plus comma/period octave shift.
- `fx_configure` (function) `progs/piano/piano.c:421` `static void fx_configure(int delay_ms, int tremolo_pct, int clip, int vol)` -- #define FX_DELAY_CAP (RATE)           /* 1 s of delay at 22050 Hz #define FX_DELAY_MAX_MS 800 #define FX_FEEDBACK...
- `fx_process` (function) `progs/piano/piano.c:440` `static float fx_process(float x)`
- `sb_flush` (function) `progs/piano/piano.c:469` `static void sb_flush(void)` -- Flush held bytes to the low-latency ring.
- `render_audio` (function) `progs/piano/piano.c:484` `static void render_audio(long ms)`
- `key_rect` (function) `progs/piano/piano.c:511` `static void key_rect(int key, int *x, int *y, int *w, int *h)`
- `hit_key` (function) `progs/piano/piano.c:518` `static int hit_key(int mx, int my)`
- `hit_velocity` (function) `progs/piano/piano.c:535` `static int hit_velocity(int key, int my)` -- Velocity 1..100 from the click's vertical position inside a key: the very * top is soft, the bottom is loud.
- `ctrl_hit` (function) `progs/piano/piano.c:563` `static int ctrl_hit(int id, int mx, int my)`
- `ctrl_active` (function) `progs/piano/piano.c:567` `static int ctrl_active(int id)`
- `ctrl_press` (function) `progs/piano/piano.c:577` `static void ctrl_press(int id)`
- `ui_run` (function) `progs/piano/piano.c:594` `static void ui_run(int bench_ms)` -- case 1: if (octave < 2) octave++; break; case 2: if (volume > 0) volume -= 5; break; case 3: if (volume < 100)...
- `rate` (function) `progs/piano/piano.c:818` `* wait below caps the frame rate (bench mode skips it so the
         * benchmark still measures ...`
- `run_selftest` (function) `progs/piano/piano.c:836` `static int run_selftest(void)` -- sys_yield(); } else { sys_yield(); } } nk_set_scancode_hook(0, 0); nk_free(&ctx); nk_sys_kbd_raw(0)...
- `run_pcm2_probe` (function) `progs/piano/piano.c:1015` `static int run_pcm2_probe(void)` -- Headless pcm2 plumbing probe (BDD hook): open NONBLOCK, stream one 2048-byte pattern, close, reopen (release...
- `main` (function) `progs/piano/piano.c:1042` `int main(int argc, char **argv)`

## progs/pokemon/platform_minios.c
Depends on: `headers/audio.h`, `kernel/string.c`, `progs/minios_abi.h`, `progs/minios_png.h`
- `audible` (function) `progs/pokemon/platform_minios.c:36` `* voice is audible (noise SFX, sweep zaps), the raw mix estimate plays.
 *
 * Debug: heartbeat to...`
- `sys_kbd` (function) `progs/pokemon/platform_minios.c:75` `static long sys_kbd(void)`
- `sys_nk_frame` (function) `progs/pokemon/platform_minios.c:81` `static long sys_nk_frame(int *origin)`
- `sys_mouse` (function) `progs/pokemon/platform_minios.c:87` `static long sys_mouse(int *xybw)`
- `sys_vga_mode` (function) `progs/pokemon/platform_minios.c:93` `static long sys_vga_mode(int on)`
- `sys_kbd_raw` (function) `progs/pokemon/platform_minios.c:99` `static long sys_kbd_raw(int on)`
- `sys_palette` (function) `progs/pokemon/platform_minios.c:105` `static long sys_palette(const unsigned char *pal)`
- `sys_gfx_title` (function) `progs/pokemon/platform_minios.c:111` `static long sys_gfx_title(const char *t)`
- `sys_tone` (function) `progs/pokemon/platform_minios.c:117` `static long sys_tone(unsigned f)`
- `sys_pcm2_open` (function) `progs/pokemon/platform_minios.c:123` `static long sys_pcm2_open(long flags)`
- `sys_pcm2_write` (function) `progs/pokemon/platform_minios.c:129` `static long sys_pcm2_write(const void *buf, long len)`
- `sys_pcm2_close` (function) `progs/pokemon/platform_minios.c:135` `static void sys_pcm2_close(void)`
- `gain` (function) `progs/pokemon/platform_minios.c:142` `* timing gain (overshoot is microseconds against millisecond waits).
 * Difference-based, so it s...`
- `gb_platform_set_debug` (function) `progs/pokemon/platform_minios.c:190` `void gb_platform_set_debug(bool enabled)`
- `audio` (function) `progs/pokemon/platform_minios.c:218` `* PC speaker audio (DOOM-style: sparse syscalls from poll points) * * Per rendered frame, live voice frequencies...`
- `minios_audio_sample` (function) `progs/pokemon/platform_minios.c:262` `static void minios_audio_sample(GBContext *ctx, int16_t left, int16_t right)`
- `gb_voice_in_range` (function) `progs/pokemon/platform_minios.c:306` `static bool gb_voice_in_range(unsigned f)`
- `sample_apu_voices` (function) `progs/pokemon/platform_minios.c:310` `static void sample_apu_voices(gb_voice_t *v)`
- `minios_audio_play` (function) `progs/pokemon/platform_minios.c:330` `static void minios_audio_play(const gb_voice_t *v, bool pcm_audible,
                            ...`
- `rebuild_joypad` (function) `progs/pokemon/platform_minios.c:402` `static void rebuild_joypad(void)`
- `poll_keyboard` (function) `progs/pokemon/platform_minios.c:416` `static void poll_keyboard(void)`
- `push_332_palette` (function) `progs/pokemon/platform_minios.c:455` `static void push_332_palette(void)` -- 3-3-2 RGB palette ramp, pushed ONCE at init (not per frame). * Pixel index = (R & 0xE0) | ((G & 0xE0) >> 3) | ((B &...
- `menu` (function) `progs/pokemon/platform_minios.c:571` `* FILE menu (no Nuklear on purpose) * * A 16 px menu bar lives in the top margin the 2x GB image never touches * (it...`
- `ui_fringe_dirty` (function) `progs/pokemon/platform_minios.c:620` `static bool ui_fringe_dirty(uint32_t now)`
- `ui_fringe_sync` (function) `progs/pokemon/platform_minios.c:626` `static void ui_fringe_sync(uint32_t now)`
- `menu_fill` (function) `progs/pokemon/platform_minios.c:632` `static void menu_fill(int x0, int y0, int w, int h, uint8_t idx)`
- `menu_text` (function) `progs/pokemon/platform_minios.c:645` `static void menu_text(int x, int y, const char *s, uint8_t fg)`
- `menu_osd` (function) `progs/pokemon/platform_minios.c:664` `static void menu_osd(const char *s)`
- `menu_draw` (function) `progs/pokemon/platform_minios.c:670` `static void menu_draw(void)`
- `menu_item_at` (function) `progs/pokemon/platform_minios.c:700` `static int menu_item_at(int lx, int ly)`
- `menu_do_save` (function) `progs/pokemon/platform_minios.c:707` `static void menu_do_save(void)`
- `menu_do_load` (function) `progs/pokemon/platform_minios.c:723` `static void menu_do_load(void)`
- `menu_activate` (function) `progs/pokemon/platform_minios.c:742` `static void menu_activate(int it)`
- `poll_menu` (function) `progs/pokemon/platform_minios.c:776` `static void poll_menu(void)` -- Esc toggles, Up/Down move, Enter activates; the mouse is a bonus. * PS/2 Set 1: Esc = 0x01, Up = 0x48, Down = 0x50...
- `pokemon_art_load_one` (function) `progs/pokemon/platform_minios.c:844` `static int pokemon_art_load_one(const char *path, unsigned char **rgb,
                          ...`
- `pokemon_art_load` (function) `progs/pokemon/platform_minios.c:869` `static void pokemon_art_load(void)`
- `pokemon_art_draw_one` (function) `progs/pokemon/platform_minios.c:887` `static void pokemon_art_draw_one(const unsigned char *rgb, int sw, int sh,
                      ...`
- `pokemon_art_draw` (function) `progs/pokemon/platform_minios.c:925` `static void pokemon_art_draw(void)`
- `px_to_idx` (function) `progs/pokemon/platform_minios.c:956` `static uint8_t px_to_idx(uint32_t pixel)`
- `upload_frame` (function) `progs/pokemon/platform_minios.c:975` `static void upload_frame(const uint32_t *framebuffer)`
- `gb_platform_init` (function) `progs/pokemon/platform_minios.c:1056` `bool gb_platform_init(int scale)`
- `minios_persist_path` (function) `progs/pokemon/platform_minios.c:1088` `static void minios_persist_path(char *out, size_t n, const GBContext *ctx,
                      ...`
- `minios_legacy_path` (function) `progs/pokemon/platform_minios.c:1097` `static void minios_legacy_path(char *out, size_t n, const GBContext *ctx,
                       ...` -- Legacy ramdisk path (pre-MiniFS fix wrote bin/<id>.* onto volatile ramdisk).
- `minios_load_helper` (function) `progs/pokemon/platform_minios.c:1103` `static bool minios_load_helper(const char *path, void *data, size_t size,
                       ...`
- `minios_save_helper` (function) `progs/pokemon/platform_minios.c:1121` `static bool minios_save_helper(const char *path, const void *data, size_t size)`
- `minios_load_battery_ram` (function) `progs/pokemon/platform_minios.c:1132` `static bool minios_load_battery_ram(GBContext *ctx, const char *rom_name,
                       ...`
- `minios_save_battery_ram` (function) `progs/pokemon/platform_minios.c:1147` `static bool minios_save_battery_ram(GBContext *ctx, const char *rom_name,
                       ...`
- `minios_load_rtc_data` (function) `progs/pokemon/platform_minios.c:1157` `static bool minios_load_rtc_data(GBContext *ctx, const char *rom_name,
                          ...`
- `minios_save_rtc_data` (function) `progs/pokemon/platform_minios.c:1170` `static bool minios_save_rtc_data(GBContext *ctx, const char *rom_name,
                          ...`
- `minios_fast_forward` (function) `progs/pokemon/platform_minios.c:1208` `static inline bool minios_fast_forward(void)`
- `minios_state_path` (function) `progs/pokemon/platform_minios.c:1212` `static void minios_state_path(char *out, size_t n, const GBContext *ctx)`
- `minios_legacy_state_path` (function) `progs/pokemon/platform_minios.c:1217` `static void minios_legacy_state_path(char *out, size_t n, const GBContext *ctx)`
- `minios_autosave` (function) `progs/pokemon/platform_minios.c:1222` `static void minios_autosave(uint32_t now)`
- `poll_hotkeys` (function) `progs/pokemon/platform_minios.c:1236` `static void poll_hotkeys(void)` -- PS/2 Set 1: F5 = 0x3F, F8 = 0x42, Ctrl = 0x1D, S = 0x1F, L = 0x26, SPACE = 0x39, Shift = 0x2A/0x36.
- `gb_platform_register_context` (function) `progs/pokemon/platform_minios.c:1288` `void gb_platform_register_context(GBContext *ctx)`
- `gb_platform_shutdown` (function) `progs/pokemon/platform_minios.c:1310` `void gb_platform_shutdown(void)`
- `gb_platform_poll_events` (function) `progs/pokemon/platform_minios.c:1321` `bool gb_platform_poll_events(GBContext *ctx)`
- `gb_platform_render_frame` (function) `progs/pokemon/platform_minios.c:1330` `void gb_platform_render_frame(const uint32_t *framebuffer)`
- `frames` (function) `progs/pokemon/platform_minios.c:1366` `* frames (menu bar not on screen yet) and any frame after the
         * LCD-off path zeroed the ...`
- `gb_platform_present_framebuffer` (function) `progs/pokemon/platform_minios.c:1399` `void gb_platform_present_framebuffer(const uint32_t *framebuffer)`
- `gb_platform_render_lcd_off_frame` (function) `progs/pokemon/platform_minios.c:1411` `void gb_platform_render_lcd_off_frame(void)`
- `gb_platform_vsync` (function) `progs/pokemon/platform_minios.c:1433` `void gb_platform_vsync(uint32_t frame_cycles)`
- `gb_platform_set_benchmark_mode` (function) `progs/pokemon/platform_minios.c:1450` `void gb_platform_set_benchmark_mode(bool enabled)`
- `gb_platform_set_input_script` (function) `progs/pokemon/platform_minios.c:1454` `bool gb_platform_set_input_script(const char *script)`
- `gb_platform_set_input_record_file` (function) `progs/pokemon/platform_minios.c:1460` `void gb_platform_set_input_record_file(const char *path)`
- `gb_platform_set_persistence_dir` (function) `progs/pokemon/platform_minios.c:1465` `bool gb_platform_set_persistence_dir(const char *path)`
- `gb_platform_set_dump_frames` (function) `progs/pokemon/platform_minios.c:1474` `void gb_platform_set_dump_frames(const char *frames)`
- `gb_platform_set_dump_present_frames` (function) `progs/pokemon/platform_minios.c:1496` `void gb_platform_set_dump_present_frames(const char *frames)`
- `gb_platform_set_screenshot_prefix` (function) `progs/pokemon/platform_minios.c:1517` `void gb_platform_set_screenshot_prefix(const char *prefix)`
- `gb_platform_get_timing_info` (function) `progs/pokemon/platform_minios.c:1523` `void gb_platform_get_timing_info(GBPlatformTimingInfo *out)`
- `gb_platform_get_joypad` (function) `progs/pokemon/platform_minios.c:1530` `uint8_t gb_platform_get_joypad(void)`
- `gb_platform_set_title` (function) `progs/pokemon/platform_minios.c:1534` `void gb_platform_set_title(const char *title)`
- `gb_platform_get_smooth_lcd_transitions` (function) `progs/pokemon/platform_minios.c:1540` `bool gb_platform_get_smooth_lcd_transitions(void)`
- `gb_platform_set_smooth_lcd_transitions` (function) `progs/pokemon/platform_minios.c:1544` `void gb_platform_set_smooth_lcd_transitions(bool enabled)`
- `gb_platform_set_launcher_return_enabled` (function) `progs/pokemon/platform_minios.c:1548` `void gb_platform_set_launcher_return_enabled(bool enabled)`
- `gb_platform_get_exit_action` (function) `progs/pokemon/platform_minios.c:1552` `GBPlatformExitAction gb_platform_get_exit_action(void)`
- `gb_platform_submit_port_frame` (function) `progs/pokemon/platform_minios.c:1556` `void gb_platform_submit_port_frame(void *user, const GBPortFrame *frame)`
- `gb_platform_test_audio_concurrency` (function) `progs/pokemon/platform_minios.c:1562` `bool gb_platform_test_audio_concurrency(uint32_t frames,
                                        ...` -- void gb_platform_set_launcher_return_enabled(bool enabled) { (void)enabled; } GBPlatformExitAction...
- `gb_platform_test_inject_persistence_fault` (function) `progs/pokemon/platform_minios.c:1571` `void gb_platform_test_inject_persistence_fault(
    GBPersistenceTestTarget target,
    GBPersist...`


Next: [API_p18.md](API_p18.md)
