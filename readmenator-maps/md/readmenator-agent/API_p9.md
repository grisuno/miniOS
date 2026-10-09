# API (page 9 of 19)
Previous: [API_p8.md](API_p8.md)

## progs/asm/lzss.s
- `lz_win` (function) `progs/asm/lzss.s:3`
- `lz_src` (function) `progs/asm/lzss.s:7`
- `lz_srclen` (function) `progs/asm/lzss.s:11`
- `lz_srcpos` (function) `progs/asm/lzss.s:15`
- `lz_dst` (function) `progs/asm/lzss.s:19`
- `lz_dstcap` (function) `progs/asm/lzss.s:23`
- `lz_dstlen` (function) `progs/asm/lzss.s:27`
- `lz_err` (function) `progs/asm/lzss.s:31`
- `lz_buf` (function) `progs/asm/lzss.s:35`
- `lz_mask` (function) `progs/asm/lzss.s:39`
- `lz_in_getc` (function) `progs/asm/lzss.s:43`
- `lz_out_put` (function) `progs/asm/lzss.s:79`
- `lz_putbit1` (function) `progs/asm/lzss.s:116`
- `lz_putbit0` (function) `progs/asm/lzss.s:174`
- `lz_flush_bits` (function) `progs/asm/lzss.s:223`
- `lz_out_literal` (function) `progs/asm/lzss.s:251`
- `lz_out_pair` (function) `progs/asm/lzss.s:321`
- `lz_next_mb` (function) `progs/asm/lzss.s:447`
- `lz_encode` (function) `progs/asm/lzss.s:451`
- `lz_getbit` (function) `progs/asm/lzss.s:1051`
- `lz_decode` (function) `progs/asm/lzss.s:1171`
- `lz_hdr_put` (function) `progs/asm/lzss.s:1514`
- `lz_hdr_get` (function) `progs/asm/lzss.s:1629`
- `lz_has` (function) `progs/asm/lzss.s:1782`
- `lz_read_all` (function) `progs/asm/lzss.s:1935`
- `lz_write_all` (function) `progs/asm/lzss.s:2150`
- `lz_compress` (function) `progs/asm/lzss.s:2257`
- `lz_decompress` (function) `progs/asm/lzss.s:2628`
- `main` (function) `progs/asm/lzss.s:3178`

## progs/asm/mtop.s
- `h_cpu` (function) `progs/asm/mtop.s:3`
- `h_mem` (function) `progs/asm/mtop.s:7`
- `h_fill` (function) `progs/asm/mtop.s:11`
- `last_dns` (function) `progs/asm/mtop.s:15`
- `last_dns_ms` (function) `progs/asm/mtop.s:19`
- `last_sock` (function) `progs/asm/mtop.s:23`
- `prev_total` (function) `progs/asm/mtop.s:27`
- `prev_idle` (function) `progs/asm/mtop.s:31`
- `have_prev` (function) `progs/asm/mtop.s:35`
- `disk_f` (function) `progs/asm/mtop.s:39`
- `disk_path` (function) `progs/asm/mtop.s:43`
- `sc3` (function) `progs/asm/mtop.s:47`
- `mtop_time` (function) `progs/asm/mtop.s:78`
- `mtop_rtc` (function) `progs/asm/mtop.s:106`
- `mtop_key` (function) `progs/asm/mtop.s:137`
- `mtop_minfo` (function) `progs/asm/mtop.s:165`
- `emit` (function) `progs/asm/mtop.s:206`
- `mtop_quit_key` (function) `progs/asm/mtop.s:241`
- `mtop_clear_ansi` (function) `progs/asm/mtop.s:317`
- `mtop_clear` (function) `progs/asm/mtop.s:401`
- `mtop_atoi` (function) `progs/asm/mtop.s:443`
- `mtop_putu` (function) `progs/asm/mtop.s:569`
- `mtop_put2` (function) `progs/asm/mtop.s:725`
- `mtop_put_kb` (function) `progs/asm/mtop.s:765`
- `mtop_bar` (function) `progs/asm/mtop.s:887`
- `mtop_hist_max` (function) `progs/asm/mtop.s:1038`
- `mtop_hist_push` (function) `progs/asm/mtop.s:1106`
- `mtop_spark` (function) `progs/asm/mtop.s:1201`
- `mtop_mem` (function) `progs/asm/mtop.s:1452`
- `mtop_cpu` (function) `progs/asm/mtop.s:1556`
- `mtop_disk_open` (function) `progs/asm/mtop.s:1842`
- `mtop_disk_read` (function) `progs/asm/mtop.s:1966`
- `mtop_net_probe` (function) `progs/asm/mtop.s:2128`
- `mtop_frame` (function) `progs/asm/mtop.s:2275`
- `main` (function) `progs/asm/mtop.s:3831`

## progs/asm/w1.s
- `main` (function) `progs/asm/w1.s:3`

