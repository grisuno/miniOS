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
#define LAPIC_TIMER_DIV 0x3E0u
#define LAPIC_TIMER_INIT 0x380u
#define LAPIC_TIMER_CUR 0x390u
#define LAPIC_TIMER_VEC 0x350u

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

static unsigned lapic_read(unsigned off) {
    return *(volatile unsigned *)(unsigned long)(LAPIC_BASE + off);
}
static void lapic_write(unsigned off, unsigned val) {
    *(volatile unsigned *)(unsigned long)(LAPIC_BASE + off) = val;
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

/* Configure this AP's local LAPIC timer to fire at 100 Hz (matching the
 * BSP's PIT rate).  Uses divide-by-16 and periodic mode. */
static void ap_lapic_timer_init(void) {
    lapic_write(LAPIC_TIMER_DIV, LAPIC_TIMER_DIVIDE_16);
    lapic_write(LAPIC_TIMER_VEC, 32);
    lapic_write(LAPIC_TIMER_INIT, PIT_HZ / 100 / 16);
}

/* Entry point every AP reaches from ap_entry.S.  Initializes per-CPU state,
 * GS base, IDTR, LAPIC timer, and enters an idle loop. */
void smp_ap_entry(void) {
    /* Progress marker: 0x42 at 0x80000 proves we reached C */
    *(volatile unsigned char *)0x80000UL = 0x42;

    unsigned id = lapic_read(LAPIC_ID_OFF) >> 24;
    int cpu = __sync_fetch_and_add(&ap_count, 1) + 1;

    /* Initialize per-CPU cpu_t */
    cpus[cpu].self = &cpus[cpu];
    cpus[cpu].cpu_id = cpu;
    cpus[cpu].cur_pid = 0;
    cpus[cpu].is_bsp = 0;
    cpus[cpu].lapic_id = id;
    cpus[cpu].idle = 1;
    cpus[cpu].syscall_kstack = SYS_KSTK_TOP;

    /* Set GS base so this_cpu() works on this AP */
    wrmsr(MSR_GSBASE, (unsigned long)&cpus[cpu]);

    /* Load the BSP's IDTR (same IDT, kernel memory, identity-mapped) */
    __asm__ volatile("lidt %0" :: "m"(bsp_idtr));

    /* Configure LAPIC timer at 100 Hz */
    ap_lapic_timer_init();

    /* Update global cpu_count (visible to all CPUs) */
    cpu_count = cpu + 1;

    /* The AP does NOT print here: kprintf's stack usage plus the LAPIC
     * timer ISR trap frame overflows the identity-mapped low-memory
     * stub stack and cascading exceptions result.  The BSP prints the
     * "Brought up N CPUs" message after ap_count confirms the AP
     * initialized. */

    /* Idle loop: enable interrupts and halt.  The LAPIC timer ISR fires
     * at 100 Hz, exercising the same isr_dispatch path as the BSP.  When
     * Phase 2 enables per-CPU scheduling, work will arrive here. */
    for (;;) {
        __asm__ volatile("sti; hlt; cli");
    }
}

void smp_init(void) {
    if (!map_lapic()) return;
    lapic_write(LAPIC_SVR_OFF, lapic_read(LAPIC_SVR_OFF) | LAPIC_SVR_ENABLE);

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
}
