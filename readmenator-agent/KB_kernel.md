# Subsystem: kernel

## kernel/cvm_host.c
- Layer: utility
- Language: c
- Symbols:
  - `n_strcmp` (function, line 21) `static int64_t n_strcmp(void *vm, int ac, uint64_t *av)`
  - `n_strncmp` (function, line 27) `static int64_t n_strncmp(void *vm, int ac, uint64_t *av)`
  - `n_strcpy` (function, line 34) `static int64_t n_strcpy(void *vm, int ac, uint64_t *av)`
  - `n_strncpy` (function, line 40) `static int64_t n_strncpy(void *vm, int ac, uint64_t *av)`
  - `n_memcpy` (function, line 47) `static int64_t n_memcpy(void *vm, int ac, uint64_t *av)`
  - `n_memset` (function, line 54) `static int64_t n_memset(void *vm, int ac, uint64_t *av)`
  - `n_memmove` (function, line 60) `static int64_t n_memmove(void *vm, int ac, uint64_t *av)`
  - `n_memcmp` (function, line 67) `static int64_t n_memcmp(void *vm, int ac, uint64_t *av)`
  - `n_strchr` (function, line 74) `static int64_t n_strchr(void *vm, int ac, uint64_t *av)`
  - `n_strstr` (function, line 80) `static int64_t n_strstr(void *vm, int ac, uint64_t *av)`
  - `n_malloc` (function, line 87) `static int64_t n_malloc(void *vm, int ac, uint64_t *av)`
  - `n_free` (function, line 92) `static int64_t n_free(void *vm, int ac, uint64_t *av)`
  - `n_calloc` (function, line 97) `static int64_t n_calloc(void *vm, int ac, uint64_t *av)`
  - `n_realloc` (function, line 105) `static int64_t n_realloc(void *vm, int ac, uint64_t *av)`
  - `n_exit` (function, line 113) `static int64_t n_exit(void *vm, int ac, uint64_t *av)`
  - `n_fopen` (function, line 120) `static int64_t n_fopen(void *vm, int ac, uint64_t *av)`
  - `n_fclose` (function, line 127) `static int64_t n_fclose(void *vm, int ac, uint64_t *av)`
  - `n_fread` (function, line 133) `static int64_t n_fread(void *vm, int ac, uint64_t *av)`
  - `n_fwrite` (function, line 140) `static int64_t n_fwrite(void *vm, int ac, uint64_t *av)`
  - `n_fseek` (function, line 147) `static int64_t n_fseek(void *vm, int ac, uint64_t *av)`
  - `n_ftell` (function, line 153) `static int64_t n_ftell(void *vm, int ac, uint64_t *av)`
  - `n_rewind` (function, line 159) `static int64_t n_rewind(void *vm, int ac, uint64_t *av)`
  - `n_fputs` (function, line 166) `static int64_t n_fputs(void *vm, int ac, uint64_t *av)`
  - `n_fputc` (function, line 172) `static int64_t n_fputc(void *vm, int ac, uint64_t *av)`
  - `n_fgetc` (function, line 178) `static int64_t n_fgetc(void *vm, int ac, uint64_t *av)`
  - `n_ungetc` (function, line 184) `static int64_t n_ungetc(void *vm, int ac, uint64_t *av)`
  - `n_fflush` (function, line 190) `static int64_t n_fflush(void *vm, int ac, uint64_t *av)`
  - `n_putchar` (function, line 196) `static int64_t n_putchar(void *vm, int ac, uint64_t *av)`
  - `n_write` (function, line 203) `static int64_t n_write(void *vm, int ac, uint64_t *av)`
  - `n_read` (function, line 212) `static int64_t n_read(void *vm, int ac, uint64_t *av)`
  - `n_puts` (function, line 227) `static int64_t n_puts(void *vm, int ac, uint64_t *av)`
  - `n_atol` (function, line 235) `static int64_t n_atol(void *vm, int ac, uint64_t *av)`
  - `n_strtol` (function, line 248) `static int64_t n_strtol(void *vm, int ac, uint64_t *av)`
  - `n_stderr_addr` (function, line 261) `static int64_t n_stderr_addr(void *vm, int ac, uint64_t *av)`
  - `n_stdout_addr` (function, line 266) `static int64_t n_stdout_addr(void *vm, int ac, uint64_t *av)`
  - `n_stdin_addr` (function, line 271) `static int64_t n_stdin_addr(void *vm, int ac, uint64_t *av)`
  - `kout_char` (function, line 276) `static void kout_char(void *ctx, char c)`
  - `kout_uint` (function, line 282) `static void kout_uint(void *ctx, unsigned long long v, int base, int upper)`
  - `kformat` (function, line 295) `static void kformat(void *ctx, const char *fmt, uint64_t *argv, int argc)`
  - `n_fprintf` (function, line 361) `static int64_t n_fprintf(void *vm, int ac, uint64_t *av)`
  - `n_printf` (function, line 368) `static int64_t n_printf(void *vm, int ac, uint64_t *av)`
  - `n_sprintf` (function, line 375) `static int64_t n_sprintf(void *vm, int ac, uint64_t *av)`
  - `n_snprintf` (function, line 383) `static int64_t n_snprintf(void *vm, int ac, uint64_t *av)`
  - `register_host_natives` (function, line 391) `static void register_host_natives(CvmState *vm)`
  - `cvm_main` (function, line 436) `int cvm_main(int argc, char **argv)`