## progs/doomedit/doomedit.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`, `progs/nuklear/nuklear_minios.h`, `progs/nuklear/nuklear_theme.h`
- `dmap_thing_type` (function) `progs/doomedit/doomedit.c:165` `static int dmap_thing_type(int cell)` -- Thing type ids from the engine mobjinfo table, each with its sprite * verified present in the shareware IWAD.
- `dmap_push_history` (function) `progs/doomedit/doomedit.c:272` `static void dmap_push_history(void)`
- `dmap_undo` (function) `progs/doomedit/doomedit.c:289` `static int dmap_undo(void)`
- `dmap_redo` (function) `progs/doomedit/doomedit.c:307` `static int dmap_redo(void)`
- `dmap_apply_cell` (function) `progs/doomedit/doomedit.c:326` `static void dmap_apply_cell(int r, int c, int brush)` -- dmap_undo_h[dmap_undo_top] = dmap_h; memcpy(dmap_undo_g[dmap_undo_top], dmap_grid, sizeof(dmap_grid))...
- `dmap_flood_fill` (function) `progs/doomedit/doomedit.c:344` `static void dmap_flood_fill(int sr, int sc, int new_cell)` -- if (brush == DMAP_PLAYER || brush == DMAP_EXIT) { for (rr = 0; rr < dmap_h; rr++) for (cc = 0; cc < dmap_w; cc++) if...
- `dmap_draw_line` (function) `progs/doomedit/doomedit.c:383` `static void dmap_draw_line(int r0, int c0, int r1, int c1, int cell)` -- if (nr < 0 || nc < 0 || nr >= dmap_h || nc >= dmap_w) continue; if (dmap_grid[nr][nc] != old_cell) continue...
- `dmap_draw_rect` (function) `progs/doomedit/doomedit.c:411` `static void dmap_draw_rect(int r0, int c0, int r1, int c1, int cell)` -- e2 = err; if (e2 > -dr) { err -= dc; r0 += sr; } if (e2 < dc) { err += dr; c0 += sc; } } dmap_level_sel = 0; } /**...
- `dmap_reach_map` (function) `progs/doomedit/doomedit.c:440` `static void dmap_reach_map(int seen[DMAP_MAX_H][DMAP_MAX_W])` -- for (r = rt; r <= rb; r++) { if (r >= 0 && r < dmap_h && cl >= 0 && cl < dmap_w) { if (dmap_grid[r][cl] !=...
- `dmap_path_len` (function) `progs/doomedit/doomedit.c:480` `static int dmap_path_len(void)` -- int nr = cr + dirs[k][0], nc = cc + dirs[k][1]; if (nr < 0 || nc < 0 || nr >= dmap_h || nc >= dmap_w) continue; if...
- `dmap_stats` (function) `progs/doomedit/doomedit.c:522` `static void dmap_stats(char *out, int max)` -- if (nr < 0 || nc < 0 || nr >= dmap_h || nc >= dmap_w) continue; if (dist[nr][nc] >= 0 ||...
- `dmap_spawn` (function) `progs/doomedit/doomedit.c:550` `static long dmap_spawn(const char *path, int argc, const char **argv)` -- } path = dmap_path_len(); if (dmap_validate(msg, sizeof(msg)) == 0) snprintf(out, (size_t)max, "%dx%d %d sect path...
- `dmap_vga` (function) `progs/doomedit/doomedit.c:561` `static long dmap_vga(int on)` -- static int dmap_validate(char *msg, int max); /** Run a program through SYS_SPAWN, preserving the editor. static...
- `dmap_is_wall` (function) `progs/doomedit/doomedit.c:570` `static int dmap_is_wall(int row, int col)` -- : "rcx", "r11", "memory"); return ret; } /** Release or reclaim the display around a spawned child. static long...
- `dmap_walkable` (function) `progs/doomedit/doomedit.c:577` `static int dmap_walkable(int cell)` -- __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_VGA_MODE), "D"((long)on) : "rcx", "r11", "memory"); return...
- `dmap_cell_class` (function) `progs/doomedit/doomedit.c:583` `static int dmap_cell_class(int cell)` -- /** True for solid cells; out of bounds counts as wall to stay closed. static int dmap_is_wall(int row, int col) {...
- `dmap_cell_color` (function) `progs/doomedit/doomedit.c:594` `static struct nk_color dmap_cell_color(int cell)` -- } /** Sector class of a walkable cell: doors stand alone, styles never merge. static int dmap_cell_class(int cell) {...
- `dmap_new` (function) `progs/doomedit/doomedit.c:639` `static void dmap_new(void)` -- case DMAP_RSUIT: case DMAP_CMAP: case DMAP_LAMP: return nk_rgb(200, 90, 200); case DMAP_KEYB: case DMAP_KEYR: case...
- `dmap_recenter` (function) `progs/doomedit/doomedit.c:804` `static void dmap_recenter(void)`
- `dmap_load_preset` (function) `progs/doomedit/doomedit.c:816` `static int dmap_load_preset(int idx)` -- /** Move the preview camera onto the player start tile. static void dmap_recenter(void) { int r, c; for (r = 0; r <...
- `dmap_rand` (function) `progs/doomedit/doomedit.c:849` `static unsigned dmap_rand(void)` -- int ch = dmap_levels[idx][row][k]; if (!dmap_walkable(ch) && ch != DMAP_WALL) return -1; dmap_grid[row][k] =...
- `dmap_free_cell` (function) `progs/doomedit/doomedit.c:857` `static int dmap_free_cell(int *r, int *c)` -- dmap_level_sel = idx + 1; snprintf(dmap_status, sizeof(dmap_status), "level: %s", dmap_level_names[idx]); return 0...
- `dmap_random_map` (function) `progs/doomedit/doomedit.c:871` `static void dmap_random_map(unsigned seed)` -- Procedural map of connected rooms: several non-overlapping rect rooms carved out of solid rock, joined in sequence...
- `dmap_load` (function) `progs/doomedit/doomedit.c:1077` `static int dmap_load(const char *path)` -- } if (dmap_validate(msg, sizeof(msg)) == 0) { dmap_recenter(); snprintf(dmap_status, sizeof(dmap_status), "random...
- `dmap_save_txt` (function) `progs/doomedit/doomedit.c:1129` `static int dmap_save_txt(const char *path)` -- if (row < 3 || w < 3 || w > DMAP_MAX_W) return -1; dmap_push_history(); dmap_anchor_active = 0; dmap_w = w; dmap_h =...
- `areas` (function) `progs/doomedit/doomedit.c:1150` `* floor areas (doors stand alone, dark and nukage never merge);`
- `dmap_label_regions` (function) `progs/doomedit/doomedit.c:1163` `static int dmap_label_regions(void)` -- Sector table backing the multi-sector exporter.
- `dmap_validate` (function) `progs/doomedit/doomedit.c:1244` `static int dmap_validate(char *msg, int max)` -- dmap_sec_floor[nsec] = DMAP_FLOOR_H; dmap_sec_ceil[nsec] = DMAP_CEIL_H; dmap_sec_flat[nsec] = DMAP_FLOOR_FLAT...
- `dmap_w8` (function) `progs/doomedit/doomedit.c:1317` `static void dmap_w8(unsigned v)`
- `dmap_w16` (function) `progs/doomedit/doomedit.c:1318` `static void dmap_w16(int v)`
- `dmap_w32` (function) `progs/doomedit/doomedit.c:1322` `static void dmap_w32(int v)`
- `dmap_wtex` (function) `progs/doomedit/doomedit.c:1326` `static void dmap_wtex(const char *name)`
- `dmap_seg_angle` (function) `progs/doomedit/doomedit.c:1333` `static int dmap_seg_angle(int dx, int dy)` -- dmap_wp++ = (unsigned char)(v & 0xFF); dmap_wp++ = (unsigned char)((v >> 8) & 0xFF); } static void dmap_w32(int v) {...
- `dmap_build_wad` (function) `progs/doomedit/doomedit.c:1343` `static int dmap_build_wad(int *size_out)` -- Compile the grid into a vanilla multi-sector E1M1 PWAD image.
- `dmap_export_wad` (function) `progs/doomedit/doomedit.c:1660` `static int dmap_export_wad(const char *path)` -- dmap_wp = dmap_wad; dmap_w8('P'); dmap_w8('W'); dmap_w8('A'); dmap_w8('D'); dmap_w32(11); dmap_w32(table_off)...
- `dmap_check_wad` (function) `progs/doomedit/doomedit.c:1675` `static int dmap_check_wad(const char *path)` -- int size = 0; FILE *fp; size_t wrote; if (dmap_build_wad(&size) != 0) return -1; fp = fopen(path, "wb"); if (!fp)...
- `dmap_preview` (function) `progs/doomedit/doomedit.c:1693` `static void dmap_preview(struct nk_command_buffer *canvas, struct nk_rect area)` -- if (!fp) return -1; if (fread(head, 1, 12, fp) != 12) { fclose(fp); return -1; } fclose(fp); magic_ok = head[0] ==...
- `dmap_brush_combo` (function) `progs/doomedit/doomedit.c:1760` `static void dmap_brush_combo(struct nk_context *ctx)` -- dist = 0.05f; line_h = (int)(area.h / dist); if (line_h > (int)area.h) line_h = (int)area.h; y0 = (int)(area.y +...
- `dmap_canvas` (function) `progs/doomedit/doomedit.c:1773` `static void dmap_canvas(struct nk_context *ctx)` -- Paintable tile canvas with per-category colors.
- `dmap_preview_row` (function) `progs/doomedit/doomedit.c:1863` `static void dmap_preview_row(struct nk_context *ctx)` -- dmap_draw_rect(dmap_anchor_r, dmap_anchor_c, r, c, dmap_brush); dmap_anchor_active = 0; dmap_level_sel = 0; } } else...
- `dmap_run_map` (function) `progs/doomedit/doomedit.c:1898` `static void dmap_run_map(void)` -- } if (nk_button_label(ctx, "Reset")) { int r, c; for (r = 0; r < dmap_h; r++) for (c = 0; c < dmap_w; c++) if...
- `dmap_scancode` (function) `progs/doomedit/doomedit.c:2037` `static void dmap_scancode(int code, int make, int e0, void *ud)`
- `dmap_gui_run` (function) `progs/doomedit/doomedit.c:2056` `static void dmap_gui_run(void)` -- dmap_ctrl_held = make; return; } if (!make || !dmap_ctrl_held) return; if (code == 0x13) dmap_run_requested = 1...
- `dmap_demo_room` (function) `progs/doomedit/doomedit.c:2110` `static void dmap_demo_room(void)` -- nk_set_window_origin(origin[0], origin[1]); nk_clear(&ctx); { unsigned t0 = (unsigned)nk_sys_time_ms(); while...
- `dmap_selftest` (function) `progs/doomedit/doomedit.c:2122` `static int dmap_selftest(void)` -- /** Headless demo room shared by --demo and the selftest build check. static void dmap_demo_room(void) { dmap_w = 9...
- `main` (function) `progs/doomedit/doomedit.c:2246` `int main(int argc, char **argv)`

## progs/doomgeneric/am_map.c
Depends on: `progs/doomgeneric/am_map.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_cheat.h`, `progs/doomgeneric/m_controls.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/p_local.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/st_stuff.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `AM_getIslope` (function) `progs/doomgeneric/am_map.c:275` `void
AM_getIslope
( mline_t*	ml,
  islope_t*	is )`
- `AM_activateNewScale` (function) `progs/doomgeneric/am_map.c:293` `void AM_activateNewScale(void)`
- `AM_saveScaleAndLoc` (function) `progs/doomgeneric/am_map.c:308` `void AM_saveScaleAndLoc(void)`
- `AM_restoreScaleAndLoc` (function) `progs/doomgeneric/am_map.c:319` `void AM_restoreScaleAndLoc(void)`
- `AM_addMark` (function) `progs/doomgeneric/am_map.c:343` `void AM_addMark(void)` -- adds a marker at the current location
- `AM_findMinMaxBoundaries` (function) `progs/doomgeneric/am_map.c:355` `void AM_findMinMaxBoundaries(void)` -- Determines bounding box of all vertices, sets global variables controlling zoom range.
- `AM_changeWindowLoc` (function) `progs/doomgeneric/am_map.c:395` `void AM_changeWindowLoc(void)`
- `AM_initVariables` (function) `progs/doomgeneric/am_map.c:424` `void AM_initVariables(void)`
- `AM_loadPics` (function) `progs/doomgeneric/am_map.c:480` `void AM_loadPics(void)`
- `AM_unloadPics` (function) `progs/doomgeneric/am_map.c:493` `void AM_unloadPics(void)`
- `AM_clearMarks` (function) `progs/doomgeneric/am_map.c:505` `void AM_clearMarks(void)`
- `AM_LevelInit` (function) `progs/doomgeneric/am_map.c:518` `void AM_LevelInit(void)` -- should be called at the start of every level right now, i figure it out myself
- `AM_Stop` (function) `progs/doomgeneric/am_map.c:541` `void AM_Stop (void)`
- `AM_Start` (function) `progs/doomgeneric/am_map.c:554` `void AM_Start (void)`
- `AM_minOutWindowScale` (function) `progs/doomgeneric/am_map.c:573` `void AM_minOutWindowScale(void)` -- set the window scale to the maximum size
- `AM_maxOutWindowScale` (function) `progs/doomgeneric/am_map.c:583` `void AM_maxOutWindowScale(void)` -- set the window scale to the minimum size
- `AM_Responder` (function) `progs/doomgeneric/am_map.c:595` `boolean
AM_Responder
( event_t*	ev )`
- `AM_changeWindowScale` (function) `progs/doomgeneric/am_map.c:742` `void AM_changeWindowScale(void)` -- Zooming
- `AM_doFollowPlayer` (function) `progs/doomgeneric/am_map.c:761` `void AM_doFollowPlayer(void)`
- `AM_updateLightLev` (function) `progs/doomgeneric/am_map.c:785` `void AM_updateLightLev(void)`
- `AM_Ticker` (function) `progs/doomgeneric/am_map.c:806` `void AM_Ticker (void)` -- Updates on Game Tick
- `AM_clearFB` (function) `progs/doomgeneric/am_map.c:834` `void AM_clearFB(int color)` -- Clear automap frame buffer.
- `AM_clipMline` (function) `progs/doomgeneric/am_map.c:848` `boolean
AM_clipMline
( mline_t*	ml,
  fline_t*	fl )`
- `AM_drawFline` (function) `progs/doomgeneric/am_map.c:984` `void
AM_drawFline
( fline_t*	fl,
  int		color )`
- `AM_drawMline` (function) `progs/doomgeneric/am_map.c:1062` `void
AM_drawMline
( mline_t*	ml,
  int		color )`
- `AM_drawGrid` (function) `progs/doomgeneric/am_map.c:1077` `void AM_drawGrid(int color)` -- Draws flat (floor/ceiling tile) aligned grid lines.
- `AM_drawWalls` (function) `progs/doomgeneric/am_map.c:1123` `void AM_drawWalls(void)` -- Determines visible lines, draws them.
- `AM_rotate` (function) `progs/doomgeneric/am_map.c:1179` `void
AM_rotate
( fixed_t*	x,
  fixed_t*	y,
  angle_t	a )`
- `AM_drawLineCharacter` (function) `progs/doomgeneric/am_map.c:1198` `void
AM_drawLineCharacter
( mline_t*	lineguy,
  int		lineguylines,
  fixed_t	scale,
  angle_t	ang...`
- `AM_drawPlayers` (function) `progs/doomgeneric/am_map.c:1246` `void AM_drawPlayers(void)`
- `AM_drawThings` (function) `progs/doomgeneric/am_map.c:1291` `void
AM_drawThings
( int	colors,
  int 	colorrange)`
- `AM_drawMarks` (function) `progs/doomgeneric/am_map.c:1311` `void AM_drawMarks(void)`
- `AM_drawCrosshair` (function) `progs/doomgeneric/am_map.c:1332` `void AM_drawCrosshair(int color)`
- `AM_Drawer` (function) `progs/doomgeneric/am_map.c:1338` `void AM_Drawer (void)`

## progs/doomgeneric/am_map.h
Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/m_cheat.h`
Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/st_stuff.c`
- `AM_Ticker` (function) `progs/doomgeneric/am_map.h:35` `void AM_Ticker (void);` -- Called by main loop.
- `AM_Drawer` (function) `progs/doomgeneric/am_map.h:39` `void AM_Drawer (void);` -- Called by main loop, called instead of view drawer if automap active.
- `AM_Stop` (function) `progs/doomgeneric/am_map.h:43` `void AM_Stop (void);` -- Called to force the automap to quit if the level is completed while it is up.

## progs/doomgeneric/d_event.c
Depends on: `progs/doomgeneric/d_event.h`
- `D_PostEvent` (function) `progs/doomgeneric/d_event.c:35` `void D_PostEvent (event_t* ev)` -- D_PostEvent Called by the I/O functions when input is detected
- `D_PopEvent` (function) `progs/doomgeneric/d_event.c:43` `event_t *D_PopEvent(void)`

## progs/doomgeneric/d_event.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/am_map.h`, `progs/doomgeneric/d_event.c`, `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/f_finale.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_joystick.c`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_menu.h`, `progs/doomgeneric/p_pspr.c`, `progs/doomgeneric/p_user.c`, `progs/doomgeneric/st_stuff.h`
- `D_PostEvent` (function) `progs/doomgeneric/d_event.h:129` `void D_PostEvent (event_t *ev);` -- Called by IO functions when input is detected.
- `D_PopEvent` (function) `progs/doomgeneric/d_event.h:133` `event_t *D_PopEvent(void);`

## progs/doomgeneric/d_iwad.c
Depends on: `kernel/string.c`, `progs/doomgeneric/config.h`, `progs/doomgeneric/d_iwad.h`, `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `AddIWADDir` (function) `progs/doomgeneric/d_iwad.c:64` `static void AddIWADDir(char *dir)`
- `GetRegistryString` (function) `progs/doomgeneric/d_iwad.c:192` `static char *GetRegistryString(registry_value_t *reg_val)`
- `CheckUninstallStrings` (function) `progs/doomgeneric/d_iwad.c:236` `static void CheckUninstallStrings(void)`
- `CheckCollectorsEdition` (function) `progs/doomgeneric/d_iwad.c:270` `static void CheckCollectorsEdition(void)`
- `CheckSteamEdition` (function) `progs/doomgeneric/d_iwad.c:297` `static void CheckSteamEdition(void)`
- `CheckSteamGUSPatches` (function) `progs/doomgeneric/d_iwad.c:324` `static void CheckSteamGUSPatches(void)`
- `CheckDOSDefaults` (function) `progs/doomgeneric/d_iwad.c:364` `static void CheckDOSDefaults(void)`
- `DirIsFile` (function) `progs/doomgeneric/d_iwad.c:391` `static boolean DirIsFile(char *path, char *filename)`
- `CheckDirectoryHasIWAD` (function) `progs/doomgeneric/d_iwad.c:408` `static char *CheckDirectoryHasIWAD(char *dir, char *iwadname)`
- `SearchDirectoryForIWAD` (function) `progs/doomgeneric/d_iwad.c:449` `static char *SearchDirectoryForIWAD(char *dir, int mask, GameMission_t *mission)`
- `IdentifyIWADByName` (function) `progs/doomgeneric/d_iwad.c:477` `static GameMission_t IdentifyIWADByName(char *name, int mask)`
- `AddDoomWadPath` (function) `progs/doomgeneric/d_iwad.c:518` `static void AddDoomWadPath(void)`
- `BuildIWADDirList` (function) `progs/doomgeneric/d_iwad.c:569` `static void BuildIWADDirList(void)`
- `D_FindWADByName` (function) `progs/doomgeneric/d_iwad.c:630` `char *D_FindWADByName(char *name)`
- `D_TryFindWADByName` (function) `progs/doomgeneric/d_iwad.c:681` `char *D_TryFindWADByName(char *filename)`
- `D_FindIWAD` (function) `progs/doomgeneric/d_iwad.c:704` `char *D_FindIWAD(int mask, GameMission_t *mission)`
- `D_FindAllIWADs` (function) `progs/doomgeneric/d_iwad.c:757` `const iwad_t **D_FindAllIWADs(int mask)`
- `D_SaveGameIWADName` (function) `progs/doomgeneric/d_iwad.c:796` `char *D_SaveGameIWADName(GameMission_t gamemission)`
- `D_SuggestIWADName` (function) `progs/doomgeneric/d_iwad.c:820` `char *D_SuggestIWADName(GameMission_t mission, GameMode_t mode)`
- `D_SuggestGameName` (function) `progs/doomgeneric/d_iwad.c:835` `char *D_SuggestGameName(GameMission_t mission, GameMode_t mode)`

## progs/doomgeneric/d_iwad.h
Depends on: `progs/doomgeneric/d_mode.h`
Imported by: `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/w_main.c`, `progs/doomgeneric/w_wad.c`
- `D_FindWADByName` (function) `progs/doomgeneric/d_iwad.h:42` `char *D_FindWADByName(char *filename);`
- `D_TryFindWADByName` (function) `progs/doomgeneric/d_iwad.h:43` `char *D_TryFindWADByName(char *filename);`
- `D_FindIWAD` (function) `progs/doomgeneric/d_iwad.h:44` `char *D_FindIWAD(int mask, GameMission_t *mission);`
- `D_FindAllIWADs` (function) `progs/doomgeneric/d_iwad.h:45` `const iwad_t **D_FindAllIWADs(int mask);`
- `D_SaveGameIWADName` (function) `progs/doomgeneric/d_iwad.h:46` `char *D_SaveGameIWADName(GameMission_t gamemission);`
- `D_SuggestIWADName` (function) `progs/doomgeneric/d_iwad.h:47` `char *D_SuggestIWADName(GameMission_t mission, GameMode_t mode);`
- `D_SuggestGameName` (function) `progs/doomgeneric/d_iwad.h:48` `char *D_SuggestGameName(GameMission_t mission, GameMode_t mode);`
- `D_CheckCorrectIWAD` (function) `progs/doomgeneric/d_iwad.h:49` `void D_CheckCorrectIWAD(GameMission_t mission);`

## progs/doomgeneric/d_loop.c
Depends on: `kernel/string.c`, `progs/doomgeneric/d_event.h`, `progs/doomgeneric/d_loop.h`, `progs/doomgeneric/d_ticcmd.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_fixed.h`, `progs/doomgeneric/net_client.h`, `progs/doomgeneric/net_gui.h`, `progs/doomgeneric/net_io.h`, `progs/doomgeneric/net_loop.h`, `progs/doomgeneric/net_query.h`, `progs/doomgeneric/net_sdl.h`, `progs/doomgeneric/net_server.h`
- `GetAdjustedTime` (function) `progs/doomgeneric/d_loop.c:119` `static int GetAdjustedTime(void)`
- `BuildNewTic` (function) `progs/doomgeneric/d_loop.c:136` `static boolean BuildNewTic(void)`
- `NetUpdate` (function) `progs/doomgeneric/d_loop.c:203` `void NetUpdate (void)`
- `D_Disconnected` (function) `progs/doomgeneric/d_loop.c:252` `static void D_Disconnected(void)`
- `D_ReceiveTic` (function) `progs/doomgeneric/d_loop.c:271` `void D_ReceiveTic(ticcmd_t *ticcmds, boolean *players_mask)`
- `D_StartGameLoop` (function) `progs/doomgeneric/d_loop.c:305` `void D_StartGameLoop(void)`
- `BlockUntilStart` (function) `progs/doomgeneric/d_loop.c:315` `static void BlockUntilStart(net_gamesettings_t *settings,
                            netgame_sta...`
- `D_StartNetGame` (function) `progs/doomgeneric/d_loop.c:340` `void D_StartNetGame(net_gamesettings_t *settings,
                    netgame_startup_callback_t ...`
- `D_InitNetGame` (function) `progs/doomgeneric/d_loop.c:452` `boolean D_InitNetGame(net_connect_data_t *connect_data)`
- `D_QuitNetGame` (function) `progs/doomgeneric/d_loop.c:560` `void D_QuitNetGame (void)` -- D_QuitNetGame Called before quitting to leave a net game without hanging the other players
- `GetLowTic` (function) `progs/doomgeneric/d_loop.c:568` `static int GetLowTic(void)`
- `OldNetSync` (function) `progs/doomgeneric/d_loop.c:591` `static void OldNetSync(void)`
- `PlayersInGame` (function) `progs/doomgeneric/d_loop.c:642` `static boolean PlayersInGame(void)`
- `TicdupSquash` (function) `progs/doomgeneric/d_loop.c:672` `static void TicdupSquash(ticcmd_set_t *set)`
- `SinglePlayerClear` (function) `progs/doomgeneric/d_loop.c:689` `static void SinglePlayerClear(ticcmd_set_t *set)`
- `TryRunTics` (function) `progs/doomgeneric/d_loop.c:706` `void TryRunTics (void)`
- `D_RegisterLoopCallbacks` (function) `progs/doomgeneric/d_loop.c:822` `void D_RegisterLoopCallbacks(loop_interface_t *i)`

## progs/doomgeneric/d_loop.h
Depends on: `progs/doomgeneric/net_defs.h`
Imported by: `progs/doomgeneric/d_loop.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/r_main.c`
- `D_RegisterLoopCallbacks` (function) `progs/doomgeneric/d_loop.h:52` `void D_RegisterLoopCallbacks(loop_interface_t *i);` -- Register callback functions for the main loop code to use.
- `NetUpdate` (function) `progs/doomgeneric/d_loop.h:55` `void NetUpdate (void);` -- Create any new ticcmds and broadcast to other players.
- `D_QuitNetGame` (function) `progs/doomgeneric/d_loop.h:59` `void D_QuitNetGame (void);` -- Broadcasts special packets to other players to notify of game exit
- `TryRunTics` (function) `progs/doomgeneric/d_loop.h:62` `void TryRunTics (void);` -- ? how many ticks to run?
- `D_StartGameLoop` (function) `progs/doomgeneric/d_loop.h:65` `void D_StartGameLoop(void);` -- Called at start of game loop to initialize timers
- `D_StartNetGame` (function) `progs/doomgeneric/d_loop.h:74` `void D_StartNetGame(net_gamesettings_t *settings, netgame_startup_callback_t callback);`

## progs/doomgeneric/d_main.c
Depends on: `kernel/string.c`, `progs/doomgeneric/am_map.h`, `progs/doomgeneric/config.h`, `progs/doomgeneric/d_iwad.h`, `progs/doomgeneric/d_main.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/f_finale.h`, `progs/doomgeneric/f_wipe.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_endoom.h`, `progs/doomgeneric/i_joystick.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_config.h`, `progs/doomgeneric/m_controls.h`, `progs/doomgeneric/m_menu.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/net_client.h`, `progs/doomgeneric/net_dedicated.h`, `progs/doomgeneric/net_query.h`, `progs/doomgeneric/p_saveg.h`, `progs/doomgeneric/p_setup.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/st_stuff.h`, `progs/doomgeneric/statdump.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_main.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/wi_stuff.h`, `progs/doomgeneric/z_zone.h`
- `D_ConnectNetGame` (function) `progs/doomgeneric/d_main.c:131` `void D_ConnectNetGame(void);`
- `D_CheckNetGame` (function) `progs/doomgeneric/d_main.c:132` `void D_CheckNetGame(void);`
- `D_ProcessEvents` (function) `progs/doomgeneric/d_main.c:139` `void D_ProcessEvents (void)` -- D_ProcessEvents Send all the events of the given timestamp down the responder chain
- `R_ExecuteSetViewSize` (function) `progs/doomgeneric/d_main.c:167` `void R_ExecuteSetViewSize (void);`
- `D_Display` (function) `progs/doomgeneric/d_main.c:169` `void D_Display (void)`
- `D_BindVariables` (function) `progs/doomgeneric/d_main.c:335` `void D_BindVariables(void)`
- `D_GrabMouseCallback` (function) `progs/doomgeneric/d_main.c:388` `boolean D_GrabMouseCallback(void)`
- `D_DoomLoop` (function) `progs/doomgeneric/d_main.c:408` `void D_DoomLoop (void)` -- D_DoomLoop
- `D_PageTicker` (function) `progs/doomgeneric/d_main.c:490` `void D_PageTicker (void)` -- D_PageTicker Handles timing for warped projection
- `D_PageDrawer` (function) `progs/doomgeneric/d_main.c:501` `void D_PageDrawer (void)` -- D_PageDrawer
- `D_AdvanceDemo` (function) `progs/doomgeneric/d_main.c:511` `void D_AdvanceDemo (void)` -- D_AdvanceDemo Called after each demo or intro demosequence finishes
- `D_DoAdvanceDemo` (function) `progs/doomgeneric/d_main.c:521` `void D_DoAdvanceDemo (void)` -- This cycles through the demo sequences.
- `D_StartTitle` (function) `progs/doomgeneric/d_main.c:609` `void D_StartTitle (void)` -- D_StartTitle
- `GetGameName` (function) `progs/doomgeneric/d_main.c:658` `static char *GetGameName(char *gamename)`
- `SetMissionForPackName` (function) `progs/doomgeneric/d_main.c:701` `static void SetMissionForPackName(char *pack_name)`
- `D_IdentifyVersion` (function) `progs/doomgeneric/d_main.c:737` `void D_IdentifyVersion(void)`
- `D_SetGameDescription` (function) `progs/doomgeneric/d_main.c:820` `void D_SetGameDescription(void)`
- `D_AddFile` (function) `progs/doomgeneric/d_main.c:883` `static boolean D_AddFile(char *filename)`
- `PrintDehackedBanners` (function) `progs/doomgeneric/d_main.c:918` `void PrintDehackedBanners(void)`
- `InitGameVersion` (function) `progs/doomgeneric/d_main.c:963` `static void InitGameVersion(void)`
- `PrintGameVersion` (function) `progs/doomgeneric/d_main.c:1065` `void PrintGameVersion(void)`
- `D_Endoom` (function) `progs/doomgeneric/d_main.c:1082` `static void D_Endoom(void)`
- `LoadIwadDeh` (function) `progs/doomgeneric/d_main.c:1105` `static void LoadIwadDeh(void)` -- if ORIGCODE Load dehacked patches needed for certain IWADs.
- `D_DoomMain` (function) `progs/doomgeneric/d_main.c:1178` `void D_DoomMain (void)` -- D_DoomMain

## progs/doomgeneric/d_main.h
Depends on: `progs/doomgeneric/doomdef.h`
Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_menu.c`
- `D_ProcessEvents` (function) `progs/doomgeneric/d_main.h:30` `void D_ProcessEvents (void);`
- `D_PageTicker` (function) `progs/doomgeneric/d_main.h:36` `void D_PageTicker (void);` -- BASE LEVEL
- `D_PageDrawer` (function) `progs/doomgeneric/d_main.h:37` `void D_PageDrawer (void);`
- `D_AdvanceDemo` (function) `progs/doomgeneric/d_main.h:38` `void D_AdvanceDemo (void);`
- `D_DoAdvanceDemo` (function) `progs/doomgeneric/d_main.h:39` `void D_DoAdvanceDemo (void);`
- `D_StartTitle` (function) `progs/doomgeneric/d_main.h:40` `void D_StartTitle (void);`

## progs/doomgeneric/d_mode.c
Depends on: `progs/doomgeneric/d_mode.h`, `progs/doomgeneric/doomtype.h`
- `D_ValidGameMode` (function) `progs/doomgeneric/d_mode.c:50` `boolean D_ValidGameMode(GameMission_t mission, GameMode_t mode)`
- `D_ValidEpisodeMap` (function) `progs/doomgeneric/d_mode.c:65` `boolean D_ValidEpisodeMap(GameMission_t mission, GameMode_t mode,
                          int e...`
- `D_GetNumEpisodes` (function) `progs/doomgeneric/d_mode.c:103` `int D_GetNumEpisodes(GameMission_t mission, GameMode_t mode)`
- `D_ValidGameVersion` (function) `progs/doomgeneric/d_mode.c:135` `boolean D_ValidGameVersion(GameMission_t mission, GameVersion_t version)`
- `D_IsEpisodeMap` (function) `progs/doomgeneric/d_mode.c:161` `boolean D_IsEpisodeMap(GameMission_t mission)`
- `D_GameMissionString` (function) `progs/doomgeneric/d_mode.c:182` `char *D_GameMissionString(GameMission_t mission)`

## progs/doomgeneric/d_mode.h
Depends on: `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/d_iwad.h`, `progs/doomgeneric/d_mode.c`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/statdump.c`, `progs/doomgeneric/w_wad.h`
- `D_GetNumEpisodes` (function) `progs/doomgeneric/d_mode.h:93` `int D_GetNumEpisodes(GameMission_t mission, GameMode_t mode);`
- `D_GameMissionString` (function) `progs/doomgeneric/d_mode.h:95` `char *D_GameMissionString(GameMission_t mission);`

## progs/doomgeneric/d_net.c
Depends on: `progs/doomgeneric/d_loop.h`, `progs/doomgeneric/d_main.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomdef.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/i_timer.h`, `progs/doomgeneric/i_video.h`, `progs/doomgeneric/m_argv.h`, `progs/doomgeneric/m_menu.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/w_checksum.h`, `progs/doomgeneric/w_wad.h`
- `PlayerQuitGame` (function) `progs/doomgeneric/d_net.c:45` `static void PlayerQuitGame(player_t *player)`
- `RunTic` (function) `progs/doomgeneric/d_net.c:71` `static void RunTic(ticcmd_t *cmds, boolean *ingame)`
- `LoadGameSettings` (function) `progs/doomgeneric/d_net.c:108` `static void LoadGameSettings(net_gamesettings_t *settings)`
- `SaveGameSettings` (function) `progs/doomgeneric/d_net.c:139` `static void SaveGameSettings(net_gamesettings_t *settings)`
- `InitConnectData` (function) `progs/doomgeneric/d_net.c:159` `static void InitConnectData(net_connect_data_t *connect_data)`
- `D_ConnectNetGame` (function) `progs/doomgeneric/d_net.c:215` `void D_ConnectNetGame(void)`
- `D_CheckNetGame` (function) `progs/doomgeneric/d_net.c:240` `void D_CheckNetGame (void)` -- D_CheckNetGame Works out player numbers among the net participants

## progs/doomgeneric/deh_main.h
Depends on: `progs/doomgeneric/deh_str.h`, `progs/doomgeneric/doomfeatures.h`, `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/sha1.h`
Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/d_net.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_inter.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_switch.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/wi_stuff.c`
- `DEH_ParseCommandLine` (function) `progs/doomgeneric/deh_main.h:33` `void DEH_ParseCommandLine(void);`
- `DEH_LoadFile` (function) `progs/doomgeneric/deh_main.h:34` `int DEH_LoadFile(char *filename);`
- `DEH_LoadLump` (function) `progs/doomgeneric/deh_main.h:35` `int DEH_LoadLump(int lumpnum, boolean allow_long, boolean allow_error);`
- `DEH_LoadLumpByName` (function) `progs/doomgeneric/deh_main.h:36` `int DEH_LoadLumpByName(char *name, boolean allow_long, boolean allow_error);`
- `DEH_Checksum` (function) `progs/doomgeneric/deh_main.h:40` `void DEH_Checksum(sha1_digest_t digest);`

## progs/doomgeneric/deh_str.h
Depends on: `progs/doomgeneric/doomfeatures.h`
Imported by: `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/v_video.c`
- `DEH_String` (function) `progs/doomgeneric/deh_str.h:29` `char *DEH_String(char *s);`
- `DEH_printf` (function) `progs/doomgeneric/deh_str.h:30` `void DEH_printf(char *fmt, ...);`
- `DEH_fprintf` (function) `progs/doomgeneric/deh_str.h:31` `void DEH_fprintf(FILE *fstream, char *fmt, ...);`
- `DEH_snprintf` (function) `progs/doomgeneric/deh_str.h:32` `void DEH_snprintf(char *buffer, size_t len, char *fmt, ...);`
- `DEH_AddStringReplacement` (function) `progs/doomgeneric/deh_str.h:33` `void DEH_AddStringReplacement(char *from_text, char *to_text);`

## progs/doomgeneric/doom.h
- `D_DoomMain` (function) `progs/doomgeneric/doom.h:28` `void D_DoomMain (void);`

## progs/doomgeneric/doomgeneric.c
Depends on: `progs/doomgeneric/doomgeneric.h`
- `dg_Create` (function) `progs/doomgeneric/doomgeneric.c:6` `void dg_Create()`

## progs/doomgeneric/doomgeneric.h
Imported by: `progs/doomgeneric/doomgeneric.c`, `progs/doomgeneric/doomgeneric_minios.c`, `progs/doomgeneric/doomgeneric_sdl.c`, `progs/doomgeneric/doomgeneric_soso.c`, `progs/doomgeneric/doomgeneric_sosox.c`, `progs/doomgeneric/doomgeneric_win.c`, `progs/doomgeneric/doomgeneric_xlib.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_timer.c`, `progs/doomgeneric/i_video.c`
- `DG_Init` (function) `progs/doomgeneric/doomgeneric.h:14` `void DG_Init();`
- `DG_DrawFrame` (function) `progs/doomgeneric/doomgeneric.h:15` `void DG_DrawFrame();`
- `DG_SleepMs` (function) `progs/doomgeneric/doomgeneric.h:16` `void DG_SleepMs(uint32_t ms);`
- `DG_GetTicksMs` (function) `progs/doomgeneric/doomgeneric.h:17` `uint32_t DG_GetTicksMs();`
- `DG_GetKey` (function) `progs/doomgeneric/doomgeneric.h:18` `int DG_GetKey(int* pressed, unsigned char* key);`
- `DG_SetWindowTitle` (function) `progs/doomgeneric/doomgeneric.h:19` `void DG_SetWindowTitle(const char * title);`

## progs/doomgeneric/doomgeneric_minios.c
Depends on: `kernel/string.c`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/s_sound.h`, `progs/minios_abi.h`
- `MINIOS_DOOM_BACKBUF_ADDR` (function) `progs/doomgeneric/doomgeneric_minios.c:4` `* MINIOS_DOOM_BACKBUF_ADDR (minios_abi.h);`
- `mini_parse_autoframes` (function) `progs/doomgeneric/doomgeneric_minios.c:24` `static void mini_parse_autoframes(int argc, char **argv)`
- `mini_parse_windowed` (function) `progs/doomgeneric/doomgeneric_minios.c:43` `static void mini_parse_windowed(int argc, char **argv)`
- `sys_time_ms` (function) `progs/doomgeneric/doomgeneric_minios.c:56` `static long sys_time_ms(void)`
- `sys_kbd` (function) `progs/doomgeneric/doomgeneric_minios.c:61` `static long sys_kbd(void)`
- `sys_palette` (function) `progs/doomgeneric/doomgeneric_minios.c:66` `static long sys_palette(const unsigned char *pal)`
- `sys_kbd_raw` (function) `progs/doomgeneric/doomgeneric_minios.c:71` `static long sys_kbd_raw(int on)`
- `sys_vga_mode` (function) `progs/doomgeneric/doomgeneric_minios.c:76` `static long sys_vga_mode(int on)`
- `sys_gfx_zoom` (function) `progs/doomgeneric/doomgeneric_minios.c:81` `static long sys_gfx_zoom(long mode)`
- `sys_doom_frame` (function) `progs/doomgeneric/doomgeneric_minios.c:86` `static long sys_doom_frame(void)`
- `load_vga_palette` (function) `progs/doomgeneric/doomgeneric_minios.c:110` `static void load_vga_palette(void)`
- `scancode_to_doom` (function) `progs/doomgeneric/doomgeneric_minios.c:123` `static unsigned char scancode_to_doom(unsigned char raw)`
- `kbd_enqueue` (function) `progs/doomgeneric/doomgeneric_minios.c:182` `static void kbd_enqueue(unsigned char doom_key, int pressed)`
- `kbd_poll` (function) `progs/doomgeneric/doomgeneric_minios.c:189` `static void kbd_poll(void)`
- `DG_Init` (function) `progs/doomgeneric/doomgeneric_minios.c:232` `void DG_Init(void)`
- `DG_DrawFrame` (function) `progs/doomgeneric/doomgeneric_minios.c:243` `void DG_DrawFrame(void)`
- `DG_SleepMs` (function) `progs/doomgeneric/doomgeneric_minios.c:274` `void DG_SleepMs(uint32_t ms)`
- `DG_GetTicksMs` (function) `progs/doomgeneric/doomgeneric_minios.c:280` `uint32_t DG_GetTicksMs(void)`
- `DG_GetKey` (function) `progs/doomgeneric/doomgeneric_minios.c:284` `int DG_GetKey(int *pressed, unsigned char *key)`
- `DG_SetWindowTitle` (function) `progs/doomgeneric/doomgeneric_minios.c:295` `void DG_SetWindowTitle(const char *title)`

## progs/doomgeneric/doomgeneric_sdl.c
Depends on: `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/m_argv.h`, `progs/pokemon/minios_stubs/SDL.h`
- `convertToDoomKey` (function) `progs/doomgeneric/doomgeneric_sdl.c:23` `static unsigned char convertToDoomKey(unsigned int key)`
- `addKeyToQueue` (function) `progs/doomgeneric/doomgeneric_sdl.c:63` `static void addKeyToQueue(int pressed, unsigned int keyCode)`
- `handleKeyInput` (function) `progs/doomgeneric/doomgeneric_sdl.c:72` `static void handleKeyInput()`
- `DG_Init` (function) `progs/doomgeneric/doomgeneric_sdl.c:93` `void DG_Init()`
- `DG_DrawFrame` (function) `progs/doomgeneric/doomgeneric_sdl.c:112` `void DG_DrawFrame()`
- `DG_SleepMs` (function) `progs/doomgeneric/doomgeneric_sdl.c:123` `void DG_SleepMs(uint32_t ms)`
- `DG_GetTicksMs` (function) `progs/doomgeneric/doomgeneric_sdl.c:128` `uint32_t DG_GetTicksMs()`
- `DG_GetKey` (function) `progs/doomgeneric/doomgeneric_sdl.c:133` `int DG_GetKey(int* pressed, unsigned char* doomKey)`
- `DG_SetWindowTitle` (function) `progs/doomgeneric/doomgeneric_sdl.c:152` `void DG_SetWindowTitle(const char * title)`

## progs/doomgeneric/doomgeneric_soso.c
Depends on: `kernel/string.c`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/m_argv.h`
- `convertToDoomKey` (function) `progs/doomgeneric/doomgeneric_soso.c:43` `static unsigned char convertToDoomKey(unsigned char scancode)`
- `addKeyToQueue` (function) `progs/doomgeneric/doomgeneric_soso.c:92` `static void addKeyToQueue(int pressed, unsigned char keyCode)`
- `disableRawMode` (function) `progs/doomgeneric/doomgeneric_soso.c:108` `void disableRawMode()`
- `enableRawMode` (function) `progs/doomgeneric/doomgeneric_soso.c:114` `void enableRawMode()`
- `DG_Init` (function) `progs/doomgeneric/doomgeneric_soso.c:124` `void DG_Init()`
- `handleKeyInput` (function) `progs/doomgeneric/doomgeneric_soso.c:186` `static void handleKeyInput()`
- `DG_DrawFrame` (function) `progs/doomgeneric/doomgeneric_soso.c:214` `void DG_DrawFrame()`
- `DG_SleepMs` (function) `progs/doomgeneric/doomgeneric_soso.c:227` `void DG_SleepMs(uint32_t ms)`
- `DG_GetTicksMs` (function) `progs/doomgeneric/doomgeneric_soso.c:232` `uint32_t DG_GetTicksMs()`
- `DG_GetKey` (function) `progs/doomgeneric/doomgeneric_soso.c:237` `int DG_GetKey(int* pressed, unsigned char* doomKey)`
- `DG_SetWindowTitle` (function) `progs/doomgeneric/doomgeneric_soso.c:258` `void DG_SetWindowTitle(const char * title)`

## progs/doomgeneric/doomgeneric_sosox.c
Depends on: `kernel/string.c`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`, `progs/doomgeneric/m_argv.h`
- `convert_to_doom_key` (function) `progs/doomgeneric/doomgeneric_sosox.c:39` `static unsigned char convert_to_doom_key(unsigned char scancode)`
- `add_key_to_queue` (function) `progs/doomgeneric/doomgeneric_sosox.c:88` `static void add_key_to_queue(int pressed, unsigned char key_code)`
- `disable_raw_mode` (function) `progs/doomgeneric/doomgeneric_sosox.c:102` `void disable_raw_mode()`
- `enable_raw_mode` (function) `progs/doomgeneric/doomgeneric_sosox.c:107` `void enable_raw_mode()`
- `DG_Init` (function) `progs/doomgeneric/doomgeneric_sosox.c:117` `void DG_Init()`
- `handle_key_input` (function) `progs/doomgeneric/doomgeneric_sosox.c:159` `static void handle_key_input()`
- `DG_DrawFrame` (function) `progs/doomgeneric/doomgeneric_sosox.c:187` `void DG_DrawFrame()`
- `DG_SleepMs` (function) `progs/doomgeneric/doomgeneric_sosox.c:225` `void DG_SleepMs(uint32_t ms)`
- `DG_GetTicksMs` (function) `progs/doomgeneric/doomgeneric_sosox.c:230` `uint32_t DG_GetTicksMs()`
- `DG_GetKey` (function) `progs/doomgeneric/doomgeneric_sosox.c:235` `int DG_GetKey(int* pressed, unsigned char* doomKey)`
- `DG_SetWindowTitle` (function) `progs/doomgeneric/doomgeneric_sosox.c:256` `void DG_SetWindowTitle(const char * title)`

## progs/doomgeneric/doomgeneric_win.c
Depends on: `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`
- `convertToDoomKey` (function) `progs/doomgeneric/doomgeneric_win.c:20` `static unsigned char convertToDoomKey(unsigned char key)`
- `addKeyToQueue` (function) `progs/doomgeneric/doomgeneric_win.c:59` `static void addKeyToQueue(int pressed, unsigned char keyCode)`
- `wndProc` (function) `progs/doomgeneric/doomgeneric_win.c:70` `static LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)`
- `DG_Init` (function) `progs/doomgeneric/doomgeneric_win.c:95` `void DG_Init()`
- `DG_DrawFrame` (function) `progs/doomgeneric/doomgeneric_win.c:146` `void DG_DrawFrame()`
- `DG_SleepMs` (function) `progs/doomgeneric/doomgeneric_win.c:162` `void DG_SleepMs(uint32_t ms)`
- `DG_GetTicksMs` (function) `progs/doomgeneric/doomgeneric_win.c:167` `uint32_t DG_GetTicksMs()`
- `DG_GetKey` (function) `progs/doomgeneric/doomgeneric_win.c:172` `int DG_GetKey(int* pressed, unsigned char* doomKey)`
- `DG_SetWindowTitle` (function) `progs/doomgeneric/doomgeneric_win.c:193` `void DG_SetWindowTitle(const char * title)`

## progs/doomgeneric/doomgeneric_xlib.c
Depends on: `kernel/string.c`, `kernel/time.c`, `progs/doomgeneric/doomgeneric.h`, `progs/doomgeneric/doomkeys.h`
- `convertToDoomKey` (function) `progs/doomgeneric/doomgeneric_xlib.c:27` `static unsigned char convertToDoomKey(unsigned int key)`
- `addKeyToQueue` (function) `progs/doomgeneric/doomgeneric_xlib.c:68` `static void addKeyToQueue(int pressed, unsigned int keyCode)`
- `DG_Init` (function) `progs/doomgeneric/doomgeneric_xlib.c:79` `void DG_Init()`
- `DG_DrawFrame` (function) `progs/doomgeneric/doomgeneric_xlib.c:127` `void DG_DrawFrame()`
- `DG_SleepMs` (function) `progs/doomgeneric/doomgeneric_xlib.c:172` `void DG_SleepMs(uint32_t ms)`
- `DG_GetTicksMs` (function) `progs/doomgeneric/doomgeneric_xlib.c:177` `uint32_t DG_GetTicksMs()`
- `DG_GetKey` (function) `progs/doomgeneric/doomgeneric_xlib.c:187` `int DG_GetKey(int* pressed, unsigned char* doomKey)`
- `DG_SetWindowTitle` (function) `progs/doomgeneric/doomgeneric_xlib.c:208` `void DG_SetWindowTitle(const char * title)`

## progs/doomgeneric/dummy.c
Depends on: `progs/doomgeneric/doomtype.h`
- `I_InitTimidityConfig` (function) `progs/doomgeneric/dummy.c:43` `void I_InitTimidityConfig(void)`

## progs/doomgeneric/f_finale.c
Depends on: `progs/doomgeneric/d_main.h`, `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/dstrings.h`, `progs/doomgeneric/hu_stuff.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/r_state.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/z_zone.h`
- `F_StartFinale` (function) `progs/doomgeneric/f_finale.c:108` `void F_StartFinale (void)` -- F_StartFinale
- `F_Responder` (function) `progs/doomgeneric/f_finale.c:160` `boolean F_Responder (event_t *event)`
- `F_Ticker` (function) `progs/doomgeneric/f_finale.c:172` `void F_Ticker (void)` -- F_Ticker
- `F_TextWrite` (function) `progs/doomgeneric/f_finale.c:227` `void F_TextWrite (void)`
- `F_StartCast` (function) `progs/doomgeneric/f_finale.c:340` `void F_StartCast (void)` -- F_StartCast
- `F_CastTicker` (function) `progs/doomgeneric/f_finale.c:358` `void F_CastTicker (void)` -- F_CastTicker
- `F_CastResponder` (function) `progs/doomgeneric/f_finale.c:465` `boolean F_CastResponder (event_t* ev)`
- `F_CastPrint` (function) `progs/doomgeneric/f_finale.c:486` `void F_CastPrint (char* text)`
- `F_CastDrawer` (function) `progs/doomgeneric/f_finale.c:541` `void F_CastDrawer (void)`
- `F_DrawPatchCol` (function) `progs/doomgeneric/f_finale.c:572` `void
F_DrawPatchCol
( int		x,
  patch_t*	patch,
  int		col )`
- `F_BunnyScroll` (function) `progs/doomgeneric/f_finale.c:606` `void F_BunnyScroll (void)` -- F_BunnyScroll
- `F_ArtScreenDrawer` (function) `progs/doomgeneric/f_finale.c:661` `static void F_ArtScreenDrawer(void)`
- `F_Drawer` (function) `progs/doomgeneric/f_finale.c:702` `void F_Drawer (void)` -- F_Drawer

## progs/doomgeneric/f_finale.h
Depends on: `progs/doomgeneric/d_event.h`, `progs/doomgeneric/doomtype.h`
Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`
- `F_Ticker` (function) `progs/doomgeneric/f_finale.h:34` `void F_Ticker (void);` -- Called by main loop.
- `F_Drawer` (function) `progs/doomgeneric/f_finale.h:37` `void F_Drawer (void);` -- Called by main loop.
- `F_StartFinale` (function) `progs/doomgeneric/f_finale.h:40` `void F_StartFinale (void);`


Next: [API_p10.md](API_p10.md)
