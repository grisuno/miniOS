# Symbols (page 21 of 25)
Previous: [SYMBOLS_p20.md](SYMBOLS_p20.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
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
| `LXABI_A6_MAGIC` | macro | `progs/src/lxabi.c:47` | `#define LXABI_A6_MAGIC` |
| `LXABI_CHILD_BAD` | macro | `progs/src/lxabi.c:48` | `#define LXABI_CHILD_BAD` |
| `LXABI_CHILD_DELAY_MS` | macro | `progs/src/lxabi.c:36` | `#define LXABI_CHILD_DELAY_MS` |
| `LXABI_CLOCK_SKEW_S` | macro | `progs/src/lxabi.c:43` | `#define LXABI_CLOCK_SKEW_S` |
| `LXABI_CLONE_NR` | macro | `progs/src/lxabi.c:45` | `#define LXABI_CLONE_NR` |
| `LXABI_CLOSE_RANGE_NR` | macro | `progs/src/lxabi.c:51` | `#define LXABI_CLOSE_RANGE_NR` |
| `LXABI_DETACHED` | macro | `progs/src/lxabi.c:39` | `#define LXABI_DETACHED` |
| `LXABI_EPOCH_2023` | macro | `progs/src/lxabi.c:42` | `#define LXABI_EPOCH_2023` |
| `LXABI_MKDIR_FILE` | macro | `progs/src/lxabi.c:50` | `#define LXABI_MKDIR_FILE` |
| `LXABI_MKDIR_PATH` | macro | `progs/src/lxabi.c:49` | `#define LXABI_MKDIR_PATH` |
| `LXABI_REG_PROBE_WORDS` | macro | `progs/src/lxabi.c:44` | `#define LXABI_REG_PROBE_WORDS` |
| `LXABI_SIGCHLD` | macro | `progs/src/lxabi.c:46` | `#define LXABI_SIGCHLD` |
| `LXABI_THREADS` | macro | `progs/src/lxabi.c:37` | `#define LXABI_THREADS` |
| `LXABI_THREAD_ITERS` | macro | `progs/src/lxabi.c:38` | `#define LXABI_THREAD_ITERS` |
| `LXABI_TIMEDWAIT_MS` | macro | `progs/src/lxabi.c:41` | `#define LXABI_TIMEDWAIT_MS` |
| `LXABI_WAIT_SPINS` | macro | `progs/src/lxabi.c:40` | `#define LXABI_WAIT_SPINS` |
| `_GNU_SOURCE` | macro | `progs/src/lxabi.c:17` | `#define _GNU_SOURCE` |
| `busy_wait_ms` | function | `progs/src/lxabi.c:71` | `static void busy_wait_ms(long ms)` |
| `check_close_range` | function | `progs/src/lxabi.c:385` | `static void check_close_range(void)` |
| `check_condvar` | function | `progs/src/lxabi.c:242` | `static void check_condvar(void)` |
| `check_detached_reaped` | function | `progs/src/lxabi.c:208` | `static void check_detached_reaped(void)` |
| `check_eventfd` | function | `progs/src/lxabi.c:360` | `static void check_eventfd(void)` |
| `check_fork_registers` | function | `progs/src/lxabi.c:128` | `static void check_fork_registers(void)` |
| `check_mkdir` | function | `progs/src/lxabi.c:406` | `static void check_mkdir(void)` |
| `check_pipe2_flags` | function | `progs/src/lxabi.c:264` | `static void check_pipe2_flags(void)` |
| `check_pipe_blocking` | function | `progs/src/lxabi.c:291` | `static void check_pipe_blocking(void)` |
| `check_pipe_epipe` | function | `progs/src/lxabi.c:313` | `static void check_pipe_epipe(void)` |
| `check_poll` | function | `progs/src/lxabi.c:336` | `static void check_poll(void)` |
| `check_threads` | function | `progs/src/lxabi.c:172` | `static void check_threads(void)` |
| `check_time` | function | `progs/src/lxabi.c:397` | `static void check_time(void)` |
| `check_writev_pipe` | function | `progs/src/lxabi.c:324` | `static void check_writev_pipe(void)` |
| `detached_worker` | function | `progs/src/lxabi.c:202` | `static void *detached_worker(void *arg)` |
| `fork_probe` | function | `progs/src/lxabi.c:85` | `static void fork_probe(uint64_t *out)` |
| `main` | function | `progs/src/lxabi.c:417` | `int main(void)` |
| `now_ms` | function | `progs/src/lxabi.c:65` | `static long now_ms(void)` |
| `regs_match` | function | `progs/src/lxabi.c:122` | `static int regs_match(const uint64_t *r)` |
| `report` | function | `progs/src/lxabi.c:55` | `static void report(const char *name, int ok, const char *detail)` |
| `signaller` | function | `progs/src/lxabi.c:232` | `static void *signaller(void *arg)` |
| `thread_result` | struct | `progs/src/lxabi.c:152` | `` |
| `tls_seen` | type_alias | `progs/src/lxabi.c:151` | `typedef struct thread_result { long tls_seen;` |
| `worker` | function | `progs/src/lxabi.c:158` | `static void *worker(void *arg)` |
| `SYS_exit` | macro | `progs/src/lxhello.c:21` | `#define SYS_exit` |
| `SYS_write` | macro | `progs/src/lxhello.c:20` | `#define SYS_write` |
| `lmain` | function | `progs/src/lxhello.c:46` | `int lmain(long argc, char **argv)` |
| `lx_strlen` | function | `progs/src/lxhello.c:23` | `static unsigned long lx_strlen(const char *s)` |
| `lx_syscall3` | function | `progs/src/lxhello.c:11` | `static long lx_syscall3(long n, long a1, long a2, long a3)` |
| `lx_write` | function | `progs/src/lxhello.c:29` | `static void lx_write(const char *s)` |
| `lx_write_int` | function | `progs/src/lxhello.c:33` | `static void lx_write_int(long v)` |
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
| `mthread_create` | function | `progs/src/mthreads.h:117` | `static int mthread_create(mthread_t *t, void *(*fn)(void *), void *arg)` |
| `mthread_entry` | function | `progs/src/mthreads.h:98` | `static void mthread_entry(void *p)` |
| `mthread_join` | function | `progs/src/mthreads.h:140` | `static int mthread_join(mthread_t t, void **retval)` |
| `mthread_slot_t` | struct | `progs/src/mthreads.h:42` | `` |
| `mthread_t` | type_alias | `progs/src/mthreads.h:35` | `typedef int mthread_t;` |
| `myield` | function | `progs/src/mthreads.h:59` | `static inline void myield(void)` |
| `MTOP_DISK_BUF` | macro | `progs/src/mtop.c:47` | `#define MTOP_DISK_BUF` |
| `MTOP_DISK_MAX` | macro | `progs/src/mtop.c:48` | `#define MTOP_DISK_MAX` |
| `MTOP_HIST` | macro | `progs/src/mtop.c:46` | `#define MTOP_HIST` |
| `MTOP_MINFO` | macro | `progs/src/mtop.c:49` | `#define MTOP_MINFO` |
| `close` | function | `progs/src/mtop.c:43` | `int close();` |
| `emit` | function | `progs/src/mtop.c:90` | `static void emit(char *s)` |
| `fclose` | function | `progs/src/mtop.c:39` | `int fclose();` |
| `fopen` | function | `progs/src/mtop.c:38` | `void *fopen();` |
| `fread` | function | `progs/src/mtop.c:40` | `int fread();` |
| `main` | function | `progs/src/mtop.c:531` | `int main(int argc, char **argv)` |
| `mtop_atoi` | function | `progs/src/mtop.c:117` | `static int mtop_atoi(char *s)` |
| `mtop_bar` | function | `progs/src/mtop.c:179` | `static void mtop_bar(long v, long max, int w)` |
| `mtop_clear` | function | `progs/src/mtop.c:113` | `static void mtop_clear(void)` |
| `mtop_clear_ansi` | function | `progs/src/mtop.c:103` | `static void mtop_clear_ansi(void)` |
| `mtop_cpu` | function | `progs/src/mtop.c:253` | `static long mtop_cpu(long *count, long *busy)` |
| `mtop_disk_open` | function | `progs/src/mtop.c:289` | `static void mtop_disk_open(void)` |
| `mtop_disk_read` | function | `progs/src/mtop.c:313` | `static long mtop_disk_read(long *bytes)` |
| `mtop_frame` | function | `progs/src/mtop.c:355` | `static void mtop_frame(int n)` |
| `mtop_hist_max` | function | `progs/src/mtop.c:194` | `static long mtop_hist_max(long *h, int n)` |
| `mtop_hist_push` | function | `progs/src/mtop.c:204` | `static void mtop_hist_push(long *h, long v)` |
| `mtop_key` | function | `progs/src/mtop.c:80` | `static long mtop_key(void)` |
| `mtop_mem` | function | `progs/src/mtop.c:242` | `static long mtop_mem(long *used, long *freeb, long *total)` |
| `mtop_minfo` | function | `progs/src/mtop.c:84` | `static long mtop_minfo(long sel, long *o1, long *o2)` |
| `mtop_net_probe` | function | `progs/src/mtop.c:337` | `static long mtop_net_probe(long *dns_ms, long *sock_ok)` |
| `mtop_put2` | function | `progs/src/mtop.c:158` | `static void mtop_put2(int v)` |
| `mtop_put_kb` | function | `progs/src/mtop.c:163` | `static void mtop_put_kb(long kb)` |
| `mtop_putu` | function | `progs/src/mtop.c:136` | `static void mtop_putu(long v)` |
| `mtop_quit_key` | function | `progs/src/mtop.c:94` | `static int mtop_quit_key(long k)` |
| `mtop_rtc` | function | `progs/src/mtop.c:76` | `static long mtop_rtc(int *h, int *m, int *s)` |
| `mtop_spark` | function | `progs/src/mtop.c:214` | `static void mtop_spark(long *h, int n)` |
| `mtop_time` | function | `progs/src/mtop.c:72` | `static long mtop_time(void)` |
| `net_dns_resolve` | function | `progs/src/mtop.c:44` | `int net_dns_resolve();` |
| `putchar` | function | `progs/src/mtop.c:35` | `int putchar();` |
| `rewind` | function | `progs/src/mtop.c:41` | `void rewind();` |
| `sc3` | function | `progs/src/mtop.c:63` | `static long sc3(long n, long a1, long a2, long a3)` |
| `socket` | function | `progs/src/mtop.c:42` | `int socket();` |
| `strcmp` | function | `progs/src/mtop.c:37` | `int strcmp();` |
| `strlen` | function | `progs/src/mtop.c:36` | `int strlen();` |
| `syscall` | function | `progs/src/mtop.c:12` | `* * All system figures come from the MINFO syscall (251): heap used / * free, ramdisk used / cap, MiniFS free /...` |
| `lmain` | function | `progs/src/mvrn.c:32` | `int lmain(void)` |
| `mvrn_exit` | function | `progs/src/mvrn.c:20` | `static void mvrn_exit(long code)` |
| `mvrn_fail` | function | `progs/src/mvrn.c:24` | `static void mvrn_fail(int step)` |
| `mvrn_sc3` | function | `progs/src/mvrn.c:9` | `static long mvrn_sc3(long n, long a1, long a2, long a3)` |
| `mvrn_write` | function | `progs/src/mvrn.c:16` | `static void mvrn_write(const char *s, unsigned long len)` |
| `_start` | function | `progs/src/nx.c:23` | `void _start(void)` |
| `exit_now` | function | `progs/src/nx.c:19` | `static void exit_now(long code)` |
| `write_str` | function | `progs/src/nx.c:11` | `static long write_str(const char *s, long n)` |
| `BUF_MS` | macro | `progs/src/opl3.c:32` | `#define BUF_MS` |
| `F_NUM_FACTOR` | macro | `progs/src/opl3.c:34` | `#define F_NUM_FACTOR` |
| `MONO_BYTES` | macro | `progs/src/opl3.c:30` | `#define MONO_BYTES` |
| `SAMPLE_RATE` | macro | `progs/src/opl3.c:28` | `#define SAMPLE_RATE` |
| `STEREO_FRAMES` | macro | `progs/src/opl3.c:29` | `#define STEREO_FRAMES` |
| `SYS_SB16_OPEN` | macro | `progs/src/opl3.c:22` | `#define SYS_SB16_OPEN` |
| `SYS_SB16_SUBMIT` | macro | `progs/src/opl3.c:23` | `#define SYS_SB16_SUBMIT` |
| `SYS_TIME` | macro | `progs/src/opl3.c:21` | `#define SYS_TIME` |
| `SYS_WRITE` | macro | `progs/src/opl3.c:24` | `#define SYS_WRITE` |
| `busy_ms` | function | `progs/src/opl3.c:46` | `static void busy_ms(long ms)` |
| `main` | function | `progs/src/opl3.c:107` | `int main(void)` |
| `note_t` | struct | `progs/src/opl3.c:102` | `` |
| `opl3_note` | function | `progs/src/opl3.c:69` | `static void opl3_note(opl3_chip *chip, unsigned block, unsigned fnum, int on)` |
| `opl3_set_instrument` | function | `progs/src/opl3.c:52` | `static void opl3_set_instrument(opl3_chip *chip)` |
| `render` | function | `progs/src/opl3.c:77` | `static void render(opl3_chip *chip, long ms, long *fail)` |
| `sys_open` | function | `progs/src/opl3.c:39` | `static long sys_open(long on)` |
| `sys_submit` | function | `progs/src/opl3.c:42` | `static long sys_submit(const void *buf, long len)` |
| `sys_time` | function | `progs/src/opl3.c:36` | `static long sys_time(void)` |
| `_start` | function | `progs/src/pcmap.c:75` | `void _start(void)` |
| `sc_exit` | function | `progs/src/pcmap.c:42` | `static void sc_exit(long code)` |
| `sc_fnv` | function | `progs/src/pcmap.c:46` | `static unsigned long sc_fnv(const char *p, long n)` |
| `sc_hex8` | function | `progs/src/pcmap.c:56` | `static void sc_hex8(unsigned long v, char *out)` |
| `sc_mmap` | function | `progs/src/pcmap.c:21` | `static long sc_mmap(long len, long prot, long flags, long fd, long off)` |
| `sc_munmap` | function | `progs/src/pcmap.c:65` | `static long sc_munmap(long addr, long len)` |
| `sc_open` | function | `progs/src/pcmap.c:12` | `static long sc_open(const char *p)` |
| `sc_write` | function | `progs/src/pcmap.c:34` | `static long sc_write(long fd, const char *s, long n)` |
| `lmain` | function | `progs/src/pollready.c:63` | `int lmain(long argc, char **argv)` |
| `p_atoi` | function | `progs/src/pollready.c:40` | `static int p_atoi(const char *s)` |
| `p_parse_ip` | function | `progs/src/pollready.c:46` | `static int p_parse_ip(const char *s, unsigned char out[4])` |
| `p_puts` | function | `progs/src/pollready.c:36` | `static void p_puts(long fd, const char *s)` |
| `p_strlen` | function | `progs/src/pollready.c:30` | `static unsigned long p_strlen(const char *s)` |
| `p_write` | function | `progs/src/pollready.c:26` | `static long p_write(long fd, const char *s, long n)` |
| `BUF` | macro | `progs/src/sbtone.c:26` | `#define BUF` |
| `RATE` | macro | `progs/src/sbtone.c:25` | `#define RATE` |
| `SYS_SB16_OPEN` | macro | `progs/src/sbtone.c:21` | `#define SYS_SB16_OPEN` |
| `SYS_SB16_SUBMIT` | macro | `progs/src/sbtone.c:22` | `#define SYS_SB16_SUBMIT` |
| `SYS_TIME` | macro | `progs/src/sbtone.c:23` | `#define SYS_TIME` |
| `WINDOW_MS` | macro | `progs/src/sbtone.c:27` | `#define WINDOW_MS` |
| `buffers` | function | `progs/src/sbtone.c:14` | `*  * Exit code is the number of submitted buffers (0 on failure to open).  */  #include <stdio.h>...` |
| `main` | function | `progs/src/sbtone.c:36` | `int main(void)` |
| `SC_ARENA` | macro | `progs/src/scfuzz.c:16` | `#define SC_ARENA` |
| `SC_OPS` | macro | `progs/src/scfuzz.c:15` | `#define SC_OPS` |
| `SC_PAGE` | macro | `progs/src/scfuzz.c:17` | `#define SC_PAGE` |
| `SC_PAGES` | macro | `progs/src/scfuzz.c:18` | `#define SC_PAGES` |
| `SC_T0_BASE` | macro | `progs/src/scfuzz.c:19` | `#define SC_T0_BASE` |
| `SC_T0_N` | macro | `progs/src/scfuzz.c:20` | `#define SC_T0_N` |
| `SC_T1_BASE` | macro | `progs/src/scfuzz.c:21` | `#define SC_T1_BASE` |
| `SC_T1_N` | macro | `progs/src/scfuzz.c:22` | `#define SC_T1_N` |
| `_start` | function | `progs/src/scfuzz.c:160` | `void _start(void)` |
| `guest` | function | `progs/src/scfuzz.c:7` | `* the guest (the BDD timeout then talks). All fuzz maps stay inside  * one private 4 MB arena (pa...` |
| `sc_exit` | function | `progs/src/scfuzz.c:61` | `static void sc_exit(long code)` |
| `sc_fold` | function | `progs/src/scfuzz.c:76` | `static unsigned long sc_fold(unsigned long h, unsigned long v)` |
| `sc_hex8` | function | `progs/src/scfuzz.c:88` | `static void sc_hex8(unsigned long v, char *out)` |
| `sc_mprotect` | function | `progs/src/scfuzz.c:38` | `static long sc_mprotect(long addr, long len, long prot)` |
| `sc_munmap` | function | `progs/src/scfuzz.c:49` | `static long sc_munmap(long addr, long len)` |
| `sc_rng` | function | `progs/src/scfuzz.c:67` | `static unsigned long sc_rng(unsigned long *s)` |
| `sc_thread1` | function | `progs/src/scfuzz.c:154` | `static void *sc_thread1(void *arg)` |
| `sc_worker` | function | `progs/src/scfuzz.c:97` | `static unsigned long sc_worker(int me, unsigned long seed)` |
| `sc_write` | function | `progs/src/scfuzz.c:53` | `static long sc_write(long fd, const char *s, long n)` |
| `expand` | function | `progs/src/shell.py:30` | `def expand(line, env)` |
| `main` | function | `progs/src/shell.py:36` | `def main()` |
| `run_capture` | function | `progs/src/shell.py:20` | `def run_capture(cmd, args)` |
| `SPIN_WLA` | macro | `progs/src/spin.c:58` | `#define SPIN_WLA` |
| `SPIN_WLB` | macro | `progs/src/spin.c:59` | `#define SPIN_WLB` |
| `SPIN_WLH` | macro | `progs/src/spin.c:57` | `#define SPIN_WLH` |
| `SPIN_WLW` | macro | `progs/src/spin.c:56` | `#define SPIN_WLW` |
| `lmain` | function | `progs/src/spin.c:225` | `int lmain(long argc, char **argv)` |
| `lx_atoi` | function | `progs/src/spin.c:42` | `static long lx_atoi(const char *s)` |
| `lx_strlen` | function | `progs/src/spin.c:20` | `static unsigned long lx_strlen(const char *s)` |
| `lx_syscall3` | function | `progs/src/spin.c:11` | `static long lx_syscall3(long n, long a1, long a2, long a3)` |
| `lx_write` | function | `progs/src/spin.c:26` | `static void lx_write(const char *s)` |
| `lx_write_int` | function | `progs/src/spin.c:30` | `static void lx_write_int(long v)` |
| `spin_box_ok` | function | `progs/src/spin.c:82` | `static int spin_box_ok(const char *box)` |
| `spin_emit` | function | `progs/src/spin.c:114` | `static int spin_emit(const char *box, unsigned int seq,         const unsigned char *msg, long mlen)` |
| `spin_hdr` | function | `progs/src/spin.c:73` | `static void spin_hdr(unsigned char *d, unsigned long id, unsigned long op,         unsigned long ...` |
| `spin_hex8` | function | `progs/src/spin.c:95` | `static void spin_hex8(unsigned int v, char *dst)` |
| `spin_pixels` | function | `progs/src/spin.c:169` | `static void spin_pixels(long off)` |
| `spin_raw_file` | function | `progs/src/spin.c:145` | `static int spin_raw_file(const char *box)` |
| `spin_u32` | function | `progs/src/spin.c:66` | `static void spin_u32(unsigned char *d, unsigned long v)` |
| `spin_wl` | function | `progs/src/spin.c:181` | `static int spin_wl(const char *box, const char *narg)` |
| `spin_write_all` | function | `progs/src/spin.c:104` | `static long spin_write_all(long fd, const unsigned char *buf, long len)` |
| `add` | function | `progs/src/test.c:1` | `int add(int a, int b)` |
| `main` | function | `progs/src/test.c:2` | `int main(void)` |
| `check` | function | `progs/src/test.lua:12` | `` |
| `read_file` | function | `progs/src/test.lua:30` | `` |
| `test_bin_aes` | function | `progs/src/test.lua:175` | `` |
| `test_bin_cp` | function | `progs/src/test.lua:135` | `` |
| `test_bin_freedom` | function | `progs/src/test.lua:205` | `` |
| `test_bin_json` | function | `progs/src/test.lua:194` | `` |
| `test_bin_lz4` | function | `progs/src/test.lua:141` | `` |
| `test_bin_lzss` | function | `progs/src/test.lua:158` | `` |
| `test_dlmalloc` | function | `progs/src/test.lua:80` | `` |
| `test_filesystem` | function | `progs/src/test.lua:53` | `` |
| `test_ftest` | function | `progs/src/test.lua:90` | `` |
| `test_hello` | function | `progs/src/test.lua:85` | `` |
| `test_ld` | function | `progs/src/test.lua:100` | `` |
| `test_minigcc` | function | `progs/src/test.lua:95` | `` |
| `test_module_bindings` | function | `progs/src/test.lua:40` | `` |
| `test_spawn_preserves_interpreter` | function | `progs/src/test.lua:122` | `` |
| `test_stb` | function | `progs/src/test.lua:75` | `` |
| `test_toolchain_roundtrip` | function | `progs/src/test.lua:112` | `` |
| `test_xxhash` | function | `progs/src/test.lua:70` | `` |
| `write_file` | function | `progs/src/test.lua:22` | `` |
| `check` | function | `progs/src/test.py:15` | `def check(name, cond, detail)` |
| `main` | function | `progs/src/test.py:261` | `def main()` |

Next: [SYMBOLS_p22.md](SYMBOLS_p22.md)
