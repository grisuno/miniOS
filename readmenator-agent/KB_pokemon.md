# Subsystem: pokemon

## progs/pokemon/fetch.sh
- Layer: utility
- Doc: fetch.sh - clone the gb-recompiled tool into progs/pokemon/upstream.  The upstream project ships the recompiler + runtim
- Language: sh

## progs/pokemon/platform_minios.c
- Layer: data_access
- Language: c
- Symbols:
  - `gb_voice_t` (struct, line 237)
  - `audible` (function, line 32) `* audible (noise SFX, sweep zaps), the raw mix estimate is played.
 *
 * Debug: heartbeat to stde...`
  - `sys_kbd` (function, line 71) `static long sys_kbd(void)`
  - `sys_nk_frame` (function, line 77) `static long sys_nk_frame(int *origin)`
  - `sys_mouse` (function, line 83) `static long sys_mouse(int *xybw)`
  - `sys_vga_mode` (function, line 89) `static long sys_vga_mode(int on)`
  - `sys_kbd_raw` (function, line 95) `static long sys_kbd_raw(int on)`
  - `sys_palette` (function, line 101) `static long sys_palette(const unsigned char *pal)`
  - `sys_gfx_title` (function, line 107) `static long sys_gfx_title(const char *t)`
  - `sys_tone` (function, line 113) `static long sys_tone(unsigned f)`
  - `gb_platform_set_debug` (function, line 153) `void gb_platform_set_debug(bool enabled)`
  - `_dl_argv` (function, line 160) `* usable _dl_argv (it bound to unrelated storage and strcmp faulted).
 * DO NOT reintroduce argv ...`
  - `minios_audio_sample` (function, line 211) `static void minios_audio_sample(GBContext *ctx, int16_t left, int16_t right)`
  - `gb_voice_in_range` (function, line 242) `static bool gb_voice_in_range(unsigned f)`
  - `sample_apu_voices` (function, line 246) `static void sample_apu_voices(gb_voice_t *v)`
  - `hold_tone` (function, line 266) `static void hold_tone(unsigned freq, unsigned ms)`
  - `minios_audio_play` (function, line 274) `static void minios_audio_play(const gb_voice_t *v, bool pcm_audible,
                            ...`
  - `minios_audio_frame` (function, line 309) `static void minios_audio_frame(void)`
  - `rebuild_joypad` (function, line 337) `static void rebuild_joypad(void)`
  - `poll_keyboard` (function, line 351) `static void poll_keyboard(void)`
  - `push_332_palette` (function, line 390) `static void push_332_palette(void)`
  - `menu_fill` (function, line 546) `static void menu_fill(int x0, int y0, int w, int h, uint8_t idx)`
  - `menu_text` (function, line 559) `static void menu_text(int x, int y, const char *s, uint8_t fg)`
  - `menu_osd` (function, line 578) `static void menu_osd(const char *s)`
  - `menu_draw` (function, line 584) `static void menu_draw(void)`
  - `menu_item_at` (function, line 614) `static int menu_item_at(int lx, int ly)`
  - `menu_do_save` (function, line 621) `static void menu_do_save(void)`
  - `menu_do_load` (function, line 637) `static void menu_do_load(void)`
  - `menu_activate` (function, line 656) `static void menu_activate(int it)`
  - `poll_menu` (function, line 690) `static void poll_menu(void)`
  - `pokemon_art_load_one` (function, line 758) `static int pokemon_art_load_one(const char *path, unsigned char **rgb,
                          ...`
  - `pokemon_art_load` (function, line 783) `static void pokemon_art_load(void)`
  - `pokemon_art_draw_one` (function, line 801) `static void pokemon_art_draw_one(const unsigned char *rgb, int sw, int sh,
                      ...`
  - `pokemon_art_draw` (function, line 839) `static void pokemon_art_draw(void)`
  - `upload_frame` (function, line 850) `static void upload_frame(const uint32_t *framebuffer)`
  - `gb_platform_init` (function, line 919) `bool gb_platform_init(int scale)`
  - `minios_persist_path` (function, line 950) `static void minios_persist_path(char *out, size_t n, const GBContext *ctx,
                      ...`
  - `minios_legacy_path` (function, line 959) `static void minios_legacy_path(char *out, size_t n, const GBContext *ctx,
                       ...`
  - `minios_load_helper` (function, line 965) `static bool minios_load_helper(const char *path, void *data, size_t size,
                       ...`
  - `minios_save_helper` (function, line 983) `static bool minios_save_helper(const char *path, const void *data, size_t size)`
  - `minios_load_battery_ram` (function, line 994) `static bool minios_load_battery_ram(GBContext *ctx, const char *rom_name,
                       ...`
  - `minios_save_battery_ram` (function, line 1009) `static bool minios_save_battery_ram(GBContext *ctx, const char *rom_name,
                       ...`
  - `minios_load_rtc_data` (function, line 1019) `static bool minios_load_rtc_data(GBContext *ctx, const char *rom_name,
                          ...`
  - `minios_save_rtc_data` (function, line 1032) `static bool minios_save_rtc_data(GBContext *ctx, const char *rom_name,
                          ...`
  - `minios_fast_forward` (function, line 1070) `static inline bool minios_fast_forward(void)`
  - `minios_state_path` (function, line 1074) `static void minios_state_path(char *out, size_t n, const GBContext *ctx)`
  - `minios_legacy_state_path` (function, line 1079) `static void minios_legacy_state_path(char *out, size_t n, const GBContext *ctx)`
  - `minios_autosave` (function, line 1084) `static void minios_autosave(uint32_t now)`
  - `poll_hotkeys` (function, line 1098) `static void poll_hotkeys(void)`
  - `gb_platform_register_context` (function, line 1150) `void gb_platform_register_context(GBContext *ctx)`
  - `gb_platform_shutdown` (function, line 1166) `void gb_platform_shutdown(void)`
  - `gb_platform_poll_events` (function, line 1173) `bool gb_platform_poll_events(GBContext *ctx)`
  - `gb_platform_render_frame` (function, line 1182) `void gb_platform_render_frame(const uint32_t *framebuffer)`
  - `gb_platform_present_framebuffer` (function, line 1240) `void gb_platform_present_framebuffer(const uint32_t *framebuffer)`
  - `gb_platform_render_lcd_off_frame` (function, line 1246) `void gb_platform_render_lcd_off_frame(void)`
  - `gb_platform_vsync` (function, line 1263) `void gb_platform_vsync(uint32_t frame_cycles)`
  - `gb_platform_set_benchmark_mode` (function, line 1284) `void gb_platform_set_benchmark_mode(bool enabled)`
  - `gb_platform_set_input_script` (function, line 1288) `bool gb_platform_set_input_script(const char *script)`
  - `gb_platform_set_input_record_file` (function, line 1294) `void gb_platform_set_input_record_file(const char *path)`
  - `gb_platform_set_persistence_dir` (function, line 1299) `bool gb_platform_set_persistence_dir(const char *path)`
  - `gb_platform_set_dump_frames` (function, line 1308) `void gb_platform_set_dump_frames(const char *frames)`
  - `gb_platform_set_dump_present_frames` (function, line 1330) `void gb_platform_set_dump_present_frames(const char *frames)`
  - `gb_platform_set_screenshot_prefix` (function, line 1351) `void gb_platform_set_screenshot_prefix(const char *prefix)`
  - `gb_platform_get_timing_info` (function, line 1357) `void gb_platform_get_timing_info(GBPlatformTimingInfo *out)`
  - `gb_platform_get_joypad` (function, line 1364) `uint8_t gb_platform_get_joypad(void)`
  - `gb_platform_set_title` (function, line 1368) `void gb_platform_set_title(const char *title)`
  - `gb_platform_get_smooth_lcd_transitions` (function, line 1374) `bool gb_platform_get_smooth_lcd_transitions(void)`
  - `gb_platform_set_smooth_lcd_transitions` (function, line 1378) `void gb_platform_set_smooth_lcd_transitions(bool enabled)`
  - `gb_platform_set_launcher_return_enabled` (function, line 1382) `void gb_platform_set_launcher_return_enabled(bool enabled)`
  - `gb_platform_get_exit_action` (function, line 1386) `GBPlatformExitAction gb_platform_get_exit_action(void)`
  - `gb_platform_submit_port_frame` (function, line 1390) `void gb_platform_submit_port_frame(void *user, const GBPortFrame *frame)`
  - `gb_platform_test_audio_concurrency` (function, line 1396) `bool gb_platform_test_audio_concurrency(uint32_t frames,
                                        ...`
  - `gb_platform_test_inject_persistence_fault` (function, line 1405) `void gb_platform_test_inject_persistence_fault(
    GBPersistenceTestTarget target,
    GBPersist...`
  - `audio` (function, line 181) `* PC speaker audio (DOOM-style: sparse syscalls from poll points) * * Per rendered frame, live voice frequencies come from gb_audio_voice() * (runtime accessor over internal channel state: enabled, DA`
  - `menu` (function, line 506) `* FILE menu (no Nuklear on purpose) * * A 16 px menu bar lives in the top margin the 2x GB image never touches * (it starts at GB_DST_Y0 = 36). Clicking FILE (or pressing Esc) drops a * 5-item menu: S`
  - `STB_IMAGE_IMPLEMENTATION` (macro, line 56) `#define STB_IMAGE_IMPLEMENTATION`
  - `STBI_ONLY_PNG` (macro, line 57) `#define STBI_ONLY_PNG`
  - `STBI_NO_STDIO` (macro, line 58) `#define STBI_NO_STDIO`
  - `FB_ADDR` (macro, line 123) `#define FB_ADDR`
  - `FB_W` (macro, line 124) `#define FB_W`
  - `FB_H` (macro, line 125) `#define FB_H`
  - `GB_SCALE` (macro, line 127) `#define GB_SCALE`
  - `GB_DST_W` (macro, line 128) `#define GB_DST_W`
  - `GB_DST_H` (macro, line 129) `#define GB_DST_H`
  - `GB_DST_X0` (macro, line 130) `#define GB_DST_X0`
  - `GB_DST_Y0` (macro, line 131) `#define GB_DST_Y0`
  - `MINIOS_AUDIO_RATE` (macro, line 196) `#define MINIOS_AUDIO_RATE`
  - `MINIOS_AUDIO_SILENCE_E` (macro, line 197) `#define MINIOS_AUDIO_SILENCE_E`
  - `MINIOS_AUDIO_MIN_HZ` (macro, line 198) `#define MINIOS_AUDIO_MIN_HZ`
  - `MINIOS_AUDIO_MAX_HZ` (macro, line 199) `#define MINIOS_AUDIO_MAX_HZ`
  - `MINIOS_ARP_BASS_MS` (macro, line 200) `#define MINIOS_ARP_BASS_MS`
  - `MINIOS_ARP_MEL_MS` (macro, line 201) `#define MINIOS_ARP_MEL_MS`
  - `MENU_BAR_H` (macro, line 521) `#define MENU_BAR_H`
  - `MENU_FILE_X0` (macro, line 522) `#define MENU_FILE_X0`
  - `MENU_FILE_X1` (macro, line 523) `#define MENU_FILE_X1`
  - `MENU_DROP_X0` (macro, line 524) `#define MENU_DROP_X0`
  - `MENU_DROP_W` (macro, line 525) `#define MENU_DROP_W`
  - `MENU_ITEM_H` (macro, line 526) `#define MENU_ITEM_H`
  - `MENU_NITEMS` (macro, line 527) `#define MENU_NITEMS`
  - `MENU_BG` (macro, line 530) `#define MENU_BG`
  - `MENU_FG` (macro, line 531) `#define MENU_FG`
  - `MENU_HOVER` (macro, line 532) `#define MENU_HOVER`
  - `MENU_OSD_BG` (macro, line 533) `#define MENU_OSD_BG`
  - `MINIOS_AUTOSAVE_MS` (macro, line 1055) `#define MINIOS_AUTOSAVE_MS`
  - `MINIOS_FF_FRAMESKIP` (macro, line 1067) `#define MINIOS_FF_FRAMESKIP`
- Depends on: `headers/audio.h`, `kernel/string.c`, `progs/minios_abi.h`, `progs/minios_png.h`
