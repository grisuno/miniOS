# API (page 18 of 21)
Previous: [API_p17.md](API_p17.md)

## progs/quake2generic/q2generic_minios.c
Depends on: `kernel/string.c`, `progs/doomgeneric/r_local.h`, `progs/minios_abi.h`
- `MINIOS_DOOM_BACKBUF_ADDR` (function) `progs/quake2generic/q2generic_minios.c:4` `* MINIOS_DOOM_BACKBUF_ADDR (minios_abi.h);`
- `MINIOS_GFX_BUF_GAME` (function) `progs/quake2generic/q2generic_minios.c:5` `* MINIOS_SYS_GFX_PRESENT with MINIOS_GFX_BUF_GAME (211 stays as a kernel
 * compat alias) and the...`
- `sys_kbd` (function) `progs/quake2generic/q2generic_minios.c:30` `static long sys_kbd(void)`
- `sys_palette` (function) `progs/quake2generic/q2generic_minios.c:36` `static long sys_palette(const unsigned char *pal)`
- `sys_kbd_raw` (function) `progs/quake2generic/q2generic_minios.c:42` `static long sys_kbd_raw(int on)`
- `sys_vga_mode` (function) `progs/quake2generic/q2generic_minios.c:48` `static long sys_vga_mode(int on)`
- `sys_doom_frame` (function) `progs/quake2generic/q2generic_minios.c:54` `static long sys_doom_frame(void)`
- `sys_mouse` (function) `progs/quake2generic/q2generic_minios.c:60` `static long sys_mouse(int *buf)`
- `sys_set_title` (function) `progs/quake2generic/q2generic_minios.c:66` `static long sys_set_title(const char *t)`
- `sys_gfx_zoom` (function) `progs/quake2generic/q2generic_minios.c:72` `static long sys_gfx_zoom(long mode)`
- `q2g_parse_windowed` (function) `progs/quake2generic/q2generic_minios.c:86` `static void q2g_parse_windowed(int argc, char **argv)`
- `Sys_Quit` (function) `progs/quake2generic/q2generic_minios.c:99` `extern void Sys_Quit(void);` -- Sys_Quit lives in the engine's system driver (other/q_system.c); not pulled * in through quake2.h, so declare it...
- `Cbuf_AddText` (function) `progs/quake2generic/q2generic_minios.c:102` `extern void Cbuf_AddText(char *text);` -- Sys_Quit lives in the engine's system driver (other/q_system.c); not pulled * in through quake2.h, so declare it...
- `q2snd_probe` (function) `progs/quake2generic/q2generic_minios.c:106` `extern int q2snd_probe(void);` -- Sound backend probe (snddma_minios.c): headless proof the DMA layer * reaches the pcm2 path, run with...
- `q2g_parse_autoframes` (function) `progs/quake2generic/q2generic_minios.c:121` `static void q2g_parse_autoframes(int argc, char **argv)`
- `QG_GetMouseDiff` (function) `progs/quake2generic/q2generic_minios.c:154` `void QG_GetMouseDiff(int *dx, int *dy)`
- `QG_CaptureMouse` (function) `progs/quake2generic/q2generic_minios.c:168` `void QG_CaptureMouse(void)`
- `QG_ReleaseMouse` (function) `progs/quake2generic/q2generic_minios.c:172` `void QG_ReleaseMouse(void)`
- `QG_Mkdir` (function) `progs/quake2generic/q2generic_minios.c:175` `void QG_Mkdir(const char *path)`
- `scancode_to_q2key` (function) `progs/quake2generic/q2generic_minios.c:179` `static unsigned char scancode_to_q2key(unsigned char raw)`
- `extended_to_q2key` (function) `progs/quake2generic/q2generic_minios.c:262` `static unsigned char extended_to_q2key(unsigned char sc)`
- `kbd_poll` (function) `progs/quake2generic/q2generic_minios.c:280` `static void kbd_poll(void)`
- `SWimp_SetPalette` (function) `progs/quake2generic/q2generic_minios.c:310` `void SWimp_SetPalette(const unsigned char *palette)`
- `SWimp_SetMode` (function) `progs/quake2generic/q2generic_minios.c:320` `rserr_t SWimp_SetMode(int *pwidth, int *pheight, int mode, qboolean fullscreen)`
- `SWimp_Init` (function) `progs/quake2generic/q2generic_minios.c:337` `int SWimp_Init(void *hInstance, void *wndProc)`
- `SWimp_Shutdown` (function) `progs/quake2generic/q2generic_minios.c:346` `void SWimp_Shutdown(void)`
- `SWimp_BeginFrame` (function) `progs/quake2generic/q2generic_minios.c:349` `void SWimp_BeginFrame(float camera_separation)`
- `SWimp_EndFrame` (function) `progs/quake2generic/q2generic_minios.c:352` `void SWimp_EndFrame(void)`
- `SWimp_AppActivate` (function) `progs/quake2generic/q2generic_minios.c:381` `void SWimp_AppActivate(qboolean active)`
- `QG_Milliseconds` (function) `progs/quake2generic/q2generic_minios.c:385` `int QG_Milliseconds(void)`
- `main` (function) `progs/quake2generic/q2generic_minios.c:389` `int main(int argc, char **argv)`

## progs/quake2generic/snddma_minios.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`
- `sys_pcm2_open` (function) `progs/quake2generic/snddma_minios.c:67` `static long sys_pcm2_open(long flags)`
- `sys_pcm2_write` (function) `progs/quake2generic/snddma_minios.c:75` `static long sys_pcm2_write(const void *buf, long len)`
- `sys_pcm2_close` (function) `progs/quake2generic/snddma_minios.c:83` `static void sys_pcm2_close(void)`
- `sys_time_ms` (function) `progs/quake2generic/snddma_minios.c:89` `static long sys_time_ms(void)`
- `q2_dma_push` (function) `progs/quake2generic/snddma_minios.c:104` `static int q2_dma_push(int end)` -- Push the freshly painted range [q2_dma_written, end) in ring order with NONBLOCK writes that take what the kernel...
- `SNDDMA_Init` (function) `progs/quake2generic/snddma_minios.c:138` `qboolean SNDDMA_Init(void)`
- `SNDDMA_GetDMAPos` (function) `progs/quake2generic/snddma_minios.c:182` `int SNDDMA_GetDMAPos(void)`
- `SNDDMA_Shutdown` (function) `progs/quake2generic/snddma_minios.c:190` `void SNDDMA_Shutdown(void)`
- `SNDDMA_BeginPainting` (function) `progs/quake2generic/snddma_minios.c:202` `void SNDDMA_BeginPainting(void)`
- `SNDDMA_Submit` (function) `progs/quake2generic/snddma_minios.c:205` `void SNDDMA_Submit(void)`
- `q2snd_probe` (function) `progs/quake2generic/snddma_minios.c:222` `int q2snd_probe(void)` -- Headless plumbing probe (BDD hook): open pcm2, stream one pattern, close, report.

