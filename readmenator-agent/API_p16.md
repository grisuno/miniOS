# API (page 16 of 21)
Previous: [API_p15.md](API_p15.md)

## progs/doomgeneric/wi_stuff.c
Depends on: `progs/doomgeneric/deh_main.h`, `progs/doomgeneric/doomstat.h`, `progs/doomgeneric/g_game.h`, `progs/doomgeneric/i_swap.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/m_misc.h`, `progs/doomgeneric/m_random.h`, `progs/doomgeneric/r_local.h`, `progs/doomgeneric/s_sound.h`, `progs/doomgeneric/sounds.h`, `progs/doomgeneric/v_video.h`, `progs/doomgeneric/w_wad.h`, `progs/doomgeneric/wi_stuff.h`, `progs/doomgeneric/z_zone.h`
- `WI_slamBackground` (function) `progs/doomgeneric/wi_stuff.c:402` `void WI_slamBackground(void)` -- slam background
- `WI_Responder` (function) `progs/doomgeneric/wi_stuff.c:409` `boolean WI_Responder(event_t* ev)` -- The ticker is used to detect keys because of timing issues in netgames.
- `WI_drawLF` (function) `progs/doomgeneric/wi_stuff.c:416` `void WI_drawLF(void)` -- Draws "<Levelname> Finished!"
- `WI_drawEL` (function) `progs/doomgeneric/wi_stuff.c:452` `void WI_drawEL(void)` -- Draws "Entering <LevelName>"
- `WI_drawOnLnode` (function) `progs/doomgeneric/wi_stuff.c:471` `void
WI_drawOnLnode
( int		n,
  patch_t*	c[] )`
- `WI_initAnimatedBack` (function) `progs/doomgeneric/wi_stuff.c:519` `void WI_initAnimatedBack(void)`
- `WI_updateAnimatedBack` (function) `progs/doomgeneric/wi_stuff.c:548` `void WI_updateAnimatedBack(void)`
- `WI_drawAnimatedBack` (function) `progs/doomgeneric/wi_stuff.c:599` `void WI_drawAnimatedBack(void)`
- `WI_drawNum` (function) `progs/doomgeneric/wi_stuff.c:628` `int
WI_drawNum
( int		x,
  int		y,
  int		n,
  int		digits )`
- `WI_drawPercent` (function) `progs/doomgeneric/wi_stuff.c:685` `void
WI_drawPercent
( int		x,
  int		y,
  int		p )`
- `WI_drawTime` (function) `progs/doomgeneric/wi_stuff.c:704` `void
WI_drawTime
( int		x,
  int		y,
  int		t )`
- `WI_End` (function) `progs/doomgeneric/wi_stuff.c:740` `void WI_End(void)`
- `WI_initNoState` (function) `progs/doomgeneric/wi_stuff.c:746` `void WI_initNoState(void)`
- `WI_updateNoState` (function) `progs/doomgeneric/wi_stuff.c:753` `void WI_updateNoState(void)`
- `WI_initShowNextLoc` (function) `progs/doomgeneric/wi_stuff.c:772` `void WI_initShowNextLoc(void)`
- `WI_updateShowNextLoc` (function) `progs/doomgeneric/wi_stuff.c:781` `void WI_updateShowNextLoc(void)`
- `WI_drawShowNextLoc` (function) `progs/doomgeneric/wi_stuff.c:791` `void WI_drawShowNextLoc(void)`
- `WI_drawNoState` (function) `progs/doomgeneric/wi_stuff.c:832` `void WI_drawNoState(void)`
- `WI_fragSum` (function) `progs/doomgeneric/wi_stuff.c:838` `int WI_fragSum(int playernum)`
- `WI_initDeathmatchStats` (function) `progs/doomgeneric/wi_stuff.c:869` `void WI_initDeathmatchStats(void)`
- `WI_updateDeathmatchStats` (function) `progs/doomgeneric/wi_stuff.c:898` `void WI_updateDeathmatchStats(void)`
- `WI_drawDeathmatchStats` (function) `progs/doomgeneric/wi_stuff.c:1001` `void WI_drawDeathmatchStats(void)`
- `WI_initNetgameStats` (function) `progs/doomgeneric/wi_stuff.c:1089` `void WI_initNetgameStats(void)`
- `WI_updateNetgameStats` (function) `progs/doomgeneric/wi_stuff.c:1117` `void WI_updateNetgameStats(void)`
- `WI_drawNetgameStats` (function) `progs/doomgeneric/wi_stuff.c:1272` `void WI_drawNetgameStats(void)`
- `WI_initStats` (function) `progs/doomgeneric/wi_stuff.c:1329` `void WI_initStats(void)`
- `WI_updateStats` (function) `progs/doomgeneric/wi_stuff.c:1341` `void WI_updateStats(void)`
- `WI_drawStats` (function) `progs/doomgeneric/wi_stuff.c:1447` `void WI_drawStats(void)`
- `WI_checkForAccelerate` (function) `progs/doomgeneric/wi_stuff.c:1481` `void WI_checkForAccelerate(void)`
- `WI_Ticker` (function) `progs/doomgeneric/wi_stuff.c:1514` `void WI_Ticker(void)` -- Updates stuff each tick
- `WI_loadUnloadData` (function) `progs/doomgeneric/wi_stuff.c:1554` `static void WI_loadUnloadData(load_callback_t callback)`
- `WI_loadCallback` (function) `progs/doomgeneric/wi_stuff.c:1704` `static void WI_loadCallback(char *name, patch_t **variable)`
- `WI_loadData` (function) `progs/doomgeneric/wi_stuff.c:1709` `void WI_loadData(void)`
- `WI_unloadCallback` (function) `progs/doomgeneric/wi_stuff.c:1735` `static void WI_unloadCallback(char *name, patch_t **variable)`
- `WI_unloadData` (function) `progs/doomgeneric/wi_stuff.c:1741` `void WI_unloadData(void)`
- `WI_Drawer` (function) `progs/doomgeneric/wi_stuff.c:1752` `void WI_Drawer (void)`
- `WI_initVariables` (function) `progs/doomgeneric/wi_stuff.c:1776` `void WI_initVariables(wbstartstruct_t* wbstartstruct)`
- `WI_Start` (function) `progs/doomgeneric/wi_stuff.c:1818` `void WI_Start(wbstartstruct_t* wbstartstruct)`

## progs/doomgeneric/wi_stuff.h
Depends on: `progs/doomgeneric/doomdef.h`
Imported by: `progs/doomgeneric/d_main.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/wi_stuff.c`
- `WI_Ticker` (function) `progs/doomgeneric/wi_stuff.h:36` `void WI_Ticker (void);` -- Called by main loop, animate the intermission.
- `WI_Drawer` (function) `progs/doomgeneric/wi_stuff.h:40` `void WI_Drawer (void);` -- Called by main loop, draws the intermission directly into the screen buffer.
- `WI_Start` (function) `progs/doomgeneric/wi_stuff.h:43` `void WI_Start(wbstartstruct_t* wbstartstruct);` -- Setup for an intermission screen.
- `WI_End` (function) `progs/doomgeneric/wi_stuff.h:46` `void WI_End(void);` -- Shut down the intermission screen

