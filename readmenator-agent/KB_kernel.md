# Subsystem: kernel (page 1 of 4)
Pages: [KB_kernel.md](KB_kernel.md), [KB_kernel_p2.md](KB_kernel_p2.md), [KB_kernel_p3.md](KB_kernel_p3.md), [KB_kernel_p4.md](KB_kernel_p4.md)

## kernel/abi.c
- Doc: Docstring: kernel/abi.c -- Boot-time ABI manifest gate.
- Layer: utility
- Language: c
- Symbols:
  - `abi_parse_num` (function, line 20) `static int abi_parse_num(const char **pp, const char *end, unsigned long *out)`
  - `abi_verify` (function, line 38) `int abi_verify(const char *text, long version, unsigned long checksum)`
  - `abi_check_manifest` (function, line 74) `int abi_check_manifest(void)`
- Depends on: `headers/abi.h`

## kernel/batch.c
- Doc: Docstring: kernel/batch.c -- Ordered batch executor.
- Layer: utility
- Language: c
- Symbols:
  - `batch_exec` (function, line 19) `long batch_exec(const batch_op_t *ops, long *results, int count,
                int *completed, ...`
- Depends on: `headers/batch.h`

## kernel/clip.c
- Doc: Docstring: kernel/clip.c -- Shared text clipboard.
- Layer: utility
- Language: c
- Symbols:
  - `clip_set` (function, line 25) `int clip_set(const char *data, unsigned long len)`
  - `clip_clear` (function, line 48) `void clip_clear(void)`
  - `clip_len_get` (function, line 55) `int clip_len_get(void)`
  - `CLIP_MAX` (macro, line 17) `#define CLIP_MAX`

## kernel/console.c
- Doc: Execution-context output: text console, capture, libc names.
- Layer: utility
- Language: c
- Symbols:
  - `vga_get_x` (function, line 18) `int vga_get_x(void)`
  - `vga_get_y` (function, line 19) `int vga_get_y(void)`
  - `vga_set_xy` (function, line 20) `void vga_set_xy(int x, int y)`
  - `vga_get_color` (function, line 21) `char vga_get_color(void)`
  - `vga_offset` (function, line 23) `static inline unsigned vga_offset(int x, int y)`
  - `vga_clear` (function, line 25) `void vga_clear(void)`
  - `vga_set_cursor` (function, line 36) `void vga_set_cursor(int x, int y)`
  - `vga_scroll` (function, line 56) `void vga_scroll(void)`
  - `vga_newline` (function, line 75) `void vga_newline(void)`
  - `vga_cursor_enable` (function, line 81) `void vga_cursor_enable(int on)`
  - `vga_raw_space` (function, line 88) `static void vga_raw_space(void)`
  - `redir_grow` (function, line 110) `static int redir_grow(void)`
  - `redirect_active` (function, line 120) `int redirect_active(void)`
  - `redirect_putc` (function, line 122) `static int redirect_putc(char c)`
  - `redirect_suspend` (function, line 129) `int redirect_suspend(void)`
  - `redirect_resume` (function, line 135) `void redirect_resume(int was)`
  - `redirect_begin` (function, line 139) `int redirect_begin(void)`
  - `redirect_commit` (function, line 147) `int redirect_commit(const char *path, int append_mode)`
  - `redirect_pending` (function, line 185) `unsigned long redirect_pending(void)`
  - `redirect_take_into` (function, line 196) `unsigned long redirect_take_into(char *dst, unsigned long cap,
        unsigned long *len_out)`
  - `redirect_discard` (function, line 216) `void redirect_discard(void)`
  - `vga_putc` (function, line 223) `void vga_putc(char c)`
  - `vga_puts` (function, line 267) `void vga_puts(const char *s)`
  - `register_libc_symbols` (function, line 271) `void register_libc_symbols(void)`
  - `XXH_STATIC_LINKING_ONLY` (macro, line 4) `#define XXH_STATIC_LINKING_ONLY`
  - `REDIR_INITIAL_CAP` (macro, line 96) `#define REDIR_INITIAL_CAP`
  - `REDIR_MAX_BYTES` (macro, line 97) `#define REDIR_MAX_BYTES`
- Depends on: `headers/sched.h`, `headers/vga_fb.h`

