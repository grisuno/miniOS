# Subsystem: root

## bootloader.c
- Layer: utility
- Language: c
- Symbols:
  - `main` (function, line 20) `void main(void)`
  - `__asm__` (function, line 3) `__asm__( ".global gdt_start\n" "gdt_start:\n" " .quad 0\n" " .quad 0x00CF9A000000FFFF\n" " .quad 0x00CF92000000FFFF\n" "gdt_end:\n" ".global gdt32_ptr\n" "gdt32_ptr:\n" " .word gdt_end - gdt_start - 1`
  - `volatile` (function, line 22) `__asm__ volatile("mov %%dl, boot_drive\n" : : : "dx");`
  - `KSECTORS` (macro, line 19) `#define KSECTORS`

## gen_minifs.py
- Layer: utility
- Language: py

## install.sh
- Layer: utility
- Language: sh

## kernel.c
- Layer: utility
- Doc: kernel.c -- Mediator: boot orchestration and the syscall trampoline.
- Language: c
- Symbols:
  - `syscall_init` (function, line 107) `void syscall_init(void)`
  - `bootlog_mark` (function, line 398) `void bootlog_mark(const char *name)`
  - `bootlog_report` (function, line 405) `void bootlog_report(void)`
  - `__attribute__` (function, line 412) `__attribute__((section(".init.text")))
void kmain(void)`
  - `table` (function, line 95) `* Symbol table (for resolving program references) * ================================================================ */ #define KSYM_MAX 256 /* ---- SYSCALL/SYSRET setup ------------------------------`
  - `wrmsr` (function, line 112) `wrmsr(MSR_STAR, ((unsigned long)GDT64_DATA_SEL << 48) | ((unsigned long)GDT64_CODE_SEL << 32));`
  - `ksyscall` (function, line 120) `extern long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);`
  - `sysretq` (function, line 158) `* trapped from the user window returns with sysretq (ring 3);`
  - `kstack` (function, line 167) `* kstack (0 on the BSP, 1 on APs): harmless while a single process * runs, fatal as soon as two threads syscall concurrently. */ _Static_assert(__builtin_offsetof(cpu_t, cur_pid) == 12, "cpu cur_pid o`
  - `ms` (function, line 391) `* 0 ms (TSC ticks since power-on divided down, still monotonic);`
  - `kprintf` (function, line 407) `kprintf("bootlog: %d phases (ms since power-on)\n", bootlog_n);`
  - `volatile` (function, line 415) `__asm__ volatile( "mov $0x10, %%ax\n" "mov %%ax, %%ds\n" "mov %%ax, %%es\n" "mov %%ax, %%fs\n" "mov %%ax, %%gs\n" "mov %%ax, %%ss\n" "mov $0x90000, %%rsp\n" ::: "ax" );`
  - `EM` (function, line 427) `* CR0: clear EM (bit 2), set MP (bit 1);`
  - `serial_init` (function, line 438) `serial_init();`
  - `vga_clear` (function, line 440) `vga_clear();`
  - `outb` (function, line 446) `outb(0x21, 0xFF);`
  - `vga_puts` (function, line 448) `vga_puts("MiniOS Kernel v0.3\n====================\n");`
  - `kallocator_init` (function, line 450) `kallocator_init();`
  - `ramdisk_init` (function, line 453) `ramdisk_init();`
  - `register_libc_symbols` (function, line 454) `register_libc_symbols();`
  - `vga_fb_boot_config` (function, line 456) `vga_fb_boot_config();`
  - `mm_setup_protections` (function, line 457) `mm_setup_protections();`
  - `net_init` (function, line 465) `net_init();`
  - `size` (function, line 468) `* image size (see kernel.ld);`
  - `ramdisk_setup_from` (function, line 470) `ramdisk_setup_from(ramdisk_start, (unsigned)ramdisk_image_size());`
  - `block_init` (function, line 485) `block_init();`
  - `minifs_init` (function, line 487) `minifs_init();`
  - `vfs_register_builtins` (function, line 497) `vfs_register_builtins();`
  - `sched_init` (function, line 504) `sched_init();`
  - `vga_fb_init` (function, line 507) `vga_fb_init();`
  - `smp_init` (function, line 518) `smp_init();`
  - `shell_run` (function, line 520) `shell_run();`
  - `syscall_kstack` (variable, line 106) `extern unsigned long syscall_kstack;`
  - `ramdisk_start` (variable, line 384) `extern char ramdisk_start[];`
  - `ramdisk_end` (variable, line 386) `extern char ramdisk_end[];`
  - `USER_WIN_LO` (macro, line 56) `#define USER_WIN_LO`
  - `USER_WIN_HI` (macro, line 57) `#define USER_WIN_HI`
  - `STR_` (macro, line 58) `#define STR_(x)`
  - `STR` (macro, line 59) `#define STR(x)`
  - `KSYM_MAX` (macro, line 97) `#define KSYM_MAX`
  - `BOOTLOG_MAX` (macro, line 394) `#define BOOTLOG_MAX`
