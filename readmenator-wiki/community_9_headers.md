# headers

*Community 9 | 11 files | cohesion 0.42*

## Definition

This community groups 11 file(s) rooted at `headers` with dominant language c (cohesion 0.42). Central symbols: `ALIGN_UP`, `C`, `CHECK`, `CMD_BUF_SZ`, `DEV_MMIO_VBASE`, `EBADF`, `EDITOR_H`, `EDIT_FILE_MAX`. Core file: `headers/kernel.h` (383 symbols). Documented purpose: the built-in line editor contract..

## Files

| File | Language | Layer | Symbols | Doc |
|------|----------|-------|---------|-----|
| `headers/editor.h` | h | infrastructure | 2 | yes |
| `headers/kernel.h` | h | utility | 383 | yes |
| `headers/pipe.h` | h | utility | 15 | yes |
| `headers/shell.h` | h | utility | 8 | yes |
| `headers/vma.h` | h | utility | 25 | no |
| `kernel/editor.c` | c | infrastructure | 22 | yes |
| `tests/test_fault.c` | c | testing | 11 | yes |
| `tests/test_pipe.c` | c | testing | 2 | yes |
| `tests/test_vma.c` | c | testing | 9 | yes |
| `tests/test_vma_bench.c` | c | testing | 6 | yes |
| `vma.c` | c | utility | 17 | no |

## Key Symbols

- `EDITOR_H` (macro, `headers/editor.h:2`) `#define EDITOR_H`
- `shell_cmd_edit` (function, `headers/editor.h:15`) `void shell_cmd_edit(int argc, char **argv);`
- `KERNEL_H` (macro, `headers/kernel.h:2`) `#define KERNEL_H`
- `EFAULT` (macro, `headers/kernel.h:4`) `#define EFAULT`
- `ALIGN_UP` (macro, `headers/kernel.h:20`) `#define ALIGN_UP(x, a)`
- `PORT_IO_DEFINED` (macro, `headers/kernel.h:22`) `#define PORT_IO_DEFINED`
- `ktime_ms` (function, `headers/kernel.h:25`) `unsigned long ktime_ms(void);` - Forward: PIT-calibrated wall clock (defined in kernel/time.c); valid * once pit_init has run. Used o
- `outb` (function, `headers/kernel.h:26`) `static inline void outb(unsigned short port, unsigned char val)`
- `inb` (function, `headers/kernel.h:29`) `static inline unsigned char inb(unsigned short port)`
- `outw` (function, `headers/kernel.h:34`) `static inline void outw(unsigned short port, unsigned short val)`
- `inw` (function, `headers/kernel.h:37`) `static inline unsigned short inw(unsigned short port)`
- `insw` (function, `headers/kernel.h:47`) `static inline void insw(unsigned short port, unsigned short *buf,` - String port I/O: one instruction moves `count` words between the port and the buffer.  Under KVM eve
- `outsw` (function, `headers/kernel.h:54`) `static inline void outsw(unsigned short port, const unsigned short *buf,`
- `waits` (function, `headers/kernel.h:64`) `* and mouse_hw_init issues dozens of waits (measured 5 s of boot).  This  * poll`
- `VGA_BASE` (macro, `headers/kernel.h:90`) `#define VGA_BASE`
- `VGA_COLS` (macro, `headers/kernel.h:91`) `#define VGA_COLS`
- `VGA_ROWS` (macro, `headers/kernel.h:92`) `#define VGA_ROWS`
- `vga_clear` (function, `headers/kernel.h:94`) `void vga_clear(void);`
- `vga_putc` (function, `headers/kernel.h:95`) `void vga_putc(char c);`
- `vga_puts` (function, `headers/kernel.h:96`) `void vga_puts(const char *s);`
- `vga_scroll` (function, `headers/kernel.h:97`) `void vga_scroll(void);`
- `vga_set_cursor` (function, `headers/kernel.h:98`) `void vga_set_cursor(int x, int y);`
- `vga_newline` (function, `headers/kernel.h:99`) `void vga_newline(void);`
- `vga_cursor_enable` (function, `headers/kernel.h:100`) `void vga_cursor_enable(int on);`
- `console_lock` (variable, `headers/kernel.h:105`) `extern spinlock_t console_lock;` - Console output lock (kernel/console.c): serializes SMP console output across CPUs. Held across the w
- `vga_get_x` (function, `headers/kernel.h:108`) `int vga_get_x(void);` - Console output lock (kernel/console.c): serializes SMP console output across CPUs. Held across the w
- `vga_get_y` (function, `headers/kernel.h:109`) `int vga_get_y(void);`
- `vga_set_xy` (function, `headers/kernel.h:110`) `void vga_set_xy(int x, int y);`
- `vga_get_color` (function, `headers/kernel.h:111`) `char vga_get_color(void);`
- `minfo_sleep_init` (function, `headers/kernel.h:116`) `void minfo_sleep_init(int tick_ok);` - MINFO sleep support (kernel/syscalls.c): timed park for ring-3 monitors. sched_init passes the tick-

## Internal vs External Edges

- Internal resolved imports (EXTRACTED): 11
- Cross-boundary resolved imports (EXTRACTED): 15

## Connections

- [EXTRACTED] depends_on community 9 <-> 7 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports progs/minios_abi.h.
- [EXTRACTED] depends_on community 9 <-> 0 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports headers/ldso.h.
- [EXTRACTED] depends_on community 9 <-> 10 (strength 0.9): Extracted import edge crosses communities: headers/kernel.h imports headers/spinlock.h.
- [EXTRACTED] depends_on community 9 <-> 4 (strength 0.9): Extracted import edge crosses communities: headers/shell.h imports headers/kernel/console_in.h.
- [EXTRACTED] depends_on community 16 <-> 9 (strength 0.9): Extracted import edge crosses communities: headers/tls_port.h imports headers/kernel.h.

## Risks

- No scoped security, taint, cycle, or layer risks.

## Open Questions

- Why do 2 file(s) lack file-level docs (e.g. `headers/vma.h`)? What purpose do they serve?
- What would break if the most connected file in headers changed?
- Should headers be split, given cohesion 0.42?

## Sources

- `headers/editor.h`
- `headers/kernel.h`
- `headers/pipe.h`
- `headers/shell.h`
- `headers/vma.h`
- `kernel/editor.c`
- `tests/test_fault.c`
- `tests/test_pipe.c`
- `tests/test_vma.c`
- `tests/test_vma_bench.c`
- `vma.c`
