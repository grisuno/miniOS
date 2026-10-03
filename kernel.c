/* kernel.c -- Mediator: boot orchestration and the syscall trampoline.
 *
 * Bounded-Context map (DDD): this file owns NO subsystem state. Execution
 * output lives in kernel/console.c, scheduling in kernel/sched.c, memory in
 * kernel/mm.c + vma.c, files in fs/, drivers in drivers/, network in net/.
 * kmain below only injects init order into those subsystems; the syscall
 * trampoline stays here because it is position-sensitive asm bound to the
 * proc_t layout asserted by sched.c. New logic belongs in a subsystem file,
 * never here. */
#include "kernel.h"
#include "abi.h"
#include "net.h"
#include "bootdefs.h"
#include "minifs.h"
#include "ide.h"
#include "block.h"
#include "pcache.h"
#include "drivers/virtio_blk.h"
#include "drivers/xhci.h"
#include "drivers/usbhid.h"
#include "drivers/usbblk.h"
#include "sched.h"
#include "vga_fb.h"
#include "sb16.h"
#include "smp.h"
#include "arch/x86/msr.h"

/* Text console, output capture and libc names: kernel/console.c. */
/* Scrollback ring: kernel/scrollback.c. */

/* Execution console, output capture and libc names: kernel/console.c. */


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

/* The kernel's layout constants are derived from minios_abi.h, and the
 * syscall trampoline's numerics (headers/syscall_asm.h, consumed by
 * arch/x86/syscall_entry.S) are checked against them at compile time,
 * so a layout edit in the ABI header can never silently leave the
 * syscall return discriminator, the page-table zone sizing or a ring-3
 * program out of step. */
#include "syscall_asm.h"
_Static_assert(SYSCALL_USER_WIN_LO == MINIOS_USER_LOAD_BASE, "syscall win lo drift");
_Static_assert(SYSCALL_USER_WIN_HI == MINIOS_USER_LOAD_END, "syscall win hi drift");
_Static_assert(SYSCALL_PROC_T_SIZE == PROC_T_SIZE, "syscall proc size drift");
_Static_assert(SYSCALL_PROC_KSTACK_OFF == PROC_KSTACK_OFF, "syscall kstack off drift");
_Static_assert(SYSCALL_MAX_PROCS == MAX_PROCS, "syscall max procs drift");
_Static_assert(USER_LOAD_BASE == MINIOS_USER_LOAD_BASE, "USER_LOAD_BASE drift");
_Static_assert(USER_LOAD_END == MINIOS_USER_LOAD_END, "USER_LOAD_END drift");
_Static_assert(USER_STACK_TOP == MINIOS_USER_STACK_TOP, "USER_STACK_TOP drift");
_Static_assert(USER_BRK_END == MINIOS_USER_BRK_END, "USER_BRK_END drift");
_Static_assert(LDSO_REGION_BASE == MINIOS_LDSO_BASE, "LDSO_BASE drift");
_Static_assert(LDSO_REGION_SIZE == MINIOS_LDSO_SIZE, "LDSO_SIZE drift");
_Static_assert(LDSO_REGION_END == MINIOS_LDSO_END, "LDSO_END drift");
_Static_assert(MINIOS_LDSO_END <= MINIOS_DOOM_BACKBUF_ADDR, "LDSO overlaps graphics tail");
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


/* ksyscall_dispatch, per-process fd views, user_range_ok, user_str_ok,
 * k_syscall_spawn moved to kernel/syscalls.c */


/* ---- syscall trampoline (arch/x86/syscall_entry.S) ----------------------
 * The entry path lives in a dedicated assembly file now (it used to be
 * a 180-line inline-asm string here): standard GNU directives, .cfi
 * unwind info, no optimizer interaction. The design contract moved
 * with it; see the header comment there. What stays here are the
 * machine-checked layout proofs the .S file cannot express in C. */

/* cpu_t layout contract for arch/x86/syscall_entry.S: it reads cur_pid
 * at gs:12 (gs:0 is the self pointer for this_cpu(), gs:8 is cpu_id).
 * Reading gs:8 instead resolves every thread to the wrong kstack (0 on
 * the BSP, 1 on APs): harmless while a single process runs, fatal as
 * soon as two threads syscall concurrently. */
_Static_assert(__builtin_offsetof(cpu_t, cur_pid) == 12, "cpu cur_pid off");
_Static_assert(__builtin_offsetof(cpu_t, cpu_id) == 8, "cpu cpu_id off");
_Static_assert(__builtin_offsetof(cpu_t, sc_n) == 72, "cpu sc_n off");
_Static_assert(__builtin_offsetof(cpu_t, sc_rip) == 80, "cpu sc_rip off");
_Static_assert(__builtin_offsetof(cpu_t, sc_pid) == 88, "cpu sc_pid off");
_Static_assert(__builtin_offsetof(cpu_t, sc_ret) == 96, "cpu sc_ret off");
_Static_assert(__builtin_offsetof(cpu_t, sc_tmp) == 112, "cpu sc_tmp off");
_Static_assert(__builtin_offsetof(cpu_t, cur_pid) == SYSCALL_CPU_CUR_PID_OFF, "syscall pid off");
_Static_assert(__builtin_offsetof(cpu_t, sc_n) == SYSCALL_CPU_SC_N_OFF, "syscall n off");
_Static_assert(__builtin_offsetof(cpu_t, sc_rip) == SYSCALL_CPU_SC_RIP_OFF, "syscall rip off");
_Static_assert(__builtin_offsetof(cpu_t, sc_pid) == SYSCALL_CPU_SC_PID_OFF, "syscall pid2 off");
_Static_assert(__builtin_offsetof(cpu_t, sc_ret) == SYSCALL_CPU_SC_RET_OFF, "syscall ret off");
_Static_assert(__builtin_offsetof(cpu_t, sc_tmp) == SYSCALL_CPU_SC_TMP_OFF, "syscall tmp off");