## kernel/editor.c
- Layer: infrastructure
- Doc: include "kernel.h" include "shell.h" include "editor.h"  ===============================================================
- Language: c
- Symbols:
  - `edit_alloc` (function, line 37) `static EditBuf *edit_alloc(const char *fname)`
  - `edit_free` (function, line 54) `static void edit_free(EditBuf *e)`
  - `edit_load` (function, line 60) `static int edit_load(EditBuf *e)`
  - `edit_save` (function, line 96) `static int edit_save(EditBuf *e)`
  - `edit_print` (function, line 110) `static void edit_print(EditBuf *e, int idx)`
  - `edit_list` (function, line 121) `static void edit_list(EditBuf *e, int start, int end)`
  - `edit_set_line` (function, line 132) `static int edit_set_line(EditBuf *e, int idx, const char *text)`
  - `edit_insert` (function, line 141) `static int edit_insert(EditBuf *e, int idx, const char *text)`
  - `edit_delete` (function, line 151) `static int edit_delete(EditBuf *e, int idx)`
  - `edit_line_cstr` (function, line 164) `static void edit_line_cstr(EditLine *l, char *out)`
  - `edit_search` (function, line 168) `static void edit_search(EditBuf *e, const char *needle)`
  - `edit_status` (function, line 185) `static void edit_status(EditBuf *e)`
  - `edit_usage` (function, line 193) `static void edit_usage(void)`
  - `edit_refuse_save` (function, line 205) `static int edit_refuse_save(EditBuf *e)`
  - `edit_arg_line` (function, line 210) `static int edit_arg_line(int argc, char **argv, EditBuf *e, int *out)`
  - `edit_loop` (function, line 218) `static void edit_loop(EditBuf *e)`
  - `shell_cmd_edit` (function, line 306) `void shell_cmd_edit(int argc, char **argv)`
  - `EDIT_MAX_LINES` (macro, line 19)
  - `EDIT_LINE_MAX` (macro, line 21)
  - `EDIT_FILE_MAX` (macro, line 22)

## kernel/exec.c
- Layer: utility
- Doc: exec.c - Process execution: setjmp/longjmp, k_exec_user, k_run_rel, kexit.
- Language: c
- Symbols:
  - `vga_mode_set` (function, line 59) `void vga_mode_set(int on)`
  - `vga_mode_is_active` (function, line 61) `int  vga_mode_is_active(void)`
  - `vga_gfx_ran_set` (function, line 62) `void vga_gfx_ran_set(int on)`
  - `k_user_fault_return` (function, line 65) `void k_user_fault_return(void)`
  - `setup_user_stack` (function, line 81) `unsigned long *setup_user_stack(char *sbase, unsigned long ssize,
                               ...`
  - `k_exec_user` (function, line 116) `int k_exec_user(void *entry, int argc, char **argv)`
  - `k_run_rel` (function, line 197) `int k_run_rel(prog_entry_t entry, int argc, char **argv)`
  - `kexit` (function, line 229) `void kexit(int code)`

## kernel/klog.c
- Layer: utility
- Doc: klog.c - Structured kernel logging with levels and subsystems.
- Language: c
- Symbols:
  - `klog_set_level` (function, line 28) `void klog_set_level(log_level_t level)`
  - `klog_set_subsys_level` (function, line 32) `void klog_set_subsys_level(log_subsystem_t subsys, log_level_t level)`
  - `klog_disable` (function, line 37) `void klog_disable(void)`
  - `klog_enable` (function, line 39) `void klog_enable(void)`
  - `klog` (function, line 40) `void klog(log_level_t level, log_subsystem_t subsys,
          const char *fmt, ...)`
  - `klog_hexdump` (function, line 118) `void klog_hexdump(log_level_t level, log_subsystem_t subsys,
                  const void *data, ...`

