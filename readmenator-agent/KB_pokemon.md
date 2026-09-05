# Subsystem: pokemon

## progs/pokemon/fetch.sh
- Layer: utility
- Doc: fetch.sh - clone the gb-recompiled tool into progs/pokemon/upstream.  The upstream project ships the recompiler + runtim
- Language: sh

## progs/pokemon/platform_minios.c
- Layer: data_access
- Language: c
- Symbols:
  - `audible` (function, line 32) `* audible (noise SFX, sweep zaps), the raw mix estimate is played.
 *
 * Debug: heartbeat to stde...`
  - `sys_kbd` (function, line 61) `static long sys_kbd(void)`
  - `sys_nk_frame` (function, line 67) `static long sys_nk_frame(void)`
  - `sys_vga_mode` (function, line 73) `static long sys_vga_mode(int on)`
  - `sys_kbd_raw` (function, line 79) `static long sys_kbd_raw(int on)`
  - `sys_palette` (function, line 85) `static long sys_palette(const unsigned char *pal)`
  - `sys_gfx_title` (function, line 91) `static long sys_gfx_title(const char *t)`
  - `sys_tone` (function, line 97) `static long sys_tone(unsigned f)`
  - `gb_platform_set_debug` (function, line 137) `void gb_platform_set_debug(bool enabled)`
  - `_dl_argv` (function, line 145) `* usable _dl_argv (it bound to unrelated storage and strcmp faulted).
 * DO NOT reintroduce argv ...`
  - `minios_audio_sample` (function, line 195) `static void minios_audio_sample(GBContext *ctx, int16_t left, int16_t right)`
  - `gb_voice_in_range` (function, line 226) `static bool gb_voice_in_range(unsigned f)`
  - `sample_apu_voices` (function, line 230) `static void sample_apu_voices(gb_voice_t *v)`
  - `hold_tone` (function, line 250) `static void hold_tone(unsigned freq, unsigned ms)`
  - `minios_audio_play` (function, line 258) `static void minios_audio_play(const gb_voice_t *v, bool pcm_audible,
                            ...`
  - `minios_audio_frame` (function, line 294) `static void minios_audio_frame(void)`
  - `rebuild_joypad` (function, line 315) `static void rebuild_joypad(void)`
  - `poll_keyboard` (function, line 328) `static void poll_keyboard(void)`
  - `push_332_palette` (function, line 368) `static void push_332_palette(void)`
  - `upload_frame` (function, line 382) `static void upload_frame(const uint32_t *framebuffer)`
  - `gb_platform_init` (function, line 441) `bool gb_platform_init(int scale)`
  - `minios_persist_path` (function, line 467) `static void minios_persist_path(char *out, size_t n, const GBContext *ctx,
                      ...`
  - `minios_load_helper` (function, line 473) `static bool minios_load_helper(const char *path, void *data, size_t size,
                       ...`
  - `minios_save_helper` (function, line 491) `static bool minios_save_helper(const char *path, const void *data, size_t size)`
  - `minios_load_battery_ram` (function, line 502) `static bool minios_load_battery_ram(GBContext *ctx, const char *rom_name,
                       ...`
  - `minios_save_battery_ram` (function, line 510) `static bool minios_save_battery_ram(GBContext *ctx, const char *rom_name,
                       ...`
  - `minios_load_rtc_data` (function, line 520) `static bool minios_load_rtc_data(GBContext *ctx, const char *rom_name,
                          ...`
  - `minios_save_rtc_data` (function, line 528) `static bool minios_save_rtc_data(GBContext *ctx, const char *rom_name,
                          ...`
  - `minios_state_path` (function, line 550) `static void minios_state_path(char *out, size_t n, const GBContext *ctx)`
  - `minios_autosave` (function, line 555) `static void minios_autosave(uint32_t now)`
  - `poll_hotkeys` (function, line 568) `static void poll_hotkeys(void)`
  - `gb_platform_register_context` (function, line 597) `void gb_platform_register_context(GBContext *ctx)`
  - `gb_platform_shutdown` (function, line 613) `void gb_platform_shutdown(void)`
  - `gb_platform_poll_events` (function, line 620) `bool gb_platform_poll_events(GBContext *ctx)`
  - `gb_platform_render_frame` (function, line 628) `void gb_platform_render_frame(const uint32_t *framebuffer)`
  - `gb_platform_present_framebuffer` (function, line 655) `void gb_platform_present_framebuffer(const uint32_t *framebuffer)`
  - `gb_platform_render_lcd_off_frame` (function, line 661) `void gb_platform_render_lcd_off_frame(void)`
  - `gb_platform_vsync` (function, line 671) `void gb_platform_vsync(uint32_t frame_cycles)`
  - `gb_platform_set_benchmark_mode` (function, line 687) `void gb_platform_set_benchmark_mode(bool enabled)`
  - `gb_platform_set_input_script` (function, line 691) `bool gb_platform_set_input_script(const char *script)`
  - `gb_platform_set_input_record_file` (function, line 697) `void gb_platform_set_input_record_file(const char *path)`
  - `gb_platform_set_persistence_dir` (function, line 702) `bool gb_platform_set_persistence_dir(const char *path)`
  - `gb_platform_set_dump_frames` (function, line 711) `void gb_platform_set_dump_frames(const char *frames)`
  - `gb_platform_set_dump_present_frames` (function, line 733) `void gb_platform_set_dump_present_frames(const char *frames)`
  - `gb_platform_set_screenshot_prefix` (function, line 754) `void gb_platform_set_screenshot_prefix(const char *prefix)`
  - `gb_platform_get_timing_info` (function, line 760) `void gb_platform_get_timing_info(GBPlatformTimingInfo *out)`
  - `gb_platform_get_joypad` (function, line 767) `uint8_t gb_platform_get_joypad(void)`
  - `gb_platform_set_title` (function, line 771) `void gb_platform_set_title(const char *title)`
  - `gb_platform_get_smooth_lcd_transitions` (function, line 777) `bool gb_platform_get_smooth_lcd_transitions(void)`
  - `gb_platform_set_smooth_lcd_transitions` (function, line 781) `void gb_platform_set_smooth_lcd_transitions(bool enabled)`
  - `gb_platform_set_launcher_return_enabled` (function, line 785) `void gb_platform_set_launcher_return_enabled(bool enabled)`
  - `gb_platform_get_exit_action` (function, line 789) `GBPlatformExitAction gb_platform_get_exit_action(void)`
  - `gb_platform_submit_port_frame` (function, line 793) `void gb_platform_submit_port_frame(void *user, const GBPortFrame *frame)`
  - `gb_platform_test_audio_concurrency` (function, line 800) `bool gb_platform_test_audio_concurrency(uint32_t frames,
                                        ...`
  - `gb_platform_test_inject_persistence_fault` (function, line 808) `void gb_platform_test_inject_persistence_fault(
    GBPersistenceTestTarget target,
    GBPersist...`
  - `FB_ADDR` (macro, line 107)
  - `FB_W` (macro, line 109)
  - `FB_H` (macro, line 110)
  - `GB_SCALE` (macro, line 111)
  - `GB_DST_W` (macro, line 113)
  - `GB_DST_H` (macro, line 114)
  - `GB_DST_X0` (macro, line 115)
  - `GB_DST_Y0` (macro, line 116)
  - `MINIOS_AUDIO_RATE` (macro, line 180)
  - `MINIOS_AUDIO_SILENCE_E` (macro, line 182)
  - `MINIOS_AUDIO_MIN_HZ` (macro, line 183)
  - `MINIOS_AUDIO_MAX_HZ` (macro, line 184)
  - `MINIOS_ARP_BASS_MS` (macro, line 185)
  - `MINIOS_ARP_MEL_MS` (macro, line 186)
  - `MINIOS_AUTOSAVE_MS` (macro, line 549)