## kernel/console_in.c
- Doc: Docstring: Console input device (kernel/console_in.c).
- Layer: utility
- Language: c
- Symbols:
  - `console_stdin_push` (function, line 32) `int console_stdin_push(const char *data, unsigned long len)`
  - `console_stdin_clear` (function, line 46) `void console_stdin_clear(void)`
  - `console_stdin_active` (function, line 56) `int console_stdin_active(void)`
  - `pb_empty` (function, line 60) `static int pb_empty(void)`
  - `pb_count` (function, line 61) `static int pb_count(void)`
  - `pb_push_back` (function, line 62) `static void pb_push_back(unsigned char c)`
  - `pb_push_front` (function, line 67) `static void pb_push_front(unsigned char c)`
  - `pb_pop` (function, line 72) `static int pb_pop(void)`
  - `pb_peek` (function, line 78) `static int pb_peek(void)`
  - `console_ungetc` (function, line 85) `void console_ungetc(unsigned char c)`
  - `console_poll_usb` (function, line 93) `static void console_poll_usb(void)`
  - `console_ps2_live` (function, line 106) `static int console_ps2_live(void)`
  - `raw_blocking_getc` (function, line 118) `static int raw_blocking_getc(void)`
  - `raw_try_getc` (function, line 139) `static int raw_try_getc(void)`
  - `ESC` (function, line 157) `* The bound keeps a bare ESC (never completed into a sequence) from
 * hanging the reader. */
#de...`
  - `consume_page_after_esc` (function, line 178) `static int consume_page_after_esc(void)`
  - `console_getc` (function, line 205) `int console_getc(void)`
  - `console_peek` (function, line 233) `int console_peek(void)`
  - `console_raw_try` (function, line 246) `int console_raw_try(void)`
  - `console_raw_get` (function, line 250) `int console_raw_get(void)`
  - `console_job_try` (function, line 257) `int console_job_try(void)`
  - `console_job_get` (function, line 267) `int console_job_get(void)`
  - `scrollback_render` (function, line 283) `static void scrollback_render(int voff, int total, const unsigned char *saved)`
  - `sb_next` (function, line 311) `static int sb_next(void)`
  - `scrollback_view` (function, line 321) `static void scrollback_view(int initial_dir)`
  - `PB_LEN` (macro, line 18) `#define PB_LEN`
  - `MAX_SEQ_POLL` (macro, line 159) `#define MAX_SEQ_POLL`
  - `SB_LEN` (macro, line 281) `#define SB_LEN`
  - `SB_PGUP` (macro, line 304) `#define SB_PGUP`
  - `SB_PGDN` (macro, line 305) `#define SB_PGDN`
  - `SB_EXIT` (macro, line 306) `#define SB_EXIT`
- Depends on: `headers/drivers/kbd.h`, `headers/drivers/usbhid.h`, `headers/drivers/xhci.h`, `headers/kernel/console_in.h`, `headers/pipe.h`, `headers/vga_fb.h`

