# Symbols (page 8 of 27)
Previous: [SYMBOLS_p7.md](SYMBOLS_p7.md)

| Symbol | Kind | File:Line | Signature |
|--------|------|-----------|-----------|
| `tables` | function | `kernel.c:275` | `* tables (already built above) for its uncached register window and the      * heap for its rings...` |
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
| `n_ftell` | function | `kernel/cvm_host.c:154` | `static int64_t n_ftell(void *vm, int ac, uint64_t *av)` |
| `n_fwrite` | function | `kernel/cvm_host.c:141` | `static int64_t n_fwrite(void *vm, int ac, uint64_t *av)` |
| `n_malloc` | function | `kernel/cvm_host.c:88` | `static int64_t n_malloc(void *vm, int ac, uint64_t *av)` |
| `n_memcmp` | function | `kernel/cvm_host.c:68` | `static int64_t n_memcmp(void *vm, int ac, uint64_t *av)` |
| `n_memcpy` | function | `kernel/cvm_host.c:48` | `static int64_t n_memcpy(void *vm, int ac, uint64_t *av)` |
| `n_memmove` | function | `kernel/cvm_host.c:61` | `static int64_t n_memmove(void *vm, int ac, uint64_t *av)` |
| `n_memset` | function | `kernel/cvm_host.c:55` | `static int64_t n_memset(void *vm, int ac, uint64_t *av)` |
| `n_printf` | function | `kernel/cvm_host.c:369` | `static int64_t n_printf(void *vm, int ac, uint64_t *av)` |
| `n_putchar` | function | `kernel/cvm_host.c:197` | `static int64_t n_putchar(void *vm, int ac, uint64_t *av)` |
| `n_puts` | function | `kernel/cvm_host.c:228` | `static int64_t n_puts(void *vm, int ac, uint64_t *av)` |
| `n_read` | function | `kernel/cvm_host.c:213` | `static int64_t n_read(void *vm, int ac, uint64_t *av)` |
| `n_realloc` | function | `kernel/cvm_host.c:106` | `static int64_t n_realloc(void *vm, int ac, uint64_t *av)` |
| `n_rewind` | function | `kernel/cvm_host.c:160` | `static int64_t n_rewind(void *vm, int ac, uint64_t *av)` |
| `n_snprintf` | function | `kernel/cvm_host.c:384` | `static int64_t n_snprintf(void *vm, int ac, uint64_t *av)` |
| `n_sprintf` | function | `kernel/cvm_host.c:376` | `static int64_t n_sprintf(void *vm, int ac, uint64_t *av)` |
| `n_stderr_addr` | function | `kernel/cvm_host.c:262` | `static int64_t n_stderr_addr(void *vm, int ac, uint64_t *av)` |
| `n_stdin_addr` | function | `kernel/cvm_host.c:272` | `static int64_t n_stdin_addr(void *vm, int ac, uint64_t *av)` |
| `n_stdout_addr` | function | `kernel/cvm_host.c:267` | `static int64_t n_stdout_addr(void *vm, int ac, uint64_t *av)` |
| `n_strchr` | function | `kernel/cvm_host.c:75` | `static int64_t n_strchr(void *vm, int ac, uint64_t *av)` |
| `n_strcmp` | function | `kernel/cvm_host.c:22` | `static int64_t n_strcmp(void *vm, int ac, uint64_t *av)` |
| `n_strcpy` | function | `kernel/cvm_host.c:35` | `static int64_t n_strcpy(void *vm, int ac, uint64_t *av)` |
| `n_strncmp` | function | `kernel/cvm_host.c:28` | `static int64_t n_strncmp(void *vm, int ac, uint64_t *av)` |
| `n_strncpy` | function | `kernel/cvm_host.c:41` | `static int64_t n_strncpy(void *vm, int ac, uint64_t *av)` |
| `n_strstr` | function | `kernel/cvm_host.c:81` | `static int64_t n_strstr(void *vm, int ac, uint64_t *av)` |
| `n_strtol` | function | `kernel/cvm_host.c:249` | `static int64_t n_strtol(void *vm, int ac, uint64_t *av)` |
| `n_ungetc` | function | `kernel/cvm_host.c:185` | `static int64_t n_ungetc(void *vm, int ac, uint64_t *av)` |
| `n_write` | function | `kernel/cvm_host.c:204` | `static int64_t n_write(void *vm, int ac, uint64_t *av)` |
| `register_host_natives` | function | `kernel/cvm_host.c:392` | `static void register_host_natives(CvmState *vm)` |
| `ed25519_verify` | function | `kernel/ed25519.c:810` | `int ed25519_verify(const unsigned char sig[64], const unsigned char *msg,                    unsi...` |
| `ed_bytes_lt_q` | function | `kernel/ed25519.c:477` | `static unsigned ed_bytes_lt_q(const unsigned char b[32])` |
| `ed_curve_d` | function | `kernel/ed25519.c:706` | `static void ed_curve_d(ed_fe *d)` |
| `ed_fe` | struct | `kernel/ed25519.c:28` | `` |
| `ed_fe_add` | function | `kernel/ed25519.c:280` | `static void ed_fe_add(ed_fe *r, const ed_fe *a, const ed_fe *b)` |
| `ed_fe_cmov` | function | `kernel/ed25519.c:238` | `static void ed_fe_cmov(ed_fe *r, const ed_fe *b, unsigned flag)` |
| `ed_fe_copy` | function | `kernel/ed25519.c:214` | `static void ed_fe_copy(ed_fe *r, const ed_fe *a)` |
| `ed_fe_eq` | function | `kernel/ed25519.c:470` | `static unsigned ed_fe_eq(const ed_fe *a, const ed_fe *b)` |
| `ed_fe_fold` | function | `kernel/ed25519.c:344` | `static void ed_fe_fold(ed_fe *r, ed_u64 w[8])` |
| `ed_fe_frombytes` | function | `kernel/ed25519.c:449` | `static void ed_fe_frombytes(ed_fe *r, const unsigned char b[32])` |
| `ed_fe_ge` | function | `kernel/ed25519.c:247` | `static unsigned ed_fe_ge(const ed_fe *a, const ed_fe *b)` |
| `ed_fe_inv` | function | `kernel/ed25519.c:438` | `static void ed_fe_inv(ed_fe *r, const ed_fe *a)` |
| `ed_fe_mul` | function | `kernel/ed25519.c:387` | `static void ed_fe_mul(ed_fe *r, const ed_fe *a, const ed_fe *b)` |
| `ed_fe_one` | function | `kernel/ed25519.c:230` | `static void ed_fe_one(ed_fe *r)` |
| `ed_fe_pow` | function | `kernel/ed25519.c:421` | `static void ed_fe_pow(ed_fe *r, const ed_fe *a, const unsigned char *bits, unsigned nbits)` |
| `ed_fe_rawsub` | function | `kernel/ed25519.c:258` | `static void ed_fe_rawsub(ed_fe *r, const ed_fe *a, const ed_fe *b)` |
| `ed_fe_sq` | function | `kernel/ed25519.c:416` | `static void ed_fe_sq(ed_fe *r, const ed_fe *a)` |
| `ed_fe_sub` | function | `kernel/ed25519.c:302` | `static void ed_fe_sub(ed_fe *r, const ed_fe *a, const ed_fe *b)` |
| `ed_fe_tobytes` | function | `kernel/ed25519.c:461` | `static void ed_fe_tobytes(unsigned char b[32], const ed_fe *a)` |
| `ed_fe_zero` | function | `kernel/ed25519.c:222` | `static void ed_fe_zero(ed_fe *r)` |
| `ed_ge` | struct | `kernel/ed25519.c:32` | `` |
| `ed_ge_add` | function | `kernel/ed25519.c:612` | `static void ed_ge_add(ed_ge *r, const ed_ge *p, const ed_ge *q, const ed_fe *d2)` |
| `ed_ge_cmov` | function | `kernel/ed25519.c:604` | `static void ed_ge_cmov(ed_ge *r, const ed_ge *b, unsigned flag)` |
| `ed_ge_copy` | function | `kernel/ed25519.c:596` | `static void ed_ge_copy(ed_ge *r, const ed_ge *a)` |
| `ed_ge_double` | function | `kernel/ed25519.c:644` | `static void ed_ge_double(ed_ge *r, const ed_ge *p)` |
| `ed_ge_scalarmult` | function | `kernel/ed25519.c:686` | `static void ed_ge_scalarmult(ed_ge *r, const ed_ge *p, const unsigned char s[32],                ...` |
| `ed_mod_l` | function | `kernel/ed25519.c:557` | `static void ed_mod_l(ed_fe *r, const unsigned char h[64])` |
| `ed_rem_ge` | function | `kernel/ed25519.c:545` | `static unsigned ed_rem_ge(const ed_u64 a[5], const ed_u64 b[5])` |
| `ed_rem_sub` | function | `kernel/ed25519.c:517` | `static void ed_rem_sub(ed_u64 r[5], const ed_u64 a[5], const ed_u64 b[5])` |
| `ed_rotr` | function | `kernel/ed25519.c:84` | `static ed_u64 ed_rotr(ed_u64 x, unsigned n)` |
| `ed_scalar_lt_l` | function | `kernel/ed25519.c:495` | `static unsigned ed_scalar_lt_l(const unsigned char b[32])` |
| `ed_sha512_final` | function | `kernel/ed25519.c:188` | `void ed_sha512_final(ed_sha *c, unsigned char out[64])` |
| `ed_sha512_init` | function | `kernel/ed25519.c:147` | `void ed_sha512_init(ed_sha *c)` |
| `ed_sha512_update` | function | `kernel/ed25519.c:162` | `void ed_sha512_update(ed_sha *c, const unsigned char *data, unsigned long len)` |
| `ed_sha_block` | function | `kernel/ed25519.c:89` | `static void ed_sha_block(ed_sha *c, const unsigned char *p)` |
| `ed_u64` | type_alias | `kernel/ed25519.c:23` | `typedef unsigned long long ed_u64;` |
| `EDIT_FILE_MAX` | macro | `kernel/editor.c:22` | `#define EDIT_FILE_MAX` |
| `EDIT_LINE_MAX` | macro | `kernel/editor.c:21` | `#define EDIT_LINE_MAX` |
| `EDIT_MAX_LINES` | macro | `kernel/editor.c:20` | `#define EDIT_MAX_LINES` |
| `EditBuf` | struct | `kernel/editor.c:29` | `` |
| `EditLine` | struct | `kernel/editor.c:24` | `` |
| `edit_alloc` | function | `kernel/editor.c:38` | `static EditBuf *edit_alloc(const char *fname)` |
| `edit_arg_line` | function | `kernel/editor.c:213` | `static int edit_arg_line(int argc, char **argv, EditBuf *e, int *out)` |
| `edit_delete` | function | `kernel/editor.c:154` | `static int edit_delete(EditBuf *e, int idx)` |
| `edit_free` | function | `kernel/editor.c:55` | `static void edit_free(EditBuf *e)` |
| `edit_insert` | function | `kernel/editor.c:144` | `static int edit_insert(EditBuf *e, int idx, const char *text)` |
| `edit_line_cstr` | function | `kernel/editor.c:166` | `static void edit_line_cstr(EditLine *l, char *out)` |
| `edit_list` | function | `kernel/editor.c:123` | `static void edit_list(EditBuf *e, int start, int end)` |
| `edit_load` | function | `kernel/editor.c:61` | `static int edit_load(EditBuf *e)` |
| `edit_loop` | function | `kernel/editor.c:224` | `static void edit_loop(EditBuf *e)` |
| `edit_print` | function | `kernel/editor.c:113` | `static void edit_print(EditBuf *e, int idx)` |
| `edit_refuse_save` | function | `kernel/editor.c:207` | `static int edit_refuse_save(EditBuf *e)` |
| `edit_save` | function | `kernel/editor.c:99` | `static int edit_save(EditBuf *e)` |
| `edit_search` | function | `kernel/editor.c:171` | `static void edit_search(EditBuf *e, const char *needle)` |
| `edit_set_line` | function | `kernel/editor.c:135` | `static int edit_set_line(EditBuf *e, int idx, const char *text)` |
| `edit_status` | function | `kernel/editor.c:188` | `static void edit_status(EditBuf *e)` |
| `edit_usage` | function | `kernel/editor.c:196` | `static void edit_usage(void)` |
| `shell_cmd_edit` | function | `kernel/editor.c:329` | `void shell_cmd_edit(int argc, char **argv)` |
| `ETREL_CHILD_STACK_SZ` | macro | `kernel/exec.c:133` | `#define ETREL_CHILD_STACK_SZ` |
| `EXEC_KSTACK_SZ` | macro | `kernel/exec.c:124` | `#define EXEC_KSTACK_SZ` |
| `k_run_rel` | function | `kernel/exec.c:233` | `int k_run_rel(prog_entry_t entry, int argc, char **argv)` |
| `k_user_fault_return` | function | `kernel/exec.c:66` | `void k_user_fault_return(void)` |
| `kexit` | function | `kernel/exec.c:284` | `void kexit(int code)` |
| `setup_user_stack` | function | `kernel/exec.c:83` | `unsigned long *setup_user_stack(char *sbase, unsigned long ssize,                                ...` |
| `syscall_kstack` | variable | `kernel/exec.c:116` | `extern unsigned long syscall_kstack;` |
| `vga_gfx_ran_set` | function | `kernel/exec.c:63` | `void vga_gfx_ran_set(int on)` |
| `vga_mode_is_active` | function | `kernel/exec.c:62` | `int  vga_mode_is_active(void)` |
| `vga_mode_set` | function | `kernel/exec.c:61` | `void vga_mode_set(int on)` |
| `futex_bucket` | function | `kernel/futex.c:31` | `static futex_bucket_t *futex_bucket(unsigned long uaddr)` |
| `futex_forget` | function | `kernel/futex.c:76` | `void futex_forget(int pid)` |
| `futex_hash` | function | `kernel/futex.c:23` | `static unsigned long futex_hash(unsigned long uaddr)` |
| `futex_init` | function | `kernel/futex.c:36` | `void futex_init(void)` |
| `futex_linux_cmd` | function | `kernel/futex.c:128` | `int futex_linux_cmd(long op)` |
| `futex_table_t` | struct | `kernel/futex.c:16` | `` |
| `futex_timeout_remaining_us` | function | `kernel/futex.c:139` | `long futex_timeout_remaining_us(int cmd, long sec, long nsec, unsigned long now_us)` |
| `futex_unlink_locked` | function | `kernel/futex.c:50` | `static void futex_unlink_locked(futex_bucket_t *b, int pid)` |
| `futex_wake` | function | `kernel/futex.c:158` | `long futex_wake(unsigned long uaddr, int n)` |
| `t_cur_pid` | variable | `kernel/futex.c:13` | `extern int t_cur_pid;` |
| `klog` | function | `kernel/klog.c:41` | `void klog(log_level_t level, log_subsystem_t subsys,           const char *fmt, ...)` |
| `klog_disable` | function | `kernel/klog.c:38` | `void klog_disable(void)` |
| `klog_enable` | function | `kernel/klog.c:39` | `void klog_enable(void)` |
| `klog_hexdump` | function | `kernel/klog.c:119` | `void klog_hexdump(log_level_t level, log_subsystem_t subsys,                   const void *data, ...` |
| `klog_set_level` | function | `kernel/klog.c:29` | `void klog_set_level(log_level_t level)` |
| `klog_set_subsys_level` | function | `kernel/klog.c:33` | `void klog_set_subsys_level(log_subsystem_t subsys, log_level_t level)` |
| `LDSO_DYN_ENT` | macro | `kernel/ldso_parse.c:15` | `#define LDSO_DYN_ENT` |
| `LDSO_EHSIZE` | macro | `kernel/ldso_parse.c:13` | `#define LDSO_EHSIZE` |
| `LDSO_HASH_HDR` | macro | `kernel/ldso_parse.c:16` | `#define LDSO_HASH_HDR` |
| `LDSO_PHENTSZ` | macro | `kernel/ldso_parse.c:14` | `#define LDSO_PHENTSZ` |
| `ldso_basename` | function | `kernel/ldso_parse.c:331` | `void ldso_basename(char *out, const char *src)` |
| `ldso_copy_str` | function | `kernel/ldso_parse.c:227` | `int ldso_copy_str(const unsigned char *file, unsigned long long fsize,         unsigned long long...` |
| `ldso_find_dynamic` | function | `kernel/ldso_parse.c:120` | `int ldso_find_dynamic(const unsigned char *file, unsigned long long fsize,         unsigned long ...` |
| `ldso_name_eq` | function | `kernel/ldso_parse.c:250` | `static int ldso_name_eq(const unsigned char *tab, unsigned long long strsz,         unsigned long...` |
| `ldso_rd16` | function | `kernel/ldso_parse.c:18` | `static unsigned ldso_rd16(const unsigned char *p)` |
| `ldso_rd32` | function | `kernel/ldso_parse.c:22` | `static unsigned long ldso_rd32(const unsigned char *p)` |
| `ldso_rd64` | function | `kernel/ldso_parse.c:27` | `static unsigned long long ldso_rd64(const unsigned char *p)` |
| `ldso_read_rela` | function | `kernel/ldso_parse.c:309` | `int ldso_read_rela(const unsigned char *file, unsigned long long fsize,         unsigned long lon...` |
| `ldso_rela_count` | function | `kernel/ldso_parse.c:296` | `int ldso_rela_count(const LdsoDynInfo *info, unsigned *nrela)` |
| `ldso_scan_dynamic` | function | `kernel/ldso_parse.c:150` | `int ldso_scan_dynamic(const unsigned char *file, unsigned long long fsize,         unsigned long ...` |
| `ldso_segments` | function | `kernel/ldso_parse.c:86` | `int ldso_segments(const unsigned char *file, unsigned long long fsize,         LdsoSeg *segs, uns...` |
| `ldso_slice` | function | `kernel/ldso_parse.c:32` | `static int ldso_slice(const unsigned char *file, unsigned long long fsize,         unsigned long ...` |
| `ldso_sym_count` | function | `kernel/ldso_parse.c:213` | `int ldso_sym_count(const unsigned char *file, unsigned long long fsize,         unsigned long lon...` |
| `ldso_sym_lookup` | function | `kernel/ldso_parse.c:263` | `int ldso_sym_lookup(const unsigned char *file, unsigned long long fsize,         unsigned long lo...` |
| `ldso_vaddr_to_offset` | function | `kernel/ldso_parse.c:54` | `int ldso_vaddr_to_offset(const unsigned char *file,         unsigned long long fsize, unsigned lo...` |
| `ldso_valid_ehdr` | function | `kernel/ldso_parse.c:40` | `static int ldso_valid_ehdr(const unsigned char *file,         unsigned long long fsize)` |
| `ELF64_R_SYM` | macro | `kernel/loader.c:62` | `#define ELF64_R_SYM(i)` |
| `ELF64_R_TYPE` | macro | `kernel/loader.c:63` | `#define ELF64_R_TYPE(i)` |
| `ELF_MAX_SEGMENTS` | macro | `kernel/loader.c:101` | `#define ELF_MAX_SEGMENTS` |
| `ELF_NAME_MAX` | macro | `kernel/loader.c:102` | `#define ELF_NAME_MAX` |
| `ELF_NOTE_ALIGN` | macro | `kernel/loader.c:88` | `#define ELF_NOTE_ALIGN` |
| `ELF_NOTE_HDR` | macro | `kernel/loader.c:87` | `#define ELF_NOTE_HDR` |
| `EM_X86_64` | macro | `kernel/loader.c:81` | `#define EM_X86_64` |
| `ETREL_IMAGE_MAX` | macro | `kernel/loader.c:71` | `#define ETREL_IMAGE_MAX` |
| `Elf64_Phdr` | struct | `kernel/loader.c:51` | `` |
| `Elf64_Rela` | struct | `kernel/loader.c:45` | `` |
| `Elf64_Shdr` | struct | `kernel/loader.c:23` | `` |
| `Elf64_Sym` | struct | `kernel/loader.c:36` | `` |
| `LdsoLibEnt` | struct | `kernel/loader.c:388` | `` |
| `PF_X` | macro | `kernel/loader.c:100` | `#define PF_X` |
| `PT_LOAD` | macro | `kernel/loader.c:82` | `#define PT_LOAD` |
| `PT_NOTE` | macro | `kernel/loader.c:83` | `#define PT_NOTE` |
| `R_X86_64_32` | macro | `kernel/loader.c:96` | `#define R_X86_64_32` |
| `R_X86_64_32S` | macro | `kernel/loader.c:97` | `#define R_X86_64_32S` |
| `R_X86_64_64` | macro | `kernel/loader.c:90` | `#define R_X86_64_64` |
| `R_X86_64_GLOB_DAT` | macro | `kernel/loader.c:93` | `#define R_X86_64_GLOB_DAT` |
| `R_X86_64_IRELATIVE` | macro | `kernel/loader.c:98` | `#define R_X86_64_IRELATIVE` |
| `R_X86_64_JUMP_SLOT` | macro | `kernel/loader.c:94` | `#define R_X86_64_JUMP_SLOT` |
| `R_X86_64_PC32` | macro | `kernel/loader.c:91` | `#define R_X86_64_PC32` |
| `R_X86_64_PLT32` | macro | `kernel/loader.c:92` | `#define R_X86_64_PLT32` |
| `R_X86_64_RELATIVE` | macro | `kernel/loader.c:95` | `#define R_X86_64_RELATIVE` |
| `SHF_ALLOC` | macro | `kernel/loader.c:78` | `#define SHF_ALLOC` |
| `SHF_EXECINSTR` | macro | `kernel/loader.c:79` | `#define SHF_EXECINSTR` |
| `SHN_UNDEF` | macro | `kernel/loader.c:64` | `#define SHN_UNDEF` |
| `SHT_NOBITS` | macro | `kernel/loader.c:77` | `#define SHT_NOBITS` |
| `SHT_NOTE` | macro | `kernel/loader.c:1067` | `#define SHT_NOTE` |
| `SHT_PROGBITS` | macro | `kernel/loader.c:76` | `#define SHT_PROGBITS` |
| `SHT_RELA` | macro | `kernel/loader.c:75` | `#define SHT_RELA` |
| `SHT_STRTAB` | macro | `kernel/loader.c:74` | `#define SHT_STRTAB` |
| `SHT_SYMTAB` | macro | `kernel/loader.c:73` | `#define SHT_SYMTAB` |
| `SIGN_NOTE_NAME` | macro | `kernel/loader.c:1069` | `#define SIGN_NOTE_NAME` |
| `apply_exec_relocs` | function | `kernel/loader.c:984` | `static void apply_exec_relocs(void *data, unsigned size, unsigned long base,                     ...` |
| `base_out` | function | `kernel/loader.c:1395` | `* the link base via base_out (0 when the caller runs static images  * only: the dynamic binder ne...` |
| `consistent` | function | `kernel/loader.c:579` | `* consistent (the next exec forgets them, a dying window frees them),  * and only reports. */ sta...` |
| `elf_load` | function | `kernel/loader.c:136` | `void *elf_load(void *data, unsigned size, void **base_out)` |
| `elf_load_fail` | function | `kernel/loader.c:128` | `static void elf_load_fail(void *base, void **sec_addrs, const char *why)` |
| `elf_name_copy` | function | `kernel/loader.c:114` | `static void elf_name_copy(char *out, unsigned out_cap, const char *tab,                          ...` |
| `elf_note_pad` | function | `kernel/loader.c:1072` | `static unsigned long elf_note_pad(unsigned long n)` |
| `elf_sign_note_find` | function | `kernel/loader.c:1108` | `static int elf_sign_note_find(const unsigned char *img, unsigned size,                           ...` |
| `elf_sign_note_span` | function | `kernel/loader.c:1083` | `static int elf_sign_note_span(const unsigned char *img, unsigned long off,                       ...` |
| `elf_sign_section_find` | function | `kernel/loader.c:1132` | `static int elf_sign_section_find(const unsigned char *img, unsigned size,                        ...` |
| `elf_sign_u32` | function | `kernel/loader.c:1181` | `static void elf_sign_u32(ed_sha *c, unsigned v)` |
| `elf_sign_u64` | function | `kernel/loader.c:1172` | `static void elf_sign_u64(ed_sha *c, unsigned long v)` |
| `elf_wants_process` | function | `kernel/loader.c:1432` | `int elf_wants_process(const void *data, unsigned size)` |
| `exec_range` | struct | `kernel/loader.c:104` | `` |
| `images` | function | `kernel/loader.c:790` | `* Static images (no dynamic section, or none needed) return 0 at * once, so the legacy paths never observe a...` |
| `inodes` | function | `kernel/loader.c:381` | `* Pseudo inodes (LDSO_INO_BASE + slot) keep registry pages apart from * MiniFS inodes in the shared cache. No unload...` |
| `ldso_bind_into` | function | `kernel/loader.c:794` | `int ldso_bind_into(void *data, unsigned size, unsigned long base,         unsigned long cr3, vma_...` |
| `ldso_ensure_slot` | function | `kernel/loader.c:483` | `static int ldso_ensure_slot(const char *needed, int *slot_out)` |
| `ldso_pseudo_read` | function | `kernel/loader.c:416` | `int ldso_pseudo_read(int ino, void *dst, unsigned long off, unsigned len)` |
| `ldso_pseudo_stat` | function | `kernel/loader.c:402` | `int ldso_pseudo_stat(int ino, unsigned long *size_out)` |
| `ldso_read_file` | function | `kernel/loader.c:441` | `static int ldso_read_file(const char *name, unsigned char **out,         unsigned *size_out)` |
| `load_exec_elf` | function | `kernel/loader.c:1262` | `void *load_exec_elf(void *data, unsigned size)` |
| `load_exec_elf_into` | function | `kernel/loader.c:1456` | `void *load_exec_elf_into(void *data, unsigned size, unsigned long cr3,                          u...` |
| `process` | function | `kernel/loader.c:1288` | `* atomic section: a 100 Hz tick between two segments would switch * CR3 into another process (copies landing in its...` |
| `time` | function | `kernel/loader.c:1520` | `* time (with the failing offset);` |
| `HASH_BITS` | macro | `kernel/lz4_kernel.c:4` | `#define HASH_BITS` |
| `HASH_SIZE` | macro | `kernel/lz4_kernel.c:5` | `#define HASH_SIZE` |
| `LZ4_compressBound` | function | `kernel/lz4_kernel.c:33` | `int LZ4_compressBound(int inputSize)` |
| `LZ4_compress_default` | function | `kernel/lz4_kernel.c:40` | `int LZ4_compress_default(const char *src, char *dst, int srcSize, int dstCapacity)` |
| `LZ4_decompress_safe` | function | `kernel/lz4_kernel.c:176` | `int LZ4_decompress_safe(const char *src, char *dst, int compressedSize, int dstCapacity)` |
| `LZ4_hash` | function | `kernel/lz4_kernel.c:26` | `static unsigned int LZ4_hash(const unsigned char *p)` |
| `LZ4_read16` | function | `kernel/lz4_kernel.c:14` | `static inline unsigned int LZ4_read16(const unsigned char *p)` |
| `LZ4_read32` | function | `kernel/lz4_kernel.c:7` | `static inline unsigned int LZ4_read32(const unsigned char *p)` |
| `LZ4_write16` | function | `kernel/lz4_kernel.c:21` | `static inline void LZ4_write16(unsigned char *dst, unsigned short v)` |
| `slots` | function | `kernel/lz4_kernel.c:43` | `* runs from file writes on 16 KB proc slots (stack discipline, * CLAUDE.md). OOM returns 0 and the caller stores...` |
| `frame` | function | `kernel/minifetch.c:159` | `* frame (stack discipline, CLAUDE.md). Fail-closed on OOM. */ char (*specs)[96] = (char (*)[96])kmalloc(20 * 96);` |
| `minifetch_cfg` | struct | `kernel/minifetch.c:21` | `` |
| `minifetch_logo` | function | `kernel/minifetch.c:81` | `static void minifetch_logo(char rows[16][33])` |
| `minifetch_row` | function | `kernel/minifetch.c:57` | `static void minifetch_row(const unsigned char *img, int w, int h, int row,                       ...` |
| `minifetch_specs` | function | `kernel/minifetch.c:101` | `static int minifetch_specs(char lines[20][96])` |
| `shell_cmd_minifetch` | function | `kernel/minifetch.c:156` | `void shell_cmd_minifetch(void)` |
| `KMALLOC_REPORT_EVERY` | macro | `kernel/mm.c:50` | `#define KMALLOC_REPORT_EVERY` |
| `kallocator_init` | function | `kernel/mm.c:32` | `void kallocator_init(void)` |
| `kcalloc` | function | `kernel/mm.c:111` | `void *kcalloc(unsigned long nmemb, unsigned long size)` |
| `kfree` | function | `kernel/mm.c:90` | `void kfree(void *ptr)` |
| `kfree_aligned` | function | `kernel/mm.c:143` | `void kfree_aligned(void *ptr)` |
| `kheap_ram_top` | function | `kernel/mm.c:19` | `static unsigned long kheap_ram_top(void)` |
| `kmalloc` | function | `kernel/mm.c:66` | `void *kmalloc(unsigned long size)` |
| `kmalloc_aligned` | function | `kernel/mm.c:127` | `void *kmalloc_aligned(unsigned long size, unsigned long align)` |
| `kmalloc_page` | function | `kernel/mm.c:81` | `void *kmalloc_page(void)` |
| `kmalloc_report_failure` | function | `kernel/mm.c:53` | `static void kmalloc_report_failure(unsigned long size)` |
| `krealloc` | function | `kernel/mm.c:115` | `void *krealloc(void *ptr, unsigned long size)` |
| `COW_BITS` | macro | `kernel/mm/cow.c:34` | `#define COW_BITS` |
| `COW_CAP` | macro | `kernel/mm/cow.c:35` | `#define COW_CAP` |
| `COW_EMPTY` | macro | `kernel/mm/cow.c:39` | `#define COW_EMPTY` |
| `COW_HASH_MUL` | macro | `kernel/mm/cow.c:41` | `#define COW_HASH_MUL` |
| `COW_LOAD_MAX` | macro | `kernel/mm/cow.c:37` | `#define COW_LOAD_MAX` |
| `COW_MASK` | macro | `kernel/mm/cow.c:36` | `#define COW_MASK` |
| `COW_TOMB` | macro | `kernel/mm/cow.c:40` | `#define COW_TOMB` |
| `COW_TOMB_MAX` | macro | `kernel/mm/cow.c:38` | `#define COW_TOMB_MAX` |
| `CPU` | function | `kernel/mm/cow.c:287` | `* address space down on every other CPU (tlb_shootdown in do_fork_ex). */ unsigned long cow_fork_...` |
| `PT_PTE_RW` | macro | `kernel/mm/cow.c:48` | `#define PT_PTE_RW` |
| `PT_USER_RO` | macro | `kernel/mm/cow.c:46` | `#define PT_USER_RO` |
| `PT_USER_RW_ENTRY` | macro | `kernel/mm/cow.c:47` | `#define PT_USER_RW_ENTRY` |
| `alternative` | function | `kernel/mm/cow.c:20` | `* window is one instruction wide and the alternative (no CoW) is * documented, so the trade stands. */ #include...` |
| `cow_copy_demand` | function | `kernel/mm/cow.c:166` | `static void cow_copy_demand(unsigned long pcr3, unsigned long ccr3)` |
| `cow_entry_t` | struct | `kernel/mm/cow.c:58` | `` |
| `cow_find` | function | `kernel/mm/cow.c:73` | `static int cow_find(unsigned long phys)` |
| `cow_fork_one` | function | `kernel/mm/cow.c:255` | `static void cow_fork_one(unsigned long pcr3, unsigned long va,         volatile unsigned long *ppte)` |
| `cow_page_shared` | function | `kernel/mm/cow.c:132` | `int cow_page_shared(unsigned long phys)` |
| `cow_rehash` | function | `kernel/mm/cow.c:110` | `static void cow_rehash(void)` |
| `cow_release_window` | function | `kernel/mm/cow.c:421` | `void cow_release_window(unsigned long cr3)` |
| `cow_remove` | function | `kernel/mm/cow.c:85` | `static void cow_remove(int idx)` |
| `cow_resolve` | function | `kernel/mm/cow.c:356` | `int cow_resolve(unsigned long cr3, unsigned long va)` |
| `cow_shared` | function | `kernel/mm/cow.c:464` | `int cow_shared(void)` |
| `cow_slot` | function | `kernel/mm/cow.c:68` | `static unsigned long cow_slot(unsigned long phys)` |
| `cow_table_ensure` | function | `kernel/mm/cow.c:98` | `static void cow_table_ensure(void)` |
| `cow_track` | function | `kernel/mm/cow.c:191` | `static int cow_track(unsigned long phys)` |
| `cow_walk` | function | `kernel/mm/cow.c:221` | `static void cow_walk(unsigned long cr3, cow_walk_fn fn)` |
| `private` | function | `kernel/mm/cow.c:217` | `* for every present page in a private (non-graphics) slot. Shared * graphics slots are never CoW: the compositor...` |
| `KMM_DEVICE_FLAGS` | macro | `kernel/mm/paging.c:211` | `#define KMM_DEVICE_FLAGS` |
| `KMM_DEVICE_MAX` | macro | `kernel/mm/paging.c:200` | `#define KMM_DEVICE_MAX` |
| `KMM_MAX_IDENTITY` | macro | `kernel/mm/paging.c:204` | `#define KMM_MAX_IDENTITY` |
| `PTE` | function | `kernel/mm/paging.c:1015` | `* PTE (a cache page stays cached, but no stale writer may reach it).  * Never allocates. */ void ...` |
| `PT_OWNED_BYTES` | macro | `kernel/mm/paging.c:371` | `#define PT_OWNED_BYTES` |
| `_kernel_end` | variable | `kernel/mm/paging.c:49` | `extern char _kernel_end[];` |
| `coherent` | function | `kernel/mm/paging.c:259` | `* for memory a device reads and writes by DMA: a controller that is not cache  * coherent (and an...` |
| `explicitly` | function | `kernel/mm/paging.c:1011` | `* teardown passes the dying window explicitly (zombie-exclusive, no * lock needed). unmap == 0 drops refs only...` |
| `honest` | function | `kernel/mm/paging.c:655` | `* and invlpg keeps the local TLB honest (cross-CPU shootdown rides  * the documented T5 follow-up...` |
| `kmm_ensure_pt` | function | `kernel/mm/paging.c:235` | `static volatile unsigned long *kmm_ensure_pt(unsigned long phys)` |
| `kmm_map_device` | function | `kernel/mm/paging.c:296` | `unsigned long kmm_map_device(unsigned long phys, unsigned long len)` |
| `mm_anon_fault` | function | `kernel/mm/paging.c:779` | `int mm_anon_fault(unsigned long cr3, unsigned long va, int write)` |
| `mm_anon_frame` | function | `kernel/mm/paging.c:715` | `static int mm_anon_frame(unsigned long phys)` |
| `mm_copy_user_page` | function | `kernel/mm/paging.c:1149` | `int mm_copy_user_page(unsigned long dst_cr3, unsigned long src_cr3, unsigned long va)` |
| `mm_demand_pte` | function | `kernel/mm/paging.c:704` | `unsigned long mm_demand_pte(unsigned long prot)` |
| `mm_file_break` | function | `kernel/mm/paging.c:1070` | `int mm_file_break(unsigned long cr3, unsigned long va)` |
| `mm_file_page_phys` | function | `kernel/mm/paging.c:861` | `unsigned long mm_file_page_phys(unsigned long cr3, unsigned long va)` |
| `mm_file_pte` | function | `kernel/mm/paging.c:880` | `static volatile unsigned long *mm_file_pte(unsigned long cr3,         unsigned long va)` |
| `mm_lock` | variable | `kernel/mm/paging.c:696` | `extern spinlock_t mm_lock;` |
| `mm_page_aligned_alloc` | function | `kernel/mm/paging.c:32` | `static unsigned char *mm_page_aligned_alloc(unsigned size,                                       ...` |
| `mm_setup_protections` | function | `kernel/mm/paging.c:41` | `void mm_setup_protections(void)` |
| `mm_user_ensure_page` | function | `kernel/mm/paging.c:625` | `int mm_user_ensure_page(unsigned long cr3, unsigned long va)` |
| `mm_user_pte_update` | function | `kernel/mm/paging.c:336` | `void mm_user_pte_update(unsigned long vaddr, int exec, unsigned long cr3)` |
| `mm_user_set_exec` | function | `kernel/mm/paging.c:356` | `void mm_user_set_exec(unsigned long start, unsigned long end, unsigned long cr3)` |
| `mt_shared_slot` | function | `kernel/mm/paging.c:549` | `static int mt_shared_slot(unsigned long pd_idx)` |
| `pt_clone_user` | function | `kernel/mm/paging.c:420` | `uint64_t pt_clone_user(uint64_t parent_cr3)` |
| `pt_clone_user_empty` | function | `kernel/mm/paging.c:568` | `unsigned long pt_clone_user_empty(void)` |
| `pt_free_user` | function | `kernel/mm/paging.c:1227` | `void pt_free_user(uint64_t cr3)` |
| `pt_owned_index` | function | `kernel/mm/paging.c:374` | `static int pt_owned_index(unsigned long phys, unsigned long *byte, unsigned *bit)` |
| `pt_page_alloc` | function | `kernel/mm/paging.c:392` | `void *pt_page_alloc(void)` |
| `pt_page_free` | function | `kernel/mm/paging.c:411` | `void pt_page_free(void *ptr)` |
| `pt_page_owned` | function | `kernel/mm/paging.c:385` | `int pt_page_owned(unsigned long phys)` |
| `tables` | function | `kernel/mm/paging.c:1010` | `* tables (munmap/mremap in caller context, under their mm_lock);` |
| `SWAP_CHUNK_CMP` | macro | `kernel/mm/swap.c:18` | `#define SWAP_CHUNK_CMP` |
| `SWAP_CHUNK_RAW` | macro | `kernel/mm/swap.c:17` | `#define SWAP_CHUNK_RAW` |
| `SWAP_CHUNK_SECTORS` | macro | `kernel/mm/swap.c:19` | `#define SWAP_CHUNK_SECTORS` |
| `SWAP_HDR_SECTORS` | macro | `kernel/mm/swap.c:20` | `#define SWAP_HDR_SECTORS` |
| `SWAP_MAGIC` | macro | `kernel/mm/swap.c:22` | `#define SWAP_MAGIC` |
| `SWAP_MAX_SECTORS` | macro | `kernel/mm/swap.c:21` | `#define SWAP_MAX_SECTORS` |
| `swap_ensure` | function | `kernel/mm/swap.c:28` | `static int swap_ensure(void)` |
| `swap_in` | function | `kernel/mm/swap.c:97` | `int swap_in(void)` |
| `swap_lba` | function | `kernel/mm/swap.c:41` | `static unsigned long swap_lba(void)` |
| `swap_out` | function | `kernel/mm/swap.c:47` | `int swap_out(unsigned long window_sz)` |
| `unwired` | function | `kernel/mm/swap.c:7` | `* * Currently unwired (the isolated-window spawn path superseded the * swap-out design);` |
| `TLB_SHOOT_SPIN_MAX` | macro | `kernel/mm/tlb.c:24` | `#define TLB_SHOOT_SPIN_MAX` |
| `tlb_others_on` | function | `kernel/mm/tlb.c:36` | `static int tlb_others_on(unsigned long cr3)` |
| `tlb_shootdown` | function | `kernel/mm/tlb.c:49` | `void tlb_shootdown(unsigned long cr3)` |
| `tlb_shootdown_count` | function | `kernel/mm/tlb.c:71` | `unsigned long tlb_shootdown_count(void)` |
| `tlb_shootdown_timeouts` | function | `kernel/mm/tlb.c:75` | `unsigned long tlb_shootdown_timeouts(void)` |
| `panic_fb_hex` | function | `kernel/panic.c:61` | `static void panic_fb_hex(unsigned long v, int digits)` |
| `panic_fb_puts` | function | `kernel/panic.c:30` | `static void panic_fb_puts(const char *s)` |
| `panic_hex` | function | `kernel/panic.c:23` | `static void panic_hex(unsigned long v, int digits)` |
| `panic_screen` | function | `kernel/panic.c:96` | `void panic_screen(unsigned long vector, unsigned long err,         unsigned long rip, unsigned lo...` |
| `rq_cpu_valid` | function | `kernel/percpu_rq.c:14` | `static int rq_cpu_valid(int cpu)` |
| `rq_empty` | function | `kernel/percpu_rq.c:115` | `int rq_empty(int cpu)` |
| `rq_enqueue` | function | `kernel/percpu_rq.c:41` | `void rq_enqueue(int cpu, int pid)` |
| `rq_init` | function | `kernel/percpu_rq.c:19` | `void rq_init(void)` |
| `rq_note_poll` | function | `kernel/percpu_rq.c:127` | `void rq_note_poll(int cpu)` |
| `rq_pop_local` | function | `kernel/percpu_rq.c:61` | `int rq_pop_local(int cpu)` |
| `rq_should_rescan` | function | `kernel/percpu_rq.c:137` | `int rq_should_rescan(int cpu)` |
| `rq_stats` | function | `kernel/percpu_rq.c:152` | `void rq_stats(int cpu, unsigned long *hits, unsigned long *steals,               unsigned long *d...` |
| `rq_steal_once` | function | `kernel/percpu_rq.c:89` | `int rq_steal_once(int self_cpu, int *from_cpu)` |
| `emit_num` | function | `kernel/printf.c:26` | `static void emit_num(void (*emit)(char, void *, int *), void *ctx, int *written,                 ...` |
| `kformat` | function | `kernel/printf.c:44` | `static void kformat(void (*emit)(char, void *, int *), void *ctx,                     int *writte...` |
| `kfprintf` | function | `kernel/printf.c:157` | `int kfprintf(KFILE *f, const char *fmt, ...)` |
| `ksnprintf` | function | `kernel/printf.c:184` | `int ksnprintf(char *buf, unsigned long size, const char *fmt, ...)` |
| `ksprintf` | function | `kernel/printf.c:166` | `int ksprintf(char *buf, const char *fmt, ...)` |
| `putc_buf` | function | `kernel/printf.c:7` | `static void putc_buf(char c, void *ctx, int *written)` |
| `putc_file` | function | `kernel/printf.c:13` | `static void putc_file(char c, void *ctx, int *written)` |
| `putc_snbuf` | function | `kernel/printf.c:178` | `static void putc_snbuf(char c, void *ctx, int *written)` |
| `putc_str` | function | `kernel/printf.c:19` | `static void putc_str(char c, void *ctx, int *written)` |
| `snctx` | struct | `kernel/printf.c:177` | `` |
| `ERR_EACCES` | macro | `kernel/proc_sec.c:43` | `#define ERR_EACCES` |
| `ERR_EINVAL` | macro | `kernel/proc_sec.c:44` | `#define ERR_EINVAL` |
| `ERR_ENOMEM` | macro | `kernel/proc_sec.c:42` | `#define ERR_ENOMEM` |
| `ERR_ENOSYS` | macro | `kernel/proc_sec.c:45` | `#define ERR_ENOSYS` |
| `ERR_EOPNOTSUPP` | macro | `kernel/proc_sec.c:46` | `#define ERR_EOPNOTSUPP` |
| `LINUX_ERRNO_MAX` | macro | `kernel/proc_sec.c:36` | `#define LINUX_ERRNO_MAX` |
| `LINUX_NR_EXIT` | macro | `kernel/proc_sec.c:35` | `#define LINUX_NR_EXIT` |
| `LINUX_NR_READ` | macro | `kernel/proc_sec.c:32` | `#define LINUX_NR_READ` |
| `LINUX_NR_RT_SIGRETURN` | macro | `kernel/proc_sec.c:34` | `#define LINUX_NR_RT_SIGRETURN` |
| `LINUX_NR_WRITE` | macro | `kernel/proc_sec.c:33` | `#define LINUX_NR_WRITE` |
| `LINUX_PR_GET_DUMPABLE` | macro | `kernel/proc_sec.c:18` | `#define LINUX_PR_GET_DUMPABLE` |
| `LINUX_PR_GET_NAME` | macro | `kernel/proc_sec.c:21` | `#define LINUX_PR_GET_NAME` |
| `LINUX_PR_GET_NO_NEW_PRIVS` | macro | `kernel/proc_sec.c:25` | `#define LINUX_PR_GET_NO_NEW_PRIVS` |
| `LINUX_PR_GET_SECCOMP` | macro | `kernel/proc_sec.c:22` | `#define LINUX_PR_GET_SECCOMP` |
| `LINUX_PR_SET_DUMPABLE` | macro | `kernel/proc_sec.c:19` | `#define LINUX_PR_SET_DUMPABLE` |
| `LINUX_PR_SET_NAME` | macro | `kernel/proc_sec.c:20` | `#define LINUX_PR_SET_NAME` |
| `LINUX_PR_SET_NO_NEW_PRIVS` | macro | `kernel/proc_sec.c:24` | `#define LINUX_PR_SET_NO_NEW_PRIVS` |
| `LINUX_PR_SET_SECCOMP` | macro | `kernel/proc_sec.c:23` | `#define LINUX_PR_SET_SECCOMP` |
| `LINUX_SECCOMP_GET_ACTION_AVAIL` | macro | `kernel/proc_sec.c:31` | `#define LINUX_SECCOMP_GET_ACTION_AVAIL` |
| `LINUX_SECCOMP_MODE_DISABLED` | macro | `kernel/proc_sec.c:26` | `#define LINUX_SECCOMP_MODE_DISABLED` |
| `LINUX_SECCOMP_MODE_FILTER` | macro | `kernel/proc_sec.c:28` | `#define LINUX_SECCOMP_MODE_FILTER` |
| `LINUX_SECCOMP_MODE_STRICT` | macro | `kernel/proc_sec.c:27` | `#define LINUX_SECCOMP_MODE_STRICT` |
| `LINUX_SECCOMP_SET_MODE_FILTER` | macro | `kernel/proc_sec.c:30` | `#define LINUX_SECCOMP_SET_MODE_FILTER` |
| `LINUX_SECCOMP_SET_MODE_STRICT` | macro | `kernel/proc_sec.c:29` | `#define LINUX_SECCOMP_SET_MODE_STRICT` |
| `LINUX_TASK_COMM_LEN` | macro | `kernel/proc_sec.c:37` | `#define LINUX_TASK_COMM_LEN` |
| `SEC_STRICT_LEN` | macro | `kernel/proc_sec.c:72` | `#define SEC_STRICT_LEN` |
| `SOCK_FPROG_FILTER_OFF` | macro | `kernel/proc_sec.c:40` | `#define SOCK_FPROG_FILTER_OFF` |
| `SOCK_FPROG_SIZE` | macro | `kernel/proc_sec.c:39` | `#define SOCK_FPROG_SIZE` |
| `chain_put` | function | `kernel/proc_sec.c:78` | `static void chain_put(sec_filter_t *f)` |
| `pid_ok` | function | `kernel/proc_sec.c:74` | `static int pid_ok(int pid)` |
| `proc_sec_exe` | function | `kernel/proc_sec.c:125` | `const char *proc_sec_exe(int pid)` |
| `proc_sec_exec` | function | `kernel/proc_sec.c:115` | `void proc_sec_exec(int pid)` |
| `proc_sec_filter` | function | `kernel/proc_sec.c:136` | `int proc_sec_filter(long n, long a1, long a2, long a3, long a4, long a5, long a6, long *ret)` |
| `proc_sec_inherit` | function | `kernel/proc_sec.c:87` | `void proc_sec_inherit(int child, int parent)` |
| `proc_sec_prctl` | function | `kernel/proc_sec.c:235` | `long proc_sec_prctl(long option, long a2, long a3, long a4, long a5)` |
| `proc_sec_release` | function | `kernel/proc_sec.c:101` | `void proc_sec_release(int pid)` |
| `proc_sec_seccomp` | function | `kernel/proc_sec.c:290` | `long proc_sec_seccomp(long op, long flags, long uargs)` |
| `proc_sec_set_exe` | function | `kernel/proc_sec.c:119` | `void proc_sec_set_exe(int pid, const char *resolved)` |
| `ref` | type_alias | `kernel/proc_sec.c:47` | `typedef struct sec_filter { int ref;` |
| `sec_filter` | struct | `kernel/proc_sec.c:48` | `` |
| `sec_install` | function | `kernel/proc_sec.c:191` | `static long sec_install(const sbpf_insn *prog, unsigned len, int strict)` |
| `sec_install_user` | function | `kernel/proc_sec.c:224` | `static long sec_install_user(long ufprog)` |
| `sec_kill` | function | `kernel/proc_sec.c:130` | `static void sec_kill(long n, int whole_group)` |
| `expires` | function | `kernel/rcu.c:193` | `* expires (ticks stalled, never a hang). No completion assert is  * possible here by design: a re...` |
| `rcu_cpu_valid` | function | `kernel/rcu.c:40` | `static int rcu_cpu_valid(int cpu)` |
| `rcu_deref` | function | `kernel/rcu.c:88` | `void *rcu_deref(void *volatile *pp)` |
| `rcu_init` | function | `kernel/rcu.c:45` | `void rcu_init(void)` |
| `rcu_me` | function | `kernel/rcu.c:13` | `static cpu_t *rcu_me(void)` |
| `rcu_me` | function | `kernel/rcu.c:17` | `static cpu_t *rcu_me(void)` |
| `rcu_note_idle` | function | `kernel/rcu.c:137` | `void rcu_note_idle(int cpu)` |
| `rcu_note_tick` | function | `kernel/rcu.c:126` | `void rcu_note_tick(int cpu)` |
| `rcu_poll` | function | `kernel/rcu.c:152` | `void rcu_poll(void)` |
| `rcu_publish` | function | `kernel/rcu.c:94` | `void rcu_publish(void *volatile *pp, void *v)` |
| `rcu_read_lock` | function | `kernel/rcu.c:63` | `void rcu_read_lock(void)` |
| `rcu_read_unlock` | function | `kernel/rcu.c:75` | `void rcu_read_unlock(void)` |
| `rcu_slot_t` | struct | `kernel/rcu.c:22` | `` |
| `rcu_state_t` | struct | `kernel/rcu.c:28` | `` |
| `shell_report` | function | `kernel/redirect.c:17` | `void shell_report(const char *what, const char *detail)` |
| `shell_report_exit` | function | `kernel/redirect.c:11` | `void shell_report_exit(int code)` |
| `shell_take_redirect` | function | `kernel/redirect.c:25` | `int shell_take_redirect(int *argc, char **argv, char **path, int *append_mode)` |
| `BSP` | function | `kernel/sched.c:1780` | `* CPU believe it is the BSP (wrong per-CPU identity, two CPUs          * running the shell contex...` |
| `FSBASE` | function | `kernel/sched.c:913` | `* for FSBASE (per-proc TLS): a thread preempted after arch_prctl * would otherwise resume with whatever base the...` |
| `IRQ4` | function | `kernel/sched.c:796` | `* IRQ4 (COM1, UART IER stays 0 so it never fires) + * IRQ5 (Sound Blaster 16 DMA done). In the mask register a bit...` |
| `KSTACK_CANARY` | macro | `kernel/sched.c:169` | `#define KSTACK_CANARY` |
| `KSTACK_PAINT` | macro | `kernel/sched.c:168` | `#define KSTACK_PAINT` |
| `KSTACK_SZ` | macro | `kernel/sched.c:155` | `#define KSTACK_SZ` |
| `MSR` | function | `kernel/sched.c:2633` | `* in the MSR (the PCB field refreshes on switch-out) and its FPU * regs live in the CPU (the PCB image refreshes on...` |
| `MXCSR` | function | `kernel/sched.c:306` | `* A fresh image is explicit zeros plus the default MXCSR (0x1F80, all  * exceptions masked): fxsa...` |
| `MY_SYS_KSTK_TOP` | macro | `kernel/sched.c:53` | `#define MY_SYS_KSTK_TOP` |
| `MY_USER_LOAD_BASE` | macro | `kernel/sched.c:55` | `#define MY_USER_LOAD_BASE` |
| `MY_USER_STACK_TOP` | macro | `kernel/sched.c:54` | `#define MY_USER_STACK_TOP` |
| `NMI_IST_SLOT` | macro | `kernel/sched.c:125` | `#define NMI_IST_SLOT` |
| `NMI_IST_STACK_SZ` | macro | `kernel/sched.c:123` | `#define NMI_IST_STACK_SZ` |
| `NMI_VECTOR` | macro | `kernel/sched.c:124` | `#define NMI_VECTOR` |
| `PROC_KSTACK_OFF` | function | `kernel/sched.c:82` | `* PROC_KSTACK_OFF (it cannot use C here). The asm derives both * immediates from headers/syscall_asm.h, so this...` |
| `PROC_SWITCHING` | function | `kernel/sched.c:2180` | `* while the thread is still PROC_SWITCHING (never claimable), * then set the resume point and publish. A...` |
| `__attribute__` | function | `kernel/sched.c:109` | `typedef struct __attribute__((packed))` |
| `__attribute__` | function | `kernel/sched.c:143` | `typedef struct __attribute__((packed))` |
| `adopt` | function | `kernel/sched.c:2922` | `* adopt (armed by Linux O_CLOEXEC on open);` |
| `alloc_kstack` | function | `kernel/sched.c:262` | `static uint64_t alloc_kstack(void)` |
| `alloc_pid_locked` | function | `kernel/sched.c:3180` | `static int alloc_pid_locked(void)` |
| `aslr_brk_pages` | function | `kernel/sched.c:2897` | `unsigned long aslr_brk_pages(void)` |
| `aslr_dyn_base` | function | `kernel/sched.c:2899` | `unsigned long aslr_dyn_base(void)` |
| `aslr_mix` | function | `kernel/sched.c:2887` | `static unsigned long aslr_mix(unsigned long salt)` |
| `aslr_mmap_pages` | function | `kernel/sched.c:2898` | `unsigned long aslr_mmap_pages(void)` |
| `aslr_stack_bytes` | function | `kernel/sched.c:2896` | `unsigned long aslr_stack_bytes(void)` |
| `cli` | function | `kernel/sched.c:2908` | `* cli (disk PIO must never run with the timer held off);` |
| `context` | function | `kernel/sched.c:888` | `* context (anything entered via k_exec_user) is inside a syscall  * (entry swapped 0 in), and a c...` |
| `copy` | function | `kernel/sched.c:362` | `* copy (fail closed, fork refuses) instead of forging pointers. */ /* Name the link a fork could ...` |
| `ctx_from_frame` | function | `kernel/sched.c:2537` | `static void ctx_from_frame(ctx_regs_t *c, const syscall_frame_t *f)` |

Next: [SYMBOLS_p9.md](SYMBOLS_p9.md)
