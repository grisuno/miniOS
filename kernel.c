#include "kernel.h"
#include "net.h"
#include "tls.h"
#include "bootdefs.h"
#include "minifs.h"
#include "ide.h"
#include "block.h"
#include "sched.h"
#include "vga_fb.h"
#include "pcspk.h"
#include "sb16.h"
#include "smp.h"
#include "rtc.h"
#include "lz4_kernel.h"
#include "drivers/kbd.h"
#include "arch/x86/msr.h"
#define XXH_STATIC_LINKING_ONLY
#include "xxhash.h"
#include "stb/stb_api.h"
#include "zip.h"

/* ================================================================
 *  VGA driver
 * ================================================================ */

/* vga_mode13h and graphics_program_ran moved to kernel/exec.c */
static int vga_x, vga_y;
static char vga_color = 0x07; /* light grey on black */

int vga_get_x(void) { return vga_x; }
int vga_get_y(void) { return vga_y; }
void vga_set_xy(int x, int y) { vga_x = x; vga_y = y; }
char vga_get_color(void) { return vga_color; }

/* Scrollback ring moved to kernel/scrollback.c */

static inline unsigned vga_offset(int x, int y) { return (unsigned)(y * VGA_COLS + x) * 2; }

void vga_clear(void) {
    int i;
    for (i = 0; i < VGA_COLS * VGA_ROWS; i++) {
        VGA_BASE[i * 2]     = ' ';
        VGA_BASE[i * 2 + 1] = vga_color;
    }
    vga_x = vga_y = 0;
    vga_set_cursor(0, 0);
    sb_reset();
}

void vga_set_cursor(int x, int y) {
    unsigned short pos = (unsigned short)(y * VGA_COLS + x);
    unsigned char lo = pos & 0xFF;
    unsigned char hi = (pos >> 8) & 0xFF;
    __asm__ volatile(
        "movw $0x3D4, %%dx\n\t"
        "movb $0x0F, %%al\n\t"
        "outb %%al, %%dx\n\t"
        "movb %b0, %%al\n\t"
        "outb %%al, %%dx\n\t"
        "movb $0x0E, %%al\n\t"
        "outb %%al, %%dx\n\t"
        "movb %b1, %%al\n\t"
        "outb %%al, %%dx"
        :
        : "r"((unsigned long)lo), "r"((unsigned long)hi)
        : "ax", "dx"
    );
}

void vga_scroll(void) {
    int y, x;
    sb_capture_row0();
    for (y = 0; y < VGA_ROWS - 1; y++) {
        for (x = 0; x < VGA_COLS; x++) {
            unsigned src = vga_offset(x, y + 1);
            unsigned dst = vga_offset(x, y);
            VGA_BASE[dst]     = VGA_BASE[src];
            VGA_BASE[dst + 1] = VGA_BASE[src + 1];
        }
    }
    for (x = 0; x < VGA_COLS; x++) {
        unsigned off = vga_offset(x, VGA_ROWS - 1);
        VGA_BASE[off]     = ' ';
        VGA_BASE[off + 1] = vga_color;
    }
    vga_y = VGA_ROWS - 1;
}

void vga_newline(void) {
    vga_x = 0;
    vga_y++;
    if (vga_y >= VGA_ROWS) vga_scroll();
}

/* Scrollback ring moved to kernel/scrollback.c */

/* Toggle the hardware text cursor. bit 5 of VGA index 0x0A disables the
 * cursor; clearing it brings the cursor back. */
void vga_cursor_enable(int on) {
    outb(0x3D4, 0x0A);
    unsigned char v = inb(0x3D5);
    if (on) v &= 0xDF; else v |= 0x20;
    outb(0x3D5, v);
}

static void vga_raw_space(void) {
    unsigned off = vga_offset(vga_x, vga_y);
    VGA_BASE[off]     = ' ';
    VGA_BASE[off + 1] = vga_color;
    vga_x++;
    if (vga_x >= VGA_COLS) vga_newline();
}


/* ================================================================
 *  Console output capture (redirect)
 *  Hot path: redirect_putc is inlined into vga_putc below.
 * ================================================================ */

#define REDIR_INITIAL_CAP (16UL * 1024)
#define REDIR_MAX_BYTES   (16UL * 1024 * 1024)

static char         *redir_buf;
static unsigned long  redir_len;
static unsigned long  redir_cap;
static int            redir_active;
static int            redir_overflow;