## kernel/cvm_host.c
- Layer: utility
- Language: c
- Symbols:
  - `n_strcmp` (function, line 22) `static int64_t n_strcmp(void *vm, int ac, uint64_t *av)`
  - `n_strncmp` (function, line 28) `static int64_t n_strncmp(void *vm, int ac, uint64_t *av)`
  - `n_strcpy` (function, line 35) `static int64_t n_strcpy(void *vm, int ac, uint64_t *av)`
  - `n_strncpy` (function, line 41) `static int64_t n_strncpy(void *vm, int ac, uint64_t *av)`
  - `n_memcpy` (function, line 48) `static int64_t n_memcpy(void *vm, int ac, uint64_t *av)`
  - `n_memset` (function, line 55) `static int64_t n_memset(void *vm, int ac, uint64_t *av)`
  - `n_memmove` (function, line 61) `static int64_t n_memmove(void *vm, int ac, uint64_t *av)`
  - `n_memcmp` (function, line 68) `static int64_t n_memcmp(void *vm, int ac, uint64_t *av)`
  - `n_strchr` (function, line 75) `static int64_t n_strchr(void *vm, int ac, uint64_t *av)`
  - `n_strstr` (function, line 81) `static int64_t n_strstr(void *vm, int ac, uint64_t *av)`
  - `n_malloc` (function, line 88) `static int64_t n_malloc(void *vm, int ac, uint64_t *av)`
  - `n_free` (function, line 93) `static int64_t n_free(void *vm, int ac, uint64_t *av)`
  - `n_calloc` (function, line 98) `static int64_t n_calloc(void *vm, int ac, uint64_t *av)`
  - `n_realloc` (function, line 106) `static int64_t n_realloc(void *vm, int ac, uint64_t *av)`
  - `n_exit` (function, line 114) `static int64_t n_exit(void *vm, int ac, uint64_t *av)`
  - `n_fopen` (function, line 121) `static int64_t n_fopen(void *vm, int ac, uint64_t *av)`
  - `n_fclose` (function, line 128) `static int64_t n_fclose(void *vm, int ac, uint64_t *av)`
  - `n_fread` (function, line 134) `static int64_t n_fread(void *vm, int ac, uint64_t *av)`
  - `n_fwrite` (function, line 141) `static int64_t n_fwrite(void *vm, int ac, uint64_t *av)`
  - `n_fseek` (function, line 148) `static int64_t n_fseek(void *vm, int ac, uint64_t *av)`
  - `n_ftell` (function, line 154) `static int64_t n_ftell(void *vm, int ac, uint64_t *av)`
  - `n_rewind` (function, line 160) `static int64_t n_rewind(void *vm, int ac, uint64_t *av)`
  - `n_fputs` (function, line 167) `static int64_t n_fputs(void *vm, int ac, uint64_t *av)`
  - `n_fputc` (function, line 173) `static int64_t n_fputc(void *vm, int ac, uint64_t *av)`
  - `n_fgetc` (function, line 179) `static int64_t n_fgetc(void *vm, int ac, uint64_t *av)`
  - `n_ungetc` (function, line 185) `static int64_t n_ungetc(void *vm, int ac, uint64_t *av)`
  - `n_fflush` (function, line 191) `static int64_t n_fflush(void *vm, int ac, uint64_t *av)`
  - `n_putchar` (function, line 197) `static int64_t n_putchar(void *vm, int ac, uint64_t *av)`
  - `n_write` (function, line 204) `static int64_t n_write(void *vm, int ac, uint64_t *av)`
  - `n_read` (function, line 213) `static int64_t n_read(void *vm, int ac, uint64_t *av)`
  - `n_puts` (function, line 228) `static int64_t n_puts(void *vm, int ac, uint64_t *av)`
  - `n_atol` (function, line 236) `static int64_t n_atol(void *vm, int ac, uint64_t *av)`
  - `n_strtol` (function, line 249) `static int64_t n_strtol(void *vm, int ac, uint64_t *av)`
  - `n_stderr_addr` (function, line 262) `static int64_t n_stderr_addr(void *vm, int ac, uint64_t *av)`
  - `n_stdout_addr` (function, line 267) `static int64_t n_stdout_addr(void *vm, int ac, uint64_t *av)`
  - `n_stdin_addr` (function, line 272) `static int64_t n_stdin_addr(void *vm, int ac, uint64_t *av)`
  - `kout_char` (function, line 277) `static void kout_char(void *ctx, char c)`
  - `kout_uint` (function, line 283) `static void kout_uint(void *ctx, unsigned long long v, int base, int upper)`
  - `kformat` (function, line 296) `static void kformat(void *ctx, const char *fmt, uint64_t *argv, int argc)`
  - `n_fprintf` (function, line 362) `static int64_t n_fprintf(void *vm, int ac, uint64_t *av)`
  - `n_printf` (function, line 369) `static int64_t n_printf(void *vm, int ac, uint64_t *av)`
  - `n_sprintf` (function, line 376) `static int64_t n_sprintf(void *vm, int ac, uint64_t *av)`
  - `n_snprintf` (function, line 384) `static int64_t n_snprintf(void *vm, int ac, uint64_t *av)`
  - `register_host_natives` (function, line 392) `static void register_host_natives(CvmState *vm)`
  - `cvm_main` (function, line 437) `int cvm_main(int argc, char **argv)`

