# Symbols (page 21 of 26)
Previous: [SYMBOLS_p20.md](SYMBOLS_p20.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `nk_context` | struct | `progs/nuklear/nuklear_minios.h:20` | `` |
| `nk_idx_to_rgb` | function | `progs/nuklear/nuklear_minios.h:37` | `void nk_idx_to_rgb(int idx, unsigned char *r, unsigned char *g, unsigned char *b);` |
| `nk_minios_font` | function | `progs/nuklear/nuklear_minios.h:63` | `struct nk_user_font nk_minios_font(void);` |
| `nk_minios_img` | struct | `progs/nuklear/nuklear_minios.h:74` | `` |
| `nk_poll_input` | function | `progs/nuklear/nuklear_minios.h:87` | `void nk_poll_input(struct nk_context *ctx);` |
| `nk_quit_requested` | function | `progs/nuklear/nuklear_minios.h:92` | `int nk_quit_requested(void);` |
| `nk_rasterize` | function | `progs/nuklear/nuklear_minios.h:66` | `void nk_rasterize(struct nk_context *ctx);` |
| `nk_rgb_available` | function | `progs/nuklear/nuklear_minios.h:33` | `int nk_rgb_available(void);` |
| `nk_set_scancode_hook` | function | `progs/nuklear/nuklear_minios.h:101` | `void nk_set_scancode_hook(nk_scancode_cb cb, void *ud);` |
| `nk_sys_fb_info` | function | `progs/nuklear/nuklear_minios.h:46` | `long nk_sys_fb_info(int *w, int *h, int *pitch);` |
| `nk_sys_gfx_set_title` | function | `progs/nuklear/nuklear_minios.h:53` | `long nk_sys_gfx_set_title(const char *t);` |
| `nk_sys_kbd` | function | `progs/nuklear/nuklear_minios.h:42` | `long nk_sys_kbd(void);` |
| `nk_sys_kbd_raw` | function | `progs/nuklear/nuklear_minios.h:44` | `long nk_sys_kbd_raw(int on);` |
| `nk_sys_mouse` | function | `progs/nuklear/nuklear_minios.h:47` | `long nk_sys_mouse(int *xybw);` |
| `nk_sys_mouse_badptr` | function | `progs/nuklear/nuklear_minios.h:51` | `long nk_sys_mouse_badptr(void);` |
| `nk_sys_nk_frame` | function | `progs/nuklear/nuklear_minios.h:52` | `long nk_sys_nk_frame(int *origin);` |
| `nk_sys_palette` | function | `progs/nuklear/nuklear_minios.h:43` | `long nk_sys_palette(const unsigned char *pal768);` |
| `nk_sys_time_ms` | function | `progs/nuklear/nuklear_minios.h:41` | `long nk_sys_time_ms(void);` |
| `nk_sys_vga_mode` | function | `progs/nuklear/nuklear_minios.h:45` | `long nk_sys_vga_mode(int on);` |
| `nk_user_font` | struct | `progs/nuklear/nuklear_minios.h:21` | `` |
| `X` | macro | `progs/nuklear/nuklear_theme.c:21` | `#define X(k, i)` |
| `nk_theme_active` | function | `progs/nuklear/nuklear_theme.c:49` | `int nk_theme_active(char *dst, int cap)` |
| `nk_theme_apply` | function | `progs/nuklear/nuklear_theme.c:141` | `int nk_theme_apply(struct nk_context *ctx, const char *name)` |
| `nk_theme_name_ok` | function | `progs/nuklear/nuklear_theme.c:37` | `static int nk_theme_name_ok(const char *name)` |
| `nk_theme_parse_line` | function | `progs/nuklear/nuklear_theme.c:73` | `static int nk_theme_parse_line(const char *line,                                unsigned char rgb...` |
| `nk_theme_probe` | function | `progs/nuklear/nuklear_theme.c:105` | `int nk_theme_probe(const char *name, unsigned char rgb[NK_THEME_KEY_COUNT][3])` |
| `nk_theme_slot` | struct | `progs/nuklear/nuklear_theme.c:15` | `` |
| `NK_THEME_DEFAULT` | macro | `progs/nuklear/nuklear_theme.h:20` | `#define NK_THEME_DEFAULT` |
| `NK_THEME_KEY_COUNT` | macro | `progs/nuklear/nuklear_theme.h:57` | `#define NK_THEME_KEY_COUNT` |
| `NK_THEME_KEY_LIST` | macro | `progs/nuklear/nuklear_theme.h:23` | `#define NK_THEME_KEY_LIST` |
| `NK_THEME_KEY_MAX` | macro | `progs/nuklear/nuklear_theme.h:16` | `#define NK_THEME_KEY_MAX` |
| `NK_THEME_LINE_MAX` | macro | `progs/nuklear/nuklear_theme.h:17` | `#define NK_THEME_LINE_MAX` |
| `NK_THEME_NAME_MAX` | macro | `progs/nuklear/nuklear_theme.h:15` | `#define NK_THEME_NAME_MAX` |
| `NK_THEME_PATH_CURRENT` | macro | `progs/nuklear/nuklear_theme.h:19` | `#define NK_THEME_PATH_CURRENT` |
| `NK_THEME_PATH_DIR` | macro | `progs/nuklear/nuklear_theme.h:18` | `#define NK_THEME_PATH_DIR` |
| `NUKLEAR_THEME_H` | macro | `progs/nuklear/nuklear_theme.h:2` | `#define NUKLEAR_THEME_H` |
| `nk_context` | struct | `progs/nuklear/nuklear_theme.h:59` | `` |
| `nk_theme_active` | function | `progs/nuklear/nuklear_theme.h:62` | `int nk_theme_active(char *dst, int cap);` |
| `nk_theme_apply` | function | `progs/nuklear/nuklear_theme.h:68` | `int nk_theme_apply(struct nk_context *ctx, const char *name);` |
| `nk_theme_probe` | function | `progs/nuklear/nuklear_theme.h:65` | `int nk_theme_probe(const char *name, unsigned char rgb[NK_THEME_KEY_COUNT][3]);` |
| `PAINT_DEFAULT_PATH` | macro | `progs/paint/paint.c:42` | `#define PAINT_DEFAULT_PATH` |
| `PAINT_FILE_BTN_W` | macro | `progs/paint/paint.c:44` | `#define PAINT_FILE_BTN_W` |
| `PAINT_FILE_MAX` | macro | `progs/paint/paint.c:36` | `#define PAINT_FILE_MAX` |
| `PAINT_FRAME_ATTEMPTS` | macro | `progs/paint/paint.c:46` | `#define PAINT_FRAME_ATTEMPTS` |
| `PAINT_FRAME_MS` | macro | `progs/paint/paint.c:45` | `#define PAINT_FRAME_MS` |
| `PAINT_H` | macro | `progs/paint/paint.c:33` | `#define PAINT_H` |
| `PAINT_N` | macro | `progs/paint/paint.c:34` | `#define PAINT_N` |
| `PAINT_NCOLORS` | macro | `progs/paint/paint.c:47` | `#define PAINT_NCOLORS` |
| `PAINT_NSIZES` | macro | `progs/paint/paint.c:48` | `#define PAINT_NSIZES` |
| `PAINT_NTOOLS` | macro | `progs/paint/paint.c:49` | `#define PAINT_NTOOLS` |
| `PAINT_PANEL_TITLE` | macro | `progs/paint/paint.c:43` | `#define PAINT_PANEL_TITLE` |
| `PAINT_PATH_MAX` | macro | `progs/paint/paint.c:35` | `#define PAINT_PATH_MAX` |
| `PAINT_PNG_MAX` | macro | `progs/paint/paint.c:39` | `#define PAINT_PNG_MAX` |
| `PAINT_PNG_MAX_DIM` | macro | `progs/paint/paint.c:40` | `#define PAINT_PNG_MAX_DIM` |
| `PAINT_STATUS_MAX` | macro | `progs/paint/paint.c:37` | `#define PAINT_STATUS_MAX` |
| `PAINT_TITLE` | macro | `progs/paint/paint.c:41` | `#define PAINT_TITLE` |
| `PAINT_TOOL_BRUSH` | macro | `progs/paint/paint.c:52` | `#define PAINT_TOOL_BRUSH` |
| `PAINT_TOOL_CIRCLE` | macro | `progs/paint/paint.c:55` | `#define PAINT_TOOL_CIRCLE` |
| `PAINT_TOOL_ERASER` | macro | `progs/paint/paint.c:57` | `#define PAINT_TOOL_ERASER` |
| `PAINT_TOOL_FILL` | macro | `progs/paint/paint.c:56` | `#define PAINT_TOOL_FILL` |
| `PAINT_TOOL_LINE` | macro | `progs/paint/paint.c:53` | `#define PAINT_TOOL_LINE` |
| `PAINT_TOOL_RECT` | macro | `progs/paint/paint.c:54` | `#define PAINT_TOOL_RECT` |
| `PAINT_UI_MEMORY` | macro | `progs/paint/paint.c:38` | `#define PAINT_UI_MEMORY` |
| `PAINT_W` | macro | `progs/paint/paint.c:32` | `#define PAINT_W` |
| `STBI_NO_STDIO` | macro | `progs/paint/paint.c:28` | `#define STBI_NO_STDIO` |
| `STBI_ONLY_PNG` | macro | `progs/paint/paint.c:27` | `#define STBI_ONLY_PNG` |
| `STB_IMAGE_IMPLEMENTATION` | macro | `progs/paint/paint.c:26` | `#define STB_IMAGE_IMPLEMENTATION` |
| `main` | function | `progs/paint/paint.c:992` | `int main(int argc, char **argv)` |
| `paint_adler` | function | `progs/paint/paint.c:296` | `static unsigned long paint_adler(const unsigned char *p, unsigned long n)` |
| `paint_blit` | function | `progs/paint/paint.c:549` | `static void paint_blit(int ox, int oy)` |
| `paint_circle_fill` | function | `progs/paint/paint.c:161` | `static int paint_circle_fill(unsigned char *buf, int w, int h, int cx,                           ...` |
| `paint_clamp` | function | `progs/paint/paint.c:92` | `static int paint_clamp(int v, int lo, int hi)` |
| `paint_crc_init` | function | `progs/paint/paint.c:272` | `static void paint_crc_init(void)` |
| `paint_crc_update` | function | `progs/paint/paint.c:285` | `static unsigned long paint_crc_update(unsigned long c,                                       cons...` |
| `paint_dab` | function | `progs/paint/paint.c:108` | `static void paint_dab(unsigned char *buf, int w, int h, int x, int y,                       unsig...` |
| `paint_flood` | function | `progs/paint/paint.c:179` | `static int paint_flood(unsigned char *buf, int w, int h, int x, int y,                        uns...` |
| `paint_gui_run` | function | `progs/paint/paint.c:942` | `static void paint_gui_run(void)` |
| `paint_handle_input` | function | `progs/paint/paint.c:577` | `static void paint_handle_input(struct nk_context *ctx)` |
| `paint_ink` | function | `progs/paint/paint.c:570` | `static unsigned char paint_ink(void)` |
| `paint_line` | function | `progs/paint/paint.c:119` | `static int paint_line(unsigned char *buf, int w, int h, int x0, int y0,                       int...` |
| `paint_load_file` | function | `progs/paint/paint.c:461` | `static int paint_load_file(const char *path)` |
| `paint_nearest` | function | `progs/paint/paint.c:223` | `static int paint_nearest(const unsigned char *pal, unsigned r, unsigned g,                       ...` |
| `paint_pal` | function | `progs/paint/paint.c:240` | `static const unsigned char *paint_pal(void)` |
| `paint_path_ok` | function | `progs/paint/paint.c:251` | `static int paint_path_ok(const char *p)` |
| `paint_pattern_present` | function | `progs/paint/paint.c:720` | `static int paint_pattern_present(int fw, int fh, int fp, int *ox, int *oy)` |
| `paint_plot` | function | `progs/paint/paint.c:99` | `static int paint_plot(unsigned char *buf, int w, int h, int x, int y,                       unsig...` |
| `paint_png_encode` | function | `progs/paint/paint.c:333` | `static long paint_png_encode(unsigned char *dst, unsigned long cap,                              ...` |
| `paint_put_bytes` | function | `progs/paint/paint.c:320` | `static int paint_put_bytes(unsigned char *dst, unsigned long cap,                            unsi...` |
| `paint_put_u32` | function | `progs/paint/paint.c:308` | `static int paint_put_u32(unsigned char *dst, unsigned long cap,                          unsigned...` |
| `paint_rect_fill` | function | `progs/paint/paint.c:144` | `static int paint_rect_fill(unsigned char *buf, int w, int h, int x0, int y0,                     ...` |
| `paint_save_file` | function | `progs/paint/paint.c:514` | `static int paint_save_file(const char *path)` |
| `paint_selftest` | function | `progs/paint/paint.c:755` | `static int paint_selftest(void)` |
| `paint_ui_build` | function | `progs/paint/paint.c:636` | `static void paint_ui_build(struct nk_context *ctx)` |
| `BK_H` | macro | `progs/piano/piano.c:193` | `#define BK_H` |
| `BK_W` | macro | `progs/piano/piano.c:192` | `#define BK_W` |
| `BTN_GAP` | macro | `progs/piano/piano.c:548` | `#define BTN_GAP` |
| `BTN_W` | macro | `progs/piano/piano.c:547` | `#define BTN_W` |
| `CTRL_H` | macro | `progs/piano/piano.c:546` | `#define CTRL_H` |
| `CTRL_Y` | macro | `progs/piano/piano.c:545` | `#define CTRL_Y` |
| `FX_DELAY_CAP` | macro | `progs/piano/piano.c:407` | `#define FX_DELAY_CAP` |
| `FX_DELAY_MAX_MS` | macro | `progs/piano/piano.c:408` | `#define FX_DELAY_MAX_MS` |
| `FX_FEEDBACK` | macro | `progs/piano/piano.c:409` | `#define FX_FEEDBACK` |
| `FX_TREM_FREQ` | macro | `progs/piano/piano.c:411` | `#define FX_TREM_FREQ` |
| `FX_WET` | macro | `progs/piano/piano.c:410` | `#define FX_WET` |
| `KBD_NO_NOTE` | macro | `progs/piano/piano.c:297` | `#define KBD_NO_NOTE` |
| `KEY_H` | macro | `progs/piano/piano.c:191` | `#define KEY_H` |
| `KEY_W` | macro | `progs/piano/piano.c:190` | `#define KEY_W` |
| `KEY_Y` | macro | `progs/piano/piano.c:194` | `#define KEY_Y` |
| `MAX_AUDIO_MS` | macro | `progs/piano/piano.c:76` | `#define MAX_AUDIO_MS` |
| `MAX_VOICES` | macro | `progs/piano/piano.c:221` | `#define MAX_VOICES` |
| `NCTRLS` | macro | `progs/piano/piano.c:561` | `#define NCTRLS` |
| `NKEYS` | macro | `progs/piano/piano.c:209` | `#define NKEYS` |
| `PCM_BUF` | macro | `progs/piano/piano.c:63` | `#define PCM_BUF` |
| `PCM_FRAG` | macro | `progs/piano/piano.c:62` | `#define PCM_FRAG` |
| `PIANO_BASE_MIDI` | macro | `progs/piano/piano.c:195` | `#define PIANO_BASE_MIDI` |
| `PIANO_FRAME_MS` | macro | `progs/piano/piano.c:84` | `#define PIANO_FRAME_MS` |
| `PIANO_FRAME_PERIOD` | macro | `progs/piano/piano.c:91` | `#define PIANO_FRAME_PERIOD` |
| `PIANO_OCTAVES` | macro | `progs/piano/piano.c:196` | `#define PIANO_OCTAVES` |
| `RATE` | macro | `progs/piano/piano.c:61` | `#define RATE` |
| `SYS_PCM2_CLOSE` | macro | `progs/piano/piano.c:59` | `#define SYS_PCM2_CLOSE` |
| `SYS_PCM2_OPEN` | macro | `progs/piano/piano.c:57` | `#define SYS_PCM2_OPEN` |
| `SYS_PCM2_WRITE` | macro | `progs/piano/piano.c:58` | `#define SYS_PCM2_WRITE` |
| `UI_MEMORY` | macro | `progs/piano/piano.c:54` | `#define UI_MEMORY` |
| `clamp_midi` | function | `progs/piano/piano.c:234` | `static int clamp_midi(int m)` |
| `ctrl_active` | function | `progs/piano/piano.c:567` | `static int ctrl_active(int id)` |
| `ctrl_hit` | function | `progs/piano/piano.c:563` | `static int ctrl_hit(int id, int mx, int my)` |
| `ctrl_press` | function | `progs/piano/piano.c:577` | `static void ctrl_press(int id)` |
| `fx_configure` | function | `progs/piano/piano.c:421` | `static void fx_configure(int delay_ms, int tremolo_pct, int clip, int vol)` |
| `fx_process` | function | `progs/piano/piano.c:440` | `static float fx_process(float x)` |
| `hit_key` | function | `progs/piano/piano.c:518` | `static int hit_key(int mx, int my)` |
| `hit_velocity` | function | `progs/piano/piano.c:535` | `static int hit_velocity(int key, int my)` |
| `kbd_all_off` | function | `progs/piano/piano.c:333` | `static void kbd_all_off(void)` |
| `kbd_semitone` | function | `progs/piano/piano.c:298` | `static int kbd_semitone(int code)` |
| `key_rect` | function | `progs/piano/piano.c:511` | `static void key_rect(int key, int *x, int *y, int *w, int *h)` |
| `main` | function | `progs/piano/piano.c:1042` | `int main(int argc, char **argv)` |
| `midi_to_key` | function | `progs/piano/piano.c:211` | `static int midi_to_key(int midi)` |
| `note_off_key` | function | `progs/piano/piano.c:268` | `static void note_off_key(int key)` |
| `note_off_sc` | function | `progs/piano/piano.c:353` | `static void note_off_sc(int code)` |
| `note_on_key` | function | `progs/piano/piano.c:281` | `static void note_on_key(int key, int midi, int vel)` |
| `note_on_sc` | function | `progs/piano/piano.c:339` | `static void note_on_sc(int code, int vel)` |
| `o3_chreg` | function | `progs/piano/piano.c:135` | `static void o3_chreg(int ch, int regbase, int val)` |
| `o3_note` | function | `progs/piano/piano.c:173` | `static void o3_note(int ch, int midi, int on)` |
| `o3_op` | function | `progs/piano/piano.c:127` | `static int o3_op(int ch, int is_car)` |
| `o3_opreg` | function | `progs/piano/piano.c:131` | `static void o3_opreg(int ch, int is_car, int regbase, int val)` |
| `pedal_set` | function | `progs/piano/piano.c:241` | `static void pedal_set(int on)` |
| `piano_scancode` | function | `progs/piano/piano.c:369` | `static void piano_scancode(int code, int make, int e0, void *ud)` |
| `rate` | function | `progs/piano/piano.c:818` | `* wait below caps the frame rate (bench mode skips it so the          * benchmark still measures ...` |
| `render_audio` | function | `progs/piano/piano.c:484` | `static void render_audio(long ms)` |
| `run_pcm2_probe` | function | `progs/piano/piano.c:1015` | `static int run_pcm2_probe(void)` |
| `run_selftest` | function | `progs/piano/piano.c:836` | `static int run_selftest(void)` |
| `sb_flush` | function | `progs/piano/piano.c:469` | `static void sb_flush(void)` |
| `sys_pcm_close` | function | `progs/piano/piano.c:101` | `static void sys_pcm_close(void)` |
| `sys_pcm_open` | function | `progs/piano/piano.c:93` | `static long sys_pcm_open(long flags)` |
| `sys_pcm_write` | function | `progs/piano/piano.c:98` | `static long sys_pcm_write(const void *buf, long len)` |
| `sys_present_idx` | function | `progs/piano/piano.c:112` | `static long sys_present_idx(int *origin)` |
| `sys_yield` | function | `progs/piano/piano.c:104` | `static void sys_yield(void)` |
| `ui_run` | function | `progs/piano/piano.c:594` | `static void ui_run(int bench_ms)` |
| `voice_alloc` | function | `progs/piano/piano.c:255` | `static int voice_alloc(void)` |
| `SDL_Delay` | function | `progs/pokemon/minios_stubs/SDL.h:14` | `static inline void SDL_Delay(Uint32 ms)` |
| `SDL_GetPerformanceCounter` | function | `progs/pokemon/minios_stubs/SDL.h:11` | `static inline Uint64 SDL_GetPerformanceCounter(void)` |
| `SDL_GetPerformanceFrequency` | function | `progs/pokemon/minios_stubs/SDL.h:12` | `static inline Uint64 SDL_GetPerformanceFrequency(void)` |
| `SDL_GetTicks` | function | `progs/pokemon/minios_stubs/SDL.h:13` | `static inline Uint32 SDL_GetTicks(void)` |
| `SDL_H_STUB_MINIOS` | macro | `progs/pokemon/minios_stubs/SDL.h:3` | `#define SDL_H_STUB_MINIOS` |
| `Sint16` | type_alias | `progs/pokemon/minios_stubs/SDL.h:8` | `typedef int16_t Sint16;` |
| `Sint32` | type_alias | `progs/pokemon/minios_stubs/SDL.h:7` | `typedef int32_t Sint32;` |
| `Uint32` | type_alias | `progs/pokemon/minios_stubs/SDL.h:6` | `typedef uint32_t Uint32;` |
| `Uint64` | type_alias | `progs/pokemon/minios_stubs/SDL.h:5` | `typedef uint64_t Uint64;` |
| `Uint8` | type_alias | `progs/pokemon/minios_stubs/SDL.h:9` | `typedef uint8_t Uint8;` |
| `FB_ADDR` | macro | `progs/pokemon/platform_minios.c:160` | `#define FB_ADDR` |
| `FB_H` | macro | `progs/pokemon/platform_minios.c:162` | `#define FB_H` |
| `FB_W` | macro | `progs/pokemon/platform_minios.c:161` | `#define FB_W` |
| `GB_DST_H` | macro | `progs/pokemon/platform_minios.c:166` | `#define GB_DST_H` |
| `GB_DST_W` | macro | `progs/pokemon/platform_minios.c:165` | `#define GB_DST_W` |
| `GB_DST_X0` | macro | `progs/pokemon/platform_minios.c:167` | `#define GB_DST_X0` |
| `GB_DST_Y0` | macro | `progs/pokemon/platform_minios.c:168` | `#define GB_DST_Y0` |
| `GB_SCALE` | macro | `progs/pokemon/platform_minios.c:164` | `#define GB_SCALE` |
| `MENU_BAR_H` | macro | `progs/pokemon/platform_minios.c:586` | `#define MENU_BAR_H` |
| `MENU_BG` | macro | `progs/pokemon/platform_minios.c:595` | `#define MENU_BG` |
| `MENU_DROP_W` | macro | `progs/pokemon/platform_minios.c:590` | `#define MENU_DROP_W` |
| `MENU_DROP_X0` | macro | `progs/pokemon/platform_minios.c:589` | `#define MENU_DROP_X0` |
| `MENU_FG` | macro | `progs/pokemon/platform_minios.c:596` | `#define MENU_FG` |
| `MENU_FILE_X0` | macro | `progs/pokemon/platform_minios.c:587` | `#define MENU_FILE_X0` |
| `MENU_FILE_X1` | macro | `progs/pokemon/platform_minios.c:588` | `#define MENU_FILE_X1` |
| `MENU_HOVER` | macro | `progs/pokemon/platform_minios.c:597` | `#define MENU_HOVER` |
| `MENU_ITEM_H` | macro | `progs/pokemon/platform_minios.c:591` | `#define MENU_ITEM_H` |
| `MENU_NITEMS` | macro | `progs/pokemon/platform_minios.c:592` | `#define MENU_NITEMS` |
| `MENU_OSD_BG` | macro | `progs/pokemon/platform_minios.c:598` | `#define MENU_OSD_BG` |
| `MINIOS_ARP_BASS_MS` | macro | `progs/pokemon/platform_minios.c:237` | `#define MINIOS_ARP_BASS_MS` |
| `MINIOS_ARP_MEL_MS` | macro | `progs/pokemon/platform_minios.c:238` | `#define MINIOS_ARP_MEL_MS` |
| `MINIOS_AUDIO_MAX_HZ` | macro | `progs/pokemon/platform_minios.c:236` | `#define MINIOS_AUDIO_MAX_HZ` |
| `MINIOS_AUDIO_MIN_HZ` | macro | `progs/pokemon/platform_minios.c:235` | `#define MINIOS_AUDIO_MIN_HZ` |
| `MINIOS_AUDIO_RATE` | macro | `progs/pokemon/platform_minios.c:233` | `#define MINIOS_AUDIO_RATE` |
| `MINIOS_AUDIO_SILENCE_E` | macro | `progs/pokemon/platform_minios.c:234` | `#define MINIOS_AUDIO_SILENCE_E` |
| `MINIOS_AUTOSAVE_MS` | macro | `progs/pokemon/platform_minios.c:1193` | `#define MINIOS_AUTOSAVE_MS` |
| `MINIOS_FF_FRAMESKIP` | macro | `progs/pokemon/platform_minios.c:1205` | `#define MINIOS_FF_FRAMESKIP` |
| `STBI_NO_STDIO` | macro | `progs/pokemon/platform_minios.c:62` | `#define STBI_NO_STDIO` |
| `STBI_ONLY_PNG` | macro | `progs/pokemon/platform_minios.c:61` | `#define STBI_ONLY_PNG` |
| `STB_IMAGE_IMPLEMENTATION` | macro | `progs/pokemon/platform_minios.c:60` | `#define STB_IMAGE_IMPLEMENTATION` |
| `_dl_argv` | function | `progs/pokemon/platform_minios.c:197` | `* usable _dl_argv (it bound to unrelated storage and strcmp faulted).  * DO NOT reintroduce argv ...` |
| `audible` | function | `progs/pokemon/platform_minios.c:36` | `* voice is audible (noise SFX, sweep zaps), the raw mix estimate plays.  *  * Debug: heartbeat to...` |
| `audio` | function | `progs/pokemon/platform_minios.c:218` | `* PC speaker audio (DOOM-style: sparse syscalls from poll points) * * Per rendered frame, live voice frequencies...` |
| `frames` | function | `progs/pokemon/platform_minios.c:1366` | `* frames (menu bar not on screen yet) and any frame after the          * LCD-off path zeroed the ...` |
| `gain` | function | `progs/pokemon/platform_minios.c:142` | `* timing gain (overshoot is microseconds against millisecond waits).  * Difference-based, so it s...` |
| `gb_platform_get_exit_action` | function | `progs/pokemon/platform_minios.c:1552` | `GBPlatformExitAction gb_platform_get_exit_action(void)` |
| `gb_platform_get_joypad` | function | `progs/pokemon/platform_minios.c:1530` | `uint8_t gb_platform_get_joypad(void)` |
| `gb_platform_get_smooth_lcd_transitions` | function | `progs/pokemon/platform_minios.c:1540` | `bool gb_platform_get_smooth_lcd_transitions(void)` |
| `gb_platform_get_timing_info` | function | `progs/pokemon/platform_minios.c:1523` | `void gb_platform_get_timing_info(GBPlatformTimingInfo *out)` |
| `gb_platform_init` | function | `progs/pokemon/platform_minios.c:1056` | `bool gb_platform_init(int scale)` |
| `gb_platform_poll_events` | function | `progs/pokemon/platform_minios.c:1321` | `bool gb_platform_poll_events(GBContext *ctx)` |
| `gb_platform_present_framebuffer` | function | `progs/pokemon/platform_minios.c:1399` | `void gb_platform_present_framebuffer(const uint32_t *framebuffer)` |
| `gb_platform_register_context` | function | `progs/pokemon/platform_minios.c:1288` | `void gb_platform_register_context(GBContext *ctx)` |
| `gb_platform_render_frame` | function | `progs/pokemon/platform_minios.c:1330` | `void gb_platform_render_frame(const uint32_t *framebuffer)` |
| `gb_platform_render_lcd_off_frame` | function | `progs/pokemon/platform_minios.c:1411` | `void gb_platform_render_lcd_off_frame(void)` |
| `gb_platform_set_benchmark_mode` | function | `progs/pokemon/platform_minios.c:1450` | `void gb_platform_set_benchmark_mode(bool enabled)` |
| `gb_platform_set_debug` | function | `progs/pokemon/platform_minios.c:190` | `void gb_platform_set_debug(bool enabled)` |
| `gb_platform_set_dump_frames` | function | `progs/pokemon/platform_minios.c:1474` | `void gb_platform_set_dump_frames(const char *frames)` |
| `gb_platform_set_dump_present_frames` | function | `progs/pokemon/platform_minios.c:1496` | `void gb_platform_set_dump_present_frames(const char *frames)` |
| `gb_platform_set_input_record_file` | function | `progs/pokemon/platform_minios.c:1460` | `void gb_platform_set_input_record_file(const char *path)` |
| `gb_platform_set_input_script` | function | `progs/pokemon/platform_minios.c:1454` | `bool gb_platform_set_input_script(const char *script)` |
| `gb_platform_set_launcher_return_enabled` | function | `progs/pokemon/platform_minios.c:1548` | `void gb_platform_set_launcher_return_enabled(bool enabled)` |
| `gb_platform_set_persistence_dir` | function | `progs/pokemon/platform_minios.c:1465` | `bool gb_platform_set_persistence_dir(const char *path)` |
| `gb_platform_set_screenshot_prefix` | function | `progs/pokemon/platform_minios.c:1517` | `void gb_platform_set_screenshot_prefix(const char *prefix)` |
| `gb_platform_set_smooth_lcd_transitions` | function | `progs/pokemon/platform_minios.c:1544` | `void gb_platform_set_smooth_lcd_transitions(bool enabled)` |
| `gb_platform_set_title` | function | `progs/pokemon/platform_minios.c:1534` | `void gb_platform_set_title(const char *title)` |
| `gb_platform_shutdown` | function | `progs/pokemon/platform_minios.c:1310` | `void gb_platform_shutdown(void)` |
| `gb_platform_submit_port_frame` | function | `progs/pokemon/platform_minios.c:1556` | `void gb_platform_submit_port_frame(void *user, const GBPortFrame *frame)` |
| `gb_platform_test_audio_concurrency` | function | `progs/pokemon/platform_minios.c:1562` | `bool gb_platform_test_audio_concurrency(uint32_t frames,                                         ...` |
| `gb_platform_test_inject_persistence_fault` | function | `progs/pokemon/platform_minios.c:1571` | `void gb_platform_test_inject_persistence_fault(     GBPersistenceTestTarget target,     GBPersist...` |
| `gb_platform_vsync` | function | `progs/pokemon/platform_minios.c:1433` | `void gb_platform_vsync(uint32_t frame_cycles)` |
| `gb_voice_in_range` | function | `progs/pokemon/platform_minios.c:306` | `static bool gb_voice_in_range(unsigned f)` |
| `gb_voice_t` | struct | `progs/pokemon/platform_minios.c:301` | `` |
| `menu` | function | `progs/pokemon/platform_minios.c:571` | `* FILE menu (no Nuklear on purpose) * * A 16 px menu bar lives in the top margin the 2x GB image never touches * (it...` |
| `menu_activate` | function | `progs/pokemon/platform_minios.c:742` | `static void menu_activate(int it)` |
| `menu_do_load` | function | `progs/pokemon/platform_minios.c:723` | `static void menu_do_load(void)` |
| `menu_do_save` | function | `progs/pokemon/platform_minios.c:707` | `static void menu_do_save(void)` |
| `menu_draw` | function | `progs/pokemon/platform_minios.c:670` | `static void menu_draw(void)` |
| `menu_fill` | function | `progs/pokemon/platform_minios.c:632` | `static void menu_fill(int x0, int y0, int w, int h, uint8_t idx)` |
| `menu_item_at` | function | `progs/pokemon/platform_minios.c:700` | `static int menu_item_at(int lx, int ly)` |
| `menu_osd` | function | `progs/pokemon/platform_minios.c:664` | `static void menu_osd(const char *s)` |
| `menu_text` | function | `progs/pokemon/platform_minios.c:645` | `static void menu_text(int x, int y, const char *s, uint8_t fg)` |
| `minios_audio_play` | function | `progs/pokemon/platform_minios.c:330` | `static void minios_audio_play(const gb_voice_t *v, bool pcm_audible,                             ...` |
| `minios_audio_sample` | function | `progs/pokemon/platform_minios.c:262` | `static void minios_audio_sample(GBContext *ctx, int16_t left, int16_t right)` |
| `minios_autosave` | function | `progs/pokemon/platform_minios.c:1222` | `static void minios_autosave(uint32_t now)` |
| `minios_fast_forward` | function | `progs/pokemon/platform_minios.c:1208` | `static inline bool minios_fast_forward(void)` |
| `minios_legacy_path` | function | `progs/pokemon/platform_minios.c:1097` | `static void minios_legacy_path(char *out, size_t n, const GBContext *ctx,                        ...` |
| `minios_legacy_state_path` | function | `progs/pokemon/platform_minios.c:1217` | `static void minios_legacy_state_path(char *out, size_t n, const GBContext *ctx)` |
| `minios_load_battery_ram` | function | `progs/pokemon/platform_minios.c:1132` | `static bool minios_load_battery_ram(GBContext *ctx, const char *rom_name,                        ...` |
| `minios_load_helper` | function | `progs/pokemon/platform_minios.c:1103` | `static bool minios_load_helper(const char *path, void *data, size_t size,                        ...` |
| `minios_load_rtc_data` | function | `progs/pokemon/platform_minios.c:1157` | `static bool minios_load_rtc_data(GBContext *ctx, const char *rom_name,                           ...` |
| `minios_persist_path` | function | `progs/pokemon/platform_minios.c:1088` | `static void minios_persist_path(char *out, size_t n, const GBContext *ctx,                       ...` |
| `minios_save_battery_ram` | function | `progs/pokemon/platform_minios.c:1147` | `static bool minios_save_battery_ram(GBContext *ctx, const char *rom_name,                        ...` |
| `minios_save_helper` | function | `progs/pokemon/platform_minios.c:1121` | `static bool minios_save_helper(const char *path, const void *data, size_t size)` |
| `minios_save_rtc_data` | function | `progs/pokemon/platform_minios.c:1170` | `static bool minios_save_rtc_data(GBContext *ctx, const char *rom_name,                           ...` |
| `minios_state_path` | function | `progs/pokemon/platform_minios.c:1212` | `static void minios_state_path(char *out, size_t n, const GBContext *ctx)` |
| `pokemon_art_draw` | function | `progs/pokemon/platform_minios.c:925` | `static void pokemon_art_draw(void)` |
| `pokemon_art_draw_one` | function | `progs/pokemon/platform_minios.c:887` | `static void pokemon_art_draw_one(const unsigned char *rgb, int sw, int sh,                       ...` |
| `pokemon_art_load` | function | `progs/pokemon/platform_minios.c:869` | `static void pokemon_art_load(void)` |
| `pokemon_art_load_one` | function | `progs/pokemon/platform_minios.c:844` | `static int pokemon_art_load_one(const char *path, unsigned char **rgb,                           ...` |
| `poll_hotkeys` | function | `progs/pokemon/platform_minios.c:1236` | `static void poll_hotkeys(void)` |
| `poll_keyboard` | function | `progs/pokemon/platform_minios.c:416` | `static void poll_keyboard(void)` |
| `poll_menu` | function | `progs/pokemon/platform_minios.c:776` | `static void poll_menu(void)` |
| `push_332_palette` | function | `progs/pokemon/platform_minios.c:455` | `static void push_332_palette(void)` |
| `px_to_idx` | function | `progs/pokemon/platform_minios.c:956` | `static uint8_t px_to_idx(uint32_t pixel)` |
| `rebuild_joypad` | function | `progs/pokemon/platform_minios.c:402` | `static void rebuild_joypad(void)` |
| `sample_apu_voices` | function | `progs/pokemon/platform_minios.c:310` | `static void sample_apu_voices(gb_voice_t *v)` |
| `sys_gfx_title` | function | `progs/pokemon/platform_minios.c:111` | `static long sys_gfx_title(const char *t)` |
| `sys_kbd` | function | `progs/pokemon/platform_minios.c:75` | `static long sys_kbd(void)` |
| `sys_kbd_raw` | function | `progs/pokemon/platform_minios.c:99` | `static long sys_kbd_raw(int on)` |
| `sys_mouse` | function | `progs/pokemon/platform_minios.c:87` | `static long sys_mouse(int *xybw)` |
| `sys_nk_frame` | function | `progs/pokemon/platform_minios.c:81` | `static long sys_nk_frame(int *origin)` |
| `sys_palette` | function | `progs/pokemon/platform_minios.c:105` | `static long sys_palette(const unsigned char *pal)` |
| `sys_pcm2_close` | function | `progs/pokemon/platform_minios.c:135` | `static void sys_pcm2_close(void)` |
| `sys_pcm2_open` | function | `progs/pokemon/platform_minios.c:123` | `static long sys_pcm2_open(long flags)` |
| `sys_pcm2_write` | function | `progs/pokemon/platform_minios.c:129` | `static long sys_pcm2_write(const void *buf, long len)` |
| `sys_tone` | function | `progs/pokemon/platform_minios.c:117` | `static long sys_tone(unsigned f)` |
| `sys_vga_mode` | function | `progs/pokemon/platform_minios.c:93` | `static long sys_vga_mode(int on)` |
| `ui_fringe_dirty` | function | `progs/pokemon/platform_minios.c:620` | `static bool ui_fringe_dirty(uint32_t now)` |
| `ui_fringe_sync` | function | `progs/pokemon/platform_minios.c:626` | `static void ui_fringe_sync(uint32_t now)` |
| `upload_frame` | function | `progs/pokemon/platform_minios.c:975` | `static void upload_frame(const uint32_t *framebuffer)` |
| `Cbuf_AddText` | function | `progs/quake2generic/q2generic_minios.c:102` | `extern void Cbuf_AddText(char *text);` |
| `MINIOS_DOOM_BACKBUF_ADDR` | function | `progs/quake2generic/q2generic_minios.c:4` | `* MINIOS_DOOM_BACKBUF_ADDR (minios_abi.h);` |
| `MINIOS_GFX_BUF_GAME` | function | `progs/quake2generic/q2generic_minios.c:5` | `* MINIOS_SYS_GFX_PRESENT with MINIOS_GFX_BUF_GAME (211 stays as a kernel  * compat alias) and the...` |
| `Q2G_BACKBUF` | macro | `progs/quake2generic/q2generic_minios.c:78` | `#define Q2G_BACKBUF` |
| `Q2G_FB_H` | macro | `progs/quake2generic/q2generic_minios.c:22` | `#define Q2G_FB_H` |
| `Q2G_FB_W` | macro | `progs/quake2generic/q2generic_minios.c:21` | `#define Q2G_FB_W` |
| `QG_CaptureMouse` | function | `progs/quake2generic/q2generic_minios.c:168` | `void QG_CaptureMouse(void)` |
| `QG_GetMouseDiff` | function | `progs/quake2generic/q2generic_minios.c:154` | `void QG_GetMouseDiff(int *dx, int *dy)` |
| `QG_Milliseconds` | function | `progs/quake2generic/q2generic_minios.c:385` | `int QG_Milliseconds(void)` |
| `QG_Mkdir` | function | `progs/quake2generic/q2generic_minios.c:175` | `void QG_Mkdir(const char *path)` |
| `QG_ReleaseMouse` | function | `progs/quake2generic/q2generic_minios.c:172` | `void QG_ReleaseMouse(void)` |
| `SWimp_AppActivate` | function | `progs/quake2generic/q2generic_minios.c:381` | `void SWimp_AppActivate(qboolean active)` |
| `SWimp_BeginFrame` | function | `progs/quake2generic/q2generic_minios.c:349` | `void SWimp_BeginFrame(float camera_separation)` |
| `SWimp_EndFrame` | function | `progs/quake2generic/q2generic_minios.c:352` | `void SWimp_EndFrame(void)` |
| `SWimp_Init` | function | `progs/quake2generic/q2generic_minios.c:337` | `int SWimp_Init(void *hInstance, void *wndProc)` |
| `SWimp_SetMode` | function | `progs/quake2generic/q2generic_minios.c:320` | `rserr_t SWimp_SetMode(int *pwidth, int *pheight, int mode, qboolean fullscreen)` |
| `SWimp_SetPalette` | function | `progs/quake2generic/q2generic_minios.c:310` | `void SWimp_SetPalette(const unsigned char *palette)` |
| `SWimp_Shutdown` | function | `progs/quake2generic/q2generic_minios.c:346` | `void SWimp_Shutdown(void)` |
| `Sys_Quit` | function | `progs/quake2generic/q2generic_minios.c:99` | `extern void Sys_Quit(void);` |
| `extended_to_q2key` | function | `progs/quake2generic/q2generic_minios.c:262` | `static unsigned char extended_to_q2key(unsigned char sc)` |
| `kbd_poll` | function | `progs/quake2generic/q2generic_minios.c:280` | `static void kbd_poll(void)` |
| `main` | function | `progs/quake2generic/q2generic_minios.c:389` | `int main(int argc, char **argv)` |
| `q2g_parse_autoframes` | function | `progs/quake2generic/q2generic_minios.c:121` | `static void q2g_parse_autoframes(int argc, char **argv)` |
| `q2g_parse_windowed` | function | `progs/quake2generic/q2generic_minios.c:86` | `static void q2g_parse_windowed(int argc, char **argv)` |
| `q2snd_probe` | function | `progs/quake2generic/q2generic_minios.c:106` | `extern int q2snd_probe(void);` |
| `scancode_to_q2key` | function | `progs/quake2generic/q2generic_minios.c:179` | `static unsigned char scancode_to_q2key(unsigned char raw)` |
| `sys_doom_frame` | function | `progs/quake2generic/q2generic_minios.c:54` | `static long sys_doom_frame(void)` |
| `sys_gfx_zoom` | function | `progs/quake2generic/q2generic_minios.c:72` | `static long sys_gfx_zoom(long mode)` |
| `sys_kbd` | function | `progs/quake2generic/q2generic_minios.c:30` | `static long sys_kbd(void)` |
| `sys_kbd_raw` | function | `progs/quake2generic/q2generic_minios.c:42` | `static long sys_kbd_raw(int on)` |
| `sys_mouse` | function | `progs/quake2generic/q2generic_minios.c:60` | `static long sys_mouse(int *buf)` |
| `sys_palette` | function | `progs/quake2generic/q2generic_minios.c:36` | `static long sys_palette(const unsigned char *pal)` |
| `sys_set_title` | function | `progs/quake2generic/q2generic_minios.c:66` | `static long sys_set_title(const char *t)` |
| `sys_vga_mode` | function | `progs/quake2generic/q2generic_minios.c:48` | `static long sys_vga_mode(int on)` |
| `Q2SND_AHEAD` | macro | `progs/quake2generic/snddma_minios.c:54` | `#define Q2SND_AHEAD` |
| `Q2SND_BUF_BYTES` | macro | `progs/quake2generic/snddma_minios.c:56` | `#define Q2SND_BUF_BYTES` |
| `Q2SND_RATE` | macro | `progs/quake2generic/snddma_minios.c:48` | `#define Q2SND_RATE` |
| `Q2SND_SAMPLES` | macro | `progs/quake2generic/snddma_minios.c:49` | `#define Q2SND_SAMPLES` |
| `Q2SND_SILENCE` | macro | `progs/quake2generic/snddma_minios.c:50` | `#define Q2SND_SILENCE` |
| `SNDDMA_BeginPainting` | function | `progs/quake2generic/snddma_minios.c:202` | `void SNDDMA_BeginPainting(void)` |
| `SNDDMA_GetDMAPos` | function | `progs/quake2generic/snddma_minios.c:182` | `int SNDDMA_GetDMAPos(void)` |
| `SNDDMA_Init` | function | `progs/quake2generic/snddma_minios.c:138` | `qboolean SNDDMA_Init(void)` |
| `SNDDMA_Shutdown` | function | `progs/quake2generic/snddma_minios.c:190` | `void SNDDMA_Shutdown(void)` |
| `SNDDMA_Submit` | function | `progs/quake2generic/snddma_minios.c:205` | `void SNDDMA_Submit(void)` |
| `q2_dma_push` | function | `progs/quake2generic/snddma_minios.c:104` | `static int q2_dma_push(int end)` |
| `q2snd_probe` | function | `progs/quake2generic/snddma_minios.c:222` | `int q2snd_probe(void)` |
| `sys_pcm2_close` | function | `progs/quake2generic/snddma_minios.c:83` | `static void sys_pcm2_close(void)` |
| `sys_pcm2_open` | function | `progs/quake2generic/snddma_minios.c:67` | `static long sys_pcm2_open(long flags)` |
| `sys_pcm2_write` | function | `progs/quake2generic/snddma_minios.c:75` | `static long sys_pcm2_write(const void *buf, long len)` |
| `sys_time_ms` | function | `progs/quake2generic/snddma_minios.c:89` | `static long sys_time_ms(void)` |
| `AES_AFFINE_C` | macro | `progs/src/aes.c:53` | `#define AES_AFFINE_C` |
| `AES_BLOCK` | macro | `progs/src/aes.c:44` | `#define AES_BLOCK` |
| `AES_EXIT_FAIL` | macro | `progs/src/aes.c:61` | `#define AES_EXIT_FAIL` |
| `AES_HDR_SIZE` | macro | `progs/src/aes.c:42` | `#define AES_HDR_SIZE` |
| `AES_KEY_BYTES` | macro | `progs/src/aes.c:45` | `#define AES_KEY_BYTES` |
| `AES_MAGIC0` | macro | `progs/src/aes.c:38` | `#define AES_MAGIC0` |
| `AES_MAGIC1` | macro | `progs/src/aes.c:39` | `#define AES_MAGIC1` |
| `AES_MAGIC2` | macro | `progs/src/aes.c:40` | `#define AES_MAGIC2` |
| `AES_MAGIC3` | macro | `progs/src/aes.c:41` | `#define AES_MAGIC3` |
| `AES_NONCE_BYTES` | macro | `progs/src/aes.c:46` | `#define AES_NONCE_BYTES` |
| `AES_POLY` | macro | `progs/src/aes.c:52` | `#define AES_POLY` |
| `AES_RCON_PAD` | macro | `progs/src/aes.c:54` | `#define AES_RCON_PAD` |
| `AES_RCON_SIZE` | macro | `progs/src/aes.c:50` | `#define AES_RCON_SIZE` |
| `AES_RK_LEN` | macro | `progs/src/aes.c:48` | `#define AES_RK_LEN` |
| `AES_ROUNDS` | macro | `progs/src/aes.c:47` | `#define AES_ROUNDS` |
| `AES_SBOX_SIZE` | macro | `progs/src/aes.c:49` | `#define AES_SBOX_SIZE` |
| `AES_SEEK_END` | macro | `progs/src/aes.c:59` | `#define AES_SEEK_END` |
| `GF` | function | `progs/src/aes.c:8` | `* generated procedurally from the GF(2^8) multiplicative inverse plus the * FIPS-197 affine transform, so the file...` |
| `HEX_KEY_LEN` | macro | `progs/src/aes.c:56` | `#define HEX_KEY_LEN` |
| `HEX_NONCE_LEN` | macro | `progs/src/aes.c:57` | `#define HEX_NONCE_LEN` |
| `aes_add_round_key` | function | `progs/src/aes.c:209` | `static void aes_add_round_key(int round)` |
| `aes_cipher` | function | `progs/src/aes.c:248` | `static void aes_cipher(void)` |
| `aes_ctr_crypt` | function | `progs/src/aes.c:273` | `static void aes_ctr_crypt(char *data, int len)` |
| `aes_gf_mul` | function | `progs/src/aes.c:130` | `static int aes_gf_mul(int a, int b)` |
| `aes_has` | function | `progs/src/aes.c:96` | `static int aes_has(const char *s, const char *needle)` |
| `aes_hdr_get` | function | `progs/src/aes.c:299` | `static int aes_hdr_get(char *h)` |
| `aes_hdr_put` | function | `progs/src/aes.c:288` | `static void aes_hdr_put(char *h, int size)` |
| `aes_init_tables` | function | `progs/src/aes.c:155` | `static void aes_init_tables(void)` |
| `aes_iv_increment` | function | `progs/src/aes.c:263` | `static void aes_iv_increment(void)` |
| `aes_key_expand` | function | `progs/src/aes.c:174` | `static void aes_key_expand(const int *key)` |
| `aes_mix_columns` | function | `progs/src/aes.c:228` | `static void aes_mix_columns(void)` |
| `aes_parse_hex` | function | `progs/src/aes.c:117` | `static int aes_parse_hex(const char *s, int want, int *out)` |
| `aes_read_all` | function | `progs/src/aes.c:69` | `static char *aes_read_all(const char *name, int *len)` |
| `aes_rotl8` | function | `progs/src/aes.c:148` | `static int aes_rotl8(int x, int n)` |
| `aes_run` | function | `progs/src/aes.c:312` | `static int aes_run(int decode, const char *keyhex, const char *noncehex,                    const...` |
| `aes_shift_rows` | function | `progs/src/aes.c:220` | `static void aes_shift_rows(void)` |
| `aes_sub_bytes` | function | `progs/src/aes.c:215` | `static void aes_sub_bytes(void)` |
| `aes_tool_name` | function | `progs/src/aes.c:307` | `static const char *aes_tool_name(int decode)` |
| `aes_write_all` | function | `progs/src/aes.c:86` | `static int aes_write_all(const char *name, char *data, int len)` |
| `aes_xtime` | function | `progs/src/aes.c:142` | `static int aes_xtime(int x)` |
| `fclose` | function | `progs/src/aes.c:29` | `int fclose();` |
| `fopen` | function | `progs/src/aes.c:28` | `void *fopen();` |
| `fread` | function | `progs/src/aes.c:30` | `int fread();` |
| `free` | function | `progs/src/aes.c:36` | `void free();` |
| `fseek` | function | `progs/src/aes.c:32` | `int fseek();` |
| `ftell` | function | `progs/src/aes.c:33` | `int ftell();` |
| `fwrite` | function | `progs/src/aes.c:31` | `int fwrite();` |
| `hex_val` | function | `progs/src/aes.c:110` | `static int hex_val(int c)` |
| `main` | function | `progs/src/aes.c:384` | `int main(int argc, char **argv)` |
| `malloc` | function | `progs/src/aes.c:35` | `void *malloc();` |
| `putchar` | function | `progs/src/aes.c:25` | `int putchar();` |
| `rewind` | function | `progs/src/aes.c:34` | `void rewind();` |
| `strcmp` | function | `progs/src/aes.c:26` | `int strcmp();` |
| `strlen` | function | `progs/src/aes.c:27` | `int strlen();` |
| `as_atou` | function | `progs/src/aslr.c:59` | `static unsigned long as_atou(const char *s)` |
| `as_execve` | function | `progs/src/aslr.c:40` | `static void as_execve(const char *path, const char **argv)` |
| `as_exit` | function | `progs/src/aslr.c:35` | `static void as_exit(long code)` |
| `as_fail` | function | `progs/src/aslr.c:74` | `static void as_fail(int step)` |
| `as_mmap` | function | `progs/src/aslr.c:18` | `static long as_mmap(void)` |
| `as_putu` | function | `progs/src/aslr.c:47` | `static void as_putu(unsigned long v)` |
| `as_rsp` | function | `progs/src/aslr.c:68` | `static unsigned long as_rsp(void)` |
| `as_sc` | function | `progs/src/aslr.c:10` | `static long as_sc(long n, long a1, long a2, long a3)` |
| `as_write` | function | `progs/src/aslr.c:31` | `static void as_write(const char *s, unsigned long len)` |
| `lmain` | function | `progs/src/aslr.c:82` | `int lmain(long argc, char **argv)` |
| `audio_get_volume` | function | `progs/src/audio.c:56` | `unsigned audio_get_volume(void)` |
| `audio_init` | function | `progs/src/audio.c:27` | `int audio_init(void)` |
| `audio_pcm_close` | function | `progs/src/audio.c:48` | `void audio_pcm_close(void)` |
| `audio_pcm_open` | function | `progs/src/audio.c:35` | `int audio_pcm_open(unsigned rate, unsigned channels, unsigned format)` |
| `audio_pcm_pump` | function | `progs/src/audio.c:44` | `void audio_pcm_pump(void)` |
| `audio_pcm_submit` | function | `progs/src/audio.c:40` | `int audio_pcm_submit(const void *buf, unsigned len)` |
| `audio_sb16_present` | function | `progs/src/audio.c:60` | `int audio_sb16_present(void)` |
| `audio_set_volume` | function | `progs/src/audio.c:52` | `void audio_set_volume(unsigned volume)` |
| `audio_stream_close` | function | `progs/src/audio.c:68` | `void audio_stream_close(int id)` |
| `audio_stream_open` | function | `progs/src/audio.c:64` | `int audio_stream_open(void)` |
| `audio_stream_submit` | function | `progs/src/audio.c:72` | `int audio_stream_submit(int id, const void *buf, unsigned len)` |
| `audio_stream_volume` | function | `progs/src/audio.c:76` | `void audio_stream_volume(int id, unsigned char vol)` |
| `audio_tone` | function | `progs/src/audio.c:31` | `void audio_tone(unsigned freq)` |
| `syscall0` | function | `progs/src/audio.c:21` | `static long syscall0(long n)` |
| `syscall1` | function | `progs/src/audio.c:3` | `static long syscall1(long n, long a1)` |
| `syscall2` | function | `progs/src/audio.c:9` | `static long syscall2(long n, long a1, long a2)` |
| `syscall3` | function | `progs/src/audio.c:15` | `static long syscall3(long n, long a1, long a2, long a3)` |
| `bn_exit` | function | `progs/src/burn.c:31` | `static void bn_exit(long code)` |
| `bn_fail` | function | `progs/src/burn.c:48` | `static void bn_fail(void)` |
| `bn_mmap` | function | `progs/src/burn.c:14` | `static long bn_mmap(unsigned long len)` |
| `bn_putu` | function | `progs/src/burn.c:36` | `static void bn_putu(unsigned long v)` |
| `bn_sc` | function | `progs/src/burn.c:6` | `static long bn_sc(long n, long a1, long a2, long a3)` |
| `bn_write` | function | `progs/src/burn.c:27` | `static void bn_write(const char *s, unsigned long len)` |
| `lmain` | function | `progs/src/burn.c:53` | `int lmain(void)` |
| `CP_BUF_SIZE` | macro | `progs/src/cp.c:7` | `#define CP_BUF_SIZE` |
| `CP_EXIT_FAIL` | macro | `progs/src/cp.c:8` | `#define CP_EXIT_FAIL` |
| `fclose` | function | `progs/src/cp.c:3` | `int fclose();` |
| `fopen` | function | `progs/src/cp.c:2` | `void *fopen();` |
| `fread` | function | `progs/src/cp.c:4` | `int fread();` |
| `fwrite` | function | `progs/src/cp.c:5` | `int fwrite();` |
| `main` | function | `progs/src/cp.c:10` | `int main(int argc, char **argv)` |
| `printf` | function | `progs/src/cp.c:1` | `int printf();` |
| `_start` | function | `progs/src/cpl.c:16` | `void _start(void)` |
| `exit_now` | function | `progs/src/cpl.c:12` | `static void exit_now(long code)` |
| `read_cpl` | function | `progs/src/cpl.c:6` | `static long read_cpl(void)` |
| `ex_exit` | function | `progs/src/execho.c:24` | `static void ex_exit(long code)` |
| `ex_fail` | function | `progs/src/execho.c:29` | `static void ex_fail(int step)` |
| `ex_write` | function | `progs/src/execho.c:20` | `static void ex_write(const char *s, unsigned long len)` |
| `lmain` | function | `progs/src/execho.c:37` | `int lmain(void)` |
| `path` | function | `progs/src/execho.c:7` | `* execs a ghost path (must fail -2, exits 42). The parent checks  * both wait4 results with Linux...` |
| `program` | function | `progs/src/execho.c:5` | `* * Proves the UNIX process composition the kernel lacked: a child * produced by fork replaces its image with execve...` |
| `et_exit` | function | `progs/src/execthr.c:19` | `static void et_exit(long code)` |
| `et_sc` | function | `progs/src/execthr.c:11` | `static long et_sc(long n, long a1, long a2, long a3)` |
| `et_thread` | function | `progs/src/execthr.c:27` | `static void et_thread(void)` |
| `lmain` | function | `progs/src/execthr.c:33` | `int lmain(void)` |
| `fib` | function | `progs/src/fib.c:1` | `int fib(int n)` |
| `main` | function | `progs/src/fib.c:6` | `int main(void)` |
| `SYS_close` | macro | `progs/src/forktest.c:32` | `#define SYS_close` |
| `SYS_exit` | macro | `progs/src/forktest.c:36` | `#define SYS_exit` |
| `SYS_fork` | macro | `progs/src/forktest.c:35` | `#define SYS_fork` |
| `SYS_pipe` | macro | `progs/src/forktest.c:33` | `#define SYS_pipe` |
| `SYS_read` | macro | `progs/src/forktest.c:30` | `#define SYS_read` |
| `SYS_wait4` | macro | `progs/src/forktest.c:37` | `#define SYS_wait4` |
| `SYS_write` | macro | `progs/src/forktest.c:31` | `#define SYS_write` |
| `SYS_yield` | macro | `progs/src/forktest.c:34` | `#define SYS_yield` |
| `_start` | function | `progs/src/forktest.c:56` | `void _start(void)` |
| `fx_exit` | function | `progs/src/forktest.c:51` | `static void fx_exit(long code)` |
| `fx_strlen` | function | `progs/src/forktest.c:41` | `static unsigned long fx_strlen(const char *s)` |
| `fx_syscall6` | function | `progs/src/forktest.c:17` | `static long fx_syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6)` |
| `fx_write` | function | `progs/src/forktest.c:47` | `static void fx_write(const char *s)` |
| `this` | function | `progs/src/forktest.c:115` | `* this (and the child's closes must survive below). */ fx_syscall6(SYS_close, pfd[1], 0, 0, 0, 0, 0);` |
| `FP_ITERS` | macro | `progs/src/fptest.c:38` | `#define FP_ITERS` |
| `fp_slot_t` | struct | `progs/src/fptest.c:56` | `` |
| `gettid` | function | `progs/src/fptest.c:21` | `* * The same run smokes gettid (Phase 0.4: the two workers must observe * distinct tids, never the constant 1) and...` |
| `main` | function | `progs/src/fptest.c:148` | `int main(void)` |
| `raw_getrandom` | function | `progs/src/fptest.c:52` | `static long raw_getrandom(void *buf, unsigned long n)` |
| `raw_gettid` | function | `progs/src/fptest.c:48` | `static long raw_gettid(void)` |
| `read_mxcsr` | function | `progs/src/fptest.c:42` | `static unsigned int read_mxcsr(void)` |
| `stack_align_canary` | function | `progs/src/fptest.c:78` | `static void stack_align_canary(void)` |
| `worker` | function | `progs/src/fptest.c:84` | `static void *worker(void *p)` |
| `FREEDOM_ATTR_MAX` | macro | `progs/src/freedom.c:81` | `#define FREEDOM_ATTR_MAX` |
| `FREEDOM_BUF` | macro | `progs/src/freedom.c:76` | `#define FREEDOM_BUF` |
| `FREEDOM_CHUNK_MAX` | macro | `progs/src/freedom.c:77` | `#define FREEDOM_CHUNK_MAX` |
| `FREEDOM_CSS_BUF` | macro | `progs/src/freedom.c:79` | `#define FREEDOM_CSS_BUF` |
| `FREEDOM_CSS_MAX` | macro | `progs/src/freedom.c:78` | `#define FREEDOM_CSS_MAX` |
| `FREEDOM_DOM_BUF` | macro | `progs/src/freedom.c:80` | `#define FREEDOM_DOM_BUF` |
| `FREEDOM_HDR_MAX` | macro | `progs/src/freedom.c:75` | `#define FREEDOM_HDR_MAX` |
| `FREEDOM_HOPS_MAX` | macro | `progs/src/freedom.c:74` | `#define FREEDOM_HOPS_MAX` |
| `FREEDOM_LINE_MAX` | macro | `progs/src/freedom.c:82` | `#define FREEDOM_LINE_MAX` |
| `append` | function | `progs/src/freedom.c:166` | `static int append(char *dst, int pos, char *src, int cap)` |
| `atoi` | function | `progs/src/freedom.c:151` | `static int atoi(char *s)` |
| `body_byte` | function | `progs/src/freedom.c:631` | `static void body_byte(int c)` |
| `ci_eq` | function | `progs/src/freedom.c:193` | `static int ci_eq(char *a, char *b)` |
| `ci_index` | function | `progs/src/freedom.c:203` | `static int ci_index(char *s, char *needle)` |
| `ci_lower` | function | `progs/src/freedom.c:176` | `static int ci_lower(int c)` |
| `ci_starts` | function | `progs/src/freedom.c:182` | `static int ci_starts(char *s, char *pre)` |
| `classify_tag` | function | `progs/src/freedom.c:546` | `static void classify_tag(void)` |
| `close` | function | `progs/src/freedom.c:56` | `int close(int fd);` |
| `connect` | function | `progs/src/freedom.c:53` | `int connect(int fd, void *addr, int addrlen);` |
| `css_append` | function | `progs/src/freedom.c:483` | `static void css_append(char *s, int n)` |
| `css_line` | function | `progs/src/freedom.c:489` | `static void css_line(char *s)` |
| `curlfree` | function | `progs/src/freedom.c:4` | `* spirit of curlfree (http.c + htmlfilter.c): a bounded header phase, * Content-Length or EOF body reading...` |
| `dom_append` | function | `progs/src/freedom.c:494` | `static void dom_append(char *s, int n)` |
| `dom_nl` | function | `progs/src/freedom.c:504` | `static void dom_nl(void)` |
| `dom_space` | function | `progs/src/freedom.c:500` | `static void dom_space(void)` |
| `fetch` | function | `progs/src/freedom.c:860` | `static int fetch(char *host, char *path, int port)` |
| `fetch_css` | function | `progs/src/freedom.c:1031` | `static void fetch_css(char *host, char *path)` |
| `has_scheme` | function | `progs/src/freedom.c:226` | `static int has_scheme(char *s)` |
| `head_line` | function | `progs/src/freedom.c:796` | `static void head_line(char *line)` |
| `is_void_tag` | function | `progs/src/freedom.c:534` | `static int is_void_tag(void)` |

Next: [SYMBOLS_p22.md](SYMBOLS_p22.md)