static int redir_grow(void) {
    unsigned long want = redir_cap ? redir_cap * 2 : REDIR_INITIAL_CAP;
    if (want > REDIR_MAX_BYTES) return 0;
    char *grown = krealloc(redir_buf, want);
    if (!grown) return 0;
    redir_buf = grown;
    redir_cap = want;
    return 1;
}

int redirect_active(void) { return redir_active; }

static int redirect_putc(char c) {
    if (!redir_active) return 0;
    if (redir_len < redir_cap || redir_grow()) redir_buf[redir_len++] = c;
    else redir_overflow = 1;
    return 1;
}

int redirect_suspend(void) {
    int was = redir_active;
    redir_active = 0;
    return was;
}

void redirect_resume(int was) {
    redir_active = was;
}

int redirect_begin(void) {
    redir_len      = 0;
    redir_overflow = 0;
    if (!redir_buf && !redir_grow()) return 0;
    redir_active = 1;
    return 1;
}

int redirect_commit(const char *path, int append_mode) {
    KFILE *f;
    unsigned long written;
    int rc;

    redir_active = 0;
    if (redir_overflow) { redir_len = 0; return -1; }

    f = kfopen(path, append_mode ? "a" : "w");
    if (!f) { redir_len = 0; return -1; }
    written = redir_len ? kfwrite(redir_buf, 1, redir_len, f) : 0;
    rc = kfclose(f);
    if (redir_len && written != redir_len) rc = -1;
    redir_len = 0;
    return rc;
}

void vga_putc(char c) {
    if (redirect_putc(c)) return;
    serial_putc(c);
    if (vga_fb_active) {
        if (c == '\n') serial_putc('\r');
        vga_fb_putc_term(c);
        return;
    }
    if (vga_mode_is_active()) {
        if (c == '\n') serial_putc('\r');
        return;
    }
    if (c == '\n') { serial_putc('\r'); vga_newline(); vga_set_cursor(vga_x, vga_y); return; }
    if (c == '\r') { vga_x = 0; vga_set_cursor(vga_x, vga_y); return; }
    if (c == '\t') {
        int spaces = 8 - (vga_x & 7);
        while (spaces--) vga_raw_space();
        vga_set_cursor(vga_x, vga_y);
        return;
    }
    if (c == '\b') {
        if (vga_x > 0) {
            vga_x--;
            unsigned off = vga_offset(vga_x, vga_y);
            VGA_BASE[off] = ' ';
            VGA_BASE[off + 1] = vga_color;
            vga_set_cursor(vga_x, vga_y);
        }
        return;
    }
    unsigned off = vga_offset(vga_x, vga_y);
    VGA_BASE[off]     = c;
    VGA_BASE[off + 1] = vga_color;
    vga_x++;
    if (vga_x >= VGA_COLS) vga_newline();
    vga_set_cursor(vga_x, vga_y);
}

void vga_puts(const char *s) {
    while (*s) vga_putc(*s++);
}


/* ================================================================
 *  Keyboard driver — see drivers/kbd.c
 * ================================================================ */


/* ================================================================
 *  Memory allocator — dlmalloc backend over the fixed kernel heap.
 *  kmalloc/free/calloc/realloc delegate to a private mspace rooted at
 *  [HEAP_BASE, HEAP_BASE+HEAP_SIZE) (see third_party/dlmalloc). The
 *  mspace is built with HAVE_MORECORE=0 and HAVE_MMAP=0, so it can
 *  never grow beyond the heap; an exhausted heap returns 0 exactly
 *  like the first-fit allocator it replaced.
 * ================================================================ */

/* ---- Physical memory map (identity-mapped 0..1GB by the bootloader) ----
 * The user-window and kernel-heap layout lives in progs/minios_abi.h (single
 * source of truth) and is surfaced through kernel.h, so a layout change is a
 * one-line edit in one file instead of a cross-file address hunt.
 *   0x00000000 .. 0x00100000   BIOS / kernel image / page tables / stack
 *   0x00400000 .. 0x0C000000   user program region (ELF load addr + brk)
 *   0x0C000000 .. 0x18000000   192 MB kernel heap (HEAP_BASE/HEAP_SIZE)
 */

/* Asm-safe (no UL suffix) mirror of the user window for the syscall-entry
 * return discriminator; the trampoline is a raw string literal, so the C
 * preprocessor cannot paste the UL-suffixed macros into it. The values must
 * track minios_abi.h; the _Static_asserts below prove they do. */
