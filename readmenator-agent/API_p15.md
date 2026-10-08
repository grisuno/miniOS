# API (page 15 of 19)
Previous: [API_p14.md](API_p14.md)

## progs/file/file.c
Depends on: `headers/leakcheck.h`, `kernel/string.c`, `progs/file/file_assoc.h`, `progs/minios_abi.h`, `progs/minios_png.h`, `progs/nuklear/nuklear_minios.h`, `progs/nuklear/nuklear_theme.h`
- `file_sys_dir_list` (function) `progs/file/file.c:101` `static long file_sys_dir_list(const char *path, char *buf, long cap)` -- static unsigned char file_icon_mask[FILE_ICON_N][FILE_ICON_MAX * FILE_ICON_MAX]; static struct nk_minios_img...
- `file_sys_spawn` (function) `progs/file/file.c:111` `static long file_sys_spawn(const char *path, int argc, const char **argv)` -- static int file_preview_h; static int file_preview_on; /** Raw DIR_LIST syscall (241): names land NUL-separated in...
- `file_ext_of` (function) `progs/file/file.c:122` `static void file_ext_of(const char *fname, char *dst, unsigned cap)` -- } /** Raw SPAWN syscall (215) preserving this app across the child. static long file_sys_spawn(const char *path, int...
- `file_icon_kind` (function) `progs/file/file.c:146` `static int file_icon_kind(const char *fname, int isdir)` -- Icon kind for an entry: folder for dirs, image for .png, object for .o/.elf/.cvm, files for the text kinds...
- `file_icon_sz` (function) `progs/file/file.c:158` `static int file_icon_sz(void)` -- and for anything else.
- `file_icon_decode` (function) `progs/file/file.c:165` `static int file_icon_decode(const char *path, unsigned char *px,
                            unsi...` -- Decode one RGBA icon into indexed pixels plus an alpha mask, scaled to the live size.
- `file_icons_load` (function) `progs/file/file.c:213` `static int file_icons_load(void)` -- Load the four kind icons; all-or-nothing so the UI never mixes icon * and text rows.
- `file_toggle_icons` (function) `progs/file/file.c:238` `static int file_toggle_icons(void)` -- Flip the icon size and reload the four kind icons.
- `file_join` (function) `progs/file/file.c:245` `static int file_join(const char *dir, const char *name, char *dst, unsigned cap)` -- Flip the icon size and reload the four kind icons.
- `file_parent` (function) `progs/file/file.c:259` `static void file_parent(char *path)` -- static int file_join(const char *dir, const char *name, char *dst, unsigned cap) { unsigned a = 0; unsigned b = 0...
- `file_assoc_line` (function) `progs/file/file.c:269` `static int file_assoc_line(const char *line, char *ext, char *prog)` -- return 0; } /** Parent of an absolute path, root stays root. static void file_parent(char *path) { unsigned n = 0...
- `file_assoc_load` (function) `progs/file/file.c:302` `static void file_assoc_load(void)` -- } if (line[p + k] && line[p + k] != '\n' && line[p + k] != '\r') return -1; while (p > 0 && (prog[p - 1] == ' ' ||...
- `file_assoc_lookup` (function) `progs/file/file.c:318` `static const char *file_assoc_lookup(const char *ext)` -- char line[FILE_LOG_LINE]; char ext[FILE_EXT_MAX + 1]; char prog[FILE_PROG_MAX + 1]; fassoc_clear(&file_assocs); f =...
- `file_action_of` (function) `progs/file/file.c:323` `static int file_action_of(const char *fname, const char **prog_out)` -- if (!f) return; while (fgets(line, sizeof(line), f)) { if (file_assoc_line(line, ext, prog) != 0) continue; if...
- `file_refresh` (function) `progs/file/file.c:336` `static void file_refresh(void)` -- /** Dispatch kind for a file name through the association table. static int file_action_of(const char *fname, const...
- `file_preview_load` (function) `progs/file/file.c:351` `static int file_preview_load(const char *path)` -- long rc = file_sys_dir_list(file_cwd, file_entries, FILE_LIST_CAP); if (rc < 0) { file_entry_count = 0...
- `file_preview_blit` (function) `progs/file/file.c:385` `static void file_preview_blit(int ox, int oy)` -- Blit the preview buffer into the NK back-buffer after rasterize (and its * RGB twin when the kernel maps it).
- `file_spawn_visible` (function) `progs/file/file.c:407` `static long file_spawn_visible(const char *tool, int argc, const char **argv,
                   ...` -- int dx = ox + x; int dy = oy + y; unsigned char r, g, b; volatile uint8_t *d; if (dx < 0 || dx >= NK_W || dy < 0 ||...
- `file_open_text` (function) `progs/file/file.c:430` `static void file_open_text(const char *path)` -- printf("file: %s exit code: %ld\n", label, rc); fflush(stdout); nk_sys_vga_mode(1); nk_build_palette(pal768)...
- `file_run_shell` (function) `progs/file/file.c:441` `static void file_run_shell(const char *path)` -- } /** Open a text file in vedit, preserving this browser. static void file_open_text(const char *path) { const char...
- `file_activate` (function) `progs/file/file.c:480` `static void file_activate(const char *dir, const char *name)` -- if (strcmp(ext, "cvm") == 0) { args[0] = path; args[1] = 0; snprintf(label, sizeof(label), "run %s", path)...
- `file_ui_build` (function) `progs/file/file.c:511` `static void file_ui_build(struct nk_context *ctx)` -- snprintf(file_preview_path, sizeof(file_preview_path), "%s", path); snprintf(file_status, sizeof(file_status)...
- `file_selftest` (function) `progs/file/file.c:613` `static int file_selftest(void)` -- Headless selftest for BDD: assoc vectors plus a live listing.
- `file_gui_run` (function) `progs/file/file.c:779` `static void file_gui_run(void)`
- `main` (function) `progs/file/file.c:838` `int main(int argc, char **argv)`

## progs/file/file_assoc.h
Depends on: `kernel/string.c`
Imported by: `progs/file/file.c`, `tests/test_file_assoc.c`, `tests/test_leakcheck.c`
- `fassoc_ext_ok` (function) `progs/file/file_assoc.h:59` `static int fassoc_ext_ok(const char *ext)` -- /** Docstring: one validated association entry, ext without dot. struct fassoc_entry { char ext[FASSOC_EXT_MAX + 1]...
- `fassoc_prog_ok` (function) `progs/file/file_assoc.h:73` `static int fassoc_prog_ok(const char *prog)` -- static int fassoc_ext_ok(const char *ext) { size_t n = 0; size_t k = 0; if (ext == NULL) return 0; while (ext[n] !=...
- `fassoc_clear` (function) `progs/file/file_assoc.h:89` `static void fassoc_clear(struct fassoc_table *t)` -- size_t k = 0; if (prog == NULL) return 0; while (prog[n] != 0) n++; if (n == 0 || n > (size_t)FASSOC_PROG_MAX)...
- `fassoc_free` (function) `progs/file/file_assoc.h:95` `static void fassoc_free(struct fassoc_table *t)` -- if (prog[0] != '/') return 0; for (k = 0; k < n; k++) { if (prog[k] == '|') return 0; } return 1; } /** Docstring...
- `fassoc_reserve` (function) `progs/file/file_assoc.h:104` `static int fassoc_reserve(struct fassoc_table *t, size_t want)` -- if (t == NULL) return; t->cnt = 0; } /** Docstring: release backing store and reset to zero init state. static void...
- `fassoc_push` (function) `progs/file/file_assoc.h:125` `static int fassoc_push(struct fassoc_table *t, const char *ext, const char *prog)` -- while (ncap < want) { size_t nxt = ncap * (size_t)FASSOC_GROW_NUM / (size_t)FASSOC_GROW_DEN + 1; if (nxt <= ncap)...
- `fassoc_lookup` (function) `progs/file/file_assoc.h:140` `static const char *fassoc_lookup(const struct fassoc_table *t, const char *ext)` -- if (t == NULL) return -1; if (!fassoc_ext_ok(ext)) return -1; if (!fassoc_prog_ok(prog)) return -1; if (t->cnt >=...
- `fassoc_count` (function) `progs/file/file_assoc.h:150` `static size_t fassoc_count(const struct fassoc_table *t)` -- return 0; } /** Docstring: program for ext in file order, empty string when unmapped. static const char...

## progs/freedomui/freedomui_minios.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`, `progs/nk_palette.h`
Imported by: `tests/test_freedomui.c`
- `net_dns_resolve` (function) `progs/freedomui/freedomui_minios.c:44` `int net_dns_resolve(const char *host);`
- `tls_handshake` (function) `progs/freedomui/freedomui_minios.c:45` `int tls_handshake(int fd, char *host);`
- `tls_send` (function) `progs/freedomui/freedomui_minios.c:46` `int tls_send(int fd, char *buf, int len);`
- `tls_recv` (function) `progs/freedomui/freedomui_minios.c:47` `int tls_recv(int fd, char *buf, int len);`
- `tls_close` (function) `progs/freedomui/freedomui_minios.c:48` `void tls_close(int fd);`
- `freedomui_default` (function) `progs/freedomui/freedomui_minios.c:97` `static FreedomUiConfig freedomui_default(void)` -- long path_max; long url_max; long hops_max; long font_w; long font_h; long port_http; long port_https; long ink_bg...
- `freedomui_build_palette` (function) `progs/freedomui/freedomui_minios.c:130` `static long freedomui_build_palette(unsigned char *pal, long cap)` -- Shared hybrid palette, one table for every NK-window app (progs/nk_palette.h); this wrapper keeps the historic name...
- `freedomui_engine_text` (function) `progs/freedomui/freedomui_minios.c:145` `static long freedomui_engine_text(char *body, long n, char **title, char **text)` -- Parse a fetched body through the real engine into owned title and text.
- `freedomui_sys_present` (function) `progs/freedomui/freedomui_minios.c:193` `static long freedomui_sys_present(long buf, long origin)` -- static char f_path[FUI_PATH_MAX]; static char f_loc[FUI_URL_MAX]; static char f_hdr[FUI_HDR_MAX]; static char...
- `freedomui_sys_title` (function) `progs/freedomui/freedomui_minios.c:200` `static long freedomui_sys_title(char *t)` -- static long f_nbytes; static long f_secure; static long f_port; static long f_status; static long f_truncated; /**...
- `freedomui_sys_palette` (function) `progs/freedomui/freedomui_minios.c:207` `static long freedomui_sys_palette(unsigned char *pal)` -- static long freedomui_sys_present(long buf, long origin) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedomui_sys_mouse` (function) `progs/freedomui/freedomui_minios.c:214` `static long freedomui_sys_mouse(long *m)` -- static long freedomui_sys_title(char *t) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedomui_sys_kbd` (function) `progs/freedomui/freedomui_minios.c:221` `static long freedomui_sys_kbd(void)` -- static long freedomui_sys_palette(unsigned char *pal) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `freedomui_sys_vga_mode` (function) `progs/freedomui/freedomui_minios.c:228` `static long freedomui_sys_vga_mode(long on)` -- static long freedomui_sys_mouse(long *m) { long ret; __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_MOUSE)...
- `freedomui_sys_kbd_raw` (function) `progs/freedomui/freedomui_minios.c:235` `static long freedomui_sys_kbd_raw(long on)` -- static long freedomui_sys_kbd(void) { long ret; __asm__ volatile("syscall" : "=a"(ret) : "a"(MINIOS_SYS_KBD), "D"(0)...
- `freedomui_sys_yield` (function) `progs/freedomui/freedomui_minios.c:242` `static long freedomui_sys_yield(void)` -- static long freedomui_sys_vga_mode(long on) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `fui_append` (function) `progs/freedomui/freedomui_minios.c:249` `static long fui_append(char *dst, long pos, char *src, long cap)` -- static long freedomui_sys_kbd_raw(long on) { long ret; __asm__ volatile("syscall" : "=a"(ret)...
- `fui_strlen` (function) `progs/freedomui/freedomui_minios.c:267` `static long fui_strlen(char *s, long cap)` -- } i = 0L; while (src[i] != 0) { if (pos + i + 1L >= cap) { return -1L; } dst[pos + i] = src[i]; i++; } dst[pos + i]...
- `fui_split_url` (function) `progs/freedomui/freedomui_minios.c:283` `static long fui_split_url(FreedomUiConfig *c, char *url, char *host, char *path, long *port, long...` -- if (!s || cap <= 0L) { return -1L; } i = 0L; while (i < cap && s[i] != 0) { i++; } if (i >= cap) { return -1L; }...
- `fui_parse_headers` (function) `progs/freedomui/freedomui_minios.c:352` `static long fui_parse_headers(FreedomUiConfig *c, char *hdr, long *status, long *clen, long *hasc...` -- return 0L; } path[k] = p[hl + k]; k++; } path[k] = 0; } else { path[0] = '/'; path[1] = 0; } return 1L; } /** Parse...
- `fui_fetch_raw` (function) `progs/freedomui/freedomui_minios.c:470` `static long fui_fetch_raw(FreedomUiConfig *c, char *host, char *path, long port, long secure)` -- } k++; } } } line++; while (hdr[i] == '\r' || hdr[i] == '\n') { i++; } } return 0L; } /** Fetch one response body...
- `fui_render` (function) `progs/freedomui/freedomui_minios.c:698` `static long fui_render(FreedomUiConfig *c, size_t off)` -- if (got < c->body_cap) { f_body[got] = (char)ch; got++; } else { f_truncated = 1L; } } } } tls_close((int)fd)...
- `fui_browse` (function) `progs/freedomui/freedomui_minios.c:817` `static long fui_browse(FreedomUiConfig *c)` -- long ink; if (bits & (0x80 >> px)) { ink = c->bar_fg; } else { ink = c->bar_bg; } fb[((size_t)c->text_rows *...
- `freedomui_selftest` (function) `progs/freedomui/freedomui_minios.c:896` `static long freedomui_selftest(void)` -- } off = ui_clamp_scroll((size_t)want, f_lay.count, (size_t)c->text_rows); changed = 1L; } if (changed) { if...
- `freedomui_host_probe` (function) `progs/freedomui/freedomui_minios.c:984` `static long freedomui_host_probe(FreedomUiConfig *c)` -- return 1L; } if (freedomui_sys_kbd() > 0x7FFFFFFFL) { printf("freedomui: kbd out of range\n"); return 1L; }...
- `freedomui_host_entry` (function) `progs/freedomui/freedomui_minios.c:1067` `int freedomui_host_entry(FreedomUiConfig *c)` -- if (title) { hp_free(title); } return -1L; } ui_layout_free(&lay); hp_free(text); if (title) { hp_free(title); }...
- `main` (function) `progs/freedomui/freedomui_minios.c:1072` `int main(int argc, char **argv)` -- ui_layout_free(&lay); hp_free(text); if (title) { hp_free(title); } return 0L; } /** Host harness entry for pure...

## progs/lisp/lisp.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`
- `numbers` (function) `progs/lisp/lisp.c:9` `* * Language surface: numbers (int64), strings, symbols, cons cells, closures * with lexical scope, and the special...`
- `lisp_version` (function) `progs/lisp/lisp.c:62` `static const char *lisp_version(void)` -- Version string printed by --version and the REPL banner.
- `msys` (function) `progs/lisp/lisp.c:205` `static long msys(long n, long a1, long a2, long a3)` -- Raw 3-argument syscall through the x86-64 Linux ABI.
- `msys5` (function) `progs/lisp/lisp.c:218` `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)` -- Raw 5-argument syscall for SYS_SPAWN with path, redirect, argc, argv.
- `fatal` (function) `progs/lisp/lisp.c:233` `static void fatal(Runtime *rt, const char *message)` -- Report a fatal internal failure and terminate the process.
- `xalloc` (function) `progs/lisp/lisp.c:242` `static void *xalloc(Runtime *rt, size_t size)` -- Allocate zeroed tracked memory that frees with the runtime.
- `xstrdup` (function) `progs/lisp/lisp.c:266` `static char *xstrdup(Runtime *rt, const char *source)` -- Duplicate a string into tracked memory.
- `make_node` (function) `progs/lisp/lisp.c:284` `static Node *make_node(Runtime *rt, NodeType type)` -- Allocate a node of the given type in tracked memory.
- `make_error` (function) `progs/lisp/lisp.c:293` `static Node *make_error(Runtime *rt, const char *message)` -- Build an error value carrying a diagnostic message.
- `make_num` (function) `progs/lisp/lisp.c:302` `static Node *make_num(Runtime *rt, int64_t value)` -- Build a numeric value node.
- `make_str` (function) `progs/lisp/lisp.c:311` `static Node *make_str(Runtime *rt, const char *value)` -- Build a string value node from a NUL-terminated source.
- `make_sym` (function) `progs/lisp/lisp.c:320` `static Node *make_sym(Runtime *rt, const char *value)` -- Build a symbol value node from a NUL-terminated name.
- `make_prim` (function) `progs/lisp/lisp.c:329` `static Node *make_prim(Runtime *rt, PrimFn function)` -- Build a primitive function value node.
- `cons` (function) `progs/lisp/lisp.c:338` `static Node *cons(Runtime *rt, Node *car, Node *cdr)` -- Build a cons cell from two values.
- `is_nil` (function) `progs/lisp/lisp.c:348` `static bool is_nil(Runtime *rt, const Node *node)` -- Test whether a node is the empty list in any of its spellings.
- `make_file` (function) `progs/lisp/lisp.c:355` `static Node *make_file(Runtime *rt, FILE *handle)` -- Register an open FILE handle and wrap it in a file value node.
- `cleanup` (function) `progs/lisp/lisp.c:377` `static void cleanup(Runtime *rt)` -- Close every tracked file and release every tracked allocation.
- `runtime_init` (function) `progs/lisp/lisp.c:399` `static void runtime_init(Runtime *rt)` -- Initialize a runtime with streams, constants and empty tables.
- `env_new` (function) `progs/lisp/lisp.c:411` `static Env *env_new(Runtime *rt, Env *parent)` -- Allocate a new environment frame with an optional parent.
- `env_bind` (function) `progs/lisp/lisp.c:421` `static void env_bind(Runtime *rt, Env *env, Node *symbol, Node *value)` -- Bind a symbol to a value in the innermost frame.
- `env_set` (function) `progs/lisp/lisp.c:432` `static bool env_set(Env *env, Node *symbol, Node *value)` -- Update the nearest visible binding of a symbol.
- `env_lookup` (function) `progs/lisp/lisp.c:454` `static Node *env_lookup(Env *env, Node *symbol)` -- Resolve the nearest visible binding of a symbol.
- `reader_peek` (function) `progs/lisp/lisp.c:475` `static char reader_peek(const Reader *reader)` -- Peek at the current reader character without consuming it.
- `reader_next` (function) `progs/lisp/lisp.c:482` `static char reader_next(Reader *reader)` -- Consume one reader character and track line and column.
- `reader_at_end` (function) `progs/lisp/lisp.c:500` `static bool reader_at_end(const Reader *reader)` -- Test whether the reader reached the end of its buffer.
- `skip_space_and_comments` (function) `progs/lisp/lisp.c:507` `static void skip_space_and_comments(Reader *reader)` -- Skip whitespace and line comments starting with a semicolon.
- `sb_init` (function) `progs/lisp/lisp.c:523` `static void sb_init(StringBuilder *builder)` -- Initialize a string builder with a bounded initial capacity.
- `sb_push` (function) `progs/lisp/lisp.c:536` `static void sb_push(StringBuilder *builder, char value)` -- Append one byte to a string builder with overflow-checked growth.
- `parse_ok` (function) `progs/lisp/lisp.c:562` `static ParseResult parse_ok(Node *value)` -- Build a successful parse result.
- `parse_eof` (function) `progs/lisp/lisp.c:573` `static ParseResult parse_eof(void)` -- Build an end-of-input parse result.
- `parse_error` (function) `progs/lisp/lisp.c:584` `static ParseResult parse_error(const char *message)` -- Build a parse error result with a bounded message.
- `read_list` (function) `progs/lisp/lisp.c:596` `static ParseResult read_list(Runtime *rt, Reader *reader)` -- Read a parenthesized list terminated by a closing paren.
- `read_string` (function) `progs/lisp/lisp.c:626` `static ParseResult read_string(Runtime *rt, Reader *reader)` -- Read a double-quoted string with backslash escapes.
- `token_delimiter` (function) `progs/lisp/lisp.c:677` `static bool token_delimiter(char c)` -- Test whether a character terminates an atom token.
- `read_atom` (function) `progs/lisp/lisp.c:685` `static ParseResult read_atom(Runtime *rt, Reader *reader)` -- Read a number, nil, t or symbol token.
- `read_expr` (function) `progs/lisp/lisp.c:721` `static ParseResult read_expr(Runtime *rt, Reader *reader)` -- Read one expression, skipping whitespace and comments first.
- `list_count` (function) `progs/lisp/lisp.c:750` `static size_t list_count(Runtime *rt, Node *list, bool *proper)` -- Count proper list elements and report whether the spine is proper.
- `has_arity` (function) `progs/lisp/lisp.c:767` `static bool has_arity(Runtime *rt, Node *args, size_t expected)` -- Test whether an argument list has exactly the expected length.
- `arg_at` (function) `progs/lisp/lisp.c:775` `static Node *arg_at(Runtime *rt, Node *args, size_t index)` -- Fetch the positional argument at an index or NULL when absent.
- `arg_matches` (function) `progs/lisp/lisp.c:815` `static bool arg_matches(const Node *value, ArgKind kind)` -- Test whether an already-fetched argument matches one ArgKind.
- `check_args` (function) `progs/lisp/lisp.c:841` `static bool check_args(Runtime *rt, Node *args, const ArgKind *kinds,
    size_t n, Node **out)` -- Validate that args is a proper list of exactly n elements whose types match kinds[0..n), writing each fetched...
- `arity0` (function) `progs/lisp/lisp.c:861` `static bool arity0(Runtime *rt, Node *args)` -- Validate that args is the empty argument list.
- `prim_add` (function) `progs/lisp/lisp.c:869` `static Node *prim_add(Runtime *rt, Node *args)` -- Add two numbers with overflow reported as an error value.
- `prim_sub` (function) `progs/lisp/lisp.c:885` `static Node *prim_sub(Runtime *rt, Node *args)` -- Subtract two numbers with overflow reported as an error value.
- `prim_mul` (function) `progs/lisp/lisp.c:901` `static Node *prim_mul(Runtime *rt, Node *args)` -- Multiply two numbers with overflow reported as an error value.
- `prim_div` (function) `progs/lisp/lisp.c:917` `static Node *prim_div(Runtime *rt, Node *args)` -- Divide two numbers with zero and overflow reported as errors.
- `prim_eq` (function) `progs/lisp/lisp.c:939` `static Node *prim_eq(Runtime *rt, Node *args)` -- Compare two numbers for equality.
- `prim_lt` (function) `progs/lisp/lisp.c:951` `static Node *prim_lt(Runtime *rt, Node *args)` -- Compare two numbers with less-than.
- `prim_car` (function) `progs/lisp/lisp.c:963` `static Node *prim_car(Runtime *rt, Node *args)` -- Return the first element of a cons cell or nil.
- `prim_cdr` (function) `progs/lisp/lisp.c:975` `static Node *prim_cdr(Runtime *rt, Node *args)` -- Return the rest of a cons cell or nil.
- `prim_cons` (function) `progs/lisp/lisp.c:987` `static Node *prim_cons(Runtime *rt, Node *args)` -- Build a cons cell from two values.
- `prim_string_concat` (function) `progs/lisp/lisp.c:999` `static Node *prim_string_concat(Runtime *rt, Node *args)` -- Concatenate two strings with an overflow-checked allocation.
- `prim_string_eq` (function) `progs/lisp/lisp.c:1026` `static Node *prim_string_eq(Runtime *rt, Node *args)` -- Compare two strings for equality.
- `prim_string_length` (function) `progs/lisp/lisp.c:1038` `static Node *prim_string_length(Runtime *rt, Node *args)` -- Return the byte length of a string.
- `prim_string_at` (function) `progs/lisp/lisp.c:1050` `static Node *prim_string_at(Runtime *rt, Node *args)` -- Return the one-character string at a byte index or nil when out of range.
- `prim_char_code` (function) `progs/lisp/lisp.c:1072` `static Node *prim_char_code(Runtime *rt, Node *args)` -- Convert between a one-character string and its byte value.
- `prim_print` (function) `progs/lisp/lisp.c:1094` `static Node *prim_print(Runtime *rt, Node *args)` -- Print a value without a trailing newline.
- `prim_println` (function) `progs/lisp/lisp.c:1108` `static Node *prim_println(Runtime *rt, Node *args)` -- Print a value with a trailing newline.
- `file_mode_allowed` (function) `progs/lisp/lisp.c:1123` `static bool file_mode_allowed(const char *mode)` -- Test whether a file mode string belongs to the safe whitelist.
- `prim_read_char` (function) `progs/lisp/lisp.c:1183` `static Node *prim_read_char(Runtime *rt, Node *args)` -- Read one byte from a file or nil at end of file.
- `prim_write` (function) `progs/lisp/lisp.c:1200` `static Node *prim_write(Runtime *rt, Node *args)` -- Write a string or byte value to an open file.
- `prim_close_file` (function) `progs/lisp/lisp.c:1224` `static Node *prim_close_file(Runtime *rt, Node *args)` -- Close an open file and release its runtime slot.
- `prim_null_p` (function) `progs/lisp/lisp.c:1249` `static Node *prim_null_p(Runtime *rt, Node *args)` -- Test whether a value is nil.
- `prim_number_p` (function) `progs/lisp/lisp.c:1261` `static Node *prim_number_p(Runtime *rt, Node *args)` -- Test whether a value is a number.
- `prim_string_p` (function) `progs/lisp/lisp.c:1273` `static Node *prim_string_p(Runtime *rt, Node *args)` -- Test whether a value is a string.
- `prim_error_message` (function) `progs/lisp/lisp.c:1285` `static Node *prim_error_message(Runtime *rt, Node *args)` -- Return the message of an error value or nil for other values.
- `arity` (function) `progs/lisp/lisp.c:1300` `* * Variable arity (0 or 1);`
- `prim_exit` (function) `progs/lisp/lisp.c:1303` `static Node *prim_exit(Runtime *rt, Node *args)` -- Terminate the process with a numeric exit status.
- `prim_time_ms` (function) `progs/lisp/lisp.c:1330` `static Node *prim_time_ms(Runtime *rt, Node *args)` -- Return milliseconds since boot through the kernel time service.
- `prim_rtc` (function) `progs/lisp/lisp.c:1340` `static Node *prim_rtc(Runtime *rt, Node *args)` -- Return the clock time as a three-element list or nil when unavailable.
- `prim_fb_info` (function) `progs/lisp/lisp.c:1357` `static Node *prim_fb_info(Runtime *rt, Node *args)` -- Return framebuffer width, height and pitch or nil when unavailable.
- `prim_vol` (function) `progs/lisp/lisp.c:1377` `static Node *prim_vol(Runtime *rt, Node *args)` -- Read or set the speaker volume, clamped to the valid range.
- `prim_pal` (function) `progs/lisp/lisp.c:1405` `static Node *prim_pal(Runtime *rt, Node *args)` -- Load a 768-byte VGA palette from a string value.
- `prim_pcspeaker` (function) `progs/lisp/lisp.c:1421` `static Node *prim_pcspeaker(Runtime *rt, Node *args)` -- Play a speaker tone for a bounded millisecond duration.
- `prim_minios_run` (function) `progs/lisp/lisp.c:1465` `static Node *prim_minios_run(Runtime *rt, Node *args)` -- Run a program through SYS_SPAWN and return its exit code.
- `eval_list` (function) `progs/lisp/lisp.c:1527` `static Node *eval_list(Runtime *rt, Node *list, Env *env)` -- Evaluate every element of a list into a fresh proper list.
- `eval_sequence` (function) `progs/lisp/lisp.c:1551` `static Node *eval_sequence(Runtime *rt, Node *body, Env *env)` -- Evaluate a body sequence and return the last value.
- `valid_params` (function) `progs/lisp/lisp.c:1569` `static bool valid_params(Runtime *rt, Node *params)` -- Test whether a parameter list holds only symbols.
- `eval` (function) `progs/lisp/lisp.c:1583` `static Node *eval(Runtime *rt, Node *expression, Env *env)` -- Evaluate an expression with tail-call reuse and a bounded depth.
- `print_escaped_string` (function) `progs/lisp/lisp.c:1846` `static void print_escaped_string(FILE *out, const char *value)` -- Write a string with escape sequences for readable output.
- `print_node` (function) `progs/lisp/lisp.c:1877` `static void print_node(Runtime *rt, Node *node, bool readable)` -- Print a value in readable or display form with a bounded depth.
- `bind_primitive` (function) `progs/lisp/lisp.c:1948` `static void bind_primitive(Runtime *rt, Env *env, const char *name,
    PrimFn function)` -- Register one named primitive in an environment frame.
- `init_env` (function) `progs/lisp/lisp.c:2004` `static Env *init_env(Runtime *rt)` -- Build the global environment with arithmetic, strings, files and MiniOS.
- `bind_argv` (function) `progs/lisp/lisp.c:2017` `static void bind_argv(Runtime *rt, Env *env, int argc, char **argv, int first)` -- Expose the script argument vector as a proper list of strings.
- `read_all_file` (function) `progs/lisp/lisp.c:2029` `static char *read_all_file(const char *filename, size_t max_bytes)` -- Read a whole file into memory with a hard size cap.
- `process_source` (function) `progs/lisp/lisp.c:2087` `static int process_source(Runtime *rt, const char *source,
    const char *source_name, bool echo)` -- Evaluate every form in a source buffer and report the first failure.
- `process_inline` (function) `progs/lisp/lisp.c:2129` `static int process_inline(Runtime *rt, const char *code)` -- Evaluate one inline expression from the -e flag.
- `print_usage` (function) `progs/lisp/lisp.c:2136` `static void print_usage(Runtime *rt)` -- Print usage for the command line interface.
- `repl` (function) `progs/lisp/lisp.c:2143` `static int repl(Runtime *rt)` -- Run the interactive read-eval loop on the runtime input stream.
- `main` (function) `progs/lisp/lisp.c:2190` `int main(int argc, char **argv)` -- Entry point with -e, script and REPL modes plus bounded arguments.

## progs/lisp/tin.c
- `main` (function) `progs/lisp/tin.c:1` `int main()`

## progs/lua/lua_main.c
Depends on: `kernel/string.c`
- `module` (function) `progs/lua/lua_main.c:5` `* C module (minios.c) can be registered globally before any script runs: * `minios.run(...)`, `minios.time_ms()`...`
- `luaL_require_global` (function) `progs/lua/lua_main.c:22` `static void luaL_require_global(lua_State *L, const char *name,
                                l...`
- `set_arg_table` (function) `progs/lua/lua_main.c:28` `static void set_arg_table(lua_State *L, int argc, char **argv, int first)`
- `docode` (function) `progs/lua/lua_main.c:41` `static int docode(lua_State *L, const char *code)`
- `dofile` (function) `progs/lua/lua_main.c:51` `static int dofile(lua_State *L, const char *name)`
- `repl` (function) `progs/lua/lua_main.c:61` `static int repl(lua_State *L)`
- `main` (function) `progs/lua/lua_main.c:105` `int main(int argc, char **argv)`

## progs/lua/minios.c
Depends on: `progs/minios_abi.h`
Imported by: `progs/micropython/variants/minios/lib/hello.py`, `progs/src/shell.py`, `progs/src/test.py`
- `msys5` (function) `progs/lua/minios.c:37` `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)` -- /* ── raw syscall helpers (x86-64 Linux ABI) ─────────────────────────── static long msys(long n, long a1, long a2...
- `minios_time_ms` (function) `progs/lua/minios.c:62` `static int minios_time_ms(lua_State *L)` -- } /* ── MiniOS syscall numbers (canonical table from minios_abi.h) ─────── #include "minios_abi.h" #define...
- `minios_rtc` (function) `progs/lua/minios.c:68` `static int minios_rtc(lua_State *L)` -- #define SYS_PCSPK_INIT  MINIOS_SYS_PCSPK_INIT #define SYS_PCSPK_TONE  MINIOS_SYS_PCSPK_TONE #define SYS_RTC...
- `minios_fb_info` (function) `progs/lua/minios.c:82` `static int minios_fb_info(lua_State *L)` -- static int minios_rtc(lua_State *L) { int h, m, s; if (msys(SYS_RTC, (long)&h, (long)&m, (long)&s) < 0) {...
- `minios_vol` (function) `progs/lua/minios.c:96` `static int minios_vol(lua_State *L)` -- static int minios_fb_info(lua_State *L) { int w, h, p; if (msys(SYS_FB_INFO, (long)&w, (long)&h, (long)&p) < 0) {...
- `minios_pal` (function) `progs/lua/minios.c:109` `static int minios_pal(lua_State *L)` -- /* ── minios.vol([v]) -> current volume ─────────────────────────────── static int minios_vol(lua_State *L) { if...
- `minios_pcspeaker` (function) `progs/lua/minios.c:119` `static int minios_pcspeaker(lua_State *L)` -- return 1; } /* ── minios.pal(buf) -- load a 768-byte VGA DAC palette ────────────── static int minios_pal(lua_State...
- `minios_run` (function) `progs/lua/minios.c:136` `static int minios_run(lua_State *L)` -- ── minios.run(path[, args][, redirect]) -> exit code ─────────────── Runs a program through SYS_SPAWN (215)...
- `luaopen_minios` (function) `progs/lua/minios.c:192` `int luaopen_minios(lua_State *L)`

## progs/micropython/variants/minios/minios_module.c
Depends on: `progs/minios_abi.h`
- `msys5` (function) `progs/micropython/variants/minios/minios_module.c:26` `static long msys5(long n, long a1, long a2, long a3, long a4, long a5)` -- /* ── raw syscall helper (x86-64 Linux ABI) ─────────────────────────── static long msys(long n, long a1, long a2...
- `minios_time_ms` (function) `progs/micropython/variants/minios/minios_module.c:52` `static mp_obj_t minios_time_ms(void)`
- `MP_DEFINE_CONST_FUN_OBJ_0` (function) `progs/micropython/variants/minios/minios_module.c:55` `static MP_DEFINE_CONST_FUN_OBJ_0(minios_time_ms_obj, minios_time_ms);`
- `minios_rtc` (function) `progs/micropython/variants/minios/minios_module.c:59` `static mp_obj_t minios_rtc(void)`
- `minios_fb_info` (function) `progs/micropython/variants/minios/minios_module.c:76` `static mp_obj_t minios_fb_info(void)`
- `MP_DEFINE_CONST_FUN_OBJ_VAR` (function) `progs/micropython/variants/minios/minios_module.c:107` `static MP_DEFINE_CONST_FUN_OBJ_VAR(minios_vol_obj, 0, minios_vol);`
- `minios_pal` (function) `progs/micropython/variants/minios/minios_module.c:111` `static mp_obj_t minios_pal(mp_obj_t buf_in)`
- `MP_DEFINE_CONST_FUN_OBJ_1` (function) `progs/micropython/variants/minios/minios_module.c:123` `static MP_DEFINE_CONST_FUN_OBJ_1(minios_pal_obj, minios_pal);`
- `minios_pcspeaker` (function) `progs/micropython/variants/minios/minios_module.c:127` `static mp_obj_t minios_pcspeaker(mp_obj_t freq_in, mp_obj_t ms_in)`
- `MP_DEFINE_CONST_FUN_OBJ_2` (function) `progs/micropython/variants/minios/minios_module.c:140` `static MP_DEFINE_CONST_FUN_OBJ_2(minios_pcspeaker_obj, minios_pcspeaker);`
- `minios_run` (function) `progs/micropython/variants/minios/minios_module.c:149` `static mp_obj_t minios_run(size_t n_args, const mp_obj_t *pos_args, mp_map_t *kw_args)`
- `MP_DEFINE_CONST_FUN_OBJ_KW` (function) `progs/micropython/variants/minios/minios_module.c:193` `static MP_DEFINE_CONST_FUN_OBJ_KW(minios_run_obj, 1, minios_run);`
- `MP_DEFINE_CONST_DICT` (function) `progs/micropython/variants/minios/minios_module.c:207` `static MP_DEFINE_CONST_DICT(minios_module_globals, minios_module_globals_table);`

## progs/minicraft/minicraft.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`
- `best_tool_for` (function) `progs/minicraft/minicraft.c:231` `static int best_tool_for(unsigned char b)`
- `break_time_ms` (function) `progs/minicraft/minicraft.c:250` `static long break_time_ms(unsigned char b, int tool)`
- `break_beep_for` (function) `progs/minicraft/minicraft.c:275` `static long break_beep_for(unsigned char b)`
- `mc_toggle_zoom` (function) `progs/minicraft/minicraft.c:316` `static void mc_toggle_zoom(void)`
- `save_world` (function) `progs/minicraft/minicraft.c:330` `static int save_world(void);`
- `s_time_ms` (function) `progs/minicraft/minicraft.c:337` `static long s_time_ms(void)`
- `s_kbd` (function) `progs/minicraft/minicraft.c:342` `static long s_kbd(void)`
- `s_kbd_raw` (function) `progs/minicraft/minicraft.c:347` `static long s_kbd_raw(long on)`
- `s_getc_raw` (function) `progs/minicraft/minicraft.c:359` `static long s_getc_raw(void)` -- Serial fallback for menus: SYS_KBD in raw mode carries PS/2 only, so a serial console can never drive a scancode...
- `ser_get` (function) `progs/minicraft/minicraft.c:373` `static long ser_get(void)`
- `ser_unget` (function) `progs/minicraft/minicraft.c:386` `static void ser_unget(unsigned char b)`
- `menu_ser_key` (function) `progs/minicraft/minicraft.c:391` `static long menu_ser_key(long b)`
- `kbd_drain` (function) `progs/minicraft/minicraft.c:428` `static void kbd_drain(void)` -- Drain stale scancodes (typematic repeats, a release that arrived with * its press) before leaving a menu, so they...
- `s_vga` (function) `progs/minicraft/minicraft.c:433` `static long s_vga(long on)`
- `s_pal` (function) `progs/minicraft/minicraft.c:438` `static long s_pal(const unsigned char *p)`
- `s_present` (function) `progs/minicraft/minicraft.c:443` `static long s_present(void)`
- `s_title` (function) `progs/minicraft/minicraft.c:448` `static long s_title(const char *t)`
- `s_mouse` (function) `progs/minicraft/minicraft.c:453` `static long s_mouse(int *m)`
- `s_zoom` (function) `progs/minicraft/minicraft.c:458` `static long s_zoom(long on)`
- `s_yield` (function) `progs/minicraft/minicraft.c:463` `static void s_yield(void)`
- `s_pcspk_init` (function) `progs/minicraft/minicraft.c:468` `static long s_pcspk_init(void)`
- `beep` (function) `progs/minicraft/minicraft.c:478` `static void beep(long freq, long dur_ms)`
- `pal_set` (function) `progs/minicraft/minicraft.c:497` `static void pal_set(int i, int r, int g, int b)`
- `build_palette` (function) `progs/minicraft/minicraft.c:503` `static void build_palette(void)`
- `in_world` (function) `progs/minicraft/minicraft.c:562` `static int in_world(int x, int y, int z)`
- `chunk_of` (function) `progs/minicraft/minicraft.c:577` `static int chunk_of(int v)` -- (void)x; (void)y; return z >= 0 && z < MC_H; } static unsigned int hash2(int x, int y); static unsigned int...
- `chunk_local` (function) `progs/minicraft/minicraft.c:581` `static int chunk_local(int v)`
- `chunk_lidx` (function) `progs/minicraft/minicraft.c:586` `static int chunk_lidx(int lx, int ly, int z)`
- `chunk_find` (function) `progs/minicraft/minicraft.c:592` `static int chunk_find(int cx, int cy)` -- O(1) fast path: DDA walks neighbours, so the last chunk almost always * hits; the 49-slot scan is the rare slow...
- `world_max_recompute` (function) `progs/minicraft/minicraft.c:606` `static void world_max_recompute(void)`
- `chunk_evict_slot` (function) `progs/minicraft/minicraft.c:615` `static int chunk_evict_slot(int cx, int cy)`
- `chunk_ensure` (function) `progs/minicraft/minicraft.c:635` `static int chunk_ensure(int cx, int cy)`
- `chunk_build_meta` (function) `progs/minicraft/minicraft.c:658` `static void chunk_build_meta(int slot)`
- `col_recompute` (function) `progs/minicraft/minicraft.c:703` `static void col_recompute(int x, int y)`
- `col_top_at` (function) `progs/minicraft/minicraft.c:728` `static int col_top_at(int x, int y)`
- `light_recompute_col` (function) `progs/minicraft/minicraft.c:735` `static void light_recompute_col(int x, int y)`
- `get_b` (function) `progs/minicraft/minicraft.c:764` `static unsigned char get_b(int x, int y, int z)`
- `set_b` (function) `progs/minicraft/minicraft.c:774` `static void set_b(int x, int y, int z, unsigned char b)`
- `set_b_raw` (function) `progs/minicraft/minicraft.c:790` `static void set_b_raw(int x, int y, int z, unsigned char b)`
- `sky_light` (function) `progs/minicraft/minicraft.c:801` `static float sky_light(int x, int y, int z)` -- world_dirty = 1; } static void set_b_raw(int x, int y, int z, unsigned char b) { int s; if (z < 0 || z >= MC_H)...
- `is_solid` (function) `progs/minicraft/minicraft.c:811` `static int is_solid(unsigned char b)`
- `in_water_at` (function) `progs/minicraft/minicraft.c:814` `static int in_water_at(float x, float y, float z)`
- `is_visible` (function) `progs/minicraft/minicraft.c:819` `static int is_visible(unsigned char b)`
- `hash2` (function) `progs/minicraft/minicraft.c:823` `static unsigned int hash2(int x, int y)`
- `hash2_seed` (function) `progs/minicraft/minicraft.c:830` `static unsigned int hash2_seed(int x, int y, unsigned int seed)`
- `mc_smoothstep` (function) `progs/minicraft/minicraft.c:839` `static float mc_smoothstep(float t)`
- `biome_fdiv` (function) `progs/minicraft/minicraft.c:846` `static int biome_fdiv(int v, int c)` -- Voronoi biome lattice: floor division so negatives land right.
- `voro_site` (function) `progs/minicraft/minicraft.c:861` `static void voro_site(int cx, int cy, unsigned int seed, int cell,
    int *sx, int *sy)`
- `biome_voro` (function) `progs/minicraft/minicraft.c:869` `static int biome_voro(int x, int y, unsigned int seed, int cell,
    int ox, int oy, unsigned int...`
- `biome_desert` (function) `progs/minicraft/minicraft.c:893` `static int biome_desert(int x, int y, unsigned int seed)`
- `biome_snow` (function) `progs/minicraft/minicraft.c:897` `static int biome_snow(int x, int y, unsigned int seed)`
- `is_cave` (function) `progs/minicraft/minicraft.c:901` `static int is_cave(int x, int y, int z, unsigned int seed)`
- `ground_h_seed` (function) `progs/minicraft/minicraft.c:909` `static int ground_h_seed(int x, int y, unsigned int seed)`
- `inv_add` (function) `progs/minicraft/minicraft.c:931` `static int inv_add(int b, int n)`
- `inv_remove` (function) `progs/minicraft/minicraft.c:945` `static int inv_remove(int b, int n)`
- `decorate_column` (function) `progs/minicraft/minicraft.c:995` `static void decorate_column(int x, int y, unsigned int seed)`
- `gen_terrain_chunk` (function) `progs/minicraft/minicraft.c:1034` `static void gen_terrain_chunk(int slot)`
- `decorate_chunk` (function) `progs/minicraft/minicraft.c:1043` `static void decorate_chunk(int slot)`
- `ensure_around_px` (function) `progs/minicraft/minicraft.c:1056` `static void ensure_around_px(float px, float py)` -- Keep a (2R+1)^2 ring of terrain around the player, an inner ring decorated, drop the rest (dirty chunks hit disk first).
- `ensure_around` (function) `progs/minicraft/minicraft.c:1090` `static void ensure_around(void)`
- `new_world` (function) `progs/minicraft/minicraft.c:1095` `static void new_world(unsigned int seed)` -- save_chunk_file(i); ch_used[i] = 0; if (ch_cache == i) ch_cache = -1; } } world_max_recompute(); } static void...
- `mob_spawn_one` (function) `progs/minicraft/minicraft.c:1191` `static void mob_spawn_one(Pig *m, int id, int hp, long now)`
- `pig_collides` (function) `progs/minicraft/minicraft.c:1243` `static int pig_collides(float x, float y, float z)`
- `creeper_explode` (function) `progs/minicraft/minicraft.c:1257` `static void creeper_explode(Pig *c, long now)`
- `creep_sense` (function) `progs/minicraft/minicraft.c:1325` `static void creep_sense(Pig *c, float *pdx, float *pdy, float *pdz, float *pd3)` -- Creeper perception in 3D: planar delta, eye-height delta and full distance.
- `creep_has_los` (function) `progs/minicraft/minicraft.c:1337` `static int creep_has_los(Pig *c)` -- Voxel line of sight between creeper eyes and player eyes, sampled every half block.
- `creep_separate` (function) `progs/minicraft/minicraft.c:1361` `static void creep_separate(Pig *p, int id, float dt)` -- Herd separation: creepers inside MC_CREEP_SEP_D push apart so the pack * never stacks on one tile and every one of...
- `tick_mob` (function) `progs/minicraft/minicraft.c:1386` `static void tick_mob(Pig *p, int id, float dt, long now)`
- `tick_pigs` (function) `progs/minicraft/minicraft.c:1512` `static void tick_pigs(float dt, long now)`
- `face_color` (function) `progs/minicraft/minicraft.c:1520` `static unsigned char face_color(unsigned char b, int face)`
- `sky_color` (function) `progs/minicraft/minicraft.c:1569` `static unsigned char sky_color(float dz, float sun_dot, int x, int y, float tsec)`
- `shade_block` (function) `progs/minicraft/minicraft.c:1602` `static unsigned char shade_block(unsigned char b, int face, int bx, int by, int bz,
             ...`
- `cast_ray` (function) `progs/minicraft/minicraft.c:1659` `static RayHit cast_ray(float ox, float oy, float oz, float dx, float dy, float dz, float maxd)`
- `eye_z` (function) `progs/minicraft/minicraft.c:1750` `static float eye_z(void)`
- `mc_glyph` (function) `progs/minicraft/minicraft.c:1817` `static int mc_glyph(char ch)`
- `mc_pixel` (function) `progs/minicraft/minicraft.c:1825` `static void mc_pixel(int x, int y, unsigned char c)`
- `mc_text` (function) `progs/minicraft/minicraft.c:1831` `static void mc_text(int x, int y, const char *s, unsigned char fg)`
- `mc_text_bg` (function) `progs/minicraft/minicraft.c:1844` `static void mc_text_bg(int x, int y, const char *s, unsigned char fg, unsigned char bg)`
- `mc_block_name` (function) `progs/minicraft/minicraft.c:1857` `static const char *mc_block_name(unsigned char b)`
- `mc_facing` (function) `progs/minicraft/minicraft.c:1877` `static char mc_facing(void)`
- `cam_build` (function) `progs/minicraft/minicraft.c:1892` `static void cam_build(void)`
- `render_terrain` (function) `progs/minicraft/minicraft.c:1910` `static void render_terrain(RayHit tgt, float cyaw, float syaw, float cpit,
                      ...`
- `mob_pixel` (function) `progs/minicraft/minicraft.c:1945` `static unsigned char mob_pixel(Pig *m, int id, int px, int py, int x0, int x1, int y0, int y1)`
- `render_mob_array` (function) `progs/minicraft/minicraft.c:1979` `static void render_mob_array(Pig *arr, int n, float fx, float fy, float fz,
    float rx, float r...`
- `render_pigs` (function) `progs/minicraft/minicraft.c:2030` `static void render_pigs(float cyaw, float syaw, float cpit, float spit, float ez)`
- `render_frame` (function) `progs/minicraft/minicraft.c:2038` `static void render_frame(void)`
- `sc_hist_push` (function) `progs/minicraft/minicraft.c:2151` `static void sc_hist_push(unsigned char b)`
- `poll_kbd` (function) `progs/minicraft/minicraft.c:2162` `static void poll_kbd(void)`
- `player_collides` (function) `progs/minicraft/minicraft.c:2355` `static int player_collides(float x, float y, float z)`
- `move_x` (function) `progs/minicraft/minicraft.c:2379` `static void move_x(float nx)`
- `move_y` (function) `progs/minicraft/minicraft.c:2384` `static void move_y(float ny)`
- `move_z_abs` (function) `progs/minicraft/minicraft.c:2389` `static MoveResult move_z_abs(float nz)`
- `block_intersects_player` (function) `progs/minicraft/minicraft.c:2404` `static int block_intersects_player(int bx, int by, int bz)`
- `try_autostep` (function) `progs/minicraft/minicraft.c:2413` `static void try_autostep(float tx, float ty)`
- `hurt` (function) `progs/minicraft/minicraft.c:2424` `static void hurt(int dmg, const char *why)`
- `tick_player` (function) `progs/minicraft/minicraft.c:2449` `static void tick_player(float dt)`
- `tick_water` (function) `progs/minicraft/minicraft.c:2548` `static void tick_water(long now)`
- `tick_hunger` (function) `progs/minicraft/minicraft.c:2596` `static void tick_hunger(long now)`
- `goal_text` (function) `progs/minicraft/minicraft.c:2608` `static const char *goal_text(void)`
- `tick_goals` (function) `progs/minicraft/minicraft.c:2619` `static void tick_goals(void)`
- `tick_discover` (function) `progs/minicraft/minicraft.c:2630` `static void tick_discover(long now)`
- `tick_interact` (function) `progs/minicraft/minicraft.c:2668` `static void tick_interact(void)`
- `mc_crc32` (function) `progs/minicraft/minicraft.c:2919` `static uint32_t mc_crc32(const void *data, size_t len, uint32_t crc)`
- `save_compute_crc` (function) `progs/minicraft/minicraft.c:2932` `static uint32_t save_compute_crc(const SaveHeader *hd)`
- `chunk_path` (function) `progs/minicraft/minicraft.c:2938` `static void chunk_path(int cx, int cy, char *out, size_t n)`
- `save_chunk_file` (function) `progs/minicraft/minicraft.c:2942` `static int save_chunk_file(int slot)`
- `load_chunk_file` (function) `progs/minicraft/minicraft.c:2974` `static int load_chunk_file(int slot, int cx, int cy)`
- `save_validate_loaded` (function) `progs/minicraft/minicraft.c:3056` `static int save_validate_loaded(void)`
- `load_reset_runtime` (function) `progs/minicraft/minicraft.c:3075` `static void load_reset_runtime(void)`
- `carve_blob` (function) `progs/minicraft/minicraft.c:3108` `static void carve_blob(const unsigned char *blob)` -- Import a 64x64x32 legacy blob into chunks (0..3, 0..3), then dirty so * region files persist it.
- `load_world_legacy` (function) `progs/minicraft/minicraft.c:3137` `static int load_world_legacy(FILE *f)` -- Legacy raw save: fixed old_inv[12] layout is fragile if B_COUNT grows; * kept read-only for ancient saves, never...
- `load_apply_player` (function) `progs/minicraft/minicraft.c:3175` `static void load_apply_player(const SaveHeader *hd)`
- `load_world_v3` (function) `progs/minicraft/minicraft.c:3194` `static int load_world_v3(FILE *f, SaveHeader *hd)`
- `load_world_v2` (function) `progs/minicraft/minicraft.c:3234` `static int load_world_v2(FILE *f, SaveHeader *hd)`
- `load_world` (function) `progs/minicraft/minicraft.c:3271` `static int load_world(void)`
- `selftest` (function) `progs/minicraft/minicraft.c:3345` `static int selftest(void)`
- `census` (function) `progs/minicraft/minicraft.c:3606` `static int census(void)` -- 128x128 columns (64 biome cells): a 64-wide patch covers too few * 16-block biome cells and the desert rate...
- `dumpstats` (function) `progs/minicraft/minicraft.c:3670` `static int dumpstats(void)`
- `title_menu` (function) `progs/minicraft/minicraft.c:3754` `static int title_menu(int have_save, int *seed_io)`
- `pause_menu` (function) `progs/minicraft/minicraft.c:3922` `static int pause_menu(int *seed_io)` -- Pause menu on ESC (Alt+F4 still kills the process kernel-side): * 0 = resume, 1 = new world with *seed_io, 2 = save...
- `main` (function) `progs/minicraft/minicraft.c:4095` `int main(int argc, char **argv)`

## progs/minios_abi.h
Imported by: `headers/kernel.h`, `headers/vga_fb.h`, `progs/doomedit/doomedit.c`, `progs/doomgeneric/doomgeneric_minios.c`, `progs/doomgeneric/i_minios_sound.c`, `progs/file/file.c`, `progs/freedomui/freedomui_minios.c`, `progs/lisp/lisp.c`, `progs/lua/minios.c`, `progs/micropython/variants/minios/minios_module.c`, `progs/minicraft/minicraft.c`, `progs/nuklear/node_editor.c`, `progs/nuklear/nuklear_minios.h`, `progs/paint/paint.c`, `progs/piano/piano.c`, `progs/pokemon/platform_minios.c`, `progs/quake2generic/q2generic_minios.c`, `progs/quake2generic/snddma_minios.c`, `progs/src/audio.c`, `progs/src/fptest.c`, `progs/src/freedom_wl.c`, `progs/src/mthreads.h`, `progs/src/opl3.c`, `progs/src/sbtone.c`, `progs/src/thdemo.c`, `progs/wl/wlcomp.c`, `tests/test_abi.c`, `tests/test_wl.c`, `tools/abi_stamp.c`
- `DOOM_BACKBUF_ADDR` (function) `progs/minios_abi.h:128` `* * All three sit in the reserved tail above DOOM_BACKBUF_ADDR (the brk cap), * so a growing heap or mmap region can...`
- `in` (function) `progs/minios_abi.h:356` `* bytes in (refused past 4096, never truncated), GET copies out up to * the caller's cap (refused when empty or...`

## progs/minios_png.h
Imported by: `progs/file/file.c`, `progs/pokemon/platform_minios.c`, `tests/test_minios_png.c`
- `mpng_332_idx` (function) `progs/minios_png.h:58` `static int mpng_332_idx(unsigned r, unsigned g, unsigned b)` -- static const char *mpng_left_candidates[MPNG_LEFT_N] = { "/icons/doom.png", "/icons/doomedit.png"...
- `mpng_nearest` (function) `progs/minios_png.h:63` `static int mpng_nearest(const unsigned char *pal, long pal_n, unsigned r,
                       ...` -- "/icons/nuklear.png", "/icons/vedit.png", "/icons/file.png", "/icons/shell.png", "/icons/paint.png"...
- `mpng_center` (function) `progs/minios_png.h:84` `static int mpng_center(int outer, int inner)` -- for (k = 0; k < pal_n; k++) { long dr = (long)pal[k * 3] - (long)r; long dg = (long)pal[k * 3 + 1] - (long)g; long...
- `mpng_fit_scale` (function) `progs/minios_png.h:93` `static int mpng_fit_scale(int sw, int sh, int boxw, int boxh)` -- } return (int)best; } /** Docstring: centered offset of inner inside outer, negative when unfit. static int...
- `mpng_rgb_to_idx_scaled` (function) `progs/minios_png.h:108` `static int mpng_rgb_to_idx_scaled(const unsigned char *rgb, int sw, int sh,
                     ...` -- int s = 1; int best = 1; if (sw <= 0 || sh <= 0 || boxw <= 0 || boxh <= 0) return -1; for (s = 1; s <= boxw && s <=...
- `bound` (function) `progs/minios_png.h:140` `* its 512 source bound (pinned by the host suite), so icon and policy
 * art never grow through t...`
- `mpng_rgb_to_332_scaled` (function) `progs/minios_png.h:172` `static int mpng_rgb_to_332_scaled(const unsigned char *rgb, int sw, int sh,
                     ...` -- int sy = y * sh / dh; for (x = 0; x < dw; x++) { int sx = x * sw / dw; const unsigned char *p = rgb + (sy * sw + sx)...
- `mpng_blit_idx` (function) `progs/minios_png.h:196` `static int mpng_blit_idx(unsigned char *fb, int fw, int fh,
                         const unsign...` -- if (dw > MPNG_MAX_DIM || dh > MPNG_MAX_DIM) return MPNG_ERR_BOUND; for (y = 0; y < dh; y++) { int sy = y * sh / dh...
- `mpng_load_file` (function) `progs/minios_png.h:222` `static int mpng_load_file(const char *path, unsigned char **out, long *out_n,
                   ...` -- int dy = oy + y; if (dy < 0 || dy >= fh) continue; for (x = 0; x < tw; x++) { int dx = ox + x; if (dx < 0 || dx >=...

## progs/nk_palette.h
Imported by: `progs/freedomui/freedomui_minios.c`, `progs/nuklear/nuklear_minios.c`, `progs/src/freedom_wl.c`, `progs/wl/wlcomp.c`, `tests/test_wl.c`
- `nk_palette_build` (function) `progs/nk_palette.h:22` `static int nk_palette_build(unsigned char *pal, long cap)`

## progs/nuklear/cvm_emit.c
Depends on: `kernel/string.c`, `progs/nuklear/cvm_emit.h`
- `module` (function) `progs/nuklear/cvm_emit.c:3` `* * Emits a cvm2 module (format v2) from a dataflow graph. Nodes are * topologically sorted (a true DAG order, so...`
- `code` (function) `progs/nuklear/cvm_emit.c:8` `* exit code (OP_HALT leaves the operand-stack top as the exit status, which
 * the shell reports ...`
- `cb_push` (function) `progs/nuklear/cvm_emit.c:79` `static int cb_push(struct codebuf *cb, unsigned char c)`
- `cb_u32` (function) `progs/nuklear/cvm_emit.c:91` `static int cb_u32(struct codebuf *cb, unsigned long v)`
- `cb_i64` (function) `progs/nuklear/cvm_emit.c:97` `static int cb_i64(struct codebuf *cb, long long v)`
- `cb_patch_u32` (function) `progs/nuklear/cvm_emit.c:103` `static void cb_patch_u32(struct codebuf *cb, size_t pos, unsigned long v)`
- `cb_imm` (function) `progs/nuklear/cvm_emit.c:111` `static int cb_imm(struct codebuf *cb, long long v)` -- static int cb_i64(struct codebuf *cb, long long v) { for (int i = 0; i < 8; i++) if (cb_push(cb, (unsigned char)(v...
- `req_inputs` (function) `progs/nuklear/cvm_emit.c:126` `static int req_inputs(enum cvm_node_type t)` -- if (v >= -128 && v <= 127) { if (cb_push(cb, OP_PUSH_IMM8) < 0) return -1; if (cb_push(cb, (unsigned char)(v &...
- `is_sink` (function) `progs/nuklear/cvm_emit.c:145` `static int is_sink(enum cvm_node_type t)`
- `topo_sort` (function) `progs/nuklear/cvm_emit.c:150` `static int topo_sort(const struct cvm_node *nodes, int n,
                     int *order, char *...` -- case NODE_EXIT: return 1; case NODE_IF: return 3; default: return 2; } } static int is_sink(enum cvm_node_type t) {...
- `emit_operand` (function) `progs/nuklear/cvm_emit.c:213` `static int emit_operand(struct codebuf *code, const struct cvm_node *nodes,
                     ...` -- Emit one operand: the wired local slot or the fallback literal.
- `emit_jz` (function) `progs/nuklear/cvm_emit.c:224` `static int emit_jz(struct codebuf *code, size_t *rel_pos)`
- `emit_jmp` (function) `progs/nuklear/cvm_emit.c:230` `static int emit_jmp(struct codebuf *code, size_t *rel_pos)`
- `cvm_compile` (function) `progs/nuklear/cvm_emit.c:236` `int cvm_compile(const struct cvm_node *nodes, int n,
                unsigned char **out, size_t ...`
- `w32` (function) `progs/nuklear/cvm_emit.c:491` `void w32(void *p, unsigned v)` -- size_t ft = (size_t)nf * CVM_FUNC_ENTRY_SIZE; size_t gt = (size_t)ng * CVM_GLOBAL_ENTRY_SIZE; size_t nt = (size_t)nn...

## progs/nuklear/cvm_emit.h
Imported by: `progs/nuklear/cvm_emit.c`, `progs/nuklear/node_editor.c`
- `graph` (function) `progs/nuklear/cvm_emit.h:6` `* * A node graph (constants, arithmetic, bitwise, comparisons, a conditional * select, and string constants feeding...`
- `err` (function) `progs/nuklear/cvm_emit.h:67` `* err (err_cap bytes). The module is heap-allocated and owned by the caller * (free it). */ int cvm_compile(const...`

## progs/nuklear/node_editor.c
Depends on: `kernel/string.c`, `progs/minios_abi.h`, `progs/nuklear/cvm_emit.h`, `progs/nuklear/nuklear_minios.h`, `progs/nuklear/nuklear_theme.h`
- `node_inputs` (function) `progs/nuklear/node_editor.c:96` `static int node_inputs(int k)`
- `node_outputs` (function) `progs/nuklear/node_editor.c:101` `static int node_outputs(int k)`
- `kind_name` (function) `progs/nuklear/node_editor.c:106` `static const char *kind_name(int k)`
- `kind_color` (function) `progs/nuklear/node_editor.c:111` `static struct nk_color kind_color(int k)`
- `graph_clear` (function) `progs/nuklear/node_editor.c:116` `static void graph_clear(void)`
- `graph_add` (function) `progs/nuklear/node_editor.c:122` `static int graph_add(int kind)`
- `graph_del` (function) `progs/nuklear/node_editor.c:136` `static void graph_del(int idx)`
- `graph_to_compiler` (function) `progs/nuklear/node_editor.c:154` `static int graph_to_compiler(struct cvm_node *out, int cap)` -- g_count--; for (int i = 0; i < g_count; i++) for (int k = 0; k < 3; k++) { if (g_nodes[i].in[k] == idx) {...
- `repair_graph` (function) `progs/nuklear/node_editor.c:176` `static int repair_graph(char *rep, size_t repcap, char *herr, size_t herrcap,
                   ...` -- Pre-compile pass: repair every open data input with a const 0 fallback (an open PrStr prints an empty line), so...
- `addrep` (function) `progs/nuklear/node_editor.c:183` `void addrep(const char *s)`
- `adderr` (function) `progs/nuklear/node_editor.c:193` `void adderr(const char *s)`
- `compile_to` (function) `progs/nuklear/node_editor.c:283` `static int compile_to(const char *path)` -- Compile the current graph to a file.
- `write_quoted` (function) `progs/nuklear/node_editor.c:339` `static void write_quoted(FILE *f, const char *s)` -- --- Headless graph text format (v2, backward compatible) ---- num a 5          str s "hi"       add b a c      add c...
- `save_graph_file` (function) `progs/nuklear/node_editor.c:392` `static int save_graph_file(const char *path)`
- `parse_graph_file` (function) `progs/nuklear/node_editor.c:430` `static int parse_graph_file(const char *path)`
- `resolve` (function) `progs/nuklear/node_editor.c:437` `int resolve(const char *nme, int upto)`
- `parse_input` (function) `progs/nuklear/node_editor.c:443` `int parse_input(const char *tok, int idx, int k)` -- static int parse_graph_file(const char *path) { FILE *f = fopen(path, "r"); if (!f) return -1; graph_clear(); static...
- `pin_y` (function) `progs/nuklear/node_editor.c:522` `static float pin_y(struct gnode *n, int slot, int is_output)` -- /* Link-drag state: click an output pin, drag to an input pin. static int linking_active; static int...
- `node_h` (function) `progs/nuklear/node_editor.c:534` `static float node_h(struct gnode *n)`
- `ui_inspector` (function) `progs/nuklear/node_editor.c:542` `static void ui_inspector(struct nk_context *ctx)`
- `ui_build` (function) `progs/nuklear/node_editor.c:622` `static void ui_build(struct nk_context *ctx, float win_w, float win_h)`
- `gui_run` (function) `progs/nuklear/node_editor.c:931` `static void gui_run(void)` -- circle.y = pin_y(n, k, 0) - PIN_R + oy; circle.w = PIN_DIAM; circle.h = PIN_DIAM; nk_fill_circle(canvas, circle...
- `main` (function) `progs/nuklear/node_editor.c:983` `int main(int argc, char **argv)`

## progs/nuklear/nuklear_minios.c
Depends on: `kernel/string.c`, `progs/nk_palette.h`, `progs/nuklear/nuklear_minios.h`, `progs/wl/wl_client.h`, `progs/wl/wl_mbox.h`
- `list` (function) `progs/nuklear/nuklear_minios.c:4` `* abstract draw command list (nk__begin/nk__next);`
- `nk_sys_time_ms` (function) `progs/nuklear/nuklear_minios.c:33` `long nk_sys_time_ms(void)` -- #include <string.h> #include <stdio.h> #include <math.h> #include "nuklear_minios.h" /* glibc program name for the...
- `nk_sys_kbd` (function) `progs/nuklear/nuklear_minios.c:38` `long nk_sys_kbd(void)`
- `nk_sys_palette` (function) `progs/nuklear/nuklear_minios.c:43` `long nk_sys_palette(const unsigned char *pal)`
- `nk_sys_kbd_raw` (function) `progs/nuklear/nuklear_minios.c:48` `long nk_sys_kbd_raw(int on)`
- `nk_sys_getpid` (function) `progs/nuklear/nuklear_minios.c:53` `long nk_sys_getpid(void)`
- `nk_client_probe` (function) `progs/nuklear/nuklear_minios.c:72` `static int nk_client_probe(void)`
- `nk_sys_vga_mode` (function) `progs/nuklear/nuklear_minios.c:114` `long nk_sys_vga_mode(int on)`
- `nk_sys_fb_info` (function) `progs/nuklear/nuklear_minios.c:121` `long nk_sys_fb_info(int *w, int *h, int *pitch)`
- `nk_sys_fb_info_rgb` (function) `progs/nuklear/nuklear_minios.c:137` `static long nk_sys_fb_info_rgb(int *w, int *h, int *pitch, int *rgb)`
- `nk_rgb_available` (function) `progs/nuklear/nuklear_minios.c:147` `int nk_rgb_available(void)`
- `rgb256_prepare` (function) `progs/nuklear/nuklear_minios.c:162` `static void rgb256_prepare(void)`
- `nk_idx_to_rgb` (function) `progs/nuklear/nuklear_minios.c:170` `void nk_idx_to_rgb(int idx, unsigned char *r, unsigned char *g,
                   unsigned char *b)`
- `cur_set` (function) `progs/nuklear/nuklear_minios.c:186` `static void cur_set(struct nk_color c)`
- `cur_bg_set` (function) `progs/nuklear/nuklear_minios.c:190` `static void cur_bg_set(struct nk_color c)`
- `nk_sys_mouse` (function) `progs/nuklear/nuklear_minios.c:193` `long nk_sys_mouse(int *xybw)`
- `nk_sys_mouse_badptr` (function) `progs/nuklear/nuklear_minios.c:198` `long nk_sys_mouse_badptr(void)`
- `nk_client_hash` (function) `progs/nuklear/nuklear_minios.c:216` `static unsigned nk_client_hash(const unsigned char *p, unsigned n)`
- `nk_client_publish` (function) `progs/nuklear/nuklear_minios.c:227` `static int nk_client_publish(void)`
- `nk_sys_nk_frame` (function) `progs/nuklear/nuklear_minios.c:280` `long nk_sys_nk_frame(int *origin)`
- `nk_mirror_box` (function) `progs/nuklear/nuklear_minios.c:314` `static void nk_mirror_box(char *dst, int cap)`
- `nk_mirror_emit` (function) `progs/nuklear/nuklear_minios.c:335` `static int nk_mirror_emit(const char *box, unsigned seq,
        const unsigned char *msg, int mlen)`
- `nk_mirror_tick` (function) `progs/nuklear/nuklear_minios.c:352` `static void nk_mirror_tick(void)`
- `nk_sys_gfx_set_title` (function) `progs/nuklear/nuklear_minios.c:409` `long nk_sys_gfx_set_title(const char *t)`
- `nk_build_palette` (function) `progs/nuklear/nuklear_minios.c:418` `void nk_build_palette(unsigned char *pal768)` -- The desktop-exact hybrid palette lives once in progs/nk_palette.h; * this wrapper keeps the platform signature while...
- `pal_prepare` (function) `progs/nuklear/nuklear_minios.c:427` `static void pal_prepare(void)`
- `col_to_idx` (function) `progs/nuklear/nuklear_minios.c:438` `static int col_to_idx(struct nk_color c)`
- `set_clip` (function) `progs/nuklear/nuklear_minios.c:469` `static void set_clip(int x, int y, int w, int h)`
- `px` (function) `progs/nuklear/nuklear_minios.c:479` `static void px(int x, int y, int c)`
- `px_bg` (function) `progs/nuklear/nuklear_minios.c:492` `static void px_bg(int x, int y, int c)` -- static void px(int x, int y, int c) { volatile uint8_t *d; if (x < clip_x || x >= clip_x + clip_w) return; if (y <...
- `px_idx` (function) `progs/nuklear/nuklear_minios.c:506` `static void px_idx(int x, int y, int c)` -- Index-owned pixels (IMAGE commands): RGB resolves through the exact * rgb256 table, so both buffers agree without a...
- `fill_rect` (function) `progs/nuklear/nuklear_minios.c:522` `static void fill_rect(int x, int y, int w, int h, int c)`
- `draw_line` (function) `progs/nuklear/nuklear_minios.c:529` `static void draw_line(int x0, int y0, int x1, int y1, int th, int c)`
- `fill_circle` (function) `progs/nuklear/nuklear_minios.c:547` `static void fill_circle(int cx, int cy, int r, int c)`
- `stroke_circle` (function) `progs/nuklear/nuklear_minios.c:553` `static void stroke_circle(int cx, int cy, int r, int th, int c)`
- `fill_poly` (function) `progs/nuklear/nuklear_minios.c:571` `static void fill_poly(int *xs, int *ys, int n, int c)` -- draw_line(cx + x, cy - y, cx - x, cy - y, th, c); draw_line(cx - x, cy + y, cx - x, cy - y, th, c); draw_line(cx +...
- `stroke_poly` (function) `progs/nuklear/nuklear_minios.c:594` `static void stroke_poly(int *xs, int *ys, int n, int th, int c)`
- `draw_text` (function) `progs/nuklear/nuklear_minios.c:601` `static void draw_text(int x, int y, const char *s, int len, int fg, int bg)`
- `draw_arc` (function) `progs/nuklear/nuklear_minios.c:615` `static void draw_arc(int cx, int cy, int r, float a0, float a1,
                     int filled, ...`
- `nk_rasterize` (function) `progs/nuklear/nuklear_minios.c:636` `void nk_rasterize(struct nk_context *ctx)`
- `nk_foreach` (function) `progs/nuklear/nuklear_minios.c:641` `nk_foreach(cmd, ctx)`
- `nk_minios_font_width` (function) `progs/nuklear/nuklear_minios.c:813` `static float nk_minios_font_width(nk_handle handle, float height,
                               ...` -- im->px[iy * im->w + ix]); } } break; } case NK_COMMAND_CUSTOM: break; default: break; } } } /* ---- Font (8x8...
- `nk_minios_font` (function) `progs/nuklear/nuklear_minios.c:819` `struct nk_user_font nk_minios_font(void)`
- `feed_key` (function) `progs/nuklear/nuklear_minios.c:854` `static void feed_key(struct nk_context *ctx, enum nk_keys key, int down)`
- `nk_set_scancode_hook` (function) `progs/nuklear/nuklear_minios.c:861` `void nk_set_scancode_hook(nk_scancode_cb cb, void *ud)`
- `handle_scancode` (function) `progs/nuklear/nuklear_minios.c:866` `static void handle_scancode(struct nk_context *ctx, unsigned char sc)`
- `nk_client_poll` (function) `progs/nuklear/nuklear_minios.c:914` `static void nk_client_poll(struct nk_context *ctx)` -- Client input pump: feed the pending .ev batch when its seq advanced, else hold the last state.
- `nk_poll_input` (function) `progs/nuklear/nuklear_minios.c:961` `void nk_poll_input(struct nk_context *ctx)`
- `nk_set_window_origin` (function) `progs/nuklear/nuklear_minios.c:1000` `void nk_set_window_origin(int x, int y)`
- `nk_quit_requested` (function) `progs/nuklear/nuklear_minios.c:1008` `int nk_quit_requested(void)` -- WM quit gesture latch: ESC or Alt+F4 pressed since the last poll.


Next: [API_p16.md](API_p16.md)