## kernel/ed25519.c
- Doc: Docstring: kernel/ed25519.c -- Ed25519 signature verification.
- Layer: utility
- Language: c
- Symbols:
  - `ed_fe` (struct, line 28)
  - `ed_ge` (struct, line 32)
  - `ed_u64` (type_alias, line 23) `typedef unsigned long long ed_u64;`
  - `ed_rotr` (function, line 84) `static ed_u64 ed_rotr(ed_u64 x, unsigned n)`
  - `ed_sha_block` (function, line 89) `static void ed_sha_block(ed_sha *c, const unsigned char *p)`
  - `ed_sha512_init` (function, line 147) `void ed_sha512_init(ed_sha *c)`
  - `ed_sha512_update` (function, line 162) `void ed_sha512_update(ed_sha *c, const unsigned char *data, unsigned long len)`
  - `ed_sha512_final` (function, line 188) `void ed_sha512_final(ed_sha *c, unsigned char out[64])`
  - `ed_fe_copy` (function, line 214) `static void ed_fe_copy(ed_fe *r, const ed_fe *a)`
  - `ed_fe_zero` (function, line 222) `static void ed_fe_zero(ed_fe *r)`
  - `ed_fe_one` (function, line 230) `static void ed_fe_one(ed_fe *r)`
  - `ed_fe_cmov` (function, line 238) `static void ed_fe_cmov(ed_fe *r, const ed_fe *b, unsigned flag)`
  - `ed_fe_ge` (function, line 247) `static unsigned ed_fe_ge(const ed_fe *a, const ed_fe *b)`
  - `ed_fe_rawsub` (function, line 258) `static void ed_fe_rawsub(ed_fe *r, const ed_fe *a, const ed_fe *b)`
  - `ed_fe_add` (function, line 280) `static void ed_fe_add(ed_fe *r, const ed_fe *a, const ed_fe *b)`
  - `ed_fe_sub` (function, line 302) `static void ed_fe_sub(ed_fe *r, const ed_fe *a, const ed_fe *b)`
  - `ed_fe_fold` (function, line 344) `static void ed_fe_fold(ed_fe *r, ed_u64 w[8])`
  - `ed_fe_mul` (function, line 387) `static void ed_fe_mul(ed_fe *r, const ed_fe *a, const ed_fe *b)`
  - `ed_fe_sq` (function, line 416) `static void ed_fe_sq(ed_fe *r, const ed_fe *a)`
  - `ed_fe_pow` (function, line 421) `static void ed_fe_pow(ed_fe *r, const ed_fe *a, const unsigned char *bits, unsigned nbits)`
  - `ed_fe_inv` (function, line 438) `static void ed_fe_inv(ed_fe *r, const ed_fe *a)`
  - `ed_fe_frombytes` (function, line 449) `static void ed_fe_frombytes(ed_fe *r, const unsigned char b[32])`
  - `ed_fe_tobytes` (function, line 461) `static void ed_fe_tobytes(unsigned char b[32], const ed_fe *a)`
  - `ed_fe_eq` (function, line 470) `static unsigned ed_fe_eq(const ed_fe *a, const ed_fe *b)`
  - `ed_bytes_lt_q` (function, line 477) `static unsigned ed_bytes_lt_q(const unsigned char b[32])`
  - `ed_scalar_lt_l` (function, line 495) `static unsigned ed_scalar_lt_l(const unsigned char b[32])`
  - `ed_rem_sub` (function, line 517) `static void ed_rem_sub(ed_u64 r[5], const ed_u64 a[5], const ed_u64 b[5])`
  - `ed_rem_ge` (function, line 545) `static unsigned ed_rem_ge(const ed_u64 a[5], const ed_u64 b[5])`
  - `ed_mod_l` (function, line 557) `static void ed_mod_l(ed_fe *r, const unsigned char h[64])`
  - `ed_ge_copy` (function, line 596) `static void ed_ge_copy(ed_ge *r, const ed_ge *a)`
  - `ed_ge_cmov` (function, line 604) `static void ed_ge_cmov(ed_ge *r, const ed_ge *b, unsigned flag)`
  - `ed_ge_add` (function, line 612) `static void ed_ge_add(ed_ge *r, const ed_ge *p, const ed_ge *q, const ed_fe *d2)`
  - `ed_ge_double` (function, line 644) `static void ed_ge_double(ed_ge *r, const ed_ge *p)`
  - `ed_ge_scalarmult` (function, line 686) `static void ed_ge_scalarmult(ed_ge *r, const ed_ge *p, const unsigned char s[32],
               ...`
  - `ed_curve_d` (function, line 706) `static void ed_curve_d(ed_fe *d)`
  - `ed25519_verify` (function, line 810) `int ed25519_verify(const unsigned char sig[64], const unsigned char *msg,
                   unsi...`
- Depends on: `headers/sign.h`

## kernel/editor.c
- Doc: edit_list: List a (possibly empty) range [start, end], both 1-based inclusive.
- Layer: utility
- Language: c
- Symbols:
  - `EditLine` (struct, line 24)
  - `EditBuf` (struct, line 29)
  - `edit_alloc` (function, line 38) `static EditBuf *edit_alloc(const char *fname)`
  - `edit_free` (function, line 55) `static void edit_free(EditBuf *e)`
  - `edit_load` (function, line 61) `static int edit_load(EditBuf *e)`
  - `edit_save` (function, line 99) `static int edit_save(EditBuf *e)`
  - `edit_print` (function, line 113) `static void edit_print(EditBuf *e, int idx)`
  - `edit_list` (function, line 123) `static void edit_list(EditBuf *e, int start, int end)`
  - `edit_set_line` (function, line 135) `static int edit_set_line(EditBuf *e, int idx, const char *text)`
  - `edit_insert` (function, line 144) `static int edit_insert(EditBuf *e, int idx, const char *text)`
  - `edit_delete` (function, line 154) `static int edit_delete(EditBuf *e, int idx)`
  - `edit_line_cstr` (function, line 166) `static void edit_line_cstr(EditLine *l, char *out)`
  - `edit_search` (function, line 171) `static void edit_search(EditBuf *e, const char *needle)`
  - `edit_status` (function, line 188) `static void edit_status(EditBuf *e)`
  - `edit_usage` (function, line 196) `static void edit_usage(void)`
  - `edit_refuse_save` (function, line 207) `static int edit_refuse_save(EditBuf *e)`
  - `edit_arg_line` (function, line 213) `static int edit_arg_line(int argc, char **argv, EditBuf *e, int *out)`
  - `edit_loop` (function, line 224) `static void edit_loop(EditBuf *e)`
  - `shell_cmd_edit` (function, line 329) `void shell_cmd_edit(int argc, char **argv)`
  - `EDIT_MAX_LINES` (macro, line 20) `#define EDIT_MAX_LINES`
  - `EDIT_LINE_MAX` (macro, line 21) `#define EDIT_LINE_MAX`
  - `EDIT_FILE_MAX` (macro, line 22) `#define EDIT_FILE_MAX`
- Depends on: `headers/editor.h`, `headers/shell.h`