## kernel/loader.c
- Layer: utility
- Doc: include "kernel.h" include "vga_fb.h"  ================================================================
- Language: c
- Symbols:
  - `exec_range` (struct, line 83)
  - `elf_name_copy` (function, line 92) `static void elf_name_copy(char *out, unsigned out_cap, const char *tab,
                         ...`
  - `elf_load_fail` (function, line 106) `static void elf_load_fail(void *base, void **sec_addrs, const char *why)`
  - `elf_load` (function, line 114) `void *elf_load(void *data, unsigned size)`
  - `apply_exec_relocs` (function, line 348) `static void apply_exec_relocs(void *data, unsigned size, unsigned long base,
                    ...`
  - `load_exec_elf` (function, line 431) `void *load_exec_elf(void *data, unsigned size)`
  - `ELF64_R_SYM` (macro, line 53)
  - `ELF64_R_TYPE` (macro, line 55)
  - `SHN_UNDEF` (macro, line 56)
  - `SHT_SYMTAB` (macro, line 57)
  - `SHT_STRTAB` (macro, line 59)
  - `SHT_RELA` (macro, line 60)
  - `SHT_PROGBITS` (macro, line 61)
  - `SHT_NOBITS` (macro, line 62)
  - `SHF_ALLOC` (macro, line 63)
  - `SHF_EXECINSTR` (macro, line 64)
  - `EM_X86_64` (macro, line 65)
  - `PT_LOAD` (macro, line 67)
  - `R_X86_64_64` (macro, line 68)
  - `R_X86_64_PC32` (macro, line 70)
  - `R_X86_64_PLT32` (macro, line 71)
  - `R_X86_64_GLOB_DAT` (macro, line 72)
  - `R_X86_64_JUMP_SLOT` (macro, line 73)
  - `R_X86_64_RELATIVE` (macro, line 74)
  - `R_X86_64_32` (macro, line 75)
  - `R_X86_64_32S` (macro, line 76)
  - `R_X86_64_IRELATIVE` (macro, line 77)
  - `PF_X` (macro, line 78)
  - `ELF_MAX_SEGMENTS` (macro, line 80)
  - `ELF_NAME_MAX` (macro, line 81)

## kernel/lz4_kernel.c
- Layer: utility
- Doc: include "kernel.h" include "lz4_kernel.h"  define HASH_BITS 12 define HASH_SIZE (1 << HASH_BITS)
- Language: c
- Symbols:
  - `LZ4_read32` (function, line 6) `static inline unsigned int LZ4_read32(const unsigned char *p)`
  - `LZ4_read16` (function, line 13) `static inline unsigned int LZ4_read16(const unsigned char *p)`
  - `LZ4_write16` (function, line 20) `static inline void LZ4_write16(unsigned char *dst, unsigned short v)`
  - `LZ4_hash` (function, line 25) `static unsigned int LZ4_hash(const unsigned char *p)`
  - `LZ4_compressBound` (function, line 32) `int LZ4_compressBound(int inputSize)`
  - `LZ4_compress_default` (function, line 39) `int LZ4_compress_default(const char *src, char *dst, int srcSize, int dstCapacity)`
  - `LZ4_decompress_safe` (function, line 163) `int LZ4_decompress_safe(const char *src, char *dst, int compressedSize, int dstCapacity)`
  - `HASH_BITS` (macro, line 3)
  - `HASH_SIZE` (macro, line 5)

## kernel/mm.c
- Layer: utility
- Doc: include "kernel.h"  ================================================================
- Language: c
- Symbols:
  - `kallocator_init` (function, line 11) `void kallocator_init(void)`
  - `kmalloc` (function, line 15) `void *kmalloc(unsigned long size)`
  - `kfree` (function, line 20) `void kfree(void *ptr)`
  - `kcalloc` (function, line 25) `void *kcalloc(unsigned long nmemb, unsigned long size)`
  - `krealloc` (function, line 29) `void *krealloc(void *ptr, unsigned long size)`

