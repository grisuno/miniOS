#include "kernel.h"
#include "bootdefs.h"
#include "smp.h"
#include "sched.h"
#include "ap_stub.h"
#include "arch/x86/msr.h"

/* SMP application-processor bring-up.
 *
 * The BSP maps the local APIC (0xFEE00000) into the page tables, enables it,
 * copies the flat AP bootstrap stub (ap_entry.S) to AP_STUB_ADDR, patches the
 * address of smp_ap_entry into it, and wakes every AP with the standard
 * INIT -> wait -> SIPI -> SIPI sequence (delivery to all-except-self).  Each
 * AP runs the stub, enters long mode, calls smp_ap_entry(), initializes its
 * per-CPU state (cpu_t, GS base, IDTR, LAPIC timer), and enters an idle loop.
 *
 * The APs do NOT yet run the scheduler (no process dispatch), but they are
 * fully interrupt-capable with their own LAPIC timers, which lays the
 * foundation for Phase 2 SMP scheduling.  Everything here is fail-safe:
 * if the LAPIC cannot be reached or no AP answers, smp_init just reports the
 * BSP and returns, and the kernel boots exactly as before.
 *
 * Per-CPU vs shared (documented in smp.h):
 *   Per-CPU: LAPIC ID, cpu_t entry, GS base, LAPIC timer, idle loop
 *   Shared:  ap_count (lockless atomic), procs[] (sched_lock),
 *            LAPIC ICR (BSP-only writes) */

#define LAPIC_BASE      0xFEE00000u
#define LAPIC_ID_OFF    0x020u
#define LAPIC_SVR_OFF   0x0F0u
#define LAPIC_ICR_HI    0x310u
#define LAPIC_ICR_LO    0x300u
#define LAPIC_LVT_TIMER 0x320u   /* timer LVT */
#define LAPIC_LVT_LINT0 0x350u   /* local pin 0 (PIC INTR line in virtual wire) */
#define LAPIC_LVT_LINT1 0x360u   /* local pin 1 (NMI) */
#define LAPIC_LVT_MASKED 0x10000u
#define LAPIC_LVT_EXTINT 0x700u  /* delivery mode 7: passthrough from PIC */
#define LAPIC_EOI_OFF   0x0B0u
#define LAPIC_TIMER_DIV 0x3E0u
#define LAPIC_TIMER_INIT 0x380u
#define LAPIC_TIMER_CUR 0x390u

#define LAPIC_SVR_ENABLE  0x100u
#define LAPIC_ICR_BUSY    0x1000u
#define LAPIC_ICR_INIT    0x500u
#define LAPIC_ICR_SIPI    0x600u
#define LAPIC_ICR_ALL_EXC 0xC0000u  /* destination shorthand: all excl. self (bits 19:18) */
#define LAPIC_ICR_LEVEL   0x4000u   /* level-assert (bit 14) */
#define LAPIC_ICR_TRIGGER 0x8000u   /* level-trigger mode (bit 15) */

#define SIPI_VECTOR       (AP_STUB_ADDR >> 12)

/* PIT frequency used by the BSP for calibration. */
#define PIT_HZ            1193182u

/* LAPIC timer divide-by-16, periodic mode, vector 32 (same as PIT). */
#define LAPIC_TIMER_DIVIDE_16  0x03u
#define LAPIC_TIMER_PERIODIC   0x20000u

/* LAPIC region mapped as 2 MB uncached (PCD|PWT) pages.  A dedicated PD is
 * parked at 0x70000 (identity mapped, fixed), just above the user page-table
 * zone [0x10000,0x70000) and below the syscall kernel stack (0x88000).  It
 * must NOT sit at 0x60000: with a 192 MB user window the page-table zone
 * extends there and the index-82 PT (the ~165 MB window) lives at 0x60000, so
 * zeroing a LAPIC PD there would unmaps those user pages. */
#define LAPIC_PD_ADDR     0x70000u
#define LAPIC_PDPT_SLOT   (LAPIC_BASE / 0x40000000u)          /* = 3 */
#define LAPIC_PD_IDX      ((LAPIC_BASE / 0x200000u) % 512u)   /* = 503 */

