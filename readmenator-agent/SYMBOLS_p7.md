# Symbols (page 7 of 26)
Previous: [SYMBOLS_p6.md](SYMBOLS_p6.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `TLS_MSG_MAX` | macro | `headers/tls.h:13` | `#define TLS_MSG_MAX` |
| `TLS_PLAIN_MAX` | macro | `headers/tls.h:14` | `#define TLS_PLAIN_MAX` |
| `TLS_READ_TIMEOUT_MS` | macro | `headers/tls.h:51` | `#define TLS_READ_TIMEOUT_MS` |
| `TLS_REC_HEADER` | macro | `headers/tls.h:11` | `#define TLS_REC_HEADER` |
| `TLS_REC_MAX` | macro | `headers/tls.h:12` | `#define TLS_REC_MAX` |
| `TLS_ROOT_COUNT` | macro | `headers/tls.h:68` | `#define TLS_ROOT_COUNT` |
| `TLS_SIG_ECDSA_P256_SHA256` | macro | `headers/tls.h:33` | `#define TLS_SIG_ECDSA_P256_SHA256` |
| `TLS_SIG_ECDSA_P384_SHA384` | macro | `headers/tls.h:34` | `#define TLS_SIG_ECDSA_P384_SHA384` |
| `TLS_SIG_RSA_PKCS1_SHA256` | macro | `headers/tls.h:32` | `#define TLS_SIG_RSA_PKCS1_SHA256` |
| `TLS_VERSION_TLS10` | macro | `headers/tls.h:16` | `#define TLS_VERSION_TLS10` |
| `TLS_VERSION_TLS12` | macro | `headers/tls.h:15` | `#define TLS_VERSION_TLS12` |
| `aes128_encrypt_block` | function | `headers/tls.h:184` | `void aes128_encrypt_block(const unsigned char key[16], const unsigned char in[16], unsigned char out[16]);` |
| `aes128_gcm_open` | function | `headers/tls.h:197` | `int aes128_gcm_open(const unsigned char key[16], const unsigned char salt[4], unsigned long long seq, const unsigned...` |
| `aes128_gcm_open_core` | function | `headers/tls.h:213` | `int aes128_gcm_open_core(const unsigned char key[16], const unsigned char nonce[12], const unsigned char *aad...` |
| `aes128_gcm_seal` | function | `headers/tls.h:189` | `int aes128_gcm_seal(const unsigned char key[16], const unsigned char salt[4], unsigned long long seq, const unsigned...` |
| `aes128_gcm_seal_core` | function | `headers/tls.h:208` | `int aes128_gcm_seal_core(const unsigned char key[16], const unsigned char nonce[12], const unsigned char *aad...` |
| `ecdsa_verify` | function | `headers/tls.h:243` | `int ecdsa_verify(int curve, const unsigned char pub_x[], const unsigned char pub_y[], const unsigned char digest[]...` |
| `hmac_sha256` | function | `headers/tls.h:174` | `void hmac_sha256(const unsigned char *key, unsigned klen, const unsigned char *data, unsigned dlen, unsigned char...` |
| `now` | function | `headers/tls.h:267` | `* window against now (days since epoch). Returns 0 on success. */ int tls_x509_verify_chain(const unsigned char...` |
| `p256_ecdh` | function | `headers/tls.h:231` | `int p256_ecdh(const unsigned char priv[32], const unsigned char peer_x[32], const unsigned char peer_y[32], unsigned...` |
| `p256_point_valid` | function | `headers/tls.h:236` | `int p256_point_valid(const unsigned char x[32], const unsigned char y[32]);` |
| `p256_pub` | function | `headers/tls.h:237` | `int p256_pub(const unsigned char priv[32], unsigned char x[32], unsigned char y[32]);` |
| `p256_scalar_mult` | function | `headers/tls.h:222` | `int p256_scalar_mult(const unsigned char scalar[32], const unsigned char qx[32], const unsigned char qy[32]...` |
| `p256_scalar_valid` | function | `headers/tls.h:239` | `int p256_scalar_valid(const unsigned char scalar[32]);` |
| `p384_scalar_mult` | function | `headers/tls.h:225` | `int p384_scalar_mult(const unsigned char scalar[48], const unsigned char qx[48], const unsigned char qy[48]...` |
| `rsa_pkcs1_verify_sha256` | function | `headers/tls.h:249` | `int rsa_pkcs1_verify_sha256(const unsigned char *n, unsigned n_len, const unsigned char *e, unsigned e_len, const...` |
| `rsa_pkcs1_verify_sha384` | function | `headers/tls.h:253` | `int rsa_pkcs1_verify_sha384(const unsigned char *n, unsigned n_len, const unsigned char *e, unsigned e_len, const...` |
| `sha256` | function | `headers/tls.h:171` | `void sha256(const unsigned char *data, unsigned len, unsigned char out[32]);` |
| `sha256_ctx` | struct | `headers/tls.h:79` | `` |
| `sha256_final` | function | `headers/tls.h:170` | `void sha256_final(struct sha256_ctx *c, unsigned char out[32]);` |
| `sha256_init` | function | `headers/tls.h:168` | `void sha256_init(struct sha256_ctx *c);` |
| `sha256_update` | function | `headers/tls.h:169` | `void sha256_update(struct sha256_ctx *c, const unsigned char *data, unsigned len);` |
| `sha384` | function | `headers/tls.h:172` | `void sha384(const unsigned char *data, unsigned len, unsigned char out[48]);` |
| `tls_free_fd` | function | `headers/tls.h:293` | `static inline void tls_free_fd(int fd)` |
| `tls_handshake` | function | `headers/tls.h:277` | `int tls_handshake(int fd, const char *host);` |
| `tls_prf` | function | `headers/tls.h:179` | `void tls_prf(const unsigned char *secret, unsigned secret_len, const char *label, const unsigned char *seed...` |
| `tls_pubkey` | struct | `headers/tls.h:85` | `` |
| `tls_recv` | function | `headers/tls.h:284` | `int tls_recv(int fd, char *buf, int len);` |
| `tls_root` | struct | `headers/tls.h:70` | `` |
| `tls_roots` | variable | `headers/tls.h:75` | `extern const struct tls_root tls_roots[TLS_ROOT_COUNT];` |
| `tls_send` | function | `headers/tls.h:280` | `int tls_send(int fd, const char *buf, int len);` |
| `tls_session` | struct | `headers/tls.h:95` | `` |
| `tls_sys_handshake` | function | `headers/tls.h:297` | `long tls_sys_handshake(long fd, long host);` |
| `tls_sys_recv` | function | `headers/tls.h:299` | `long tls_sys_recv(long fd, long buf, long len);` |
| `tls_sys_send` | function | `headers/tls.h:298` | `long tls_sys_send(long fd, long buf, long len);` |
| `tls_x509_parse_pubkey` | function | `headers/tls.h:261` | `int tls_x509_parse_pubkey(const unsigned char *der, unsigned len, struct tls_pubkey *pk);` |
| `TLS_CLOSE` | macro | `headers/tls_port.h:38` | `#define TLS_CLOSE` |
| `TLS_CLOSE` | macro | `headers/tls_port.h:89` | `#define TLS_CLOSE` |
| `TLS_CLOSE` | macro | `headers/tls_port.h:114` | `#define TLS_CLOSE` |
| `TLS_FD_MAX` | macro | `headers/tls_port.h:18` | `#define TLS_FD_MAX` |
| `TLS_FD_MAX` | macro | `headers/tls_port.h:71` | `#define TLS_FD_MAX` |
| `TLS_FD_MAX` | macro | `headers/tls_port.h:115` | `#define TLS_FD_MAX` |
| `TLS_FREE` | macro | `headers/tls_port.h:22` | `#define TLS_FREE(p)` |
| `TLS_FREE` | macro | `headers/tls_port.h:75` | `#define TLS_FREE(p)` |
| `TLS_FREE` | macro | `headers/tls_port.h:105` | `#define TLS_FREE(p)` |
| `TLS_MALLOC` | macro | `headers/tls_port.h:21` | `#define TLS_MALLOC(n)` |
| `TLS_MALLOC` | macro | `headers/tls_port.h:74` | `#define TLS_MALLOC(n)` |
| `TLS_MALLOC` | macro | `headers/tls_port.h:104` | `#define TLS_MALLOC(n)` |
| `TLS_MEMCMP` | macro | `headers/tls_port.h:25` | `#define TLS_MEMCMP` |
| `TLS_MEMCMP` | macro | `headers/tls_port.h:78` | `#define TLS_MEMCMP` |
| `TLS_MEMCMP` | macro | `headers/tls_port.h:108` | `#define TLS_MEMCMP` |
| `TLS_MEMCPY` | macro | `headers/tls_port.h:23` | `#define TLS_MEMCPY` |
| `TLS_MEMCPY` | macro | `headers/tls_port.h:76` | `#define TLS_MEMCPY` |
| `TLS_MEMCPY` | macro | `headers/tls_port.h:106` | `#define TLS_MEMCPY` |
| `TLS_MEMSET` | macro | `headers/tls_port.h:24` | `#define TLS_MEMSET` |
| `TLS_MEMSET` | macro | `headers/tls_port.h:77` | `#define TLS_MEMSET` |
| `TLS_MEMSET` | macro | `headers/tls_port.h:107` | `#define TLS_MEMSET` |
| `TLS_PORT_H` | macro | `headers/tls_port.h:2` | `#define TLS_PORT_H` |
| `TLS_PRINTF` | macro | `headers/tls_port.h:20` | `#define TLS_PRINTF` |
| `TLS_PRINTF` | macro | `headers/tls_port.h:73` | `#define TLS_PRINTF` |
| `TLS_PRINTF` | macro | `headers/tls_port.h:103` | `#define TLS_PRINTF` |
| `TLS_RECV` | macro | `headers/tls_port.h:36` | `#define TLS_RECV` |
| `TLS_RECV` | macro | `headers/tls_port.h:87` | `#define TLS_RECV` |
| `TLS_RECV` | macro | `headers/tls_port.h:112` | `#define TLS_RECV` |
| `TLS_RECV_TIMEOUT` | macro | `headers/tls_port.h:37` | `#define TLS_RECV_TIMEOUT` |
| `TLS_RECV_TIMEOUT` | macro | `headers/tls_port.h:88` | `#define TLS_RECV_TIMEOUT` |
| `TLS_RECV_TIMEOUT` | macro | `headers/tls_port.h:113` | `#define TLS_RECV_TIMEOUT` |
| `TLS_SEND` | macro | `headers/tls_port.h:35` | `#define TLS_SEND` |
| `TLS_SEND` | macro | `headers/tls_port.h:86` | `#define TLS_SEND` |
| `TLS_SEND` | macro | `headers/tls_port.h:111` | `#define TLS_SEND` |
| `TLS_STRLEN` | macro | `headers/tls_port.h:26` | `#define TLS_STRLEN` |
| `TLS_STRLEN` | macro | `headers/tls_port.h:79` | `#define TLS_STRLEN` |
| `TLS_STRLEN` | macro | `headers/tls_port.h:109` | `#define TLS_STRLEN` |
| `gettimeofday` | function | `headers/tls_port.h:64` | `* gettimeofday(96) and entropy from /dev/urandom with a time/pid * fallback. Session slots are indexed by raw OS fd...` |
| `sockets` | function | `headers/tls_port.h:62` | `* sockets (glibc maps socket/connect/send/recv/poll onto the MiniOS * Linux ABI numbers the kernel implements);` |
| `syscall` | function | `headers/tls_port.h:95` | `* the MiniOS DNS syscall (200, invoked sig-0-safe). 0 on success. */ int tls_u_resolve(const char *host, unsigned...` |
| `these` | function | `headers/tls_port.h:29` | `* of these (tls_test.c). */ extern int tls_test_send(int fd, const char *buf, int len);` |
| `tls_now_days` | function | `headers/tls_port.h:40` | `static inline long tls_now_days(void)` |
| `tls_random` | function | `headers/tls_port.h:44` | `static inline void tls_random(unsigned char *out, unsigned len)` |
| `tls_test_close` | function | `headers/tls_port.h:33` | `extern void tls_test_close(int fd);` |
| `tls_test_recv` | function | `headers/tls_port.h:31` | `extern int tls_test_recv(int fd, char *buf, int len);` |
| `tls_test_recv_timeout` | function | `headers/tls_port.h:32` | `extern int tls_test_recv_timeout(int fd, char *buf, int len, unsigned long ms);` |
| `tls_u_close` | function | `headers/tls_port.h:84` | `void tls_u_close(int fd);` |
| `tls_u_recv` | function | `headers/tls_port.h:82` | `int tls_u_recv(int fd, char *buf, int len);` |
| `tls_u_recv_timeout` | function | `headers/tls_port.h:83` | `int tls_u_recv_timeout(int fd, char *buf, int len, unsigned long ms);` |
| `COL_BG` | macro | `headers/vga_fb.h:83` | `#define COL_BG` |
| `COL_BLACK` | macro | `headers/vga_fb.h:82` | `#define COL_BLACK` |
| `COL_BORDER` | macro | `headers/vga_fb.h:91` | `#define COL_BORDER` |
| `COL_HIGHLIGHT` | macro | `headers/vga_fb.h:94` | `#define COL_HIGHLIGHT` |
| `COL_SCROLLBAR` | macro | `headers/vga_fb.h:95` | `#define COL_SCROLLBAR` |
| `COL_SCROLL_THUMB` | macro | `headers/vga_fb.h:96` | `#define COL_SCROLL_THUMB` |
| `COL_SHADOW` | macro | `headers/vga_fb.h:93` | `#define COL_SHADOW` |
| `COL_TASKBAR` | macro | `headers/vga_fb.h:84` | `#define COL_TASKBAR` |
| `COL_TASKBAR_TXT` | macro | `headers/vga_fb.h:85` | `#define COL_TASKBAR_TXT` |
| `COL_TERMINAL` | macro | `headers/vga_fb.h:88` | `#define COL_TERMINAL` |
| `COL_TERM_CUR` | macro | `headers/vga_fb.h:90` | `#define COL_TERM_CUR` |
| `COL_TERM_TXT` | macro | `headers/vga_fb.h:89` | `#define COL_TERM_TXT` |
| `COL_TITLEBAR` | macro | `headers/vga_fb.h:86` | `#define COL_TITLEBAR` |
| `COL_TITLE_TXT` | macro | `headers/vga_fb.h:87` | `#define COL_TITLE_TXT` |
| `COL_WHITE` | macro | `headers/vga_fb.h:92` | `#define COL_WHITE` |
| `DOOM_BACKBUF_ADDR` | macro | `headers/vga_fb.h:48` | `#define DOOM_BACKBUF_ADDR` |
| `DOOM_H` | macro | `headers/vga_fb.h:47` | `#define DOOM_H` |
| `DOOM_W` | macro | `headers/vga_fb.h:46` | `#define DOOM_W` |
| `FB_ADDR` | macro | `headers/vga_fb.h:22` | `#define FB_ADDR` |
| `FONT_H` | macro | `headers/vga_fb.h:108` | `#define FONT_H` |
| `FONT_W` | macro | `headers/vga_fb.h:107` | `#define FONT_W` |
| `GFX_TITLE_DEFAULT` | macro | `headers/vga_fb.h:52` | `#define GFX_TITLE_DEFAULT` |
| `NK_BACKBUF_ADDR` | macro | `headers/vga_fb.h:69` | `#define NK_BACKBUF_ADDR` |
| `NK_H` | macro | `headers/vga_fb.h:68` | `#define NK_H` |
| `NK_RGB_ADDR` | macro | `headers/vga_fb.h:73` | `#define NK_RGB_ADDR` |
| `NK_RGB_BYTES` | macro | `headers/vga_fb.h:74` | `#define NK_RGB_BYTES` |
| `NK_W` | macro | `headers/vga_fb.h:67` | `#define NK_W` |
| `SB_LINE_MAX` | macro | `headers/vga_fb.h:174` | `#define SB_LINE_MAX` |
| `SB_MAX_LINES` | macro | `headers/vga_fb.h:173` | `#define SB_MAX_LINES` |
| `SCROLLBAR_PAD` | macro | `headers/vga_fb.h:143` | `#define SCROLLBAR_PAD` |
| `SCROLLBAR_W` | macro | `headers/vga_fb.h:142` | `#define SCROLLBAR_W` |
| `SYS_DOOM_FRAME` | function | `headers/vga_fb.h:44` | `* and calls SYS_DOOM_FRAME (211) to have the kernel composite it onto the * desktop at its native resolution, so the...` |
| `SYS_NK_FRAME` | function | `headers/vga_fb.h:63` | `* SYS_NK_FRAME (220);` |
| `TASKBAR_BTN_W` | macro | `headers/vga_fb.h:123` | `#define TASKBAR_BTN_W` |
| `TASKBAR_CLOCK_CH` | macro | `headers/vga_fb.h:119` | `#define TASKBAR_CLOCK_CH` |
| `TASKBAR_H` | macro | `headers/vga_fb.h:117` | `#define TASKBAR_H` |
| `TASKBAR_ICON_W` | macro | `headers/vga_fb.h:122` | `#define TASKBAR_ICON_W` |
| `TASKBAR_KBD_CH` | macro | `headers/vga_fb.h:125` | `#define TASKBAR_KBD_CH` |
| `TASKBAR_KBD_W` | macro | `headers/vga_fb.h:126` | `#define TASKBAR_KBD_W` |
| `TASKBAR_PAD` | macro | `headers/vga_fb.h:118` | `#define TASKBAR_PAD` |
| `TASKBAR_THEME_CH` | macro | `headers/vga_fb.h:128` | `#define TASKBAR_THEME_CH` |
| `TASKBAR_THEME_W` | macro | `headers/vga_fb.h:129` | `#define TASKBAR_THEME_W` |
| `TASKBAR_VOL_CH` | macro | `headers/vga_fb.h:120` | `#define TASKBAR_VOL_CH` |
| `TASKBAR_VOL_STEP` | macro | `headers/vga_fb.h:121` | `#define TASKBAR_VOL_STEP` |
| `TERM_MAX_COLS` | macro | `headers/vga_fb.h:113` | `#define TERM_MAX_COLS` |
| `TERM_MAX_ROWS` | macro | `headers/vga_fb.h:114` | `#define TERM_MAX_ROWS` |
| `TILING_BOTTOM` | macro | `headers/vga_fb.h:135` | `#define TILING_BOTTOM` |
| `TILING_BOTTOM_LEFT` | macro | `headers/vga_fb.h:138` | `#define TILING_BOTTOM_LEFT` |
| `TILING_BOTTOM_RIGHT` | macro | `headers/vga_fb.h:139` | `#define TILING_BOTTOM_RIGHT` |
| `TILING_LEFT` | macro | `headers/vga_fb.h:132` | `#define TILING_LEFT` |
| `TILING_RIGHT` | macro | `headers/vga_fb.h:133` | `#define TILING_RIGHT` |
| `TILING_TOP` | macro | `headers/vga_fb.h:134` | `#define TILING_TOP` |
| `TILING_TOP_LEFT` | macro | `headers/vga_fb.h:136` | `#define TILING_TOP_LEFT` |
| `TILING_TOP_RIGHT` | macro | `headers/vga_fb.h:137` | `#define TILING_TOP_RIGHT` |
| `VGA_FB_H` | macro | `headers/vga_fb.h:2` | `#define VGA_FB_H` |
| `WALLPAPER_PATH` | macro | `headers/vga_fb.h:103` | `#define WALLPAPER_PATH` |
| `WALL_PAL_BASE` | macro | `headers/vga_fb.h:104` | `#define WALL_PAL_BASE` |
| `WALL_PAL_SIZE` | macro | `headers/vga_fb.h:105` | `#define WALL_PAL_SIZE` |
| `WM_BTN_CLOSE` | macro | `headers/vga_fb.h:153` | `#define WM_BTN_CLOSE` |
| `WM_BTN_H` | macro | `headers/vga_fb.h:149` | `#define WM_BTN_H` |
| `WM_BTN_MAX` | macro | `headers/vga_fb.h:152` | `#define WM_BTN_MAX` |
| `WM_BTN_MIN` | macro | `headers/vga_fb.h:151` | `#define WM_BTN_MIN` |
| `WM_BTN_PAD` | macro | `headers/vga_fb.h:150` | `#define WM_BTN_PAD` |
| `WM_BTN_W` | macro | `headers/vga_fb.h:148` | `#define WM_BTN_W` |
| `WM_FOCUS_GFX` | macro | `headers/vga_fb.h:222` | `#define WM_FOCUS_GFX` |
| `below` | function | `headers/vga_fb.h:99` | `* file below (800x600 RGB PNG on the ramdisk, produced by * tools/gen_desktop_pngs.py) is decoded once per boot via...` |
| `dock_bounce_counts` | function | `headers/vga_fb.h:253` | `void dock_bounce_counts(unsigned long *kicks, unsigned long *paints);` |
| `dock_click_count` | function | `headers/vga_fb.h:254` | `void dock_click_count(unsigned long *edges);` |
| `dock_pending_active` | function | `headers/vga_fb.h:255` | `int dock_pending_active(void);` |
| `fb_bpp` | variable | `headers/vga_fb.h:26` | `extern int fb_bpp;` |
| `fb_bytes_per_pixel` | function | `headers/vga_fb.h:30` | `int fb_bytes_per_pixel(void);` |
| `fb_height` | variable | `headers/vga_fb.h:24` | `extern int fb_height;` |
| `fb_phys_base` | variable | `headers/vga_fb.h:27` | `extern unsigned long fb_phys_base;` |
| `fb_pitch` | variable | `headers/vga_fb.h:25` | `extern int fb_pitch;` |
| `fb_read_packed` | function | `headers/vga_fb.h:193` | `unsigned long fb_read_packed(int x, int y);` |
| `fb_read_row_packed` | function | `headers/vga_fb.h:218` | `void fb_read_row_packed(int x, int y, unsigned int *dst, int n);` |
| `fb_width` | variable | `headers/vga_fb.h:23` | `extern int fb_width;` |
| `fb_write_packed` | function | `headers/vga_fb.h:194` | `void fb_write_packed(int x, int y, unsigned long rgb);` |
| `fb_write_row_packed` | function | `headers/vga_fb.h:217` | `void fb_write_row_packed(int x, int y, const unsigned int *src, int n);` |
| `fx_melts_completed` | variable | `headers/vga_fb.h:273` | `extern unsigned long fx_melts_completed;` |
| `gfx_frames_composited` | variable | `headers/vga_fb.h:59` | `extern unsigned long gfx_frames_composited;` |
| `gfx_win_title` | variable | `headers/vga_fb.h:50` | `extern const char *gfx_win_title;` |
| `mouse_state` | variable | `headers/vga_fb.h:167` | `extern mouse_state_t mouse_state;` |
| `mouse_state_t` | struct | `headers/vga_fb.h:159` | `` |
| `nk_win_y` | variable | `headers/vga_fb.h:79` | `extern int nk_win_x, nk_win_y;` |
| `pixels` | function | `headers/vga_fb.h:259` | `* are heap buffers of packed pixels (fb_read_packed order), 0 on OOM or a * degenerate rect. A disabled effect or a...` |
| `term_clear` | function | `headers/vga_fb.h:188` | `void term_clear(void);` |
| `term_rows` | variable | `headers/vga_fb.h:156` | `extern int term_x, term_y, term_cols, term_rows;` |
| `vga_fb_active` | variable | `headers/vga_fb.h:282` | `extern int vga_fb_active;` |
| `vga_fb_blit_nk_rgb_window` | function | `headers/vga_fb.h:76` | `void vga_fb_blit_nk_rgb_window(void);` |
| `vga_fb_blit_nk_window` | function | `headers/vga_fb.h:75` | `void vga_fb_blit_nk_window(void);` |
| `vga_fb_boot_config` | function | `headers/vga_fb.h:40` | `void vga_fb_boot_config(void);` |
| `vga_fb_char` | function | `headers/vga_fb.h:184` | `void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg);` |
| `vga_fb_clear` | function | `headers/vga_fb.h:178` | `void vga_fb_clear(void);` |
| `vga_fb_close_active` | function | `headers/vga_fb.h:219` | `int vga_fb_close_active(void);` |
| `vga_fb_draw_desktop` | function | `headers/vga_fb.h:195` | `void vga_fb_draw_desktop(void);` |
| `vga_fb_focus_event` | function | `headers/vga_fb.h:228` | `const wm_notify_event_t *vga_fb_focus_event(void);` |
| `vga_fb_focus_get` | function | `headers/vga_fb.h:225` | `int vga_fb_focus_get(void);` |
| `vga_fb_focus_id` | function | `headers/vga_fb.h:224` | `int vga_fb_focus_id(int id);` |
| `vga_fb_focus_next` | function | `headers/vga_fb.h:223` | `void vga_fb_focus_next(void);` |
| `vga_fb_focus_report` | function | `headers/vga_fb.h:229` | `void vga_fb_focus_report(int before, int source);` |
| `vga_fb_gfx_map_mouse` | function | `headers/vga_fb.h:215` | `void vga_fb_gfx_map_mouse(int *x, int *y);` |
| `vga_fb_gfx_origin` | function | `headers/vga_fb.h:214` | `void vga_fb_gfx_origin(int *x, int *y);` |
| `vga_fb_gfx_set_fullscreen` | function | `headers/vga_fb.h:211` | `int vga_fb_gfx_set_fullscreen(int on);` |
| `vga_fb_gfx_set_hidden` | function | `headers/vga_fb.h:212` | `int vga_fb_gfx_set_hidden(int hide);` |
| `vga_fb_gfx_view_name` | function | `headers/vga_fb.h:213` | `const char *vga_fb_gfx_view_name(void);` |
| `vga_fb_hide_text_cursor` | function | `headers/vga_fb.h:190` | `void vga_fb_hide_text_cursor(void);` |
| `vga_fb_init` | function | `headers/vga_fb.h:177` | `void vga_fb_init(void);` |
| `vga_fb_is_fullscreen` | function | `headers/vga_fb.h:203` | `int vga_fb_is_fullscreen(void);` |
| `vga_fb_is_minimized` | function | `headers/vga_fb.h:202` | `int vga_fb_is_minimized(void);` |
| `vga_fb_layout_cycle` | function | `headers/vga_fb.h:242` | `void vga_fb_layout_cycle(void);` |
| `vga_fb_layout_get` | function | `headers/vga_fb.h:243` | `int vga_fb_layout_get(void);` |
| `vga_fb_layout_name` | function | `headers/vga_fb.h:244` | `const char *vga_fb_layout_name(void);` |
| `vga_fb_layout_set` | function | `headers/vga_fb.h:241` | `int vga_fb_layout_set(int mode);` |
| `vga_fb_list_windows` | function | `headers/vga_fb.h:245` | `void vga_fb_list_windows(void);` |
| `vga_fb_mouse_init` | function | `headers/vga_fb.h:250` | `void vga_fb_mouse_init(void);` |
| `vga_fb_mouse_tick` | function | `headers/vga_fb.h:249` | `void vga_fb_mouse_tick(void);` |
| `vga_fb_move_terminal` | function | `headers/vga_fb.h:197` | `void vga_fb_move_terminal(int dx, int dy);` |
| `vga_fb_nterms_get` | function | `headers/vga_fb.h:237` | `int vga_fb_nterms_get(void);` |
| `vga_fb_pixel` | function | `headers/vga_fb.h:179` | `void vga_fb_pixel(int x, int y, uint8_t color);` |
| `vga_fb_pixel_rgb` | function | `headers/vga_fb.h:182` | `void vga_fb_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b);` |
| `vga_fb_ps2_owner` | function | `headers/vga_fb.h:236` | `int vga_fb_ps2_owner(int pid);` |
| `vga_fb_putc_term` | function | `headers/vga_fb.h:186` | `void vga_fb_putc_term(char c);` |
| `vga_fb_puts_term` | function | `headers/vga_fb.h:187` | `void vga_fb_puts_term(const char *s);` |
| `vga_fb_read_rgb` | function | `headers/vga_fb.h:34` | `unsigned long vga_fb_read_rgb(int x, int y);` |
| `vga_fb_rect` | function | `headers/vga_fb.h:180` | `void vga_fb_rect(int x, int y, int w, int h, uint8_t color);` |
| `vga_fb_rect_rgb` | function | `headers/vga_fb.h:183` | `void vga_fb_rect_rgb(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b);` |
| `vga_fb_reset_default` | function | `headers/vga_fb.h:200` | `void vga_fb_reset_default(void);` |
| `vga_fb_resize` | function | `headers/vga_fb.h:199` | `void vga_fb_resize(int dcols, int drows);` |
| `vga_fb_set_gfx_mode` | function | `headers/vga_fb.h:280` | `void vga_fb_set_gfx_mode(int on);` |
| `vga_fb_set_gfx_palette` | function | `headers/vga_fb.h:38` | `void vga_fb_set_gfx_palette(const unsigned char *pal);` |
| `vga_fb_snap_window` | function | `headers/vga_fb.h:198` | `void vga_fb_snap_window(int zone);` |
| `vga_fb_str` | function | `headers/vga_fb.h:185` | `void vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg);` |
| `vga_fb_term_close_focused` | function | `headers/vga_fb.h:239` | `int vga_fb_term_close_focused(void);` |
| `vga_fb_term_split` | function | `headers/vga_fb.h:238` | `int vga_fb_term_split(void);` |
| `vga_fb_text_cursor` | function | `headers/vga_fb.h:189` | `void vga_fb_text_cursor(int col);` |
| `vga_fb_theme_name` | function | `headers/vga_fb.h:230` | `int vga_fb_theme_name(char *dst, int cap);` |
| `vga_fb_tile_all` | function | `headers/vga_fb.h:240` | `void vga_fb_tile_all(void);` |
| `vga_fb_toggle_fullscreen` | function | `headers/vga_fb.h:196` | `void vga_fb_toggle_fullscreen(void);` |
| `vga_fb_toggle_minimize` | function | `headers/vga_fb.h:201` | `void vga_fb_toggle_minimize(void);` |
| `vga_fx_enabled` | function | `headers/vga_fb.h:263` | `int vga_fx_enabled(void);` |
| `vga_fx_free` | function | `headers/vga_fb.h:266` | `void vga_fx_free(unsigned int *buf);` |
| `vga_fx_melt_from_black` | function | `headers/vga_fb.h:269` | `void vga_fx_melt_from_black(int x, int y, int w, int h, const unsigned int *newb);` |
| `vga_fx_melt_rect` | function | `headers/vga_fb.h:267` | `void vga_fx_melt_rect(int x, int y, int w, int h, const unsigned int *oldb, const unsigned int *newb);` |
| `vga_fx_restore_rect` | function | `headers/vga_fb.h:265` | `void vga_fx_restore_rect(int x, int y, int w, int h, const unsigned int *buf);` |
| `vga_fx_snap_rect` | function | `headers/vga_fb.h:264` | `unsigned int *vga_fx_snap_rect(int x, int y, int w, int h);` |
| `wm_clear_close` | function | `headers/vga_fb.h:247` | `void wm_clear_close(void);` |
| `wm_close_pending` | function | `headers/vga_fb.h:246` | `int wm_close_pending(void);` |
| `wm_gfx_mode_active` | function | `headers/vga_fb.h:248` | `int wm_gfx_mode_active(void);` |
| `VGA_FX_COLS_MAX` | macro | `headers/vga_fx.h:27` | `#define VGA_FX_COLS_MAX` |
| `VGA_FX_CONFIG_DEFAULT` | macro | `headers/vga_fx.h:24` | `#define VGA_FX_CONFIG_DEFAULT` |
| `VGA_FX_H` | macro | `headers/vga_fx.h:13` | `#define VGA_FX_H` |
| `vga_fx_advance` | function | `headers/vga_fx.h:71` | `static inline int vga_fx_advance(const vga_fx_config_t *cfg, int *cols, int w, int h)` |
| `vga_fx_clamp_rect` | function | `headers/vga_fx.h:109` | `static inline int vga_fx_clamp_rect(int *x, int *y, int *w, int *h, int fb_w, int fb_h)` |
| `vga_fx_config_t` | struct | `headers/vga_fx.h:16` | `` |
| `vga_fx_front` | function | `headers/vga_fx.h:97` | `static inline int vga_fx_front(int col_y, int h)` |
| `vga_fx_init_cols` | function | `headers/vga_fx.h:47` | `static inline int vga_fx_init_cols(const vga_fx_config_t *cfg, int *cols, int w)` |
| `vga_fx_rand` | function | `headers/vga_fx.h:30` | `static inline unsigned long vga_fx_rand(unsigned long *s)` |
| `VMA_H` | macro | `headers/vma.h:2` | `#define VMA_H` |
| `VMA_MAX` | macro | `headers/vma.h:31` | `#define VMA_MAX` |
| `VMA_NIL` | variable | `headers/vma.h:54` | `extern vma_node_t *VMA_NIL;` |
| `base` | type_alias | `headers/vma.h:20` | `typedef struct vma_node { unsigned long base;` |
| `vma_ctx_alloc` | function | `headers/vma.h:87` | `vma_ctx_t *vma_ctx_alloc(void);` |
| `vma_ctx_bind` | function | `headers/vma.h:68` | `void vma_ctx_bind(vma_ctx_t *c);` |
| `vma_ctx_free` | function | `headers/vma.h:88` | `void vma_ctx_free(vma_ctx_t *c);` |
| `vma_ctx_init` | function | `headers/vma.h:67` | `void vma_ctx_init(vma_ctx_t *c, vma_node_t *pool);` |
| `vma_ctx_save` | function | `headers/vma.h:69` | `void vma_ctx_save(vma_ctx_t *c);` |
| `vma_ctx_t` | struct | `headers/vma.h:44` | `` |
| `vma_free_root` | variable | `headers/vma.h:56` | `extern vma_node_t *vma_free_root;` |
| `vma_legacy` | variable | `headers/vma.h:60` | `extern vma_ctx_t vma_legacy;` |
| `vma_live_root` | variable | `headers/vma.h:55` | `extern vma_node_t *vma_live_root;` |
| `vma_node` | struct | `headers/vma.h:21` | `` |
| `vma_pool` | variable | `headers/vma.h:57` | `extern vma_node_t vma_pool[VMA_MAX];` |
| `vma_pool_n` | variable | `headers/vma.h:58` | `extern int vma_pool_n;` |
| `vma_pool_ptr` | variable | `headers/vma.h:59` | `extern vma_node_t *vma_pool_ptr;` |
| `vma_tree_delete` | function | `headers/vma.h:66` | `int vma_tree_delete(vma_node_t **root, unsigned long base);` |
| `vma_tree_find` | function | `headers/vma.h:64` | `vma_node_t *vma_tree_find(vma_node_t *root, unsigned long base);` |
| `vma_tree_find_containing` | function | `headers/vma.h:65` | `vma_node_t *vma_tree_find_containing(vma_node_t *root, unsigned long va);` |
| `vma_tree_init` | function | `headers/vma.h:62` | `void vma_tree_init(void);` |
| `vma_tree_insert` | function | `headers/vma.h:63` | `vma_node_t *vma_tree_insert(vma_node_t **root, unsigned long base, unsigned long len);` |
| `vma_view_load` | function | `headers/vma.h:84` | `void vma_view_load(const vma_view_t *v);` |
| `vma_view_save` | function | `headers/vma.h:83` | `void vma_view_save(vma_view_t *v);` |
| `vma_view_t` | struct | `headers/vma.h:74` | `` |
| `WM_COMBOS_N` | macro | `headers/wm_events.h:198` | `#define WM_COMBOS_N` |
| `WM_EVENTS_H` | macro | `headers/wm_events.h:11` | `#define WM_EVENTS_H` |
| `WM_EVENT_CONFIG_DEFAULT` | macro | `headers/wm_events.h:49` | `#define WM_EVENT_CONFIG_DEFAULT` |
| `WM_PATH_COOKED` | macro | `headers/wm_events.h:138` | `#define WM_PATH_COOKED` |
| `WM_PATH_RAW` | macro | `headers/wm_events.h:139` | `#define WM_PATH_RAW` |
| `WM_SC_DOWN` | macro | `headers/wm_events.h:121` | `#define WM_SC_DOWN` |
| `WM_SC_END` | macro | `headers/wm_events.h:125` | `#define WM_SC_END` |
| `WM_SC_ENTER` | macro | `headers/wm_events.h:111` | `#define WM_SC_ENTER` |
| `WM_SC_EQUAL` | macro | `headers/wm_events.h:113` | `#define WM_SC_EQUAL` |
| `WM_SC_HOME` | macro | `headers/wm_events.h:124` | `#define WM_SC_HOME` |
| `WM_SC_LBRACKET` | macro | `headers/wm_events.h:116` | `#define WM_SC_LBRACKET` |
| `WM_SC_LEFT` | macro | `headers/wm_events.h:122` | `#define WM_SC_LEFT` |
| `WM_SC_M` | macro | `headers/wm_events.h:118` | `#define WM_SC_M` |
| `WM_SC_MINUS` | macro | `headers/wm_events.h:112` | `#define WM_SC_MINUS` |
| `WM_SC_Q` | macro | `headers/wm_events.h:115` | `#define WM_SC_Q` |
| `WM_SC_RBRACKET` | macro | `headers/wm_events.h:117` | `#define WM_SC_RBRACKET` |
| `WM_SC_RIGHT` | macro | `headers/wm_events.h:123` | `#define WM_SC_RIGHT` |
| `WM_SC_TAB` | macro | `headers/wm_events.h:110` | `#define WM_SC_TAB` |
| `WM_SC_UP` | macro | `headers/wm_events.h:120` | `#define WM_SC_UP` |
| `WM_SC_X` | macro | `headers/wm_events.h:119` | `#define WM_SC_X` |
| `WM_SC_ZERO` | macro | `headers/wm_events.h:114` | `#define WM_SC_ZERO` |
| `WM_SNAP_BOTTOM` | macro | `headers/wm_events.h:131` | `#define WM_SNAP_BOTTOM` |
| `WM_SNAP_BOTTOM_LEFT` | macro | `headers/wm_events.h:134` | `#define WM_SNAP_BOTTOM_LEFT` |
| `WM_SNAP_BOTTOM_RIGHT` | macro | `headers/wm_events.h:135` | `#define WM_SNAP_BOTTOM_RIGHT` |
| `WM_SNAP_LEFT` | macro | `headers/wm_events.h:128` | `#define WM_SNAP_LEFT` |
| `WM_SNAP_RIGHT` | macro | `headers/wm_events.h:129` | `#define WM_SNAP_RIGHT` |
| `WM_SNAP_TOP` | macro | `headers/wm_events.h:130` | `#define WM_SNAP_TOP` |
| `WM_SNAP_TOP_LEFT` | macro | `headers/wm_events.h:132` | `#define WM_SNAP_TOP_LEFT` |
| `WM_SNAP_TOP_RIGHT` | macro | `headers/wm_events.h:133` | `#define WM_SNAP_TOP_RIGHT` |
| `wm_combo_lookup` | function | `headers/wm_events.h:201` | `static inline int wm_combo_lookup(int alt, int altgr, int sup, int e0, int sc, int path, int *zon...` |
| `wm_combo_lookup_mods` | function | `headers/wm_events.h:238` | `static inline int wm_combo_lookup_mods(const modifier_state_t *st, int e0, int sc, int path, int ...` |
| `wm_combo_t` | struct | `headers/wm_events.h:158` | `` |
| `wm_event_config_t` | struct | `headers/wm_events.h:43` | `` |
| `wm_event_suppresses_drag` | function | `headers/wm_events.h:104` | `static inline int wm_event_suppresses_drag(const wm_event_t *evt)` |
| `wm_event_t` | struct | `headers/wm_events.h:34` | `` |
| `wm_is_click_edge` | function | `headers/wm_events.h:52` | `static inline int wm_is_click_edge(const wm_event_config_t *cfg, int prev_buttons, int curr_buttons)` |
| `wm_is_release_edge` | function | `headers/wm_events.h:59` | `static inline int wm_is_release_edge(const wm_event_config_t *cfg, int prev_buttons, int curr_but...` |
| `wm_mouse_t` | struct | `headers/wm_events.h:25` | `` |
| `wm_translate_event` | function | `headers/wm_events.h:66` | `static inline wm_event_t wm_translate_event(const wm_event_config_t *cfg, const wm_mouse_t *prev,...` |
| `WM_FOCUS_H` | macro | `headers/wm_focus.h:10` | `#define WM_FOCUS_H` |
| `wm_focus_next` | function | `headers/wm_focus.h:38` | `static inline int wm_focus_next(const wm_focus_state_t *st)` |
| `wm_focus_selectable` | function | `headers/wm_focus.h:23` | `static inline int wm_focus_selectable(const wm_focus_state_t *st, int id)` |
| `wm_focus_set` | function | `headers/wm_focus.h:55` | `static inline int wm_focus_set(const wm_focus_state_t *st, int id)` |
| `wm_focus_state_t` | struct | `headers/wm_focus.h:15` | `` |
| `WM_GEOM_CONFIG_DEFAULT` | macro | `headers/wm_geom.h:22` | `#define WM_GEOM_CONFIG_DEFAULT` |
| `WM_GEOM_H` | macro | `headers/wm_geom.h:11` | `#define WM_GEOM_H` |
| `wm_clamp_point` | function | `headers/wm_geom.h:91` | `static inline void wm_clamp_point(int *px, int *py, int fb_w, int fb_h)` |
| `wm_content_rect` | function | `headers/wm_geom.h:59` | `static inline wm_rect_t wm_content_rect(const wm_geom_config_t *cfg, int px, int py, int w, int h)` |
| `wm_geom_config_t` | struct | `headers/wm_geom.h:14` | `` |
| `wm_hit_title_bar` | function | `headers/wm_geom.h:84` | `static inline int wm_hit_title_bar(const wm_geom_config_t *cfg, int wx, int wy, int w, int px, in...` |
| `wm_rect_contains` | function | `headers/wm_geom.h:39` | `static inline int wm_rect_contains(const wm_rect_t *r, int px, int py)` |
| `wm_rect_t` | struct | `headers/wm_geom.h:25` | `` |
| `wm_rect_valid` | function | `headers/wm_geom.h:33` | `static inline int wm_rect_valid(const wm_rect_t *r)` |
| `wm_scrollbar_rect` | function | `headers/wm_geom.h:71` | `static inline wm_rect_t wm_scrollbar_rect(const wm_geom_config_t *cfg, int px, int py, int conten...` |
| `wm_title_bar_rect` | function | `headers/wm_geom.h:48` | `static inline wm_rect_t wm_title_bar_rect(const wm_geom_config_t *cfg, int px, int py, int w)` |
| `Downscale` | function | `headers/wm_gfxview.h:88` | `* Downscale (fit below 1x) always takes the exact fit. Returns 1 on  * success, 0 on degenerate i...` |
| `WM_GFXVIEW_CONFIG_DEFAULT` | macro | `headers/wm_gfxview.h:41` | `#define WM_GFXVIEW_CONFIG_DEFAULT` |
| `WM_GFXVIEW_DIM_MAX` | macro | `headers/wm_gfxview.h:44` | `#define WM_GFXVIEW_DIM_MAX` |
| `WM_GFXVIEW_H` | macro | `headers/wm_gfxview.h:21` | `#define WM_GFXVIEW_H` |
| `wm_gfxview_clamp` | function | `headers/wm_gfxview.h:134` | `static inline void wm_gfxview_clamp(wm_gfxview_rect_t *r, int fb_w, int fb_h)` |
| `wm_gfxview_config_t` | struct | `headers/wm_gfxview.h:31` | `` |
| `wm_gfxview_dims_ok` | function | `headers/wm_gfxview.h:79` | `static inline int wm_gfxview_dims_ok(int w, int h)` |
| `wm_gfxview_ease` | function | `headers/wm_gfxview.h:291` | `static inline long wm_gfxview_ease(int t, int n, long den)` |
| `wm_gfxview_lerp_rect` | function | `headers/wm_gfxview.h:313` | `static inline int wm_gfxview_lerp_rect(const wm_gfxview_rect_t *a, const wm_gfxview_rect_t *b,   ...` |
| `wm_gfxview_map_point` | function | `headers/wm_gfxview.h:255` | `static inline int wm_gfxview_map_point(const wm_gfxview_t *v, int sw, int sh,                    ...` |
| `wm_gfxview_mode_name` | function | `headers/wm_gfxview.h:64` | `static inline const char *wm_gfxview_mode_name(int mode)` |
| `wm_gfxview_place_content` | function | `headers/wm_gfxview.h:160` | `static inline int wm_gfxview_place_content(const wm_gfxview_config_t *cfg, int sw, int sh,       ...` |
| `wm_gfxview_rect_same` | function | `headers/wm_gfxview.h:336` | `static inline int wm_gfxview_rect_same(const wm_gfxview_rect_t *a, const wm_gfxview_rect_t *b)` |
| `wm_gfxview_rect_t` | struct | `headers/wm_gfxview.h:47` | `` |
| `wm_gfxview_t` | struct | `headers/wm_gfxview.h:56` | `` |
| `WM_LAYOUT_CONFIG_DEFAULT` | macro | `headers/wm_layout.h:45` | `#define WM_LAYOUT_CONFIG_DEFAULT` |
| `WM_LAYOUT_H` | macro | `headers/wm_layout.h:12` | `#define WM_LAYOUT_H` |
| `WM_LAYOUT_MODE_COUNT` | macro | `headers/wm_layout.h:24` | `#define WM_LAYOUT_MODE_COUNT` |
| `wm_layout_cell_t` | struct | `headers/wm_layout.h:48` | `` |
| `wm_layout_clamp_cell` | function | `headers/wm_layout.h:82` | `static inline int wm_layout_clamp_cell(wm_layout_cell_t *cell, int max_cols, int max_rows)` |
| `wm_layout_compute` | function | `headers/wm_layout.h:361` | `static inline int wm_layout_compute(const wm_layout_config_t *cfg, const wm_layout_window_t *wins...` |
| `wm_layout_compute_bsp` | function | `headers/wm_layout.h:182` | `static inline int wm_layout_compute_bsp(const wm_layout_window_t *wins, int nwin, int max_cols, i...` |
| `wm_layout_compute_cascade` | function | `headers/wm_layout.h:250` | `static inline int wm_layout_compute_cascade(const wm_layout_config_t *cfg, const wm_layout_window...` |
| `wm_layout_compute_fibonacci` | function | `headers/wm_layout.h:285` | `static inline int wm_layout_compute_fibonacci(const wm_layout_config_t *cfg, const wm_layout_wind...` |
| `wm_layout_compute_tile` | function | `headers/wm_layout.h:135` | `static inline int wm_layout_compute_tile(const wm_layout_window_t *wins, int nwin, int max_cols, ...` |
| `wm_layout_config_t` | struct | `headers/wm_layout.h:36` | `` |
| `wm_layout_fullscreen_cell` | function | `headers/wm_layout.h:118` | `static inline int wm_layout_fullscreen_cell(int max_cols, int max_rows, wm_layout_cell_t *out)` |
| `wm_layout_mode_name` | function | `headers/wm_layout.h:57` | `static inline const char *wm_layout_mode_name(int mode)` |
| `wm_layout_mode_valid` | function | `headers/wm_layout.h:76` | `static inline int wm_layout_mode_valid(int mode)` |
| `wm_layout_same` | function | `headers/wm_layout.h:443` | `static inline int wm_layout_same(const wm_layout_cell_t *a, const wm_layout_cell_t *b, int n)` |
| `wm_layout_window_t` | struct | `headers/wm_layout.h:27` | `` |
| `WM_NOTIFY_H` | macro | `headers/wm_notify.h:2` | `#define WM_NOTIFY_H` |
| `WM_NOTIFY_MAX_HANDLERS` | macro | `headers/wm_notify.h:41` | `#define WM_NOTIFY_MAX_HANDLERS` |
| `wm_notify_bus_t` | struct | `headers/wm_notify.h:43` | `` |
| `wm_notify_emit` | function | `headers/wm_notify.h:76` | `static inline void wm_notify_emit(wm_notify_bus_t *bus,                                   const w...` |
| `wm_notify_event_t` | struct | `headers/wm_notify.h:30` | `` |
| `wm_notify_last` | function | `headers/wm_notify.h:90` | `static inline const wm_notify_event_t *wm_notify_last(     const wm_notify_bus_t *bus)` |
| `wm_notify_reset` | function | `headers/wm_notify.h:51` | `static inline void wm_notify_reset(wm_notify_bus_t *bus)` |
| `wm_notify_src_name` | function | `headers/wm_notify.h:98` | `static inline const char *wm_notify_src_name(int source)` |
| `wm_notify_subscribe` | function | `headers/wm_notify.h:66` | `static inline int wm_notify_subscribe(wm_notify_bus_t *bus,                                      ...` |
| `WM_RENDER_CONFIG_DEFAULT` | macro | `headers/wm_render.h:36` | `#define WM_RENDER_CONFIG_DEFAULT` |
| `WM_RENDER_H` | macro | `headers/wm_render.h:11` | `#define WM_RENDER_H` |
| `wm_build_render_plan` | function | `headers/wm_render.h:39` | `static inline int wm_build_render_plan(const wm_render_config_t *cfg, const int *present, int nte...` |
| `wm_render_config_t` | struct | `headers/wm_render.h:31` | `` |
| `wm_render_item_t` | struct | `headers/wm_render.h:25` | `` |
| `WM_TILING_H` | macro | `headers/wm_tiling.h:10` | `#define WM_TILING_H` |
| `wm_tile_cell_t` | struct | `headers/wm_tiling.h:13` | `` |
| `wm_tile_layout` | function | `headers/wm_tiling.h:22` | `static inline int wm_tile_layout(const int *present, int nterms, int gfx_active, int max_cols, in...` |
| `WM_WINDOW_GFX_ID` | macro | `headers/wm_window.h:23` | `#define WM_WINDOW_GFX_ID` |
| `WM_WINDOW_H` | macro | `headers/wm_window.h:11` | `#define WM_WINDOW_H` |
| `WM_WINDOW_MAX_TERMS` | macro | `headers/wm_window.h:26` | `#define WM_WINDOW_MAX_TERMS` |
| `wm_focus_next_id` | function | `headers/wm_window.h:77` | `static inline int wm_focus_next_id(const int *present, int nterms, int gfx_active, int focus)` |
| `wm_paint_order` | function | `headers/wm_window.h:114` | `static inline int wm_paint_order(const int *present, int nterms, int focus, int *order, int cap)` |
| `wm_window_active` | function | `headers/wm_window.h:41` | `static inline int wm_window_active(const wm_window_t *w)` |
| `wm_window_contains` | function | `headers/wm_window.h:58` | `static inline int wm_window_contains(const wm_window_t *w, int px, int py)` |
| `wm_window_rect` | function | `headers/wm_window.h:47` | `static inline wm_rect_t wm_window_rect(const wm_window_t *w)` |
| `wm_window_t` | struct | `headers/wm_window.h:29` | `` |
| `wm_window_title_hits` | function | `headers/wm_window.h:68` | `static inline int wm_window_title_hits(const wm_geom_config_t *cfg, const wm_window_t *w, int px,...` |
| `ZIP_H` | macro | `headers/zip.h:2` | `#define ZIP_H` |
| `miniz` | function | `headers/zip.h:6` | `* * The shell builtins over miniz (see zip.c) are declared here so kernel.c's * shell dispatcher can route the...` |
| `shell_cmd_zip` | function | `headers/zip.h:15` | `void shell_cmd_zip(int argc, char **argv);` |
| `BOOTLOG_MAX` | macro | `kernel.c:186` | `#define BOOTLOG_MAX` |
| `EM` | function | `kernel.c:219` | `* CR0: clear EM (bit 2), set MP (bit 1);` |
| `KSYM_MAX` | macro | `kernel.c:105` | `#define KSYM_MAX` |
| `__attribute__` | function | `kernel.c:205` | `__attribute__((section(".init.text"))) void kmain(void)` |
| `bootlog_mark` | function | `kernel.c:190` | `void bootlog_mark(const char *name)` |
| `bootlog_report` | function | `kernel.c:197` | `void bootlog_report(void)` |
| `kstack` | function | `kernel.c:144` | `* Reading gs:8 instead resolves every thread to the wrong kstack (0 on * the BSP, 1 on APs): harmless while a single...` |
| `ksyscall` | function | `kernel.c:128` | `extern long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);` |
| `ms` | function | `kernel.c:183` | `* 0 ms (TSC ticks since power-on divided down, still monotonic);` |
| `ramdisk_end` | variable | `kernel.c:178` | `extern char ramdisk_end[];` |
| `ramdisk_start` | variable | `kernel.c:177` | `extern char ramdisk_start[];` |
| `size` | function | `kernel.c:260` | `* image size (see kernel.ld);` |
| `syscall_init` | function | `kernel.c:115` | `void syscall_init(void)` |
| `syscall_kstack` | variable | `kernel.c:113` | `extern unsigned long syscall_kstack;` |
| `table` | function | `kernel.c:102` | `* Symbol table (for resolving program references) * ================================================================...` |
| `tables` | function | `kernel.c:282` | `* tables (already built above) for its uncached register window and the      * heap for its rings...` |
| `abi_check_manifest` | function | `kernel/abi.c:74` | `int abi_check_manifest(void)` |
| `abi_parse_num` | function | `kernel/abi.c:20` | `static int abi_parse_num(const char **pp, const char *end, unsigned long *out)` |
| `abi_verify` | function | `kernel/abi.c:38` | `int abi_verify(const char *text, long version, unsigned long checksum)` |
| `batch_exec` | function | `kernel/batch.c:19` | `long batch_exec(const batch_op_t *ops, long *results, int count,                 int *completed, ...` |
| `CLIP_MAX` | macro | `kernel/clip.c:17` | `#define CLIP_MAX` |
| `clip_clear` | function | `kernel/clip.c:48` | `void clip_clear(void)` |
| `clip_len_get` | function | `kernel/clip.c:55` | `int clip_len_get(void)` |
| `clip_set` | function | `kernel/clip.c:25` | `int clip_set(const char *data, unsigned long len)` |
| `REDIR_INITIAL_CAP` | macro | `kernel/console.c:96` | `#define REDIR_INITIAL_CAP` |
| `REDIR_MAX_BYTES` | macro | `kernel/console.c:97` | `#define REDIR_MAX_BYTES` |
| `XXH_STATIC_LINKING_ONLY` | macro | `kernel/console.c:4` | `#define XXH_STATIC_LINKING_ONLY` |
| `redir_grow` | function | `kernel/console.c:110` | `static int redir_grow(void)` |
| `redirect_active` | function | `kernel/console.c:120` | `int redirect_active(void)` |
| `redirect_begin` | function | `kernel/console.c:139` | `int redirect_begin(void)` |
| `redirect_commit` | function | `kernel/console.c:147` | `int redirect_commit(const char *path, int append_mode)` |
| `redirect_discard` | function | `kernel/console.c:216` | `void redirect_discard(void)` |
| `redirect_pending` | function | `kernel/console.c:185` | `unsigned long redirect_pending(void)` |
| `redirect_putc` | function | `kernel/console.c:122` | `static int redirect_putc(char c)` |
| `redirect_resume` | function | `kernel/console.c:135` | `void redirect_resume(int was)` |
| `redirect_suspend` | function | `kernel/console.c:129` | `int redirect_suspend(void)` |
| `redirect_take_into` | function | `kernel/console.c:196` | `unsigned long redirect_take_into(char *dst, unsigned long cap,         unsigned long *len_out)` |
| `register_libc_symbols` | function | `kernel/console.c:271` | `void register_libc_symbols(void)` |
| `vga_clear` | function | `kernel/console.c:25` | `void vga_clear(void)` |
| `vga_cursor_enable` | function | `kernel/console.c:81` | `void vga_cursor_enable(int on)` |
| `vga_get_color` | function | `kernel/console.c:21` | `char vga_get_color(void)` |
| `vga_get_x` | function | `kernel/console.c:18` | `int vga_get_x(void)` |
| `vga_get_y` | function | `kernel/console.c:19` | `int vga_get_y(void)` |
| `vga_newline` | function | `kernel/console.c:75` | `void vga_newline(void)` |
| `vga_offset` | function | `kernel/console.c:23` | `static inline unsigned vga_offset(int x, int y)` |
| `vga_putc` | function | `kernel/console.c:223` | `void vga_putc(char c)` |
| `vga_puts` | function | `kernel/console.c:267` | `void vga_puts(const char *s)` |
| `vga_raw_space` | function | `kernel/console.c:88` | `static void vga_raw_space(void)` |
| `vga_scroll` | function | `kernel/console.c:56` | `void vga_scroll(void)` |
| `vga_set_cursor` | function | `kernel/console.c:36` | `void vga_set_cursor(int x, int y)` |
| `vga_set_xy` | function | `kernel/console.c:20` | `void vga_set_xy(int x, int y)` |
| `ESC` | function | `kernel/console_in.c:157` | `* The bound keeps a bare ESC (never completed into a sequence) from  * hanging the reader. */ #de...` |
| `MAX_SEQ_POLL` | macro | `kernel/console_in.c:159` | `#define MAX_SEQ_POLL` |
| `PB_LEN` | macro | `kernel/console_in.c:18` | `#define PB_LEN` |
| `SB_EXIT` | macro | `kernel/console_in.c:306` | `#define SB_EXIT` |
| `SB_LEN` | macro | `kernel/console_in.c:281` | `#define SB_LEN` |
| `SB_PGDN` | macro | `kernel/console_in.c:305` | `#define SB_PGDN` |
| `SB_PGUP` | macro | `kernel/console_in.c:304` | `#define SB_PGUP` |
| `console_getc` | function | `kernel/console_in.c:205` | `int console_getc(void)` |
| `console_job_get` | function | `kernel/console_in.c:267` | `int console_job_get(void)` |
| `console_job_try` | function | `kernel/console_in.c:257` | `int console_job_try(void)` |
| `console_peek` | function | `kernel/console_in.c:233` | `int console_peek(void)` |
| `console_poll_usb` | function | `kernel/console_in.c:93` | `static void console_poll_usb(void)` |
| `console_ps2_live` | function | `kernel/console_in.c:106` | `static int console_ps2_live(void)` |
| `console_raw_get` | function | `kernel/console_in.c:250` | `int console_raw_get(void)` |
| `console_raw_try` | function | `kernel/console_in.c:246` | `int console_raw_try(void)` |
| `console_stdin_active` | function | `kernel/console_in.c:56` | `int console_stdin_active(void)` |
| `console_stdin_clear` | function | `kernel/console_in.c:46` | `void console_stdin_clear(void)` |
| `console_stdin_push` | function | `kernel/console_in.c:32` | `int console_stdin_push(const char *data, unsigned long len)` |
| `console_ungetc` | function | `kernel/console_in.c:85` | `void console_ungetc(unsigned char c)` |
| `consume_page_after_esc` | function | `kernel/console_in.c:178` | `static int consume_page_after_esc(void)` |
| `pb_count` | function | `kernel/console_in.c:61` | `static int pb_count(void)` |
| `pb_empty` | function | `kernel/console_in.c:60` | `static int pb_empty(void)` |
| `pb_peek` | function | `kernel/console_in.c:78` | `static int pb_peek(void)` |
| `pb_pop` | function | `kernel/console_in.c:72` | `static int pb_pop(void)` |
| `pb_push_back` | function | `kernel/console_in.c:62` | `static void pb_push_back(unsigned char c)` |
| `pb_push_front` | function | `kernel/console_in.c:67` | `static void pb_push_front(unsigned char c)` |
| `raw_blocking_getc` | function | `kernel/console_in.c:118` | `static int raw_blocking_getc(void)` |
| `raw_try_getc` | function | `kernel/console_in.c:139` | `static int raw_try_getc(void)` |
| `sb_next` | function | `kernel/console_in.c:311` | `static int sb_next(void)` |
| `scrollback_render` | function | `kernel/console_in.c:283` | `static void scrollback_render(int voff, int total, const unsigned char *saved)` |
| `scrollback_view` | function | `kernel/console_in.c:321` | `static void scrollback_view(int initial_dir)` |
| `cvm_main` | function | `kernel/cvm_host.c:437` | `int cvm_main(int argc, char **argv)` |
| `kformat` | function | `kernel/cvm_host.c:296` | `static void kformat(void *ctx, const char *fmt, uint64_t *argv, int argc)` |
| `kout_char` | function | `kernel/cvm_host.c:277` | `static void kout_char(void *ctx, char c)` |
| `kout_uint` | function | `kernel/cvm_host.c:283` | `static void kout_uint(void *ctx, unsigned long long v, int base, int upper)` |
| `n_atol` | function | `kernel/cvm_host.c:236` | `static int64_t n_atol(void *vm, int ac, uint64_t *av)` |
| `n_calloc` | function | `kernel/cvm_host.c:98` | `static int64_t n_calloc(void *vm, int ac, uint64_t *av)` |
| `n_exit` | function | `kernel/cvm_host.c:114` | `static int64_t n_exit(void *vm, int ac, uint64_t *av)` |
| `n_fclose` | function | `kernel/cvm_host.c:128` | `static int64_t n_fclose(void *vm, int ac, uint64_t *av)` |
| `n_fflush` | function | `kernel/cvm_host.c:191` | `static int64_t n_fflush(void *vm, int ac, uint64_t *av)` |
| `n_fgetc` | function | `kernel/cvm_host.c:179` | `static int64_t n_fgetc(void *vm, int ac, uint64_t *av)` |
| `n_fopen` | function | `kernel/cvm_host.c:121` | `static int64_t n_fopen(void *vm, int ac, uint64_t *av)` |
| `n_fprintf` | function | `kernel/cvm_host.c:362` | `static int64_t n_fprintf(void *vm, int ac, uint64_t *av)` |
| `n_fputc` | function | `kernel/cvm_host.c:173` | `static int64_t n_fputc(void *vm, int ac, uint64_t *av)` |
| `n_fputs` | function | `kernel/cvm_host.c:167` | `static int64_t n_fputs(void *vm, int ac, uint64_t *av)` |
| `n_fread` | function | `kernel/cvm_host.c:134` | `static int64_t n_fread(void *vm, int ac, uint64_t *av)` |
| `n_free` | function | `kernel/cvm_host.c:93` | `static int64_t n_free(void *vm, int ac, uint64_t *av)` |
| `n_fseek` | function | `kernel/cvm_host.c:148` | `static int64_t n_fseek(void *vm, int ac, uint64_t *av)` |

Next: [SYMBOLS_p8.md](SYMBOLS_p8.md)