- Depends on: `headers/abi.h`, `headers/arch/x86/boot/bootdefs.h`, `headers/arch/x86/msr.h`, `headers/block.h`, `headers/ide.h`, `headers/kernel.h`, `headers/minifs.h`, `headers/net.h`, `headers/sb16.h`, `headers/sched.h`, `headers/smp.h`, `headers/vga_fb.h`

## make_usb.sh
- Layer: utility
- Doc: Build the MiniOS bootable USB image and optionally write it to a device.  Wraps the Makefile targets so there is a singl
- Language: sh
- Symbols:
  - `usage` (function, line 40)
  - `wizard` (function, line 56)

## minifs_dump.py
- Layer: utility
- Language: py
- Symbols:
  - `u16` (function, line 13) `def u16(d, o)`
  - `u32` (function, line 14) `def u32(d, o)`
  - `mode_str` (function, line 16) `def mode_str(m)`
  - `FS` (class, line 25) `class FS`
  - `main` (method, line 105) `def main()`
  - `__init__` (method, line 26) `def __init__(self, fn)`
  - `blk` (method, line 29) `def blk(self, n)`
  - `_sb` (method, line 30) `def _sb(self)`
  - `inode` (method, line 38) `def inode(self, i)`
  - `read` (method, line 47) `def read(self, ino)`
  - `resolve` (method, line 67) `def resolve(self, path)`
  - `ls` (method, line 86) `def ls(self, ino, prefix)`

## minifs_fsck.py
- Layer: utility
- Language: py
- Symbols:
  - `u16` (function, line 13) `def u16(d, o)`
  - `u32` (function, line 14) `def u32(d, o)`
  - `FSCK` (class, line 16) `class FSCK`
  - `main` (method, line 136) `def main()`
  - `__init__` (method, line 17) `def __init__(self, fn)`
  - `_find_base` (method, line 24) `def _find_base(self)`
  - `blk` (method, line 42) `def blk(self, n)`
  - `_sb` (method, line 45) `def _sb(self)`
  - `inode` (method, line 51) `def inode(self, i)`
  - `read` (method, line 58) `def read(self, ino)`
  - `err` (method, line 73) `def err(self, msg)`
  - `mark_block` (method, line 75) `def mark_block(self, n)`
  - `scan_inode` (method, line 80) `def scan_inode(self, i)`
  - `scan_dir` (method, line 89) `def scan_dir(self, ino)`
  - `run` (method, line 121) `def run(self)`

## mkfs.minifs.py
- Layer: utility
- Language: py
- Symbols:
  - `roundup4` (function, line 22) `def roundup4(v)`
  - `div_round_up` (function, line 25) `def div_round_up(n, d)`
  - `crc16` (function, line 28) `def crc16(data)`
  - `crc32` (function, line 36) `def crc32(data)`
  - `MiniFS` (class, line 44) `class MiniFS`
  - `main` (method, line 241) `def main()`
  - `__init__` (method, line 45) `def __init__(self, total_blocks)`
  - `mark_inodes_used` (method, line 67) `def mark_inodes_used(self, start, count)`
  - `mark_blocks_used` (method, line 71) `def mark_blocks_used(self, start, count)`
  - `alloc_inode` (method, line 75) `def alloc_inode(self)`
  - `alloc_block` (method, line 81) `def alloc_block(self)`
  - `create_root` (method, line 87) `def create_root(self)`
  - `create_inode` (method, line 95) `def create_inode(self, mode)`
  - `inode_set_size` (method, line 102) `def inode_set_size(self, ino, size)`
  - `inode_set_block` (method, line 106) `def inode_set_block(self, ino, logblk, phys)`
  - `add_dir_entry` (method, line 136) `def add_dir_entry(self, dir_ino, name, child_ino, ftype)`
  - `write_file` (method, line 174) `def write_file(self, parent_ino, name, data)`
  - `write_dir` (method, line 191) `def write_dir(self, parent_ino, name)`
  - `serialize` (method, line 197) `def serialize(self)`
  - `pack_tree` (method, line 271) `def pack_tree(parent_ino, path, rel)`