## kernel/printf.c
- Layer: utility
- Doc: include "kernel.h"  ================================================================
- Language: c
- Symbols:
  - `snctx` (struct, line 172)
  - `putc_buf` (function, line 6) `static void putc_buf(char c, void *ctx, int *written)`
  - `putc_file` (function, line 12) `static void putc_file(char c, void *ctx, int *written)`
  - `putc_str` (function, line 18) `static void putc_str(char c, void *ctx, int *written)`
  - `emit_num` (function, line 25) `static void emit_num(void (*emit)(char, void *, int *), void *ctx, int *written,
                ...`
  - `kformat` (function, line 43) `static void kformat(void (*emit)(char, void *, int *), void *ctx,
                    int *writte...`
  - `kprintf` (function, line 142) `int kprintf(const char *fmt, ...)`
  - `kfprintf` (function, line 151) `int kfprintf(KFILE *f, const char *fmt, ...)`
  - `ksprintf` (function, line 160) `int ksprintf(char *buf, const char *fmt, ...)`
  - `putc_snbuf` (function, line 173) `static void putc_snbuf(char c, void *ctx, int *written)`
  - `ksnprintf` (function, line 178) `int ksnprintf(char *buf, unsigned long size, const char *fmt, ...)`

## kernel/redirect.c
- Layer: infrastructure
- Doc: include "kernel.h"  ================================================================
- Language: c
- Symbols:
  - `shell_report_exit` (function, line 10) `void shell_report_exit(int code)`
  - `shell_report` (function, line 16) `void shell_report(const char *what, const char *detail)`
  - `shell_take_redirect` (function, line 24) `int shell_take_redirect(int *argc, char **argv, char **path, int *append_mode)`

## kernel/sched.c
- Layer: utility
- Language: c
- Symbols:
  - `read_cr3` (function, line 27) `static inline unsigned long read_cr3(void)`
  - `__attribute__` (function, line 35) `typedef struct __attribute__((packed))`
  - `__attribute__` (function, line 47) `typedef struct __attribute__((packed))`
  - `__attribute__` (function, line 52) `typedef struct __attribute__((packed))`
  - `alloc_kstack` (function, line 59) `static uint64_t alloc_kstack(void)`
  - `idt_set` (function, line 74) `static void idt_set(int vec, void (*h)(void))`
  - `idt_init` (function, line 84) `static void idt_init(void)`
  - `pic_init` (function, line 98) `static void pic_init(void)`
  - `pit_init` (function, line 111) `static void pit_init(void)`
  - `pic_eoi` (function, line 117) `static void pic_eoi(int irq)`
  - `tss_init` (function, line 125) `static void tss_init(void)`
  - `isr_dispatch` (function, line 165) `void isr_dispatch(int vector, trap_frame_t *frame)`
  - `ring` (function, line 277) `* the hardware ring (CS RPL) and the fault address. */
        if ((frame->cs & 3) == 3 &&
      ...`
  - `proc_get` (function, line 291) `proc_t *proc_get(int pid)`
  - `proc_create` (function, line 297) `int proc_create(const char *name, int parent_pid)`
  - `schedule` (function, line 337) `void schedule(void)`
  - `yield` (function, line 356) `void yield(void)`
  - `do_exit` (function, line 361) `void do_exit(int code)`
  - `do_waitpid` (function, line 381) `int do_waitpid(int pid)`
  - `do_kill` (function, line 406) `int do_kill(int pid)`
  - `timer_tick` (function, line 413) `void timer_tick(void)`
  - `mouse_wait_cmd` (function, line 417) `static void mouse_wait_cmd(void)`
  - `mouse_wait_data` (function, line 423) `static void mouse_wait_data(void)`
  - `mouse_write` (function, line 430) `static void mouse_write(unsigned char data)`
  - `mouse_read` (function, line 437) `static unsigned char mouse_read(void)`
  - `mouse_hw_init` (function, line 442) `static void mouse_hw_init(void)`
  - `mouse_disable` (function, line 486) `void mouse_disable(void)`
  - `mouse_enable` (function, line 488) `void mouse_enable(void)`
  - `sched_init` (function, line 489) `void sched_init(void)`
  - `MY_SYS_KSTK_TOP` (macro, line 15)
  - `MY_USER_STACK_TOP` (macro, line 16)
  - `MY_USER_LOAD_BASE` (macro, line 17)

## kernel/scrollback.c
- Layer: utility
- Doc: scrollback.c - Console scrollback ring buffer.
- Language: c
- Symbols:
  - `sb_init` (function, line 16) `void sb_init(void)`
  - `sb_capture_row0` (function, line 22) `void sb_capture_row0(void)`
  - `sb_reset` (function, line 33) `void sb_reset(void)`
  - `sb_get_count` (function, line 37) `int sb_get_count(void)`
  - `sb_get_head` (function, line 39) `int sb_get_head(void)`
  - `sb_get_char` (function, line 40) `char sb_get_char(int row, int col)`
  - `SCROLLBACK_ROWS` (macro, line 11)