/* k_exec_user, k_run_rel, kexit moved to kernel/exec.c */


/* The entire shell (console line reader, history, completion, built-in
 * editor, builtin commands, shell_run) moved to kernel/shell.c. */


/* Libc symbol registration: kernel/console.c. */


/* ================================================================
 *  Kernel entry point
 * ================================================================ */

extern char ramdisk_start[];
extern char ramdisk_end[];
/* ramdisk_size decl + ramdisk_image_size() wrapper live in kernel.h. */

/* `bootlog` -- timestamped boot-phase marks for the observability set.
 * ktime_ms is PIT-calibrated only after sched_init, so early marks read
 * 0 ms (TSC ticks since power-on divided down, still monotonic); later
 * marks are wall milliseconds. Fixed table, no heap, no locks: marks are
 * appended before the shell runs (single CPU), reads are shell-time. */
#define BOOTLOG_MAX 12
static const char *bootlog_name[BOOTLOG_MAX];
static unsigned long bootlog_ms[BOOTLOG_MAX];
static int bootlog_n;
void bootlog_mark(const char *name) {
    unsigned long ms = ktime_ms();
    if (bootlog_n < 0 || bootlog_n >= BOOTLOG_MAX) return;
    bootlog_name[bootlog_n] = name;
    bootlog_ms[bootlog_n] = ms;
    bootlog_n++;
}
void bootlog_report(void) {
    int i;
    kprintf("bootlog: %d phases (ms since power-on)\n", bootlog_n);
    for (i = 0; i < bootlog_n; i++)
        kprintf("  +%6lums %s\n", bootlog_ms[i], bootlog_name[i]);
    if (!bootlog_n) kprintf("  (empty)\n");
}

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
    /* Mask every PIC line immediately: until sched_init's pic_init
     * remaps the 8259s and installs the IDT, the power-on vector base
     * (0x70 for the slave) delivers hardware IRQs (e.g. IDE IRQ14
     * during the pre-IDT disk probe) into the real-mode IVT, whose
     * garbage gates triple-fault the machine. */
    outb(0x21, 0xFF);
    outb(0xA1, 0xFF);
    vga_puts("MiniOS Kernel v0.3\n====================\n");
    bootlog_mark("entry");

    kallocator_init();
    bootlog_mark("heap");
    ramdisk_init();
    register_libc_symbols();
    syscall_init();
    vga_fb_boot_config();
    mm_setup_protections();
    bootlog_mark("mm+fb");
    kprintf("fb: %dx%d pitch %d bpp %d base 0x%lx\n",
            fb_width, fb_height, fb_pitch, fb_bpp, fb_phys_base);
    kprintf("kernel: physical base 0x%x, user pages 4 KB with NX\n",
            *(unsigned *)BOOT_KASLR_ADDR);
    kprintf("isolation: user window %x..%x ring 3, syscall ABI on %x\n",
            USER_LOAD_BASE, USER_LOAD_END, SYS_KSTK_TOP);
    net_init();

    /* ramdisk_size is an absolute linker symbol whose address IS the
     * image size (see kernel.ld); no pointer subtraction involved. */
    if (ramdisk_image_size() > 0) {
        ramdisk_setup_from(ramdisk_start, (unsigned)ramdisk_image_size());
    }

    /* ABI generation gate: the ramdisk must come from the same source
     * generation as this kernel. A stale or foreign ramdisk halts here
     * with a diagnostic instead of running mismatched binaries. */
    {
        int abi_rc = abi_check_manifest();
        if (abi_rc != ABI_OK) {
            kprintf("abi: manifest check failed (%d), halting; rebuild the image",
                    abi_rc);
            for (;;) __asm__ volatile("hlt");
        }
        kprintf("abi: manifest ok (v%d)\n", MINIOS_ABI_VERSION);
    }

    /* Bring up USB before the block layer, so a USB stick is a backend
     * candidate rather than a device discovered too late to be used. This is
     * a probe that finds nothing on a machine with no xHCI controller, and
     * the boot is unchanged in that case. The controller needs the page
     * tables (already built above) for its uncached register window and the
     * heap for its rings, and it needs no interrupt, so it runs before the IDT
     * exists without risk. */
    if (xhc_init()) {
        unsigned version = 0;
        unsigned slots = 0;
        unsigned ports = 0;
        int found = xhc_enumerate_all();
        int hid;
        xhc_info(&version, &slots, &ports, 0);
        kprintf("usb: xHCI %u.%u, %u slots, %u ports, %d devices\n",
                (version >> 8) & 0xFFu, version & 0xFFu, slots, ports, found);
        hid = usbhid_init();
        if (hid)
            kprintf("usb: hid kbd=%d mouse=%d\n", usbhid_keyboard_present(),
                    usbhid_mouse_present());
    }

    block_init();
    pcache_init();
    minifs_init();
    bootlog_mark("block+minifs");
    if (ide_present() || vblk_present() || ubk_present()) {
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
    bootlog_mark("sched");

    vga_fb_init();

    /* Probe the Sound Blaster 16 for real audio; fall back to the PC speaker
     * when none is present. */
    if (sb16_init())
        kprintf("sb16: DSP probed, 8-bit %d Hz DMA channel 1\n", 22050);
    else
        kprintf("sb16: not present, PC speaker stays the audio sink\n");

    /* Wake the application processors; fail-safe, APs idle, system unchanged. */
    smp_init();
    bootlog_mark("smp+audio-ready");

    shell_run();
}