## progs/src/aes.c
- `GF` (function) `progs/src/aes.c:8` `* generated procedurally from the GF(2^8) multiplicative inverse plus the * FIPS-197 affine transform, so the file...`
- `putchar` (function) `progs/src/aes.c:25` `int putchar();`
- `strcmp` (function) `progs/src/aes.c:26` `int strcmp();`
- `strlen` (function) `progs/src/aes.c:27` `int strlen();`
- `fopen` (function) `progs/src/aes.c:28` `void *fopen();`
- `fclose` (function) `progs/src/aes.c:29` `int fclose();`
- `fread` (function) `progs/src/aes.c:30` `int fread();`
- `fwrite` (function) `progs/src/aes.c:31` `int fwrite();`
- `fseek` (function) `progs/src/aes.c:32` `int fseek();`
- `ftell` (function) `progs/src/aes.c:33` `int ftell();`
- `rewind` (function) `progs/src/aes.c:34` `void rewind();`
- `malloc` (function) `progs/src/aes.c:35` `void *malloc();`
- `free` (function) `progs/src/aes.c:36` `void free();`
- `aes_read_all` (function) `progs/src/aes.c:69` `static char *aes_read_all(const char *name, int *len)`
- `aes_write_all` (function) `progs/src/aes.c:86` `static int aes_write_all(const char *name, char *data, int len)`
- `aes_has` (function) `progs/src/aes.c:96` `static int aes_has(const char *s, const char *needle)`
- `hex_val` (function) `progs/src/aes.c:110` `static int hex_val(int c)`
- `aes_parse_hex` (function) `progs/src/aes.c:117` `static int aes_parse_hex(const char *s, int want, int *out)`
- `aes_gf_mul` (function) `progs/src/aes.c:130` `static int aes_gf_mul(int a, int b)` -- static int aes_parse_hex(const char *s, int want, int *out) { int i, hi, lo; if ((int)strlen(s) != want) return 0...
- `aes_xtime` (function) `progs/src/aes.c:142` `static int aes_xtime(int x)`
- `aes_rotl8` (function) `progs/src/aes.c:148` `static int aes_rotl8(int x, int n)`
- `aes_init_tables` (function) `progs/src/aes.c:155` `static void aes_init_tables(void)` -- Build the S-box from first principles: multiplicative inverse in GF(2^8) composed with the FIPS-197 affine transform.
- `aes_key_expand` (function) `progs/src/aes.c:174` `static void aes_key_expand(const int *key)` -- Expand the 32-byte key into AES_RK_LEN round-key bytes (FIPS-197 for Nk=8, Nr=14: RotWord plus SubWord every Nk...
- `aes_add_round_key` (function) `progs/src/aes.c:209` `static void aes_add_round_key(int round)`
- `aes_sub_bytes` (function) `progs/src/aes.c:215` `static void aes_sub_bytes(void)`
- `aes_shift_rows` (function) `progs/src/aes.c:220` `static void aes_shift_rows(void)`
- `aes_mix_columns` (function) `progs/src/aes.c:228` `static void aes_mix_columns(void)`
- `aes_cipher` (function) `progs/src/aes.c:248` `static void aes_cipher(void)`
- `aes_iv_increment` (function) `progs/src/aes.c:263` `static void aes_iv_increment(void)` -- int r; aes_add_round_key(0); for (r = 1; r < AES_ROUNDS; r++) { aes_sub_bytes(); aes_shift_rows()...
- `aes_ctr_crypt` (function) `progs/src/aes.c:273` `static void aes_ctr_crypt(char *data, int len)` -- aes_add_round_key(AES_ROUNDS); } /* Big-endian increment of the whole counter block (SP 800-38A CTR). static void...
- `aes_hdr_put` (function) `progs/src/aes.c:288` `static void aes_hdr_put(char *h, int size)`
- `aes_hdr_get` (function) `progs/src/aes.c:299` `static int aes_hdr_get(char *h)`
- `aes_tool_name` (function) `progs/src/aes.c:307` `static const char *aes_tool_name(int decode)`
- `aes_run` (function) `progs/src/aes.c:312` `static int aes_run(int decode, const char *keyhex, const char *noncehex,
                   const...`
- `main` (function) `progs/src/aes.c:384` `int main(int argc, char **argv)`

## progs/src/apsse.c
Depends on: `kernel/string.c`
- `apsse_grind` (function) `progs/src/apsse.c:49` `static uint64_t apsse_grind(int id)` -- SSE2 integer lanes, a double accumulator and an SSE2 memchr per round; the folded value depends on every lane, so a...
- `apsse_worker` (function) `progs/src/apsse.c:75` `static void *apsse_worker(void *arg)`
- `main` (function) `progs/src/apsse.c:81` `int main(void)`

## progs/src/aslr.c
- `as_sc` (function) `progs/src/aslr.c:10` `static long as_sc(long n, long a1, long a2, long a3)` -- aslr -- userspace ASLR probe (self-exec chain).  gen0 (no args) prints its stack pointer, brk and first-mmap...
- `as_mmap` (function) `progs/src/aslr.c:18` `static long as_mmap(void)`
- `as_write` (function) `progs/src/aslr.c:31` `static void as_write(const char *s, unsigned long len)`
- `as_exit` (function) `progs/src/aslr.c:35` `static void as_exit(long code)`
- `as_execve` (function) `progs/src/aslr.c:40` `static void as_execve(const char *path, const char **argv)`
- `as_putu` (function) `progs/src/aslr.c:47` `static void as_putu(unsigned long v)`
- `as_atou` (function) `progs/src/aslr.c:59` `static unsigned long as_atou(const char *s)`
- `as_rsp` (function) `progs/src/aslr.c:68` `static unsigned long as_rsp(void)`
- `as_fail` (function) `progs/src/aslr.c:74` `static void as_fail(int step)`
- `lmain` (function) `progs/src/aslr.c:82` `int lmain(long argc, char **argv)`

## progs/src/audio.c
Depends on: `progs/minios_abi.h`
- `syscall1` (function) `progs/src/audio.c:3` `static long syscall1(long n, long a1)`
- `syscall2` (function) `progs/src/audio.c:9` `static long syscall2(long n, long a1, long a2)`
- `syscall3` (function) `progs/src/audio.c:15` `static long syscall3(long n, long a1, long a2, long a3)`
- `syscall0` (function) `progs/src/audio.c:21` `static long syscall0(long n)`
- `audio_init` (function) `progs/src/audio.c:27` `int audio_init(void)`
- `audio_tone` (function) `progs/src/audio.c:31` `void audio_tone(unsigned freq)`
- `audio_pcm_open` (function) `progs/src/audio.c:35` `int audio_pcm_open(unsigned rate, unsigned channels, unsigned format)`
- `audio_pcm_submit` (function) `progs/src/audio.c:40` `int audio_pcm_submit(const void *buf, unsigned len)`
- `audio_pcm_pump` (function) `progs/src/audio.c:44` `void audio_pcm_pump(void)`
- `audio_pcm_close` (function) `progs/src/audio.c:48` `void audio_pcm_close(void)`
- `audio_set_volume` (function) `progs/src/audio.c:52` `void audio_set_volume(unsigned volume)`
- `audio_get_volume` (function) `progs/src/audio.c:56` `unsigned audio_get_volume(void)`
- `audio_sb16_present` (function) `progs/src/audio.c:60` `int audio_sb16_present(void)`
- `audio_stream_open` (function) `progs/src/audio.c:64` `int audio_stream_open(void)`
- `audio_stream_close` (function) `progs/src/audio.c:68` `void audio_stream_close(int id)`
- `audio_stream_submit` (function) `progs/src/audio.c:72` `int audio_stream_submit(int id, const void *buf, unsigned len)`
- `audio_stream_volume` (function) `progs/src/audio.c:76` `void audio_stream_volume(int id, unsigned char vol)`

## progs/src/burn.c
- `bn_sc` (function) `progs/src/burn.c:6` `static long bn_sc(long n, long a1, long a2, long a3)` -- burn -- SMP mixed-workload probe: brk plus mmap plus CPU burn with a deterministic checksum.
- `bn_mmap` (function) `progs/src/burn.c:14` `static long bn_mmap(unsigned long len)`
- `bn_write` (function) `progs/src/burn.c:27` `static void bn_write(const char *s, unsigned long len)`
- `bn_exit` (function) `progs/src/burn.c:31` `static void bn_exit(long code)`
- `bn_putu` (function) `progs/src/burn.c:36` `static void bn_putu(unsigned long v)`
- `bn_fail` (function) `progs/src/burn.c:48` `static void bn_fail(void)`
- `lmain` (function) `progs/src/burn.c:53` `int lmain(void)`

## progs/src/cp.c
- `printf` (function) `progs/src/cp.c:1` `int printf();`
- `fopen` (function) `progs/src/cp.c:2` `void *fopen();`
- `fclose` (function) `progs/src/cp.c:3` `int fclose();`
- `fread` (function) `progs/src/cp.c:4` `int fread();`
- `fwrite` (function) `progs/src/cp.c:5` `int fwrite();`
- `main` (function) `progs/src/cp.c:10` `int main(int argc, char **argv)`

## progs/src/cpl.c
- `read_cpl` (function) `progs/src/cpl.c:6` `static long read_cpl(void)` -- Ring-3 privilege probe.
- `exit_now` (function) `progs/src/cpl.c:12` `static void exit_now(long code)`

## progs/src/execho.c
- `program` (function) `progs/src/execho.c:5` `* * Proves the UNIX process composition the kernel lacked: a child * produced by fork replaces its image with execve...`
- `path` (function) `progs/src/execho.c:7` `* execs a ghost path (must fail -2, exits 42). The parent checks
 * both wait4 results with Linux...`
- `ex_write` (function) `progs/src/execho.c:20` `static void ex_write(const char *s, unsigned long len)`
- `ex_exit` (function) `progs/src/execho.c:24` `static void ex_exit(long code)`
- `ex_fail` (function) `progs/src/execho.c:29` `static void ex_fail(int step)`
- `lmain` (function) `progs/src/execho.c:37` `int lmain(void)`

## progs/src/execthr.c
- `et_sc` (function) `progs/src/execthr.c:11` `static long et_sc(long n, long a1, long a2, long a3)` -- execthr -- execve kills sibling threads (Linux semantics).
- `et_exit` (function) `progs/src/execthr.c:19` `static void et_exit(long code)`
- `et_thread` (function) `progs/src/execthr.c:27` `static void et_thread(void)`
- `lmain` (function) `progs/src/execthr.c:33` `int lmain(void)`

## progs/src/fib.c
- `fib` (function) `progs/src/fib.c:1` `int fib(int n)`
- `main` (function) `progs/src/fib.c:6` `int main(void)`

## progs/src/forktest.c
- `fx_syscall6` (function) `progs/src/forktest.c:17` `static long fx_syscall6(long n, long a1, long a2, long a3, long a4, long a5, long a6)`
- `fx_strlen` (function) `progs/src/forktest.c:41` `static unsigned long fx_strlen(const char *s)`
- `fx_write` (function) `progs/src/forktest.c:47` `static void fx_write(const char *s)`
- `fx_exit` (function) `progs/src/forktest.c:51` `static void fx_exit(long code)`
- `this` (function) `progs/src/forktest.c:115` `* this (and the child's closes must survive below). */ fx_syscall6(SYS_close, pfd[1], 0, 0, 0, 0, 0);`

## progs/src/fptest.c
Depends on: `progs/minios_abi.h`, `progs/src/mthreads.h`
- `gettid` (function) `progs/src/fptest.c:21` `* * The same run smokes gettid (Phase 0.4: the two workers must observe * distinct tids, never the constant 1) and...`
- `read_mxcsr` (function) `progs/src/fptest.c:42` `static unsigned int read_mxcsr(void)`
- `raw_gettid` (function) `progs/src/fptest.c:48` `static long raw_gettid(void)`
- `raw_getrandom` (function) `progs/src/fptest.c:52` `static long raw_getrandom(void *buf, unsigned long n)`
- `stack_align_canary` (function) `progs/src/fptest.c:78` `static void stack_align_canary(void)` -- Stack-alignment canary: an aligned SSE store to a stack slot faults with #GP unless the thread entry stack satisfies...
- `worker` (function) `progs/src/fptest.c:84` `static void *worker(void *p)`
- `main` (function) `progs/src/fptest.c:148` `int main(void)`

## progs/src/freedom.c
Depends on: `kernel/string.c`
- `curlfree` (function) `progs/src/freedom.c:4` `* spirit of curlfree (http.c + htmlfilter.c): a bounded header phase, * Content-Length or EOF body reading...`
- `net_dns_resolve` (function) `progs/src/freedom.c:41` `int net_dns_resolve(const char *host);` -- Ring-3 TLS build (phase 2 of docs/TLS_MIGRATION.md): host libc for sockets/stdio/strings (identical ABI numbers...
- `tls_handshake` (function) `progs/src/freedom.c:42` `int tls_handshake(int fd, char *host);`
- `tls_send` (function) `progs/src/freedom.c:43` `int tls_send(int fd, char *buf, int len);`
- `tls_recv` (function) `progs/src/freedom.c:44` `int tls_recv(int fd, char *buf, int len);`
- `socket` (function) `progs/src/freedom.c:52` `int socket(int domain, int type, int proto);` -- else
- `connect` (function) `progs/src/freedom.c:53` `int connect(int fd, void *addr, int addrlen);`
- `sendto` (function) `progs/src/freedom.c:54` `int sendto(int fd, char *buf, int len, int flags, void *to, int tolen);`
- `recvfrom` (function) `progs/src/freedom.c:55` `int recvfrom(int fd, char *buf, int len, int flags, void *from, int *fromlen);`
- `close` (function) `progs/src/freedom.c:56` `int close(int fd);`
- `tls_close` (function) `progs/src/freedom.c:58` `static int tls_close(int fd)` -- Session-aware close (frees the TLS session for fd, no-op when none): every fetch path must use this, never raw...
- `printf` (function) `progs/src/freedom.c:63` `int printf(char *fmt, ...);`
- `puts` (function) `progs/src/freedom.c:64` `int puts(char *s);`
- `strlen` (function) `progs/src/freedom.c:65` `int strlen(char *s);`
- `strchr` (function) `progs/src/freedom.c:66` `char *strchr(char *s, int c);`
- `strcmp` (function) `progs/src/freedom.c:67` `int strcmp(char *a, char *b);`
- `strncmp` (function) `progs/src/freedom.c:68` `int strncmp(char *a, char *b, int n);`
- `memcpy` (function) `progs/src/freedom.c:69` `int memcpy(char *dst, char *src, int n);`
- `memset` (function) `progs/src/freedom.c:70` `int memset(char *dst, int c, int n);`
- `putchar` (function) `progs/src/freedom.c:71` `int putchar(int c);`
- `atoi` (function) `progs/src/freedom.c:151` `static int atoi(char *s)` -- static char f_dom[FREEDOM_DOM_BUF]; static int  f_domlen; static char f_css[FREEDOM_CSS_BUF]; static int  f_csslen...
- `append` (function) `progs/src/freedom.c:166` `static int append(char *dst, int pos, char *src, int cap)` -- Append src to dst at pos; returns the new length or -1 when it does not fit.
- `ci_lower` (function) `progs/src/freedom.c:176` `static int ci_lower(int c)`
- `ci_starts` (function) `progs/src/freedom.c:182` `static int ci_starts(char *s, char *pre)` -- if (pos < 0) return -1; n = strlen(src); if (pos + n >= cap) return -1; memcpy(dst + pos, src, n); dst[pos + n] = 0...
- `ci_eq` (function) `progs/src/freedom.c:193` `static int ci_eq(char *a, char *b)` -- } /* Case-insensitive starts-with. static int ci_starts(char *s, char *pre) { while (*pre) { if (!*s) return 0; if...
- `ci_index` (function) `progs/src/freedom.c:203` `static int ci_index(char *s, char *needle)` -- return 1; } /* Case-insensitive equality. static int ci_eq(char *a, char *b) { while (*a && *b) { if (ci_lower(*a)...
- `looks_like_url` (function) `progs/src/freedom.c:212` `static int looks_like_url(char *s)` -- } return *a == 0 && *b == 0; } /* Case-insensitive index of needle in haystack, or -1. static int ci_index(char *s...
- `has_scheme` (function) `progs/src/freedom.c:226` `static int has_scheme(char *s)` -- Does s begin with "<scheme>:" per RFC 3986 (ALPHA *(ALPHA/DIGIT/+/-/.) ":")?
- `make_search` (function) `progs/src/freedom.c:242` `static void make_search(char *out, char *query, int cap)` -- char c; c = s[0]; if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))) return 0; for (i = 1; s[i]; i++) { c =...
- `split_url` (function) `progs/src/freedom.c:266` `static int split_url(char *url)` -- Split an http:// or https:// URL into f_host, f_path, f_port and f_secure.
- `resolve_redirect` (function) `progs/src/freedom.c:313` `static int resolve_redirect(void)` -- Recompute f_host/f_path/f_port/f_secure from the last Location value.
- `put_ws` (function) `progs/src/freedom.c:366` `static void put_ws(void)`
- `put_utf` (function) `progs/src/freedom.c:377` `static void put_utf(int c)` -- Print one text byte through the UTF-8 gate.
- `put_text` (function) `progs/src/freedom.c:427` `static void put_text(int c)` -- Print one text byte: whitespace collapses, everything else goes * through the UTF-8 gate.
- `css_append` (function) `progs/src/freedom.c:483` `static void css_append(char *s, int n)`
- `css_line` (function) `progs/src/freedom.c:489` `static void css_line(char *s)`
- `dom_append` (function) `progs/src/freedom.c:494` `static void dom_append(char *s, int n)`
- `dom_space` (function) `progs/src/freedom.c:500` `static void dom_space(void)`
- `dom_nl` (function) `progs/src/freedom.c:504` `static void dom_nl(void)`
- `record_attr` (function) `progs/src/freedom.c:509` `static void record_attr(void)` -- int i; for (i = 0; i < n && f_domlen < FREEDOM_DOM_BUF - 1; i++) f_dom[f_domlen++] = s[i]; } static void...
- `is_void_tag` (function) `progs/src/freedom.c:534` `static int is_void_tag(void)` -- f_hreflen = f_vallen < 127 ? f_vallen : 127; memcpy(f_href, f_val, f_hreflen); f_href[f_hreflen] = 0; } else if...
- `classify_tag` (function) `progs/src/freedom.c:546` `static void classify_tag(void)` -- A tag was fully collected into f_tagn (+ attributes).
- `body_byte` (function) `progs/src/freedom.c:631` `static void body_byte(int c)` -- } dom_nl(); if (!is_void_tag()) f_depth++; } if (ci_eq(f_tagn, "br") || ci_eq(f_tagn, "p") || ci_eq(f_tagn, "div")...
- `head_line` (function) `progs/src/freedom.c:796` `static void head_line(char *line)` -- f_rel_ss = 0; return; } if (c == '&') { f_entlen = 1; f_ent[0] = 0; return; } put_text(c); } /* --- HTTP
- `parse_head` (function) `progs/src/freedom.c:821` `static void parse_head(void)` -- Parse the collected header block f_hdr[0..f_hlen-1] (the last four * bytes are the terminating CRLF CRLF).
- `recv_body` (function) `progs/src/freedom.c:843` `static int recv_body(int fd, char *buf, int len)` -- f_hdr[lend] = 0; if (i == 0) { char *sp; sp = strchr(f_hdr, ' '); if (sp) f_status = atoi(sp + 1); } else if (lend >...
- `send_all` (function) `progs/src/freedom.c:849` `static int send_all(int fd, char *buf, int len)` -- head_line(f_hdr + i); } f_hdr[lend] = '\r'; i = lend + 2; } } /* Receive body bytes: TLS for f_secure, plain TCP...
- `fetch` (function) `progs/src/freedom.c:860` `static int fetch(char *host, char *path, int port)` -- Send one HTTP request and process the response body.
- `fetch_css` (function) `progs/src/freedom.c:1031` `static void fetch_css(char *host, char *path)` -- Fetch a linked stylesheet and print its raw body (through the UTF-8 * gate).
- `print_css_dump` (function) `progs/src/freedom.c:1113` `static void print_css_dump(void)` -- } continue; } f_ws = 0; put_utf(c); got++; } } tls_close(fd); putchar('\n'); printf("freedom: %s (%d bytes)\n"...
- `print_dom_dump` (function) `progs/src/freedom.c:1122` `static void print_dom_dump(void)` -- putchar('\n'); printf("freedom: %s (%d bytes)\n", host, got); } /* Print the collected CSS dump. static void...
- `main` (function) `progs/src/freedom.c:1129` `int main(int argc, char **argv)`

## progs/src/freedom_wl.c
Depends on: `headers/vga_fb.h`, `kernel/string.c`, `progs/minios_abi.h`, `progs/nk_palette.h`, `progs/wl/wl_mini.h`
Imported by: `tests/test_freedom_wl.c`
- `net_dns_resolve` (function) `progs/src/freedom_wl.c:42` `int net_dns_resolve(const char *host);`
- `tls_handshake` (function) `progs/src/freedom_wl.c:43` `int tls_handshake(int fd, char *host);`
- `tls_send` (function) `progs/src/freedom_wl.c:44` `int tls_send(int fd, char *buf, int len);`
- `tls_recv` (function) `progs/src/freedom_wl.c:45` `int tls_recv(int fd, char *buf, int len);`
- `tls_close` (function) `progs/src/freedom_wl.c:46` `void tls_close(int fd);`
- `freedom_wl_surface_id` (function) `progs/src/freedom_wl.c:114` `static long freedom_wl_surface_id(void)` -- Logical Wayland-mini surface id for this client (ADR-0024).
- `freedom_wl_surface_attach` (function) `progs/src/freedom_wl.c:129` `static long freedom_wl_surface_attach(FreedomWlConfig *c)` -- Attach this client to the wlcomp mapping: encode an attach message for the first pool and a commit for our surface...
- `freedom_wl_default` (function) `progs/src/freedom_wl.c:158` `static FreedomWlConfig freedom_wl_default(void)` -- if (pool != WL_ID_POOL_BASE || w != (int)c->surface_w || h != (int)c->surface_h) return -1L; n =...
- `freedom_wl_clip_rect` (function) `progs/src/freedom_wl.c:196` `static long freedom_wl_clip_rect(FreedomWlConfig *c, long *x, long *y, long *w, long *h)` -- c.hops_max = WL_HOPS_MAX; c.font_w = WL_FONT_W; c.font_h = WL_FONT_H; c.port_http = 80L; c.port_https = 443L...
- `freedom_wl_frame_bytes` (function) `progs/src/freedom_wl.c:227` `static long freedom_wl_frame_bytes(FreedomWlConfig *c, long w, long h)` -- } if (*x + *w > c->surface_w) { w = c->surface_w - *x; } if (*y + *h > c->surface_h) { h = c->surface_h - *y; } if...
- `freedom_wl_keysym` (function) `progs/src/freedom_wl.c:246` `static long freedom_wl_keysym(FreedomWlConfig *c, long sc)` -- if (w <= 0L || h <= 0L) { return -1L; } if (w > c->surface_w || h > c->surface_h) { return -1L; } bytes_per_pixel =...
- `freedom_wl_sanitize_utf8` (function) `progs/src/freedom_wl.c:286` `static long freedom_wl_sanitize_utf8(char *s, long cap)` -- } if (make == 0x39L) { return 32L; } if (make == 0x0EL) { return 8L; } if (make == 0x0FL) { return 9L; } return -1L...
- `freedom_wl_title_ok` (function) `progs/src/freedom_wl.c:359` `static long freedom_wl_title_ok(FreedomWlConfig *c, char *t, long n)` -- i++; } if (o >= cap - 1L) { break; } } if (o >= cap) { return -1L; } s[o] = 0; return o; } /** Validate a window...
- `wl_copy` (function) `progs/src/freedom_wl.c:370` `static long wl_copy(char *dst, char *src, long cap)` -- } /** Validate a window title against the kernel title bound. static long freedom_wl_title_ok(FreedomWlConfig *c...
- `wl_strlen` (function) `progs/src/freedom_wl.c:388` `static long wl_strlen(char *s, long cap)` -- } i = 0L; while (src[i] != 0) { if (i + 1L >= cap) { return -1L; } dst[i] = src[i]; i++; } dst[i] = 0; return 0L; }...
- `wl_append` (function) `progs/src/freedom_wl.c:404` `static long wl_append(char *dst, long pos, char *src, long cap)` -- if (!s || cap <= 0L) { return -1L; } i = 0L; while (i < cap && s[i] != 0) { i++; } if (i >= cap) { return -1L; }...
- `wl_ci_lower` (function) `progs/src/freedom_wl.c:427` `static long wl_ci_lower(long ch)` -- } if (pos + n >= cap) { return -1L; } i = 0L; while (i < n) { dst[pos + i] = src[i]; i++; } dst[pos + n] = 0; return...
- `wl_ci_starts` (function) `progs/src/freedom_wl.c:435` `static long wl_ci_starts(char *s, char *pre)` -- } dst[pos + n] = 0; return pos + n; } /** ASCII lowercase fold. static long wl_ci_lower(long ch) { if (ch >= 'A' &&...
- `wl_ci_contains` (function) `progs/src/freedom_wl.c:453` `static long wl_ci_contains(char *s, char *needle)` -- while (*pre) { if (*s == 0) { return 0L; } if (wl_ci_lower(*s) != wl_ci_lower(*pre)) { return 0L; } s++; pre++; }...
- `wl_has_scheme` (function) `progs/src/freedom_wl.c:467` `static long wl_has_scheme(char *s)` -- static long wl_ci_contains(char *s, char *needle) { if (!s || !needle) { return 0L; } while (*s) { if...
- `wl_looks_like_url` (function) `progs/src/freedom_wl.c:493` `static long wl_looks_like_url(char *s)` -- ch = s[i]; if (ch == ':') { return 1L; } if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' &&...
- `wl_make_search` (function) `progs/src/freedom_wl.c:512` `static long wl_make_search(char *out, char *query, long cap)` -- dot = 0L; while (*s) { if (*s == ' ' || *s == '\t') { return 0L; } if (*s == '.') { dot = 1L; } s++; } return dot; }...
- `wl_split_url` (function) `progs/src/freedom_wl.c:544` `static long wl_split_url(FreedomWlConfig *c, char *url, char *host, char *path, long *port, long ...` -- } else { out[pos] = *query; pos++; out[pos] = 0; } if (pos < 0L) { return -1L; } query++; } return pos; } /** Split...
- `wl_resolve_redirect` (function) `progs/src/freedom_wl.c:609` `static long wl_resolve_redirect(FreedomWlConfig *c, char *loc, long secure, char *host, char *pat...` -- if (plen < 0L) { return 0L; } if (wl_copy(path, p + hl, c->path_max) < 0L) { return 0L; } } else { path[0] = '/'...
- `wl_scroll_clamp` (function) `progs/src/freedom_wl.c:689` `static long wl_scroll_clamp(FreedomWlConfig *c, long off, long nlines)` -- if (last + 1L + l >= c->path_max) { return 0L; } i = 0L; while (i < l) { path[last + 1L + i] = loc[i]; i++; }...
- `wl_filter_wrap` (function) `progs/src/freedom_wl.c:708` `static long wl_filter_wrap(FreedomWlConfig *c, char *body, long n, char *lines, long maxlines, lo...` -- if (nlines <= c->text_rows) { return 0L; } maxoff = nlines - c->text_rows; if (off < 0L) { return 0L; } if (off >...
- `wl_status_text` (function) `progs/src/freedom_wl.c:951` `static long wl_status_text(FreedomWlConfig *c, char *host, long nbytes, long off, long nlines, ch...` -- lines[li * linelen + co] = (char)ch; co++; lines[li * linelen + co] = 0; } if (co > 0L) { return li + 1L; } if (li...
- `freedom_wl_build_palette` (function) `progs/src/freedom_wl.c:1039` `static long freedom_wl_build_palette(unsigned char *pal, long cap)` -- Shared hybrid palette, one table for every NK-window app (progs/nk_palette.h); this wrapper keeps the historic name...
- `freedom_wl_sys_present` (function) `progs/src/freedom_wl.c:1062` `static long freedom_wl_sys_present(long buf, long origin)` -- static char w_host[WL_HOST_MAX]; static char w_path[WL_PATH_MAX]; static char w_loc[WL_URL_MAX]; static char...
- `freedom_wl_sys_title` (function) `progs/src/freedom_wl.c:1069` `static long freedom_wl_sys_title(char *t)` -- static long w_nbytes; static long w_secure; static long w_port; static long w_status; static long w_truncated; /**...
- `freedom_wl_sys_palette` (function) `progs/src/freedom_wl.c:1076` `static long freedom_wl_sys_palette(unsigned char *pal)` -- static long freedom_wl_sys_present(long buf, long origin) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedom_wl_sys_mouse` (function) `progs/src/freedom_wl.c:1083` `static long freedom_wl_sys_mouse(long *m)` -- static long freedom_wl_sys_title(char *t) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedom_wl_sys_kbd` (function) `progs/src/freedom_wl.c:1090` `static long freedom_wl_sys_kbd(void)` -- static long freedom_wl_sys_palette(unsigned char *pal) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedom_wl_sys_vga_mode` (function) `progs/src/freedom_wl.c:1097` `static long freedom_wl_sys_vga_mode(long on)` -- static long freedom_wl_sys_mouse(long *m) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedom_wl_sys_kbd_raw` (function) `progs/src/freedom_wl.c:1104` `static long freedom_wl_sys_kbd_raw(long on)` -- static long freedom_wl_sys_kbd(void) { long ret; __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_KBD)...
- `freedom_wl_sys_yield` (function) `progs/src/freedom_wl.c:1111` `static long freedom_wl_sys_yield(void)` -- static long freedom_wl_sys_vga_mode(long on) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `wl_parse_headers` (function) `progs/src/freedom_wl.c:1118` `static long wl_parse_headers(FreedomWlConfig *c, char *hdr, long *status, long *clen, long *hascl...` -- static long freedom_wl_sys_kbd_raw(long on) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `wl_fetch_raw` (function) `progs/src/freedom_wl.c:1210` `static long wl_fetch_raw(FreedomWlConfig *c, char *host, char *path, long port, long secure)` -- if (!wl_ci_starts(hdr + k, "text")) { istext = 0L; } } } line++; while (hdr[i] == '\r' || hdr[i] == '\n') { i++; } }...
- `wl_render` (function) `progs/src/freedom_wl.c:1445` `static long wl_render(FreedomWlConfig *c, long off)` -- if (got < c->body_cap) { w_body[got] = (char)ch; got++; } else { w_truncated = 1L; } } } } tls_close((int)fd)...
- `wl_browse` (function) `progs/src/freedom_wl.c:1532` `static long wl_browse(FreedomWlConfig *c)` -- long ink; if (bits & (0x80 >> px)) { ink = c->bar_fg; } else { ink = c->bar_bg; } fb[(c->text_rows * c->font_h +...
- `freedom_wl_selftest` (function) `progs/src/freedom_wl.c:1613` `static long freedom_wl_selftest(void)` -- off = off + (long)m[3] * c->scroll_step; changed = 1L; } if (changed) { off = wl_scroll_clamp(c, off, w_nlines); if...
- `freedom_wl_host_probe` (function) `progs/src/freedom_wl.c:1696` `int freedom_wl_host_probe(FreedomWlConfig *c)` -- return 1L; } if (freedom_wl_sys_kbd() > 0x7FFFFFFFL) { printf("freedom_wl: kbd out of range\n"); return 1L; }...
- `main` (function) `progs/src/freedom_wl.c:1731` `int main(int argc, char **argv)` -- } buf[0] = 'h'; buf[1] = 'i'; buf[2] = 0; if (freedom_wl_sanitize_utf8(buf, 16L) != 2L) { return 1; } if...

## progs/src/ftest.c
- `fprintf` (function) `progs/src/ftest.c:4` `extern int fprintf(void *stream, const char *fmt, ...);` -- Exercises the kernel libc surface used by loaded .o programs: fprintf to stdout/stderr, snprintf into a buffer...
- `snprintf` (function) `progs/src/ftest.c:5` `extern int snprintf(char *buf, unsigned long size, const char *fmt, ...);`
- `printf` (function) `progs/src/ftest.c:6` `extern int printf(const char *fmt, ...);`
- `exit` (function) `progs/src/ftest.c:7` `extern void exit(int code);`
- `fopen` (function) `progs/src/ftest.c:11` `extern void *fopen(const char *path, const char *mode);`
- `main` (function) `progs/src/ftest.c:13` `int main(int argc, char **argv)`

## progs/src/hello.c
- `printf` (function) `progs/src/hello.c:2` `extern int printf(const char *fmt, ...);` -- /* MiniOS test program — compiled as relocatable .o, loaded by kernel ELF loader
- `main` (function) `progs/src/hello.c:4` `int main(int argc, char **argv)`

## progs/src/http.c
- `kernel` (function) `progs/src/http.c:3` `* Hostnames are resolved by the kernel (net_dns_resolve syscall). */ int socket(int domain, int type, int proto);`
- `connect` (function) `progs/src/http.c:6` `int connect(int fd, void *addr, int addrlen);`
- `sendto` (function) `progs/src/http.c:7` `int sendto(int fd, char *buf, int len, int flags, void *to, int tolen);`
- `recvfrom` (function) `progs/src/http.c:8` `int recvfrom(int fd, char *buf, int len, int flags, void *from, int *fromlen);`
- `shutdown` (function) `progs/src/http.c:9` `int shutdown(int fd, int how);`
- `close` (function) `progs/src/http.c:10` `int close(int fd);`
- `net_dns_resolve` (function) `progs/src/http.c:11` `int net_dns_resolve(const char *host);`
- `puts` (function) `progs/src/http.c:12` `int puts(char *s);`
- `printf` (function) `progs/src/http.c:13` `int printf(char *fmt, ...);`
- `strlen` (function) `progs/src/http.c:14` `int strlen(char *s);`
- `putchar` (function) `progs/src/http.c:15` `int putchar(int c);`
- `atoi` (function) `progs/src/http.c:18` `int atoi(char *s)` -- int socket(int domain, int type, int proto); int connect(int fd, void *addr, int addrlen); int sendto(int fd, char...
- `main` (function) `progs/src/http.c:29` `int main(int argc, char **argv)`

## progs/src/json.c
- `js_str` (function) `progs/src/json.c:5` `* members keep their key in js_str (the member value node) and their value * in the node itself, and object members...`
- `free` (function) `progs/src/json.c:14` `void free();`
- `printf` (function) `progs/src/json.c:15` `int printf();`
- `putchar` (function) `progs/src/json.c:16` `int putchar();`
- `puts` (function) `progs/src/json.c:17` `int puts();`
- `strlen` (function) `progs/src/json.c:18` `int strlen();`
- `strcmp` (function) `progs/src/json.c:19` `int strcmp();`
- `fopen` (function) `progs/src/json.c:20` `void *fopen();`
- `fclose` (function) `progs/src/json.c:21` `int fclose();`
- `fread` (function) `progs/src/json.c:22` `int fread();`
- `fseek` (function) `progs/src/json.c:23` `int fseek();`
- `ftell` (function) `progs/src/json.c:24` `int ftell();`
- `rewind` (function) `progs/src/json.c:25` `void rewind();`
- `js_read_all` (function) `progs/src/json.c:58` `static char *js_read_all(const char *name, int *len)`
- `js_new` (function) `progs/src/json.c:76` `static int js_new(void)`
- `js_skip_ws` (function) `progs/src/json.c:81` `static void js_skip_ws(void)`
- `js_peek` (function) `progs/src/json.c:89` `static int js_peek(void)`
- `js_parse_string` (function) `progs/src/json.c:97` `static int js_parse_string(void)`
- `js_parse_number` (function) `progs/src/json.c:133` `static int js_parse_number(void)`
- `js_key_match` (function) `progs/src/json.c:143` `static int js_key_match(int child, const char *key)`
- `js_parse_object` (function) `progs/src/json.c:147` `static int js_parse_object(void)`
- `js_parse_array` (function) `progs/src/json.c:182` `static int js_parse_array(void)`
- `js_parse_value` (function) `progs/src/json.c:211` `static int js_parse_value(void)`
- `js_indent` (function) `progs/src/json.c:281` `static void js_indent(int n)`
- `js_print_str` (function) `progs/src/json.c:286` `static void js_print_str(const char *s)`
- `js_print_value` (function) `progs/src/json.c:303` `static void js_print_value(int node, int depth)`
- `js_find_member` (function) `progs/src/json.c:347` `static int js_find_member(int obj, const char *key)`
- `js_array_at` (function) `progs/src/json.c:357` `static int js_array_at(int arr, int idx)`
- `js_query` (function) `progs/src/json.c:369` `static int js_query(int root, const char *path)`
- `main` (function) `progs/src/json.c:401` `int main(int argc, char **argv)`

## progs/src/kmem.c
- `syscall3` (function) `progs/src/kmem.c:7` `static long syscall3(long n, long a1, long a2, long a3)` -- Kernel-pointer rejection probe.
- `exit_now` (function) `progs/src/kmem.c:14` `static void exit_now(long code)`

## progs/src/ldhello.c
- `main` (function) `progs/src/ldhello.c:1` `int main(void)`

## progs/src/lxabi.c
Depends on: `headers/sched.h`, `kernel/string.c`, `kernel/time.c`
- `report` (function) `progs/src/lxabi.c:65` `static void report(const char *name, int ok, const char *detail)`
- `now_ms` (function) `progs/src/lxabi.c:75` `static long now_ms(void)`
- `busy_wait_ms` (function) `progs/src/lxabi.c:81` `static void busy_wait_ms(long ms)`
- `fork_probe` (function) `progs/src/lxabi.c:95` `static void fork_probe(uint64_t *out)` -- Raw clone(SIGCHLD) with known values in every callee-saved register and in * the argument registers; both sides...
- `regs_match` (function) `progs/src/lxabi.c:132` `static int regs_match(const uint64_t *r)`
- `check_fork_registers` (function) `progs/src/lxabi.c:138` `static void check_fork_registers(void)`
- `check_fork_cow_kernel_write` (function) `progs/src/lxabi.c:160` `static void check_fork_cow_kernel_write(void)`
- `worker` (function) `progs/src/lxabi.c:201` `static void *worker(void *arg)`
- `check_threads` (function) `progs/src/lxabi.c:215` `static void check_threads(void)`
- `detached_worker` (function) `progs/src/lxabi.c:245` `static void *detached_worker(void *arg)`
- `check_detached_reaped` (function) `progs/src/lxabi.c:251` `static void check_detached_reaped(void)`
- `signaller` (function) `progs/src/lxabi.c:275` `static void *signaller(void *arg)`
- `check_condvar` (function) `progs/src/lxabi.c:285` `static void check_condvar(void)`
- `check_pipe2_flags` (function) `progs/src/lxabi.c:307` `static void check_pipe2_flags(void)`
- `check_pipe_blocking` (function) `progs/src/lxabi.c:334` `static void check_pipe_blocking(void)`
- `check_pipe_epipe` (function) `progs/src/lxabi.c:356` `static void check_pipe_epipe(void)`
- `check_writev_pipe` (function) `progs/src/lxabi.c:382` `static void check_writev_pipe(void)`
- `check_poll` (function) `progs/src/lxabi.c:394` `static void check_poll(void)`
- `check_eventfd` (function) `progs/src/lxabi.c:418` `static void check_eventfd(void)`
- `check_close_range` (function) `progs/src/lxabi.c:443` `static void check_close_range(void)`
- `check_time` (function) `progs/src/lxabi.c:455` `static void check_time(void)`
- `check_mkdir` (function) `progs/src/lxabi.c:464` `static void check_mkdir(void)`
- `check_limits` (function) `progs/src/lxabi.c:478` `static void check_limits(void)` -- The answers glibc sizes memory from: a finite stack limit (thread stacks default to it) and a CPU count that matches...
- `mono_us` (function) `progs/src/lxabi.c:491` `static long mono_us(void)`
- `check_sleep` (function) `progs/src/lxabi.c:500` `static void check_sleep(void)` -- Sleeps really wait: nanosleep for a relative interval, clock_nanosleep until an absolute monotonic deadline, and a...
- `lxabi_sleeper` (function) `progs/src/lxabi.c:527` `static void *lxabi_sleeper(void *arg)` -- rc = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &abs_t, NULL); waited = mono_us() - t0...
- `child_status` (function) `progs/src/lxabi.c:535` `static int child_status(void (*body)(void))` -- Fork a child that runs body, wait for it with a bounded spin and return * its wait status, or -1 when it never ended...
- `abort_from_worker_body` (function) `progs/src/lxabi.c:555` `static void abort_from_worker_body(void)`
- `lxabi_exit_group_worker` (function) `progs/src/lxabi.c:561` `static void *lxabi_exit_group_worker(void *arg)`
- `exit_group_from_worker_body` (function) `progs/src/lxabi.c:567` `static void exit_group_from_worker_body(void)`
- `wild_jump_body` (function) `progs/src/lxabi.c:573` `static void wild_jump_body(void)`
- `process` (function) `progs/src/lxabi.c:581` `* process (never a kernel panic), and kill(pid, 0) or a harmless signal
 * leaves the target aliv...`
- `check_uid_gid` (function) `progs/src/lxabi.c:642` `static void check_uid_gid(void)` -- Every process runs as root (uid/gid 0); glibc and CPython's startup * read these, and -ENOSYS made them answer...
- `copy_dentry_name` (function) `progs/src/lxabi.c:680` `static void copy_dentry_name(char *dst, size_t cap, const char *src)` -- getdents64 (217): a directory fd enumerates MiniFS entries with the right d_type and resumes across calls; a regular...
- `check_getdents64` (function) `progs/src/lxabi.c:687` `static void check_getdents64(void)`
- `main` (function) `progs/src/lxabi.c:754` `int main(void)`

## progs/src/lxhello.c
- `lx_syscall3` (function) `progs/src/lxhello.c:11` `static long lx_syscall3(long n, long a1, long a2, long a3)`
- `lx_strlen` (function) `progs/src/lxhello.c:23` `static unsigned long lx_strlen(const char *s)`
- `lx_write` (function) `progs/src/lxhello.c:29` `static void lx_write(const char *s)`
- `lx_write_int` (function) `progs/src/lxhello.c:33` `static void lx_write_int(long v)`
- `lmain` (function) `progs/src/lxhello.c:46` `int lmain(long argc, char **argv)` -- static void lx_write_int(long v) { char buf[24]; int i = (int)sizeof(buf); int neg = 0; buf[--i] = 0; if (v < 0) {...

## progs/src/lxnet.c
Depends on: `kernel/string.c`
- `report` (function) `progs/src/lxnet.c:49` `static void report(const char *name, int ok, const char *detail)`
- `wait_for` (function) `progs/src/lxnet.c:55` `static int wait_for(int fd, short events)`
- `read_all` (function) `progs/src/lxnet.c:62` `static int read_all(int fd, char *buf, size_t len)` -- static void report(const char *name, int ok, const char *detail) { if (ok) printf("lxnet: %s ok\n", name); else {...
- `check_udp` (function) `progs/src/lxnet.c:73` `static void check_udp(const struct sockaddr_in *peer)`
- `check_refused` (function) `progs/src/lxnet.c:150` `static void check_refused(const struct sockaddr_in *peer)` -- A non-blocking connect to a port nobody listens on fails through poll * (POLLERR) with SO_ERROR = ECONNREFUSED...
- `check_tcp` (function) `progs/src/lxnet.c:174` `static void check_tcp(const struct sockaddr_in *peer)`
- `check_misc` (function) `progs/src/lxnet.c:217` `static void check_misc(void)`
- `dial` (function) `progs/src/lxnet.c:236` `static int dial(const char *host, const char *port)` -- if (fd >= 0) close(fd); struct addrinfo hints, *res = NULL; memset(&hints, 0, sizeof hints); hints.ai_family =...
- `main` (function) `progs/src/lxnet.c:280` `int main(int argc, char **argv)`

## progs/src/lxproc.c
Depends on: `progs/minios_abi.h`
- `report_exe` (function) `progs/src/lxproc.c:50` `static int report_exe(void)` -- uint32_t namesz; uint32_t descsz; uint32_t type; char     name[sizeof MINIOS_NOTE_NAME]; uint32_t desc; }...
- `report_fork` (function) `progs/src/lxproc.c:64` `static int report_fork(void)` -- Fork a child that exits with LXPROC_CHILD_CODE and reap it; 0 when the * outcome is one of the two the contract allows.
- `main` (function) `progs/src/lxproc.c:91` `int main(void)`

## progs/src/lxsecc.c
Depends on: `kernel/string.c`
- `report` (function) `progs/src/lxsecc.c:44` `static void report(const char *name, int ok, const char *detail)`
- `exit_code_of` (function) `progs/src/lxsecc.c:53` `static int exit_code_of(int st)` -- Exit code of a reaped child under both encodings: Linux's status word (code << 8, signal in the low bits) and...
- `run_child` (function) `progs/src/lxsecc.c:58` `static int run_child(void (*body)(void))`
- `install_filter` (function) `progs/src/lxsecc.c:72` `static int install_filter(unsigned getpid_action)` -- Filter: arch guard, getpid -> ERRNO(err_getpid), write/exit/exit_group/ * rt_sigreturn/mprotect(no PROT_EXEC)/fork...
- `child_errno_action` (function) `progs/src/lxsecc.c:100` `static void child_errno_action(void)`
- `child_kill_action` (function) `progs/src/lxsecc.c:107` `static void child_kill_action(void)`
- `child_wx` (function) `progs/src/lxsecc.c:116` `static void child_wx(void)` -- The page is the child's own anonymous mapping, made before the filter (which forbids mmap): a copy-on-write page...
- `grandchild_inherits` (function) `progs/src/lxsecc.c:127` `static void grandchild_inherits(void)`
- `child_inherit` (function) `progs/src/lxsecc.c:133` `static void child_inherit(void)`
- `child_stacked` (function) `progs/src/lxsecc.c:142` `static void child_stacked(void)`
- `child_strict` (function) `progs/src/lxsecc.c:150` `static void child_strict(void)`
- `child_no_nnp` (function) `progs/src/lxsecc.c:157` `static void child_no_nnp(void)`
- `child_bad_program` (function) `progs/src/lxsecc.c:165` `static void child_bad_program(void)`
- `check_prctl_flags` (function) `progs/src/lxsecc.c:177` `static void check_prctl_flags(void)`
- `check_proc_self_exe` (function) `progs/src/lxsecc.c:197` `static void check_proc_self_exe(const char *argv0)`
- `main` (function) `progs/src/lxsecc.c:215` `int main(int argc, char **argv)`

## progs/src/lxsel.c
Depends on: `kernel/time.c`
- `report` (function) `progs/src/lxsel.c:36` `static void report(const char *name, int ok)`
- `raw_select` (function) `progs/src/lxsel.c:45` `static long raw_select(long nfds, fd_set *r, fd_set *w, fd_set *e,
                       struct ...`
- `raw_pselect6` (function) `progs/src/lxsel.c:50` `static long raw_pselect6(long nfds, fd_set *r, fd_set *w, fd_set *e,
                         str...`
- `elapsed_ms` (function) `progs/src/lxsel.c:55` `static long elapsed_ms(struct timespec *a, struct timespec *b)`
- `main` (function) `progs/src/lxsel.c:60` `int main(void)`

## progs/src/lxtls.c
Depends on: `kernel/string.c`
- `lxtls_sink` (function) `progs/src/lxtls.c:39` `static size_t lxtls_sink(char *data, size_t size, size_t nmemb, void *user)` -- Count the body without storing it: the probe proves transport, not * content.
- `lxtls_debug` (function) `progs/src/lxtls.c:46` `static int lxtls_debug(CURL *h, curl_infotype type, char *data, size_t size, void *user)` -- Count the body without storing it: the probe proves transport, not * content. static size_t lxtls_sink(char *data...
- `lxtls_step` (function) `progs/src/lxtls.c:65` `static int lxtls_step(const char *name, int ok)` -- return 0; for (i = 0; i <= size; i++) { if (i == size || data[i] == '\n') { size_t len = i - start; if (len > 0 &&...
- `lxtls_rand` (function) `progs/src/lxtls.c:73` `static int lxtls_rand(void)` -- } fflush(stdout); return 0; } /* Report one RAND step and, on failure, OpenSSL's error queue. static int...
- `main` (function) `progs/src/lxtls.c:87` `int main(int argc, char **argv)`

## progs/src/lz4.c
- `kernel` (function) `progs/src/lz4.c:6` `* * The codec lives in the kernel (lz4_kernel.c, the same one MiniFS uses), so * these tools are thin front-ends...`
- `free` (function) `progs/src/lz4.c:15` `void free();`
- `printf` (function) `progs/src/lz4.c:16` `int printf();`
- `strcmp` (function) `progs/src/lz4.c:17` `int strcmp();`
- `strlen` (function) `progs/src/lz4.c:18` `int strlen();`
- `fopen` (function) `progs/src/lz4.c:19` `void *fopen();`
- `fclose` (function) `progs/src/lz4.c:20` `int fclose();`
- `fread` (function) `progs/src/lz4.c:21` `int fread();`
- `fwrite` (function) `progs/src/lz4.c:22` `int fwrite();`
- `fseek` (function) `progs/src/lz4.c:23` `int fseek();`
- `ftell` (function) `progs/src/lz4.c:24` `int ftell();`
- `rewind` (function) `progs/src/lz4.c:25` `void rewind();`
- `lz4_compress` (function) `progs/src/lz4.c:27` `int lz4_compress(char *src, int srclen, char *dst, int dstcap);`
- `lz4_decompress` (function) `progs/src/lz4.c:28` `int lz4_decompress(char *src, int srclen, char *dst, int dstcap);`
- `lz4_has` (function) `progs/src/lz4.c:39` `static int lz4_has(const char *s, const char *needle)`
- `lz4_read_all` (function) `progs/src/lz4.c:53` `static char *lz4_read_all(const char *name, int *len)`
- `lz4_write_all` (function) `progs/src/lz4.c:70` `static int lz4_write_all(const char *name, char *data, int len)`
- `lz4_compress_file` (function) `progs/src/lz4.c:80` `static int lz4_compress_file(const char *src, const char *dst)`
- `lz4_decompress_file` (function) `progs/src/lz4.c:117` `static int lz4_decompress_file(const char *src, const char *dst)`
- `main` (function) `progs/src/lz4.c:164` `int main(int argc, char **argv)`


Next: [API_p19.md](API_p19.md)