## progs/doomgeneric/z_zone.c
Depends on: `progs/doomgeneric/doomtype.h`, `progs/doomgeneric/i_system.h`, `progs/doomgeneric/z_zone.h`
- `Z_ClearZone` (function) `progs/doomgeneric/z_zone.c:71` `void Z_ClearZone (memzone_t* zone)` -- Z_ClearZone
- `Z_Init` (function) `progs/doomgeneric/z_zone.c:97` `void Z_Init (void)` -- Z_Init
- `Z_Free` (function) `progs/doomgeneric/z_zone.c:126` `void Z_Free (void* ptr)` -- Z_Free
- `Z_Malloc` (function) `progs/doomgeneric/z_zone.c:185` `void*
Z_Malloc
( int		size,
  int		tag,
  void*		user )`
- `Z_FreeTags` (function) `progs/doomgeneric/z_zone.c:298` `void
Z_FreeTags
( int		lowtag,
  int		hightag )`
- `Z_DumpHeap` (function) `progs/doomgeneric/z_zone.c:328` `void
Z_DumpHeap
( int		lowtag,
  int		hightag )`
- `Z_FileDumpHeap` (function) `progs/doomgeneric/z_zone.c:367` `void Z_FileDumpHeap (FILE* f)` -- Z_FileDumpHeap
- `Z_CheckHeap` (function) `progs/doomgeneric/z_zone.c:400` `void Z_CheckHeap (void)` -- Z_CheckHeap
- `Z_ChangeTag2` (function) `progs/doomgeneric/z_zone.c:429` `void Z_ChangeTag2(void *ptr, int tag, char *file, int line)` -- Z_ChangeTag
- `Z_ChangeUser` (function) `progs/doomgeneric/z_zone.c:446` `void Z_ChangeUser(void *ptr, void **user)`
- `Z_FreeMemory` (function) `progs/doomgeneric/z_zone.c:466` `int Z_FreeMemory (void)` -- Z_FreeMemory
- `Z_ZoneSize` (function) `progs/doomgeneric/z_zone.c:484` `unsigned int Z_ZoneSize(void)`

## progs/doomgeneric/z_zone.h
Imported by: `progs/doomgeneric/am_map.c`, `progs/doomgeneric/d_iwad.c`, `progs/doomgeneric/d_main.c`, `progs/doomgeneric/f_finale.c`, `progs/doomgeneric/f_wipe.c`, `progs/doomgeneric/g_game.c`, `progs/doomgeneric/gusconf.c`, `progs/doomgeneric/hu_stuff.c`, `progs/doomgeneric/i_input.c`, `progs/doomgeneric/i_minios_sound.c`, `progs/doomgeneric/i_scale.c`, `progs/doomgeneric/i_system.c`, `progs/doomgeneric/i_video.c`, `progs/doomgeneric/m_config.c`, `progs/doomgeneric/m_menu.c`, `progs/doomgeneric/m_misc.c`, `progs/doomgeneric/memio.c`, `progs/doomgeneric/p_ceilng.c`, `progs/doomgeneric/p_doors.c`, `progs/doomgeneric/p_floor.c`, `progs/doomgeneric/p_lights.c`, `progs/doomgeneric/p_mobj.c`, `progs/doomgeneric/p_plats.c`, `progs/doomgeneric/p_saveg.c`, `progs/doomgeneric/p_setup.c`, `progs/doomgeneric/p_spec.c`, `progs/doomgeneric/p_tick.c`, `progs/doomgeneric/r_data.c`, `progs/doomgeneric/r_draw.c`, `progs/doomgeneric/r_plane.c`, `progs/doomgeneric/r_things.c`, `progs/doomgeneric/s_sound.c`, `progs/doomgeneric/st_lib.c`, `progs/doomgeneric/st_stuff.c`, `progs/doomgeneric/v_video.c`, `progs/doomgeneric/w_file_stdc.c`, `progs/doomgeneric/w_main.c`, `progs/doomgeneric/w_wad.c`, `progs/doomgeneric/wi_stuff.c`, `progs/doomgeneric/z_zone.c`
- `Z_Init` (function) `progs/doomgeneric/z_zone.h:53` `void Z_Init (void);`
- `Z_Malloc` (function) `progs/doomgeneric/z_zone.h:54` `void* Z_Malloc (int size, int tag, void *ptr);`
- `Z_Free` (function) `progs/doomgeneric/z_zone.h:55` `void Z_Free (void *ptr);`
- `Z_FreeTags` (function) `progs/doomgeneric/z_zone.h:56` `void Z_FreeTags (int lowtag, int hightag);`
- `Z_DumpHeap` (function) `progs/doomgeneric/z_zone.h:57` `void Z_DumpHeap (int lowtag, int hightag);`
- `Z_FileDumpHeap` (function) `progs/doomgeneric/z_zone.h:58` `void Z_FileDumpHeap (FILE *f);`
- `Z_CheckHeap` (function) `progs/doomgeneric/z_zone.h:59` `void Z_CheckHeap (void);`
- `Z_ChangeTag2` (function) `progs/doomgeneric/z_zone.h:60` `void Z_ChangeTag2 (void *ptr, int tag, char *file, int line);`
- `Z_ChangeUser` (function) `progs/doomgeneric/z_zone.h:61` `void Z_ChangeUser(void *ptr, void **user);`
- `Z_FreeMemory` (function) `progs/doomgeneric/z_zone.h:62` `int Z_FreeMemory (void);`
- `Z_ZoneSize` (function) `progs/doomgeneric/z_zone.h:63` `unsigned int Z_ZoneSize(void);`

