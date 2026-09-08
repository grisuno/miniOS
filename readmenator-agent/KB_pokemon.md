# Subsystem: pokemon

## progs/pokemon/fetch.sh
- Layer: utility
- Doc: fetch.sh - clone the gb-recompiled tool into progs/pokemon/upstream.  The upstream project ships the recompiler + runtim
- Language: sh

## progs/pokemon/platform_minios.c
- Layer: data_access
- Language: c
- Symbols:
  - `gb_voice_t` (struct, line 228)
  - `audible` (function, line 32) `* audible (noise SFX, sweep zaps), the raw mix estimate is played.
 *
 * Debug: heartbeat to stde...`
  - `sys_kbd` (function, line 61) `static long sys_kbd(void)`
  - `sys_nk_frame` (function, line 67) `static long sys_nk_frame(int *origin)`
  - `sys_mouse` (function, line 73) `static long sys_mouse(int *xybw)`
  - `sys_vga_mode` (function, line 79) `static long sys_vga_mode(int on)`
  - `sys_kbd_raw` (function, line 85) `static long sys_kbd_raw(int on)`
  - `sys_palette` (function, line 91) `static long sys_palette(const unsigned char *pal)`
  - `sys_gfx_title` (function, line 97) `static long sys_gfx_title(const char *t)`
  - `sys_tone` (function, line 103) `static long sys_tone(unsigned f)`
  - `gb_platform_set_debug` (function, line 143) `void gb_platform_set_debug(bool enabled)`
  - `_dl_argv` (function, line 151) `* usable _dl_argv (it bound to unrelated storage and strcmp faulted).
 * DO NOT reintroduce argv ...`
  - `minios_audio_sample` (function, line 201) `static void minios_audio_sample(GBContext *ctx, int16_t left, int16_t right)`
  - `gb_voice_in_range` (function, line 232) `static bool gb_voice_in_range(unsigned f)`
  - `sample_apu_voices` (function, line 236) `static void sample_apu_voices(gb_voice_t *v)`
  - `hold_tone` (function, line 256) `static void hold_tone(unsigned freq, unsigned ms)`
  - `minios_audio_play` (function, line 264) `static void minios_audio_play(const gb_voice_t *v, bool pcm_audible,
                            ...`
  - `minios_audio_frame` (function, line 300) `static void minios_audio_frame(void)`
  - `rebuild_joypad` (function, line 327) `static void rebuild_joypad(void)`
  - `poll_keyboard` (function, line 341) `static void poll_keyboard(void)`
  - `push_332_palette` (function, line 381) `static void push_332_palette(void)`
  - `menu_fill` (function, line 536) `static void menu_fill(int x0, int y0, int w, int h, uint8_t idx)`
  - `menu_text` (function, line 549) `static void menu_text(int x, int y, const char *s, uint8_t fg)`
  - `menu_osd` (function, line 568) `static void menu_osd(const char *s)`
  - `menu_draw` (function, line 574) `static void menu_draw(void)`
  - `menu_item_at` (function, line 604) `static int menu_item_at(int lx, int ly)`
  - `menu_do_save` (function, line 611) `static void menu_do_save(void)`
  - `menu_do_load` (function, line 627) `static void menu_do_load(void)`
  - `menu_activate` (function, line 646) `static void menu_activate(int it)`
  - `poll_menu` (function, line 681) `static void poll_menu(void)`
  - `upload_frame` (function, line 738) `static void upload_frame(const uint32_t *framebuffer)`
  - `gb_platform_init` (function, line 805) `bool gb_platform_init(int scale)`
  - `minios_persist_path` (function, line 834) `static void minios_persist_path(char *out, size_t n, const GBContext *ctx,
                      ...`
  - `minios_legacy_path` (function, line 844) `static void minios_legacy_path(char *out, size_t n, const GBContext *ctx,
                       ...`
  - `minios_load_helper` (function, line 849) `static bool minios_load_helper(const char *path, void *data, size_t size,
                       ...`
  - `minios_save_helper` (function, line 867) `static bool minios_save_helper(const char *path, const void *data, size_t size)`
  - `minios_load_battery_ram` (function, line 878) `static bool minios_load_battery_ram(GBContext *ctx, const char *rom_name,
                       ...`
  - `minios_save_battery_ram` (function, line 893) `static bool minios_save_battery_ram(GBContext *ctx, const char *rom_name,
                       ...`
  - `minios_load_rtc_data` (function, line 903) `static bool minios_load_rtc_data(GBContext *ctx, const char *rom_name,
                          ...`
  - `minios_save_rtc_data` (function, line 916) `static bool minios_save_rtc_data(GBContext *ctx, const char *rom_name,
                          ...`
  - `minios_fast_forward` (function, line 955) `static inline bool minios_fast_forward(void)`
  - `minios_state_path` (function, line 958) `static void minios_state_path(char *out, size_t n, const GBContext *ctx)`
  - `minios_legacy_state_path` (function, line 963) `static void minios_legacy_state_path(char *out, size_t n, const GBContext *ctx)`
  - `minios_autosave` (function, line 968) `static void minios_autosave(uint32_t now)`
  - `poll_hotkeys` (function, line 983) `static void poll_hotkeys(void)`
  - `gb_platform_register_context` (function, line 1034) `void gb_platform_register_context(GBContext *ctx)`
  - `gb_platform_shutdown` (function, line 1050) `void gb_platform_shutdown(void)`
  - `gb_platform_poll_events` (function, line 1057) `bool gb_platform_poll_events(GBContext *ctx)`
  - `gb_platform_render_frame` (function, line 1066) `void gb_platform_render_frame(const uint32_t *framebuffer)`
  - `gb_platform_present_framebuffer` (function, line 1124) `void gb_platform_present_framebuffer(const uint32_t *framebuffer)`
  - `gb_platform_render_lcd_off_frame` (function, line 1130) `void gb_platform_render_lcd_off_frame(void)`
  - `gb_platform_vsync` (function, line 1146) `void gb_platform_vsync(uint32_t frame_cycles)`
  - `gb_platform_set_benchmark_mode` (function, line 1167) `void gb_platform_set_benchmark_mode(bool enabled)`
  - `gb_platform_set_input_script` (function, line 1171) `bool gb_platform_set_input_script(const char *script)`
  - `gb_platform_set_input_record_file` (function, line 1177) `void gb_platform_set_input_record_file(const char *path)`
  - `gb_platform_set_persistence_dir` (function, line 1182) `bool gb_platform_set_persistence_dir(const char *path)`
  - `gb_platform_set_dump_frames` (function, line 1191) `void gb_platform_set_dump_frames(const char *frames)`
  - `gb_platform_set_dump_present_frames` (function, line 1213) `void gb_platform_set_dump_present_frames(const char *frames)`
  - `gb_platform_set_screenshot_prefix` (function, line 1234) `void gb_platform_set_screenshot_prefix(const char *prefix)`
  - `gb_platform_get_timing_info` (function, line 1240) `void gb_platform_get_timing_info(GBPlatformTimingInfo *out)`
  - `gb_platform_get_joypad` (function, line 1247) `uint8_t gb_platform_get_joypad(void)`
  - `gb_platform_set_title` (function, line 1251) `void gb_platform_set_title(const char *title)`
  - `gb_platform_get_smooth_lcd_transitions` (function, line 1257) `bool gb_platform_get_smooth_lcd_transitions(void)`
  - `gb_platform_set_smooth_lcd_transitions` (function, line 1261) `void gb_platform_set_smooth_lcd_transitions(bool enabled)`
  - `gb_platform_set_launcher_return_enabled` (function, line 1265) `void gb_platform_set_launcher_return_enabled(bool enabled)`
  - `gb_platform_get_exit_action` (function, line 1269) `GBPlatformExitAction gb_platform_get_exit_action(void)`
  - `gb_platform_submit_port_frame` (function, line 1273) `void gb_platform_submit_port_frame(void *user, const GBPortFrame *frame)`
  - `gb_platform_test_audio_concurrency` (function, line 1280) `bool gb_platform_test_audio_concurrency(uint32_t frames,
                                        ...`
  - `gb_platform_test_inject_persistence_fault` (function, line 1288) `void gb_platform_test_inject_persistence_fault(
    GBPersistenceTestTarget target,
    GBPersist...`
  - `volatile` (function, line 58) `__asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_TIME), "D"(0) : "rcx","r11","memory");`
  - `fprintf` (function, line 162) `fprintf(stderr, "[MINIOS-DBG] render=%u present=%u lcd_off=%u poll=%u vsync=%u " "joypad dpad=%02x buttons=%02x\n", g_dbg_render, g_dbg_present, g_dbg_lcd_off, g_dbg_poll, g_dbg_vsync, g_joypad_dpad, `
  - `fflush` (function, line 168) `fflush(stderr);`
  - `audio` (function, line 172) `* PC speaker audio (DOOM-style: sparse syscalls from poll points) * * Per rendered frame, live voice frequencies come from gb_audio_voice() * (runtime accessor over internal channel state: enabled, DA`
  - `menu` (function, line 497) `* FILE menu (no Nuklear on purpose) * * A 16 px menu bar lives in the top margin the 2x GB image never touches * (it starts at GB_DST_Y0 = 36). Clicking FILE (or pressing Esc) drops a * 5-item menu: S`
  - `strncpy` (function, line 570) `strncpy(g_osd, s, sizeof(g_osd) - 1);`
  - `gb_context_save_ram` (function, line 617) `gb_context_save_ram(g_ctx);`
  - `exit` (function, line 675) `exit(0);`
  - `memset` (function, line 813) `memset(g_last_guest_framebuffer, 0, sizeof(g_last_guest_framebuffer));`
  - `snprintf` (function, line 838) `snprintf(out, n, "saves/%.40s%s", id, ext);`
  - `fclose` (function, line 858) `fclose(f);`
  - `memcpy` (function, line 993) `memcpy(prev, g_key_state, sizeof(prev));`
  - `gb_set_platform_callbacks` (function, line 1048) `gb_set_platform_callbacks(ctx, &cbs);`
  - `dbg_heartbeat` (function, line 1086) `dbg_heartbeat();`
  - `FB_ADDR` (macro, line 113) `#define FB_ADDR`
  - `FB_W` (macro, line 115) `#define FB_W`
  - `FB_H` (macro, line 116) `#define FB_H`
  - `GB_SCALE` (macro, line 117) `#define GB_SCALE`
  - `GB_DST_W` (macro, line 119) `#define GB_DST_W`
  - `GB_DST_H` (macro, line 120) `#define GB_DST_H`
  - `GB_DST_X0` (macro, line 121) `#define GB_DST_X0`
  - `GB_DST_Y0` (macro, line 122) `#define GB_DST_Y0`
  - `MINIOS_AUDIO_RATE` (macro, line 186) `#define MINIOS_AUDIO_RATE`
  - `MINIOS_AUDIO_SILENCE_E` (macro, line 188) `#define MINIOS_AUDIO_SILENCE_E`
  - `MINIOS_AUDIO_MIN_HZ` (macro, line 189) `#define MINIOS_AUDIO_MIN_HZ`
  - `MINIOS_AUDIO_MAX_HZ` (macro, line 190) `#define MINIOS_AUDIO_MAX_HZ`
  - `MINIOS_ARP_BASS_MS` (macro, line 191) `#define MINIOS_ARP_BASS_MS`
  - `MINIOS_ARP_MEL_MS` (macro, line 192) `#define MINIOS_ARP_MEL_MS`
  - `MENU_BAR_H` (macro, line 511) `#define MENU_BAR_H`
  - `MENU_FILE_X0` (macro, line 513) `#define MENU_FILE_X0`
  - `MENU_FILE_X1` (macro, line 514) `#define MENU_FILE_X1`
  - `MENU_DROP_X0` (macro, line 515) `#define MENU_DROP_X0`
  - `MENU_DROP_W` (macro, line 516) `#define MENU_DROP_W`
  - `MENU_ITEM_H` (macro, line 517) `#define MENU_ITEM_H`
  - `MENU_NITEMS` (macro, line 518) `#define MENU_NITEMS`
  - `MENU_BG` (macro, line 521) `#define MENU_BG`
  - `MENU_FG` (macro, line 522) `#define MENU_FG`
  - `MENU_HOVER` (macro, line 523) `#define MENU_HOVER`
  - `MENU_OSD_BG` (macro, line 524) `#define MENU_OSD_BG`
  - `MINIOS_AUTOSAVE_MS` (macro, line 940) `#define MINIOS_AUTOSAVE_MS`
  - `MINIOS_FF_FRAMESKIP` (macro, line 952) `#define MINIOS_FF_FRAMESKIP`
- Depends on: `audio.h`, `kernel/string.c`, `progs/minios_abi.h`