static volatile unsigned ap_count;
spinlock_t smp_lock = SPINLOCK_INIT;
volatile unsigned smp_dbg_svr;
volatile unsigned smp_dbg_lvt;
volatile unsigned smp_dbg_ipis;
volatile unsigned smp_dbg_sent;

/* Per-AP kernel stack for the idle loop entry (the 2 KB stub stack is
 * too shallow for the loop's C frames plus nested IPI ISRs). */
static char ap_idle_kstack[MAX_CPUS][8192] __attribute__((aligned(16)));

/* The syscall trampoline lives in kernel.c (declared global there). */
extern void syscall_entry(void);

static unsigned lapic_read(unsigned off) {
    return *(volatile unsigned *)(unsigned long)(LAPIC_BASE + off);
}
static void lapic_write(unsigned off, unsigned val) {
    *(volatile unsigned *)(unsigned long)(LAPIC_BASE + off) = val;
}

/* Broadcast one fixed-delivery IPI to every other CPU.  The BSP timer
 * ISR uses this as the SMP tick: QEMU's per-AP LAPIC timers are not a
 * dependable wakeup for a halted AP (an AP that never wakes cannot
 * claim work), so the BSP shares its PIT tick over the IPI.  Delivery
 * mode 0 (fixed), destination shorthand all-excluding-self.  BSP-only:
 * ICR contention is avoided by construction. */
void smp_ipi_broadcast(int vector) {
    lapic_write(LAPIC_ICR_HI, 0);
    /* Fixed delivery needs the level-assert bit (14); without it the
     * IPI is a deassert and QEMU drops it. */
    lapic_write(LAPIC_ICR_LO, LAPIC_ICR_ALL_EXC | LAPIC_ICR_LEVEL
                              | (unsigned)vector);
}

/* Map the LAPIC so the BSP can program the ICR, and the APs can read their id
 * registers.  Extends stage 2's tables: PDPT slot 3 gains a new PD whose
 * entry covers the LAPIC's 2 MB window as uncached.  Returns 1 on success. */
static int map_lapic(void) {
    unsigned long *pd = (unsigned long *)LAPIC_PD_ADDR;
    unsigned long *pdpt = (unsigned long *)(unsigned long)PT_PDPT_ADDR;
    unsigned i;
    for (i = 0; i < 512; i++) pd[i] = 0;
    /* 2 MB identity leaf, present|rw|PCD|PWT (uncached) */
    pd[LAPIC_PD_IDX] = (unsigned long)(LAPIC_BASE & ~0x1FFFFFu)
                       | 0x0000000000000083u;
    pdpt[LAPIC_PDPT_SLOT] = (unsigned long)LAPIC_PD_ADDR | 0x0000000000000003u;
    __asm__ volatile("invlpg (%0)" : : "r"(LAPIC_BASE) : "memory");
    return 1;
}

static void ap_delay(void) {
    volatile unsigned long i;
    for (i = 0; i < 200000u; i++) __asm__ volatile("pause");
}

/* The AP's wakeup is the BSP's IPI tick (smp_ipi_broadcast, 100 Hz),
 * not its own LAPIC timer: the timer counts local-APIC bus clocks, so a
 * count derived from PIT_HZ fires ~84 kHz under QEMU (745 ticks at
 * divide-by-16 ~= 12 us) and wedges the machine under an interrupt
 * storm.  The local timer therefore stays MASKED; the halted AP wakes
 * only on the IPI, which also drives its preemption ISR.  The SVR must
 * still be enabled FIRST: the INIT/SIPI reset leaves each AP's LAPIC
 * disabled (the BSP's smp_init enable covers only the BSP's own unit),
 * and with the SVR off the AP cannot receive IPIs at all, so its hlt
 * never wakes and it never claims a thread. */
static void ap_lapic_timer_init(void) {
    lapic_write(LAPIC_SVR_OFF, lapic_read(LAPIC_SVR_OFF) | LAPIC_SVR_ENABLE);
    lapic_write(LAPIC_LVT_TIMER, LAPIC_LVT_MASKED);
    /* The AP has no PIC passthrough: mask both local pins so stray
     * line assertions cannot inject a bogus vector. */
    lapic_write(LAPIC_LVT_LINT0, LAPIC_LVT_MASKED);
    lapic_write(LAPIC_LVT_LINT1, LAPIC_LVT_MASKED);
    smp_dbg_svr = lapic_read(LAPIC_SVR_OFF);
    smp_dbg_lvt = lapic_read(LAPIC_LVT_TIMER);
}