## progs/file/file.c
Depends on: `headers/leakcheck.h`, `kernel/string.c`, `progs/file/file_assoc.h`, `progs/minios_abi.h`, `progs/minios_png.h`, `progs/nuklear/nuklear_minios.h`, `progs/nuklear/nuklear_theme.h`
- `file_sys_dir_list` (function) `progs/file/file.c:101` `static long file_sys_dir_list(const char *path, char *buf, long cap)` -- static unsigned char file_icon_mask[FILE_ICON_N][FILE_ICON_MAX * FILE_ICON_MAX]; static struct nk_minios_img...
- `file_sys_spawn` (function) `progs/file/file.c:111` `static long file_sys_spawn(const char *path, int argc, const char **argv)` -- static int file_preview_h; static int file_preview_on; /** Raw DIR_LIST syscall (241): names land NUL-separated in...
- `file_ext_of` (function) `progs/file/file.c:122` `static void file_ext_of(const char *fname, char *dst, unsigned cap)` -- } /** Raw SPAWN syscall (215) preserving this app across the child. static long file_sys_spawn(const char *path, int...
- `file_icon_kind` (function) `progs/file/file.c:146` `static int file_icon_kind(const char *fname, int isdir)` -- Icon kind for an entry: folder for dirs, image for .png, object for .o/.elf/.cvm, files for the text kinds...
- `file_icon_sz` (function) `progs/file/file.c:158` `static int file_icon_sz(void)` -- and for anything else.
- `file_icon_decode` (function) `progs/file/file.c:165` `static int file_icon_decode(const char *path, unsigned char *px,
                            unsi...` -- Decode one RGBA icon into indexed pixels plus an alpha mask, scaled to the live size.
- `file_icons_load` (function) `progs/file/file.c:213` `static int file_icons_load(void)` -- Load the four kind icons; all-or-nothing so the UI never mixes icon * and text rows.
- `file_toggle_icons` (function) `progs/file/file.c:238` `static int file_toggle_icons(void)` -- Flip the icon size and reload the four kind icons.
- `file_join` (function) `progs/file/file.c:245` `static int file_join(const char *dir, const char *name, char *dst, unsigned cap)` -- Flip the icon size and reload the four kind icons.
- `file_parent` (function) `progs/file/file.c:259` `static void file_parent(char *path)` -- static int file_join(const char *dir, const char *name, char *dst, unsigned cap) { unsigned a = 0; unsigned b = 0...
- `file_assoc_line` (function) `progs/file/file.c:269` `static int file_assoc_line(const char *line, char *ext, char *prog)` -- return 0; } /** Parent of an absolute path, root stays root. static void file_parent(char *path) { unsigned n = 0...
- `file_assoc_load` (function) `progs/file/file.c:302` `static void file_assoc_load(void)` -- } if (line[p + k] && line[p + k] != '\n' && line[p + k] != '\r') return -1; while (p > 0 && (prog[p - 1] == ' ' ||...
- `file_assoc_lookup` (function) `progs/file/file.c:318` `static const char *file_assoc_lookup(const char *ext)` -- char line[FILE_LOG_LINE]; char ext[FILE_EXT_MAX + 1]; char prog[FILE_PROG_MAX + 1]; fassoc_clear(&file_assocs); f =...
- `file_action_of` (function) `progs/file/file.c:323` `static int file_action_of(const char *fname, const char **prog_out)` -- if (!f) return; while (fgets(line, sizeof(line), f)) { if (file_assoc_line(line, ext, prog) != 0) continue; if...
- `file_refresh` (function) `progs/file/file.c:336` `static void file_refresh(void)` -- /** Dispatch kind for a file name through the association table. static int file_action_of(const char *fname, const...
- `file_preview_load` (function) `progs/file/file.c:351` `static int file_preview_load(const char *path)` -- long rc = file_sys_dir_list(file_cwd, file_entries, FILE_LIST_CAP); if (rc < 0) { file_entry_count = 0...
- `file_preview_blit` (function) `progs/file/file.c:385` `static void file_preview_blit(int ox, int oy)` -- Blit the preview buffer into the NK back-buffer after rasterize (and its * RGB twin when the kernel maps it).
- `file_spawn_visible` (function) `progs/file/file.c:407` `static long file_spawn_visible(const char *tool, int argc, const char **argv,
                   ...` -- int dx = ox + x; int dy = oy + y; unsigned char r, g, b; volatile uint8_t *d; if (dx < 0 || dx >= NK_W || dy < 0 ||...
- `file_open_text` (function) `progs/file/file.c:430` `static void file_open_text(const char *path)` -- printf("file: %s exit code: %ld\n", label, rc); fflush(stdout); nk_sys_vga_mode(1); nk_build_palette(pal768)...
- `file_run_shell` (function) `progs/file/file.c:441` `static void file_run_shell(const char *path)` -- } /** Open a text file in vedit, preserving this browser. static void file_open_text(const char *path) { const char...
- `file_activate` (function) `progs/file/file.c:480` `static void file_activate(const char *dir, const char *name)` -- if (strcmp(ext, "cvm") == 0) { args[0] = path; args[1] = 0; snprintf(label, sizeof(label), "run %s", path)...
- `file_ui_build` (function) `progs/file/file.c:511` `static void file_ui_build(struct nk_context *ctx)` -- snprintf(file_preview_path, sizeof(file_preview_path), "%s", path); snprintf(file_status, sizeof(file_status)...
- `file_selftest` (function) `progs/file/file.c:613` `static int file_selftest(void)` -- Headless selftest for BDD: assoc vectors plus a live listing.
- `file_gui_run` (function) `progs/file/file.c:779` `static void file_gui_run(void)`
- `main` (function) `progs/file/file.c:838` `int main(int argc, char **argv)`

## progs/file/file_assoc.h
Depends on: `kernel/string.c`
Imported by: `progs/file/file.c`, `tests/test_file_assoc.c`, `tests/test_leakcheck.c`
- `fassoc_ext_ok` (function) `progs/file/file_assoc.h:59` `static int fassoc_ext_ok(const char *ext)` -- /** Docstring: one validated association entry, ext without dot. struct fassoc_entry { char ext[FASSOC_EXT_MAX + 1]...
- `fassoc_prog_ok` (function) `progs/file/file_assoc.h:73` `static int fassoc_prog_ok(const char *prog)` -- static int fassoc_ext_ok(const char *ext) { size_t n = 0; size_t k = 0; if (ext == NULL) return 0; while (ext[n] !=...
- `fassoc_clear` (function) `progs/file/file_assoc.h:89` `static void fassoc_clear(struct fassoc_table *t)` -- size_t k = 0; if (prog == NULL) return 0; while (prog[n] != 0) n++; if (n == 0 || n > (size_t)FASSOC_PROG_MAX)...
- `fassoc_free` (function) `progs/file/file_assoc.h:95` `static void fassoc_free(struct fassoc_table *t)` -- if (prog[0] != '/') return 0; for (k = 0; k < n; k++) { if (prog[k] == '|') return 0; } return 1; } /** Docstring...
- `fassoc_reserve` (function) `progs/file/file_assoc.h:104` `static int fassoc_reserve(struct fassoc_table *t, size_t want)` -- if (t == NULL) return; t->cnt = 0; } /** Docstring: release backing store and reset to zero init state. static void...
- `fassoc_push` (function) `progs/file/file_assoc.h:125` `static int fassoc_push(struct fassoc_table *t, const char *ext, const char *prog)` -- while (ncap < want) { size_t nxt = ncap * (size_t)FASSOC_GROW_NUM / (size_t)FASSOC_GROW_DEN + 1; if (nxt <= ncap)...
- `fassoc_lookup` (function) `progs/file/file_assoc.h:140` `static const char *fassoc_lookup(const struct fassoc_table *t, const char *ext)` -- if (t == NULL) return -1; if (!fassoc_ext_ok(ext)) return -1; if (!fassoc_prog_ok(prog)) return -1; if (t->cnt >=...
- `fassoc_count` (function) `progs/file/file_assoc.h:150` `static size_t fassoc_count(const struct fassoc_table *t)` -- return 0; } /** Docstring: program for ext in file order, empty string when unmapped. static const char...

## progs/freedomui/freedomui_minios.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`, `progs/nk_palette.h`
Imported by: `tests/test_freedomui.c`
- `net_dns_resolve` (function) `progs/freedomui/freedomui_minios.c:44` `int net_dns_resolve(const char *host);`
- `tls_handshake` (function) `progs/freedomui/freedomui_minios.c:45` `int tls_handshake(int fd, char *host);`
- `tls_send` (function) `progs/freedomui/freedomui_minios.c:46` `int tls_send(int fd, char *buf, int len);`
- `tls_recv` (function) `progs/freedomui/freedomui_minios.c:47` `int tls_recv(int fd, char *buf, int len);`
- `tls_close` (function) `progs/freedomui/freedomui_minios.c:48` `void tls_close(int fd);`
- `freedomui_default` (function) `progs/freedomui/freedomui_minios.c:97` `static FreedomUiConfig freedomui_default(void)` -- long path_max; long url_max; long hops_max; long font_w; long font_h; long port_http; long port_https; long ink_bg...
- `freedomui_build_palette` (function) `progs/freedomui/freedomui_minios.c:130` `static long freedomui_build_palette(unsigned char *pal, long cap)` -- Shared hybrid palette, one table for every NK-window app (progs/nk_palette.h); this wrapper keeps the historic name...
- `freedomui_engine_text` (function) `progs/freedomui/freedomui_minios.c:145` `static long freedomui_engine_text(char *body, long n, char **title, char **text)` -- Parse a fetched body through the real engine into owned title and text.
- `freedomui_sys_present` (function) `progs/freedomui/freedomui_minios.c:193` `static long freedomui_sys_present(long buf, long origin)` -- static char f_path[FUI_PATH_MAX]; static char f_loc[FUI_URL_MAX]; static char f_hdr[FUI_HDR_MAX]; static char...
- `freedomui_sys_title` (function) `progs/freedomui/freedomui_minios.c:200` `static long freedomui_sys_title(char *t)` -- static long f_nbytes; static long f_secure; static long f_port; static long f_status; static long f_truncated; /**...
- `freedomui_sys_palette` (function) `progs/freedomui/freedomui_minios.c:207` `static long freedomui_sys_palette(unsigned char *pal)` -- static long freedomui_sys_present(long buf, long origin) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedomui_sys_mouse` (function) `progs/freedomui/freedomui_minios.c:214` `static long freedomui_sys_mouse(long *m)` -- static long freedomui_sys_title(char *t) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedomui_sys_kbd` (function) `progs/freedomui/freedomui_minios.c:221` `static long freedomui_sys_kbd(void)` -- static long freedomui_sys_palette(unsigned char *pal) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedomui_sys_vga_mode` (function) `progs/freedomui/freedomui_minios.c:228` `static long freedomui_sys_vga_mode(long on)` -- static long freedomui_sys_mouse(long *m) { long ret; __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_MOUSE)...
- `freedomui_sys_kbd_raw` (function) `progs/freedomui/freedomui_minios.c:235` `static long freedomui_sys_kbd_raw(long on)` -- static long freedomui_sys_kbd(void) { long ret; __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_KBD), "D"(0)...
- `freedomui_sys_yield` (function) `progs/freedomui/freedomui_minios.c:242` `static long freedomui_sys_yield(void)` -- static long freedomui_sys_vga_mode(long on) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `fui_append` (function) `progs/freedomui/freedomui_minios.c:249` `static long fui_append(char *dst, long pos, char *src, long cap)` -- static long freedomui_sys_kbd_raw(long on) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `fui_strlen` (function) `progs/freedomui/freedomui_minios.c:267` `static long fui_strlen(char *s, long cap)` -- } i = 0L; while (src[i] != 0) { if (pos + i + 1L >= cap) { return -1L; } dst[pos + i] = src[i]; i++; } dst[pos + i]...
- `fui_split_url` (function) `progs/freedomui/freedomui_minios.c:283` `static long fui_split_url(FreedomUiConfig *c, char *url, char *host, char *path, long *port, long...` -- if (!s || cap <= 0L) { return -1L; } i = 0L; while (i < cap && s[i] != 0) { i++; } if (i >= cap) { return -1L; }...
- `fui_parse_headers` (function) `progs/freedomui/freedomui_minios.c:352` `static long fui_parse_headers(FreedomUiConfig *c, char *hdr, long *status, long *clen, long *hasc...` -- return 0L; } path[k] = p[hl + k]; k++; } path[k] = 0; } else { path[0] = '/'; path[1] = 0; } return 1L; } /** Parse...
- `fui_fetch_raw` (function) `progs/freedomui/freedomui_minios.c:470` `static long fui_fetch_raw(FreedomUiConfig *c, char *host, char *path, long port, long secure)` -- } k++; } } } line++; while (hdr[i] == '\r' || hdr[i] == '\n') { i++; } } return 0L; } /** Fetch one response body...
- `fui_render` (function) `progs/freedomui/freedomui_minios.c:698` `static long fui_render(FreedomUiConfig *c, size_t off)` -- if (got < c->body_cap) { f_body[got] = (char)ch; got++; } else { f_truncated = 1L; } } } } tls_close((int)fd)...
- `fui_browse` (function) `progs/freedomui/freedomui_minios.c:817` `static long fui_browse(FreedomUiConfig *c)` -- long ink; if (bits & (0x80 >> px)) { ink = c->bar_fg; } else { ink = c->bar_bg; } fb[((size_t)c->text_rows *...
- `freedomui_selftest` (function) `progs/freedomui/freedomui_minios.c:896` `static long freedomui_selftest(void)` -- } off = ui_clamp_scroll((size_t)want, f_lay.count, (size_t)c->text_rows); changed = 1L; } if (changed) { if...
- `freedomui_host_probe` (function) `progs/freedomui/freedomui_minios.c:984` `static long freedomui_host_probe(FreedomUiConfig *c)` -- return 1L; } if (freedomui_sys_kbd() > 0x7FFFFFFFL) { printf("freedomui: kbd out of range\n"); return 1L; }...
- `freedomui_host_entry` (function) `progs/freedomui/freedomui_minios.c:1067` `int freedomui_host_entry(FreedomUiConfig *c)` -- if (title) { hp_free(title); } return -1L; } ui_layout_free(&lay); hp_free(text); if (title) { hp_free(title); }...
- `main` (function) `progs/freedomui/freedomui_minios.c:1072` `int main(int argc, char **argv)` -- ui_layout_free(&lay); hp_free(text); if (title) { hp_free(title); } return 0L; } /** Host harness entry for pure...

## progs/freedomui/media_unavailable.c
Depends on: `kernel/string.c`
- `write_all` (function) `progs/freedomui/media_unavailable.c:20` `static void write_all(int fd, const void *buf, size_t len)` -- closed: no decoder process is ever started, and a direct --media-decoder invocation answers with one MD_ERROR and...
- `media_decoder_run` (function) `progs/freedomui/media_unavailable.c:41` `void media_decoder_run(int out_fd, int cmd_fd)` -- Refuses to start a decoder: the caller reports the failure and stays * responsive (browser_ui video_play already...

## progs/freedomui/platform_minios.c
Depends on: `kernel/string.c`, `progs/freedomui/ps2_keymap.h`, `progs/minios_abi.h`
- `sys_fb_info_rgb` (function) `progs/freedomui/platform_minios.c:83` `static long sys_fb_info_rgb(int *rgb)`
- `now_ms` (function) `progs/freedomui/platform_minios.c:94` `static long now_ms(void)`
- `set_title` (function) `progs/freedomui/platform_minios.c:98` `static void set_title(const char *title)`
- `pf_display_open` (function) `progs/freedomui/platform_minios.c:137` `pf_status pf_display_open(pf_display **out)`
- `pf_display_close` (function) `progs/freedomui/platform_minios.c:153` `void pf_display_close(pf_display *d)`
- `pf_display_flush` (function) `progs/freedomui/platform_minios.c:162` `void pf_display_flush(pf_display *d)`
- `pf_display_set_cursor` (function) `progs/freedomui/platform_minios.c:166` `void pf_display_set_cursor(pf_display *d, pf_cursor c)`
- `deliver_pending` (function) `progs/freedomui/platform_minios.c:173` `static int deliver_pending(pf_display *d)`
- `key_event` (function) `progs/freedomui/platform_minios.c:183` `static void key_event(pf_display *d, const ps2_key *k, int kind)`
- `pump_keyboard` (function) `progs/freedomui/platform_minios.c:210` `static int pump_keyboard(pf_display *d)`
- `pump_mouse` (function) `progs/freedomui/platform_minios.c:224` `static int pump_mouse(pf_display *d)`
- `pf_display_wait` (function) `progs/freedomui/platform_minios.c:267` `int pf_display_wait(pf_display *d, struct pollfd *extra, int n, int timeout_ms)`
- `pf_clipboard_available` (function) `progs/freedomui/platform_minios.c:292` `int pf_clipboard_available(const pf_display *d)`
- `pf_clipboard_set_text` (function) `progs/freedomui/platform_minios.c:296` `pf_status pf_clipboard_set_text(pf_display *d, const char *text)`
- `pf_clipboard_get_text` (function) `progs/freedomui/platform_minios.c:303` `pf_status pf_clipboard_get_text(pf_display *d, char **out, size_t *out_len)`
- `pf_window_open` (function) `progs/freedomui/platform_minios.c:319` `pf_status pf_window_open(pf_display *d, const pf_window_opts *o,
                         const p...`
- `pf_window_close` (function) `progs/freedomui/platform_minios.c:341` `void pf_window_close(pf_window *w)`
- `pf_window_surface` (function) `progs/freedomui/platform_minios.c:358` `cairo_surface_t *pf_window_surface(pf_window *w, int width, int height)`
- `pf_window_present` (function) `progs/freedomui/platform_minios.c:373` `void pf_window_present(pf_window *w)`
- `pf_window_set_title` (function) `progs/freedomui/platform_minios.c:407` `void pf_window_set_title(pf_window *w, const char *title)`
- `set_zoom_state` (function) `progs/freedomui/platform_minios.c:413` `static void set_zoom_state(pf_window *w, unsigned bit, int on)`
- `pf_window_set_maximized` (function) `progs/freedomui/platform_minios.c:422` `void pf_window_set_maximized(pf_window *w, int on)`
- `pf_window_set_fullscreen` (function) `progs/freedomui/platform_minios.c:426` `void pf_window_set_fullscreen(pf_window *w, int on)`
- `pf_window_minimize` (function) `progs/freedomui/platform_minios.c:430` `void pf_window_minimize(pf_window *w)`
- `pf_window_begin_move` (function) `progs/freedomui/platform_minios.c:434` `void pf_window_begin_move(pf_window *w)`
- `pf_window_begin_resize` (function) `progs/freedomui/platform_minios.c:438` `void pf_window_begin_resize(pf_window *w, pf_edge edge)`

## progs/freedomui/ps2_keymap.c
Depends on: `kernel/string.c`, `progs/freedomui/ps2_keymap.h`
- `ps2_init` (function) `progs/freedomui/ps2_keymap.c:144` `void ps2_init(ps2_state *s)`
- `held_mods` (function) `progs/freedomui/ps2_keymap.c:150` `static unsigned held_mods(const ps2_state *s)`
- `set_text` (function) `progs/freedomui/ps2_keymap.c:158` `static void set_text(ps2_key *k, char c)`
- `is_letter` (function) `progs/freedomui/ps2_keymap.c:164` `static int is_letter(char c)`
- `modifier_key` (function) `progs/freedomui/ps2_keymap.c:169` `static uint32_t modifier_key(ps2_state *s, unsigned code, int extended, int make)` -- return m; } static void set_text(ps2_key *k, char c) { k->text[0] = c; k->text[1] = '\0'; k->text_len = 1; } static...
- `extended_key` (function) `progs/freedomui/ps2_keymap.c:195` `static uint32_t extended_key(unsigned code, ps2_key *k)` -- if (make) s->caps_lock = !s->caps_lock; return KE_KEY_Caps_Lock; } else if (!extended && code == SC_NUMLOCK) { if...
- `plain_key` (function) `progs/freedomui/ps2_keymap.c:218` `static uint32_t plain_key(const ps2_state *s, unsigned code, ps2_key *k)` -- case SC_E0_RIGHT:  return KE_KEY_Right; case SC_E0_END:    return KE_KEY_End; case SC_E0_DOWN:   return KE_KEY_Down...
- `ps2_feed` (function) `progs/freedomui/ps2_keymap.c:253` `int ps2_feed(ps2_state *s, uint8_t byte, ps2_key *out)`

## progs/freedomui/ps2_keymap.h
Imported by: `progs/freedomui/platform_minios.c`, `progs/freedomui/ps2_keymap.c`, `tests/test_ps2_keymap.c`
- `ps2_init` (function) `progs/freedomui/ps2_keymap.h:47` `void ps2_init(ps2_state *s);` -- int      extended;  /* an E0 prefix is pending int      skip;      /* bytes of an E1 sequence still to swallow }...
- `arguments` (function) `progs/freedomui/ps2_keymap.h:51` `* arguments (out is then left untouched). */ int ps2_feed(ps2_state *s, uint8_t byte, ps2_key *out);`

## progs/lisp/lisp.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`
- `numbers` (function) `progs/lisp/lisp.c:9` `* * Language surface: numbers (int64), strings, symbols, cons cells, closures * with lexical scope, and the special...`
- `lisp_version` (function) `progs/lisp/lisp.c:62` `static const char *lisp_version(void)` -- Version string printed by --version and the REPL banner.
- `msys` (function) `progs/lisp/lisp.c:205` `static long msys(long n, long a1, long a2, long a3)` -- Raw 3-argument syscall through the x86-64 Linux ABI.
- `msys5` (function) `progs/lisp/lisp.c:218` `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)` -- Raw 5-argument syscall for SYS_SPAWN with path, redirect, argc, argv.
- `fatal` (function) `progs/lisp/lisp.c:233` `static void fatal(Runtime *rt, const char *message)` -- Report a fatal internal failure and terminate the process.
- `xalloc` (function) `progs/lisp/lisp.c:242` `static void *xalloc(Runtime *rt, size_t size)` -- Allocate zeroed tracked memory that frees with the runtime.
- `xstrdup` (function) `progs/lisp/lisp.c:266` `static char *xstrdup(Runtime *rt, const char *source)` -- Duplicate a string into tracked memory.
- `make_node` (function) `progs/lisp/lisp.c:284` `static Node *make_node(Runtime *rt, NodeType type)` -- Allocate a node of the given type in tracked memory.
- `make_error` (function) `progs/lisp/lisp.c:293` `static Node *make_error(Runtime *rt, const char *message)` -- Build an error value carrying a diagnostic message.
- `make_num` (function) `progs/lisp/lisp.c:302` `static Node *make_num(Runtime *rt, int64_t value)` -- Build a numeric value node.
- `make_str` (function) `progs/lisp/lisp.c:311` `static Node *make_str(Runtime *rt, const char *value)` -- Build a string value node from a NUL-terminated source.
- `make_sym` (function) `progs/lisp/lisp.c:320` `static Node *make_sym(Runtime *rt, const char *value)` -- Build a symbol value node from a NUL-terminated name.
- `make_prim` (function) `progs/lisp/lisp.c:329` `static Node *make_prim(Runtime *rt, PrimFn function)` -- Build a primitive function value node.
- `cons` (function) `progs/lisp/lisp.c:338` `static Node *cons(Runtime *rt, Node *car, Node *cdr)` -- Build a cons cell from two values.
- `is_nil` (function) `progs/lisp/lisp.c:348` `static bool is_nil(Runtime *rt, const Node *node)` -- Test whether a node is the empty list in any of its spellings.
- `make_file` (function) `progs/lisp/lisp.c:355` `static Node *make_file(Runtime *rt, FILE *handle)` -- Register an open FILE handle and wrap it in a file value node.
- `cleanup` (function) `progs/lisp/lisp.c:377` `static void cleanup(Runtime *rt)` -- Close every tracked file and release every tracked allocation.
- `runtime_init` (function) `progs/lisp/lisp.c:399` `static void runtime_init(Runtime *rt)` -- Initialize a runtime with streams, constants and empty tables.
- `env_new` (function) `progs/lisp/lisp.c:411` `static Env *env_new(Runtime *rt, Env *parent)` -- Allocate a new environment frame with an optional parent.
- `env_bind` (function) `progs/lisp/lisp.c:421` `static void env_bind(Runtime *rt, Env *env, Node *symbol, Node *value)` -- Bind a symbol to a value in the innermost frame.
- `env_set` (function) `progs/lisp/lisp.c:432` `static bool env_set(Env *env, Node *symbol, Node *value)` -- Update the nearest visible binding of a symbol.
- `env_lookup` (function) `progs/lisp/lisp.c:454` `static Node *env_lookup(Env *env, Node *symbol)` -- Resolve the nearest visible binding of a symbol.
- `reader_peek` (function) `progs/lisp/lisp.c:475` `static char reader_peek(const Reader *reader)` -- Peek at the current reader character without consuming it.
- `reader_next` (function) `progs/lisp/lisp.c:482` `static char reader_next(Reader *reader)` -- Consume one reader character and track line and column.
- `reader_at_end` (function) `progs/lisp/lisp.c:500` `static bool reader_at_end(const Reader *reader)` -- Test whether the reader reached the end of its buffer.
- `skip_space_and_comments` (function) `progs/lisp/lisp.c:507` `static void skip_space_and_comments(Reader *reader)` -- Skip whitespace and line comments starting with a semicolon.
- `sb_init` (function) `progs/lisp/lisp.c:523` `static void sb_init(StringBuilder *builder)` -- Initialize a string builder with a bounded initial capacity.
- `sb_push` (function) `progs/lisp/lisp.c:536` `static void sb_push(StringBuilder *builder, char value)` -- Append one byte to a string builder with overflow-checked growth.
- `parse_ok` (function) `progs/lisp/lisp.c:562` `static ParseResult parse_ok(Node *value)` -- Build a successful parse result.
- `parse_eof` (function) `progs/lisp/lisp.c:573` `static ParseResult parse_eof(void)` -- Build an end-of-input parse result.
- `parse_error` (function) `progs/lisp/lisp.c:584` `static ParseResult parse_error(const char *message)` -- Build a parse error result with a bounded message.
- `read_list` (function) `progs/lisp/lisp.c:596` `static ParseResult read_list(Runtime *rt, Reader *reader)` -- Read a parenthesized list terminated by a closing paren.
- `read_string` (function) `progs/lisp/lisp.c:626` `static ParseResult read_string(Runtime *rt, Reader *reader)` -- Read a double-quoted string with backslash escapes.
- `token_delimiter` (function) `progs/lisp/lisp.c:677` `static bool token_delimiter(char c)` -- Test whether a character terminates an atom token.
- `read_atom` (function) `progs/lisp/lisp.c:685` `static ParseResult read_atom(Runtime *rt, Reader *reader)` -- Read a number, nil, t or symbol token.
- `read_expr` (function) `progs/lisp/lisp.c:721` `static ParseResult read_expr(Runtime *rt, Reader *reader)` -- Read one expression, skipping whitespace and comments first.
- `list_count` (function) `progs/lisp/lisp.c:750` `static size_t list_count(Runtime *rt, Node *list, bool *proper)` -- Count proper list elements and report whether the spine is proper.
- `has_arity` (function) `progs/lisp/lisp.c:767` `static bool has_arity(Runtime *rt, Node *args, size_t expected)` -- Test whether an argument list has exactly the expected length.
- `arg_at` (function) `progs/lisp/lisp.c:775` `static Node *arg_at(Runtime *rt, Node *args, size_t index)` -- Fetch the positional argument at an index or NULL when absent.
- `arg_matches` (function) `progs/lisp/lisp.c:815` `static bool arg_matches(const Node *value, ArgKind kind)` -- Test whether an already-fetched argument matches one ArgKind.
- `check_args` (function) `progs/lisp/lisp.c:841` `static bool check_args(Runtime *rt, Node *args, const ArgKind *kinds,
    size_t n, Node **out)` -- Validate that args is a proper list of exactly n elements whose types match kinds[0..n), writing each fetched...
