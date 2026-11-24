# Symbols (page 23 of 28)
Previous: [SYMBOLS_p22.md](SYMBOLS_p22.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
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
| `main` | function | `progs/src/cvmfmt.c:19` | `int main(void)` |
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
| `check_getdents64` | function | `progs/src/lxabi.c:722` | `static void check_getdents64(void)` |
| `check_limits` | function | `progs/src/lxabi.c:478` | `static void check_limits(void)` |
| `check_mkdir` | function | `progs/src/lxabi.c:464` | `static void check_mkdir(void)` |
| `check_pipe2_flags` | function | `progs/src/lxabi.c:307` | `static void check_pipe2_flags(void)` |
| `check_pipe_blocking` | function | `progs/src/lxabi.c:334` | `static void check_pipe_blocking(void)` |
| `check_pipe_epipe` | function | `progs/src/lxabi.c:356` | `static void check_pipe_epipe(void)` |
| `check_poll` | function | `progs/src/lxabi.c:394` | `static void check_poll(void)` |
| `check_rename_dir` | function | `progs/src/lxabi.c:649` | `static void check_rename_dir(void)` |
| `check_sleep` | function | `progs/src/lxabi.c:500` | `static void check_sleep(void)` |
| `check_threads` | function | `progs/src/lxabi.c:215` | `static void check_threads(void)` |
| `check_time` | function | `progs/src/lxabi.c:455` | `static void check_time(void)` |
| `check_uid_gid` | function | `progs/src/lxabi.c:642` | `static void check_uid_gid(void)` |
| `check_writev_pipe` | function | `progs/src/lxabi.c:382` | `static void check_writev_pipe(void)` |
| `child_status` | function | `progs/src/lxabi.c:535` | `static int child_status(void (*body)(void))` |
| `copy_dentry_name` | function | `progs/src/lxabi.c:715` | `static void copy_dentry_name(char *dst, size_t cap, const char *src)` |
| `detached_worker` | function | `progs/src/lxabi.c:245` | `static void *detached_worker(void *arg)` |
| `exit_group_from_worker_body` | function | `progs/src/lxabi.c:567` | `static void exit_group_from_worker_body(void)` |
| `fork_probe` | function | `progs/src/lxabi.c:95` | `static void fork_probe(uint64_t *out)` |
| `lxabi_exit_group_worker` | function | `progs/src/lxabi.c:561` | `static void *lxabi_exit_group_worker(void *arg)` |
| `lxabi_sleeper` | function | `progs/src/lxabi.c:527` | `static void *lxabi_sleeper(void *arg)` |
| `main` | function | `progs/src/lxabi.c:789` | `int main(void)` |
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
| `LXNET_BUF` | macro | `progs/src/lxnet.c:41` | `#define LXNET_BUF` |
| `LXNET_IP_UNKNOWN` | macro | `progs/src/lxnet.c:45` | `#define LXNET_IP_UNKNOWN` |
| `LXNET_LOOPBACK` | macro | `progs/src/lxnet.c:44` | `#define LXNET_LOOPBACK` |
| `LXNET_TCP_MSG` | macro | `progs/src/lxnet.c:43` | `#define LXNET_TCP_MSG` |
| `LXNET_UDP_MSG` | macro | `progs/src/lxnet.c:42` | `#define LXNET_UDP_MSG` |
| `LXNET_WAIT_MS` | macro | `progs/src/lxnet.c:40` | `#define LXNET_WAIT_MS` |
| `_GNU_SOURCE` | macro | `progs/src/lxnet.c:24` | `#define _GNU_SOURCE` |
| `check_misc` | function | `progs/src/lxnet.c:217` | `static void check_misc(void)` |
| `check_refused` | function | `progs/src/lxnet.c:150` | `static void check_refused(const struct sockaddr_in *peer)` |
| `check_tcp` | function | `progs/src/lxnet.c:174` | `static void check_tcp(const struct sockaddr_in *peer)` |
| `check_udp` | function | `progs/src/lxnet.c:73` | `static void check_udp(const struct sockaddr_in *peer)` |
| `dial` | function | `progs/src/lxnet.c:236` | `static int dial(const char *host, const char *port)` |
| `main` | function | `progs/src/lxnet.c:280` | `int main(int argc, char **argv)` |
| `read_all` | function | `progs/src/lxnet.c:62` | `static int read_all(int fd, char *buf, size_t len)` |
| `report` | function | `progs/src/lxnet.c:49` | `static void report(const char *name, int ok, const char *detail)` |
| `wait_for` | function | `progs/src/lxnet.c:55` | `static int wait_for(int fd, short events)` |
| `LXPROC_BAD` | macro | `progs/src/lxproc.c:31` | `#define LXPROC_BAD` |
| `LXPROC_CHILD_CODE` | macro | `progs/src/lxproc.c:29` | `#define LXPROC_CHILD_CODE` |
| `LXPROC_EXE_MAX` | macro | `progs/src/lxproc.c:27` | `#define LXPROC_EXE_MAX` |
| `LXPROC_OK` | macro | `progs/src/lxproc.c:30` | `#define LXPROC_OK` |
| `_GNU_SOURCE` | macro | `progs/src/lxproc.c:17` | `#define _GNU_SOURCE` |
| `lxproc_note` | struct | `progs/src/lxproc.c:35` | `` |
| `main` | function | `progs/src/lxproc.c:91` | `int main(void)` |
| `report_exe` | function | `progs/src/lxproc.c:50` | `static int report_exe(void)` |
| `report_fork` | function | `progs/src/lxproc.c:64` | `static int report_fork(void)` |
| `LXSECC_BAD_CODE` | macro | `progs/src/lxsecc.c:31` | `#define LXSECC_BAD_CODE` |
| `LXSECC_ERRNO_A` | macro | `progs/src/lxsecc.c:35` | `#define LXSECC_ERRNO_A` |
| `LXSECC_ERRNO_B` | macro | `progs/src/lxsecc.c:36` | `#define LXSECC_ERRNO_B` |
| `LXSECC_EXEC_CODE` | macro | `progs/src/lxsecc.c:29` | `#define LXSECC_EXEC_CODE` |
| `LXSECC_EXEC_FLAG` | macro | `progs/src/lxsecc.c:28` | `#define LXSECC_EXEC_FLAG` |
| `LXSECC_EXE_MAX` | macro | `progs/src/lxsecc.c:32` | `#define LXSECC_EXE_MAX` |
| `LXSECC_NAME` | macro | `progs/src/lxsecc.c:33` | `#define LXSECC_NAME` |
| `LXSECC_NAME_MAX` | macro | `progs/src/lxsecc.c:34` | `#define LXSECC_NAME_MAX` |
| `LXSECC_OK_CODE` | macro | `progs/src/lxsecc.c:30` | `#define LXSECC_OK_CODE` |
| `LXSECC_PAGE` | macro | `progs/src/lxsecc.c:37` | `#define LXSECC_PAGE` |
| `LXSECC_STATUS_BYTE` | macro | `progs/src/lxsecc.c:40` | `#define LXSECC_STATUS_BYTE` |
| `LXSECC_STATUS_MASK` | macro | `progs/src/lxsecc.c:38` | `#define LXSECC_STATUS_MASK` |
| `LXSECC_STATUS_SHIFT` | macro | `progs/src/lxsecc.c:39` | `#define LXSECC_STATUS_SHIFT` |
| `_GNU_SOURCE` | macro | `progs/src/lxsecc.c:13` | `#define _GNU_SOURCE` |
| `check_prctl_flags` | function | `progs/src/lxsecc.c:177` | `static void check_prctl_flags(void)` |
| `check_proc_self_exe` | function | `progs/src/lxsecc.c:197` | `static void check_proc_self_exe(const char *argv0)` |
| `child_bad_program` | function | `progs/src/lxsecc.c:165` | `static void child_bad_program(void)` |
| `child_errno_action` | function | `progs/src/lxsecc.c:100` | `static void child_errno_action(void)` |
| `child_inherit` | function | `progs/src/lxsecc.c:133` | `static void child_inherit(void)` |
| `child_kill_action` | function | `progs/src/lxsecc.c:107` | `static void child_kill_action(void)` |
| `child_no_nnp` | function | `progs/src/lxsecc.c:157` | `static void child_no_nnp(void)` |
| `child_stacked` | function | `progs/src/lxsecc.c:142` | `static void child_stacked(void)` |
| `child_strict` | function | `progs/src/lxsecc.c:150` | `static void child_strict(void)` |
| `child_wx` | function | `progs/src/lxsecc.c:116` | `static void child_wx(void)` |
| `exit_code_of` | function | `progs/src/lxsecc.c:53` | `static int exit_code_of(int st)` |
| `grandchild_inherits` | function | `progs/src/lxsecc.c:127` | `static void grandchild_inherits(void)` |
| `install_filter` | function | `progs/src/lxsecc.c:72` | `static int install_filter(unsigned getpid_action)` |
| `main` | function | `progs/src/lxsecc.c:215` | `int main(int argc, char **argv)` |
| `report` | function | `progs/src/lxsecc.c:44` | `static void report(const char *name, int ok, const char *detail)` |
| `run_child` | function | `progs/src/lxsecc.c:58` | `static int run_child(void (*body)(void))` |
| `LXSEL_BAD_FD` | macro | `progs/src/lxsel.c:29` | `#define LXSEL_BAD_FD` |
| `LXSEL_NFDS_OUT_OF_RANGE` | macro | `progs/src/lxsel.c:28` | `#define LXSEL_NFDS_OUT_OF_RANGE` |
| `LXSEL_PSELECT_TIMEOUT_NS` | macro | `progs/src/lxsel.c:32` | `#define LXSEL_PSELECT_TIMEOUT_NS` |
| `LXSEL_TIMEOUT_MS_MIN` | macro | `progs/src/lxsel.c:31` | `#define LXSEL_TIMEOUT_MS_MIN` |
| `LXSEL_TIMEOUT_US` | macro | `progs/src/lxsel.c:30` | `#define LXSEL_TIMEOUT_US` |
| `_GNU_SOURCE` | macro | `progs/src/lxsel.c:17` | `#define _GNU_SOURCE` |
| `elapsed_ms` | function | `progs/src/lxsel.c:55` | `static long elapsed_ms(struct timespec *a, struct timespec *b)` |
| `main` | function | `progs/src/lxsel.c:60` | `int main(void)` |
| `raw_pselect6` | function | `progs/src/lxsel.c:50` | `static long raw_pselect6(long nfds, fd_set *r, fd_set *w, fd_set *e,                          str...` |
| `raw_select` | function | `progs/src/lxsel.c:45` | `static long raw_select(long nfds, fd_set *r, fd_set *w, fd_set *e,                        struct ...` |
| `report` | function | `progs/src/lxsel.c:36` | `static void report(const char *name, int ok)` |
| `LXTLS_CA_BUNDLE` | macro | `progs/src/lxtls.c:34` | `#define LXTLS_CA_BUNDLE` |
| `LXTLS_CONNECT_S` | macro | `progs/src/lxtls.c:32` | `#define LXTLS_CONNECT_S` |
| `LXTLS_MAX_REDIRECTS` | macro | `progs/src/lxtls.c:33` | `#define LXTLS_MAX_REDIRECTS` |
| `LXTLS_RAND_BYTES` | macro | `progs/src/lxtls.c:35` | `#define LXTLS_RAND_BYTES` |
| `LXTLS_TIMEOUT_S` | macro | `progs/src/lxtls.c:31` | `#define LXTLS_TIMEOUT_S` |
| `lxtls_debug` | function | `progs/src/lxtls.c:46` | `static int lxtls_debug(CURL *h, curl_infotype type, char *data, size_t size, void *user)` |
| `lxtls_rand` | function | `progs/src/lxtls.c:73` | `static int lxtls_rand(void)` |
| `lxtls_sink` | function | `progs/src/lxtls.c:39` | `static size_t lxtls_sink(char *data, size_t size, size_t nmemb, void *user)` |
| `lxtls_step` | function | `progs/src/lxtls.c:65` | `static int lxtls_step(const char *name, int ok)` |
| `main` | function | `progs/src/lxtls.c:87` | `int main(int argc, char **argv)` |
| `LZ4_BOUND_DEN` | macro | `progs/src/lz4.c:31` | `#define LZ4_BOUND_DEN` |
| `LZ4_BOUND_SLACK` | macro | `progs/src/lz4.c:32` | `#define LZ4_BOUND_SLACK` |
| `LZ4_EXIT_FAIL` | macro | `progs/src/lz4.c:37` | `#define LZ4_EXIT_FAIL` |
| `LZ4_HDR_SIZE` | macro | `progs/src/lz4.c:30` | `#define LZ4_HDR_SIZE` |
| `LZ4_MAX_BLOCK` | macro | `progs/src/lz4.c:33` | `#define LZ4_MAX_BLOCK` |
| `LZ4_SEEK_END` | macro | `progs/src/lz4.c:35` | `#define LZ4_SEEK_END` |
| `fclose` | function | `progs/src/lz4.c:20` | `int fclose();` |
| `fopen` | function | `progs/src/lz4.c:19` | `void *fopen();` |
| `fread` | function | `progs/src/lz4.c:21` | `int fread();` |
| `free` | function | `progs/src/lz4.c:15` | `void free();` |
| `fseek` | function | `progs/src/lz4.c:23` | `int fseek();` |
| `ftell` | function | `progs/src/lz4.c:24` | `int ftell();` |
| `fwrite` | function | `progs/src/lz4.c:22` | `int fwrite();` |
| `kernel` | function | `progs/src/lz4.c:6` | `* * The codec lives in the kernel (lz4_kernel.c, the same one MiniFS uses), so * these tools are thin front-ends...` |
| `lz4_compress` | function | `progs/src/lz4.c:27` | `int lz4_compress(char *src, int srclen, char *dst, int dstcap);` |
| `lz4_compress_file` | function | `progs/src/lz4.c:80` | `static int lz4_compress_file(const char *src, const char *dst)` |
| `lz4_decompress` | function | `progs/src/lz4.c:28` | `int lz4_decompress(char *src, int srclen, char *dst, int dstcap);` |
| `lz4_decompress_file` | function | `progs/src/lz4.c:117` | `static int lz4_decompress_file(const char *src, const char *dst)` |
| `lz4_has` | function | `progs/src/lz4.c:39` | `static int lz4_has(const char *s, const char *needle)` |
| `lz4_read_all` | function | `progs/src/lz4.c:53` | `static char *lz4_read_all(const char *name, int *len)` |
| `lz4_write_all` | function | `progs/src/lz4.c:70` | `static int lz4_write_all(const char *name, char *data, int len)` |
| `main` | function | `progs/src/lz4.c:164` | `int main(int argc, char **argv)` |
| `printf` | function | `progs/src/lz4.c:16` | `int printf();` |
| `rewind` | function | `progs/src/lz4.c:25` | `void rewind();` |
| `strcmp` | function | `progs/src/lz4.c:17` | `int strcmp();` |
| `strlen` | function | `progs/src/lz4.c:18` | `int strlen();` |
| `LZSS_EI` | macro | `progs/src/lzss.c:26` | `#define LZSS_EI` |
| `LZSS_EJ` | macro | `progs/src/lzss.c:27` | `#define LZSS_EJ` |
| `LZSS_ENC_SLACK` | macro | `progs/src/lzss.c:39` | `#define LZSS_ENC_SLACK` |
| `LZSS_ERR_NONE` | macro | `progs/src/lzss.c:45` | `#define LZSS_ERR_NONE` |
| `LZSS_ERR_OVERFLOW` | macro | `progs/src/lzss.c:46` | `#define LZSS_ERR_OVERFLOW` |
| `LZSS_EXIT_FAIL` | macro | `progs/src/lzss.c:48` | `#define LZSS_EXIT_FAIL` |
| `LZSS_EXPAND_DEN` | macro | `progs/src/lzss.c:41` | `#define LZSS_EXPAND_DEN` |
| `LZSS_EXPAND_NUM` | macro | `progs/src/lzss.c:40` | `#define LZSS_EXPAND_NUM` |
| `LZSS_F` | macro | `progs/src/lzss.c:30` | `#define LZSS_F` |
| `LZSS_HDR_SIZE` | macro | `progs/src/lzss.c:37` | `#define LZSS_HDR_SIZE` |
| `LZSS_MAGIC0` | macro | `progs/src/lzss.c:33` | `#define LZSS_MAGIC0` |
| `LZSS_MAGIC1` | macro | `progs/src/lzss.c:34` | `#define LZSS_MAGIC1` |
| `LZSS_MAGIC2` | macro | `progs/src/lzss.c:35` | `#define LZSS_MAGIC2` |
| `LZSS_MAGIC3` | macro | `progs/src/lzss.c:36` | `#define LZSS_MAGIC3` |
| `LZSS_N` | macro | `progs/src/lzss.c:29` | `#define LZSS_N` |
| `LZSS_P` | macro | `progs/src/lzss.c:28` | `#define LZSS_P` |
| `LZSS_SEEK_END` | macro | `progs/src/lzss.c:43` | `#define LZSS_SEEK_END` |
| `LZSS_WIN` | macro | `progs/src/lzss.c:31` | `#define LZSS_WIN` |
| `fclose` | function | `progs/src/lzss.c:19` | `int fclose();` |
| `fopen` | function | `progs/src/lzss.c:18` | `void *fopen();` |
| `fread` | function | `progs/src/lzss.c:20` | `int fread();` |
| `free` | function | `progs/src/lzss.c:14` | `void free();` |
| `fseek` | function | `progs/src/lzss.c:22` | `int fseek();` |
| `ftell` | function | `progs/src/lzss.c:23` | `int ftell();` |
| `fwrite` | function | `progs/src/lzss.c:21` | `int fwrite();` |
| `lz_compress` | function | `progs/src/lzss.c:278` | `static int lz_compress(const char *src, const char *dst)` |
| `lz_decode` | function | `progs/src/lzss.c:189` | `static int lz_decode(void)` |
| `lz_decompress` | function | `progs/src/lzss.c:325` | `static int lz_decompress(const char *src, const char *dst)` |
| `lz_encode` | function | `progs/src/lzss.c:118` | `static int lz_encode(void)` |
| `lz_flush_bits` | function | `progs/src/lzss.c:93` | `static void lz_flush_bits(void)` |
| `lz_getbit` | function | `progs/src/lzss.c:173` | `static int lz_getbit(int n)` |
| `lz_has` | function | `progs/src/lzss.c:237` | `static int lz_has(const char *s, const char *needle)` |
| `lz_hdr_get` | function | `progs/src/lzss.c:229` | `static int lz_hdr_get(char *h)` |
| `lz_hdr_put` | function | `progs/src/lzss.c:218` | `static void lz_hdr_put(char *h, int size)` |
| `lz_in_getc` | function | `progs/src/lzss.c:64` | `static int lz_in_getc(void)` |
| `lz_out_literal` | function | `progs/src/lzss.c:97` | `static void lz_out_literal(int c)` |
| `lz_out_pair` | function | `progs/src/lzss.c:105` | `static void lz_out_pair(int x, int y)` |
| `lz_out_put` | function | `progs/src/lzss.c:69` | `static void lz_out_put(int c)` |
| `lz_putbit0` | function | `progs/src/lzss.c:84` | `static void lz_putbit0(void)` |
| `lz_putbit1` | function | `progs/src/lzss.c:74` | `static void lz_putbit1(void)` |
| `lz_read_all` | function | `progs/src/lzss.c:251` | `static char *lz_read_all(const char *name, int *len)` |
| `lz_write_all` | function | `progs/src/lzss.c:268` | `static int lz_write_all(const char *name, char *data, int len)` |
| `main` | function | `progs/src/lzss.c:397` | `int main(int argc, char **argv)` |
| `malloc` | function | `progs/src/lzss.c:13` | `void *malloc();` |
| `printf` | function | `progs/src/lzss.c:15` | `int printf();` |
| `rewind` | function | `progs/src/lzss.c:24` | `void rewind();` |
| `strcmp` | function | `progs/src/lzss.c:16` | `int strcmp();` |
| `strlen` | function | `progs/src/lzss.c:17` | `int strlen();` |
| `ENOMEM` | function | `progs/src/mmreuse.c:3` | `* downward mmap cursor drains until a map fails with ENOMEM (-12);` |
| `_start` | function | `progs/src/mmreuse.c:35` | `void _start(void)` |
| `exit_now` | function | `progs/src/mmreuse.c:31` | `static void exit_now(long code)` |
| `mmap_anon` | function | `progs/src/mmreuse.c:7` | `static long mmap_anon(long len)` |
| `munmap` | function | `progs/src/mmreuse.c:21` | `static long munmap(long addr, long len)` |
| `_start` | function | `progs/src/mprot.c:48` | `void _start(void)` |
| `exit_now` | function | `progs/src/mprot.c:44` | `static void exit_now(long code)` |
| `mmap_anon` | function | `progs/src/mprot.c:11` | `static long mmap_anon(long len)` |
| `mprotect_sys` | function | `progs/src/mprot.c:25` | `static long mprotect_sys(long addr, long len, long prot)` |
| `write_str` | function | `progs/src/mprot.c:36` | `static long write_str(const char *s, long n)` |
| `MMUTEX_CONTENDED` | macro | `progs/src/mthreads.h:33` | `#define MMUTEX_CONTENDED` |
| `MMUTEX_FREE` | macro | `progs/src/mthreads.h:31` | `#define MMUTEX_FREE` |
| `MMUTEX_HELD` | macro | `progs/src/mthreads.h:32` | `#define MMUTEX_HELD` |
| `MMUTEX_SPINS` | macro | `progs/src/mthreads.h:34` | `#define MMUTEX_SPINS` |
| `MTHREADS_H` | macro | `progs/src/mthreads.h:24` | `#define MTHREADS_H` |
| `MTHREAD_MAX` | macro | `progs/src/mthreads.h:29` | `#define MTHREAD_MAX` |
| `MTHREAD_STACK_SZ` | macro | `progs/src/mthreads.h:28` | `#define MTHREAD_STACK_SZ` |
| `m_syscall6` | function | `progs/src/mthreads.h:50` | `static inline long m_syscall6(long n, long a, long b, long c)` |
| `mfutex_wait` | function | `progs/src/mthreads.h:63` | `static inline long mfutex_wait(volatile int *addr, int val)` |
| `mfutex_wake` | function | `progs/src/mthreads.h:67` | `static inline long mfutex_wake(volatile int *addr, int n)` |
| `mmutex_init` | function | `progs/src/mthreads.h:71` | `static inline void mmutex_init(mmutex_t *m)` |
| `mmutex_lock` | function | `progs/src/mthreads.h:75` | `static inline void mmutex_lock(mmutex_t *m)` |
| `mmutex_t` | struct | `progs/src/mthreads.h:38` | `` |
| `mmutex_unlock` | function | `progs/src/mthreads.h:90` | `static inline void mmutex_unlock(mmutex_t *m)` |

Next: [SYMBOLS_p24.md](SYMBOLS_p24.md)