/* Entry point every AP reaches from ap_entry.S.  Initializes per-CPU state,
 * GS base, IDTR, LAPIC timer and task register, then enters the AP idle
 * loop (smp_ap_idle_loop), which claims READY CLONE_VM threads and runs
 * them.  Non-VM processes stay on the BSP by construction (the AP-side
 * pick and preempt paths only ever consider CLONE_VM). */
void smp_ap_entry(void) {
    /* Progress marker: 0x42 at 0x80000 proves we reached C */
    *(volatile unsigned char *)0x80000UL = 0x42;

    unsigned id = lapic_read(LAPIC_ID_OFF) >> 24;
    int cpu = __sync_fetch_and_add(&ap_count, 1) + 1;

    /* Initialize per-CPU cpu_t */
    cpus[cpu].self = &cpus[cpu];
    cpus[cpu].cpu_id = cpu;
    cpus[cpu].cur_pid = -1;
    cpus[cpu].is_bsp = 0;
    cpus[cpu].lapic_id = id;
    cpus[cpu].idle = 1;
    cpus[cpu].syscall_kstack = SYS_KSTK_TOP;

    /* Set GS base so this_cpu() works on this AP */
    wrmsr(MSR_GSBASE, (unsigned long)&cpus[cpu]);

    /* Seed this CPU's SYSCALL swap target: without it the first ring-3
     * syscall from an AP-dispatched thread swaps in the reset MSR value
     * and the entry math reads garbage as cur_pid.  MSRs are per-CPU,
     * so the BSP's k_exec_user setup never reaches here. */
    wrmsr(MSR_KERNEL_GS_BASE, (unsigned long)&cpus[cpu]);

    /* Per-CPU SYSCALL configuration: STAR, LSTAR, SFMASK and EFER.SCE
     * were programmed only on the BSP (syscall_init runs in kmain), so
     * an AP's first sysretq loaded SS from a zeroed STAR (selector 0x08,
     * kernel code, as SS) and died with #SS.  The values mirror
     * syscall_init in kernel.c exactly. */
    wrmsr(0xC0000081u, ((unsigned long)GDT64_DATA_SEL << 48)
                       | ((unsigned long)GDT64_CODE_SEL << 32));  /* STAR */
    wrmsr(0xC0000082u, (unsigned long)syscall_entry);              /* LSTAR */
    wrmsr(0xC0000084u, 0x600);                                     /* SFMASK */
    wrmsr(0xC0000080u, (unsigned long)(rdmsr(0xC0000080u) | 1));   /* EFER.SCE */
    /* EFER is per-CPU: ap_entry.S only sets LME, so the AP runs with
     * EFER.NXE clear.  Every user-window PTE carries the NX bit, and
     * with NXE clear a set NX bit is RESERVED - any access to an
     * NX page on the AP faults with a reserved-bit #PF.  Enable NXE
     * to match the BSP's stage-2 setup. */
    wrmsr(0xC0000080u, (unsigned long)(rdmsr(0xC0000080u) | EFER_NXE));

    /* Load the BSP's IDTR (same IDT, kernel memory, identity-mapped) */
    __asm__ volatile("lidt %0" :: "m"(bsp_idtr));

    /* Private TSS so ring-3 preempts on this AP land on its own stack. */
    tss_init_ap(cpu);

    /* Mark the idle context; the first switch_to out of the idle loop
     * saves the loop registers here for later resumes.  cr3 must be the
     * kernel tables: switch_to loads next->ctx.cr3 unconditionally, so a
     * zero would wipe the page tables on the first park. */
    ap_idle_proc[cpu].pid = -1;
    ap_idle_proc[cpu].state = PROC_BLOCKED;
    ap_idle_proc[cpu].parent_pid = -1;
    {
        unsigned long cr3;
        __asm__ volatile("mov %%cr3, %0" : "=r"(cr3));
        ap_idle_proc[cpu].ctx.cr3 = cr3;
    }

    /* Configure LAPIC timer at 100 Hz */
    ap_lapic_timer_init();

    /* Update global cpu_count (visible to all CPUs) under smp_lock:
     * concurrent APs must not interleave their read-modify-write. */
    {
        irqflags_t flags;
        spin_lock_irqsave(&smp_lock, &flags);
        cpu_count = cpu + 1;
        spin_unlock_irqrestore(&smp_lock, flags);
    }

    /* The AP does NOT print here: kprintf's stack usage plus the LAPIC
     * timer ISR trap frame overflows the identity-mapped low-memory
     * stub stack and cascading exceptions result.  The BSP prints the
     * "Brought up N CPUs" message after ap_count confirms the AP
     * initialized. */

    /* Enter the scheduler idle loop.  The loop is stateless (re-reads
     * its CPU from GS on every entry), so a fresh stack each park is
     * fine — schedule() resets the idle ctx before every switch into
     * it.  Move off the 2 KB stub stack first: the loop and the IPI
     * ISRs it services need real depth. */
    cpus[cpu].idle = 1;
    __asm__ volatile("movq %0, %%rsp" ::
                        "r"(&ap_idle_kstack[cpu][8192]) :);
    smp_ap_idle_loop();
    for (;;) {
        __asm__ volatile("sti; hlt; cli");
    }
}

