#ifndef SMP_H
#define SMP_H

/* SMP bring-up: wake the application processors (APs) via the LAPIC INIT/SIPI
 * protocol and count them.  This is deliberately a SAFE first increment: the
 * APs boot into long mode (reusing stage 2's page tables and GDT), report
 * their LAPIC id, and idle in an hlt loop.  They do NOT yet run the scheduler
 * or handle syscalls, so the existing single-core system is untouched and the
 * boot never depends on the APs (smp_init is fail-safe and returns immediately
 * when the LAPIC cannot be reached). */

void smp_init(void);
void smp_ap_entry(void);   /* entry point each AP jumps to from ap_entry.S */

#endif