#define USER_WIN_LO     0x00400000
#define USER_WIN_HI     0x0C000000
#define STR_(x) #x
#define STR(x)  STR_(x)

/* The kernel's layout constants are derived from minios_abi.h, and the
 * asm-safe mirrors above are checked against them at compile time, so a
 * layout edit in the ABI header can never silently leave the syscall return
 * discriminator, the page-table zone sizing or a ring-3 program out of step. */
_Static_assert(USER_WIN_LO == MINIOS_USER_LOAD_BASE, "USER_WIN_LO drift");
_Static_assert(USER_WIN_HI == MINIOS_USER_LOAD_END, "USER_WIN_HI drift");
_Static_assert(USER_LOAD_BASE == MINIOS_USER_LOAD_BASE, "USER_LOAD_BASE drift");
_Static_assert(USER_LOAD_END == MINIOS_USER_LOAD_END, "USER_LOAD_END drift");
_Static_assert(USER_STACK_TOP == MINIOS_USER_STACK_TOP, "USER_STACK_TOP drift");
_Static_assert(USER_BRK_END == MINIOS_USER_BRK_END, "USER_BRK_END drift");
_Static_assert(HEAP_BASE == MINIOS_HEAP_BASE, "HEAP_BASE drift");
_Static_assert(HEAP_SIZE == MINIOS_HEAP_SIZE, "HEAP_SIZE drift");

/* SYSCALL/SYSRET setup and page table code moved to:
 *   arch/x86/msr.h          - wrmsr/rdmsr
 *   kernel/mm/paging.c      - page table management
 *   kernel/mm/swap.c        - swap-out/swap-in
 */



/* Code moved to kernel/mm/paging.c */



/* ================================================================
 *  Ramdisk file system
 * ================================================================ */





/* ================================================================
 *  Symbol table (for resolving program references)
 * ================================================================ */

#define KSYM_MAX 256




/* ---- SYSCALL/SYSRET setup ---------------------------------- */

extern void syscall_entry(void);
extern unsigned long syscall_kstack;

void syscall_init(void) {
    /* SYSCALL loads CS=0x08, SS=0x10 from STAR[47:32]. SYSRET derives its
     * selectors from STAR[63:48]: CS = n + 16 = 0x20 (user code), SS =
     * n + 8 = 0x18 (user data), the Linux layout. */
    wrmsr(MSR_STAR,  ((unsigned long)GDT64_DATA_SEL << 48) | ((unsigned long)GDT64_CODE_SEL << 32));
    wrmsr(MSR_LSTAR, (unsigned long)syscall_entry);
    wrmsr(MSR_SFMASK, 0x600); /* clear DF and IF on entry */
    wrmsr(MSR_EFER, rdmsr(MSR_EFER) | 1); /* SCE: enable SYSCALL */
}


/* ---- Syscall dispatcher moved to kernel/syscalls.c -------------------- */

extern long ksyscall(long n, long a1, long a2, long a3, long a4, long a5, long a6);


/* ksyscall_dispatch, kfd_table, user_range_ok, user_str_ok, k_syscall_spawn
 * moved to kernel/syscalls.c */


/* ---- syscall trampoline: marshal Linux ABI regs into the C ABI ----------
 * The kernel stack is a fixed region (SYS_KSTK_TOP) exchanged on entry, so
 * the kernel never runs on a user stack and never touches the user red
 * zone. `syscall_kstack` holds the kernel stack top while a program runs
 * and the incoming rsp during a syscall. The return discriminates on the
 * restored rsp: a syscall that came from ring 3 ran on the user stack in
 * the user window and returns with sysretq (ring 3); a ring-0 ET_REL
 * syscall ran on a kernel stack and returns with `jmp *%rcx`, the old
 * contract, because sysretq always lands on ring 3. */