void smp_init(void) {
    if (!map_lapic()) return;
    lapic_write(LAPIC_SVR_OFF, lapic_read(LAPIC_SVR_OFF) | LAPIC_SVR_ENABLE);
    /* Virtual-wire mode via the local APIC: with the LAPIC enabled, the
     * PIC's INTR line only reaches the CPU through LINT0, so LINT0 must
     * be programmed as ExtINT delivery.  Without this the PIT (IRQ0)
     * stops being delivered the moment the LAPIC is enabled and the
     * whole timer-driven kernel goes dead.  LINT1 stays masked. */
    lapic_write(LAPIC_LVT_LINT0, LAPIC_LVT_EXTINT);
    lapic_write(LAPIC_LVT_LINT1, LAPIC_LVT_MASKED);

    /* Copy the flat stub and patch in the C entry point's address. */
    kmemcpy((void *)(unsigned long)AP_STUB_ADDR, ap_stub_blob, ap_stub_len);
    *(unsigned long *)(unsigned long)(AP_STUB_ADDR + ap_patch_off)
        = (unsigned long)smp_ap_entry;

    /* INIT-SIPI-SIPI per Intel MP spec.
     * INIT (edge-triggered): resets APs to wait-for-SIPI state.
     * QEMU 11 drops level-triggered INIT (delivery status never clears),
     * so edge-triggered is used.  Two SIPIs deliver the startup vector. */
    lapic_write(LAPIC_ICR_HI, 0);
    lapic_write(LAPIC_ICR_LO, LAPIC_ICR_ALL_EXC | LAPIC_ICR_INIT);
    unsigned t0;
    for (t0 = 0; t0 < 100000u; t0++) __asm__ volatile("pause");

    unsigned sipi_val = LAPIC_ICR_SIPI | SIPI_VECTOR | LAPIC_ICR_ALL_EXC;
    lapic_write(LAPIC_ICR_HI, 0);
    lapic_write(LAPIC_ICR_LO, sipi_val);
    ap_delay();
    lapic_write(LAPIC_ICR_HI, 0);
    lapic_write(LAPIC_ICR_LO, sipi_val);
    ap_delay();

    unsigned expected = 1u;
    unsigned t;
    for (t = 0; t < 500000u; t++) {
        if (ap_count >= expected) break;
        __asm__ volatile("pause");
    }

    if (ap_count)
        kprintf("SMP: Brought up %u CPUs\n", (unsigned)ap_count + 1u);
    else
        kprintf("SMP: 1 CPU (APs not woken)\n");

    /* IPI delivery probe: three fixed-mode IPIs (vector 32) from plain
     * BSP context.  The AP ISR counts them in smp_dbg_ipis; the `smp`
     * builtin prints it, so delivery is observable on the console. */
    for (t = 0; t < 3; t++) {
        smp_ipi_broadcast(32);
        for (t0 = 0; t0 < 200000u; t0++) __asm__ volatile("pause");
    }
}