## kernel/serial.c
- Layer: utility
- Doc: include "kernel.h"  serial.c -- COM1 16550 UART driver.
- Language: c
- Symbols:
  - `serial_init` (function, line 18) `void serial_init(void)`
  - `serial_tx_ready` (function, line 28) `static int serial_tx_ready(void)`
  - `serial_rx_ready` (function, line 30) `static int serial_rx_ready(void)`
  - `serial_putc` (function, line 31) `void serial_putc(char c)`
  - `serial_puts` (function, line 36) `void serial_puts(const char *s)`
  - `serial_available` (function, line 38) `int serial_available(void)`
  - `serial_getc` (function, line 40) `int serial_getc(void)`
  - `COM1` (macro, line 16)

## kernel/shell.c
- Layer: utility
- Doc: include "kernel.h" include "net.h" include "minifs.h" include "sched.h" include "vga_fb.h" include "pcspk.h" include "sb
- Language: c
- Symbols:
  - `shell_queue_launch` (function, line 65) `void shell_queue_launch(const char *cmd)`
  - `shell_prompt` (function, line 85) `static void shell_prompt(void)`
  - `shell_parse_vol` (function, line 93) `static int shell_parse_vol(const char *s, unsigned *out)`
  - `pb_empty` (function, line 126) `static int pb_empty(void)`
  - `pb_count` (function, line 128) `static int pb_count(void)`
  - `pb_push_back` (function, line 129) `static void pb_push_back(unsigned char c)`
  - `pb_push_front` (function, line 134) `static void pb_push_front(unsigned char c)`
  - `pb_pop` (function, line 139) `static int pb_pop(void)`
  - `pb_peek` (function, line 145) `static int pb_peek(void)`
  - `raw_blocking_getc` (function, line 152) `static int raw_blocking_getc(void)`
  - `raw_try_getc` (function, line 171) `static int raw_try_getc(void)`
  - `consume_page_after_esc` (function, line 206) `static int consume_page_after_esc(void)`
  - `console_getc` (function, line 231) `* returns console_getc() simply serves the FIFO again. */
int console_getc(void)`
  - `console_peek` (function, line 253) `static int console_peek(void)`
  - `scrollback_render` (function, line 268) `static void scrollback_render(int voff, int total, const unsigned char *saved)`
  - `scrollback_view` (function, line 305) `static void scrollback_view(int initial_dir)`
  - `shell_readline_buf` (function, line 350) `void shell_readline_buf(char *buf, int size)`
  - `shell_name_base` (function, line 379) `static const char *shell_name_base(const char *path)`
  - `shell_complete_replace` (function, line 389) `static void shell_complete_replace(char *buf, int size, int *pos,
                               ...`
  - `shell_readline` (function, line 406) `static void shell_readline(void)`
  - `shell_hist_show` (function, line 415) `static void shell_hist_show(char *buf, int size, int *pos, const char *text)`
  - `shell_line_repaint` (function, line 437) `static void shell_line_repaint(char *buf, int size, int pos)`
  - `shell_line_insert` (function, line 450) `static void shell_line_insert(char *buf, int size, int *pos, char c)`
  - `shell_line_backspace` (function, line 459) `static void shell_line_backspace(char *buf, int size, int *pos)`
  - `shell_line_delete` (function, line 467) `static void shell_line_delete(char *buf, int size, int *pos)`
  - `shell_line_kill_front` (function, line 474) `static void shell_line_kill_front(char *buf, int size, int *pos)`
  - `shell_line_kill_tail` (function, line 481) `static void shell_line_kill_tail(char *buf, int size, int *pos)`
  - `shell_line_kill_word` (function, line 486) `static void shell_line_kill_word(char *buf, int size, int *pos)`
  - `shell_hist_nav` (function, line 497) `static void shell_hist_nav(char *buf, int size, int *pos, int up)`
  - `shell_parse` (function, line 696) `int shell_parse(char *line, char **argv, int max_args)`
  - `shell_run` (function, line 717) `void shell_run(void)`
  - `shell_load` (function, line 764) `static int shell_load(const char *fname, char *progname_out, void **entry_out)`
  - `outw_port` (function, line 822) `static inline void outw_port(unsigned short port, unsigned short val)`
  - `shell_cmd_poweroff` (function, line 828) `static void shell_cmd_poweroff(void)`
  - `shell_run_dir_for` (function, line 845) `static const ShellRunDir *shell_run_dir_for(const char *name)`
  - `shell_file_is_real` (function, line 863) `static int shell_file_is_real(const char *resolved)`
  - `shell_resolve_run` (function, line 875) `static int shell_resolve_run(const char *name, char *out, unsigned cap)`
  - `shell_run_elf_buf` (function, line 911) `static int shell_run_elf_buf(const char *data, unsigned size, int argc,
                         ...`
  - `shell_run_elf_file` (function, line 932) `static int shell_run_elf_file(const char *full, int argc, char **argv)`
  - `shell_run_elf_minifs` (function, line 945) `static int shell_run_elf_minifs(const char *name, int argc, char **argv)`
  - `shell_run_cvm` (function, line 991) `static int shell_run_cvm(const char *full, int argc, char **argv)`
  - `shell_run_file` (function, line 1020) `static int shell_run_file(const char *name, int argc, char **argv)`
  - `shell_run_any` (function, line 1049) `int shell_run_any(const char *name, int argc, char **argv)`
  - `gfx_parse_int` (function, line 1109) `static int gfx_parse_int(const char *s, int *out)`
  - `gfx_read_palette` (function, line 1129) `static void gfx_read_palette(unsigned char pal[768])`
  - `shell_cmd_gfx` (function, line 1135) `static void shell_cmd_gfx(int argc, char **argv)`
  - `shell_cmd_wm` (function, line 1251) `static void shell_cmd_wm(int argc, char **argv)`
  - `shell_cmd_hash` (function, line 1272) `static void shell_cmd_hash(int argc, char **argv)`
  - `shell_exec_builtin` (function, line 1286) `void shell_exec_builtin(int argc, char **argv)`
  - `XXH_STATIC_LINKING_ONLY` (macro, line 10)
  - `SHELL_CVM_INTERP` (macro, line 33)
  - `SHELL_RUN_DIRS` (macro, line 52)
  - `SHELL_HIST_MAX` (macro, line 75)
  - `PB_LEN` (macro, line 122)
  - `MAX_SEQ_POLL` (macro, line 188)
  - `SB_LEN` (macro, line 267)
  - `SB_PGUP` (macro, line 289)
  - `SB_PGDN` (macro, line 291)
  - `SB_EXIT` (macro, line 292)
  - `QEMU_PM_PORT` (macro, line 826)