- `arity0` (function) `progs/lisp/lisp.c:861` `static bool arity0(Runtime *rt, Node *args)` -- Validate that args is the empty argument list.
- `prim_add` (function) `progs/lisp/lisp.c:869` `static Node *prim_add(Runtime *rt, Node *args)` -- Add two numbers with overflow reported as an error value.
- `prim_sub` (function) `progs/lisp/lisp.c:885` `static Node *prim_sub(Runtime *rt, Node *args)` -- Subtract two numbers with overflow reported as an error value.
- `prim_mul` (function) `progs/lisp/lisp.c:901` `static Node *prim_mul(Runtime *rt, Node *args)` -- Multiply two numbers with overflow reported as an error value.
- `prim_div` (function) `progs/lisp/lisp.c:917` `static Node *prim_div(Runtime *rt, Node *args)` -- Divide two numbers with zero and overflow reported as errors.
- `prim_eq` (function) `progs/lisp/lisp.c:939` `static Node *prim_eq(Runtime *rt, Node *args)` -- Compare two numbers for equality.
- `prim_lt` (function) `progs/lisp/lisp.c:951` `static Node *prim_lt(Runtime *rt, Node *args)` -- Compare two numbers with less-than.
- `prim_car` (function) `progs/lisp/lisp.c:963` `static Node *prim_car(Runtime *rt, Node *args)` -- Return the first element of a cons cell or nil.
- `prim_cdr` (function) `progs/lisp/lisp.c:975` `static Node *prim_cdr(Runtime *rt, Node *args)` -- Return the rest of a cons cell or nil.
- `prim_cons` (function) `progs/lisp/lisp.c:987` `static Node *prim_cons(Runtime *rt, Node *args)` -- Build a cons cell from two values.
- `prim_string_concat` (function) `progs/lisp/lisp.c:999` `static Node *prim_string_concat(Runtime *rt, Node *args)` -- Concatenate two strings with an overflow-checked allocation.
- `prim_string_eq` (function) `progs/lisp/lisp.c:1026` `static Node *prim_string_eq(Runtime *rt, Node *args)` -- Compare two strings for equality.
- `prim_string_length` (function) `progs/lisp/lisp.c:1038` `static Node *prim_string_length(Runtime *rt, Node *args)` -- Return the byte length of a string.
- `prim_string_at` (function) `progs/lisp/lisp.c:1050` `static Node *prim_string_at(Runtime *rt, Node *args)` -- Return the one-character string at a byte index or nil when out of range.
- `prim_char_code` (function) `progs/lisp/lisp.c:1072` `static Node *prim_char_code(Runtime *rt, Node *args)` -- Convert between a one-character string and its byte value.
- `prim_print` (function) `progs/lisp/lisp.c:1094` `static Node *prim_print(Runtime *rt, Node *args)` -- Print a value without a trailing newline.
- `prim_println` (function) `progs/lisp/lisp.c:1108` `static Node *prim_println(Runtime *rt, Node *args)` -- Print a value with a trailing newline.
- `file_mode_allowed` (function) `progs/lisp/lisp.c:1123` `static bool file_mode_allowed(const char *mode)` -- Test whether a file mode string belongs to the safe whitelist.
- `prim_read_char` (function) `progs/lisp/lisp.c:1183` `static Node *prim_read_char(Runtime *rt, Node *args)` -- Read one byte from a file or nil at end of file.
- `prim_write` (function) `progs/lisp/lisp.c:1200` `static Node *prim_write(Runtime *rt, Node *args)` -- Write a string or byte value to an open file.
- `prim_close_file` (function) `progs/lisp/lisp.c:1224` `static Node *prim_close_file(Runtime *rt, Node *args)` -- Close an open file and release its runtime slot.
- `prim_null_p` (function) `progs/lisp/lisp.c:1249` `static Node *prim_null_p(Runtime *rt, Node *args)` -- Test whether a value is nil.
- `prim_number_p` (function) `progs/lisp/lisp.c:1261` `static Node *prim_number_p(Runtime *rt, Node *args)` -- Test whether a value is a number.
- `prim_string_p` (function) `progs/lisp/lisp.c:1273` `static Node *prim_string_p(Runtime *rt, Node *args)` -- Test whether a value is a string.
- `prim_error_message` (function) `progs/lisp/lisp.c:1285` `static Node *prim_error_message(Runtime *rt, Node *args)` -- Return the message of an error value or nil for other values.
- `arity` (function) `progs/lisp/lisp.c:1300` `* * Variable arity (0 or 1);`
- `prim_exit` (function) `progs/lisp/lisp.c:1303` `static Node *prim_exit(Runtime *rt, Node *args)` -- Terminate the process with a numeric exit status.
- `prim_time_ms` (function) `progs/lisp/lisp.c:1330` `static Node *prim_time_ms(Runtime *rt, Node *args)` -- Return milliseconds since boot through the kernel time service.
- `prim_rtc` (function) `progs/lisp/lisp.c:1340` `static Node *prim_rtc(Runtime *rt, Node *args)` -- Return the clock time as a three-element list or nil when unavailable.
- `prim_fb_info` (function) `progs/lisp/lisp.c:1357` `static Node *prim_fb_info(Runtime *rt, Node *args)` -- Return framebuffer width, height and pitch or nil when unavailable.
- `prim_vol` (function) `progs/lisp/lisp.c:1377` `static Node *prim_vol(Runtime *rt, Node *args)` -- Read or set the speaker volume, clamped to the valid range.
- `prim_pal` (function) `progs/lisp/lisp.c:1405` `static Node *prim_pal(Runtime *rt, Node *args)` -- Load a 768-byte VGA palette from a string value.
- `prim_pcspeaker` (function) `progs/lisp/lisp.c:1421` `static Node *prim_pcspeaker(Runtime *rt, Node *args)` -- Play a speaker tone for a bounded millisecond duration.
- `prim_minios_run` (function) `progs/lisp/lisp.c:1465` `static Node *prim_minios_run(Runtime *rt, Node *args)` -- Run a program through SYS_SPAWN and return its exit code.
- `eval_list` (function) `progs/lisp/lisp.c:1527` `static Node *eval_list(Runtime *rt, Node *list, Env *env)` -- Evaluate every element of a list into a fresh proper list.
- `eval_sequence` (function) `progs/lisp/lisp.c:1551` `static Node *eval_sequence(Runtime *rt, Node *body, Env *env)` -- Evaluate a body sequence and return the last value.
- `valid_params` (function) `progs/lisp/lisp.c:1569` `static bool valid_params(Runtime *rt, Node *params)` -- Test whether a parameter list holds only symbols.
- `eval` (function) `progs/lisp/lisp.c:1583` `static Node *eval(Runtime *rt, Node *expression, Env *env)` -- Evaluate an expression with tail-call reuse and a bounded depth.
- `print_escaped_string` (function) `progs/lisp/lisp.c:1846` `static void print_escaped_string(FILE *out, const char *value)` -- Write a string with escape sequences for readable output.
- `print_node` (function) `progs/lisp/lisp.c:1877` `static void print_node(Runtime *rt, Node *node, bool readable)` -- Print a value in readable or display form with a bounded depth.
- `bind_primitive` (function) `progs/lisp/lisp.c:1948` `static void bind_primitive(Runtime *rt, Env *env, const char *name,
    PrimFn function)` -- Register one named primitive in an environment frame.