__asm__(
    ".text\n"
    ".global syscall_kstack\n"
    ".data\n"
    ".align 8\n"
    "syscall_kstack:\n"
    "  .quad 0\n"
    ".text\n"
    ".global syscall_entry\n"
    "syscall_entry:\n"
    "  xchgq %rsp, syscall_kstack(%rip)\n"
    "  pushq %r9\n"              /* 64(%rsp) a6 */
    "  pushq %r8\n"              /* 56       a5 */
    "  pushq %r10\n"             /* 48       a4 */
    "  pushq %rdx\n"             /* 40       a3 */
    "  pushq %rsi\n"             /* 32       a2 */
    "  pushq %rdi\n"             /* 24       a1 */
    "  pushq %rax\n"             /* 16       n / return value slot */
    "  pushq %rcx\n"             /*  8       user rip */
    "  pushq %r11\n"             /*  0       user rflags */
    "  movq 16(%rsp), %rdi\n"    /* C arg1 = n  */
    "  movq 24(%rsp), %rsi\n"    /* C arg2 = a1 */
    "  movq 32(%rsp), %rdx\n"    /* C arg3 = a2 */
    "  movq 40(%rsp), %rcx\n"    /* C arg4 = a3 */
    "  movq 48(%rsp), %r8\n"     /* C arg5 = a4 */
    "  movq 56(%rsp), %r9\n"     /* C arg6 = a5 */
    "  movq 64(%rsp), %rax\n"
    "  pushq %rax\n"             /* C arg7 = a6 (stack) */
    "  call ksyscall\n"
    "  addq $8, %rsp\n"
    "  movq %rax, 16(%rsp)\n"    /* stash return value in the n slot */
    "  popq %r11\n"
    "  popq %rcx\n"
    "  popq %rax\n"
    "  popq %rdi\n"
    "  popq %rsi\n"
    "  popq %rdx\n"
    "  popq %r10\n"
    "  popq %r8\n"
    "  popq %r9\n"
    "  xchgq %rsp, syscall_kstack(%rip)\n"
    "  cmpq $" STR(USER_WIN_LO) ", %rsp\n"
    "  jb 1f\n"
    "  cmpq $" STR(USER_WIN_HI) ", %rsp\n"
    "  jae 1f\n"
    "  sysretq\n"
    "1:\n"
    "  jmp *%rcx\n"
);


/* k_exec_user, k_run_rel, kexit moved to kernel/exec.c */


/* The entire shell (console line reader, history, completion, built-in
 * editor, builtin commands, shell_run) moved to kernel/shell.c. */


/* ================================================================
 *  Libc symbol registration
 * ================================================================ */

static void register_libc_symbols(void) {
    /* String functions */
    k_register_symbol("strlen",   (void *)kstrlen);
    k_register_symbol("strcpy",   (void *)kstrcpy);
    k_register_symbol("strncpy",  (void *)kstrncpy);
    k_register_symbol("strncat",  (void *)kstrncat);
    k_register_symbol("strcmp",   (void *)kstrcmp);
    k_register_symbol("strncmp",  (void *)kstrncmp);
    k_register_symbol("strchr",   (void *)kstrchr);
    k_register_symbol("strstr",   (void *)kstrstr);
    k_register_symbol("memcpy",   (void *)kmemcpy);
    k_register_symbol("memmove",  (void *)kmemmove);
    k_register_symbol("memset",   (void *)kmemset);
    k_register_symbol("memcmp",   (void *)kmemcmp);
    k_register_symbol("strlen",   (void *)kstrlen);

    /* Memory */
    k_register_symbol("malloc",   (void *)kmalloc);
    k_register_symbol("free",     (void *)kfree);
    k_register_symbol("calloc",   (void *)kcalloc);
    k_register_symbol("realloc",  (void *)krealloc);

    /* Hash (xxHash XXH64) */
    k_register_symbol("XXH64",    (void *)XXH64);

    /* stb image API (third_party/stb, PNG/TGA decode) */
    k_register_symbol("stbi_load_file", (void *)stbi_load_file);
    k_register_symbol("stbi_load_from_memory", (void *)stbi_load_from_memory);
    k_register_symbol("stbi_image_free", (void *)stbi_image_free);

    /* File I/O */
    k_register_symbol("fopen",    (void *)kfopen);
    k_register_symbol("fclose",   (void *)kfclose);
    k_register_symbol("fread",    (void *)kfread);
    k_register_symbol("fwrite",   (void *)kfwrite);
    k_register_symbol("fseek",    (void *)kfseek);
    k_register_symbol("ftell",    (void *)kftell);
    k_register_symbol("fputs",    (void *)kfputs);
    k_register_symbol("fputc",    (void *)kfputc);
    k_register_symbol("fgetc",    (void *)kfgetc);
    k_register_symbol("fgets",    (void *)kfgets);
    k_register_symbol("ungetc",   (void *)kfungetc);
    k_register_symbol("fflush",   (void *)kfflush);
    k_register_symbol("rewind",   (void *)krewind);
    k_register_symbol("fprintf",  (void *)kfprintf);

    /* Output */
    k_register_symbol("printf",   (void *)kprintf);
    k_register_symbol("sprintf",  (void *)ksprintf);
    k_register_symbol("putchar",  (void *)vga_putc);
    k_register_symbol("puts",     (void *)vga_puts);

    /* Stdio streams are FILE* *variables*: register the address of each. */
    k_register_symbol("stdin",    (void *)&kstdin);
    k_register_symbol("stdout",   (void *)&kstdout);
    k_register_symbol("stderr",   (void *)&kstderr);

    /* Exit */
    k_register_symbol("exit",     (void *)kexit);

    /* Additional libc */
    k_register_symbol("snprintf", (void *)ksnprintf);
    k_register_symbol("atol",     (void *)katol);
    k_register_symbol("strtol",   (void *)katol);
    k_register_symbol("abort",    (void *)kexit);
}