## kernel/string.c
- Layer: utility
- Doc: include "kernel.h"  string.c -- Kernel string and memory functions.
- Language: c
- Symbols:
  - `kstrlen` (function, line 16) `unsigned long kstrlen(const char *s)`
  - `kstrcpy` (function, line 22) `char *kstrcpy(char *dst, const char *src)`
  - `kstrncpy` (function, line 28) `char *kstrncpy(char *dst, const char *src, unsigned long n)`
  - `kstrncat` (function, line 34) `char *kstrncat(char *dst, const char *src, unsigned long n)`
  - `kstrcmp` (function, line 42) `int kstrcmp(const char *a, const char *b)`
  - `kstrncmp` (function, line 47) `int kstrncmp(const char *a, const char *b, unsigned long n)`
  - `kstrchr` (function, line 52) `char *kstrchr(const char *s, int c)`
  - `kstrstr` (function, line 57) `char *kstrstr(const char *hay, const char *ndl)`
  - `kmemcpy` (function, line 67) `void *kmemcpy(void *dst, const void *src, unsigned long n)`
  - `kmemset` (function, line 74) `void *kmemset(void *dst, int c, unsigned long n)`
  - `kmemcmp` (function, line 80) `int kmemcmp(const void *a, const void *b, unsigned long n)`
  - `kmemmove` (function, line 86) `void *kmemmove(void *dst, const void *src, unsigned long n)`
  - `katol` (function, line 94) `long katol(const char *s)`

## kernel/symtab.c
- Layer: utility
- Doc: include "kernel.h"  ================================================================
- Language: c
- Symbols:
  - `k_register_symbol` (function, line 9) `void k_register_symbol(const char *name, void *addr)`
  - `ksym_resolve` (function, line 17) `void *ksym_resolve(const char *name)`
  - `kprog_slot` (function, line 33) `KProg *kprog_slot(const char *name)`
  - `kprog_lookup` (function, line 41) `KProg *kprog_lookup(const char *name)`
  - `k_register_program` (function, line 48) `void k_register_program(const char *name, prog_entry_t entry)`
  - `k_register_process` (function, line 56) `void k_register_process(const char *name, void *proc_entry)`
  - `k_spawn` (function, line 64) `int k_spawn(const char *name, int argc, char **argv)`