## kernel/exec.c
- Doc: Process execution: setjmp/longjmp, k_exec_user, k_run_rel, kexit.
- Layer: utility
- Language: c
- Symbols:
  - `vga_mode_set` (function, line 61) `void vga_mode_set(int on)`
  - `vga_mode_is_active` (function, line 62) `int  vga_mode_is_active(void)`
  - `vga_gfx_ran_set` (function, line 63) `void vga_gfx_ran_set(int on)`
  - `k_user_fault_return` (function, line 66) `void k_user_fault_return(void)`
  - `setup_user_stack` (function, line 83) `unsigned long *setup_user_stack(char *sbase, unsigned long ssize,
                               ...`
  - `k_run_rel` (function, line 233) `int k_run_rel(prog_entry_t entry, int argc, char **argv)`
  - `kexit` (function, line 284) `void kexit(int code)`
  - `syscall_kstack` (variable, line 116) `extern unsigned long syscall_kstack;`
  - `EXEC_KSTACK_SZ` (macro, line 124) `#define EXEC_KSTACK_SZ`
  - `ETREL_CHILD_STACK_SZ` (macro, line 133) `#define ETREL_CHILD_STACK_SZ`
- Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/arch/x86/msr.h`, `headers/drivers/kbd.h`, `headers/proc_sec.h`, `headers/sched.h`, `headers/vga_fb.h`

## kernel/futex.c
- Doc: Docstring: kernel/futex.c -- Kernel side of the futex contract.
- Layer: utility
- Language: c
- Symbols:
  - `futex_table_t` (struct, line 16)
  - `futex_hash` (function, line 23) `static unsigned long futex_hash(unsigned long uaddr)`
  - `futex_bucket` (function, line 31) `static futex_bucket_t *futex_bucket(unsigned long uaddr)`
  - `futex_init` (function, line 36) `void futex_init(void)`
  - `futex_unlink_locked` (function, line 50) `static void futex_unlink_locked(futex_bucket_t *b, int pid)`
  - `futex_forget` (function, line 76) `void futex_forget(int pid)`
  - `futex_linux_cmd` (function, line 128) `int futex_linux_cmd(long op)`
  - `futex_timeout_remaining_us` (function, line 139) `long futex_timeout_remaining_us(int cmd, long sec, long nsec, unsigned long now_us)`
  - `futex_wake` (function, line 158) `long futex_wake(unsigned long uaddr, int n)`
  - `t_cur_pid` (variable, line 13) `extern int t_cur_pid;`
- Depends on: `headers/futex.h`, `headers/sync.h`

## kernel/klog.c
- Doc: Structured kernel logging with levels and subsystems.
- Layer: utility
- Language: c
- Symbols:
  - `klog_set_level` (function, line 29) `void klog_set_level(log_level_t level)`
  - `klog_set_subsys_level` (function, line 33) `void klog_set_subsys_level(log_subsystem_t subsys, log_level_t level)`
  - `klog_disable` (function, line 38) `void klog_disable(void)`
  - `klog_enable` (function, line 39) `void klog_enable(void)`
  - `klog` (function, line 41) `void klog(log_level_t level, log_subsystem_t subsys,
          const char *fmt, ...)`
  - `klog_hexdump` (function, line 119) `void klog_hexdump(log_level_t level, log_subsystem_t subsys,
                  const void *data, ...`

## kernel/ldso_parse.c
- Doc: Docstring: kernel/ldso_parse.c -- pure dynamic-table parsing (T8 ld.so).
- Layer: utility
- Language: c
- Symbols:
  - `ldso_rd16` (function, line 18) `static unsigned ldso_rd16(const unsigned char *p)`
  - `ldso_rd32` (function, line 22) `static unsigned long ldso_rd32(const unsigned char *p)`
  - `ldso_rd64` (function, line 27) `static unsigned long long ldso_rd64(const unsigned char *p)`
  - `ldso_slice` (function, line 32) `static int ldso_slice(const unsigned char *file, unsigned long long fsize,
        unsigned long ...`
  - `ldso_valid_ehdr` (function, line 40) `static int ldso_valid_ehdr(const unsigned char *file,
        unsigned long long fsize)`
  - `ldso_vaddr_to_offset` (function, line 54) `int ldso_vaddr_to_offset(const unsigned char *file,
        unsigned long long fsize, unsigned lo...`
  - `ldso_segments` (function, line 86) `int ldso_segments(const unsigned char *file, unsigned long long fsize,
        LdsoSeg *segs, uns...`
  - `ldso_find_dynamic` (function, line 120) `int ldso_find_dynamic(const unsigned char *file, unsigned long long fsize,
        unsigned long ...`
  - `ldso_scan_dynamic` (function, line 150) `int ldso_scan_dynamic(const unsigned char *file, unsigned long long fsize,
        unsigned long ...`
  - `ldso_sym_count` (function, line 213) `int ldso_sym_count(const unsigned char *file, unsigned long long fsize,
        unsigned long lon...`
  - `ldso_copy_str` (function, line 227) `int ldso_copy_str(const unsigned char *file, unsigned long long fsize,
        unsigned long long...`
  - `ldso_name_eq` (function, line 250) `static int ldso_name_eq(const unsigned char *tab, unsigned long long strsz,
        unsigned long...`
  - `ldso_sym_lookup` (function, line 263) `int ldso_sym_lookup(const unsigned char *file, unsigned long long fsize,
        unsigned long lo...`
  - `ldso_rela_count` (function, line 296) `int ldso_rela_count(const LdsoDynInfo *info, unsigned *nrela)`
  - `ldso_read_rela` (function, line 309) `int ldso_read_rela(const unsigned char *file, unsigned long long fsize,
        unsigned long lon...`
  - `ldso_basename` (function, line 331) `void ldso_basename(char *out, const char *src)`
  - `LDSO_EHSIZE` (macro, line 13) `#define LDSO_EHSIZE`
  - `LDSO_PHENTSZ` (macro, line 14) `#define LDSO_PHENTSZ`
  - `LDSO_DYN_ENT` (macro, line 15) `#define LDSO_DYN_ENT`
  - `LDSO_HASH_HDR` (macro, line 16) `#define LDSO_HASH_HDR`
- Depends on: `headers/ldso.h`
- Imported by: `tests/test_ldso.c`

## kernel/loader.c
- Doc: ldso_read_file: Read a whole library file by DT_NEEDED name: exact path first, then the...
- Layer: utility
- Language: c
- Symbols:
  - `exec_range` (struct, line 104)
  - `Elf64_Shdr` (struct, line 23)
  - `Elf64_Sym` (struct, line 36)
  - `Elf64_Rela` (struct, line 45)
  - `Elf64_Phdr` (struct, line 51)
  - `LdsoLibEnt` (struct, line 388)
  - `elf_name_copy` (function, line 114) `static void elf_name_copy(char *out, unsigned out_cap, const char *tab,
                         ...`
  - `elf_load_fail` (function, line 128) `static void elf_load_fail(void *base, void **sec_addrs, const char *why)`
  - `elf_load` (function, line 136) `void *elf_load(void *data, unsigned size, void **base_out)`
  - `ldso_pseudo_stat` (function, line 402) `int ldso_pseudo_stat(int ino, unsigned long *size_out)`
  - `ldso_pseudo_read` (function, line 416) `int ldso_pseudo_read(int ino, void *dst, unsigned long off, unsigned len)`
  - `ldso_read_file` (function, line 441) `static int ldso_read_file(const char *name, unsigned char **out,
        unsigned *size_out)`
  - `ldso_ensure_slot` (function, line 483) `static int ldso_ensure_slot(const char *needed, int *slot_out)`
  - `consistent` (function, line 579) `* consistent (the next exec forgets them, a dying window frees them),
 * and only reports. */
sta...`
  - `ldso_bind_into` (function, line 794) `int ldso_bind_into(void *data, unsigned size, unsigned long base,
        unsigned long cr3, vma_...`
  - `apply_exec_relocs` (function, line 984) `static void apply_exec_relocs(void *data, unsigned size, unsigned long base,
                    ...`
  - `elf_note_pad` (function, line 1072) `static unsigned long elf_note_pad(unsigned long n)`
  - `elf_sign_note_span` (function, line 1083) `static int elf_sign_note_span(const unsigned char *img, unsigned long off,
                      ...`
  - `elf_sign_note_find` (function, line 1108) `static int elf_sign_note_find(const unsigned char *img, unsigned size,
                          ...`
  - `elf_sign_section_find` (function, line 1132) `static int elf_sign_section_find(const unsigned char *img, unsigned size,
                       ...`
  - `elf_sign_u64` (function, line 1172) `static void elf_sign_u64(ed_sha *c, unsigned long v)`
  - `elf_sign_u32` (function, line 1181) `static void elf_sign_u32(ed_sha *c, unsigned v)`
  - `load_exec_elf` (function, line 1262) `void *load_exec_elf(void *data, unsigned size)`
  - `base_out` (function, line 1395) `* the link base via base_out (0 when the caller runs static images
 * only: the dynamic binder ne...`
  - `elf_wants_process` (function, line 1432) `int elf_wants_process(const void *data, unsigned size)`
  - `load_exec_elf_into` (function, line 1456) `void *load_exec_elf_into(void *data, unsigned size, unsigned long cr3,
                         u...`
  - `inodes` (function, line 381) `* Pseudo inodes (LDSO_INO_BASE + slot) keep registry pages apart from * MiniFS inodes in the shared cache. No unload...`
  - `images` (function, line 790) `* Static images (no dynamic section, or none needed) return 0 at * once, so the legacy paths never observe a...`
  - `process` (function, line 1288) `* atomic section: a 100 Hz tick between two segments would switch * CR3 into another process (copies landing in its...`
  - `time` (function, line 1520) `* time (with the failing offset);`
  - `ELF64_R_SYM` (macro, line 62) `#define ELF64_R_SYM(i)`
  - `ELF64_R_TYPE` (macro, line 63) `#define ELF64_R_TYPE(i)`
  - `SHN_UNDEF` (macro, line 64) `#define SHN_UNDEF`
  - `ETREL_IMAGE_MAX` (macro, line 71) `#define ETREL_IMAGE_MAX`
  - `SHT_SYMTAB` (macro, line 73) `#define SHT_SYMTAB`
  - `SHT_STRTAB` (macro, line 74) `#define SHT_STRTAB`
  - `SHT_RELA` (macro, line 75) `#define SHT_RELA`
  - `SHT_PROGBITS` (macro, line 76) `#define SHT_PROGBITS`
  - `SHT_NOBITS` (macro, line 77) `#define SHT_NOBITS`
  - `SHF_ALLOC` (macro, line 78) `#define SHF_ALLOC`
  - `SHF_EXECINSTR` (macro, line 79) `#define SHF_EXECINSTR`
  - `EM_X86_64` (macro, line 81) `#define EM_X86_64`
  - `PT_LOAD` (macro, line 82) `#define PT_LOAD`
  - `PT_NOTE` (macro, line 83) `#define PT_NOTE`
  - `ELF_NOTE_HDR` (macro, line 87) `#define ELF_NOTE_HDR`
  - `ELF_NOTE_ALIGN` (macro, line 88) `#define ELF_NOTE_ALIGN`
  - `R_X86_64_64` (macro, line 90) `#define R_X86_64_64`
  - `R_X86_64_PC32` (macro, line 91) `#define R_X86_64_PC32`
  - `R_X86_64_PLT32` (macro, line 92) `#define R_X86_64_PLT32`
  - `R_X86_64_GLOB_DAT` (macro, line 93) `#define R_X86_64_GLOB_DAT`
  - `R_X86_64_JUMP_SLOT` (macro, line 94) `#define R_X86_64_JUMP_SLOT`
  - `R_X86_64_RELATIVE` (macro, line 95) `#define R_X86_64_RELATIVE`
  - `R_X86_64_32` (macro, line 96) `#define R_X86_64_32`
  - `R_X86_64_32S` (macro, line 97) `#define R_X86_64_32S`
  - `R_X86_64_IRELATIVE` (macro, line 98) `#define R_X86_64_IRELATIVE`
  - `PF_X` (macro, line 100) `#define PF_X`
  - `ELF_MAX_SEGMENTS` (macro, line 101) `#define ELF_MAX_SEGMENTS`
  - `ELF_NAME_MAX` (macro, line 102) `#define ELF_NAME_MAX`
  - `SHT_NOTE` (macro, line 1067) `#define SHT_NOTE`
  - `SIGN_NOTE_NAME` (macro, line 1069) `#define SIGN_NOTE_NAME`
- Depends on: `headers/ldso.h`, `headers/minifs.h`, `headers/pcache.h`, `headers/sched.h`, `headers/sign.h`, `headers/vga_fb.h`

## kernel/lz4_kernel.c
- Layer: utility
- Language: c
- Symbols:
  - `LZ4_read32` (function, line 7) `static inline unsigned int LZ4_read32(const unsigned char *p)`
  - `LZ4_read16` (function, line 14) `static inline unsigned int LZ4_read16(const unsigned char *p)`
  - `LZ4_write16` (function, line 21) `static inline void LZ4_write16(unsigned char *dst, unsigned short v)`
  - `LZ4_hash` (function, line 26) `static unsigned int LZ4_hash(const unsigned char *p)`
  - `LZ4_compressBound` (function, line 33) `int LZ4_compressBound(int inputSize)`
  - `LZ4_compress_default` (function, line 40) `int LZ4_compress_default(const char *src, char *dst, int srcSize, int dstCapacity)`
  - `LZ4_decompress_safe` (function, line 176) `int LZ4_decompress_safe(const char *src, char *dst, int compressedSize, int dstCapacity)`
  - `slots` (function, line 43) `* runs from file writes on 16 KB proc slots (stack discipline, * CLAUDE.md). OOM returns 0 and the caller stores...`
  - `HASH_BITS` (macro, line 4) `#define HASH_BITS`
  - `HASH_SIZE` (macro, line 5) `#define HASH_SIZE`
- Depends on: `headers/lz4_kernel.h`

## kernel/minifetch.c
- Doc: Docstring: kernel/minifetch.c -- neofetch-style system screen.
- Layer: utility
- Language: c
- Symbols:
  - `minifetch_cfg` (struct, line 21)
  - `minifetch_row` (function, line 57) `static void minifetch_row(const unsigned char *img, int w, int h, int row,
                      ...`
  - `minifetch_logo` (function, line 81) `static void minifetch_logo(char rows[16][33])`
  - `minifetch_specs` (function, line 101) `static int minifetch_specs(char lines[20][96])`
  - `shell_cmd_minifetch` (function, line 156) `void shell_cmd_minifetch(void)`
  - `frame` (function, line 159) `* frame (stack discipline, CLAUDE.md). Fail-closed on OOM. */ char (*specs)[96] = (char (*)[96])kmalloc(20 * 96);`
- Depends on: `headers/minifetch.h`, `headers/minifs.h`, `headers/net.h`, `headers/rtc.h`, `headers/sched.h`, `headers/vga_fb.h`

## kernel/mm.c
- Doc: kheap_ram_top: RAM top from the CMOS extended-memory count (the identity map covers the first...
- Layer: utility
- Language: c
- Symbols:
  - `kheap_ram_top` (function, line 19) `static unsigned long kheap_ram_top(void)`
  - `kallocator_init` (function, line 32) `void kallocator_init(void)`
  - `kmalloc_report_failure` (function, line 53) `static void kmalloc_report_failure(unsigned long size)`
  - `kmalloc` (function, line 66) `void *kmalloc(unsigned long size)`
  - `kmalloc_page` (function, line 81) `void *kmalloc_page(void)`
  - `kfree` (function, line 90) `void kfree(void *ptr)`
  - `kcalloc` (function, line 111) `void *kcalloc(unsigned long nmemb, unsigned long size)`
  - `krealloc` (function, line 115) `void *krealloc(void *ptr, unsigned long size)`
  - `kmalloc_aligned` (function, line 127) `void *kmalloc_aligned(unsigned long size, unsigned long align)`
  - `kfree_aligned` (function, line 143) `void kfree_aligned(void *ptr)`
  - `KMALLOC_REPORT_EVERY` (macro, line 50) `#define KMALLOC_REPORT_EVERY`
- Depends on: `headers/arch/x86/boot/bootdefs.h`, `headers/sched.h`

## kernel/panic.c
- Doc: Docstring: kernel/panic.c -- Kernel panic screen.
- Layer: utility
- Language: c
- Symbols:
  - `panic_hex` (function, line 23) `static void panic_hex(unsigned long v, int digits)`
  - `panic_fb_puts` (function, line 30) `static void panic_fb_puts(const char *s)`
  - `panic_fb_hex` (function, line 61) `static void panic_fb_hex(unsigned long v, int digits)`
  - `panic_screen` (function, line 96) `void panic_screen(unsigned long vector, unsigned long err,
        unsigned long rip, unsigned lo...`
- Depends on: `headers/panic.h`, `headers/sched.h`, `headers/vga_fb.h`

## kernel/percpu_rq.c
- Doc: Docstring: kernel/percpu_rq.c -- Per-CPU runqueue hints and stealing.
- Layer: utility
- Language: c
- Symbols:
  - `rq_cpu_valid` (function, line 14) `static int rq_cpu_valid(int cpu)`
  - `rq_init` (function, line 19) `void rq_init(void)`
  - `rq_enqueue` (function, line 41) `void rq_enqueue(int cpu, int pid)`
  - `rq_pop_local` (function, line 61) `int rq_pop_local(int cpu)`
  - `rq_steal_once` (function, line 89) `int rq_steal_once(int self_cpu, int *from_cpu)`
  - `rq_empty` (function, line 115) `int rq_empty(int cpu)`
  - `rq_note_poll` (function, line 127) `void rq_note_poll(int cpu)`
  - `rq_should_rescan` (function, line 137) `int rq_should_rescan(int cpu)`
  - `rq_stats` (function, line 152) `void rq_stats(int cpu, unsigned long *hits, unsigned long *steals,
              unsigned long *d...`
- Depends on: `headers/percpu_rq.h`

## kernel/printf.c
- Layer: utility
- Language: c
- Symbols:
  - `snctx` (struct, line 177)
  - `putc_buf` (function, line 7) `static void putc_buf(char c, void *ctx, int *written)`
  - `putc_file` (function, line 13) `static void putc_file(char c, void *ctx, int *written)`
  - `putc_str` (function, line 19) `static void putc_str(char c, void *ctx, int *written)`
  - `emit_num` (function, line 26) `static void emit_num(void (*emit)(char, void *, int *), void *ctx, int *written,
                ...`
  - `kformat` (function, line 44) `static void kformat(void (*emit)(char, void *, int *), void *ctx,
                    int *writte...`
  - `kfprintf` (function, line 157) `int kfprintf(KFILE *f, const char *fmt, ...)`
  - `ksprintf` (function, line 166) `int ksprintf(char *buf, const char *fmt, ...)`
  - `putc_snbuf` (function, line 178) `static void putc_snbuf(char c, void *ctx, int *written)`
  - `ksnprintf` (function, line 184) `int ksnprintf(char *buf, unsigned long size, const char *fmt, ...)`


Next: [KB_kernel_p2.md](KB_kernel_p2.md)
