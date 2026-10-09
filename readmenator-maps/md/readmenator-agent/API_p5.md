# API (page 5 of 19)
Previous: [API_p4.md](API_p4.md)

## headers/tls.h
Imported by: `net/net.c`, `net/tls.c`, `net/tls_crypto.c`, `net/tls_x509.c`, `progs/tls_u/tls_u_main.c`, `tls_test.c`
- `sha256_init` (function) `headers/tls.h:168` `void sha256_init(struct sha256_ctx *c);`
- `sha256_update` (function) `headers/tls.h:169` `void sha256_update(struct sha256_ctx *c, const unsigned char *data, unsigned len);`
- `sha256_final` (function) `headers/tls.h:170` `void sha256_final(struct sha256_ctx *c, unsigned char out[32]);`
- `sha256` (function) `headers/tls.h:171` `void sha256(const unsigned char *data, unsigned len, unsigned char out[32]);`
- `sha384` (function) `headers/tls.h:172` `void sha384(const unsigned char *data, unsigned len, unsigned char out[48]);`
- `hmac_sha256` (function) `headers/tls.h:174` `void hmac_sha256(const unsigned char *key, unsigned klen, const unsigned char *data, unsigned dlen, unsigned char...`
- `tls_prf` (function) `headers/tls.h:179` `void tls_prf(const unsigned char *secret, unsigned secret_len, const char *label, const unsigned char *seed...`
- `aes128_encrypt_block` (function) `headers/tls.h:184` `void aes128_encrypt_block(const unsigned char key[16], const unsigned char in[16], unsigned char out[16]);` -- void sha256_final(struct sha256_ctx *c, unsigned char out[32]); void sha256(const unsigned char *data, unsigned len...
- `aes128_gcm_seal` (function) `headers/tls.h:189` `int aes128_gcm_seal(const unsigned char key[16], const unsigned char salt[4], unsigned long long seq, const unsigned...` -- GCM.
- `aes128_gcm_open` (function) `headers/tls.h:197` `int aes128_gcm_open(const unsigned char key[16], const unsigned char salt[4], unsigned long long seq, const unsigned...` -- GCM.
- `aes128_gcm_seal_core` (function) `headers/tls.h:208` `int aes128_gcm_seal_core(const unsigned char key[16], const unsigned char nonce[12], const unsigned char *aad...` -- Core GCM with an arbitrary 12-byte nonce (the TLS API above is the 4-byte salt + 8-byte sequence special case).
- `aes128_gcm_open_core` (function) `headers/tls.h:213` `int aes128_gcm_open_core(const unsigned char key[16], const unsigned char nonce[12], const unsigned char *aad...`
- `p256_scalar_mult` (function) `headers/tls.h:222` `int p256_scalar_mult(const unsigned char scalar[32], const unsigned char qx[32], const unsigned char qy[32]...` -- secp256r1 / secp384r1: shared Jacobian point arithmetic over NIST * primes. curve: 0 = P-256, 1 = P-384.
- `p384_scalar_mult` (function) `headers/tls.h:225` `int p384_scalar_mult(const unsigned char scalar[48], const unsigned char qx[48], const unsigned char qy[48]...`
- `p256_ecdh` (function) `headers/tls.h:231` `int p256_ecdh(const unsigned char priv[32], const unsigned char peer_x[32], const unsigned char peer_y[32], unsigned...` -- ECDH shared secret: Z = priv * peer_pub (P-256).
- `p256_point_valid` (function) `headers/tls.h:236` `int p256_point_valid(const unsigned char x[32], const unsigned char y[32]);` -- ECDH shared secret: Z = priv * peer_pub (P-256).
- `p256_pub` (function) `headers/tls.h:237` `int p256_pub(const unsigned char priv[32], unsigned char x[32], unsigned char y[32]);`
- `p256_scalar_valid` (function) `headers/tls.h:239` `int p256_scalar_valid(const unsigned char scalar[32]);`
- `ecdsa_verify` (function) `headers/tls.h:243` `int ecdsa_verify(int curve, const unsigned char pub_x[], const unsigned char pub_y[], const unsigned char digest[]...` -- ECDSA verify over a SHA-256 or SHA-384 digest. curve: 0 = P-256, * 1 = P-384.
- `rsa_pkcs1_verify_sha256` (function) `headers/tls.h:249` `int rsa_pkcs1_verify_sha256(const unsigned char *n, unsigned n_len, const unsigned char *e, unsigned e_len, const...` -- RSA PKCS#1 v1.5 signature verify with SHA-256. modulus up to 4096 bits. * digest is the SHA-256 of the signed data.
- `rsa_pkcs1_verify_sha384` (function) `headers/tls.h:253` `int rsa_pkcs1_verify_sha384(const unsigned char *n, unsigned n_len, const unsigned char *e, unsigned e_len, const...`
- `tls_x509_parse_pubkey` (function) `headers/tls.h:261` `int tls_x509_parse_pubkey(const unsigned char *der, unsigned len, struct tls_pubkey *pk);` -- RSA PKCS#1 v1.5 signature verify with SHA-256. modulus up to 4096 bits. * digest is the SHA-256 of the signed data.
- `now` (function) `headers/tls.h:267` `* window against now (days since epoch). Returns 0 on success. */ int tls_x509_verify_chain(const unsigned char...`
- `tls_handshake` (function) `headers/tls.h:277` `int tls_handshake(int fd, const char *host);` -- Blocking TLS 1.2 handshake over an open TCP socket (net fd index). host is the SNI + certificate hostname.
- `tls_send` (function) `headers/tls.h:280` `int tls_send(int fd, const char *buf, int len);` -- Blocking TLS 1.2 handshake over an open TCP socket (net fd index). host is the SNI + certificate hostname.
- `tls_recv` (function) `headers/tls.h:284` `int tls_recv(int fd, char *buf, int len);` -- Receive decrypted application bytes.
- `tls_free_fd` (function) `headers/tls.h:293` `static inline void tls_free_fd(int fd)` -- Kernel built without the TLS engine (net/tls*.c unlinked): no session can ever exist, so the net.c close path needs...
- `tls_sys_handshake` (function) `headers/tls.h:297` `long tls_sys_handshake(long fd, long host);` -- Kernel built without the TLS engine (net/tls*.c unlinked): no session can ever exist, so the net.c close path needs...
- `tls_sys_send` (function) `headers/tls.h:298` `long tls_sys_send(long fd, long buf, long len);`
- `tls_sys_recv` (function) `headers/tls.h:299` `long tls_sys_recv(long fd, long buf, long len);`

## headers/tls_port.h
Depends on: `headers/kernel.h`, `headers/net.h`, `kernel/string.c`, `kernel/time.c`
Imported by: `net/tls.c`, `net/tls_crypto.c`, `net/tls_x509.c`, `progs/tls_u/tls_u_main.c`, `tls_test.c`
- `these` (function) `headers/tls_port.h:29` `* of these (tls_test.c). */ extern int tls_test_send(int fd, const char *buf, int len);`
- `tls_test_recv` (function) `headers/tls_port.h:31` `extern int tls_test_recv(int fd, char *buf, int len);`
- `tls_test_recv_timeout` (function) `headers/tls_port.h:32` `extern int tls_test_recv_timeout(int fd, char *buf, int len, unsigned long ms);`
- `tls_test_close` (function) `headers/tls_port.h:33` `extern void tls_test_close(int fd);`
- `tls_now_days` (function) `headers/tls_port.h:40` `static inline long tls_now_days(void)`
- `tls_random` (function) `headers/tls_port.h:44` `static inline void tls_random(unsigned char *out, unsigned len)`
- `sockets` (function) `headers/tls_port.h:62` `* sockets (glibc maps socket/connect/send/recv/poll onto the MiniOS * Linux ABI numbers the kernel implements);`
- `gettimeofday` (function) `headers/tls_port.h:64` `* gettimeofday(96) and entropy from /dev/urandom with a time/pid * fallback. Session slots are indexed by raw OS fd...`
- `tls_u_recv` (function) `headers/tls_port.h:82` `int tls_u_recv(int fd, char *buf, int len);`
- `tls_u_recv_timeout` (function) `headers/tls_port.h:83` `int tls_u_recv_timeout(int fd, char *buf, int len, unsigned long ms);`
- `tls_u_close` (function) `headers/tls_port.h:84` `void tls_u_close(int fd);`
- `syscall` (function) `headers/tls_port.h:95` `* the MiniOS DNS syscall (200, invoked sig-0-safe). 0 on success. */ int tls_u_resolve(const char *host, unsigned...`

## headers/vga_fb.h
Depends on: `headers/wm_notify.h`, `progs/minios_abi.h`
Imported by: `drivers/kbd.c`, `drivers/usbhid.c`, `kernel.c`, `kernel/console.c`, `kernel/console_in.c`, `kernel/exec.c`, `kernel/loader.c`, `kernel/minifetch.c`, `kernel/mm/cow.c`, `kernel/mm/paging.c`, `kernel/panic.c`, `kernel/sched.c`, `kernel/shell.c`, `kernel/spawn.c`, `kernel/syscalls.c`, `kernel/vga_cursor.c`, `kernel/vga_fb.c`, `kernel/vga_fx.c`, `progs/src/freedom_wl.c`
- `fb_bytes_per_pixel` (function) `headers/vga_fb.h:30` `int fb_bytes_per_pixel(void);` -- Bytes per framebuffer pixel derived from fb_bpp (1 for 8-bit, 3 for 24, * 4 for 32).
- `vga_fb_read_rgb` (function) `headers/vga_fb.h:34` `unsigned long vga_fb_read_rgb(int x, int y);` -- Read one desktop pixel as packed 0x00RRGGBB (palette-resolved in 8-bit mode, native in true color).
- `vga_fb_set_gfx_palette` (function) `headers/vga_fb.h:38` `void vga_fb_set_gfx_palette(const unsigned char *pal);` -- Store the graphics program's 768-byte palette (SYS_PALETTE).
- `vga_fb_boot_config` (function) `headers/vga_fb.h:40` `void vga_fb_boot_config(void);`
- `SYS_DOOM_FRAME` (function) `headers/vga_fb.h:44` `* and calls SYS_DOOM_FRAME (211) to have the kernel composite it onto the * desktop at its native resolution, so the...`
- `SYS_NK_FRAME` (function) `headers/vga_fb.h:63` `* SYS_NK_FRAME (220);`
- `vga_fb_blit_nk_window` (function) `headers/vga_fb.h:75` `void vga_fb_blit_nk_window(void);` -- RGB companion buffer (3 bytes per pixel, R,G,B order, NK_W x NK_H).
- `vga_fb_blit_nk_rgb_window` (function) `headers/vga_fb.h:76` `void vga_fb_blit_nk_rgb_window(void);`
- `below` (function) `headers/vga_fb.h:99` `* file below (800x600 RGB PNG on the ramdisk, produced by * tools/gen_desktop_pngs.py) is decoded once per boot via...`
- `vga_fb_init` (function) `headers/vga_fb.h:177` `void vga_fb_init(void);` -- A scrollback line can be up to the widest terminal (TERM_MAX_COLS), and a long logical line that wrapped across...
- `vga_fb_clear` (function) `headers/vga_fb.h:178` `void vga_fb_clear(void);`
- `vga_fb_pixel` (function) `headers/vga_fb.h:179` `void vga_fb_pixel(int x, int y, uint8_t color);`
- `vga_fb_rect` (function) `headers/vga_fb.h:180` `void vga_fb_rect(int x, int y, int w, int h, uint8_t color);`
- `vga_fb_pixel_rgb` (function) `headers/vga_fb.h:182` `void vga_fb_pixel_rgb(int x, int y, uint8_t r, uint8_t g, uint8_t b);` -- A scrollback line can be up to the widest terminal (TERM_MAX_COLS), and a long logical line that wrapped across...
- `vga_fb_rect_rgb` (function) `headers/vga_fb.h:183` `void vga_fb_rect_rgb(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b);`
- `vga_fb_char` (function) `headers/vga_fb.h:184` `void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg);`
- `vga_fb_str` (function) `headers/vga_fb.h:185` `void vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg);`
- `vga_fb_putc_term` (function) `headers/vga_fb.h:186` `void vga_fb_putc_term(char c);`
- `vga_fb_puts_term` (function) `headers/vga_fb.h:187` `void vga_fb_puts_term(const char *s);`
- `term_clear` (function) `headers/vga_fb.h:188` `void term_clear(void);`
- `vga_fb_text_cursor` (function) `headers/vga_fb.h:189` `void vga_fb_text_cursor(int col);`
- `vga_fb_hide_text_cursor` (function) `headers/vga_fb.h:190` `void vga_fb_hide_text_cursor(void);`
- `fb_read_packed` (function) `headers/vga_fb.h:193` `unsigned long fb_read_packed(int x, int y);` -- Packed-pixel primitives (0x00RRGGBB): the cursor layer draws through * these so it never touches raw framebuffer...
- `fb_write_packed` (function) `headers/vga_fb.h:194` `void fb_write_packed(int x, int y, unsigned long rgb);`
- `vga_fb_draw_desktop` (function) `headers/vga_fb.h:195` `void vga_fb_draw_desktop(void);`
- `vga_fb_toggle_fullscreen` (function) `headers/vga_fb.h:196` `void vga_fb_toggle_fullscreen(void);`
- `vga_fb_move_terminal` (function) `headers/vga_fb.h:197` `void vga_fb_move_terminal(int dx, int dy);`
- `vga_fb_snap_window` (function) `headers/vga_fb.h:198` `void vga_fb_snap_window(int zone);`
- `vga_fb_resize` (function) `headers/vga_fb.h:199` `void vga_fb_resize(int dcols, int drows);`
- `vga_fb_reset_default` (function) `headers/vga_fb.h:200` `void vga_fb_reset_default(void);`
- `vga_fb_toggle_minimize` (function) `headers/vga_fb.h:201` `void vga_fb_toggle_minimize(void);`
- `vga_fb_is_minimized` (function) `headers/vga_fb.h:202` `int vga_fb_is_minimized(void);`
- `vga_fb_is_fullscreen` (function) `headers/vga_fb.h:203` `int vga_fb_is_fullscreen(void);`
- `vga_fb_gfx_set_fullscreen` (function) `headers/vga_fb.h:211` `int vga_fb_gfx_set_fullscreen(int on);` -- Graphics window view (headers/wm_gfxview.h owns the math).
- `vga_fb_gfx_set_hidden` (function) `headers/vga_fb.h:212` `int vga_fb_gfx_set_hidden(int hide);`
- `vga_fb_gfx_view_name` (function) `headers/vga_fb.h:213` `const char *vga_fb_gfx_view_name(void);`
- `vga_fb_gfx_origin` (function) `headers/vga_fb.h:214` `void vga_fb_gfx_origin(int *x, int *y);`
- `vga_fb_gfx_map_mouse` (function) `headers/vga_fb.h:215` `void vga_fb_gfx_map_mouse(int *x, int *y);`
- `fb_write_row_packed` (function) `headers/vga_fb.h:217` `void fb_write_row_packed(int x, int y, const unsigned int *src, int n);` -- Graphics window view (headers/wm_gfxview.h owns the math).
- `fb_read_row_packed` (function) `headers/vga_fb.h:218` `void fb_read_row_packed(int x, int y, unsigned int *dst, int n);`
- `vga_fb_close_active` (function) `headers/vga_fb.h:219` `int vga_fb_close_active(void);`
- `vga_fb_focus_next` (function) `headers/vga_fb.h:223` `void vga_fb_focus_next(void);` -- Multi-window manager: Alt-Tab focus cycle, Super-Tab tiling, second * terminal.
- `vga_fb_focus_id` (function) `headers/vga_fb.h:224` `int vga_fb_focus_id(int id);`
- `vga_fb_focus_get` (function) `headers/vga_fb.h:225` `int vga_fb_focus_get(void);`
- `vga_fb_focus_event` (function) `headers/vga_fb.h:228` `const wm_notify_event_t *vga_fb_focus_event(void);` -- Focus event bus (wm_notify.h): last move for serial-observable state, * plus programmatic reporting for focus moves...
- `vga_fb_focus_report` (function) `headers/vga_fb.h:229` `void vga_fb_focus_report(int before, int source);`
- `vga_fb_theme_name` (function) `headers/vga_fb.h:230` `int vga_fb_theme_name(char *dst, int cap);`
- `vga_fb_ps2_owner` (function) `headers/vga_fb.h:236` `int vga_fb_ps2_owner(int pid);` -- PS/2 ownership for pid: 1 when pid may consume the keyboard port.
- `vga_fb_nterms_get` (function) `headers/vga_fb.h:237` `int vga_fb_nterms_get(void);`
- `vga_fb_term_split` (function) `headers/vga_fb.h:238` `int vga_fb_term_split(void);`
- `vga_fb_term_close_focused` (function) `headers/vga_fb.h:239` `int vga_fb_term_close_focused(void);`
- `vga_fb_tile_all` (function) `headers/vga_fb.h:240` `void vga_fb_tile_all(void);`
- `vga_fb_layout_set` (function) `headers/vga_fb.h:241` `int vga_fb_layout_set(int mode);`
- `vga_fb_layout_cycle` (function) `headers/vga_fb.h:242` `void vga_fb_layout_cycle(void);`
- `vga_fb_layout_get` (function) `headers/vga_fb.h:243` `int vga_fb_layout_get(void);`
- `vga_fb_layout_name` (function) `headers/vga_fb.h:244` `const char *vga_fb_layout_name(void);`
- `vga_fb_list_windows` (function) `headers/vga_fb.h:245` `void vga_fb_list_windows(void);`
- `wm_close_pending` (function) `headers/vga_fb.h:246` `int wm_close_pending(void);`
- `wm_clear_close` (function) `headers/vga_fb.h:247` `void wm_clear_close(void);`
- `wm_gfx_mode_active` (function) `headers/vga_fb.h:248` `int wm_gfx_mode_active(void);`
- `vga_fb_mouse_tick` (function) `headers/vga_fb.h:249` `void vga_fb_mouse_tick(void);`
- `vga_fb_mouse_init` (function) `headers/vga_fb.h:250` `void vga_fb_mouse_init(void);`
- `dock_bounce_counts` (function) `headers/vga_fb.h:253` `void dock_bounce_counts(unsigned long *kicks, unsigned long *paints);` -- Dock click bounce (Mac style): arm count and strip repaints while live, * for the serial-observable proof (`wm...
- `dock_click_count` (function) `headers/vga_fb.h:254` `void dock_click_count(unsigned long *edges);`
- `dock_pending_active` (function) `headers/vga_fb.h:255` `int dock_pending_active(void);`
- `pixels` (function) `headers/vga_fb.h:259` `* are heap buffers of packed pixels (fb_read_packed order), 0 on OOM or a * degenerate rect. A disabled effect or a...`
- `vga_fx_enabled` (function) `headers/vga_fb.h:263` `int vga_fx_enabled(void);`
- `vga_fx_snap_rect` (function) `headers/vga_fb.h:264` `unsigned int *vga_fx_snap_rect(int x, int y, int w, int h);`
- `vga_fx_restore_rect` (function) `headers/vga_fb.h:265` `void vga_fx_restore_rect(int x, int y, int w, int h, const unsigned int *buf);`
- `vga_fx_free` (function) `headers/vga_fb.h:266` `void vga_fx_free(unsigned int *buf);`
- `vga_fx_melt_rect` (function) `headers/vga_fb.h:267` `void vga_fx_melt_rect(int x, int y, int w, int h, const unsigned int *oldb, const unsigned int *newb);`
- `vga_fx_melt_from_black` (function) `headers/vga_fb.h:269` `void vga_fx_melt_from_black(int x, int y, int w, int h, const unsigned int *newb);`
- `vga_fb_set_gfx_mode` (function) `headers/vga_fb.h:280` `void vga_fb_set_gfx_mode(int on);` -- Graphics-mode pointer.

## headers/vga_fx.h
Imported by: `kernel/vga_fb.c`, `kernel/vga_fx.c`, `tests/test_fx.c`
- `vga_fx_rand` (function) `headers/vga_fx.h:30` `static inline unsigned long vga_fx_rand(unsigned long *s)` -- typedef struct { int step_px; int frame_ms; int max_delay; unsigned long seed; } vga_fx_config_t; /** Docstring...
- `vga_fx_init_cols` (function) `headers/vga_fx.h:47` `static inline int vga_fx_init_cols(const vga_fx_config_t *cfg, int *cols, int w)` -- Docstring: Seed consecutive column fronts with staggered delays.
- `vga_fx_advance` (function) `headers/vga_fx.h:71` `static inline int vga_fx_advance(const vga_fx_config_t *cfg, int *cols, int w, int h)` -- Docstring: Advance every column front one melt frame. * Returns 1 when every front reached the rect bottom, 0 otherwise.
- `vga_fx_front` (function) `headers/vga_fx.h:97` `static inline int vga_fx_front(int col_y, int h)` -- done = 0; } else if (cols[i] < h) { int dy = (cols[i] < 16) ? cols[i] + 1 : step; cols[i] += dy; if (cols[i] > h) {...
- `vga_fx_clamp_rect` (function) `headers/vga_fx.h:109` `static inline int vga_fx_clamp_rect(int *x, int *y, int *w, int *h, int fb_w, int fb_h)` -- /** Docstring: Rows [0, front) of one column already show the new frame. static inline int vga_fx_front(int col_y...

## headers/vma.h
Imported by: `headers/kernel.h`, `headers/sched.h`, `headers/spawn.h`, `kernel/spawn.c`, `tests/test_fault.c`, `tests/test_vma.c`, `tests/test_vma_bench.c`, `vma.c`
- `vma_tree_init` (function) `headers/vma.h:64` `void vma_tree_init(void);`
- `vma_tree_insert` (function) `headers/vma.h:65` `vma_node_t *vma_tree_insert(vma_node_t **root, unsigned long base, unsigned long len);`
- `vma_tree_find` (function) `headers/vma.h:66` `vma_node_t *vma_tree_find(vma_node_t *root, unsigned long base);`
- `vma_tree_find_containing` (function) `headers/vma.h:67` `vma_node_t *vma_tree_find_containing(vma_node_t *root, unsigned long va);`
- `vma_tree_delete` (function) `headers/vma.h:68` `int vma_tree_delete(vma_node_t **root, unsigned long base);`
- `vma_ctx_init` (function) `headers/vma.h:69` `void vma_ctx_init(vma_ctx_t *c, vma_node_t *pool);`
- `vma_ctx_bind` (function) `headers/vma.h:70` `void vma_ctx_bind(vma_ctx_t *c);`
- `vma_ctx_save` (function) `headers/vma.h:71` `void vma_ctx_save(vma_ctx_t *c);`
- `vma_view_save` (function) `headers/vma.h:86` `void vma_view_save(vma_view_t *v);`
- `vma_view_load` (function) `headers/vma.h:87` `void vma_view_load(const vma_view_t *v);`
- `vma_ctx_alloc` (function) `headers/vma.h:90` `vma_ctx_t *vma_ctx_alloc(void);` -- Heap-backed contexts live in sched.c (vma.c stays host-testable): * alloc returns a fresh context with a private...
- `vma_ctx_free` (function) `headers/vma.h:91` `void vma_ctx_free(vma_ctx_t *c);`

## headers/wm_events.h
Depends on: `headers/drivers/modifiers.h`
Imported by: `drivers/kbd.c`, `kernel/vga_fb.c`, `tests/test_wm.c`
- `wm_is_click_edge` (function) `headers/wm_events.h:52` `static inline int wm_is_click_edge(const wm_event_config_t *cfg, int prev_buttons, int curr_buttons)` -- int button; int wheel; } wm_event_t; /** Docstring: Centralized event translator configuration. typedef struct { int...
- `wm_is_release_edge` (function) `headers/wm_events.h:59` `static inline int wm_is_release_edge(const wm_event_config_t *cfg, int prev_buttons, int curr_but...` -- int wheel_step; } wm_event_config_t; /** Docstring: Default event configuration matching the PS/2 mouse path....
- `wm_translate_event` (function) `headers/wm_events.h:66` `static inline wm_event_t wm_translate_event(const wm_event_config_t *cfg, const wm_mouse_t *prev,...` -- static inline int wm_is_click_edge(const wm_event_config_t *cfg, int prev_buttons, int curr_buttons) { int mask =...
- `wm_event_suppresses_drag` (function) `headers/wm_events.h:104` `static inline int wm_event_suppresses_drag(const wm_event_t *evt)` -- return evt; } if (curr->wheel != 0) { evt.type = WM_EVT_SCROLL; return evt; } if (curr->x != prev->x || curr->y !=...
- `wm_combo_lookup` (function) `headers/wm_events.h:201` `static inline int wm_combo_lookup(int alt, int altgr, int sup, int e0, int sc, int path, int *zon...` -- {1, 0, 1, WM_SC_HOME, WM_PATH_COOKED, WM_COMBO_SNAP, WM_SNAP_TOP_LEFT}, {1, 0, 1, WM_SC_END, WM_PATH_COOKED...
- `wm_combo_lookup_mods` (function) `headers/wm_events.h:238` `static inline int wm_combo_lookup_mods(const modifier_state_t *st, int e0, int sc, int path, int ...` -- continue; } if (!(WM_COMBOS[i].paths & path)) { continue; } if (zone_out != 0) { zone_out = WM_COMBOS[i].zone; }...

## headers/wm_focus.h
Depends on: `headers/wm_window.h`
Imported by: `kernel/vga_fb.c`, `tests/test_wm.c`
- `wm_focus_selectable` (function) `headers/wm_focus.h:23` `static inline int wm_focus_selectable(const wm_focus_state_t *st, int id)` -- #ifndef WM_FOCUS_H #define WM_FOCUS_H #include "wm_window.h" /** Docstring: Focus state snapshot consumed by every...
- `wm_focus_next` (function) `headers/wm_focus.h:38` `static inline int wm_focus_next(const wm_focus_state_t *st)` -- { if (st == 0) { return 0; } if (id == WM_WINDOW_GFX_ID) { return st->gfx_active ?
- `wm_focus_set` (function) `headers/wm_focus.h:55` `static inline int wm_focus_set(const wm_focus_state_t *st, int id)` -- int i; if (st == 0) { return 0; } for (i = 0; i < 4; i++) { flat[i] = 0; } for (i = 0; i < st->nterms && i < 4; i++)...

## headers/wm_geom.h
Imported by: `headers/wm_window.h`, `kernel/vga_fb.c`, `tests/test_wm.c`
- `wm_rect_valid` (function) `headers/wm_geom.h:33` `static inline int wm_rect_valid(const wm_rect_t *r)` -- } wm_geom_config_t; /** Docstring: Default geometry matching the kernel 8x8 font layout. #define...
- `wm_rect_contains` (function) `headers/wm_geom.h:39` `static inline int wm_rect_contains(const wm_rect_t *r, int px, int py)` -- typedef struct { int x; int y; int w; int h; } wm_rect_t; /** Docstring: True when the rectangle can contain any...
- `wm_title_bar_rect` (function) `headers/wm_geom.h:48` `static inline wm_rect_t wm_title_bar_rect(const wm_geom_config_t *cfg, int px, int py, int w)` -- { return r != 0 && r->w > 0 && r->h > 0; } /** Docstring: True when point px,py lies inside rectangle r. static...
- `wm_content_rect` (function) `headers/wm_geom.h:59` `static inline wm_rect_t wm_content_rect(const wm_geom_config_t *cfg, int px, int py, int w, int h)` -- } /** Docstring: Title bar strip for a window at px,py with total width w. static inline wm_rect_t...
- `wm_scrollbar_rect` (function) `headers/wm_geom.h:71` `static inline wm_rect_t wm_scrollbar_rect(const wm_geom_config_t *cfg, int px, int py, int conten...` -- /** Docstring: Text content area below the title bar. static inline wm_rect_t wm_content_rect(const wm_geom_config_t...
- `wm_hit_title_bar` (function) `headers/wm_geom.h:84` `static inline int wm_hit_title_bar(const wm_geom_config_t *cfg, int wx, int wy, int w, int px, in...` -- /** Docstring: Scrollbar strip at the right edge of the content area. static inline wm_rect_t...
- `wm_clamp_point` (function) `headers/wm_geom.h:91` `static inline void wm_clamp_point(int *px, int *py, int fb_w, int fb_h)` -- r.y = py + th; r.w = sw; r.h = content_h > 0 ? content_h : 0; return r; } /** Docstring: True when point px,py hits...

## headers/wm_gfxview.h
Imported by: `kernel/vga_fb.c`, `tests/test_wm.c`
- `wm_gfxview_mode_name` (function) `headers/wm_gfxview.h:64` `static inline const char *wm_gfxview_mode_name(int mode)` -- Docstring: One computed view: frame (chrome plus content area), * title strip height (0 in fullscreen) and the...
- `wm_gfxview_dims_ok` (function) `headers/wm_gfxview.h:79` `static inline int wm_gfxview_dims_ok(int w, int h)` -- { switch (mode) { case WM_GFXVIEW_FLOAT: return "floating"; case WM_GFXVIEW_TILED: return "tiled"; case...
- `Downscale` (function) `headers/wm_gfxview.h:88` `* Downscale (fit below 1x) always takes the exact fit. Returns 1 on
 * success, 0 on degenerate i...`
- `wm_gfxview_clamp` (function) `headers/wm_gfxview.h:134` `static inline void wm_gfxview_clamp(wm_gfxview_rect_t *r, int fb_w, int fb_h)` -- Docstring: Clamp a rect inside the framebuffer by moving, then by * shrinking when it is larger than the screen.
- `wm_gfxview_place_content` (function) `headers/wm_gfxview.h:160` `static inline int wm_gfxview_place_content(const wm_gfxview_config_t *cfg, int sw, int sh,
      ...` -- r->x = fb_w - r->w; } if (r->y + r->h > fb_h) { r->y = fb_h - r->h; } if (r->x < 0) { r->x = 0; } if (r->y < 0) {...
- `wm_gfxview_map_point` (function) `headers/wm_gfxview.h:255` `static inline int wm_gfxview_map_point(const wm_gfxview_t *v, int sw, int sh,
                   ...` -- Docstring: Map a framebuffer point into back-buffer space.
- `wm_gfxview_ease` (function) `headers/wm_gfxview.h:291` `static inline long wm_gfxview_ease(int t, int n, long den)` -- Docstring: Ease-out cubic progress in [0, den] for step t of n.
- `wm_gfxview_lerp_rect` (function) `headers/wm_gfxview.h:313` `static inline int wm_gfxview_lerp_rect(const wm_gfxview_rect_t *a, const wm_gfxview_rect_t *b,
  ...` -- return 0; } inv = (long)(n - t); r = den - (den * inv * inv * inv) / ((long)n * (long)n * (long)n); if (r < 0) { r =...
- `wm_gfxview_rect_same` (function) `headers/wm_gfxview.h:336` `static inline int wm_gfxview_rect_same(const wm_gfxview_rect_t *a, const wm_gfxview_rect_t *b)` -- out->x = a->x + (int)(((long)(b->x - a->x) * p) / den); out->y = a->y + (int)(((long)(b->y - a->y) * p) / den)...

## headers/wm_layout.h
Imported by: `kernel/shell.c`, `kernel/vga_fb.c`, `tests/test_wm.c`
- `wm_layout_mode_name` (function) `headers/wm_layout.h:57` `static inline const char *wm_layout_mode_name(int mode)` -- /** Docstring: Default layout matching the legacy two terminal split. #define WM_LAYOUT_CONFIG_DEFAULT { 0, 4, 2...
- `wm_layout_mode_valid` (function) `headers/wm_layout.h:76` `static inline int wm_layout_mode_valid(int mode)` -- case WM_LAYOUT_BSP: return "bsp"; case WM_LAYOUT_CASCADE: return "cascade"; case WM_LAYOUT_FIBONACCI: return...
- `wm_layout_clamp_cell` (function) `headers/wm_layout.h:82` `static inline int wm_layout_clamp_cell(wm_layout_cell_t *cell, int max_cols, int max_rows)` -- case WM_LAYOUT_FULLSCREEN: return "fullscreen"; default: return 0; } } /** Docstring: True when mode is a selectable...
- `wm_layout_fullscreen_cell` (function) `headers/wm_layout.h:118` `static inline int wm_layout_fullscreen_cell(int max_cols, int max_rows, wm_layout_cell_t *out)` -- } if (cell->rows < 1) { cell->rows = 1; } if (cell->x + cell->cols > max_cols) { cell->cols = max_cols - cell->x; }...
- `wm_layout_compute_tile` (function) `headers/wm_layout.h:135` `static inline int wm_layout_compute_tile(const wm_layout_window_t *wins, int nwin, int max_cols, ...` -- return 0; } if (max_cols <= 0 || max_rows <= 0) { return 0; } out->x = 0; out->y = 0; out->cols = max_cols...
- `wm_layout_compute_bsp` (function) `headers/wm_layout.h:182` `static inline int wm_layout_compute_bsp(const wm_layout_window_t *wins, int nwin, int max_cols, i...` -- } base = max_rows / nwin; rem = max_rows - base * nwin; for (i = 0; i < nwin; i++) { out[i].x = 0; out[i].y = i *...
- `wm_layout_compute_cascade` (function) `headers/wm_layout.h:250` `static inline int wm_layout_compute_cascade(const wm_layout_config_t *cfg, const wm_layout_window...` -- } out[i].x = rx; out[i].y = ry; out[i].cols = rw; out[i].rows = half; out[i].fullscreen = 0; ry = ry + half; rh = rh...
- `wm_layout_compute_fibonacci` (function) `headers/wm_layout.h:285` `static inline int wm_layout_compute_fibonacci(const wm_layout_config_t *cfg, const wm_layout_wind...` -- out[i].cols = max_cols - ox; out[i].rows = max_rows - oy; out[i].fullscreen = 0; if (out[i].cols < 1) { out[i].cols...
- `wm_layout_compute` (function) `headers/wm_layout.h:361` `static inline int wm_layout_compute(const wm_layout_config_t *cfg, const wm_layout_window_t *wins...` -- } out[i].x = rx; out[i].y = ry; out[i].cols = rw; out[i].rows = cut; out[i].fullscreen = 0; ry = ry + cut; rh = rh...
- `wm_layout_same` (function) `headers/wm_layout.h:443` `static inline int wm_layout_same(const wm_layout_cell_t *a, const wm_layout_cell_t *b, int n)` -- } if (n != nc) { return 0; } for (i = 0; i < nc; i++) { if (!wm_layout_clamp_cell(&cells[i], max_cols, max_rows)) {...

## headers/wm_notify.h
Imported by: `headers/vga_fb.h`, `kernel/shell.c`, `kernel/vga_fb.c`, `tests/test_notify.c`
- `wm_notify_reset` (function) `headers/wm_notify.h:51` `static inline void wm_notify_reset(wm_notify_bus_t *bus)` -- /** Docstring: Focus listener, runs synchronously inside emit. typedef void (*wm_notify_handler_t)(const...
- `wm_notify_subscribe` (function) `headers/wm_notify.h:66` `static inline int wm_notify_subscribe(wm_notify_bus_t *bus,
                                     ...` -- { int i; if (bus == 0) return; for (i = 0; i < WM_NOTIFY_MAX_HANDLERS; i++) bus->handlers[i] = 0; bus->count = 0...
- `wm_notify_emit` (function) `headers/wm_notify.h:76` `static inline void wm_notify_emit(wm_notify_bus_t *bus,
                                  const w...` -- bus->has_event = 0; } /** Docstring: Register one listener, -1 when full or null. static inline int...
- `wm_notify_last` (function) `headers/wm_notify.h:90` `static inline const wm_notify_event_t *wm_notify_last(
    const wm_notify_bus_t *bus)` -- static inline void wm_notify_emit(wm_notify_bus_t *bus, const wm_notify_event_t *event) { int i; if (bus == 0 ||...
- `wm_notify_src_name` (function) `headers/wm_notify.h:98` `static inline const char *wm_notify_src_name(int source)` -- } bus->last = *event; bus->has_event = 1; } /** Docstring: Last emitted event, 0 when none was ever emitted. static...

## headers/wm_render.h
Depends on: `headers/wm_window.h`
Imported by: `kernel/vga_fb.c`, `tests/test_wm.c`
- `wm_build_render_plan` (function) `headers/wm_render.h:39` `static inline int wm_build_render_plan(const wm_render_config_t *cfg, const int *present, int nte...` -- typedef struct { wm_layer_t layer; int id; } wm_render_item_t; /** Docstring: Centralized render pipeline...

## headers/wm_tiling.h
Imported by: `kernel/vga_fb.c`, `tests/test_wm.c`
- `wm_tile_layout` (function) `headers/wm_tiling.h:22` `static inline int wm_tile_layout(const int *present, int nterms, int gfx_active, int max_cols, in...` -- #ifndef WM_TILING_H #define WM_TILING_H /** Docstring: Terminal cell in character units. typedef struct { int x; int...

## headers/wm_window.h
Depends on: `headers/wm_geom.h`
Imported by: `headers/wm_focus.h`, `headers/wm_render.h`, `kernel/vga_fb.c`, `tests/test_wm.c`
- `wm_window_active` (function) `headers/wm_window.h:41` `static inline int wm_window_active(const wm_window_t *w)` -- /** Docstring: Unified window descriptor in framebuffer pixels. typedef struct { wm_window_kind_t kind; int id; int...
- `wm_window_rect` (function) `headers/wm_window.h:47` `static inline wm_rect_t wm_window_rect(const wm_window_t *w)` -- int y; int w; int h; int present; int minimized; } wm_window_t; /** Docstring: True when the window can receive...
- `wm_window_contains` (function) `headers/wm_window.h:58` `static inline int wm_window_contains(const wm_window_t *w, int px, int py)` -- } /** Docstring: Rectangle covering the whole window including decorations. static inline wm_rect_t...
- `wm_window_title_hits` (function) `headers/wm_window.h:68` `static inline int wm_window_title_hits(const wm_geom_config_t *cfg, const wm_window_t *w, int px,...` -- return r; } /** Docstring: True when point px,py hits the window body or decorations. static inline int...
- `wm_focus_next_id` (function) `headers/wm_window.h:77` `static inline int wm_focus_next_id(const int *present, int nterms, int gfx_active, int focus)` -- } return wm_rect_contains(&r, px, py); } /** Docstring: True when point px,py hits the window title bar. static...
- `wm_paint_order` (function) `headers/wm_window.h:114` `static inline int wm_paint_order(const int *present, int nterms, int focus, int *order, int cap)` -- return focus; } for (k = 0; k < n; k++) { if (ids[k] == focus) { at = k; } } if (at < 0) { return ids[0]; } return...

## headers/zip.h
Imported by: `kernel/shell.c`, `kernel/syscalls.c`
- `miniz` (function) `headers/zip.h:6` `* * The shell builtins over miniz (see zip.c) are declared here so kernel.c's * shell dispatcher can route the...`
- `shell_cmd_zip` (function) `headers/zip.h:15` `void shell_cmd_zip(int argc, char **argv);`

## kernel.c
Depends on: `headers/abi.h`, `headers/arch/x86/boot/bootdefs.h`, `headers/arch/x86/msr.h`, `headers/block.h`, `headers/drivers/usbblk.h`, `headers/drivers/usbhid.h`, `headers/drivers/virtio_blk.h`, `headers/drivers/xhci.h`, `headers/ide.h`, `headers/minifs.h`, `headers/net.h`, `headers/pcache.h`, `headers/sb16.h`, `headers/sched.h`, `headers/smp.h`, `headers/syscall_asm.h`, `headers/vga_fb.h`
- `table` (function) `kernel.c:103` `* Symbol table (for resolving program references) * ================================================================...`
- `syscall_init` (function) `kernel.c:116` `void syscall_init(void)`
- `ksyscall` (function) `kernel.c:129` `extern long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);`
- `kstack` (function) `kernel.c:145` `* Reading gs:8 instead resolves every thread to the wrong kstack (0 on * the BSP, 1 on APs): harmless while a single...`
- `ms` (function) `kernel.c:184` `* 0 ms (TSC ticks since power-on divided down, still monotonic);`
- `bootlog_mark` (function) `kernel.c:191` `void bootlog_mark(const char *name)`
- `bootlog_report` (function) `kernel.c:198` `void bootlog_report(void)`
- `EM` (function) `kernel.c:220` `* CR0: clear EM (bit 2), set MP (bit 1);`
- `size` (function) `kernel.c:261` `* image size (see kernel.ld);`
- `tables` (function) `kernel.c:283` `* tables (already built above) for its uncached register window and the
     * heap for its rings...`

## kernel/abi.c
Depends on: `headers/abi.h`
- `abi_parse_num` (function) `kernel/abi.c:20` `static int abi_parse_num(const char **pp, const char *end, unsigned long *out)` -- order, junk, overflow, missing newline) fails closed as BAD_FORMAT.
- `abi_verify` (function) `kernel/abi.c:38` `int abi_verify(const char *text, long version, unsigned long checksum)` -- return 0; while (p < end && *p >= '0' && *p <= '9') { unsigned digit = (unsigned)(*p - '0'); if (v >...
- `abi_check_manifest` (function) `kernel/abi.c:74` `int abi_check_manifest(void)` -- p += 2; if (!abi_parse_num(&p, end, &c)) return ABI_BAD_FORMAT; if (p + 1 != end || *p != '\n') return...

## kernel/batch.c
Depends on: `headers/batch.h`
- `batch_exec` (function) `kernel/batch.c:19` `long batch_exec(const batch_op_t *ops, long *results, int count,
                int *completed, ...` -- Docstring: Run ops in order, storing one result per index.

## kernel/clip.c
- `clip_set` (function) `kernel/clip.c:25` `int clip_set(const char *data, unsigned long len)` -- Docstring: Replace the clipboard with len bytes from data.
- `clip_clear` (function) `kernel/clip.c:48` `void clip_clear(void)` -- Docstring: Copy the clipboard into out (cap bytes).
- `clip_len_get` (function) `kernel/clip.c:55` `int clip_len_get(void)` -- Docstring: Current length, or -1 when empty.

## kernel/console.c
Depends on: `headers/sched.h`, `headers/vga_fb.h`
- `vga_get_x` (function) `kernel/console.c:18` `int vga_get_x(void)`
- `vga_get_y` (function) `kernel/console.c:19` `int vga_get_y(void)`
- `vga_set_xy` (function) `kernel/console.c:20` `void vga_set_xy(int x, int y)`
- `vga_get_color` (function) `kernel/console.c:21` `char vga_get_color(void)`
- `vga_offset` (function) `kernel/console.c:23` `static inline unsigned vga_offset(int x, int y)`
- `vga_clear` (function) `kernel/console.c:25` `void vga_clear(void)`
- `vga_set_cursor` (function) `kernel/console.c:36` `void vga_set_cursor(int x, int y)`
- `vga_scroll` (function) `kernel/console.c:56` `void vga_scroll(void)`
- `vga_newline` (function) `kernel/console.c:75` `void vga_newline(void)`
- `vga_cursor_enable` (function) `kernel/console.c:81` `void vga_cursor_enable(int on)`
- `vga_raw_space` (function) `kernel/console.c:88` `static void vga_raw_space(void)`
- `redir_grow` (function) `kernel/console.c:110` `static int redir_grow(void)`
- `redirect_active` (function) `kernel/console.c:120` `int redirect_active(void)`
- `redirect_putc` (function) `kernel/console.c:122` `static int redirect_putc(char c)`
- `redirect_suspend` (function) `kernel/console.c:129` `int redirect_suspend(void)`
- `redirect_resume` (function) `kernel/console.c:135` `void redirect_resume(int was)`
- `redirect_begin` (function) `kernel/console.c:139` `int redirect_begin(void)`
- `redirect_commit` (function) `kernel/console.c:147` `int redirect_commit(const char *path, int append_mode)`
- `redirect_pending` (function) `kernel/console.c:185` `unsigned long redirect_pending(void)` -- Docstring: Bytes waiting in the capture, 0 when idle or overflowed.
- `redirect_take_into` (function) `kernel/console.c:196` `unsigned long redirect_take_into(char *dst, unsigned long cap,
        unsigned long *len_out)` -- Docstring: Drain the capture into the caller's arena memory instead of a fresh heap block.
- `redirect_discard` (function) `kernel/console.c:216` `void redirect_discard(void)` -- Docstring: Drop the capture without any allocation.
- `vga_putc` (function) `kernel/console.c:223` `void vga_putc(char c)`
- `vga_puts` (function) `kernel/console.c:267` `void vga_puts(const char *s)`
- `register_libc_symbols` (function) `kernel/console.c:271` `void register_libc_symbols(void)`

## kernel/console_in.c
Depends on: `headers/drivers/kbd.h`, `headers/drivers/usbhid.h`, `headers/drivers/xhci.h`, `headers/kernel/console_in.h`, `headers/pipe.h`, `headers/vga_fb.h`
- `console_stdin_push` (function) `kernel/console_in.c:32` `int console_stdin_push(const char *data, unsigned long len)` -- Pipeline stdin override (see console_in.h): heap buffer served ahead of every live source while set.
- `console_stdin_clear` (function) `kernel/console_in.c:46` `void console_stdin_clear(void)` -- int console_stdin_push(const char *data, unsigned long len) { unsigned long i; if (!data || len == 0u || len >...
- `console_stdin_active` (function) `kernel/console_in.c:56` `int console_stdin_active(void)` -- Docstring: True while a pipeline stdin buffer is installed (drained * or not).
- `pb_empty` (function) `kernel/console_in.c:60` `static int pb_empty(void)`
- `pb_count` (function) `kernel/console_in.c:61` `static int pb_count(void)`
- `pb_push_back` (function) `kernel/console_in.c:62` `static void pb_push_back(unsigned char c)`
- `pb_push_front` (function) `kernel/console_in.c:67` `static void pb_push_front(unsigned char c)`
- `pb_pop` (function) `kernel/console_in.c:72` `static int pb_pop(void)`
- `pb_peek` (function) `kernel/console_in.c:78` `static int pb_peek(void)`
- `console_ungetc` (function) `kernel/console_in.c:85` `void console_ungetc(unsigned char c)` -- Docstring: Push one byte back into the console FIFO; the next * console_getc/console_peek serves it first.
- `console_poll_usb` (function) `kernel/console_in.c:93` `static void console_poll_usb(void)` -- Docstring: Service the polled USB input path: drain the controller's event ring, then take one report from each...
- `console_ps2_live` (function) `kernel/console_in.c:106` `static int console_ps2_live(void)` -- Docstring: True when the PS/2 data port should be read.
- `raw_blocking_getc` (function) `kernel/console_in.c:118` `static int raw_blocking_getc(void)` -- Docstring: Next raw byte (kbd queue, then serial, then USB, then PS/2) without touching the pushback FIFO; blocks...
- `raw_try_getc` (function) `kernel/console_in.c:139` `static int raw_try_getc(void)` -- } console_poll_usb(); if (!kbd_q_empty()) return kbd_q_pop(); if (console_ps2_live()) { int c = kbd_read(); if (c >=...
- `ESC` (function) `kernel/console_in.c:157` `* The bound keeps a bare ESC (never completed into a sequence) from
 * hanging the reader. */
#de...`
- `consume_page_after_esc` (function) `kernel/console_in.c:178` `static int consume_page_after_esc(void)` -- Docstring: Called after an ESC byte has been read.
- `console_getc` (function) `kernel/console_in.c:205` `int console_getc(void)` -- Docstring: Blocking read from either the PS/2 keyboard or COM1 serial line.
- `console_peek` (function) `kernel/console_in.c:233` `int console_peek(void)` -- Docstring: Next buffered byte without consuming it, or -1 when nothing is available right now.
- `console_raw_try` (function) `kernel/console_in.c:246` `int console_raw_try(void)` -- Docstring: Raw console multiplexer for the GETC_RAW syscall.
- `console_raw_get` (function) `kernel/console_in.c:250` `int console_raw_get(void)`
- `console_job_try` (function) `kernel/console_in.c:257` `int console_job_try(void)` -- Docstring: GETC_RAW source for ring-3 background jobs.
- `console_job_get` (function) `kernel/console_in.c:267` `int console_job_get(void)` -- Docstring: GETC_RAW source for ring-3 background jobs.
- `scrollback_render` (function) `kernel/console_in.c:283` `static void scrollback_render(int voff, int total, const unsigned char *saved)`
- `sb_next` (function) `kernel/console_in.c:311` `static int sb_next(void)` -- Docstring: Reads the next scrollback key event: PageUp/PageDown navigate; any other key (or a non-page escape...
- `scrollback_view` (function) `kernel/console_in.c:321` `static void scrollback_view(int initial_dir)`

## kernel/cvm_host.c
- `n_strcmp` (function) `kernel/cvm_host.c:22` `static int64_t n_strcmp(void *vm, int ac, uint64_t *av)`
- `n_strncmp` (function) `kernel/cvm_host.c:28` `static int64_t n_strncmp(void *vm, int ac, uint64_t *av)`
- `n_strcpy` (function) `kernel/cvm_host.c:35` `static int64_t n_strcpy(void *vm, int ac, uint64_t *av)`
- `n_strncpy` (function) `kernel/cvm_host.c:41` `static int64_t n_strncpy(void *vm, int ac, uint64_t *av)`
- `n_memcpy` (function) `kernel/cvm_host.c:48` `static int64_t n_memcpy(void *vm, int ac, uint64_t *av)`
- `n_memset` (function) `kernel/cvm_host.c:55` `static int64_t n_memset(void *vm, int ac, uint64_t *av)`
- `n_memmove` (function) `kernel/cvm_host.c:61` `static int64_t n_memmove(void *vm, int ac, uint64_t *av)`
- `n_memcmp` (function) `kernel/cvm_host.c:68` `static int64_t n_memcmp(void *vm, int ac, uint64_t *av)`
- `n_strchr` (function) `kernel/cvm_host.c:75` `static int64_t n_strchr(void *vm, int ac, uint64_t *av)`
- `n_strstr` (function) `kernel/cvm_host.c:81` `static int64_t n_strstr(void *vm, int ac, uint64_t *av)`
- `n_malloc` (function) `kernel/cvm_host.c:88` `static int64_t n_malloc(void *vm, int ac, uint64_t *av)`
- `n_free` (function) `kernel/cvm_host.c:93` `static int64_t n_free(void *vm, int ac, uint64_t *av)`
- `n_calloc` (function) `kernel/cvm_host.c:98` `static int64_t n_calloc(void *vm, int ac, uint64_t *av)`
- `n_realloc` (function) `kernel/cvm_host.c:106` `static int64_t n_realloc(void *vm, int ac, uint64_t *av)`
- `n_exit` (function) `kernel/cvm_host.c:114` `static int64_t n_exit(void *vm, int ac, uint64_t *av)`
- `n_fopen` (function) `kernel/cvm_host.c:121` `static int64_t n_fopen(void *vm, int ac, uint64_t *av)`
- `n_fclose` (function) `kernel/cvm_host.c:128` `static int64_t n_fclose(void *vm, int ac, uint64_t *av)`
- `n_fread` (function) `kernel/cvm_host.c:134` `static int64_t n_fread(void *vm, int ac, uint64_t *av)`
- `n_fwrite` (function) `kernel/cvm_host.c:141` `static int64_t n_fwrite(void *vm, int ac, uint64_t *av)`
- `n_fseek` (function) `kernel/cvm_host.c:148` `static int64_t n_fseek(void *vm, int ac, uint64_t *av)`
- `n_ftell` (function) `kernel/cvm_host.c:154` `static int64_t n_ftell(void *vm, int ac, uint64_t *av)`
- `n_rewind` (function) `kernel/cvm_host.c:160` `static int64_t n_rewind(void *vm, int ac, uint64_t *av)`
- `n_fputs` (function) `kernel/cvm_host.c:167` `static int64_t n_fputs(void *vm, int ac, uint64_t *av)`
- `n_fputc` (function) `kernel/cvm_host.c:173` `static int64_t n_fputc(void *vm, int ac, uint64_t *av)`
- `n_fgetc` (function) `kernel/cvm_host.c:179` `static int64_t n_fgetc(void *vm, int ac, uint64_t *av)`
- `n_ungetc` (function) `kernel/cvm_host.c:185` `static int64_t n_ungetc(void *vm, int ac, uint64_t *av)`
- `n_fflush` (function) `kernel/cvm_host.c:191` `static int64_t n_fflush(void *vm, int ac, uint64_t *av)`
- `n_putchar` (function) `kernel/cvm_host.c:197` `static int64_t n_putchar(void *vm, int ac, uint64_t *av)`
- `n_write` (function) `kernel/cvm_host.c:204` `static int64_t n_write(void *vm, int ac, uint64_t *av)`
- `n_read` (function) `kernel/cvm_host.c:213` `static int64_t n_read(void *vm, int ac, uint64_t *av)`
- `n_puts` (function) `kernel/cvm_host.c:228` `static int64_t n_puts(void *vm, int ac, uint64_t *av)`
- `n_atol` (function) `kernel/cvm_host.c:236` `static int64_t n_atol(void *vm, int ac, uint64_t *av)`
- `n_strtol` (function) `kernel/cvm_host.c:249` `static int64_t n_strtol(void *vm, int ac, uint64_t *av)`
- `n_stderr_addr` (function) `kernel/cvm_host.c:262` `static int64_t n_stderr_addr(void *vm, int ac, uint64_t *av)`
- `n_stdout_addr` (function) `kernel/cvm_host.c:267` `static int64_t n_stdout_addr(void *vm, int ac, uint64_t *av)`
- `n_stdin_addr` (function) `kernel/cvm_host.c:272` `static int64_t n_stdin_addr(void *vm, int ac, uint64_t *av)`
- `kout_char` (function) `kernel/cvm_host.c:277` `static void kout_char(void *ctx, char c)`
- `kout_uint` (function) `kernel/cvm_host.c:283` `static void kout_uint(void *ctx, unsigned long long v, int base, int upper)`
- `kformat` (function) `kernel/cvm_host.c:296` `static void kformat(void *ctx, const char *fmt, uint64_t *argv, int argc)`
- `n_fprintf` (function) `kernel/cvm_host.c:362` `static int64_t n_fprintf(void *vm, int ac, uint64_t *av)`
- `n_printf` (function) `kernel/cvm_host.c:369` `static int64_t n_printf(void *vm, int ac, uint64_t *av)`
- `n_sprintf` (function) `kernel/cvm_host.c:376` `static int64_t n_sprintf(void *vm, int ac, uint64_t *av)`
- `n_snprintf` (function) `kernel/cvm_host.c:384` `static int64_t n_snprintf(void *vm, int ac, uint64_t *av)`
- `register_host_natives` (function) `kernel/cvm_host.c:392` `static void register_host_natives(CvmState *vm)`
- `cvm_main` (function) `kernel/cvm_host.c:437` `int cvm_main(int argc, char **argv)`

## kernel/editor.c
Depends on: `headers/editor.h`, `headers/shell.h`
- `edit_alloc` (function) `kernel/editor.c:38` `static EditBuf *edit_alloc(const char *fname)`
- `edit_free` (function) `kernel/editor.c:55` `static void edit_free(EditBuf *e)`
- `edit_load` (function) `kernel/editor.c:61` `static int edit_load(EditBuf *e)`
- `edit_save` (function) `kernel/editor.c:99` `static int edit_save(EditBuf *e)`
- `edit_print` (function) `kernel/editor.c:113` `static void edit_print(EditBuf *e, int idx)`
- `edit_list` (function) `kernel/editor.c:123` `static void edit_list(EditBuf *e, int start, int end)` -- List a (possibly empty) range [start, end], both 1-based inclusive.
- `edit_set_line` (function) `kernel/editor.c:135` `static int edit_set_line(EditBuf *e, int idx, const char *text)`
- `edit_insert` (function) `kernel/editor.c:144` `static int edit_insert(EditBuf *e, int idx, const char *text)`
- `edit_delete` (function) `kernel/editor.c:154` `static int edit_delete(EditBuf *e, int idx)`
- `edit_line_cstr` (function) `kernel/editor.c:166` `static void edit_line_cstr(EditLine *l, char *out)` -- Copy a line into a NUL-terminated scratch buffer (lines are otherwise * stored length-prefixed without a terminator).
- `edit_search` (function) `kernel/editor.c:171` `static void edit_search(EditBuf *e, const char *needle)`
- `edit_status` (function) `kernel/editor.c:188` `static void edit_status(EditBuf *e)`
- `edit_usage` (function) `kernel/editor.c:196` `static void edit_usage(void)`
- `edit_refuse_save` (function) `kernel/editor.c:207` `static int edit_refuse_save(EditBuf *e)` -- A buffer that did not hold the whole file must never be written back: * saving it would drop the part that was never...
- `edit_arg_line` (function) `kernel/editor.c:213` `static int edit_arg_line(int argc, char **argv, EditBuf *e, int *out)`
- `edit_loop` (function) `kernel/editor.c:224` `static void edit_loop(EditBuf *e)`
- `shell_cmd_edit` (function) `kernel/editor.c:329` `void shell_cmd_edit(int argc, char **argv)`

## kernel/exec.c
Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/arch/x86/msr.h`, `headers/drivers/kbd.h`, `headers/proc_sec.h`, `headers/sched.h`, `headers/vga_fb.h`
- `vga_mode_set` (function) `kernel/exec.c:61` `void vga_mode_set(int on)`
- `vga_mode_is_active` (function) `kernel/exec.c:62` `int  vga_mode_is_active(void)`
- `vga_gfx_ran_set` (function) `kernel/exec.c:63` `void vga_gfx_ran_set(int on)`
- `k_user_fault_return` (function) `kernel/exec.c:66` `void k_user_fault_return(void)` -- VGA mode tracking: set/cleared by k_exec_user and k_run_rel when a * graphics program owns the display. static int...
- `setup_user_stack` (function) `kernel/exec.c:83` `unsigned long *setup_user_stack(char *sbase, unsigned long ssize,
                               ...`
- `k_run_rel` (function) `kernel/exec.c:233` `int k_run_rel(prog_entry_t entry, int argc, char **argv)`
- `kexit` (function) `kernel/exec.c:284` `void kexit(int code)`

## kernel/futex.c
Depends on: `headers/futex.h`, `headers/sync.h`
- `futex_hash` (function) `kernel/futex.c:23` `static unsigned long futex_hash(unsigned long uaddr)`
- `futex_bucket` (function) `kernel/futex.c:31` `static futex_bucket_t *futex_bucket(unsigned long uaddr)`
- `futex_init` (function) `kernel/futex.c:36` `void futex_init(void)` -- static unsigned long futex_hash(unsigned long uaddr) { unsigned long word = uaddr >> 2; word ^= word >> 16; word *=...
- `futex_linux_cmd` (function) `kernel/futex.c:84` `int futex_linux_cmd(long op)` -- futex_table.awaited[cur->pid] = uaddr; if (b->head == WQ_NONE) { b->head = cur->pid; b->tail = cur->pid; } else {...
- `futex_timeout_remaining_us` (function) `kernel/futex.c:95` `long futex_timeout_remaining_us(int cmd, long sec, long nsec, unsigned long now_us)` -- } /** Docstring: Decode a Linux futex(2) op to WAIT/WAKE. int futex_linux_cmd(long op) { long cmd; if (op < 0)...
- `futex_wake` (function) `kernel/futex.c:112` `long futex_wake(unsigned long uaddr, int n)` -- Docstring: Wake up to n sleepers waiting on uaddr.

## kernel/klog.c
- `klog_set_level` (function) `kernel/klog.c:29` `void klog_set_level(log_level_t level)`
- `klog_set_subsys_level` (function) `kernel/klog.c:33` `void klog_set_subsys_level(log_subsystem_t subsys, log_level_t level)`
- `klog_disable` (function) `kernel/klog.c:38` `void klog_disable(void)`
- `klog_enable` (function) `kernel/klog.c:39` `void klog_enable(void)`
- `klog` (function) `kernel/klog.c:41` `void klog(log_level_t level, log_subsystem_t subsys,
          const char *fmt, ...)`
- `klog_hexdump` (function) `kernel/klog.c:119` `void klog_hexdump(log_level_t level, log_subsystem_t subsys,
                  const void *data, ...`

## kernel/ldso_parse.c
Depends on: `headers/ldso.h`
Imported by: `tests/test_ldso.c`
- `ldso_rd16` (function) `kernel/ldso_parse.c:18` `static unsigned ldso_rd16(const unsigned char *p)`
- `ldso_rd32` (function) `kernel/ldso_parse.c:22` `static unsigned long ldso_rd32(const unsigned char *p)`
- `ldso_rd64` (function) `kernel/ldso_parse.c:27` `static unsigned long long ldso_rd64(const unsigned char *p)`
- `ldso_slice` (function) `kernel/ldso_parse.c:32` `static int ldso_slice(const unsigned char *file, unsigned long long fsize,
        unsigned long ...`
- `ldso_valid_ehdr` (function) `kernel/ldso_parse.c:40` `static int ldso_valid_ehdr(const unsigned char *file,
        unsigned long long fsize)`
- `ldso_vaddr_to_offset` (function) `kernel/ldso_parse.c:54` `int ldso_vaddr_to_offset(const unsigned char *file,
        unsigned long long fsize, unsigned lo...`
- `ldso_segments` (function) `kernel/ldso_parse.c:86` `int ldso_segments(const unsigned char *file, unsigned long long fsize,
        LdsoSeg *segs, uns...`
- `ldso_find_dynamic` (function) `kernel/ldso_parse.c:120` `int ldso_find_dynamic(const unsigned char *file, unsigned long long fsize,
        unsigned long ...`
- `ldso_scan_dynamic` (function) `kernel/ldso_parse.c:150` `int ldso_scan_dynamic(const unsigned char *file, unsigned long long fsize,
        unsigned long ...`
- `ldso_sym_count` (function) `kernel/ldso_parse.c:213` `int ldso_sym_count(const unsigned char *file, unsigned long long fsize,
        unsigned long lon...`
- `ldso_copy_str` (function) `kernel/ldso_parse.c:227` `int ldso_copy_str(const unsigned char *file, unsigned long long fsize,
        unsigned long long...`
- `ldso_name_eq` (function) `kernel/ldso_parse.c:250` `static int ldso_name_eq(const unsigned char *tab, unsigned long long strsz,
        unsigned long...`
- `ldso_sym_lookup` (function) `kernel/ldso_parse.c:263` `int ldso_sym_lookup(const unsigned char *file, unsigned long long fsize,
        unsigned long lo...`
- `ldso_rela_count` (function) `kernel/ldso_parse.c:296` `int ldso_rela_count(const LdsoDynInfo *info, unsigned *nrela)`
- `ldso_read_rela` (function) `kernel/ldso_parse.c:309` `int ldso_read_rela(const unsigned char *file, unsigned long long fsize,
        unsigned long lon...`
- `ldso_basename` (function) `kernel/ldso_parse.c:331` `void ldso_basename(char *out, const char *src)`

## kernel/loader.c
Depends on: `headers/ldso.h`, `headers/minifs.h`, `headers/pcache.h`, `headers/sched.h`, `headers/vga_fb.h`
- `elf_name_copy` (function) `kernel/loader.c:107` `static void elf_name_copy(char *out, unsigned out_cap, const char *tab,
                         ...`
- `elf_load_fail` (function) `kernel/loader.c:121` `static void elf_load_fail(void *base, void **sec_addrs, const char *why)`
- `elf_load` (function) `kernel/loader.c:129` `void *elf_load(void *data, unsigned size, void **base_out)`
- `inodes` (function) `kernel/loader.c:374` `* Pseudo inodes (LDSO_INO_BASE + slot) keep registry pages apart from * MiniFS inodes in the shared cache. No unload...`
- `ldso_pseudo_stat` (function) `kernel/loader.c:395` `int ldso_pseudo_stat(int ino, unsigned long *size_out)`
- `ldso_pseudo_read` (function) `kernel/loader.c:409` `int ldso_pseudo_read(int ino, void *dst, unsigned long off, unsigned len)`
- `ldso_read_file` (function) `kernel/loader.c:434` `static int ldso_read_file(const char *name, unsigned char **out,
        unsigned *size_out)` -- Read a whole library file by DT_NEEDED name: exact path first, then the basename, ramdisk before MiniFS (the shell's...
- `ldso_ensure_slot` (function) `kernel/loader.c:476` `static int ldso_ensure_slot(const char *needed, int *slot_out)` -- Resolve a DT_NEEDED name to a registry slot, loading and reserving on first use.
- `consistent` (function) `kernel/loader.c:572` `* consistent (the next exec forgets them, a dying window frees them),
 * and only reports. */
sta...`
- `images` (function) `kernel/loader.c:783` `* Static images (no dynamic section, or none needed) return 0 at * once, so the legacy paths never observe a...`
- `ldso_bind_into` (function) `kernel/loader.c:787` `int ldso_bind_into(void *data, unsigned size, unsigned long base,
        unsigned long cr3, vma_...` -- Bind one executable image with DT_NEEDED libraries: map every library into the target window, then resolve each...
- `apply_exec_relocs` (function) `kernel/loader.c:977` `static void apply_exec_relocs(void *data, unsigned size, unsigned long base,
                    ...`
- `load_exec_elf` (function) `kernel/loader.c:1060` `void *load_exec_elf(void *data, unsigned size)`
- `process` (function) `kernel/loader.c:1084` `* atomic section: a 100 Hz tick between two segments would switch * CR3 into another process (copies landing in its...`
- `base_out` (function) `kernel/loader.c:1191` `* the link base via base_out (0 when the caller runs static images
 * only: the dynamic binder ne...`
- `time` (function) `kernel/loader.c:1262` `* time (with the failing offset);`

## kernel/lz4_kernel.c
Depends on: `headers/lz4_kernel.h`
- `LZ4_read32` (function) `kernel/lz4_kernel.c:7` `static inline unsigned int LZ4_read32(const unsigned char *p)`
- `LZ4_read16` (function) `kernel/lz4_kernel.c:14` `static inline unsigned int LZ4_read16(const unsigned char *p)`
- `LZ4_write16` (function) `kernel/lz4_kernel.c:21` `static inline void LZ4_write16(unsigned char *dst, unsigned short v)`
- `LZ4_hash` (function) `kernel/lz4_kernel.c:26` `static unsigned int LZ4_hash(const unsigned char *p)`
- `LZ4_compressBound` (function) `kernel/lz4_kernel.c:33` `int LZ4_compressBound(int inputSize)`
- `LZ4_compress_default` (function) `kernel/lz4_kernel.c:40` `int LZ4_compress_default(const char *src, char *dst, int srcSize, int dstCapacity)`
- `slots` (function) `kernel/lz4_kernel.c:43` `* runs from file writes on 16 KB proc slots (stack discipline, * CLAUDE.md). OOM returns 0 and the caller stores...`
- `LZ4_decompress_safe` (function) `kernel/lz4_kernel.c:176` `int LZ4_decompress_safe(const char *src, char *dst, int compressedSize, int dstCapacity)`


Next: [API_p6.md](API_p6.md)