## kernel/syscalls.c
- Layer: utility
- Doc: syscalls.c - Linux x86-64 syscall dispatcher and SYS_SPAWN.
- Language: c
- Symbols:
  - `kiovec` (struct, line 36)
  - `syscall_trace_enabled` (function, line 41) `long syscall_trace_enabled(void)`
  - `syscall_trace_set` (function, line 43) `void syscall_trace_set(int on)`
  - `trace_is_noisy` (function, line 56) `static int trace_is_noisy(long n)`
  - `ksyscall` (function, line 60) `long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6)`
  - `user_range_ok` (function, line 79) `int user_range_ok(unsigned long p, unsigned long len)`
  - `user_str_ok` (function, line 85) `int user_str_ok(unsigned long p, unsigned long maxlen)`
  - `ksyscall_dispatch` (function, line 93) `static long ksyscall_dispatch(long n, long a1, long a2, long a3, long a4, long a5, long a6)`
  - `tools` (function, line 622) `* ET_EXEC tools (lzss/lz4/aes/json/freedom) are run by the shell, not from an
 * interpreter.
 */...`
  - `KFD_MAX` (macro, line 30)
  - `SYSCALL_TRACE` (macro, line 37)
  - `SYS_NOISY_TIME` (macro, line 49)
  - `SYS_NOISY_KBD` (macro, line 50)
  - `SYS_NOISY_MOUSE` (macro, line 51)

## kernel/time.c
- Layer: utility
- Doc: include "kernel.h"  ================================================================
- Language: c
- Symbols:
  - `ktime_rdtsc` (function, line 11) `static unsigned long ktime_rdtsc(void)`
  - `ktime_init` (function, line 17) `static void ktime_init(void)`
  - `ktime_ms` (function, line 31) `unsigned long ktime_ms(void)`
- Imported by: `mcp/mcp_dbg_driver.py`, `mcp/mcp_dogfood.py`, `mcp/minios_addons.py`, `mcp/minios_mcp.py`, `test_http_server.py`, `tls_test.py`, `tools/gdb_repro.py`, `tools/minios_cli.py`, `tools/minios_gui.py`, `tools/qga_client.py`, `tools/repro_gui.py`

