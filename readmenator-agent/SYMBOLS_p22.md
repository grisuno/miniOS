# Symbols (page 22 of 27)
Previous: [SYMBOLS_p21.md](SYMBOLS_p21.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
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
| `APSSE_BAD` | macro | `progs/src/apsse.c:40` | `#define APSSE_BAD` |
| `APSSE_BUF` | macro | `progs/src/apsse.c:34` | `#define APSSE_BUF` |
| `APSSE_MAP_BYTES` | macro | `progs/src/apsse.c:37` | `#define APSSE_MAP_BYTES` |
| `APSSE_MAP_FILL` | macro | `progs/src/apsse.c:38` | `#define APSSE_MAP_FILL` |
| `APSSE_MAP_ROUNDS` | macro | `progs/src/apsse.c:36` | `#define APSSE_MAP_ROUNDS` |
| `APSSE_NEEDLE` | macro | `progs/src/apsse.c:35` | `#define APSSE_NEEDLE` |
| `APSSE_OK` | macro | `progs/src/apsse.c:39` | `#define APSSE_OK` |
| `APSSE_ROUNDS` | macro | `progs/src/apsse.c:32` | `#define APSSE_ROUNDS` |
| `APSSE_SEED` | macro | `progs/src/apsse.c:33` | `#define APSSE_SEED` |
| `APSSE_THREADS` | macro | `progs/src/apsse.c:31` | `#define APSSE_THREADS` |
| `_GNU_SOURCE` | macro | `progs/src/apsse.c:23` | `#define _GNU_SOURCE` |
| `apsse_grind` | function | `progs/src/apsse.c:49` | `static uint64_t apsse_grind(int id)` |
| `apsse_job` | struct | `progs/src/apsse.c:42` | `` |
| `apsse_worker` | function | `progs/src/apsse.c:75` | `static void *apsse_worker(void *arg)` |
| `main` | function | `progs/src/apsse.c:81` | `int main(void)` |
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
| `looks_like_url` | function | `progs/src/freedom.c:212` | `static int looks_like_url(char *s)` |
| `main` | function | `progs/src/freedom.c:1129` | `int main(int argc, char **argv)` |
| `make_search` | function | `progs/src/freedom.c:242` | `static void make_search(char *out, char *query, int cap)` |
| `memcpy` | function | `progs/src/freedom.c:69` | `int memcpy(char *dst, char *src, int n);` |
| `memset` | function | `progs/src/freedom.c:70` | `int memset(char *dst, int c, int n);` |
| `net_dns_resolve` | function | `progs/src/freedom.c:41` | `int net_dns_resolve(const char *host);` |
| `parse_head` | function | `progs/src/freedom.c:821` | `static void parse_head(void)` |
| `print_css_dump` | function | `progs/src/freedom.c:1113` | `static void print_css_dump(void)` |
| `print_dom_dump` | function | `progs/src/freedom.c:1122` | `static void print_dom_dump(void)` |
| `printf` | function | `progs/src/freedom.c:63` | `int printf(char *fmt, ...);` |
| `put_text` | function | `progs/src/freedom.c:427` | `static void put_text(int c)` |
| `put_utf` | function | `progs/src/freedom.c:377` | `static void put_utf(int c)` |
| `put_ws` | function | `progs/src/freedom.c:366` | `static void put_ws(void)` |
| `putchar` | function | `progs/src/freedom.c:71` | `int putchar(int c);` |
| `puts` | function | `progs/src/freedom.c:64` | `int puts(char *s);` |
| `record_attr` | function | `progs/src/freedom.c:509` | `static void record_attr(void)` |
| `recv_body` | function | `progs/src/freedom.c:843` | `static int recv_body(int fd, char *buf, int len)` |
| `recvfrom` | function | `progs/src/freedom.c:55` | `int recvfrom(int fd, char *buf, int len, int flags, void *from, int *fromlen);` |
| `resolve_redirect` | function | `progs/src/freedom.c:313` | `static int resolve_redirect(void)` |
| `send_all` | function | `progs/src/freedom.c:849` | `static int send_all(int fd, char *buf, int len)` |
| `sendto` | function | `progs/src/freedom.c:54` | `int sendto(int fd, char *buf, int len, int flags, void *to, int tolen);` |
| `socket` | function | `progs/src/freedom.c:52` | `int socket(int domain, int type, int proto);` |
| `split_url` | function | `progs/src/freedom.c:266` | `static int split_url(char *url)` |
| `strchr` | function | `progs/src/freedom.c:66` | `char *strchr(char *s, int c);` |
| `strcmp` | function | `progs/src/freedom.c:67` | `int strcmp(char *a, char *b);` |
| `strlen` | function | `progs/src/freedom.c:65` | `int strlen(char *s);` |
| `strncmp` | function | `progs/src/freedom.c:68` | `int strncmp(char *a, char *b, int n);` |
| `tls_close` | function | `progs/src/freedom.c:58` | `static int tls_close(int fd)` |
| `tls_handshake` | function | `progs/src/freedom.c:42` | `int tls_handshake(int fd, char *host);` |
| `tls_recv` | function | `progs/src/freedom.c:44` | `int tls_recv(int fd, char *buf, int len);` |
| `tls_send` | function | `progs/src/freedom.c:43` | `int tls_send(int fd, char *buf, int len);` |
| `FreedomWlConfig` | struct | `progs/src/freedom_wl.c:76` | `` |
| `WL_BODY_CAP` | macro | `progs/src/freedom_wl.c:54` | `#define WL_BODY_CAP` |
| `WL_COLS` | macro | `progs/src/freedom_wl.c:49` | `#define WL_COLS` |
| `WL_ENT_MAX` | macro | `progs/src/freedom_wl.c:65` | `#define WL_ENT_MAX` |
| `WL_FONT_H` | macro | `progs/src/freedom_wl.c:63` | `#define WL_FONT_H` |
| `WL_FONT_W` | macro | `progs/src/freedom_wl.c:62` | `#define WL_FONT_W` |
| `WL_HDR_MAX` | macro | `progs/src/freedom_wl.c:55` | `#define WL_HDR_MAX` |
| `WL_HOPS_MAX` | macro | `progs/src/freedom_wl.c:61` | `#define WL_HOPS_MAX` |
| `WL_HOST_MAX` | macro | `progs/src/freedom_wl.c:58` | `#define WL_HOST_MAX` |
| `WL_LINES_MAX` | macro | `progs/src/freedom_wl.c:52` | `#define WL_LINES_MAX` |
| `WL_LINE_LEN` | macro | `progs/src/freedom_wl.c:53` | `#define WL_LINE_LEN` |
| `WL_NET_BUF` | macro | `progs/src/freedom_wl.c:56` | `#define WL_NET_BUF` |
| `WL_PATH_MAX` | macro | `progs/src/freedom_wl.c:59` | `#define WL_PATH_MAX` |
| `WL_REQ_MAX` | macro | `progs/src/freedom_wl.c:57` | `#define WL_REQ_MAX` |
| `WL_ROWS` | macro | `progs/src/freedom_wl.c:50` | `#define WL_ROWS` |
| `WL_TAG_MAX` | macro | `progs/src/freedom_wl.c:64` | `#define WL_TAG_MAX` |
| `WL_TEXT_ROWS` | macro | `progs/src/freedom_wl.c:51` | `#define WL_TEXT_ROWS` |
| `WL_URL_MAX` | macro | `progs/src/freedom_wl.c:60` | `#define WL_URL_MAX` |
| `freedom_wl_build_palette` | function | `progs/src/freedom_wl.c:1039` | `static long freedom_wl_build_palette(unsigned char *pal, long cap)` |
| `freedom_wl_clip_rect` | function | `progs/src/freedom_wl.c:196` | `static long freedom_wl_clip_rect(FreedomWlConfig *c, long *x, long *y, long *w, long *h)` |
| `freedom_wl_default` | function | `progs/src/freedom_wl.c:158` | `static FreedomWlConfig freedom_wl_default(void)` |
| `freedom_wl_frame_bytes` | function | `progs/src/freedom_wl.c:227` | `static long freedom_wl_frame_bytes(FreedomWlConfig *c, long w, long h)` |
| `freedom_wl_host_probe` | function | `progs/src/freedom_wl.c:1696` | `int freedom_wl_host_probe(FreedomWlConfig *c)` |
| `freedom_wl_keysym` | function | `progs/src/freedom_wl.c:246` | `static long freedom_wl_keysym(FreedomWlConfig *c, long sc)` |
| `freedom_wl_sanitize_utf8` | function | `progs/src/freedom_wl.c:286` | `static long freedom_wl_sanitize_utf8(char *s, long cap)` |
| `freedom_wl_selftest` | function | `progs/src/freedom_wl.c:1613` | `static long freedom_wl_selftest(void)` |
| `freedom_wl_surface_attach` | function | `progs/src/freedom_wl.c:129` | `static long freedom_wl_surface_attach(FreedomWlConfig *c)` |
| `freedom_wl_surface_id` | function | `progs/src/freedom_wl.c:114` | `static long freedom_wl_surface_id(void)` |
| `freedom_wl_sys_kbd` | function | `progs/src/freedom_wl.c:1090` | `static long freedom_wl_sys_kbd(void)` |
| `freedom_wl_sys_kbd_raw` | function | `progs/src/freedom_wl.c:1104` | `static long freedom_wl_sys_kbd_raw(long on)` |
| `freedom_wl_sys_mouse` | function | `progs/src/freedom_wl.c:1083` | `static long freedom_wl_sys_mouse(long *m)` |
| `freedom_wl_sys_palette` | function | `progs/src/freedom_wl.c:1076` | `static long freedom_wl_sys_palette(unsigned char *pal)` |
| `freedom_wl_sys_present` | function | `progs/src/freedom_wl.c:1062` | `static long freedom_wl_sys_present(long buf, long origin)` |
| `freedom_wl_sys_title` | function | `progs/src/freedom_wl.c:1069` | `static long freedom_wl_sys_title(char *t)` |
| `freedom_wl_sys_vga_mode` | function | `progs/src/freedom_wl.c:1097` | `static long freedom_wl_sys_vga_mode(long on)` |
| `freedom_wl_sys_yield` | function | `progs/src/freedom_wl.c:1111` | `static long freedom_wl_sys_yield(void)` |
| `freedom_wl_title_ok` | function | `progs/src/freedom_wl.c:359` | `static long freedom_wl_title_ok(FreedomWlConfig *c, char *t, long n)` |
| `main` | function | `progs/src/freedom_wl.c:1731` | `int main(int argc, char **argv)` |
| `net_dns_resolve` | function | `progs/src/freedom_wl.c:42` | `int net_dns_resolve(const char *host);` |
| `present_buf` | type_alias | `progs/src/freedom_wl.c:76` | `typedef struct FreedomWlConfig { long present_buf;` |
| `tls_close` | function | `progs/src/freedom_wl.c:46` | `void tls_close(int fd);` |
| `tls_handshake` | function | `progs/src/freedom_wl.c:43` | `int tls_handshake(int fd, char *host);` |
| `tls_recv` | function | `progs/src/freedom_wl.c:45` | `int tls_recv(int fd, char *buf, int len);` |
| `tls_send` | function | `progs/src/freedom_wl.c:44` | `int tls_send(int fd, char *buf, int len);` |
| `wl_append` | function | `progs/src/freedom_wl.c:404` | `static long wl_append(char *dst, long pos, char *src, long cap)` |
| `wl_browse` | function | `progs/src/freedom_wl.c:1532` | `static long wl_browse(FreedomWlConfig *c)` |
| `wl_ci_contains` | function | `progs/src/freedom_wl.c:453` | `static long wl_ci_contains(char *s, char *needle)` |
| `wl_ci_lower` | function | `progs/src/freedom_wl.c:427` | `static long wl_ci_lower(long ch)` |
| `wl_ci_starts` | function | `progs/src/freedom_wl.c:435` | `static long wl_ci_starts(char *s, char *pre)` |
| `wl_copy` | function | `progs/src/freedom_wl.c:370` | `static long wl_copy(char *dst, char *src, long cap)` |
| `wl_fetch_raw` | function | `progs/src/freedom_wl.c:1210` | `static long wl_fetch_raw(FreedomWlConfig *c, char *host, char *path, long port, long secure)` |
| `wl_filter_wrap` | function | `progs/src/freedom_wl.c:708` | `static long wl_filter_wrap(FreedomWlConfig *c, char *body, long n, char *lines, long maxlines, lo...` |
| `wl_has_scheme` | function | `progs/src/freedom_wl.c:467` | `static long wl_has_scheme(char *s)` |
| `wl_looks_like_url` | function | `progs/src/freedom_wl.c:493` | `static long wl_looks_like_url(char *s)` |
| `wl_make_search` | function | `progs/src/freedom_wl.c:512` | `static long wl_make_search(char *out, char *query, long cap)` |
| `wl_parse_headers` | function | `progs/src/freedom_wl.c:1118` | `static long wl_parse_headers(FreedomWlConfig *c, char *hdr, long *status, long *clen, long *hascl...` |
| `wl_render` | function | `progs/src/freedom_wl.c:1445` | `static long wl_render(FreedomWlConfig *c, long off)` |
| `wl_resolve_redirect` | function | `progs/src/freedom_wl.c:609` | `static long wl_resolve_redirect(FreedomWlConfig *c, char *loc, long secure, char *host, char *pat...` |
| `wl_scroll_clamp` | function | `progs/src/freedom_wl.c:689` | `static long wl_scroll_clamp(FreedomWlConfig *c, long off, long nlines)` |
| `wl_split_url` | function | `progs/src/freedom_wl.c:544` | `static long wl_split_url(FreedomWlConfig *c, char *url, char *host, char *path, long *port, long ...` |
| `wl_status_text` | function | `progs/src/freedom_wl.c:951` | `static long wl_status_text(FreedomWlConfig *c, char *host, long nbytes, long off, long nlines, ch...` |
| `wl_strlen` | function | `progs/src/freedom_wl.c:388` | `static long wl_strlen(char *s, long cap)` |
| `errno` | variable | `progs/src/ftest.c:10` | `extern int errno;` |
| `exit` | function | `progs/src/ftest.c:7` | `extern void exit(int code);` |
| `fopen` | function | `progs/src/ftest.c:11` | `extern void *fopen(const char *path, const char *mode);` |
| `fprintf` | function | `progs/src/ftest.c:4` | `extern int fprintf(void *stream, const char *fmt, ...);` |
| `main` | function | `progs/src/ftest.c:13` | `int main(int argc, char **argv)` |
| `printf` | function | `progs/src/ftest.c:6` | `extern int printf(const char *fmt, ...);` |
| `snprintf` | function | `progs/src/ftest.c:5` | `extern int snprintf(char *buf, unsigned long size, const char *fmt, ...);` |
| `stderr` | variable | `progs/src/ftest.c:9` | `extern void *stderr;` |
| `stdout` | variable | `progs/src/ftest.c:8` | `extern void *stdout;` |
| `main` | function | `progs/src/hello.c:4` | `int main(int argc, char **argv)` |
| `printf` | function | `progs/src/hello.c:2` | `extern int printf(const char *fmt, ...);` |
| `atoi` | function | `progs/src/http.c:18` | `int atoi(char *s)` |
| `close` | function | `progs/src/http.c:10` | `int close(int fd);` |
| `connect` | function | `progs/src/http.c:6` | `int connect(int fd, void *addr, int addrlen);` |
| `kernel` | function | `progs/src/http.c:3` | `* Hostnames are resolved by the kernel (net_dns_resolve syscall). */ int socket(int domain, int type, int proto);` |
| `main` | function | `progs/src/http.c:29` | `int main(int argc, char **argv)` |
| `net_dns_resolve` | function | `progs/src/http.c:11` | `int net_dns_resolve(const char *host);` |
| `printf` | function | `progs/src/http.c:13` | `int printf(char *fmt, ...);` |
| `putchar` | function | `progs/src/http.c:15` | `int putchar(int c);` |
| `puts` | function | `progs/src/http.c:12` | `int puts(char *s);` |
| `recvfrom` | function | `progs/src/http.c:8` | `int recvfrom(int fd, char *buf, int len, int flags, void *from, int *fromlen);` |
| `sendto` | function | `progs/src/http.c:7` | `int sendto(int fd, char *buf, int len, int flags, void *to, int tolen);` |
| `shutdown` | function | `progs/src/http.c:9` | `int shutdown(int fd, int how);` |
| `strlen` | function | `progs/src/http.c:14` | `int strlen(char *s);` |
| `JS_ARR` | macro | `progs/src/json.c:35` | `#define JS_ARR` |
| `JS_BOOL` | macro | `progs/src/json.c:31` | `#define JS_BOOL` |
| `JS_EXIT_FAIL` | macro | `progs/src/json.c:39` | `#define JS_EXIT_FAIL` |
| `JS_EXIT_OK` | macro | `progs/src/json.c:38` | `#define JS_EXIT_OK` |
| `JS_MAX_NODES` | macro | `progs/src/json.c:27` | `#define JS_MAX_NODES` |
| `JS_NULL` | macro | `progs/src/json.c:30` | `#define JS_NULL` |
| `JS_NUM` | macro | `progs/src/json.c:32` | `#define JS_NUM` |
| `JS_OBJ` | macro | `progs/src/json.c:34` | `#define JS_OBJ` |
| `JS_POOL` | macro | `progs/src/json.c:28` | `#define JS_POOL` |
| `JS_SEEK_END` | macro | `progs/src/json.c:37` | `#define JS_SEEK_END` |
| `JS_STR` | macro | `progs/src/json.c:33` | `#define JS_STR` |
| `fclose` | function | `progs/src/json.c:21` | `int fclose();` |
| `fopen` | function | `progs/src/json.c:20` | `void *fopen();` |
| `fread` | function | `progs/src/json.c:22` | `int fread();` |
| `free` | function | `progs/src/json.c:14` | `void free();` |
| `fseek` | function | `progs/src/json.c:23` | `int fseek();` |
| `ftell` | function | `progs/src/json.c:24` | `int ftell();` |
| `js_array_at` | function | `progs/src/json.c:357` | `static int js_array_at(int arr, int idx)` |
| `js_find_member` | function | `progs/src/json.c:347` | `static int js_find_member(int obj, const char *key)` |
| `js_indent` | function | `progs/src/json.c:281` | `static void js_indent(int n)` |
| `js_key_match` | function | `progs/src/json.c:143` | `static int js_key_match(int child, const char *key)` |
| `js_new` | function | `progs/src/json.c:76` | `static int js_new(void)` |
| `js_parse_array` | function | `progs/src/json.c:182` | `static int js_parse_array(void)` |
| `js_parse_number` | function | `progs/src/json.c:133` | `static int js_parse_number(void)` |
| `js_parse_object` | function | `progs/src/json.c:147` | `static int js_parse_object(void)` |
| `js_parse_string` | function | `progs/src/json.c:97` | `static int js_parse_string(void)` |
| `js_parse_value` | function | `progs/src/json.c:211` | `static int js_parse_value(void)` |
| `js_peek` | function | `progs/src/json.c:89` | `static int js_peek(void)` |
| `js_print_str` | function | `progs/src/json.c:286` | `static void js_print_str(const char *s)` |
| `js_print_value` | function | `progs/src/json.c:303` | `static void js_print_value(int node, int depth)` |
| `js_query` | function | `progs/src/json.c:369` | `static int js_query(int root, const char *path)` |
| `js_read_all` | function | `progs/src/json.c:58` | `static char *js_read_all(const char *name, int *len)` |
| `js_skip_ws` | function | `progs/src/json.c:81` | `static void js_skip_ws(void)` |
| `js_str` | function | `progs/src/json.c:5` | `* members keep their key in js_str (the member value node) and their value * in the node itself, and object members...` |
| `main` | function | `progs/src/json.c:401` | `int main(int argc, char **argv)` |
| `printf` | function | `progs/src/json.c:15` | `int printf();` |
| `putchar` | function | `progs/src/json.c:16` | `int putchar();` |
| `puts` | function | `progs/src/json.c:17` | `int puts();` |
| `rewind` | function | `progs/src/json.c:25` | `void rewind();` |
| `strcmp` | function | `progs/src/json.c:19` | `int strcmp();` |
| `strlen` | function | `progs/src/json.c:18` | `int strlen();` |
| `_start` | function | `progs/src/kmem.c:18` | `void _start(void)` |
| `exit_now` | function | `progs/src/kmem.c:14` | `static void exit_now(long code)` |
| `syscall3` | function | `progs/src/kmem.c:7` | `static long syscall3(long n, long a1, long a2, long a3)` |
| `main` | function | `progs/src/ldhello.c:1` | `int main(void)` |
| `LXABI_A6_MAGIC` | macro | `progs/src/lxabi.c:55` | `#define LXABI_A6_MAGIC` |
| `LXABI_CHILD_BAD` | macro | `progs/src/lxabi.c:56` | `#define LXABI_CHILD_BAD` |
| `LXABI_CHILD_DELAY_MS` | macro | `progs/src/lxabi.c:41` | `#define LXABI_CHILD_DELAY_MS` |
| `LXABI_CLOCK_SKEW_S` | macro | `progs/src/lxabi.c:51` | `#define LXABI_CLOCK_SKEW_S` |
| `LXABI_CLONE_NR` | macro | `progs/src/lxabi.c:53` | `#define LXABI_CLONE_NR` |
| `LXABI_CLOSE_RANGE_NR` | macro | `progs/src/lxabi.c:59` | `#define LXABI_CLOSE_RANGE_NR` |
| `LXABI_COW_WORD` | macro | `progs/src/lxabi.c:61` | `#define LXABI_COW_WORD` |
| `LXABI_DETACHED` | macro | `progs/src/lxabi.c:44` | `#define LXABI_DETACHED` |
| `LXABI_EPOCH_2023` | macro | `progs/src/lxabi.c:50` | `#define LXABI_EPOCH_2023` |
| `LXABI_GROUP_EXIT_CODE` | macro | `progs/src/lxabi.c:46` | `#define LXABI_GROUP_EXIT_CODE` |
| `LXABI_MAX_SANE_CPUS` | macro | `progs/src/lxabi.c:48` | `#define LXABI_MAX_SANE_CPUS` |
| `LXABI_MKDIR_FILE` | macro | `progs/src/lxabi.c:58` | `#define LXABI_MKDIR_FILE` |
| `LXABI_MKDIR_PATH` | macro | `progs/src/lxabi.c:57` | `#define LXABI_MKDIR_PATH` |
| `LXABI_PAGE` | macro | `progs/src/lxabi.c:60` | `#define LXABI_PAGE` |
| `LXABI_REG_PROBE_WORDS` | macro | `progs/src/lxabi.c:52` | `#define LXABI_REG_PROBE_WORDS` |
| `LXABI_SIGCHLD` | macro | `progs/src/lxabi.c:54` | `#define LXABI_SIGCHLD` |
| `LXABI_SLEEP_MS` | macro | `progs/src/lxabi.c:47` | `#define LXABI_SLEEP_MS` |
| `LXABI_THREADS` | macro | `progs/src/lxabi.c:42` | `#define LXABI_THREADS` |
| `LXABI_THREAD_ITERS` | macro | `progs/src/lxabi.c:43` | `#define LXABI_THREAD_ITERS` |
| `LXABI_TIMEDWAIT_MS` | macro | `progs/src/lxabi.c:49` | `#define LXABI_TIMEDWAIT_MS` |
| `LXABI_WAIT_SPINS` | macro | `progs/src/lxabi.c:45` | `#define LXABI_WAIT_SPINS` |
| `_GNU_SOURCE` | macro | `progs/src/lxabi.c:17` | `#define _GNU_SOURCE` |
| `abort_from_worker_body` | function | `progs/src/lxabi.c:555` | `static void abort_from_worker_body(void)` |
| `busy_wait_ms` | function | `progs/src/lxabi.c:81` | `static void busy_wait_ms(long ms)` |
| `check_close_range` | function | `progs/src/lxabi.c:443` | `static void check_close_range(void)` |
| `check_condvar` | function | `progs/src/lxabi.c:285` | `static void check_condvar(void)` |
| `check_detached_reaped` | function | `progs/src/lxabi.c:251` | `static void check_detached_reaped(void)` |
| `check_eventfd` | function | `progs/src/lxabi.c:418` | `static void check_eventfd(void)` |
| `check_fork_cow_kernel_write` | function | `progs/src/lxabi.c:160` | `static void check_fork_cow_kernel_write(void)` |
| `check_fork_registers` | function | `progs/src/lxabi.c:138` | `static void check_fork_registers(void)` |
| `check_getdents64` | function | `progs/src/lxabi.c:687` | `static void check_getdents64(void)` |
| `check_limits` | function | `progs/src/lxabi.c:478` | `static void check_limits(void)` |
| `check_mkdir` | function | `progs/src/lxabi.c:464` | `static void check_mkdir(void)` |
| `check_pipe2_flags` | function | `progs/src/lxabi.c:307` | `static void check_pipe2_flags(void)` |
| `check_pipe_blocking` | function | `progs/src/lxabi.c:334` | `static void check_pipe_blocking(void)` |
| `check_pipe_epipe` | function | `progs/src/lxabi.c:356` | `static void check_pipe_epipe(void)` |
| `check_poll` | function | `progs/src/lxabi.c:394` | `static void check_poll(void)` |
| `check_sleep` | function | `progs/src/lxabi.c:500` | `static void check_sleep(void)` |
| `check_threads` | function | `progs/src/lxabi.c:215` | `static void check_threads(void)` |
| `check_time` | function | `progs/src/lxabi.c:455` | `static void check_time(void)` |
| `check_uid_gid` | function | `progs/src/lxabi.c:642` | `static void check_uid_gid(void)` |
| `check_writev_pipe` | function | `progs/src/lxabi.c:382` | `static void check_writev_pipe(void)` |
| `child_status` | function | `progs/src/lxabi.c:535` | `static int child_status(void (*body)(void))` |
| `copy_dentry_name` | function | `progs/src/lxabi.c:680` | `static void copy_dentry_name(char *dst, size_t cap, const char *src)` |
| `detached_worker` | function | `progs/src/lxabi.c:245` | `static void *detached_worker(void *arg)` |
| `exit_group_from_worker_body` | function | `progs/src/lxabi.c:567` | `static void exit_group_from_worker_body(void)` |
| `fork_probe` | function | `progs/src/lxabi.c:95` | `static void fork_probe(uint64_t *out)` |
| `lxabi_exit_group_worker` | function | `progs/src/lxabi.c:561` | `static void *lxabi_exit_group_worker(void *arg)` |
| `lxabi_sleeper` | function | `progs/src/lxabi.c:527` | `static void *lxabi_sleeper(void *arg)` |
| `main` | function | `progs/src/lxabi.c:754` | `int main(void)` |
| `mono_us` | function | `progs/src/lxabi.c:491` | `static long mono_us(void)` |
| `now_ms` | function | `progs/src/lxabi.c:75` | `static long now_ms(void)` |
| `process` | function | `progs/src/lxabi.c:581` | `* process (never a kernel panic), and kill(pid, 0) or a harmless signal  * leaves the target aliv...` |
| `regs_match` | function | `progs/src/lxabi.c:132` | `static int regs_match(const uint64_t *r)` |
| `report` | function | `progs/src/lxabi.c:65` | `static void report(const char *name, int ok, const char *detail)` |
| `signaller` | function | `progs/src/lxabi.c:275` | `static void *signaller(void *arg)` |
| `thread_result` | struct | `progs/src/lxabi.c:195` | `` |
| `tls_seen` | type_alias | `progs/src/lxabi.c:194` | `typedef struct thread_result { long tls_seen;` |
| `wild_jump_body` | function | `progs/src/lxabi.c:573` | `static void wild_jump_body(void)` |
| `worker` | function | `progs/src/lxabi.c:201` | `static void *worker(void *arg)` |
| `SYS_exit` | macro | `progs/src/lxhello.c:21` | `#define SYS_exit` |
| `SYS_write` | macro | `progs/src/lxhello.c:20` | `#define SYS_write` |
| `lmain` | function | `progs/src/lxhello.c:46` | `int lmain(long argc, char **argv)` |
| `lx_strlen` | function | `progs/src/lxhello.c:23` | `static unsigned long lx_strlen(const char *s)` |
| `lx_syscall3` | function | `progs/src/lxhello.c:11` | `static long lx_syscall3(long n, long a1, long a2, long a3)` |
| `lx_write` | function | `progs/src/lxhello.c:29` | `static void lx_write(const char *s)` |
| `lx_write_int` | function | `progs/src/lxhello.c:33` | `static void lx_write_int(long v)` |

Next: [SYMBOLS_p23.md](SYMBOLS_p23.md)