- `init_env` (function) `progs/lisp/lisp.c:2004` `static Env *init_env(Runtime *rt)` -- Build the global environment with arithmetic, strings, files and MiniOS.
- `bind_argv` (function) `progs/lisp/lisp.c:2017` `static void bind_argv(Runtime *rt, Env *env, int argc, char **argv, int first)` -- Expose the script argument vector as a proper list of strings.
- `read_all_file` (function) `progs/lisp/lisp.c:2029` `static char *read_all_file(const char *filename, size_t max_bytes)` -- Read a whole file into memory with a hard size cap.
- `process_source` (function) `progs/lisp/lisp.c:2087` `static int process_source(Runtime *rt, const char *source,
    const char *source_name, bool echo)` -- Evaluate every form in a source buffer and report the first failure.
- `process_inline` (function) `progs/lisp/lisp.c:2129` `static int process_inline(Runtime *rt, const char *code)` -- Evaluate one inline expression from the -e flag.
- `print_usage` (function) `progs/lisp/lisp.c:2136` `static void print_usage(Runtime *rt)` -- Print usage for the command line interface.
- `repl` (function) `progs/lisp/lisp.c:2143` `static int repl(Runtime *rt)` -- Run the interactive read-eval loop on the runtime input stream.
- `main` (function) `progs/lisp/lisp.c:2190` `int main(int argc, char **argv)` -- Entry point with -e, script and REPL modes plus bounded arguments.