## kernel/vga_fb.c
- Layer: utility
- Language: c
- Symbols:
  - `vga_fb_boot_config` (function, line 24) `void vga_fb_boot_config(void)`
  - `lg_get` (function, line 79) `static const char *lg_get(int i)`
  - `lg_push` (function, line 85) `static void lg_push(const char *line, int len)`
  - `line_nrows` (function, line 97) `static int line_nrows(int len)`
  - `act_nrows` (function, line 103) `static int act_nrows(void)`
  - `total_rows` (function, line 107) `static int total_rows(void)`
  - `disp_clamp` (function, line 115) `static void disp_clamp(void)`
  - `line_at` (function, line 133) `static const char *line_at(int abs, int *off)`
  - `cursor_save_bg` (function, line 174) `static void cursor_save_bg(int mx, int my)`
  - `cursor_draw` (function, line 182) `static void cursor_draw(int mx, int my)`
  - `cursor_restore` (function, line 193) `static void cursor_restore(int mx, int my)`
  - `cursor_over` (function, line 207) `static int cursor_over(int x0, int y0, int w, int h)`
  - `vga_fb_set_gfx_mode` (function, line 231) `void vga_fb_set_gfx_mode(int on)`
  - `vga_fb_gfx_cursor_erase` (function, line 244) `static void vga_fb_gfx_cursor_erase(void)`
  - `vga_fb_gfx_cursor_draw` (function, line 252) `static void vga_fb_gfx_cursor_draw(void)`
  - `vga_fb_set_palette` (function, line 405) `static void vga_fb_set_palette(void)`
  - `vga_fb_pixel` (function, line 460) `void vga_fb_pixel(int x, int y, uint8_t color)`
  - `vga_fb_rect` (function, line 464) `void vga_fb_rect(int x, int y, int w, int h, uint8_t color)`
  - `vga_fb_char` (function, line 471) `void vga_fb_char(int col, int row, char c, uint8_t fg, uint8_t bg)`
  - `vga_fb_str` (function, line 486) `void vga_fb_str(int col, int row, const char *s, uint8_t fg, uint8_t bg)`
  - `text_px` (function, line 498) `static void text_px(int px, int py, const char *s, uint8_t fg, uint8_t bg)`
  - `wm_draw_buttons` (function, line 525) `static void wm_draw_buttons(int px, int py, int win_w, uint8_t fg, uint8_t bg)`
  - `wm_buttons_hit` (function, line 551) `static int wm_buttons_hit(int mx, int my, int win_x, int win_y, int win_w)`
  - `wm_close_pending` (function, line 566) `int wm_close_pending(void)`
  - `wm_clear_close` (function, line 567) `void wm_clear_close(void)`
  - `wm_gfx_mode_active` (function, line 568) `int wm_gfx_mode_active(void)`
  - `wm_button_click` (function, line 573) `static int wm_button_click(int mx, int my)`
  - `vga_fb_blit_gfx_window` (function, line 616) `void vga_fb_blit_gfx_window(void)`
  - `vga_fb_clear` (function, line 641) `void vga_fb_clear(void)`
  - `vga_fb_blit_nk_window` (function, line 657) `void vga_fb_blit_nk_window(void)`
  - `term_recalc` (function, line 688) `static void term_recalc(void)`
  - `draw_title` (function, line 715) `static void draw_title(void)`
  - `taskbar_layout` (function, line 732) `static void taskbar_layout(void)`
  - `draw_speaker_icon` (function, line 750) `static void draw_speaker_icon(int x, int y, uint8_t color)`
  - `taskbar_render` (function, line 758) `static void taskbar_render(void)`
  - `taskbar_tick` (function, line 785) `static void taskbar_tick(void)`
  - `taskbar_handle_click` (function, line 799) `static void taskbar_handle_click(int mx, int my)`
  - `draw_scrollbar` (function, line 833) `static void draw_scrollbar(void)`
  - `render_row` (function, line 869) `static void render_row(int vrow, int abs)`
  - `term_render` (function, line 897) `static void term_render(void)`
  - `term_render_active` (function, line 910) `static void term_render_active(void)`
  - `line` (function, line 951) `* display stale bytes left over from a longer previous line (e.g. the prompt
 * would show the ta...`
  - `vga_fb_puts_term` (function, line 993) `void vga_fb_puts_term(const char *s)`
  - `vga_fb_text_cursor` (function, line 1000) `void vga_fb_text_cursor(int col)`
  - `vga_fb_hide_text_cursor` (function, line 1008) `void vga_fb_hide_text_cursor(void)`
  - `vga_fb_draw_desktop` (function, line 1011) `void vga_fb_draw_desktop(void)`
  - `vga_fb_toggle_fullscreen` (function, line 1037) `void vga_fb_toggle_fullscreen(void)`
  - `vga_fb_toggle_minimize` (function, line 1047) `void vga_fb_toggle_minimize(void)`
  - `vga_fb_is_minimized` (function, line 1053) `int vga_fb_is_minimized(void)`
  - `vga_fb_is_fullscreen` (function, line 1055) `int vga_fb_is_fullscreen(void)`
  - `vga_fb_move_terminal` (function, line 1076) `void vga_fb_move_terminal(int dx, int dy)`
  - `term_max_cols` (function, line 1105) `static int term_max_cols(void)`
  - `term_max_rows` (function, line 1109) `static int term_max_rows(void)`
  - `term_finish_layout` (function, line 1113) `static void term_finish_layout(void)`
  - `vga_fb_snap_window` (function, line 1119) `void vga_fb_snap_window(int zone)`
  - `vga_fb_resize` (function, line 1141) `void vga_fb_resize(int dcols, int drows)`
  - `vga_fb_reset_default` (function, line 1159) `void vga_fb_reset_default(void)`
  - `pipe_field` (function, line 1199) `static const char *pipe_field(const char *line, int idx, char *buf, int buflen)`
  - `desktop_shortcuts_load` (function, line 1214) `void desktop_shortcuts_load(void)`
  - `desktop_shortcuts_draw` (function, line 1273) `void desktop_shortcuts_draw(void)`
  - `desktop_shortcuts_hit_test` (function, line 1295) `const char *desktop_shortcuts_hit_test(int mx, int my)`
  - `vga_fb_mouse_tick` (function, line 1308) `void vga_fb_mouse_tick(void)`
  - `vga_fb_mouse_init` (function, line 1431) `void vga_fb_mouse_init(void)`
  - `vga_fb_init` (function, line 1446) `void vga_fb_init(void)`
  - `CURSOR_TIP_X` (macro, line 163)
  - `CURSOR_TIP_Y` (macro, line 164)
  - `WIN_DEF_COLS` (macro, line 374)
  - `WIN_DEF_ROWS` (macro, line 375)
  - `WIN_DEF_X` (macro, line 376)
  - `WIN_DEF_Y` (macro, line 377)
  - `FB_OFFSET` (macro, line 397)
