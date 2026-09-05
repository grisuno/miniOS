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
  - `sys_kbd` (function, line 60) `static long sys_kbd(void)`
  - `sys_nk_frame` (function, line 66) `static long sys_nk_frame(void)`
  - `sys_vga_mode` (function, line 72) `static long sys_vga_mode(int on)`
  - `sys_kbd_raw` (function, line 78) `static long sys_kbd_raw(int on)`
  - `sys_palette` (function, line 84) `static long sys_palette(const unsigned char *pal)`
  - `sys_gfx_title` (function, line 90) `static long sys_gfx_title(const char *t)`
  - `sys_tone` (function, line 96) `static long sys_tone(unsigned f)`
  - `gb_platform_set_debug` (function, line 136) `void gb_platform_set_debug(bool enabled)`
  - `_dl_argv` (function, line 144) `* usable _dl_argv (it bound to unrelated storage and strcmp faulted).
 * DO NOT reintroduce argv ...`
  - `minios_audio_sample` (function, line 182) `static void minios_audio_sample(GBContext *ctx, int16_t left, int16_t right)`
  - `minios_audio_ensure` (function, line 201) `static void minios_audio_ensure(GBContext *ctx)`
  - `gb_voice_freq` (function, line 215) `static unsigned gb_voice_freq(unsigned n)`
  - `gb_voice_in_range` (function, line 221) `static bool gb_voice_in_range(unsigned f)`
  - `sample_apu_voices` (function, line 225) `static void sample_apu_voices(gb_voice_t *v)`
  - `hold_tone` (function, line 263) `static void hold_tone(unsigned freq, unsigned ms)`
  - `minios_audio_play` (function, line 271) `static void minios_audio_play(const gb_voice_t *v, bool pcm_audible,
                            ...`
  - `minios_audio_frame` (function, line 307) `static void minios_audio_frame(void)`
  - `rebuild_joypad` (function, line 328) `static void rebuild_joypad(void)`
  - `poll_keyboard` (function, line 341) `static void poll_keyboard(void)`
  - `push_332_palette` (function, line 381) `static void push_332_palette(void)`
  - `upload_frame` (function, line 395) `static void upload_frame(const uint32_t *framebuffer)`
  - `gb_platform_init` (function, line 454) `bool gb_platform_init(int scale)`
  - `gb_platform_register_context` (function, line 472) `void gb_platform_register_context(GBContext *ctx)`
  - `gb_platform_shutdown` (function, line 476) `void gb_platform_shutdown(void)`
  - `gb_platform_poll_events` (function, line 483) `bool gb_platform_poll_events(GBContext *ctx)`
  - `gb_platform_render_frame` (function, line 490) `void gb_platform_render_frame(const uint32_t *framebuffer)`
  - `gb_platform_present_framebuffer` (function, line 517) `void gb_platform_present_framebuffer(const uint32_t *framebuffer)`
  - `gb_platform_render_lcd_off_frame` (function, line 523) `void gb_platform_render_lcd_off_frame(void)`
  - `gb_platform_vsync` (function, line 533) `void gb_platform_vsync(uint32_t frame_cycles)`
  - `gb_platform_set_benchmark_mode` (function, line 549) `void gb_platform_set_benchmark_mode(bool enabled)`
  - `gb_platform_set_input_script` (function, line 553) `bool gb_platform_set_input_script(const char *script)`
  - `gb_platform_set_input_record_file` (function, line 559) `void gb_platform_set_input_record_file(const char *path)`
  - `gb_platform_set_persistence_dir` (function, line 564) `bool gb_platform_set_persistence_dir(const char *path)`
  - `gb_platform_set_dump_frames` (function, line 573) `void gb_platform_set_dump_frames(const char *frames)`
  - `gb_platform_set_dump_present_frames` (function, line 595) `void gb_platform_set_dump_present_frames(const char *frames)`
  - `gb_platform_set_screenshot_prefix` (function, line 616) `void gb_platform_set_screenshot_prefix(const char *prefix)`
  - `gb_platform_get_timing_info` (function, line 622) `void gb_platform_get_timing_info(GBPlatformTimingInfo *out)`
  - `gb_platform_get_joypad` (function, line 629) `uint8_t gb_platform_get_joypad(void)`
  - `gb_platform_set_title` (function, line 633) `void gb_platform_set_title(const char *title)`
  - `gb_platform_get_smooth_lcd_transitions` (function, line 639) `bool gb_platform_get_smooth_lcd_transitions(void)`
  - `gb_platform_set_smooth_lcd_transitions` (function, line 643) `void gb_platform_set_smooth_lcd_transitions(bool enabled)`
  - `gb_platform_set_launcher_return_enabled` (function, line 647) `void gb_platform_set_launcher_return_enabled(bool enabled)`
  - `gb_platform_get_exit_action` (function, line 651) `GBPlatformExitAction gb_platform_get_exit_action(void)`
  - `gb_platform_submit_port_frame` (function, line 655) `void gb_platform_submit_port_frame(void *user, const GBPortFrame *frame)`
  - `gb_platform_test_audio_concurrency` (function, line 662) `bool gb_platform_test_audio_concurrency(uint32_t frames,
                                        ...`
  - `gb_platform_test_inject_persistence_fault` (function, line 670) `void gb_platform_test_inject_persistence_fault(
    GBPersistenceTestTarget target,
    GBPersist...`
  - `FB_ADDR` (macro, line 106)
  - `FB_W` (macro, line 108)
  - `FB_H` (macro, line 109)
  - `GB_SCALE` (macro, line 110)
  - `GB_DST_W` (macro, line 112)
  - `GB_DST_H` (macro, line 113)
  - `GB_DST_X0` (macro, line 114)
  - `GB_DST_Y0` (macro, line 115)
  - `MINIOS_AUDIO_RATE` (macro, line 167)
  - `MINIOS_AUDIO_SILENCE_E` (macro, line 169)
  - `MINIOS_AUDIO_MIN_HZ` (macro, line 170)
  - `MINIOS_AUDIO_MAX_HZ` (macro, line 171)
  - `MINIOS_ARP_BASS_MS` (macro, line 172)
  - `MINIOS_ARP_MEL_MS` (macro, line 173)