## progs/lisp/tin.c
- `main` (function) `progs/lisp/tin.c:1` `int main()`

## progs/lua/lua_main.c
Depends on: `kernel/string.c`
- `module` (function) `progs/lua/lua_main.c:5` `* C module (minios.c) can be registered globally before any script runs: * `minios.run(...)`, `minios.time_ms()`...`
- `luaL_require_global` (function) `progs/lua/lua_main.c:22` `static void luaL_require_global(lua_State *L, const char *name,
                                l...`
- `set_arg_table` (function) `progs/lua/lua_main.c:28` `static void set_arg_table(lua_State *L, int argc, char **argv, int first)`
- `docode` (function) `progs/lua/lua_main.c:41` `static int docode(lua_State *L, const char *code)`
- `dofile` (function) `progs/lua/lua_main.c:51` `static int dofile(lua_State *L, const char *name)`
- `repl` (function) `progs/lua/lua_main.c:61` `static int repl(lua_State *L)`
- `main` (function) `progs/lua/lua_main.c:105` `int main(int argc, char **argv)`

## progs/lua/minios.c
Depends on: `progs/minios_abi.h`
Imported by: `progs/micropython/variants/minios/lib/hello.py`, `progs/micropython/variants/minios/lib/mip.py`, `progs/src/shell.py`, `progs/src/test.py`
- `msys5` (function) `progs/lua/minios.c:37` `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)` -- /* ── raw syscall helpers (x86-64 Linux ABI) ─────────────────────────── static long msys(long n, long a1, long a2...
- `minios_time_ms` (function) `progs/lua/minios.c:62` `static int minios_time_ms(lua_State *L)` -- } /* ── MiniOS syscall numbers (canonical table from minios_abi.h) ─────── #include "minios_abi.h" #define...
- `minios_rtc` (function) `progs/lua/minios.c:68` `static int minios_rtc(lua_State *L)` -- #define SYS_PCSPK_INIT  MINIOS_SYS_PCSPK_INIT #define SYS_PCSPK_TONE  MINIOS_SYS_PCSPK_TONE #define SYS_RTC...
- `minios_fb_info` (function) `progs/lua/minios.c:82` `static int minios_fb_info(lua_State *L)` -- static int minios_rtc(lua_State *L) { int h, m, s; if (msys(SYS_RTC, (long)&h, (long)&m, (long)&s) < 0) {...
- `minios_vol` (function) `progs/lua/minios.c:96` `static int minios_vol(lua_State *L)` -- static int minios_fb_info(lua_State *L) { int w, h, p; if (msys(SYS_FB_INFO, (long)&w, (long)&h, (long)&p) < 0) {...
- `minios_pal` (function) `progs/lua/minios.c:109` `static int minios_pal(lua_State *L)` -- /* ── minios.vol([v]) -> current volume ─────────────────────────────── static int minios_vol(lua_State *L) { if...
- `minios_pcspeaker` (function) `progs/lua/minios.c:119` `static int minios_pcspeaker(lua_State *L)` -- return 1; } /* ── minios.pal(buf) -- load a 768-byte VGA DAC palette ────────────── static int minios_pal(lua_State...
- `minios_run` (function) `progs/lua/minios.c:136` `static int minios_run(lua_State *L)` -- ── minios.run(path[, args][, redirect]) -> exit code ─────────────── Runs a program through SYS_SPAWN (215)...
- `luaopen_minios` (function) `progs/lua/minios.c:192` `int luaopen_minios(lua_State *L)`

## progs/micropython/variants/minios/lib/mip.py
Depends on: `progs/lua/minios.c`
Imported by: `progs/src/test_py.py`
- `parse_url` (function) `progs/micropython/variants/minios/lib/mip.py:49` `def parse_url(url)` -- Split an http/https URL into (scheme, host, port, path).
- `split_url` (function) `progs/micropython/variants/minios/lib/mip.py:98` `def split_url(url)` -- Split an http URL into (host, port, path); https is refused here.
- `split_https_url` (function) `progs/micropython/variants/minios/lib/mip.py:106` `def split_https_url(url)` -- Split an https URL into (host, port, path); http is refused here.
- `module_name` (function) `progs/micropython/variants/minios/lib/mip.py:114` `def module_name(url)` -- Return the .py file name a URL installs, validating it is bare.
- `parse_response` (function) `progs/micropython/variants/minios/lib/mip.py:150` `def parse_response(data)` -- Split one HTTP/1.x response into (status, headers, body).
- `absolute_url` (function) `progs/micropython/variants/minios/lib/mip.py:202` `def absolute_url(base, location)` -- Resolve a redirect Location against base; http and https survive.
- `http_get` (function) `progs/micropython/variants/minios/lib/mip.py:222` `def http_get(host, port, path)` -- Fetch http://host:port/path, returning the raw response bytes.
- `ensure_dir` (function) `progs/micropython/variants/minios/lib/mip.py:276` `def ensure_dir(path)` -- Create path and its parents; existing directories are fine.
- `https_get` (function) `progs/micropython/variants/minios/lib/mip.py:298` `def https_get(host, port, path)` -- Fetch https://host:port/path through the ring-3 TLS engine.
- `install` (function) `progs/micropython/variants/minios/lib/mip.py:336` `def install(url, dest)` -- Fetch url and write it as <dest>/<module>.py; returns the path.
- `main` (function) `progs/micropython/variants/minios/lib/mip.py:394` `def main(argv)` -- CLI entry point: install <url> [dest]; returns the exit code.

## progs/micropython/variants/minios/minios_module.c
Depends on: `progs/minios_abi.h`
- `msys5` (function) `progs/micropython/variants/minios/minios_module.c:26` `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)` -- /* ── raw syscall helper (x86-64 Linux ABI) ─────────────────────────── static long msys(long n, long a1, long a2...
- `minios_time_ms` (function) `progs/micropython/variants/minios/minios_module.c:52` `static mp_obj_t minios_time_ms(void)`
- `MP_DEFINE_CONST_FUN_OBJ_0` (function) `progs/micropython/variants/minios/minios_module.c:55` `static MP_DEFINE_CONST_FUN_OBJ_0(minios_time_ms_obj, minios_time_ms);`
- `minios_rtc` (function) `progs/micropython/variants/minios/minios_module.c:59` `static mp_obj_t minios_rtc(void)`
- `minios_fb_info` (function) `progs/micropython/variants/minios/minios_module.c:76` `static mp_obj_t minios_fb_info(void)`
- `MP_DEFINE_CONST_FUN_OBJ_VAR` (function) `progs/micropython/variants/minios/minios_module.c:107` `static MP_DEFINE_CONST_FUN_OBJ_VAR(minios_vol_obj, 0, minios_vol);`
- `minios_pal` (function) `progs/micropython/variants/minios/minios_module.c:111` `static mp_obj_t minios_pal(mp_obj_t buf_in)`
- `MP_DEFINE_CONST_FUN_OBJ_1` (function) `progs/micropython/variants/minios/minios_module.c:123` `static MP_DEFINE_CONST_FUN_OBJ_1(minios_pal_obj, minios_pal);`
- `minios_pcspeaker` (function) `progs/micropython/variants/minios/minios_module.c:127` `static mp_obj_t minios_pcspeaker(mp_obj_t freq_in, mp_obj_t ms_in)`
- `MP_DEFINE_CONST_FUN_OBJ_2` (function) `progs/micropython/variants/minios/minios_module.c:140` `static MP_DEFINE_CONST_FUN_OBJ_2(minios_pcspeaker_obj, minios_pcspeaker);`
- `minios_run` (function) `progs/micropython/variants/minios/minios_module.c:149` `static mp_obj_t minios_run(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)`
- `MP_DEFINE_CONST_FUN_OBJ_KW` (function) `progs/micropython/variants/minios/minios_module.c:193` `static MP_DEFINE_CONST_FUN_OBJ_KW(minios_run_obj, 1, minios_run);`
- `MP_DEFINE_CONST_DICT` (function) `progs/micropython/variants/minios/minios_module.c:207` `static MP_DEFINE_CONST_DICT(minios_module_globals, minios_module_globals_table);`


Next: [API_p17.md](API_p17.md)