## mkramdisk.py
- Layer: infrastructure
- Language: py
- Symbols:
  - `pack_name` (function, line 20) `def pack_name(path, common)`
  - `main` (function, line 30) `def main()`

## mkroots.sh
- Layer: utility
- Doc: mkroots.sh - regenerate tls_roots.h from the DER files in tls_roots_src/.  Provenance of each root (2026 web PKI reality
- Language: sh

## mutate.sh
- Layer: utility
- Doc: Mutation testing for MiniOS.  Each mutation is applied to the source in place, the disk image is rebuilt and the behavio
- Language: sh
- Symbols:
  - `usage` (function, line 51)
  - `restore_sources` (function, line 101)
  - `cleanup` (function, line 108)
  - `record` (function, line 283)
  - `find_index` (function, line 289)

## qga.c
- Layer: utility
- Doc: MiniOS QEMU guest agent (QGA).
- Language: c
- Symbols:
  - `qga_pair` (struct, line 49)
  - `qga_tx_ready` (function, line 26) `static int qga_tx_ready(void)`
  - `qga_rx_ready` (function, line 28) `static int qga_rx_ready(void)`
  - `qga_putc` (function, line 29) `static void qga_putc(char c)`
  - `qga_init` (function, line 34) `void qga_init(void)`
  - `qga_ws` (function, line 55) `static int qga_ws(char c)`
  - `qga_parse_object` (function, line 65) `static int qga_parse_object(const char **pp, struct qga_pair *out, int max,
                     ...`
  - `qga_parse_flat` (function, line 147) `static int qga_parse_flat(const char *s, struct qga_pair *out, int max)`
  - `qga_get_str` (function, line 157) `static const char *qga_get_str(const struct qga_pair *pairs, int n, const char *key)`
  - `qga_get_int` (function, line 165) `static int qga_get_int(const struct qga_pair *pairs, int n, const char *key, long *out)`
  - `qga_resp_reset` (function, line 183) `static void qga_resp_reset(void)`
  - `qga_resp_puts` (function, line 185) `static void qga_resp_puts(const char *s)`
  - `qga_resp_putc_enc` (function, line 193) `static void qga_resp_putc_enc(char c)`
  - `qga_resp_put_long` (function, line 201) `static void qga_resp_put_long(long v)`
  - `qga_err` (function, line 209) `static void qga_err(const char *klass, const char *desc)`
  - `qga_puts_resp` (function, line 217) `static void qga_puts_resp(void)`
  - `qga_b64_encode` (function, line 230) `static void qga_b64_encode(const unsigned char *in, int n)`
  - `qga_cmd_get_time` (function, line 280) `static void qga_cmd_get_time(void)`
  - `qga_cmd_exec` (function, line 306) `static void qga_cmd_exec(const struct qga_pair *pairs, int n)`
  - `qga_cmd_shutdown` (function, line 315) `static void qga_cmd_shutdown(const struct qga_pair *pairs, int n)`
  - `qga_file_size` (function, line 328) `static int qga_file_size(const KFILE *f)`
  - `qga_cmd_file_open` (function, line 333) `static void qga_cmd_file_open(const struct qga_pair *pairs, int n)`
  - `qga_cmd_file_read` (function, line 359) `static void qga_cmd_file_read(const struct qga_pair *pairs, int n)`
  - `qga_cmd_file_close` (function, line 383) `static void qga_cmd_file_close(const struct qga_pair *pairs, int n)`
  - `qga_dispatch` (function, line 400) `static void qga_dispatch(struct qga_pair *pairs, int n)`
  - `qga_poll` (function, line 446) `void qga_poll(void)`
  - `channel` (function, line 9) `* * Polled channel (no interrupt controller): qga_init sets up COM2 and * qga_poll, called from raw_blocking_getc, services one complete line per * call. Every input path is bounded and fail-closed: a`
  - `outb` (function, line 32) `outb(QGA_COM2_BASE + QGA_UART_THR, (unsigned char)c);`
  - `kstrcpy` (function, line 90) `else kstrcpy(np, key);`
  - `shell_queue_launch` (function, line 312) `shell_queue_launch(path);`
  - `kfclose` (function, line 391) `kfclose(qga_files[handle]);`
- Depends on: `headers/kernel.h`, `headers/qga.h`, `headers/rtc.h`

## smp.c
- Layer: utility
- Doc: include "kernel.h" include "bootdefs.h" include "smp.h" include "sched.h" include "ap_stub.h" include "arch/x86/msr.h"  
- Language: c
- Symbols:
  - `lapic_read` (function, line 83) `static unsigned lapic_read(unsigned off)`
  - `lapic_write` (function, line 87) `static void lapic_write(unsigned off, unsigned val)`
  - `map_lapic` (function, line 108) `static int map_lapic(void)`
  - `ap_delay` (function, line 120) `static void ap_delay(void)`
  - `lapic_calibrate` (function, line 149) `static void lapic_calibrate(void)`
  - `ap_lapic_timer_start` (function, line 184) `static void ap_lapic_timer_start(void)`
  - `ap_lapic_timer_init` (function, line 190) `static void ap_lapic_timer_init(void)`
  - `smp_init` (function, line 304) `void smp_init(void)`
  - `syscall_entry` (function, line 82) `extern void syscall_entry(void);`
  - `volatile` (function, line 117) `__asm__ volatile("invlpg (%0)" : : "r"(LAPIC_BASE) : "memory");`
  - `wrmsr` (function, line 229) `wrmsr(MSR_GSBASE, (unsigned long)&cpus[cpu]);`
  - `BSP` (function, line 238) `* were programmed only on the BSP (syscall_init runs in kmain), so * an AP's first sysretq loaded SS from a zeroed STAR (selector 0x08, * kernel code, as SS) and died with #SS. The values mirror * sys`
  - `tss_init_ap` (function, line 258) `tss_init_ap(cpu);`
  - `spin_lock_irqsave` (function, line 280) `spin_lock_irqsave(&smp_lock, &flags);`
  - `spin_unlock_irqrestore` (function, line 282) `spin_unlock_irqrestore(&smp_lock, flags);`
  - `smp_ap_idle_loop` (function, line 299) `smp_ap_idle_loop();`
  - `kmemcpy` (function, line 318) `kmemcpy((void *)(unsigned long)AP_STUB_ADDR, ap_stub_blob, ap_stub_len);`
  - `INIT` (function, line 323) `* INIT (edge-triggered): resets APs to wait-for-SIPI state. * QEMU 11 drops level-triggered INIT (delivery status never clears), * so edge-triggered is used. Two SIPIs deliver the startup vector. */ l`
  - `kprintf` (function, line 348) `else kprintf("SMP: 1 CPU (APs not woken)\n");`
  - `smp_ipi_broadcast` (function, line 355) `smp_ipi_broadcast(32);`
  - `LAPIC_BASE` (macro, line 27) `#define LAPIC_BASE`
  - `LAPIC_ID_OFF` (macro, line 29) `#define LAPIC_ID_OFF`
  - `LAPIC_SVR_OFF` (macro, line 30) `#define LAPIC_SVR_OFF`
  - `LAPIC_ICR_HI` (macro, line 31) `#define LAPIC_ICR_HI`
  - `LAPIC_ICR_LO` (macro, line 32) `#define LAPIC_ICR_LO`
  - `LAPIC_LVT_TIMER` (macro, line 33) `#define LAPIC_LVT_TIMER`
  - `LAPIC_LVT_LINT0` (macro, line 34) `#define LAPIC_LVT_LINT0`
  - `LAPIC_LVT_LINT1` (macro, line 35) `#define LAPIC_LVT_LINT1`
  - `LAPIC_LVT_MASKED` (macro, line 36) `#define LAPIC_LVT_MASKED`
  - `LAPIC_LVT_EXTINT` (macro, line 37) `#define LAPIC_LVT_EXTINT`
  - `LAPIC_EOI_OFF` (macro, line 38) `#define LAPIC_EOI_OFF`
  - `LAPIC_TIMER_DIV` (macro, line 39) `#define LAPIC_TIMER_DIV`
  - `LAPIC_TIMER_INIT` (macro, line 40) `#define LAPIC_TIMER_INIT`
  - `LAPIC_TIMER_CUR` (macro, line 41) `#define LAPIC_TIMER_CUR`
  - `LAPIC_SVR_ENABLE` (macro, line 42) `#define LAPIC_SVR_ENABLE`
  - `LAPIC_ICR_BUSY` (macro, line 44) `#define LAPIC_ICR_BUSY`
  - `LAPIC_ICR_INIT` (macro, line 45) `#define LAPIC_ICR_INIT`
  - `LAPIC_ICR_SIPI` (macro, line 46) `#define LAPIC_ICR_SIPI`
  - `LAPIC_ICR_ALL_EXC` (macro, line 47) `#define LAPIC_ICR_ALL_EXC`
  - `LAPIC_ICR_LEVEL` (macro, line 48) `#define LAPIC_ICR_LEVEL`
  - `LAPIC_ICR_TRIGGER` (macro, line 49) `#define LAPIC_ICR_TRIGGER`
  - `SIPI_VECTOR` (macro, line 50) `#define SIPI_VECTOR`
  - `PIT_HZ` (macro, line 54) `#define PIT_HZ`
  - `LAPIC_TIMER_DIVIDE_16` (macro, line 57) `#define LAPIC_TIMER_DIVIDE_16`
  - `LAPIC_TIMER_PERIODIC` (macro, line 58) `#define LAPIC_TIMER_PERIODIC`
  - `LAPIC_PD_ADDR` (macro, line 66) `#define LAPIC_PD_ADDR`
  - `LAPIC_PDPT_SLOT` (macro, line 67) `#define LAPIC_PDPT_SLOT`
  - `LAPIC_PD_IDX` (macro, line 68) `#define LAPIC_PD_IDX`
- Depends on: `headers/ap_stub.h`, `headers/arch/x86/boot/bootdefs.h`, `headers/arch/x86/msr.h`, `headers/kernel.h`, `headers/sched.h`, `headers/smp.h`

## test_bdd.sh
- Layer: testing
- Doc: BDD suite for MiniOS: boots the disk image in QEMU and drives the shell over the serial console (COM1). Every scenario s
- Language: sh
- Symbols:
  - `should_run` (function, line 35)
  - `cleanup_stale_qemu` (function, line 43)
  - `scenario` (function, line 54)
  - `scenario_smp` (function, line 74)
  - `expect` (function, line 97)
  - `expect_count` (function, line 119)
  - `refute` (function, line 142)
  - `http_server_start` (function, line 853)
  - `http_server_stop` (function, line 860)
  - `http_fixture_start` (function, line 865)
  - `http_fixture_stop` (function, line 872)

## test_http_server.py
- Layer: testing
- Language: py
- Symbols:
  - `Handler` (class, line 21) `class Handler(BaseHTTPRequestHandler)`
  - `do_GET` (method, line 24) `def do_GET(self)`
  - `log_message` (method, line 114) `def log_message(self, fmt)`
- Depends on: `kernel/time.c`

## tls_test.c
- Layer: testing
- Doc: tls_test.c - host-side tests for the kernel TLS stack.
- Language: c
- Symbols:
  - `tls_test_send` (function, line 25) `int tls_test_send(int fd, const char *buf, int len)`
  - `tls_test_recv` (function, line 35) `int tls_test_recv(int fd, char *buf, int len)`
  - `tls_test_recv_timeout` (function, line 40) `int tls_test_recv_timeout(int fd, char *buf, int len, unsigned long ms)`
  - `tls_test_close` (function, line 53) `void tls_test_close(int fd)`
  - `hexdigit` (function, line 66) `static int hexdigit(int c)`
  - `unhex` (function, line 73) `static void unhex(const char *hex, unsigned char *out, int n)`
  - `bytes_eq` (function, line 79) `static int bytes_eq(const unsigned char *a, const unsigned char *b, int n)`
  - `test_sha256` (function, line 87) `static void test_sha256(void)`
  - `test_sha384` (function, line 102) `static void test_sha384(void)`
  - `test_gcm` (function, line 113) `static void test_gcm(void)`
  - `test_p256` (function, line 153) `static void test_p256(void)`
  - `test_rsa_ecdsa_vectors` (function, line 199) `static void test_rsa_ecdsa_vectors(void)`
  - `tcp_connect` (function, line 248) `static int tcp_connect(int port)`
  - `http_over_tls` (function, line 265) `static int http_over_tls(int port, const char *host)`
  - `scenario_good` (function, line 289) `static int scenario_good(int port)`
  - `scenario_wild_good` (function, line 295) `static int scenario_wild_good(int port)`
  - `scenario_wild_root` (function, line 298) `static int scenario_wild_root(int port)`
  - `scenario_wild_deep` (function, line 308) `static int scenario_wild_deep(int port)`
  - `scenario_bad_host` (function, line 318) `static int scenario_bad_host(int port)`
  - `scenario_bad_ca` (function, line 328) `static int scenario_bad_ca(int port)`
  - `scenario_expired` (function, line 338) `static int scenario_expired(int port)`
  - `main` (function, line 348) `int main(int argc, char **argv)`
  - `FD_ZERO` (function, line 47) `FD_ZERO(&fds);`
  - `FD_SET` (function, line 48) `FD_SET(fd, &fds);`
  - `close` (function, line 55) `close(fd);`
  - `sha256` (function, line 95) `sha256((const unsigned char *)"abc", 3, out);`
  - `CHECK` (function, line 97) `CHECK("sha256 abc", bytes_eq(out, want, 32));`
  - `sha384` (function, line 109) `sha384((const unsigned char *)"abc", 3, out);`
  - `memset` (function, line 194) `memset(ox, 0, 32);`
  - `memcpy` (function, line 211) `memcpy(bad, test_rsa_sig, sizeof(test_rsa_sig));`
  - `fwrite` (function, line 280) `fwrite(buf, 1, (size_t)n, stdout);`
  - `tls_free_fd` (function, line 284) `tls_free_fd(fd);`
  - `printf` (function, line 350) `printf("tls_test\n");`
  - `CHECK` (macro, line 61) `#define CHECK(name, cond)`
- Depends on: `headers/tls.h`, `headers/tls_port.h`, `headers/tls_test_roots.h`, `kernel/string.c`

## tls_test.py
- Layer: testing
- Language: py
- Symbols:
  - `run` (function, line 26) `def run(cmd)`
  - `check` (function, line 30) `def check(cmd)`
  - `gen_certs` (function, line 37) `def gen_certs()`
  - `der_bytes` (function, line 154) `def der_bytes(pem_path)`
  - `rsa_params` (function, line 162) `def rsa_params(key_path)`
  - `ec_pub` (function, line 172) `def ec_pub(key_path)`
  - `c_bytes` (function, line 183) `def c_bytes(data, name)`
  - `gen_header` (function, line 191) `def gen_header(p)`
  - `Server` (class, line 241) `class Server(Thread)`
  - `serve` (method, line 280) `def serve(cert, key)`
  - `serve_openssl` (method, line 288) `def serve_openssl(cert, key, chain)`
  - `expect` (method, line 306) `def expect(bin_path, args, want_zero, marker)`
  - `main` (method, line 319) `def main()`
  - `server_cert` (method, line 61) `def server_cert(name, algo, curve, ca_name, ca_algo, curve_ca, extra, subj)`
  - `__init__` (method, line 242) `def __init__(self, cert, key, tls13_ok)`
  - `run` (method, line 248) `def run(self)`
- Depends on: `kernel/time.c`

## vma.c
- Layer: utility
- Doc: include "vma.h"
- Language: c
- Symbols:
  - `vma_ctx_init` (function, line 31) `void vma_ctx_init(vma_ctx_t *c, vma_node_t *pool)`
  - `vma_ctx_bind` (function, line 45) `void vma_ctx_bind(vma_ctx_t *c)`
  - `vma_ctx_save` (function, line 56) `void vma_ctx_save(vma_ctx_t *c)`
  - `vma_tree_init` (function, line 65) `void vma_tree_init(void)`
  - `vma_alloc_node` (function, line 79) `static vma_node_t *vma_alloc_node(void)`
  - `vma_rotate_left` (function, line 85) `static void vma_rotate_left(vma_node_t **root, vma_node_t *x)`
  - `vma_rotate_right` (function, line 97) `static void vma_rotate_right(vma_node_t **root, vma_node_t *x)`
  - `vma_insert_fixup` (function, line 109) `static void vma_insert_fixup(vma_node_t **root, vma_node_t *z)`
  - `vma_tree_insert` (function, line 148) `vma_node_t *vma_tree_insert(vma_node_t **root, unsigned long base, unsigned long len)`
  - `vma_tree_find` (function, line 171) `vma_node_t *vma_tree_find(vma_node_t *root, unsigned long base)`
  - `vma_transplant` (function, line 183) `static void vma_transplant(vma_node_t **root, vma_node_t *u, vma_node_t *v)`
  - `vma_tree_minimum` (function, line 190) `static vma_node_t *vma_tree_minimum(vma_node_t *x)`
  - `vma_delete_fixup` (function, line 195) `static void vma_delete_fixup(vma_node_t **root, vma_node_t *x)`
  - `vma_tree_delete` (function, line 250) `int vma_tree_delete(vma_node_t **root, unsigned long base)`
- Depends on: `headers/vma.h`