/* ================================================================
 *  Kernel entry point
 * ================================================================ */

extern char ramdisk_start[];
extern char ramdisk_end[];

__attribute__((section(".init.text")))
void kmain(void) {
    __asm__ volatile(
        "mov $0x10, %%ax\n"
        "mov %%ax, %%ds\n"
        "mov %%ax, %%es\n"
        "mov %%ax, %%fs\n"
        "mov %%ax, %%gs\n"
        "mov %%ax, %%ss\n"
        "mov $0x90000, %%rsp\n"
        ::: "ax"
    );

    /* Enable SSE so loaded programs (and Linux binaries) may use XMM/SSE2.
     * CR0: clear EM (bit 2), set MP (bit 1); CR4: set OSFXSR|OSXMMEXCPT. */
    __asm__ volatile(
        "mov %%cr0, %%rax\n"
        "and $0xFFFFFFFFFFFFFFFB, %%rax\n"
        "or  $0x2, %%rax\n"
        "mov %%rax, %%cr0\n"
        "mov %%cr4, %%rax\n"
        "or  $0x600, %%rax\n"
        "mov %%rax, %%cr4\n"
        ::: "rax"
    );

    serial_init();
    vga_clear();
    vga_puts("MiniOS Kernel v0.3\n====================\n");

    kallocator_init();
    ramdisk_init();
    register_libc_symbols();
    syscall_init();
    vga_fb_boot_config();
    mm_setup_protections();
    kprintf("fb: %dx%d pitch %d base 0x%lx\n",
            fb_width, fb_height, fb_pitch, fb_phys_base);
    kprintf("kernel: physical base 0x%x, user pages 4 KB with NX\n",
            *(unsigned *)BOOT_KASLR_ADDR);
    kprintf("isolation: user window %x..%x ring 3, syscall ABI on %x\n",
            USER_LOAD_BASE, USER_LOAD_END, SYS_KSTK_TOP);
    net_init();

    if ((unsigned long)(ramdisk_end - ramdisk_start) > 0) {
        ramdisk_setup_from(ramdisk_start, (unsigned)(ramdisk_end - ramdisk_start));
    }

    block_init();
    minifs_init();
    if (ide_present()) {
        if (minifs_mount() < 0) {
            kprintf("minifs: no filesystem found on disk\n");
        }
    }

    /* Register VFS drivers.  Ramdisk is always available; MiniFS is
     * registered only when the IDE disk was found and mounted. */
    vfs_register_builtins();

    kprintf("Heap: %d MB  Symbols: %d  (Linux ELF: syscall ABI ready)\n",
            (int)(HEAP_SIZE >> 20), ksym_count);

    /* Initialize the scheduler: IDT, TSS, PIC, PIT timer.
     * This enables interrupts and the 100 Hz timer tick. */
    sched_init();
    kprintf("Scheduler: IDT 256 entries, TSS loaded, PIT 100 Hz, preemptive\n");

    vga_fb_init();

    /* Probe the Sound Blaster 16 for real audio; fall back to the PC speaker
     * when none is present. */
    if (sb16_init())
        kprintf("sb16: DSP probed, 8-bit %d Hz DMA channel 1\n", 22050);
    else
        kprintf("sb16: not present, PC speaker stays the audio sink\n");

    /* Wake the application processors; fail-safe, APs idle, system unchanged. */
    smp_init();

    shell_run();
}
