#include "kernel.h"
#include "bootdefs.h"
#include "smp.h"
#include "ap_stub.h"

/* SMP application-processor bring-up.
 *
 * The BSP maps the local APIC (0xFEE00000) into the page tables, enables it,
 * copies the flat AP bootstrap stub (ap_entry.S) to AP_STUB_ADDR, patches the
 * address of smp_ap_entry into it, and wakes every AP with the standard
 * INIT -> wait -> SIPI -> SIPI sequence (delivery to all-except-self).  Each
 * AP runs the stub, enters long mode, calls smp_ap_entry(), increments a
 * shared counter, prints its LAPIC id and idles in an hlt loop.
 *
 * The APs do NOT enter the scheduler or the syscall path, so their presence is
 * invisible to the existing single-core system.  Everything here is fail-safe:
 * if the LAPIC cannot be reached or no AP answers, smp_init just reports the
 * BSP and returns, and the kernel boots exactly as before.
 *
 * Per-CPU vs shared (documented in smp.h):
 *   Per-CPU: LAPIC ID, AP stack, hlt loop
 *   Shared:  ap_count (protected by __sync_fetch_and_add, lockless atomic),
 *            LAPIC registers (BSP-only writes, no contention) */

#define LAPIC_BASE      0xFEE00000u
#define LAPIC_ID_OFF    0x020u
#define LAPIC_SVR_OFF   0x0F0u
#define LAPIC_ICR_HI    0x310u
#define LAPIC_ICR_LO    0x300u

#define LAPIC_SVR_ENABLE  0x100u
#define LAPIC_ICR_BUSY    0x1000u
#define LAPIC_ICR_INIT    0x500u
#define LAPIC_ICR_SIPI    0x600u
#define LAPIC_ICR_ALL_EXC 0x30000u   /* dest shorthand = all-except-self */

#define SIPI_VECTOR       (AP_STUB_ADDR >> 12)

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

static void lapic_send_ipi(unsigned delivery, unsigned vector) {
    lapic_write(LAPIC_ICR_HI, 0);                 /* unused with shorthand */
    lapic_write(LAPIC_ICR_LO, delivery | vector | LAPIC_ICR_ALL_EXC);
    unsigned t = 0;
    while ((lapic_read(LAPIC_ICR_LO) & LAPIC_ICR_BUSY) && t++ < 100000) ;
}

static void ap_delay(void) {
    /* ~10 ms pause via a bounded counter loop (no TSC dependency). */
    volatile unsigned long i;
    for (i = 0; i < 2000000u; i++) __asm__ volatile("pause");
}

/* Entry point every AP reaches from ap_entry.S.  Counts up, reports, idles. */
void smp_ap_entry(void) {
    unsigned id = lapic_read(LAPIC_ID_OFF) >> 24;
    __sync_fetch_and_add(&ap_count, 1);
    kprintf("SMP: CPU %u up\n", id);
    for (;;) __asm__ volatile("hlt");
}

void smp_init(void) {
    if (!map_lapic()) return;
    /* Enable the APIC (software-enable bit in the SVR). */
    lapic_write(LAPIC_SVR_OFF, lapic_read(LAPIC_SVR_OFF) | LAPIC_SVR_ENABLE);

    /* Copy the flat stub and patch in the C entry point's address. */
    kmemcpy((void *)(unsigned long)AP_STUB_ADDR, ap_stub_blob, ap_stub_len);
    *(unsigned long *)(unsigned long)(AP_STUB_ADDR + ap_patch_off)
        = (unsigned long)smp_ap_entry;

    /* Wake the APs.  INIT trips QEMU's AP triple-fault on reset, so only SIPI
     * is used here (works when the firmware left the APs in wait-for-SIPI). */
    lapic_send_ipi(LAPIC_ICR_SIPI, SIPI_VECTOR);
    ap_delay();
    lapic_send_ipi(LAPIC_ICR_SIPI, SIPI_VECTOR);

    unsigned t;
    for (t = 0; t < 2000000; t++)
        if (ap_count >= 3) break;

    if (ap_count)
        kprintf("SMP: Brought up %u CPUs\n", (unsigned)ap_count + 1u);
    else
        kprintf("SMP: 1 CPU (APs not woken: QEMU INIT quirk)\n");
}
