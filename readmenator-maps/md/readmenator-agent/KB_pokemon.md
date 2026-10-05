# Subsystem: pokemon

## progs/pokemon/fetch.sh
- Layer: utility
- Doc: fetch.sh - clone the gb-recompiled tool into progs/pokemon/upstream.  The upstream project ships the recompiler + runtim
- Language: sh

## progs/pokemon/platform_minios.c
- Layer: data_access
- Language: c
- Symbols:
  - `gb_voice_t` (struct, line 301)
  - `audible` (function, line 36) `* voice is audible (noise SFX, sweep zaps), the raw mix estimate plays.
 *
 * Debug: heartbeat to...`
  - `sys_kbd` (function, line 75) `static long sys_kbd(void)`
  - `sys_nk_frame` (function, line 81) `static long sys_nk_frame(int *origin)`
  - `sys_mouse` (function, line 87) `static long sys_mouse(int *xybw)`
  - `sys_vga_mode` (function, line 93) `static long sys_vga_mode(int on)`
  - `sys_kbd_raw` (function, line 99) `static long sys_kbd_raw(int on)`
  - `sys_palette` (function, line 105) `static long sys_palette(const unsigned char *pal)`
  - `sys_gfx_title` (function, line 111) `static long sys_gfx_title(const char *t)`
  - `sys_tone` (function, line 117) `static long sys_tone(unsigned f)`
  - `sys_pcm2_open` (function, line 123) `static long sys_pcm2_open(long flags)`
  - `sys_pcm2_write` (function, line 129) `static long sys_pcm2_write(const void *buf, long len)`
  - `sys_pcm2_close` (function, line 135) `static void sys_pcm2_close(void)`
  - `gain` (function, line 142) `* timing gain (overshoot is microseconds against millisecond waits).
 * Difference-based, so it s...`
  - `gb_platform_set_debug` (function, line 190) `void gb_platform_set_debug(bool enabled)`
  - `_dl_argv` (function, line 197) `* usable _dl_argv (it bound to unrelated storage and strcmp faulted).
 * DO NOT reintroduce argv ...`
  - `minios_audio_sample` (function, line 262) `static void minios_audio_sample(GBContext *ctx, int16_t left, int16_t right)`
  - `gb_voice_in_range` (function, line 306) `static bool gb_voice_in_range(unsigned f)`
  - `sample_apu_voices` (function, line 310) `static void sample_apu_voices(gb_voice_t *v)`
  - `minios_audio_play` (function, line 330) `static void minios_audio_play(const gb_voice_t *v, bool pcm_audible,
                            ...`
  - `rebuild_joypad` (function, line 402) `static void rebuild_joypad(void)`
  - `poll_keyboard` (function, line 416) `static void poll_keyboard(void)`
  - `push_332_palette` (function, line 455) `static void push_332_palette(void)`
  - `ui_fringe_dirty` (function, line 620) `static bool ui_fringe_dirty(uint32_t now)`
  - `ui_fringe_sync` (function, line 626) `static void ui_fringe_sync(uint32_t now)`
  - `menu_fill` (function, line 632) `static void menu_fill(int x0, int y0, int w, int h, uint8_t idx)`
  - `menu_text` (function, line 645) `static void menu_text(int x, int y, const char *s, uint8_t fg)`
  - `menu_osd` (function, line 664) `static void menu_osd(const char *s)`
  - `menu_draw` (function, line 670) `static void menu_draw(void)`
  - `menu_item_at` (function, line 700) `static int menu_item_at(int lx, int ly)`
  - `menu_do_save` (function, line 707) `static void menu_do_save(void)`
  - `menu_do_load` (function, line 723) `static void menu_do_load(void)`
  - `menu_activate` (function, line 742) `static void menu_activate(int it)`
  - `poll_menu` (function, line 776) `static void poll_menu(void)`
  - `pokemon_art_load_one` (function, line 844) `static int pokemon_art_load_one(const char *path, unsigned char **rgb,
                          ...`
  - `pokemon_art_load` (function, line 869) `static void pokemon_art_load(void)`
  - `pokemon_art_draw_one` (function, line 887) `static void pokemon_art_draw_one(const unsigned char *rgb, int sw, int sh,
                      ...`
  - `pokemon_art_draw` (function, line 925) `static void pokemon_art_draw(void)`
  - `px_to_idx` (function, line 956) `static uint8_t px_to_idx(uint32_t pixel)`
  - `upload_frame` (function, line 975) `static void upload_frame(const uint32_t *framebuffer)`
  - `gb_platform_init` (function, line 1056) `bool gb_platform_init(int scale)`
  - `minios_persist_path` (function, line 1088) `static void minios_persist_path(char *out, size_t n, const GBContext *ctx,
                      ...`
  - `minios_legacy_path` (function, line 1097) `static void minios_legacy_path(char *out, size_t n, const GBContext *ctx,
                       ...`
  - `minios_load_helper` (function, line 1103) `static bool minios_load_helper(const char *path, void *data, size_t size,
                       ...`
  - `minios_save_helper` (function, line 1121) `static bool minios_save_helper(const char *path, const void *data, size_t size)`
  - `minios_load_battery_ram` (function, line 1132) `static bool minios_load_battery_ram(GBContext *ctx, const char *rom_name,
                       ...`
  - `minios_save_battery_ram` (function, line 1147) `static bool minios_save_battery_ram(GBContext *ctx, const char *rom_name,
                       ...`
  - `minios_load_rtc_data` (function, line 1157) `static bool minios_load_rtc_data(GBContext *ctx, const char *rom_name,
                          ...`
  - `minios_save_rtc_data` (function, line 1170) `static bool minios_save_rtc_data(GBContext *ctx, const char *rom_name,
                          ...`
  - `minios_fast_forward` (function, line 1208) `static inline bool minios_fast_forward(void)`
  - `minios_state_path` (function, line 1212) `static void minios_state_path(char *out, size_t n, const GBContext *ctx)`
  - `minios_legacy_state_path` (function, line 1217) `static void minios_legacy_state_path(char *out, size_t n, const GBContext *ctx)`
  - `minios_autosave` (function, line 1222) `static void minios_autosave(uint32_t now)`
  - `poll_hotkeys` (function, line 1236) `static void poll_hotkeys(void)`
  - `gb_platform_register_context` (function, line 1288) `void gb_platform_register_context(GBContext *ctx)`
  - `gb_platform_shutdown` (function, line 1310) `void gb_platform_shutdown(void)`
  - `gb_platform_poll_events` (function, line 1321) `bool gb_platform_poll_events(GBContext *ctx)`
  - `gb_platform_render_frame` (function, line 1330) `void gb_platform_render_frame(const uint32_t *framebuffer)`
  - `frames` (function, line 1366) `* frames (menu bar not on screen yet) and any frame after the
         * LCD-off path zeroed the ...`
  - `gb_platform_present_framebuffer` (function, line 1399) `void gb_platform_present_framebuffer(const uint32_t *framebuffer)`
  - `gb_platform_render_lcd_off_frame` (function, line 1411) `void gb_platform_render_lcd_off_frame(void)`
  - `gb_platform_vsync` (function, line 1433) `void gb_platform_vsync(uint32_t frame_cycles)`
  - `gb_platform_set_benchmark_mode` (function, line 1450) `void gb_platform_set_benchmark_mode(bool enabled)`
  - `gb_platform_set_input_script` (function, line 1454) `bool gb_platform_set_input_script(const char *script)`
  - `gb_platform_set_input_record_file` (function, line 1460) `void gb_platform_set_input_record_file(const char *path)`
  - `gb_platform_set_persistence_dir` (function, line 1465) `bool gb_platform_set_persistence_dir(const char *path)`
  - `gb_platform_set_dump_frames` (function, line 1474) `void gb_platform_set_dump_frames(const char *frames)`
  - `gb_platform_set_dump_present_frames` (function, line 1496) `void gb_platform_set_dump_present_frames(const char *frames)`
  - `gb_platform_set_screenshot_prefix` (function, line 1517) `void gb_platform_set_screenshot_prefix(const char *prefix)`
  - `gb_platform_get_timing_info` (function, line 1523) `void gb_platform_get_timing_info(GBPlatformTimingInfo *out)`
  - `gb_platform_get_joypad` (function, line 1530) `uint8_t gb_platform_get_joypad(void)`
  - `gb_platform_set_title` (function, line 1534) `void gb_platform_set_title(const char *title)`
  - `gb_platform_get_smooth_lcd_transitions` (function, line 1540) `bool gb_platform_get_smooth_lcd_transitions(void)`
  - `gb_platform_set_smooth_lcd_transitions` (function, line 1544) `void gb_platform_set_smooth_lcd_transitions(bool enabled)`
  - `gb_platform_set_launcher_return_enabled` (function, line 1548) `void gb_platform_set_launcher_return_enabled(bool enabled)`
  - `gb_platform_get_exit_action` (function, line 1552) `GBPlatformExitAction gb_platform_get_exit_action(void)`
  - `gb_platform_submit_port_frame` (function, line 1556) `void gb_platform_submit_port_frame(void *user, const GBPortFrame *frame)`
  - `gb_platform_test_audio_concurrency` (function, line 1562) `bool gb_platform_test_audio_concurrency(uint32_t frames,
                                        ...`
  - `gb_platform_test_inject_persistence_fault` (function, line 1571) `void gb_platform_test_inject_persistence_fault(
    GBPersistenceTestTarget target,
    GBPersist...`
  - `audio` (function, line 218) `* PC speaker audio (DOOM-style: sparse syscalls from poll points) * * Per rendered frame, live voice frequencies come from gb_audio_voice() * (runtime accessor over internal channel state: enabled, DA`
  - `menu` (function, line 571) `* FILE menu (no Nuklear on purpose) * * A 16 px menu bar lives in the top margin the 2x GB image never touches * (it starts at GB_DST_Y0 = 36). Clicking FILE (or pressing Esc) drops a * 5-item menu: S`
  - `STB_IMAGE_IMPLEMENTATION` (macro, line 60) `#define STB_IMAGE_IMPLEMENTATION`
  - `STBI_ONLY_PNG` (macro, line 61) `#define STBI_ONLY_PNG`
  - `STBI_NO_STDIO` (macro, line 62) `#define STBI_NO_STDIO`
  - `FB_ADDR` (macro, line 160) `#define FB_ADDR`
  - `FB_W` (macro, line 161) `#define FB_W`
  - `FB_H` (macro, line 162) `#define FB_H`
  - `GB_SCALE` (macro, line 164) `#define GB_SCALE`
  - `GB_DST_W` (macro, line 165) `#define GB_DST_W`
  - `GB_DST_H` (macro, line 166) `#define GB_DST_H`
  - `GB_DST_X0` (macro, line 167) `#define GB_DST_X0`
  - `GB_DST_Y0` (macro, line 168) `#define GB_DST_Y0`
  - `MINIOS_AUDIO_RATE` (macro, line 233) `#define MINIOS_AUDIO_RATE`
  - `MINIOS_AUDIO_SILENCE_E` (macro, line 234) `#define MINIOS_AUDIO_SILENCE_E`
  - `MINIOS_AUDIO_MIN_HZ` (macro, line 235) `#define MINIOS_AUDIO_MIN_HZ`
  - `MINIOS_AUDIO_MAX_HZ` (macro, line 236) `#define MINIOS_AUDIO_MAX_HZ`
  - `MINIOS_ARP_BASS_MS` (macro, line 237) `#define MINIOS_ARP_BASS_MS`
  - `MINIOS_ARP_MEL_MS` (macro, line 238) `#define MINIOS_ARP_MEL_MS`
  - `MENU_BAR_H` (macro, line 586) `#define MENU_BAR_H`
  - `MENU_FILE_X0` (macro, line 587) `#define MENU_FILE_X0`
  - `MENU_FILE_X1` (macro, line 588) `#define MENU_FILE_X1`
  - `MENU_DROP_X0` (macro, line 589) `#define MENU_DROP_X0`
  - `MENU_DROP_W` (macro, line 590) `#define MENU_DROP_W`
  - `MENU_ITEM_H` (macro, line 591) `#define MENU_ITEM_H`
  - `MENU_NITEMS` (macro, line 592) `#define MENU_NITEMS`
  - `MENU_BG` (macro, line 595) `#define MENU_BG`
  - `MENU_FG` (macro, line 596) `#define MENU_FG`
  - `MENU_HOVER` (macro, line 597) `#define MENU_HOVER`
  - `MENU_OSD_BG` (macro, line 598) `#define MENU_OSD_BG`
  - `MINIOS_AUTOSAVE_MS` (macro, line 1193) `#define MINIOS_AUTOSAVE_MS`
  - `MINIOS_FF_FRAMESKIP` (macro, line 1205) `#define MINIOS_FF_FRAMESKIP`
- Depends on: `headers/audio.h`, `kernel/string.c`, `progs/minios_abi.h`, `progs/minios_png.h`
