#ifndef SMP_H
#define SMP_H

#include "spinlock.h"

/* SMP bring-up: wake the application processors (APs) via the LAPIC INIT/SIPI
 * protocol and count them.  This is deliberately a SAFE first increment: the
 * APs boot into long mode (reusing stage 2's page tables and GDT), report
 * their LAPIC id, and idle in an hlt loop.  They do NOT yet run the scheduler
 * or handle syscalls, so the existing single-core system is untouched and the
 * boot never depends on the APs (smp_init is fail-safe and returns immediately
 * when the LAPIC cannot be reached).
 *
 * Per-CPU vs shared structures:
 *   Per-CPU (no lock needed):
 *     - LAPIC ID register (read-only per AP)
 *     - AP stack (each AP has its own stack from ap_entry.S)
 *     - hlt loop (each AP idles independently)
 *   Shared (protected by smp_lock):
 *     - ap_count: atomic counter incremented by each AP on startup
 *     - LAPIC ICR: only the BSP sends IPIs, so no contention
 *     - LAPIC SVR: only the BSP enables the APIC, so no contention
 */

extern spinlock_t smp_lock;

/* Read-back diagnostics written by the AP after its LAPIC setup; the
 * `smp` builtin prints them so a dead AP's APIC state is visible over
 * the serial console. */
extern volatile unsigned smp_dbg_svr;
extern volatile unsigned smp_dbg_lvt;
extern volatile unsigned smp_dbg_ipis;  /* vector-32 ISRs run on APs */
extern volatile unsigned smp_dbg_sent;   /* IPIs the BSP tick sent */

void smp_init(void);
void smp_ap_entry(void);   /* entry point each AP jumps to from ap_entry.S */
void smp_ipi_broadcast(int vector);  /* fixed-delivery IPI, all except self */

#endif
